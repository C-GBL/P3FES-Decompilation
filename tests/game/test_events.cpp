// Pair tests for slice events (game/src/event/events.cpp): the story-event player against its recompiled bodies. Every
// pair compares the whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and the cycle count at every check
// point and at the return, all 32 MiB of RAM (write-tracked) including the dead stack, the scratchpad, the bus log and,
// with stand-ins (stand_ins.h), every call the bodies make to a function this test library does not emit: its address,
// $ra, arguments and entry check point (a recorder each; printf / sprintf / the heap stand in as usual).
//   * random worlds: every body on p3fes_handgen's random worlds (runs that reach a missing callee stop identically);
//   * the unit / key lists: sorted insertion by frame (sub_361140), unlinking (sub_361200), the re-sort pass
//     (sub_361270), units by type rank (sub_361B60) -- the order and the links checked on the host after each pair;
//   * documented rules: the key conditions of sub_360ED0 (always / counter / flag bank / invalid -> cleared), the
//     unit-type table and its cache (sub_36F500), the work getters and setters, the event counters, the field-resume
//     pair, the clamp of sub_38A480, the name table of sub_361FE0;
//   * real game data: the live opening event of the dorm route (E401_002) in two snapshots taken during it
//     (extracted/_ours/events_dorm_2100 and events_dorm_2300; skipped when absent): the record layouts checked against
//     the data (units in rank order, frame-sorted keys, counts), then the counting helpers, every key's condition, every
//     unit's current key, all per-frame appliers on every model unit and every work-level step at the start, current,
//     next, last and message-key frames, with the actor lookups answering "none" and "present".
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/events.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
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
void fn_sub_360110_00360110(EEContext&);  // generated body
void fn_sub_360110_00360110__recomp(EEContext&);  // recompiled
void fn_sub_3604A0_003604a0(EEContext&);  // generated body
void fn_sub_3604A0_003604a0__recomp(EEContext&);  // recompiled
void fn_sub_360570_00360570(EEContext&);  // generated body
void fn_sub_360570_00360570__recomp(EEContext&);  // recompiled
void fn_sub_360640_00360640(EEContext&);  // generated body
void fn_sub_360640_00360640__recomp(EEContext&);  // recompiled
void fn_sub_3606F0_003606f0(EEContext&);  // generated body
void fn_sub_3606F0_003606f0__recomp(EEContext&);  // recompiled
void fn_sub_3607A0_003607a0(EEContext&);  // generated body
void fn_sub_3607A0_003607a0__recomp(EEContext&);  // recompiled
void fn_sub_3608E0_003608e0(EEContext&);  // generated body
void fn_sub_3608E0_003608e0__recomp(EEContext&);  // recompiled
void fn_sub_360990_00360990(EEContext&);  // generated body
void fn_sub_360990_00360990__recomp(EEContext&);  // recompiled
void fn_sub_360A40_00360a40(EEContext&);  // generated body
void fn_sub_360A40_00360a40__recomp(EEContext&);  // recompiled
void fn_sub_360AB0_00360ab0(EEContext&);  // generated body
void fn_sub_360AB0_00360ab0__recomp(EEContext&);  // recompiled
void fn_sub_360B00_00360b00(EEContext&);  // generated body
void fn_sub_360B00_00360b00__recomp(EEContext&);  // recompiled
void fn_sub_360B70_00360b70(EEContext&);  // generated body
void fn_sub_360B70_00360b70__recomp(EEContext&);  // recompiled
void fn_sub_360C50_00360c50(EEContext&);  // generated body
void fn_sub_360C50_00360c50__recomp(EEContext&);  // recompiled
void fn_sub_360CF0_00360cf0(EEContext&);  // generated body
void fn_sub_360CF0_00360cf0__recomp(EEContext&);  // recompiled
void fn_sub_360D40_00360d40(EEContext&);  // generated body
void fn_sub_360D40_00360d40__recomp(EEContext&);  // recompiled
void fn_sub_360ED0_00360ed0(EEContext&);  // generated body
void fn_sub_360ED0_00360ed0__recomp(EEContext&);  // recompiled
void fn_sub_361050_00361050(EEContext&);  // generated body
void fn_sub_361050_00361050__recomp(EEContext&);  // recompiled
void fn_sub_361070_00361070(EEContext&);  // generated body
void fn_sub_361070_00361070__recomp(EEContext&);  // recompiled
void fn_sub_361140_00361140(EEContext&);  // generated body
void fn_sub_361140_00361140__recomp(EEContext&);  // recompiled
void fn_sub_361200_00361200(EEContext&);  // generated body
void fn_sub_361200_00361200__recomp(EEContext&);  // recompiled
void fn_sub_361270_00361270(EEContext&);  // generated body
void fn_sub_361270_00361270__recomp(EEContext&);  // recompiled
void fn_sub_361350_00361350(EEContext&);  // generated body
void fn_sub_361350_00361350__recomp(EEContext&);  // recompiled
void fn_sub_361830_00361830(EEContext&);  // generated body
void fn_sub_361830_00361830__recomp(EEContext&);  // recompiled
void fn_sub_361890_00361890(EEContext&);  // generated body
void fn_sub_361890_00361890__recomp(EEContext&);  // recompiled
void fn_sub_361B60_00361b60(EEContext&);  // generated body
void fn_sub_361B60_00361b60__recomp(EEContext&);  // recompiled
void fn_sub_361C30_00361c30(EEContext&);  // generated body
void fn_sub_361C30_00361c30__recomp(EEContext&);  // recompiled
void fn_sub_361CA0_00361ca0(EEContext&);  // generated body
void fn_sub_361CA0_00361ca0__recomp(EEContext&);  // recompiled
void fn_sub_361D60_00361d60(EEContext&);  // generated body
void fn_sub_361D60_00361d60__recomp(EEContext&);  // recompiled
void fn_sub_361DD0_00361dd0(EEContext&);  // generated body
void fn_sub_361DD0_00361dd0__recomp(EEContext&);  // recompiled
void fn_sub_361EE0_00361ee0(EEContext&);  // generated body
void fn_sub_361EE0_00361ee0__recomp(EEContext&);  // recompiled
void fn_sub_361F20_00361f20(EEContext&);  // generated body
void fn_sub_361F20_00361f20__recomp(EEContext&);  // recompiled
void fn_sub_361F60_00361f60(EEContext&);  // generated body
void fn_sub_361F60_00361f60__recomp(EEContext&);  // recompiled
void fn_sub_361FE0_00361fe0(EEContext&);  // generated body
void fn_sub_361FE0_00361fe0__recomp(EEContext&);  // recompiled
void fn_nullsub_114_00362100(EEContext&);  // generated body
void fn_nullsub_114_00362100__recomp(EEContext&);  // recompiled
void fn_nullsub_115_00362110(EEContext&);  // generated body
void fn_nullsub_115_00362110__recomp(EEContext&);  // recompiled
void fn_sub_362120_00362120(EEContext&);  // generated body
void fn_sub_362120_00362120__recomp(EEContext&);  // recompiled
void fn_sub_362240_00362240(EEContext&);  // generated body
void fn_sub_362240_00362240__recomp(EEContext&);  // recompiled
void fn_sub_362290_00362290(EEContext&);  // generated body
void fn_sub_362290_00362290__recomp(EEContext&);  // recompiled
void fn_sub_362310_00362310(EEContext&);  // generated body
void fn_sub_362310_00362310__recomp(EEContext&);  // recompiled
void fn_sub_362F20_00362f20(EEContext&);  // generated body
void fn_sub_362F20_00362f20__recomp(EEContext&);  // recompiled
void fn_sub_362FA0_00362fa0(EEContext&);  // generated body
void fn_sub_362FA0_00362fa0__recomp(EEContext&);  // recompiled
void fn_sub_362FF0_00362ff0(EEContext&);  // generated body
void fn_sub_362FF0_00362ff0__recomp(EEContext&);  // recompiled
void fn_sub_363030_00363030(EEContext&);  // generated body
void fn_sub_363030_00363030__recomp(EEContext&);  // recompiled
void fn_sub_3638E0_003638e0(EEContext&);  // generated body
void fn_sub_3638E0_003638e0__recomp(EEContext&);  // recompiled
void fn_sub_364470_00364470(EEContext&);  // generated body
void fn_sub_364470_00364470__recomp(EEContext&);  // recompiled
void fn_sub_3645C0_003645c0(EEContext&);  // generated body
void fn_sub_3645C0_003645c0__recomp(EEContext&);  // recompiled
void fn_sub_3646D0_003646d0(EEContext&);  // generated body
void fn_sub_3646D0_003646d0__recomp(EEContext&);  // recompiled
void fn_sub_3648E0_003648e0(EEContext&);  // generated body
void fn_sub_3648E0_003648e0__recomp(EEContext&);  // recompiled
void fn_sub_364A30_00364a30(EEContext&);  // generated body
void fn_sub_364A30_00364a30__recomp(EEContext&);  // recompiled
void fn_sub_364B10_00364b10(EEContext&);  // generated body
void fn_sub_364B10_00364b10__recomp(EEContext&);  // recompiled
void fn_sub_364E40_00364e40(EEContext&);  // generated body
void fn_sub_364E40_00364e40__recomp(EEContext&);  // recompiled
void fn_sub_3650C0_003650c0(EEContext&);  // generated body
void fn_sub_3650C0_003650c0__recomp(EEContext&);  // recompiled
void fn_sub_365250_00365250(EEContext&);  // generated body
void fn_sub_365250_00365250__recomp(EEContext&);  // recompiled
void fn_sub_365360_00365360(EEContext&);  // generated body
void fn_sub_365360_00365360__recomp(EEContext&);  // recompiled
void fn_sub_365430_00365430(EEContext&);  // generated body
void fn_sub_365430_00365430__recomp(EEContext&);  // recompiled
void fn_sub_3655F0_003655f0(EEContext&);  // generated body
void fn_sub_3655F0_003655f0__recomp(EEContext&);  // recompiled
void fn_sub_3657E0_003657e0(EEContext&);  // generated body
void fn_sub_3657E0_003657e0__recomp(EEContext&);  // recompiled
void fn_sub_3658B0_003658b0(EEContext&);  // generated body
void fn_sub_3658B0_003658b0__recomp(EEContext&);  // recompiled
void fn_sub_365A40_00365a40(EEContext&);  // generated body
void fn_sub_365A40_00365a40__recomp(EEContext&);  // recompiled
void fn_sub_365B70_00365b70(EEContext&);  // generated body
void fn_sub_365B70_00365b70__recomp(EEContext&);  // recompiled
void fn_sub_365CD0_00365cd0(EEContext&);  // generated body
void fn_sub_365CD0_00365cd0__recomp(EEContext&);  // recompiled
void fn_sub_365F80_00365f80(EEContext&);  // generated body
void fn_sub_365F80_00365f80__recomp(EEContext&);  // recompiled
void fn_sub_366210_00366210(EEContext&);  // generated body
void fn_sub_366210_00366210__recomp(EEContext&);  // recompiled
void fn_sub_366330_00366330(EEContext&);  // generated body
void fn_sub_366330_00366330__recomp(EEContext&);  // recompiled
void fn_sub_3663F0_003663f0(EEContext&);  // generated body
void fn_sub_3663F0_003663f0__recomp(EEContext&);  // recompiled
void fn_sub_366540_00366540(EEContext&);  // generated body
void fn_sub_366540_00366540__recomp(EEContext&);  // recompiled
void fn_sub_366660_00366660(EEContext&);  // generated body
void fn_sub_366660_00366660__recomp(EEContext&);  // recompiled
void fn_sub_366970_00366970(EEContext&);  // generated body
void fn_sub_366970_00366970__recomp(EEContext&);  // recompiled
void fn_sub_366AC0_00366ac0(EEContext&);  // generated body
void fn_sub_366AC0_00366ac0__recomp(EEContext&);  // recompiled
void fn_sub_36D030_0036d030(EEContext&);  // generated body
void fn_sub_36D030_0036d030__recomp(EEContext&);  // recompiled
void fn_sub_36D320_0036d320(EEContext&);  // generated body
void fn_sub_36D320_0036d320__recomp(EEContext&);  // recompiled
void fn_sub_36D470_0036d470(EEContext&);  // generated body
void fn_sub_36D470_0036d470__recomp(EEContext&);  // recompiled
void fn_sub_36D500_0036d500(EEContext&);  // generated body
void fn_sub_36D500_0036d500__recomp(EEContext&);  // recompiled
void fn_sub_36DA10_0036da10(EEContext&);  // generated body
void fn_sub_36DA10_0036da10__recomp(EEContext&);  // recompiled
void fn_sub_36DB20_0036db20(EEContext&);  // generated body
void fn_sub_36DB20_0036db20__recomp(EEContext&);  // recompiled
void fn_sub_36E140_0036e140(EEContext&);  // generated body
void fn_sub_36E140_0036e140__recomp(EEContext&);  // recompiled
void fn_sub_36E260_0036e260(EEContext&);  // generated body
void fn_sub_36E260_0036e260__recomp(EEContext&);  // recompiled
void fn_sub_36E690_0036e690(EEContext&);  // generated body
void fn_sub_36E690_0036e690__recomp(EEContext&);  // recompiled
void fn_sub_36ED30_0036ed30(EEContext&);  // generated body
void fn_sub_36ED30_0036ed30__recomp(EEContext&);  // recompiled
void fn_sub_36EDD0_0036edd0(EEContext&);  // generated body
void fn_sub_36EDD0_0036edd0__recomp(EEContext&);  // recompiled
void fn_mtEvtMain_UpdateZikkiPlayModeEventViewerTask_0036ee30(EEContext&);  // generated body
void fn_mtEvtMain_UpdateZikkiPlayModeEventViewerTask_0036ee30__recomp(EEContext&);  // recompiled
void fn_sub_36EFB0_0036efb0(EEContext&);  // generated body
void fn_sub_36EFB0_0036efb0__recomp(EEContext&);  // recompiled
void fn_sub_36F000_0036f000(EEContext&);  // generated body
void fn_sub_36F000_0036f000__recomp(EEContext&);  // recompiled
void fn_sub_36F260_0036f260(EEContext&);  // generated body
void fn_sub_36F260_0036f260__recomp(EEContext&);  // recompiled
void fn_sub_36F370_0036f370(EEContext&);  // generated body
void fn_sub_36F370_0036f370__recomp(EEContext&);  // recompiled
void fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0(EEContext&);  // generated body
void fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0__recomp(EEContext&);  // recompiled
void fn_sub_36F480_0036f480(EEContext&);  // generated body
void fn_sub_36F480_0036f480__recomp(EEContext&);  // recompiled
void fn_sub_36F490_0036f490(EEContext&);  // generated body
void fn_sub_36F490_0036f490__recomp(EEContext&);  // recompiled
void fn_sub_36F4C0_0036f4c0(EEContext&);  // generated body
void fn_sub_36F4C0_0036f4c0__recomp(EEContext&);  // recompiled
void fn_sub_36F4D0_0036f4d0(EEContext&);  // generated body
void fn_sub_36F4D0_0036f4d0__recomp(EEContext&);  // recompiled
void fn_sub_36F500_0036f500(EEContext&);  // generated body
void fn_sub_36F500_0036f500__recomp(EEContext&);  // recompiled
void fn_sub_36F5F0_0036f5f0(EEContext&);  // generated body
void fn_sub_36F5F0_0036f5f0__recomp(EEContext&);  // recompiled
void fn_sub_36F640_0036f640(EEContext&);  // generated body
void fn_sub_36F640_0036f640__recomp(EEContext&);  // recompiled
void fn_sub_36F900_0036f900(EEContext&);  // generated body
void fn_sub_36F900_0036f900__recomp(EEContext&);  // recompiled
void fn_sub_36FA40_0036fa40(EEContext&);  // generated body
void fn_sub_36FA40_0036fa40__recomp(EEContext&);  // recompiled
void fn_sub_385860_00385860(EEContext&);  // generated body
void fn_sub_385860_00385860__recomp(EEContext&);  // recompiled
void fn_sub_3858C0_003858c0(EEContext&);  // generated body
void fn_sub_3858C0_003858c0__recomp(EEContext&);  // recompiled
void fn_sub_385B20_00385b20(EEContext&);  // generated body
void fn_sub_385B20_00385b20__recomp(EEContext&);  // recompiled
void fn_nullsub_26_00385b90(EEContext&);  // generated body
void fn_nullsub_26_00385b90__recomp(EEContext&);  // recompiled
void fn_sub_385BA0_00385ba0(EEContext&);  // generated body
void fn_sub_385BA0_00385ba0__recomp(EEContext&);  // recompiled
void fn_sub_386110_00386110(EEContext&);  // generated body
void fn_sub_386110_00386110__recomp(EEContext&);  // recompiled
void fn_sub_386210_00386210(EEContext&);  // generated body
void fn_sub_386210_00386210__recomp(EEContext&);  // recompiled
void fn_sub_386390_00386390(EEContext&);  // generated body
void fn_sub_386390_00386390__recomp(EEContext&);  // recompiled
void fn_sub_386AA0_00386aa0(EEContext&);  // generated body
void fn_sub_386AA0_00386aa0__recomp(EEContext&);  // recompiled
void fn_sub_386AE0_00386ae0(EEContext&);  // generated body
void fn_sub_386AE0_00386ae0__recomp(EEContext&);  // recompiled
void fn_sub_386B70_00386b70(EEContext&);  // generated body
void fn_sub_386B70_00386b70__recomp(EEContext&);  // recompiled
void fn_sub_386C40_00386c40(EEContext&);  // generated body
void fn_sub_386C40_00386c40__recomp(EEContext&);  // recompiled
void fn_sub_386CD0_00386cd0(EEContext&);  // generated body
void fn_sub_386CD0_00386cd0__recomp(EEContext&);  // recompiled
void fn_sub_386E10_00386e10(EEContext&);  // generated body
void fn_sub_386E10_00386e10__recomp(EEContext&);  // recompiled
void fn_sub_386E20_00386e20(EEContext&);  // generated body
void fn_sub_386E20_00386e20__recomp(EEContext&);  // recompiled
void fn_sub_386E30_00386e30(EEContext&);  // generated body
void fn_sub_386E30_00386e30__recomp(EEContext&);  // recompiled
void fn_sub_386E40_00386e40(EEContext&);  // generated body
void fn_sub_386E40_00386e40__recomp(EEContext&);  // recompiled
void fn_sub_388FF0_00388ff0(EEContext&);  // generated body
void fn_sub_388FF0_00388ff0__recomp(EEContext&);  // recompiled
void fn_sub_389F40_00389f40(EEContext&);  // generated body
void fn_sub_389F40_00389f40__recomp(EEContext&);  // recompiled
void fn_sub_38A0B0_0038a0b0(EEContext&);  // generated body
void fn_sub_38A0B0_0038a0b0__recomp(EEContext&);  // recompiled
void fn_sub_38A0C0_0038a0c0(EEContext&);  // generated body
void fn_sub_38A0C0_0038a0c0__recomp(EEContext&);  // recompiled
void fn_sub_38A140_0038a140(EEContext&);  // generated body
void fn_sub_38A140_0038a140__recomp(EEContext&);  // recompiled
void fn_sub_38A180_0038a180(EEContext&);  // generated body
void fn_sub_38A180_0038a180__recomp(EEContext&);  // recompiled
void fn_sub_38A220_0038a220(EEContext&);  // generated body
void fn_sub_38A220_0038a220__recomp(EEContext&);  // recompiled
void fn_sub_38A480_0038a480(EEContext&);  // generated body
void fn_sub_38A480_0038a480__recomp(EEContext&);  // recompiled
void fn_sub_38A4B0_0038a4b0(EEContext&);  // generated body
void fn_sub_38A4B0_0038a4b0__recomp(EEContext&);  // recompiled
void fn_sub_38A590_0038a590(EEContext&);  // generated body
void fn_sub_38A590_0038a590__recomp(EEContext&);  // recompiled
void fn_sub_38A620_0038a620(EEContext&);  // generated body
void fn_sub_38A620_0038a620__recomp(EEContext&);  // recompiled
void fn_sub_38A6C0_0038a6c0(EEContext&);  // generated body
void fn_sub_38A6C0_0038a6c0__recomp(EEContext&);  // recompiled
void fn_sub_38A730_0038a730(EEContext&);  // generated body
void fn_sub_38A730_0038a730__recomp(EEContext&);  // recompiled
void fn_sub_38A900_0038a900(EEContext&);  // generated body
void fn_sub_38A900_0038a900__recomp(EEContext&);  // recompiled
void fn_sub_38C460_0038c460(EEContext&);  // generated body
void fn_sub_38C460_0038c460__recomp(EEContext&);  // recompiled
void fn_sub_38CA00_0038ca00(EEContext&);  // generated body
void fn_sub_38CA00_0038ca00__recomp(EEContext&);  // recompiled
void fn_sub_38CA80_0038ca80(EEContext&);  // generated body
void fn_sub_38CA80_0038ca80__recomp(EEContext&);  // recompiled
void fn_sub_38CC10_0038cc10(EEContext&);  // generated body
void fn_sub_38CC10_0038cc10__recomp(EEContext&);  // recompiled
void fn_sub_38D560_0038d560(EEContext&);  // generated body
void fn_sub_38D560_0038d560__recomp(EEContext&);  // recompiled
void fn_sub_38D6B0_0038d6b0(EEContext&);  // generated body
void fn_sub_38D6B0_0038d6b0__recomp(EEContext&);  // recompiled
void fn_sub_38D6F0_0038d6f0(EEContext&);  // generated body
void fn_sub_38D6F0_0038d6f0__recomp(EEContext&);  // recompiled
void fn_sub_38D720_0038d720(EEContext&);  // generated body
void fn_sub_38D720_0038d720__recomp(EEContext&);  // recompiled
void fn_sub_38D790_0038d790(EEContext&);  // generated body
void fn_sub_38D790_0038d790__recomp(EEContext&);  // recompiled
void fn_sub_38D840_0038d840(EEContext&);  // generated body
void fn_sub_38D840_0038d840__recomp(EEContext&);  // recompiled
void fn_sub_38D910_0038d910(EEContext&);  // generated body
void fn_sub_38D910_0038d910__recomp(EEContext&);  // recompiled
void fn_sub_38D980_0038d980(EEContext&);  // generated body
void fn_sub_38D980_0038d980__recomp(EEContext&);  // recompiled
void fn_sub_38DA10_0038da10(EEContext&);  // generated body
void fn_sub_38DA10_0038da10__recomp(EEContext&);  // recompiled
void fn_sub_38F0F0_0038f0f0(EEContext&);  // generated body
void fn_sub_38F0F0_0038f0f0__recomp(EEContext&);  // recompiled
void fn_sub_38F440_0038f440(EEContext&);  // generated body
void fn_sub_38F440_0038f440__recomp(EEContext&);  // recompiled
void fn_sub_38F8C0_0038f8c0(EEContext&);  // generated body
void fn_sub_38F8C0_0038f8c0__recomp(EEContext&);  // recompiled
void fn_sub_38FA10_0038fa10(EEContext&);  // generated body
void fn_sub_38FA10_0038fa10__recomp(EEContext&);  // recompiled
void fn_sub_38FFB0_0038ffb0(EEContext&);  // generated body
void fn_sub_38FFB0_0038ffb0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_360110", 0x360110, &recomp_gen::fn_sub_360110_00360110, &recomp_gen::fn_sub_360110_00360110__recomp},
    {"sub_3604A0", 0x3604A0, &recomp_gen::fn_sub_3604A0_003604a0, &recomp_gen::fn_sub_3604A0_003604a0__recomp},
    {"sub_360570", 0x360570, &recomp_gen::fn_sub_360570_00360570, &recomp_gen::fn_sub_360570_00360570__recomp},
    {"sub_360640", 0x360640, &recomp_gen::fn_sub_360640_00360640, &recomp_gen::fn_sub_360640_00360640__recomp},
    {"sub_3606F0", 0x3606F0, &recomp_gen::fn_sub_3606F0_003606f0, &recomp_gen::fn_sub_3606F0_003606f0__recomp},
    {"sub_3607A0", 0x3607A0, &recomp_gen::fn_sub_3607A0_003607a0, &recomp_gen::fn_sub_3607A0_003607a0__recomp},
    {"sub_3608E0", 0x3608E0, &recomp_gen::fn_sub_3608E0_003608e0, &recomp_gen::fn_sub_3608E0_003608e0__recomp},
    {"sub_360990", 0x360990, &recomp_gen::fn_sub_360990_00360990, &recomp_gen::fn_sub_360990_00360990__recomp},
    {"sub_360A40", 0x360A40, &recomp_gen::fn_sub_360A40_00360a40, &recomp_gen::fn_sub_360A40_00360a40__recomp},
    {"sub_360AB0", 0x360AB0, &recomp_gen::fn_sub_360AB0_00360ab0, &recomp_gen::fn_sub_360AB0_00360ab0__recomp},
    {"sub_360B00", 0x360B00, &recomp_gen::fn_sub_360B00_00360b00, &recomp_gen::fn_sub_360B00_00360b00__recomp},
    {"sub_360B70", 0x360B70, &recomp_gen::fn_sub_360B70_00360b70, &recomp_gen::fn_sub_360B70_00360b70__recomp},
    {"sub_360C50", 0x360C50, &recomp_gen::fn_sub_360C50_00360c50, &recomp_gen::fn_sub_360C50_00360c50__recomp},
    {"sub_360CF0", 0x360CF0, &recomp_gen::fn_sub_360CF0_00360cf0, &recomp_gen::fn_sub_360CF0_00360cf0__recomp},
    {"sub_360D40", 0x360D40, &recomp_gen::fn_sub_360D40_00360d40, &recomp_gen::fn_sub_360D40_00360d40__recomp},
    {"sub_360ED0", 0x360ED0, &recomp_gen::fn_sub_360ED0_00360ed0, &recomp_gen::fn_sub_360ED0_00360ed0__recomp},
    {"sub_361050", 0x361050, &recomp_gen::fn_sub_361050_00361050, &recomp_gen::fn_sub_361050_00361050__recomp},
    {"sub_361070", 0x361070, &recomp_gen::fn_sub_361070_00361070, &recomp_gen::fn_sub_361070_00361070__recomp},
    {"sub_361140", 0x361140, &recomp_gen::fn_sub_361140_00361140, &recomp_gen::fn_sub_361140_00361140__recomp},
    {"sub_361200", 0x361200, &recomp_gen::fn_sub_361200_00361200, &recomp_gen::fn_sub_361200_00361200__recomp},
    {"sub_361270", 0x361270, &recomp_gen::fn_sub_361270_00361270, &recomp_gen::fn_sub_361270_00361270__recomp},
    {"sub_361350", 0x361350, &recomp_gen::fn_sub_361350_00361350, &recomp_gen::fn_sub_361350_00361350__recomp},
    {"sub_361830", 0x361830, &recomp_gen::fn_sub_361830_00361830, &recomp_gen::fn_sub_361830_00361830__recomp},
    {"sub_361890", 0x361890, &recomp_gen::fn_sub_361890_00361890, &recomp_gen::fn_sub_361890_00361890__recomp},
    {"sub_361B60", 0x361B60, &recomp_gen::fn_sub_361B60_00361b60, &recomp_gen::fn_sub_361B60_00361b60__recomp},
    {"sub_361C30", 0x361C30, &recomp_gen::fn_sub_361C30_00361c30, &recomp_gen::fn_sub_361C30_00361c30__recomp},
    {"sub_361CA0", 0x361CA0, &recomp_gen::fn_sub_361CA0_00361ca0, &recomp_gen::fn_sub_361CA0_00361ca0__recomp},
    {"sub_361D60", 0x361D60, &recomp_gen::fn_sub_361D60_00361d60, &recomp_gen::fn_sub_361D60_00361d60__recomp},
    {"sub_361DD0", 0x361DD0, &recomp_gen::fn_sub_361DD0_00361dd0, &recomp_gen::fn_sub_361DD0_00361dd0__recomp},
    {"sub_361EE0", 0x361EE0, &recomp_gen::fn_sub_361EE0_00361ee0, &recomp_gen::fn_sub_361EE0_00361ee0__recomp},
    {"sub_361F20", 0x361F20, &recomp_gen::fn_sub_361F20_00361f20, &recomp_gen::fn_sub_361F20_00361f20__recomp},
    {"sub_361F60", 0x361F60, &recomp_gen::fn_sub_361F60_00361f60, &recomp_gen::fn_sub_361F60_00361f60__recomp},
    {"sub_361FE0", 0x361FE0, &recomp_gen::fn_sub_361FE0_00361fe0, &recomp_gen::fn_sub_361FE0_00361fe0__recomp},
    {"nullsub_114", 0x362100, &recomp_gen::fn_nullsub_114_00362100, &recomp_gen::fn_nullsub_114_00362100__recomp},
    {"nullsub_115", 0x362110, &recomp_gen::fn_nullsub_115_00362110, &recomp_gen::fn_nullsub_115_00362110__recomp},
    {"sub_362120", 0x362120, &recomp_gen::fn_sub_362120_00362120, &recomp_gen::fn_sub_362120_00362120__recomp},
    {"sub_362240", 0x362240, &recomp_gen::fn_sub_362240_00362240, &recomp_gen::fn_sub_362240_00362240__recomp},
    {"sub_362290", 0x362290, &recomp_gen::fn_sub_362290_00362290, &recomp_gen::fn_sub_362290_00362290__recomp},
    {"sub_362310", 0x362310, &recomp_gen::fn_sub_362310_00362310, &recomp_gen::fn_sub_362310_00362310__recomp},
    {"sub_362F20", 0x362F20, &recomp_gen::fn_sub_362F20_00362f20, &recomp_gen::fn_sub_362F20_00362f20__recomp},
    {"sub_362FA0", 0x362FA0, &recomp_gen::fn_sub_362FA0_00362fa0, &recomp_gen::fn_sub_362FA0_00362fa0__recomp},
    {"sub_362FF0", 0x362FF0, &recomp_gen::fn_sub_362FF0_00362ff0, &recomp_gen::fn_sub_362FF0_00362ff0__recomp},
    {"sub_363030", 0x363030, &recomp_gen::fn_sub_363030_00363030, &recomp_gen::fn_sub_363030_00363030__recomp},
    {"sub_3638E0", 0x3638E0, &recomp_gen::fn_sub_3638E0_003638e0, &recomp_gen::fn_sub_3638E0_003638e0__recomp},
    {"sub_364470", 0x364470, &recomp_gen::fn_sub_364470_00364470, &recomp_gen::fn_sub_364470_00364470__recomp},
    {"sub_3645C0", 0x3645C0, &recomp_gen::fn_sub_3645C0_003645c0, &recomp_gen::fn_sub_3645C0_003645c0__recomp},
    {"sub_3646D0", 0x3646D0, &recomp_gen::fn_sub_3646D0_003646d0, &recomp_gen::fn_sub_3646D0_003646d0__recomp},
    {"sub_3648E0", 0x3648E0, &recomp_gen::fn_sub_3648E0_003648e0, &recomp_gen::fn_sub_3648E0_003648e0__recomp},
    {"sub_364A30", 0x364A30, &recomp_gen::fn_sub_364A30_00364a30, &recomp_gen::fn_sub_364A30_00364a30__recomp},
    {"sub_364B10", 0x364B10, &recomp_gen::fn_sub_364B10_00364b10, &recomp_gen::fn_sub_364B10_00364b10__recomp},
    {"sub_364E40", 0x364E40, &recomp_gen::fn_sub_364E40_00364e40, &recomp_gen::fn_sub_364E40_00364e40__recomp},
    {"sub_3650C0", 0x3650C0, &recomp_gen::fn_sub_3650C0_003650c0, &recomp_gen::fn_sub_3650C0_003650c0__recomp},
    {"sub_365250", 0x365250, &recomp_gen::fn_sub_365250_00365250, &recomp_gen::fn_sub_365250_00365250__recomp},
    {"sub_365360", 0x365360, &recomp_gen::fn_sub_365360_00365360, &recomp_gen::fn_sub_365360_00365360__recomp},
    {"sub_365430", 0x365430, &recomp_gen::fn_sub_365430_00365430, &recomp_gen::fn_sub_365430_00365430__recomp},
    {"sub_3655F0", 0x3655F0, &recomp_gen::fn_sub_3655F0_003655f0, &recomp_gen::fn_sub_3655F0_003655f0__recomp},
    {"sub_3657E0", 0x3657E0, &recomp_gen::fn_sub_3657E0_003657e0, &recomp_gen::fn_sub_3657E0_003657e0__recomp},
    {"sub_3658B0", 0x3658B0, &recomp_gen::fn_sub_3658B0_003658b0, &recomp_gen::fn_sub_3658B0_003658b0__recomp},
    {"sub_365A40", 0x365A40, &recomp_gen::fn_sub_365A40_00365a40, &recomp_gen::fn_sub_365A40_00365a40__recomp},
    {"sub_365B70", 0x365B70, &recomp_gen::fn_sub_365B70_00365b70, &recomp_gen::fn_sub_365B70_00365b70__recomp},
    {"sub_365CD0", 0x365CD0, &recomp_gen::fn_sub_365CD0_00365cd0, &recomp_gen::fn_sub_365CD0_00365cd0__recomp},
    {"sub_365F80", 0x365F80, &recomp_gen::fn_sub_365F80_00365f80, &recomp_gen::fn_sub_365F80_00365f80__recomp},
    {"sub_366210", 0x366210, &recomp_gen::fn_sub_366210_00366210, &recomp_gen::fn_sub_366210_00366210__recomp},
    {"sub_366330", 0x366330, &recomp_gen::fn_sub_366330_00366330, &recomp_gen::fn_sub_366330_00366330__recomp},
    {"sub_3663F0", 0x3663F0, &recomp_gen::fn_sub_3663F0_003663f0, &recomp_gen::fn_sub_3663F0_003663f0__recomp},
    {"sub_366540", 0x366540, &recomp_gen::fn_sub_366540_00366540, &recomp_gen::fn_sub_366540_00366540__recomp},
    {"sub_366660", 0x366660, &recomp_gen::fn_sub_366660_00366660, &recomp_gen::fn_sub_366660_00366660__recomp},
    {"sub_366970", 0x366970, &recomp_gen::fn_sub_366970_00366970, &recomp_gen::fn_sub_366970_00366970__recomp},
    {"sub_366AC0", 0x366AC0, &recomp_gen::fn_sub_366AC0_00366ac0, &recomp_gen::fn_sub_366AC0_00366ac0__recomp},
    {"sub_36D030", 0x36D030, &recomp_gen::fn_sub_36D030_0036d030, &recomp_gen::fn_sub_36D030_0036d030__recomp},
    {"sub_36D320", 0x36D320, &recomp_gen::fn_sub_36D320_0036d320, &recomp_gen::fn_sub_36D320_0036d320__recomp},
    {"sub_36D470", 0x36D470, &recomp_gen::fn_sub_36D470_0036d470, &recomp_gen::fn_sub_36D470_0036d470__recomp},
    {"sub_36D500", 0x36D500, &recomp_gen::fn_sub_36D500_0036d500, &recomp_gen::fn_sub_36D500_0036d500__recomp},
    {"sub_36DA10", 0x36DA10, &recomp_gen::fn_sub_36DA10_0036da10, &recomp_gen::fn_sub_36DA10_0036da10__recomp},
    {"sub_36DB20", 0x36DB20, &recomp_gen::fn_sub_36DB20_0036db20, &recomp_gen::fn_sub_36DB20_0036db20__recomp},
    {"sub_36E140", 0x36E140, &recomp_gen::fn_sub_36E140_0036e140, &recomp_gen::fn_sub_36E140_0036e140__recomp},
    {"sub_36E260", 0x36E260, &recomp_gen::fn_sub_36E260_0036e260, &recomp_gen::fn_sub_36E260_0036e260__recomp},
    {"sub_36E690", 0x36E690, &recomp_gen::fn_sub_36E690_0036e690, &recomp_gen::fn_sub_36E690_0036e690__recomp},
    {"sub_36ED30", 0x36ED30, &recomp_gen::fn_sub_36ED30_0036ed30, &recomp_gen::fn_sub_36ED30_0036ed30__recomp},
    {"sub_36EDD0", 0x36EDD0, &recomp_gen::fn_sub_36EDD0_0036edd0, &recomp_gen::fn_sub_36EDD0_0036edd0__recomp},
    {"mtEvtMain_UpdateZikkiPlayModeEventViewerTask", 0x36EE30, &recomp_gen::fn_mtEvtMain_UpdateZikkiPlayModeEventViewerTask_0036ee30, &recomp_gen::fn_mtEvtMain_UpdateZikkiPlayModeEventViewerTask_0036ee30__recomp},
    {"sub_36EFB0", 0x36EFB0, &recomp_gen::fn_sub_36EFB0_0036efb0, &recomp_gen::fn_sub_36EFB0_0036efb0__recomp},
    {"sub_36F000", 0x36F000, &recomp_gen::fn_sub_36F000_0036f000, &recomp_gen::fn_sub_36F000_0036f000__recomp},
    {"sub_36F260", 0x36F260, &recomp_gen::fn_sub_36F260_0036f260, &recomp_gen::fn_sub_36F260_0036f260__recomp},
    {"sub_36F370", 0x36F370, &recomp_gen::fn_sub_36F370_0036f370, &recomp_gen::fn_sub_36F370_0036f370__recomp},
    {"mtEvtMain_CreateZikkiPlayModeEventViewerTask", 0x36F3B0, &recomp_gen::fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0, &recomp_gen::fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0__recomp},
    {"sub_36F480", 0x36F480, &recomp_gen::fn_sub_36F480_0036f480, &recomp_gen::fn_sub_36F480_0036f480__recomp},
    {"sub_36F490", 0x36F490, &recomp_gen::fn_sub_36F490_0036f490, &recomp_gen::fn_sub_36F490_0036f490__recomp},
    {"sub_36F4C0", 0x36F4C0, &recomp_gen::fn_sub_36F4C0_0036f4c0, &recomp_gen::fn_sub_36F4C0_0036f4c0__recomp},
    {"sub_36F4D0", 0x36F4D0, &recomp_gen::fn_sub_36F4D0_0036f4d0, &recomp_gen::fn_sub_36F4D0_0036f4d0__recomp},
    {"sub_36F500", 0x36F500, &recomp_gen::fn_sub_36F500_0036f500, &recomp_gen::fn_sub_36F500_0036f500__recomp},
    {"sub_36F5F0", 0x36F5F0, &recomp_gen::fn_sub_36F5F0_0036f5f0, &recomp_gen::fn_sub_36F5F0_0036f5f0__recomp},
    {"sub_36F640", 0x36F640, &recomp_gen::fn_sub_36F640_0036f640, &recomp_gen::fn_sub_36F640_0036f640__recomp},
    {"sub_36F900", 0x36F900, &recomp_gen::fn_sub_36F900_0036f900, &recomp_gen::fn_sub_36F900_0036f900__recomp},
    {"sub_36FA40", 0x36FA40, &recomp_gen::fn_sub_36FA40_0036fa40, &recomp_gen::fn_sub_36FA40_0036fa40__recomp},
    {"sub_385860", 0x385860, &recomp_gen::fn_sub_385860_00385860, &recomp_gen::fn_sub_385860_00385860__recomp},
    {"sub_3858C0", 0x3858C0, &recomp_gen::fn_sub_3858C0_003858c0, &recomp_gen::fn_sub_3858C0_003858c0__recomp},
    {"sub_385B20", 0x385B20, &recomp_gen::fn_sub_385B20_00385b20, &recomp_gen::fn_sub_385B20_00385b20__recomp},
    {"nullsub_26", 0x385B90, &recomp_gen::fn_nullsub_26_00385b90, &recomp_gen::fn_nullsub_26_00385b90__recomp},
    {"sub_385BA0", 0x385BA0, &recomp_gen::fn_sub_385BA0_00385ba0, &recomp_gen::fn_sub_385BA0_00385ba0__recomp},
    {"sub_386110", 0x386110, &recomp_gen::fn_sub_386110_00386110, &recomp_gen::fn_sub_386110_00386110__recomp},
    {"sub_386210", 0x386210, &recomp_gen::fn_sub_386210_00386210, &recomp_gen::fn_sub_386210_00386210__recomp},
    {"sub_386390", 0x386390, &recomp_gen::fn_sub_386390_00386390, &recomp_gen::fn_sub_386390_00386390__recomp},
    {"sub_386AA0", 0x386AA0, &recomp_gen::fn_sub_386AA0_00386aa0, &recomp_gen::fn_sub_386AA0_00386aa0__recomp},
    {"sub_386AE0", 0x386AE0, &recomp_gen::fn_sub_386AE0_00386ae0, &recomp_gen::fn_sub_386AE0_00386ae0__recomp},
    {"sub_386B70", 0x386B70, &recomp_gen::fn_sub_386B70_00386b70, &recomp_gen::fn_sub_386B70_00386b70__recomp},
    {"sub_386C40", 0x386C40, &recomp_gen::fn_sub_386C40_00386c40, &recomp_gen::fn_sub_386C40_00386c40__recomp},
    {"sub_386CD0", 0x386CD0, &recomp_gen::fn_sub_386CD0_00386cd0, &recomp_gen::fn_sub_386CD0_00386cd0__recomp},
    {"sub_386E10", 0x386E10, &recomp_gen::fn_sub_386E10_00386e10, &recomp_gen::fn_sub_386E10_00386e10__recomp},
    {"sub_386E20", 0x386E20, &recomp_gen::fn_sub_386E20_00386e20, &recomp_gen::fn_sub_386E20_00386e20__recomp},
    {"sub_386E30", 0x386E30, &recomp_gen::fn_sub_386E30_00386e30, &recomp_gen::fn_sub_386E30_00386e30__recomp},
    {"sub_386E40", 0x386E40, &recomp_gen::fn_sub_386E40_00386e40, &recomp_gen::fn_sub_386E40_00386e40__recomp},
    {"sub_388FF0", 0x388FF0, &recomp_gen::fn_sub_388FF0_00388ff0, &recomp_gen::fn_sub_388FF0_00388ff0__recomp},
    {"sub_389F40", 0x389F40, &recomp_gen::fn_sub_389F40_00389f40, &recomp_gen::fn_sub_389F40_00389f40__recomp},
    {"sub_38A0B0", 0x38A0B0, &recomp_gen::fn_sub_38A0B0_0038a0b0, &recomp_gen::fn_sub_38A0B0_0038a0b0__recomp},
    {"sub_38A0C0", 0x38A0C0, &recomp_gen::fn_sub_38A0C0_0038a0c0, &recomp_gen::fn_sub_38A0C0_0038a0c0__recomp},
    {"sub_38A140", 0x38A140, &recomp_gen::fn_sub_38A140_0038a140, &recomp_gen::fn_sub_38A140_0038a140__recomp},
    {"sub_38A180", 0x38A180, &recomp_gen::fn_sub_38A180_0038a180, &recomp_gen::fn_sub_38A180_0038a180__recomp},
    {"sub_38A220", 0x38A220, &recomp_gen::fn_sub_38A220_0038a220, &recomp_gen::fn_sub_38A220_0038a220__recomp},
    {"sub_38A480", 0x38A480, &recomp_gen::fn_sub_38A480_0038a480, &recomp_gen::fn_sub_38A480_0038a480__recomp},
    {"sub_38A4B0", 0x38A4B0, &recomp_gen::fn_sub_38A4B0_0038a4b0, &recomp_gen::fn_sub_38A4B0_0038a4b0__recomp},
    {"sub_38A590", 0x38A590, &recomp_gen::fn_sub_38A590_0038a590, &recomp_gen::fn_sub_38A590_0038a590__recomp},
    {"sub_38A620", 0x38A620, &recomp_gen::fn_sub_38A620_0038a620, &recomp_gen::fn_sub_38A620_0038a620__recomp},
    {"sub_38A6C0", 0x38A6C0, &recomp_gen::fn_sub_38A6C0_0038a6c0, &recomp_gen::fn_sub_38A6C0_0038a6c0__recomp},
    {"sub_38A730", 0x38A730, &recomp_gen::fn_sub_38A730_0038a730, &recomp_gen::fn_sub_38A730_0038a730__recomp},
    {"sub_38A900", 0x38A900, &recomp_gen::fn_sub_38A900_0038a900, &recomp_gen::fn_sub_38A900_0038a900__recomp},
    {"sub_38C460", 0x38C460, &recomp_gen::fn_sub_38C460_0038c460, &recomp_gen::fn_sub_38C460_0038c460__recomp},
    {"sub_38CA00", 0x38CA00, &recomp_gen::fn_sub_38CA00_0038ca00, &recomp_gen::fn_sub_38CA00_0038ca00__recomp},
    {"sub_38CA80", 0x38CA80, &recomp_gen::fn_sub_38CA80_0038ca80, &recomp_gen::fn_sub_38CA80_0038ca80__recomp},
    {"sub_38CC10", 0x38CC10, &recomp_gen::fn_sub_38CC10_0038cc10, &recomp_gen::fn_sub_38CC10_0038cc10__recomp},
    {"sub_38D560", 0x38D560, &recomp_gen::fn_sub_38D560_0038d560, &recomp_gen::fn_sub_38D560_0038d560__recomp},
    {"sub_38D6B0", 0x38D6B0, &recomp_gen::fn_sub_38D6B0_0038d6b0, &recomp_gen::fn_sub_38D6B0_0038d6b0__recomp},
    {"sub_38D6F0", 0x38D6F0, &recomp_gen::fn_sub_38D6F0_0038d6f0, &recomp_gen::fn_sub_38D6F0_0038d6f0__recomp},
    {"sub_38D720", 0x38D720, &recomp_gen::fn_sub_38D720_0038d720, &recomp_gen::fn_sub_38D720_0038d720__recomp},
    {"sub_38D790", 0x38D790, &recomp_gen::fn_sub_38D790_0038d790, &recomp_gen::fn_sub_38D790_0038d790__recomp},
    {"sub_38D840", 0x38D840, &recomp_gen::fn_sub_38D840_0038d840, &recomp_gen::fn_sub_38D840_0038d840__recomp},
    {"sub_38D910", 0x38D910, &recomp_gen::fn_sub_38D910_0038d910, &recomp_gen::fn_sub_38D910_0038d910__recomp},
    {"sub_38D980", 0x38D980, &recomp_gen::fn_sub_38D980_0038d980, &recomp_gen::fn_sub_38D980_0038d980__recomp},
    {"sub_38DA10", 0x38DA10, &recomp_gen::fn_sub_38DA10_0038da10, &recomp_gen::fn_sub_38DA10_0038da10__recomp},
    {"sub_38F0F0", 0x38F0F0, &recomp_gen::fn_sub_38F0F0_0038f0f0, &recomp_gen::fn_sub_38F0F0_0038f0f0__recomp},
    {"sub_38F440", 0x38F440, &recomp_gen::fn_sub_38F440_0038f440, &recomp_gen::fn_sub_38F440_0038f440__recomp},
    {"sub_38F8C0", 0x38F8C0, &recomp_gen::fn_sub_38F8C0_0038f8c0, &recomp_gen::fn_sub_38F8C0_0038f8c0__recomp},
    {"sub_38FA10", 0x38FA10, &recomp_gen::fn_sub_38FA10_0038fa10, &recomp_gen::fn_sub_38FA10_0038fa10__recomp},
    {"sub_38FFB0", 0x38FFB0, &recomp_gen::fn_sub_38FFB0_0038ffb0, &recomp_gen::fn_sub_38FFB0_0038ffb0__recomp},
};

