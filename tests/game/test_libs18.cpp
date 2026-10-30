// Pair tests for slice libs18 (game/src/cri/libs18.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log). Worlds: random worlds; the RAM of
// the replay snapshots with the live ADXT handles (0x787570, 16 x 200 bytes) and ADX decoder objects (0x7838F0, 16 x
// 260 bytes) as arguments; and documented rules on the host. A callee this build does not emit stops both runs at the
// same call (no test asserts such a stop).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs18.h"

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
void fn_sub_535DC0_00535dc0(EEContext&);  // generated body
void fn_sub_535DC0_00535dc0__recomp(EEContext&);  // recompiled
void fn_sub_535DC8_00535dc8(EEContext&);  // generated body
void fn_sub_535DC8_00535dc8__recomp(EEContext&);  // recompiled
void fn_sub_535DD0_00535dd0(EEContext&);  // generated body
void fn_sub_535DD0_00535dd0__recomp(EEContext&);  // recompiled
void fn_sub_537490_00537490(EEContext&);  // generated body
void fn_sub_537490_00537490__recomp(EEContext&);  // recompiled
void fn_sub_537498_00537498(EEContext&);  // generated body
void fn_sub_537498_00537498__recomp(EEContext&);  // recompiled
void fn_sub_5374B0_005374b0(EEContext&);  // generated body
void fn_sub_5374B0_005374b0__recomp(EEContext&);  // recompiled
void fn_sub_5376E0_005376e0(EEContext&);  // generated body
void fn_sub_5376E0_005376e0__recomp(EEContext&);  // recompiled
void fn_sub_537750_00537750(EEContext&);  // generated body
void fn_sub_537750_00537750__recomp(EEContext&);  // recompiled
void fn_sub_5377D0_005377d0(EEContext&);  // generated body
void fn_sub_5377D0_005377d0__recomp(EEContext&);  // recompiled
void fn_sub_537F18_00537f18(EEContext&);  // generated body
void fn_sub_537F18_00537f18__recomp(EEContext&);  // recompiled
void fn_sub_538408_00538408(EEContext&);  // generated body
void fn_sub_538408_00538408__recomp(EEContext&);  // recompiled
void fn_sub_538B00_00538b00(EEContext&);  // generated body
void fn_sub_538B00_00538b00__recomp(EEContext&);  // recompiled
void fn_sub_53B278_0053b278(EEContext&);  // generated body
void fn_sub_53B278_0053b278__recomp(EEContext&);  // recompiled
void fn_sub_53B3D8_0053b3d8(EEContext&);  // generated body
void fn_sub_53B3D8_0053b3d8__recomp(EEContext&);  // recompiled
void fn_sub_53B468_0053b468(EEContext&);  // generated body
void fn_sub_53B468_0053b468__recomp(EEContext&);  // recompiled
void fn_sub_53B6F8_0053b6f8(EEContext&);  // generated body
void fn_sub_53B6F8_0053b6f8__recomp(EEContext&);  // recompiled
void fn_sub_53BC88_0053bc88(EEContext&);  // generated body
void fn_sub_53BC88_0053bc88__recomp(EEContext&);  // recompiled
void fn_sub_53BD50_0053bd50(EEContext&);  // generated body
void fn_sub_53BD50_0053bd50__recomp(EEContext&);  // recompiled
void fn_sub_53BE28_0053be28(EEContext&);  // generated body
void fn_sub_53BE28_0053be28__recomp(EEContext&);  // recompiled
void fn_sub_53C1D8_0053c1d8(EEContext&);  // generated body
void fn_sub_53C1D8_0053c1d8__recomp(EEContext&);  // recompiled
void fn_sub_53C720_0053c720(EEContext&);  // generated body
void fn_sub_53C720_0053c720__recomp(EEContext&);  // recompiled
void fn_sub_53CA78_0053ca78(EEContext&);  // generated body
void fn_sub_53CA78_0053ca78__recomp(EEContext&);  // recompiled
void fn_sub_53CC78_0053cc78(EEContext&);  // generated body
void fn_sub_53CC78_0053cc78__recomp(EEContext&);  // recompiled
void fn_sub_53D040_0053d040(EEContext&);  // generated body
void fn_sub_53D040_0053d040__recomp(EEContext&);  // recompiled
void fn_sub_53D128_0053d128(EEContext&);  // generated body
void fn_sub_53D128_0053d128__recomp(EEContext&);  // recompiled
void fn_sub_53D418_0053d418(EEContext&);  // generated body
void fn_sub_53D418_0053d418__recomp(EEContext&);  // recompiled
void fn_sub_53D540_0053d540(EEContext&);  // generated body
void fn_sub_53D540_0053d540__recomp(EEContext&);  // recompiled
void fn_sub_53D790_0053d790(EEContext&);  // generated body
void fn_sub_53D790_0053d790__recomp(EEContext&);  // recompiled
void fn_sub_53D900_0053d900(EEContext&);  // generated body
void fn_sub_53D900_0053d900__recomp(EEContext&);  // recompiled
void fn_sub_53D9E0_0053d9e0(EEContext&);  // generated body
void fn_sub_53D9E0_0053d9e0__recomp(EEContext&);  // recompiled
void fn_sub_53DA90_0053da90(EEContext&);  // generated body
void fn_sub_53DA90_0053da90__recomp(EEContext&);  // recompiled
void fn_sub_53DB28_0053db28(EEContext&);  // generated body
void fn_sub_53DB28_0053db28__recomp(EEContext&);  // recompiled
void fn_sub_53DC70_0053dc70(EEContext&);  // generated body
void fn_sub_53DC70_0053dc70__recomp(EEContext&);  // recompiled
void fn_sub_53DF40_0053df40(EEContext&);  // generated body
void fn_sub_53DF40_0053df40__recomp(EEContext&);  // recompiled
void fn_sub_53DFC8_0053dfc8(EEContext&);  // generated body
void fn_sub_53DFC8_0053dfc8__recomp(EEContext&);  // recompiled
void fn_sub_53E038_0053e038(EEContext&);  // generated body
void fn_sub_53E038_0053e038__recomp(EEContext&);  // recompiled
void fn_sub_53E190_0053e190(EEContext&);  // generated body
void fn_sub_53E190_0053e190__recomp(EEContext&);  // recompiled
void fn_sub_53E1D0_0053e1d0(EEContext&);  // generated body
void fn_sub_53E1D0_0053e1d0__recomp(EEContext&);  // recompiled
void fn_sub_53E238_0053e238(EEContext&);  // generated body
void fn_sub_53E238_0053e238__recomp(EEContext&);  // recompiled
void fn_sub_53E270_0053e270(EEContext&);  // generated body
void fn_sub_53E270_0053e270__recomp(EEContext&);  // recompiled
void fn_sub_53E7D0_0053e7d0(EEContext&);  // generated body
void fn_sub_53E7D0_0053e7d0__recomp(EEContext&);  // recompiled
void fn_sub_53E850_0053e850(EEContext&);  // generated body
void fn_sub_53E850_0053e850__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_3_0053e9b8(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_3_0053e9b8__recomp(EEContext&);  // recompiled
void fn_sub_53E9C8_0053e9c8(EEContext&);  // generated body
void fn_sub_53E9C8_0053e9c8__recomp(EEContext&);  // recompiled
void fn_sub_53EA08_0053ea08(EEContext&);  // generated body
void fn_sub_53EA08_0053ea08__recomp(EEContext&);  // recompiled
void fn_sub_53EC00_0053ec00(EEContext&);  // generated body
void fn_sub_53EC00_0053ec00__recomp(EEContext&);  // recompiled
void fn_sub_53EF00_0053ef00(EEContext&);  // generated body
void fn_sub_53EF00_0053ef00__recomp(EEContext&);  // recompiled
void fn_sub_53F030_0053f030(EEContext&);  // generated body
void fn_sub_53F030_0053f030__recomp(EEContext&);  // recompiled
void fn_sub_53F148_0053f148(EEContext&);  // generated body
void fn_sub_53F148_0053f148__recomp(EEContext&);  // recompiled
void fn_sub_53F228_0053f228(EEContext&);  // generated body
void fn_sub_53F228_0053f228__recomp(EEContext&);  // recompiled
void fn_sub_53F408_0053f408(EEContext&);  // generated body
void fn_sub_53F408_0053f408__recomp(EEContext&);  // recompiled
void fn_sub_53F508_0053f508(EEContext&);  // generated body
void fn_sub_53F508_0053f508__recomp(EEContext&);  // recompiled
void fn_sub_53F510_0053f510(EEContext&);  // generated body
void fn_sub_53F510_0053f510__recomp(EEContext&);  // recompiled
void fn_sub_53F580_0053f580(EEContext&);  // generated body
void fn_sub_53F580_0053f580__recomp(EEContext&);  // recompiled
void fn_sub_53F7C0_0053f7c0(EEContext&);  // generated body
void fn_sub_53F7C0_0053f7c0__recomp(EEContext&);  // recompiled
void fn_sub_53F7D8_0053f7d8(EEContext&);  // generated body
void fn_sub_53F7D8_0053f7d8__recomp(EEContext&);  // recompiled
void fn_sub_53F7F0_0053f7f0(EEContext&);  // generated body
void fn_sub_53F7F0_0053f7f0__recomp(EEContext&);  // recompiled
void fn_atan2l_0_0053f808(EEContext&);  // generated body
void fn_atan2l_0_0053f808__recomp(EEContext&);  // recompiled
void fn_cosl_0_0053f820(EEContext&);  // generated body
void fn_cosl_0_0053f820__recomp(EEContext&);  // recompiled
void fn_coshl_0_0053f838(EEContext&);  // generated body
void fn_coshl_0_0053f838__recomp(EEContext&);  // recompiled
void fn_expl_0_0053f850(EEContext&);  // generated body
void fn_expl_0_0053f850__recomp(EEContext&);  // recompiled
void fn_hypotf_0_0053f868(EEContext&);  // generated body
void fn_hypotf_0_0053f868__recomp(EEContext&);  // recompiled
void fn_sub_541978_00541978(EEContext&);  // generated body
void fn_sub_541978_00541978__recomp(EEContext&);  // recompiled
void fn_sub_541990_00541990(EEContext&);  // generated body
void fn_sub_541990_00541990__recomp(EEContext&);  // recompiled
void fn_sub_5419A8_005419a8(EEContext&);  // generated body
void fn_sub_5419A8_005419a8__recomp(EEContext&);  // recompiled
void fn_sub_541A48_00541a48(EEContext&);  // generated body
void fn_sub_541A48_00541a48__recomp(EEContext&);  // recompiled
void fn_atan2l_1_00541a60(EEContext&);  // generated body
void fn_atan2l_1_00541a60__recomp(EEContext&);  // recompiled
void fn_sub_541AF0_00541af0(EEContext&);  // generated body
void fn_sub_541AF0_00541af0__recomp(EEContext&);  // recompiled
void fn_sub_541B40_00541b40(EEContext&);  // generated body
void fn_sub_541B40_00541b40__recomp(EEContext&);  // recompiled
void fn_sub_541BE8_00541be8(EEContext&);  // generated body
void fn_sub_541BE8_00541be8__recomp(EEContext&);  // recompiled
void fn_sub_541C00_00541c00(EEContext&);  // generated body
void fn_sub_541C00_00541c00__recomp(EEContext&);  // recompiled
void fn_sub_541C18_00541c18(EEContext&);  // generated body
void fn_sub_541C18_00541c18__recomp(EEContext&);  // recompiled
void fn_sub_541C30_00541c30(EEContext&);  // generated body
void fn_sub_541C30_00541c30__recomp(EEContext&);  // recompiled
void fn_sub_541C48_00541c48(EEContext&);  // generated body
void fn_sub_541C48_00541c48__recomp(EEContext&);  // recompiled
void fn___env_lock_6_00541c78(EEContext&);  // generated body
void fn___env_lock_6_00541c78__recomp(EEContext&);  // recompiled
void fn_sqrtl_1_00541c80(EEContext&);  // generated body
void fn_sqrtl_1_00541c80__recomp(EEContext&);  // recompiled
void fn___env_unlock_6_00541cc0(EEContext&);  // generated body
void fn___env_unlock_6_00541cc0__recomp(EEContext&);  // recompiled
void fn_sub_542050_00542050(EEContext&);  // generated body
void fn_sub_542050_00542050__recomp(EEContext&);  // recompiled
void fn_sub_542F90_00542f90(EEContext&);  // generated body
void fn_sub_542F90_00542f90__recomp(EEContext&);  // recompiled
void fn_sub_542FA0_00542fa0(EEContext&);  // generated body
void fn_sub_542FA0_00542fa0__recomp(EEContext&);  // recompiled
void fn_sub_542FD8_00542fd8(EEContext&);  // generated body
void fn_sub_542FD8_00542fd8__recomp(EEContext&);  // recompiled
void fn_sub_542FF0_00542ff0(EEContext&);  // generated body
void fn_sub_542FF0_00542ff0__recomp(EEContext&);  // recompiled
void fn__M_ctype_facet__CQ24_STL8ios_base_0_005430c0(EEContext&);  // generated body
void fn__M_ctype_facet__CQ24_STL8ios_base_0_005430c0__recomp(EEContext&);  // recompiled
void fn_sub_5430D0_005430d0(EEContext&);  // generated body
void fn_sub_5430D0_005430d0__recomp(EEContext&);  // recompiled
void fn_sub_5430E0_005430e0(EEContext&);  // generated body
void fn_sub_5430E0_005430e0__recomp(EEContext&);  // recompiled
void fn_sub_543160_00543160(EEContext&);  // generated body
void fn_sub_543160_00543160__recomp(EEContext&);  // recompiled
void fn_sub_543190_00543190(EEContext&);  // generated body
void fn_sub_543190_00543190__recomp(EEContext&);  // recompiled
void fn_sub_5431C0_005431c0(EEContext&);  // generated body
void fn_sub_5431C0_005431c0__recomp(EEContext&);  // recompiled
void fn_sub_543250_00543250(EEContext&);  // generated body
void fn_sub_543250_00543250__recomp(EEContext&);  // recompiled
void fn_sub_5433D8_005433d8(EEContext&);  // generated body
void fn_sub_5433D8_005433d8__recomp(EEContext&);  // recompiled
void fn_sub_5433F8_005433f8(EEContext&);  // generated body
void fn_sub_5433F8_005433f8__recomp(EEContext&);  // recompiled
void fn_sub_543628_00543628(EEContext&);  // generated body
void fn_sub_543628_00543628__recomp(EEContext&);  // recompiled
void fn_sub_5436B8_005436b8(EEContext&);  // generated body
void fn_sub_5436B8_005436b8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_4_005436c0(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_4_005436c0__recomp(EEContext&);  // recompiled
void fn_sub_543700_00543700(EEContext&);  // generated body
void fn_sub_543700_00543700__recomp(EEContext&);  // recompiled
void fn_sub_543858_00543858(EEContext&);  // generated body
void fn_sub_543858_00543858__recomp(EEContext&);  // recompiled
void fn_sub_543A80_00543a80(EEContext&);  // generated body
void fn_sub_543A80_00543a80__recomp(EEContext&);  // recompiled
void fn_sub_543B08_00543b08(EEContext&);  // generated body
void fn_sub_543B08_00543b08__recomp(EEContext&);  // recompiled
void fn_sub_543EE0_00543ee0(EEContext&);  // generated body
void fn_sub_543EE0_00543ee0__recomp(EEContext&);  // recompiled
void fn_sub_545440_00545440(EEContext&);  // generated body
void fn_sub_545440_00545440__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_535DC0", 0x535DC0, &recomp_gen::fn_sub_535DC0_00535dc0, &recomp_gen::fn_sub_535DC0_00535dc0__recomp},
    {"sub_535DC8", 0x535DC8, &recomp_gen::fn_sub_535DC8_00535dc8, &recomp_gen::fn_sub_535DC8_00535dc8__recomp},
    {"sub_535DD0", 0x535DD0, &recomp_gen::fn_sub_535DD0_00535dd0, &recomp_gen::fn_sub_535DD0_00535dd0__recomp},
    {"sub_537490", 0x537490, &recomp_gen::fn_sub_537490_00537490, &recomp_gen::fn_sub_537490_00537490__recomp},
    {"sub_537498", 0x537498, &recomp_gen::fn_sub_537498_00537498, &recomp_gen::fn_sub_537498_00537498__recomp},
    {"sub_5374B0", 0x5374B0, &recomp_gen::fn_sub_5374B0_005374b0, &recomp_gen::fn_sub_5374B0_005374b0__recomp},
    {"sub_5376E0", 0x5376E0, &recomp_gen::fn_sub_5376E0_005376e0, &recomp_gen::fn_sub_5376E0_005376e0__recomp},
    {"sub_537750", 0x537750, &recomp_gen::fn_sub_537750_00537750, &recomp_gen::fn_sub_537750_00537750__recomp},
    {"sub_5377D0", 0x5377D0, &recomp_gen::fn_sub_5377D0_005377d0, &recomp_gen::fn_sub_5377D0_005377d0__recomp},
    {"sub_537F18", 0x537F18, &recomp_gen::fn_sub_537F18_00537f18, &recomp_gen::fn_sub_537F18_00537f18__recomp},
    {"sub_538408", 0x538408, &recomp_gen::fn_sub_538408_00538408, &recomp_gen::fn_sub_538408_00538408__recomp},
    {"sub_538B00", 0x538B00, &recomp_gen::fn_sub_538B00_00538b00, &recomp_gen::fn_sub_538B00_00538b00__recomp},
    {"sub_53B278", 0x53B278, &recomp_gen::fn_sub_53B278_0053b278, &recomp_gen::fn_sub_53B278_0053b278__recomp},
    {"sub_53B3D8", 0x53B3D8, &recomp_gen::fn_sub_53B3D8_0053b3d8, &recomp_gen::fn_sub_53B3D8_0053b3d8__recomp},
    {"sub_53B468", 0x53B468, &recomp_gen::fn_sub_53B468_0053b468, &recomp_gen::fn_sub_53B468_0053b468__recomp},
    {"sub_53B6F8", 0x53B6F8, &recomp_gen::fn_sub_53B6F8_0053b6f8, &recomp_gen::fn_sub_53B6F8_0053b6f8__recomp},
    {"sub_53BC88", 0x53BC88, &recomp_gen::fn_sub_53BC88_0053bc88, &recomp_gen::fn_sub_53BC88_0053bc88__recomp},
    {"sub_53BD50", 0x53BD50, &recomp_gen::fn_sub_53BD50_0053bd50, &recomp_gen::fn_sub_53BD50_0053bd50__recomp},
    {"sub_53BE28", 0x53BE28, &recomp_gen::fn_sub_53BE28_0053be28, &recomp_gen::fn_sub_53BE28_0053be28__recomp},
    {"sub_53C1D8", 0x53C1D8, &recomp_gen::fn_sub_53C1D8_0053c1d8, &recomp_gen::fn_sub_53C1D8_0053c1d8__recomp},
    {"sub_53C720", 0x53C720, &recomp_gen::fn_sub_53C720_0053c720, &recomp_gen::fn_sub_53C720_0053c720__recomp},
    {"sub_53CA78", 0x53CA78, &recomp_gen::fn_sub_53CA78_0053ca78, &recomp_gen::fn_sub_53CA78_0053ca78__recomp},
    {"sub_53CC78", 0x53CC78, &recomp_gen::fn_sub_53CC78_0053cc78, &recomp_gen::fn_sub_53CC78_0053cc78__recomp},
    {"sub_53D040", 0x53D040, &recomp_gen::fn_sub_53D040_0053d040, &recomp_gen::fn_sub_53D040_0053d040__recomp},
    {"sub_53D128", 0x53D128, &recomp_gen::fn_sub_53D128_0053d128, &recomp_gen::fn_sub_53D128_0053d128__recomp},
    {"sub_53D418", 0x53D418, &recomp_gen::fn_sub_53D418_0053d418, &recomp_gen::fn_sub_53D418_0053d418__recomp},
    {"sub_53D540", 0x53D540, &recomp_gen::fn_sub_53D540_0053d540, &recomp_gen::fn_sub_53D540_0053d540__recomp},
    {"sub_53D790", 0x53D790, &recomp_gen::fn_sub_53D790_0053d790, &recomp_gen::fn_sub_53D790_0053d790__recomp},
    {"sub_53D900", 0x53D900, &recomp_gen::fn_sub_53D900_0053d900, &recomp_gen::fn_sub_53D900_0053d900__recomp},
    {"sub_53D9E0", 0x53D9E0, &recomp_gen::fn_sub_53D9E0_0053d9e0, &recomp_gen::fn_sub_53D9E0_0053d9e0__recomp},
    {"sub_53DA90", 0x53DA90, &recomp_gen::fn_sub_53DA90_0053da90, &recomp_gen::fn_sub_53DA90_0053da90__recomp},
    {"sub_53DB28", 0x53DB28, &recomp_gen::fn_sub_53DB28_0053db28, &recomp_gen::fn_sub_53DB28_0053db28__recomp},
    {"sub_53DC70", 0x53DC70, &recomp_gen::fn_sub_53DC70_0053dc70, &recomp_gen::fn_sub_53DC70_0053dc70__recomp},
    {"sub_53DF40", 0x53DF40, &recomp_gen::fn_sub_53DF40_0053df40, &recomp_gen::fn_sub_53DF40_0053df40__recomp},
    {"sub_53DFC8", 0x53DFC8, &recomp_gen::fn_sub_53DFC8_0053dfc8, &recomp_gen::fn_sub_53DFC8_0053dfc8__recomp},
    {"sub_53E038", 0x53E038, &recomp_gen::fn_sub_53E038_0053e038, &recomp_gen::fn_sub_53E038_0053e038__recomp},
    {"sub_53E190", 0x53E190, &recomp_gen::fn_sub_53E190_0053e190, &recomp_gen::fn_sub_53E190_0053e190__recomp},
    {"sub_53E1D0", 0x53E1D0, &recomp_gen::fn_sub_53E1D0_0053e1d0, &recomp_gen::fn_sub_53E1D0_0053e1d0__recomp},
    {"sub_53E238", 0x53E238, &recomp_gen::fn_sub_53E238_0053e238, &recomp_gen::fn_sub_53E238_0053e238__recomp},
    {"sub_53E270", 0x53E270, &recomp_gen::fn_sub_53E270_0053e270, &recomp_gen::fn_sub_53E270_0053e270__recomp},
    {"sub_53E7D0", 0x53E7D0, &recomp_gen::fn_sub_53E7D0_0053e7d0, &recomp_gen::fn_sub_53E7D0_0053e7d0__recomp},
    {"sub_53E850", 0x53E850, &recomp_gen::fn_sub_53E850_0053e850, &recomp_gen::fn_sub_53E850_0053e850__recomp},
    {"sceLibgcc32GetErxEntries_3", 0x53E9B8, &recomp_gen::fn_sceLibgcc32GetErxEntries_3_0053e9b8, &recomp_gen::fn_sceLibgcc32GetErxEntries_3_0053e9b8__recomp},
    {"sub_53E9C8", 0x53E9C8, &recomp_gen::fn_sub_53E9C8_0053e9c8, &recomp_gen::fn_sub_53E9C8_0053e9c8__recomp},
    {"sub_53EA08", 0x53EA08, &recomp_gen::fn_sub_53EA08_0053ea08, &recomp_gen::fn_sub_53EA08_0053ea08__recomp},
    {"sub_53EC00", 0x53EC00, &recomp_gen::fn_sub_53EC00_0053ec00, &recomp_gen::fn_sub_53EC00_0053ec00__recomp},
    {"sub_53EF00", 0x53EF00, &recomp_gen::fn_sub_53EF00_0053ef00, &recomp_gen::fn_sub_53EF00_0053ef00__recomp},
    {"sub_53F030", 0x53F030, &recomp_gen::fn_sub_53F030_0053f030, &recomp_gen::fn_sub_53F030_0053f030__recomp},
    {"sub_53F148", 0x53F148, &recomp_gen::fn_sub_53F148_0053f148, &recomp_gen::fn_sub_53F148_0053f148__recomp},
    {"sub_53F228", 0x53F228, &recomp_gen::fn_sub_53F228_0053f228, &recomp_gen::fn_sub_53F228_0053f228__recomp},
    {"sub_53F408", 0x53F408, &recomp_gen::fn_sub_53F408_0053f408, &recomp_gen::fn_sub_53F408_0053f408__recomp},
    {"sub_53F508", 0x53F508, &recomp_gen::fn_sub_53F508_0053f508, &recomp_gen::fn_sub_53F508_0053f508__recomp},
    {"sub_53F510", 0x53F510, &recomp_gen::fn_sub_53F510_0053f510, &recomp_gen::fn_sub_53F510_0053f510__recomp},
    {"sub_53F580", 0x53F580, &recomp_gen::fn_sub_53F580_0053f580, &recomp_gen::fn_sub_53F580_0053f580__recomp},
    {"sub_53F7C0", 0x53F7C0, &recomp_gen::fn_sub_53F7C0_0053f7c0, &recomp_gen::fn_sub_53F7C0_0053f7c0__recomp},
    {"sub_53F7D8", 0x53F7D8, &recomp_gen::fn_sub_53F7D8_0053f7d8, &recomp_gen::fn_sub_53F7D8_0053f7d8__recomp},
    {"sub_53F7F0", 0x53F7F0, &recomp_gen::fn_sub_53F7F0_0053f7f0, &recomp_gen::fn_sub_53F7F0_0053f7f0__recomp},
    {"atan2l_0", 0x53F808, &recomp_gen::fn_atan2l_0_0053f808, &recomp_gen::fn_atan2l_0_0053f808__recomp},
    {"cosl_0", 0x53F820, &recomp_gen::fn_cosl_0_0053f820, &recomp_gen::fn_cosl_0_0053f820__recomp},
    {"coshl_0", 0x53F838, &recomp_gen::fn_coshl_0_0053f838, &recomp_gen::fn_coshl_0_0053f838__recomp},
    {"expl_0", 0x53F850, &recomp_gen::fn_expl_0_0053f850, &recomp_gen::fn_expl_0_0053f850__recomp},
    {"hypotf_0", 0x53F868, &recomp_gen::fn_hypotf_0_0053f868, &recomp_gen::fn_hypotf_0_0053f868__recomp},
    {"sub_541978", 0x541978, &recomp_gen::fn_sub_541978_00541978, &recomp_gen::fn_sub_541978_00541978__recomp},
    {"sub_541990", 0x541990, &recomp_gen::fn_sub_541990_00541990, &recomp_gen::fn_sub_541990_00541990__recomp},
    {"sub_5419A8", 0x5419A8, &recomp_gen::fn_sub_5419A8_005419a8, &recomp_gen::fn_sub_5419A8_005419a8__recomp},
    {"sub_541A48", 0x541A48, &recomp_gen::fn_sub_541A48_00541a48, &recomp_gen::fn_sub_541A48_00541a48__recomp},
    {"atan2l_1", 0x541A60, &recomp_gen::fn_atan2l_1_00541a60, &recomp_gen::fn_atan2l_1_00541a60__recomp},
    {"sub_541AF0", 0x541AF0, &recomp_gen::fn_sub_541AF0_00541af0, &recomp_gen::fn_sub_541AF0_00541af0__recomp},
    {"sub_541B40", 0x541B40, &recomp_gen::fn_sub_541B40_00541b40, &recomp_gen::fn_sub_541B40_00541b40__recomp},
    {"sub_541BE8", 0x541BE8, &recomp_gen::fn_sub_541BE8_00541be8, &recomp_gen::fn_sub_541BE8_00541be8__recomp},
    {"sub_541C00", 0x541C00, &recomp_gen::fn_sub_541C00_00541c00, &recomp_gen::fn_sub_541C00_00541c00__recomp},
    {"sub_541C18", 0x541C18, &recomp_gen::fn_sub_541C18_00541c18, &recomp_gen::fn_sub_541C18_00541c18__recomp},
    {"sub_541C30", 0x541C30, &recomp_gen::fn_sub_541C30_00541c30, &recomp_gen::fn_sub_541C30_00541c30__recomp},
    {"sub_541C48", 0x541C48, &recomp_gen::fn_sub_541C48_00541c48, &recomp_gen::fn_sub_541C48_00541c48__recomp},
    {"__env_lock_6", 0x541C78, &recomp_gen::fn___env_lock_6_00541c78, &recomp_gen::fn___env_lock_6_00541c78__recomp},
    {"sqrtl_1", 0x541C80, &recomp_gen::fn_sqrtl_1_00541c80, &recomp_gen::fn_sqrtl_1_00541c80__recomp},
    {"__env_unlock_6", 0x541CC0, &recomp_gen::fn___env_unlock_6_00541cc0, &recomp_gen::fn___env_unlock_6_00541cc0__recomp},
    {"sub_542050", 0x542050, &recomp_gen::fn_sub_542050_00542050, &recomp_gen::fn_sub_542050_00542050__recomp},
    {"sub_542F90", 0x542F90, &recomp_gen::fn_sub_542F90_00542f90, &recomp_gen::fn_sub_542F90_00542f90__recomp},
    {"sub_542FA0", 0x542FA0, &recomp_gen::fn_sub_542FA0_00542fa0, &recomp_gen::fn_sub_542FA0_00542fa0__recomp},
    {"sub_542FD8", 0x542FD8, &recomp_gen::fn_sub_542FD8_00542fd8, &recomp_gen::fn_sub_542FD8_00542fd8__recomp},
    {"sub_542FF0", 0x542FF0, &recomp_gen::fn_sub_542FF0_00542ff0, &recomp_gen::fn_sub_542FF0_00542ff0__recomp},
    {"_M_ctype_facet__CQ24_STL8ios_base_0", 0x5430C0, &recomp_gen::fn__M_ctype_facet__CQ24_STL8ios_base_0_005430c0, &recomp_gen::fn__M_ctype_facet__CQ24_STL8ios_base_0_005430c0__recomp},
    {"sub_5430D0", 0x5430D0, &recomp_gen::fn_sub_5430D0_005430d0, &recomp_gen::fn_sub_5430D0_005430d0__recomp},
    {"sub_5430E0", 0x5430E0, &recomp_gen::fn_sub_5430E0_005430e0, &recomp_gen::fn_sub_5430E0_005430e0__recomp},
    {"sub_543160", 0x543160, &recomp_gen::fn_sub_543160_00543160, &recomp_gen::fn_sub_543160_00543160__recomp},
    {"sub_543190", 0x543190, &recomp_gen::fn_sub_543190_00543190, &recomp_gen::fn_sub_543190_00543190__recomp},
    {"sub_5431C0", 0x5431C0, &recomp_gen::fn_sub_5431C0_005431c0, &recomp_gen::fn_sub_5431C0_005431c0__recomp},
    {"sub_543250", 0x543250, &recomp_gen::fn_sub_543250_00543250, &recomp_gen::fn_sub_543250_00543250__recomp},
    {"sub_5433D8", 0x5433D8, &recomp_gen::fn_sub_5433D8_005433d8, &recomp_gen::fn_sub_5433D8_005433d8__recomp},
    {"sub_5433F8", 0x5433F8, &recomp_gen::fn_sub_5433F8_005433f8, &recomp_gen::fn_sub_5433F8_005433f8__recomp},
    {"sub_543628", 0x543628, &recomp_gen::fn_sub_543628_00543628, &recomp_gen::fn_sub_543628_00543628__recomp},
    {"sub_5436B8", 0x5436B8, &recomp_gen::fn_sub_5436B8_005436b8, &recomp_gen::fn_sub_5436B8_005436b8__recomp},
    {"sceLibgcc32GetErxEntries_4", 0x5436C0, &recomp_gen::fn_sceLibgcc32GetErxEntries_4_005436c0, &recomp_gen::fn_sceLibgcc32GetErxEntries_4_005436c0__recomp},
    {"sub_543700", 0x543700, &recomp_gen::fn_sub_543700_00543700, &recomp_gen::fn_sub_543700_00543700__recomp},
    {"sub_543858", 0x543858, &recomp_gen::fn_sub_543858_00543858, &recomp_gen::fn_sub_543858_00543858__recomp},
    {"sub_543A80", 0x543A80, &recomp_gen::fn_sub_543A80_00543a80, &recomp_gen::fn_sub_543A80_00543a80__recomp},
    {"sub_543B08", 0x543B08, &recomp_gen::fn_sub_543B08_00543b08, &recomp_gen::fn_sub_543B08_00543b08__recomp},
    {"sub_543EE0", 0x543EE0, &recomp_gen::fn_sub_543EE0_00543ee0, &recomp_gen::fn_sub_543EE0_00543ee0__recomp},
    {"sub_545440", 0x545440, &recomp_gen::fn_sub_545440_00545440, &recomp_gen::fn_sub_545440_00545440__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs18): every body equals its recompiled body on random worlds") {
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

constexpr u32 kAdxtHandles = 0x787570u;  // 16 ADXT handles of 200 bytes; byte +0 = used (adxt_Create's scan)
constexpr u32 kAdxtStride = 200u;
constexpr u32 kAdxDecoders = 0x7838F0u;  // 16 ADX decoder objects of 260 bytes; s16 +0 = state (sub_538B00)
constexpr u32 kAdxDecStride = 260u;

void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u16 r16(Machine& m, u32 va) {
    u16 v = 0;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }

}  // namespace

// Every body over the RAM of the replay snapshots (the real ADX / ADXF / ADXT / RNA globals), its first argument a live
// ADXT handle or ADX decoder object (or a world pointer when the snapshot holds none), the others small values.
TEST_CASE("game(libs18): every body equals its recompiled body on the replay snapshots") {
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
        std::vector<u32> pool;
        for (u32 i = 0; i < 16; ++i) {
            if (snap[kAdxtHandles + kAdxtStride * i] != 0) pool.push_back(kAdxtHandles + kAdxtStride * i);
            s16 st = 0;
            std::memcpy(&st, snap.data() + kAdxDecoders + kAdxDecStride * i, 2);
            if (st != 0) pool.push_back(kAdxDecoders + kAdxDecStride * i);
        }
        if (pool.empty()) pool.push_back(kWorld);
        for (const Case& c : kCases) {
            std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            for (u32 seed = 1; seed <= 4; ++seed) {
                std::mt19937 rng{seed * 131u + c.addr};
                const Args args{sx(pool[(seed - 1) % pool.size()]), rng() % 4, sx(kWorld + 0x100u * (rng() % 16)), sx(kWorld + 0x40u * (rng() % 64))};
                hgp::pair(*m, c.hand, c.recomp, args, seed, c.name);
            }
        }
        const std::string note = std::string(dir) + ": " + std::to_string(pool.size()) + " live ADXT handles / decoder objects, " +
                                 std::to_string((sizeof kCases / sizeof kCases[0]) * 4) + " pairs";
        MESSAGE(note);
    }
}

