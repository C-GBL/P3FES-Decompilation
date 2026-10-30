// Phase 5 pair tests for slice battle6 (game/src/battle/battle6_*.cpp): every body against its recompiled body
// (__recomp) on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the
// cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack and every stray store),
// the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same
// deterministic heap behind the RwMalloc / RwFree slots, printf / sprintf, the H_Cdvd layer and the same recorders).
//
//   * random worlds (the p3fes_handgen skeleton's), every function;
//   * the replay snapshots, perturbed, by subsystem: b_5800 (a battle in state ACTION: live gBtl, btlActions, btlUnits,
//     DatUnits, packets and the battle panel works -- the panel and core functions), battle_ref_6150 (the result
//     screen: the hero / persona / parameter panels and the persona sequence), b20_climb_10850 / b20_climb_11200
//     (Shuffle Time: the camera list, the pose nodes, the cards and the cursor live), climb_ref_17000 (no battle: the
//     null paths). The perturbations follow the branches (the works' flag and step words, the units' fade / colour /
//     flag words, the actions' state words, the pose nodes' modes and dirty bits); the arguments are of the kind each
//     function takes (an action, a unit, a packet data block of its layout, a pose node of a consistent kind / mode
//     with real children, a camera record, a card, a staff roll line slot, the staff roll file image, ...);
//   * built worlds: the staff roll from the real DATA/OPED/ED_SR.BIN and ED_SR_F.BIN (the script object, the scroll
//     and resource works registered at their $gp slots), pose graphs of every kind and mode;
//   * documented rules on the host: the staff roll script layout and its command stream (one line command per string,
//     the cursor step per command), the pose nodes' kind / mode initialisers and the timed moves' velocity /
//     acceleration, Shuffle Time's card shuffle (a permutation of the slots), the motion length formula, the unit
//     packet creators' callbacks and data, the shake packet's decay / end rule, the tutorial's seen flags.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"
#include "p3fes/game/battle6.h"

#include <algorithm>
#include <cmath>
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
namespace b3 = p3fes::game::b3;
namespace b4 = p3fes::game::b4;
namespace b5 = p3fes::game::b5;
namespace b6 = p3fes::game::b6;

