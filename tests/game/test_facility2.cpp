// Pair tests of slice facility2 (game/src/facility/facility2_*.cpp): every hand body against its recompiled body, both
// on identical guest machines, compared by tests/game/handgen_pairs.h (the whole register file and cycles at every
// check point and at the return / stop, all 32 MiB of RAM -- the dead stack and the stand-in heap included --, the
// scratchpad, the BIOS window, the bus log) and, through stand-in worlds (tests/game/stand_ins.h: the heap behind the RW
// slots and H_Malloc, printf / sprintf, the H_Cdvd layer), the two call logs.
//   1. Random worlds: all 121 functions.
//   2. The quantity selector of BUY / SELL on hand-made selectors over the shop snapshot (yen, owned counts, the stock
//      block): every key, every clamp; the counts, flags and results against the documented rule.
//   3. Weapon fusion: the best-stat mask, the fusion-flag table, the level bands, the recipe search and the order, on
//      the fusion snapshot's stock personas and 120 made-up personas; every result against a host model of the ELF's
//      tables.
//   4. Elizabeth's requests: the 100 records' accessors (those not stood in by test_ui6) against the table, the deadline
//      of every request on three dates,
//      accept / cancel / the flag, the request list (sort order, update, the eight animation parts, the draws, destroy).
//   5. The compendium: the list filled from the save's registered personas (price rule with and without game flag 4889),
//      both sorts against host comparators, register-all, the stock test, destroy.
//   6. The trade and weapon-fusion lists built on the shop snapshot (every row against the tables, the owned counts and
//      the availability rule), then every list function on them: refresh, update, window animations over 24 frames in
//      each status, row drawers on every row, the old-list compare and mark, destroy.
//   7. A lineup filled into a buy list with every filter, the price rate rule and the sale rule.
//   8. The shop steps' callbacks on the live shop sequence, the panel drivers and part animator, the option rows, the
//      date panel on three dates (its sprintf texts against the calendar).
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function (random worlds), one function, a trace line per pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/facility2.h"

#include <algorithm>
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
namespace f2 = p3fes::game::fac2;

