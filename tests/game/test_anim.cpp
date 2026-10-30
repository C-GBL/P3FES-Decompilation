// Pair tests for slice anim (game/src/model/anim.cpp: RtAnim, RpHAnim, RpSkin, RpUVAnim, the compressed and game
// keyframe schemes, the model manager's animation slots). Every body against its recompiled body, compared by
// tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log.
//   1. the generic sweep: random words and pointers in a scratch window (mostly the bad-input and early-stop paths);
//   2. the real animation state of three replay snapshots (b_5800 battle, dorm_replay_4900, climb_ref_17000), found
//      through the model lists (models.h): the time functions on every live interpolator, the hierarchy matrix update
//      on every hierarchy, the look-at and model updates, the skins of every model clump;
//   3. documented rules checked on the recompiled run's result: interpolated frames between their keyframes and (the
//      compressed scheme) the translation lerp of the decompressed keyframes scaled by the custom data, the time wrap
//      of AddAnimTime, the node matrices against a host RpHAnim walk (apply x parent, push / pop stack), the apply
//      callback against the quaternion-to-matrix formula, slot times equal to their interpolators', the skin weight
//      packing, the 16-bit float format, the initial fields of created interpolators / animations;
//   4. creation on the heap stand-ins (tests/game/stand_ins.h: RwMalloc / RwFree / the free lists).
// Callees run for real where emitted or hand-written (the interpolate / blend callbacks, mdlAnimEndCB, the RW matrix and
// frame functions; the slot update sub_313490 is hand-written since finalB; the destroy functions test_field3_units
// stands in stay recompiled); a $f12 argument (time, weight, value) is set by a wrapper around both bodies (pair_f12).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/anim.h"
#include "p3fes/game/models.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
namespace anim = p3fes::game::anim;
namespace mdl = p3fes::game::mdl;

