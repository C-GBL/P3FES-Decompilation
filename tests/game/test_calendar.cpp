// Pair tests for slice calendar (game/src/calendar/calendar.cpp: clnd.c's calendar band and the rest of datPersona.c /
// g_data.c). Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file
// and cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the
// scratchpad, the BIOS window and the bus log.
//   1. the generic sweep: random words and pointers in a scratch window (mostly the bad-input and early-stop paths);
//   2. the real game state: the replay snapshots (climb_ref_17000, fusion_vr_5000, shop_ref_4100, dorm_replay_4900:
//      days 15 / 16 / 2, the real "CalenderDraw" task in 0x7CDFEC) as the machine, each function on the arguments its
//      callers pass -- every day of the year and every time slot for the date functions, every state of the task
//      updates (fake tasks whose work starts in that state), the hero's personas and held items -- through two
//      trampolines that give each body a fresh, identical stand-in world (stand_ins.h: the heap behind H_Malloc and
//      the RW slots, printf / sprintf, the H_Cdvd layer; recorders for the callees this build does not emit);
//   3. documented rules, the expected values computed on the host from the ELF's own tables (tbl_clndMonthLengths,
//      tbl_clndHolidays, tbl_clndMoonPhase) and checked on the recompiled run's result: the next holiday of every day,
//      the date codes of the social timers, THE TIME-ADVANCE RULE of the calendar task (every day x every slot, and
//      the time-skip cases), today's scheduled event on a built event table, the persona skill list, the bit arrays,
//      the clamp, the hero's name strings; and the calendar facts of calendar.h against the ELF.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/calendar.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_176210_00176210(EEContext&);  // generated body
void fn_sub_176210_00176210__recomp(EEContext&);  // recompiled
void fn_sub_1764B0_001764b0(EEContext&);  // generated body
void fn_sub_1764B0_001764b0__recomp(EEContext&);  // recompiled
void fn_sub_176510_00176510(EEContext&);  // generated body
void fn_sub_176510_00176510__recomp(EEContext&);  // recompiled
void fn_sub_176600_00176600(EEContext&);  // generated body
void fn_sub_176600_00176600__recomp(EEContext&);  // recompiled
void fn_sub_176680_00176680(EEContext&);  // generated body
void fn_sub_176680_00176680__recomp(EEContext&);  // recompiled
void fn_sub_176840_00176840(EEContext&);  // generated body
void fn_sub_176840_00176840__recomp(EEContext&);  // recompiled
void fn_sub_1768E0_001768e0(EEContext&);  // generated body
void fn_sub_1768E0_001768e0__recomp(EEContext&);  // recompiled
void fn_sub_176990_00176990(EEContext&);  // generated body
void fn_sub_176990_00176990__recomp(EEContext&);  // recompiled
void fn_sub_176A30_00176a30(EEContext&);  // generated body
void fn_sub_176A30_00176a30__recomp(EEContext&);  // recompiled
void fn_sub_176AC0_00176ac0(EEContext&);  // generated body
void fn_sub_176AC0_00176ac0__recomp(EEContext&);  // recompiled
void fn_sub_176C80_00176c80(EEContext&);  // generated body
void fn_sub_176C80_00176c80__recomp(EEContext&);  // recompiled
void fn_sub_176D10_00176d10(EEContext&);  // generated body
void fn_sub_176D10_00176d10__recomp(EEContext&);  // recompiled
void fn_sub_176DA0_00176da0(EEContext&);  // generated body
void fn_sub_176DA0_00176da0__recomp(EEContext&);  // recompiled
void fn_sub_176FB0_00176fb0(EEContext&);  // generated body
void fn_sub_176FB0_00176fb0__recomp(EEContext&);  // recompiled
void fn_sub_1770D0_001770d0(EEContext&);  // generated body
void fn_sub_1770D0_001770d0__recomp(EEContext&);  // recompiled
void fn_nullsub_4_00177270(EEContext&);  // generated body
void fn_nullsub_4_00177270__recomp(EEContext&);  // recompiled
void fn_sub_1773D0_001773d0(EEContext&);  // generated body
void fn_sub_1773D0_001773d0__recomp(EEContext&);  // recompiled
void fn_sub_177410_00177410(EEContext&);  // generated body
void fn_sub_177410_00177410__recomp(EEContext&);  // recompiled
void fn_sub_1774E0_001774e0(EEContext&);  // generated body
void fn_sub_1774E0_001774e0__recomp(EEContext&);  // recompiled
void fn_sub_1775A0_001775a0(EEContext&);  // generated body
void fn_sub_1775A0_001775a0__recomp(EEContext&);  // recompiled
void fn_sub_177670_00177670(EEContext&);  // generated body
void fn_sub_177670_00177670__recomp(EEContext&);  // recompiled
void fn_sub_177790_00177790(EEContext&);  // generated body
void fn_sub_177790_00177790__recomp(EEContext&);  // recompiled
void fn_sub_1778B0_001778b0(EEContext&);  // generated body
void fn_sub_1778B0_001778b0__recomp(EEContext&);  // recompiled
void fn_sub_1779A0_001779a0(EEContext&);  // generated body
void fn_sub_1779A0_001779a0__recomp(EEContext&);  // recompiled
void fn_sub_177A40_00177a40(EEContext&);  // generated body
void fn_sub_177A40_00177a40__recomp(EEContext&);  // recompiled
void fn_sub_177A90_00177a90(EEContext&);  // generated body
void fn_sub_177A90_00177a90__recomp(EEContext&);  // recompiled
void fn_sub_177B50_00177b50(EEContext&);  // generated body
void fn_sub_177B50_00177b50__recomp(EEContext&);  // recompiled
void fn_sub_177B90_00177b90(EEContext&);  // generated body
void fn_sub_177B90_00177b90__recomp(EEContext&);  // recompiled
void fn_sub_177C10_00177c10(EEContext&);  // generated body
void fn_sub_177C10_00177c10__recomp(EEContext&);  // recompiled
void fn_sub_177C50_00177c50(EEContext&);  // generated body
void fn_sub_177C50_00177c50__recomp(EEContext&);  // recompiled
void fn_sub_177CA0_00177ca0(EEContext&);  // generated body
void fn_sub_177CA0_00177ca0__recomp(EEContext&);  // recompiled
void fn_sub_177CE0_00177ce0(EEContext&);  // generated body
void fn_sub_177CE0_00177ce0__recomp(EEContext&);  // recompiled
void fn_sub_177D10_00177d10(EEContext&);  // generated body
void fn_sub_177D10_00177d10__recomp(EEContext&);  // recompiled
void fn_sub_177D40_00177d40(EEContext&);  // generated body
void fn_sub_177D40_00177d40__recomp(EEContext&);  // recompiled
void fn_sub_17AC60_0017ac60(EEContext&);  // generated body
void fn_sub_17AC60_0017ac60__recomp(EEContext&);  // recompiled
void fn_sub_17AD90_0017ad90(EEContext&);  // generated body
void fn_sub_17AD90_0017ad90__recomp(EEContext&);  // recompiled
void fn_sub_17ADF0_0017adf0(EEContext&);  // generated body
void fn_sub_17ADF0_0017adf0__recomp(EEContext&);  // recompiled
void fn_sub_17AE30_0017ae30(EEContext&);  // generated body
void fn_sub_17AE30_0017ae30__recomp(EEContext&);  // recompiled
void fn_sub_17AE50_0017ae50(EEContext&);  // generated body
void fn_sub_17AE50_0017ae50__recomp(EEContext&);  // recompiled
void fn_sub_17AF20_0017af20(EEContext&);  // generated body
void fn_sub_17AF20_0017af20__recomp(EEContext&);  // recompiled
void fn_sub_17AFD0_0017afd0(EEContext&);  // generated body
void fn_sub_17AFD0_0017afd0__recomp(EEContext&);  // recompiled
void fn_sub_17B070_0017b070(EEContext&);  // generated body
void fn_sub_17B070_0017b070__recomp(EEContext&);  // recompiled
void fn_sub_17B100_0017b100(EEContext&);  // generated body
void fn_sub_17B100_0017b100__recomp(EEContext&);  // recompiled
void fn_sub_17B160_0017b160(EEContext&);  // generated body
void fn_sub_17B160_0017b160__recomp(EEContext&);  // recompiled
void fn_sub_17B170_0017b170(EEContext&);  // generated body
void fn_sub_17B170_0017b170__recomp(EEContext&);  // recompiled
void fn_sub_17B180_0017b180(EEContext&);  // generated body
void fn_sub_17B180_0017b180__recomp(EEContext&);  // recompiled
void fn_sub_17B1A0_0017b1a0(EEContext&);  // generated body
void fn_sub_17B1A0_0017b1a0__recomp(EEContext&);  // recompiled
void fn_sub_17B1E0_0017b1e0(EEContext&);  // generated body
void fn_sub_17B1E0_0017b1e0__recomp(EEContext&);  // recompiled
void fn_sub_17B220_0017b220(EEContext&);  // generated body
void fn_sub_17B220_0017b220__recomp(EEContext&);  // recompiled
void fn_sub_17B260_0017b260(EEContext&);  // generated body
void fn_sub_17B260_0017b260__recomp(EEContext&);  // recompiled
void fn_sub_17B2A0_0017b2a0(EEContext&);  // generated body
void fn_sub_17B2A0_0017b2a0__recomp(EEContext&);  // recompiled
void fn_sub_17B2E0_0017b2e0(EEContext&);  // generated body
void fn_sub_17B2E0_0017b2e0__recomp(EEContext&);  // recompiled
void fn_sub_17B3D0_0017b3d0(EEContext&);  // generated body
void fn_sub_17B3D0_0017b3d0__recomp(EEContext&);  // recompiled
void fn_sub_17B480_0017b480(EEContext&);  // generated body
void fn_sub_17B480_0017b480__recomp(EEContext&);  // recompiled
void fn_sub_17B4E0_0017b4e0(EEContext&);  // generated body
void fn_sub_17B4E0_0017b4e0__recomp(EEContext&);  // recompiled
void fn_sub_17B500_0017b500(EEContext&);  // generated body
void fn_sub_17B500_0017b500__recomp(EEContext&);  // recompiled
void fn_sub_17B5B0_0017b5b0(EEContext&);  // generated body
void fn_sub_17B5B0_0017b5b0__recomp(EEContext&);  // recompiled
void fn_sub_17B660_0017b660(EEContext&);  // generated body
void fn_sub_17B660_0017b660__recomp(EEContext&);  // recompiled
void fn_sub_17BB40_0017bb40(EEContext&);  // generated body
void fn_sub_17BB40_0017bb40__recomp(EEContext&);  // recompiled
void fn_sub_17BBB0_0017bbb0(EEContext&);  // generated body
void fn_sub_17BBB0_0017bbb0__recomp(EEContext&);  // recompiled
void fn_sub_17BC20_0017bc20(EEContext&);  // generated body
void fn_sub_17BC20_0017bc20__recomp(EEContext&);  // recompiled
void fn_sub_17BE10_0017be10(EEContext&);  // generated body
void fn_sub_17BE10_0017be10__recomp(EEContext&);  // recompiled
void fn_sub_17BF70_0017bf70(EEContext&);  // generated body
void fn_sub_17BF70_0017bf70__recomp(EEContext&);  // recompiled
void fn_sub_17BFA0_0017bfa0(EEContext&);  // generated body
void fn_sub_17BFA0_0017bfa0__recomp(EEContext&);  // recompiled
void fn_sub_17C070_0017c070(EEContext&);  // generated body
void fn_sub_17C070_0017c070__recomp(EEContext&);  // recompiled
void fn_sub_17C0E0_0017c0e0(EEContext&);  // generated body
void fn_sub_17C0E0_0017c0e0__recomp(EEContext&);  // recompiled
void fn_sub_17C190_0017c190(EEContext&);  // generated body
void fn_sub_17C190_0017c190__recomp(EEContext&);  // recompiled
void fn_sub_17C1C0_0017c1c0(EEContext&);  // generated body
void fn_sub_17C1C0_0017c1c0__recomp(EEContext&);  // recompiled
void fn_sub_17C220_0017c220(EEContext&);  // generated body
void fn_sub_17C220_0017c220__recomp(EEContext&);  // recompiled
void fn_sub_17C280_0017c280(EEContext&);  // generated body
void fn_sub_17C280_0017c280__recomp(EEContext&);  // recompiled
void fn_sub_17D7C0_0017d7c0(EEContext&);  // generated body
void fn_sub_17D7C0_0017d7c0__recomp(EEContext&);  // recompiled
void fn_sub_17D7F0_0017d7f0(EEContext&);  // generated body
void fn_sub_17D7F0_0017d7f0__recomp(EEContext&);  // recompiled
void fn_sub_17DDF0_0017ddf0(EEContext&);  // generated body
void fn_sub_17DDF0_0017ddf0__recomp(EEContext&);  // recompiled
void fn_sub_17E050_0017e050(EEContext&);  // generated body
void fn_sub_17E050_0017e050__recomp(EEContext&);  // recompiled
void fn_sub_17E680_0017e680(EEContext&);  // generated body
void fn_sub_17E680_0017e680__recomp(EEContext&);  // recompiled
void fn_sub_17F8D0_0017f8d0(EEContext&);  // generated body
void fn_sub_17F8D0_0017f8d0__recomp(EEContext&);  // recompiled
void fn_sub_17FA10_0017fa10(EEContext&);  // generated body
void fn_sub_17FA10_0017fa10__recomp(EEContext&);  // recompiled
void fn_sub_17FAA0_0017faa0(EEContext&);  // generated body
void fn_sub_17FAA0_0017faa0__recomp(EEContext&);  // recompiled
void fn_sub_17FAD0_0017fad0(EEContext&);  // generated body
void fn_sub_17FAD0_0017fad0__recomp(EEContext&);  // recompiled
void fn_sub_17FB90_0017fb90(EEContext&);  // generated body
void fn_sub_17FB90_0017fb90__recomp(EEContext&);  // recompiled
void fn_sub_17FC70_0017fc70(EEContext&);  // generated body
void fn_sub_17FC70_0017fc70__recomp(EEContext&);  // recompiled
void fn_sub_17FE10_0017fe10(EEContext&);  // generated body
void fn_sub_17FE10_0017fe10__recomp(EEContext&);  // recompiled
void fn_sub_180030_00180030(EEContext&);  // generated body
void fn_sub_180030_00180030__recomp(EEContext&);  // recompiled
void fn_sub_180220_00180220(EEContext&);  // generated body
void fn_sub_180220_00180220__recomp(EEContext&);  // recompiled
void fn_sub_180A20_00180a20(EEContext&);  // generated body
void fn_sub_180A20_00180a20__recomp(EEContext&);  // recompiled
void fn_sub_180C40_00180c40(EEContext&);  // generated body
void fn_sub_180C40_00180c40__recomp(EEContext&);  // recompiled
void fn_sub_180E60_00180e60(EEContext&);  // generated body
void fn_sub_180E60_00180e60__recomp(EEContext&);  // recompiled
void fn_sub_180EE0_00180ee0(EEContext&);  // generated body
void fn_sub_180EE0_00180ee0__recomp(EEContext&);  // recompiled
void fn_sub_181010_00181010(EEContext&);  // generated body
void fn_sub_181010_00181010__recomp(EEContext&);  // recompiled
void fn_sub_181170_00181170(EEContext&);  // generated body
void fn_sub_181170_00181170__recomp(EEContext&);  // recompiled
void fn_sub_181310_00181310(EEContext&);  // generated body
void fn_sub_181310_00181310__recomp(EEContext&);  // recompiled
void fn_sub_181430_00181430(EEContext&);  // generated body
void fn_sub_181430_00181430__recomp(EEContext&);  // recompiled
void fn_sub_181580_00181580(EEContext&);  // generated body
void fn_sub_181580_00181580__recomp(EEContext&);  // recompiled
void fn_sub_181720_00181720(EEContext&);  // generated body
void fn_sub_181720_00181720__recomp(EEContext&);  // recompiled
void fn_sub_181950_00181950(EEContext&);  // generated body
void fn_sub_181950_00181950__recomp(EEContext&);  // recompiled
void fn_sub_181B70_00181b70(EEContext&);  // generated body
void fn_sub_181B70_00181b70__recomp(EEContext&);  // recompiled
void fn_sub_181CC0_00181cc0(EEContext&);  // generated body
void fn_sub_181CC0_00181cc0__recomp(EEContext&);  // recompiled
void fn_sub_182720_00182720(EEContext&);  // generated body
void fn_sub_182720_00182720__recomp(EEContext&);  // recompiled
void fn_sub_182750_00182750(EEContext&);  // generated body
void fn_sub_182750_00182750__recomp(EEContext&);  // recompiled
void fn_sub_182810_00182810(EEContext&);  // generated body
void fn_sub_182810_00182810__recomp(EEContext&);  // recompiled
void fn_sub_1828D0_001828d0(EEContext&);  // generated body
void fn_sub_1828D0_001828d0__recomp(EEContext&);  // recompiled
void fn_sub_182C50_00182c50(EEContext&);  // generated body
void fn_sub_182C50_00182c50__recomp(EEContext&);  // recompiled
void fn_sub_182D90_00182d90(EEContext&);  // generated body
void fn_sub_182D90_00182d90__recomp(EEContext&);  // recompiled
void fn_sub_1830C0_001830c0(EEContext&);  // generated body
void fn_sub_1830C0_001830c0__recomp(EEContext&);  // recompiled
void fn_sub_1831E0_001831e0(EEContext&);  // generated body
void fn_sub_1831E0_001831e0__recomp(EEContext&);  // recompiled
void fn_sub_1833E0_001833e0(EEContext&);  // generated body
void fn_sub_1833E0_001833e0__recomp(EEContext&);  // recompiled
void fn_sub_184890_00184890(EEContext&);  // generated body
void fn_sub_184890_00184890__recomp(EEContext&);  // recompiled
void fn_H_DayParts_CreateTask_00184db0(EEContext&);  // generated body
void fn_H_DayParts_CreateTask_00184db0__recomp(EEContext&);  // recompiled
void fn_sub_184F00_00184f00(EEContext&);  // generated body
void fn_sub_184F00_00184f00__recomp(EEContext&);  // recompiled
void fn_sub_185830_00185830(EEContext&);  // generated body
void fn_sub_185830_00185830__recomp(EEContext&);  // recompiled
void fn_sub_185880_00185880(EEContext&);  // generated body
void fn_sub_185880_00185880__recomp(EEContext&);  // recompiled
void fn_sub_185980_00185980(EEContext&);  // generated body
void fn_sub_185980_00185980__recomp(EEContext&);  // recompiled
void fn_sub_185AE0_00185ae0(EEContext&);  // generated body
void fn_sub_185AE0_00185ae0__recomp(EEContext&);  // recompiled
void fn_H_DayChgDraw_DrawStrip_00185b40(EEContext&);  // generated body
void fn_H_DayChgDraw_DrawStrip_00185b40__recomp(EEContext&);  // recompiled
void fn_sub_186050_00186050(EEContext&);  // generated body
void fn_sub_186050_00186050__recomp(EEContext&);  // recompiled
void fn_sub_186100_00186100(EEContext&);  // generated body
void fn_sub_186100_00186100__recomp(EEContext&);  // recompiled
void fn_sub_186140_00186140(EEContext&);  // generated body
void fn_sub_186140_00186140__recomp(EEContext&);  // recompiled
void fn_sub_186190_00186190(EEContext&);  // generated body
void fn_sub_186190_00186190__recomp(EEContext&);  // recompiled
void fn_sub_1868F0_001868f0(EEContext&);  // generated body
void fn_sub_1868F0_001868f0__recomp(EEContext&);  // recompiled
void fn_sub_186960_00186960(EEContext&);  // generated body
void fn_sub_186960_00186960__recomp(EEContext&);  // recompiled
void fn_sub_186A40_00186a40(EEContext&);  // generated body
void fn_sub_186A40_00186a40__recomp(EEContext&);  // recompiled
void fn_sub_186BD0_00186bd0(EEContext&);  // generated body
void fn_sub_186BD0_00186bd0__recomp(EEContext&);  // recompiled
void fn_sub_186D50_00186d50(EEContext&);  // generated body
void fn_sub_186D50_00186d50__recomp(EEContext&);  // recompiled
void fn_sub_187050_00187050(EEContext&);  // generated body
void fn_sub_187050_00187050__recomp(EEContext&);  // recompiled
void fn_sub_1870E0_001870e0(EEContext&);  // generated body
void fn_sub_1870E0_001870e0__recomp(EEContext&);  // recompiled
void fn_sub_1871A0_001871a0(EEContext&);  // generated body
void fn_sub_1871A0_001871a0__recomp(EEContext&);  // recompiled
void fn_sub_187520_00187520(EEContext&);  // generated body
void fn_sub_187520_00187520__recomp(EEContext&);  // recompiled
void fn_sub_187550_00187550(EEContext&);  // generated body
void fn_sub_187550_00187550__recomp(EEContext&);  // recompiled
void fn_sub_187DF0_00187df0(EEContext&);  // generated body
void fn_sub_187DF0_00187df0__recomp(EEContext&);  // recompiled
void fn_sub_187E20_00187e20(EEContext&);  // generated body
void fn_sub_187E20_00187e20__recomp(EEContext&);  // recompiled
void fn_sub_187EC0_00187ec0(EEContext&);  // generated body
void fn_sub_187EC0_00187ec0__recomp(EEContext&);  // recompiled
void fn_sub_1883D0_001883d0(EEContext&);  // generated body
void fn_sub_1883D0_001883d0__recomp(EEContext&);  // recompiled
void fn_sub_188440_00188440(EEContext&);  // generated body
void fn_sub_188440_00188440__recomp(EEContext&);  // recompiled
void fn_sub_188510_00188510(EEContext&);  // generated body
void fn_sub_188510_00188510__recomp(EEContext&);  // recompiled
void fn_sub_1885A0_001885a0(EEContext&);  // generated body
void fn_sub_1885A0_001885a0__recomp(EEContext&);  // recompiled
void fn_nullsub_5_00188650(EEContext&);  // generated body
void fn_nullsub_5_00188650__recomp(EEContext&);  // recompiled
void fn_nullsub_6_00188670(EEContext&);  // generated body
void fn_nullsub_6_00188670__recomp(EEContext&);  // recompiled
void fn_nullsub_7_00188680(EEContext&);  // generated body
void fn_nullsub_7_00188680__recomp(EEContext&);  // recompiled
void fn_clndUpdateBootupCheckMemcardTask_00188690(EEContext&);  // generated body
void fn_clndUpdateBootupCheckMemcardTask_00188690__recomp(EEContext&);  // recompiled
void fn_sub_188830_00188830(EEContext&);  // generated body
void fn_sub_188830_00188830__recomp(EEContext&);  // recompiled
void fn_sub_188860_00188860(EEContext&);  // generated body
void fn_sub_188860_00188860__recomp(EEContext&);  // recompiled
void fn_sub_188900_00188900(EEContext&);  // generated body
void fn_sub_188900_00188900__recomp(EEContext&);  // recompiled
void fn_sub_188B20_00188b20(EEContext&);  // generated body
void fn_sub_188B20_00188b20__recomp(EEContext&);  // recompiled
void fn_sub_188B50_00188b50(EEContext&);  // generated body
void fn_sub_188B50_00188b50__recomp(EEContext&);  // recompiled
void fn_sub_188C30_00188c30(EEContext&);  // generated body
void fn_sub_188C30_00188c30__recomp(EEContext&);  // recompiled
void fn_sub_189230_00189230(EEContext&);  // generated body
void fn_sub_189230_00189230__recomp(EEContext&);  // recompiled
void fn_sub_189810_00189810(EEContext&);  // generated body
void fn_sub_189810_00189810__recomp(EEContext&);  // recompiled
void fn_sub_189DF0_00189df0(EEContext&);  // generated body
void fn_sub_189DF0_00189df0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_176210", 0x176210, &recomp_gen::fn_sub_176210_00176210, &recomp_gen::fn_sub_176210_00176210__recomp},
    {"sub_1764B0", 0x1764B0, &recomp_gen::fn_sub_1764B0_001764b0, &recomp_gen::fn_sub_1764B0_001764b0__recomp},
    {"sub_176510", 0x176510, &recomp_gen::fn_sub_176510_00176510, &recomp_gen::fn_sub_176510_00176510__recomp},
    {"sub_176600", 0x176600, &recomp_gen::fn_sub_176600_00176600, &recomp_gen::fn_sub_176600_00176600__recomp},
    {"sub_176680", 0x176680, &recomp_gen::fn_sub_176680_00176680, &recomp_gen::fn_sub_176680_00176680__recomp},
    {"sub_176840", 0x176840, &recomp_gen::fn_sub_176840_00176840, &recomp_gen::fn_sub_176840_00176840__recomp},
    {"sub_1768E0", 0x1768E0, &recomp_gen::fn_sub_1768E0_001768e0, &recomp_gen::fn_sub_1768E0_001768e0__recomp},
    {"sub_176990", 0x176990, &recomp_gen::fn_sub_176990_00176990, &recomp_gen::fn_sub_176990_00176990__recomp},
    {"sub_176A30", 0x176A30, &recomp_gen::fn_sub_176A30_00176a30, &recomp_gen::fn_sub_176A30_00176a30__recomp},
    {"sub_176AC0", 0x176AC0, &recomp_gen::fn_sub_176AC0_00176ac0, &recomp_gen::fn_sub_176AC0_00176ac0__recomp},
    {"sub_176C80", 0x176C80, &recomp_gen::fn_sub_176C80_00176c80, &recomp_gen::fn_sub_176C80_00176c80__recomp},
    {"sub_176D10", 0x176D10, &recomp_gen::fn_sub_176D10_00176d10, &recomp_gen::fn_sub_176D10_00176d10__recomp},
    {"sub_176DA0", 0x176DA0, &recomp_gen::fn_sub_176DA0_00176da0, &recomp_gen::fn_sub_176DA0_00176da0__recomp},
    {"sub_176FB0", 0x176FB0, &recomp_gen::fn_sub_176FB0_00176fb0, &recomp_gen::fn_sub_176FB0_00176fb0__recomp},
    {"sub_1770D0", 0x1770D0, &recomp_gen::fn_sub_1770D0_001770d0, &recomp_gen::fn_sub_1770D0_001770d0__recomp},
    {"nullsub_4", 0x177270, &recomp_gen::fn_nullsub_4_00177270, &recomp_gen::fn_nullsub_4_00177270__recomp},
    {"sub_1773D0", 0x1773D0, &recomp_gen::fn_sub_1773D0_001773d0, &recomp_gen::fn_sub_1773D0_001773d0__recomp},
    {"sub_177410", 0x177410, &recomp_gen::fn_sub_177410_00177410, &recomp_gen::fn_sub_177410_00177410__recomp},
    {"sub_1774E0", 0x1774E0, &recomp_gen::fn_sub_1774E0_001774e0, &recomp_gen::fn_sub_1774E0_001774e0__recomp},
    {"sub_1775A0", 0x1775A0, &recomp_gen::fn_sub_1775A0_001775a0, &recomp_gen::fn_sub_1775A0_001775a0__recomp},
    {"sub_177670", 0x177670, &recomp_gen::fn_sub_177670_00177670, &recomp_gen::fn_sub_177670_00177670__recomp},
    {"sub_177790", 0x177790, &recomp_gen::fn_sub_177790_00177790, &recomp_gen::fn_sub_177790_00177790__recomp},
    {"sub_1778B0", 0x1778B0, &recomp_gen::fn_sub_1778B0_001778b0, &recomp_gen::fn_sub_1778B0_001778b0__recomp},
    {"sub_1779A0", 0x1779A0, &recomp_gen::fn_sub_1779A0_001779a0, &recomp_gen::fn_sub_1779A0_001779a0__recomp},
    {"sub_177A40", 0x177A40, &recomp_gen::fn_sub_177A40_00177a40, &recomp_gen::fn_sub_177A40_00177a40__recomp},
    {"sub_177A90", 0x177A90, &recomp_gen::fn_sub_177A90_00177a90, &recomp_gen::fn_sub_177A90_00177a90__recomp},
    {"sub_177B50", 0x177B50, &recomp_gen::fn_sub_177B50_00177b50, &recomp_gen::fn_sub_177B50_00177b50__recomp},
    {"sub_177B90", 0x177B90, &recomp_gen::fn_sub_177B90_00177b90, &recomp_gen::fn_sub_177B90_00177b90__recomp},
    {"sub_177C10", 0x177C10, &recomp_gen::fn_sub_177C10_00177c10, &recomp_gen::fn_sub_177C10_00177c10__recomp},
    {"sub_177C50", 0x177C50, &recomp_gen::fn_sub_177C50_00177c50, &recomp_gen::fn_sub_177C50_00177c50__recomp},
    {"sub_177CA0", 0x177CA0, &recomp_gen::fn_sub_177CA0_00177ca0, &recomp_gen::fn_sub_177CA0_00177ca0__recomp},
    {"sub_177CE0", 0x177CE0, &recomp_gen::fn_sub_177CE0_00177ce0, &recomp_gen::fn_sub_177CE0_00177ce0__recomp},
    {"sub_177D10", 0x177D10, &recomp_gen::fn_sub_177D10_00177d10, &recomp_gen::fn_sub_177D10_00177d10__recomp},
    {"sub_177D40", 0x177D40, &recomp_gen::fn_sub_177D40_00177d40, &recomp_gen::fn_sub_177D40_00177d40__recomp},
    {"sub_17AC60", 0x17AC60, &recomp_gen::fn_sub_17AC60_0017ac60, &recomp_gen::fn_sub_17AC60_0017ac60__recomp},
    {"sub_17AD90", 0x17AD90, &recomp_gen::fn_sub_17AD90_0017ad90, &recomp_gen::fn_sub_17AD90_0017ad90__recomp},
    {"sub_17ADF0", 0x17ADF0, &recomp_gen::fn_sub_17ADF0_0017adf0, &recomp_gen::fn_sub_17ADF0_0017adf0__recomp},
    {"sub_17AE30", 0x17AE30, &recomp_gen::fn_sub_17AE30_0017ae30, &recomp_gen::fn_sub_17AE30_0017ae30__recomp},
    {"sub_17AE50", 0x17AE50, &recomp_gen::fn_sub_17AE50_0017ae50, &recomp_gen::fn_sub_17AE50_0017ae50__recomp},
    {"sub_17AF20", 0x17AF20, &recomp_gen::fn_sub_17AF20_0017af20, &recomp_gen::fn_sub_17AF20_0017af20__recomp},
    {"sub_17AFD0", 0x17AFD0, &recomp_gen::fn_sub_17AFD0_0017afd0, &recomp_gen::fn_sub_17AFD0_0017afd0__recomp},
    {"sub_17B070", 0x17B070, &recomp_gen::fn_sub_17B070_0017b070, &recomp_gen::fn_sub_17B070_0017b070__recomp},
    {"sub_17B100", 0x17B100, &recomp_gen::fn_sub_17B100_0017b100, &recomp_gen::fn_sub_17B100_0017b100__recomp},
    {"sub_17B160", 0x17B160, &recomp_gen::fn_sub_17B160_0017b160, &recomp_gen::fn_sub_17B160_0017b160__recomp},
    {"sub_17B170", 0x17B170, &recomp_gen::fn_sub_17B170_0017b170, &recomp_gen::fn_sub_17B170_0017b170__recomp},
    {"sub_17B180", 0x17B180, &recomp_gen::fn_sub_17B180_0017b180, &recomp_gen::fn_sub_17B180_0017b180__recomp},
    {"sub_17B1A0", 0x17B1A0, &recomp_gen::fn_sub_17B1A0_0017b1a0, &recomp_gen::fn_sub_17B1A0_0017b1a0__recomp},
    {"sub_17B1E0", 0x17B1E0, &recomp_gen::fn_sub_17B1E0_0017b1e0, &recomp_gen::fn_sub_17B1E0_0017b1e0__recomp},
    {"sub_17B220", 0x17B220, &recomp_gen::fn_sub_17B220_0017b220, &recomp_gen::fn_sub_17B220_0017b220__recomp},
    {"sub_17B260", 0x17B260, &recomp_gen::fn_sub_17B260_0017b260, &recomp_gen::fn_sub_17B260_0017b260__recomp},
    {"sub_17B2A0", 0x17B2A0, &recomp_gen::fn_sub_17B2A0_0017b2a0, &recomp_gen::fn_sub_17B2A0_0017b2a0__recomp},
    {"sub_17B2E0", 0x17B2E0, &recomp_gen::fn_sub_17B2E0_0017b2e0, &recomp_gen::fn_sub_17B2E0_0017b2e0__recomp},
    {"sub_17B3D0", 0x17B3D0, &recomp_gen::fn_sub_17B3D0_0017b3d0, &recomp_gen::fn_sub_17B3D0_0017b3d0__recomp},
    {"sub_17B480", 0x17B480, &recomp_gen::fn_sub_17B480_0017b480, &recomp_gen::fn_sub_17B480_0017b480__recomp},
    {"sub_17B4E0", 0x17B4E0, &recomp_gen::fn_sub_17B4E0_0017b4e0, &recomp_gen::fn_sub_17B4E0_0017b4e0__recomp},
    {"sub_17B500", 0x17B500, &recomp_gen::fn_sub_17B500_0017b500, &recomp_gen::fn_sub_17B500_0017b500__recomp},
    {"sub_17B5B0", 0x17B5B0, &recomp_gen::fn_sub_17B5B0_0017b5b0, &recomp_gen::fn_sub_17B5B0_0017b5b0__recomp},
    {"sub_17B660", 0x17B660, &recomp_gen::fn_sub_17B660_0017b660, &recomp_gen::fn_sub_17B660_0017b660__recomp},
    {"sub_17BB40", 0x17BB40, &recomp_gen::fn_sub_17BB40_0017bb40, &recomp_gen::fn_sub_17BB40_0017bb40__recomp},
    {"sub_17BBB0", 0x17BBB0, &recomp_gen::fn_sub_17BBB0_0017bbb0, &recomp_gen::fn_sub_17BBB0_0017bbb0__recomp},
    {"sub_17BC20", 0x17BC20, &recomp_gen::fn_sub_17BC20_0017bc20, &recomp_gen::fn_sub_17BC20_0017bc20__recomp},
    {"sub_17BE10", 0x17BE10, &recomp_gen::fn_sub_17BE10_0017be10, &recomp_gen::fn_sub_17BE10_0017be10__recomp},
    {"sub_17BF70", 0x17BF70, &recomp_gen::fn_sub_17BF70_0017bf70, &recomp_gen::fn_sub_17BF70_0017bf70__recomp},
    {"sub_17BFA0", 0x17BFA0, &recomp_gen::fn_sub_17BFA0_0017bfa0, &recomp_gen::fn_sub_17BFA0_0017bfa0__recomp},
    {"sub_17C070", 0x17C070, &recomp_gen::fn_sub_17C070_0017c070, &recomp_gen::fn_sub_17C070_0017c070__recomp},
    {"sub_17C0E0", 0x17C0E0, &recomp_gen::fn_sub_17C0E0_0017c0e0, &recomp_gen::fn_sub_17C0E0_0017c0e0__recomp},
    {"sub_17C190", 0x17C190, &recomp_gen::fn_sub_17C190_0017c190, &recomp_gen::fn_sub_17C190_0017c190__recomp},
    {"sub_17C1C0", 0x17C1C0, &recomp_gen::fn_sub_17C1C0_0017c1c0, &recomp_gen::fn_sub_17C1C0_0017c1c0__recomp},
    {"sub_17C220", 0x17C220, &recomp_gen::fn_sub_17C220_0017c220, &recomp_gen::fn_sub_17C220_0017c220__recomp},
    {"sub_17C280", 0x17C280, &recomp_gen::fn_sub_17C280_0017c280, &recomp_gen::fn_sub_17C280_0017c280__recomp},
    {"sub_17D7C0", 0x17D7C0, &recomp_gen::fn_sub_17D7C0_0017d7c0, &recomp_gen::fn_sub_17D7C0_0017d7c0__recomp},
    {"sub_17D7F0", 0x17D7F0, &recomp_gen::fn_sub_17D7F0_0017d7f0, &recomp_gen::fn_sub_17D7F0_0017d7f0__recomp},
    {"sub_17DDF0", 0x17DDF0, &recomp_gen::fn_sub_17DDF0_0017ddf0, &recomp_gen::fn_sub_17DDF0_0017ddf0__recomp},
    {"sub_17E050", 0x17E050, &recomp_gen::fn_sub_17E050_0017e050, &recomp_gen::fn_sub_17E050_0017e050__recomp},
    {"sub_17E680", 0x17E680, &recomp_gen::fn_sub_17E680_0017e680, &recomp_gen::fn_sub_17E680_0017e680__recomp},
    {"sub_17F8D0", 0x17F8D0, &recomp_gen::fn_sub_17F8D0_0017f8d0, &recomp_gen::fn_sub_17F8D0_0017f8d0__recomp},
    {"sub_17FA10", 0x17FA10, &recomp_gen::fn_sub_17FA10_0017fa10, &recomp_gen::fn_sub_17FA10_0017fa10__recomp},
    {"sub_17FAA0", 0x17FAA0, &recomp_gen::fn_sub_17FAA0_0017faa0, &recomp_gen::fn_sub_17FAA0_0017faa0__recomp},
    {"sub_17FAD0", 0x17FAD0, &recomp_gen::fn_sub_17FAD0_0017fad0, &recomp_gen::fn_sub_17FAD0_0017fad0__recomp},
    {"sub_17FB90", 0x17FB90, &recomp_gen::fn_sub_17FB90_0017fb90, &recomp_gen::fn_sub_17FB90_0017fb90__recomp},
    {"sub_17FC70", 0x17FC70, &recomp_gen::fn_sub_17FC70_0017fc70, &recomp_gen::fn_sub_17FC70_0017fc70__recomp},
    {"sub_17FE10", 0x17FE10, &recomp_gen::fn_sub_17FE10_0017fe10, &recomp_gen::fn_sub_17FE10_0017fe10__recomp},
    {"sub_180030", 0x180030, &recomp_gen::fn_sub_180030_00180030, &recomp_gen::fn_sub_180030_00180030__recomp},
    {"sub_180220", 0x180220, &recomp_gen::fn_sub_180220_00180220, &recomp_gen::fn_sub_180220_00180220__recomp},
    {"sub_180A20", 0x180A20, &recomp_gen::fn_sub_180A20_00180a20, &recomp_gen::fn_sub_180A20_00180a20__recomp},
    {"sub_180C40", 0x180C40, &recomp_gen::fn_sub_180C40_00180c40, &recomp_gen::fn_sub_180C40_00180c40__recomp},
    {"sub_180E60", 0x180E60, &recomp_gen::fn_sub_180E60_00180e60, &recomp_gen::fn_sub_180E60_00180e60__recomp},
    {"sub_180EE0", 0x180EE0, &recomp_gen::fn_sub_180EE0_00180ee0, &recomp_gen::fn_sub_180EE0_00180ee0__recomp},
    {"sub_181010", 0x181010, &recomp_gen::fn_sub_181010_00181010, &recomp_gen::fn_sub_181010_00181010__recomp},
    {"sub_181170", 0x181170, &recomp_gen::fn_sub_181170_00181170, &recomp_gen::fn_sub_181170_00181170__recomp},
    {"sub_181310", 0x181310, &recomp_gen::fn_sub_181310_00181310, &recomp_gen::fn_sub_181310_00181310__recomp},
    {"sub_181430", 0x181430, &recomp_gen::fn_sub_181430_00181430, &recomp_gen::fn_sub_181430_00181430__recomp},
    {"sub_181580", 0x181580, &recomp_gen::fn_sub_181580_00181580, &recomp_gen::fn_sub_181580_00181580__recomp},
    {"sub_181720", 0x181720, &recomp_gen::fn_sub_181720_00181720, &recomp_gen::fn_sub_181720_00181720__recomp},
    {"sub_181950", 0x181950, &recomp_gen::fn_sub_181950_00181950, &recomp_gen::fn_sub_181950_00181950__recomp},
    {"sub_181B70", 0x181B70, &recomp_gen::fn_sub_181B70_00181b70, &recomp_gen::fn_sub_181B70_00181b70__recomp},
    {"sub_181CC0", 0x181CC0, &recomp_gen::fn_sub_181CC0_00181cc0, &recomp_gen::fn_sub_181CC0_00181cc0__recomp},
    {"sub_182720", 0x182720, &recomp_gen::fn_sub_182720_00182720, &recomp_gen::fn_sub_182720_00182720__recomp},
    {"sub_182750", 0x182750, &recomp_gen::fn_sub_182750_00182750, &recomp_gen::fn_sub_182750_00182750__recomp},
    {"sub_182810", 0x182810, &recomp_gen::fn_sub_182810_00182810, &recomp_gen::fn_sub_182810_00182810__recomp},
    {"sub_1828D0", 0x1828D0, &recomp_gen::fn_sub_1828D0_001828d0, &recomp_gen::fn_sub_1828D0_001828d0__recomp},
    {"sub_182C50", 0x182C50, &recomp_gen::fn_sub_182C50_00182c50, &recomp_gen::fn_sub_182C50_00182c50__recomp},
    {"sub_182D90", 0x182D90, &recomp_gen::fn_sub_182D90_00182d90, &recomp_gen::fn_sub_182D90_00182d90__recomp},
    {"sub_1830C0", 0x1830C0, &recomp_gen::fn_sub_1830C0_001830c0, &recomp_gen::fn_sub_1830C0_001830c0__recomp},
    {"sub_1831E0", 0x1831E0, &recomp_gen::fn_sub_1831E0_001831e0, &recomp_gen::fn_sub_1831E0_001831e0__recomp},
    {"sub_1833E0", 0x1833E0, &recomp_gen::fn_sub_1833E0_001833e0, &recomp_gen::fn_sub_1833E0_001833e0__recomp},
    {"sub_184890", 0x184890, &recomp_gen::fn_sub_184890_00184890, &recomp_gen::fn_sub_184890_00184890__recomp},
    {"H_DayParts_CreateTask", 0x184DB0, &recomp_gen::fn_H_DayParts_CreateTask_00184db0, &recomp_gen::fn_H_DayParts_CreateTask_00184db0__recomp},
    {"sub_184F00", 0x184F00, &recomp_gen::fn_sub_184F00_00184f00, &recomp_gen::fn_sub_184F00_00184f00__recomp},
    {"sub_185830", 0x185830, &recomp_gen::fn_sub_185830_00185830, &recomp_gen::fn_sub_185830_00185830__recomp},
    {"sub_185880", 0x185880, &recomp_gen::fn_sub_185880_00185880, &recomp_gen::fn_sub_185880_00185880__recomp},
    {"sub_185980", 0x185980, &recomp_gen::fn_sub_185980_00185980, &recomp_gen::fn_sub_185980_00185980__recomp},
    {"sub_185AE0", 0x185AE0, &recomp_gen::fn_sub_185AE0_00185ae0, &recomp_gen::fn_sub_185AE0_00185ae0__recomp},
    {"H_DayChgDraw_DrawStrip", 0x185B40, &recomp_gen::fn_H_DayChgDraw_DrawStrip_00185b40, &recomp_gen::fn_H_DayChgDraw_DrawStrip_00185b40__recomp},
    {"sub_186050", 0x186050, &recomp_gen::fn_sub_186050_00186050, &recomp_gen::fn_sub_186050_00186050__recomp},
    {"sub_186100", 0x186100, &recomp_gen::fn_sub_186100_00186100, &recomp_gen::fn_sub_186100_00186100__recomp},
    {"sub_186140", 0x186140, &recomp_gen::fn_sub_186140_00186140, &recomp_gen::fn_sub_186140_00186140__recomp},
    {"sub_186190", 0x186190, &recomp_gen::fn_sub_186190_00186190, &recomp_gen::fn_sub_186190_00186190__recomp},
    {"sub_1868F0", 0x1868F0, &recomp_gen::fn_sub_1868F0_001868f0, &recomp_gen::fn_sub_1868F0_001868f0__recomp},
    {"sub_186960", 0x186960, &recomp_gen::fn_sub_186960_00186960, &recomp_gen::fn_sub_186960_00186960__recomp},
    {"sub_186A40", 0x186A40, &recomp_gen::fn_sub_186A40_00186a40, &recomp_gen::fn_sub_186A40_00186a40__recomp},
    {"sub_186BD0", 0x186BD0, &recomp_gen::fn_sub_186BD0_00186bd0, &recomp_gen::fn_sub_186BD0_00186bd0__recomp},
    {"sub_186D50", 0x186D50, &recomp_gen::fn_sub_186D50_00186d50, &recomp_gen::fn_sub_186D50_00186d50__recomp},
    {"sub_187050", 0x187050, &recomp_gen::fn_sub_187050_00187050, &recomp_gen::fn_sub_187050_00187050__recomp},
    {"sub_1870E0", 0x1870E0, &recomp_gen::fn_sub_1870E0_001870e0, &recomp_gen::fn_sub_1870E0_001870e0__recomp},
    {"sub_1871A0", 0x1871A0, &recomp_gen::fn_sub_1871A0_001871a0, &recomp_gen::fn_sub_1871A0_001871a0__recomp},
    {"sub_187520", 0x187520, &recomp_gen::fn_sub_187520_00187520, &recomp_gen::fn_sub_187520_00187520__recomp},
    {"sub_187550", 0x187550, &recomp_gen::fn_sub_187550_00187550, &recomp_gen::fn_sub_187550_00187550__recomp},
    {"sub_187DF0", 0x187DF0, &recomp_gen::fn_sub_187DF0_00187df0, &recomp_gen::fn_sub_187DF0_00187df0__recomp},
    {"sub_187E20", 0x187E20, &recomp_gen::fn_sub_187E20_00187e20, &recomp_gen::fn_sub_187E20_00187e20__recomp},
    {"sub_187EC0", 0x187EC0, &recomp_gen::fn_sub_187EC0_00187ec0, &recomp_gen::fn_sub_187EC0_00187ec0__recomp},
    {"sub_1883D0", 0x1883D0, &recomp_gen::fn_sub_1883D0_001883d0, &recomp_gen::fn_sub_1883D0_001883d0__recomp},
    {"sub_188440", 0x188440, &recomp_gen::fn_sub_188440_00188440, &recomp_gen::fn_sub_188440_00188440__recomp},
    {"sub_188510", 0x188510, &recomp_gen::fn_sub_188510_00188510, &recomp_gen::fn_sub_188510_00188510__recomp},
    {"sub_1885A0", 0x1885A0, &recomp_gen::fn_sub_1885A0_001885a0, &recomp_gen::fn_sub_1885A0_001885a0__recomp},
    {"nullsub_5", 0x188650, &recomp_gen::fn_nullsub_5_00188650, &recomp_gen::fn_nullsub_5_00188650__recomp},
    {"nullsub_6", 0x188670, &recomp_gen::fn_nullsub_6_00188670, &recomp_gen::fn_nullsub_6_00188670__recomp},
    {"nullsub_7", 0x188680, &recomp_gen::fn_nullsub_7_00188680, &recomp_gen::fn_nullsub_7_00188680__recomp},
    {"clndUpdateBootupCheckMemcardTask", 0x188690, &recomp_gen::fn_clndUpdateBootupCheckMemcardTask_00188690, &recomp_gen::fn_clndUpdateBootupCheckMemcardTask_00188690__recomp},
    {"sub_188830", 0x188830, &recomp_gen::fn_sub_188830_00188830, &recomp_gen::fn_sub_188830_00188830__recomp},
    {"sub_188860", 0x188860, &recomp_gen::fn_sub_188860_00188860, &recomp_gen::fn_sub_188860_00188860__recomp},
    {"sub_188900", 0x188900, &recomp_gen::fn_sub_188900_00188900, &recomp_gen::fn_sub_188900_00188900__recomp},
    {"sub_188B20", 0x188B20, &recomp_gen::fn_sub_188B20_00188b20, &recomp_gen::fn_sub_188B20_00188b20__recomp},
    {"sub_188B50", 0x188B50, &recomp_gen::fn_sub_188B50_00188b50, &recomp_gen::fn_sub_188B50_00188b50__recomp},
    {"sub_188C30", 0x188C30, &recomp_gen::fn_sub_188C30_00188c30, &recomp_gen::fn_sub_188C30_00188c30__recomp},
    {"sub_189230", 0x189230, &recomp_gen::fn_sub_189230_00189230, &recomp_gen::fn_sub_189230_00189230__recomp},
    {"sub_189810", 0x189810, &recomp_gen::fn_sub_189810_00189810, &recomp_gen::fn_sub_189810_00189810__recomp},
    {"sub_189DF0", 0x189DF0, &recomp_gen::fn_sub_189DF0_00189df0, &recomp_gen::fn_sub_189DF0_00189df0__recomp},
};

