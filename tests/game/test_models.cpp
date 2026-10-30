// Pair tests of the models slice (game/src/model/models.cpp): every hand body against its recompiled body.
//   1. Random worlds (tests/game/handgen_pairs.h): all 150 functions, the whole register file and cycles at every check
//      point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log.
//   2. Built model records (ModelWorld below): model lists per kind, the four animation slots with animation sets
//      (real, empty and placeholder entries), hierarchies and interpolators, clumps with frames, the alternative and
//      material animation records, helper tables, effect lists, sound records, pending load requests, an attached
//      child -- in the stand-in heap arena, reserved in every run's heap, so the create / clone / destroy / detach /
//      load paths allocate and free real blocks. Pairs through run_pair_si (stand_ins.h: the guest heap, the H_Cdvd
//      layer, printf / sprintf, recorders for the callees no test library emits); a world the original itself faults
//      on compares the two bodies' faults.
//   3. Documented rules on the results of both bodies: the record mdlModelCreate builds, the list walk of
//      mdlModelFind, the slot queries against the animation sets, the setters, the NPC file names (story substitutions,
//      the June-September outfits), the party-member NPC numbers, the packed kinds' archive names, the sound-bank LRU,
//      the keyframe curves.
//   4. The replay snapshots (extracted/_ours: b_5800, battle_ref_6150, dorm_replay_4900, climb_ref_17000 when present):
//      the model API on the live records of real routes (party members, enemies, map objects, NPCs, weapons on helpers).
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function, one function, a trace line per pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/hcdvd.h"
#include "p3fes/game/models.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game::mdl;

