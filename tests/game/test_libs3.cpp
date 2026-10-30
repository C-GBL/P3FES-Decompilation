// Pair tests for slice libs3 (game/src/libc/libs3_*.cpp: newlib's stdio core, mprec / strtod, qsort, the heap internals,
// __ieee754_pow; game/src/lib/libs3_*.cpp: CRI Sofdec's M2V / MPS / MPV / MWSFD helpers). Every body against its
// recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the
// return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log. On top
// of the generic sweep (random worlds), meaningful inputs with documented-rule checks:
//   * sscanf / _sscanf_r against the host's sscanf (integers in every base, strings, scansets, %n, %*, floats through
//     strtod); sprintf_r / vsprintf_r against the host's snprintf (the recompiled vfprintf inside);
//   * ungetc on a string FILE, lflush's flag test (__srefill, _fwalk, __swrite and 9 CRI helpers stay recompiled:
//     test_libs1_newlib / test_libs4 / test_libs5 stand them in);
//   * strtod / strtodf / _strtod_r within one ulp of the host; the mprec Bigint arithmetic against host bignums;
//   * qsort with strcmp as the comparator (its three swap types) against std::sort; __ieee754_pow and the pi/2 reduction;
//   * newlib's heap on a replay snapshot's arena;
//   * MPS on the disc's movies (extracted/DATA/SFD): start-code classes, the start-code search, the demultiplexer on
//     real packs against a host walk of ISO/IEC 11172-1 / 13818-1; the MPEG-2 probe and the MPV header decoder on the
//     movies' video;
//   * CRI's muldiv against host 64-bit arithmetic, MPV's clip table, the M2V / MPV handle pools, MWSFD's work allocator
//     and code mappers, the key table and the descrambler (twice = identity), the MPS getters.
// Every random draw is its own statement (the order of evaluation inside one expression differs between compilers).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs3.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
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
namespace libs3 = p3fes::game::libs3;
namespace libc = p3fes::game::libc;
namespace tail1 = p3fes::game::tail1;