// --- worlds ----------------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;  // free RAM above the harness's arena (also in the replay snapshots)
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;
constexpr u32 kScrGlobalsPtr = 0x7CCA5Cu;  // g_scrGlobals (the event counters at +800)
constexpr u32 kTypeTable = 0x69E1A0u;      // sub_36F500's 12-byte rows per unit type
constexpr u32 kRankTable = 0x69D590u;      // sub_361B60's rank byte per unit type

namespace rg = p3fes::recomp_gen;
namespace ev = p3fes::game::evt;

u32 rd32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 rd16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void wr32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wr16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// Every callee of the slice that is neither one of its own functions nor in game/replaced.txt: a recorder each (the
// ones this test library emits run for real; the stand-ins answer only for the others), so pairs on real data run past
// the actor / camera / sound / message calls and compare each call's arguments, $ra and entry check point.
struct Callee {
    u32 va;
    const char* name;
};
const Callee kRecorded[] = {
    {0x1005B0u, "H_Cursor_CreateTask"}, {0x3B5760u, "MT_Scene_Load"}, {0x3C2350u, "comu_CreateRevMailSeqTask"},
    {0x530DA0u, "fptodp"}, {0x35AE50u, "nullsub_22"}, {0x35AE60u, "nullsub_23"}, {0x35AE70u, "nullsub_24"},
    {0x35AE80u, "nullsub_25"}, {0x3952A0u, "nullsub_27"}, {0x395420u, "nullsub_28"}, {0x103C30u, "sub_103C30"},
    {0x103CB0u, "sub_103CB0"}, {0x1071B0u, "sub_1071B0"}, {0x108570u, "sub_108570"}, {0x1085C0u, "sub_1085C0"},
    {0x108670u, "sub_108670"}, {0x1086A0u, "sub_1086A0"}, {0x108710u, "sub_108710"}, {0x108F70u, "sub_108F70"},
    {0x108FD0u, "sub_108FD0"}, {0x10A4E0u, "sub_10A4E0"}, {0x10A720u, "sub_10A720"}, {0x10A770u, "sub_10A770"},
    {0x10BC20u, "sub_10BC20"}, {0x16C920u, "sub_16C920"}, {0x16D6B0u, "sub_16D6B0"}, {0x16DBA0u, "sub_16DBA0"},
    {0x16DBC0u, "sub_16DBC0"}, {0x16DCE0u, "sub_16DCE0"}, {0x16DD40u, "sub_16DD40"}, {0x16DDD0u, "sub_16DDD0"},
    {0x16DE50u, "sub_16DE50"}, {0x16DF30u, "sub_16DF30"}, {0x16E100u, "sub_16E100"}, {0x16E2B0u, "sub_16E2B0"},
    {0x16E410u, "sub_16E410"}, {0x171110u, "sub_171110"}, {0x1717B0u, "sub_1717B0"}, {0x171C40u, "sub_171C40"},
    {0x172200u, "sub_172200"}, {0x172820u, "sub_172820"}, {0x172C50u, "sub_172C50"}, {0x176FB0u, "sub_176FB0"},
    {0x198590u, "sub_198590"}, {0x1A0430u, "sub_1A0430"}, {0x1A0D00u, "sub_1A0D00"}, {0x1A0D40u, "sub_1A0D40"},
    {0x1A0D80u, "sub_1A0D80"}, {0x1A4580u, "sub_1A4580"}, {0x1A4600u, "sub_1A4600"}, {0x1A7020u, "sub_1A7020"},
    {0x1A7060u, "sub_1A7060"}, {0x2FF260u, "sub_2FF260"}, {0x316E00u, "sub_316E00"}, {0x316F70u, "sub_316F70"},
    {0x3174E0u, "sub_3174E0"}, {0x3185B0u, "sub_3185B0"}, {0x318870u, "sub_318870"}, {0x318B00u, "sub_318B00"},
    {0x319090u, "sub_319090"}, {0x319100u, "sub_319100"}, {0x319190u, "sub_319190"}, {0x3191D0u, "sub_3191D0"},
    {0x31B680u, "sub_31B680"}, {0x31BE80u, "sub_31BE80"}, {0x362390u, "sub_362390"}, {0x3625E0u, "sub_3625E0"},
    {0x385990u, "sub_385990"}, {0x386D50u, "sub_386D50"}, {0x388DF0u, "sub_388DF0"}, {0x3890E0u, "sub_3890E0"},
    {0x38C540u, "sub_38C540"}, {0x3912F0u, "sub_3912F0"}, {0x393E30u, "sub_393E30"}, {0x393F30u, "sub_393F30"},
    {0x394070u, "sub_394070"}, {0x394270u, "sub_394270"}, {0x3942F0u, "sub_3942F0"}, {0x394C30u, "sub_394C30"},
    {0x395230u, "sub_395230"}, {0x395270u, "sub_395270"}, {0x3952B0u, "sub_3952B0"}, {0x3952C0u, "sub_3952C0"},
    {0x3952D0u, "sub_3952D0"}, {0x395350u, "sub_395350"}, {0x3953E0u, "sub_3953E0"}, {0x395430u, "sub_395430"},
    {0x3954E0u, "sub_3954E0"}, {0x396410u, "sub_396410"}, {0x396480u, "sub_396480"}, {0x3964C0u, "sub_3964C0"},
    {0x396530u, "sub_396530"}, {0x3965D0u, "sub_3965D0"}, {0x3965F0u, "sub_3965F0"}, {0x396760u, "sub_396760"},
    {0x3968A0u, "sub_3968A0"}, {0x396910u, "sub_396910"}, {0x3969B0u, "sub_3969B0"}, {0x396C70u, "sub_396C70"},
    {0x396E30u, "sub_396E30"}, {0x396ED0u, "sub_396ED0"}, {0x396F50u, "sub_396F50"}, {0x397030u, "sub_397030"},
    {0x3970D0u, "sub_3970D0"}, {0x397500u, "sub_397500"}, {0x397510u, "sub_397510"}, {0x397520u, "sub_397520"},
    {0x397580u, "sub_397580"}, {0x397630u, "sub_397630"}, {0x3976F0u, "sub_3976F0"}, {0x397870u, "sub_397870"},
    {0x397F80u, "sub_397F80"}, {0x398060u, "sub_398060"}, {0x3980E0u, "sub_3980E0"}, {0x39B8B0u, "sub_39B8B0"},
    {0x39E1B0u, "sub_39E1B0"}, {0x39E6F0u, "sub_39E6F0"}, {0x39E820u, "sub_39E820"}, {0x39E880u, "sub_39E880"},
    {0x39EA20u, "sub_39EA20"}, {0x39EB90u, "sub_39EB90"}, {0x39EEE0u, "sub_39EEE0"}, {0x39EEF0u, "sub_39EEF0"},
    {0x39EF30u, "sub_39EF30"}, {0x39F210u, "sub_39F210"}, {0x39F350u, "sub_39F350"}, {0x39F410u, "sub_39F410"},
    {0x39F6E0u, "sub_39F6E0"}, {0x39F750u, "sub_39F750"}, {0x3A2090u, "sub_3A2090"}, {0x3A4010u, "sub_3A4010"},
    {0x3A4220u, "sub_3A4220"}, {0x3A4270u, "sub_3A4270"}, {0x3B5430u, "sub_3B5430"}, {0x3B5550u, "sub_3B5550"},
    {0x3B5620u, "sub_3B5620"}, {0x3B58C0u, "sub_3B58C0"}, {0x3B5980u, "sub_3B5980"}, {0x3B5A10u, "sub_3B5A10"},
    {0x3B5AB0u, "sub_3B5AB0"}, {0x3B5D00u, "sub_3B5D00"}, {0x3B5D10u, "sub_3B5D10"}, {0x3B5D50u, "sub_3B5D50"},
    {0x3B5DF0u, "sub_3B5DF0"}, {0x3B5F70u, "sub_3B5F70"}, {0x3B6000u, "sub_3B6000"}, {0x3B7090u, "sub_3B7090"},
    {0x3B7460u, "sub_3B7460"}, {0x3B78B0u, "sub_3B78B0"}, {0x3B7930u, "sub_3B7930"}, {0x3B79A0u, "sub_3B79A0"},
    {0x3B8310u, "sub_3B8310"}, {0x3B8470u, "sub_3B8470"}, {0x3B8690u, "sub_3B8690"}, {0x3B86C0u, "sub_3B86C0"},
    {0x3B8730u, "sub_3B8730"}, {0x3B87F0u, "sub_3B87F0"}, {0x3B89F0u, "sub_3B89F0"}, {0x3B8A60u, "sub_3B8A60"},
    {0x3B8B30u, "sub_3B8B30"}, {0x3B8C30u, "sub_3B8C30"}, {0x3B8E10u, "sub_3B8E10"}, {0x3B8E80u, "sub_3B8E80"},
    {0x3B8F30u, "sub_3B8F30"}, {0x3B8FF0u, "sub_3B8FF0"}, {0x3B9260u, "sub_3B9260"}, {0x3B9500u, "sub_3B9500"},
    {0x3B9550u, "sub_3B9550"}, {0x3BB010u, "sub_3BB010"}, {0x3BB180u, "sub_3BB180"}, {0x3BB1D0u, "sub_3BB1D0"},
    {0x3BB280u, "sub_3BB280"}, {0x3BB340u, "sub_3BB340"}, {0x3BB390u, "sub_3BB390"}, {0x3BB400u, "sub_3BB400"},
    {0x3BB450u, "sub_3BB450"}, {0x3BCBF0u, "sub_3BCBF0"}, {0x3BCC80u, "sub_3BCC80"}, {0x3BD8B0u, "sub_3BD8B0"},
    {0x3BDED0u, "sub_3BDED0"}, {0x3BEA20u, "sub_3BEA20"}, {0x3BEB10u, "sub_3BEB10"}, {0x3BECA0u, "sub_3BECA0"},
    {0x3BEE80u, "sub_3BEE80"}, {0x3C2EE0u, "sub_3C2EE0"}, {0x3C3F40u, "sub_3C3F40"}, {0x3C3F80u, "sub_3C3F80"},
    {0x3C3FE0u, "sub_3C3FE0"}, {0x3C4130u, "sub_3C4130"}, {0x3C43F0u, "sub_3C43F0"}, {0x3C7850u, "sub_3C7850"},
    {0x3C7B90u, "sub_3C7B90"}, {0x3C9790u, "sub_3C9790"}, {0x3CF440u, "sub_3CF440"}, {0x3CF630u, "sub_3CF630"},
    {0x4C31B0u, "sub_4C31B0"},
    // reached since later slices (models, script3, social_map) hand-wrote callees this file used to record: those
    // always run for real, and their own callees need recorders here
    {0x3CF3A0u, "sub_3CF3A0"},
    {0x3A3420u, "sub_3A3420"},
    {0x3A2A30u, "sub_3A2A30"},
    {0x3B5CF0u, "sub_3B5CF0"},
};

