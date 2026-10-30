// Pair tests for slice libs19 (game/src/cri/libs19.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log), on random worlds, on the snapshots' live ADXT
// handles and streamers, and on built handles with the documented rules: the ADX encoder's fields, the wrappers'
// results and null-handle reports, the small globals, the disc-range name.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/cri2.h"
#include "p3fes/game/libs19.h"
#include "p3fes/game/libs9.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace p3fes::recomp_gen {
void fn_sub_545598_00545598(EEContext&);  // generated body
void fn_sub_545598_00545598__recomp(EEContext&);  // recompiled
void fn_sub_5455A0_005455a0(EEContext&);  // generated body
void fn_sub_5455A0_005455a0__recomp(EEContext&);  // recompiled
void fn_sub_545608_00545608(EEContext&);  // generated body
void fn_sub_545608_00545608__recomp(EEContext&);  // recompiled
void fn_sub_545620_00545620(EEContext&);  // generated body
void fn_sub_545620_00545620__recomp(EEContext&);  // recompiled
void fn_sub_545628_00545628(EEContext&);  // generated body
void fn_sub_545628_00545628__recomp(EEContext&);  // recompiled
void fn_sub_545630_00545630(EEContext&);  // generated body
void fn_sub_545630_00545630__recomp(EEContext&);  // recompiled
void fn_sub_545638_00545638(EEContext&);  // generated body
void fn_sub_545638_00545638__recomp(EEContext&);  // recompiled
void fn_sub_545640_00545640(EEContext&);  // generated body
void fn_sub_545640_00545640__recomp(EEContext&);  // recompiled
void fn_sub_545648_00545648(EEContext&);  // generated body
void fn_sub_545648_00545648__recomp(EEContext&);  // recompiled
void fn_sub_545650_00545650(EEContext&);  // generated body
void fn_sub_545650_00545650__recomp(EEContext&);  // recompiled
void fn_sub_545658_00545658(EEContext&);  // generated body
void fn_sub_545658_00545658__recomp(EEContext&);  // recompiled
void fn_sub_545680_00545680(EEContext&);  // generated body
void fn_sub_545680_00545680__recomp(EEContext&);  // recompiled
void fn_sub_5456B0_005456b0(EEContext&);  // generated body
void fn_sub_5456B0_005456b0__recomp(EEContext&);  // recompiled
void fn_sub_545718_00545718(EEContext&);  // generated body
void fn_sub_545718_00545718__recomp(EEContext&);  // recompiled
void fn_sub_545798_00545798(EEContext&);  // generated body
void fn_sub_545798_00545798__recomp(EEContext&);  // recompiled
void fn_sub_545898_00545898(EEContext&);  // generated body
void fn_sub_545898_00545898__recomp(EEContext&);  // recompiled
void fn_sub_545900_00545900(EEContext&);  // generated body
void fn_sub_545900_00545900__recomp(EEContext&);  // recompiled
void fn_sub_545908_00545908(EEContext&);  // generated body
void fn_sub_545908_00545908__recomp(EEContext&);  // recompiled
void fn_sub_545910_00545910(EEContext&);  // generated body
void fn_sub_545910_00545910__recomp(EEContext&);  // recompiled
void fn_sub_545918_00545918(EEContext&);  // generated body
void fn_sub_545918_00545918__recomp(EEContext&);  // recompiled
void fn_sub_545920_00545920(EEContext&);  // generated body
void fn_sub_545920_00545920__recomp(EEContext&);  // recompiled
void fn_sub_545940_00545940(EEContext&);  // generated body
void fn_sub_545940_00545940__recomp(EEContext&);  // recompiled
void fn_expl_2_00545c50(EEContext&);  // generated body
void fn_expl_2_00545c50__recomp(EEContext&);  // recompiled
void fn_sub_545C58_00545c58(EEContext&);  // generated body
void fn_sub_545C58_00545c58__recomp(EEContext&);  // recompiled
void fn_hypotf_2_00545c68(EEContext&);  // generated body
void fn_hypotf_2_00545c68__recomp(EEContext&);  // recompiled
void fn_sub_545CC0_00545cc0(EEContext&);  // generated body
void fn_sub_545CC0_00545cc0__recomp(EEContext&);  // recompiled
void fn_sub_546360_00546360(EEContext&);  // generated body
void fn_sub_546360_00546360__recomp(EEContext&);  // recompiled
void fn_sub_546E78_00546e78(EEContext&);  // generated body
void fn_sub_546E78_00546e78__recomp(EEContext&);  // recompiled
void fn_sub_546F60_00546f60(EEContext&);  // generated body
void fn_sub_546F60_00546f60__recomp(EEContext&);  // recompiled
void fn_sub_547060_00547060(EEContext&);  // generated body
void fn_sub_547060_00547060__recomp(EEContext&);  // recompiled
void fn_sub_547180_00547180(EEContext&);  // generated body
void fn_sub_547180_00547180__recomp(EEContext&);  // recompiled
void fn_sub_5471C0_005471c0(EEContext&);  // generated body
void fn_sub_5471C0_005471c0__recomp(EEContext&);  // recompiled
void fn_sub_5471F0_005471f0(EEContext&);  // generated body
void fn_sub_5471F0_005471f0__recomp(EEContext&);  // recompiled
void fn_sub_547200_00547200(EEContext&);  // generated body
void fn_sub_547200_00547200__recomp(EEContext&);  // recompiled
void fn_sub_5472A0_005472a0(EEContext&);  // generated body
void fn_sub_5472A0_005472a0__recomp(EEContext&);  // recompiled
void fn_sub_5473D8_005473d8(EEContext&);  // generated body
void fn_sub_5473D8_005473d8__recomp(EEContext&);  // recompiled
void fn_sub_547428_00547428(EEContext&);  // generated body
void fn_sub_547428_00547428__recomp(EEContext&);  // recompiled
void fn_sub_547488_00547488(EEContext&);  // generated body
void fn_sub_547488_00547488__recomp(EEContext&);  // recompiled
void fn_sub_5474C8_005474c8(EEContext&);  // generated body
void fn_sub_5474C8_005474c8__recomp(EEContext&);  // recompiled
void fn_sub_547510_00547510(EEContext&);  // generated body
void fn_sub_547510_00547510__recomp(EEContext&);  // recompiled
void fn_ADXPS2_LoadFcacheDvd_00547768(EEContext&);  // generated body
void fn_ADXPS2_LoadFcacheDvd_00547768__recomp(EEContext&);  // recompiled
void fn_sub_5477C8_005477c8(EEContext&);  // generated body
void fn_sub_5477C8_005477c8__recomp(EEContext&);  // recompiled
void fn_sub_547830_00547830(EEContext&);  // generated body
void fn_sub_547830_00547830__recomp(EEContext&);  // recompiled
void fn_atan2l_3_00547898(EEContext&);  // generated body
void fn_atan2l_3_00547898__recomp(EEContext&);  // recompiled
void fn_cosl_3_005478b0(EEContext&);  // generated body
void fn_cosl_3_005478b0__recomp(EEContext&);  // recompiled
void fn_coshl_3_005478c8(EEContext&);  // generated body
void fn_coshl_3_005478c8__recomp(EEContext&);  // recompiled
void fn_expl_3_005478e0(EEContext&);  // generated body
void fn_expl_3_005478e0__recomp(EEContext&);  // recompiled
void fn_hypotf_3_005478f8(EEContext&);  // generated body
void fn_hypotf_3_005478f8__recomp(EEContext&);  // recompiled
void fn_sub_547948_00547948(EEContext&);  // generated body
void fn_sub_547948_00547948__recomp(EEContext&);  // recompiled
void fn_sceInsockSetErrnoMode_2_005479e8(EEContext&);  // generated body
void fn_sceInsockSetErrnoMode_2_005479e8__recomp(EEContext&);  // recompiled
void fn_sceInsockGetErrnoMode_2_005479f8(EEContext&);  // generated body
void fn_sceInsockGetErrnoMode_2_005479f8__recomp(EEContext&);  // recompiled
void fn_my_malloc_2_00547a08(EEContext&);  // generated body
void fn_my_malloc_2_00547a08__recomp(EEContext&);  // recompiled
void fn_sub_547A18_00547a18(EEContext&);  // generated body
void fn_sub_547A18_00547a18__recomp(EEContext&);  // recompiled
void fn_sub_547A28_00547a28(EEContext&);  // generated body
void fn_sub_547A28_00547a28__recomp(EEContext&);  // recompiled
void fn_powl_3_00547a70(EEContext&);  // generated body
void fn_powl_3_00547a70__recomp(EEContext&);  // recompiled
void fn_sub_547AC0_00547ac0(EEContext&);  // generated body
void fn_sub_547AC0_00547ac0__recomp(EEContext&);  // recompiled
void fn_sub_5482D8_005482d8(EEContext&);  // generated body
void fn_sub_5482D8_005482d8__recomp(EEContext&);  // recompiled
void fn_sub_5487D0_005487d0(EEContext&);  // generated body
void fn_sub_5487D0_005487d0__recomp(EEContext&);  // recompiled
void fn_sub_548838_00548838(EEContext&);  // generated body
void fn_sub_548838_00548838__recomp(EEContext&);  // recompiled
void fn_sub_548950_00548950(EEContext&);  // generated body
void fn_sub_548950_00548950__recomp(EEContext&);  // recompiled
void fn_sub_548E30_00548e30(EEContext&);  // generated body
void fn_sub_548E30_00548e30__recomp(EEContext&);  // recompiled
void fn_sub_549050_00549050(EEContext&);  // generated body
void fn_sub_549050_00549050__recomp(EEContext&);  // recompiled
void fn_sub_5490D8_005490d8(EEContext&);  // generated body
void fn_sub_5490D8_005490d8__recomp(EEContext&);  // recompiled
void fn_sub_549350_00549350(EEContext&);  // generated body
void fn_sub_549350_00549350__recomp(EEContext&);  // recompiled
void fn_sub_549418_00549418(EEContext&);  // generated body
void fn_sub_549418_00549418__recomp(EEContext&);  // recompiled
void fn_sub_549598_00549598(EEContext&);  // generated body
void fn_sub_549598_00549598__recomp(EEContext&);  // recompiled
void fn_sub_5495F0_005495f0(EEContext&);  // generated body
void fn_sub_5495F0_005495f0__recomp(EEContext&);  // recompiled
void fn_sub_549658_00549658(EEContext&);  // generated body
void fn_sub_549658_00549658__recomp(EEContext&);  // recompiled
void fn_sub_5496A8_005496a8(EEContext&);  // generated body
void fn_sub_5496A8_005496a8__recomp(EEContext&);  // recompiled
void fn_sub_549728_00549728(EEContext&);  // generated body
void fn_sub_549728_00549728__recomp(EEContext&);  // recompiled
void fn_sub_549768_00549768(EEContext&);  // generated body
void fn_sub_549768_00549768__recomp(EEContext&);  // recompiled
void fn_sub_549870_00549870(EEContext&);  // generated body
void fn_sub_549870_00549870__recomp(EEContext&);  // recompiled
void fn_sub_549980_00549980(EEContext&);  // generated body
void fn_sub_549980_00549980__recomp(EEContext&);  // recompiled
void fn_sub_549A30_00549a30(EEContext&);  // generated body
void fn_sub_549A30_00549a30__recomp(EEContext&);  // recompiled
void fn_sub_549AC8_00549ac8(EEContext&);  // generated body
void fn_sub_549AC8_00549ac8__recomp(EEContext&);  // recompiled
void fn_sub_549AD0_00549ad0(EEContext&);  // generated body
void fn_sub_549AD0_00549ad0__recomp(EEContext&);  // recompiled
void fn_sub_549B68_00549b68(EEContext&);  // generated body
void fn_sub_549B68_00549b68__recomp(EEContext&);  // recompiled
void fn_sub_549C18_00549c18(EEContext&);  // generated body
void fn_sub_549C18_00549c18__recomp(EEContext&);  // recompiled
void fn_sub_549D40_00549d40(EEContext&);  // generated body
void fn_sub_549D40_00549d40__recomp(EEContext&);  // recompiled
void fn_sub_549E30_00549e30(EEContext&);  // generated body
void fn_sub_549E30_00549e30__recomp(EEContext&);  // recompiled
void fn_sub_549FB8_00549fb8(EEContext&);  // generated body
void fn_sub_549FB8_00549fb8__recomp(EEContext&);  // recompiled
void fn_sub_54A060_0054a060(EEContext&);  // generated body
void fn_sub_54A060_0054a060__recomp(EEContext&);  // recompiled
void fn_sub_54A0D0_0054a0d0(EEContext&);  // generated body
void fn_sub_54A0D0_0054a0d0__recomp(EEContext&);  // recompiled
void fn_sub_54A280_0054a280(EEContext&);  // generated body
void fn_sub_54A280_0054a280__recomp(EEContext&);  // recompiled
void fn_sub_54A2E8_0054a2e8(EEContext&);  // generated body
void fn_sub_54A2E8_0054a2e8__recomp(EEContext&);  // recompiled
void fn_sub_54A358_0054a358(EEContext&);  // generated body
void fn_sub_54A358_0054a358__recomp(EEContext&);  // recompiled
void fn_sub_54A598_0054a598(EEContext&);  // generated body
void fn_sub_54A598_0054a598__recomp(EEContext&);  // recompiled
void fn_sub_54A5E0_0054a5e0(EEContext&);  // generated body
void fn_sub_54A5E0_0054a5e0__recomp(EEContext&);  // recompiled
void fn_sub_54A640_0054a640(EEContext&);  // generated body
void fn_sub_54A640_0054a640__recomp(EEContext&);  // recompiled
void fn_sub_54A6C8_0054a6c8(EEContext&);  // generated body
void fn_sub_54A6C8_0054a6c8__recomp(EEContext&);  // recompiled
void fn_sub_54A6D0_0054a6d0(EEContext&);  // generated body
void fn_sub_54A6D0_0054a6d0__recomp(EEContext&);  // recompiled
void fn___env_lock_1_0054a6d8(EEContext&);  // generated body
void fn___env_lock_1_0054a6d8__recomp(EEContext&);  // recompiled
void fn___env_unlock_1_0054a6e0(EEContext&);  // generated body
void fn___env_unlock_1_0054a6e0__recomp(EEContext&);  // recompiled
void fn___env_lock_2_0054a6e8(EEContext&);  // generated body
void fn___env_lock_2_0054a6e8__recomp(EEContext&);  // recompiled
void fn___env_unlock_2_0054a6f0(EEContext&);  // generated body
void fn___env_unlock_2_0054a6f0__recomp(EEContext&);  // recompiled
void fn_sub_54A6F8_0054a6f8(EEContext&);  // generated body
void fn_sub_54A6F8_0054a6f8__recomp(EEContext&);  // recompiled
void fn_sub_54A840_0054a840(EEContext&);  // generated body
void fn_sub_54A840_0054a840__recomp(EEContext&);  // recompiled
void fn_sub_54A8C8_0054a8c8(EEContext&);  // generated body
void fn_sub_54A8C8_0054a8c8__recomp(EEContext&);  // recompiled
void fn_sub_54A9A0_0054a9a0(EEContext&);  // generated body
void fn_sub_54A9A0_0054a9a0__recomp(EEContext&);  // recompiled
void fn_sub_54A9E0_0054a9e0(EEContext&);  // generated body
void fn_sub_54A9E0_0054a9e0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_545598", 0x545598, &recomp_gen::fn_sub_545598_00545598, &recomp_gen::fn_sub_545598_00545598__recomp},
    {"sub_5455A0", 0x5455A0, &recomp_gen::fn_sub_5455A0_005455a0, &recomp_gen::fn_sub_5455A0_005455a0__recomp},
    {"sub_545608", 0x545608, &recomp_gen::fn_sub_545608_00545608, &recomp_gen::fn_sub_545608_00545608__recomp},
    {"sub_545620", 0x545620, &recomp_gen::fn_sub_545620_00545620, &recomp_gen::fn_sub_545620_00545620__recomp},
    {"sub_545628", 0x545628, &recomp_gen::fn_sub_545628_00545628, &recomp_gen::fn_sub_545628_00545628__recomp},
    {"sub_545630", 0x545630, &recomp_gen::fn_sub_545630_00545630, &recomp_gen::fn_sub_545630_00545630__recomp},
    {"sub_545638", 0x545638, &recomp_gen::fn_sub_545638_00545638, &recomp_gen::fn_sub_545638_00545638__recomp},
    {"sub_545640", 0x545640, &recomp_gen::fn_sub_545640_00545640, &recomp_gen::fn_sub_545640_00545640__recomp},
    {"sub_545648", 0x545648, &recomp_gen::fn_sub_545648_00545648, &recomp_gen::fn_sub_545648_00545648__recomp},
    {"sub_545650", 0x545650, &recomp_gen::fn_sub_545650_00545650, &recomp_gen::fn_sub_545650_00545650__recomp},
    {"sub_545658", 0x545658, &recomp_gen::fn_sub_545658_00545658, &recomp_gen::fn_sub_545658_00545658__recomp},
    {"sub_545680", 0x545680, &recomp_gen::fn_sub_545680_00545680, &recomp_gen::fn_sub_545680_00545680__recomp},
    {"sub_5456B0", 0x5456B0, &recomp_gen::fn_sub_5456B0_005456b0, &recomp_gen::fn_sub_5456B0_005456b0__recomp},
    {"sub_545718", 0x545718, &recomp_gen::fn_sub_545718_00545718, &recomp_gen::fn_sub_545718_00545718__recomp},
    {"sub_545798", 0x545798, &recomp_gen::fn_sub_545798_00545798, &recomp_gen::fn_sub_545798_00545798__recomp},
    {"sub_545898", 0x545898, &recomp_gen::fn_sub_545898_00545898, &recomp_gen::fn_sub_545898_00545898__recomp},
    {"sub_545900", 0x545900, &recomp_gen::fn_sub_545900_00545900, &recomp_gen::fn_sub_545900_00545900__recomp},
    {"sub_545908", 0x545908, &recomp_gen::fn_sub_545908_00545908, &recomp_gen::fn_sub_545908_00545908__recomp},
    {"sub_545910", 0x545910, &recomp_gen::fn_sub_545910_00545910, &recomp_gen::fn_sub_545910_00545910__recomp},
    {"sub_545918", 0x545918, &recomp_gen::fn_sub_545918_00545918, &recomp_gen::fn_sub_545918_00545918__recomp},
    {"sub_545920", 0x545920, &recomp_gen::fn_sub_545920_00545920, &recomp_gen::fn_sub_545920_00545920__recomp},
    {"sub_545940", 0x545940, &recomp_gen::fn_sub_545940_00545940, &recomp_gen::fn_sub_545940_00545940__recomp},
    {"expl_2", 0x545C50, &recomp_gen::fn_expl_2_00545c50, &recomp_gen::fn_expl_2_00545c50__recomp},
    {"sub_545C58", 0x545C58, &recomp_gen::fn_sub_545C58_00545c58, &recomp_gen::fn_sub_545C58_00545c58__recomp},
    {"hypotf_2", 0x545C68, &recomp_gen::fn_hypotf_2_00545c68, &recomp_gen::fn_hypotf_2_00545c68__recomp},
    {"sub_545CC0", 0x545CC0, &recomp_gen::fn_sub_545CC0_00545cc0, &recomp_gen::fn_sub_545CC0_00545cc0__recomp},
    {"sub_546360", 0x546360, &recomp_gen::fn_sub_546360_00546360, &recomp_gen::fn_sub_546360_00546360__recomp},
    {"sub_546E78", 0x546E78, &recomp_gen::fn_sub_546E78_00546e78, &recomp_gen::fn_sub_546E78_00546e78__recomp},
    {"sub_546F60", 0x546F60, &recomp_gen::fn_sub_546F60_00546f60, &recomp_gen::fn_sub_546F60_00546f60__recomp},
    {"sub_547060", 0x547060, &recomp_gen::fn_sub_547060_00547060, &recomp_gen::fn_sub_547060_00547060__recomp},
    {"sub_547180", 0x547180, &recomp_gen::fn_sub_547180_00547180, &recomp_gen::fn_sub_547180_00547180__recomp},
    {"sub_5471C0", 0x5471C0, &recomp_gen::fn_sub_5471C0_005471c0, &recomp_gen::fn_sub_5471C0_005471c0__recomp},
    {"sub_5471F0", 0x5471F0, &recomp_gen::fn_sub_5471F0_005471f0, &recomp_gen::fn_sub_5471F0_005471f0__recomp},
    {"sub_547200", 0x547200, &recomp_gen::fn_sub_547200_00547200, &recomp_gen::fn_sub_547200_00547200__recomp},
    {"sub_5472A0", 0x5472A0, &recomp_gen::fn_sub_5472A0_005472a0, &recomp_gen::fn_sub_5472A0_005472a0__recomp},
    {"sub_5473D8", 0x5473D8, &recomp_gen::fn_sub_5473D8_005473d8, &recomp_gen::fn_sub_5473D8_005473d8__recomp},
    {"sub_547428", 0x547428, &recomp_gen::fn_sub_547428_00547428, &recomp_gen::fn_sub_547428_00547428__recomp},
    {"sub_547488", 0x547488, &recomp_gen::fn_sub_547488_00547488, &recomp_gen::fn_sub_547488_00547488__recomp},
    {"sub_5474C8", 0x5474C8, &recomp_gen::fn_sub_5474C8_005474c8, &recomp_gen::fn_sub_5474C8_005474c8__recomp},
    {"sub_547510", 0x547510, &recomp_gen::fn_sub_547510_00547510, &recomp_gen::fn_sub_547510_00547510__recomp},
    {"ADXPS2_LoadFcacheDvd", 0x547768, &recomp_gen::fn_ADXPS2_LoadFcacheDvd_00547768, &recomp_gen::fn_ADXPS2_LoadFcacheDvd_00547768__recomp},
    {"sub_5477C8", 0x5477C8, &recomp_gen::fn_sub_5477C8_005477c8, &recomp_gen::fn_sub_5477C8_005477c8__recomp},
    {"sub_547830", 0x547830, &recomp_gen::fn_sub_547830_00547830, &recomp_gen::fn_sub_547830_00547830__recomp},
    {"atan2l_3", 0x547898, &recomp_gen::fn_atan2l_3_00547898, &recomp_gen::fn_atan2l_3_00547898__recomp},
    {"cosl_3", 0x5478B0, &recomp_gen::fn_cosl_3_005478b0, &recomp_gen::fn_cosl_3_005478b0__recomp},
    {"coshl_3", 0x5478C8, &recomp_gen::fn_coshl_3_005478c8, &recomp_gen::fn_coshl_3_005478c8__recomp},
    {"expl_3", 0x5478E0, &recomp_gen::fn_expl_3_005478e0, &recomp_gen::fn_expl_3_005478e0__recomp},
    {"hypotf_3", 0x5478F8, &recomp_gen::fn_hypotf_3_005478f8, &recomp_gen::fn_hypotf_3_005478f8__recomp},
    {"sub_547948", 0x547948, &recomp_gen::fn_sub_547948_00547948, &recomp_gen::fn_sub_547948_00547948__recomp},
    {"sceInsockSetErrnoMode_2", 0x5479E8, &recomp_gen::fn_sceInsockSetErrnoMode_2_005479e8, &recomp_gen::fn_sceInsockSetErrnoMode_2_005479e8__recomp},
    {"sceInsockGetErrnoMode_2", 0x5479F8, &recomp_gen::fn_sceInsockGetErrnoMode_2_005479f8, &recomp_gen::fn_sceInsockGetErrnoMode_2_005479f8__recomp},
    {"my_malloc_2", 0x547A08, &recomp_gen::fn_my_malloc_2_00547a08, &recomp_gen::fn_my_malloc_2_00547a08__recomp},
    {"sub_547A18", 0x547A18, &recomp_gen::fn_sub_547A18_00547a18, &recomp_gen::fn_sub_547A18_00547a18__recomp},
    {"sub_547A28", 0x547A28, &recomp_gen::fn_sub_547A28_00547a28, &recomp_gen::fn_sub_547A28_00547a28__recomp},
    {"powl_3", 0x547A70, &recomp_gen::fn_powl_3_00547a70, &recomp_gen::fn_powl_3_00547a70__recomp},
    {"sub_547AC0", 0x547AC0, &recomp_gen::fn_sub_547AC0_00547ac0, &recomp_gen::fn_sub_547AC0_00547ac0__recomp},
    {"sub_5482D8", 0x5482D8, &recomp_gen::fn_sub_5482D8_005482d8, &recomp_gen::fn_sub_5482D8_005482d8__recomp},
    {"sub_5487D0", 0x5487D0, &recomp_gen::fn_sub_5487D0_005487d0, &recomp_gen::fn_sub_5487D0_005487d0__recomp},
    {"sub_548838", 0x548838, &recomp_gen::fn_sub_548838_00548838, &recomp_gen::fn_sub_548838_00548838__recomp},
    {"sub_548950", 0x548950, &recomp_gen::fn_sub_548950_00548950, &recomp_gen::fn_sub_548950_00548950__recomp},
    {"sub_548E30", 0x548E30, &recomp_gen::fn_sub_548E30_00548e30, &recomp_gen::fn_sub_548E30_00548e30__recomp},
    {"sub_549050", 0x549050, &recomp_gen::fn_sub_549050_00549050, &recomp_gen::fn_sub_549050_00549050__recomp},
    {"sub_5490D8", 0x5490D8, &recomp_gen::fn_sub_5490D8_005490d8, &recomp_gen::fn_sub_5490D8_005490d8__recomp},
    {"sub_549350", 0x549350, &recomp_gen::fn_sub_549350_00549350, &recomp_gen::fn_sub_549350_00549350__recomp},
    {"sub_549418", 0x549418, &recomp_gen::fn_sub_549418_00549418, &recomp_gen::fn_sub_549418_00549418__recomp},
    {"sub_549598", 0x549598, &recomp_gen::fn_sub_549598_00549598, &recomp_gen::fn_sub_549598_00549598__recomp},
    {"sub_5495F0", 0x5495F0, &recomp_gen::fn_sub_5495F0_005495f0, &recomp_gen::fn_sub_5495F0_005495f0__recomp},
    {"sub_549658", 0x549658, &recomp_gen::fn_sub_549658_00549658, &recomp_gen::fn_sub_549658_00549658__recomp},
    {"sub_5496A8", 0x5496A8, &recomp_gen::fn_sub_5496A8_005496a8, &recomp_gen::fn_sub_5496A8_005496a8__recomp},
    {"sub_549728", 0x549728, &recomp_gen::fn_sub_549728_00549728, &recomp_gen::fn_sub_549728_00549728__recomp},
    {"sub_549768", 0x549768, &recomp_gen::fn_sub_549768_00549768, &recomp_gen::fn_sub_549768_00549768__recomp},
    {"sub_549870", 0x549870, &recomp_gen::fn_sub_549870_00549870, &recomp_gen::fn_sub_549870_00549870__recomp},
    {"sub_549980", 0x549980, &recomp_gen::fn_sub_549980_00549980, &recomp_gen::fn_sub_549980_00549980__recomp},
    {"sub_549A30", 0x549A30, &recomp_gen::fn_sub_549A30_00549a30, &recomp_gen::fn_sub_549A30_00549a30__recomp},
    {"sub_549AC8", 0x549AC8, &recomp_gen::fn_sub_549AC8_00549ac8, &recomp_gen::fn_sub_549AC8_00549ac8__recomp},
    {"sub_549AD0", 0x549AD0, &recomp_gen::fn_sub_549AD0_00549ad0, &recomp_gen::fn_sub_549AD0_00549ad0__recomp},
    {"sub_549B68", 0x549B68, &recomp_gen::fn_sub_549B68_00549b68, &recomp_gen::fn_sub_549B68_00549b68__recomp},
    {"sub_549C18", 0x549C18, &recomp_gen::fn_sub_549C18_00549c18, &recomp_gen::fn_sub_549C18_00549c18__recomp},
    {"sub_549D40", 0x549D40, &recomp_gen::fn_sub_549D40_00549d40, &recomp_gen::fn_sub_549D40_00549d40__recomp},
    {"sub_549E30", 0x549E30, &recomp_gen::fn_sub_549E30_00549e30, &recomp_gen::fn_sub_549E30_00549e30__recomp},
    {"sub_549FB8", 0x549FB8, &recomp_gen::fn_sub_549FB8_00549fb8, &recomp_gen::fn_sub_549FB8_00549fb8__recomp},
    {"sub_54A060", 0x54A060, &recomp_gen::fn_sub_54A060_0054a060, &recomp_gen::fn_sub_54A060_0054a060__recomp},
    {"sub_54A0D0", 0x54A0D0, &recomp_gen::fn_sub_54A0D0_0054a0d0, &recomp_gen::fn_sub_54A0D0_0054a0d0__recomp},
    {"sub_54A280", 0x54A280, &recomp_gen::fn_sub_54A280_0054a280, &recomp_gen::fn_sub_54A280_0054a280__recomp},
    {"sub_54A2E8", 0x54A2E8, &recomp_gen::fn_sub_54A2E8_0054a2e8, &recomp_gen::fn_sub_54A2E8_0054a2e8__recomp},
    {"sub_54A358", 0x54A358, &recomp_gen::fn_sub_54A358_0054a358, &recomp_gen::fn_sub_54A358_0054a358__recomp},
    {"sub_54A598", 0x54A598, &recomp_gen::fn_sub_54A598_0054a598, &recomp_gen::fn_sub_54A598_0054a598__recomp},
    {"sub_54A5E0", 0x54A5E0, &recomp_gen::fn_sub_54A5E0_0054a5e0, &recomp_gen::fn_sub_54A5E0_0054a5e0__recomp},
    {"sub_54A640", 0x54A640, &recomp_gen::fn_sub_54A640_0054a640, &recomp_gen::fn_sub_54A640_0054a640__recomp},
    {"sub_54A6C8", 0x54A6C8, &recomp_gen::fn_sub_54A6C8_0054a6c8, &recomp_gen::fn_sub_54A6C8_0054a6c8__recomp},
    {"sub_54A6D0", 0x54A6D0, &recomp_gen::fn_sub_54A6D0_0054a6d0, &recomp_gen::fn_sub_54A6D0_0054a6d0__recomp},
    {"__env_lock_1", 0x54A6D8, &recomp_gen::fn___env_lock_1_0054a6d8, &recomp_gen::fn___env_lock_1_0054a6d8__recomp},
    {"__env_unlock_1", 0x54A6E0, &recomp_gen::fn___env_unlock_1_0054a6e0, &recomp_gen::fn___env_unlock_1_0054a6e0__recomp},
    {"__env_lock_2", 0x54A6E8, &recomp_gen::fn___env_lock_2_0054a6e8, &recomp_gen::fn___env_lock_2_0054a6e8__recomp},
    {"__env_unlock_2", 0x54A6F0, &recomp_gen::fn___env_unlock_2_0054a6f0, &recomp_gen::fn___env_unlock_2_0054a6f0__recomp},
    {"sub_54A6F8", 0x54A6F8, &recomp_gen::fn_sub_54A6F8_0054a6f8, &recomp_gen::fn_sub_54A6F8_0054a6f8__recomp},
    {"sub_54A840", 0x54A840, &recomp_gen::fn_sub_54A840_0054a840, &recomp_gen::fn_sub_54A840_0054a840__recomp},
    {"sub_54A8C8", 0x54A8C8, &recomp_gen::fn_sub_54A8C8_0054a8c8, &recomp_gen::fn_sub_54A8C8_0054a8c8__recomp},
    {"sub_54A9A0", 0x54A9A0, &recomp_gen::fn_sub_54A9A0_0054a9a0, &recomp_gen::fn_sub_54A9A0_0054a9a0__recomp},
    {"sub_54A9E0", 0x54A9E0, &recomp_gen::fn_sub_54A9E0_0054a9e0, &recomp_gen::fn_sub_54A9E0_0054a9e0__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
// Output buffers for the snapshot sweeps: zero in every replay snapshot (stand_ins.h: zero from 0x1BC0000 up to the
// main-thread stack), so a body's writes through $a1..$a3 land on known bytes.
constexpr u32 kOut = 0x01E00000u;

namespace adxt = p3fes::game::cri2::adxt;
namespace enc = p3fes::game::libs9::adxenc;

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs19: no case for an address");
}
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u8 r8(Machine& m, u32 va) { return *m.at(va); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
std::vector<u8> snapshot(const char* dir) {
    std::vector<u8> snap = read_snapshot(dir);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot " << dir << " not found");
        snap.clear();
    }
    return snap;
}
void restore(Machine& m, const std::vector<u8>& snap) { std::memcpy(m.mem.main_ram(), snap.data(), snap.size()); }

