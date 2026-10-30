// Pair tests for slice libs17 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log.
// Four sets: the skeleton's random worlds; built worlds (an SFD handle with its header object, an SFX converter with
// its Z object, callback record and tables, callbacks into a real non-leaf function for the jalr calls); the same
// worlds over the replay snapshots (the real meter table 0x7833A8, the handle table 0x7B4774, the vsync rate
// 0x7B4728); and rule checks on the results (drop-frame time codes, the Z ramp, the luma-key table, the
// frame-interval tracker, the composition tables, the plane steps, the meter references).
// The error reporter sub_59FD10 and the SFD lock (sub_58C100 / sub_58C118) are recorders (stood in by other tests
// already); the SFD header update, the SFX tag lookup and the converter helpers that packet libs14 claims are emitted
// (_callees), never stood in.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs17.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
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
void fn_sub_5356B8_005356b8(EEContext&);  // generated body
void fn_sub_5356B8_005356b8__recomp(EEContext&);  // recompiled
void fn_sub_535708_00535708(EEContext&);  // generated body
void fn_sub_535708_00535708__recomp(EEContext&);  // recompiled
void fn_sub_535758_00535758(EEContext&);  // generated body
void fn_sub_535758_00535758__recomp(EEContext&);  // recompiled
void fn_sub_5358D8_005358d8(EEContext&);  // generated body
void fn_sub_5358D8_005358d8__recomp(EEContext&);  // recompiled
void fn_sub_535D40_00535d40(EEContext&);  // generated body
void fn_sub_535D40_00535d40__recomp(EEContext&);  // recompiled
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1_00535da0(EEContext&);  // generated body
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1_00535da0__recomp(EEContext&);  // recompiled
void fn_sub_535DB0_00535db0(EEContext&);  // generated body
void fn_sub_535DB0_00535db0__recomp(EEContext&);  // recompiled
void fn_sub_535DB8_00535db8(EEContext&);  // generated body
void fn_sub_535DB8_00535db8__recomp(EEContext&);  // recompiled
void fn_sub_598D90_00598d90(EEContext&);  // generated body
void fn_sub_598D90_00598d90__recomp(EEContext&);  // recompiled
void fn_sub_598E18_00598e18(EEContext&);  // generated body
void fn_sub_598E18_00598e18__recomp(EEContext&);  // recompiled
void fn_sub_598E88_00598e88(EEContext&);  // generated body
void fn_sub_598E88_00598e88__recomp(EEContext&);  // recompiled
void fn_sub_598EE8_00598ee8(EEContext&);  // generated body
void fn_sub_598EE8_00598ee8__recomp(EEContext&);  // recompiled
void fn_sub_598FD8_00598fd8(EEContext&);  // generated body
void fn_sub_598FD8_00598fd8__recomp(EEContext&);  // recompiled
void fn_sub_5990A8_005990a8(EEContext&);  // generated body
void fn_sub_5990A8_005990a8__recomp(EEContext&);  // recompiled
void fn_sub_599590_00599590(EEContext&);  // generated body
void fn_sub_599590_00599590__recomp(EEContext&);  // recompiled
void fn_sub_599808_00599808(EEContext&);  // generated body
void fn_sub_599808_00599808__recomp(EEContext&);  // recompiled
void fn_sub_599AA0_00599aa0(EEContext&);  // generated body
void fn_sub_599AA0_00599aa0__recomp(EEContext&);  // recompiled
void fn_sub_599B40_00599b40(EEContext&);  // generated body
void fn_sub_599B40_00599b40__recomp(EEContext&);  // recompiled
void fn_sub_599EC8_00599ec8(EEContext&);  // generated body
void fn_sub_599EC8_00599ec8__recomp(EEContext&);  // recompiled
void fn_sub_599F28_00599f28(EEContext&);  // generated body
void fn_sub_599F28_00599f28__recomp(EEContext&);  // recompiled
void fn_sub_599FA0_00599fa0(EEContext&);  // generated body
void fn_sub_599FA0_00599fa0__recomp(EEContext&);  // recompiled
void fn_sub_599FB0_00599fb0(EEContext&);  // generated body
void fn_sub_599FB0_00599fb0__recomp(EEContext&);  // recompiled
void fn_sub_59A2E0_0059a2e0(EEContext&);  // generated body
void fn_sub_59A2E0_0059a2e0__recomp(EEContext&);  // recompiled
void fn_sub_59A340_0059a340(EEContext&);  // generated body
void fn_sub_59A340_0059a340__recomp(EEContext&);  // recompiled
void fn_sub_59A360_0059a360(EEContext&);  // generated body
void fn_sub_59A360_0059a360__recomp(EEContext&);  // recompiled
void fn_sub_59A508_0059a508(EEContext&);  // generated body
void fn_sub_59A508_0059a508__recomp(EEContext&);  // recompiled
void fn_sub_59A578_0059a578(EEContext&);  // generated body
void fn_sub_59A578_0059a578__recomp(EEContext&);  // recompiled
void fn_sub_59A6F0_0059a6f0(EEContext&);  // generated body
void fn_sub_59A6F0_0059a6f0__recomp(EEContext&);  // recompiled
void fn_sub_59A778_0059a778(EEContext&);  // generated body
void fn_sub_59A778_0059a778__recomp(EEContext&);  // recompiled
void fn_sub_59AA10_0059aa10(EEContext&);  // generated body
void fn_sub_59AA10_0059aa10__recomp(EEContext&);  // recompiled
void fn_sub_59AAE8_0059aae8(EEContext&);  // generated body
void fn_sub_59AAE8_0059aae8__recomp(EEContext&);  // recompiled
void fn_sub_59AB80_0059ab80(EEContext&);  // generated body
void fn_sub_59AB80_0059ab80__recomp(EEContext&);  // recompiled
void fn_sub_59AC28_0059ac28(EEContext&);  // generated body
void fn_sub_59AC28_0059ac28__recomp(EEContext&);  // recompiled
void fn_sub_59AC88_0059ac88(EEContext&);  // generated body
void fn_sub_59AC88_0059ac88__recomp(EEContext&);  // recompiled
void fn_sub_59ACF0_0059acf0(EEContext&);  // generated body
void fn_sub_59ACF0_0059acf0__recomp(EEContext&);  // recompiled
void fn_sub_59B198_0059b198(EEContext&);  // generated body
void fn_sub_59B198_0059b198__recomp(EEContext&);  // recompiled
void fn_sub_59B300_0059b300(EEContext&);  // generated body
void fn_sub_59B300_0059b300__recomp(EEContext&);  // recompiled
void fn_sub_59B398_0059b398(EEContext&);  // generated body
void fn_sub_59B398_0059b398__recomp(EEContext&);  // recompiled
void fn_sub_59B3A0_0059b3a0(EEContext&);  // generated body
void fn_sub_59B3A0_0059b3a0__recomp(EEContext&);  // recompiled
void fn_sub_59B458_0059b458(EEContext&);  // generated body
void fn_sub_59B458_0059b458__recomp(EEContext&);  // recompiled
void fn_sub_59BE98_0059be98(EEContext&);  // generated body
void fn_sub_59BE98_0059be98__recomp(EEContext&);  // recompiled
void fn_sub_59C3B8_0059c3b8(EEContext&);  // generated body
void fn_sub_59C3B8_0059c3b8__recomp(EEContext&);  // recompiled
void fn_sub_59CC58_0059cc58(EEContext&);  // generated body
void fn_sub_59CC58_0059cc58__recomp(EEContext&);  // recompiled
void fn_sub_59CC60_0059cc60(EEContext&);  // generated body
void fn_sub_59CC60_0059cc60__recomp(EEContext&);  // recompiled
void fn_sub_59CC68_0059cc68(EEContext&);  // generated body
void fn_sub_59CC68_0059cc68__recomp(EEContext&);  // recompiled
void fn_sub_59CC70_0059cc70(EEContext&);  // generated body
void fn_sub_59CC70_0059cc70__recomp(EEContext&);  // recompiled
void fn_sub_59CC90_0059cc90(EEContext&);  // generated body
void fn_sub_59CC90_0059cc90__recomp(EEContext&);  // recompiled
void fn_sub_59CCB0_0059ccb0(EEContext&);  // generated body
void fn_sub_59CCB0_0059ccb0__recomp(EEContext&);  // recompiled
void fn_sub_59CCD0_0059ccd0(EEContext&);  // generated body
void fn_sub_59CCD0_0059ccd0__recomp(EEContext&);  // recompiled
void fn_sub_59CCF0_0059ccf0(EEContext&);  // generated body
void fn_sub_59CCF0_0059ccf0__recomp(EEContext&);  // recompiled
void fn_sub_59CF98_0059cf98(EEContext&);  // generated body
void fn_sub_59CF98_0059cf98__recomp(EEContext&);  // recompiled
void fn_sub_59E918_0059e918(EEContext&);  // generated body
void fn_sub_59E918_0059e918__recomp(EEContext&);  // recompiled
void fn_sub_59E960_0059e960(EEContext&);  // generated body
void fn_sub_59E960_0059e960__recomp(EEContext&);  // recompiled
void fn_sub_59E998_0059e998(EEContext&);  // generated body
void fn_sub_59E998_0059e998__recomp(EEContext&);  // recompiled
void fn_sub_59E9D0_0059e9d0(EEContext&);  // generated body
void fn_sub_59E9D0_0059e9d0__recomp(EEContext&);  // recompiled
void fn_sub_59EA18_0059ea18(EEContext&);  // generated body
void fn_sub_59EA18_0059ea18__recomp(EEContext&);  // recompiled
void fn_sub_59EA50_0059ea50(EEContext&);  // generated body
void fn_sub_59EA50_0059ea50__recomp(EEContext&);  // recompiled
void fn_sub_59EA80_0059ea80(EEContext&);  // generated body
void fn_sub_59EA80_0059ea80__recomp(EEContext&);  // recompiled
void fn_sub_59EAF8_0059eaf8(EEContext&);  // generated body
void fn_sub_59EAF8_0059eaf8__recomp(EEContext&);  // recompiled
void fn_sub_59EBD0_0059ebd0(EEContext&);  // generated body
void fn_sub_59EBD0_0059ebd0__recomp(EEContext&);  // recompiled
void fn_sub_59ED78_0059ed78(EEContext&);  // generated body
void fn_sub_59ED78_0059ed78__recomp(EEContext&);  // recompiled
void fn_sub_59EE38_0059ee38(EEContext&);  // generated body
void fn_sub_59EE38_0059ee38__recomp(EEContext&);  // recompiled
void fn_sub_59EF08_0059ef08(EEContext&);  // generated body
void fn_sub_59EF08_0059ef08__recomp(EEContext&);  // recompiled
void fn_sub_59EF28_0059ef28(EEContext&);  // generated body
void fn_sub_59EF28_0059ef28__recomp(EEContext&);  // recompiled
void fn_sub_59EF48_0059ef48(EEContext&);  // generated body
void fn_sub_59EF48_0059ef48__recomp(EEContext&);  // recompiled
void fn_sub_59EF68_0059ef68(EEContext&);  // generated body
void fn_sub_59EF68_0059ef68__recomp(EEContext&);  // recompiled
void fn_sub_59EF90_0059ef90(EEContext&);  // generated body
void fn_sub_59EF90_0059ef90__recomp(EEContext&);  // recompiled
void fn_sub_59F008_0059f008(EEContext&);  // generated body
void fn_sub_59F008_0059f008__recomp(EEContext&);  // recompiled
void fn_sub_59F080_0059f080(EEContext&);  // generated body
void fn_sub_59F080_0059f080__recomp(EEContext&);  // recompiled
void fn_sub_59F0C8_0059f0c8(EEContext&);  // generated body
void fn_sub_59F0C8_0059f0c8__recomp(EEContext&);  // recompiled
void fn_sub_59F518_0059f518(EEContext&);  // generated body
void fn_sub_59F518_0059f518__recomp(EEContext&);  // recompiled
void fn_sub_59F6C8_0059f6c8(EEContext&);  // generated body
void fn_sub_59F6C8_0059f6c8__recomp(EEContext&);  // recompiled
void fn_sub_59F740_0059f740(EEContext&);  // generated body
void fn_sub_59F740_0059f740__recomp(EEContext&);  // recompiled
void fn_sub_59F7E8_0059f7e8(EEContext&);  // generated body
void fn_sub_59F7E8_0059f7e8__recomp(EEContext&);  // recompiled
void fn_sub_59FDC0_0059fdc0(EEContext&);  // generated body
void fn_sub_59FDC0_0059fdc0__recomp(EEContext&);  // recompiled
void fn_sub_59FDF0_0059fdf0(EEContext&);  // generated body
void fn_sub_59FDF0_0059fdf0__recomp(EEContext&);  // recompiled
void fn_sub_59FE60_0059fe60(EEContext&);  // generated body
void fn_sub_59FE60_0059fe60__recomp(EEContext&);  // recompiled
void fn_sub_59FF48_0059ff48(EEContext&);  // generated body
void fn_sub_59FF48_0059ff48__recomp(EEContext&);  // recompiled
void fn_sub_59FF60_0059ff60(EEContext&);  // generated body
void fn_sub_59FF60_0059ff60__recomp(EEContext&);  // recompiled
void fn_sub_59FF78_0059ff78(EEContext&);  // generated body
void fn_sub_59FF78_0059ff78__recomp(EEContext&);  // recompiled
void fn_sub_59FF98_0059ff98(EEContext&);  // generated body
void fn_sub_59FF98_0059ff98__recomp(EEContext&);  // recompiled
void fn_sub_59FFB0_0059ffb0(EEContext&);  // generated body
void fn_sub_59FFB0_0059ffb0__recomp(EEContext&);  // recompiled
void fn_sub_5A0008_005a0008(EEContext&);  // generated body
void fn_sub_5A0008_005a0008__recomp(EEContext&);  // recompiled
void fn_sub_5A00B0_005a00b0(EEContext&);  // generated body
void fn_sub_5A00B0_005a00b0__recomp(EEContext&);  // recompiled
void fn_sub_5A0188_005a0188(EEContext&);  // generated body
void fn_sub_5A0188_005a0188__recomp(EEContext&);  // recompiled
void fn_sub_5A01B0_005a01b0(EEContext&);  // generated body
void fn_sub_5A01B0_005a01b0__recomp(EEContext&);  // recompiled
void fn_sub_5A0208_005a0208(EEContext&);  // generated body
void fn_sub_5A0208_005a0208__recomp(EEContext&);  // recompiled
void fn_sub_5A0220_005a0220(EEContext&);  // generated body
void fn_sub_5A0220_005a0220__recomp(EEContext&);  // recompiled
void fn_sub_5A0250_005a0250(EEContext&);  // generated body
void fn_sub_5A0250_005a0250__recomp(EEContext&);  // recompiled
void fn_sub_5A02C0_005a02c0(EEContext&);  // generated body
void fn_sub_5A02C0_005a02c0__recomp(EEContext&);  // recompiled
void fn_sub_5A03B0_005a03b0(EEContext&);  // generated body
void fn_sub_5A03B0_005a03b0__recomp(EEContext&);  // recompiled
void fn_sub_5A0608_005a0608(EEContext&);  // generated body
void fn_sub_5A0608_005a0608__recomp(EEContext&);  // recompiled
void fn_sub_5A0688_005a0688(EEContext&);  // generated body
void fn_sub_5A0688_005a0688__recomp(EEContext&);  // recompiled
void fn_sub_5A07E0_005a07e0(EEContext&);  // generated body
void fn_sub_5A07E0_005a07e0__recomp(EEContext&);  // recompiled
void fn_sub_5A0830_005a0830(EEContext&);  // generated body
void fn_sub_5A0830_005a0830__recomp(EEContext&);  // recompiled
void fn_sub_5A0B00_005a0b00(EEContext&);  // generated body
void fn_sub_5A0B00_005a0b00__recomp(EEContext&);  // recompiled
void fn_sub_5A0B68_005a0b68(EEContext&);  // generated body
void fn_sub_5A0B68_005a0b68__recomp(EEContext&);  // recompiled
void fn___errno_15_005a0bf0(EEContext&);  // generated body
void fn___errno_15_005a0bf0__recomp(EEContext&);  // recompiled
void fn_sub_5A1088_005a1088(EEContext&);  // generated body
void fn_sub_5A1088_005a1088__recomp(EEContext&);  // recompiled
void fn_sub_5A1778_005a1778(EEContext&);  // generated body
void fn_sub_5A1778_005a1778__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_5356B8", 0x5356B8, &recomp_gen::fn_sub_5356B8_005356b8, &recomp_gen::fn_sub_5356B8_005356b8__recomp},
    {"sub_535708", 0x535708, &recomp_gen::fn_sub_535708_00535708, &recomp_gen::fn_sub_535708_00535708__recomp},
    {"sub_535758", 0x535758, &recomp_gen::fn_sub_535758_00535758, &recomp_gen::fn_sub_535758_00535758__recomp},
    {"sub_5358D8", 0x5358D8, &recomp_gen::fn_sub_5358D8_005358d8, &recomp_gen::fn_sub_5358D8_005358d8__recomp},
    {"sub_535D40", 0x535D40, &recomp_gen::fn_sub_535D40_00535d40, &recomp_gen::fn_sub_535D40_00535d40__recomp},
    {"_ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1", 0x535DA0, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1_00535da0, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1_00535da0__recomp},
    {"sub_535DB0", 0x535DB0, &recomp_gen::fn_sub_535DB0_00535db0, &recomp_gen::fn_sub_535DB0_00535db0__recomp},
    {"sub_535DB8", 0x535DB8, &recomp_gen::fn_sub_535DB8_00535db8, &recomp_gen::fn_sub_535DB8_00535db8__recomp},
    {"sub_598D90", 0x598D90, &recomp_gen::fn_sub_598D90_00598d90, &recomp_gen::fn_sub_598D90_00598d90__recomp},
    {"sub_598E18", 0x598E18, &recomp_gen::fn_sub_598E18_00598e18, &recomp_gen::fn_sub_598E18_00598e18__recomp},
    {"sub_598E88", 0x598E88, &recomp_gen::fn_sub_598E88_00598e88, &recomp_gen::fn_sub_598E88_00598e88__recomp},
    {"sub_598EE8", 0x598EE8, &recomp_gen::fn_sub_598EE8_00598ee8, &recomp_gen::fn_sub_598EE8_00598ee8__recomp},
    {"sub_598FD8", 0x598FD8, &recomp_gen::fn_sub_598FD8_00598fd8, &recomp_gen::fn_sub_598FD8_00598fd8__recomp},
    {"sub_5990A8", 0x5990A8, &recomp_gen::fn_sub_5990A8_005990a8, &recomp_gen::fn_sub_5990A8_005990a8__recomp},
    {"sub_599590", 0x599590, &recomp_gen::fn_sub_599590_00599590, &recomp_gen::fn_sub_599590_00599590__recomp},
    {"sub_599808", 0x599808, &recomp_gen::fn_sub_599808_00599808, &recomp_gen::fn_sub_599808_00599808__recomp},
    {"sub_599AA0", 0x599AA0, &recomp_gen::fn_sub_599AA0_00599aa0, &recomp_gen::fn_sub_599AA0_00599aa0__recomp},
    {"sub_599B40", 0x599B40, &recomp_gen::fn_sub_599B40_00599b40, &recomp_gen::fn_sub_599B40_00599b40__recomp},
    {"sub_599EC8", 0x599EC8, &recomp_gen::fn_sub_599EC8_00599ec8, &recomp_gen::fn_sub_599EC8_00599ec8__recomp},
    {"sub_599F28", 0x599F28, &recomp_gen::fn_sub_599F28_00599f28, &recomp_gen::fn_sub_599F28_00599f28__recomp},
    {"sub_599FA0", 0x599FA0, &recomp_gen::fn_sub_599FA0_00599fa0, &recomp_gen::fn_sub_599FA0_00599fa0__recomp},
    {"sub_599FB0", 0x599FB0, &recomp_gen::fn_sub_599FB0_00599fb0, &recomp_gen::fn_sub_599FB0_00599fb0__recomp},
    {"sub_59A2E0", 0x59A2E0, &recomp_gen::fn_sub_59A2E0_0059a2e0, &recomp_gen::fn_sub_59A2E0_0059a2e0__recomp},
    {"sub_59A340", 0x59A340, &recomp_gen::fn_sub_59A340_0059a340, &recomp_gen::fn_sub_59A340_0059a340__recomp},
    {"sub_59A360", 0x59A360, &recomp_gen::fn_sub_59A360_0059a360, &recomp_gen::fn_sub_59A360_0059a360__recomp},
    {"sub_59A508", 0x59A508, &recomp_gen::fn_sub_59A508_0059a508, &recomp_gen::fn_sub_59A508_0059a508__recomp},
    {"sub_59A578", 0x59A578, &recomp_gen::fn_sub_59A578_0059a578, &recomp_gen::fn_sub_59A578_0059a578__recomp},
    {"sub_59A6F0", 0x59A6F0, &recomp_gen::fn_sub_59A6F0_0059a6f0, &recomp_gen::fn_sub_59A6F0_0059a6f0__recomp},
    {"sub_59A778", 0x59A778, &recomp_gen::fn_sub_59A778_0059a778, &recomp_gen::fn_sub_59A778_0059a778__recomp},
    {"sub_59AA10", 0x59AA10, &recomp_gen::fn_sub_59AA10_0059aa10, &recomp_gen::fn_sub_59AA10_0059aa10__recomp},
    {"sub_59AAE8", 0x59AAE8, &recomp_gen::fn_sub_59AAE8_0059aae8, &recomp_gen::fn_sub_59AAE8_0059aae8__recomp},
    {"sub_59AB80", 0x59AB80, &recomp_gen::fn_sub_59AB80_0059ab80, &recomp_gen::fn_sub_59AB80_0059ab80__recomp},
    {"sub_59AC28", 0x59AC28, &recomp_gen::fn_sub_59AC28_0059ac28, &recomp_gen::fn_sub_59AC28_0059ac28__recomp},
    {"sub_59AC88", 0x59AC88, &recomp_gen::fn_sub_59AC88_0059ac88, &recomp_gen::fn_sub_59AC88_0059ac88__recomp},
    {"sub_59ACF0", 0x59ACF0, &recomp_gen::fn_sub_59ACF0_0059acf0, &recomp_gen::fn_sub_59ACF0_0059acf0__recomp},
    {"sub_59B198", 0x59B198, &recomp_gen::fn_sub_59B198_0059b198, &recomp_gen::fn_sub_59B198_0059b198__recomp},
    {"sub_59B300", 0x59B300, &recomp_gen::fn_sub_59B300_0059b300, &recomp_gen::fn_sub_59B300_0059b300__recomp},
    {"sub_59B398", 0x59B398, &recomp_gen::fn_sub_59B398_0059b398, &recomp_gen::fn_sub_59B398_0059b398__recomp},
    {"sub_59B3A0", 0x59B3A0, &recomp_gen::fn_sub_59B3A0_0059b3a0, &recomp_gen::fn_sub_59B3A0_0059b3a0__recomp},
    {"sub_59B458", 0x59B458, &recomp_gen::fn_sub_59B458_0059b458, &recomp_gen::fn_sub_59B458_0059b458__recomp},
    {"sub_59BE98", 0x59BE98, &recomp_gen::fn_sub_59BE98_0059be98, &recomp_gen::fn_sub_59BE98_0059be98__recomp},
    {"sub_59C3B8", 0x59C3B8, &recomp_gen::fn_sub_59C3B8_0059c3b8, &recomp_gen::fn_sub_59C3B8_0059c3b8__recomp},
    {"sub_59CC58", 0x59CC58, &recomp_gen::fn_sub_59CC58_0059cc58, &recomp_gen::fn_sub_59CC58_0059cc58__recomp},
    {"sub_59CC60", 0x59CC60, &recomp_gen::fn_sub_59CC60_0059cc60, &recomp_gen::fn_sub_59CC60_0059cc60__recomp},
    {"sub_59CC68", 0x59CC68, &recomp_gen::fn_sub_59CC68_0059cc68, &recomp_gen::fn_sub_59CC68_0059cc68__recomp},
    {"sub_59CC70", 0x59CC70, &recomp_gen::fn_sub_59CC70_0059cc70, &recomp_gen::fn_sub_59CC70_0059cc70__recomp},
    {"sub_59CC90", 0x59CC90, &recomp_gen::fn_sub_59CC90_0059cc90, &recomp_gen::fn_sub_59CC90_0059cc90__recomp},
    {"sub_59CCB0", 0x59CCB0, &recomp_gen::fn_sub_59CCB0_0059ccb0, &recomp_gen::fn_sub_59CCB0_0059ccb0__recomp},
    {"sub_59CCD0", 0x59CCD0, &recomp_gen::fn_sub_59CCD0_0059ccd0, &recomp_gen::fn_sub_59CCD0_0059ccd0__recomp},
    {"sub_59CCF0", 0x59CCF0, &recomp_gen::fn_sub_59CCF0_0059ccf0, &recomp_gen::fn_sub_59CCF0_0059ccf0__recomp},
    {"sub_59CF98", 0x59CF98, &recomp_gen::fn_sub_59CF98_0059cf98, &recomp_gen::fn_sub_59CF98_0059cf98__recomp},
    {"sub_59E918", 0x59E918, &recomp_gen::fn_sub_59E918_0059e918, &recomp_gen::fn_sub_59E918_0059e918__recomp},
    {"sub_59E960", 0x59E960, &recomp_gen::fn_sub_59E960_0059e960, &recomp_gen::fn_sub_59E960_0059e960__recomp},
    {"sub_59E998", 0x59E998, &recomp_gen::fn_sub_59E998_0059e998, &recomp_gen::fn_sub_59E998_0059e998__recomp},
    {"sub_59E9D0", 0x59E9D0, &recomp_gen::fn_sub_59E9D0_0059e9d0, &recomp_gen::fn_sub_59E9D0_0059e9d0__recomp},
    {"sub_59EA18", 0x59EA18, &recomp_gen::fn_sub_59EA18_0059ea18, &recomp_gen::fn_sub_59EA18_0059ea18__recomp},
    {"sub_59EA50", 0x59EA50, &recomp_gen::fn_sub_59EA50_0059ea50, &recomp_gen::fn_sub_59EA50_0059ea50__recomp},
    {"sub_59EA80", 0x59EA80, &recomp_gen::fn_sub_59EA80_0059ea80, &recomp_gen::fn_sub_59EA80_0059ea80__recomp},
    {"sub_59EAF8", 0x59EAF8, &recomp_gen::fn_sub_59EAF8_0059eaf8, &recomp_gen::fn_sub_59EAF8_0059eaf8__recomp},
    {"sub_59EBD0", 0x59EBD0, &recomp_gen::fn_sub_59EBD0_0059ebd0, &recomp_gen::fn_sub_59EBD0_0059ebd0__recomp},
    {"sub_59ED78", 0x59ED78, &recomp_gen::fn_sub_59ED78_0059ed78, &recomp_gen::fn_sub_59ED78_0059ed78__recomp},
    {"sub_59EE38", 0x59EE38, &recomp_gen::fn_sub_59EE38_0059ee38, &recomp_gen::fn_sub_59EE38_0059ee38__recomp},
    {"sub_59EF08", 0x59EF08, &recomp_gen::fn_sub_59EF08_0059ef08, &recomp_gen::fn_sub_59EF08_0059ef08__recomp},
    {"sub_59EF28", 0x59EF28, &recomp_gen::fn_sub_59EF28_0059ef28, &recomp_gen::fn_sub_59EF28_0059ef28__recomp},
    {"sub_59EF48", 0x59EF48, &recomp_gen::fn_sub_59EF48_0059ef48, &recomp_gen::fn_sub_59EF48_0059ef48__recomp},
    {"sub_59EF68", 0x59EF68, &recomp_gen::fn_sub_59EF68_0059ef68, &recomp_gen::fn_sub_59EF68_0059ef68__recomp},
    {"sub_59EF90", 0x59EF90, &recomp_gen::fn_sub_59EF90_0059ef90, &recomp_gen::fn_sub_59EF90_0059ef90__recomp},
    {"sub_59F008", 0x59F008, &recomp_gen::fn_sub_59F008_0059f008, &recomp_gen::fn_sub_59F008_0059f008__recomp},
    {"sub_59F080", 0x59F080, &recomp_gen::fn_sub_59F080_0059f080, &recomp_gen::fn_sub_59F080_0059f080__recomp},
    {"sub_59F0C8", 0x59F0C8, &recomp_gen::fn_sub_59F0C8_0059f0c8, &recomp_gen::fn_sub_59F0C8_0059f0c8__recomp},
    {"sub_59F518", 0x59F518, &recomp_gen::fn_sub_59F518_0059f518, &recomp_gen::fn_sub_59F518_0059f518__recomp},
    {"sub_59F6C8", 0x59F6C8, &recomp_gen::fn_sub_59F6C8_0059f6c8, &recomp_gen::fn_sub_59F6C8_0059f6c8__recomp},
    {"sub_59F740", 0x59F740, &recomp_gen::fn_sub_59F740_0059f740, &recomp_gen::fn_sub_59F740_0059f740__recomp},
    {"sub_59F7E8", 0x59F7E8, &recomp_gen::fn_sub_59F7E8_0059f7e8, &recomp_gen::fn_sub_59F7E8_0059f7e8__recomp},
    {"sub_59FDC0", 0x59FDC0, &recomp_gen::fn_sub_59FDC0_0059fdc0, &recomp_gen::fn_sub_59FDC0_0059fdc0__recomp},
    {"sub_59FDF0", 0x59FDF0, &recomp_gen::fn_sub_59FDF0_0059fdf0, &recomp_gen::fn_sub_59FDF0_0059fdf0__recomp},
    {"sub_59FE60", 0x59FE60, &recomp_gen::fn_sub_59FE60_0059fe60, &recomp_gen::fn_sub_59FE60_0059fe60__recomp},
    {"sub_59FF48", 0x59FF48, &recomp_gen::fn_sub_59FF48_0059ff48, &recomp_gen::fn_sub_59FF48_0059ff48__recomp},
    {"sub_59FF60", 0x59FF60, &recomp_gen::fn_sub_59FF60_0059ff60, &recomp_gen::fn_sub_59FF60_0059ff60__recomp},
    {"sub_59FF78", 0x59FF78, &recomp_gen::fn_sub_59FF78_0059ff78, &recomp_gen::fn_sub_59FF78_0059ff78__recomp},
    {"sub_59FF98", 0x59FF98, &recomp_gen::fn_sub_59FF98_0059ff98, &recomp_gen::fn_sub_59FF98_0059ff98__recomp},
    {"sub_59FFB0", 0x59FFB0, &recomp_gen::fn_sub_59FFB0_0059ffb0, &recomp_gen::fn_sub_59FFB0_0059ffb0__recomp},
    {"sub_5A0008", 0x5A0008, &recomp_gen::fn_sub_5A0008_005a0008, &recomp_gen::fn_sub_5A0008_005a0008__recomp},
    {"sub_5A00B0", 0x5A00B0, &recomp_gen::fn_sub_5A00B0_005a00b0, &recomp_gen::fn_sub_5A00B0_005a00b0__recomp},
    {"sub_5A0188", 0x5A0188, &recomp_gen::fn_sub_5A0188_005a0188, &recomp_gen::fn_sub_5A0188_005a0188__recomp},
    {"sub_5A01B0", 0x5A01B0, &recomp_gen::fn_sub_5A01B0_005a01b0, &recomp_gen::fn_sub_5A01B0_005a01b0__recomp},
    {"sub_5A0208", 0x5A0208, &recomp_gen::fn_sub_5A0208_005a0208, &recomp_gen::fn_sub_5A0208_005a0208__recomp},
    {"sub_5A0220", 0x5A0220, &recomp_gen::fn_sub_5A0220_005a0220, &recomp_gen::fn_sub_5A0220_005a0220__recomp},
    {"sub_5A0250", 0x5A0250, &recomp_gen::fn_sub_5A0250_005a0250, &recomp_gen::fn_sub_5A0250_005a0250__recomp},
    {"sub_5A02C0", 0x5A02C0, &recomp_gen::fn_sub_5A02C0_005a02c0, &recomp_gen::fn_sub_5A02C0_005a02c0__recomp},
    {"sub_5A03B0", 0x5A03B0, &recomp_gen::fn_sub_5A03B0_005a03b0, &recomp_gen::fn_sub_5A03B0_005a03b0__recomp},
    {"sub_5A0608", 0x5A0608, &recomp_gen::fn_sub_5A0608_005a0608, &recomp_gen::fn_sub_5A0608_005a0608__recomp},
    {"sub_5A0688", 0x5A0688, &recomp_gen::fn_sub_5A0688_005a0688, &recomp_gen::fn_sub_5A0688_005a0688__recomp},
    {"sub_5A07E0", 0x5A07E0, &recomp_gen::fn_sub_5A07E0_005a07e0, &recomp_gen::fn_sub_5A07E0_005a07e0__recomp},
    {"sub_5A0830", 0x5A0830, &recomp_gen::fn_sub_5A0830_005a0830, &recomp_gen::fn_sub_5A0830_005a0830__recomp},
    {"sub_5A0B00", 0x5A0B00, &recomp_gen::fn_sub_5A0B00_005a0b00, &recomp_gen::fn_sub_5A0B00_005a0b00__recomp},
    {"sub_5A0B68", 0x5A0B68, &recomp_gen::fn_sub_5A0B68_005a0b68, &recomp_gen::fn_sub_5A0B68_005a0b68__recomp},
    {"__errno_15", 0x5A0BF0, &recomp_gen::fn___errno_15_005a0bf0, &recomp_gen::fn___errno_15_005a0bf0__recomp},
    {"sub_5A1088", 0x5A1088, &recomp_gen::fn_sub_5A1088_005a1088, &recomp_gen::fn_sub_5A1088_005a1088__recomp},
    {"sub_5A1778", 0x5A1778, &recomp_gen::fn_sub_5A1778_005a1778, &recomp_gen::fn_sub_5A1778_005a1778__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs17): every body equals its recompiled body on random worlds") {
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

