// Pair tests for slice tail1 (game/src/lib/tail1_*.cpp: the CRI Sofdec middleware of the ELF tail -- the SFH stream-header
// parser, SFD's header-info builder, error records and parameter tables, MWSFD's header ring, the MPS / MPV handle and
// start-code helpers, SUD's tag and time base, SFX's handle pool). Every body against its recompiled body, compared by
// tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log. On top of the generic sweep (random worlds):
//   * SFH on the Sofdec headers of the disc's 41 movies (extracted/DATA/SFD): every getter against the bytes the header
//     holds, the picture size / frame rate against MPEG's packing and frame_rate_code table, the version gates on
//     edited copies, bad headers, the stream-id classes of ISO/IEC 13818-1;
//   * SFD's header-info record built from those headers; the SFH view pool;
//   * the start-code classifier on every code (ISO/IEC 13818-2 table 6-1), the scanners on random buffers against a
//     host model, the MPEG-1 / MPEG-2 decision on the movies' video;
//   * the error records (a real callback: sub_59D1B0 clears its argument), the handle pools of MPS / MPV / SFD, SFD's
//     parameter tables and their filter;
//   * MWSFD's header ring fed with the movies' headers; SUD's tag finder and time base (64-bit division); SFX's pool;
//     the stream-object peek with stand-ins for the object's calls; the empty duplicates against nullsub_1.
// Every random draw is its own statement (the order of evaluation inside one expression differs between compilers).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/tail1.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace tail1 = p3fes::game::tail1;

