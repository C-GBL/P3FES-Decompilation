// Phase 5 pair tests for slice battle5 (game/src/battle/battle5.cpp): every body against its recompiled body (__recomp)
// on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack and every stray store), the
// scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same deterministic
// heap behind the RwMalloc / RwFree slots, sprintf and the H_Cdvd layer, and the same recorders).
//
//   * random worlds (the p3fes_handgen skeleton's);
//   * battle worlds: the replay snapshots b_5800 (the first battle in state ACTION: live gBtl, btlActions, btlUnits,
//     DatUnits, packets, the battle panel works), battle_ref_6150 / b_6150 (the battle over: the result screen),
//     b_6300 / b_6700 / climb_ref_17000 (no battle: the null paths). Each pair is perturbed the way the branches ask --
//     bad-status bits, HP, the encounter id (the boss encounters 416..436 / 456 and 0x1A0..0x1B4), a boss enemy id on
//     one enemy unit, the gBtl flag bits the bodies test (sound, navigator ready, analysis view, scene lit, the battle
//     over), the navigator / support words, the unit walk / model / motion words, the panel works' flags -- and
//     restored afterwards (a long-lived BaseRange); the arguments are of the kind each function takes (an action, a
//     unit, a packet data block of the packet's layout, a sprite sheet, a camera shot, a bp_list record, ...).
//   * documented rules on the host: the formation pick against the formation table, the boss tables by encounter
//     (fixed placements, the reaction motions, the win conditions), the battle music by the encounter table, the voice
//     line maps of the party members, the skill / named sound file paths, the op fade's alpha, the bp_list cursor, the
//     indexed grid mesh, the analysis view close.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
namespace b3 = p3fes::game::b3;
namespace b4 = p3fes::game::b4;
namespace b5 = p3fes::game::b5;

