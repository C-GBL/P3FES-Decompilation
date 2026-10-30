// Pair tests for slice libs9 (game/src/cri/libs9.cpp: ADXM's thread layer, the ADX encoder, ADXSTM / ADXT accessors,
// the MPEG-audio Layer II decoder). Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the
// whole register file and cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack
// too), the scratchpad, the BIOS window and the bus log; both bodies' stand-in call logs must be equal. Most callees
// belong to slices running now (libs7 / libs8 / libs10 / libs11): they are neither stood in nor emitted here, so a pair
// ends at such a call, identically. Stand-ins only for callees other tests of main already stand in (the ADX error
// reporter, the ADXSTM / PS2RNA switches, the ADXT time getter). On top of the random worlds:
//   * every function on the live ADXT handles and MPEG-audio decoders of three snapshots (battle, boot movie, dorm);
//   * the ADXT accessors' rules (null-handle reports, getters, the refill threshold, error-field reset, time offset,
//     the play time in hundredths); the ADX encoder's create defaults, setters, dispatch, server and finish; ADXT's
//     time mode, the streamer's request size and small getters.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/cri2.h"
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
void fn___errno_0_00540d70(EEContext&);  // generated body
void fn___errno_0_00540d70__recomp(EEContext&);  // recompiled
void fn_sub_541040_00541040(EEContext&);  // generated body
void fn_sub_541040_00541040__recomp(EEContext&);  // recompiled
void fn_sub_541058_00541058(EEContext&);  // generated body
void fn_sub_541058_00541058__recomp(EEContext&);  // recompiled
void fn_sub_5410A0_005410a0(EEContext&);  // generated body
void fn_sub_5410A0_005410a0__recomp(EEContext&);  // recompiled
void fn_sub_541100_00541100(EEContext&);  // generated body
void fn_sub_541100_00541100__recomp(EEContext&);  // recompiled
void fn_sub_541118_00541118(EEContext&);  // generated body
void fn_sub_541118_00541118__recomp(EEContext&);  // recompiled
void fn_sub_541180_00541180(EEContext&);  // generated body
void fn_sub_541180_00541180__recomp(EEContext&);  // recompiled
void fn_sub_541198_00541198(EEContext&);  // generated body
void fn_sub_541198_00541198__recomp(EEContext&);  // recompiled
void fn_ADXM_SetupThrdEx_005411b0(EEContext&);  // generated body
void fn_ADXM_SetupThrdEx_005411b0__recomp(EEContext&);  // recompiled
void fn_sub_5413A0_005413a0(EEContext&);  // generated body
void fn_sub_5413A0_005413a0__recomp(EEContext&);  // recompiled
void fn_sub_541450_00541450(EEContext&);  // generated body
void fn_sub_541450_00541450__recomp(EEContext&);  // recompiled
void fn_sub_541478_00541478(EEContext&);  // generated body
void fn_sub_541478_00541478__recomp(EEContext&);  // recompiled
void fn_sub_5414A0_005414a0(EEContext&);  // generated body
void fn_sub_5414A0_005414a0__recomp(EEContext&);  // recompiled
void fn_sub_5414B8_005414b8(EEContext&);  // generated body
void fn_sub_5414B8_005414b8__recomp(EEContext&);  // recompiled
void fn_sub_541540_00541540(EEContext&);  // generated body
void fn_sub_541540_00541540__recomp(EEContext&);  // recompiled
void fn_sub_5415C0_005415c0(EEContext&);  // generated body
void fn_sub_5415C0_005415c0__recomp(EEContext&);  // recompiled
void fn___errno_1_00541628(EEContext&);  // generated body
void fn___errno_1_00541628__recomp(EEContext&);  // recompiled
void fn_sub_541638_00541638(EEContext&);  // generated body
void fn_sub_541638_00541638__recomp(EEContext&);  // recompiled
void fn_sub_541668_00541668(EEContext&);  // generated body
void fn_sub_541668_00541668__recomp(EEContext&);  // recompiled
void fn_sub_5417F8_005417f8(EEContext&);  // generated body
void fn_sub_5417F8_005417f8__recomp(EEContext&);  // recompiled
void fn_sub_541838_00541838(EEContext&);  // generated body
void fn_sub_541838_00541838__recomp(EEContext&);  // recompiled
void fn_sub_541878_00541878(EEContext&);  // generated body
void fn_sub_541878_00541878__recomp(EEContext&);  // recompiled
void fn_sub_5418B0_005418b0(EEContext&);  // generated body
void fn_sub_5418B0_005418b0__recomp(EEContext&);  // recompiled
void fn_sub_5418E8_005418e8(EEContext&);  // generated body
void fn_sub_5418E8_005418e8__recomp(EEContext&);  // recompiled
void fn_sub_541900_00541900(EEContext&);  // generated body
void fn_sub_541900_00541900__recomp(EEContext&);  // recompiled
void fn_sub_541918_00541918(EEContext&);  // generated body
void fn_sub_541918_00541918__recomp(EEContext&);  // recompiled
void fn_sub_541930_00541930(EEContext&);  // generated body
void fn_sub_541930_00541930__recomp(EEContext&);  // recompiled
void fn_sub_541948_00541948(EEContext&);  // generated body
void fn_sub_541948_00541948__recomp(EEContext&);  // recompiled
void fn_sub_541960_00541960(EEContext&);  // generated body
void fn_sub_541960_00541960__recomp(EEContext&);  // recompiled
void fn_sub_544900_00544900(EEContext&);  // generated body
void fn_sub_544900_00544900__recomp(EEContext&);  // recompiled
void fn_sub_544A00_00544a00(EEContext&);  // generated body
void fn_sub_544A00_00544a00__recomp(EEContext&);  // recompiled
void fn_sub_545158_00545158(EEContext&);  // generated body
void fn_sub_545158_00545158__recomp(EEContext&);  // recompiled
void fn_sub_5451B0_005451b0(EEContext&);  // generated body
void fn_sub_5451B0_005451b0__recomp(EEContext&);  // recompiled
void fn_sub_545208_00545208(EEContext&);  // generated body
void fn_sub_545208_00545208__recomp(EEContext&);  // recompiled
void fn_sub_5453D8_005453d8(EEContext&);  // generated body
void fn_sub_5453D8_005453d8__recomp(EEContext&);  // recompiled
void fn_sub_545448_00545448(EEContext&);  // generated body
void fn_sub_545448_00545448__recomp(EEContext&);  // recompiled
void fn_sub_545570_00545570(EEContext&);  // generated body
void fn_sub_545570_00545570__recomp(EEContext&);  // recompiled
void fn_sub_545580_00545580(EEContext&);  // generated body
void fn_sub_545580_00545580__recomp(EEContext&);  // recompiled
void fn_sub_545590_00545590(EEContext&);  // generated body
void fn_sub_545590_00545590__recomp(EEContext&);  // recompiled
void fn_sub_545610_00545610(EEContext&);  // generated body
void fn_sub_545610_00545610__recomp(EEContext&);  // recompiled
void fn_sub_545838_00545838(EEContext&);  // generated body
void fn_sub_545838_00545838__recomp(EEContext&);  // recompiled
void fn_sub_545948_00545948(EEContext&);  // generated body
void fn_sub_545948_00545948__recomp(EEContext&);  // recompiled
void fn_sub_545AB8_00545ab8(EEContext&);  // generated body
void fn_sub_545AB8_00545ab8__recomp(EEContext&);  // recompiled
void fn_sub_545B50_00545b50(EEContext&);  // generated body
void fn_sub_545B50_00545b50__recomp(EEContext&);  // recompiled
void fn_sub_545B90_00545b90(EEContext&);  // generated body
void fn_sub_545B90_00545b90__recomp(EEContext&);  // recompiled
void fn_sub_545CC8_00545cc8(EEContext&);  // generated body
void fn_sub_545CC8_00545cc8__recomp(EEContext&);  // recompiled
void fn_sub_546770_00546770(EEContext&);  // generated body
void fn_sub_546770_00546770__recomp(EEContext&);  // recompiled
void fn_sub_546EC0_00546ec0(EEContext&);  // generated body
void fn_sub_546EC0_00546ec0__recomp(EEContext&);  // recompiled
void fn_sub_546EF0_00546ef0(EEContext&);  // generated body
void fn_sub_546EF0_00546ef0__recomp(EEContext&);  // recompiled
void fn_sub_546F48_00546f48(EEContext&);  // generated body
void fn_sub_546F48_00546f48__recomp(EEContext&);  // recompiled
void fn_sub_546F98_00546f98(EEContext&);  // generated body
void fn_sub_546F98_00546f98__recomp(EEContext&);  // recompiled
void fn_sub_5470E8_005470e8(EEContext&);  // generated body
void fn_sub_5470E8_005470e8__recomp(EEContext&);  // recompiled
void fn_sub_547120_00547120(EEContext&);  // generated body
void fn_sub_547120_00547120__recomp(EEContext&);  // recompiled
void fn_sub_5471B8_005471b8(EEContext&);  // generated body
void fn_sub_5471B8_005471b8__recomp(EEContext&);  // recompiled
void fn_sub_547248_00547248(EEContext&);  // generated body
void fn_sub_547248_00547248__recomp(EEContext&);  // recompiled
void fn_sub_5472E8_005472e8(EEContext&);  // generated body
void fn_sub_5472E8_005472e8__recomp(EEContext&);  // recompiled
void fn_sub_547418_00547418(EEContext&);  // generated body
void fn_sub_547418_00547418__recomp(EEContext&);  // recompiled
void fn_sub_547468_00547468(EEContext&);  // generated body
void fn_sub_547468_00547468__recomp(EEContext&);  // recompiled
void fn_sub_5474B8_005474b8(EEContext&);  // generated body
void fn_sub_5474B8_005474b8__recomp(EEContext&);  // recompiled
void fn___errno_2_00547500(EEContext&);  // generated body
void fn___errno_2_00547500__recomp(EEContext&);  // recompiled
void fn_sub_547548_00547548(EEContext&);  // generated body
void fn_sub_547548_00547548__recomp(EEContext&);  // recompiled
void fn_sub_547590_00547590(EEContext&);  // generated body
void fn_sub_547590_00547590__recomp(EEContext&);  // recompiled
void fn_sub_547598_00547598(EEContext&);  // generated body
void fn_sub_547598_00547598__recomp(EEContext&);  // recompiled
void fn_sub_5475C8_005475c8(EEContext&);  // generated body
void fn_sub_5475C8_005475c8__recomp(EEContext&);  // recompiled
void fn_sub_547650_00547650(EEContext&);  // generated body
void fn_sub_547650_00547650__recomp(EEContext&);  // recompiled
void fn_log10l_3_00547a58(EEContext&);  // generated body
void fn_log10l_3_00547a58__recomp(EEContext&);  // recompiled
void fn_sub_547AA8_00547aa8(EEContext&);  // generated body
void fn_sub_547AA8_00547aa8__recomp(EEContext&);  // recompiled
void fn_sub_547F78_00547f78(EEContext&);  // generated body
void fn_sub_547F78_00547f78__recomp(EEContext&);  // recompiled
void fn_sub_548250_00548250(EEContext&);  // generated body
void fn_sub_548250_00548250__recomp(EEContext&);  // recompiled
void fn_sub_548300_00548300(EEContext&);  // generated body
void fn_sub_548300_00548300__recomp(EEContext&);  // recompiled
void fn_sub_5485A8_005485a8(EEContext&);  // generated body
void fn_sub_5485A8_005485a8__recomp(EEContext&);  // recompiled
void fn_sub_548800_00548800(EEContext&);  // generated body
void fn_sub_548800_00548800__recomp(EEContext&);  // recompiled
void fn_sub_548888_00548888(EEContext&);  // generated body
void fn_sub_548888_00548888__recomp(EEContext&);  // recompiled
void fn_sub_548AD0_00548ad0(EEContext&);  // generated body
void fn_sub_548AD0_00548ad0__recomp(EEContext&);  // recompiled
void fn_sub_548E68_00548e68(EEContext&);  // generated body
void fn_sub_548E68_00548e68__recomp(EEContext&);  // recompiled
void fn_sub_549088_00549088(EEContext&);  // generated body
void fn_sub_549088_00549088__recomp(EEContext&);  // recompiled
void fn_sub_549110_00549110(EEContext&);  // generated body
void fn_sub_549110_00549110__recomp(EEContext&);  // recompiled
void fn_sub_5492C8_005492c8(EEContext&);  // generated body
void fn_sub_5492C8_005492c8__recomp(EEContext&);  // recompiled
void fn_sub_549568_00549568(EEContext&);  // generated body
void fn_sub_549568_00549568__recomp(EEContext&);  // recompiled
void fn_sub_5495D0_005495d0(EEContext&);  // generated body
void fn_sub_5495D0_005495d0__recomp(EEContext&);  // recompiled
void fn_sub_549638_00549638(EEContext&);  // generated body
void fn_sub_549638_00549638__recomp(EEContext&);  // recompiled
void fn_sub_549690_00549690(EEContext&);  // generated body
void fn_sub_549690_00549690__recomp(EEContext&);  // recompiled
void fn_sub_5496E0_005496e0(EEContext&);  // generated body
void fn_sub_5496E0_005496e0__recomp(EEContext&);  // recompiled
void fn_sub_5497A8_005497a8(EEContext&);  // generated body
void fn_sub_5497A8_005497a8__recomp(EEContext&);  // recompiled
void fn_sub_5498D0_005498d0(EEContext&);  // generated body
void fn_sub_5498D0_005498d0__recomp(EEContext&);  // recompiled
void fn_sub_5499B0_005499b0(EEContext&);  // generated body
void fn_sub_5499B0_005499b0__recomp(EEContext&);  // recompiled
void fn_sub_549A70_00549a70(EEContext&);  // generated body
void fn_sub_549A70_00549a70__recomp(EEContext&);  // recompiled
void fn_sub_549B08_00549b08(EEContext&);  // generated body
void fn_sub_549B08_00549b08__recomp(EEContext&);  // recompiled
void fn_sub_549C58_00549c58(EEContext&);  // generated body
void fn_sub_549C58_00549c58__recomp(EEContext&);  // recompiled
void fn_sub_549D78_00549d78(EEContext&);  // generated body
void fn_sub_549D78_00549d78__recomp(EEContext&);  // recompiled
void fn_sub_549E68_00549e68(EEContext&);  // generated body
void fn_sub_549E68_00549e68__recomp(EEContext&);  // recompiled
void fn_sub_549FE0_00549fe0(EEContext&);  // generated body
void fn_sub_549FE0_00549fe0__recomp(EEContext&);  // recompiled
void fn_sub_54A090_0054a090(EEContext&);  // generated body
void fn_sub_54A090_0054a090__recomp(EEContext&);  // recompiled
void fn_sub_54A108_0054a108(EEContext&);  // generated body
void fn_sub_54A108_0054a108__recomp(EEContext&);  // recompiled
void fn_sub_54A2B8_0054a2b8(EEContext&);  // generated body
void fn_sub_54A2B8_0054a2b8__recomp(EEContext&);  // recompiled
void fn_sub_54A328_0054a328(EEContext&);  // generated body
void fn_sub_54A328_0054a328__recomp(EEContext&);  // recompiled
void fn_sub_54A390_0054a390(EEContext&);  // generated body
void fn_sub_54A390_0054a390__recomp(EEContext&);  // recompiled
void fn_sub_54A5C8_0054a5c8(EEContext&);  // generated body
void fn_sub_54A5C8_0054a5c8__recomp(EEContext&);  // recompiled
void fn_sub_54A618_0054a618(EEContext&);  // generated body
void fn_sub_54A618_0054a618__recomp(EEContext&);  // recompiled
void fn_sub_54A678_0054a678(EEContext&);  // generated body
void fn_sub_54A678_0054a678__recomp(EEContext&);  // recompiled
void fn_sub_54A6B0_0054a6b0(EEContext&);  // generated body
void fn_sub_54A6B0_0054a6b0__recomp(EEContext&);  // recompiled
void fn_sub_54A710_0054a710(EEContext&);  // generated body
void fn_sub_54A710_0054a710__recomp(EEContext&);  // recompiled
void fn_sub_54A758_0054a758(EEContext&);  // generated body
void fn_sub_54A758_0054a758__recomp(EEContext&);  // recompiled
void fn_sub_54A878_0054a878(EEContext&);  // generated body
void fn_sub_54A878_0054a878__recomp(EEContext&);  // recompiled
void fn_sub_54A880_0054a880(EEContext&);  // generated body
void fn_sub_54A880_0054a880__recomp(EEContext&);  // recompiled
void fn_sub_54A8C0_0054a8c0(EEContext&);  // generated body
void fn_sub_54A8C0_0054a8c0__recomp(EEContext&);  // recompiled
void fn_sub_54A910_0054a910(EEContext&);  // generated body
void fn_sub_54A910_0054a910__recomp(EEContext&);  // recompiled
void fn_sub_54A9D8_0054a9d8(EEContext&);  // generated body
void fn_sub_54A9D8_0054a9d8__recomp(EEContext&);  // recompiled
void fn_sub_54AA30_0054aa30(EEContext&);  // generated body
void fn_sub_54AA30_0054aa30__recomp(EEContext&);  // recompiled
void fn_sub_54AA80_0054aa80(EEContext&);  // generated body
void fn_sub_54AA80_0054aa80__recomp(EEContext&);  // recompiled
void fn_sub_54AAF0_0054aaf0(EEContext&);  // generated body
void fn_sub_54AAF0_0054aaf0__recomp(EEContext&);  // recompiled
void fn_sub_54AB78_0054ab78(EEContext&);  // generated body
void fn_sub_54AB78_0054ab78__recomp(EEContext&);  // recompiled
void fn_sub_54ABA8_0054aba8(EEContext&);  // generated body
void fn_sub_54ABA8_0054aba8__recomp(EEContext&);  // recompiled
void fn_sub_54AC80_0054ac80(EEContext&);  // generated body
void fn_sub_54AC80_0054ac80__recomp(EEContext&);  // recompiled
void fn_sub_54ACD8_0054acd8(EEContext&);  // generated body
void fn_sub_54ACD8_0054acd8__recomp(EEContext&);  // recompiled
void fn_sub_54AF38_0054af38(EEContext&);  // generated body
void fn_sub_54AF38_0054af38__recomp(EEContext&);  // recompiled
void fn_sub_54AF78_0054af78(EEContext&);  // generated body
void fn_sub_54AF78_0054af78__recomp(EEContext&);  // recompiled
void fn_sub_54AFD8_0054afd8(EEContext&);  // generated body
void fn_sub_54AFD8_0054afd8__recomp(EEContext&);  // recompiled
void fn_sub_54B028_0054b028(EEContext&);  // generated body
void fn_sub_54B028_0054b028__recomp(EEContext&);  // recompiled
void fn_sub_54B070_0054b070(EEContext&);  // generated body
void fn_sub_54B070_0054b070__recomp(EEContext&);  // recompiled
void fn_sub_54B388_0054b388(EEContext&);  // generated body
void fn_sub_54B388_0054b388__recomp(EEContext&);  // recompiled
void fn_sub_54C580_0054c580(EEContext&);  // generated body
void fn_sub_54C580_0054c580__recomp(EEContext&);  // recompiled
void fn_sub_54CB08_0054cb08(EEContext&);  // generated body
void fn_sub_54CB08_0054cb08__recomp(EEContext&);  // recompiled
void fn_sub_54D88C_0054d88c(EEContext&);  // generated body
void fn_sub_54D88C_0054d88c__recomp(EEContext&);  // recompiled
void fn_sub_54DAD8_0054dad8(EEContext&);  // generated body
void fn_sub_54DAD8_0054dad8__recomp(EEContext&);  // recompiled
void fn_sub_54DD08_0054dd08(EEContext&);  // generated body
void fn_sub_54DD08_0054dd08__recomp(EEContext&);  // recompiled
void fn_sub_54E048_0054e048(EEContext&);  // generated body
void fn_sub_54E048_0054e048__recomp(EEContext&);  // recompiled
void fn_sub_54E0D8_0054e0d8(EEContext&);  // generated body
void fn_sub_54E0D8_0054e0d8__recomp(EEContext&);  // recompiled
void fn_sub_54E130_0054e130(EEContext&);  // generated body
void fn_sub_54E130_0054e130__recomp(EEContext&);  // recompiled
void fn_sub_54E180_0054e180(EEContext&);  // generated body
void fn_sub_54E180_0054e180__recomp(EEContext&);  // recompiled
void fn_sub_54E260_0054e260(EEContext&);  // generated body
void fn_sub_54E260_0054e260__recomp(EEContext&);  // recompiled
void fn_sub_54E388_0054e388(EEContext&);  // generated body
void fn_sub_54E388_0054e388__recomp(EEContext&);  // recompiled
void fn_sub_54E3C0_0054e3c0(EEContext&);  // generated body
void fn_sub_54E3C0_0054e3c0__recomp(EEContext&);  // recompiled
void fn_sub_54E648_0054e648(EEContext&);  // generated body
void fn_sub_54E648_0054e648__recomp(EEContext&);  // recompiled
void fn_sub_54E658_0054e658(EEContext&);  // generated body
void fn_sub_54E658_0054e658__recomp(EEContext&);  // recompiled
void fn_sub_54E838_0054e838(EEContext&);  // generated body
void fn_sub_54E838_0054e838__recomp(EEContext&);  // recompiled
void fn_sub_54E9A0_0054e9a0(EEContext&);  // generated body
void fn_sub_54E9A0_0054e9a0__recomp(EEContext&);  // recompiled
void fn_sub_54EAB8_0054eab8(EEContext&);  // generated body
void fn_sub_54EAB8_0054eab8__recomp(EEContext&);  // recompiled
void fn_sub_54EAD8_0054ead8(EEContext&);  // generated body
void fn_sub_54EAD8_0054ead8__recomp(EEContext&);  // recompiled
void fn_sub_54EBC0_0054ebc0(EEContext&);  // generated body
void fn_sub_54EBC0_0054ebc0__recomp(EEContext&);  // recompiled
void fn_sub_54ED48_0054ed48(EEContext&);  // generated body
void fn_sub_54ED48_0054ed48__recomp(EEContext&);  // recompiled
void fn_sub_54F028_0054f028(EEContext&);  // generated body
void fn_sub_54F028_0054f028__recomp(EEContext&);  // recompiled
void fn_sub_54F730_0054f730(EEContext&);  // generated body
void fn_sub_54F730_0054f730__recomp(EEContext&);  // recompiled
void fn_atan2l_6_0054f7a0(EEContext&);  // generated body
void fn_atan2l_6_0054f7a0__recomp(EEContext&);  // recompiled
void fn_cosl_6_0054f7b8(EEContext&);  // generated body
void fn_cosl_6_0054f7b8__recomp(EEContext&);  // recompiled
void fn_coshl_6_0054f7d0(EEContext&);  // generated body
void fn_coshl_6_0054f7d0__recomp(EEContext&);  // recompiled
void fn_sub_54F8C8_0054f8c8(EEContext&);  // generated body
void fn_sub_54F8C8_0054f8c8__recomp(EEContext&);  // recompiled
void fn_sub_54FA78_0054fa78(EEContext&);  // generated body
void fn_sub_54FA78_0054fa78__recomp(EEContext&);  // recompiled
void fn_sub_54FC68_0054fc68(EEContext&);  // generated body
void fn_sub_54FC68_0054fc68__recomp(EEContext&);  // recompiled
void fn_sub_54FE58_0054fe58(EEContext&);  // generated body
void fn_sub_54FE58_0054fe58__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"__errno_0", 0x540D70, &recomp_gen::fn___errno_0_00540d70, &recomp_gen::fn___errno_0_00540d70__recomp},
    {"sub_541040", 0x541040, &recomp_gen::fn_sub_541040_00541040, &recomp_gen::fn_sub_541040_00541040__recomp},
    {"sub_541058", 0x541058, &recomp_gen::fn_sub_541058_00541058, &recomp_gen::fn_sub_541058_00541058__recomp},
    {"sub_5410A0", 0x5410A0, &recomp_gen::fn_sub_5410A0_005410a0, &recomp_gen::fn_sub_5410A0_005410a0__recomp},
    {"sub_541100", 0x541100, &recomp_gen::fn_sub_541100_00541100, &recomp_gen::fn_sub_541100_00541100__recomp},
    {"sub_541118", 0x541118, &recomp_gen::fn_sub_541118_00541118, &recomp_gen::fn_sub_541118_00541118__recomp},
    {"sub_541180", 0x541180, &recomp_gen::fn_sub_541180_00541180, &recomp_gen::fn_sub_541180_00541180__recomp},
    {"sub_541198", 0x541198, &recomp_gen::fn_sub_541198_00541198, &recomp_gen::fn_sub_541198_00541198__recomp},
    {"ADXM_SetupThrdEx", 0x5411B0, &recomp_gen::fn_ADXM_SetupThrdEx_005411b0, &recomp_gen::fn_ADXM_SetupThrdEx_005411b0__recomp},
    {"sub_5413A0", 0x5413A0, &recomp_gen::fn_sub_5413A0_005413a0, &recomp_gen::fn_sub_5413A0_005413a0__recomp},
    {"sub_541450", 0x541450, &recomp_gen::fn_sub_541450_00541450, &recomp_gen::fn_sub_541450_00541450__recomp},
    {"sub_541478", 0x541478, &recomp_gen::fn_sub_541478_00541478, &recomp_gen::fn_sub_541478_00541478__recomp},
    {"sub_5414A0", 0x5414A0, &recomp_gen::fn_sub_5414A0_005414a0, &recomp_gen::fn_sub_5414A0_005414a0__recomp},
    {"sub_5414B8", 0x5414B8, &recomp_gen::fn_sub_5414B8_005414b8, &recomp_gen::fn_sub_5414B8_005414b8__recomp},
    {"sub_541540", 0x541540, &recomp_gen::fn_sub_541540_00541540, &recomp_gen::fn_sub_541540_00541540__recomp},
    {"sub_5415C0", 0x5415C0, &recomp_gen::fn_sub_5415C0_005415c0, &recomp_gen::fn_sub_5415C0_005415c0__recomp},
    {"__errno_1", 0x541628, &recomp_gen::fn___errno_1_00541628, &recomp_gen::fn___errno_1_00541628__recomp},
    {"sub_541638", 0x541638, &recomp_gen::fn_sub_541638_00541638, &recomp_gen::fn_sub_541638_00541638__recomp},
    {"sub_541668", 0x541668, &recomp_gen::fn_sub_541668_00541668, &recomp_gen::fn_sub_541668_00541668__recomp},
    {"sub_5417F8", 0x5417F8, &recomp_gen::fn_sub_5417F8_005417f8, &recomp_gen::fn_sub_5417F8_005417f8__recomp},
    {"sub_541838", 0x541838, &recomp_gen::fn_sub_541838_00541838, &recomp_gen::fn_sub_541838_00541838__recomp},
    {"sub_541878", 0x541878, &recomp_gen::fn_sub_541878_00541878, &recomp_gen::fn_sub_541878_00541878__recomp},
    {"sub_5418B0", 0x5418B0, &recomp_gen::fn_sub_5418B0_005418b0, &recomp_gen::fn_sub_5418B0_005418b0__recomp},
    {"sub_5418E8", 0x5418E8, &recomp_gen::fn_sub_5418E8_005418e8, &recomp_gen::fn_sub_5418E8_005418e8__recomp},
    {"sub_541900", 0x541900, &recomp_gen::fn_sub_541900_00541900, &recomp_gen::fn_sub_541900_00541900__recomp},
    {"sub_541918", 0x541918, &recomp_gen::fn_sub_541918_00541918, &recomp_gen::fn_sub_541918_00541918__recomp},
    {"sub_541930", 0x541930, &recomp_gen::fn_sub_541930_00541930, &recomp_gen::fn_sub_541930_00541930__recomp},
    {"sub_541948", 0x541948, &recomp_gen::fn_sub_541948_00541948, &recomp_gen::fn_sub_541948_00541948__recomp},
    {"sub_541960", 0x541960, &recomp_gen::fn_sub_541960_00541960, &recomp_gen::fn_sub_541960_00541960__recomp},
    {"sub_544900", 0x544900, &recomp_gen::fn_sub_544900_00544900, &recomp_gen::fn_sub_544900_00544900__recomp},
    {"sub_544A00", 0x544A00, &recomp_gen::fn_sub_544A00_00544a00, &recomp_gen::fn_sub_544A00_00544a00__recomp},
    {"sub_545158", 0x545158, &recomp_gen::fn_sub_545158_00545158, &recomp_gen::fn_sub_545158_00545158__recomp},
    {"sub_5451B0", 0x5451B0, &recomp_gen::fn_sub_5451B0_005451b0, &recomp_gen::fn_sub_5451B0_005451b0__recomp},
    {"sub_545208", 0x545208, &recomp_gen::fn_sub_545208_00545208, &recomp_gen::fn_sub_545208_00545208__recomp},
    {"sub_5453D8", 0x5453D8, &recomp_gen::fn_sub_5453D8_005453d8, &recomp_gen::fn_sub_5453D8_005453d8__recomp},
    {"sub_545448", 0x545448, &recomp_gen::fn_sub_545448_00545448, &recomp_gen::fn_sub_545448_00545448__recomp},
    {"sub_545570", 0x545570, &recomp_gen::fn_sub_545570_00545570, &recomp_gen::fn_sub_545570_00545570__recomp},
    {"sub_545580", 0x545580, &recomp_gen::fn_sub_545580_00545580, &recomp_gen::fn_sub_545580_00545580__recomp},
    {"sub_545590", 0x545590, &recomp_gen::fn_sub_545590_00545590, &recomp_gen::fn_sub_545590_00545590__recomp},
    {"sub_545610", 0x545610, &recomp_gen::fn_sub_545610_00545610, &recomp_gen::fn_sub_545610_00545610__recomp},
    {"sub_545838", 0x545838, &recomp_gen::fn_sub_545838_00545838, &recomp_gen::fn_sub_545838_00545838__recomp},
    {"sub_545948", 0x545948, &recomp_gen::fn_sub_545948_00545948, &recomp_gen::fn_sub_545948_00545948__recomp},
    {"sub_545AB8", 0x545AB8, &recomp_gen::fn_sub_545AB8_00545ab8, &recomp_gen::fn_sub_545AB8_00545ab8__recomp},
    {"sub_545B50", 0x545B50, &recomp_gen::fn_sub_545B50_00545b50, &recomp_gen::fn_sub_545B50_00545b50__recomp},
    {"sub_545B90", 0x545B90, &recomp_gen::fn_sub_545B90_00545b90, &recomp_gen::fn_sub_545B90_00545b90__recomp},
    {"sub_545CC8", 0x545CC8, &recomp_gen::fn_sub_545CC8_00545cc8, &recomp_gen::fn_sub_545CC8_00545cc8__recomp},
    {"sub_546770", 0x546770, &recomp_gen::fn_sub_546770_00546770, &recomp_gen::fn_sub_546770_00546770__recomp},
    {"sub_546EC0", 0x546EC0, &recomp_gen::fn_sub_546EC0_00546ec0, &recomp_gen::fn_sub_546EC0_00546ec0__recomp},
    {"sub_546EF0", 0x546EF0, &recomp_gen::fn_sub_546EF0_00546ef0, &recomp_gen::fn_sub_546EF0_00546ef0__recomp},
    {"sub_546F48", 0x546F48, &recomp_gen::fn_sub_546F48_00546f48, &recomp_gen::fn_sub_546F48_00546f48__recomp},
    {"sub_546F98", 0x546F98, &recomp_gen::fn_sub_546F98_00546f98, &recomp_gen::fn_sub_546F98_00546f98__recomp},
    {"sub_5470E8", 0x5470E8, &recomp_gen::fn_sub_5470E8_005470e8, &recomp_gen::fn_sub_5470E8_005470e8__recomp},
    {"sub_547120", 0x547120, &recomp_gen::fn_sub_547120_00547120, &recomp_gen::fn_sub_547120_00547120__recomp},
    {"sub_5471B8", 0x5471B8, &recomp_gen::fn_sub_5471B8_005471b8, &recomp_gen::fn_sub_5471B8_005471b8__recomp},
    {"sub_547248", 0x547248, &recomp_gen::fn_sub_547248_00547248, &recomp_gen::fn_sub_547248_00547248__recomp},
    {"sub_5472E8", 0x5472E8, &recomp_gen::fn_sub_5472E8_005472e8, &recomp_gen::fn_sub_5472E8_005472e8__recomp},
    {"sub_547418", 0x547418, &recomp_gen::fn_sub_547418_00547418, &recomp_gen::fn_sub_547418_00547418__recomp},
    {"sub_547468", 0x547468, &recomp_gen::fn_sub_547468_00547468, &recomp_gen::fn_sub_547468_00547468__recomp},
    {"sub_5474B8", 0x5474B8, &recomp_gen::fn_sub_5474B8_005474b8, &recomp_gen::fn_sub_5474B8_005474b8__recomp},
    {"__errno_2", 0x547500, &recomp_gen::fn___errno_2_00547500, &recomp_gen::fn___errno_2_00547500__recomp},
    {"sub_547548", 0x547548, &recomp_gen::fn_sub_547548_00547548, &recomp_gen::fn_sub_547548_00547548__recomp},
    {"sub_547590", 0x547590, &recomp_gen::fn_sub_547590_00547590, &recomp_gen::fn_sub_547590_00547590__recomp},
    {"sub_547598", 0x547598, &recomp_gen::fn_sub_547598_00547598, &recomp_gen::fn_sub_547598_00547598__recomp},
    {"sub_5475C8", 0x5475C8, &recomp_gen::fn_sub_5475C8_005475c8, &recomp_gen::fn_sub_5475C8_005475c8__recomp},
    {"sub_547650", 0x547650, &recomp_gen::fn_sub_547650_00547650, &recomp_gen::fn_sub_547650_00547650__recomp},
    {"log10l_3", 0x547A58, &recomp_gen::fn_log10l_3_00547a58, &recomp_gen::fn_log10l_3_00547a58__recomp},
    {"sub_547AA8", 0x547AA8, &recomp_gen::fn_sub_547AA8_00547aa8, &recomp_gen::fn_sub_547AA8_00547aa8__recomp},
    {"sub_547F78", 0x547F78, &recomp_gen::fn_sub_547F78_00547f78, &recomp_gen::fn_sub_547F78_00547f78__recomp},
    {"sub_548250", 0x548250, &recomp_gen::fn_sub_548250_00548250, &recomp_gen::fn_sub_548250_00548250__recomp},
    {"sub_548300", 0x548300, &recomp_gen::fn_sub_548300_00548300, &recomp_gen::fn_sub_548300_00548300__recomp},
    {"sub_5485A8", 0x5485A8, &recomp_gen::fn_sub_5485A8_005485a8, &recomp_gen::fn_sub_5485A8_005485a8__recomp},
    {"sub_548800", 0x548800, &recomp_gen::fn_sub_548800_00548800, &recomp_gen::fn_sub_548800_00548800__recomp},
    {"sub_548888", 0x548888, &recomp_gen::fn_sub_548888_00548888, &recomp_gen::fn_sub_548888_00548888__recomp},
    {"sub_548AD0", 0x548AD0, &recomp_gen::fn_sub_548AD0_00548ad0, &recomp_gen::fn_sub_548AD0_00548ad0__recomp},
    {"sub_548E68", 0x548E68, &recomp_gen::fn_sub_548E68_00548e68, &recomp_gen::fn_sub_548E68_00548e68__recomp},
    {"sub_549088", 0x549088, &recomp_gen::fn_sub_549088_00549088, &recomp_gen::fn_sub_549088_00549088__recomp},
    {"sub_549110", 0x549110, &recomp_gen::fn_sub_549110_00549110, &recomp_gen::fn_sub_549110_00549110__recomp},
    {"sub_5492C8", 0x5492C8, &recomp_gen::fn_sub_5492C8_005492c8, &recomp_gen::fn_sub_5492C8_005492c8__recomp},
    {"sub_549568", 0x549568, &recomp_gen::fn_sub_549568_00549568, &recomp_gen::fn_sub_549568_00549568__recomp},
    {"sub_5495D0", 0x5495D0, &recomp_gen::fn_sub_5495D0_005495d0, &recomp_gen::fn_sub_5495D0_005495d0__recomp},
    {"sub_549638", 0x549638, &recomp_gen::fn_sub_549638_00549638, &recomp_gen::fn_sub_549638_00549638__recomp},
    {"sub_549690", 0x549690, &recomp_gen::fn_sub_549690_00549690, &recomp_gen::fn_sub_549690_00549690__recomp},
    {"sub_5496E0", 0x5496E0, &recomp_gen::fn_sub_5496E0_005496e0, &recomp_gen::fn_sub_5496E0_005496e0__recomp},
    {"sub_5497A8", 0x5497A8, &recomp_gen::fn_sub_5497A8_005497a8, &recomp_gen::fn_sub_5497A8_005497a8__recomp},
    {"sub_5498D0", 0x5498D0, &recomp_gen::fn_sub_5498D0_005498d0, &recomp_gen::fn_sub_5498D0_005498d0__recomp},
    {"sub_5499B0", 0x5499B0, &recomp_gen::fn_sub_5499B0_005499b0, &recomp_gen::fn_sub_5499B0_005499b0__recomp},
    {"sub_549A70", 0x549A70, &recomp_gen::fn_sub_549A70_00549a70, &recomp_gen::fn_sub_549A70_00549a70__recomp},
    {"sub_549B08", 0x549B08, &recomp_gen::fn_sub_549B08_00549b08, &recomp_gen::fn_sub_549B08_00549b08__recomp},
    {"sub_549C58", 0x549C58, &recomp_gen::fn_sub_549C58_00549c58, &recomp_gen::fn_sub_549C58_00549c58__recomp},
    {"sub_549D78", 0x549D78, &recomp_gen::fn_sub_549D78_00549d78, &recomp_gen::fn_sub_549D78_00549d78__recomp},
    {"sub_549E68", 0x549E68, &recomp_gen::fn_sub_549E68_00549e68, &recomp_gen::fn_sub_549E68_00549e68__recomp},
    {"sub_549FE0", 0x549FE0, &recomp_gen::fn_sub_549FE0_00549fe0, &recomp_gen::fn_sub_549FE0_00549fe0__recomp},
    {"sub_54A090", 0x54A090, &recomp_gen::fn_sub_54A090_0054a090, &recomp_gen::fn_sub_54A090_0054a090__recomp},
    {"sub_54A108", 0x54A108, &recomp_gen::fn_sub_54A108_0054a108, &recomp_gen::fn_sub_54A108_0054a108__recomp},
    {"sub_54A2B8", 0x54A2B8, &recomp_gen::fn_sub_54A2B8_0054a2b8, &recomp_gen::fn_sub_54A2B8_0054a2b8__recomp},
    {"sub_54A328", 0x54A328, &recomp_gen::fn_sub_54A328_0054a328, &recomp_gen::fn_sub_54A328_0054a328__recomp},
    {"sub_54A390", 0x54A390, &recomp_gen::fn_sub_54A390_0054a390, &recomp_gen::fn_sub_54A390_0054a390__recomp},
    {"sub_54A5C8", 0x54A5C8, &recomp_gen::fn_sub_54A5C8_0054a5c8, &recomp_gen::fn_sub_54A5C8_0054a5c8__recomp},
    {"sub_54A618", 0x54A618, &recomp_gen::fn_sub_54A618_0054a618, &recomp_gen::fn_sub_54A618_0054a618__recomp},
    {"sub_54A678", 0x54A678, &recomp_gen::fn_sub_54A678_0054a678, &recomp_gen::fn_sub_54A678_0054a678__recomp},
    {"sub_54A6B0", 0x54A6B0, &recomp_gen::fn_sub_54A6B0_0054a6b0, &recomp_gen::fn_sub_54A6B0_0054a6b0__recomp},
    {"sub_54A710", 0x54A710, &recomp_gen::fn_sub_54A710_0054a710, &recomp_gen::fn_sub_54A710_0054a710__recomp},
    {"sub_54A758", 0x54A758, &recomp_gen::fn_sub_54A758_0054a758, &recomp_gen::fn_sub_54A758_0054a758__recomp},
    {"sub_54A878", 0x54A878, &recomp_gen::fn_sub_54A878_0054a878, &recomp_gen::fn_sub_54A878_0054a878__recomp},
    {"sub_54A880", 0x54A880, &recomp_gen::fn_sub_54A880_0054a880, &recomp_gen::fn_sub_54A880_0054a880__recomp},
    {"sub_54A8C0", 0x54A8C0, &recomp_gen::fn_sub_54A8C0_0054a8c0, &recomp_gen::fn_sub_54A8C0_0054a8c0__recomp},
    {"sub_54A910", 0x54A910, &recomp_gen::fn_sub_54A910_0054a910, &recomp_gen::fn_sub_54A910_0054a910__recomp},
    {"sub_54A9D8", 0x54A9D8, &recomp_gen::fn_sub_54A9D8_0054a9d8, &recomp_gen::fn_sub_54A9D8_0054a9d8__recomp},
    {"sub_54AA30", 0x54AA30, &recomp_gen::fn_sub_54AA30_0054aa30, &recomp_gen::fn_sub_54AA30_0054aa30__recomp},
    {"sub_54AA80", 0x54AA80, &recomp_gen::fn_sub_54AA80_0054aa80, &recomp_gen::fn_sub_54AA80_0054aa80__recomp},
    {"sub_54AAF0", 0x54AAF0, &recomp_gen::fn_sub_54AAF0_0054aaf0, &recomp_gen::fn_sub_54AAF0_0054aaf0__recomp},
    {"sub_54AB78", 0x54AB78, &recomp_gen::fn_sub_54AB78_0054ab78, &recomp_gen::fn_sub_54AB78_0054ab78__recomp},
    {"sub_54ABA8", 0x54ABA8, &recomp_gen::fn_sub_54ABA8_0054aba8, &recomp_gen::fn_sub_54ABA8_0054aba8__recomp},
    {"sub_54AC80", 0x54AC80, &recomp_gen::fn_sub_54AC80_0054ac80, &recomp_gen::fn_sub_54AC80_0054ac80__recomp},
    {"sub_54ACD8", 0x54ACD8, &recomp_gen::fn_sub_54ACD8_0054acd8, &recomp_gen::fn_sub_54ACD8_0054acd8__recomp},
    {"sub_54AF38", 0x54AF38, &recomp_gen::fn_sub_54AF38_0054af38, &recomp_gen::fn_sub_54AF38_0054af38__recomp},
    {"sub_54AF78", 0x54AF78, &recomp_gen::fn_sub_54AF78_0054af78, &recomp_gen::fn_sub_54AF78_0054af78__recomp},
    {"sub_54AFD8", 0x54AFD8, &recomp_gen::fn_sub_54AFD8_0054afd8, &recomp_gen::fn_sub_54AFD8_0054afd8__recomp},
    {"sub_54B028", 0x54B028, &recomp_gen::fn_sub_54B028_0054b028, &recomp_gen::fn_sub_54B028_0054b028__recomp},
    {"sub_54B070", 0x54B070, &recomp_gen::fn_sub_54B070_0054b070, &recomp_gen::fn_sub_54B070_0054b070__recomp},
    {"sub_54B388", 0x54B388, &recomp_gen::fn_sub_54B388_0054b388, &recomp_gen::fn_sub_54B388_0054b388__recomp},
    {"sub_54C580", 0x54C580, &recomp_gen::fn_sub_54C580_0054c580, &recomp_gen::fn_sub_54C580_0054c580__recomp},
    {"sub_54CB08", 0x54CB08, &recomp_gen::fn_sub_54CB08_0054cb08, &recomp_gen::fn_sub_54CB08_0054cb08__recomp},
    {"sub_54D88C", 0x54D88C, &recomp_gen::fn_sub_54D88C_0054d88c, &recomp_gen::fn_sub_54D88C_0054d88c__recomp},
    {"sub_54DAD8", 0x54DAD8, &recomp_gen::fn_sub_54DAD8_0054dad8, &recomp_gen::fn_sub_54DAD8_0054dad8__recomp},
    {"sub_54DD08", 0x54DD08, &recomp_gen::fn_sub_54DD08_0054dd08, &recomp_gen::fn_sub_54DD08_0054dd08__recomp},
    {"sub_54E048", 0x54E048, &recomp_gen::fn_sub_54E048_0054e048, &recomp_gen::fn_sub_54E048_0054e048__recomp},
    {"sub_54E0D8", 0x54E0D8, &recomp_gen::fn_sub_54E0D8_0054e0d8, &recomp_gen::fn_sub_54E0D8_0054e0d8__recomp},
    {"sub_54E130", 0x54E130, &recomp_gen::fn_sub_54E130_0054e130, &recomp_gen::fn_sub_54E130_0054e130__recomp},
    {"sub_54E180", 0x54E180, &recomp_gen::fn_sub_54E180_0054e180, &recomp_gen::fn_sub_54E180_0054e180__recomp},
    {"sub_54E260", 0x54E260, &recomp_gen::fn_sub_54E260_0054e260, &recomp_gen::fn_sub_54E260_0054e260__recomp},
    {"sub_54E388", 0x54E388, &recomp_gen::fn_sub_54E388_0054e388, &recomp_gen::fn_sub_54E388_0054e388__recomp},
    {"sub_54E3C0", 0x54E3C0, &recomp_gen::fn_sub_54E3C0_0054e3c0, &recomp_gen::fn_sub_54E3C0_0054e3c0__recomp},
    {"sub_54E648", 0x54E648, &recomp_gen::fn_sub_54E648_0054e648, &recomp_gen::fn_sub_54E648_0054e648__recomp},
    {"sub_54E658", 0x54E658, &recomp_gen::fn_sub_54E658_0054e658, &recomp_gen::fn_sub_54E658_0054e658__recomp},
    {"sub_54E838", 0x54E838, &recomp_gen::fn_sub_54E838_0054e838, &recomp_gen::fn_sub_54E838_0054e838__recomp},
    {"sub_54E9A0", 0x54E9A0, &recomp_gen::fn_sub_54E9A0_0054e9a0, &recomp_gen::fn_sub_54E9A0_0054e9a0__recomp},
    {"sub_54EAB8", 0x54EAB8, &recomp_gen::fn_sub_54EAB8_0054eab8, &recomp_gen::fn_sub_54EAB8_0054eab8__recomp},
    {"sub_54EAD8", 0x54EAD8, &recomp_gen::fn_sub_54EAD8_0054ead8, &recomp_gen::fn_sub_54EAD8_0054ead8__recomp},
    {"sub_54EBC0", 0x54EBC0, &recomp_gen::fn_sub_54EBC0_0054ebc0, &recomp_gen::fn_sub_54EBC0_0054ebc0__recomp},
    {"sub_54ED48", 0x54ED48, &recomp_gen::fn_sub_54ED48_0054ed48, &recomp_gen::fn_sub_54ED48_0054ed48__recomp},
    {"sub_54F028", 0x54F028, &recomp_gen::fn_sub_54F028_0054f028, &recomp_gen::fn_sub_54F028_0054f028__recomp},
    {"sub_54F730", 0x54F730, &recomp_gen::fn_sub_54F730_0054f730, &recomp_gen::fn_sub_54F730_0054f730__recomp},
    {"atan2l_6", 0x54F7A0, &recomp_gen::fn_atan2l_6_0054f7a0, &recomp_gen::fn_atan2l_6_0054f7a0__recomp},
    {"cosl_6", 0x54F7B8, &recomp_gen::fn_cosl_6_0054f7b8, &recomp_gen::fn_cosl_6_0054f7b8__recomp},
    {"coshl_6", 0x54F7D0, &recomp_gen::fn_coshl_6_0054f7d0, &recomp_gen::fn_coshl_6_0054f7d0__recomp},
    {"sub_54F8C8", 0x54F8C8, &recomp_gen::fn_sub_54F8C8_0054f8c8, &recomp_gen::fn_sub_54F8C8_0054f8c8__recomp},
    {"sub_54FA78", 0x54FA78, &recomp_gen::fn_sub_54FA78_0054fa78, &recomp_gen::fn_sub_54FA78_0054fa78__recomp},
    {"sub_54FC68", 0x54FC68, &recomp_gen::fn_sub_54FC68_0054fc68, &recomp_gen::fn_sub_54FC68_0054fc68__recomp},
    {"sub_54FE58", 0x54FE58, &recomp_gen::fn_sub_54FE58_0054fe58, &recomp_gen::fn_sub_54FE58_0054fe58__recomp},
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
namespace mpa = p3fes::game::libs9::mpa;

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs9: no case for an address");
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
// Only callees other tests of main already stand in (and that no current packet claims), plus none new: every other
// callee either runs (hand-written or emitted) or ends the pair at the call, identically in both bodies. Recorders
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
enum class Arg { None, Adxt, Mpa };
Arg arg_of(u32 a) {
    switch (a) {
    case 0x548888u: case 0x548E68u: case 0x549088u: case 0x549110u: case 0x549568u: case 0x5495D0u: case 0x549638u:
    case 0x549690u: case 0x5497A8u: case 0x5498D0u: case 0x5499B0u: case 0x549A70u: case 0x549B08u: case 0x549C58u:
    case 0x549D78u: case 0x549E68u: case 0x54A090u: case 0x54A108u: case 0x54A2B8u: case 0x54A328u: case 0x54A390u:
    case 0x54A678u: case 0x54A6B0u: case 0x54A710u: case 0x54A758u: case 0x54A878u: case 0x54A880u: case 0x54A8C0u:
    case 0x54A910u: case 0x54A9D8u: case 0x54AA30u: case 0x54AA80u: case 0x54AAF0u: case 0x54AB78u: case 0x54AC80u:
    case 0x54ACD8u: case 0x54AF38u: case 0x54AF78u: case 0x54B028u: case 0x54B070u: case 0x54C580u: case 0x54CB08u:
        return Arg::Adxt;
    case 0x54E260u: case 0x54E388u: case 0x54E3C0u: case 0x54E648u: case 0x54E658u: case 0x54E838u:
        return Arg::Mpa;
    default:
        return Arg::None;
    }
}

}  // namespace