// Documented rules, from the instructions (both bodies run and are compared, then the result is checked).
TEST_CASE("game(libs18): byte order, key step, header writer, RNA getters and record rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto run = [&](const char* name, const Args& a, u32 seed = 1) {
        const Case& c = find_case(name);
        return hgp::pair(*m, c.hand, c.recomp, a, seed, c.name);
    };
    const u32 w = kWorld;
    // sub_53E238 / sub_53E270: little-endian halfword / word stores, byte by byte (an odd address is fine).
    run("sub_53E238", Args{sx(w + 1), 0x1234u, 0, 0});
    CHECK(*m->at(w + 1) == 0x34);
    CHECK(*m->at(w + 2) == 0x12);
    run("sub_53E270", Args{sx(w + 5), 0xA1B2C3D4u, 0, 0});
    CHECK(*m->at(w + 5) == 0xD4);
    CHECK(*m->at(w + 6) == 0xC3);
    CHECK(*m->at(w + 7) == 0xB2);
    CHECK(*m->at(w + 8) == 0xA1);
    // sub_537750: *a0 = *a0 * *a1 + *a2 in 16 bits; returns 0.
    w16(*m, w + 0x10, 0x1234);
    w16(*m, w + 0x12, 0x0101);
    w16(*m, w + 0x14, 0x0010);
    CHECK(v0_of(run("sub_537750", Args{sx(w + 0x10), sx(w + 0x12), sx(w + 0x14), 0})) == 0u);
    CHECK(r16(*m, w + 0x10) == static_cast<u16>(0x1234u * 0x0101u + 0x10u));
    // sub_542050: the word at +12 + 4 * index.
    run("sub_542050", Args{sx(w + 0x20), 3, 0xCAFEF00Du, 0});
    CHECK(r32(*m, w + 0x20 + 12 + 12) == 0xCAFEF00Du);
    // sub_543EE0: 0 for a null record, else the s8 at +88 + index.
    w8(*m, w + 0x80 + 88 + 2, 0xF0);
    CHECK(v0_of(run("sub_543EE0", Args{0, 2, 0, 0})) == 0u);
    CHECK(v0_of(run("sub_543EE0", Args{sx(w + 0x80), 2, 0, 0})) == sx(0xFFFFFFF0u));
    // Constants.
    CHECK(v0_of(run("sub_5436B8", Args{})) == 256u);
    CHECK(v0_of(run("sub_5433D8", Args{})) == 0u);
    CHECK(v0_of(run("sub_537490", Args{})) == 0u);
    // sub_542FF0 sets the three s16 at +160.. of the decoder handle (+4); sub_542FD8 reads them back as u16.
    w32(*m, w + 0x204, w + 0x300);  // the handle's decoder (+4)
    run("sub_542FF0", Args{sx(w + 0x200), sx(0xFFFFFFFEu), 3, 0x10004u});
    CHECK(r16(*m, w + 0x300 + 160) == 0xFFFEu);
    CHECK(r16(*m, w + 0x300 + 162) == 3u);
    CHECK(r16(*m, w + 0x300 + 164) == 4u);
    run("sub_542FD8", Args{sx(w + 0x200), sx(w + 0x400), sx(w + 0x402), sx(w + 0x404)});
    CHECK(r16(*m, w + 0x400) == 0xFFFEu);
    CHECK(r16(*m, w + 0x404) == 4u);
    // sub_541BE8: 0 only when the RNA mode word 0x7A93F8 is 1 and the count 0x7A93F0 is <= 0; else the word +48.
    w32(*m, w + 0x500 + 48, 0x55u);
    w32(*m, 0x7A93F8u, 1);
    w32(*m, 0x7A93F0u, 0);
    CHECK(v0_of(run("sub_541BE8", Args{sx(w + 0x500), 0, 0, 0})) == 0u);
    w32(*m, 0x7A93F0u, 2);
    CHECK(v0_of(run("sub_541BE8", Args{sx(w + 0x500), 0, 0, 0})) == 0x55u);
    w32(*m, 0x7A93F8u, 0);
    w32(*m, 0x7A93F0u, 0);
    CHECK(v0_of(run("sub_541BE8", Args{sx(w + 0x500), 0, 0, 0})) == 0x55u);
    CHECK(v0_of(run("sub_541C48", Args{})) == 16u);
    // sub_5419A8: the word table 0x7A9430[a0] for a0 < 2, else 0.
    w32(*m, 0x7A9434u, 0x77u);
    CHECK(v0_of(run("sub_5419A8", Args{1, 0, 0, 0})) == 0x77u);
    CHECK(v0_of(run("sub_5419A8", Args{2, 0, 0, 0})) == 0u);
    // sub_543B08: nothing for null; else 12 zero bytes; returns the record.
    std::memset(m->at(w + 0x600), 0xAB, 16);
    CHECK(v0_of(run("sub_543B08", Args{0, 0, 0, 0})) == 0u);
    CHECK(v0_of(run("sub_543B08", Args{sx(w + 0x600), 0, 0, 0})) == sx(w + 0x600));
    CHECK(r32(*m, w + 0x600) == 0u);
    CHECK(r32(*m, w + 0x608) == 0u);
    CHECK(r32(*m, w + 0x60C) == 0xABABABABu);
    // sub_543A80 zeroes 192 bytes at 0x7921F8; sub_5377D0 zeroes the 16 x 260-byte decoder table.
    std::memset(m->at(0x7921F8u), 0x5A, 196);
    run("sub_543A80", Args{});
    CHECK(r32(*m, 0x7921F8u + 188) == 0u);
    CHECK(r32(*m, 0x7921F8u + 192) == 0x5A5A5A5Au);
    std::memset(m->at(kAdxDecoders), 0x11, 16 * kAdxDecStride);
    run("sub_5377D0", Args{});
    CHECK(r32(*m, kAdxDecoders) == 0u);
    CHECK(r32(*m, kAdxDecoders + 16 * kAdxDecStride - 4) == 0u);
    // sub_53E7D0: a buffer under 36 bytes gives -1 (and *size = 0); 36 gives the 0x80 0x00 magic, *size = 36, 0.
    w32(*m, w + 0x700, 0x99u);
    CHECK(v0_of(run("sub_53E7D0", Args{sx(w + 0x800), 35, sx(w + 0x700), sx(w + 0x900)})) == sx(0xFFFFFFFFu));
    CHECK(r32(*m, w + 0x700) == 0u);
    CHECK(v0_of(run("sub_53E7D0", Args{sx(w + 0x800), 36, sx(w + 0x700), sx(w + 0x900)})) == 0u);
    CHECK(*m->at(w + 0x800) == 0x80);
    CHECK(*m->at(w + 0x801) == 0x00);
    CHECK(r32(*m, w + 0x700) == 36u);
    // sub_53EA08 counts a server call in 0x787568 before its tail call.
    w32(*m, 0x787568u, 41);
    run("sub_53EA08", Args{});
    CHECK(r32(*m, 0x787568u) == 42u);
    // The callbacks through `jalr` (sub_5374B0, sub_5433F8): fn(arg, a0) with a non-leaf callee (sub_543B08, which
    // spills $ra below the $sp it gets), so the dead stack is compared; the callee clears 12 bytes at arg; returns 0.
    run("sub_537498", Args{0x543B08u, sx(w + 0xA00), 0, 0});
    CHECK(r32(*m, 0x7838D0u) == 0x543B08u);
    CHECK(r32(*m, 0x7838D4u) == w + 0xA00);
    std::memset(m->at(w + 0xA00), 0xCD, 16);
    CHECK(v0_of(run("sub_5374B0", Args{5, 0, 0, 0})) == 0u);
    CHECK(r32(*m, w + 0xA08) == 0u);
    CHECK(r32(*m, w + 0xA0C) == 0xCDCDCDCDu);
    w32(*m, 0x790A1Cu, 0x543B08u);
    w32(*m, 0x790A20u, w + 0xB00);
    std::memset(m->at(w + 0xB00), 0xCD, 16);
    CHECK(v0_of(run("sub_5433F8", Args{5, 0, 0, 0})) == 0u);
    CHECK(r32(*m, w + 0xB04) == 0u);
    CHECK(r32(*m, w + 0xB0C) == 0xCDCDCDCDu);
}

#else

TEST_CASE("game(libs18): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