// The generic sweep's world: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

}  // namespace

TEST_CASE("game(calendar): every body equals its recompiled body on random worlds") {
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
            ++pairs;
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// The real game state
// =====================================================================================================================
namespace {

namespace cal = p3fes::game::calendar;

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u8 r8(Machine& m, u32 va) { return *m.at(va); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
s16 rs16(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
bool flag(Machine& m, s32 f) { return (r32(m, cal::kFlagWords + 4 * static_cast<u32>(f / 32)) >> (f % 32) & 1u) != 0; }
void set_flag(Machine& m, s32 f, bool on) {
    const u32 va = cal::kFlagWords + 4 * static_cast<u32>(f / 32);
    const u32 bit = 1u << (f % 32);
    w32(m, va, on ? (r32(m, va) | bit) : (r32(m, va) & ~bit));
}

constexpr u64 S(s64 v) { return static_cast<u64>(v); }
s64 v0_of(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(r.end.gpr[GPR_V0].u64[0])); }

// Free in every replay snapshot used here and in the ELF image (zero in all four).
constexpr u32 kScratch = 0x01BC0000u;
constexpr u32 kOutA = kScratch + 0x000;     // out words
constexpr u32 kOutB = kScratch + 0x010;
constexpr u32 kTask = kScratch + 0x100;     // a fake KwlnTask (0x68 bytes), +0x3C -> kWork
constexpr u32 kWork = kScratch + 0x200;     // its work (0x200 bytes)
constexpr u32 kHud = kScratch + 0x400;      // a fake day-parts HUD task, +0x3C -> kHudWork
constexpr u32 kHudWork = kScratch + 0x480;
constexpr u32 kPersona = kScratch + 0x600;  // a scratch persona (52 bytes)
constexpr u32 kList = kScratch + 0x680;     // a persona pointer list
constexpr u32 kEntry = kScratch + 0x700;    // a 20-byte equipment entry
constexpr u32 kEvents = kScratch + 0x800;   // the stand-in scheduled-event table: {u32 rows, s32 count}
constexpr u32 kEventRows = kScratch + 0x810;
constexpr u32 kNames = kScratch + 0xC00;    // name strings
constexpr const char* kSnapshots[] = {"climb_ref_17000", "fusion_vr_5000", "shop_ref_4100", "dorm_replay_4900"};

// --- the pair runner ---------------------------------------------------------------------------------------------------
// hgp::pair through two trampolines that give each body a fresh, identical stand-in world, whose call logs must match.
// The calendar world: install_standard plus a recorder for every callee of the slice's bodies that this build does not
// emit (they log the call and return 0, or the value below), and the scheduled-event table getter sub_3BD880 serving
// the table the tests build at kEvents.
u32 g_event_table = 0;  // 0: sub_3BD880 returns 0 (a recorder)

void calendar_world(StandInWorld& w) {
    install_standard(w);
    const std::pair<u32, const char*> rec[] = {
        {0x1005B0u, "H_Cursor_CreateTask"}, {0x191260u, "H_Memcard_UpdateChkAreaSeq"},
        {0x420340u, "Y_McProc_CreateMcProcDrawTask"}, {0x4214E0u, "Y_Misc_CreateMCWNDProcTasks"},
        {0x1BA5F0u, "k_Field_CreateFieldRootTask"}, {0x112370u, "sprAddFile"}, {0x112420u, "sprCreateHandleFromData"},
        {0x1159F0u, "sprDrawSpriteBasic"}, {0x104D10u, "sub_104D10 (debug print)"}, {0x1052B0u, "sub_1052B0 (debug log)"},
        {0x1086D0u, "sub_1086D0"}, {0x108F70u, "sub_108F70"}, {0x109F60u, "sub_109F60"}, {0x10A370u, "sub_10A370"},
        {0x10BDA0u, "sub_10BDA0"}, {0x111CB0u, "sub_111CB0"}, {0x111D50u, "sub_111D50"}, {0x111DD0u, "sub_111DD0"},
        {0x111EC0u, "sub_111EC0"}, {0x111EE0u, "sub_111EE0"}, {0x111F20u, "sub_111F20"}, {0x1124B0u, "sub_1124B0"},
        {0x115BC0u, "sub_115BC0"}, {0x191D10u, "sub_191D10"}, {0x1967D0u, "sub_1967D0"}, {0x1A5CD0u, "sub_1A5CD0"},
        {0x1B7700u, "sub_1B7700"}, {0x3B2CB0u, "sub_3B2CB0"}, {0x3BD890u, "sub_3BD890 (dated conditions)"},
        {0x3BD8A0u, "sub_3BD8A0 (dated flags)"}, {0x3BDD60u, "sub_3BDD60 (script start)"}, {0x4204F0u, "sub_4204F0"},
        {0x4215B0u, "sub_4215B0"}, {0x421650u, "sub_421650"}, {0x421700u, "sub_421700"},
    };
    for (const auto& [va, name] : rec) w.si.install_recorder(va, name, 0);
    if (g_event_table != 0)
        w.si.install(0x3BD880u, "sub_3BD880 (scheduled events)", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = g_event_table; });
    else
        w.si.install_recorder(0x3BD880u, "sub_3BD880 (scheduled events)", 0);
}

struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
};
Tramp g_t;

template <int K>
void tramp(EEContext& c) {
    g_t.world[K] = std::make_unique<StandInWorld>();
    calendar_world(*g_t.world[K]);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

std::map<std::string, int> g_stops;  // early stops by function and reason (reported once)

struct Real {
    Machine& m;
    std::vector<u8> base;
    std::string name;
    int pairs = 0, stops = 0;
    u32 seed = 1;
    void reset() { std::memcpy(m.mem.main_ram(), base.data(), base.size()); }
    hgp::Run call(const char* fn, Args a) {
        const Case& c = find_case(fn);
        g_t.fn[0] = c.hand;
        g_t.fn[1] = c.recomp;
        const std::string what = name + " " + fn;
        hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, ++seed, what.c_str());
        if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
        ++pairs;
        if (r.stopped) {
            ++stops;
            ++g_stops[std::string(fn) + ": " + r.what.substr(0, 90)];
        }
        return r;
    }
    s64 v0(const char* fn, Args a) { return v0_of(call(fn, a)); }
};

std::unique_ptr<Machine> real_machine(const char* snapshot, std::vector<u8>& base) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    write_rw_slots(*m);
    std::memcpy(base.data(), m->mem.main_ram(), base.size());
    return m;
}

