// Pair tests for slice events2 (game/src/event/events2.cpp): the event system's second pass against its recompiled
// bodies. Every pair compares the whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and the cycle count at
// every check point and at the return, all 32 MiB of RAM (write-tracked) including the dead stack, the scratchpad, the
// bus log and, with stand-ins (stand_ins.h), every call to a function this test library does not emit (a recorder
// each; printf / the heap / the H_Cdvd layer stand in as usual, the files from extracted/DATA).
//   * random worlds: every body on p3fes_handgen's random worlds (runs that reach a missing callee stop identically);
//   * the editor: 16 key setters of the menu-action table 0x69DE40 on built units, each documented copy (key field =
//     edit field) checked on the host, the menu popped, the other keys untouched; deleting a key (the list, the count,
//     the cursor rule); the random-jump pick against the draw it logs;
//   * the live opening event of the dorm route (E401_002; extracted/_ours/events_dorm_2100 / 2300, skipped when
//     absent): the debug seek for every pad step (the jump request and its clamped frame), the cut-flag reset at four
//     frames, the PM scene parsed again (the same section pointers as the live record), the units and keys built again
//     from the live scene into an empty copy of the work (the same units type by type and the same keys -- all but the
//     actors and the camera model, which earlier load states make --, the frame header rule), the NPC reload step through its six states, and all 14 custom events: created (kOverlayTask,
//     kFlagOverlay, the record's work / key), run six frames on the real .pak / .bmd files and destroyed.
#include "handgen_pairs.h"

#include "stand_ins.h"

#include "p3fes/game/events2.h"

