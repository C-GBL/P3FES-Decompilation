// The effect system, second pass (slice fx2): the particle-system types 8..11 (the update and scale slots of the type
// rows 0x69C590..0x69C5C4, the particle-system constructor sub_332070) and the ribbon effects of the classes 2 / 15
// (instance slots, the child object, the two ribbon meshes and their VU0 band builder). Records: fx2.h (namespace
// fx2).
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass adds the role of each function above it, comments on the main blocks (`// 0x00xxxxxx` names
// the original basic block a C++ block comes from) and named record offsets (constexpr values equal to the
// instructions' offsets; check_spec in the slice notes confirms the statements equal the generator's). Names in
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

// 0x00330100 sub_330100 -- 140 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 8, slot 1 [fxPsysScale8]: the type's scale ($a0 = the particle system, $f12 = the factor).
// Every size-like parameter of the live block (FxPsys +32) is the base block's (+36) times $f12: the floats at +100,
// +104, the three emission extents +116 / +124 / +132 (stride 8) and the type-8 fields +200, +220, +228, +232. Called
// through the type row (sub_332330 [fxTrackSetTime] in fx_types) when an effect is rescaled.
void sub_330100(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00330100
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, kPsysParams);
    lw(a1, a0, kPsysBaseParams);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x00330148: the three extents +116 + 8 i, i < 3
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033012c
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x00330154: the type-8 fields
    charge(ctx, 14);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 220);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 220);
    lwc1(f0, a1, 228);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 228);
    lwc1(f0, a1, 232);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 232);
}

// 0x00330190 sub_330190 -- 2588 bytes; frame 0x170: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 9, slot 0 [fxPsysUpdate9] ($a0 = the particle system; called by sub_332210 [fxTrackUpdate]
// once per frame). Nothing happens without a particle life (params +184). The emitter origin is the world origin
// 0x957A80 when the system is in world space (flag bit 0), else the parameter position. How many particles to emit
// this frame: none once the emitter lifetime (+32) has run out; on frame 0 with the burst flag (+189) all of them
// (times a random 1 - rand * (+40) factor when +40 > 0); otherwise the rate (+36), randomised the same way, plus the
// fraction carried in FxPsys +20. Then for every particle slot (the 32-byte particles +24, 36-byte state +28): an
// expired particle (age >= life) becomes free (-1) or finished (-2 when the emitter has a lifetime) and its trail
// cells are cleared; a free one is emitted while the budget lasts: a random unit direction (sub_358030 = random
// float, VU0 normalise), the speed range +220 / +224 and the speed / spin / scale randomness (+204 .. +216, +108,
// +152, the spin mode +156), a random start age in burst mode with its trail copy; a live one moves along its state
// (velocity, drag +228, the bounding test of the VU0 block: a particle past the limit bounces with a random speed),
// then sub_32A770 samples its colour / size curves, the scale and spin factors apply and sub_32A890 writes its trail
// cell; the age counts up.
void sub_330190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x00330190
    enter(ctx, 34);  // entry check point + this block's cycles
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
    s1 = a0;
    lw(v1, a0, 4);
    sq(v1, sp, 0x120);
    lw(v1, a0, 12);
    sq(v1, sp, 0x110);
    lw(s4, a0, 24);
    lw(s3, a0, 28);
    lw(s2, a0, 32);
    lw(v1, s2, kPpLife);
    if (v1 != 0) {
        // 0x00330218: a particle life: the origin (world 0x957A80 or the parameter position) into sp+0x140
        charge(ctx, 4);
        lq(v0, sp, 0x110);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x0033023c
            charge(ctx, 5);
            v1 = addiu(sp, 0x140);
            v0 = 0x950000;
            v0 = addiu(v0, 31360);  // &0x957A80
            lq(v0, v0, 0);  // 0x957A80
            sq(v0, v1, 0);
        } else {
            // 0x00330228
            charge(ctx, 5);
            v1 = addiu(sp, 0x140);
            lq(v0, s2, kPpPos);
            sq(v0, v1, 0);
        }
        // 0x00330250: the parameters this frame needs: life, lifetime, speed range, spin mode, drag
        charge(ctx, 11);
        lw(v1, s2, kPpLife);
        sq(v1, sp, 0x100);
        lw(fp, s2, kPpLifetime);
        lw(v1, s2, 216);
        sq(v1, sp, 0xF0);
        lbu(v1, s2, kPpSpinMode);
        sq(v1, sp, 0xE0);
        lwc1(f20, s2, 228);
        sw(zero, sp, 0x16C);
        if (fp != 0) {
            // 0x0033027c: the emitter lifetime has run out: emit nothing
            charge(ctx, 4);
            lw(v1, s1, kPsysFrame);
            v1 = slt(v1, fp);
            if (v1 != 0) {
                goto L_0033029c;
            }
            // 0x0033028c
            charge(ctx, 4);
            s6 = 0;
            s0 = 0;
            goto L_00330440;
        }
    L_0033029c:
        charge(ctx, 3);
        lw(v1, s1, kPsysFrame);
        if (v1 == 0) {
            // 0x003302a8: frame 0: burst?
            charge(ctx, 3);
            lbu(v1, s2, kPpBurst);
            if (v1 == 0) {
                goto L_00330348;
            }
            // 0x003302b4: burst: every particle (randomised by +40)
            charge(ctx, 7);
            s6 = 1;
            lwc1(f1, s2, kPpRateRand);
            mtc1(zero, f0);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x0033033c
                charge(ctx, 3);
                lw(s0, s1, kPsysCount);
            } else {
                // 0x003302d0
                charge(ctx, 10);
                a0 = 0;
                jal(ctx, 0x3302D4u, gen::fn_sub_358030_00358030);
                lwc1(f2, s2, kPpRateRand);
                lwc1(f1, gp, -32576);  // 0x7CADB0
                sub_s(f1, f1, f2);
                mul_s(f1, f1, f0);
                lw(v1, s1, kPsysCount);
                if (i64(v1) < 0) {
                    // 0x0033030c
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x003302f8
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00330328
                charge(ctx, 5);
                mul_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
            }
            goto L_00330440;
        }
    L_00330348:
        charge(ctx, 7);
        s6 = 0;
        lwc1(f1, s2, kPpRateRand);
        mtc1(zero, f0);
        c_le_s(f1, f0);
        if (cond(ctx)) {
            // 0x003303dc: rate plus the carried fraction
            charge(ctx, 3);
            lw(v1, s2, kPpRate);
            if (i64(v1) < 0) {
                // 0x003303fc
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003303e8
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
            }
            // 0x00330418
            charge(ctx, 3);
            lwc1(f0, s1, kPsysEmitAcc);
            add_s(f0, f0, f1);
            swc1(f0, s1, kPsysEmitAcc);
        } else {
            // 0x00330364: rate x (1 - rand * +40) plus the carried fraction
            charge(ctx, 10);
            a0 = 0;
            jal(ctx, 0x330368u, gen::fn_sub_358030_00358030);
            lwc1(f2, s2, kPpRateRand);
            lwc1(f1, gp, -32576);  // 0x7CADB0
            sub_s(f1, f1, f2);
            mul_s(f3, f1, f0);
            lw(v1, s2, kPpRate);
            if (i64(v1) < 0) {
                // 0x003303a0
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f2, f0);
                add_s(f2, f2, f2);
            } else {
                // 0x0033038c
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f2, f0);
            }
            // 0x003303bc
            charge(ctx, 8);
            lwc1(f1, s1, kPsysEmitAcc);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f2, f3);
            swc1(f0, s1, kPsysEmitAcc);
        }
        // 0x00330424: emit the whole part now, keep the fraction
        charge(ctx, 7);
        lwc1(f1, s1, kPsysEmitAcc);
        abs_s(f0, f1);
        cvt_w_s(f0, f0);
        mfc1(s0, f0);
        cvt_s_w(f0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, s1, kPsysEmitAcc);
    L_00330440:
        charge(ctx, 16);
        s7 = 0;
        v1 = 0x3F000000;
        mtc1(v1, f27);
        v1 = 0x40000000;
        mtc1(v1, f26);
        v1 = 0x3F800000;
        mtc1(v1, f25);
        mtc1(zero, f24);
        lwc1(f23, gp, -32416);  // 0x7CAE50
        v1 = lui(0xBF80);
        mtc1(v1, f22);
        lwc1(f21, gp, -32404);  // 0x7CAE5C
        lwc1(f0, gp, -32400);  // 0x7CAE60
        swc1(f0, sp, 0xDC);
        for (;;) {
            // 0x00330b38: for each particle slot
            charge(ctx, 4);
            lq(v1, sp, 0x120);
            v1 = sltu(s7, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00330480: age >= life: free (-1) or finished (-2), clear its trail cells
            charge(ctx, 5);
            lw(a0, s4, kPtAge);
            lq(v1, sp, 0x100);
            v1 = slt(a0, v1);
            if (v1 == 0) {
                // 0x00330494
                charge(ctx, 2);
                if (fp == 0) {
                    // 0x003304a8
                    charge(ctx, 1);
                    v1 = si(-1);
                } else {
                    // 0x0033049c
                    charge(ctx, 3);
                    v1 = si(-2);
                }
                // 0x003304ac
                charge(ctx, 7);
                sw(v1, s4, kPtAge);
                lw(v1, s1, kPsysParams);
                lw(a0, v1, 192);
                lw(v1, v1, 196);
                mult(a2, a0, v1);
                if (a2 != 0) {
                    // 0x003304c8
                    charge(ctx, 12);
                    lw(a1, s1, kPsysParticles);
                    v1 = subu(s4, a1);
                    v1 = srl(v1, 5);
                    mult(a0, v1, a2);
                    lw(v1, s1, kPsysCount);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    a3 = addu(a1, v1);
                    a1 = 0;
                    a0 = si(-1);
                    for (;;) {
                        // 0x00330504
                        charge(ctx, 4);
                        v1 = slt(a1, a2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003304f8
                        charge(ctx, 3);
                        sw(a0, a3, 16);
                        a3 = addiu(a3, 32);
                        a1 = addiu(a1, 1);
                    }
                }
            }
            // 0x00330514
            charge(ctx, 4);
            lw(s5, s4, kPtAge);
            v1 = si(-2);
            if (s5 != v1) {
                // 0x00330524
                charge(ctx, 3);
                v1 = si(-1);
                if (s5 != v1) {
                    // 0x00330928
                    charge(ctx, 9);
                    v1 = addiu(sp, 0x150);
                    lq(v0, s4, kPtPos);
                    sq(v0, v1, 0);
                    lwc1(f30, s3, 12);
                    lw(v1, s4, kPtAge);
                    lq(v0, sp, 0xF0);
                    at = slt(v1, v0);
                    if (at != 0) {
                        // 0x0033094c
                        charge(ctx, 3);
                        lwc1(f0, s3, 16);
                        add_s(f0, f30, f0);
                        swc1(f0, s3, 12);
                    }
                    // 0x00330958
                    charge(ctx, 11);
                    mtc1(s5, f0);
                    cvt_s_w(f2, f0);
                    lwc1(f1, s3, 20);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f31, f20, f2);
                    c_lt_s(f31, f24);
                    if (cond(ctx)) {
                        // 0x00330984
                        charge(ctx, 1);
                        mov_s(f31, f24);
                    }
                    // 0x00330988
                    charge(ctx, 29);
                    lwc1(f0, s3, 0);
                    swc1(f0, sp, 0x160);
                    lwc1(f0, s3, 4);
                    swc1(f0, sp, 0x164);
                    lwc1(f0, s3, 8);
                    swc1(f0, sp, 0x168);
                    v0 = addiu(sp, 0x160);
                    lqc2(vf12, v0, 0);
                    lqc2(vf11, s4, kPtPos);
                    vmove(0xF, vf10, vf12);  // vmove.xyzw
                    mfc1(v0, f31);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vadd(0xF, vf11, vf11, vf10);  // vadd.xyzw
                    v0 = addiu(sp, 0x140);
                    lqc2(vf10, v0, 0);
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                    vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
                    vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
                    vsqrt(vf2, 0);  // vsqrt
                    vwaitq(ctx);
                    cfc2(v0, 22, false);  // cfc2
                    mtc1(v0, f29);
                    c_le_s(f29, f30);
                    if (cond(ctx)) {
                        // 0x00330ac8
                        charge(ctx, 1);
                        sqc2(vf11, s4, kPtPos);
                    } else {
                        // 0x003309fc
                        charge(ctx, 51);
                        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                        vwaitq(ctx);
                        vmulq(0xE, vf10, vf10);  // vmulq.xyz
                        vmove(0xF, vf11, vf12);  // vmove.xyzw
                        vmul(0xE, vf2, vf10, vf11);  // vmul.xyz
                        vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
                        vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
                        qmfc2(v0, vf2, false);  // qmfc2
                        mtc1(v0, f28);
                        a0 = 0;
                        jal(ctx, 0x330A34u, gen::fn_sub_358030_00358030);
                        mtc1(zero, f2);
                        lwc1(f1, sp, 0xDC);
                        adda_s(f2, f1);
                        madd_s(f0, f21, f0);
                        mul_s(f0, f28, f0);
                        mul_s(f0, f26, f0);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                        v0 = addiu(sp, 0x130);
                        sqc2(vf11, v0, 0);
                        lwc1(f0, sp, 0x130);
                        swc1(f0, s3, 0);
                        lwc1(f0, sp, 0x134);
                        swc1(f0, s3, 4);
                        lwc1(f0, sp, 0x138);
                        swc1(f0, s3, 8);
                        sub_s(f1, f29, f30);
                        lqc2(vf10, s4, kPtPos);
                        sub_s(f0, f31, f1);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf12, vf12, vf2, 0);  // vmulx.xyzw
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        mfc1(v0, f1);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, s4, kPtPos);
                    }
                    // 0x00330acc
                    charge(ctx, 24);
                    a0 = s4;
                    a1 = s2;
                    a2 = s5;
                    a3 = addiu(sp, 0x150);
                    jal(ctx, 0x330ADCu, gen::fn_sub_32A770_0032a770);
                    lwc1(f1, s4, kPtScale);
                    lwc1(f0, s3, 24);
                    mul_s(f0, f1, f0);
                    swc1(f0, s4, kPtScale);
                    lwc1(f1, s4, kPtSpin);
                    lwc1(f0, s3, 32);
                    mul_s(f0, f1, f0);
                    swc1(f0, s4, kPtSpin);
                    lwc1(f1, s3, 28);
                    lwc1(f0, s4, kPtSpin);
                    add_s(f0, f0, f1);
                    swc1(f0, s4, kPtSpin);
                    a0 = s1;
                    a1 = s4;
                    jal(ctx, 0x330B1Cu, gen::fn_sub_32A890_0032a890);
                    v1 = addiu(s5, 1);
                    sw(v1, s4, kPtAge);
                } else {
                    // 0x00330530
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x00330538
                        charge(ctx, 81);
                        a0 = 0;
                        jal(ctx, 0x33053Cu, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x160);
                        a0 = 0;
                        jal(ctx, 0x330554u, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x164);
                        a0 = 0;
                        jal(ctx, 0x33056Cu, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x168);
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                        vwaitq(ctx);
                        vmulq(0xE, vf10, vf10);  // vmulq.xyz
                        sqc2(vf10, v0, 0);
                        lwc1(f0, sp, 0x160);
                        swc1(f0, s3, 0);
                        lwc1(f0, sp, 0x164);
                        swc1(f0, s3, 4);
                        lwc1(f0, sp, 0x168);
                        swc1(f0, s3, 8);
                        lwc1(f28, s2, 224);
                        a0 = 0;
                        jal(ctx, 0x3305C8u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s2, 220);
                        mul_s(f0, f0, f1);
                        abs_s(f0, f0);
                        swc1(f0, s3, 20);
                        lwc1(f28, s2, 204);
                        a0 = 0;
                        jal(ctx, 0x3305FCu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s2, 200);
                        mul_s(f29, f0, f1);
                        lwc1(f28, s2, 212);
                        a0 = 0;
                        jal(ctx, 0x330628u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s2, 208);
                        mul_s(f28, f0, f1);
                        swc1(f29, s3, 12);
                        sub_s(f1, f28, f29);
                        lq(v0, sp, 0xF0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s3, 16);
                        if (s6 == 0) {
                            // 0x00330708
                            charge(ctx, 1);
                            sw(zero, s4, kPtAge);
                        } else {
                            // 0x0033067c
                            charge(ctx, 20);
                            a0 = 0;
                            jal(ctx, 0x330680u, gen::fn_sub_357FD0_00357fd0);
                            lq(v1, sp, 0x100);
                            divu(v0, v1);
                            mfhi(v0);
                            sw(v0, s4, kPtAge);
                            lwc1(f3, s3, 16);
                            lwc1(f0, s4, kPtAge);
                            cvt_s_w(f2, f0);
                            lwc1(f1, s3, 12);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f3, f2);
                            swc1(f0, s3, 12);
                            lwc1(f1, s3, 16);
                            c_le_s(f1, f24);
                            if (!cond(ctx)) {
                                // 0x003306cc
                                charge(ctx, 4);
                                lwc1(f0, s3, 12);
                                c_le_s(f0, f28);
                                if (cond(ctx)) {
                                    goto L_003306dc;
                                }
                            L_003306f8:
                                charge(ctx, 1);
                                swc1(f28, s3, 12);
                                goto L_003306fc;
                            }
                        L_003306dc:
                            charge(ctx, 3);
                            c_lt_s(f1, f24);
                            if (cond(ctx)) {
                                // 0x003306e8
                                charge(ctx, 4);
                                lwc1(f0, s3, 12);
                                c_lt_s(f0, f28);
                                if (cond(ctx)) {
                                    goto L_003306f8;
                                }
                            }
                        L_003306fc:
                            charge(ctx, 3);
                            lwc1(f29, s3, 12);
                        }
                        // 0x0033070c
                        charge(ctx, 35);
                        a0 = 0;
                        jal(ctx, 0x330710u, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x160);
                        a0 = 0;
                        jal(ctx, 0x330728u, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x164);
                        a0 = 0;
                        jal(ctx, 0x330740u, gen::fn_sub_358030_00358030);
                        sub_s(f0, f0, f27);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x168);
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                        vwaitq(ctx);
                        vmulq(0xE, vf10, vf10);  // vmulq.xyz
                        mfc1(v0, f29);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        lq(v0, sp, 0x110);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            // 0x00330798
                            charge(ctx, 3);
                            v0 = addiu(sp, 0x140);
                            lqc2(vf11, v0, 0);
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        }
                        // 0x003307a4
                        charge(ctx, 16);
                        sqc2(vf10, s4, kPtPos);
                        lwc1(f28, s2, kPpScaleRand);
                        a0 = 0;
                        jal(ctx, 0x3307B0u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f0, f28, f0);
                        swc1(f0, s3, 24);
                        lq(v0, sp, 0xE0);
                        s5 = v0 & 0xFF;
                        v0 = 2;
                        if (s5 == v0) {
                            // 0x00330864
                            charge(ctx, 2);
                            swc1(f24, s3, 28);
                            swc1(f25, s3, 32);
                        } else {
                            // 0x003307e4
                            charge(ctx, 13);
                            lwc1(f28, s2, kPpSpinRand);
                            a0 = 0;
                            jal(ctx, 0x3307ECu, gen::fn_sub_358030_00358030);
                            sub_s(f2, f25, f28);
                            mtc1(zero, f1);
                            adda_s(f1, f2);
                            madd_s(f0, f28, f0);
                            swc1(f0, s3, 32);
                            v0 = 1;
                            if (s5 != v0) {
                                // 0x00330858
                                charge(ctx, 3);
                                swc1(f24, s3, 28);
                            } else {
                                // 0x00330818
                                charge(ctx, 11);
                                a0 = 0;
                                jal(ctx, 0x33081Cu, gen::fn_sub_358030_00358030);
                                mul_s(f0, f23, f0);
                                swc1(f0, s3, 28);
                                a0 = 0;
                                jal(ctx, 0x330830u, gen::fn_sub_357FD0_00357fd0);
                                v0 = v0 & 0x1;
                                if (v0 != 0) {
                                    // 0x00330844
                                    charge(ctx, 5);
                                    lwc1(f0, s3, 32);
                                    mul_s(f0, f0, f22);
                                    swc1(f0, s3, 32);
                                }
                            }
                        }
                        // 0x0033086c
                        charge(ctx, 20);
                        a0 = s4;
                        a1 = s2;
                        lw(a2, s4, kPtAge);
                        a3 = s4;
                        jal(ctx, 0x33087Cu, gen::fn_sub_32A770_0032a770);
                        lwc1(f1, s4, kPtScale);
                        lwc1(f0, s3, 24);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, kPtScale);
                        lwc1(f1, s4, kPtSpin);
                        lwc1(f0, s3, 32);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, kPtSpin);
                        lwc1(f1, s3, 28);
                        lwc1(f0, s4, kPtSpin);
                        add_s(f0, f0, f1);
                        swc1(f0, s4, kPtSpin);
                        if (s6 != 0) {
                            // 0x003308bc
                            charge(ctx, 6);
                            lw(v1, s1, kPsysParams);
                            lw(a0, v1, 192);
                            lw(v1, v1, 196);
                            mult(v1, a0, v1);
                            if (v1 != 0) {
                                // 0x003308d4
                                charge(ctx, 15);
                                lw(a0, s1, kPsysParticles);
                                v0 = subu(s4, a0);
                                v0 = srl(v0, 5);
                                mult(v1, v0, v1);
                                lw(v0, s1, kPsysCount);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 5);
                                s5 = addu(a0, v0);
                                a0 = s5;
                                a1 = s4;
                                a2 = 32;
                                jal(ctx, 0x330900u, gen::fn_memcpy_00521250);
                                v1 = si(-1);
                                sw(v1, s5, 16);
                            }
                            // 0x00330910
                            charge(ctx, 3);
                            lw(v1, s4, kPtAge);
                            v1 = addiu(v1, 1);
                            sw(v1, s4, kPtAge);
                        }
                        // 0x0033091c
                        charge(ctx, 3);
                        s0 = addiu(s0, -1);
                    }
                }
            }
            // 0x00330b2c
            charge(ctx, 3);
            s7 = addiu(s7, 1);
            s3 = addiu(s3, 36);
            s4 = addiu(s4, 32);
        }
    }
    // 0x00330b48 (the shared epilogue, written out on this path)
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