namespace p3fes::recomp_gen {
void fn_sub_311310_00311310(EEContext&);  // generated body
void fn_sub_311310_00311310__recomp(EEContext&);  // recompiled
void fn_sub_311480_00311480(EEContext&);  // generated body
void fn_sub_311480_00311480__recomp(EEContext&);  // recompiled
void fn_sub_3115A0_003115a0(EEContext&);  // generated body
void fn_sub_3115A0_003115a0__recomp(EEContext&);  // recompiled
void fn_sub_311610_00311610(EEContext&);  // generated body
void fn_sub_311610_00311610__recomp(EEContext&);  // recompiled
void fn_sub_311640_00311640(EEContext&);  // generated body
void fn_sub_311640_00311640__recomp(EEContext&);  // recompiled
void fn_sub_312C70_00312c70(EEContext&);  // generated body
void fn_sub_312C70_00312c70__recomp(EEContext&);  // recompiled
void fn_sub_312D40_00312d40(EEContext&);  // generated body
void fn_sub_312D40_00312d40__recomp(EEContext&);  // recompiled
void fn_mdlManagerSetMaterialMatFxPipeline_00312e80(EEContext&);  // generated body
void fn_mdlManagerSetMaterialMatFxPipeline_00312e80__recomp(EEContext&);  // recompiled
void fn_mdlManagerSetClumpPipelines_00312f90(EEContext&);  // generated body
void fn_mdlManagerSetClumpPipelines_00312f90__recomp(EEContext&);  // recompiled
void fn_sub_313090_00313090(EEContext&);  // generated body
void fn_sub_313090_00313090__recomp(EEContext&);  // recompiled
void fn_sub_313230_00313230(EEContext&);  // generated body
void fn_sub_313230_00313230__recomp(EEContext&);  // recompiled
void fn_sub_3132C0_003132c0(EEContext&);  // generated body
void fn_sub_3132C0_003132c0__recomp(EEContext&);  // recompiled
void fn_sub_313BE0_00313be0(EEContext&);  // generated body
void fn_sub_313BE0_00313be0__recomp(EEContext&);  // recompiled
void fn_sub_313CA0_00313ca0(EEContext&);  // generated body
void fn_sub_313CA0_00313ca0__recomp(EEContext&);  // recompiled
void fn_sub_313E60_00313e60(EEContext&);  // generated body
void fn_sub_313E60_00313e60__recomp(EEContext&);  // recompiled
void fn_sub_313F40_00313f40(EEContext&);  // generated body
void fn_sub_313F40_00313f40__recomp(EEContext&);  // recompiled
void fn_sub_313FE0_00313fe0(EEContext&);  // generated body
void fn_sub_313FE0_00313fe0__recomp(EEContext&);  // recompiled
void fn_sub_314020_00314020(EEContext&);  // generated body
void fn_sub_314020_00314020__recomp(EEContext&);  // recompiled
void fn_sub_314060_00314060(EEContext&);  // generated body
void fn_sub_314060_00314060__recomp(EEContext&);  // recompiled
void fn_sub_3140C0_003140c0(EEContext&);  // generated body
void fn_sub_3140C0_003140c0__recomp(EEContext&);  // recompiled
void fn_sub_314170_00314170(EEContext&);  // generated body
void fn_sub_314170_00314170__recomp(EEContext&);  // recompiled
void fn_sub_3142B0_003142b0(EEContext&);  // generated body
void fn_sub_3142B0_003142b0__recomp(EEContext&);  // recompiled
void fn_sub_3143C0_003143c0(EEContext&);  // generated body
void fn_sub_3143C0_003143c0__recomp(EEContext&);  // recompiled
void fn_sub_314510_00314510(EEContext&);  // generated body
void fn_sub_314510_00314510__recomp(EEContext&);  // recompiled
void fn_sub_314650_00314650(EEContext&);  // generated body
void fn_sub_314650_00314650__recomp(EEContext&);  // recompiled
void fn_sub_314730_00314730(EEContext&);  // generated body
void fn_sub_314730_00314730__recomp(EEContext&);  // recompiled
void fn_sub_315010_00315010(EEContext&);  // generated body
void fn_sub_315010_00315010__recomp(EEContext&);  // recompiled
void fn_sub_315090_00315090(EEContext&);  // generated body
void fn_sub_315090_00315090__recomp(EEContext&);  // recompiled
void fn_sub_315ED0_00315ed0(EEContext&);  // generated body
void fn_sub_315ED0_00315ed0__recomp(EEContext&);  // recompiled
void fn_sub_315F50_00315f50(EEContext&);  // generated body
void fn_sub_315F50_00315f50__recomp(EEContext&);  // recompiled
void fn_sub_316320_00316320(EEContext&);  // generated body
void fn_sub_316320_00316320__recomp(EEContext&);  // recompiled
void fn_sub_316360_00316360(EEContext&);  // generated body
void fn_sub_316360_00316360__recomp(EEContext&);  // recompiled
void fn_sub_316410_00316410(EEContext&);  // generated body
void fn_sub_316410_00316410__recomp(EEContext&);  // recompiled
void fn_sub_3164C0_003164c0(EEContext&);  // generated body
void fn_sub_3164C0_003164c0__recomp(EEContext&);  // recompiled
void fn_sub_3164F0_003164f0(EEContext&);  // generated body
void fn_sub_3164F0_003164f0__recomp(EEContext&);  // recompiled
void fn_sub_3165E0_003165e0(EEContext&);  // generated body
void fn_sub_3165E0_003165e0__recomp(EEContext&);  // recompiled
void fn_sub_316690_00316690(EEContext&);  // generated body
void fn_sub_316690_00316690__recomp(EEContext&);  // recompiled
void fn_sub_316910_00316910(EEContext&);  // generated body
void fn_sub_316910_00316910__recomp(EEContext&);  // recompiled
void fn_sub_316970_00316970(EEContext&);  // generated body
void fn_sub_316970_00316970__recomp(EEContext&);  // recompiled
void fn_sub_316B40_00316b40(EEContext&);  // generated body
void fn_sub_316B40_00316b40__recomp(EEContext&);  // recompiled
void fn_sub_316BD0_00316bd0(EEContext&);  // generated body
void fn_sub_316BD0_00316bd0__recomp(EEContext&);  // recompiled
void fn_sub_316C70_00316c70(EEContext&);  // generated body
void fn_sub_316C70_00316c70__recomp(EEContext&);  // recompiled
void fn_sub_317450_00317450(EEContext&);  // generated body
void fn_sub_317450_00317450__recomp(EEContext&);  // recompiled
void fn_sub_3174E0_003174e0(EEContext&);  // generated body
void fn_sub_3174E0_003174e0__recomp(EEContext&);  // recompiled
void fn_sub_3176C0_003176c0(EEContext&);  // generated body
void fn_sub_3176C0_003176c0__recomp(EEContext&);  // recompiled
void fn_sub_3182D0_003182d0(EEContext&);  // generated body
void fn_sub_3182D0_003182d0__recomp(EEContext&);  // recompiled
void fn_sub_318540_00318540(EEContext&);  // generated body
void fn_sub_318540_00318540__recomp(EEContext&);  // recompiled
void fn_sub_3185B0_003185b0(EEContext&);  // generated body
void fn_sub_3185B0_003185b0__recomp(EEContext&);  // recompiled
void fn_sub_318620_00318620(EEContext&);  // generated body
void fn_sub_318620_00318620__recomp(EEContext&);  // recompiled
void fn_sub_3186E0_003186e0(EEContext&);  // generated body
void fn_sub_3186E0_003186e0__recomp(EEContext&);  // recompiled
void fn_sub_318770_00318770(EEContext&);  // generated body
void fn_sub_318770_00318770__recomp(EEContext&);  // recompiled
void fn_sub_318870_00318870(EEContext&);  // generated body
void fn_sub_318870_00318870__recomp(EEContext&);  // recompiled
void fn_sub_318910_00318910(EEContext&);  // generated body
void fn_sub_318910_00318910__recomp(EEContext&);  // recompiled
void fn_sub_318990_00318990(EEContext&);  // generated body
void fn_sub_318990_00318990__recomp(EEContext&);  // recompiled
void fn_sub_3189F0_003189f0(EEContext&);  // generated body
void fn_sub_3189F0_003189f0__recomp(EEContext&);  // recompiled
void fn_sub_318A30_00318a30(EEContext&);  // generated body
void fn_sub_318A30_00318a30__recomp(EEContext&);  // recompiled
void fn_sub_318A50_00318a50(EEContext&);  // generated body
void fn_sub_318A50_00318a50__recomp(EEContext&);  // recompiled
void fn_sub_318A70_00318a70(EEContext&);  // generated body
void fn_sub_318A70_00318a70__recomp(EEContext&);  // recompiled
void fn_sub_318A90_00318a90(EEContext&);  // generated body
void fn_sub_318A90_00318a90__recomp(EEContext&);  // recompiled
void fn_sub_318AD0_00318ad0(EEContext&);  // generated body
void fn_sub_318AD0_00318ad0__recomp(EEContext&);  // recompiled
void fn_sub_318B00_00318b00(EEContext&);  // generated body
void fn_sub_318B00_00318b00__recomp(EEContext&);  // recompiled
void fn_sub_318B10_00318b10(EEContext&);  // generated body
void fn_sub_318B10_00318b10__recomp(EEContext&);  // recompiled
void fn_sub_318B60_00318b60(EEContext&);  // generated body
void fn_sub_318B60_00318b60__recomp(EEContext&);  // recompiled
void fn_sub_318B70_00318b70(EEContext&);  // generated body
void fn_sub_318B70_00318b70__recomp(EEContext&);  // recompiled
void fn_sub_318B80_00318b80(EEContext&);  // generated body
void fn_sub_318B80_00318b80__recomp(EEContext&);  // recompiled
void fn_sub_318B90_00318b90(EEContext&);  // generated body
void fn_sub_318B90_00318b90__recomp(EEContext&);  // recompiled
void fn_sub_318D10_00318d10(EEContext&);  // generated body
void fn_sub_318D10_00318d10__recomp(EEContext&);  // recompiled
void fn_sub_318ED0_00318ed0(EEContext&);  // generated body
void fn_sub_318ED0_00318ed0__recomp(EEContext&);  // recompiled
void fn_sub_318FC0_00318fc0(EEContext&);  // generated body
void fn_sub_318FC0_00318fc0__recomp(EEContext&);  // recompiled
void fn_sub_319010_00319010(EEContext&);  // generated body
void fn_sub_319010_00319010__recomp(EEContext&);  // recompiled
void fn_sub_319030_00319030(EEContext&);  // generated body
void fn_sub_319030_00319030__recomp(EEContext&);  // recompiled
void fn_sub_319050_00319050(EEContext&);  // generated body
void fn_sub_319050_00319050__recomp(EEContext&);  // recompiled
void fn_sub_319070_00319070(EEContext&);  // generated body
void fn_sub_319070_00319070__recomp(EEContext&);  // recompiled
void fn_sub_319090_00319090(EEContext&);  // generated body
void fn_sub_319090_00319090__recomp(EEContext&);  // recompiled
void fn_sub_3190A0_003190a0(EEContext&);  // generated body
void fn_sub_3190A0_003190a0__recomp(EEContext&);  // recompiled
void fn_sub_3190B0_003190b0(EEContext&);  // generated body
void fn_sub_3190B0_003190b0__recomp(EEContext&);  // recompiled
void fn_sub_319100_00319100(EEContext&);  // generated body
void fn_sub_319100_00319100__recomp(EEContext&);  // recompiled
void fn_sub_319150_00319150(EEContext&);  // generated body
void fn_sub_319150_00319150__recomp(EEContext&);  // recompiled
void fn_sub_319190_00319190(EEContext&);  // generated body
void fn_sub_319190_00319190__recomp(EEContext&);  // recompiled
void fn_sub_3191B0_003191b0(EEContext&);  // generated body
void fn_sub_3191B0_003191b0__recomp(EEContext&);  // recompiled
void fn_sub_3191D0_003191d0(EEContext&);  // generated body
void fn_sub_3191D0_003191d0__recomp(EEContext&);  // recompiled
void fn_sub_3191F0_003191f0(EEContext&);  // generated body
void fn_sub_3191F0_003191f0__recomp(EEContext&);  // recompiled
void fn_sub_319200_00319200(EEContext&);  // generated body
void fn_sub_319200_00319200__recomp(EEContext&);  // recompiled
void fn_sub_319210_00319210(EEContext&);  // generated body
void fn_sub_319210_00319210__recomp(EEContext&);  // recompiled
void fn_sub_319230_00319230(EEContext&);  // generated body
void fn_sub_319230_00319230__recomp(EEContext&);  // recompiled
void fn_sub_3192A0_003192a0(EEContext&);  // generated body
void fn_sub_3192A0_003192a0__recomp(EEContext&);  // recompiled
void fn_sub_319390_00319390(EEContext&);  // generated body
void fn_sub_319390_00319390__recomp(EEContext&);  // recompiled
void fn_sub_319490_00319490(EEContext&);  // generated body
void fn_sub_319490_00319490__recomp(EEContext&);  // recompiled
void fn_sub_3195F0_003195f0(EEContext&);  // generated body
void fn_sub_3195F0_003195f0__recomp(EEContext&);  // recompiled
void fn_sub_3196D0_003196d0(EEContext&);  // generated body
void fn_sub_3196D0_003196d0__recomp(EEContext&);  // recompiled
void fn_sub_3196F0_003196f0(EEContext&);  // generated body
void fn_sub_3196F0_003196f0__recomp(EEContext&);  // recompiled
void fn_sub_319770_00319770(EEContext&);  // generated body
void fn_sub_319770_00319770__recomp(EEContext&);  // recompiled
void fn_sub_3197C0_003197c0(EEContext&);  // generated body
void fn_sub_3197C0_003197c0__recomp(EEContext&);  // recompiled
void fn_sub_319840_00319840(EEContext&);  // generated body
void fn_sub_319840_00319840__recomp(EEContext&);  // recompiled
void fn_sub_3198A0_003198a0(EEContext&);  // generated body
void fn_sub_3198A0_003198a0__recomp(EEContext&);  // recompiled
void fn_sub_3198C0_003198c0(EEContext&);  // generated body
void fn_sub_3198C0_003198c0__recomp(EEContext&);  // recompiled
void fn_sub_319900_00319900(EEContext&);  // generated body
void fn_sub_319900_00319900__recomp(EEContext&);  // recompiled
void fn_sub_319910_00319910(EEContext&);  // generated body
void fn_sub_319910_00319910__recomp(EEContext&);  // recompiled
void fn_sub_31B220_0031b220(EEContext&);  // generated body
void fn_sub_31B220_0031b220__recomp(EEContext&);  // recompiled
void fn_sub_31B470_0031b470(EEContext&);  // generated body
void fn_sub_31B470_0031b470__recomp(EEContext&);  // recompiled
void fn_sub_31B4A0_0031b4a0(EEContext&);  // generated body
void fn_sub_31B4A0_0031b4a0__recomp(EEContext&);  // recompiled
void fn_sub_31B680_0031b680(EEContext&);  // generated body
void fn_sub_31B680_0031b680__recomp(EEContext&);  // recompiled
void fn_sub_31BE80_0031be80(EEContext&);  // generated body
void fn_sub_31BE80_0031be80__recomp(EEContext&);  // recompiled
void fn_sub_31C000_0031c000(EEContext&);  // generated body
void fn_sub_31C000_0031c000__recomp(EEContext&);  // recompiled
void fn_sub_31C7E0_0031c7e0(EEContext&);  // generated body
void fn_sub_31C7E0_0031c7e0__recomp(EEContext&);  // recompiled
void fn_sub_31D4F0_0031d4f0(EEContext&);  // generated body
void fn_sub_31D4F0_0031d4f0__recomp(EEContext&);  // recompiled
void fn_sub_31D530_0031d530(EEContext&);  // generated body
void fn_sub_31D530_0031d530__recomp(EEContext&);  // recompiled
void fn_sub_31D6B0_0031d6b0(EEContext&);  // generated body
void fn_sub_31D6B0_0031d6b0__recomp(EEContext&);  // recompiled
void fn_sub_31D700_0031d700(EEContext&);  // generated body
void fn_sub_31D700_0031d700__recomp(EEContext&);  // recompiled
void fn_sub_31D790_0031d790(EEContext&);  // generated body
void fn_sub_31D790_0031d790__recomp(EEContext&);  // recompiled
void fn_sub_31D7D0_0031d7d0(EEContext&);  // generated body
void fn_sub_31D7D0_0031d7d0__recomp(EEContext&);  // recompiled
void fn_sub_31D7E0_0031d7e0(EEContext&);  // generated body
void fn_sub_31D7E0_0031d7e0__recomp(EEContext&);  // recompiled
void fn_sub_31D900_0031d900(EEContext&);  // generated body
void fn_sub_31D900_0031d900__recomp(EEContext&);  // recompiled
void fn_sub_31D9C0_0031d9c0(EEContext&);  // generated body
void fn_sub_31D9C0_0031d9c0__recomp(EEContext&);  // recompiled
void fn_sub_31DC80_0031dc80(EEContext&);  // generated body
void fn_sub_31DC80_0031dc80__recomp(EEContext&);  // recompiled
void fn_sub_31DCE0_0031dce0(EEContext&);  // generated body
void fn_sub_31DCE0_0031dce0__recomp(EEContext&);  // recompiled
void fn_sub_31DD40_0031dd40(EEContext&);  // generated body
void fn_sub_31DD40_0031dd40__recomp(EEContext&);  // recompiled
void fn_sub_31DDA0_0031dda0(EEContext&);  // generated body
void fn_sub_31DDA0_0031dda0__recomp(EEContext&);  // recompiled
void fn_sub_31DE30_0031de30(EEContext&);  // generated body
void fn_sub_31DE30_0031de30__recomp(EEContext&);  // recompiled
void fn_sub_31DED0_0031ded0(EEContext&);  // generated body
void fn_sub_31DED0_0031ded0__recomp(EEContext&);  // recompiled
void fn_sub_31DF80_0031df80(EEContext&);  // generated body
void fn_sub_31DF80_0031df80__recomp(EEContext&);  // recompiled
void fn_sub_31DFF0_0031dff0(EEContext&);  // generated body
void fn_sub_31DFF0_0031dff0__recomp(EEContext&);  // recompiled
void fn_sub_31E0B0_0031e0b0(EEContext&);  // generated body
void fn_sub_31E0B0_0031e0b0__recomp(EEContext&);  // recompiled
void fn_sub_31E130_0031e130(EEContext&);  // generated body
void fn_sub_31E130_0031e130__recomp(EEContext&);  // recompiled
void fn_sub_31E1B0_0031e1b0(EEContext&);  // generated body
void fn_sub_31E1B0_0031e1b0__recomp(EEContext&);  // recompiled
void fn_sub_31E1E0_0031e1e0(EEContext&);  // generated body
void fn_sub_31E1E0_0031e1e0__recomp(EEContext&);  // recompiled
void fn_sub_31E210_0031e210(EEContext&);  // generated body
void fn_sub_31E210_0031e210__recomp(EEContext&);  // recompiled
void fn_sub_31E240_0031e240(EEContext&);  // generated body
void fn_sub_31E240_0031e240__recomp(EEContext&);  // recompiled
void fn_sub_31E270_0031e270(EEContext&);  // generated body
void fn_sub_31E270_0031e270__recomp(EEContext&);  // recompiled
void fn_sub_31E2C0_0031e2c0(EEContext&);  // generated body
void fn_sub_31E2C0_0031e2c0__recomp(EEContext&);  // recompiled
void fn_sub_31E300_0031e300(EEContext&);  // generated body
void fn_sub_31E300_0031e300__recomp(EEContext&);  // recompiled
void fn_sub_31E310_0031e310(EEContext&);  // generated body
void fn_sub_31E310_0031e310__recomp(EEContext&);  // recompiled
void fn_sub_31E420_0031e420(EEContext&);  // generated body
void fn_sub_31E420_0031e420__recomp(EEContext&);  // recompiled
void fn_sub_31EBE0_0031ebe0(EEContext&);  // generated body
void fn_sub_31EBE0_0031ebe0__recomp(EEContext&);  // recompiled
void fn_sub_31EE80_0031ee80(EEContext&);  // generated body
void fn_sub_31EE80_0031ee80__recomp(EEContext&);  // recompiled
void fn_sub_31EEB0_0031eeb0(EEContext&);  // generated body
void fn_sub_31EEB0_0031eeb0__recomp(EEContext&);  // recompiled
void fn_sub_31EEE0_0031eee0(EEContext&);  // generated body
void fn_sub_31EEE0_0031eee0__recomp(EEContext&);  // recompiled
void fn_sub_31F5C0_0031f5c0(EEContext&);  // generated body
void fn_sub_31F5C0_0031f5c0__recomp(EEContext&);  // recompiled
void fn_sub_31F6D0_0031f6d0(EEContext&);  // generated body
void fn_sub_31F6D0_0031f6d0__recomp(EEContext&);  // recompiled
void fn_sub_31F740_0031f740(EEContext&);  // generated body
void fn_sub_31F740_0031f740__recomp(EEContext&);  // recompiled
void fn_sub_31F7A0_0031f7a0(EEContext&);  // generated body
void fn_sub_31F7A0_0031f7a0__recomp(EEContext&);  // recompiled
void fn_sub_31F870_0031f870(EEContext&);  // generated body
void fn_sub_31F870_0031f870__recomp(EEContext&);  // recompiled
void fn_sub_31F9D0_0031f9d0(EEContext&);  // generated body
void fn_sub_31F9D0_0031f9d0__recomp(EEContext&);  // recompiled
void fn_sub_31FAF0_0031faf0(EEContext&);  // generated body
void fn_sub_31FAF0_0031faf0__recomp(EEContext&);  // recompiled
void fn_sub_31FBD0_0031fbd0(EEContext&);  // generated body
void fn_sub_31FBD0_0031fbd0__recomp(EEContext&);  // recompiled
void fn_sub_31FD00_0031fd00(EEContext&);  // generated body
void fn_sub_31FD00_0031fd00__recomp(EEContext&);  // recompiled
void fn_sub_31FDE0_0031fde0(EEContext&);  // generated body
void fn_sub_31FDE0_0031fde0__recomp(EEContext&);  // recompiled
void fn_sub_31FF40_0031ff40(EEContext&);  // generated body
void fn_sub_31FF40_0031ff40__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_311310", 0x311310, &recomp_gen::fn_sub_311310_00311310, &recomp_gen::fn_sub_311310_00311310__recomp},
    {"sub_311480", 0x311480, &recomp_gen::fn_sub_311480_00311480, &recomp_gen::fn_sub_311480_00311480__recomp},
    {"sub_3115A0", 0x3115A0, &recomp_gen::fn_sub_3115A0_003115a0, &recomp_gen::fn_sub_3115A0_003115a0__recomp},
    {"sub_311610", 0x311610, &recomp_gen::fn_sub_311610_00311610, &recomp_gen::fn_sub_311610_00311610__recomp},
    {"sub_311640", 0x311640, &recomp_gen::fn_sub_311640_00311640, &recomp_gen::fn_sub_311640_00311640__recomp},
    {"sub_312C70", 0x312C70, &recomp_gen::fn_sub_312C70_00312c70, &recomp_gen::fn_sub_312C70_00312c70__recomp},
    {"sub_312D40", 0x312D40, &recomp_gen::fn_sub_312D40_00312d40, &recomp_gen::fn_sub_312D40_00312d40__recomp},
    {"mdlManagerSetMaterialMatFxPipeline", 0x312E80, &recomp_gen::fn_mdlManagerSetMaterialMatFxPipeline_00312e80, &recomp_gen::fn_mdlManagerSetMaterialMatFxPipeline_00312e80__recomp},
    {"mdlManagerSetClumpPipelines", 0x312F90, &recomp_gen::fn_mdlManagerSetClumpPipelines_00312f90, &recomp_gen::fn_mdlManagerSetClumpPipelines_00312f90__recomp},
    {"sub_313090", 0x313090, &recomp_gen::fn_sub_313090_00313090, &recomp_gen::fn_sub_313090_00313090__recomp},
    {"sub_313230", 0x313230, &recomp_gen::fn_sub_313230_00313230, &recomp_gen::fn_sub_313230_00313230__recomp},
    {"sub_3132C0", 0x3132C0, &recomp_gen::fn_sub_3132C0_003132c0, &recomp_gen::fn_sub_3132C0_003132c0__recomp},
    {"sub_313BE0", 0x313BE0, &recomp_gen::fn_sub_313BE0_00313be0, &recomp_gen::fn_sub_313BE0_00313be0__recomp},
    {"sub_313CA0", 0x313CA0, &recomp_gen::fn_sub_313CA0_00313ca0, &recomp_gen::fn_sub_313CA0_00313ca0__recomp},
    {"sub_313E60", 0x313E60, &recomp_gen::fn_sub_313E60_00313e60, &recomp_gen::fn_sub_313E60_00313e60__recomp},
    {"sub_313F40", 0x313F40, &recomp_gen::fn_sub_313F40_00313f40, &recomp_gen::fn_sub_313F40_00313f40__recomp},
    {"sub_313FE0", 0x313FE0, &recomp_gen::fn_sub_313FE0_00313fe0, &recomp_gen::fn_sub_313FE0_00313fe0__recomp},
    {"sub_314020", 0x314020, &recomp_gen::fn_sub_314020_00314020, &recomp_gen::fn_sub_314020_00314020__recomp},
    {"sub_314060", 0x314060, &recomp_gen::fn_sub_314060_00314060, &recomp_gen::fn_sub_314060_00314060__recomp},
    {"sub_3140C0", 0x3140C0, &recomp_gen::fn_sub_3140C0_003140c0, &recomp_gen::fn_sub_3140C0_003140c0__recomp},
    {"sub_314170", 0x314170, &recomp_gen::fn_sub_314170_00314170, &recomp_gen::fn_sub_314170_00314170__recomp},
    {"sub_3142B0", 0x3142B0, &recomp_gen::fn_sub_3142B0_003142b0, &recomp_gen::fn_sub_3142B0_003142b0__recomp},
    {"sub_3143C0", 0x3143C0, &recomp_gen::fn_sub_3143C0_003143c0, &recomp_gen::fn_sub_3143C0_003143c0__recomp},
    {"sub_314510", 0x314510, &recomp_gen::fn_sub_314510_00314510, &recomp_gen::fn_sub_314510_00314510__recomp},
    {"sub_314650", 0x314650, &recomp_gen::fn_sub_314650_00314650, &recomp_gen::fn_sub_314650_00314650__recomp},
    {"sub_314730", 0x314730, &recomp_gen::fn_sub_314730_00314730, &recomp_gen::fn_sub_314730_00314730__recomp},
    {"sub_315010", 0x315010, &recomp_gen::fn_sub_315010_00315010, &recomp_gen::fn_sub_315010_00315010__recomp},
    {"sub_315090", 0x315090, &recomp_gen::fn_sub_315090_00315090, &recomp_gen::fn_sub_315090_00315090__recomp},
    {"sub_315ED0", 0x315ED0, &recomp_gen::fn_sub_315ED0_00315ed0, &recomp_gen::fn_sub_315ED0_00315ed0__recomp},
    {"sub_315F50", 0x315F50, &recomp_gen::fn_sub_315F50_00315f50, &recomp_gen::fn_sub_315F50_00315f50__recomp},
    {"sub_316320", 0x316320, &recomp_gen::fn_sub_316320_00316320, &recomp_gen::fn_sub_316320_00316320__recomp},
    {"sub_316360", 0x316360, &recomp_gen::fn_sub_316360_00316360, &recomp_gen::fn_sub_316360_00316360__recomp},
    {"sub_316410", 0x316410, &recomp_gen::fn_sub_316410_00316410, &recomp_gen::fn_sub_316410_00316410__recomp},
    {"sub_3164C0", 0x3164C0, &recomp_gen::fn_sub_3164C0_003164c0, &recomp_gen::fn_sub_3164C0_003164c0__recomp},
    {"sub_3164F0", 0x3164F0, &recomp_gen::fn_sub_3164F0_003164f0, &recomp_gen::fn_sub_3164F0_003164f0__recomp},
    {"sub_3165E0", 0x3165E0, &recomp_gen::fn_sub_3165E0_003165e0, &recomp_gen::fn_sub_3165E0_003165e0__recomp},
    {"sub_316690", 0x316690, &recomp_gen::fn_sub_316690_00316690, &recomp_gen::fn_sub_316690_00316690__recomp},
    {"sub_316910", 0x316910, &recomp_gen::fn_sub_316910_00316910, &recomp_gen::fn_sub_316910_00316910__recomp},
    {"sub_316970", 0x316970, &recomp_gen::fn_sub_316970_00316970, &recomp_gen::fn_sub_316970_00316970__recomp},
    {"sub_316B40", 0x316B40, &recomp_gen::fn_sub_316B40_00316b40, &recomp_gen::fn_sub_316B40_00316b40__recomp},
    {"sub_316BD0", 0x316BD0, &recomp_gen::fn_sub_316BD0_00316bd0, &recomp_gen::fn_sub_316BD0_00316bd0__recomp},
    {"sub_316C70", 0x316C70, &recomp_gen::fn_sub_316C70_00316c70, &recomp_gen::fn_sub_316C70_00316c70__recomp},
    {"sub_317450", 0x317450, &recomp_gen::fn_sub_317450_00317450, &recomp_gen::fn_sub_317450_00317450__recomp},
    {"sub_3174E0", 0x3174E0, &recomp_gen::fn_sub_3174E0_003174e0, &recomp_gen::fn_sub_3174E0_003174e0__recomp},
    {"sub_3176C0", 0x3176C0, &recomp_gen::fn_sub_3176C0_003176c0, &recomp_gen::fn_sub_3176C0_003176c0__recomp},
    {"sub_3182D0", 0x3182D0, &recomp_gen::fn_sub_3182D0_003182d0, &recomp_gen::fn_sub_3182D0_003182d0__recomp},
    {"sub_318540", 0x318540, &recomp_gen::fn_sub_318540_00318540, &recomp_gen::fn_sub_318540_00318540__recomp},
    {"sub_3185B0", 0x3185B0, &recomp_gen::fn_sub_3185B0_003185b0, &recomp_gen::fn_sub_3185B0_003185b0__recomp},
    {"sub_318620", 0x318620, &recomp_gen::fn_sub_318620_00318620, &recomp_gen::fn_sub_318620_00318620__recomp},
    {"sub_3186E0", 0x3186E0, &recomp_gen::fn_sub_3186E0_003186e0, &recomp_gen::fn_sub_3186E0_003186e0__recomp},
    {"sub_318770", 0x318770, &recomp_gen::fn_sub_318770_00318770, &recomp_gen::fn_sub_318770_00318770__recomp},
    {"sub_318870", 0x318870, &recomp_gen::fn_sub_318870_00318870, &recomp_gen::fn_sub_318870_00318870__recomp},
    {"sub_318910", 0x318910, &recomp_gen::fn_sub_318910_00318910, &recomp_gen::fn_sub_318910_00318910__recomp},
    {"sub_318990", 0x318990, &recomp_gen::fn_sub_318990_00318990, &recomp_gen::fn_sub_318990_00318990__recomp},
    {"sub_3189F0", 0x3189F0, &recomp_gen::fn_sub_3189F0_003189f0, &recomp_gen::fn_sub_3189F0_003189f0__recomp},
    {"sub_318A30", 0x318A30, &recomp_gen::fn_sub_318A30_00318a30, &recomp_gen::fn_sub_318A30_00318a30__recomp},
    {"sub_318A50", 0x318A50, &recomp_gen::fn_sub_318A50_00318a50, &recomp_gen::fn_sub_318A50_00318a50__recomp},
    {"sub_318A70", 0x318A70, &recomp_gen::fn_sub_318A70_00318a70, &recomp_gen::fn_sub_318A70_00318a70__recomp},
    {"sub_318A90", 0x318A90, &recomp_gen::fn_sub_318A90_00318a90, &recomp_gen::fn_sub_318A90_00318a90__recomp},
    {"sub_318AD0", 0x318AD0, &recomp_gen::fn_sub_318AD0_00318ad0, &recomp_gen::fn_sub_318AD0_00318ad0__recomp},
    {"sub_318B00", 0x318B00, &recomp_gen::fn_sub_318B00_00318b00, &recomp_gen::fn_sub_318B00_00318b00__recomp},
    {"sub_318B10", 0x318B10, &recomp_gen::fn_sub_318B10_00318b10, &recomp_gen::fn_sub_318B10_00318b10__recomp},
    {"sub_318B60", 0x318B60, &recomp_gen::fn_sub_318B60_00318b60, &recomp_gen::fn_sub_318B60_00318b60__recomp},
    {"sub_318B70", 0x318B70, &recomp_gen::fn_sub_318B70_00318b70, &recomp_gen::fn_sub_318B70_00318b70__recomp},
    {"sub_318B80", 0x318B80, &recomp_gen::fn_sub_318B80_00318b80, &recomp_gen::fn_sub_318B80_00318b80__recomp},
    {"sub_318B90", 0x318B90, &recomp_gen::fn_sub_318B90_00318b90, &recomp_gen::fn_sub_318B90_00318b90__recomp},
    {"sub_318D10", 0x318D10, &recomp_gen::fn_sub_318D10_00318d10, &recomp_gen::fn_sub_318D10_00318d10__recomp},
    {"sub_318ED0", 0x318ED0, &recomp_gen::fn_sub_318ED0_00318ed0, &recomp_gen::fn_sub_318ED0_00318ed0__recomp},
    {"sub_318FC0", 0x318FC0, &recomp_gen::fn_sub_318FC0_00318fc0, &recomp_gen::fn_sub_318FC0_00318fc0__recomp},
    {"sub_319010", 0x319010, &recomp_gen::fn_sub_319010_00319010, &recomp_gen::fn_sub_319010_00319010__recomp},
    {"sub_319030", 0x319030, &recomp_gen::fn_sub_319030_00319030, &recomp_gen::fn_sub_319030_00319030__recomp},
    {"sub_319050", 0x319050, &recomp_gen::fn_sub_319050_00319050, &recomp_gen::fn_sub_319050_00319050__recomp},
    {"sub_319070", 0x319070, &recomp_gen::fn_sub_319070_00319070, &recomp_gen::fn_sub_319070_00319070__recomp},
    {"sub_319090", 0x319090, &recomp_gen::fn_sub_319090_00319090, &recomp_gen::fn_sub_319090_00319090__recomp},
    {"sub_3190A0", 0x3190A0, &recomp_gen::fn_sub_3190A0_003190a0, &recomp_gen::fn_sub_3190A0_003190a0__recomp},
    {"sub_3190B0", 0x3190B0, &recomp_gen::fn_sub_3190B0_003190b0, &recomp_gen::fn_sub_3190B0_003190b0__recomp},
    {"sub_319100", 0x319100, &recomp_gen::fn_sub_319100_00319100, &recomp_gen::fn_sub_319100_00319100__recomp},
    {"sub_319150", 0x319150, &recomp_gen::fn_sub_319150_00319150, &recomp_gen::fn_sub_319150_00319150__recomp},
    {"sub_319190", 0x319190, &recomp_gen::fn_sub_319190_00319190, &recomp_gen::fn_sub_319190_00319190__recomp},
    {"sub_3191B0", 0x3191B0, &recomp_gen::fn_sub_3191B0_003191b0, &recomp_gen::fn_sub_3191B0_003191b0__recomp},
    {"sub_3191D0", 0x3191D0, &recomp_gen::fn_sub_3191D0_003191d0, &recomp_gen::fn_sub_3191D0_003191d0__recomp},
    {"sub_3191F0", 0x3191F0, &recomp_gen::fn_sub_3191F0_003191f0, &recomp_gen::fn_sub_3191F0_003191f0__recomp},
    {"sub_319200", 0x319200, &recomp_gen::fn_sub_319200_00319200, &recomp_gen::fn_sub_319200_00319200__recomp},
    {"sub_319210", 0x319210, &recomp_gen::fn_sub_319210_00319210, &recomp_gen::fn_sub_319210_00319210__recomp},
    {"sub_319230", 0x319230, &recomp_gen::fn_sub_319230_00319230, &recomp_gen::fn_sub_319230_00319230__recomp},
    {"sub_3192A0", 0x3192A0, &recomp_gen::fn_sub_3192A0_003192a0, &recomp_gen::fn_sub_3192A0_003192a0__recomp},
    {"sub_319390", 0x319390, &recomp_gen::fn_sub_319390_00319390, &recomp_gen::fn_sub_319390_00319390__recomp},
    {"sub_319490", 0x319490, &recomp_gen::fn_sub_319490_00319490, &recomp_gen::fn_sub_319490_00319490__recomp},
    {"sub_3195F0", 0x3195F0, &recomp_gen::fn_sub_3195F0_003195f0, &recomp_gen::fn_sub_3195F0_003195f0__recomp},
    {"sub_3196D0", 0x3196D0, &recomp_gen::fn_sub_3196D0_003196d0, &recomp_gen::fn_sub_3196D0_003196d0__recomp},
    {"sub_3196F0", 0x3196F0, &recomp_gen::fn_sub_3196F0_003196f0, &recomp_gen::fn_sub_3196F0_003196f0__recomp},
    {"sub_319770", 0x319770, &recomp_gen::fn_sub_319770_00319770, &recomp_gen::fn_sub_319770_00319770__recomp},
    {"sub_3197C0", 0x3197C0, &recomp_gen::fn_sub_3197C0_003197c0, &recomp_gen::fn_sub_3197C0_003197c0__recomp},
    {"sub_319840", 0x319840, &recomp_gen::fn_sub_319840_00319840, &recomp_gen::fn_sub_319840_00319840__recomp},
    {"sub_3198A0", 0x3198A0, &recomp_gen::fn_sub_3198A0_003198a0, &recomp_gen::fn_sub_3198A0_003198a0__recomp},
    {"sub_3198C0", 0x3198C0, &recomp_gen::fn_sub_3198C0_003198c0, &recomp_gen::fn_sub_3198C0_003198c0__recomp},
    {"sub_319900", 0x319900, &recomp_gen::fn_sub_319900_00319900, &recomp_gen::fn_sub_319900_00319900__recomp},
    {"sub_319910", 0x319910, &recomp_gen::fn_sub_319910_00319910, &recomp_gen::fn_sub_319910_00319910__recomp},
    {"sub_31B220", 0x31B220, &recomp_gen::fn_sub_31B220_0031b220, &recomp_gen::fn_sub_31B220_0031b220__recomp},
    {"sub_31B470", 0x31B470, &recomp_gen::fn_sub_31B470_0031b470, &recomp_gen::fn_sub_31B470_0031b470__recomp},
    {"sub_31B4A0", 0x31B4A0, &recomp_gen::fn_sub_31B4A0_0031b4a0, &recomp_gen::fn_sub_31B4A0_0031b4a0__recomp},
    {"sub_31B680", 0x31B680, &recomp_gen::fn_sub_31B680_0031b680, &recomp_gen::fn_sub_31B680_0031b680__recomp},
    {"sub_31BE80", 0x31BE80, &recomp_gen::fn_sub_31BE80_0031be80, &recomp_gen::fn_sub_31BE80_0031be80__recomp},
    {"sub_31C000", 0x31C000, &recomp_gen::fn_sub_31C000_0031c000, &recomp_gen::fn_sub_31C000_0031c000__recomp},
    {"sub_31C7E0", 0x31C7E0, &recomp_gen::fn_sub_31C7E0_0031c7e0, &recomp_gen::fn_sub_31C7E0_0031c7e0__recomp},
    {"sub_31D4F0", 0x31D4F0, &recomp_gen::fn_sub_31D4F0_0031d4f0, &recomp_gen::fn_sub_31D4F0_0031d4f0__recomp},
    {"sub_31D530", 0x31D530, &recomp_gen::fn_sub_31D530_0031d530, &recomp_gen::fn_sub_31D530_0031d530__recomp},
    {"sub_31D6B0", 0x31D6B0, &recomp_gen::fn_sub_31D6B0_0031d6b0, &recomp_gen::fn_sub_31D6B0_0031d6b0__recomp},
    {"sub_31D700", 0x31D700, &recomp_gen::fn_sub_31D700_0031d700, &recomp_gen::fn_sub_31D700_0031d700__recomp},
    {"sub_31D790", 0x31D790, &recomp_gen::fn_sub_31D790_0031d790, &recomp_gen::fn_sub_31D790_0031d790__recomp},
    {"sub_31D7D0", 0x31D7D0, &recomp_gen::fn_sub_31D7D0_0031d7d0, &recomp_gen::fn_sub_31D7D0_0031d7d0__recomp},
    {"sub_31D7E0", 0x31D7E0, &recomp_gen::fn_sub_31D7E0_0031d7e0, &recomp_gen::fn_sub_31D7E0_0031d7e0__recomp},
    {"sub_31D900", 0x31D900, &recomp_gen::fn_sub_31D900_0031d900, &recomp_gen::fn_sub_31D900_0031d900__recomp},
    {"sub_31D9C0", 0x31D9C0, &recomp_gen::fn_sub_31D9C0_0031d9c0, &recomp_gen::fn_sub_31D9C0_0031d9c0__recomp},
    {"sub_31DC80", 0x31DC80, &recomp_gen::fn_sub_31DC80_0031dc80, &recomp_gen::fn_sub_31DC80_0031dc80__recomp},
    {"sub_31DCE0", 0x31DCE0, &recomp_gen::fn_sub_31DCE0_0031dce0, &recomp_gen::fn_sub_31DCE0_0031dce0__recomp},
    {"sub_31DD40", 0x31DD40, &recomp_gen::fn_sub_31DD40_0031dd40, &recomp_gen::fn_sub_31DD40_0031dd40__recomp},
    {"sub_31DDA0", 0x31DDA0, &recomp_gen::fn_sub_31DDA0_0031dda0, &recomp_gen::fn_sub_31DDA0_0031dda0__recomp},
    {"sub_31DE30", 0x31DE30, &recomp_gen::fn_sub_31DE30_0031de30, &recomp_gen::fn_sub_31DE30_0031de30__recomp},
    {"sub_31DED0", 0x31DED0, &recomp_gen::fn_sub_31DED0_0031ded0, &recomp_gen::fn_sub_31DED0_0031ded0__recomp},
    {"sub_31DF80", 0x31DF80, &recomp_gen::fn_sub_31DF80_0031df80, &recomp_gen::fn_sub_31DF80_0031df80__recomp},
    {"sub_31DFF0", 0x31DFF0, &recomp_gen::fn_sub_31DFF0_0031dff0, &recomp_gen::fn_sub_31DFF0_0031dff0__recomp},
    {"sub_31E0B0", 0x31E0B0, &recomp_gen::fn_sub_31E0B0_0031e0b0, &recomp_gen::fn_sub_31E0B0_0031e0b0__recomp},
    {"sub_31E130", 0x31E130, &recomp_gen::fn_sub_31E130_0031e130, &recomp_gen::fn_sub_31E130_0031e130__recomp},
    {"sub_31E1B0", 0x31E1B0, &recomp_gen::fn_sub_31E1B0_0031e1b0, &recomp_gen::fn_sub_31E1B0_0031e1b0__recomp},
    {"sub_31E1E0", 0x31E1E0, &recomp_gen::fn_sub_31E1E0_0031e1e0, &recomp_gen::fn_sub_31E1E0_0031e1e0__recomp},
    {"sub_31E210", 0x31E210, &recomp_gen::fn_sub_31E210_0031e210, &recomp_gen::fn_sub_31E210_0031e210__recomp},
    {"sub_31E240", 0x31E240, &recomp_gen::fn_sub_31E240_0031e240, &recomp_gen::fn_sub_31E240_0031e240__recomp},
    {"sub_31E270", 0x31E270, &recomp_gen::fn_sub_31E270_0031e270, &recomp_gen::fn_sub_31E270_0031e270__recomp},
    {"sub_31E2C0", 0x31E2C0, &recomp_gen::fn_sub_31E2C0_0031e2c0, &recomp_gen::fn_sub_31E2C0_0031e2c0__recomp},
    {"sub_31E300", 0x31E300, &recomp_gen::fn_sub_31E300_0031e300, &recomp_gen::fn_sub_31E300_0031e300__recomp},
    {"sub_31E310", 0x31E310, &recomp_gen::fn_sub_31E310_0031e310, &recomp_gen::fn_sub_31E310_0031e310__recomp},
    {"sub_31E420", 0x31E420, &recomp_gen::fn_sub_31E420_0031e420, &recomp_gen::fn_sub_31E420_0031e420__recomp},
    {"sub_31EBE0", 0x31EBE0, &recomp_gen::fn_sub_31EBE0_0031ebe0, &recomp_gen::fn_sub_31EBE0_0031ebe0__recomp},
    {"sub_31EE80", 0x31EE80, &recomp_gen::fn_sub_31EE80_0031ee80, &recomp_gen::fn_sub_31EE80_0031ee80__recomp},
    {"sub_31EEB0", 0x31EEB0, &recomp_gen::fn_sub_31EEB0_0031eeb0, &recomp_gen::fn_sub_31EEB0_0031eeb0__recomp},
    {"sub_31EEE0", 0x31EEE0, &recomp_gen::fn_sub_31EEE0_0031eee0, &recomp_gen::fn_sub_31EEE0_0031eee0__recomp},
    {"sub_31F5C0", 0x31F5C0, &recomp_gen::fn_sub_31F5C0_0031f5c0, &recomp_gen::fn_sub_31F5C0_0031f5c0__recomp},
    {"sub_31F6D0", 0x31F6D0, &recomp_gen::fn_sub_31F6D0_0031f6d0, &recomp_gen::fn_sub_31F6D0_0031f6d0__recomp},
    {"sub_31F740", 0x31F740, &recomp_gen::fn_sub_31F740_0031f740, &recomp_gen::fn_sub_31F740_0031f740__recomp},
    {"sub_31F7A0", 0x31F7A0, &recomp_gen::fn_sub_31F7A0_0031f7a0, &recomp_gen::fn_sub_31F7A0_0031f7a0__recomp},
    {"sub_31F870", 0x31F870, &recomp_gen::fn_sub_31F870_0031f870, &recomp_gen::fn_sub_31F870_0031f870__recomp},
    {"sub_31F9D0", 0x31F9D0, &recomp_gen::fn_sub_31F9D0_0031f9d0, &recomp_gen::fn_sub_31F9D0_0031f9d0__recomp},
    {"sub_31FAF0", 0x31FAF0, &recomp_gen::fn_sub_31FAF0_0031faf0, &recomp_gen::fn_sub_31FAF0_0031faf0__recomp},
    {"sub_31FBD0", 0x31FBD0, &recomp_gen::fn_sub_31FBD0_0031fbd0, &recomp_gen::fn_sub_31FBD0_0031fbd0__recomp},
    {"sub_31FD00", 0x31FD00, &recomp_gen::fn_sub_31FD00_0031fd00, &recomp_gen::fn_sub_31FD00_0031fd00__recomp},
    {"sub_31FDE0", 0x31FDE0, &recomp_gen::fn_sub_31FDE0_0031fde0, &recomp_gen::fn_sub_31FDE0_0031fde0__recomp},
    {"sub_31FF40", 0x31FF40, &recomp_gen::fn_sub_31FF40_0031ff40, &recomp_gen::fn_sub_31FF40_0031ff40__recomp},
};