namespace p3fes::recomp_gen {
void fn_sub_242CC0_00242cc0(EEContext&);
void fn_sub_242CC0_00242cc0__recomp(EEContext&);
void fn_sub_2441B0_002441b0(EEContext&);
void fn_sub_2441B0_002441b0__recomp(EEContext&);
void fn_sub_244770_00244770(EEContext&);
void fn_sub_244770_00244770__recomp(EEContext&);
void fn_sub_244A00_00244a00(EEContext&);
void fn_sub_244A00_00244a00__recomp(EEContext&);
void fn_sub_244A40_00244a40(EEContext&);
void fn_sub_244A40_00244a40__recomp(EEContext&);
void fn_sub_248500_00248500(EEContext&);
void fn_sub_248500_00248500__recomp(EEContext&);
void fn_sub_248F40_00248f40(EEContext&);
void fn_sub_248F40_00248f40__recomp(EEContext&);
void fn_sub_249250_00249250(EEContext&);
void fn_sub_249250_00249250__recomp(EEContext&);
void fn_sub_2492B0_002492b0(EEContext&);
void fn_sub_2492B0_002492b0__recomp(EEContext&);
void fn_sub_249690_00249690(EEContext&);
void fn_sub_249690_00249690__recomp(EEContext&);
void fn_sub_24A230_0024a230(EEContext&);
void fn_sub_24A230_0024a230__recomp(EEContext&);
void fn_sub_24A260_0024a260(EEContext&);
void fn_sub_24A260_0024a260__recomp(EEContext&);
void fn_sub_24A630_0024a630(EEContext&);
void fn_sub_24A630_0024a630__recomp(EEContext&);
void fn_sub_24CCA0_0024cca0(EEContext&);
void fn_sub_24CCA0_0024cca0__recomp(EEContext&);
void fn_sub_25B690_0025b690(EEContext&);
void fn_sub_25B690_0025b690__recomp(EEContext&);
void fn_sub_25C220_0025c220(EEContext&);
void fn_sub_25C220_0025c220__recomp(EEContext&);
void fn_sub_25CF20_0025cf20(EEContext&);
void fn_sub_25CF20_0025cf20__recomp(EEContext&);
void fn_sub_25D020_0025d020(EEContext&);
void fn_sub_25D020_0025d020__recomp(EEContext&);
void fn_sub_25D130_0025d130(EEContext&);
void fn_sub_25D130_0025d130__recomp(EEContext&);
void fn_sub_25D470_0025d470(EEContext&);
void fn_sub_25D470_0025d470__recomp(EEContext&);
void fn_sub_25F5D0_0025f5d0(EEContext&);
void fn_sub_25F5D0_0025f5d0__recomp(EEContext&);
void fn_sub_25FC50_0025fc50(EEContext&);
void fn_sub_25FC50_0025fc50__recomp(EEContext&);
void fn_sub_260430_00260430(EEContext&);
void fn_sub_260430_00260430__recomp(EEContext&);
void fn_sub_260D20_00260d20(EEContext&);
void fn_sub_260D20_00260d20__recomp(EEContext&);
void fn_sub_260E00_00260e00(EEContext&);
void fn_sub_260E00_00260e00__recomp(EEContext&);
void fn_sub_262730_00262730(EEContext&);
void fn_sub_262730_00262730__recomp(EEContext&);
void fn_sub_2630E0_002630e0(EEContext&);
void fn_sub_2630E0_002630e0__recomp(EEContext&);
void fn_sub_264DD0_00264dd0(EEContext&);
void fn_sub_264DD0_00264dd0__recomp(EEContext&);
void fn_sub_264E30_00264e30(EEContext&);
void fn_sub_264E30_00264e30__recomp(EEContext&);
void fn_sub_264F90_00264f90(EEContext&);
void fn_sub_264F90_00264f90__recomp(EEContext&);
void fn_sub_264FF0_00264ff0(EEContext&);
void fn_sub_264FF0_00264ff0__recomp(EEContext&);
void fn_sub_265C20_00265c20(EEContext&);
void fn_sub_265C20_00265c20__recomp(EEContext&);
void fn_sub_265EF0_00265ef0(EEContext&);
void fn_sub_265EF0_00265ef0__recomp(EEContext&);
void fn_sub_266710_00266710(EEContext&);
void fn_sub_266710_00266710__recomp(EEContext&);
void fn_sub_266EB0_00266eb0(EEContext&);
void fn_sub_266EB0_00266eb0__recomp(EEContext&);
void fn_sub_266F00_00266f00(EEContext&);
void fn_sub_266F00_00266f00__recomp(EEContext&);
void fn_sub_267180_00267180(EEContext&);
void fn_sub_267180_00267180__recomp(EEContext&);
void fn_sub_267260_00267260(EEContext&);
void fn_sub_267260_00267260__recomp(EEContext&);
void fn_sub_267370_00267370(EEContext&);
void fn_sub_267370_00267370__recomp(EEContext&);
void fn_sub_267390_00267390(EEContext&);
void fn_sub_267390_00267390__recomp(EEContext&);
void fn_sub_268E20_00268e20(EEContext&);
void fn_sub_268E20_00268e20__recomp(EEContext&);
void fn_sub_269690_00269690(EEContext&);
void fn_sub_269690_00269690__recomp(EEContext&);
void fn_sub_26C710_0026c710(EEContext&);
void fn_sub_26C710_0026c710__recomp(EEContext&);
void fn_sub_26CC90_0026cc90(EEContext&);
void fn_sub_26CC90_0026cc90__recomp(EEContext&);
void fn_sub_26E000_0026e000(EEContext&);
void fn_sub_26E000_0026e000__recomp(EEContext&);
void fn_sub_271230_00271230(EEContext&);
void fn_sub_271230_00271230__recomp(EEContext&);
void fn_sub_2716D0_002716d0(EEContext&);
void fn_sub_2716D0_002716d0__recomp(EEContext&);
void fn_sub_271C10_00271c10(EEContext&);
void fn_sub_271C10_00271c10__recomp(EEContext&);
void fn_sub_271CD0_00271cd0(EEContext&);
void fn_sub_271CD0_00271cd0__recomp(EEContext&);
void fn_sub_271D70_00271d70(EEContext&);
void fn_sub_271D70_00271d70__recomp(EEContext&);
void fn_sub_271DB0_00271db0(EEContext&);
void fn_sub_271DB0_00271db0__recomp(EEContext&);
void fn_sub_271E10_00271e10(EEContext&);
void fn_sub_271E10_00271e10__recomp(EEContext&);
void fn_sub_271E70_00271e70(EEContext&);
void fn_sub_271E70_00271e70__recomp(EEContext&);
void fn_sub_271EC0_00271ec0(EEContext&);
void fn_sub_271EC0_00271ec0__recomp(EEContext&);
void fn_sub_2721D0_002721d0(EEContext&);
void fn_sub_2721D0_002721d0__recomp(EEContext&);
void fn_sub_272220_00272220(EEContext&);
void fn_sub_272220_00272220__recomp(EEContext&);
void fn_sub_272290_00272290(EEContext&);
void fn_sub_272290_00272290__recomp(EEContext&);
void fn_sub_2722E0_002722e0(EEContext&);
void fn_sub_2722E0_002722e0__recomp(EEContext&);
void fn_sub_272380_00272380(EEContext&);
void fn_sub_272380_00272380__recomp(EEContext&);
void fn_sub_272400_00272400(EEContext&);
void fn_sub_272400_00272400__recomp(EEContext&);
void fn_sub_2727C0_002727c0(EEContext&);
void fn_sub_2727C0_002727c0__recomp(EEContext&);
void fn_sub_273800_00273800(EEContext&);
void fn_sub_273800_00273800__recomp(EEContext&);
void fn_sub_273A10_00273a10(EEContext&);
void fn_sub_273A10_00273a10__recomp(EEContext&);
void fn_sub_273B30_00273b30(EEContext&);
void fn_sub_273B30_00273b30__recomp(EEContext&);
void fn_sub_273E90_00273e90(EEContext&);
void fn_sub_273E90_00273e90__recomp(EEContext&);
void fn_sub_2741F0_002741f0(EEContext&);
void fn_sub_2741F0_002741f0__recomp(EEContext&);
void fn_sub_2743A0_002743a0(EEContext&);
void fn_sub_2743A0_002743a0__recomp(EEContext&);
void fn_sub_2743E0_002743e0(EEContext&);
void fn_sub_2743E0_002743e0__recomp(EEContext&);
void fn_sub_274590_00274590(EEContext&);
void fn_sub_274590_00274590__recomp(EEContext&);
void fn_sub_274C00_00274c00(EEContext&);
void fn_sub_274C00_00274c00__recomp(EEContext&);
void fn_sub_274F00_00274f00(EEContext&);
void fn_sub_274F00_00274f00__recomp(EEContext&);
void fn_sub_275050_00275050(EEContext&);
void fn_sub_275050_00275050__recomp(EEContext&);
void fn_sub_2751E0_002751e0(EEContext&);
void fn_sub_2751E0_002751e0__recomp(EEContext&);
void fn_sub_275370_00275370(EEContext&);
void fn_sub_275370_00275370__recomp(EEContext&);
void fn_sub_2753C0_002753c0(EEContext&);
void fn_sub_2753C0_002753c0__recomp(EEContext&);
void fn_sub_275A80_00275a80(EEContext&);
void fn_sub_275A80_00275a80__recomp(EEContext&);
void fn_sub_275CB0_00275cb0(EEContext&);
void fn_sub_275CB0_00275cb0__recomp(EEContext&);
void fn_sub_2767E0_002767e0(EEContext&);
void fn_sub_2767E0_002767e0__recomp(EEContext&);
void fn_sub_276920_00276920(EEContext&);
void fn_sub_276920_00276920__recomp(EEContext&);
void fn_sub_276930_00276930(EEContext&);
void fn_sub_276930_00276930__recomp(EEContext&);
void fn_sub_2769C0_002769c0(EEContext&);
void fn_sub_2769C0_002769c0__recomp(EEContext&);
void fn_sub_276BA0_00276ba0(EEContext&);
void fn_sub_276BA0_00276ba0__recomp(EEContext&);
void fn_sub_276D30_00276d30(EEContext&);
void fn_sub_276D30_00276d30__recomp(EEContext&);
void fn_sub_276D90_00276d90(EEContext&);
void fn_sub_276D90_00276d90__recomp(EEContext&);
void fn_sub_277070_00277070(EEContext&);
void fn_sub_277070_00277070__recomp(EEContext&);
void fn_sub_2770F0_002770f0(EEContext&);
void fn_sub_2770F0_002770f0__recomp(EEContext&);
void fn_sub_279120_00279120(EEContext&);
void fn_sub_279120_00279120__recomp(EEContext&);
void fn_sub_2791B0_002791b0(EEContext&);
void fn_sub_2791B0_002791b0__recomp(EEContext&);
void fn_sub_2792C0_002792c0(EEContext&);
void fn_sub_2792C0_002792c0__recomp(EEContext&);
void fn_sub_279330_00279330(EEContext&);
void fn_sub_279330_00279330__recomp(EEContext&);
void fn_sub_279660_00279660(EEContext&);
void fn_sub_279660_00279660__recomp(EEContext&);
void fn_sub_27B5B0_0027b5b0(EEContext&);
void fn_sub_27B5B0_0027b5b0__recomp(EEContext&);
void fn_sub_27B5D0_0027b5d0(EEContext&);
void fn_sub_27B5D0_0027b5d0__recomp(EEContext&);
void fn_sub_27BBA0_0027bba0(EEContext&);
void fn_sub_27BBA0_0027bba0__recomp(EEContext&);
void fn_sub_27BE50_0027be50(EEContext&);
void fn_sub_27BE50_0027be50__recomp(EEContext&);
void fn_sub_27F940_0027f940(EEContext&);
void fn_sub_27F940_0027f940__recomp(EEContext&);
void fn_sub_2802D0_002802d0(EEContext&);
void fn_sub_2802D0_002802d0__recomp(EEContext&);
void fn_sub_280390_00280390(EEContext&);
void fn_sub_280390_00280390__recomp(EEContext&);
void fn_sub_280480_00280480(EEContext&);
void fn_sub_280480_00280480__recomp(EEContext&);
void fn_sub_280DA0_00280da0(EEContext&);
void fn_sub_280DA0_00280da0__recomp(EEContext&);
void fn_sub_281AD0_00281ad0(EEContext&);
void fn_sub_281AD0_00281ad0__recomp(EEContext&);
void fn_sub_2823B0_002823b0(EEContext&);
void fn_sub_2823B0_002823b0__recomp(EEContext&);
void fn_sub_2826D0_002826d0(EEContext&);
void fn_sub_2826D0_002826d0__recomp(EEContext&);
void fn_sub_2831C0_002831c0(EEContext&);
void fn_sub_2831C0_002831c0__recomp(EEContext&);
void fn_sub_284E10_00284e10(EEContext&);
void fn_sub_284E10_00284e10__recomp(EEContext&);
void fn_sub_2850F0_002850f0(EEContext&);
void fn_sub_2850F0_002850f0__recomp(EEContext&);
void fn_sub_285750_00285750(EEContext&);
void fn_sub_285750_00285750__recomp(EEContext&);
void fn_sub_287740_00287740(EEContext&);
void fn_sub_287740_00287740__recomp(EEContext&);
void fn_sub_2878D0_002878d0(EEContext&);
void fn_sub_2878D0_002878d0__recomp(EEContext&);
void fn_sub_289B50_00289b50(EEContext&);
void fn_sub_289B50_00289b50__recomp(EEContext&);
void fn_sub_28CDA0_0028cda0(EEContext&);
void fn_sub_28CDA0_0028cda0__recomp(EEContext&);
void fn_sub_28D5A0_0028d5a0(EEContext&);
void fn_sub_28D5A0_0028d5a0__recomp(EEContext&);
void fn_sub_28DBF0_0028dbf0(EEContext&);
void fn_sub_28DBF0_0028dbf0__recomp(EEContext&);
void fn_sub_297A60_00297a60(EEContext&);
void fn_sub_297A60_00297a60__recomp(EEContext&);
void fn_sub_2984E0_002984e0(EEContext&);
void fn_sub_2984E0_002984e0__recomp(EEContext&);
void fn_sub_299270_00299270(EEContext&);
void fn_sub_299270_00299270__recomp(EEContext&);
void fn_sub_299B00_00299b00(EEContext&);
void fn_sub_299B00_00299b00__recomp(EEContext&);
void fn_sub_29DFC0_0029dfc0(EEContext&);
void fn_sub_29DFC0_0029dfc0__recomp(EEContext&);
void fn_sub_29EE20_0029ee20(EEContext&);
void fn_sub_29EE20_0029ee20__recomp(EEContext&);
void fn_sub_29FAA0_0029faa0(EEContext&);
void fn_sub_29FAA0_0029faa0__recomp(EEContext&);
void fn_sub_2A46E0_002a46e0(EEContext&);
void fn_sub_2A46E0_002a46e0__recomp(EEContext&);
void fn_sub_2A4C70_002a4c70(EEContext&);
void fn_sub_2A4C70_002a4c70__recomp(EEContext&);
void fn_sub_2A5430_002a5430(EEContext&);
void fn_sub_2A5430_002a5430__recomp(EEContext&);
void fn_sub_2AD680_002ad680(EEContext&);
void fn_sub_2AD680_002ad680__recomp(EEContext&);
void fn_sub_2AE150_002ae150(EEContext&);
void fn_sub_2AE150_002ae150__recomp(EEContext&);
void fn_sub_2B2060_002b2060(EEContext&);
void fn_sub_2B2060_002b2060__recomp(EEContext&);
void fn_sub_2B58F0_002b58f0(EEContext&);
void fn_sub_2B58F0_002b58f0__recomp(EEContext&);
void fn_sub_2B64D0_002b64d0(EEContext&);
void fn_sub_2B64D0_002b64d0__recomp(EEContext&);
void fn_sub_2B7060_002b7060(EEContext&);
void fn_sub_2B7060_002b7060__recomp(EEContext&);
void fn_sub_2B71E0_002b71e0(EEContext&);
void fn_sub_2B71E0_002b71e0__recomp(EEContext&);
void fn_sub_2C6300_002c6300(EEContext&);
void fn_sub_2C6300_002c6300__recomp(EEContext&);
void fn_sub_2D1210_002d1210(EEContext&);
void fn_sub_2D1210_002d1210__recomp(EEContext&);
void fn_sub_2D1A10_002d1a10(EEContext&);
void fn_sub_2D1A10_002d1a10__recomp(EEContext&);
void fn_sub_2D1AC0_002d1ac0(EEContext&);
void fn_sub_2D1AC0_002d1ac0__recomp(EEContext&);
void fn_sub_2D1DE0_002d1de0(EEContext&);
void fn_sub_2D1DE0_002d1de0__recomp(EEContext&);
void fn_sub_2D6620_002d6620(EEContext&);
void fn_sub_2D6620_002d6620__recomp(EEContext&);
void fn_sub_2D79A0_002d79a0(EEContext&);
void fn_sub_2D79A0_002d79a0__recomp(EEContext&);
void fn_sub_2DAA20_002daa20(EEContext&);
void fn_sub_2DAA20_002daa20__recomp(EEContext&);
void fn_sub_2DAD00_002dad00(EEContext&);
void fn_sub_2DAD00_002dad00__recomp(EEContext&);
void fn_sub_2DAE30_002dae30(EEContext&);
void fn_sub_2DAE30_002dae30__recomp(EEContext&);
void fn_sub_2DB6A0_002db6a0(EEContext&);
void fn_sub_2DB6A0_002db6a0__recomp(EEContext&);
void fn_sub_2DB860_002db860(EEContext&);
void fn_sub_2DB860_002db860__recomp(EEContext&);
void fn_sub_2DB960_002db960(EEContext&);
void fn_sub_2DB960_002db960__recomp(EEContext&);
void fn_sub_2DBA80_002dba80(EEContext&);
void fn_sub_2DBA80_002dba80__recomp(EEContext&);
void fn_sub_2DBEB0_002dbeb0(EEContext&);
void fn_sub_2DBEB0_002dbeb0__recomp(EEContext&);
void fn_sub_2DCD30_002dcd30(EEContext&);
void fn_sub_2DCD30_002dcd30__recomp(EEContext&);
void fn_sub_2DCED0_002dced0(EEContext&);
void fn_sub_2DCED0_002dced0__recomp(EEContext&);
void fn_sub_2DCF10_002dcf10(EEContext&);
void fn_sub_2DCF10_002dcf10__recomp(EEContext&);
void fn_sub_2DCF80_002dcf80(EEContext&);
void fn_sub_2DCF80_002dcf80__recomp(EEContext&);
void fn_sub_2DD020_002dd020(EEContext&);
void fn_sub_2DD020_002dd020__recomp(EEContext&);
void fn_sub_2DD2F0_002dd2f0(EEContext&);
void fn_sub_2DD2F0_002dd2f0__recomp(EEContext&);
void fn_sub_2DD510_002dd510(EEContext&);
void fn_sub_2DD510_002dd510__recomp(EEContext&);
void fn_sub_2DD630_002dd630(EEContext&);
void fn_sub_2DD630_002dd630__recomp(EEContext&);
void fn_sub_2DDBA0_002ddba0(EEContext&);
void fn_sub_2DDBA0_002ddba0__recomp(EEContext&);
void fn_sub_2DDBE0_002ddbe0(EEContext&);
void fn_sub_2DDBE0_002ddbe0__recomp(EEContext&);
void fn_sub_2DE2A0_002de2a0(EEContext&);
void fn_sub_2DE2A0_002de2a0__recomp(EEContext&);
void fn_sub_2DED60_002ded60(EEContext&);
void fn_sub_2DED60_002ded60__recomp(EEContext&);
void fn_sub_2E1500_002e1500(EEContext&);
void fn_sub_2E1500_002e1500__recomp(EEContext&);
void fn_sub_2E2560_002e2560(EEContext&);
void fn_sub_2E2560_002e2560__recomp(EEContext&);
void fn_sub_2E2D70_002e2d70(EEContext&);
void fn_sub_2E2D70_002e2d70__recomp(EEContext&);
void fn_sub_2E3560_002e3560(EEContext&);
void fn_sub_2E3560_002e3560__recomp(EEContext&);
void fn_sub_2E35A0_002e35a0(EEContext&);
void fn_sub_2E35A0_002e35a0__recomp(EEContext&);
void fn_sub_2E3650_002e3650(EEContext&);
void fn_sub_2E3650_002e3650__recomp(EEContext&);
void fn_sub_2E3740_002e3740(EEContext&);
void fn_sub_2E3740_002e3740__recomp(EEContext&);
void fn_sub_2E3830_002e3830(EEContext&);
void fn_sub_2E3830_002e3830__recomp(EEContext&);
void fn_sub_2E3870_002e3870(EEContext&);
void fn_sub_2E3870_002e3870__recomp(EEContext&);
void fn_sub_2E3900_002e3900(EEContext&);
void fn_sub_2E3900_002e3900__recomp(EEContext&);
void fn_sub_2E39E0_002e39e0(EEContext&);
void fn_sub_2E39E0_002e39e0__recomp(EEContext&);
void fn_sub_2E3B20_002e3b20(EEContext&);
void fn_sub_2E3B20_002e3b20__recomp(EEContext&);
void fn_sub_2E3BE0_002e3be0(EEContext&);
void fn_sub_2E3BE0_002e3be0__recomp(EEContext&);
void fn_sub_2F8FD0_002f8fd0(EEContext&);
void fn_sub_2F8FD0_002f8fd0__recomp(EEContext&);
void fn_sub_2F9B60_002f9b60(EEContext&);
void fn_sub_2F9B60_002f9b60__recomp(EEContext&);
void fn_sub_2F9C10_002f9c10(EEContext&);
void fn_sub_2F9C10_002f9c10__recomp(EEContext&);
void fn_sub_2FA240_002fa240(EEContext&);
void fn_sub_2FA240_002fa240__recomp(EEContext&);
void fn_sub_2FAA50_002faa50(EEContext&);
void fn_sub_2FAA50_002faa50__recomp(EEContext&);
void fn_sub_2FAAB0_002faab0(EEContext&);
void fn_sub_2FAAB0_002faab0__recomp(EEContext&);
void fn_sub_2FD520_002fd520(EEContext&);
void fn_sub_2FD520_002fd520__recomp(EEContext&);
void fn_sub_2FD660_002fd660(EEContext&);
void fn_sub_2FD660_002fd660__recomp(EEContext&);
void fn_sub_2FDE40_002fde40(EEContext&);
void fn_sub_2FDE40_002fde40__recomp(EEContext&);
void fn_sub_2FED10_002fed10(EEContext&);
void fn_sub_2FED10_002fed10__recomp(EEContext&);
void fn_datGetFlag_0016f190(EEContext&);
void fn_sub_17D800_0017d800(EEContext&);
void fn_sub_2B6DE0_002b6de0(EEContext&);
void fn_datCalcIsDead_0030b5a0(EEContext&);
void fn_datCalcIsHpSkill_002d6370(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3, then $t0..$t2) -----------------------------------------
// A btlAction   U btlUnit   D unit packet data {unit, u16 major, u16 minor, flags, request}   E damage packet data
// {source, action, HP, SP, set, clear, extra, ..., u16 +34 / +38 flags}   T turn packet data {unit, target unit,
// flags, frames}   Y placement packet data (+0 / +36 units, +16 flags, +24 first frame, +28 push)   N navigator line
// data {action, u16 line, args, flags, result}   S navigator load data (u16 +4 navigator, +6 step)   R named sound
// data {u16 channel, name}   K skill sound data {frames, u16 skill, u16 step, request}   O step sound data (u16 kind
// 0 / 1)   P packet data (64 random small bytes)   L a bp_list record   H a sprite sheet (+260 textures, +388 cells)
// Q a camera shot (+224 action, +256 target, +236 path)   Z a camera path {unit, unit, ..., u16 key, frame, flags,
// key table}   V a vertex job {&&vertices, u, v, work, index}   W a light fade record   X a script task (+60 the flash
// state)   J an object block (+1536 a block, +1540 flags)   B a persona sequence start block {owner, u16 persona}
// G persona id   M mesh kind 0 / 1   g 0..12   r an action's AI record (+136)   k skill   e element   l a navigator
// line 0..40   u uid   m motion   n small 0..7   c a sheet cell 0..3   p a frame piece 0..7   f flags   F frames
// o out buffer   v f32[3]   t a short text   z zero
struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};
const Case kCases[] = {
    {"sub_242CC0", 0x242CC0u, &rg::fn_sub_242CC0_00242cc0, &rg::fn_sub_242CC0_00242cc0__recomp, ""},
    {"sub_2441B0", 0x2441B0u, &rg::fn_sub_2441B0_002441b0, &rg::fn_sub_2441B0_002441b0__recomp, "n"},
    {"sub_244770", 0x244770u, &rg::fn_sub_244770_00244770, &rg::fn_sub_244770_00244770__recomp, ""},
    {"sub_244A00", 0x244A00u, &rg::fn_sub_244A00_00244a00, &rg::fn_sub_244A00_00244a00__recomp, ""},
    {"sub_244A40", 0x244A40u, &rg::fn_sub_244A40_00244a40, &rg::fn_sub_244A40_00244a40__recomp, "u"},
    {"sub_248500", 0x248500u, &rg::fn_sub_248500_00248500, &rg::fn_sub_248500_00248500__recomp, "t"},
    {"sub_248F40", 0x248F40u, &rg::fn_sub_248F40_00248f40, &rg::fn_sub_248F40_00248f40__recomp, "t"},
    {"sub_249250", 0x249250u, &rg::fn_sub_249250_00249250, &rg::fn_sub_249250_00249250__recomp, ""},
    {"sub_2492B0", 0x2492B0u, &rg::fn_sub_2492B0_002492b0, &rg::fn_sub_2492B0_002492b0__recomp, ""},
    {"sub_249690", 0x249690u, &rg::fn_sub_249690_00249690, &rg::fn_sub_249690_00249690__recomp, "J"},
    {"sub_24A230", 0x24A230u, &rg::fn_sub_24A230_0024a230, &rg::fn_sub_24A230_0024a230__recomp, "oo"},
    {"sub_24A260", 0x24A260u, &rg::fn_sub_24A260_0024a260, &rg::fn_sub_24A260_0024a260__recomp, "L"},
    {"sub_24A630", 0x24A630u, &rg::fn_sub_24A630_0024a630, &rg::fn_sub_24A630_0024a630__recomp, "Ln"},
    {"sub_24CCA0", 0x24CCA0u, &rg::fn_sub_24CCA0_0024cca0, &rg::fn_sub_24CCA0_0024cca0__recomp, ""},
    {"sub_25B690", 0x25B690u, &rg::fn_sub_25B690_0025b690, &rg::fn_sub_25B690_0025b690__recomp, ""},
    {"sub_25C220", 0x25C220u, &rg::fn_sub_25C220_0025c220, &rg::fn_sub_25C220_0025c220__recomp, ""},
    {"sub_25CF20", 0x25CF20u, &rg::fn_sub_25CF20_0025cf20, &rg::fn_sub_25CF20_0025cf20__recomp, ""},
    {"sub_25D020", 0x25D020u, &rg::fn_sub_25D020_0025d020, &rg::fn_sub_25D020_0025d020__recomp, ""},
    {"sub_25D130", 0x25D130u, &rg::fn_sub_25D130_0025d130, &rg::fn_sub_25D130_0025d130__recomp, ""},
    {"sub_25D470", 0x25D470u, &rg::fn_sub_25D470_0025d470, &rg::fn_sub_25D470_0025d470__recomp, ""},
    {"sub_25F5D0", 0x25F5D0u, &rg::fn_sub_25F5D0_0025f5d0, &rg::fn_sub_25F5D0_0025f5d0__recomp, "oHc"},
    {"sub_25FC50", 0x25FC50u, &rg::fn_sub_25FC50_0025fc50, &rg::fn_sub_25FC50_0025fc50__recomp, "oHcp"},
    {"sub_260430", 0x260430u, &rg::fn_sub_260430_00260430, &rg::fn_sub_260430_00260430__recomp, "Hcop"},
    {"sub_260D20", 0x260D20u, &rg::fn_sub_260D20_00260d20, &rg::fn_sub_260D20_00260d20__recomp, ""},
    {"sub_260E00", 0x260E00u, &rg::fn_sub_260E00_00260e00, &rg::fn_sub_260E00_00260e00__recomp, ""},
    {"sub_262730", 0x262730u, &rg::fn_sub_262730_00262730, &rg::fn_sub_262730_00262730__recomp, ""},
    {"sub_2630E0", 0x2630E0u, &rg::fn_sub_2630E0_002630e0, &rg::fn_sub_2630E0_002630e0__recomp, ""},
    {"sub_264DD0", 0x264DD0u, &rg::fn_sub_264DD0_00264dd0, &rg::fn_sub_264DD0_00264dd0__recomp, ""},
    {"sub_264E30", 0x264E30u, &rg::fn_sub_264E30_00264e30, &rg::fn_sub_264E30_00264e30__recomp, "G"},
    {"sub_264F90", 0x264F90u, &rg::fn_sub_264F90_00264f90, &rg::fn_sub_264F90_00264f90__recomp, ""},
    {"sub_264FF0", 0x264FF0u, &rg::fn_sub_264FF0_00264ff0, &rg::fn_sub_264FF0_00264ff0__recomp, ""},
    {"sub_265C20", 0x265C20u, &rg::fn_sub_265C20_00265c20, &rg::fn_sub_265C20_00265c20__recomp, "z"},
    {"sub_265EF0", 0x265EF0u, &rg::fn_sub_265EF0_00265ef0, &rg::fn_sub_265EF0_00265ef0__recomp, "z"},
    {"sub_266710", 0x266710u, &rg::fn_sub_266710_00266710, &rg::fn_sub_266710_00266710__recomp, ""},
    {"sub_266EB0", 0x266EB0u, &rg::fn_sub_266EB0_00266eb0, &rg::fn_sub_266EB0_00266eb0__recomp, "o"},
    {"sub_266F00", 0x266F00u, &rg::fn_sub_266F00_00266f00, &rg::fn_sub_266F00_00266f00__recomp, ""},
    {"sub_267180", 0x267180u, &rg::fn_sub_267180_00267180, &rg::fn_sub_267180_00267180__recomp, ""},
    {"sub_267260", 0x267260u, &rg::fn_sub_267260_00267260, &rg::fn_sub_267260_00267260__recomp, ""},
    {"sub_267370", 0x267370u, &rg::fn_sub_267370_00267370, &rg::fn_sub_267370_00267370__recomp, "n"},
    {"sub_267390", 0x267390u, &rg::fn_sub_267390_00267390, &rg::fn_sub_267390_00267390__recomp, ""},
    {"sub_268E20", 0x268E20u, &rg::fn_sub_268E20_00268e20, &rg::fn_sub_268E20_00268e20__recomp, ""},
    {"sub_269690", 0x269690u, &rg::fn_sub_269690_00269690, &rg::fn_sub_269690_00269690__recomp, "Mgg"},
    {"sub_26C710", 0x26C710u, &rg::fn_sub_26C710_0026c710, &rg::fn_sub_26C710_0026c710__recomp, ""},
    {"sub_26CC90", 0x26CC90u, &rg::fn_sub_26CC90_0026cc90, &rg::fn_sub_26CC90_0026cc90__recomp, ""},
    {"sub_26E000", 0x26E000u, &rg::fn_sub_26E000_0026e000, &rg::fn_sub_26E000_0026e000__recomp, ""},
    {"sub_271230", 0x271230u, &rg::fn_sub_271230_00271230, &rg::fn_sub_271230_00271230__recomp, "V"},
    {"sub_2716D0", 0x2716D0u, &rg::fn_sub_2716D0_002716d0, &rg::fn_sub_2716D0_002716d0__recomp, "V"},
    {"sub_271C10", 0x271C10u, &rg::fn_sub_271C10_00271c10, &rg::fn_sub_271C10_00271c10__recomp, ""},
    {"sub_271CD0", 0x271CD0u, &rg::fn_sub_271CD0_00271cd0, &rg::fn_sub_271CD0_00271cd0__recomp, "o"},
    {"sub_271D70", 0x271D70u, &rg::fn_sub_271D70_00271d70, &rg::fn_sub_271D70_00271d70__recomp, ""},
    {"sub_271DB0", 0x271DB0u, &rg::fn_sub_271DB0_00271db0, &rg::fn_sub_271DB0_00271db0__recomp, ""},
    {"sub_271E10", 0x271E10u, &rg::fn_sub_271E10_00271e10, &rg::fn_sub_271E10_00271e10__recomp, ""},
    {"sub_271E70", 0x271E70u, &rg::fn_sub_271E70_00271e70, &rg::fn_sub_271E70_00271e70__recomp, ""},
    {"sub_271EC0", 0x271EC0u, &rg::fn_sub_271EC0_00271ec0, &rg::fn_sub_271EC0_00271ec0__recomp, ""},
    {"sub_2721D0", 0x2721D0u, &rg::fn_sub_2721D0_002721d0, &rg::fn_sub_2721D0_002721d0__recomp, "F"},
    {"sub_272220", 0x272220u, &rg::fn_sub_272220_00272220, &rg::fn_sub_272220_00272220__recomp, "o"},
    {"sub_272290", 0x272290u, &rg::fn_sub_272290_00272290, &rg::fn_sub_272290_00272290__recomp, ""},
    {"sub_2722E0", 0x2722E0u, &rg::fn_sub_2722E0_002722e0, &rg::fn_sub_2722E0_002722e0__recomp, ""},
    {"sub_272380", 0x272380u, &rg::fn_sub_272380_00272380, &rg::fn_sub_272380_00272380__recomp, ""},
    {"sub_272400", 0x272400u, &rg::fn_sub_272400_00272400, &rg::fn_sub_272400_00272400__recomp, "B"},
    {"sub_2727C0", 0x2727C0u, &rg::fn_sub_2727C0_002727c0, &rg::fn_sub_2727C0_002727c0__recomp, ""},
    {"sub_273800", 0x273800u, &rg::fn_sub_273800_00273800, &rg::fn_sub_273800_00273800__recomp, ""},
    {"sub_273A10", 0x273A10u, &rg::fn_sub_273A10_00273a10, &rg::fn_sub_273A10_00273a10__recomp, ""},
    {"sub_273B30", 0x273B30u, &rg::fn_sub_273B30_00273b30, &rg::fn_sub_273B30_00273b30__recomp, ""},
    {"sub_273E90", 0x273E90u, &rg::fn_sub_273E90_00273e90, &rg::fn_sub_273E90_00273e90__recomp, ""},
    {"sub_2741F0", 0x2741F0u, &rg::fn_sub_2741F0_002741f0, &rg::fn_sub_2741F0_002741f0__recomp, ""},
    {"sub_2743A0", 0x2743A0u, &rg::fn_sub_2743A0_002743a0, &rg::fn_sub_2743A0_002743a0__recomp, ""},
    {"sub_2743E0", 0x2743E0u, &rg::fn_sub_2743E0_002743e0, &rg::fn_sub_2743E0_002743e0__recomp, "oo"},
    {"sub_274590", 0x274590u, &rg::fn_sub_274590_00274590, &rg::fn_sub_274590_00274590__recomp, ""},
    {"sub_274C00", 0x274C00u, &rg::fn_sub_274C00_00274c00, &rg::fn_sub_274C00_00274c00__recomp, ""},
    {"sub_274F00", 0x274F00u, &rg::fn_sub_274F00_00274f00, &rg::fn_sub_274F00_00274f00__recomp, ""},
    {"sub_275050", 0x275050u, &rg::fn_sub_275050_00275050, &rg::fn_sub_275050_00275050__recomp, "n"},
    {"sub_2751E0", 0x2751E0u, &rg::fn_sub_2751E0_002751e0, &rg::fn_sub_2751E0_002751e0__recomp, ""},
    {"sub_275370", 0x275370u, &rg::fn_sub_275370_00275370, &rg::fn_sub_275370_00275370__recomp, ""},
    {"sub_2753C0", 0x2753C0u, &rg::fn_sub_2753C0_002753c0, &rg::fn_sub_2753C0_002753c0__recomp, ""},
    {"sub_275A80", 0x275A80u, &rg::fn_sub_275A80_00275a80, &rg::fn_sub_275A80_00275a80__recomp, ""},
    {"sub_275CB0", 0x275CB0u, &rg::fn_sub_275CB0_00275cb0, &rg::fn_sub_275CB0_00275cb0__recomp, ""},
    {"sub_2767E0", 0x2767E0u, &rg::fn_sub_2767E0_002767e0, &rg::fn_sub_2767E0_002767e0__recomp, ""},
    {"sub_276920", 0x276920u, &rg::fn_sub_276920_00276920, &rg::fn_sub_276920_00276920__recomp, ""},
    {"sub_276930", 0x276930u, &rg::fn_sub_276930_00276930, &rg::fn_sub_276930_00276930__recomp, ""},
    {"sub_2769C0", 0x2769C0u, &rg::fn_sub_2769C0_002769c0, &rg::fn_sub_2769C0_002769c0__recomp, "JG"},
    {"sub_276BA0", 0x276BA0u, &rg::fn_sub_276BA0_00276ba0, &rg::fn_sub_276BA0_00276ba0__recomp, ""},
    {"sub_276D30", 0x276D30u, &rg::fn_sub_276D30_00276d30, &rg::fn_sub_276D30_00276d30__recomp, ""},
    {"sub_276D90", 0x276D90u, &rg::fn_sub_276D90_00276d90, &rg::fn_sub_276D90_00276d90__recomp, ""},
    {"sub_277070", 0x277070u, &rg::fn_sub_277070_00277070, &rg::fn_sub_277070_00277070__recomp, ""},
    {"sub_2770F0", 0x2770F0u, &rg::fn_sub_2770F0_002770f0, &rg::fn_sub_2770F0_002770f0__recomp, ""},
    {"sub_279120", 0x279120u, &rg::fn_sub_279120_00279120, &rg::fn_sub_279120_00279120__recomp, ""},
    {"sub_2791B0", 0x2791B0u, &rg::fn_sub_2791B0_002791b0, &rg::fn_sub_2791B0_002791b0__recomp, "k"},
    {"sub_2792C0", 0x2792C0u, &rg::fn_sub_2792C0_002792c0, &rg::fn_sub_2792C0_002792c0__recomp, ""},
    {"sub_279330", 0x279330u, &rg::fn_sub_279330_00279330, &rg::fn_sub_279330_00279330__recomp, "k"},
    {"sub_279660", 0x279660u, &rg::fn_sub_279660_00279660, &rg::fn_sub_279660_00279660__recomp, ""},
    {"sub_27B5B0", 0x27B5B0u, &rg::fn_sub_27B5B0_0027b5b0, &rg::fn_sub_27B5B0_0027b5b0__recomp, "o"},
    {"sub_27B5D0", 0x27B5D0u, &rg::fn_sub_27B5D0_0027b5d0, &rg::fn_sub_27B5D0_0027b5d0__recomp, ""},
    {"sub_27BBA0", 0x27BBA0u, &rg::fn_sub_27BBA0_0027bba0, &rg::fn_sub_27BBA0_0027bba0__recomp, ""},
    {"sub_27BE50", 0x27BE50u, &rg::fn_sub_27BE50_0027be50, &rg::fn_sub_27BE50_0027be50__recomp, ""},
    {"sub_27F940", 0x27F940u, &rg::fn_sub_27F940_0027f940, &rg::fn_sub_27F940_0027f940__recomp, "UUUmoon"},
    {"sub_2802D0", 0x2802D0u, &rg::fn_sub_2802D0_002802d0, &rg::fn_sub_2802D0_002802d0__recomp, "UUo"},
    {"sub_280390", 0x280390u, &rg::fn_sub_280390_00280390, &rg::fn_sub_280390_00280390__recomp, "UUo"},
    {"sub_280480", 0x280480u, &rg::fn_sub_280480_00280480, &rg::fn_sub_280480_00280480__recomp, "UUo"},
    {"sub_280DA0", 0x280DA0u, &rg::fn_sub_280DA0_00280da0, &rg::fn_sub_280DA0_00280da0__recomp, "U"},
    {"sub_281AD0", 0x281AD0u, &rg::fn_sub_281AD0_00281ad0, &rg::fn_sub_281AD0_00281ad0__recomp, "Y"},
    {"sub_2823B0", 0x2823B0u, &rg::fn_sub_2823B0_002823b0, &rg::fn_sub_2823B0_002823b0__recomp, "T"},
    {"sub_2826D0", 0x2826D0u, &rg::fn_sub_2826D0_002826d0, &rg::fn_sub_2826D0_002826d0__recomp, "U"},
    {"sub_2831C0", 0x2831C0u, &rg::fn_sub_2831C0_002831c0, &rg::fn_sub_2831C0_002831c0__recomp, "Un"},
    {"sub_284E10", 0x284E10u, &rg::fn_sub_284E10_00284e10, &rg::fn_sub_284E10_00284e10__recomp, "D"},
    {"sub_2850F0", 0x2850F0u, &rg::fn_sub_2850F0_002850f0, &rg::fn_sub_2850F0_002850f0__recomp, "D"},
    {"sub_285750", 0x285750u, &rg::fn_sub_285750_00285750, &rg::fn_sub_285750_00285750__recomp, "D"},
    {"sub_287740", 0x287740u, &rg::fn_sub_287740_00287740, &rg::fn_sub_287740_00287740__recomp, "U"},
    {"sub_2878D0", 0x2878D0u, &rg::fn_sub_2878D0_002878d0, &rg::fn_sub_2878D0_002878d0__recomp, "U"},
    {"sub_289B50", 0x289B50u, &rg::fn_sub_289B50_00289b50, &rg::fn_sub_289B50_00289b50__recomp, "A"},
    {"sub_28CDA0", 0x28CDA0u, &rg::fn_sub_28CDA0_0028cda0, &rg::fn_sub_28CDA0_0028cda0__recomp, "A"},
    {"sub_28D5A0", 0x28D5A0u, &rg::fn_sub_28D5A0_0028d5a0, &rg::fn_sub_28D5A0_0028d5a0__recomp, "A"},
    {"sub_28DBF0", 0x28DBF0u, &rg::fn_sub_28DBF0_0028dbf0, &rg::fn_sub_28DBF0_0028dbf0__recomp, "A"},
    {"sub_297A60", 0x297A60u, &rg::fn_sub_297A60_00297a60, &rg::fn_sub_297A60_00297a60__recomp, "A"},
    {"sub_2984E0", 0x2984E0u, &rg::fn_sub_2984E0_002984e0, &rg::fn_sub_2984E0_002984e0__recomp, "A"},
    {"sub_299270", 0x299270u, &rg::fn_sub_299270_00299270, &rg::fn_sub_299270_00299270__recomp, "A"},
    {"sub_299B00", 0x299B00u, &rg::fn_sub_299B00_00299b00, &rg::fn_sub_299B00_00299b00__recomp, "A"},
    {"sub_29DFC0", 0x29DFC0u, &rg::fn_sub_29DFC0_0029dfc0, &rg::fn_sub_29DFC0_0029dfc0__recomp, ""},
    {"sub_29EE20", 0x29EE20u, &rg::fn_sub_29EE20_0029ee20, &rg::fn_sub_29EE20_0029ee20__recomp, "U"},
    {"sub_29FAA0", 0x29FAA0u, &rg::fn_sub_29FAA0_0029faa0, &rg::fn_sub_29FAA0_0029faa0__recomp, "W"},
    {"sub_2A46E0", 0x2A46E0u, &rg::fn_sub_2A46E0_002a46e0, &rg::fn_sub_2A46E0_002a46e0__recomp, ""},
    {"sub_2A4C70", 0x2A4C70u, &rg::fn_sub_2A4C70_002a4c70, &rg::fn_sub_2A4C70_002a4c70__recomp, "Q"},
    {"sub_2A5430", 0x2A5430u, &rg::fn_sub_2A5430_002a5430, &rg::fn_sub_2A5430_002a5430__recomp, "Q"},
    {"sub_2AD680", 0x2AD680u, &rg::fn_sub_2AD680_002ad680, &rg::fn_sub_2AD680_002ad680__recomp, "Q"},
    {"sub_2AE150", 0x2AE150u, &rg::fn_sub_2AE150_002ae150, &rg::fn_sub_2AE150_002ae150__recomp, "Q"},
    {"sub_2B2060", 0x2B2060u, &rg::fn_sub_2B2060_002b2060, &rg::fn_sub_2B2060_002b2060__recomp, "Q"},
    {"sub_2B58F0", 0x2B58F0u, &rg::fn_sub_2B58F0_002b58f0, &rg::fn_sub_2B58F0_002b58f0__recomp, "Q"},
    {"sub_2B64D0", 0x2B64D0u, &rg::fn_sub_2B64D0_002b64d0, &rg::fn_sub_2B64D0_002b64d0__recomp, "QZ"},
    {"sub_2B7060", 0x2B7060u, &rg::fn_sub_2B7060_002b7060, &rg::fn_sub_2B7060_002b7060__recomp, ""},
    {"sub_2B71E0", 0x2B71E0u, &rg::fn_sub_2B71E0_002b71e0, &rg::fn_sub_2B71E0_002b71e0__recomp, ""},
    {"sub_2C6300", 0x2C6300u, &rg::fn_sub_2C6300_002c6300, &rg::fn_sub_2C6300_002c6300__recomp, "Aren"},
    {"sub_2D1210", 0x2D1210u, &rg::fn_sub_2D1210_002d1210, &rg::fn_sub_2D1210_002d1210__recomp, ""},
    {"sub_2D1A10", 0x2D1A10u, &rg::fn_sub_2D1A10_002d1a10, &rg::fn_sub_2D1A10_002d1a10__recomp, ""},
    {"sub_2D1AC0", 0x2D1AC0u, &rg::fn_sub_2D1AC0_002d1ac0, &rg::fn_sub_2D1AC0_002d1ac0__recomp, ""},
    {"sub_2D1DE0", 0x2D1DE0u, &rg::fn_sub_2D1DE0_002d1de0, &rg::fn_sub_2D1DE0_002d1de0__recomp, "ovv"},
    {"sub_2D6620", 0x2D6620u, &rg::fn_sub_2D6620_002d6620, &rg::fn_sub_2D6620_002d6620__recomp, "A"},
    {"sub_2D79A0", 0x2D79A0u, &rg::fn_sub_2D79A0_002d79a0, &rg::fn_sub_2D79A0_002d79a0__recomp, "E"},
    {"sub_2DAA20", 0x2DAA20u, &rg::fn_sub_2DAA20_002daa20, &rg::fn_sub_2DAA20_002daa20__recomp, "Alnnf"},
    {"sub_2DAD00", 0x2DAD00u, &rg::fn_sub_2DAD00_002dad00, &rg::fn_sub_2DAD00_002dad00__recomp, ""},
    {"sub_2DAE30", 0x2DAE30u, &rg::fn_sub_2DAE30_002dae30, &rg::fn_sub_2DAE30_002dae30__recomp, "n"},
    {"sub_2DB6A0", 0x2DB6A0u, &rg::fn_sub_2DB6A0_002db6a0, &rg::fn_sub_2DB6A0_002db6a0__recomp, "N"},
    {"sub_2DB860", 0x2DB860u, &rg::fn_sub_2DB860_002db860, &rg::fn_sub_2DB860_002db860__recomp, "P"},
    {"sub_2DB960", 0x2DB960u, &rg::fn_sub_2DB960_002db960, &rg::fn_sub_2DB960_002db960__recomp, ""},
    {"sub_2DBA80", 0x2DBA80u, &rg::fn_sub_2DBA80_002dba80, &rg::fn_sub_2DBA80_002dba80__recomp, ""},
    {"sub_2DBEB0", 0x2DBEB0u, &rg::fn_sub_2DBEB0_002dbeb0, &rg::fn_sub_2DBEB0_002dbeb0__recomp, "S"},
    {"sub_2DCD30", 0x2DCD30u, &rg::fn_sub_2DCD30_002dcd30, &rg::fn_sub_2DCD30_002dcd30__recomp, ""},
    {"sub_2DCED0", 0x2DCED0u, &rg::fn_sub_2DCED0_002dced0, &rg::fn_sub_2DCED0_002dced0__recomp, "n"},
    {"sub_2DCF10", 0x2DCF10u, &rg::fn_sub_2DCF10_002dcf10, &rg::fn_sub_2DCF10_002dcf10__recomp, ""},
    {"sub_2DCF80", 0x2DCF80u, &rg::fn_sub_2DCF80_002dcf80, &rg::fn_sub_2DCF80_002dcf80__recomp, "nn"},
    {"sub_2DD020", 0x2DD020u, &rg::fn_sub_2DD020_002dd020, &rg::fn_sub_2DD020_002dd020__recomp, "P"},
    {"sub_2DD2F0", 0x2DD2F0u, &rg::fn_sub_2DD2F0_002dd2f0, &rg::fn_sub_2DD2F0_002dd2f0__recomp, "K"},
    {"sub_2DD510", 0x2DD510u, &rg::fn_sub_2DD510_002dd510, &rg::fn_sub_2DD510_002dd510__recomp, "O"},
    {"sub_2DD630", 0x2DD630u, &rg::fn_sub_2DD630_002dd630, &rg::fn_sub_2DD630_002dd630__recomp, "R"},
    {"sub_2DDBA0", 0x2DDBA0u, &rg::fn_sub_2DDBA0_002ddba0, &rg::fn_sub_2DDBA0_002ddba0__recomp, "n"},
    {"sub_2DDBE0", 0x2DDBE0u, &rg::fn_sub_2DDBE0_002ddbe0, &rg::fn_sub_2DDBE0_002ddbe0__recomp, ""},
    {"sub_2DE2A0", 0x2DE2A0u, &rg::fn_sub_2DE2A0_002de2a0, &rg::fn_sub_2DE2A0_002de2a0__recomp, "A"},
    {"sub_2DED60", 0x2DED60u, &rg::fn_sub_2DED60_002ded60, &rg::fn_sub_2DED60_002ded60__recomp, "A"},
    {"sub_2E1500", 0x2E1500u, &rg::fn_sub_2E1500_002e1500, &rg::fn_sub_2E1500_002e1500__recomp, "Ag"},
    {"sub_2E2560", 0x2E2560u, &rg::fn_sub_2E2560_002e2560, &rg::fn_sub_2E2560_002e2560__recomp, "A"},
    {"sub_2E2D70", 0x2E2D70u, &rg::fn_sub_2E2D70_002e2d70, &rg::fn_sub_2E2D70_002e2d70__recomp, "P"},
    {"sub_2E3560", 0x2E3560u, &rg::fn_sub_2E3560_002e3560, &rg::fn_sub_2E3560_002e3560__recomp, "P"},
    {"sub_2E35A0", 0x2E35A0u, &rg::fn_sub_2E35A0_002e35a0, &rg::fn_sub_2E35A0_002e35a0__recomp, ""},
    {"sub_2E3650", 0x2E3650u, &rg::fn_sub_2E3650_002e3650, &rg::fn_sub_2E3650_002e3650__recomp, "P"},
    {"sub_2E3740", 0x2E3740u, &rg::fn_sub_2E3740_002e3740, &rg::fn_sub_2E3740_002e3740__recomp, "P"},
    {"sub_2E3830", 0x2E3830u, &rg::fn_sub_2E3830_002e3830, &rg::fn_sub_2E3830_002e3830__recomp, "P"},
    {"sub_2E3870", 0x2E3870u, &rg::fn_sub_2E3870_002e3870, &rg::fn_sub_2E3870_002e3870__recomp, ""},
    {"sub_2E3900", 0x2E3900u, &rg::fn_sub_2E3900_002e3900, &rg::fn_sub_2E3900_002e3900__recomp, "P"},
    {"sub_2E39E0", 0x2E39E0u, &rg::fn_sub_2E39E0_002e39e0, &rg::fn_sub_2E39E0_002e39e0__recomp, "P"},
    {"sub_2E3B20", 0x2E3B20u, &rg::fn_sub_2E3B20_002e3b20, &rg::fn_sub_2E3B20_002e3b20__recomp, ""},
    {"sub_2E3BE0", 0x2E3BE0u, &rg::fn_sub_2E3BE0_002e3be0, &rg::fn_sub_2E3BE0_002e3be0__recomp, "P"},
    {"sub_2F8FD0", 0x2F8FD0u, &rg::fn_sub_2F8FD0_002f8fd0, &rg::fn_sub_2F8FD0_002f8fd0__recomp, "Uk"},
    {"sub_2F9B60", 0x2F9B60u, &rg::fn_sub_2F9B60_002f9b60, &rg::fn_sub_2F9B60_002f9b60__recomp, ""},
    {"sub_2F9C10", 0x2F9C10u, &rg::fn_sub_2F9C10_002f9c10, &rg::fn_sub_2F9C10_002f9c10__recomp, "A"},
    {"sub_2FA240", 0x2FA240u, &rg::fn_sub_2FA240_002fa240, &rg::fn_sub_2FA240_002fa240__recomp, ""},
    {"sub_2FAA50", 0x2FAA50u, &rg::fn_sub_2FAA50_002faa50, &rg::fn_sub_2FAA50_002faa50__recomp, ""},
    {"sub_2FAAB0", 0x2FAAB0u, &rg::fn_sub_2FAAB0_002faab0, &rg::fn_sub_2FAAB0_002faab0__recomp, ""},
    {"sub_2FD520", 0x2FD520u, &rg::fn_sub_2FD520_002fd520, &rg::fn_sub_2FD520_002fd520__recomp, "U"},
    {"sub_2FD660", 0x2FD660u, &rg::fn_sub_2FD660_002fd660, &rg::fn_sub_2FD660_002fd660__recomp, ""},
    {"sub_2FDE40", 0x2FDE40u, &rg::fn_sub_2FDE40_002fde40, &rg::fn_sub_2FDE40_002fde40__recomp, ""},
    {"sub_2FED10", 0x2FED10u, &rg::fn_sub_2FED10_002fed10, &rg::fn_sub_2FED10_002fed10__recomp, "X"},
};

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 8)); }
void st8(Machine& m, u32 va, u8 v) { *ram(m, va) = v; }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(ram(m, va), &v, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(ram(m, va), &v, 4); }
void stf(Machine& m, u32 va, float v) { std::memcpy(ram(m, va), &v, 4); }
u8 ld8(Machine& m, u32 va) { return *ram(m, va); }
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, ram(m, va), 2);
    return v;
}
u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }
bool in_ram(u32 va) { return va >= 0x100000u && va < 0x2000000u; }