// 0x00330BB0 sub_330BB0 -- 140 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 9, slot 1 [fxPsysScale9]: the type's scale ($a0 = the particle system, $f12 = the factor).
// Every size-like parameter of the live block (FxPsys +32) is the base block's (+36) times $f12: the floats at +100,
// +104, the three emission extents +116 / +124 / +132 (stride 8) and the type-9 fields +200, +208, +220, +228. Called
// through the type row (sub_332330 [fxTrackSetTime] in fx_types) when an effect is rescaled.
void sub_330BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00330bb0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, kPsysParams);
    lw(a1, a0, kPsysBaseParams);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x00330bf8
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00330bdc
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x00330c04
    charge(ctx, 14);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 208);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 208);
    lwc1(f0, a1, 220);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 220);
    lwc1(f0, a1, 228);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 228);
}

// 0x00330C40 sub_330C40 -- 2440 bytes; frame 0x160: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 10, slot 0 [fxPsysUpdate10] ($a0 = the particle system; per frame from sub_332210). The
// emission budget is computed as in sub_330190 (lifetime +32, burst +189, rate +36 with randomness +40, the carried
// fraction FxPsys +20). Particles are placed on a circle: an emitted particle draws a random angle and radius (radius
// range +200 / +204 through sinf / cosf, the height +208 with the alternating-sign flag +228 for every second
// particle, a random angle in [0, 2 pi) (0x7CAE50)) and its state (+28, 36 bytes) keeps angle, radius and height
// steps; a live particle advances them each frame (gravity +220 on the height), its position is rebuilt from the
// circle and rotated by the emitter matrix (VU0, sub_357E30) unless in world space; sub_32A770 then samples its
// colour and size, the scale / spin factors apply and sub_32A890 writes its trail cell.
void sub_330C40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29};
    Vf vf10{ctx, 10}, vf11{ctx, 11}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00330c40: the particle state, the emitter matrix (VU0, sub_357E30)
    enter(ctx, 32);  // entry check point + this block's cycles
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
    s1 = a0;
    lw(v1, a0, 4);
    sq(v1, sp, 0x100);
    lw(v1, a0, 12);
    sq(v1, sp, 0xF0);
    lw(s4, a0, 24);
    lw(s3, a0, 28);
    lw(s2, a0, 32);
    lw(s7, s2, kPpLife);
    if (s7 != 0) {
        // 0x00330cc0
        charge(ctx, 18);
        lw(v0, s2, kPpLifetime);
        sq(v0, sp, 0xE0);
        lbu(v0, s2, kPpSpinMode);
        sq(v0, sp, 0xD0);
        lwc1(f28, s2, 220);
        lwc1(f27, s2, 216);
        sw(zero, sp, 0x15C);
        sw(zero, sp, 0x13C);
        sw(zero, sp, 0x14C);
        v1 = addiu(sp, 0x120);
        lq(v0, s2, kPpPos);
        sq(v0, v1, 0);
        lqc2(vf10, s2, kPpRot);
        jal(ctx, 0x330CF4u, gen::fn_sub_357E30_00357e30);
        lq(v1, sp, 0xE0);
        if (v1 != 0) {
            // 0x00330d08
            charge(ctx, 4);
            lw(a0, s1, kPsysFrame);
            v1 = slt(a0, v1);
            if (v1 != 0) {
                goto L_00330d28;
            }
            // 0x00330d18
            charge(ctx, 4);
            fp = 0;
            s0 = 0;
            goto L_00330ecc;
        }
    L_00330d28:
        charge(ctx, 3);
        lw(v1, s1, kPsysFrame);
        if (v1 == 0) {
            // 0x00330d34
            charge(ctx, 3);
            lbu(v1, s2, kPpBurst);
            if (v1 == 0) {
                goto L_00330dd4;
            }
            // 0x00330d40
            charge(ctx, 7);
            fp = 0x1;
            lwc1(f1, s2, kPpRateRand);
            mtc1(zero, f0);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00330dc8
                charge(ctx, 3);
                lw(s0, s1, kPsysCount);
            } else {
                // 0x00330d5c
                charge(ctx, 10);
                a0 = 0;
                jal(ctx, 0x330D60u, gen::fn_sub_358030_00358030);
                lwc1(f2, s2, kPpRateRand);
                lwc1(f1, gp, -32576);  // 0x7CADB0
                sub_s(f1, f1, f2);
                mul_s(f1, f1, f0);
                lw(v1, s1, kPsysCount);
                if (i64(v1) < 0) {
                    // 0x00330d98
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00330d84
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00330db4
                charge(ctx, 5);
                mul_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
            }
            goto L_00330ecc;
        }
    L_00330dd4:
        charge(ctx, 7);
        fp = 0;
        lwc1(f1, s2, kPpRateRand);
        mtc1(zero, f0);
        c_le_s(f1, f0);
        if (cond(ctx)) {
            // 0x00330e68
            charge(ctx, 3);
            lw(v1, s2, kPpRate);
            if (i64(v1) < 0) {
                // 0x00330e88
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x00330e74
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
            }
            // 0x00330ea4
            charge(ctx, 3);
            lwc1(f0, s1, kPsysEmitAcc);
            add_s(f0, f0, f1);
            swc1(f0, s1, kPsysEmitAcc);
        } else {
            // 0x00330df0
            charge(ctx, 10);
            a0 = 0;
            jal(ctx, 0x330DF4u, gen::fn_sub_358030_00358030);
            lwc1(f2, s2, kPpRateRand);
            lwc1(f1, gp, -32576);  // 0x7CADB0
            sub_s(f1, f1, f2);
            mul_s(f3, f1, f0);
            lw(v1, s2, kPpRate);
            if (i64(v1) < 0) {
                // 0x00330e2c
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f2, f0);
                add_s(f2, f2, f2);
            } else {
                // 0x00330e18
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f2, f0);
            }
            // 0x00330e48
            charge(ctx, 8);
            lwc1(f1, s1, kPsysEmitAcc);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f2, f3);
            swc1(f0, s1, kPsysEmitAcc);
        }
        // 0x00330eb0
        charge(ctx, 7);
        lwc1(f1, s1, kPsysEmitAcc);
        abs_s(f0, f1);
        cvt_w_s(f0, f0);
        mfc1(s0, f0);
        cvt_s_w(f0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, s1, kPsysEmitAcc);
    L_00330ecc:
        charge(ctx, 12);
        s6 = 0;
        lwc1(f25, gp, -32408);  // 0x7CAE58
        v1 = 0x3F800000;
        mtc1(v1, f24);
        v1 = 0x3F000000;
        mtc1(v1, f23);
        lwc1(f22, gp, -32416);  // 0x7CAE50
        v1 = lui(0xBF80);
        mtc1(v1, f21);
        mtc1(zero, f20);
        for (;;) {
            // 0x0033155c
            charge(ctx, 4);
            lq(v1, sp, 0x100);
            v1 = sltu(s6, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00330efc
            charge(ctx, 4);
            lw(v1, s4, kPtAge);
            v1 = slt(v1, s7);
            if (v1 == 0) {
                // 0x00330f0c
                charge(ctx, 3);
                lq(v1, sp, 0xE0);
                if (v1 == 0) {
                    // 0x00330f24
                    charge(ctx, 1);
                    v1 = si(-1);
                } else {
                    // 0x00330f18
                    charge(ctx, 3);
                    v1 = si(-2);
                }
                // 0x00330f28
                charge(ctx, 7);
                sw(v1, s4, kPtAge);
                lw(v1, s1, kPsysParams);
                lw(a0, v1, 192);
                lw(v1, v1, 196);
                mult(a2, a0, v1);
                if (a2 != 0) {
                    // 0x00330f44
                    charge(ctx, 12);
                    lw(a1, s1, kPsysParticles);
                    v1 = subu(s4, a1);
                    v1 = srl(v1, 5);
                    mult(a0, v1, a2);
                    lw(v1, s1, kPsysCount);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    a3 = addu(a1, v1);
                    a1 = 0;
                    a0 = si(-1);
                    for (;;) {
                        // 0x00330f80
                        charge(ctx, 4);
                        v1 = slt(a1, a2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00330f74
                        charge(ctx, 3);
                        sw(a0, a3, 16);
                        a3 = addiu(a3, 32);
                        a1 = addiu(a1, 1);
                    }
                }
            }
            // 0x00330f90
            charge(ctx, 4);
            lw(s5, s4, kPtAge);
            v1 = si(-2);
            if (s5 != v1) {
                // 0x00330fa0
                charge(ctx, 3);
                v1 = si(-1);
                if (s5 != v1) {
                    // 0x003313d8
                    charge(ctx, 9);
                    v1 = addiu(sp, 0x110);
                    lq(v0, s4, kPtPos);
                    sq(v0, v1, 0);
                    mtc1(s5, f0);
                    cvt_s_w(f3, f0);
                    lbu(v0, s2, 228);
                    if (v0 != 0) {
                        // 0x003313fc
                        charge(ctx, 3);
                        v0 = s6 & 0x1;
                        if (v0 != 0) {
                            goto L_00331408;
                        }
                        // 0x0033142c
                        charge(ctx, 7);
                        mul_s(f2, f27, f3);
                        lwc1(f1, s3, 8);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        msub_s(f0, f23, f2);
                        mul_s(f26, f3, f0);
                        goto L_00331448;
                    }
                L_00331408:
                    charge(ctx, 9);
                    mul_s(f2, f27, f3);
                    lwc1(f1, s3, 8);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f0, f23, f2);
                    mul_s(f26, f3, f0);
                L_00331448:
                    charge(ctx, 35);
                    lwc1(f0, s3, 12);
                    add_s(f26, f26, f0);
                    lwc1(f1, s3, 16);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    msub_s(f0, f28, f3);
                    swc1(f0, s3, 16);
                    lwc1(f1, s3, 4);
                    lwc1(f0, s3, 0);
                    add_s(f0, f0, f1);
                    swc1(f0, s3, 0);
                    lwc1(f1, s3, 20);
                    lwc1(f0, s3, 16);
                    add_s(f0, f0, f1);
                    swc1(f0, s3, 16);
                    lwc1(f29, s3, 0);
                    mov_s(f12, f26);
                    jal(ctx, 0x331490u, gen::fn_cosf_0052e6d8);
                    mul_s(f0, f29, f0);
                    swc1(f0, sp, 0x130);
                    lwc1(f0, s3, 16);
                    swc1(f0, sp, 0x134);
                    mov_s(f12, f26);
                    jal(ctx, 0x3314ACu, gen::fn_sinf_0052e878);
                    mul_s(f0, f29, f0);
                    swc1(f0, sp, 0x138);
                    v0 = addiu(sp, 0x130);
                    lqc2(vf10, v0, 0);
                    lq(v0, sp, 0xF0);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x003314d4
                        charge(ctx, 6);
                        vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                        vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                        vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                        v0 = addiu(sp, 0x120);
                        lqc2(vf11, v0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    }
                    // 0x003314ec
                    charge(ctx, 25);
                    sqc2(vf10, s4, kPtPos);
                    a0 = s4;
                    a1 = s2;
                    a2 = s5;
                    a3 = addiu(sp, 0x110);
                    jal(ctx, 0x331500u, gen::fn_sub_32A770_0032a770);
                    lwc1(f1, s4, kPtScale);
                    lwc1(f0, s3, 24);
                    mul_s(f0, f1, f0);
                    swc1(f0, s4, kPtScale);
                    lwc1(f1, s4, kPtSpin);
                    lwc1(f0, s3, 32);
                    mul_s(f0, f1, f0);
                    swc1(f0, s4, kPtSpin);
                    lwc1(f1, s3, 28);
                    lwc1(f0, s4, kPtSpin);
                    add_s(f0, f0, f1);
                    swc1(f0, s4, kPtSpin);
                    a0 = s1;
                    a1 = s4;
                    jal(ctx, 0x331540u, gen::fn_sub_32A890_0032a890);
                    v1 = addiu(s5, 1);
                    sw(v1, s4, kPtAge);
                } else {
                    // 0x00330fac
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x00330fb4
                        charge(ctx, 27);
                        lwc1(f26, s2, 224);
                        a0 = 0;
                        jal(ctx, 0x330FBCu, gen::fn_sub_358030_00358030);
                        mul_s(f1, f25, f26);
                        mula_s(f1, f0);
                        sub_s(f0, f24, f26);
                        mul_s(f0, f25, f0);
                        madd_s(f26, f23, f0);
                        mov_s(f12, f26);
                        jal(ctx, 0x330FDCu, gen::fn_sinf_0052e878);
                        lwc1(f1, s2, 200);
                        mul_s(f2, f1, f0);
                        lwc1(f1, s2, 204);
                        mul_s(f0, f1, f0);
                        swc1(f2, s3, 0);
                        sub_s(f1, f0, f2);
                        mtc1(s7, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s3, 4);
                        lbu(v0, s2, 228);
                        if (v0 != 0) {
                            // 0x00331020
                            charge(ctx, 3);
                            v0 = s6 & 0x1;
                            if (v0 != 0) {
                                goto L_0033102c;
                            }
                            // 0x00331064
                            charge(ctx, 13);
                            lwc1(f29, s2, 212);
                            a0 = 0;
                            jal(ctx, 0x33106Cu, gen::fn_sub_358030_00358030);
                            sub_s(f2, f24, f29);
                            mtc1(zero, f1);
                            adda_s(f1, f2);
                            madd_s(f1, f29, f0);
                            lwc1(f0, s2, 208);
                            neg_s(f0, f0);
                            mul_s(f0, f0, f1);
                            swc1(f0, s3, 8);
                            goto L_00331098;
                        }
                    L_0033102c:
                        charge(ctx, 14);
                        lwc1(f29, s2, 212);
                        a0 = 0;
                        jal(ctx, 0x331034u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f29);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f29, f0);
                        lwc1(f0, s2, 208);
                        mul_s(f0, f0, f1);
                        swc1(f0, s3, 8);
                    L_00331098:
                        charge(ctx, 38);
                        a0 = 0;
                        jal(ctx, 0x33109Cu, gen::fn_sub_358030_00358030);
                        mul_s(f0, f22, f0);
                        swc1(f0, s3, 12);
                        mov_s(f12, f26);
                        jal(ctx, 0x3310B0u, gen::fn_cosf_0052e6d8);
                        lwc1(f1, s2, 200);
                        mul_s(f2, f1, f0);
                        lwc1(f1, s2, 204);
                        mul_s(f0, f1, f0);
                        swc1(f2, s3, 16);
                        sub_s(f1, f0, f2);
                        mtc1(s7, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s3, 20);
                        lwc1(f26, s3, 0);
                        lwc1(f12, s3, 12);
                        jal(ctx, 0x3310ECu, gen::fn_cosf_0052e6d8);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x150);
                        lwc1(f0, s3, 16);
                        swc1(f0, sp, 0x154);
                        lwc1(f12, s3, 12);
                        jal(ctx, 0x331108u, gen::fn_sinf_0052e878);
                        mul_s(f0, f26, f0);
                        swc1(f0, sp, 0x158);
                        v0 = addiu(sp, 0x150);
                        lqc2(vf10, v0, 0);
                        lq(v0, sp, 0xF0);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            // 0x00331130
                            charge(ctx, 6);
                            vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                            vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                            vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                            v0 = addiu(sp, 0x120);
                            lqc2(vf11, v0, 0);
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        }
                        // 0x00331148
                        charge(ctx, 16);
                        sqc2(vf10, s4, kPtPos);
                        lwc1(f26, s2, kPpScaleRand);
                        a0 = 0;
                        jal(ctx, 0x331154u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f26);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f0, f26, f0);
                        swc1(f0, s3, 24);
                        lq(v0, sp, 0xD0);
                        s5 = v0 & 0xFF;
                        v0 = 2;
                        if (s5 == v0) {
                            // 0x00331208
                            charge(ctx, 2);
                            swc1(f20, s3, 28);
                            swc1(f24, s3, 32);
                        } else {
                            // 0x00331188
                            charge(ctx, 13);
                            lwc1(f26, s2, kPpSpinRand);
                            a0 = 0;
                            jal(ctx, 0x331190u, gen::fn_sub_358030_00358030);
                            sub_s(f2, f24, f26);
                            mtc1(zero, f1);
                            adda_s(f1, f2);
                            madd_s(f0, f26, f0);
                            swc1(f0, s3, 32);
                            v0 = 1;
                            if (s5 != v0) {
                                // 0x003311fc
                                charge(ctx, 3);
                                swc1(f20, s3, 28);
                            } else {
                                // 0x003311bc
                                charge(ctx, 11);
                                a0 = 0;
                                jal(ctx, 0x3311C0u, gen::fn_sub_358030_00358030);
                                mul_s(f0, f22, f0);
                                swc1(f0, s3, 28);
                                a0 = 0;
                                jal(ctx, 0x3311D4u, gen::fn_sub_357FD0_00357fd0);
                                v0 = v0 & 0x1;
                                if (v0 != 0) {
                                    // 0x003311e8
                                    charge(ctx, 5);
                                    lwc1(f0, s3, 32);
                                    mul_s(f0, f0, f21);
                                    swc1(f0, s3, 32);
                                }
                            }
                        }
                        // 0x00331210
                        charge(ctx, 6);
                        sw(zero, s4, kPtAge);
                        v1 = addiu(sp, 0x110);
                        lq(v0, s4, kPtPos);
                        sq(v0, v1, 0);
                        if (fp != 0) {
                            // 0x00331228
                            charge(ctx, 7);
                            a0 = 0;
                            jal(ctx, 0x33122Cu, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s7);
                            mfhi(v0);
                            if (i64(v0) < 0) {
                                // 0x00331258
                                charge(ctx, 7);
                                v1 = srl(v0, 1);
                                v0 = v0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f26, f0);
                                add_s(f26, f26, f26);
                            } else {
                                // 0x00331244
                                charge(ctx, 5);
                                mtc1(v0, f0);
                                cvt_s_w(f26, f0);
                            }
                            // 0x00331274
                            charge(ctx, 31);
                            mul_s(f0, f28, f26);
                            mul_s(f1, f26, f0);
                            lwc1(f0, s3, 16);
                            mtc1(zero, f2);
                            adda_s(f2, f0);
                            msub_s(f0, f23, f1);
                            swc1(f0, s3, 16);
                            lwc1(f1, s3, 4);
                            lwc1(f0, s3, 0);
                            adda_s(f2, f0);
                            madd_s(f29, f1, f26);
                            swc1(f29, s3, 0);
                            lwc1(f12, s3, 12);
                            jal(ctx, 0x3312ACu, gen::fn_cosf_0052e6d8);
                            mul_s(f0, f29, f0);
                            swc1(f0, sp, 0x150);
                            lwc1(f0, s3, 16);
                            swc1(f0, sp, 0x154);
                            lwc1(f12, s3, 12);
                            jal(ctx, 0x3312C8u, gen::fn_sinf_0052e878);
                            mul_s(f0, f29, f0);
                            swc1(f0, sp, 0x158);
                            v0 = addiu(sp, 0x150);
                            lqc2(vf10, v0, 0);
                            lq(v0, sp, 0xF0);
                            v0 = v0 & 0x1;
                            if (v0 == 0) {
                                // 0x003312f0
                                charge(ctx, 6);
                                vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                                vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                                vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                                v0 = addiu(sp, 0x120);
                                lqc2(vf11, v0, 0);
                                vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            }
                            // 0x00331308
                            charge(ctx, 5);
                            sqc2(vf10, s4, kPtPos);
                            cvt_w_s(f0, f26);
                            mfc1(v0, f0);
                            sw(v0, s4, kPtAge);
                        }
                        // 0x0033131c
                        charge(ctx, 20);
                        a0 = s4;
                        a1 = s2;
                        lw(a2, s4, kPtAge);
                        a3 = addiu(sp, 0x110);
                        jal(ctx, 0x33132Cu, gen::fn_sub_32A770_0032a770);
                        lwc1(f1, s4, kPtScale);
                        lwc1(f0, s3, 24);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, kPtScale);
                        lwc1(f1, s4, kPtSpin);
                        lwc1(f0, s3, 32);
                        mul_s(f0, f1, f0);
                        swc1(f0, s4, kPtSpin);
                        lwc1(f1, s3, 28);
                        lwc1(f0, s4, kPtSpin);
                        add_s(f0, f0, f1);
                        swc1(f0, s4, kPtSpin);
                        if (fp != 0) {
                            // 0x0033136c
                            charge(ctx, 6);
                            lw(v1, s1, kPsysParams);
                            lw(a0, v1, 192);
                            lw(v1, v1, 196);
                            mult(v1, a0, v1);
                            if (v1 != 0) {
                                // 0x00331384
                                charge(ctx, 15);
                                lw(a0, s1, kPsysParticles);
                                v0 = subu(s4, a0);
                                v0 = srl(v0, 5);
                                mult(v1, v0, v1);
                                lw(v0, s1, kPsysCount);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 5);
                                s5 = addu(a0, v0);
                                a0 = s5;
                                a1 = s4;
                                a2 = 32;
                                jal(ctx, 0x3313B0u, gen::fn_memcpy_00521250);
                                v1 = si(-1);
                                sw(v1, s5, 16);
                            }
                            // 0x003313c0
                            charge(ctx, 3);
                            lw(v1, s4, kPtAge);
                            v1 = addiu(v1, 1);
                            sw(v1, s4, kPtAge);
                        }
                        // 0x003313cc
                        charge(ctx, 3);
                        s0 = addiu(s0, -1);
                    }
                }
            }
            // 0x00331550
            charge(ctx, 3);
            s6 = addiu(s6, 1);
            s3 = addiu(s3, 36);
            s4 = addiu(s4, 32);
        }
    }
    // 0x0033156c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
}

