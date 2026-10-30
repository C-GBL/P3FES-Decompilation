// Pair tests for slice fx2 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log.
// On top of the random worlds: every update / draw that runs on the replay routes, on the instance it was running on in
// the fx2_* snapshots (battle and fusion routes, made for this slice at the vblanks where the band's effects are
// alive), with stand-ins for the RenderWare / layer-manager callees this library does not emit; and documented-rule
// checks (the particle-system layout, the scale slots, class 13's dispatch, the instance allocators, the ribbon colour
// alpha rule, the full-screen filters, the texture reference count, the filter update slots, the filter quad builder).
#include "handgen_pairs.h"

#include "p3fes/game/fx2.h"
#include "stand_ins.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_330100_00330100(EEContext&);  // generated body
void fn_sub_330100_00330100__recomp(EEContext&);  // recompiled
void fn_sub_330190_00330190(EEContext&);  // generated body
void fn_sub_330190_00330190__recomp(EEContext&);  // recompiled
void fn_sub_330BB0_00330bb0(EEContext&);  // generated body
void fn_sub_330BB0_00330bb0__recomp(EEContext&);  // recompiled
void fn_sub_330C40_00330c40(EEContext&);  // generated body
void fn_sub_330C40_00330c40__recomp(EEContext&);  // recompiled
void fn_sub_3315D0_003315d0(EEContext&);  // generated body
void fn_sub_3315D0_003315d0__recomp(EEContext&);  // recompiled
void fn_sub_331FD0_00331fd0(EEContext&);  // generated body
void fn_sub_331FD0_00331fd0__recomp(EEContext&);  // recompiled
void fn_sub_332070_00332070(EEContext&);  // generated body
void fn_sub_332070_00332070__recomp(EEContext&);  // recompiled
void fn_sub_332370_00332370(EEContext&);  // generated body
void fn_sub_332370_00332370__recomp(EEContext&);  // recompiled
void fn_sub_332470_00332470(EEContext&);  // generated body
void fn_sub_332470_00332470__recomp(EEContext&);  // recompiled
void fn_sub_3325D0_003325d0(EEContext&);  // generated body
void fn_sub_3325D0_003325d0__recomp(EEContext&);  // recompiled
void fn_sub_332700_00332700(EEContext&);  // generated body
void fn_sub_332700_00332700__recomp(EEContext&);  // recompiled
void fn_sub_332780_00332780(EEContext&);  // generated body
void fn_sub_332780_00332780__recomp(EEContext&);  // recompiled
void fn_sub_332880_00332880(EEContext&);  // generated body
void fn_sub_332880_00332880__recomp(EEContext&);  // recompiled
void fn_sub_332990_00332990(EEContext&);  // generated body
void fn_sub_332990_00332990__recomp(EEContext&);  // recompiled
void fn_sub_332A30_00332a30(EEContext&);  // generated body
void fn_sub_332A30_00332a30__recomp(EEContext&);  // recompiled
void fn_sub_332AC0_00332ac0(EEContext&);  // generated body
void fn_sub_332AC0_00332ac0__recomp(EEContext&);  // recompiled
void fn_sub_332B60_00332b60(EEContext&);  // generated body
void fn_sub_332B60_00332b60__recomp(EEContext&);  // recompiled
void fn_sub_332E10_00332e10(EEContext&);  // generated body
void fn_sub_332E10_00332e10__recomp(EEContext&);  // recompiled
void fn_sub_332F10_00332f10(EEContext&);  // generated body
void fn_sub_332F10_00332f10__recomp(EEContext&);  // recompiled
void fn_sub_3330E0_003330e0(EEContext&);  // generated body
void fn_sub_3330E0_003330e0__recomp(EEContext&);  // recompiled
void fn_sub_333300_00333300(EEContext&);  // generated body
void fn_sub_333300_00333300__recomp(EEContext&);  // recompiled
void fn_sub_333420_00333420(EEContext&);  // generated body
void fn_sub_333420_00333420__recomp(EEContext&);  // recompiled
void fn_sub_333970_00333970(EEContext&);  // generated body
void fn_sub_333970_00333970__recomp(EEContext&);  // recompiled
void fn_sub_3341C0_003341c0(EEContext&);  // generated body
void fn_sub_3341C0_003341c0__recomp(EEContext&);  // recompiled
void fn_sub_334220_00334220(EEContext&);  // generated body
void fn_sub_334220_00334220__recomp(EEContext&);  // recompiled
void fn_sub_337A60_00337a60(EEContext&);  // generated body
void fn_sub_337A60_00337a60__recomp(EEContext&);  // recompiled
void fn_sub_337B70_00337b70(EEContext&);  // generated body
void fn_sub_337B70_00337b70__recomp(EEContext&);  // recompiled
void fn_sub_337BB0_00337bb0(EEContext&);  // generated body
void fn_sub_337BB0_00337bb0__recomp(EEContext&);  // recompiled
void fn_sub_337C10_00337c10(EEContext&);  // generated body
void fn_sub_337C10_00337c10__recomp(EEContext&);  // recompiled
void fn_sub_337C40_00337c40(EEContext&);  // generated body
void fn_sub_337C40_00337c40__recomp(EEContext&);  // recompiled
void fn_sub_337C90_00337c90(EEContext&);  // generated body
void fn_sub_337C90_00337c90__recomp(EEContext&);  // recompiled
void fn_sub_337CF0_00337cf0(EEContext&);  // generated body
void fn_sub_337CF0_00337cf0__recomp(EEContext&);  // recompiled
void fn_sub_337D40_00337d40(EEContext&);  // generated body
void fn_sub_337D40_00337d40__recomp(EEContext&);  // recompiled
void fn_sub_337DD0_00337dd0(EEContext&);  // generated body
void fn_sub_337DD0_00337dd0__recomp(EEContext&);  // recompiled
void fn_sub_337DE0_00337de0(EEContext&);  // generated body
void fn_sub_337DE0_00337de0__recomp(EEContext&);  // recompiled
void fn_sub_337DF0_00337df0(EEContext&);  // generated body
void fn_sub_337DF0_00337df0__recomp(EEContext&);  // recompiled
void fn_sub_337E00_00337e00(EEContext&);  // generated body
void fn_sub_337E00_00337e00__recomp(EEContext&);  // recompiled
void fn_sub_337E90_00337e90(EEContext&);  // generated body
void fn_sub_337E90_00337e90__recomp(EEContext&);  // recompiled
void fn_sub_337FD0_00337fd0(EEContext&);  // generated body
void fn_sub_337FD0_00337fd0__recomp(EEContext&);  // recompiled
void fn_sub_338360_00338360(EEContext&);  // generated body
void fn_sub_338360_00338360__recomp(EEContext&);  // recompiled
void fn_sub_338EA0_00338ea0(EEContext&);  // generated body
void fn_sub_338EA0_00338ea0__recomp(EEContext&);  // recompiled
void fn_sub_339200_00339200(EEContext&);  // generated body
void fn_sub_339200_00339200__recomp(EEContext&);  // recompiled
void fn_sub_3393D0_003393d0(EEContext&);  // generated body
void fn_sub_3393D0_003393d0__recomp(EEContext&);  // recompiled
void fn_sub_3397D0_003397d0(EEContext&);  // generated body
void fn_sub_3397D0_003397d0__recomp(EEContext&);  // recompiled
void fn_sub_3398C0_003398c0(EEContext&);  // generated body
void fn_sub_3398C0_003398c0__recomp(EEContext&);  // recompiled
void fn_sub_3399A0_003399a0(EEContext&);  // generated body
void fn_sub_3399A0_003399a0__recomp(EEContext&);  // recompiled
void fn_sub_33A220_0033a220(EEContext&);  // generated body
void fn_sub_33A220_0033a220__recomp(EEContext&);  // recompiled
void fn_sub_33A3E0_0033a3e0(EEContext&);  // generated body
void fn_sub_33A3E0_0033a3e0__recomp(EEContext&);  // recompiled
void fn_sub_33A4D0_0033a4d0(EEContext&);  // generated body
void fn_sub_33A4D0_0033a4d0__recomp(EEContext&);  // recompiled
void fn_sub_33A560_0033a560(EEContext&);  // generated body
void fn_sub_33A560_0033a560__recomp(EEContext&);  // recompiled
void fn_sub_33A5B0_0033a5b0(EEContext&);  // generated body
void fn_sub_33A5B0_0033a5b0__recomp(EEContext&);  // recompiled
void fn_sub_33AF10_0033af10(EEContext&);  // generated body
void fn_sub_33AF10_0033af10__recomp(EEContext&);  // recompiled
void fn_sub_33BDA0_0033bda0(EEContext&);  // generated body
void fn_sub_33BDA0_0033bda0__recomp(EEContext&);  // recompiled
void fn_sub_33BE90_0033be90(EEContext&);  // generated body
void fn_sub_33BE90_0033be90__recomp(EEContext&);  // recompiled
void fn_sub_33BFA0_0033bfa0(EEContext&);  // generated body
void fn_sub_33BFA0_0033bfa0__recomp(EEContext&);  // recompiled
void fn_sub_33C0A0_0033c0a0(EEContext&);  // generated body
void fn_sub_33C0A0_0033c0a0__recomp(EEContext&);  // recompiled
void fn_sub_33C150_0033c150(EEContext&);  // generated body
void fn_sub_33C150_0033c150__recomp(EEContext&);  // recompiled
void fn_sub_33C1A0_0033c1a0(EEContext&);  // generated body
void fn_sub_33C1A0_0033c1a0__recomp(EEContext&);  // recompiled
void fn_sub_33C960_0033c960(EEContext&);  // generated body
void fn_sub_33C960_0033c960__recomp(EEContext&);  // recompiled
void fn_sub_33CB20_0033cb20(EEContext&);  // generated body
void fn_sub_33CB20_0033cb20__recomp(EEContext&);  // recompiled
void fn_sub_33CC10_0033cc10(EEContext&);  // generated body
void fn_sub_33CC10_0033cc10__recomp(EEContext&);  // recompiled
void fn_sub_33CD20_0033cd20(EEContext&);  // generated body
void fn_sub_33CD20_0033cd20__recomp(EEContext&);  // recompiled
void fn_sub_33CE10_0033ce10(EEContext&);  // generated body
void fn_sub_33CE10_0033ce10__recomp(EEContext&);  // recompiled
void fn_sub_33CEB0_0033ceb0(EEContext&);  // generated body
void fn_sub_33CEB0_0033ceb0__recomp(EEContext&);  // recompiled
void fn_sub_33CF00_0033cf00(EEContext&);  // generated body
void fn_sub_33CF00_0033cf00__recomp(EEContext&);  // recompiled
void fn_sub_33D6D0_0033d6d0(EEContext&);  // generated body
void fn_sub_33D6D0_0033d6d0__recomp(EEContext&);  // recompiled
void fn_sub_33D890_0033d890(EEContext&);  // generated body
void fn_sub_33D890_0033d890__recomp(EEContext&);  // recompiled
void fn_sub_33D980_0033d980(EEContext&);  // generated body
void fn_sub_33D980_0033d980__recomp(EEContext&);  // recompiled
void fn_sub_33DA90_0033da90(EEContext&);  // generated body
void fn_sub_33DA90_0033da90__recomp(EEContext&);  // recompiled
void fn_sub_33DB80_0033db80(EEContext&);  // generated body
void fn_sub_33DB80_0033db80__recomp(EEContext&);  // recompiled
void fn_sub_33DC20_0033dc20(EEContext&);  // generated body
void fn_sub_33DC20_0033dc20__recomp(EEContext&);  // recompiled
void fn_sub_33DC70_0033dc70(EEContext&);  // generated body
void fn_sub_33DC70_0033dc70__recomp(EEContext&);  // recompiled
void fn_sub_33E540_0033e540(EEContext&);  // generated body
void fn_sub_33E540_0033e540__recomp(EEContext&);  // recompiled
void fn_sub_33F4A0_0033f4a0(EEContext&);  // generated body
void fn_sub_33F4A0_0033f4a0__recomp(EEContext&);  // recompiled
void fn_sub_33F590_0033f590(EEContext&);  // generated body
void fn_sub_33F590_0033f590__recomp(EEContext&);  // recompiled
void fn_sub_33F6A0_0033f6a0(EEContext&);  // generated body
void fn_sub_33F6A0_0033f6a0__recomp(EEContext&);  // recompiled
void fn_sub_33F780_0033f780(EEContext&);  // generated body
void fn_sub_33F780_0033f780__recomp(EEContext&);  // recompiled
void fn_sub_33F810_0033f810(EEContext&);  // generated body
void fn_sub_33F810_0033f810__recomp(EEContext&);  // recompiled
void fn_sub_33F860_0033f860(EEContext&);  // generated body
void fn_sub_33F860_0033f860__recomp(EEContext&);  // recompiled
void fn_sub_340100_00340100(EEContext&);  // generated body
void fn_sub_340100_00340100__recomp(EEContext&);  // recompiled
void fn_sub_341F10_00341f10(EEContext&);  // generated body
void fn_sub_341F10_00341f10__recomp(EEContext&);  // recompiled
void fn_sub_342480_00342480(EEContext&);  // generated body
void fn_sub_342480_00342480__recomp(EEContext&);  // recompiled
void fn_sub_342550_00342550(EEContext&);  // generated body
void fn_sub_342550_00342550__recomp(EEContext&);  // recompiled
void fn_sub_342990_00342990(EEContext&);  // generated body
void fn_sub_342990_00342990__recomp(EEContext&);  // recompiled
void fn_sub_342A90_00342a90(EEContext&);  // generated body
void fn_sub_342A90_00342a90__recomp(EEContext&);  // recompiled
void fn_sub_343410_00343410(EEContext&);  // generated body
void fn_sub_343410_00343410__recomp(EEContext&);  // recompiled
void fn_sub_343790_00343790(EEContext&);  // generated body
void fn_sub_343790_00343790__recomp(EEContext&);  // recompiled
void fn_sub_343860_00343860(EEContext&);  // generated body
void fn_sub_343860_00343860__recomp(EEContext&);  // recompiled
void fn_sub_343C60_00343c60(EEContext&);  // generated body
void fn_sub_343C60_00343c60__recomp(EEContext&);  // recompiled
void fn_sub_343D10_00343d10(EEContext&);  // generated body
void fn_sub_343D10_00343d10__recomp(EEContext&);  // recompiled
void fn_sub_343D60_00343d60(EEContext&);  // generated body
void fn_sub_343D60_00343d60__recomp(EEContext&);  // recompiled
void fn_sub_344720_00344720(EEContext&);  // generated body
void fn_sub_344720_00344720__recomp(EEContext&);  // recompiled
void fn_sub_345CF0_00345cf0(EEContext&);  // generated body
void fn_sub_345CF0_00345cf0__recomp(EEContext&);  // recompiled
void fn_sub_3461A0_003461a0(EEContext&);  // generated body
void fn_sub_3461A0_003461a0__recomp(EEContext&);  // recompiled
void fn_sub_346350_00346350(EEContext&);  // generated body
void fn_sub_346350_00346350__recomp(EEContext&);  // recompiled
void fn_sub_3463C0_003463c0(EEContext&);  // generated body
void fn_sub_3463C0_003463c0__recomp(EEContext&);  // recompiled
void fn_sub_346460_00346460(EEContext&);  // generated body
void fn_sub_346460_00346460__recomp(EEContext&);  // recompiled
void fn_sub_346530_00346530(EEContext&);  // generated body
void fn_sub_346530_00346530__recomp(EEContext&);  // recompiled
void fn_sub_347100_00347100(EEContext&);  // generated body
void fn_sub_347100_00347100__recomp(EEContext&);  // recompiled
void fn_sub_347170_00347170(EEContext&);  // generated body
void fn_sub_347170_00347170__recomp(EEContext&);  // recompiled
void fn_sub_3472D0_003472d0(EEContext&);  // generated body
void fn_sub_3472D0_003472d0__recomp(EEContext&);  // recompiled
void fn_sub_347350_00347350(EEContext&);  // generated body
void fn_sub_347350_00347350__recomp(EEContext&);  // recompiled
void fn_sub_3473B0_003473b0(EEContext&);  // generated body
void fn_sub_3473B0_003473b0__recomp(EEContext&);  // recompiled
void fn_sub_347CB0_00347cb0(EEContext&);  // generated body
void fn_sub_347CB0_00347cb0__recomp(EEContext&);  // recompiled
void fn_sub_347FC0_00347fc0(EEContext&);  // generated body
void fn_sub_347FC0_00347fc0__recomp(EEContext&);  // recompiled
void fn_sub_348030_00348030(EEContext&);  // generated body
void fn_sub_348030_00348030__recomp(EEContext&);  // recompiled
void fn_sub_348090_00348090(EEContext&);  // generated body
void fn_sub_348090_00348090__recomp(EEContext&);  // recompiled
void fn_sub_348340_00348340(EEContext&);  // generated body
void fn_sub_348340_00348340__recomp(EEContext&);  // recompiled
void fn_sub_348760_00348760(EEContext&);  // generated body
void fn_sub_348760_00348760__recomp(EEContext&);  // recompiled
void fn_sub_348BD0_00348bd0(EEContext&);  // generated body
void fn_sub_348BD0_00348bd0__recomp(EEContext&);  // recompiled
void fn_sub_348F30_00348f30(EEContext&);  // generated body
void fn_sub_348F30_00348f30__recomp(EEContext&);  // recompiled
void fn_sub_349260_00349260(EEContext&);  // generated body
void fn_sub_349260_00349260__recomp(EEContext&);  // recompiled
void fn_sub_349450_00349450(EEContext&);  // generated body
void fn_sub_349450_00349450__recomp(EEContext&);  // recompiled
void fn_sub_349870_00349870(EEContext&);  // generated body
void fn_sub_349870_00349870__recomp(EEContext&);  // recompiled
void fn_sub_349AF0_00349af0(EEContext&);  // generated body
void fn_sub_349AF0_00349af0__recomp(EEContext&);  // recompiled
void fn_sub_349ED0_00349ed0(EEContext&);  // generated body
void fn_sub_349ED0_00349ed0__recomp(EEContext&);  // recompiled
void fn_sub_349FA0_00349fa0(EEContext&);  // generated body
void fn_sub_349FA0_00349fa0__recomp(EEContext&);  // recompiled
void fn_sub_34A1D0_0034a1d0(EEContext&);  // generated body
void fn_sub_34A1D0_0034a1d0__recomp(EEContext&);  // recompiled
void fn_sub_34A280_0034a280(EEContext&);  // generated body
void fn_sub_34A280_0034a280__recomp(EEContext&);  // recompiled
void fn_sub_34A340_0034a340(EEContext&);  // generated body
void fn_sub_34A340_0034a340__recomp(EEContext&);  // recompiled
void fn_sub_34A590_0034a590(EEContext&);  // generated body
void fn_sub_34A590_0034a590__recomp(EEContext&);  // recompiled
void fn_sub_34A8C0_0034a8c0(EEContext&);  // generated body
void fn_sub_34A8C0_0034a8c0__recomp(EEContext&);  // recompiled
void fn_sub_34A990_0034a990(EEContext&);  // generated body
void fn_sub_34A990_0034a990__recomp(EEContext&);  // recompiled
void fn_sub_34A9C0_0034a9c0(EEContext&);  // generated body
void fn_sub_34A9C0_0034a9c0__recomp(EEContext&);  // recompiled
void fn_sub_34ABC0_0034abc0(EEContext&);  // generated body
void fn_sub_34ABC0_0034abc0__recomp(EEContext&);  // recompiled
void fn_sub_34AC70_0034ac70(EEContext&);  // generated body
void fn_sub_34AC70_0034ac70__recomp(EEContext&);  // recompiled
void fn_sub_34B1A0_0034b1a0(EEContext&);  // generated body
void fn_sub_34B1A0_0034b1a0__recomp(EEContext&);  // recompiled
void fn_sub_34B320_0034b320(EEContext&);  // generated body
void fn_sub_34B320_0034b320__recomp(EEContext&);  // recompiled
void fn_sub_34B3A0_0034b3a0(EEContext&);  // generated body
void fn_sub_34B3A0_0034b3a0__recomp(EEContext&);  // recompiled
void fn_sub_34B600_0034b600(EEContext&);  // generated body
void fn_sub_34B600_0034b600__recomp(EEContext&);  // recompiled
void fn_sub_34B6B0_0034b6b0(EEContext&);  // generated body
void fn_sub_34B6B0_0034b6b0__recomp(EEContext&);  // recompiled
void fn_sub_34B830_0034b830(EEContext&);  // generated body
void fn_sub_34B830_0034b830__recomp(EEContext&);  // recompiled
void fn_sub_34B8B0_0034b8b0(EEContext&);  // generated body
void fn_sub_34B8B0_0034b8b0__recomp(EEContext&);  // recompiled
void fn_sub_34BB10_0034bb10(EEContext&);  // generated body
void fn_sub_34BB10_0034bb10__recomp(EEContext&);  // recompiled
void fn_sub_34BBC0_0034bbc0(EEContext&);  // generated body
void fn_sub_34BBC0_0034bbc0__recomp(EEContext&);  // recompiled
void fn_sub_34BC80_0034bc80(EEContext&);  // generated body
void fn_sub_34BC80_0034bc80__recomp(EEContext&);  // recompiled
void fn_sub_34BD60_0034bd60(EEContext&);  // generated body
void fn_sub_34BD60_0034bd60__recomp(EEContext&);  // recompiled
void fn_sub_34BDF0_0034bdf0(EEContext&);  // generated body
void fn_sub_34BDF0_0034bdf0__recomp(EEContext&);  // recompiled
void fn_sub_34BEF0_0034bef0(EEContext&);  // generated body
void fn_sub_34BEF0_0034bef0__recomp(EEContext&);  // recompiled
void fn_sub_34BF10_0034bf10(EEContext&);  // generated body
void fn_sub_34BF10_0034bf10__recomp(EEContext&);  // recompiled
void fn_sub_34BFC0_0034bfc0(EEContext&);  // generated body
void fn_sub_34BFC0_0034bfc0__recomp(EEContext&);  // recompiled
void fn_sub_34C160_0034c160(EEContext&);  // generated body
void fn_sub_34C160_0034c160__recomp(EEContext&);  // recompiled
void fn_sub_34C1B0_0034c1b0(EEContext&);  // generated body
void fn_sub_34C1B0_0034c1b0__recomp(EEContext&);  // recompiled
void fn_sub_34C670_0034c670(EEContext&);  // generated body
void fn_sub_34C670_0034c670__recomp(EEContext&);  // recompiled
void fn_sub_34C890_0034c890(EEContext&);  // generated body
void fn_sub_34C890_0034c890__recomp(EEContext&);  // recompiled
void fn_sub_34C9B0_0034c9b0(EEContext&);  // generated body
void fn_sub_34C9B0_0034c9b0__recomp(EEContext&);  // recompiled
void fn_sub_34D510_0034d510(EEContext&);  // generated body
void fn_sub_34D510_0034d510__recomp(EEContext&);  // recompiled
void fn_sub_34D670_0034d670(EEContext&);  // generated body
void fn_sub_34D670_0034d670__recomp(EEContext&);  // recompiled
void fn_sub_34D6F0_0034d6f0(EEContext&);  // generated body
void fn_sub_34D6F0_0034d6f0__recomp(EEContext&);  // recompiled
void fn_sub_34D8A0_0034d8a0(EEContext&);  // generated body
void fn_sub_34D8A0_0034d8a0__recomp(EEContext&);  // recompiled
void fn_sub_34E4C0_0034e4c0(EEContext&);  // generated body
void fn_sub_34E4C0_0034e4c0__recomp(EEContext&);  // recompiled
void fn_sub_34E610_0034e610(EEContext&);  // generated body
void fn_sub_34E610_0034e610__recomp(EEContext&);  // recompiled
void fn_sub_34E690_0034e690(EEContext&);  // generated body
void fn_sub_34E690_0034e690__recomp(EEContext&);  // recompiled
void fn_sub_34E820_0034e820(EEContext&);  // generated body
void fn_sub_34E820_0034e820__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_330100", 0x330100, &recomp_gen::fn_sub_330100_00330100, &recomp_gen::fn_sub_330100_00330100__recomp},
    {"sub_330190", 0x330190, &recomp_gen::fn_sub_330190_00330190, &recomp_gen::fn_sub_330190_00330190__recomp},
    {"sub_330BB0", 0x330BB0, &recomp_gen::fn_sub_330BB0_00330bb0, &recomp_gen::fn_sub_330BB0_00330bb0__recomp},
    {"sub_330C40", 0x330C40, &recomp_gen::fn_sub_330C40_00330c40, &recomp_gen::fn_sub_330C40_00330c40__recomp},
    {"sub_3315D0", 0x3315D0, &recomp_gen::fn_sub_3315D0_003315d0, &recomp_gen::fn_sub_3315D0_003315d0__recomp},
    {"sub_331FD0", 0x331FD0, &recomp_gen::fn_sub_331FD0_00331fd0, &recomp_gen::fn_sub_331FD0_00331fd0__recomp},
    {"sub_332070", 0x332070, &recomp_gen::fn_sub_332070_00332070, &recomp_gen::fn_sub_332070_00332070__recomp},
    {"sub_332370", 0x332370, &recomp_gen::fn_sub_332370_00332370, &recomp_gen::fn_sub_332370_00332370__recomp},
    {"sub_332470", 0x332470, &recomp_gen::fn_sub_332470_00332470, &recomp_gen::fn_sub_332470_00332470__recomp},
    {"sub_3325D0", 0x3325D0, &recomp_gen::fn_sub_3325D0_003325d0, &recomp_gen::fn_sub_3325D0_003325d0__recomp},
    {"sub_332700", 0x332700, &recomp_gen::fn_sub_332700_00332700, &recomp_gen::fn_sub_332700_00332700__recomp},
    {"sub_332780", 0x332780, &recomp_gen::fn_sub_332780_00332780, &recomp_gen::fn_sub_332780_00332780__recomp},
    {"sub_332880", 0x332880, &recomp_gen::fn_sub_332880_00332880, &recomp_gen::fn_sub_332880_00332880__recomp},
    {"sub_332990", 0x332990, &recomp_gen::fn_sub_332990_00332990, &recomp_gen::fn_sub_332990_00332990__recomp},
    {"sub_332A30", 0x332A30, &recomp_gen::fn_sub_332A30_00332a30, &recomp_gen::fn_sub_332A30_00332a30__recomp},
    {"sub_332AC0", 0x332AC0, &recomp_gen::fn_sub_332AC0_00332ac0, &recomp_gen::fn_sub_332AC0_00332ac0__recomp},
    {"sub_332B60", 0x332B60, &recomp_gen::fn_sub_332B60_00332b60, &recomp_gen::fn_sub_332B60_00332b60__recomp},
    {"sub_332E10", 0x332E10, &recomp_gen::fn_sub_332E10_00332e10, &recomp_gen::fn_sub_332E10_00332e10__recomp},
    {"sub_332F10", 0x332F10, &recomp_gen::fn_sub_332F10_00332f10, &recomp_gen::fn_sub_332F10_00332f10__recomp},
    {"sub_3330E0", 0x3330E0, &recomp_gen::fn_sub_3330E0_003330e0, &recomp_gen::fn_sub_3330E0_003330e0__recomp},
    {"sub_333300", 0x333300, &recomp_gen::fn_sub_333300_00333300, &recomp_gen::fn_sub_333300_00333300__recomp},
    {"sub_333420", 0x333420, &recomp_gen::fn_sub_333420_00333420, &recomp_gen::fn_sub_333420_00333420__recomp},
    {"sub_333970", 0x333970, &recomp_gen::fn_sub_333970_00333970, &recomp_gen::fn_sub_333970_00333970__recomp},
    {"sub_3341C0", 0x3341C0, &recomp_gen::fn_sub_3341C0_003341c0, &recomp_gen::fn_sub_3341C0_003341c0__recomp},
    {"sub_334220", 0x334220, &recomp_gen::fn_sub_334220_00334220, &recomp_gen::fn_sub_334220_00334220__recomp},
    {"sub_337A60", 0x337A60, &recomp_gen::fn_sub_337A60_00337a60, &recomp_gen::fn_sub_337A60_00337a60__recomp},
    {"sub_337B70", 0x337B70, &recomp_gen::fn_sub_337B70_00337b70, &recomp_gen::fn_sub_337B70_00337b70__recomp},
    {"sub_337BB0", 0x337BB0, &recomp_gen::fn_sub_337BB0_00337bb0, &recomp_gen::fn_sub_337BB0_00337bb0__recomp},
    {"sub_337C10", 0x337C10, &recomp_gen::fn_sub_337C10_00337c10, &recomp_gen::fn_sub_337C10_00337c10__recomp},
    {"sub_337C40", 0x337C40, &recomp_gen::fn_sub_337C40_00337c40, &recomp_gen::fn_sub_337C40_00337c40__recomp},
    {"sub_337C90", 0x337C90, &recomp_gen::fn_sub_337C90_00337c90, &recomp_gen::fn_sub_337C90_00337c90__recomp},
    {"sub_337CF0", 0x337CF0, &recomp_gen::fn_sub_337CF0_00337cf0, &recomp_gen::fn_sub_337CF0_00337cf0__recomp},
    {"sub_337D40", 0x337D40, &recomp_gen::fn_sub_337D40_00337d40, &recomp_gen::fn_sub_337D40_00337d40__recomp},
    {"sub_337DD0", 0x337DD0, &recomp_gen::fn_sub_337DD0_00337dd0, &recomp_gen::fn_sub_337DD0_00337dd0__recomp},
    {"sub_337DE0", 0x337DE0, &recomp_gen::fn_sub_337DE0_00337de0, &recomp_gen::fn_sub_337DE0_00337de0__recomp},
    {"sub_337DF0", 0x337DF0, &recomp_gen::fn_sub_337DF0_00337df0, &recomp_gen::fn_sub_337DF0_00337df0__recomp},
    {"sub_337E00", 0x337E00, &recomp_gen::fn_sub_337E00_00337e00, &recomp_gen::fn_sub_337E00_00337e00__recomp},
    {"sub_337E90", 0x337E90, &recomp_gen::fn_sub_337E90_00337e90, &recomp_gen::fn_sub_337E90_00337e90__recomp},
    {"sub_337FD0", 0x337FD0, &recomp_gen::fn_sub_337FD0_00337fd0, &recomp_gen::fn_sub_337FD0_00337fd0__recomp},
    {"sub_338360", 0x338360, &recomp_gen::fn_sub_338360_00338360, &recomp_gen::fn_sub_338360_00338360__recomp},
    {"sub_338EA0", 0x338EA0, &recomp_gen::fn_sub_338EA0_00338ea0, &recomp_gen::fn_sub_338EA0_00338ea0__recomp},
    {"sub_339200", 0x339200, &recomp_gen::fn_sub_339200_00339200, &recomp_gen::fn_sub_339200_00339200__recomp},
    {"sub_3393D0", 0x3393D0, &recomp_gen::fn_sub_3393D0_003393d0, &recomp_gen::fn_sub_3393D0_003393d0__recomp},
    {"sub_3397D0", 0x3397D0, &recomp_gen::fn_sub_3397D0_003397d0, &recomp_gen::fn_sub_3397D0_003397d0__recomp},
    {"sub_3398C0", 0x3398C0, &recomp_gen::fn_sub_3398C0_003398c0, &recomp_gen::fn_sub_3398C0_003398c0__recomp},
    {"sub_3399A0", 0x3399A0, &recomp_gen::fn_sub_3399A0_003399a0, &recomp_gen::fn_sub_3399A0_003399a0__recomp},
    {"sub_33A220", 0x33A220, &recomp_gen::fn_sub_33A220_0033a220, &recomp_gen::fn_sub_33A220_0033a220__recomp},
    {"sub_33A3E0", 0x33A3E0, &recomp_gen::fn_sub_33A3E0_0033a3e0, &recomp_gen::fn_sub_33A3E0_0033a3e0__recomp},
    {"sub_33A4D0", 0x33A4D0, &recomp_gen::fn_sub_33A4D0_0033a4d0, &recomp_gen::fn_sub_33A4D0_0033a4d0__recomp},
    {"sub_33A560", 0x33A560, &recomp_gen::fn_sub_33A560_0033a560, &recomp_gen::fn_sub_33A560_0033a560__recomp},
    {"sub_33A5B0", 0x33A5B0, &recomp_gen::fn_sub_33A5B0_0033a5b0, &recomp_gen::fn_sub_33A5B0_0033a5b0__recomp},
    {"sub_33AF10", 0x33AF10, &recomp_gen::fn_sub_33AF10_0033af10, &recomp_gen::fn_sub_33AF10_0033af10__recomp},
    {"sub_33BDA0", 0x33BDA0, &recomp_gen::fn_sub_33BDA0_0033bda0, &recomp_gen::fn_sub_33BDA0_0033bda0__recomp},
    {"sub_33BE90", 0x33BE90, &recomp_gen::fn_sub_33BE90_0033be90, &recomp_gen::fn_sub_33BE90_0033be90__recomp},
    {"sub_33BFA0", 0x33BFA0, &recomp_gen::fn_sub_33BFA0_0033bfa0, &recomp_gen::fn_sub_33BFA0_0033bfa0__recomp},
    {"sub_33C0A0", 0x33C0A0, &recomp_gen::fn_sub_33C0A0_0033c0a0, &recomp_gen::fn_sub_33C0A0_0033c0a0__recomp},
    {"sub_33C150", 0x33C150, &recomp_gen::fn_sub_33C150_0033c150, &recomp_gen::fn_sub_33C150_0033c150__recomp},
    {"sub_33C1A0", 0x33C1A0, &recomp_gen::fn_sub_33C1A0_0033c1a0, &recomp_gen::fn_sub_33C1A0_0033c1a0__recomp},
    {"sub_33C960", 0x33C960, &recomp_gen::fn_sub_33C960_0033c960, &recomp_gen::fn_sub_33C960_0033c960__recomp},
    {"sub_33CB20", 0x33CB20, &recomp_gen::fn_sub_33CB20_0033cb20, &recomp_gen::fn_sub_33CB20_0033cb20__recomp},
    {"sub_33CC10", 0x33CC10, &recomp_gen::fn_sub_33CC10_0033cc10, &recomp_gen::fn_sub_33CC10_0033cc10__recomp},
    {"sub_33CD20", 0x33CD20, &recomp_gen::fn_sub_33CD20_0033cd20, &recomp_gen::fn_sub_33CD20_0033cd20__recomp},
    {"sub_33CE10", 0x33CE10, &recomp_gen::fn_sub_33CE10_0033ce10, &recomp_gen::fn_sub_33CE10_0033ce10__recomp},
    {"sub_33CEB0", 0x33CEB0, &recomp_gen::fn_sub_33CEB0_0033ceb0, &recomp_gen::fn_sub_33CEB0_0033ceb0__recomp},
    {"sub_33CF00", 0x33CF00, &recomp_gen::fn_sub_33CF00_0033cf00, &recomp_gen::fn_sub_33CF00_0033cf00__recomp},
    {"sub_33D6D0", 0x33D6D0, &recomp_gen::fn_sub_33D6D0_0033d6d0, &recomp_gen::fn_sub_33D6D0_0033d6d0__recomp},
    {"sub_33D890", 0x33D890, &recomp_gen::fn_sub_33D890_0033d890, &recomp_gen::fn_sub_33D890_0033d890__recomp},
    {"sub_33D980", 0x33D980, &recomp_gen::fn_sub_33D980_0033d980, &recomp_gen::fn_sub_33D980_0033d980__recomp},
    {"sub_33DA90", 0x33DA90, &recomp_gen::fn_sub_33DA90_0033da90, &recomp_gen::fn_sub_33DA90_0033da90__recomp},
    {"sub_33DB80", 0x33DB80, &recomp_gen::fn_sub_33DB80_0033db80, &recomp_gen::fn_sub_33DB80_0033db80__recomp},
    {"sub_33DC20", 0x33DC20, &recomp_gen::fn_sub_33DC20_0033dc20, &recomp_gen::fn_sub_33DC20_0033dc20__recomp},
    {"sub_33DC70", 0x33DC70, &recomp_gen::fn_sub_33DC70_0033dc70, &recomp_gen::fn_sub_33DC70_0033dc70__recomp},
    {"sub_33E540", 0x33E540, &recomp_gen::fn_sub_33E540_0033e540, &recomp_gen::fn_sub_33E540_0033e540__recomp},
    {"sub_33F4A0", 0x33F4A0, &recomp_gen::fn_sub_33F4A0_0033f4a0, &recomp_gen::fn_sub_33F4A0_0033f4a0__recomp},
    {"sub_33F590", 0x33F590, &recomp_gen::fn_sub_33F590_0033f590, &recomp_gen::fn_sub_33F590_0033f590__recomp},
    {"sub_33F6A0", 0x33F6A0, &recomp_gen::fn_sub_33F6A0_0033f6a0, &recomp_gen::fn_sub_33F6A0_0033f6a0__recomp},
    {"sub_33F780", 0x33F780, &recomp_gen::fn_sub_33F780_0033f780, &recomp_gen::fn_sub_33F780_0033f780__recomp},
    {"sub_33F810", 0x33F810, &recomp_gen::fn_sub_33F810_0033f810, &recomp_gen::fn_sub_33F810_0033f810__recomp},
    {"sub_33F860", 0x33F860, &recomp_gen::fn_sub_33F860_0033f860, &recomp_gen::fn_sub_33F860_0033f860__recomp},
    {"sub_340100", 0x340100, &recomp_gen::fn_sub_340100_00340100, &recomp_gen::fn_sub_340100_00340100__recomp},
    {"sub_341F10", 0x341F10, &recomp_gen::fn_sub_341F10_00341f10, &recomp_gen::fn_sub_341F10_00341f10__recomp},
    {"sub_342480", 0x342480, &recomp_gen::fn_sub_342480_00342480, &recomp_gen::fn_sub_342480_00342480__recomp},
    {"sub_342550", 0x342550, &recomp_gen::fn_sub_342550_00342550, &recomp_gen::fn_sub_342550_00342550__recomp},
    {"sub_342990", 0x342990, &recomp_gen::fn_sub_342990_00342990, &recomp_gen::fn_sub_342990_00342990__recomp},
    {"sub_342A90", 0x342A90, &recomp_gen::fn_sub_342A90_00342a90, &recomp_gen::fn_sub_342A90_00342a90__recomp},
    {"sub_343410", 0x343410, &recomp_gen::fn_sub_343410_00343410, &recomp_gen::fn_sub_343410_00343410__recomp},
    {"sub_343790", 0x343790, &recomp_gen::fn_sub_343790_00343790, &recomp_gen::fn_sub_343790_00343790__recomp},
    {"sub_343860", 0x343860, &recomp_gen::fn_sub_343860_00343860, &recomp_gen::fn_sub_343860_00343860__recomp},
    {"sub_343C60", 0x343C60, &recomp_gen::fn_sub_343C60_00343c60, &recomp_gen::fn_sub_343C60_00343c60__recomp},
    {"sub_343D10", 0x343D10, &recomp_gen::fn_sub_343D10_00343d10, &recomp_gen::fn_sub_343D10_00343d10__recomp},
    {"sub_343D60", 0x343D60, &recomp_gen::fn_sub_343D60_00343d60, &recomp_gen::fn_sub_343D60_00343d60__recomp},
    {"sub_344720", 0x344720, &recomp_gen::fn_sub_344720_00344720, &recomp_gen::fn_sub_344720_00344720__recomp},
    {"sub_345CF0", 0x345CF0, &recomp_gen::fn_sub_345CF0_00345cf0, &recomp_gen::fn_sub_345CF0_00345cf0__recomp},
    {"sub_3461A0", 0x3461A0, &recomp_gen::fn_sub_3461A0_003461a0, &recomp_gen::fn_sub_3461A0_003461a0__recomp},
    {"sub_346350", 0x346350, &recomp_gen::fn_sub_346350_00346350, &recomp_gen::fn_sub_346350_00346350__recomp},
    {"sub_3463C0", 0x3463C0, &recomp_gen::fn_sub_3463C0_003463c0, &recomp_gen::fn_sub_3463C0_003463c0__recomp},
    {"sub_346460", 0x346460, &recomp_gen::fn_sub_346460_00346460, &recomp_gen::fn_sub_346460_00346460__recomp},
    {"sub_346530", 0x346530, &recomp_gen::fn_sub_346530_00346530, &recomp_gen::fn_sub_346530_00346530__recomp},
    {"sub_347100", 0x347100, &recomp_gen::fn_sub_347100_00347100, &recomp_gen::fn_sub_347100_00347100__recomp},
    {"sub_347170", 0x347170, &recomp_gen::fn_sub_347170_00347170, &recomp_gen::fn_sub_347170_00347170__recomp},
    {"sub_3472D0", 0x3472D0, &recomp_gen::fn_sub_3472D0_003472d0, &recomp_gen::fn_sub_3472D0_003472d0__recomp},
    {"sub_347350", 0x347350, &recomp_gen::fn_sub_347350_00347350, &recomp_gen::fn_sub_347350_00347350__recomp},
    {"sub_3473B0", 0x3473B0, &recomp_gen::fn_sub_3473B0_003473b0, &recomp_gen::fn_sub_3473B0_003473b0__recomp},
    {"sub_347CB0", 0x347CB0, &recomp_gen::fn_sub_347CB0_00347cb0, &recomp_gen::fn_sub_347CB0_00347cb0__recomp},
    {"sub_347FC0", 0x347FC0, &recomp_gen::fn_sub_347FC0_00347fc0, &recomp_gen::fn_sub_347FC0_00347fc0__recomp},
    {"sub_348030", 0x348030, &recomp_gen::fn_sub_348030_00348030, &recomp_gen::fn_sub_348030_00348030__recomp},
    {"sub_348090", 0x348090, &recomp_gen::fn_sub_348090_00348090, &recomp_gen::fn_sub_348090_00348090__recomp},
    {"sub_348340", 0x348340, &recomp_gen::fn_sub_348340_00348340, &recomp_gen::fn_sub_348340_00348340__recomp},
    {"sub_348760", 0x348760, &recomp_gen::fn_sub_348760_00348760, &recomp_gen::fn_sub_348760_00348760__recomp},
    {"sub_348BD0", 0x348BD0, &recomp_gen::fn_sub_348BD0_00348bd0, &recomp_gen::fn_sub_348BD0_00348bd0__recomp},
    {"sub_348F30", 0x348F30, &recomp_gen::fn_sub_348F30_00348f30, &recomp_gen::fn_sub_348F30_00348f30__recomp},
    {"sub_349260", 0x349260, &recomp_gen::fn_sub_349260_00349260, &recomp_gen::fn_sub_349260_00349260__recomp},
    {"sub_349450", 0x349450, &recomp_gen::fn_sub_349450_00349450, &recomp_gen::fn_sub_349450_00349450__recomp},
    {"sub_349870", 0x349870, &recomp_gen::fn_sub_349870_00349870, &recomp_gen::fn_sub_349870_00349870__recomp},
    {"sub_349AF0", 0x349AF0, &recomp_gen::fn_sub_349AF0_00349af0, &recomp_gen::fn_sub_349AF0_00349af0__recomp},
    {"sub_349ED0", 0x349ED0, &recomp_gen::fn_sub_349ED0_00349ed0, &recomp_gen::fn_sub_349ED0_00349ed0__recomp},
    {"sub_349FA0", 0x349FA0, &recomp_gen::fn_sub_349FA0_00349fa0, &recomp_gen::fn_sub_349FA0_00349fa0__recomp},
    {"sub_34A1D0", 0x34A1D0, &recomp_gen::fn_sub_34A1D0_0034a1d0, &recomp_gen::fn_sub_34A1D0_0034a1d0__recomp},
    {"sub_34A280", 0x34A280, &recomp_gen::fn_sub_34A280_0034a280, &recomp_gen::fn_sub_34A280_0034a280__recomp},
    {"sub_34A340", 0x34A340, &recomp_gen::fn_sub_34A340_0034a340, &recomp_gen::fn_sub_34A340_0034a340__recomp},
    {"sub_34A590", 0x34A590, &recomp_gen::fn_sub_34A590_0034a590, &recomp_gen::fn_sub_34A590_0034a590__recomp},
    {"sub_34A8C0", 0x34A8C0, &recomp_gen::fn_sub_34A8C0_0034a8c0, &recomp_gen::fn_sub_34A8C0_0034a8c0__recomp},
    {"sub_34A990", 0x34A990, &recomp_gen::fn_sub_34A990_0034a990, &recomp_gen::fn_sub_34A990_0034a990__recomp},
    {"sub_34A9C0", 0x34A9C0, &recomp_gen::fn_sub_34A9C0_0034a9c0, &recomp_gen::fn_sub_34A9C0_0034a9c0__recomp},
    {"sub_34ABC0", 0x34ABC0, &recomp_gen::fn_sub_34ABC0_0034abc0, &recomp_gen::fn_sub_34ABC0_0034abc0__recomp},
    {"sub_34AC70", 0x34AC70, &recomp_gen::fn_sub_34AC70_0034ac70, &recomp_gen::fn_sub_34AC70_0034ac70__recomp},
    {"sub_34B1A0", 0x34B1A0, &recomp_gen::fn_sub_34B1A0_0034b1a0, &recomp_gen::fn_sub_34B1A0_0034b1a0__recomp},
    {"sub_34B320", 0x34B320, &recomp_gen::fn_sub_34B320_0034b320, &recomp_gen::fn_sub_34B320_0034b320__recomp},
    {"sub_34B3A0", 0x34B3A0, &recomp_gen::fn_sub_34B3A0_0034b3a0, &recomp_gen::fn_sub_34B3A0_0034b3a0__recomp},
    {"sub_34B600", 0x34B600, &recomp_gen::fn_sub_34B600_0034b600, &recomp_gen::fn_sub_34B600_0034b600__recomp},
    {"sub_34B6B0", 0x34B6B0, &recomp_gen::fn_sub_34B6B0_0034b6b0, &recomp_gen::fn_sub_34B6B0_0034b6b0__recomp},
    {"sub_34B830", 0x34B830, &recomp_gen::fn_sub_34B830_0034b830, &recomp_gen::fn_sub_34B830_0034b830__recomp},
    {"sub_34B8B0", 0x34B8B0, &recomp_gen::fn_sub_34B8B0_0034b8b0, &recomp_gen::fn_sub_34B8B0_0034b8b0__recomp},
    {"sub_34BB10", 0x34BB10, &recomp_gen::fn_sub_34BB10_0034bb10, &recomp_gen::fn_sub_34BB10_0034bb10__recomp},
    {"sub_34BBC0", 0x34BBC0, &recomp_gen::fn_sub_34BBC0_0034bbc0, &recomp_gen::fn_sub_34BBC0_0034bbc0__recomp},
    {"sub_34BC80", 0x34BC80, &recomp_gen::fn_sub_34BC80_0034bc80, &recomp_gen::fn_sub_34BC80_0034bc80__recomp},
    {"sub_34BD60", 0x34BD60, &recomp_gen::fn_sub_34BD60_0034bd60, &recomp_gen::fn_sub_34BD60_0034bd60__recomp},
    {"sub_34BDF0", 0x34BDF0, &recomp_gen::fn_sub_34BDF0_0034bdf0, &recomp_gen::fn_sub_34BDF0_0034bdf0__recomp},
    {"sub_34BEF0", 0x34BEF0, &recomp_gen::fn_sub_34BEF0_0034bef0, &recomp_gen::fn_sub_34BEF0_0034bef0__recomp},
    {"sub_34BF10", 0x34BF10, &recomp_gen::fn_sub_34BF10_0034bf10, &recomp_gen::fn_sub_34BF10_0034bf10__recomp},
    {"sub_34BFC0", 0x34BFC0, &recomp_gen::fn_sub_34BFC0_0034bfc0, &recomp_gen::fn_sub_34BFC0_0034bfc0__recomp},
    {"sub_34C160", 0x34C160, &recomp_gen::fn_sub_34C160_0034c160, &recomp_gen::fn_sub_34C160_0034c160__recomp},
    {"sub_34C1B0", 0x34C1B0, &recomp_gen::fn_sub_34C1B0_0034c1b0, &recomp_gen::fn_sub_34C1B0_0034c1b0__recomp},
    {"sub_34C670", 0x34C670, &recomp_gen::fn_sub_34C670_0034c670, &recomp_gen::fn_sub_34C670_0034c670__recomp},
    {"sub_34C890", 0x34C890, &recomp_gen::fn_sub_34C890_0034c890, &recomp_gen::fn_sub_34C890_0034c890__recomp},
    {"sub_34C9B0", 0x34C9B0, &recomp_gen::fn_sub_34C9B0_0034c9b0, &recomp_gen::fn_sub_34C9B0_0034c9b0__recomp},
    {"sub_34D510", 0x34D510, &recomp_gen::fn_sub_34D510_0034d510, &recomp_gen::fn_sub_34D510_0034d510__recomp},
    {"sub_34D670", 0x34D670, &recomp_gen::fn_sub_34D670_0034d670, &recomp_gen::fn_sub_34D670_0034d670__recomp},
    {"sub_34D6F0", 0x34D6F0, &recomp_gen::fn_sub_34D6F0_0034d6f0, &recomp_gen::fn_sub_34D6F0_0034d6f0__recomp},
    {"sub_34D8A0", 0x34D8A0, &recomp_gen::fn_sub_34D8A0_0034d8a0, &recomp_gen::fn_sub_34D8A0_0034d8a0__recomp},
    {"sub_34E4C0", 0x34E4C0, &recomp_gen::fn_sub_34E4C0_0034e4c0, &recomp_gen::fn_sub_34E4C0_0034e4c0__recomp},
    {"sub_34E610", 0x34E610, &recomp_gen::fn_sub_34E610_0034e610, &recomp_gen::fn_sub_34E610_0034e610__recomp},
    {"sub_34E690", 0x34E690, &recomp_gen::fn_sub_34E690_0034e690, &recomp_gen::fn_sub_34E690_0034e690__recomp},
    {"sub_34E820", 0x34E820, &recomp_gen::fn_sub_34E820_0034e820, &recomp_gen::fn_sub_34E820_0034e820__recomp},
};

