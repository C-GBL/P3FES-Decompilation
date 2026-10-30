// Pair tests for slice libs20 (game/src/cri/libs20.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the BIOS window and the bus log), with stand-ins for DTX_CallUrpc (scripted reply
// words), scePrintf, the ADX error callback and the streamer state. Worlds: random ones, the RAM of three replay
// snapshots, and built structures with documented-rule checks: the ADXT error check's counters and codes, the init
// counters, the bit masks, the AIX info readers, CRI CFG, SRD / HTCI settings, DTR records, the block header, the DTX
// URPC argument and reply blocks, and the memory-file handles (open, seek, tell, read, sector length).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs20.h"

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
void fn_sub_54AA48_0054aa48(EEContext&);  // generated body
void fn_sub_54AA48_0054aa48__recomp(EEContext&);  // recompiled
void fn_sub_54AAB8_0054aab8(EEContext&);  // generated body
void fn_sub_54AAB8_0054aab8__recomp(EEContext&);  // recompiled
void fn_sub_54AB28_0054ab28(EEContext&);  // generated body
void fn_sub_54AB28_0054ab28__recomp(EEContext&);  // recompiled
void fn_sub_54AE80_0054ae80(EEContext&);  // generated body
void fn_sub_54AE80_0054ae80__recomp(EEContext&);  // recompiled
void fn_sub_54AFA8_0054afa8(EEContext&);  // generated body
void fn_sub_54AFA8_0054afa8__recomp(EEContext&);  // recompiled
void fn_sub_54AFF0_0054aff0(EEContext&);  // generated body
void fn_sub_54AFF0_0054aff0__recomp(EEContext&);  // recompiled
void fn_sub_54B030_0054b030(EEContext&);  // generated body
void fn_sub_54B030_0054b030__recomp(EEContext&);  // recompiled
void fn_sub_54B1D0_0054b1d0(EEContext&);  // generated body
void fn_sub_54B1D0_0054b1d0__recomp(EEContext&);  // recompiled
void fn_sceInsockAbortGethostbyaddr_2_0054b348(EEContext&);  // generated body
void fn_sceInsockAbortGethostbyaddr_2_0054b348__recomp(EEContext&);  // recompiled
void fn_set_new_handler__FPFv_v_0054c0e8(EEContext&);  // generated body
void fn_set_new_handler__FPFv_v_0054c0e8__recomp(EEContext&);  // recompiled
void fn_sub_54C670_0054c670(EEContext&);  // generated body
void fn_sub_54C670_0054c670__recomp(EEContext&);  // recompiled
void fn_sub_54CAD0_0054cad0(EEContext&);  // generated body
void fn_sub_54CAD0_0054cad0__recomp(EEContext&);  // recompiled
void fn_sub_54D010_0054d010(EEContext&);  // generated body
void fn_sub_54D010_0054d010__recomp(EEContext&);  // recompiled
void fn_sub_54D560_0054d560(EEContext&);  // generated body
void fn_sub_54D560_0054d560__recomp(EEContext&);  // recompiled
void fn_sub_54D588_0054d588(EEContext&);  // generated body
void fn_sub_54D588_0054d588__recomp(EEContext&);  // recompiled
void fn_sqrtl_5_0054d5b0(EEContext&);  // generated body
void fn_sqrtl_5_0054d5b0__recomp(EEContext&);  // recompiled
void fn_sub_54D5D8_0054d5d8(EEContext&);  // generated body
void fn_sub_54D5D8_0054d5d8__recomp(EEContext&);  // recompiled
void fn_valloc_0_0054d5f8(EEContext&);  // generated body
void fn_valloc_0_0054d5f8__recomp(EEContext&);  // recompiled
void fn_pvalloc_0_0054d618(EEContext&);  // generated body
void fn_pvalloc_0_0054d618__recomp(EEContext&);  // recompiled
void fn_sub_54D668_0054d668(EEContext&);  // generated body
void fn_sub_54D668_0054d668__recomp(EEContext&);  // recompiled
void fn_sub_54D818_0054d818(EEContext&);  // generated body
void fn_sub_54D818_0054d818__recomp(EEContext&);  // recompiled
void fn_sub_54DC48_0054dc48(EEContext&);  // generated body
void fn_sub_54DC48_0054dc48__recomp(EEContext&);  // recompiled
void fn_sub_54DDF8_0054ddf8(EEContext&);  // generated body
void fn_sub_54DDF8_0054ddf8__recomp(EEContext&);  // recompiled
void fn_sub_54DE18_0054de18(EEContext&);  // generated body
void fn_sub_54DE18_0054de18__recomp(EEContext&);  // recompiled
void fn_sub_54E810_0054e810(EEContext&);  // generated body
void fn_sub_54E810_0054e810__recomp(EEContext&);  // recompiled
void fn_sub_554998_00554998(EEContext&);  // generated body
void fn_sub_554998_00554998__recomp(EEContext&);  // recompiled
void fn_sub_554A00_00554a00(EEContext&);  // generated body
void fn_sub_554A00_00554a00__recomp(EEContext&);  // recompiled
void fn_sub_554AA0_00554aa0(EEContext&);  // generated body
void fn_sub_554AA0_00554aa0__recomp(EEContext&);  // recompiled
void fn_sub_5556A0_005556a0(EEContext&);  // generated body
void fn_sub_5556A0_005556a0__recomp(EEContext&);  // recompiled
void fn_sub_555720_00555720(EEContext&);  // generated body
void fn_sub_555720_00555720__recomp(EEContext&);  // recompiled
void fn_sub_555820_00555820(EEContext&);  // generated body
void fn_sub_555820_00555820__recomp(EEContext&);  // recompiled
void fn_sub_555A08_00555a08(EEContext&);  // generated body
void fn_sub_555A08_00555a08__recomp(EEContext&);  // recompiled
void fn_sub_557F60_00557f60(EEContext&);  // generated body
void fn_sub_557F60_00557f60__recomp(EEContext&);  // recompiled
void fn_sub_5580F8_005580f8(EEContext&);  // generated body
void fn_sub_5580F8_005580f8__recomp(EEContext&);  // recompiled
void fn_sub_558108_00558108(EEContext&);  // generated body
void fn_sub_558108_00558108__recomp(EEContext&);  // recompiled
void fn_sub_558118_00558118(EEContext&);  // generated body
void fn_sub_558118_00558118__recomp(EEContext&);  // recompiled
void fn___errno_3_00558128(EEContext&);  // generated body
void fn___errno_3_00558128__recomp(EEContext&);  // recompiled
void fn_sub_5585F0_005585f0(EEContext&);  // generated body
void fn_sub_5585F0_005585f0__recomp(EEContext&);  // recompiled
void fn___errno_5_00558600(EEContext&);  // generated body
void fn___errno_5_00558600__recomp(EEContext&);  // recompiled
void fn_sub_558678_00558678(EEContext&);  // generated body
void fn_sub_558678_00558678__recomp(EEContext&);  // recompiled
void fn_sub_5586B0_005586b0(EEContext&);  // generated body
void fn_sub_5586B0_005586b0__recomp(EEContext&);  // recompiled
void fn_sub_5586E8_005586e8(EEContext&);  // generated body
void fn_sub_5586E8_005586e8__recomp(EEContext&);  // recompiled
void fn_sub_558720_00558720(EEContext&);  // generated body
void fn_sub_558720_00558720__recomp(EEContext&);  // recompiled
void fn_sub_558758_00558758(EEContext&);  // generated body
void fn_sub_558758_00558758__recomp(EEContext&);  // recompiled
void fn_sub_558898_00558898(EEContext&);  // generated body
void fn_sub_558898_00558898__recomp(EEContext&);  // recompiled
void fn_sub_558968_00558968(EEContext&);  // generated body
void fn_sub_558968_00558968__recomp(EEContext&);  // recompiled
void fn_sub_558978_00558978(EEContext&);  // generated body
void fn_sub_558978_00558978__recomp(EEContext&);  // recompiled
void fn_sub_5589A8_005589a8(EEContext&);  // generated body
void fn_sub_5589A8_005589a8__recomp(EEContext&);  // recompiled
void fn_sub_559200_00559200(EEContext&);  // generated body
void fn_sub_559200_00559200__recomp(EEContext&);  // recompiled
void fn_sub_5596D0_005596d0(EEContext&);  // generated body
void fn_sub_5596D0_005596d0__recomp(EEContext&);  // recompiled
void fn_sub_559700_00559700(EEContext&);  // generated body
void fn_sub_559700_00559700__recomp(EEContext&);  // recompiled
void fn_sub_559E30_00559e30(EEContext&);  // generated body
void fn_sub_559E30_00559e30__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_6_0055b6d8(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_6_0055b6d8__recomp(EEContext&);  // recompiled
void fn_cosl_7_0055b700(EEContext&);  // generated body
void fn_cosl_7_0055b700__recomp(EEContext&);  // recompiled
void fn_coshl_7_0055b718(EEContext&);  // generated body
void fn_coshl_7_0055b718__recomp(EEContext&);  // recompiled
void fn_expl_7_0055b730(EEContext&);  // generated body
void fn_expl_7_0055b730__recomp(EEContext&);  // recompiled
void fn_hypotf_7_0055b748(EEContext&);  // generated body
void fn_hypotf_7_0055b748__recomp(EEContext&);  // recompiled
void fn_sub_55B760_0055b760(EEContext&);  // generated body
void fn_sub_55B760_0055b760__recomp(EEContext&);  // recompiled
void fn_sub_55B848_0055b848(EEContext&);  // generated body
void fn_sub_55B848_0055b848__recomp(EEContext&);  // recompiled
void fn_sub_55BA50_0055ba50(EEContext&);  // generated body
void fn_sub_55BA50_0055ba50__recomp(EEContext&);  // recompiled
void fn_sub_55BB08_0055bb08(EEContext&);  // generated body
void fn_sub_55BB08_0055bb08__recomp(EEContext&);  // recompiled
void fn_sub_55BDC8_0055bdc8(EEContext&);  // generated body
void fn_sub_55BDC8_0055bdc8__recomp(EEContext&);  // recompiled
void fn_sub_55BF40_0055bf40(EEContext&);  // generated body
void fn_sub_55BF40_0055bf40__recomp(EEContext&);  // recompiled
void fn_sub_55CF58_0055cf58(EEContext&);  // generated body
void fn_sub_55CF58_0055cf58__recomp(EEContext&);  // recompiled
void fn_sub_55D0B0_0055d0b0(EEContext&);  // generated body
void fn_sub_55D0B0_0055d0b0__recomp(EEContext&);  // recompiled
void fn_sub_55D0D8_0055d0d8(EEContext&);  // generated body
void fn_sub_55D0D8_0055d0d8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_7_0055d188(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_7_0055d188__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_8_0055d200(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_8_0055d200__recomp(EEContext&);  // recompiled
void fn_WTLS_get_table_0055d210(EEContext&);  // generated body
void fn_WTLS_get_table_0055d210__recomp(EEContext&);  // recompiled
void fn___errno_9_0055d230(EEContext&);  // generated body
void fn___errno_9_0055d230__recomp(EEContext&);  // recompiled
void fn_sub_55D6F0_0055d6f0(EEContext&);  // generated body
void fn_sub_55D6F0_0055d6f0__recomp(EEContext&);  // recompiled
void fn_sub_55DAE0_0055dae0(EEContext&);  // generated body
void fn_sub_55DAE0_0055dae0__recomp(EEContext&);  // recompiled
void fn_sub_55E498_0055e498(EEContext&);  // generated body
void fn_sub_55E498_0055e498__recomp(EEContext&);  // recompiled
void fn_sub_55E538_0055e538(EEContext&);  // generated body
void fn_sub_55E538_0055e538__recomp(EEContext&);  // recompiled
void fn_sub_55E580_0055e580(EEContext&);  // generated body
void fn_sub_55E580_0055e580__recomp(EEContext&);  // recompiled
void fn_sub_55E640_0055e640(EEContext&);  // generated body
void fn_sub_55E640_0055e640__recomp(EEContext&);  // recompiled
void fn_sub_55E678_0055e678(EEContext&);  // generated body
void fn_sub_55E678_0055e678__recomp(EEContext&);  // recompiled
void fn_sub_55E850_0055e850(EEContext&);  // generated body
void fn_sub_55E850_0055e850__recomp(EEContext&);  // recompiled
void fn_sub_55E888_0055e888(EEContext&);  // generated body
void fn_sub_55E888_0055e888__recomp(EEContext&);  // recompiled
void fn_sub_55E8C0_0055e8c0(EEContext&);  // generated body
void fn_sub_55E8C0_0055e8c0__recomp(EEContext&);  // recompiled
void fn_sub_55EFC8_0055efc8(EEContext&);  // generated body
void fn_sub_55EFC8_0055efc8__recomp(EEContext&);  // recompiled
void fn_sub_55F640_0055f640(EEContext&);  // generated body
void fn_sub_55F640_0055f640__recomp(EEContext&);  // recompiled
void fn_sub_560DE8_00560de8(EEContext&);  // generated body
void fn_sub_560DE8_00560de8__recomp(EEContext&);  // recompiled
void fn_sub_560E30_00560e30(EEContext&);  // generated body
void fn_sub_560E30_00560e30__recomp(EEContext&);  // recompiled
void fn_sub_5613E0_005613e0(EEContext&);  // generated body
void fn_sub_5613E0_005613e0__recomp(EEContext&);  // recompiled
void fn_sub_561518_00561518(EEContext&);  // generated body
void fn_sub_561518_00561518__recomp(EEContext&);  // recompiled
void fn_sub_561560_00561560(EEContext&);  // generated body
void fn_sub_561560_00561560__recomp(EEContext&);  // recompiled
void fn_nullsub_144_005615a8(EEContext&);  // generated body
void fn_nullsub_144_005615a8__recomp(EEContext&);  // recompiled
void fn_sub_5615F8_005615f8(EEContext&);  // generated body
void fn_sub_5615F8_005615f8__recomp(EEContext&);  // recompiled
void fn_sub_561708_00561708(EEContext&);  // generated body
void fn_sub_561708_00561708__recomp(EEContext&);  // recompiled
void fn_sub_561718_00561718(EEContext&);  // generated body
void fn_sub_561718_00561718__recomp(EEContext&);  // recompiled
void fn_sub_563DD0_00563dd0(EEContext&);  // generated body
void fn_sub_563DD0_00563dd0__recomp(EEContext&);  // recompiled
void fn_sub_563F38_00563f38(EEContext&);  // generated body
void fn_sub_563F38_00563f38__recomp(EEContext&);  // recompiled
void fn_sub_563F90_00563f90(EEContext&);  // generated body
void fn_sub_563F90_00563f90__recomp(EEContext&);  // recompiled
void fn_sub_564068_00564068(EEContext&);  // generated body
void fn_sub_564068_00564068__recomp(EEContext&);  // recompiled
void fn_sub_5640D8_005640d8(EEContext&);  // generated body
void fn_sub_5640D8_005640d8__recomp(EEContext&);  // recompiled
void fn_sub_564108_00564108(EEContext&);  // generated body
void fn_sub_564108_00564108__recomp(EEContext&);  // recompiled
void fn_sub_564178_00564178(EEContext&);  // generated body
void fn_sub_564178_00564178__recomp(EEContext&);  // recompiled
void fn_sub_5641C8_005641c8(EEContext&);  // generated body
void fn_sub_5641C8_005641c8__recomp(EEContext&);  // recompiled
void fn_sub_564268_00564268(EEContext&);  // generated body
void fn_sub_564268_00564268__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_54AA48", 0x54AA48, &recomp_gen::fn_sub_54AA48_0054aa48, &recomp_gen::fn_sub_54AA48_0054aa48__recomp},
    {"sub_54AAB8", 0x54AAB8, &recomp_gen::fn_sub_54AAB8_0054aab8, &recomp_gen::fn_sub_54AAB8_0054aab8__recomp},
    {"sub_54AB28", 0x54AB28, &recomp_gen::fn_sub_54AB28_0054ab28, &recomp_gen::fn_sub_54AB28_0054ab28__recomp},
    {"sub_54AE80", 0x54AE80, &recomp_gen::fn_sub_54AE80_0054ae80, &recomp_gen::fn_sub_54AE80_0054ae80__recomp},
    {"sub_54AFA8", 0x54AFA8, &recomp_gen::fn_sub_54AFA8_0054afa8, &recomp_gen::fn_sub_54AFA8_0054afa8__recomp},
    {"sub_54AFF0", 0x54AFF0, &recomp_gen::fn_sub_54AFF0_0054aff0, &recomp_gen::fn_sub_54AFF0_0054aff0__recomp},
    {"sub_54B030", 0x54B030, &recomp_gen::fn_sub_54B030_0054b030, &recomp_gen::fn_sub_54B030_0054b030__recomp},
    {"sub_54B1D0", 0x54B1D0, &recomp_gen::fn_sub_54B1D0_0054b1d0, &recomp_gen::fn_sub_54B1D0_0054b1d0__recomp},
    {"sceInsockAbortGethostbyaddr_2", 0x54B348, &recomp_gen::fn_sceInsockAbortGethostbyaddr_2_0054b348, &recomp_gen::fn_sceInsockAbortGethostbyaddr_2_0054b348__recomp},
    {"set_new_handler__FPFv_v", 0x54C0E8, &recomp_gen::fn_set_new_handler__FPFv_v_0054c0e8, &recomp_gen::fn_set_new_handler__FPFv_v_0054c0e8__recomp},
    {"sub_54C670", 0x54C670, &recomp_gen::fn_sub_54C670_0054c670, &recomp_gen::fn_sub_54C670_0054c670__recomp},
    {"sub_54CAD0", 0x54CAD0, &recomp_gen::fn_sub_54CAD0_0054cad0, &recomp_gen::fn_sub_54CAD0_0054cad0__recomp},
    {"sub_54D010", 0x54D010, &recomp_gen::fn_sub_54D010_0054d010, &recomp_gen::fn_sub_54D010_0054d010__recomp},
    {"sub_54D560", 0x54D560, &recomp_gen::fn_sub_54D560_0054d560, &recomp_gen::fn_sub_54D560_0054d560__recomp},
    {"sub_54D588", 0x54D588, &recomp_gen::fn_sub_54D588_0054d588, &recomp_gen::fn_sub_54D588_0054d588__recomp},
    {"sqrtl_5", 0x54D5B0, &recomp_gen::fn_sqrtl_5_0054d5b0, &recomp_gen::fn_sqrtl_5_0054d5b0__recomp},
    {"sub_54D5D8", 0x54D5D8, &recomp_gen::fn_sub_54D5D8_0054d5d8, &recomp_gen::fn_sub_54D5D8_0054d5d8__recomp},
    {"valloc_0", 0x54D5F8, &recomp_gen::fn_valloc_0_0054d5f8, &recomp_gen::fn_valloc_0_0054d5f8__recomp},
    {"pvalloc_0", 0x54D618, &recomp_gen::fn_pvalloc_0_0054d618, &recomp_gen::fn_pvalloc_0_0054d618__recomp},
    {"sub_54D668", 0x54D668, &recomp_gen::fn_sub_54D668_0054d668, &recomp_gen::fn_sub_54D668_0054d668__recomp},
    {"sub_54D818", 0x54D818, &recomp_gen::fn_sub_54D818_0054d818, &recomp_gen::fn_sub_54D818_0054d818__recomp},
    {"sub_54DC48", 0x54DC48, &recomp_gen::fn_sub_54DC48_0054dc48, &recomp_gen::fn_sub_54DC48_0054dc48__recomp},
    {"sub_54DDF8", 0x54DDF8, &recomp_gen::fn_sub_54DDF8_0054ddf8, &recomp_gen::fn_sub_54DDF8_0054ddf8__recomp},
    {"sub_54DE18", 0x54DE18, &recomp_gen::fn_sub_54DE18_0054de18, &recomp_gen::fn_sub_54DE18_0054de18__recomp},
    {"sub_54E810", 0x54E810, &recomp_gen::fn_sub_54E810_0054e810, &recomp_gen::fn_sub_54E810_0054e810__recomp},
    {"sub_554998", 0x554998, &recomp_gen::fn_sub_554998_00554998, &recomp_gen::fn_sub_554998_00554998__recomp},
    {"sub_554A00", 0x554A00, &recomp_gen::fn_sub_554A00_00554a00, &recomp_gen::fn_sub_554A00_00554a00__recomp},
    {"sub_554AA0", 0x554AA0, &recomp_gen::fn_sub_554AA0_00554aa0, &recomp_gen::fn_sub_554AA0_00554aa0__recomp},
    {"sub_5556A0", 0x5556A0, &recomp_gen::fn_sub_5556A0_005556a0, &recomp_gen::fn_sub_5556A0_005556a0__recomp},
    {"sub_555720", 0x555720, &recomp_gen::fn_sub_555720_00555720, &recomp_gen::fn_sub_555720_00555720__recomp},
    {"sub_555820", 0x555820, &recomp_gen::fn_sub_555820_00555820, &recomp_gen::fn_sub_555820_00555820__recomp},
    {"sub_555A08", 0x555A08, &recomp_gen::fn_sub_555A08_00555a08, &recomp_gen::fn_sub_555A08_00555a08__recomp},
    {"sub_557F60", 0x557F60, &recomp_gen::fn_sub_557F60_00557f60, &recomp_gen::fn_sub_557F60_00557f60__recomp},
    {"sub_5580F8", 0x5580F8, &recomp_gen::fn_sub_5580F8_005580f8, &recomp_gen::fn_sub_5580F8_005580f8__recomp},
    {"sub_558108", 0x558108, &recomp_gen::fn_sub_558108_00558108, &recomp_gen::fn_sub_558108_00558108__recomp},
    {"sub_558118", 0x558118, &recomp_gen::fn_sub_558118_00558118, &recomp_gen::fn_sub_558118_00558118__recomp},
    {"__errno_3", 0x558128, &recomp_gen::fn___errno_3_00558128, &recomp_gen::fn___errno_3_00558128__recomp},
    {"sub_5585F0", 0x5585F0, &recomp_gen::fn_sub_5585F0_005585f0, &recomp_gen::fn_sub_5585F0_005585f0__recomp},
    {"__errno_5", 0x558600, &recomp_gen::fn___errno_5_00558600, &recomp_gen::fn___errno_5_00558600__recomp},
    {"sub_558678", 0x558678, &recomp_gen::fn_sub_558678_00558678, &recomp_gen::fn_sub_558678_00558678__recomp},
    {"sub_5586B0", 0x5586B0, &recomp_gen::fn_sub_5586B0_005586b0, &recomp_gen::fn_sub_5586B0_005586b0__recomp},
    {"sub_5586E8", 0x5586E8, &recomp_gen::fn_sub_5586E8_005586e8, &recomp_gen::fn_sub_5586E8_005586e8__recomp},
    {"sub_558720", 0x558720, &recomp_gen::fn_sub_558720_00558720, &recomp_gen::fn_sub_558720_00558720__recomp},
    {"sub_558758", 0x558758, &recomp_gen::fn_sub_558758_00558758, &recomp_gen::fn_sub_558758_00558758__recomp},
    {"sub_558898", 0x558898, &recomp_gen::fn_sub_558898_00558898, &recomp_gen::fn_sub_558898_00558898__recomp},
    {"sub_558968", 0x558968, &recomp_gen::fn_sub_558968_00558968, &recomp_gen::fn_sub_558968_00558968__recomp},
    {"sub_558978", 0x558978, &recomp_gen::fn_sub_558978_00558978, &recomp_gen::fn_sub_558978_00558978__recomp},
    {"sub_5589A8", 0x5589A8, &recomp_gen::fn_sub_5589A8_005589a8, &recomp_gen::fn_sub_5589A8_005589a8__recomp},
    {"sub_559200", 0x559200, &recomp_gen::fn_sub_559200_00559200, &recomp_gen::fn_sub_559200_00559200__recomp},
    {"sub_5596D0", 0x5596D0, &recomp_gen::fn_sub_5596D0_005596d0, &recomp_gen::fn_sub_5596D0_005596d0__recomp},
    {"sub_559700", 0x559700, &recomp_gen::fn_sub_559700_00559700, &recomp_gen::fn_sub_559700_00559700__recomp},
    {"sub_559E30", 0x559E30, &recomp_gen::fn_sub_559E30_00559e30, &recomp_gen::fn_sub_559E30_00559e30__recomp},
    {"sceLibgcc32GetErxEntries_6", 0x55B6D8, &recomp_gen::fn_sceLibgcc32GetErxEntries_6_0055b6d8, &recomp_gen::fn_sceLibgcc32GetErxEntries_6_0055b6d8__recomp},
    {"cosl_7", 0x55B700, &recomp_gen::fn_cosl_7_0055b700, &recomp_gen::fn_cosl_7_0055b700__recomp},
    {"coshl_7", 0x55B718, &recomp_gen::fn_coshl_7_0055b718, &recomp_gen::fn_coshl_7_0055b718__recomp},
    {"expl_7", 0x55B730, &recomp_gen::fn_expl_7_0055b730, &recomp_gen::fn_expl_7_0055b730__recomp},
    {"hypotf_7", 0x55B748, &recomp_gen::fn_hypotf_7_0055b748, &recomp_gen::fn_hypotf_7_0055b748__recomp},
    {"sub_55B760", 0x55B760, &recomp_gen::fn_sub_55B760_0055b760, &recomp_gen::fn_sub_55B760_0055b760__recomp},
    {"sub_55B848", 0x55B848, &recomp_gen::fn_sub_55B848_0055b848, &recomp_gen::fn_sub_55B848_0055b848__recomp},
    {"sub_55BA50", 0x55BA50, &recomp_gen::fn_sub_55BA50_0055ba50, &recomp_gen::fn_sub_55BA50_0055ba50__recomp},
    {"sub_55BB08", 0x55BB08, &recomp_gen::fn_sub_55BB08_0055bb08, &recomp_gen::fn_sub_55BB08_0055bb08__recomp},
    {"sub_55BDC8", 0x55BDC8, &recomp_gen::fn_sub_55BDC8_0055bdc8, &recomp_gen::fn_sub_55BDC8_0055bdc8__recomp},
    {"sub_55BF40", 0x55BF40, &recomp_gen::fn_sub_55BF40_0055bf40, &recomp_gen::fn_sub_55BF40_0055bf40__recomp},
    {"sub_55CF58", 0x55CF58, &recomp_gen::fn_sub_55CF58_0055cf58, &recomp_gen::fn_sub_55CF58_0055cf58__recomp},
    {"sub_55D0B0", 0x55D0B0, &recomp_gen::fn_sub_55D0B0_0055d0b0, &recomp_gen::fn_sub_55D0B0_0055d0b0__recomp},
    {"sub_55D0D8", 0x55D0D8, &recomp_gen::fn_sub_55D0D8_0055d0d8, &recomp_gen::fn_sub_55D0D8_0055d0d8__recomp},
    {"sceLibgcc32GetErxEntries_7", 0x55D188, &recomp_gen::fn_sceLibgcc32GetErxEntries_7_0055d188, &recomp_gen::fn_sceLibgcc32GetErxEntries_7_0055d188__recomp},
    {"sceLibgcc32GetErxEntries_8", 0x55D200, &recomp_gen::fn_sceLibgcc32GetErxEntries_8_0055d200, &recomp_gen::fn_sceLibgcc32GetErxEntries_8_0055d200__recomp},
    {"WTLS_get_table", 0x55D210, &recomp_gen::fn_WTLS_get_table_0055d210, &recomp_gen::fn_WTLS_get_table_0055d210__recomp},
    {"__errno_9", 0x55D230, &recomp_gen::fn___errno_9_0055d230, &recomp_gen::fn___errno_9_0055d230__recomp},
    {"sub_55D6F0", 0x55D6F0, &recomp_gen::fn_sub_55D6F0_0055d6f0, &recomp_gen::fn_sub_55D6F0_0055d6f0__recomp},
    {"sub_55DAE0", 0x55DAE0, &recomp_gen::fn_sub_55DAE0_0055dae0, &recomp_gen::fn_sub_55DAE0_0055dae0__recomp},
    {"sub_55E498", 0x55E498, &recomp_gen::fn_sub_55E498_0055e498, &recomp_gen::fn_sub_55E498_0055e498__recomp},
    {"sub_55E538", 0x55E538, &recomp_gen::fn_sub_55E538_0055e538, &recomp_gen::fn_sub_55E538_0055e538__recomp},
    {"sub_55E580", 0x55E580, &recomp_gen::fn_sub_55E580_0055e580, &recomp_gen::fn_sub_55E580_0055e580__recomp},
    {"sub_55E640", 0x55E640, &recomp_gen::fn_sub_55E640_0055e640, &recomp_gen::fn_sub_55E640_0055e640__recomp},
    {"sub_55E678", 0x55E678, &recomp_gen::fn_sub_55E678_0055e678, &recomp_gen::fn_sub_55E678_0055e678__recomp},
    {"sub_55E850", 0x55E850, &recomp_gen::fn_sub_55E850_0055e850, &recomp_gen::fn_sub_55E850_0055e850__recomp},
    {"sub_55E888", 0x55E888, &recomp_gen::fn_sub_55E888_0055e888, &recomp_gen::fn_sub_55E888_0055e888__recomp},
    {"sub_55E8C0", 0x55E8C0, &recomp_gen::fn_sub_55E8C0_0055e8c0, &recomp_gen::fn_sub_55E8C0_0055e8c0__recomp},
    {"sub_55EFC8", 0x55EFC8, &recomp_gen::fn_sub_55EFC8_0055efc8, &recomp_gen::fn_sub_55EFC8_0055efc8__recomp},
    {"sub_55F640", 0x55F640, &recomp_gen::fn_sub_55F640_0055f640, &recomp_gen::fn_sub_55F640_0055f640__recomp},
    {"sub_560DE8", 0x560DE8, &recomp_gen::fn_sub_560DE8_00560de8, &recomp_gen::fn_sub_560DE8_00560de8__recomp},
    {"sub_560E30", 0x560E30, &recomp_gen::fn_sub_560E30_00560e30, &recomp_gen::fn_sub_560E30_00560e30__recomp},
    {"sub_5613E0", 0x5613E0, &recomp_gen::fn_sub_5613E0_005613e0, &recomp_gen::fn_sub_5613E0_005613e0__recomp},
    {"sub_561518", 0x561518, &recomp_gen::fn_sub_561518_00561518, &recomp_gen::fn_sub_561518_00561518__recomp},
    {"sub_561560", 0x561560, &recomp_gen::fn_sub_561560_00561560, &recomp_gen::fn_sub_561560_00561560__recomp},
    {"nullsub_144", 0x5615A8, &recomp_gen::fn_nullsub_144_005615a8, &recomp_gen::fn_nullsub_144_005615a8__recomp},
    {"sub_5615F8", 0x5615F8, &recomp_gen::fn_sub_5615F8_005615f8, &recomp_gen::fn_sub_5615F8_005615f8__recomp},
    {"sub_561708", 0x561708, &recomp_gen::fn_sub_561708_00561708, &recomp_gen::fn_sub_561708_00561708__recomp},
    {"sub_561718", 0x561718, &recomp_gen::fn_sub_561718_00561718, &recomp_gen::fn_sub_561718_00561718__recomp},
    {"sub_563DD0", 0x563DD0, &recomp_gen::fn_sub_563DD0_00563dd0, &recomp_gen::fn_sub_563DD0_00563dd0__recomp},
    {"sub_563F38", 0x563F38, &recomp_gen::fn_sub_563F38_00563f38, &recomp_gen::fn_sub_563F38_00563f38__recomp},
    {"sub_563F90", 0x563F90, &recomp_gen::fn_sub_563F90_00563f90, &recomp_gen::fn_sub_563F90_00563f90__recomp},
    {"sub_564068", 0x564068, &recomp_gen::fn_sub_564068_00564068, &recomp_gen::fn_sub_564068_00564068__recomp},
    {"sub_5640D8", 0x5640D8, &recomp_gen::fn_sub_5640D8_005640d8, &recomp_gen::fn_sub_5640D8_005640d8__recomp},
    {"sub_564108", 0x564108, &recomp_gen::fn_sub_564108_00564108, &recomp_gen::fn_sub_564108_00564108__recomp},
    {"sub_564178", 0x564178, &recomp_gen::fn_sub_564178_00564178, &recomp_gen::fn_sub_564178_00564178__recomp},
    {"sub_5641C8", 0x5641C8, &recomp_gen::fn_sub_5641C8_005641c8, &recomp_gen::fn_sub_5641C8_005641c8__recomp},
    {"sub_564268", 0x564268, &recomp_gen::fn_sub_564268_00564268, &recomp_gen::fn_sub_564268_00564268__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena, filled by hgp::random_world.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 48;

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 r16(Machine& m, u32 va) {
    u16 v = 0;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }

const Case& find(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// The stand-ins (on top of install_standard: heap, printf / sprintf, H_Cdvd), for the callees the bodies meet that this
// build does not emit and no current packet claims: the IOP RPC DTX_CallUrpc (it writes the reply words a scripted
// function of the command, so the reply paths read known values), scePrintf, the ADX error callback 0x53AE08 (the AIX
// argument check reports through it) and the streamer state sub_546368 (returns g_stm_state, for the error check's
// streamer path). Both bodies of a pair get a fresh set and their call logs must be equal.
constexpr u32 kDtxCallUrpc = 0x559C10u;
u64 g_stm_state = 0;
u32 reply_word(u32 cmd, u32 k) { return 0x1000u + cmd * 16u + k; }
void install_stand_ins(StandInWorld& w) {
    install_standard(w);
    w.si.clobber_scratch = true;
    w.si.install(kDtxCallUrpc, "DTX_CallUrpc", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 cmd = static_cast<u32>(c.args[0]), reply = static_cast<u32>(c.args[3]), n = static_cast<u32>(c.args[4]);
        if (reply != 0)
            for (u32 k = 0; k < n && k < 16; ++k) ctx.memory->write<u32>(reply + 4 * k, reply_word(cmd, k));
        c.v0 = 0;
    }, 3);
    w.si.install_recorder(0x505E48u, "scePrintf", 0, 3);
    w.si.install_recorder(0x53AE08u, "sub_53AE08 (ADX error callback)", 0, 3);
    const u64 st = g_stm_state;
    w.si.install(0x546368u, "sub_546368 (streamer state)", [st](EEContext&, StandIns&, StandInCall& c) { c.v0 = st; }, 3);
}
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
// One pair with the stand-ins; `log` (when given) receives the hand body's call log.
hgp::Run spair(Machine& m, const Case& c, const Args& args, u32 seed, std::vector<StandInCall>* log = nullptr,
               const HwCheck& hw = {}) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    install_stand_ins(*wh);
    install_stand_ins(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, c.name, hw);
    expect_same_log(wh->si, wr->si, c.name);
    if (log) *log = wh->si.log;
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }
u32 v0_32(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[2].u64[0]); }

void run_random(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");  // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s %s seed %u\n", label, c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(m, kWorld, kWorldSize, rng);
            g_stm_state = rng() % 2 ? 4u : rng() % 4;
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += spair(m, c, args, seed).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
    g_stm_state = 0;
}

// A non-leaf function for the jalr calls (it spills $ra below the $sp it receives): sub_54AFF0, the locked read of an
// ADXT handle's +12 word (sub_54B028), so a fake object's +12 word is the "callee's" result.
constexpr u32 kNonLeaf = 0x54AFF0u;

}  // namespace

TEST_CASE("game(libs20): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    run_random(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds, "random");
}

// The same over the RAM of the replay snapshots: the real globals (the ADXT handles at 0x787570, the sound server
// 0x793F44, srd_obj 0x7A08B0, the HTCI / CVFS tables, the PS2RNA mode words), with random worlds for the pointers.
TEST_CASE("game(libs20): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_random(*m, 4u, dir);
    }
}

