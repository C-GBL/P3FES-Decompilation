// Pair tests for slice libs5 (game/src/lib/libs5_*.cpp: CRI Sofdec 0x580000-0x5AFFFF -- MWSFD's player layer, SFD's
// audio transfer, small transfer modules and stream-core helpers, SFX's handle pools, SUD's tag reader -- and the kernel
// payloads' do-nothing functions). Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the
// whole register file and cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack
// too), the scratchpad, the BIOS window, the bus log. The callees this test binary does not emit (ADXT, the loop-play
// list, SVM, the SFD core's still-recompiled parts, the error reporter) are stand-ins (stand_ins.h): recorders without
// scratch clobbering -- a stand-in's entry check point holds the call's arguments, so the pair compares the calls --
// and, for the SFD status getter and the stream accessors, their real effect on the guest. On top of the generic sweep
// (random worlds):
//   * every function on the boot movie's live player, SFD handle, audio slave and SFX handle (snapshot
//     libs5_movie_860: the dorm route at vblank 860, made for this slice) and on the dorm snapshot's MWSFD;
//   * mwPlyGetStat's status rules, the handle check, the player accessors and server words;
//   * the file-name copy (fits / too long / empty); SFX's two handle pools and the work layout; the SFD statistics
//     record against a host model; SFD's handle accessors on the live handle (parameters, transfer slots, time,
//     'time valid' statuses), the time-base setters, the record initialisers, the vsync counter; the audio
//     transfer's ADXT configuration and the module inits; the constant returns.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs5.h"

