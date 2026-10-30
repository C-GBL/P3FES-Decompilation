// Pair tests for slice libs7 (the CRI ADX middleware: ADXB containers / keys / decode steps, ADXF, the ADX header,
// ADXT / ADXM). Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log. Worlds: random worlds; the replay snapshots' live ADXF handle and partition tables; the
// disc's BGM/01.ADX header, a built AIFF and Sun .snd header, a built handle. Rule checks: the ADXF handle rules, the
// ADX header layout, the container magics, the key derivation. Callees a wave-2 packet claims are not stood in: a
// pair that reaches one stops there, identically.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs7.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
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

namespace p3fes::recomp_gen {
void fn_sub_535A88_00535a88(EEContext&);  // generated body
void fn_sub_535A88_00535a88__recomp(EEContext&);  // recompiled
void fn_sub_535D18_00535d18(EEContext&);  // generated body
void fn_sub_535D18_00535d18__recomp(EEContext&);  // recompiled
void fn_sub_535E58_00535e58(EEContext&);  // generated body
void fn_sub_535E58_00535e58__recomp(EEContext&);  // recompiled
void fn_sub_535F38_00535f38(EEContext&);  // generated body
void fn_sub_535F38_00535f38__recomp(EEContext&);  // recompiled
void fn_sub_536058_00536058(EEContext&);  // generated body
void fn_sub_536058_00536058__recomp(EEContext&);  // recompiled
void fn_sub_5360B0_005360b0(EEContext&);  // generated body
void fn_sub_5360B0_005360b0__recomp(EEContext&);  // recompiled
void fn_sub_536440_00536440(EEContext&);  // generated body
void fn_sub_536440_00536440__recomp(EEContext&);  // recompiled
void fn_sub_5364A8_005364a8(EEContext&);  // generated body
void fn_sub_5364A8_005364a8__recomp(EEContext&);  // recompiled
void fn_sub_5365B8_005365b8(EEContext&);  // generated body
void fn_sub_5365B8_005365b8__recomp(EEContext&);  // recompiled
void fn_sub_5366D0_005366d0(EEContext&);  // generated body
void fn_sub_5366D0_005366d0__recomp(EEContext&);  // recompiled
void fn_sub_536868_00536868(EEContext&);  // generated body
void fn_sub_536868_00536868__recomp(EEContext&);  // recompiled
void fn_sub_5369E8_005369e8(EEContext&);  // generated body
void fn_sub_5369E8_005369e8__recomp(EEContext&);  // recompiled
void fn_sub_536A10_00536a10(EEContext&);  // generated body
void fn_sub_536A10_00536a10__recomp(EEContext&);  // recompiled
void fn_sub_536D28_00536d28(EEContext&);  // generated body
void fn_sub_536D28_00536d28__recomp(EEContext&);  // recompiled
void fn_sub_536D80_00536d80(EEContext&);  // generated body
void fn_sub_536D80_00536d80__recomp(EEContext&);  // recompiled
void fn_sub_536E90_00536e90(EEContext&);  // generated body
void fn_sub_536E90_00536e90__recomp(EEContext&);  // recompiled
void fn_sub_536F90_00536f90(EEContext&);  // generated body
void fn_sub_536F90_00536f90__recomp(EEContext&);  // recompiled
void fn_sub_537128_00537128(EEContext&);  // generated body
void fn_sub_537128_00537128__recomp(EEContext&);  // recompiled
void fn_sub_5372A8_005372a8(EEContext&);  // generated body
void fn_sub_5372A8_005372a8__recomp(EEContext&);  // recompiled
void fn_sub_537450_00537450(EEContext&);  // generated body
void fn_sub_537450_00537450__recomp(EEContext&);  // recompiled
void fn_sub_5374E8_005374e8(EEContext&);  // generated body
void fn_sub_5374E8_005374e8__recomp(EEContext&);  // recompiled
void fn_sub_537508_00537508(EEContext&);  // generated body
void fn_sub_537508_00537508__recomp(EEContext&);  // recompiled
void fn_sub_537528_00537528(EEContext&);  // generated body
void fn_sub_537528_00537528__recomp(EEContext&);  // recompiled
void fn_sub_537808_00537808(EEContext&);  // generated body
void fn_sub_537808_00537808__recomp(EEContext&);  // recompiled
void fn_sub_537838_00537838(EEContext&);  // generated body
void fn_sub_537838_00537838__recomp(EEContext&);  // recompiled
void fn_sub_537858_00537858(EEContext&);  // generated body
void fn_sub_537858_00537858__recomp(EEContext&);  // recompiled
void fn_sub_5379F8_005379f8(EEContext&);  // generated body
void fn_sub_5379F8_005379f8__recomp(EEContext&);  // recompiled
void fn_sub_537F70_00537f70(EEContext&);  // generated body
void fn_sub_537F70_00537f70__recomp(EEContext&);  // recompiled
void fn_sub_537FE0_00537fe0(EEContext&);  // generated body
void fn_sub_537FE0_00537fe0__recomp(EEContext&);  // recompiled
void fn_sub_537FF0_00537ff0(EEContext&);  // generated body
void fn_sub_537FF0_00537ff0__recomp(EEContext&);  // recompiled
void fn_sub_537FF8_00537ff8(EEContext&);  // generated body
void fn_sub_537FF8_00537ff8__recomp(EEContext&);  // recompiled
void fn_sub_538058_00538058(EEContext&);  // generated body
void fn_sub_538058_00538058__recomp(EEContext&);  // recompiled
void fn_sub_5380A0_005380a0(EEContext&);  // generated body
void fn_sub_5380A0_005380a0__recomp(EEContext&);  // recompiled
void fn_sub_5380E0_005380e0(EEContext&);  // generated body
void fn_sub_5380E0_005380e0__recomp(EEContext&);  // recompiled
void fn_sub_538148_00538148(EEContext&);  // generated body
void fn_sub_538148_00538148__recomp(EEContext&);  // recompiled
void fn_sub_5381C0_005381c0(EEContext&);  // generated body
void fn_sub_5381C0_005381c0__recomp(EEContext&);  // recompiled
void fn_sub_538410_00538410(EEContext&);  // generated body
void fn_sub_538410_00538410__recomp(EEContext&);  // recompiled
void fn_sub_538460_00538460(EEContext&);  // generated body
void fn_sub_538460_00538460__recomp(EEContext&);  // recompiled
void fn_sub_5384B8_005384b8(EEContext&);  // generated body
void fn_sub_5384B8_005384b8__recomp(EEContext&);  // recompiled
void fn_sub_538510_00538510(EEContext&);  // generated body
void fn_sub_538510_00538510__recomp(EEContext&);  // recompiled
void fn_sub_538618_00538618(EEContext&);  // generated body
void fn_sub_538618_00538618__recomp(EEContext&);  // recompiled
void fn_sub_538648_00538648(EEContext&);  // generated body
void fn_sub_538648_00538648__recomp(EEContext&);  // recompiled
void fn_sub_5386B8_005386b8(EEContext&);  // generated body
void fn_sub_5386B8_005386b8__recomp(EEContext&);  // recompiled
void fn_sub_5386D8_005386d8(EEContext&);  // generated body
void fn_sub_5386D8_005386d8__recomp(EEContext&);  // recompiled
void fn_sub_538860_00538860(EEContext&);  // generated body
void fn_sub_538860_00538860__recomp(EEContext&);  // recompiled
void fn_sub_538B60_00538b60(EEContext&);  // generated body
void fn_sub_538B60_00538b60__recomp(EEContext&);  // recompiled
void fn_sub_538C80_00538c80(EEContext&);  // generated body
void fn_sub_538C80_00538c80__recomp(EEContext&);  // recompiled
void fn_sub_538D78_00538d78(EEContext&);  // generated body
void fn_sub_538D78_00538d78__recomp(EEContext&);  // recompiled
void fn_sub_539248_00539248(EEContext&);  // generated body
void fn_sub_539248_00539248__recomp(EEContext&);  // recompiled
void fn_sub_5393C0_005393c0(EEContext&);  // generated body
void fn_sub_5393C0_005393c0__recomp(EEContext&);  // recompiled
void fn_sub_539558_00539558(EEContext&);  // generated body
void fn_sub_539558_00539558__recomp(EEContext&);  // recompiled
void fn_sub_539760_00539760(EEContext&);  // generated body
void fn_sub_539760_00539760__recomp(EEContext&);  // recompiled
void fn_sub_53AD70_0053ad70(EEContext&);  // generated body
void fn_sub_53AD70_0053ad70__recomp(EEContext&);  // recompiled
void fn_sub_53ADA8_0053ada8(EEContext&);  // generated body
void fn_sub_53ADA8_0053ada8__recomp(EEContext&);  // recompiled
void fn_sub_53ADE0_0053ade0(EEContext&);  // generated body
void fn_sub_53ADE0_0053ade0__recomp(EEContext&);  // recompiled
void fn_sub_53AED0_0053aed0(EEContext&);  // generated body
void fn_sub_53AED0_0053aed0__recomp(EEContext&);  // recompiled
void fn_sub_53B060_0053b060(EEContext&);  // generated body
void fn_sub_53B060_0053b060__recomp(EEContext&);  // recompiled
void fn_sub_53B080_0053b080(EEContext&);  // generated body
void fn_sub_53B080_0053b080__recomp(EEContext&);  // recompiled
void fn_sub_53B158_0053b158(EEContext&);  // generated body
void fn_sub_53B158_0053b158__recomp(EEContext&);  // recompiled
void fn_adxf_SetupRofs_0053b250(EEContext&);  // generated body
void fn_adxf_SetupRofs_0053b250__recomp(EEContext&);  // recompiled
void fn_sub_53B2A0_0053b2a0(EEContext&);  // generated body
void fn_sub_53B2A0_0053b2a0__recomp(EEContext&);  // recompiled
void fn_adxf_AddRofsVol_0053b318(EEContext&);  // generated body
void fn_adxf_AddRofsVol_0053b318__recomp(EEContext&);  // recompiled
void fn_sub_53B408_0053b408(EEContext&);  // generated body
void fn_sub_53B408_0053b408__recomp(EEContext&);  // recompiled
void fn_sub_53B4A0_0053b4a0(EEContext&);  // generated body
void fn_sub_53B4A0_0053b4a0__recomp(EEContext&);  // recompiled
void fn_adxf_SetDefDev_0053b528(EEContext&);  // generated body
void fn_adxf_SetDefDev_0053b528__recomp(EEContext&);  // recompiled
void fn___env_lock_0053b598(EEContext&);  // generated body
void fn___env_lock_0053b598__recomp(EEContext&);  // recompiled
void fn___env_unlock_0053b5a0(EEContext&);  // generated body
void fn___env_unlock_0053b5a0__recomp(EEContext&);  // recompiled
void fn_sub_53B5A8_0053b5a8(EEContext&);  // generated body
void fn_sub_53B5A8_0053b5a8__recomp(EEContext&);  // recompiled
void fn_sub_53B5D0_0053b5d0(EEContext&);  // generated body
void fn_sub_53B5D0_0053b5d0__recomp(EEContext&);  // recompiled
void fn_sub_53B680_0053b680(EEContext&);  // generated body
void fn_sub_53B680_0053b680__recomp(EEContext&);  // recompiled
void fn_sub_53B6B0_0053b6b0(EEContext&);  // generated body
void fn_sub_53B6B0_0053b6b0__recomp(EEContext&);  // recompiled
void fn_adxf_LoadPartitionNw_0053b8d0(EEContext&);  // generated body
void fn_adxf_LoadPartitionNw_0053b8d0__recomp(EEContext&);  // recompiled
void fn_sub_53BD10_0053bd10(EEContext&);  // generated body
void fn_sub_53BD10_0053bd10__recomp(EEContext&);  // recompiled
void fn_sub_53BDD8_0053bdd8(EEContext&);  // generated body
void fn_sub_53BDD8_0053bdd8__recomp(EEContext&);  // recompiled
void fn_sub_53BEB0_0053beb0(EEContext&);  // generated body
void fn_sub_53BEB0_0053beb0__recomp(EEContext&);  // recompiled
void fn_sub_53C198_0053c198(EEContext&);  // generated body
void fn_sub_53C198_0053c198__recomp(EEContext&);  // recompiled
void fn_sub_53C268_0053c268(EEContext&);  // generated body
void fn_sub_53C268_0053c268__recomp(EEContext&);  // recompiled
void fn_sub_53C758_0053c758(EEContext&);  // generated body
void fn_sub_53C758_0053c758__recomp(EEContext&);  // recompiled
void fn_sub_53C770_0053c770(EEContext&);  // generated body
void fn_sub_53C770_0053c770__recomp(EEContext&);  // recompiled
void fn_sub_53C7C8_0053c7c8(EEContext&);  // generated body
void fn_sub_53C7C8_0053c7c8__recomp(EEContext&);  // recompiled
void fn_adxf_SetFileInfoEx_0053c860(EEContext&);  // generated body
void fn_adxf_SetFileInfoEx_0053c860__recomp(EEContext&);  // recompiled
void fn_sub_53C9F8_0053c9f8(EEContext&);  // generated body
void fn_sub_53C9F8_0053c9f8__recomp(EEContext&);  // recompiled
void fn_sub_53CAE0_0053cae0(EEContext&);  // generated body
void fn_sub_53CAE0_0053cae0__recomp(EEContext&);  // recompiled
void fn_sub_53CBA0_0053cba0(EEContext&);  // generated body
void fn_sub_53CBA0_0053cba0__recomp(EEContext&);  // recompiled
void fn_sub_53CCC0_0053ccc0(EEContext&);  // generated body
void fn_sub_53CCC0_0053ccc0__recomp(EEContext&);  // recompiled
void fn_sub_53CD60_0053cd60(EEContext&);  // generated body
void fn_sub_53CD60_0053cd60__recomp(EEContext&);  // recompiled
void fn_sub_53CDD0_0053cdd0(EEContext&);  // generated body
void fn_sub_53CDD0_0053cdd0__recomp(EEContext&);  // recompiled
void fn_sub_53CE00_0053ce00(EEContext&);  // generated body
void fn_sub_53CE00_0053ce00__recomp(EEContext&);  // recompiled
void fn_sub_53CEB8_0053ceb8(EEContext&);  // generated body
void fn_sub_53CEB8_0053ceb8__recomp(EEContext&);  // recompiled
void fn_sub_53CEE0_0053cee0(EEContext&);  // generated body
void fn_sub_53CEE0_0053cee0__recomp(EEContext&);  // recompiled
void fn_sub_53CF40_0053cf40(EEContext&);  // generated body
void fn_sub_53CF40_0053cf40__recomp(EEContext&);  // recompiled
void fn_sub_53D098_0053d098(EEContext&);  // generated body
void fn_sub_53D098_0053d098__recomp(EEContext&);  // recompiled
void fn_sub_53D180_0053d180(EEContext&);  // generated body
void fn_sub_53D180_0053d180__recomp(EEContext&);  // recompiled
void fn_adxf_ReadNw32_0053d1f0(EEContext&);  // generated body
void fn_adxf_ReadNw32_0053d1f0__recomp(EEContext&);  // recompiled
void fn_sub_53D450_0053d450(EEContext&);  // generated body
void fn_sub_53D450_0053d450__recomp(EEContext&);  // recompiled
void fn_sub_53D578_0053d578(EEContext&);  // generated body
void fn_sub_53D578_0053d578__recomp(EEContext&);  // recompiled
void fn_adxf_ExecOne_0053d640(EEContext&);  // generated body
void fn_adxf_ExecOne_0053d640__recomp(EEContext&);  // recompiled
void fn_sub_53D7E8_0053d7e8(EEContext&);  // generated body
void fn_sub_53D7E8_0053d7e8__recomp(EEContext&);  // recompiled
void fn_sub_53D938_0053d938(EEContext&);  // generated body
void fn_sub_53D938_0053d938__recomp(EEContext&);  // recompiled
void fn_adxf_GetFsizeSct_0053d9a0(EEContext&);  // generated body
void fn_adxf_GetFsizeSct_0053d9a0__recomp(EEContext&);  // recompiled
void fn_sub_53DA18_0053da18(EEContext&);  // generated body
void fn_sub_53DA18_0053da18__recomp(EEContext&);  // recompiled
void fn_sub_53DAD8_0053dad8(EEContext&);  // generated body
void fn_sub_53DAD8_0053dad8__recomp(EEContext&);  // recompiled
void fn_sub_53DB60_0053db60(EEContext&);  // generated body
void fn_sub_53DB60_0053db60__recomp(EEContext&);  // recompiled
void fn_adxf_GetStat_0053dbc8(EEContext&);  // generated body
void fn_adxf_GetStat_0053dbc8__recomp(EEContext&);  // recompiled
void fn_sub_53DBF8_0053dbf8(EEContext&);  // generated body
void fn_sub_53DBF8_0053dbf8__recomp(EEContext&);  // recompiled
void fn_sub_53DCE8_0053dce8(EEContext&);  // generated body
void fn_sub_53DCE8_0053dce8__recomp(EEContext&);  // recompiled
void fn_sub_53DD98_0053dd98(EEContext&);  // generated body
void fn_sub_53DD98_0053dd98__recomp(EEContext&);  // recompiled
void fn_sub_53DEF0_0053def0(EEContext&);  // generated body
void fn_sub_53DEF0_0053def0__recomp(EEContext&);  // recompiled
void fn_sub_53DF28_0053df28(EEContext&);  // generated body
void fn_sub_53DF28_0053df28__recomp(EEContext&);  // recompiled
void fn_adxf_SetReqRdSct_0053df90(EEContext&);  // generated body
void fn_adxf_SetReqRdSct_0053df90__recomp(EEContext&);  // recompiled
void fn_sub_53E000_0053e000(EEContext&);  // generated body
void fn_sub_53E000_0053e000__recomp(EEContext&);  // recompiled
void fn_sub_53E070_0053e070(EEContext&);  // generated body
void fn_sub_53E070_0053e070__recomp(EEContext&);  // recompiled
void fn_sub_53E088_0053e088(EEContext&);  // generated body
void fn_sub_53E088_0053e088__recomp(EEContext&);  // recompiled
void fn_sub_53E0A0_0053e0a0(EEContext&);  // generated body
void fn_sub_53E0A0_0053e0a0__recomp(EEContext&);  // recompiled
void fn_ADXT_UpdateFsStat_0053e0b8(EEContext&);  // generated body
void fn_ADXT_UpdateFsStat_0053e0b8__recomp(EEContext&);  // recompiled
void fn_sub_53E1B8_0053e1b8(EEContext&);  // generated body
void fn_sub_53E1B8_0053e1b8__recomp(EEContext&);  // recompiled
void fn_sub_53E208_0053e208(EEContext&);  // generated body
void fn_sub_53E208_0053e208__recomp(EEContext&);  // recompiled
void fn_sub_53E220_0053e220(EEContext&);  // generated body
void fn_sub_53E220_0053e220__recomp(EEContext&);  // recompiled
void fn_sub_53E250_0053e250(EEContext&);  // generated body
void fn_sub_53E250_0053e250__recomp(EEContext&);  // recompiled
void fn_sub_53E290_0053e290(EEContext&);  // generated body
void fn_sub_53E290_0053e290__recomp(EEContext&);  // recompiled
void fn_sub_53E350_0053e350(EEContext&);  // generated body
void fn_sub_53E350_0053e350__recomp(EEContext&);  // recompiled
void fn_sub_53E370_0053e370(EEContext&);  // generated body
void fn_sub_53E370_0053e370__recomp(EEContext&);  // recompiled
void fn_sub_53E460_0053e460(EEContext&);  // generated body
void fn_sub_53E460_0053e460__recomp(EEContext&);  // recompiled
void fn_sub_53E520_0053e520(EEContext&);  // generated body
void fn_sub_53E520_0053e520__recomp(EEContext&);  // recompiled
void fn_sub_53E6D8_0053e6d8(EEContext&);  // generated body
void fn_sub_53E6D8_0053e6d8__recomp(EEContext&);  // recompiled
void fn_sub_53E9D8_0053e9d8(EEContext&);  // generated body
void fn_sub_53E9D8_0053e9d8__recomp(EEContext&);  // recompiled
void fn_sub_53E9F0_0053e9f0(EEContext&);  // generated body
void fn_sub_53E9F0_0053e9f0__recomp(EEContext&);  // recompiled
void fn_sub_53F080_0053f080(EEContext&);  // generated body
void fn_sub_53F080_0053f080__recomp(EEContext&);  // recompiled
void fn_sub_53F178_0053f178(EEContext&);  // generated body
void fn_sub_53F178_0053f178__recomp(EEContext&);  // recompiled
void fn_sub_53F5F0_0053f5f0(EEContext&);  // generated body
void fn_sub_53F5F0_0053f5f0__recomp(EEContext&);  // recompiled
void fn_sub_53F618_0053f618(EEContext&);  // generated body
void fn_sub_53F618_0053f618__recomp(EEContext&);  // recompiled
void fn_sub_53F630_0053f630(EEContext&);  // generated body
void fn_sub_53F630_0053f630__recomp(EEContext&);  // recompiled
void fn_sub_53F640_0053f640(EEContext&);  // generated body
void fn_sub_53F640_0053f640__recomp(EEContext&);  // recompiled
void fn_sub_53F6D0_0053f6d0(EEContext&);  // generated body
void fn_sub_53F6D0_0053f6d0__recomp(EEContext&);  // recompiled
void fn_sub_53F880_0053f880(EEContext&);  // generated body
void fn_sub_53F880_0053f880__recomp(EEContext&);  // recompiled
void fn_adxm_goto_svr_border_0053f9b0(EEContext&);  // generated body
void fn_adxm_goto_svr_border_0053f9b0__recomp(EEContext&);  // recompiled
void fn_sub_53FA98_0053fa98(EEContext&);  // generated body
void fn_sub_53FA98_0053fa98__recomp(EEContext&);  // recompiled
void fn_adxm_vsync_proc_0053fbf0(EEContext&);  // generated body
void fn_adxm_vsync_proc_0053fbf0__recomp(EEContext&);  // recompiled
void fn_adxm_mwidle_proc_0053fde8(EEContext&);  // generated body
void fn_adxm_mwidle_proc_0053fde8__recomp(EEContext&);  // recompiled
void fn_sub_53FFF8_0053fff8(EEContext&);  // generated body
void fn_sub_53FFF8_0053fff8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_535A88", 0x535A88, &recomp_gen::fn_sub_535A88_00535a88, &recomp_gen::fn_sub_535A88_00535a88__recomp},
    {"sub_535D18", 0x535D18, &recomp_gen::fn_sub_535D18_00535d18, &recomp_gen::fn_sub_535D18_00535d18__recomp},
    {"sub_535E58", 0x535E58, &recomp_gen::fn_sub_535E58_00535e58, &recomp_gen::fn_sub_535E58_00535e58__recomp},
    {"sub_535F38", 0x535F38, &recomp_gen::fn_sub_535F38_00535f38, &recomp_gen::fn_sub_535F38_00535f38__recomp},
    {"sub_536058", 0x536058, &recomp_gen::fn_sub_536058_00536058, &recomp_gen::fn_sub_536058_00536058__recomp},
    {"sub_5360B0", 0x5360B0, &recomp_gen::fn_sub_5360B0_005360b0, &recomp_gen::fn_sub_5360B0_005360b0__recomp},
    {"sub_536440", 0x536440, &recomp_gen::fn_sub_536440_00536440, &recomp_gen::fn_sub_536440_00536440__recomp},
    {"sub_5364A8", 0x5364A8, &recomp_gen::fn_sub_5364A8_005364a8, &recomp_gen::fn_sub_5364A8_005364a8__recomp},
    {"sub_5365B8", 0x5365B8, &recomp_gen::fn_sub_5365B8_005365b8, &recomp_gen::fn_sub_5365B8_005365b8__recomp},
    {"sub_5366D0", 0x5366D0, &recomp_gen::fn_sub_5366D0_005366d0, &recomp_gen::fn_sub_5366D0_005366d0__recomp},
    {"sub_536868", 0x536868, &recomp_gen::fn_sub_536868_00536868, &recomp_gen::fn_sub_536868_00536868__recomp},
    {"sub_5369E8", 0x5369E8, &recomp_gen::fn_sub_5369E8_005369e8, &recomp_gen::fn_sub_5369E8_005369e8__recomp},
    {"sub_536A10", 0x536A10, &recomp_gen::fn_sub_536A10_00536a10, &recomp_gen::fn_sub_536A10_00536a10__recomp},
    {"sub_536D28", 0x536D28, &recomp_gen::fn_sub_536D28_00536d28, &recomp_gen::fn_sub_536D28_00536d28__recomp},
    {"sub_536D80", 0x536D80, &recomp_gen::fn_sub_536D80_00536d80, &recomp_gen::fn_sub_536D80_00536d80__recomp},
    {"sub_536E90", 0x536E90, &recomp_gen::fn_sub_536E90_00536e90, &recomp_gen::fn_sub_536E90_00536e90__recomp},
    {"sub_536F90", 0x536F90, &recomp_gen::fn_sub_536F90_00536f90, &recomp_gen::fn_sub_536F90_00536f90__recomp},
    {"sub_537128", 0x537128, &recomp_gen::fn_sub_537128_00537128, &recomp_gen::fn_sub_537128_00537128__recomp},
    {"sub_5372A8", 0x5372A8, &recomp_gen::fn_sub_5372A8_005372a8, &recomp_gen::fn_sub_5372A8_005372a8__recomp},
    {"sub_537450", 0x537450, &recomp_gen::fn_sub_537450_00537450, &recomp_gen::fn_sub_537450_00537450__recomp},
    {"sub_5374E8", 0x5374E8, &recomp_gen::fn_sub_5374E8_005374e8, &recomp_gen::fn_sub_5374E8_005374e8__recomp},
    {"sub_537508", 0x537508, &recomp_gen::fn_sub_537508_00537508, &recomp_gen::fn_sub_537508_00537508__recomp},
    {"sub_537528", 0x537528, &recomp_gen::fn_sub_537528_00537528, &recomp_gen::fn_sub_537528_00537528__recomp},
    {"sub_537808", 0x537808, &recomp_gen::fn_sub_537808_00537808, &recomp_gen::fn_sub_537808_00537808__recomp},
    {"sub_537838", 0x537838, &recomp_gen::fn_sub_537838_00537838, &recomp_gen::fn_sub_537838_00537838__recomp},
    {"sub_537858", 0x537858, &recomp_gen::fn_sub_537858_00537858, &recomp_gen::fn_sub_537858_00537858__recomp},
    {"sub_5379F8", 0x5379F8, &recomp_gen::fn_sub_5379F8_005379f8, &recomp_gen::fn_sub_5379F8_005379f8__recomp},
    {"sub_537F70", 0x537F70, &recomp_gen::fn_sub_537F70_00537f70, &recomp_gen::fn_sub_537F70_00537f70__recomp},
    {"sub_537FE0", 0x537FE0, &recomp_gen::fn_sub_537FE0_00537fe0, &recomp_gen::fn_sub_537FE0_00537fe0__recomp},
    {"sub_537FF0", 0x537FF0, &recomp_gen::fn_sub_537FF0_00537ff0, &recomp_gen::fn_sub_537FF0_00537ff0__recomp},
    {"sub_537FF8", 0x537FF8, &recomp_gen::fn_sub_537FF8_00537ff8, &recomp_gen::fn_sub_537FF8_00537ff8__recomp},
    {"sub_538058", 0x538058, &recomp_gen::fn_sub_538058_00538058, &recomp_gen::fn_sub_538058_00538058__recomp},
    {"sub_5380A0", 0x5380A0, &recomp_gen::fn_sub_5380A0_005380a0, &recomp_gen::fn_sub_5380A0_005380a0__recomp},
    {"sub_5380E0", 0x5380E0, &recomp_gen::fn_sub_5380E0_005380e0, &recomp_gen::fn_sub_5380E0_005380e0__recomp},
    {"sub_538148", 0x538148, &recomp_gen::fn_sub_538148_00538148, &recomp_gen::fn_sub_538148_00538148__recomp},
    {"sub_5381C0", 0x5381C0, &recomp_gen::fn_sub_5381C0_005381c0, &recomp_gen::fn_sub_5381C0_005381c0__recomp},
    {"sub_538410", 0x538410, &recomp_gen::fn_sub_538410_00538410, &recomp_gen::fn_sub_538410_00538410__recomp},
    {"sub_538460", 0x538460, &recomp_gen::fn_sub_538460_00538460, &recomp_gen::fn_sub_538460_00538460__recomp},
    {"sub_5384B8", 0x5384B8, &recomp_gen::fn_sub_5384B8_005384b8, &recomp_gen::fn_sub_5384B8_005384b8__recomp},
    {"sub_538510", 0x538510, &recomp_gen::fn_sub_538510_00538510, &recomp_gen::fn_sub_538510_00538510__recomp},
    {"sub_538618", 0x538618, &recomp_gen::fn_sub_538618_00538618, &recomp_gen::fn_sub_538618_00538618__recomp},
    {"sub_538648", 0x538648, &recomp_gen::fn_sub_538648_00538648, &recomp_gen::fn_sub_538648_00538648__recomp},
    {"sub_5386B8", 0x5386B8, &recomp_gen::fn_sub_5386B8_005386b8, &recomp_gen::fn_sub_5386B8_005386b8__recomp},
    {"sub_5386D8", 0x5386D8, &recomp_gen::fn_sub_5386D8_005386d8, &recomp_gen::fn_sub_5386D8_005386d8__recomp},
    {"sub_538860", 0x538860, &recomp_gen::fn_sub_538860_00538860, &recomp_gen::fn_sub_538860_00538860__recomp},
    {"sub_538B60", 0x538B60, &recomp_gen::fn_sub_538B60_00538b60, &recomp_gen::fn_sub_538B60_00538b60__recomp},
    {"sub_538C80", 0x538C80, &recomp_gen::fn_sub_538C80_00538c80, &recomp_gen::fn_sub_538C80_00538c80__recomp},
    {"sub_538D78", 0x538D78, &recomp_gen::fn_sub_538D78_00538d78, &recomp_gen::fn_sub_538D78_00538d78__recomp},
    {"sub_539248", 0x539248, &recomp_gen::fn_sub_539248_00539248, &recomp_gen::fn_sub_539248_00539248__recomp},
    {"sub_5393C0", 0x5393C0, &recomp_gen::fn_sub_5393C0_005393c0, &recomp_gen::fn_sub_5393C0_005393c0__recomp},
    {"sub_539558", 0x539558, &recomp_gen::fn_sub_539558_00539558, &recomp_gen::fn_sub_539558_00539558__recomp},
    {"sub_539760", 0x539760, &recomp_gen::fn_sub_539760_00539760, &recomp_gen::fn_sub_539760_00539760__recomp},
    {"sub_53AD70", 0x53AD70, &recomp_gen::fn_sub_53AD70_0053ad70, &recomp_gen::fn_sub_53AD70_0053ad70__recomp},
    {"sub_53ADA8", 0x53ADA8, &recomp_gen::fn_sub_53ADA8_0053ada8, &recomp_gen::fn_sub_53ADA8_0053ada8__recomp},
    {"sub_53ADE0", 0x53ADE0, &recomp_gen::fn_sub_53ADE0_0053ade0, &recomp_gen::fn_sub_53ADE0_0053ade0__recomp},
    {"sub_53AED0", 0x53AED0, &recomp_gen::fn_sub_53AED0_0053aed0, &recomp_gen::fn_sub_53AED0_0053aed0__recomp},
    {"sub_53B060", 0x53B060, &recomp_gen::fn_sub_53B060_0053b060, &recomp_gen::fn_sub_53B060_0053b060__recomp},
    {"sub_53B080", 0x53B080, &recomp_gen::fn_sub_53B080_0053b080, &recomp_gen::fn_sub_53B080_0053b080__recomp},
    {"sub_53B158", 0x53B158, &recomp_gen::fn_sub_53B158_0053b158, &recomp_gen::fn_sub_53B158_0053b158__recomp},
    {"adxf_SetupRofs", 0x53B250, &recomp_gen::fn_adxf_SetupRofs_0053b250, &recomp_gen::fn_adxf_SetupRofs_0053b250__recomp},
    {"sub_53B2A0", 0x53B2A0, &recomp_gen::fn_sub_53B2A0_0053b2a0, &recomp_gen::fn_sub_53B2A0_0053b2a0__recomp},
    {"adxf_AddRofsVol", 0x53B318, &recomp_gen::fn_adxf_AddRofsVol_0053b318, &recomp_gen::fn_adxf_AddRofsVol_0053b318__recomp},
    {"sub_53B408", 0x53B408, &recomp_gen::fn_sub_53B408_0053b408, &recomp_gen::fn_sub_53B408_0053b408__recomp},
    {"sub_53B4A0", 0x53B4A0, &recomp_gen::fn_sub_53B4A0_0053b4a0, &recomp_gen::fn_sub_53B4A0_0053b4a0__recomp},
    {"adxf_SetDefDev", 0x53B528, &recomp_gen::fn_adxf_SetDefDev_0053b528, &recomp_gen::fn_adxf_SetDefDev_0053b528__recomp},
    {"__env_lock", 0x53B598, &recomp_gen::fn___env_lock_0053b598, &recomp_gen::fn___env_lock_0053b598__recomp},
    {"__env_unlock", 0x53B5A0, &recomp_gen::fn___env_unlock_0053b5a0, &recomp_gen::fn___env_unlock_0053b5a0__recomp},
    {"sub_53B5A8", 0x53B5A8, &recomp_gen::fn_sub_53B5A8_0053b5a8, &recomp_gen::fn_sub_53B5A8_0053b5a8__recomp},
    {"sub_53B5D0", 0x53B5D0, &recomp_gen::fn_sub_53B5D0_0053b5d0, &recomp_gen::fn_sub_53B5D0_0053b5d0__recomp},
    {"sub_53B680", 0x53B680, &recomp_gen::fn_sub_53B680_0053b680, &recomp_gen::fn_sub_53B680_0053b680__recomp},
    {"sub_53B6B0", 0x53B6B0, &recomp_gen::fn_sub_53B6B0_0053b6b0, &recomp_gen::fn_sub_53B6B0_0053b6b0__recomp},
    {"adxf_LoadPartitionNw", 0x53B8D0, &recomp_gen::fn_adxf_LoadPartitionNw_0053b8d0, &recomp_gen::fn_adxf_LoadPartitionNw_0053b8d0__recomp},
    {"sub_53BD10", 0x53BD10, &recomp_gen::fn_sub_53BD10_0053bd10, &recomp_gen::fn_sub_53BD10_0053bd10__recomp},
    {"sub_53BDD8", 0x53BDD8, &recomp_gen::fn_sub_53BDD8_0053bdd8, &recomp_gen::fn_sub_53BDD8_0053bdd8__recomp},
    {"sub_53BEB0", 0x53BEB0, &recomp_gen::fn_sub_53BEB0_0053beb0, &recomp_gen::fn_sub_53BEB0_0053beb0__recomp},
    {"sub_53C198", 0x53C198, &recomp_gen::fn_sub_53C198_0053c198, &recomp_gen::fn_sub_53C198_0053c198__recomp},
    {"sub_53C268", 0x53C268, &recomp_gen::fn_sub_53C268_0053c268, &recomp_gen::fn_sub_53C268_0053c268__recomp},
    {"sub_53C758", 0x53C758, &recomp_gen::fn_sub_53C758_0053c758, &recomp_gen::fn_sub_53C758_0053c758__recomp},
    {"sub_53C770", 0x53C770, &recomp_gen::fn_sub_53C770_0053c770, &recomp_gen::fn_sub_53C770_0053c770__recomp},
    {"sub_53C7C8", 0x53C7C8, &recomp_gen::fn_sub_53C7C8_0053c7c8, &recomp_gen::fn_sub_53C7C8_0053c7c8__recomp},
    {"adxf_SetFileInfoEx", 0x53C860, &recomp_gen::fn_adxf_SetFileInfoEx_0053c860, &recomp_gen::fn_adxf_SetFileInfoEx_0053c860__recomp},
    {"sub_53C9F8", 0x53C9F8, &recomp_gen::fn_sub_53C9F8_0053c9f8, &recomp_gen::fn_sub_53C9F8_0053c9f8__recomp},
    {"sub_53CAE0", 0x53CAE0, &recomp_gen::fn_sub_53CAE0_0053cae0, &recomp_gen::fn_sub_53CAE0_0053cae0__recomp},
    {"sub_53CBA0", 0x53CBA0, &recomp_gen::fn_sub_53CBA0_0053cba0, &recomp_gen::fn_sub_53CBA0_0053cba0__recomp},
    {"sub_53CCC0", 0x53CCC0, &recomp_gen::fn_sub_53CCC0_0053ccc0, &recomp_gen::fn_sub_53CCC0_0053ccc0__recomp},
    {"sub_53CD60", 0x53CD60, &recomp_gen::fn_sub_53CD60_0053cd60, &recomp_gen::fn_sub_53CD60_0053cd60__recomp},
    {"sub_53CDD0", 0x53CDD0, &recomp_gen::fn_sub_53CDD0_0053cdd0, &recomp_gen::fn_sub_53CDD0_0053cdd0__recomp},
    {"sub_53CE00", 0x53CE00, &recomp_gen::fn_sub_53CE00_0053ce00, &recomp_gen::fn_sub_53CE00_0053ce00__recomp},
    {"sub_53CEB8", 0x53CEB8, &recomp_gen::fn_sub_53CEB8_0053ceb8, &recomp_gen::fn_sub_53CEB8_0053ceb8__recomp},
    {"sub_53CEE0", 0x53CEE0, &recomp_gen::fn_sub_53CEE0_0053cee0, &recomp_gen::fn_sub_53CEE0_0053cee0__recomp},
    {"sub_53CF40", 0x53CF40, &recomp_gen::fn_sub_53CF40_0053cf40, &recomp_gen::fn_sub_53CF40_0053cf40__recomp},
    {"sub_53D098", 0x53D098, &recomp_gen::fn_sub_53D098_0053d098, &recomp_gen::fn_sub_53D098_0053d098__recomp},
    {"sub_53D180", 0x53D180, &recomp_gen::fn_sub_53D180_0053d180, &recomp_gen::fn_sub_53D180_0053d180__recomp},
    {"adxf_ReadNw32", 0x53D1F0, &recomp_gen::fn_adxf_ReadNw32_0053d1f0, &recomp_gen::fn_adxf_ReadNw32_0053d1f0__recomp},
    {"sub_53D450", 0x53D450, &recomp_gen::fn_sub_53D450_0053d450, &recomp_gen::fn_sub_53D450_0053d450__recomp},
    {"sub_53D578", 0x53D578, &recomp_gen::fn_sub_53D578_0053d578, &recomp_gen::fn_sub_53D578_0053d578__recomp},
    {"adxf_ExecOne", 0x53D640, &recomp_gen::fn_adxf_ExecOne_0053d640, &recomp_gen::fn_adxf_ExecOne_0053d640__recomp},
    {"sub_53D7E8", 0x53D7E8, &recomp_gen::fn_sub_53D7E8_0053d7e8, &recomp_gen::fn_sub_53D7E8_0053d7e8__recomp},
    {"sub_53D938", 0x53D938, &recomp_gen::fn_sub_53D938_0053d938, &recomp_gen::fn_sub_53D938_0053d938__recomp},
    {"adxf_GetFsizeSct", 0x53D9A0, &recomp_gen::fn_adxf_GetFsizeSct_0053d9a0, &recomp_gen::fn_adxf_GetFsizeSct_0053d9a0__recomp},
    {"sub_53DA18", 0x53DA18, &recomp_gen::fn_sub_53DA18_0053da18, &recomp_gen::fn_sub_53DA18_0053da18__recomp},
    {"sub_53DAD8", 0x53DAD8, &recomp_gen::fn_sub_53DAD8_0053dad8, &recomp_gen::fn_sub_53DAD8_0053dad8__recomp},
    {"sub_53DB60", 0x53DB60, &recomp_gen::fn_sub_53DB60_0053db60, &recomp_gen::fn_sub_53DB60_0053db60__recomp},
    {"adxf_GetStat", 0x53DBC8, &recomp_gen::fn_adxf_GetStat_0053dbc8, &recomp_gen::fn_adxf_GetStat_0053dbc8__recomp},
    {"sub_53DBF8", 0x53DBF8, &recomp_gen::fn_sub_53DBF8_0053dbf8, &recomp_gen::fn_sub_53DBF8_0053dbf8__recomp},
    {"sub_53DCE8", 0x53DCE8, &recomp_gen::fn_sub_53DCE8_0053dce8, &recomp_gen::fn_sub_53DCE8_0053dce8__recomp},
    {"sub_53DD98", 0x53DD98, &recomp_gen::fn_sub_53DD98_0053dd98, &recomp_gen::fn_sub_53DD98_0053dd98__recomp},
    {"sub_53DEF0", 0x53DEF0, &recomp_gen::fn_sub_53DEF0_0053def0, &recomp_gen::fn_sub_53DEF0_0053def0__recomp},
    {"sub_53DF28", 0x53DF28, &recomp_gen::fn_sub_53DF28_0053df28, &recomp_gen::fn_sub_53DF28_0053df28__recomp},
    {"adxf_SetReqRdSct", 0x53DF90, &recomp_gen::fn_adxf_SetReqRdSct_0053df90, &recomp_gen::fn_adxf_SetReqRdSct_0053df90__recomp},
    {"sub_53E000", 0x53E000, &recomp_gen::fn_sub_53E000_0053e000, &recomp_gen::fn_sub_53E000_0053e000__recomp},
    {"sub_53E070", 0x53E070, &recomp_gen::fn_sub_53E070_0053e070, &recomp_gen::fn_sub_53E070_0053e070__recomp},
    {"sub_53E088", 0x53E088, &recomp_gen::fn_sub_53E088_0053e088, &recomp_gen::fn_sub_53E088_0053e088__recomp},
    {"sub_53E0A0", 0x53E0A0, &recomp_gen::fn_sub_53E0A0_0053e0a0, &recomp_gen::fn_sub_53E0A0_0053e0a0__recomp},
    {"ADXT_UpdateFsStat", 0x53E0B8, &recomp_gen::fn_ADXT_UpdateFsStat_0053e0b8, &recomp_gen::fn_ADXT_UpdateFsStat_0053e0b8__recomp},
    {"sub_53E1B8", 0x53E1B8, &recomp_gen::fn_sub_53E1B8_0053e1b8, &recomp_gen::fn_sub_53E1B8_0053e1b8__recomp},
    {"sub_53E208", 0x53E208, &recomp_gen::fn_sub_53E208_0053e208, &recomp_gen::fn_sub_53E208_0053e208__recomp},
    {"sub_53E220", 0x53E220, &recomp_gen::fn_sub_53E220_0053e220, &recomp_gen::fn_sub_53E220_0053e220__recomp},
    {"sub_53E250", 0x53E250, &recomp_gen::fn_sub_53E250_0053e250, &recomp_gen::fn_sub_53E250_0053e250__recomp},
    {"sub_53E290", 0x53E290, &recomp_gen::fn_sub_53E290_0053e290, &recomp_gen::fn_sub_53E290_0053e290__recomp},
    {"sub_53E350", 0x53E350, &recomp_gen::fn_sub_53E350_0053e350, &recomp_gen::fn_sub_53E350_0053e350__recomp},
    {"sub_53E370", 0x53E370, &recomp_gen::fn_sub_53E370_0053e370, &recomp_gen::fn_sub_53E370_0053e370__recomp},
    {"sub_53E460", 0x53E460, &recomp_gen::fn_sub_53E460_0053e460, &recomp_gen::fn_sub_53E460_0053e460__recomp},
    {"sub_53E520", 0x53E520, &recomp_gen::fn_sub_53E520_0053e520, &recomp_gen::fn_sub_53E520_0053e520__recomp},
    {"sub_53E6D8", 0x53E6D8, &recomp_gen::fn_sub_53E6D8_0053e6d8, &recomp_gen::fn_sub_53E6D8_0053e6d8__recomp},
    {"sub_53E9D8", 0x53E9D8, &recomp_gen::fn_sub_53E9D8_0053e9d8, &recomp_gen::fn_sub_53E9D8_0053e9d8__recomp},
    {"sub_53E9F0", 0x53E9F0, &recomp_gen::fn_sub_53E9F0_0053e9f0, &recomp_gen::fn_sub_53E9F0_0053e9f0__recomp},
    {"sub_53F080", 0x53F080, &recomp_gen::fn_sub_53F080_0053f080, &recomp_gen::fn_sub_53F080_0053f080__recomp},
    {"sub_53F178", 0x53F178, &recomp_gen::fn_sub_53F178_0053f178, &recomp_gen::fn_sub_53F178_0053f178__recomp},
    {"sub_53F5F0", 0x53F5F0, &recomp_gen::fn_sub_53F5F0_0053f5f0, &recomp_gen::fn_sub_53F5F0_0053f5f0__recomp},
    {"sub_53F618", 0x53F618, &recomp_gen::fn_sub_53F618_0053f618, &recomp_gen::fn_sub_53F618_0053f618__recomp},
    {"sub_53F630", 0x53F630, &recomp_gen::fn_sub_53F630_0053f630, &recomp_gen::fn_sub_53F630_0053f630__recomp},
    {"sub_53F640", 0x53F640, &recomp_gen::fn_sub_53F640_0053f640, &recomp_gen::fn_sub_53F640_0053f640__recomp},
    {"sub_53F6D0", 0x53F6D0, &recomp_gen::fn_sub_53F6D0_0053f6d0, &recomp_gen::fn_sub_53F6D0_0053f6d0__recomp},
    {"sub_53F880", 0x53F880, &recomp_gen::fn_sub_53F880_0053f880, &recomp_gen::fn_sub_53F880_0053f880__recomp},
    {"adxm_goto_svr_border", 0x53F9B0, &recomp_gen::fn_adxm_goto_svr_border_0053f9b0, &recomp_gen::fn_adxm_goto_svr_border_0053f9b0__recomp},
    {"sub_53FA98", 0x53FA98, &recomp_gen::fn_sub_53FA98_0053fa98, &recomp_gen::fn_sub_53FA98_0053fa98__recomp},
    {"adxm_vsync_proc", 0x53FBF0, &recomp_gen::fn_adxm_vsync_proc_0053fbf0, &recomp_gen::fn_adxm_vsync_proc_0053fbf0__recomp},
    {"adxm_mwidle_proc", 0x53FDE8, &recomp_gen::fn_adxm_mwidle_proc_0053fde8, &recomp_gen::fn_adxm_mwidle_proc_0053fde8__recomp},
    {"sub_53FFF8", 0x53FFF8, &recomp_gen::fn_sub_53FFF8_0053fff8, &recomp_gen::fn_sub_53FFF8_0053fff8__recomp},
};