constexpr u32 kModelLookup = 0x3B5D10u;  // sub_3B5D10(resId) -> the model record (0: none)
constexpr u32 kStageLookup = 0x3B5D00u;  // sub_3B5D00() -> the stage (0: none)

// The world of one run: the usual stand-ins, a recorder for every other callee; `model` != 0 makes the model / stage
// lookups answer with that record (the actors exist), else they answer 0.
WorldSetup event_world(u32 model) {
    return [model](StandInWorld& w) {
        install_standard(w);
        for (const Callee& c : kRecorded) w.si.install_recorder(c.va, c.name, 0);
        if (model != 0) {
            w.si.install_recorder(kModelLookup, "sub_3B5D10", model);
            w.si.install_recorder(kStageLookup, "sub_3B5D00", model);
        }
    };
}

// Pairs every body on random worlds from the skeleton; then the slice's own worlds below.
}  // namespace

TEST_CASE("game(events): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE("random worlds: " << total << " pairs, " << stops << " stopped early (identically)");
}

namespace {

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

#define NEED_MACHINE()                                    \
    Machine* mp = machine();                              \
    if (!mp) {                                            \
        MESSAGE("SKIP: no ELF at " << elf_path());        \
        return;                                           \
    }                                                     \
    Machine& m = *mp

// A unit with `n` keys in the world at `u` (keys at u + 0x100 + 0x60 * i), frames from `frames`, linked in that order.
void build_unit(Machine& m, u32 u, u32 type, const std::vector<u16>& frames) {
    std::memset(m.at(u), 0, ev::unit::kSize);
    wr32(m, u + ev::unit::kType, type);
    wr32(m, u + ev::unit::kName, 0xFFFFFFFFu);
    u32 prev = 0;
    for (std::size_t i = 0; i < frames.size(); ++i) {
        const u32 k = u + 0x100u + 0x60u * static_cast<u32>(i);
        std::memset(m.at(k), 0, ev::key::kSize);
        wr16(m, k + ev::key::kFrame, frames[i]);
        wr32(m, k + ev::key::kOwnerType, type);
        wr32(m, k + ev::key::kPrev, prev);
        if (prev) wr32(m, prev + ev::key::kNext, k);
        else wr32(m, u + ev::unit::kKeyHead, k);
        prev = k;
    }
    wr32(m, u + ev::unit::kKeyTail, prev);
    wr32(m, u + ev::unit::kKeyCount, static_cast<u32>(frames.size()));
}

// The keys of a unit in list order (bounded walk), and whether the back links agree.
std::vector<u32> keys_of(Machine& m, u32 u, bool* links_ok = nullptr) {
    std::vector<u32> out;
    u32 prev = 0;
    bool ok = true;
    for (u32 k = rd32(m, u + ev::unit::kKeyHead); k != 0 && out.size() < 512; k = rd32(m, k + ev::key::kNext)) {
        ok = ok && rd32(m, k + ev::key::kPrev) == prev;
        out.push_back(k);
        prev = k;
    }
    ok = ok && rd32(m, u + ev::unit::kKeyTail) == prev;
    if (links_ok) *links_ok = ok;
    return out;
}

}  // namespace