// 0x003315D0 sub_3315D0 -- 128 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 10, slot 1 [fxPsysScale10]: the type's scale ($a0 = the particle system, $f12 = the factor).
// Every size-like parameter of the live block (FxPsys +32) is the base block's (+36) times $f12: the floats at +100,
// +104, the three emission extents +116 / +124 / +132 (stride 8) and the type-10 fields +200, +204, +220. Called
// through the type row (sub_332330 [fxTrackSetTime] in fx_types) when an effect is rescaled.
void sub_3315D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003315d0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, kPsysParams);
    lw(a1, a0, kPsysBaseParams);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x00331618
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003315fc
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x00331624
    charge(ctx, 11);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 204);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 204);
    lwc1(f0, a1, 220);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 220);
}

// 0x00331FD0 sub_331FD0 -- 152 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Particle-system type 11, slot 1 [fxPsysScale11]: the type's scale ($a0 = the particle system, $f12 = the factor).
// Every size-like parameter of the live block (FxPsys +32) is the base block's (+36) times $f12: the floats at +100,
// +104, the three emission extents +116 / +124 / +132 (stride 8) and the type-11 fields +200, +204, +212, +216, +224.
// Called through the type row (sub_332330 [fxTrackSetTime] in fx_types) when an effect is rescaled.
void sub_331FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00331fd0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, kPsysParams);
    lw(a1, a0, kPsysBaseParams);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x00332018
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00331ffc
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x00332024
    charge(ctx, 17);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 204);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 204);
    lwc1(f0, a1, 212);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 212);
    lwc1(f0, a1, 216);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 216);
    lwc1(f0, a1, 224);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 224);
}

