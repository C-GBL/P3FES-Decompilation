// Phase 5 pair tests for slice battle4 (game/src/battle/battle4.cpp): every body against its recompiled body (__recomp)
// on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack and every stray store), the
// scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same deterministic
// heap behind the RwMalloc / RwFree slots, sprintf and the H_Cdvd layer, and the same recorders).
//
//   * random worlds (the p3fes_handgen skeleton's);
//   * battle worlds: the replay snapshots b_5800 (the first battle in state ACTION: live gBtl, btlActions, btlUnits,
//     DatUnits, packets, the battle panel works), battle_ref_6150 / b_6150 (the battle over), b_6300 / b_6700 /
//     climb_ref_17000 (no battle: the null paths). Each pair is perturbed the way the branches ask -- bad-status bits,
//     HP, the encounter id (the boss encounters 416..436 / 456 and 0x1A7..0x1B3), a boss enemy id on one unit, the
//     advantage word, the boss rule flag, the panel works' flags -- and restored afterwards (a long-lived BaseRange);
//     the arguments are of the kind each function takes (an action, a unit, a packet data block, a panel slot or entry,
//     a path node, a skill / item list, a skill, an element, an AI predicate, ...).
//   * documented rules on the host: the boss set-up table of btlBossSetup (every encounter's rule flags, AI row and
//     mode word, the three AI_EVENT procedure lookups), the skill effect / sound file names, the screen projection, the
//     ground-plane geometry (distances, the side test, the segment test), the navigator's opening line against the
//     advantage / count / level model, the voice line maps, the analysed-enemy records, the battle panel registries.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"

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