TEST_CASE("game(events): the unit / key lists keep their documented order") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE7E7001u};
    int pairs = 0;
    const u32 u = kWorld, nk = kWorld + 0x8000u;
    for (int i = 0; i < 48; ++i) {
        // sub_361140: insert a key into a sorted list -> still sorted, the new key before the first greater frame
        std::vector<u16> frames(rng() % 7);
        for (u16& f : frames) f = static_cast<u16>(rng() % 50);
        std::sort(frames.begin(), frames.end());
        build_unit(m, u, 1, frames);
        std::memset(m.at(nk), 0, ev::key::kSize);
        const u16 f = static_cast<u16>(rng() % 50);
        wr16(m, nk + ev::key::kFrame, f);
        run_pair_si(m, rg::fn_sub_361140_00361140, rg::fn_sub_361140_00361140__recomp, {sx(u), sx(nk), 0, 0}, rng(),
                    "sub_361140 insert", hw, event_world(0));
        ++pairs;
        bool links = false;
        const std::vector<u32> ks = keys_of(m, u, &links);
        CHECK(links);
        REQUIRE(ks.size() == frames.size() + 1);
        CHECK(rd32(m, u + ev::unit::kKeyCount) == ks.size());
        for (std::size_t j = 1; j < ks.size(); ++j) CHECK(rd16(m, ks[j - 1]) <= rd16(m, ks[j]));
        const std::size_t at = static_cast<std::size_t>(std::find(ks.begin(), ks.end(), nk) - ks.begin());
        REQUIRE(at < ks.size());
        if (at + 1 < ks.size()) CHECK(rd16(m, ks[at + 1]) > f);  // inserted before the first strictly greater frame
        // sub_361200: unlink it again -> the original list
        run_pair_si(m, rg::fn_sub_361200_00361200, rg::fn_sub_361200_00361200__recomp, {sx(u), sx(nk), 0, 0}, rng(),
                    "sub_361200 unlink", hw, event_world(0));
        ++pairs;
        const std::vector<u32> back = keys_of(m, u, &links);
        CHECK(links);
        CHECK(back.size() == frames.size());
        CHECK(rd32(m, nk + ev::key::kNext) == 0);
        CHECK(rd32(m, nk + ev::key::kPrev) == 0);
        // sub_361270: one re-sort pass over an unsorted list keeps every key and the links consistent
        std::vector<u16> mixed(1 + rng() % 6);
        for (u16& g : mixed) g = static_cast<u16>(rng() % 20);
        build_unit(m, u, 1, mixed);
        run_pair_si(m, rg::fn_sub_361270_00361270, rg::fn_sub_361270_00361270__recomp, {sx(u), 0, 0, 0}, rng(),
                    "sub_361270 sort pass", hw, event_world(0));
        ++pairs;
        CHECK(keys_of(m, u, &links).size() == mixed.size());
        CHECK(links);
    }
    // sub_361B60: units sorted by the rank byte of their type
    for (int i = 0; i < 32; ++i) {
        const u32 w = kWorld + 0x4000u;
        std::memset(m.at(w), 0, 0x200);
        std::vector<u32> units;
        for (int j = 0; j < 6; ++j) {
            const u32 un = kWorld + 0x5000u + 0xA0u * static_cast<u32>(j);
            std::memset(m.at(un), 0, ev::unit::kSize);
            wr32(m, un + ev::unit::kType, rng() % 51);
            run_pair_si(m, rg::fn_sub_361B60_00361b60, rg::fn_sub_361B60_00361b60__recomp, {sx(un), sx(w), 0, 0}, rng(),
                        "sub_361B60 insert unit", hw, event_world(0));
            ++pairs;
            units.push_back(un);
        }
        CHECK(rd32(m, w + ev::work::kUnitCount) == 6);
        s32 last = -1;
        int n = 0;
        for (u32 un = rd32(m, w + ev::work::kUnitHead); un != 0 && n < 10; un = rd32(m, un + ev::unit::kNext), ++n) {
            const s32 rank = static_cast<s8>(*m.at(kRankTable + rd32(m, un + ev::unit::kType)));
            CHECK(rank >= last);
            last = rank;
        }
        CHECK(n == 6);
    }
    MESSAGE("list rules: " << pairs << " pairs");
}