#include <algorithm>
#include <cstdint>
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
void fn_sub_5800F0_005800f0(EEContext&);  // generated body
void fn_sub_5800F0_005800f0__recomp(EEContext&);  // recompiled
void fn_sub_580130_00580130(EEContext&);  // generated body
void fn_sub_580130_00580130__recomp(EEContext&);  // recompiled
void fn_sub_580270_00580270(EEContext&);  // generated body
void fn_sub_580270_00580270__recomp(EEContext&);  // recompiled
void fn_sub_580368_00580368(EEContext&);  // generated body
void fn_sub_580368_00580368__recomp(EEContext&);  // recompiled
void fn_sub_580378_00580378(EEContext&);  // generated body
void fn_sub_580378_00580378__recomp(EEContext&);  // recompiled
void fn_sub_580628_00580628(EEContext&);  // generated body
void fn_sub_580628_00580628__recomp(EEContext&);  // recompiled
void fn_sub_580750_00580750(EEContext&);  // generated body
void fn_sub_580750_00580750__recomp(EEContext&);  // recompiled
void fn_sub_580900_00580900(EEContext&);  // generated body
void fn_sub_580900_00580900__recomp(EEContext&);  // recompiled
void fn_sub_580958_00580958(EEContext&);  // generated body
void fn_sub_580958_00580958__recomp(EEContext&);  // recompiled
void fn_sub_5809B0_005809b0(EEContext&);  // generated body
void fn_sub_5809B0_005809b0__recomp(EEContext&);  // recompiled
void fn_sub_580C80_00580c80(EEContext&);  // generated body
void fn_sub_580C80_00580c80__recomp(EEContext&);  // recompiled
void fn_sub_580CB0_00580cb0(EEContext&);  // generated body
void fn_sub_580CB0_00580cb0__recomp(EEContext&);  // recompiled
void fn_sub_580D40_00580d40(EEContext&);  // generated body
void fn_sub_580D40_00580d40__recomp(EEContext&);  // recompiled
void fn_WTLS_get_table_0_00580df0(EEContext&);  // generated body
void fn_WTLS_get_table_0_00580df0__recomp(EEContext&);  // recompiled
void fn_sub_580E10_00580e10(EEContext&);  // generated body
void fn_sub_580E10_00580e10__recomp(EEContext&);  // recompiled
void fn_sub_580E78_00580e78(EEContext&);  // generated body
void fn_sub_580E78_00580e78__recomp(EEContext&);  // recompiled
void fn_sub_580E98_00580e98(EEContext&);  // generated body
void fn_sub_580E98_00580e98__recomp(EEContext&);  // recompiled
void fn_sub_580F78_00580f78(EEContext&);  // generated body
void fn_sub_580F78_00580f78__recomp(EEContext&);  // recompiled
void fn_sub_5810F0_005810f0(EEContext&);  // generated body
void fn_sub_5810F0_005810f0__recomp(EEContext&);  // recompiled
void fn_sub_581108_00581108(EEContext&);  // generated body
void fn_sub_581108_00581108__recomp(EEContext&);  // recompiled
void fn_sub_581120_00581120(EEContext&);  // generated body
void fn_sub_581120_00581120__recomp(EEContext&);  // recompiled
void fn___env_lock_11_00581138(EEContext&);  // generated body
void fn___env_lock_11_00581138__recomp(EEContext&);  // recompiled
void fn_sub_581148_00581148(EEContext&);  // generated body
void fn_sub_581148_00581148__recomp(EEContext&);  // recompiled
void fn_sub_5811D0_005811d0(EEContext&);  // generated body
void fn_sub_5811D0_005811d0__recomp(EEContext&);  // recompiled
void fn_sub_581690_00581690(EEContext&);  // generated body
void fn_sub_581690_00581690__recomp(EEContext&);  // recompiled
void fn_sub_5816F0_005816f0(EEContext&);  // generated body
void fn_sub_5816F0_005816f0__recomp(EEContext&);  // recompiled
void fn_sub_581798_00581798(EEContext&);  // generated body
void fn_sub_581798_00581798__recomp(EEContext&);  // recompiled
void fn_sub_581840_00581840(EEContext&);  // generated body
void fn_sub_581840_00581840__recomp(EEContext&);  // recompiled
void fn_sub_582798_00582798(EEContext&);  // generated body
void fn_sub_582798_00582798__recomp(EEContext&);  // recompiled
void fn_sub_5827F0_005827f0(EEContext&);  // generated body
void fn_sub_5827F0_005827f0__recomp(EEContext&);  // recompiled
void fn_sub_5827F8_005827f8(EEContext&);  // generated body
void fn_sub_5827F8_005827f8__recomp(EEContext&);  // recompiled
void fn_sub_582810_00582810(EEContext&);  // generated body
void fn_sub_582810_00582810__recomp(EEContext&);  // recompiled
void fn_sub_582828_00582828(EEContext&);  // generated body
void fn_sub_582828_00582828__recomp(EEContext&);  // recompiled
void fn_sub_583028_00583028(EEContext&);  // generated body
void fn_sub_583028_00583028__recomp(EEContext&);  // recompiled
void fn_sub_5833D8_005833d8(EEContext&);  // generated body
void fn_sub_5833D8_005833d8__recomp(EEContext&);  // recompiled
void fn_sub_5833E8_005833e8(EEContext&);  // generated body
void fn_sub_5833E8_005833e8__recomp(EEContext&);  // recompiled
void fn_sub_583410_00583410(EEContext&);  // generated body
void fn_sub_583410_00583410__recomp(EEContext&);  // recompiled
void fn_sub_583470_00583470(EEContext&);  // generated body
void fn_sub_583470_00583470__recomp(EEContext&);  // recompiled
void fn_sub_5834A0_005834a0(EEContext&);  // generated body
void fn_sub_5834A0_005834a0__recomp(EEContext&);  // recompiled
void fn_sub_583500_00583500(EEContext&);  // generated body
void fn_sub_583500_00583500__recomp(EEContext&);  // recompiled
void fn_sub_583520_00583520(EEContext&);  // generated body
void fn_sub_583520_00583520__recomp(EEContext&);  // recompiled
void fn_sub_5835A8_005835a8(EEContext&);  // generated body
void fn_sub_5835A8_005835a8__recomp(EEContext&);  // recompiled
void fn_sub_5847A8_005847a8(EEContext&);  // generated body
void fn_sub_5847A8_005847a8__recomp(EEContext&);  // recompiled
void fn_sub_5847D0_005847d0(EEContext&);  // generated body
void fn_sub_5847D0_005847d0__recomp(EEContext&);  // recompiled
void fn_sub_584C80_00584c80(EEContext&);  // generated body
void fn_sub_584C80_00584c80__recomp(EEContext&);  // recompiled
void fn_sub_584CD8_00584cd8(EEContext&);  // generated body
void fn_sub_584CD8_00584cd8__recomp(EEContext&);  // recompiled
void fn_sub_584E08_00584e08(EEContext&);  // generated body
void fn_sub_584E08_00584e08__recomp(EEContext&);  // recompiled
void fn_sub_585050_00585050(EEContext&);  // generated body
void fn_sub_585050_00585050__recomp(EEContext&);  // recompiled
void fn_sub_585100_00585100(EEContext&);  // generated body
void fn_sub_585100_00585100__recomp(EEContext&);  // recompiled
void fn_WTLS_get_table_1_005851b0(EEContext&);  // generated body
void fn_WTLS_get_table_1_005851b0__recomp(EEContext&);  // recompiled
void fn_sub_5851D0_005851d0(EEContext&);  // generated body
void fn_sub_5851D0_005851d0__recomp(EEContext&);  // recompiled
void fn_sub_585210_00585210(EEContext&);  // generated body
void fn_sub_585210_00585210__recomp(EEContext&);  // recompiled
void fn_sub_5852F8_005852f8(EEContext&);  // generated body
void fn_sub_5852F8_005852f8__recomp(EEContext&);  // recompiled
void fn_sub_585360_00585360(EEContext&);  // generated body
void fn_sub_585360_00585360__recomp(EEContext&);  // recompiled
void fn_sub_5853B8_005853b8(EEContext&);  // generated body
void fn_sub_5853B8_005853b8__recomp(EEContext&);  // recompiled
void fn_sub_585410_00585410(EEContext&);  // generated body
void fn_sub_585410_00585410__recomp(EEContext&);  // recompiled
void fn_atan2l_11_00585468(EEContext&);  // generated body
void fn_atan2l_11_00585468__recomp(EEContext&);  // recompiled
void fn_cosl_11_00585480(EEContext&);  // generated body
void fn_cosl_11_00585480__recomp(EEContext&);  // recompiled
void fn_sub_585578_00585578(EEContext&);  // generated body
void fn_sub_585578_00585578__recomp(EEContext&);  // recompiled
void fn_log10l_11_00585628(EEContext&);  // generated body
void fn_log10l_11_00585628__recomp(EEContext&);  // recompiled
void fn_sub_585698_00585698(EEContext&);  // generated body
void fn_sub_585698_00585698__recomp(EEContext&);  // recompiled
void fn_sub_585738_00585738(EEContext&);  // generated body
void fn_sub_585738_00585738__recomp(EEContext&);  // recompiled
void fn_sub_5857B8_005857b8(EEContext&);  // generated body
void fn_sub_5857B8_005857b8__recomp(EEContext&);  // recompiled
void fn_sub_585960_00585960(EEContext&);  // generated body
void fn_sub_585960_00585960__recomp(EEContext&);  // recompiled
void fn_sub_585A20_00585a20(EEContext&);  // generated body
void fn_sub_585A20_00585a20__recomp(EEContext&);  // recompiled
void fn_sub_585AC8_00585ac8(EEContext&);  // generated body
void fn_sub_585AC8_00585ac8__recomp(EEContext&);  // recompiled
void fn_sub_585B40_00585b40(EEContext&);  // generated body
void fn_sub_585B40_00585b40__recomp(EEContext&);  // recompiled
void fn_sub_585BA8_00585ba8(EEContext&);  // generated body
void fn_sub_585BA8_00585ba8__recomp(EEContext&);  // recompiled
void fn_sub_585BC0_00585bc0(EEContext&);  // generated body
void fn_sub_585BC0_00585bc0__recomp(EEContext&);  // recompiled
void fn_sub_585C08_00585c08(EEContext&);  // generated body
void fn_sub_585C08_00585c08__recomp(EEContext&);  // recompiled
void fn_sub_585C50_00585c50(EEContext&);  // generated body
void fn_sub_585C50_00585c50__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_3_00585c70(EEContext&);  // generated body
void fn_r_lock_def_free_3_00585c70__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_3_00585c90(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_3_00585c90__recomp(EEContext&);  // recompiled
void fn_sub_585DA8_00585da8(EEContext&);  // generated body
void fn_sub_585DA8_00585da8__recomp(EEContext&);  // recompiled
void fn_sub_585DD8_00585dd8(EEContext&);  // generated body
void fn_sub_585DD8_00585dd8__recomp(EEContext&);  // recompiled
void fn_sub_585E40_00585e40(EEContext&);  // generated body
void fn_sub_585E40_00585e40__recomp(EEContext&);  // recompiled
void fn_sub_585E70_00585e70(EEContext&);  // generated body
void fn_sub_585E70_00585e70__recomp(EEContext&);  // recompiled
void fn_sub_585F38_00585f38(EEContext&);  // generated body
void fn_sub_585F38_00585f38__recomp(EEContext&);  // recompiled
void fn_sub_5860E8_005860e8(EEContext&);  // generated body
void fn_sub_5860E8_005860e8__recomp(EEContext&);  // recompiled
void fn_sub_586130_00586130(EEContext&);  // generated body
void fn_sub_586130_00586130__recomp(EEContext&);  // recompiled
void fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138(EEContext&);  // generated body
void fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138__recomp(EEContext&);  // recompiled
void fn_sub_586140_00586140(EEContext&);  // generated body
void fn_sub_586140_00586140__recomp(EEContext&);  // recompiled
void fn_sub_5861B8_005861b8(EEContext&);  // generated body
void fn_sub_5861B8_005861b8__recomp(EEContext&);  // recompiled
void fn_sub_586200_00586200(EEContext&);  // generated body
void fn_sub_586200_00586200__recomp(EEContext&);  // recompiled
void fn_sub_586248_00586248(EEContext&);  // generated body
void fn_sub_586248_00586248__recomp(EEContext&);  // recompiled
void fn_sub_5862F0_005862f0(EEContext&);  // generated body
void fn_sub_5862F0_005862f0__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_4_005863f8(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_4_005863f8__recomp(EEContext&);  // recompiled
void fn_sub_586428_00586428(EEContext&);  // generated body
void fn_sub_586428_00586428__recomp(EEContext&);  // recompiled
void fn_sub_5864A8_005864a8(EEContext&);  // generated body
void fn_sub_5864A8_005864a8__recomp(EEContext&);  // recompiled
void fn_sub_5864C0_005864c0(EEContext&);  // generated body
void fn_sub_5864C0_005864c0__recomp(EEContext&);  // recompiled
void fn_sub_586530_00586530(EEContext&);  // generated body
void fn_sub_586530_00586530__recomp(EEContext&);  // recompiled
void fn_sub_5865A8_005865a8(EEContext&);  // generated body
void fn_sub_5865A8_005865a8__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_lock_free_4_005865c0(EEContext&);  // generated body
void fn_R_LOCK_DEF_lock_free_4_005865c0__recomp(EEContext&);  // recompiled
void fn_sub_586610_00586610(EEContext&);  // generated body
void fn_sub_586610_00586610__recomp(EEContext&);  // recompiled
void fn_sub_586800_00586800(EEContext&);  // generated body
void fn_sub_586800_00586800__recomp(EEContext&);  // recompiled
void fn_sub_586858_00586858(EEContext&);  // generated body
void fn_sub_586858_00586858__recomp(EEContext&);  // recompiled
void fn_sub_5868C0_005868c0(EEContext&);  // generated body
void fn_sub_5868C0_005868c0__recomp(EEContext&);  // recompiled
void fn_sub_586950_00586950(EEContext&);  // generated body
void fn_sub_586950_00586950__recomp(EEContext&);  // recompiled
void fn_sub_586A08_00586a08(EEContext&);  // generated body
void fn_sub_586A08_00586a08__recomp(EEContext&);  // recompiled
void fn_sub_586A10_00586a10(EEContext&);  // generated body
void fn_sub_586A10_00586a10__recomp(EEContext&);  // recompiled
void fn_sub_586AA0_00586aa0(EEContext&);  // generated body
void fn_sub_586AA0_00586aa0__recomp(EEContext&);  // recompiled
void fn_sub_586AD0_00586ad0(EEContext&);  // generated body
void fn_sub_586AD0_00586ad0__recomp(EEContext&);  // recompiled
void fn_sub_586B58_00586b58(EEContext&);  // generated body
void fn_sub_586B58_00586b58__recomp(EEContext&);  // recompiled
void fn_sub_587268_00587268(EEContext&);  // generated body
void fn_sub_587268_00587268__recomp(EEContext&);  // recompiled
void fn_sub_587310_00587310(EEContext&);  // generated body
void fn_sub_587310_00587310__recomp(EEContext&);  // recompiled
void fn_sub_587338_00587338(EEContext&);  // generated body
void fn_sub_587338_00587338__recomp(EEContext&);  // recompiled
void fn_sub_5874D8_005874d8(EEContext&);  // generated body
void fn_sub_5874D8_005874d8__recomp(EEContext&);  // recompiled
void fn_sub_587520_00587520(EEContext&);  // generated body
void fn_sub_587520_00587520__recomp(EEContext&);  // recompiled
void fn_sub_587540_00587540(EEContext&);  // generated body
void fn_sub_587540_00587540__recomp(EEContext&);  // recompiled
void fn_sub_5875E8_005875e8(EEContext&);  // generated body
void fn_sub_5875E8_005875e8__recomp(EEContext&);  // recompiled
void fn_sub_587600_00587600(EEContext&);  // generated body
void fn_sub_587600_00587600__recomp(EEContext&);  // recompiled
void fn_sub_587638_00587638(EEContext&);  // generated body
void fn_sub_587638_00587638__recomp(EEContext&);  // recompiled
void fn_sub_587718_00587718(EEContext&);  // generated body
void fn_sub_587718_00587718__recomp(EEContext&);  // recompiled
void fn_sub_587780_00587780(EEContext&);  // generated body
void fn_sub_587780_00587780__recomp(EEContext&);  // recompiled
void fn_sub_5878D8_005878d8(EEContext&);  // generated body
void fn_sub_5878D8_005878d8__recomp(EEContext&);  // recompiled
void fn_sub_587A90_00587a90(EEContext&);  // generated body
void fn_sub_587A90_00587a90__recomp(EEContext&);  // recompiled
void fn___errno_13_00587b00(EEContext&);  // generated body
void fn___errno_13_00587b00__recomp(EEContext&);  // recompiled
void fn_sub_587B10_00587b10(EEContext&);  // generated body
void fn_sub_587B10_00587b10__recomp(EEContext&);  // recompiled
void fn_sub_587B50_00587b50(EEContext&);  // generated body
void fn_sub_587B50_00587b50__recomp(EEContext&);  // recompiled
void fn_sub_587C10_00587c10(EEContext&);  // generated body
void fn_sub_587C10_00587c10__recomp(EEContext&);  // recompiled
void fn_sub_587CB8_00587cb8(EEContext&);  // generated body
void fn_sub_587CB8_00587cb8__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_5_00587d90(EEContext&);  // generated body
void fn_r_lock_def_free_5_00587d90__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_5_00587db0(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_5_00587db0__recomp(EEContext&);  // recompiled
void fn_sub_587DC8_00587dc8(EEContext&);  // generated body
void fn_sub_587DC8_00587dc8__recomp(EEContext&);  // recompiled
void fn_sub_587DE8_00587de8(EEContext&);  // generated body
void fn_sub_587DE8_00587de8__recomp(EEContext&);  // recompiled
void fn_sub_588138_00588138(EEContext&);  // generated body
void fn_sub_588138_00588138__recomp(EEContext&);  // recompiled
void fn_sub_5883B8_005883b8(EEContext&);  // generated body
void fn_sub_5883B8_005883b8__recomp(EEContext&);  // recompiled
void fn_sub_5883C8_005883c8(EEContext&);  // generated body
void fn_sub_5883C8_005883c8__recomp(EEContext&);  // recompiled
void fn_sub_588438_00588438(EEContext&);  // generated body
void fn_sub_588438_00588438__recomp(EEContext&);  // recompiled
void fn_sub_5884A8_005884a8(EEContext&);  // generated body
void fn_sub_5884A8_005884a8__recomp(EEContext&);  // recompiled
void fn_sub_588518_00588518(EEContext&);  // generated body
void fn_sub_588518_00588518__recomp(EEContext&);  // recompiled
void fn_sub_588558_00588558(EEContext&);  // generated body
void fn_sub_588558_00588558__recomp(EEContext&);  // recompiled
void fn_sub_588560_00588560(EEContext&);  // generated body
void fn_sub_588560_00588560__recomp(EEContext&);  // recompiled
void fn_sub_5885B0_005885b0(EEContext&);  // generated body
void fn_sub_5885B0_005885b0__recomp(EEContext&);  // recompiled
void fn_sub_5885F8_005885f8(EEContext&);  // generated body
void fn_sub_5885F8_005885f8__recomp(EEContext&);  // recompiled
void fn_sub_58C130_0058c130(EEContext&);  // generated body
void fn_sub_58C130_0058c130__recomp(EEContext&);  // recompiled
void fn_sub_58C140_0058c140(EEContext&);  // generated body
void fn_sub_58C140_0058c140__recomp(EEContext&);  // recompiled
void fn_sub_58C168_0058c168(EEContext&);  // generated body
void fn_sub_58C168_0058c168__recomp(EEContext&);  // recompiled
void fn_sub_58C170_0058c170(EEContext&);  // generated body
void fn_sub_58C170_0058c170__recomp(EEContext&);  // recompiled
void fn_sub_59C9F0_0059c9f0(EEContext&);  // generated body
void fn_sub_59C9F0_0059c9f0__recomp(EEContext&);  // recompiled
void fn_sub_59CA00_0059ca00(EEContext&);  // generated body
void fn_sub_59CA00_0059ca00__recomp(EEContext&);  // recompiled
void fn_sub_59CA48_0059ca48(EEContext&);  // generated body
void fn_sub_59CA48_0059ca48__recomp(EEContext&);  // recompiled
void fn_sub_59CAD0_0059cad0(EEContext&);  // generated body
void fn_sub_59CAD0_0059cad0__recomp(EEContext&);  // recompiled
void fn_sub_59CB50_0059cb50(EEContext&);  // generated body
void fn_sub_59CB50_0059cb50__recomp(EEContext&);  // recompiled
void fn_sub_59CB58_0059cb58(EEContext&);  // generated body
void fn_sub_59CB58_0059cb58__recomp(EEContext&);  // recompiled
void fn_sub_59CB60_0059cb60(EEContext&);  // generated body
void fn_sub_59CB60_0059cb60__recomp(EEContext&);  // recompiled
void fn_sub_59CB90_0059cb90(EEContext&);  // generated body
void fn_sub_59CB90_0059cb90__recomp(EEContext&);  // recompiled
void fn_sub_59CC08_0059cc08(EEContext&);  // generated body
void fn_sub_59CC08_0059cc08__recomp(EEContext&);  // recompiled
void fn_sub_59CC30_0059cc30(EEContext&);  // generated body
void fn_sub_59CC30_0059cc30__recomp(EEContext&);  // recompiled
void fn_sub_59CC48_0059cc48(EEContext&);  // generated body
void fn_sub_59CC48_0059cc48__recomp(EEContext&);  // recompiled
void fn_sub_59CCF8_0059ccf8(EEContext&);  // generated body
void fn_sub_59CCF8_0059ccf8__recomp(EEContext&);  // recompiled
void fn_sub_59CD08_0059cd08(EEContext&);  // generated body
void fn_sub_59CD08_0059cd08__recomp(EEContext&);  // recompiled
void fn_sub_59CD60_0059cd60(EEContext&);  // generated body
void fn_sub_59CD60_0059cd60__recomp(EEContext&);  // recompiled
void fn_sub_59CE28_0059ce28(EEContext&);  // generated body
void fn_sub_59CE28_0059ce28__recomp(EEContext&);  // recompiled
void fn_sub_59CEA8_0059cea8(EEContext&);  // generated body
void fn_sub_59CEA8_0059cea8__recomp(EEContext&);  // recompiled
void fn_sub_59CEB0_0059ceb0(EEContext&);  // generated body
void fn_sub_59CEB0_0059ceb0__recomp(EEContext&);  // recompiled
void fn_sub_59CEB8_0059ceb8(EEContext&);  // generated body
void fn_sub_59CEB8_0059ceb8__recomp(EEContext&);  // recompiled
void fn_sub_59CEC0_0059cec0(EEContext&);  // generated body
void fn_sub_59CEC0_0059cec0__recomp(EEContext&);  // recompiled
void fn_sub_59CF28_0059cf28(EEContext&);  // generated body
void fn_sub_59CF28_0059cf28__recomp(EEContext&);  // recompiled
void fn_sub_59CF70_0059cf70(EEContext&);  // generated body
void fn_sub_59CF70_0059cf70__recomp(EEContext&);  // recompiled
void fn_sub_599408_00599408(EEContext&);  // generated body
void fn_sub_599408_00599408__recomp(EEContext&);  // recompiled
void fn_sub_5996B0_005996b0(EEContext&);  // generated body
void fn_sub_5996B0_005996b0__recomp(EEContext&);  // recompiled
void fn_sub_599730_00599730(EEContext&);  // generated body
void fn_sub_599730_00599730__recomp(EEContext&);  // recompiled
void fn_sub_5997F8_005997f8(EEContext&);  // generated body
void fn_sub_5997F8_005997f8__recomp(EEContext&);  // recompiled
void fn_sub_599A30_00599a30(EEContext&);  // generated body
void fn_sub_599A30_00599a30__recomp(EEContext&);  // recompiled
void fn_sub_599A78_00599a78(EEContext&);  // generated body
void fn_sub_599A78_00599a78__recomp(EEContext&);  // recompiled
void fn_sub_599B80_00599b80(EEContext&);  // generated body
void fn_sub_599B80_00599b80__recomp(EEContext&);  // recompiled
void fn_sub_599C08_00599c08(EEContext&);  // generated body
void fn_sub_599C08_00599c08__recomp(EEContext&);  // recompiled
void fn_sub_599C58_00599c58(EEContext&);  // generated body
void fn_sub_599C58_00599c58__recomp(EEContext&);  // recompiled
void fn_sub_599CC8_00599cc8(EEContext&);  // generated body
void fn_sub_599CC8_00599cc8__recomp(EEContext&);  // recompiled
void fn_sub_599D00_00599d00(EEContext&);  // generated body
void fn_sub_599D00_00599d00__recomp(EEContext&);  // recompiled
void fn_sub_599D28_00599d28(EEContext&);  // generated body
void fn_sub_599D28_00599d28__recomp(EEContext&);  // recompiled
void fn_sub_599E08_00599e08(EEContext&);  // generated body
void fn_sub_599E08_00599e08__recomp(EEContext&);  // recompiled
void fn_sub_599E48_00599e48(EEContext&);  // generated body
void fn_sub_599E48_00599e48__recomp(EEContext&);  // recompiled
void fn_sub_59A150_0059a150(EEContext&);  // generated body
void fn_sub_59A150_0059a150__recomp(EEContext&);  // recompiled
void fn_sub_59A168_0059a168(EEContext&);  // generated body
void fn_sub_59A168_0059a168__recomp(EEContext&);  // recompiled
void fn_sub_59A200_0059a200(EEContext&);  // generated body
void fn_sub_59A200_0059a200__recomp(EEContext&);  // recompiled
void fn_sub_59A458_0059a458(EEContext&);  // generated body
void fn_sub_59A458_0059a458__recomp(EEContext&);  // recompiled
void fn_sub_59A560_0059a560(EEContext&);  // generated body
void fn_sub_59A560_0059a560__recomp(EEContext&);  // recompiled
void fn_sub_59A7E0_0059a7e0(EEContext&);  // generated body
void fn_sub_59A7E0_0059a7e0__recomp(EEContext&);  // recompiled
void fn_sub_59A860_0059a860(EEContext&);  // generated body
void fn_sub_59A860_0059a860__recomp(EEContext&);  // recompiled
void fn_sub_59A870_0059a870(EEContext&);  // generated body
void fn_sub_59A870_0059a870__recomp(EEContext&);  // recompiled
void fn_sub_59B490_0059b490(EEContext&);  // generated body
void fn_sub_59B490_0059b490__recomp(EEContext&);  // recompiled
void fn_sub_59B4B0_0059b4b0(EEContext&);  // generated body
void fn_sub_59B4B0_0059b4b0__recomp(EEContext&);  // recompiled
void fn_sub_59BB88_0059bb88(EEContext&);  // generated body
void fn_sub_59BB88_0059bb88__recomp(EEContext&);  // recompiled
void fn_sub_59BC20_0059bc20(EEContext&);  // generated body
void fn_sub_59BC20_0059bc20__recomp(EEContext&);  // recompiled
void fn_sub_59BC88_0059bc88(EEContext&);  // generated body
void fn_sub_59BC88_0059bc88__recomp(EEContext&);  // recompiled
void fn_sub_59BCB8_0059bcb8(EEContext&);  // generated body
void fn_sub_59BCB8_0059bcb8__recomp(EEContext&);  // recompiled
void fn_sub_59BDD0_0059bdd0(EEContext&);  // generated body
void fn_sub_59BDD0_0059bdd0__recomp(EEContext&);  // recompiled
void fn_sub_59BE10_0059be10(EEContext&);  // generated body
void fn_sub_59BE10_0059be10__recomp(EEContext&);  // recompiled
void fn_sub_59BE18_0059be18(EEContext&);  // generated body
void fn_sub_59BE18_0059be18__recomp(EEContext&);  // recompiled
void fn_sub_59BE30_0059be30(EEContext&);  // generated body
void fn_sub_59BE30_0059be30__recomp(EEContext&);  // recompiled
void fn_sub_59BE48_0059be48(EEContext&);  // generated body
void fn_sub_59BE48_0059be48__recomp(EEContext&);  // recompiled
void fn_sub_59BE60_0059be60(EEContext&);  // generated body
void fn_sub_59BE60_0059be60__recomp(EEContext&);  // recompiled
void fn_sub_59BE78_0059be78(EEContext&);  // generated body
void fn_sub_59BE78_0059be78__recomp(EEContext&);  // recompiled
void fn_sub_59F970_0059f970(EEContext&);  // generated body
void fn_sub_59F970_0059f970__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_22_0059f9e0(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_22_0059f9e0__recomp(EEContext&);  // recompiled
void fn_sub_59F9F0_0059f9f0(EEContext&);  // generated body
void fn_sub_59F9F0_0059f9f0__recomp(EEContext&);  // recompiled
void fn_sub_59FAA8_0059faa8(EEContext&);  // generated body
void fn_sub_59FAA8_0059faa8__recomp(EEContext&);  // recompiled
void fn_sub_59FBC0_0059fbc0(EEContext&);  // generated body
void fn_sub_59FBC0_0059fbc0__recomp(EEContext&);  // recompiled
void fn_sub_59FC10_0059fc10(EEContext&);  // generated body
void fn_sub_59FC10_0059fc10__recomp(EEContext&);  // recompiled
void fn_sub_59FCB0_0059fcb0(EEContext&);  // generated body
void fn_sub_59FCB0_0059fcb0__recomp(EEContext&);  // recompiled
void fn_sub_59FCC0_0059fcc0(EEContext&);  // generated body
void fn_sub_59FCC0_0059fcc0__recomp(EEContext&);  // recompiled
void fn_sub_59FD50_0059fd50(EEContext&);  // generated body
void fn_sub_59FD50_0059fd50__recomp(EEContext&);  // recompiled
void fn_sub_5A0238_005a0238(EEContext&);  // generated body
void fn_sub_5A0238_005a0238__recomp(EEContext&);  // recompiled
void fn_sub_5A0268_005a0268(EEContext&);  // generated body
void fn_sub_5A0268_005a0268__recomp(EEContext&);  // recompiled
void fn_sub_5A02C8_005a02c8(EEContext&);  // generated body
void fn_sub_5A02C8_005a02c8__recomp(EEContext&);  // recompiled
void fn_sub_5A0320_005a0320(EEContext&);  // generated body
void fn_sub_5A0320_005a0320__recomp(EEContext&);  // recompiled
void fn_sub_5A0370_005a0370(EEContext&);  // generated body
void fn_sub_5A0370_005a0370__recomp(EEContext&);  // recompiled
void fn_sub_5A0388_005a0388(EEContext&);  // generated body
void fn_sub_5A0388_005a0388__recomp(EEContext&);  // recompiled
void fn_sub_5A1108_005a1108(EEContext&);  // generated body
void fn_sub_5A1108_005a1108__recomp(EEContext&);  // recompiled
void fn_sub_5A1340_005a1340(EEContext&);  // generated body
void fn_sub_5A1340_005a1340__recomp(EEContext&);  // recompiled
void fn_sub_77F598_0077f598(EEContext&);  // generated body
void fn_sub_77F598_0077f598__recomp(EEContext&);  // recompiled
void fn_sub_77F5F8_0077f5f8(EEContext&);  // generated body
void fn_sub_77F5F8_0077f5f8__recomp(EEContext&);  // recompiled
void fn_sub_77F65C_0077f65c(EEContext&);  // generated body
void fn_sub_77F65C_0077f65c__recomp(EEContext&);  // recompiled
void fn_sub_77F67C_0077f67c(EEContext&);  // generated body
void fn_sub_77F67C_0077f67c__recomp(EEContext&);  // recompiled
void fn_sub_77F6B4_0077f6b4(EEContext&);  // generated body
void fn_sub_77F6B4_0077f6b4__recomp(EEContext&);  // recompiled
void fn_sub_77F704_0077f704(EEContext&);  // generated body
void fn_sub_77F704_0077f704__recomp(EEContext&);  // recompiled
void fn_sub_77FF10_0077ff10(EEContext&);  // generated body
void fn_sub_77FF10_0077ff10__recomp(EEContext&);  // recompiled
void fn_sub_7803D0_007803d0(EEContext&);  // generated body
void fn_sub_7803D0_007803d0__recomp(EEContext&);  // recompiled
void fn_sub_7803EC_007803ec(EEContext&);  // generated body
void fn_sub_7803EC_007803ec__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_5800F0", 0x5800F0, &recomp_gen::fn_sub_5800F0_005800f0, &recomp_gen::fn_sub_5800F0_005800f0__recomp},
    {"sub_580130", 0x580130, &recomp_gen::fn_sub_580130_00580130, &recomp_gen::fn_sub_580130_00580130__recomp},
    {"sub_580270", 0x580270, &recomp_gen::fn_sub_580270_00580270, &recomp_gen::fn_sub_580270_00580270__recomp},
    {"sub_580368", 0x580368, &recomp_gen::fn_sub_580368_00580368, &recomp_gen::fn_sub_580368_00580368__recomp},
    {"sub_580378", 0x580378, &recomp_gen::fn_sub_580378_00580378, &recomp_gen::fn_sub_580378_00580378__recomp},
    {"sub_580628", 0x580628, &recomp_gen::fn_sub_580628_00580628, &recomp_gen::fn_sub_580628_00580628__recomp},
    {"sub_580750", 0x580750, &recomp_gen::fn_sub_580750_00580750, &recomp_gen::fn_sub_580750_00580750__recomp},
    {"sub_580900", 0x580900, &recomp_gen::fn_sub_580900_00580900, &recomp_gen::fn_sub_580900_00580900__recomp},
    {"sub_580958", 0x580958, &recomp_gen::fn_sub_580958_00580958, &recomp_gen::fn_sub_580958_00580958__recomp},
    {"sub_5809B0", 0x5809B0, &recomp_gen::fn_sub_5809B0_005809b0, &recomp_gen::fn_sub_5809B0_005809b0__recomp},
    {"sub_580C80", 0x580C80, &recomp_gen::fn_sub_580C80_00580c80, &recomp_gen::fn_sub_580C80_00580c80__recomp},
    {"sub_580CB0", 0x580CB0, &recomp_gen::fn_sub_580CB0_00580cb0, &recomp_gen::fn_sub_580CB0_00580cb0__recomp},
    {"sub_580D40", 0x580D40, &recomp_gen::fn_sub_580D40_00580d40, &recomp_gen::fn_sub_580D40_00580d40__recomp},
    {"WTLS_get_table_0", 0x580DF0, &recomp_gen::fn_WTLS_get_table_0_00580df0, &recomp_gen::fn_WTLS_get_table_0_00580df0__recomp},
    {"sub_580E10", 0x580E10, &recomp_gen::fn_sub_580E10_00580e10, &recomp_gen::fn_sub_580E10_00580e10__recomp},
    {"sub_580E78", 0x580E78, &recomp_gen::fn_sub_580E78_00580e78, &recomp_gen::fn_sub_580E78_00580e78__recomp},
    {"sub_580E98", 0x580E98, &recomp_gen::fn_sub_580E98_00580e98, &recomp_gen::fn_sub_580E98_00580e98__recomp},
    {"sub_580F78", 0x580F78, &recomp_gen::fn_sub_580F78_00580f78, &recomp_gen::fn_sub_580F78_00580f78__recomp},
    {"sub_5810F0", 0x5810F0, &recomp_gen::fn_sub_5810F0_005810f0, &recomp_gen::fn_sub_5810F0_005810f0__recomp},
    {"sub_581108", 0x581108, &recomp_gen::fn_sub_581108_00581108, &recomp_gen::fn_sub_581108_00581108__recomp},
    {"sub_581120", 0x581120, &recomp_gen::fn_sub_581120_00581120, &recomp_gen::fn_sub_581120_00581120__recomp},
    {"__env_lock_11", 0x581138, &recomp_gen::fn___env_lock_11_00581138, &recomp_gen::fn___env_lock_11_00581138__recomp},
    {"sub_581148", 0x581148, &recomp_gen::fn_sub_581148_00581148, &recomp_gen::fn_sub_581148_00581148__recomp},
    {"sub_5811D0", 0x5811D0, &recomp_gen::fn_sub_5811D0_005811d0, &recomp_gen::fn_sub_5811D0_005811d0__recomp},
    {"sub_581690", 0x581690, &recomp_gen::fn_sub_581690_00581690, &recomp_gen::fn_sub_581690_00581690__recomp},
    {"sub_5816F0", 0x5816F0, &recomp_gen::fn_sub_5816F0_005816f0, &recomp_gen::fn_sub_5816F0_005816f0__recomp},
    {"sub_581798", 0x581798, &recomp_gen::fn_sub_581798_00581798, &recomp_gen::fn_sub_581798_00581798__recomp},
    {"sub_581840", 0x581840, &recomp_gen::fn_sub_581840_00581840, &recomp_gen::fn_sub_581840_00581840__recomp},
    {"sub_582798", 0x582798, &recomp_gen::fn_sub_582798_00582798, &recomp_gen::fn_sub_582798_00582798__recomp},
    {"sub_5827F0", 0x5827F0, &recomp_gen::fn_sub_5827F0_005827f0, &recomp_gen::fn_sub_5827F0_005827f0__recomp},
    {"sub_5827F8", 0x5827F8, &recomp_gen::fn_sub_5827F8_005827f8, &recomp_gen::fn_sub_5827F8_005827f8__recomp},
    {"sub_582810", 0x582810, &recomp_gen::fn_sub_582810_00582810, &recomp_gen::fn_sub_582810_00582810__recomp},
    {"sub_582828", 0x582828, &recomp_gen::fn_sub_582828_00582828, &recomp_gen::fn_sub_582828_00582828__recomp},
    {"sub_583028", 0x583028, &recomp_gen::fn_sub_583028_00583028, &recomp_gen::fn_sub_583028_00583028__recomp},
    {"sub_5833D8", 0x5833D8, &recomp_gen::fn_sub_5833D8_005833d8, &recomp_gen::fn_sub_5833D8_005833d8__recomp},
    {"sub_5833E8", 0x5833E8, &recomp_gen::fn_sub_5833E8_005833e8, &recomp_gen::fn_sub_5833E8_005833e8__recomp},
    {"sub_583410", 0x583410, &recomp_gen::fn_sub_583410_00583410, &recomp_gen::fn_sub_583410_00583410__recomp},
    {"sub_583470", 0x583470, &recomp_gen::fn_sub_583470_00583470, &recomp_gen::fn_sub_583470_00583470__recomp},
    {"sub_5834A0", 0x5834A0, &recomp_gen::fn_sub_5834A0_005834a0, &recomp_gen::fn_sub_5834A0_005834a0__recomp},
    {"sub_583500", 0x583500, &recomp_gen::fn_sub_583500_00583500, &recomp_gen::fn_sub_583500_00583500__recomp},
    {"sub_583520", 0x583520, &recomp_gen::fn_sub_583520_00583520, &recomp_gen::fn_sub_583520_00583520__recomp},
    {"sub_5835A8", 0x5835A8, &recomp_gen::fn_sub_5835A8_005835a8, &recomp_gen::fn_sub_5835A8_005835a8__recomp},
    {"sub_5847A8", 0x5847A8, &recomp_gen::fn_sub_5847A8_005847a8, &recomp_gen::fn_sub_5847A8_005847a8__recomp},
    {"sub_5847D0", 0x5847D0, &recomp_gen::fn_sub_5847D0_005847d0, &recomp_gen::fn_sub_5847D0_005847d0__recomp},
    {"sub_584C80", 0x584C80, &recomp_gen::fn_sub_584C80_00584c80, &recomp_gen::fn_sub_584C80_00584c80__recomp},
    {"sub_584CD8", 0x584CD8, &recomp_gen::fn_sub_584CD8_00584cd8, &recomp_gen::fn_sub_584CD8_00584cd8__recomp},
    {"sub_584E08", 0x584E08, &recomp_gen::fn_sub_584E08_00584e08, &recomp_gen::fn_sub_584E08_00584e08__recomp},
    {"sub_585050", 0x585050, &recomp_gen::fn_sub_585050_00585050, &recomp_gen::fn_sub_585050_00585050__recomp},
    {"sub_585100", 0x585100, &recomp_gen::fn_sub_585100_00585100, &recomp_gen::fn_sub_585100_00585100__recomp},
    {"WTLS_get_table_1", 0x5851B0, &recomp_gen::fn_WTLS_get_table_1_005851b0, &recomp_gen::fn_WTLS_get_table_1_005851b0__recomp},
    {"sub_5851D0", 0x5851D0, &recomp_gen::fn_sub_5851D0_005851d0, &recomp_gen::fn_sub_5851D0_005851d0__recomp},
    {"sub_585210", 0x585210, &recomp_gen::fn_sub_585210_00585210, &recomp_gen::fn_sub_585210_00585210__recomp},
    {"sub_5852F8", 0x5852F8, &recomp_gen::fn_sub_5852F8_005852f8, &recomp_gen::fn_sub_5852F8_005852f8__recomp},
    {"sub_585360", 0x585360, &recomp_gen::fn_sub_585360_00585360, &recomp_gen::fn_sub_585360_00585360__recomp},
    {"sub_5853B8", 0x5853B8, &recomp_gen::fn_sub_5853B8_005853b8, &recomp_gen::fn_sub_5853B8_005853b8__recomp},
    {"sub_585410", 0x585410, &recomp_gen::fn_sub_585410_00585410, &recomp_gen::fn_sub_585410_00585410__recomp},
    {"atan2l_11", 0x585468, &recomp_gen::fn_atan2l_11_00585468, &recomp_gen::fn_atan2l_11_00585468__recomp},
    {"cosl_11", 0x585480, &recomp_gen::fn_cosl_11_00585480, &recomp_gen::fn_cosl_11_00585480__recomp},
    {"sub_585578", 0x585578, &recomp_gen::fn_sub_585578_00585578, &recomp_gen::fn_sub_585578_00585578__recomp},
    {"log10l_11", 0x585628, &recomp_gen::fn_log10l_11_00585628, &recomp_gen::fn_log10l_11_00585628__recomp},
    {"sub_585698", 0x585698, &recomp_gen::fn_sub_585698_00585698, &recomp_gen::fn_sub_585698_00585698__recomp},
    {"sub_585738", 0x585738, &recomp_gen::fn_sub_585738_00585738, &recomp_gen::fn_sub_585738_00585738__recomp},
    {"sub_5857B8", 0x5857B8, &recomp_gen::fn_sub_5857B8_005857b8, &recomp_gen::fn_sub_5857B8_005857b8__recomp},
    {"sub_585960", 0x585960, &recomp_gen::fn_sub_585960_00585960, &recomp_gen::fn_sub_585960_00585960__recomp},
    {"sub_585A20", 0x585A20, &recomp_gen::fn_sub_585A20_00585a20, &recomp_gen::fn_sub_585A20_00585a20__recomp},
    {"sub_585AC8", 0x585AC8, &recomp_gen::fn_sub_585AC8_00585ac8, &recomp_gen::fn_sub_585AC8_00585ac8__recomp},
    {"sub_585B40", 0x585B40, &recomp_gen::fn_sub_585B40_00585b40, &recomp_gen::fn_sub_585B40_00585b40__recomp},
    {"sub_585BA8", 0x585BA8, &recomp_gen::fn_sub_585BA8_00585ba8, &recomp_gen::fn_sub_585BA8_00585ba8__recomp},
    {"sub_585BC0", 0x585BC0, &recomp_gen::fn_sub_585BC0_00585bc0, &recomp_gen::fn_sub_585BC0_00585bc0__recomp},
    {"sub_585C08", 0x585C08, &recomp_gen::fn_sub_585C08_00585c08, &recomp_gen::fn_sub_585C08_00585c08__recomp},
    {"sub_585C50", 0x585C50, &recomp_gen::fn_sub_585C50_00585c50, &recomp_gen::fn_sub_585C50_00585c50__recomp},
    {"r_lock_def_free_3", 0x585C70, &recomp_gen::fn_r_lock_def_free_3_00585c70, &recomp_gen::fn_r_lock_def_free_3_00585c70__recomp},
    {"r_lock_def_get_free_item_3", 0x585C90, &recomp_gen::fn_r_lock_def_get_free_item_3_00585c90, &recomp_gen::fn_r_lock_def_get_free_item_3_00585c90__recomp},
    {"sub_585DA8", 0x585DA8, &recomp_gen::fn_sub_585DA8_00585da8, &recomp_gen::fn_sub_585DA8_00585da8__recomp},
    {"sub_585DD8", 0x585DD8, &recomp_gen::fn_sub_585DD8_00585dd8, &recomp_gen::fn_sub_585DD8_00585dd8__recomp},
    {"sub_585E40", 0x585E40, &recomp_gen::fn_sub_585E40_00585e40, &recomp_gen::fn_sub_585E40_00585e40__recomp},
    {"sub_585E70", 0x585E70, &recomp_gen::fn_sub_585E70_00585e70, &recomp_gen::fn_sub_585E70_00585e70__recomp},
    {"sub_585F38", 0x585F38, &recomp_gen::fn_sub_585F38_00585f38, &recomp_gen::fn_sub_585F38_00585f38__recomp},
    {"sub_5860E8", 0x5860E8, &recomp_gen::fn_sub_5860E8_005860e8, &recomp_gen::fn_sub_5860E8_005860e8__recomp},
    {"sub_586130", 0x586130, &recomp_gen::fn_sub_586130_00586130, &recomp_gen::fn_sub_586130_00586130__recomp},
    {"tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc", 0x586138, &recomp_gen::fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138, &recomp_gen::fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138__recomp},
    {"sub_586140", 0x586140, &recomp_gen::fn_sub_586140_00586140, &recomp_gen::fn_sub_586140_00586140__recomp},
    {"sub_5861B8", 0x5861B8, &recomp_gen::fn_sub_5861B8_005861b8, &recomp_gen::fn_sub_5861B8_005861b8__recomp},
    {"sub_586200", 0x586200, &recomp_gen::fn_sub_586200_00586200, &recomp_gen::fn_sub_586200_00586200__recomp},
    {"sub_586248", 0x586248, &recomp_gen::fn_sub_586248_00586248, &recomp_gen::fn_sub_586248_00586248__recomp},
    {"sub_5862F0", 0x5862F0, &recomp_gen::fn_sub_5862F0_005862f0, &recomp_gen::fn_sub_5862F0_005862f0__recomp},
    {"r_lock_def_get_free_item_4", 0x5863F8, &recomp_gen::fn_r_lock_def_get_free_item_4_005863f8, &recomp_gen::fn_r_lock_def_get_free_item_4_005863f8__recomp},
    {"sub_586428", 0x586428, &recomp_gen::fn_sub_586428_00586428, &recomp_gen::fn_sub_586428_00586428__recomp},
    {"sub_5864A8", 0x5864A8, &recomp_gen::fn_sub_5864A8_005864a8, &recomp_gen::fn_sub_5864A8_005864a8__recomp},
    {"sub_5864C0", 0x5864C0, &recomp_gen::fn_sub_5864C0_005864c0, &recomp_gen::fn_sub_5864C0_005864c0__recomp},
    {"sub_586530", 0x586530, &recomp_gen::fn_sub_586530_00586530, &recomp_gen::fn_sub_586530_00586530__recomp},
    {"sub_5865A8", 0x5865A8, &recomp_gen::fn_sub_5865A8_005865a8, &recomp_gen::fn_sub_5865A8_005865a8__recomp},
    {"R_LOCK_DEF_lock_free_4", 0x5865C0, &recomp_gen::fn_R_LOCK_DEF_lock_free_4_005865c0, &recomp_gen::fn_R_LOCK_DEF_lock_free_4_005865c0__recomp},
    {"sub_586610", 0x586610, &recomp_gen::fn_sub_586610_00586610, &recomp_gen::fn_sub_586610_00586610__recomp},
    {"sub_586800", 0x586800, &recomp_gen::fn_sub_586800_00586800, &recomp_gen::fn_sub_586800_00586800__recomp},
    {"sub_586858", 0x586858, &recomp_gen::fn_sub_586858_00586858, &recomp_gen::fn_sub_586858_00586858__recomp},
    {"sub_5868C0", 0x5868C0, &recomp_gen::fn_sub_5868C0_005868c0, &recomp_gen::fn_sub_5868C0_005868c0__recomp},
    {"sub_586950", 0x586950, &recomp_gen::fn_sub_586950_00586950, &recomp_gen::fn_sub_586950_00586950__recomp},
    {"sub_586A08", 0x586A08, &recomp_gen::fn_sub_586A08_00586a08, &recomp_gen::fn_sub_586A08_00586a08__recomp},
    {"sub_586A10", 0x586A10, &recomp_gen::fn_sub_586A10_00586a10, &recomp_gen::fn_sub_586A10_00586a10__recomp},
    {"sub_586AA0", 0x586AA0, &recomp_gen::fn_sub_586AA0_00586aa0, &recomp_gen::fn_sub_586AA0_00586aa0__recomp},
    {"sub_586AD0", 0x586AD0, &recomp_gen::fn_sub_586AD0_00586ad0, &recomp_gen::fn_sub_586AD0_00586ad0__recomp},
    {"sub_586B58", 0x586B58, &recomp_gen::fn_sub_586B58_00586b58, &recomp_gen::fn_sub_586B58_00586b58__recomp},
    {"sub_587268", 0x587268, &recomp_gen::fn_sub_587268_00587268, &recomp_gen::fn_sub_587268_00587268__recomp},
    {"sub_587310", 0x587310, &recomp_gen::fn_sub_587310_00587310, &recomp_gen::fn_sub_587310_00587310__recomp},
    {"sub_587338", 0x587338, &recomp_gen::fn_sub_587338_00587338, &recomp_gen::fn_sub_587338_00587338__recomp},
    {"sub_5874D8", 0x5874D8, &recomp_gen::fn_sub_5874D8_005874d8, &recomp_gen::fn_sub_5874D8_005874d8__recomp},
    {"sub_587520", 0x587520, &recomp_gen::fn_sub_587520_00587520, &recomp_gen::fn_sub_587520_00587520__recomp},
    {"sub_587540", 0x587540, &recomp_gen::fn_sub_587540_00587540, &recomp_gen::fn_sub_587540_00587540__recomp},
    {"sub_5875E8", 0x5875E8, &recomp_gen::fn_sub_5875E8_005875e8, &recomp_gen::fn_sub_5875E8_005875e8__recomp},
    {"sub_587600", 0x587600, &recomp_gen::fn_sub_587600_00587600, &recomp_gen::fn_sub_587600_00587600__recomp},
    {"sub_587638", 0x587638, &recomp_gen::fn_sub_587638_00587638, &recomp_gen::fn_sub_587638_00587638__recomp},
    {"sub_587718", 0x587718, &recomp_gen::fn_sub_587718_00587718, &recomp_gen::fn_sub_587718_00587718__recomp},
    {"sub_587780", 0x587780, &recomp_gen::fn_sub_587780_00587780, &recomp_gen::fn_sub_587780_00587780__recomp},
    {"sub_5878D8", 0x5878D8, &recomp_gen::fn_sub_5878D8_005878d8, &recomp_gen::fn_sub_5878D8_005878d8__recomp},
    {"sub_587A90", 0x587A90, &recomp_gen::fn_sub_587A90_00587a90, &recomp_gen::fn_sub_587A90_00587a90__recomp},
    {"__errno_13", 0x587B00, &recomp_gen::fn___errno_13_00587b00, &recomp_gen::fn___errno_13_00587b00__recomp},
    {"sub_587B10", 0x587B10, &recomp_gen::fn_sub_587B10_00587b10, &recomp_gen::fn_sub_587B10_00587b10__recomp},
    {"sub_587B50", 0x587B50, &recomp_gen::fn_sub_587B50_00587b50, &recomp_gen::fn_sub_587B50_00587b50__recomp},
    {"sub_587C10", 0x587C10, &recomp_gen::fn_sub_587C10_00587c10, &recomp_gen::fn_sub_587C10_00587c10__recomp},
    {"sub_587CB8", 0x587CB8, &recomp_gen::fn_sub_587CB8_00587cb8, &recomp_gen::fn_sub_587CB8_00587cb8__recomp},
    {"r_lock_def_free_5", 0x587D90, &recomp_gen::fn_r_lock_def_free_5_00587d90, &recomp_gen::fn_r_lock_def_free_5_00587d90__recomp},
    {"r_lock_def_get_free_item_5", 0x587DB0, &recomp_gen::fn_r_lock_def_get_free_item_5_00587db0, &recomp_gen::fn_r_lock_def_get_free_item_5_00587db0__recomp},
    {"sub_587DC8", 0x587DC8, &recomp_gen::fn_sub_587DC8_00587dc8, &recomp_gen::fn_sub_587DC8_00587dc8__recomp},
    {"sub_587DE8", 0x587DE8, &recomp_gen::fn_sub_587DE8_00587de8, &recomp_gen::fn_sub_587DE8_00587de8__recomp},
    {"sub_588138", 0x588138, &recomp_gen::fn_sub_588138_00588138, &recomp_gen::fn_sub_588138_00588138__recomp},
    {"sub_5883B8", 0x5883B8, &recomp_gen::fn_sub_5883B8_005883b8, &recomp_gen::fn_sub_5883B8_005883b8__recomp},
    {"sub_5883C8", 0x5883C8, &recomp_gen::fn_sub_5883C8_005883c8, &recomp_gen::fn_sub_5883C8_005883c8__recomp},
    {"sub_588438", 0x588438, &recomp_gen::fn_sub_588438_00588438, &recomp_gen::fn_sub_588438_00588438__recomp},
    {"sub_5884A8", 0x5884A8, &recomp_gen::fn_sub_5884A8_005884a8, &recomp_gen::fn_sub_5884A8_005884a8__recomp},
    {"sub_588518", 0x588518, &recomp_gen::fn_sub_588518_00588518, &recomp_gen::fn_sub_588518_00588518__recomp},
    {"sub_588558", 0x588558, &recomp_gen::fn_sub_588558_00588558, &recomp_gen::fn_sub_588558_00588558__recomp},
    {"sub_588560", 0x588560, &recomp_gen::fn_sub_588560_00588560, &recomp_gen::fn_sub_588560_00588560__recomp},
    {"sub_5885B0", 0x5885B0, &recomp_gen::fn_sub_5885B0_005885b0, &recomp_gen::fn_sub_5885B0_005885b0__recomp},
    {"sub_5885F8", 0x5885F8, &recomp_gen::fn_sub_5885F8_005885f8, &recomp_gen::fn_sub_5885F8_005885f8__recomp},
    {"sub_58C130", 0x58C130, &recomp_gen::fn_sub_58C130_0058c130, &recomp_gen::fn_sub_58C130_0058c130__recomp},
    {"sub_58C140", 0x58C140, &recomp_gen::fn_sub_58C140_0058c140, &recomp_gen::fn_sub_58C140_0058c140__recomp},
    {"sub_58C168", 0x58C168, &recomp_gen::fn_sub_58C168_0058c168, &recomp_gen::fn_sub_58C168_0058c168__recomp},
    {"sub_58C170", 0x58C170, &recomp_gen::fn_sub_58C170_0058c170, &recomp_gen::fn_sub_58C170_0058c170__recomp},
    {"sub_59C9F0", 0x59C9F0, &recomp_gen::fn_sub_59C9F0_0059c9f0, &recomp_gen::fn_sub_59C9F0_0059c9f0__recomp},
    {"sub_59CA00", 0x59CA00, &recomp_gen::fn_sub_59CA00_0059ca00, &recomp_gen::fn_sub_59CA00_0059ca00__recomp},
    {"sub_59CA48", 0x59CA48, &recomp_gen::fn_sub_59CA48_0059ca48, &recomp_gen::fn_sub_59CA48_0059ca48__recomp},
    {"sub_59CAD0", 0x59CAD0, &recomp_gen::fn_sub_59CAD0_0059cad0, &recomp_gen::fn_sub_59CAD0_0059cad0__recomp},
    {"sub_59CB50", 0x59CB50, &recomp_gen::fn_sub_59CB50_0059cb50, &recomp_gen::fn_sub_59CB50_0059cb50__recomp},
    {"sub_59CB58", 0x59CB58, &recomp_gen::fn_sub_59CB58_0059cb58, &recomp_gen::fn_sub_59CB58_0059cb58__recomp},
    {"sub_59CB60", 0x59CB60, &recomp_gen::fn_sub_59CB60_0059cb60, &recomp_gen::fn_sub_59CB60_0059cb60__recomp},
    {"sub_59CB90", 0x59CB90, &recomp_gen::fn_sub_59CB90_0059cb90, &recomp_gen::fn_sub_59CB90_0059cb90__recomp},
    {"sub_59CC08", 0x59CC08, &recomp_gen::fn_sub_59CC08_0059cc08, &recomp_gen::fn_sub_59CC08_0059cc08__recomp},
    {"sub_59CC30", 0x59CC30, &recomp_gen::fn_sub_59CC30_0059cc30, &recomp_gen::fn_sub_59CC30_0059cc30__recomp},
    {"sub_59CC48", 0x59CC48, &recomp_gen::fn_sub_59CC48_0059cc48, &recomp_gen::fn_sub_59CC48_0059cc48__recomp},
    {"sub_59CCF8", 0x59CCF8, &recomp_gen::fn_sub_59CCF8_0059ccf8, &recomp_gen::fn_sub_59CCF8_0059ccf8__recomp},
    {"sub_59CD08", 0x59CD08, &recomp_gen::fn_sub_59CD08_0059cd08, &recomp_gen::fn_sub_59CD08_0059cd08__recomp},
    {"sub_59CD60", 0x59CD60, &recomp_gen::fn_sub_59CD60_0059cd60, &recomp_gen::fn_sub_59CD60_0059cd60__recomp},
    {"sub_59CE28", 0x59CE28, &recomp_gen::fn_sub_59CE28_0059ce28, &recomp_gen::fn_sub_59CE28_0059ce28__recomp},
    {"sub_59CEA8", 0x59CEA8, &recomp_gen::fn_sub_59CEA8_0059cea8, &recomp_gen::fn_sub_59CEA8_0059cea8__recomp},
    {"sub_59CEB0", 0x59CEB0, &recomp_gen::fn_sub_59CEB0_0059ceb0, &recomp_gen::fn_sub_59CEB0_0059ceb0__recomp},
    {"sub_59CEB8", 0x59CEB8, &recomp_gen::fn_sub_59CEB8_0059ceb8, &recomp_gen::fn_sub_59CEB8_0059ceb8__recomp},
    {"sub_59CEC0", 0x59CEC0, &recomp_gen::fn_sub_59CEC0_0059cec0, &recomp_gen::fn_sub_59CEC0_0059cec0__recomp},
    {"sub_59CF28", 0x59CF28, &recomp_gen::fn_sub_59CF28_0059cf28, &recomp_gen::fn_sub_59CF28_0059cf28__recomp},
    {"sub_59CF70", 0x59CF70, &recomp_gen::fn_sub_59CF70_0059cf70, &recomp_gen::fn_sub_59CF70_0059cf70__recomp},
    {"sub_599408", 0x599408, &recomp_gen::fn_sub_599408_00599408, &recomp_gen::fn_sub_599408_00599408__recomp},
    {"sub_5996B0", 0x5996B0, &recomp_gen::fn_sub_5996B0_005996b0, &recomp_gen::fn_sub_5996B0_005996b0__recomp},
    {"sub_599730", 0x599730, &recomp_gen::fn_sub_599730_00599730, &recomp_gen::fn_sub_599730_00599730__recomp},
    {"sub_5997F8", 0x5997F8, &recomp_gen::fn_sub_5997F8_005997f8, &recomp_gen::fn_sub_5997F8_005997f8__recomp},
    {"sub_599A30", 0x599A30, &recomp_gen::fn_sub_599A30_00599a30, &recomp_gen::fn_sub_599A30_00599a30__recomp},
    {"sub_599A78", 0x599A78, &recomp_gen::fn_sub_599A78_00599a78, &recomp_gen::fn_sub_599A78_00599a78__recomp},
    {"sub_599B80", 0x599B80, &recomp_gen::fn_sub_599B80_00599b80, &recomp_gen::fn_sub_599B80_00599b80__recomp},
    {"sub_599C08", 0x599C08, &recomp_gen::fn_sub_599C08_00599c08, &recomp_gen::fn_sub_599C08_00599c08__recomp},
    {"sub_599C58", 0x599C58, &recomp_gen::fn_sub_599C58_00599c58, &recomp_gen::fn_sub_599C58_00599c58__recomp},
    {"sub_599CC8", 0x599CC8, &recomp_gen::fn_sub_599CC8_00599cc8, &recomp_gen::fn_sub_599CC8_00599cc8__recomp},
    {"sub_599D00", 0x599D00, &recomp_gen::fn_sub_599D00_00599d00, &recomp_gen::fn_sub_599D00_00599d00__recomp},
    {"sub_599D28", 0x599D28, &recomp_gen::fn_sub_599D28_00599d28, &recomp_gen::fn_sub_599D28_00599d28__recomp},
    {"sub_599E08", 0x599E08, &recomp_gen::fn_sub_599E08_00599e08, &recomp_gen::fn_sub_599E08_00599e08__recomp},
    {"sub_599E48", 0x599E48, &recomp_gen::fn_sub_599E48_00599e48, &recomp_gen::fn_sub_599E48_00599e48__recomp},
    {"sub_59A150", 0x59A150, &recomp_gen::fn_sub_59A150_0059a150, &recomp_gen::fn_sub_59A150_0059a150__recomp},
    {"sub_59A168", 0x59A168, &recomp_gen::fn_sub_59A168_0059a168, &recomp_gen::fn_sub_59A168_0059a168__recomp},
    {"sub_59A200", 0x59A200, &recomp_gen::fn_sub_59A200_0059a200, &recomp_gen::fn_sub_59A200_0059a200__recomp},
    {"sub_59A458", 0x59A458, &recomp_gen::fn_sub_59A458_0059a458, &recomp_gen::fn_sub_59A458_0059a458__recomp},
    {"sub_59A560", 0x59A560, &recomp_gen::fn_sub_59A560_0059a560, &recomp_gen::fn_sub_59A560_0059a560__recomp},
    {"sub_59A7E0", 0x59A7E0, &recomp_gen::fn_sub_59A7E0_0059a7e0, &recomp_gen::fn_sub_59A7E0_0059a7e0__recomp},
    {"sub_59A860", 0x59A860, &recomp_gen::fn_sub_59A860_0059a860, &recomp_gen::fn_sub_59A860_0059a860__recomp},
    {"sub_59A870", 0x59A870, &recomp_gen::fn_sub_59A870_0059a870, &recomp_gen::fn_sub_59A870_0059a870__recomp},
    {"sub_59B490", 0x59B490, &recomp_gen::fn_sub_59B490_0059b490, &recomp_gen::fn_sub_59B490_0059b490__recomp},
    {"sub_59B4B0", 0x59B4B0, &recomp_gen::fn_sub_59B4B0_0059b4b0, &recomp_gen::fn_sub_59B4B0_0059b4b0__recomp},
    {"sub_59BB88", 0x59BB88, &recomp_gen::fn_sub_59BB88_0059bb88, &recomp_gen::fn_sub_59BB88_0059bb88__recomp},
    {"sub_59BC20", 0x59BC20, &recomp_gen::fn_sub_59BC20_0059bc20, &recomp_gen::fn_sub_59BC20_0059bc20__recomp},
    {"sub_59BC88", 0x59BC88, &recomp_gen::fn_sub_59BC88_0059bc88, &recomp_gen::fn_sub_59BC88_0059bc88__recomp},
    {"sub_59BCB8", 0x59BCB8, &recomp_gen::fn_sub_59BCB8_0059bcb8, &recomp_gen::fn_sub_59BCB8_0059bcb8__recomp},
    {"sub_59BDD0", 0x59BDD0, &recomp_gen::fn_sub_59BDD0_0059bdd0, &recomp_gen::fn_sub_59BDD0_0059bdd0__recomp},
    {"sub_59BE10", 0x59BE10, &recomp_gen::fn_sub_59BE10_0059be10, &recomp_gen::fn_sub_59BE10_0059be10__recomp},
    {"sub_59BE18", 0x59BE18, &recomp_gen::fn_sub_59BE18_0059be18, &recomp_gen::fn_sub_59BE18_0059be18__recomp},
    {"sub_59BE30", 0x59BE30, &recomp_gen::fn_sub_59BE30_0059be30, &recomp_gen::fn_sub_59BE30_0059be30__recomp},
    {"sub_59BE48", 0x59BE48, &recomp_gen::fn_sub_59BE48_0059be48, &recomp_gen::fn_sub_59BE48_0059be48__recomp},
    {"sub_59BE60", 0x59BE60, &recomp_gen::fn_sub_59BE60_0059be60, &recomp_gen::fn_sub_59BE60_0059be60__recomp},
    {"sub_59BE78", 0x59BE78, &recomp_gen::fn_sub_59BE78_0059be78, &recomp_gen::fn_sub_59BE78_0059be78__recomp},
    {"sub_59F970", 0x59F970, &recomp_gen::fn_sub_59F970_0059f970, &recomp_gen::fn_sub_59F970_0059f970__recomp},
    {"sceLibgcc32GetErxEntries_22", 0x59F9E0, &recomp_gen::fn_sceLibgcc32GetErxEntries_22_0059f9e0, &recomp_gen::fn_sceLibgcc32GetErxEntries_22_0059f9e0__recomp},
    {"sub_59F9F0", 0x59F9F0, &recomp_gen::fn_sub_59F9F0_0059f9f0, &recomp_gen::fn_sub_59F9F0_0059f9f0__recomp},
    {"sub_59FAA8", 0x59FAA8, &recomp_gen::fn_sub_59FAA8_0059faa8, &recomp_gen::fn_sub_59FAA8_0059faa8__recomp},
    {"sub_59FBC0", 0x59FBC0, &recomp_gen::fn_sub_59FBC0_0059fbc0, &recomp_gen::fn_sub_59FBC0_0059fbc0__recomp},
    {"sub_59FC10", 0x59FC10, &recomp_gen::fn_sub_59FC10_0059fc10, &recomp_gen::fn_sub_59FC10_0059fc10__recomp},
    {"sub_59FCB0", 0x59FCB0, &recomp_gen::fn_sub_59FCB0_0059fcb0, &recomp_gen::fn_sub_59FCB0_0059fcb0__recomp},
    {"sub_59FCC0", 0x59FCC0, &recomp_gen::fn_sub_59FCC0_0059fcc0, &recomp_gen::fn_sub_59FCC0_0059fcc0__recomp},
    {"sub_59FD50", 0x59FD50, &recomp_gen::fn_sub_59FD50_0059fd50, &recomp_gen::fn_sub_59FD50_0059fd50__recomp},
    {"sub_5A0238", 0x5A0238, &recomp_gen::fn_sub_5A0238_005a0238, &recomp_gen::fn_sub_5A0238_005a0238__recomp},
    {"sub_5A0268", 0x5A0268, &recomp_gen::fn_sub_5A0268_005a0268, &recomp_gen::fn_sub_5A0268_005a0268__recomp},
    {"sub_5A02C8", 0x5A02C8, &recomp_gen::fn_sub_5A02C8_005a02c8, &recomp_gen::fn_sub_5A02C8_005a02c8__recomp},
    {"sub_5A0320", 0x5A0320, &recomp_gen::fn_sub_5A0320_005a0320, &recomp_gen::fn_sub_5A0320_005a0320__recomp},
    {"sub_5A0370", 0x5A0370, &recomp_gen::fn_sub_5A0370_005a0370, &recomp_gen::fn_sub_5A0370_005a0370__recomp},
    {"sub_5A0388", 0x5A0388, &recomp_gen::fn_sub_5A0388_005a0388, &recomp_gen::fn_sub_5A0388_005a0388__recomp},
    {"sub_5A1108", 0x5A1108, &recomp_gen::fn_sub_5A1108_005a1108, &recomp_gen::fn_sub_5A1108_005a1108__recomp},
    {"sub_5A1340", 0x5A1340, &recomp_gen::fn_sub_5A1340_005a1340, &recomp_gen::fn_sub_5A1340_005a1340__recomp},
    {"sub_77F598", 0x77F598, &recomp_gen::fn_sub_77F598_0077f598, &recomp_gen::fn_sub_77F598_0077f598__recomp},
    {"sub_77F5F8", 0x77F5F8, &recomp_gen::fn_sub_77F5F8_0077f5f8, &recomp_gen::fn_sub_77F5F8_0077f5f8__recomp},
    {"sub_77F65C", 0x77F65C, &recomp_gen::fn_sub_77F65C_0077f65c, &recomp_gen::fn_sub_77F65C_0077f65c__recomp},
    {"sub_77F67C", 0x77F67C, &recomp_gen::fn_sub_77F67C_0077f67c, &recomp_gen::fn_sub_77F67C_0077f67c__recomp},
    {"sub_77F6B4", 0x77F6B4, &recomp_gen::fn_sub_77F6B4_0077f6b4, &recomp_gen::fn_sub_77F6B4_0077f6b4__recomp},
    {"sub_77F704", 0x77F704, &recomp_gen::fn_sub_77F704_0077f704, &recomp_gen::fn_sub_77F704_0077f704__recomp},
    {"sub_77FF10", 0x77FF10, &recomp_gen::fn_sub_77FF10_0077ff10, &recomp_gen::fn_sub_77FF10_0077ff10__recomp},
    {"sub_7803D0", 0x7803D0, &recomp_gen::fn_sub_7803D0_007803d0, &recomp_gen::fn_sub_7803D0_007803d0__recomp},
    {"sub_7803EC", 0x7803EC, &recomp_gen::fn_sub_7803EC_007803ec, &recomp_gen::fn_sub_7803EC_007803ec__recomp},
};

// ---- the world --------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;      // free RAM for random worlds and built records
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;
constexpr u32 kOut = 0x01820000u;        // out-parameter area (16 KiB, zeroed per pair by the caller)
constexpr u32 kPlayers = 0x7B2FBCu;      // MWSFD's 8 players (MWSFD work 0x7B2F50 + 108), 684 bytes each
constexpr u32 kPlySize = 684;
constexpr u32 kMwsfdWork = 0x7B2F50u;
constexpr const char* kMovieSnap = "libs5_movie_860";  // the dorm route at vblank 860: the boot movie playing

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs5: no case for an address");
}
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u64 r64(Machine& m, u32 va) { u64 v; std::memcpy(&v, m.at(va), 8); return v; }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
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

// ---- the stand-ins: every callee this test binary does not emit -------------------------------------------------
// Recorders without scratch clobbering (both bodies of a pair are served alike; the runner compares the whole
// register file at each callee's entry check point, i.e. the call's arguments), returning `g_v0`. The SFD stream
// accessors and the SFD status getter are served with their real effect on the guest (read / write the handle), so
// the bodies run their real paths on a live handle.
const u32 kDrivers[] = {
    0x53EA90u, 0x541008u, 0x541CE8u, 0x545FC8u, 0x546058u, 0x5460E0u, 0x546270u, 0x546368u, 0x546498u, 0x5465A0u,
    0x546718u, 0x546FA0u, 0x548FC8u, 0x54A680u, 0x55D668u, 0x55D790u, 0x55D7C0u, 0x55DA48u, 0x564DD0u, 0x564FE8u,
    0x5651B0u, 0x565550u, 0x5655E8u, 0x565690u, 0x56DE28u, 0x56F4B8u, 0x575410u, 0x575880u, 0x57C730u, 0x57D518u,
    0x57DB58u, 0x57FA98u, 0x57FC60u, 0x580A28u, 0x580ED8u, 0x580F10u, 0x580FB8u, 0x580FE8u, 0x581070u, 0x5835F0u,
    0x5837A0u, 0x584B18u, 0x584C38u, 0x584D30u, 0x585590u, 0x587618u, 0x5876F0u, 0x587F00u, 0x588F48u, 0x589018u,
    0x5890F0u, 0x5895F0u, 0x589BE0u, 0x589D80u, 0x589F38u, 0x589F70u, 0x58A108u, 0x58C100u, 0x58C118u, 0x58C228u,
    0x5957D8u, 0x595988u, 0x595BA0u, 0x595BC0u, 0x595BE8u, 0x595C60u, 0x5972B0u, 0x597368u, 0x597438u, 0x597968u,
    0x599368u, 0x599D70u, 0x59BCF0u, 0x59BE90u, 0x59BEF0u, 0x59C8E0u, 0x59CAC8u, 0x59CDE0u, 0x59FD10u, 0x5A1868u,
    0x5A19C0u, 0x5A1A30u, 0x59E7A8u, 0x59E808u, 0x59E8F0u, 0x5A1158u, 0x5A1B80u, 0x599240u, 0x548048u, 0x5484E0u,
    0x548678u, 0x548768u, 0x548AE8u, 0x548EB8u, 0x548F40u, 0x5497F8u, 0x549DE8u, 0x549FF8u, 0x547BC0u, 0x562388u,
    0x563C28u, 0x57F328u};
constexpr u32 kSfdStat = 0x5990C0u, kStmCb = 0x589CB0u, kStmInEnd = 0x589CD0u, kStmOutEnd = 0x589D10u;
constexpr u32 kErr = 0x585590u, kLastErr = 0x57FC60u;
u64 g_v0 = 0;
bool in_ram(u64 a) { return a < 0x01FFFF00u; }
void install_drivers(StandIns& s) {
    s.clobber_scratch = false;
    for (u32 va : kDrivers) s.install_recorder(va, "driver", g_v0, 3);
    s.install(kSfdStat, "SFD_GetHnStat", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.v0 = in_ram(c.args[0] + 72) && c.args[0] != 0 ? sx(ctx.memory->read<u32>(static_cast<u32>(c.args[0]) + 72)) : g_v0;
    }, 4);
    s.install(kStmInEnd, "stream_in_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = c.args[0] + 116 * (c.args[1] & 0xFF) + 4888;
        c.v0 = in_ram(a) ? sx(ctx.memory->read<u32>(static_cast<u32>(a))) : 0;
    }, 3);
    s.install(kStmOutEnd, "stream_out_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = c.args[0] + 116 * (c.args[1] & 0xFF) + 4892;
        c.v0 = in_ram(a) ? sx(ctx.memory->read<u32>(static_cast<u32>(a))) : 0;
    }, 3);
    s.install(kStmCb, "stream_set_in_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = c.args[0] + 116 * (c.args[1] & 0xFF) + 4888;
        if (in_ram(a)) ctx.memory->write<u32>(static_cast<u32>(a), static_cast<u32>(c.args[2]));
        c.v0 = 116 * (c.args[1] & 0xFF);
    }, 3);
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
// One pair from the machine's current state (the recompiled run's memory stays), with the drivers stood in; `log`
// receives the hand body's call log.
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
// The same comparison on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore()
// copies back only the pages a pair wrote (instead of a 32 MiB copy per pair).
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
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto &x = h.bus[i], &y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs");
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    same_log(sh, sr, c.name);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const hgp::Run r = pr(m, addr, a, std::move(t));
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