namespace p3fes::recomp_gen {
void fn_sub_3D3170_003d3170(EEContext&);  // generated body
void fn_sub_3D3170_003d3170__recomp(EEContext&);  // recompiled
void fn_sub_3D3760_003d3760(EEContext&);  // generated body
void fn_sub_3D3760_003d3760__recomp(EEContext&);  // recompiled
void fn_sub_3D9820_003d9820(EEContext&);  // generated body
void fn_sub_3D9820_003d9820__recomp(EEContext&);  // recompiled
void fn_sub_3DCA10_003dca10(EEContext&);  // generated body
void fn_sub_3DCA10_003dca10__recomp(EEContext&);  // recompiled
void fn_sub_3DCFB0_003dcfb0(EEContext&);  // generated body
void fn_sub_3DCFB0_003dcfb0__recomp(EEContext&);  // recompiled
void fn_sub_3E0940_003e0940(EEContext&);  // generated body
void fn_sub_3E0940_003e0940__recomp(EEContext&);  // recompiled
void fn_sub_3E6E20_003e6e20(EEContext&);  // generated body
void fn_sub_3E6E20_003e6e20__recomp(EEContext&);  // recompiled
void fn_sub_3EAEB0_003eaeb0(EEContext&);  // generated body
void fn_sub_3EAEB0_003eaeb0__recomp(EEContext&);  // recompiled
void fn_sub_3EAF30_003eaf30(EEContext&);  // generated body
void fn_sub_3EAF30_003eaf30__recomp(EEContext&);  // recompiled
void fn_sub_3EB940_003eb940(EEContext&);  // generated body
void fn_sub_3EB940_003eb940__recomp(EEContext&);  // recompiled
void fn_sub_3EBB90_003ebb90(EEContext&);  // generated body
void fn_sub_3EBB90_003ebb90__recomp(EEContext&);  // recompiled
void fn_sub_3EBC70_003ebc70(EEContext&);  // generated body
void fn_sub_3EBC70_003ebc70__recomp(EEContext&);  // recompiled
void fn_sub_3EBFE0_003ebfe0(EEContext&);  // generated body
void fn_sub_3EBFE0_003ebfe0__recomp(EEContext&);  // recompiled
void fn_sub_3EC280_003ec280(EEContext&);  // generated body
void fn_sub_3EC280_003ec280__recomp(EEContext&);  // recompiled
void fn_sub_3EC6A0_003ec6a0(EEContext&);  // generated body
void fn_sub_3EC6A0_003ec6a0__recomp(EEContext&);  // recompiled
void fn_sub_3EC8E0_003ec8e0(EEContext&);  // generated body
void fn_sub_3EC8E0_003ec8e0__recomp(EEContext&);  // recompiled
void fn_sub_3ECCE0_003ecce0(EEContext&);  // generated body
void fn_sub_3ECCE0_003ecce0__recomp(EEContext&);  // recompiled
void fn_sub_3ECF80_003ecf80(EEContext&);  // generated body
void fn_sub_3ECF80_003ecf80__recomp(EEContext&);  // recompiled
void fn_sub_3ED310_003ed310(EEContext&);  // generated body
void fn_sub_3ED310_003ed310__recomp(EEContext&);  // recompiled
void fn_sub_3ED5A0_003ed5a0(EEContext&);  // generated body
void fn_sub_3ED5A0_003ed5a0__recomp(EEContext&);  // recompiled
void fn_sub_3EDD80_003edd80(EEContext&);  // generated body
void fn_sub_3EDD80_003edd80__recomp(EEContext&);  // recompiled
void fn_sub_3EE4E0_003ee4e0(EEContext&);  // generated body
void fn_sub_3EE4E0_003ee4e0__recomp(EEContext&);  // recompiled
void fn_sub_3EE640_003ee640(EEContext&);  // generated body
void fn_sub_3EE640_003ee640__recomp(EEContext&);  // recompiled
void fn_sub_3EEE50_003eee50(EEContext&);  // generated body
void fn_sub_3EEE50_003eee50__recomp(EEContext&);  // recompiled
void fn_sub_3EFC20_003efc20(EEContext&);  // generated body
void fn_sub_3EFC20_003efc20__recomp(EEContext&);  // recompiled
void fn_sub_3F1910_003f1910(EEContext&);  // generated body
void fn_sub_3F1910_003f1910__recomp(EEContext&);  // recompiled
void fn_sub_3F1BA0_003f1ba0(EEContext&);  // generated body
void fn_sub_3F1BA0_003f1ba0__recomp(EEContext&);  // recompiled
void fn_sub_3F2320_003f2320(EEContext&);  // generated body
void fn_sub_3F2320_003f2320__recomp(EEContext&);  // recompiled
void fn_sub_3F25E0_003f25e0(EEContext&);  // generated body
void fn_sub_3F25E0_003f25e0__recomp(EEContext&);  // recompiled
void fn_sub_3F3E60_003f3e60(EEContext&);  // generated body
void fn_sub_3F3E60_003f3e60__recomp(EEContext&);  // recompiled
void fn_sub_3F4A90_003f4a90(EEContext&);  // generated body
void fn_sub_3F4A90_003f4a90__recomp(EEContext&);  // recompiled
void fn_sub_3F5AB0_003f5ab0(EEContext&);  // generated body
void fn_sub_3F5AB0_003f5ab0__recomp(EEContext&);  // recompiled
void fn_sub_3F5D10_003f5d10(EEContext&);  // generated body
void fn_sub_3F5D10_003f5d10__recomp(EEContext&);  // recompiled
void fn_sub_3F5F50_003f5f50(EEContext&);  // generated body
void fn_sub_3F5F50_003f5f50__recomp(EEContext&);  // recompiled
void fn_sub_3F61D0_003f61d0(EEContext&);  // generated body
void fn_sub_3F61D0_003f61d0__recomp(EEContext&);  // recompiled
void fn_sub_3F67E0_003f67e0(EEContext&);  // generated body
void fn_sub_3F67E0_003f67e0__recomp(EEContext&);  // recompiled
void fn_sub_3F6F20_003f6f20(EEContext&);  // generated body
void fn_sub_3F6F20_003f6f20__recomp(EEContext&);  // recompiled
void fn_sub_3F7890_003f7890(EEContext&);  // generated body
void fn_sub_3F7890_003f7890__recomp(EEContext&);  // recompiled
void fn_sub_3F9510_003f9510(EEContext&);  // generated body
void fn_sub_3F9510_003f9510__recomp(EEContext&);  // recompiled
void fn_sub_3FA210_003fa210(EEContext&);  // generated body
void fn_sub_3FA210_003fa210__recomp(EEContext&);  // recompiled
void fn_sub_3FA520_003fa520(EEContext&);  // generated body
void fn_sub_3FA520_003fa520__recomp(EEContext&);  // recompiled
void fn_sub_3FA800_003fa800(EEContext&);  // generated body
void fn_sub_3FA800_003fa800__recomp(EEContext&);  // recompiled
void fn_sub_3FAAE0_003faae0(EEContext&);  // generated body
void fn_sub_3FAAE0_003faae0__recomp(EEContext&);  // recompiled
void fn_sub_3FADC0_003fadc0(EEContext&);  // generated body
void fn_sub_3FADC0_003fadc0__recomp(EEContext&);  // recompiled
void fn_sub_3FB0C0_003fb0c0(EEContext&);  // generated body
void fn_sub_3FB0C0_003fb0c0__recomp(EEContext&);  // recompiled
void fn_sub_3FB2F0_003fb2f0(EEContext&);  // generated body
void fn_sub_3FB2F0_003fb2f0__recomp(EEContext&);  // recompiled
void fn_sub_3FB530_003fb530(EEContext&);  // generated body
void fn_sub_3FB530_003fb530__recomp(EEContext&);  // recompiled
void fn_sub_3FBF10_003fbf10(EEContext&);  // generated body
void fn_sub_3FBF10_003fbf10__recomp(EEContext&);  // recompiled
void fn_sub_3FCA00_003fca00(EEContext&);  // generated body
void fn_sub_3FCA00_003fca00__recomp(EEContext&);  // recompiled
void fn_sub_3FCBE0_003fcbe0(EEContext&);  // generated body
void fn_sub_3FCBE0_003fcbe0__recomp(EEContext&);  // recompiled
void fn_sub_3FD140_003fd140(EEContext&);  // generated body
void fn_sub_3FD140_003fd140__recomp(EEContext&);  // recompiled
void fn_sub_3FD7E0_003fd7e0(EEContext&);  // generated body
void fn_sub_3FD7E0_003fd7e0__recomp(EEContext&);  // recompiled
void fn_sub_3FD8E0_003fd8e0(EEContext&);  // generated body
void fn_sub_3FD8E0_003fd8e0__recomp(EEContext&);  // recompiled
void fn_sub_3FD990_003fd990(EEContext&);  // generated body
void fn_sub_3FD990_003fd990__recomp(EEContext&);  // recompiled
void fn_sub_3FE1F0_003fe1f0(EEContext&);  // generated body
void fn_sub_3FE1F0_003fe1f0__recomp(EEContext&);  // recompiled
void fn_sub_3FE3E0_003fe3e0(EEContext&);  // generated body
void fn_sub_3FE3E0_003fe3e0__recomp(EEContext&);  // recompiled
void fn_sub_3FE5D0_003fe5d0(EEContext&);  // generated body
void fn_sub_3FE5D0_003fe5d0__recomp(EEContext&);  // recompiled
void fn_sub_3FE690_003fe690(EEContext&);  // generated body
void fn_sub_3FE690_003fe690__recomp(EEContext&);  // recompiled
void fn_sub_3FE7D0_003fe7d0(EEContext&);  // generated body
void fn_sub_3FE7D0_003fe7d0__recomp(EEContext&);  // recompiled
void fn_sub_3FE850_003fe850(EEContext&);  // generated body
void fn_sub_3FE850_003fe850__recomp(EEContext&);  // recompiled
void fn_sub_3FE950_003fe950(EEContext&);  // generated body
void fn_sub_3FE950_003fe950__recomp(EEContext&);  // recompiled
void fn_sub_3FEA10_003fea10(EEContext&);  // generated body
void fn_sub_3FEA10_003fea10__recomp(EEContext&);  // recompiled
void fn_sub_3FEB30_003feb30(EEContext&);  // generated body
void fn_sub_3FEB30_003feb30__recomp(EEContext&);  // recompiled
void fn_sub_3FEE40_003fee40(EEContext&);  // generated body
void fn_sub_3FEE40_003fee40__recomp(EEContext&);  // recompiled
void fn_sub_3FEF30_003fef30(EEContext&);  // generated body
void fn_sub_3FEF30_003fef30__recomp(EEContext&);  // recompiled
void fn_sub_3FF150_003ff150(EEContext&);  // generated body
void fn_sub_3FF150_003ff150__recomp(EEContext&);  // recompiled
void fn_sub_3FF460_003ff460(EEContext&);  // generated body
void fn_sub_3FF460_003ff460__recomp(EEContext&);  // recompiled
void fn_sub_3FF570_003ff570(EEContext&);  // generated body
void fn_sub_3FF570_003ff570__recomp(EEContext&);  // recompiled
void fn_sub_4003A0_004003a0(EEContext&);  // generated body
void fn_sub_4003A0_004003a0__recomp(EEContext&);  // recompiled
void fn_sub_4006C0_004006c0(EEContext&);  // generated body
void fn_sub_4006C0_004006c0__recomp(EEContext&);  // recompiled
void fn_sub_4008F0_004008f0(EEContext&);  // generated body
void fn_sub_4008F0_004008f0__recomp(EEContext&);  // recompiled
void fn_sub_400E30_00400e30(EEContext&);  // generated body
void fn_sub_400E30_00400e30__recomp(EEContext&);  // recompiled
void fn_sub_4016D0_004016d0(EEContext&);  // generated body
void fn_sub_4016D0_004016d0__recomp(EEContext&);  // recompiled
void fn_sub_401800_00401800(EEContext&);  // generated body
void fn_sub_401800_00401800__recomp(EEContext&);  // recompiled
void fn_sub_401A00_00401a00(EEContext&);  // generated body
void fn_sub_401A00_00401a00__recomp(EEContext&);  // recompiled
void fn_sub_401C90_00401c90(EEContext&);  // generated body
void fn_sub_401C90_00401c90__recomp(EEContext&);  // recompiled
void fn_sub_401CF0_00401cf0(EEContext&);  // generated body
void fn_sub_401CF0_00401cf0__recomp(EEContext&);  // recompiled
void fn_sub_401D90_00401d90(EEContext&);  // generated body
void fn_sub_401D90_00401d90__recomp(EEContext&);  // recompiled
void fn_sub_401DE0_00401de0(EEContext&);  // generated body
void fn_sub_401DE0_00401de0__recomp(EEContext&);  // recompiled
void fn_sub_402400_00402400(EEContext&);  // generated body
void fn_sub_402400_00402400__recomp(EEContext&);  // recompiled
void fn_sub_402510_00402510(EEContext&);  // generated body
void fn_sub_402510_00402510__recomp(EEContext&);  // recompiled
void fn_sub_4032F0_004032f0(EEContext&);  // generated body
void fn_sub_4032F0_004032f0__recomp(EEContext&);  // recompiled
void fn_sub_403340_00403340(EEContext&);  // generated body
void fn_sub_403340_00403340__recomp(EEContext&);  // recompiled
void fn_sub_403410_00403410(EEContext&);  // generated body
void fn_sub_403410_00403410__recomp(EEContext&);  // recompiled
void fn_sub_403760_00403760(EEContext&);  // generated body
void fn_sub_403760_00403760__recomp(EEContext&);  // recompiled
void fn_sub_403780_00403780(EEContext&);  // generated body
void fn_sub_403780_00403780__recomp(EEContext&);  // recompiled
void fn_sub_4037A0_004037a0(EEContext&);  // generated body
void fn_sub_4037A0_004037a0__recomp(EEContext&);  // recompiled
void fn_sub_4037C0_004037c0(EEContext&);  // generated body
void fn_sub_4037C0_004037c0__recomp(EEContext&);  // recompiled
void fn_sub_4037E0_004037e0(EEContext&);  // generated body
void fn_sub_4037E0_004037e0__recomp(EEContext&);  // recompiled
void fn_sub_403860_00403860(EEContext&);  // generated body
void fn_sub_403860_00403860__recomp(EEContext&);  // recompiled
void fn_sub_4038E0_004038e0(EEContext&);  // generated body
void fn_sub_4038E0_004038e0__recomp(EEContext&);  // recompiled
void fn_sub_404470_00404470(EEContext&);  // generated body
void fn_sub_404470_00404470__recomp(EEContext&);  // recompiled
void fn_sub_404750_00404750(EEContext&);  // generated body
void fn_sub_404750_00404750__recomp(EEContext&);  // recompiled
void fn_sub_405A90_00405a90(EEContext&);  // generated body
void fn_sub_405A90_00405a90__recomp(EEContext&);  // recompiled
void fn_sub_405D60_00405d60(EEContext&);  // generated body
void fn_sub_405D60_00405d60__recomp(EEContext&);  // recompiled
void fn_sub_405DB0_00405db0(EEContext&);  // generated body
void fn_sub_405DB0_00405db0__recomp(EEContext&);  // recompiled
void fn_sub_405E00_00405e00(EEContext&);  // generated body
void fn_sub_405E00_00405e00__recomp(EEContext&);  // recompiled
void fn_sub_405E30_00405e30(EEContext&);  // generated body
void fn_sub_405E30_00405e30__recomp(EEContext&);  // recompiled
void fn_sub_406AA0_00406aa0(EEContext&);  // generated body
void fn_sub_406AA0_00406aa0__recomp(EEContext&);  // recompiled
void fn_sub_407180_00407180(EEContext&);  // generated body
void fn_sub_407180_00407180__recomp(EEContext&);  // recompiled
void fn_sub_407210_00407210(EEContext&);  // generated body
void fn_sub_407210_00407210__recomp(EEContext&);  // recompiled
void fn_sub_409C80_00409c80(EEContext&);  // generated body
void fn_sub_409C80_00409c80__recomp(EEContext&);  // recompiled
void fn_sub_409E90_00409e90(EEContext&);  // generated body
void fn_sub_409E90_00409e90__recomp(EEContext&);  // recompiled
void fn_sub_409F20_00409f20(EEContext&);  // generated body
void fn_sub_409F20_00409f20__recomp(EEContext&);  // recompiled
void fn_sub_40A200_0040a200(EEContext&);  // generated body
void fn_sub_40A200_0040a200__recomp(EEContext&);  // recompiled
void fn_sub_40A260_0040a260(EEContext&);  // generated body
void fn_sub_40A260_0040a260__recomp(EEContext&);  // recompiled
void fn_sub_40A5B0_0040a5b0(EEContext&);  // generated body
void fn_sub_40A5B0_0040a5b0__recomp(EEContext&);  // recompiled
void fn_sub_40A640_0040a640(EEContext&);  // generated body
void fn_sub_40A640_0040a640__recomp(EEContext&);  // recompiled
void fn_sub_40A6D0_0040a6d0(EEContext&);  // generated body
void fn_sub_40A6D0_0040a6d0__recomp(EEContext&);  // recompiled
void fn_sub_40A7C0_0040a7c0(EEContext&);  // generated body
void fn_sub_40A7C0_0040a7c0__recomp(EEContext&);  // recompiled
void fn_sub_40B630_0040b630(EEContext&);  // generated body
void fn_sub_40B630_0040b630__recomp(EEContext&);  // recompiled
void fn_sub_40B780_0040b780(EEContext&);  // generated body
void fn_sub_40B780_0040b780__recomp(EEContext&);  // recompiled
void fn_sub_40C150_0040c150(EEContext&);  // generated body
void fn_sub_40C150_0040c150__recomp(EEContext&);  // recompiled
void fn_sub_40C1E0_0040c1e0(EEContext&);  // generated body
void fn_sub_40C1E0_0040c1e0__recomp(EEContext&);  // recompiled
void fn_sub_40C460_0040c460(EEContext&);  // generated body
void fn_sub_40C460_0040c460__recomp(EEContext&);  // recompiled
void fn_sub_40C520_0040c520(EEContext&);  // generated body
void fn_sub_40C520_0040c520__recomp(EEContext&);  // recompiled
void fn_sub_40C5B0_0040c5b0(EEContext&);  // generated body
void fn_sub_40C5B0_0040c5b0__recomp(EEContext&);  // recompiled
void fn_sub_40C650_0040c650(EEContext&);  // generated body
void fn_sub_40C650_0040c650__recomp(EEContext&);  // recompiled
void fn_sub_40C6A0_0040c6a0(EEContext&);  // generated body
void fn_sub_40C6A0_0040c6a0__recomp(EEContext&);  // recompiled
void fn_sub_40CA00_0040ca00(EEContext&);  // generated body
void fn_sub_40CA00_0040ca00__recomp(EEContext&);  // recompiled
void fn_sub_40D330_0040d330(EEContext&);  // generated body
void fn_sub_40D330_0040d330__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

// Hand-written (or emitted) callees the tests use to set worlds up and as oracles of the documented rules.
namespace p3fes::recomp_gen {
void fn_sub_3C58F0_003c58f0(EEContext&);   // [nmCmdListCreate](flags, size, rows, spacing)
void fn_nmCmdListAddRow_003c5a40(EEContext&);
void fn_sub_3DFEB0_003dfeb0(EEContext&);   // element set create
void fn_sub_17C960_0017c960(EEContext&);   // [datCompendiumStore](persona)
void fn_sub_17C8C0_0017c8c0(EEContext&);   // [datCompendiumGet](id)
void fn_sub_173580_00173580(EEContext&);   // persona stat without the equipment bonus
void fn_sub_173A00_00173a00(EEContext&);   // persona stat (the best-stat mask's)
void fn_sub_174A90_00174a90(EEContext&);   // stock persona of a slot
void fn_sub_175410_00175410(EEContext&);   // the stock size
void fn_datGetDaysSinceApr5_0016ef20(EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(EEContext&);
void fn_clndGetMonthFromDaysSinceApr5_0017d830(EEContext&);
void fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0(EEContext&);
void fn_clndGetCurrentMonth_0017d920(EEContext&);
void fn_clndGetCurrentDay_0017da40(EEContext&);
void fn_sub_17D250_0017d250(EEContext&);   // [datBlock30Get](a, key)
void fn_sub_3E6DC0_003e6dc0(EEContext&);   // the shop's date key
void fn_sub_170ED0_00170ed0(EEContext&);   // item record + kind
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_3D3170", 0x3D3170, &recomp_gen::fn_sub_3D3170_003d3170, &recomp_gen::fn_sub_3D3170_003d3170__recomp},
    {"sub_3D3760", 0x3D3760, &recomp_gen::fn_sub_3D3760_003d3760, &recomp_gen::fn_sub_3D3760_003d3760__recomp},
    {"sub_3D9820", 0x3D9820, &recomp_gen::fn_sub_3D9820_003d9820, &recomp_gen::fn_sub_3D9820_003d9820__recomp},
    {"sub_3DCA10", 0x3DCA10, &recomp_gen::fn_sub_3DCA10_003dca10, &recomp_gen::fn_sub_3DCA10_003dca10__recomp},
    {"sub_3DCFB0", 0x3DCFB0, &recomp_gen::fn_sub_3DCFB0_003dcfb0, &recomp_gen::fn_sub_3DCFB0_003dcfb0__recomp},
    {"sub_3E0940", 0x3E0940, &recomp_gen::fn_sub_3E0940_003e0940, &recomp_gen::fn_sub_3E0940_003e0940__recomp},
    {"sub_3E6E20", 0x3E6E20, &recomp_gen::fn_sub_3E6E20_003e6e20, &recomp_gen::fn_sub_3E6E20_003e6e20__recomp},
    {"sub_3EAEB0", 0x3EAEB0, &recomp_gen::fn_sub_3EAEB0_003eaeb0, &recomp_gen::fn_sub_3EAEB0_003eaeb0__recomp},
    {"sub_3EAF30", 0x3EAF30, &recomp_gen::fn_sub_3EAF30_003eaf30, &recomp_gen::fn_sub_3EAF30_003eaf30__recomp},
    {"sub_3EB940", 0x3EB940, &recomp_gen::fn_sub_3EB940_003eb940, &recomp_gen::fn_sub_3EB940_003eb940__recomp},
    {"sub_3EBB90", 0x3EBB90, &recomp_gen::fn_sub_3EBB90_003ebb90, &recomp_gen::fn_sub_3EBB90_003ebb90__recomp},
    {"sub_3EBC70", 0x3EBC70, &recomp_gen::fn_sub_3EBC70_003ebc70, &recomp_gen::fn_sub_3EBC70_003ebc70__recomp},
    {"sub_3EBFE0", 0x3EBFE0, &recomp_gen::fn_sub_3EBFE0_003ebfe0, &recomp_gen::fn_sub_3EBFE0_003ebfe0__recomp},
    {"sub_3EC280", 0x3EC280, &recomp_gen::fn_sub_3EC280_003ec280, &recomp_gen::fn_sub_3EC280_003ec280__recomp},
    {"sub_3EC6A0", 0x3EC6A0, &recomp_gen::fn_sub_3EC6A0_003ec6a0, &recomp_gen::fn_sub_3EC6A0_003ec6a0__recomp},
    {"sub_3EC8E0", 0x3EC8E0, &recomp_gen::fn_sub_3EC8E0_003ec8e0, &recomp_gen::fn_sub_3EC8E0_003ec8e0__recomp},
    {"sub_3ECCE0", 0x3ECCE0, &recomp_gen::fn_sub_3ECCE0_003ecce0, &recomp_gen::fn_sub_3ECCE0_003ecce0__recomp},
    {"sub_3ECF80", 0x3ECF80, &recomp_gen::fn_sub_3ECF80_003ecf80, &recomp_gen::fn_sub_3ECF80_003ecf80__recomp},
    {"sub_3ED310", 0x3ED310, &recomp_gen::fn_sub_3ED310_003ed310, &recomp_gen::fn_sub_3ED310_003ed310__recomp},
    {"sub_3ED5A0", 0x3ED5A0, &recomp_gen::fn_sub_3ED5A0_003ed5a0, &recomp_gen::fn_sub_3ED5A0_003ed5a0__recomp},
    {"sub_3EDD80", 0x3EDD80, &recomp_gen::fn_sub_3EDD80_003edd80, &recomp_gen::fn_sub_3EDD80_003edd80__recomp},
    {"sub_3EE4E0", 0x3EE4E0, &recomp_gen::fn_sub_3EE4E0_003ee4e0, &recomp_gen::fn_sub_3EE4E0_003ee4e0__recomp},
    {"sub_3EE640", 0x3EE640, &recomp_gen::fn_sub_3EE640_003ee640, &recomp_gen::fn_sub_3EE640_003ee640__recomp},
    {"sub_3EEE50", 0x3EEE50, &recomp_gen::fn_sub_3EEE50_003eee50, &recomp_gen::fn_sub_3EEE50_003eee50__recomp},
    {"sub_3EFC20", 0x3EFC20, &recomp_gen::fn_sub_3EFC20_003efc20, &recomp_gen::fn_sub_3EFC20_003efc20__recomp},
    {"sub_3F1910", 0x3F1910, &recomp_gen::fn_sub_3F1910_003f1910, &recomp_gen::fn_sub_3F1910_003f1910__recomp},
    {"sub_3F1BA0", 0x3F1BA0, &recomp_gen::fn_sub_3F1BA0_003f1ba0, &recomp_gen::fn_sub_3F1BA0_003f1ba0__recomp},
    {"sub_3F2320", 0x3F2320, &recomp_gen::fn_sub_3F2320_003f2320, &recomp_gen::fn_sub_3F2320_003f2320__recomp},
    {"sub_3F25E0", 0x3F25E0, &recomp_gen::fn_sub_3F25E0_003f25e0, &recomp_gen::fn_sub_3F25E0_003f25e0__recomp},
    {"sub_3F3E60", 0x3F3E60, &recomp_gen::fn_sub_3F3E60_003f3e60, &recomp_gen::fn_sub_3F3E60_003f3e60__recomp},
    {"sub_3F4A90", 0x3F4A90, &recomp_gen::fn_sub_3F4A90_003f4a90, &recomp_gen::fn_sub_3F4A90_003f4a90__recomp},
    {"sub_3F5AB0", 0x3F5AB0, &recomp_gen::fn_sub_3F5AB0_003f5ab0, &recomp_gen::fn_sub_3F5AB0_003f5ab0__recomp},
    {"sub_3F5D10", 0x3F5D10, &recomp_gen::fn_sub_3F5D10_003f5d10, &recomp_gen::fn_sub_3F5D10_003f5d10__recomp},
    {"sub_3F5F50", 0x3F5F50, &recomp_gen::fn_sub_3F5F50_003f5f50, &recomp_gen::fn_sub_3F5F50_003f5f50__recomp},
    {"sub_3F61D0", 0x3F61D0, &recomp_gen::fn_sub_3F61D0_003f61d0, &recomp_gen::fn_sub_3F61D0_003f61d0__recomp},
    {"sub_3F67E0", 0x3F67E0, &recomp_gen::fn_sub_3F67E0_003f67e0, &recomp_gen::fn_sub_3F67E0_003f67e0__recomp},
    {"sub_3F6F20", 0x3F6F20, &recomp_gen::fn_sub_3F6F20_003f6f20, &recomp_gen::fn_sub_3F6F20_003f6f20__recomp},
    {"sub_3F7890", 0x3F7890, &recomp_gen::fn_sub_3F7890_003f7890, &recomp_gen::fn_sub_3F7890_003f7890__recomp},
    {"sub_3F9510", 0x3F9510, &recomp_gen::fn_sub_3F9510_003f9510, &recomp_gen::fn_sub_3F9510_003f9510__recomp},
    {"sub_3FA210", 0x3FA210, &recomp_gen::fn_sub_3FA210_003fa210, &recomp_gen::fn_sub_3FA210_003fa210__recomp},
    {"sub_3FA520", 0x3FA520, &recomp_gen::fn_sub_3FA520_003fa520, &recomp_gen::fn_sub_3FA520_003fa520__recomp},
    {"sub_3FA800", 0x3FA800, &recomp_gen::fn_sub_3FA800_003fa800, &recomp_gen::fn_sub_3FA800_003fa800__recomp},
    {"sub_3FAAE0", 0x3FAAE0, &recomp_gen::fn_sub_3FAAE0_003faae0, &recomp_gen::fn_sub_3FAAE0_003faae0__recomp},
    {"sub_3FADC0", 0x3FADC0, &recomp_gen::fn_sub_3FADC0_003fadc0, &recomp_gen::fn_sub_3FADC0_003fadc0__recomp},
    {"sub_3FB0C0", 0x3FB0C0, &recomp_gen::fn_sub_3FB0C0_003fb0c0, &recomp_gen::fn_sub_3FB0C0_003fb0c0__recomp},
    {"sub_3FB2F0", 0x3FB2F0, &recomp_gen::fn_sub_3FB2F0_003fb2f0, &recomp_gen::fn_sub_3FB2F0_003fb2f0__recomp},
    {"sub_3FB530", 0x3FB530, &recomp_gen::fn_sub_3FB530_003fb530, &recomp_gen::fn_sub_3FB530_003fb530__recomp},
    {"sub_3FBF10", 0x3FBF10, &recomp_gen::fn_sub_3FBF10_003fbf10, &recomp_gen::fn_sub_3FBF10_003fbf10__recomp},
    {"sub_3FCA00", 0x3FCA00, &recomp_gen::fn_sub_3FCA00_003fca00, &recomp_gen::fn_sub_3FCA00_003fca00__recomp},
    {"sub_3FCBE0", 0x3FCBE0, &recomp_gen::fn_sub_3FCBE0_003fcbe0, &recomp_gen::fn_sub_3FCBE0_003fcbe0__recomp},
    {"sub_3FD140", 0x3FD140, &recomp_gen::fn_sub_3FD140_003fd140, &recomp_gen::fn_sub_3FD140_003fd140__recomp},
    {"sub_3FD7E0", 0x3FD7E0, &recomp_gen::fn_sub_3FD7E0_003fd7e0, &recomp_gen::fn_sub_3FD7E0_003fd7e0__recomp},
    {"sub_3FD8E0", 0x3FD8E0, &recomp_gen::fn_sub_3FD8E0_003fd8e0, &recomp_gen::fn_sub_3FD8E0_003fd8e0__recomp},
    {"sub_3FD990", 0x3FD990, &recomp_gen::fn_sub_3FD990_003fd990, &recomp_gen::fn_sub_3FD990_003fd990__recomp},
    {"sub_3FE1F0", 0x3FE1F0, &recomp_gen::fn_sub_3FE1F0_003fe1f0, &recomp_gen::fn_sub_3FE1F0_003fe1f0__recomp},
    {"sub_3FE3E0", 0x3FE3E0, &recomp_gen::fn_sub_3FE3E0_003fe3e0, &recomp_gen::fn_sub_3FE3E0_003fe3e0__recomp},
    {"sub_3FE5D0", 0x3FE5D0, &recomp_gen::fn_sub_3FE5D0_003fe5d0, &recomp_gen::fn_sub_3FE5D0_003fe5d0__recomp},
    {"sub_3FE690", 0x3FE690, &recomp_gen::fn_sub_3FE690_003fe690, &recomp_gen::fn_sub_3FE690_003fe690__recomp},
    {"sub_3FE7D0", 0x3FE7D0, &recomp_gen::fn_sub_3FE7D0_003fe7d0, &recomp_gen::fn_sub_3FE7D0_003fe7d0__recomp},
    {"sub_3FE850", 0x3FE850, &recomp_gen::fn_sub_3FE850_003fe850, &recomp_gen::fn_sub_3FE850_003fe850__recomp},
    {"sub_3FE950", 0x3FE950, &recomp_gen::fn_sub_3FE950_003fe950, &recomp_gen::fn_sub_3FE950_003fe950__recomp},
    {"sub_3FEA10", 0x3FEA10, &recomp_gen::fn_sub_3FEA10_003fea10, &recomp_gen::fn_sub_3FEA10_003fea10__recomp},
    {"sub_3FEB30", 0x3FEB30, &recomp_gen::fn_sub_3FEB30_003feb30, &recomp_gen::fn_sub_3FEB30_003feb30__recomp},
    {"sub_3FEE40", 0x3FEE40, &recomp_gen::fn_sub_3FEE40_003fee40, &recomp_gen::fn_sub_3FEE40_003fee40__recomp},
    {"sub_3FEF30", 0x3FEF30, &recomp_gen::fn_sub_3FEF30_003fef30, &recomp_gen::fn_sub_3FEF30_003fef30__recomp},
    {"sub_3FF150", 0x3FF150, &recomp_gen::fn_sub_3FF150_003ff150, &recomp_gen::fn_sub_3FF150_003ff150__recomp},
    {"sub_3FF460", 0x3FF460, &recomp_gen::fn_sub_3FF460_003ff460, &recomp_gen::fn_sub_3FF460_003ff460__recomp},
    {"sub_3FF570", 0x3FF570, &recomp_gen::fn_sub_3FF570_003ff570, &recomp_gen::fn_sub_3FF570_003ff570__recomp},
    {"sub_4003A0", 0x4003A0, &recomp_gen::fn_sub_4003A0_004003a0, &recomp_gen::fn_sub_4003A0_004003a0__recomp},
    {"sub_4006C0", 0x4006C0, &recomp_gen::fn_sub_4006C0_004006c0, &recomp_gen::fn_sub_4006C0_004006c0__recomp},
    {"sub_4008F0", 0x4008F0, &recomp_gen::fn_sub_4008F0_004008f0, &recomp_gen::fn_sub_4008F0_004008f0__recomp},
    {"sub_400E30", 0x400E30, &recomp_gen::fn_sub_400E30_00400e30, &recomp_gen::fn_sub_400E30_00400e30__recomp},
    {"sub_4016D0", 0x4016D0, &recomp_gen::fn_sub_4016D0_004016d0, &recomp_gen::fn_sub_4016D0_004016d0__recomp},
    {"sub_401800", 0x401800, &recomp_gen::fn_sub_401800_00401800, &recomp_gen::fn_sub_401800_00401800__recomp},
    {"sub_401A00", 0x401A00, &recomp_gen::fn_sub_401A00_00401a00, &recomp_gen::fn_sub_401A00_00401a00__recomp},
    {"sub_401C90", 0x401C90, &recomp_gen::fn_sub_401C90_00401c90, &recomp_gen::fn_sub_401C90_00401c90__recomp},
    {"sub_401CF0", 0x401CF0, &recomp_gen::fn_sub_401CF0_00401cf0, &recomp_gen::fn_sub_401CF0_00401cf0__recomp},
    {"sub_401D90", 0x401D90, &recomp_gen::fn_sub_401D90_00401d90, &recomp_gen::fn_sub_401D90_00401d90__recomp},
    {"sub_401DE0", 0x401DE0, &recomp_gen::fn_sub_401DE0_00401de0, &recomp_gen::fn_sub_401DE0_00401de0__recomp},
    {"sub_402400", 0x402400, &recomp_gen::fn_sub_402400_00402400, &recomp_gen::fn_sub_402400_00402400__recomp},
    {"sub_402510", 0x402510, &recomp_gen::fn_sub_402510_00402510, &recomp_gen::fn_sub_402510_00402510__recomp},
    {"sub_4032F0", 0x4032F0, &recomp_gen::fn_sub_4032F0_004032f0, &recomp_gen::fn_sub_4032F0_004032f0__recomp},
    {"sub_403340", 0x403340, &recomp_gen::fn_sub_403340_00403340, &recomp_gen::fn_sub_403340_00403340__recomp},
    {"sub_403410", 0x403410, &recomp_gen::fn_sub_403410_00403410, &recomp_gen::fn_sub_403410_00403410__recomp},
    {"sub_403760", 0x403760, &recomp_gen::fn_sub_403760_00403760, &recomp_gen::fn_sub_403760_00403760__recomp},
    {"sub_403780", 0x403780, &recomp_gen::fn_sub_403780_00403780, &recomp_gen::fn_sub_403780_00403780__recomp},
    {"sub_4037A0", 0x4037A0, &recomp_gen::fn_sub_4037A0_004037a0, &recomp_gen::fn_sub_4037A0_004037a0__recomp},
    {"sub_4037C0", 0x4037C0, &recomp_gen::fn_sub_4037C0_004037c0, &recomp_gen::fn_sub_4037C0_004037c0__recomp},
    {"sub_4037E0", 0x4037E0, &recomp_gen::fn_sub_4037E0_004037e0, &recomp_gen::fn_sub_4037E0_004037e0__recomp},
    {"sub_403860", 0x403860, &recomp_gen::fn_sub_403860_00403860, &recomp_gen::fn_sub_403860_00403860__recomp},
    {"sub_4038E0", 0x4038E0, &recomp_gen::fn_sub_4038E0_004038e0, &recomp_gen::fn_sub_4038E0_004038e0__recomp},
    {"sub_404470", 0x404470, &recomp_gen::fn_sub_404470_00404470, &recomp_gen::fn_sub_404470_00404470__recomp},
    {"sub_404750", 0x404750, &recomp_gen::fn_sub_404750_00404750, &recomp_gen::fn_sub_404750_00404750__recomp},
    {"sub_405A90", 0x405A90, &recomp_gen::fn_sub_405A90_00405a90, &recomp_gen::fn_sub_405A90_00405a90__recomp},
    {"sub_405D60", 0x405D60, &recomp_gen::fn_sub_405D60_00405d60, &recomp_gen::fn_sub_405D60_00405d60__recomp},
    {"sub_405DB0", 0x405DB0, &recomp_gen::fn_sub_405DB0_00405db0, &recomp_gen::fn_sub_405DB0_00405db0__recomp},
    {"sub_405E00", 0x405E00, &recomp_gen::fn_sub_405E00_00405e00, &recomp_gen::fn_sub_405E00_00405e00__recomp},
    {"sub_405E30", 0x405E30, &recomp_gen::fn_sub_405E30_00405e30, &recomp_gen::fn_sub_405E30_00405e30__recomp},
    {"sub_406AA0", 0x406AA0, &recomp_gen::fn_sub_406AA0_00406aa0, &recomp_gen::fn_sub_406AA0_00406aa0__recomp},
    {"sub_407180", 0x407180, &recomp_gen::fn_sub_407180_00407180, &recomp_gen::fn_sub_407180_00407180__recomp},
    {"sub_407210", 0x407210, &recomp_gen::fn_sub_407210_00407210, &recomp_gen::fn_sub_407210_00407210__recomp},
    {"sub_409C80", 0x409C80, &recomp_gen::fn_sub_409C80_00409c80, &recomp_gen::fn_sub_409C80_00409c80__recomp},
    {"sub_409E90", 0x409E90, &recomp_gen::fn_sub_409E90_00409e90, &recomp_gen::fn_sub_409E90_00409e90__recomp},
    {"sub_409F20", 0x409F20, &recomp_gen::fn_sub_409F20_00409f20, &recomp_gen::fn_sub_409F20_00409f20__recomp},
    {"sub_40A200", 0x40A200, &recomp_gen::fn_sub_40A200_0040a200, &recomp_gen::fn_sub_40A200_0040a200__recomp},
    {"sub_40A260", 0x40A260, &recomp_gen::fn_sub_40A260_0040a260, &recomp_gen::fn_sub_40A260_0040a260__recomp},
    {"sub_40A5B0", 0x40A5B0, &recomp_gen::fn_sub_40A5B0_0040a5b0, &recomp_gen::fn_sub_40A5B0_0040a5b0__recomp},
    {"sub_40A640", 0x40A640, &recomp_gen::fn_sub_40A640_0040a640, &recomp_gen::fn_sub_40A640_0040a640__recomp},
    {"sub_40A6D0", 0x40A6D0, &recomp_gen::fn_sub_40A6D0_0040a6d0, &recomp_gen::fn_sub_40A6D0_0040a6d0__recomp},
    {"sub_40A7C0", 0x40A7C0, &recomp_gen::fn_sub_40A7C0_0040a7c0, &recomp_gen::fn_sub_40A7C0_0040a7c0__recomp},
    {"sub_40B630", 0x40B630, &recomp_gen::fn_sub_40B630_0040b630, &recomp_gen::fn_sub_40B630_0040b630__recomp},
    {"sub_40B780", 0x40B780, &recomp_gen::fn_sub_40B780_0040b780, &recomp_gen::fn_sub_40B780_0040b780__recomp},
    {"sub_40C150", 0x40C150, &recomp_gen::fn_sub_40C150_0040c150, &recomp_gen::fn_sub_40C150_0040c150__recomp},
    {"sub_40C1E0", 0x40C1E0, &recomp_gen::fn_sub_40C1E0_0040c1e0, &recomp_gen::fn_sub_40C1E0_0040c1e0__recomp},
    {"sub_40C460", 0x40C460, &recomp_gen::fn_sub_40C460_0040c460, &recomp_gen::fn_sub_40C460_0040c460__recomp},
    {"sub_40C520", 0x40C520, &recomp_gen::fn_sub_40C520_0040c520, &recomp_gen::fn_sub_40C520_0040c520__recomp},
    {"sub_40C5B0", 0x40C5B0, &recomp_gen::fn_sub_40C5B0_0040c5b0, &recomp_gen::fn_sub_40C5B0_0040c5b0__recomp},
    {"sub_40C650", 0x40C650, &recomp_gen::fn_sub_40C650_0040c650, &recomp_gen::fn_sub_40C650_0040c650__recomp},
    {"sub_40C6A0", 0x40C6A0, &recomp_gen::fn_sub_40C6A0_0040c6a0, &recomp_gen::fn_sub_40C6A0_0040c6a0__recomp},
    {"sub_40CA00", 0x40CA00, &recomp_gen::fn_sub_40CA00_0040ca00, &recomp_gen::fn_sub_40CA00_0040ca00__recomp},
    {"sub_40D330", 0x40D330, &recomp_gen::fn_sub_40D330_0040d330, &recomp_gen::fn_sub_40D330_0040d330__recomp},
};

constexpr u32 kWorld = 0x01810000u;  // the random worlds: 64 KiB of free RAM above the harness's arena
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 16;
constexpr u32 kOut = 0x01F40000u;    // free in every snapshot (above the stand-in heap) and in the ELF image
constexpr u32 kYen = 0x83A6DCu;      // the yen counter (datGetMoney sub_16DD50 reads it)
constexpr u32 kFlagWords = 0x83A21Cu;  // datGetFlag / datSetFlag bit array
constexpr u32 kPadA = 0x7E0952u, kPadB = 0x7E095Au;  // the pad words the selectors read
constexpr u32 kPersonaTablePtr = 0x7CE420u;  // PERSONA.TBL section 0 (14-byte records)

// --- the pair runner of this file (as test_fcl.cpp) ---------------------------------------------------------------
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    bool persist = false;
    WorldSetup setup;
};
Tramp g_t;
int g_pairs = 0;
std::map<std::string, int> g_stops;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    if (!g_t.persist || !g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        install_standard(*g_t.world[K]);
        if (g_t.setup) g_t.setup(*g_t.world[K]);
    }
    g_t.world[K]->si.log.clear();
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// Recorders for the callees deeper in the hand-written code that this test library does not emit (functions other
// slices' tests stand in: the shop band's sub_3F04F0, ui4's sprite handles), so the pairs run past them.
void recorders(StandInWorld& w) {
    w.si.install_recorder(0x3F04F0u, "sub_3F04F0", 0);
    w.si.install_recorder(0x1158B0u, "sprCreateHandle (-> kOut + 0x3000)", 0x01F43000u);
    w.si.install_recorder(0x115980u, "sub_115980", 0);
    w.si.install_recorder(0x1124B0u, "sub_1124B0", 0);
    w.si.install_recorder(0x1052B0u, "sub_1052B0 (debug log)", 0);
    // callbacks the lists call through jalr and helpers of the hand-written shop code, all kept recompiled
    for (const u32 va : {0x3F33D0u, 0x3F55B0u, 0x3F5830u, 0x3F4DE0u, 0x406CA0u, 0x3FF630u, 0x40A7F0u, 0x40B3A0u, 0x51E028u, 0x51DF58u})
        w.si.install_recorder(va, "callback", 0);
}
struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    bool standins = true;
    bool persist = false;
    WorldSetup setup = recorders;
};
const Opt kKeep{{}, true, true, recorders};