// --- the calendar on the host, from the ELF's own tables -----------------------------------------------------------------
struct Host {
    s16 len[12];
    std::set<std::pair<s32, s32>> holidays;
    u8 moon[368];
    explicit Host(Machine& m) {
        for (u32 i = 0; i < 12; ++i) len[i] = rs16(m, cal::kMonthLengths + 2 * i);
        for (u32 i = 0; i < static_cast<u32>(cal::kHolidayScanMax); ++i) {
            const s16 mo = rs16(m, cal::kHolidays + 4 * i);
            if (mo == -1) break;
            holidays.insert({mo, rs16(m, cal::kHolidays + 4 * i + 2)});
        }
        for (u32 i = 0; i < 368; ++i) moon[i] = r8(m, cal::kMoonPhases + i);
    }
    cal::Date date(s32 d) const {
        s32 mo = 4, rem = d + 4;
        while (rem >= len[mo - 1]) {
            rem -= len[mo - 1];
            mo = mo == 12 ? 1 : mo + 1;
        }
        return {mo, rem + 1};
    }
    bool holiday(s32 d) const {  // sub_17DB40: a Sunday or a listed date
        const cal::Date dt = date(d);
        return cal::weekday_of_day(d) == cal::kSunday || holidays.count({dt.month, dt.day}) != 0;
    }
    s32 days_before_month(s32 d) const {  // sub_17E050's running sum: the days from April 1 to the first of d's month
        s32 mo = 4, rem = d + 4, sum = 0;
        while (rem >= len[mo - 1]) {
            rem -= len[mo - 1];
            sum += len[mo - 1];
            mo = mo == 12 ? 1 : mo + 1;
        }
        return sum;
    }
    s32 week_of_month(s32 d) const {  // the Sunday-started week of the month, 0 first
        const s32 sum = days_before_month(d), dom0 = date(d).day - 1;
        s32 wd = (sum + cal::kFirstOfAprilWeekday) % 7, week = 0;
        for (s32 i = 0; i < dom0; ++i)
            if (++wd == 7) {
                ++week;
                wd = 0;
            }
        return week;
    }
};