namespace fx2 = ::p3fes::game::fx2;  // the record offsets (fx2.h)

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that set chosen FPRs after the random register file
// and, when asked, give each body its own stand-in world (stand_ins.h: the heap behind the RW slots, printf, the file
// layer, plus the recorders of fx_world() for the RenderWare / layer-manager callees this test library does not emit).
// The two worlds' call logs must match.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    WorldSetup setup;
};
Tramp g_t;
int g_pairs = 0;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    g_t.world[K] = std::make_unique<StandInWorld>();
    install_standard(*g_t.world[K]);
    if (g_t.setup) g_t.setup(*g_t.world[K]);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float bitsf(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = false;
    WorldSetup setup;
};

hgp::Run fx_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.world[0].reset();
    g_t.world[1].reset();
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    ++g_pairs;
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
float rf(const Machine& m, u32 va) { return bitsf(r32(m, va)); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float f) { w32(m, va, fbits(f)); }

std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// The callees of this slice's bodies, served by stand-ins so the pairs run past them. A stand-in only takes effect
// for a callee the test library neither replaces nor emits: the replaced ones among these (geometryLock /
// RpGeometryUnlock, the layer manager's placement and queues, sub_3210C0, RwTextureDestroy, ...) run for real:
// geometryLock / RpGeometryUnlock (return the geometry), the random float sub_358030 ($f0 from the call count), the
// layer manager's mesh placement / queues (sub_3238D0, sub_323860, sub_323880, sub_321180, sub_3211D0), its mesh
// constructors (a fake mesh pointer), sub_3237C0 (mesh destroy), the particle samplers sub_32A770 / sub_32A890, the
// projections sub_329A60 (on screen) / sub_329BA0 ($f0 = 12.5) / sub_329890, the sprite players sub_322D40 /
// sub_322D10 / sub_322FD0 / sub_323BF0, RwTextureDestroy sub_4D0F00, the texture getter sub_3210C0, the frame ops
// sub_4CB2F0 / sub_4CB7F0, and the class-13 / class-12 kind slots sub_334310 .. sub_3377F0, sub_338530 ..
// sub_338AC0 (not emitted).
constexpr u32 kFakeMesh = 0x01F40000u;  // free in the ELF image and every snapshot used here
WorldSetup fx_world() {
    return [](StandInWorld& w) {
        w.si.install(0x493370u, "geometryLock", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
        w.si.install(0x4933D0u, "RpGeometryUnlock", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
        w.si.install(0x358030u, "sub_358030", [](EEContext& ctx, StandIns& s, StandInCall&) {
            ctx.fpr[0] = fbits(0.125f + 0.0625f * static_cast<float>(s.sequence % 13));
        });
        w.si.install(0x329BA0u, "sub_329BA0", [](EEContext& ctx, StandIns&, StandInCall&) { ctx.fpr[0] = fbits(12.5f); });
        w.si.install_recorder(0x329A60u, "sub_329A60", 1);
        w.si.install_recorder(0x329890u, "sub_329890", 0);
        for (u32 va : {0x3238D0u, 0x323860u, 0x323880u, 0x321180u, 0x3211D0u, 0x3237C0u, 0x32A770u, 0x32A890u, 0x322D40u,
                       0x322D10u, 0x322FD0u, 0x323BF0u, 0x4D0F00u, 0x4CB2F0u, 0x4CB7F0u})
            w.si.install_recorder(va, "callee", 0);
        for (u32 va : {0x3233A0u, 0x323240u, 0x323FB0u, 0x323E10u, 0x323640u, 0x324160u, 0x3210C0u})
            w.si.install_recorder(va, "mesh/texture", kFakeMesh);
        for (u32 va : {0x334310u, 0x334390u, 0x334820u, 0x3348B0u, 0x335180u, 0x3353F0u, 0x335540u, 0x3359E0u, 0x335A70u,
                       0x336630u, 0x3368A0u, 0x336920u, 0x336DF0u, 0x336E80u, 0x3377F0u, 0x338530u, 0x3385D0u, 0x338770u,
                       0x3387C0u, 0x338AC0u, 0x349FD0u, 0x34AE30u, 0x34A370u, 0x34A650u})
            w.si.install_recorder(va, "kind slot", 0x01F41000u);
    };
}

// The fake mesh a stood-in constructor returns: flags 0, 8 vertices, an atomic whose geometry has a prelight /
// texcoord / vertex buffer, two colour pointers -- enough for the create paths that touch the result.
void put_fake_mesh(Machine& m) {
    const u32 mesh = kFakeMesh, atomic = mesh + 0x100, geo = mesh + 0x200, morph = mesh + 0x300, buf = mesh + 0x400;
    std::memset(m.at(mesh), 0, 0x1000);
    w16(m, mesh + 8, 8);
    w32(m, mesh + 16, atomic);
    w32(m, mesh + 20, mesh + 0x380);
    w32(m, mesh + 40, mesh + 0x3C0);
    for (u32 i = 0; i < 8; ++i) w32(m, mesh + 0x3C0 + 4 * i, mesh + 0x3E0 + 8 * i);  // colour pointers (+4 RGBA)
    w32(m, atomic + 24, geo);
    w32(m, geo + 48, buf);          // prelight
    w32(m, geo + 52, buf + 0x200);  // texcoords
    w32(m, geo + 92, morph);
    w32(m, morph + 20, buf + 0x400);  // vertices
}

// --- the replay snapshots with live effects -----------------------------------------------------------------------------
// extracted/_ours/fx2_* (made for this slice from the battle and fusion routes at the vblanks where effects of the
// band are alive; RAM identical to the reference builds'), and the instance each listed function was last called with
// within the last 2.5 vblanks before the snapshot (recorded by the measuring build; kLive below).
const std::vector<u8>& snapshot(const char* dir) {
    static std::map<std::string, std::vector<u8>> cache;
    auto it = cache.find(dir);
    if (it == cache.end()) it = cache.emplace(dir, read_snapshot(dir)).first;
    return it->second;
}
bool restore(Machine& m, const char* dir) {
    const std::vector<u8>& s = snapshot(dir);
    if (s.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), s.data(), s.size());
    return true;
}

struct Live {
    const char* snap;
    const char* fn;
    u32 a0, a1, a2;
};
const Live kLive[] = {
    {"fx2_battle_4596", "sub_332B60", 0x013E6A20u, 0x00000002u, 0x00000002u},
    {"fx2_battle_4596", "sub_332E10", 0x013E6A20u, 0x00957978u, 0x00000004u},
    {"fx2_battle_4596", "sub_333300", 0x013E6A80u, 0x0000001Du, 0x01FFFB9Cu},
    {"fx2_battle_4596", "sub_333970", 0x013E6A80u, 0x0000001Du, 0x01FFFB80u},
    {"fx2_battle_4596", "sub_3341C0", 0x013E6A80u, 0x01400780u, 0x00000007u},
    {"fx2_battle_4596", "sub_334220", 0x013E6A80u, 0x000000FFu, 0x01FFFB9Cu},
    {"fx2_battle_4596", "sub_337FD0", 0x01879B10u, 0x01FFF9D0u, 0x01FFF9D0u},
    {"fx2_battle_4596", "sub_338360", 0x01879B10u, 0x01FFFB30u, 0x01879AB0u},
    {"fx2_battle_4596", "sub_338EA0", 0x013E6280u, 0x01FFFC00u, 0x01FFFC00u},
    {"fx2_battle_4596", "sub_339200", 0x013E6280u, 0x00957978u, 0x00000004u},
    {"fx2_battle_4596", "sub_33A5B0", 0x01400E20u, 0x01FFFC00u, 0x01FFFC00u},
    {"fx2_battle_4596", "sub_33AF10", 0x01400E20u, 0x0095797Cu, 0x00000008u},
    {"fx2_battle_4596", "sub_33C1A0", 0x013E4EA0u, 0x01FFFC00u, 0x01FFFC00u},
    {"fx2_battle_4596", "sub_33C960", 0x013E4EA0u, 0x0095797Cu, 0x00000008u},
    {"fx2_battle_4596", "sub_346530", 0x01879310u, 0x01FFFB30u, 0x01879AB0u},
    {"fx2_battle_4596", "sub_348340", 0x0143C7E0u, 0x01FFF8E0u, 0x70000020u},
    {"fx2_battle_4596", "sub_348760", 0x0143C7E0u, 0x01FFF9E0u, 0x700020E0u},
    {"fx2_battle_4596", "sub_349450", 0x0143CAF0u, 0x0143CB90u, 0x00000000u},
    {"fx2_battle_4596", "sub_34A9C0", 0x0143CA00u, 0x00000000u, 0xFFFFFFFFu},
    {"fx2_battle_4596", "sub_34ABC0", 0x0143C3A0u, 0x0000000Eu, 0x80001101u},
    {"fx2_battle_4720", "sub_330190", 0x016E1560u, 0x00000012u, 0x00000014u},
    {"fx2_battle_4720", "sub_330C40", 0x016E3030u, 0x01FFFB40u, 0x01FFFB40u},
    {"fx2_battle_4720", "sub_332B60", 0x016E0420u, 0x01FFFB40u, 0x01FFFB40u},
    {"fx2_battle_4720", "sub_332E10", 0x016E0420u, 0x00957460u, 0x00000008u},
    {"fx2_battle_4720", "sub_3341C0", 0x016E0480u, 0x01FFFB40u, 0x01FFFB40u},
    {"fx2_battle_4720", "sub_334220", 0x016E0480u, 0x00000004u, 0x0000000Au},
    {"fx2_battle_4720", "sub_348340", 0x0163E504u, 0x01FFF930u, 0x70002020u},
    {"fx2_battle_4720", "sub_348760", 0x0163E504u, 0x01FFFA30u, 0x700007E0u},
    {"fx2_battle_4720", "sub_349AF0", 0x0163E410u, 0x00000004u, 0x0000000Au},
    {"fx2_battle_5450", "sub_33F860", 0x01437C50u, 0x6E446F8Eu, 0x705B0364u},
    {"fx2_battle_5450", "sub_340100", 0x01437C50u, 0x00957998u, 0x00000008u},
    {"fx2_battle_5760", "sub_338EA0", 0x015D42E0u, 0x00000023u, 0x014EE7E0u},
    {"fx2_battle_5760", "sub_339200", 0x015D42E0u, 0x016B99C0u, 0x00000024u},
    {"fx2_battle_5760", "sub_33DC70", 0x015D8AE0u, 0x00000004u, 0x014EE7E0u},
    {"fx2_battle_5760", "sub_33E540", 0x015D8AE0u, 0x016B99C0u, 0x00000020u},
    {"fx2_battle_5760", "sub_342A90", 0x014FBD70u, 0x00000023u, 0x014EE7E0u},
    {"fx2_battle_5760", "sub_343410", 0x014FBD70u, 0x01FFFBF0u, 0x00000024u},
    {"fx2_battle_5760", "sub_348340", 0x01607FD4u, 0x01FFF930u, 0x70002020u},
    {"fx2_battle_5760", "sub_348760", 0x01607FD4u, 0x01FFFA30u, 0x700007E0u},
    {"fx2_battle_5760", "sub_349AF0", 0x01607EE0u, 0x01FFFB60u, 0x01607E80u},
    {"fx2_battle_5840", "sub_330190", 0x016DCD30u, 0x00000004u, 0x00000012u},
    {"fx2_battle_5840", "sub_332B60", 0x013B8370u, 0x0000001Cu, 0x01FFFB40u},
    {"fx2_battle_5840", "sub_332E10", 0x013B8370u, 0x01629B40u, 0x0000001Du},
    {"fx2_battle_5840", "sub_333300", 0x014564C0u, 0x00000003u, 0x01FFFADCu},
    {"fx2_battle_5840", "sub_333970", 0x014564C0u, 0x00000003u, 0x01FFFAC0u},
    {"fx2_battle_5840", "sub_3341C0", 0x013B83D0u, 0x0000001Cu, 0x01FFFB40u},
    {"fx2_battle_5840", "sub_334220", 0x013B83D0u, 0x00000005u, 0x0000000Au},
    {"fx2_battle_5840", "sub_338EA0", 0x015D9060u, 0x0000000Au, 0x0000000Au},
    {"fx2_battle_5840", "sub_339200", 0x015D9060u, 0x00957960u, 0x00000008u},
    {"fx2_battle_5840", "sub_33CF00", 0x0141ABA0u, 0x01FFFB60u, 0x015D9000u},
    {"fx2_battle_5840", "sub_33D6D0", 0x0141ABA0u, 0x01FFFBF0u, 0x0000001Du},
    {"fx2_battle_5840", "sub_348340", 0x014562B4u, 0x01FFF930u, 0x70000020u},
    {"fx2_battle_5840", "sub_348760", 0x014562B4u, 0x01FFFA30u, 0x700020E0u},
    {"fx2_battle_5840", "sub_349AF0", 0x01607EE0u, 0x01FFFB60u, 0x01607E80u},
    {"fx2_battle_5840", "sub_34AC70", 0x0187FD30u, 0x00000004u, 0x01FFFB40u},
    {"fx2_fusion_5400", "sub_337FD0", 0x01ACB4C0u, 0x01FFFBF0u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_338360", 0x01ACB4C0u, 0x01A93DF0u, 0x00000028u},
    {"fx2_fusion_5400", "sub_3399A0", 0x01ACFAF0u, 0x01FFFBF0u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_33A220", 0x01ACFAF0u, 0x009578B0u, 0x00000004u},
    {"fx2_fusion_5400", "sub_33A5B0", 0x01A92A20u, 0x01FFFBF0u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_33AF10", 0x01A92A20u, 0x009577B4u, 0x00000008u},
    {"fx2_fusion_5400", "sub_33C1A0", 0x01A8A3B0u, 0x01FFFBF0u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_33C960", 0x01A8A3B0u, 0x01A93DF0u, 0x00000028u},
    {"fx2_fusion_5400", "sub_33DC70", 0x01A56CE0u, 0x01FFFBF0u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_33E540", 0x01A56CE0u, 0x01A93DF0u, 0x00000020u},
    {"fx2_fusion_5400", "sub_342A90", 0x01A8CB50u, 0x01FFFC10u, 0xFFFFFFFFu},
    {"fx2_fusion_5400", "sub_343410", 0x01A8CB50u, 0x01FFFC10u, 0xFFFFFFFFu},
    {"fx2_fusion_5400", "sub_343D60", 0x01A56840u, 0x00000004u, 0xFFFFFFFFu},
    {"fx2_fusion_5400", "sub_344720", 0x01A56840u, 0x009579B4u, 0x00000008u},
    {"fx2_fusion_5400", "sub_3473B0", 0x013B8410u, 0x009577B4u, 0x00000020u},
    {"fx2_fusion_5400", "sub_348340", 0x01AD0D74u, 0x01FFF930u, 0x70002020u},
    {"fx2_fusion_5400", "sub_348760", 0x01AD0D74u, 0x01FFFA30u, 0x70000120u},
    {"fx2_fusion_5400", "sub_348BD0", 0x01A92890u, 0x01FFFA40u, 0x80001101u},
    {"fx2_fusion_5400", "sub_349870", 0x01ACF860u, 0x00000002u, 0x01FFFBF0u},
    {"fx2_fusion_5400", "sub_349AF0", 0x01AD0C80u, 0x01FFFC10u, 0x00000024u},
    {"fx2_fusion_5400", "sub_34AC70", 0x01A927A0u, 0x01FFFC10u, 0x00000008u},
};

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(fx2): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int stops_total = 0, pairs_total = 0;
    // the image as loaded: restored before each function (a stray store of an earlier body through a random pointer
    // could otherwise re-aim a function pointer the next body calls through, e.g. the RW memory slots)
    const std::vector<u8> image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        std::memcpy(m->mem.main_ram(), image.data(), image.size());
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops_total += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs_total;
        }
    }
    MESSAGE("random worlds: " << pairs_total << " pairs, " << stops_total << " stopped early");
}

// =====================================================================================================================
// The live effects of the battle / fusion snapshots: each function on the instance it was running on, plus every other
// slot of the same class / kind that takes the instance (update, draw, restart), on the stand-in world
// =====================================================================================================================
TEST_CASE("game(fx2): the effect handlers on the live instances of the battle and fusion snapshots") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    // the slots that take the same instance as a listed function (classes / kinds whose update and draw both run)
    const std::map<std::string, std::vector<const char*>> siblings = {
        {"sub_332B60", {"sub_332E10", "sub_332F10"}}, {"sub_332E10", {"sub_332B60"}},
        {"sub_337FD0", {"sub_338360"}}, {"sub_338EA0", {"sub_339200"}},
        {"sub_3399A0", {"sub_33A220"}}, {"sub_33A5B0", {"sub_33AF10"}}, {"sub_33C1A0", {"sub_33C960"}},
        {"sub_33CF00", {"sub_33D6D0"}}, {"sub_33DC70", {"sub_33E540"}}, {"sub_33F860", {"sub_340100"}},
        {"sub_342A90", {"sub_343410"}}, {"sub_343D60", {"sub_344720"}}, {"sub_346530", {"sub_347100"}},
        {"sub_3473B0", {"sub_347CB0"}}, {"sub_34A9C0", {"sub_34ABC0"}},
    };
    int ran = 0, stopped = 0, snaps = 0;
    const char* last = "";
    for (const Live& l : kLive) {
        if (std::string(last) != l.snap) {
            last = l.snap;
            if (snapshot(l.snap).size() != EEMemory::kMainRamSize) {
                MESSAGE("SKIP: extracted/_ours/" << l.snap << " not found");
                continue;
            }
            ++snaps;
        }
        if (snapshot(l.snap).size() != EEMemory::kMainRamSize) continue;
        std::vector<const char*> fns = {l.fn};
        if (auto it = siblings.find(l.fn); it != siblings.end()) fns.insert(fns.end(), it->second.begin(), it->second.end());
        for (const char* fn : fns) {
            for (u32 seed = 1; seed <= 3; ++seed) {
                REQUIRE(restore(m, l.snap));
                put_fake_mesh(m);
                Opt o;
                o.standins = true;
                o.setup = fx_world();
                o.fpr[12] = fbits(seed == 1 ? 1.0f : 0.5f * static_cast<float>(seed));
                const std::string what = std::string(l.snap) + " " + fn;
                const hgp::Run r = fx_pair(m, fn, Args{sx(l.a0), sx(l.a1), sx(l.a2), 0}, 300 + seed, what.c_str(), o);
                ++ran;
                stopped += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE("live-instance pairs: " << ran << " on " << snaps << " snapshots (" << stopped << " stopped early)");
}

// =====================================================================================================================
// Documented rules
// =====================================================================================================================
// sub_332070 [fxPsysCreate]: the one-block layout (header 48, particles count * (cells + 1) * 32, the type's
// per-particle state and two parameter copies), the type, count and slots, the flag bit 0 from params +188.
TEST_CASE("game(fx2): the particle-system constructor's layout") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 params = 0x01F20000u;
    int checks = 0;
    for (u32 type : {8u, 9u, 10u, 11u}) {
        for (u32 count : {1u, 7u, 30u}) {
            for (u32 world : {0u, 1u}) {
                std::memset(m.at(params), 0, 0x200);
                for (u32 i = 0; i < 0x40; ++i) w32(m, params + 4 * i, 0x1000u + i);
                w32(m, params + 192, 2);
                w32(m, params + 196, type == 9 ? 0 : 3);
                w8(m, params + 188, static_cast<u8>(world));
                Opt o;
                o.standins = true;
                o.setup = fx_world();
                const hgp::Run r = fx_pair(m, "sub_332070", Args{type, count, sx(params), 0}, 40 + type + count, "psys create", o);
                if (r.stopped) continue;
                const u32 ps = static_cast<u32>(v0_of(r));
                const u32 cells = r32(m, params + 192) * r32(m, params + 196);
                const u32 slots = count * (cells + 1);
                const u32 psize = r32(m, 0x69C51Cu + 16 * type);
                CHECK(r16(m, ps + fx2::kPsysType) == type);
                CHECK(r32(m, ps + fx2::kPsysCount) == count);
                CHECK(r32(m, ps + fx2::kPsysSlots) == slots);
                CHECK(r32(m, ps + fx2::kPsysParticles) == ps + 48);
                CHECK(r32(m, ps + fx2::kPsysParams) == ps + 48 + 32 * slots);
                CHECK(r32(m, ps + fx2::kPsysBaseParams) == ps + 48 + 32 * slots + psize);
                CHECK(r32(m, ps + fx2::kPsysState) == ps + 48 + 32 * slots + 2 * psize);
                CHECK(r32(m, ps + fx2::kPsysSelf) == ps);
                CHECK((r32(m, ps + fx2::kPsysFlags) & 1u) == world);
                CHECK(r32(m, ps + fx2::kPsysFrame) == 0);
                const u32 live = r32(m, ps + fx2::kPsysParams), base = r32(m, ps + fx2::kPsysBaseParams);
                for (u32 off = 32; off < psize; off += 4) CHECK(r32(m, live + off) == r32(m, params + off));  // pos / rot cleared
                for (u32 off = 0; off < 32; off += 4) CHECK(r32(m, live + off) == (off % 16 == 12 ? 0x3F800000u : 0u));  // vf0
                for (u32 off = 0; off < psize; off += 4) CHECK(r32(m, base + off) == r32(m, params + off));
                checks += 11;
            }
        }
    }
    MESSAGE("psys create checks: " << checks);
}

// The four scale slots: every listed parameter of the live block = the base block's x $f12, the rest untouched.
TEST_CASE("game(fx2): the particle-system scale slots") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    struct S {
        const char* fn;
        std::vector<u32> offs;
    };
    const S fns[] = {{"sub_330100", {100, 104, 116, 124, 132, 200, 220, 228, 232}},
                     {"sub_330BB0", {100, 104, 116, 124, 132, 200, 208, 220, 228}},
                     {"sub_3315D0", {100, 104, 116, 124, 132, 200, 204, 220}},
                     {"sub_331FD0", {100, 104, 116, 124, 132, 200, 204, 212, 216, 224}}};
    const u32 ps = 0x01F20000u, live = ps + 0x100, base = ps + 0x300;
    std::mt19937 rng{0x5CA1Eu};
    for (const S& s : fns) {
        for (int k = 0; k < 8; ++k) {
            std::memset(m.at(ps), 0, 0x500);
            w32(m, ps + fx2::kPsysParams, live);
            w32(m, ps + fx2::kPsysBaseParams, base);
            for (u32 off = 0; off < 0x100; off += 4) {
                wf(m, base + off, static_cast<float>(static_cast<int>(rng() % 2000) - 1000) / 8.0f);
                w32(m, live + off, 0xDEAD0000u + off);
            }
            const float f = k == 0 ? 1.0f : static_cast<float>(static_cast<int>(rng() % 64) - 16) / 4.0f;
            Opt o;
            o.fpr[12] = fbits(f);
            fx_pair(m, s.fn, Args{sx(ps), 0, 0, 0}, 70 + k, s.fn, o);
            for (u32 off = 0; off < 0x100; off += 4) {
                const bool listed = std::find(s.offs.begin(), s.offs.end(), off) != s.offs.end();
                if (listed)
                    CHECK(rf(m, live + off) == rf(m, base + off) * f);  // one EE multiply: exact for these operands
                else
                    CHECK(r32(m, live + off) == 0xDEAD0000u + off);
            }
        }
    }
}

// Class 13's slots over the kind rows 0x69C5D0 (kinds 1, 3, 4: their slots are stood in): update ++frame, draw only
// with frame > 0, restart = init + frame 0, destroy = kind destroy on the object + RwFree; and the constructor's layout.
TEST_CASE("game(fx2): class 13 dispatch and constructor") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 inst = 0x01F20000u;
    const u32 slots[3][5] = {{0x334310u, 0x334390u, 0x334820u, 0x3348B0u, 0x335180u},
                             {0x3353F0u, 0x335540u, 0x3359E0u, 0x335A70u, 0x336630u},
                             {0x3368A0u, 0x336920u, 0x336DF0u, 0x336E80u, 0x3377F0u}};
    const u32 kinds[3] = {1, 3, 4};
    for (int ki = 0; ki < 3; ++ki) {
        for (s32 frame : {-1, 0, 1, 5}) {
            auto setup = [&] {
                std::memset(m.at(inst), 0, 0x100);
                w32(m, inst + fx2::kC13Kind, kinds[ki]);
                w32(m, inst + fx2::kC13Frame, static_cast<u32>(frame));
                w32(m, inst + fx2::kC13Obj, 0x01F21000u);
            };
            Opt o;
            o.standins = true;
            o.setup = fx_world();
            setup();
            fx_pair(m, "sub_337C90", Args{sx(inst), 0, 0, 0}, 1, "c13 step", o);
            CHECK(r32(m, inst + fx2::kC13Frame) == static_cast<u32>(frame + 1));
            CHECK(g_t.world[1]->si.calls_to(slots[ki][3]) == 1);
            setup();
            fx_pair(m, "sub_337CF0", Args{sx(inst), 0, 0, 0}, 2, "c13 draw", o);
            CHECK(g_t.world[1]->si.calls_to(slots[ki][4]) == (frame > 0 ? 1u : 0u));
            setup();
            fx_pair(m, "sub_337D40", Args{sx(inst), 0, 0, 0}, 3, "c13 update", o);
            CHECK(g_t.world[1]->si.calls_to(slots[ki][3]) == 1);
            CHECK(g_t.world[1]->si.calls_to(slots[ki][4]) == (frame + 1 > 0 ? 1u : 0u));
            setup();
            fx_pair(m, "sub_337C40", Args{sx(inst), 0, 0, 0}, 4, "c13 restart", o);
            CHECK(r32(m, inst + fx2::kC13Frame) == 0);
            CHECK(g_t.world[1]->si.calls_to(slots[ki][0]) == 1);
            setup();
            fx_pair(m, "sub_337BB0", Args{sx(inst), 0, 0, 0}, 5, "c13 destroy", o);
            REQUIRE(g_t.world[1]->si.calls_to(slots[ki][2]) == 1);
            for (const StandInCall& c : g_t.world[1]->si.log)
                if (c.va == slots[ki][2]) CHECK(static_cast<u32>(c.args[0]) == inst);  // the instance, not the object
        }
        // the constructor: frame 0, kind, colour -1, scale 1.0, the parameters copied, create then init
        const u32 params = 0x01F22000u;
        for (u32 i = 0; i < 64; ++i) w32(m, params + 4 * i, 0xC0DE0000u + i);
        Opt o;
        o.standins = true;
        o.setup = fx_world();
        const hgp::Run r = fx_pair(m, "sub_337A60", Args{kinds[ki], sx(params), 0, 0}, 6, "c13 create", o);
        const u32 c = static_cast<u32>(v0_of(r));
        CHECK(r32(m, c + fx2::kC13Frame) == 0);
        CHECK(r32(m, c + fx2::kC13Kind) == kinds[ki]);
        CHECK(r32(m, c + fx2::kC13Colour) == 0xFFFFFFFFu);
        CHECK(rf(m, c + fx2::kC13Scale) == 1.0f);
        CHECK(r32(m, c + fx2::kC13Params) == c + 64);
        CHECK(r32(m, c + fx2::kC13Obj) == 0x01F41000u);  // the stood-in create's result
        const u32 psize = r32(m, 0x69C5D0u + 24 * kinds[ki] + 20);
        for (u32 off = 0; off < psize; off += 4) CHECK(r32(m, c + 64 + off) == r32(m, params + off));
        const auto& log = g_t.world[1]->si.log;
        int ci = -1, ii = -1;
        for (std::size_t i = 0; i < log.size(); ++i) {
            if (log[i].va == slots[ki][1]) {
                ci = static_cast<int>(i);
                CHECK(static_cast<u32>(log[i].args[0]) == params);
            }
            if (log[i].va == slots[ki][0]) {
                ii = static_cast<int>(i);
                CHECK(static_cast<u32>(log[i].args[0]) == c);
            }
        }
        CHECK(ci >= 0);
        CHECK(ii > ci);  // create before init
    }
}

// The instance allocators of classes 12 / 10 / 16: frame 0, kind, colour -1, scale (1, 1, 1, 1), the parameters at
// +80; class 12's runs the kind's create and init (kind 2: sub_3385D0 / sub_338530 stood in), the other two none.
TEST_CASE("game(fx2): the class 12 / 10 / 16 instance allocators") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 params = 0x01F22000u;
    struct A {
        const char* fn;
        u32 kind;
        u32 size_slot;  // where the kind row keeps the parameter size
    };
    const A as[] = {{"sub_3393D0", 2, 0x69C650u + 24 * 2 + 20}, {"sub_341F10", 4, 0x69C850u + 28 * 4 + 24},
                    {"sub_341F10", 8, 0x69C850u + 28 * 8 + 24}, {"sub_345CF0", 1, 0x69C970u + 28 * 1 + 24},
                    {"sub_345CF0", 3, 0x69C970u + 28 * 3 + 24}};
    for (const A& a : as) {
        for (u32 i = 0; i < 128; ++i) w32(m, params + 4 * i, 0xFACE0000u + i);
        Opt o;
        o.standins = true;
        o.setup = fx_world();
        const hgp::Run r = fx_pair(m, a.fn, Args{a.kind, sx(params), 0, 0}, 7, a.fn, o);
        const u32 c = static_cast<u32>(v0_of(r));
        CHECK(r32(m, c + fx2::kC12Frame) == 0);
        CHECK(r32(m, c + fx2::kC12Kind) == a.kind);
        CHECK(r32(m, c + fx2::kC12Colour) == 0xFFFFFFFFu);
        for (u32 k = 0; k < 4; ++k) CHECK(rf(m, c + fx2::kC12Scale + 4 * k) == 1.0f);
        for (u32 k = 0; k < 8; ++k)  // position and rotation = vf0 = (0, 0, 0, 1)
            CHECK(r32(m, c + 4 * k) == (k % 4 == 3 ? 0x3F800000u : 0u));
        CHECK(r32(m, c + fx2::kC12Params) == c + 80);
        const u32 psize = r32(m, a.size_slot);
        for (u32 off = 0; off < psize; off += 4) CHECK(r32(m, c + 80 + off) == r32(m, params + off));
        const bool c12 = std::string(a.fn) == "sub_3393D0";
        CHECK(g_t.world[1]->si.calls_to(0x3385D0u) == (c12 ? 1u : 0u));
        CHECK(g_t.world[1]->si.calls_to(0x338530u) == (c12 ? 1u : 0u));
        if (c12) CHECK(r32(m, c + fx2::kC12Obj) == 0x01F41000u);
    }
}

// sub_333300 [fxStripsSetColour]: both meshes' ribbon colour = the RGBA bytes, an alpha of 255 written as 254 (and the
// source restored to 255): the fx_types finding 5 on the ribbon meshes.
TEST_CASE("game(fx2): the ribbon colour copy writes alpha 255 as 254") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 strips = 0x01F20000u, meshA = strips + 0x100, meshB = strips + 0x200, rgba = strips + 0x300;
    for (u32 alpha : {0u, 1u, 128u, 254u, 255u}) {
        for (u32 ribbon : {0u, 3u}) {
            std::memset(m.at(strips), 0, 0x1000);
            w32(m, strips + fx2::kStMeshA, meshA);
            w32(m, strips + fx2::kStMeshB, meshB);
            w32(m, meshA + fx2::kMeshColours, strips + 0x400);
            w32(m, meshB + fx2::kMeshColours, strips + 0x480);
            for (u32 i = 0; i < 8; ++i) {
                w32(m, strips + 0x400 + 4 * i, strips + 0x500 + 16 * i);
                w32(m, strips + 0x480 + 4 * i, strips + 0x600 + 16 * i);
            }
            w32(m, rgba, 0x00305070u | (alpha << 24));
            fx_pair(m, "sub_333300", Args{sx(strips), ribbon, sx(rgba), 0}, 9 + alpha, "ribbon colour");
            const u32 want = 0x00305070u | ((alpha == 255 ? 254u : alpha) << 24);
            CHECK(r32(m, strips + 0x500 + 16 * ribbon + 4) == want);
            CHECK(r32(m, strips + 0x600 + 16 * ribbon + 4) == want);
            CHECK(r32(m, rgba) == (0x00305070u | (alpha << 24)));  // the source is restored
        }
    }
}