// The random worlds: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;  // P3FES_HG_SEEDS overrides

// --- shared helpers ----------------------------------------------------------------------------------------------

Machine* machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        write_rw_slots(*mm);
        return mm;
    }();
    return m;
}

#define NEED_MACHINE()                                                  \
    Machine* mp = machine();                                            \
    if (!mp) {                                                          \
        MESSAGE("SKIP: no ELF at " << elf_path());                      \
        return;                                                         \
    }                                                                   \
    Machine& m = *mp

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    static const Case none{"?", 0, nullptr, nullptr};
    FAIL("no case " << name);
    return none;
}

void w8(Machine& m, u32 va, u32 v) { *m.at(va) = static_cast<u8>(v); }
void w16(Machine& m, u32 va, u32 v) {
    const u16 x = static_cast<u16>(v);
    std::memcpy(m.at(va), &x, 2);
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u32 r16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
s32 rs16(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
float rf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
float as_float(u32 bits) {
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}

constexpr u32 kLists = 0x9571F0u;      // gMdlLists[12]
constexpr u32 kDummyAnim = 0x9571D0u;  // gMdlDummyAnim
constexpr u32 kFlagWords = 0x83A21Cu;  // datGetFlag's 176-word flag array (ui_tables.cpp)
constexpr u32 kDays = 0x83679Cu;       // datGetDaysSinceApr5's s16 (ui.h)
constexpr u32 kScenario = 0x7CDFA4u;   // sub_17D800's word: 1 = The Answer (ui2.h)
constexpr u32 kPathVa = kStandInHeap + 0x2F0000u;  // a model path in the world (outside the world's blocks)

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// The callees no test library emits (tests/game/CMakeLists.txt) that the slice's bodies call: recorders (they log the
// call and return 0), so a pair runs past them instead of stopping. The H_Cdvd requests / destroy / read-sync, printf
// and sprintf are install_standard's; the hand-written callees (H_Cdvd_IsFileLoaded / ArchiveGetFile, datGetFlag,
// RpPDSGetPipe, the matrix ops, the effect-node API) always run for real.
constexpr u32 kRecorded[] = {0x109ae0, 0x109df0, 0x10a0e0, 0x10a240, 0x1a14c0, 0x1a6400, 0x1a6c00, 0x1a7170, 0x1a7570,
                             0x1a7710, 0x1b5a30, 0x1b5ae0, 0x1eda00, 0x1eda90, 0x1eded0, 0x1ee1d0, 0x1ee220, 0x1ee230,
                             0x1ef340, 0x311730, 0x3138e0, 0x314850, 0x3170c0, 0x319970, 0x31aad0, 0x31b820, 0x31e8d0,
                             0x31ef80, 0x320290, 0x320380, 0x3204a0, 0x320640, 0x320770, 0x320810, 0x4663d0, 0x466480,
                             0x466710, 0x466ef0, 0x468dc0, 0x469510, 0x48a2a0, 0x48a2c0, 0x48a3d0, 0x48a3f0, 0x48a480,
                             0x48ee80, 0x48eed0, 0x48ef80, 0x4916d0, 0x491ea0, 0x4932c0, 0x4b6980, 0x4b6eb0, 0x4b7010,
                             0x4b78b0, 0x4c1d50, 0x4c5780, 0x4c58a0, 0x524670,
                             0x324bd0,   // the effect-node create behind the hand-written sub_34FCD0
                             0x1a6860,   // the user-data frame search behind sub_1A69A0 (per3HelperId)
                             0x316e00, 0x316f70};  // left recompiled (test_field_hi's walks stop at them)

// sub_31C820 (the model file name, not in this slice): writes "model/player/bc%03X.RMD" for (type, id) into $a2.
void install_path_builder(StandInWorld& w) {
    w.si.install(0x31C820u, "sub_31C820", [](EEContext& ctx, StandIns&, StandInCall& call) {
        char buf[64];
        std::snprintf(buf, sizeof buf, "model/player/bc%03X.RMD", static_cast<unsigned>(call.args[1] & 0xFFFF));
        const u32 out = static_cast<u32>(call.args[2]);
        std::memcpy(ctx.memory->main_ram() + out, buf, std::strlen(buf) + 1);
        call.text = buf;
        call.v0 = 0;
    });
}

void install_models_world(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "recorded", 0);
    install_path_builder(w);
}

// --- a world of model records -----------------------------------------------------------------------------------
// Built by the host in the stand-in heap arena (above the blocks the stand-in heap hands out) and reserved in each run's
// heap, so the destroy paths free real blocks. Every field is one the slice's bodies read (models.h names them).
struct ModelWorld {
    static constexpr u32 kBase = kStandInHeap + 0x200000u;
    u32 next = kBase;
    std::vector<std::pair<u32, u32>> blocks;
    std::vector<u32> models;   // every record
    std::vector<u32> anims;    // animations: +12 duration (seconds)
    std::vector<u32> lists;    // effect lists (heads)
    std::vector<u32> sounds;   // sound records (model + kMdlSound)
    std::vector<u32> afx;      // after-effect handles
    std::vector<u32> matrices; // free 64-byte matrices for the matrix functions
    std::vector<u32> curves;   // {count, ., key size, keys*} curves (8-byte scalar keys / 16-byte vec3 keys)
    std::vector<u32> vec3s;    // three floats each
    u32 rgba = 0;

    u32 alloc(Machine& m, u32 size) {
        const u32 p = next;
        next += (size + 15u) & ~15u;
        std::memset(m.at(p), 0, size);
        blocks.emplace_back(p, (size + 15u) & ~15u);
        return p;
    }
    void identity(Machine& m, u32 p, std::mt19937& rng) {
        for (u32 i = 0; i < 16; ++i) wf(m, p + 4 * i, 0.0f);
        wf(m, p, 1.0f);
        wf(m, p + 20, 1.0f);
        wf(m, p + 40, 1.0f);
        for (u32 i = 0; i < 3; ++i) wf(m, p + 48 + 4 * i, static_cast<float>(static_cast<int>(rng() % 200) - 100));
        w32(m, p + 12, 0x20003u);
    }
    WorldSetup setup() const {
        const auto b = blocks;
        return [b](StandInWorld& w) {
            install_models_world(w);
            for (const auto& [p, n] : b) w.heap.reserve(p, n);
        };
    }
    u32 model(std::mt19937& rng) const { return models[rng() % models.size()]; }
};

ModelWorld build_world(Machine& m, std::mt19937& rng) {
    ModelWorld W;
    std::memset(m.at(kLists), 0, 4 * kMdlListCount);
    // the whole stand-in heap arena and a clean H_Cdvd request list / cache (FakeCd keeps them in guest memory): every
    // world starts from the same bytes, whatever the pairs before it left there
    std::memset(m.at(kStandInHeap), 0, kStandInHeapSize);
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
    for (int k = 0; k < 8; ++k) {
        const u32 a = W.alloc(m, 32);
        wf(m, a + 12, 0.5f * static_cast<float>(k + 1));
        W.anims.push_back(a);
    }
    auto anim_set = [&](u32 n) {
        const u32 s = W.alloc(m, 16 + kSetEntrySize * n);
        w32(m, s + kSetEntries, s + 16);
        w16(m, s + kSetCount, n);
        w16(m, s + kSetRefs, 1 + rng() % 2);
        for (u32 i = 0; i < n; ++i) {
            const u32 e = s + 16 + kSetEntrySize * i;
            W.identity(m, e, rng);
            const u32 r = rng() % 6;
            w32(m, e + kEntAnim, r == 0 ? 0u : r == 1 ? kDummyAnim : W.anims[rng() % W.anims.size()]);
            w32(m, e + kEntFlags, rng() % 4 == 0 ? 1u : 0u);
        }
        return s;
    };
    auto fx_list = [&](u32 n) {
        const u32 head = W.alloc(m, 4);
        u32 prev = 0;
        for (u32 i = 0; i < n; ++i) {
            const u32 def = W.alloc(m, 32);
            w32(m, def + kFxDefData, def + 16);
            w32(m, def + kFxDefRefs, 1);
            w32(m, def + kFxDefFlags, rng() % 2);
            const u32 node = W.alloc(m, 20);
            w32(m, node + kFxDef, def);
            w16(m, node + kFxHelper, rng() % 4);
            w32(m, node + kFxPrev, prev);
            if (prev) w32(m, prev + kFxNext, node);
            else w32(m, head, node);
            prev = node;
        }
        W.lists.push_back(head);
        return head;
    };
    const u32 kinds[] = {1, 1, 2, 4, 5, 5, 7};
    const u32 ids[] = {1, 2, 5, 37, 225, 58, 172};
    const int n = 5 + static_cast<int>(rng() % 3);
    for (int i = 0; i < n; ++i) {
        const u32 md = W.alloc(m, kMdlSize);
        const u32 kind = kinds[rng() % 7];
        const u32 id = ids[rng() % 7];
        W.identity(m, md + kMdlPlace, rng);
        W.identity(m, md + kMdlRootOffset, rng);
        for (u32 k = 0; k < 3; ++k) wf(m, md + kMdlScale + 4 * k, 1.0f);
        for (u32 k = 0; k < 4; ++k) w8(m, md + kMdlColour + k, rng());
        w16(m, md + kMdlType, kind);
        w16(m, md + kMdlId, id);
        u32 flags = 0x118 | (rng() % 4 != 0 ? 0x1000u : 0u);
        if (rng() % 5 == 0) flags |= 0x2000;
        if (rng() % 3 == 0) flags |= 0x1;
        w16(m, md + kMdlFlags, flags);
        if (rng() % 6 != 0) {  // a clump with its frame (root = itself, clean)
            const u32 clump = W.alloc(m, 0x40);
            const u32 frame = W.alloc(m, 0xC0);
            W.identity(m, frame + 16, rng);
            W.identity(m, frame + 80, rng);
            w32(m, frame + 0xA0, frame);
            w32(m, clump + 4, frame);
            w32(m, md + kMdlClump, clump);
        }
        for (u32 s = 0; s < kMdlSlotCount; ++s) {
            const u32 sl = md + kMdlSlots + kSlotSize * s;
            w16(m, sl + kSlotFlags, rng() & 0x13);
            w8(m, sl + kSlotDone, rng() % 2);
            wf(m, sl + kSlotSpeed, 1.0f);
            wf(m, sl + kSlotTime, 0.1f * static_cast<float>(rng() % 30));
            wf(m, sl + kSlotBlend, rng() % 3 == 0 ? 0.5f : 1.0f);
            w16(m, sl + kSlotPrevAnim, 0xFFFF);
            wf(m, sl + kSlotLookSpeed, 0.2f);
            wf(m, sl + kSlotLookYaw, 70.0f);
            wf(m, sl + kSlotLookPitch, 80.0f);
            const bool animated = s == 0 ? rng() % 5 != 0 : rng() % 6 == 0;
            if (animated) {
                const u32 cnt = 1 + rng() % 5;
                w32(m, sl + kSlotSet, anim_set(cnt));
                w16(m, sl + kSlotAnim, static_cast<u32>(static_cast<int>(rng() % (cnt + 2)) - 1));
                const u32 hier = W.alloc(m, 0x50);
                const u32 interp = W.alloc(m, 0x60);
                w32(m, interp, W.anims[rng() % W.anims.size()]);
                w32(m, hier + 32, rng() % 5 == 0 ? 0u : interp);
                w32(m, sl + kSlotHier, hier);
            } else {
                w16(m, sl + kSlotAnim, 0xFFFF);
            }
        }
        w8(m, md + kMdlMatAnim + kSlotDone, 1);
        w16(m, md + kMdlMatAnim + kSlotAnim, 0xFFFF);
        wf(m, md + kMdlMatAnim + kSlotSpeed, 1.0f);
        if (rng() % 4 == 0) {  // the alternative (0x320xxx) animations of slot 0
            const u32 cnt = 1 + rng() % 3;
            const u32 alt = W.alloc(m, 16 + 8 * cnt);
            w32(m, alt, alt + 16);
            w16(m, alt + 4, cnt);
            w16(m, alt + 6, 1);
            for (u32 k = 0; k < cnt; ++k) w32(m, alt + 16 + 8 * k, rng() % 3 == 0 ? 0u : W.anims[k]);
            w32(m, md + kMdlAltAnim, alt);
        }
        if (rng() % 3 == 0) {  // a helper table
            const u32 cnt = 1 + rng() % 4;
            const u32 tab = W.alloc(m, 8);
            const u32 ent = W.alloc(m, kSetEntrySize * cnt);
            w16(m, tab, cnt);
            w16(m, tab + 2, 1 + rng() % 2);
            w32(m, tab + 4, ent);
            for (u32 k = 0; k < cnt; ++k) {
                W.identity(m, ent + kSetEntrySize * k, rng);
                w32(m, ent + kSetEntrySize * k + 64, k);
                w32(m, ent + kSetEntrySize * k + 68, rng() % 2);
            }
            w32(m, md + kMdlHelpers, tab);
        }
        if (rng() % 3 == 0) w32(m, md + kMdlFxList, fx_list(1 + rng() % 3));
        // the sound record: no bank, or a loaded / pending bank
        const u32 snd = md + kMdlSound;
        w16(m, snd + 12, 0xFFFF);
        w16(m, snd + 28, 0xFFFF);
        w16(m, snd + 30, 0xFFFF);
        w16(m, snd + 6, 0x20);
        if (rng() % 3 == 0) {
            const u32 bank = W.alloc(m, 32);
            w32(m, bank + 4, 1 + rng() % 2);
            w16(m, bank + 8, 1 + rng() % 2);
            w16(m, bank + 14, rng() % 2 == 0 ? 0x5u : 0x0u);
            w32(m, snd, bank);
            w16(m, snd + 12, rng() % 3);
            w16(m, snd + 28, static_cast<u32>(static_cast<int>(rng() % 4) - 2));
        }
        W.sounds.push_back(snd);
        w16(m, md + kMdlLayer, 2);
        // a pending load request now and then
        if (!(flags & 0x1000) && rng() % 2 == 0) {
            const u32 ld = W.alloc(m, 80);
            w8(m, ld + kLdState, 4 + rng() % 2);
            w32(m, md + kMdlLoad, ld);
        }
        // link at the head of its list
        const u32 head = r32(m, kLists + 4 * kind);
        w32(m, md + kMdlNext, head);
        if (head) w32(m, head + kMdlPrev, md);
        w32(m, kLists + 4 * kind, md);
        W.models.push_back(md);
    }
    // attachments: the first model carries the last one (a weapon) on its helper 1
    if (W.models.size() >= 2) {
        const u32 parent = W.models.front(), child = W.models.back();
        w8(m, parent + kMdlAttach + kAttachSize * 1 + kAttFlags, 1);
        w32(m, parent + kMdlAttach + kAttachSize * 1 + kAttChild, child);
        w32(m, parent + kMdlAttach + kAttachSize * 1 + kAttHelper, 1);
        w16(m, child + kMdlFlags, r16(m, child + kMdlFlags) | 0x8004u);
    }
    for (int k = 0; k < 4; ++k) {
        const u32 mx = W.alloc(m, 64);
        W.identity(m, mx, rng);
        W.matrices.push_back(mx);
    }
    for (int k = 0; k < 4; ++k) {
        const u32 v = W.alloc(m, 16);
        for (u32 i = 0; i < 3; ++i) wf(m, v + 4 * i, 0.25f * static_cast<float>(static_cast<int>(rng() % 9) - 4));
        W.vec3s.push_back(v);
    }
    if (W.lists.empty()) fx_list(1 + rng() % 2);  // a list for the list functions even when no model has one
    m.put(kPathVa, "model/npc/n00058.RMD");
    W.rgba = W.alloc(m, 4);
    w32(m, W.rgba, rng());
    for (int k = 0; k < 3; ++k) {  // after-effect handles over a blob
        const u32 blob = W.alloc(m, 32);
        w32(m, blob, blob + 16);
        w32(m, blob + 4, 1 + rng() % 2);
        const u32 h = W.alloc(m, 8);
        w32(m, h, blob);
        W.afx.push_back(h);
    }
    for (int k = 0; k < 2; ++k) {  // keyframe curves: scalar (8-byte keys) and vec3 (16-byte keys)
        const u32 cnt = 2 + rng() % 4, size = k == 0 ? 8u : 16u;
        const u32 c = W.alloc(m, 16), keys = W.alloc(m, size * cnt);
        w32(m, c, cnt);
        w32(m, c + 8, size);
        w32(m, c + 12, keys);
        for (u32 i = 0; i < cnt; ++i) {
            wf(m, keys + size * i, static_cast<float>(i));
            for (u32 j = 4; j < size; j += 4) wf(m, keys + size * i + j, 0.1f * static_cast<float>(rng() % 20));
        }
        W.curves.push_back(c);
    }
    return W;
}

// One pair on the world; a world the original itself faults on compares the two faults (each body alone).
struct Tally {
    int pairs = 0, faults = 0;
    std::map<std::string, int> kinds;  // the fault messages
};
std::map<std::string, Tally> g_tally;

// `restore` puts the pair's starting RAM back (a fault leaves the RAM half-written).
void pair_checked(Machine& m, const Case& c, const Args& a, u32 seed, const HwCheck& hw, const WorldSetup& setup,
                  const std::function<void()>& restore) {
    Tally& t = g_tally[c.name];
    ++t.pairs;
    std::string in_pair;
    try {
        run_pair_si(m, c.hand, c.recomp, a, seed, c.name, hw, setup);
        return;
    } catch (const rt_test::FatalEvent& e) {
        in_pair = std::to_string(e.pc) + ": " + e.what;
    }
    ++t.faults;
    auto alone = [&](Fn fn) {
        restore();
        StandInWorld w;
        setup(w);
        StandInsScope scope(w.si);
        return fault_of([&] { run_hw(m, fn, a, seed, hw); });
    };
    const std::string fh = alone(c.hand), fr = alone(c.recomp);
    ++t.kinds[fh];
    INFO(std::string(c.name) << " seed " << seed << ": hand " << fh << " / recomp " << fr << " (in the pair: " << in_pair << ")");
    CHECK(fh == fr);
    CHECK(!fh.empty());
}
using ArgGen = std::function<Args(const ModelWorld&, std::mt19937&)>;
struct WorldCase {
    const char* name;
    ArgGen args;
    std::map<unsigned, u64> regs = {};  // arguments 5.. ($t0..)
};

u64 m_(const ModelWorld& W, std::mt19937& r) { return sx(W.model(r)); }
u64 slot_(std::mt19937& r) { return r() % 4; }
u64 att_(std::mt19937& r) { return r() % 5; }

const std::vector<WorldCase>& world_cases() {
    static const std::vector<WorldCase> v = {
        // the model API on records
        {"sub_316910", [](const ModelWorld&, std::mt19937& r) { return Args{1 + r() % 7, (r() % 2) ? 5u : 225u, r() % 2 ? 0x1000u : 0u, 0}; }},
        {"sub_317450", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3174E0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_316690", [](const ModelWorld&, std::mt19937& r) { return Args{1 + r() % 7, r() % 300, 0, 0}; }},
        {"sub_316B40", [](const ModelWorld&, std::mt19937& r) { return Args{5, r() % 300, sx(kArena), r() % 2}; }},
        {"sub_316BD0", [](const ModelWorld& W, std::mt19937& r) { return Args{4, r() % 300, sx(W.anims[0]), 32}; }, {{GPR_T0, 1}}},
        {"sub_3176C0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3182D0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), r() % 6, 0}; }},
        {"sub_318540", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_3185B0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_318620", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), r() % 7, 0}; }},
        {"sub_3186E0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), r() % 7, 0}; }},
        {"sub_318770", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_318870", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_318910", [](const ModelWorld& W, std::mt19937& r) {
             // only slots with a hierarchy and a set are valid here (the original reads set +0 unchecked)
             const u32 md = W.models.front();
             (void)r;
             return Args{sx(md), 0, 0, 0};
         }},
        {"sub_318990", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_3189F0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), slot_(r), 0, 0}; }},
        {"sub_318A30", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), r() % 3, 0}; }},
        {"sub_318A50", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), r() % 3, 0}; }},
        {"sub_318A70", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.matrices[r() % 4]), r() % 3, 0}; }},
        {"sub_318A90", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), r() % 3, 0}; }},
        {"sub_318AD0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.rgba), 0, 0}; }},
        {"sub_318B00", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_318B10", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.matrices[r() % 4]), 0, 0, 0}; }},
        {"sub_318B60", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_318B70", [](const ModelWorld& W, std::mt19937&) { return Args{sx(W.models.front()), 0, 0, 0}; }},
        {"sub_318B80", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_318B90", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_318D10", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), r() % 5, sx(W.matrices[0]), 0}; }},
        {"sub_318ED0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), r() % 5, sx(W.vec3s[0]), 0}; }},
        {"sub_318FC0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319010", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319030", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319050", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319070", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319090", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3190A0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3190B0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), 0, 0}; }},
        {"sub_319100", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), 0, 0}; }},
        {"sub_319150", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319190", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3191B0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3191D0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_3191F0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), r() & 0x3FF, 0, 0}; }},
        {"sub_319200", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319210", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.vec3s[r() % 4]), 0, 0}; }},
        {"sub_319230", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), r() % 8, 0, 0}; }},
        {"sub_3192A0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), 7, 1 + r() % 9}; }, {{GPR_T0, kPathVa}, {GPR_T1, 0}}},
        {"sub_319390", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), 7, 1 + r() % 9}; }, {{GPR_T0, kPathVa}, {GPR_T1, 32}, {GPR_T2, 1}}},
        {"sub_319490", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), 1 + r() % 7, (r() % 2) ? 5u : 225u}; }, {{GPR_T0, 0}}},
        {"sub_3195F0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), m_(W, r), 0}; }},
        {"sub_3196D0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), r() % 6, 0}; }},
        {"sub_3196F0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.models.front()), att_(r), 0, 0}; }},
        {"sub_319770", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), att_(r), 0, 0}; }},
        {"sub_3197C0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), sx(W.matrices[r() % 4]), 0, 0}; }},
        {"sub_319840", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        {"sub_319910", [](const ModelWorld& W, std::mt19937& r) {
             // a model with a request (the world gives some; else one made here)
             for (u32 md : W.models)
                 if (md && (r() % 2)) return Args{sx(md), 0, 0, 0};
             return Args{sx(W.models.front()), 0, 0, 0};
         }},
        {"sub_31B220", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        // animation slots, sets, the material animations
        {"sub_313230", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.model(r) + kMdlSlots + kSlotSize * (r() % 4)), 0, 0, 0}; }},
        {"sub_3132C0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.model(r) + kMdlSlots + kSlotSize * (r() % 4)), 0, 0, 0}; }},
        {"sub_313090", [](const ModelWorld& W, std::mt19937& r) { return Args{0, sx(W.model(r) + kMdlSlots), 0, 0}; }},
        {"sub_313CA0", [](const ModelWorld& W, std::mt19937& r) {
             const u32 md = W.model(r);
             return Args{sx(md + kMdlAltAnim), sx(md + kMdlSlots), 0, 0};
         }},
        {"sub_3140C0", [](const ModelWorld& W, std::mt19937& r) { return Args{0, sx(W.model(r) + kMdlMatAnim), 0, 0}; }},
        {"sub_314730", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.model(r) + kMdlMatAnim), 0, 0, 0}; }},
        // effect lists and after effects
        {"sub_31D6B0", [](const ModelWorld&, std::mt19937&) { return Args{0, 0, 0, 0}; }},
        {"sub_31D7D0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[0] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31D7E0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[0] : W.lists[0]), sx(W.anims[0]), 24, r() % 5}; }},
        {"sub_31DF80", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[1] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31DCE0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[1] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31DE30", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[1] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31D790", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[1] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31D700", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.lists.empty() ? W.matrices[1] : W.lists[r() % W.lists.size()]), 0, 0, 0}; }},
        {"sub_31DFF0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.anims[r() % 8]), 16 + r() % 64, 0, 0}; }},
        {"sub_31E0B0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), 0, 0, 0}; }},
        {"sub_31E130", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), 0, 0, 0}; }},
        {"sub_31E1B0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), m_(W, r), 0, 0}; }},
        {"sub_31E270", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), m_(W, r), 0, 0}; }},
        {"sub_31E2C0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), 0, 0, 0}; }},
        {"sub_31E300", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.afx[r() % 3]), 0, 0, 0}; }},
        // the sound record
        {"sub_31EEB0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.sounds[r() % W.sounds.size()]), 0, 0, 0}; }},
        {"sub_31EE80", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.sounds[r() % W.sounds.size()]), sx(W.sounds[r() % W.sounds.size()]), 0, 0}; }},
        {"sub_31EEE0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.sounds[r() % W.sounds.size()]), 0, 0, 0}; }},
        {"sub_31EBE0", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.sounds[r() % W.sounds.size()]), 0, 0, 0}; }},
        {"sub_31C7E0", [](const ModelWorld& W, std::mt19937& r) { return Args{m_(W, r), 0, 0, 0}; }},
        // curves
        {"sub_31F740", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.curves[r() % 2]), 0, 0, 0}; }},
        {"sub_31F7A0", [](const ModelWorld& W, std::mt19937&) { return Args{sx(W.curves[0]), 0, 0, 0}; }},
        {"sub_31FBD0", [](const ModelWorld& W, std::mt19937&) { return Args{sx(W.curves[1]), 0, 0, 0}; }},
        {"sub_31FF40", [](const ModelWorld& W, std::mt19937& r) { return Args{sx(W.vec3s[r() % 4]), sx(W.matrices[0]), 0, 0}; }},
        // names
        {"sub_31D530", [](const ModelWorld&, std::mt19937& r) { return Args{1 + r() % 5, r() % 12, sx(kArena), 0}; }},
        {"sub_31E420", [](const ModelWorld&, std::mt19937& r) { return Args{r() % 3, r() % 12, 0, 0}; }},
        {"sub_31E310", [](const ModelWorld&, std::mt19937& r) { return Args{1 + r() % 3, r() % 6, 0, 0}; }},
        {"sub_31D4F0", [](const ModelWorld&, std::mt19937& r) { return Args{r() % 6, 0, 0, 0}; }},
    };
    return v;
}

}  // namespace