namespace p3fes::recomp_gen {
void fn_sub_4B65A0_004b65a0(EEContext&);  // generated body
void fn_sub_4B65A0_004b65a0__recomp(EEContext&);  // recompiled
void fn_sub_4B6600_004b6600(EEContext&);  // generated body
void fn_sub_4B6600_004b6600__recomp(EEContext&);  // recompiled
void fn_sub_4B6640_004b6640(EEContext&);  // generated body
void fn_sub_4B6640_004b6640__recomp(EEContext&);  // recompiled
void fn_sub_4B6680_004b6680(EEContext&);  // generated body
void fn_sub_4B6680_004b6680__recomp(EEContext&);  // recompiled
void fn_sub_4B67B0_004b67b0(EEContext&);  // generated body
void fn_sub_4B67B0_004b67b0__recomp(EEContext&);  // recompiled
void fn_sub_4B6840_004b6840(EEContext&);  // generated body
void fn_sub_4B6840_004b6840__recomp(EEContext&);  // recompiled
void fn_sub_4B69B0_004b69b0(EEContext&);  // generated body
void fn_sub_4B69B0_004b69b0__recomp(EEContext&);  // recompiled
void fn_sub_4B6A40_004b6a40(EEContext&);  // generated body
void fn_sub_4B6A40_004b6a40__recomp(EEContext&);  // recompiled
void fn_sub_4B6C80_004b6c80(EEContext&);  // generated body
void fn_sub_4B6C80_004b6c80__recomp(EEContext&);  // recompiled
void fn_sub_4B6D90_004b6d90(EEContext&);  // generated body
void fn_sub_4B6D90_004b6d90__recomp(EEContext&);  // recompiled
void fn_sub_4B6DD0_004b6dd0(EEContext&);  // generated body
void fn_sub_4B6DD0_004b6dd0__recomp(EEContext&);  // recompiled
void fn_sub_4B6E10_004b6e10(EEContext&);  // generated body
void fn_sub_4B6E10_004b6e10__recomp(EEContext&);  // recompiled
void fn_sub_4B6EC0_004b6ec0(EEContext&);  // generated body
void fn_sub_4B6EC0_004b6ec0__recomp(EEContext&);  // recompiled
void fn_sub_4B7010_004b7010(EEContext&);  // generated body
void fn_sub_4B7010_004b7010__recomp(EEContext&);  // recompiled
void fn_sub_4B7020_004b7020(EEContext&);  // generated body
void fn_sub_4B7020_004b7020__recomp(EEContext&);  // recompiled
void fn_sub_4B7050_004b7050(EEContext&);  // generated body
void fn_sub_4B7050_004b7050__recomp(EEContext&);  // recompiled
void fn_sub_4B7240_004b7240(EEContext&);  // generated body
void fn_sub_4B7240_004b7240__recomp(EEContext&);  // recompiled
void fn_sub_4B74C0_004b74c0(EEContext&);  // generated body
void fn_sub_4B74C0_004b74c0__recomp(EEContext&);  // recompiled
void fn_sub_4B7510_004b7510(EEContext&);  // generated body
void fn_sub_4B7510_004b7510__recomp(EEContext&);  // recompiled
void fn_sub_4B75D0_004b75d0(EEContext&);  // generated body
void fn_sub_4B75D0_004b75d0__recomp(EEContext&);  // recompiled
void fn_sub_4B76B0_004b76b0(EEContext&);  // generated body
void fn_sub_4B76B0_004b76b0__recomp(EEContext&);  // recompiled
void fn_sub_4B7750_004b7750(EEContext&);  // generated body
void fn_sub_4B7750_004b7750__recomp(EEContext&);  // recompiled
void fn_sub_4B7760_004b7760(EEContext&);  // generated body
void fn_sub_4B7760_004b7760__recomp(EEContext&);  // recompiled
void fn_sub_4B7770_004b7770(EEContext&);  // generated body
void fn_sub_4B7770_004b7770__recomp(EEContext&);  // recompiled
void fn_sub_4B77F0_004b77f0(EEContext&);  // generated body
void fn_sub_4B77F0_004b77f0__recomp(EEContext&);  // recompiled
void fn_sub_4B79D0_004b79d0(EEContext&);  // generated body
void fn_sub_4B79D0_004b79d0__recomp(EEContext&);  // recompiled
void fn_sub_4B7C60_004b7c60(EEContext&);  // generated body
void fn_sub_4B7C60_004b7c60__recomp(EEContext&);  // recompiled
void fn_sub_4B7D00_004b7d00(EEContext&);  // generated body
void fn_sub_4B7D00_004b7d00__recomp(EEContext&);  // recompiled
void fn_sub_4B7E10_004b7e10(EEContext&);  // generated body
void fn_sub_4B7E10_004b7e10__recomp(EEContext&);  // recompiled
void fn_sub_4B7F30_004b7f30(EEContext&);  // generated body
void fn_sub_4B7F30_004b7f30__recomp(EEContext&);  // recompiled
void fn_sub_4B7F80_004b7f80(EEContext&);  // generated body
void fn_sub_4B7F80_004b7f80__recomp(EEContext&);  // recompiled
void fn_sub_4B7FD0_004b7fd0(EEContext&);  // generated body
void fn_sub_4B7FD0_004b7fd0__recomp(EEContext&);  // recompiled
void fn_sub_4B8080_004b8080(EEContext&);  // generated body
void fn_sub_4B8080_004b8080__recomp(EEContext&);  // recompiled
void fn_sub_4B8120_004b8120(EEContext&);  // generated body
void fn_sub_4B8120_004b8120__recomp(EEContext&);  // recompiled
void fn_sub_4B81F0_004b81f0(EEContext&);  // generated body
void fn_sub_4B81F0_004b81f0__recomp(EEContext&);  // recompiled
void fn_sub_4B8290_004b8290(EEContext&);  // generated body
void fn_sub_4B8290_004b8290__recomp(EEContext&);  // recompiled
void fn_sub_4B82D0_004b82d0(EEContext&);  // generated body
void fn_sub_4B82D0_004b82d0__recomp(EEContext&);  // recompiled
void fn_sub_4B83D0_004b83d0(EEContext&);  // generated body
void fn_sub_4B83D0_004b83d0__recomp(EEContext&);  // recompiled
void fn_sub_4B8500_004b8500(EEContext&);  // generated body
void fn_sub_4B8500_004b8500__recomp(EEContext&);  // recompiled
void fn_nullsub_125_004b8610(EEContext&);  // generated body
void fn_nullsub_125_004b8610__recomp(EEContext&);  // recompiled
void fn_nullsub_126_004b8620(EEContext&);  // generated body
void fn_nullsub_126_004b8620__recomp(EEContext&);  // recompiled
void fn_sub_4B8630_004b8630(EEContext&);  // generated body
void fn_sub_4B8630_004b8630__recomp(EEContext&);  // recompiled
void fn_sub_4B8740_004b8740(EEContext&);  // generated body
void fn_sub_4B8740_004b8740__recomp(EEContext&);  // recompiled
void fn_sub_4B87D0_004b87d0(EEContext&);  // generated body
void fn_sub_4B87D0_004b87d0__recomp(EEContext&);  // recompiled
void fn_sub_4B8830_004b8830(EEContext&);  // generated body
void fn_sub_4B8830_004b8830__recomp(EEContext&);  // recompiled
void fn_sub_4B88E0_004b88e0(EEContext&);  // generated body
void fn_sub_4B88E0_004b88e0__recomp(EEContext&);  // recompiled
void fn_sub_4B8920_004b8920(EEContext&);  // generated body
void fn_sub_4B8920_004b8920__recomp(EEContext&);  // recompiled
void fn_sub_4B89D0_004b89d0(EEContext&);  // generated body
void fn_sub_4B89D0_004b89d0__recomp(EEContext&);  // recompiled
void fn_sub_4B8B10_004b8b10(EEContext&);  // generated body
void fn_sub_4B8B10_004b8b10__recomp(EEContext&);  // recompiled
void fn_sub_4B8C30_004b8c30(EEContext&);  // generated body
void fn_sub_4B8C30_004b8c30__recomp(EEContext&);  // recompiled
void fn_sub_4B8D50_004b8d50(EEContext&);  // generated body
void fn_sub_4B8D50_004b8d50__recomp(EEContext&);  // recompiled
void fn_sub_4B8E70_004b8e70(EEContext&);  // generated body
void fn_sub_4B8E70_004b8e70__recomp(EEContext&);  // recompiled
void fn_sub_4B9030_004b9030(EEContext&);  // generated body
void fn_sub_4B9030_004b9030__recomp(EEContext&);  // recompiled
void fn_sub_4B90A0_004b90a0(EEContext&);  // generated body
void fn_sub_4B90A0_004b90a0__recomp(EEContext&);  // recompiled
void fn_sub_4B9140_004b9140(EEContext&);  // generated body
void fn_sub_4B9140_004b9140__recomp(EEContext&);  // recompiled
void fn_sub_4B91C0_004b91c0(EEContext&);  // generated body
void fn_sub_4B91C0_004b91c0__recomp(EEContext&);  // recompiled
void fn_sub_4B92D0_004b92d0(EEContext&);  // generated body
void fn_sub_4B92D0_004b92d0__recomp(EEContext&);  // recompiled
void fn_sub_4B9350_004b9350(EEContext&);  // generated body
void fn_sub_4B9350_004b9350__recomp(EEContext&);  // recompiled
void fn_sub_4B9370_004b9370(EEContext&);  // generated body
void fn_sub_4B9370_004b9370__recomp(EEContext&);  // recompiled
void fn_sub_4B96E0_004b96e0(EEContext&);  // generated body
void fn_sub_4B96E0_004b96e0__recomp(EEContext&);  // recompiled
void fn_sub_4B96F0_004b96f0(EEContext&);  // generated body
void fn_sub_4B96F0_004b96f0__recomp(EEContext&);  // recompiled
void fn_sub_4B97B0_004b97b0(EEContext&);  // generated body
void fn_sub_4B97B0_004b97b0__recomp(EEContext&);  // recompiled
void fn_sub_4B97D0_004b97d0(EEContext&);  // generated body
void fn_sub_4B97D0_004b97d0__recomp(EEContext&);  // recompiled
void fn_sub_4B97F0_004b97f0(EEContext&);  // generated body
void fn_sub_4B97F0_004b97f0__recomp(EEContext&);  // recompiled
void fn_sub_4F7300_004f7300(EEContext&);  // generated body
void fn_sub_4F7300_004f7300__recomp(EEContext&);  // recompiled
void fn_sub_4F7470_004f7470(EEContext&);  // generated body
void fn_sub_4F7470_004f7470__recomp(EEContext&);  // recompiled
void fn_sub_4F7560_004f7560(EEContext&);  // generated body
void fn_sub_4F7560_004f7560__recomp(EEContext&);  // recompiled
void fn_sub_4F7F40_004f7f40(EEContext&);  // generated body
void fn_sub_4F7F40_004f7f40__recomp(EEContext&);  // recompiled
void fn_sub_4F8560_004f8560(EEContext&);  // generated body
void fn_sub_4F8560_004f8560__recomp(EEContext&);  // recompiled
void fn_sub_4F8690_004f8690(EEContext&);  // generated body
void fn_sub_4F8690_004f8690__recomp(EEContext&);  // recompiled
void fn_sub_4F8790_004f8790(EEContext&);  // generated body
void fn_sub_4F8790_004f8790__recomp(EEContext&);  // recompiled
void fn_sub_4F87B0_004f87b0(EEContext&);  // generated body
void fn_sub_4F87B0_004f87b0__recomp(EEContext&);  // recompiled
void fn_sub_4F8CB0_004f8cb0(EEContext&);  // generated body
void fn_sub_4F8CB0_004f8cb0__recomp(EEContext&);  // recompiled
void fn_sub_4F8E10_004f8e10(EEContext&);  // generated body
void fn_sub_4F8E10_004f8e10__recomp(EEContext&);  // recompiled
void fn_sub_35A290_0035a290(EEContext&);  // generated body
void fn_sub_35A290_0035a290__recomp(EEContext&);  // recompiled
void fn_sub_35A3F0_0035a3f0(EEContext&);  // generated body
void fn_sub_35A3F0_0035a3f0__recomp(EEContext&);  // recompiled
void fn_sub_35A620_0035a620(EEContext&);  // generated body
void fn_sub_35A620_0035a620__recomp(EEContext&);  // recompiled
void fn_sub_35A6A0_0035a6a0(EEContext&);  // generated body
void fn_sub_35A6A0_0035a6a0__recomp(EEContext&);  // recompiled
void fn_sub_35A770_0035a770(EEContext&);  // generated body
void fn_sub_35A770_0035a770__recomp(EEContext&);  // recompiled
void fn_sub_35A850_0035a850(EEContext&);  // generated body
void fn_sub_35A850_0035a850__recomp(EEContext&);  // recompiled
void fn_sub_35A870_0035a870(EEContext&);  // generated body
void fn_sub_35A870_0035a870__recomp(EEContext&);  // recompiled
void fn_sub_35AA10_0035aa10(EEContext&);  // generated body
void fn_sub_35AA10_0035aa10__recomp(EEContext&);  // recompiled
void fn_sub_35ABA0_0035aba0(EEContext&);  // generated body
void fn_sub_35ABA0_0035aba0__recomp(EEContext&);  // recompiled
void fn_sub_464760_00464760(EEContext&);  // generated body
void fn_sub_464760_00464760__recomp(EEContext&);  // recompiled
void fn_sub_464850_00464850(EEContext&);  // generated body
void fn_sub_464850_00464850__recomp(EEContext&);  // recompiled
void fn_sub_464E80_00464e80(EEContext&);  // generated body
void fn_sub_464E80_00464e80__recomp(EEContext&);  // recompiled
void fn_sub_4654A0_004654a0(EEContext&);  // generated body
void fn_sub_4654A0_004654a0__recomp(EEContext&);  // recompiled
void fn_sub_465590_00465590(EEContext&);  // generated body
void fn_sub_465590_00465590__recomp(EEContext&);  // recompiled
void fn_sub_465660_00465660(EEContext&);  // generated body
void fn_sub_465660_00465660__recomp(EEContext&);  // recompiled
void fn_sub_465670_00465670(EEContext&);  // generated body
void fn_sub_465670_00465670__recomp(EEContext&);  // recompiled
void fn_sub_4657D0_004657d0(EEContext&);  // generated body
void fn_sub_4657D0_004657d0__recomp(EEContext&);  // recompiled
void fn_sub_465930_00465930(EEContext&);  // generated body
void fn_sub_465930_00465930__recomp(EEContext&);  // recompiled
void fn_sub_465A00_00465a00(EEContext&);  // generated body
void fn_sub_465A00_00465a00__recomp(EEContext&);  // recompiled
void fn_sub_465AE0_00465ae0(EEContext&);  // generated body
void fn_sub_465AE0_00465ae0__recomp(EEContext&);  // recompiled
void fn_sub_465B20_00465b20(EEContext&);  // generated body
void fn_sub_465B20_00465b20__recomp(EEContext&);  // recompiled
void fn_sub_465B40_00465b40(EEContext&);  // generated body
void fn_sub_465B40_00465b40__recomp(EEContext&);  // recompiled
void fn_sub_465BF0_00465bf0(EEContext&);  // generated body
void fn_sub_465BF0_00465bf0__recomp(EEContext&);  // recompiled
void fn_sub_465CF0_00465cf0(EEContext&);  // generated body
void fn_sub_465CF0_00465cf0__recomp(EEContext&);  // recompiled
void fn_sub_465EB0_00465eb0(EEContext&);  // generated body
void fn_sub_465EB0_00465eb0__recomp(EEContext&);  // recompiled
void fn_sub_466130_00466130(EEContext&);  // generated body
void fn_sub_466130_00466130__recomp(EEContext&);  // recompiled
void fn_sub_4661B0_004661b0(EEContext&);  // generated body
void fn_sub_4661B0_004661b0__recomp(EEContext&);  // recompiled
void fn_sub_466260_00466260(EEContext&);  // generated body
void fn_sub_466260_00466260__recomp(EEContext&);  // recompiled
void fn_sub_466480_00466480(EEContext&);  // generated body
void fn_sub_466480_00466480__recomp(EEContext&);  // recompiled
void fn_sub_466640_00466640(EEContext&);  // generated body
void fn_sub_466640_00466640__recomp(EEContext&);  // recompiled
void fn_sub_466710_00466710(EEContext&);  // generated body
void fn_sub_466710_00466710__recomp(EEContext&);  // recompiled
void fn_sub_466720_00466720(EEContext&);  // generated body
void fn_sub_466720_00466720__recomp(EEContext&);  // recompiled
void fn_sub_466730_00466730(EEContext&);  // generated body
void fn_sub_466730_00466730__recomp(EEContext&);  // recompiled
void fn_sub_466EF0_00466ef0(EEContext&);  // generated body
void fn_sub_466EF0_00466ef0__recomp(EEContext&);  // recompiled
void fn_sub_489020_00489020(EEContext&);  // generated body
void fn_sub_489020_00489020__recomp(EEContext&);  // recompiled
void fn_sub_489080_00489080(EEContext&);  // generated body
void fn_sub_489080_00489080__recomp(EEContext&);  // recompiled
void fn_sub_489160_00489160(EEContext&);  // generated body
void fn_sub_489160_00489160__recomp(EEContext&);  // recompiled
void fn_sub_489320_00489320(EEContext&);  // generated body
void fn_sub_489320_00489320__recomp(EEContext&);  // recompiled
void fn_sub_489350_00489350(EEContext&);  // generated body
void fn_sub_489350_00489350__recomp(EEContext&);  // recompiled
void fn_sub_4893E0_004893e0(EEContext&);  // generated body
void fn_sub_4893E0_004893e0__recomp(EEContext&);  // recompiled
void fn_sub_489460_00489460(EEContext&);  // generated body
void fn_sub_489460_00489460__recomp(EEContext&);  // recompiled
void fn_sub_489550_00489550(EEContext&);  // generated body
void fn_sub_489550_00489550__recomp(EEContext&);  // recompiled
void fn_sub_489730_00489730(EEContext&);  // generated body
void fn_sub_489730_00489730__recomp(EEContext&);  // recompiled
void fn_sub_489840_00489840(EEContext&);  // generated body
void fn_sub_489840_00489840__recomp(EEContext&);  // recompiled
void fn_sub_4898C0_004898c0(EEContext&);  // generated body
void fn_sub_4898C0_004898c0__recomp(EEContext&);  // recompiled
void fn_sub_4898E0_004898e0(EEContext&);  // generated body
void fn_sub_4898E0_004898e0__recomp(EEContext&);  // recompiled
void fn_sub_489950_00489950(EEContext&);  // generated body
void fn_sub_489950_00489950__recomp(EEContext&);  // recompiled
void fn_sub_489960_00489960(EEContext&);  // generated body
void fn_sub_489960_00489960__recomp(EEContext&);  // recompiled
void fn_sub_4899A0_004899a0(EEContext&);  // generated body
void fn_sub_4899A0_004899a0__recomp(EEContext&);  // recompiled
void fn_sub_4899BC_004899bc(EEContext&);  // generated body
void fn_sub_4899BC_004899bc__recomp(EEContext&);  // recompiled
void fn_sub_4899D0_004899d0(EEContext&);  // generated body
void fn_sub_4899D0_004899d0__recomp(EEContext&);  // recompiled
void fn_sub_4899F0_004899f0(EEContext&);  // generated body
void fn_sub_4899F0_004899f0__recomp(EEContext&);  // recompiled
void fn_sub_489A80_00489a80(EEContext&);  // generated body
void fn_sub_489A80_00489a80__recomp(EEContext&);  // recompiled
void fn_sub_489AE0_00489ae0(EEContext&);  // generated body
void fn_sub_489AE0_00489ae0__recomp(EEContext&);  // recompiled
void fn_sub_489B70_00489b70(EEContext&);  // generated body
void fn_sub_489B70_00489b70__recomp(EEContext&);  // recompiled
void fn_sub_489CD0_00489cd0(EEContext&);  // generated body
void fn_sub_489CD0_00489cd0__recomp(EEContext&);  // recompiled
void fn_sub_489F20_00489f20(EEContext&);  // generated body
void fn_sub_489F20_00489f20__recomp(EEContext&);  // recompiled
void fn_sub_48A180_0048a180(EEContext&);  // generated body
void fn_sub_48A180_0048a180__recomp(EEContext&);  // recompiled
void fn_sub_48A190_0048a190(EEContext&);  // generated body
void fn_sub_48A190_0048a190__recomp(EEContext&);  // recompiled
void fn_sub_48A1A0_0048a1a0(EEContext&);  // generated body
void fn_sub_48A1A0_0048a1a0__recomp(EEContext&);  // recompiled
void fn_sub_48A2A0_0048a2a0(EEContext&);  // generated body
void fn_sub_48A2A0_0048a2a0__recomp(EEContext&);  // recompiled
void fn_sub_48A2C0_0048a2c0(EEContext&);  // generated body
void fn_sub_48A2C0_0048a2c0__recomp(EEContext&);  // recompiled
void fn_sub_48A2E0_0048a2e0(EEContext&);  // generated body
void fn_sub_48A2E0_0048a2e0__recomp(EEContext&);  // recompiled
void fn_sub_48A370_0048a370(EEContext&);  // generated body
void fn_sub_48A370_0048a370__recomp(EEContext&);  // recompiled
void fn_name__C9type_info_0048a3d0(EEContext&);  // generated body
void fn_name__C9type_info_0048a3d0__recomp(EEContext&);  // recompiled
void fn_sub_48A3F0_0048a3f0(EEContext&);  // generated body
void fn_sub_48A3F0_0048a3f0__recomp(EEContext&);  // recompiled
void fn_sub_48A480_0048a480(EEContext&);  // generated body
void fn_sub_48A480_0048a480__recomp(EEContext&);  // recompiled
void fn_sub_48A4B0_0048a4b0(EEContext&);  // generated body
void fn_sub_48A4B0_0048a4b0__recomp(EEContext&);  // recompiled
void fn_sub_48A790_0048a790(EEContext&);  // generated body
void fn_sub_48A790_0048a790__recomp(EEContext&);  // recompiled
void fn_sub_48A7A0_0048a7a0(EEContext&);  // generated body
void fn_sub_48A7A0_0048a7a0__recomp(EEContext&);  // recompiled
void fn_sub_48A800_0048a800(EEContext&);  // generated body
void fn_sub_48A800_0048a800__recomp(EEContext&);  // recompiled
void fn_sub_48A9A0_0048a9a0(EEContext&);  // generated body
void fn_sub_48A9A0_0048a9a0__recomp(EEContext&);  // recompiled
void fn_sub_48ABF0_0048abf0(EEContext&);  // generated body
void fn_sub_48ABF0_0048abf0__recomp(EEContext&);  // recompiled
void fn_sub_48AC00_0048ac00(EEContext&);  // generated body
void fn_sub_48AC00_0048ac00__recomp(EEContext&);  // recompiled
void fn_sub_48AC10_0048ac10(EEContext&);  // generated body
void fn_sub_48AC10_0048ac10__recomp(EEContext&);  // recompiled
void fn_sub_311730_00311730(EEContext&);  // generated body
void fn_sub_311730_00311730__recomp(EEContext&);  // recompiled
void fn_sub_317730_00317730(EEContext&);  // generated body
void fn_sub_317730_00317730__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_4B65A0", 0x4B65A0, &recomp_gen::fn_sub_4B65A0_004b65a0, &recomp_gen::fn_sub_4B65A0_004b65a0__recomp},
    {"sub_4B6600", 0x4B6600, &recomp_gen::fn_sub_4B6600_004b6600, &recomp_gen::fn_sub_4B6600_004b6600__recomp},
    {"sub_4B6640", 0x4B6640, &recomp_gen::fn_sub_4B6640_004b6640, &recomp_gen::fn_sub_4B6640_004b6640__recomp},
    {"sub_4B6680", 0x4B6680, &recomp_gen::fn_sub_4B6680_004b6680, &recomp_gen::fn_sub_4B6680_004b6680__recomp},
    {"sub_4B67B0", 0x4B67B0, &recomp_gen::fn_sub_4B67B0_004b67b0, &recomp_gen::fn_sub_4B67B0_004b67b0__recomp},
    {"sub_4B6840", 0x4B6840, &recomp_gen::fn_sub_4B6840_004b6840, &recomp_gen::fn_sub_4B6840_004b6840__recomp},
    {"sub_4B69B0", 0x4B69B0, &recomp_gen::fn_sub_4B69B0_004b69b0, &recomp_gen::fn_sub_4B69B0_004b69b0__recomp},
    {"sub_4B6A40", 0x4B6A40, &recomp_gen::fn_sub_4B6A40_004b6a40, &recomp_gen::fn_sub_4B6A40_004b6a40__recomp},
    {"sub_4B6C80", 0x4B6C80, &recomp_gen::fn_sub_4B6C80_004b6c80, &recomp_gen::fn_sub_4B6C80_004b6c80__recomp},
    {"sub_4B6D90", 0x4B6D90, &recomp_gen::fn_sub_4B6D90_004b6d90, &recomp_gen::fn_sub_4B6D90_004b6d90__recomp},
    {"sub_4B6DD0", 0x4B6DD0, &recomp_gen::fn_sub_4B6DD0_004b6dd0, &recomp_gen::fn_sub_4B6DD0_004b6dd0__recomp},
    {"sub_4B6E10", 0x4B6E10, &recomp_gen::fn_sub_4B6E10_004b6e10, &recomp_gen::fn_sub_4B6E10_004b6e10__recomp},
    {"sub_4B6EC0", 0x4B6EC0, &recomp_gen::fn_sub_4B6EC0_004b6ec0, &recomp_gen::fn_sub_4B6EC0_004b6ec0__recomp},
    {"sub_4B7010", 0x4B7010, &recomp_gen::fn_sub_4B7010_004b7010, &recomp_gen::fn_sub_4B7010_004b7010__recomp},
    {"sub_4B7020", 0x4B7020, &recomp_gen::fn_sub_4B7020_004b7020, &recomp_gen::fn_sub_4B7020_004b7020__recomp},
    {"sub_4B7050", 0x4B7050, &recomp_gen::fn_sub_4B7050_004b7050, &recomp_gen::fn_sub_4B7050_004b7050__recomp},
    {"sub_4B7240", 0x4B7240, &recomp_gen::fn_sub_4B7240_004b7240, &recomp_gen::fn_sub_4B7240_004b7240__recomp},
    {"sub_4B74C0", 0x4B74C0, &recomp_gen::fn_sub_4B74C0_004b74c0, &recomp_gen::fn_sub_4B74C0_004b74c0__recomp},
    {"sub_4B7510", 0x4B7510, &recomp_gen::fn_sub_4B7510_004b7510, &recomp_gen::fn_sub_4B7510_004b7510__recomp},
    {"sub_4B75D0", 0x4B75D0, &recomp_gen::fn_sub_4B75D0_004b75d0, &recomp_gen::fn_sub_4B75D0_004b75d0__recomp},
    {"sub_4B76B0", 0x4B76B0, &recomp_gen::fn_sub_4B76B0_004b76b0, &recomp_gen::fn_sub_4B76B0_004b76b0__recomp},
    {"sub_4B7750", 0x4B7750, &recomp_gen::fn_sub_4B7750_004b7750, &recomp_gen::fn_sub_4B7750_004b7750__recomp},
    {"sub_4B7760", 0x4B7760, &recomp_gen::fn_sub_4B7760_004b7760, &recomp_gen::fn_sub_4B7760_004b7760__recomp},
    {"sub_4B7770", 0x4B7770, &recomp_gen::fn_sub_4B7770_004b7770, &recomp_gen::fn_sub_4B7770_004b7770__recomp},
    {"sub_4B77F0", 0x4B77F0, &recomp_gen::fn_sub_4B77F0_004b77f0, &recomp_gen::fn_sub_4B77F0_004b77f0__recomp},
    {"sub_4B79D0", 0x4B79D0, &recomp_gen::fn_sub_4B79D0_004b79d0, &recomp_gen::fn_sub_4B79D0_004b79d0__recomp},
    {"sub_4B7C60", 0x4B7C60, &recomp_gen::fn_sub_4B7C60_004b7c60, &recomp_gen::fn_sub_4B7C60_004b7c60__recomp},
    {"sub_4B7D00", 0x4B7D00, &recomp_gen::fn_sub_4B7D00_004b7d00, &recomp_gen::fn_sub_4B7D00_004b7d00__recomp},
    {"sub_4B7E10", 0x4B7E10, &recomp_gen::fn_sub_4B7E10_004b7e10, &recomp_gen::fn_sub_4B7E10_004b7e10__recomp},
    {"sub_4B7F30", 0x4B7F30, &recomp_gen::fn_sub_4B7F30_004b7f30, &recomp_gen::fn_sub_4B7F30_004b7f30__recomp},
    {"sub_4B7F80", 0x4B7F80, &recomp_gen::fn_sub_4B7F80_004b7f80, &recomp_gen::fn_sub_4B7F80_004b7f80__recomp},
    {"sub_4B7FD0", 0x4B7FD0, &recomp_gen::fn_sub_4B7FD0_004b7fd0, &recomp_gen::fn_sub_4B7FD0_004b7fd0__recomp},
    {"sub_4B8080", 0x4B8080, &recomp_gen::fn_sub_4B8080_004b8080, &recomp_gen::fn_sub_4B8080_004b8080__recomp},
    {"sub_4B8120", 0x4B8120, &recomp_gen::fn_sub_4B8120_004b8120, &recomp_gen::fn_sub_4B8120_004b8120__recomp},
    {"sub_4B81F0", 0x4B81F0, &recomp_gen::fn_sub_4B81F0_004b81f0, &recomp_gen::fn_sub_4B81F0_004b81f0__recomp},
    {"sub_4B8290", 0x4B8290, &recomp_gen::fn_sub_4B8290_004b8290, &recomp_gen::fn_sub_4B8290_004b8290__recomp},
    {"sub_4B82D0", 0x4B82D0, &recomp_gen::fn_sub_4B82D0_004b82d0, &recomp_gen::fn_sub_4B82D0_004b82d0__recomp},
    {"sub_4B83D0", 0x4B83D0, &recomp_gen::fn_sub_4B83D0_004b83d0, &recomp_gen::fn_sub_4B83D0_004b83d0__recomp},
    {"sub_4B8500", 0x4B8500, &recomp_gen::fn_sub_4B8500_004b8500, &recomp_gen::fn_sub_4B8500_004b8500__recomp},
    {"nullsub_125", 0x4B8610, &recomp_gen::fn_nullsub_125_004b8610, &recomp_gen::fn_nullsub_125_004b8610__recomp},
    {"nullsub_126", 0x4B8620, &recomp_gen::fn_nullsub_126_004b8620, &recomp_gen::fn_nullsub_126_004b8620__recomp},
    {"sub_4B8630", 0x4B8630, &recomp_gen::fn_sub_4B8630_004b8630, &recomp_gen::fn_sub_4B8630_004b8630__recomp},
    {"sub_4B8740", 0x4B8740, &recomp_gen::fn_sub_4B8740_004b8740, &recomp_gen::fn_sub_4B8740_004b8740__recomp},
    {"sub_4B87D0", 0x4B87D0, &recomp_gen::fn_sub_4B87D0_004b87d0, &recomp_gen::fn_sub_4B87D0_004b87d0__recomp},
    {"sub_4B8830", 0x4B8830, &recomp_gen::fn_sub_4B8830_004b8830, &recomp_gen::fn_sub_4B8830_004b8830__recomp},
    {"sub_4B88E0", 0x4B88E0, &recomp_gen::fn_sub_4B88E0_004b88e0, &recomp_gen::fn_sub_4B88E0_004b88e0__recomp},
    {"sub_4B8920", 0x4B8920, &recomp_gen::fn_sub_4B8920_004b8920, &recomp_gen::fn_sub_4B8920_004b8920__recomp},
    {"sub_4B89D0", 0x4B89D0, &recomp_gen::fn_sub_4B89D0_004b89d0, &recomp_gen::fn_sub_4B89D0_004b89d0__recomp},
    {"sub_4B8B10", 0x4B8B10, &recomp_gen::fn_sub_4B8B10_004b8b10, &recomp_gen::fn_sub_4B8B10_004b8b10__recomp},
    {"sub_4B8C30", 0x4B8C30, &recomp_gen::fn_sub_4B8C30_004b8c30, &recomp_gen::fn_sub_4B8C30_004b8c30__recomp},
    {"sub_4B8D50", 0x4B8D50, &recomp_gen::fn_sub_4B8D50_004b8d50, &recomp_gen::fn_sub_4B8D50_004b8d50__recomp},
    {"sub_4B8E70", 0x4B8E70, &recomp_gen::fn_sub_4B8E70_004b8e70, &recomp_gen::fn_sub_4B8E70_004b8e70__recomp},
    {"sub_4B9030", 0x4B9030, &recomp_gen::fn_sub_4B9030_004b9030, &recomp_gen::fn_sub_4B9030_004b9030__recomp},
    {"sub_4B90A0", 0x4B90A0, &recomp_gen::fn_sub_4B90A0_004b90a0, &recomp_gen::fn_sub_4B90A0_004b90a0__recomp},
    {"sub_4B9140", 0x4B9140, &recomp_gen::fn_sub_4B9140_004b9140, &recomp_gen::fn_sub_4B9140_004b9140__recomp},
    {"sub_4B91C0", 0x4B91C0, &recomp_gen::fn_sub_4B91C0_004b91c0, &recomp_gen::fn_sub_4B91C0_004b91c0__recomp},
    {"sub_4B92D0", 0x4B92D0, &recomp_gen::fn_sub_4B92D0_004b92d0, &recomp_gen::fn_sub_4B92D0_004b92d0__recomp},
    {"sub_4B9350", 0x4B9350, &recomp_gen::fn_sub_4B9350_004b9350, &recomp_gen::fn_sub_4B9350_004b9350__recomp},
    {"sub_4B9370", 0x4B9370, &recomp_gen::fn_sub_4B9370_004b9370, &recomp_gen::fn_sub_4B9370_004b9370__recomp},
    {"sub_4B96E0", 0x4B96E0, &recomp_gen::fn_sub_4B96E0_004b96e0, &recomp_gen::fn_sub_4B96E0_004b96e0__recomp},
    {"sub_4B96F0", 0x4B96F0, &recomp_gen::fn_sub_4B96F0_004b96f0, &recomp_gen::fn_sub_4B96F0_004b96f0__recomp},
    {"sub_4B97B0", 0x4B97B0, &recomp_gen::fn_sub_4B97B0_004b97b0, &recomp_gen::fn_sub_4B97B0_004b97b0__recomp},
    {"sub_4B97D0", 0x4B97D0, &recomp_gen::fn_sub_4B97D0_004b97d0, &recomp_gen::fn_sub_4B97D0_004b97d0__recomp},
    {"sub_4B97F0", 0x4B97F0, &recomp_gen::fn_sub_4B97F0_004b97f0, &recomp_gen::fn_sub_4B97F0_004b97f0__recomp},
    {"sub_4F7300", 0x4F7300, &recomp_gen::fn_sub_4F7300_004f7300, &recomp_gen::fn_sub_4F7300_004f7300__recomp},
    {"sub_4F7470", 0x4F7470, &recomp_gen::fn_sub_4F7470_004f7470, &recomp_gen::fn_sub_4F7470_004f7470__recomp},
    {"sub_4F7560", 0x4F7560, &recomp_gen::fn_sub_4F7560_004f7560, &recomp_gen::fn_sub_4F7560_004f7560__recomp},
    {"sub_4F7F40", 0x4F7F40, &recomp_gen::fn_sub_4F7F40_004f7f40, &recomp_gen::fn_sub_4F7F40_004f7f40__recomp},
    {"sub_4F8560", 0x4F8560, &recomp_gen::fn_sub_4F8560_004f8560, &recomp_gen::fn_sub_4F8560_004f8560__recomp},
    {"sub_4F8690", 0x4F8690, &recomp_gen::fn_sub_4F8690_004f8690, &recomp_gen::fn_sub_4F8690_004f8690__recomp},
    {"sub_4F8790", 0x4F8790, &recomp_gen::fn_sub_4F8790_004f8790, &recomp_gen::fn_sub_4F8790_004f8790__recomp},
    {"sub_4F87B0", 0x4F87B0, &recomp_gen::fn_sub_4F87B0_004f87b0, &recomp_gen::fn_sub_4F87B0_004f87b0__recomp},
    {"sub_4F8CB0", 0x4F8CB0, &recomp_gen::fn_sub_4F8CB0_004f8cb0, &recomp_gen::fn_sub_4F8CB0_004f8cb0__recomp},
    {"sub_4F8E10", 0x4F8E10, &recomp_gen::fn_sub_4F8E10_004f8e10, &recomp_gen::fn_sub_4F8E10_004f8e10__recomp},
    {"sub_35A290", 0x35A290, &recomp_gen::fn_sub_35A290_0035a290, &recomp_gen::fn_sub_35A290_0035a290__recomp},
    {"sub_35A3F0", 0x35A3F0, &recomp_gen::fn_sub_35A3F0_0035a3f0, &recomp_gen::fn_sub_35A3F0_0035a3f0__recomp},
    {"sub_35A620", 0x35A620, &recomp_gen::fn_sub_35A620_0035a620, &recomp_gen::fn_sub_35A620_0035a620__recomp},
    {"sub_35A6A0", 0x35A6A0, &recomp_gen::fn_sub_35A6A0_0035a6a0, &recomp_gen::fn_sub_35A6A0_0035a6a0__recomp},
    {"sub_35A770", 0x35A770, &recomp_gen::fn_sub_35A770_0035a770, &recomp_gen::fn_sub_35A770_0035a770__recomp},
    {"sub_35A850", 0x35A850, &recomp_gen::fn_sub_35A850_0035a850, &recomp_gen::fn_sub_35A850_0035a850__recomp},
    {"sub_35A870", 0x35A870, &recomp_gen::fn_sub_35A870_0035a870, &recomp_gen::fn_sub_35A870_0035a870__recomp},
    {"sub_35AA10", 0x35AA10, &recomp_gen::fn_sub_35AA10_0035aa10, &recomp_gen::fn_sub_35AA10_0035aa10__recomp},
    {"sub_35ABA0", 0x35ABA0, &recomp_gen::fn_sub_35ABA0_0035aba0, &recomp_gen::fn_sub_35ABA0_0035aba0__recomp},
    {"sub_464760", 0x464760, &recomp_gen::fn_sub_464760_00464760, &recomp_gen::fn_sub_464760_00464760__recomp},
    {"sub_464850", 0x464850, &recomp_gen::fn_sub_464850_00464850, &recomp_gen::fn_sub_464850_00464850__recomp},
    {"sub_464E80", 0x464E80, &recomp_gen::fn_sub_464E80_00464e80, &recomp_gen::fn_sub_464E80_00464e80__recomp},
    {"sub_4654A0", 0x4654A0, &recomp_gen::fn_sub_4654A0_004654a0, &recomp_gen::fn_sub_4654A0_004654a0__recomp},
    {"sub_465590", 0x465590, &recomp_gen::fn_sub_465590_00465590, &recomp_gen::fn_sub_465590_00465590__recomp},
    {"sub_465660", 0x465660, &recomp_gen::fn_sub_465660_00465660, &recomp_gen::fn_sub_465660_00465660__recomp},
    {"sub_465670", 0x465670, &recomp_gen::fn_sub_465670_00465670, &recomp_gen::fn_sub_465670_00465670__recomp},
    {"sub_4657D0", 0x4657D0, &recomp_gen::fn_sub_4657D0_004657d0, &recomp_gen::fn_sub_4657D0_004657d0__recomp},
    {"sub_465930", 0x465930, &recomp_gen::fn_sub_465930_00465930, &recomp_gen::fn_sub_465930_00465930__recomp},
    {"sub_465A00", 0x465A00, &recomp_gen::fn_sub_465A00_00465a00, &recomp_gen::fn_sub_465A00_00465a00__recomp},
    {"sub_465AE0", 0x465AE0, &recomp_gen::fn_sub_465AE0_00465ae0, &recomp_gen::fn_sub_465AE0_00465ae0__recomp},
    {"sub_465B20", 0x465B20, &recomp_gen::fn_sub_465B20_00465b20, &recomp_gen::fn_sub_465B20_00465b20__recomp},
    {"sub_465B40", 0x465B40, &recomp_gen::fn_sub_465B40_00465b40, &recomp_gen::fn_sub_465B40_00465b40__recomp},
    {"sub_465BF0", 0x465BF0, &recomp_gen::fn_sub_465BF0_00465bf0, &recomp_gen::fn_sub_465BF0_00465bf0__recomp},
    {"sub_465CF0", 0x465CF0, &recomp_gen::fn_sub_465CF0_00465cf0, &recomp_gen::fn_sub_465CF0_00465cf0__recomp},
    {"sub_465EB0", 0x465EB0, &recomp_gen::fn_sub_465EB0_00465eb0, &recomp_gen::fn_sub_465EB0_00465eb0__recomp},
    {"sub_466130", 0x466130, &recomp_gen::fn_sub_466130_00466130, &recomp_gen::fn_sub_466130_00466130__recomp},
    {"sub_4661B0", 0x4661B0, &recomp_gen::fn_sub_4661B0_004661b0, &recomp_gen::fn_sub_4661B0_004661b0__recomp},
    {"sub_466260", 0x466260, &recomp_gen::fn_sub_466260_00466260, &recomp_gen::fn_sub_466260_00466260__recomp},
    {"sub_466480", 0x466480, &recomp_gen::fn_sub_466480_00466480, &recomp_gen::fn_sub_466480_00466480__recomp},
    {"sub_466640", 0x466640, &recomp_gen::fn_sub_466640_00466640, &recomp_gen::fn_sub_466640_00466640__recomp},
    {"sub_466710", 0x466710, &recomp_gen::fn_sub_466710_00466710, &recomp_gen::fn_sub_466710_00466710__recomp},
    {"sub_466720", 0x466720, &recomp_gen::fn_sub_466720_00466720, &recomp_gen::fn_sub_466720_00466720__recomp},
    {"sub_466730", 0x466730, &recomp_gen::fn_sub_466730_00466730, &recomp_gen::fn_sub_466730_00466730__recomp},
    {"sub_466EF0", 0x466EF0, &recomp_gen::fn_sub_466EF0_00466ef0, &recomp_gen::fn_sub_466EF0_00466ef0__recomp},
    {"sub_489020", 0x489020, &recomp_gen::fn_sub_489020_00489020, &recomp_gen::fn_sub_489020_00489020__recomp},
    {"sub_489080", 0x489080, &recomp_gen::fn_sub_489080_00489080, &recomp_gen::fn_sub_489080_00489080__recomp},
    {"sub_489160", 0x489160, &recomp_gen::fn_sub_489160_00489160, &recomp_gen::fn_sub_489160_00489160__recomp},
    {"sub_489320", 0x489320, &recomp_gen::fn_sub_489320_00489320, &recomp_gen::fn_sub_489320_00489320__recomp},
    {"sub_489350", 0x489350, &recomp_gen::fn_sub_489350_00489350, &recomp_gen::fn_sub_489350_00489350__recomp},
    {"sub_4893E0", 0x4893E0, &recomp_gen::fn_sub_4893E0_004893e0, &recomp_gen::fn_sub_4893E0_004893e0__recomp},
    {"sub_489460", 0x489460, &recomp_gen::fn_sub_489460_00489460, &recomp_gen::fn_sub_489460_00489460__recomp},
    {"sub_489550", 0x489550, &recomp_gen::fn_sub_489550_00489550, &recomp_gen::fn_sub_489550_00489550__recomp},
    {"sub_489730", 0x489730, &recomp_gen::fn_sub_489730_00489730, &recomp_gen::fn_sub_489730_00489730__recomp},
    {"sub_489840", 0x489840, &recomp_gen::fn_sub_489840_00489840, &recomp_gen::fn_sub_489840_00489840__recomp},
    {"sub_4898C0", 0x4898C0, &recomp_gen::fn_sub_4898C0_004898c0, &recomp_gen::fn_sub_4898C0_004898c0__recomp},
    {"sub_4898E0", 0x4898E0, &recomp_gen::fn_sub_4898E0_004898e0, &recomp_gen::fn_sub_4898E0_004898e0__recomp},
    {"sub_489950", 0x489950, &recomp_gen::fn_sub_489950_00489950, &recomp_gen::fn_sub_489950_00489950__recomp},
    {"sub_489960", 0x489960, &recomp_gen::fn_sub_489960_00489960, &recomp_gen::fn_sub_489960_00489960__recomp},
    {"sub_4899A0", 0x4899A0, &recomp_gen::fn_sub_4899A0_004899a0, &recomp_gen::fn_sub_4899A0_004899a0__recomp},
    {"sub_4899BC", 0x4899BC, &recomp_gen::fn_sub_4899BC_004899bc, &recomp_gen::fn_sub_4899BC_004899bc__recomp},
    {"sub_4899D0", 0x4899D0, &recomp_gen::fn_sub_4899D0_004899d0, &recomp_gen::fn_sub_4899D0_004899d0__recomp},
    {"sub_4899F0", 0x4899F0, &recomp_gen::fn_sub_4899F0_004899f0, &recomp_gen::fn_sub_4899F0_004899f0__recomp},
    {"sub_489A80", 0x489A80, &recomp_gen::fn_sub_489A80_00489a80, &recomp_gen::fn_sub_489A80_00489a80__recomp},
    {"sub_489AE0", 0x489AE0, &recomp_gen::fn_sub_489AE0_00489ae0, &recomp_gen::fn_sub_489AE0_00489ae0__recomp},
    {"sub_489B70", 0x489B70, &recomp_gen::fn_sub_489B70_00489b70, &recomp_gen::fn_sub_489B70_00489b70__recomp},
    {"sub_489CD0", 0x489CD0, &recomp_gen::fn_sub_489CD0_00489cd0, &recomp_gen::fn_sub_489CD0_00489cd0__recomp},
    {"sub_489F20", 0x489F20, &recomp_gen::fn_sub_489F20_00489f20, &recomp_gen::fn_sub_489F20_00489f20__recomp},
    {"sub_48A180", 0x48A180, &recomp_gen::fn_sub_48A180_0048a180, &recomp_gen::fn_sub_48A180_0048a180__recomp},
    {"sub_48A190", 0x48A190, &recomp_gen::fn_sub_48A190_0048a190, &recomp_gen::fn_sub_48A190_0048a190__recomp},
    {"sub_48A1A0", 0x48A1A0, &recomp_gen::fn_sub_48A1A0_0048a1a0, &recomp_gen::fn_sub_48A1A0_0048a1a0__recomp},
    {"sub_48A2A0", 0x48A2A0, &recomp_gen::fn_sub_48A2A0_0048a2a0, &recomp_gen::fn_sub_48A2A0_0048a2a0__recomp},
    {"sub_48A2C0", 0x48A2C0, &recomp_gen::fn_sub_48A2C0_0048a2c0, &recomp_gen::fn_sub_48A2C0_0048a2c0__recomp},
    {"sub_48A2E0", 0x48A2E0, &recomp_gen::fn_sub_48A2E0_0048a2e0, &recomp_gen::fn_sub_48A2E0_0048a2e0__recomp},
    {"sub_48A370", 0x48A370, &recomp_gen::fn_sub_48A370_0048a370, &recomp_gen::fn_sub_48A370_0048a370__recomp},
    {"name__C9type_info", 0x48A3D0, &recomp_gen::fn_name__C9type_info_0048a3d0, &recomp_gen::fn_name__C9type_info_0048a3d0__recomp},
    {"sub_48A3F0", 0x48A3F0, &recomp_gen::fn_sub_48A3F0_0048a3f0, &recomp_gen::fn_sub_48A3F0_0048a3f0__recomp},
    {"sub_48A480", 0x48A480, &recomp_gen::fn_sub_48A480_0048a480, &recomp_gen::fn_sub_48A480_0048a480__recomp},
    {"sub_48A4B0", 0x48A4B0, &recomp_gen::fn_sub_48A4B0_0048a4b0, &recomp_gen::fn_sub_48A4B0_0048a4b0__recomp},
    {"sub_48A790", 0x48A790, &recomp_gen::fn_sub_48A790_0048a790, &recomp_gen::fn_sub_48A790_0048a790__recomp},
    {"sub_48A7A0", 0x48A7A0, &recomp_gen::fn_sub_48A7A0_0048a7a0, &recomp_gen::fn_sub_48A7A0_0048a7a0__recomp},
    {"sub_48A800", 0x48A800, &recomp_gen::fn_sub_48A800_0048a800, &recomp_gen::fn_sub_48A800_0048a800__recomp},
    {"sub_48A9A0", 0x48A9A0, &recomp_gen::fn_sub_48A9A0_0048a9a0, &recomp_gen::fn_sub_48A9A0_0048a9a0__recomp},
    {"sub_48ABF0", 0x48ABF0, &recomp_gen::fn_sub_48ABF0_0048abf0, &recomp_gen::fn_sub_48ABF0_0048abf0__recomp},
    {"sub_48AC00", 0x48AC00, &recomp_gen::fn_sub_48AC00_0048ac00, &recomp_gen::fn_sub_48AC00_0048ac00__recomp},
    {"sub_48AC10", 0x48AC10, &recomp_gen::fn_sub_48AC10_0048ac10, &recomp_gen::fn_sub_48AC10_0048ac10__recomp},
    {"sub_311730", 0x311730, &recomp_gen::fn_sub_311730_00311730, &recomp_gen::fn_sub_311730_00311730__recomp},
    {"sub_317730", 0x317730, &recomp_gen::fn_sub_317730_00317730, &recomp_gen::fn_sub_317730_00317730__recomp},
};

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// The generic sweep's world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// --- guest memory on the host ----------------------------------------------------------------------------------------
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va & 0x1FFFFFFu), 4); return v; }
s32 rs32(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va & 0x1FFFFFFu), 2); return v; }
s16 rs16(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
u8 r8(Machine& m, u32 va) { return *m.at(va & 0x1FFFFFFu); }
float rf(Machine& m, u32 va) { float v; std::memcpy(&v, m.at(va & 0x1FFFFFFu), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va & 0x1FFFFFFu), &v, 4); }
void wf(Machine& m, u32 va, float f) { std::memcpy(m.at(va & 0x1FFFFFFu), &f, 4); }
bool in_ram(u32 va) { return va >= 0x00100000u && va < 0x02000000u; }
s64 v0_of(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(r.end.gpr[GPR_V0].u64[0])); }
constexpr u64 S(s64 v) { return static_cast<u64>(v); }