constexpr u32 kGpVa = 0x7D2CF0u;
constexpr u32 kGBtlSlot = 0x7CE3ECu;
// The address of a $gp slot (its signed offset from $gp).
u32 gp(s32 off) { return kGpVa + static_cast<u32>(off); }
// Free guest memory for the blocks a test builds (zero in every replay snapshot; the stand-in heap allocates from
// kStandInHeap upwards and never gets this far in these pairs).
constexpr u32 kScratch = kStandInHeap + 0x2C0000u;

// The stand-ins: heap, printf, sprintf, H_Cdvd, and recorders for the callees the test build does not emit that the
// bodies reach on the battle worlds (both bodies meet the same recorder; its log is compared).
const u32 kRecorded[] = {0x324BD0u, 0x2E3AE0u, 0x2DCFB0u, 0x242600u, 0x2B94F0u, 0x316F70u, 0x4F7560u, 0x242720u, 0x25BE60u,
                         // the sound layer below the bodies' sound requests (sub_10A4E0 and the sound driver entries)
                         0x51DF58u, 0x51E028u, 0x108FD0u, 0x109180u, 0x109F60u, 0x10A100u, 0x10A720u, 0x1099D0u, 0x10A370u,
                         0x109AE0u, 0x109DF0u,
                         // the light / camera / RW callees, the font / texture loaders, the message window and status tasks
                         0x1A0700u, 0x1A07F0u, 0x1A4580u, 0x4C9D70u, 0x4DD2E0u, 0x20F9A0u, 0x21EC40u, 0x3A2D80u, 0x3B7090u,
                         0x3C77A0u, 0x3C7BC0u, 0x3C8F70u, 0x3C9850u, 0x3C9AB0u, 0x3C9D00u, 0x3170C0u, 0x31C820u,
                         // still-recompiled battle callees (other slices' stand-ins included: recorders here never take them)
                         0x245EA0u, 0x267120u, 0x274030u, 0x2813F0u, 0x282D40u, 0x288110u, 0x28DF00u, 0x2B6460u,
                         // the navigator line pickers (the table 0x6978F0) and the boss handlers by encounter
                         0x2D8610u, 0x2D8780u, 0x2D87E0u, 0x2D89E0u, 0x2D8CF0u, 0x2D8DC0u, 0x2D8E80u, 0x2D9B20u, 0x2DA810u,
                         0x2DA930u, 0x2E97E0u, 0x2EAA40u, 0x2EC190u, 0x2EF9D0u, 0x2EFB40u,
                         // more of the same kinds (the second round of the snapshot pairs' stops)
                         0x108F70u, 0x1A08E0u, 0x20F570u, 0x21C9F0u, 0x21CC20u, 0x3C8230u, 0x491EA0u};