// ---- the stand-ins ----------------------------------------------------------------------------------------------
// Only callees other tests of main already stand in (test_libs9.cpp's driver set and sprintf) and that no current
// packet claims. Every other callee either runs (hand-written or emitted) or ends the pair at the call, identically in
// both bodies (sub_53F298, sub_561688, sub_5616C8 and sub_564218 are other packets' and stay unstood). Recorders
// without scratch clobbering, returning `g_v0`; the ADX error reporter keeps its message, the time getter writes a
// time (samples, rate) through its two pointers.
u64 g_v0 = 0;
u32 g_time = 3 * 44100;
bool in_ram(u64 a) { return a < 0x01FFFF00u; }
std::string gstr(EEContext& ctx, u64 va) {
    std::string s;
    for (u32 a = static_cast<u32>(va); in_ram(a) && s.size() < 96; ++a) {
        const char ch = static_cast<char>(ctx.memory->read<u8>(a));
        if (!ch) break;
        s += ch;
    }
    return s;
}
void install_drivers(StandIns& s) {
    s.clobber_scratch = false;
    for (const auto& [va, name] : std::initializer_list<std::pair<u32, const char*>>{
             {0x546FA0u, "ADXSTM_SetReqRdSize"}, {0x5463A8u, "ADXSTM_SetBufSize"}, {0x546498u, "ADXSTM_Start"},
             {0x541A78u, "PS2RNA_SetTransSw (cosl_1)"}, {0x541A90u, "PS2RNA_SetPlaySw (coshl_1)"}})
        s.install_recorder(va, name, g_v0, 3);
    s.install(0x53AE08u, "ADXERR_CallErrFunc1", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, c.args[0]); }, 3);
    s.install(0x548B38u, "adxt_GetTime (sceInsockBind_2)", [](EEContext& ctx, StandIns&, StandInCall& c) {
        if (in_ram(c.args[1]) && c.args[1] >= 0x100000u) ctx.memory->write<u32>(static_cast<u32>(c.args[1]), g_time);
        if (in_ram(c.args[2]) && c.args[2] >= 0x100000u) ctx.memory->write<u32>(static_cast<u32>(c.args[2]), 44100u);
        c.v0 = 0;
    }, 3);
    install_sprintf(s, 3);
}