// --- $f12 arguments: hgp::pair randomises the FPRs, so a time / weight argument is set by a wrapper around both bodies
// (the same host step in both runs, before the body's entry check point).
u32 g_f12 = 0;
Fn g_hand = nullptr, g_recomp = nullptr;
void hand_f12(EEContext& c) { c.fpr[12] = g_f12; g_hand(c); }
void recomp_f12(EEContext& c) { c.fpr[12] = g_f12; g_recomp(c); }
u32 bits(float f) { u32 b; std::memcpy(&b, &f, 4); return b; }
float flt(u32 b) { float f; std::memcpy(&f, &b, 4); return f; }

// Where the pairs stopped early (both bodies at the same stop: a callee not emitted in the test build), per test case.
std::map<std::string, int> g_stops;
hgp::Run tally(hgp::Run r, const char* fn) {
    if (r.stopped) ++g_stops[std::string(fn) + ": " + r.what];
    return r;
}
void report_stops(const char* what) {
    int n = 0;
    for (const auto& [k, v] : g_stops) n += v;
    const std::string line = std::string(what) + ": " + std::to_string(n) + " pairs stopped early (identically)";
    MESSAGE(line);
    for (const auto& [k, v] : g_stops) MESSAGE("  " << v << " x " << k);
    g_stops.clear();
}
hgp::Run pair_f12(Machine& m, const char* fn, Args a, float f12, u32 seed, const std::string& what) {
    const Case& c = find_case(fn);
    g_f12 = bits(f12);
    g_hand = c.hand;
    g_recomp = c.recomp;
    return tally(hgp::pair(m, &hand_f12, &recomp_f12, a, seed, (what + " " + fn).c_str()), fn);
}
hgp::Run pair_fn(Machine& m, const char* fn, Args a, u32 seed, const std::string& what) {
    const Case& c = find_case(fn);
    return tally(hgp::pair(m, c.hand, c.recomp, a, seed, (what + " " + fn).c_str()), fn);
}

