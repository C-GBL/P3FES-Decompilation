// Pair tests of the shops slice (game/src/facility/shops.cpp): the shop code of the facilities band 0x3DF4A0-0x417158.
// Every pair runs the hand body and its recompiled body from the same guest machine through tests/game/handgen_pairs.h --
// the whole register file and the cycle count at every check point and at the return / stop, all 32 MiB of RAM
// (write-tracked), the scratchpad, the BIOS window, the bus log -- and, except in the random-world case, on two
// identical stand-in worlds (tests/game/stand_ins.h plus the shop world below: the yen accessors, the sprite layer, the
// script parameters, recorders for the item / link callees the test build leaves out) whose call logs must match.
//
// Inputs: the p3fes_handgen random worlds for every function; the gate's shop route snapshots (shop_ref_4100 /
// shop_3700 / shop_3200: the pharmacy open) for the root state machine in every state, the tasks, steps, the background
// manager and the real element set; the real shop tables of the ELF for every shop type. Documented-rule checks: the
// root's transitions, the element animator's delay / end rules, find / all-done against a host walk, the money clamp
// (0..9,999,999), the category code, the sellable ranges, the lineup iterator, the comparators, the description fade,
// the background mode rule, the COMM handlers' facility number.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/shops.h"

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
namespace shop = p3fes::game::shop;