// The date code rule of sub_17E050 (calendar.h; the function's comment).
bool date_code_matches(const Host& h, s32 d, s32 code, s32 a, s32 b) {
    const s32 wd = cal::weekday_of_day(d);
    if (code == cal::kCodeWeekday) return wd != 0;
    if (code == cal::kCodeHoliday) return h.holiday(d);
    if (code >= 1 && code <= 7) return wd == code - 1;
    if (code == cal::kCodeDate) return a == h.days_before_month(d) && b == h.date(d).day;
    return h.week_of_month(d) == code / 10 - 1 && code % 10 - 1 == wd;
}

// The time-advance rule of the calendar task's state 22 (calendar.h section 2).
struct Now {
    s32 day, slot;
    bool skip;
    bool operator==(const Now&) const = default;
};
Now advance(const Host& h, Now n, s32 skip_day, s32 skip_slot) {
    if (n.skip && (skip_day - n.day >= 6 || (n.day == skip_day && n.slot == skip_slot))) return {skip_day, skip_slot, false};
    if (n.slot == cal::kSlotDarkHour) {
        n.day += 1;
        n.slot = cal::kSlotSouchou;
    } else if (!h.holiday(n.day) && cal::weekday_of_day(n.day) == cal::kSaturday && n.slot == cal::kSlotGozen) {
        n.slot = cal::kSlotHoukago;
    } else if (h.holiday(n.day) && n.slot == cal::kSlotAsa) {
        n.slot = cal::kSlotGogo;
    } else if (h.holiday(n.day) && n.slot == cal::kSlotGogo) {
        n.slot = cal::kSlotYoru;
    } else {
        n.slot += 1;
    }
    if (n.skip && n.day == skip_day && n.slot == skip_slot) n.skip = false;
    return n;
}