void b5_setup(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "rec_" + hex64(va), 0, 4);
}

// --- stand-ins and the pair -----------------------------------------------------------------------------------------
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
// hgp::pair (everything at every check point, the end / stop, all RAM, scratchpad, BIOS, bus) with a fresh stand-in
// world around each body and the two call logs compared. Returns the recompiled run.
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b5_setup(*wh);
    b5_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// hgp::pair's comparison on a long-lived BaseRange (write_tracker.h) instead of a PairRange per pair: the snapshot
// world's 32 MiB stay the base and restore() copies back only the pages a pair wrote. Same checks as hgp::pair.
hgp::Run pair_base(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b5_setup(*wh);
    b5_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
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
    INFO(std::string(what) << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
              << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string())
              << (h.stopped ? " (hand stopped: " + h.what + " at " + hex64(h.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
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
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                                  << unsigned(m.mem.main_ram()[first]));
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
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// One body alone (the rule checks) with its own stand-in world (kept in g_solo for its call log).
std::unique_ptr<StandInWorld> g_solo;
hgp::Run solo(Machine& m, Fn fn, const Args& args, const HwCheck& hw = {}) {
    g_solo = std::make_unique<StandInWorld>();
    b5_setup(*g_solo);
    g_si[0] = g_solo.get();
    g_fn[0] = fn;
    return hgp::run_one(m, &thunk0, args, 1, hw);
}
// The path of the last file-layer request of the solo run ("" when none).
std::string last_request_path() {
    for (auto it = g_solo->si.log.rbegin(); it != g_solo->si.log.rend(); ++it)
        if (it->va == 0x100D80u) return it->text;
    return {};
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

std::unique_ptr<Machine> new_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// --- the battle objects of a snapshot -------------------------------------------------------------------------------
struct Objects {
    u32 btl = 0;
    std::vector<u32> acts, units, dats, data;  // data: the packets' data blocks
    std::vector<u16> ids;
    std::vector<u32> uids;
    std::vector<u32> works;  // the live panel / result screen works ($gp slots), for the flag perturbations
};
// The $gp slots of the panel and result-screen works these bodies read (each work's +0 is its flag word).
const s32 kWorkSlots[] = {b4::kGpBpcWork, b4::kGpBpmWork, b4::kGpBpWork328, b4::kGpBpDialogWork, b4::kGpBpRushWork,
                          b5::kGpBaiWork, b5::kGpSflCount, b5::kGpSflPsel, b5::kGpBrHero, b5::kGpBrPersona,
                          b5::kGpBpPersona, b5::kGpOpTitle, b5::kGpOpMenu, b5::kGpOpWait, b5::kGpOpFade, b5::kGpBrpSeq,
                          b5::kGpBrLvPanel, b5::kGpBrpPersona, b5::kGpBrpParam, b5::kGpSflPersona};
Objects objects_of(Machine& m) {
    Objects o;
    for (s32 slot : kWorkSlots)
        if (const u32 w = ld32(m, gp(slot)); in_ram(w)) o.works.push_back(w);
    o.btl = ld32(m, kGBtlSlot);
    if (!in_ram(o.btl)) {
        o.btl = 0;
        return o;
    }
    for (u32 a = ld32(m, o.btl + b3::gbtl::kActionList), n = 0; in_ram(a) && n < 32; a = ld32(m, a + b3::act::kNext), ++n)
        o.acts.push_back(a);
    for (u32 s = 0; s < 4; ++s)
        for (u32 u = ld32(m, o.btl + b3::gbtl::kUnitHead0 + 8 * s), n = 0; in_ram(u) && n < 32; u = ld32(m, u + b3::unit::kNext), ++n) {
            o.units.push_back(u);
            o.ids.push_back(ld16(m, u + b3::unit::kId));
            o.uids.push_back(ld32(m, u + b3::unit::kUid));
            if (const u32 d = ld32(m, u + b3::unit::kDat); in_ram(d)) o.dats.push_back(d);
        }
    for (u32 q = 0; q < 4; ++q)
        for (u32 p = ld32(m, o.btl + b3::gbtl::kPktHead0 + 8 * q), n = 0; in_ram(p) && n < 64; p = ld32(m, p + b3::pkt::kNext), ++n)
            if (const u32 d = ld32(m, p + b3::pkt::kData); in_ram(d)) o.data.push_back(d);
    return o;
}
template <class T>
T pick(const std::vector<T>& v, std::mt19937& rng, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

// The encounters the bodies branch on: the boss fights 416..436 / 456 (and their 0x1A0..0x1B4 hex spelling), the
// music kinds, some plain ones.
const u16 kEncounters[] = {416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434,
                           435, 436, 456, 1, 25, 120, 300, 412, 468, 506};
// The enemy ids the boss rules test (the bosses of 416..436, the reaction rows 149..156).
const u16 kBossIds[] = {149, 150, 153, 156, 241, 242, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 269, 271,
                        272, 273, 278, 279, 280};

// The perturbations of one battle-world pair: the bad-status words and HP of a few DatUnits, the encounter id, a boss
// id on one enemy unit, the gBtl flag bits and navigator / support words the bodies test, the unit walk / model /
// motion words, the works' flag words.
void perturb(Machine& m, const Objects& o, std::mt19937& rng) {
    static const u32 kStatus[] = {0x100000u, 0x80000u, 0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x100u, 0x200u, 0x261u};
    for (u32 d : o.dats) {
        if (chance(rng, 35)) {
            const bool clear = chance(rng, 50);
            const u32 a = kStatus[rng() % 12];
            const bool two = chance(rng, 20);
            const u32 b = kStatus[rng() % 12];
            st32(m, d + b3::dat::kStatus, clear ? 0 : a | (two ? b : 0));
        }
        if (chance(rng, 20)) {
            const bool zero = chance(rng, 30);
            const u32 hp = 1 + rng() % 400;
            st16(m, d + b3::dat::kHp, static_cast<u16>(zero ? 0 : hp));
        }
    }
    for (u32 w : o.works)
        if (chance(rng, 20)) {
            const u32 bits = rng() & 0x1FFu;
            st32(m, w, ld32(m, w) ^ bits);
        }
    // the persona sequence's step (brp_seq.c): 2..5 are the steps sub_273800 walks, others K_Assert and spin
    if (const u32 seq = ld32(m, gp(b5::kGpBrpSeq)); in_ram(seq) && chance(rng, 60)) {
        const u32 step = 1 + rng() % 5;
        st32(m, seq + b5::brpseq::kStep, step);
    }
    if (!o.btl) return;
    if (chance(rng, 45))
        if (const u32 g = ld32(m, o.btl + b3::gbtl::kSetupEnemies); in_ram(g)) {
            const u16 enc = kEncounters[rng() % std::size(kEncounters)];
            st16(m, g + 8, enc);
        }
    if (chance(rng, 35) && !o.units.empty()) {
        const u32 u = o.units[rng() % o.units.size()];
        const u16 id = kBossIds[rng() % std::size(kBossIds)];
        if (ld8(m, u + b3::unit::kSide) == 1) st16(m, u + b3::unit::kId, id);
    }
    static const u32 kFlagBits[] = {0x2u, 0x10u, 0x20u, 0x40u, 0x80u, 0x2000u, 0x4000u, 0x10000u, 0x200000u, 0x400000u,
                                    0x1000000u, 0x2000000u};
    for (int k = 0; k < 3; ++k)
        if (chance(rng, 30)) {
            const u32 bit = kFlagBits[rng() % std::size(kFlagBits)];
            st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) ^ bit);
        }
    if (chance(rng, 25)) {
        const u16 pend = static_cast<u16>(rng() % 3);
        st16(m, o.btl + b5::gbtl5::kNaviPending, pend);
    }
    if (chance(rng, 25)) {
        const u16 fl = static_cast<u16>(rng() & 1);
        st16(m, o.btl + b5::gbtl5::kNaviFlags, fl);
    }
    if (chance(rng, 25)) {
        const u16 ev = static_cast<u16>(rng() & 7);
        st16(m, o.btl + b5::gbtl5::kSupportEvents, ev);
    }
    if (chance(rng, 20)) {
        const u16 cam = static_cast<u16>(rng() % 3);
        st32(m, o.btl + b5::gbtl5::kCamHold, cam);
    }
    for (u32 u : o.units) {
        if (chance(rng, 15)) {
            const u16 wf = static_cast<u16>(rng() & 0x17u);
            st16(m, u + b3::unit::kWalkFlags, wf);
        }
        if (chance(rng, 10)) {
            const u32 mf = rng() & 0xFu;
            st32(m, u + b3::unit::kModelFlags, (ld32(m, u + b3::unit::kModelFlags) & ~0xFu) | mf);
        }
        if (chance(rng, 10)) {
            const u16 idle = static_cast<u16>(rng() % 8);
            st16(m, u + b5::unit5::kIdleKind, idle);
        }
    }
    for (u32 a : o.acts)
        if (chance(rng, 15)) {
            const u16 kind = static_cast<u16>(rng() % 13);
            st16(m, a + b3::act::kCmdKind, kind);
        }
}

// Builds the argument blocks in the scratch area and returns the value for one kind.
u64 arg_of(Machine& m, char kind, const Objects& o, std::mt19937& rng, u32& blk) {
    auto block = [&](u32 size) {
        const u32 b = kScratch + blk;
        blk += (size + 15) & ~15u;
        for (u32 i = 0; i < size; i += 4) {
            const bool zero = chance(rng, 60);
            const u32 v = rng() % 64;
            st32(m, b + i, zero ? 0 : v);
        }
        return b;
    };
    auto rnd_f = [&](int lo, int hi) {
        const int v = lo + static_cast<int>(rng() % static_cast<u32>(hi - lo + 1));
        return static_cast<float>(v);
    };
    const u32 act = pick(o.acts, rng, 0u);
    const u32 unit = pick(o.units, rng, 0u);
    const u32 unit2 = pick(o.units, rng, 0u);
    switch (kind) {
    case 'A': return sx(act);
    case 'r': return sx(act ? act + b3::act::kTargetRec : 0);
    case 'U': return sx(unit);
    case 'D': {
        const u32 b = block(64);
        st32(m, b, unit);
        const u16 major = static_cast<u16>(rng() % 3);
        st16(m, b + 4, major);
        const u16 minor = static_cast<u16>(rng() % 12);
        st16(m, b + 6, minor);
        const u32 fl = rng() & 0x16Fu;
        st32(m, b + 8, fl);
        st32(m, b + 12, 0);
        return sx(b);
    }
    case 'E': {
        const u32 b = block(64);
        st32(m, b + b5::pdd::kSource, act);
        const u32 hit = pick(o.acts, rng, 0u);
        st32(m, b + b5::pdd::kAction, hit);
        const s32 hp = static_cast<s32>(rng() % 401) - 200;
        st32(m, b + b5::pdd::kHp, static_cast<u32>(hp));
        const s32 sp = static_cast<s32>(rng() % 41) - 20;
        st32(m, b + b5::pdd::kSp, static_cast<u32>(sp));
        static const u32 kSet[] = {0u, 0x80000u, 0x100000u, 0x200u, 0x2u, 0x10u};
        const u32 set = kSet[rng() % std::size(kSet)];
        st32(m, b + b5::pdd::kSetStatus, set);
        const u32 clr = kSet[rng() % std::size(kSet)];
        st32(m, b + b5::pdd::kClearStatus, clr);
        const u16 f1 = static_cast<u16>(rng() & 0x18u);
        st16(m, b + b5::pdd::kFlags, f1);
        const u16 f2 = static_cast<u16>(rng() & 0x6u);
        st16(m, b + b5::pdd::kFlags2, f2);
        return sx(b);
    }
    case 'T': {
        const u32 b = block(32);
        st32(m, b, unit);
        st32(m, b + 4, unit2);
        const u32 fl = rng() & 0x22u;
        st32(m, b + 8, fl);
        const bool first = chance(rng, 70);
        const u32 frames = rng() % 8;
        st32(m, b + 12, first ? 0 : frames);
        return sx(b);
    }
    case 'Y': {
        const u32 b = block(64);
        st32(m, b, unit2);
        const u32 fl = rng() & 0x40u;
        st32(m, b + 16, fl);
        const bool first = chance(rng, 70);
        st32(m, b + 24, first ? 0 : 1);
        stf(m, b + 28, rnd_f(0, 60));
        st32(m, b + 36, unit);
        return sx(b);
    }
    case 'N': {
        const u32 b = block(32);
        st32(m, b, act);
        const u16 line = static_cast<u16>(rng() % 41);
        st16(m, b + 4, line);
        const u32 fl = rng() & 7u;
        st32(m, b + 16, fl);
        st32(m, b + 20, 0);
        return sx(b);
    }
    case 'S': {
        const u32 b = block(16);
        const u16 navi = static_cast<u16>(rng() % 2);
        st16(m, b + 4, navi);
        const u16 step = static_cast<u16>(rng() % 6);
        st16(m, b + 6, step);
        return sx(b);
    }
    case 'R': {
        static const char* kNames[] = {"BTL_SE.VAG", "", "WIN.VAG"};
        const u32 b = block(16), name = block(32);
        const char* t = kNames[rng() % std::size(kNames)];
        std::memcpy(m.at(name), t, std::strlen(t) + 1);
        const u16 ch = static_cast<u16>(rng() % 4);
        st16(m, b, ch);
        st32(m, b + 4, name);
        return sx(b);
    }
    case 'K': {
        const u32 b = block(16);
        const u16 skill = static_cast<u16>(rng() % 0x1D0);
        st16(m, b + 4, skill);
        const u16 step = static_cast<u16>(1 + rng() % 2);
        st16(m, b + 6, step);
        st32(m, b + 8, 0);
        return sx(b);
    }
    case 'O': {
        const u32 b = block(16);
        const u16 k = static_cast<u16>(rng() % 3);
        st16(m, b, k);
        return sx(b);
    }
    case 'P': return sx(block(64));
    case 'L': {  // a bp_list record: flags (the 'moved' bit 1 mostly clear), top, rows, cursor, count, the move sounds
        const u32 b = block(64);
        const u32 fl = rng() & 0x6u;
        const bool moved = chance(rng, 10);
        st32(m, b + b5::blist::kFlags, fl | (moved ? 1u : 0u));
        const u32 count = rng() % 12;
        const u32 rows = 1 + rng() % 6;
        const u32 cur = count ? rng() % count : 0;
        const u32 top = rng() % 4;
        st32(m, b + b5::blist::kTop, top);
        st32(m, b + b5::blist::kRows, rows);
        st32(m, b + b5::blist::kCursor, cur);
        st32(m, b + b5::blist::kCount, count);
        for (u32 k = 0; k < 8; ++k) {
            const u8 sk = static_cast<u8>(rng() % 3);
            st8(m, b + b5::blist::kSounds + 4 * k, sk);
        }
        return sx(b);
    }
    case 'H': {  // a sprite sheet: the texture table (+260) and four 128-byte cells (+388)
        const u32 b = block(400), cells = block(512), tex = block(32);
        st32(m, b + b5::sheet::kCells, cells);
        for (u32 k = 0; k < 4; ++k) st32(m, b + b5::sheet::kTextures + 4 * k, tex);
        const u32 tw = 16 + rng() % 240;
        st32(m, tex + 12, tw);
        const u32 th = 16 + rng() % 240;
        st32(m, tex + 16, th);
        for (u32 k = 0; k < 4; ++k) {
            const u32 c = cells + 128 * k;
            st32(m, c + 20, rng() % 4);
            st32(m, c + 24, rng() & 3u);
            for (u32 i = 0; i < 4; ++i) st32(m, c + 84 + 4 * i, rng() % 256);
            for (u32 i = 0; i < 4; ++i) st32(m, c + 100 + 4 * i, rng());
        }
        return sx(b);
    }
    case 'Q': {  // a camera shot: the action +224, its kind +228, the point +156, the path +236, the target +256
        const u32 b = block(288);
        st32(m, b + 224, act);
        const u16 sk = static_cast<u16>(rng() % 36);
        st16(m, b + 228, sk);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 156 + 4 * i, rnd_f(-500, 500));
        const u32 tgt = act ? ld32(m, act + b3::act::kTargets) : 0;
        const bool same = chance(rng, 70);
        st32(m, b + 256, same ? tgt : pick(o.acts, rng, 0u));
        const u32 keep = rng() % 2;
        st32(m, b + 276, keep);
        return sx(b);
    }
    case 'Z': {  // a camera path between two units: the key table of 60-byte keys after a u16 count
        const u32 b = block(32), keys = block(4 + 60 * 4);
        st32(m, b, act);
        st32(m, b + 4, pick(o.acts, rng, 0u));
        const s16 key = static_cast<s16>(static_cast<int>(rng() % 5) - 1);
        st16(m, b + 10, static_cast<u16>(key));
        const u16 frame = static_cast<u16>(rng() % 4);
        st16(m, b + 12, frame);
        const u16 fl = static_cast<u16>((rng() & 0x1Eu) | 1u);
        st16(m, b + 14, fl);
        st32(m, b + 16, keys);
        const u16 nk = static_cast<u16>(1 + rng() % 4);
        st16(m, keys, nk);
        for (u32 k = 0; k < 4; ++k) {
            const u32 kb = keys + 4 + 60 * k;
            const u16 len = static_cast<u16>(rng() % 3);
            st16(m, kb, len);
            const u16 kk = static_cast<u16>(1 + rng() % 2);
            st16(m, kb + 2, kk);
            for (u32 i = 1; i < 14; ++i) stf(m, kb + 4 * i, rnd_f(-300, 300));
            const u16 tk = static_cast<u16>(1 + rng() % 2);
            st16(m, kb + 28, tk);
        }
        return sx(b);
    }
    case 'V': {  // a vertex job: &&vertices, the screen u / v (0..1), the wait work (+4472 fade), the vertex index
        const u32 b = block(32), pp = block(16), verts = block(64 * 8), work = block(4480);
        st32(m, pp, verts);
        st32(m, b, pp);
        stf(m, b + 4, rnd_f(0, 1000) / 1000.0f);
        stf(m, b + 8, rnd_f(0, 1000) / 1000.0f);
        st32(m, b + 12, work);
        stf(m, work + 4472, rnd_f(0, 100) / 100.0f);
        st32(m, b + 16, rng() % 8);
        return sx(b);
    }
    case 'W': {  // a light fade record: three target colours, the length +96, the frame +100, the flags +104
        const u32 b = block(112);
        for (u32 i = 0; i < 24; ++i) stf(m, b + 4 * i, rnd_f(0, 255) / 255.0f);
        const u32 len = 1 + rng() % 30;
        st32(m, b + 96, len);
        const u32 fr = rng() % (len + 2);
        st32(m, b + 100, fr);
        const u16 fl = static_cast<u16>(rng() & 5u);
        st16(m, b + 104, fl);
        return sx(b);
    }
    case 'X': {  // a script task whose +60 holds the flash state {u8 state, ..., u16 +6}
        const u32 b = block(64), st = block(16);
        st32(m, b + 60, st);
        const u8 s = static_cast<u8>(rng() % 4);
        st8(m, st, s);
        const u16 v = static_cast<u16>(rng() % 2);
        st16(m, st + 6, v);
        return sx(b);
    }
    case 'J': {
        const u32 b = block(1600), att = block(64);
        st32(m, b + 1536, att);
        const u32 fl = rng() & 1u;
        st32(m, b + 1540, fl);
        return sx(b);
    }
    case 'B': {
        const u32 b = block(16);
        const u32 owner = rng() & 1u;
        st32(m, b, owner);
        const u16 ps = static_cast<u16>(1 + rng() % 180);
        st16(m, b + 4, ps);
        return sx(b);
    }
    case 'G': return 1 + rng() % 180;
    case 'M': return rng() % 2;
    case 'k': {
        const bool none = chance(rng, 5);
        const bool common = chance(rng, 90);
        const u32 k = rng() % (common ? 464 : 624);
        return none ? sx(0xFFFFFFFFu) : k;
    }
    case 'e': return sx(static_cast<u32>(static_cast<int>(rng() % 20) - 1));
    case 'l': return rng() % 41;
    case 'u': {
        const bool live = chance(rng, 80);
        const u32 any = rng() % 0x400;
        return live ? pick(o.uids, rng, 0u) : any;
    }
    case 'm': return rng() % 26;
    case 'g': return rng() % 13;
    case 'n': return rng() % 8;
    case 'c': return rng() % 4;
    case 'p': return rng() % 9;
    case 'f': return rng() & 0x3F;
    case 'F': return rng() % 60;
    case 'z': return 0;
    case 'o': return sx(block(64));
    case 't': {  // a short text
        static const char* kTexts[] = {"", "Attack", "The enemy is down!", "One more!"};
        const u32 b = block(32);
        const char* t = kTexts[rng() % 4];
        std::memcpy(m.at(b), t, std::strlen(t) + 1);
        return sx(b);
    }
    case 'v': {
        const u32 b = block(16);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 4 * i, rnd_f(-1800, 1800) / 1.5f);
        return sx(b);
    }
    default: return rng() % 8;
    }
}