// --- the documented formats ------------------------------------------------------------------------------------------
// The compressed scheme's 16-bit floats (cmpKeyFrameInterpolate's decode, cmpKeyFloatToHalf's encode): sign bit 15,
// a 4-bit exponent (bits 11..14) biased so that float exponent = e + 112, an 11-bit mantissa; 0x0000 / 0x8000 = 0.
float half_to_float(u16 h) {
    u32 b = static_cast<u32>(h & 0x8000u) << 16;
    if (h & 0x7FFFu) b |= ((static_cast<u32>(h & 0x7800u) << 12) + 0x38000000u) | (static_cast<u32>(h & 0x7FFu) << 12);
    return flt(b);
}
struct Quat { float x, y, z, w; };
struct V3 { float x, y, z; };
// RwMatrix: right, flags, up, pad, at, pad, pos, pad (row vectors; RwMatrixMultiply(dst, a, b) = a x b).
struct Mtx { V3 r, u, a, p; };
Mtx read_mtx(Machine& m, u32 va) {
    return {{rf(m, va), rf(m, va + 4), rf(m, va + 8)}, {rf(m, va + 16), rf(m, va + 20), rf(m, va + 24)},
            {rf(m, va + 32), rf(m, va + 36), rf(m, va + 40)}, {rf(m, va + 48), rf(m, va + 52), rf(m, va + 56)}};
}
// RpHAnimKeyFrameApply's matrix: right = (1 - 2(y2 + z2), 2(xy + wz), 2(xz - wy)), up = (2(xy - wz), 1 - 2(x2 + z2),
// 2(yz + wx)), at = (2(xz + wy), 2(yz - wx), 1 - 2(x2 + y2)), pos = the translation.
Mtx quat_mtx(Quat q, V3 t) {
    const float x = q.x, y = q.y, z = q.z, w = q.w;
    return {{1 - 2 * (y * y + z * z), 2 * (x * y + w * z), 2 * (x * z - w * y)},
            {2 * (x * y - w * z), 1 - 2 * (x * x + z * z), 2 * (y * z + w * x)},
            {2 * (x * z + w * y), 2 * (y * z - w * x), 1 - 2 * (x * x + y * y)},
            t};
}
V3 xform_vec(V3 v, const Mtx& b) {
    return {v.x * b.r.x + v.y * b.u.x + v.z * b.a.x, v.x * b.r.y + v.y * b.u.y + v.z * b.a.y, v.x * b.r.z + v.y * b.u.z + v.z * b.a.z};
}
Mtx mul(const Mtx& a, const Mtx& b) {
    Mtx o{xform_vec(a.r, b), xform_vec(a.u, b), xform_vec(a.a, b), xform_vec(a.p, b)};
    o.p = {o.p.x + b.p.x, o.p.y + b.p.y, o.p.z + b.p.z};
    return o;
}
float mdiff(const Mtx& a, const Mtx& b) {
    const float* x = &a.r.x;
    const float* y = &b.r.x;
    float d = 0;
    for (int i = 0; i < 12; ++i) {
        const float s = std::max(1.0f, std::fabs(y[i]));
        d = std::max(d, std::fabs(x[i] - y[i]) / s);
    }
    return d;
}