namespace p3fes::recomp_gen {
void fn__getpid_r_00520048(EEContext&);  // generated body
void fn__getpid_r_00520048__recomp(EEContext&);  // recompiled
void fn__fwalk_00520410(EEContext&);  // generated body
void fn__fwalk_00520410__recomp(EEContext&);  // recompiled
void fn__execve_r_00520580(EEContext&);  // generated body
void fn__execve_r_00520580__recomp(EEContext&);  // recompiled
void fn__fork_r_005205d8(EEContext&);  // generated body
void fn__fork_r_005205d8__recomp(EEContext&);  // recompiled
void fn_malloc_extend_top_00520768(EEContext&);  // generated body
void fn_malloc_extend_top_00520768__recomp(EEContext&);  // recompiled
void fn__malloc_r_005209c0(EEContext&);  // generated body
void fn__malloc_r_005209c0__recomp(EEContext&);  // recompiled
void fn__Balloc_00521578(EEContext&);  // generated body
void fn__Balloc_00521578__recomp(EEContext&);  // recompiled
void fn__multadd_00521650(EEContext&);  // generated body
void fn__multadd_00521650__recomp(EEContext&);  // recompiled
void fn__s2b_00521758(EEContext&);  // generated body
void fn__s2b_00521758__recomp(EEContext&);  // recompiled
void fn__i2b_005219c8(EEContext&);  // generated body
void fn__i2b_005219c8__recomp(EEContext&);  // recompiled
void fn__multiply_00521a00(EEContext&);  // generated body
void fn__multiply_00521a00__recomp(EEContext&);  // recompiled
void fn__pow5mult_00521c08(EEContext&);  // generated body
void fn__pow5mult_00521c08__recomp(EEContext&);  // recompiled
void fn__lshift_00521d10(EEContext&);  // generated body
void fn__lshift_00521d10__recomp(EEContext&);  // recompiled
void fn___mdiff_00521ed8(EEContext&);  // generated body
void fn___mdiff_00521ed8__recomp(EEContext&);  // recompiled
void fn__d2b_005222c0(EEContext&);  // generated body
void fn__d2b_005222c0__recomp(EEContext&);  // recompiled
void fn__printf_r_00522568(EEContext&);  // generated body
void fn__printf_r_00522568__recomp(EEContext&);  // recompiled
void fn_qsort_005225f8(EEContext&);  // generated body
void fn_qsort_005225f8__recomp(EEContext&);  // recompiled
void fn__realloc_r_00522fc0(EEContext&);  // generated body
void fn__realloc_r_00522fc0__recomp(EEContext&);  // recompiled
void fn_lflush_00523550(EEContext&);  // generated body
void fn_lflush_00523550__recomp(EEContext&);  // recompiled
void fn___srefill_00523580(EEContext&);  // generated body
void fn___srefill_00523580__recomp(EEContext&);  // recompiled
void fn__sprintf_r_00523a58(EEContext&);  // generated body
void fn__sprintf_r_00523a58__recomp(EEContext&);  // recompiled
void fn_sscanf_00523b40(EEContext&);  // generated body
void fn_sscanf_00523b40__recomp(EEContext&);  // recompiled
void fn__sscanf_r_00523bc8(EEContext&);  // generated body
void fn__sscanf_r_00523bc8__recomp(EEContext&);  // recompiled
void fn___sread_00523c60(EEContext&);  // generated body
void fn___sread_00523c60__recomp(EEContext&);  // recompiled
void fn___swrite_00523cc0(EEContext&);  // generated body
void fn___swrite_00523cc0__recomp(EEContext&);  // recompiled
void fn___sseek_00523d40(EEContext&);  // generated body
void fn___sseek_00523d40__recomp(EEContext&);  // recompiled
void fn___sclose_00523da8(EEContext&);  // generated body
void fn___sclose_00523da8__recomp(EEContext&);  // recompiled
void fn__strtod_r_00524aa8(EEContext&);  // generated body
void fn__strtod_r_00524aa8__recomp(EEContext&);  // recompiled
void fn_strtod_005258f8(EEContext&);  // generated body
void fn_strtod_005258f8__recomp(EEContext&);  // recompiled
void fn_strtodf_00525920(EEContext&);  // generated body
void fn_strtodf_00525920__recomp(EEContext&);  // recompiled
void fn___submore_00525ec8(EEContext&);  // generated body
void fn___submore_00525ec8__recomp(EEContext&);  // recompiled
void fn_ungetc_00525fb0(EEContext&);  // generated body
void fn_ungetc_00525fb0__recomp(EEContext&);  // recompiled
void fn___sprint_00526140(EEContext&);  // generated body
void fn___sprint_00526140__recomp(EEContext&);  // recompiled
void fn___sbprintf_00526188(EEContext&);  // generated body
void fn___sbprintf_00526188__recomp(EEContext&);  // recompiled
void fn_cvt_00527810(EEContext&);  // generated body
void fn_cvt_00527810__recomp(EEContext&);  // recompiled
void fn_vfscanf_00527a88(EEContext&);  // generated body
void fn_vfscanf_00527a88__recomp(EEContext&);  // recompiled
void fn___svfscanf_00527b00(EEContext&);  // generated body
void fn___svfscanf_00527b00__recomp(EEContext&);  // recompiled
void fn__vfscanf_r_00527b30(EEContext&);  // generated body
void fn__vfscanf_r_00527b30__recomp(EEContext&);  // recompiled
void fn___svfscanf_r_00527b48(EEContext&);  // generated body
void fn___svfscanf_r_00527b48__recomp(EEContext&);  // recompiled
void fn__vsprintf_r_00528920(EEContext&);  // generated body
void fn__vsprintf_r_00528920__recomp(EEContext&);  // recompiled
void fn___swsetup_005289d0(EEContext&);  // generated body
void fn___swsetup_005289d0__recomp(EEContext&);  // recompiled
void fn___ieee754_pow_005296f0(EEContext&);  // generated body
void fn___ieee754_pow_005296f0__recomp(EEContext&);  // recompiled
void fn___ieee754_rem_pio2_0052a3f0(EEContext&);  // generated body
void fn___ieee754_rem_pio2_0052a3f0__recomp(EEContext&);  // recompiled
void fn_sub_574CA8_00574ca8(EEContext&);  // generated body
void fn_sub_574CA8_00574ca8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_16_00574e50(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_16_00574e50__recomp(EEContext&);  // recompiled
void fn_sub_574E60_00574e60(EEContext&);  // generated body
void fn_sub_574E60_00574e60__recomp(EEContext&);  // recompiled
void fn_sub_574F10_00574f10(EEContext&);  // generated body
void fn_sub_574F10_00574f10__recomp(EEContext&);  // recompiled
void fn_sub_574FE8_00574fe8(EEContext&);  // generated body
void fn_sub_574FE8_00574fe8__recomp(EEContext&);  // recompiled
void fn_sub_575088_00575088(EEContext&);  // generated body
void fn_sub_575088_00575088__recomp(EEContext&);  // recompiled
void fn_sub_575138_00575138(EEContext&);  // generated body
void fn_sub_575138_00575138__recomp(EEContext&);  // recompiled
void fn_sub_575140_00575140(EEContext&);  // generated body
void fn_sub_575140_00575140__recomp(EEContext&);  // recompiled
void fn_sub_575178_00575178(EEContext&);  // generated body
void fn_sub_575178_00575178__recomp(EEContext&);  // recompiled
void fn_sub_5751C8_005751c8(EEContext&);  // generated body
void fn_sub_5751C8_005751c8__recomp(EEContext&);  // recompiled
void fn_sub_575288_00575288(EEContext&);  // generated body
void fn_sub_575288_00575288__recomp(EEContext&);  // recompiled
void fn_sub_5752D8_005752d8(EEContext&);  // generated body
void fn_sub_5752D8_005752d8__recomp(EEContext&);  // recompiled
void fn_sub_5752E0_005752e0(EEContext&);  // generated body
void fn_sub_5752E0_005752e0__recomp(EEContext&);  // recompiled
void fn_sub_575390_00575390(EEContext&);  // generated body
void fn_sub_575390_00575390__recomp(EEContext&);  // recompiled
void fn_sub_5753E8_005753e8(EEContext&);  // generated body
void fn_sub_5753E8_005753e8__recomp(EEContext&);  // recompiled
void fn_sub_575410_00575410(EEContext&);  // generated body
void fn_sub_575410_00575410__recomp(EEContext&);  // recompiled
void fn_sub_575428_00575428(EEContext&);  // generated body
void fn_sub_575428_00575428__recomp(EEContext&);  // recompiled
void fn_sub_575440_00575440(EEContext&);  // generated body
void fn_sub_575440_00575440__recomp(EEContext&);  // recompiled
void fn_sub_575458_00575458(EEContext&);  // generated body
void fn_sub_575458_00575458__recomp(EEContext&);  // recompiled
void fn_atan2l_10_00575470(EEContext&);  // generated body
void fn_atan2l_10_00575470__recomp(EEContext&);  // recompiled
void fn_cosl_10_00575488(EEContext&);  // generated body
void fn_cosl_10_00575488__recomp(EEContext&);  // recompiled
void fn_coshl_10_005754a0(EEContext&);  // generated body
void fn_coshl_10_005754a0__recomp(EEContext&);  // recompiled
void fn_expl_10_005754b8(EEContext&);  // generated body
void fn_expl_10_005754b8__recomp(EEContext&);  // recompiled
void fn_sub_5756A0_005756a0(EEContext&);  // generated body
void fn_sub_5756A0_005756a0__recomp(EEContext&);  // recompiled
void fn_sub_575880_00575880(EEContext&);  // generated body
void fn_sub_575880_00575880__recomp(EEContext&);  // recompiled
void fn___env_lock_3_00575948(EEContext&);  // generated body
void fn___env_lock_3_00575948__recomp(EEContext&);  // recompiled
void fn_sub_575958_00575958(EEContext&);  // generated body
void fn_sub_575958_00575958__recomp(EEContext&);  // recompiled
void fn_sub_5759B0_005759b0(EEContext&);  // generated body
void fn_sub_5759B0_005759b0__recomp(EEContext&);  // recompiled
void fn_sub_575A00_00575a00(EEContext&);  // generated body
void fn_sub_575A00_00575a00__recomp(EEContext&);  // recompiled
void fn_sub_575A50_00575a50(EEContext&);  // generated body
void fn_sub_575A50_00575a50__recomp(EEContext&);  // recompiled
void fn_sub_575AA0_00575aa0(EEContext&);  // generated body
void fn_sub_575AA0_00575aa0__recomp(EEContext&);  // recompiled
void fn_sub_575B48_00575b48(EEContext&);  // generated body
void fn_sub_575B48_00575b48__recomp(EEContext&);  // recompiled
void fn_sub_575C68_00575c68(EEContext&);  // generated body
void fn_sub_575C68_00575c68__recomp(EEContext&);  // recompiled
void fn_sub_575D70_00575d70(EEContext&);  // generated body
void fn_sub_575D70_00575d70__recomp(EEContext&);  // recompiled
void fn_sub_5761D8_005761d8(EEContext&);  // generated body
void fn_sub_5761D8_005761d8__recomp(EEContext&);  // recompiled
void fn_sub_576A48_00576a48(EEContext&);  // generated body
void fn_sub_576A48_00576a48__recomp(EEContext&);  // recompiled
void fn_sub_5776B0_005776b0(EEContext&);  // generated body
void fn_sub_5776B0_005776b0__recomp(EEContext&);  // recompiled
void fn_sub_577720_00577720(EEContext&);  // generated body
void fn_sub_577720_00577720__recomp(EEContext&);  // recompiled
void fn_sub_577780_00577780(EEContext&);  // generated body
void fn_sub_577780_00577780__recomp(EEContext&);  // recompiled
void fn___env_lock_4_005777e8(EEContext&);  // generated body
void fn___env_lock_4_005777e8__recomp(EEContext&);  // recompiled
void fn_sub_5777F8_005777f8(EEContext&);  // generated body
void fn_sub_5777F8_005777f8__recomp(EEContext&);  // recompiled
void fn_sub_577860_00577860(EEContext&);  // generated body
void fn_sub_577860_00577860__recomp(EEContext&);  // recompiled
void fn_sub_577910_00577910(EEContext&);  // generated body
void fn_sub_577910_00577910__recomp(EEContext&);  // recompiled
void fn_sub_5779A8_005779a8(EEContext&);  // generated body
void fn_sub_5779A8_005779a8__recomp(EEContext&);  // recompiled
void fn_sub_577A38_00577a38(EEContext&);  // generated body
void fn_sub_577A38_00577a38__recomp(EEContext&);  // recompiled
void fn_sub_577AB0_00577ab0(EEContext&);  // generated body
void fn_sub_577AB0_00577ab0__recomp(EEContext&);  // recompiled
void fn_sub_577DD8_00577dd8(EEContext&);  // generated body
void fn_sub_577DD8_00577dd8__recomp(EEContext&);  // recompiled
void fn_sub_577E68_00577e68(EEContext&);  // generated body
void fn_sub_577E68_00577e68__recomp(EEContext&);  // recompiled
void fn_sub_578F10_00578f10(EEContext&);  // generated body
void fn_sub_578F10_00578f10__recomp(EEContext&);  // recompiled
void fn_sub_579080_00579080(EEContext&);  // generated body
void fn_sub_579080_00579080__recomp(EEContext&);  // recompiled
void fn_sub_579450_00579450(EEContext&);  // generated body
void fn_sub_579450_00579450__recomp(EEContext&);  // recompiled
void fn_sub_5796D0_005796d0(EEContext&);  // generated body
void fn_sub_5796D0_005796d0__recomp(EEContext&);  // recompiled
void fn_sub_579818_00579818(EEContext&);  // generated body
void fn_sub_579818_00579818__recomp(EEContext&);  // recompiled
void fn_sub_579ED8_00579ed8(EEContext&);  // generated body
void fn_sub_579ED8_00579ed8__recomp(EEContext&);  // recompiled
void fn_sub_57A158_0057a158(EEContext&);  // generated body
void fn_sub_57A158_0057a158__recomp(EEContext&);  // recompiled
void fn_sub_57A740_0057a740(EEContext&);  // generated body
void fn_sub_57A740_0057a740__recomp(EEContext&);  // recompiled
void fn_sub_57A800_0057a800(EEContext&);  // generated body
void fn_sub_57A800_0057a800__recomp(EEContext&);  // recompiled
void fn_sub_57A8F0_0057a8f0(EEContext&);  // generated body
void fn_sub_57A8F0_0057a8f0__recomp(EEContext&);  // recompiled
void fn_sub_57AAB8_0057aab8(EEContext&);  // generated body
void fn_sub_57AAB8_0057aab8__recomp(EEContext&);  // recompiled
void fn_sub_57ABC0_0057abc0(EEContext&);  // generated body
void fn_sub_57ABC0_0057abc0__recomp(EEContext&);  // recompiled
void fn_sub_57AC68_0057ac68(EEContext&);  // generated body
void fn_sub_57AC68_0057ac68__recomp(EEContext&);  // recompiled
void fn_sub_57ADC0_0057adc0(EEContext&);  // generated body
void fn_sub_57ADC0_0057adc0__recomp(EEContext&);  // recompiled
void fn_sub_57AE90_0057ae90(EEContext&);  // generated body
void fn_sub_57AE90_0057ae90__recomp(EEContext&);  // recompiled
void fn_sub_57AEE8_0057aee8(EEContext&);  // generated body
void fn_sub_57AEE8_0057aee8__recomp(EEContext&);  // recompiled
void fn_sub_57AEF0_0057aef0(EEContext&);  // generated body
void fn_sub_57AEF0_0057aef0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_18_0057aef8(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_18_0057aef8__recomp(EEContext&);  // recompiled
void fn_sub_57AF08_0057af08(EEContext&);  // generated body
void fn_sub_57AF08_0057af08__recomp(EEContext&);  // recompiled
void fn_sub_57AFA0_0057afa0(EEContext&);  // generated body
void fn_sub_57AFA0_0057afa0__recomp(EEContext&);  // recompiled
void fn_sub_57B078_0057b078(EEContext&);  // generated body
void fn_sub_57B078_0057b078__recomp(EEContext&);  // recompiled
void fn_sub_57B0F0_0057b0f0(EEContext&);  // generated body
void fn_sub_57B0F0_0057b0f0__recomp(EEContext&);  // recompiled
void fn_sub_57B0F8_0057b0f8(EEContext&);  // generated body
void fn_sub_57B0F8_0057b0f8__recomp(EEContext&);  // recompiled
void fn_sub_57B100_0057b100(EEContext&);  // generated body
void fn_sub_57B100_0057b100__recomp(EEContext&);  // recompiled
void fn_sub_57B118_0057b118(EEContext&);  // generated body
void fn_sub_57B118_0057b118__recomp(EEContext&);  // recompiled
void fn_sub_57B120_0057b120(EEContext&);  // generated body
void fn_sub_57B120_0057b120__recomp(EEContext&);  // recompiled
void fn_sub_57B138_0057b138(EEContext&);  // generated body
void fn_sub_57B138_0057b138__recomp(EEContext&);  // recompiled
void fn_sub_57B140_0057b140(EEContext&);  // generated body
void fn_sub_57B140_0057b140__recomp(EEContext&);  // recompiled
void fn_sub_57B158_0057b158(EEContext&);  // generated body
void fn_sub_57B158_0057b158__recomp(EEContext&);  // recompiled
void fn_sub_57B1A8_0057b1a8(EEContext&);  // generated body
void fn_sub_57B1A8_0057b1a8__recomp(EEContext&);  // recompiled
void fn_sub_57B230_0057b230(EEContext&);  // generated body
void fn_sub_57B230_0057b230__recomp(EEContext&);  // recompiled
void fn_sub_57B278_0057b278(EEContext&);  // generated body
void fn_sub_57B278_0057b278__recomp(EEContext&);  // recompiled
void fn_sub_57B2B0_0057b2b0(EEContext&);  // generated body
void fn_sub_57B2B0_0057b2b0__recomp(EEContext&);  // recompiled
void fn_sub_57B2B8_0057b2b8(EEContext&);  // generated body
void fn_sub_57B2B8_0057b2b8__recomp(EEContext&);  // recompiled
void fn_sub_57B368_0057b368(EEContext&);  // generated body
void fn_sub_57B368_0057b368__recomp(EEContext&);  // recompiled
void fn_sub_57B418_0057b418(EEContext&);  // generated body
void fn_sub_57B418_0057b418__recomp(EEContext&);  // recompiled
void fn_sub_57B440_0057b440(EEContext&);  // generated body
void fn_sub_57B440_0057b440__recomp(EEContext&);  // recompiled
void fn_sub_57B498_0057b498(EEContext&);  // generated body
void fn_sub_57B498_0057b498__recomp(EEContext&);  // recompiled
void fn_sub_57B4E8_0057b4e8(EEContext&);  // generated body
void fn_sub_57B4E8_0057b4e8__recomp(EEContext&);  // recompiled
void fn_sub_57B5B0_0057b5b0(EEContext&);  // generated body
void fn_sub_57B5B0_0057b5b0__recomp(EEContext&);  // recompiled
void fn_sub_57B5C8_0057b5c8(EEContext&);  // generated body
void fn_sub_57B5C8_0057b5c8__recomp(EEContext&);  // recompiled
void fn___env_lock_5_0057b630(EEContext&);  // generated body
void fn___env_lock_5_0057b630__recomp(EEContext&);  // recompiled
void fn___env_unlock_5_0057b638(EEContext&);  // generated body
void fn___env_unlock_5_0057b638__recomp(EEContext&);  // recompiled
void fn_sub_57B640_0057b640(EEContext&);  // generated body
void fn_sub_57B640_0057b640__recomp(EEContext&);  // recompiled
void fn_sub_57B648_0057b648(EEContext&);  // generated body
void fn_sub_57B648_0057b648__recomp(EEContext&);  // recompiled
void fn_sub_57B710_0057b710(EEContext&);  // generated body
void fn_sub_57B710_0057b710__recomp(EEContext&);  // recompiled
void fn_sub_57B760_0057b760(EEContext&);  // generated body
void fn_sub_57B760_0057b760__recomp(EEContext&);  // recompiled
void fn_sub_57B818_0057b818(EEContext&);  // generated body
void fn_sub_57B818_0057b818__recomp(EEContext&);  // recompiled
void fn_sub_57B830_0057b830(EEContext&);  // generated body
void fn_sub_57B830_0057b830__recomp(EEContext&);  // recompiled
void fn_sub_57B860_0057b860(EEContext&);  // generated body
void fn_sub_57B860_0057b860__recomp(EEContext&);  // recompiled
void fn_sub_57B878_0057b878(EEContext&);  // generated body
void fn_sub_57B878_0057b878__recomp(EEContext&);  // recompiled
void fn_sub_57B890_0057b890(EEContext&);  // generated body
void fn_sub_57B890_0057b890__recomp(EEContext&);  // recompiled
void fn_sub_57B8A8_0057b8a8(EEContext&);  // generated body
void fn_sub_57B8A8_0057b8a8__recomp(EEContext&);  // recompiled
void fn_sub_57B8D0_0057b8d0(EEContext&);  // generated body
void fn_sub_57B8D0_0057b8d0__recomp(EEContext&);  // recompiled
void fn_sub_57B998_0057b998(EEContext&);  // generated body
void fn_sub_57B998_0057b998__recomp(EEContext&);  // recompiled
void fn_sub_57BAD8_0057bad8(EEContext&);  // generated body
void fn_sub_57BAD8_0057bad8__recomp(EEContext&);  // recompiled
void fn_sub_57BAF0_0057baf0(EEContext&);  // generated body
void fn_sub_57BAF0_0057baf0__recomp(EEContext&);  // recompiled
void fn_sub_57BB60_0057bb60(EEContext&);  // generated body
void fn_sub_57BB60_0057bb60__recomp(EEContext&);  // recompiled
void fn_sub_57BC10_0057bc10(EEContext&);  // generated body
void fn_sub_57BC10_0057bc10__recomp(EEContext&);  // recompiled
void fn_sub_57BCB8_0057bcb8(EEContext&);  // generated body
void fn_sub_57BCB8_0057bcb8__recomp(EEContext&);  // recompiled
void fn_sub_57BCD8_0057bcd8(EEContext&);  // generated body
void fn_sub_57BCD8_0057bcd8__recomp(EEContext&);  // recompiled
void fn_sub_57BD10_0057bd10(EEContext&);  // generated body
void fn_sub_57BD10_0057bd10__recomp(EEContext&);  // recompiled
void fn_sub_57BD30_0057bd30(EEContext&);  // generated body
void fn_sub_57BD30_0057bd30__recomp(EEContext&);  // recompiled
void fn_sub_57BD50_0057bd50(EEContext&);  // generated body
void fn_sub_57BD50_0057bd50__recomp(EEContext&);  // recompiled
void fn_sub_57BF08_0057bf08(EEContext&);  // generated body
void fn_sub_57BF08_0057bf08__recomp(EEContext&);  // recompiled
void fn_sub_57BF78_0057bf78(EEContext&);  // generated body
void fn_sub_57BF78_0057bf78__recomp(EEContext&);  // recompiled
void fn_sub_57BF98_0057bf98(EEContext&);  // generated body
void fn_sub_57BF98_0057bf98__recomp(EEContext&);  // recompiled
void fn_sub_57BFB8_0057bfb8(EEContext&);  // generated body
void fn_sub_57BFB8_0057bfb8__recomp(EEContext&);  // recompiled
void fn_sub_57BFC0_0057bfc0(EEContext&);  // generated body
void fn_sub_57BFC0_0057bfc0__recomp(EEContext&);  // recompiled
void fn_sub_57C188_0057c188(EEContext&);  // generated body
void fn_sub_57C188_0057c188__recomp(EEContext&);  // recompiled
void fn_sub_57C210_0057c210(EEContext&);  // generated body
void fn_sub_57C210_0057c210__recomp(EEContext&);  // recompiled
void fn_sub_57C270_0057c270(EEContext&);  // generated body
void fn_sub_57C270_0057c270__recomp(EEContext&);  // recompiled
void fn_sub_57C2B0_0057c2b0(EEContext&);  // generated body
void fn_sub_57C2B0_0057c2b0__recomp(EEContext&);  // recompiled
void fn_sub_57C398_0057c398(EEContext&);  // generated body
void fn_sub_57C398_0057c398__recomp(EEContext&);  // recompiled
void fn_sub_57C3E8_0057c3e8(EEContext&);  // generated body
void fn_sub_57C3E8_0057c3e8__recomp(EEContext&);  // recompiled
void fn_sub_57C4E8_0057c4e8(EEContext&);  // generated body
void fn_sub_57C4E8_0057c4e8__recomp(EEContext&);  // recompiled
void fn_sub_57C538_0057c538(EEContext&);  // generated body
void fn_sub_57C538_0057c538__recomp(EEContext&);  // recompiled
void fn_sub_57C568_0057c568(EEContext&);  // generated body
void fn_sub_57C568_0057c568__recomp(EEContext&);  // recompiled
void fn_sub_57C570_0057c570(EEContext&);  // generated body
void fn_sub_57C570_0057c570__recomp(EEContext&);  // recompiled
void fn_sub_57C628_0057c628(EEContext&);  // generated body
void fn_sub_57C628_0057c628__recomp(EEContext&);  // recompiled
void fn_sub_57C680_0057c680(EEContext&);  // generated body
void fn_sub_57C680_0057c680__recomp(EEContext&);  // recompiled
void fn_sub_57C6E0_0057c6e0(EEContext&);  // generated body
void fn_sub_57C6E0_0057c6e0__recomp(EEContext&);  // recompiled
void fn_sub_57C730_0057c730(EEContext&);  // generated body
void fn_sub_57C730_0057c730__recomp(EEContext&);  // recompiled
void fn_sub_57C800_0057c800(EEContext&);  // generated body
void fn_sub_57C800_0057c800__recomp(EEContext&);  // recompiled
void fn_sub_57C910_0057c910(EEContext&);  // generated body
void fn_sub_57C910_0057c910__recomp(EEContext&);  // recompiled
void fn_sub_57CA78_0057ca78(EEContext&);  // generated body
void fn_sub_57CA78_0057ca78__recomp(EEContext&);  // recompiled
void fn_sub_57D1D0_0057d1d0(EEContext&);  // generated body
void fn_sub_57D1D0_0057d1d0__recomp(EEContext&);  // recompiled
void fn_sub_57D208_0057d208(EEContext&);  // generated body
void fn_sub_57D208_0057d208__recomp(EEContext&);  // recompiled
void fn_sub_57D220_0057d220(EEContext&);  // generated body
void fn_sub_57D220_0057d220__recomp(EEContext&);  // recompiled
void fn_sub_57D308_0057d308(EEContext&);  // generated body
void fn_sub_57D308_0057d308__recomp(EEContext&);  // recompiled
void fn_sub_57D380_0057d380(EEContext&);  // generated body
void fn_sub_57D380_0057d380__recomp(EEContext&);  // recompiled
void fn_sub_57D3C8_0057d3c8(EEContext&);  // generated body
void fn_sub_57D3C8_0057d3c8__recomp(EEContext&);  // recompiled
void fn_sub_57D518_0057d518(EEContext&);  // generated body
void fn_sub_57D518_0057d518__recomp(EEContext&);  // recompiled
void fn_sub_57D5B0_0057d5b0(EEContext&);  // generated body
void fn_sub_57D5B0_0057d5b0__recomp(EEContext&);  // recompiled
void fn_sub_57D5D8_0057d5d8(EEContext&);  // generated body
void fn_sub_57D5D8_0057d5d8__recomp(EEContext&);  // recompiled
void fn_sub_57D960_0057d960(EEContext&);  // generated body
void fn_sub_57D960_0057d960__recomp(EEContext&);  // recompiled
void fn_sub_57D9B0_0057d9b0(EEContext&);  // generated body
void fn_sub_57D9B0_0057d9b0__recomp(EEContext&);  // recompiled
void fn_sub_57DA08_0057da08(EEContext&);  // generated body
void fn_sub_57DA08_0057da08__recomp(EEContext&);  // recompiled
void fn_sub_57DA90_0057da90(EEContext&);  // generated body
void fn_sub_57DA90_0057da90__recomp(EEContext&);  // recompiled
void fn_sub_57DB58_0057db58(EEContext&);  // generated body
void fn_sub_57DB58_0057db58__recomp(EEContext&);  // recompiled
void fn_sub_57DC80_0057dc80(EEContext&);  // generated body
void fn_sub_57DC80_0057dc80__recomp(EEContext&);  // recompiled
void fn_sub_57DC90_0057dc90(EEContext&);  // generated body
void fn_sub_57DC90_0057dc90__recomp(EEContext&);  // recompiled
void fn_sub_57DF60_0057df60(EEContext&);  // generated body
void fn_sub_57DF60_0057df60__recomp(EEContext&);  // recompiled
void fn_sub_57DFB0_0057dfb0(EEContext&);  // generated body
void fn_sub_57DFB0_0057dfb0__recomp(EEContext&);  // recompiled
void fn_sub_57E028_0057e028(EEContext&);  // generated body
void fn_sub_57E028_0057e028__recomp(EEContext&);  // recompiled
void fn_sub_57E070_0057e070(EEContext&);  // generated body
void fn_sub_57E070_0057e070__recomp(EEContext&);  // recompiled
void fn_sub_57E110_0057e110(EEContext&);  // generated body
void fn_sub_57E110_0057e110__recomp(EEContext&);  // recompiled
void fn_sub_57E148_0057e148(EEContext&);  // generated body
void fn_sub_57E148_0057e148__recomp(EEContext&);  // recompiled
void fn_sub_57E180_0057e180(EEContext&);  // generated body
void fn_sub_57E180_0057e180__recomp(EEContext&);  // recompiled
void fn_sub_57E1D0_0057e1d0(EEContext&);  // generated body
void fn_sub_57E1D0_0057e1d0__recomp(EEContext&);  // recompiled
void fn_sub_57E1D8_0057e1d8(EEContext&);  // generated body
void fn_sub_57E1D8_0057e1d8__recomp(EEContext&);  // recompiled
void fn_sub_57E210_0057e210(EEContext&);  // generated body
void fn_sub_57E210_0057e210__recomp(EEContext&);  // recompiled
void fn_sub_57E270_0057e270(EEContext&);  // generated body
void fn_sub_57E270_0057e270__recomp(EEContext&);  // recompiled
void fn_sub_57E290_0057e290(EEContext&);  // generated body
void fn_sub_57E290_0057e290__recomp(EEContext&);  // recompiled
void fn_sub_57E298_0057e298(EEContext&);  // generated body
void fn_sub_57E298_0057e298__recomp(EEContext&);  // recompiled
void fn_sub_57E320_0057e320(EEContext&);  // generated body
void fn_sub_57E320_0057e320__recomp(EEContext&);  // recompiled
void fn_sub_57E360_0057e360(EEContext&);  // generated body
void fn_sub_57E360_0057e360__recomp(EEContext&);  // recompiled
void fn_sub_57E378_0057e378(EEContext&);  // generated body
void fn_sub_57E378_0057e378__recomp(EEContext&);  // recompiled
void fn_sub_57E3D0_0057e3d0(EEContext&);  // generated body
void fn_sub_57E3D0_0057e3d0__recomp(EEContext&);  // recompiled
void fn_sub_57E428_0057e428(EEContext&);  // generated body
void fn_sub_57E428_0057e428__recomp(EEContext&);  // recompiled
void fn_sub_57E530_0057e530(EEContext&);  // generated body
void fn_sub_57E530_0057e530__recomp(EEContext&);  // recompiled
void fn_sub_57E698_0057e698(EEContext&);  // generated body
void fn_sub_57E698_0057e698__recomp(EEContext&);  // recompiled
void fn_sub_57E6E0_0057e6e0(EEContext&);  // generated body
void fn_sub_57E6E0_0057e6e0__recomp(EEContext&);  // recompiled
void fn_sub_57E730_0057e730(EEContext&);  // generated body
void fn_sub_57E730_0057e730__recomp(EEContext&);  // recompiled
void fn_sub_57E910_0057e910(EEContext&);  // generated body
void fn_sub_57E910_0057e910__recomp(EEContext&);  // recompiled
void fn_sub_57E9A8_0057e9a8(EEContext&);  // generated body
void fn_sub_57E9A8_0057e9a8__recomp(EEContext&);  // recompiled
void fn_sub_57E9D8_0057e9d8(EEContext&);  // generated body
void fn_sub_57E9D8_0057e9d8__recomp(EEContext&);  // recompiled
void fn_sub_57EA18_0057ea18(EEContext&);  // generated body
void fn_sub_57EA18_0057ea18__recomp(EEContext&);  // recompiled
void fn_sub_57EA80_0057ea80(EEContext&);  // generated body
void fn_sub_57EA80_0057ea80__recomp(EEContext&);  // recompiled
void fn_sub_57EB38_0057eb38(EEContext&);  // generated body
void fn_sub_57EB38_0057eb38__recomp(EEContext&);  // recompiled
void fn_sub_57EB80_0057eb80(EEContext&);  // generated body
void fn_sub_57EB80_0057eb80__recomp(EEContext&);  // recompiled
void fn_sub_57EC00_0057ec00(EEContext&);  // generated body
void fn_sub_57EC00_0057ec00__recomp(EEContext&);  // recompiled
void fn_sub_57EC38_0057ec38(EEContext&);  // generated body
void fn_sub_57EC38_0057ec38__recomp(EEContext&);  // recompiled
void fn_sub_57ED00_0057ed00(EEContext&);  // generated body
void fn_sub_57ED00_0057ed00__recomp(EEContext&);  // recompiled
void fn_sub_57ED40_0057ed40(EEContext&);  // generated body
void fn_sub_57ED40_0057ed40__recomp(EEContext&);  // recompiled
void fn_sub_57EDA8_0057eda8(EEContext&);  // generated body
void fn_sub_57EDA8_0057eda8__recomp(EEContext&);  // recompiled
void fn_sub_57EDD8_0057edd8(EEContext&);  // generated body
void fn_sub_57EDD8_0057edd8__recomp(EEContext&);  // recompiled
void fn_sub_57EE50_0057ee50(EEContext&);  // generated body
void fn_sub_57EE50_0057ee50__recomp(EEContext&);  // recompiled
void fn_sub_57EF08_0057ef08(EEContext&);  // generated body
void fn_sub_57EF08_0057ef08__recomp(EEContext&);  // recompiled
void fn_sub_57EF78_0057ef78(EEContext&);  // generated body
void fn_sub_57EF78_0057ef78__recomp(EEContext&);  // recompiled
void fn_sub_57F050_0057f050(EEContext&);  // generated body
void fn_sub_57F050_0057f050__recomp(EEContext&);  // recompiled
void fn_sub_57F058_0057f058(EEContext&);  // generated body
void fn_sub_57F058_0057f058__recomp(EEContext&);  // recompiled
void fn_sub_57F0A8_0057f0a8(EEContext&);  // generated body
void fn_sub_57F0A8_0057f0a8__recomp(EEContext&);  // recompiled
void fn_sub_57F600_0057f600(EEContext&);  // generated body
void fn_sub_57F600_0057f600__recomp(EEContext&);  // recompiled
void fn_sub_57F670_0057f670(EEContext&);  // generated body
void fn_sub_57F670_0057f670__recomp(EEContext&);  // recompiled
void fn_sub_57F6F8_0057f6f8(EEContext&);  // generated body
void fn_sub_57F6F8_0057f6f8__recomp(EEContext&);  // recompiled
void fn_sub_57F750_0057f750(EEContext&);  // generated body
void fn_sub_57F750_0057f750__recomp(EEContext&);  // recompiled
void fn_sub_57F768_0057f768(EEContext&);  // generated body
void fn_sub_57F768_0057f768__recomp(EEContext&);  // recompiled
void fn_sub_57F920_0057f920(EEContext&);  // generated body
void fn_sub_57F920_0057f920__recomp(EEContext&);  // recompiled
void fn_sub_57F980_0057f980(EEContext&);  // generated body
void fn_sub_57F980_0057f980__recomp(EEContext&);  // recompiled
void fn_sub_57FA28_0057fa28(EEContext&);  // generated body
void fn_sub_57FA28_0057fa28__recomp(EEContext&);  // recompiled
void fn_sub_57FA50_0057fa50(EEContext&);  // generated body
void fn_sub_57FA50_0057fa50__recomp(EEContext&);  // recompiled
void fn_sub_57FA70_0057fa70(EEContext&);  // generated body
void fn_sub_57FA70_0057fa70__recomp(EEContext&);  // recompiled
void fn_sub_57FA98_0057fa98(EEContext&);  // generated body
void fn_sub_57FA98_0057fa98__recomp(EEContext&);  // recompiled
void fn_sub_57FAB8_0057fab8(EEContext&);  // generated body
void fn_sub_57FAB8_0057fab8__recomp(EEContext&);  // recompiled
void fn_sub_57FAF0_0057faf0(EEContext&);  // generated body
void fn_sub_57FAF0_0057faf0__recomp(EEContext&);  // recompiled
void fn_sub_57FC60_0057fc60(EEContext&);  // generated body
void fn_sub_57FC60_0057fc60__recomp(EEContext&);  // recompiled
void fn_sub_57FC90_0057fc90(EEContext&);  // generated body
void fn_sub_57FC90_0057fc90__recomp(EEContext&);  // recompiled
void fn_sub_57FCB0_0057fcb0(EEContext&);  // generated body
void fn_sub_57FCB0_0057fcb0__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_2_0057fd58(EEContext&);  // generated body
void fn_r_lock_def_free_2_0057fd58__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_2_0057fd78(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_2_0057fd78__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"_getpid_r", 0x520048, &recomp_gen::fn__getpid_r_00520048, &recomp_gen::fn__getpid_r_00520048__recomp},
    {"_execve_r", 0x520580, &recomp_gen::fn__execve_r_00520580, &recomp_gen::fn__execve_r_00520580__recomp},
    {"_fork_r", 0x5205D8, &recomp_gen::fn__fork_r_005205d8, &recomp_gen::fn__fork_r_005205d8__recomp},
    {"malloc_extend_top", 0x520768, &recomp_gen::fn_malloc_extend_top_00520768, &recomp_gen::fn_malloc_extend_top_00520768__recomp},
    {"_malloc_r", 0x5209C0, &recomp_gen::fn__malloc_r_005209c0, &recomp_gen::fn__malloc_r_005209c0__recomp},
    {"_Balloc", 0x521578, &recomp_gen::fn__Balloc_00521578, &recomp_gen::fn__Balloc_00521578__recomp},
    {"_multadd", 0x521650, &recomp_gen::fn__multadd_00521650, &recomp_gen::fn__multadd_00521650__recomp},
    {"_s2b", 0x521758, &recomp_gen::fn__s2b_00521758, &recomp_gen::fn__s2b_00521758__recomp},
    {"_i2b", 0x5219C8, &recomp_gen::fn__i2b_005219c8, &recomp_gen::fn__i2b_005219c8__recomp},
    {"_multiply", 0x521A00, &recomp_gen::fn__multiply_00521a00, &recomp_gen::fn__multiply_00521a00__recomp},
    {"_pow5mult", 0x521C08, &recomp_gen::fn__pow5mult_00521c08, &recomp_gen::fn__pow5mult_00521c08__recomp},
    {"_lshift", 0x521D10, &recomp_gen::fn__lshift_00521d10, &recomp_gen::fn__lshift_00521d10__recomp},
    {"__mdiff", 0x521ED8, &recomp_gen::fn___mdiff_00521ed8, &recomp_gen::fn___mdiff_00521ed8__recomp},
    {"_d2b", 0x5222C0, &recomp_gen::fn__d2b_005222c0, &recomp_gen::fn__d2b_005222c0__recomp},
    {"_printf_r", 0x522568, &recomp_gen::fn__printf_r_00522568, &recomp_gen::fn__printf_r_00522568__recomp},
    {"qsort", 0x5225F8, &recomp_gen::fn_qsort_005225f8, &recomp_gen::fn_qsort_005225f8__recomp},
    {"_realloc_r", 0x522FC0, &recomp_gen::fn__realloc_r_00522fc0, &recomp_gen::fn__realloc_r_00522fc0__recomp},
    {"lflush", 0x523550, &recomp_gen::fn_lflush_00523550, &recomp_gen::fn_lflush_00523550__recomp},
    {"_sprintf_r", 0x523A58, &recomp_gen::fn__sprintf_r_00523a58, &recomp_gen::fn__sprintf_r_00523a58__recomp},
    {"sscanf", 0x523B40, &recomp_gen::fn_sscanf_00523b40, &recomp_gen::fn_sscanf_00523b40__recomp},
    {"_sscanf_r", 0x523BC8, &recomp_gen::fn__sscanf_r_00523bc8, &recomp_gen::fn__sscanf_r_00523bc8__recomp},
    {"__sread", 0x523C60, &recomp_gen::fn___sread_00523c60, &recomp_gen::fn___sread_00523c60__recomp},
    {"__sseek", 0x523D40, &recomp_gen::fn___sseek_00523d40, &recomp_gen::fn___sseek_00523d40__recomp},
    {"__sclose", 0x523DA8, &recomp_gen::fn___sclose_00523da8, &recomp_gen::fn___sclose_00523da8__recomp},
    {"_strtod_r", 0x524AA8, &recomp_gen::fn__strtod_r_00524aa8, &recomp_gen::fn__strtod_r_00524aa8__recomp},
    {"strtod", 0x5258F8, &recomp_gen::fn_strtod_005258f8, &recomp_gen::fn_strtod_005258f8__recomp},
    {"strtodf", 0x525920, &recomp_gen::fn_strtodf_00525920, &recomp_gen::fn_strtodf_00525920__recomp},
    {"__submore", 0x525EC8, &recomp_gen::fn___submore_00525ec8, &recomp_gen::fn___submore_00525ec8__recomp},
    {"ungetc", 0x525FB0, &recomp_gen::fn_ungetc_00525fb0, &recomp_gen::fn_ungetc_00525fb0__recomp},
    {"__sprint", 0x526140, &recomp_gen::fn___sprint_00526140, &recomp_gen::fn___sprint_00526140__recomp},
    {"__sbprintf", 0x526188, &recomp_gen::fn___sbprintf_00526188, &recomp_gen::fn___sbprintf_00526188__recomp},
    {"cvt", 0x527810, &recomp_gen::fn_cvt_00527810, &recomp_gen::fn_cvt_00527810__recomp},
    {"vfscanf", 0x527A88, &recomp_gen::fn_vfscanf_00527a88, &recomp_gen::fn_vfscanf_00527a88__recomp},
    {"__svfscanf", 0x527B00, &recomp_gen::fn___svfscanf_00527b00, &recomp_gen::fn___svfscanf_00527b00__recomp},
    {"_vfscanf_r", 0x527B30, &recomp_gen::fn__vfscanf_r_00527b30, &recomp_gen::fn__vfscanf_r_00527b30__recomp},
    {"__svfscanf_r", 0x527B48, &recomp_gen::fn___svfscanf_r_00527b48, &recomp_gen::fn___svfscanf_r_00527b48__recomp},
    {"_vsprintf_r", 0x528920, &recomp_gen::fn__vsprintf_r_00528920, &recomp_gen::fn__vsprintf_r_00528920__recomp},
    {"__swsetup", 0x5289D0, &recomp_gen::fn___swsetup_005289d0, &recomp_gen::fn___swsetup_005289d0__recomp},
    {"__ieee754_pow", 0x5296F0, &recomp_gen::fn___ieee754_pow_005296f0, &recomp_gen::fn___ieee754_pow_005296f0__recomp},
    {"__ieee754_rem_pio2", 0x52A3F0, &recomp_gen::fn___ieee754_rem_pio2_0052a3f0, &recomp_gen::fn___ieee754_rem_pio2_0052a3f0__recomp},
    {"sub_574CA8", 0x574CA8, &recomp_gen::fn_sub_574CA8_00574ca8, &recomp_gen::fn_sub_574CA8_00574ca8__recomp},
    {"sceLibgcc32GetErxEntries_16", 0x574E50, &recomp_gen::fn_sceLibgcc32GetErxEntries_16_00574e50, &recomp_gen::fn_sceLibgcc32GetErxEntries_16_00574e50__recomp},
    {"sub_574E60", 0x574E60, &recomp_gen::fn_sub_574E60_00574e60, &recomp_gen::fn_sub_574E60_00574e60__recomp},
    {"sub_574F10", 0x574F10, &recomp_gen::fn_sub_574F10_00574f10, &recomp_gen::fn_sub_574F10_00574f10__recomp},
    {"sub_574FE8", 0x574FE8, &recomp_gen::fn_sub_574FE8_00574fe8, &recomp_gen::fn_sub_574FE8_00574fe8__recomp},
    {"sub_575088", 0x575088, &recomp_gen::fn_sub_575088_00575088, &recomp_gen::fn_sub_575088_00575088__recomp},
    {"sub_575138", 0x575138, &recomp_gen::fn_sub_575138_00575138, &recomp_gen::fn_sub_575138_00575138__recomp},
    {"sub_575140", 0x575140, &recomp_gen::fn_sub_575140_00575140, &recomp_gen::fn_sub_575140_00575140__recomp},
    {"sub_575178", 0x575178, &recomp_gen::fn_sub_575178_00575178, &recomp_gen::fn_sub_575178_00575178__recomp},
    {"sub_5751C8", 0x5751C8, &recomp_gen::fn_sub_5751C8_005751c8, &recomp_gen::fn_sub_5751C8_005751c8__recomp},
    {"sub_575288", 0x575288, &recomp_gen::fn_sub_575288_00575288, &recomp_gen::fn_sub_575288_00575288__recomp},
    {"sub_5752D8", 0x5752D8, &recomp_gen::fn_sub_5752D8_005752d8, &recomp_gen::fn_sub_5752D8_005752d8__recomp},
    {"sub_5752E0", 0x5752E0, &recomp_gen::fn_sub_5752E0_005752e0, &recomp_gen::fn_sub_5752E0_005752e0__recomp},
    {"sub_575390", 0x575390, &recomp_gen::fn_sub_575390_00575390, &recomp_gen::fn_sub_575390_00575390__recomp},
    {"sub_575428", 0x575428, &recomp_gen::fn_sub_575428_00575428, &recomp_gen::fn_sub_575428_00575428__recomp},
    {"sub_575440", 0x575440, &recomp_gen::fn_sub_575440_00575440, &recomp_gen::fn_sub_575440_00575440__recomp},
    {"sub_575458", 0x575458, &recomp_gen::fn_sub_575458_00575458, &recomp_gen::fn_sub_575458_00575458__recomp},
    {"atan2l_10", 0x575470, &recomp_gen::fn_atan2l_10_00575470, &recomp_gen::fn_atan2l_10_00575470__recomp},
    {"cosl_10", 0x575488, &recomp_gen::fn_cosl_10_00575488, &recomp_gen::fn_cosl_10_00575488__recomp},
    {"coshl_10", 0x5754A0, &recomp_gen::fn_coshl_10_005754a0, &recomp_gen::fn_coshl_10_005754a0__recomp},
    {"expl_10", 0x5754B8, &recomp_gen::fn_expl_10_005754b8, &recomp_gen::fn_expl_10_005754b8__recomp},
    {"sub_5756A0", 0x5756A0, &recomp_gen::fn_sub_5756A0_005756a0, &recomp_gen::fn_sub_5756A0_005756a0__recomp},
    {"__env_lock_3", 0x575948, &recomp_gen::fn___env_lock_3_00575948, &recomp_gen::fn___env_lock_3_00575948__recomp},
    {"sub_575958", 0x575958, &recomp_gen::fn_sub_575958_00575958, &recomp_gen::fn_sub_575958_00575958__recomp},
    {"sub_5759B0", 0x5759B0, &recomp_gen::fn_sub_5759B0_005759b0, &recomp_gen::fn_sub_5759B0_005759b0__recomp},
    {"sub_575A00", 0x575A00, &recomp_gen::fn_sub_575A00_00575a00, &recomp_gen::fn_sub_575A00_00575a00__recomp},
    {"sub_575A50", 0x575A50, &recomp_gen::fn_sub_575A50_00575a50, &recomp_gen::fn_sub_575A50_00575a50__recomp},
    {"sub_575AA0", 0x575AA0, &recomp_gen::fn_sub_575AA0_00575aa0, &recomp_gen::fn_sub_575AA0_00575aa0__recomp},
    {"sub_575B48", 0x575B48, &recomp_gen::fn_sub_575B48_00575b48, &recomp_gen::fn_sub_575B48_00575b48__recomp},
    {"sub_575C68", 0x575C68, &recomp_gen::fn_sub_575C68_00575c68, &recomp_gen::fn_sub_575C68_00575c68__recomp},
    {"sub_575D70", 0x575D70, &recomp_gen::fn_sub_575D70_00575d70, &recomp_gen::fn_sub_575D70_00575d70__recomp},
    {"sub_5761D8", 0x5761D8, &recomp_gen::fn_sub_5761D8_005761d8, &recomp_gen::fn_sub_5761D8_005761d8__recomp},
    {"sub_576A48", 0x576A48, &recomp_gen::fn_sub_576A48_00576a48, &recomp_gen::fn_sub_576A48_00576a48__recomp},
    {"sub_5776B0", 0x5776B0, &recomp_gen::fn_sub_5776B0_005776b0, &recomp_gen::fn_sub_5776B0_005776b0__recomp},
    {"sub_577720", 0x577720, &recomp_gen::fn_sub_577720_00577720, &recomp_gen::fn_sub_577720_00577720__recomp},
    {"sub_577780", 0x577780, &recomp_gen::fn_sub_577780_00577780, &recomp_gen::fn_sub_577780_00577780__recomp},
    {"__env_lock_4", 0x5777E8, &recomp_gen::fn___env_lock_4_005777e8, &recomp_gen::fn___env_lock_4_005777e8__recomp},
    {"sub_5777F8", 0x5777F8, &recomp_gen::fn_sub_5777F8_005777f8, &recomp_gen::fn_sub_5777F8_005777f8__recomp},
    {"sub_577860", 0x577860, &recomp_gen::fn_sub_577860_00577860, &recomp_gen::fn_sub_577860_00577860__recomp},
    {"sub_577910", 0x577910, &recomp_gen::fn_sub_577910_00577910, &recomp_gen::fn_sub_577910_00577910__recomp},
    {"sub_5779A8", 0x5779A8, &recomp_gen::fn_sub_5779A8_005779a8, &recomp_gen::fn_sub_5779A8_005779a8__recomp},
    {"sub_577A38", 0x577A38, &recomp_gen::fn_sub_577A38_00577a38, &recomp_gen::fn_sub_577A38_00577a38__recomp},
    {"sub_577AB0", 0x577AB0, &recomp_gen::fn_sub_577AB0_00577ab0, &recomp_gen::fn_sub_577AB0_00577ab0__recomp},
    {"sub_577DD8", 0x577DD8, &recomp_gen::fn_sub_577DD8_00577dd8, &recomp_gen::fn_sub_577DD8_00577dd8__recomp},
    {"sub_577E68", 0x577E68, &recomp_gen::fn_sub_577E68_00577e68, &recomp_gen::fn_sub_577E68_00577e68__recomp},
    {"sub_578F10", 0x578F10, &recomp_gen::fn_sub_578F10_00578f10, &recomp_gen::fn_sub_578F10_00578f10__recomp},
    {"sub_579080", 0x579080, &recomp_gen::fn_sub_579080_00579080, &recomp_gen::fn_sub_579080_00579080__recomp},
    {"sub_579450", 0x579450, &recomp_gen::fn_sub_579450_00579450, &recomp_gen::fn_sub_579450_00579450__recomp},
    {"sub_5796D0", 0x5796D0, &recomp_gen::fn_sub_5796D0_005796d0, &recomp_gen::fn_sub_5796D0_005796d0__recomp},
    {"sub_579818", 0x579818, &recomp_gen::fn_sub_579818_00579818, &recomp_gen::fn_sub_579818_00579818__recomp},
    {"sub_579ED8", 0x579ED8, &recomp_gen::fn_sub_579ED8_00579ed8, &recomp_gen::fn_sub_579ED8_00579ed8__recomp},
    {"sub_57A158", 0x57A158, &recomp_gen::fn_sub_57A158_0057a158, &recomp_gen::fn_sub_57A158_0057a158__recomp},
    {"sub_57A740", 0x57A740, &recomp_gen::fn_sub_57A740_0057a740, &recomp_gen::fn_sub_57A740_0057a740__recomp},
    {"sub_57A800", 0x57A800, &recomp_gen::fn_sub_57A800_0057a800, &recomp_gen::fn_sub_57A800_0057a800__recomp},
    {"sub_57A8F0", 0x57A8F0, &recomp_gen::fn_sub_57A8F0_0057a8f0, &recomp_gen::fn_sub_57A8F0_0057a8f0__recomp},
    {"sub_57AAB8", 0x57AAB8, &recomp_gen::fn_sub_57AAB8_0057aab8, &recomp_gen::fn_sub_57AAB8_0057aab8__recomp},
    {"sub_57ABC0", 0x57ABC0, &recomp_gen::fn_sub_57ABC0_0057abc0, &recomp_gen::fn_sub_57ABC0_0057abc0__recomp},
    {"sub_57ADC0", 0x57ADC0, &recomp_gen::fn_sub_57ADC0_0057adc0, &recomp_gen::fn_sub_57ADC0_0057adc0__recomp},
    {"sub_57AEE8", 0x57AEE8, &recomp_gen::fn_sub_57AEE8_0057aee8, &recomp_gen::fn_sub_57AEE8_0057aee8__recomp},
    {"sub_57AEF0", 0x57AEF0, &recomp_gen::fn_sub_57AEF0_0057aef0, &recomp_gen::fn_sub_57AEF0_0057aef0__recomp},
    {"sceLibgcc32GetErxEntries_18", 0x57AEF8, &recomp_gen::fn_sceLibgcc32GetErxEntries_18_0057aef8, &recomp_gen::fn_sceLibgcc32GetErxEntries_18_0057aef8__recomp},
    {"sub_57AF08", 0x57AF08, &recomp_gen::fn_sub_57AF08_0057af08, &recomp_gen::fn_sub_57AF08_0057af08__recomp},
    {"sub_57AFA0", 0x57AFA0, &recomp_gen::fn_sub_57AFA0_0057afa0, &recomp_gen::fn_sub_57AFA0_0057afa0__recomp},
    {"sub_57B078", 0x57B078, &recomp_gen::fn_sub_57B078_0057b078, &recomp_gen::fn_sub_57B078_0057b078__recomp},
    {"sub_57B0F0", 0x57B0F0, &recomp_gen::fn_sub_57B0F0_0057b0f0, &recomp_gen::fn_sub_57B0F0_0057b0f0__recomp},
    {"sub_57B0F8", 0x57B0F8, &recomp_gen::fn_sub_57B0F8_0057b0f8, &recomp_gen::fn_sub_57B0F8_0057b0f8__recomp},
    {"sub_57B100", 0x57B100, &recomp_gen::fn_sub_57B100_0057b100, &recomp_gen::fn_sub_57B100_0057b100__recomp},
    {"sub_57B118", 0x57B118, &recomp_gen::fn_sub_57B118_0057b118, &recomp_gen::fn_sub_57B118_0057b118__recomp},
    {"sub_57B120", 0x57B120, &recomp_gen::fn_sub_57B120_0057b120, &recomp_gen::fn_sub_57B120_0057b120__recomp},
    {"sub_57B138", 0x57B138, &recomp_gen::fn_sub_57B138_0057b138, &recomp_gen::fn_sub_57B138_0057b138__recomp},
    {"sub_57B140", 0x57B140, &recomp_gen::fn_sub_57B140_0057b140, &recomp_gen::fn_sub_57B140_0057b140__recomp},
    {"sub_57B158", 0x57B158, &recomp_gen::fn_sub_57B158_0057b158, &recomp_gen::fn_sub_57B158_0057b158__recomp},
    {"sub_57B1A8", 0x57B1A8, &recomp_gen::fn_sub_57B1A8_0057b1a8, &recomp_gen::fn_sub_57B1A8_0057b1a8__recomp},
    {"sub_57B230", 0x57B230, &recomp_gen::fn_sub_57B230_0057b230, &recomp_gen::fn_sub_57B230_0057b230__recomp},
    {"sub_57B278", 0x57B278, &recomp_gen::fn_sub_57B278_0057b278, &recomp_gen::fn_sub_57B278_0057b278__recomp},
    {"sub_57B2B0", 0x57B2B0, &recomp_gen::fn_sub_57B2B0_0057b2b0, &recomp_gen::fn_sub_57B2B0_0057b2b0__recomp},
    {"sub_57B2B8", 0x57B2B8, &recomp_gen::fn_sub_57B2B8_0057b2b8, &recomp_gen::fn_sub_57B2B8_0057b2b8__recomp},
    {"sub_57B368", 0x57B368, &recomp_gen::fn_sub_57B368_0057b368, &recomp_gen::fn_sub_57B368_0057b368__recomp},
    {"sub_57B418", 0x57B418, &recomp_gen::fn_sub_57B418_0057b418, &recomp_gen::fn_sub_57B418_0057b418__recomp},
    {"sub_57B440", 0x57B440, &recomp_gen::fn_sub_57B440_0057b440, &recomp_gen::fn_sub_57B440_0057b440__recomp},
    {"sub_57B498", 0x57B498, &recomp_gen::fn_sub_57B498_0057b498, &recomp_gen::fn_sub_57B498_0057b498__recomp},
    {"sub_57B4E8", 0x57B4E8, &recomp_gen::fn_sub_57B4E8_0057b4e8, &recomp_gen::fn_sub_57B4E8_0057b4e8__recomp},
    {"sub_57B5B0", 0x57B5B0, &recomp_gen::fn_sub_57B5B0_0057b5b0, &recomp_gen::fn_sub_57B5B0_0057b5b0__recomp},
    {"sub_57B5C8", 0x57B5C8, &recomp_gen::fn_sub_57B5C8_0057b5c8, &recomp_gen::fn_sub_57B5C8_0057b5c8__recomp},
    {"__env_lock_5", 0x57B630, &recomp_gen::fn___env_lock_5_0057b630, &recomp_gen::fn___env_lock_5_0057b630__recomp},
    {"__env_unlock_5", 0x57B638, &recomp_gen::fn___env_unlock_5_0057b638, &recomp_gen::fn___env_unlock_5_0057b638__recomp},
    {"sub_57B640", 0x57B640, &recomp_gen::fn_sub_57B640_0057b640, &recomp_gen::fn_sub_57B640_0057b640__recomp},
    {"sub_57B648", 0x57B648, &recomp_gen::fn_sub_57B648_0057b648, &recomp_gen::fn_sub_57B648_0057b648__recomp},
    {"sub_57B710", 0x57B710, &recomp_gen::fn_sub_57B710_0057b710, &recomp_gen::fn_sub_57B710_0057b710__recomp},
    {"sub_57B760", 0x57B760, &recomp_gen::fn_sub_57B760_0057b760, &recomp_gen::fn_sub_57B760_0057b760__recomp},
    {"sub_57B818", 0x57B818, &recomp_gen::fn_sub_57B818_0057b818, &recomp_gen::fn_sub_57B818_0057b818__recomp},
    {"sub_57B830", 0x57B830, &recomp_gen::fn_sub_57B830_0057b830, &recomp_gen::fn_sub_57B830_0057b830__recomp},
    {"sub_57B860", 0x57B860, &recomp_gen::fn_sub_57B860_0057b860, &recomp_gen::fn_sub_57B860_0057b860__recomp},
    {"sub_57B878", 0x57B878, &recomp_gen::fn_sub_57B878_0057b878, &recomp_gen::fn_sub_57B878_0057b878__recomp},
    {"sub_57B890", 0x57B890, &recomp_gen::fn_sub_57B890_0057b890, &recomp_gen::fn_sub_57B890_0057b890__recomp},
    {"sub_57B8A8", 0x57B8A8, &recomp_gen::fn_sub_57B8A8_0057b8a8, &recomp_gen::fn_sub_57B8A8_0057b8a8__recomp},
    {"sub_57B8D0", 0x57B8D0, &recomp_gen::fn_sub_57B8D0_0057b8d0, &recomp_gen::fn_sub_57B8D0_0057b8d0__recomp},
    {"sub_57B998", 0x57B998, &recomp_gen::fn_sub_57B998_0057b998, &recomp_gen::fn_sub_57B998_0057b998__recomp},
    {"sub_57BAD8", 0x57BAD8, &recomp_gen::fn_sub_57BAD8_0057bad8, &recomp_gen::fn_sub_57BAD8_0057bad8__recomp},
    {"sub_57BAF0", 0x57BAF0, &recomp_gen::fn_sub_57BAF0_0057baf0, &recomp_gen::fn_sub_57BAF0_0057baf0__recomp},
    {"sub_57BB60", 0x57BB60, &recomp_gen::fn_sub_57BB60_0057bb60, &recomp_gen::fn_sub_57BB60_0057bb60__recomp},
    {"sub_57BC10", 0x57BC10, &recomp_gen::fn_sub_57BC10_0057bc10, &recomp_gen::fn_sub_57BC10_0057bc10__recomp},
    {"sub_57BCB8", 0x57BCB8, &recomp_gen::fn_sub_57BCB8_0057bcb8, &recomp_gen::fn_sub_57BCB8_0057bcb8__recomp},
    {"sub_57BCD8", 0x57BCD8, &recomp_gen::fn_sub_57BCD8_0057bcd8, &recomp_gen::fn_sub_57BCD8_0057bcd8__recomp},
    {"sub_57BD10", 0x57BD10, &recomp_gen::fn_sub_57BD10_0057bd10, &recomp_gen::fn_sub_57BD10_0057bd10__recomp},
    {"sub_57BD30", 0x57BD30, &recomp_gen::fn_sub_57BD30_0057bd30, &recomp_gen::fn_sub_57BD30_0057bd30__recomp},
    {"sub_57BD50", 0x57BD50, &recomp_gen::fn_sub_57BD50_0057bd50, &recomp_gen::fn_sub_57BD50_0057bd50__recomp},
    {"sub_57BF08", 0x57BF08, &recomp_gen::fn_sub_57BF08_0057bf08, &recomp_gen::fn_sub_57BF08_0057bf08__recomp},
    {"sub_57BF78", 0x57BF78, &recomp_gen::fn_sub_57BF78_0057bf78, &recomp_gen::fn_sub_57BF78_0057bf78__recomp},
    {"sub_57BF98", 0x57BF98, &recomp_gen::fn_sub_57BF98_0057bf98, &recomp_gen::fn_sub_57BF98_0057bf98__recomp},
    {"sub_57BFB8", 0x57BFB8, &recomp_gen::fn_sub_57BFB8_0057bfb8, &recomp_gen::fn_sub_57BFB8_0057bfb8__recomp},
    {"sub_57BFC0", 0x57BFC0, &recomp_gen::fn_sub_57BFC0_0057bfc0, &recomp_gen::fn_sub_57BFC0_0057bfc0__recomp},
    {"sub_57C188", 0x57C188, &recomp_gen::fn_sub_57C188_0057c188, &recomp_gen::fn_sub_57C188_0057c188__recomp},
    {"sub_57C210", 0x57C210, &recomp_gen::fn_sub_57C210_0057c210, &recomp_gen::fn_sub_57C210_0057c210__recomp},
    {"sub_57C270", 0x57C270, &recomp_gen::fn_sub_57C270_0057c270, &recomp_gen::fn_sub_57C270_0057c270__recomp},
    {"sub_57C2B0", 0x57C2B0, &recomp_gen::fn_sub_57C2B0_0057c2b0, &recomp_gen::fn_sub_57C2B0_0057c2b0__recomp},
    {"sub_57C398", 0x57C398, &recomp_gen::fn_sub_57C398_0057c398, &recomp_gen::fn_sub_57C398_0057c398__recomp},
    {"sub_57C3E8", 0x57C3E8, &recomp_gen::fn_sub_57C3E8_0057c3e8, &recomp_gen::fn_sub_57C3E8_0057c3e8__recomp},
    {"sub_57C4E8", 0x57C4E8, &recomp_gen::fn_sub_57C4E8_0057c4e8, &recomp_gen::fn_sub_57C4E8_0057c4e8__recomp},
    {"sub_57C538", 0x57C538, &recomp_gen::fn_sub_57C538_0057c538, &recomp_gen::fn_sub_57C538_0057c538__recomp},
    {"sub_57C568", 0x57C568, &recomp_gen::fn_sub_57C568_0057c568, &recomp_gen::fn_sub_57C568_0057c568__recomp},
    {"sub_57C570", 0x57C570, &recomp_gen::fn_sub_57C570_0057c570, &recomp_gen::fn_sub_57C570_0057c570__recomp},
    {"sub_57C628", 0x57C628, &recomp_gen::fn_sub_57C628_0057c628, &recomp_gen::fn_sub_57C628_0057c628__recomp},
    {"sub_57C680", 0x57C680, &recomp_gen::fn_sub_57C680_0057c680, &recomp_gen::fn_sub_57C680_0057c680__recomp},
    {"sub_57C6E0", 0x57C6E0, &recomp_gen::fn_sub_57C6E0_0057c6e0, &recomp_gen::fn_sub_57C6E0_0057c6e0__recomp},
    {"sub_57C800", 0x57C800, &recomp_gen::fn_sub_57C800_0057c800, &recomp_gen::fn_sub_57C800_0057c800__recomp},
    {"sub_57C910", 0x57C910, &recomp_gen::fn_sub_57C910_0057c910, &recomp_gen::fn_sub_57C910_0057c910__recomp},
    {"sub_57CA78", 0x57CA78, &recomp_gen::fn_sub_57CA78_0057ca78, &recomp_gen::fn_sub_57CA78_0057ca78__recomp},
    {"sub_57D1D0", 0x57D1D0, &recomp_gen::fn_sub_57D1D0_0057d1d0, &recomp_gen::fn_sub_57D1D0_0057d1d0__recomp},
    {"sub_57D208", 0x57D208, &recomp_gen::fn_sub_57D208_0057d208, &recomp_gen::fn_sub_57D208_0057d208__recomp},
    {"sub_57D220", 0x57D220, &recomp_gen::fn_sub_57D220_0057d220, &recomp_gen::fn_sub_57D220_0057d220__recomp},
    {"sub_57D308", 0x57D308, &recomp_gen::fn_sub_57D308_0057d308, &recomp_gen::fn_sub_57D308_0057d308__recomp},
    {"sub_57D380", 0x57D380, &recomp_gen::fn_sub_57D380_0057d380, &recomp_gen::fn_sub_57D380_0057d380__recomp},
    {"sub_57D3C8", 0x57D3C8, &recomp_gen::fn_sub_57D3C8_0057d3c8, &recomp_gen::fn_sub_57D3C8_0057d3c8__recomp},
    {"sub_57D5B0", 0x57D5B0, &recomp_gen::fn_sub_57D5B0_0057d5b0, &recomp_gen::fn_sub_57D5B0_0057d5b0__recomp},
    {"sub_57D5D8", 0x57D5D8, &recomp_gen::fn_sub_57D5D8_0057d5d8, &recomp_gen::fn_sub_57D5D8_0057d5d8__recomp},
    {"sub_57D960", 0x57D960, &recomp_gen::fn_sub_57D960_0057d960, &recomp_gen::fn_sub_57D960_0057d960__recomp},
    {"sub_57D9B0", 0x57D9B0, &recomp_gen::fn_sub_57D9B0_0057d9b0, &recomp_gen::fn_sub_57D9B0_0057d9b0__recomp},
    {"sub_57DA08", 0x57DA08, &recomp_gen::fn_sub_57DA08_0057da08, &recomp_gen::fn_sub_57DA08_0057da08__recomp},
    {"sub_57DA90", 0x57DA90, &recomp_gen::fn_sub_57DA90_0057da90, &recomp_gen::fn_sub_57DA90_0057da90__recomp},
    {"sub_57DC80", 0x57DC80, &recomp_gen::fn_sub_57DC80_0057dc80, &recomp_gen::fn_sub_57DC80_0057dc80__recomp},
    {"sub_57DC90", 0x57DC90, &recomp_gen::fn_sub_57DC90_0057dc90, &recomp_gen::fn_sub_57DC90_0057dc90__recomp},
    {"sub_57DF60", 0x57DF60, &recomp_gen::fn_sub_57DF60_0057df60, &recomp_gen::fn_sub_57DF60_0057df60__recomp},
    {"sub_57DFB0", 0x57DFB0, &recomp_gen::fn_sub_57DFB0_0057dfb0, &recomp_gen::fn_sub_57DFB0_0057dfb0__recomp},
    {"sub_57E028", 0x57E028, &recomp_gen::fn_sub_57E028_0057e028, &recomp_gen::fn_sub_57E028_0057e028__recomp},
    {"sub_57E070", 0x57E070, &recomp_gen::fn_sub_57E070_0057e070, &recomp_gen::fn_sub_57E070_0057e070__recomp},
    {"sub_57E110", 0x57E110, &recomp_gen::fn_sub_57E110_0057e110, &recomp_gen::fn_sub_57E110_0057e110__recomp},
    {"sub_57E148", 0x57E148, &recomp_gen::fn_sub_57E148_0057e148, &recomp_gen::fn_sub_57E148_0057e148__recomp},
    {"sub_57E180", 0x57E180, &recomp_gen::fn_sub_57E180_0057e180, &recomp_gen::fn_sub_57E180_0057e180__recomp},
    {"sub_57E1D0", 0x57E1D0, &recomp_gen::fn_sub_57E1D0_0057e1d0, &recomp_gen::fn_sub_57E1D0_0057e1d0__recomp},
    {"sub_57E1D8", 0x57E1D8, &recomp_gen::fn_sub_57E1D8_0057e1d8, &recomp_gen::fn_sub_57E1D8_0057e1d8__recomp},
    {"sub_57E210", 0x57E210, &recomp_gen::fn_sub_57E210_0057e210, &recomp_gen::fn_sub_57E210_0057e210__recomp},
    {"sub_57E270", 0x57E270, &recomp_gen::fn_sub_57E270_0057e270, &recomp_gen::fn_sub_57E270_0057e270__recomp},
    {"sub_57E290", 0x57E290, &recomp_gen::fn_sub_57E290_0057e290, &recomp_gen::fn_sub_57E290_0057e290__recomp},
    {"sub_57E298", 0x57E298, &recomp_gen::fn_sub_57E298_0057e298, &recomp_gen::fn_sub_57E298_0057e298__recomp},
    {"sub_57E320", 0x57E320, &recomp_gen::fn_sub_57E320_0057e320, &recomp_gen::fn_sub_57E320_0057e320__recomp},
    {"sub_57E360", 0x57E360, &recomp_gen::fn_sub_57E360_0057e360, &recomp_gen::fn_sub_57E360_0057e360__recomp},
    {"sub_57E378", 0x57E378, &recomp_gen::fn_sub_57E378_0057e378, &recomp_gen::fn_sub_57E378_0057e378__recomp},
    {"sub_57E3D0", 0x57E3D0, &recomp_gen::fn_sub_57E3D0_0057e3d0, &recomp_gen::fn_sub_57E3D0_0057e3d0__recomp},
    {"sub_57E428", 0x57E428, &recomp_gen::fn_sub_57E428_0057e428, &recomp_gen::fn_sub_57E428_0057e428__recomp},
    {"sub_57E530", 0x57E530, &recomp_gen::fn_sub_57E530_0057e530, &recomp_gen::fn_sub_57E530_0057e530__recomp},
    {"sub_57E698", 0x57E698, &recomp_gen::fn_sub_57E698_0057e698, &recomp_gen::fn_sub_57E698_0057e698__recomp},
    {"sub_57E6E0", 0x57E6E0, &recomp_gen::fn_sub_57E6E0_0057e6e0, &recomp_gen::fn_sub_57E6E0_0057e6e0__recomp},
    {"sub_57E730", 0x57E730, &recomp_gen::fn_sub_57E730_0057e730, &recomp_gen::fn_sub_57E730_0057e730__recomp},
    {"sub_57E910", 0x57E910, &recomp_gen::fn_sub_57E910_0057e910, &recomp_gen::fn_sub_57E910_0057e910__recomp},
    {"sub_57E9A8", 0x57E9A8, &recomp_gen::fn_sub_57E9A8_0057e9a8, &recomp_gen::fn_sub_57E9A8_0057e9a8__recomp},
    {"sub_57E9D8", 0x57E9D8, &recomp_gen::fn_sub_57E9D8_0057e9d8, &recomp_gen::fn_sub_57E9D8_0057e9d8__recomp},
    {"sub_57EA18", 0x57EA18, &recomp_gen::fn_sub_57EA18_0057ea18, &recomp_gen::fn_sub_57EA18_0057ea18__recomp},
    {"sub_57EA80", 0x57EA80, &recomp_gen::fn_sub_57EA80_0057ea80, &recomp_gen::fn_sub_57EA80_0057ea80__recomp},
    {"sub_57EB38", 0x57EB38, &recomp_gen::fn_sub_57EB38_0057eb38, &recomp_gen::fn_sub_57EB38_0057eb38__recomp},
    {"sub_57EB80", 0x57EB80, &recomp_gen::fn_sub_57EB80_0057eb80, &recomp_gen::fn_sub_57EB80_0057eb80__recomp},
    {"sub_57EC00", 0x57EC00, &recomp_gen::fn_sub_57EC00_0057ec00, &recomp_gen::fn_sub_57EC00_0057ec00__recomp},
    {"sub_57EC38", 0x57EC38, &recomp_gen::fn_sub_57EC38_0057ec38, &recomp_gen::fn_sub_57EC38_0057ec38__recomp},
    {"sub_57ED00", 0x57ED00, &recomp_gen::fn_sub_57ED00_0057ed00, &recomp_gen::fn_sub_57ED00_0057ed00__recomp},
    {"sub_57ED40", 0x57ED40, &recomp_gen::fn_sub_57ED40_0057ed40, &recomp_gen::fn_sub_57ED40_0057ed40__recomp},
    {"sub_57EDA8", 0x57EDA8, &recomp_gen::fn_sub_57EDA8_0057eda8, &recomp_gen::fn_sub_57EDA8_0057eda8__recomp},
    {"sub_57EDD8", 0x57EDD8, &recomp_gen::fn_sub_57EDD8_0057edd8, &recomp_gen::fn_sub_57EDD8_0057edd8__recomp},
    {"sub_57EE50", 0x57EE50, &recomp_gen::fn_sub_57EE50_0057ee50, &recomp_gen::fn_sub_57EE50_0057ee50__recomp},
    {"sub_57EF08", 0x57EF08, &recomp_gen::fn_sub_57EF08_0057ef08, &recomp_gen::fn_sub_57EF08_0057ef08__recomp},
    {"sub_57EF78", 0x57EF78, &recomp_gen::fn_sub_57EF78_0057ef78, &recomp_gen::fn_sub_57EF78_0057ef78__recomp},
    {"sub_57F050", 0x57F050, &recomp_gen::fn_sub_57F050_0057f050, &recomp_gen::fn_sub_57F050_0057f050__recomp},
    {"sub_57F058", 0x57F058, &recomp_gen::fn_sub_57F058_0057f058, &recomp_gen::fn_sub_57F058_0057f058__recomp},
    {"sub_57F0A8", 0x57F0A8, &recomp_gen::fn_sub_57F0A8_0057f0a8, &recomp_gen::fn_sub_57F0A8_0057f0a8__recomp},
    {"sub_57F600", 0x57F600, &recomp_gen::fn_sub_57F600_0057f600, &recomp_gen::fn_sub_57F600_0057f600__recomp},
    {"sub_57F670", 0x57F670, &recomp_gen::fn_sub_57F670_0057f670, &recomp_gen::fn_sub_57F670_0057f670__recomp},
    {"sub_57F6F8", 0x57F6F8, &recomp_gen::fn_sub_57F6F8_0057f6f8, &recomp_gen::fn_sub_57F6F8_0057f6f8__recomp},
    {"sub_57F750", 0x57F750, &recomp_gen::fn_sub_57F750_0057f750, &recomp_gen::fn_sub_57F750_0057f750__recomp},
    {"sub_57F768", 0x57F768, &recomp_gen::fn_sub_57F768_0057f768, &recomp_gen::fn_sub_57F768_0057f768__recomp},
    {"sub_57F920", 0x57F920, &recomp_gen::fn_sub_57F920_0057f920, &recomp_gen::fn_sub_57F920_0057f920__recomp},
    {"sub_57F980", 0x57F980, &recomp_gen::fn_sub_57F980_0057f980, &recomp_gen::fn_sub_57F980_0057f980__recomp},
    {"sub_57FA28", 0x57FA28, &recomp_gen::fn_sub_57FA28_0057fa28, &recomp_gen::fn_sub_57FA28_0057fa28__recomp},
    {"sub_57FA50", 0x57FA50, &recomp_gen::fn_sub_57FA50_0057fa50, &recomp_gen::fn_sub_57FA50_0057fa50__recomp},
    {"sub_57FA70", 0x57FA70, &recomp_gen::fn_sub_57FA70_0057fa70, &recomp_gen::fn_sub_57FA70_0057fa70__recomp},
    {"sub_57FAB8", 0x57FAB8, &recomp_gen::fn_sub_57FAB8_0057fab8, &recomp_gen::fn_sub_57FAB8_0057fab8__recomp},
    {"sub_57FAF0", 0x57FAF0, &recomp_gen::fn_sub_57FAF0_0057faf0, &recomp_gen::fn_sub_57FAF0_0057faf0__recomp},
    {"sub_57FC90", 0x57FC90, &recomp_gen::fn_sub_57FC90_0057fc90, &recomp_gen::fn_sub_57FC90_0057fc90__recomp},
    {"sub_57FCB0", 0x57FCB0, &recomp_gen::fn_sub_57FCB0_0057fcb0, &recomp_gen::fn_sub_57FCB0_0057fcb0__recomp},
    {"r_lock_def_free_2", 0x57FD58, &recomp_gen::fn_r_lock_def_free_2_0057fd58, &recomp_gen::fn_r_lock_def_free_2_0057fd58__recomp},
    {"r_lock_def_get_free_item_2", 0x57FD78, &recomp_gen::fn_r_lock_def_get_free_item_2_0057fd78, &recomp_gen::fn_r_lock_def_get_free_item_2_0057fd78__recomp},
};

// --- worlds and helpers -------------------------------------------------------------------------------------------------

// The random world of the generic sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// The meaningful worlds: free RAM far above .bss and below the stand-in heap (0x1C00000).
constexpr u32 kStr = 0x01900000u;     // input strings
constexpr u32 kFmt = 0x01901000u;     // formats
constexpr u32 kOut = 0x01902000u;     // outputs (words, strings)
constexpr u32 kFile = 0x01903000u;    // a FILE (88 bytes), a glue list, fake records
constexpr u32 kFree = 0x01904000u;    // the Bigint free-list table and its blocks (32 KiB)
constexpr u32 kBigA = 0x0190C000u;    // built Bigints
constexpr u32 kBigB = 0x0190D000u;
constexpr u32 kArr = 0x01910000u;     // qsort arrays (64 KiB)
constexpr u32 kBuf = 0x01920000u;     // movie data / elementary streams (256 KiB)
constexpr u32 kHandle = 0x01960000u;  // fake handles (MPS, MPV, players)
constexpr u32 kWork = 0x01970000u;    // pool work areas (128 KiB)
constexpr u32 kStrcmp = 0x524128u;    // strcmp (libc slice) as the qsort comparator
constexpr u32 kStrlen = 0x524388u;    // strlen (libc slice) as a callback that returns something of its argument
constexpr u32 kEofread = 0x523B38u;   // eofread: the read callback of a string FILE

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}
std::map<std::string, int> g_pairs;  // pairs per function, per section
// One hand / recompiled pair of `fn` (both from the same state; the recompiled run's memory stays in place). `more` =
// $t0..$t3 (arguments 5..8).
hgp::Run pair_fn(Machine& m, const char* fn, Args a, u32 seed, std::vector<u64> more = {}) {
    const Case& c = find_case(fn);
    HwCheck hw;
    for (std::size_t i = 0; i < more.size(); ++i) hw.gpr_in[GPR_T0 + static_cast<unsigned>(i)] = more[i];
    ++g_pairs[fn];
    return hgp::pair(m, c.hand, c.recomp, a, seed, fn, hw);
}
u64 v0_64(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u32 v0_of(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
s32 sv0(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }
u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
s32 gs32(Machine& m, u32 va) { return static_cast<s32>(g32(m, va)); }
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u16 g16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void p16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u64 g64(Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.at(va), 8);
    return v;
}
void p64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
u64 dbits(double d) {
    u64 b;
    std::memcpy(&b, &d, 8);
    return b;
}
double bitsd(u64 b) {
    double d;
    std::memcpy(&d, &b, 8);
    return d;
}
float bitsf(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
s64 ulps_d(double a, double b) {
    auto key = [](double x) {
        const s64 i = static_cast<s64>(dbits(x));
        return i < 0 ? static_cast<s64>(0x8000000000000000ull) - i : i;
    };
    const s64 d = key(a) - key(b);
    return d < 0 ? -d : d;
}
s64 ulps_f(float a, float b) {
    auto key = [](float x) {
        const s32 i = static_cast<s32>(fbits(x));
        return i < 0 ? static_cast<s64>(INT32_MIN) - i : static_cast<s64>(i);
    };
    const s64 d = key(a) - key(b);
    return d < 0 ? -d : d;
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
u32 reent_of(Machine& m) { return g32(m, libc::kImpurePtr); }
// A run that must reach the return: says where it stopped otherwise.
#define REQUIRE_RUN(r)                                                                                      \
    do {                                                                                                    \
        if ((r).stopped) MESSAGE("stopped: " << (r).what << " at 0x" << std::hex << (r).stop_pc << std::dec); \
        REQUIRE_FALSE((r).stopped);                                                                         \
    } while (0)

// mprec's Bigint free lists, filled so that _Balloc never has to allocate (_calloc_r is not emitted in this build):
// the _reent's table (+0x4C) points at kFree, and every size class 0..7 gets a chain of blocks with k / maxwds set.
void seed_freelists(Machine& m, u32 reent, u32 per_class = 10) {
    std::memset(m.at(kFree), 0, 0x8000);
    u32 next_block = kFree + 0x100;
    for (u32 k = 0; k < 8; ++k) {
        u32 head = 0;
        const u32 bytes = (24 + 4 * ((1u << k) - 1) + 7) & ~7u;
        for (u32 i = 0; i < per_class; ++i) {
            const u32 b = next_block;
            next_block += bytes;
            p32(m, b + libc::bigint::kNext, head);
            p32(m, b + libc::bigint::kK, k);
            p32(m, b + libc::bigint::kMaxWds, 1u << k);
            head = b;
        }
        p32(m, kFree + 4 * k, head);
    }
    REQUIRE(next_block < kFree + 0x8000);
    p32(m, reent + libc::reent::kFreelist, kFree);
    p32(m, reent + libs3::reent::kP5s, 0);  // _pow5mult's cached 5^4 chain lived in the blocks just overwritten
}

using Big = std::vector<u32>;  // little-endian words
void trim(Big& a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}
Big big_mul(const Big& a, const Big& b) {
    Big r(a.size() + b.size(), 0);
    for (std::size_t i = 0; i < a.size(); ++i) {
        u64 carry = 0;
        for (std::size_t j = 0; j < b.size(); ++j) {
            const u64 t = static_cast<u64>(a[i]) * b[j] + r[i + j] + carry;
            r[i + j] = static_cast<u32>(t);
            carry = t >> 32;
        }
        r[i + b.size()] = static_cast<u32>(carry);
    }
    trim(r);
    return r;
}
Big big_shl(const Big& a, u32 k) {
    Big r(k / 32, 0);
    const u32 s = k % 32;
    u32 carry = 0;
    for (u32 w : a) {
        r.push_back(s ? (w << s) | carry : w);
        carry = s ? w >> (32 - s) : 0;
    }
    r.push_back(carry);
    trim(r);
    return r;
}
int big_cmp(const Big& a, const Big& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (std::size_t i = a.size(); i-- > 0;)
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}
Big big_sub(const Big& a, const Big& b) {  // a >= b
    Big r(a.size());
    s64 borrow = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        s64 t = static_cast<s64>(a[i]) - (i < b.size() ? b[i] : 0) - borrow;
        borrow = t < 0;
        r[i] = static_cast<u32>(t);
    }
    trim(r);
    return r;
}
void put_big(Machine& m, u32 va, const Big& w, u32 k) {
    p32(m, va + libc::bigint::kNext, 0);
    p32(m, va + libc::bigint::kK, k);
    p32(m, va + libc::bigint::kMaxWds, 1u << k);
    p32(m, va + libc::bigint::kSign, 0);
    p32(m, va + libc::bigint::kWds, static_cast<u32>(w.size()));
    for (std::size_t i = 0; i < w.size(); ++i) p32(m, va + libc::bigint::kX + 4 * static_cast<u32>(i), w[i]);
}
Big get_big(Machine& m, u32 va) {
    Big w(g32(m, va + libc::bigint::kWds));
    for (std::size_t i = 0; i < w.size(); ++i) w[i] = g32(m, va + libc::bigint::kX + 4 * static_cast<u32>(i));
    return w;
}
u32 k_for(std::size_t words) {
    u32 k = 0;
    while ((static_cast<std::size_t>(1) << k) < words) ++k;
    return k;
}

// A read-only string FILE as sscanf builds it (flags 4, buffer = the string, read callback eofread).
void make_string_file(Machine& m, u32 fp, u32 base, u32 pos, u32 left, u32 reent) {
    std::memset(m.at(fp), 0, libs3::file::kSize);
    p16(m, fp + libc::file::kFlags, 4);
    p16(m, fp + libc::file::kFile, 0xFFFF);
    p32(m, fp + libc::file::kP, pos);
    p32(m, fp + libc::file::kR, left);
    p32(m, fp + libc::file::kBufBase, base);
    p32(m, fp + libc::file::kBufSize, pos - base + left);
    p32(m, fp + libc::file::kCookie, fp);
    p32(m, fp + libc::file::kRead, kEofread);
    p32(m, fp + libc::file::kData, reent);
}

// --- the movies of the disc (MPEG program streams) ---------------------------------------------------------------------
std::string sfd_dir() { return extracted_root() + "/DATA/SFD"; }
struct Movie {
    std::string name;
    std::vector<u8> data;  // the first 256 KiB
};
std::vector<Movie> movies() {
    std::vector<Movie> out;
    std::error_code ec;
    for (const auto& e : std::filesystem::directory_iterator(sfd_dir(), ec)) {
        if (!e.is_regular_file()) continue;
        std::ifstream f(e.path(), std::ios::binary);
        Movie mv{e.path().filename().string(), std::vector<u8>(256 * 1024)};
        f.read(reinterpret_cast<char*>(mv.data.data()), static_cast<std::streamsize>(mv.data.size()));
        mv.data.resize(static_cast<std::size_t>(f.gcount()));
        out.push_back(std::move(mv));
    }
    std::sort(out.begin(), out.end(), [](const Movie& a, const Movie& b) { return a.name < b.name; });
    return out;
}
bool is_code(const std::vector<u8>& d, std::size_t i, u8 code) {
    return i + 4 <= d.size() && d[i] == 0 && d[i + 1] == 0 && d[i + 2] == 1 && d[i + 3] == code;
}
// A host walk of the program stream (ISO/IEC 11172-1 / 13818-1): the packs, and the payload of one stream id.
struct Pack {
    std::size_t at;         // the pack start code
    bool mpeg2;             // '01' after the code
    std::size_t len;        // pack header length
    bool system;            // a system header follows
    std::size_t first_pes;  // offset of the first PES packet after the header(s)
    u8 stream_id;           // its stream id
    std::size_t pes_hdr;    // bytes of that PES packet's header (up to its payload)
};
std::size_t pes_header_len(const std::vector<u8>& d, std::size_t p, bool& ok) {
    ok = false;
    if (p + 6 > d.size()) return 0;
    const u8 id = d[p + 3];
    if (id == 0xBE || id == 0xBF) {
        ok = true;
        return 6;
    }
    std::size_t q = p + 6;
    if (q < d.size() && (d[q] & 0xC0) == 0x80) {  // MPEG-2 PES header
        if (q + 3 > d.size()) return 0;
        ok = true;
        return 9 + d[q + 2];
    }
    while (q < d.size() && d[q] == 0xFF) ++q;  // MPEG-1: stuffing
    if (q < d.size() && (d[q] & 0xC0) == 0x40) q += 2;  // STD buffer
    if (q >= d.size()) return 0;
    if ((d[q] & 0xF0) == 0x20) q += 5;
    else if ((d[q] & 0xF0) == 0x30) q += 10;
    else if (d[q] == 0x0F) q += 1;
    else return 0;
    ok = true;
    return q - p;
}
std::vector<Pack> packs(const std::vector<u8>& d, std::size_t max) {
    std::vector<Pack> out;
    std::size_t i = 0;
    while (i + 14 < d.size() && out.size() < max) {
        if (!is_code(d, i, 0xBA)) {
            ++i;
            continue;
        }
        Pack pk{};
        pk.at = i;
        pk.mpeg2 = (d[i + 4] & 0xC0) == 0x40;
        pk.len = pk.mpeg2 ? 14 + (d[i + 13] & 7) : 12;
        std::size_t q = i + pk.len;
        if (is_code(d, q, 0xBB)) {
            pk.system = true;
            q += 6 + ((std::size_t(d[q + 4]) << 8) | d[q + 5]);
        }
        if (q + 6 <= d.size() && d[q] == 0 && d[q + 1] == 0 && d[q + 2] == 1 && d[q + 3] >= 0xBC) {
            pk.first_pes = q;
            pk.stream_id = d[q + 3];
            bool ok = false;
            pk.pes_hdr = pes_header_len(d, q, ok);
            if (ok) out.push_back(pk);
        }
        i += pk.len;
    }
    return out;
}
std::vector<u8> elementary(const std::vector<u8>& d, u8 sid) {
    std::vector<u8> es;
    std::size_t i = 0;
    while (i + 6 < d.size()) {
        if (!(d[i] == 0 && d[i + 1] == 0 && d[i + 2] == 1)) {
            ++i;
            continue;
        }
        const u8 code = d[i + 3];
        if (code == 0xBA) {
            i += (d[i + 4] & 0xC0) == 0x40 ? 14 + (d[i + 13] & 7) : 12;
            continue;
        }
        if (code < 0xBB) {
            ++i;
            continue;
        }
        const std::size_t plen = (std::size_t(d[i + 4]) << 8) | d[i + 5];
        if (i + 6 + plen > d.size()) break;
        if (code == sid) {
            bool ok = false;
            const std::size_t h = pes_header_len(d, i, ok);
            if (ok && h <= 6 + plen) es.insert(es.end(), d.begin() + static_cast<std::ptrdiff_t>(i + h), d.begin() + static_cast<std::ptrdiff_t>(i + 6 + plen));
        }
        i += 6 + plen;
    }
    return es;
}
// ISO/IEC 13818-2: is there a sequence_extension (0x1B5 with identifier 1) right after the first sequence header?
bool host_is_mpeg2(const std::vector<u8>& es) {
    for (std::size_t i = 0; i + 4 <= es.size(); ++i) {
        if (!is_code(es, i, 0xB3)) continue;
        for (std::size_t j = i + 4; j + 4 < es.size(); ++j)
            if (es[j] == 0 && es[j + 1] == 0 && es[j + 2] == 1) return es[j + 3] == 0xB5 && (es[j + 4] >> 4) == 1;
        return false;
    }
    return false;
}

}  // namespace

// ======================================================================================================================
// 1. The generic sweep: every body against its recompiled body on random worlds (mostly bad-input paths).
TEST_CASE("game(libs3): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    u32 pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (u64& x : args) x = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("generic sweep: " << pairs << " pairs, " << stops << " stopped early (identically)");
}

// ======================================================================================================================
// 2. sscanf / _sscanf_r (the string FILE, __svfscanf_r, __srefill, ungetc) against the host's sscanf.
TEST_CASE("game(libs3): sscanf converts like the host's sscanf") {
    auto m = machine();
    if (!m) return;
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    struct Conv {
        const char* in;
        const char* fmt;
        const char* kinds;  // per output: i = int, s = string, c = char, d = double, f = float
    };
    const Conv convs[] = {
        {"  123 -45 0x1f", "%d %d %x", "iii"},   {"abc defgh", "%s %3s", "ss"},      {"hello, world", "%[^,], %s", "ss"},
        {"077 1010 -12", "%o %i %i", "iii"},     {"x=42;y=7", "x=%d;y=%d", "ii"},    {"12345678", "%3d%2d%d", "iii"},
        {"-0 +17", "%u %u", "ii"},               {"zzz", "%d", "i"},                 {"", "%d", "i"},
        {"1 2", "%*d %d", "i"},             {"0x7fffffff", "%i", "i"},
        {"aaa123bbb", "%[a]%d%[b]", "sis"},      {"3.25 -0.5", "%f %lf", "fd"},      {"   +6.125e1", "%lf", "d"},
        {"1e3 .5", "%f %f", "ff"},               {"tab\tsep\nline", "%s %s %s", "sss"}, {"5;", "%d;%d", "ii"},
        {"0100 017", "%i %i", "ii"},             {"ff FF 10", "%x %X %o", "iii"},
    };
    for (const Conv& c : convs) {
        INFO("sscanf(\"" << std::string(c.in) << "\", \"" << std::string(c.fmt) << "\")");
        const std::size_t n = std::strlen(c.kinds);
        // the host's results
        int hi[6] = {};
        char hs[6][64] = {};
        double hd[6] = {};
        float hf[6] = {};
        void* hp[6];
        for (std::size_t i = 0; i < n; ++i) {
            const char k = c.kinds[i];
            hp[i] = k == 'i' ? static_cast<void*>(&hi[i]) : k == 'd' ? static_cast<void*>(&hd[i]) : k == 'f' ? static_cast<void*>(&hf[i]) : static_cast<void*>(hs[i]);
        }
        for (std::size_t i = n; i < 6; ++i) hp[i] = nullptr;
        const int hret = std::sscanf(c.in, c.fmt, hp[0], hp[1], hp[2], hp[3], hp[4], hp[5]);
        for (int which = 0; which < 2; ++which) {
            m->put(kStr, c.in);
            m->put(kFmt, c.fmt);
            std::memset(m->at(kOut), 0, 0x800);
            seed_freelists(*m, reent);
            std::vector<u64> ptrs;
            for (std::size_t i = 0; i < n; ++i) ptrs.push_back(sx(kOut + 0x100 * static_cast<u32>(i)));
            hgp::Run r;
            if (which == 0) {
                ptrs.resize(6, 0);
                r = pair_fn(*m, "sscanf", {sx(kStr), sx(kFmt), ptrs[0], ptrs[1]}, seed++, {ptrs[2], ptrs[3], ptrs[4], ptrs[5]});
            } else {
                ptrs.resize(5, 0);
                r = pair_fn(*m, "_sscanf_r", {sx(reent), sx(kStr), sx(kFmt), ptrs[0]}, seed++, {ptrs[1], ptrs[2], ptrs[3], ptrs[4]});
            }
            REQUIRE_RUN(r);
            CHECK(sv0(r) == hret);
            for (std::size_t i = 0; i < n && static_cast<int>(i) < hret; ++i) {
                const u32 at = kOut + 0x100 * static_cast<u32>(i);
                const char k = c.kinds[i];
                if (k == 'i') CHECK(gs32(*m, at) == hi[i]);
                if (k == 's') CHECK(m->str(at) == hs[i]);
                if (k == 'c') CHECK(static_cast<char>(m->at(at)[0]) == hs[i][0]);
                if (k == 'd') CHECK(bitsd(g64(*m, at)) == hd[i]);
                if (k == 'f') CHECK(bitsf(g32(*m, at)) == hf[i]);
            }
        }
    }
    // random integers in three bases, formatted on the host, read back
    std::mt19937 rng{0x5CA4u};
    for (int i = 0; i < 40; ++i) {
        const s32 a = static_cast<s32>(rng());
        const u32 b = rng();
        const u32 c = rng() >> 8;
        char text[96];
        std::snprintf(text, sizeof text, "%d  %x\t%o", a, b, c);
        m->put(kStr, text);
        m->put(kFmt, "%d %x %o");
        std::memset(m->at(kOut), 0, 0x400);
        hgp::Run r = pair_fn(*m, "sscanf", {sx(kStr), sx(kFmt), sx(kOut), sx(kOut + 4)}, seed++, {sx(kOut + 8)});
        CHECK(sv0(r) == 3);
        CHECK(gs32(*m, kOut) == a);
        CHECK(g32(*m, kOut + 4) == b);
        CHECK(g32(*m, kOut + 8) == c);
    }
    report("sscanf");
}

// ======================================================================================================================
// 3. sprintf_r / vsprintf_r (the string FILE around the recompiled vfprintf) against the host's snprintf.
TEST_CASE("game(libs3): sprintf_r and vsprintf_r format like the host") {
    auto m = machine();
    if (!m) return;
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    std::mt19937 rng{0x5F7u};
    struct Fmt {
        const char* fmt;
        int nargs;   // integer arguments (strings are given as 's' in kinds)
        const char* kinds;
    };
    const Fmt fmts[] = {{"%d", 1, "i"},          {"[%5d|%-5d|%05d]", 3, "iii"}, {"%x %X %o", 3, "iii"}, {"%u", 1, "i"},
                        {"%+d % d", 2, "ii"},    {"%c%c%%", 2, "ii"},           {"<%s|%10s|%-6s|%.3s>", 4, "ssss"},
                        {"%#x %#o", 2, "ii"},    {"%ld", 1, "l"},               {"%s=%d", 2, "si"}};
    const char* words[] = {"", "a", "hello", "Persona", "0123456789AB"};
    for (const Fmt& f : fmts) {
        for (int round = 0; round < 6; ++round) {
            u64 args[4] = {};
            char host[256];
            std::vector<std::string> strs;
            long long hv[4] = {};
            for (int i = 0; i < f.nargs; ++i) {
                const char k = f.kinds[i];
                if (k == 's') {
                    const u32 w = rng() % 5;
                    strs.push_back(words[w]);
                    m->put(kStr + 0x100 * static_cast<u32>(i), words[w]);
                    args[i] = sx(kStr + 0x100 * static_cast<u32>(i));
                } else if (k == 'l') {
                    const u64 hi = rng();
                    const u64 lo = rng();
                    hv[i] = static_cast<long long>((hi << 32) | lo);
                    args[i] = static_cast<u64>(hv[i]);
                } else {
                    const u32 sel = rng() % 4;
                    const u32 raw = rng();
                    const s32 v = sel == 0 ? static_cast<s32>(raw % 100) : sel == 1 ? -static_cast<s32>(raw % 1000) : static_cast<s32>(raw);
                    hv[i] = v;
                    args[i] = sx(static_cast<u32>(v));
                    if (std::strchr("cC", f.fmt[1])) args[i] = 'A' + raw % 26, hv[i] = static_cast<long long>(args[i]);
                }
            }
            // the host's text (the same arguments; %ld is 64-bit on the EE)
            std::string hf = f.fmt;
            for (std::size_t p = hf.find("%ld"); p != std::string::npos; p = hf.find("%ld")) hf.replace(p, 3, "%lld");
            auto sarg = [&](int i) { return strs.empty() ? "" : strs[std::min<std::size_t>(static_cast<std::size_t>(std::count(f.kinds, f.kinds + i, 's')), strs.size() - 1)].c_str(); };
            if (std::string(f.kinds) == "ssss") std::snprintf(host, sizeof host, hf.c_str(), strs[0].c_str(), strs[1].c_str(), strs[2].c_str(), strs[3].c_str());
            else if (std::string(f.kinds) == "si") std::snprintf(host, sizeof host, hf.c_str(), sarg(0), static_cast<int>(hv[1]));
            else if (std::string(f.kinds) == "l") std::snprintf(host, sizeof host, hf.c_str(), hv[0]);
            else std::snprintf(host, sizeof host, hf.c_str(), static_cast<int>(hv[0]), static_cast<int>(hv[1]), static_cast<int>(hv[2]), static_cast<int>(hv[3]));
            INFO("format " << f.fmt << " -> host \"" << host << "\"");
            m->put(kFmt, f.fmt);
            std::memset(m->at(kOut), 0x5A, 0x200);
            hgp::Run r = pair_fn(*m, "_sprintf_r", {sx(reent), sx(kOut), sx(kFmt), args[0]}, seed++, {args[1], args[2], args[3]});
            REQUIRE_RUN(r);
            CHECK(m->str(kOut) == host);
            CHECK(sv0(r) == static_cast<s32>(std::strlen(host)));
            // vsprintf_r: the same arguments as a va_list of 8-byte slots
            for (int i = 0; i < 4; ++i) p64(*m, kStr + 0x800 + 8 * static_cast<u32>(i), args[i]);
            std::memset(m->at(kOut), 0x5A, 0x200);
            r = pair_fn(*m, "_vsprintf_r", {sx(reent), sx(kOut), sx(kFmt), sx(kStr + 0x800)}, seed++);
            REQUIRE_RUN(r);
            CHECK(m->str(kOut) == host);
        }
    }
    report("sprintf_r / vsprintf_r");
}

// ======================================================================================================================
// 4. The FILE leaves on built FILEs: ungetc on a string FILE, lflush's test.
TEST_CASE("game(libs3): ungetc and lflush on built FILEs") {
    auto m = machine();
    if (!m) return;
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    const u32 fp = kFile;
    m->put(kStr, "abcdef");
    // ungetc of the byte just read backs up inside the buffer
    make_string_file(*m, fp, kStr, kStr + 3, 3, reent);
    hgp::Run r = pair_fn(*m, "ungetc", {'c', sx(fp), 0, 0}, seed++);
    CHECK(sv0(r) == 'c');
    CHECK(g32(*m, fp + libc::file::kP) == kStr + 2);
    CHECK(gs32(*m, fp + libc::file::kR) == 4);
    // EOF is refused
    make_string_file(*m, fp, kStr, kStr + 3, 3, reent);
    r = pair_fn(*m, "ungetc", {sx(0xFFFFFFFFu), sx(fp), 0, 0}, seed++);
    CHECK(sv0(r) == -1);
    // another byte: the ungetc buffer (the FILE's own 3 bytes), the read position saved
    make_string_file(*m, fp, kStr, kStr + 3, 3, reent);
    r = pair_fn(*m, "ungetc", {'X', sx(fp), 0, 0}, seed++);
    CHECK(sv0(r) == 'X');
    CHECK(g32(*m, fp + libs3::file::kUbBase) == fp + libs3::file::kUbuf);
    CHECK(g32(*m, fp + libs3::file::kUp) == kStr + 3);
    CHECK(gs32(*m, fp + libs3::file::kUr) == 3);
    CHECK(gs32(*m, fp + libc::file::kR) == 1);
    CHECK(m->at(g32(*m, fp + libc::file::kP))[0] == 'X');
    // a second push goes below it in the same buffer
    r = pair_fn(*m, "ungetc", {'Y', sx(fp), 0, 0}, seed++);
    CHECK(sv0(r) == 'Y');
    CHECK(gs32(*m, fp + libc::file::kR) == 2);
    // ungetc clears EOF
    make_string_file(*m, fp, kStr, kStr + 6, 0, reent);
    p16(*m, fp + libc::file::kFlags, static_cast<u16>(g16(*m, fp + libc::file::kFlags) | libs3::file::kFlagEof));
    r = pair_fn(*m, "ungetc", {'z', sx(fp), 0, 0}, seed++);
    CHECK((g16(*m, fp + libc::file::kFlags) & libs3::file::kFlagEof) == 0);

    // lflush: 0 unless line buffered and writing; then fflush (libs1's hand-written one, so both runs execute it),
    // which returns 0 on this FILE with no buffer
    for (const u16 fl : {u16{0}, u16{1}, u16{8}, u16{0x18}, u16{0x11}, u16{9}, u16{0x29}}) {
        std::memset(m->at(fp), 0, libs3::file::kSize);
        p16(*m, fp + libc::file::kFlags, fl);
        r = pair_fn(*m, "lflush", {sx(fp), 0, 0, 0}, seed++);
        CHECK_FALSE(r.stopped);
        CHECK(sv0(r) == 0);
    }
    report("FILE leaves");
}

// ======================================================================================================================
// 5. strtod / strtodf / _strtod_r against the host: the double equals the host's for every normal result (the Bigint
//    correction makes it exact even on the truncating soft-float library); the float through dptofp within one ulp.
TEST_CASE("game(libs3): strtod reads decimal numbers like the host") {
    auto m = machine();
    if (!m) return;
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    std::mt19937 rng{0x57D0u};
    s64 worst = 0, worstf = 0;
    int exact = 0, total = 0;
    std::vector<std::string> inputs = {"0", "1", "-1", "0.5", "3.141592653589793", "2.5e-3", "1e10", "1E-10", "+42.",
                                       ".125", "123456789012345678", "9007199254740993", "1.7976931348623157e308",
                                       "2.2250738585072014e-308", "  -7.25xyz", "abc", "-", "1e", "4.9e-324"};
    for (int i = 0; i < 160; ++i) {
        const u32 digits = 1 + rng() % 19;
        std::string s;
        const u32 neg = rng() % 2;
        if (neg) s += '-';
        for (u32 d = 0; d < digits; ++d) {
            const u32 dig = rng() % 10;
            s += static_cast<char>('0' + dig);
        }
        const u32 dot = rng() % (digits + 1);
        if (dot < digits) s.insert(s.size() - dot, ".");
        const u32 withexp = rng() % 2;
        if (withexp) {
            const s32 e = static_cast<s32>(rng() % 81) - 40;
            s += "e" + std::to_string(e);
        }
        inputs.push_back(s);
    }
    for (const std::string& s : inputs) {
        INFO("strtod(\"" << s << "\")");
        char* hend = nullptr;
        const double want = std::strtod(s.c_str(), &hend);
        const u32 used = static_cast<u32>(hend - s.c_str());
        m->put(kStr, s);
        seed_freelists(*m, reent);
        p32(*m, kOut, 0xDEADBEEFu);
        const bool paired = total % 4 == 0;
        u64 got = 0;
        hgp::Run r = pair_fn(*m, paired ? "_strtod_r" : "strtod", paired ? Args{sx(reent), sx(kStr), sx(kOut), 0} : Args{sx(kStr), sx(kOut), 0, 0}, seed++);
        REQUIRE_RUN(r);
        got = v0_64(r);
        INFO("got " << bitsd(got) << " host " << want);
        CHECK(g32(*m, kOut) == kStr + used);
        if (std::isfinite(want) && want != 0.0 && std::fabs(want) > 2.3e-308) {
            const s64 u = ulps_d(bitsd(got), want);
            CHECK(u == 0);  // measured: every normal result equals the host's
            worst = std::max(worst, u);
            exact += u == 0;
        } else if (want == 0.0) {
            CHECK(bitsd(got) == 0.0);
        }
        ++total;
        // strtodf: the float through dptofp
        if (total % 3 == 0 && std::isfinite(want) && std::fabs(want) < 1e38 && std::fabs(want) > 1e-37) {
            seed_freelists(*m, reent);
            r = pair_fn(*m, "strtodf", {sx(kStr), sx(kOut), 0, 0}, seed++);
            REQUIRE_RUN(r);
            const s64 u = ulps_f(bitsf(r.end.fpr[0]), static_cast<float>(want));
            CHECK(u <= 1);
            worstf = std::max(worstf, u);
        }
    }
    MESSAGE("strtod: " << total << " inputs, " << exact << " exact, worst " << worst << " ulp (double), " << worstf << " ulp (float)");
    report("strtod");
}

// ======================================================================================================================
// 6. mprec's Bigint arithmetic against host bignums (the free lists seeded: _Balloc pops blocks).
TEST_CASE("game(libs3): mprec Bigint arithmetic equals host bignum arithmetic") {
    auto m = machine();
    if (!m) return;
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    std::mt19937 rng{0xB16Bu};
    auto rand_big = [&](std::size_t n) {
        Big b(n);
        for (u32& w : b) w = rng();
        b.back() |= 1;
        trim(b);
        return b;
    };
    for (int i = 0; i < 40; ++i) {
        // _i2b
        const u32 v = rng();
        seed_freelists(*m, reent);
        hgp::Run r = pair_fn(*m, "_i2b", {sx(reent), sx(v), 0, 0}, seed++);
        CHECK(get_big(*m, v0_of(r)) == Big{v});
        // _multiply
        const std::size_t na = 1 + rng() % 6;
        const std::size_t nb = 1 + rng() % 6;
        const Big a = rand_big(na);
        const Big b = rand_big(nb);
        seed_freelists(*m, reent);
        put_big(*m, kBigA, a, k_for(a.size()));
        put_big(*m, kBigB, b, k_for(b.size()));
        r = pair_fn(*m, "_multiply", {sx(reent), sx(kBigA), sx(kBigB), 0}, seed++);
        CHECK(get_big(*m, v0_of(r)) == big_mul(a, b));
        // _lshift
        const u32 k = rng() % 100;
        seed_freelists(*m, reent);
        put_big(*m, kBigA, a, k_for(a.size()));
        r = pair_fn(*m, "_lshift", {sx(reent), sx(kBigA), k, 0}, seed++);
        CHECK(get_big(*m, v0_of(r)) == big_shl(a, k));
        // __mdiff: |a - b| and the sign word
        seed_freelists(*m, reent);
        put_big(*m, kBigA, a, k_for(a.size()));
        put_big(*m, kBigB, b, k_for(b.size()));
        r = pair_fn(*m, "__mdiff", {sx(reent), sx(kBigA), sx(kBigB), 0}, seed++);
        const int cmp = big_cmp(a, b);
        const Big diff = cmp >= 0 ? big_sub(a, b) : big_sub(b, a);
        Big got = get_big(*m, v0_of(r));
        trim(got);
        CHECK(got == (cmp == 0 ? Big{0} : diff));
        CHECK(g32(*m, v0_of(r) + libc::bigint::kSign) == (cmp < 0 ? 1u : 0u));
        // _multadd: b * mul + add (the result may be a new, larger Bigint)
        const u32 mul = 1 + rng() % 65535;  // _multadd works in 16-bit halves: m and a below 2^16 (dtoa: 10, 5^k)
        const u32 add = rng() % 65536;
        seed_freelists(*m, reent);
        put_big(*m, kBigA, a, k_for(a.size()));
        r = pair_fn(*m, "_multadd", {sx(reent), sx(kBigA), mul, add}, seed++);
        Big want = big_mul(a, Big{mul});
        {
            u64 carry = add;
            for (u32& w : want) {
                const u64 t = static_cast<u64>(w) + carry;
                w = static_cast<u32>(t);
                carry = t >> 32;
            }
            if (carry) want.push_back(static_cast<u32>(carry));
        }
        CHECK(get_big(*m, v0_of(r)) == want);
        // _pow5mult: b * 5^k (the 5^4 cache in the _reent built on the way)
        const u32 k5 = rng() % 40;
        seed_freelists(*m, reent, 16);
        p32(*m, reent + libs3::reent::kP5s, 0);
        put_big(*m, kBigA, a, k_for(a.size()));
        r = pair_fn(*m, "_pow5mult", {sx(reent), sx(kBigA), k5, 0}, seed++);
        Big p5 = a;
        for (u32 j = 0; j < k5; ++j) p5 = big_mul(p5, Big{5});
        CHECK(get_big(*m, v0_of(r)) == p5);
    }
    // _s2b: a decimal digit string (nd0 digits before the point) as a Bigint
    for (int i = 0; i < 20; ++i) {
        const u32 nd = 10 + rng() % 30;
        std::string s;
        for (u32 d = 0; d < nd; ++d) {
            const u32 dig = rng() % 10;
            s += static_cast<char>('1' + dig % 9);
        }
        const u32 nd0 = 9 + rng() % (nd - 9);
        std::string with_point = s.substr(0, nd0) + "." + s.substr(nd0);
        m->put(kStr, with_point);
        u32 y9 = 0;
        for (int d = 0; d < 9; ++d) y9 = 10 * y9 + static_cast<u32>(s[d] - '0');
        seed_freelists(*m, reent);
        hgp::Run r = pair_fn(*m, "_s2b", {sx(reent), sx(kStr), nd0, nd}, seed++, {y9});
        Big want{0};
        for (char ch : s) {
            want = big_mul(want, Big{10});
            u64 carry = static_cast<u32>(ch - '0');
            for (u32& w : want) {
                const u64 t = w + carry;
                w = static_cast<u32>(t);
                carry = t >> 32;
            }
            if (carry) want.push_back(static_cast<u32>(carry));
            trim(want);
        }
        CHECK(get_big(*m, v0_of(r)) == want);
    }
    // _d2b: d == bits of the Bigint * 2^e, with the count of significant bits
    for (int i = 0; i < 30; ++i) {
        const double d = std::ldexp(1.0 + static_cast<double>(rng() % 1000000) / 1000000.0, static_cast<int>(rng() % 1200) - 600);
        seed_freelists(*m, reent);
        hgp::Run r = pair_fn(*m, "_d2b", {sx(reent), dbits(d), sx(kOut), sx(kOut + 4)}, seed++);
        const Big b = get_big(*m, v0_of(r));
        double val = 0;
        for (std::size_t j = b.size(); j-- > 0;) val = val * 4294967296.0 + b[j];
        CHECK(std::ldexp(val, gs32(*m, kOut)) == d);
        CHECK((b[0] & 1) == 1);  // trailing zero bits removed
        u32 bits = 0;
        for (double t = val; t >= 1.0; t /= 2) ++bits;
        CHECK(gs32(*m, kOut + 4) == static_cast<s32>(bits));
    }
    report("mprec");
}

// ======================================================================================================================
// 7. qsort with strcmp as the comparator: the three swap types -- one doubleword (size 8), doublewords (16, 24) and
//    bytes (4, 5, 12: not multiples of 8).
TEST_CASE("game(libs3): qsort sorts arrays like the host") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    std::mt19937 rng{0x9507u};
    for (u32 size : {8u, 16u, 24u, 4u, 5u, 12u}) {
        for (u32 n : {0u, 1u, 2u, 3u, 6u, 7u, 8u, 13u, 40u, 41u, 100u, 300u}) {
            std::vector<std::string> v(n);
            for (std::string& s : v) {
                const u32 len = rng() % size;  // up to size - 1 characters + NUL
                for (u32 j = 0; j < len; ++j) {
                    const u32 ch = rng() % 4;  // few letters: many equal elements
                    s += static_cast<char>('a' + ch);
                }
            }
            std::memset(m->at(kArr), 0, n * size + 16);
            for (u32 i = 0; i < n; ++i) m->put(kArr + i * size, v[i]);
            hgp::Run r = pair_fn(*m, "qsort", {sx(kArr), n, size, kStrcmp}, seed++);
            REQUIRE_RUN(r);
            std::vector<std::string> got(n);
            for (u32 i = 0; i < n; ++i) got[i] = m->str(kArr + i * size, size);
            std::sort(v.begin(), v.end());
            CHECK(got == v);
        }
    }
    report("qsort");
}

// ======================================================================================================================
// 8. __ieee754_pow (the body of pow; pow itself is a stand-in of test_libs2 and stays recompiled) and
//    __ieee754_rem_pio2 against the host.
TEST_CASE("game(libs3): __ieee754_pow and the pi/2 reduction against the host") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    std::mt19937 rng{0x90Fu};
    s64 worst = 0;
    int n = 0;
    std::vector<std::pair<double, double>> cases = {{2, 10}, {2, 0.5}, {10, -3}, {-2, 3}, {-2, 2}, {0, 5}, {0, 0},
                                                    {1, 1e300}, {-1, 3}, {9, 0.5}, {1e10, 2}, {1.0001, 10000}, {7, 1}};
    for (int i = 0; i < 300; ++i) {
        const double x = static_cast<double>(1 + rng() % 100000) / 1000.0;
        const double y = (static_cast<double>(rng() % 20001) - 10000.0) / 1000.0;
        cases.emplace_back(x, y);
    }
    for (const auto& [x, y] : cases) {
        const double want = std::pow(x, y);
        hgp::Run r = pair_fn(*m, "__ieee754_pow", {dbits(x), dbits(y), 0, 0}, seed++);
        REQUIRE_RUN(r);
        const double got = bitsd(v0_64(r));
        INFO("pow(" << x << ", " << y << ") = " << got << ", host " << want);
        if (std::isfinite(want) && want != 0.0 && std::fabs(want) > 1e-300) {
            const s64 u = ulps_d(got, want);
            worst = std::max(worst, u);
            CHECK(u <= 1);  // measured worst
        } else if (want == 0.0) {
            CHECK(got == 0.0);
        }
        ++n;
    }
    MESSAGE("pow: " << n << " cases, worst " << worst << " ulp");
    // __ieee754_rem_pio2(x, y): x - n * pi/2 = y[0] + y[1]
    const double pio2 = 1.57079632679489661923;
    for (int i = 0; i < 120; ++i) {
        const u32 range = rng() % 4;
        const double scale = range == 0 ? 0.7 : range == 1 ? 3.0 : range == 2 ? 300.0 : 1e5;
        const double x = (static_cast<double>(rng()) / 4294967296.0 * 2.0 - 1.0) * scale;
        hgp::Run r = pair_fn(*m, "__ieee754_rem_pio2", {dbits(x), sx(kOut), 0, 0}, seed++);
        REQUIRE_RUN(r);
        const s32 q = sv0(r);
        const double y0 = bitsd(g64(*m, kOut));
        const double y1 = bitsd(g64(*m, kOut + 8));
        INFO("rem_pio2(" << x << ") = " << q << ", " << y0 << " + " << y1);
        CHECK(std::fabs(y0) <= pio2 / 2 * 1.0000001);
        CHECK(std::fabs((x - q * pio2) - (y0 + y1)) <= 1e-9 * std::max(1.0, std::fabs(x)));
    }
    report("pow / rem_pio2");
}