// Each body runs with its own stand-in set (a thunk installs it around the body); the two call logs must be equal.
StandIns* g_si[2] = {nullptr, nullptr};
Fn g_fn[2] = {nullptr, nullptr};
void thunk0(EEContext& ctx) {
    StandInsScope s(*g_si[0]);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(*g_si[1]);
    g_fn[1](ctx);
}
void same_log(const StandIns& a, const StandIns& b, const char* what) {
    INFO(what);
    CHECK(a.log.size() == b.log.size());
    for (std::size_t i = 0; i < std::min(a.log.size(), b.log.size()); ++i) {
        if (!(a.log[i] == b.log[i])) {
            INFO("stand-in call " << i << " differs (callee " << std::hex << a.log[i].va << " / " << b.log[i].va << ")");
            CHECK(false);
            break;
        }
    }
}

std::map<std::string, int> g_pairs;
u32 g_seed = 1;
// One pair from the machine's current state (hgp::pair: register file at every check point and at the end, all of
// RAM, scratchpad, BIOS window, bus log); the recompiled run's memory stays. `log` receives the hand body's calls.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, StandIns* log = nullptr) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_drivers(sh);
    install_drivers(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    hgp::Run r = hgp::pair(m, &thunk0, &thunk1, a, g_seed++, c.name, hw);
    same_log(sh, sr, c.name);
    if (log) log->log = sh.log;
    return r;
}
// The same comparison on a long-lived BaseRange (write_tracker.h): the snapshot stays the base and restore() copies
// back only the pages a pair wrote.
hgp::Run pr_base(Machine& m, BaseRange& ram, u32 addr, const Args& args, const HwCheck& hw) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_drivers(sh);
    install_drivers(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    ++g_pairs[c.name];
    const u32 seed = g_seed++;
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, &thunk0, args, seed, hw);
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, &thunk1, args, seed, hw);
    const bool bios_r = !hgp::bios_clean(m);
    INFO(c.name << " a0=" << std::hex << args[0] << " a1=" << args[1] << " a2=" << args[2] << " a3=" << args[3] << std::dec
                << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << std::hex << first);
        CHECK(false);
    }
    CHECK(h.spr == r.spr);
    CHECK(h.bus.size() == r.bus.size());
    CHECK(h.vu_control == r.vu_control);
    same_log(sh, sr, c.name);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
