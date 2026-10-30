// Pair tests for slice gamedata (game/src/data/gamedata.cpp: the g_data.c / datPersona.c state accessors). Every body
// against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS
// window and the bus log.
//   1. the generic sweep: random words and pointers in a scratch window (mostly the bad-input and early-stop paths);
//   2. the real game state: the replay snapshots climb_ref_17000 (Tartarus, the party formed), fusion_vr_5000 (the
//      Velvet Room, two personas held), shop_ref_4100 and dorm_replay_4900 as the machine, every function on the ids
//      its callers pass (pc 1..10, comu 0..29, owners -1 / 1 / members / 256 + pc, the held item ids, the stock
//      slots and personas) plus the edges its branches test;
//   3. documented rules on the host (expected values computed from the snapshot's own records: money and its clamp,
//      the item counts and their 0..99 clamp, the equipment entries, the persona stock size and searches, the social
//      link ranks / arcana search, the exp table level, the item kinds), checked on the recompiled run's result.
// The callees run for real (tests/game/CMakeLists.txt: the dat* layer is hand-written, sub_3BDxxx / sub_17AC60 /
// sub_17AD90 / sub_176210 / sub_176680 / sub_17CD30 / sub_16DBC0 are emitted); printf (sub_16E670) is a stand-in.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/gamedata.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
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