// Screen filter kind 1 (class 4) and class 5's kind 1 on frame 0: the output rectangle is the whole 640 x 448 screen
// (class 4 also its centre 320, 224), the layer word is copied; past the duration the output alpha byte is cleared.
TEST_CASE("game(fx2): the full-screen filter kinds on frame 0 and past their duration") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 inst = 0x01F20000u, params = inst + 48;
    for (const char* fn : {"sub_349870", "sub_34AC70"}) {
        for (s32 frame : {0, 3, 40}) {
            std::memset(m.at(inst), 0, 0x400);
            w32(m, inst + fx2::kFltParams, params);
            w32(m, inst + fx2::kFltFrame, static_cast<u32>(frame));
            w32(m, inst + fx2::kFltColour, 0x80808080u);
            w32(m, params + fx2::kFpDuration, 20);
            w32(m, params + fx2::kFpLayer, 0x12345678u);
            w32(m, params + 192, 0xAAAAAAAAu);
            Opt o;
            o.standins = true;
            o.setup = fx_world();
            const hgp::Run r = fx_pair(m, fn, Args{sx(inst), 0, 0, 0}, 11 + frame, fn, o);
            if (r.stopped) continue;
            const bool c4 = std::string(fn) == "sub_349870";
            if (frame == 0) {
                if (c4) {
                    CHECK(rf(m, params + 208) == 320.0f);
                    CHECK(rf(m, params + 212) == 224.0f);
                    CHECK(rf(m, params + 216) == 0.0f);
                    CHECK(rf(m, params + 220) == 0.0f);
                    CHECK(rf(m, params + 224) == 640.0f);
                    CHECK(rf(m, params + 228) == 448.0f);
                    CHECK(r32(m, params + 196) == 0x12345678u);
                } else {
                    CHECK(rf(m, params + 200) == 0.0f);
                    CHECK(rf(m, params + 204) == 0.0f);
                    CHECK(rf(m, params + 208) == 640.0f);
                    CHECK(rf(m, params + 212) == 448.0f);
                    CHECK(r32(m, params + 196) == 0x12345678u);
                }
            }
            if (frame > 20) CHECK(r8(m, params + 195) == 0);  // past the duration: alpha of the output colour cleared
        }
    }
}