hgp::Run run_fns(Machine& m, Fn hand, Fn recomp, const char* name, const Args& a, u32 seed, const char* what, const Opt& o) {
    g_t.fn[0] = hand;
    g_t.fn[1] = recomp;
    g_t.standins = o.standins;
    if (!o.persist) {
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    g_t.persist = o.persist;
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s (%s) seed %u\n", name, what, seed);
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    if (r.stopped) ++g_stops[std::string(name) + " @ " + hex64(r.stop_pc) + " (" + r.what.substr(0, 60) + ")"];
    ++g_pairs;
    return r;
}
// A pair of the slice function `name` (hand body vs its recompiled body).
hgp::Run f2pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    return run_fns(m, c.hand, c.recomp, name, a, seed, what, o);
}
// A set-up call (a hand-written callee) run in both persisted worlds from the same machine: the two worlds' heaps stay
// identical, and the pair checks the two runs agree.
hgp::Run setup(Machine& m, Fn fn, const char* name, const Args& a, u32 seed) {
    return run_fns(m, fn, fn, name, a, seed, name, kKeep);
}
void fresh_worlds() {
    g_t.world[0].reset();
    g_t.world[1].reset();
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u32 v0u(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }

// A read-only callee run once (an oracle of a documented rule): returns $v0.
u64 oracle(Machine& m, Fn fn, const Args& a) {
    const hgp::Run r = hgp::run_one(m, fn, a, 77, {});
    REQUIRE(!r.stopped);
    return r.end.gpr[GPR_V0].u64[0];
}

// --- guest memory helpers -------------------------------------------------------------------------------------------
u32 ram_off(u32 va, u32 n) {
    const u32 a = va & 0x01FFFFFFu;
    return a + n <= EEMemory::kMainRamSize ? a : 0;
}
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
s16 r16(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 2), 2);
    return v;
}
u16 ru16(const Machine& m, u32 va) { return static_cast<u16>(r16(m, va)); }
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[ram_off(va, 1)]; }
float rf(const Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
bool flag(const Machine& m, u32 id) { return (r32(m, kFlagWords + 4 * (id / 32)) >> (id % 32)) & 1u; }
void set_flag(Machine& m, u32 id, bool on) {
    u32 w = r32(m, kFlagWords + 4 * (id / 32));
    w = on ? (w | (1u << (id % 32))) : (w & ~(1u << (id % 32)));
    w32(m, kFlagWords + 4 * (id / 32), w);
}

// --- snapshots ----------------------------------------------------------------------------------------------------
const std::vector<u8>& snapshot(const char* dir) {
    static std::map<std::string, std::vector<u8>> cache;
    auto it = cache.find(dir);
    if (it == cache.end()) it = cache.emplace(dir, read_snapshot(dir)).first;
    return it->second;
}
bool restore(Machine& m, const char* dir) {
    const std::vector<u8>& s = snapshot(dir);
    if (s.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), s.data(), s.size());
    return true;
}
std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}
// The machine on a snapshot, or the ELF image (with a note) when the snapshot is absent.
std::unique_ptr<Machine> snap_machine(const char* dir, bool& have) {
    auto m = elf_machine();
    if (!m) return nullptr;
    have = restore(*m, dir);
    if (!have) MESSAGE("note: extracted/_ours/" << dir << " not found; the ELF image instead");
    return m;
}