void set_now(Machine& m, s32 day, s32 slot) {
    w16(m, cal::kDaysSinceApr5, static_cast<u16>(day));
    w8(m, cal::kTimeSlot, static_cast<u8>(slot));
}

// A fake task whose work starts in `state` (the rest of the work zero), with the day-parts HUD idle (state 2).
void fake_task(Machine& m, u32 state, u32 work_size = 0x200) {
    std::memset(m.at(kTask), 0, 0x68);
    std::memset(m.at(kWork), 0, work_size);
    std::memset(m.at(kHud), 0, 0x68);
    std::memset(m.at(kHudWork), 0, 0x40);
    w32(m, kTask + cal::task::kWork, kWork);
    w32(m, kHud + cal::task::kWork, kHudWork);
    w32(m, kHudWork, 2);
    w32(m, kWork, state);
    w32(m, kWork + cal::task::kDayPartsTask, kHud);
}

// The scheduled-event table at kEvents: rows of 24 bytes.
struct EventRow {
    u8 month, day, slot;
    u16 id = 0;
    u8 major = 0, minor = 0, skip_month = 4, skip_day = 6, skip_slot = 1, comu = 0xFF;
    u16 comu_rank = 0, need1 = 0, need2 = 0, not1 = 0, not2 = 0, done = 0;
};
void write_events(Machine& m, const std::vector<EventRow>& rows) {
    std::memset(m.at(kEventRows), 0, 24 * 16);
    for (u32 i = 0; i < rows.size(); ++i) {
        const u32 r = kEventRows + 24 * i;
        const EventRow& e = rows[i];
        w8(m, r + cal::event::kMonth, e.month);
        w8(m, r + cal::event::kDay, e.day);
        w8(m, r + cal::event::kSlot, e.slot);
        w16(m, r + cal::event::kId, e.id);
        w8(m, r + cal::event::kMajor, e.major);
        w8(m, r + cal::event::kMinor, e.minor);
        w8(m, r + cal::event::kSkipMonth, e.skip_month);
        w8(m, r + cal::event::kSkipDay, e.skip_day);
        w8(m, r + cal::event::kSkipSlot, e.skip_slot);
        w8(m, r + cal::event::kComu, e.comu);
        w16(m, r + cal::event::kComuRank, e.comu_rank);
        w16(m, r + cal::event::kFlagSet1, e.need1);
        w16(m, r + cal::event::kFlagSet2, e.need2);
        w16(m, r + cal::event::kFlagClear1, e.not1);
        w16(m, r + cal::event::kFlagClear2, e.not2);
        w16(m, r + cal::event::kDoneFlag, e.done);
    }
    w32(m, kEvents, kEventRows);
    w32(m, kEvents + 4, static_cast<u32>(rows.size()));
}