// The texture reference of the filters: sub_34BBC0 makes {type, 1, texture} (type 1: the texture by name, fx_layers'
// sub_3210C0; types other than 1 / 4: no texture); sub_34BC80 drops a count (the texture destroy and the free at zero
// run through RwTextureDestroy, replaced elsewhere, and the heap stand-in: the pair compares them).
TEST_CASE("game(fx2): the filter texture reference count") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 block = 0x01F20000u;
    for (u32 type : {1u, 2u, 3u}) {
        Opt o;
        o.standins = true;
        o.setup = fx_world();
        const hgp::Run r = fx_pair(m, "sub_34BBC0", Args{sx(block), type, 0, 0}, 13, "tex ref create", o);
        if (r.stopped) continue;
        const u32 ref = static_cast<u32>(v0_of(r));
        CHECK(r32(m, ref) == type);
        CHECK(r32(m, ref + 4) == 1);
        if (type != 1) CHECK(r32(m, ref + 8) == 0u);
    }
    const u32 ref = 0x01F21000u;
    for (u32 type : {1u, 4u}) {
        for (u32 count : {1u, 2u, 3u}) {
            w32(m, ref, type);
            w32(m, ref + 4, count);
            w32(m, ref + 8, 0x01F23000u);
            Opt o;
            o.standins = true;
            o.setup = fx_world();
            const hgp::Run r = fx_pair(m, "sub_34BC80", Args{sx(ref), 0, 0, 0}, 14 + count, "tex ref release", o);
            if (r.stopped) continue;
            CHECK(r32(m, ref + 4) == count - 1);
        }
    }
}