namespace p3fes::recomp_gen {
void fn_sub_16C470_0016c470(EEContext&);  // generated body
void fn_sub_16C470_0016c470__recomp(EEContext&);  // recompiled
void fn_sub_16C4F0_0016c4f0(EEContext&);  // generated body
void fn_sub_16C4F0_0016c4f0__recomp(EEContext&);  // recompiled
void fn_sub_16C570_0016c570(EEContext&);  // generated body
void fn_sub_16C570_0016c570__recomp(EEContext&);  // recompiled
void fn_sub_16C5F0_0016c5f0(EEContext&);  // generated body
void fn_sub_16C5F0_0016c5f0__recomp(EEContext&);  // recompiled
void fn_sub_16C670_0016c670(EEContext&);  // generated body
void fn_sub_16C670_0016c670__recomp(EEContext&);  // recompiled
void fn_sub_16C7E0_0016c7e0(EEContext&);  // generated body
void fn_sub_16C7E0_0016c7e0__recomp(EEContext&);  // recompiled
void fn_sub_16C860_0016c860(EEContext&);  // generated body
void fn_sub_16C860_0016c860__recomp(EEContext&);  // recompiled
void fn_sub_16C910_0016c910(EEContext&);  // generated body
void fn_sub_16C910_0016c910__recomp(EEContext&);  // recompiled
void fn_sub_16C920_0016c920(EEContext&);  // generated body
void fn_sub_16C920_0016c920__recomp(EEContext&);  // recompiled
void fn_sub_16C970_0016c970(EEContext&);  // generated body
void fn_sub_16C970_0016c970__recomp(EEContext&);  // recompiled
void fn_sub_16C9F0_0016c9f0(EEContext&);  // generated body
void fn_sub_16C9F0_0016c9f0__recomp(EEContext&);  // recompiled
void fn_sub_16CA40_0016ca40(EEContext&);  // generated body
void fn_sub_16CA40_0016ca40__recomp(EEContext&);  // recompiled
void fn_sub_16CA90_0016ca90(EEContext&);  // generated body
void fn_sub_16CA90_0016ca90__recomp(EEContext&);  // recompiled
void fn_sub_16CDF0_0016cdf0(EEContext&);  // generated body
void fn_sub_16CDF0_0016cdf0__recomp(EEContext&);  // recompiled
void fn_sub_16CEF0_0016cef0(EEContext&);  // generated body
void fn_sub_16CEF0_0016cef0__recomp(EEContext&);  // recompiled
void fn_sub_16CF40_0016cf40(EEContext&);  // generated body
void fn_sub_16CF40_0016cf40__recomp(EEContext&);  // recompiled
void fn_sub_16CF90_0016cf90(EEContext&);  // generated body
void fn_sub_16CF90_0016cf90__recomp(EEContext&);  // recompiled
void fn_sub_16D230_0016d230(EEContext&);  // generated body
void fn_sub_16D230_0016d230__recomp(EEContext&);  // recompiled
void fn_sub_16D280_0016d280(EEContext&);  // generated body
void fn_sub_16D280_0016d280__recomp(EEContext&);  // recompiled
void fn_sub_16D560_0016d560(EEContext&);  // generated body
void fn_sub_16D560_0016d560__recomp(EEContext&);  // recompiled
void fn_sub_16D6B0_0016d6b0(EEContext&);  // generated body
void fn_sub_16D6B0_0016d6b0__recomp(EEContext&);  // recompiled
void fn_sub_16D8B0_0016d8b0(EEContext&);  // generated body
void fn_sub_16D8B0_0016d8b0__recomp(EEContext&);  // recompiled
void fn_sub_16D930_0016d930(EEContext&);  // generated body
void fn_sub_16D930_0016d930__recomp(EEContext&);  // recompiled
void fn_sub_16D980_0016d980(EEContext&);  // generated body
void fn_sub_16D980_0016d980__recomp(EEContext&);  // recompiled
void fn_sub_16D9D0_0016d9d0(EEContext&);  // generated body
void fn_sub_16D9D0_0016d9d0__recomp(EEContext&);  // recompiled
void fn_sub_16DA50_0016da50(EEContext&);  // generated body
void fn_sub_16DA50_0016da50__recomp(EEContext&);  // recompiled
void fn_sub_16DAD0_0016dad0(EEContext&);  // generated body
void fn_sub_16DAD0_0016dad0__recomp(EEContext&);  // recompiled
void fn_sub_16DD80_0016dd80(EEContext&);  // generated body
void fn_sub_16DD80_0016dd80__recomp(EEContext&);  // recompiled
void fn_sub_16DB70_0016db70(EEContext&);  // generated body
void fn_sub_16DB70_0016db70__recomp(EEContext&);  // recompiled
void fn_sub_16DBA0_0016dba0(EEContext&);  // generated body
void fn_sub_16DBA0_0016dba0__recomp(EEContext&);  // recompiled
void fn_sub_16DCE0_0016dce0(EEContext&);  // generated body
void fn_sub_16DCE0_0016dce0__recomp(EEContext&);  // recompiled
void fn_sub_16DD20_0016dd20(EEContext&);  // generated body
void fn_sub_16DD20_0016dd20__recomp(EEContext&);  // recompiled
void fn_sub_16DD40_0016dd40(EEContext&);  // generated body
void fn_sub_16DD40_0016dd40__recomp(EEContext&);  // recompiled
void fn_sub_16DEB0_0016deb0(EEContext&);  // generated body
void fn_sub_16DEB0_0016deb0__recomp(EEContext&);  // recompiled
void fn_sub_16DF30_0016df30(EEContext&);  // generated body
void fn_sub_16DF30_0016df30__recomp(EEContext&);  // recompiled
void fn_sub_16DFB0_0016dfb0(EEContext&);  // generated body
void fn_sub_16DFB0_0016dfb0__recomp(EEContext&);  // recompiled
void fn_sub_16E100_0016e100(EEContext&);  // generated body
void fn_sub_16E100_0016e100__recomp(EEContext&);  // recompiled
void fn_sub_16E2B0_0016e2b0(EEContext&);  // generated body
void fn_sub_16E2B0_0016e2b0__recomp(EEContext&);  // recompiled
void fn_sub_16E410_0016e410(EEContext&);  // generated body
void fn_sub_16E410_0016e410__recomp(EEContext&);  // recompiled
void fn_sub_16E5F0_0016e5f0(EEContext&);  // generated body
void fn_sub_16E5F0_0016e5f0__recomp(EEContext&);  // recompiled
void fn_sub_16E670_0016e670(EEContext&);  // generated body
void fn_sub_16E670_0016e670__recomp(EEContext&);  // recompiled
void fn_sub_16E7A0_0016e7a0(EEContext&);  // generated body
void fn_sub_16E7A0_0016e7a0__recomp(EEContext&);  // recompiled
void fn_sub_16E850_0016e850(EEContext&);  // generated body
void fn_sub_16E850_0016e850__recomp(EEContext&);  // recompiled
void fn_sub_16E920_0016e920(EEContext&);  // generated body
void fn_sub_16E920_0016e920__recomp(EEContext&);  // recompiled
void fn_sub_1717B0_001717b0(EEContext&);  // generated body
void fn_sub_1717B0_001717b0__recomp(EEContext&);  // recompiled
void fn_sub_1717C0_001717c0(EEContext&);  // generated body
void fn_sub_1717C0_001717c0__recomp(EEContext&);  // recompiled
void fn_sub_1718B0_001718b0(EEContext&);  // generated body
void fn_sub_1718B0_001718b0__recomp(EEContext&);  // recompiled
void fn_sub_171960_00171960(EEContext&);  // generated body
void fn_sub_171960_00171960__recomp(EEContext&);  // recompiled
void fn_sub_171AC0_00171ac0(EEContext&);  // generated body
void fn_sub_171AC0_00171ac0__recomp(EEContext&);  // recompiled
void fn_sub_171B50_00171b50(EEContext&);  // generated body
void fn_sub_171B50_00171b50__recomp(EEContext&);  // recompiled
void fn_sub_171C40_00171c40(EEContext&);  // generated body
void fn_sub_171C40_00171c40__recomp(EEContext&);  // recompiled
void fn_sub_171E90_00171e90(EEContext&);  // generated body
void fn_sub_171E90_00171e90__recomp(EEContext&);  // recompiled
void fn_sub_171F50_00171f50(EEContext&);  // generated body
void fn_sub_171F50_00171f50__recomp(EEContext&);  // recompiled
void fn_sub_1720C0_001720c0(EEContext&);  // generated body
void fn_sub_1720C0_001720c0__recomp(EEContext&);  // recompiled
void fn_sub_172160_00172160(EEContext&);  // generated body
void fn_sub_172160_00172160__recomp(EEContext&);  // recompiled
void fn_sub_172200_00172200(EEContext&);  // generated body
void fn_sub_172200_00172200__recomp(EEContext&);  // recompiled
void fn_sub_1723A0_001723a0(EEContext&);  // generated body
void fn_sub_1723A0_001723a0__recomp(EEContext&);  // recompiled
void fn_sub_1724A0_001724a0(EEContext&);  // generated body
void fn_sub_1724A0_001724a0__recomp(EEContext&);  // recompiled
void fn_sub_1725A0_001725a0(EEContext&);  // generated body
void fn_sub_1725A0_001725a0__recomp(EEContext&);  // recompiled
void fn_sub_172660_00172660(EEContext&);  // generated body
void fn_sub_172660_00172660__recomp(EEContext&);  // recompiled
void fn_sub_16DD50_0016dd50(EEContext&);  // generated body
void fn_sub_16DD50_0016dd50__recomp(EEContext&);  // recompiled
void fn_sub_16DD60_0016dd60(EEContext&);  // generated body
void fn_sub_16DD60_0016dd60__recomp(EEContext&);  // recompiled
void fn_sub_16E930_0016e930(EEContext&);  // generated body
void fn_sub_16E930_0016e930__recomp(EEContext&);  // recompiled
void fn_sub_16E990_0016e990(EEContext&);  // generated body
void fn_sub_16E990_0016e990__recomp(EEContext&);  // recompiled
void fn_sub_16E9B0_0016e9b0(EEContext&);  // generated body
void fn_sub_16E9B0_0016e9b0__recomp(EEContext&);  // recompiled
void fn_sub_16EA40_0016ea40(EEContext&);  // generated body
void fn_sub_16EA40_0016ea40__recomp(EEContext&);  // recompiled
void fn_sub_16DDD0_0016ddd0(EEContext&);  // generated body
void fn_sub_16DDD0_0016ddd0__recomp(EEContext&);  // recompiled
void fn_sub_16DE50_0016de50(EEContext&);  // generated body
void fn_sub_16DE50_0016de50__recomp(EEContext&);  // recompiled
void fn_sub_16F490_0016f490(EEContext&);  // generated body
void fn_sub_16F490_0016f490__recomp(EEContext&);  // recompiled
void fn_sub_16F720_0016f720(EEContext&);  // generated body
void fn_sub_16F720_0016f720__recomp(EEContext&);  // recompiled
void fn_sub_16F810_0016f810(EEContext&);  // generated body
void fn_sub_16F810_0016f810__recomp(EEContext&);  // recompiled
void fn_sub_16F9F0_0016f9f0(EEContext&);  // generated body
void fn_sub_16F9F0_0016f9f0__recomp(EEContext&);  // recompiled
void fn_sub_16FAE0_0016fae0(EEContext&);  // generated body
void fn_sub_16FAE0_0016fae0__recomp(EEContext&);  // recompiled
void fn_sub_16FBD0_0016fbd0(EEContext&);  // generated body
void fn_sub_16FBD0_0016fbd0__recomp(EEContext&);  // recompiled
void fn_sub_16FCC0_0016fcc0(EEContext&);  // generated body
void fn_sub_16FCC0_0016fcc0__recomp(EEContext&);  // recompiled
void fn_sub_16FDB0_0016fdb0(EEContext&);  // generated body
void fn_sub_16FDB0_0016fdb0__recomp(EEContext&);  // recompiled
void fn_sub_16FEA0_0016fea0(EEContext&);  // generated body
void fn_sub_16FEA0_0016fea0__recomp(EEContext&);  // recompiled
void fn_sub_16FF90_0016ff90(EEContext&);  // generated body
void fn_sub_16FF90_0016ff90__recomp(EEContext&);  // recompiled
void fn_sub_170080_00170080(EEContext&);  // generated body
void fn_sub_170080_00170080__recomp(EEContext&);  // recompiled
void fn_sub_170170_00170170(EEContext&);  // generated body
void fn_sub_170170_00170170__recomp(EEContext&);  // recompiled
void fn_sub_170260_00170260(EEContext&);  // generated body
void fn_sub_170260_00170260__recomp(EEContext&);  // recompiled
void fn_sub_170350_00170350(EEContext&);  // generated body
void fn_sub_170350_00170350__recomp(EEContext&);  // recompiled
void fn_sub_170440_00170440(EEContext&);  // generated body
void fn_sub_170440_00170440__recomp(EEContext&);  // recompiled
void fn_sub_170530_00170530(EEContext&);  // generated body
void fn_sub_170530_00170530__recomp(EEContext&);  // recompiled
void fn_sub_170620_00170620(EEContext&);  // generated body
void fn_sub_170620_00170620__recomp(EEContext&);  // recompiled
void fn_sub_170670_00170670(EEContext&);  // generated body
void fn_sub_170670_00170670__recomp(EEContext&);  // recompiled
void fn_sub_1706C0_001706c0(EEContext&);  // generated body
void fn_sub_1706C0_001706c0__recomp(EEContext&);  // recompiled
void fn_sub_170710_00170710(EEContext&);  // generated body
void fn_sub_170710_00170710__recomp(EEContext&);  // recompiled
void fn_sub_170A40_00170a40(EEContext&);  // generated body
void fn_sub_170A40_00170a40__recomp(EEContext&);  // recompiled
void fn_sub_170AB0_00170ab0(EEContext&);  // generated body
void fn_sub_170AB0_00170ab0__recomp(EEContext&);  // recompiled
void fn_sub_170B20_00170b20(EEContext&);  // generated body
void fn_sub_170B20_00170b20__recomp(EEContext&);  // recompiled
void fn_sub_170B90_00170b90(EEContext&);  // generated body
void fn_sub_170B90_00170b90__recomp(EEContext&);  // recompiled
void fn_sub_170760_00170760(EEContext&);  // generated body
void fn_sub_170760_00170760__recomp(EEContext&);  // recompiled
void fn_sub_170860_00170860(EEContext&);  // generated body
void fn_sub_170860_00170860__recomp(EEContext&);  // recompiled
void fn_sub_170C00_00170c00(EEContext&);  // generated body
void fn_sub_170C00_00170c00__recomp(EEContext&);  // recompiled
void fn_sub_171060_00171060(EEContext&);  // generated body
void fn_sub_171060_00171060__recomp(EEContext&);  // recompiled
void fn_sub_171110_00171110(EEContext&);  // generated body
void fn_sub_171110_00171110__recomp(EEContext&);  // recompiled
void fn_sub_171250_00171250(EEContext&);  // generated body
void fn_sub_171250_00171250__recomp(EEContext&);  // recompiled
void fn_sub_171360_00171360(EEContext&);  // generated body
void fn_sub_171360_00171360__recomp(EEContext&);  // recompiled
void fn_sub_171390_00171390(EEContext&);  // generated body
void fn_sub_171390_00171390__recomp(EEContext&);  // recompiled
void fn_sub_172820_00172820(EEContext&);  // generated body
void fn_sub_172820_00172820__recomp(EEContext&);  // recompiled
void fn_sub_172890_00172890(EEContext&);  // generated body
void fn_sub_172890_00172890__recomp(EEContext&);  // recompiled
void fn_sub_1728D0_001728d0(EEContext&);  // generated body
void fn_sub_1728D0_001728d0__recomp(EEContext&);  // recompiled
void fn_sub_172990_00172990(EEContext&);  // generated body
void fn_sub_172990_00172990__recomp(EEContext&);  // recompiled
void fn_sub_1729A0_001729a0(EEContext&);  // generated body
void fn_sub_1729A0_001729a0__recomp(EEContext&);  // recompiled
void fn_sub_1729D0_001729d0(EEContext&);  // generated body
void fn_sub_1729D0_001729d0__recomp(EEContext&);  // recompiled
void fn_sub_172A10_00172a10(EEContext&);  // generated body
void fn_sub_172A10_00172a10__recomp(EEContext&);  // recompiled
void fn_sub_172A20_00172a20(EEContext&);  // generated body
void fn_sub_172A20_00172a20__recomp(EEContext&);  // recompiled
void fn_sub_172A30_00172a30(EEContext&);  // generated body
void fn_sub_172A30_00172a30__recomp(EEContext&);  // recompiled
void fn_sub_172AB0_00172ab0(EEContext&);  // generated body
void fn_sub_172AB0_00172ab0__recomp(EEContext&);  // recompiled
void fn_sub_172AE0_00172ae0(EEContext&);  // generated body
void fn_sub_172AE0_00172ae0__recomp(EEContext&);  // recompiled
void fn_sub_172B20_00172b20(EEContext&);  // generated body
void fn_sub_172B20_00172b20__recomp(EEContext&);  // recompiled
void fn_sub_172C50_00172c50(EEContext&);  // generated body
void fn_sub_172C50_00172c50__recomp(EEContext&);  // recompiled
void fn_sub_172CC0_00172cc0(EEContext&);  // generated body
void fn_sub_172CC0_00172cc0__recomp(EEContext&);  // recompiled
void fn_sub_172D70_00172d70(EEContext&);  // generated body
void fn_sub_172D70_00172d70__recomp(EEContext&);  // recompiled
void fn_sub_172E10_00172e10(EEContext&);  // generated body
void fn_sub_172E10_00172e10__recomp(EEContext&);  // recompiled
void fn_sub_172E40_00172e40(EEContext&);  // generated body
void fn_sub_172E40_00172e40__recomp(EEContext&);  // recompiled
void fn_sub_173280_00173280(EEContext&);  // generated body
void fn_sub_173280_00173280__recomp(EEContext&);  // recompiled
void fn_sub_173300_00173300(EEContext&);  // generated body
void fn_sub_173300_00173300__recomp(EEContext&);  // recompiled
void fn_sub_173330_00173330(EEContext&);  // generated body
void fn_sub_173330_00173330__recomp(EEContext&);  // recompiled
void fn_sub_173340_00173340(EEContext&);  // generated body
void fn_sub_173340_00173340__recomp(EEContext&);  // recompiled
void fn_sub_173370_00173370(EEContext&);  // generated body
void fn_sub_173370_00173370__recomp(EEContext&);  // recompiled
void fn_sub_173580_00173580(EEContext&);  // generated body
void fn_sub_173580_00173580__recomp(EEContext&);  // recompiled
void fn_sub_173660_00173660(EEContext&);  // generated body
void fn_sub_173660_00173660__recomp(EEContext&);  // recompiled
void fn_sub_173780_00173780(EEContext&);  // generated body
void fn_sub_173780_00173780__recomp(EEContext&);  // recompiled
void fn_sub_173A00_00173a00(EEContext&);  // generated body
void fn_sub_173A00_00173a00__recomp(EEContext&);  // recompiled
void fn_sub_173B00_00173b00(EEContext&);  // generated body
void fn_sub_173B00_00173b00__recomp(EEContext&);  // recompiled
void fn_sub_173B60_00173b60(EEContext&);  // generated body
void fn_sub_173B60_00173b60__recomp(EEContext&);  // recompiled
void fn_sub_173BB0_00173bb0(EEContext&);  // generated body
void fn_sub_173BB0_00173bb0__recomp(EEContext&);  // recompiled
void fn_sub_173C00_00173c00(EEContext&);  // generated body
void fn_sub_173C00_00173c00__recomp(EEContext&);  // recompiled
void fn_sub_174650_00174650(EEContext&);  // generated body
void fn_sub_174650_00174650__recomp(EEContext&);  // recompiled
void fn_sub_174710_00174710(EEContext&);  // generated body
void fn_sub_174710_00174710__recomp(EEContext&);  // recompiled
void fn_sub_1748C0_001748c0(EEContext&);  // generated body
void fn_sub_1748C0_001748c0__recomp(EEContext&);  // recompiled
void fn_sub_174960_00174960(EEContext&);  // generated body
void fn_sub_174960_00174960__recomp(EEContext&);  // recompiled
void fn_sub_1749A0_001749a0(EEContext&);  // generated body
void fn_sub_1749A0_001749a0__recomp(EEContext&);  // recompiled
void fn_sub_174B40_00174b40(EEContext&);  // generated body
void fn_sub_174B40_00174b40__recomp(EEContext&);  // recompiled
void fn_sub_174E20_00174e20(EEContext&);  // generated body
void fn_sub_174E20_00174e20__recomp(EEContext&);  // recompiled
void fn_sub_174E70_00174e70(EEContext&);  // generated body
void fn_sub_174E70_00174e70__recomp(EEContext&);  // recompiled
void fn_sub_174FB0_00174fb0(EEContext&);  // generated body
void fn_sub_174FB0_00174fb0__recomp(EEContext&);  // recompiled
void fn_sub_175130_00175130(EEContext&);  // generated body
void fn_sub_175130_00175130__recomp(EEContext&);  // recompiled
void fn_sub_175200_00175200(EEContext&);  // generated body
void fn_sub_175200_00175200__recomp(EEContext&);  // recompiled
void fn_sub_1752B0_001752b0(EEContext&);  // generated body
void fn_sub_1752B0_001752b0__recomp(EEContext&);  // recompiled
void fn_sub_175360_00175360(EEContext&);  // generated body
void fn_sub_175360_00175360__recomp(EEContext&);  // recompiled
void fn_sub_1754A0_001754a0(EEContext&);  // generated body
void fn_sub_1754A0_001754a0__recomp(EEContext&);  // recompiled
void fn_sub_1755C0_001755c0(EEContext&);  // generated body
void fn_sub_1755C0_001755c0__recomp(EEContext&);  // recompiled
void fn_sub_1756F0_001756f0(EEContext&);  // generated body
void fn_sub_1756F0_001756f0__recomp(EEContext&);  // recompiled
void fn_sub_1757F0_001757f0(EEContext&);  // generated body
void fn_sub_1757F0_001757f0__recomp(EEContext&);  // recompiled
void fn_sub_175BE0_00175be0(EEContext&);  // generated body
void fn_sub_175BE0_00175be0__recomp(EEContext&);  // recompiled
void fn_sub_175C70_00175c70(EEContext&);  // generated body
void fn_sub_175C70_00175c70__recomp(EEContext&);  // recompiled
void fn_sub_175CA0_00175ca0(EEContext&);  // generated body
void fn_sub_175CA0_00175ca0__recomp(EEContext&);  // recompiled
void fn_sub_176100_00176100(EEContext&);  // generated body
void fn_sub_176100_00176100__recomp(EEContext&);  // recompiled
void fn_sub_1761B0_001761b0(EEContext&);  // generated body
void fn_sub_1761B0_001761b0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_16C470", 0x16C470, &recomp_gen::fn_sub_16C470_0016c470, &recomp_gen::fn_sub_16C470_0016c470__recomp},
    {"sub_16C4F0", 0x16C4F0, &recomp_gen::fn_sub_16C4F0_0016c4f0, &recomp_gen::fn_sub_16C4F0_0016c4f0__recomp},
    {"sub_16C570", 0x16C570, &recomp_gen::fn_sub_16C570_0016c570, &recomp_gen::fn_sub_16C570_0016c570__recomp},
    {"sub_16C5F0", 0x16C5F0, &recomp_gen::fn_sub_16C5F0_0016c5f0, &recomp_gen::fn_sub_16C5F0_0016c5f0__recomp},
    {"sub_16C670", 0x16C670, &recomp_gen::fn_sub_16C670_0016c670, &recomp_gen::fn_sub_16C670_0016c670__recomp},
    {"sub_16C7E0", 0x16C7E0, &recomp_gen::fn_sub_16C7E0_0016c7e0, &recomp_gen::fn_sub_16C7E0_0016c7e0__recomp},
    {"sub_16C860", 0x16C860, &recomp_gen::fn_sub_16C860_0016c860, &recomp_gen::fn_sub_16C860_0016c860__recomp},
    {"sub_16C910", 0x16C910, &recomp_gen::fn_sub_16C910_0016c910, &recomp_gen::fn_sub_16C910_0016c910__recomp},
    {"sub_16C920", 0x16C920, &recomp_gen::fn_sub_16C920_0016c920, &recomp_gen::fn_sub_16C920_0016c920__recomp},
    {"sub_16C970", 0x16C970, &recomp_gen::fn_sub_16C970_0016c970, &recomp_gen::fn_sub_16C970_0016c970__recomp},
    {"sub_16C9F0", 0x16C9F0, &recomp_gen::fn_sub_16C9F0_0016c9f0, &recomp_gen::fn_sub_16C9F0_0016c9f0__recomp},
    {"sub_16CA40", 0x16CA40, &recomp_gen::fn_sub_16CA40_0016ca40, &recomp_gen::fn_sub_16CA40_0016ca40__recomp},
    {"sub_16CA90", 0x16CA90, &recomp_gen::fn_sub_16CA90_0016ca90, &recomp_gen::fn_sub_16CA90_0016ca90__recomp},
    {"sub_16CDF0", 0x16CDF0, &recomp_gen::fn_sub_16CDF0_0016cdf0, &recomp_gen::fn_sub_16CDF0_0016cdf0__recomp},
    {"sub_16CEF0", 0x16CEF0, &recomp_gen::fn_sub_16CEF0_0016cef0, &recomp_gen::fn_sub_16CEF0_0016cef0__recomp},
    {"sub_16CF40", 0x16CF40, &recomp_gen::fn_sub_16CF40_0016cf40, &recomp_gen::fn_sub_16CF40_0016cf40__recomp},
    {"sub_16CF90", 0x16CF90, &recomp_gen::fn_sub_16CF90_0016cf90, &recomp_gen::fn_sub_16CF90_0016cf90__recomp},
    {"sub_16D230", 0x16D230, &recomp_gen::fn_sub_16D230_0016d230, &recomp_gen::fn_sub_16D230_0016d230__recomp},
    {"sub_16D280", 0x16D280, &recomp_gen::fn_sub_16D280_0016d280, &recomp_gen::fn_sub_16D280_0016d280__recomp},
    {"sub_16D560", 0x16D560, &recomp_gen::fn_sub_16D560_0016d560, &recomp_gen::fn_sub_16D560_0016d560__recomp},
    {"sub_16D6B0", 0x16D6B0, &recomp_gen::fn_sub_16D6B0_0016d6b0, &recomp_gen::fn_sub_16D6B0_0016d6b0__recomp},
    {"sub_16D8B0", 0x16D8B0, &recomp_gen::fn_sub_16D8B0_0016d8b0, &recomp_gen::fn_sub_16D8B0_0016d8b0__recomp},
    {"sub_16D930", 0x16D930, &recomp_gen::fn_sub_16D930_0016d930, &recomp_gen::fn_sub_16D930_0016d930__recomp},
    {"sub_16D980", 0x16D980, &recomp_gen::fn_sub_16D980_0016d980, &recomp_gen::fn_sub_16D980_0016d980__recomp},
    {"sub_16D9D0", 0x16D9D0, &recomp_gen::fn_sub_16D9D0_0016d9d0, &recomp_gen::fn_sub_16D9D0_0016d9d0__recomp},
    {"sub_16DA50", 0x16DA50, &recomp_gen::fn_sub_16DA50_0016da50, &recomp_gen::fn_sub_16DA50_0016da50__recomp},
    {"sub_16DAD0", 0x16DAD0, &recomp_gen::fn_sub_16DAD0_0016dad0, &recomp_gen::fn_sub_16DAD0_0016dad0__recomp},
    {"sub_16DD80", 0x16DD80, &recomp_gen::fn_sub_16DD80_0016dd80, &recomp_gen::fn_sub_16DD80_0016dd80__recomp},
    {"sub_16DB70", 0x16DB70, &recomp_gen::fn_sub_16DB70_0016db70, &recomp_gen::fn_sub_16DB70_0016db70__recomp},
    {"sub_16DBA0", 0x16DBA0, &recomp_gen::fn_sub_16DBA0_0016dba0, &recomp_gen::fn_sub_16DBA0_0016dba0__recomp},
    {"sub_16DCE0", 0x16DCE0, &recomp_gen::fn_sub_16DCE0_0016dce0, &recomp_gen::fn_sub_16DCE0_0016dce0__recomp},
    {"sub_16DD20", 0x16DD20, &recomp_gen::fn_sub_16DD20_0016dd20, &recomp_gen::fn_sub_16DD20_0016dd20__recomp},
    {"sub_16DD40", 0x16DD40, &recomp_gen::fn_sub_16DD40_0016dd40, &recomp_gen::fn_sub_16DD40_0016dd40__recomp},
    {"sub_16DEB0", 0x16DEB0, &recomp_gen::fn_sub_16DEB0_0016deb0, &recomp_gen::fn_sub_16DEB0_0016deb0__recomp},
    {"sub_16DF30", 0x16DF30, &recomp_gen::fn_sub_16DF30_0016df30, &recomp_gen::fn_sub_16DF30_0016df30__recomp},
    {"sub_16DFB0", 0x16DFB0, &recomp_gen::fn_sub_16DFB0_0016dfb0, &recomp_gen::fn_sub_16DFB0_0016dfb0__recomp},
    {"sub_16E100", 0x16E100, &recomp_gen::fn_sub_16E100_0016e100, &recomp_gen::fn_sub_16E100_0016e100__recomp},
    {"sub_16E2B0", 0x16E2B0, &recomp_gen::fn_sub_16E2B0_0016e2b0, &recomp_gen::fn_sub_16E2B0_0016e2b0__recomp},
    {"sub_16E410", 0x16E410, &recomp_gen::fn_sub_16E410_0016e410, &recomp_gen::fn_sub_16E410_0016e410__recomp},
    {"sub_16E5F0", 0x16E5F0, &recomp_gen::fn_sub_16E5F0_0016e5f0, &recomp_gen::fn_sub_16E5F0_0016e5f0__recomp},
    {"sub_16E670", 0x16E670, &recomp_gen::fn_sub_16E670_0016e670, &recomp_gen::fn_sub_16E670_0016e670__recomp},
    {"sub_16E7A0", 0x16E7A0, &recomp_gen::fn_sub_16E7A0_0016e7a0, &recomp_gen::fn_sub_16E7A0_0016e7a0__recomp},
    {"sub_16E850", 0x16E850, &recomp_gen::fn_sub_16E850_0016e850, &recomp_gen::fn_sub_16E850_0016e850__recomp},
    {"sub_16E920", 0x16E920, &recomp_gen::fn_sub_16E920_0016e920, &recomp_gen::fn_sub_16E920_0016e920__recomp},
    {"sub_1717B0", 0x1717B0, &recomp_gen::fn_sub_1717B0_001717b0, &recomp_gen::fn_sub_1717B0_001717b0__recomp},
    {"sub_1717C0", 0x1717C0, &recomp_gen::fn_sub_1717C0_001717c0, &recomp_gen::fn_sub_1717C0_001717c0__recomp},
    {"sub_1718B0", 0x1718B0, &recomp_gen::fn_sub_1718B0_001718b0, &recomp_gen::fn_sub_1718B0_001718b0__recomp},
    {"sub_171960", 0x171960, &recomp_gen::fn_sub_171960_00171960, &recomp_gen::fn_sub_171960_00171960__recomp},
    {"sub_171AC0", 0x171AC0, &recomp_gen::fn_sub_171AC0_00171ac0, &recomp_gen::fn_sub_171AC0_00171ac0__recomp},
    {"sub_171B50", 0x171B50, &recomp_gen::fn_sub_171B50_00171b50, &recomp_gen::fn_sub_171B50_00171b50__recomp},
    {"sub_171C40", 0x171C40, &recomp_gen::fn_sub_171C40_00171c40, &recomp_gen::fn_sub_171C40_00171c40__recomp},
    {"sub_171E90", 0x171E90, &recomp_gen::fn_sub_171E90_00171e90, &recomp_gen::fn_sub_171E90_00171e90__recomp},
    {"sub_171F50", 0x171F50, &recomp_gen::fn_sub_171F50_00171f50, &recomp_gen::fn_sub_171F50_00171f50__recomp},
    {"sub_1720C0", 0x1720C0, &recomp_gen::fn_sub_1720C0_001720c0, &recomp_gen::fn_sub_1720C0_001720c0__recomp},
    {"sub_172160", 0x172160, &recomp_gen::fn_sub_172160_00172160, &recomp_gen::fn_sub_172160_00172160__recomp},
    {"sub_172200", 0x172200, &recomp_gen::fn_sub_172200_00172200, &recomp_gen::fn_sub_172200_00172200__recomp},
    {"sub_1723A0", 0x1723A0, &recomp_gen::fn_sub_1723A0_001723a0, &recomp_gen::fn_sub_1723A0_001723a0__recomp},
    {"sub_1724A0", 0x1724A0, &recomp_gen::fn_sub_1724A0_001724a0, &recomp_gen::fn_sub_1724A0_001724a0__recomp},
    {"sub_1725A0", 0x1725A0, &recomp_gen::fn_sub_1725A0_001725a0, &recomp_gen::fn_sub_1725A0_001725a0__recomp},
    {"sub_172660", 0x172660, &recomp_gen::fn_sub_172660_00172660, &recomp_gen::fn_sub_172660_00172660__recomp},
    {"sub_16DD50", 0x16DD50, &recomp_gen::fn_sub_16DD50_0016dd50, &recomp_gen::fn_sub_16DD50_0016dd50__recomp},
    {"sub_16DD60", 0x16DD60, &recomp_gen::fn_sub_16DD60_0016dd60, &recomp_gen::fn_sub_16DD60_0016dd60__recomp},
    {"sub_16E930", 0x16E930, &recomp_gen::fn_sub_16E930_0016e930, &recomp_gen::fn_sub_16E930_0016e930__recomp},
    {"sub_16E990", 0x16E990, &recomp_gen::fn_sub_16E990_0016e990, &recomp_gen::fn_sub_16E990_0016e990__recomp},
    {"sub_16E9B0", 0x16E9B0, &recomp_gen::fn_sub_16E9B0_0016e9b0, &recomp_gen::fn_sub_16E9B0_0016e9b0__recomp},
    {"sub_16EA40", 0x16EA40, &recomp_gen::fn_sub_16EA40_0016ea40, &recomp_gen::fn_sub_16EA40_0016ea40__recomp},
    {"sub_16DDD0", 0x16DDD0, &recomp_gen::fn_sub_16DDD0_0016ddd0, &recomp_gen::fn_sub_16DDD0_0016ddd0__recomp},
    {"sub_16DE50", 0x16DE50, &recomp_gen::fn_sub_16DE50_0016de50, &recomp_gen::fn_sub_16DE50_0016de50__recomp},
    {"sub_16F490", 0x16F490, &recomp_gen::fn_sub_16F490_0016f490, &recomp_gen::fn_sub_16F490_0016f490__recomp},
    {"sub_16F720", 0x16F720, &recomp_gen::fn_sub_16F720_0016f720, &recomp_gen::fn_sub_16F720_0016f720__recomp},
    {"sub_16F810", 0x16F810, &recomp_gen::fn_sub_16F810_0016f810, &recomp_gen::fn_sub_16F810_0016f810__recomp},
    {"sub_16F9F0", 0x16F9F0, &recomp_gen::fn_sub_16F9F0_0016f9f0, &recomp_gen::fn_sub_16F9F0_0016f9f0__recomp},
    {"sub_16FAE0", 0x16FAE0, &recomp_gen::fn_sub_16FAE0_0016fae0, &recomp_gen::fn_sub_16FAE0_0016fae0__recomp},
    {"sub_16FBD0", 0x16FBD0, &recomp_gen::fn_sub_16FBD0_0016fbd0, &recomp_gen::fn_sub_16FBD0_0016fbd0__recomp},
    {"sub_16FCC0", 0x16FCC0, &recomp_gen::fn_sub_16FCC0_0016fcc0, &recomp_gen::fn_sub_16FCC0_0016fcc0__recomp},
    {"sub_16FDB0", 0x16FDB0, &recomp_gen::fn_sub_16FDB0_0016fdb0, &recomp_gen::fn_sub_16FDB0_0016fdb0__recomp},
    {"sub_16FEA0", 0x16FEA0, &recomp_gen::fn_sub_16FEA0_0016fea0, &recomp_gen::fn_sub_16FEA0_0016fea0__recomp},
    {"sub_16FF90", 0x16FF90, &recomp_gen::fn_sub_16FF90_0016ff90, &recomp_gen::fn_sub_16FF90_0016ff90__recomp},
    {"sub_170080", 0x170080, &recomp_gen::fn_sub_170080_00170080, &recomp_gen::fn_sub_170080_00170080__recomp},
    {"sub_170170", 0x170170, &recomp_gen::fn_sub_170170_00170170, &recomp_gen::fn_sub_170170_00170170__recomp},
    {"sub_170260", 0x170260, &recomp_gen::fn_sub_170260_00170260, &recomp_gen::fn_sub_170260_00170260__recomp},
    {"sub_170350", 0x170350, &recomp_gen::fn_sub_170350_00170350, &recomp_gen::fn_sub_170350_00170350__recomp},
    {"sub_170440", 0x170440, &recomp_gen::fn_sub_170440_00170440, &recomp_gen::fn_sub_170440_00170440__recomp},
    {"sub_170530", 0x170530, &recomp_gen::fn_sub_170530_00170530, &recomp_gen::fn_sub_170530_00170530__recomp},
    {"sub_170620", 0x170620, &recomp_gen::fn_sub_170620_00170620, &recomp_gen::fn_sub_170620_00170620__recomp},
    {"sub_170670", 0x170670, &recomp_gen::fn_sub_170670_00170670, &recomp_gen::fn_sub_170670_00170670__recomp},
    {"sub_1706C0", 0x1706C0, &recomp_gen::fn_sub_1706C0_001706c0, &recomp_gen::fn_sub_1706C0_001706c0__recomp},
    {"sub_170710", 0x170710, &recomp_gen::fn_sub_170710_00170710, &recomp_gen::fn_sub_170710_00170710__recomp},
    {"sub_170A40", 0x170A40, &recomp_gen::fn_sub_170A40_00170a40, &recomp_gen::fn_sub_170A40_00170a40__recomp},
    {"sub_170AB0", 0x170AB0, &recomp_gen::fn_sub_170AB0_00170ab0, &recomp_gen::fn_sub_170AB0_00170ab0__recomp},
    {"sub_170B20", 0x170B20, &recomp_gen::fn_sub_170B20_00170b20, &recomp_gen::fn_sub_170B20_00170b20__recomp},
    {"sub_170B90", 0x170B90, &recomp_gen::fn_sub_170B90_00170b90, &recomp_gen::fn_sub_170B90_00170b90__recomp},
    {"sub_170760", 0x170760, &recomp_gen::fn_sub_170760_00170760, &recomp_gen::fn_sub_170760_00170760__recomp},
    {"sub_170860", 0x170860, &recomp_gen::fn_sub_170860_00170860, &recomp_gen::fn_sub_170860_00170860__recomp},
    {"sub_170C00", 0x170C00, &recomp_gen::fn_sub_170C00_00170c00, &recomp_gen::fn_sub_170C00_00170c00__recomp},
    {"sub_171060", 0x171060, &recomp_gen::fn_sub_171060_00171060, &recomp_gen::fn_sub_171060_00171060__recomp},
    {"sub_171110", 0x171110, &recomp_gen::fn_sub_171110_00171110, &recomp_gen::fn_sub_171110_00171110__recomp},
    {"sub_171250", 0x171250, &recomp_gen::fn_sub_171250_00171250, &recomp_gen::fn_sub_171250_00171250__recomp},
    {"sub_171360", 0x171360, &recomp_gen::fn_sub_171360_00171360, &recomp_gen::fn_sub_171360_00171360__recomp},
    {"sub_171390", 0x171390, &recomp_gen::fn_sub_171390_00171390, &recomp_gen::fn_sub_171390_00171390__recomp},
    {"sub_172820", 0x172820, &recomp_gen::fn_sub_172820_00172820, &recomp_gen::fn_sub_172820_00172820__recomp},
    {"sub_172890", 0x172890, &recomp_gen::fn_sub_172890_00172890, &recomp_gen::fn_sub_172890_00172890__recomp},
    {"sub_1728D0", 0x1728D0, &recomp_gen::fn_sub_1728D0_001728d0, &recomp_gen::fn_sub_1728D0_001728d0__recomp},
    {"sub_172990", 0x172990, &recomp_gen::fn_sub_172990_00172990, &recomp_gen::fn_sub_172990_00172990__recomp},
    {"sub_1729A0", 0x1729A0, &recomp_gen::fn_sub_1729A0_001729a0, &recomp_gen::fn_sub_1729A0_001729a0__recomp},
    {"sub_1729D0", 0x1729D0, &recomp_gen::fn_sub_1729D0_001729d0, &recomp_gen::fn_sub_1729D0_001729d0__recomp},
    {"sub_172A10", 0x172A10, &recomp_gen::fn_sub_172A10_00172a10, &recomp_gen::fn_sub_172A10_00172a10__recomp},
    {"sub_172A20", 0x172A20, &recomp_gen::fn_sub_172A20_00172a20, &recomp_gen::fn_sub_172A20_00172a20__recomp},
    {"sub_172A30", 0x172A30, &recomp_gen::fn_sub_172A30_00172a30, &recomp_gen::fn_sub_172A30_00172a30__recomp},
    {"sub_172AB0", 0x172AB0, &recomp_gen::fn_sub_172AB0_00172ab0, &recomp_gen::fn_sub_172AB0_00172ab0__recomp},
    {"sub_172AE0", 0x172AE0, &recomp_gen::fn_sub_172AE0_00172ae0, &recomp_gen::fn_sub_172AE0_00172ae0__recomp},
    {"sub_172B20", 0x172B20, &recomp_gen::fn_sub_172B20_00172b20, &recomp_gen::fn_sub_172B20_00172b20__recomp},
    {"sub_172C50", 0x172C50, &recomp_gen::fn_sub_172C50_00172c50, &recomp_gen::fn_sub_172C50_00172c50__recomp},
    {"sub_172CC0", 0x172CC0, &recomp_gen::fn_sub_172CC0_00172cc0, &recomp_gen::fn_sub_172CC0_00172cc0__recomp},
    {"sub_172D70", 0x172D70, &recomp_gen::fn_sub_172D70_00172d70, &recomp_gen::fn_sub_172D70_00172d70__recomp},
    {"sub_172E10", 0x172E10, &recomp_gen::fn_sub_172E10_00172e10, &recomp_gen::fn_sub_172E10_00172e10__recomp},
    {"sub_172E40", 0x172E40, &recomp_gen::fn_sub_172E40_00172e40, &recomp_gen::fn_sub_172E40_00172e40__recomp},
    {"sub_173280", 0x173280, &recomp_gen::fn_sub_173280_00173280, &recomp_gen::fn_sub_173280_00173280__recomp},
    {"sub_173300", 0x173300, &recomp_gen::fn_sub_173300_00173300, &recomp_gen::fn_sub_173300_00173300__recomp},
    {"sub_173330", 0x173330, &recomp_gen::fn_sub_173330_00173330, &recomp_gen::fn_sub_173330_00173330__recomp},
    {"sub_173340", 0x173340, &recomp_gen::fn_sub_173340_00173340, &recomp_gen::fn_sub_173340_00173340__recomp},
    {"sub_173370", 0x173370, &recomp_gen::fn_sub_173370_00173370, &recomp_gen::fn_sub_173370_00173370__recomp},
    {"sub_173580", 0x173580, &recomp_gen::fn_sub_173580_00173580, &recomp_gen::fn_sub_173580_00173580__recomp},
    {"sub_173660", 0x173660, &recomp_gen::fn_sub_173660_00173660, &recomp_gen::fn_sub_173660_00173660__recomp},
    {"sub_173780", 0x173780, &recomp_gen::fn_sub_173780_00173780, &recomp_gen::fn_sub_173780_00173780__recomp},
    {"sub_173A00", 0x173A00, &recomp_gen::fn_sub_173A00_00173a00, &recomp_gen::fn_sub_173A00_00173a00__recomp},
    {"sub_173B00", 0x173B00, &recomp_gen::fn_sub_173B00_00173b00, &recomp_gen::fn_sub_173B00_00173b00__recomp},
    {"sub_173B60", 0x173B60, &recomp_gen::fn_sub_173B60_00173b60, &recomp_gen::fn_sub_173B60_00173b60__recomp},
    {"sub_173BB0", 0x173BB0, &recomp_gen::fn_sub_173BB0_00173bb0, &recomp_gen::fn_sub_173BB0_00173bb0__recomp},
    {"sub_173C00", 0x173C00, &recomp_gen::fn_sub_173C00_00173c00, &recomp_gen::fn_sub_173C00_00173c00__recomp},
    {"sub_174650", 0x174650, &recomp_gen::fn_sub_174650_00174650, &recomp_gen::fn_sub_174650_00174650__recomp},
    {"sub_174710", 0x174710, &recomp_gen::fn_sub_174710_00174710, &recomp_gen::fn_sub_174710_00174710__recomp},
    {"sub_1748C0", 0x1748C0, &recomp_gen::fn_sub_1748C0_001748c0, &recomp_gen::fn_sub_1748C0_001748c0__recomp},
    {"sub_174960", 0x174960, &recomp_gen::fn_sub_174960_00174960, &recomp_gen::fn_sub_174960_00174960__recomp},
    {"sub_1749A0", 0x1749A0, &recomp_gen::fn_sub_1749A0_001749a0, &recomp_gen::fn_sub_1749A0_001749a0__recomp},
    {"sub_174B40", 0x174B40, &recomp_gen::fn_sub_174B40_00174b40, &recomp_gen::fn_sub_174B40_00174b40__recomp},
    {"sub_174E20", 0x174E20, &recomp_gen::fn_sub_174E20_00174e20, &recomp_gen::fn_sub_174E20_00174e20__recomp},
    {"sub_174E70", 0x174E70, &recomp_gen::fn_sub_174E70_00174e70, &recomp_gen::fn_sub_174E70_00174e70__recomp},
    {"sub_174FB0", 0x174FB0, &recomp_gen::fn_sub_174FB0_00174fb0, &recomp_gen::fn_sub_174FB0_00174fb0__recomp},
    {"sub_175130", 0x175130, &recomp_gen::fn_sub_175130_00175130, &recomp_gen::fn_sub_175130_00175130__recomp},
    {"sub_175200", 0x175200, &recomp_gen::fn_sub_175200_00175200, &recomp_gen::fn_sub_175200_00175200__recomp},
    {"sub_1752B0", 0x1752B0, &recomp_gen::fn_sub_1752B0_001752b0, &recomp_gen::fn_sub_1752B0_001752b0__recomp},
    {"sub_175360", 0x175360, &recomp_gen::fn_sub_175360_00175360, &recomp_gen::fn_sub_175360_00175360__recomp},
    {"sub_1754A0", 0x1754A0, &recomp_gen::fn_sub_1754A0_001754a0, &recomp_gen::fn_sub_1754A0_001754a0__recomp},
    {"sub_1755C0", 0x1755C0, &recomp_gen::fn_sub_1755C0_001755c0, &recomp_gen::fn_sub_1755C0_001755c0__recomp},
    {"sub_1756F0", 0x1756F0, &recomp_gen::fn_sub_1756F0_001756f0, &recomp_gen::fn_sub_1756F0_001756f0__recomp},
    {"sub_1757F0", 0x1757F0, &recomp_gen::fn_sub_1757F0_001757f0, &recomp_gen::fn_sub_1757F0_001757f0__recomp},
    {"sub_175BE0", 0x175BE0, &recomp_gen::fn_sub_175BE0_00175be0, &recomp_gen::fn_sub_175BE0_00175be0__recomp},
    {"sub_175C70", 0x175C70, &recomp_gen::fn_sub_175C70_00175c70, &recomp_gen::fn_sub_175C70_00175c70__recomp},
    {"sub_175CA0", 0x175CA0, &recomp_gen::fn_sub_175CA0_00175ca0, &recomp_gen::fn_sub_175CA0_00175ca0__recomp},
    {"sub_176100", 0x176100, &recomp_gen::fn_sub_176100_00176100, &recomp_gen::fn_sub_176100_00176100__recomp},
    {"sub_1761B0", 0x1761B0, &recomp_gen::fn_sub_1761B0_001761b0, &recomp_gen::fn_sub_1761B0_001761b0__recomp},
};