// The hero's persona stock slots in use and the held equipment / item ids of a snapshot.
std::vector<u32> held_personas(Machine& m) {
    std::vector<u32> v;
    for (u32 s = 0; s < 12; ++s)
        if (r16(m, 0x836BACu + 52 * s) & 1) v.push_back(0x836BACu + 52 * s);
    return v;
}

// --- every function on its real arguments ----------------------------------------------------------------------------------
void run_all(Real& x, const Host& h) {
    Machine& m = x.m;
    const s32 today = rs16(m, cal::kDaysSinceApr5);
    const s32 slot_now = r8(m, cal::kTimeSlot);
    // the date functions on every day / a sample of the codes
    for (s32 d = 0; d <= cal::kLastDay; d += 3) {
        set_now(m, d, slot_now);
        x.call("sub_17DDF0", {kOutA, kOutB, 0, 0});
        for (s64 code : {101, 100, 1, 7, 13, 26, 37, 51, 0}) x.call("sub_17E050", {S(code), S(h.days_before_month(d)), S(h.date(d).day), 0});
    }
    x.reset();
    // the slot sequences on their own slots, with and without a time skip, on the real calendar task when there is one
    const u32 cal_task = r32(m, 0x7CDFECu);
    for (s32 slot = 0; slot <= cal::kSlotDarkHour; ++slot) {
        for (bool skip : {false, true}) {
            x.reset();
            set_now(m, today, slot);
            w32(m, cal::kSkipActive, skip ? 1u : 0u);
            const u32 task = cal_task != 0 ? cal_task : kTask;
            if (cal_task == 0) fake_task(m, cal::task::kStateAdvance);
            static const char* const kSeq[] = {"sub_180A20", "sub_180C40", "sub_180EE0", "sub_181010", "sub_181170",
                                               "sub_181310", "sub_181430", "sub_17FC70", "sub_181580"};
            x.call(kSeq[slot], {task, kOutA, 0, 0});
        }
    }
    x.reset();
    for (const char* fn : {"sub_180E60", "sub_180030", "sub_180220", "sub_181720", "sub_181B70", "sub_17F8D0", "sub_17FA10"})
        x.call(fn, {kTask, 0, 0, 0});
    x.reset();
    x.call("sub_17FE10", {kTask, 0, 0, 0});
    // the task updates in every state (a fake task, the work zero but for the state)
    const std::pair<const char*, u32> tasks[] = {
        {"sub_17E680", 25}, {"sub_181CC0", 11}, {"sub_184F00", 10}, {"sub_186190", 12}, {"sub_186D50", 5},
        {"sub_1871A0", 2}, {"clndUpdateBootupCheckMemcardTask", 6}, {"sub_188900", 6}, {"sub_188C30", 8},
        {"sub_189230", 8}, {"sub_189810", 8}, {"sub_189DF0", 8},
    };
    for (const auto& [fn, n] : tasks)
        for (u32 st = 0; st < n; ++st) {
            x.reset();
            fake_task(m, st);
            x.call(fn, {kTask, 0, 0, 0});
        }
    // the destroy functions and the creators (the heap and the task kernel run on the stand-ins)
    for (const char* fn : {"sub_17FAA0", "sub_182720", "sub_1833E0", "sub_184890", "sub_185830", "sub_1868F0", "sub_187050",
                           "sub_187520", "sub_187DF0", "sub_1883D0", "sub_188830", "sub_188B20"}) {
        x.reset();
        fake_task(m, 0);
        x.call(fn, {kTask, 0, 0, 0});
    }
    x.reset();
    for (const char* fn : {"sub_17FAD0", "sub_17FB90", "sub_187E20", "sub_188B50"}) x.call(fn, {0, 0, 0, 0});
    for (const char* fn : {"sub_182750", "H_DayParts_CreateTask", "sub_1870E0", "sub_187550", "sub_188860"}) x.call(fn, {cal_task, 0, 0, 0});
    x.call("sub_185880", {cal_task, 4, 6, 4});
    x.call("sub_186960", {cal_task, 1, 2, 0});
    x.call("sub_188440", {cal_task, 3, 31, 7});
    x.reset();
    // the HUD drawers (sprite handle 0: sprDrawSpriteBasic is a recorder)
    for (s64 mo : {4, 5, 12, 1, 3}) {
        x.call("sub_185980", {0, 0, 255, S(mo)});
        x.call("H_DayChgDraw_DrawStrip", {0, 0, 128, S(mo)});
    }
    for (s64 slot = 0; slot <= 8; ++slot) {
        x.call("sub_186A40", {0, 0, 0, S(slot)});
        x.call("sub_186BD0", {0, 0, S(slot == 4 ? 255 : 0), S(slot)});
    }
    for (const char* fn : {"sub_185AE0", "sub_186050", "sub_186100", "sub_186140"}) x.call(fn, {0, 0, 0, 0});
    fake_task(m, 0);
    for (const auto& [mo, dy, sl] : std::vector<std::tuple<s64, s64, s64>>{{3, 31, 4}, {3, 31, 6}, {3, 31, 7}, {4, 2, 7}, {4, 1, 2}, {5, 5, 8}})
        x.call("sub_187EC0", {kTask, S(mo), S(dy), S(sl)});
    x.reset();
    // the scripts' commands (their script state is the snapshot's)
    x.call("sub_1885A0", {0, 0, 0, 0});
    x.call("sub_188510", {0, 0, 0, 0});
    x.reset();
    // personas: the hero's stock
    const std::vector<u32> held = held_personas(m);
    for (u32 p : held) {
        for (s64 lv : {0, 1, 2, 10, 50, 99, 120}) x.call("sub_176210", {p, S(lv), 0, 0});
        x.call("sub_176600", {p, 0, 0, 0});
        x.call("sub_176A30", {p, 0, 0, 0});
        x.call("sub_176990", {p, r16(m, p + 0xC), 0, 0});
        x.call("sub_176990", {p, 0x3FF, 0, 0});
        x.call("sub_1764B0", {p, 10, 0, 0});
        x.call("sub_176C80", {kPersona, p, 0, 0});
        x.call("sub_176D10", {kPersona, p, 0, 0});
        x.call("sub_176FB0", {r16(m, p + 2), kNames, kOutA, 0});
        x.call("sub_1770D0", {r16(m, p + 2), r16(m, p + 0xC), 0, 0});
    }
    if (!held.empty()) {
        for (u32 i = 0; i < held.size(); ++i) w32(m, kList + 4 * i, held[i]);
        std::memcpy(m.at(kPersona), m.at(held[0]), 52);
        x.call("sub_176AC0", {kPersona, kList, held.size(), 0});
    }
    for (s64 id : {1, 46, 100, 0xC1, 0xC8}) {
        std::memset(m.at(kPersona), 0, 52);
        x.call("sub_176680", {kPersona, S(id), 0, 0});
        x.call("sub_176DA0", {kPersona, 0, 0, 0});
        x.call("sub_176840", {kPersona, 0x101, 0, 0});
        x.call("sub_1768E0", {kPersona, 0x101, 0, 0});
        x.call("sub_176510", {kPersona, 0, 0, 0});
    }
    x.reset();
    // names
    x.call("sub_1773D0", {0, 0, 0, 0});
    for (s64 pc : {1, 2, 3, 4, 7, 9, 10, 11, 12}) {
        x.call("sub_1775A0", {S(pc), 0, 0, 0});
        x.call("sub_177670", {S(pc), 0, 0, 0});
        x.call("sub_177790", {S(pc), 0, 0, 0});
        x.call("sub_1778B0", {S(pc), 0, 0, 0});
    }
    x.reset();
    // the record backup entries and words
    x.call("sub_1779A0", {0, 0, 0, 0});
    x.reset();
    for (s64 pc : {2, 3, 7, 10}) {
        for (s64 i : {0, 1, 3}) {
            x.call("sub_177A40", {S(pc), S(i), 0, 0});
            x.call("sub_177A90", {S(pc), S(i), 0, 0});
            x.call("sub_177B90", {S(pc), S(i), S(3 - i), 0});
            x.call("sub_177C10", {S(pc), S(i), 0, 0});
            x.call("sub_177CA0", {S(pc), S(i), 0, 0});
            x.call("sub_177C50", {S(pc), S(i), 0, 0});
            x.call("sub_177B50", {S(pc), S(i), 0, 0});
        }
        x.call("sub_177CE0", {S(pc), 77, 0, 0});
        x.call("sub_177D10", {S(pc), 0, 0, 0});
    }
    x.call("sub_177A90", {S(1), S(4), 0, 0});
    x.reset();
    x.call("sub_177D40", {0, 0, 0, 0});
    x.reset();
    // the dated list
    for (s64 key : {0x00010504, 0x00010504, 0x00020607, 0x00000000})  x.call("sub_17AC60", {S(key), 0, 0, 0});
    for (s64 i : {0, 1, 255}) x.call("sub_17AE30", {S(i), 0, 0, 0});
    x.call("sub_17AD90", {0, 0, 0, 0});
    x.call("sub_17ADF0", {0, 0, 0, 0});
    x.reset();
    // items: held equipment by stock reference, consumables, ids not held
    const u32 stock = r32(m, 0x836794u);
    for (s64 item : {0x8000, 0x8001, 0x8005, 1, 5, 1001, 2003, 4001, 4004, 4010, 4200, 3001}) {
        x.call("sub_17AE50", {S(item), 0, 0, 0});
        x.call("sub_17AFD0", {S(item), 0, 0, 0});
        x.call("sub_17B100", {S(item), 0, 0, 0});
    }
    (void)stock;
    for (s64 item : {4001, 4004, 1, 1001, 2003, 3001}) x.call("sub_17AF20", {S(item), 0, 0, 0});
    for (s64 item : {4001, 4004, 0x8000, 0x8003}) x.call("sub_17B070", {S(item), 0, 0, 0});
    x.reset();
    // equipment entries from the item table
    for (s64 id : {1, 20, 1001, 1020, 2001, 2010, 3001, 4001, 0}) {
        x.call("sub_1828D0", {S(id), kEntry, 0, 0});
        x.call("sub_182C50", {S(id), kEntry, 0, 0});
        x.call("sub_182D90", {S(id), 3, 1, kEntry});
        x.call("sub_182810", {S(id), 0, 0, 0});
    }
    x.call("sub_1830C0", {kEntry, 0, 0, 0});
    x.call("sub_1831E0", {2, 1, kEntry, 0});
    x.reset();
    // the counters and bit arrays
    x.call("sub_17B160", {0, 0, 0, 0});
    x.call("sub_17B180", {5, 0, 0, 0});
    x.call("sub_17B170", {0, 0, 0, 0});
    for (s64 i : {0, 31, 32, 351}) {
        x.call("sub_17B1E0", {S(i), 0, 0, 0});
        x.call("sub_17B260", {S(i), 0, 0, 0});
        x.call("sub_17B220", {S(i), 0, 0, 0});
    }
    for (const auto& [id, j] : std::vector<std::pair<s64, s64>>{{0, 0}, {5, 9}, {335, 3}, {336, 0}, {1, 10}}) {
        x.call("sub_17B2E0", {S(id), S(j), 1, 0});
        x.call("sub_17B3D0", {S(id), S(j), 0, 0});
        x.call("sub_17B2E0", {S(id), S(j), 0, 0});
    }
    x.call("sub_17B1A0", {0, 0, 0, 0});
    x.call("sub_17B2A0", {0, 0, 0, 0});
    x.reset();
    // the skill helpers on party units
    for (s64 sk : {0, 1, 100, 415, 425, 0x1BF, 0x1CF, 0x1D0, 0x26F}) {
        x.call("sub_17B480", {S(sk), 0, 0, 0});
        x.call("sub_17BB40", {S(sk), 0, 0, 0});
        x.call("sub_17BBB0", {S(sk), 0, 0, 0});
        x.call("sub_17BF70", {S(sk), 0, 0, 0});
        x.call("sub_17BFA0", {S(sk), 2, 0, 0});
        x.call("sub_17C070", {S(sk), 0, 0, 0});
        for (s64 pc : {1, 2, 4}) {
            x.call("sub_17B500", {S(pc), S(sk), 0, 0});
            x.call("sub_17B5B0", {S(pc), S(sk), 0, 0});
            x.call("sub_17B660", {S(pc), S(sk), 0, 0});
            x.call("sub_17BC20", {S(pc), 2, S(sk), 0});
        }
    }
    x.call("sub_17B4E0", {100, 0, 0, 0});
    x.call("sub_17BE10", {1, 2, 100, 0});
    for (s64 id : {0, 1, 100, 255}) x.call("sub_17C0E0", {S(id), 0, 0, 0});
    x.reset();
    x.call("sub_17C220", {kOutA, 0, 0, 0});
    x.call("sub_17C1C0", {kOutA, 0, 0, 0});
    x.call("sub_17C190", {0, 0, 0, 0});
    x.call("sub_17C280", {0, 0, 0, 0});
    for (s64 n : {0, 50, 99, 100, 1000}) x.call("sub_17D7C0", {S(n), 0, 0, 0});
    x.call("sub_17D7F0", {0, 0, 0, 0});
    for (const char* fn : {"nullsub_4", "nullsub_5", "nullsub_6", "nullsub_7"}) x.call(fn, {0, 0, 0, 0});
    x.reset();
}

}  // namespace