namespace p3fes::recomp_gen {
void fn_sub_241910_00241910(EEContext&);
void fn_sub_241910_00241910__recomp(EEContext&);
void fn_sub_242260_00242260(EEContext&);
void fn_sub_242260_00242260__recomp(EEContext&);
void fn_sub_242320_00242320(EEContext&);
void fn_sub_242320_00242320__recomp(EEContext&);
void fn_sub_242540_00242540(EEContext&);
void fn_sub_242540_00242540__recomp(EEContext&);
void fn_sub_242840_00242840(EEContext&);
void fn_sub_242840_00242840__recomp(EEContext&);
void fn_sub_2428F0_002428f0(EEContext&);
void fn_sub_2428F0_002428f0__recomp(EEContext&);
void fn_sub_242950_00242950(EEContext&);
void fn_sub_242950_00242950__recomp(EEContext&);
void fn_sub_242A30_00242a30(EEContext&);
void fn_sub_242A30_00242a30__recomp(EEContext&);
void fn_sub_242A50_00242a50(EEContext&);
void fn_sub_242A50_00242a50__recomp(EEContext&);
void fn_sub_242A60_00242a60(EEContext&);
void fn_sub_242A60_00242a60__recomp(EEContext&);
void fn_sub_242AE0_00242ae0(EEContext&);
void fn_sub_242AE0_00242ae0__recomp(EEContext&);
void fn_sub_242B80_00242b80(EEContext&);
void fn_sub_242B80_00242b80__recomp(EEContext&);
void fn_sub_242C40_00242c40(EEContext&);
void fn_sub_242C40_00242c40__recomp(EEContext&);
void fn_sub_242C60_00242c60(EEContext&);
void fn_sub_242C60_00242c60__recomp(EEContext&);
void fn_sub_244120_00244120(EEContext&);
void fn_sub_244120_00244120__recomp(EEContext&);
void fn_sub_244E10_00244e10(EEContext&);
void fn_sub_244E10_00244e10__recomp(EEContext&);
void fn_sub_2453D0_002453d0(EEContext&);
void fn_sub_2453D0_002453d0__recomp(EEContext&);
void fn_sub_245420_00245420(EEContext&);
void fn_sub_245420_00245420__recomp(EEContext&);
void fn_sub_245910_00245910(EEContext&);
void fn_sub_245910_00245910__recomp(EEContext&);
void fn_sub_245970_00245970(EEContext&);
void fn_sub_245970_00245970__recomp(EEContext&);
void fn_sub_245A00_00245a00(EEContext&);
void fn_sub_245A00_00245a00__recomp(EEContext&);
void fn_sub_245BF0_00245bf0(EEContext&);
void fn_sub_245BF0_00245bf0__recomp(EEContext&);
void fn_sub_248490_00248490(EEContext&);
void fn_sub_248490_00248490__recomp(EEContext&);
void fn_sub_2484A0_002484a0(EEContext&);
void fn_sub_2484A0_002484a0__recomp(EEContext&);
void fn_sub_248620_00248620(EEContext&);
void fn_sub_248620_00248620__recomp(EEContext&);
void fn_sub_248BB0_00248bb0(EEContext&);
void fn_sub_248BB0_00248bb0__recomp(EEContext&);
void fn_sub_248FC0_00248fc0(EEContext&);
void fn_sub_248FC0_00248fc0__recomp(EEContext&);
void fn_sub_249180_00249180(EEContext&);
void fn_sub_249180_00249180__recomp(EEContext&);
void fn_sub_2491F0_002491f0(EEContext&);
void fn_sub_2491F0_002491f0__recomp(EEContext&);
void fn_sub_249240_00249240(EEContext&);
void fn_sub_249240_00249240__recomp(EEContext&);
void fn_sub_24A6C0_0024a6c0(EEContext&);
void fn_sub_24A6C0_0024a6c0__recomp(EEContext&);
void fn_sub_24A6D0_0024a6d0(EEContext&);
void fn_sub_24A6D0_0024a6d0__recomp(EEContext&);
void fn_sub_251050_00251050(EEContext&);
void fn_sub_251050_00251050__recomp(EEContext&);
void fn_sub_251060_00251060(EEContext&);
void fn_sub_251060_00251060__recomp(EEContext&);
void fn_sub_251A70_00251a70(EEContext&);
void fn_sub_251A70_00251a70__recomp(EEContext&);
void fn_sub_251F20_00251f20(EEContext&);
void fn_sub_251F20_00251f20__recomp(EEContext&);
void fn_sub_251F30_00251f30(EEContext&);
void fn_sub_251F30_00251f30__recomp(EEContext&);
void fn_sub_252060_00252060(EEContext&);
void fn_sub_252060_00252060__recomp(EEContext&);
void fn_sub_252340_00252340(EEContext&);
void fn_sub_252340_00252340__recomp(EEContext&);
void fn_sub_252E60_00252e60(EEContext&);
void fn_sub_252E60_00252e60__recomp(EEContext&);
void fn_sub_252E80_00252e80(EEContext&);
void fn_sub_252E80_00252e80__recomp(EEContext&);
void fn_sub_252E90_00252e90(EEContext&);
void fn_sub_252E90_00252e90__recomp(EEContext&);
void fn_sub_252EE0_00252ee0(EEContext&);
void fn_sub_252EE0_00252ee0__recomp(EEContext&);
void fn_sub_252F30_00252f30(EEContext&);
void fn_sub_252F30_00252f30__recomp(EEContext&);
void fn_sub_25BDF0_0025bdf0(EEContext&);
void fn_sub_25BDF0_0025bdf0__recomp(EEContext&);
void fn_sub_25BE00_0025be00(EEContext&);
void fn_sub_25BE00_0025be00__recomp(EEContext&);
void fn_sub_25C110_0025c110(EEContext&);
void fn_sub_25C110_0025c110__recomp(EEContext&);
void fn_sub_25C190_0025c190(EEContext&);
void fn_sub_25C190_0025c190__recomp(EEContext&);
void fn_sub_25C1E0_0025c1e0(EEContext&);
void fn_sub_25C1E0_0025c1e0__recomp(EEContext&);
void fn_sub_25C9C0_0025c9c0(EEContext&);
void fn_sub_25C9C0_0025c9c0__recomp(EEContext&);
void fn_sub_25CD30_0025cd30(EEContext&);
void fn_sub_25CD30_0025cd30__recomp(EEContext&);
void fn_sub_25CEB0_0025ceb0(EEContext&);
void fn_sub_25CEB0_0025ceb0__recomp(EEContext&);
void fn_sub_25CF00_0025cf00(EEContext&);
void fn_sub_25CF00_0025cf00__recomp(EEContext&);
void fn_sub_25CF10_0025cf10(EEContext&);
void fn_sub_25CF10_0025cf10__recomp(EEContext&);
void fn_sub_25D6C0_0025d6c0(EEContext&);
void fn_sub_25D6C0_0025d6c0__recomp(EEContext&);
void fn_sub_25D710_0025d710(EEContext&);
void fn_sub_25D710_0025d710__recomp(EEContext&);
void fn_sub_25FB60_0025fb60(EEContext&);
void fn_sub_25FB60_0025fb60__recomp(EEContext&);
void fn_sub_280050_00280050(EEContext&);
void fn_sub_280050_00280050__recomp(EEContext&);
void fn_sub_280130_00280130(EEContext&);
void fn_sub_280130_00280130__recomp(EEContext&);
void fn_sub_280580_00280580(EEContext&);
void fn_sub_280580_00280580__recomp(EEContext&);
void fn_sub_2806D0_002806d0(EEContext&);
void fn_sub_2806D0_002806d0__recomp(EEContext&);
void fn_sub_2807A0_002807a0(EEContext&);
void fn_sub_2807A0_002807a0__recomp(EEContext&);
void fn_sub_280870_00280870(EEContext&);
void fn_sub_280870_00280870__recomp(EEContext&);
void fn_sub_2812D0_002812d0(EEContext&);
void fn_sub_2812D0_002812d0__recomp(EEContext&);
void fn_sub_283C70_00283c70(EEContext&);
void fn_sub_283C70_00283c70__recomp(EEContext&);
void fn_sub_283E40_00283e40(EEContext&);
void fn_sub_283E40_00283e40__recomp(EEContext&);
void fn_sub_284DF0_00284df0(EEContext&);
void fn_sub_284DF0_00284df0__recomp(EEContext&);
void fn_sub_284F30_00284f30(EEContext&);
void fn_sub_284F30_00284f30__recomp(EEContext&);
void fn_sub_284F50_00284f50(EEContext&);
void fn_sub_284F50_00284f50__recomp(EEContext&);
void fn_sub_284FE0_00284fe0(EEContext&);
void fn_sub_284FE0_00284fe0__recomp(EEContext&);
void fn_sub_2890A0_002890a0(EEContext&);
void fn_sub_2890A0_002890a0__recomp(EEContext&);
void fn_sub_289860_00289860(EEContext&);
void fn_sub_289860_00289860__recomp(EEContext&);
void fn_sub_28CE50_0028ce50(EEContext&);
void fn_sub_28CE50_0028ce50__recomp(EEContext&);
void fn_sub_28D560_0028d560(EEContext&);
void fn_sub_28D560_0028d560__recomp(EEContext&);
void fn_sub_28E7F0_0028e7f0(EEContext&);
void fn_sub_28E7F0_0028e7f0__recomp(EEContext&);
void fn_sub_296320_00296320(EEContext&);
void fn_sub_296320_00296320__recomp(EEContext&);
void fn_sub_299520_00299520(EEContext&);
void fn_sub_299520_00299520__recomp(EEContext&);
void fn_sub_299800_00299800(EEContext&);
void fn_sub_299800_00299800__recomp(EEContext&);
void fn_sub_29EA50_0029ea50(EEContext&);
void fn_sub_29EA50_0029ea50__recomp(EEContext&);
void fn_sub_29F150_0029f150(EEContext&);
void fn_sub_29F150_0029f150__recomp(EEContext&);
void fn_sub_29F760_0029f760(EEContext&);
void fn_sub_29F760_0029f760__recomp(EEContext&);
void fn_sub_2B1020_002b1020(EEContext&);
void fn_sub_2B1020_002b1020__recomp(EEContext&);
void fn_sub_2B4DB0_002b4db0(EEContext&);
void fn_sub_2B4DB0_002b4db0__recomp(EEContext&);
void fn_sub_2B4FD0_002b4fd0(EEContext&);
void fn_sub_2B4FD0_002b4fd0__recomp(EEContext&);
void fn_sub_2B5600_002b5600(EEContext&);
void fn_sub_2B5600_002b5600__recomp(EEContext&);
void fn_sub_2B93E0_002b93e0(EEContext&);
void fn_sub_2B93E0_002b93e0__recomp(EEContext&);
void fn_sub_2BAA20_002baa20(EEContext&);
void fn_sub_2BAA20_002baa20__recomp(EEContext&);
void fn_sub_2BAAD0_002baad0(EEContext&);
void fn_sub_2BAAD0_002baad0__recomp(EEContext&);
void fn_sub_2BB6F0_002bb6f0(EEContext&);
void fn_sub_2BB6F0_002bb6f0__recomp(EEContext&);
void fn_sub_2BB7D0_002bb7d0(EEContext&);
void fn_sub_2BB7D0_002bb7d0__recomp(EEContext&);
void fn_sub_2BBC00_002bbc00(EEContext&);
void fn_sub_2BBC00_002bbc00__recomp(EEContext&);
void fn_sub_2BC420_002bc420(EEContext&);
void fn_sub_2BC420_002bc420__recomp(EEContext&);
void fn_sub_2BC480_002bc480(EEContext&);
void fn_sub_2BC480_002bc480__recomp(EEContext&);
void fn_sub_2BD5F0_002bd5f0(EEContext&);
void fn_sub_2BD5F0_002bd5f0__recomp(EEContext&);
void fn_sub_2BD6F0_002bd6f0(EEContext&);
void fn_sub_2BD6F0_002bd6f0__recomp(EEContext&);
void fn_sub_2BED10_002bed10(EEContext&);
void fn_sub_2BED10_002bed10__recomp(EEContext&);
void fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0(EEContext&);
void fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0__recomp(EEContext&);
void fn_sub_2C0070_002c0070(EEContext&);
void fn_sub_2C0070_002c0070__recomp(EEContext&);
void fn_sub_2C1080_002c1080(EEContext&);
void fn_sub_2C1080_002c1080__recomp(EEContext&);
void fn_sub_2C1710_002c1710(EEContext&);
void fn_sub_2C1710_002c1710__recomp(EEContext&);
void fn_sub_2C17B0_002c17b0(EEContext&);
void fn_sub_2C17B0_002c17b0__recomp(EEContext&);
void fn_sub_2C1F60_002c1f60(EEContext&);
void fn_sub_2C1F60_002c1f60__recomp(EEContext&);
void fn_sub_2C22D0_002c22d0(EEContext&);
void fn_sub_2C22D0_002c22d0__recomp(EEContext&);
void fn_sub_2C2B20_002c2b20(EEContext&);
void fn_sub_2C2B20_002c2b20__recomp(EEContext&);
void fn_sub_2C2BE0_002c2be0(EEContext&);
void fn_sub_2C2BE0_002c2be0__recomp(EEContext&);
void fn_sub_2C2D00_002c2d00(EEContext&);
void fn_sub_2C2D00_002c2d00__recomp(EEContext&);
void fn_sub_2C2ED0_002c2ed0(EEContext&);
void fn_sub_2C2ED0_002c2ed0__recomp(EEContext&);
void fn_sub_2C30F0_002c30f0(EEContext&);
void fn_sub_2C30F0_002c30f0__recomp(EEContext&);
void fn_sub_2C3120_002c3120(EEContext&);
void fn_sub_2C3120_002c3120__recomp(EEContext&);
void fn_sub_2C3430_002c3430(EEContext&);
void fn_sub_2C3430_002c3430__recomp(EEContext&);
void fn_sub_2C4C80_002c4c80(EEContext&);
void fn_sub_2C4C80_002c4c80__recomp(EEContext&);
void fn_sub_2C4E50_002c4e50(EEContext&);
void fn_sub_2C4E50_002c4e50__recomp(EEContext&);
void fn_sub_2C5030_002c5030(EEContext&);
void fn_sub_2C5030_002c5030__recomp(EEContext&);
void fn_sub_2C5380_002c5380(EEContext&);
void fn_sub_2C5380_002c5380__recomp(EEContext&);
void fn_sub_2C59D0_002c59d0(EEContext&);
void fn_sub_2C59D0_002c59d0__recomp(EEContext&);
void fn_sub_2C5FC0_002c5fc0(EEContext&);
void fn_sub_2C5FC0_002c5fc0__recomp(EEContext&);
void fn_sub_2C6F50_002c6f50(EEContext&);
void fn_sub_2C6F50_002c6f50__recomp(EEContext&);
void fn_sub_2C70D0_002c70d0(EEContext&);
void fn_sub_2C70D0_002c70d0__recomp(EEContext&);
void fn_sub_2D1570_002d1570(EEContext&);
void fn_sub_2D1570_002d1570__recomp(EEContext&);
void fn_sub_2D15A0_002d15a0(EEContext&);
void fn_sub_2D15A0_002d15a0__recomp(EEContext&);
void fn_sub_2D1E70_002d1e70(EEContext&);
void fn_sub_2D1E70_002d1e70__recomp(EEContext&);
void fn_sub_2D1ED0_002d1ed0(EEContext&);
void fn_sub_2D1ED0_002d1ed0__recomp(EEContext&);
void fn_sub_2D1F30_002d1f30(EEContext&);
void fn_sub_2D1F30_002d1f30__recomp(EEContext&);
void fn_sub_2D1FD0_002d1fd0(EEContext&);
void fn_sub_2D1FD0_002d1fd0__recomp(EEContext&);
void fn_sub_2D20A0_002d20a0(EEContext&);
void fn_sub_2D20A0_002d20a0__recomp(EEContext&);
void fn_sub_2D2470_002d2470(EEContext&);
void fn_sub_2D2470_002d2470__recomp(EEContext&);
void fn_sub_2D25C0_002d25c0(EEContext&);
void fn_sub_2D25C0_002d25c0__recomp(EEContext&);
void fn_sub_2D2A00_002d2a00(EEContext&);
void fn_sub_2D2A00_002d2a00__recomp(EEContext&);
void fn_sub_2D2C10_002d2c10(EEContext&);
void fn_sub_2D2C10_002d2c10__recomp(EEContext&);
void fn_sub_2D2EE0_002d2ee0(EEContext&);
void fn_sub_2D2EE0_002d2ee0__recomp(EEContext&);
void fn_sub_2D2F50_002d2f50(EEContext&);
void fn_sub_2D2F50_002d2f50__recomp(EEContext&);
void fn_sub_2D32B0_002d32b0(EEContext&);
void fn_sub_2D32B0_002d32b0__recomp(EEContext&);
void fn_sub_2D41C0_002d41c0(EEContext&);
void fn_sub_2D41C0_002d41c0__recomp(EEContext&);
void fn_sub_2D4810_002d4810(EEContext&);
void fn_sub_2D4810_002d4810__recomp(EEContext&);
void fn_sub_2D48C0_002d48c0(EEContext&);
void fn_sub_2D48C0_002d48c0__recomp(EEContext&);
void fn_sub_2D5DC0_002d5dc0(EEContext&);
void fn_sub_2D5DC0_002d5dc0__recomp(EEContext&);
void fn_sub_2D7560_002d7560(EEContext&);
void fn_sub_2D7560_002d7560__recomp(EEContext&);
void fn_sub_2D7E20_002d7e20(EEContext&);
void fn_sub_2D7E20_002d7e20__recomp(EEContext&);
void fn_sub_2D8390_002d8390(EEContext&);
void fn_sub_2D8390_002d8390__recomp(EEContext&);
void fn_sub_2D9BE0_002d9be0(EEContext&);
void fn_sub_2D9BE0_002d9be0__recomp(EEContext&);
void fn_sub_2D9D70_002d9d70(EEContext&);
void fn_sub_2D9D70_002d9d70__recomp(EEContext&);
void fn_sub_2DD270_002dd270(EEContext&);
void fn_sub_2DD270_002dd270__recomp(EEContext&);
void fn_sub_2DD690_002dd690(EEContext&);
void fn_sub_2DD690_002dd690__recomp(EEContext&);
void fn_sub_2DD8E0_002dd8e0(EEContext&);
void fn_sub_2DD8E0_002dd8e0__recomp(EEContext&);
void fn_sub_2DD960_002dd960(EEContext&);
void fn_sub_2DD960_002dd960__recomp(EEContext&);
void fn_sub_2E0620_002e0620(EEContext&);
void fn_sub_2E0620_002e0620__recomp(EEContext&);
void fn_sub_2E0F70_002e0f70(EEContext&);
void fn_sub_2E0F70_002e0f70__recomp(EEContext&);
void fn_sub_2E12D0_002e12d0(EEContext&);
void fn_sub_2E12D0_002e12d0__recomp(EEContext&);
void fn_sub_2E1BF0_002e1bf0(EEContext&);
void fn_sub_2E1BF0_002e1bf0__recomp(EEContext&);
void fn_sub_2E2410_002e2410(EEContext&);
void fn_sub_2E2410_002e2410__recomp(EEContext&);
void fn_sub_2E2680_002e2680(EEContext&);
void fn_sub_2E2680_002e2680__recomp(EEContext&);
void fn_sub_2E3120_002e3120(EEContext&);
void fn_sub_2E3120_002e3120__recomp(EEContext&);
void fn_sub_2E32A0_002e32a0(EEContext&);
void fn_sub_2E32A0_002e32a0__recomp(EEContext&);
void fn_sub_2E3350_002e3350(EEContext&);
void fn_sub_2E3350_002e3350__recomp(EEContext&);
void fn_sub_2E35D0_002e35d0(EEContext&);
void fn_sub_2E35D0_002e35d0__recomp(EEContext&);
void fn_sub_2E36F0_002e36f0(EEContext&);
void fn_sub_2E36F0_002e36f0__recomp(EEContext&);
void fn_sub_2E37E0_002e37e0(EEContext&);
void fn_sub_2E37E0_002e37e0__recomp(EEContext&);
void fn_sub_2E3C80_002e3c80(EEContext&);
void fn_sub_2E3C80_002e3c80__recomp(EEContext&);
void fn_sub_2E4290_002e4290(EEContext&);
void fn_sub_2E4290_002e4290__recomp(EEContext&);
void fn_sub_2E42E0_002e42e0(EEContext&);
void fn_sub_2E42E0_002e42e0__recomp(EEContext&);
void fn_sub_2E4330_002e4330(EEContext&);
void fn_sub_2E4330_002e4330__recomp(EEContext&);
void fn_sub_2E4430_002e4430(EEContext&);
void fn_sub_2E4430_002e4430__recomp(EEContext&);
void fn_btlBossSetup_002f6e00(EEContext&);
void fn_btlBossSetup_002f6e00__recomp(EEContext&);
void fn_sub_2F9710_002f9710(EEContext&);
void fn_sub_2F9710_002f9710__recomp(EEContext&);
void fn_sub_2FC5D0_002fc5d0(EEContext&);
void fn_sub_2FC5D0_002fc5d0__recomp(EEContext&);
void fn_sub_2FD2E0_002fd2e0(EEContext&);
void fn_sub_2FD2E0_002fd2e0__recomp(EEContext&);
void fn_sub_2FD8A0_002fd8a0(EEContext&);
void fn_sub_2FD8A0_002fd8a0__recomp(EEContext&);
void fn_sub_2FE0B0_002fe0b0(EEContext&);
void fn_sub_2FE0B0_002fe0b0__recomp(EEContext&);
void fn_sub_2FE780_002fe780(EEContext&);
void fn_sub_2FE780_002fe780__recomp(EEContext&);
void fn_btlCountActiveUnits_002d4e10(EEContext&);
void fn_btlGetMeanLevel_002d4cf0(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3, then $t0..$t2) -----------------------------------------
// A btlAction   U btlUnit   D unit packet data (a unit at +0)   P packet data (64 random bytes)   K effect-file packet
// data {handle, request, name, flags}   H effect handle (+1584 flags, +1586 uses)   Y effect bank (788-byte rows)
// Q camera object (+224 an action)   S a battle info slot   B a bpc entry   N a path node   r an action's AI record (+56)
// L u16 skill list   I u16 item list   c an AI predicate   k skill   e element   x status mask   M side mask   u uid
// i id   m motion   n small 0..7   g 0..12   f flags   F frames   C RGBA   E enemy id   v f32[3]   q f32[4]   o out
// buffer   w a font line chain   t a short text   b boss event kind 0..2   d a digit count
struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};
const Case kCases[] = {
    {"sub_241910", 0x241910u, &rg::fn_sub_241910_00241910, &rg::fn_sub_241910_00241910__recomp, ""},
    {"sub_242260", 0x242260u, &rg::fn_sub_242260_00242260, &rg::fn_sub_242260_00242260__recomp, ""},
    {"sub_242320", 0x242320u, &rg::fn_sub_242320_00242320, &rg::fn_sub_242320_00242320__recomp, "Sn"},
    {"sub_242540", 0x242540u, &rg::fn_sub_242540_00242540, &rg::fn_sub_242540_00242540__recomp, "S"},
    {"sub_242840", 0x242840u, &rg::fn_sub_242840_00242840, &rg::fn_sub_242840_00242840__recomp, "Sd"},
    {"sub_2428F0", 0x2428F0u, &rg::fn_sub_2428F0_002428f0, &rg::fn_sub_2428F0_002428f0__recomp, "Sn"},
    {"sub_242950", 0x242950u, &rg::fn_sub_242950_00242950, &rg::fn_sub_242950_00242950__recomp, "n"},
    {"sub_242A30", 0x242A30u, &rg::fn_sub_242A30_00242a30, &rg::fn_sub_242A30_00242a30__recomp, "S"},
    {"sub_242A50", 0x242A50u, &rg::fn_sub_242A50_00242a50, &rg::fn_sub_242A50_00242a50__recomp, "Su"},
    {"sub_242A60", 0x242A60u, &rg::fn_sub_242A60_00242a60, &rg::fn_sub_242A60_00242a60__recomp, ""},
    {"sub_242AE0", 0x242AE0u, &rg::fn_sub_242AE0_00242ae0, &rg::fn_sub_242AE0_00242ae0__recomp, "u"},
    {"sub_242B80", 0x242B80u, &rg::fn_sub_242B80_00242b80, &rg::fn_sub_242B80_00242b80__recomp, "uo"},
    {"sub_242C40", 0x242C40u, &rg::fn_sub_242C40_00242c40, &rg::fn_sub_242C40_00242c40__recomp, "o"},
    {"sub_242C60", 0x242C60u, &rg::fn_sub_242C60_00242c60, &rg::fn_sub_242C60_00242c60__recomp, ""},
    {"sub_244120", 0x244120u, &rg::fn_sub_244120_00244120, &rg::fn_sub_244120_00244120__recomp, "u"},
    {"sub_244E10", 0x244E10u, &rg::fn_sub_244E10_00244e10, &rg::fn_sub_244E10_00244e10__recomp, ""},
    {"sub_2453D0", 0x2453D0u, &rg::fn_sub_2453D0_002453d0, &rg::fn_sub_2453D0_002453d0__recomp, "n"},
    {"sub_245420", 0x245420u, &rg::fn_sub_245420_00245420, &rg::fn_sub_245420_00245420__recomp, "Bn"},
    {"sub_245910", 0x245910u, &rg::fn_sub_245910_00245910, &rg::fn_sub_245910_00245910__recomp, "B"},
    {"sub_245970", 0x245970u, &rg::fn_sub_245970_00245970, &rg::fn_sub_245970_00245970__recomp, "B"},
    {"sub_245A00", 0x245A00u, &rg::fn_sub_245A00_00245a00, &rg::fn_sub_245A00_00245a00__recomp, "A"},
    {"sub_245BF0", 0x245BF0u, &rg::fn_sub_245BF0_00245bf0, &rg::fn_sub_245BF0_00245bf0__recomp, "u"},
    {"sub_248490", 0x248490u, &rg::fn_sub_248490_00248490, &rg::fn_sub_248490_00248490__recomp, "o"},
    {"sub_2484A0", 0x2484A0u, &rg::fn_sub_2484A0_002484a0, &rg::fn_sub_2484A0_002484a0__recomp, ""},
    {"sub_248620", 0x248620u, &rg::fn_sub_248620_00248620, &rg::fn_sub_248620_00248620__recomp, ""},
    {"sub_248BB0", 0x248BB0u, &rg::fn_sub_248BB0_00248bb0, &rg::fn_sub_248BB0_00248bb0__recomp, ""},
    {"sub_248FC0", 0x248FC0u, &rg::fn_sub_248FC0_00248fc0, &rg::fn_sub_248FC0_00248fc0__recomp, "P"},
    {"sub_249180", 0x249180u, &rg::fn_sub_249180_00249180, &rg::fn_sub_249180_00249180__recomp, ""},
    {"sub_2491F0", 0x2491F0u, &rg::fn_sub_2491F0_002491f0, &rg::fn_sub_2491F0_002491f0__recomp, ""},
    {"sub_249240", 0x249240u, &rg::fn_sub_249240_00249240, &rg::fn_sub_249240_00249240__recomp, "o"},
    {"sub_24A6C0", 0x24A6C0u, &rg::fn_sub_24A6C0_0024a6c0, &rg::fn_sub_24A6C0_0024a6c0__recomp, "o"},
    {"sub_24A6D0", 0x24A6D0u, &rg::fn_sub_24A6D0_0024a6d0, &rg::fn_sub_24A6D0_0024a6d0__recomp, ""},
    {"sub_251050", 0x251050u, &rg::fn_sub_251050_00251050, &rg::fn_sub_251050_00251050__recomp, "o"},
    {"sub_251060", 0x251060u, &rg::fn_sub_251060_00251060, &rg::fn_sub_251060_00251060__recomp, ""},
    {"sub_251A70", 0x251A70u, &rg::fn_sub_251A70_00251a70, &rg::fn_sub_251A70_00251a70__recomp, "o"},
    {"sub_251F20", 0x251F20u, &rg::fn_sub_251F20_00251f20, &rg::fn_sub_251F20_00251f20__recomp, "o"},
    {"sub_251F30", 0x251F30u, &rg::fn_sub_251F30_00251f30, &rg::fn_sub_251F30_00251f30__recomp, ""},
    {"sub_252060", 0x252060u, &rg::fn_sub_252060_00252060, &rg::fn_sub_252060_00252060__recomp, ""},
    {"sub_252340", 0x252340u, &rg::fn_sub_252340_00252340, &rg::fn_sub_252340_00252340__recomp, ""},
    {"sub_252E60", 0x252E60u, &rg::fn_sub_252E60_00252e60, &rg::fn_sub_252E60_00252e60__recomp, "o"},
    {"sub_252E80", 0x252E80u, &rg::fn_sub_252E80_00252e80, &rg::fn_sub_252E80_00252e80__recomp, ""},
    {"sub_252E90", 0x252E90u, &rg::fn_sub_252E90_00252e90, &rg::fn_sub_252E90_00252e90__recomp, ""},
    {"sub_252EE0", 0x252EE0u, &rg::fn_sub_252EE0_00252ee0, &rg::fn_sub_252EE0_00252ee0__recomp, ""},
    {"sub_252F30", 0x252F30u, &rg::fn_sub_252F30_00252f30, &rg::fn_sub_252F30_00252f30__recomp, ""},
    {"sub_25BDF0", 0x25BDF0u, &rg::fn_sub_25BDF0_0025bdf0, &rg::fn_sub_25BDF0_0025bdf0__recomp, "o"},
    {"sub_25BE00", 0x25BE00u, &rg::fn_sub_25BE00_0025be00, &rg::fn_sub_25BE00_0025be00__recomp, ""},
    {"sub_25C110", 0x25C110u, &rg::fn_sub_25C110_0025c110, &rg::fn_sub_25C110_0025c110__recomp, ""},
    {"sub_25C190", 0x25C190u, &rg::fn_sub_25C190_0025c190, &rg::fn_sub_25C190_0025c190__recomp, ""},
    {"sub_25C1E0", 0x25C1E0u, &rg::fn_sub_25C1E0_0025c1e0, &rg::fn_sub_25C1E0_0025c1e0__recomp, ""},
    {"sub_25C9C0", 0x25C9C0u, &rg::fn_sub_25C9C0_0025c9c0, &rg::fn_sub_25C9C0_0025c9c0__recomp, ""},
    {"sub_25CD30", 0x25CD30u, &rg::fn_sub_25CD30_0025cd30, &rg::fn_sub_25CD30_0025cd30__recomp, ""},
    {"sub_25CEB0", 0x25CEB0u, &rg::fn_sub_25CEB0_0025ceb0, &rg::fn_sub_25CEB0_0025ceb0__recomp, "w"},
    {"sub_25CF00", 0x25CF00u, &rg::fn_sub_25CF00_0025cf00, &rg::fn_sub_25CF00_0025cf00__recomp, "o"},
    {"sub_25CF10", 0x25CF10u, &rg::fn_sub_25CF10_0025cf10, &rg::fn_sub_25CF10_0025cf10__recomp, ""},
    {"sub_25D6C0", 0x25D6C0u, &rg::fn_sub_25D6C0_0025d6c0, &rg::fn_sub_25D6C0_0025d6c0__recomp, ""},
    {"sub_25D710", 0x25D710u, &rg::fn_sub_25D710_0025d710, &rg::fn_sub_25D710_0025d710__recomp, ""},
    {"sub_25FB60", 0x25FB60u, &rg::fn_sub_25FB60_0025fb60, &rg::fn_sub_25FB60_0025fb60__recomp, "Pno"},
    {"sub_280050", 0x280050u, &rg::fn_sub_280050_00280050, &rg::fn_sub_280050_00280050__recomp, "Uo"},
    {"sub_280130", 0x280130u, &rg::fn_sub_280130_00280130, &rg::fn_sub_280130_00280130__recomp, "Uo"},
    {"sub_280580", 0x280580u, &rg::fn_sub_280580_00280580, &rg::fn_sub_280580_00280580__recomp, "Uo"},
    {"sub_2806D0", 0x2806D0u, &rg::fn_sub_2806D0_002806d0, &rg::fn_sub_2806D0_002806d0__recomp, "Uo"},
    {"sub_2807A0", 0x2807A0u, &rg::fn_sub_2807A0_002807a0, &rg::fn_sub_2807A0_002807a0__recomp, "Uo"},
    {"sub_280870", 0x280870u, &rg::fn_sub_280870_00280870, &rg::fn_sub_280870_00280870__recomp, "Mxooon"},
    {"sub_2812D0", 0x2812D0u, &rg::fn_sub_2812D0_002812d0, &rg::fn_sub_2812D0_002812d0__recomp, "UUm"},
    {"sub_283C70", 0x283C70u, &rg::fn_sub_283C70_00283c70, &rg::fn_sub_283C70_00283c70__recomp, "Um"},
    {"sub_283E40", 0x283E40u, &rg::fn_sub_283E40_00283e40, &rg::fn_sub_283E40_00283e40__recomp, "Um"},
    {"sub_284DF0", 0x284DF0u, &rg::fn_sub_284DF0_00284df0, &rg::fn_sub_284DF0_00284df0__recomp, "D"},
    {"sub_284F30", 0x284F30u, &rg::fn_sub_284F30_00284f30, &rg::fn_sub_284F30_00284f30__recomp, "D"},
    {"sub_284F50", 0x284F50u, &rg::fn_sub_284F50_00284f50, &rg::fn_sub_284F50_00284f50__recomp, "Unn"},
    {"sub_284FE0", 0x284FE0u, &rg::fn_sub_284FE0_00284fe0, &rg::fn_sub_284FE0_00284fe0__recomp, "D"},
    {"sub_2890A0", 0x2890A0u, &rg::fn_sub_2890A0_002890a0, &rg::fn_sub_2890A0_002890a0__recomp, "oo"},
    {"sub_289860", 0x289860u, &rg::fn_sub_289860_00289860, &rg::fn_sub_289860_00289860__recomp, "A"},
    {"sub_28CE50", 0x28CE50u, &rg::fn_sub_28CE50_0028ce50, &rg::fn_sub_28CE50_0028ce50__recomp, "A"},
    {"sub_28D560", 0x28D560u, &rg::fn_sub_28D560_0028d560, &rg::fn_sub_28D560_0028d560__recomp, "A"},
    {"sub_28E7F0", 0x28E7F0u, &rg::fn_sub_28E7F0_0028e7f0, &rg::fn_sub_28E7F0_0028e7f0__recomp, "A"},
    {"sub_296320", 0x296320u, &rg::fn_sub_296320_00296320, &rg::fn_sub_296320_00296320__recomp, "A"},
    {"sub_299520", 0x299520u, &rg::fn_sub_299520_00299520, &rg::fn_sub_299520_00299520__recomp, "A"},
    {"sub_299800", 0x299800u, &rg::fn_sub_299800_00299800, &rg::fn_sub_299800_00299800__recomp, "A"},
    {"sub_29EA50", 0x29EA50u, &rg::fn_sub_29EA50_0029ea50, &rg::fn_sub_29EA50_0029ea50__recomp, ""},
    {"sub_29F150", 0x29F150u, &rg::fn_sub_29F150_0029f150, &rg::fn_sub_29F150_0029f150__recomp, "P"},
    {"sub_29F760", 0x29F760u, &rg::fn_sub_29F760_0029f760, &rg::fn_sub_29F760_0029f760__recomp, "P"},
    {"sub_2B1020", 0x2B1020u, &rg::fn_sub_2B1020_002b1020, &rg::fn_sub_2B1020_002b1020__recomp, "Q"},
    {"sub_2B4DB0", 0x2B4DB0u, &rg::fn_sub_2B4DB0_002b4db0, &rg::fn_sub_2B4DB0_002b4db0__recomp, "Q"},
    {"sub_2B4FD0", 0x2B4FD0u, &rg::fn_sub_2B4FD0_002b4fd0, &rg::fn_sub_2B4FD0_002b4fd0__recomp, "Q"},
    {"sub_2B5600", 0x2B5600u, &rg::fn_sub_2B5600_002b5600, &rg::fn_sub_2B5600_002b5600__recomp, "Q"},
    {"sub_2B93E0", 0x2B93E0u, &rg::fn_sub_2B93E0_002b93e0, &rg::fn_sub_2B93E0_002b93e0__recomp, "Ynnnn"},
    {"sub_2BAA20", 0x2BAA20u, &rg::fn_sub_2BAA20_002baa20, &rg::fn_sub_2BAA20_002baa20__recomp, "K"},
    {"sub_2BAAD0", 0x2BAAD0u, &rg::fn_sub_2BAAD0_002baad0, &rg::fn_sub_2BAAD0_002baad0__recomp, "K"},
    {"sub_2BB6F0", 0x2BB6F0u, &rg::fn_sub_2BB6F0_002bb6f0, &rg::fn_sub_2BB6F0_002bb6f0__recomp, "ko"},
    {"sub_2BB7D0", 0x2BB7D0u, &rg::fn_sub_2BB7D0_002bb7d0, &rg::fn_sub_2BB7D0_002bb7d0__recomp, ""},
    {"sub_2BBC00", 0x2BBC00u, &rg::fn_sub_2BBC00_002bbc00, &rg::fn_sub_2BBC00_002bbc00__recomp, "n"},
    {"sub_2BC420", 0x2BC420u, &rg::fn_sub_2BC420_002bc420, &rg::fn_sub_2BC420_002bc420__recomp, ""},
    {"sub_2BC480", 0x2BC480u, &rg::fn_sub_2BC480_002bc480, &rg::fn_sub_2BC480_002bc480__recomp, ""},
    {"sub_2BD5F0", 0x2BD5F0u, &rg::fn_sub_2BD5F0_002bd5f0, &rg::fn_sub_2BD5F0_002bd5f0__recomp, "P"},
    {"sub_2BD6F0", 0x2BD6F0u, &rg::fn_sub_2BD6F0_002bd6f0, &rg::fn_sub_2BD6F0_002bd6f0__recomp, "P"},
    {"sub_2BED10", 0x2BED10u, &rg::fn_sub_2BED10_002bed10, &rg::fn_sub_2BED10_002bed10__recomp, ""},
    {"btlCommand_CreateBattleCommandCalcTasks", 0x2BF3F0u, &rg::fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0, &rg::fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0__recomp, "A"},
    {"sub_2C0070", 0x2C0070u, &rg::fn_sub_2C0070_002c0070, &rg::fn_sub_2C0070_002c0070__recomp, "An"},
    {"sub_2C1080", 0x2C1080u, &rg::fn_sub_2C1080_002c1080, &rg::fn_sub_2C1080_002c1080__recomp, "AkMxfc"},
    {"sub_2C1710", 0x2C1710u, &rg::fn_sub_2C1710_002c1710, &rg::fn_sub_2C1710_002c1710__recomp, "Ax"},
    {"sub_2C17B0", 0x2C17B0u, &rg::fn_sub_2C17B0_002c17b0, &rg::fn_sub_2C17B0_002c17b0__recomp, "An"},
    {"sub_2C1F60", 0x2C1F60u, &rg::fn_sub_2C1F60_002c1f60, &rg::fn_sub_2C1F60_002c1f60__recomp, "Ae"},
    {"sub_2C22D0", 0x2C22D0u, &rg::fn_sub_2C22D0_002c22d0, &rg::fn_sub_2C22D0_002c22d0__recomp, "An"},
    {"sub_2C2B20", 0x2C2B20u, &rg::fn_sub_2C2B20_002c2b20, &rg::fn_sub_2C2B20_002c2b20__recomp, "Ak"},
    {"sub_2C2BE0", 0x2C2BE0u, &rg::fn_sub_2C2BE0_002c2be0, &rg::fn_sub_2C2BE0_002c2be0__recomp, "Ae"},
    {"sub_2C2D00", 0x2C2D00u, &rg::fn_sub_2C2D00_002c2d00, &rg::fn_sub_2C2D00_002c2d00__recomp, "Ae"},
    {"sub_2C2ED0", 0x2C2ED0u, &rg::fn_sub_2C2ED0_002c2ed0, &rg::fn_sub_2C2ED0_002c2ed0__recomp, "Aen"},
    {"sub_2C30F0", 0x2C30F0u, &rg::fn_sub_2C30F0_002c30f0, &rg::fn_sub_2C30F0_002c30f0__recomp, "Ae"},
    {"sub_2C3120", 0x2C3120u, &rg::fn_sub_2C3120_002c3120, &rg::fn_sub_2C3120_002c3120__recomp, "Ae"},
    {"sub_2C3430", 0x2C3430u, &rg::fn_sub_2C3430_002c3430, &rg::fn_sub_2C3430_002c3430__recomp, "Aexfnc"},
    {"sub_2C4C80", 0x2C4C80u, &rg::fn_sub_2C4C80_002c4c80, &rg::fn_sub_2C4C80_002c4c80__recomp, "AALnn"},
    {"sub_2C4E50", 0x2C4E50u, &rg::fn_sub_2C4E50_002c4e50, &rg::fn_sub_2C4E50_002c4e50__recomp, "AAInn"},
    {"sub_2C5030", 0x2C5030u, &rg::fn_sub_2C5030_002c5030, &rg::fn_sub_2C5030_002c5030__recomp, "AAnn"},
    {"sub_2C5380", 0x2C5380u, &rg::fn_sub_2C5380_002c5380, &rg::fn_sub_2C5380_002c5380__recomp, "AAnn"},
    {"sub_2C59D0", 0x2C59D0u, &rg::fn_sub_2C59D0_002c59d0, &rg::fn_sub_2C59D0_002c59d0__recomp, "AAnn"},
    {"sub_2C5FC0", 0x2C5FC0u, &rg::fn_sub_2C5FC0_002c5fc0, &rg::fn_sub_2C5FC0_002c5fc0__recomp, "AAen"},
    {"sub_2C6F50", 0x2C6F50u, &rg::fn_sub_2C6F50_002c6f50, &rg::fn_sub_2C6F50_002c6f50__recomp, "Arnn"},
    {"sub_2C70D0", 0x2C70D0u, &rg::fn_sub_2C70D0_002c70d0, &rg::fn_sub_2C70D0_002c70d0__recomp, "Ar"},
    {"sub_2D1570", 0x2D1570u, &rg::fn_sub_2D1570_002d1570, &rg::fn_sub_2D1570_002d1570__recomp, "o"},
    {"sub_2D15A0", 0x2D15A0u, &rg::fn_sub_2D15A0_002d15a0, &rg::fn_sub_2D15A0_002d15a0__recomp, "o"},
    {"sub_2D1E70", 0x2D1E70u, &rg::fn_sub_2D1E70_002d1e70, &rg::fn_sub_2D1E70_002d1e70__recomp, "vv"},
    {"sub_2D1ED0", 0x2D1ED0u, &rg::fn_sub_2D1ED0_002d1ed0, &rg::fn_sub_2D1ED0_002d1ed0__recomp, "vv"},
    {"sub_2D1F30", 0x2D1F30u, &rg::fn_sub_2D1F30_002d1f30, &rg::fn_sub_2D1F30_002d1f30__recomp, "qq"},
    {"sub_2D1FD0", 0x2D1FD0u, &rg::fn_sub_2D1FD0_002d1fd0, &rg::fn_sub_2D1FD0_002d1fd0__recomp, "vvvo"},
    {"sub_2D20A0", 0x2D20A0u, &rg::fn_sub_2D20A0_002d20a0, &rg::fn_sub_2D20A0_002d20a0__recomp, "vo"},
    {"sub_2D2470", 0x2D2470u, &rg::fn_sub_2D2470_002d2470, &rg::fn_sub_2D2470_002d2470__recomp, "vvv"},
    {"sub_2D25C0", 0x2D25C0u, &rg::fn_sub_2D25C0_002d25c0, &rg::fn_sub_2D25C0_002d25c0__recomp, "NN"},
    {"sub_2D2A00", 0x2D2A00u, &rg::fn_sub_2D2A00_002d2a00, &rg::fn_sub_2D2A00_002d2a00__recomp, "UU"},
    {"sub_2D2C10", 0x2D2C10u, &rg::fn_sub_2D2C10_002d2c10, &rg::fn_sub_2D2C10_002d2c10__recomp, "NN"},
    {"sub_2D2EE0", 0x2D2EE0u, &rg::fn_sub_2D2EE0_002d2ee0, &rg::fn_sub_2D2EE0_002d2ee0__recomp, "vvv"},
    {"sub_2D2F50", 0x2D2F50u, &rg::fn_sub_2D2F50_002d2f50, &rg::fn_sub_2D2F50_002d2f50__recomp, "N"},
    {"sub_2D32B0", 0x2D32B0u, &rg::fn_sub_2D32B0_002d32b0, &rg::fn_sub_2D32B0_002d32b0__recomp, ""},
    {"sub_2D41C0", 0x2D41C0u, &rg::fn_sub_2D41C0_002d41c0, &rg::fn_sub_2D41C0_002d41c0__recomp, "o"},
    {"sub_2D4810", 0x2D4810u, &rg::fn_sub_2D4810_002d4810, &rg::fn_sub_2D4810_002d4810__recomp, ""},
    {"sub_2D48C0", 0x2D48C0u, &rg::fn_sub_2D48C0_002d48c0, &rg::fn_sub_2D48C0_002d48c0__recomp, "ovv"},
    {"sub_2D5DC0", 0x2D5DC0u, &rg::fn_sub_2D5DC0_002d5dc0, &rg::fn_sub_2D5DC0_002d5dc0__recomp, "o"},
    {"sub_2D7560", 0x2D7560u, &rg::fn_sub_2D7560_002d7560, &rg::fn_sub_2D7560_002d7560__recomp, "A"},
    {"sub_2D7E20", 0x2D7E20u, &rg::fn_sub_2D7E20_002d7e20, &rg::fn_sub_2D7E20_002d7e20__recomp, "UUonn"},
    {"sub_2D8390", 0x2D8390u, &rg::fn_sub_2D8390_002d8390, &rg::fn_sub_2D8390_002d8390__recomp, ""},
    {"sub_2D9BE0", 0x2D9BE0u, &rg::fn_sub_2D9BE0_002d9be0, &rg::fn_sub_2D9BE0_002d9be0__recomp, "A"},
    {"sub_2D9D70", 0x2D9D70u, &rg::fn_sub_2D9D70_002d9d70, &rg::fn_sub_2D9D70_002d9d70__recomp, "A"},
    {"sub_2DD270", 0x2DD270u, &rg::fn_sub_2DD270_002dd270, &rg::fn_sub_2DD270_002dd270__recomp, "P"},
    {"sub_2DD690", 0x2DD690u, &rg::fn_sub_2DD690_002dd690, &rg::fn_sub_2DD690_002dd690__recomp, "nt"},
    {"sub_2DD8E0", 0x2DD8E0u, &rg::fn_sub_2DD8E0_002dd8e0, &rg::fn_sub_2DD8E0_002dd8e0__recomp, "n"},
    {"sub_2DD960", 0x2DD960u, &rg::fn_sub_2DD960_002dd960, &rg::fn_sub_2DD960_002dd960__recomp, "n"},
    {"sub_2E0620", 0x2E0620u, &rg::fn_sub_2E0620_002e0620, &rg::fn_sub_2E0620_002e0620__recomp, "An"},
    {"sub_2E0F70", 0x2E0F70u, &rg::fn_sub_2E0F70_002e0f70, &rg::fn_sub_2E0F70_002e0f70__recomp, "A"},
    {"sub_2E12D0", 0x2E12D0u, &rg::fn_sub_2E12D0_002e12d0, &rg::fn_sub_2E12D0_002e12d0__recomp, "A"},
    {"sub_2E1BF0", 0x2E1BF0u, &rg::fn_sub_2E1BF0_002e1bf0, &rg::fn_sub_2E1BF0_002e1bf0__recomp, "A"},
    {"sub_2E2410", 0x2E2410u, &rg::fn_sub_2E2410_002e2410, &rg::fn_sub_2E2410_002e2410__recomp, "A"},
    {"sub_2E2680", 0x2E2680u, &rg::fn_sub_2E2680_002e2680, &rg::fn_sub_2E2680_002e2680__recomp, "A"},
    {"sub_2E3120", 0x2E3120u, &rg::fn_sub_2E3120_002e3120, &rg::fn_sub_2E3120_002e3120__recomp, "A"},
    {"sub_2E32A0", 0x2E32A0u, &rg::fn_sub_2E32A0_002e32a0, &rg::fn_sub_2E32A0_002e32a0__recomp, "AAk"},
    {"sub_2E3350", 0x2E3350u, &rg::fn_sub_2E3350_002e3350, &rg::fn_sub_2E3350_002e3350__recomp, "Ae"},
    {"sub_2E35D0", 0x2E35D0u, &rg::fn_sub_2E35D0_002e35d0, &rg::fn_sub_2E35D0_002e35d0__recomp, "nn"},
    {"sub_2E36F0", 0x2E36F0u, &rg::fn_sub_2E36F0_002e36f0, &rg::fn_sub_2E36F0_002e36f0__recomp, ""},
    {"sub_2E37E0", 0x2E37E0u, &rg::fn_sub_2E37E0_002e37e0, &rg::fn_sub_2E37E0_002e37e0__recomp, ""},
    {"sub_2E3C80", 0x2E3C80u, &rg::fn_sub_2E3C80_002e3c80, &rg::fn_sub_2E3C80_002e3c80__recomp, ""},
    {"sub_2E4290", 0x2E4290u, &rg::fn_sub_2E4290_002e4290, &rg::fn_sub_2E4290_002e4290__recomp, "A"},
    {"sub_2E42E0", 0x2E42E0u, &rg::fn_sub_2E42E0_002e42e0, &rg::fn_sub_2E42E0_002e42e0__recomp, "A"},
    {"sub_2E4330", 0x2E4330u, &rg::fn_sub_2E4330_002e4330, &rg::fn_sub_2E4330_002e4330__recomp, "A"},
    {"sub_2E4430", 0x2E4430u, &rg::fn_sub_2E4430_002e4430, &rg::fn_sub_2E4430_002e4430__recomp, "Ak"},
    {"btlBossSetup", 0x2F6E00u, &rg::fn_btlBossSetup_002f6e00, &rg::fn_btlBossSetup_002f6e00__recomp, ""},
    {"sub_2F9710", 0x2F9710u, &rg::fn_sub_2F9710_002f9710, &rg::fn_sub_2F9710_002f9710__recomp, ""},
    {"sub_2FC5D0", 0x2FC5D0u, &rg::fn_sub_2FC5D0_002fc5d0, &rg::fn_sub_2FC5D0_002fc5d0__recomp, "UUm"},
    {"sub_2FD2E0", 0x2FD2E0u, &rg::fn_sub_2FD2E0_002fd2e0, &rg::fn_sub_2FD2E0_002fd2e0__recomp, "Ab"},
    {"sub_2FD8A0", 0x2FD8A0u, &rg::fn_sub_2FD8A0_002fd8a0, &rg::fn_sub_2FD8A0_002fd8a0__recomp, "A"},
    {"sub_2FE0B0", 0x2FE0B0u, &rg::fn_sub_2FE0B0_002fe0b0, &rg::fn_sub_2FE0B0_002fe0b0__recomp, "oonn"},
    {"sub_2FE780", 0x2FE780u, &rg::fn_sub_2FE780_002fe780, &rg::fn_sub_2FE780_002fe780__recomp, "oonn"},
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
// Free guest memory for the blocks a test builds (zero in every replay snapshot; the stand-in heap allocates from
// kStandInHeap upwards and never gets this far in these pairs).
constexpr u32 kScratch = kStandInHeap + 0x2C0000u;

// The stand-ins: heap, printf, sprintf, H_Cdvd, and recorders for the callees the test build does not emit that the
// bodies reach on the battle worlds (both bodies meet the same recorder; its log is compared).
const u32 kRecorded[] = {0x324BD0u, 0x2E3AE0u, 0x2DCFB0u, 0x242600u, 0x2B94F0u, 0x316F70u, 0x4F7560u, 0x242720u, 0x25BE60u, 0x1FF890u, 0x31C820u,
                         0x3A2D80u, 0x491EA0u, 0x1A7710u, 0x3170C0u, 0x3A4990u, 0x4B78B0u};
void b4_setup(StandInWorld& w) {
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
    b4_setup(*wh);
    b4_setup(*wr);
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
    b4_setup(*wh);
    b4_setup(*wr);
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
    b4_setup(*g_solo);
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
float f0_of(const hgp::Run& r) {
    float f;
    std::memcpy(&f, &r.end.fpr[0], 4);
    return f;
}

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
    std::vector<u32> slots, entries, nodes;  // battle info slots, bpc entries, path nodes
};
Objects objects_of(Machine& m) {
    Objects o;
    // the battle panel works (live while the battle panel is up)
    if (const u32 bi = ld32(m, kGpVa + b4::kGpBiWork); in_ram(bi))
        for (u32 k = 0; k < 16; ++k) o.slots.push_back(bi + b4::bi::kSlotSize * k);
    if (const u32 bpc = ld32(m, kGpVa + b4::kGpBpcWork); in_ram(bpc)) {
        const u32 n = std::min<u32>(ld32(m, bpc + b4::bpc::kEntryCount), 8);
        for (u32 k = 0; k < std::max<u32>(n, 1); ++k) o.entries.push_back(bpc + b4::bpc::kEntries + b4::bpc::kEntrySize * k);
    }
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
    for (u32 k = 0; k < 4; ++k) o.nodes.push_back(o.btl + b4::gbtl4::kFieldNodes + b4::path::kNodeSize * k);
    o.nodes.push_back(o.btl + b4::gbtl4::kPathStart);
    o.nodes.push_back(o.btl + b4::gbtl4::kPathGoal);
    for (u32 g = ld32(m, o.btl + b3::gbtl::kGridList), n = 0; in_ram(g) && n < 16; g = ld32(m, g + b4::path::kBoxNext), ++n)
        for (u32 k = 0; k < 4; ++k) o.nodes.push_back(g + b4::path::kBoxNodes + b4::path::kNodeSize * k);
    return o;
}
template <class T>
T pick(const std::vector<T>& v, std::mt19937& rng, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

// The perturbations of one battle-world pair: the bad-status words and HP of a few DatUnits, the encounter id, a boss
// id on one enemy unit, the advantage word, the boss rule flag, the panel works' flag words.
void perturb(Machine& m, const Objects& o, std::mt19937& rng) {
    static const u32 kStatus[] = {0x100000u, 0x80000u, 0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x100u, 0x200u, 0x261u};
    for (u32 d : o.dats) {
        if (chance(rng, 35)) st32(m, d + b3::dat::kStatus, chance(rng, 50) ? 0 : kStatus[rng() % 12] | (chance(rng, 20) ? kStatus[rng() % 12] : 0));
        if (chance(rng, 20)) st16(m, d + b3::dat::kHp, static_cast<u16>(chance(rng, 30) ? 0 : 1 + rng() % 400));
    }
    for (u32 s : o.slots)
        if (chance(rng, 15)) st32(m, s, rng() & 0x33Fu);
    for (u32 e : o.entries)
        if (chance(rng, 20)) st32(m, e, rng() & 0x6F0u);
    if (!o.btl) return;
    if (chance(rng, 40)) {
        static const u16 kEnc[] = {416, 417, 420, 421, 423, 424, 428, 429, 431, 432, 433, 434, 435, 436, 456, 0x1A7, 0x1A9,
                                   0x1AA, 0x1AB, 0x1AE, 0x1AF, 0x1B0, 0x1B1, 0x1B2, 0x1B3, 468, 506};
        if (const u32 g = ld32(m, o.btl + b3::gbtl::kSetupEnemies); in_ram(g)) st16(m, g + 8, kEnc[rng() % std::size(kEnc)]);
    }
    if (chance(rng, 30) && !o.units.empty()) {
        static const u16 kBoss[] = {233, 234, 235, 236, 237, 238, 239, 240, 241, 256, 264, 267, 268, 271, 272, 294, 295};
        const u32 u = o.units[rng() % o.units.size()];
        if (ld8(m, u + b3::unit::kSide) == 1) st16(m, u + b3::unit::kId, kBoss[rng() % std::size(kBoss)]);
    }
    if (chance(rng, 30)) st16(m, o.btl + b3::gbtl::kAdvantage, static_cast<u16>(rng() % 3));
    if (chance(rng, 25)) st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) ^ 0x200000u);
    if (chance(rng, 20)) st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) ^ 0x2000000u);
}