TEST_CASE("game(models): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stopped = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stopped += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE("random worlds: " << total << " pairs, " << stopped << " stopped early (identically)");
}

TEST_CASE("game(models): the model API on built model records (stand-in heap, files and recorders)") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    const char* only = std::getenv("P3FES_HG_ONLY");
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 n = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 12u;
    int pairs = 0;
    for (const WorldCase& wc : world_cases()) {
        if (only && std::string(only) != wc.name) continue;
        const Case& c = by_name(wc.name);
        for (u32 i = 0; i < n; ++i) {
            const u32 world_seed = 0x6D0000u + c.addr * 31u + i;
            std::mt19937 rng{world_seed};
            const ModelWorld W = build_world(m, rng);
            const Args a = wc.args(W, rng);
            HwCheck hwc = hw;
            for (const auto& [reg, v] : wc.regs) hwc.gpr_in[reg] = v;
            pair_checked(m, c, a, world_seed ^ 0x55u, hwc, W.setup(), [&] {
                std::mt19937 r{world_seed};
                (void)build_world(m, r);
            });
            ++pairs;
        }
    }
    MESSAGE("model worlds: " << pairs << " pairs");
}

namespace {

// One body run alone on the machine with chosen float arguments ($f12..$f14), under the stand-ins of a fresh world;
// returns the end context. The rule checks below run the hand body and the recompiled body this way from the same
// bytes and compare both results with the documented rule (the pairs above compare everything else).
struct Ran {
    EEContext ctx;
    std::vector<StandInCall> log;
};
Ran run_alone(Machine& m, Fn fn, const Args& a, std::initializer_list<float> f = {}, const WorldSetup& setup = install_models_world) {
    StandInWorld w;
    setup(w);
    StandInsScope scope(w.si);
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{1};
    m.fresh_context(a, rng);
    unsigned k = 12;
    for (float x : f) {
        u32 bits;
        std::memcpy(&bits, &x, 4);
        m.ctx.fpr[k++] = bits;
    }
    fn(m.ctx);
    Ran r;
    r.ctx = m.ctx;
    r.log = w.si.log;
    return r;
}
u32 v0_of(const Ran& r) { return static_cast<u32>(r.ctx.gpr[GPR_V0].u64[0]); }
float f0_of(const Ran& r) { return as_float(r.ctx.fpr[0]); }

// Runs both bodies from the same RAM (restored between them) and hands each result to `check`.
template <class Check>
void both(Machine& m, const Case& c, const Args& a, std::initializer_list<float> f, Check check,
          const WorldSetup& setup = install_models_world) {
    const std::vector<u8> before(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    {
        INFO(c.name << " (hand)");
        check(run_alone(m, c.hand, a, f, setup));
    }
    std::memcpy(m.mem.main_ram(), before.data(), before.size());
    {
        INFO(c.name << " (recompiled)");
        check(run_alone(m, c.recomp, a, f, setup));
    }
}

}  // namespace

TEST_CASE("game(models): mdlModelCreate builds the documented record and links it at the list head") {
    NEED_MACHINE();
    std::mt19937 rng{0x6D1001};
    for (int i = 0; i < 6; ++i) {
        const ModelWorld W = build_world(m, rng);
        const u32 kind = 1 + rng() % 7, id = rng() % 400;
        const u32 old_head = r32(m, kLists + 4 * kind);
        both(m, by_name("sub_316690"), {kind, id, 0, 0}, {}, [&](const Ran& r) {
            const u32 md = v0_of(r);
            REQUIRE(md >= kStandInHeap);
            CHECK(r16(m, md + kMdlType) == kind);
            CHECK(r16(m, md + kMdlId) == id);
            CHECK(r16(m, md + kMdlFlags) == 0x118u);
            CHECK(r32(m, md + kMdlColour) == 0xFFFFFFFFu);
            CHECK(r32(m, md + kMdlColour2) == 0xFFFFFFFFu);
            CHECK(r32(m, md + kMdl228) == 68u);
            CHECK(r32(m, md + kMdl232) == 0x717FBu);
            CHECK(rf(m, md + kMdlPlace) == 1.0f);
            CHECK(rf(m, md + kMdlPlace + 20) == 1.0f);
            CHECK(rf(m, md + kMdlRootOffset + 40) == 1.0f);
            CHECK(r32(m, md + kMdlPlace + 12) == 0x20003u);
            CHECK(rf(m, md + kMdlScale + 8) == 1.0f);
            CHECK(r16(m, md + kMdlLayer) == 2u);
            for (u32 s = 0; s < kMdlSlotCount; ++s) {
                const u32 sl = md + kMdlSlots + kSlotSize * s;
                CHECK(rs16(m, sl + kSlotAnim) == -1);
                CHECK(rs16(m, sl + kSlotPrevAnim) == -1);
                CHECK(*m.at(sl + kSlotDone) == 1);
                CHECK(rf(m, sl + kSlotSpeed) == 1.0f);
                CHECK(rf(m, sl + kSlotBlend) == 1.0f);
                CHECK(rf(m, sl + kSlotLookYaw) == 70.0f);
                CHECK(rf(m, sl + kSlotLookPitch) == 80.0f);
                CHECK(std::fabs(rf(m, sl + kSlotLookSpeed) - 0.2f) < 1e-6f);
                CHECK(rf(m, sl + kSlotLookQuat + 12) == 1.0f);
            }
            for (u32 k = 0; k < kMdlAttachCount; ++k) CHECK(r32(m, md + kMdlAttach + kAttachSize * k + kAttHelper) == 0xFFFFFFFFu);
            CHECK(rs16(m, md + kMdlMatAnim + kSlotAnim) == -1);
            CHECK(r32(m, kLists + 4 * kind) == md);  // the new head
            CHECK(r32(m, md + kMdlNext) == old_head);
            CHECK(r32(m, md + kMdlPrev) == 0u);
            if (old_head) CHECK(r32(m, old_head + kMdlPrev) == md);
            CHECK(r.log.front().args[0] == static_cast<u64>(kMdlSize));  // RwMalloc(1072, 0x40000)
            CHECK(r.log.front().args[1] == 0x40000u);
        });
    }
}

TEST_CASE("game(models): mdlModelFind walks the kind's list by id and flag mask") {
    NEED_MACHINE();
    std::mt19937 rng{0x6D1002};
    for (int i = 0; i < 10; ++i) {
        const ModelWorld W = build_world(m, rng);
        const u32 kind = 1 + rng() % 7, id = (rng() % 2) ? 5u : 225u, mask = (rng() % 2) ? 0x1000u : 0u;
        u32 want = 0;
        for (u32 md = r32(m, kLists + 4 * kind); md; md = r32(m, md + kMdlNext))
            if (r16(m, md + kMdlId) == id && (!mask || (r16(m, md + kMdlFlags) & mask))) {
                want = md;
                break;
            }
        both(m, by_name("sub_316910"), {kind, id, mask, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == want); });
    }
}