// a0..a3 in Args; $t0..$t2 through HwCheck::gpr_in.
void args_for(Machine& m, const Case& c, const Objects& o, std::mt19937& rng, Args& a, HwCheck& hw) {
    u32 blk = 0;
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 7; ++i) {
        const u64 v = i < n ? arg_of(m, c.kinds[i], o, rng, blk) : rng() % 8;
        if (i < 4) a[i] = v;
        else hw.gpr_in[GPR_T0 + (i - 4)] = v;
    }
}

// Bodies paired on the battle snapshots only (see each reason).
bool random_world_skip(u32 addr) {
    (void)addr;
    return false;
}

// b_5800: the first battle in state ACTION (4 actions, 7 units, 15 packets) -- most pairs; battle_ref_6150 / b_6150:
// the battle over (RESULT, empty lists); b_6300 / b_6700 / climb_ref_17000: no battle (gBtl 0): the null paths.
struct Snap {
    const char* dir;
    u32 reps;
};
const Snap kSnapshots[] = {{"b_5800", 24}, {"battle_ref_6150", 3}, {"b_6150", 2}, {"b_6300", 1}, {"b_6700", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle5): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    constexpr u32 kWorld = 0x01810000u, kWorldSize = 0x10000u;
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        if (random_world_skip(c.addr)) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name, {}).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " ended at a compared stop");
}