// 0x00332070 sub_332070 -- 340 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a particle system [fxPsysCreate] ($a0 = the type (u16), $a1 = the particle count, $a2 = the type
// parameters; returns it in $v0). One RwMalloc block (0x960178, flags 0x40000) holds the 48-byte header, count *
// (cells + 1) particles of 32 bytes (cells = params +192 * +196), the per-particle state (row +8 bytes each, the
// multiplication in HI1/LO1 by mult1) and two copies of the parameters (row +12 bytes): +32 the live set, +36 the
// base for the scale functions. The live position and rotation are cleared (vf0) and flag bit 0 is set when the
// parameters ask for world space (+188). Callers: the class 2 / 15 ribbons (sub_332AC0), sub_326C70 and the EPL
// particle kinds (sub_34D8A0, sub_34E820).
void sub_332070(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x00332070
    enter(ctx, 70);  // entry check point + this block's cycles
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
    s4 = a1;
    s3 = a2;
    lw(v1, a2, 196);
    lw(v0, a2, 192);
    mult(v0, v1, v0);
    v0 = addiu(v0, 1);
    mult(s0, s4, v0);
    s6 = sll(s0, 5);
    v0 = s5 & 0xFFFF;
    v1 = sll(v0, 4);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15080);  // &0x69C518
    v0 = addu(v0, v1);
    lw(v0, v0, kPsysType);
    mult1(a0, s4, v0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15076);  // &0x69C51C
    v0 = addu(v0, v1);
    lw(s1, v0, kPsysType);
    v1 = sll(s1, 1);
    v0 = addiu(s6, 48);
    v0 = addu(a0, v0);
    a0 = addu(v0, v1);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x332100u, v0.u());
    s2 = v0;
    v1 = addiu(v0, 48);
    sw(v1, v0, kPsysParticles);
    v1 = addu(v1, s6);
    sw(v1, v0, kPsysParams);
    v1 = addu(v1, s1);
    sw(v1, v0, kPsysBaseParams);
    v1 = addu(v1, s1);
    sw(v1, v0, kPsysState);
    sh(s5, v0, kPsysType);
    sw(s4, v0, kPsysCount);
    sw(s0, v0, kPsysSlots);
    sw(zero, v0, kPsysFlags);
    sw(zero, v0, kPsysFrame);
    sw(zero, v0, kPsysEmitAcc);
    sw(v0, v0, kPsysSelf);
    lw(a0, v0, kPsysParams);
    a1 = s3;
    a2 = s1;
    jal(ctx, 0x332154u, gen::fn_memcpy_00521250);
    lw(a0, s2, kPsysBaseParams);
    a1 = s3;
    a2 = s1;
    jal(ctx, 0x332168u, gen::fn_memcpy_00521250);
    lw(v0, s2, kPsysParams);
    sqc2(vf0, v0, kPsysType);
    sqc2(vf0, v0, kPsysFrame);
    lbu(v0, v0, 188);
    if (v0 != 0) {
        // 0x00332188: params +188: world-space particles (flag bit 0)
        charge(ctx, 3);
        lw(v0, s2, kPsysFlags);
        v0 = v0 | 0x1;
        sw(v0, s2, kPsysFlags);
    }
    // 0x00332194 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s2;
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