namespace {

namespace L = p3fes::game::libs17;

// The built world: an SFD handle (kHandle, 0x37D0 bytes and its header object at kHdr), an SFX converter (kSfx)
// with its Z object (kZ), callback record (kCb), 256-byte table (kTab8) and a 2 KiB Z table area (kZTab), and
// scratch output words (kOut). Every other word is drawn from the values the bodies compare against or is a pointer
// into the world.
constexpr u32 kBase = 0x01820000u;
constexpr u32 kSpan = 0x10000u;
constexpr u32 kHandle = kBase;
constexpr u32 kHdr = kBase + 0x4000u;
constexpr u32 kSfx = kBase + 0x8000u;
constexpr u32 kZ = kBase + 0x8400u;
constexpr u32 kCb = kBase + 0x8800u;
constexpr u32 kTab8 = kBase + 0x8C00u;
constexpr u32 kOut = kBase + 0x9000u;
constexpr u32 kZTab = kBase + 0xA000u;  // 1 KiB output + 1 KiB ramp
constexpr u32 kNonLeaf = 0x59A340u;     // sub_59A340: non-leaf ($ra spilled below the $sp it gets), runs to its return

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void wf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }

u32 enum_word(std::mt19937& rng) {
    static const u32 kValues[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 16u, 17u, 21u, 24u, 32u, 33u, 49u, 65u, 81u, 97u, 100u,
                                  113u, 241u, 257u, 273u, 4097u, 0xFFFFFFFFu, 0xFFFFFFFDu, 0xFFFFFFFBu, 0x7FFFFFFFu,
                                  0x80000000u, 1000u, 29970u, 59940u, 90000u};
    const u32 k = rng() % 8;
    if (k < 5) return kValues[rng() % (sizeof kValues / sizeof kValues[0])];
    if (k < 7) return kBase + ((rng() % kSpan) & ~3u);
    return rng() % 0x10000u;
}