#include <algorithm>
#include <cstring>
#include <map>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Update_00100980(EEContext&);  // not emitted: served by the stand-ins' file layer
void fn_sub_361980_00361980(EEContext&);  // generated body
void fn_sub_361980_00361980__recomp(EEContext&);  // recompiled
void fn_sub_362390_00362390(EEContext&);  // generated body
void fn_sub_362390_00362390__recomp(EEContext&);  // recompiled
void fn_sub_3625E0_003625e0(EEContext&);  // generated body
void fn_sub_3625E0_003625e0__recomp(EEContext&);  // recompiled
void fn_sub_3628F0_003628f0(EEContext&);  // generated body
void fn_sub_3628F0_003628f0__recomp(EEContext&);  // recompiled
void fn_sub_366EA0_00366ea0(EEContext&);  // generated body
void fn_sub_366EA0_00366ea0__recomp(EEContext&);  // recompiled
void fn_sub_366EB0_00366eb0(EEContext&);  // generated body
void fn_sub_366EB0_00366eb0__recomp(EEContext&);  // recompiled
void fn_sub_366F90_00366f90(EEContext&);  // generated body
void fn_sub_366F90_00366f90__recomp(EEContext&);  // recompiled
void fn_sub_3670F0_003670f0(EEContext&);  // generated body
void fn_sub_3670F0_003670f0__recomp(EEContext&);  // recompiled
void fn_sub_367190_00367190(EEContext&);  // generated body
void fn_sub_367190_00367190__recomp(EEContext&);  // recompiled
void fn_sub_367230_00367230(EEContext&);  // generated body
void fn_sub_367230_00367230__recomp(EEContext&);  // recompiled
void fn_sub_367390_00367390(EEContext&);  // generated body
void fn_sub_367390_00367390__recomp(EEContext&);  // recompiled
void fn_sub_367440_00367440(EEContext&);  // generated body
void fn_sub_367440_00367440__recomp(EEContext&);  // recompiled
void fn_sub_3674B0_003674b0(EEContext&);  // generated body
void fn_sub_3674B0_003674b0__recomp(EEContext&);  // recompiled
void fn_sub_367A20_00367a20(EEContext&);  // generated body
void fn_sub_367A20_00367a20__recomp(EEContext&);  // recompiled
void fn_sub_367CB0_00367cb0(EEContext&);  // generated body
void fn_sub_367CB0_00367cb0__recomp(EEContext&);  // recompiled
void fn_sub_367D70_00367d70(EEContext&);  // generated body
void fn_sub_367D70_00367d70__recomp(EEContext&);  // recompiled
void fn_sub_367E00_00367e00(EEContext&);  // generated body
void fn_sub_367E00_00367e00__recomp(EEContext&);  // recompiled
void fn_sub_367EC0_00367ec0(EEContext&);  // generated body
void fn_sub_367EC0_00367ec0__recomp(EEContext&);  // recompiled
void fn_sub_368020_00368020(EEContext&);  // generated body
void fn_sub_368020_00368020__recomp(EEContext&);  // recompiled
void fn_sub_3680E0_003680e0(EEContext&);  // generated body
void fn_sub_3680E0_003680e0__recomp(EEContext&);  // recompiled
void fn_sub_3682F0_003682f0(EEContext&);  // generated body
void fn_sub_3682F0_003682f0__recomp(EEContext&);  // recompiled
void fn_sub_3683A0_003683a0(EEContext&);  // generated body
void fn_sub_3683A0_003683a0__recomp(EEContext&);  // recompiled
void fn_sub_368440_00368440(EEContext&);  // generated body
void fn_sub_368440_00368440__recomp(EEContext&);  // recompiled
void fn_sub_3684D0_003684d0(EEContext&);  // generated body
void fn_sub_3684D0_003684d0__recomp(EEContext&);  // recompiled
void fn_sub_3685C0_003685c0(EEContext&);  // generated body
void fn_sub_3685C0_003685c0__recomp(EEContext&);  // recompiled
void fn_sub_368680_00368680(EEContext&);  // generated body
void fn_sub_368680_00368680__recomp(EEContext&);  // recompiled
void fn_sub_368710_00368710(EEContext&);  // generated body
void fn_sub_368710_00368710__recomp(EEContext&);  // recompiled
void fn_sub_3687B0_003687b0(EEContext&);  // generated body
void fn_sub_3687B0_003687b0__recomp(EEContext&);  // recompiled
void fn_sub_368830_00368830(EEContext&);  // generated body
void fn_sub_368830_00368830__recomp(EEContext&);  // recompiled
void fn_sub_3688D0_003688d0(EEContext&);  // generated body
void fn_sub_3688D0_003688d0__recomp(EEContext&);  // recompiled
void fn_sub_3689C0_003689c0(EEContext&);  // generated body
void fn_sub_3689C0_003689c0__recomp(EEContext&);  // recompiled
void fn_sub_368A30_00368a30(EEContext&);  // generated body
void fn_sub_368A30_00368a30__recomp(EEContext&);  // recompiled
void fn_sub_368B00_00368b00(EEContext&);  // generated body
void fn_sub_368B00_00368b00__recomp(EEContext&);  // recompiled
void fn_sub_368C10_00368c10(EEContext&);  // generated body
void fn_sub_368C10_00368c10__recomp(EEContext&);  // recompiled
void fn_sub_368CB0_00368cb0(EEContext&);  // generated body
void fn_sub_368CB0_00368cb0__recomp(EEContext&);  // recompiled
void fn_sub_368D70_00368d70(EEContext&);  // generated body
void fn_sub_368D70_00368d70__recomp(EEContext&);  // recompiled
void fn_sub_368F20_00368f20(EEContext&);  // generated body
void fn_sub_368F20_00368f20__recomp(EEContext&);  // recompiled
void fn_sub_369320_00369320(EEContext&);  // generated body
void fn_sub_369320_00369320__recomp(EEContext&);  // recompiled
void fn_sub_3698A0_003698a0(EEContext&);  // generated body
void fn_sub_3698A0_003698a0__recomp(EEContext&);  // recompiled
void fn_sub_369A20_00369a20(EEContext&);  // generated body
void fn_sub_369A20_00369a20__recomp(EEContext&);  // recompiled
void fn_sub_36BE10_0036be10(EEContext&);  // generated body
void fn_sub_36BE10_0036be10__recomp(EEContext&);  // recompiled
void fn_sub_36BE60_0036be60(EEContext&);  // generated body
void fn_sub_36BE60_0036be60__recomp(EEContext&);  // recompiled
void fn_sub_36CC30_0036cc30(EEContext&);  // generated body
void fn_sub_36CC30_0036cc30__recomp(EEContext&);  // recompiled
void fn_sub_36D5F0_0036d5f0(EEContext&);  // generated body
void fn_sub_36D5F0_0036d5f0__recomp(EEContext&);  // recompiled
void fn_sub_36E2F0_0036e2f0(EEContext&);  // generated body
void fn_sub_36E2F0_0036e2f0__recomp(EEContext&);  // recompiled
void fn_sub_36F680_0036f680(EEContext&);  // generated body
void fn_sub_36F680_0036f680__recomp(EEContext&);  // recompiled
void fn_sub_385990_00385990(EEContext&);  // generated body
void fn_sub_385990_00385990__recomp(EEContext&);  // recompiled
void fn_sub_385BD0_00385bd0(EEContext&);  // generated body
void fn_sub_385BD0_00385bd0__recomp(EEContext&);  // recompiled
void fn_sub_385CD0_00385cd0(EEContext&);  // generated body
void fn_sub_385CD0_00385cd0__recomp(EEContext&);  // recompiled
void fn_sub_385E20_00385e20(EEContext&);  // generated body
void fn_sub_385E20_00385e20__recomp(EEContext&);  // recompiled
void fn_sub_385F00_00385f00(EEContext&);  // generated body
void fn_sub_385F00_00385f00__recomp(EEContext&);  // recompiled
void fn_sub_385F90_00385f90(EEContext&);  // generated body
void fn_sub_385F90_00385f90__recomp(EEContext&);  // recompiled
void fn_sub_386060_00386060(EEContext&);  // generated body
void fn_sub_386060_00386060__recomp(EEContext&);  // recompiled
void fn_sub_386130_00386130(EEContext&);  // generated body
void fn_sub_386130_00386130__recomp(EEContext&);  // recompiled
void fn_sub_386230_00386230(EEContext&);  // generated body
void fn_sub_386230_00386230__recomp(EEContext&);  // recompiled
void fn_sub_386310_00386310(EEContext&);  // generated body
void fn_sub_386310_00386310__recomp(EEContext&);  // recompiled
void fn_sub_3863C0_003863c0(EEContext&);  // generated body
void fn_sub_3863C0_003863c0__recomp(EEContext&);  // recompiled
void fn_sub_386430_00386430(EEContext&);  // generated body
void fn_sub_386430_00386430__recomp(EEContext&);  // recompiled
void fn_sub_3865F0_003865f0(EEContext&);  // generated body
void fn_sub_3865F0_003865f0__recomp(EEContext&);  // recompiled
void fn_sub_386680_00386680(EEContext&);  // generated body
void fn_sub_386680_00386680__recomp(EEContext&);  // recompiled
void fn_sub_386780_00386780(EEContext&);  // generated body
void fn_sub_386780_00386780__recomp(EEContext&);  // recompiled
void fn_sub_386860_00386860(EEContext&);  // generated body
void fn_sub_386860_00386860__recomp(EEContext&);  // recompiled
void fn_sub_386940_00386940(EEContext&);  // generated body
void fn_sub_386940_00386940__recomp(EEContext&);  // recompiled
void fn_sub_386A00_00386a00(EEContext&);  // generated body
void fn_sub_386A00_00386a00__recomp(EEContext&);  // recompiled
void fn_sub_386D50_00386d50(EEContext&);  // generated body
void fn_sub_386D50_00386d50__recomp(EEContext&);  // recompiled
void fn_sub_386E50_00386e50(EEContext&);  // generated body
void fn_sub_386E50_00386e50__recomp(EEContext&);  // recompiled
void fn_sub_386F70_00386f70(EEContext&);  // generated body
void fn_sub_386F70_00386f70__recomp(EEContext&);  // recompiled
void fn_sub_3877C0_003877c0(EEContext&);  // generated body
void fn_sub_3877C0_003877c0__recomp(EEContext&);  // recompiled
void fn_sub_388000_00388000(EEContext&);  // generated body
void fn_sub_388000_00388000__recomp(EEContext&);  // recompiled
void fn_sub_388A40_00388a40(EEContext&);  // generated body
void fn_sub_388A40_00388a40__recomp(EEContext&);  // recompiled
void fn_sub_388DF0_00388df0(EEContext&);  // generated body
void fn_sub_388DF0_00388df0__recomp(EEContext&);  // recompiled
void fn_sub_3890E0_003890e0(EEContext&);  // generated body
void fn_sub_3890E0_003890e0__recomp(EEContext&);  // recompiled
void fn_sub_3897F0_003897f0(EEContext&);  // generated body
void fn_sub_3897F0_003897f0__recomp(EEContext&);  // recompiled
void fn_sub_389B50_00389b50(EEContext&);  // generated body
void fn_sub_389B50_00389b50__recomp(EEContext&);  // recompiled
void fn_sub_389D80_00389d80(EEContext&);  // generated body
void fn_sub_389D80_00389d80__recomp(EEContext&);  // recompiled
void fn_sub_38A260_0038a260(EEContext&);  // generated body
void fn_sub_38A260_0038a260__recomp(EEContext&);  // recompiled
void fn_sub_38A7C0_0038a7c0(EEContext&);  // generated body
void fn_sub_38A7C0_0038a7c0__recomp(EEContext&);  // recompiled
void fn_sub_38A920_0038a920(EEContext&);  // generated body
void fn_sub_38A920_0038a920__recomp(EEContext&);  // recompiled
void fn_sub_38AB00_0038ab00(EEContext&);  // generated body
void fn_sub_38AB00_0038ab00__recomp(EEContext&);  // recompiled
void fn_sub_38AF70_0038af70(EEContext&);  // generated body
void fn_sub_38AF70_0038af70__recomp(EEContext&);  // recompiled
void fn_sub_38B140_0038b140(EEContext&);  // generated body
void fn_sub_38B140_0038b140__recomp(EEContext&);  // recompiled
void fn_sub_38B2C0_0038b2c0(EEContext&);  // generated body
void fn_sub_38B2C0_0038b2c0__recomp(EEContext&);  // recompiled
void fn_sub_38B550_0038b550(EEContext&);  // generated body
void fn_sub_38B550_0038b550__recomp(EEContext&);  // recompiled
void fn_sub_38B600_0038b600(EEContext&);  // generated body
void fn_sub_38B600_0038b600__recomp(EEContext&);  // recompiled
void fn_sub_38B6E0_0038b6e0(EEContext&);  // generated body
void fn_sub_38B6E0_0038b6e0__recomp(EEContext&);  // recompiled
void fn_sub_38B960_0038b960(EEContext&);  // generated body
void fn_sub_38B960_0038b960__recomp(EEContext&);  // recompiled
void fn_sub_38BC70_0038bc70(EEContext&);  // generated body
void fn_sub_38BC70_0038bc70__recomp(EEContext&);  // recompiled
void fn_sub_38C540_0038c540(EEContext&);  // generated body
void fn_sub_38C540_0038c540__recomp(EEContext&);  // recompiled
void fn_sub_38C830_0038c830(EEContext&);  // generated body
void fn_sub_38C830_0038c830__recomp(EEContext&);  // recompiled
void fn_sub_38DAD0_0038dad0(EEContext&);  // generated body
void fn_sub_38DAD0_0038dad0__recomp(EEContext&);  // recompiled
void fn_sub_38E660_0038e660(EEContext&);  // generated body
void fn_sub_38E660_0038e660__recomp(EEContext&);  // recompiled
void fn_sub_38E860_0038e860(EEContext&);  // generated body
void fn_sub_38E860_0038e860__recomp(EEContext&);  // recompiled
void fn_sub_3902C0_003902c0(EEContext&);  // generated body
void fn_sub_3902C0_003902c0__recomp(EEContext&);  // recompiled
void fn_sub_3905F0_003905f0(EEContext&);  // generated body
void fn_sub_3905F0_003905f0__recomp(EEContext&);  // recompiled
void fn_sub_390920_00390920(EEContext&);  // generated body
void fn_sub_390920_00390920__recomp(EEContext&);  // recompiled
void fn_sub_390C90_00390c90(EEContext&);  // generated body
void fn_sub_390C90_00390c90__recomp(EEContext&);  // recompiled
void fn_sub_390EF0_00390ef0(EEContext&);  // generated body
void fn_sub_390EF0_00390ef0__recomp(EEContext&);  // recompiled
void fn_sub_391080_00391080(EEContext&);  // generated body
void fn_sub_391080_00391080__recomp(EEContext&);  // recompiled
void fn_sub_3912F0_003912f0(EEContext&);  // generated body
void fn_sub_3912F0_003912f0__recomp(EEContext&);  // recompiled
void fn_sub_3942F0_003942f0(EEContext&);  // generated body
void fn_sub_3942F0_003942f0__recomp(EEContext&);  // recompiled
void fn_sub_395950_00395950(EEContext&);  // generated body
void fn_sub_395950_00395950__recomp(EEContext&);  // recompiled
void fn_sub_395E20_00395e20(EEContext&);  // generated body
void fn_sub_395E20_00395e20__recomp(EEContext&);  // recompiled
void fn_sub_398530_00398530(EEContext&);  // generated body
void fn_sub_398530_00398530__recomp(EEContext&);  // recompiled
void fn_sub_399830_00399830(EEContext&);  // generated body
void fn_sub_399830_00399830__recomp(EEContext&);  // recompiled
void fn_sub_3998B0_003998b0(EEContext&);  // generated body
void fn_sub_3998B0_003998b0__recomp(EEContext&);  // recompiled
void fn_sub_399BE0_00399be0(EEContext&);  // generated body
void fn_sub_399BE0_00399be0__recomp(EEContext&);  // recompiled
void fn_sub_399C40_00399c40(EEContext&);  // generated body
void fn_sub_399C40_00399c40__recomp(EEContext&);  // recompiled
void fn_sub_39A560_0039a560(EEContext&);  // generated body
void fn_sub_39A560_0039a560__recomp(EEContext&);  // recompiled
void fn_sub_39A5C0_0039a5c0(EEContext&);  // generated body
void fn_sub_39A5C0_0039a5c0__recomp(EEContext&);  // recompiled
void fn_sub_39A840_0039a840(EEContext&);  // generated body
void fn_sub_39A840_0039a840__recomp(EEContext&);  // recompiled
void fn_sub_39A8A0_0039a8a0(EEContext&);  // generated body
void fn_sub_39A8A0_0039a8a0__recomp(EEContext&);  // recompiled
void fn_sub_39B830_0039b830(EEContext&);  // generated body
void fn_sub_39B830_0039b830__recomp(EEContext&);  // recompiled
void fn_sub_39B8B0_0039b8b0(EEContext&);  // generated body
void fn_sub_39B8B0_0039b8b0__recomp(EEContext&);  // recompiled
void fn_sub_39B950_0039b950(EEContext&);  // generated body
void fn_sub_39B950_0039b950__recomp(EEContext&);  // recompiled
void fn_sub_39C090_0039c090(EEContext&);  // generated body
void fn_sub_39C090_0039c090__recomp(EEContext&);  // recompiled
void fn_sub_39C0F0_0039c0f0(EEContext&);  // generated body
void fn_sub_39C0F0_0039c0f0__recomp(EEContext&);  // recompiled
void fn_sub_39C3E0_0039c3e0(EEContext&);  // generated body
void fn_sub_39C3E0_0039c3e0__recomp(EEContext&);  // recompiled
void fn_sub_39C440_0039c440(EEContext&);  // generated body
void fn_sub_39C440_0039c440__recomp(EEContext&);  // recompiled
void fn_sub_39CD60_0039cd60(EEContext&);  // generated body
void fn_sub_39CD60_0039cd60__recomp(EEContext&);  // recompiled
void fn_sub_39CDC0_0039cdc0(EEContext&);  // generated body
void fn_sub_39CDC0_0039cdc0__recomp(EEContext&);  // recompiled
void fn_sub_39CFB0_0039cfb0(EEContext&);  // generated body
void fn_sub_39CFB0_0039cfb0__recomp(EEContext&);  // recompiled
void fn_sub_39D010_0039d010(EEContext&);  // generated body
void fn_sub_39D010_0039d010__recomp(EEContext&);  // recompiled
void fn_sub_39D190_0039d190(EEContext&);  // generated body
void fn_sub_39D190_0039d190__recomp(EEContext&);  // recompiled
void fn_sub_39D1C0_0039d1c0(EEContext&);  // generated body
void fn_sub_39D1C0_0039d1c0__recomp(EEContext&);  // recompiled
void fn_sub_39D550_0039d550(EEContext&);  // generated body
void fn_sub_39D550_0039d550__recomp(EEContext&);  // recompiled
void fn_sub_39D880_0039d880(EEContext&);  // generated body
void fn_sub_39D880_0039d880__recomp(EEContext&);  // recompiled
void fn_sub_39D8E0_0039d8e0(EEContext&);  // generated body
void fn_sub_39D8E0_0039d8e0__recomp(EEContext&);  // recompiled
void fn_sub_39DB00_0039db00(EEContext&);  // generated body
void fn_sub_39DB00_0039db00__recomp(EEContext&);  // recompiled
void fn_sub_39DB60_0039db60(EEContext&);  // generated body
void fn_sub_39DB60_0039db60__recomp(EEContext&);  // recompiled
void fn_sub_39DD30_0039dd30(EEContext&);  // generated body
void fn_sub_39DD30_0039dd30__recomp(EEContext&);  // recompiled
void fn_sub_39DD90_0039dd90(EEContext&);  // generated body
void fn_sub_39DD90_0039dd90__recomp(EEContext&);  // recompiled
void fn_sub_39E130_0039e130(EEContext&);  // generated body
void fn_sub_39E130_0039e130__recomp(EEContext&);  // recompiled
void fn_sub_39E1B0_0039e1b0(EEContext&);  // generated body
void fn_sub_39E1B0_0039e1b0__recomp(EEContext&);  // recompiled
void fn_sub_39F850_0039f850(EEContext&);  // generated body
void fn_sub_39F850_0039f850__recomp(EEContext&);  // recompiled
void fn_sub_39F950_0039f950(EEContext&);  // generated body
void fn_sub_39F950_0039f950__recomp(EEContext&);  // recompiled
void fn_sub_39FB10_0039fb10(EEContext&);  // generated body
void fn_sub_39FB10_0039fb10__recomp(EEContext&);  // recompiled
void fn_sub_39FBD0_0039fbd0(EEContext&);  // generated body
void fn_sub_39FBD0_0039fbd0__recomp(EEContext&);  // recompiled
void fn_sub_39FFC0_0039ffc0(EEContext&);  // generated body
void fn_sub_39FFC0_0039ffc0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_361980", 0x361980, &recomp_gen::fn_sub_361980_00361980, &recomp_gen::fn_sub_361980_00361980__recomp},
    {"sub_362390", 0x362390, &recomp_gen::fn_sub_362390_00362390, &recomp_gen::fn_sub_362390_00362390__recomp},
    {"sub_3625E0", 0x3625E0, &recomp_gen::fn_sub_3625E0_003625e0, &recomp_gen::fn_sub_3625E0_003625e0__recomp},
    {"sub_3628F0", 0x3628F0, &recomp_gen::fn_sub_3628F0_003628f0, &recomp_gen::fn_sub_3628F0_003628f0__recomp},
    {"sub_366EA0", 0x366EA0, &recomp_gen::fn_sub_366EA0_00366ea0, &recomp_gen::fn_sub_366EA0_00366ea0__recomp},
    {"sub_366EB0", 0x366EB0, &recomp_gen::fn_sub_366EB0_00366eb0, &recomp_gen::fn_sub_366EB0_00366eb0__recomp},
    {"sub_366F90", 0x366F90, &recomp_gen::fn_sub_366F90_00366f90, &recomp_gen::fn_sub_366F90_00366f90__recomp},
    {"sub_3670F0", 0x3670F0, &recomp_gen::fn_sub_3670F0_003670f0, &recomp_gen::fn_sub_3670F0_003670f0__recomp},
    {"sub_367190", 0x367190, &recomp_gen::fn_sub_367190_00367190, &recomp_gen::fn_sub_367190_00367190__recomp},
    {"sub_367230", 0x367230, &recomp_gen::fn_sub_367230_00367230, &recomp_gen::fn_sub_367230_00367230__recomp},
    {"sub_367390", 0x367390, &recomp_gen::fn_sub_367390_00367390, &recomp_gen::fn_sub_367390_00367390__recomp},
    {"sub_367440", 0x367440, &recomp_gen::fn_sub_367440_00367440, &recomp_gen::fn_sub_367440_00367440__recomp},
    {"sub_3674B0", 0x3674B0, &recomp_gen::fn_sub_3674B0_003674b0, &recomp_gen::fn_sub_3674B0_003674b0__recomp},
    {"sub_367A20", 0x367A20, &recomp_gen::fn_sub_367A20_00367a20, &recomp_gen::fn_sub_367A20_00367a20__recomp},
    {"sub_367CB0", 0x367CB0, &recomp_gen::fn_sub_367CB0_00367cb0, &recomp_gen::fn_sub_367CB0_00367cb0__recomp},
    {"sub_367D70", 0x367D70, &recomp_gen::fn_sub_367D70_00367d70, &recomp_gen::fn_sub_367D70_00367d70__recomp},
    {"sub_367E00", 0x367E00, &recomp_gen::fn_sub_367E00_00367e00, &recomp_gen::fn_sub_367E00_00367e00__recomp},
    {"sub_367EC0", 0x367EC0, &recomp_gen::fn_sub_367EC0_00367ec0, &recomp_gen::fn_sub_367EC0_00367ec0__recomp},
    {"sub_368020", 0x368020, &recomp_gen::fn_sub_368020_00368020, &recomp_gen::fn_sub_368020_00368020__recomp},
    {"sub_3680E0", 0x3680E0, &recomp_gen::fn_sub_3680E0_003680e0, &recomp_gen::fn_sub_3680E0_003680e0__recomp},
    {"sub_3682F0", 0x3682F0, &recomp_gen::fn_sub_3682F0_003682f0, &recomp_gen::fn_sub_3682F0_003682f0__recomp},
    {"sub_3683A0", 0x3683A0, &recomp_gen::fn_sub_3683A0_003683a0, &recomp_gen::fn_sub_3683A0_003683a0__recomp},
    {"sub_368440", 0x368440, &recomp_gen::fn_sub_368440_00368440, &recomp_gen::fn_sub_368440_00368440__recomp},
    {"sub_3684D0", 0x3684D0, &recomp_gen::fn_sub_3684D0_003684d0, &recomp_gen::fn_sub_3684D0_003684d0__recomp},
    {"sub_3685C0", 0x3685C0, &recomp_gen::fn_sub_3685C0_003685c0, &recomp_gen::fn_sub_3685C0_003685c0__recomp},
    {"sub_368680", 0x368680, &recomp_gen::fn_sub_368680_00368680, &recomp_gen::fn_sub_368680_00368680__recomp},
    {"sub_368710", 0x368710, &recomp_gen::fn_sub_368710_00368710, &recomp_gen::fn_sub_368710_00368710__recomp},
    {"sub_3687B0", 0x3687B0, &recomp_gen::fn_sub_3687B0_003687b0, &recomp_gen::fn_sub_3687B0_003687b0__recomp},
    {"sub_368830", 0x368830, &recomp_gen::fn_sub_368830_00368830, &recomp_gen::fn_sub_368830_00368830__recomp},
    {"sub_3688D0", 0x3688D0, &recomp_gen::fn_sub_3688D0_003688d0, &recomp_gen::fn_sub_3688D0_003688d0__recomp},
    {"sub_3689C0", 0x3689C0, &recomp_gen::fn_sub_3689C0_003689c0, &recomp_gen::fn_sub_3689C0_003689c0__recomp},
    {"sub_368A30", 0x368A30, &recomp_gen::fn_sub_368A30_00368a30, &recomp_gen::fn_sub_368A30_00368a30__recomp},
    {"sub_368B00", 0x368B00, &recomp_gen::fn_sub_368B00_00368b00, &recomp_gen::fn_sub_368B00_00368b00__recomp},
    {"sub_368C10", 0x368C10, &recomp_gen::fn_sub_368C10_00368c10, &recomp_gen::fn_sub_368C10_00368c10__recomp},
    {"sub_368CB0", 0x368CB0, &recomp_gen::fn_sub_368CB0_00368cb0, &recomp_gen::fn_sub_368CB0_00368cb0__recomp},
    {"sub_368D70", 0x368D70, &recomp_gen::fn_sub_368D70_00368d70, &recomp_gen::fn_sub_368D70_00368d70__recomp},
    {"sub_368F20", 0x368F20, &recomp_gen::fn_sub_368F20_00368f20, &recomp_gen::fn_sub_368F20_00368f20__recomp},
    {"sub_369320", 0x369320, &recomp_gen::fn_sub_369320_00369320, &recomp_gen::fn_sub_369320_00369320__recomp},
    {"sub_3698A0", 0x3698A0, &recomp_gen::fn_sub_3698A0_003698a0, &recomp_gen::fn_sub_3698A0_003698a0__recomp},
    {"sub_369A20", 0x369A20, &recomp_gen::fn_sub_369A20_00369a20, &recomp_gen::fn_sub_369A20_00369a20__recomp},
    {"sub_36BE10", 0x36BE10, &recomp_gen::fn_sub_36BE10_0036be10, &recomp_gen::fn_sub_36BE10_0036be10__recomp},
    {"sub_36BE60", 0x36BE60, &recomp_gen::fn_sub_36BE60_0036be60, &recomp_gen::fn_sub_36BE60_0036be60__recomp},
    {"sub_36CC30", 0x36CC30, &recomp_gen::fn_sub_36CC30_0036cc30, &recomp_gen::fn_sub_36CC30_0036cc30__recomp},
    {"sub_36D5F0", 0x36D5F0, &recomp_gen::fn_sub_36D5F0_0036d5f0, &recomp_gen::fn_sub_36D5F0_0036d5f0__recomp},
    {"sub_36E2F0", 0x36E2F0, &recomp_gen::fn_sub_36E2F0_0036e2f0, &recomp_gen::fn_sub_36E2F0_0036e2f0__recomp},
    {"sub_36F680", 0x36F680, &recomp_gen::fn_sub_36F680_0036f680, &recomp_gen::fn_sub_36F680_0036f680__recomp},
    {"sub_385990", 0x385990, &recomp_gen::fn_sub_385990_00385990, &recomp_gen::fn_sub_385990_00385990__recomp},
    {"sub_385BD0", 0x385BD0, &recomp_gen::fn_sub_385BD0_00385bd0, &recomp_gen::fn_sub_385BD0_00385bd0__recomp},
    {"sub_385CD0", 0x385CD0, &recomp_gen::fn_sub_385CD0_00385cd0, &recomp_gen::fn_sub_385CD0_00385cd0__recomp},
    {"sub_385E20", 0x385E20, &recomp_gen::fn_sub_385E20_00385e20, &recomp_gen::fn_sub_385E20_00385e20__recomp},
    {"sub_385F00", 0x385F00, &recomp_gen::fn_sub_385F00_00385f00, &recomp_gen::fn_sub_385F00_00385f00__recomp},
    {"sub_385F90", 0x385F90, &recomp_gen::fn_sub_385F90_00385f90, &recomp_gen::fn_sub_385F90_00385f90__recomp},
    {"sub_386060", 0x386060, &recomp_gen::fn_sub_386060_00386060, &recomp_gen::fn_sub_386060_00386060__recomp},
    {"sub_386130", 0x386130, &recomp_gen::fn_sub_386130_00386130, &recomp_gen::fn_sub_386130_00386130__recomp},
    {"sub_386230", 0x386230, &recomp_gen::fn_sub_386230_00386230, &recomp_gen::fn_sub_386230_00386230__recomp},
    {"sub_386310", 0x386310, &recomp_gen::fn_sub_386310_00386310, &recomp_gen::fn_sub_386310_00386310__recomp},
    {"sub_3863C0", 0x3863C0, &recomp_gen::fn_sub_3863C0_003863c0, &recomp_gen::fn_sub_3863C0_003863c0__recomp},
    {"sub_386430", 0x386430, &recomp_gen::fn_sub_386430_00386430, &recomp_gen::fn_sub_386430_00386430__recomp},
    {"sub_3865F0", 0x3865F0, &recomp_gen::fn_sub_3865F0_003865f0, &recomp_gen::fn_sub_3865F0_003865f0__recomp},
    {"sub_386680", 0x386680, &recomp_gen::fn_sub_386680_00386680, &recomp_gen::fn_sub_386680_00386680__recomp},
    {"sub_386780", 0x386780, &recomp_gen::fn_sub_386780_00386780, &recomp_gen::fn_sub_386780_00386780__recomp},
    {"sub_386860", 0x386860, &recomp_gen::fn_sub_386860_00386860, &recomp_gen::fn_sub_386860_00386860__recomp},
    {"sub_386940", 0x386940, &recomp_gen::fn_sub_386940_00386940, &recomp_gen::fn_sub_386940_00386940__recomp},
    {"sub_386A00", 0x386A00, &recomp_gen::fn_sub_386A00_00386a00, &recomp_gen::fn_sub_386A00_00386a00__recomp},
    {"sub_386D50", 0x386D50, &recomp_gen::fn_sub_386D50_00386d50, &recomp_gen::fn_sub_386D50_00386d50__recomp},
    {"sub_386E50", 0x386E50, &recomp_gen::fn_sub_386E50_00386e50, &recomp_gen::fn_sub_386E50_00386e50__recomp},
    {"sub_386F70", 0x386F70, &recomp_gen::fn_sub_386F70_00386f70, &recomp_gen::fn_sub_386F70_00386f70__recomp},
    {"sub_3877C0", 0x3877C0, &recomp_gen::fn_sub_3877C0_003877c0, &recomp_gen::fn_sub_3877C0_003877c0__recomp},
    {"sub_388000", 0x388000, &recomp_gen::fn_sub_388000_00388000, &recomp_gen::fn_sub_388000_00388000__recomp},
    {"sub_388A40", 0x388A40, &recomp_gen::fn_sub_388A40_00388a40, &recomp_gen::fn_sub_388A40_00388a40__recomp},
    {"sub_388DF0", 0x388DF0, &recomp_gen::fn_sub_388DF0_00388df0, &recomp_gen::fn_sub_388DF0_00388df0__recomp},
    {"sub_3890E0", 0x3890E0, &recomp_gen::fn_sub_3890E0_003890e0, &recomp_gen::fn_sub_3890E0_003890e0__recomp},
    {"sub_3897F0", 0x3897F0, &recomp_gen::fn_sub_3897F0_003897f0, &recomp_gen::fn_sub_3897F0_003897f0__recomp},
    {"sub_389B50", 0x389B50, &recomp_gen::fn_sub_389B50_00389b50, &recomp_gen::fn_sub_389B50_00389b50__recomp},
    {"sub_389D80", 0x389D80, &recomp_gen::fn_sub_389D80_00389d80, &recomp_gen::fn_sub_389D80_00389d80__recomp},
    {"sub_38A260", 0x38A260, &recomp_gen::fn_sub_38A260_0038a260, &recomp_gen::fn_sub_38A260_0038a260__recomp},
    {"sub_38A7C0", 0x38A7C0, &recomp_gen::fn_sub_38A7C0_0038a7c0, &recomp_gen::fn_sub_38A7C0_0038a7c0__recomp},
    {"sub_38A920", 0x38A920, &recomp_gen::fn_sub_38A920_0038a920, &recomp_gen::fn_sub_38A920_0038a920__recomp},
    {"sub_38AB00", 0x38AB00, &recomp_gen::fn_sub_38AB00_0038ab00, &recomp_gen::fn_sub_38AB00_0038ab00__recomp},
    {"sub_38AF70", 0x38AF70, &recomp_gen::fn_sub_38AF70_0038af70, &recomp_gen::fn_sub_38AF70_0038af70__recomp},
    {"sub_38B140", 0x38B140, &recomp_gen::fn_sub_38B140_0038b140, &recomp_gen::fn_sub_38B140_0038b140__recomp},
    {"sub_38B2C0", 0x38B2C0, &recomp_gen::fn_sub_38B2C0_0038b2c0, &recomp_gen::fn_sub_38B2C0_0038b2c0__recomp},
    {"sub_38B550", 0x38B550, &recomp_gen::fn_sub_38B550_0038b550, &recomp_gen::fn_sub_38B550_0038b550__recomp},
    {"sub_38B600", 0x38B600, &recomp_gen::fn_sub_38B600_0038b600, &recomp_gen::fn_sub_38B600_0038b600__recomp},
    {"sub_38B6E0", 0x38B6E0, &recomp_gen::fn_sub_38B6E0_0038b6e0, &recomp_gen::fn_sub_38B6E0_0038b6e0__recomp},
    {"sub_38B960", 0x38B960, &recomp_gen::fn_sub_38B960_0038b960, &recomp_gen::fn_sub_38B960_0038b960__recomp},
    {"sub_38BC70", 0x38BC70, &recomp_gen::fn_sub_38BC70_0038bc70, &recomp_gen::fn_sub_38BC70_0038bc70__recomp},
    {"sub_38C540", 0x38C540, &recomp_gen::fn_sub_38C540_0038c540, &recomp_gen::fn_sub_38C540_0038c540__recomp},
    {"sub_38C830", 0x38C830, &recomp_gen::fn_sub_38C830_0038c830, &recomp_gen::fn_sub_38C830_0038c830__recomp},
    {"sub_38DAD0", 0x38DAD0, &recomp_gen::fn_sub_38DAD0_0038dad0, &recomp_gen::fn_sub_38DAD0_0038dad0__recomp},
    {"sub_38E660", 0x38E660, &recomp_gen::fn_sub_38E660_0038e660, &recomp_gen::fn_sub_38E660_0038e660__recomp},
    {"sub_38E860", 0x38E860, &recomp_gen::fn_sub_38E860_0038e860, &recomp_gen::fn_sub_38E860_0038e860__recomp},
    {"sub_3902C0", 0x3902C0, &recomp_gen::fn_sub_3902C0_003902c0, &recomp_gen::fn_sub_3902C0_003902c0__recomp},
    {"sub_3905F0", 0x3905F0, &recomp_gen::fn_sub_3905F0_003905f0, &recomp_gen::fn_sub_3905F0_003905f0__recomp},
    {"sub_390920", 0x390920, &recomp_gen::fn_sub_390920_00390920, &recomp_gen::fn_sub_390920_00390920__recomp},
    {"sub_390C90", 0x390C90, &recomp_gen::fn_sub_390C90_00390c90, &recomp_gen::fn_sub_390C90_00390c90__recomp},
    {"sub_390EF0", 0x390EF0, &recomp_gen::fn_sub_390EF0_00390ef0, &recomp_gen::fn_sub_390EF0_00390ef0__recomp},
    {"sub_391080", 0x391080, &recomp_gen::fn_sub_391080_00391080, &recomp_gen::fn_sub_391080_00391080__recomp},
    {"sub_3912F0", 0x3912F0, &recomp_gen::fn_sub_3912F0_003912f0, &recomp_gen::fn_sub_3912F0_003912f0__recomp},
    {"sub_3942F0", 0x3942F0, &recomp_gen::fn_sub_3942F0_003942f0, &recomp_gen::fn_sub_3942F0_003942f0__recomp},
    {"sub_395950", 0x395950, &recomp_gen::fn_sub_395950_00395950, &recomp_gen::fn_sub_395950_00395950__recomp},
    {"sub_395E20", 0x395E20, &recomp_gen::fn_sub_395E20_00395e20, &recomp_gen::fn_sub_395E20_00395e20__recomp},
    {"sub_398530", 0x398530, &recomp_gen::fn_sub_398530_00398530, &recomp_gen::fn_sub_398530_00398530__recomp},
    {"sub_399830", 0x399830, &recomp_gen::fn_sub_399830_00399830, &recomp_gen::fn_sub_399830_00399830__recomp},
    {"sub_3998B0", 0x3998B0, &recomp_gen::fn_sub_3998B0_003998b0, &recomp_gen::fn_sub_3998B0_003998b0__recomp},
    {"sub_399BE0", 0x399BE0, &recomp_gen::fn_sub_399BE0_00399be0, &recomp_gen::fn_sub_399BE0_00399be0__recomp},
    {"sub_399C40", 0x399C40, &recomp_gen::fn_sub_399C40_00399c40, &recomp_gen::fn_sub_399C40_00399c40__recomp},
    {"sub_39A560", 0x39A560, &recomp_gen::fn_sub_39A560_0039a560, &recomp_gen::fn_sub_39A560_0039a560__recomp},
    {"sub_39A5C0", 0x39A5C0, &recomp_gen::fn_sub_39A5C0_0039a5c0, &recomp_gen::fn_sub_39A5C0_0039a5c0__recomp},
    {"sub_39A840", 0x39A840, &recomp_gen::fn_sub_39A840_0039a840, &recomp_gen::fn_sub_39A840_0039a840__recomp},
    {"sub_39A8A0", 0x39A8A0, &recomp_gen::fn_sub_39A8A0_0039a8a0, &recomp_gen::fn_sub_39A8A0_0039a8a0__recomp},
    {"sub_39B830", 0x39B830, &recomp_gen::fn_sub_39B830_0039b830, &recomp_gen::fn_sub_39B830_0039b830__recomp},
    {"sub_39B8B0", 0x39B8B0, &recomp_gen::fn_sub_39B8B0_0039b8b0, &recomp_gen::fn_sub_39B8B0_0039b8b0__recomp},
    {"sub_39B950", 0x39B950, &recomp_gen::fn_sub_39B950_0039b950, &recomp_gen::fn_sub_39B950_0039b950__recomp},
    {"sub_39C090", 0x39C090, &recomp_gen::fn_sub_39C090_0039c090, &recomp_gen::fn_sub_39C090_0039c090__recomp},
    {"sub_39C0F0", 0x39C0F0, &recomp_gen::fn_sub_39C0F0_0039c0f0, &recomp_gen::fn_sub_39C0F0_0039c0f0__recomp},
    {"sub_39C3E0", 0x39C3E0, &recomp_gen::fn_sub_39C3E0_0039c3e0, &recomp_gen::fn_sub_39C3E0_0039c3e0__recomp},
    {"sub_39C440", 0x39C440, &recomp_gen::fn_sub_39C440_0039c440, &recomp_gen::fn_sub_39C440_0039c440__recomp},
    {"sub_39CD60", 0x39CD60, &recomp_gen::fn_sub_39CD60_0039cd60, &recomp_gen::fn_sub_39CD60_0039cd60__recomp},
    {"sub_39CDC0", 0x39CDC0, &recomp_gen::fn_sub_39CDC0_0039cdc0, &recomp_gen::fn_sub_39CDC0_0039cdc0__recomp},
    {"sub_39CFB0", 0x39CFB0, &recomp_gen::fn_sub_39CFB0_0039cfb0, &recomp_gen::fn_sub_39CFB0_0039cfb0__recomp},
    {"sub_39D010", 0x39D010, &recomp_gen::fn_sub_39D010_0039d010, &recomp_gen::fn_sub_39D010_0039d010__recomp},
    {"sub_39D190", 0x39D190, &recomp_gen::fn_sub_39D190_0039d190, &recomp_gen::fn_sub_39D190_0039d190__recomp},
    {"sub_39D1C0", 0x39D1C0, &recomp_gen::fn_sub_39D1C0_0039d1c0, &recomp_gen::fn_sub_39D1C0_0039d1c0__recomp},
    {"sub_39D550", 0x39D550, &recomp_gen::fn_sub_39D550_0039d550, &recomp_gen::fn_sub_39D550_0039d550__recomp},
    {"sub_39D880", 0x39D880, &recomp_gen::fn_sub_39D880_0039d880, &recomp_gen::fn_sub_39D880_0039d880__recomp},
    {"sub_39D8E0", 0x39D8E0, &recomp_gen::fn_sub_39D8E0_0039d8e0, &recomp_gen::fn_sub_39D8E0_0039d8e0__recomp},
    {"sub_39DB00", 0x39DB00, &recomp_gen::fn_sub_39DB00_0039db00, &recomp_gen::fn_sub_39DB00_0039db00__recomp},
    {"sub_39DB60", 0x39DB60, &recomp_gen::fn_sub_39DB60_0039db60, &recomp_gen::fn_sub_39DB60_0039db60__recomp},
    {"sub_39DD30", 0x39DD30, &recomp_gen::fn_sub_39DD30_0039dd30, &recomp_gen::fn_sub_39DD30_0039dd30__recomp},
    {"sub_39DD90", 0x39DD90, &recomp_gen::fn_sub_39DD90_0039dd90, &recomp_gen::fn_sub_39DD90_0039dd90__recomp},
    {"sub_39E130", 0x39E130, &recomp_gen::fn_sub_39E130_0039e130, &recomp_gen::fn_sub_39E130_0039e130__recomp},
    {"sub_39E1B0", 0x39E1B0, &recomp_gen::fn_sub_39E1B0_0039e1b0, &recomp_gen::fn_sub_39E1B0_0039e1b0__recomp},
    {"sub_39F850", 0x39F850, &recomp_gen::fn_sub_39F850_0039f850, &recomp_gen::fn_sub_39F850_0039f850__recomp},
    {"sub_39F950", 0x39F950, &recomp_gen::fn_sub_39F950_0039f950, &recomp_gen::fn_sub_39F950_0039f950__recomp},
    {"sub_39FB10", 0x39FB10, &recomp_gen::fn_sub_39FB10_0039fb10, &recomp_gen::fn_sub_39FB10_0039fb10__recomp},
    {"sub_39FBD0", 0x39FBD0, &recomp_gen::fn_sub_39FBD0_0039fbd0, &recomp_gen::fn_sub_39FBD0_0039fbd0__recomp},
    {"sub_39FFC0", 0x39FFC0, &recomp_gen::fn_sub_39FFC0_0039ffc0, &recomp_gen::fn_sub_39FFC0_0039ffc0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(events2): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// ===== The slice's own worlds: built editor records, documented rules, and the live event of the dorm route =====
namespace {

namespace rg = p3fes::recomp_gen;
namespace ev = p3fes::game::evt;
namespace ev2 = p3fes::game::evt2;

u32 rd32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 rd16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
u8 rd8(Machine& m, u32 va) { return *m.at(va); }
void wr32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wr16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// Every function the slice's bodies can reach (directly, or through callees this test library emits or that are
// hand-written) that this library does not emit -- 90, from the callee lists of the pseudocode reference; printf, the
// H_Cdvd requests and the heap stand in through install_standard: a recorder each, so the pairs run past them and
// compare every call's arguments, $ra and entry check point.
struct Callee {
    u32 va;
    const char* name;
};
const Callee kRecorded[] = {
    {0x1050E0u, "sub_1050E0"}, {0x109F60u, "sub_109F60"}, {0x10A370u, "sub_10A370"}, {0x10C1A0u, "sub_10C1A0"},
    {0x10C3A0u, "sub_10C3A0"}, {0x176FB0u, "sub_176FB0"}, {0x17AE50u, "sub_17AE50"}, {0x17AF20u, "sub_17AF20"},
    {0x17AFD0u, "sub_17AFD0"}, {0x17B070u, "sub_17B070"}, {0x17B100u, "sub_17B100"}, {0x1A0430u, "sub_1A0430"},
    {0x1A0D00u, "sub_1A0D00"}, {0x1A0D40u, "sub_1A0D40"}, {0x1A0D80u, "sub_1A0D80"}, {0x1A1150u, "sub_1A1150"},
    {0x1A1190u, "sub_1A1190"}, {0x1A11D0u, "sub_1A11D0"}, {0x1A3AE0u, "sub_1A3AE0"}, {0x1A3BF0u, "sub_1A3BF0"},
    {0x1A3DC0u, "sub_1A3DC0"}, {0x1A41B0u, "sub_1A41B0"}, {0x1A42F0u, "sub_1A42F0"}, {0x1A4510u, "sub_1A4510"},
    {0x1A7710u, "sub_1A7710"}, {0x1E2370u, "sub_1E2370"}, {0x316E00u, "sub_316E00"}, {0x316F70u, "sub_316F70"},
    {0x359380u, "sub_359380"}, {0x37CF50u, "sub_37CF50"}, {0x3A2090u, "sub_3A2090"}, {0x3A2A30u, "sub_3A2A30"},
    {0x3A2D80u, "itfMesMngInitialize"}, {0x3A30C0u, "itfMesMngRequestMessage"}, {0x3A3420u, "sub_3A3420"},
    {0x3A37C0u, "sub_3A37C0"}, {0x3A4010u, "sub_3A4010"}, {0x3A4990u, "itfMesMngChangeWindowType"},
    {0x3A4B90u, "sub_3A4B90"}, {0x3B5550u, "sub_3B5550"}, {0x3B55B0u, "sub_3B55B0"}, {0x3B5CF0u, "sub_3B5CF0"},
    {0x3B5D00u, "sub_3B5D00"}, {0x3B5DF0u, "sub_3B5DF0"}, {0x3B5F70u, "sub_3B5F70"}, {0x3B6270u, "sub_3B6270"},
    {0x3B7090u, "sub_3B7090"}, {0x3B7460u, "sub_3B7460"}, {0x3B78B0u, "sub_3B78B0"}, {0x3B79A0u, "sub_3B79A0"},
    {0x3B7AC0u, "sub_3B7AC0"}, {0x3B8310u, "sub_3B8310"}, {0x3B83A0u, "sub_3B83A0"}, {0x3B83D0u, "sub_3B83D0"},
    {0x3B89F0u, "sub_3B89F0"}, {0x3B91C0u, "sub_3B91C0"}, {0x3B9320u, "sub_3B9320"}, {0x3B9500u, "sub_3B9500"},
    {0x3B9550u, "sub_3B9550"}, {0x3B95A0u, "sub_3B95A0"}, {0x3BB010u, "sub_3BB010"}, {0x3BB1D0u, "sub_3BB1D0"},
    {0x3BB280u, "sub_3BB280"}, {0x3BB340u, "sub_3BB340"}, {0x3BB450u, "sub_3BB450"}, {0x3BB9B0u, "sub_3BB9B0"},
    {0x3BBAA0u, "sub_3BBAA0"}, {0x3BBC90u, "sub_3BBC90"}, {0x3BC730u, "sub_3BC730"}, {0x3BC8F0u, "sub_3BC8F0"},
    {0x3BDA60u, "sub_3BDA60"}, {0x3BDBA0u, "sub_3BDBA0"}, {0x3BEB70u, "sub_3BEB70"}, {0x3BECA0u, "sub_3BECA0"},
    {0x3BEE80u, "sub_3BEE80"}, {0x3C77A0u, "sub_3C77A0"}, {0x3C7B90u, "sub_3C7B90"}, {0x3C7BC0u, "sub_3C7BC0"},
    {0x3C7C20u, "sub_3C7C20"}, {0x3C7C90u, "sub_3C7C90"}, {0x3C94E0u, "sub_3C94E0"}, {0x3C9790u, "sub_3C9790"},
    {0x491EA0u, "sub_491EA0"}, {0x4B78B0u, "sub_4B78B0"}, {0x4C0240u, "sub_4C0240"}, {0x4C0370u, "sub_4C0370"},
    {0x51DF58u, "sceSkSsSESQ_Control"}, {0x51E028u, "sceSkSsSESQ_Status"}, {0x52E038u, "cos"}, {0x52E328u, "sin"},
};

// `keep`: heap blocks an earlier pair of the same sequence left allocated (reserved again, so a run of several frames
// keeps its records and loaded files instead of handing their addresses out a second time).
WorldSetup event_world(u32 model = 0, std::map<u32, u32> keep = {}) {
    return [model, keep](StandInWorld& w) {
        install_standard(w);
        for (const auto& [start, size] : keep) w.heap.reserve(start, size);
        for (const Callee& c : kRecorded) w.si.install_recorder(c.va, c.name, 0);
        if (model != 0) {
            w.si.install_recorder(0x3B5D10u, "sub_3B5D10", model);  // the model lookup answers with a record
            w.si.install_recorder(0x3B5D00u, "sub_3B5D00", model);  // the stage lookup too
        }
    };
}

Machine* machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        write_rw_slots(*mm);
        return mm;
    }();
    return m;
}