TEST_CASE("game(models): the slot queries follow the animation set") {
    NEED_MACHINE();
    std::mt19937 rng{0x6D1003};
    for (int i = 0; i < 8; ++i) {
        const ModelWorld W = build_world(m, rng);
        for (u32 md : W.models) {
            for (u32 s = 0; s < kMdlSlotCount; ++s) {
                const u32 sl = md + kMdlSlots + kSlotSize * s;
                const u32 set = r32(m, sl + kSlotSet);
                const bool has = set != 0 || (s == 0 && r32(m, md + kMdlAltAnim) != 0);
                both(m, by_name("sub_3185B0"), {md, s, 0, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == (has ? 1u : 0u)); });
                both(m, by_name("sub_318540"), {md, s, 0, 0}, {}, [&](const Ran& r) {
                    CHECK(static_cast<s32>(v0_of(r)) == (has ? rs16(m, sl + kSlotAnim) : -1));
                });
                for (u32 a = 0; a < 6; ++a) {
                    bool in = false, dummy = false;
                    if (set && a < r16(m, set + kSetCount)) {
                        const u32 e = r32(m, set + kSetEntries) + kSetEntrySize * a;
                        in = r32(m, e + kEntAnim) != 0;
                        dummy = r32(m, e + kEntAnim) == kDummyAnim;
                    }
                    const u32 alt = r32(m, md + kMdlAltAnim);
                    if (s == 0 && alt && a < r16(m, alt + 4) && r32(m, r32(m, alt) + 8 * a) != 0) in = true;
                    both(m, by_name("sub_318620"), {md, s, a, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == (in ? 1u : 0u)); });
                    both(m, by_name("sub_3186E0"), {md, s, a, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == (dummy ? 1u : 0u)); });
                }
                // the slot's time field in frames (x 30), 0 without a current animation
                const float t = rs16(m, sl + kSlotAnim) >= 0 ? rf(m, sl + kSlotTime) * 30.0f : 0.0f;
                both(m, by_name("sub_318990"), {md, s, 0, 0}, {}, [&](const Ran& r) { CHECK(f0_of(r) == doctest::Approx(t).epsilon(1e-5)); });
            }
        }
    }
}