// The ADXT error check sub_54C670 on a built handle: the stall counter, the starve counter through the input joint's
// +36 entry (a jalr into a non-leaf function), the two error codes, the recovery mode 0 (no action).
TEST_CASE("game(libs20): the ADXT error check's counters and error codes") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    using namespace p3fes::game::l20;
    const u32 h = kWorld, sjd = kWorld + 0x400, sj = kWorld + 0x800, vt = kWorld + 0xC00;
    zero(*m, kWorld, 0x1000);
    w32(*m, vt + 36, kNonLeaf);
    w32(*m, sj, vt);
    w32(*m, sj + 12, 100);  // the input joint holds 100 bytes: not starved
    m->at(h + adxt::kStat)[0] = 3;
    w32(*m, h + adxt::kSjd, sjd);
    w32(*m, h + adxt::kSji, sj);
    w32(*m, h + adxt::kChkUnit, 1000);
    w32(*m, h + adxt::kLastSmpl, 0x7FFFFFFFu);  // not the decoder's count: the first check resets the stall counter
    const Case& c = find("sub_54C670");
    hgp::Run r = spair(*m, c, Args{sx(h), 0, 0, 0}, 1);
    REQUIRE(!r.stopped);
    CHECK(r16(*m, h + adxt::kStallCnt) == 0u);
    CHECK(r16(*m, h + adxt::kStarveCnt) == 0u);
    const u32 smpl = r32(*m, h + adxt::kLastSmpl);  // now the decoder's count
    CHECK(smpl != 0x7FFFFFFFu);
    spair(*m, c, Args{sx(h), 0, 0, 0}, 2);
    CHECK(r16(*m, h + adxt::kStallCnt) == 1u);  // the same count again
    CHECK(r32(*m, h + adxt::kLastSmpl) == smpl);
    CHECK(r16(*m, h + adxt::kErrCode) == 0u);
    w32(*m, h + adxt::kChkUnit, 0);  // limit 5 x 0: the next stall sets -2
    spair(*m, c, Args{sx(h), 0, 0, 0}, 3);
    CHECK(r16(*m, h + adxt::kStallCnt) == 2u);
    CHECK(r16(*m, h + adxt::kErrCode) == 0xFFFEu);
    CHECK(r16(*m, h + adxt::kStarveCnt) == 0u);  // 100 bytes in: the starve counter stays reset
    // starved input (10 bytes): the starve counter runs; with a unit of 1000 no error yet
    w16(*m, h + adxt::kErrCode, 0);
    w32(*m, h + adxt::kChkUnit, 1000);
    w32(*m, sj + 12, 10);
    spair(*m, c, Args{sx(h), 0, 0, 0}, 4);
    spair(*m, c, Args{sx(h), 0, 0, 0}, 5);
    CHECK(r16(*m, h + adxt::kStarveCnt) == 2u);
    CHECK(r16(*m, h + adxt::kStallCnt) == 4u);
    CHECK(r16(*m, h + adxt::kErrCode) == 0u);
    // not playing (stat 2, preparing): no stall check (counter reset); the starve limit is 20 x the unit
    m->at(h + adxt::kStat)[0] = 2;
    w32(*m, h + adxt::kChkUnit, 0);
    spair(*m, c, Args{sx(h), 0, 0, 0}, 6);
    CHECK(r16(*m, h + adxt::kStallCnt) == 0u);
    CHECK(r16(*m, h + adxt::kStarveCnt) == 3u);
    CHECK(r16(*m, h + adxt::kErrCode) == 0xFFFFu);
    // stopped (stat 0): both counters reset, the error code kept
    m->at(h + adxt::kStat)[0] = 0;
    spair(*m, c, Args{sx(h), 0, 0, 0}, 7);
    CHECK(r16(*m, h + adxt::kStallCnt) == 0u);
    CHECK(r16(*m, h + adxt::kStarveCnt) == 0u);
    CHECK(r16(*m, h + adxt::kErrCode) == 0xFFFFu);
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
TEST_CASE("game(libs20): handlers, counters, masks, info readers, CFG, SRD / HTCI settings and DTR records") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 b = kWorld;
    zero(*m, b, kWorldSize);
    std::vector<StandInCall> log;
    // set_new_handler: swaps the handler word 0x793B68.
    w32(*m, 0x793B68u, 0x111u);
    CHECK(v0_32(spair(*m, find("set_new_handler__FPFv_v"), Args{0x222, 0, 0, 0}, 1)) == 0x111u);
    CHECK(r32(*m, 0x793B68u) == 0x222u);
    // sub_54AE80: the global word 0x787560; with no handle in use nothing else runs.
    for (u32 i = 0; i < 16; ++i) m->at(0x787570u + 200 * i)[0] = 0;
    spair(*m, find("sub_54AE80"), Args{1, 0, 0, 0}, 1, &log);
    CHECK(r32(*m, 0x787560u) == 1u);
    // pvalloc_0 / sub_54D668: the init counter 0x796F50 clears the 704-byte table 0x796FE0 at 0 -> 1 and 1 -> 0.
    {
        w32(*m, 0x796F50u, 0);
        std::memset(m->at(0x796FE0u), 0xAA, 704);
        CHECK(v0_32(spair(*m, find("pvalloc_0"), Args{}, 1)) == 1u);
        CHECK(m->at(0x796FE0u)[0] == 0);
        CHECK(m->at(0x796FE0u + 703)[0] == 0);
        std::memset(m->at(0x796FE0u), 0xAA, 704);
        CHECK(v0_32(spair(*m, find("pvalloc_0"), Args{}, 2)) == 2u);
        CHECK(m->at(0x796FE0u)[0] == 0xAA);
        spair(*m, find("sub_54D668"), Args{}, 3);
        CHECK(r32(*m, 0x796F50u) == 1u);
        CHECK(m->at(0x796FE0u)[0] == 0xAA);
        spair(*m, find("sub_54D668"), Args{}, 4);
        CHECK(r32(*m, 0x796F50u) == 0u);
        CHECK(m->at(0x796FE0u + 100)[0] == 0);
    }
    // sub_54D818: the mask of the n low bits.
    for (u32 n : {0u, 1u, 7u, 8u, 9u, 16u, 23u, 31u}) {
        const hgp::Run r = spair(*m, find("sub_54D818"), Args{n, 0, 0, 0}, n + 1);
        REQUIRE(!r.stopped);
        CHECK(v0_32(r) == static_cast<u32>((u64{1} << n) - 1));
    }
    // sub_54DE18: the callback *0x7973A4 (object *0x7973A8, $a0); returns 0. A recorder target shows the arguments, the
    // non-leaf target the jalr frame.
    {
        w32(*m, 0x7973A4u, kDtxCallUrpc);
        w32(*m, 0x7973A8u, b + 0x100);
        CHECK(v0_of(spair(*m, find("sub_54DE18"), Args{0x55, 0, 0, 0}, 1, &log)) == 0u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == b + 0x100);
        CHECK(log[0].args[1] == 0x55u);
        w32(*m, 0x7973A4u, kNonLeaf);
        CHECK(v0_of(spair(*m, find("sub_54DE18"), Args{0x55, 0, 0, 0}, 2)) == 0u);
        w32(*m, 0x7973A4u, 0);
        CHECK(v0_of(spair(*m, find("sub_54DE18"), Args{0x55, 0, 0, 0}, 3, &log)) == 0u);
        CHECK(log.empty());
    }
    // sub_554998 / sub_554A00: the AIX info readers (16-byte track records at +700, 8-byte u16 records at +6456).
    {
        const u32 info = b + 0x2000, out = b + 0x100;
        w32(*m, info + 700 + 16 * 3, 0x1234u);
        w32(*m, info + 704 + 16 * 3, 0x5678u);
        spair(*m, find("sub_554998"), Args{sx(info), 3, sx(out), sx(out + 4)}, 1);
        CHECK(r32(*m, out) == 0x1234u);
        CHECK(r32(*m, out + 4) == 0x5678u);
        for (u32 k = 0; k < 4; ++k) w16(*m, info + 6456 + 8 * 2 + 2 * k, static_cast<u16>(0xF001u + k));
        HwCheck hw;
        hw.gpr_in[8] = sx(out + 8);
        hw.gpr_in[9] = sx(out + 12);
        spair(*m, find("sub_554A00"), Args{sx(info), 2, sx(out), sx(out + 4)}, 2, nullptr, hw);
        for (u32 k = 0; k < 4; ++k) CHECK(r32(*m, out + 4 * k) == 0xF001u + k);  // zero-extended
        hw.gpr_in[8] = 0;
        hw.gpr_in[9] = 0;
        spair(*m, find("sub_554A00"), Args{sx(info), 2, 0, 0}, 3, nullptr, hw);  // null outputs: nothing written
    }
    // sub_554AA0: a bad argument reports through the ADX error callback and returns -1.
    for (const Args& a : {Args{0, 16, sx(b), 0}, Args{sx(b), 0, sx(b), 0}, Args{sx(b), 16, 0, 0}}) {
        const hgp::Run r = spair(*m, find("sub_554AA0"), a, 1, &log);
        if (r.stopped) continue;
        CHECK(v0_of(r) == ~u64{0});
    }
    // CRI CFG: init makes a 16-entry table at 0x997418; an entry stores 12 name characters and the value; finish clears.
    {
        spair(*m, find("sub_5556A0"), Args{}, 1);
        CHECK(r32(*m, 0x997408u) == 0x7C3908u);
        CHECK(r32(*m, 0x99740Cu) == 0x997418u);
        CHECK(r32(*m, 0x997410u) == 16u);
        std::memcpy(m->at(b + 0x300), "ABCDEFGHIJKLMNOP", 17);
        const hgp::Run r = spair(*m, find("sub_555820"), Args{sx(b + 0x300), 7, 0, 0}, 2);
        if (!r.stopped) {
            CHECK(v0_of(r) == 0u);
            CHECK(std::memcmp(m->at(0x997418u), "ABCDEFGHIJKL", 12) == 0);
            CHECK(r32(*m, 0x997418u + 12) == 7u);
        }
        spair(*m, find("sub_555720"), Args{}, 3);
        CHECK(r32(*m, 0x99740Cu) == 0u);
        CHECK(r32(*m, 0x997410u) == 0u);
        CHECK(v0_of(spair(*m, find("sub_555820"), Args{sx(b + 0x300), 7, 0, 0}, 4)) == ~u64{0});
    }
    // SRD settings and getters.
    {
        spair(*m, find("sub_5580F8"), Args{0x1F5, 0, 0, 0}, 1);
        CHECK(v0_of(spair(*m, find("sub_558118"), Args{}, 2)) == 0xF5u);  // the byte, zero-extended
        spair(*m, find("sub_558108"), Args{sx(0xFFFFFFF0u), 0, 0, 0}, 3);
        CHECK(v0_of(spair(*m, find("__errno_3"), Args{}, 4)) == sx(0xFFFFFFF0u));
        CHECK(v0_of(spair(*m, find("sub_558758"), Args{}, 5)) == 9u);
        CHECK(m->at(0x7A08B2u)[0] == 9);
        m->at(0x7A08B1u)[0] = 2;
        CHECK(v0_of(spair(*m, find("sub_5585F0"), Args{}, 6)) == 2u);
    }
    // DTR / DTX records.
    {
        CHECK(v0_32(spair(*m, find("sub_5596D0"), Args{3, 0, 0, 0}, 1)) == 0x7A1160u + 3 * 68);
        CHECK(v0_of(spair(*m, find("sub_5596D0"), Args{16, 0, 0, 0}, 2)) == 0u);
        CHECK(v0_of(spair(*m, find("sub_5596D0"), Args{~u64{0}, 0, 0, 0}, 3)) == 0u);
        std::memset(m->at(b + 0x400), 0xCC, 64);
        spair(*m, find("sub_559700"), Args{sx(b + 0x400), 0, 0, 0}, 4);
        CHECK(r32(*m, b + 0x400 + 28) == 0xCCCCCCCCu);
        for (u32 off = 32; off <= 44; off += 4) CHECK(r32(*m, b + 0x400 + off) == 0u);
        CHECK(r32(*m, b + 0x400 + 48) == 0xCCCCCCCCu);
        zero(*m, 0x7A1DF0u, 40 * 72);
        CHECK(v0_of(spair(*m, find("sub_559E30"), Args{}, 5)) == 0u);
        m->at(0x7A1DF0u + 5 * 72)[0] = 1;
        m->at(0x7A1DF0u + 5 * 72 + 2)[0] = 1;
        CHECK(v0_of(spair(*m, find("sub_559E30"), Args{}, 6)) == 0u);
        m->at(0x7A1DF0u + 5 * 72 + 2)[0] = 2;
        CHECK(v0_of(spair(*m, find("sub_559E30"), Args{}, 7)) == 1u);
        m->at(0x7A1DF0u + 5 * 72)[0] = 0;
        CHECK(v0_of(spair(*m, find("sub_559E30"), Args{}, 8)) == 0u);  // byte +2 alone does not count
    }
    // HTCI settings: the open mode, the error callback, the address getters.
    {
        spair(*m, find("sub_55D0D8"), Args{1, 0, 0, 0}, 1);
        CHECK(v0_of(spair(*m, find("WTLS_get_table"), Args{}, 2)) == 1u);
        spair(*m, find("sub_55D0D8"), Args{2, 0, 0, 0}, 3);
        CHECK(v0_of(spair(*m, find("WTLS_get_table"), Args{}, 4)) == 0x8001u);
        spair(*m, find("sub_55BA50"), Args{0x123, 0x456, 0, 0}, 5);
        CHECK(r32(*m, 0x7A2C0Cu) == 0x123u);
        CHECK(r32(*m, 0x7A2C10u) == 0x456u);
        CHECK(v0_32(spair(*m, find("sceLibgcc32GetErxEntries_7"), Args{}, 6)) == 0x7A3038u);
        CHECK(v0_32(spair(*m, find("sceLibgcc32GetErxEntries_8"), Args{}, 7)) == 0x7A3140u);
        spair(*m, find("sub_55DAE0"), Args{0x10, 0x20, 0x30, 0}, 8);
        CHECK(r32(*m, 0x7A3168u) == 0x10u);
        CHECK(r32(*m, 0x7A3170u) == 0x30u);
        spair(*m, find("sub_55DAE0"), Args{0, 0x20, 0x30, 0}, 9);
        CHECK(r32(*m, 0x7A316Cu) == 0u);
        CHECK(r32(*m, 0x7A3170u) == 0u);
    }
    // LSC flag: +4 = ($a1 == 1).
    {
        m->at(b + 0x500 + 4)[0] = 7;
        CHECK(v0_of(spair(*m, find("sub_55D6F0"), Args{sx(b + 0x500), 1, 0, 0}, 1)) == 1u);
        CHECK(m->at(b + 0x500 + 4)[0] == 1);
        spair(*m, find("sub_55D6F0"), Args{sx(b + 0x500), 2, 0, 0}, 2);
        CHECK(m->at(b + 0x500 + 4)[0] == 0);
    }
    // The 16-byte block header: tag (7 characters) and (size - 16) in 7 lower-case hex digits at +8.
    {
        const u32 desc = b + 0x600, buf = b + 0x700;
        std::memset(m->at(buf), 0xEE, 0x200);
        w32(*m, desc, buf);
        w32(*m, desc + 4, 0x1AB + 16);
        std::memcpy(m->at(b + 0x680), "TAGNAMEXYZ", 11);
        const hgp::Run r = spair(*m, find("sub_563DD0"), Args{sx(desc), sx(b + 0x680), 0, 0}, 1);
        if (!r.stopped) {
            CHECK(std::memcmp(m->at(buf), "TAGNAME\0" "00001ab", 15) == 0);
            CHECK(m->at(buf + 15)[0] == 0);
            CHECK(m->at(buf + 0x1BA)[0] == 0);  // the buffer's 0x1BB bytes cleared, past them untouched
            CHECK(m->at(buf + 0x1BB)[0] == 0xEE);
        }
    }
    // With the debug print level 0x78FF80 at 2, sub_541760 prints nothing (the print itself would stop in vsprintf's
    // unemitted tail): DTR_Init's counter and work clear, the PS2RNA stubs' report path to its end.
    {
        w32(*m, 0x78FF80u, 2);
        w32(*m, 0x7A0934u, 0);
        std::memset(m->at(0x7A0938u), 0xAB, 2048);
        const Case& dtr = find("sub_559200");
        REQUIRE(!spair(*m, dtr, Args{}, 1).stopped);
        CHECK(r32(*m, 0x7A0934u) == 1u);
        CHECK(m->at(0x7A0938u)[0] == 0);
        CHECK(m->at(0x7A0938u + 2047)[0] == 0);
        std::memset(m->at(0x7A0938u), 0xAB, 2048);
        REQUIRE(!spair(*m, dtr, Args{}, 2).stopped);
        CHECK(r32(*m, 0x7A0934u) == 2u);
        CHECK(m->at(0x7A0938u)[0] == 0xAB);
        for (u32 mode : {0u, 1u}) {
            w32(*m, 0x7A93F8u, mode);
            w32(*m, 0x7A93F0u, 0);
            u32 seed = 1;
            for (const char* fn : {"sub_560DE8", "sub_560E30", "sub_5613E0", "sub_561518", "sub_561560", "sub_5615F8"}) {
                const hgp::Run r = spair(*m, find(fn), Args{}, seed++);
                REQUIRE(!r.stopped);
                if (std::string(fn) == "sub_5613E0" || std::string(fn) == "sub_561518") CHECK(v0_of(r) == 0u);
            }
        }
        w32(*m, 0x78FF80u, 0);
    }
    // htCiOpen's argument checks report through the host CI error callback (here the DTX recorder) and return 0.
    {
        w32(*m, 0x7A2C0Cu, kDtxCallUrpc);
        w32(*m, 0x7A2C10u, b + 0x900);
        const Case& open = find("sub_55BDC8");
        CHECK(v0_of(spair(*m, open, Args{0, 0, 0, 0}, 1, &log)) == 0u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == b + 0x900);
        CHECK(log[0].args[1] == 0x7C51C8u);  // "E0092708:fname is null.(htCiOpen)"
        std::memcpy(m->at(b + 0x980), "A.BIN", 6);
        CHECK(v0_of(spair(*m, open, Args{sx(b + 0x980), 0, 1, 0}, 2, &log)) == 0u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[1] == 0x7C51F0u);  // "E0092709:rw is illigal.(htCiOpen)"
        w32(*m, 0x7A2C0Cu, 0);
        spair(*m, find("sub_55BF40"), Args{0, 0, 0, 0}, 3, &log);  // a null handle: nothing
        CHECK(log.empty());
    }
    // DTX URPC commands: the command number, the argument block 0x999C00 and the reply words.
    {
        const hgp::Run r = spair(*m, find("sub_563F38"), Args{11, 22, 33, 0}, 1, &log);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == 32u);
        CHECK(log[0].args[1] == 0x999C00u);
        CHECK(log[0].args[2] == 3u);
        CHECK(log[0].args[3] == 0x999D00u);
        CHECK(log[0].args[4] == 1u);
        CHECK(r32(*m, 0x999C08u) == 33u);
        CHECK(v0_32(r) == reply_word(32, 0));
        CHECK(v0_32(spair(*m, find("sub_564068"), Args{5, 0, 0, 0}, 2, &log)) == 0x999BC0u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == 36u);
        for (u32 k = 0; k < 4; ++k) CHECK(r32(*m, 0x999BC0u + 4 * k) == reply_word(36, k));
        spair(*m, find("sub_564108"), Args{1, 2, 3, sx(b + 0x800)}, 3, &log);
        CHECK(r32(*m, b + 0x800) == reply_word(38, 0));
        CHECK(r32(*m, b + 0x804) == reply_word(38, 1));
        // one reply word asked for ($t0 = 1), yet the second (0x999D04) is returned through $a3: it keeps its old value
        w32(*m, 0x999D04u, 0x7777u);
        CHECK(v0_32(spair(*m, find("sub_564268"), Args{1, 2, 3, sx(b + 0x810)}, 4, &log)) == reply_word(42, 0));
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[4] == 1u);
        CHECK(r32(*m, b + 0x810) == 0x7777u);
        w32(*m, b + 0x820, 0xAAu);
        w32(*m, b + 0x824, 0xBBu);
        spair(*m, find("sub_5641C8"), Args{7, 8, sx(b + 0x820), 0}, 5, &log);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == 40u);
        CHECK(log[0].args[2] == 4u);
        CHECK(log[0].args[3] == 0u);
        CHECK(r32(*m, 0x999C0Cu) == 0xBBu);
    }
}