#define NEED_MACHINE()                                    \
    Machine* mp = machine();                              \
    if (!mp) {                                            \
        MESSAGE("SKIP: no ELF at " << elf_path());        \
        return;                                           \
    }                                                     \
    Machine& m = *mp

// An editor world: the work at W (kSelf, a menu stack of depth 2), one unit of `type` at U with `n` keys
// (U + 0x100 + 0x60 * i, frames 10 * i), the editor showing that unit with the cursor on key `sel`.
constexpr u32 W = kWorld;
constexpr u32 U = kWorld + 0x1000u;
void build_editor(Machine& m, u32 type, int n, int sel, std::mt19937& rng) {
    std::memset(m.at(W), 0, ev::work::kSize);
    wr32(m, W + ev::work::kSelf, W);
    wr32(m, W + ev::work::kMenuDepth, 2);
    wr32(m, W + ev::work::kMenuId, 5);
    std::memset(m.at(U), 0, ev::unit::kSize);
    wr32(m, U + ev::unit::kType, type);
    wr32(m, U + ev::unit::kName, 0xFFFFFFFFu);
    u32 prev = 0;
    for (int i = 0; i < n; ++i) {
        const u32 k = U + 0x100u + 0x60u * static_cast<u32>(i);
        std::memset(m.at(k), 0, ev::key::kSize);
        wr16(m, k + ev::key::kFrame, static_cast<u16>(10 * i));
        wr32(m, k + ev::key::kName, 0xFFFFFFFFu);
        wr32(m, k + ev::key::kOwnerType, type);
        wr32(m, k + ev::key::kPrev, prev);
        if (prev) wr32(m, prev + ev::key::kNext, k);
        else wr32(m, U + ev::unit::kKeyHead, k);
        prev = k;
    }
    wr32(m, U + ev::unit::kKeyTail, prev);
    wr32(m, U + ev::unit::kKeyCount, static_cast<u32>(n));
    wr32(m, W + ev::work::kEdUnit, U);
    // the selected key is the (scroll + index)-th: split `sel` between the two
    const int scroll = sel / 2;
    wr32(m, W + ev::work::kEdKeyScroll, static_cast<u32>(scroll));
    wr32(m, W + ev::work::kEdKeyIndex, static_cast<u32>(sel - scroll));
    wr32(m, W + ev2::work::kEdValue, rng());
    for (int i = 0; i < 12; ++i) wr32(m, W + ev2::work::kEdParams + 4 * i, rng());
    for (int i = 0; i < 4; ++i) wr16(m, W + ev2::work::kEdCondition + 2 * i, static_cast<u16>(rng()));
}
u32 key_at(int i) { return U + 0x100u + 0x60u * static_cast<u32>(i); }