// What $a0 is for each function (the records of libs5.h): the snapshot sweep's argument recipe.
enum class Arg { None, Ply, Slave, Sfd, Pool };
Arg arg_of(u32 a) {
    switch (a) {
    case 0x5800F0u: case 0x580130u: case 0x580270u: case 0x580368u: case 0x580378u: case 0x580628u: case 0x580750u:
    case 0x580900u: case 0x580958u: case 0x5809B0u: case 0x5811D0u: case 0x581690u: case 0x5816F0u: case 0x581798u:
    case 0x581840u: case 0x582828u: case 0x583028u: case 0x5833D8u: case 0x583410u: case 0x583470u: case 0x5834A0u:
    case 0x583500u: case 0x583520u: case 0x5835A8u: case 0x5847D0u: case 0x585050u: case 0x585698u: case 0x585738u:
    case 0x5857B8u: case 0x585960u: case 0x585A20u: case 0x585AC8u: case 0x585B40u: case 0x585F38u: case 0x586130u:
    case 0x586138u: case 0x586140u: case 0x586248u: case 0x5861B8u:
        return Arg::Ply;
    case 0x584C80u: case 0x584CD8u: case 0x584E08u: case 0x585100u: case 0x5851D0u:
        return Arg::Slave;
    case 0x59FCC0u: case 0x5A0370u: case 0x5A0388u: case 0x582810u:
        return Arg::Pool;
    default:
        break;
    }
    if ((a >= 0x5868C0u && a < 0x58C300u) || (a >= 0x599100u && a < 0x59CFA0u)) return Arg::Sfd;
    return Arg::None;
}
// Functions the sweep leaves to their own sections (they rebuild a module's global state from scratch).
bool sweep_skips(u32 a) {
    switch (a) {
    case 0x580C80u: case 0x582798u: case 0x585210u: case 0x585410u: case 0x586858u: case 0x59F970u: case 0x59F9F0u:
    case 0x5A0268u: case 0x5A1108u:
        return true;
    default:
        return false;
    }
}

}  // namespace