// 0x00332370 sub_332370 -- 248 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 2, slot 0 [fxRibbonCreate] ($a0 = the effect record; returns the instance). Block A (sub_3245B0) holds
// the ribbon head (+0) and the particle parameters (+28): the ribbon count = (params lifetime +32, else particle life
// +184) * rate +36 (the parameters at block +28), at most 100; a 56-byte instance (RwMalloc 0x960178, cleared) with
// colour -1, scale 1.0, +52 = 1; the head and ribbon meshes (sub_332A30) and the particle system (sub_332AC0) from
// the block. The effect kind (+12) is the particle-system type.
void sub_332370(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332370
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x33238Cu, gen::fn_sub_3245B0_003245b0);
    s0 = v0;
    lw(v1, v0, 60);
    if (v1 != 0) {
        // 0x003323b8
        charge(ctx, 2);
        lw(v0, s0, 64);
        mult(s3, v1, v0);
    } else {
        // 0x003323a4
        charge(ctx, 5);
        lw(v1, s0, 212);
        lw(v0, s0, 64);
        mult(s3, v1, v0);
    }
    // 0x003323c0
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x003323cc
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x003323d0: allocate and initialise the 56-byte instance
    charge(ctx, 38);
    a0 = 56;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3323E0u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x3323F8u, gen::fn_memset_00521408);
    sw(s3, s2, kC2Count);
    v0 = si(-1);
    sw(v0, s2, kC2Colour);
    v0 = 0x3F800000;
    sw(v0, s2, kC2Scale);
    v0 = 1;
    sh(v0, s2, kC2Alive);
    lhu(a1, s1, kEfKind);
    a0 = s2;
    a2 = s0;
    jal(ctx, 0x332428u, gen::fn_sub_332A30_00332a30);
    lhu(a1, s1, kEfKind);
    a0 = s2;
    a2 = addiu(s0, 28);
    jal(ctx, 0x33243Cu, gen::fn_sub_332AC0_00332ac0);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00332470 sub_332470 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Sets up the child object of a class 15 ribbon [fxRibbonSetChild] ($a0 = the instance, $a1 = block B's type, $a2 =
// block B). The child (+44) is created on first use (sub_326490 with the ribbon count; its +76 takes the particle
// system). Then by type (jump table 0x7B9290): 1 / 2 / 4 / 7 re-size the child (sub_326CF0) and attach a model frame
// list / sprite set / texture name / image sequence (sub_326E50 / sub_326F00 / sub_326DB0 / sub_3271C0), 5 and 6
// attach without re-sizing (sub_326F60 / sub_327090); 0 and 3 attach nothing. The child's type word (+12) takes $a1.
void sub_332470(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332470
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(v1, a0, 44);
    if (v1 == 0) {
        // 0x0033249c: no child yet: create it (sub_326490), its +76 = the particle system
        charge(ctx, 6);
        lw(a0, s2, kC2Count);
        jal(ctx, 0x3324A0u, gen::fn_sub_326490_00326490);
        sw(v0, s2, kC2Child);
        lw(v1, s2, kC2Psys);
        sw(v1, v0, 76);
    }
    // 0x003324b4
    charge(ctx, 4);
    a2 = s1 & 0xFFFF;
    at = sltiu(a2, 8);
    if (at != 0) {
        // 0x003324c4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -28016);  // &0x7B9290
        v1 = sll(a2, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x3324E0u:  // table[1]
            // 0x003324e0
            charge(ctx, 10);
            lw(a0, s2, kC2Child);
            lw(a1, s2, kC2Count);
            jal(ctx, 0x3324E8u, gen::fn_sub_326CF0_00326cf0);
            lw(a0, s2, kC2Child);
            a1 = s0;
            jal(ctx, 0x3324F8u, gen::fn_sub_326E50_00326e50);
            break;
        case 0x332508u:  // table[2]
            // 0x00332508
            charge(ctx, 10);
            lw(a0, s2, kC2Child);
            lw(a1, s2, kC2Count);
            jal(ctx, 0x332510u, gen::fn_sub_326CF0_00326cf0);
            lw(a0, s2, kC2Child);
            a1 = s0;
            jal(ctx, 0x332520u, gen::fn_sub_326F00_00326f00);
            break;
        case 0x332530u:  // table[4]
            // 0x00332530
            charge(ctx, 10);
            lw(a0, s2, kC2Child);
            lw(a1, s2, kC2Count);
            jal(ctx, 0x332538u, gen::fn_sub_326CF0_00326cf0);
            lw(a0, s2, kC2Child);
            lw(a1, s0, 0);
            jal(ctx, 0x332548u, gen::fn_sub_326DB0_00326db0);
            break;
        case 0x332558u:  // table[5]
            // 0x00332558
            charge(ctx, 6);
            lw(a0, s2, kC2Child);
            a1 = s0;
            jal(ctx, 0x332560u, gen::fn_sub_326F60_00326f60);
            break;
        case 0x332570u:  // table[6]
            // 0x00332570
            charge(ctx, 6);
            lw(a0, s2, kC2Child);
            a1 = s0;
            jal(ctx, 0x332578u, gen::fn_sub_327090_00327090);
            break;
        case 0x332588u:  // table[7]
            // 0x00332588
            charge(ctx, 8);
            lw(a0, s2, kC2Child);
            lw(a1, s2, kC2Count);
            jal(ctx, 0x332590u, gen::fn_sub_326CF0_00326cf0);
            lw(a0, s2, kC2Child);
            a1 = s0;
            jal(ctx, 0x3325A0u, gen::fn_sub_3271C0_003271c0);
            break;
        case 0x3325A8u:  // table[0, 3]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x003325a8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, s2, kC2Child);
    sh(s1, v1, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003325D0 sub_3325D0 -- 292 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 15, slot 0 [fxRibbonCreate15]: as sub_332370 (the ribbon count = (params lifetime +32, else particle
// life +184) * rate +36 (the parameters at block +28), at most 100; a 56-byte instance (RwMalloc 0x960178, cleared)
// with colour -1, scale 1.0, +52 = 1; the head and ribbon meshes (sub_332A30) and the particle system (sub_332AC0)
// from the block), then when block B is present (sub_3245F0) the class-1 child object is set up from it by sub_332470
// with block B's type (+28).
void sub_3325D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003325d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3325ECu, gen::fn_sub_3245B0_003245b0);
    s0 = v0;
    a0 = addiu(s0, 28);
    lw(v1, v0, 60);
    if (v1 != 0) {
        // 0x0033261c
        charge(ctx, 2);
        lw(v0, a0, 36);
        mult(s3, v1, v0);
    } else {
        // 0x00332608
        charge(ctx, 5);
        lw(v1, a0, 184);
        lw(v0, a0, 36);
        mult(s3, v1, v0);
    }
    // 0x00332624
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x00332630
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x00332634: allocate and initialise the 56-byte instance
    charge(ctx, 34);
    a0 = 56;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x332644u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x33265Cu, gen::fn_memset_00521408);
    sw(s3, s2, kC2Count);
    v0 = si(-1);
    sw(v0, s2, kC2Colour);
    v0 = 0x3F800000;
    sw(v0, s2, kC2Scale);
    v0 = 1;
    sh(v0, s2, kC2Alive);
    lhu(a1, s1, kEfKind);
    a0 = s2;
    a2 = s0;
    jal(ctx, 0x33268Cu, gen::fn_sub_332A30_00332a30);
    lhu(a1, s1, kEfKind);
    a0 = s2;
    a2 = addiu(s0, 28);
    jal(ctx, 0x3326A0u, gen::fn_sub_332AC0_00332ac0);
    a0 = s1;
    jal(ctx, 0x3326ACu, gen::fn_sub_3245F0_003245f0);
    if (v0 != 0) {
        // 0x003326bc: block B: the child object
        charge(ctx, 5);
        a0 = s2;
        lhu(a1, s1, kEfBlockBType);
        a2 = v0;
        jal(ctx, 0x3326C8u, gen::fn_sub_332470_00332470);
    }
    // 0x003326d0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00332700 sub_332700 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect classes 2 and 15, slot 4 [fxRibbonDestroy] ($a0 = the instance): destroys the child object (sub_326740), the
// ribbon meshes (sub_3338B0) and the particle system (sub_3321D0) when present, then frees the instance (RwFree,
// 0x96017C).
void sub_332700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332700
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 44);
    if (a0 != 0) {
        // 0x0033271c
        charge(ctx, 2);
        jal(ctx, 0x33271Cu, gen::fn_sub_326740_00326740);
    }
    // 0x00332724
    charge(ctx, 3);
    lw(a0, s0, kC2Strips);
    if (a0 != 0) {
        // 0x00332730
        charge(ctx, 2);
        jal(ctx, 0x332730u, gen::fn_sub_3338B0_003338b0);
    }
    // 0x00332738
    charge(ctx, 3);
    lw(a0, s0, kC2Psys);
    if (a0 != 0) {
        // 0x00332744
        charge(ctx, 2);
        jal(ctx, 0x332744u, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0033274c
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x332758u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00332780 sub_332780 -- 252 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 2, slot 5 [fxRibbonClone] ($a0 = the instance to copy; returns the new one): the same set-up as
// sub_332370 but from the source's particle system (its base parameters +36 and its type +0) and its head copy (+12).
void sub_332780(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332780
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, 48);
    lw(s1, v0, 36);
    lw(v1, s1, kPpLifetime);
    if (v1 != 0) {
        // 0x003327c4
        charge(ctx, 2);
        lw(v0, s1, kPpRate);
        mult(s3, v1, v0);
    } else {
        // 0x003327b0
        charge(ctx, 5);
        lw(v1, s1, kPpLife);
        lw(v0, s1, kPpRate);
        mult(s3, v1, v0);
    }
    // 0x003327cc
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x003327d8
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x003327dc: allocate and initialise the 56-byte instance
    charge(ctx, 40);
    a0 = 56;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3327ECu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x332804u, gen::fn_memset_00521408);
    sw(s3, s0, kC2Count);
    v0 = si(-1);
    sw(v0, s0, kC2Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kC2Scale);
    v0 = 1;
    sh(v0, s0, kC2Alive);
    lw(v0, s2, kC2Psys);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = addiu(s2, 12);
    jal(ctx, 0x332838u, gen::fn_sub_332A30_00332a30);
    lw(v0, s2, kC2Psys);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = s1;
    jal(ctx, 0x332850u, gen::fn_sub_332AC0_00332ac0);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00332880 sub_332880 -- 268 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 15, slot 5 [fxRibbonClone15]: as sub_332780, then the child object is copied by sub_332990.
void sub_332880(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332880
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, 48);
    lw(s1, v0, 36);
    lw(v1, s1, kPpLifetime);
    if (v1 != 0) {
        // 0x003328c4
        charge(ctx, 2);
        lw(v0, s1, kPpRate);
        mult(s3, v1, v0);
    } else {
        // 0x003328b0
        charge(ctx, 5);
        lw(v1, s1, kPpLife);
        lw(v0, s1, kPpRate);
        mult(s3, v1, v0);
    }
    // 0x003328cc
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x003328d8
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x003328dc: allocate and initialise the 56-byte instance
    charge(ctx, 44);
    a0 = 56;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3328ECu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x332904u, gen::fn_memset_00521408);
    sw(s3, s0, kC2Count);
    v0 = si(-1);
    sw(v0, s0, kC2Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kC2Scale);
    v0 = 1;
    sh(v0, s0, kC2Alive);
    lw(v0, s2, kC2Psys);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = addiu(s2, 12);
    jal(ctx, 0x332938u, gen::fn_sub_332A30_00332a30);
    lw(v0, s2, kC2Psys);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = s1;
    jal(ctx, 0x332950u, gen::fn_sub_332AC0_00332ac0);
    a0 = s0;
    a1 = s2;
    jal(ctx, 0x332960u, gen::fn_sub_332990_00332990);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00332990 sub_332990 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Copies the child object of a ribbon [fxRibbonCopyChild] ($a0 = the new instance, $a1 = the source): creates the
// child on first use (sub_326490, +76 = the particle system), duplicates the source child's image sequence (+80,
// sub_323640) when it has one, copies the rest with sub_3269E0 and the type word (+12).
void sub_332990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332990
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    lw(v0, a0, 44);
    if (v0 == 0) {
        // 0x003329b4: no child yet: create it
        charge(ctx, 6);
        lw(a0, s0, kC2Count);
        jal(ctx, 0x3329B8u, gen::fn_sub_326490_00326490);
        sw(v0, s0, kC2Child);
        lw(v1, s0, kC2Psys);
        sw(v1, v0, 76);
    }
    // 0x003329cc
    charge(ctx, 4);
    lw(v0, s1, kC2Child);
    lw(a0, v0, 80);
    if (a0 != 0) {
        // 0x003329dc: the source child has an image sequence: duplicate it
        charge(ctx, 4);
        jal(ctx, 0x3329DCu, gen::fn_sub_323640_00323640);
        lw(v1, s0, kC2Child);
        sw(v0, v1, 80);
    }
    // 0x003329ec
    charge(ctx, 14);
    lw(a0, s0, kC2Child);
    lw(a1, s1, kC2Child);
    jal(ctx, 0x3329F4u, gen::fn_sub_3269E0_003269e0);
    lw(v1, s1, kC2Child);
    lhu(a0, v1, 12);
    lw(v1, s0, kC2Child);
    sh(a0, v1, 12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00332A30 sub_332A30 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Sets the head of a ribbon [fxRibbonSetHead] ($a0 = the instance, $a1 = the type (unused), $a2 = the block head):
// copies the 28-byte head to +12 and, when the instance has ribbons, replaces the ribbon meshes: the old ones are
// destroyed (sub_3338B0), new ones made for the count and the head's points per ribbon (sub_3330E0) and coloured from
// the head's colour pair (+8, sub_333420).
void sub_332A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332a30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a0 = addiu(s1, 12);
    a1 = s0;
    a2 = 28;
    jal(ctx, 0x332A54u, gen::fn_memcpy_00521250);
    lw(v1, s1, kC2Count);
    if (v1 != 0) {
        // 0x00332a68: ribbons: rebuild the meshes
        charge(ctx, 3);
        lw(a0, s1, kC2Strips);
        if (a0 != 0) {
            // 0x00332a74
            charge(ctx, 2);
            jal(ctx, 0x332A74u, gen::fn_sub_3338B0_003338b0);
        }
        // 0x00332a7c
        charge(ctx, 9);
        lhu(a0, s1, kC2Count);
        lhu(a1, s0, 0);
        jal(ctx, 0x332A84u, gen::fn_sub_3330E0_003330e0);
        sw(v0, s1, kC2Strips);
        a0 = v0;
        a1 = addiu(s0, 8);
        jal(ctx, 0x332A98u, gen::fn_sub_333420_00333420);
    }
    // 0x00332aa0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00332AC0 sub_332AC0 -- 104 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Replaces the particle system of a ribbon [fxRibbonSetPsys] ($a0 = the instance, $a1 = the type, $a2 = the
// parameters): frees the old one (sub_3321D0) and creates one of the type with the instance's count (sub_332070).
void sub_332AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00332ac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, 48);
    if (a0 != 0) {
        // 0x00332aec
        charge(ctx, 2);
        jal(ctx, 0x332AECu, gen::fn_sub_3321D0_003321d0);
    }
    // 0x00332af4
    charge(ctx, 13);
    a0 = s1 & 0xFFFF;
    lw(a1, s2, kC2Count);
    a2 = s0;
    jal(ctx, 0x332B00u, gen::fn_sub_332070_00332070);
    sw(v0, s2, kC2Psys);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00332B60 sub_332B60 -- 688 bytes; frame 0xA0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect classes 2 and 15, slot 2 [fxRibbonStep] ($a0 = the instance; nothing without ribbons). Steps the particle
// system (sub_332210), takes the instance colour as floats / 255 (x 0x7CAE4C) and locks the ribbon meshes
// (sub_3341C0). Then per ribbon i with particle i: a ribbon whose mask is set (sub_333940) is left alone; a finished
// particle (-2) collapses the ribbon to the origin 0x957A90 with the tint gp-18348 and sets its mask (sub_333920); a
// free or newborn particle does the same but clears the mask (sub_333900); a live one pushes its position into the
// ribbon with its size (sub_333970) and colours it with the particle colour x the instance colour (VU0: bytes to
// floats, x 1/255, x 255, back to bytes; sub_333300). Afterwards the meshes are unlocked (sub_334220) and the child
// object, from its start frame on (+16), gets the colour (sub_329490) and runs (sub_327250 with the scale +36 / 10).
void sub_332B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00332b60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(v1, a0, 0);
    if (v1 != 0) {
        // 0x00332b90: step the particle system; colour as floats; lock the meshes
        charge(ctx, 28);
        lw(a0, s4, kC2Psys);
        jal(ctx, 0x332B94u, gen::fn_sub_332210_00332210);
        lw(v1, s4, kC2Psys);
        lw(v0, s4, kC2Colour);
        sw(v0, sp, 0x98);
        v0 = addiu(sp, 0x98);
        lwc1(f20, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f20);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x70);
        sqc2(vf10, v0, 0);
        lw(s3, v1, 24);
        lw(s0, s4, kC2Count);
        lw(s1, s4, kC2Strips);
        a0 = s1;
        jal(ctx, 0x332BECu, gen::fn_sub_3341C0_003341c0);
        s2 = 0;
        for (;;) {
            // 0x00332d7c: for each ribbon
            charge(ctx, 3);
            v0 = slt(s2, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00332c00: ribbon i still drawn? (mask, sub_333940)
            charge(ctx, 6);
            a1 = s2 & 0xFFFF;
            a0 = s1;
            jal(ctx, 0x332C08u, gen::fn_sub_333940_00333940);
            if (v0 == 0) {
                // 0x00332c18
                charge(ctx, 4);
                lw(v1, s3, kPtAge);
                v0 = si(-2);
                if (v1 != v0) {
                    // 0x00332c70
                    charge(ctx, 3);
                    v0 = si(-1);
                    if (v1 != v0) {
                        // 0x00332c7c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            goto L_00332c84;
                        }
                        // 0x00332ccc: live particle: push its position (size +24), colour = particle x instance
                        charge(ctx, 42);
                        lwc1(f0, s3, kPtPos);
                        swc1(f0, sp, 0x80);
                        lwc1(f0, s3, 4);
                        swc1(f0, sp, 0x84);
                        lwc1(f0, s3, 8);
                        swc1(f0, sp, 0x88);
                        a1 = s2 & 0xFFFF;
                        a0 = s1;
                        a2 = addiu(sp, 0x80);
                        lwc1(f12, s3, kPtScale);
                        jal(ctx, 0x332CF4u, gen::fn_sub_333970_00333970);
                        lw(v0, s3, kPtColour);
                        sw(v0, sp, 0x94);
                        v0 = addiu(sp, 0x94);
                        lw(v0, v0, 0);
                        pextlb(v0, zero, v0);
                        pextlh(v0, zero, v0);
                        qmtc2(v0, vf10, false);  // qmtc2
                        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x70);
                        lqc2(vf11, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        v0 = 0x437F0000;
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x90);
                        lw(v0, sp, 0x90);
                        sw(v0, sp, 0x9C);
                        a1 = s2 & 0xFFFF;
                        a0 = s1;
                        a2 = addiu(sp, 0x9C);
                        jal(ctx, 0x332D6Cu, gen::fn_sub_333300_00333300);
                        goto L_00332d74;
                    }
                L_00332c84:
                    charge(ctx, 18);
                    a1 = s2 & 0xFFFF;
                    mtc1(zero, f12);
                    a0 = s1;
                    a2 = 0x950000;
                    a2 = addiu(a2, 31376);  // &0x957A90
                    jal(ctx, 0x332C98u, gen::fn_sub_333970_00333970);
                    a1 = s2 & 0xFFFF;
                    a0 = s1;
                    a2 = addiu(gp, -18348);  // &0x7CE544
                    jal(ctx, 0x332CACu, gen::fn_sub_333300_00333300);
                    a1 = s2 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x332CBCu, gen::fn_sub_333900_00333900);
                } else {
                    // 0x00332c28: finished particle: collapse the ribbon to 0x957A90, tint, set the mask
                    charge(ctx, 18);
                    a1 = s2 & 0xFFFF;
                    mtc1(zero, f12);
                    a0 = s1;
                    a2 = 0x950000;
                    a2 = addiu(a2, 31376);  // &0x957A90
                    jal(ctx, 0x332C3Cu, gen::fn_sub_333970_00333970);
                    a1 = s2 & 0xFFFF;
                    a0 = s1;
                    a2 = addiu(gp, -18348);  // &0x7CE544
                    jal(ctx, 0x332C50u, gen::fn_sub_333300_00333300);
                    a1 = s2 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x332C60u, gen::fn_sub_333920_00333920);
                }
            }
        L_00332d74:
            charge(ctx, 2);
            s2 = addiu(s2, 1);
            s3 = addiu(s3, 32);
        }
        // 0x00332d88: unlock the meshes; the child object from its start frame on
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x332D8Cu, gen::fn_sub_334220_00334220);
        lw(a0, s4, kC2Child);
        if (a0 != 0) {
            // 0x00332da0
            charge(ctx, 6);
            lw(v1, s4, kC2Psys);
            lw(a1, v1, 16);
            lw(v1, s4, kC2ChildStart);
            v1 = sltu(a1, v1);
            if (v1 == 0) {
                // 0x00332db8
                charge(ctx, 12);
                lw(a1, s4, kC2Colour);
                jal(ctx, 0x332DBCu, gen::fn_sub_329490_00329490);
                v0 = 0x41200000;
                mtc1(v0, f1);
                lwc1(f0, s4, kC2ChildScale);
                div_s(f12, f0, f1);
                lw(a0, s4, kC2Child);
                jal(ctx, 0x332DE0u, gen::fn_sub_327250_00327250);
            }
        }
    }
    // 0x00332de8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00332E10 sub_332E10 -- 256 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect classes 2 and 15, slot 3 [fxRibbonDraw] ($a0 = the instance): nothing before the particle system's second