TEST_CASE("game(libs9): every body equals its recompiled body on random worlds") {
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

// The battle (b_5800), boot-movie (libs5_movie_860) and dorm (dorm_replay_4900) snapshots hold live ADXT handles (the
// 16 x 200-byte pool of cri2.h: 8 live across the three); the MPEG-audio decoder's table 0x797598 is empty in all three, so its functions run on null and the random worlds only. Every
// function runs on them with the record its role takes -- each live handle and null for the ADXT and decoder functions,
// 0 / 1 / an output buffer otherwise -- second arguments from the values its branches test and the stood-in callees
// returning 0 or 1; each pair starts from the snapshot.
TEST_CASE("game(libs9): every body on the snapshots' live ADXT and MPEG-audio handles") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int runs = 0, stops = 0, live_adxt = 0, live_mpa = 0;
    for (const char* dir : {"b_5800", "libs5_movie_860", "dorm_replay_4900"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        std::vector<u64> handles, decoders;
        for (u32 i = 0; i < adxt::kCount; ++i)
            if (r8(*m, adxt::kPool + i * adxt::kSize) == 1) handles.push_back(adxt::kPool + i * adxt::kSize);
        for (u32 i = 0; i < 16; ++i)
            if (const u32 d = r32(*m, mpa::kTable + 4 * i); d != 0 && in_ram(d)) decoders.push_back(d);
        live_adxt += static_cast<int>(handles.size());
        live_mpa += static_cast<int>(decoders.size());
        handles.push_back(0);
        decoders.push_back(0);
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            std::vector<u64> a0s;
            switch (arg_of(c.addr)) {
            case Arg::Adxt: a0s = handles; break;
            case Arg::Mpa: a0s = decoders; break;
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
    MESSAGE(runs << " pairs from the snapshots (" << live_adxt << " live ADXT handles, " << live_mpa
                 << " MPEG-audio decoders), " << stops << " stopped identically");
}

// The ADXT accessors' documented rules on a handle built in a zeroed world: the null-handle reports (message and
// result), the status / volume / flag getters, the refill threshold (85 % of the buffer, a given value, passed to the streamer), the
// error-field reset and the time offset.
TEST_CASE("game(libs9): the ADXT accessors' rules") {
    auto m = machine();
    if (!m) return;
    const u32 h = kWorld;
    auto fresh = [&] {
        std::memset(m->at(kWorld), 0, kWorldSize);
        w8(*m, h + adxt::kStat, 5);
        w16(*m, h + adxt::kMaxSct, 100);
        w16(*m, h + adxt::kOutVol, static_cast<u16>(-60));
        w8(*m, h + adxt::kHold, 0);
        w8(*m, h + adxt::kStarted, 1);
        w8(*m, h + adxt::kPanMode, 1);
        w8(*m, h + adxt::kTrapFlag, 7);
    };
    // the null handle: each reporter logs its own error number and gives its error result
    struct Null { u32 addr; const char* code; s32 result; };
    for (const Null& n : {Null{0x549088u, "E02080822", -1}, Null{0x549110u, "E02080821", -1}, Null{0x549568u, "E02080824", 0},
                          Null{0x549B08u, "E02080834", -1}, Null{0x549D78u, "E02080836", -1}, Null{0x549E68u, "E02080802", -1},
                          Null{0x54A108u, "E02080829", -1}, Null{0x54A2B8u, "E02080833", 0}, Null{0x54A390u, "E02080831", -1},
                          Null{0x54AA80u, "E02080818", -1}, Null{0x54AAF0u, "E04041901", -1}}) {
        fresh();
        StandIns log;
        const s32 v = sv(prv(*m, n.addr, {0, 0, 0, 0}, &log));
        INFO(by_addr(n.addr).name);
        CHECK(v == n.result);
        REQUIRE(log.log.size() == 1);
        CHECK(log.log[0].va == 0x53AE08u);
        CHECK(log.log[0].text.rfind(n.code, 0) == 0);
    }
    fresh();
    CHECK(sv(prv(*m, 0x549E68u, {h, 0, 0, 0})) == 1);  // status 5: play end
    w8(*m, h + adxt::kStat, 3);
    CHECK(sv(prv(*m, 0x549E68u, {h, 0, 0, 0})) == 0);
    CHECK(sv(prv(*m, 0x549568u, {h, 0, 0, 0})) == -60);  // the s16 volume, sign-extended
    CHECK(sv(prv(*m, 0x54A390u, {h, 0, 0, 0})) == 1);
    CHECK(sv(prv(*m, 0x5497A8u, {h, 0, 0, 0})) == 1);
    CHECK(sv(prv(*m, 0x54A9D8u, {h, 0, 0, 0})) == 7);
    prv(*m, 0x54A328u, {h, 1, 0, 0});
    CHECK(r8(*m, h + adxt::kHold) == 1);
    // status < 2: the decoder accessors give 0 without asking the decoder
    w8(*m, h + adxt::kStat, 1);
    CHECK(sv(prv(*m, 0x549088u, {h, 0, 0, 0})) == 0);
    CHECK(sv(prv(*m, 0x549110u, {h, 0, 0, 0})) == 0);
    // the refill threshold: 85 % of 100 sectors (the float product truncates: 84), a given value; no streamer, no call
    StandIns log;
    prv(*m, 0x5499B0u, {h, 0, 0, 0}, &log);
    CHECK(static_cast<s16>(r16(*m, h + adxt::kMinSct)) == 84);
    CHECK(log.log.empty());
    prv(*m, 0x549A70u, {h, 40, 0, 0}, &log);
    CHECK(static_cast<s16>(r16(*m, h + adxt::kMinSct)) == 40);
    // with a streamer the threshold goes to it in bytes, with the buffer size
    w32(*m, h + adxt::kStm, 0x01812000u);
    prv(*m, 0x549A70u, {h, 30, 0, 0}, &log);
    REQUIRE(log.log.size() == 1);
    CHECK(log.log[0].va == 0x546FA0u);
    CHECK(log.log[0].args[0] == 0x01812000u);
    CHECK(log.log[0].args[1] == 30u << 11);
    CHECK(log.log[0].args[2] == 100u << 11);
    // the error fields cleared; the time offset stored and read back
    w16(*m, h + 96, 0xFFFF);
    w32(*m, h + 100, 5);
    w16(*m, h + 104, 3);
    w16(*m, h + 106, 4);
    prv(*m, 0x54A090u, {h, 0, 0, 0});
    CHECK(r16(*m, h + 96) == 0);
    CHECK(r32(*m, h + 100) == 0);
    CHECK(r16(*m, h + 104) == 0);
    CHECK(r16(*m, h + 106) == 0);
    prv(*m, 0x54A8C0u, {h, 12345, 0, 0});
    CHECK(sv(prv(*m, 0x54A878u, {h, 0, 0, 0})) == 12345);
    // the play time in hundredths of a second: 3 s -> 300
    g_time = 3 * 44100;
    CHECK(sv(prv(*m, 0x548E68u, {h, 0, 0, 0})) == 300);
    MESSAGE(summary());
}

// The ADX encoder: create on the zeroed pool fills the defaults before its first work-buffer request (sub_543BF0, not
// emitted here: the pair ends there identically); the setters; finish's use count; the server on a free pool.
TEST_CASE("game(libs9): the ADX encoder's handle rules") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(enc::kPool), 0, enc::kCount * enc::kSize);
    std::memset(m->at(kWorld), 0, kWorldSize);
    w32(*m, kWorld, 0x01811000u);
    w32(*m, kWorld + 4, 0x01811100u);
    // a taken first slot: create picks the second
    w8(*m, enc::kPool, 1);
    // the pair stops at the first sub_543BF0 call while that callee is absent; with it replaced (libs8) it may run on
    const hgp::Run r = pr(*m, 0x545208u, {2, kWorld, 0x01811200u, 0});
    const u32 h = enc::kPool + enc::kSize;
    CHECK(r8(*m, h + enc::kNchIn) == 2);
    CHECK(r32(*m, h + enc::kSjIn) == 0x01811000u);
    CHECK(r32(*m, h + enc::kSjIn + 4) == 0x01811100u);
    CHECK(r32(*m, h + enc::kSjOut) == 0x01811200u);
    CHECK(r32(*m, h + enc::kEncoding) == 3u);
    CHECK(r32(*m, h + enc::kBlockSize) == 18u);
    CHECK(r32(*m, h + enc::kBits) == 4u);
    CHECK(r32(*m, h + enc::kNch) == 2u);
    CHECK(r32(*m, h + enc::kRate) == 44100u);
    CHECK(r32(*m, h + enc::kHighpass) == 500u);
    CHECK(r32(*m, h + enc::kTotal) == 0x7FFF0000u);
    CHECK(r32(*m, h + enc::kWorkSize) == 32u);
    CHECK(r8(*m, h + enc::kUsed) == (r.stopped ? 0 : 1));  // taken only at the end
    // a full pool: 0, no call
    for (u32 i = 0; i < enc::kCount; ++i) w8(*m, enc::kPool + i * enc::kSize, 1);
    CHECK(prv(*m, 0x545208u, {1, kWorld, 0, 0}) == 0);
    // the setters
    prv(*m, 0x545580u, {h, 22050, 0, 0});
    CHECK(r32(*m, h + enc::kRate) == 22050u);
    prv(*m, 0x545590u, {h, 1, 0, 0});
    CHECK(r32(*m, h + enc::kNch) == 1u);
    prv(*m, 0x545610u, {h, 999, 0, 0});
    CHECK(r32(*m, h + enc::kTotal) == 999u);
    CHECK(r32(*m, h + enc::kLimit) == 999u);
    prv(*m, 0x545838u, {h, 2, 48000, 1000});
    CHECK(r32(*m, h + enc::kNch) == 2u);
    CHECK(r32(*m, h + enc::kRate) == 48000u);
    CHECK(r32(*m, h + enc::kTotal) == 1000u);
    CHECK(r32(*m, h + enc::kHdrOfs) == 284u);
    CHECK(sv(prv(*m, 0x545570u, {h, 0, 0, 0})) == 1);
    CHECK(r8(*m, h + enc::kEnd) == 1);
    // the state dispatch: state 0 gives 2 without work
    w8(*m, h + enc::kState, 0);
    CHECK(sv(prv(*m, 0x545B50u, {h, 0, 0, 0})) == 2);
    // the server on a free pool: nothing runs
    std::memset(m->at(enc::kPool), 0, enc::kCount * enc::kSize);
    StandIns log;
    prv(*m, 0x545B90u, {0, 0, 0, 0}, &log);
    CHECK(log.log.empty());
    // finish: the use count drops (no work while it stays above 0)
    w32(*m, 0x790A28u, 2);
    prv(*m, 0x5451B0u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x790A28u) == 1u);
    MESSAGE(summary());
}