TEST_CASE("game(libs5): every body equals its recompiled body on random worlds") {
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

// The boot movie's snapshot (dorm route, vblank 860) holds a live MWSFD player (#0, playing) with its SFD handle,
// audio transfer and SFX handle; the dorm snapshot an initialised MWSFD with no player. Every function runs on them
// with the record its role takes -- the live player / slave / SFD handle, a free player, null -- second arguments
// from the values its branches test, and the stood-in callees returning 0, 1, 3 or -1; each pair starts from the
// snapshot.
TEST_CASE("game(libs5): every body on the live movie player, its SFD handle and the dorm MWSFD") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int runs = 0, stops = 0;
    for (const char* dir : {kMovieSnap, "dorm_replay_4900"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        const u32 live = kPlayers;
        const u32 sfd = r32(*m, live + 60);
        if (std::string(dir) == kMovieSnap) {
            REQUIRE(r32(*m, live) == 1u);   // in use
            REQUIRE(r32(*m, live + 4) == 2u);  // playing
            REQUIRE(sfd != 0u);
        }
        const u32 sfx = r32(*m, live + 168);
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            if (sweep_skips(c.addr)) continue;
            std::vector<u64> a0s;
            switch (arg_of(c.addr)) {
            case Arg::Ply: a0s = {live, live + kPlySize, 0}; break;
            case Arg::Slave: a0s = {live + 640, live + kPlySize + 640}; break;
            case Arg::Sfd: a0s = {sfd ? sfd : kWorld}; break;
            case Arg::Pool: a0s = {sfx, 0}; break;
            case Arg::None: a0s = {0, 1, kOut}; break;
            }
            for (u64 a0 : a0s)
                for (u64 a1 : {0ull, 1ull, 3ull, 6ull, 8ull})
                    for (u64 v : {0ull, 1ull, 3ull, ~0ull}) {
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
    MESSAGE(runs << " pairs from the snapshots, " << stops << " stopped identically");
}

// mwPlyGetStat: a bad handle reports and gives 0 with last error -12; a good one gives its status, and while playing
// follows SFD's status: 2 for SFD 4 or 6, 4 for a negative one, 1 otherwise.
TEST_CASE("game(libs5): mwPlyGetStat, the handle check and the player accessors") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot(kMovieSnap);
    if (snap.empty()) return;
    const u32 live = kPlayers;
    for (s32 code = -3; code <= 8; ++code) {
        restore(*m, snap);
        w32(*m, r32(*m, live + 60) + 72, static_cast<u32>(code));
        const s32 v = sv(prv(*m, 0x581840u, {live, 0, 0, 0}));
        const s32 want = code < 0 ? 4 : (code == 4 || code == 6) ? 2 : 1;
        CHECK(v == want);
    }
    for (u32 st : {0u, 1u, 3u, 4u}) {
        restore(*m, snap);
        w32(*m, live + 4, st);
        CHECK(sv(prv(*m, 0x581840u, {live, 0, 0, 0})) == static_cast<s32>(st));
    }
    restore(*m, snap);
    StandIns log;
    const hgp::Run bad = pr(*m, 0x581840u, {live + kPlySize, 0, 0, 0}, {}, &log);
    CHECK_FALSE(bad.stopped);
    CHECK(v0of(bad) == 0u);
    CHECK(log.calls_to(kLastErr) == 1u);
    CHECK(log.calls_to(kErr) == 1u);
    // the handle check and the SFD / SFX handle getters
    restore(*m, snap);
    CHECK(prv(*m, 0x581798u, {live, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x581798u, {live + kPlySize, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x581798u, {0, 0, 0, 0}) == 0u);
    CHECK(static_cast<u32>(prv(*m, 0x5811D0u, {live, 0, 0, 0})) == r32(*m, live + 60));
    CHECK(prv(*m, 0x5811D0u, {live + kPlySize, 0, 0, 0}) == 0u);
    CHECK(static_cast<u32>(prv(*m, 0x582828u, {live, 0, 0, 0})) == r32(*m, live + 168));
    // the 'in server' words and the frame counters
    prv(*m, 0x586130u, {live, 7, 0, 0});
    CHECK(r32(*m, live + 96) == 7u);
    CHECK(prv(*m, 0x586138u, {live, 0, 0, 0}) == 7u);
    prv(*m, 0x586140u, {live, 5, 0, 0});
    CHECK(r32(*m, live + 100) == 5u);
    w32(*m, live + 124, 11); w32(*m, live + 128, 12);
    prv(*m, 0x580368u, {live, 0, 0, 0});
    CHECK(r32(*m, live + 124) == 0u);
    CHECK(r32(*m, live + 128) == 0u);
    prv(*m, 0x583500u, {live, 0, 0, 0});
    CHECK(r32(*m, live + 400) == 0xFFFFFFFFu);
    CHECK(r32(*m, live + 404) == 0u);
    CHECK(r32(*m, live + 412) == 0u);
    // the server-busy word: player +92 and MWSFD work +36
    prv(*m, 0x5861B8u, {live, 1, 0, 0});
    CHECK(r32(*m, live + 92) == 1u);
    CHECK(r32(*m, kMwsfdWork + 36) == 1u);
    CHECK(prv(*m, 0x586200u, {0, 0, 0, 0}) == 1u);
    prv(*m, 0x5861B8u, {0, 0, 0, 0});
    CHECK(r32(*m, kMwsfdWork + 36) == 0u);
    MESSAGE(summary());
}

// mwPlySetFname: a name that fits is copied with its terminator; a longer one is reported ('filename is longer.')
// and copied to the capacity, unterminated.
TEST_CASE("game(libs5): the file name copy of a player") {
    auto m = machine();
    if (!m) return;
    const u32 ply = kWorld, buf = kWorld + 0x1000, name = kWorld + 0x2000;
    for (const std::string s : {std::string("MOVIE01.SFD"), std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.SFD"), std::string("")}) {
        std::memset(m->at(kWorld), 0, 0x3000);
        std::memset(m->at(buf), 0x5A, 64);
        w32(*m, ply + 420, buf);
        w32(*m, ply + 424, 16);
        std::memcpy(m->at(name), s.c_str(), s.size() + 1);
        StandIns log;
        const hgp::Run r = pr(*m, 0x5809B0u, {ply, name, 0, 0}, {}, &log);
        CHECK_FALSE(r.stopped);
        if (s.size() <= 16) {
            CHECK(std::string(reinterpret_cast<const char*>(m->at(buf))) == s);
            CHECK(log.calls_to(kErr) == 0u);
        } else {
            CHECK(std::memcmp(m->at(buf), s.data(), 16) == 0);
            CHECK(*m->at(buf + 16) == 0x5A);  // no terminator
            CHECK(log.calls_to(kErr) == 1u);
        }
    }
}

// SFX's two handle pools: init clears them (8 handles each), the free-handle searches take the first free slot,
// sfx_InitHn lays the work out (rounded up to 32, then +1024 / +2048 / +3072), the work check is >= 6175 bytes.
TEST_CASE("game(libs5): the SFX handle pools and the work layout") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(0x7B4920u), 0xEE, 1224);
    prv(*m, 0x59F9F0u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7B4920u) == 0u);
    CHECK(r32(*m, 0x7B4924u) == 8u);
    CHECK(r32(*m, 0x7B4934u) == 1u);
    CHECK(static_cast<u32>(prv(*m, 0x59FBC0u, {0, 0, 0, 0})) == 0x7B4938u);
    w32(*m, 0x7B4938u, 1);
    CHECK(static_cast<u32>(prv(*m, 0x59FBC0u, {0, 0, 0, 0})) == 0x7B4938u + 148u);
    for (u32 i = 0; i < 8; ++i) w32(*m, 0x7B4938u + 148 * i, 1);
    CHECK(prv(*m, 0x59FBC0u, {0, 0, 0, 0}) == 0u);
    for (u32 work : {0x01810000u, 0x01810005u, 0x0181001Fu, 0x01810021u}) {
        std::memset(m->at(kWorld + 0x8000), 0xCC, 148);
        prv(*m, 0x59FC10u, {kWorld + 0x8000, work, 7000, 0});
        const u32 al = (work + 31) & ~31u;
        CHECK(r32(*m, kWorld + 0x8000) == 1u);
        CHECK(r32(*m, kWorld + 0x8000 + 80) == work);
        CHECK(r32(*m, kWorld + 0x8000 + 84) == 7000u);
        CHECK(r32(*m, kWorld + 0x8000 + 56) == al);
        CHECK(r32(*m, kWorld + 0x8000 + 60) == al + 1024);
        CHECK(r32(*m, kWorld + 0x8000 + 64) == al + 2048);
        CHECK(r32(*m, kWorld + 0x8000 + 68) == al + 3072);
        CHECK(r32(*m, kWorld + 0x8000 + 88) == 0xFFFFFFFFu);
    }
    for (u64 n : {0ull, 6174ull, 6175ull, 6176ull, 100000ull})
        CHECK(prv(*m, 0x59FCB0u, {n, 0, 0, 0}) == (n >= 6175 ? 1u : 0u));
    CHECK(prv(*m, 0x5827F0u, {0, 0, 0, 0}) == 6175u);  // MWSFD asks for exactly the minimum
    // the Z pool
    std::memset(m->at(0x7B4DE8u), 0xEE, 620);
    prv(*m, 0x5A0268u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7B4DE8u) == 0u);
    CHECK(r32(*m, 0x7B4DF0u) == 8u);
    const u32 z = static_cast<u32>(prv(*m, 0x5A02C8u, {0, 0, 0, 0}));
    CHECK(z == 0x7B4DF4u);
    CHECK(r32(*m, z) == 1u);
    CHECK(r32(*m, 0x7B4DE8u) == 1u);
    CHECK(static_cast<u32>(prv(*m, 0x5A02C8u, {0, 0, 0, 0})) == 0x7B4DF4u + 76u);
    prv(*m, 0x5A0388u, {z, 0, 0, 0});
    CHECK(r32(*m, z) == 0u);
    CHECK(r32(*m, 0x7B4DE8u) == 1u);
    prv(*m, 0x5A0388u, {0, 0, 0, 0});  // a null handle: nothing changes
    CHECK(r32(*m, 0x7B4DE8u) == 1u);
    MESSAGE(summary());
}

// The SFD statistics record: count, minimum (starts at INT64_MAX), maximum and sum of 64-bit samples.
TEST_CASE("game(libs5): the SFD statistics record against a host model") {
    auto m = machine();
    if (!m) return;
    std::mt19937_64 rng{5};
    for (int round = 0; round < 8; ++round) {
        const u32 rec = kWorld + 0x100 * round;
        prv(*m, 0x59B490u, {rec, 0, 0, 0});
        CHECK(r32(*m, rec + 24) == 0u);
        CHECK(r64(*m, rec + 8) == 0x7FFFFFFFFFFFFFFFull);
        s64 sum = 0, mn = INT64_MAX, mx = 0;
        for (int i = 0; i < 20; ++i) {
            const u64 draw = rng();
            const s64 x = static_cast<s64>(draw % 2000001) - 1000000;
            prv(*m, 0x59B4B0u, {rec, static_cast<u64>(x), 0, 0});
            sum += x;
            mn = std::min(mn, x);
            mx = std::max(mx, x);
        }
        CHECK(static_cast<s64>(r64(*m, rec)) == sum);
        CHECK(static_cast<s64>(r64(*m, rec + 8)) == mn);
        CHECK(static_cast<s64>(r64(*m, rec + 16)) == mx);
        CHECK(r32(*m, rec + 24) == 20u);
    }
}

// SFD's handle accessors on the live handle: the parameter table, the transfer slots' end flags and work heads, the
// time pair, the 'time valid' statuses, the time-base setters; record initialisers on built memory.
TEST_CASE("game(libs5): the SFD handle accessors on the live handle") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot(kMovieSnap);
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 h = r32(*m, kPlayers + 60);
    for (u32 id = 0; id < 80; ++id) CHECK(static_cast<u32>(prv(*m, 0x599408u, {h, id, 0, 0})) == r32(*m, h + 2572 + 4 * id));
    for (u32 s = 0; s < 9; ++s) {
        CHECK(static_cast<u32>(prv(*m, 0x59BC88u, {h, s, 0, 0})) == r32(*m, h + 7984 + 68 * s));
        CHECK(static_cast<u32>(prv(*m, 0x59BCB8u, {h, s, 0, 0})) == r32(*m, h + 7988 + 68 * s));
        w32(*m, kOut, 0xDEADBEEFu);
        prv(*m, 0x599730u, {h, s, kOut, 0});
        const u32 work = r32(*m, h + 7992 + 68 * s);
        CHECK(r32(*m, kOut) == (work ? r32(*m, work) : 0u));
    }
    prv(*m, 0x59A168u, {h, kOut, kOut + 4, 0});
    CHECK(r32(*m, kOut) == r32(*m, h + 3376 + 652));
    CHECK(r32(*m, kOut + 4) == r32(*m, h + 3376 + 656));
    for (s32 st = -7; st <= 7; ++st) {
        restore(*m, snap);
        w32(*m, h + 72, static_cast<u32>(st));
        w32(*m, kOut, 5); w32(*m, kOut + 4, 5);
        const bool valid = st == 4 || st == -4 || st == 6 || st == -6;
        CHECK(prv(*m, 0x59A458u, {h, kOut, kOut + 4, 0}) == (valid ? 1u : 0u));
        CHECK(r32(*m, kOut) == (valid ? 5u : 0xFFFFFFFFu));
        CHECK(r32(*m, kOut + 4) == (valid ? 5u : 1u));
    }
    // the time base setters
    const u32 tb = kWorld;
    std::memset(m->at(tb), 0, 0x200);
    prv(*m, 0x59BE10u, {tb, 3, 0, 0});
    CHECK(r32(*m, tb) == 3u);
    w64(*m, kOut, 1234); w64(*m, kOut + 8, 1000000);
    for (u32 f : {0x59BE18u, 0x59BE30u, 0x59BE48u, 0x59BE60u}) prv(*m, f, {tb, kOut, 0, 0});
    for (u32 off : {312u, 328u, 344u, 360u}) {
        CHECK(r64(*m, tb + off) == 1234u);
        CHECK(r64(*m, tb + off + 8) == 1000000u);
    }
    prv(*m, 0x59BE78u, {tb, 0, 0, 0});
    CHECK(r32(*m, tb + 16) == 0u);
    prv(*m, 0x59BE78u, {tb, 77, 0, 0});
    CHECK(r32(*m, tb + 16) == 77u);
    prv(*m, 0x59BE78u, {tb, sx(0xFFFFFFFFu), 0, 0});
    CHECK(r32(*m, tb + 16) == 77u);
    // record initialisers
    std::memset(m->at(tb), 0xAB, 64);
    CHECK(prv(*m, 0x599A30u, {tb, 9, 0, 0}) == 1u);
    for (u32 o = 0; o < 36; o += 4) CHECK(r32(*m, tb + o) == 0u);
    CHECK(r32(*m, tb + 36) == 9u);
    CHECK(r32(*m, tb + 40) == 1u);
    std::memset(m->at(tb), 0xAB, 16);
    prv(*m, 0x5997F8u, {tb, 4, 0, 0});
    CHECK(r32(*m, tb) == 0u);
    CHECK(r32(*m, tb + 4) == 0u);
    CHECK(r32(*m, tb + 8) == 4u);
    // the vsync over every handle counts one call
    restore(*m, snap);
    const u32 before = r32(*m, 0x7B4720u);
    pr(*m, 0x599B80u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7B4720u) == before + 1);
    MESSAGE(summary());
}