// A pair whose path is all hand-written, emitted or stood in: it must return.
u64 prv(Machine& m, u32 addr, Args a, StandIns* log = nullptr) {
    const hgp::Run r = pr(m, addr, a, {}, log);
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

// What $a0 is for each function in the snapshot sweep.
enum class Arg { None, Adxt, Stm, Enc };
Arg arg_of(u32 a) {
    if (a >= 0x545598u && a <= 0x545940u) return Arg::Enc;
    switch (a) {
    case 0x546E78u: case 0x546F60u: case 0x547180u: case 0x5471C0u: case 0x547200u: case 0x5472A0u: case 0x5473D8u:
    case 0x547428u:
        return Arg::Stm;
    case 0x547510u: case 0x5478F8u: case 0x548838u: case 0x548950u: case 0x548E30u: case 0x549050u: case 0x5490D8u:
    case 0x549350u: case 0x549418u: case 0x549598u: case 0x5495F0u: case 0x549658u: case 0x549728u: case 0x549768u:
    case 0x549870u: case 0x549980u: case 0x549A30u: case 0x549AC8u: case 0x549AD0u: case 0x549B68u: case 0x549C18u:
    case 0x549D40u: case 0x549E30u: case 0x54A060u: case 0x54A0D0u: case 0x54A280u: case 0x54A2E8u: case 0x54A358u:
    case 0x54A640u: case 0x54A840u: case 0x54A8C8u: case 0x54A9A0u: case 0x54A9E0u:
        return Arg::Adxt;
    default:
        return Arg::None;
    }
}

}  // namespace