TEST_CASE("game(models): set-anim-speed / look-at setters write slot 0 (and the material animations)") {
    NEED_MACHINE();
    std::mt19937 rng{0x6D1004};
    const ModelWorld W = build_world(m, rng);
    const u32 md = W.models.front();
    both(m, by_name("sub_3189F0"), {md, 0, 0, 0}, {1.75f}, [&](const Ran&) {
        CHECK(rf(m, md + kMdlSlots + kSlotSpeed) == 1.75f);
        CHECK(rf(m, md + kMdlMatAnim + kSlotSpeed) == 1.75f);
    });
    both(m, by_name("sub_3189F0"), {md, 2, 0, 0}, {0.5f}, [&](const Ran&) {
        CHECK(rf(m, md + kMdlSlots + kSlotSize * 2 + kSlotSpeed) == 0.5f);
    });
    both(m, by_name("sub_3190A0"), {md, 0, 0, 0}, {45.0f, 30.0f}, [&](const Ran&) {
        CHECK(rf(m, md + kMdlSlots + kSlotLookYaw) == 45.0f);
        CHECK(rf(m, md + kMdlSlots + kSlotLookPitch) == 30.0f);
    });
    w16(m, md + kMdlSlots + kSlotLook, 0x3E0);
    both(m, by_name("sub_3190B0"), {md, W.vec3s[1], 0, 0}, {}, [&](const Ran&) {
        CHECK(r16(m, md + kMdlSlots + kSlotLook) == 0x240u);  // 0x40 on, 0x20 / 0x80 / 0x100 off
        CHECK(rf(m, md + kMdlSlots + kSlotLookTarget + 4) == rf(m, W.vec3s[1] + 4));
    });
    w16(m, md + kMdlSlots + kSlotLook, 0x3E0);
    both(m, by_name("sub_319150"), {md, 0, 0, 0}, {0.25f, -0.5f}, [&](const Ran&) {
        CHECK(r16(m, md + kMdlSlots + kSlotLook) == 0x280u);
        CHECK(rf(m, md + kMdlSlots + kSlotLookTarget) == 0.25f);
        CHECK(rf(m, md + kMdlSlots + kSlotLookTarget + 4) == -0.5f);
    });
    for (u32 f : {0u, 0x20u, 0x100u, 0x1E0u}) {
        w16(m, md + kMdlSlots + kSlotLook, f);
        both(m, by_name("sub_3191D0"), {md, 0, 0, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == ((f & 0x1E0) ? 1u : 0u)); });
    }
}