// One setter's documented copy: key + `koff` (`width` bytes) = the low bytes of work + `woff`.
struct Copy {
    s32 koff;
    int width;
    s32 woff;
};
struct Setter {
    const char* name;
    Fn hand, recomp;
    u32 type;  // the unit type the setter needs (0: any)
    std::vector<Copy> copies;
};

constexpr s32 P(int i) { return ev2::work::kEdParams + 4 * i; }

// The live event's work in a snapshot: the record that points at itself with plausible event numbers and a task.
u32 find_work(Machine& m) {
    for (u32 a = 0x100000u; a + ev::work::kSize < 0x1C00000u; a += 16) {
        if (rd32(m, a) != a) continue;
        const u32 major = rd32(m, a + ev::work::kMajor), minor = rd32(m, a + ev::work::kMinor);
        if (major == 0 || major >= 1000 || minor >= 1000 || rd32(m, a + ev::work::kTask) == 0) continue;
        return a;
    }
    return 0;
}
std::vector<u32> units_of(Machine& m, u32 w) {
    std::vector<u32> out;
    for (u32 un = rd32(m, w + ev::work::kUnitHead); un != 0 && out.size() < 400; un = rd32(m, un + ev::unit::kNext)) out.push_back(un);
    return out;
}
std::map<u32, std::pair<int, int>> census(Machine& m, u32 w) {  // unit type -> {units, keys}
    std::map<u32, std::pair<int, int>> c;
    for (u32 un : units_of(m, w)) {
        auto& e = c[rd32(m, un + ev::unit::kType)];
        ++e.first;
        e.second += static_cast<int>(rd32(m, un + ev::unit::kKeyCount));
    }
    return c;
}

}  // namespace