// frame. When the particles live in world space (flag bit 0) both ribbon meshes are placed at the system position /
// rotation (sub_3322F0 / sub_3322B0 into stack vectors, sub_324470 with scale 1.0); the child object is drawn
// (sub_3275D0, scale +36 / 10); the meshes are queued on the parameters' draw layer (+84, sub_3342C0
// [fxObj2AttachBoth]).
void sub_332E10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00332e10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 0);
    if (v1 != 0) {
        // 0x00332e34
        charge(ctx, 5);
        lw(a0, s2, kC2Psys);
        lw(v1, a0, 16);
        at = slti(v1, 2);
        if (at == 0) {
            // 0x00332e48: from frame 2: meshes, parameters
            charge(ctx, 6);
            lw(s1, s2, kC2Strips);
            lw(s0, a0, 32);
            lw(v0, a0, 12);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x00332e60: world space: place both meshes at the system
                charge(ctx, 21);
                a1 = addiu(sp, 0x40);
                jal(ctx, 0x332E64u, gen::fn_sub_3322F0_003322f0);
                lw(a0, s2, kC2Psys);
                a1 = addiu(sp, 0x50);
                jal(ctx, 0x332E74u, gen::fn_sub_3322B0_003322b0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s1, kStMeshA);
                a1 = addiu(sp, 0x50);
                a2 = addiu(sp, 0x40);
                jal(ctx, 0x332E90u, gen::fn_sub_324470_00324470);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s1, kStMeshB);
                a1 = addiu(sp, 0x50);
                a2 = addiu(sp, 0x40);
                jal(ctx, 0x332EACu, gen::fn_sub_324470_00324470);
            }
            // 0x00332eb4
            charge(ctx, 3);
            lw(a0, s2, kC2Child);
            if (a0 != 0) {
                // 0x00332ec0: the child object
                charge(ctx, 9);
                v0 = 0x41200000;
                mtc1(v0, f1);
                lwc1(f0, s2, kC2ChildScale);
                div_s(f12, f0, f1);
                jal(ctx, 0x332EDCu, gen::fn_sub_3275D0_003275d0);
            }
            // 0x00332ee4: queue on the draw layer +84
            charge(ctx, 4);
            lhu(a1, s0, kPpLayer);
            a0 = s1;
            jal(ctx, 0x332EECu, gen::fn_sub_3342C0_003342c0);
        }
    }
    // 0x00332ef4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00332F10 sub_332F10 -- 264 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect classes 2 and 15, slot 1 [fxRibbonUpdate]: sub_332B60 [fxRibbonStep], then the body of sub_332E10
// [fxRibbonDraw] inline: nothing before the particle system's second frame. When the particles live in world space
// (flag bit 0) both ribbon meshes are placed at the system position / rotation (sub_3322F0 / sub_3322B0 into stack
// vectors, sub_324470 with scale 1.0); the child object is drawn (sub_3275D0, scale +36 / 10); the meshes are queued
// on the parameters' draw layer (+84, sub_3342C0 [fxObj2AttachBoth]).
void sub_332F10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00332f10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x332F28u, gen::fn_sub_332B60_00332b60);
    lw(v1, s2, kC2Count);
    if (v1 != 0) {
        // 0x00332f3c
        charge(ctx, 5);
        lw(a0, s2, kC2Psys);
        lw(v1, a0, 16);
        at = slti(v1, 2);
        if (at == 0) {
            // 0x00332f50: from frame 2: meshes, parameters
            charge(ctx, 6);
            lw(s1, s2, kC2Strips);
            lw(s0, a0, 32);
            lw(v0, a0, 12);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x00332f68: world space: place both meshes at the system
                charge(ctx, 21);
                a1 = addiu(sp, 0x40);
                jal(ctx, 0x332F6Cu, gen::fn_sub_3322F0_003322f0);
                lw(a0, s2, kC2Psys);
                a1 = addiu(sp, 0x50);
                jal(ctx, 0x332F7Cu, gen::fn_sub_3322B0_003322b0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s1, kStMeshA);
                a1 = addiu(sp, 0x50);
                a2 = addiu(sp, 0x40);
                jal(ctx, 0x332F98u, gen::fn_sub_324470_00324470);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s1, kStMeshB);
                a1 = addiu(sp, 0x50);
                a2 = addiu(sp, 0x40);
                jal(ctx, 0x332FB4u, gen::fn_sub_324470_00324470);
            }
            // 0x00332fbc
            charge(ctx, 3);
            lw(a0, s2, kC2Child);
            if (a0 != 0) {
                // 0x00332fc8: the child object
                charge(ctx, 9);
                v0 = 0x41200000;
                mtc1(v0, f1);
                lwc1(f0, s2, kC2ChildScale);
                div_s(f12, f0, f1);
                jal(ctx, 0x332FE4u, gen::fn_sub_3275D0_003275d0);
            }
            // 0x00332fec: queue on the draw layer +84
            charge(ctx, 4);
            lhu(a1, s0, kPpLayer);
            a0 = s1;
            jal(ctx, 0x332FF4u, gen::fn_sub_3342C0_003342c0);
        }
    }
    // 0x00332ffc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003330E0 sub_3330E0 -- 536 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates the ribbon meshes [fxStripsCreate] ($a0 = the ribbon count, $a1 = points per ribbon; returns the object). A