TEST_CASE("game(battle5): every body on the battle snapshots, perturbed") {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    int pairs = 0, stops = 0, used = 0;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    std::string always;
    std::vector<int> stopped_of(std::size(kCases), 0), ran_of(std::size(kCases), 0);
    std::vector<std::string> why_of(std::size(kCases));
    std::map<u32, std::string> missing;  // not-emitted callees the pairs stopped at, and who reached them
    for (const Snap& sn : kSnapshots) {
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        const std::vector<u8> snap = read_snapshot(sn.dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(sn.dir) << "/eeMemory.bin not found");
            continue;
        }
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        ++used;
        MESSAGE(std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions, " << o.units.size()
                                    << " units, " << o.data.size() << " packet data blocks, " << o.works.size() << " live works");
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (std::size_t ci = 0; ci < std::size(kCases); ++ci) {
            const Case& c = kCases[ci];
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                std::mt19937 rng{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                perturb(*m, o, rng);
                Args a{};
                HwCheck hw;
                args_for(*m, c, o, rng, a, hw);
                const hgp::Run r = pair_base(*m, base, c.hand, c.recomp, a, rng(), c.name, hw);
                ++pairs;
                ++ran_of[ci];
                if (r.stopped) {
                    ++stops;
                    if (stopped_of[ci]++ == 0) why_of[ci] = r.what + " at " + hex64(r.stop_pc);
                    if (r.what.rfind("missing_function", 0) == 0 && missing[r.stop_pc].find(c.name) == std::string::npos)
                        missing[r.stop_pc] += std::string(" ") + c.name;
                }
                base.restore();
            }
        }
    }
    for (std::size_t ci = 0; ci < std::size(kCases); ++ci)
        if (ran_of[ci] && stopped_of[ci] == ran_of[ci]) always += std::string(" ") + kCases[ci].name + " (" + why_of[ci] + ")";
    for (const auto& [pc, who] : missing) MESSAGE("stopped at the not-emitted " << hex64(pc) << ":" << who.substr(0, 200));
    MESSAGE("battle snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops
                                 << " ended at a compared stop; always stopped:" << (always.empty() ? " none" : always));
}