// The filter update slots (classes 4 / 5): the kind's update (row +8 of 0x69CB90 / 0x69CC50, stood in) on the
// instance, then ++frame (the layer queue from frame 1 on is fx_layers' sub_321180 / sub_3211D0: compared by the pair).
TEST_CASE("game(fx2): the filter update slots count the frame and queue from frame 1") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 inst = 0x01F20000u, params = inst + 48;
    struct F {
        const char* fn;
        u32 queue;
        u32 kind;
        u32 update;
    };
    const F fs[] = {{"sub_34B600", 0x321180u, 3, 0x349FD0u}, {"sub_34BB10", 0x3211D0u, 2, 0x34AE30u}};
    for (const F& f : fs) {
        for (s32 frame : {-2, -1, 0, 4}) {
            std::memset(m.at(inst), 0, 0x400);
            w32(m, inst + fx2::kFltKind, f.kind);
            w32(m, inst + fx2::kFltFrame, static_cast<u32>(frame));
            w32(m, inst + fx2::kFltParams, params);
            w16(m, params + 40, 7);
            w32(m, params + 184, 100);
            Opt o;
            o.standins = true;
            o.setup = fx_world();
            const hgp::Run r = fx_pair(m, f.fn, Args{sx(inst), 0, 0, 0}, 17 + frame, f.fn, o);
            if (r.stopped) continue;
            CHECK(r32(m, inst + fx2::kFltFrame) == static_cast<u32>(frame + 1));
            CHECK(g_t.world[1]->si.calls_to(f.update) == 1u);
            for (const StandInCall& c : g_t.world[1]->si.log)
                if (c.va == f.update) CHECK(static_cast<u32>(c.args[0]) == inst);
        }
    }
}

