// The effect system, second pass (slice fx2): the streamer kinds 1 / 2 of effect class 16 (kind rows 0x69C970 + 28 *
// kind) and the class-16 instance allocator sub_345CF0. Records: fx2.h (namespace fx2).
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

// 0x00342480 sub_342480 -- 208 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 1, slot 0 [k16Streamer1Init] ($a0 = the instance): every strand's material colour (mesh +40 [i])
// takes the tint gp-18348 (alpha 255 written as 254 and restored) and its record is marked free (word 0 = -1; 48-byte
// records).
void sub_342480(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, gp{ctx, 28};
    // 0x00342480
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    lw(a3, a1, 0);
    lw(v1, a0, 64);
    lw(a0, v1, 56);
    a2 = 0;
    v1 = 255;
    t6 = 254;
    t1 = si(-1);
    for (;;) {
        // 0x0034253c
        charge(ctx, 3);
        t0 = sltu(a2, a0);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003424a8
        charge(ctx, 4);
        lw(t3, a1, 4);
        lbu(t0, gp, -18345);  // 0x7CE547
        if (t0 == v1) {
            // 0x003424f4
            charge(ctx, 15);
            sb(t6, gp, -18345);  // 0x7CE547
            t0 = a2 & 0xFFFF;
            t2 = sll(t0, 2);
            lw(t0, t3, 40);
            t0 = addu(t0, t2);
            lw(t5, t0, 0);
            lbu(t4, gp, -18348);  // 0x7CE544
            lbu(t3, gp, -18347);  // 0x7CE545
            lbu(t2, gp, -18346);  // 0x7CE546
            lbu(t0, gp, -18345);  // 0x7CE547
            sb(t4, t5, 4);
            sb(t3, t5, 5);
            sb(t2, t5, 6);
            sb(t0, t5, 7);
            sb(v1, gp, -18345);  // 0x7CE547
        } else {
            // 0x003424b8
            charge(ctx, 15);
            t0 = a2 & 0xFFFF;
            t2 = sll(t0, 2);
            lw(t0, t3, 40);
            t0 = addu(t0, t2);
            lw(t5, t0, 0);
            lbu(t4, gp, -18348);  // 0x7CE544
            lbu(t3, gp, -18347);  // 0x7CE545
            lbu(t2, gp, -18346);  // 0x7CE546
            lbu(t0, gp, -18345);  // 0x7CE547
            sb(t4, t5, 4);
            sb(t3, t5, 5);
            sb(t2, t5, 6);
            sb(t0, t5, 7);
        }
        // 0x00342530
        charge(ctx, 3);
        sw(t1, a3, 0);
        a2 = addiu(a2, 1);
        a3 = addiu(a3, 48);
    }
    // 0x00342548
    charge(ctx, 2);
}

// 0x00342550 sub_342550 -- 824 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 1 [k16Streamer1Geometry] ($a0 = the kind object, $a1 = the kind parameters): locks the mesh
// (prelight + texcoords) and writes the first strand: for each of the segments + 1 points (+140) a prelight colour
// white with the alpha ramp of the fade-in / fade-out fractions (+120 / +124) and the texture coordinates (u 0 / 1, v
// advancing by +144 / 3); then copies that strand to every other one (memcpy) and unlocks (re-instance when flagged).
void sub_342550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00342550
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    s3 = a0;
    s4 = a1;
    lw(fp, a1, 56);
    if (fp != 0) {
        // 0x00342590
        charge(ctx, 55);
        lw(v0, s3, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4088;
        jal(ctx, 0x3425A0u, gen::fn_geometryLock_00493370);
        lw(v0, s3, 4);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(s1, v0, 48);
        s2 = s1;
        lw(s7, v0, 52);
        s0 = s7;
        v0 = 0x40400000;
        mtc1(v0, f2);
        lwc1(f0, s4, 144);
        div_s(f8, f0, f2);
        lw(a3, s4, 140);
        mtc1(a3, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s4, 120);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        lwc1(f0, s4, 124);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        a0 = addiu(a3, 1);
        v1 = sll(a0, 2);
        t0 = 0;
        t1 = subu(a3, a1);
        v0 = 0x40000000;
        mtc1(v0, f0);
        mul_s(f7, f0, f8);
        mul_s(f6, f2, f8);
        v0 = 0x3F800000;
        mtc1(v0, f3);
        mtc1(t1, f0);
        cvt_s_w(f4, f0);
        mtc1(a2, f0);
        cvt_s_w(f5, f0);
        v0 = 0xFF0000;
        v0 = v0 | 0xFFFF;  // &0xFFFFFF
        t1 = 0x437F0000;
        mtc1(t1, f2);
        t1 = 0x4F000000;
        mtc1(t1, f1);
        t5 = lui(0x8000);
        for (;;) {
            // 0x003427c0
            charge(ctx, 3);
            t1 = sltu(t0, a0);
            if (t1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034266c
            charge(ctx, 3);
            at = sltu(t0, a2);
            if (at == 0) {
                // 0x003426d0
                charge(ctx, 3);
                at = sltu(a1, t0);
                if (at == 0) {
                    // 0x00342738
                    charge(ctx, 1);
                    mov_s(f0, f3);
                } else {
                    // 0x003426dc
                    charge(ctx, 3);
                    t1 = subu(a3, t0);
                    if (i64(t1) < 0) {
                        // 0x003426fc
                        charge(ctx, 7);
                        t2 = srl(t1, 1);
                        t1 = t1 & 0x1;
                        t2 = t2 | t1;
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003426e8
                        charge(ctx, 5);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x00342718
                    charge(ctx, 8);
                    div_s(f0, f0, f4);
                }
            } else {
                // 0x00342678
                charge(ctx, 2);
                if (i64(t0) < 0) {
                    // 0x00342694
                    charge(ctx, 7);
                    t2 = srl(t0, 1);
                    t1 = t0 & 0x1;
                    t2 = t2 | t1;
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00342680
                    charge(ctx, 5);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x003426b0
                charge(ctx, 8);
                div_s(f0, f0, f5);
            }
            // 0x0034273c
            charge(ctx, 5);
            sw(v0, s2, 0);
            mul_s(f0, f2, f0);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00342760
                charge(ctx, 5);
                sub_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(t1, f0);
                t1 = t1 | t5;
            } else {
                // 0x00342750
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t1, f0);
            }
            // 0x00342774
            charge(ctx, 19);
            t1 = sll(t1, 24);
            t1 = t1 | v0;
            sw(t1, s2, 4);
            lbu(t4, s2, 4);
            lbu(t3, s2, 5);
            lbu(t2, s2, 6);
            lbu(t1, s2, 7);
            sb(t4, s2, 8);
            sb(t3, s2, 9);
            sb(t2, s2, 10);
            sb(t1, s2, 11);
            sw(v0, s2, 12);
            s2 = addiu(s2, 16);
            sw(zero, s0, 0);
            swc1(f8, s0, 8);
            swc1(f7, s0, 16);
            swc1(f6, s0, 24);
            s0 = addiu(s0, 32);
            t0 = addiu(t0, 1);
        }
        // 0x003427cc
        charge(ctx, 5);
        s4 = 1;
        s6 = sll(v1, 2);
        s5 = sll(v1, 3);
        for (;;) {
            // 0x00342814
            charge(ctx, 3);
            v0 = sltu(s4, fp);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003427e0
            charge(ctx, 13);
            a0 = s2;
            a1 = s1;
            a2 = s6;
            jal(ctx, 0x3427ECu, gen::fn_memcpy_00521250);
            s2 = addu(s2, s6);
            a0 = s0;
            a1 = s7;
            a2 = s5;
            jal(ctx, 0x342804u, gen::fn_memcpy_00521250);
            s0 = addu(s0, s5);
            s4 = addiu(s4, 1);
        }
        // 0x00342820
        charge(ctx, 10);
        lw(s1, s3, 4);
        lw(v0, s1, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x342830u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s1, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x00342848
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x00342854 (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0xA0);
}

// 0x00342990 sub_342990 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 1, slot 3 [k16Streamer1Clone] ($a0 = the instance; returns a new kind object): a copy for a clone:
// the same block, the segments raised to 3, the mesh duplicated (sub_324160 of the old object's mesh, the RW mesh
// creation) and the strand geometry by sub_342550.
void sub_342990(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00342990
    enter(ctx, 25);  // entry check point + this block's cycles
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
    v0 = sll(v0, 4);
    a0 = addiu(v0, 12);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3429CCu, v0.u());
    s2 = v0;
    v1 = addiu(s2, 12);
    sw(v1, v0, 0);
    sw(s2, v0, 8);
    lw(v0, s1, 140);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x003429f4
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s1, 140);
    }
    // 0x003429fc
    charge(ctx, 16);
    lw(a0, s0, 4);
    jal(ctx, 0x342A00u, gen::fn_sub_324160_00324160);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x342A14u, gen::fn_sub_342550_00342550);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00342A90 sub_342A90 -- 2432 bytes; frame 0x170: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 1, slot 4 [k16Streamer1Update] ($a0 = the instance): within the lifetime, with a strand life (+128).