// ======================================================================================================================
// 9. newlib's heap on a replay snapshot (its arena is live there): _malloc_r / _realloc_r pairs.
TEST_CASE("game(libs3): newlib's heap on a snapshot heap") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: no snapshot b_5800");
        return;
    }
    copy_from_snapshot(*m, snap, 0, EEMemory::kMainRamSize);
    const u32 reent = reent_of(*m);
    u32 seed = 1;
    int full = 0;
    for (u32 size : {1u, 8u, 16u, 24u, 100u, 500u, 1000u, 4000u, 20000u}) {
        hgp::Run r = pair_fn(*m, "_malloc_r", {sx(reent), size, 0, 0}, seed++);
        if (!r.stopped && v0_of(r) != 0) {
            ++full;
            const u32 p = v0_of(r);
            CHECK(p % 8 == 0);
            const u32 chunk = g32(*m, p - 4) & ~7u;  // the chunk size word before the user pointer
            CHECK(chunk >= size + 4);
            // grow and shrink it
            r = pair_fn(*m, "_realloc_r", {sx(reent), sx(p), size * 2 + 64, 0}, seed++);
            r = pair_fn(*m, "_realloc_r", {sx(reent), sx(v0_of(r)), size / 2 + 1, 0}, seed++);
        }
    }
    MESSAGE("heap: " << full << " allocations ran to the end");
    report("heap");
}