TEST_CASE("game(libs19): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
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
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += pr(*m, c.addr, Args{a0, a1, a2, a3}).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The dorm (dorm_replay_4900), battle (b_5800) and climb (climb_ref_17000) snapshots hold live ADXT handles (the
// 16 x 200-byte pool of cri2.h) with their file streamers (+8); the ADX encoder pool is idle, so its functions run on
// its first two slots as they stand in the snapshot. Every function runs with the record its role takes -- each live
// handle and null for the ADXT wrappers, each live streamer for the ADXSTM ones, 0 / 1 / a zeroed output buffer
// otherwise -- second arguments from the values its branches test and the stood-in callees returning 0 or 1; each
// pair starts from the snapshot.
TEST_CASE("game(libs19): every body on the snapshots' live ADXT handles and streamers") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int runs = 0, stops = 0, live_adxt = 0, live_stm = 0;
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        std::vector<u64> handles, streamers;
        for (u32 i = 0; i < adxt::kCount; ++i) {
            const u32 h = adxt::kPool + i * adxt::kSize;
            if (r8(*m, h + adxt::kUsed) != 1) continue;
            handles.push_back(h);
            if (const u32 s = r32(*m, h + adxt::kStm); s != 0 && in_ram(s)) streamers.push_back(s);
        }
        live_adxt += static_cast<int>(handles.size());
        live_stm += static_cast<int>(streamers.size());
        handles.push_back(0);
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            std::vector<u64> a0s;
            switch (arg_of(c.addr)) {
            case Arg::Adxt: a0s = handles; break;
            case Arg::Stm: a0s = streamers; break;
            case Arg::Enc: a0s = {enc::kPool, enc::kPool + enc::kSize}; break;
            case Arg::None: a0s = {0, 1, kOut}; break;
            }
            for (u64 a0 : a0s)
                for (u64 a1 : {0ull, 1ull, 3ull})
                    for (u64 v : {0ull, 1ull}) {
                        g_v0 = v;
                        if (trace) std::fprintf(stderr, "%s %s a0 %llx a1 %llx v0 %llx\n", dir, c.name,
                                                (unsigned long long)a0, (unsigned long long)a1, (unsigned long long)v);
                        HwCheck hw;
                        hw.gpr_in = {{GPR_T0, kOut + 0x200}};
                        const hgp::Run r = pr_base(*m, base, c.addr, Args{a0, a1, kOut, kOut + 0x100}, hw);
                        base.restore();
                        ++runs;
                        stops += r.stopped ? 1 : 0;
                    }
        }
    }
    g_v0 = 0;
    MESSAGE(runs << " pairs from the snapshots (" << live_adxt << " live ADXT handles, " << live_stm
                 << " streamers), " << stops << " stopped identically");
}