// --- the live animation records of a snapshot (the model lists, models.h) --------------------------------------------
struct LiveSlot {
    u32 model, slot, hier, itp, anim;
    s32 nodes;
};
std::vector<u32> live_models(Machine& m) {
    std::vector<u32> v;
    for (u32 kind = 0; kind < mdl::kMdlListCount; ++kind) {
        u32 p = r32(m, 0x9571F0u + 4 * kind);
        for (int n = 0; p && in_ram(p) && n < 64; ++n) {
            v.push_back(p);
            p = r32(m, p + mdl::kMdlNext);
        }
    }
    return v;
}
std::vector<LiveSlot> live_slots(Machine& m) {
    std::vector<LiveSlot> v;
    for (u32 model : live_models(m))
        for (u32 s = 0; s < mdl::kMdlSlotCount; ++s) {
            const u32 slot = model + mdl::kMdlSlots + mdl::kSlotSize * s;
            const u32 hier = r32(m, slot + mdl::kSlotHier);
            if (!in_ram(hier)) continue;
            const u32 itp = r32(m, hier + anim::kHierInterp);
            if (!in_ram(itp)) continue;
            const u32 an = r32(m, itp + anim::kItpAnim);
            v.push_back({model, slot, hier, itp, in_ram(an) ? an : 0u, rs32(m, hier + anim::kHierNumNodes)});
        }
    return v;
}