namespace p3fes::recomp_gen {
void fn_nullsub_1_001007f0(EEContext&);  // hand-written by font2: the original of the empty duplicates
void fn___env_unlock_3_00575950(EEContext&);  // generated body
void fn___env_unlock_3_00575950__recomp(EEContext&);  // recompiled
void fn___env_unlock_4_005777f0(EEContext&);  // generated body
void fn___env_unlock_4_005777f0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_17_00577a28(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_17_00577a28__recomp(EEContext&);  // recompiled
void fn_sub_577B40_00577b40(EEContext&);  // generated body
void fn_sub_577B40_00577b40__recomp(EEContext&);  // recompiled
void fn_sub_577BE0_00577be0(EEContext&);  // generated body
void fn_sub_577BE0_00577be0__recomp(EEContext&);  // recompiled
void fn_sub_577C30_00577c30(EEContext&);  // generated body
void fn_sub_577C30_00577c30__recomp(EEContext&);  // recompiled
void fn_sub_577C68_00577c68(EEContext&);  // generated body
void fn_sub_577C68_00577c68__recomp(EEContext&);  // recompiled
void fn_sub_577D00_00577d00(EEContext&);  // generated body
void fn_sub_577D00_00577d00__recomp(EEContext&);  // recompiled
void fn_sub_577D10_00577d10(EEContext&);  // generated body
void fn_sub_577D10_00577d10__recomp(EEContext&);  // recompiled
void fn_sub_577DB0_00577db0(EEContext&);  // generated body
void fn_sub_577DB0_00577db0__recomp(EEContext&);  // recompiled
void fn_sub_577E10_00577e10(EEContext&);  // generated body
void fn_sub_577E10_00577e10__recomp(EEContext&);  // recompiled
void fn_sub_577F08_00577f08(EEContext&);  // generated body
void fn_sub_577F08_00577f08__recomp(EEContext&);  // recompiled
void fn_sub_577F20_00577f20(EEContext&);  // generated body
void fn_sub_577F20_00577f20__recomp(EEContext&);  // recompiled
void fn_sub_577F48_00577f48(EEContext&);  // generated body
void fn_sub_577F48_00577f48__recomp(EEContext&);  // recompiled
void fn_sub_577F78_00577f78(EEContext&);  // generated body
void fn_sub_577F78_00577f78__recomp(EEContext&);  // recompiled
void fn_sub_577FC8_00577fc8(EEContext&);  // generated body
void fn_sub_577FC8_00577fc8__recomp(EEContext&);  // recompiled
void fn_sub_578060_00578060(EEContext&);  // generated body
void fn_sub_578060_00578060__recomp(EEContext&);  // recompiled
void fn_sub_578160_00578160(EEContext&);  // generated body
void fn_sub_578160_00578160__recomp(EEContext&);  // recompiled
void fn_sub_578D98_00578d98(EEContext&);  // generated body
void fn_sub_578D98_00578d98__recomp(EEContext&);  // recompiled
void fn_sub_578E08_00578e08(EEContext&);  // generated body
void fn_sub_578E08_00578e08__recomp(EEContext&);  // recompiled
void fn_sub_578E88_00578e88(EEContext&);  // generated body
void fn_sub_578E88_00578e88__recomp(EEContext&);  // recompiled
void fn_sub_578ED8_00578ed8(EEContext&);  // generated body
void fn_sub_578ED8_00578ed8__recomp(EEContext&);  // recompiled
void fn_sub_578FC0_00578fc0(EEContext&);  // generated body
void fn_sub_578FC0_00578fc0__recomp(EEContext&);  // recompiled
void fn_sub_579070_00579070(EEContext&);  // generated body
void fn_sub_579070_00579070__recomp(EEContext&);  // recompiled
void fn_sub_579078_00579078(EEContext&);  // generated body
void fn_sub_579078_00579078__recomp(EEContext&);  // recompiled
void fn_sub_579138_00579138(EEContext&);  // generated body
void fn_sub_579138_00579138__recomp(EEContext&);  // recompiled
void fn_sub_579240_00579240(EEContext&);  // generated body
void fn_sub_579240_00579240__recomp(EEContext&);  // recompiled
void fn_sub_5792A0_005792a0(EEContext&);  // generated body
void fn_sub_5792A0_005792a0__recomp(EEContext&);  // recompiled
void fn_sub_579368_00579368(EEContext&);  // generated body
void fn_sub_579368_00579368__recomp(EEContext&);  // recompiled
void fn_sub_5793E0_005793e0(EEContext&);  // generated body
void fn_sub_5793E0_005793e0__recomp(EEContext&);  // recompiled
void fn_sub_5793E8_005793e8(EEContext&);  // generated body
void fn_sub_5793E8_005793e8__recomp(EEContext&);  // recompiled
void fn_sub_579410_00579410(EEContext&);  // generated body
void fn_sub_579410_00579410__recomp(EEContext&);  // recompiled
void fn_sub_579428_00579428(EEContext&);  // generated body
void fn_sub_579428_00579428__recomp(EEContext&);  // recompiled
void fn_sub_579660_00579660(EEContext&);  // generated body
void fn_sub_579660_00579660__recomp(EEContext&);  // recompiled
void fn_sub_579770_00579770(EEContext&);  // generated body
void fn_sub_579770_00579770__recomp(EEContext&);  // recompiled
void fn_sub_57B7F0_0057b7f0(EEContext&);  // generated body
void fn_sub_57B7F0_0057b7f0__recomp(EEContext&);  // recompiled
void fn_sub_57F0C0_0057f0c0(EEContext&);  // generated body
void fn_sub_57F0C0_0057f0c0__recomp(EEContext&);  // recompiled
void fn_sub_57F0F0_0057f0f0(EEContext&);  // generated body
void fn_sub_57F0F0_0057f0f0__recomp(EEContext&);  // recompiled
void fn_sub_57F218_0057f218(EEContext&);  // generated body
void fn_sub_57F218_0057f218__recomp(EEContext&);  // recompiled
void fn_sub_57F258_0057f258(EEContext&);  // generated body
void fn_sub_57F258_0057f258__recomp(EEContext&);  // recompiled
void fn_sub_57F2C8_0057f2c8(EEContext&);  // generated body
void fn_sub_57F2C8_0057f2c8__recomp(EEContext&);  // recompiled
void fn_sub_57F2F8_0057f2f8(EEContext&);  // generated body
void fn_sub_57F2F8_0057f2f8__recomp(EEContext&);  // recompiled
void fn_sub_57F328_0057f328(EEContext&);  // generated body
void fn_sub_57F328_0057f328__recomp(EEContext&);  // recompiled
void fn_sub_57F390_0057f390(EEContext&);  // generated body
void fn_sub_57F390_0057f390__recomp(EEContext&);  // recompiled
void fn_sub_57F3E0_0057f3e0(EEContext&);  // generated body
void fn_sub_57F3E0_0057f3e0__recomp(EEContext&);  // recompiled
void fn_sub_57F528_0057f528(EEContext&);  // generated body
void fn_sub_57F528_0057f528__recomp(EEContext&);  // recompiled
void fn_sub_57F5F8_0057f5f8(EEContext&);  // generated body
void fn_sub_57F5F8_0057f5f8__recomp(EEContext&);  // recompiled
void fn___gthread_get_ee_key_value_0057f730(EEContext&);  // generated body
void fn___gthread_get_ee_key_value_0057f730__recomp(EEContext&);  // recompiled
void fn___gthread_get_ee_key_use_0057f740(EEContext&);  // generated body
void fn___gthread_get_ee_key_use_0057f740__recomp(EEContext&);  // recompiled
void fn_sub_582A08_00582a08(EEContext&);  // generated body
void fn_sub_582A08_00582a08__recomp(EEContext&);  // recompiled
void fn_sub_58B108_0058b108(EEContext&);  // generated body
void fn_sub_58B108_0058b108__recomp(EEContext&);  // recompiled
void fn_sub_58B128_0058b128(EEContext&);  // generated body
void fn_sub_58B128_0058b128__recomp(EEContext&);  // recompiled
void fn_sub_58B140_0058b140(EEContext&);  // generated body
void fn_sub_58B140_0058b140__recomp(EEContext&);  // recompiled
void fn_sub_58B158_0058b158(EEContext&);  // generated body
void fn_sub_58B158_0058b158__recomp(EEContext&);  // recompiled
void fn_sub_58B220_0058b220(EEContext&);  // generated body
void fn_sub_58B220_0058b220__recomp(EEContext&);  // recompiled
void fn_sub_58B248_0058b248(EEContext&);  // generated body
void fn_sub_58B248_0058b248__recomp(EEContext&);  // recompiled
void fn_sub_58B278_0058b278(EEContext&);  // generated body
void fn_sub_58B278_0058b278__recomp(EEContext&);  // recompiled
void fn_sub_58B510_0058b510(EEContext&);  // generated body
void fn_sub_58B510_0058b510__recomp(EEContext&);  // recompiled
void fn_sub_58B560_0058b560(EEContext&);  // generated body
void fn_sub_58B560_0058b560__recomp(EEContext&);  // recompiled
void fn_sub_58B5C8_0058b5c8(EEContext&);  // generated body
void fn_sub_58B5C8_0058b5c8__recomp(EEContext&);  // recompiled
void fn_sub_58B720_0058b720(EEContext&);  // generated body
void fn_sub_58B720_0058b720__recomp(EEContext&);  // recompiled
void fn_sub_58B7B0_0058b7b0(EEContext&);  // generated body
void fn_sub_58B7B0_0058b7b0__recomp(EEContext&);  // recompiled
void fn_sub_58B868_0058b868(EEContext&);  // generated body
void fn_sub_58B868_0058b868__recomp(EEContext&);  // recompiled
void fn_sub_58B8E0_0058b8e0(EEContext&);  // generated body
void fn_sub_58B8E0_0058b8e0__recomp(EEContext&);  // recompiled
void fn_sub_58B978_0058b978(EEContext&);  // generated body
void fn_sub_58B978_0058b978__recomp(EEContext&);  // recompiled
void fn_sub_58BB10_0058bb10(EEContext&);  // generated body
void fn_sub_58BB10_0058bb10__recomp(EEContext&);  // recompiled
void fn_sub_58BB48_0058bb48(EEContext&);  // generated body
void fn_sub_58BB48_0058bb48__recomp(EEContext&);  // recompiled
void fn_sub_58BB80_0058bb80(EEContext&);  // generated body
void fn_sub_58BB80_0058bb80__recomp(EEContext&);  // recompiled
void fn_sub_58BBA8_0058bba8(EEContext&);  // generated body
void fn_sub_58BBA8_0058bba8__recomp(EEContext&);  // recompiled
void fn_sub_58BBB0_0058bbb0(EEContext&);  // generated body
void fn_sub_58BBB0_0058bbb0__recomp(EEContext&);  // recompiled
void fn_sub_58BBE8_0058bbe8(EEContext&);  // generated body
void fn_sub_58BBE8_0058bbe8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_20_0058bc10(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_20_0058bc10__recomp(EEContext&);  // recompiled
void fn_sub_58BC20_0058bc20(EEContext&);  // generated body
void fn_sub_58BC20_0058bc20__recomp(EEContext&);  // recompiled
void fn_sub_58BD58_0058bd58(EEContext&);  // generated body
void fn_sub_58BD58_0058bd58__recomp(EEContext&);  // recompiled
void fn_sub_58BE10_0058be10(EEContext&);  // generated body
void fn_sub_58BE10_0058be10__recomp(EEContext&);  // recompiled
void fn_sub_58BE28_0058be28(EEContext&);  // generated body
void fn_sub_58BE28_0058be28__recomp(EEContext&);  // recompiled
void fn_sub_58BE40_0058be40(EEContext&);  // generated body
void fn_sub_58BE40_0058be40__recomp(EEContext&);  // recompiled
void fn_sub_58BEB0_0058beb0(EEContext&);  // generated body
void fn_sub_58BEB0_0058beb0__recomp(EEContext&);  // recompiled
void fn_sub_58BEF0_0058bef0(EEContext&);  // generated body
void fn_sub_58BEF0_0058bef0__recomp(EEContext&);  // recompiled
void fn_sub_58BF88_0058bf88(EEContext&);  // generated body
void fn_sub_58BF88_0058bf88__recomp(EEContext&);  // recompiled
void fn_sub_58BF98_0058bf98(EEContext&);  // generated body
void fn_sub_58BF98_0058bf98__recomp(EEContext&);  // recompiled
void fn_sub_58C060_0058c060(EEContext&);  // generated body
void fn_sub_58C060_0058c060__recomp(EEContext&);  // recompiled
void fn_sub_58E250_0058e250(EEContext&);  // generated body
void fn_sub_58E250_0058e250__recomp(EEContext&);  // recompiled
void fn_sub_599100_00599100(EEContext&);  // generated body
void fn_sub_599100_00599100__recomp(EEContext&);  // recompiled
void fn_sub_5991B8_005991b8(EEContext&);  // generated body
void fn_sub_5991B8_005991b8__recomp(EEContext&);  // recompiled
void fn_sub_599240_00599240(EEContext&);  // generated body
void fn_sub_599240_00599240__recomp(EEContext&);  // recompiled
void fn_sub_599290_00599290(EEContext&);  // generated body
void fn_sub_599290_00599290__recomp(EEContext&);  // recompiled
void fn_sub_5992E0_005992e0(EEContext&);  // generated body
void fn_sub_5992E0_005992e0__recomp(EEContext&);  // recompiled
void fn_sub_59BCD0_0059bcd0(EEContext&);  // generated body
void fn_sub_59BCD0_0059bcd0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_21_0059cfa0(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_21_0059cfa0__recomp(EEContext&);  // recompiled
void fn_sub_59CFB0_0059cfb0(EEContext&);  // generated body
void fn_sub_59CFB0_0059cfb0__recomp(EEContext&);  // recompiled
void fn_sub_59CFC0_0059cfc0(EEContext&);  // generated body
void fn_sub_59CFC0_0059cfc0__recomp(EEContext&);  // recompiled
void fn_sub_59D050_0059d050(EEContext&);  // generated body
void fn_sub_59D050_0059d050__recomp(EEContext&);  // recompiled
void fn_sub_59D098_0059d098(EEContext&);  // generated body
void fn_sub_59D098_0059d098__recomp(EEContext&);  // recompiled
void fn_sub_59D160_0059d160(EEContext&);  // generated body
void fn_sub_59D160_0059d160__recomp(EEContext&);  // recompiled
void fn_sub_59D1B0_0059d1b0(EEContext&);  // generated body
void fn_sub_59D1B0_0059d1b0__recomp(EEContext&);  // recompiled
void fn_sub_59D1C8_0059d1c8(EEContext&);  // generated body
void fn_sub_59D1C8_0059d1c8__recomp(EEContext&);  // recompiled
void fn_sub_59D1E0_0059d1e0(EEContext&);  // generated body
void fn_sub_59D1E0_0059d1e0__recomp(EEContext&);  // recompiled
void fn_sub_59D230_0059d230(EEContext&);  // generated body
void fn_sub_59D230_0059d230__recomp(EEContext&);  // recompiled
void fn_sub_59D240_0059d240(EEContext&);  // generated body
void fn_sub_59D240_0059d240__recomp(EEContext&);  // recompiled
void fn_sub_59D288_0059d288(EEContext&);  // generated body
void fn_sub_59D288_0059d288__recomp(EEContext&);  // recompiled
void fn_sub_59D2B0_0059d2b0(EEContext&);  // generated body
void fn_sub_59D2B0_0059d2b0__recomp(EEContext&);  // recompiled
void fn_sub_59D3A0_0059d3a0(EEContext&);  // generated body
void fn_sub_59D3A0_0059d3a0__recomp(EEContext&);  // recompiled
void fn_sub_59D410_0059d410(EEContext&);  // generated body
void fn_sub_59D410_0059d410__recomp(EEContext&);  // recompiled
void fn_sub_59D4E0_0059d4e0(EEContext&);  // generated body
void fn_sub_59D4E0_0059d4e0__recomp(EEContext&);  // recompiled
void fn_sub_59D528_0059d528(EEContext&);  // generated body
void fn_sub_59D528_0059d528__recomp(EEContext&);  // recompiled
void fn_sub_59D598_0059d598(EEContext&);  // generated body
void fn_sub_59D598_0059d598__recomp(EEContext&);  // recompiled
void fn_sub_59D608_0059d608(EEContext&);  // generated body
void fn_sub_59D608_0059d608__recomp(EEContext&);  // recompiled
void fn_sub_59D6A0_0059d6a0(EEContext&);  // generated body
void fn_sub_59D6A0_0059d6a0__recomp(EEContext&);  // recompiled
void fn_sub_59D770_0059d770(EEContext&);  // generated body
void fn_sub_59D770_0059d770__recomp(EEContext&);  // recompiled
void fn_sub_59D848_0059d848(EEContext&);  // generated body
void fn_sub_59D848_0059d848__recomp(EEContext&);  // recompiled
void fn_sub_59D898_0059d898(EEContext&);  // generated body
void fn_sub_59D898_0059d898__recomp(EEContext&);  // recompiled
void fn_sub_59D8E8_0059d8e8(EEContext&);  // generated body
void fn_sub_59D8E8_0059d8e8__recomp(EEContext&);  // recompiled
void fn_sub_59D938_0059d938(EEContext&);  // generated body
void fn_sub_59D938_0059d938__recomp(EEContext&);  // recompiled
void fn_sub_59D988_0059d988(EEContext&);  // generated body
void fn_sub_59D988_0059d988__recomp(EEContext&);  // recompiled
void fn_sub_59D9E8_0059d9e8(EEContext&);  // generated body
void fn_sub_59D9E8_0059d9e8__recomp(EEContext&);  // recompiled
void fn_sub_59DA70_0059da70(EEContext&);  // generated body
void fn_sub_59DA70_0059da70__recomp(EEContext&);  // recompiled
void fn_sub_59DAC0_0059dac0(EEContext&);  // generated body
void fn_sub_59DAC0_0059dac0__recomp(EEContext&);  // recompiled
void fn_sub_59DB10_0059db10(EEContext&);  // generated body
void fn_sub_59DB10_0059db10__recomp(EEContext&);  // recompiled
void fn_sub_59DB60_0059db60(EEContext&);  // generated body
void fn_sub_59DB60_0059db60__recomp(EEContext&);  // recompiled
void fn_sub_59DBB0_0059dbb0(EEContext&);  // generated body
void fn_sub_59DBB0_0059dbb0__recomp(EEContext&);  // recompiled
void fn_sub_59DC18_0059dc18(EEContext&);  // generated body
void fn_sub_59DC18_0059dc18__recomp(EEContext&);  // recompiled
void fn_sub_59DC68_0059dc68(EEContext&);  // generated body
void fn_sub_59DC68_0059dc68__recomp(EEContext&);  // recompiled
void fn_sub_59DCB8_0059dcb8(EEContext&);  // generated body
void fn_sub_59DCB8_0059dcb8__recomp(EEContext&);  // recompiled
void fn_sub_59DD08_0059dd08(EEContext&);  // generated body
void fn_sub_59DD08_0059dd08__recomp(EEContext&);  // recompiled
void fn_sub_59DD40_0059dd40(EEContext&);  // generated body
void fn_sub_59DD40_0059dd40__recomp(EEContext&);  // recompiled
void fn_sub_59DD78_0059dd78(EEContext&);  // generated body
void fn_sub_59DD78_0059dd78__recomp(EEContext&);  // recompiled
void fn_sub_59DDF0_0059ddf0(EEContext&);  // generated body
void fn_sub_59DDF0_0059ddf0__recomp(EEContext&);  // recompiled
void fn_sub_59DE68_0059de68(EEContext&);  // generated body
void fn_sub_59DE68_0059de68__recomp(EEContext&);  // recompiled
void fn_sub_59DEC0_0059dec0(EEContext&);  // generated body
void fn_sub_59DEC0_0059dec0__recomp(EEContext&);  // recompiled
void fn_sub_59DF30_0059df30(EEContext&);  // generated body
void fn_sub_59DF30_0059df30__recomp(EEContext&);  // recompiled
void fn_sub_59DFB0_0059dfb0(EEContext&);  // generated body
void fn_sub_59DFB0_0059dfb0__recomp(EEContext&);  // recompiled
void fn_sub_59E020_0059e020(EEContext&);  // generated body
void fn_sub_59E020_0059e020__recomp(EEContext&);  // recompiled
void fn_sub_59E090_0059e090(EEContext&);  // generated body
void fn_sub_59E090_0059e090__recomp(EEContext&);  // recompiled
void fn_sub_59E100_0059e100(EEContext&);  // generated body
void fn_sub_59E100_0059e100__recomp(EEContext&);  // recompiled
void fn_sub_59E178_0059e178(EEContext&);  // generated body
void fn_sub_59E178_0059e178__recomp(EEContext&);  // recompiled
void fn_sub_59E228_0059e228(EEContext&);  // generated body
void fn_sub_59E228_0059e228__recomp(EEContext&);  // recompiled
void fn_sub_59E298_0059e298(EEContext&);  // generated body
void fn_sub_59E298_0059e298__recomp(EEContext&);  // recompiled
void fn_sub_59E308_0059e308(EEContext&);  // generated body
void fn_sub_59E308_0059e308__recomp(EEContext&);  // recompiled
void fn_sub_59E378_0059e378(EEContext&);  // generated body
void fn_sub_59E378_0059e378__recomp(EEContext&);  // recompiled
void fn_sub_59E3E8_0059e3e8(EEContext&);  // generated body
void fn_sub_59E3E8_0059e3e8__recomp(EEContext&);  // recompiled
void fn_sub_59E460_0059e460(EEContext&);  // generated body
void fn_sub_59E460_0059e460__recomp(EEContext&);  // recompiled
void fn_sub_59E4D0_0059e4d0(EEContext&);  // generated body
void fn_sub_59E4D0_0059e4d0__recomp(EEContext&);  // recompiled
void fn_sub_59E558_0059e558(EEContext&);  // generated body
void fn_sub_59E558_0059e558__recomp(EEContext&);  // recompiled
void fn_sub_59E5E0_0059e5e0(EEContext&);  // generated body
void fn_sub_59E5E0_0059e5e0__recomp(EEContext&);  // recompiled
void fn_sub_59E670_0059e670(EEContext&);  // generated body
void fn_sub_59E670_0059e670__recomp(EEContext&);  // recompiled
void fn_sub_59E6E0_0059e6e0(EEContext&);  // generated body
void fn_sub_59E6E0_0059e6e0__recomp(EEContext&);  // recompiled
void fn_sub_59E720_0059e720(EEContext&);  // generated body
void fn_sub_59E720_0059e720__recomp(EEContext&);  // recompiled
void fn_sub_59E760_0059e760(EEContext&);  // generated body
void fn_sub_59E760_0059e760__recomp(EEContext&);  // recompiled
void fn_sub_59E7A8_0059e7a8(EEContext&);  // generated body
void fn_sub_59E7A8_0059e7a8__recomp(EEContext&);  // recompiled
void fn_sub_59E800_0059e800(EEContext&);  // generated body
void fn_sub_59E800_0059e800__recomp(EEContext&);  // recompiled
void fn_sub_59E808_0059e808(EEContext&);  // generated body
void fn_sub_59E808_0059e808__recomp(EEContext&);  // recompiled
void fn_sub_59E860_0059e860(EEContext&);  // generated body
void fn_sub_59E860_0059e860__recomp(EEContext&);  // recompiled
void fn_sub_59E8B0_0059e8b0(EEContext&);  // generated body
void fn_sub_59E8B0_0059e8b0__recomp(EEContext&);  // recompiled
void fn_sub_59E8F0_0059e8f0(EEContext&);  // generated body
void fn_sub_59E8F0_0059e8f0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_23_005a1158(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_23_005a1158__recomp(EEContext&);  // recompiled
void fn_sub_5A1218_005a1218(EEContext&);  // generated body
void fn_sub_5A1218_005a1218__recomp(EEContext&);  // recompiled
void fn_sub_5A12F8_005a12f8(EEContext&);  // generated body
void fn_sub_5A12F8_005a12f8__recomp(EEContext&);  // recompiled
void fn_sub_5A1790_005a1790(EEContext&);  // generated body
void fn_sub_5A1790_005a1790__recomp(EEContext&);  // recompiled
void fn_sub_5A1858_005a1858(EEContext&);  // generated body
void fn_sub_5A1858_005a1858__recomp(EEContext&);  // recompiled
void fn_sub_5A1B58_005a1b58(EEContext&);  // generated body
void fn_sub_5A1B58_005a1b58__recomp(EEContext&);  // recompiled
void fn_sub_5A1B68_005a1b68(EEContext&);  // generated body
void fn_sub_5A1B68_005a1b68__recomp(EEContext&);  // recompiled
void fn_sub_5A1B80_005a1b80(EEContext&);  // generated body
void fn_sub_5A1B80_005a1b80__recomp(EEContext&);  // recompiled
void fn_sub_5A1C08_005a1c08(EEContext&);  // generated body
void fn_sub_5A1C08_005a1c08__recomp(EEContext&);  // recompiled
void fn_sub_5A1CE0_005a1ce0(EEContext&);  // generated body
void fn_sub_5A1CE0_005a1ce0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"__env_unlock_3", 0x575950, &recomp_gen::fn___env_unlock_3_00575950, &recomp_gen::fn___env_unlock_3_00575950__recomp},
    {"__env_unlock_4", 0x5777F0, &recomp_gen::fn___env_unlock_4_005777f0, &recomp_gen::fn___env_unlock_4_005777f0__recomp},
    {"sceLibgcc32GetErxEntries_17", 0x577A28, &recomp_gen::fn_sceLibgcc32GetErxEntries_17_00577a28, &recomp_gen::fn_sceLibgcc32GetErxEntries_17_00577a28__recomp},
    {"sub_577B40", 0x577B40, &recomp_gen::fn_sub_577B40_00577b40, &recomp_gen::fn_sub_577B40_00577b40__recomp},
    {"sub_577BE0", 0x577BE0, &recomp_gen::fn_sub_577BE0_00577be0, &recomp_gen::fn_sub_577BE0_00577be0__recomp},
    {"sub_577C30", 0x577C30, &recomp_gen::fn_sub_577C30_00577c30, &recomp_gen::fn_sub_577C30_00577c30__recomp},
    {"sub_577C68", 0x577C68, &recomp_gen::fn_sub_577C68_00577c68, &recomp_gen::fn_sub_577C68_00577c68__recomp},
    {"sub_577D00", 0x577D00, &recomp_gen::fn_sub_577D00_00577d00, &recomp_gen::fn_sub_577D00_00577d00__recomp},
    {"sub_577D10", 0x577D10, &recomp_gen::fn_sub_577D10_00577d10, &recomp_gen::fn_sub_577D10_00577d10__recomp},
    {"sub_577DB0", 0x577DB0, &recomp_gen::fn_sub_577DB0_00577db0, &recomp_gen::fn_sub_577DB0_00577db0__recomp},
    {"sub_577E10", 0x577E10, &recomp_gen::fn_sub_577E10_00577e10, &recomp_gen::fn_sub_577E10_00577e10__recomp},
    {"sub_577F08", 0x577F08, &recomp_gen::fn_sub_577F08_00577f08, &recomp_gen::fn_sub_577F08_00577f08__recomp},
    {"sub_577F20", 0x577F20, &recomp_gen::fn_sub_577F20_00577f20, &recomp_gen::fn_sub_577F20_00577f20__recomp},
    {"sub_577F48", 0x577F48, &recomp_gen::fn_sub_577F48_00577f48, &recomp_gen::fn_sub_577F48_00577f48__recomp},
    {"sub_577F78", 0x577F78, &recomp_gen::fn_sub_577F78_00577f78, &recomp_gen::fn_sub_577F78_00577f78__recomp},
    {"sub_577FC8", 0x577FC8, &recomp_gen::fn_sub_577FC8_00577fc8, &recomp_gen::fn_sub_577FC8_00577fc8__recomp},
    {"sub_578060", 0x578060, &recomp_gen::fn_sub_578060_00578060, &recomp_gen::fn_sub_578060_00578060__recomp},
    {"sub_578160", 0x578160, &recomp_gen::fn_sub_578160_00578160, &recomp_gen::fn_sub_578160_00578160__recomp},
    {"sub_578D98", 0x578D98, &recomp_gen::fn_sub_578D98_00578d98, &recomp_gen::fn_sub_578D98_00578d98__recomp},
    {"sub_578E08", 0x578E08, &recomp_gen::fn_sub_578E08_00578e08, &recomp_gen::fn_sub_578E08_00578e08__recomp},
    {"sub_578E88", 0x578E88, &recomp_gen::fn_sub_578E88_00578e88, &recomp_gen::fn_sub_578E88_00578e88__recomp},
    {"sub_578ED8", 0x578ED8, &recomp_gen::fn_sub_578ED8_00578ed8, &recomp_gen::fn_sub_578ED8_00578ed8__recomp},
    {"sub_578FC0", 0x578FC0, &recomp_gen::fn_sub_578FC0_00578fc0, &recomp_gen::fn_sub_578FC0_00578fc0__recomp},
    {"sub_579070", 0x579070, &recomp_gen::fn_sub_579070_00579070, &recomp_gen::fn_sub_579070_00579070__recomp},
    {"sub_579078", 0x579078, &recomp_gen::fn_sub_579078_00579078, &recomp_gen::fn_sub_579078_00579078__recomp},
    {"sub_579138", 0x579138, &recomp_gen::fn_sub_579138_00579138, &recomp_gen::fn_sub_579138_00579138__recomp},
    {"sub_579240", 0x579240, &recomp_gen::fn_sub_579240_00579240, &recomp_gen::fn_sub_579240_00579240__recomp},
    {"sub_5792A0", 0x5792A0, &recomp_gen::fn_sub_5792A0_005792a0, &recomp_gen::fn_sub_5792A0_005792a0__recomp},
    {"sub_579368", 0x579368, &recomp_gen::fn_sub_579368_00579368, &recomp_gen::fn_sub_579368_00579368__recomp},
    {"sub_5793E0", 0x5793E0, &recomp_gen::fn_sub_5793E0_005793e0, &recomp_gen::fn_sub_5793E0_005793e0__recomp},
    {"sub_5793E8", 0x5793E8, &recomp_gen::fn_sub_5793E8_005793e8, &recomp_gen::fn_sub_5793E8_005793e8__recomp},
    {"sub_579410", 0x579410, &recomp_gen::fn_sub_579410_00579410, &recomp_gen::fn_sub_579410_00579410__recomp},
    {"sub_579428", 0x579428, &recomp_gen::fn_sub_579428_00579428, &recomp_gen::fn_sub_579428_00579428__recomp},
    {"sub_579660", 0x579660, &recomp_gen::fn_sub_579660_00579660, &recomp_gen::fn_sub_579660_00579660__recomp},
    {"sub_579770", 0x579770, &recomp_gen::fn_sub_579770_00579770, &recomp_gen::fn_sub_579770_00579770__recomp},
    {"sub_57B7F0", 0x57B7F0, &recomp_gen::fn_sub_57B7F0_0057b7f0, &recomp_gen::fn_sub_57B7F0_0057b7f0__recomp},
    {"sub_57F0C0", 0x57F0C0, &recomp_gen::fn_sub_57F0C0_0057f0c0, &recomp_gen::fn_sub_57F0C0_0057f0c0__recomp},
    {"sub_57F0F0", 0x57F0F0, &recomp_gen::fn_sub_57F0F0_0057f0f0, &recomp_gen::fn_sub_57F0F0_0057f0f0__recomp},
    {"sub_57F218", 0x57F218, &recomp_gen::fn_sub_57F218_0057f218, &recomp_gen::fn_sub_57F218_0057f218__recomp},
    {"sub_57F258", 0x57F258, &recomp_gen::fn_sub_57F258_0057f258, &recomp_gen::fn_sub_57F258_0057f258__recomp},
    {"sub_57F2C8", 0x57F2C8, &recomp_gen::fn_sub_57F2C8_0057f2c8, &recomp_gen::fn_sub_57F2C8_0057f2c8__recomp},
    {"sub_57F2F8", 0x57F2F8, &recomp_gen::fn_sub_57F2F8_0057f2f8, &recomp_gen::fn_sub_57F2F8_0057f2f8__recomp},
    {"sub_57F328", 0x57F328, &recomp_gen::fn_sub_57F328_0057f328, &recomp_gen::fn_sub_57F328_0057f328__recomp},
    {"sub_57F390", 0x57F390, &recomp_gen::fn_sub_57F390_0057f390, &recomp_gen::fn_sub_57F390_0057f390__recomp},
    {"sub_57F3E0", 0x57F3E0, &recomp_gen::fn_sub_57F3E0_0057f3e0, &recomp_gen::fn_sub_57F3E0_0057f3e0__recomp},
    {"sub_57F528", 0x57F528, &recomp_gen::fn_sub_57F528_0057f528, &recomp_gen::fn_sub_57F528_0057f528__recomp},
    {"sub_57F5F8", 0x57F5F8, &recomp_gen::fn_sub_57F5F8_0057f5f8, &recomp_gen::fn_sub_57F5F8_0057f5f8__recomp},
    {"__gthread_get_ee_key_value", 0x57F730, &recomp_gen::fn___gthread_get_ee_key_value_0057f730, &recomp_gen::fn___gthread_get_ee_key_value_0057f730__recomp},
    {"__gthread_get_ee_key_use", 0x57F740, &recomp_gen::fn___gthread_get_ee_key_use_0057f740, &recomp_gen::fn___gthread_get_ee_key_use_0057f740__recomp},
    {"sub_582A08", 0x582A08, &recomp_gen::fn_sub_582A08_00582a08, &recomp_gen::fn_sub_582A08_00582a08__recomp},
    {"sub_58B108", 0x58B108, &recomp_gen::fn_sub_58B108_0058b108, &recomp_gen::fn_sub_58B108_0058b108__recomp},
    {"sub_58B128", 0x58B128, &recomp_gen::fn_sub_58B128_0058b128, &recomp_gen::fn_sub_58B128_0058b128__recomp},
    {"sub_58B140", 0x58B140, &recomp_gen::fn_sub_58B140_0058b140, &recomp_gen::fn_sub_58B140_0058b140__recomp},
    {"sub_58B158", 0x58B158, &recomp_gen::fn_sub_58B158_0058b158, &recomp_gen::fn_sub_58B158_0058b158__recomp},
    {"sub_58B220", 0x58B220, &recomp_gen::fn_sub_58B220_0058b220, &recomp_gen::fn_sub_58B220_0058b220__recomp},
    {"sub_58B248", 0x58B248, &recomp_gen::fn_sub_58B248_0058b248, &recomp_gen::fn_sub_58B248_0058b248__recomp},
    {"sub_58B278", 0x58B278, &recomp_gen::fn_sub_58B278_0058b278, &recomp_gen::fn_sub_58B278_0058b278__recomp},
    {"sub_58B510", 0x58B510, &recomp_gen::fn_sub_58B510_0058b510, &recomp_gen::fn_sub_58B510_0058b510__recomp},
    {"sub_58B560", 0x58B560, &recomp_gen::fn_sub_58B560_0058b560, &recomp_gen::fn_sub_58B560_0058b560__recomp},
    {"sub_58B5C8", 0x58B5C8, &recomp_gen::fn_sub_58B5C8_0058b5c8, &recomp_gen::fn_sub_58B5C8_0058b5c8__recomp},
    {"sub_58B720", 0x58B720, &recomp_gen::fn_sub_58B720_0058b720, &recomp_gen::fn_sub_58B720_0058b720__recomp},
    {"sub_58B7B0", 0x58B7B0, &recomp_gen::fn_sub_58B7B0_0058b7b0, &recomp_gen::fn_sub_58B7B0_0058b7b0__recomp},
    {"sub_58B868", 0x58B868, &recomp_gen::fn_sub_58B868_0058b868, &recomp_gen::fn_sub_58B868_0058b868__recomp},
    {"sub_58B8E0", 0x58B8E0, &recomp_gen::fn_sub_58B8E0_0058b8e0, &recomp_gen::fn_sub_58B8E0_0058b8e0__recomp},
    {"sub_58B978", 0x58B978, &recomp_gen::fn_sub_58B978_0058b978, &recomp_gen::fn_sub_58B978_0058b978__recomp},
    {"sub_58BB10", 0x58BB10, &recomp_gen::fn_sub_58BB10_0058bb10, &recomp_gen::fn_sub_58BB10_0058bb10__recomp},
    {"sub_58BB48", 0x58BB48, &recomp_gen::fn_sub_58BB48_0058bb48, &recomp_gen::fn_sub_58BB48_0058bb48__recomp},
    {"sub_58BB80", 0x58BB80, &recomp_gen::fn_sub_58BB80_0058bb80, &recomp_gen::fn_sub_58BB80_0058bb80__recomp},
    {"sub_58BBA8", 0x58BBA8, &recomp_gen::fn_sub_58BBA8_0058bba8, &recomp_gen::fn_sub_58BBA8_0058bba8__recomp},
    {"sub_58BBB0", 0x58BBB0, &recomp_gen::fn_sub_58BBB0_0058bbb0, &recomp_gen::fn_sub_58BBB0_0058bbb0__recomp},
    {"sub_58BBE8", 0x58BBE8, &recomp_gen::fn_sub_58BBE8_0058bbe8, &recomp_gen::fn_sub_58BBE8_0058bbe8__recomp},
    {"sceLibgcc32GetErxEntries_20", 0x58BC10, &recomp_gen::fn_sceLibgcc32GetErxEntries_20_0058bc10, &recomp_gen::fn_sceLibgcc32GetErxEntries_20_0058bc10__recomp},
    {"sub_58BC20", 0x58BC20, &recomp_gen::fn_sub_58BC20_0058bc20, &recomp_gen::fn_sub_58BC20_0058bc20__recomp},
    {"sub_58BD58", 0x58BD58, &recomp_gen::fn_sub_58BD58_0058bd58, &recomp_gen::fn_sub_58BD58_0058bd58__recomp},
    {"sub_58BE10", 0x58BE10, &recomp_gen::fn_sub_58BE10_0058be10, &recomp_gen::fn_sub_58BE10_0058be10__recomp},
    {"sub_58BE28", 0x58BE28, &recomp_gen::fn_sub_58BE28_0058be28, &recomp_gen::fn_sub_58BE28_0058be28__recomp},
    {"sub_58BE40", 0x58BE40, &recomp_gen::fn_sub_58BE40_0058be40, &recomp_gen::fn_sub_58BE40_0058be40__recomp},
    {"sub_58BEB0", 0x58BEB0, &recomp_gen::fn_sub_58BEB0_0058beb0, &recomp_gen::fn_sub_58BEB0_0058beb0__recomp},
    {"sub_58BEF0", 0x58BEF0, &recomp_gen::fn_sub_58BEF0_0058bef0, &recomp_gen::fn_sub_58BEF0_0058bef0__recomp},
    {"sub_58BF88", 0x58BF88, &recomp_gen::fn_sub_58BF88_0058bf88, &recomp_gen::fn_sub_58BF88_0058bf88__recomp},
    {"sub_58BF98", 0x58BF98, &recomp_gen::fn_sub_58BF98_0058bf98, &recomp_gen::fn_sub_58BF98_0058bf98__recomp},
    {"sub_58C060", 0x58C060, &recomp_gen::fn_sub_58C060_0058c060, &recomp_gen::fn_sub_58C060_0058c060__recomp},
    {"sub_58E250", 0x58E250, &recomp_gen::fn_sub_58E250_0058e250, &recomp_gen::fn_sub_58E250_0058e250__recomp},
    {"sub_599100", 0x599100, &recomp_gen::fn_sub_599100_00599100, &recomp_gen::fn_sub_599100_00599100__recomp},
    {"sub_5991B8", 0x5991B8, &recomp_gen::fn_sub_5991B8_005991b8, &recomp_gen::fn_sub_5991B8_005991b8__recomp},
    {"sub_599240", 0x599240, &recomp_gen::fn_sub_599240_00599240, &recomp_gen::fn_sub_599240_00599240__recomp},
    {"sub_599290", 0x599290, &recomp_gen::fn_sub_599290_00599290, &recomp_gen::fn_sub_599290_00599290__recomp},
    {"sub_5992E0", 0x5992E0, &recomp_gen::fn_sub_5992E0_005992e0, &recomp_gen::fn_sub_5992E0_005992e0__recomp},
    {"sub_59BCD0", 0x59BCD0, &recomp_gen::fn_sub_59BCD0_0059bcd0, &recomp_gen::fn_sub_59BCD0_0059bcd0__recomp},
    {"sceLibgcc32GetErxEntries_21", 0x59CFA0, &recomp_gen::fn_sceLibgcc32GetErxEntries_21_0059cfa0, &recomp_gen::fn_sceLibgcc32GetErxEntries_21_0059cfa0__recomp},
    {"sub_59CFB0", 0x59CFB0, &recomp_gen::fn_sub_59CFB0_0059cfb0, &recomp_gen::fn_sub_59CFB0_0059cfb0__recomp},
    {"sub_59CFC0", 0x59CFC0, &recomp_gen::fn_sub_59CFC0_0059cfc0, &recomp_gen::fn_sub_59CFC0_0059cfc0__recomp},
    {"sub_59D050", 0x59D050, &recomp_gen::fn_sub_59D050_0059d050, &recomp_gen::fn_sub_59D050_0059d050__recomp},
    {"sub_59D098", 0x59D098, &recomp_gen::fn_sub_59D098_0059d098, &recomp_gen::fn_sub_59D098_0059d098__recomp},
    {"sub_59D160", 0x59D160, &recomp_gen::fn_sub_59D160_0059d160, &recomp_gen::fn_sub_59D160_0059d160__recomp},
    {"sub_59D1B0", 0x59D1B0, &recomp_gen::fn_sub_59D1B0_0059d1b0, &recomp_gen::fn_sub_59D1B0_0059d1b0__recomp},
    {"sub_59D1C8", 0x59D1C8, &recomp_gen::fn_sub_59D1C8_0059d1c8, &recomp_gen::fn_sub_59D1C8_0059d1c8__recomp},
    {"sub_59D1E0", 0x59D1E0, &recomp_gen::fn_sub_59D1E0_0059d1e0, &recomp_gen::fn_sub_59D1E0_0059d1e0__recomp},
    {"sub_59D230", 0x59D230, &recomp_gen::fn_sub_59D230_0059d230, &recomp_gen::fn_sub_59D230_0059d230__recomp},
    {"sub_59D240", 0x59D240, &recomp_gen::fn_sub_59D240_0059d240, &recomp_gen::fn_sub_59D240_0059d240__recomp},
    {"sub_59D288", 0x59D288, &recomp_gen::fn_sub_59D288_0059d288, &recomp_gen::fn_sub_59D288_0059d288__recomp},
    {"sub_59D2B0", 0x59D2B0, &recomp_gen::fn_sub_59D2B0_0059d2b0, &recomp_gen::fn_sub_59D2B0_0059d2b0__recomp},
    {"sub_59D3A0", 0x59D3A0, &recomp_gen::fn_sub_59D3A0_0059d3a0, &recomp_gen::fn_sub_59D3A0_0059d3a0__recomp},
    {"sub_59D410", 0x59D410, &recomp_gen::fn_sub_59D410_0059d410, &recomp_gen::fn_sub_59D410_0059d410__recomp},
    {"sub_59D4E0", 0x59D4E0, &recomp_gen::fn_sub_59D4E0_0059d4e0, &recomp_gen::fn_sub_59D4E0_0059d4e0__recomp},
    {"sub_59D528", 0x59D528, &recomp_gen::fn_sub_59D528_0059d528, &recomp_gen::fn_sub_59D528_0059d528__recomp},
    {"sub_59D598", 0x59D598, &recomp_gen::fn_sub_59D598_0059d598, &recomp_gen::fn_sub_59D598_0059d598__recomp},
    {"sub_59D608", 0x59D608, &recomp_gen::fn_sub_59D608_0059d608, &recomp_gen::fn_sub_59D608_0059d608__recomp},
    {"sub_59D6A0", 0x59D6A0, &recomp_gen::fn_sub_59D6A0_0059d6a0, &recomp_gen::fn_sub_59D6A0_0059d6a0__recomp},
    {"sub_59D770", 0x59D770, &recomp_gen::fn_sub_59D770_0059d770, &recomp_gen::fn_sub_59D770_0059d770__recomp},
    {"sub_59D848", 0x59D848, &recomp_gen::fn_sub_59D848_0059d848, &recomp_gen::fn_sub_59D848_0059d848__recomp},
    {"sub_59D898", 0x59D898, &recomp_gen::fn_sub_59D898_0059d898, &recomp_gen::fn_sub_59D898_0059d898__recomp},
    {"sub_59D8E8", 0x59D8E8, &recomp_gen::fn_sub_59D8E8_0059d8e8, &recomp_gen::fn_sub_59D8E8_0059d8e8__recomp},
    {"sub_59D938", 0x59D938, &recomp_gen::fn_sub_59D938_0059d938, &recomp_gen::fn_sub_59D938_0059d938__recomp},
    {"sub_59D988", 0x59D988, &recomp_gen::fn_sub_59D988_0059d988, &recomp_gen::fn_sub_59D988_0059d988__recomp},
    {"sub_59D9E8", 0x59D9E8, &recomp_gen::fn_sub_59D9E8_0059d9e8, &recomp_gen::fn_sub_59D9E8_0059d9e8__recomp},
    {"sub_59DA70", 0x59DA70, &recomp_gen::fn_sub_59DA70_0059da70, &recomp_gen::fn_sub_59DA70_0059da70__recomp},
    {"sub_59DAC0", 0x59DAC0, &recomp_gen::fn_sub_59DAC0_0059dac0, &recomp_gen::fn_sub_59DAC0_0059dac0__recomp},
    {"sub_59DB10", 0x59DB10, &recomp_gen::fn_sub_59DB10_0059db10, &recomp_gen::fn_sub_59DB10_0059db10__recomp},
    {"sub_59DB60", 0x59DB60, &recomp_gen::fn_sub_59DB60_0059db60, &recomp_gen::fn_sub_59DB60_0059db60__recomp},
    {"sub_59DBB0", 0x59DBB0, &recomp_gen::fn_sub_59DBB0_0059dbb0, &recomp_gen::fn_sub_59DBB0_0059dbb0__recomp},
    {"sub_59DC18", 0x59DC18, &recomp_gen::fn_sub_59DC18_0059dc18, &recomp_gen::fn_sub_59DC18_0059dc18__recomp},
    {"sub_59DC68", 0x59DC68, &recomp_gen::fn_sub_59DC68_0059dc68, &recomp_gen::fn_sub_59DC68_0059dc68__recomp},
    {"sub_59DCB8", 0x59DCB8, &recomp_gen::fn_sub_59DCB8_0059dcb8, &recomp_gen::fn_sub_59DCB8_0059dcb8__recomp},
    {"sub_59DD08", 0x59DD08, &recomp_gen::fn_sub_59DD08_0059dd08, &recomp_gen::fn_sub_59DD08_0059dd08__recomp},
    {"sub_59DD40", 0x59DD40, &recomp_gen::fn_sub_59DD40_0059dd40, &recomp_gen::fn_sub_59DD40_0059dd40__recomp},
    {"sub_59DD78", 0x59DD78, &recomp_gen::fn_sub_59DD78_0059dd78, &recomp_gen::fn_sub_59DD78_0059dd78__recomp},
    {"sub_59DDF0", 0x59DDF0, &recomp_gen::fn_sub_59DDF0_0059ddf0, &recomp_gen::fn_sub_59DDF0_0059ddf0__recomp},
    {"sub_59DE68", 0x59DE68, &recomp_gen::fn_sub_59DE68_0059de68, &recomp_gen::fn_sub_59DE68_0059de68__recomp},
    {"sub_59DEC0", 0x59DEC0, &recomp_gen::fn_sub_59DEC0_0059dec0, &recomp_gen::fn_sub_59DEC0_0059dec0__recomp},
    {"sub_59DF30", 0x59DF30, &recomp_gen::fn_sub_59DF30_0059df30, &recomp_gen::fn_sub_59DF30_0059df30__recomp},
    {"sub_59DFB0", 0x59DFB0, &recomp_gen::fn_sub_59DFB0_0059dfb0, &recomp_gen::fn_sub_59DFB0_0059dfb0__recomp},
    {"sub_59E020", 0x59E020, &recomp_gen::fn_sub_59E020_0059e020, &recomp_gen::fn_sub_59E020_0059e020__recomp},
    {"sub_59E090", 0x59E090, &recomp_gen::fn_sub_59E090_0059e090, &recomp_gen::fn_sub_59E090_0059e090__recomp},
    {"sub_59E100", 0x59E100, &recomp_gen::fn_sub_59E100_0059e100, &recomp_gen::fn_sub_59E100_0059e100__recomp},
    {"sub_59E178", 0x59E178, &recomp_gen::fn_sub_59E178_0059e178, &recomp_gen::fn_sub_59E178_0059e178__recomp},
    {"sub_59E228", 0x59E228, &recomp_gen::fn_sub_59E228_0059e228, &recomp_gen::fn_sub_59E228_0059e228__recomp},
    {"sub_59E298", 0x59E298, &recomp_gen::fn_sub_59E298_0059e298, &recomp_gen::fn_sub_59E298_0059e298__recomp},
    {"sub_59E308", 0x59E308, &recomp_gen::fn_sub_59E308_0059e308, &recomp_gen::fn_sub_59E308_0059e308__recomp},
    {"sub_59E378", 0x59E378, &recomp_gen::fn_sub_59E378_0059e378, &recomp_gen::fn_sub_59E378_0059e378__recomp},
    {"sub_59E3E8", 0x59E3E8, &recomp_gen::fn_sub_59E3E8_0059e3e8, &recomp_gen::fn_sub_59E3E8_0059e3e8__recomp},
    {"sub_59E460", 0x59E460, &recomp_gen::fn_sub_59E460_0059e460, &recomp_gen::fn_sub_59E460_0059e460__recomp},
    {"sub_59E4D0", 0x59E4D0, &recomp_gen::fn_sub_59E4D0_0059e4d0, &recomp_gen::fn_sub_59E4D0_0059e4d0__recomp},
    {"sub_59E558", 0x59E558, &recomp_gen::fn_sub_59E558_0059e558, &recomp_gen::fn_sub_59E558_0059e558__recomp},
    {"sub_59E5E0", 0x59E5E0, &recomp_gen::fn_sub_59E5E0_0059e5e0, &recomp_gen::fn_sub_59E5E0_0059e5e0__recomp},
    {"sub_59E670", 0x59E670, &recomp_gen::fn_sub_59E670_0059e670, &recomp_gen::fn_sub_59E670_0059e670__recomp},
    {"sub_59E6E0", 0x59E6E0, &recomp_gen::fn_sub_59E6E0_0059e6e0, &recomp_gen::fn_sub_59E6E0_0059e6e0__recomp},
    {"sub_59E720", 0x59E720, &recomp_gen::fn_sub_59E720_0059e720, &recomp_gen::fn_sub_59E720_0059e720__recomp},
    {"sub_59E760", 0x59E760, &recomp_gen::fn_sub_59E760_0059e760, &recomp_gen::fn_sub_59E760_0059e760__recomp},
    {"sub_59E7A8", 0x59E7A8, &recomp_gen::fn_sub_59E7A8_0059e7a8, &recomp_gen::fn_sub_59E7A8_0059e7a8__recomp},
    {"sub_59E800", 0x59E800, &recomp_gen::fn_sub_59E800_0059e800, &recomp_gen::fn_sub_59E800_0059e800__recomp},
    {"sub_59E808", 0x59E808, &recomp_gen::fn_sub_59E808_0059e808, &recomp_gen::fn_sub_59E808_0059e808__recomp},
    {"sub_59E860", 0x59E860, &recomp_gen::fn_sub_59E860_0059e860, &recomp_gen::fn_sub_59E860_0059e860__recomp},
    {"sub_59E8B0", 0x59E8B0, &recomp_gen::fn_sub_59E8B0_0059e8b0, &recomp_gen::fn_sub_59E8B0_0059e8b0__recomp},
    {"sub_59E8F0", 0x59E8F0, &recomp_gen::fn_sub_59E8F0_0059e8f0, &recomp_gen::fn_sub_59E8F0_0059e8f0__recomp},
    {"sceLibgcc32GetErxEntries_23", 0x5A1158, &recomp_gen::fn_sceLibgcc32GetErxEntries_23_005a1158, &recomp_gen::fn_sceLibgcc32GetErxEntries_23_005a1158__recomp},
    {"sub_5A1218", 0x5A1218, &recomp_gen::fn_sub_5A1218_005a1218, &recomp_gen::fn_sub_5A1218_005a1218__recomp},
    {"sub_5A12F8", 0x5A12F8, &recomp_gen::fn_sub_5A12F8_005a12f8, &recomp_gen::fn_sub_5A12F8_005a12f8__recomp},
    {"sub_5A1790", 0x5A1790, &recomp_gen::fn_sub_5A1790_005a1790, &recomp_gen::fn_sub_5A1790_005a1790__recomp},
    {"sub_5A1858", 0x5A1858, &recomp_gen::fn_sub_5A1858_005a1858, &recomp_gen::fn_sub_5A1858_005a1858__recomp},
    {"sub_5A1B58", 0x5A1B58, &recomp_gen::fn_sub_5A1B58_005a1b58, &recomp_gen::fn_sub_5A1B58_005a1b58__recomp},
    {"sub_5A1B68", 0x5A1B68, &recomp_gen::fn_sub_5A1B68_005a1b68, &recomp_gen::fn_sub_5A1B68_005a1b68__recomp},
    {"sub_5A1B80", 0x5A1B80, &recomp_gen::fn_sub_5A1B80_005a1b80, &recomp_gen::fn_sub_5A1B80_005a1b80__recomp},
    {"sub_5A1C08", 0x5A1C08, &recomp_gen::fn_sub_5A1C08_005a1c08, &recomp_gen::fn_sub_5A1C08_005a1c08__recomp},
    {"sub_5A1CE0", 0x5A1CE0, &recomp_gen::fn_sub_5A1CE0_005a1ce0, &recomp_gen::fn_sub_5A1CE0_005a1ce0__recomp},
};

// The random world of the generic sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// The meaningful worlds: free RAM far above .bss and below the stand-in heap (0x1C00000).
constexpr u32 kView = 0x01900000u;    // an SFH view (16 bytes)
constexpr u32 kOut = 0x01900100u;     // outputs of the getters (words / strings)
constexpr u32 kHdr = 0x01901000u;     // one header sector (2,048 bytes)
constexpr u32 kInfo = 0x01902000u;    // an SFD header-info record (148 + 2,048 bytes)
constexpr u32 kBuf = 0x01910000u;     // byte buffers (start codes, tags, movie data): 256 KiB
constexpr u32 kHandle = 0x01950000u;  // a fake SFD handle (0x37B0 bytes) and a second one
constexpr u32 kHandle2 = 0x01954000u;
constexpr u32 kMpsWork = 0x01958000u; // a fake MPS work block (16 + 8 * 256 bytes)
constexpr u32 kMpv = 0x0195A000u;     // a fake MPV handle (1,024 bytes)
constexpr u32 kPlayer = 0x0195B000u;  // a fake MWSFD player (512 bytes)
constexpr u32 kMarker = 0x0195C000u;  // the argument of the error callback (cleared by it)
constexpr u32 kCallback = 0x59D1B0u;  // sub_59D1B0 (sfhClearView) as an error callback: clears 16 bytes at its argument

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}
std::map<std::string, int> g_pairs;  // pairs per function, per section
// One hand / recompiled pair of `fn` (both from the same state; the recompiled run's memory stays in place). $t0..$t3 =
// arguments 5..8.
hgp::Run pair_fn(Machine& m, const char* fn, Args a, u32 seed, std::vector<u64> more = {}) {
    const Case& c = find_case(fn);
    HwCheck hw;
    for (std::size_t i = 0; i < more.size(); ++i) hw.gpr_in[GPR_T0 + static_cast<unsigned>(i)] = more[i];
    ++g_pairs[fn];
    return hgp::pair(m, c.hand, c.recomp, a, seed, fn, hw);
}
u32 v0_of(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
s32 sv0(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }
u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
s32 gs32(Machine& m, u32 va) { return static_cast<s32>(g32(m, va)); }
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u64 g64(Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.at(va), 8);
    return v;
}
void report(const char* section) {
    int total = 0;
    for (const auto& kv : g_pairs) total += kv.second;
    const std::string line = std::string(section) + ": " + std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
    MESSAGE(line);
    g_pairs.clear();
}
std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}

// --- the Sofdec headers of the disc ------------------------------------------------------------------------------------
std::string sfd_dir() { return extracted_root() + "/DATA/SFD"; }
struct SfdFile {
    std::string name;
    std::vector<u8> head;  // the first 64 KiB
};
std::vector<SfdFile> sfd_files() {
    std::vector<SfdFile> out;
    std::error_code ec;
    for (const auto& e : std::filesystem::directory_iterator(sfd_dir(), ec)) {
        if (!e.is_regular_file()) continue;
        std::ifstream f(e.path(), std::ios::binary);
        SfdFile s{e.path().filename().string(), std::vector<u8>(64 * 1024)};
        f.read(reinterpret_cast<char*>(s.head.data()), static_cast<std::streamsize>(s.head.size()));
        s.head.resize(static_cast<std::size_t>(f.gcount()));
        out.push_back(std::move(s));
    }
    std::sort(out.begin(), out.end(), [](const SfdFile& a, const SfdFile& b) { return a.name < b.name; });
    return out;
}
// The header sector: the 2,048-byte pack whose bytes +32.. are "SofdecStream" (sector 2 in every SFD on the disc).
std::size_t header_sector(const std::vector<u8>& f) {
    for (std::size_t s = 0; s + 2048 <= f.size(); s += 2048)
        if (std::memcmp(f.data() + s + 32, "SofdecStream", 12) == 0) return s;
    return std::string::npos;
}

// The header as the format lays it out (read on the host from the bytes; tail1::sfh).
struct HostHdr {
    const u8* h;
    u32 le32(u32 off) const { return u32(h[off]) | u32(h[off + 1]) << 8 | u32(h[off + 2]) << 16 | u32(h[off + 3]) << 24; }
    s32 version() const { return 100 * h[56] + h[57]; }
    const u8* stream(u32 id) const {
        for (u32 e = 0; e < 26; ++e)
            if (h[384 + 64 * e + 24] == id) return h + 384 + 64 * e;
        return nullptr;
    }
};
// ISO/IEC 13818-2 table 6-4, x 1,000.
u32 frame_rate_x1000(s32 code) {
    static const u32 t[] = {0, 23976, 24000, 25000, 29970, 30000, 50000, 59940, 60000};
    return code >= 1 && code <= 8 ? t[code] : 0;
}
// ISO/IEC 13818-1 table 2-18 as the SFH classifier groups it.
u32 stream_class(u32 id) {
    if (id >= 0xC0 && id <= 0xDF) return 0xC0;
    if (id >= 0xE0 && id <= 0xEF) return 0xE0;
    if (id == 0xBD || id == 0xBF) return 0xBD;
    return 0;
}

std::string lower12(const u8* p) {
    std::string s(reinterpret_cast<const char*>(p), 12);
    for (char& ch : s) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    return s;
}

void load_view(Machine& m, const u8* sector, u32 size, s32 state = 1) {
    std::memcpy(m.at(kHdr), sector, 2048);
    p32(m, kView + 0, static_cast<u32>(state));
    p32(m, kView + 4, kHdr);
    p32(m, kView + 8, size);
    p32(m, kView + 12, 0);
}

// --- MPEG start codes ------------------------------------------------------------------------------------------------
// ISO/IEC 13818-2 table 6-1, as sub_577FC8 maps it to its class bits (tail1::sc).
u32 start_code_class(u32 code) {
    if (code == 0x100) return 4;
    if (code == 0x101) return 3;
    if (code >= 0x102 && code <= 0x1AF) return 1;
    switch (code) {
    case 0x1B2: return 32;
    case 0x1B3: return 64;
    case 0x1B5: return 16;
    case 0x1B7: return 128;
    case 0x1B8: return 8;
    default: return 0;
    }
}
// The forward scan as the binary does it (a four-state machine over the bytes; a rejected code restarts the machine
// after its fourth byte, so a code that starts inside that byte is not seen).
u32 host_scan_forward(const std::vector<u8>& b, u32 base, u32 len, u32 mask) {
    u32 state = 0;
    for (u32 i = 0; i < len; ++i) {
        const u8 c = b[i];
        if (state == 1) state = c == 0 ? 2 : 0;
        else if (state == 0) state = c == 0 ? 1 : 0;
        else if (state == 2) state = c == 1 ? 3 : (c == 0 ? 2 : 0);
        else {
            const u32 at = i - 3;
            const u32 code = u32(b[at]) << 24 | u32(b[at + 1]) << 16 | u32(b[at + 2]) << 8 | b[at + 3];
            if (start_code_class(code) & mask) return base + at;
            state = 0;
        }
    }
    return 0;
}

// --- the stand-in stream object of sub_579660 ---------------------------------------------------------------------------
constexpr u32 kGetChunk = 0x5A1868u;    // two function starts this build does not emit (served by stand-ins)
constexpr u32 kUngetChunk = 0x5A19C0u;

}  // namespace