namespace p3fes::recomp_gen {
void fn_sub_3DF4A0_003df4a0(EEContext&);  // generated body
void fn_sub_3DF4A0_003df4a0__recomp(EEContext&);  // recompiled
void fn_sub_3DFAC0_003dfac0(EEContext&);  // generated body
void fn_sub_3DFAC0_003dfac0__recomp(EEContext&);  // recompiled
void fn_sub_3DFAE0_003dfae0(EEContext&);  // generated body
void fn_sub_3DFAE0_003dfae0__recomp(EEContext&);  // recompiled
void fn_sub_3DFEB0_003dfeb0(EEContext&);  // generated body
void fn_sub_3DFEB0_003dfeb0__recomp(EEContext&);  // recompiled
void fn_sub_3DFF00_003dff00(EEContext&);  // generated body
void fn_sub_3DFF00_003dff00__recomp(EEContext&);  // recompiled
void fn_sub_3DFF30_003dff30(EEContext&);  // generated body
void fn_sub_3DFF30_003dff30__recomp(EEContext&);  // recompiled
void fn_sub_3DFF80_003dff80(EEContext&);  // generated body
void fn_sub_3DFF80_003dff80__recomp(EEContext&);  // recompiled
void fn_sub_3DFFC0_003dffc0(EEContext&);  // generated body
void fn_sub_3DFFC0_003dffc0__recomp(EEContext&);  // recompiled
void fn_sub_3E0080_003e0080(EEContext&);  // generated body
void fn_sub_3E0080_003e0080__recomp(EEContext&);  // recompiled
void fn_sub_3E0260_003e0260(EEContext&);  // generated body
void fn_sub_3E0260_003e0260__recomp(EEContext&);  // recompiled
void fn_sub_3E0330_003e0330(EEContext&);  // generated body
void fn_sub_3E0330_003e0330__recomp(EEContext&);  // recompiled
void fn_sub_3E04E0_003e04e0(EEContext&);  // generated body
void fn_sub_3E04E0_003e04e0__recomp(EEContext&);  // recompiled
void fn_sub_3E0650_003e0650(EEContext&);  // generated body
void fn_sub_3E0650_003e0650__recomp(EEContext&);  // recompiled
void fn_sub_3E0680_003e0680(EEContext&);  // generated body
void fn_sub_3E0680_003e0680__recomp(EEContext&);  // recompiled
void fn_sub_3E0700_003e0700(EEContext&);  // generated body
void fn_sub_3E0700_003e0700__recomp(EEContext&);  // recompiled
void fn_fclShop_CreateShopDrawTasks_003e0780(EEContext&);  // generated body
void fn_fclShop_CreateShopDrawTasks_003e0780__recomp(EEContext&);  // recompiled
void fn_sub_3E0830_003e0830(EEContext&);  // generated body
void fn_sub_3E0830_003e0830__recomp(EEContext&);  // recompiled
void fn_fclShop_UpdateShopDrawTask_003e0870(EEContext&);  // generated body
void fn_fclShop_UpdateShopDrawTask_003e0870__recomp(EEContext&);  // recompiled
void fn_fclShop_UpdateShopDraw2Task_003e08e0(EEContext&);  // generated body
void fn_fclShop_UpdateShopDraw2Task_003e08e0__recomp(EEContext&);  // recompiled
void fn_sub_3E0920_003e0920(EEContext&);  // generated body
void fn_sub_3E0920_003e0920__recomp(EEContext&);  // recompiled
void fn_sub_3E0950_003e0950(EEContext&);  // generated body
void fn_sub_3E0950_003e0950__recomp(EEContext&);  // recompiled
void fn_sub_3E0BB0_003e0bb0(EEContext&);  // generated body
void fn_sub_3E0BB0_003e0bb0__recomp(EEContext&);  // recompiled
void fn_sub_3E0BC0_003e0bc0(EEContext&);  // generated body
void fn_sub_3E0BC0_003e0bc0__recomp(EEContext&);  // recompiled
void fn_sub_3E6400_003e6400(EEContext&);  // generated body
void fn_sub_3E6400_003e6400__recomp(EEContext&);  // recompiled
void fn_sub_3E6D40_003e6d40(EEContext&);  // generated body
void fn_sub_3E6D40_003e6d40__recomp(EEContext&);  // recompiled
void fn_sub_3E6D70_003e6d70(EEContext&);  // generated body
void fn_sub_3E6D70_003e6d70__recomp(EEContext&);  // recompiled
void fn_sub_3E6DC0_003e6dc0(EEContext&);  // generated body
void fn_sub_3E6DC0_003e6dc0__recomp(EEContext&);  // recompiled
void fn_sub_3E6E80_003e6e80(EEContext&);  // generated body
void fn_sub_3E6E80_003e6e80__recomp(EEContext&);  // recompiled
void fn_sub_3E86C0_003e86c0(EEContext&);  // generated body
void fn_sub_3E86C0_003e86c0__recomp(EEContext&);  // recompiled
void fn_sub_3E8740_003e8740(EEContext&);  // generated body
void fn_sub_3E8740_003e8740__recomp(EEContext&);  // recompiled
void fn_sub_3E87C0_003e87c0(EEContext&);  // generated body
void fn_sub_3E87C0_003e87c0__recomp(EEContext&);  // recompiled
void fn_sub_3E8830_003e8830(EEContext&);  // generated body
void fn_sub_3E8830_003e8830__recomp(EEContext&);  // recompiled
void fn_sub_3E8860_003e8860(EEContext&);  // generated body
void fn_sub_3E8860_003e8860__recomp(EEContext&);  // recompiled
void fn_sub_3E8E10_003e8e10(EEContext&);  // generated body
void fn_sub_3E8E10_003e8e10__recomp(EEContext&);  // recompiled
void fn_sub_3E8E20_003e8e20(EEContext&);  // generated body
void fn_sub_3E8E20_003e8e20__recomp(EEContext&);  // recompiled
void fn_sub_3E8FF0_003e8ff0(EEContext&);  // generated body
void fn_sub_3E8FF0_003e8ff0__recomp(EEContext&);  // recompiled
void fn_sub_3E90B0_003e90b0(EEContext&);  // generated body
void fn_sub_3E90B0_003e90b0__recomp(EEContext&);  // recompiled
void fn_sub_3E94F0_003e94f0(EEContext&);  // generated body
void fn_sub_3E94F0_003e94f0__recomp(EEContext&);  // recompiled
void fn_sub_3E96F0_003e96f0(EEContext&);  // generated body
void fn_sub_3E96F0_003e96f0__recomp(EEContext&);  // recompiled
void fn_sub_3E9790_003e9790(EEContext&);  // generated body
void fn_sub_3E9790_003e9790__recomp(EEContext&);  // recompiled
void fn_sub_3E97F0_003e97f0(EEContext&);  // generated body
void fn_sub_3E97F0_003e97f0__recomp(EEContext&);  // recompiled
void fn_sub_3E98B0_003e98b0(EEContext&);  // generated body
void fn_sub_3E98B0_003e98b0__recomp(EEContext&);  // recompiled
void fn_sub_3E9970_003e9970(EEContext&);  // generated body
void fn_sub_3E9970_003e9970__recomp(EEContext&);  // recompiled
void fn_sub_3E9A90_003e9a90(EEContext&);  // generated body
void fn_sub_3E9A90_003e9a90__recomp(EEContext&);  // recompiled
void fn_sub_3EA4D0_003ea4d0(EEContext&);  // generated body
void fn_sub_3EA4D0_003ea4d0__recomp(EEContext&);  // recompiled
void fn_sub_3EA560_003ea560(EEContext&);  // generated body
void fn_sub_3EA560_003ea560__recomp(EEContext&);  // recompiled
void fn_sub_3EA600_003ea600(EEContext&);  // generated body
void fn_sub_3EA600_003ea600__recomp(EEContext&);  // recompiled
void fn_sub_3EA6B0_003ea6b0(EEContext&);  // generated body
void fn_sub_3EA6B0_003ea6b0__recomp(EEContext&);  // recompiled
void fn_sub_3EA770_003ea770(EEContext&);  // generated body
void fn_sub_3EA770_003ea770__recomp(EEContext&);  // recompiled
void fn_sub_3EA7E0_003ea7e0(EEContext&);  // generated body
void fn_sub_3EA7E0_003ea7e0__recomp(EEContext&);  // recompiled
void fn_sub_3EAC40_003eac40(EEContext&);  // generated body
void fn_sub_3EAC40_003eac40__recomp(EEContext&);  // recompiled
void fn_sub_3EACB0_003eacb0(EEContext&);  // generated body
void fn_sub_3EACB0_003eacb0__recomp(EEContext&);  // recompiled
void fn_sub_3EE310_003ee310(EEContext&);  // generated body
void fn_sub_3EE310_003ee310__recomp(EEContext&);  // recompiled
void fn_sub_3EE3D0_003ee3d0(EEContext&);  // generated body
void fn_sub_3EE3D0_003ee3d0__recomp(EEContext&);  // recompiled
void fn_sub_3EE480_003ee480(EEContext&);  // generated body
void fn_sub_3EE480_003ee480__recomp(EEContext&);  // recompiled
void fn_sub_3EE510_003ee510(EEContext&);  // generated body
void fn_sub_3EE510_003ee510__recomp(EEContext&);  // recompiled
void fn_sub_3EE560_003ee560(EEContext&);  // generated body
void fn_sub_3EE560_003ee560__recomp(EEContext&);  // recompiled
void fn_sub_3EE570_003ee570(EEContext&);  // generated body
void fn_sub_3EE570_003ee570__recomp(EEContext&);  // recompiled
void fn_sub_3EE5F0_003ee5f0(EEContext&);  // generated body
void fn_sub_3EE5F0_003ee5f0__recomp(EEContext&);  // recompiled
void fn_sub_3EEC60_003eec60(EEContext&);  // generated body
void fn_sub_3EEC60_003eec60__recomp(EEContext&);  // recompiled
void fn_sub_3EED10_003eed10(EEContext&);  // generated body
void fn_sub_3EED10_003eed10__recomp(EEContext&);  // recompiled
void fn_sub_3EED90_003eed90(EEContext&);  // generated body
void fn_sub_3EED90_003eed90__recomp(EEContext&);  // recompiled
void fn_sub_3EEE10_003eee10(EEContext&);  // generated body
void fn_sub_3EEE10_003eee10__recomp(EEContext&);  // recompiled
void fn_sub_3EFB40_003efb40(EEContext&);  // generated body
void fn_sub_3EFB40_003efb40__recomp(EEContext&);  // recompiled
void fn_sub_3EFBC0_003efbc0(EEContext&);  // generated body
void fn_sub_3EFBC0_003efbc0__recomp(EEContext&);  // recompiled
void fn_sub_3EFC60_003efc60(EEContext&);  // generated body
void fn_sub_3EFC60_003efc60__recomp(EEContext&);  // recompiled
void fn_sub_3EFCA0_003efca0(EEContext&);  // generated body
void fn_sub_3EFCA0_003efca0__recomp(EEContext&);  // recompiled
void fn_sub_3EFCE0_003efce0(EEContext&);  // generated body
void fn_sub_3EFCE0_003efce0__recomp(EEContext&);  // recompiled
void fn_sub_3EFD70_003efd70(EEContext&);  // generated body
void fn_sub_3EFD70_003efd70__recomp(EEContext&);  // recompiled
void fn_sub_3EFDE0_003efde0(EEContext&);  // generated body
void fn_sub_3EFDE0_003efde0__recomp(EEContext&);  // recompiled
void fn_sub_3EFE60_003efe60(EEContext&);  // generated body
void fn_sub_3EFE60_003efe60__recomp(EEContext&);  // recompiled
void fn_sub_3EFED0_003efed0(EEContext&);  // generated body
void fn_sub_3EFED0_003efed0__recomp(EEContext&);  // recompiled
void fn_sub_3EFEF0_003efef0(EEContext&);  // generated body
void fn_sub_3EFEF0_003efef0__recomp(EEContext&);  // recompiled
void fn_sub_3EFF00_003eff00(EEContext&);  // generated body
void fn_sub_3EFF00_003eff00__recomp(EEContext&);  // recompiled
void fn_sub_3EFFF0_003efff0(EEContext&);  // generated body
void fn_sub_3EFFF0_003efff0__recomp(EEContext&);  // recompiled
void fn_sub_3F0090_003f0090(EEContext&);  // generated body
void fn_sub_3F0090_003f0090__recomp(EEContext&);  // recompiled
void fn_sub_3F00D0_003f00d0(EEContext&);  // generated body
void fn_sub_3F00D0_003f00d0__recomp(EEContext&);  // recompiled
void fn_sub_3F01D0_003f01d0(EEContext&);  // generated body
void fn_sub_3F01D0_003f01d0__recomp(EEContext&);  // recompiled
void fn_sub_3F0240_003f0240(EEContext&);  // generated body
void fn_sub_3F0240_003f0240__recomp(EEContext&);  // recompiled
void fn_sub_3F0350_003f0350(EEContext&);  // generated body
void fn_sub_3F0350_003f0350__recomp(EEContext&);  // recompiled
void fn_sub_3F03E0_003f03e0(EEContext&);  // generated body
void fn_sub_3F03E0_003f03e0__recomp(EEContext&);  // recompiled
void fn_sub_3F06E0_003f06e0(EEContext&);  // generated body
void fn_sub_3F06E0_003f06e0__recomp(EEContext&);  // recompiled
void fn_sub_3F0830_003f0830(EEContext&);  // generated body
void fn_sub_3F0830_003f0830__recomp(EEContext&);  // recompiled
void fn_sub_3F0D60_003f0d60(EEContext&);  // generated body
void fn_sub_3F0D60_003f0d60__recomp(EEContext&);  // recompiled
void fn_sub_3F10B0_003f10b0(EEContext&);  // generated body
void fn_sub_3F10B0_003f10b0__recomp(EEContext&);  // recompiled
void fn_sub_3F1470_003f1470(EEContext&);  // generated body
void fn_sub_3F1470_003f1470__recomp(EEContext&);  // recompiled
void fn_sub_3F15D0_003f15d0(EEContext&);  // generated body
void fn_sub_3F15D0_003f15d0__recomp(EEContext&);  // recompiled
void fn_sub_3F1720_003f1720(EEContext&);  // generated body
void fn_sub_3F1720_003f1720__recomp(EEContext&);  // recompiled
void fn_sub_3F1830_003f1830(EEContext&);  // generated body
void fn_sub_3F1830_003f1830__recomp(EEContext&);  // recompiled
void fn_sub_3F1A10_003f1a10(EEContext&);  // generated body
void fn_sub_3F1A10_003f1a10__recomp(EEContext&);  // recompiled
void fn_sub_3F2240_003f2240(EEContext&);  // generated body
void fn_sub_3F2240_003f2240__recomp(EEContext&);  // recompiled
void fn_sub_3F2510_003f2510(EEContext&);  // generated body
void fn_sub_3F2510_003f2510__recomp(EEContext&);  // recompiled
void fn_sub_3F2D60_003f2d60(EEContext&);  // generated body
void fn_sub_3F2D60_003f2d60__recomp(EEContext&);  // recompiled
void fn_sub_3F2DC0_003f2dc0(EEContext&);  // generated body
void fn_sub_3F2DC0_003f2dc0__recomp(EEContext&);  // recompiled
void fn_sub_3F3280_003f3280(EEContext&);  // generated body
void fn_sub_3F3280_003f3280__recomp(EEContext&);  // recompiled
void fn_sub_3F3970_003f3970(EEContext&);  // generated body
void fn_sub_3F3970_003f3970__recomp(EEContext&);  // recompiled
void fn_sub_3F3DC0_003f3dc0(EEContext&);  // generated body
void fn_sub_3F3DC0_003f3dc0__recomp(EEContext&);  // recompiled
void fn_sub_3F3F00_003f3f00(EEContext&);  // generated body
void fn_sub_3F3F00_003f3f00__recomp(EEContext&);  // recompiled
void fn_sub_3F7730_003f7730(EEContext&);  // generated body
void fn_sub_3F7730_003f7730__recomp(EEContext&);  // recompiled
void fn_sub_3F98F0_003f98f0(EEContext&);  // generated body
void fn_sub_3F98F0_003f98f0__recomp(EEContext&);  // recompiled
void fn_sub_3F99D0_003f99d0(EEContext&);  // generated body
void fn_sub_3F99D0_003f99d0__recomp(EEContext&);  // recompiled
void fn_sub_3F9B20_003f9b20(EEContext&);  // generated body
void fn_sub_3F9B20_003f9b20__recomp(EEContext&);  // recompiled
void fn_sub_3F9CB0_003f9cb0(EEContext&);  // generated body
void fn_sub_3F9CB0_003f9cb0__recomp(EEContext&);  // recompiled
void fn_sub_3FA0D0_003fa0d0(EEContext&);  // generated body
void fn_sub_3FA0D0_003fa0d0__recomp(EEContext&);  // recompiled
void fn_sub_3FA190_003fa190(EEContext&);  // generated body
void fn_sub_3FA190_003fa190__recomp(EEContext&);  // recompiled
void fn_sub_3FA1B0_003fa1b0(EEContext&);  // generated body
void fn_sub_3FA1B0_003fa1b0__recomp(EEContext&);  // recompiled
void fn_sub_3FA1E0_003fa1e0(EEContext&);  // generated body
void fn_sub_3FA1E0_003fa1e0__recomp(EEContext&);  // recompiled
void fn_sub_3FB290_003fb290(EEContext&);  // generated body
void fn_sub_3FB290_003fb290__recomp(EEContext&);  // recompiled
void fn_sub_3FBF20_003fbf20(EEContext&);  // generated body
void fn_sub_3FBF20_003fbf20__recomp(EEContext&);  // recompiled
void fn_sub_3FC980_003fc980(EEContext&);  // generated body
void fn_sub_3FC980_003fc980__recomp(EEContext&);  // recompiled
void fn_sub_3FFA20_003ffa20(EEContext&);  // generated body
void fn_sub_3FFA20_003ffa20__recomp(EEContext&);  // recompiled
void fn_sub_3FFE00_003ffe00(EEContext&);  // generated body
void fn_sub_3FFE00_003ffe00__recomp(EEContext&);  // recompiled
void fn_sub_400690_00400690(EEContext&);  // generated body
void fn_sub_400690_00400690__recomp(EEContext&);  // recompiled
void fn_sub_400740_00400740(EEContext&);  // generated body
void fn_sub_400740_00400740__recomp(EEContext&);  // recompiled
void fn_sub_400A90_00400a90(EEContext&);  // generated body
void fn_sub_400A90_00400a90__recomp(EEContext&);  // recompiled
void fn_sub_400B90_00400b90(EEContext&);  // generated body
void fn_sub_400B90_00400b90__recomp(EEContext&);  // recompiled
void fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60(EEContext&);  // generated body
void fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60__recomp(EEContext&);  // recompiled
void fn_sub_401170_00401170(EEContext&);  // generated body
void fn_sub_401170_00401170__recomp(EEContext&);  // recompiled
void fn_fclShopMisc_UpdateShopDrawBGLowTask_00401210(EEContext&);  // generated body
void fn_fclShopMisc_UpdateShopDrawBGLowTask_00401210__recomp(EEContext&);  // recompiled
void fn_fclShopMisc_UpdateShopDrawBGHighLowTask_004012c0(EEContext&);  // generated body
void fn_fclShopMisc_UpdateShopDrawBGHighLowTask_004012c0__recomp(EEContext&);  // recompiled
void fn_fclShopMisc_UpdateShopDrawBGHighTopTask_00401370(EEContext&);  // generated body
void fn_fclShopMisc_UpdateShopDrawBGHighTopTask_00401370__recomp(EEContext&);  // recompiled
void fn_sub_401420_00401420(EEContext&);  // generated body
void fn_sub_401420_00401420__recomp(EEContext&);  // recompiled
void fn_sub_4014E0_004014e0(EEContext&);  // generated body
void fn_sub_4014E0_004014e0__recomp(EEContext&);  // recompiled
void fn_sub_4015A0_004015a0(EEContext&);  // generated body
void fn_sub_4015A0_004015a0__recomp(EEContext&);  // recompiled
void fn_sub_4015E0_004015e0(EEContext&);  // generated body
void fn_sub_4015E0_004015e0__recomp(EEContext&);  // recompiled
void fn_sub_401600_00401600(EEContext&);  // generated body
void fn_sub_401600_00401600__recomp(EEContext&);  // recompiled
void fn_sub_40D410_0040d410(EEContext&);  // generated body
void fn_sub_40D410_0040d410__recomp(EEContext&);  // recompiled
void fn_sub_40D490_0040d490(EEContext&);  // generated body
void fn_sub_40D490_0040d490__recomp(EEContext&);  // recompiled
void fn_sub_40D5E0_0040d5e0(EEContext&);  // generated body
void fn_sub_40D5E0_0040d5e0__recomp(EEContext&);  // recompiled
void fn_sub_40D610_0040d610(EEContext&);  // generated body
void fn_sub_40D610_0040d610__recomp(EEContext&);  // recompiled
void fn_sub_40E300_0040e300(EEContext&);  // generated body
void fn_sub_40E300_0040e300__recomp(EEContext&);  // recompiled
void fn_sub_40E390_0040e390(EEContext&);  // generated body
void fn_sub_40E390_0040e390__recomp(EEContext&);  // recompiled
void fn_sub_40E3C0_0040e3c0(EEContext&);  // generated body
void fn_sub_40E3C0_0040e3c0__recomp(EEContext&);  // recompiled
void fn_sub_40E3F0_0040e3f0(EEContext&);  // generated body
void fn_sub_40E3F0_0040e3f0__recomp(EEContext&);  // recompiled
void fn_sub_40E450_0040e450(EEContext&);  // generated body
void fn_sub_40E450_0040e450__recomp(EEContext&);  // recompiled
void fn_sub_40E4F0_0040e4f0(EEContext&);  // generated body
void fn_sub_40E4F0_0040e4f0__recomp(EEContext&);  // recompiled
void fn_sub_40E580_0040e580(EEContext&);  // generated body
void fn_sub_40E580_0040e580__recomp(EEContext&);  // recompiled
void fn_sub_40E610_0040e610(EEContext&);  // generated body
void fn_sub_40E610_0040e610__recomp(EEContext&);  // recompiled
void fn_sub_40E710_0040e710(EEContext&);  // generated body
void fn_sub_40E710_0040e710__recomp(EEContext&);  // recompiled
void fn_sub_40EB50_0040eb50(EEContext&);  // generated body
void fn_sub_40EB50_0040eb50__recomp(EEContext&);  // recompiled
void fn_sub_40EC20_0040ec20(EEContext&);  // generated body
void fn_sub_40EC20_0040ec20__recomp(EEContext&);  // recompiled
void fn_sub_40EC50_0040ec50(EEContext&);  // generated body
void fn_sub_40EC50_0040ec50__recomp(EEContext&);  // recompiled
void fn_sub_40EEF0_0040eef0(EEContext&);  // generated body
void fn_sub_40EEF0_0040eef0__recomp(EEContext&);  // recompiled
void fn_sub_410D30_00410d30(EEContext&);  // generated body
void fn_sub_410D30_00410d30__recomp(EEContext&);  // recompiled
void fn_sub_410E70_00410e70(EEContext&);  // generated body
void fn_sub_410E70_00410e70__recomp(EEContext&);  // recompiled
void fn_sub_4110F0_004110f0(EEContext&);  // generated body
void fn_sub_4110F0_004110f0__recomp(EEContext&);  // recompiled
void fn_sub_411190_00411190(EEContext&);  // generated body
void fn_sub_411190_00411190__recomp(EEContext&);  // recompiled
void fn_sub_411340_00411340(EEContext&);  // generated body
void fn_sub_411340_00411340__recomp(EEContext&);  // recompiled
void fn_sub_412580_00412580(EEContext&);  // generated body
void fn_sub_412580_00412580__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_3DF4A0", 0x3DF4A0, &recomp_gen::fn_sub_3DF4A0_003df4a0, &recomp_gen::fn_sub_3DF4A0_003df4a0__recomp},
    {"sub_3DFAC0", 0x3DFAC0, &recomp_gen::fn_sub_3DFAC0_003dfac0, &recomp_gen::fn_sub_3DFAC0_003dfac0__recomp},
    {"sub_3DFAE0", 0x3DFAE0, &recomp_gen::fn_sub_3DFAE0_003dfae0, &recomp_gen::fn_sub_3DFAE0_003dfae0__recomp},
    {"sub_3DFEB0", 0x3DFEB0, &recomp_gen::fn_sub_3DFEB0_003dfeb0, &recomp_gen::fn_sub_3DFEB0_003dfeb0__recomp},
    {"sub_3DFF00", 0x3DFF00, &recomp_gen::fn_sub_3DFF00_003dff00, &recomp_gen::fn_sub_3DFF00_003dff00__recomp},
    {"sub_3DFF30", 0x3DFF30, &recomp_gen::fn_sub_3DFF30_003dff30, &recomp_gen::fn_sub_3DFF30_003dff30__recomp},
    {"sub_3DFF80", 0x3DFF80, &recomp_gen::fn_sub_3DFF80_003dff80, &recomp_gen::fn_sub_3DFF80_003dff80__recomp},
    {"sub_3DFFC0", 0x3DFFC0, &recomp_gen::fn_sub_3DFFC0_003dffc0, &recomp_gen::fn_sub_3DFFC0_003dffc0__recomp},
    {"sub_3E0080", 0x3E0080, &recomp_gen::fn_sub_3E0080_003e0080, &recomp_gen::fn_sub_3E0080_003e0080__recomp},
    {"sub_3E0260", 0x3E0260, &recomp_gen::fn_sub_3E0260_003e0260, &recomp_gen::fn_sub_3E0260_003e0260__recomp},
    {"sub_3E0330", 0x3E0330, &recomp_gen::fn_sub_3E0330_003e0330, &recomp_gen::fn_sub_3E0330_003e0330__recomp},
    {"sub_3E04E0", 0x3E04E0, &recomp_gen::fn_sub_3E04E0_003e04e0, &recomp_gen::fn_sub_3E04E0_003e04e0__recomp},
    {"sub_3E0650", 0x3E0650, &recomp_gen::fn_sub_3E0650_003e0650, &recomp_gen::fn_sub_3E0650_003e0650__recomp},
    {"sub_3E0680", 0x3E0680, &recomp_gen::fn_sub_3E0680_003e0680, &recomp_gen::fn_sub_3E0680_003e0680__recomp},
    {"sub_3E0700", 0x3E0700, &recomp_gen::fn_sub_3E0700_003e0700, &recomp_gen::fn_sub_3E0700_003e0700__recomp},
    {"fclShop_CreateShopDrawTasks", 0x3E0780, &recomp_gen::fn_fclShop_CreateShopDrawTasks_003e0780, &recomp_gen::fn_fclShop_CreateShopDrawTasks_003e0780__recomp},
    {"sub_3E0830", 0x3E0830, &recomp_gen::fn_sub_3E0830_003e0830, &recomp_gen::fn_sub_3E0830_003e0830__recomp},
    {"fclShop_UpdateShopDrawTask", 0x3E0870, &recomp_gen::fn_fclShop_UpdateShopDrawTask_003e0870, &recomp_gen::fn_fclShop_UpdateShopDrawTask_003e0870__recomp},
    {"fclShop_UpdateShopDraw2Task", 0x3E08E0, &recomp_gen::fn_fclShop_UpdateShopDraw2Task_003e08e0, &recomp_gen::fn_fclShop_UpdateShopDraw2Task_003e08e0__recomp},
    {"sub_3E0920", 0x3E0920, &recomp_gen::fn_sub_3E0920_003e0920, &recomp_gen::fn_sub_3E0920_003e0920__recomp},
    {"sub_3E0950", 0x3E0950, &recomp_gen::fn_sub_3E0950_003e0950, &recomp_gen::fn_sub_3E0950_003e0950__recomp},
    {"sub_3E0BB0", 0x3E0BB0, &recomp_gen::fn_sub_3E0BB0_003e0bb0, &recomp_gen::fn_sub_3E0BB0_003e0bb0__recomp},
    {"sub_3E0BC0", 0x3E0BC0, &recomp_gen::fn_sub_3E0BC0_003e0bc0, &recomp_gen::fn_sub_3E0BC0_003e0bc0__recomp},
    {"sub_3E6400", 0x3E6400, &recomp_gen::fn_sub_3E6400_003e6400, &recomp_gen::fn_sub_3E6400_003e6400__recomp},
    {"sub_3E6D40", 0x3E6D40, &recomp_gen::fn_sub_3E6D40_003e6d40, &recomp_gen::fn_sub_3E6D40_003e6d40__recomp},
    {"sub_3E6D70", 0x3E6D70, &recomp_gen::fn_sub_3E6D70_003e6d70, &recomp_gen::fn_sub_3E6D70_003e6d70__recomp},
    {"sub_3E6DC0", 0x3E6DC0, &recomp_gen::fn_sub_3E6DC0_003e6dc0, &recomp_gen::fn_sub_3E6DC0_003e6dc0__recomp},
    {"sub_3E6E80", 0x3E6E80, &recomp_gen::fn_sub_3E6E80_003e6e80, &recomp_gen::fn_sub_3E6E80_003e6e80__recomp},
    {"sub_3E86C0", 0x3E86C0, &recomp_gen::fn_sub_3E86C0_003e86c0, &recomp_gen::fn_sub_3E86C0_003e86c0__recomp},
    {"sub_3E8740", 0x3E8740, &recomp_gen::fn_sub_3E8740_003e8740, &recomp_gen::fn_sub_3E8740_003e8740__recomp},
    {"sub_3E87C0", 0x3E87C0, &recomp_gen::fn_sub_3E87C0_003e87c0, &recomp_gen::fn_sub_3E87C0_003e87c0__recomp},
    {"sub_3E8830", 0x3E8830, &recomp_gen::fn_sub_3E8830_003e8830, &recomp_gen::fn_sub_3E8830_003e8830__recomp},
    {"sub_3E8860", 0x3E8860, &recomp_gen::fn_sub_3E8860_003e8860, &recomp_gen::fn_sub_3E8860_003e8860__recomp},
    {"sub_3E8E10", 0x3E8E10, &recomp_gen::fn_sub_3E8E10_003e8e10, &recomp_gen::fn_sub_3E8E10_003e8e10__recomp},
    {"sub_3E8E20", 0x3E8E20, &recomp_gen::fn_sub_3E8E20_003e8e20, &recomp_gen::fn_sub_3E8E20_003e8e20__recomp},
    {"sub_3E8FF0", 0x3E8FF0, &recomp_gen::fn_sub_3E8FF0_003e8ff0, &recomp_gen::fn_sub_3E8FF0_003e8ff0__recomp},
    {"sub_3E90B0", 0x3E90B0, &recomp_gen::fn_sub_3E90B0_003e90b0, &recomp_gen::fn_sub_3E90B0_003e90b0__recomp},
    {"sub_3E94F0", 0x3E94F0, &recomp_gen::fn_sub_3E94F0_003e94f0, &recomp_gen::fn_sub_3E94F0_003e94f0__recomp},
    {"sub_3E96F0", 0x3E96F0, &recomp_gen::fn_sub_3E96F0_003e96f0, &recomp_gen::fn_sub_3E96F0_003e96f0__recomp},
    {"sub_3E9790", 0x3E9790, &recomp_gen::fn_sub_3E9790_003e9790, &recomp_gen::fn_sub_3E9790_003e9790__recomp},
    {"sub_3E97F0", 0x3E97F0, &recomp_gen::fn_sub_3E97F0_003e97f0, &recomp_gen::fn_sub_3E97F0_003e97f0__recomp},
    {"sub_3E98B0", 0x3E98B0, &recomp_gen::fn_sub_3E98B0_003e98b0, &recomp_gen::fn_sub_3E98B0_003e98b0__recomp},
    {"sub_3E9970", 0x3E9970, &recomp_gen::fn_sub_3E9970_003e9970, &recomp_gen::fn_sub_3E9970_003e9970__recomp},
    {"sub_3E9A90", 0x3E9A90, &recomp_gen::fn_sub_3E9A90_003e9a90, &recomp_gen::fn_sub_3E9A90_003e9a90__recomp},
    {"sub_3EA4D0", 0x3EA4D0, &recomp_gen::fn_sub_3EA4D0_003ea4d0, &recomp_gen::fn_sub_3EA4D0_003ea4d0__recomp},
    {"sub_3EA560", 0x3EA560, &recomp_gen::fn_sub_3EA560_003ea560, &recomp_gen::fn_sub_3EA560_003ea560__recomp},
    {"sub_3EA600", 0x3EA600, &recomp_gen::fn_sub_3EA600_003ea600, &recomp_gen::fn_sub_3EA600_003ea600__recomp},
    {"sub_3EA6B0", 0x3EA6B0, &recomp_gen::fn_sub_3EA6B0_003ea6b0, &recomp_gen::fn_sub_3EA6B0_003ea6b0__recomp},
    {"sub_3EA770", 0x3EA770, &recomp_gen::fn_sub_3EA770_003ea770, &recomp_gen::fn_sub_3EA770_003ea770__recomp},
    {"sub_3EA7E0", 0x3EA7E0, &recomp_gen::fn_sub_3EA7E0_003ea7e0, &recomp_gen::fn_sub_3EA7E0_003ea7e0__recomp},
    {"sub_3EAC40", 0x3EAC40, &recomp_gen::fn_sub_3EAC40_003eac40, &recomp_gen::fn_sub_3EAC40_003eac40__recomp},
    {"sub_3EACB0", 0x3EACB0, &recomp_gen::fn_sub_3EACB0_003eacb0, &recomp_gen::fn_sub_3EACB0_003eacb0__recomp},
    {"sub_3EE310", 0x3EE310, &recomp_gen::fn_sub_3EE310_003ee310, &recomp_gen::fn_sub_3EE310_003ee310__recomp},
    {"sub_3EE3D0", 0x3EE3D0, &recomp_gen::fn_sub_3EE3D0_003ee3d0, &recomp_gen::fn_sub_3EE3D0_003ee3d0__recomp},
    {"sub_3EE480", 0x3EE480, &recomp_gen::fn_sub_3EE480_003ee480, &recomp_gen::fn_sub_3EE480_003ee480__recomp},
    {"sub_3EE510", 0x3EE510, &recomp_gen::fn_sub_3EE510_003ee510, &recomp_gen::fn_sub_3EE510_003ee510__recomp},
    {"sub_3EE560", 0x3EE560, &recomp_gen::fn_sub_3EE560_003ee560, &recomp_gen::fn_sub_3EE560_003ee560__recomp},
    {"sub_3EE570", 0x3EE570, &recomp_gen::fn_sub_3EE570_003ee570, &recomp_gen::fn_sub_3EE570_003ee570__recomp},
    {"sub_3EE5F0", 0x3EE5F0, &recomp_gen::fn_sub_3EE5F0_003ee5f0, &recomp_gen::fn_sub_3EE5F0_003ee5f0__recomp},
    {"sub_3EEC60", 0x3EEC60, &recomp_gen::fn_sub_3EEC60_003eec60, &recomp_gen::fn_sub_3EEC60_003eec60__recomp},
    {"sub_3EED10", 0x3EED10, &recomp_gen::fn_sub_3EED10_003eed10, &recomp_gen::fn_sub_3EED10_003eed10__recomp},
    {"sub_3EED90", 0x3EED90, &recomp_gen::fn_sub_3EED90_003eed90, &recomp_gen::fn_sub_3EED90_003eed90__recomp},
    {"sub_3EEE10", 0x3EEE10, &recomp_gen::fn_sub_3EEE10_003eee10, &recomp_gen::fn_sub_3EEE10_003eee10__recomp},
    {"sub_3EFB40", 0x3EFB40, &recomp_gen::fn_sub_3EFB40_003efb40, &recomp_gen::fn_sub_3EFB40_003efb40__recomp},
    {"sub_3EFBC0", 0x3EFBC0, &recomp_gen::fn_sub_3EFBC0_003efbc0, &recomp_gen::fn_sub_3EFBC0_003efbc0__recomp},
    {"sub_3EFC60", 0x3EFC60, &recomp_gen::fn_sub_3EFC60_003efc60, &recomp_gen::fn_sub_3EFC60_003efc60__recomp},
    {"sub_3EFCA0", 0x3EFCA0, &recomp_gen::fn_sub_3EFCA0_003efca0, &recomp_gen::fn_sub_3EFCA0_003efca0__recomp},
    {"sub_3EFCE0", 0x3EFCE0, &recomp_gen::fn_sub_3EFCE0_003efce0, &recomp_gen::fn_sub_3EFCE0_003efce0__recomp},
    {"sub_3EFD70", 0x3EFD70, &recomp_gen::fn_sub_3EFD70_003efd70, &recomp_gen::fn_sub_3EFD70_003efd70__recomp},
    {"sub_3EFDE0", 0x3EFDE0, &recomp_gen::fn_sub_3EFDE0_003efde0, &recomp_gen::fn_sub_3EFDE0_003efde0__recomp},
    {"sub_3EFE60", 0x3EFE60, &recomp_gen::fn_sub_3EFE60_003efe60, &recomp_gen::fn_sub_3EFE60_003efe60__recomp},
    {"sub_3EFED0", 0x3EFED0, &recomp_gen::fn_sub_3EFED0_003efed0, &recomp_gen::fn_sub_3EFED0_003efed0__recomp},
    {"sub_3EFEF0", 0x3EFEF0, &recomp_gen::fn_sub_3EFEF0_003efef0, &recomp_gen::fn_sub_3EFEF0_003efef0__recomp},
    {"sub_3EFF00", 0x3EFF00, &recomp_gen::fn_sub_3EFF00_003eff00, &recomp_gen::fn_sub_3EFF00_003eff00__recomp},
    {"sub_3EFFF0", 0x3EFFF0, &recomp_gen::fn_sub_3EFFF0_003efff0, &recomp_gen::fn_sub_3EFFF0_003efff0__recomp},
    {"sub_3F0090", 0x3F0090, &recomp_gen::fn_sub_3F0090_003f0090, &recomp_gen::fn_sub_3F0090_003f0090__recomp},
    {"sub_3F00D0", 0x3F00D0, &recomp_gen::fn_sub_3F00D0_003f00d0, &recomp_gen::fn_sub_3F00D0_003f00d0__recomp},
    {"sub_3F01D0", 0x3F01D0, &recomp_gen::fn_sub_3F01D0_003f01d0, &recomp_gen::fn_sub_3F01D0_003f01d0__recomp},
    {"sub_3F0240", 0x3F0240, &recomp_gen::fn_sub_3F0240_003f0240, &recomp_gen::fn_sub_3F0240_003f0240__recomp},
    {"sub_3F0350", 0x3F0350, &recomp_gen::fn_sub_3F0350_003f0350, &recomp_gen::fn_sub_3F0350_003f0350__recomp},
    {"sub_3F03E0", 0x3F03E0, &recomp_gen::fn_sub_3F03E0_003f03e0, &recomp_gen::fn_sub_3F03E0_003f03e0__recomp},
    {"sub_3F06E0", 0x3F06E0, &recomp_gen::fn_sub_3F06E0_003f06e0, &recomp_gen::fn_sub_3F06E0_003f06e0__recomp},
    {"sub_3F0830", 0x3F0830, &recomp_gen::fn_sub_3F0830_003f0830, &recomp_gen::fn_sub_3F0830_003f0830__recomp},
    {"sub_3F0D60", 0x3F0D60, &recomp_gen::fn_sub_3F0D60_003f0d60, &recomp_gen::fn_sub_3F0D60_003f0d60__recomp},
    {"sub_3F10B0", 0x3F10B0, &recomp_gen::fn_sub_3F10B0_003f10b0, &recomp_gen::fn_sub_3F10B0_003f10b0__recomp},
    {"sub_3F1470", 0x3F1470, &recomp_gen::fn_sub_3F1470_003f1470, &recomp_gen::fn_sub_3F1470_003f1470__recomp},
    {"sub_3F15D0", 0x3F15D0, &recomp_gen::fn_sub_3F15D0_003f15d0, &recomp_gen::fn_sub_3F15D0_003f15d0__recomp},
    {"sub_3F1720", 0x3F1720, &recomp_gen::fn_sub_3F1720_003f1720, &recomp_gen::fn_sub_3F1720_003f1720__recomp},
    {"sub_3F1830", 0x3F1830, &recomp_gen::fn_sub_3F1830_003f1830, &recomp_gen::fn_sub_3F1830_003f1830__recomp},
    {"sub_3F1A10", 0x3F1A10, &recomp_gen::fn_sub_3F1A10_003f1a10, &recomp_gen::fn_sub_3F1A10_003f1a10__recomp},
    {"sub_3F2240", 0x3F2240, &recomp_gen::fn_sub_3F2240_003f2240, &recomp_gen::fn_sub_3F2240_003f2240__recomp},
    {"sub_3F2510", 0x3F2510, &recomp_gen::fn_sub_3F2510_003f2510, &recomp_gen::fn_sub_3F2510_003f2510__recomp},
    {"sub_3F2D60", 0x3F2D60, &recomp_gen::fn_sub_3F2D60_003f2d60, &recomp_gen::fn_sub_3F2D60_003f2d60__recomp},
    {"sub_3F2DC0", 0x3F2DC0, &recomp_gen::fn_sub_3F2DC0_003f2dc0, &recomp_gen::fn_sub_3F2DC0_003f2dc0__recomp},
    {"sub_3F3280", 0x3F3280, &recomp_gen::fn_sub_3F3280_003f3280, &recomp_gen::fn_sub_3F3280_003f3280__recomp},
    {"sub_3F3970", 0x3F3970, &recomp_gen::fn_sub_3F3970_003f3970, &recomp_gen::fn_sub_3F3970_003f3970__recomp},
    {"sub_3F3DC0", 0x3F3DC0, &recomp_gen::fn_sub_3F3DC0_003f3dc0, &recomp_gen::fn_sub_3F3DC0_003f3dc0__recomp},
    {"sub_3F3F00", 0x3F3F00, &recomp_gen::fn_sub_3F3F00_003f3f00, &recomp_gen::fn_sub_3F3F00_003f3f00__recomp},
    {"sub_3F7730", 0x3F7730, &recomp_gen::fn_sub_3F7730_003f7730, &recomp_gen::fn_sub_3F7730_003f7730__recomp},
    {"sub_3F98F0", 0x3F98F0, &recomp_gen::fn_sub_3F98F0_003f98f0, &recomp_gen::fn_sub_3F98F0_003f98f0__recomp},
    {"sub_3F99D0", 0x3F99D0, &recomp_gen::fn_sub_3F99D0_003f99d0, &recomp_gen::fn_sub_3F99D0_003f99d0__recomp},
    {"sub_3F9B20", 0x3F9B20, &recomp_gen::fn_sub_3F9B20_003f9b20, &recomp_gen::fn_sub_3F9B20_003f9b20__recomp},
    {"sub_3F9CB0", 0x3F9CB0, &recomp_gen::fn_sub_3F9CB0_003f9cb0, &recomp_gen::fn_sub_3F9CB0_003f9cb0__recomp},
    {"sub_3FA0D0", 0x3FA0D0, &recomp_gen::fn_sub_3FA0D0_003fa0d0, &recomp_gen::fn_sub_3FA0D0_003fa0d0__recomp},
    {"sub_3FA190", 0x3FA190, &recomp_gen::fn_sub_3FA190_003fa190, &recomp_gen::fn_sub_3FA190_003fa190__recomp},
    {"sub_3FA1B0", 0x3FA1B0, &recomp_gen::fn_sub_3FA1B0_003fa1b0, &recomp_gen::fn_sub_3FA1B0_003fa1b0__recomp},
    {"sub_3FA1E0", 0x3FA1E0, &recomp_gen::fn_sub_3FA1E0_003fa1e0, &recomp_gen::fn_sub_3FA1E0_003fa1e0__recomp},
    {"sub_3FB290", 0x3FB290, &recomp_gen::fn_sub_3FB290_003fb290, &recomp_gen::fn_sub_3FB290_003fb290__recomp},
    {"sub_3FBF20", 0x3FBF20, &recomp_gen::fn_sub_3FBF20_003fbf20, &recomp_gen::fn_sub_3FBF20_003fbf20__recomp},
    {"sub_3FC980", 0x3FC980, &recomp_gen::fn_sub_3FC980_003fc980, &recomp_gen::fn_sub_3FC980_003fc980__recomp},
    {"sub_3FFA20", 0x3FFA20, &recomp_gen::fn_sub_3FFA20_003ffa20, &recomp_gen::fn_sub_3FFA20_003ffa20__recomp},
    {"sub_3FFE00", 0x3FFE00, &recomp_gen::fn_sub_3FFE00_003ffe00, &recomp_gen::fn_sub_3FFE00_003ffe00__recomp},
    {"sub_400690", 0x400690, &recomp_gen::fn_sub_400690_00400690, &recomp_gen::fn_sub_400690_00400690__recomp},
    {"sub_400740", 0x400740, &recomp_gen::fn_sub_400740_00400740, &recomp_gen::fn_sub_400740_00400740__recomp},
    {"sub_400A90", 0x400A90, &recomp_gen::fn_sub_400A90_00400a90, &recomp_gen::fn_sub_400A90_00400a90__recomp},
    {"sub_400B90", 0x400B90, &recomp_gen::fn_sub_400B90_00400b90, &recomp_gen::fn_sub_400B90_00400b90__recomp},
    {"fclShopMisc_CreateShopDrawBGLowTasks", 0x400D60, &recomp_gen::fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60, &recomp_gen::fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60__recomp},
    {"sub_401170", 0x401170, &recomp_gen::fn_sub_401170_00401170, &recomp_gen::fn_sub_401170_00401170__recomp},
    {"fclShopMisc_UpdateShopDrawBGLowTask", 0x401210, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGLowTask_00401210, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGLowTask_00401210__recomp},
    {"fclShopMisc_UpdateShopDrawBGHighLowTask", 0x4012C0, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGHighLowTask_004012c0, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGHighLowTask_004012c0__recomp},
    {"fclShopMisc_UpdateShopDrawBGHighTopTask", 0x401370, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGHighTopTask_00401370, &recomp_gen::fn_fclShopMisc_UpdateShopDrawBGHighTopTask_00401370__recomp},
    {"sub_401420", 0x401420, &recomp_gen::fn_sub_401420_00401420, &recomp_gen::fn_sub_401420_00401420__recomp},
    {"sub_4014E0", 0x4014E0, &recomp_gen::fn_sub_4014E0_004014e0, &recomp_gen::fn_sub_4014E0_004014e0__recomp},
    {"sub_4015A0", 0x4015A0, &recomp_gen::fn_sub_4015A0_004015a0, &recomp_gen::fn_sub_4015A0_004015a0__recomp},
    {"sub_4015E0", 0x4015E0, &recomp_gen::fn_sub_4015E0_004015e0, &recomp_gen::fn_sub_4015E0_004015e0__recomp},
    {"sub_401600", 0x401600, &recomp_gen::fn_sub_401600_00401600, &recomp_gen::fn_sub_401600_00401600__recomp},
    {"sub_40D410", 0x40D410, &recomp_gen::fn_sub_40D410_0040d410, &recomp_gen::fn_sub_40D410_0040d410__recomp},
    {"sub_40D490", 0x40D490, &recomp_gen::fn_sub_40D490_0040d490, &recomp_gen::fn_sub_40D490_0040d490__recomp},
    {"sub_40D5E0", 0x40D5E0, &recomp_gen::fn_sub_40D5E0_0040d5e0, &recomp_gen::fn_sub_40D5E0_0040d5e0__recomp},
    {"sub_40D610", 0x40D610, &recomp_gen::fn_sub_40D610_0040d610, &recomp_gen::fn_sub_40D610_0040d610__recomp},
    {"sub_40E300", 0x40E300, &recomp_gen::fn_sub_40E300_0040e300, &recomp_gen::fn_sub_40E300_0040e300__recomp},
    {"sub_40E390", 0x40E390, &recomp_gen::fn_sub_40E390_0040e390, &recomp_gen::fn_sub_40E390_0040e390__recomp},
    {"sub_40E3C0", 0x40E3C0, &recomp_gen::fn_sub_40E3C0_0040e3c0, &recomp_gen::fn_sub_40E3C0_0040e3c0__recomp},
    {"sub_40E3F0", 0x40E3F0, &recomp_gen::fn_sub_40E3F0_0040e3f0, &recomp_gen::fn_sub_40E3F0_0040e3f0__recomp},
    {"sub_40E450", 0x40E450, &recomp_gen::fn_sub_40E450_0040e450, &recomp_gen::fn_sub_40E450_0040e450__recomp},
    {"sub_40E4F0", 0x40E4F0, &recomp_gen::fn_sub_40E4F0_0040e4f0, &recomp_gen::fn_sub_40E4F0_0040e4f0__recomp},
    {"sub_40E580", 0x40E580, &recomp_gen::fn_sub_40E580_0040e580, &recomp_gen::fn_sub_40E580_0040e580__recomp},
    {"sub_40E610", 0x40E610, &recomp_gen::fn_sub_40E610_0040e610, &recomp_gen::fn_sub_40E610_0040e610__recomp},
    {"sub_40E710", 0x40E710, &recomp_gen::fn_sub_40E710_0040e710, &recomp_gen::fn_sub_40E710_0040e710__recomp},
    {"sub_40EB50", 0x40EB50, &recomp_gen::fn_sub_40EB50_0040eb50, &recomp_gen::fn_sub_40EB50_0040eb50__recomp},
    {"sub_40EC20", 0x40EC20, &recomp_gen::fn_sub_40EC20_0040ec20, &recomp_gen::fn_sub_40EC20_0040ec20__recomp},
    {"sub_40EC50", 0x40EC50, &recomp_gen::fn_sub_40EC50_0040ec50, &recomp_gen::fn_sub_40EC50_0040ec50__recomp},
    {"sub_40EEF0", 0x40EEF0, &recomp_gen::fn_sub_40EEF0_0040eef0, &recomp_gen::fn_sub_40EEF0_0040eef0__recomp},
    {"sub_410D30", 0x410D30, &recomp_gen::fn_sub_410D30_00410d30, &recomp_gen::fn_sub_410D30_00410d30__recomp},
    {"sub_410E70", 0x410E70, &recomp_gen::fn_sub_410E70_00410e70, &recomp_gen::fn_sub_410E70_00410e70__recomp},
    {"sub_4110F0", 0x4110F0, &recomp_gen::fn_sub_4110F0_004110f0, &recomp_gen::fn_sub_4110F0_004110f0__recomp},
    {"sub_411190", 0x411190, &recomp_gen::fn_sub_411190_00411190, &recomp_gen::fn_sub_411190_00411190__recomp},
    {"sub_411340", 0x411340, &recomp_gen::fn_sub_411340_00411340, &recomp_gen::fn_sub_411340_00411340__recomp},
    {"sub_412580", 0x412580, &recomp_gen::fn_sub_412580_00412580, &recomp_gen::fn_sub_412580_00412580__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that give each body a fresh, identical stand-in world
// (stand_ins.h: the heap behind H_Malloc and the RW slots, printf / sprintf, the H_Cdvd layer, plus the shop world
// below), whose call logs must match.
constexpr u32 kYen = 0x83A6DCu;          // the yen counter (sub_16DD50 reads it, sub_16E930 writes it)
constexpr u32 kOut = 0x01F40000u;        // free in every shop snapshot and in the ELF image
constexpr u32 kSprite = 0x01F47000u;     // the stand-in sprite handle (64 bytes)
constexpr u32 kFacility = 0x7CDA00u;     // the COMM handlers' facility number

// The shop world: the yen accessors as the real code has them (on the guest word), sprCreateHandle returning a fixed
// scratch block (the drawers' stores land in compared memory), and recorders for every other callee of the slice that
// the test build does not emit (they log the call and return 0, so the pairs run on past them).
std::vector<std::pair<u32, u32>> g_reserved;

void shop_world(StandInWorld& w) {
    install_standard(w);
    w.si.install(0x16DD50u, "yen get", [](EEContext& ctx, StandIns&, StandInCall& c) { c.v0 = ctx.memory->read<u32>(kYen); });
    w.si.install(0x16E930u, "yen set", [](EEContext& ctx, StandIns&, StandInCall& c) {
        ctx.memory->write<u32>(kYen, static_cast<u32>(c.args[0]));
        c.v0 = 0;
    });
    w.si.install(0x1158B0u, "sprCreateHandle", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = kSprite; });
    // every callee of the slice's bodies that the test build does not emit (a recorder returns 0)
    const std::pair<u32, const char*> rec[] = {
        {0x1052B0u, "sub_1052B0"}, {0x1099D0u, "sub_1099D0"}, {0x111C50u, "sub_111C50"}, {0x111CA0u, "sub_111CA0"},
        {0x111CB0u, "sub_111CB0"}, {0x111D50u, "sub_111D50"}, {0x111DD0u, "sub_111DD0"}, {0x111EC0u, "sub_111EC0"},
        {0x111EE0u, "sub_111EE0"}, {0x111F00u, "sub_111F00"}, {0x111F10u, "sub_111F10"}, {0x111F20u, "sub_111F20"},
        {0x112420u, "sprCreateHandleFromData"}, {0x1124B0u, "sub_1124B0"}, {0x1127D0u, "sub_1127D0"},
        {0x115980u, "sub_115980"}, {0x16E2B0u, "sub_16E2B0"}, {0x16F720u, "sub_16F720"}, {0x170C00u, "sub_170C00"},
        {0x17C190u, "sub_17C190"}, {0x17C220u, "sub_17C220"}, {0x17C670u, "sub_17C670"}, {0x17D040u, "sub_17D040"},
        {0x17D1A0u, "sub_17D1A0"}, {0x17D250u, "sub_17D250"}, {0x17D610u, "sub_17D610"}, {0x1830C0u, "sub_1830C0"},
        {0x1A1150u, "sub_1A1150"}, {0x1A1190u, "sub_1A1190"}, {0x1A4580u, "sub_1A4580"}, {0x3A2090u, "sub_3A2090"},
        {0x3B5760u, "MT_Scene_Load"}, {0x3B5A10u, "sub_3B5A10"}, {0x3C7B90u, "sub_3C7B90"},
        {0x3C7BC0u, "sub_3C7BC0"}, {0x3C7C20u, "sub_3C7C20"}, {0x3C7D80u, "sub_3C7D80"}, {0x3C82E0u, "sub_3C82E0"},
        {0x3C83B0u, "sub_3C83B0"}, {0x3C9790u, "sub_3C9790"}, {0x3C9850u, "fclMisc_CreatePsStatusTasks"},
        {0x3C9AB0u, "sub_3C9AB0"}, {0x3E0A10u, "sub_3E0A10"}, {0x3E0C20u, "sub_3E0C20"}, {0x3E6130u, "sub_3E6130"},
        {0x3E9200u, "sub_3E9200"}, {0x3EAD10u, "sub_3EAD10"}, {0x3EADD0u, "sub_3EADD0"}, {0x3EB9B0u, "sub_3EB9B0"},
        {0x3EBA10u, "sub_3EBA10"}, {0x3EBAD0u, "sub_3EBAD0"}, {0x3EC030u, "sub_3EC030"}, {0x3EC090u, "sub_3EC090"},
        {0x3EC150u, "sub_3EC150"}, {0x3EC6F0u, "sub_3EC6F0"}, {0x3EC7B0u, "sub_3EC7B0"}, {0x3ECD30u, "sub_3ECD30"},
        {0x3ECDF0u, "sub_3ECDF0"}, {0x3ED380u, "sub_3ED380"}, {0x3ED420u, "sub_3ED420"}, {0x3EDDD0u, "sub_3EDDD0"},
        {0x3EDE80u, "sub_3EDE80"}, {0x3EED50u, "sub_3EED50"}, {0x3EF970u, "sub_3EF970"}, {0x3F00B0u, "sub_3F00B0"},
        {0x3F04F0u, "sub_3F04F0"}, {0x3F0AC0u, "sub_3F0AC0"}, {0x3F0EC0u, "sub_3F0EC0"}, {0x3F12A0u, "sub_3F12A0"},
        {0x3F1520u, "sub_3F1520"}, {0x3F1690u, "sub_3F1690"}, {0x3F1DC0u, "sub_3F1DC0"}, {0x3F33D0u, "sub_3F33D0"},
        {0x3F39A0u, "sub_3F39A0"}, {0x3F9E30u, "sub_3F9E30"}, {0x3FBC00u, "sub_3FBC00"}, {0x3FC060u, "sub_3FC060"},
        {0x3FC540u, "sub_3FC540"}, {0x3FD820u, "sub_3FD820"}, {0x3FD8A0u, "sub_3FD8A0"}, {0x3FDF80u, "sub_3FDF80"},
        {0x3FE2B0u, "sub_3FE2B0"}, {0x3FF630u, "sub_3FF630"}, {0x3FFBB0u, "sub_3FFBB0"}, {0x3FFE60u, "sub_3FFE60"},
        {0x4003F0u, "sub_4003F0"}, {0x400E90u, "sub_400E90"}, {0x401890u, "sub_401890"}, {0x401950u, "sub_401950"},
        {0x402480u, "sub_402480"}, {0x4030B0u, "sub_4030B0"}, {0x4030F0u, "sub_4030F0"}, {0x403520u, "sub_403520"},
        {0x403610u, "sub_403610"}, {0x4038A0u, "sub_4038A0"}, {0x403970u, "sub_403970"}, {0x403E40u, "sub_403E40"},
        {0x403F20u, "sub_403F20"}, {0x404120u, "sub_404120"}, {0x4044C0u, "sub_4044C0"}, {0x40C170u, "sub_40C170"},
        {0x40C310u, "sub_40C310"}, {0x40C490u, "sub_40C490"}, {0x40C6F0u, "sub_40C6F0"}, {0x40CAD0u, "sub_40CAD0"},
        {0x40D640u, "sub_40D640"},
    };
    for (const auto& [va, name] : rec) w.si.install_recorder(va, name, 0);
    // deeper callees the pairs reach through emitted code: the message system, the step callbacks of the sequence
    // (MONEY / BUY / SELL / the ROOT menu draws) and a libc helper
    const std::pair<u32, const char*> deep[] = {
        {0x3A2A30u, "msg (sub_3A2A30)"}, {0x3A2D80u, "msg (sub_3A2D80)"}, {0x3A4360u, "msg (sub_3A4360)"},
        {0x51E028u, "libc (sub_51E028)"}, {0x3EE920u, "MONEY draw (sub_3EE920)"}, {0x3EE670u, "MONEY update (sub_3EE670)"},
        {0x3F45E0u, "row draw (sub_3F45E0)"}, {0x3EA820u, "SELL update (sub_3EA820)"}, {0x3E9AF0u, "BUY update (sub_3E9AF0)"},
        {0x3EEE80u, "SUBTITLE update (sub_3EEE80)"}, {0x3EF2B0u, "SUBTITLE draw (sub_3EF2B0)"},
        {0x3A30C0u, "msg (sub_3A30C0)"}, {0x3A3420u, "msg (sub_3A3420)"}, {0x3C8230u, "msg (sub_3C8230)"},
        {0x51DF58u, "libc (sub_51DF58)"}, {0x3F8E10u, "TALK draw (sub_3F8E10)"},
    };
    for (const auto& [va, name] : deep) w.si.install_recorder(va, name, 0);
    // heap blocks made by an earlier pair that later pairs build on (each pair starts a fresh allocator)
    for (const auto& [va, size] : g_reserved) w.heap.reserve(va, size);
}

struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
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
    shop_world(*g_t.world[K]);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = true;
};