constexpr const char* kSnapshots[] = {"b_5800", "dorm_replay_4900", "climb_ref_17000"};

std::unique_ptr<Machine> snapshot_machine(const char* snapshot, std::vector<u8>& base) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    return m;
}

// Every interpolated frame of interpolator `itp` lies between its two keyframes (key1.time <= t <= key2.time, both
// keyframes inside the animation, key2's previous frame is key1 or a later keyframe of the node), and for the
// compressed scheme its translation is the lerp of the two decompressed keyframes, scaled and offset by the custom data.
int check_frames(Machine& m, u32 itp, const std::string& what) {
    const u32 an = r32(m, itp + anim::kItpAnim);
    const u32 info = r32(m, an + anim::kAnmInfo);
    const s32 nodes = rs32(m, itp + anim::kItpNumNodes);
    const s32 fsize = rs32(m, itp + anim::kItpFrameSize);
    const s32 ksize = rs32(m, info + anim::kInfoAnimFrameSize);
    const u32 frames = r32(m, an + anim::kAnmFrames);
    const u32 end = frames + static_cast<u32>(ksize * rs32(m, an + anim::kAnmNumFrames));
    const float t = rf(m, itp + anim::kItpTime);
    const bool compressed = rs32(m, info + anim::kInfoTypeId) == 2;
    const u32 custom = r32(m, an + anim::kAnmCustomData);
    int checks = 0;
    INFO(what << " itp " << hex64(itp) << " t=" << t);
    CHECK(t >= 0.0f);
    CHECK(t <= rf(m, an + anim::kAnmDuration) + 1e-4f);
    for (s32 i = 0; i < nodes; ++i) {
        const u32 f = itp + anim::kItpFrames + static_cast<u32>(i * fsize);
        const u32 k1 = r32(m, f + anim::kIfKey1), k2 = r32(m, f + anim::kIfKey2);
        INFO("node " << i << " key1 " << hex64(k1) << " key2 " << hex64(k2));
        CHECK(k1 >= frames);
        CHECK(k1 < end);
        CHECK(k2 >= frames);
        CHECK(k2 < end);
        const float t1 = rf(m, k1 + anim::kKfTime), t2 = rf(m, k2 + anim::kKfTime);
        CHECK(t1 <= t + 1e-4f);
        CHECK(t2 >= t - 1e-4f);
        ++checks;
        if (compressed && t2 > t1) {
            const float u = (t - t1) / (t2 - t1);
            for (int c = 0; c < 3; ++c) {
                const float a = half_to_float(r16(m, k1 + 16 + 2 * c)), b = half_to_float(r16(m, k2 + 16 + 2 * c));
                const float want = (a + (b - a) * u) * rf(m, custom + 12 + 4 * c) + rf(m, custom + 4 * c);
                const float got = rf(m, f + anim::kIfTrans + 4 * c);
                CHECK(std::fabs(got - want) <= 1e-3f * std::max(1.0f, std::fabs(want)));
            }
            Quat q{rf(m, f + 8), rf(m, f + 12), rf(m, f + 16), rf(m, f + 20)};
            const float len = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
            CHECK(std::fabs(len - 1.0f) < 2e-3f);
        }
    }
    return checks;
}

}  // namespace