u32 callback(std::mt19937& rng) { return rng() % 3 == 0 ? 0u : kNonLeaf; }

float small_float(std::mt19937& rng) { return static_cast<float>(static_cast<int>(rng() % 4001) - 2000) / 16.0f; }

void build_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= kSpan; i += 4) w32(m, kBase + i, enum_word(rng));
    // the SFD handle: valid word, API mode, header object, time record, parameters, time-source state
    w32(m, kHandle + 72, rng() % 4 == 0 ? 0u : 1u + rng() % 6);
    w32(m, kHandle + 76, rng() % 2 ? 4u : rng() % 4);
    w32(m, kHandle + 14000, rng() % 4 == 0 ? 0u : kHdr);
    w32(m, kHandle + 4100, callback(rng));
    w32(m, kHandle + 4104, rng() % 3 == 0 ? 0xFFFFFFFBu : rng() % 5000);
    w32(m, kHandle + 4116, 0xFFFFu);
    w32(m, kHandle + 4092, rng() % 3 == 0 ? 0xFFFFFFFFu : rng() % 100000);
    w32(m, kHandle + 4012, rng() % 3 == 0 ? 0xFFFFFFFBu : rng() % 100000);
    w32(m, kHandle + 4016, rng() % 60000);
    w32(m, kHandle + 8004, rng() % 4);
    for (u32 s = 0; s < 4; ++s) w32(m, kHandle + 4880 + 116 * s + 80, rng() % 9);
    for (u32 t = 0; t < 9; ++t) w32(m, kHandle + 7984 + 68 * t + 32, rng() % 3 == 0 ? 0xFFFFFFFFu : rng() % 500);
    w32(m, kHandle + 2572 + 4 * 49, rng() % 2);
    w32(m, kHandle + 2572 + 4 * 71, rng() % 2);
    // the frame-interval tracker words (+660..+672)
    w32(m, kHandle + 660, rng() % 3 == 0 ? 0xFFFFFFFBu : rng() % 10000);
    w32(m, kHandle + 664, rng() % 3 == 0 ? 0x7FFFFFFFu : rng() % 200);
    // the SFX converter
    static const u32 kCompo[] = {17u, 33u, 49u, 65u, 81u, 97u, 113u, 241u, 257u, 273u, 4097u, 0u, 7u};
    w32(m, kSfx + 4, kCompo[rng() % (sizeof kCompo / sizeof kCompo[0])]);
    w32(m, kSfx + 8, rng() % 2 ? 0u : 64u * (1 + rng() % 8));
    w32(m, kSfx + L::sfx::kZObj, kZ);
    w32(m, kSfx + L::sfx::kCbRec, kCb);
    w32(m, kSfx + L::sfx::kTable, kTab8);
    w32(m, kSfx + 52, rng() % 2 ? 100u : rng() % 6);
    w32(m, kSfx + 68, rng() % 4 == 0 ? kNonLeaf : 0u);
    w32(m, kSfx + 104, callback(rng));
    w32(m, kSfx + 108, callback(rng));
    w32(m, kSfx + 112, callback(rng));
    // the Z object: depth, data flag / pointer, clip pair, callback
    w32(m, kZ + 4, rng() % 2 ? 16u : 32u);
    w32(m, kZ + 40, rng() % 4 == 0 ? 0u : 1u);
    w32(m, kZ + 44, rng() % 3 == 0 ? 0u : kOut);
    wf(m, kZ + L::zobj::kClipNear, small_float(rng));
    wf(m, kZ + L::zobj::kClipFar, small_float(rng));
    w32(m, kZ + 68, rng() % 4 == 0 ? kNonLeaf : 0u);
    // the callback record
    w32(m, kCb + L::cbrec::kBusy, rng() % 2);
    w32(m, kCb + L::cbrec::kCopyCb, callback(rng));
    w32(m, kCb + L::cbrec::kCbA, callback(rng));
    w32(m, kCb + L::cbrec::kCbB, callback(rng));
}