TEST_CASE("game(events2): the editor's key setters copy the edit fields into the selected key") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE2E2001u};
    // read from the instructions (pseudocode reference + handgen bodies) and checked here on both bodies
    const std::vector<Setter> setters = {
        {"sub_3670F0", rg::fn_sub_3670F0_003670f0, rg::fn_sub_3670F0_003670f0__recomp, 0, {{20, 4, ev2::work::kEdValue}}},
        {"sub_367190", rg::fn_sub_367190_00367190, rg::fn_sub_367190_00367190__recomp, 0, {{20, 4, P(1)}, {24, 2, P(2)}}},
        {"sub_367390", rg::fn_sub_367390_00367390, rg::fn_sub_367390_00367390__recomp, 0,
         {{8, 2, ev2::work::kEdCondition}, {10, 2, ev2::work::kEdCondition + 2}, {12, 2, ev2::work::kEdCondition + 4},
          {14, 2, ev2::work::kEdCondition + 6}}},
        {"sub_367D70", rg::fn_sub_367D70_00367d70, rg::fn_sub_367D70_00367d70__recomp, 0, {{21, 1, P(0)}, {20, 1, P(1)}}},
        {"sub_367E00", rg::fn_sub_367E00_00367e00, rg::fn_sub_367E00_00367e00__recomp, 0,
         {{28, 2, P(0)}, {30, 2, P(1)}, {32, 1, P(2)}, {20, 2, P(3)}, {22, 2, P(4)}, {24, 2, P(5)}, {26, 2, P(6)}, {34, 1, P(7)}}},
        {"sub_368020", rg::fn_sub_368020_00368020, rg::fn_sub_368020_00368020__recomp, 0,
         {{16, 1, P(0)}, {17, 1, P(1)}, {18, 1, P(2)}, {19, 1, P(3)}, {24, 2, P(4)}, {26, 2, P(5)}, {28, 2, P(6)}, {30, 2, P(7)}}},
        {"sub_3682F0", rg::fn_sub_3682F0_003682f0, rg::fn_sub_3682F0_003682f0__recomp, 0,
         {{16, 2, P(0)}, {18, 2, P(1)}, {20, 2, P(2)}, {22, 2, P(3)}, {24, 2, P(4)}, {26, 2, P(5)}}},
        {"sub_3683A0", rg::fn_sub_3683A0_003683a0, rg::fn_sub_3683A0_003683a0__recomp, 0,
         {{20, 1, P(0)}, {21, 1, P(1)}, {22, 1, P(2)}, {24, 4, P(3)}}},
        {"sub_368440", rg::fn_sub_368440_00368440, rg::fn_sub_368440_00368440__recomp, 0, {{16, 2, P(0)}, {18, 2, P(1)}}},
        {"sub_368680", rg::fn_sub_368680_00368680, rg::fn_sub_368680_00368680__recomp, 0, {{16, 2, P(0)}, {18, 2, P(1)}}},
        {"sub_368710", rg::fn_sub_368710_00368710, rg::fn_sub_368710_00368710__recomp, 33, {{48, 1, P(0)}}},
        {"sub_3687B0", rg::fn_sub_3687B0_003687b0, rg::fn_sub_3687B0_003687b0__recomp, 0, {{20, 2, P(0)}}},
        {"sub_368830", rg::fn_sub_368830_00368830, rg::fn_sub_368830_00368830__recomp, 0,
         {{20, 1, P(0)}, {21, 1, P(1)}, {22, 2, P(2)}, {24, 2, P(3)}, {26, 2, P(4)}}},
        {"sub_368C10", rg::fn_sub_368C10_00368c10, rg::fn_sub_368C10_00368c10__recomp, 0,
         {{16, 1, P(0)}, {17, 1, P(1)}, {18, 1, P(2)}, {19, 1, P(3)}}},
        {"sub_366EB0", rg::fn_sub_366EB0_00366eb0, rg::fn_sub_366EB0_00366eb0__recomp, 0,
         {{20, 4, ev2::work::kEdValue}, {32, 2, P(0)}, {34, 1, P(1)}, {35, 1, P(2)}, {36, 1, P(3)}, {37, 1, P(4)}, {38, 2, P(5)},
          {40, 2, P(6)}, {42, 2, P(7)}}},
        {"sub_368B00 kind 4", rg::fn_sub_368B00_00368b00, rg::fn_sub_368B00_00368b00__recomp, 1,
         {{40, 1, P(8)}, {41, 1, P(9)}, {42, 1, P(10)}, {43, 1, P(11)}}},
    };
    int pairs = 0, checked = 0;
    for (const Setter& s : setters) {
        for (int round = 0; round < 12; ++round) {
            const int n = 1 + static_cast<int>(rng() % 6);
            const int sel = static_cast<int>(rng() % n);
            build_editor(m, s.type ? s.type : 1 + rng() % 50, n, sel, rng);
            if (std::string(s.name) == "sub_368B00 kind 4") *m.at(key_at(sel) + 16) = 4;
            const int depth = static_cast<int>(rd32(m, W + ev::work::kMenuDepth));
            run_pair_si(m, s.hand, s.recomp, {0, 5, sx(W), 0}, rng(), s.name, hw, event_world());
            ++pairs;
            INFO(s.name << " sel " << sel << " of " << n);
            const u32 k = key_at(sel);
            for (const Copy& c : s.copies) {
                const u32 want = rd32(m, W + static_cast<u32>(c.woff));
                const u32 got = c.width == 4 ? rd32(m, k + c.koff) : c.width == 2 ? rd16(m, k + c.koff) : rd8(m, k + c.koff);
                const u32 mask = c.width == 4 ? 0xFFFFFFFFu : c.width == 2 ? 0xFFFFu : 0xFFu;
                CHECK(got == (want & mask));
                ++checked;
            }
            // every setter pops the editor's menu (sub_36F640)
            CHECK(static_cast<int>(rd32(m, W + ev::work::kMenuDepth)) == depth - 1);
            // and touches no other key
            for (int i = 0; i < n; ++i)
                if (i != sel) CHECK(rd16(m, key_at(i) + ev::key::kFrame) == 10 * i);
        }
    }
    MESSAGE("setters: " << pairs << " pairs, " << checked << " fields checked");
}