TEST_CASE("game(events): key conditions, the type table, counters and small helpers") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE7E7002u};
    int pairs = 0;
    const u32 globals = kWorld + 0x6000u;  // g_scrGlobals for the counters (+800)
    wr32(m, kScrGlobalsPtr, globals);
    // sub_36F500: the answer per unit type follows the table row (menu 18 listed), and is cached in the row
    for (u32 type = 0; type < 51; ++type) {
        const u32 row = kTypeTable + 12u * type;
        const std::vector<u8> before(m.at(row), m.at(row) + 12);
        bool has18 = false;
        const s16 count = static_cast<s16>(rd16(m, row));
        for (s16 i = 0; i < count; ++i) has18 = has18 || *m.at(row + 2u + static_cast<u32>(i)) == 18;
        const u8 cache = *m.at(row + 10u);
        const SiPair p = run_pair_si(m, rg::fn_sub_36F500_0036f500, rg::fn_sub_36F500_0036f500__recomp, {type, 0, 0, 0}, rng(),
                                     "sub_36F500", hw, event_world(0));
        ++pairs;
        const u64 v0 = p.hw.recomp.gpr[GPR_V0].u64[0];
        const bool expect = cache == 1 ? true : cache == 2 ? false : has18;
        CHECK(v0 == (expect ? 1u : 0u));
        CHECK(*m.at(row + 10u) == (cache == 1 || cache == 2 ? cache : (expect ? 1 : 2)));
        std::memcpy(m.at(row), before.data(), 12);  // the next type starts from the ELF's table
    }
    // sub_360ED0: the condition rules
    const u32 k = kWorld + 0x7000u;
    for (int i = 0; i < 400; ++i) {
        std::memset(m.at(k), 0, ev::key::kSize);
        const u32 owner = (rng() & 1) ? 1u : rng() % 51;  // type 1 (characters) carries conditions
        wr32(m, k + ev::key::kOwnerType, owner);
        const u8 ctype = static_cast<u8>(rng() % 5);
        const u8 bank = static_cast<u8>(rng() % 4);
        const s16 flag = static_cast<s16>(rng() % 12);
        const s16 value = static_cast<s16>(rng() % 3);
        *m.at(k + ev::key::kCondType) = ctype;
        *m.at(k + ev::key::kCondBank) = bank;
        wr16(m, k + ev::key::kCondFlag, static_cast<u16>(flag));
        wr16(m, k + ev::key::kCondValue, static_cast<u16>(value));
        for (u32 c = 0; c < 10; ++c) wr32(m, globals + 800u + 4u * c, rng() % 3);
        const SiPair p = run_pair_si(m, rg::fn_sub_360ED0_00360ed0, rg::fn_sub_360ED0_00360ed0__recomp, {sx(k), 0, 0, 0}, rng(),
                                     "sub_360ED0", hw, event_world(0));
        ++pairs;
        const u64 v0 = p.hw.recomp.gpr[GPR_V0].u64[0];
        // the type's answer from the (now cached) table row
        const u8 cached = *m.at(kTypeTable + 12u * owner + 10u);
        if (cached == 2 || ctype == 0) {
            CHECK(v0 == 1);
        } else if (ctype == 1) {
            const s32 counter = flag < 10 ? static_cast<s32>(rd32(m, globals + 800u + 4u * static_cast<u32>(flag))) : -1;
            CHECK(v0 == (counter == value ? 1u : 0u));
        } else if (ctype == 2) {
            if (bank >= 3) CHECK(v0 == 0);
            else CHECK(v0 <= 1);
        } else {  // an unknown type: the message, the condition cleared, fires
            CHECK(v0 == 1);
            CHECK(p.recomp->si.calls_to(kPrintf) == 1);
            CHECK(rd32(m, k + ev::key::kCondFlag) == 0);
            CHECK(rd32(m, k + ev::key::kCondType) == 0);
        }
    }
    // sub_38A480: clamp(a + b, lo, hi)
    for (int i = 0; i < 200; ++i) {
        const s32 a = static_cast<s32>(rng() % 200) - 100, b = static_cast<s32>(rng() % 200) - 100;
        const s32 lo = static_cast<s32>(rng() % 100) - 50, hi = static_cast<s32>(rng() % 100) - 20;
        const SiPair p = run_pair_si(m, rg::fn_sub_38A480_0038a480, rg::fn_sub_38A480_0038a480__recomp,
                                     {sx(static_cast<u32>(a)), sx(static_cast<u32>(b)), sx(static_cast<u32>(lo)), sx(static_cast<u32>(hi))},
                                     rng(), "sub_38A480", hw, event_world(0));
        ++pairs;
        s32 x = a + b;
        if (x < lo) x = lo;
        if (x >= hi) x = hi;
        CHECK(static_cast<s32>(p.hw.recomp.gpr[GPR_V0].u64[0]) == x);
    }
    // the work getters / setters and the field-resume pair
    const u32 w = kWorld + 0x9000u;
    for (int i = 0; i < 16; ++i) {
        std::memset(m.at(w), 0, ev::work::kSize);
        const u32 major = rng() % 1000, minor = rng() % 1000;
        run_pair_si(m, rg::fn_sub_386E20_00386e20, rg::fn_sub_386E20_00386e20__recomp, {sx(w), major, 0, 0}, rng(), "sub_386E20", hw, event_world(0));
        run_pair_si(m, rg::fn_sub_386E40_00386e40, rg::fn_sub_386E40_00386e40__recomp, {sx(w), minor, 0, 0}, rng(), "sub_386E40", hw, event_world(0));
        const SiPair a = run_pair_si(m, rg::fn_sub_386E10_00386e10, rg::fn_sub_386E10_00386e10__recomp, {sx(w), 0, 0, 0}, rng(), "sub_386E10", hw, event_world(0));
        const SiPair b = run_pair_si(m, rg::fn_sub_386E30_00386e30, rg::fn_sub_386E30_00386e30__recomp, {sx(w), 0, 0, 0}, rng(), "sub_386E30", hw, event_world(0));
        pairs += 4;
        CHECK(a.hw.recomp.gpr[GPR_V0].u64[0] == major);
        CHECK(b.hw.recomp.gpr[GPR_V0].u64[0] == minor);
        CHECK(rd32(m, w + ev::work::kMajor) == major);
        CHECK(rd32(m, w + ev::work::kMinor) == minor);
        const u32 on = rng() % 3;
        run_pair_si(m, rg::fn_sub_36F490_0036f490, rg::fn_sub_36F490_0036f490__recomp, {on, 0, 0, 0}, rng(), "sub_36F490", hw, event_world(0));
        const SiPair kf = run_pair_si(m, rg::fn_sub_36F480_0036f480, rg::fn_sub_36F480_0036f480__recomp, {0, 0, 0, 0}, rng(), "sub_36F480", hw, event_world(0));
        pairs += 2;
        CHECK(kf.hw.recomp.gpr[GPR_V0].u64[0] == (on == 1 ? 1u : 0u));
        const u32 n = rng() % 12, value = rng();
        run_pair_si(m, rg::fn_sub_38D6B0_0038d6b0, rg::fn_sub_38D6B0_0038d6b0__recomp, {n, value, 0, 0}, rng(), "sub_38D6B0", hw, event_world(0));
        const SiPair g = run_pair_si(m, rg::fn_sub_38D6F0_0038d6f0, rg::fn_sub_38D6F0_0038d6f0__recomp, {n, 0, 0, 0}, rng(), "sub_38D6F0", hw, event_world(0));
        pairs += 2;
        CHECK(static_cast<u32>(g.hw.recomp.gpr[GPR_V0].u64[0]) == (n < 10 ? value : 0xFFFFFFFFu));
    }
    // sub_361FE0: one name per event -- found again by its text, appended when the table is empty
    for (int i = 0; i < 16; ++i) {
        std::memset(m.at(w), 0, ev::work::kSize);
        const u32 name = kWorld + 0xC000u;
        const std::string text = "E" + std::to_string(rng() % 900) + "_00" + std::to_string(rng() % 9);
        m.put(name, text);
        const SiPair add = run_pair_si(m, rg::fn_sub_361FE0_00361fe0, rg::fn_sub_361FE0_00361fe0__recomp, {sx(name), sx(w), 0, 0}, rng(),
                                       "sub_361FE0 add", hw, event_world(0));
        const SiPair find = run_pair_si(m, rg::fn_sub_361FE0_00361fe0, rg::fn_sub_361FE0_00361fe0__recomp, {sx(name), sx(w), 0, 0}, rng(),
                                        "sub_361FE0 find", hw, event_world(0));
        pairs += 2;
        CHECK(add.hw.recomp.gpr[GPR_V0].u64[0] == 0);
        CHECK(find.hw.recomp.gpr[GPR_V0].u64[0] == 0);
        CHECK(rd32(m, w + ev::work::kNameCount) == 1);
        CHECK(m.str(w + ev::work::kNames) == text);
    }
    MESSAGE("rules: " << pairs << " pairs");
}