// ======================================================================================================================
// 10. MPS on the movies of the disc: start-code classes, the start-code search, the demultiplexer on real packs.
TEST_CASE("game(libs3): MPS classifies start codes and parses the movies' packs") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    // every 00 00 01 xx code and a few broken prefixes
    for (u32 code = 0; code < 0x100; ++code) {
        const u8 bytes[4] = {0, 0, 1, static_cast<u8>(code)};
        std::memcpy(m->at(kBuf), bytes, 4);
        const bool paired = code % 8 == 0 || (code >= 0xB8 && code <= 0xBD);
        const u32 want = code == 0xBA ? libs3::mps::kClassPack : code == 0xBB ? libs3::mps::kClassSystem : code == 0xB9 ? libs3::mps::kClassEnd : code >= 0xBC ? libs3::mps::kClassPes : 0;
        if (paired) {
            hgp::Run r = pair_fn(*m, "sub_5776B0", {sx(kBuf), 0, 0, 0}, seed++);
            CHECK(v0_of(r) == want);
        }
    }
    for (const u32 bad : {0x010000BAu, 0xBA010001u, 0xBA020000u}) {
        p32(*m, kBuf, bad);
        CHECK(v0_of(pair_fn(*m, "sub_5776B0", {sx(kBuf), 0, 0, 0}, seed++)) == 0);
    }
    // the byte search against the host
    std::mt19937 rng{0x3B5u};
    for (int i = 0; i < 30; ++i) {
        std::vector<u8> d(200 + rng() % 300);
        for (u8& b : d) {
            const u32 x = rng() % 6;
            b = static_cast<u8>(x < 3 ? 0 : x < 4 ? 1 : 0xBA);
        }
        const u32 code = rng() % 2 ? 0xBA : 0xBB;
        std::memcpy(m->at(kBuf), d.data(), d.size());
        hgp::Run r = pair_fn(*m, "sub_577780", {sx(kBuf), d.size(), code, 0}, seed++);
        u32 want = 0;
        for (std::size_t j = 0; j + 4 <= d.size(); ++j)
            if (is_code(d, j, static_cast<u8>(code))) {
                want = kBuf + static_cast<u32>(j);
                break;
            }
        CHECK(v0_of(r) == want);
    }
    // the demultiplexer on the first packs of every movie
    const auto mv = movies();
    if (mv.empty()) {
        MESSAGE("SKIP: no movies under " << sfd_dir());
        report("MPS");
        return;
    }
    int checked = 0, systems = 0;
    for (const Movie& f : mv) {
        std::memcpy(m->at(kBuf), f.data.data(), f.data.size());
        const auto ps = packs(f.data, 12);
        for (const Pack& pk : ps) {
            INFO(f.name << " pack at " << pk.at);
            std::memset(m->at(kHandle), 0, 256);
            p32(*m, kHandle + tail1::mps::kHandleState, 2);
            p32(*m, kHandle + libs3::mps::kParser, 0x575B48u);
            p32(*m, kHandle + libs3::mps::kMode, 2);  // as sub_577E68 sets it: 16-bit PES packet lengths
            p32(*m, kOut, 0);
            p32(*m, kOut + 4, 0);
            const u32 len = static_cast<u32>(f.data.size() - pk.at);
            hgp::Run r = pair_fn(*m, "sub_575AA0", {sx(kHandle), sx(kBuf + static_cast<u32>(pk.at)), len, sx(kOut)}, seed++, {sx(kOut + 4)});
            REQUIRE_RUN(r);
            const u32 classes = g32(*m, kOut + 4);
            CHECK((classes & libs3::mps::kClassPack) != 0);
            CHECK((classes & libs3::mps::kClassPes) != 0);
            CHECK(((classes & libs3::mps::kClassSystem) != 0) == pk.system);
            CHECK(m->at(kHandle + libs3::mps::kPesStreamId)[0] == pk.stream_id);
            INFO("used " << g32(*m, kOut) << ", pack " << pk.len << " (mpeg2 " << pk.mpeg2 << "), first PES at +" << (pk.first_pes - pk.at)
                         << ", PES header " << pk.pes_hdr << ", id " << unsigned(pk.stream_id));
            CHECK(g32(*m, kOut) == static_cast<u32>(pk.first_pes - pk.at + pk.pes_hdr));
            systems += pk.system;
            ++checked;
        }
    }
    MESSAGE("MPS: " << checked << " packs of " << mv.size() << " movies (" << systems << " with a system header)");
    report("MPS");
}