std::map<std::string, int> g_stops;  // early stops of the pairs by function and reason (reported by the last case)

hgp::Run sp_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    ++g_pairs;
    if (r.stopped) ++g_stops[std::string(name) + ": " + r.what.substr(0, 90)];
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(v0_of(r))); }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
s16 r16s(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u16 r16(const Machine& m, u32 va) { return static_cast<u16>(r16s(m, va)); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

// The shop snapshots of the gate's shop route (the pharmacy, type 2): 3200 / 3700 / 4100 have the shop open (4100 in
// state 0x35, the shopkeeper's chat). Empty when absent.
std::vector<u8> shop_snapshot(const char* dir) {
    std::vector<u8> s = read_snapshot(dir);
    return s.size() == EEMemory::kMainRamSize ? s : std::vector<u8>{};
}
void restore(Machine& m, const std::vector<u8>& snap) { std::memcpy(m.mem.main_ram(), snap.data(), snap.size()); }

struct ShopView {
    u32 seq = 0, work = 0, set = 0;
};
ShopView view_of(const Machine& m) {
    ShopView v;
    v.seq = r32(m, shop::kShopSeqGlobal);
    if (v.seq) v.work = r32(m, r32(m, v.seq + shop::kListObjPayload) + 12);  // nmObjPayloadWord12
    if (v.work) v.set = r32(m, v.work + shop::kShopElements);
    return v;
}
u32 step_payload(const Machine& m, u32 node) { return node ? r32(m, r32(m, node + shop::kNodePayload) + 40) : 0; }  // sub_3C5470

// --- host models of documented rules ---------------------------------------------------------------------------------
// sub_3F1A10: the category code of an item flag word.
u32 category_of(u32 a) {
    u32 r = (a & 0x7FFFFu) != 0 ? 0x1000u : 0x4000u;
    if (a & 0xFF00u) {
        a >>= 8;
        r |= 0x2000u;
    }
    if (a & 1u) return r;
    static const std::pair<u32, u32> bits[] = {{2, 1}, {4, 2}, {8, 3}, {0x10, 4}, {0x20, 5}, {0x40, 6}, {0x80, 7},
                                               {0x10000, 0x109}, {0x20000, 0x20A}, {0x40000, 0x30B}, {0x80000, 0x40D},
                                               {0x100000, 0x40E}};
    for (const auto& [bit, code] : bits)
        if (a & bit) return r | code;
    return 0;
}
// sub_3F98F0: sellable unless in one of the 16 ranges {first, last} of 0x6ACCA0 (last 0: one id).
bool sellable(const Machine& m, u16 item) {
    for (u32 k = 0; k < 16; ++k) {
        const u16 lo = r16(m, 0x6ACCA0u + 4 * k), hi = r16(m, 0x6ACCA2u + 4 * k);
        if (hi ? (item >= lo && item <= hi) : item == lo) return false;
    }
    return true;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(shops): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int stops_total = 0, pairs_total = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
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
// The shop root state machine on the real pharmacy (every state), with the documented transitions
// =====================================================================================================================
TEST_CASE("game(shops): the shop root, its steps and tasks on the shop route's snapshots") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    int snaps = 0;
    for (const char* dir : {"shop_ref_4100", "shop_3700", "shop_3200"}) {
        const std::vector<u8> snap = shop_snapshot(dir);
        if (snap.empty()) continue;
        ++snaps;
        restore(m, snap);
        const ShopView v = view_of(m);
        REQUIRE(v.seq != 0);
        REQUIRE(v.work != 0);
        CHECK(r32(m, v.work + shop::kShopType) == 2u);  // the pharmacy
        const u32 seed0 = 0x5000u + 0x100u * static_cast<u32>(snaps);
        // the accessors
        CHECK(v0s(sp_pair(m, "sub_3E6DC0", {0, 0, 0, 0}, seed0 + 1, "sub_3E6DC0 type")) == 2);
        CHECK(v0_of(sp_pair(m, "sub_3E0BB0", {0, 0, 0, 0}, seed0 + 2, "sub_3E0BB0 exists")) == 1u);
        CHECK(v0_of(sp_pair(m, "sub_3E0920", {0, 0, 0, 0}, seed0 + 3, "sub_3E0920 open")) == 1u);
        const hgp::Run hl = sp_pair(m, "sub_3E6D70", {0, 0, 0, 0}, seed0 + 4, "sub_3E6D70 lineup");
        CHECK(v0_of(hl) == ((r32(m, v.work + shop::kShopFlags) & 4u) ? 1u : 0u));
        // every root state on the real work record (RAM restored before each)
        int stopped = 0;
        for (u32 state = 0; state <= 82; ++state) {
            restore(m, snap);
            w32(m, v.work + shop::kShopState, state);
            const hgp::Run r = sp_pair(m, "sub_3E6E80", {sx(v.seq), 0, 0, 0}, seed0 + 16 + state, "sub_3E6E80 state");
            if (r.stopped) {
                ++stopped;
                continue;
            }
            const u32 next = r32(m, v.work + shop::kShopState);
            // documented transitions (the case comments of sub_3E6E80)
            if (state == 1) CHECK(next == 4u);
            if (state == 4) CHECK(next == 5u);
            if (state == 54) CHECK(next == 2u);  // 54 -> 55 -> 2 in the same frame
            if (state == 55) CHECK(next == 2u);
            if (state == 0 || state > 80) CHECK(next == state);  // outside the table: nothing happens
            if (state != 2 && state != 3) CHECK(v0_of(r) == 0u);  // 2 / 3 return 1 once the fade is over
        }
        MESSAGE(std::string(dir) << ": root states 0..82, " << stopped << " stopped early");
        restore(m, snap);
        // the task callbacks and the per-frame helpers on the live sequence
        sp_pair(m, "fclShop_UpdateShopDrawTask", {0, 0, 0, 0}, seed0 + 101, "fclShopDraw");
        sp_pair(m, "fclShop_UpdateShopDraw2Task", {0, 0, 0, 0}, seed0 + 102, "fclShopDraw2");
        sp_pair(m, "sub_3E6D40", {0, 0, 0, 0}, seed0 + 103, "sub_3E6D40 step draws");
        restore(m, snap);
        sp_pair(m, "sub_3E0830", {0, 0, 0, 0}, seed0 + 104, "fclShop task");
        restore(m, snap);
        sp_pair(m, "sub_3E0BC0", {0, 0, 0, 0}, seed0 + 105, "sub_3E0BC0 poll end");
        // the step pollers / showers on the live steps
        for (const char* n : {"sub_3E8FF0", "sub_3E98B0", "sub_3EA6B0", "sub_3EE3D0", "sub_3E8740"}) {
            restore(m, snap);
            sp_pair(m, n, {sx(v.work), 0, 0, 0}, seed0 + 110, n);
        }
        for (const char* n : {"sub_3E9790", "sub_3EA560", "sub_3EACB0", "sub_3EEC60", "sub_3EED10", "sub_3EFE60", "sub_3EFD70"})
            for (u32 a = 0; a < 4; ++a) {
                restore(m, snap);
                sp_pair(m, n, {a, 0, 0, 0}, seed0 + 120 + a, n);
            }
        // the BG step: the manager, its mode rule and its three layer tasks
        const u32 mgr = r32(m, step_payload(m, r32(m, v.work + shop::kShopStepBg)) + 8);
        if (mgr != 0) {
            restore(m, snap);
            for (u32 mode = 0; mode < 6; ++mode) {
                const u32 before_mode = r32(m, mgr + shop::kBgMode), before = r32(m, mgr + shop::kBgFlags);
                sp_pair(m, "sub_3EFDE0", {0, mode, 0, 0}, seed0 + 130 + mode, "sub_3EFDE0 mode");
                const u32 after = r32(m, mgr + shop::kBgFlags);
                if (before_mode != mode) {
                    CHECK(r32(m, mgr + shop::kBgMode) == mode);
                    CHECK((after & 1u) == 1u);
                    CHECK((after & 4u) == ((before & 1u) ? 4u : (before & 4u)));
                } else {
                    CHECK(after == before);
                }
                const hgp::Run b = sp_pair(m, "sub_4015E0", {sx(mgr), 0, 0, 0}, seed0 + 140 + mode, "sub_4015E0");
                CHECK(v0_of(b) == ((after & 2u) ? 1u : 0u));
            }
            const u32 task = r32(m, mgr + shop::kBgTask);
            restore(m, snap);
            sp_pair(m, "fclShopMisc_UpdateShopDrawBGLowTask", {sx(task), 0, 0, 0}, seed0 + 150, "BG low");
            sp_pair(m, "fclShopMisc_UpdateShopDrawBGHighLowTask", {sx(task), 0, 0, 0}, seed0 + 151, "BG high-low");
            sp_pair(m, "fclShopMisc_UpdateShopDrawBGHighTopTask", {sx(task), 0, 0, 0}, seed0 + 152, "BG high-top");
            sp_pair(m, "sub_401170", {sx(mgr), 0, 0, 0}, seed0 + 153, "BG layer 3");
            sp_pair(m, "sub_4014E0", {sx(mgr), 0, 0, 0}, seed0 + 154, "BG load poll");
            // the background event handlers with every event code
            for (u32 ev = 0; ev < 24; ++ev) {
                restore(m, snap);
                w16(m, kOut + 6, static_cast<u16>(ev));
                for (const char* n : {"sub_4110F0", "sub_411190", "sub_411340"}) {
                    const hgp::Run r = sp_pair(m, n, {0, 0, sx(kOut), 0}, seed0 + 160 + ev, n);
                    if (!r.stopped) CHECK(v0_of(r) == 1u);
                }
            }
        }
        // the openers on the real work record (each from the snapshot)
        for (const char* n : {"sub_3E86C0", "sub_3E8E20", "sub_3E97F0", "sub_3EA600", "sub_3EE310", "sub_3EE570",
                              "sub_3EED90", "sub_3EFB40", "sub_3EFCE0"}) {
            restore(m, snap);
            sp_pair(m, n, {sx(v.work), 0, 0, 0}, seed0 + 200, n);
        }
    }
    if (snaps == 0) MESSAGE("SKIP: no shop snapshot under extracted/_ours");
}

// =====================================================================================================================
// The facility element library on the real element set of the shop (and the documented find / done rules)
// =====================================================================================================================
TEST_CASE("game(shops): the facility element set on the shop snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = shop_snapshot("shop_ref_4100");
    if (snap.empty()) {
        MESSAGE("SKIP: no shop snapshot under extracted/_ours");
        return;
    }
    restore(m, snap);
    const ShopView v = view_of(m);
    REQUIRE(v.set != 0);
    const u32 list = r32(m, v.set);
    std::vector<u32> nodes;
    for (u32 n = r32(m, list + shop::kListHead); n != 0 && nodes.size() < 64; n = r32(m, n + shop::kNodeNext)) nodes.push_back(n);
    REQUIRE(!nodes.empty());
    // find by id (host walk) and all-done
    for (u32 id = 0; id < 24; ++id) {
        u32 want = 0;
        for (u32 n : nodes)
            if (r32(m, r32(m, n + shop::kNodePayload) + shop::kElemId) == id) {
                want = r32(m, n + shop::kNodePayload);
                break;
            }
        CHECK(v0_of(sp_pair(m, "sub_3DFF80", {sx(v.set), id, 0, 0}, 0x6000 + id, "sub_3DFF80 find")) == want);
    }
    bool all = true;
    for (u32 n : nodes) all = all && (r32(m, r32(m, n + shop::kNodePayload) + shop::kElemFlags) & 4u) != 0;
    CHECK(v0_of(sp_pair(m, "sub_3DFF30", {sx(v.set), 0, 0, 0}, 0x6100, "sub_3DFF30 all done")) == (all ? 1u : 0u));
    // the animator on every node in every state, with delays / durations around their edges
    u32 seed = 0x6200;
    for (u32 n : nodes) {
        const u32 e = r32(m, n + shop::kNodePayload);
        for (u32 state = 0; state <= 7; ++state)
            for (u32 k = 0; k < 3; ++k) {
                restore(m, snap);
                w32(m, e + shop::kElemState, state);
                w16(m, e + shop::kElemDelay, static_cast<u16>(k));            // 0, 1, 2 frames of delay
                w16(m, e + shop::kElemFrame, static_cast<u16>(k * 4));         // frame 0 / 4 / 8
                w16(m, e + shop::kElemFrames, static_cast<u16>(8 + k));        // duration 8 / 9 / 10
                if (k == 2) w32(m, e + shop::kElemFlags, r32(m, e + shop::kElemFlags) | 2u);  // the arc path
                const hgp::Run r = sp_pair(m, "sub_3DF4A0", {sx(v.set), sx(n), 0, 0}, ++seed, "sub_3DF4A0 animate");
                if (r.stopped) continue;
                CHECK(v0_of(r) == 0u);
                const u32 now = r32(m, e + shop::kElemState);
                if (state == 1) CHECK(now == (k <= 1 ? ((r32(m, e + shop::kElemFlags) & 2u) ? 3u : 2u) : 1u));
                if (state == 4 && k == 2) {  // frame 8 -> 9 of 10: still running
                    CHECK(now == 4u);
                }
                if (state == 4 && k == 1) {  // frame 4 -> 5 of 9
                    CHECK(now == 4u);
                }
                if ((state == 4 || state == 5) && k == 0) {  // frame 0 -> 1 of 8
                    CHECK(now == state);
                }
                if (state == 0 || state >= 6) CHECK(now == state);
            }
    }
    // the end of a move snaps to the end values, state 6, flag 4
    {
        restore(m, snap);
        const u32 e = r32(m, nodes[0] + shop::kNodePayload);
        w32(m, e + shop::kElemState, 4);
        w32(m, e + shop::kElemFlags, 0);
        w16(m, e + shop::kElemFrame, 9);
        w16(m, e + shop::kElemFrames, 10);
        w16(m, e + shop::kElemX1, 123);
        w16(m, e + shop::kElemY1, 45);
        w16(m, e + shop::kElemAlpha1, 200);
        const hgp::Run r = sp_pair(m, "sub_3DF4A0", {sx(v.set), sx(nodes[0]), 0, 0}, 0x6300, "sub_3DF4A0 end");
        if (!r.stopped) {
            CHECK(r32(m, e + shop::kElemState) == 6u);
            CHECK((r32(m, e + shop::kElemFlags) & 4u) == 4u);
            CHECK(r16s(m, e + shop::kElemX) == 123);
            CHECK(r16s(m, e + shop::kElemY) == 45);
            CHECK(r16s(m, e + shop::kElemAlpha) == 200);
            CHECK(r16(m, e + shop::kElemFrame) == 0u);
        }
    }
    // start (find or append), one frame of the set, for-each with the shop's drawer, destroy
    for (u32 id = 0; id < 20; id += 3) {
        restore(m, snap);
        const hgp::Run r = sp_pair(m, "sub_3DFFC0", {sx(v.set), id, id & 1u, 0}, 0x6400 + id, "sub_3DFFC0 start");
        if (!r.stopped) {
            const u32 e = static_cast<u32>(v0_of(r));
            bool had = false;  // an existing element is found by its id; a new node's id is left to the descriptor
            for (u32 n : nodes) had = had || r32(m, r32(m, n + shop::kNodePayload) + shop::kElemId) == id;
            if (had) CHECK(r32(m, e + shop::kElemId) == id);
            CHECK(r32(m, e + shop::kElemState) == 1u);
            CHECK((r32(m, e + shop::kElemFlags) & 4u) == 0u);
        }
        restore(m, snap);
        for (u32 k = 0; k < 2; ++k) sp_pair(m, "sub_3E04E0", {sx(v.set), id & 3u, k, 0x40}, 0x6500 + id + k, "sub_3E04E0 template");
    }
    restore(m, snap);
    sp_pair(m, "sub_3E0650", {sx(v.set), 0, 0, 0}, 0x6600, "sub_3E0650 frame");
    sp_pair(m, "sub_3E0680", {sx(v.set), 0x3E6400u, 0, 0}, 0x6601, "sub_3E0680 for-each draw");
    for (u32 n : nodes)
        for (u32 pass = 0; pass < 2; ++pass) {  // the drawer in both passes (flag 0x20 of the work)
            restore(m, snap);
            if (pass) w32(m, v.work + shop::kShopFlags, r32(m, v.work + shop::kShopFlags) | 0x20u);
            for (u32 id = 0; id < 19; ++id) {
                w32(m, r32(m, n + shop::kNodePayload) + shop::kElemId, id);
                sp_pair(m, "sub_3E6400", {sx(v.set), sx(r32(m, n + shop::kNodePayload)), 0, 0}, 0x6700 + id + 32 * pass, "sub_3E6400 draw");
            }
        }
    restore(m, snap);
    sp_pair(m, "sub_3DFAC0", {sx(v.set), 0, 0, 0}, 0x6800, "sub_3DFAC0");
    sp_pair(m, "sub_3DFF00", {sx(v.set), 0, 0, 0}, 0x6801, "sub_3DFF00 destroy");
    sp_pair(m, "sub_3DFF00", {0, 0, 0, 0}, 0x6802, "sub_3DFF00 null");
    restore(m, snap);
    const hgp::Run c = sp_pair(m, "sub_3DFEB0", {sx(v.work), 0, 0, 0}, 0x6803, "sub_3DFEB0 create");
    if (!c.stopped && v0_of(c) != 0) CHECK(r32(m, static_cast<u32>(v0_of(c)) + 4) == v.work);
}

// =====================================================================================================================
// fclShopMisc.c's data: the shop records, lineups, messages and social links of every shop type (real tables)
// =====================================================================================================================
TEST_CASE("game(shops): shop records, lineups, greetings and links of every type") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = shop_snapshot("shop_ref_4100");
    const bool have = !snap.empty();
    if (have) restore(m, snap);  // the story flags and social links of the route; the ELF's .bss otherwise
    u32 seed = 0x7000;
    for (u32 type = 0; type <= 8; ++type) {
        const hgp::Run rec = sp_pair(m, "sub_3EFFF0", {type, 0, 0, 0}, ++seed, "sub_3EFFF0 record");
        const u32 base = static_cast<u32>(v0_of(rec));
        CHECK((base == 0x6AC9D0u + 36 * type || base == 0x6AC9D0u + 36 * (type + 9)));
        CHECK(v0s(sp_pair(m, "sub_3F0090", {type, 0, 0, 0}, ++seed, "sub_3F0090 intro")) == r16s(m, 0x6ACC70u + 4 * type));
        const hgp::Run lu = sp_pair(m, "sub_3F0240", {type, 0, 0, 0}, ++seed, "sub_3F0240 lineup");
        if (type > 2) CHECK(v0_of(lu) == 0u);
        const hgp::Run rk = sp_pair(m, "sub_3F03E0", {type, 0, 0, 0}, ++seed, "sub_3F03E0 rank");
        if (type != 0 && type != 4 && type != 8) CHECK(v0_of(rk) == 0u);
        if (!rk.stopped) CHECK(v0s(rk) <= 10);
        sp_pair(m, "sub_3F1470", {type, 0, 0, 0}, ++seed, "sub_3F1470");
        sp_pair(m, "sub_3F0830", {type, 0, 0, 0}, ++seed, "sub_3F0830 greeting");
        for (u32 item = 0; item < 0x400; item += 0x55) {
            sp_pair(m, "sub_3F10B0", {type, item, 0, 0}, ++seed, "sub_3F10B0");
            sp_pair(m, "sub_3F0D60", {type, item, 0, 0}, ++seed, "sub_3F0D60");
        }
        const hgp::Run sm = sp_pair(m, "sub_3EFF00", {type, sx(kOut), 0, 0}, ++seed, "sub_3EFF00 summary");
        if (!sm.stopped) CHECK(r16(m, kOut + 2) == static_cast<u16>(v0_of(sp_pair(m, "sub_3F2510", {0, 0, 0, 0}, ++seed, "sub_3F2510"))));
        // the lineup walkers on the record's lists, from several start indices
        for (u32 list = 0; list < 3; ++list)
            for (u32 start = 0; start < 3; ++start) {
                w32(m, kOut + 0x40, start);
                sp_pair(m, "sub_3F00D0", {sx(base + 8 * list), list & 1u, sx(kOut + 0x40), 0}, ++seed, "sub_3F00D0");
                sp_pair(m, "sub_3F01D0", {sx(base), list, sx(kOut + 0x40), 0}, ++seed, "sub_3F01D0");
                w32(m, kOut + 0x44, start);
                const hgp::Run it = sp_pair(m, "sub_3F0350", {sx(base), sx(kOut + 0x44), 0, 0}, ++seed, "sub_3F0350");
                if (!it.stopped) {
                    const s32 count = static_cast<s32>(r32(m, base + 24));
                    if (static_cast<s32>(start) < count) {
                        CHECK(v0_of(it) == static_cast<u64>(r32(m, base + 28) + 12 * start));
                        CHECK(r32(m, kOut + 0x44) == start + 1);
                    } else {
                        CHECK(v0_of(it) == 0u);
                    }
                }
            }
        // the message selector on the greeting lists
        const u32 msgs = r32(m, base + 32);
        if (msgs != 0)
            for (u32 mode = 0; mode < 2; ++mode) sp_pair(m, "sub_3F06E0", {sx(msgs + 20), mode, 0, 0}, ++seed, "sub_3F06E0");
    }
    const char* note = have ? "flags / links from shop_ref_4100" : "note: no shop snapshot; flags / links of the ELF image";
    MESSAGE(std::string(note));
}

// =====================================================================================================================
// Money, items, rows and lists (documented rules)
// =====================================================================================================================
TEST_CASE("game(shops): money, item rows, sellable items, categories and comparators (documented rules)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = shop_snapshot("shop_ref_4100");
    if (!snap.empty()) restore(m, snap);
    u32 seed = 0x8000;
    // sub_3F15D0: yen += price * count, clamped to [0, 9,999,999]; returns the change applied
    const s32 yens[] = {0, 1, 500, 12345, 9999000, 9999999};
    const s32 prices[] = {-100000, -3000, -1, 0, 1, 250, 4000, 9999999};
    const s32 counts[] = {0, 1, 3, 99};
    for (s32 yen : yens)
        for (s32 price : prices)
            for (s32 count : counts) {
                w32(m, kYen, static_cast<u32>(yen));
                const hgp::Run r = sp_pair(m, "sub_3F15D0", {sx(static_cast<u32>(price)), sx(static_cast<u32>(count)), 0, 0}, ++seed, "sub_3F15D0 money");
                if (r.stopped) continue;
                const s32 delta = static_cast<s32>(static_cast<u32>(price) * static_cast<u32>(count));  // mult: the low 32 bits
                const s64 sum = static_cast<s64>(yen) + delta;
                const s64 want = sum < 0 ? 0 : (sum > shop::kYenMax ? shop::kYenMax : sum);
                CHECK(static_cast<s32>(r32(m, kYen)) == want);
                CHECK(v0s(r) == static_cast<s32>(want - yen));
            }
    // sub_3F1A10: the category code of a flag word (every single bit, pairs and random words)
    std::mt19937 rng{0x3F1A10u};
    std::vector<u32> words = {0};
    for (u32 b = 0; b < 32; ++b) words.push_back(1u << b);
    for (u32 b = 0; b < 24; ++b) words.push_back((1u << b) | 0x100u);
    for (int i = 0; i < 64; ++i) words.push_back(rng() & (rng() % 2 ? 0x1FFFFFu : 0xFFFFFFFFu));
    for (u32 w : words) CHECK(static_cast<u32>(v0_of(sp_pair(m, "sub_3F1A10", {w, 0, 0, 0}, ++seed, "sub_3F1A10"))) == category_of(w));
    // sub_3F98F0: sellable unless in the 16 ranges of 0x6ACCA0
    for (u32 item = 0; item < 0x800; item += 7) {
        const hgp::Run r = sp_pair(m, "sub_3F98F0", {item, 0, 0, 0}, ++seed, "sub_3F98F0 sellable");
        if (!r.stopped) CHECK(v0_of(r) == (sellable(m, static_cast<u16>(item)) ? 1u : 0u));
    }
    // inventory rows of real items (sub_3F2240), buy / sell row refresh, the comparators
    for (u32 item = 0; item < 0x300; item += 0x17) {
        sp_pair(m, "sub_3F2240", {sx(kOut + 0x100), item, 0, 0}, ++seed, "sub_3F2240 row");
        // a fake list row: node {+20 -> payload {+28 -> row}}
        const u32 node = kOut + 0x200, pay = kOut + 0x240, row = kOut + 0x280;
        std::memset(m.at(node), 0, 0x100);
        w32(m, node + shop::kNodePayload, pay);
        w32(m, pay + 28, row);
        w16(m, row + 4, static_cast<u16>(item));
        w16(m, row + 6, static_cast<u16>(item & 0xFF));
        w32(m, row + 8, (item & 1u) ? 0x4000u : 0x1003u);
        w32(m, row + 16, item * 37u);
        w32(m, kYen, item * 20u);
        const hgp::Run b = sp_pair(m, "sub_3F2DC0", {sx(kOut + 0x300), sx(node), 0, 0}, ++seed, "sub_3F2DC0 buy row");
        if (!b.stopped && r32(m, row + 16) > r32(m, kYen)) CHECK((r32(m, row) & 0x10u) == 0x10u);
        sp_pair(m, "sub_3F9B20", {sx(kOut + 0x300), sx(node), 0, 0}, ++seed, "sub_3F9B20 sell row");
    }
    // comparators: two rows, keys by category nibble, then the id
    for (int i = 0; i < 64; ++i) {
        const u32 na = kOut + 0x400, nb = kOut + 0x500;
        for (u32 n : {na, nb}) {
            std::memset(m.at(n), 0, 0x100);
            w32(m, n, n + 0x10);             // the comparator gets pointers to node pointers
            w32(m, n + 0x10 + shop::kNodePayload, n + 0x40);
            w32(m, n + 0x40 + 28, n + 0x80);
            const u32 row = n + 0x80;
            w32(m, row, rng() & 0x40u);
            w16(m, row + 4, static_cast<u16>(rng() % 0x300));
            w32(m, row + 8, (rng() % 3) | ((rng() % 5) << 8));
            w32(m, row + 16, rng() % 100000);
            for (u32 o : {20u, 24u, 26u}) w16(m, row + o, static_cast<u16>(rng() % 50));
        }
        sp_pair(m, "sub_3F3280", {sx(na), sx(nb), 0, 0}, ++seed, "sub_3F3280 compare");
        const hgp::Run s = sp_pair(m, "sub_3F9CB0", {sx(na), sx(nb), 0, 0}, ++seed, "sub_3F9CB0 compare");
        const bool ea = (r32(m, na + 0x80) & 0x40u) != 0, eb = (r32(m, nb + 0x80) & 0x40u) != 0;
        if (!s.stopped && ea != eb) CHECK(v0s(s) == (ea ? 1 : -1));  // +1 when the first row is the equipped one
    }
    // the description fade: 10 frames in, 10 out
    for (u32 state = 0; state <= 6; ++state)
        for (u32 frame = 0; frame < 12; frame += 3) {
            std::memset(m.at(kOut + 0x600), 0, 0x100);
            w16(m, kOut + 0x600, static_cast<u16>(state));
            w32(m, kOut + 0x608, frame);
            const hgp::Run f = sp_pair(m, "sub_3FBF20", {sx(kOut + 0x600), 0, 0, 0}, ++seed, "sub_3FBF20 fade");
            if (f.stopped) continue;
            if (state == 1 || state == 2) {
                const u32 n = state == 1 ? 1u : frame + 1;
                CHECK(r16s(m, kOut + 0x600 + 148) == static_cast<s16>(static_cast<s32>(255.0f * static_cast<float>(n) / 10.0f)));
            }
        }
    // the description row copy, the list view bits, the type info dispatch
    sp_pair(m, "sub_3FB290", {sx(kOut + 0x700), sx(kOut + 0x100), 0, 0}, ++seed, "sub_3FB290");
    CHECK(std::memcmp(m.at(kOut + 0x70C), m.at(kOut + 0x100), 28) == 0);
}

// =====================================================================================================================
// The sprite bank, the number drawer, the background manager and the COMM handlers
// =====================================================================================================================
TEST_CASE("game(shops): sprite bank, digits, background manager and the facility COMM handlers") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = shop_snapshot("shop_ref_4100");
    if (!snap.empty()) restore(m, snap);
    write_rw_slots(m);
    u32 seed = 0x9000;
    // the bank of every descriptor of 0x6A9930 (create / load / free on the heap stand-ins) and the current one's draws
    for (u32 d = 0; d < 9; ++d) {
        const hgp::Run desc = sp_pair(m, "sub_3EFED0", {d, 0, 0, 0}, ++seed, "sub_3EFED0 descriptor");
        CHECK(v0_of(desc) == static_cast<u64>(0x6A9930u + 16 * d));
        sp_pair(m, "sub_40E450", {sx(0x6A9930u + 16 * d), 0, 0, 0}, ++seed, "sub_40E450 bank create");
    }
    CHECK(v0_of(sp_pair(m, "sub_3EFEF0", {0, 0, 0, 0}, ++seed, "sub_3EFEF0")) == 0x6A99C0u);
    if (!snap.empty() && r32(m, shop::kSpriteBankGlobal) != 0) {
        const u32 bank = r32(m, shop::kSpriteBankGlobal);
        for (u32 s = 0; s < 40; s += 3) {
            sp_pair(m, "sub_40E3C0", {sx(100 + s), sx(200), s & 0xFFu, s}, ++seed, "sub_40E3C0 sprite", Opt{{{GPR_T0, s & 3u}}, {{12, 0x3F800000u}}, true});
            sp_pair(m, "sub_40E3F0", {sx(100 + s), sx(200), s & 0xFFu, s}, ++seed, "sub_40E3F0 sprite ex",
                    Opt{{{GPR_T0, 0}, {GPR_T1, 4}, {GPR_T2, 8}}, {{12, 0x3F000000u}, {13, 0x3F800000u}, {15, 0x40000000u}}, true});
        }
        sp_pair(m, "sub_40E4F0", {sx(bank), 0, 0, 0}, ++seed, "sub_40E4F0 bank load");
        sp_pair(m, "sub_40E390", {0, 0, 0, 0}, ++seed, "sub_40E390 ready");
        sp_pair(m, "sub_40E580", {sx(bank), 0, 0, 0}, ++seed, "sub_40E580 bank free");
        restore(m, snap);
        write_rw_slots(m);
        sp_pair(m, "sub_40E300", {sx(0x6A9930u + 16 * 2), 7, 0, 0}, ++seed, "sub_40E300 bank swap");
        CHECK(r32(m, shop::kSpriteBankArg) == 7u);
    }
    // digit strings: spaces, separators (flag 8), alignment (1 right, 2 centre)
    const char* strs[] = {"0", "7", "42", "1234", "9999999", " 12", "100000", "12 34"};
    for (const char* s : strs)
        for (u32 flags : {0u, 1u, 2u, 8u, 9u, 10u})
            for (u32 size = 0; size < 5; ++size) {
                std::memset(m.at(kOut + 0x800), 0, 32);
                std::memcpy(m.at(kOut + 0x800), s, std::strlen(s));
                sp_pair(m, "sub_40EB50", {sx(300), sx(100), 0x80u, size}, ++seed, "sub_40EB50 digits",
                        Opt{{{GPR_T0, sx(kOut + 0x800)}, {GPR_T1, flags}}, {{12, 0x3F800000u}}, true});
            }
    // a fresh background manager: create, mode rule, scene of the pharmacy, load poll
    if (!snap.empty()) restore(m, snap);
    write_rw_slots(m);
    const hgp::Run mk = sp_pair(m, "fclShopMisc_CreateShopDrawBGLowTasks", {0, 0, 0, 0}, ++seed, "BG create");
    if (!mk.stopped && v0_of(mk) != 0) {
        const u32 mgr = static_cast<u32>(v0_of(mk));
        if (g_t.world[1])  // the manager's blocks stay taken for the pairs below
            for (const auto& [va, size] : g_t.world[1]->heap.live()) g_reserved.emplace_back(va, size);
        CHECK(static_cast<s32>(r32(m, mgr + shop::kBgMode)) == -1);
        for (u32 mode : {3u, 3u, 5u, 0u}) {
            const u32 before = r32(m, mgr + shop::kBgFlags), was = r32(m, mgr + shop::kBgMode);
            sp_pair(m, "sub_4015A0", {sx(mgr), mode, 0, 0}, ++seed, "sub_4015A0 mode");
            if (was != mode) {
                CHECK(r32(m, mgr + shop::kBgMode) == mode);
                CHECK(r32(m, mgr + shop::kBgFlags) == ((before & 1u) ? (before | 5u) : (before | 1u)));
            } else {
                CHECK(r32(m, mgr + shop::kBgFlags) == before);
            }
        }
        const u32 scene = r32(m, 0x6B1F30u + 16 * 2);
        (void)scene;
        sp_pair(m, "sub_401420", {sx(mgr), sx(0x6B1F30u + 16 * 2), 0, 0}, ++seed, "sub_401420 scene");
        CHECK(r32(m, mgr + shop::kBgScene) == 0x6B1F30u + 16 * 2);
        sp_pair(m, "sub_4014E0", {sx(mgr), 0, 0, 0}, ++seed, "sub_4014E0 load poll");
        g_reserved.clear();
    }
    // the COMM handlers on the snapshot's script state (scrGetIntPara / scrGetCmdTimer are hand-written: they read the
    // running script), the facility number they keep, and the wait handler for every number
    for (u32 n = 0; n <= 10; ++n) {
        if (!snap.empty()) restore(m, snap);
        write_rw_slots(m);
        const hgp::Run s = sp_pair(m, "sub_40D410", {0, 0, 0, 0}, ++seed, "sub_40D410 facility start");
        if (!s.stopped) {
            CHECK(v0_of(s) == 1u);
            const u32 f = r32(m, kFacility);
            CHECK((f <= 8u || f == 0xFFFFFFFFu));
        }
        w32(m, kFacility, n <= 8 ? n : 0xFFFFFFFFu);
        const hgp::Run wt = sp_pair(m, "sub_40D490", {0, 0, 0, 0}, ++seed, "sub_40D490 facility wait");
        if (!wt.stopped) CHECK(v0_of(wt) <= 1u);
        if (!wt.stopped && n > 8) CHECK(r32(m, kFacility) == 0xFFFFFFFFu);
    }
}

TEST_CASE("game(shops): pair count") {
    MESSAGE("shops pairs run (outside the random-world case): " << g_pairs);
    for (const auto& [k, n] : g_stops) MESSAGE("  stopped " << n << "x  " << k);
}

#else

TEST_CASE("game(shops): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