TEST_CASE("game(events2): deleting a key and the random-jump pick follow their rules") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE2E2002u};
    int pairs = 0;
    // sub_361980 [evtEdDeleteKey]: the selected key leaves the list, the count drops by one, the cursor moves up
    for (int round = 0; round < 40; ++round) {
        const int n = 1 + static_cast<int>(rng() % 6);
        const int sel = static_cast<int>(rng() % n);
        const u32 types[] = {1, 4, 10, 18, 20, 21, 26, 3, 36, 48};
        build_editor(m, types[rng() % 10], n, sel, rng);
        const u32 victim = key_at(sel);
        const int idx = static_cast<int>(rd32(m, W + ev::work::kEdKeyIndex)), scr = static_cast<int>(rd32(m, W + ev::work::kEdKeyScroll));
        run_pair_si(m, rg::fn_sub_361980_00361980, rg::fn_sub_361980_00361980__recomp, {sx(W), 0, 0, 0}, rng(), "sub_361980", hw, event_world());
        ++pairs;
        INFO("delete " << sel << " of " << n);
        CHECK(rd32(m, U + ev::unit::kKeyCount) == static_cast<u32>(n - 1));
        int seen = 0;
        for (u32 k = rd32(m, U + ev::unit::kKeyHead); k != 0 && seen < 16; k = rd32(m, k + ev::key::kNext), ++seen) CHECK(k != victim);
        CHECK(seen == n - 1);
        // the cursor: scroll first when it is non-zero, else the index (never below 0)
        const int idx2 = static_cast<int>(rd32(m, W + ev::work::kEdKeyIndex)), scr2 = static_cast<int>(rd32(m, W + ev::work::kEdKeyScroll));
        if (scr > 0 && idx <= 0) CHECK((scr2 == scr - 1 && idx2 == idx));
        else if (idx > 0) CHECK((idx2 == idx - 1 && scr2 == scr));
    }
    // sub_388DF0 [evtRandomJumpPick]: the draw (logged by printf as "random value=%d") falls into the range of the
    // returned index; weights 0 never win the draw
    for (int round = 0; round < 60; ++round) {
        const u32 n = 1 + rng() % 10;
        const u32 weights = kWorld + 0x3000u;
        std::vector<u32> wv(n);
        for (u32 i = 0; i < n; ++i) wv[i] = (rng() % 3 == 0) ? 0 : 1 + rng() % 40;
        for (u32 i = 0; i < n; ++i) wr32(m, weights + 4 * i, wv[i]);
        const SiPair p = run_pair_si(m, rg::fn_sub_388DF0_00388df0, rg::fn_sub_388DF0_00388df0__recomp, {n, sx(weights), 0, 0}, rng(),
                                     "sub_388DF0", hw, event_world());
        ++pairs;
        int r = -1;
        for (const StandInCall& c : p.recomp->si.log)
            if (c.text.rfind("random value=", 0) == 0) r = std::atoi(c.text.c_str() + 13);
        REQUIRE(r >= 0);
        const u32 got = static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]);
        u32 lo = 0, want = 0xFFFFFFFFu;
        for (u32 i = 0; i < n && want == 0xFFFFFFFFu; ++i) {
            if (wv[i] && static_cast<u32>(r) >= lo && static_cast<u32>(r) <= lo + wv[i] - 1) want = i;
            lo += wv[i];
        }
        if (want == 0xFFFFFFFFu) {  // past the total: the heaviest (first of equals)
            u32 best = 0;
            want = 0;
            for (u32 i = 0; i < n; ++i)
                if (wv[i] > best) best = wv[i], want = i;
        }
        INFO("draw " << r << " n " << n);
        CHECK(got == want);
    }
    MESSAGE("rules: " << pairs << " pairs");
}