namespace {
// A small fake battle on the scratch area for the rule checks: a zeroed gBtl (3,440 bytes) behind $gp - 18692, its
// setup genus (+3004, the encounter id at +8), one action / unit / DatUnit triple.
struct Fake {
    u32 btl = kScratch + 0x10000u, genus = kScratch + 0x10E00u, act = kScratch + 0x11000u, unit = kScratch + 0x11800u,
        dat = kScratch + 0x12400u;
};
Fake fake_battle(Machine& m, u16 encounter) {
    Fake f;
    std::memset(m.at(kScratch + 0x10000u), 0, 0x3000);
    st32(m, kGBtlSlot, f.btl);
    st32(m, f.btl + b3::gbtl::kSetupEnemies, f.genus);
    st16(m, f.genus + 8, encounter);
    st32(m, f.act + b3::act::kUnit, f.unit);
    st32(m, f.unit + b3::unit::kDat, f.dat);
    return f;
}
// One body alone with extra recorders {address, $v0} (the dispatch rules: which handler an encounter reaches).
hgp::Run solo_rec(Machine& m, Fn fn, const Args& args, const std::vector<std::pair<u32, u64>>& recs) {
    g_solo = std::make_unique<StandInWorld>();
    b5_setup(*g_solo);
    for (const auto& [va, v0] : recs) g_solo->si.install_recorder(va, "rule_" + hex64(va), v0, 4);
    g_si[0] = g_solo.get();
    g_fn[0] = fn;
    return hgp::run_one(m, &thunk0, args, 1, {});
}
// The solo run's last call of the stood-in `va` (nullptr when none).
const StandInCall* solo_call(u32 va) {
    for (auto it = g_solo->si.log.rbegin(); it != g_solo->si.log.rend(); ++it)
        if (it->va == va) return &*it;
    return nullptr;
}
std::string fmt_hex3(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "%03X", v);
    return b;
}
std::string guest_str(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }
// The file layer logs a request's normalised path (H_Cdvd_BuildPathUppercase: "VOL:\" + upper case, backslashes).
std::string cd_path(std::string p) {
    for (char& c : p) c = c == '/' ? '\\' : static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return "VOL:\\" + p;
}
}  // namespace