namespace adxf = p3fes::game::adxf;

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    static const Case none{"?", 0, nullptr, nullptr};
    FAIL("no case for " << hex64(addr));
    return none;
}

// --- guest memory helpers ------------------------------------------------------------------------------------------
u8 r8(Machine& m, u32 va) { return *m.at(va); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wbytes(Machine& m, u32 va, std::initializer_list<u8> b) { std::memcpy(m.at(va), b.begin(), b.size()); }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
std::string rstr(Machine& m, u32 va, std::size_t max = 255) {
    std::string s;
    for (u32 a = va; s.size() < max && *m.at(a); ++a) s += static_cast<char>(*m.at(a));
    return s;
}
u32 be16(const u8* p) { return (u32{p[0]} << 8) | p[1]; }
u32 be32(const u8* p) { return (u32{p[0]} << 24) | (u32{p[1]} << 16) | (u32{p[2]} << 8) | p[3]; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u64 sx64(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }

// --- the built world ---------------------------------------------------------------------------------------------------
constexpr u32 kWork = 0x01810000u;               // free RAM above the harness's arena (the random worlds' region too)
constexpr u32 kWorkSize = 0x10000u;
constexpr u32 kHnd = kWork + 0x0000u;            // a built ADXF handle (68 bytes)
constexpr u32 kOut = kWork + 0x0100u;            // outputs (256 bytes, 0xCD)
constexpr u32 kText = kWork + 0x0200u;           // a pass phrase
constexpr u32 kInfo = kWork + 0x0300u;           // an ADX header info record (256 bytes)
constexpr u32 kDec = kWork + 0x0400u;            // a decoder record of world words (1 KiB)
constexpr u32 kHalf = kWork + 0x0800u;           // halfword copy source / destination (2 x 256 bytes)
constexpr u32 kAdx = kWork + 0x1000u;            // the first 2 KiB of a disc ADX (or a built header)
constexpr u32 kAiff = kWork + 0x2000u;           // a built AIFF (4 KiB + 256)
constexpr u32 kAu = kWork + 0x3200u;             // a built Sun .snd header (256 bytes)
constexpr u32 kStm = kWork + 0x3400u;            // the address the ADXSTM create stand-in hands out
constexpr u32 kAiffSsnd = kAiff + 12 + 8 + 18;   // the SSND chunk (after FORM/AIFF and the 18-byte COMM)

// Stand-ins: callees no test build emits and no wave-2 packet claims (the claimed ones stop the pair, identically).
constexpr u32 kErrReport = 0x53AE08u;            // the ADX error report (its text in $a0)
constexpr u32 kStmCreate = 0x545FC8u;            // ADXSTM create
constexpr u32 kStmStat = 0x546368u;              // ADXSTM status
const u32 kRecorders[] = {0x53AE60u, 0x53AFD8u, 0x53DD10u, 0x546058u, 0x5463A8u, 0x546718u, 0x5465A0u, 0x54A928u, 0x55DA48u};

std::vector<std::string> g_err;  // texts the error-report stand-in received (both runs of a pair)
u64 g_stm_create = kStm;         // what the ADXSTM create stand-in returns
u64 g_stm_stat = 1;

hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const Case& c = by_addr(addr);
    StandIns si;
    si.clobber_scratch = false;
    install_sprintf(si);
    si.install(kErrReport, "adx error report", [](EEContext& ctx, StandIns&, StandInCall& call) {
        std::string s;
        for (u32 va = static_cast<u32>(call.args[0]); va && s.size() < 120; ++va) {
            const char ch = static_cast<char>(ctx.memory->read<u8>(va));
            if (ch == 0) break;
            s += ch;
        }
        g_err.push_back(s);
    });
    si.install_recorder(kStmCreate, "adxstm create", g_stm_create);
    si.install_recorder(kStmStat, "adxstm status", g_stm_stat);
    for (u32 va : kRecorders) si.install_recorder(va, "recorder", 0);
    StandInsScope scope{si};
    HwCheck hw;
    hw.gpr_in = std::move(t);
    static u32 seed = 1;
    return hgp::pair(m, c.hand, c.recomp, a, seed++, c.name, hw);
}
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const hgp::Run r = pr(m, addr, a, std::move(t));
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return r.end.gpr[GPR_V0].u64[0];
}
std::map<unsigned, u64> tregs(u64 t0, u64 t1 = 0) { return {{GPR_T0, t0}, {GPR_T0 + 1, t1}}; }
std::string last_err() { return g_err.empty() ? std::string() : g_err.back(); }

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