TEST_CASE("game(events2): the live event of the dorm route -- seek, cut flags, the PM parse and rebuild, custom events") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE2E2003u};
    int pairs = 0, snapshots = 0;
    std::size_t calls = 0;
    for (const char* dir : {"events_dorm_2100", "events_dorm_2300"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << " is not there (a --reference-mode dorm run to that vblank makes it)");
            continue;
        }
        ++snapshots;
        auto fresh = [&] {
            copy_from_snapshot(m, snap, 0, EEMemory::kMainRamSize);
            write_rw_slots(m);
        };
        fresh();
        const u32 w = find_work(m);
        REQUIRE(w != 0);
        CHECK(rd32(m, w + ev::work::kMajor) == 401);
        const s32 frame = static_cast<s32>(rd32(m, w + ev::work::kFrame));
        const s32 count = static_cast<s32>(rd32(m, w + ev2::work::kFrameCount));
        const s32 start = static_cast<s32>(rd32(m, w + ev::work::kStartFrame));
        // the frame header rule of sub_3912F0: kFrame stays in [0, kFrameCount - 1]
        CHECK(count > 0);
        CHECK(frame >= 0);
        CHECK(frame <= count - 1);
        const u32 scene = rd32(m, w + ev::work::kScene);
        REQUIRE(scene != 0);

        // sub_362390 [evtDebugSeek]: each pad bit's step, the target clamped to [0, count - 1], requested as a jump
        struct Pad {
            u16 w952, w94c, flags;
            int step;  // 0x7FFF: back to the start frame
        };
        const Pad pads[] = {{0x2000, 0, 0, 1},   {0x8000, 0, 0, -1}, {0x0004, 0, 0, -10}, {0x0008, 0, 0, 10},
                            {0x0008, 0x2000, 0, 100}, {0x0004, 0x8000, 0, -100}, {0, 0, 0x100, 0x7FFF}, {0, 0, 0, 0}};
        for (const Pad& pd : pads) {
            fresh();
            wr16(m, 0x7E0952u, pd.w952);
            wr16(m, 0x7E094Cu, pd.w94c);
            wr16(m, 0x7E094Eu, pd.flags);
            wr32(m, w + ev::work::kJumpRequest, 0);
            calls += run_pair_si(m, rg::fn_sub_362390_00362390, rg::fn_sub_362390_00362390__recomp, {sx(w), 0, 0, 0}, rng(), "sub_362390 live",
                                 hw, event_world()).recomp->si.log.size();
            ++pairs;
            // the cascade of sub_362390 (no message units are consulted: L1 / R1 are not pressed here)
            const bool r_ = (pd.w952 & 0x2000) != 0, l_ = (pd.w952 & 0x8000) != 0, u_ = (pd.w952 & 4) != 0, d_ = (pd.w952 & 8) != 0;
            int step = 0;
            if ((pd.w94c & 0x2000) && d_ && frame > 0) step = 100;
            else if ((pd.w94c & 0x8000) && u_ && frame > 0) step = -100;
            else if (l_ && frame > 0) step = -1;
            else if (r_ && frame < count - 1) step = 1;
            else if (u_) step = -10;
            else if (d_) step = 10;
            else if ((pd.flags & 0x100) && frame != start) step = start - frame;
            INFO("pad " << pd.w952 << "/" << pd.w94c << "/" << pd.flags << " frame " << frame);
            if (step == 0) {
                CHECK(rd32(m, w + ev::work::kJumpRequest) == 0);
            } else {
                const s32 want = std::clamp(frame + step, 0, count - 1);
                CHECK(rd32(m, w + ev::work::kJumpRequest) == 1);
                CHECK(static_cast<s32>(rd32(m, w + ev::work::kJumpFrame)) == want);
            }
        }
        // sub_38C830 [evtApplyMessageCutFlags] at the start, current, next and last frames
        for (s32 f : {0, frame, frame + 1, count - 1}) {
            fresh();
            calls += run_pair_si(m, rg::fn_sub_38C830_0038c830, rg::fn_sub_38C830_0038c830__recomp, {sx(w), sx(static_cast<u32>(f)), 0, 0}, rng(),
                                 "sub_38C830 live", hw, event_world()).recomp->si.log.size();
            ++pairs;
        }
        // sub_3942F0 [pmSceneParse]: parsing the live scene's PM1 / PM2 / PM3 again into a fresh record gives the
        // live record's section pointers back
        {
            fresh();
            const u32 rec = kWorld + 0x4000u, slot = kWorld + 0x6000u;
            std::memset(m.at(rec), 0, 0x200);
            std::memset(m.at(slot), 0, 0x100);
            HwCheck h2 = hw;
            h2.gpr_in[GPR_T0] = sx(rd32(m, scene + ev2::scene::kPm3));
            calls += run_pair_si(m, rg::fn_sub_3942F0_003942f0, rg::fn_sub_3942F0_003942f0__recomp,
                                 {sx(slot), sx(rec), sx(rd32(m, scene + ev2::scene::kPm1)), sx(rd32(m, scene + ev2::scene::kPm2))}, rng(),
                                 "sub_3942F0 live", h2, event_world()).recomp->si.log.size();
            ++pairs;
            int same = 0;
            for (s32 off = ev2::scene::kPm1; off <= 272; off += 4) {
                INFO("scene +" << off);
                CHECK(rd32(m, rec + off) == rd32(m, scene + off));
                ++same;
            }
            CHECK(same == (272 - 16) / 4 + 1);
            CHECK(rd32(m, rec + ev2::scene::kFrameHeader) != 0);
            CHECK(rd32(m, rec + ev2::scene::kRefTable) != 0);  // the 508-byte table, allocated
        }
        // sub_3912F0 [evtSetGameData]: the live scene built again into a copy of the work whose unit list is empty
        // yields the same units (type by type) and the same keys
        {
            fresh();
            const auto live = census(m, w);
            const u32 f = kWorld + 0x8000u;
            std::memcpy(m.at(f), m.at(w), ev::work::kSize);
            wr32(m, f + ev::work::kSelf, f);
            wr32(m, f + ev::work::kUnitHead, 0);
            wr32(m, f + ev::work::kUnitTail, 0);
            wr32(m, f + ev::work::kUnitCount, 0);
            wr32(m, f + ev::work::kNameCount, 0);
            calls += run_pair_si(m, rg::fn_sub_3912F0_003912f0, rg::fn_sub_3912F0_003912f0__recomp, {sx(scene), sx(f), 0, 0}, rng(),
                                 "sub_3912F0 live", hw, event_world()).recomp->si.log.size();
            ++pairs;
            const auto built = census(m, f);
            CHECK(rd32(m, f + ev::work::kUnitCount) == units_of(m, f).size());
            // the actors (type 1) and the camera model (type 33) are not built here: the earlier load states make
            // them (the NPC models of states 5..7, the event camera), and sub_3912F0 only fills them from the scene
            CHECK(built.count(1) == 0);
            CHECK(built.count(33) == 0);
            for (const auto& [type, e] : live) {
                if (type == 1 || type == 33) continue;
                INFO("unit type " << type);
                CHECK(built.count(type) == 1);
                if (built.count(type)) {
                    CHECK(built.at(type).first == e.first);
                    CHECK(built.at(type).second == e.second);
                }
            }
            CHECK(built.size() + (live.count(1) ? 1 : 0) + (live.count(33) ? 1 : 0) == live.size());
            CHECK(static_cast<s32>(rd32(m, f + ev2::work::kFrameCount)) == count);
            CHECK(static_cast<s32>(rd32(m, f + ev::work::kStartFrame)) == start);
            CHECK(static_cast<s32>(rd32(m, f + ev::work::kFrame)) == std::clamp(start, 0, count - 1));
            CHECK(rd32(m, f + ev::work::kPrevFrame) == 0xFFFFFFFFu);
        }
        // the work-level helpers of the second pass on the live work
        for (const char* name : {"sub_386D50", "sub_3890E0", "sub_3625E0"}) {
            for (const Case& c : kCases) {
                if (std::string(c.name) != name) continue;
                fresh();
                calls += run_pair_si(m, c.hand, c.recomp, {sx(w), 0, 0, 0}, rng(), name, hw, event_world()).recomp->si.log.size();
                ++pairs;
            }
        }
        // sub_36E2F0 [evtStepNpcReload] through its states, one slot with a model id
        for (u32 state = 0; state <= 5; ++state) {
            fresh();
            const u32 process = kWorld + 0xB000u;
            std::memset(m.at(process), 0, 0x100);
            wr32(m, process + 60u, w);
            const u32 npc = w + ev2::work::kNpc;
            std::memset(m.at(npc), 0, 68);
            wr32(m, npc + ev2::npc::kState, state);
            wr32(m, npc + ev2::npc::kCount, 1);
            wr16(m, npc + ev2::npc::kRowKind, 3);
            wr16(m, npc + ev2::npc::kRowModel, state == 2 ? 0x1234 : 0);
            wr32(m, npc + ev2::npc::kReturnStep, 0x36E690u);
            const SiPair p = run_pair_si(m, rg::fn_sub_36E2F0_0036e2f0, rg::fn_sub_36E2F0_0036e2f0__recomp, {sx(process), 0, 0, 0}, rng(),
                                         "sub_36E2F0 live", hw, event_world());
            calls += p.recomp->si.log.size();
            ++pairs;
            INFO("npc state " << state);
            if (state == 5) {  // done: the flag cleared, the saved step returned
                CHECK((rd32(m, w + ev::work::kFlags) & ev::work::kFlag10000) == 0);
                CHECK(static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]) == 0x36E690u);
            } else {
                CHECK(p.hw.recomp.gpr[GPR_V0].u64[0] == 0);
            }
            if (state == 4) CHECK(rd32(m, npc + ev2::npc::kState) == 5);
            if (state == 2) CHECK(rd32(m, npc + ev2::npc::kState) == 3);  // a model id: its load requested
        }
        // the custom events: sub_39E1B0 creates the kind's task under kTask (kOverlayTask, kFlagOverlay), then its
        // update runs a few frames and its destroy frees it
        struct Ce {
            u32 kind;
            const char* update;
            const char* destroy;
        };
        const Ce kinds[] = {{0, "sub_398530", "sub_399830"},  {1, "sub_3998B0", "sub_399BE0"},  {2, "sub_399C40", "sub_39A560"},
                            {3, "sub_39A5C0", "sub_39A840"},  {4, "sub_39A8A0", "sub_39B830"},  {5, "sub_39B950", "sub_39C090"},
                            {6, "sub_39C0F0", "sub_39C3E0"},  {7, "sub_39C440", "sub_39CD60"},  {8, "sub_39CDC0", "sub_39CFB0"},
                            {9, "sub_39D010", "sub_39D190"},  {10, "sub_39D550", "sub_39D880"}, {11, "sub_39D8E0", "sub_39DB00"},
                            {12, "sub_39DB60", "sub_39DD30"}, {13, "sub_39DD90", "sub_39E130"}};
        auto find_case = [&](const char* name) -> const Case* {
            for (const Case& c : kCases)
                if (std::string(c.name) == name) return &c;
            return nullptr;
        };
        std::string ce_states;
        // each kind in play mode (the live flags) and in the editor's mode (kFlagPlayMode cleared: some kinds skip
        // their availability checks there and go straight to their files)
        for (int pass = 0; pass < 2; ++pass)
        for (const Ce& ce : kinds) {
            fresh();
            if (pass == 1) wr32(m, w + ev::work::kFlags, rd32(m, w + ev::work::kFlags) & ~ev::work::kFlagPlayMode);
            if (pass == 1 && ce.kind == 0) ce_states += "  | editor mode:";
            const u32 key = kWorld + 0xC000u;
            std::memset(m.at(key), 0, ev::key::kSize);
            *m.at(key + ev::key::kCmd) = static_cast<u8>(ce.kind);
            wr32(m, key + ev::key::kOwnerType, 41);
            wr32(m, w + ev::work::kOverlayTask, 0);
            const u32 flags0 = rd32(m, w + ev::work::kFlags);
            std::map<u32, u32> keep;  // the sequence's live heap blocks, carried from pair to pair
            {
                const SiPair p = run_pair_si(m, rg::fn_sub_39E1B0_0039e1b0, rg::fn_sub_39E1B0_0039e1b0__recomp, {sx(w), sx(key), 0, 0}, rng(),
                                             "sub_39E1B0 live", hw, event_world());
                calls += p.recomp->si.log.size();
                keep = p.recomp->heap.live();
            }
            ++pairs;
            INFO("custom event kind " << ce.kind);
            const u32 task = rd32(m, w + ev::work::kOverlayTask);
            CHECK(task != 0);
            CHECK(rd32(m, w + ev::work::kFlags) == (flags0 | ev::work::kFlagOverlay));
            if (task == 0) continue;
            const u32 rec = rd32(m, task + 60u);  // the record the update receives through its process
            CHECK(rec != 0);
            if (ce.kind == 0) {
                CHECK(rd32(m, rec + 72) == w);
                CHECK(rd32(m, rec + 76) == key);
            } else if (ce.kind != 4) {
                CHECK(rd32(m, rec + ev2::ce::kWork) == w);
                CHECK(rd32(m, rec + ev2::ce::kKey) == key);
            }
            const Case* up = find_case(ce.update);
            const Case* de = find_case(ce.destroy);
            REQUIRE(up != nullptr);
            REQUIRE(de != nullptr);
            // the update until it reports the end (-1) or 40 frames; the first word is the state for most kinds
            int frames = 0;
            bool ended = false;
            u32 max_state = 0;
            while (frames < 40 && !ended) {
                const SiPair p = run_pair_si(m, up->hand, up->recomp, {sx(task), 0, 0, 0}, rng(), ce.update, hw, event_world(0, keep));
                calls += p.recomp->si.log.size();
                keep = p.recomp->heap.live();
                ++pairs;
                ++frames;
                ended = static_cast<s64>(p.hw.recomp.gpr[GPR_V0].u64[0]) == -1;
                max_state = std::max(max_state, rd32(m, rec));
                // the frame's file service (the retail cdvd task's H_Cdvd_Update: completes pending requests)
                const SiPair u = run_pair_si(m, rg::fn_H_Cdvd_Update_00100980, rg::fn_H_Cdvd_Update_00100980, {0, 0, 0, 0}, rng(),
                                             "H_Cdvd_Update", hw, event_world(0, keep));
                keep = u.recomp->heap.live();
            }
            ce_states += " " + std::to_string(ce.kind) + ":" + std::to_string(frames) + (ended ? "/end" : "/run") + "/s" + std::to_string(max_state);
            calls += run_pair_si(m, de->hand, de->recomp, {sx(task), 0, 0, 0}, rng(), ce.destroy, hw, event_world(0, keep)).recomp->si.log.size();
            ++pairs;
        }
        MESSAGE(std::string(dir) << " custom events, kind:frames/end-or-running/highest state:" << ce_states);
    }
    MESSAGE("live event: " << snapshots << " snapshots, " << pairs << " pairs, " << calls << " stand-in calls compared");
}

#else

TEST_CASE("game(events2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