// ======================================================================================================================
// 11. M2V's MPEG-2 probe on the movies' video streams; the MPV header decoder over a memory stream.
TEST_CASE("game(libs3): the MPEG-2 probe and the MPV header decoder on the movies' video") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    const auto mv = movies();
    if (mv.empty()) {
        MESSAGE("SKIP: no movies under " << sfd_dir());
        return;
    }
    int mpeg2 = 0, decoded = 0;
    for (const Movie& f : mv) {
        std::vector<u8> es = elementary(f.data, 0xE0);
        if (es.size() < 1024) continue;
        es.resize(std::min<std::size_t>(es.size(), 128 * 1024));
        INFO(f.name);
        std::memcpy(m->at(kBuf), es.data(), es.size());
        hgp::Run r = pair_fn(*m, "sub_574E60", {sx(kBuf), es.size(), 0, 0}, seed++);
        const bool want2 = host_is_mpeg2(es);
        CHECK(v0_of(r) == (want2 ? 1u : 0u));
        mpeg2 += want2;
        // the MPV header decoder (MPEG-1 streams: sequence / GOP / picture headers up to the first slice)
        if (want2) continue;
        std::memset(m->at(kHandle), 0, libs3::mpv::kHandleStride);
        p32(*m, kHandle + tail1::mpv::kHandleState, tail1::mpv::kStateValid);
        p32(*m, kOut, kBuf);
        p32(*m, kOut + 4, static_cast<u32>(es.size()));
        p32(*m, kOut + 8, 0);
        r = pair_fn(*m, "sub_5796D0", {sx(kHandle), sx(kOut), sx(kOut + 8), 0}, seed++);
        if (r.stopped) continue;
        ++decoded;
        // the sequence header as ISO/IEC 11172-2 lays it out
        std::size_t s = 0;
        while (s + 12 < es.size() && !is_code(es, s, 0xB3)) ++s;
        const u32 w = (u32(es[s + 4]) << 4) | (es[s + 5] >> 4);
        const u32 h = (u32(es[s + 5] & 15) << 8) | es[s + 6];
        CHECK(g32(*m, kHandle + libs3::mpv::kSeq) == w);
        CHECK(g32(*m, kHandle + libs3::mpv::kSeq + 4) == h);
    }
    MESSAGE("video: " << mv.size() << " movies, " << mpeg2 << " MPEG-2, " << decoded << " MPEG-1 headers decoded to the end");
    report("MPEG-2 probe / MPV headers");
}