namespace p3fes::recomp_gen {
void fn_sub_242C20_00242c20(EEContext&);
void fn_sub_242C20_00242c20__recomp(EEContext&);
void fn_sub_243150_00243150(EEContext&);
void fn_sub_243150_00243150__recomp(EEContext&);
void fn_sub_244E80_00244e80(EEContext&);
void fn_sub_244E80_00244e80__recomp(EEContext&);
void fn_sub_2459D0_002459d0(EEContext&);
void fn_sub_2459D0_002459d0__recomp(EEContext&);
void fn_sub_245CD0_00245cd0(EEContext&);
void fn_sub_245CD0_00245cd0__recomp(EEContext&);
void fn_sub_248580_00248580(EEContext&);
void fn_sub_248580_00248580__recomp(EEContext&);
void fn_sub_249420_00249420(EEContext&);
void fn_sub_249420_00249420__recomp(EEContext&);
void fn_sub_24A6E0_0024a6e0(EEContext&);
void fn_sub_24A6E0_0024a6e0__recomp(EEContext&);
void fn_sub_24A750_0024a750(EEContext&);
void fn_sub_24A750_0024a750__recomp(EEContext&);
void fn_sub_24A7A0_0024a7a0(EEContext&);
void fn_sub_24A7A0_0024a7a0__recomp(EEContext&);
void fn_sub_2510D0_002510d0(EEContext&);
void fn_sub_2510D0_002510d0__recomp(EEContext&);
void fn_sub_2518B0_002518b0(EEContext&);
void fn_sub_2518B0_002518b0__recomp(EEContext&);
void fn_sub_251A20_00251a20(EEContext&);
void fn_sub_251A20_00251a20__recomp(EEContext&);
void fn_sub_251A80_00251a80(EEContext&);
void fn_sub_251A80_00251a80__recomp(EEContext&);
void fn_sub_251ED0_00251ed0(EEContext&);
void fn_sub_251ED0_00251ed0__recomp(EEContext&);
void fn_sub_251F40_00251f40(EEContext&);
void fn_sub_251F40_00251f40__recomp(EEContext&);
void fn_sub_266F60_00266f60(EEContext&);
void fn_sub_266F60_00266f60__recomp(EEContext&);
void fn_sub_267070_00267070(EEContext&);
void fn_sub_267070_00267070__recomp(EEContext&);
void fn_sub_267210_00267210(EEContext&);
void fn_sub_267210_00267210__recomp(EEContext&);
void fn_sub_27B9F0_0027b9f0(EEContext&);
void fn_sub_27B9F0_0027b9f0__recomp(EEContext&);
void fn_sub_27BA90_0027ba90(EEContext&);
void fn_sub_27BA90_0027ba90__recomp(EEContext&);
void fn_sub_27BAE0_0027bae0(EEContext&);
void fn_sub_27BAE0_0027bae0__recomp(EEContext&);
void fn_sub_24D160_0024d160(EEContext&);
void fn_sub_24D160_0024d160__recomp(EEContext&);
void fn_sub_24D1C0_0024d1c0(EEContext&);
void fn_sub_24D1C0_0024d1c0__recomp(EEContext&);
void fn_sub_24D280_0024d280(EEContext&);
void fn_sub_24D280_0024d280__recomp(EEContext&);
void fn_sub_24D2E0_0024d2e0(EEContext&);
void fn_sub_24D2E0_0024d2e0__recomp(EEContext&);
void fn_sub_24D3B0_0024d3b0(EEContext&);
void fn_sub_24D3B0_0024d3b0__recomp(EEContext&);
void fn_sub_24D430_0024d430(EEContext&);
void fn_sub_24D430_0024d430__recomp(EEContext&);
void fn_sub_24D4C0_0024d4c0(EEContext&);
void fn_sub_24D4C0_0024d4c0__recomp(EEContext&);
void fn_sub_24D5E0_0024d5e0(EEContext&);
void fn_sub_24D5E0_0024d5e0__recomp(EEContext&);
void fn_sub_24D7D0_0024d7d0(EEContext&);
void fn_sub_24D7D0_0024d7d0__recomp(EEContext&);
void fn_sub_24D8D0_0024d8d0(EEContext&);
void fn_sub_24D8D0_0024d8d0__recomp(EEContext&);
void fn_sub_24D940_0024d940(EEContext&);
void fn_sub_24D940_0024d940__recomp(EEContext&);
void fn_sub_24D9A0_0024d9a0(EEContext&);
void fn_sub_24D9A0_0024d9a0__recomp(EEContext&);
void fn_sub_24DA20_0024da20(EEContext&);
void fn_sub_24DA20_0024da20__recomp(EEContext&);
void fn_sub_24DB90_0024db90(EEContext&);
void fn_sub_24DB90_0024db90__recomp(EEContext&);
void fn_sub_24DC10_0024dc10(EEContext&);
void fn_sub_24DC10_0024dc10__recomp(EEContext&);
void fn_sub_24DC90_0024dc90(EEContext&);
void fn_sub_24DC90_0024dc90__recomp(EEContext&);
void fn_sub_24F210_0024f210(EEContext&);
void fn_sub_24F210_0024f210__recomp(EEContext&);
void fn_sub_24F2C0_0024f2c0(EEContext&);
void fn_sub_24F2C0_0024f2c0__recomp(EEContext&);
void fn_sub_24F350_0024f350(EEContext&);
void fn_sub_24F350_0024f350__recomp(EEContext&);
void fn_sub_24F410_0024f410(EEContext&);
void fn_sub_24F410_0024f410__recomp(EEContext&);
void fn_sub_24F780_0024f780(EEContext&);
void fn_sub_24F780_0024f780__recomp(EEContext&);
void fn_sub_24F7F0_0024f7f0(EEContext&);
void fn_sub_24F7F0_0024f7f0__recomp(EEContext&);
void fn_sub_24FAA0_0024faa0(EEContext&);
void fn_sub_24FAA0_0024faa0__recomp(EEContext&);
void fn_sub_24FBA0_0024fba0(EEContext&);
void fn_sub_24FBA0_0024fba0__recomp(EEContext&);
void fn_sub_24FC40_0024fc40(EEContext&);
void fn_sub_24FC40_0024fc40__recomp(EEContext&);
void fn_sub_24FD10_0024fd10(EEContext&);
void fn_sub_24FD10_0024fd10__recomp(EEContext&);
void fn_sub_24FD20_0024fd20(EEContext&);
void fn_sub_24FD20_0024fd20__recomp(EEContext&);
void fn_sub_24FD40_0024fd40(EEContext&);
void fn_sub_24FD40_0024fd40__recomp(EEContext&);
void fn_sub_24FD80_0024fd80(EEContext&);
void fn_sub_24FD80_0024fd80__recomp(EEContext&);
void fn_sub_24FDC0_0024fdc0(EEContext&);
void fn_sub_24FDC0_0024fdc0__recomp(EEContext&);
void fn_sub_24FE20_0024fe20(EEContext&);
void fn_sub_24FE20_0024fe20__recomp(EEContext&);
void fn_sub_24FE40_0024fe40(EEContext&);
void fn_sub_24FE40_0024fe40__recomp(EEContext&);
void fn_sub_24FF10_0024ff10(EEContext&);
void fn_sub_24FF10_0024ff10__recomp(EEContext&);
void fn_sub_250280_00250280(EEContext&);
void fn_sub_250280_00250280__recomp(EEContext&);
void fn_sub_2503F0_002503f0(EEContext&);
void fn_sub_2503F0_002503f0__recomp(EEContext&);
void fn_sub_250480_00250480(EEContext&);
void fn_sub_250480_00250480__recomp(EEContext&);
void fn_sub_250500_00250500(EEContext&);
void fn_sub_250500_00250500__recomp(EEContext&);
void fn_sub_2505B0_002505b0(EEContext&);
void fn_sub_2505B0_002505b0__recomp(EEContext&);
void fn_sub_2508C0_002508c0(EEContext&);
void fn_sub_2508C0_002508c0__recomp(EEContext&);
void fn_sub_250A30_00250a30(EEContext&);
void fn_sub_250A30_00250a30__recomp(EEContext&);
void fn_sub_250B90_00250b90(EEContext&);
void fn_sub_250B90_00250b90__recomp(EEContext&);
void fn_sub_250BE0_00250be0(EEContext&);
void fn_sub_250BE0_00250be0__recomp(EEContext&);
void fn_sub_250C70_00250c70(EEContext&);
void fn_sub_250C70_00250c70__recomp(EEContext&);
void fn_sub_250E70_00250e70(EEContext&);
void fn_sub_250E70_00250e70__recomp(EEContext&);
void fn_sub_250EF0_00250ef0(EEContext&);
void fn_sub_250EF0_00250ef0__recomp(EEContext&);
void fn_sub_250F80_00250f80(EEContext&);
void fn_sub_250F80_00250f80__recomp(EEContext&);
void fn_sub_251010_00251010(EEContext&);
void fn_sub_251010_00251010__recomp(EEContext&);
void fn_sub_251030_00251030(EEContext&);
void fn_sub_251030_00251030__recomp(EEContext&);
void fn_sub_253A40_00253a40(EEContext&);
void fn_sub_253A40_00253a40__recomp(EEContext&);
void fn_sub_2564C0_002564c0(EEContext&);
void fn_sub_2564C0_002564c0__recomp(EEContext&);
void fn_sub_258B40_00258b40(EEContext&);
void fn_sub_258B40_00258b40__recomp(EEContext&);
void fn_sub_25A130_0025a130(EEContext&);
void fn_sub_25A130_0025a130__recomp(EEContext&);
void fn_sub_25A440_0025a440(EEContext&);
void fn_sub_25A440_0025a440__recomp(EEContext&);
void fn_sub_25A7D0_0025a7d0(EEContext&);
void fn_sub_25A7D0_0025a7d0__recomp(EEContext&);
void fn_sub_260A50_00260a50(EEContext&);
void fn_sub_260A50_00260a50__recomp(EEContext&);
void fn_sub_261480_00261480(EEContext&);
void fn_sub_261480_00261480__recomp(EEContext&);
void fn_sub_27BC00_0027bc00(EEContext&);
void fn_sub_27BC00_0027bc00__recomp(EEContext&);
void fn_sub_27BD10_0027bd10(EEContext&);
void fn_sub_27BD10_0027bd10__recomp(EEContext&);
void fn_sub_27BDF0_0027bdf0(EEContext&);
void fn_sub_27BDF0_0027bdf0__recomp(EEContext&);
void fn_sub_27BF60_0027bf60(EEContext&);
void fn_sub_27BF60_0027bf60__recomp(EEContext&);
void fn_sub_27BFB0_0027bfb0(EEContext&);
void fn_sub_27BFB0_0027bfb0__recomp(EEContext&);
void fn_sub_24AC90_0024ac90(EEContext&);
void fn_sub_24AC90_0024ac90__recomp(EEContext&);
void fn_sub_24BA50_0024ba50(EEContext&);
void fn_sub_24BA50_0024ba50__recomp(EEContext&);
void fn_sub_24BB30_0024bb30(EEContext&);
void fn_sub_24BB30_0024bb30__recomp(EEContext&);
void fn_sub_24BF80_0024bf80(EEContext&);
void fn_sub_24BF80_0024bf80__recomp(EEContext&);
void fn_sub_25D8A0_0025d8a0(EEContext&);
void fn_sub_25D8A0_0025d8a0__recomp(EEContext&);
void fn_sub_25D9E0_0025d9e0(EEContext&);
void fn_sub_25D9E0_0025d9e0__recomp(EEContext&);
void fn_sub_25DA30_0025da30(EEContext&);
void fn_sub_25DA30_0025da30__recomp(EEContext&);
void fn_sub_25ED40_0025ed40(EEContext&);
void fn_sub_25ED40_0025ed40__recomp(EEContext&);
void fn_brItem_UpdateStockOverBgTask_0025f4a0(EEContext&);
void fn_brItem_UpdateStockOverBgTask_0025f4a0__recomp(EEContext&);
void fn_sub_25F510_0025f510(EEContext&);
void fn_sub_25F510_0025f510__recomp(EEContext&);
void fn_sub_262790_00262790(EEContext&);
void fn_sub_262790_00262790__recomp(EEContext&);
void fn_sub_263170_00263170(EEContext&);
void fn_sub_263170_00263170__recomp(EEContext&);
void fn_sub_263DB0_00263db0(EEContext&);
void fn_sub_263DB0_00263db0__recomp(EEContext&);
void fn_sub_264EF0_00264ef0(EEContext&);
void fn_sub_264EF0_00264ef0__recomp(EEContext&);
void fn_sub_272810_00272810(EEContext&);
void fn_sub_272810_00272810__recomp(EEContext&);
void fn_sub_273C00_00273c00(EEContext&);
void fn_sub_273C00_00273c00__recomp(EEContext&);
void fn_sub_273C70_00273c70(EEContext&);
void fn_sub_273C70_00273c70__recomp(EEContext&);
void fn_sub_273D50_00273d50(EEContext&);
void fn_sub_273D50_00273d50__recomp(EEContext&);
void fn_sub_274100_00274100(EEContext&);
void fn_sub_274100_00274100__recomp(EEContext&);
void fn_sub_275440_00275440(EEContext&);
void fn_sub_275440_00275440__recomp(EEContext&);
void fn_sub_275520_00275520(EEContext&);
void fn_sub_275520_00275520__recomp(EEContext&);
void fn_sub_2755D0_002755d0(EEContext&);
void fn_sub_2755D0_002755d0__recomp(EEContext&);
void fn_sub_275670_00275670(EEContext&);
void fn_sub_275670_00275670__recomp(EEContext&);
void fn_sub_2756C0_002756c0(EEContext&);
void fn_sub_2756C0_002756c0__recomp(EEContext&);
void fn_sub_2757A0_002757a0(EEContext&);
void fn_sub_2757A0_002757a0__recomp(EEContext&);
void fn_sub_2757E0_002757e0(EEContext&);
void fn_sub_2757E0_002757e0__recomp(EEContext&);
void fn_sub_2758E0_002758e0(EEContext&);
void fn_sub_2758E0_002758e0__recomp(EEContext&);
void fn_sub_2768C0_002768c0(EEContext&);
void fn_sub_2768C0_002768c0__recomp(EEContext&);
void fn_sub_276A80_00276a80(EEContext&);
void fn_sub_276A80_00276a80__recomp(EEContext&);
void fn_sub_276B10_00276b10(EEContext&);
void fn_sub_276B10_00276b10__recomp(EEContext&);
void fn_sub_276C30_00276c30(EEContext&);
void fn_sub_276C30_00276c30__recomp(EEContext&);
void fn_sub_2771F0_002771f0(EEContext&);
void fn_sub_2771F0_002771f0__recomp(EEContext&);
void fn_sub_278550_00278550(EEContext&);
void fn_sub_278550_00278550__recomp(EEContext&);
void fn_sub_279940_00279940(EEContext&);
void fn_sub_279940_00279940__recomp(EEContext&);
void fn_sub_279AC0_00279ac0(EEContext&);
void fn_sub_279AC0_00279ac0__recomp(EEContext&);
void fn_sub_279AF0_00279af0(EEContext&);
void fn_sub_279AF0_00279af0__recomp(EEContext&);
void fn_sub_279B10_00279b10(EEContext&);
void fn_sub_279B10_00279b10__recomp(EEContext&);
void fn_sub_279B20_00279b20(EEContext&);
void fn_sub_279B20_00279b20__recomp(EEContext&);
void fn_sub_279B30_00279b30(EEContext&);
void fn_sub_279B30_00279b30__recomp(EEContext&);
void fn_sub_279BF0_00279bf0(EEContext&);
void fn_sub_279BF0_00279bf0__recomp(EEContext&);
void fn_sub_279C90_00279c90(EEContext&);
void fn_sub_279C90_00279c90__recomp(EEContext&);
void fn_sub_279D10_00279d10(EEContext&);
void fn_sub_279D10_00279d10__recomp(EEContext&);
void fn_sub_279D60_00279d60(EEContext&);
void fn_sub_279D60_00279d60__recomp(EEContext&);
void fn_sub_27A3B0_0027a3b0(EEContext&);
void fn_sub_27A3B0_0027a3b0__recomp(EEContext&);
void fn_sub_27A4A0_0027a4a0(EEContext&);
void fn_sub_27A4A0_0027a4a0__recomp(EEContext&);
void fn_sub_27A560_0027a560(EEContext&);
void fn_sub_27A560_0027a560__recomp(EEContext&);
void fn_sub_27A5D0_0027a5d0(EEContext&);
void fn_sub_27A5D0_0027a5d0__recomp(EEContext&);
void fn_sub_27A6A0_0027a6a0(EEContext&);
void fn_sub_27A6A0_0027a6a0__recomp(EEContext&);
void fn_sub_27A930_0027a930(EEContext&);
void fn_sub_27A930_0027a930__recomp(EEContext&);
void fn_sub_27AA00_0027aa00(EEContext&);
void fn_sub_27AA00_0027aa00__recomp(EEContext&);
void fn_sub_27AAA0_0027aaa0(EEContext&);
void fn_sub_27AAA0_0027aaa0__recomp(EEContext&);
void fn_sub_27AB10_0027ab10(EEContext&);
void fn_sub_27AB10_0027ab10__recomp(EEContext&);
void fn_sub_27AB80_0027ab80(EEContext&);
void fn_sub_27AB80_0027ab80__recomp(EEContext&);
void fn_sub_27AC60_0027ac60(EEContext&);
void fn_sub_27AC60_0027ac60__recomp(EEContext&);
void fn_sub_27AC80_0027ac80(EEContext&);
void fn_sub_27AC80_0027ac80__recomp(EEContext&);
void fn_sub_27ACE0_0027ace0(EEContext&);
void fn_sub_27ACE0_0027ace0__recomp(EEContext&);
void fn_sub_27AE90_0027ae90(EEContext&);
void fn_sub_27AE90_0027ae90__recomp(EEContext&);
void fn_sub_27AF80_0027af80(EEContext&);
void fn_sub_27AF80_0027af80__recomp(EEContext&);
void fn_sub_27AFD0_0027afd0(EEContext&);
void fn_sub_27AFD0_0027afd0__recomp(EEContext&);
void fn_sub_27B070_0027b070(EEContext&);
void fn_sub_27B070_0027b070__recomp(EEContext&);
void fn_sub_27B0B0_0027b0b0(EEContext&);
void fn_sub_27B0B0_0027b0b0__recomp(EEContext&);
void fn_sub_27B200_0027b200(EEContext&);
void fn_sub_27B200_0027b200__recomp(EEContext&);
void fn_sub_27B2B0_0027b2b0(EEContext&);
void fn_sub_27B2B0_0027b2b0__recomp(EEContext&);
void fn_sub_27B3F0_0027b3f0(EEContext&);
void fn_sub_27B3F0_0027b3f0__recomp(EEContext&);
void fn_sub_27B460_0027b460(EEContext&);
void fn_sub_27B460_0027b460__recomp(EEContext&);
void fn_sub_280200_00280200(EEContext&);
void fn_sub_280200_00280200__recomp(EEContext&);
void fn_sub_283750_00283750(EEContext&);
void fn_sub_283750_00283750__recomp(EEContext&);
void fn_sub_284470_00284470(EEContext&);
void fn_sub_284470_00284470__recomp(EEContext&);
void fn_sub_284690_00284690(EEContext&);
void fn_sub_284690_00284690__recomp(EEContext&);
void fn_sub_284D10_00284d10(EEContext&);
void fn_sub_284D10_00284d10__recomp(EEContext&);
void fn_sub_284D60_00284d60(EEContext&);
void fn_sub_284D60_00284d60__recomp(EEContext&);
void fn_sub_284D80_00284d80(EEContext&);
void fn_sub_284D80_00284d80__recomp(EEContext&);
void fn_sub_285DE0_00285de0(EEContext&);
void fn_sub_285DE0_00285de0__recomp(EEContext&);
void fn_sub_285E00_00285e00(EEContext&);
void fn_sub_285E00_00285e00__recomp(EEContext&);
void fn_sub_285E30_00285e30(EEContext&);
void fn_sub_285E30_00285e30__recomp(EEContext&);
void fn_sub_285E50_00285e50(EEContext&);
void fn_sub_285E50_00285e50__recomp(EEContext&);
void fn_sub_285EB0_00285eb0(EEContext&);
void fn_sub_285EB0_00285eb0__recomp(EEContext&);
void fn_sub_285ED0_00285ed0(EEContext&);
void fn_sub_285ED0_00285ed0__recomp(EEContext&);
void fn_sub_285F00_00285f00(EEContext&);
void fn_sub_285F00_00285f00__recomp(EEContext&);
void fn_sub_285F20_00285f20(EEContext&);
void fn_sub_285F20_00285f20__recomp(EEContext&);
void fn_sub_286380_00286380(EEContext&);
void fn_sub_286380_00286380__recomp(EEContext&);
void fn_sub_2863F0_002863f0(EEContext&);
void fn_sub_2863F0_002863f0__recomp(EEContext&);
void fn_sub_286480_00286480(EEContext&);
void fn_sub_286480_00286480__recomp(EEContext&);
void fn_sub_2864A0_002864a0(EEContext&);
void fn_sub_2864A0_002864a0__recomp(EEContext&);
void fn_sub_286540_00286540(EEContext&);
void fn_sub_286540_00286540__recomp(EEContext&);
void fn_sub_287860_00287860(EEContext&);
void fn_sub_287860_00287860__recomp(EEContext&);
void fn_sub_28B230_0028b230(EEContext&);
void fn_sub_28B230_0028b230__recomp(EEContext&);
void fn_sub_28CA00_0028ca00(EEContext&);
void fn_sub_28CA00_0028ca00__recomp(EEContext&);
void fn_sub_28CF20_0028cf20(EEContext&);
void fn_sub_28CF20_0028cf20__recomp(EEContext&);
void fn_sub_28CF80_0028cf80(EEContext&);
void fn_sub_28CF80_0028cf80__recomp(EEContext&);
void fn_sub_28D080_0028d080(EEContext&);
void fn_sub_28D080_0028d080__recomp(EEContext&);
void fn_datGetFlag_0016f190(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions, their argument kinds ($a0..$a3, then $t0..$t2) and their group ---------------------------------
// A btlAction   U btlUnit   D unit packet data {unit, u16, u16, u16 flags, s32 started}   H shake packet data {unit,
// f32 amplitude, count}   J hop packet data {f32 start[3], unit, u16 frames, u16 step, f32 t}   B a bpc entry
// W a work-sized block   N a pose node (consistent kind / mode, real children)   C a Shuffle Time camera record
// X an RW camera {+4 a frame}   R a Shuffle Time card   L a staff roll line slot   F the staff roll file image
// S a staff roll script object   Y a staff roll scroll work block   Z a staff roll resource work block   T a task
// {+60 a heap block}   K a 'persona grow' pack (3 entries)   v f32[3]   q f32[4]   o an out buffer   t a short text
// k persona id   m motion   u u16   i index 0..2   b 0 / 1   n small 0..7   F frames
// Groups: p panel, s Shuffle Time, r result screen, e staff roll, c battle core.
struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
    char group;
};
const Case kCases[] = {
    {"sub_242C20", 0x242C20u, &rg::fn_sub_242C20_00242c20, &rg::fn_sub_242C20_00242c20__recomp, "Wuu", 'p'},
    {"sub_243150", 0x243150u, &rg::fn_sub_243150_00243150, &rg::fn_sub_243150_00243150__recomp, "", 'p'},
    {"sub_244E80", 0x244E80u, &rg::fn_sub_244E80_00244e80, &rg::fn_sub_244E80_00244e80__recomp, "", 'p'},
    {"sub_2459D0", 0x2459D0u, &rg::fn_sub_2459D0_002459d0, &rg::fn_sub_2459D0_002459d0__recomp, "B", 'p'},
    {"sub_245CD0", 0x245CD0u, &rg::fn_sub_245CD0_00245cd0, &rg::fn_sub_245CD0_00245cd0__recomp, "", 'p'},
    {"sub_248580", 0x248580u, &rg::fn_sub_248580_00248580, &rg::fn_sub_248580_00248580__recomp, "nu", 'p'},
    {"sub_249420", 0x249420u, &rg::fn_sub_249420_00249420, &rg::fn_sub_249420_00249420__recomp, "nii", 'p'},
    {"sub_24A6E0", 0x24A6E0u, &rg::fn_sub_24A6E0_0024a6e0, &rg::fn_sub_24A6E0_0024a6e0__recomp, "n", 'p'},
    {"sub_24A750", 0x24A750u, &rg::fn_sub_24A750_0024a750, &rg::fn_sub_24A750_0024a750__recomp, "", 'p'},
    {"sub_24A7A0", 0x24A7A0u, &rg::fn_sub_24A7A0_0024a7a0, &rg::fn_sub_24A7A0_0024a7a0__recomp, "", 'p'},
    {"sub_2510D0", 0x2510D0u, &rg::fn_sub_2510D0_002510d0, &rg::fn_sub_2510D0_002510d0__recomp, "", 'p'},
    {"sub_2518B0", 0x2518B0u, &rg::fn_sub_2518B0_002518b0, &rg::fn_sub_2518B0_002518b0__recomp, "i", 'p'},
    {"sub_251A20", 0x251A20u, &rg::fn_sub_251A20_00251a20, &rg::fn_sub_251A20_00251a20__recomp, "", 'p'},
    {"sub_251A80", 0x251A80u, &rg::fn_sub_251A80_00251a80, &rg::fn_sub_251A80_00251a80__recomp, "", 'p'},
    {"sub_251ED0", 0x251ED0u, &rg::fn_sub_251ED0_00251ed0, &rg::fn_sub_251ED0_00251ed0__recomp, "", 'p'},
    {"sub_251F40", 0x251F40u, &rg::fn_sub_251F40_00251f40, &rg::fn_sub_251F40_00251f40__recomp, "b", 'p'},
    {"sub_266F60", 0x266F60u, &rg::fn_sub_266F60_00266f60, &rg::fn_sub_266F60_00266f60__recomp, "k", 'p'},
    {"sub_267070", 0x267070u, &rg::fn_sub_267070_00267070, &rg::fn_sub_267070_00267070__recomp, "k", 'p'},
    {"sub_267210", 0x267210u, &rg::fn_sub_267210_00267210, &rg::fn_sub_267210_00267210__recomp, "", 'p'},
    {"sub_27B9F0", 0x27B9F0u, &rg::fn_sub_27B9F0_0027b9f0, &rg::fn_sub_27B9F0_0027b9f0__recomp, "", 'p'},
    {"sub_27BA90", 0x27BA90u, &rg::fn_sub_27BA90_0027ba90, &rg::fn_sub_27BA90_0027ba90__recomp, "", 'p'},
    {"sub_27BAE0", 0x27BAE0u, &rg::fn_sub_27BAE0_0027bae0, &rg::fn_sub_27BAE0_0027bae0__recomp, "v", 'p'},
    {"sub_24D160", 0x24D160u, &rg::fn_sub_24D160_0024d160, &rg::fn_sub_24D160_0024d160__recomp, "", 's'},
    {"sub_24D1C0", 0x24D1C0u, &rg::fn_sub_24D1C0_0024d1c0, &rg::fn_sub_24D1C0_0024d1c0__recomp, "", 's'},
    {"sub_24D280", 0x24D280u, &rg::fn_sub_24D280_0024d280, &rg::fn_sub_24D280_0024d280__recomp, "W", 's'},
    {"sub_24D2E0", 0x24D2E0u, &rg::fn_sub_24D2E0_0024d2e0, &rg::fn_sub_24D2E0_0024d2e0__recomp, "uC", 's'},
    {"sub_24D3B0", 0x24D3B0u, &rg::fn_sub_24D3B0_0024d3b0, &rg::fn_sub_24D3B0_0024d3b0__recomp, "u", 's'},
    {"sub_24D430", 0x24D430u, &rg::fn_sub_24D430_0024d430, &rg::fn_sub_24D430_0024d430__recomp, "u", 's'},
    {"sub_24D4C0", 0x24D4C0u, &rg::fn_sub_24D4C0_0024d4c0, &rg::fn_sub_24D4C0_0024d4c0__recomp, "u", 's'},
    {"sub_24D5E0", 0x24D5E0u, &rg::fn_sub_24D5E0_0024d5e0, &rg::fn_sub_24D5E0_0024d5e0__recomp, "C", 's'},
    {"sub_24D7D0", 0x24D7D0u, &rg::fn_sub_24D7D0_0024d7d0, &rg::fn_sub_24D7D0_0024d7d0__recomp, "XC", 's'},
    {"sub_24D8D0", 0x24D8D0u, &rg::fn_sub_24D8D0_0024d8d0, &rg::fn_sub_24D8D0_0024d8d0__recomp, "C", 's'},
    {"sub_24D940", 0x24D940u, &rg::fn_sub_24D940_0024d940, &rg::fn_sub_24D940_0024d940__recomp, "CN", 's'},
    {"sub_24D9A0", 0x24D9A0u, &rg::fn_sub_24D9A0_0024d9a0, &rg::fn_sub_24D9A0_0024d9a0__recomp, "CN", 's'},
    {"sub_24DA20", 0x24DA20u, &rg::fn_sub_24DA20_0024da20, &rg::fn_sub_24DA20_0024da20__recomp, "", 's'},
    {"sub_24DB90", 0x24DB90u, &rg::fn_sub_24DB90_0024db90, &rg::fn_sub_24DB90_0024db90__recomp, "", 's'},
    {"sub_24DC10", 0x24DC10u, &rg::fn_sub_24DC10_0024dc10, &rg::fn_sub_24DC10_0024dc10__recomp, "", 's'},
    {"sub_24DC90", 0x24DC90u, &rg::fn_sub_24DC90_0024dc90, &rg::fn_sub_24DC90_0024dc90__recomp, "N", 's'},
    {"sub_24F210", 0x24F210u, &rg::fn_sub_24F210_0024f210, &rg::fn_sub_24F210_0024f210__recomp, "Nn", 's'},
    {"sub_24F2C0", 0x24F2C0u, &rg::fn_sub_24F2C0_0024f2c0, &rg::fn_sub_24F2C0_0024f2c0__recomp, "N", 's'},
    {"sub_24F350", 0x24F350u, &rg::fn_sub_24F350_0024f350, &rg::fn_sub_24F350_0024f350__recomp, "N", 's'},
    {"sub_24F410", 0x24F410u, &rg::fn_sub_24F410_0024f410, &rg::fn_sub_24F410_0024f410__recomp, "N", 's'},
    {"sub_24F780", 0x24F780u, &rg::fn_sub_24F780_0024f780, &rg::fn_sub_24F780_0024f780__recomp, "N", 's'},
    {"sub_24F7F0", 0x24F7F0u, &rg::fn_sub_24F7F0_0024f7f0, &rg::fn_sub_24F7F0_0024f7f0__recomp, "Nv", 's'},
    {"sub_24FAA0", 0x24FAA0u, &rg::fn_sub_24FAA0_0024faa0, &rg::fn_sub_24FAA0_0024faa0__recomp, "N", 's'},
    {"sub_24FBA0", 0x24FBA0u, &rg::fn_sub_24FBA0_0024fba0, &rg::fn_sub_24FBA0_0024fba0__recomp, "No", 's'},
    {"sub_24FC40", 0x24FC40u, &rg::fn_sub_24FC40_0024fc40, &rg::fn_sub_24FC40_0024fc40__recomp, "Nq", 's'},
    {"sub_24FD10", 0x24FD10u, &rg::fn_sub_24FD10_0024fd10, &rg::fn_sub_24FD10_0024fd10__recomp, "N", 's'},
    {"sub_24FD20", 0x24FD20u, &rg::fn_sub_24FD20_0024fd20, &rg::fn_sub_24FD20_0024fd20__recomp, "N", 's'},
    {"sub_24FD40", 0x24FD40u, &rg::fn_sub_24FD40_0024fd40, &rg::fn_sub_24FD40_0024fd40__recomp, "N", 's'},
    {"sub_24FD80", 0x24FD80u, &rg::fn_sub_24FD80_0024fd80, &rg::fn_sub_24FD80_0024fd80__recomp, "N", 's'},
    {"sub_24FDC0", 0x24FDC0u, &rg::fn_sub_24FDC0_0024fdc0, &rg::fn_sub_24FDC0_0024fdc0__recomp, "N", 's'},
    {"sub_24FE20", 0x24FE20u, &rg::fn_sub_24FE20_0024fe20, &rg::fn_sub_24FE20_0024fe20__recomp, "N", 's'},
    {"sub_24FE40", 0x24FE40u, &rg::fn_sub_24FE40_0024fe40, &rg::fn_sub_24FE40_0024fe40__recomp, "N", 's'},
    {"sub_24FF10", 0x24FF10u, &rg::fn_sub_24FF10_0024ff10, &rg::fn_sub_24FF10_0024ff10__recomp, "N", 's'},
    {"sub_250280", 0x250280u, &rg::fn_sub_250280_00250280, &rg::fn_sub_250280_00250280__recomp, "Nv", 's'},
    {"sub_2503F0", 0x2503F0u, &rg::fn_sub_2503F0_002503f0, &rg::fn_sub_2503F0_002503f0__recomp, "NiN", 's'},
    {"sub_250480", 0x250480u, &rg::fn_sub_250480_00250480, &rg::fn_sub_250480_00250480__recomp, "N", 's'},
    {"sub_250500", 0x250500u, &rg::fn_sub_250500_00250500, &rg::fn_sub_250500_00250500__recomp, "NvF", 's'},
    {"sub_2505B0", 0x2505B0u, &rg::fn_sub_2505B0_002505b0, &rg::fn_sub_2505B0_002505b0__recomp, "NvFv", 's'},
    {"sub_2508C0", 0x2508C0u, &rg::fn_sub_2508C0_002508c0, &rg::fn_sub_2508C0_002508c0__recomp, "NvF", 's'},
    {"sub_250A30", 0x250A30u, &rg::fn_sub_250A30_00250a30, &rg::fn_sub_250A30_00250a30__recomp, "NvF", 's'},
    {"sub_250B90", 0x250B90u, &rg::fn_sub_250B90_00250b90, &rg::fn_sub_250B90_00250b90__recomp, "N", 's'},
    {"sub_250BE0", 0x250BE0u, &rg::fn_sub_250BE0_00250be0, &rg::fn_sub_250BE0_00250be0__recomp, "NiN", 's'},
    {"sub_250C70", 0x250C70u, &rg::fn_sub_250C70_00250c70, &rg::fn_sub_250C70_00250c70__recomp, "N", 's'},
    {"sub_250E70", 0x250E70u, &rg::fn_sub_250E70_00250e70, &rg::fn_sub_250E70_00250e70__recomp, "N", 's'},
    {"sub_250EF0", 0x250EF0u, &rg::fn_sub_250EF0_00250ef0, &rg::fn_sub_250EF0_00250ef0__recomp, "N", 's'},
    {"sub_250F80", 0x250F80u, &rg::fn_sub_250F80_00250f80, &rg::fn_sub_250F80_00250f80__recomp, "ov", 's'},
    {"sub_251010", 0x251010u, &rg::fn_sub_251010_00251010, &rg::fn_sub_251010_00251010__recomp, "NF", 's'},
    {"sub_251030", 0x251030u, &rg::fn_sub_251030_00251030, &rg::fn_sub_251030_00251030__recomp, "N", 's'},
    {"sub_253A40", 0x253A40u, &rg::fn_sub_253A40_00253a40, &rg::fn_sub_253A40_00253a40__recomp, "", 's'},
    {"sub_2564C0", 0x2564C0u, &rg::fn_sub_2564C0_002564c0, &rg::fn_sub_2564C0_002564c0__recomp, "R", 's'},
    {"sub_258B40", 0x258B40u, &rg::fn_sub_258B40_00258b40, &rg::fn_sub_258B40_00258b40__recomp, "", 's'},
    {"sub_25A130", 0x25A130u, &rg::fn_sub_25A130_0025a130, &rg::fn_sub_25A130_0025a130__recomp, "", 's'},
    {"sub_25A440", 0x25A440u, &rg::fn_sub_25A440_0025a440, &rg::fn_sub_25A440_0025a440__recomp, "", 's'},
    {"sub_25A7D0", 0x25A7D0u, &rg::fn_sub_25A7D0_0025a7d0, &rg::fn_sub_25A7D0_0025a7d0__recomp, "", 's'},
    {"sub_260A50", 0x260A50u, &rg::fn_sub_260A50_00260a50, &rg::fn_sub_260A50_00260a50__recomp, "", 's'},
    {"sub_261480", 0x261480u, &rg::fn_sub_261480_00261480, &rg::fn_sub_261480_00261480__recomp, "", 's'},
    {"sub_27BC00", 0x27BC00u, &rg::fn_sub_27BC00_0027bc00, &rg::fn_sub_27BC00_0027bc00__recomp, "k", 's'},
    {"sub_27BD10", 0x27BD10u, &rg::fn_sub_27BD10_0027bd10, &rg::fn_sub_27BD10_0027bd10__recomp, "k", 's'},
    {"sub_27BDF0", 0x27BDF0u, &rg::fn_sub_27BDF0_0027bdf0, &rg::fn_sub_27BDF0_0027bdf0__recomp, "", 's'},
    {"sub_27BF60", 0x27BF60u, &rg::fn_sub_27BF60_0027bf60, &rg::fn_sub_27BF60_0027bf60__recomp, "", 's'},
    {"sub_27BFB0", 0x27BFB0u, &rg::fn_sub_27BFB0_0027bfb0, &rg::fn_sub_27BFB0_0027bfb0__recomp, "", 's'},
    {"sub_24AC90", 0x24AC90u, &rg::fn_sub_24AC90_0024ac90, &rg::fn_sub_24AC90_0024ac90__recomp, "", 'r'},
    {"sub_24BA50", 0x24BA50u, &rg::fn_sub_24BA50_0024ba50, &rg::fn_sub_24BA50_0024ba50__recomp, "", 'r'},
    {"sub_24BB30", 0x24BB30u, &rg::fn_sub_24BB30_0024bb30, &rg::fn_sub_24BB30_0024bb30__recomp, "", 'r'},
    {"sub_24BF80", 0x24BF80u, &rg::fn_sub_24BF80_0024bf80, &rg::fn_sub_24BF80_0024bf80__recomp, "", 'r'},
    {"sub_25D8A0", 0x25D8A0u, &rg::fn_sub_25D8A0_0025d8a0, &rg::fn_sub_25D8A0_0025d8a0__recomp, "W", 'r'},
    {"sub_25D9E0", 0x25D9E0u, &rg::fn_sub_25D9E0_0025d9e0, &rg::fn_sub_25D9E0_0025d9e0__recomp, "", 'r'},
    {"sub_25DA30", 0x25DA30u, &rg::fn_sub_25DA30_0025da30, &rg::fn_sub_25DA30_0025da30__recomp, "", 'r'},
    {"sub_25ED40", 0x25ED40u, &rg::fn_sub_25ED40_0025ed40, &rg::fn_sub_25ED40_0025ed40__recomp, "", 'r'},
    {"brItem_UpdateStockOverBgTask", 0x25F4A0u, &rg::fn_brItem_UpdateStockOverBgTask_0025f4a0, &rg::fn_brItem_UpdateStockOverBgTask_0025f4a0__recomp, "", 'r'},
    {"sub_25F510", 0x25F510u, &rg::fn_sub_25F510_0025f510, &rg::fn_sub_25F510_0025f510__recomp, "T", 'r'},
    {"sub_262790", 0x262790u, &rg::fn_sub_262790_00262790, &rg::fn_sub_262790_00262790__recomp, "", 'r'},
    {"sub_263170", 0x263170u, &rg::fn_sub_263170_00263170, &rg::fn_sub_263170_00263170__recomp, "", 'r'},
    {"sub_263DB0", 0x263DB0u, &rg::fn_sub_263DB0_00263db0, &rg::fn_sub_263DB0_00263db0__recomp, "", 'r'},
    {"sub_264EF0", 0x264EF0u, &rg::fn_sub_264EF0_00264ef0, &rg::fn_sub_264EF0_00264ef0__recomp, "k", 'r'},
    {"sub_272810", 0x272810u, &rg::fn_sub_272810_00272810, &rg::fn_sub_272810_00272810__recomp, "", 'r'},
    {"sub_273C00", 0x273C00u, &rg::fn_sub_273C00_00273c00, &rg::fn_sub_273C00_00273c00__recomp, "", 'r'},
    {"sub_273C70", 0x273C70u, &rg::fn_sub_273C70_00273c70, &rg::fn_sub_273C70_00273c70__recomp, "", 'r'},
    {"sub_273D50", 0x273D50u, &rg::fn_sub_273D50_00273d50, &rg::fn_sub_273D50_00273d50__recomp, "", 'r'},
    {"sub_274100", 0x274100u, &rg::fn_sub_274100_00274100, &rg::fn_sub_274100_00274100__recomp, "", 'r'},
    {"sub_275440", 0x275440u, &rg::fn_sub_275440_00275440, &rg::fn_sub_275440_00275440__recomp, "", 'r'},
    {"sub_275520", 0x275520u, &rg::fn_sub_275520_00275520, &rg::fn_sub_275520_00275520__recomp, "", 'r'},
    {"sub_2755D0", 0x2755D0u, &rg::fn_sub_2755D0_002755d0, &rg::fn_sub_2755D0_002755d0__recomp, "W", 'r'},
    {"sub_275670", 0x275670u, &rg::fn_sub_275670_00275670, &rg::fn_sub_275670_00275670__recomp, "", 'r'},
    {"sub_2756C0", 0x2756C0u, &rg::fn_sub_2756C0_002756c0, &rg::fn_sub_2756C0_002756c0__recomp, "", 'r'},
    {"sub_2757A0", 0x2757A0u, &rg::fn_sub_2757A0_002757a0, &rg::fn_sub_2757A0_002757a0__recomp, "", 'r'},
    {"sub_2757E0", 0x2757E0u, &rg::fn_sub_2757E0_002757e0, &rg::fn_sub_2757E0_002757e0__recomp, "K", 'r'},
    {"sub_2758E0", 0x2758E0u, &rg::fn_sub_2758E0_002758e0, &rg::fn_sub_2758E0_002758e0__recomp, "nk", 'r'},
    {"sub_2768C0", 0x2768C0u, &rg::fn_sub_2768C0_002768c0, &rg::fn_sub_2768C0_002768c0__recomp, "", 'r'},
    {"sub_276A80", 0x276A80u, &rg::fn_sub_276A80_00276a80, &rg::fn_sub_276A80_00276a80__recomp, "", 'r'},
    {"sub_276B10", 0x276B10u, &rg::fn_sub_276B10_00276b10, &rg::fn_sub_276B10_00276b10__recomp, "", 'r'},
    {"sub_276C30", 0x276C30u, &rg::fn_sub_276C30_00276c30, &rg::fn_sub_276C30_00276c30__recomp, "", 'r'},
    {"sub_2771F0", 0x2771F0u, &rg::fn_sub_2771F0_002771f0, &rg::fn_sub_2771F0_002771f0__recomp, "", 'r'},
    {"sub_278550", 0x278550u, &rg::fn_sub_278550_00278550, &rg::fn_sub_278550_00278550__recomp, "", 'r'},
    {"sub_279940", 0x279940u, &rg::fn_sub_279940_00279940, &rg::fn_sub_279940_00279940__recomp, "F", 'e'},
    {"sub_279AC0", 0x279AC0u, &rg::fn_sub_279AC0_00279ac0, &rg::fn_sub_279AC0_00279ac0__recomp, "S", 'e'},
    {"sub_279AF0", 0x279AF0u, &rg::fn_sub_279AF0_00279af0, &rg::fn_sub_279AF0_00279af0__recomp, "Si", 'e'},
    {"sub_279B10", 0x279B10u, &rg::fn_sub_279B10_00279b10, &rg::fn_sub_279B10_00279b10__recomp, "S", 'e'},
    {"sub_279B20", 0x279B20u, &rg::fn_sub_279B20_00279b20, &rg::fn_sub_279B20_00279b20__recomp, "S", 'e'},
    {"sub_279B30", 0x279B30u, &rg::fn_sub_279B30_00279b30, &rg::fn_sub_279B30_00279b30__recomp, "Y", 'e'},
    {"sub_279BF0", 0x279BF0u, &rg::fn_sub_279BF0_00279bf0, &rg::fn_sub_279BF0_00279bf0__recomp, "", 'e'},
    {"sub_279C90", 0x279C90u, &rg::fn_sub_279C90_00279c90, &rg::fn_sub_279C90_00279c90__recomp, "", 'e'},
    {"sub_279D10", 0x279D10u, &rg::fn_sub_279D10_00279d10, &rg::fn_sub_279D10_00279d10__recomp, "", 'e'},
    {"sub_279D60", 0x279D60u, &rg::fn_sub_279D60_00279d60, &rg::fn_sub_279D60_00279d60__recomp, "", 'e'},
    {"sub_27A3B0", 0x27A3B0u, &rg::fn_sub_27A3B0_0027a3b0, &rg::fn_sub_27A3B0_0027a3b0__recomp, "", 'e'},
    {"sub_27A4A0", 0x27A4A0u, &rg::fn_sub_27A4A0_0027a4a0, &rg::fn_sub_27A4A0_0027a4a0__recomp, "", 'e'},
    {"sub_27A560", 0x27A560u, &rg::fn_sub_27A560_0027a560, &rg::fn_sub_27A560_0027a560__recomp, "L", 'e'},
    {"sub_27A5D0", 0x27A5D0u, &rg::fn_sub_27A5D0_0027a5d0, &rg::fn_sub_27A5D0_0027a5d0__recomp, "", 'e'},
    {"sub_27A6A0", 0x27A6A0u, &rg::fn_sub_27A6A0_0027a6a0, &rg::fn_sub_27A6A0_0027a6a0__recomp, "Ltb", 'e'},
    {"sub_27A930", 0x27A930u, &rg::fn_sub_27A930_0027a930, &rg::fn_sub_27A930_0027a930__recomp, "Lv", 'e'},
    {"sub_27AA00", 0x27AA00u, &rg::fn_sub_27AA00_0027aa00, &rg::fn_sub_27AA00_0027aa00__recomp, "Lq", 'e'},
    {"sub_27AAA0", 0x27AAA0u, &rg::fn_sub_27AAA0_0027aaa0, &rg::fn_sub_27AAA0_0027aaa0__recomp, "", 'e'},
    {"sub_27AB10", 0x27AB10u, &rg::fn_sub_27AB10_0027ab10, &rg::fn_sub_27AB10_0027ab10__recomp, "", 'e'},
    {"sub_27AB80", 0x27AB80u, &rg::fn_sub_27AB80_0027ab80, &rg::fn_sub_27AB80_0027ab80__recomp, "", 'e'},
    {"sub_27AC60", 0x27AC60u, &rg::fn_sub_27AC60_0027ac60, &rg::fn_sub_27AC60_0027ac60__recomp, "Z", 'e'},
    {"sub_27AC80", 0x27AC80u, &rg::fn_sub_27AC80_0027ac80, &rg::fn_sub_27AC80_0027ac80__recomp, "", 'e'},
    {"sub_27ACE0", 0x27ACE0u, &rg::fn_sub_27ACE0_0027ace0, &rg::fn_sub_27ACE0_0027ace0__recomp, "", 'e'},
    {"sub_27AE90", 0x27AE90u, &rg::fn_sub_27AE90_0027ae90, &rg::fn_sub_27AE90_0027ae90__recomp, "", 'e'},
    {"sub_27AF80", 0x27AF80u, &rg::fn_sub_27AF80_0027af80, &rg::fn_sub_27AF80_0027af80__recomp, "", 'e'},
    {"sub_27AFD0", 0x27AFD0u, &rg::fn_sub_27AFD0_0027afd0, &rg::fn_sub_27AFD0_0027afd0__recomp, "", 'e'},
    {"sub_27B070", 0x27B070u, &rg::fn_sub_27B070_0027b070, &rg::fn_sub_27B070_0027b070__recomp, "", 'e'},
    {"sub_27B0B0", 0x27B0B0u, &rg::fn_sub_27B0B0_0027b0b0, &rg::fn_sub_27B0B0_0027b0b0__recomp, "", 'e'},
    {"sub_27B200", 0x27B200u, &rg::fn_sub_27B200_0027b200, &rg::fn_sub_27B200_0027b200__recomp, "", 'e'},
    {"sub_27B2B0", 0x27B2B0u, &rg::fn_sub_27B2B0_0027b2b0, &rg::fn_sub_27B2B0_0027b2b0__recomp, "", 'e'},
    {"sub_27B3F0", 0x27B3F0u, &rg::fn_sub_27B3F0_0027b3f0, &rg::fn_sub_27B3F0_0027b3f0__recomp, "T", 'e'},
    {"sub_27B460", 0x27B460u, &rg::fn_sub_27B460_0027b460, &rg::fn_sub_27B460_0027b460__recomp, "", 'e'},
    {"sub_280200", 0x280200u, &rg::fn_sub_280200_00280200, &rg::fn_sub_280200_00280200__recomp, "UOo", 'c'},
    {"sub_283750", 0x283750u, &rg::fn_sub_283750_00283750, &rg::fn_sub_283750_00283750__recomp, "Um", 'c'},
    {"sub_284470", 0x284470u, &rg::fn_sub_284470_00284470, &rg::fn_sub_284470_00284470__recomp, "H", 'c'},
    {"sub_284690", 0x284690u, &rg::fn_sub_284690_00284690, &rg::fn_sub_284690_00284690__recomp, "J", 'c'},
    {"sub_284D10", 0x284D10u, &rg::fn_sub_284D10_00284d10, &rg::fn_sub_284D10_00284d10__recomp, "D", 'c'},
    {"sub_284D60", 0x284D60u, &rg::fn_sub_284D60_00284d60, &rg::fn_sub_284D60_00284d60__recomp, "D", 'c'},
    {"sub_284D80", 0x284D80u, &rg::fn_sub_284D80_00284d80, &rg::fn_sub_284D80_00284d80__recomp, "Uu", 'c'},
    {"sub_285DE0", 0x285DE0u, &rg::fn_sub_285DE0_00285de0, &rg::fn_sub_285DE0_00285de0__recomp, "D", 'c'},
    {"sub_285E00", 0x285E00u, &rg::fn_sub_285E00_00285e00, &rg::fn_sub_285E00_00285e00__recomp, "D", 'c'},
    {"sub_285E30", 0x285E30u, &rg::fn_sub_285E30_00285e30, &rg::fn_sub_285E30_00285e30__recomp, "D", 'c'},
    {"sub_285E50", 0x285E50u, &rg::fn_sub_285E50_00285e50, &rg::fn_sub_285E50_00285e50__recomp, "U", 'c'},
    {"sub_285EB0", 0x285EB0u, &rg::fn_sub_285EB0_00285eb0, &rg::fn_sub_285EB0_00285eb0__recomp, "D", 'c'},
    {"sub_285ED0", 0x285ED0u, &rg::fn_sub_285ED0_00285ed0, &rg::fn_sub_285ED0_00285ed0__recomp, "D", 'c'},
    {"sub_285F00", 0x285F00u, &rg::fn_sub_285F00_00285f00, &rg::fn_sub_285F00_00285f00__recomp, "D", 'c'},
    {"sub_285F20", 0x285F20u, &rg::fn_sub_285F20_00285f20, &rg::fn_sub_285F20_00285f20__recomp, "U", 'c'},
    {"sub_286380", 0x286380u, &rg::fn_sub_286380_00286380, &rg::fn_sub_286380_00286380__recomp, "D", 'c'},
    {"sub_2863F0", 0x2863F0u, &rg::fn_sub_2863F0_002863f0, &rg::fn_sub_2863F0_002863f0__recomp, "D", 'c'},
    {"sub_286480", 0x286480u, &rg::fn_sub_286480_00286480, &rg::fn_sub_286480_00286480__recomp, "D", 'c'},
    {"sub_2864A0", 0x2864A0u, &rg::fn_sub_2864A0_002864a0, &rg::fn_sub_2864A0_002864a0__recomp, "Uuu", 'c'},
    {"sub_286540", 0x286540u, &rg::fn_sub_286540_00286540, &rg::fn_sub_286540_00286540__recomp, "", 'c'},
    {"sub_287860", 0x287860u, &rg::fn_sub_287860_00287860, &rg::fn_sub_287860_00287860__recomp, "U", 'c'},
    {"sub_28B230", 0x28B230u, &rg::fn_sub_28B230_0028b230, &rg::fn_sub_28B230_0028b230__recomp, "A", 'c'},
    {"sub_28CA00", 0x28CA00u, &rg::fn_sub_28CA00_0028ca00, &rg::fn_sub_28CA00_0028ca00__recomp, "A", 'c'},
    {"sub_28CF20", 0x28CF20u, &rg::fn_sub_28CF20_0028cf20, &rg::fn_sub_28CF20_0028cf20__recomp, "A", 'c'},
    {"sub_28CF80", 0x28CF80u, &rg::fn_sub_28CF80_0028cf80, &rg::fn_sub_28CF80_0028cf80__recomp, "A", 'c'},
    {"sub_28D080", 0x28D080u, &rg::fn_sub_28D080_0028d080, &rg::fn_sub_28D080_0028d080__recomp, "A", 'c'},
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
float ldf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }
bool in_ram(u32 va) { return va >= 0x100000u && va < 0x2000000u; }

constexpr u32 kGpVa = 0x7D2CF0u;
constexpr u32 kGBtlSlot = 0x7CE3ECu;
u32 gp(s32 off) { return kGpVa + static_cast<u32>(off); }
// Free guest memory for the blocks a test builds (zero in every replay snapshot; the stand-in heap allocates from
// kStandInHeap upwards and never gets this far in these pairs).
constexpr u32 kScratch = kStandInHeap + 0x2C0000u;

// The stand-ins: heap, printf, sprintf, H_Cdvd, and recorders for the callees the test build does not emit that the
// bodies reach (both bodies meet the same recorder; its log is compared).
const u32 kRecorded[] = {
    0x324BD0u, 0x2E3AE0u, 0x2DCFB0u, 0x242600u, 0x2B94F0u, 0x316F70u, 0x4F7560u, 0x242720u, 0x25BE60u,
    // the sound layer below the bodies' sound requests (the sound driver entries)
    0x51DF58u, 0x51E028u, 0x108FD0u, 0x109180u, 0x109F60u, 0x10A100u, 0x10A720u, 0x1099D0u, 0x10A370u,
    0x109AE0u, 0x109DF0u, 0x108F70u,
    // the light / camera / RW callees, the font / texture loaders, the message window and status tasks
    0x1A0700u, 0x1A07F0u, 0x1A4580u, 0x4C9D70u, 0x4DD2E0u, 0x20F9A0u, 0x21EC40u, 0x3A2D80u, 0x3B7090u,
    0x3C77A0u, 0x3C7BC0u, 0x3C8F70u, 0x3C9850u, 0x3C9AB0u, 0x3C9D00u, 0x3170C0u, 0x31C820u,
    0x1A08E0u, 0x20F570u, 0x21C9F0u, 0x21CC20u, 0x3C8230u, 0x491EA0u,
    // still-recompiled battle callees (other slices' stand-ins included: recorders here never take them)
    0x245EA0u, 0x267120u, 0x274030u, 0x2813F0u, 0x282D40u, 0x288110u, 0x28DF00u, 0x2B6460u,
    0x24F090u, 0x255B20u, 0x257130u, 0x258630u, 0x25AAD0u, 0x2879F0u, 0x287EA0u, 0x2849A0u, 0x281F20u,
    // battle6: the not-emitted callees its bodies reach -- the model / camera / texture helpers of Shuffle Time and the
    // result screen, the message window steps, the persona-grow pack installer, the unit instance / effect helpers
    0x1052B0u, 0x1A0E50u, 0x1A7710u, 0x20AC90u, 0x20C500u, 0x20EC50u, 0x239280u, 0x3A4360u, 0x3C7990u, 0x3C94E0u,
    0x4DB350u,
    0x20C400u, 0x233E70u, 0x3252A0u, 0x3A30C0u, 0x3C9790u,
    0x20D770u,
    // the START / START HOME inits that stay recompiled (btlActionSetState reaches them from the state updates)
    0x28AA20u, 0x28B800u,
};
void b6_setup(StandInWorld& w) {
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
    b6_setup(*wh);
    b6_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// hgp::pair's comparison on a long-lived BaseRange (write_tracker.h) instead of a PairRange per pair: the world's
// 32 MiB stay the base and restore() copies back only the pages a pair wrote. Same checks as hgp::pair.
hgp::Run pair_base(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b6_setup(*wh);
    b6_setup(*wr);
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
    b6_setup(*g_solo);
    g_si[0] = g_solo.get();
    g_fn[0] = fn;
    return hgp::run_one(m, &thunk0, args, 1, hw);
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

// --- the staff roll data: DATA/OPED/ED_SR.BIN / ED_SR_F.BIN -----------------------------------------------------
// The archive: entries of {char name[252], u32 size} + data, each 64-byte aligned; entry 0 is the script file
// (edfile::), 1 / 2 the fonts 6 / 7.
std::vector<u8> read_file(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}
// The script file (entry 0) of an ED_SR archive; empty when the archive is not there.
std::vector<u8> ed_script_file(const char* name) {
    const std::vector<u8> a = read_file(extracted_root() + "/DATA/OPED/" + name);
    if (a.size() < 256) return {};
    u32 size;
    std::memcpy(&size, a.data() + 252, 4);
    if (256 + size > a.size()) return {};
    return std::vector<u8>(a.begin() + 256, a.begin() + 256 + size);
}
u32 rd32(const std::vector<u8>& v, std::size_t off) {
    u32 x = 0;
    if (off + 4 <= v.size()) std::memcpy(&x, v.data() + off, 4);
    return x;
}
// Copies a host image into guest memory at va.
void put_bytes(Machine& m, u32 va, const std::vector<u8>& v) { std::memcpy(ram(m, va), v.data(), v.size()); }

// The staff roll world: the script file image at kEdFile, the scroll / resource works at kEdScroll / kEdRes registered
// at their $gp slots, a script object built on the host the way edScriptBuild builds it (at kEdScript), and line
// slots with glyph-list words pointing at zeroed blocks.
constexpr u32 kEdFile = kScratch + 0x20000u, kEdScript = kScratch + 0x24000u, kEdScroll = kScratch + 0x28000u,
              kEdRes = kScratch + 0x2A000u, kEdSr = kScratch + 0x2B000u;
u32 ed_build_script_host(Machine& m, const std::vector<u8>& f, u32 at) {
    const u32 cmd_off = rd32(f, 4), cmd_size = rd32(f, 8), count = rd32(f, 12), len_off = rd32(f, 16), str_off = rd32(f, 20),
              str_size = rd32(f, 24);
    auto al = [](u32 x) { return (x + 3u) & ~3u; };
    const u32 table = at + 20, strings = al(table + 4 * count), cmds = al(strings + str_size);
    st32(m, at + b6::edscript::kWord0, rd32(f, 0));
    st32(m, at + b6::edscript::kStringCount, count);
    st32(m, at + b6::edscript::kStrings, table);
    st32(m, at + b6::edscript::kStringData, strings);
    st32(m, at + b6::edscript::kCommands, cmds);
    std::memcpy(ram(m, strings), f.data() + str_off, str_size);
    std::memcpy(ram(m, cmds), f.data() + cmd_off, cmd_size);
    u32 p = strings;
    for (u32 i = 0; i < count; ++i) {
        st32(m, table + 4 * i, p);
        p += f[len_off + i];
    }
    return at;
}
void ed_world(Machine& m, const std::vector<u8>& f, std::mt19937& rng) {
    std::memset(ram(m, kScratch + 0x20000u), 0, 0x10000);
    if (!f.empty()) {
        put_bytes(m, kEdFile, f);
        ed_build_script_host(m, f, kEdScript);
    }
    st32(m, gp(b6::kGpEdScroll), kEdScroll);
    st32(m, gp(b6::kGpEdRes), kEdRes);
    st32(m, gp(b6::kGpEdSr), kEdSr);
    st32(m, kEdRes + b6::edres::kScript, f.empty() ? 0 : kEdScript);
    const u32 flags = rng() & 7u;
    st32(m, kEdScroll + b6::edscroll::kFlags, flags);
    const u32 cursor = f.empty() ? 0 : rng() % (rd32(f, 8) - 1);
    st32(m, kEdScroll + b6::edscroll::kCursor, cursor);
    const u32 sidx = f.empty() ? 0 : rng() % rd32(f, 12);
    st32(m, kEdScroll + b6::edscroll::kStringIndex, sidx);
    const float y = static_cast<float>(rng() % 900) - 200.0f;
    stf(m, kEdScroll + b6::edscroll::kNextY, y);
    const u32 phase = rng() % 3;
    st32(m, kEdScroll + b6::edscroll::kEndPhase, phase);
    const u32 frame = rng() % 200;
    st32(m, kEdScroll + b6::edscroll::kEndFrame, frame);
    const float y0 = 208.0f + static_cast<float>(rng() % 400);
    stf(m, kEdScroll + b6::edscroll::kEndY0, y0);
    // a few used line slots (0..2 words each, glyph lists 0) and the last line pointing at one of them
    for (u32 i = 0; i < 32; ++i) {
        const u32 s = kEdScroll + b6::edscroll::kLines + 144 * i;
        const bool used = chance(rng, 25);
        st32(m, s + b6::edline::kFlags, used ? 1 : 0);
        st32(m, s + b6::edline::kWordCount, 0);
        const float ly = static_cast<float>(rng() % 600) - 100.0f;
        stf(m, s + b6::edline::kY, ly);
    }
    st32(m, kEdScroll + b6::edscroll::kLastLine, kEdScroll + b6::edscroll::kLines + 144 * (rng() % 32));
    const u32 rflags = rng() & 1u;
    st32(m, kEdRes + b6::edres::kLoading, rflags);
    const u32 loaded = rng() & 1u;
    st32(m, kEdRes + b6::edres::kLoaded, loaded);
    const u32 srflags = rng() & 1u;
    st32(m, kEdSr + b6::edsr::kFlags, srflags);
    const u32 step = rng() % 4;
    st32(m, kEdSr + b6::edsr::kStep, step);
}

// --- the objects of a snapshot ----------------------------------------------------------------------------------------
struct Objects {
    u32 btl = 0;
    std::vector<u32> acts, units, dats, data;  // data: the packets' data blocks
    std::vector<u32> works;                    // the live works ($gp slots), for the flag perturbations
    std::vector<u32> poses, cams, cards;       // Shuffle Time: the pose nodes, the camera records, the cards
    u32 bpc = 0;
};
const s32 kWorkSlots[] = {b4::kGpBpcWork, b4::kGpBpmWork, b4::kGpBpWork328, b6::kGpBasWork, b6::kGpBpTut, b6::kGpBpTuta,
                          b4::kGpBpoWork, b5::kGpBpPersona, b5::kGpBpSelect, b6::kGpSflCamera, b6::kGpSflCard,
                          b6::kGpSflCursor, b5::kGpSflPsel, b5::kGpSflPersona, b6::kGpBrItem, b5::kGpBrHero,
                          b5::kGpBrPersona, b5::kGpBrpSeq, b5::kGpBrLvPanel, b5::kGpBrpPersona, b5::kGpBrpParam,
                          b6::kGpBrpRoot, b6::kGpBrpBirth, b6::kGpBrpRes};
Objects objects_of(Machine& m) {
    Objects o;
    for (s32 slot : kWorkSlots)
        if (const u32 w = ld32(m, gp(slot)); in_ram(w)) o.works.push_back(w);
    if (const u32 g = ld32(m, gp(b6::kGpGcPose)); in_ram(g))
        for (u32 p = ld32(m, g + b6::gcpose::kHead), n = 0; in_ram(p) && n < 256; p = ld32(m, p + b6::pose::kNext), ++n)
            o.poses.push_back(p);
    if (const u32 c = ld32(m, gp(b6::kGpSflCamera)); in_ram(c))
        for (u32 r = ld32(m, c + b6::sflcam::kHead), n = 0; in_ram(r) && n < 32; r = ld32(m, r + b6::sflcamrec::kNext), ++n)
            o.cams.push_back(r);
    if (const u32 w = ld32(m, gp(b6::kGpSflCard)); in_ram(w))
        for (u32 c = ld32(m, w + 75356), n = 0; in_ram(c) && n < 32; c = ld32(m, c + 4036), ++n) o.cards.push_back(c);
    if (const u32 w = ld32(m, gp(b4::kGpBpcWork)); in_ram(w)) o.bpc = w;
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

// The perturbations of one snapshot pair: the works' flag words and step words, the pose nodes' dirty bits and
// times, the units' fade / colour / flag words, the actions' state words, the battle flags the bodies test.
void perturb(Machine& m, const Objects& o, std::mt19937& rng) {
    for (u32 w : o.works)
        if (chance(rng, 20)) {
            const u32 bits = rng() & 0x7FFu;
            st32(m, w, ld32(m, w) ^ bits);
        }
    if (const u32 seq = ld32(m, gp(b5::kGpBrpSeq)); in_ram(seq) && chance(rng, 50)) {
        const u32 step = rng() % 6;
        st32(m, seq + b5::brpseq::kStep, step);
        const u32 sub = rng() % 6;
        st32(m, seq + b6::brpseq6::kSkillStep + 4 * (rng() % 3), sub);
    }
    if (const u32 t = ld32(m, gp(b6::kGpBpTut)); in_ram(t) && chance(rng, 40)) {
        const u32 ph = rng() % 2;
        st32(m, t + b6::tut::kPhase, ph);
        const u32 step = rng() % 8;
        st32(m, t + b6::tut::kStep, step);
        const u32 kind = rng() % 4;
        st32(m, t + b6::tut::kKind, kind);
    }
    if (const u32 t = ld32(m, gp(b6::kGpBpTuta)); in_ram(t) && chance(rng, 40)) {
        const u32 ph = rng() % 2;
        st32(m, t + b6::tuta::kPhase, ph);
        const u32 step = rng() % 4;
        st32(m, t + b6::tuta::kStep, step);
    }
    if (const u32 c = ld32(m, gp(b6::kGpSflCursor)); in_ram(c) && chance(rng, 40)) {
        const u32 kind = rng() % 4;
        st32(m, c + b6::sflcur::kMoveKind, kind);
        const u32 sel = rng() % 6;
        st32(m, c + b6::sflcur::kSel, sel);
        const u32 fr = rng() % 17;
        st32(m, c + b6::sflcur::kMoveFrame, fr);
    }
    if (const u32 w = ld32(m, gp(b6::kGpSflCard)); in_ram(w) && chance(rng, 40)) {
        const u32 phase = rng() % 6;
        st32(m, w + 75888, phase);
        const u32 sub = rng() % 3;
        st32(m, w + 75892 + 4 * (rng() % 2), sub);
        const u32 fr = rng() % 31;
        st32(m, w + 75900, fr);
    }
    for (u32 p : o.poses)
        if (chance(rng, 15)) {
            const u32 f = ld32(m, p + b6::pose::kFlags) | 2u;
            st32(m, p + b6::pose::kFlags, f);
        }
    for (u32 c : o.cards)
        if (chance(rng, 15)) {
            const u32 bits = rng() & 0x2B8u;
            st32(m, c + b6::card::kFlags, ld32(m, c + b6::card::kFlags) ^ bits);
        }
    if (!o.btl) return;
    static const u32 kFlagBits[] = {0x2u, 0x80u, 0x2000u, 0x4000u, 0x80000u, 0x400000u, 0x4000000u};
    for (int k = 0; k < 2; ++k)
        if (chance(rng, 30)) {
            const u32 bit = kFlagBits[rng() % std::size(kFlagBits)];
            st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) ^ bit);
        }
    for (u32 u : o.units) {
        if (chance(rng, 15)) {
            const u32 mf = rng() & 0x7u;
            st32(m, u + b3::unit::kModelFlags, (ld32(m, u + b3::unit::kModelFlags) & ~0x7u) | mf);
        }
        if (chance(rng, 10)) {
            const u16 fade = static_cast<u16>(rng() % 9);
            st16(m, u + 76, fade);
        }
        if (chance(rng, 10)) {
            const u8 a = static_cast<u8>(rng());
            st8(m, u + 55, a);
        }
    }
    for (u32 a : o.acts) {
        if (chance(rng, 15)) {
            const u32 w = rng() % 8;
            st32(m, a + 1156, w);
        }
        if (chance(rng, 10)) {
            const u8 om = static_cast<u8>(rng() % 2);
            st8(m, a + b3::act::kOneMore, om);
        }
    }
}

// A pose node of kind / mode drawn at random, with children from `pool` (or other built nodes), in the scratch area.
u32 build_pose(Machine& m, std::mt19937& rng, u32 at, const std::vector<u32>& pool) {
    std::memset(ram(m, at), 0, 128);
    const u32 kind = chance(rng, 45) ? 0 : chance(rng, 30) ? 1 : 2;
    st32(m, at + b6::pose::kKind, kind);
    const u32 active = chance(rng, 85) ? 1u : 0u;  // each draw its own statement (operand order differs by compiler)
    const u32 dirty = chance(rng, 85) ? 2u : 0u;
    const u32 flags = active | dirty;
    st32(m, at + b6::pose::kFlags, flags);
    const u32 time = (rng() % 400) << 16;
    st32(m, at + b6::pose::kTime, time);
    for (u32 i = 0; i < 4; ++i) {
        const float v = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 16.0f;
        stf(m, at + b6::pose::kValue + 4 * i, v);
    }
    auto child = [&]() -> u32 {
        if (pool.empty() || chance(rng, 15)) return 0;
        return pool[rng() % pool.size()];
    };
    auto fl = [&](u32 off, int lo, int hi) {
        const float v = static_cast<float>(lo + static_cast<int>(rng() % static_cast<u32>(hi - lo + 1)));
        stf(m, at + off, v);
    };
    if (kind == 0) {
        const u32 mode = rng() % 4;
        st32(m, at + b6::pose::kPosMode, mode);
        if (mode == 1) {
            fl(84, 1, 40);
            const u32 period = 1 + rng() % 200;
            st32(m, at + 88, period);
            fl(92, 1, 20);
            fl(96, 0, 3);
            for (u32 off = 36; off < 84; off += 4) fl(off, -50, 50);
        } else if (mode == 2) {
            for (u32 i = 0; i < 3; ++i) st32(m, at + 36 + 4 * i, child());
        } else if (mode == 3) {
            const u32 curve = rng() % 2;
            st32(m, at + 36, curve);
            const u32 run = rng() & 1u;
            st32(m, at + 40, run);
            const u32 dur = (1 + rng() % 60) << 16;
            st32(m, at + 44, dur);
            for (u32 off = 48; off < 96; off += 4) fl(off, -100, 100);
        }
    } else if (kind == 1) {
        st32(m, at + 36, child());
        st32(m, at + 40, child());
    } else {
        const u32 mode = rng() % 5;
        st32(m, at + 36, mode);
        if (mode == 1) {
            st32(m, at + 40, child());
            st32(m, at + 44, child());
        } else if (mode == 2) {
            for (u32 i = 0; i < 3; ++i) st32(m, at + 40 + 4 * i, child());
        } else if (mode == 3) {
            const u32 curve = rng() % 2;
            st32(m, at + 40, curve);
            const u32 run = rng() & 1u;
            st32(m, at + 44, run);
            const u32 dur = (1 + rng() % 60) << 16;
            st32(m, at + 48, dur);
            for (u32 off = 52; off < 100; off += 4) fl(off, -3, 3);
        } else if (mode == 4) {
            for (u32 off = 40; off < 100; off += 4) fl(off, -30, 30);
            const u32 period = 1 + rng() % 200;
            st32(m, at + 100, period);
            fl(104, 1, 20);
            fl(108, 0, 3);
        }
    }
    return at;
}

// Builds the argument blocks in the scratch area and returns the value for one kind.
u64 arg_of(Machine& m, char kind, const Objects& o, std::mt19937& rng, u32& blk, std::vector<u32>& built) {
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
    switch (kind) {
    case 'A': return sx(act);
    case 'U': return sx(unit);
    case 'D': {
        const u32 b = block(32);
        st32(m, b + b6::pdunit::kUnit, unit);
        const u16 fl = static_cast<u16>(rng() & 0x10u);
        st16(m, b + b6::pdunit::kFlags, fl);
        return sx(b);
    }
    case 'H': {
        const u32 b = block(16);
        st32(m, b + b6::pshake::kUnit, unit);
        const float amp = rnd_f(0, 60) / 2.0f;
        stf(m, b + b6::pshake::kAmp, amp);
        return sx(b);
    }
    case 'J': {
        const u32 b = block(32);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 4 * i, rnd_f(-500, 500));
        st32(m, b + b6::phop::kUnit, unit);
        const u16 frames = static_cast<u16>(1 + rng() % 12);
        st16(m, b + b6::phop::kFrames, frames);
        const u16 step = static_cast<u16>(rng() % (frames + 1u));
        st16(m, b + b6::phop::kStep, step);
        stf(m, b + b6::phop::kT, rnd_f(0, 10) / 10.0f);
        return sx(b);
    }
    case 'B': return sx(o.bpc ? o.bpc + b4::bpc::kEntries + 2624 * (rng() % 4) : block(2624));
    case 'W': return sx(block(512));
    case 'N': {
        if (!o.poses.empty() && chance(rng, 60)) return sx(pick(o.poses, rng, 0u));
        std::vector<u32> pool = o.poses;
        pool.insert(pool.end(), built.begin(), built.end());
        const u32 b = kScratch + blk;
        blk += 128;
        build_pose(m, rng, b, pool);
        built.push_back(b);
        return sx(b);
    }
    case 'C': {
        if (!o.cams.empty() && chance(rng, 70)) return sx(pick(o.cams, rng, 0u));
        const u32 b = block(272);
        const u32 k = chance(rng, 85) ? 1 : 0;
        st32(m, b + b6::sflcamrec::kKind, k);
        std::vector<u32> pool = o.poses;
        build_pose(m, rng, b + b6::sflcamrec::kPosNode, pool);
        build_pose(m, rng, b + b6::sflcamrec::kRotNode, pool);
        const u32 la = pick(o.poses, rng, 0u);
        st32(m, b + b6::sflcamrec::kLookAt, la);
        return sx(b);
    }
    case 'X': {
        const u32 b = block(32);
        st32(m, b + 4, block(96));
        return sx(b);
    }
    case 'R': return sx(pick(o.cards, rng, 0u));
    case 'L': {
        const u32 b = block(144);
        const u32 words = rng() % 3;
        st32(m, b + b6::edline::kWordCount, words);
        for (u32 i = 0; i < words; ++i) {  // glyph lists: zeroed blocks (an empty list)
            const u32 gl = kScratch + blk;
            blk += 64;
            std::memset(ram(m, gl), 0, 64);
            st32(m, b + b6::edline::kWords + 8 * i + 4, gl);
        }
        return sx(b);
    }
    case 'F': return sx(kEdFile);
    case 'S': return sx(kEdScript);
    case 'Y': return sx(block(4656));
    case 'Z': return sx(block(16));
    case 'T': {
        const u32 b = block(64);
        st32(m, b + b6::ktask::kWork, block(64));
        return sx(b);
    }
    case 'K': {
        const u32 b = block(96);
        st16(m, b + 4, chance(rng, 85) ? 3 : 2);
        for (u32 i = 0; i < 3; ++i) st32(m, b + 8 + 8 * i, 48 + 8 * i);
        return sx(b);
    }
    case 'v': {
        const u32 b = block(16);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 4 * i, rnd_f(-1800, 1800) / 1.5f);
        return sx(b);
    }
    case 'q': {
        const u32 b = block(16);
        for (u32 i = 0; i < 4; ++i) stf(m, b + 4 * i, rnd_f(-100, 100) / 100.0f);
        return sx(b);
    }
    case 'o': return sx(block(64));
    case 't': {
        const u32 b = block(32);
        const char* s = chance(rng, 50) ? "Analysis" : "Rest";
        std::memcpy(ram(m, b), s, std::strlen(s) + 1);
        return sx(b);
    }
    case 'k': return chance(rng, 50) ? 1 + rng() % 8 : 1 + rng() % 200;  // low ids: the personas a stock usually holds
    case 'm': return rng() % 30;
    case 'u': return rng() % 40;
    case 'i': return rng() % 3;
    case 'b': return rng() % 2;
    case 'n': return rng() % 8;
    default: return rng() % 8;
    }
}