// The ADXT configuration record the audio transfer keeps (0x9A6ED0): words 0, 1, 3, 4, 5 as given, the two buffer
// sizes (words 2 and 6) rounded up to 32.
TEST_CASE("game(libs5): the audio transfer's ADXT configuration and the module inits") {
    auto m = machine();
    if (!m) return;
    for (u32 n : {0u, 1u, 31u, 32u, 33u, 4095u}) {
        for (u32 i = 0; i < 7; ++i) w32(*m, kWorld + 4 * i, 100 * (i + 1) + n);
        prv(*m, 0x586800u, {kWorld, 0, 0, 0});
        CHECK(r32(*m, 0x9A6ED0u) == 100u + n);
        CHECK(r32(*m, 0x9A6ED4u) == 200u + n);
        CHECK(r32(*m, 0x9A6ED8u) == ((300u + n + 31) & ~31u));
        CHECK(r32(*m, 0x9A6EDCu) == 400u + n);
        CHECK(r32(*m, 0x9A6EE0u) == 500u + n);
        CHECK(r32(*m, 0x9A6EE4u) == 600u + n);
        CHECK(r32(*m, 0x9A6EE8u) == ((700u + n + 31) & ~31u));
    }
    // the inits run on a fresh machine (their callees stood in)
    CHECK(prv(*m, 0x580C80u, {0, 0, 0, 0}) == 1u);
    CHECK(r32(*m, 0x7B4528u) == 1u);
    CHECK(prv(*m, 0x580DF0u, {0, 0, 0, 0}) == 1u);
    prv(*m, 0x585210u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x9A6EC4u) == 0u);
    CHECK(static_cast<u32>(prv(*m, 0x585410u, {0, 0, 0, 0})) == 0x99A0C8u);
    CHECK(r32(*m, 0x99A0C8u) == 0x585480u);  // the swap-out hook
    CHECK(static_cast<u32>(prv(*m, 0x582798u, {0, 0, 0, 0})) == 0x7B4928u);
    CHECK(r32(*m, 0x7B4928u) == 0x5827C0u);
    prv(*m, 0x586858u, {0, 0, 0, 0});
    prv(*m, 0x5A1108u, {0, 0, 0, 0});
    const u32 sud = r32(*m, 0x7B5058u);
    prv(*m, 0x5A1108u, {0, 0, 0, 0});  // counted: a second init does nothing
    CHECK(r32(*m, 0x7B5058u) == sud);
    MESSAGE(summary());
}