// The ADX encoder's setters and getters on a handle in a zeroed world: each field at its documented offset, the AINF
// chunk's switch (the header offset grows by 36 when it turns on, and -- as in the binary -- again when it is reset),
// the input-joint index rule (< 2 unsigned), the key string's three key halfwords.
TEST_CASE("game(libs19): the ADX encoder's setters and getters") {
    auto m = machine();
    if (!m) return;
    const u32 h = kWorld;
    std::memset(m->at(kWorld), 0, kWorldSize);
    struct Set { u32 addr; s32 off; };
    for (const Set& s : {Set{0x545598u, enc::kBits}, Set{0x545608u, enc::kBlockSize}, Set{0x545620u, enc::kHighpass},
                         Set{0x545628u, enc::kLoopCnt}, Set{0x545630u, enc::kAlignSmpl}, Set{0x545638u, enc::kLoop},
                         Set{0x545640u, enc::kLoop + 4}, Set{0x545648u, enc::kLoop + 8}, Set{0x545650u, enc::kLoop + 12},
                         Set{0x545910u, enc::kSmplDone}, Set{0x545940u, enc::kSjOut}}) {
        const u32 v = 0x1000u + s.addr % 0x1000u;
        prv(*m, s.addr, {h, v, 0, 0});
        INFO(by_addr(s.addr).name);
        CHECK(r32(*m, h + s.off) == v);
    }
    w32(*m, h + enc::kOutBytes, 1234);
    CHECK(prv(*m, 0x545900u, {h, 0, 0, 0}) == 1234u);
    w32(*m, h + enc::kSmplDone, 777);
    CHECK(prv(*m, 0x545908u, {h, 0, 0, 0}) == 777u);
    CHECK(prv(*m, 0x545918u, {h, 0, 0, 0}) == 777u);
    // the input joints: indexes 0 and 1 only
    prv(*m, 0x545920u, {h, 1, 0x01811100u, 0});
    CHECK(r32(*m, h + enc::kSjIn + 4) == 0x01811100u);
    const u32 sj_out = r32(*m, h + enc::kSjOut);  // index 2 would land on the output joint
    prv(*m, 0x545920u, {h, 2, 0x01811200u, 0});
    CHECK(r32(*m, h + enc::kSjIn + 8) == sj_out);
    prv(*m, 0x545920u, {h, ~0ull, 0x01811300u, 0});
    CHECK(r32(*m, h + enc::kSjIn - 4) == 0u);
    // the AINF chunk: turned on once (+36 on the header offset), volume and pans; reset adds 36 again
    w32(*m, h + enc::kHdrOfs, 284);
    prv(*m, 0x545658u, {h, 100, 0, 0});
    CHECK(r8(*m, h + enc::kAinf) == 1);
    CHECK(r32(*m, h + enc::kHdrOfs) == 320u);
    CHECK(r16(*m, h + enc::kAinfVol) == 100);
    prv(*m, 0x545680u, {h, 1, 0xFFC0, 0});
    CHECK(r32(*m, h + enc::kHdrOfs) == 320u);  // already on
    CHECK(r16(*m, h + enc::kAinfPanR) == 0xFFC0);
    std::memcpy(m->at(kWorld + 0x800), "P3FES-AINF-TEXT-LONGER", 23);
    prv(*m, 0x5456B0u, {h, kWorld + 0x800, 0, 0});
    CHECK(std::memcmp(m->at(h + enc::kAinfData), "P3FES-AINF-TEXT-", 16) == 0);
    prv(*m, 0x545718u, {h, kWorld + 0x801, 0, 0});  // unaligned source
    CHECK(std::memcmp(m->at(h + enc::kAinfData), "3FES-AINF-TEXT-L", 16) == 0);
    prv(*m, 0x545798u, {h, 0, 0, 0});
    CHECK(r8(*m, h + enc::kAinf) == 0);
    CHECK(r32(*m, h + enc::kHdrOfs) == 356u);
    CHECK(r16(*m, h + enc::kAinfVol) == 0);
    CHECK(r16(*m, h + enc::kAinfPanL) == 0xFF80);
    CHECK(r16(*m, h + enc::kAinfPanR) == 0xFF80);
    for (u32 i = 0; i < 16; ++i) CHECK(r8(*m, h + enc::kAinfData + i) == 0);
    prv(*m, 0x545798u, {h, 0, 0, 0});
    CHECK(r32(*m, h + enc::kHdrOfs) == 356u);  // off: no change
    // the key string: three 15-bit keys
    std::memcpy(m->at(kWorld + 0x900), "persona3", 9);
    prv(*m, 0x545898u, {h, kWorld + 0x900, 0, 0});
    const u16 k0 = r16(*m, h + enc::kFlag720), k1 = r16(*m, h + enc::kFlag720 + 2), k2 = r16(*m, h + enc::kFlag720 + 4);
    CHECK(k0 < 0x8000);
    CHECK(k1 < 0x8000);
    CHECK(k2 < 0x8000);
    CHECK((k0 | k1 | k2) != 0);
    MESSAGE(summary());
}