// a0..a3 in Args; $t0..$t2 through HwCheck::gpr_in.
void args_for(Machine& m, const Case& c, const Objects& o, std::mt19937& rng, Args& a, HwCheck& hw) {
    u32 blk = 0;
    std::vector<u32> built;
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 7; ++i) {
        const u64 v = i < n ? arg_of(m, c.kinds[i], o, rng, blk, built) : rng() % 8;
        if (i < 4) a[i] = v;
        else hw.gpr_in[GPR_T0 + (i - 4)] = v;
    }
}

// The snapshots, each with the groups it serves and the pairs per function.
struct Snap {
    const char* dir;
    const char* groups;
    u32 reps;
};
const Snap kSnapshots[] = {{"b_5800", "pc", 24},          {"battle_ref_6150", "rc", 16}, {"b20_climb_10850", "spc", 16},
                           {"b20_climb_11200", "sr", 16}, {"climb_ref_17000", "psrec", 2}};

}  // namespace

TEST_CASE("game(battle6): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 16;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    constexpr u32 kWorld = 0x01810000u, kWorldSize = 0x10000u;
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
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

TEST_CASE("game(battle6): every body on the replay snapshots, perturbed, by subsystem") {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    int pairs = 0, stops = 0, used = 0;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
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
                                    << " units, " << o.works.size() << " live works, " << o.poses.size() << " pose nodes, "
                                    << o.cams.size() << " cameras, " << o.cards.size() << " cards");
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (std::size_t ci = 0; ci < std::size(kCases); ++ci) {
            const Case& c = kCases[ci];
            if (only && std::string(only) != c.name) continue;
            if (!std::strchr(sn.groups, c.group)) continue;
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
    std::string always;
    for (std::size_t ci = 0; ci < std::size(kCases); ++ci)
        if (ran_of[ci] && stopped_of[ci] == ran_of[ci]) always += std::string(" ") + kCases[ci].name + " (" + why_of[ci] + ")";
    for (const auto& [pc, who] : missing) MESSAGE("stopped at the not-emitted " << hex64(pc) << ":" << who.substr(0, 200));
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops
                          << " ended at a compared stop; always stopped:" << (always.empty() ? " none" : always));
}