// The emission period is +132 (only on frame 0 with the once flag +184). The mesh is locked (vertices + prelight +
// texcoords) and each 48-byte record runs: -2 finished; age >= life: the strand dies (vertices cleared unless +136
// keeps them, colour back to the tint); -1 free: (re-)emitted with a random direction, speed and spin from the
// parameters (sub_358030 / sub_357FD0, cosf / sinf); live: the head moves, every point of the strand shifts one place
// back and the head point is rebuilt (VU0); unlock, re-instance when flagged.
void sub_342A90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x00342a90
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
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
    swc1(f31, sp, 0x2C);
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
    lw(v1, s1, kStmLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x00342b04
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00342b0c;
        }
        // 0x003433ac (the shared epilogue, written out on this path)
        charge(ctx, 25);
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
        lwc1(f31, sp, 0x2C);
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
        sp = addiu(sp, 0x170);
        return;
    }
L_00342b0c:
    charge(ctx, 5);
    lw(v1, s1, kStmCount);
    sq(v1, sp, 0x120);
    lw(s0, s1, kStmLife);
    if (s0 != 0) {
        // 0x00342b20
        charge(ctx, 3);
        lbu(v0, s1, kStmOnce);
        if (v0 != 0) {
            // 0x00342b2c
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_00342b4c;
            }
            // 0x00342b34
            charge(ctx, 6);
            v0 = 1;
            sw(v0, sp, 0x140);
            paddub(v0, v1, zero);
            sw(v0, sp, 0x130);
            goto L_00342b58;
        }
    L_00342b4c:
        charge(ctx, 3);
        sw(zero, sp, 0x140);
        lw(v0, s1, kStmRespawn);
        sw(v0, sp, 0x130);
    L_00342b58:
        charge(ctx, 23);
        lw(v0, a0, 60);
        lw(s4, v0, 0);
        lw(s6, v0, 4);
        lbu(v0, s1, kStmKeep);
        sq(v0, sp, 0x110);
        lwc1(f0, s1, 244);
        swc1(f0, sp, 0xF4);
        lw(v0, s6, 16);
        lw(a0, v0, 24);
        a1 = 4082;
        jal(ctx, 0x342B80u, gen::fn_geometryLock_00493370);
        lw(v0, s6, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s2, v0, 20);
        lw(s5, v1, 52);
        lh(s7, s6, 8);
        lw(v0, s1, kStmPoints);
        v0 = addiu(v0, 1);
        sq(v0, sp, 0x100);
        if (i64(v0) < 0) {
            // 0x00342bc8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f25, f0);
            add_s(f25, f25, f25);
        } else {
            // 0x00342bb4
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f25, f0);
        }
        // 0x00342be4
        charge(ctx, 21);
        lwc1(f0, s1, 152);
        swc1(f0, sp, 0xF0);
        lwc1(f0, s1, 228);
        swc1(f0, sp, 0xE8);
        lwc1(f30, s1, 164);
        fp = 0;
        v0 = 0x3F800000;
        mtc1(v0, f22);
        lwc1(f0, gp, -32416);  // 0x7CAE50
        swc1(f0, sp, 0xE4);
        v0 = 0x3F000000;
        mtc1(v0, f0);
        swc1(f0, sp, 0xE0);
        mtc1(zero, f21);
        v0 = 0x3E800000;
        mtc1(v0, f0);
        swc1(f0, sp, 0xDC);
        for (;;) {
            // 0x0034336c
            charge(ctx, 4);
            lq(v0, sp, 0x120);
            v0 = sltu(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00342c38
            charge(ctx, 4);
            lw(a0, s4, 0);
            v0 = si(-2);
            if (a0 != v0) {
                // 0x00342c48
                charge(ctx, 3);
                v1 = si(-1);
                if (a0 == v1) {
                    // 0x00342c54
                    charge(ctx, 10);
                    v0 = sll(s7, 1);
                    v0 = addu(v0, s7);
                    a2 = sll(v0, 2);
                    a0 = s2;
                    a1 = 0;
                    jal(ctx, 0x342C68u, gen::fn_memset_00521408);
                    lw(v0, sp, 0x130);
                    if (v0 != 0) {
                        // 0x00342c7c
                        charge(ctx, 25);
                        lwc1(f20, s1, 192);
                        a0 = 0;
                        jal(ctx, 0x342C84u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 188);
                        mul_s(f20, f0, f1);
                        lwc1(f23, s1, 200);
                        a0 = 0;
                        jal(ctx, 0x342CB0u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f23);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f23, f0);
                        lwc1(f0, s1, 196);
                        mul_s(f0, f0, f1);
                        sub_s(f1, f0, f20);
                        if (i64(s0) < 0) {
                            // 0x00342cf4
                            charge(ctx, 7);
                            v1 = srl(s0, 1);
                            v0 = s0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00342ce0
                            charge(ctx, 5);
                            mtc1(s0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00342d10
                        charge(ctx, 30);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 12);
                        swc1(f20, s4, 8);
                        lwc1(f20, s1, 208);
                        a0 = 0;
                        jal(ctx, 0x342D2Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 204);
                        mul_s(f20, f0, f1);
                        lwc1(f23, s1, 216);
                        a0 = 0;
                        jal(ctx, 0x342D58u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f23);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f23, f0);
                        lwc1(f0, s1, 212);
                        mul_s(f0, f0, f1);
                        sub_s(f1, f0, f20);
                        if (i64(s0) < 0) {
                            // 0x00342d9c
                            charge(ctx, 7);
                            v1 = srl(s0, 1);
                            v0 = s0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00342d88
                            charge(ctx, 5);
                            mtc1(s0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00342db8
                        charge(ctx, 74);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 20);
                        swc1(f20, s4, 16);
                        lwc1(f20, s1, 224);
                        a0 = 0;
                        jal(ctx, 0x342DD4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 232);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 40);
                        a0 = 0;
                        jal(ctx, 0x342E00u, gen::fn_sub_358030_00358030);
                        lwc1(f1, sp, 0xE4);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, 28);
                        lwc1(f20, s1, 240);
                        a0 = 0;
                        jal(ctx, 0x342E1Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 236);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 24);
                        lwc1(f20, s1, 180);
                        a0 = 0;
                        jal(ctx, 0x342E4Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 176);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 32);
                        lwc1(f20, s1, 172);
                        a0 = 0;
                        jal(ctx, 0x342E7Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 168);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 36);
                        lwc1(f20, s1, 156);
                        a0 = 0;
                        jal(ctx, 0x342EACu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f22, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 152);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 44);
                        lw(v0, sp, 0x140);
                        if (v0 == 0) {
                            // 0x00342f38
                            charge(ctx, 1);
                            sw(zero, s4, 0);
                        } else {
                            // 0x00342ee0
                            charge(ctx, 22);
                            a0 = 0;
                            jal(ctx, 0x342EE4u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                            lwc1(f0, s4, 0);
                            cvt_s_w(f3, f0);
                            lwc1(f1, s4, 20);
                            lwc1(f0, s4, 16);
                            mtc1(zero, f2);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 16);
                            lwc1(f1, s4, 12);
                            lwc1(f0, s4, 8);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 8);
                        }
                        // 0x00342f3c
                        charge(ctx, 5);
                        lw(v0, sp, 0x130);
                        v0 = addiu(v0, -1);
                        sw(v0, sp, 0x130);
                    }
                    goto L_0034334c;
                }
                // 0x00342f50
                charge(ctx, 3);
                v0 = sltu(a0, s0);
                if (v0 == 0) {
                    // 0x00342f5c
                    charge(ctx, 3);
                    lq(v0, sp, 0x110);
                    if (v0 == 0) {
                        // 0x00342f74
                        charge(ctx, 9);
                        v0 = sll(s7, 1);
                        v0 = addu(v0, s7);
                        a2 = sll(v0, 2);
                        a0 = s2;
                        a1 = 0;
                        jal(ctx, 0x342F88u, gen::fn_memset_00521408);
                        v0 = si(-2);
                        sw(v0, s4, 0);
                    } else {
                        // 0x00342f68
                        charge(ctx, 3);
                        sw(v1, s4, 0);
                    }
                    // 0x00342f98
                    charge(ctx, 4);
                    lbu(v0, gp, -18345);  // 0x7CE547
                    a3 = 255;
                    if (v0 == a3) {
                        // 0x00342fe4
                        charge(ctx, 18);
                        v0 = 254;
                        sb(v0, gp, -18345);  // 0x7CE547
                        v0 = fp & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s6, 40);
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
                        // 0x00342fa8
                        charge(ctx, 15);
                        v0 = fp & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s6, 40);
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
                    goto L_0034334c;
                }
                // 0x0034302c
                charge(ctx, 34);
                mtc1(a0, f0);
                cvt_s_w(f3, f0);
                lwc1(f0, sp, 0xF4);
                mul_s(f2, f0, f3);
                lwc1(f1, s4, 24);
                mtc1(zero, f0);
                adda_s(f0, f1);
                lwc1(f0, sp, 0xE0);
                madd_s(f0, f0, f2);
                mul_s(f1, f3, f0);
                lwc1(f0, s4, 28);
                add_s(f29, f1, f0);
                lwc1(f1, s4, 20);
                lwc1(f0, s4, 16);
                add_s(f0, f0, f1);
                swc1(f0, s4, 16);
                lwc1(f1, s4, 12);
                lwc1(f0, s4, 8);
                add_s(f0, f0, f1);
                swc1(f0, s4, 8);
                mov_s(f27, f21);
                lwc1(f0, s4, 16);
                div_s(f26, f0, f25);
                lwc1(f0, s4, 8);
                swc1(f0, sp, 0xF8);
                lwc1(f1, s4, 32);
                lwc1(f0, sp, 0xDC);
                mul_s(f31, f0, f1);
                lwc1(f0, s4, 24);
                c_lt_s(f0, f21);
                if (cond(ctx)) {
                    // 0x003430d4
                    charge(ctx, 3);
                    lwc1(f0, s4, 36);
                    neg_s(f0, f0);
                    div_s(f28, f0, f25);
                } else {
                    // 0x003430b4
                    charge(ctx, 8);
                    lwc1(f0, s4, 36);
                    div_s(f28, f0, f25);
                }
                // 0x003430e0
                charge(ctx, 8);
                swc1(f26, sp, 0x154);
                lwc1(f0, s4, 40);
                swc1(f0, sp, 0xEC);
                lwc1(f0, s4, 44);
                swc1(f0, sp, 0xFC);
                s3 = 0;
                for (;;) {
                    // 0x0034331c
                    charge(ctx, 4);
                    lq(v0, sp, 0x100);
                    v0 = sltu(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00343100
                    charge(ctx, 2);
                    if (i64(s3) < 0) {
                        // 0x0034311c
                        charge(ctx, 7);
                        v1 = srl(s3, 1);
                        v0 = s3 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x00343108
                        charge(ctx, 5);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x00343138
                    charge(ctx, 93);
                    div_s(f1, f0, f25);
                    lwc1(f0, sp, 0xE8);
                    sub_s(f0, f1, f0);
                    mul_s(f1, f0, f0);
                    lwc1(f0, sp, 0xEC);
                    mul_s(f23, f0, f1);
                    lwc1(f0, sp, 0xF8);
                    add_s(f24, f0, f23);
                    mov_s(f12, f29);
                    jal(ctx, 0x343164u, gen::fn_cosf_0052e6d8);
                    mov_s(f20, f0);
                    mov_s(f12, f29);
                    jal(ctx, 0x343174u, gen::fn_sinf_0052e878);
                    mul_s(f1, f20, f24);
                    swc1(f1, sp, 0x160);
                    swc1(f27, sp, 0x164);
                    mul_s(f1, f0, f24);
                    swc1(f1, sp, 0x168);
                    mul_s(f1, f20, f23);
                    swc1(f1, sp, 0x150);
                    mul_s(f0, f0, f23);
                    swc1(f0, sp, 0x158);
                    v0 = addiu(sp, 0x150);
                    lqc2(vf10, v0, 0);
                    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                    vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                    vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                    vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                    vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                    vwaitq(ctx);
                    vmulq(0xE, vf10, vf10);  // vmulq.xyz
                    mfc1(v0, f31);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vmove(0xF, vf11, vf10);  // vmove.xyzw
                    v0 = addiu(sp, 0x160);
                    lqc2(vf10, v0, 0);
                    vmove(0xF, vf12, vf10);  // vmove.xyzw
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    v1 = 0x6A0000;
                    v1 = addiu(v1, -15152);  // &0x69C4D0
                    sqc2(vf10, v1, 0);  // 0x69C4D0
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15152);  // 0x69C4D0
                    swc1(f0, s2, 12);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15148);  // 0x69C4D4
                    swc1(f0, s2, 16);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15144);  // 0x69C4D8
                    swc1(f0, s2, 20);
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    sqc2(vf10, v1, 0);  // 0x69C4D0
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15152);  // 0x69C4D0
                    swc1(f0, s2, 0);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15148);  // 0x69C4D4
                    swc1(f0, s2, 4);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15144);  // 0x69C4D8
                    swc1(f0, s2, 8);
                    vmove(0xF, vf10, vf12);  // vmove.xyzw
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    sqc2(vf10, v1, 0);  // 0x69C4D0
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15152);  // 0x69C4D0
                    swc1(f0, s2, 24);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15148);  // 0x69C4D4
                    swc1(f0, s2, 28);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15144);  // 0x69C4D8
                    swc1(f0, s2, 32);
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    sqc2(vf10, v1, 0);  // 0x69C4D0
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15152);  // 0x69C4D0
                    swc1(f0, s2, 36);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15148);  // 0x69C4D4
                    swc1(f0, s2, 40);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15144);  // 0x69C4D8
                    swc1(f0, s2, 44);
                    s2 = addiu(s2, 48);
                    if (i64(s3) < 0) {
                        // 0x003432c0
                        charge(ctx, 7);
                        v1 = srl(s3, 1);
                        v0 = s3 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003432ac
                        charge(ctx, 5);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003432dc
                    charge(ctx, 16);
                    div_s(f2, f0, f25);
                    mtc1(zero, f1);
                    lwc1(f0, sp, 0xFC);
                    adda_s(f1, f0);
                    lwc1(f0, sp, 0xF0);
                    madd_s(f0, f0, f2);
                    swc1(f0, s5, 4);
                    swc1(f0, s5, 12);
                    swc1(f0, s5, 20);
                    swc1(f0, s5, 28);
                    s5 = addiu(s5, 32);
                    add_s(f29, f29, f28);
                    add_s(f27, f27, f26);
                    s3 = addiu(s3, 1);
                }
                // 0x0034332c
                charge(ctx, 8);
                lwc1(f0, s4, 44);
                add_s(f0, f0, f30);
                swc1(f0, s4, 44);
                lw(v0, s4, 0);
                v0 = addiu(v0, 1);
                sw(v0, s4, 0);
                goto L_00343364;
            }
        L_0034334c:
            charge(ctx, 6);
            v0 = sll(s7, 1);
            v0 = addu(v0, s7);
            v0 = sll(v0, 2);
            s2 = addu(s2, v0);
            v0 = sll(s7, 3);
            s5 = addu(s5, v0);
        L_00343364:
            charge(ctx, 2);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 48);
        }
        // 0x0034337c
        charge(ctx, 9);
        lw(v0, s6, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x343388u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s6, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x003433a0
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x003433ac (the shared epilogue, written out on this path)
    charge(ctx, 25);
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
    lwc1(f31, sp, 0x2C);
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
    sp = addiu(sp, 0x170);
}