// sub_348340 [fltQuadUvRotated]: 0 for a rectangle off the 640 x 448 screen; otherwise 1 and four vertices with the
// near-screen z (0x960088), rhw = 1 / the camera's far plane, the colour bytes as floats, the rectangle's corners.
TEST_CASE("game(fx2): the filter quad builder") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    const u32 out = 0x01F20000u, verts = 0x01F21000u;
    wf(m, 0x957BACu, 640.0f);  // the screen size globals of fx_types' sub_34BD10 (.bss: zero in the ELF image)
    wf(m, 0x957BB0u, 448.0f);
    struct R {
        float x0, y0, x1, y1;
        bool on;
    };
    const R rs[] = {{10, 20, 100, 200, true}, {700, 20, 100, 200, false}, {10, 500, 100, 200, false},
                    {10, 20, -5, 200, false}, {0, 0, 640, 448, true}};
    for (const R& rr : rs) {
        for (float angle : {0.0f, 0.5f}) {
            std::memset(m.at(out), 0, 0x100);
            std::memset(m.at(verts), 0, 0x100);
            w32(m, out, 0x40302010u);
            wf(m, out + 8, angle);
            wf(m, out + 12, 1.0f);
            wf(m, out + 16, 320.0f);
            wf(m, out + 20, 224.0f);
            wf(m, out + 24, rr.x0);
            wf(m, out + 28, rr.y0);
            wf(m, out + 32, rr.x1);
            wf(m, out + 36, rr.y1);
            Opt o;
            o.standins = true;
            o.setup = fx_world();
            const hgp::Run r = fx_pair(m, "sub_348340", Args{sx(out), sx(verts), 0, 0}, 19, "filter quad", o);
            if (r.stopped) continue;  // the camera getter (sub_198590) when this library does not emit it
            CHECK(static_cast<u32>(v0_of(r)) == (rr.on ? 1u : 0u));
            if (!rr.on) continue;
            for (u32 v = 0; v < 4; ++v) {
                CHECK(r32(m, verts + 64 * v + 8) == r32(m, 0x960088u));
                CHECK(rf(m, verts + 64 * v + 32) == 16.0f);
                CHECK(rf(m, verts + 64 * v + 44) == 64.0f);
            }
            CHECK(rf(m, verts + 0) == rr.x0);
            CHECK(rf(m, verts + 4) == rr.y0);
            CHECK(rf(m, verts + 64 * 2 + 0) == rr.x1);
            CHECK(rf(m, verts + 64 * 2 + 4) == rr.y1);
        }
    }
}

TEST_CASE("game(fx2): pair count") { MESSAGE("fx2 pairs run (outside the random-world case): " << g_pairs); }

#else

TEST_CASE("game(fx2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