std::vector<u8> read_file(const std::string& path, std::size_t len) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    std::vector<u8> b(len);
    f.read(reinterpret_cast<char*>(b.data()), static_cast<std::streamsize>(len));
    if (static_cast<std::size_t>(f.gcount()) != len) return {};
    return b;
}
std::vector<u8> disc_adx() { return read_file(extracted_root() + "/BGM/01.ADX", 0x800); }

// A stopped ADXF handle on a 100-sector file, at sector 10, its last request 7 sectors from 3 (5 read).
void build_handle(Machine& m) {
    std::memset(m.at(kHnd), 0, adxf::kHandleSize);
    w8(m, kHnd + adxf::kUsed, 1);
    w8(m, kHnd + adxf::kStat, 1);
    w32(m, kHnd + adxf::kFsizeSct, 100);
    w32(m, kHnd + adxf::kFsizeByte, 100 * 2048 - 300);
    w32(m, kHnd + adxf::kOfst, 10);
    w32(m, kHnd + adxf::kReqStart, 3);
    w32(m, kHnd + adxf::kReqNsct, 7);
    w32(m, kHnd + adxf::kReadNsct, 5);
    w32(m, kHnd + adxf::kMaxReqSct, 512);
}

void build_world(Machine& m, u32 seed) {
    std::mt19937 rng{seed};
    build_handle(m);
    std::memset(m.at(kOut), 0xCD, 0x100);
    wstr(m, kText, "persona3fes");
    std::memset(m.at(kInfo), 0, 0x100);
    hgp::random_world(m, kDec, 0x400, rng);
    for (u32 i = 0; i < 0x100; ++i) w8(m, kHalf + i, static_cast<u8>(rng()));
    // an ADX header: the disc's BGM/01.ADX when present, else a built one of the same form
    const std::vector<u8> adx = disc_adx();
    if (!adx.empty()) {
        std::memcpy(m.at(kAdx), adx.data(), adx.size());
    } else {
        std::memset(m.at(kAdx), 0, 0x800);
        wbytes(m, kAdx, {0x80, 0x00, 0x00, 0x1C, 3, 18, 4, 2, 0x00, 0x00, 0xAC, 0x44, 0x00, 0x10, 0x00, 0x00, 0x01, 0xF4, 3, 0});
    }
    // an AIFF: FORM / AIFF, COMM (2 channels, 0x1234 frames, 16 bits, 44100 Hz), SSND (offset 0, block 0), samples
    std::memset(m.at(kAiff), 0, 0x1100);
    const u32 form = 4 + (8 + 18) + (8 + 8 + 0x1000);
    wbytes(m, kAiff, {'F', 'O', 'R', 'M', u8(form >> 24), u8(form >> 16), u8(form >> 8), u8(form), 'A', 'I', 'F', 'F'});
    wbytes(m, kAiff + 12, {'C', 'O', 'M', 'M', 0, 0, 0, 18, 0, 2, 0, 0, 0x12, 0x34, 0, 16, 0x40, 0x0E, 0xAC, 0x44, 0, 0, 0, 0, 0, 0});
    wbytes(m, kAiffSsnd, {'S', 'S', 'N', 'D', 0, 0, 0x10, 0x08, 0, 0, 0, 0, 0, 0, 0, 0});
    for (u32 i = 0; i < 0x1000; ++i) w8(m, kAiffSsnd + 16 + i, static_cast<u8>(rng()));
    // a Sun .snd header: offset 32, size 0x1000, encoding 3 (16-bit linear), 22050 Hz, 1 channel
    std::memset(m.at(kAu), 0, 0x100);
    wbytes(m, kAu, {'.', 's', 'n', 'd', 0, 0, 0, 32, 0, 0, 0x10, 0, 0, 0, 0, 3, 0, 0, 0x56, 0x22, 0, 0, 0, 1});
}