TEST_CASE("game(calendar): every body equals its recompiled body on the replay snapshots' game state") {
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
        const Host h(*m);
        run_all(x, h);
        MESSAGE(std::string(snap) << " (day " << rs16(*m, cal::kDaysSinceApr5) << "): " << x.pairs << " pairs, " << x.stops
                                  << " stopped early");
    }
    for (const auto& [k, n] : g_stops) MESSAGE("  stopped " << n << "x  " << k);
    if (machines == 0) MESSAGE("SKIP: no replay snapshot");
}

TEST_CASE("game(calendar): the calendar facts of calendar.h against the ELF's tables") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const Host h(*m);
    s32 total = 0;
    for (s32 i = 0; i < 12; ++i) {
        CHECK(h.len[i] == cal::kMonthLen[i]);
        total += h.len[i];
    }
    CHECK(total == 365);
    // the holiday list: 71 dates, in calendar order from April, none a duplicate
    CHECK(h.holidays.size() == 71);
    CHECK(h.holidays.count({4, 29}) == 1);
    CHECK(h.holidays.count({1, 1}) == 1);
    CHECK(h.holidays.count({8, 15}) == 1);
    CHECK(h.holidays.count({3, 22}) == 1);
    CHECK(h.holidays.count({12, 24}) == 0);
    // the host walk equals the inlined one for every day; the year's dates
    for (s32 d = 0; d <= cal::kLastDay; ++d) {
        CHECK(h.date(d).month == cal::date_of_day(d).month);
        CHECK(h.date(d).day == cal::date_of_day(d).day);
        // the inverse (clndGetDaysSinceStartFromDate's walk) holds up to March 31; days 361..364 are April 1..4 again
        // and map back to -4..-1
        if (d <= 360) CHECK(cal::day_of_date(h.date(d).month, h.date(d).day) == d);
        else CHECK(cal::day_of_date(h.date(d).month, h.date(d).day) == d - 365);
    }
    CHECK(cal::weekday_of_day(0) == cal::kSunday);  // April 5, 2009
    CHECK(cal::weekday_of_day(cal::day_of_date(1, 1)) == 5);  // January 1, 2010: a Friday
    // the moon: 0..29, full (14) on the 13 days of the 2009/2010 full moons, new (0) between them
    std::vector<s32> full;
    for (s32 d = 0; d < 368; ++d) {
        CHECK(h.moon[d] < 30);
        if (h.moon[d] == cal::kFullMoon) full.push_back(d);
    }
    CHECK(full == std::vector<s32>{4, 34, 64, 93, 123, 153, 182, 212, 241, 270, 301, 329, 359});
    CHECK(h.date(4).month == 4);
    CHECK(h.date(4).day == 9);
}

TEST_CASE("game(calendar): documented rules -- the next holiday, the date codes, today's event") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    Real x{m, std::move(base), "rules"};
    const Host h(m);
    // sub_17DDF0: the first Sunday or holiday after today, before day 351
    for (s32 d = 0; d <= cal::kLastDay; ++d) {
        x.reset();
        set_now(m, d, 0);
        s32 want = -1;
        for (s32 e = d + 1; e < cal::kNextHolidayLimit; ++e)
            if (h.holiday(e)) {
                want = e;
                break;
            }
        const s64 got = x.v0("sub_17DDF0", {kOutA, kOutB, 0, 0});
        INFO("day " << d);
        CHECK(got == (want >= 0 ? 1 : 0));
        if (want >= 0) {
            CHECK(rs16(m, kOutA) == h.date(want).month);
            CHECK(rs16(m, kOutB) == h.date(want).day);
        }
    }
    // sub_17E050: the date codes on every day (weekday, holiday, the day's own weekday and week codes, a date)
    int matched = 0;
    for (s32 d = 0; d <= cal::kLastDay; ++d) {
        x.reset();
        set_now(m, d, 0);
        const s32 wd = cal::weekday_of_day(d), wk = h.week_of_month(d);
        const s32 a = h.days_before_month(d), b = h.date(d).day;
        std::vector<std::tuple<s32, s32, s32>> codes = {{101, 0, 0}, {100, 0, 0}, {wd + 1, 0, 0}, {(wd + 1) % 7 + 1, 0, 0},
                                                        {10 * (wk + 1) + wd + 1, 0, 0}, {10 * (wk + 2) + wd + 1, 0, 0},
                                                        {0, a, b}, {0, h.date(d).month, b}};
        for (const auto& [code, ca, cb] : codes) {
            INFO("day " << d << " code " << code);
            const bool want = date_code_matches(h, d, code, ca, cb);
            CHECK(x.v0("sub_17E050", {S(code), S(ca), S(cb), 0}) == (want ? 1 : 0));
            matched += want ? 1 : 0;
        }
    }
    MESSAGE("date codes: " << matched << " matches");
    // sub_181720: today's scheduled event on a built table (the getter sub_3BD880 stood in)
    x.reset();
    const s32 today = 16;
    set_now(m, today, cal::kSlotGogo);
    const cal::Date dt = h.date(today);
    const s32 kNeed = 0x15F0, kNot = 0x15F1, kDone2 = 0x15F2, kDone3 = 0x15F3;
    set_flag(m, kNeed, false);
    set_flag(m, kNot, true);
    set_flag(m, kDone2, false);
    set_flag(m, kDone3, false);
    std::vector<EventRow> rows(6);
    rows[0] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day + 1), cal::kSlotGogo};  // another date
    rows[1] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day), cal::kSlotYoru};      // another slot
    rows[2] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day), cal::kSlotGogo};
    rows[2].need1 = static_cast<u16>(kNeed);  // needs a clear flag: not taken
    rows[2].done = static_cast<u16>(kDone2);
    rows[3] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day), cal::kSlotGogo};
    rows[3].not1 = static_cast<u16>(kNot);  // needs a set flag clear: not taken
    rows[4] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day), cal::kSlotGogo};
    rows[4].comu = 0;
    rows[4].comu_rank = 11;  // a rank no link reaches: not taken
    rows[5] = {static_cast<u8>(dt.month), static_cast<u8>(dt.day), cal::kSlotGogo};
    rows[5].done = static_cast<u16>(kDone3);
    write_events(m, rows);
    g_event_table = kEvents;
    CHECK(x.v0("sub_181720", {0, 0, 0, 0}) == 5);
    CHECK(flag(m, kDone3));
    set_flag(m, kNeed, true);  // now row 2 holds
    CHECK(x.v0("sub_181720", {0, 0, 0, 0}) == 2);
    CHECK(flag(m, kDone2));
    set_now(m, today, cal::kSlotDarkHour);  // no row for this slot
    CHECK(x.v0("sub_181720", {0, 0, 0, 0}) == -1);
    // sub_181950 starts row 5 (a field event): the time-skip target becomes the row's date and slot
    x.reset();
    set_now(m, today, cal::kSlotGogo);
    rows[5].skip_month = 5;
    rows[5].skip_day = 6;
    rows[5].skip_slot = cal::kSlotYoru;
    rows[5].minor = 0xFF;  // a script: no HUD call
    write_events(m, rows);
    fake_task(m, 0);
    x.call("sub_181950", {kTask, 5, 0, 0});
    CHECK(r32(m, cal::kSkipActive) == 1u);
    CHECK(rs16(m, cal::kSkipDay) == cal::day_of_date(5, 6));
    CHECK(r8(m, cal::kSkipSlot) == cal::kSlotYoru);
    g_event_table = 0;
}