// cleared block of 28 + 2 n bytes (+24 points to the u16 lengths at +28); +16 a band mesh (sub_323FB0, layout
// 0x69BCD0, 3 vertices a point, vertex size 72), +20 a grid mesh (sub_323E10, layout 0x69BDE0); flag 4 of both
// cleared. Every ribbon's material colour of both meshes takes the tint gp-18348 (an alpha of 255 written as 254,
// then restored: the fx_types finding).
void sub_3330E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003330e0
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s1 = s4 & 0xFFFF;
    v0 = sll(s1, 1);
    s2 = addiu(v0, 28);
    a0 = s2;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x333120u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = s2;
    jal(ctx, 0x333138u, gen::fn_memset_00521408);
    v0 = addiu(s0, 28);
    sw(v0, s0, kStLengths);
    a0 = s4;
    a1 = s3;
    a2 = 0x6A0000;
    a2 = addiu(a2, -17200);  // &0x69BCD0
    a3 = 3;
    t0 = 72;
    jal(ctx, 0x333160u, gen::fn_sub_323FB0_00323fb0);
    sw(v0, s0, kStMeshA);
    lhu(v1, v0, 0);
    v1 = v1 & 0xFFFB;
    sh(v1, v0, 0);
    a0 = s4;
    a1 = 1;
    a2 = 6;
    a3 = 8;
    t0 = 0x6A0000;
    t0 = addiu(t0, -16928);  // &0x69BDE0
    t1 = 72;
    jal(ctx, 0x333194u, gen::fn_sub_323E10_00323e10);
    sw(v0, s0, kStMeshB);
    lhu(v1, v0, 0);
    v1 = v1 & 0xFFFB;
    sh(v1, v0, 0);
    a1 = 0;
    v1 = 255;
    v0 = 254;
    for (;;) {
        // 0x003332c4: for each ribbon: both meshes' colour = the tint gp-18348
        charge(ctx, 3);
        a0 = sltu(a1, s1);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003331c0
        charge(ctx, 4);
        lw(a2, s0, kStMeshA);
        lbu(a0, gp, -18345);  // 0x7CE547
        if (a0 == v1) {
            // 0x0033320c
            charge(ctx, 15);
            sb(v0, gp, -18345);  // 0x7CE547
            a0 = a1 & 0xFFFF;
            a0 = sll(a0, 2);
            lw(a2, a2, 40);
            a2 = addu(a2, a0);
            lw(t2, a2, 0);
            lbu(t1, gp, -18348);  // 0x7CE544
            lbu(t0, gp, -18347);  // 0x7CE545
            lbu(a3, gp, -18346);  // 0x7CE546
            lbu(a2, gp, -18345);  // 0x7CE547
            sb(t1, t2, 4);
            sb(t0, t2, 5);
            sb(a3, t2, 6);
            sb(a2, t2, 7);
            sb(v1, gp, -18345);  // 0x7CE547
        } else {
            // 0x003331d0
            charge(ctx, 15);
            a0 = a1 & 0xFFFF;
            a0 = sll(a0, 2);
            lw(a2, a2, 40);
            a2 = addu(a2, a0);
            lw(t2, a2, 0);
            lbu(t1, gp, -18348);  // 0x7CE544
            lbu(t0, gp, -18347);  // 0x7CE545
            lbu(a3, gp, -18346);  // 0x7CE546
            lbu(a2, gp, -18345);  // 0x7CE547
            sb(t1, t2, 4);
            sb(t0, t2, 5);
            sb(a3, t2, 6);
            sb(a2, t2, 7);
        }
        // 0x00333248
        charge(ctx, 4);
        lw(a3, s0, kStMeshB);
        lbu(a2, gp, -18345);  // 0x7CE547
        if (a2 == v1) {
            // 0x0033328c
            charge(ctx, 13);
            sb(v0, gp, -18345);  // 0x7CE547
            lw(a2, a3, 40);
            a0 = addu(a2, a0);
            lw(t1, a0, 0);
            lbu(t0, gp, -18348);  // 0x7CE544
            lbu(a3, gp, -18347);  // 0x7CE545
            lbu(a2, gp, -18346);  // 0x7CE546
            lbu(a0, gp, -18345);  // 0x7CE547
            sb(t0, t1, 4);
            sb(a3, t1, 5);
            sb(a2, t1, 6);
            sb(a0, t1, 7);
            sb(v1, gp, -18345);  // 0x7CE547
        } else {
            // 0x00333258
            charge(ctx, 13);
            lw(a2, a3, 40);
            a0 = addu(a2, a0);
            lw(t1, a0, 0);
            lbu(t0, gp, -18348);  // 0x7CE544
            lbu(a3, gp, -18347);  // 0x7CE545
            lbu(a2, gp, -18346);  // 0x7CE546
            lbu(a0, gp, -18345);  // 0x7CE547
            sb(t0, t1, 4);
            sb(a3, t1, 5);
            sb(a2, t1, 6);
            sb(a0, t1, 7);
        }
        // 0x003332c0
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x003332d0
    charge(ctx, 10);
    v0 = s0;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00333300 sub_333300 -- 280 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Sets the colour of one ribbon [fxStripsSetColour] ($a0 = the ribbon meshes, $a1 = the ribbon (u16), $a2 = the RGBA
// bytes): the colour pointer of ribbon i (mesh +40 [i]) of both meshes gets the four bytes at +4..+7; an alpha of 255
// is written as 254 and restored afterwards (fx_types finding 5).
void sub_333300(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x00333300
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a3, a0, kStMeshA);
    lbu(v1, a2, 3);
    t3 = 255;
    if (v1 == t3) {
        // 0x00333350: alpha 255: write 254, then restore
        charge(ctx, 16);
        v1 = 254;
        sb(v1, a2, 3);
        v1 = a1 & 0xFFFF;
        v1 = sll(v1, 2);
        lw(a1, a3, 40);
        a1 = addu(a1, v1);
        lw(t2, a1, 0);
        lbu(t1, a2, 0);
        lbu(t0, a2, 1);
        lbu(a3, a2, 2);
        lbu(a1, a2, 3);
        sb(t1, t2, 4);
        sb(t0, t2, 5);
        sb(a3, t2, 6);
        sb(a1, t2, 7);
        sb(t3, a2, 3);
    } else {
        // 0x00333314
        charge(ctx, 15);
        v1 = a1 & 0xFFFF;
        v1 = sll(v1, 2);
        lw(a1, a3, 40);
        a1 = addu(a1, v1);
        lw(t2, a1, 0);
        lbu(t1, a2, 0);
        lbu(t0, a2, 1);
        lbu(a3, a2, 2);
        lbu(a1, a2, 3);
        sb(t1, t2, 4);
        sb(t0, t2, 5);
        sb(a3, t2, 6);
        sb(a1, t2, 7);
    }
    // 0x00333390: the second mesh
    charge(ctx, 5);
    lw(a1, a0, kStMeshB);
    lbu(a0, a2, 3);
    t1 = 255;
    if (a0 == t1) {
        // 0x003333d8
        charge(ctx, 14);
        a0 = 254;
        sb(a0, a2, 3);
        lw(a0, a1, 40);
        v1 = addu(a0, v1);
        lw(t0, v1, 0);
        lbu(a3, a2, 0);
        lbu(a1, a2, 1);
        lbu(a0, a2, 2);
        lbu(v1, a2, 3);
        sb(a3, t0, 4);
        sb(a1, t0, 5);
        sb(a0, t0, 6);
        sb(v1, t0, 7);
        sb(t1, a2, 3);
    } else {
        // 0x003333a4
        charge(ctx, 13);
        lw(a0, a1, 40);
        v1 = addu(a0, v1);
        lw(t0, v1, 0);
        lbu(a3, a2, 0);
        lbu(a1, a2, 1);
        lbu(a0, a2, 2);
        lbu(v1, a2, 3);
        sb(a3, t0, 4);
        sb(a1, t0, 5);
        sb(a0, t0, 6);
        sb(v1, t0, 7);
    }
    // 0x00333410 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00333420 sub_333420 -- 1168 bytes; frame 0xF0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq); lock the band mesh (prelight); the start / end key colours as floats (VU0, x 1/255)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Fills the prelight colours of the band mesh [fxStripsSetGradient] ($a0 = the ribbon meshes, $a1 = the head's colour
// block: start / end RGBA). Locks the band mesh geometry (prelight, rwGEOMETRYLOCKPRELIGHT 8), turns the key colours
// into floats (VU0, x 1/255 = 0x7CAE4C) and writes, for each point along a ribbon (vertex count / 3 points, three
// vertices a point), the colour interpolated from start to end, scaled back to bytes; then unlocks (sub_4933D0) and
// re-instances when the mesh asks for it (flag 4 -> lockedSinceLastInst bit 0).
void sub_333420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00333420: lock the band mesh (prelight); the start / end key colours as floats (VU0, x 1/255)
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    s1 = a1;
    lw(s3, a0, 16);
    lw(v0, s3, 16);
    lw(a0, v0, 24);
    a1 = 8;
    jal(ctx, 0x333460u, gen::fn_geometryLock_00493370);
    lh(s2, s3, 28);
    lh(a3, s3, 8);
    v0 = 3;
    divu(a3, v0);
    mflo(a2);
    lw(v0, s3, 16);
    lw(v0, v0, 24);
    lw(s0, v0, 48);
    s7 = s0;
    v0 = 0x3F800000;
    mtc1(v0, f1);
    if (i64(a2) < 0) {
        // 0x003334b0
        charge(ctx, 7);
        v1 = srl(a2, 1);
        v0 = a2 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0033349c
        charge(ctx, 5);
        mtc1(a2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x003334cc
    charge(ctx, 64);
    div_s(f2, f1, f0);
    mtc1(zero, f3);
    lw(v0, s1, 0);
    sw(v0, sp, 0xEC);
    v0 = addiu(sp, 0xEC);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    a1 = addiu(sp, 0xC0);
    sqc2(vf10, a1, 0);
    lw(v0, s1, 4);
    sw(v0, sp, 0xE8);
    v0 = addiu(sp, 0xE8);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    a0 = addiu(sp, 0xA0);
    sqc2(vf10, a0, 0);
    lw(v0, s1, 8);
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
    v1 = addiu(sp, 0xB0);
    sqc2(vf10, v1, 0);
    lw(v0, s1, 12);
    sw(v0, sp, 0xE0);
    v0 = addiu(sp, 0xE0);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    t5 = addiu(sp, 0x90);
    sqc2(vf10, t5, 0);
    v0 = 0;
    if (a2 != 0) {
        // 0x003335cc: for each point of the first ribbon: the interpolated colour on its three vertices
        charge(ctx, 5);
        t0 = 0x3F800000;
        mtc1(t0, f1);
        t4 = 0x437F0000;
        for (;;) {
            // 0x003336b0
            charge(ctx, 3);
            t0 = sltu(v0, a2);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003335e0
            charge(ctx, 52);
            lqc2(vf11, a1, 0);
            lqc2(vf10, v1, 0);
            mfc1(t0, f3);
            qmtc2(t0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            sub_s(f0, f1, f3);
            mfc1(t0, f0);
            qmtc2(t0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
            qmtc2(t4, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(t0, vf10, false);  // qmfc2
            ppach(t0, zero, t0);
            ppacb(t0, zero, t0);
            sw(t0, sp, 0xDC);
            lw(t0, sp, 0xDC);
            sw(t0, s0, 4);
            lqc2(vf11, a0, 0);
            lqc2(vf10, t5, 0);
            mfc1(t0, f3);
            qmtc2(t0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            mfc1(t0, f0);
            qmtc2(t0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
            qmtc2(t4, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(t0, vf10, false);  // qmfc2
            ppach(t0, zero, t0);
            ppacb(t0, zero, t0);
            sw(t0, sp, 0xD8);
            lw(t0, sp, 0xD8);
            sw(t0, s0, 0);
            lbu(t3, s0, 0);
            lbu(t2, s0, 1);
            lbu(t1, s0, 2);
            lbu(t0, s0, 3);
            sb(t3, s0, 8);
            sb(t2, s0, 9);
            sb(t1, s0, 10);
            sb(t0, s0, 11);
            add_s(f3, f3, f2);
            s0 = addiu(s0, 12);
            v0 = addiu(v0, 1);
        }
    }
    // 0x003336bc
    charge(ctx, 4);
    s4 = 1;
    s5 = sll(a3, 2);
    for (;;) {
        // 0x003336e8
        charge(ctx, 3);
        v0 = sltu(s4, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003336cc: copy the first ribbon's colours to every other ribbon (memcpy)
        charge(ctx, 7);
        a0 = s0;
        a1 = s7;
        a2 = s5;
        jal(ctx, 0x3336D8u, gen::fn_memcpy_00521250);
        s0 = addu(s0, s5);
        s4 = addiu(s4, 1);
    }
    // 0x003336f4: unlock the band mesh (re-instance when flagged)
    charge(ctx, 9);
    lw(v0, s3, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x333700u, gen::fn_sub_4933D0_004933d0);
    lhu(v0, s3, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00333718
        charge(ctx, 3);
        lhu(v0, s0, 12);
        v0 = v0 | 0x1;
        sh(v0, s0, 12);
    }
    // 0x00333724: the grid mesh: lock, copy the colours to every ribbon, unlock
    charge(ctx, 65);
    lw(s0, s6, 20);
    lw(v0, s0, 16);
    lw(a0, v0, 24);
    a1 = 8;
    jal(ctx, 0x333734u, gen::fn_geometryLock_00493370);
    lw(v0, s0, 16);
    lw(v0, v0, 24);
    lw(s3, v0, 48);
    lw(v0, s1, 0);
    sw(v0, s3, 0);
    lw(v0, s1, 4);
    sw(v0, s3, 4);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 8);
    sb(a0, s3, 9);
    sb(v1, s3, 10);
    sb(v0, s3, 11);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 12);
    sb(a0, s3, 13);
    sb(v1, s3, 14);
    sb(v0, s3, 15);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 16);
    sb(a0, s3, 17);
    sb(v1, s3, 18);
    sb(v0, s3, 19);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 20);
    sb(a0, s3, 21);
    sb(v1, s3, 22);
    sb(v0, s3, 23);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 24);
    sb(a0, s3, 25);
    sb(v1, s3, 26);
    sb(v0, s3, 27);
    lbu(a1, s3, 4);
    lbu(a0, s3, 5);
    lbu(v1, s3, 6);
    lbu(v0, s3, 7);
    sb(a1, s3, 28);
    sb(a0, s3, 29);
    sb(v1, s3, 30);
    sb(v0, s3, 31);
    s4 = addiu(s3, 32);
    s1 = 1;
    for (;;) {
        // 0x00333844
        charge(ctx, 3);
        v0 = sltu(s1, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00333828
        charge(ctx, 7);
        a0 = s4;
        a1 = s3;
        a2 = 32;
        jal(ctx, 0x333834u, gen::fn_memcpy_00521250);
        s4 = addiu(s4, 32);
        s1 = addiu(s1, 1);
    }
    // 0x00333850
    charge(ctx, 9);
    lw(v0, s0, 16);
    lw(s1, v0, 24);
    a0 = s1;
    jal(ctx, 0x33385Cu, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s0, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00333874
        charge(ctx, 3);
        lhu(v1, s1, 12);
        v1 = v1 | 0x1;
        sh(v1, s1, 12);
    }
    // 0x00333880 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
}

// 0x00333970 sub_333970 -- 2120 bytes; frame 0xC0: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0; ribbon i's vertices in the band geometry (morph target +20, three per point)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Pushes a new head point into one ribbon [fxStripsPush] ($a0 = the ribbon meshes, $a1 = the ribbon, $a2 = the point
// (vec3), $f12 = the width). The ribbon's vertices (morph target +20 of the band geometry, 12 bytes each, three per
// point) are shifted back by one point and the new point goes in front; the pushed count (+24 [i]) grows up to the
// ribbon length. Then the band is rebuilt from the camera (0x69C4C0 / sub_329890): for each point the side vector is
// the normalised cross product of the segment and the view direction (VU0 vopmula / vopmsub, vrsqrt), scaled by the
// width tapering along the ribbon, giving the two outer vertices; the grid mesh's vertices of the ribbon are written
// from the same points (the head cap from 0x7CAD94-relative constants).
void sub_333970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf3{ctx, 3}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf24{ctx, 24}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00333970: ribbon i's vertices in the band geometry (morph target +20, three per point)
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s5 = a1;
    mov_s(f24, f12);
    lw(a0, a0, 16);
    lhu(v1, a0, 8);
    lw(a0, a0, 16);
    lw(a0, a0, 24);
    lw(a0, a0, 92);
    lw(a3, a0, 20);
    a0 = s5 & 0xFFFF;
    mult(a1, v1, a0);
    a0 = sll(a1, 1);
    a0 = addu(a0, a1);
    a0 = sll(a0, 2);
    s3 = addu(a3, a0);
    a1 = addiu(v1, -5);
    a0 = sll(a1, 1);
    a0 = addu(a0, a1);
    a0 = sll(a0, 2);
    a3 = addu(s3, a0);
    a1 = addiu(v1, -2);
    a0 = sll(a1, 1);
    a0 = addu(a0, a1);
    a0 = sll(a0, 2);
    t0 = addu(s3, a0);
    a1 = 3;
    for (;;) {
        // 0x00333a40
        charge(ctx, 4);
        a0 = a1 & 0xFFFF;
        a0 = slt(a0, v1);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00333a18: shift every point one place back
        charge(ctx, 10);
        lwc1(f2, a3, 0);
        lwc1(f1, a3, 4);
        lwc1(f0, a3, 8);
        swc1(f2, t0, 0);
        swc1(f1, t0, 4);
        swc1(f0, t0, 8);
        a3 = addiu(a3, -36);
        t0 = addiu(t0, -36);
        a0 = addiu(a1, 3);
        a1 = a0 & 0xFFFF;
    }
    // 0x00333a50: the new head point; the pushed count grows up to the ribbon length
    charge(ctx, 19);
    lwc1(f2, a2, 0);
    lwc1(f1, a2, 4);
    lwc1(f0, a2, 8);
    swc1(f2, s3, 12);
    swc1(f1, s3, 16);
    swc1(f0, s3, 20);
    a0 = 3;
    div(v1, a0);
    mflo(v1);
    v1 = addiu(v1, -1);
    s0 = v1 & 0xFFFF;
    v1 = s5 & 0xFFFF;
    a0 = sll(v1, 1);
    lw(v1, s4, kStLengths);
    a0 = addu(v1, a0);
    lhu(a1, a0, 0);
    at = slt(s0, a1);
    if (at == 0) {
        // 0x00333a9c: two or more points: rebuild the band from the camera direction (VU0)
        charge(ctx, 3);
        v1 = addiu(a1, 1);
        a1 = v1 & 0xFFFF;
        sh(v1, a0, 0);
    }
    // 0x00333aa8
    charge(ctx, 11);
    s2 = s3;
    mtc1(zero, f21);
    v1 = addiu(sp, 0xB0);
    sqc2(vf0, v1, 0);
    v1 = addiu(sp, 0xA0);
    sqc2(vf0, v1, 0);
    s1 = 0;
    v1 = a1 & 0xFFFF;
    at = slti(v1, 2);
    if (at == 0) {
        // 0x00333ad4
        charge(ctx, 2);
        if (i64(a1) < 0) {
            // 0x00333af0
            charge(ctx, 7);
            v1 = srl(a1, 1);
            v0 = a1 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x00333adc
            charge(ctx, 5);
            mtc1(a1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x00333b0c
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x00333b28
            charge(ctx, 7);
            v1 = srl(s0, 1);
            v0 = s0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00333b14
            charge(ctx, 5);
            mtc1(s0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x00333b44
        charge(ctx, 8);
        div_s(f23, f1, f0);
        if (i64(a1) < 0) {
            // 0x00333b78
            charge(ctx, 7);
            v1 = srl(a1, 1);
            v0 = a1 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00333b64
            charge(ctx, 5);
            mtc1(a1, f0);
            cvt_s_w(f0, f0);
        }
        // 0x00333b94
        charge(ctx, 95);
        div_s(f22, f23, f0);
        mul_s(f21, f24, f23);
        v0 = addiu(a1, -1);
        s6 = v0 & 0xFFFF;
        v0 = 0x6A0000;
        v0 = addiu(v0, -15168);  // &0x69C4C0
        lqc2(vf10, v0, 0);  // 0x69C4C0
        vmove(0xF, vf24, vf10);  // vmove.xyzw
        lqc2(vf11, s4, 0);
        vmul(0xE, vf2, vf10, vf11);  // vmul.xyz
        vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
        vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
        qmfc2(v0, vf2, false);  // qmfc2
        mtc1(v0, f1);
        lwc1(f0, gp, -32496);  // 0x7CAE00
        mul_s(f20, f0, f1);
        lwc1(f0, s3, 12);
        v0 = 0x6A0000;
        swc1(f0, v0, -15152);  // 0x69C4D0
        lwc1(f0, s3, 16);
        v0 = 0x6A0000;
        swc1(f0, v0, -15148);  // 0x69C4D4
        lwc1(f0, s3, 20);
        v0 = 0x6A0000;
        swc1(f0, v0, -15144);  // 0x69C4D8
        v1 = 0x6A0000;
        v1 = addiu(v1, -15152);  // &0x69C4D0
        lqc2(vf12, v1, 0);  // 0x69C4D0
        lwc1(f0, s3, 48);
        v0 = 0x6A0000;
        swc1(f0, v0, -15152);  // 0x69C4D0
        lwc1(f0, s3, 52);
        v0 = 0x6A0000;
        swc1(f0, v0, -15148);  // 0x69C4D4
        lwc1(f0, s3, 56);
        v0 = 0x6A0000;
        swc1(f0, v0, -15144);  // 0x69C4D8
        lqc2(vf10, v1, 0);  // 0x69C4D0
        vsub(0xF, vf10, vf10, vf12);  // vsub.xyzw
        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
        vwaitq(ctx);
        vmulq(0xE, vf10, vf10);  // vmulq.xyz
        v0 = addiu(sp, 0xB0);
        sqc2(vf10, v0, 0);
        mov_s(f12, f20);
        jal(ctx, 0x333C60u, gen::fn_sub_329890_00329890);
        vmove(0xF, vf10, vf24);  // vmove.xyzw
        vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
        vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
        vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
        v1 = addiu(sp, 0xA0);
        sqc2(vf10, v1, 0);
        mov_s(f0, f21);
        mfc1(v1, f0);
        qmtc2(v1, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vadd(0xF, vf12, vf12, vf10);  // vadd.xyzw
        a0 = 0x6A0000;
        a0 = addiu(a0, -15152);  // &0x69C4D0
        sqc2(vf12, a0, 0);  // 0x69C4D0
        v1 = 0x6A0000;
        lwc1(f0, v1, -15152);  // 0x69C4D0
        swc1(f0, s3, 0);
        v1 = 0x6A0000;
        lwc1(f0, v1, -15148);  // 0x69C4D4
        swc1(f0, s3, 4);
        v1 = 0x6A0000;
        lwc1(f0, v1, -15144);  // 0x69C4D8
        swc1(f0, s3, 8);
        vsub(0xF, vf12, vf12, vf10);  // vsub.xyzw
        vsub(0xF, vf12, vf12, vf10);  // vsub.xyzw
        sqc2(vf12, a0, 0);  // 0x69C4D0
        v1 = 0x6A0000;
        lwc1(f0, v1, -15152);  // 0x69C4D0
        swc1(f0, s3, 24);
        v1 = 0x6A0000;
        lwc1(f0, v1, -15148);  // 0x69C4D4
        swc1(f0, s3, 28);
        v1 = 0x6A0000;
        lwc1(f0, v1, -15144);  // 0x69C4D8
        swc1(f0, s3, 32);
        sub_s(f23, f23, f22);
        s3 = addiu(s3, 36);
        v1 = addiu(s1, 1);
        s1 = v1 & 0xFFFF;
        for (;;) {
            // 0x00333e2c
            charge(ctx, 5);
            a0 = s1 & 0xFFFF;
            v1 = s6 & 0xFFFF;
            v1 = slt(a0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00333d10: each further point: side vector (sub_329890), the two outer vertices
            charge(ctx, 71);
            lwc1(f0, s3, 12);
            v0 = 0x6A0000;
            swc1(f0, v0, -15152);  // 0x69C4D0
            lwc1(f0, s3, 16);
            v0 = 0x6A0000;
            swc1(f0, v0, -15148);  // 0x69C4D4
            lwc1(f0, s3, 20);
            v0 = 0x6A0000;
            swc1(f0, v0, -15144);  // 0x69C4D8
            v1 = 0x6A0000;
            v1 = addiu(v1, -15152);  // &0x69C4D0
            lqc2(vf12, v1, 0);  // 0x69C4D0
            lwc1(f0, s3, 48);
            v0 = 0x6A0000;
            swc1(f0, v0, -15152);  // 0x69C4D0
            lwc1(f0, s3, 52);
            v0 = 0x6A0000;
            swc1(f0, v0, -15148);  // 0x69C4D4
            lwc1(f0, s3, 56);
            v0 = 0x6A0000;
            swc1(f0, v0, -15144);  // 0x69C4D8
            lqc2(vf10, v1, 0);  // 0x69C4D0
            vsub(0xF, vf10, vf10, vf12);  // vsub.xyzw
            vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
            vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
            vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
            vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
            vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
            vwaitq(ctx);
            vmulq(0xE, vf10, vf10);  // vmulq.xyz
            mov_s(f12, f20);
            jal(ctx, 0x333D8Cu, gen::fn_sub_329890_00329890);
            vmove(0xF, vf10, vf24);  // vmove.xyzw
            vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
            vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
            vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
            mul_s(f0, f24, f23);
            mfc1(v1, f0);
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf12, vf12, vf10);  // vadd.xyzw
            a0 = 0x6A0000;
            a0 = addiu(a0, -15152);  // &0x69C4D0
            sqc2(vf12, a0, 0);  // 0x69C4D0
            v1 = 0x6A0000;
            lwc1(f0, v1, -15152);  // 0x69C4D0
            swc1(f0, s3, 0);
            v1 = 0x6A0000;
            lwc1(f0, v1, -15148);  // 0x69C4D4
            swc1(f0, s3, 4);
            v1 = 0x6A0000;
            lwc1(f0, v1, -15144);  // 0x69C4D8
            swc1(f0, s3, 8);
            vsub(0xF, vf12, vf12, vf10);  // vsub.xyzw
            vsub(0xF, vf12, vf12, vf10);  // vsub.xyzw
            sqc2(vf12, a0, 0);  // 0x69C4D0
            v1 = 0x6A0000;
            lwc1(f0, v1, -15152);  // 0x69C4D0
            swc1(f0, s3, 24);
            v1 = 0x6A0000;
            lwc1(f0, v1, -15148);  // 0x69C4D4
            swc1(f0, s3, 28);
            v1 = 0x6A0000;
            lwc1(f0, v1, -15144);  // 0x69C4D8
            swc1(f0, s3, 32);
            sub_s(f23, f23, f22);
            s3 = addiu(s3, 36);
            v1 = addiu(s1, 1);
            s1 = v1 & 0xFFFF;
        }
    }
    // 0x00333e40: the tail point
    charge(ctx, 16);
    lwc1(f2, s3, 12);
    lwc1(f1, s3, 16);
    lwc1(f0, s3, 20);
    swc1(f2, s3, 0);
    swc1(f1, s3, 4);
    swc1(f0, s3, 8);
    lwc1(f2, s3, 12);
    lwc1(f1, s3, 16);
    lwc1(f0, s3, 20);
    swc1(f2, s3, 24);
    swc1(f1, s3, 28);
    swc1(f0, s3, 32);
    a1 = addiu(s3, 36);
    a0 = s0 & 0xFFFF;
    for (;;) {
        // 0x00333ed4
        charge(ctx, 4);
        v1 = s1 & 0xFFFF;
        v1 = slt(v1, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00333e80: the points not pushed yet collapse onto the tail
        charge(ctx, 21);
        lwc1(f2, s3, 0);
        lwc1(f1, s3, 4);
        lwc1(f0, s3, 8);
        swc1(f2, a1, 0);
        swc1(f1, a1, 4);
        swc1(f0, a1, 8);
        lwc1(f2, s3, 12);
        lwc1(f1, s3, 16);
        lwc1(f0, s3, 20);
        swc1(f2, a1, 12);
        swc1(f1, a1, 16);
        swc1(f0, a1, 20);
        lwc1(f2, s3, 24);
        lwc1(f1, s3, 28);
        lwc1(f0, s3, 32);
        swc1(f2, a1, 24);
        swc1(f1, a1, 28);
        swc1(f0, a1, 32);
        a1 = addiu(a1, 36);
        v1 = addiu(s1, 1);
        s1 = v1 & 0xFFFF;
    }
    // 0x00333ee4
    charge(ctx, 181);
    lw(v1, s4, kStMeshB);
    lhu(a0, v1, 8);
    lw(v1, v1, 16);
    lw(v1, v1, 24);
    lw(v1, v1, 92);
    lw(a1, v1, 20);
    v1 = s5 & 0xFFFF;
    mult(a0, a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(a1, v1);
    lwc1(f2, s2, 12);
    lwc1(f1, s2, 16);
    lwc1(f0, s2, 20);
    swc1(f2, v1, 0);
    swc1(f1, v1, 4);
    swc1(f0, v1, 8);
    lwc1(f2, s2, 0);
    lwc1(f1, s2, 4);
    lwc1(f0, s2, 8);
    swc1(f2, v1, 12);
    swc1(f1, v1, 16);
    swc1(f0, v1, 20);
    lwc1(f2, s2, 24);
    lwc1(f1, s2, 28);
    lwc1(f0, s2, 32);
    swc1(f2, v1, 84);
    swc1(f1, v1, 88);
    swc1(f0, v1, 92);
    a0 = addiu(sp, 0xB0);
    lqc2(vf11, a0, 0);
    vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
    a0 = 0x40000000;
    mtc1(a0, f0);
    mul_s(f0, f0, f21);
    mfc1(a0, f0);
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
    lwc1(f0, s2, 12);
    a0 = 0x6A0000;
    swc1(f0, a0, -15152);  // 0x69C4D0
    lwc1(f0, s2, 16);
    a0 = 0x6A0000;
    swc1(f0, a0, -15148);  // 0x69C4D4
    lwc1(f0, s2, 20);
    a0 = 0x6A0000;
    swc1(f0, a0, -15144);  // 0x69C4D8
    a2 = 0x6A0000;
    a2 = addiu(a2, -15152);  // &0x69C4D0
    lqc2(vf12, a2, 0);  // 0x69C4D0
    a1 = addiu(sp, 0xA0);
    lqc2(vf10, a1, 0);
    lwc1(f0, gp, -32364);  // 0x7CAE84
    mul_s(f4, f0, f21);
    mfc1(a0, f4);
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    lwc1(f3, gp, -32360);  // 0x7CAE88
    mfc1(a0, f3);
    qmtc2(a0, vf2, false);  // qmtc2
    vsub_bc(0x1, vf3, vf0, vf2, 0);  // vsubx.w
    vmula_bc(0xF, vf11, vf2, 0);  // vmulax.xyzw
    vmadd_bc(0xF, vf10, vf10, vf3, 3);  // vmaddw.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    sqc2(vf10, a2, 0);  // 0x69C4D0
    a0 = 0x6A0000;
    lwc1(f0, a0, -15152);  // 0x69C4D0
    swc1(f0, v1, 24);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15148);  // 0x69C4D4
    swc1(f0, v1, 28);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15144);  // 0x69C4D8
    swc1(f0, v1, 32);
    lqc2(vf10, a1, 0);
    lwc1(f0, gp, -32356);  // 0x7CAE8C
    mul_s(f2, f0, f21);
    mfc1(a0, f2);
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    lwc1(f1, gp, -32676);  // 0x7CAD4C
    mfc1(a0, f1);
    qmtc2(a0, vf2, false);  // qmtc2
    vsub_bc(0x1, vf3, vf0, vf2, 0);  // vsubx.w
    vmula_bc(0xF, vf11, vf2, 0);  // vmulax.xyzw
    vmadd_bc(0xF, vf10, vf10, vf3, 3);  // vmaddw.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    sqc2(vf10, a2, 0);  // 0x69C4D0
    a0 = 0x6A0000;
    lwc1(f0, a0, -15152);  // 0x69C4D0
    swc1(f0, v1, 36);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15148);  // 0x69C4D4
    swc1(f0, v1, 40);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15144);  // 0x69C4D8
    swc1(f0, v1, 44);
    lqc2(vf10, a1, 0);
    mfc1(a0, f4);
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
    mfc1(a0, f3);
    qmtc2(a0, vf2, false);  // qmtc2
    vsub_bc(0x1, vf3, vf0, vf2, 0);  // vsubx.w
    vmula_bc(0xF, vf11, vf2, 0);  // vmulax.xyzw
    vmadd_bc(0xF, vf10, vf10, vf3, 3);  // vmaddw.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    sqc2(vf10, a2, 0);  // 0x69C4D0
    a0 = 0x6A0000;
    lwc1(f0, a0, -15152);  // 0x69C4D0
    swc1(f0, v1, 72);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15148);  // 0x69C4D4
    swc1(f0, v1, 76);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15144);  // 0x69C4D8
    swc1(f0, v1, 80);
    lqc2(vf10, a1, 0);
    mfc1(a0, f2);
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
    mfc1(a0, f1);
    qmtc2(a0, vf2, false);  // qmtc2
    vsub_bc(0x1, vf3, vf0, vf2, 0);  // vsubx.w
    vmula_bc(0xF, vf11, vf2, 0);  // vmulax.xyzw
    vmadd_bc(0xF, vf10, vf10, vf3, 3);  // vmaddw.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    sqc2(vf10, a2, 0);  // 0x69C4D0
    a0 = 0x6A0000;
    lwc1(f0, a0, -15152);  // 0x69C4D0
    swc1(f0, v1, 60);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15148);  // 0x69C4D4
    swc1(f0, v1, 64);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15144);  // 0x69C4D8
    swc1(f0, v1, 68);
    lw(a0, gp, -32604);  // 0x7CAD94
    qmtc2(a0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
    vadd(0xF, vf11, vf11, vf12);  // vadd.xyzw
    sqc2(vf11, a2, 0);  // 0x69C4D0
    a0 = 0x6A0000;
    lwc1(f0, a0, -15152);  // 0x69C4D0
    swc1(f0, v1, 48);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15148);  // 0x69C4D4
    swc1(f0, v1, 52);
    a0 = 0x6A0000;
    lwc1(f0, a0, -15144);  // 0x69C4D8
    swc1(f0, v1, 56);
    ld(ra, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x003341C0 sub_3341C0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Locks the ribbon meshes for a frame [fxStripsLock] ($a0 = the ribbon meshes): the camera position into a stack
// vector (sub_329740 [fxCameraPos]), then geometryLock(vertices | prelight = 10) on the band and the grid geometry.
void sub_3341C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003341c0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x3341D0u, gen::fn_sub_329740_00329740);
    lw(v0, s0, kStMeshA);
    lw(v0, v0, 16);
    lw(a0, v0, 24);
    a1 = 10;
    jal(ctx, 0x3341E8u, gen::fn_geometryLock_00493370);
    lw(v0, s0, kStMeshB);
    lw(v0, v0, 16);
    lw(a0, v0, 24);
    a1 = 10;
    jal(ctx, 0x334200u, gen::fn_geometryLock_00493370);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00334220 sub_334220 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Unlocks the ribbon meshes [fxStripsUnlock] ($a0 = the ribbon meshes): RpGeometryUnlock (sub_4933D0) on the grid and
// the band geometry, each followed by lockedSinceLastInst |= 1 when the mesh has flag 4.
void sub_334220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00334220
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s2, a0, 20);
    lw(v0, s2, 16);
    lw(s1, v0, 24);
    a0 = s1;
    jal(ctx, 0x334248u, gen::fn_sub_4933D0_004933d0);
    lhu(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00334260
        charge(ctx, 3);
        lhu(v0, s1, 12);
        v0 = v0 | 0x1;
        sh(v0, s1, 12);
    }
    // 0x0033426c
    charge(ctx, 10);
    lw(s1, s0, kStMeshA);
    lw(v0, s1, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33427Cu, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s1, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00334294
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x003342a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