u64 world_arg(std::mt19937& rng) {
    static const u32 kPtrs[] = {kHandle, kHdr, kSfx, kZ, kCb, kTab8, kOut, kZTab};
    const u32 k = rng() % 8;
    if (k < 4) return sx(kPtrs[rng() % (sizeof kPtrs / sizeof kPtrs[0])]);
    if (k < 5) return sx(kOut + ((rng() % 0x400u) & ~3u));
    return sx(enum_word(rng));
}

// The object $a0 points to, by family (three times in four): the callback record, the Z object, a plane record, the
// SFX converter or the SFD handle.
u64 first_arg(u32 addr, std::mt19937& rng) {
    if (rng() % 4 == 0) return world_arg(rng);
    switch (addr) {
    case 0x59E918u: case 0x59E960u: case 0x59E998u: case 0x59E9D0u: case 0x59EA18u:
        return sx(kCb);
    case 0x5A03B0u: case 0x5A0608u: case 0x5A0B00u: case 0x5A07E0u: case 0x5A0830u:
        return sx(kZ);
    case 0x5A00B0u: case 0x5A0188u: case 0x59EA80u:
        return sx(kOut + 0x300);
    default:
        return sx(addr >= 0x59E918u ? kSfx : kHandle);
    }
}

// Recorders for the stood-in callees (each logs the call and returns $v0); both bodies get a fresh set and the two
// call logs must be equal.
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x59FD10u, "sub_59FD10 (error)", 0},
    {0x58C100u, "sub_58C100 (lock)", 0},
    {0x58C118u, "sub_58C118 (unlock)", 0},
};
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        w->si.clobber_scratch = true;
        for (const Rec& r : kRecorders) w->si.install_recorder(r.va, r.name, r.v0, 3);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