TEST_CASE("game(models): the NPC file names -- story substitutions and the seasonal outfits") {
    NEED_MACHINE();
    // datGetDaysSinceApr5 / datGetFlag are hand-written callees: their guest words are set directly.
    struct Row {
        u32 npc, days;
        bool flag_b00;
        const char* name;
    };
    const Row rows[] = {
        {13, 10, false, "model/npc/n00013b.RMD"},   // seasonal NPC, April: winter outfit
        {13, 57, false, "model/npc/n00013a.RMD"},   // June 1: summer
        {13, 178, false, "model/npc/n00013a.RMD"},  // September 30: still summer
        {13, 179, false, "model/npc/n00013b.RMD"},  // October 1: winter
        {3, 100, false, "model/npc/n00003.RMD"},    // not in the seasonal list
        {1, 100, false, "model/npc/n00001a.RMD"},   // flag 0xB00 clear: NPC 1 itself (seasonal)
        {1, 100, true, "model/npc/n00002a.RMD"},    // flag 0xB00 set: NPC 1 -> 2
        {37, 20, false, "model/npc/n00037b.RMD"},
    };
    for (const Row& row : rows) {
        w16(m, kDays, row.days);
        u32 word = r32(m, kFlagWords + 4 * (0xB00 / 32));
        word = row.flag_b00 ? (word | 1u) : (word & ~1u);
        w32(m, kFlagWords + 4 * (0xB00 / 32), word);
        w32(m, kFlagWords + 4 * (0xB01 / 32), word & ~0xEu);  // the other rows' flags 0xB01..0xB03 clear
        std::memset(m.at(kArena), 0, 64);
        both(m, by_name("sub_31B4A0"), {kArena, row.npc, 0, 0}, {}, [&](const Ran&) { CHECK(m.str(kArena) == row.name); });
    }
}