TEST_CASE("game(events): the actor key appliers on built units, every command firing") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE7E7004u};
    int pairs = 0;
    std::size_t calls = 0;
    const u32 w = kWorld + 0x9000u, u = kWorld, model = kWorld + 0xA000u, ctl = kWorld + 0xA800u;
    const u32 globals = kWorld + 0x6000u;
    wr32(m, kScrGlobalsPtr, globals);
    struct Applier {
        const char* name;
        Fn hand, recomp;
        int args;  // 0: (frame, unit), 1: (work, frame, unit), 2: (frame, work, unit)
    };
    const Applier appliers[] = {
        {"sub_364470", rg::fn_sub_364470_00364470, rg::fn_sub_364470_00364470__recomp, 0},
        {"sub_3645C0", rg::fn_sub_3645C0_003645c0, rg::fn_sub_3645C0_003645c0__recomp, 0},
        {"sub_3646D0", rg::fn_sub_3646D0_003646d0, rg::fn_sub_3646D0_003646d0__recomp, 0},
        {"sub_364A30", rg::fn_sub_364A30_00364a30, rg::fn_sub_364A30_00364a30__recomp, 0},
        {"sub_364B10", rg::fn_sub_364B10_00364b10, rg::fn_sub_364B10_00364b10__recomp, 0},
        {"sub_3648E0", rg::fn_sub_3648E0_003648e0, rg::fn_sub_3648E0_003648e0__recomp, 1},
        {"sub_364E40", rg::fn_sub_364E40_00364e40, rg::fn_sub_364E40_00364e40__recomp, 2},
        {"sub_3650C0", rg::fn_sub_3650C0_003650c0, rg::fn_sub_3650C0_003650c0__recomp, 2},
        {"sub_365250", rg::fn_sub_365250_00365250, rg::fn_sub_365250_00365250__recomp, 2},
        {"sub_365360", rg::fn_sub_365360_00365360, rg::fn_sub_365360_00365360__recomp, 2},
        {"sub_3655F0", rg::fn_sub_3655F0_003655f0, rg::fn_sub_3655F0_003655f0__recomp, 2},
    };
    const u8 commands[] = {0, 1, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 24; ++i) {
        // a character unit (type 1) whose model kind is 1 or 3 (the head / expression controllers), one key per
        // command, most at the test frame, some before it; conditions mostly "always"
        const u16 frame = static_cast<u16>(10 + rng() % 40);
        std::vector<u16> frames;
        for (std::size_t j = 0; j < std::size(commands); ++j) frames.push_back(static_cast<u16>((rng() % 4) ? frame : frame - 1 - rng() % 5));
        std::sort(frames.begin(), frames.end());
        build_unit(m, u, 1, frames);
        const u16 kind = (rng() & 1) ? 1 : 3;
        wr16(m, u + ev::unit::kResId, static_cast<u16>((kind << 10) | (rng() & 0x3FF)));
        wr32(m, u + ev::unit::kModelFlags, rng() & 2);
        const std::vector<u32> ks = keys_of(m, u);
        for (std::size_t j = 0; j < ks.size(); ++j) {
            const u32 k = ks[j];
            for (u32 off = 16; off < 56; off += 4) wr32(m, k + off, rng() % 4 ? rng() % 3 : rng());
            *m.at(k + ev::key::kCmd) = commands[(j + static_cast<std::size_t>(i)) % std::size(commands)];
            *m.at(k + 20u) = static_cast<u8>(rng() % 3);  // the mode byte most commands test
            if ((rng() % 8) == 0) *m.at(k + ev::key::kCondType) = 1;  // a counter condition now and then
        }
        std::memset(m.at(w), 0, ev::work::kSize);
        wr32(m, w + ev::work::kStartFrame, (rng() & 1) ? frame : 0);
        wr32(m, w + ev::work::kFlags, rng() & ev::work::kFlagPlayMode);
        std::memset(m.at(model), 0, 0x200);
        std::memset(m.at(ctl), 0, 0x100);
        wr32(m, model + 296u, ctl);
        for (const Applier& a : appliers) {
            const Args args = a.args == 0   ? Args{frame, sx(u), 0, 0}
                              : a.args == 1 ? Args{sx(w), frame, sx(u), 0}
                                            : Args{frame, sx(w), sx(u), 0};
            calls += run_pair_si(m, a.hand, a.recomp, args, rng(), a.name, hw, event_world(model)).recomp->si.log.size();
            ++pairs;
        }
    }
    MESSAGE("appliers: " << pairs << " pairs, " << calls << " stand-in calls compared");
}