void run_built_worlds(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            build_world(m, rng);
            const Args args{first_arg(c.addr, rng), world_arg(rng), world_arg(rng), world_arg(rng)};
            stops += spair(m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

const Case& find(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    return kCases[0];
}

}  // namespace

TEST_CASE("game(libs17): every body equals its recompiled body on built worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    run_built_worlds(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 48u, "built world");
}

TEST_CASE("game(libs17): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000"};
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_built_worlds(*m, 4u, dir);
        // the open SFD handles of the table 0x7B4774[8], as the snapshot holds them
        for (u32 i = 0; i < 8; ++i) {
            u32 h = 0;
            std::memcpy(&h, snap.data() + 0x7B4774u + 4 * i, 4);
            if (h == 0 || h >= 0x01FF0000u) continue;
            for (const Case& c : kCases) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                for (u32 seed = 1; seed <= 2; ++seed) {
                    std::mt19937 rng{seed + c.addr};
                    spair(*m, c.hand, c.recomp, Args{sx(h), rng() % 8, sx(kOut), sx(kOut + 16)}, seed, c.name);
                }
            }
            const std::string note = std::string(dir) + ": open SFD handle " + hex64(h);
            MESSAGE(note);
        }
    }
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
TEST_CASE("game(libs17): time codes, Z ramp, luma-key table, interval tracker and table rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto v0_of = [](const hgp::Run& r) { return r.end.gpr[2].u64[0]; };
    // Drop-frame time codes: 1 h 2 m 3 s 4 f, extra 5, field 1 at the unit 30000.
    {
        const u32 tc = kOut, out = kOut + 0x40, unit = kOut + 0x44;
        w32(*m, tc + 8, 1);
        w32(*m, tc + 12, 2);
        w32(*m, tc + 16, 3);
        w32(*m, tc + 20, 4);
        w32(*m, tc + 24, 5);
        const s16 field = 1;
        std::memcpy(m->at(tc + 30), &field, 2);
        const Case& a = find("sub_59AAE8");
        hgp::pair(*m, a.hand, a.recomp, Args{30000, sx(tc), sx(out), sx(unit)}, 1, a.name);
        CHECK(r32(*m, out) == (107892u + 1798u * 2 + 30u * 3 + 4u + 5u) * 1000u + 500u);
        CHECK(r32(*m, unit) == 30000u);
        const Case& b = find("sub_59AB80");
        hgp::pair(*m, b.hand, b.recomp, Args{60000, sx(tc), sx(out), sx(unit)}, 1, b.name);
        CHECK(r32(*m, out) == (215892u + 3598u * 2 + 60u * 3 + 4u + 5u) * 1000u + 500u);
        CHECK(r32(*m, unit) == 60000u);
        w32(*m, tc + 12, 12);  // the tens of minutes add 2 frames each
        hgp::pair(*m, a.hand, a.recomp, Args{30000, sx(tc), sx(out), sx(unit)}, 2, a.name);
        CHECK(r32(*m, out) == (107892u + 1798u * 12 + 2u + 30u * 3 + 4u + 5u) * 1000u + 500u);
    }
    // The Z ramp: 0 for 0..8, near for 9..16, the linear ramp for 17..223, far for 224..239, 0x7FFFFFFF after.
    {
        const Case& c = find("sub_5A0688");
        const u32 near = 100, far = 100 + 207 * 3, t = kZTab;
        hgp::pair(*m, c.hand, c.recomp, Args{0, near, far, sx(t)}, 1, c.name);
        CHECK(r32(*m, t) == 0u);
        CHECK(r32(*m, t + 4 * 8) == 0u);
        CHECK(r32(*m, t + 4 * 9) == near);
        CHECK(r32(*m, t + 4 * 16) == near);
        CHECK(r32(*m, t + 4 * 17) == near);
        CHECK(r32(*m, t + 4 * 100) == near + 3u * 83u);
        CHECK(r32(*m, t + 4 * 223) == near + 3u * 206u);
        CHECK(r32(*m, t + 4 * 224) == far);
        CHECK(r32(*m, t + 4 * 239) == far);
        CHECK(r32(*m, t + 4 * 240) == 0x7FFFFFFFu);
        CHECK(r32(*m, t + 4 * 255) == 0x7FFFFFFFu);
        hgp::pair(*m, c.hand, c.recomp, Args{0, sx(0x80000000u), 5, sx(t)}, 2, c.name);  // INT_MIN near -> INT_MAX
        CHECK(r32(*m, t + 4 * 9) == 0x7FFFFFFFu);
    }
    // The luma-key table: 0 below 16, a ramp to 127 at 235, 0x80 from 236.
    {
        const Case& c = find("sub_59EE38");
        w32(*m, kSfx + L::sfx::kTable, kTab8);
        hgp::pair(*m, c.hand, c.recomp, Args{sx(kSfx), 0, 0, 0}, 1, c.name);
        const u8* t = m->at(kTab8);
        CHECK(t[0] == 0);
        CHECK(t[15] == 0);
        CHECK(t[16] == 0);
        CHECK(t[235] == 127);
        CHECK(t[236] == 0x80);
        CHECK(t[255] == 0x80);
        bool rising = true;
        for (int i = 17; i <= 235; ++i) rising = rising && t[i] >= t[i - 1];
        CHECK(rising);
    }
    // The frame-interval tracker: the first time is only stored; then interval, maximum, minimum, smoothed.
    {
        const Case& c = find("sub_599AA0");
        const u32 r = kHandle;
        w32(*m, r + 660, 0xFFFFFFFBu);
        hgp::pair(*m, c.hand, c.recomp, Args{sx(r), 100, 0, 0}, 1, c.name);
        CHECK(r32(*m, r + 660) == 100u);
        w32(*m, r + 664, 0x7FFFFFFFu);
        w32(*m, r + 668, 0);
        w32(*m, r + 672, 1000);
        hgp::pair(*m, c.hand, c.recomp, Args{sx(r), 120, 0, 0}, 2, c.name);
        CHECK(r32(*m, r + 660) == 120u);
        CHECK(r32(*m, r + 664) == 20u);
        CHECK(r32(*m, r + 668) == 20u);
        CHECK(r32(*m, r + 672) == 20u);
        hgp::pair(*m, c.hand, c.recomp, Args{sx(r), 124, 0, 0}, 3, c.name);  // 4 < 20: down by (20 - 4) / 8 = 2
        CHECK(r32(*m, r + 664) == 18u);
        CHECK(r32(*m, r + 672) == 4u);
        const Case& n = find("sub_599B40");  // the next limit: 124 + 18 while before it
        CHECK(v0_of(hgp::pair(*m, n.hand, n.recomp, Args{sx(r), 130, 0, 0}, 1, n.name)) == 142u);
        CHECK(v0_of(hgp::pair(*m, n.hand, n.recomp, Args{sx(r), 143, 0, 0}, 2, n.name)) == 144u);
        CHECK(v0_of(hgp::pair(*m, n.hand, n.recomp, Args{sx(r), 150, 0, 0}, 3, n.name)) == 0x7FFFFFFFu);
    }
    // Compositions: the upper-half test and the conversion mode.
    {
        const Case& up = find("sub_59EAF8");
        const Case& mode = find("sub_59EBD0");
        const u32 s = kSfx, f = kOut + 0x100;
        const struct {
            u32 compo, upper, mode, mode81;
        } kRows[] = {{33, 1, 5, 4}, {257, 1, 5, 4}, {17, 0, 5, 4}, {81, 0, 4, 4}, {97, 0, 5, 5}, {4097, 0, 5, 4}};
        for (const auto& row : kRows) {
            w32(*m, s + 4, row.compo);
            CHECK(v0_of(hgp::pair(*m, up.hand, up.recomp, Args{sx(s), 0, 0, 0}, 1, up.name)) == row.upper);
            w32(*m, f + 148, 0);
            CHECK(v0_of(hgp::pair(*m, mode.hand, mode.recomp, Args{sx(s), sx(f), 0, 0}, 1, mode.name)) == row.mode);
            w32(*m, f + 148, 81);
            CHECK(v0_of(hgp::pair(*m, mode.hand, mode.recomp, Args{sx(s), sx(f), 0, 0}, 2, mode.name)) == row.mode81);
        }
        const Case& z = find("sub_5A1088");  // Z bits to the CFT depth code
        CHECK(v0_of(hgp::pair(*m, z.hand, z.recomp, Args{16, 0, 0, 0}, 1, z.name)) == 1u);
        CHECK(v0_of(hgp::pair(*m, z.hand, z.recomp, Args{24, 0, 0, 0}, 2, z.name)) == 2u);
        CHECK(v0_of(hgp::pair(*m, z.hand, z.recomp, Args{32, 0, 0, 0}, 3, z.name)) == 3u);
    }
    // Plane steps: base += lines x pitch (+ columns), lines -= n.
    {
        const u32 p = kOut + 0x200;
        w32(*m, p + L::plane::kBase, 0x1000);
        w32(*m, p + L::plane::kPitch, 640);
        w32(*m, p + L::plane::kLines, 480);
        const Case& a = find("sub_5A00B0");
        hgp::pair(*m, a.hand, a.recomp, Args{sx(p), 10, 0, 0}, 1, a.name);
        CHECK(r32(*m, p + L::plane::kBase) == 0x1000u + 6400u);
        CHECK(r32(*m, p + L::plane::kLines) == 470u);
        const Case& b = find("sub_5A0188");
        hgp::pair(*m, b.hand, b.recomp, Args{sx(p), 2, 8, 0}, 1, b.name);
        CHECK(r32(*m, p + L::plane::kBase) == 0x1000u + 6400u + 1280u + 8u);
        CHECK(r32(*m, p + L::plane::kLines) == 468u);
    }
    // The meter references: the first open clears the 16 records, the last close clears them again.
    {
        w32(*m, L::meter::kRefs, 0);
        std::memset(m->at(L::meter::kTable), 0x5A, 16 * L::meter::kStride);
        const Case& open = find("sub_5356B8");
        const Case& close = find("sub_535708");
        CHECK(v0_of(hgp::pair(*m, open.hand, open.recomp, Args{0, 0, 0, 0}, 1, open.name)) == 1u);
        CHECK(m->at(L::meter::kTable)[0] == 0);
        CHECK(m->at(L::meter::kTable)[16 * L::meter::kStride - 1] == 0);
        hgp::pair(*m, open.hand, open.recomp, Args{0, 0, 0, 0}, 2, open.name);
        CHECK(r32(*m, L::meter::kRefs) == 2u);
        m->at(L::meter::kTable)[5] = 7;
        hgp::pair(*m, close.hand, close.recomp, Args{0, 0, 0, 0}, 1, close.name);
        CHECK(m->at(L::meter::kTable)[5] == 7);  // still referenced: kept
        hgp::pair(*m, close.hand, close.recomp, Args{0, 0, 0, 0}, 2, close.name);
        CHECK(r32(*m, L::meter::kRefs) == 0u);
        CHECK(m->at(L::meter::kTable)[5] == 0);
    }
}

#else

TEST_CASE("game(libs17): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