TEST_CASE("game(calendar): documented rules -- the time-advance rule of the calendar task (state 22)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    Real x{m, std::move(base), "advance"};
    const Host h(m);
    int checked = 0, holidays = 0, saturdays = 0;
    // every day x every slot, no time skip
    for (s32 d = 0; d < cal::kLastDay; ++d)
        for (s32 s = 0; s <= cal::kSlotDarkHour; ++s) {
            x.reset();
            set_now(m, d, s);
            w32(m, cal::kSkipActive, 0);
            fake_task(m, cal::task::kStateAdvance);
            w32(m, kWork + cal::task::kAdvance, 1);
            const s64 v = x.v0("sub_17E680", {kTask, 0, 0, 0});
            const Now want = advance(h, {d, s, false}, 0, 0);
            INFO("day " << d << " slot " << s);
            CHECK(v == 0);
            CHECK(rs16(m, cal::kDaysSinceApr5) == want.day);
            CHECK(r8(m, cal::kTimeSlot) == want.slot);
            CHECK(r32(m, kWork) == 4u);  // -> state 4
            if (s == cal::kSlotAsa) CHECK_FALSE(flag(m, cal::kFlagMorningFirst));  // sub_180E60 cleared the morning flags
            ++checked;
            if (h.holiday(d) && (s == 1 || s == 4)) ++holidays;
            if (!h.holiday(d) && cal::weekday_of_day(d) == cal::kSaturday && s == 2) ++saturdays;
        }
    // the time skip: a target 6+ days ahead or reached jumps and ends the skip; else a normal step, the skip ending
    // when the step lands on the target
    const std::tuple<s32, s32, s32, s32> skips[] = {
        {10, 2, 16, 0}, {10, 2, 30, 8}, {10, 2, 10, 2}, {10, 2, 12, 1}, {10, 2, 10, 3}, {10, 8, 11, 0}, {100, 6, 103, 1},
        {200, 1, 201, 8}, {20, 7, 25, 5}, {20, 7, 26, 5},
    };
    for (const auto& [d, s, td, ts] : skips) {
        x.reset();
        set_now(m, d, s);
        w32(m, cal::kSkipActive, 1);
        w16(m, cal::kSkipDay, static_cast<u16>(td));
        w8(m, cal::kSkipSlot, static_cast<u8>(ts));
        fake_task(m, cal::task::kStateAdvance);
        w32(m, kWork + cal::task::kAdvance, 1);
        x.call("sub_17E680", {kTask, 0, 0, 0});
        const Now want = advance(h, {d, s, true}, td, ts);
        INFO("skip from day " << d << " slot " << s << " to " << td << "/" << ts);
        CHECK(rs16(m, cal::kDaysSinceApr5) == want.day);
        CHECK(r8(m, cal::kTimeSlot) == want.slot);
        CHECK((r32(m, cal::kSkipActive) != 0) == want.skip);
        ++checked;
    }
    // work +0x24 != 1: no step
    x.reset();
    set_now(m, 40, 3);
    fake_task(m, cal::task::kStateAdvance);
    x.call("sub_17E680", {kTask, 0, 0, 0});
    CHECK(rs16(m, cal::kDaysSinceApr5) == 40);
    CHECK(r8(m, cal::kTimeSlot) == 3);
    MESSAGE("time advance: " << checked << " steps checked (" << holidays << " holiday shortcuts, " << saturdays
                             << " school Saturdays)");
}

TEST_CASE("game(calendar): documented rules -- personas, bit arrays, the clamp, the hero's names") {
    std::vector<u8> base;
    auto mp = real_machine("fusion_vr_5000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no fusion_vr_5000 snapshot");
        return;
    }
    Machine& m = *mp;
    Real x{m, std::move(base), "rules2"};
    // the skill list of a scratch persona: add until full, find, remove + pack, count
    std::memset(m.at(kPersona), 0, 52);
    w16(m, kPersona + 2, 46);
    for (s64 i = 0; i < 8; ++i) CHECK(x.v0("sub_176840", {kPersona, S(0x10 + i), 0, 0}) == 1);
    CHECK(x.v0("sub_176840", {kPersona, 0x20, 0, 0}) == 0);  // full
    CHECK(x.v0("sub_176A30", {kPersona, 0, 0, 0}) == 8);
    CHECK(x.v0("sub_176990", {kPersona, 0x13, 0, 0}) == 3);
    CHECK(x.v0("sub_1768E0", {kPersona, 0x13, 0, 0}) == 1);
    CHECK(x.v0("sub_1768E0", {kPersona, 0x13, 0, 0}) == 0);
    CHECK(x.v0("sub_176990", {kPersona, 0x13, 0, 0}) == -1);
    CHECK(x.v0("sub_176990", {kPersona, 0x14, 0, 0}) == 3);  // packed down
    CHECK(r16(m, kPersona + 0xC + 14) == 0);
    CHECK(x.v0("sub_176A30", {kPersona, 0, 0, 0}) == 7);
    // the lock state from flags bits 2 / 3
    for (const auto& [f, want] : std::vector<std::pair<u16, s64>>{{0, 0}, {4, 1}, {0xC, 2}, {8, 0}, {5, 1}}) {
        w16(m, kPersona, f);
        CHECK(x.v0("sub_176600", {kPersona, 0, 0, 0}) == want);
    }
    // the exp of a level: 0 below 2, non-decreasing to 99, clamped above
    for (s64 id : {1, 46, 120}) {
        w16(m, kPersona + 2, static_cast<u16>(id));
        CHECK(x.v0("sub_176210", {kPersona, 0, 0, 0}) == 0);
        CHECK(x.v0("sub_176210", {kPersona, 1, 0, 0}) == 0);
        s64 prev = 0;
        for (s64 lv = 2; lv <= 99; lv += 7) {
            const s64 e = x.v0("sub_176210", {kPersona, S(lv), 0, 0});
            CHECK(e >= prev);
            prev = e;
        }
        CHECK(x.v0("sub_176210", {kPersona, 150, 0, 0}) == x.v0("sub_176210", {kPersona, 99, 0, 0}));
    }
    // exp += n
    w32(m, kPersona + 8, 1000);
    x.call("sub_1764B0", {kPersona, 234, 0, 0});
    CHECK(r32(m, kPersona + 8) == 1234u);
    // the bit arrays
    x.reset();
    for (s64 i : {0, 1, 31, 32, 200, 351}) {
        x.call("sub_17B1E0", {S(i), 0, 0, 0});
        CHECK(x.v0("sub_17B260", {S(i), 0, 0, 0}) != 0);
        x.call("sub_17B220", {S(i), 0, 0, 0});
        CHECK(x.v0("sub_17B260", {S(i), 0, 0, 0}) == 0);
    }
    for (const auto& [id, j] : std::vector<std::pair<s64, s64>>{{0, 0}, {7, 3}, {335, 9}}) {
        x.call("sub_17B2E0", {S(id), S(j), 1, 0});
        CHECK(x.v0("sub_17B3D0", {S(id), S(j), 0, 0}) == 1);
        CHECK((r32(m, 0x83A8F0u + 4 * static_cast<u32>((10 * id + j) / 32)) >> ((10 * id + j) % 32) & 1u) == 1u);
        x.call("sub_17B2E0", {S(id), S(j), 0, 0});
        CHECK(x.v0("sub_17B3D0", {S(id), S(j), 0, 0}) == 0);
    }
    // the 0..99 clamp of 0x83AA98
    for (const auto& [n, want] : std::vector<std::pair<s64, u32>>{{0, 0}, {42, 42}, {99, 99}, {100, 99}, {-1, 99}}) {
        x.call("sub_17D7C0", {S(n), 0, 0, 0});
        CHECK(r32(m, 0x83AA98u) == want);
    }
    // the counter +0x44E8
    x.call("sub_17B160", {0, 0, 0, 0});
    CHECK(x.v0("sub_17B180", {3, 0, 0, 0}) == 3);
    CHECK(x.v0("sub_17B180", {4, 0, 0, 0}) == 7);
    CHECK(x.v0("sub_17B170", {0, 0, 0, 0}) == 7);
    // the hero's names: +0x00 / +0x12 of gGlobalWork, the full name "<+0x12> <+0x00>" through sprintf (stood in)
    x.reset();
    std::memcpy(m.at(kNames), "Minato", 7);
    std::memcpy(m.at(kNames + 0x20), "Arisato", 8);
    x.call("sub_177410", {kNames, kNames + 0x20, 0, 0});
    CHECK(std::string(reinterpret_cast<const char*>(m.at(0x836200u))) == "Minato");
    CHECK(std::string(reinterpret_cast<const char*>(m.at(0x836212u))) == "Arisato");
    CHECK(std::string(reinterpret_cast<const char*>(m.at(0x833BF0u))) == "Arisato Minato");
    w32(m, 0x7CDFA4u, 0);  // The Journey: the hero's name strings
    CHECK(static_cast<u32>(x.v0("sub_1775A0", {1, 0, 0, 0})) == 0x833BF0u);
    CHECK(static_cast<u32>(x.v0("sub_177670", {1, 0, 0, 0})) == 0x833BB0u);
    CHECK(static_cast<u32>(x.v0("sub_177790", {1, 0, 0, 0})) == 0x833BD0u);
    CHECK(static_cast<u32>(x.v0("sub_1778B0", {1, 0, 0, 0})) == 0x833BD0u);
    CHECK(static_cast<u32>(x.v0("sub_1778B0", {3, 0, 0, 0})) == static_cast<u32>(x.v0("sub_177670", {3, 0, 0, 0})));
    // the record backup entries: copy equipment slot 1 of record 3 into backup slot 2, then clear it
    x.reset();
    x.call("sub_177B90", {3, 2, 1, 0});
    const u32 rec3 = 0x834010u + 868u;
    CHECK(std::memcmp(m.at(rec3 + 0x130 + 40), m.at(rec3 + 0x5C + 20), 20) == 0);
    CHECK(static_cast<u32>(x.v0("sub_177A90", {3, 2, 0, 0})) == rec3 + 0x130 + 40);
    CHECK(x.v0("sub_177A40", {3, 2, 0, 0}) == (r16(m, rec3 + 0x5C + 20) != 0 ? 1 : 0));
    x.call("sub_177B50", {3, 2, 0, 0});
    CHECK(x.v0("sub_177A40", {3, 2, 0, 0}) == 0);
    MESSAGE("rules on " << x.pairs << " pairs");
}

#else

TEST_CASE("game(calendar): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