// Builds the argument blocks in the scratch area and returns the value for one kind.
u64 arg_of(Machine& m, char kind, const Objects& o, std::mt19937& rng, u32& blk) {
    auto block = [&](u32 size) {
        const u32 b = kScratch + blk;
        blk += (size + 15) & ~15u;
        for (u32 i = 0; i < size; i += 4) st32(m, b + i, chance(rng, 60) ? 0 : rng() % 64);
        return b;
    };
    const u32 act = pick(o.acts, rng, 0u), unit = pick(o.units, rng, 0u);
    switch (kind) {
    case 'A': return sx(act);
    case 'r': return sx(act ? act + 56 : 0);
    case 'U': return sx(unit);
    case 'D': {
        const u32 b = block(64);
        st32(m, b, unit);
        st16(m, b + 4, static_cast<u16>(rng() % 12));
        st16(m, b + 6, static_cast<u16>(rng() % 4));
        if (chance(rng, 50)) st32(m, b + 8, rng() & 0x10u);
        return sx(b);
    }
    case 'P': return sx(block(64));
    case 'H': {
        const u32 b = block(1600);
        st16(m, b + 1584, static_cast<u16>(rng() % 16));
        st16(m, b + 1586, static_cast<u16>(rng() % 3));
        return sx(b);
    }
    case 'K': {  // the effect-file packet data: the handle, the request, the file name, the flags
        const u32 b = block(32), h = block(1600), name = block(32);
        std::memcpy(m.at(name), "battle/btl_none.bed", 20);
        st16(m, h + 1584, static_cast<u16>(rng() % 16));
        st16(m, h + 1586, static_cast<u16>(rng() % 3));
        st32(m, b, h);
        st32(m, b + 4, 0);
        st32(m, b + 8, name);
        st32(m, b + 12, rng() % 2);
        return sx(b);
    }
    case 'Y': {
        const u32 b = block(4096);
        for (u32 k = 0; k < 4; ++k) st16(m, b + 788 * k + 16, static_cast<u16>(rng() % 6));
        return sx(b);
    }
    case 'Q': {
        const u32 b = block(288);
        st32(m, b + 224, act);
        return sx(b);
    }
    case 'S': return sx(chance(rng, 85) ? pick(o.slots, rng, block(3920)) : block(3920));
    case 'B': return sx(chance(rng, 85) ? pick(o.entries, rng, block(2624)) : block(2624));
    case 'N': return sx(chance(rng, 90) ? pick(o.nodes, rng, block(304)) : block(304));
    case 'L':
    case 'I': {
        const u32 b = block(32);
        for (u32 i = 0; i < 16; ++i) st16(m, b + 2 * i, static_cast<u16>(chance(rng, 15) ? 0 : rng() % (kind == 'L' ? 464 : 300)));
        return sx(b);
    }
    case 'c': {
        static const u32 kPreds[] = {0x2C1710u, 0x2C1E10u, 0x2C1ED0u, 0x2C30F0u, 0x2C3120u};
        return kPreds[rng() % 5];
    }
    case 'k': return chance(rng, 5) ? sx(0xFFFFFFFFu) : rng() % (chance(rng, 90) ? 464 : 624);
    case 'e': return sx(static_cast<u32>(static_cast<int>(rng() % 20) - 1));
    case 'x': {
        static const u32 kMasks[] = {0u, 0x80000u, 0x100000u, 0x100261u, 0x180000u, 0xFFFFFu, 0x4u};
        return kMasks[rng() % 7];
    }
    case 'M': return 1 + rng() % 15;
    case 'u': return chance(rng, 80) ? pick(o.uids, rng, 0u) : rng() % 0x400;
    case 'i': return chance(rng, 80) ? pick(o.ids, rng, u16{1}) : rng() % 340;
    case 'm': return rng() % 26;
    case 'g': return rng() % 13;
    case 'n': return rng() % 8;
    case 'b': return rng() % 3;
    case 'd': return 1 + rng() % 6;
    case 'f': return rng() & 0x3F;
    case 'C': return rng();
    case 'F': return rng() % 60;
    case 'E': return 200 + rng() % 140;
    case 'o': return sx(block(64));
    case 't': {  // a short text
        static const char* kTexts[] = {"", "Attack", "The enemy is down!", "One more!"};
        const u32 b = block(32);
        const char* t = kTexts[rng() % 4];
        std::memcpy(m.at(b), t, std::strlen(t) + 1);
        return sx(b);
    }
    case 'w': {  // a font line chain of 1..3 nodes linked by +36
        const u32 a = block(64), b = block(64);
        st32(m, a + 36, chance(rng, 50) ? b : 0);
        st32(m, b + 36, 0);
        return sx(a);
    }
    case 'v': {
        const u32 b = block(16);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 4 * i, static_cast<float>(static_cast<int>(rng() % 3600) - 1800) / 1.5f);
        return sx(b);
    }
    case 'q': {
        const u32 b = block(16);
        float q[4], n2 = 0;
        for (float& x : q) {
            x = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 1000.0f;
            n2 += x * x;
        }
        const float s = n2 > 0 ? 1.0f / std::sqrt(n2) : 1.0f;
        for (u32 i = 0; i < 4; ++i) stf(m, b + 4 * i, q[i] * s);
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

// b_5800: the first battle in state ACTION (4 actions, 7 units, 15 packets) -- most pairs; battle_ref_6150 / b_6150:
// the battle over (RESULT, empty lists); b_6300 / b_6700 / climb_ref_17000: no battle (gBtl 0): the null paths.
struct Snap {
    const char* dir;
    u32 reps;
};
const Snap kSnapshots[] = {{"b_5800", 24}, {"battle_ref_6150", 3}, {"b_6150", 2}, {"b_6300", 1}, {"b_6700", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle4): every body equals its recompiled body on random worlds") {
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
        // sub_2BC480 (the effect archive loader) spins on H_Cdvd_ReadSync of a request that never completes when a
        // random world's gBtl test bit reads as set -- in both bodies: it is paired on the battle snapshots only.
        if (c.addr == 0x2BC480u) continue;
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

TEST_CASE("game(battle4): every body on the battle snapshots, perturbed") {
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
                                    << " units, " << o.data.size() << " packet data blocks, " << o.slots.size() << " info slots, "
                                    << o.entries.size() << " bpc entries, " << o.nodes.size() << " path nodes");
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
// A script header with one procedure section (type 0) naming `names` (32 bytes each), as scrFindPrcdIdxByName reads it.
u32 fake_script(Machine& m, const std::vector<std::string>& names) {
    const u32 s = kScratch + 0x13000u;
    std::memset(m.at(s), 0, 0x1000);
    st32(m, s + 16, 1);           // sections
    st32(m, s + 32, 0);           // section 0: type 0 = procedures
    st32(m, s + 40, static_cast<u32>(names.size()));
    st32(m, s + 44, 0x100);       // their table
    for (std::size_t i = 0; i < names.size(); ++i) std::memcpy(m.at(s + 0x100 + 32 * static_cast<u32>(i)), names[i].c_str(), names[i].size() + 1);
    return s;
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

TEST_CASE("game(battle4): the battle code follows the documented rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    // (1) btlBossSetup: the boss encounters 416..436 / 456 -- rule flags, AI rows, mode word, the three AI_EVENT
    //     procedure lookups (and +2856, the boss task, cleared), nothing for other encounters.
    {
        const u32 base = 0x01A00000u;
        for (u32 e = 410; e <= 460; ++e) {
            const Fake f = fake_battle(*m, static_cast<u16>(e));
            st32(*m, kGpVa + b4::kGpBossAiTbl, base);
            std::vector<std::string> names = {"AI_EVENT_" + fmt_hex3(e) + "_ACTEND", "OTHER"};
            if (e % 2 == 0) names.push_back("AI_EVENT_" + fmt_hex3(e) + "_BTLSTART");
            st32(*m, kGpVa + b4::kGpBossScript, fake_script(*m, names));
            const u32 flags0 = 0x04010402u | 0x80u;
            st32(*m, f.btl + b3::gbtl::kFlags, flags0);
            st32(*m, f.btl + b3::gbtl::kBossTask, 0x1234u);
            st32(*m, f.btl + b4::gbtl4::kBossBlock + 40, 0xFFFFFFFFu);  // inside the cleared block
            solo(*m, &rg::fn_btlBossSetup_002f6e00, {0, 0, 0, 0});
            const bool boss = e >= 416 && e <= 436;
            u32 flags = flags0, rules = 0, rows = 0, mode = 0;
            if (boss) {
                flags = (flags & ~0x10000u & ~0x4000000u) | 0x200000u;
                if (e == 429 || e == 436) flags &= ~0x400u;
                rules = 0x1u | 0x2u | 0x8u | 0x10u;
                if (e == 416 || (e >= 424 && e <= 427) || (e >= 430 && e <= 432)) rules |= 0x80u;
                if (e == 429) rules |= 0x20u, mode = 2;
                rows = base + 1044u * (e - 415u);
            } else if (e == 456) {
                flags &= ~0x10000u & ~0x4000000u;
                rules = 0x40u | 0x1u | 0x10u;
                rows = base;
                mode = 1;
            }
            INFO("encounter " << e);
            CHECK(ld32(*m, f.btl + b3::gbtl::kFlags) == flags);
            CHECK(ld32(*m, f.btl + b4::gbtl4::kRules) == rules);
            CHECK(ld32(*m, f.btl + b4::gbtl4::kBossAiRows) == rows);
            CHECK(ld16(*m, f.btl + b4::gbtl4::kBossMode) == mode);
            CHECK(ld32(*m, f.btl + b4::gbtl4::kBossBlock + 40) == 0u);
            CHECK(static_cast<s32>(ld32(*m, f.btl + b4::gbtl4::kBossEvtStart)) == (e % 2 == 0 ? 2 : -1));
            CHECK(static_cast<s32>(ld32(*m, f.btl + b4::gbtl4::kBossEvtActStart)) == -1);
            CHECK(static_cast<s32>(ld32(*m, f.btl + b4::gbtl4::kBossEvtActEnd)) == 0);
            CHECK(ld32(*m, f.btl + b3::gbtl::kBossTask) == 0u);
            ++checks;
        }
    }
    // (2) the boss sound paks: "snd_benc/boss/eXXX.pak" with the encounter id in hex into the boss block's first word
    for (u32 e = 414; e <= 458; ++e) {
        const Fake f = fake_battle(*m, static_cast<u16>(e));
        st32(*m, f.btl + b4::gbtl4::kBossBlock, 0xABCDu);
        solo(*m, &rg::fn_sub_2F9710_002f9710, {0, 0, 0, 0});
        const bool has = (e >= 416 && e <= 436) || e == 456;
        INFO("encounter " << e);
        CHECK(last_request_path() == (has ? cd_path("snd_benc/boss/e" + fmt_hex3(e) + ".pak") : std::string()));
        if (!has) CHECK(ld32(*m, f.btl + b4::gbtl4::kBossBlock) == 0xABCDu);
        else CHECK(ld32(*m, f.btl + b4::gbtl4::kBossBlock) != 0xABCDu);
        ++checks;
    }
    // (3) the skill effect / sound file names
    for (u32 skill : {0u, 1u, 0x2Au, 0x100u, 0x1CFu, 0xFFFu}) {
        const Fake f = fake_battle(*m, 1);
        for (u32 test = 0; test < 2; ++test) {
            st32(*m, f.btl + b4::gbtl4::kTestFlags, test);
            const u32 out = kScratch + 0x14000u;
            std::memset(m->at(out), 0, 64);
            solo(*m, &rg::fn_sub_2BB6F0_002bb6f0, {skill, sx(out), 0, 0});
            CHECK(guest_str(*m, out) == (test ? std::string("battle/BTL_TEST.BED") : "skill/" + fmt_hex3(skill) + ".BED"));
            ++checks;
        }
        for (u32 flag = 0; flag < 2; ++flag) {
            const u32 d = kScratch + 0x14100u;
            std::memset(m->at(d), 0xEE, 16);
            st16(*m, d + 4, static_cast<u16>(skill));
            st16(*m, d + 12, static_cast<u16>(flag));
            solo(*m, &rg::fn_sub_2DD270_002dd270, {sx(d), 0, 0, 0});
            CHECK(last_request_path() == (flag ? std::string() : cd_path("skill/" + fmt_hex3(skill) + ".se")));
            if (flag) CHECK(ld32(*m, d + 8) == 0u);
            CHECK(ld16(*m, d + 6) == 1u);
            CHECK(ld32(*m, d) == 0u);
            ++checks;
        }
    }
    // (4) ground-plane geometry: distances, the side test, the quaternion angle (host float models)
    {
        std::mt19937 rng{0xB4u};
        auto rnd = [&] { return static_cast<float>(static_cast<int>(rng() % 4001) - 2000) / 3.0f; };
        const u32 a = kScratch + 0x15000u, b = a + 16, c = a + 32;
        for (int k = 0; k < 300; ++k) {
            float p[3] = {rnd(), rnd(), rnd()}, q[3] = {rnd(), rnd(), rnd()}, r[3] = {rnd(), rnd(), rnd()};
            for (u32 i = 0; i < 3; ++i) stf(*m, a + 4 * i, p[i]), stf(*m, b + 4 * i, q[i]), stf(*m, c + 4 * i, r[i]);
            const float d3 = std::sqrt((p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]) + (p[2] - q[2]) * (p[2] - q[2]));
            const float d2 = std::sqrt((p[0] - q[0]) * (p[0] - q[0]) + (p[2] - q[2]) * (p[2] - q[2]));
            CHECK(std::fabs(f0_of(solo(*m, &rg::fn_sub_2D1E70_002d1e70, {sx(a), sx(b), 0, 0})) - d3) <= 1e-3f * (1 + d3));
            CHECK(std::fabs(f0_of(solo(*m, &rg::fn_sub_2D1ED0_002d1ed0, {sx(a), sx(b), 0, 0})) - d2) <= 1e-3f * (1 + d2));
            // the side test works on (x, z) = (+0, +4) of its points: the sign of cross(b - a, c - a), -1 when negative
            const double cross = static_cast<double>(q[0] - p[0]) * (r[1] - p[1]) - static_cast<double>(q[1] - p[1]) * (r[0] - p[0]);
            if (std::fabs(cross) > 1.0) {
                const s32 side = static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2D2EE0_002d2ee0, {sx(a), sx(b), sx(c), 0})));
                INFO("cross " << cross);
                CHECK(side == (cross < 0 ? -1 : 1));
            }
            ++checks;
        }
        for (int k = 0; k < 100; ++k) {
            float q1[4], q2[4], n1 = 0, n2 = 0;
            for (u32 i = 0; i < 4; ++i) q1[i] = rnd(), q2[i] = rnd(), n1 += q1[i] * q1[i], n2 += q2[i] * q2[i];
            for (u32 i = 0; i < 4; ++i) stf(*m, a + 4 * i, q1[i] / std::sqrt(n1)), stf(*m, b + 4 * i, q2[i] / std::sqrt(n2));
            double dot = 0;
            for (u32 i = 0; i < 4; ++i) dot += static_cast<double>(q1[i] / std::sqrt(n1)) * (q2[i] / std::sqrt(n2));
            const double want = 2.0 * std::acos(std::min(1.0, std::fabs(dot)));
            CHECK(std::fabs(f0_of(solo(*m, &rg::fn_sub_2D1F30_002d1f30, {sx(a), sx(b), 0, 0})) - want) <= 2e-3);
            ++checks;
        }
    }
    // (5) the voice line maps: sub_2D9BE0 (party id -> 346..354, no id 6), sub_2E0F70 (a member's line on 1..4 enemies left)
    {
        static const s32 kBase[11] = {-1, 346, 347, 348, 349, 350, -1, 351, 352, 353, 354};
        for (u16 id = 0; id <= 11; ++id)
            for (u8 side = 0; side < 2; ++side) {
                const Fake f = fake_battle(*m, 1);
                st8(*m, f.unit + b3::unit::kSide, side);
                st16(*m, f.unit + b3::unit::kId, id);
                const s32 got = static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2D9BE0_002d9be0, {sx(f.act), 0, 0, 0})));
                CHECK(got == (side == 0 && id <= 10 ? kBase[id] : -1));
                ++checks;
            }
    }
    // (6) the battle panel registries: a register stores its work in the $gp slot, the matching release clears it
    {
        struct Reg {
            Fn reg, rel;
            s32 slot;
        };
        const Reg regs[] = {{&rg::fn_sub_24A6C0_0024a6c0, &rg::fn_sub_24A6D0_0024a6d0, b4::kGpBpWork32C},
                            {&rg::fn_sub_251F20_00251f20, &rg::fn_sub_251F30_00251f30, b4::kGpBpoWork},
                            {&rg::fn_sub_252E60_00252e60, &rg::fn_sub_252E80_00252e80, b4::kGpBpdWork},
                            {&rg::fn_sub_25CF00_0025cf00, &rg::fn_sub_25CF10_0025cf10, b4::kGpBpRushWork}};
        for (const Reg& r : regs) {
            const u32 w = kScratch + 0x16000u;
            st32(*m, w, 0xFFFFFFFFu);
            solo(*m, r.reg, {sx(w), 0, 0, 0});
            CHECK(ld32(*m, kGpVa + r.slot) == w);
            CHECK(ld32(*m, w) == 0u);
            solo(*m, r.rel, {0, 0, 0, 0});
            CHECK(ld32(*m, kGpVa + r.slot) == 0u);
            ++checks;
        }
    }
    // (7) the battle info slots: allocation takes the first free slot (flags 1), the free / owner tests
    {
        const u32 w = kScratch + 0x20000u;
        std::memset(m->at(w), 0, 16 * 3920);
        st32(*m, kGpVa + b4::kGpBiWork, w);
        std::mt19937 rng{0xB1u};
        for (int k = 0; k < 40; ++k) {
            u32 used = 0;
            for (u32 s = 0; s < 16; ++s) {
                const bool live = k == 39 ? true : chance(rng, 60);
                st32(*m, w + 3920 * s, live ? 1u : 0u);
                st32(*m, w + 3920 * s + b4::bi::kOwner, rng() % 4);
                used |= live ? 1u << s : 0;
            }
            const u32 owner = rng() % 4;
            bool own = false;
            for (u32 s = 0; s < 16; ++s) own |= (used >> s & 1) && ld32(*m, w + 3920 * s + b4::bi::kOwner) == owner;
            CHECK(v0_of(solo(*m, &rg::fn_sub_242A60_00242a60, {0, 0, 0, 0})) == (used != 0xFFFFu ? 1u : 0u));
            CHECK(v0_of(solo(*m, &rg::fn_sub_242AE0_00242ae0, {owner, 0, 0, 0})) == (own ? 1u : 0u));
            if (used != 0xFFFFu) {
                u32 first = 0;
                while (used >> first & 1) ++first;
                CHECK(static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_242260_00242260, {0, 0, 0, 0}))) == w + 3920 * first);
                CHECK(ld32(*m, w + 3920 * first) == 1u);
            }
            ++checks;
        }
    }
    // (8) the path search's open list: sub_2D4810 unlinks and returns the node of lowest cost
    {
        const Fake f = fake_battle(*m, 1);
        std::mt19937 rng{0x2D48u};
        for (int k = 0; k < 60; ++k) {
            const u32 n = 1 + rng() % 8, nodes = kScratch + 0x17000u;
            u32 best = 0;
            float bestc = 1e30f;
            for (u32 i = 0; i < n; ++i) {
                const u32 nd = nodes + 64 * i;
                const float cost = static_cast<float>(rng() % 5000) / 7.0f;
                stf(*m, nd + b4::path::kCost, cost);
                st32(*m, nd + b4::path::kNextOpen, i + 1 < n ? nd + 64 : 0);
                if (cost < bestc) bestc = cost, best = nd;
            }
            st32(*m, f.btl + b4::gbtl4::kPathOpen, nodes);
            CHECK(static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_2D4810_002d4810, {0, 0, 0, 0}))) == best);
            u32 left = 0;
            bool found = false;
            for (u32 p = ld32(*m, f.btl + b4::gbtl4::kPathOpen); p && left < 16; p = ld32(*m, p + b4::path::kNextOpen), ++left) found |= p == best;
            CHECK(left == n - 1);
            CHECK(!found);
            ++checks;
        }
    }
    // (9) the analysed-enemy records (gBtl +2656: s8 side, u16 base id; -1 = free): a unit's record is found or taken
    {
        const Fake f = fake_battle(*m, 1);
        for (u32 k = 0; k < 12; ++k) st8(*m, f.btl + b4::gbtl4::kAnalysis + 4 * k, 0xFF);
        // one enemy unit in side 1 with base id 77; the action's unit (side 1, base id 77) maps to a new record
        st32(*m, f.btl + b3::gbtl::kUnitHead1, f.unit);
        st8(*m, f.unit + b3::unit::kSide, 1);
        st16(*m, f.dat + b3::dat::kBaseId, 77);
        const u32 r1 = static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_2E3120_002e3120, {sx(f.act), 0, 0, 0})));
        CHECK(r1 == f.btl + b4::gbtl4::kAnalysis);
        CHECK(ld8(*m, r1) == 1u);
        CHECK(ld16(*m, r1 + 2) == 77u);
        const u32 r2 = static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_2E3120_002e3120, {sx(f.act), 0, 0, 0})));
        CHECK(r2 == r1);
        // a record whose enemy left the battle is dropped
        st8(*m, f.btl + b4::gbtl4::kAnalysis + 4, 1);
        st16(*m, f.btl + b4::gbtl4::kAnalysis + 6, 99);
        solo(*m, &rg::fn_sub_2E3120_002e3120, {sx(f.act), 0, 0, 0});
        CHECK(ld8(*m, f.btl + b4::gbtl4::kAnalysis + 4) == 0xFFu);
        CHECK(ld16(*m, f.btl + b4::gbtl4::kAnalysis + 6) == 0u);
        checks += 3;
    }
    // (10) the navigator's opening line on the battle snapshot against the host model of sub_2D8390
    {
        const std::vector<u8> snap = read_snapshot("b_5800");
        if (!snap.empty()) {
            std::mt19937 rng{0x2D83u};
            for (int k = 0; k < 60; ++k) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                write_rw_slots(*m);
                const Objects o = objects_of(*m);
                if (!o.btl) break;
                for (u32 d : o.dats)
                    if (chance(rng, 30)) st32(*m, d + b3::dat::kStatus, chance(rng, 50) ? 2u : 0u);
                st16(*m, o.btl + b3::gbtl::kAdvantage, static_cast<u16>(rng() % 4));
                const u32 count = static_cast<u16>(v0_of(solo(*m, &rg::fn_btlCountActiveUnits_002d4e10, {2, 0x80000, 0, 0})));
                const u32 mean = static_cast<u16>(v0_of(solo(*m, &rg::fn_btlGetMeanLevel_002d4cf0, {2, 0x80000, 0, 0})));
                const u32 hero = ld32(*m, o.btl + b3::gbtl::kPlayerAction);
                const u32 hlv = ld8(*m, ld32(*m, ld32(*m, hero + b3::act::kUnit) + b3::unit::kDat) + b3::dat::kLevel);
                bool sleep = false, rare = false, strong = false;
                const u32 etbl = ld32(*m, kGpVa + b4::kGpEnemyTbl);
                for (u32 u = ld32(*m, o.btl + b4::gbtl4::kUnitTail1); in_ram(u); u = ld32(*m, u + b3::unit::kPrev)) {
                    sleep |= (ld32(*m, ld32(*m, u + b3::unit::kDat) + b3::dat::kStatus) & 2u) != 0;
                    const u16 fl = ld16(*m, etbl + 62u * ld16(*m, u + b3::unit::kId));
                    rare |= (fl & 0x40) != 0;
                    strong |= (fl & 0x80) != 0;
                }
                const bool high = static_cast<s32>(mean - hlv) >= 4;
                const u16 adv = ld16(*m, o.btl + b3::gbtl::kAdvantage);
                s32 want = -1;
                if (count < 6) {
                    if (adv == 2) want = strong ? 92 : rare ? 93 : static_cast<s32>(count + (high ? 86 : 81));
                    else if (adv == 1) want = strong ? 80 : rare ? 81 : static_cast<s32>(count + (high ? 69 : 59) + (sleep ? 5 : 0));
                    else if (adv == 0) want = strong ? 10 : rare ? 11 : static_cast<s32>(count + (high ? 4 : 0)) - (high ? 0 : 1);
                }
                INFO("advantage " << adv << " count " << count << " mean " << mean << " hero level " << hlv);
                CHECK(static_cast<s32>(v0_of(solo(*m, &rg::fn_sub_2D8390_002d8390, {0, 0, 0, 0}))) == want);
                ++checks;
            }
        }
    }
    MESSAGE("documented rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle4): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