// Small rules: ADXT's time mode and vsync rate, the streamer's request size, the four-word record, the getters.
TEST_CASE("game(libs9): the time mode, the request size and the small getters") {
    auto m = machine();
    if (!m) return;
    w32(*m, 0x793B60u, 1);
    prv(*m, 0x548800u, {1, 0, 0, 0});
    CHECK(r32(*m, 0x793B60u) == 5994u);  // NTSC: 59.94 Hz in hundredths
    CHECK(r32(*m, 0x793B14u) == 1u);
    prv(*m, 0x548800u, {2, 0, 0, 0});
    CHECK(r32(*m, 0x793B60u) == 5000u);  // PAL
    prv(*m, 0x548800u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x793B60u) == 5000u);  // other modes leave the rate
    CHECK(r32(*m, 0x793B14u) == 0u);
    std::memset(m->at(kWorld), 0, 0x100);
    prv(*m, 0x547418u, {kWorld, 7, 0, 0});
    CHECK(r32(*m, kWorld + 20) == 7u);
    CHECK(r32(*m, kWorld + 16) == 7u << 11);
    CHECK(prv(*m, 0x5414B8u, {1, 2, 3, 4}) == 0x997038u);
    for (u32 i = 0; i < 4; ++i) CHECK(r32(*m, 0x997038u + 4 * i) == i + 1);
    w32(*m, kWorld + 24, 11);
    w32(*m, kWorld + 28, 22);
    CHECK(prv(*m, 0x546F48u, {kWorld, kWorld + 0x40, kWorld + 0x44, 0}) == 1);
    CHECK(r32(*m, kWorld + 0x40) == 22u);
    CHECK(r32(*m, kWorld + 0x44) == 11u);
    CHECK(prv(*m, 0x54D88Cu, {5, 0x1234, 0, 0}) == 0x1234u);
    w32(*m, 0x790000u + 0x2BD0u, 0);
    prv(*m, 0x5474B8u, {77, 0, 0, 0});
    CHECK(prv(*m, 0x547500u, {0, 0, 0, 0}) == 77u);
    w32(*m, kWorld + 424, 12);
    CHECK(prv(*m, 0x54E648u, {kWorld, 0, 0, 0}) == 1u);
    w32(*m, kWorld + 424, 11);
    CHECK(prv(*m, 0x54E648u, {kWorld, 0, 0, 0}) == 0u);
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs9): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