// 0x00343410 sub_343410 -- 884 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 1, slot 5 [k16Streamer1Draw] ($a0 = the instance): within the lifetime, the effect colour = instance
// colour (+48) x the colour track (sub_32A120 on +36) on VU0; for each strand alive (record age < life) its material
// colour = that colour x its own track (sub_32A120 on +60 at +96), else the tint gp-18348 (alpha 255 -> 254 trick);
// then the mesh gets the instance matrix (sub_3244C0 [fxSetModelMatrixB]), its additive bit from +185, and is queued
// on the layer +40 (sub_3243D0 [fxLayerAttach]).
void sub_343410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00343410
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v1, a0, 60);
    lw(s2, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s2, kStmLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0034345c
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_00343464;
        }
        // 0x00343754 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        return;
    }
L_00343464:
    charge(ctx, 46);
    lw(s3, v1, 0);
    a0 = s2;
    a1 = addiu(s2, 36);
    jal(ctx, 0x343470u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s4, 48);
    sw(v0, sp, 0xA8);
    v0 = addiu(sp, 0xA8);
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
    sw(v1, sp, 0xA4);
    v0 = addiu(sp, 0xA4);
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
    sw(v0, sp, 0xA0);
    lw(s6, sp, 0xA0);
    lw(s7, s2, kStmCount);
    lw(s5, s2, kStmLife);
    s1 = 0;
    for (;;) {
        // 0x003436f4
        charge(ctx, 3);
        v0 = sltu(s1, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034351c
        charge(ctx, 4);
        lw(a2, s3, 0);
        at = sltu(a2, s5);
        if (at == 0) {
            // 0x00343660
            charge(ctx, 4);
            lbu(v0, gp, -18345);  // 0x7CE547
            a3 = 255;
            if (v0 == a3) {
                // 0x003436ac
                charge(ctx, 16);
                v0 = 254;
                sb(v0, gp, -18345);  // 0x7CE547
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
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
                // 0x00343670
                charge(ctx, 15);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
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
        } else {
            // 0x0034352c
            charge(ctx, 44);
            a0 = addiu(s2, 60);
            a1 = addiu(s2, 96);
            a3 = s5;
            jal(ctx, 0x343538u, gen::fn_sub_32A120_0032a120);
            sw(v0, sp, 0x9C);
            v0 = addiu(sp, 0x9C);
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
            sw(s6, sp, 0x98);
            v0 = addiu(sp, 0x98);
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
            sw(v0, sp, 0x94);
            lw(v0, sp, 0x94);
            sw(v0, sp, 0xAC);
            lbu(v0, sp, 0xAF);
            a3 = 255;
            if (v0 == a3) {
                // 0x00343618
                charge(ctx, 18);
                v0 = 254;
                sb(v0, sp, 0xAF);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
                v0 = addu(v0, v1);
                lw(a2, v0, 0);
                lbu(a1, sp, 0xAC);
                lbu(a0, sp, 0xAD);
                lbu(v1, sp, 0xAE);
                lbu(v0, sp, 0xAF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
                sb(a3, sp, 0xAF);
            } else {
                // 0x003435dc
                charge(ctx, 15);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
                v0 = addu(v0, v1);
                lw(a2, v0, 0);
                lbu(a1, sp, 0xAC);
                lbu(a0, sp, 0xAD);
                lbu(v1, sp, 0xAE);
                lbu(v0, sp, 0xAF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
            }
        }
        // 0x003436ec
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        s3 = addiu(s3, 48);
    }
    // 0x00343700
    charge(ctx, 9);
    a0 = s0;
    a1 = s4;
    a2 = addiu(s4, 16);
    a3 = addiu(s4, 32);
    jal(ctx, 0x343710u, gen::fn_sub_3244C0_003244c0);
    lbu(v0, s2, kStmAdditive);
    if (v0 == 0) {
        // 0x00343738
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x00343724
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x00343744
    charge(ctx, 4);
    lhu(a1, s2, kStmLayer);
    a0 = s0;
    jal(ctx, 0x34374Cu, gen::fn_sub_3243D0_003243d0);
    // 0x00343754 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x00343790 sub_343790 -- 208 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2, slot 0 [k16Streamer2Init] ($a0 = the instance): every strand's material colour (mesh +40 [i])
// takes the tint gp-18348 (alpha 255 written as 254 and restored) and its record is marked free (word 0 = -1; 48-byte
// records).
void sub_343790(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, gp{ctx, 28};
    // 0x00343790
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    lw(a3, a1, 0);
    lw(v1, a0, 64);
    lw(a0, v1, 56);
    a2 = 0;
    v1 = 255;
    t6 = 254;
    t1 = si(-1);
    for (;;) {
        // 0x0034384c
        charge(ctx, 3);
        t0 = sltu(a2, a0);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003437b8
        charge(ctx, 4);
        lw(t3, a1, 4);
        lbu(t0, gp, -18345);  // 0x7CE547
        if (t0 == v1) {
            // 0x00343804
            charge(ctx, 15);
            sb(t6, gp, -18345);  // 0x7CE547
            t0 = a2 & 0xFFFF;
            t2 = sll(t0, 2);
            lw(t0, t3, 40);
            t0 = addu(t0, t2);
            lw(t5, t0, 0);
            lbu(t4, gp, -18348);  // 0x7CE544
            lbu(t3, gp, -18347);  // 0x7CE545
            lbu(t2, gp, -18346);  // 0x7CE546
            lbu(t0, gp, -18345);  // 0x7CE547
            sb(t4, t5, 4);
            sb(t3, t5, 5);
            sb(t2, t5, 6);
            sb(t0, t5, 7);
            sb(v1, gp, -18345);  // 0x7CE547
        } else {
            // 0x003437c8
            charge(ctx, 15);
            t0 = a2 & 0xFFFF;
            t2 = sll(t0, 2);
            lw(t0, t3, 40);
            t0 = addu(t0, t2);
            lw(t5, t0, 0);
            lbu(t4, gp, -18348);  // 0x7CE544
            lbu(t3, gp, -18347);  // 0x7CE545
            lbu(t2, gp, -18346);  // 0x7CE546
            lbu(t0, gp, -18345);  // 0x7CE547
            sb(t4, t5, 4);
            sb(t3, t5, 5);
            sb(t2, t5, 6);
            sb(t0, t5, 7);
        }
        // 0x00343840
        charge(ctx, 3);
        sw(t1, a3, 0);
        a2 = addiu(a2, 1);
        a3 = addiu(a3, 48);
    }
    // 0x00343858
    charge(ctx, 2);
}

// 0x00343860 sub_343860 -- 764 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2 [k16Streamer2Geometry] ($a0 = the kind object, $a1 = the kind parameters): locks the mesh
// (prelight + texcoords) and writes the first strand: for each of the segments + 1 points (+140) a prelight colour
// white with the alpha ramp of the fade-in / fade-out fractions (+120 / +124) and the texture coordinates (u 0 / 1, v
// advancing by +144 / 3; the same body as sub_342550); then copies that strand to every other one (memcpy) and
// unlocks (re-instance when flagged).
void sub_343860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00343860
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    lw(s7, a1, 56);
    if (s7 != 0) {
        // 0x0034389c
        charge(ctx, 55);
        lw(v0, s0, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4088;
        jal(ctx, 0x3438ACu, gen::fn_geometryLock_00493370);
        lw(v1, s0, 4);
        lw(v1, v1, 16);
        lw(v1, v1, 24);
        lw(s2, v1, 48);
        s3 = s2;
        lw(s0, v1, 52);
        s1 = s0;
        v1 = 0x40400000;
        mtc1(v1, f2);
        lwc1(f0, s4, 144);
        div_s(f8, f0, f2);
        lw(t0, s4, 140);
        mtc1(t0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s4, 120);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a3, f0);
        lwc1(f0, s4, 124);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        a1 = addiu(t0, 1);
        a0 = sll(a1, 2);
        t1 = 0;
        t2 = subu(t0, a2);
        v1 = 0x40000000;
        mtc1(v1, f0);
        mul_s(f7, f0, f8);
        mul_s(f6, f2, f8);
        v1 = 0x3F800000;
        mtc1(v1, f3);
        mtc1(t2, f0);
        cvt_s_w(f4, f0);
        mtc1(a3, f0);
        cvt_s_w(f5, f0);
        v1 = 0xFF0000;
        v1 = v1 | 0xFFFF;  // &0xFFFFFF
        t2 = 0x437F0000;
        mtc1(t2, f2);
        t2 = 0x4F000000;
        mtc1(t2, f1);
        t6 = lui(0x8000);
        for (;;) {
            // 0x00343acc
            charge(ctx, 3);
            t2 = sltu(t1, a1);
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00343978
            charge(ctx, 3);
            at = sltu(t1, a3);
            if (at == 0) {
                // 0x003439dc
                charge(ctx, 3);
                at = sltu(a2, t1);
                if (at == 0) {
                    // 0x00343a44
                    charge(ctx, 1);
                    mov_s(f0, f3);
                } else {
                    // 0x003439e8
                    charge(ctx, 3);
                    t2 = subu(t0, t1);
                    if (i64(t2) < 0) {
                        // 0x00343a08
                        charge(ctx, 7);
                        t3 = srl(t2, 1);
                        t2 = t2 & 0x1;
                        t3 = t3 | t2;
                        mtc1(t3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003439f4
                        charge(ctx, 5);
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x00343a24
                    charge(ctx, 8);
                    div_s(f0, f0, f4);
                }
            } else {
                // 0x00343984
                charge(ctx, 2);
                if (i64(t1) < 0) {
                    // 0x003439a0
                    charge(ctx, 7);
                    t3 = srl(t1, 1);
                    t2 = t1 & 0x1;
                    t3 = t3 | t2;
                    mtc1(t3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0034398c
                    charge(ctx, 5);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x003439bc
                charge(ctx, 8);
                div_s(f0, f0, f5);
            }
            // 0x00343a48
            charge(ctx, 5);
            sw(v1, s3, 0);
            mul_s(f0, f2, f0);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00343a6c
                charge(ctx, 5);
                sub_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(t2, f0);
                t2 = t2 | t6;
            } else {
                // 0x00343a5c
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t2, f0);
            }
            // 0x00343a80
            charge(ctx, 19);
            t2 = sll(t2, 24);
            t2 = t2 | v1;
            sw(t2, s3, 4);
            lbu(t5, s3, 4);
            lbu(t4, s3, 5);
            lbu(t3, s3, 6);
            lbu(t2, s3, 7);
            sb(t5, s3, 8);
            sb(t4, s3, 9);
            sb(t3, s3, 10);
            sb(t2, s3, 11);
            sw(v1, s3, 12);
            s3 = addiu(s3, 16);
            sw(zero, s1, 0);
            swc1(f8, s1, 8);
            swc1(f7, s1, 16);
            swc1(f6, s1, 24);
            s1 = addiu(s1, 32);
            t1 = addiu(t1, 1);
        }
        // 0x00343ad8
        charge(ctx, 5);
        s4 = 1;
        s6 = sll(a0, 2);
        s5 = sll(a0, 3);
        for (;;) {
            // 0x00343b20
            charge(ctx, 3);
            v1 = sltu(s4, s7);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00343aec
            charge(ctx, 13);
            a0 = s3;
            a1 = s2;
            a2 = s6;
            jal(ctx, 0x343AF8u, gen::fn_memcpy_00521250);
            s3 = addu(s3, s6);
            a0 = s1;
            a1 = s0;
            a2 = s5;
            jal(ctx, 0x343B10u, gen::fn_memcpy_00521250);
            s1 = addu(s1, s5);
            s4 = addiu(s4, 1);
        }
    }
    // 0x00343b2c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00343C60 sub_343C60 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2, slot 3 [k16Streamer2Clone] ($a0 = the instance; returns a new kind object): a copy for a clone:
// the same block, the segments raised to 3, the mesh duplicated (sub_324160 of the old object's mesh, the RW mesh
// creation) and the strand geometry by sub_343860.
void sub_343C60(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00343c60
    enter(ctx, 25);  // entry check point + this block's cycles
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
    v0 = sll(v0, 4);
    a0 = addiu(v0, 12);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x343C9Cu, v0.u());
    s2 = v0;
    v1 = addiu(s2, 12);
    sw(v1, v0, 0);
    sw(s2, v0, 8);
    lw(v0, s1, 140);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00343cc4
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s1, 140);
    }
    // 0x00343ccc
    charge(ctx, 16);
    lw(a0, s0, 4);
    jal(ctx, 0x343CD0u, gen::fn_sub_324160_00324160);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x343CE4u, gen::fn_sub_343860_00343860);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00343D10 sub_343D10 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2, slot 2 [k16Streamer2Destroy] ($a0 = the kind object): sub_324310 on the mesh (+4, the RW mesh
// destruction, as fx_types' sub_342A40 for kind 1), then RwFree of the block (+8).
void sub_343D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00343d10
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 4);
    jal(ctx, 0x343D24u, gen::fn_sub_324310_00324310);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x343D38u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00343D60 sub_343D60 -- 2484 bytes; frame 0x160: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2, slot 4 [k16Streamer2Update] ($a0 = the instance): within the lifetime, with a strand life (+128).
// The emission period is +132 (only on frame 0 with the once flag +184). The mesh is locked (vertices + prelight +
// texcoords) and each 48-byte record runs: -2 finished; age >= life: the strand dies (vertices cleared unless +136
// keeps them, colour back to the tint); -1 free: (re-)emitted with a random direction, speed and spin from the
// parameters (sub_358030 / sub_357FD0, cosf / sinf; kind 2 spirals its heads around the emitter axis); live: the head
// moves, every point of the strand shifts one place back and the head point is rebuilt (VU0); unlock, re-instance
// when flagged.
void sub_343D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x00343d60
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
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
    swc1(f31, sp, 0x2C);
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
    lw(v1, s1, kStmLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x00343dd4
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00343ddc;
        }
        // 0x003446b0 (the shared epilogue, written out on this path)
        charge(ctx, 25);
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
        lwc1(f31, sp, 0x2C);
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
        sp = addiu(sp, 0x160);
        return;
    }
L_00343ddc:
    charge(ctx, 5);
    lw(v1, s1, kStmCount);
    sq(v1, sp, 0x110);
    lw(s0, s1, kStmLife);
    if (s0 != 0) {
        // 0x00343df0
        charge(ctx, 3);
        lbu(v0, s1, kStmOnce);
        if (v0 != 0) {
            // 0x00343dfc
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_00343e1c;
            }
            // 0x00343e04
            charge(ctx, 6);
            v0 = 1;
            sw(v0, sp, 0x130);
            paddub(v0, v1, zero);
            sw(v0, sp, 0x120);
            goto L_00343e28;
        }
    L_00343e1c:
        charge(ctx, 3);
        sw(zero, sp, 0x130);
        lw(v0, s1, kStmRespawn);
        sw(v0, sp, 0x120);
    L_00343e28:
        charge(ctx, 23);
        lw(v0, a0, 60);
        lw(s4, v0, 0);
        lw(s5, v0, 4);
        lbu(v0, s1, kStmKeep);
        sq(v0, sp, 0x100);
        lwc1(f0, s1, 216);
        swc1(f0, sp, 0xE8);
        lwc1(f30, s1, 228);
        lw(v0, s5, 16);
        lw(a0, v0, 24);
        a1 = 4082;
        jal(ctx, 0x343E54u, gen::fn_geometryLock_00493370);
        lw(v0, s5, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 52);
        lh(s6, s5, 8);
        lw(v0, s1, kStmPoints);
        fp = addiu(v0, 0x1);
        if (i64(fp) < 0) {
            // 0x00343e98
            charge(ctx, 7);
            v1 = srl(fp, 1);
            v0 = fp & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f27, f0);
            add_s(f27, f27, f27);
        } else {
            // 0x00343e84
            charge(ctx, 5);
            mtc1(fp, f0);
            cvt_s_w(f27, f0);
        }
        // 0x00343eb4
        charge(ctx, 24);
        lwc1(f0, s1, 152);
        swc1(f0, sp, 0xE4);
        lwc1(f24, s1, 236);
        lwc1(f31, s1, 164);
        s7 = 0;
        v0 = 0x3F800000;
        mtc1(v0, f23);
        lwc1(f0, gp, -32416);  // 0x7CAE50
        swc1(f0, sp, 0xE0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        swc1(f0, sp, 0xDC);
        v0 = 0x3F000000;
        mtc1(v0, f22);
        v0 = 0x3E800000;
        mtc1(v0, f0);
        swc1(f0, sp, 0xD8);
        mtc1(zero, f0);
        swc1(f0, sp, 0xD4);
        for (;;) {
            // 0x00344670
            charge(ctx, 4);
            lq(v0, sp, 0x110);
            v0 = sltu(s7, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00343f14
            charge(ctx, 4);
            lw(a0, s4, 0);
            v0 = si(-2);
            if (a0 != v0) {
                // 0x00343f24
                charge(ctx, 3);
                v1 = si(-1);
                if (a0 == v1) {
                    // 0x00343f30
                    charge(ctx, 10);
                    v0 = sll(s6, 1);
                    v0 = addu(v0, s6);
                    a2 = sll(v0, 2);
                    a0 = s3;
                    a1 = 0;
                    jal(ctx, 0x343F44u, gen::fn_memset_00521408);
                    lw(v0, sp, 0x120);
                    if (v0 != 0) {
                        // 0x00343f58
                        charge(ctx, 25);
                        lwc1(f20, s1, 192);
                        a0 = 0;
                        jal(ctx, 0x343F60u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 188);
                        mul_s(f20, f0, f1);
                        lwc1(f21, s1, 200);
                        a0 = 0;
                        jal(ctx, 0x343F8Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f21);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f21, f0);
                        lwc1(f0, s1, 196);
                        mul_s(f0, f0, f1);
                        sub_s(f1, f0, f20);
                        if (i64(s0) < 0) {
                            // 0x00343fd0
                            charge(ctx, 7);
                            v1 = srl(s0, 1);
                            v0 = s0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00343fbc
                            charge(ctx, 5);
                            mtc1(s0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00343fec
                        charge(ctx, 94);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 12);
                        swc1(f20, s4, 8);
                        lwc1(f20, s1, 224);
                        a0 = 0;
                        jal(ctx, 0x344008u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 220);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 16);
                        a0 = 0;
                        jal(ctx, 0x344034u, gen::fn_sub_358030_00358030);
                        lwc1(f1, s1, 204);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, 20);
                        lwc1(f20, s1, 232);
                        a0 = 0;
                        jal(ctx, 0x344050u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 240);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 40);
                        a0 = 0;
                        jal(ctx, 0x34407Cu, gen::fn_sub_358030_00358030);
                        lwc1(f1, sp, 0xE0);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, 28);
                        lwc1(f20, s1, 212);
                        a0 = 0;
                        jal(ctx, 0x344098u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 208);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 24);
                        lwc1(f20, s1, 180);
                        a0 = 0;
                        jal(ctx, 0x3440C8u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 176);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 32);
                        lwc1(f20, s1, 172);
                        a0 = 0;
                        jal(ctx, 0x3440F8u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 168);
                        mul_s(f1, f0, f1);
                        lwc1(f0, sp, 0xDC);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 36);
                        lwc1(f20, s1, 156);
                        a0 = 0;
                        jal(ctx, 0x344130u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 152);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 44);
                        lw(v0, sp, 0x130);
                        if (v0 == 0) {
                            // 0x003441d4
                            charge(ctx, 1);
                            sw(zero, s4, 0);
                        } else {
                            // 0x00344164
                            charge(ctx, 28);
                            a0 = 0;
                            jal(ctx, 0x344168u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                            lwc1(f0, s4, 0);
                            cvt_s_w(f3, f0);
                            lwc1(f1, s4, 16);
                            lwc1(f0, s4, 20);
                            mtc1(zero, f2);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 20);
                            mul_s(f0, f30, f3);
                            mul_s(f1, f3, f0);
                            lwc1(f0, s4, 20);
                            adda_s(f2, f0);
                            msub_s(f0, f22, f1);
                            swc1(f0, s4, 20);
                            lwc1(f1, s4, 12);
                            lwc1(f0, s4, 8);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 8);
                        }
                        // 0x003441d8
                        charge(ctx, 5);
                        lw(v0, sp, 0x120);
                        v0 = addiu(v0, -1);
                        sw(v0, sp, 0x120);
                    }
                    goto L_00344650;
                }
                // 0x003441ec
                charge(ctx, 3);
                v0 = sltu(a0, s0);
                if (v0 == 0) {
                    // 0x003441f8
                    charge(ctx, 3);
                    lq(v0, sp, 0x100);
                    if (v0 == 0) {
                        // 0x00344210
                        charge(ctx, 9);
                        v0 = sll(s6, 1);
                        v0 = addu(v0, s6);
                        a2 = sll(v0, 2);
                        a0 = s3;
                        a1 = 0;
                        jal(ctx, 0x344224u, gen::fn_memset_00521408);
                        v0 = si(-2);
                        sw(v0, s4, 0);
                    } else {
                        // 0x00344204
                        charge(ctx, 3);
                        sw(v1, s4, 0);
                    }
                    // 0x00344234
                    charge(ctx, 4);
                    lbu(v0, gp, -18345);  // 0x7CE547
                    a3 = 255;
                    if (v0 == a3) {
                        // 0x00344280
                        charge(ctx, 18);
                        v0 = 254;
                        sb(v0, gp, -18345);  // 0x7CE547
                        v0 = s7 & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s5, 40);
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
                        // 0x00344244
                        charge(ctx, 15);
                        v0 = s7 & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s5, 40);
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
                    goto L_00344650;
                }
                // 0x003442c8
                charge(ctx, 20);
                lwc1(f0, s4, 44);
                swc1(f0, sp, 0xEC);
                mtc1(a0, f0);
                cvt_s_w(f21, f0);
                lwc1(f0, sp, 0xE8);
                mul_s(f2, f0, f21);
                lwc1(f1, s4, 24);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f0, f22, f2);
                mul_s(f1, f21, f0);
                lwc1(f0, s4, 28);
                add_s(f29, f1, f0);
                lwc1(f2, s4, 8);
                lwc1(f28, s4, 20);
                lwc1(f25, s4, 40);
                if (i64(s0) < 0) {
                    // 0x0034432c
                    charge(ctx, 7);
                    v1 = srl(s0, 1);
                    v0 = s0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00344318
                    charge(ctx, 5);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00344348
                charge(ctx, 36);
                div_s(f0, f21, f0);
                sub_s(f0, f0, f24);
                mul_s(f1, f0, f0);
                mtc1(zero, f0);
                adda_s(f0, f2);
                madd_s(f20, f25, f1);
                mov_s(f12, f29);
                jal(ctx, 0x344370u, gen::fn_cosf_0052e6d8);
                mov_s(f26, f0);
                mov_s(f12, f29);
                jal(ctx, 0x344380u, gen::fn_sinf_0052e878);
                mul_s(f1, f26, f20);
                swc1(f1, sp, 0x150);
                swc1(f28, sp, 0x154);
                mul_s(f1, f0, f20);
                swc1(f1, sp, 0x158);
                v0 = addiu(sp, 0x150);
                lqc2(vf11, v0, 0);
                vmove(0xF, vf12, vf11);  // vmove.xyzw
                lwc1(f1, s4, 16);
                add_s(f2, f28, f1);
                mtc1(zero, f1);
                adda_s(f1, f2);
                msub_s(f28, f30, f21);
                lwc1(f2, s4, 8);
                lwc1(f1, s4, 12);
                add_s(f3, f2, f1);
                add_s(f2, f23, f21);
                if (i64(s0) < 0) {
                    // 0x003443ec
                    charge(ctx, 7);
                    v1 = srl(s0, 1);
                    v0 = s0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f1);
                    cvt_s_w(f1, f1);
                    add_s(f1, f1, f1);
                } else {
                    // 0x003443d8
                    charge(ctx, 5);
                    mtc1(s0, f1);
                    cvt_s_w(f1, f1);
                }
                // 0x00344408
                charge(ctx, 69);
                div_s(f1, f2, f1);
                sub_s(f1, f1, f24);
                mul_s(f1, f1, f1);
                mtc1(zero, f4);
                adda_s(f4, f3);
                madd_s(f2, f25, f1);
                mul_s(f1, f26, f2);
                swc1(f1, sp, 0x150);
                swc1(f28, sp, 0x154);
                mul_s(f1, f0, f2);
                swc1(f1, sp, 0x158);
                v1 = addiu(sp, 0x150);
                lqc2(vf10, v1, 0);
                vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                v0 = addiu(sp, 0x140);
                sqc2(vf10, v0, 0);
                swc1(f28, s4, 20);
                lwc1(f2, s4, 12);
                lwc1(f1, s4, 8);
                add_s(f1, f1, f2);
                swc1(f1, s4, 8);
                lwc1(f2, s4, 32);
                lwc1(f1, sp, 0xD8);
                mul_s(f3, f1, f2);
                lwc1(f1, s4, 36);
                div_s(f2, f1, f27);
                swc1(f26, sp, 0x150);
                lwc1(f1, sp, 0xD4);
                swc1(f1, sp, 0x154);
                swc1(f0, sp, 0x158);
                lqc2(vf11, v1, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                mfc1(v0, f3);
                qmtc2(v0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                t6 = 0;
                t4 = 0x6A0000;
                t4 = addiu(t4, -15152);  // &0x69C4D0
                t1 = 0x6A0000;
                t0 = 0x6A0000;
                a3 = 0x6A0000;
                a2 = 0x6A0000;
                a1 = 0x6A0000;
                a0 = 0x6A0000;
                v1 = 0x6A0000;
                v0 = 0x6A0000;
                t7 = 0x6A0000;
                t8 = 0x6A0000;
                t9 = 0x6A0000;
                t2 = 0x6A0000;
                sq(t2, sp, 0xF0);
                lwc1(f0, sp, 0xEC);
                adda_s(f4, f0);
                mfc1(t5, f2);
                for (;;) {
                    // 0x00344624
                    charge(ctx, 3);
                    t2 = sltu(t6, fp);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0034451c
                    charge(ctx, 38);
                    vmove(0xF, vf10, vf12);  // vmove.xyzw
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    sqc2(vf10, t4, 0);
                    lwc1(f0, t1, -15152);
                    swc1(f0, s3, 12);
                    lwc1(f0, t0, -15148);
                    swc1(f0, s3, 16);
                    lwc1(f0, a3, -15144);
                    swc1(f0, s3, 20);
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    sqc2(vf10, t4, 0);
                    lwc1(f0, a2, -15152);
                    swc1(f0, s3, 0);
                    lwc1(f0, a1, -15148);
                    swc1(f0, s3, 4);
                    lwc1(f0, a0, -15144);
                    swc1(f0, s3, 8);
                    vmove(0xF, vf10, vf12);  // vmove.xyzw
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    sqc2(vf10, t4, 0);
                    lwc1(f0, v1, -15152);
                    swc1(f0, s3, 24);
                    lwc1(f0, v0, -15148);
                    swc1(f0, s3, 28);
                    lwc1(f0, t7, -15144);
                    swc1(f0, s3, 32);
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    sqc2(vf10, t4, 0);
                    lwc1(f0, t8, -15152);
                    swc1(f0, s3, 36);
                    lwc1(f0, t9, -15148);
                    swc1(f0, s3, 40);
                    lq(t2, sp, 0xF0);
                    lwc1(f0, t2, -15144);
                    swc1(f0, s3, 44);
                    s3 = addiu(s3, 48);
                    if (i64(t6) < 0) {
                        // 0x003445c8
                        charge(ctx, 7);
                        t3 = srl(t6, 1);
                        t2 = t6 & 0x1;
                        t3 = t3 | t2;
                        mtc1(t3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003445b4
                        charge(ctx, 5);
                        mtc1(t6, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003445e4
                    charge(ctx, 16);
                    div_s(f1, f0, f27);
                    lwc1(f0, sp, 0xE4);
                    madd_s(f0, f0, f1);
                    swc1(f0, s2, 4);
                    swc1(f0, s2, 12);
                    swc1(f0, s2, 20);
                    swc1(f0, s2, 28);
                    s2 = addiu(s2, 32);
                    t2 = addiu(sp, 0x140);
                    lqc2(vf10, t2, 0);
                    qmtc2(t5, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vadd(0xF, vf12, vf12, vf10);  // vadd.xyzw
                    t6 = addiu(t6, 1);
                }
                // 0x00344630
                charge(ctx, 8);
                lwc1(f0, s4, 44);
                add_s(f0, f0, f31);
                swc1(f0, s4, 44);
                lw(v0, s4, 0);
                v0 = addiu(v0, 1);
                sw(v0, s4, 0);
                goto L_00344668;
            }
        L_00344650:
            charge(ctx, 6);
            v0 = sll(s6, 1);
            v0 = addu(v0, s6);
            v0 = sll(v0, 2);
            s3 = addu(s3, v0);
            v0 = sll(s6, 3);
            s2 = addu(s2, v0);
        L_00344668:
            charge(ctx, 2);
            s7 = addiu(s7, 1);
            s4 = addiu(s4, 48);
        }
        // 0x00344680
        charge(ctx, 9);
        lw(v0, s5, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x34468Cu, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s5, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x003446a4
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x003446b0 (the shared epilogue, written out on this path)
    charge(ctx, 25);
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
    lwc1(f31, sp, 0x2C);
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
    sp = addiu(sp, 0x160);
}

// 0x00344720 sub_344720 -- 884 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 16, kind 2, slot 5 [k16Streamer2Draw] ($a0 = the instance): within the lifetime, the effect colour = instance
// colour (+48) x the colour track (sub_32A120 on +36) on VU0; for each strand alive (record age < life) its material
// colour = that colour x its own track (sub_32A120 on +60 at +96), else the tint gp-18348 (alpha 255 -> 254 trick);
// then the mesh gets the instance matrix (sub_3244C0 [fxSetModelMatrixB]), its additive bit from +185, and is queued
// on the layer +40 (sub_3243D0 [fxLayerAttach]).
void sub_344720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00344720
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v1, a0, 60);
    lw(s2, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s2, kStmLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0034476c
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_00344774;
        }
        // 0x00344a64 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        return;
    }
L_00344774:
    charge(ctx, 46);
    lw(s3, v1, 0);
    a0 = s2;
    a1 = addiu(s2, 36);
    jal(ctx, 0x344780u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s4, 48);
    sw(v0, sp, 0xA8);
    v0 = addiu(sp, 0xA8);
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
    sw(v1, sp, 0xA4);
    v0 = addiu(sp, 0xA4);
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
    sw(v0, sp, 0xA0);
    lw(s6, sp, 0xA0);
    lw(s7, s2, kStmCount);
    lw(s5, s2, kStmLife);
    s1 = 0;
    for (;;) {
        // 0x00344a04
        charge(ctx, 3);
        v0 = sltu(s1, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034482c
        charge(ctx, 4);
        lw(a2, s3, 0);
        at = sltu(a2, s5);
        if (at == 0) {
            // 0x00344970
            charge(ctx, 4);
            lbu(v0, gp, -18345);  // 0x7CE547
            a3 = 255;
            if (v0 == a3) {
                // 0x003449bc
                charge(ctx, 16);
                v0 = 254;
                sb(v0, gp, -18345);  // 0x7CE547
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
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
                // 0x00344980
                charge(ctx, 15);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
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
        } else {
            // 0x0034483c
            charge(ctx, 44);
            a0 = addiu(s2, 60);
            a1 = addiu(s2, 96);
            a3 = s5;
            jal(ctx, 0x344848u, gen::fn_sub_32A120_0032a120);
            sw(v0, sp, 0x9C);
            v0 = addiu(sp, 0x9C);
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
            sw(s6, sp, 0x98);
            v0 = addiu(sp, 0x98);
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
            sw(v0, sp, 0x94);
            lw(v0, sp, 0x94);
            sw(v0, sp, 0xAC);
            lbu(v0, sp, 0xAF);
            a3 = 255;
            if (v0 == a3) {
                // 0x00344928
                charge(ctx, 18);
                v0 = 254;
                sb(v0, sp, 0xAF);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
                v0 = addu(v0, v1);
                lw(a2, v0, 0);
                lbu(a1, sp, 0xAC);
                lbu(a0, sp, 0xAD);
                lbu(v1, sp, 0xAE);
                lbu(v0, sp, 0xAF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
                sb(a3, sp, 0xAF);
            } else {
                // 0x003448ec
                charge(ctx, 15);
                v0 = s1 & 0xFFFF;
                v1 = sll(v0, 2);
                lw(v0, s0, 40);
                v0 = addu(v0, v1);
                lw(a2, v0, 0);
                lbu(a1, sp, 0xAC);
                lbu(a0, sp, 0xAD);
                lbu(v1, sp, 0xAE);
                lbu(v0, sp, 0xAF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
            }
        }
        // 0x003449fc
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        s3 = addiu(s3, 48);
    }
    // 0x00344a10
    charge(ctx, 9);
    a0 = s0;
    a1 = s4;
    a2 = addiu(s4, 16);
    a3 = addiu(s4, 32);
    jal(ctx, 0x344A20u, gen::fn_sub_3244C0_003244c0);
    lbu(v0, s2, kStmAdditive);
    if (v0 == 0) {
        // 0x00344a48
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x00344a34
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x00344a54
    charge(ctx, 4);
    lhu(a1, s2, kStmLayer);
    a0 = s0;
    jal(ctx, 0x344A5Cu, gen::fn_sub_3243D0_003243d0);
    // 0x00344a64 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x00345CF0 sub_345CF0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a class-16 instance [kobj16Alloc] ($a0 = the kind, $a1 = the kind parameters; returns it; fx_types'
// sub_345DB0 / sub_345F00 call it): one RwMalloc block of 80 bytes + the kind's parameter size (row +24 of 0x69C970):
// frame 0, kind, colour -1, scale (1, 1, 1, 1), position / rotation cleared, the parameters copied to +80 (+64 points
// there). Unlike sub_3393D0 it runs no kind slot: the class's create (fx_types) does.
void sub_345CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x00345cf0
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
    v0 = addiu(v0, -13944);  // &0x69C988
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = addiu(s1, 80);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x345D3Cu, v0.u());
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
    jal(ctx, 0x345D84u, gen::fn_memcpy_00521250);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