// --- the argument recipes ------------------------------------------------------------------------------------------------
struct Call {
    Args a;
    u64 t0 = 0, t1 = 0;
};
// The live ADXF handles (used) and partitions of the machine's state.
std::vector<u32> live_handles(Machine& m) {
    std::vector<u32> v;
    for (u32 i = 0; i < adxf::kHandleCount; ++i)
        if (r8(m, adxf::kHandleTable + i * adxf::kHandleSize) == 1) v.push_back(adxf::kHandleTable + i * adxf::kHandleSize);
    return v;
}
std::vector<u32> live_partitions(Machine& m) {
    std::vector<u32> v;
    for (u32 i = 0; i < 256; ++i)
        if (r32(m, adxf::kPartTable + 4 * i)) v.push_back(i);
    return v;
}

std::vector<Call> recipes(Machine& m, u32 addr) {
    std::vector<Call> v;
    auto add = [&](u64 a0 = 0, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0, u64 t0 = 0, u64 t1 = 0) { v.push_back({Args{a0, a1, a2, a3}, t0, t1}); };
    std::vector<u32> hns = live_handles(m);
    hns.push_back(kHnd);
    const std::vector<u32> pts = live_partitions(m);
    switch (addr) {
    // containers and keys
    case 0x535F38: add(kAiff); add(kOut); break;
    case 0x5360B0: add(kAiff, kOut, kOut + 4, kOut + 8, kOut + 12); add(kAu, kOut, kOut + 4, kOut + 8, kOut + 12); break;
    case 0x536440: case 0x536D28: add(kAiff); add(kAu); break;
    case 0x5364A8: case 0x536D80:
        for (u32 len : {7u, 8u, 4095u, 0x1100u}) add(addr == 0x5364A8u ? kAiff : kAu, len, kOut, kOut + 2, kOut + 3, kOut + 4);
        break;
    case 0x536A10: add(kAu, 0x100, kOut, kOut + 4, kOut + 8, kOut + 12); add(kAiff, 0x100, kOut, kOut + 4, kOut + 8, kOut + 12); break;
    case 0x5365B8: case 0x536E90: case 0x538C80: add(kDec, kAiff, 0x1100); add(kDec, kAu, 0x100); add(kDec, kAdx, 0x800); break;
    case 0x5379F8: add(kDec, kAdx, 0x800); add(kDec, kAiff, 0x800); break;
    case 0x537528: add(kText, 11, kOut, kOut + 2, kOut + 4); add(0, 0, kOut, kOut + 2, kOut + 4); break;
    case 0x5380E0: add(kDec, kText); break;
    case 0x538148: add(kText); break;
    case 0x5381C0: for (u32 ver : {3u, 4u, 16u}) add(kDec, ver, 16, 0x12345678u, kOut, kOut + 2); break;  // the 7th argument on the stack
    case 0x538618: add(kHalf + 0x80, kHalf, 64); add(kHalf, kHalf, 0); add(kHalf, kHalf + 2, sx64(-1)); break;
    case 0x538648: add(kHalf, 8, 32, 8); break;
    case 0x5386B8: add(kHalf, 8, 0, 8); break;
    case 0x53AED0: for (s32 n : {0, 7, 1234, -56}) add(sx64(n), kOut, 32); break;
    case 0x53B060: add(kHalf, 0x100); break;
    case 0x53B5A8: for (s32 n : {0, 1, 2048, 2049, -1, -2049}) add(sx64(n)); break;
    case 0x53B5D0: add(4, 0, kHnd, 7, 3); add(4, 1, kHnd, 7, 3); break;
    case 0x53B6B0: add(3, kOut); add(3, 0); add(256, kOut); break;
    // ADXF
    case 0x53C758: case 0x53DF28: case 0x53DEF0: for (u32 p : pts) add(p); break;
    case 0x53DBF8: for (u32 p : pts) for (s32 f : {0, 1, -1, 100000}) add(p, sx64(f)); add(255, 0); add(256, 0); break;
    case 0x53DD98: case 0x53DCE8: for (u32 p : pts) for (s32 f : {0, 3}) add(p, sx64(f), kOut, kOut + 4, kOut + 8, kOut + 12); break;
    case 0x53CBA0: for (u32 p : pts) add(kHnd, p, 0); add(kHnd, 300, 0); break;
    case 0x53CCC0: for (u32 p : pts) add(p, 0); break;
    case 0x53C860: add(kHnd, kText, 0); add(kHnd, 0, 0); break;
    case 0x53C9F8: add(kHnd, kText, 0, 20, 10); break;
    case 0x53CAE0: add(kText, 0, 20, 10); break;
    case 0x53D098: case 0x53CF40: for (u32 h : hns) add(h, 3, kDec); add(0, 3, kDec); add(kHnd, sx64(-1), kDec); add(kHnd, 3, 0); break;
    case 0x53D1F0: for (u32 h : hns) add(h, 2, kHalf); add(0, 2, kHalf); add(kHnd, sx64(-1), kHalf); add(kHnd, 2, 0); break;
    case 0x53D7E8: for (u32 h : hns) for (u32 type : {0u, 1u, 2u, 3u}) add(h, sx64(-5), type); add(0, 0, 0); break;
    case 0x53DAD8: for (u32 h : hns) add(h, kOut); add(0, kOut); break;
    case 0x53DF90: for (u32 h : hns) add(h, 77); break;
    case 0x53E220: add(kOut, 0x1234); break;
    case 0x53E250: add(kOut, 0x12345678u); break;
    case 0x53E290: case 0x53E350: case 0x53E370: case 0x53E460: add(kAdx + 4, kInfo); break;
    case 0x53E520: for (u32 len : {3u, 0x20u, 0x800u}) add(kAdx, len, kOut, kInfo); add(kAdx, 0x800, kOut, 0); add(kAiff, 0x800, kOut, kInfo); break;
    case 0x53E6D8: add(kOut, kInfo); break;
    case 0x53E9D8: case 0x53E9F0: add(0, kText); break;
    case 0x53F630: case 0x53F880: for (s32 mode : {-1, 0, 1, 2, 3}) add(sx64(mode)); break;
    case 0x53FFF8: add(0); add(1); break;
    case 0x53F080: case 0x53F178: add(0, 0, 0); add(kDec, 0, 0); break;
    default:
        // the handle getters / close / stop / exec and the decoder records: every live handle, the built handle, null,
        // the decoder record of world words
        for (u32 h : hns) add(h, kOut, kOut + 4, kOut + 8);
        add(0, kOut, kOut + 4, kOut + 8);
        add(kDec, kOut, kOut + 4, kOut + 8, kOut + 12);
        break;
    }
    return v;
}

}  // namespace