TEST_CASE("game(battle6): the staff roll and the pose graphs on built worlds") {
    auto m = new_machine();
    if (!m) return;
    const std::vector<u8> files[2] = {ed_script_file("ED_SR.BIN"), ed_script_file("ED_SR_F.BIN")};
    if (files[0].empty()) MESSAGE("SKIP (staff roll data): DATA/OPED/ED_SR.BIN not found; the built works use no script");
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int pairs = 0, stops = 0;
    const Objects none;
    for (const Case& c : kCases) {
        if (c.group != 'e' && c.group != 's') continue;
        if (only && std::string(only) != c.name) continue;
        for (u32 rep = 0; rep < reps; ++rep) {
            std::mt19937 rng{rep * 7919u + c.addr * 3u};
            if (c.group == 'e') ed_world(*m, files[rep & 1], rng);
            Objects o;
            // a small pose graph for the Shuffle Time bodies: 12 nodes linked into the gc_pose work's list
            if (c.group == 's') {
                const u32 work = kScratch + 0x30000u;
                std::memset(ram(*m, work), 0, 0x2000);
                st32(*m, gp(b6::kGpGcPose), work);
                std::vector<u32> pool;
                for (u32 i = 0; i < 12; ++i) {
                    const u32 at = work + 0x400 + 128 * i;
                    build_pose(*m, rng, at, pool);
                    pool.push_back(at);
                }
                for (u32 i = 0; i < 12; ++i) st32(*m, pool[i] + b6::pose::kNext, i + 1 < 12 ? pool[i + 1] : 0);
                st32(*m, work + b6::gcpose::kHead, pool[0]);
                o.poses = pool;
            }
            Args a{};
            HwCheck hw;
            args_for(*m, c, c.group == 's' ? o : none, rng, a, hw);
            const hgp::Run r = pair(*m, c.hand, c.recomp, a, rng(), c.name, hw);
            stops += r.stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("built worlds: " << pairs << " pairs, " << stops << " ended at a compared stop");
}

namespace {
// A body run with $f12 set (the float argument of btlUnitMotionFrames).
float g_f12 = 0.0f;
Fn g_target = nullptr;
void with_f12(EEContext& ctx) {
    std::memcpy(&ctx.fpr[12], &g_f12, 4);
    g_target(ctx);
}
u32 v0_32(const hgp::Run& r) { return static_cast<u32>(v0_of(r)); }
bool near(float a, float b) { return std::fabs(a - b) <= 1e-4f * std::max(1.0f, std::fabs(b)); }

// The host's reading of a staff roll command stream: the commands in order (with the operand of command 3) up to
// and including the closing 0.
struct EdCmd {
    u8 op, arg;
    u32 at;
};
std::vector<EdCmd> ed_commands(const std::vector<u8>& f) {
    std::vector<EdCmd> out;
    const u32 off = rd32(f, 4), size = rd32(f, 8);
    for (u32 i = 0; i < size;) {
        const u8 op = f[off + i];
        const u8 arg = op == 3 && i + 1 < size ? f[off + i + 1] : 0;
        out.push_back({op, arg, i});
        if (op == 0) break;
        i += op == 3 ? 2 : 1;
    }
    return out;
}
}  // namespace

TEST_CASE("game(battle6): the staff roll script follows its documented layout") {
    auto m = new_machine();
    if (!m) return;
    int files = 0;
    for (const char* name : {"ED_SR.BIN", "ED_SR_F.BIN"}) {
        const std::vector<u8> f = ed_script_file(name);
        if (f.empty()) {
            MESSAGE("SKIP: DATA/OPED/" << name << " not found");
            continue;
        }
        ++files;
        INFO(std::string(name));
        const u32 count = rd32(f, 12), len_off = rd32(f, 16), str_size = rd32(f, 24), cmd_size = rd32(f, 8);
        // host: the lengths cover the string data (each string NUL-padded), one line command per string, the stream
        // closed by a 0 in its last byte
        u32 sum = 0;
        for (u32 i = 0; i < count; ++i) sum += f[len_off + i];
        CHECK(sum <= str_size);
        CHECK(str_size - sum < 4);
        const std::vector<EdCmd> cmds = ed_commands(f);
        REQUIRE(!cmds.empty());
        CHECK(cmds.back().op == 0);
        CHECK(cmds.back().at == cmd_size - 1);
        u32 lines = 0;
        for (const EdCmd& c : cmds) {
            CHECK(c.op <= 4);
            lines += c.op == 1 ? 1 : 0;
        }
        CHECK(lines == count);

        // guest: edScriptBuild makes the object the host builds -- the head, the table, the strings, the commands
        std::memset(ram(*m, kScratch + 0x20000u), 0, 0x10000);
        put_bytes(*m, kEdFile, f);
        const hgp::Run rb = solo(*m, &rg::fn_sub_279940_00279940, Args{sx(kEdFile), 0, 0, 0});
        REQUIRE(!rb.stopped);
        const u32 obj = v0_32(rb);
        REQUIRE(in_ram(obj));
        CHECK(ld32(*m, obj + b6::edscript::kWord0) == rd32(f, 0));
        CHECK(ld32(*m, obj + b6::edscript::kStringCount) == count);
        const u32 table = ld32(*m, obj + b6::edscript::kStrings), data = ld32(*m, obj + b6::edscript::kStringData),
                  stream = ld32(*m, obj + b6::edscript::kCommands);
        CHECK(table == obj + 20);
        CHECK(data == ((table + 4 * count + 3) & ~3u));
        CHECK(stream == ((data + str_size + 3) & ~3u));
        u32 p = data;
        int bad = 0;
        for (u32 i = 0; i < count; ++i) {
            bad += ld32(*m, table + 4 * i) != p ? 1 : 0;
            p += f[len_off + i];
        }
        CHECK(bad == 0);
        CHECK(std::memcmp(ram(*m, data), f.data() + rd32(f, 20), str_size) == 0);
        CHECK(std::memcmp(ram(*m, stream), f.data() + rd32(f, 4), cmd_size) == 0);
        // the getters
        CHECK(v0_32(solo(*m, &rg::fn_sub_279B20_00279b20, Args{sx(obj), 0, 0, 0})) == count);
        CHECK(v0_32(solo(*m, &rg::fn_sub_279B10_00279b10, Args{sx(obj), 0, 0, 0})) == stream);
        for (u32 i : {0u, 1u, count / 2, count - 1})
            CHECK(v0_32(solo(*m, &rg::fn_sub_279AF0_00279af0, Args{sx(obj), i, 0, 0})) == ld32(*m, table + 4 * i));

        // guest: walking the stream with the scroll's peek / operand / step equals the host's reading, and the cursor
        // moves one byte per command 1 / 2 / 4, two for command 3, none at the closing 0
        std::mt19937 rng{7};
        ed_world(*m, {}, rng);
        st32(*m, kEdRes + b6::edres::kScript, obj);
        st32(*m, kEdScroll + b6::edscroll::kCursor, 0);
        int mismatches = 0;
        for (const EdCmd& c : cmds) {
            const u32 before = ld32(*m, kEdScroll + b6::edscroll::kCursor);
            mismatches += before != c.at ? 1 : 0;
            const u32 op = v0_32(solo(*m, &rg::fn_sub_27AAA0_0027aaa0, Args{}));
            mismatches += op != c.op ? 1 : 0;
            if (c.op == 3) mismatches += v0_32(solo(*m, &rg::fn_sub_27AB10_0027ab10, Args{})) != c.arg ? 1 : 0;
            solo(*m, &rg::fn_sub_27AB80_0027ab80, Args{});
            const u32 after = ld32(*m, kEdScroll + b6::edscroll::kCursor);
            const u32 step = c.op == 0 ? 0 : c.op == 3 ? 2 : 1;
            mismatches += after != before + step ? 1 : 0;
        }
        CHECK(mismatches == 0);
        MESSAGE(std::string(name) << ": " << count << " strings, " << cmds.size() << " commands walked");
    }
    if (!files) MESSAGE("SKIP: no staff roll data");
}

TEST_CASE("game(battle6): the pose nodes follow their documented rules") {
    auto m = new_machine();
    if (!m) return;
    const u32 work = kScratch + 0x30000u, n = work + 0x400, a = n + 0x100, b = n + 0x200;
    std::memset(ram(*m, work), 0, 0x2000);
    st32(*m, gp(b6::kGpGcPose), work);
    // the initialisers: kind / mode words, the children cleared
    struct Init {
        Fn fn;
        u32 kind, mode_off, mode;
        u32 cleared_from, cleared;
    };
    const Init inits[] = {{&rg::fn_sub_24FD10_0024fd10, 0, b6::pose::kPosMode, 0, 0, 0},
                          {&rg::fn_sub_24FD20_0024fd20, 0, b6::pose::kPosMode, 1, 0, 0},
                          {&rg::fn_sub_24FD40_0024fd40, 0, b6::pose::kPosMode, 2, 36, 3},
                          {&rg::fn_sub_24FD80_0024fd80, 0, b6::pose::kPosMode, 3, 0, 0},
                          {&rg::fn_sub_24FDC0_0024fdc0, 2, 36, 2, 40, 3},
                          {&rg::fn_sub_24FE20_0024fe20, 2, 36, 4, 0, 0}};
    for (const Init& in : inits) {
        std::memset(ram(*m, n), 0xA5, 128);
        solo(*m, in.fn, Args{sx(n), 0, 0, 0});
        CHECK(ld32(*m, n + b6::pose::kKind) == in.kind);
        CHECK(ld32(*m, n + in.mode_off) == in.mode);
        for (u32 i = 0; i < in.cleared; ++i) CHECK(ld32(*m, n + in.cleared_from + 4 * i) == 0);
    }
    // the timed moves: from the current value to `end` in `frames` frames, t = frames / 30 s (16.16 time / 1966080)
    std::mt19937 rng{11};
    int moves = 0;
    for (int k = 0; k < 40; ++k) {
        std::memset(ram(*m, n), 0, 0x300);
        solo(*m, &rg::fn_sub_24FD80_0024fd80, Args{sx(n), 0, 0, 0});
        float p0[3], p1[3];
        for (int i = 0; i < 3; ++i) {
            const int x0 = static_cast<int>(rng() % 801) - 400;
            p0[i] = static_cast<float>(x0) / 4.0f;
            const int x1 = static_cast<int>(rng() % 801) - 400;
            p1[i] = static_cast<float>(x1) / 4.0f;
            stf(*m, n + b6::pose::kValue + 4 * i, p0[i]);
            stf(*m, b + 4 * i, p1[i]);
        }
        const u32 frames = 1 + rng() % 90;
        const float t = static_cast<float>(static_cast<s32>(frames << 16)) / 1966080.0f;
        const int which = k % 3;
        const Fn fn = which == 0 ? &rg::fn_sub_250500_00250500 : which == 1 ? &rg::fn_sub_2508C0_002508c0 : &rg::fn_sub_250A30_00250a30;
        solo(*m, fn, Args{sx(n), sx(b), frames, 0});
        CHECK(ld32(*m, n + 44) == frames << 16);
        CHECK(ld32(*m, n + b6::pose::kTime) == 0);
        CHECK((ld32(*m, n + 40) & 1u) == 1u);
        for (int i = 0; i < 3; ++i) {
            const float d = p1[i] - p0[i];
            if (which == 0) {  // straight: curve 0, end +48, start +60
                CHECK(ld32(*m, n + 36) == 0);
                CHECK(ldf(*m, n + 48 + 4 * i) == p1[i]);
                CHECK(ldf(*m, n + 60 + 4 * i) == p0[i]);
            } else if (which == 1) {  // arriving at rest: velocity 2d / t, acceleration -2d / t^2
                CHECK(ld32(*m, n + 36) == 1);
                CHECK(near(ldf(*m, n + 60 + 4 * i), 2.0f * d / t));
                CHECK(near(ldf(*m, n + 48 + 4 * i), -2.0f * d / (t * t)));
                CHECK(ldf(*m, n + 72 + 4 * i) == p0[i]);
                CHECK(ldf(*m, n + 84 + 4 * i) == p1[i]);
            } else {  // from rest: velocity 0, acceleration 2d / t^2
                CHECK(ld32(*m, n + 36) == 1);
                CHECK(ldf(*m, n + 60 + 4 * i) == 0.0f);
                CHECK(near(ldf(*m, n + 48 + 4 * i), 2.0f * d / (t * t)));
            }
        }
        // the evaluation at a time inside the move (dirty, active): straight = lerp, arc = start + (v + a t / 2) t;
        // past the end the time clamps to the duration and the run flag clears
        const u32 at_frames = rng() % (frames + 20);
        st32(*m, n + b6::pose::kTime, at_frames << 16);
        st32(*m, n + b6::pose::kFlags, 3);
        st32(*m, n + b6::pose::kNext, 0);
        st32(*m, work + b6::gcpose::kHead, n);
        solo(*m, &rg::fn_sub_24DC90_0024dc90, Args{sx(n), 0, 0, 0});
        const u32 tt = std::min(at_frames, frames) << 16;
        CHECK(ld32(*m, n + b6::pose::kTime) == tt);
        CHECK((ld32(*m, n + b6::pose::kFlags) & 2u) == 0);
        CHECK(((ld32(*m, n + 40) & 1u) == 0) == (at_frames >= frames));
        for (int i = 0; i < 3; ++i) {
            float want;
            if (which == 0) {
                const float d = p1[i] - p0[i];
                const float frac = static_cast<float>(static_cast<s32>(tt)) / static_cast<float>(static_cast<s32>(frames << 16));
                want = d * frac + p0[i];
            } else {
                const float s = static_cast<float>(static_cast<s32>(tt)) / 1966080.0f;
                const float acc = ldf(*m, n + 48 + 4 * i), vel = ldf(*m, n + 60 + 4 * i);
                want = ldf(*m, n + 72 + 4 * i) + (acc * (0.5f * s) + vel) * s;
            }
            CHECK(near(ldf(*m, n + b6::pose::kValue + 4 * i), want));
        }
        ++moves;
    }
    // sum and direction nodes over fixed clean children
    for (int k = 0; k < 20; ++k) {
        std::memset(ram(*m, n), 0, 0x300);
        float va[3], vb[3];
        for (u32 node : {a, b}) {
            solo(*m, &rg::fn_sub_24FD10_0024fd10, Args{sx(node), 0, 0, 0});
            st32(*m, node + b6::pose::kFlags, 1);
        }
        for (int i = 0; i < 3; ++i) {
            const int xa = static_cast<int>(rng() % 201) - 100;
            va[i] = static_cast<float>(xa);
            const int xb = static_cast<int>(rng() % 201) - 100;
            vb[i] = static_cast<float>(xb);
            stf(*m, a + b6::pose::kValue + 4 * i, va[i]);
            stf(*m, b + b6::pose::kValue + 4 * i, vb[i]);
        }
        const bool sum = k % 2 == 0;
        if (sum) {
            solo(*m, &rg::fn_sub_24FD40_0024fd40, Args{sx(n), 0, 0, 0});
            solo(*m, &rg::fn_sub_2503F0_002503f0, Args{sx(n), 0, sx(a), 0});
            solo(*m, &rg::fn_sub_2503F0_002503f0, Args{sx(n), 2, sx(b), 0});
        } else {
            st32(*m, n + b6::pose::kKind, 1);
            st32(*m, n + b6::pose::kPosMode, 1);  // a direction node's only mode
            st32(*m, n + 36, a);
            st32(*m, n + 40, b);
        }
        st32(*m, n + b6::pose::kFlags, 3);
        const hgp::Run r = solo(*m, &rg::fn_sub_24DC90_0024dc90, Args{sx(n), 0, 0, 0});
        INFO("stopped " << r.stopped << " " << r.what << " at " << hex64(r.stop_pc) << " flags " << ld32(*m, n + 8) << " kind "
                        << ld32(*m, n + 12) << " mode " << ld32(*m, n + 32) << " c0 " << hex64(ld32(*m, n + 36)) << " c2 "
                        << hex64(ld32(*m, n + 44)) << " depth " << ld32(*m, work + 520));
        for (int i = 0; i < 3; ++i) CHECK(ldf(*m, n + b6::pose::kValue + 4 * i) == (sum ? va[i] + vb[i] : vb[i] - va[i]));
    }
    MESSAGE("pose rules: 6 initialisers, " << moves << " timed moves, 20 sum / direction nodes");
}

TEST_CASE("game(battle6): Shuffle Time, the motion length, the unit packets and the tutorial follow their rules") {
    // Shuffle Time's card shuffle: the cards' slots (+16) stay a permutation of 0..n-1 (n = the work's +75388)
    for (const char* dir : {"b20_climb_10850", "b20_climb_11200"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: " << dir);
            continue;
        }
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        const u32 work = ld32(*m, gp(b6::kGpSflCard));
        if (!in_ram(work) || o.cards.empty()) continue;
        const u32 count = ld32(*m, work + 75388);
        INFO(dir << ": " << count << " cards");
        const hgp::Run r = solo(*m, &rg::fn_sub_258B40_00258b40, Args{});
        CHECK(!r.stopped);
        std::vector<u32> slots;
        for (u32 c : o.cards)
            if ((ld32(*m, c) & 2u) == 0) slots.push_back(ld32(*m, c + 16));
        std::sort(slots.begin(), slots.end());
        CHECK(slots.size() == count);
        for (u32 i = 0; i < slots.size(); ++i) CHECK(slots[i] == i);
        CHECK((ld32(*m, work) & 0x10u) == 0);
    }

    auto m = new_machine();
    if (!m) return;
    // btlUnitMotionFrames: row = the per-side table 0x693290 (26 bytes per side) at the motion; past the unit's rows 0,
    // else (s16)(frames / (speed * pct / 100)), 0 for negative frames
    const u32 unit = kScratch + 0x40000u, rows = kScratch + 0x41000u;
    std::mt19937 rng{5};
    int lengths = 0;
    for (int k = 0; k < 200; ++k) {
        std::memset(ram(*m, unit), 0, 0x1000);
        const u8 side = (k & 1) ? 2 : 0;
        st8(*m, unit + b3::unit::kSide, side);
        const u16 nrows = static_cast<u16>(rng() % 40);
        st16(*m, unit + b3::unit::kMotionCount, nrows);
        st32(*m, unit + b3::unit::kMotionTbl, rows);
        for (u32 i = 0; i < 40; ++i) {
            const s16 pct = static_cast<s16>(10 + rng() % 300);
            st16(*m, rows + 10 * i + 2, static_cast<u16>(pct));
            const s16 fr = static_cast<s16>(static_cast<int>(rng() % 400) - 20);
            st16(*m, rows + 10 * i + 4, static_cast<u16>(fr));
        }
        const u32 motion = rng() % 26;
        const u32 speed = 1 + rng() % 8;
        g_f12 = static_cast<float>(speed) / 2.0f;
        g_target = &rg::fn_sub_283750_00283750;
        const hgp::Run r = solo(*m, &with_f12, Args{sx(unit), motion, 0, 0});
        REQUIRE(!r.stopped);
        const u8 idx = *m->at(0x693290u + 26u * side + motion);
        s32 want = 0;
        if (idx < nrows) {
            const s16 fr = static_cast<s16>(ld16(*m, rows + 10 * idx + 4));
            if (fr >= 0) {
                const float pct = static_cast<float>(static_cast<s16>(ld16(*m, rows + 10 * idx + 2))) / 100.0f;
                want = static_cast<s16>(static_cast<s32>(static_cast<float>(fr) / (g_f12 * pct)));
            }
        }
        CHECK(static_cast<s64>(v0_of(r)) == want);
        ++lengths;
    }

    // the unit packets on the battle snapshot: the creators' callbacks and data
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: b_5800 not found (unit packets, tutorial)");
        return;
    }
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    const Objects o = objects_of(*m);
    REQUIRE(!o.units.empty());
    struct Creator {
        Fn fn;
        u32 init, update, end;
    };
    const Creator creators[] = {{&rg::fn_sub_284D80_00284d80, 0x284CF0u, 0x284D10u, 0x284D60u},
                                {&rg::fn_sub_285E50_00285e50, 0x285DE0u, 0x285E00u, 0x285E30u},
                                {&rg::fn_sub_285F20_00285f20, 0x285EB0u, 0x285ED0u, 0x285F00u},
                                {&rg::fn_sub_2864A0_002864a0, 0x286380u, 0x2863F0u, 0x286480u}};
    int packets = 0;
    for (const Creator& c : creators)
        for (u32 u : o.units) {
            const hgp::Run r = solo(*m, c.fn, Args{sx(u), 7, 9, 0});
            if (r.stopped) continue;
            const u32 pkt = v0_32(r);
            REQUIRE(in_ram(pkt));
            CHECK(ld32(*m, pkt + 104) == c.init);
            CHECK(ld32(*m, pkt + 108) == c.update);
            CHECK(ld32(*m, pkt + 112) == c.end);
            const u32 data = ld32(*m, pkt + b3::pkt::kData);
            CHECK(ld32(*m, data + b6::pdunit::kUnit) == u);
            if (c.fn == &rg::fn_sub_284D80_00284d80) CHECK(ld16(*m, data + 4) == 7);
            if (c.fn == &rg::fn_sub_2864A0_002864a0) {
                CHECK(ld16(*m, data + 4) == ld8(*m, u + b3::unit::kSide) + 1u);
                CHECK(ld16(*m, data + 6) == 7);
                CHECK(ld16(*m, data + 8) == 9);
                CHECK(ld32(*m, data + 12) == 0);
                CHECK((ld8(*m, pkt + 71) & 1u) == 0);
            }
            ++packets;
        }
    // the shake packet's update: done (1) once the amplitude is 0.5 or less, the offset zeroed and motion flag 1
    // cleared; else (0) the amplitude decays by the constant at 0x7CAE10, the count steps, motion flag 1 set
    const float decay = ldf(*m, 0x7CAE10u);
    int shakes = 0;
    for (int k = 0; k < 40; ++k) {
        const u32 u = o.units[static_cast<std::size_t>(k) % o.units.size()], d = kScratch + 0x42000u;
        const float amp = static_cast<float>(k) / 8.0f;
        st32(*m, d + b6::pshake::kUnit, u);
        stf(*m, d + b6::pshake::kAmp, amp);
        st32(*m, d + b6::pshake::kCount, static_cast<u32>(k));
        const hgp::Run r = solo(*m, &rg::fn_sub_284470_00284470, Args{sx(d), 0, 0, 0});
        if (r.stopped) continue;
        const bool done = amp <= 0.5f;
        CHECK(v0_of(r) == (done ? 1u : 0u));
        CHECK(((ld16(*m, u + b5::unit5::kMotionFlags) & 1u) != 0) == !done);
        if (done) {
            for (u32 i = 0; i < 3; ++i) CHECK(ld32(*m, u + b4::unit4::kShakeOff + 4 * i) == 0);
        } else {
            CHECK(near(ldf(*m, d + b6::pshake::kAmp), amp * decay));  // the R5900 FPU rounds toward zero
            CHECK(ld32(*m, d + b6::pshake::kCount) == static_cast<u32>(k + 1));
        }
        ++shakes;
    }
    // the battle tutorial's open: the seen flag 4871 + kind, the kind, phase 0, open
    int tutorials = 0;
    if (const u32 tut = ld32(*m, gp(b6::kGpBpTut)); in_ram(tut))
        for (u32 kind = 0; kind < 4; ++kind) {
            const hgp::Run r = solo(*m, &rg::fn_sub_2518B0_002518b0, Args{kind, 0, 0, 0});
            if (r.stopped) continue;
            CHECK(v0_of(solo(*m, &rg::fn_datGetFlag_0016f190, Args{4871 + kind, 0, 0, 0})) == 1);
            CHECK(ld32(*m, tut + b6::tut::kKind) == kind);
            CHECK(ld32(*m, tut + b6::tut::kPhase) == 0);
            CHECK((ld32(*m, tut + b6::tut::kFlags) & 1u) == 1u);
            ++tutorials;
        }
    MESSAGE("rules: " << lengths << " motion lengths, " << packets << " unit packets, " << shakes << " shake steps, "
                      << tutorials << " tutorial opens");
}

#else

TEST_CASE("game(battle6): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