TEST_CASE("game(anim): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// The snapshots' live interpolators: the time functions on every one (forward, backward, wrapping past the duration,
// restarting), each followed by the documented frame rule (check_frames) on the recompiled run's result.
TEST_CASE("game(anim): RtAnim on the snapshots' live interpolators") {
    int pairs = 0, rules = 0, snaps = 0, itps = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto mp = snapshot_machine(snap, base);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << snap);
            continue;
        }
        Machine& m = *mp;
        ++snaps;
        u32 seed = 1;
        for (const LiveSlot& s : live_slots(m)) {
            if (!s.anim) continue;
            ++itps;
            const std::string what = std::string(snap) + " model " + hex64(s.model);
            const float dur = rf(m, s.anim + anim::kAnmDuration);
            // the node count of the animation equals the interpolator's (and the hierarchy's)
            const hgp::Run nn = pair_fn(m, "sub_4B6DD0", {sx(s.anim), 0, 0, 0}, seed++, what);
            ++pairs;
            CHECK(v0_of(nn) == rs32(m, s.itp + anim::kItpNumNodes));
            CHECK(v0_of(nn) == s.nodes);
            rules += check_frames(m, s.itp, what + " as found");
            // 1. as the game runs them: the loop callback (mdlAnimEndCB) attached, so a wrap may restart, freeze or
            //    re-time the animation (models.cpp) -- pairs only
            const float t0 = rf(m, s.itp + anim::kItpTime);
            for (const float dt : {1.0f / 30.0f, 0.5f, dur}) {
                pair_f12(m, "sub_4B7240", {sx(s.itp), 0, 0, 0}, dt, seed++, what + " live dt=" + std::to_string(dt));
                ++pairs;
            }
            for (const float t : {t0, 0.0f}) {
                pair_f12(m, "sub_4B74C0", {sx(s.itp), 0, 0, 0}, t, seed++, what + " live t=" + std::to_string(t));
                ++pairs;
            }
            // 2. the documented rules, with the callbacks detached (the same bytes in both runs): restart, then the time
            //    functions forward, backward and past the duration
            w32(m, s.itp + anim::kItpLoopCallBack, 0);
            w32(m, s.itp + anim::kItpCallBack, 0);
            {
                const hgp::Run r = pair_fn(m, "sub_4B6EC0", {sx(s.itp), sx(s.anim), 0, 0}, seed++, what);
                ++pairs;
                CHECK(v0_of(r) == 1);
                CHECK(rf(m, s.itp + anim::kItpTime) == 0.0f);
                const u32 ksize = r32(m, r32(m, s.anim + anim::kAnmInfo) + anim::kInfoAnimFrameSize);
                CHECK(r32(m, s.itp + anim::kItpNextFrame) == r32(m, s.anim + anim::kAnmFrames) + 2 * ksize * static_cast<u32>(s.nodes));
                rules += check_frames(m, s.itp, what + " SetCurrentAnim");
            }
            for (const float t : {t0, t0 + 1.0f / 30.0f, t0 + 0.5f, t0 * 0.5f, 0.0f, dur * 0.97f, dur * 0.3f}) {
                if (t > dur) continue;
                const hgp::Run r = pair_f12(m, "sub_4B74C0", {sx(s.itp), 0, 0, 0}, t, seed++, what + " t=" + std::to_string(t));
                ++pairs;
                CHECK(v0_of(r) == 1);
                CHECK(std::fabs(rf(m, s.itp + anim::kItpTime) - t) <= 1e-4f * std::max(1.0f, dur));
                rules += check_frames(m, s.itp, what + " SetCurrentTime " + std::to_string(t));
            }
            for (const float dt : {1.0f / 60.0f, 1.0f / 30.0f, 0.0f, -0.5f, dur * 1.5f, 0.25f}) {
                const float before = rf(m, s.itp + anim::kItpTime);
                pair_f12(m, "sub_4B7240", {sx(s.itp), 0, 0, 0}, dt, seed++, what + " dt=" + std::to_string(dt));
                ++pairs;
                const float after = rf(m, s.itp + anim::kItpTime);
                if (dt <= 0.0f) {
                    CHECK(after == before);  // no step for dt <= 0
                } else {
                    float want = before + dt;  // the documented wrap: subtract the duration while past it
                    while (want > dur) want -= dur;
                    CHECK(std::fabs(after - want) <= 1e-4f * std::max(1.0f, dur));
                }
                rules += check_frames(m, s.itp, what + " AddAnimTime " + std::to_string(dt));
            }
            // interpolator copy into the outgoing blend interpolator when the slot has one of the same shape
            const u32 ia = r32(m, s.slot + mdl::kSlotInterpA);
            if (in_ram(ia) && rs32(m, ia + anim::kItpNumNodes) == s.nodes && r32(m, ia + anim::kItpFrameSize) == r32(m, s.itp + anim::kItpFrameSize)) {
                pair_fn(m, "sub_4B7020", {sx(ia), sx(s.itp), 0, 0}, seed++, what);
                ++pairs;
                CHECK(std::memcmp(m.at(ia + anim::kItpFrames), m.at(s.itp + anim::kItpFrames), r32(m, ia + anim::kItpFrameSize) * static_cast<u32>(s.nodes)) == 0);
                // and the blend of the two (weights 0, 0.5, 1)
                const u32 ib = r32(m, s.slot + mdl::kSlotInterpB);
                if (in_ram(ib) && rs32(m, ib + anim::kItpNumNodes) == s.nodes)
                    for (const float w : {0.0f, 0.5f, 1.0f}) {
                        pair_f12(m, "sub_4B7510", {sx(s.itp), sx(ia), sx(ib), 0}, w, seed++, what + " blend");
                        ++pairs;
                    }
            }
        }
    }
    report_stops("RtAnim");
    MESSAGE("RtAnim: " << snaps << " snapshots, " << itps << " live interpolators, " << pairs << " pairs, " << rules << " frame rules");
    if (snaps) CHECK(itps > 0);
}

// The snapshots' hierarchies: RpHAnimHierarchyUpdateMatrices on each (after a time step), then on the host: every node
// matrix is the keyframe apply of its interpolated frame times its parent's matrix, the parent taken from a stack the
// node flags drive (2 push, 1 pop) -- the documented RpHAnim walk.
TEST_CASE("game(anim): RpHAnim matrix update on the snapshots' hierarchies") {
    int pairs = 0, nodes_checked = 0, hiers = 0, snaps = 0, applies = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto mp = snapshot_machine(snap, base);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << snap);
            continue;
        }
        Machine& m = *mp;
        ++snaps;
        u32 seed = 100;
        for (const LiveSlot& s : live_slots(m)) {
            if (!s.anim) continue;
            const u32 flags = r32(m, s.hier + anim::kHierFlags);
            if (flags & 2u) continue;  // no matrix array (none in these snapshots)
            ++hiers;
            const std::string what = std::string(snap) + " hier " + hex64(s.hier);
            pair_f12(m, "sub_4B7240", {sx(s.itp), 0, 0, 0}, 1.0f / 30.0f, seed++, what);
            const hgp::Run r = pair_fn(m, "sub_466EF0", {sx(s.hier), 0, 0, 0}, seed++, what);
            pairs += 2;
            CHECK(v0_of(r) == 1);
            // the host walk
            const u32 mats = r32(m, s.hier + anim::kHierMatrices);
            const u32 info = r32(m, s.hier + anim::kHierNodeInfo);
            const s32 fsize = rs32(m, s.itp + anim::kItpFrameSize);
            std::vector<s32> stack;
            s32 parent = -1;  // the root's parent: the parent frame's chain (not recomputed here)
            for (s32 i = 0; i < s.nodes; ++i) {
                const u32 f = s.itp + anim::kItpFrames + static_cast<u32>(i * fsize);
                const Mtx local = quat_mtx({rf(m, f + 8), rf(m, f + 12), rf(m, f + 16), rf(m, f + 20)},
                                           {rf(m, f + 24), rf(m, f + 28), rf(m, f + 32)});
                const Mtx got = read_mtx(m, mats + 64u * static_cast<u32>(i));
                if (parent >= 0) {
                    const Mtx want = mul(local, read_mtx(m, mats + 64u * static_cast<u32>(parent)));
                    INFO(what << " node " << i << " parent " << parent << " diff " << mdiff(got, want));
                    CHECK(mdiff(got, want) < 2e-3f);
                    ++nodes_checked;
                }
                const s32 nf = rs32(m, info + 16u * static_cast<u32>(i) + anim::kNodeFlags);
                if (nf & 2) stack.push_back(parent);
                if (nf & 1) {
                    if (!stack.empty()) {
                        parent = stack.back();
                        stack.pop_back();
                    }
                } else {
                    parent = i;
                }
            }
            // the apply callback of the scheme on the first frames, into a scratch matrix
            const u32 apply = r32(m, s.itp + anim::kItpApplyCB);
            if (apply == 0x4F7470u)
                for (s32 i = 0; i < std::min(s.nodes, 4); ++i) {
                    const u32 f = s.itp + anim::kItpFrames + static_cast<u32>(i * fsize);
                    constexpr u32 kScratch = 0x01BF0000u;
                    pair_fn(m, "sub_4F7470", {sx(kScratch), sx(f), 0, 0}, seed++, what + " apply");
                    ++pairs;
                    ++applies;
                    const Mtx want = quat_mtx({rf(m, f + 8), rf(m, f + 12), rf(m, f + 16), rf(m, f + 20)},
                                              {rf(m, f + 24), rf(m, f + 28), rf(m, f + 32)});
                    CHECK(mdiff(read_mtx(m, kScratch), want) < 1e-5f);
                    CHECK(r32(m, kScratch + 12) == 3u);
                }
        }
    }
    report_stops("RpHAnim");
    MESSAGE("RpHAnim: " << snaps << " snapshots, " << hiers << " hierarchies, " << pairs << " pairs, " << nodes_checked
                        << " node matrices against the host walk, " << applies << " apply callbacks");
    if (snaps) CHECK(nodes_checked > 0);
}

// The model side on the snapshots: as found, every slot that plays a real animation has its time equal to its
// interpolator's (mdlAnimSlotUpdate, recompiled, copies it after each update -- the state a networked character
// carries); then the look-at hierarchy update sub_311730 on every live slot (hierarchy, slot, the slot's look record),
// and mdlModelUpdate on every ready top-level model (it runs until the first not-emitted callee, the recompiled slot
// update sub_313490, identically in both bodies).
TEST_CASE("game(anim): the model side on the snapshots") {
    int pairs = 0, snaps = 0, synced = 0, models = 0, looks = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto mp = snapshot_machine(snap, base);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << snap);
            continue;
        }
        Machine& m = *mp;
        ++snaps;
        u32 seed = 300;
        for (u32 model : live_models(m)) {
            if (!(r16(m, model + mdl::kMdlFlags) & 0x1000u)) continue;
            for (u32 sl = 0; sl < mdl::kMdlSlotCount; ++sl) {
                const u32 slot = model + mdl::kMdlSlots + mdl::kSlotSize * sl;
                const u32 hier = r32(m, slot + mdl::kSlotHier);
                if (!in_ram(hier)) continue;
                const s16 idx = rs16(m, slot + mdl::kSlotAnim);
                const u32 set = r32(m, slot + mdl::kSlotSet);
                if (idx >= 0 && in_ram(set) && idx < static_cast<s16>(r16(m, set + mdl::kSetCount)) && r8(m, slot + mdl::kSlotDone) != 1) {
                    const u32 an = r32(m, r32(m, set + mdl::kSetEntries) + mdl::kSetEntrySize * static_cast<u32>(idx) + mdl::kEntAnim);
                    if (in_ram(an) && an != 0x9571D0u) {
                        INFO(snap << " slot " << hex64(slot));
                        CHECK(rf(m, slot + mdl::kSlotTime) == rf(m, r32(m, hier + anim::kHierInterp) + anim::kItpTime));
                        ++synced;
                    }
                }
                const std::string what = std::string(snap) + " slot " + hex64(slot);
                pair_fn(m, "sub_311730", {sx(hier), sx(slot), sx(slot + mdl::kSlotLook), 0}, seed++, what);
                ++pairs;
                ++looks;
            }
        }
        for (u32 model : live_models(m)) {
            if (!(r16(m, model + mdl::kMdlFlags) & 0x1000u) || (r16(m, model + mdl::kMdlFlags) & 0x8000u)) continue;
            pair_fn(m, "sub_317730", {sx(model), 0, 0, 0}, seed++, std::string(snap) + " model " + hex64(model));
            ++pairs;
            ++models;
        }
    }
    report_stops("model side");
    MESSAGE("model side: " << snaps << " snapshots, " << pairs << " pairs, " << synced << " slot times equal to their interpolator's, "
                           << looks << " look-at updates, " << models << " model updates");
    if (snaps) CHECK(synced > 0);
}