// Command lists made in both worlds (nmCmdListCreate) and rows added to them (nmCmdListAddRow).
u32 make_list(Machine& m, u32 size, u32 rows, u32 spacing, u32& seed) {
    return v0u(setup(m, &recomp_gen::fn_sub_3C58F0_003c58f0, "nmCmdListCreate", {0, size, rows, spacing}, ++seed));
}
u32 add_row(Machine& m, u32 list, u32 user_size, u32& seed) {
    const u32 key = ru16(m, list + f2::lst::kCount) + 1u;
    return v0u(setup(m, &recomp_gen::fn_nmCmdListAddRow_003c5a40, "nmCmdListAddRow", {sx(list), key, user_size, 0}, ++seed));
}
u32 row_user(const Machine& m, u32 node) { return r32(m, r32(m, node + f2::node::kPayload) + f2::row::kUser); }
std::vector<u32> rows_of(const Machine& m, u32 list) {
    std::vector<u32> v;
    for (u32 n = r32(m, list + f2::lst::kHead); n && v.size() < 512; n = r32(m, n + f2::node::kNext)) v.push_back(n);
    return v;
}
u32 win_user(const Machine& m, u32 list) { return r32(m, r32(m, list + f2::lst::kState) + f2::win::kUser); }

// --- host models of the ELF's tables ---------------------------------------------------------------------------------
struct Persona {
    u16 id = 0;
    u8 level = 0;
};
u8 arcana_of(const Machine& m, u16 id) { return r8(m, r32(m, kPersonaTablePtr) + 14u * id + 2u); }

// sub_4016D0's best-stat mask from the five stats (the documented quirk: only St / Ma ties are kept).
u32 best_mask(const std::array<s64, 5>& s) {
    s64 best = s[0];
    u32 mask = 1;
    if (s[1] >= best) {
        mask = s[1] == best ? 3u : 2u;
        best = s[1];
    }
    for (int k = 2; k < 5; ++k)
        if (best < s[k]) {
            mask = 1u << k;
            best = s[k];
        }
    return mask;
}
}  // namespace

namespace p3fes::recomp_gen {
void fn_sub_3F03E0_003f03e0(EEContext&);   // shops: the progress count of a kind (sub_3F03E0(4) bounds the extra trade tables)
void fn_sub_171360_00171360(EEContext&);   // [datIsKeyItem]
void fn_sub_170760_00170760(EEContext&);   // [datGetItemNum](owner, id)
void fn_sub_16F630_0016f630(EEContext&);   // [datGetEquipmentItemId](owner, slot)
}  // namespace p3fes::recomp_gen

namespace {
constexpr u32 kDaysSinceApr5 = 0x83679Cu;   // s16 (calendar.h)
constexpr u32 kQuestTable = 0x6AD4C0u;      // *(0x7CD8F0): 100 x 64 bytes
constexpr u32 kTradeTables = 0x6AD4A0u;     // {entries, count} trades, +8 trade-ins, +16 {extra tables, count}

// The item record and kind of sub_170ED0 (oracle; the kind word goes to kOut + 0xFF0).
std::pair<u32, s32> item_record(Machine& m, u32 item) {
    w32(m, kOut + 0xFF0, 0xFFFFFFFFu);
    const u32 rec = static_cast<u32>(oracle(m, &recomp_gen::fn_sub_170ED0_00170ed0, {sx(static_cast<u32>(static_cast<s16>(item))), sx(kOut + 0xFF0), 0, 0}));
    return {rec, static_cast<s32>(r32(m, kOut + 0xFF0))};
}
// How many of `item` the party holds (sub_3F1910's rule, from the oracles of its callees).
s32 owned_model(Machine& m, u32 item) {
    const auto [rec, kind] = item_record(m, item);
    if (kind == 4) return static_cast<s32>(static_cast<u16>(oracle(m, &recomp_gen::fn_sub_170760_00170760, {1, sx(static_cast<u32>(static_cast<s16>(item))), 0, 0})));
    if (kind < 0 || kind > 3) return 0;
    s32 n = 0;
    for (u32 slot = 0; slot < 300; ++slot)
        if (static_cast<u16>(oracle(m, &recomp_gen::fn_sub_16F630_0016f630, {1, slot, 0, 0})) == static_cast<u16>(item)) ++n;
    return n;
}
// The item entry's price (sub_3F1BA0's rule).
s32 price_model(Machine& m, u32 item) {
    if (oracle(m, &recomp_gen::fn_sub_171360_00171360, {item & 0xFFFFu, 0, 0, 0}) != 0) return 0;
    const auto [rec, kind] = item_record(m, item);
    switch (kind) {
    case 4: return static_cast<s32>(r32(m, rec + 12));
    case 3: case 2: case 1: return static_cast<s32>(r32(m, rec + 16));
    case 0: return static_cast<s32>(r32(m, rec + 24));
    default: return 0;
    }
}
}  // namespace