// The kernel payloads' do-nothing functions (they run in kernel mode at 0x80074000.. in retail, never here) and the
// small transfer modules' constant methods.
TEST_CASE("game(libs5): constant returns") {
    auto m = machine();
    if (!m) return;
    const u64 arg0 = 0x1234, arg1 = 0x5678;
    CHECK(prv(*m, 0x77F598u, {arg0, arg1, 0, 0}) == 0u);
    CHECK(prv(*m, 0x77F5F8u, {arg0, arg1, 0, 0}) == ~0ull);
    CHECK(prv(*m, 0x77F65Cu, {arg0, arg1, 0, 0}) == arg0);
    CHECK(prv(*m, 0x77F67Cu, {arg0, arg1, 0, 0}) == ~0ull);
    CHECK(prv(*m, 0x77F6B4u, {arg0, arg1, 0, 0}) == arg0);
    CHECK(prv(*m, 0x77F704u, {arg0, arg1, 0, 0}) == arg0);
    CHECK(prv(*m, 0x77FF10u, {arg0, arg1, 0, 0}) == 0u);
    CHECK(prv(*m, 0x7803D0u, {arg0, arg1, 0, 0}) == 0u);
    CHECK(prv(*m, 0x7803ECu, {arg0, arg1, 0, 0}) == arg1);
    for (u32 f : {0x5883B8u, 0x588560u, 0x58C130u, 0x58C168u, 0x58C170u, 0x59C9F0u, 0x59CB58u, 0x59CC48u, 0x59CCF8u,
                  0x59CEB0u, 0x59CEB8u, 0x59CEC0u, 0x5862F0u})
        CHECK(prv(*m, f, {arg0, arg1, 0, 0}) == 0u);
    CHECK(prv(*m, 0x59CB50u, {arg0, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x59CEA8u, {arg0, 0, 0, 0}) == 1u);
}

#else

TEST_CASE("game(libs5): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