// The snapshots' skins: every atomic of every model clump (RpClump +8 list, RpAtomic +64 link); its geometry's skin
// (RpSkinGeometryGetSkin), bone count, the atomic's skin type, and skinPrepareWeights on the real vertices; then the
// documented packing: weight slot k's low 10 bits are (bone index k (remapped for a partitioned skin) + 1) x 4 when the
// weight is non-zero, a zero weight stays 0, and the per-weight-count totals add up to the vertex count.
TEST_CASE("game(anim): RpSkin on the snapshots' skinned geometries") {
    int pairs = 0, skins = 0, vertices = 0, snaps = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto mp = snapshot_machine(snap, base);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << snap);
            continue;
        }
        Machine& m = *mp;
        ++snaps;
        const u32 geo_off = r32(m, 0x95DE18u);
        u32 seed = 500;
        std::vector<u32> seen;
        for (u32 model : live_models(m)) {
            const u32 clump = r32(m, model + mdl::kMdlClump);
            if (!in_ram(clump)) continue;
            const u32 head = clump + 8;
            u32 link = r32(m, head);
            for (int n = 0; link != head && in_ram(link) && n < 64; ++n, link = r32(m, link)) {
                const u32 atomic = link - 64;
                const u32 geo = r32(m, atomic + anim::kAtmGeometry);
                if (!in_ram(geo) || std::find(seen.begin(), seen.end(), geo) != seen.end()) continue;
                seen.push_back(geo);
                const std::string what = std::string(snap) + " geometry " + hex64(geo);
                const hgp::Run g = pair_fn(m, "sub_48A2C0", {sx(geo), 0, 0, 0}, seed++, what);
                pair_fn(m, "sub_48A480", {sx(atomic), 0, 0, 0}, seed++, what);
                pairs += 2;
                const u32 skin = static_cast<u32>(v0_of(g));
                CHECK(skin == r32(m, geo + geo_off));
                if (!in_ram(skin) || (r32(m, geo + anim::kGeoFlags) & 0x1000000u)) continue;
                ++skins;
                const hgp::Run nb = pair_fn(m, "name__C9type_info", {sx(skin), 0, 0, 0}, seed++, what);
                ++pairs;
                CHECK(v0_of(nb) == rs32(m, skin + anim::kSkinNumBones));
                pair_fn(m, "sub_48A4B0", {sx(geo), 0, 0, 0}, seed++, what);
                ++pairs;
                const u32 nv = r32(m, geo + anim::kGeoNumVertices);
                const u32 idx = r32(m, skin + anim::kSkinVertexIndices), wts = r32(m, skin + anim::kSkinVertexWeights);
                const bool split = r32(m, skin + anim::kSkinSplitNumMeshes) != 0;
                const u32 remap = r32(m, skin + anim::kSkinSplitRemap);
                u32 counts = 0;
                for (int k = 0; k < 4; ++k) counts += r32(m, skin + anim::kSkinWeightCounts + 4 * k);
                CHECK(counts == nv);
                for (u32 v = 0; v < nv; ++v) {
                    const u32 bones = r32(m, idx + 4 * v);
                    for (u32 k = 0; k < 4; ++k) {
                        const u32 w = r32(m, wts + 16 * v + 4 * k);
                        const u32 bone = (bones >> (8 * k)) & 0xFFu;
                        const u32 want = split ? r8(m, remap + bone) : bone;
                        if (k == 0 || flt(w) != 0.0f) {
                            INFO(what << " vertex " << v << " slot " << k);
                            CHECK((w & 0x3FFu) == ((want + 1u) << 2));
                        } else {
                            CHECK(w == 0u);
                        }
                    }
                    ++vertices;
                }
            }
        }
    }
    report_stops("RpSkin");
    MESSAGE("RpSkin: " << snaps << " snapshots, " << skins << " skins, " << pairs << " pairs, " << vertices << " vertices checked");
    if (snaps) CHECK(skins > 0);
}

// The compressed scheme's float packing (cmpKeyFloatToHalf, value in $f12): pairs over the range, and decode(encode(x))
// within the 11-bit mantissa of x for 2^-15 <= |x| <= 1 (zero below, the largest value above).
TEST_CASE("game(anim): cmpKeyFloatToHalf against the documented 16-bit format") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0xA417};
    int pairs = 0;
    for (int i = 0; i < 400; ++i) {
        const float x = i < 8 ? std::array<float, 8>{0.0f, 1.0f, -1.0f, 0.5f, 2.0f, 1e-6f, -3e-5f, 0.999f}[i]
                              : (static_cast<float>(rng() % 200001) - 100000.0f) / 100000.0f * (rng() % 2 ? 1.0f : 0.01f);
        const hgp::Run r = pair_f12(*m, "sub_4F7300", {0, 0, 0, 0}, x, static_cast<u32>(i + 1), "float " + std::to_string(x));
        ++pairs;
        const u16 h = static_cast<u16>(r.end.gpr[GPR_V0].u64[0]);
        const float back = half_to_float(h);
        const float ax = std::fabs(x);
        INFO("x=" << x << " h=" << hex64(h) << " back=" << back);
        if (ax > 1.0f) CHECK(std::fabs(back) >= 1.0f);
        else if (ax >= 1.0f / 32768.0f) CHECK(std::fabs(back - x) <= ax / 2048.0f + 1e-9f);
        else CHECK(std::fabs(back) <= 1.0f / 32768.0f);
        if (x != 0.0f && std::fabs(back) > 0.0f) CHECK((back < 0) == (x < 0));
    }
    MESSAGE("cmpKeyFloatToHalf: " << pairs << " pairs");
}

// Creation and destruction on the heap stand-ins: interpolators, animations, hierarchies (the free-list allocations
// through the 0x960188 / 0x96018C slots), sub-interpolators; the documented initial fields on the recompiled run.
TEST_CASE("game(anim): creation on the heap stand-ins") {
    std::vector<u8> base;
    auto mp = snapshot_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no snapshot b_5800");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    int pairs = 0;
    for (const auto& [nodes, size] : std::initializer_list<std::pair<u32, u32>>{{1, 36}, {94, 36}, {7, 52}, {40, 24}}) {
        const Case& c = find_case("sub_4B6E10");
        const SiPair p = run_pair_si(m, c.hand, c.recomp, {nodes, size, 0, 0}, nodes, "RtAnimInterpolatorCreate", hw);
        ++pairs;
        const u32 itp = static_cast<u32>(p.hw.recomp.base.v0);
        REQUIRE(itp != 0u);
        CHECK(p.recomp->heap.size_of(itp) >= 76 + nodes * size);
        CHECK(rs32(m, itp + anim::kItpNumNodes) == static_cast<s32>(nodes));
        CHECK(r32(m, itp + anim::kItpMaxFrameSize) == size);
        CHECK(r32(m, itp + anim::kItpFrameSize) == size);
        CHECK(rs32(m, itp + anim::kItpAnimFrameSize) == -1);
        CHECK(rf(m, itp + anim::kItpCallBackTime) == -1.0f);
        CHECK(r32(m, itp + anim::kItpParent) == itp);
        CHECK(r32(m, itp + anim::kItpAnim) == 0u);
    }
    // the live animations' node counts / schemes: a sub-interpolator of a live interpolator, and a fresh animation of the
    // compressed scheme (id 2)
    for (const LiveSlot& s : live_slots(m)) {
        if (!s.anim || s.nodes < 4) continue;
        const Case& c = find_case("sub_4B75D0");
        const SiPair p = run_pair_si(m, c.hand, c.recomp, {sx(s.itp), 2, S(s.nodes - 2), S(-1)}, 7, "CreateSubInterpolator", hw);
        ++pairs;
        const u32 sub = static_cast<u32>(p.hw.recomp.base.v0);
        REQUIRE(sub != 0u);
        CHECK(r32(m, sub + anim::kItpParent) == s.itp);
        CHECK(r32(m, sub + anim::kItpOffsetInParent) == 2u);
        CHECK(r32(m, sub + anim::kItpIsSub) == 1u);
        CHECK(rs32(m, sub + anim::kItpNumNodes) == s.nodes - 2);
        CHECK(r32(m, sub + anim::kItpMaxFrameSize) == r32(m, s.itp + anim::kItpMaxFrameSize));
        break;
    }
    for (const u32 frames : {4u, 100u}) {
        const Case& c = find_case("sub_4B6840");
        auto setup_f12 = [](StandInWorld& w) { install_standard(w); };
        g_f12 = bits(2.5f);
        g_hand = c.hand;
        g_recomp = c.recomp;
        const SiPair p = run_pair_si(m, &hand_f12, &recomp_f12, {2, frames, 0, 0}, frames, "RtAnimAnimationCreate", hw, setup_f12);
        ++pairs;
        const u32 an = static_cast<u32>(p.hw.recomp.base.v0);
        REQUIRE(an != 0u);
        CHECK(r32(m, an + anim::kAnmInfo) == 0x95FBE0u);  // the compressed scheme is the first registered
        CHECK(r32(m, an + anim::kAnmNumFrames) == frames);
        CHECK(rf(m, an + anim::kAnmDuration) == 2.5f);
        CHECK(r32(m, an + anim::kAnmFrames) == an + 24);
        CHECK(r32(m, an + anim::kAnmCustomData) == an + 24 + 24 * frames);
        CHECK(p.recomp->heap.size_of(an) >= 24 + 24 * frames + 24);
    }
    MESSAGE("creation: " << pairs << " pairs on the heap stand-ins");
}

#else

TEST_CASE("game(anim): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