// The generic sweep's world: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(gamedata): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// =====================================================================================================================
// The real game state
// =====================================================================================================================
namespace {

namespace gd = p3fes::game::gamedata;

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u8 r8(Machine& m, u32 va) { return *m.at(va); }
s8 rs8(Machine& m, u32 va) { return static_cast<s8>(*m.at(va)); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
s16 rs16(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
s32 rs32(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

constexpr u64 S(s64 v) { return static_cast<u64>(v); }
// $v0 of a run as the callers read it: the low 32 bits, signed.
s64 v0_of(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(r.end.gpr[GPR_V0].u64[0])); }

// Free in every replay snapshot (zero in climb_ref_17000, fusion_vr_5000, shop_ref_4100 and dorm_replay_4900).
constexpr u32 kScratch = 0x01BC0000u;
constexpr const char* kSnapshots[] = {"climb_ref_17000", "fusion_vr_5000", "shop_ref_4100", "dorm_replay_4900"};

// One snapshot as the machine; every pair starts from what the previous pairs left (the bodies equal step by step),
// reset() returns to the snapshot.
struct Real {
    Machine& m;
    std::vector<u8> base;
    std::string name;
    int pairs = 0, stops = 0;
    void reset() { std::memcpy(m.mem.main_ram(), base.data(), base.size()); }
    hgp::Run call(const char* fn, Args a, u32 seed = 1) {
        const Case& c = find_case(fn);
        ++pairs;
        hgp::Run r = hgp::pair(m, c.hand, c.recomp, a, seed, (name + " " + fn).c_str());
        if (r.stopped) ++stops;
        return r;
    }
    s64 v0(const char* fn, Args a, u32 seed = 1) { return v0_of(call(fn, a, seed)); }
};

std::unique_ptr<Machine> real_machine(const char* snapshot, std::vector<u8>& base) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    return m;
}

// --- the ids the callers pass ------------------------------------------------------------------------------------
const s64 kPcs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11, -1};
const s64 kComus[] = {0, 1, 2, 5, 9, 14, 20, 29, -1, 30, 31};
const s64 kOwners[] = {-1, 1, 2, 3, 5, 10, 258, 260, 266};
const s64 kItems[] = {4001, 4004, 4009, 4010, 4100, 4200, 4500, 4000, 3999, 0};

std::vector<s64> owner_idx(s64 owner) {
    if (owner == -1) return {0, 1, 5, 19};
    if (owner == 1) return {0, 1, 2, 3, 4, 5, 6, 50, 299};
    return {0, 1, 2, 3};
}
// A persona pointer: the hero's stock slots and the members' record personas.
std::vector<u32> personas() {
    std::vector<u32> v;
    for (u32 s = 0; s < 12; ++s) v.push_back(gd::kHeroPersonaStock + 52 * s);
    for (s32 pc = 2; pc <= 10; ++pc) v.push_back(gd::party_record(pc) + 0xDC);
    return v;
}

// Every function on its real arguments (the order: getters before the setters that change what they read).
void run_all(Real& x) {
    std::mt19937 rng{0x6D47A};
    // party member records
    for (const char* fn : {"sub_16C470", "sub_16C4F0", "sub_16C570", "sub_16C5F0", "sub_16C670", "sub_16C7E0", "sub_16C860",
                           "sub_16C920", "sub_16C970", "sub_16C9F0", "sub_16CA40", "sub_16DD80", "sub_173300"})
        for (s64 pc : kPcs) x.call(fn, {S(pc), 0, 0, 0});
    x.call("sub_16C910", {0, 0, 0, 0});
    for (s64 exp : {0, 19, 20, 47, 1000, 99999, 0x7FFFFFFF, -1}) x.call("sub_16D280", {S(exp), 0, 0, 0});
    for (s64 pc : kPcs) {
        x.call("sub_16CA90", {S(pc), 0, 0, 0});
        x.call("sub_16D560", {S(pc), S(static_cast<s64>(rng() % 500)), 0, 0});
        for (s64 cond : {0, 1, 2, 3, 5, 4, 3}) x.call("sub_16D6B0", {S(pc), S(cond), 0, 0});
        for (const char* fn : {"sub_16CEF0", "sub_16CF40", "sub_16CF90", "sub_16D230", "sub_16D930", "sub_16D980"})
            x.call(fn, {S(pc), S(static_cast<s64>(rng() % 300)), 0, 0});
        for (s64 v : {1, 10, 11, -1}) x.call("sub_16DAD0", {S(pc), S(v), 0, 0});
        for (s64 slot : {0, 1, 2, 3}) x.call("sub_16DA50", {S(pc), S(slot), S(static_cast<s64>(rng() % 4)), 0});
        x.call("sub_16D8B0", {S(pc), 0, 0, 0});
        x.call("sub_16D9D0", {S(pc), 0, 0, 0});
    }
    // social links
    for (const char* fn : {"sub_16DBA0", "sub_16DCE0", "sub_16DD20", "sub_16DF30", "sub_16E100", "sub_16E850", "sub_1717C0",
                           "sub_171AC0", "sub_172160", "sub_172660"})
        for (s64 c : kComus) x.call(fn, {S(c), 0, 0, 0});
    for (s64 a = 0; a <= 23; ++a) x.call("sub_16DEB0", {S(a), 0, 0, 0});
    x.call("sub_16DD40", {0, 0, 0, 0});
    x.call("sub_1717B0", {0, 0, 0, 0});
    for (s64 c : kComus) {
        x.call("sub_1720C0", {S(c), kScratch, 0, 0});
        for (s64 rank : {1, 2, 5, 10, 0, 11, -1}) {
            x.call("sub_1723A0", {S(c), S(rank), S(rank & 1), 0});
            x.call("sub_1724A0", {S(c), S(rank), S((rank >> 1) & 1), 0});
        }
        x.call("sub_172660", {S(c), 0, 0, 0});
        x.call("sub_1725A0", {S(c), 0, 0, 0});
        for (s64 pts : {0, 5, 40, 1000}) x.call("sub_16E2B0", {S(c), S(pts), 0, 0});
        for (s64 v : {-2, 0, 4, 9, 12}) x.call("sub_16E5F0", {S(c), S(v), 0, 0});
        for (s64 v : {-5, 0, 16, 360, 400}) x.call("sub_16E7A0", {S(c), S(v), 0, 0});
        for (s64 on : {1, 1, 0, 2}) {
            x.call("sub_171C40", {S(c), S(on), 0, 0});
            x.call("sub_171F50", {S(c), S(on), 0, 0});
            x.call("sub_172200", {S(c), S(on), 0, 0});
        }
        for (s64 v : {0, 3, 32, 40}) x.call("sub_171E90", {S(c), S(v), 0, 0});
        for (s64 v : {1, 7, 2000}) x.call("sub_171960", {S(c), S(v), 0, 0});
        x.call("sub_1718B0", {S(c), 0, 0, 0});
        x.call("sub_171B50", {S(c), 0, 0, 0});
        x.call("sub_172CC0", {S(c), 0, 0, 0});
        for (s64 rank : {0, 1, 3, 10, 11}) x.call("sub_16E410", {S(c), S(rank), 0, 0});
        x.call("sub_16DFB0", {S(c), 0, 0, 0});
    }
    x.call("sub_172D70", {kScratch, 0, 0, 0});
    for (s64 v : {0, 7, -1}) x.call("sub_16E920", {S(v), 0, 0, 0});
    // money and the party list
    x.call("sub_16DD50", {0, 0, 0, 0});
    for (s64 i : {0, 1, 2, 3}) x.call("sub_16DD60", {S(i), 0, 0, 0});
    for (s64 d : {0, 100, -100, -2000000000, 2000000000, 9999999, -9999999}) {
        x.call("sub_16EA40", {S(d), 0, 0, 0});
        x.call("sub_16E9B0", {S(d), 0, 0, 0});
    }
    for (s64 v : {0, 5000, 9999999, 10000000, -1}) x.call("sub_16E930", {S(v), 0, 0, 0});
    for (s64 i : {0, 1, 2, 3}) x.call("sub_16E990", {S(i), S(static_cast<s64>(2 + rng() % 9)), 0, 0});
    for (s64 i : {0, 3, 7, 8, -1}) {
        x.call("sub_16DE50", {S(i), 0, 0, 0});
        x.call("sub_16DDD0", {S(i), 0, 0, 0});
    }
    // equipment entries
    for (s64 o : {-1, 1, 2, 5, 10, 0, 255, 258, 266, 300}) x.call("sub_16F490", {S(o), 0, 0, 0});
    for (s64 o : kOwners)
        for (s64 i : owner_idx(o)) {
            for (const char* fn : {"sub_16F720", "sub_16F810", "sub_16F9F0", "sub_16FAE0", "sub_16FBD0", "sub_16FCC0", "sub_16FDB0"})
                x.call(fn, {S(o), S(i), 0, 0});
            for (const char* fn : {"sub_16FEA0", "sub_16FF90", "sub_170080", "sub_170170", "sub_170260", "sub_170350", "sub_170440",
                                   "sub_170530"})
                x.call(fn, {S(o), S(i), S(static_cast<s64>(rng() % 0x10000)), 0});
        }
    for (s64 pc = 2; pc <= 10; ++pc)
        for (s64 i : {0, 1, 3, 11}) {
            x.call("sub_170620", {S(pc), S(i), 0, 0});
            x.call("sub_170670", {S(pc), S(i), 0, 0});
            x.call("sub_1706C0", {S(pc), S(i), 0, 0});
            x.call("sub_170710", {S(pc), S(i), S(static_cast<s64>(rng() % 100)), 0});
        }
    for (s64 pc : {2, 5, 10, 258, 266})
        for (s64 i : {0, 1, 19}) {
            x.call("sub_170A40", {S(pc), S(i), 0, 0});
            x.call("sub_170AB0", {S(pc), S(i), 0, 0});
            x.call("sub_170B20", {S(pc), S(i), S(static_cast<s64>(4001 + rng() % 50)), 0});
            x.call("sub_170B90", {S(pc), S(i), S(static_cast<s64>(rng() % 10)), 0});
        }
    // items
    for (s64 o : {-1, 1, 2, 258, 260, 266})
        for (s64 id : kItems) {
            x.call("sub_170760", {S(o), S(id), 0, 0});
            for (s64 d : {1, 5, -3, 120, -200}) x.call("sub_170C00", {S(o), S(id), S(d), 0});
            for (s64 n : {0, 1, 99, 100}) x.call("sub_170860", {S(o), S(id), S(n), 0});
        }
    for (s64 id : {0, 1, 999, 1000, 1999, 2000, 2999, 3000, 3999, 4000, 4999, 5000, 5127, 5128, 6000, 32767, -1}) {
        x.call("sub_171060", {S(id), 0, 0, 0});
        x.call("sub_171250", {S(id), 0, 0, 0});
        x.call("sub_171360", {S(id), 0, 0, 0});
        if (id >= 0 && id < 6000)
            for (s64 col : {0, 1, 4}) x.call("sub_171110", {S(id), S(col), 0, 0});
    }
    for (s64 id : {5000, 5001, 5063, 5127, 4999, 5128}) x.call("sub_171390", {S(id), 0, 0, 0});
    // day-event records
    for (s64 i = 0; i < 56; ++i) *x.m.at(kScratch + 0x100 + static_cast<u32>(i)) = static_cast<u8>(i * 7 + 3);
    *x.m.at(kScratch + 0x100 + 4) = 3;
    *x.m.at(kScratch + 0x100 + 0x24) = 0xFF;
    for (int k = 0; k < 2; ++k) {
        x.call("sub_1729A0", {0, 0, 0, 0});
        x.call("sub_172990", {0, 0, 0, 0});
        x.call("sub_1729D0", {kScratch, 0, 0, 0});
        x.call("sub_172A10", {0, 0, 0, 0});
        x.call("sub_172A30", {0, 0, 0, 0});
        x.call("sub_172C50", {kScratch, 0, 0, 0});
        x.call("sub_172B20", {0, 0, 0, 0});
        x.call("sub_1728D0", {kScratch + 0x100, 0, 0, 0});
        for (s64 v : {0, 1, 2}) x.call("sub_172A20", {S(v), 0, 0, 0});
        x.call("sub_172A30", {0, 0, 0, 0});
        x.call("sub_1729D0", {kScratch, 0, 0, 0});
        x.call("sub_172AB0", {S(static_cast<s64>(rng() % 30)), 0, 0, 0});
        x.call("sub_172820", {S(static_cast<s64>(rng() % 6)), 0, 0, 0});
        x.call("sub_172E40", {0, 0, 0, 0});
        x.call("sub_172E10", {0, 0, 0, 0});
        x.call("sub_172890", {0, 0, 0, 0});
        x.call("sub_172AE0", {0, 0, 0, 0});
        *x.m.at(kScratch + 0x100 + 0x24) = 2;
    }
    // persona stock and personas
    for (u32 p : personas()) {
        for (const char* fn : {"sub_173330", "sub_173340", "sub_173370", "sub_175CA0", "sub_1761B0"}) x.call(fn, {p, 0, 0, 0});
        for (s64 st : {0, 1, 2, 3, 4, 5}) {
            for (const char* fn : {"sub_173580", "sub_173660", "sub_173A00", "sub_173B00", "sub_173C00"}) x.call(fn, {p, S(st), 0, 0});
            x.call("sub_174650", {p, S(st), S(static_cast<s64>(rng() % 7) - 3), 0});
        }
    }
    for (s64 id : {0, 1, 46, 100, 192, 255, 256, 300}) x.call("sub_173280", {S(id), 0, 0, 0});
    for (s64 pc : kPcs)
        for (s64 st : {0, 4}) {
            x.call("sub_173B60", {S(pc), S(st), S(static_cast<s64>(rng() % 5)), 0});
            x.call("sub_173BB0", {S(pc), S(st), 1, 0});
        }
    for (s64 slot : {0, 1, 2, 5, 11, -1, 12}) {
        x.call("sub_174960", {S(slot), 0, 0, 0});
        for (s64 st : {0, 4}) {
            x.call("sub_173780", {S(slot), S(st), 0, 0});
            x.call("sub_174710", {S(slot), S(st), 1, 0});
        }
    }
    x.call("sub_1748C0", {0, 0, 0, 0});
    x.call("sub_1756F0", {0, 0, 0, 0});
    x.call("sub_1755C0", {0, 0, 0, 0});
    x.call("sub_1752B0", {0, 0, 0, 0});
    x.call("sub_175360", {0, 0, 0, 0});
    // the held ids (and some that are not)
    std::vector<s64> ids = {0, 1, 2, 46, 255};
    for (u32 s = 0; s < 12; ++s)
        if (r16(x.m, gd::kHeroPersonaStock + 52 * s) & 1) ids.push_back(r16(x.m, gd::kHeroPersonaStock + 52 * s + 2));
    for (s64 id : ids) {
        x.call("sub_1749A0", {S(id), 0, 0, 0});
        x.call("sub_175130", {S(id), 0, 0, 0});
    }
    for (s64 slot : {0, 1, 11, 12, -1}) x.call("sub_175200", {S(slot), 0, 0, 0});
    // a level-up record for sub_176100
    std::memset(x.m.at(kScratch + 0x200), 0, 40);
    *x.m.at(kScratch + 0x200) = 2;
    for (u32 i = 0; i < 5; ++i) *x.m.at(kScratch + 0x200 + 34 + i) = static_cast<u8>(i);
    for (u32 p : personas()) x.call("sub_176100", {p, kScratch + 0x200, 0, 0});
    // the stock-size levels
    for (s64 lv : {0, 1, 2, 3, 4, 5, 6, -1, 4}) {
        x.call("sub_1754A0", {S(lv), 0, 0, 0});
        x.call("sub_1755C0", {0, 0, 0, 0});
        x.call("sub_1756F0", {0, 0, 0, 0});
    }
    // fills and removals: a copy of slot 0 (or an empty record), new personas, the removals
    std::memcpy(x.m.at(kScratch + 0x300), x.m.at(gd::kHeroPersonaStock), 52);
    for (int k = 0; k < 3; ++k) x.call("sub_174FB0", {kScratch + 0x300, 0, 0, 0});
    for (s64 id : {1, 46, 120}) {
        x.call("sub_174E70", {S(id), 0, 0, 0});
        x.call("sub_174E20", {S(id), 0, 0, 0});
    }
    for (s64 id : ids) x.call("sub_174B40", {S(id), 0, 0, 0});
    for (s64 pc : {2, 1}) x.call("sub_175BE0", {S(pc), 0, 0, 0});
    x.call("sub_1757F0", {0, 0, 0, 0});
    x.call("sub_175C70", {0, 0, 0, 0});
    x.call("sub_16DB70", {0, 0, 0, 0});
    for (s64 pc : kPcs) x.call("sub_16CDF0", {S(pc), 0, 0, 0});
}

}  // namespace