// The ADXT and ADXSTM wrappers on a handle built in a zeroed world give their internals' results, and the
// null-handle reports pass through the lock stubs; the small globals' setters and getters; the empty stubs.
TEST_CASE("game(libs19): the wrappers' and small getters' rules") {
    auto m = machine();
    if (!m) return;
    const u32 h = kWorld;
    std::memset(m->at(kWorld), 0, kWorldSize);
    w8(*m, h + adxt::kStat, 5);
    w16(*m, h + adxt::kMinSct, 42);
    w32(*m, h + adxt::kTimeOfs, 900);
    w8(*m, h + adxt::kTrapFlag, 7);
    w8(*m, h + adxt::kStarted, 1);
    w32(*m, h + adxt::kSjd, kWorld + 0x400);
    // null handles: the internal's error number and result
    struct Null { u32 addr; const char* code; s32 result; };
    for (const Null& n : {Null{0x549050u, "E02080822", -1}, Null{0x5490D8u, "E02080821", -1}, Null{0x549E30u, "E02080802", -1},
                          Null{0x54A0D0u, "E02080829", -1}, Null{0x54A280u, "E02080833", 0}, Null{0x54A358u, "E02080831", -1}}) {
        StandIns log;
        const s32 v = sv(prv(*m, n.addr, {0, 0, 0, 0}, &log));
        INFO(by_addr(n.addr).name);
        CHECK(v == n.result);
        REQUIRE(log.log.size() == 1);
        CHECK(log.log[0].va == 0x53AE08u);
        CHECK(log.log[0].text.rfind(n.code, 0) == 0);
    }
    CHECK(sv(prv(*m, 0x549E30u, {h, 0, 0, 0})) == 1);  // status 5: play end
    CHECK(sv(prv(*m, 0x549AC8u, {h, 0, 0, 0})) == 42);
    CHECK(prv(*m, 0x54A840u, {h, 0, 0, 0}) == 900u);
    CHECK(prv(*m, 0x54A9A0u, {h, 0, 0, 0}) == 7u);
    CHECK(sv(prv(*m, 0x54A358u, {h, 0, 0, 0})) == 1);
    prv(*m, 0x549728u, {h, 1, 0, 0});
    CHECK(r8(*m, h + adxt::kPanMode) == 1);
    CHECK(prv(*m, 0x549768u, {h, 0, 0, 0}) == 1u);
    prv(*m, 0x54A2E8u, {h, 1, 0, 0});
    CHECK(r8(*m, h + adxt::kHold) == 1);
    prv(*m, 0x54A9E0u, {h, 0x11, 0x22, 0});
    CHECK(r32(*m, kWorld + 0x400 + 80) == 0x11u);
    CHECK(r32(*m, kWorld + 0x400 + 84) == 0x22u);
    w32(*m, h + adxt::kStm, kWorld + 0x600);
    CHECK(prv(*m, 0x54A640u, {h, 0, 0, 0}) == kWorld + 0x600);
    // the streamer wrappers: the request size and word +4
    prv(*m, 0x5473D8u, {kWorld + 0x600, 9, 0, 0});
    CHECK(r32(*m, kWorld + 0x600 + 20) == 9u);
    CHECK(r32(*m, kWorld + 0x600 + 16) == 9u << 11);
    w32(*m, kWorld + 0x600 + 4, 0xABCD);
    CHECK(prv(*m, 0x546F60u, {kWorld + 0x600, 0, 0, 0}) == 0xABCDu);
    // ADXSTM's word 0x792BD0, through the lock stubs
    prv(*m, 0x547488u, {55, 0, 0, 0});
    CHECK(r32(*m, 0x792BD0u) == 55u);
    CHECK(prv(*m, 0x5474C8u, {0, 0, 0, 0}) == 55u);
    // the 0x792BC4 / 0x792BC8 pair
    prv(*m, 0x545C58u, {12, 0, 0, 0});
    CHECK(r32(*m, 0x792BC4u) == 28u);
    CHECK(r32(*m, 0x792BC8u) == 12u);
    // the small globals
    prv(*m, 0x5479E8u, {3, 0, 0, 0});
    CHECK(prv(*m, 0x5479F8u, {0, 0, 0, 0}) == 3u);
    prv(*m, 0x547A18u, {0x4444, 0, 0, 0});
    CHECK(prv(*m, 0x547A08u, {0, 0, 0, 0}) == 0x4444u);
    prv(*m, 0x5478B0u, {1, 0, 0, 0});
    CHECK(prv(*m, 0x5478C8u, {0, 0, 0, 0}) == 1u);
    prv(*m, 0x5478B0u, {2, 0, 0, 0});  // 2 and up store 0
    CHECK(prv(*m, 0x5478C8u, {0, 0, 0, 0}) == 0u);
    // *$a1 = 0, result 1; the signed byte +73; the zero getter
    w32(*m, kWorld + 0x700, 99);
    CHECK(prv(*m, 0x5471F0u, {0, kWorld + 0x700, 0, 0}) == 1u);
    CHECK(r32(*m, kWorld + 0x700) == 0u);
    w8(*m, kWorld + 73, 0xF0);
    CHECK(sv(prv(*m, 0x546360u, {kWorld, 0, 0, 0})) == -16);
    CHECK(prv(*m, 0x54A6D0u, {0, 0, 0, 0}) == 0u);
    // the empty stubs leave every register (hgp::pair compares the files)
    for (u32 a : {0x545CC0u, 0x547060u, 0x54A6C8u, 0x54A6D8u, 0x54A6E0u, 0x54A6E8u, 0x54A6F0u}) prv(*m, a, {1, 2, 3, 4});
    MESSAGE(summary());
}

// The disc-range starters build the name "%08x.%08x" of (start sector, length rounded up to sectors) in their frame
// before the call; the name stays in the dead stack whatever the callee does (its frame lies below).
TEST_CASE("game(libs19): the disc-range name") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(kWorld), 0, kWorldSize);
    const u32 sp = kWorld + 0x8000;
    for (u32 addr : {0x5478F8u, 0x547948u}) {
        pr(*m, addr, {0, 0x1A2B, 4097, 0}, {{GPR_SP, sp}});
        INFO(by_addr(addr).name);
        CHECK(std::string(reinterpret_cast<const char*>(m->at(sp - 0x30))) == "00001a2b.00000003");
    }
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs19): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