// ======================================================================================================================
// 1. Every body against its recompiled body on random worlds (mostly bad-input paths).
TEST_CASE("game(tail1): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    u32 pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            args[0] = hgp::random_arg(rng, kWorld, kWorldSize);
            args[1] = hgp::random_arg(rng, kWorld, kWorldSize);
            args[2] = hgp::random_arg(rng, kWorld, kWorldSize);
            args[3] = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("generic sweep: " << pairs << " pairs, " << stops << " stopped early (identically)");
}

// ======================================================================================================================
// 2. SFH on the Sofdec headers of the disc's 41 movies, then on edited copies (version gates, bad headers).
TEST_CASE("game(tail1): the SFH header parser reads every field the Sofdec header holds") {
    auto m = machine();
    if (!m) return;
    const std::vector<SfdFile> files = sfd_files();
    if (files.empty()) {
        MESSAGE("SKIP: no movies under " << sfd_dir());
        return;
    }
    u32 seed = 1, headers = 0;
    for (const SfdFile& f : files) {
        const std::size_t s = header_sector(f.head);
        REQUIRE(s != std::string::npos);
        CHECK(s == 4096);  // every movie of the disc: pack 0 and 1, then the header
        const u8* sec = f.head.data() + s;
        const HostHdr hh{sec};
        ++headers;
        // parse: a Sofdec header -> state 2, version 100 * major + minor, ok = 1
        load_view(*m, sec, 2048);
        p32(*m, kOut, 0xDEAD);
        hgp::Run r = pair_fn(*m, "sub_59D2B0", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == 1);
        CHECK(g32(*m, kOut) == 1);
        CHECK(gs32(*m, kView) == 2);
        CHECK(gs32(*m, kView + 12) == hh.version());
        CHECK(hh.version() == 226);  // 2.26 in every movie; the creator text says Ver.1.74 (the smaller one)
        // the version helper: max(header bytes, the creator text's "Ver.")
        r = pair_fn(*m, "sub_59D6A0", {sx(kView), sx(kOut), sx(kOut + 4), 0}, seed++);
        CHECK(v0_of(r) == 1);
        CHECK(g32(*m, kOut) == 2);
        CHECK(g32(*m, kOut + 4) == 26);
        // the creator text and its "Ver.1.74"
        std::memset(m->at(kOut), 0x55, 128);
        pair_fn(*m, "sub_59D608", {sx(kView), sx(kOut), 0, 0}, seed++);
        const std::string creator = m->str(kOut, 64);
        CHECK(creator == std::string(reinterpret_cast<const char*>(sec + 96), std::min<std::size_t>(32, std::strlen(reinterpret_cast<const char*>(sec + 96)))));
        CHECK(m->at(kOut)[32] == 0);
        m->put(kBuf, creator);
        r = pair_fn(*m, "sub_59D988", {sx(kBuf), sx(kOut + 64), sx(kOut + 68), 0}, seed++);
        CHECK(v0_of(r) == 1);
        CHECK(g32(*m, kOut + 64) == 1);
        CHECK(g32(*m, kOut + 68) == 74);
        // the three texts: the file's 8.3 name (+64), its date "yyyymmddhhmm" (+76), +224
        const char* texts[] = {"sub_59D528", "sub_59D598", "sub_59D770"};
        const u32 toff[] = {64, 76, 224}, tlen[] = {12, 12, 64};
        for (int t = 0; t < 3; ++t) {
            std::memset(m->at(kOut), 0x55, 128);
            r = pair_fn(*m, texts[t], {sx(kView), sx(kOut), 0, 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(std::memcmp(m->at(kOut), sec + toff[t], tlen[t]) == 0);
            CHECK(m->at(kOut)[tlen[t]] == 0);
        }
        CHECK(lower12(sec + 64).find(".sfd") != std::string::npos);  // an 8.3 name
        // the general and system blocks
        struct Get {
            const char* fn;
            u32 want;
        };
        const Get gets[] = {{"sub_59D848", hh.le32(128)},
                            {"sub_59D898", sec[132]},
                            {"sub_59D8E8", static_cast<u32>(static_cast<s32>(static_cast<s16>(sec[136] | sec[137] << 8)))},
                            {"sub_59D938", hh.le32(140)},
                            {"sub_59DA70", sec[176]},
                            {"sub_59DAC0", sec[177]},
                            {"sub_59DB10", sec[178]},
                            {"sub_59DB60", sec[179]},
                            {"sub_59DBB0", hh.le32(180)},
                            {"sub_59DC18", hh.le32(184)},
                            {"sub_59DC68", hh.le32(188)},
                            {"sub_59DCB8", hh.le32(192)},
                            {"sub_59DD08", hh.le32(196)},
                            {"sub_59DD40", hh.le32(200)}};
        for (const Get& g : gets) {
            p32(*m, kOut, 0xDEADBEEFu);
            r = pair_fn(*m, g.fn, {sx(kView), sx(kOut), 0, 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(g32(*m, kOut) == g.want);
        }
        CHECK(hh.le32(128) == 2048);
        // the stream table: 0xBF, 0xC0 and 0xE0 are listed, 0xE1 / 0xC1 / 0xBD are not
        for (u32 id : {0xBFu, 0xC0u, 0xE0u, 0xE1u, 0xC1u, 0xBDu}) {
            p32(*m, kOut, 0xDEAD);
            r = pair_fn(*m, "sub_59D3A0", {sx(kView), id, sx(kOut), 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(g32(*m, kOut) == (hh.stream(id) ? 1u : 0u));
            r = pair_fn(*m, "sub_59DE68", {sx(kView), id, 0, 0}, seed++);
            const u8* e = hh.stream(id);
            CHECK(v0_of(r) == (e ? kHdr + static_cast<u32>(e - sec) : 0u));
        }
        // audio stream 0xC0: 2 channels, 48,000 Hz in every movie (bytes +27, word +28)
        const u8* au = hh.stream(0xC0);
        REQUIRE(au);
        const Get aget[] = {{"sub_59DEC0", au[25]}, {"sub_59DFB0", au[27]}, {"sub_59E020", HostHdr{au}.le32(28)}};
        for (const Get& g : aget) {
            r = pair_fn(*m, g.fn, {sx(kView), 0xC0, sx(kOut), 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(g32(*m, kOut) == g.want);
        }
        CHECK(au[27] == 2);
        CHECK(HostHdr{au}.le32(28) == 48000);
        r = pair_fn(*m, "sub_59DF30", {sx(kView), 0xC0, sx(kOut), 0}, seed++);  // byte +26 only when +25 is 1
        CHECK(v0_of(r) == (au[25] == 1 ? 1u : 0u));
        // video stream 0xE0: the picture size as the MPEG sequence header packs it, the frame rate, the flags
        const u8* vi = hh.stream(0xE0);
        REQUIRE(vi);
        r = pair_fn(*m, "sub_59E178", {sx(kView), 0xE0, sx(kOut), sx(kOut + 4)}, seed++);
        CHECK(v0_of(r) == 1);
        const u32 w = g32(*m, kOut), h = g32(*m, kOut + 4);
        CHECK(w == (u32(vi[28]) << 4 | vi[29] >> 4));
        CHECK(h == ((u32(vi[29]) << 8 | vi[30]) & 0xFFF));
        CHECK(w == 640);
        CHECK((h == 448 || h == 368));
        r = pair_fn(*m, "sub_59E228", {sx(kView), 0xE0, sx(kOut), 0}, seed++);
        CHECK(g32(*m, kOut) == frame_rate_x1000(vi[31]));
        CHECK(g32(*m, kOut) == 29970);  // NTSC
        const u16 h26 = static_cast<u16>(vi[26] | vi[27] << 8);
        const Get vget[] = {{"sub_59E090", vi[25]},          {"sub_59E100", h26 == 0xFFFF ? 0u : h26},
                            {"sub_59E298", vi[33]},          {"sub_59E308", vi[34]},
                            {"sub_59E378", vi[35] & 1u},     {"sub_59E3E8", (vi[35] & 0x10) ? 1u : 0u},
                            {"sub_59E460", vi[36]},          {"sub_59E4D0", vi[37] < 64 ? vi[37] : 0xFFFFFFFFu},
                            {"sub_59E558", vi[38] < 64 ? vi[38] : 0xFFFFFFFFu}, {"sub_59E5E0", vi[39]},
                            {"sub_59D410", vi[32] == 1 ? 1u : 0u}};
        for (const Get& g : vget) {
            r = pair_fn(*m, g.fn, {sx(kView), 0xE0, sx(kOut), 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(g32(*m, kOut) == g.want);
        }
        // the audio getters refuse a video id and the video getters an audio id
        r = pair_fn(*m, "sub_59E020", {sx(kView), 0xE0, sx(kOut), 0}, seed++);
        CHECK(v0_of(r) == 0);
        r = pair_fn(*m, "sub_59E178", {sx(kView), 0xC0, sx(kOut), sx(kOut + 4)}, seed++);
        CHECK(v0_of(r) == 0);
        // the two stream texts: the elementary stream's file name and date
        for (const char* fn : {"sub_59DD78", "sub_59DDF0"}) {
            std::memset(m->at(kOut), 0x55, 32);
            r = pair_fn(*m, fn, {sx(kView), 0xE0, sx(kOut), 0}, seed++);
            CHECK(v0_of(r) == 1);
            CHECK(std::memcmp(m->at(kOut), vi + (std::string(fn) == "sub_59DD78" ? 0 : 12), 12) == 0);
        }
        CHECK((lower12(vi).find(".sfv") != std::string::npos || lower12(vi).find(".m2v") != std::string::npos));
        CHECK(lower12(au).find(".sfa") != std::string::npos);
    }
    // edited copies: the version gates (1.07 or >= 1.10 to read at all; >= 1.10, >= 2.10, >= 2.25 for some fields)
    const u8* sec = files[0].head.data() + 4096;
    for (s32 ver : {105, 107, 109, 110, 111, 209, 210, 224, 225, 226, 300}) {
        load_view(*m, sec, 2048, 2);
        p32(*m, kView + 12, static_cast<u32>(ver));
        hgp::Run r = pair_fn(*m, "sub_59D240", {sx(kView), 0, 0, 0}, seed++);
        const bool readable = ver == 107 || ver >= 110;
        CHECK(v0_of(r) == (readable ? 1u : 0u));
        r = pair_fn(*m, "sub_59DBB0", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == (readable && ver >= 110 ? 1u : 0u));
        r = pair_fn(*m, "sub_59DD08", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == (ver >= 225 ? 1u : 0u));  // no readability gate
        r = pair_fn(*m, "sub_59E5E0", {sx(kView), 0xE0, sx(kOut), 0}, seed++);
        CHECK(v0_of(r) == (readable && ver >= 210 ? 1u : 0u));
        r = pair_fn(*m, "sub_59D410", {sx(kView), 0xE0, sx(kOut), 0}, seed++);
        CHECK(v0_of(r) == (readable && ver >= 110 ? 1u : 0u));
    }
    // view states: only state >= 2 (or < -1) is readable
    for (s32 st : {-2, -1, 0, 1, 2, 3}) {
        load_view(*m, sec, 2048, st);
        p32(*m, kView + 12, 226);
        hgp::Run r = pair_fn(*m, "sub_59D288", {sx(kView), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == ((st >= 2 || st < -1) ? 1u : 0u));
        r = pair_fn(*m, "sub_59D230", {sx(kView), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == (st == 0 ? 1u : 0u));
    }
    // bad headers: short, foreign signature, a free view
    {
        std::vector<u8> bad(sec, sec + 2048);
        load_view(*m, bad.data(), 2047);
        hgp::Run r = pair_fn(*m, "sub_59D2B0", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == 0);
        CHECK(gs32(*m, kView) == -1);
        bad[32 + 5] ^= 0x20;
        load_view(*m, bad.data(), 2048);
        r = pair_fn(*m, "sub_59D2B0", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == 0);
        CHECK(gs32(*m, kView) == -1);
        load_view(*m, sec, 2048, 0);
        r = pair_fn(*m, "sub_59D2B0", {sx(kView), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == 0);
        CHECK(gs32(*m, kView) == 0);
    }
    // the decimal reader: digits up to '.', ' ', NUL or any other character
    for (const char* t : {"1.74", "226 ", "12x", "0", ".5", " 7", "", "999999.1", "3"}) {
        m->put(kBuf, t);
        hgp::Run r = pair_fn(*m, "sub_59D9E8", {sx(kBuf), sx(kOut), 0, 0}, seed++);
        const char* p = t;
        u32 v = 0;
        if (*p >= '0' && *p <= '9')
            while (*p >= '0' && *p <= '9') v = v * 10 + static_cast<u32>(*p++ - '0');
        CHECK(g32(*m, kOut) == v);
        CHECK(v0_of(r) == kBuf + static_cast<u32>(p - t));
    }
    // the frame-rate table and the stream-id classes, every input
    for (s32 code = -2; code <= 12; ++code) {
        hgp::Run r = pair_fn(*m, "sub_59E670", {sx(static_cast<u32>(code)), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == frame_rate_x1000(code));
    }
    for (u32 id = 0; id < 0x100; id += 1) {
        hgp::Run r = pair_fn(*m, "sub_59E760", {id, 0, 0, 0}, seed++);
        CHECK(v0_of(r) == stream_class(id));
    }
    MESSAGE(headers << " headers");
    report("SFH");
}

// ======================================================================================================================
// 3. The SFH view pool and SFD's header-info builder on the real headers.
TEST_CASE("game(tail1): SFD builds the header-info record from the Sofdec header") {
    auto m = machine();
    if (!m) return;
    const std::vector<SfdFile> files = sfd_files();
    if (files.empty()) {
        MESSAGE("SKIP: no movies under " << sfd_dir());
        return;
    }
    u32 seed = 100;
    // SFH init through SFD (32 views at 0x9A7F90): the pool, the banner; a second init only counts
    hgp::Run r = pair_fn(*m, "sub_58B108", {0, 0, 0, 0}, seed++);
    CHECK(g32(*m, tail1::sfh::kPoolUsers) == 1);
    CHECK(g32(*m, tail1::sfh::kPool + 0) == 32);
    CHECK(g32(*m, tail1::sfh::kPool + 4) == 0);
    CHECK(g32(*m, tail1::sfh::kPool + 8) == tail1::sfh::kViewArray);
    CHECK(m->str(g32(*m, tail1::sfh::kPoolBanner)).find("CRI SFH/PS2EE Ver.1.19") != std::string::npos);
    pair_fn(*m, "sub_59CFC0", {4, sx(kBuf), 0, 0}, seed++);
    CHECK(g32(*m, tail1::sfh::kPoolUsers) == 1);  // only the first init counts (the increment sits inside the test)
    CHECK(g32(*m, tail1::sfh::kPool + 0) == 32);  // unchanged
    // views: take 32, the 33rd fails, release one, take it again
    std::vector<u32> views;
    for (int i = 0; i < 33; ++i) {
        r = pair_fn(*m, "sub_59D098", {sx(kHdr), 2048, 0, 0}, seed++);
        views.push_back(v0_of(r));
    }
    for (int i = 0; i < 32; ++i) {
        CHECK(views[i] == tail1::sfh::kViewArray + 16u * static_cast<u32>(i));
        CHECK(g32(*m, views[i]) == 1);
        CHECK(g32(*m, views[i] + 4) == kHdr);
    }
    CHECK(views[32] == 0);
    pair_fn(*m, "sub_59D160", {sx(views[7]), 0, 0, 0}, seed++);
    CHECK(g32(*m, tail1::sfh::kPool + 4) == 31);
    r = pair_fn(*m, "sub_59D098", {sx(kHdr), 2048, 0, 0}, seed++);
    CHECK(v0_of(r) == views[7]);
    for (u32 v : views)
        if (v) pair_fn(*m, "sub_59D160", {sx(v), 0, 0, 0}, seed++);
    CHECK(g32(*m, tail1::sfh::kPool + 4) == 0);
    for (const SfdFile& f : files) {
        const u8* sec = f.head.data() + 4096;
        const HostHdr hh{sec};
        // is it a Sofdec header? (a view taken and released around the parse)
        std::memcpy(m->at(kHdr), sec, 2048);
        r = pair_fn(*m, "sub_58B278", {sx(kHdr), 2048, 0, 0}, seed++);
        CHECK(v0_of(r) == 1);
        r = pair_fn(*m, "sub_58B278", {sx(kHdr), 1024, 0, 0}, seed++);
        CHECK(v0_of(r) == 0);
        // the info record from the header copy at +148
        std::memset(m->at(kInfo), 0xA5, 148);
        std::memcpy(m->at(kInfo + 148), sec, 2048);
        p32(*m, kInfo + 144, 2048);
        pair_fn(*m, "sub_58B560", {sx(kInfo), 0, 0, 0}, seed++);
        namespace si = tail1::sfdinfo;
        CHECK(g32(*m, kInfo + si::kValid) == 1);
        CHECK(g32(*m, kInfo + si::kMajor) == 2);
        CHECK(g32(*m, kInfo + si::kMinor) == 26);
        CHECK(g32(*m, kInfo + si::kSysWord4) == hh.le32(180));  // version >= 1.10: not negated
        CHECK(g32(*m, kInfo + si::kGeneral + 0) == hh.le32(128));
        CHECK(g32(*m, kInfo + si::kGeneral + 4) == sec[132]);
        CHECK(g32(*m, kInfo + si::kGeneral + 12) == hh.le32(140));
        for (u32 k = 0; k < 4; ++k) CHECK(g32(*m, kInfo + si::kSystem + 4 * k) == sec[176 + k]);
        CHECK(g32(*m, kInfo + si::kSystem + 16) == hh.le32(184));
        CHECK(g32(*m, kInfo + si::kFirstPrivate1) == 0);     // no 0xBD stream
        CHECK(g32(*m, kInfo + si::kFirstPrivate2) == 0xBF);
        CHECK(g32(*m, kInfo + si::kFirstAudio) == 0xC0);
        CHECK(g32(*m, kInfo + si::kFirstVideo) == 0xE0);
        CHECK(g32(*m, kInfo + si::kAudio + 8) == 2);         // channels
        CHECK(g32(*m, kInfo + si::kAudio + 12) == 48000);    // Hz
        CHECK(g32(*m, kInfo + si::kVideo + 8) == 640);
        CHECK(g32(*m, kInfo + si::kVideo + 16) == 29970);
        CHECK(g32(*m, kInfo + si::kVideo + 20) == 1);        // the entry flag (kind byte +32 == 1)
        // the handle-level readers over the same record
        std::memset(m->at(kHandle), 0, 0x400);
        std::memcpy(m->at(kHandle + 120), m->at(kInfo), 148);
        r = pair_fn(*m, "sub_58BBB0", {sx(kHandle), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == 226);
        r = pair_fn(*m, "sub_58BBE8", {sx(kHandle), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == g32(*m, kInfo + si::kVideo + 24));
        // the first-stream finder over the class ranges
        r = pair_fn(*m, "sub_59D098", {sx(kInfo + 148), 2048, 0, 0}, seed++);
        const u32 view = v0_of(r);
        pair_fn(*m, "sub_59D2B0", {sx(view), sx(kOut), 0, 0}, seed++);
        for (auto [lo, hi, want] : {std::tuple<u32, u32, u32>{0xC0, 0xDF, 0xC0}, {0xE0, 0xEF, 0xE0}, {0xBD, 0xBD, 0}, {0xE1, 0xEF, 0}, {0xEF, 0xE0, 0}}) {
            r = pair_fn(*m, "sub_58B868", {sx(view), lo, hi, 0}, seed++);
            CHECK(v0_of(r) == want);
        }
        pair_fn(*m, "sub_59D160", {sx(view), 0, 0, 0}, seed++);
    }
    // the start code of a private_stream_2 packet and the big-endian reader
    const u8* pk = files[0].head.data() + 4096 + 12;  // the header packet's start code 00 00 01 BF
    std::memcpy(m->at(kBuf), pk, 4);
    r = pair_fn(*m, "sub_58B220", {sx(kBuf), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 1);
    r = pair_fn(*m, "sub_58B248", {sx(kBuf), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0x1BF);
    m->at(kBuf)[3] = 0xBE;
    r = pair_fn(*m, "sub_58B220", {sx(kBuf), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    r = pair_fn(*m, "sub_58BC20", {0, 0x37B0, 0, 0}, seed++);
    CHECK(v0_of(r) == 1);
    r = pair_fn(*m, "sub_58BC20", {0, 0x37AF, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    // finish: the count drops to 0 and the pool is cleared; a second finish goes below 0 and clears again
    pair_fn(*m, "sub_58B128", {0, 0, 0, 0}, seed++);
    CHECK(g32(*m, tail1::sfh::kPoolUsers) == 0);
    CHECK(g32(*m, tail1::sfh::kPool) == 0);
    CHECK(g32(*m, tail1::sfh::kPool + 8) == 0);
    pair_fn(*m, "sub_59D050", {0, 0, 0, 0}, seed++);
    CHECK(gs32(*m, tail1::sfh::kPoolUsers) == -1);
    r = pair_fn(*m, "sub_59CFC0", {32, sx(tail1::sfh::kViewArray), 0, 0}, seed++);  // init again from -1
    CHECK(g32(*m, tail1::sfh::kPoolUsers) == 0);
    CHECK(g32(*m, tail1::sfh::kPool) == 32);
    report("SFD header info");
}

// ======================================================================================================================
// 4. MPEG start codes: the classifier on every code, the scanners on random buffers and on the movies' video data, the
//    MPEG-1 / MPEG-2 decision.
TEST_CASE("game(tail1): the MPEG start-code helpers follow ISO/IEC 13818-2") {
    auto m = machine();
    if (!m) return;
    u32 seed = 200;
    for (u32 code = 0xF0; code < 0x210; ++code) {
        const u8 b[4] = {static_cast<u8>(code >> 24), static_cast<u8>(code >> 16), static_cast<u8>(code >> 8), static_cast<u8>(code)};
        std::memcpy(m->at(kBuf), b, 4);
        hgp::Run r = pair_fn(*m, "sub_577FC8", {sx(kBuf), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == start_code_class(code));
    }
    std::mt19937 rng{0x5A1D0001u};
    for (int round = 0; round < 48; ++round) {
        const u32 len = 16 + rng() % 600;
        std::vector<u8> b(len + 8);
        for (u8& c : b) {
            const u32 k = rng() % 4;
            c = k == 0 ? 0 : static_cast<u8>(rng());
        }
        const int plants = static_cast<int>(rng() % 4);
        for (int i = 0; i < plants; ++i) {
            const u32 at = rng() % (len - 4);
            static const u8 codes[] = {0x00, 0x01, 0x20, 0xAF, 0xB2, 0xB3, 0xB5, 0xB7, 0xB8, 0xB9, 0xBA};
            const u8 xx = codes[rng() % std::size(codes)];
            b[at] = 0;
            b[at + 1] = 0;
            b[at + 2] = 1;
            b[at + 3] = xx;
        }
        std::memcpy(m->at(kBuf), b.data(), b.size());
        static const u32 masks[] = {0xFFFFFFFFu, 64, 4, 0xCC, 16, 1, 0};
        const u32 mask = masks[rng() % std::size(masks)];
        hgp::Run r = pair_fn(*m, "sub_578160", {sx(kBuf), len, mask, 0}, seed++);
        CHECK(v0_of(r) == host_scan_forward(b, kBuf, len, mask));
        // backwards: a hit is a "00 00 01" whose class matches, inside the searched range
        r = pair_fn(*m, "sub_578060", {sx(kBuf + len), len, mask, 0}, seed++);
        const u32 hit = v0_of(r);
        if (hit) {
            const u32 at = hit - kBuf;
            CHECK(at < len);
            CHECK(b[at] == 0);
            CHECK(b[at + 1] == 0);
            CHECK(b[at + 2] == 1);
            CHECK((start_code_class(0x100u | b[at + 3]) & mask) != 0);
        }
    }
    // the movies' video: 38 are MPEG-1 (a sequence header followed by user data), 3 MPEG-2 (a sequence_extension after it)
    const std::vector<SfdFile> files = sfd_files();
    int movies = 0, m2v = 0;
    for (const SfdFile& f : files) {
        const u8* d = f.head.data();
        std::size_t seq = std::string::npos;
        for (std::size_t i = 0; i + 4 < f.head.size(); ++i)
            if (d[i] == 0 && d[i + 1] == 0 && d[i + 2] == 1 && d[i + 3] == 0xB3) {
                seq = i;
                break;
            }
        if (seq == std::string::npos || seq < 16 || seq + 2048 > f.head.size()) continue;
        ++movies;
        const u32 n = 2048;
        std::memcpy(m->at(kBuf), d + seq - 16, n);
        hgp::Run r = pair_fn(*m, "sub_578160", {sx(kBuf), n, 64, 0}, seed++);
        CHECK(v0_of(r) == kBuf + 16);
        // the decision: sequence header, then an extension start code -> 2
        std::memset(m->at(kMpv), 0, 1024);
        p32(*m, kOut, kBuf);
        p32(*m, kOut + 4, n);
        r = pair_fn(*m, "sub_579770", {sx(kMpv), sx(kOut), 0, 0}, seed++);
        bool ext = false;
        for (u32 i = 16 + 4; i + 4 < n; ++i)
            if (d[seq - 16 + i] == 0 && d[seq - 16 + i + 1] == 0 && d[seq - 16 + i + 2] == 1) {
                ext = d[seq - 16 + i + 3] == 0xB5;
                break;
            }
        const u32 kind = ext ? 2u : 1u;
        CHECK(v0_of(r) == kind);
        CHECK(g32(*m, kMpv + tail1::mpv::kMpegKind) == kind);
        // the authoring tool names an MPEG-2 elementary stream ".m2v" and an MPEG-1 one ".sfv" (the header's video entry)
        const u8* ve = HostHdr{d + 4096}.stream(0xE0);
        REQUIRE(ve);
        std::string vname(reinterpret_cast<const char*>(ve), 12);
        for (char& ch : vname) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        CHECK((vname.find(".m2v") != std::string::npos) == ext);
        m2v += ext ? 1 : 0;
        r = pair_fn(*m, "sub_579770", {sx(kMpv), sx(kOut), 0, 0}, seed++);  // decided once
        CHECK(v0_of(r) == kind);
        // the other kind: the code after the sequence header swapped (user data <-> extension)
        std::vector<u8> flip(d + seq - 16, d + seq - 16 + n);
        for (u32 i = 20; i + 4 < n; ++i)
            if (flip[i] == 0 && flip[i + 1] == 0 && flip[i + 2] == 1) {
                flip[i + 3] = ext ? 0xB2 : 0xB5;
                break;
            }
        std::memcpy(m->at(kBuf), flip.data(), n);
        std::memset(m->at(kMpv), 0, 1024);
        r = pair_fn(*m, "sub_579770", {sx(kMpv), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == (ext ? 1u : 2u));
        // and a header with nothing after it: undecided (0), and +856 stays 0
        std::memset(m->at(kBuf + 20), 0xFF, n - 20);
        std::memset(m->at(kMpv), 0, 1024);
        r = pair_fn(*m, "sub_579770", {sx(kMpv), sx(kOut), 0, 0}, seed++);
        CHECK(v0_of(r) == 0);
        // picture-level search through the MPV handle (state +392 = 2): offset of the sequence header
        std::memcpy(m->at(kBuf), d + seq - 16, n);
        p32(*m, kMpv + tail1::mpv::kHandleState, 2);
        r = pair_fn(*m, "sub_578FC0", {sx(kMpv), sx(kOut), sx(kOut + 8), 0}, seed++);
        CHECK(v0_of(r) == 0);
        CHECK(g32(*m, kOut + 8) == 16);
    }
    MESSAGE(movies << " movies with video in their first 64 KiB, " << m2v << " of them MPEG-2");
    CHECK(m2v == 3);  // P3CTOP, P3FCT003, STAFF_ROLL_F
    report("start codes");
}

// ======================================================================================================================
// 5. The CRI error records, handle checks and handle pools of MPS, MPV and SFD; SFD's parameter tables.
TEST_CASE("game(tail1): error records, handle pools and parameter tables") {
    auto m = machine();
    if (!m) return;
    u32 seed = 300;
    namespace t = tail1;
    // --- MPS: a work block of four handles
    std::memset(m->at(kMpsWork), 0, 16 + 4 * 256);
    p32(*m, t::mps::kWorkSlot, kMpsWork);
    p32(*m, kMpsWork + t::mps::kWorkCount, 4);
    for (u32 i = 0; i < 4; ++i) p32(*m, kMpsWork + 16 + 256 * i, i == 2 ? 1u : 2u);  // handle 2 free
    hgp::Run r = pair_fn(*m, "sub_577E10", {0, 0, 0, 0}, seed++);
    CHECK(v0_of(r) == kMpsWork + 16 + 2 * 256);
    const u32 h1 = kMpsWork + 16 + 256;
    r = pair_fn(*m, "sub_577DB0", {sx(h1), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    CHECK(g32(*m, 0x99B2B4u) == h1);
    r = pair_fn(*m, "sub_577DB0", {sx(kMpsWork + 16 + 512), 0, 0, 0}, seed++);  // free: not a handle
    CHECK(sv0(r) == -1);
    // the error callback: set, raise (the callback clears the marker), read back
    std::memset(m->at(kMarker), 0x77, 16);
    r = pair_fn(*m, "sub_577C68", {sx(h1), kCallback, sx(kMarker), 0}, seed++);
    CHECK(v0_of(r) == 0);
    CHECK(g32(*m, h1 + 4) == kCallback);
    CHECK(g32(*m, h1 + 8) == kMarker);
    r = pair_fn(*m, "sub_577BE0", {sx(h1), sx(0xFF020999u), 0, 0}, seed++);
    CHECK(v0_of(r) == 0xFF020999u);
    CHECK(g32(*m, h1 + 12) == 0xFF020999u);
    CHECK(g32(*m, kMarker) == 0);  // the callback ran
    std::memset(m->at(kOut), 0, 16);
    pair_fn(*m, "sub_577D10", {sx(h1), sx(kOut), 0, 0}, seed++);
    CHECK(g32(*m, kOut) == kCallback);
    CHECK(g32(*m, kOut + 8) == 0xFF020999u);
    // code 0: stored, no call
    std::memset(m->at(kMarker), 0x77, 16);
    pair_fn(*m, "sub_577BE0", {sx(h1), 0, 0, 0}, seed++);
    CHECK(g32(*m, kMarker) == 0x77777777u);
    // a bad handle raises 0xFF020101 on the global record
    r = pair_fn(*m, "sub_577C68", {sx(kMpsWork + 16 + 512), kCallback, sx(kMarker), 0}, seed++);
    CHECK(v0_of(r) == 0xFF020101u);
    CHECK(g32(*m, kMpsWork + 8) == 0xFF020101u);
    // destroy / finish
    r = pair_fn(*m, "sub_577F78", {sx(h1), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    CHECK(g32(*m, h1) == 1);
    r = pair_fn(*m, "sub_577F78", {sx(h1), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0xFF020103u);
    pair_fn(*m, "sub_577B40", {0, 0, 0, 0}, seed++);
    for (u32 i = 0; i < 4; ++i) CHECK(g32(*m, kMpsWork + 16 + 256 * i) == 1);
    // the record resets
    for (const char* fn : {"sub_577F08", "sub_577F20", "sub_577F48"}) {
        std::memset(m->at(kOut), 0x11, 64);
        r = pair_fn(*m, fn, {sx(kOut), 0, 0, 0}, seed++);
        CHECK(sv0(r) == -1);
        const std::string f = fn;
        const u32 n = f == "sub_577F08" ? 16 : f == "sub_577F20" ? 32 : 40;
        for (u32 i = 0; i < n; ++i) CHECK(m->at(kOut)[i] == 0xFF);
        CHECK(m->at(kOut)[n] == 0x11);
    }
    // --- MPV: one handle (state 2 at +392)
    std::memset(m->at(kMpv), 0, 1024);
    p32(*m, kMpv + t::mpv::kHandleState, 2);
    r = pair_fn(*m, "sub_57B7F0", {sx(kMpv), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    std::memset(m->at(kMarker), 0x77, 16);
    pair_fn(*m, "sub_578D98", {sx(kMpv), kCallback, sx(kMarker), 0}, seed++);
    r = pair_fn(*m, "sub_578E88", {sx(kMpv), sx(0xFF030777u), 0, 0}, seed++);
    CHECK(v0_of(r) == 0xFF030777u);
    CHECK(g32(*m, kMarker) == 0);
    pair_fn(*m, "sub_578E08", {sx(kMpv), sx(kOut), 0, 0}, seed++);
    CHECK(g32(*m, kOut + 8) == 0xFF030777u);
    // the figures of a sequence header: vbv size in bytes, bit rate
    for (u32 br : {0x3FFFFu, 0u, 15000u, 0x3FFFEu}) {
        p32(*m, kMpv + t::mpv::kBitRate, br);
        p32(*m, kMpv + t::mpv::kVbvSize, 112);
        p32(*m, kMpv + t::mpv::kWord700, 30);
        r = pair_fn(*m, "sub_5792A0", {sx(kMpv), sx(kOut), sx(kOut + 4), sx(kOut + 8)}, seed++);
        CHECK(v0_of(r) == 0);
        CHECK(g32(*m, kOut) == 112u * 2048u);
        CHECK(g32(*m, kOut + 4) == 30);
        CHECK(gs32(*m, kOut + 8) == (br == 0x3FFFF ? -1 : static_cast<s32>(30 * br / 1800)));
        r = pair_fn(*m, "sub_579240", {sx(kMpv), sx(kOut), 0, 0}, seed++);
        CHECK(g32(*m, kOut) == br);
    }
    for (u32 i = 0; i < 128; ++i) m->at(kMpv + 464 + i)[0] = static_cast<u8>(i * 7);
    pair_fn(*m, "sub_579138", {sx(kMpv), sx(kOut), 0, 0}, seed++);
    CHECK(std::memcmp(m->at(kOut), m->at(kMpv + 464), 128) == 0);
    pair_fn(*m, "sub_579410", {sx(kMpv), 0x1234, 0x5678, 0}, seed++);
    pair_fn(*m, "sub_579428", {sx(kMpv), sx(kOut), sx(kOut + 4), 0}, seed++);
    CHECK(g32(*m, kOut) == 0x1234);
    CHECK(g32(*m, kOut + 4) == 0);
    r = pair_fn(*m, "sub_5793E8", {sx(kMpv), 2, 0xA, 0xB}, seed++, {0xC});
    CHECK(v0_of(r) == 24);
    CHECK(g32(*m, kMpv + 952 + 24 + 8) == 0xC);
    p32(*m, kMpv + t::mpv::kHandleState, 1);  // not valid any more
    r = pair_fn(*m, "sub_579368", {sx(kMpv), sx(kOut), sx(kOut + 4), 0}, seed++);
    CHECK(v0_of(r) == 0xFF03020Eu);
    // --- SFD: two handles in the open-handle table, the parameter tables and their filter
    std::memset(m->at(kHandle), 0, 0x37B0);
    std::memset(m->at(kHandle2), 0, 0x37B0);
    p32(*m, kHandle + t::sfd::kHandleValid, 1);
    p32(*m, kHandle2 + t::sfd::kHandleValid, 1);
    for (u32 i = 0; i < 8; ++i) p32(*m, t::sfd::kHandles + 4 * i, i == 1 ? kHandle : i == 5 ? kHandle2 : 0);
    r = pair_fn(*m, "sub_58C060", {sx(kHandle), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    CHECK(g32(*m, t::sfd::kLastHandle) == kHandle);
    // the filter: (6, 1) needs stream record 3 active, (5, 1) record 2
    for (auto [id, val, rec2, rec3, want] : {std::tuple<u32, u32, u32, u32, u32>{6, 1, 0, 0, 0}, {6, 1, 0, 1, 1}, {5, 1, 0, 1, 0},
                                             {5, 1, 1, 0, 1}, {6, 0, 0, 0, 1}, {7, 1, 0, 0, 1}}) {
        p32(*m, kHandle + t::sfd::kStreamRecs + 68 * 2, rec2);
        p32(*m, kHandle + t::sfd::kStreamRecs + 68 * 3, rec3);
        r = pair_fn(*m, "sub_5992E0", {sx(kHandle), id, val, 0}, seed++);
        CHECK(v0_of(r) == want);
        r = pair_fn(*m, "sub_59BCD0", {sx(kHandle), 3, 0, 0}, seed++);
        CHECK(v0_of(r) == (rec3 ? 1u : 0u));
    }
    // set a parameter on one handle: both tables
    r = pair_fn(*m, "sub_599100", {sx(kHandle), 40, 0x4444, 0}, seed++);
    CHECK(v0_of(r) == 0);
    CHECK(g32(*m, kHandle + t::sfd::kParams + 4 * 40) == 0x4444);
    CHECK(g32(*m, kHandle + t::sfd::kParams2 + 4 * 40) == 0x4444);
    CHECK(g32(*m, kHandle2 + t::sfd::kParams + 4 * 40) == 0);
    // for every handle: the open ones (first table) and the global default
    r = pair_fn(*m, "sub_599100", {0, 41, 0x5555, 0}, seed++);
    CHECK(g32(*m, kHandle + t::sfd::kParams + 4 * 41) == 0x5555);
    CHECK(g32(*m, kHandle2 + t::sfd::kParams + 4 * 41) == 0x5555);
    CHECK(g32(*m, kHandle2 + t::sfd::kParams2 + 4 * 41) == 0);
    CHECK(g32(*m, t::sfd::kWork + 4 * 41) == 0x5555);
    // the error record: set the callback, raise twice (the first code sticks), read back
    std::memset(m->at(kMarker), 0x77, 16);
    pair_fn(*m, "sub_58BEF0", {sx(kHandle), kCallback, sx(kMarker), 0}, seed++);
    r = pair_fn(*m, "sub_58BE40", {sx(kHandle), sx(0xFF000AAAu), 0, 0}, seed++);
    CHECK(v0_of(r) == 0xFF000AAAu);
    CHECK(g32(*m, kMarker) == 0);
    CHECK(gs32(*m, kHandle + t::sfd::kHandleValid) == -1);  // negated
    pair_fn(*m, "sub_58BE40", {sx(kHandle), sx(0xFF000BBBu), 0, 0}, seed++);
    pair_fn(*m, "sub_58BF98", {sx(kHandle), sx(kOut), 0, 0}, seed++);
    CHECK(g32(*m, kOut + 8) == 0xFF000AAAu);
    r = pair_fn(*m, "sub_58BE40", {sx(kHandle), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    // a negative valid word still passes the check (non-zero); zero does not
    r = pair_fn(*m, "sub_58C060", {sx(kHandle), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    p32(*m, kHandle + t::sfd::kHandleValid, 0);
    r = pair_fn(*m, "sub_599100", {sx(kHandle), 3, 3, 0}, seed++);
    CHECK(v0_of(r) == 0xFF000112u);
    // the error-record twins: the MPV copy (sub_578ED8) and the MPS copy (sub_577C30) behave alike on the same record
    for (const char* fn : {"sub_577C30", "sub_578ED8"}) {
        p32(*m, kOut, kCallback);
        p32(*m, kOut + 4, kMarker);
        std::memset(m->at(kMarker), 0x77, 16);
        r = pair_fn(*m, fn, {sx(kOut), 9, 0, 0}, seed++);
        CHECK(g32(*m, kOut + 8) == 9);
        CHECK(g32(*m, kMarker) == 0);
    }
    report("error records / pools / parameters");
}

// ======================================================================================================================
// 6. MWSFD's header ring, fed by the header-sector callback with the movies' headers.
TEST_CASE("game(tail1): the MWSFD header callback fills the player's header ring") {
    auto m = machine();
    if (!m) return;
    const std::vector<SfdFile> files = sfd_files();
    if (files.empty()) {
        MESSAGE("SKIP: no movies under " << sfd_dir());
        return;
    }
    u32 seed = 400;
    namespace w = tail1::mwsfd;
    pair_fn(*m, "sub_58B108", {0, 0, 0, 0}, seed++);  // SFH views
    std::memset(m->at(kPlayer), 0x5A, 512);
    pair_fn(*m, "sub_57F328", {sx(kPlayer), 0, 0, 0}, seed++);
    CHECK(g32(*m, kPlayer + w::kHdrCount) == 0);
    for (u32 e = 0; e < 8; ++e) {
        CHECK(g32(*m, kPlayer + w::kRing + 20 * e) == 0);
        CHECK(g32(*m, kPlayer + w::kRing + 20 * e + 16) == 17);
    }
    // ten header sectors: nine movies' headers and one that is not a header
    u32 n = 0;
    for (std::size_t i = 0; i < files.size() && n < 10; ++i, ++n) {
        const u8* sec = files[i].head.data() + (n == 4 ? 0 : 4096);
        std::memcpy(m->at(kHdr), sec, 2048);
        pair_fn(*m, "sub_57F3E0", {sx(kPlayer), sx(kHdr), 2048, 0}, seed++);
    }
    CHECK(g32(*m, kPlayer + w::kHdrCount) == 10);
    CHECK(g32(*m, kPlayer + w::kRingWrite) == 9 % 8);  // nine entries pushed, mod 8
    for (u32 e = 0; e < 8; ++e) {
        const u32 ent = kPlayer + w::kRing + 20 * e;
        CHECK(g32(*m, ent) == 1);
        CHECK(g32(*m, ent + 16) == 17);  // the movies' video byte +39 is 0
        hgp::Run r = pair_fn(*m, "sub_582A08", {sx(kPlayer), e, 0, 0}, seed++);
        CHECK(v0_of(r) == 17);
    }
    // the entry numbers skip the non-header (number 4)
    CHECK(g32(*m, kPlayer + w::kRing + 20 * 0 + 4) == 9);  // the ninth entry (header number 9) wrapped onto slot 0
    CHECK(g32(*m, kPlayer + w::kRing + 20 * 4 + 4) == 5);
    // short sectors are counted but not pushed
    pair_fn(*m, "sub_57F3E0", {sx(kPlayer), sx(kHdr), 2047, 0}, seed++);
    CHECK(g32(*m, kPlayer + w::kHdrCount) == 11);
    CHECK(g32(*m, kPlayer + w::kRingWrite) == 1);
    // the kind code read back through the read position, 81 / 97 reported as 65
    for (u32 kind : {17u, 33u, 81u, 97u}) {
        p32(*m, kPlayer + w::kRingRead, 3);
        p32(*m, kPlayer + w::kRing + 20 * 3 + 16, kind);
        hgp::Run r = pair_fn(*m, "sub_57F218", {sx(kPlayer), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == ((kind == 81 || kind == 97) ? 65u : kind));
        r = pair_fn(*m, "sub_57F5F8", {sx(kPlayer), 0, 0, 0}, seed++);
        CHECK(v0_of(r) == 3);
    }
    // the probe of mwPlyGetHdrInf over a movie's first three sectors: the header is the third
    std::memcpy(m->at(kBuf), files[0].head.data(), 3 * 2048);
    std::memset(m->at(kOut), 0x33, 64);
    pair_fn(*m, "sub_57F0F0", {sx(kBuf), 3 * 2048, sx(kOut), 0}, seed++);
    const HostHdr hh{files[0].head.data() + 4096};
    CHECK(g32(*m, kOut + 20) == hh.le32(192));
    CHECK(g32(*m, kOut + 24) == 17);
    CHECK(g32(*m, kOut + 28) == files[0].head[4096 + 178]);
    CHECK(g32(*m, kOut + 32) == files[0].head[4096 + 177]);
    // installing the callback on the player's SFD handle: parameters 75 / 76
    std::memset(m->at(kHandle), 0, 0x37B0);
    p32(*m, kHandle + tail1::sfd::kHandleValid, 1);
    p32(*m, kPlayer + w::kSfdHandle, kHandle);
    pair_fn(*m, "sub_57F390", {sx(kPlayer), 0, 0, 0}, seed++);
    CHECK(g32(*m, kHandle + tail1::sfd::kParams + 4 * 75) == 0x57F3E0u);
    CHECK(g32(*m, kHandle + tail1::sfd::kParams + 4 * 76) == kPlayer);
    report("MWSFD header ring");
}

// ======================================================================================================================
// 7. SUD: the "<SUDPS_>" tag and the time base; SFX's handle pool; the stream-object peek with stand-ins.
TEST_CASE("game(tail1): SUD tags and time base, the SFX pool, the start-code peek") {
    auto m = machine();
    if (!m) return;
    u32 seed = 500;
    std::mt19937 rng{0x5A1D0002u};
    // the time base: set, get, below-2 test, 64-bit division (C's truncation toward zero)
    for (s64 tb : {1LL, 2LL, 576000LL, 0x123456789LL}) {
        pair_fn(*m, "sub_5A1CE0", {static_cast<u64>(tb), 0, 0, 0}, seed++);
        hgp::Run r = pair_fn(*m, "sub_5A1B80", {0, 0, 0, 0}, seed++);
        CHECK(static_cast<s64>(r.end.gpr[GPR_V0].u64[0]) == tb);
        r = pair_fn(*m, "sub_5A1B58", {0, 0, 0, 0}, seed++);
        CHECK(v0_of(r) == (tb < 2 ? 1u : 0u));
        for (s64 x : {0LL, 1LL, -1LL, 1000000007LL, -98765432101LL}) {
            r = pair_fn(*m, "sub_5A1C08", {static_cast<u64>(x), 0, 0, 0}, seed++);
            CHECK(static_cast<s64>(r.end.gpr[GPR_V0].u64[0]) == x / tb);
        }
    }
    pair_fn(*m, "sub_5A1B68", {77, 0, 0, 0}, seed++);
    CHECK(g64(*m, tail1::sud::kTimeBase) == 77);
    // the tag finder: the last "<SUDPS_>" in the buffer, length 35
    for (int round = 0; round < 24; ++round) {
        const u32 len = 40 + rng() % 400;
        std::vector<u8> b(len + 16);
        for (u8& c : b) {
            const u32 k = rng() % 5;
            c = k == 0 ? static_cast<u8>('<') : static_cast<u8>(rng());
        }
        const int plants = static_cast<int>(rng() % 3);
        for (int i = 0; i < plants; ++i) {
            const u32 at = rng() % (len - 8);
            std::memcpy(b.data() + at, "<SUDPS_>", 8);
        }
        std::memcpy(m->at(kBuf), b.data(), b.size());
        p32(*m, kOut, 0xDEAD);
        p32(*m, kOut + 4, 0xDEAD);
        pair_fn(*m, "sub_5A1790", {sx(kBuf), len, sx(kOut), sx(kOut + 4)}, seed++);
        u32 last = 0;
        for (u32 i = 0; i < len; ++i)
            if (std::memcmp(b.data() + i, "<SUDPS_>", 8) == 0) last = kBuf + i;
        CHECK(g32(*m, kOut) == last);
        CHECK(g32(*m, kOut + 4) == (last ? 35u : 0u));
    }
    // the tag's two-digit number at +16 / +17. Finding: the two characters are copied to the stack WITHOUT a terminator,
    // so atoi goes on into whatever the stack holds after them (sp + 2 of its 0x20-byte frame): a NUL there gives the
    // two-digit number, a digit there a third digit.
    const u32 frame = kSp - 0x20u;
    for (const char* digits : {"02", "13", "99", "7x", "00"}) {
        for (const char after : {'\0', '5'}) {
            std::memset(m->at(kBuf), 'Z', 32);
            std::memcpy(m->at(kBuf + 16), digits, 2);
            m->at(frame + 2)[0] = static_cast<u8>(after);
            m->at(frame + 3)[0] = 0;
            hgp::Run r = pair_fn(*m, "sub_5A12F8", {sx(kBuf), 35, 0, 0}, seed++);
            const std::string text = std::string(digits, 2) + (after ? std::string(1, after) : std::string());
            CHECK(v0_of(r) == static_cast<u32>(std::atoi(text.c_str())));
        }
    }
    hgp::Run r = pair_fn(*m, "sub_5A12F8", {0, 35, 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    r = pair_fn(*m, "sub_5A12F8", {sx(kBuf), sx(0xFFFFFFFFu), 0, 0}, seed++);
    CHECK(v0_of(r) == 0);
    for (u32 i0 = 0; i0 < 2; ++i0)
        for (u32 i2 = 0; i2 < 2; ++i2) {
            p32(*m, kOut, i0);
            p32(*m, kOut + 4, 1 - i0);
            p32(*m, kOut + 8, i2);
            std::memset(m->at(kBuf), '.', 8);
            pair_fn(*m, "sub_5A1218", {sx(kBuf), sx(kOut), 0, 0}, seed++);
            const u32 tables[] = {0x7CABE0u, 0x7CABF8u, 0x7CAC10u}, idx[] = {i0, 1 - i0, i2};
            for (int k = 0; k < 3; ++k) CHECK(m->at(kBuf + 2 + static_cast<u32>(k))[0] == m->at(g32(*m, tables[k] + 4 * idx[k]))[0]);
            CHECK(m->at(kBuf + 1)[0] == '.');
            CHECK(m->at(kBuf + 5)[0] == '.');
        }
    // SFX: init, create until full (8), destroy one, create again
    pair_fn(*m, "sub_59E7A8", {0, 0, 0, 0}, seed++);
    std::vector<u32> hs;
    for (int i = 0; i < 9; ++i) {
        r = pair_fn(*m, "sub_59E808", {0, 0, 0, 0}, seed++);
        hs.push_back(v0_of(r));
    }
    for (int i = 0; i < 8; ++i) {
        CHECK(hs[i] == 0x7B47F8u + 36u * static_cast<u32>(i));
        CHECK(g32(*m, hs[i]) == 1);
        CHECK(g32(*m, hs[i] + 16) == 100);
        CHECK(m->at(hs[i] + 21)[0] == 64);
    }
    CHECK(hs[8] == 0);
    CHECK(g32(*m, 0x7B47F0u) == 8);
    pair_fn(*m, "sub_59E8F0", {sx(hs[3]), 0, 0, 0}, seed++);
    CHECK(g32(*m, 0x7B47F0u) == 7);
    r = pair_fn(*m, "sub_59E808", {0, 0, 0, 0}, seed++);
    CHECK(v0_of(r) == hs[3]);
    // the start-code peek of sub_579660 on a stream object whose get / unget chunk calls are stand-ins
    for (u32 len : {0u, 3u, 4u, 64u}) {
        const u8 code[4] = {0, 0, 1, 0xB3};
        std::memcpy(m->at(kBuf), code, 4);
        const u32 obj = kOut, vtbl = kOut + 32;
        p32(*m, obj, vtbl);
        p32(*m, vtbl + 24, kGetChunk);
        p32(*m, vtbl + 28, kUngetChunk);
        Machine* mp = m.get();
        const WorldSetup setup = [mp, len](StandInWorld& wld) {
            wld.si.install(kGetChunk, "get chunk", [mp, len](EEContext&, StandIns&, StandInCall& c) {
                const u32 out = static_cast<u32>(c.args[3]);
                p32(*mp, out, kBuf);
                p32(*mp, out + 4, len);
            });
            wld.si.install_recorder(kUngetChunk, "unget chunk");
        };
        HwCheck hw;
        hw.ranges = {{0u, EEMemory::kMainRamSize}};
        hw.gpr_mask = kAllGprs;
        hw.compare_hilo = true;
        hw.compare_checkpoint_regs = true;
        hw.compare_dead_stack = true;
        SiPair sp = run_pair_si(*m, find_case("sub_579660").hand, find_case("sub_579660").recomp, {sx(obj), 0, 0, 0}, seed++,
                                "sub_579660", hw, setup);
        ++g_pairs["sub_579660"];
        CHECK(static_cast<u32>(sp.hw.recomp.base.v0) == (len >= 4 ? 64u : 0u));
        CHECK(sp.recomp->si.log.size() == 2);
    }
    // the duplicates of replaced functions: the empty ones against nullsub_1 (0x1007F0, hand-written by font2)
    for (const char* fn : {"__env_unlock_3", "__env_unlock_4", "sub_579070", "sub_5793E0", "sub_59E800"}) {
        for (u32 s = 0; s < 4; ++s) {
            const Case& c = find_case(fn);
            ++g_pairs[fn];
            hgp::pair(*m, c.hand, &recomp_gen::fn_nullsub_1_001007f0, {sx(kBuf), s, 0, 0}, seed++, fn);
        }
    }
    report("SUD / SFX / peek / duplicates");
}

#else

TEST_CASE("game(tail1): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