// =====================================================================================================================
// 1. Every body on random worlds (the p3fes_handgen skeleton; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(facility2): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int stops = 0, pairs = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// 2. The quantity selector (documented rule)
// =====================================================================================================================
TEST_CASE("game(facility2): the quantity selector of BUY / SELL (documented rule)") {
    bool have = false;
    auto mp = snap_machine("shop_ref_4100", have);
    if (!mp) return;
    Machine& m = *mp;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    const u32 q = kOut;
    u32 seed = 2000;
    int checked = 0;
    struct Key {
        u16 a, b;
        s32 step;
    };
    const Key keys[] = {{0, 0, 0}, {0x1000, 0, 1}, {0, 0x1000, 1}, {0x4000, 0, -1}, {0x2000, 0, 10}, {0, 0x2000, 10},
                        {0x8000, 0, -10}, {0x1000, 0x4000, 1}, {0x4000, 0x2000, -1}};
    std::mt19937 rng{12};
    for (int trial = 0; trial < 60; ++trial) {
        const u32 price = trial % 7 == 0 ? 0u : 1u + rng() % 20000u;
        const u32 yen = trial % 5 == 0 ? 0u : rng() % 3000000u;
        const s16 owned = static_cast<s16>(rng() % 100);
        const u16 item = static_cast<u16>(1 + rng() % 0x600);
        for (const int selling : {0, 1}) {
            reset();
            zero(m, q, 64);
            w32(m, kYen, yen);
            w16(m, q + f2::qsel::kItemId, item);
            w16(m, q + f2::qsel::kLimit, static_cast<u16>(owned));
            w32(m, q + f2::qsel::kPrice, price);
            // the maximum, from the rule (the stock through the oracles of sub_3E6DC0 / sub_17D250)
            s32 max = 99;
            if (!selling) {
                if (price) max = static_cast<s32>(yen / price);
                if (max + owned >= 100) max = 99 - owned;
                const u32 key = static_cast<u16>(oracle(m, &recomp_gen::fn_sub_3E6DC0_003e6dc0, {0, 0, 0, 0}));
                const s64 stock = static_cast<s64>(oracle(m, &recomp_gen::fn_sub_17D250_0017d250, {key, item, 0, 0}));
                if (stock != -1 && stock < max) max = static_cast<s32>(stock);
            } else {
                max = owned;
            }
            f2pair(m, "sub_3FB0C0", {sx(q), static_cast<u64>(selling), 0, 0}, ++seed, "qty open");
            u32 fl = r32(m, q + f2::qsel::kFlags);
            CHECK(r32(m, q + f2::qsel::kCount) == 1u);
            CHECK((fl & 1u) != 0u);
            CHECK((fl & 6u) == (selling ? 4u : 2u));
            CHECK(((fl & 8u) != 0u) == !(1 < max));
            CHECK((fl & 0x10u) != 0u);
            ++checked;
            s32 count = 1;
            for (int k = 0; k < 14; ++k) {
                const Key& key = keys[(trial + k * 3) % std::size(keys)];
                w16(m, kPadA, key.a);
                w16(m, kPadB, key.b);
                s32 n = count + key.step;
                u32 want_ret = 0, want_flags = r32(m, q + f2::qsel::kFlags);
                if (key.step != 0) {
                    if (!selling) {
                        n = n >= 100 ? 99 : (n <= 0 ? 1 : n);
                        if (n < max) want_flags &= ~8u;
                        else {
                            want_flags |= 8u;
                            n = max;
                        }
                    } else {
                        n = n > max ? max : (n <= 0 ? 1 : n);
                        want_flags = n < max ? (want_flags & ~8u) : (want_flags | 8u);
                    }
                    want_flags = n == 1 ? (want_flags | 0x10u) : (want_flags & ~0x10u);
                    if (n != count) want_ret = key.step > 0 ? 1u : 2u;
                } else {
                    n = count;
                }
                const hgp::Run r = f2pair(m, selling ? "sub_3FB530" : "sub_3FB2F0", {sx(q), 0, 0, 0}, ++seed, "qty step");
                CHECK(v0u(r) == want_ret);
                CHECK(static_cast<s32>(r32(m, q + f2::qsel::kCount)) == n);
                CHECK(r32(m, q + f2::qsel::kFlags) == want_flags);
                count = n;
                ++checked;
            }
        }
    }
    MESSAGE("quantity selector: " << checked << " checked steps, " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 3. Weapon fusion: best stats, the fusion flags, the bands, the recipe search and the order (documented rules)
// =====================================================================================================================
TEST_CASE("game(facility2): weapon-fusion recipes and orders (documented rules)") {
    bool have = false;
    auto mp = snap_machine("fusion_vr_5000", have);
    if (!mp) return;
    Machine& m = *mp;
    if (!have) return;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    u32 seed = 3000;
    // the item flag table: 24 halfwords of 0x6AF3A0 -> 4736 + i
    for (u32 item = 0; item < 0x140; ++item) {
        u32 want = 0;
        for (u32 i = 0; i < 24; ++i)
            if (ru16(m, 0x6AF3A0u + 2 * i) == item) {
                want = 4736 + i;
                break;
            }
        CHECK(v0u(f2pair(m, "sub_401800", {item, 0, 0, 0}, ++seed, "fusion flag", {{}, false})) == want);
    }
    // personas: the stock's, then 120 made-up records (52 bytes: +2 id, +4 level, +28 the five base stats)
    std::vector<u32> personas;
    const u32 stock = static_cast<u16>(oracle(m, &recomp_gen::fn_sub_175410_00175410, {0, 0, 0, 0}));
    for (u32 i = 0; i < stock; ++i)
        if (const u32 p = static_cast<u32>(oracle(m, &recomp_gen::fn_sub_174A90_00174a90, {i, 0, 0, 0}))) personas.push_back(p);
    std::mt19937 rng{33};
    const u32 made = kOut + 0x4000;
    for (u32 k = 0; k < 120; ++k) {
        const u32 p = made + 64 * k;
        personas.push_back(p);
    }
    auto make_personas = [&] {
        std::mt19937 r2{34};
        for (u32 k = 0; k < 120; ++k) {
            const u32 p = made + 64 * k;
            zero(m, p, 64);
            w16(m, p + 0, 1);
            w16(m, p + f2::persona::kId, static_cast<u16>(1 + r2() % 200));
            w8(m, p + f2::persona::kLevel, static_cast<u8>(1 + r2() % 99));
            for (u32 s = 0; s < 5; ++s) w8(m, p + 28 + s, static_cast<u8>(k % 9 == 0 ? 20 : 1 + r2() % 60));  // some all-equal
        }
    };
    make_personas();
    const std::vector<u8> base2(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset2 = [&] { std::memcpy(m.mem.main_ram(), base2.data(), base2.size()); };
    const u32 fixed = r32(m, 0x7CD8E8u), nfixed = r32(m, 0x7CD8ECu);
    const u32 groups = r32(m, 0x7CD8C0u), ngroups = r32(m, 0x7CD8C4u);
    const u32 recipes = r32(m, 0x7CD8D0u), nrecipes = r32(m, 0x7CD8D4u);
    std::vector<u32> base_items;
    for (u32 i = 0; i < 8; ++i) base_items.push_back(ru16(m, 0x6AF180u + 2 * i));
    for (u32 i = 0; i < ngroups && i < 6; ++i) base_items.push_back(ru16(m, groups + 4 * i));
    int fixed_hits = 0, recipe_hits = 0, none = 0;
    for (const u32 p : personas) {
        reset2();
        std::array<s64, 5> st{};
        for (u32 s = 0; s < 5; ++s) st[s] = static_cast<s64>(oracle(m, &recomp_gen::fn_sub_173A00_00173a00, {sx(p), s, 0, 0}));
        const u32 mask = best_mask(st);
        CHECK(v0u(f2pair(m, "sub_4016D0", {sx(p), 0, 0, 0}, ++seed, "best stats", {{}, false})) == mask);
        // the level bands
        f2pair(m, "sub_401CF0", {sx(p), 0, 0, 0}, ++seed, "arcana band", {{}, false});
        f2pair(m, "sub_401D90", {sx(p), 0, 0, 0}, ++seed, "fool entry", {{}, false});
        const u16 id = ru16(m, p + f2::persona::kId);
        const u8 level = r8(m, p + f2::persona::kLevel);
        for (const u32 item : base_items) {
            // host model of sub_401A00
            u32 want_item = 0, want_ret = 0;
            for (u32 i = 0; i < nfixed; ++i)
                if (ru16(m, fixed + 4 * i) == id) {
                    want_item = ru16(m, fixed + 4 * i + 2);
                    break;
                }
            if (want_item) want_ret = 2;
            u32 rec_used = 0;
            if (!want_ret) {
                s32 group = -1;
                for (u32 i = 0; i < 8; ++i)
                    if (ru16(m, 0x6AF180u + 2 * i) == item) group = static_cast<s32>(item);
                if (group < 0) {
                    group = 0;
                    for (u32 i = 0; i < ngroups; ++i)
                        if (static_cast<s32>(r16(m, groups + 4 * i)) == static_cast<s32>(item)) {
                            group = static_cast<s16>(ru16(m, groups + 4 * i + 2));
                            break;
                        }
                }
                for (u32 i = 0; i < nrecipes; ++i) {
                    const u32 rc = recipes + 16 * i;
                    if (static_cast<s32>(ru16(m, rc + f2::recipe::kGroup)) == group && (r32(m, rc + f2::recipe::kMask) & mask)) {
                        want_item = ru16(m, rc + f2::recipe::kItem);
                        want_ret = 1;
                        rec_used = rc;
                        break;
                    }
                }
            }
            const hgp::Run r = f2pair(m, "sub_401A00", {item, sx(p), sx(kOut), 0}, ++seed, "fusion result", {{}, false});
            CHECK(v0u(r) == want_ret);
            CHECK(ru16(m, kOut) == static_cast<u16>(want_item));
            (want_ret == 2 ? fixed_hits : want_ret == 1 ? recipe_hits : none)++;
            if (want_ret == 1) f2pair(m, "sub_401C90", {sx(rec_used + f2::recipe::kBands), sx(p), 0, 0}, ++seed, "recipe band", {{}, false});
            // the order (the item entry a1: +0 the base item)
            const u32 order = kOut + 0x100, entry = kOut + 0x140;
            zero(m, entry, 28);
            w16(m, entry, static_cast<u16>(item));
            const hgp::Run o = f2pair(m, "sub_401DE0", {sx(order), sx(entry), sx(p), 0}, ++seed, "fusion order");
            if (o.stopped) continue;
            if (!want_ret) {
                CHECK(v0u(o) == 0u);
                continue;
            }
            CHECK(v0u(o) == 1u);
            const u16 fl = ru16(m, order + f2::order::kFlags);
            CHECK((fl & 1u) != 0u);
            CHECK(((fl & 2u) != 0u) == (want_ret == 2));
            const s16 today = static_cast<s16>(oracle(m, &recomp_gen::fn_datGetDaysSinceApr5_0016ef20, {0, 0, 0, 0}));
            const s16 day = static_cast<s16>(today + (want_ret == 2 ? 2 : 1));
            CHECK(r8(m, order + f2::order::kMonth) == static_cast<u8>(oracle(m, &recomp_gen::fn_clndGetMonthFromDaysSinceApr5_0017d830, {sx(static_cast<u32>(day)), 0, 0, 0})));
            CHECK(r8(m, order + f2::order::kDay) == static_cast<u8>(oracle(m, &recomp_gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0, {sx(static_cast<u32>(day)), 0, 0, 0})));
            if (want_ret == 1) {
                CHECK(ru16(m, order + f2::order::kItem) == static_cast<u16>(want_item));
                // +24: the record value while the item's fusion flag is unset, else level / 5 + 1
                u32 fflag = 0;
                for (u32 i = 0; i < 24; ++i)
                    if (ru16(m, 0x6AF3A0u + 2 * i) == want_item) fflag = 4736 + i;
                if (!(fflag && !flag(m, fflag))) CHECK(r32(m, order + f2::order::kValue) == static_cast<u32>(level / 5 + 1));
                // the shop item entry of the order
                const u32 out = kOut + 0x180;
                f2pair(m, "sub_402400", {sx(order), sx(out), 0, 0}, ++seed, "order item");
                CHECK(ru16(m, out + f2::item::kId) == ru16(m, order + f2::order::kItem));
                CHECK(ru16(m, out + f2::item::kCount) == 1u);
                CHECK(r32(m, out + f2::item::kPrice) == 1u);
                CHECK(ru16(m, out + f2::item::kStatA) == ru16(m, order + f2::order::kStatA));
                CHECK(ru16(m, out + f2::item::kStatB) == ru16(m, order + f2::order::kStatB));
            }
        }
    }
    reset();
    MESSAGE("weapon fusion: " << personas.size() << " personas x " << base_items.size() << " base items: fixed " << fixed_hits
                              << ", recipes " << recipe_hits << ", none " << none << "; " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 4. Elizabeth's requests: accessors, deadlines, accept / cancel, the request list
// =====================================================================================================================
TEST_CASE("game(facility2): Elizabeth's requests (documented rules)") {
    bool have = false;
    auto mp = snap_machine("shop_ref_4100", have);
    if (!mp) return;
    Machine& m = *mp;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    u32 seed = 4000;
    REQUIRE(r32(m, f2::quest::kTableSlot) == kQuestTable);
    const Opt plain{{}, false};
    for (u32 id = 0; id < 100; ++id) {
        const u32 q = kQuestTable + 64 * id;
        CHECK(v0s(f2pair(m, "sub_403760", {id, 0, 0, 0}, ++seed, "q48", plain)) == r16(m, q + f2::quest::kHalf48));
        CHECK(v0s(f2pair(m, "sub_403780", {id, 0, 0, 0}, ++seed, "q50", plain)) == r16(m, q + f2::quest::kHalf50));
        CHECK(v0s(f2pair(m, "sub_4037A0", {id, 0, 0, 0}, ++seed, "q54", plain)) == r16(m, q + f2::quest::kHalf54));
        CHECK(v0s(f2pair(m, "sub_4037C0", {id, 0, 0, 0}, ++seed, "q52", plain)) == r16(m, q + f2::quest::kHalf52));
        CHECK(v0u(f2pair(m, "sub_4037E0", {id, 0, 0, 0}, ++seed, "qcond", plain)) == q + f2::quest::kCond);
        CHECK(v0u(f2pair(m, "sub_403860", {id, 0, 0, 0}, ++seed, "q16", plain)) == q + f2::quest::kText16);
        CHECK(v0u(f2pair(m, "sub_4038E0", {id, 0, 0, 0}, ++seed, "q44", plain)) == r32(m, q + f2::quest::kWord44));
    }
    // the deadline of every request on three days (2 today, 1 before, 0 after, 3 none)
    int states[4] = {};
    for (const s16 today : {static_cast<s16>(r16(m, kDaysSinceApr5)), s16{20}, s16{250}}) {
        reset();
        w16(m, kDaysSinceApr5, static_cast<u16>(today));
        for (u32 id = 0; id < 100; ++id) {
            const u32 c = kQuestTable + 64 * id + f2::quest::kCond;
            const s64 kind = static_cast<s64>(static_cast<s8>(r8(m, c + f2::qcond::kKind))) >> 4;
            const hgp::Run r = f2pair(m, "sub_403410", {id, 0, 0, 0}, ++seed, "deadline", plain);
            if (kind < 0 || kind > 2) continue;  // other kinds compare the caller's registers (not modelled)
            if (kind == 0) {
                CHECK(v0u(r) == 3u);
                ++states[3];
                continue;
            }
            const s64 now = static_cast<s16>(oracle(m, &recomp_gen::fn_datGetDaysSinceApr5_0016ef20, {0, 0, 0, 0}));
            const u32 dw = static_cast<u32>(static_cast<s64>(r16(m, kind == 2 ? c + f2::qcond::kDateA : c + f2::qcond::kDateB)));
            const u64 month = static_cast<u64>(static_cast<s64>(static_cast<s16>(dw)) << 52 >> 58);
            const u64 day = static_cast<u64>(static_cast<s64>(static_cast<s8>(dw)) << 58 >> 58);
            s64 due = static_cast<s32>(oracle(m, &recomp_gen::fn_clndGetDaysSinceStartFromDate_0017d8b0, {month, day, 0, 0}));
            if (kind == 2) due = (static_cast<s32>(static_cast<u32>(static_cast<s32>(r16(m, c + f2::qcond::kDateB))) << 20) >> 20) + static_cast<s32>(due);
            const u32 want = now == due ? 2u : (now < due ? 1u : 0u);
            CHECK(v0u(r) == want);
            ++states[want];
        }
    }
    // accept / cancel: the request's flag (+20, 0xFFFF none)
    for (u32 id = 0; id < 100; id += 7) {
        reset();
        const u16 f = ru16(m, kQuestTable + 64 * id + f2::quest::kFlag);
        f2pair(m, "sub_404470", {id, 1, 0, 0}, ++seed, "quest flag on");
        if (f != 0xFFFFu) CHECK(flag(m, f));
        f2pair(m, "sub_404470", {id, 0, 0, 0}, ++seed, "quest flag off");
        if (f != 0xFFFFu) CHECK(!flag(m, f));
        f2pair(m, "sub_4032F0", {id, 0, 0, 0}, ++seed, "accept");
        if (f != 0xFFFFu) CHECK(flag(m, f));
        f2pair(m, "sub_403340", {id, 0, 0, 0}, ++seed, "cancel");
        if (f != 0xFFFFu) CHECK(!flag(m, f));
    }
    // the request list: rows (user +4 the request id, +8 an element set), sorted by +58, updated, animated, drawn, freed
    reset();
    fresh_worlds();
    const u32 list = make_list(m, 88, 6, 26, seed);
    REQUIRE(list >= kStandInHeap);
    const u32 wu = win_user(m, list);
    w32(m, wu + f2::menu::kElems, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
    for (u32 k = 0; k < 9; ++k) {
        const u32 node = add_row(m, list, 16, seed);
        const u32 u = row_user(m, node);
        w32(m, u + 4, (k * 37) % 100);
        w32(m, u + 8, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
    }
    f2pair(m, "sub_405E00", {sx(list), 0, 0, 0}, ++seed, "sort requests", kKeep);
    {
        s32 prev = -0x10000;
        for (const u32 node : rows_of(m, list)) {
            const s32 key = r16(m, kQuestTable + 64 * r32(m, row_user(m, node) + 4) + f2::quest::kOrder);
            CHECK((key <= prev || prev == -0x10000));  // the comparator is b - a: descending order keys
            prev = key;
        }
    }
    const auto rows = rows_of(m, list);
    for (u32 n = 0; n + 1 < rows.size(); ++n) {
        const u32 a = kOut + 0x300, b = kOut + 0x304;
        w32(m, a, rows[n]);
        w32(m, b, rows[n + 1]);
        const s32 ka = r16(m, kQuestTable + 64 * r32(m, row_user(m, rows[n]) + 4) + f2::quest::kOrder);
        const s32 kb = r16(m, kQuestTable + 64 * r32(m, row_user(m, rows[n + 1]) + 4) + f2::quest::kOrder);
        CHECK(v0s(f2pair(m, "sub_405DB0", {sx(a), sx(b), 0, 0}, ++seed, "compare", kKeep)) == kb - ka);
    }
    for (u32 part = 0; part < 9; ++part)
        for (u32 phase = 0; phase < 2; ++phase) f2pair(m, "sub_404750", {sx(list), part, phase, 0}, ++seed, "request anim", kKeep);
    for (int frame = 0; frame < 6; ++frame) {
        w16(m, kPadA, frame == 2 ? 0x1000 : 0);
        f2pair(m, "sub_405E30", {sx(list), 0, 0, 0}, ++seed, "request update", kKeep);
        if (const u32 cur = r32(m, list + f2::lst::kCursor)) CHECK(flag(m, 4351 + r16(m, row_user(m, cur) + 4)));
    }
    f2pair(m, "sub_407180", {10, 20, 128, sx(list)}, ++seed, "request window draw", kKeep);
    for (const u32 node : rows_of(m, list)) {
        Opt o = kKeep;
        o.gpr_in = {{GPR_T0, sx(node)}};
        f2pair(m, "sub_407210", {10, 20, 128, sx(list)}, ++seed, "request row draw", o);
    }
    f2pair(m, "sub_405A90", {sx(list), sx(rows.back()), 0, 0}, ++seed, "request row free", kKeep);
    f2pair(m, "sub_405D60", {sx(list), 0, 0, 0}, ++seed, "request list destroy", kKeep);
    MESSAGE("requests: deadline states 0/1/2/3 = " << states[0] << "/" << states[1] << "/" << states[2] << "/" << states[3] << "; "
                                                   << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 5. The compendium: the list, the price rule, the sorts, register-all, the stock test
// =====================================================================================================================
TEST_CASE("game(facility2): the compendium list (documented rules)") {
    bool have = false;
    auto mp = snap_machine("fusion_vr_5000", have);
    if (!mp) return;
    Machine& m = *mp;
    if (!have) return;
    u32 seed = 5000;
    fresh_worlds();
    // make sure some personas are registered: the stock's (datCompendiumStore)
    const u32 stock = static_cast<u16>(oracle(m, &recomp_gen::fn_sub_175410_00175410, {0, 0, 0, 0}));
    for (u32 i = 0; i < stock; ++i)
        if (const u32 p = static_cast<u32>(oracle(m, &recomp_gen::fn_sub_174A90_00174a90, {i, 0, 0, 0})))
            setup(m, &recomp_gen::fn_sub_17C960_0017c960, "datCompendiumStore", {sx(p), 0, 0, 0}, ++seed);
    f2pair(m, "sub_409E90", {0, 0, 0, 0}, ++seed, "stock registered", kKeep);
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    for (const bool flag4889 : {false, true}) {
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        set_flag(m, 4889, flag4889);
        const u32 list = make_list(m, 88, 7, 26, seed);
        f2pair(m, "sub_409C80", {sx(list), 0, 0, 0}, ++seed, "compendium fill", kKeep);
        std::vector<u32> want;
        for (u32 id = 1; id < 256; ++id)
            if (const u32 p = static_cast<u32>(oracle(m, &recomp_gen::fn_sub_17C8C0_0017c8c0, {id, 0, 0, 0}))) want.push_back(p);
        const auto rows = rows_of(m, list);
        CHECK(rows.size() == want.size());
        MESSAGE("compendium (flag 4889 " << flag4889 << "): " << rows.size() << " registered personas listed");
        for (std::size_t k = 0; k < rows.size() && k < want.size(); ++k) {
            const u32 u = row_user(m, rows[k]);
            CHECK(r32(m, u + f2::crow::kPersona) == want[k]);
            u32 s = 0;
            for (u32 st = 0; st < 5; ++st) s += static_cast<u8>(oracle(m, &recomp_gen::fn_sub_173580_00173580, {sx(want[k]), st, 0, 0}));
            u32 price = 3u * s * s + 2000u;
            if (flag4889) price = 4u * price < 10000000u ? 4u * price : 9999999u;
            CHECK(r32(m, u + f2::crow::kPrice) == price);
            CHECK(r32(m, u + f2::crow::kElems) != 0u);
        }
        // the two sorts against host comparators (level, arcana, id) / (arcana, level, id)
        for (const u32 by_arcana : {0u, 1u, 0u}) {
            f2pair(m, "sub_40A6D0", {sx(list), by_arcana, 0, 0}, ++seed, "compendium sort", kKeep);
            CHECK(((r32(m, win_user(m, list) + f2::menu::kFlags) & 2u) != 0u) == (by_arcana == 1u));
            const auto sorted = rows_of(m, list);
            for (std::size_t k = 0; k + 1 < sorted.size(); ++k) {
                const u32 pa = r32(m, row_user(m, sorted[k]) + f2::crow::kPersona), pb = r32(m, row_user(m, sorted[k + 1]) + f2::crow::kPersona);
                const s32 la = r8(m, pa + f2::persona::kLevel), lb = r8(m, pb + f2::persona::kLevel);
                const s32 aa = arcana_of(m, ru16(m, pa + f2::persona::kId)), ab = arcana_of(m, ru16(m, pb + f2::persona::kId));
                const s32 ia = ru16(m, pa + f2::persona::kId), ib = ru16(m, pb + f2::persona::kId);
                // comparators as the bodies compute them, on the stored pair
                const u32 a = kOut + 0x300, b = kOut + 0x304;
                w32(m, a, sorted[k]);
                w32(m, b, sorted[k + 1]);
                const s32 got_level = v0s(f2pair(m, "sub_40A5B0", {sx(a), sx(b), 0, 0}, ++seed, "cmp level", kKeep));
                CHECK(got_level == (lb != la ? lb - la : (ab != aa ? aa - ab : ia - ib)));
                const s32 got_arcana = v0s(f2pair(m, "sub_40A640", {sx(a), sx(b), 0, 0}, ++seed, "cmp arcana", kKeep));
                CHECK(got_arcana == (aa != ab ? aa - ab : (lb != la ? lb - la : ia - ib)));
                CHECK((by_arcana ? got_arcana : got_level) <= 0);  // nmCmdListSort: ascending by the comparator
            }
        }
        f2pair(m, "sub_40A260", {sx(list), 0, 0, 0}, ++seed, "register all", kKeep);
        f2pair(m, "sub_40B630", {10, 20, 200, sx(list)}, ++seed, "compendium window draw", kKeep);
        for (const u32 node : rows_of(m, list)) {
            Opt o = kKeep;
            o.gpr_in = {{GPR_T0, sx(node)}};
            f2pair(m, "sub_40B780", {10, 20, 200, sx(list)}, ++seed, "compendium row draw", o);
            f2pair(m, "sub_40A7C0", {10, 20, 200, 0}, ++seed, "mark", kKeep);
        }
        if (!rows_of(m, list).empty()) f2pair(m, "sub_409F20", {sx(list), sx(rows_of(m, list).front()), 0, 0}, ++seed, "row free", kKeep);
        f2pair(m, "sub_40A200", {sx(list), 0, 0, 0}, ++seed, "compendium destroy", kKeep);
    }
    MESSAGE("compendium: " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 6. The trade and weapon-fusion lists on the shop snapshot, and every list function on them
// =====================================================================================================================
TEST_CASE("game(facility2): trade and weapon-fusion lists (documented rules)") {
    bool have = false;
    auto mp = snap_machine("shop_ref_4100", have);
    if (!mp) return;
    Machine& m = *mp;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    u32 seed = 6000;
    int rows_checked = 0;
    for (const u32 type : {3u, 4u}) {
        for (const u32 mode : {0u, 1u}) {
            std::memcpy(m.mem.main_ram(), base.data(), base.size());
            fresh_worlds();
            const hgp::Run built = f2pair(m, "sub_3FEF30", {type, mode, 0, 0}, ++seed, "trade list", kKeep);
            const u32 list = v0u(built);
            INFO("trade list: " << (built.stopped ? built.what + " at " + hex64(built.stop_pc) : std::string("returned")));
            REQUIRE(list >= kStandInHeap);
            CHECK(r16(m, win_user(m, list) + f2::menu::kShopType) == static_cast<s16>(type));
            CHECK(r16(m, win_user(m, list) + f2::menu::kMode) == (mode ? f2::menu::kModeTradeIn : f2::menu::kModeTrade));
            // the rows against the tables: the base table, then (trades) the extra tables 1..sub_3F03E0(4)
            std::vector<u32> want;
            auto table = [&](u32 entries, u32 count) {
                for (u32 i = 0; i < count; ++i) {
                    const u32 e = entries + f2::tent::kSize * i;
                    const s16 fl = r16(m, e + f2::tent::kFlag);
                    if (fl != 0 && !flag(m, static_cast<u16>(fl))) continue;
                    if (r16(m, e + f2::tent::kItem) == 0 || r16(m, e + f2::tent::kMatCount) == 0) continue;
                    want.push_back(e);
                }
            };
            table(r32(m, kTradeTables + (mode ? 8 : 0)), r32(m, kTradeTables + (mode ? 12 : 4)));
            if (!mode) {
                const s64 n = static_cast<s32>(oracle(m, &recomp_gen::fn_sub_3F03E0_003f03e0, {4, 0, 0, 0}));
                const u32 extra = r32(m, kTradeTables + 16), nextra = r32(m, kTradeTables + 20);
                for (s64 i = 1; i <= n; ++i) table(r32(m, extra + 8 * static_cast<u32>(i)), r32(m, extra + 8 * static_cast<u32>(i) + 4));
                (void)nextra;  // an index past the count is only K_Assert'ed (retail continues): the table is still read
            }
            const auto rows = rows_of(m, list);
            CHECK(rows.size() == want.size());
            for (std::size_t k = 0; k < rows.size() && k < want.size(); ++k) {
                const u32 u = row_user(m, rows[k]), e = want[k];
                CHECK(r16(m, u + f2::srow::kItem) == r16(m, e + f2::tent::kItem));
                CHECK(r16(m, u + f2::srow::kMat1Count) == r16(m, e + f2::tent::kMatCount));
                if (k < 24) {  // the owned count and the availability rule, from the inventory oracles
                    const s32 owned = owned_model(m, ru16(m, u + f2::srow::kItem));
                    CHECK(r16(m, u + f2::srow::kOwned) == owned);
                    bool unavailable = owned >= 99;
                    for (const auto [mi, mc] : {std::pair{f2::srow::kMat1, f2::srow::kMat1Count}, std::pair{f2::srow::kMat2, f2::srow::kMat2Count}})
                        if (r16(m, u + mi) != 0 && owned_model(m, ru16(m, u + mi)) < r16(m, u + mc)) unavailable = true;
                    CHECK(((r32(m, u + f2::srow::kFlags) & 0x10u) != 0u) == unavailable);
                    ++rows_checked;
                }
            }
            // every list function on it
            f2pair(m, "sub_3FEE40", {sx(list), 0, 0, 0}, ++seed, "trade refresh", kKeep);
            for (const u32 node : rows) f2pair(m, "sub_3FEB30", {sx(list), sx(node), 0, 0}, ++seed, "trade row state", kKeep);
            const u32 old = v0u(f2pair(m, "sub_3FF150", {type, mode, 0, 0}, ++seed, "old trade list", kKeep));
            f2pair(m, "sub_3F3E60", {sx(list), sx(old), 0, 0}, ++seed, "remove listed", kKeep);
            f2pair(m, "sub_3FF460", {sx(list), sx(old), 0, 0}, ++seed, "mark new trades", kKeep);
            for (int frame = 0; frame < 4; ++frame) {
                w16(m, kPadA, frame == 1 ? 0x1000 : (frame == 2 ? 0x4000 : 0));
                f2pair(m, "sub_3FF570", {sx(list), 0, 0, 0}, ++seed, "trade update", kKeep);
                f2pair(m, "sub_3FE1F0", {sx(list), 0, 0, 0}, ++seed, "category update", kKeep);
                f2pair(m, "sub_3FE5D0", {sx(list), 0, 0, 0}, ++seed, "fusion items update", kKeep);
                f2pair(m, "sub_3FE950", {sx(list), 0, 0, 0}, ++seed, "fusion personas update", kKeep);
            }
            // the window animations: every variant over 24 frames in each fade state
            const u32 st = r32(m, list + f2::lst::kState);
            for (const u32 flags : {0x0Au, 0x02u, 0x82u, 0x102u, 0x8Eu}) {
                for (s16 t = 0; t < 24; t += 3) {
                    w32(m, st + f2::win::kFlags, flags);
                    w16(m, st + f2::win::kFrame, static_cast<u16>(t));
                    for (const char* fn : {"sub_3FA210", "sub_3FA520", "sub_3FA800", "sub_3FAAE0", "sub_3FADC0"}) {
                        const hgp::Run r = f2pair(m, fn, {sx(list), 0, 0, 0}, ++seed, "window anim", kKeep);
                        const u32 u = win_user(m, list);
                        if (v0u(r) == 20u) {  // closing
                            CHECK(r16(m, u + f2::menu::kSlideX) == (t >= 11 ? -160 : static_cast<s16>(static_cast<s32>(static_cast<float>(-160 * t) / 10.0f))));
                            if (t >= 6) CHECK(r16(m, u + f2::menu::kAlpha) == 0);
                        } else if (v0u(r) == 12u) {  // opening
                            CHECK(r16(m, u + f2::menu::kSlideX) == 0);
                            CHECK(r16(m, u + f2::menu::kSlideY) == 0);
                            if (t >= 6) CHECK(r16(m, u + f2::menu::kAlpha) == 255);
                        }
                    }
                }
            }
            w32(m, st + f2::win::kFlags, 0x0Au);
            // the row drawers on every row
            for (const u32 node : rows) {
                Opt o = kKeep;
                o.gpr_in = {{GPR_T0, sx(node)}, {GPR_T1, sx(node)}};
                f2pair(m, "sub_3F9510", {40, 60, 128, sx(list)}, ++seed, "row draw", o);
                for (const char* fn : {"sub_3F5AB0", "sub_3F5D10", "sub_3F5F50", "sub_3F61D0", "sub_3F6F20"}) f2pair(m, fn, {40, 60, 128, 0}, ++seed, fn, o);
                for (const u64 a3 : {0, 1, 2}) {
                    Opt o2 = kKeep;
                    o2.gpr_in = {{GPR_T0, 0}, {GPR_T1, sx(node)}};
                    f2pair(m, "sub_3F67E0", {40, 60, 128, a3}, ++seed, "compare B", o2);
                    f2pair(m, "sub_3F7890", {40, 60, 128, a3}, ++seed, "owned box", o2);
                }
                f2pair(m, "sub_3FCBE0", {40, 60, 128, sx(list)}, ++seed, "category row A", o);
                f2pair(m, "sub_3FD140", {40, 60, 128, sx(list)}, ++seed, "category row B", o);
                f2pair(m, "sub_3FE7D0", {sx(list), sx(node), 0, 0}, ++seed, "fusion row flags", kKeep);
            }
            const u32 hdr = kOut + 0x400;
            w16(m, hdr, 5);
            w16(m, hdr + 2, 7);
            w16(m, hdr + 12, 200);
            for (const u64 a3 : {0, 1, 2, 3, 4, 7}) {
                Opt o = kKeep;
                o.gpr_in = {{GPR_T1, sx(hdr)}};
                f2pair(m, "sub_3F4A90", {40, 60, 128, a3}, ++seed, "list header", o);
            }
            f2pair(m, "sub_3FCA00", {0, 0, 200, 0}, ++seed, "frame sprites", kKeep);
            f2pair(m, "sub_40C150", {sx(list), 0, 0, 0}, ++seed, "flag bit", kKeep);
            // destroy through the pair helper: {list, object}
            w32(m, kOut + 0x500, list);
            w32(m, kOut + 0x504, 0);
            f2pair(m, "sub_4003A0", {sx(kOut + 0x500), 0, 0, 0}, ++seed, "destroy pair", kKeep);
        }
        // weapon fusion: the base-item list, then the persona list for each base item
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        fresh_worlds();
        const u32 items = v0u(f2pair(m, "sub_3FE3E0", {type, 0, 0, 0}, ++seed, "fusion item list", kKeep));
        REQUIRE(items >= kStandInHeap);
        CHECK(r16(m, win_user(m, items) + f2::menu::kMode) == f2::menu::kModeFusionItems);
        for (u32 i = 0; i < 8; ++i) {
            const u32 entry = kOut + 0x600;
            zero(m, entry, 28);
            w16(m, entry, ru16(m, 0x6AF180u + 2 * i));
            const u32 pl = v0u(f2pair(m, "sub_3FE850", {type, sx(entry), 0, 0}, ++seed, "fusion persona list", kKeep));
            REQUIRE(pl >= kStandInHeap);
            CHECK(r16(m, win_user(m, pl) + f2::menu::kMode) == f2::menu::kModeFusionPersonas);
            const u32 stock = static_cast<u16>(oracle(m, &recomp_gen::fn_sub_175410_00175410, {0, 0, 0, 0}));
            u32 nonzero = 0;
            for (u32 s = 0; s < stock; ++s)
                if (oracle(m, &recomp_gen::fn_sub_174A90_00174a90, {s, 0, 0, 0})) ++nonzero;
            CHECK(rows_of(m, pl).size() == nonzero);
            for (const u32 node : rows_of(m, pl)) {
                const u32 u = row_user(m, node);
                CHECK(((r32(m, u + f2::srow::kFlags) & 0x10u) != 0u) == (ru16(m, u + f2::srow::kResult) == 0));
                Opt o = kKeep;
                o.gpr_in = {{GPR_T0, sx(node)}};
                f2pair(m, "sub_3F9510", {40, 60, 128, sx(pl)}, ++seed, "fusion row draw", o);
            }
            f2pair(m, "sub_3FE690", {sx(pl), sx(entry), 0, 0}, ++seed, "fusion personas again", kKeep);
        }
    }
    MESSAGE("trade / fusion lists: " << rows_checked << " rows checked; " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 7. A lineup filled into a buy list: filters, the price rate, the sale
// =====================================================================================================================
TEST_CASE("game(facility2): lineup prices and the sale (documented rules)") {
    bool have = false;
    auto mp = snap_machine("shop_ref_4100", have);
    if (!mp) return;
    Machine& m = *mp;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    u32 seed = 7000;
    // items: the trade tables' (real items of every kind)
    std::vector<u16> items;
    for (u32 t = 0; t < 2; ++t)
        for (u32 i = 0; i < r32(m, kTradeTables + 8 * t + 4) && items.size() < 24; ++i) {
            const u16 id = ru16(m, r32(m, kTradeTables + 8 * t) + 14 * i);
            if (id && std::find(items.begin(), items.end(), id) == items.end()) items.push_back(id);
        }
    REQUIRE(!items.empty());
    const u32 lu = kOut + 0x1000, ent = kOut + 0x1100;
    int priced = 0, sold = 0;
    for (const u32 filter : {0u, 1u, 0x2000u, 0x4000u, 0x400u, 0x800u, 0x1000u, 0x4001u}) {
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        fresh_worlds();
        zero(m, lu, 0x200);
        w16(m, lu + f2::lineup::kRate, 120);
        w16(m, lu + f2::lineup::kCount, static_cast<u16>(items.size()));
        w32(m, lu + f2::lineup::kEntries, ent);
        for (u32 i = 0; i < items.size(); ++i) {
            const u32 e = ent + f2::lent::kSize * i;
            w16(m, e + f2::lent::kId, items[i]);
            w16(m, e + f2::lent::kRate, static_cast<u16>(i % 3 == 0 ? 0 : 50 + 25 * (i % 5)));
            w8(m, e + f2::lent::kCond, static_cast<u8>(i % 11 == 5 ? 1 : 0));
            w8(m, e + f2::lent::kFlags, static_cast<u8>((i % 4 == 1 ? 1 | 4 : i % 4 == 2 ? 1 | 2 : 0) | (i % 6 == 3 ? 8 : 0)));
            w8(m, e + f2::lent::kStock, static_cast<u8>(i % 8));
        }
        const u32 list = make_list(m, 88, 7, 26, seed);
        const hgp::Run r = f2pair(m, "sub_3F25E0", {sx(list), sx(lu), filter, 0}, ++seed, "lineup fill", kKeep);
        if (filter == 0x1000u) continue;  // the test-only filter returns at the first passing item
        if (filter == 0x2000u) f2pair(m, "sub_3F25E0", {sx(list), sx(lu), filter, 0}, ++seed, "lineup fill again", kKeep);
        CHECK(v0u(r) == 0u);
        for (const u32 node : rows_of(m, list)) {
            const u32 u = row_user(m, node);
            const u16 id = ru16(m, u + f2::srow::kItem);
            const auto it = std::find(items.begin(), items.end(), id);
            REQUIRE(it != items.end());
            const u32 e = ent + f2::lent::kSize * static_cast<u32>(it - items.begin());
            const s32 rate = r16(m, e + f2::lent::kRate) > 0 ? r16(m, e + f2::lent::kRate) : 120;
            CHECK(static_cast<s32>(r32(m, u + f2::srow::kPrice)) == price_model(m, id) * rate / 100);
            CHECK(((r32(m, u + f2::srow::kFlags) & 1u) != 0u) == ((filter & 1u) != 0u));
            CHECK(ru16(m, node + f2::node::kWord4) == id);
            ++priced;
        }
        if (filter == 0x2000u) {  // the second fill skipped every listed item
            std::vector<u16> seen;
            for (const u32 node : rows_of(m, list)) {
                const u16 id = ru16(m, row_user(m, node) + f2::srow::kItem);
                CHECK(std::find(seen.begin(), seen.end(), id) == seen.end());
                seen.push_back(id);
            }
        }
        // the sale
        std::vector<std::pair<u32, s32>> before;
        for (const u32 node : rows_of(m, list)) before.emplace_back(row_user(m, node), static_cast<s32>(r32(m, row_user(m, node) + f2::srow::kPrice)));
        f2pair(m, "sub_3F2320", {sx(list), sx(lu), 0, 0}, ++seed, "sale", kKeep);
        CHECK((r32(m, win_user(m, list) + f2::menu::kFlags) & 2u) != 0u);
        for (const auto& [u, p] : before) {
            const u32 fl = r32(m, u + f2::srow::kFlags);
            const float k = (fl & 8u) ? 0.5f : (fl & 4u) ? 0.3f : 0.25f;
            const float pf = static_cast<float>(p);
            s32 want = static_cast<s32>(pf - k * pf);
            if (want < 0) want = 1;
            CHECK(static_cast<s32>(r32(m, u + f2::srow::kPrice)) == want);
            ++sold;
        }
    }
    MESSAGE("lineups: " << priced << " rows priced, " << sold << " sale prices; " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 8. The shop steps' callbacks, the panels, the option rows, the fusion list helpers, the date panel
// =====================================================================================================================
TEST_CASE("game(facility2): shop steps, panels and the date panel") {
    bool have = false;
    auto mp = snap_machine("shop_ref_4100", have);
    if (!mp) return;
    Machine& m = *mp;
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    u32 seed = 8000;
    const Opt plain{{}, false};
    const u32 seq = r32(m, 0x7CE688u);
    CHECK(v0u(f2pair(m, "sub_3E0940", {0, 0, 0, 0}, ++seed, "shop sequence", plain)) == seq);
    if (seq) {
        const u32 work = r32(m, r32(m, seq + f2::lst::kState) + 12);
        for (const u32 mask : {0u, 1u, 4u, 0x20u, 0xFFu, 0xFFFFFFFFu})
            CHECK(v0u(f2pair(m, "sub_3E6E20", {mask, 0, 0, 0}, ++seed, "shop flags", plain)) ==
                  ((r32(m, work + f2::shopw::kFlags) & mask) ? 1u : 0u));
        // steps: a node whose payload chain gives the step payload (sub_3C5470: node +20 -> +40)
        const u32 node = kOut + 0x2000, pl = kOut + 0x2040, pay = kOut + 0x2080;
        auto step_node = [&] {
            zero(m, kOut + 0x2000, 0x200);
            w32(m, node + f2::node::kPayload, pl);
            w32(m, pl + 40, pay);
        };
        for (const u32 state : {69u, 71u, 3u}) {
            reset();
            fresh_worlds();
            step_node();
            w32(m, work + f2::shopw::kState, state);
            const hgp::Run ti = f2pair(m, "sub_3EBB90", {sx(seq), sx(node), 0, 0}, ++seed, "TRADE init", kKeep);
            INFO("TRADE init: " << (ti.stopped ? ti.what + " at " + hex64(ti.stop_pc) : std::string("returned")));
            CHECK(r32(m, pay + f2::step::kPhase) == 1u);
            CHECK((r32(m, pay + f2::step::kFlags) & 2u) != 0u);
            if (state != 3u) {
                CHECK(r32(m, pay + f2::step::kList) >= kStandInHeap);
                for (const u32 hidden : {2u, 0u}) {
                    w32(m, pay + f2::step::kFlags, hidden);
                    f2pair(m, "sub_3EBFE0", {sx(seq), sx(node), 0, 0}, ++seed, "TRADE draw", kKeep);
                    f2pair(m, "sub_3EC6A0", {sx(seq), sx(node), 0, 0}, ++seed, "QUEST draw", kKeep);
                    f2pair(m, "sub_3ECCE0", {sx(seq), sx(node), 0, 0}, ++seed, "QUESTCANCEL draw", kKeep);
                    f2pair(m, "sub_3EDD80", {sx(seq), sx(node), 0, 0}, ++seed, "BOOKREGIST draw", kKeep);
                }
                f2pair(m, "sub_3EBC70", {sx(seq), sx(node), 0, 0}, ++seed, "TRADE fini", kKeep);
            }
        }
        reset();
        fresh_worlds();
        step_node();
        f2pair(m, "sub_3EAEB0", {sx(seq), sx(node), 0, 0}, ++seed, "ARMSCOMBINE init", kKeep);
        CHECK(r32(m, pay + f2::step::kList) >= kStandInHeap);
        CHECK(r32(m, pay + f2::step::kList2) == 0u);
        for (const u32 hidden : {2u, 0u}) {
            w32(m, pay + f2::step::kFlags, hidden);
            f2pair(m, "sub_3EB940", {sx(seq), sx(node), 0, 0}, ++seed, "ARMSCOMBINE draw", kKeep);
        }
        f2pair(m, "sub_3EAF30", {sx(seq), sx(node), 0, 0}, ++seed, "ARMSCOMBINE fini", kKeep);
        // QUEST / QUESTCANCEL / BOOK / BOOKREGIST finis on lists with a window element set (and a book task word 0)
        for (const char* fini : {"sub_3EC280", "sub_3EC8E0", "sub_3ED5A0", "sub_3ECF80"}) {
            reset();
            fresh_worlds();
            step_node();
            const u32 list = make_list(m, 88, 6, 26, seed);
            const u32 wu = win_user(m, list);
            w32(m, wu + f2::menu::kElems, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
            w32(m, wu + f2::menu::kElemsA, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
            w32(m, pay + f2::step::kList, list);
            w32(m, pay + f2::step::kList2, list);
            f2pair(m, "sub_3ED310", {sx(seq), sx(node), 0, 0}, ++seed, "BOOK draw", kKeep);
            f2pair(m, fini, {sx(seq), sx(node), 0, 0}, ++seed, fini, kKeep);
        }
        for (const char* fini : {"sub_3EE4E0", "sub_3EE640", "sub_3EEE50"}) f2pair(m, fini, {sx(seq), sx(node), 0, 0}, ++seed, fini, plain);
        // BG fini on the live background manager (the BG step +64 of the work record)
        reset();
        const u32 bgnode = r32(m, work + 64);
        if (bgnode) f2pair(m, "sub_3EFC20", {sx(seq), sx(bgnode), 0, 0}, ++seed, "BG fini");
    }
    // the BG part lists (a part list object at the list user +4 with {+4, +6} events)
    reset();
    fresh_worlds();
    {
        const u32 list = make_list(m, 88, 6, 26, seed);
        const u32 parts = make_list(m, 16, 4, 8, seed);
        w32(m, win_user(m, list) + f2::menu::kShopType, parts);
        for (u32 k = 0; k < 5; ++k) {
            const u32 n = add_row(m, parts, 16, seed);
            const u32 p = r32(m, n + f2::node::kPayload);
            w16(m, p + f2::bgpart::kCondA, static_cast<u16>(k));
            w16(m, p + f2::bgpart::kCondB, static_cast<u16>(k * 3));
        }
        for (u32 rowsn = 3; rowsn < 7; ++rowsn) {
            w16(m, list + f2::lst::kCount, static_cast<u16>(rowsn));
            f2pair(m, "sub_4008F0", {10, 20, 200, sx(list)}, ++seed, "bg parts draw", kKeep);
        }
        f2pair(m, "sub_4006C0", {10, 20, 200, sx(list)}, ++seed, "bg parts purge", kKeep);
    }
    // option rows (16-byte entries {flag A, flag B}) and the panel drivers / part animator on the list
    reset();
    fresh_worlds();
    {
        const u32 list = make_list(m, 88, 6, 26, seed);
        const u32 work = kOut + 0x2400, tab = kOut + 0x2500, keys = kOut + 0x2600;
        zero(m, kOut + 0x2400, 0x400);
        w32(m, work + 12, list);
        w32(m, tab + f2::ttab::kEntries, tab + 0x20);
        w32(m, tab + f2::ttab::kCount, 6);
        for (u32 i = 0; i < 6; ++i) {
            w32(m, tab + 0x20 + 16 * i + f2::hent::kFlagA, i == 2 ? 4889u : 0u);
            w32(m, tab + 0x20 + 16 * i + f2::hent::kFlagB, i == 4 ? 100u : 0u);
            w32(m, keys + 4 * i, 10 + i);
        }
        f2pair(m, "sub_40C1E0", {sx(work), sx(tab), sx(keys), 0}, ++seed, "option rows (keys)", kKeep);
        f2pair(m, "sub_40C1E0", {sx(work), sx(tab), 0, 0}, ++seed, "option rows", kKeep);
        for (const u32 node : rows_of(m, list)) CHECK(r32(m, row_user(m, node) + f2::hrow::kEntry) >= tab + 0x20);
        const u32 panel = win_user(m, list);
        w32(m, panel + f2::panel::kElems, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
        w32(m, panel + f2::panel::kList, list);
        for (u32 part = 0; part < 9; ++part)
            for (const u32 phase : {0u, 1u, 3u, 2u}) f2pair(m, "sub_3D9820", {sx(panel), part, phase, 0}, ++seed, "part anim", kKeep);
        for (const char* fn : {"sub_40C520", "sub_40C5B0", "sub_40C650", "sub_40C6A0", "sub_40CA00"}) f2pair(m, fn, {sx(panel), 0, 0, 0}, ++seed, fn, kKeep);
        f2pair(m, "sub_40D330", {sx(list), 0, 0, 0}, ++seed, "panel step", kKeep);
        if (!rows_of(m, list).empty()) f2pair(m, "sub_40C460", {sx(list), sx(rows_of(m, list).front()), 0, 0}, ++seed, "option row free", kKeep);
        // the category lists (a category work {+0 list of categories, +8 window elements}; category rows {+4 sub-list,
        // +8 elements})
        const u32 cw = kOut + 0x2800;
        zero(m, cw, 0x40);
        const u32 cats = make_list(m, 88, 6, 26, seed);
        w32(m, cw + f2::catw::kList, cats);
        w32(m, cw + f2::catw::kElems, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
        for (u32 k = 0; k < 3; ++k) {
            const u32 n = add_row(m, cats, 16, seed);
            const u32 p = r32(m, n + f2::node::kPayload);
            w32(m, p + f2::cat::kList, make_list(m, 88, 6, 26, seed));
            w32(m, p + f2::cat::kElems, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
        }
        w32(m, cats + f2::lst::kCursor, r32(m, cats + f2::lst::kHead));
        f2pair(m, "sub_3FD8E0", {sx(cw), 0, 0, 0}, ++seed, "open categories", kKeep);
        for (const u16 pad : {u16{0}, u16{8}, u16{4}, u16{0}}) {
            w16(m, kPadA, pad);
            f2pair(m, "sub_3FD990", {sx(cw), 0, 0, 0}, ++seed, "categories update", kKeep);
        }
        const u32 cat0 = r32(m, cats + f2::lst::kHead);
        f2pair(m, "sub_3FD7E0", {sx(cats), sx(cat0), 0, 0}, ++seed, "free category row", kKeep);
    }
    // the fusion list helpers on a hand-made list work (+0 -> {+8 command list, +16 element set}, +20 elements)
    reset();
    fresh_worlds();
    {
        const u32 list = make_list(m, 88, 6, 26, seed);
        const u32 lw = kOut + 0x3000, inner = kOut + 0x3040;
        zero(m, lw, 0x80);
        w32(m, lw, inner);
        w32(m, inner + 8, list);
        w32(m, inner + 16, v0u(setup(m, &recomp_gen::fn_sub_3DFEB0_003dfeb0, "elements", {0, 0, 0, 0}, ++seed)));
        w32(m, inner + 20, r32(m, inner + 16));
        f2pair(m, "sub_3D3170", {sx(lw), 0, 0, 0}, ++seed, "fusion list cancel", kKeep);
        f2pair(m, "sub_3D3170", {0, 0, 0, 0}, ++seed, "fusion list cancel (no work)", kKeep);
        for (u32 part = 0; part < 2; ++part)
            for (u32 phase = 0; phase < 3; ++phase) f2pair(m, "sub_3D3760", {sx(inner), part, phase, 0}, ++seed, "fusion panel anim", kKeep);
        const u32 row = add_row(m, list, 16, seed);
        w32(m, row_user(m, row) + 4, 0x5A5u);
        for (const u32 mode : {3u, 0u}) {
            w32(m, win_user(m, list) + 12, mode);
            Opt o = kKeep;
            o.gpr_in = {{GPR_T0, sx(row)}, {GPR_T1, 7}};
            f2pair(m, "sub_3DCA10", {100, 50, 200, sx(list)}, ++seed, "stock slots", o);
        }
        // the icon strip: an element {x, y, alpha} and a context {x, y, alpha, flags, -> row flags, ..., -> list}
        const u32 el = kOut + 0x3100, cx = kOut + 0x3180, fl = kOut + 0x31C0;
        zero(m, el, 0x100);
        w16(m, el + f2::elem::kX, 12);
        w16(m, el + f2::elem::kY, 34);
        w16(m, el + f2::elem::kAlpha, 200);
        w32(m, cx + 0, 40);
        w32(m, cx + 4, 60);
        w16(m, cx + 8, 255);
        w32(m, cx + 12, fl);
        w32(m, cx + 20, list);
        for (const u32 lmode : {0u, 2u})
            for (const u32 rowflag : {0u, 1u})
                for (const u16 cflag : {u16{0}, u16{2}})
                    for (const u64 bright : {0, 1}) {
                        w32(m, win_user(m, list) + 4, lmode);
                        w32(m, fl, rowflag);
                        w16(m, cx + 10, cflag);
                        f2pair(m, "sub_3DCFB0", {0, sx(el), sx(cx), bright}, ++seed, "icon strip", kKeep);
                    }
    }
    // the date panel on three days: the month / day texts against the calendar
    for (const s16 day : {static_cast<s16>(r16(m, kDaysSinceApr5)), s16{0}, s16{200}}) {
        reset();
        w16(m, kDaysSinceApr5, static_cast<u16>(day));
        const hgp::Run dp = f2pair(m, "sub_406AA0", {20, 30, 255, 0}, ++seed, "date panel");
        INFO("date panel: " << (dp.stopped ? dp.what + " at " + hex64(dp.stop_pc) : std::string("returned")));
        const auto& log = g_t.world[1]->si.log;
        std::vector<std::string> texts;
        for (const StandInCall& c : log)
            if (c.va == kSprintf) texts.push_back(c.text);
        REQUIRE(texts.size() == 2u);
        char want[16];
        std::snprintf(want, sizeof want, "%d", static_cast<int>(static_cast<s32>(oracle(m, &recomp_gen::fn_clndGetCurrentMonth_0017d920, {0, 0, 0, 0}))));
        CHECK(texts[0] == want);
        std::snprintf(want, sizeof want, "%d", static_cast<int>(static_cast<s32>(oracle(m, &recomp_gen::fn_clndGetCurrentDay_0017da40, {0, 0, 0, 0}))));
        CHECK(texts[1] == want);
    }
    // the small helpers
    reset();
    f2pair(m, "sub_3FBF10", {sx(kOut), 0, 0, 0}, ++seed, "word 3", plain);
    CHECK(ru16(m, kOut) == 3u);
    for (u32 item = 1; item < 0x700; item += 97) f2pair(m, "sub_3F1910", {item, 0, 0, 0}, ++seed, "count owned", plain);
    for (u32 item = 1; item < 0x700; item += 89) {
        f2pair(m, "sub_3F1BA0", {sx(kOut + 0x100), item, 0, 0}, ++seed, "item entry", plain);
        CHECK(ru16(m, kOut + 0x100 + f2::item::kId) == item);
        CHECK(static_cast<s32>(r32(m, kOut + 0x100 + f2::item::kPrice)) == price_model(m, item));
    }
    for (u32 slot = 0; slot < 300; slot += 13)
        for (const u64 opts : {0, 1, 2, 4, 8, 15}) {
            const u32 item = static_cast<u16>(oracle(m, &recomp_gen::fn_sub_16F630_0016f630, {1, slot, 0, 0}));
            f2pair(m, "sub_402510", {item, sx(0xFFFFFFFFu), opts, slot}, ++seed, "slot holds", plain);
            f2pair(m, "sub_402510", {item, 0, opts, slot}, ++seed, "slot holds (member 0)", plain);
            CHECK(v0u(f2pair(m, "sub_402510", {(item + 1) & 0xFFFFu, 0, opts, slot}, ++seed, "slot holds other", plain)) == 0u);
        }
    MESSAGE("steps / panels: " << g_pairs << " pairs in all");
    for (const auto& [where, n] : g_stops) MESSAGE("  stopped early (both bodies alike): " << where << " x" << n);
}

#else

TEST_CASE("game(facility2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