namespace {

// The event viewer's work in a snapshot: the record that points at itself with plausible event numbers and a task.
u32 find_work(Machine& m) {
    for (u32 a = 0x100000u; a + ev::work::kSize < 0x1C00000u; a += 16) {
        if (rd32(m, a) != a) continue;
        const u32 major = rd32(m, a + ev::work::kMajor), minor = rd32(m, a + ev::work::kMinor);
        if (major == 0 || major >= 1000 || minor >= 1000 || rd32(m, a + ev::work::kTask) == 0) continue;
        return a;
    }
    return 0;
}

}  // namespace

TEST_CASE("game(events): the live event of the dorm route (E401_002 in events_dorm_2100 / 2300)") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE7E7003u};
    int pairs = 0, snapshots = 0;
    std::size_t calls = 0;  // stand-in calls compared (the callees the bodies reached)
    for (const char* dir : {"events_dorm_2100", "events_dorm_2300"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << " is not there (a --reference-mode dorm run to that vblank makes it)");
            continue;
        }
        ++snapshots;
        copy_from_snapshot(m, snap, 0, EEMemory::kMainRamSize);
        write_rw_slots(m);
        const u32 w = find_work(m);
        REQUIRE(w != 0);
        // the record as the slice reads it: event E401_002 in play mode, frames 0..60, units in rank order with
        // frame-sorted keys, the counts matching the lists
        CHECK(rd32(m, w + ev::work::kMajor) == 401);
        CHECK(rd32(m, w + ev::work::kMinor) == 2);
        CHECK(m.str(w + ev::work::kEventName) == "E401_002");
        CHECK((rd32(m, w + ev::work::kFlags) & ev::work::kFlagPlayMode) != 0);
        const s32 frame = static_cast<s32>(rd32(m, w + ev::work::kFrame));
        const s32 end = static_cast<s32>(rd32(m, w + ev::work::kEndFrame));
        CHECK(frame >= 0);
        CHECK(frame <= end);
        std::vector<u32> units;
        s32 last_rank = -1;
        for (u32 un = rd32(m, w + ev::work::kUnitHead); un != 0 && units.size() < 200; un = rd32(m, un + ev::unit::kNext)) {
            units.push_back(un);
            const u32 type = rd32(m, un + ev::unit::kType);
            REQUIRE(type < 51);
            const s32 rank = static_cast<s8>(*m.at(kRankTable + type));
            CHECK(rank >= last_rank);
            last_rank = rank;
            bool links = false;
            const std::vector<u32> ks = keys_of(m, un, &links);
            CHECK(links);
            CHECK(ks.size() == rd32(m, un + ev::unit::kKeyCount));
            for (std::size_t j = 1; j < ks.size(); ++j) CHECK(rd16(m, ks[j - 1]) <= rd16(m, ks[j]));
            for (u32 kk : ks) CHECK(rd32(m, kk + ev::key::kOwnerType) == type);
        }
        CHECK(units.size() == rd32(m, w + ev::work::kUnitCount));

        // counting helpers against the lists
        const SiPair cnt = run_pair_si(m, rg::fn_sub_361F20_00361f20, rg::fn_sub_361F20_00361f20__recomp, {sx(w), 0, 0, 0}, rng(),
                                       "sub_361F20", hw, event_world(0));
        ++pairs;
        CHECK(cnt.hw.recomp.gpr[GPR_V0].u64[0] == units.size());
        for (u32 type : {1u, 4u, 10u, 36u, 48u}) {
            u32 n = 0;
            for (u32 un : units) n += rd32(m, un + ev::unit::kType) == type ? 1u : 0u;
            const SiPair c = run_pair_si(m, rg::fn_sub_361EE0_00361ee0, rg::fn_sub_361EE0_00361ee0__recomp, {type, sx(w), 0, 0}, rng(),
                                         "sub_361EE0", hw, event_world(0));
            ++pairs;
            CHECK(c.hw.recomp.gpr[GPR_V0].u64[0] == n);
        }
        for (u32 kind : {2u, 3u}) {
            run_pair_si(m, rg::fn_sub_361F60_00361f60, rg::fn_sub_361F60_00361f60__recomp, {kind, sx(w), 0, 0}, rng(), "sub_361F60", hw,
                        event_world(0));
            ++pairs;
        }
        // every key's condition, and every unit's current key at a few frames
        for (u32 un : units) {
            for (u32 kk : keys_of(m, un)) {
                run_pair_si(m, rg::fn_sub_360ED0_00360ed0, rg::fn_sub_360ED0_00360ed0__recomp, {sx(kk), 0, 0, 0}, rng(), "sub_360ED0 live",
                            hw, event_world(0));
                ++pairs;
            }
            for (s32 f : {0, frame, frame + 1, end}) {
                const u32 out = kWorld + 0xF000u;
                run_pair_si(m, rg::fn_sub_38C460_0038c460, rg::fn_sub_38C460_0038c460__recomp, {sx(un), sx(static_cast<u32>(f)), sx(out), sx(out + 4)},
                            rng(), "sub_38C460 live", hw, event_world(0));
                ++pairs;
            }
        }
        // the per-frame appliers on the live units, with and without actors, at the start, the current and the next
        // frames and at every key frame of the message unit
        std::vector<s32> frames = {0, frame, frame + 1, end};
        for (u32 un : units)
            if (rd32(m, un + ev::unit::kType) == 4)
                for (u32 kk : keys_of(m, un)) frames.push_back(rd16(m, kk));
        const u32 model = kWorld + 0xA000u;  // a zeroed model record for the "actors exist" worlds
        std::memset(m.at(model), 0, 0x200);
        const Case* by_name[160] = {};
        auto find_case = [&](const char* name) -> const Case* {
            for (const Case& c : kCases)
                if (std::string(c.name) == name) return &c;
            return nullptr;
        };
        (void)by_name;
        const char* per_frame[] = {"sub_365430", "sub_3657E0", "sub_3658B0", "sub_365A40", "sub_365B70", "sub_365CD0", "sub_365F80",
                                   "sub_366210", "sub_366330", "sub_3663F0", "sub_366970", "sub_366AC0"};
        const char* per_unit[] = {"sub_364470", "sub_3645C0", "sub_3646D0", "sub_364A30", "sub_364B10"};
        const char* per_unit_w[] = {"sub_3648E0", "sub_364E40", "sub_3650C0", "sub_365250", "sub_365360"};
        for (const s32 f : frames) {
            for (const u32 actors : {0u, model}) {
                for (const char* name : per_frame) {
                    const Case* c = find_case(name);
                    REQUIRE(c != nullptr);
                    calls += run_pair_si(m, c->hand, c->recomp, {sx(static_cast<u32>(f)), sx(w), 0, 0}, rng(), name, hw, event_world(actors)).recomp->si.log.size();
                    ++pairs;
                }
                for (u32 un : units) {
                    const u32 type = rd32(m, un + ev::unit::kType);
                    if (type != 1 && type != 48) continue;
                    for (const char* name : per_unit) {
                        const Case* c = find_case(name);
                        calls += run_pair_si(m, c->hand, c->recomp, {sx(static_cast<u32>(f)), sx(un), 0, 0}, rng(), name, hw, event_world(actors)).recomp->si.log.size();
                        ++pairs;
                    }
                    for (const char* name : per_unit_w) {
                        const Case* c = find_case(name);
                        // sub_3648E0 takes (work, frame, unit); the others (frame, work, unit)
                        const Args a = std::string(name) == "sub_3648E0" ? Args{sx(w), sx(static_cast<u32>(f)), sx(un), 0}
                                                                          : Args{sx(static_cast<u32>(f)), sx(w), sx(un), 0};
                        calls += run_pair_si(m, c->hand, c->recomp, a, rng(), name, hw, event_world(actors)).recomp->si.log.size();
                        ++pairs;
                    }
                }
            }
        }
        // the work-level steps: the stop state, the camera update, the message keys around the frame, the step functions
        const u32 process = kWorld + 0xB000u;  // a process record whose +60 is the work (the step functions' argument)
        // Each pair below starts from the snapshot again. These steps create tasks; every pair's stand-in heap hands out
        // the same blocks, so a task left linked by an earlier pair would be linked a second time and the task list
        // would turn into a cycle (kwlnTaskAddChild then never returns).
        auto fresh = [&] {
            copy_from_snapshot(m, snap, 0, EEMemory::kMainRamSize);
            write_rw_slots(m);
            std::memset(m.at(model), 0, 0x200);
            std::memset(m.at(process), 0, 0x100);
            wr32(m, process + 60u, w);
        };
        const char* per_work[] = {"sub_36D030", "sub_38CA80", "sub_362290", "sub_362310", "sub_362FF0", "sub_38A0B0", "sub_38D720",
                                  "sub_362240", "sub_362FA0", "sub_362F20", "sub_38A6C0", "sub_38A730"};
        for (const char* name : per_work) {
            for (const u32 actors : {0u, model}) {
                const Case* c = find_case(name);
                REQUIRE(c != nullptr);
                fresh();
                calls += run_pair_si(m, c->hand, c->recomp, {sx(w), 0, 0, 0}, rng(), name, hw, event_world(actors)).recomp->si.log.size();
                ++pairs;
            }
        }
        for (const char* name : {"sub_36E690", "sub_36E260", "sub_36E140", "sub_36ED30", "sub_36DB20"}) {
            for (const u32 actors : {0u, model}) {
                const Case* c = find_case(name);
                REQUIRE(c != nullptr);
                fresh();
                calls += run_pair_si(m, c->hand, c->recomp, {sx(process), 0, 0, 0}, rng(), name, hw, event_world(actors)).recomp->si.log.size();
                ++pairs;
            }
        }
        // the frame step: sub_36E690 applies the keys exactly when the frame differs from the last applied one, then
        // advances by one (no jump pending, not stopped, before the last frame) -- checked on the host
        fresh();
        if (rd32(m, w + ev::work::kStopped) == 0 && rd32(m, w + ev::work::kJumpRequest) == 0 && frame < end &&
            (rd32(m, w + ev::work::kFlags) & (ev::work::kFlagEnd | ev::work::kFlagReload | 0x10000u | ev::work::kFlagOverlay)) == 0) {
            run_pair_si(m, rg::fn_sub_36E690_0036e690, rg::fn_sub_36E690_0036e690__recomp, {sx(process), 0, 0, 0}, rng(), "sub_36E690 step",
                        hw, event_world(0));
            ++pairs;
            CHECK(static_cast<s32>(rd32(m, w + ev::work::kPrevFrame)) == frame);
        }
    }
    MESSAGE("live event: " << snapshots << " snapshots, " << pairs << " pairs, " << calls << " stand-in calls compared");
}

#else

TEST_CASE("game(events): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