TEST_CASE("game(battle5): the battle code follows the documented rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    auto flag_of = [&](u32 slot) -> u64 {  // datGetFlag(*slot), 0 for the -1 'no flag' entries
        const u32 id = ld32(*m, slot);
        if (id == 0xFFFFFFFFu) return 0;
        return v0_of(solo(*m, &rg::fn_datGetFlag_0016f190, {id, 0, 0, 0})) != 0 ? 1 : 0;
    };
    const bool fes = v0_of(solo(*m, &rg::fn_sub_17D800_0017d800, {0, 0, 0, 0})) != 0;

    // (1) the formation pick: the first of the 24 formations (224-byte rows of 0x694F10) whose size limits (+216 small,
    //     +218 medium, +220 large) hold the enemies counted by sub_2B6DE0 (by scale * radius / height), else 23 (b_5800,
    //     a plain encounter, the enemies' sizes varied).
    {
        const std::vector<u8> snap = read_snapshot("b_5800");
        if (!snap.empty()) {
            std::mt19937 rng{0x2B70u};
            std::map<u32, int> seen;  // the (small, medium, large) counts met
            for (int k = 0; k < 160; ++k) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                write_rw_slots(*m);
                const Objects o = objects_of(*m);
                if (!o.btl) break;
                if (const u32 g = ld32(*m, o.btl + b3::gbtl::kSetupEnemies); in_ram(g)) st16(*m, g + 8, 1);
                // the enemy list (gBtl +348, +2608 next): sizes, and one to four copies of its head unit chained in
                const u32 head = ld32(*m, o.btl + b3::gbtl::kUnitHead1);
                if (!in_ram(head)) break;
                if (const u32 d = ld32(*m, head + b3::unit::kDat); in_ram(d)) {  // alive (the copies share it)
                    st16(*m, d + b3::dat::kHp, 100);
                    st32(*m, d + b3::dat::kStatus, 0);
                }
                const u32 extra = rng() % 4;
                for (u32 i = 0; i < extra; ++i) {
                    const u32 copy = kScratch + 0x20000u + 0x1000u * i;
                    std::memcpy(m->at(copy), m->at(head), 0xA40);
                    st32(*m, copy + b3::unit::kNext, ld32(*m, head + b3::unit::kNext));
                    st32(*m, head + b3::unit::kNext, copy);
                }
                for (u32 u = head, n = 0; in_ram(u) && n < 8; u = ld32(*m, u + b3::unit::kNext), ++n) {
                    stf(*m, u + b3::unit::kScale, 1.0f);
                    const u32 radius = 40 + rng() % 140;
                    stf(*m, u + b3::unit::kRadius, static_cast<float>(radius));
                    const u32 height = 100 + rng() % 260;
                    stf(*m, u + b4::unit4::kHeight, static_cast<float>(height));
                }
                const u32 buf = kScratch + 0x18000u;
                std::memset(m->at(buf), 0, 16);
                solo(*m, &rg::fn_sub_2B6DE0_002b6de0, {sx(buf), 0, 0, 0});
                const u16 small = ld16(*m, buf), medium = ld16(*m, buf + 2), large = ld16(*m, buf + 4);
                s32 want = 23;
                for (u32 i = 0; i < 24; ++i) {
                    const u32 row = 0x694F10u + 224u * i;
                    if (ld16(*m, row + 216) >= small && ld16(*m, row + 218) >= medium && ld16(*m, row + 220) >= large) {
                        want = static_cast<s32>(i);
                        break;
                    }
                }
                INFO("S " << small << " M " << medium << " L " << large);
                CHECK(static_cast<s16>(v0_of(solo(*m, &rg::fn_sub_2B7060_002b7060, {0, 0, 0, 0}))) == want);
                ++seen[small * 100u + medium * 10u + large];
                ++checks;
            }
            MESSAGE("formation pick: " << seen.size() << " different (small, medium, large) counts");
        }
    }
    // (2) the boss dispatch by encounter: the win condition (sub_2FD660), the action check (sub_2FDE40, only with gBtl
    //     +12 bit 0x200000), the after-damage hook (sub_2FAA50) -- each encounter reaches its own handler (recorders
    //     with distinct results), the plain encounters none.
    for (u32 enc = 410; enc <= 460; ++enc) {
        const Fake f = fake_battle(*m, static_cast<u16>(enc));
        const std::vector<std::pair<u32, u64>> recs = {{0x2E97E0u, 5}, {0x2EF9D0u, 6}, {0x2F1B60u, 7}, {0x2EEE20u, 8},
                                                       {0x2F5BF0u, 9}, {0x2EC190u, 10}};
        INFO("encounter " << enc);
        const u64 win = v0_of(solo_rec(*m, &rg::fn_sub_2FD660_002fd660, {0, 0, 0, 0}, recs));
        if (enc == 416) CHECK(win == 5u);
        else if (enc == 424) CHECK(win == 6u);
        else if (enc == 436 || enc == 420) CHECK(win == 1u);  // no boss unit in the (empty) enemy list: won
        else CHECK(win == 0u);
        for (u32 armed = 0; armed < 2; ++armed) {
            st32(*m, f.btl + b3::gbtl::kFlags, armed ? 0x200000u : 0u);
            const u64 r = v0_of(solo_rec(*m, &rg::fn_sub_2FDE40_002fde40, {0, 0, 0, 0}, recs));
            CHECK(r == (!armed ? 0u : enc == 426 ? 7u : enc == 423 ? 8u : 0u));
        }
        solo_rec(*m, &rg::fn_sub_2FAA50_002faa50, {0, 0, 0, 0}, recs);
        CHECK((solo_call(0x2F5BF0u) != nullptr) == (enc == 436));
        CHECK((solo_call(0x2EC190u) != nullptr) == (enc == 421));
        ++checks;
    }
    //     ... and the win conditions of 436 / 420 over a living / dead boss unit in the enemy list (gBtl +344, +2612 prev)
    for (u32 enc : {436u, 420u})
        for (u16 id : {u16{241}, u16{242}, u16{261}, u16{262}, u16{100}})
            for (u32 dead = 0; dead < 2; ++dead) {
                const Fake f = fake_battle(*m, static_cast<u16>(enc));
                st32(*m, f.btl + b4::gbtl4::kUnitTail1, f.unit);
                st16(*m, f.unit + b3::unit::kId, id);
                st16(*m, f.dat + b3::dat::kHp, static_cast<u16>(dead ? 0 : 50));
                st32(*m, f.dat + b3::dat::kStatus, dead ? 0x80000u : 0u);
                const bool is_dead = v0_of(solo(*m, &rg::fn_datCalcIsDead_0030b5a0, {sx(f.dat), 0, 0, 0})) != 0;
                const bool boss = enc == 436 ? id == 241 : (id == 261 || id == 262);
                INFO("encounter " << enc << " id " << id << " dead " << is_dead);
                CHECK(v0_of(solo(*m, &rg::fn_sub_2FD660_002fd660, {0, 0, 0, 0})) == (boss && !is_dead ? 0u : 1u));
                ++checks;
            }
    // (3) the boss reaction motions (sub_2F8FD0) by encounter, enemy id and skill
    {
        const u32 react = ld32(*m, gp(b5::kGpReactRows));
        const u16 encs[] = {436, 424, 422, 421, 419, 418, 417, 1, 300};
        const u16 ids[] = {241, 269, 266, 263, 260, 259, 257, 258, 149, 152, 156, 157, 100};
        std::mt19937 rng{0x2F8Fu};
        for (u16 enc : encs)
            for (u16 id : ids)
                for (int k = 0; k < 12; ++k) {
                    static const u16 kSkills[] = {293, 294, 295, 296, 308, 144, 115, 131, 363, 364, 355, 368, 1, 10, 120};
                    const bool listed = chance(rng, 70);
                    const u16 any = static_cast<u16>(rng() % 0x1D0);
                    u16 skill = listed ? kSkills[rng() % std::size(kSkills)] : any;
                    const bool row_skill = id >= 149 && id <= 156 && in_ram(react) && chance(rng, 40);
                    const u32 col = rng() % 4;
                    if (row_skill) skill = ld16(*m, react + 8u * (id - 149u) + 2u * col);
                    for (u8 side : {u8{1}, u8{0}}) {
                        const Fake f = fake_battle(*m, enc);
                        st8(*m, f.unit + b3::unit::kSide, side);
                        st16(*m, f.unit + b3::unit::kId, id);
                        const bool second = chance(rng, 50);
                        st32(*m, f.btl + b3::gbtl::kBossWork4, second ? 1u : 0u);
                        const bool hp_skill = v0_of(solo(*m, &rg::fn_datCalcIsHpSkill_002d6370, {skill, 0, 0, 0})) != 0;
                        s32 want = -1;
                        if (side == 1) {
                            switch (enc) {
                            case 436: want = id == 241 && skill >= 293 && skill <= 296 ? 0 : -1; break;
                            case 424: want = id == 269 && skill == 308 ? (second ? 21 : 7) : -1; break;
                            case 422: {
                                const bool hit = skill == 144 || skill == 142 || skill == 141 || skill == 131 || skill == 128 ||
                                                 skill == 127 || skill == 119 || skill == 117 || skill == 115;
                                want = id == 266 && hit ? 24 : -1;
                                break;
                            }
                            case 421: want = id == 263 && skill == 363 ? 23 : id == 263 && skill == 364 ? 25 : -1; break;
                            case 419: want = id == 260 && hp_skill ? 24 : -1; break;
                            case 418: want = id == 259 && skill == 355 ? 23 : -1; break;
                            case 417: want = (id == 257 || id == 258) && skill == 368 ? 23 : -1; break;
                            default:
                                if (id >= 149 && id <= 156) {
                                    static const s32 kMotion[4] = {4, 7, 23, 24};
                                    want = 7;
                                    for (u32 c = 0; c < 4; ++c)
                                        if (ld16(*m, react + 8u * (id - 149u) + 2u * c) == skill) {
                                            want = kMotion[c];
                                            break;
                                        }
                                }
                                break;
                            }
                        }
                        INFO("encounter " << enc << " id " << id << " side " << int(side) << " skill " << skill);
                        CHECK(static_cast<s16>(v0_of(solo(*m, &rg::fn_sub_2F8FD0_002f8fd0, {sx(f.unit), skill, 0, 0}))) == want);
                        ++checks;
                    }
                }
    }
    // (4) the voice line maps of the party members (sub_2DE2A0 / sub_2DED60 / sub_2E1500), enemies -1
    {
        const bool f_be0 = flag_of(0x697BE0u) != 0, f_be4 = flag_of(0x697BE4u) != 0, f_be8 = flag_of(0x697BE8u) != 0,
                   f_bec = flag_of(0x697BECu) != 0, f_bf4 = flag_of(0x697BF4u) != 0, f_bf8 = flag_of(0x697BF8u) != 0;
        static const s32 kSitOff[10] = {0, 1, 2, 3, 4, 6, 5, 9, 7, 8};
        for (u16 id = 0; id <= 11; ++id)
            for (u8 side : {u8{0}, u8{1}}) {
                const Fake f = fake_battle(*m, 1);
                st8(*m, f.unit + b3::unit::kSide, side);
                st16(*m, f.unit + b3::unit::kId, id);
                s32 a = -1, b = -1, base = -1;
                if (side == 0) switch (id) {
                    case 2: a = 176; b = f_be0 ? 165 : 164; base = 203; break;
                    case 3: a = f_be4 ? 260 : 259; b = f_be4 ? 246 : 245; base = 297; break;
                    case 4: a = 358; b = f_be8 ? 347 : 346; base = 385; break;
                    case 5: a = 431; b = f_bec ? 420 : 419; base = 458; break;
                    case 7: a = 523; b = f_bf4 ? 493 : 492; base = 531; break;
                    case 8: a = 563; b = f_bf8 ? 566 : 565; base = 604; break;
                    case 9: a = fes ? 1139 : 642; b = fes ? 1130 : 634; base = fes ? 1174 : 669; break;
                    default: break;
                    }
                INFO("id " << id << " side " << int(side));
                CHECK(static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2DE2A0_002de2a0, {sx(f.act), 0, 0, 0}))) == a);
                CHECK(static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2DED60_002ded60, {sx(f.act), 0, 0, 0}))) == b);
                for (u32 s = 0; s <= 11; ++s) {
                    const s32 want = base < 0 || s > 9 ? -1 : base + kSitOff[s];
                    CHECK(static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2E1500_002e1500, {sx(f.act), s, 0, 0}))) == want);
                }
                ++checks;
            }
    }
    // (5) the battle music (sub_2DCD30): the encounter table's music kind (gEncountTbl 28-byte rows, +22) -> the track
    //     (2..6 -> 27..31, 7 / 8 -> 113 / 114, else 2, or 106 with sub_17D800), only with the sound flag (gBtl +12 0x40)
    {
        const u32 etbl = ld32(*m, gp(b3::kGpEncountTbl));
        for (u32 enc = 0; enc < 520 && in_ram(etbl); enc += 3)
            for (u32 sound = 0; sound < 2; ++sound) {
                const Fake f = fake_battle(*m, static_cast<u16>(enc));
                st32(*m, f.btl + b3::gbtl::kFlags, sound ? 0x40u : 0u);
                solo(*m, &rg::fn_sub_2DCD30_002dcd30, {0, 0, 0, 0});
                const StandInCall* c = solo_call(0x1099D0u);
                const u16 kind = ld16(*m, etbl + 28u * enc + 22u);
                static const u32 kTracks[9] = {0, 0, 27, 28, 29, 30, 31, 113, 114};
                const u32 want = kind >= 2 && kind <= 8 ? kTracks[kind] : (fes ? 106u : 2u);
                INFO("encounter " << enc << " music kind " << kind);
                CHECK((c != nullptr) == (sound != 0));
                if (c) {
                    CHECK(static_cast<u32>(c->args[0]) == want);
                    CHECK(static_cast<u32>(c->args[1]) == 1u);
                }
                ++checks;
            }
    }
    // (6) the skill sound bank path "skill/%03X.se" (sub_2DD2F0) and the named battle sounds "SOUND2\BATTLE\<name>"
    //     (sub_2DD630, channel +0)
    for (u32 skill : {0u, 1u, 0x2Au, 0x100u, 0x1CFu, 0xFFFu}) {
        const Fake f = fake_battle(*m, 1);
        const u32 d = kScratch + 0x18100u;
        std::memset(m->at(d), 0, 16);
        st16(*m, d + 4, static_cast<u16>(skill));
        st16(*m, d + 6, 1);
        solo(*m, &rg::fn_sub_2DD2F0_002dd2f0, {sx(d), 0, 0, 0});
        CHECK(last_request_path() == cd_path("skill/" + fmt_hex3(skill) + ".se"));
        CHECK(ld32(*m, d + 8) != 0u);
        (void)f;
        ++checks;
    }
    for (const char* name : {"BTL_SE.VAG", "A", "WIN_JINGLE"})
        for (u16 ch = 0; ch < 3; ++ch) {
            const u32 d = kScratch + 0x18200u, s = kScratch + 0x18300u;
            std::memcpy(m->at(s), name, std::strlen(name) + 1);
            st16(*m, d, ch);
            st32(*m, d + 4, s);
            CHECK(v0_of(solo(*m, &rg::fn_sub_2DD630_002dd630, {sx(d), 0, 0, 0})) == 1u);
            const StandInCall* c = solo_call(0x10A370u);
            REQUIRE(c != nullptr);
            CHECK(static_cast<u32>(c->args[0]) == ch);
            CHECK(guest_str(*m, static_cast<u32>(c->args[1])) == std::string("SOUND2\\BATTLE\\") + name);
            ++checks;
        }
    // (7) the sound packets' memory: a bank replays only a changed sound (sub_2DD020, gBtl +2708 + 6 * bank); the
    //     footsteps cycle the sounds 5..8 (sub_2DD510, gBtl +2704 / +2706)
    {
        const Fake f = fake_battle(*m, 1);
        std::mt19937 rng{0x2DD0u};
        for (int k = 0; k < 60; ++k) {
            const u16 bank = static_cast<u16>(rng() % 4);
            const u16 id = static_cast<u16>(rng() % 3);
            const u16 arg = static_cast<u16>(rng() % 2);
            const u32 memo = f.btl + b5::gbtl5::kSoundMemo + 6u * bank;
            const u16 old_id = ld16(*m, memo), old_arg = ld16(*m, memo + 2);
            st8(*m, memo + 4, 0x5A);
            const u32 d = kScratch + 0x18400u;
            st16(*m, d, bank);
            st16(*m, d + 2, id);
            st16(*m, d + 4, arg);
            CHECK(v0_of(solo(*m, &rg::fn_sub_2DD020_002dd020, {sx(d), 0, 0, 0})) == 1u);
            const bool changed = old_id != id || old_arg != arg;
            CHECK(ld16(*m, memo) == id);
            CHECK(ld16(*m, memo + 2) == arg);
            CHECK(ld8(*m, memo + 4) == (changed ? 0u : 0x5Au));
            ++checks;
        }
        st16(*m, f.btl + b5::gbtl5::kStepSound, 5);
        for (int k = 0; k < 10; ++k) {
            const u16 before = ld16(*m, f.btl + b5::gbtl5::kStepSound);
            st8(*m, f.btl + b5::gbtl5::kStepSoundIdle, 0xFF);
            const u32 d = kScratch + 0x18500u;
            st16(*m, d, 1);
            solo(*m, &rg::fn_sub_2DD510_002dd510, {sx(d), 0, 0, 0});
            CHECK(ld8(*m, f.btl + b5::gbtl5::kStepSoundIdle) == 0u);
            CHECK(ld16(*m, f.btl + b5::gbtl5::kStepSound) == (before + 1u >= 9u ? 5u : before + 1u));
            // not idle: nothing moves
            solo(*m, &rg::fn_sub_2DD510_002dd510, {sx(d), 0, 0, 0});
            CHECK(ld16(*m, f.btl + b5::gbtl5::kStepSound) == (before + 1u >= 9u ? 5u : before + 1u));
            ++checks;
        }
    }
    // (8) the op fade (op_fade.c): start in / out set the mode and restart the frame; a step counts the frame to the
    //     length, then the fade stops (flag 1 cleared, opFadeIsActive 0)
    {
        const u32 w = kScratch + 0x19000u;
        std::memset(m->at(w), 0, 0x200);
        solo(*m, &rg::fn_sub_271CD0_00271cd0, {sx(w), 0, 0, 0});
        CHECK(ld32(*m, gp(b5::kGpOpFade)) == w);
        CHECK(ld8(*m, w + b5::opfade::kColour + 3) == 0xFFu);
        for (u32 len : {0u, 1u, 5u, 12u})
            for (u32 mode = 1; mode <= 2; ++mode) {
                solo(*m, &rg::fn_sub_2721D0_002721d0, {len, 0, 0, 0});
                CHECK(ld32(*m, w + b5::opfade::kMode) == 0u);
                solo(*m, mode == 1 ? &rg::fn_sub_271DB0_00271db0 : &rg::fn_sub_271E10_00271e10, {0, 0, 0, 0});
                CHECK(ld32(*m, w + b5::opfade::kMode) == mode);
                CHECK(ld32(*m, w + b5::opfade::kFrame) == 0u);
                for (u32 step = 0; step <= len + 1; ++step) {
                    CHECK(v0_of(solo(*m, &rg::fn_sub_271E70_00271e70, {0, 0, 0, 0})) == (step <= len ? 1u : 0u));
                    solo(*m, &rg::fn_sub_271EC0_00271ec0, {0, 0, 0, 0});
                    CHECK(ld32(*m, w + b5::opfade::kFrame) == std::min(step + 1, len));
                }
                ++checks;
            }
    }
    // (9) the battle list cursor (bp_list.c, sub_24A260): down / up wrap, R2 / L2 page, the window follows the cursor
    {
        std::mt19937 rng{0x24A2u};
        const u32 l = kScratch + 0x19400u;
        for (int k = 0; k < 400; ++k) {
            std::memset(m->at(l), 0, 64);
            const s32 count = static_cast<s32>(rng() % 12);
            const s32 rows = static_cast<s32>(1 + rng() % 6);
            const s32 cur0 = count ? static_cast<s32>(rng() % static_cast<u32>(count)) : 0;
            const s32 top0 = static_cast<s32>(rng() % 4);
            const u32 fl0 = rng() & 2u;
            st32(*m, l + b5::blist::kFlags, fl0);
            st32(*m, l + b5::blist::kTop, static_cast<u32>(top0));
            st32(*m, l + b5::blist::kRows, static_cast<u32>(rows));
            st32(*m, l + b5::blist::kCursor, static_cast<u32>(cur0));
            st32(*m, l + b5::blist::kCount, static_cast<u32>(count));
            static const u16 kPads[] = {0x4000, 0x1000, 0x0002, 0x0001, 0x0000, 0x4000, 0x1000};
            const u16 pad = kPads[rng() % std::size(kPads)];
            const bool held = chance(rng, 20);
            st16(*m, 0x7E0952u, pad);
            st16(*m, 0x7E095Au, 0);
            st16(*m, 0x7E094Cu, held ? 0x4000 : 0);
            st16(*m, 0x7E0956u, 0);
            solo(*m, &rg::fn_sub_24A260_0024a260, {sx(l), 0, 0, 0});
            // host model
            u32 fl = fl0;
            s32 cur = cur0, top = top0;
            if (!(fl & 2u) || !held) {
                fl &= ~2u;
                auto moved = [&](bool at_end) {
                    if (at_end) fl |= 2u;
                    fl |= 1u;
                };
                if (pad & 0x4000) {
                    if (count >= 2) {
                        if (cur >= count - 1) cur = top = 0;
                        else {
                            ++cur;
                            if (cur >= top + rows - 1 && top < count - rows) ++top;
                        }
                        moved(cur == count - 1);
                    }
                } else if (pad & 0x1000) {
                    if (count >= 2) {
                        if (cur <= 0) {
                            cur = count - 1;
                            top = count - rows;
                        } else {
                            --cur;
                            if (top >= cur && top > 0) --top;
                        }
                        moved(cur == 0);
                    }
                } else if (pad & 2) {
                    if (count >= 2 && cur != count - 1) {
                        if (cur + rows >= count - 1 || count - rows < top + rows) {
                            cur = count - 1;
                            top = count - rows;
                        } else {
                            cur += rows;
                            top += rows;
                        }
                        moved(cur == count - 1);
                    }
                } else if ((pad & 1) && count >= 2 && cur != 0) {
                    if (cur < rows || top < rows) cur = top = 0;
                    else {
                        cur -= rows;
                        top -= rows;
                    }
                    moved(cur == 0);
                }
            }
            INFO("count " << count << " rows " << rows << " cursor " << cur0 << " top " << top0 << " pad " << hex64(pad)
                          << " held " << held << " flags " << fl0);
            CHECK(static_cast<s32>(ld32(*m, l + b5::blist::kCursor)) == cur);
            CHECK(static_cast<s32>(ld32(*m, l + b5::blist::kTop)) == top);
            CHECK(ld32(*m, l + b5::blist::kFlags) == fl);
            ++checks;
        }
        st16(*m, 0x7E0952u, 0);
        st16(*m, 0x7E094Cu, 0);
    }
    // (10) the indexed grid mesh (sub_269690, kind 0): (c + 1)(r + 1) 64-byte vertices, 6cr u16 indices, two triangles
    //      per cell {v, v + 1, v + c + 1, v + 1, v + c + 2, v + c + 1}; the header {vertices, indices, c, r, counts, kind}
    for (u32 c = 1; c <= 6; ++c)
        for (u32 r = 1; r <= 5; ++r) {
            const u32 mesh = static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_269690_00269690, {0, c, r, 0})));
            REQUIRE(in_ram(mesh));
            const u32 nv = (c + 1) * (r + 1), ni = 6 * c * r;
            INFO("cols " << c << " rows " << r);
            CHECK(ld32(*m, mesh) == mesh + 32);
            CHECK(ld32(*m, mesh + 4) == mesh + 32 + 64 * nv);
            CHECK(ld32(*m, mesh + 8) == c);
            CHECK(ld32(*m, mesh + 12) == r);
            CHECK(ld32(*m, mesh + 16) == nv);
            CHECK(ld32(*m, mesh + 20) == ni);
            CHECK(ld32(*m, mesh + 24) == 0u);
            const u32 idx = ld32(*m, mesh + 4);
            u32 v = 0, n = 0;
            bool ok = true;
            for (u32 y = 0; y < r; ++y, ++v)
                for (u32 x = 0; x < c; ++x, ++v) {
                    const u32 want[6] = {v, v + 1, v + c + 1, v + 1, v + c + 2, v + c + 1};
                    for (u32 w : want) ok &= ld16(*m, idx + 2 * n++) == w;
                }
            CHECK(ok);
            ++checks;
        }
    // (11) closing the analysis view (sub_2D1A10) clears gBtl +12 bit 0x2000 and nothing else
    for (u32 flags : {0u, 0x2000u, 0x6000u, 0x2040u, 0x4000u}) {
        const Fake f = fake_battle(*m, 1);
        st32(*m, f.btl + b3::gbtl::kFlags, flags);
        solo(*m, &rg::fn_sub_2D1A10_002d1a10, {0, 0, 0, 0});
        CHECK(ld32(*m, f.btl + b3::gbtl::kFlags) == (flags & ~0x2000u));
        ++checks;
    }
    MESSAGE("documented rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle5): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