// ======================================================================================================================
// 12. CRI helpers: muldiv against the host, the clip table, the handle pools, MWSFD's allocator and code mappers,
//     the key table and the descrambler, the MPS getters.
TEST_CASE("game(libs3): CRI arithmetic, pools, allocator and descrambler") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    std::mt19937 rng{0xC21u};
    // muldiv: (a * b) / c with 64-bit intermediate; c == 0 saturates
    for (int i = 0; i < 60; ++i) {
        const s32 a = static_cast<s32>(rng());
        const s32 b = static_cast<s32>(rng() % 200001) - 100000;
        const u32 csel = rng() % 8;
        const s32 c = csel == 0 ? 0 : static_cast<s32>(rng() % 2000001) - 1000000;
        hgp::Run r = pair_fn(*m, "sub_57BAF0", {sx(static_cast<u32>(a)), sx(static_cast<u32>(b)), sx(static_cast<u32>(c)), 0}, seed++);
        const s64 p = static_cast<s64>(a) * b;
        const s32 want = c ? static_cast<s32>(p / c) : ((a < 0) != (b < 0) ? INT32_MIN : INT32_MAX);
        CHECK(sv0(r) == want);
        if (c) {
            const s64 aa = a < 0 ? -static_cast<s64>(a) : a, bb = b < 0 ? -static_cast<s64>(b) : b, cc = c < 0 ? -static_cast<s64>(c) : c;
            const s64 q = (aa * bb + cc / 2) / cc;
            const bool negative = ((a < 0) != (b < 0)) != (c < 0);
            const s64 rw = negative ? -q : q;
            r = pair_fn(*m, "sub_57BB60", {sx(static_cast<u32>(a)), sx(static_cast<u32>(b)), sx(static_cast<u32>(c)), 0}, seed++);
            CHECK(sv0(r) == static_cast<s32>(rw));
            r = pair_fn(*m, "sub_57BC10", {sx(static_cast<u32>(a)), sx(static_cast<u32>(b)), sx(static_cast<u32>(c)), 0}, seed++);
            CHECK(sv0(r) == static_cast<s32>(rw));
        }
    }
    // the clip table: 384 x 0, 0..255, 384 x 255; the copy and the zero point
    hgp::Run r = pair_fn(*m, "sub_57B158", {sx(kWork), 0, 0, 0}, seed++);
    CHECK(v0_of(r) == kWork + 384);
    CHECK(g32(*m, libs3::mpv::kClipZero) == kWork + 384);
    for (u32 i = 0; i < 1024; ++i) {
        const u8 want = i < 384 ? 0 : i < 640 ? static_cast<u8>(i - 384) : 255;
        if (m->at(kWork)[i] != want || m->at(libs3::mpv::kClipTable)[i] != want) {
            CHECK(false);
            break;
        }
    }
    // M2V pool: layout for 3 handles, the first free one, the handle check
    r = pair_fn(*m, "sub_574FE8", {3, sx(kWork + 5), 0x10000, 0}, seed++);
    CHECK(gs32(*m, libs3::m2v::kPoolCount) == 3);
    const u32 m2base = g32(*m, libs3::m2v::kPoolBase);
    CHECK(m2base == ((kWork + 5 + 63) & ~63u));
    for (u32 i = 0; i < 3; ++i) p32(*m, m2base + i * libs3::m2v::kHandleStride, libs3::m2v::kStateFree);
    r = pair_fn(*m, "sub_575178", {0, 0, 0, 0}, seed++);
    CHECK(v0_of(r) == m2base);
    p32(*m, m2base, libs3::m2v::kStateValid);
    r = pair_fn(*m, "sub_575178", {0, 0, 0, 0}, seed++);
    CHECK(v0_of(r) == m2base + libs3::m2v::kHandleStride);
    r = pair_fn(*m, "sub_575390", {5, 0x1234560, 0, 0}, seed++);
    CHECK(g32(*m, m2base + libs3::m2v::kCallbacks + 20) == 0x1234560u);
    CHECK(g32(*m, m2base + libs3::m2v::kHandleStride + libs3::m2v::kCallbacks + 20) != 0x1234560u);
    // MPV pool: layout for 4 handles, all freed, find / set-all
    const u32 mvwork = kWork + 0x4000;
    r = pair_fn(*m, "sub_57B2B8", {4, sx(mvwork), 0, 0}, seed++);
    CHECK(gs32(*m, libs3::mpv::kPoolCount) == 4);
    const u32 mvbase = g32(*m, libs3::mpv::kPoolBase);
    CHECK(mvbase == mvwork);
    CHECK(g32(*m, libs3::mpv::kShared) == mvbase + 5 * libs3::mpv::kHandleStride);  // after the 4 handles and one more
    pair_fn(*m, "sub_57B230", {0, 0, 0, 0}, seed++);
    for (u32 i = 0; i < 4; ++i) CHECK(g32(*m, mvbase + i * libs3::mpv::kHandleStride + tail1::mpv::kHandleState) == 1u);
    p32(*m, mvbase + tail1::mpv::kHandleState, tail1::mpv::kStateValid);
    r = pair_fn(*m, "sub_57B498", {0, 0, 0, 0}, seed++);
    CHECK(v0_of(r) == mvbase + libs3::mpv::kHandleStride);
    pair_fn(*m, "sub_57B710", {3, 0xABCDE0, 0, 0}, seed++);
    CHECK(g32(*m, mvbase + libs3::mpv::kCallbacks + 12) == 0xABCDE0u);
    CHECK(g32(*m, mvbase + libs3::mpv::kHandleStride + libs3::mpv::kCallbacks + 12) != 0xABCDE0u);
    r = pair_fn(*m, "sub_57B760", {0, 2, sx(kOut), 0}, seed++);
    CHECK(g32(*m, kOut) == g32(*m, libs3::mpv::kDefaultCbs + 8));
    // MWSFD's work allocator over user work: bump allocations, the table, the count, then free-all
    const u32 pl = kHandle + 0x1000;
    std::memset(m->at(pl), 0, libs3::mwsfd::kPlayerStride);
    p32(*m, pl + libs3::mwsfd::kWorkUse, 1);
    p32(*m, pl + libs3::mwsfd::kWorkSize, 1000);
    p32(*m, pl + libs3::mwsfd::kWorkCur, kWork + 0x10000);
    u32 expect = kWork + 0x10000, used = 0;
    for (u32 size : {100u, 200u, 300u, 350u, 60u}) {
        r = pair_fn(*m, "sub_57E070", {sx(pl), size, 0, 0}, seed++);
        if (used + size <= 1000) {
            CHECK(v0_of(r) == expect);
            expect += size;
            used += size;
        } else {
            CHECK(v0_of(r) == 0);
        }
    }
    CHECK(gs32(*m, pl + libs3::mwsfd::kAllocCount) == 4);
    CHECK(g32(*m, pl + libs3::mwsfd::kAllocTable) == kWork + 0x10000);
    pair_fn(*m, "sub_57E210", {sx(pl), 0, 0, 0}, seed++);
    CHECK(gs32(*m, pl + libs3::mwsfd::kAllocCount) == 0);
    for (u32 i = 0; i < 32; ++i) CHECK(g32(*m, pl + libs3::mwsfd::kAllocTable + 4 * i) == 0);
    // ... and through the malloc / free callbacks of the work record (strlen stands in: it returns its object's length)
    const u32 wr = tail1::mwsfd::kWork;
    m->put(kStr, "malloc!");
    p32(*m, wr + libs3::mwsfd::kWorkMalloc, kStrlen);
    p32(*m, wr + libs3::mwsfd::kWorkFree, kStrlen);
    p32(*m, wr + libs3::mwsfd::kWorkAllocObj, kStr);
    p32(*m, pl + libs3::mwsfd::kWorkUse, 0);
    r = pair_fn(*m, "sub_57E070", {sx(pl), 64, 0, 0}, seed++);
    CHECK(v0_of(r) == 7u);
    CHECK(gs32(*m, pl + libs3::mwsfd::kAllocCount) == 1);
    pair_fn(*m, "sub_57E210", {sx(pl), 0, 0, 0}, seed++);
    CHECK(gs32(*m, pl + libs3::mwsfd::kAllocCount) == 0);
    // the code mappers
    for (s32 x = -1; x <= 6; ++x) {
        const u32 want = (x >= 1 && x <= 3) ? static_cast<u32>(x) : 3u;
        CHECK(v0_of(pair_fn(*m, "sub_57E9D8", {sx(static_cast<u32>(x)), 0, 0, 0}, seed++)) == want);
        CHECK(v0_of(pair_fn(*m, "sub_57ED00", {sx(static_cast<u32>(x)), 0, 0, 0}, seed++)) == want);
        CHECK(v0_of(pair_fn(*m, "sub_57D1D0", {sx(static_cast<u32>(x)), 0, 0, 0}, seed++)) == ((x == 2 || x == 3) ? 0u : 1u));
        if (x >= 1 && x <= 4) {
            CHECK(v0_of(pair_fn(*m, "sub_57EA18", {static_cast<u64>(x), 0, 0, 0}, seed++)) == static_cast<u32>(x));
            CHECK(v0_of(pair_fn(*m, "sub_57ED40", {static_cast<u64>(x), 0, 0, 0}, seed++)) == static_cast<u32>(x));
        }
        if (x >= 0 && x <= 3) CHECK(v0_of(pair_fn(*m, "sub_57C4E8", {static_cast<u64>(x), 0, 0, 0}, seed++)) == (x == 0 ? 2u : static_cast<u32>(x)));
    }
    for (u32 bits = 0; bits < 8; ++bits) {
        std::memset(m->at(kOut), 0, 16);
        p32(*m, kOut + 4, bits & 1);
        p32(*m, kOut + 8, (bits >> 1) & 1);
        p32(*m, kOut + 12, (bits >> 2) & 1);
        const u32 b4 = bits & 1, b8 = (bits >> 1) & 1, b12 = (bits >> 2) & 1;
        const u32 want = b4 ? (b12 ? 1u : 3u) : (b8 ? (b12 ? 0u : 2u) : 0u);
        CHECK(v0_of(pair_fn(*m, "sub_57DF60", {sx(kOut), 0, 0, 0}, seed++)) == want);
    }
    for (s32 kind = 0; kind < 4; ++kind) {
        for (s32 rate : {0, 6000, 12000, 24000, 48000, 44100, 32000, -5}) {
            std::memset(m->at(kOut), 0, 64);
            p32(*m, kOut + 4, static_cast<u32>(kind));
            p32(*m, kOut + 36, static_cast<u32>(rate));
            const bool known = rate == 0 || rate == 6000 || rate == 12000 || rate == 24000 || rate == 48000;
            const u32 want = (kind == 0 || kind == 2) ? 0u : kind == 1 ? (known ? 1u : 0u) : 1u;
            CHECK(v0_of(pair_fn(*m, "sub_57DFB0", {sx(kOut), 0, 0, 0}, seed++)) == want);
        }
    }
    // the start-code test of the descrambler: 00 00 01 B9 / BA only
    for (u32 code = 0xB0; code < 0xC0; ++code) {
        const u8 b[4] = {0, 0, 1, static_cast<u8>(code)};
        std::memcpy(m->at(kBuf), b, 4);
        CHECK(v0_of(pair_fn(*m, "sub_57C270", {0, sx(kBuf), 0, 0}, seed++)) == ((code == 0xB9 || code == 0xBA) ? 1u : 0u));
    }
    // the key table from a string, then the descrambler twice: the block comes back
    const u32 table = kWork + 0x18000;
    std::memset(m->at(table), 0, 0x100);
    m->put(kStr, "PERSONA3FES");
    pair_fn(*m, "sub_57BFC0", {sx(table), sx(kStr), 0, 0}, seed++);
    std::vector<u8> block(2048);
    for (u8& x : block) x = static_cast<u8>(rng());
    std::memcpy(m->at(kBuf), block.data(), block.size());
    pair_fn(*m, "sub_57C188", {sx(table), sx(kBuf), 0, 0}, seed++);
    const bool changed = std::memcmp(m->at(kBuf), block.data(), block.size()) != 0;
    CHECK(changed);
    pair_fn(*m, "sub_57C188", {sx(table), sx(kBuf), 0, 0}, seed++);
    CHECK(std::memcmp(m->at(kBuf), block.data(), block.size()) == 0);
    // the key generator step: x = x * a + c (16-bit)
    p16(*m, kOut, 1234);
    p16(*m, kOut + 2, 4321);
    p16(*m, kOut + 4, 777);
    pair_fn(*m, "sub_57BF78", {sx(kOut), sx(kOut + 2), sx(kOut + 4), 0}, seed++);
    CHECK(g16(*m, kOut) == static_cast<u16>(1234 * 4321 + 777));
    // MPS getters on a valid handle: the records copied out
    std::memset(m->at(kHandle), 0, 256);
    p32(*m, kHandle + tail1::mps::kHandleState, 2);
    for (u32 i = 0; i < 256 - 16; i += 4) p32(*m, kHandle + 16 + i, 0x11110000u + i);
    pair_fn(*m, "sub_5777F8", {sx(kHandle), sx(kOut), 0, 0}, seed++);
    CHECK(std::memcmp(m->at(kOut), m->at(kHandle + libs3::mps::kPack), 16) == 0);
    pair_fn(*m, "sub_577860", {sx(kHandle), sx(kOut), 2, 0}, seed++);
    CHECK(std::memcmp(m->at(kOut), m->at(kHandle + libs3::mps::kStreamInfo + 64), 32) == 0);
    pair_fn(*m, "sub_577910", {sx(kHandle), sx(kOut), 0, 0}, seed++);
    CHECK(std::memcmp(m->at(kOut), m->at(kHandle + libs3::mps::kSystem), 32) == 0);
    pair_fn(*m, "sub_5779A8", {sx(kHandle), sx(kOut), 0, 0}, seed++);
    CHECK(std::memcmp(m->at(kOut), m->at(kHandle + libs3::mps::kPes), 40) == 0);
    pair_fn(*m, "sub_575A50", {sx(kHandle), 0x5656560, 0x7878780, 0}, seed++);
    CHECK(g32(*m, kHandle + libs3::mps::kPesCb) == 0x5656560u);
    CHECK(g32(*m, kHandle + libs3::mps::kPesCb + 4) == 0x7878780u);
    // a free handle (state 1) fails the check: MPS raises 0xFF020201 on the global record
    p32(*m, kHandle + tail1::mps::kHandleState, 1);
    r = pair_fn(*m, "sub_5777F8", {sx(kHandle), sx(kOut), 0, 0}, seed++);
    CHECK(v0_of(r) == 0xFF020201u);
    report("CRI helpers");
}

#else

TEST_CASE("game(libs3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