// mfCi, the memory files: open by name, seek, tell, read, sector length.
TEST_CASE("game(libs20): memory-file handles: open, seek, tell, read and the sector length") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    using namespace p3fes::game::l20;
    const u32 h = kWorld, src = kWorld + 0x1000, dst = kWorld + 0x2000;
    zero(*m, kWorld, 0x3000);
    for (u32 i = 0; i < 40; ++i) m->at(src)[i] = static_cast<u8>(0x40 + i);
    // a built handle: 40 bytes in 16-byte sectors (3 sectors), at sector 0
    m->at(h + mfci::kUsed)[0] = 1;
    m->at(h + mfci::kStat)[0] = 1;
    w32(*m, h + mfci::kSctLen, 16);
    w32(*m, h + mfci::kSize, 40);
    w32(*m, h + mfci::kNumSct, 3);
    char name[32];
    std::snprintf(name, sizeof name, "%08X.%08X", src, 40u);
    std::memcpy(m->at(h + mfci::kName), name, 18);
    // seek: from the start, from the position, from the end; clamped to 0..sectors
    {
        const Case& c = find("sub_55E580");
        const struct {
            s32 off;
            u32 whence, pos;
        } rows[] = {{2, 0, 2}, {1, 1, 3}, {-1, 2, 2}, {9, 0, 3}, {-5, 1, 0}};
        u32 seed = 1;
        for (const auto& row : rows) {
            const hgp::Run r = spair(*m, c, Args{sx(h), sx(static_cast<u32>(row.off)), row.whence, 0}, seed++);
            REQUIRE(!r.stopped);
            CHECK(v0_32(r) == row.pos);
            CHECK(r32(*m, h + mfci::kPos) == row.pos);
            CHECK(v0_32(spair(*m, find("sub_55E640"), Args{sx(h), 0, 0, 0}, seed++)) == row.pos);
        }
    }
    CHECK(v0_32(spair(*m, find("sub_55E888"), Args{sx(h), 0, 0, 0}, 1)) == 16u);
    CHECK(v0_32(spair(*m, find("sub_55E850"), Args{sx(h), 0, 0, 0}, 1)) == 1u);
    // read 2 sectors at 0, then 5 more (clamped to the last sector: 8 bytes of file, 8 zeroed)
    {
        std::memset(m->at(dst), 0xEE, 64);
        const hgp::Run r1 = spair(*m, find("sub_55E678"), Args{sx(h), 2, sx(dst), 0}, 1);
        if (!r1.stopped) {
            CHECK(v0_32(r1) == 2u);
            CHECK(r32(*m, h + mfci::kPos) == 2u);
            CHECK(r32(*m, h + mfci::kTrBytes) == 32u);
            CHECK(m->at(h + mfci::kStat)[0] == 1);
            CHECK(std::memcmp(m->at(dst), m->at(src), 32) == 0);
            CHECK(m->at(dst + 32)[0] == 0xEE);
            const hgp::Run r2 = spair(*m, find("sub_55E678"), Args{sx(h), 5, sx(dst + 32), 0}, 2);
            REQUIRE(!r2.stopped);
            CHECK(v0_32(r2) == 1u);
            CHECK(r32(*m, h + mfci::kPos) == 3u);
            CHECK(std::memcmp(m->at(dst + 32), m->at(src + 32), 8) == 0);
            for (u32 i = 40; i < 48; ++i) CHECK(m->at(dst + i)[0] == 0);
            CHECK(m->at(dst + 48)[0] == 0xEE);
        }
        // 0 sectors: completes at once; a busy handle (status 2) reads nothing
        w32(*m, h + mfci::kPos, 3);
        CHECK(v0_of(spair(*m, find("sub_55E678"), Args{sx(h), 0, sx(dst), 0}, 3)) == 0u);
        CHECK(m->at(h + mfci::kStat)[0] == 1);
        m->at(h + mfci::kStat)[0] = 2;
        CHECK(v0_of(spair(*m, find("sub_55E678"), Args{sx(h), 1, sx(dst), 0}, 4)) == 0u);
        CHECK(r32(*m, h + mfci::kPos) == 3u);
        m->at(h + mfci::kStat)[0] = 1;
    }
    // sector length 16 -> 8: sectors (40 + 7) / 8 = 5, position 3 x 16 / 8 = 6, bytes moved = last request x 8
    {
        w32(*m, h + mfci::kReqSct, 1);
        spair(*m, find("sub_55E8C0"), Args{sx(h), 8, 0, 0}, 1);
        CHECK(r32(*m, h + mfci::kSctLen) == 8u);
        CHECK(r32(*m, h + mfci::kNumSct) == 5u);
        CHECK(r32(*m, h + mfci::kPos) == 6u);
        CHECK(r32(*m, h + mfci::kTrBytes) == 8u);
    }
    // null handles: 0
    for (const char* fn : {"sub_55E640", "sub_55E850", "sub_55E888", "sub_55E580", "sub_55E678"})
        CHECK(v0_of(spair(*m, find(fn), Args{0, 1, sx(dst), 0}, 9)) == 0u);
    // open by name: a free handle with the name, sector length 2048 and the size parsed from the name
    {
        const u32 nm = kWorld + 0x2800;
        std::memcpy(m->at(nm), name, 18);
        const hgp::Run r = spair(*m, find("sub_55E498"), Args{sx(nm), 0, 0, 0}, 1);
        if (!r.stopped && v0_32(r) != 0) {
            const u32 oh = v0_32(r);
            CHECK(std::memcmp(m->at(oh + mfci::kName), name, 18) == 0);
            CHECK(r32(*m, oh + mfci::kSctLen) == 2048u);
            CHECK(r32(*m, oh + mfci::kSize) == 40u);
            spair(*m, find("sub_55E538"), Args{sx(oh), 0, 0, 0}, 2);
            CHECK(m->at(oh + mfci::kUsed)[0] == 0);
        }
        CHECK(v0_of(spair(*m, find("sub_55E498"), Args{sx(nm), 0, 1, 0}, 3)) == 0u);  // a write mode: refused
        CHECK(v0_of(spair(*m, find("sub_55E498"), Args{0, 0, 0, 0}, 4)) == 0u);
    }
}

#else

TEST_CASE("game(libs20): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