TEST_CASE("game(gamedata): every body equals its recompiled body on the replay snapshots' game state") {
    int machines = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto m = real_machine(snap, base);
        if (!m) {
            MESSAGE("SKIP: " << std::string(snap) << " (no ELF or no extracted/_ours/" << snap << "/eeMemory.bin)");
            continue;
        }
        ++machines;
        Real x{*m, std::move(base), snap};
        run_all(x);
        MESSAGE(std::string(snap) << ": " << x.pairs << " pairs, " << x.stops << " stopped early (a callee not in this build)");
    }
    if (machines == 0) MESSAGE("SKIP: no replay snapshot");
}

TEST_CASE("game(gamedata): documented rules on the replay snapshots' records") {
    int checked = 0;
    for (const char* snap : kSnapshots) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        Real x{m, std::move(base), snap};
        INFO(std::string(snap));
        // --- money (gGlobalWork +0x44DC): the getter, the clamped add, the range check -------------------------------
        const s32 money = rs32(m, gd::kMoney);
        CHECK(x.v0("sub_16DD50", {0, 0, 0, 0}) == money);
        for (s64 d : {0, 1, -1, 12345, -2000000000, 2000000000}) {
            x.reset();
            const s64 sum = static_cast<s32>(static_cast<u32>(money) + static_cast<u32>(d));  // addu: 32-bit
            const s64 want = sum >= gd::kMoneyLimit ? gd::kMoneyMax : (sum < 0 ? 0 : sum);
            CHECK(x.v0("sub_16EA40", {S(d), 0, 0, 0}) == (sum >= gd::kMoneyLimit ? 1 : (sum < 0 ? -1 : 0)));
            CHECK(x.v0("sub_16E9B0", {S(d), 0, 0, 0}) == want);
            CHECK(rs32(m, gd::kMoney) == want);
        }
        x.reset();
        x.call("sub_16E930", {S(4321), 0, 0, 0});
        CHECK(rs32(m, gd::kMoney) == 4321);
        // --- the party list --------------------------------------------------------------------------------------------
        for (s64 i = 0; i < 4; ++i) CHECK(x.v0("sub_16DD60", {S(i), 0, 0, 0}) == rs16(m, gd::kParty + 2 * static_cast<u32>(i)));
        x.call("sub_16E990", {S(3), S(7), 0, 0});
        CHECK(rs16(m, gd::kParty + 6) == 7);
        // --- the hero's and the members' records ------------------------------------------------------------------------
        x.reset();
        CHECK(x.v0("sub_16C920", {1, 0, 0, 0}) == r16(m, gd::kHeroCondition));
        CHECK(x.v0("sub_16C7E0", {1, 0, 0, 0}) == rs32(m, gd::kHeroExp));
        for (s32 pc = 2; pc <= 10; ++pc) {
            CHECK(x.v0("sub_16C920", {S(pc), 0, 0, 0}) == r16(m, gd::party_record(pc) + 0x4C));
            CHECK(x.v0("sub_16C9F0", {S(pc), 0, 0, 0}) == r16(m, gd::party_record(pc) + 0x4E));
            CHECK(x.v0("sub_16CA40", {S(pc), 0, 0, 0}) == r16(m, gd::party_record(pc) + 0x50));
            CHECK(x.v0("sub_16DD80", {S(pc), 0, 0, 0}) == rs8(m, gd::party_record(pc) + 4 + 0x10));
            // a member's exp is its persona's (record + 0xDC, +8)
            CHECK(x.v0("sub_16C7E0", {S(pc), 0, 0, 0}) == rs32(m, gd::party_record(pc) + 0xDC + 8));
            CHECK(x.v0("sub_16C860", {S(pc), 0, 0, 0}) == r16(m, gd::party_record(pc) + 0xDC + 2));
            x.call("sub_16CF40", {S(pc), S(123), 0, 0});
            CHECK(r16(m, gd::party_record(pc) + 4 + 8) == 123);  // unit.hp
            x.call("sub_16CF90", {S(pc), S(45), 0, 0});
            CHECK(r16(m, gd::party_record(pc) + 4 + 10) == 45);  // unit.sp
        }
        // the exp table level (sub_16D280) on the hero's table
        {
            std::vector<s32> table(99);
            for (u32 i = 0; i < 99; ++i) table[i] = rs32(m, gd::kHeroExpTable + 4 * i);
            CHECK(std::is_sorted(table.begin(), table.end()));
            for (s64 exp : {s64{0}, s64{table[1]} - 1, s64{table[1]}, s64{table[10]}, s64{table[98]}, s64{0x7FFFFFFF}}) {
                s64 want = 0;
                while (want < 99 && exp >= table[static_cast<std::size_t>(want)]) ++want;
                CHECK(x.v0("sub_16D280", {S(exp), 0, 0, 0}) == want);
            }
        }
        // the condition setter: counter pc + 15 follows the new condition (sub_16F3E0 = kCounters[i])
        x.reset();
        for (const auto& [cond, counter] : std::vector<std::pair<s64, s64>>{{5, 60}, {3, 50}, {0, 0}, {2, 1}}) {
            x.call("sub_16D6B0", {S(3), S(cond), 0, 0});
            CHECK(r16(m, gd::party_record(3) + 0x4C) == cond);
            CHECK(rs32(m, 0x83A4DCu + 4 * (3 + 15)) == counter);
        }
        // --- social links -----------------------------------------------------------------------------------------------
        x.reset();
        for (s64 c = 0; c < gd::kComuCount; ++c) {
            const s8 rank = rs8(m, gd::kComuRank + static_cast<u32>(c));
            CHECK(x.v0("sub_16DBA0", {S(c), 0, 0, 0}) == rank);
            CHECK(x.v0("sub_16E100", {S(c), 0, 0, 0}) == (rank > 0 ? 1 : 0));
            CHECK(x.v0("sub_16DF30", {S(c), 0, 0, 0}) == rs8(m, gd::kComuArcana + static_cast<u32>(c)));
            CHECK(x.v0("sub_16DCE0", {S(c), 0, 0, 0}) == 1);
        }
        CHECK(x.v0("sub_16DCE0", {S(30), 0, 0, 0}) == 0);
        CHECK(x.v0("sub_16DCE0", {S(-1), 0, 0, 0}) == 0);
        for (s64 a = 0; a <= 22; ++a) {  // the highest-ranked link of an arcana (first on a tie), -1 when none
            s64 want = -1, best = -1;
            for (s64 c = 0; c < gd::kComuCount; ++c) {
                const s64 rank = rs8(m, gd::kComuRank + static_cast<u32>(c));
                if (rs8(m, gd::kComuArcana + static_cast<u32>(c)) == a && best < rank) {
                    want = c;
                    best = rank;
                }
            }
            CHECK(x.v0("sub_16DEB0", {S(a), 0, 0, 0}) == want);
        }
        // the rank bits: set 'ready' for rank 3 of link 7, then it is pending until 'seen' is set
        x.reset();
        for (s64 r = 1; r <= 10; ++r) {
            x.call("sub_1723A0", {7, S(r), 0, 0});
            x.call("sub_1724A0", {7, S(r), 0, 0});
        }
        CHECK(x.v0("sub_172660", {7, 0, 0, 0}) == 0);
        x.call("sub_1723A0", {7, 3, 1, 0});
        CHECK(x.v0("sub_172660", {7, 0, 0, 0}) == 1);
        x.call("sub_1724A0", {7, 3, 1, 0});
        CHECK(x.v0("sub_172660", {7, 0, 0, 0}) == 0);
        // comu_b stays in 0..9; the day stamp in 0..360
        for (const auto& [v, want] : std::vector<std::pair<s64, s64>>{{-3, 0}, {4, 4}, {12, 9}}) {
            x.call("sub_16E5F0", {2, S(v), 0, 0});
            CHECK(rs8(m, gd::kComuB + 2) == want);
        }
        for (const auto& [v, want] : std::vector<std::pair<s64, s64>>{{-3, 0}, {45, 45}, {999, 360}}) {
            x.call("sub_16E7A0", {2, S(v), 0, 0});
            CHECK(rs16(m, gd::kComuDay + 4) == want);
        }
        // --- items ------------------------------------------------------------------------------------------------------
        x.reset();
        const u32 counts = r32(m, gd::kHeroItemNum);
        for (s64 id : {4001, 4004, 4009, 4010, 4100}) {
            const u16 have = r16(m, counts + 2 * static_cast<u32>(id - 4000));
            CHECK(x.v0("sub_170760", {1, S(id), 0, 0}) == have);
            for (s64 d : {1, -1, 200, -200}) {
                x.reset();
                const s64 want = std::clamp<s64>(s64{have} + d, 0, gd::kItemMax);
                CHECK(x.v0("sub_170C00", {1, S(id), S(d), 0}) == want);
                CHECK(r16(m, counts + 2 * static_cast<u32>(id - 4000)) == want);
            }
        }
        x.reset();
        x.call("sub_170860", {S(-1), 4007, 12, 0});
        CHECK(r16(m, gd::kTempItemNum + 2 * 4007) == 12);
        CHECK(x.v0("sub_170760", {S(-1), 4007, 0, 0}) == 12);
        CHECK(x.v0("sub_170760", {S(5), 4007, 0, 0}) == 0);  // a member holds no counted items
        for (s64 id : {0, 999, 1000, 2500, 3999, 4000, 4321, 5000, 5127, 5999}) {
            CHECK(x.v0("sub_171250", {S(id), 0, 0, 0}) == std::min<s64>(id / 1000, 4));
            CHECK(x.v0("sub_171060", {S(id), 0, 0, 0}) == id % 1000);
            CHECK(x.v0("sub_171360", {S(id), 0, 0, 0}) == (id >= 5000 && id < 5128 ? 1 : 0));
        }
        // a key item is a flag bit: datSetFlag(id - 0x1188)
        x.reset();
        x.call("sub_171390", {S(5010), 0, 0, 0});
        {
            const u32 flag = 5010 - 0x1188;
            CHECK((r32(m, 0x83A21Cu + 4 * (flag / 32)) >> (flag % 32) & 1) == 1);
        }
        // --- equipment entries ------------------------------------------------------------------------------------------
        x.reset();
        {
            const u32 stock = r32(m, gd::kHeroEquipmentStock);
            s64 used = 0;
            for (u32 i = 0; i < 300; ++i) used += r16(m, stock + 20 * i) != 0 ? 1 : 0;
            CHECK(x.v0("sub_16F490", {1, 0, 0, 0}) == used);
            for (s64 i : {0, 1, 2, 3}) {
                const u32 e = stock + 20 * static_cast<u32>(i);
                CHECK(x.v0("sub_16FDB0", {1, S(i), 0, 0}) == static_cast<s32>(e));
                CHECK(x.v0("sub_16F720", {1, S(i), 0, 0}) == rs32(m, e + 4));
                CHECK(x.v0("sub_16F810", {1, S(i), 0, 0}) == r8(m, e + 8));
                CHECK(x.v0("sub_16F9F0", {1, S(i), 0, 0}) == r16(m, e + 0xA));
                CHECK(x.v0("sub_16FAE0", {1, S(i), 0, 0}) == r16(m, e + 0xC));
                CHECK(x.v0("sub_16FBD0", {1, S(i), 0, 0}) == r16(m, e + 0xE));
                CHECK(x.v0("sub_16FCC0", {1, S(i), 0, 0}) == r16(m, e + 0x10));
            }
            for (s32 pc = 2; pc <= 10; ++pc) {
                s64 n = 0;
                for (u32 i = 0; i < 4; ++i) n += r16(m, gd::party_record(pc) + 0x5C + 20 * i) != 0 ? 1 : 0;
                CHECK(x.v0("sub_16F490", {S(pc), 0, 0, 0}) == n);
                CHECK(x.v0("sub_16FDB0", {S(pc), 2, 0, 0}) == static_cast<s32>(gd::party_record(pc) + 0x5C + 40));
                CHECK(x.v0("sub_16FDB0", {S(pc + 256), 1, 0, 0}) == static_cast<s32>(gd::party_record(pc) + 0x180 + 20));
            }
            x.call("sub_170260", {S(4), 1, 77, 0});
            CHECK(r16(m, gd::party_record(4) + 0x5C + 20 + 0xA) == 77);
            CHECK(x.v0("sub_16F9F0", {S(4), 1, 0, 0}) == 77);
        }
        // --- the persona stock -------------------------------------------------------------------------------------------
        x.reset();
        {
            const u32 flags = r32(m, gd::kPersonaStockFlags);
            const s64 size = flags & 4 ? 12 : flags & 2 ? 10 : flags & 1 ? 9 : flags & 0x2000 ? 8 : flags & 0x1000 ? 6 : 4;
            static const s64 kSizes[] = {4, 6, 8, 9, 10, 12};
            const s64 want_level = std::find(std::begin(kSizes), std::end(kSizes), size) - std::begin(kSizes);
            CHECK(x.v0("sub_1755C0", {0, 0, 0, 0}) == want_level);
            s64 used = 0, first_free = -1;
            for (s64 s = 0; s < size; ++s) {
                const bool u = (r16(m, gd::kHeroPersonaStock + 52 * static_cast<u32>(s)) & 1) != 0;
                used += u ? 1 : 0;
                if (!u && first_free < 0) first_free = s;
            }
            CHECK(x.v0("sub_1756F0", {0, 0, 0, 0}) == used);
            CHECK(x.v0("sub_1748C0", {0, 0, 0, 0}) == first_free);
            for (s64 s = 0; s < 12; ++s) {
                const u32 p = gd::kHeroPersonaStock + 52 * static_cast<u32>(s);
                CHECK(x.v0("sub_174960", {S(s), 0, 0, 0}) == (r16(m, p) & 1));
                if (s < size && (r16(m, p) & 1)) {
                    CHECK(x.v0("sub_1749A0", {r16(m, p + 2), 0, 0, 0}) == static_cast<s32>(p));
                    CHECK(x.v0("sub_173330", {p, 0, 0, 0}) == rs32(m, p + 8));
                    for (s64 st = 0; st < 5; ++st) {
                        const s64 sum = s64{r8(m, p + 0x1C + static_cast<u32>(st))} + rs8(m, p + 0x21 + static_cast<u32>(st)) +
                                        rs8(m, p + 0x26 + static_cast<u32>(st));
                        CHECK(x.v0("sub_173A00", {p, S(st), 0, 0}) == std::min<s64>(sum, 99));
                    }
                }
            }
            const s16 cur = rs16(m, gd::kHeroPersonaIdx);
            if (cur >= 0 && cur < size && (r16(m, gd::kHeroPersonaStock + 52 * static_cast<u32>(cur)) & 1)) {
                CHECK(x.v0("sub_175360", {0, 0, 0, 0}) == cur);
                CHECK(x.v0("sub_1752B0", {0, 0, 0, 0}) == r16(m, gd::kHeroPersonaStock + 52 * static_cast<u32>(cur) + 2));
                CHECK(x.v0("sub_16C860", {1, 0, 0, 0}) == r16(m, gd::kHeroPersonaStock + 52 * static_cast<u32>(cur) + 2));
            }
            CHECK(x.v0("sub_1749A0", {S(255), 0, 0, 0}) == 0);  // persona 255 is never held in these snapshots
            // the arcana of persona ids in the 14-byte table
            const u32 table = r32(m, gd::kPersonaTable);
            for (s64 id : {1, 2, 46, 100, 200}) CHECK(x.v0("sub_173280", {S(id), 0, 0, 0}) == r8(m, table + 14 * static_cast<u32>(id) + 2));
        }
        // the stock level setter and getter are inverse (and the size follows)
        for (s64 lv = 0; lv <= 5; ++lv) {
            x.call("sub_1754A0", {S(lv), 0, 0, 0});
            CHECK(x.v0("sub_1755C0", {0, 0, 0, 0}) == lv);
        }
        // the party-persona id range
        x.reset();
        std::memset(m.at(kScratch + 0x400), 0, 52);
        for (const auto& [id, want] : std::vector<std::pair<s64, s64>>{{0xBF, 0}, {0xC0, 1}, {0xDF, 1}, {0xE0, 0}, {1, 0}}) {
            const u16 id16 = static_cast<u16>(id);
            std::memcpy(m.at(kScratch + 0x400 + 2), &id16, 2);
            CHECK(x.v0("sub_175CA0", {kScratch + 0x400, 0, 0, 0}) == want);
        }
        ++checked;
        MESSAGE(std::string(snap) << ": rules checked on " << x.pairs << " pairs");
    }
    if (checked == 0) MESSAGE("SKIP: no replay snapshot");
}