TEST_CASE("game(models): party-member NPC numbers 60000..60399") {
    NEED_MACHINE();
    for (u32 id : {59999u, 60000u, 60042u, 60100u, 60250u, 60399u, 60400u}) {
        for (u32 type : {5u, 4u}) {
            w32(m, kArena, 0xAAAAu);
            w32(m, kArena + 4, 0xBBBBu);
            both(m, by_name("sub_31B680"), {type, id, kArena, kArena + 4}, {}, [&](const Ran& r) {
                const bool party = type == 5 && id >= 60000 && id < 60400;
                CHECK(v0_of(r) == (party ? 1u : 0u));
                if (party) CHECK(r32(m, kArena + 4) == id % 100);
                if (party && id < 60100) CHECK(r32(m, kArena) == 1u);  // the hero
                if (!party) CHECK(r32(m, kArena) == 0xAAAAu);
            });
        }
    }
}

TEST_CASE("game(models): the packed model kinds and their archive names") {
    NEED_MACHINE();
    for (u32 t = 0; t < 8; ++t)
        both(m, by_name("sub_31D4F0"), {t, 0, 0, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == ((t == 1 || t == 2) ? 1u : 0u)); });
    // kind 1, id 2 has outfit flag 0xC3 (table 0x69BA18): clear -> ".pac", set -> "a.pac"; The Answer -> "a.pac"
    for (int k = 0; k < 3; ++k) {
        w32(m, kScenario, k == 2 ? 1u : 0u);
        u32 word = r32(m, kFlagWords + 4 * (0xC3 / 32));
        word = k == 1 ? (word | (1u << (0xC3 % 32))) : (word & ~(1u << (0xC3 % 32)));
        w32(m, kFlagWords + 4 * (0xC3 / 32), word);
        std::memset(m.at(kArena), 0, 64);
        both(m, by_name("sub_31D530"), {1, 2, kArena, 0}, {}, [&](const Ran& r) {
            CHECK(v0_of(r) == 1u);
            CHECK(m.str(kArena) == (k == 0 ? "model/pack/bc002.pac" : "model/pack/bc002a.pac"));
        });
        both(m, by_name("sub_31E420"), {1, 2, 0, 0}, {}, [&](const Ran& r) { CHECK(v0_of(r) == (k == 0 ? 0u : 1u)); });
    }
    w32(m, kScenario, 0);
    // other kinds: the plain name (sub_31C820)
    std::memset(m.at(kArena), 0, 64);
    both(m, by_name("sub_31D530"), {4, 0x1F, kArena, 0}, {}, [&](const Ran&) { CHECK(m.str(kArena) == "model/player/bc01F.RMD"); });
}

TEST_CASE("game(models): the three sound-bank slots are least-recently used") {
    NEED_MACHINE();
    std::memset(m.at(0x957220u), 0, 24);
    w32(m, 0x7CE528u, 0);
    const Case& c = by_name("sub_31E310");
    // fresh: rows (stamp 0) are taken in order 0, 1, 2 (+3), a hit returns its row, a fourth key evicts the oldest
    const std::pair<std::pair<u32, u32>, u32> seq[] = {{{1, 5}, 3}, {{2, 37}, 4}, {{1, 5}, 3}, {{5, 9}, 5}, {{4, 1}, 3}, {{2, 37}, 4}};
    for (const auto& [key, want] : seq) {
        Ran r = run_alone(m, c.hand, {key.first, key.second, 0, 0});
        CHECK(v0_of(r) == want);
    }
    CHECK(r32(m, 0x7CE528u) == 4u);  // four misses
}

TEST_CASE("game(models): the keyframe curves interpolate linearly and clamp at the last key") {
    NEED_MACHINE();
    const u32 c = kArena + 0x100, keys = kArena + 0x200;
    // scalar keys (time, value): (0, 1) (1, 3) (3, 0)
    w32(m, c, 3);
    w32(m, c + 8, 8);
    w32(m, c + 12, keys);
    const float kv[] = {0.0f, 1.0f, 1.0f, 3.0f, 3.0f, 0.0f};
    for (int i = 0; i < 6; ++i) wf(m, keys + 4 * i, kv[i]);
    struct T {
        float t, idx, value;
    };
    for (const T& t : {T{0.0f, 0, 1.0f}, T{0.5f, 0, 2.0f}, T{1.0f, 1, 3.0f}, T{2.0f, 1, 1.5f}, T{5.0f, 2, 0.0f}}) {
        both(m, by_name("sub_31F740"), {c, 0, 0, 0}, {t.t}, [&](const Ran& r) { CHECK(v0_of(r) == static_cast<u32>(t.idx)); });
        both(m, by_name("sub_31F7A0"), {c, 0, 0, 0}, {t.t}, [&](const Ran& r) {
            CHECK(v0_of(r) == 0x7CE530u);
            CHECK(rf(m, 0x7CE530u) == t.t);
            CHECK(rf(m, 0x7CE534u) == doctest::Approx(t.value));
        });
    }
    // vec3 keys (time, x, y, z): (0, 0 0 0) (2, 2 4 -2)
    w32(m, c + 8, 16);
    w32(m, c, 2);
    const float vv[] = {0, 0, 0, 0, 2, 2, 4, -2};
    for (int i = 0; i < 8; ++i) wf(m, keys + 4 * i, vv[i]);
    both(m, by_name("sub_31FBD0"), {c, 0, 0, 0}, {0.5f}, [&](const Ran& r) {
        CHECK(v0_of(r) == 0x957240u);
        CHECK(rf(m, 0x957244u) == doctest::Approx(0.5f));
        CHECK(rf(m, 0x957248u) == doctest::Approx(1.0f));
        CHECK(rf(m, 0x95724Cu) == doctest::Approx(-0.5f));
    });
    // colour bytes from a {t, r, g, b} record
    const u32 rec = kArena + 0x300, out = kArena + 0x340;
    wf(m, rec + 4, 1.0f);
    wf(m, rec + 8, 0.5f);
    wf(m, rec + 12, 0.0f);
    both(m, by_name("sub_31FF40"), {rec, out, 0, 0}, {}, [&](const Ran&) {
        CHECK(*m.at(out + 4) == 255);
        CHECK(*m.at(out + 5) == 127);
        CHECK(*m.at(out + 6) == 0);
    });
}

// The replay snapshots: the model records of a real route (party, enemies, map objects, NPCs, weapons on helpers).
std::vector<std::filesystem::path> snapshots() {
    std::vector<std::filesystem::path> v;
    const std::filesystem::path base = std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours";
    for (const char* s : {"b_5800", "battle_ref_6150", "dorm_replay_4900", "climb_ref_17000"}) {
        const auto p = base / s / "eeMemory.bin";
        if (std::filesystem::exists(p)) v.push_back(p);
    }
    return v;
}
bool load_snapshot(Machine& m, const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    in.read(reinterpret_cast<char*>(m.mem.main_ram()), EEMemory::kMainRamSize);
    return in.gcount() == static_cast<std::streamsize>(EEMemory::kMainRamSize);
}

TEST_CASE("game(models): the model API on the replay snapshots' live records") {
    auto mp = std::make_unique<Machine>();
    if (mp->load_elf(elf_path()) != nullptr) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const auto snaps = snapshots();
    if (snaps.empty()) {
        MESSAGE("SKIP: no replay snapshot under extracted/_ours");
        return;
    }
    const HwCheck hw = full_check();
    const WorldSetup setup = install_models_world;
    int pairs = 0, models = 0;
    std::vector<u8> image(EEMemory::kMainRamSize);
    for (const auto& p : snaps) {
        REQUIRE(load_snapshot(m, p));
        INFO(p.string());
        std::memcpy(image.data(), m.mem.main_ram(), image.size());
        std::vector<u32> live;
        for (u32 k = 0; k < kMdlListCount; ++k)
            for (u32 md = r32(m, kLists + 4 * k); md && live.size() < 64; md = r32(m, md + kMdlNext)) live.push_back(md);
        models += static_cast<int>(live.size());
        u32 seed = 1;
        auto run = [&](const char* name, const Args& a) {
            const Case& c = by_name(name);
            pair_checked(m, c, a, seed++, hw, setup, [&] { std::memcpy(m.mem.main_ram(), image.data(), image.size()); });
            ++pairs;
        };
        for (u32 md : live) {
            const u32 kind = r16(m, md + kMdlType), id = r16(m, md + kMdlId);
            run("sub_316910", {kind, id, 0, 0});
            run("sub_316910", {kind, id, 0x1000, 0});
            run("sub_318FC0", {md, 0, 0, 0});
            run("sub_3191D0", {md, 0, 0, 0});
            run("sub_319200", {md, 0, 0, 0});
            run("sub_318B00", {md, 0, 0, 0});
            run("sub_318B70", {md, 0, 0, 0});
            run("sub_318B80", {md, 0, 0, 0});
            for (u32 s = 0; s < 2; ++s) {
                run("sub_3185B0", {md, s, 0, 0});
                run("sub_318540", {md, s, 0, 0});
                run("sub_318870", {md, s, 0, 0});
                run("sub_318990", {md, s, 0, 0});
                for (u32 a = 0; a < 3; ++a) {
                    run("sub_318620", {md, s, a, 0});
                    run("sub_3186E0", {md, s, a, 0});
                }
            }
            for (u32 h = 0; h < 3; ++h) {
                run("sub_318ED0", {md, h, kArena, 0});  // the helpers' positions on the real frames
                run("sub_318D10", {md, h, kArena + 0x40, 0});
            }
            for (u32 a = 0; a < kMdlAttachCount; ++a) run("sub_319770", {md, a, 0, 0});
            run("sub_31EBE0", {md + kMdlSound, 0, 0, 0});
            run("sub_3176C0", {md, 0, 0, 0});  // the placement onto the real clump frame
        }
    }
    MESSAGE("snapshots: " << models << " live model records, " << pairs << " pairs");
}

TEST_CASE("game(models): pair tally") {
    int pairs = 0, faults = 0;
    for (const auto& [name, t] : g_tally) {
        pairs += t.pairs;
        faults += t.faults;
        if (!t.faults) continue;
        std::string kinds;
        for (const auto& [k, n] : t.kinds) kinds += "\n    " + std::to_string(n) + "x " + k;
        MESSAGE(name << ": " << t.pairs << " pairs, " << t.faults << " stopped at the same fault in both bodies" << kinds);
    }
    MESSAGE("model-world pairs: " << pairs << " (" << faults << " compared as faults)");
}

#else

TEST_CASE("game(models): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