TEST_CASE("game(libs7): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24u;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWork, kWorkSize, rng);
            const Args args{hgp::random_arg(rng, kWork, kWorkSize), hgp::random_arg(rng, kWork, kWorkSize),
                            hgp::random_arg(rng, kWork, kWorkSize), hgp::random_arg(rng, kWork, kWorkSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// Every function on the replay snapshots: the live ADXF handle table (0x784A60) and partition table (0x784EA0), the
// ADX globals, plus the built world (the disc's BGM/01.ADX header, an AIFF, a Sun .snd header, a pass phrase, a built
// handle). Each pair starts from the snapshot.
TEST_CASE("game(libs7): every body on the snapshots' live ADXF handles and partitions") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int ran = 0, stopped = 0, handles = 0, partitions = 0;
    for (const char* dir : {"dorm_replay_4900", "b_5800", "fusion_ref_6300"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        CHECK(r32(*m, adxf::kInitCount) != 0u);  // ADXF is up on every route
        handles += static_cast<int>(live_handles(*m).size());
        partitions += static_cast<int>(live_partitions(*m).size());
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            restore(*m, snap);
            build_world(*m, c.addr);
            const std::vector<Call> calls = recipes(*m, c.addr);
            for (const Call& call : calls) {
                restore(*m, snap);
                build_world(*m, c.addr);
                const hgp::Run r = pr(*m, c.addr, call.a, tregs(call.t0, call.t1));
                ++ran;
                stopped += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE(ran << " pairs on snapshot state, " << stopped << " stopped (identically); live handles " << handles << ", partitions " << partitions);
}

// ADXF's handle rules on a fresh machine: allocate into the first free slot (the stream created, 512-sector requests),
// 'not enough handle' / 'can't create stm handle', the getters and their null-handle errors, the seek clamps, the
// request-size setter refused while reading, close, the call log ring, init / finish nesting.
TEST_CASE("game(libs7): ADXF -- handles, getters, seek, the call log, init / finish") {
    auto m = machine();
    if (!m) return;
    build_world(*m, 1);
    g_err.clear();
    std::memset(m->at(adxf::kHandleTable), 0, adxf::kHandleCount * adxf::kHandleSize);
    // allocate: slot 0, then slot 1 (the pair's recompiled run leaves its memory)
    g_stm_create = kStm;
    CHECK(prv(*m, 0x53C7C8u, Args{0, 0, 0, 0}) == adxf::kHandleTable);
    CHECK(r8(*m, adxf::kHandleTable + adxf::kUsed) == 1);
    CHECK(r8(*m, adxf::kHandleTable + adxf::kStat) == 1);
    CHECK(r32(*m, adxf::kHandleTable + adxf::kStm) == kStm);
    CHECK(r32(*m, adxf::kHandleTable + adxf::kMaxReqSct) == 512u);
    CHECK(prv(*m, 0x53C7C8u, Args{0, 0, 0, 0}) == adxf::kHandleTable + adxf::kHandleSize);
    CHECK(prv(*m, 0x53C770u, Args{0, 0, 0, 0}) == adxf::kHandleTable + 2 * adxf::kHandleSize);
    // the stream create fails: 0 and the text; the slot keeps the null stream
    g_stm_create = 0;
    CHECK(prv(*m, 0x53C7C8u, Args{0, 0, 0, 0}) == 0u);
    CHECK(last_err().rfind("E02111001", 0) == 0);
    g_stm_create = kStm;
    // a full table: 0 and 'not enough ADXF handle'
    for (u32 i = 0; i < adxf::kHandleCount; ++i) w8(*m, adxf::kHandleTable + i * adxf::kHandleSize, 1);
    CHECK(prv(*m, 0x53C770u, Args{0, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x53C7C8u, Args{0, 0, 0, 0}) == 0u);
    CHECK(last_err().rfind("E04041201", 0) == 0);
    // the getters
    build_handle(*m);
    CHECK(prv(*m, 0x53DBC8u, Args{kHnd, 0, 0, 0}) == 1u);
    CHECK(sv(prv(*m, 0x53DBC8u, Args{0, 0, 0, 0})) == -3);
    CHECK(last_err() == "E9040832:'adxf' is NULL.(adxf_GetStat)");
    CHECK(prv(*m, 0x53D938u, Args{kHnd, 0, 0, 0}) == 10u);
    CHECK(sv(prv(*m, 0x53D938u, Args{0, 0, 0, 0})) == -3);
    CHECK(prv(*m, 0x53DAD8u, Args{kHnd, kOut, 0, 0}) == 7u);
    CHECK(r32(*m, kOut) == 3u);
    CHECK(sv(prv(*m, 0x53DAD8u, Args{0, kOut, 0, 0})) == -3);
    CHECK(r32(*m, kOut) == 0u);
    CHECK(prv(*m, 0x53DB60u, Args{kHnd, 0, 0, 0}) == 5u);
    CHECK(last_err().rfind("E9040830", 0) == 0);
    // seek: from the start, the current sector, the end; clamped to [0, size]; bad type / null handle -3
    CHECK(prv(*m, 0x53D7E8u, Args{kHnd, 5, 0, 0}) == 5u);
    CHECK(prv(*m, 0x53D7E8u, Args{kHnd, 5, 1, 0}) == 10u);
    CHECK(prv(*m, 0x53D7E8u, Args{kHnd, sx64(-20), 1, 0}) == 0u);
    CHECK(prv(*m, 0x53D7E8u, Args{kHnd, 500, 0, 0}) == 100u);
    CHECK(prv(*m, 0x53D7E8u, Args{kHnd, sx64(-1), 2, 0}) == 99u);
    CHECK(r32(*m, kHnd + adxf::kOfst) == 99u);
    CHECK(sv(prv(*m, 0x53D7E8u, Args{kHnd, 0, 3, 0})) == -3);
    CHECK(last_err().rfind("E9040826", 0) == 0);
    CHECK(r32(*m, kHnd + adxf::kOfst) == 99u);
    CHECK(sv(prv(*m, 0x53D7E8u, Args{0, 0, 0, 0})) == -3);
    CHECK(last_err().rfind("E9040825", 0) == 0);
    // the request size: stored while stopped, refused while reading
    prv(*m, 0x53DF90u, Args{kHnd, 77, 0, 0});
    CHECK(r32(*m, kHnd + adxf::kMaxReqSct) == 77u);
    w8(*m, kHnd + adxf::kStat, 2);
    g_err.clear();
    prv(*m, 0x53DF90u, Args{kHnd, 99, 0, 0});
    CHECK(r32(*m, kHnd + adxf::kMaxReqSct) == 77u);
    CHECK(last_err() == "E0041201:state is reading(ADXF_SetReqRdSct)");
    // close a stopped handle without a stream: the 68 bytes cleared, the close counted once (call id 3)
    build_handle(*m);
    const u16 closes = r16(*m, adxf::kCallCount + 2 * 3);
    prv(*m, 0x53CE00u, Args{kHnd, 0, 0, 0});
    for (u32 i = 0; i < adxf::kHandleSize; ++i) CHECK(r8(*m, kHnd + i) == 0);
    CHECK(r16(*m, adxf::kCallCount + 2 * 3) == closes + 1);
    // bytes to sectors, rounded up
    for (s32 n : {0, 1, 2047, 2048, 2049, 100000}) CHECK(sv(prv(*m, 0x53B5A8u, Args{sx64(n), 0, 0, 0})) == (n + 2047) / 2048);
    // the call log: entry at the ring index (mod 16), {id, leave, count, a, b, c}, the index advanced; a leave is not counted
    w32(*m, adxf::kCallLogPos, 31);
    const u16 reads = r16(*m, adxf::kCallCount + 2 * 4);
    prv(*m, 0x53B5D0u, Args{4, 0, kHnd, 7}, tregs(3));
    const u32 e = adxf::kCallLog + 15 * 16;
    CHECK(r8(*m, e) == 4);
    CHECK(r8(*m, e + 1) == 0);
    CHECK(r16(*m, e + 2) == reads + 1);
    CHECK(r32(*m, e + 4) == kHnd);
    CHECK(r32(*m, e + 8) == 7u);
    CHECK(r32(*m, e + 12) == 3u);
    CHECK(r32(*m, adxf::kCallLogPos) == 16u);
    prv(*m, 0x53B5D0u, Args{4, 1, kHnd, 7}, tregs(3));
    CHECK(r8(*m, adxf::kCallLog) == 4);
    CHECK(r8(*m, adxf::kCallLog + 1) == 1);
    CHECK(r16(*m, adxf::kCallLog + 2) == reads + 1);
    CHECK(r32(*m, adxf::kCallLogPos) == 1u);
    // init / finish nesting: the first init clears, a second keeps, the last finish closes and clears
    std::memset(m->at(adxf::kHandleTable), 0, adxf::kHandleCount * adxf::kHandleSize);
    w32(*m, adxf::kInitCount, 0);
    w32(*m, adxf::kPartTable, 0x1234);
    CHECK(prv(*m, 0x53B080u, Args{0, 0, 0, 0}) == 1u);
    CHECK(r32(*m, adxf::kPartTable) == 0u);
    CHECK(r32(*m, adxf::kCallLog) == 0xFFFFFFFFu);
    CHECK(r32(*m, adxf::kCallLogPos) == 0u);
    CHECK(rstr(*m, r32(*m, 0x997028u)).find("ADXF/PS2EE Ver.7.30") != std::string::npos);
    w32(*m, adxf::kPartTable, 0x1234);
    CHECK(prv(*m, 0x53B080u, Args{0, 0, 0, 0}) == 2u);
    CHECK(r32(*m, adxf::kPartTable) == 0x1234u);
    prv(*m, 0x53B158u, Args{0, 0, 0, 0});
    CHECK(r32(*m, adxf::kInitCount) == 1u);
    CHECK(r32(*m, adxf::kPartTable) == 0x1234u);
    prv(*m, 0x53B158u, Args{0, 0, 0, 0});
    CHECK(r32(*m, adxf::kInitCount) == 0u);
    CHECK(r32(*m, adxf::kPartTable) == 0u);
    // the partition argument check
    CHECK(prv(*m, 0x53B6B0u, Args{3, kOut, 0, 0}) == 0u);
    CHECK(sv(prv(*m, 0x53B6B0u, Args{3, 0, 0, 0})) == -3);
    CHECK(last_err().rfind("E9040802", 0) == 0);
    CHECK(sv(prv(*m, 0x53B6B0u, Args{256, kOut, 0, 0})) == -3);
    CHECK(last_err().rfind("E9040801", 0) == 0);
}

// The ADX header (the public layout: 0x8000, the header size, encoding, block size, bits, channels, rate, samples) on
// the disc's BGM/01.ADX: decoded field by field, the error codes for a short / foreign / truncated buffer, the
// big-endian stores, and the encoder's "(c)CRI" signature.
TEST_CASE("game(libs7): ADX header -- decode the disc's header, the errors, big-endian stores, the encoder") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> adx = disc_adx();
    if (adx.empty()) {
        MESSAGE("SKIP: extracted/BGM/01.ADX not found");
        return;
    }
    build_world(*m, 2);
    const u32 hsize = be16(&adx[2]);
    CHECK(prv(*m, 0x53E520u, Args{kAdx, 0x800, kOut, kInfo}) == 0u);
    CHECK(r32(*m, kOut) == hsize);
    CHECK(r8(*m, kInfo + 0) == adx[4]);  // encoding
    CHECK(r8(*m, kInfo + 1) == adx[5]);  // block size
    CHECK(r8(*m, kInfo + 2) == adx[6]);  // bits
    CHECK(r8(*m, kInfo + 3) == adx[7]);  // channels
    CHECK(r32(*m, kInfo + 4) == be32(&adx[8]));   // sample rate
    CHECK(r32(*m, kInfo + 8) == be32(&adx[12]));  // samples
    CHECK(r8(*m, kInfo + 3) >= 1);
    CHECK(r32(*m, kInfo + 4) > 8000u);
    // no info record: only the size; short: -1 (the size cleared); not an ADX: -4; the size past the buffer: -2
    w32(*m, kOut, 0xCDCDCDCDu);
    CHECK(prv(*m, 0x53E520u, Args{kAdx, 0x800, kOut, 0}) == 0u);
    CHECK(r32(*m, kOut) == hsize);
    CHECK(sv(prv(*m, 0x53E520u, Args{kAdx, 3, kOut, kInfo})) == -1);
    CHECK(r32(*m, kOut) == 0u);
    CHECK(sv(prv(*m, 0x53E520u, Args{kAiff, 0x800, kOut, kInfo})) == -4);
    CHECK(sv(prv(*m, 0x53E520u, Args{kAdx, hsize, kOut, kInfo})) == -2);
    // big-endian stores
    prv(*m, 0x53E220u, Args{kOut, 0x1234, 0, 0});
    CHECK(r8(*m, kOut) == 0x12);
    CHECK(r8(*m, kOut + 1) == 0x34);
    prv(*m, 0x53E250u, Args{kOut, 0x12345678u, 0, 0});
    CHECK(be32(m->at(kOut)) == 0x12345678u);
    // the encoder writes the decoded info back: the format bytes, the rate and samples big-endian, the signature
    prv(*m, 0x53E520u, Args{kAdx, 0x800, kOut + 0x80, kInfo});
    std::memset(m->at(kOut), 0, 0x80);
    prv(*m, 0x53E6D8u, Args{kOut, kInfo, 0, 0});
    for (u32 i = 0; i < 4; ++i) CHECK(r8(*m, kOut + i) == r8(*m, kInfo + i));
    CHECK(be32(m->at(kOut + 4)) == r32(*m, kInfo + 4));
    CHECK(be32(m->at(kOut + 8)) == r32(*m, kInfo + 8));
    bool sig = false;
    for (u32 i = 0; i + 6 <= 0x80; ++i) sig = sig || std::memcmp(m->at(kOut + i), "(c)CRI", 6) == 0;
    CHECK(sig);
}

// The PCM containers and small helpers: the AIFF parser on a built file (COMM's channels / frames / bits / rate, the
// sample data's address), the magic tests, the AC-3 sync word, the key derivation (deterministic; the handle and the
// default setters agree; no phrase, no keys), the halfword copy, the mode resolver.
TEST_CASE("game(libs7): ADXB -- AIFF / .snd / AC-3 tests, the AIFF parser, the keys, the copy helper") {
    auto m = machine();
    if (!m) return;
    build_world(*m, 3);
    // AIFF parser: the address after SSND's offset field (+ the offset), the COMM fields
    CHECK(prv(*m, 0x5360B0u, Args{kAiff, kOut, kOut + 4, kOut + 8}, tregs(kOut + 12)) == kAiffSsnd + 8 + 4);
    CHECK(r32(*m, kOut) == 44100u);
    CHECK(r32(*m, kOut + 4) == 2u);
    CHECK(r32(*m, kOut + 8) == 16u);
    CHECK(r32(*m, kOut + 12) == 0x1234u);
    CHECK(prv(*m, 0x5360B0u, Args{kAu, kOut, kOut + 4, kOut + 8}, tregs(kOut + 12)) == 0u);
    // magics
    CHECK(prv(*m, 0x536440u, Args{kAiff, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x536440u, Args{kAu, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x536D28u, Args{kAu, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x536D28u, Args{kAiff, 0, 0, 0}) == 0u);
    // AC-3 sync word 0x0B77 at byte 0 or 16, in either byte order
    std::memset(m->at(kOut), 0, 32);
    CHECK(prv(*m, 0x535F38u, Args{kOut, 0, 0, 0}) == 0u);
    wbytes(*m, kOut, {0x0B, 0x77});
    CHECK(prv(*m, 0x535F38u, Args{kOut, 0, 0, 0}) == 1u);
    wbytes(*m, kOut, {0x77, 0x0B});
    CHECK(prv(*m, 0x535F38u, Args{kOut, 0, 0, 0}) == 1u);
    wbytes(*m, kOut, {0x77, 0x77});
    wbytes(*m, kOut + 16, {0x0B, 0x77});
    CHECK(prv(*m, 0x535F38u, Args{kOut, 0, 0, 0}) == 1u);
    // keys: no phrase -> 0, 0, 0; the same phrase -> the same keys through the handle setter and the default setter
    prv(*m, 0x537528u, Args{0, 0, kOut, kOut + 2}, tregs(kOut + 4));
    CHECK(r16(*m, kOut) == 0);
    CHECK(r16(*m, kOut + 2) == 0);
    CHECK(r16(*m, kOut + 4) == 0);
    CHECK(r32(*m, 0x7838CCu) != 0u);  // the key tables were set up on the way
    prv(*m, 0x537528u, Args{kText, 11, kOut, kOut + 2}, tregs(kOut + 4));
    const u16 k0 = r16(*m, kOut), km = r16(*m, kOut + 2), ka = r16(*m, kOut + 4);
    CHECK((k0 | km | ka) != 0);
    prv(*m, 0x5380E0u, Args{kDec, kText, 0, 0});
    CHECK(r16(*m, kDec + 160) == k0);
    CHECK(r16(*m, kDec + 162) == km);
    CHECK(r16(*m, kDec + 164) == ka);
    prv(*m, 0x538148u, Args{kText, 0, 0, 0});
    CHECK(r16(*m, 0x7838E4u) == k0);
    CHECK(r16(*m, 0x7838E6u) == km);
    CHECK(r16(*m, 0x7838E8u) == ka);
    wstr(*m, kText, "persona3fet");
    prv(*m, 0x537528u, Args{kText, 11, kOut, kOut + 2}, tregs(kOut + 4));
    CHECK((r16(*m, kOut) != k0 || r16(*m, kOut + 2) != km || r16(*m, kOut + 4) != ka));
    // the halfword copy: n halfwords; n <= 0 copies nothing
    std::vector<u8> src(m->at(kHalf), m->at(kHalf) + 0x80);
    prv(*m, 0x538618u, Args{kHalf + 0x80, kHalf, 64, 0});
    CHECK(std::memcmp(m->at(kHalf + 0x80), src.data(), 0x80) == 0);
    w16(*m, kHalf + 0x80, 0xBEEF);
    prv(*m, 0x538618u, Args{kHalf + 0x80, kHalf, sx64(-1), 0});
    CHECK(r16(*m, kHalf + 0x80) == 0xBEEF);
    // the sync mode setter and the resolver (an explicit mode passes through)
    prv(*m, 0x53F630u, Args{3, 0, 0, 0});
    CHECK(r32(*m, 0x788630u) == 3u);
    for (u32 mode : {0u, 1u, 2u, 3u}) CHECK(prv(*m, 0x53F880u, Args{mode, 0, 0, 0}) == mode);
    // the key-table init count
    w32(*m, 0x7838CCu, 5);
    CHECK(prv(*m, 0x5374E8u, Args{0, 0, 0, 0}) == 0u);
    CHECK(r32(*m, 0x7838CCu) == 6u);
    CHECK(prv(*m, 0x537508u, Args{0, 0, 0, 0}) == 0u);
    CHECK(r32(*m, 0x7838CCu) == 5u);
}

#else

TEST_CASE("game(libs7): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