// sub_16E670 on a link without a rank prints "no exist comu %s %d" (g_data.c, line 1568) through printf: paired on the
// printf stand-in (stand_ins.h), the text compared in both call logs.
TEST_CASE("game(gamedata): sub_16E670's 'no exist comu' message on the printf stand-in") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
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
    const Case& c = find_case("sub_16E670");
    int printed = 0, bumped = 0;
    for (s64 comu = 0; comu < gd::kComuCount; ++comu) {
        const s8 rank = rs8(m, gd::kComuRank + static_cast<u32>(comu));
        const s8 before = rs8(m, gd::kComuB + static_cast<u32>(comu));
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {S(comu), 0, 0, 0}, static_cast<u32>(comu) + 1, "sub_16E670", hw);
        const auto& log = sp.recomp->si.log;
        if (rank > 0) {
            CHECK(log.empty());
            CHECK(rs8(m, gd::kComuB + static_cast<u32>(comu)) == std::min<s8>(static_cast<s8>(before + 1), 9));
            ++bumped;
        } else {
            REQUIRE(log.size() == 1);
            CHECK(log[0].text == "no exist comu g_data.c 1568");
            ++printed;
        }
    }
    MESSAGE("sub_16E670: " << printed << " messages, " << bumped << " bumps");
}

#else

TEST_CASE("game(gamedata): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
