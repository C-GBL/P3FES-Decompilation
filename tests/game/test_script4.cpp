// Pair tests for slice script4 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window and the bus
// log; the pairs that reach the heap, printf or the file layer run inside identical stand-in worlds (stand_ins.h) whose
// call logs must match too.
//
// On top of the random worlds:
//   * COMM 146 [scrCommand_SHAKE_STOP] dispatched by CodeFunc_Comm on a live script task of the dorm snapshot;
//   * the screen-shake request through its frames, effMiscRand against its generator rule, the class 31 allocator and
//     slots, the fade kinds 2 / 3 / 4 / 10 on the battle snapshot b_5800 (the light pairs of gBtl, every battle unit and
//     the unit filter against a host model, the camera's field of view), class 30 kind 1's strip, the VU0 matrix helpers
//     against host maths;
//   * the message manager on the dorm snapshot's live slots (tag parameters, argument strings, the per-frame panel step
//     and draw, the text rebuild, the slot release), itfPanel create / move and the window layouts, the event-message
//     sequence on an open MT_Msg slot and the event-busy test.
// Every random draw of this file is its own statement (the shared harness is outside this rule): two draws inside one
// argument list are evaluated in different orders by MSVC and clang-cl.
#include "handgen_pairs.h"

#include "p3fes/game/script4_fx.h"
#include "p3fes/game/script4_msg.h"
#include "stand_ins.h"

#include <bit>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

namespace p3fes::recomp_gen {
void fn_CodeFunc_Comm_0035cf20(EEContext&);          // the COMM opcode (hand-written, script_vm)
void fn_CodeFunc_Comm_0035cf20__recomp(EEContext&);  // recompiled
void fn_sub_3296A0_003296a0(EEContext&);  // generated body
void fn_sub_3296A0_003296a0__recomp(EEContext&);  // recompiled
void fn_sub_350070_00350070(EEContext&);  // generated body
void fn_sub_350070_00350070__recomp(EEContext&);  // recompiled
void fn_sub_350080_00350080(EEContext&);  // generated body
void fn_sub_350080_00350080__recomp(EEContext&);  // recompiled
void fn_sub_3500A0_003500a0(EEContext&);  // generated body
void fn_sub_3500A0_003500a0__recomp(EEContext&);  // recompiled
void fn_sub_3500E0_003500e0(EEContext&);  // generated body
void fn_sub_3500E0_003500e0__recomp(EEContext&);  // recompiled
void fn_sub_350110_00350110(EEContext&);  // generated body
void fn_sub_350110_00350110__recomp(EEContext&);  // recompiled
void fn_sub_350200_00350200(EEContext&);  // generated body
void fn_sub_350200_00350200__recomp(EEContext&);  // recompiled
void fn_sub_3503E0_003503e0(EEContext&);  // generated body
void fn_sub_3503E0_003503e0__recomp(EEContext&);  // recompiled
void fn_sub_350500_00350500(EEContext&);  // generated body
void fn_sub_350500_00350500__recomp(EEContext&);  // recompiled
void fn_sub_3505A0_003505a0(EEContext&);  // generated body
void fn_sub_3505A0_003505a0__recomp(EEContext&);  // recompiled
void fn_sub_3505B0_003505b0(EEContext&);  // generated body
void fn_sub_3505B0_003505b0__recomp(EEContext&);  // recompiled
void fn_sub_351280_00351280(EEContext&);  // generated body
void fn_sub_351280_00351280__recomp(EEContext&);  // recompiled
void fn_sub_351BB0_00351bb0(EEContext&);  // generated body
void fn_sub_351BB0_00351bb0__recomp(EEContext&);  // recompiled
void fn_sub_351CA0_00351ca0(EEContext&);  // generated body
void fn_sub_351CA0_00351ca0__recomp(EEContext&);  // recompiled
void fn_sub_351D20_00351d20(EEContext&);  // generated body
void fn_sub_351D20_00351d20__recomp(EEContext&);  // recompiled
void fn_sub_351E20_00351e20(EEContext&);  // generated body
void fn_sub_351E20_00351e20__recomp(EEContext&);  // recompiled
void fn_sub_352800_00352800(EEContext&);  // generated body
void fn_sub_352800_00352800__recomp(EEContext&);  // recompiled
void fn_sub_352910_00352910(EEContext&);  // generated body
void fn_sub_352910_00352910__recomp(EEContext&);  // recompiled
void fn_sub_352980_00352980(EEContext&);  // generated body
void fn_sub_352980_00352980__recomp(EEContext&);  // recompiled
void fn_sub_352A80_00352a80(EEContext&);  // generated body
void fn_sub_352A80_00352a80__recomp(EEContext&);  // recompiled
void fn_sub_352AD0_00352ad0(EEContext&);  // generated body
void fn_sub_352AD0_00352ad0__recomp(EEContext&);  // recompiled
void fn_sub_352B30_00352b30(EEContext&);  // generated body
void fn_sub_352B30_00352b30__recomp(EEContext&);  // recompiled
void fn_sub_352B80_00352b80(EEContext&);  // generated body
void fn_sub_352B80_00352b80__recomp(EEContext&);  // recompiled
void fn_sub_352C10_00352c10(EEContext&);  // generated body
void fn_sub_352C10_00352c10__recomp(EEContext&);  // recompiled
void fn_sub_352C20_00352c20(EEContext&);  // generated body
void fn_sub_352C20_00352c20__recomp(EEContext&);  // recompiled
void fn_sub_352C30_00352c30(EEContext&);  // generated body
void fn_sub_352C30_00352c30__recomp(EEContext&);  // recompiled
void fn_sub_352C50_00352c50(EEContext&);  // generated body
void fn_sub_352C50_00352c50__recomp(EEContext&);  // recompiled
void fn_sub_352C70_00352c70(EEContext&);  // generated body
void fn_sub_352C70_00352c70__recomp(EEContext&);  // recompiled
void fn_sub_352E10_00352e10(EEContext&);  // generated body
void fn_sub_352E10_00352e10__recomp(EEContext&);  // recompiled
void fn_sub_352EB0_00352eb0(EEContext&);  // generated body
void fn_sub_352EB0_00352eb0__recomp(EEContext&);  // recompiled
void fn_sub_352F20_00352f20(EEContext&);  // generated body
void fn_sub_352F20_00352f20__recomp(EEContext&);  // recompiled
void fn_sub_353960_00353960(EEContext&);  // generated body
void fn_sub_353960_00353960__recomp(EEContext&);  // recompiled
void fn_sub_353990_00353990(EEContext&);  // generated body
void fn_sub_353990_00353990__recomp(EEContext&);  // recompiled
void fn_sub_3539C0_003539c0(EEContext&);  // generated body
void fn_sub_3539C0_003539c0__recomp(EEContext&);  // recompiled
void fn_nullsub_112_00354290(EEContext&);  // generated body
void fn_nullsub_112_00354290__recomp(EEContext&);  // recompiled
void fn_sub_3542A0_003542a0(EEContext&);  // generated body
void fn_sub_3542A0_003542a0__recomp(EEContext&);  // recompiled
void fn_sub_354B20_00354b20(EEContext&);  // generated body
void fn_sub_354B20_00354b20__recomp(EEContext&);  // recompiled
void fn_sub_354B50_00354b50(EEContext&);  // generated body
void fn_sub_354B50_00354b50__recomp(EEContext&);  // recompiled
void fn_sub_354B80_00354b80(EEContext&);  // generated body
void fn_sub_354B80_00354b80__recomp(EEContext&);  // recompiled
void fn_sub_355670_00355670(EEContext&);  // generated body
void fn_sub_355670_00355670__recomp(EEContext&);  // recompiled
void fn_sub_3556A0_003556a0(EEContext&);  // generated body
void fn_sub_3556A0_003556a0__recomp(EEContext&);  // recompiled
void fn_sub_355DD0_00355dd0(EEContext&);  // generated body
void fn_sub_355DD0_00355dd0__recomp(EEContext&);  // recompiled
void fn_sub_355E70_00355e70(EEContext&);  // generated body
void fn_sub_355E70_00355e70__recomp(EEContext&);  // recompiled
void fn_sub_355EE0_00355ee0(EEContext&);  // generated body
void fn_sub_355EE0_00355ee0__recomp(EEContext&);  // recompiled
void fn_sub_355F30_00355f30(EEContext&);  // generated body
void fn_sub_355F30_00355f30__recomp(EEContext&);  // recompiled
void fn_sub_356B00_00356b00(EEContext&);  // generated body
void fn_sub_356B00_00356b00__recomp(EEContext&);  // recompiled
void fn_sub_356BA0_00356ba0(EEContext&);  // generated body
void fn_sub_356BA0_00356ba0__recomp(EEContext&);  // recompiled
void fn_sub_356C20_00356c20(EEContext&);  // generated body
void fn_sub_356C20_00356c20__recomp(EEContext&);  // recompiled
void fn_sub_356FD0_00356fd0(EEContext&);  // generated body
void fn_sub_356FD0_00356fd0__recomp(EEContext&);  // recompiled
void fn_sub_3570B0_003570b0(EEContext&);  // generated body
void fn_sub_3570B0_003570b0__recomp(EEContext&);  // recompiled
void fn_sub_357170_00357170(EEContext&);  // generated body
void fn_sub_357170_00357170__recomp(EEContext&);  // recompiled
void fn_sub_357450_00357450(EEContext&);  // generated body
void fn_sub_357450_00357450__recomp(EEContext&);  // recompiled
void fn_sub_357470_00357470(EEContext&);  // generated body
void fn_sub_357470_00357470__recomp(EEContext&);  // recompiled
void fn_nullsub_113_00357540(EEContext&);  // generated body
void fn_nullsub_113_00357540__recomp(EEContext&);  // recompiled
void fn_sub_357770_00357770(EEContext&);  // generated body
void fn_sub_357770_00357770__recomp(EEContext&);  // recompiled
void fn_sub_357830_00357830(EEContext&);  // generated body
void fn_sub_357830_00357830__recomp(EEContext&);  // recompiled
void fn_sub_357930_00357930(EEContext&);  // generated body
void fn_sub_357930_00357930__recomp(EEContext&);  // recompiled
void fn_sub_3579B0_003579b0(EEContext&);  // generated body
void fn_sub_3579B0_003579b0__recomp(EEContext&);  // recompiled
void fn_sub_357BA0_00357ba0(EEContext&);  // generated body
void fn_sub_357BA0_00357ba0__recomp(EEContext&);  // recompiled
void fn_sub_357C10_00357c10(EEContext&);  // generated body
void fn_sub_357C10_00357c10__recomp(EEContext&);  // recompiled
void fn_sub_357C80_00357c80(EEContext&);  // generated body
void fn_sub_357C80_00357c80__recomp(EEContext&);  // recompiled
void fn_sub_357CE0_00357ce0(EEContext&);  // generated body
void fn_sub_357CE0_00357ce0__recomp(EEContext&);  // recompiled
void fn_sub_357D90_00357d90(EEContext&);  // generated body
void fn_sub_357D90_00357d90__recomp(EEContext&);  // recompiled
void fn_sub_357DA0_00357da0(EEContext&);  // generated body
void fn_sub_357DA0_00357da0__recomp(EEContext&);  // recompiled
void fn_sub_357DB0_00357db0(EEContext&);  // generated body
void fn_sub_357DB0_00357db0__recomp(EEContext&);  // recompiled
void fn_sub_357DC0_00357dc0(EEContext&);  // generated body
void fn_sub_357DC0_00357dc0__recomp(EEContext&);  // recompiled
void fn_sub_357DD0_00357dd0(EEContext&);  // generated body
void fn_sub_357DD0_00357dd0__recomp(EEContext&);  // recompiled
void fn_sub_357E00_00357e00(EEContext&);  // generated body
void fn_sub_357E00_00357e00__recomp(EEContext&);  // recompiled
void fn_sub_357E30_00357e30(EEContext&);  // generated body
void fn_sub_357E30_00357e30__recomp(EEContext&);  // recompiled
void fn_sub_357EA0_00357ea0(EEContext&);  // generated body
void fn_sub_357EA0_00357ea0__recomp(EEContext&);  // recompiled
void fn_sub_357FD0_00357fd0(EEContext&);  // generated body
void fn_sub_357FD0_00357fd0__recomp(EEContext&);  // recompiled
void fn_sub_358160_00358160(EEContext&);  // generated body
void fn_sub_358160_00358160__recomp(EEContext&);  // recompiled
void fn_sub_3581F0_003581f0(EEContext&);  // generated body
void fn_sub_3581F0_003581f0__recomp(EEContext&);  // recompiled
void fn_sub_358340_00358340(EEContext&);  // generated body
void fn_sub_358340_00358340__recomp(EEContext&);  // recompiled
void fn_sub_358380_00358380(EEContext&);  // generated body
void fn_sub_358380_00358380__recomp(EEContext&);  // recompiled
void fn_sub_358410_00358410(EEContext&);  // generated body
void fn_sub_358410_00358410__recomp(EEContext&);  // recompiled
void fn_sub_3A0B50_003a0b50(EEContext&);  // generated body
void fn_sub_3A0B50_003a0b50__recomp(EEContext&);  // recompiled
void fn_sub_3A1C00_003a1c00(EEContext&);  // generated body
void fn_sub_3A1C00_003a1c00__recomp(EEContext&);  // recompiled
void fn_sub_3A3530_003a3530(EEContext&);  // generated body
void fn_sub_3A3530_003a3530__recomp(EEContext&);  // recompiled
void fn_sub_3A3680_003a3680(EEContext&);  // generated body
void fn_sub_3A3680_003a3680__recomp(EEContext&);  // recompiled
void fn_sub_3A4A70_003a4a70(EEContext&);  // generated body
void fn_sub_3A4A70_003a4a70__recomp(EEContext&);  // recompiled
void fn_sub_3A4DD0_003a4dd0(EEContext&);  // generated body
void fn_sub_3A4DD0_003a4dd0__recomp(EEContext&);  // recompiled
void fn_sub_3A4EF0_003a4ef0(EEContext&);  // generated body
void fn_sub_3A4EF0_003a4ef0__recomp(EEContext&);  // recompiled
void fn_sub_3A53B0_003a53b0(EEContext&);  // generated body
void fn_sub_3A53B0_003a53b0__recomp(EEContext&);  // recompiled
void fn_sub_3A5570_003a5570(EEContext&);  // generated body
void fn_sub_3A5570_003a5570__recomp(EEContext&);  // recompiled
void fn_sub_3A56F0_003a56f0(EEContext&);  // generated body
void fn_sub_3A56F0_003a56f0__recomp(EEContext&);  // recompiled
void fn_sub_3A5980_003a5980(EEContext&);  // generated body
void fn_sub_3A5980_003a5980__recomp(EEContext&);  // recompiled
void fn_sub_3A5CA0_003a5ca0(EEContext&);  // generated body
void fn_sub_3A5CA0_003a5ca0__recomp(EEContext&);  // recompiled
void fn_sub_3A5EA0_003a5ea0(EEContext&);  // generated body
void fn_sub_3A5EA0_003a5ea0__recomp(EEContext&);  // recompiled
void fn_sub_3A6140_003a6140(EEContext&);  // generated body
void fn_sub_3A6140_003a6140__recomp(EEContext&);  // recompiled
void fn_sub_3A6520_003a6520(EEContext&);  // generated body
void fn_sub_3A6520_003a6520__recomp(EEContext&);  // recompiled
void fn_sub_3A67E0_003a67e0(EEContext&);  // generated body
void fn_sub_3A67E0_003a67e0__recomp(EEContext&);  // recompiled
void fn_sub_3A6CA0_003a6ca0(EEContext&);  // generated body
void fn_sub_3A6CA0_003a6ca0__recomp(EEContext&);  // recompiled
void fn_sub_3A6E30_003a6e30(EEContext&);  // generated body
void fn_sub_3A6E30_003a6e30__recomp(EEContext&);  // recompiled
void fn_itfMesManagerDrawMsg_003a7e90(EEContext&);  // generated body
void fn_itfMesManagerDrawMsg_003a7e90__recomp(EEContext&);  // recompiled
void fn_sub_3A87D0_003a87d0(EEContext&);  // generated body
void fn_sub_3A87D0_003a87d0__recomp(EEContext&);  // recompiled
void fn_sub_3A8B00_003a8b00(EEContext&);  // generated body
void fn_sub_3A8B00_003a8b00__recomp(EEContext&);  // recompiled
void fn_sub_3A8EA0_003a8ea0(EEContext&);  // generated body
void fn_sub_3A8EA0_003a8ea0__recomp(EEContext&);  // recompiled
void fn_sub_3A9ED0_003a9ed0(EEContext&);  // generated body
void fn_sub_3A9ED0_003a9ed0__recomp(EEContext&);  // recompiled
void fn_sub_3AA000_003aa000(EEContext&);  // generated body
void fn_sub_3AA000_003aa000__recomp(EEContext&);  // recompiled
void fn_sub_3AA130_003aa130(EEContext&);  // generated body
void fn_sub_3AA130_003aa130__recomp(EEContext&);  // recompiled
void fn_sub_3AA370_003aa370(EEContext&);  // generated body
void fn_sub_3AA370_003aa370__recomp(EEContext&);  // recompiled
void fn_sub_3AC240_003ac240(EEContext&);  // generated body
void fn_sub_3AC240_003ac240__recomp(EEContext&);  // recompiled
void fn_sub_3AC350_003ac350(EEContext&);  // generated body
void fn_sub_3AC350_003ac350__recomp(EEContext&);  // recompiled
void fn_sub_3AC900_003ac900(EEContext&);  // generated body
void fn_sub_3AC900_003ac900__recomp(EEContext&);  // recompiled
void fn_sub_3AD400_003ad400(EEContext&);  // generated body
void fn_sub_3AD400_003ad400__recomp(EEContext&);  // recompiled
void fn_sub_3AD740_003ad740(EEContext&);  // generated body
void fn_sub_3AD740_003ad740__recomp(EEContext&);  // recompiled
void fn_sub_3CF630_003cf630(EEContext&);  // generated body
void fn_sub_3CF630_003cf630__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_3296A0", 0x3296A0, &recomp_gen::fn_sub_3296A0_003296a0, &recomp_gen::fn_sub_3296A0_003296a0__recomp},
    {"sub_350070", 0x350070, &recomp_gen::fn_sub_350070_00350070, &recomp_gen::fn_sub_350070_00350070__recomp},
    {"sub_350080", 0x350080, &recomp_gen::fn_sub_350080_00350080, &recomp_gen::fn_sub_350080_00350080__recomp},
    {"sub_3500A0", 0x3500A0, &recomp_gen::fn_sub_3500A0_003500a0, &recomp_gen::fn_sub_3500A0_003500a0__recomp},
    {"sub_3500E0", 0x3500E0, &recomp_gen::fn_sub_3500E0_003500e0, &recomp_gen::fn_sub_3500E0_003500e0__recomp},
    {"sub_350110", 0x350110, &recomp_gen::fn_sub_350110_00350110, &recomp_gen::fn_sub_350110_00350110__recomp},
    {"sub_350200", 0x350200, &recomp_gen::fn_sub_350200_00350200, &recomp_gen::fn_sub_350200_00350200__recomp},
    {"sub_3503E0", 0x3503E0, &recomp_gen::fn_sub_3503E0_003503e0, &recomp_gen::fn_sub_3503E0_003503e0__recomp},
    {"sub_350500", 0x350500, &recomp_gen::fn_sub_350500_00350500, &recomp_gen::fn_sub_350500_00350500__recomp},
    {"sub_3505A0", 0x3505A0, &recomp_gen::fn_sub_3505A0_003505a0, &recomp_gen::fn_sub_3505A0_003505a0__recomp},
    {"sub_3505B0", 0x3505B0, &recomp_gen::fn_sub_3505B0_003505b0, &recomp_gen::fn_sub_3505B0_003505b0__recomp},
    {"sub_351280", 0x351280, &recomp_gen::fn_sub_351280_00351280, &recomp_gen::fn_sub_351280_00351280__recomp},
    {"sub_351BB0", 0x351BB0, &recomp_gen::fn_sub_351BB0_00351bb0, &recomp_gen::fn_sub_351BB0_00351bb0__recomp},
    {"sub_351CA0", 0x351CA0, &recomp_gen::fn_sub_351CA0_00351ca0, &recomp_gen::fn_sub_351CA0_00351ca0__recomp},
    {"sub_351D20", 0x351D20, &recomp_gen::fn_sub_351D20_00351d20, &recomp_gen::fn_sub_351D20_00351d20__recomp},
    {"sub_351E20", 0x351E20, &recomp_gen::fn_sub_351E20_00351e20, &recomp_gen::fn_sub_351E20_00351e20__recomp},
    {"sub_352800", 0x352800, &recomp_gen::fn_sub_352800_00352800, &recomp_gen::fn_sub_352800_00352800__recomp},
    {"sub_352910", 0x352910, &recomp_gen::fn_sub_352910_00352910, &recomp_gen::fn_sub_352910_00352910__recomp},
    {"sub_352980", 0x352980, &recomp_gen::fn_sub_352980_00352980, &recomp_gen::fn_sub_352980_00352980__recomp},
    {"sub_352A80", 0x352A80, &recomp_gen::fn_sub_352A80_00352a80, &recomp_gen::fn_sub_352A80_00352a80__recomp},
    {"sub_352AD0", 0x352AD0, &recomp_gen::fn_sub_352AD0_00352ad0, &recomp_gen::fn_sub_352AD0_00352ad0__recomp},
    {"sub_352B30", 0x352B30, &recomp_gen::fn_sub_352B30_00352b30, &recomp_gen::fn_sub_352B30_00352b30__recomp},
    {"sub_352B80", 0x352B80, &recomp_gen::fn_sub_352B80_00352b80, &recomp_gen::fn_sub_352B80_00352b80__recomp},
    {"sub_352C10", 0x352C10, &recomp_gen::fn_sub_352C10_00352c10, &recomp_gen::fn_sub_352C10_00352c10__recomp},
    {"sub_352C20", 0x352C20, &recomp_gen::fn_sub_352C20_00352c20, &recomp_gen::fn_sub_352C20_00352c20__recomp},
    {"sub_352C30", 0x352C30, &recomp_gen::fn_sub_352C30_00352c30, &recomp_gen::fn_sub_352C30_00352c30__recomp},
    {"sub_352C50", 0x352C50, &recomp_gen::fn_sub_352C50_00352c50, &recomp_gen::fn_sub_352C50_00352c50__recomp},
    {"sub_352C70", 0x352C70, &recomp_gen::fn_sub_352C70_00352c70, &recomp_gen::fn_sub_352C70_00352c70__recomp},
    {"sub_352E10", 0x352E10, &recomp_gen::fn_sub_352E10_00352e10, &recomp_gen::fn_sub_352E10_00352e10__recomp},
    {"sub_352EB0", 0x352EB0, &recomp_gen::fn_sub_352EB0_00352eb0, &recomp_gen::fn_sub_352EB0_00352eb0__recomp},
    {"sub_352F20", 0x352F20, &recomp_gen::fn_sub_352F20_00352f20, &recomp_gen::fn_sub_352F20_00352f20__recomp},
    {"sub_353960", 0x353960, &recomp_gen::fn_sub_353960_00353960, &recomp_gen::fn_sub_353960_00353960__recomp},
    {"sub_353990", 0x353990, &recomp_gen::fn_sub_353990_00353990, &recomp_gen::fn_sub_353990_00353990__recomp},
    {"sub_3539C0", 0x3539C0, &recomp_gen::fn_sub_3539C0_003539c0, &recomp_gen::fn_sub_3539C0_003539c0__recomp},
    {"nullsub_112", 0x354290, &recomp_gen::fn_nullsub_112_00354290, &recomp_gen::fn_nullsub_112_00354290__recomp},
    {"sub_3542A0", 0x3542A0, &recomp_gen::fn_sub_3542A0_003542a0, &recomp_gen::fn_sub_3542A0_003542a0__recomp},
    {"sub_354B20", 0x354B20, &recomp_gen::fn_sub_354B20_00354b20, &recomp_gen::fn_sub_354B20_00354b20__recomp},
    {"sub_354B50", 0x354B50, &recomp_gen::fn_sub_354B50_00354b50, &recomp_gen::fn_sub_354B50_00354b50__recomp},
    {"sub_354B80", 0x354B80, &recomp_gen::fn_sub_354B80_00354b80, &recomp_gen::fn_sub_354B80_00354b80__recomp},
    {"sub_355670", 0x355670, &recomp_gen::fn_sub_355670_00355670, &recomp_gen::fn_sub_355670_00355670__recomp},
    {"sub_3556A0", 0x3556A0, &recomp_gen::fn_sub_3556A0_003556a0, &recomp_gen::fn_sub_3556A0_003556a0__recomp},
    {"sub_355DD0", 0x355DD0, &recomp_gen::fn_sub_355DD0_00355dd0, &recomp_gen::fn_sub_355DD0_00355dd0__recomp},
    {"sub_355E70", 0x355E70, &recomp_gen::fn_sub_355E70_00355e70, &recomp_gen::fn_sub_355E70_00355e70__recomp},
    {"sub_355EE0", 0x355EE0, &recomp_gen::fn_sub_355EE0_00355ee0, &recomp_gen::fn_sub_355EE0_00355ee0__recomp},
    {"sub_355F30", 0x355F30, &recomp_gen::fn_sub_355F30_00355f30, &recomp_gen::fn_sub_355F30_00355f30__recomp},
    {"sub_356B00", 0x356B00, &recomp_gen::fn_sub_356B00_00356b00, &recomp_gen::fn_sub_356B00_00356b00__recomp},
    {"sub_356BA0", 0x356BA0, &recomp_gen::fn_sub_356BA0_00356ba0, &recomp_gen::fn_sub_356BA0_00356ba0__recomp},
    {"sub_356C20", 0x356C20, &recomp_gen::fn_sub_356C20_00356c20, &recomp_gen::fn_sub_356C20_00356c20__recomp},
    {"sub_356FD0", 0x356FD0, &recomp_gen::fn_sub_356FD0_00356fd0, &recomp_gen::fn_sub_356FD0_00356fd0__recomp},
    {"sub_3570B0", 0x3570B0, &recomp_gen::fn_sub_3570B0_003570b0, &recomp_gen::fn_sub_3570B0_003570b0__recomp},
    {"sub_357170", 0x357170, &recomp_gen::fn_sub_357170_00357170, &recomp_gen::fn_sub_357170_00357170__recomp},
    {"sub_357450", 0x357450, &recomp_gen::fn_sub_357450_00357450, &recomp_gen::fn_sub_357450_00357450__recomp},
    {"sub_357470", 0x357470, &recomp_gen::fn_sub_357470_00357470, &recomp_gen::fn_sub_357470_00357470__recomp},
    {"nullsub_113", 0x357540, &recomp_gen::fn_nullsub_113_00357540, &recomp_gen::fn_nullsub_113_00357540__recomp},
    {"sub_357770", 0x357770, &recomp_gen::fn_sub_357770_00357770, &recomp_gen::fn_sub_357770_00357770__recomp},
    {"sub_357830", 0x357830, &recomp_gen::fn_sub_357830_00357830, &recomp_gen::fn_sub_357830_00357830__recomp},
    {"sub_357930", 0x357930, &recomp_gen::fn_sub_357930_00357930, &recomp_gen::fn_sub_357930_00357930__recomp},
    {"sub_3579B0", 0x3579B0, &recomp_gen::fn_sub_3579B0_003579b0, &recomp_gen::fn_sub_3579B0_003579b0__recomp},
    {"sub_357BA0", 0x357BA0, &recomp_gen::fn_sub_357BA0_00357ba0, &recomp_gen::fn_sub_357BA0_00357ba0__recomp},
    {"sub_357C10", 0x357C10, &recomp_gen::fn_sub_357C10_00357c10, &recomp_gen::fn_sub_357C10_00357c10__recomp},
    {"sub_357C80", 0x357C80, &recomp_gen::fn_sub_357C80_00357c80, &recomp_gen::fn_sub_357C80_00357c80__recomp},
    {"sub_357CE0", 0x357CE0, &recomp_gen::fn_sub_357CE0_00357ce0, &recomp_gen::fn_sub_357CE0_00357ce0__recomp},
    {"sub_357D90", 0x357D90, &recomp_gen::fn_sub_357D90_00357d90, &recomp_gen::fn_sub_357D90_00357d90__recomp},
    {"sub_357DA0", 0x357DA0, &recomp_gen::fn_sub_357DA0_00357da0, &recomp_gen::fn_sub_357DA0_00357da0__recomp},
    {"sub_357DB0", 0x357DB0, &recomp_gen::fn_sub_357DB0_00357db0, &recomp_gen::fn_sub_357DB0_00357db0__recomp},
    {"sub_357DC0", 0x357DC0, &recomp_gen::fn_sub_357DC0_00357dc0, &recomp_gen::fn_sub_357DC0_00357dc0__recomp},
    {"sub_357DD0", 0x357DD0, &recomp_gen::fn_sub_357DD0_00357dd0, &recomp_gen::fn_sub_357DD0_00357dd0__recomp},
    {"sub_357E00", 0x357E00, &recomp_gen::fn_sub_357E00_00357e00, &recomp_gen::fn_sub_357E00_00357e00__recomp},
    {"sub_357E30", 0x357E30, &recomp_gen::fn_sub_357E30_00357e30, &recomp_gen::fn_sub_357E30_00357e30__recomp},
    {"sub_357EA0", 0x357EA0, &recomp_gen::fn_sub_357EA0_00357ea0, &recomp_gen::fn_sub_357EA0_00357ea0__recomp},
    {"sub_357FD0", 0x357FD0, &recomp_gen::fn_sub_357FD0_00357fd0, &recomp_gen::fn_sub_357FD0_00357fd0__recomp},
    {"sub_358160", 0x358160, &recomp_gen::fn_sub_358160_00358160, &recomp_gen::fn_sub_358160_00358160__recomp},
    {"sub_3581F0", 0x3581F0, &recomp_gen::fn_sub_3581F0_003581f0, &recomp_gen::fn_sub_3581F0_003581f0__recomp},
    {"sub_358340", 0x358340, &recomp_gen::fn_sub_358340_00358340, &recomp_gen::fn_sub_358340_00358340__recomp},
    {"sub_358380", 0x358380, &recomp_gen::fn_sub_358380_00358380, &recomp_gen::fn_sub_358380_00358380__recomp},
    {"sub_358410", 0x358410, &recomp_gen::fn_sub_358410_00358410, &recomp_gen::fn_sub_358410_00358410__recomp},
    {"sub_3A0B50", 0x3A0B50, &recomp_gen::fn_sub_3A0B50_003a0b50, &recomp_gen::fn_sub_3A0B50_003a0b50__recomp},
    {"sub_3A1C00", 0x3A1C00, &recomp_gen::fn_sub_3A1C00_003a1c00, &recomp_gen::fn_sub_3A1C00_003a1c00__recomp},
    {"sub_3A3530", 0x3A3530, &recomp_gen::fn_sub_3A3530_003a3530, &recomp_gen::fn_sub_3A3530_003a3530__recomp},
    {"sub_3A3680", 0x3A3680, &recomp_gen::fn_sub_3A3680_003a3680, &recomp_gen::fn_sub_3A3680_003a3680__recomp},
    {"sub_3A4A70", 0x3A4A70, &recomp_gen::fn_sub_3A4A70_003a4a70, &recomp_gen::fn_sub_3A4A70_003a4a70__recomp},
    {"sub_3A4DD0", 0x3A4DD0, &recomp_gen::fn_sub_3A4DD0_003a4dd0, &recomp_gen::fn_sub_3A4DD0_003a4dd0__recomp},
    {"sub_3A4EF0", 0x3A4EF0, &recomp_gen::fn_sub_3A4EF0_003a4ef0, &recomp_gen::fn_sub_3A4EF0_003a4ef0__recomp},
    {"sub_3A53B0", 0x3A53B0, &recomp_gen::fn_sub_3A53B0_003a53b0, &recomp_gen::fn_sub_3A53B0_003a53b0__recomp},
    {"sub_3A5570", 0x3A5570, &recomp_gen::fn_sub_3A5570_003a5570, &recomp_gen::fn_sub_3A5570_003a5570__recomp},
    {"sub_3A56F0", 0x3A56F0, &recomp_gen::fn_sub_3A56F0_003a56f0, &recomp_gen::fn_sub_3A56F0_003a56f0__recomp},
    {"sub_3A5980", 0x3A5980, &recomp_gen::fn_sub_3A5980_003a5980, &recomp_gen::fn_sub_3A5980_003a5980__recomp},
    {"sub_3A5CA0", 0x3A5CA0, &recomp_gen::fn_sub_3A5CA0_003a5ca0, &recomp_gen::fn_sub_3A5CA0_003a5ca0__recomp},
    {"sub_3A5EA0", 0x3A5EA0, &recomp_gen::fn_sub_3A5EA0_003a5ea0, &recomp_gen::fn_sub_3A5EA0_003a5ea0__recomp},
    {"sub_3A6140", 0x3A6140, &recomp_gen::fn_sub_3A6140_003a6140, &recomp_gen::fn_sub_3A6140_003a6140__recomp},
    {"sub_3A6520", 0x3A6520, &recomp_gen::fn_sub_3A6520_003a6520, &recomp_gen::fn_sub_3A6520_003a6520__recomp},
    {"sub_3A67E0", 0x3A67E0, &recomp_gen::fn_sub_3A67E0_003a67e0, &recomp_gen::fn_sub_3A67E0_003a67e0__recomp},
    {"sub_3A6CA0", 0x3A6CA0, &recomp_gen::fn_sub_3A6CA0_003a6ca0, &recomp_gen::fn_sub_3A6CA0_003a6ca0__recomp},
    {"sub_3A6E30", 0x3A6E30, &recomp_gen::fn_sub_3A6E30_003a6e30, &recomp_gen::fn_sub_3A6E30_003a6e30__recomp},
    {"itfMesManagerDrawMsg", 0x3A7E90, &recomp_gen::fn_itfMesManagerDrawMsg_003a7e90, &recomp_gen::fn_itfMesManagerDrawMsg_003a7e90__recomp},
    {"sub_3A87D0", 0x3A87D0, &recomp_gen::fn_sub_3A87D0_003a87d0, &recomp_gen::fn_sub_3A87D0_003a87d0__recomp},
    {"sub_3A8B00", 0x3A8B00, &recomp_gen::fn_sub_3A8B00_003a8b00, &recomp_gen::fn_sub_3A8B00_003a8b00__recomp},
    {"sub_3A8EA0", 0x3A8EA0, &recomp_gen::fn_sub_3A8EA0_003a8ea0, &recomp_gen::fn_sub_3A8EA0_003a8ea0__recomp},
    {"sub_3A9ED0", 0x3A9ED0, &recomp_gen::fn_sub_3A9ED0_003a9ed0, &recomp_gen::fn_sub_3A9ED0_003a9ed0__recomp},
    {"sub_3AA000", 0x3AA000, &recomp_gen::fn_sub_3AA000_003aa000, &recomp_gen::fn_sub_3AA000_003aa000__recomp},
    {"sub_3AA130", 0x3AA130, &recomp_gen::fn_sub_3AA130_003aa130, &recomp_gen::fn_sub_3AA130_003aa130__recomp},
    {"sub_3AA370", 0x3AA370, &recomp_gen::fn_sub_3AA370_003aa370, &recomp_gen::fn_sub_3AA370_003aa370__recomp},
    {"sub_3AC240", 0x3AC240, &recomp_gen::fn_sub_3AC240_003ac240, &recomp_gen::fn_sub_3AC240_003ac240__recomp},
    {"sub_3AC350", 0x3AC350, &recomp_gen::fn_sub_3AC350_003ac350, &recomp_gen::fn_sub_3AC350_003ac350__recomp},
    {"sub_3AC900", 0x3AC900, &recomp_gen::fn_sub_3AC900_003ac900, &recomp_gen::fn_sub_3AC900_003ac900__recomp},
    {"sub_3AD400", 0x3AD400, &recomp_gen::fn_sub_3AD400_003ad400, &recomp_gen::fn_sub_3AD400_003ad400__recomp},
    {"sub_3AD740", 0x3AD740, &recomp_gen::fn_sub_3AD740_003ad740, &recomp_gen::fn_sub_3AD740_003ad740__recomp},
    {"sub_3CF630", 0x3CF630, &recomp_gen::fn_sub_3CF630_003cf630, &recomp_gen::fn_sub_3CF630_003cf630__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair through two trampolines that (a) set chosen FPRs after the random register file and (b) optionally give
// each body a fresh, identical stand-in world (the heap behind H_Malloc and the RW slots, printf / sprintf, the H_Cdvd
// layer) whose call logs must match; the blocks a chain of pairs allocated stay reserved in the next worlds (g_live).
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    bool persist = false;  // keep each side's world across the pairs of a sequence (heap, file layer)
    std::vector<std::tuple<u32, std::string, u64>> recorders;
};
Tramp g_t;
std::map<u32, u32> g_live;
int g_pairs = 0;
int g_checks = 0;  // documented-rule checks (host side)

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    if (!g_t.persist || !g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        for (const auto& [p, n] : g_live) g_t.world[K]->heap.reserve(p, n);
        install_standard(*g_t.world[K]);
        for (const auto& [va, name, v0] : g_t.recorders) g_t.world[K]->si.install_recorder(va, name, v0);
    }
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case kExtra[] = {
    {"CodeFunc_Comm", 0x35CF20, &recomp_gen::fn_CodeFunc_Comm_0035cf20, &recomp_gen::fn_CodeFunc_Comm_0035cf20__recomp},
};

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    for (const Case& c : kExtra)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = true;
    std::vector<std::tuple<u32, std::string, u64>> recorders;
    bool persist = false;
};

hgp::Run s4_pair(Machine& m, const char* name, const Args& a, u32 seed, const std::string& what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.recorders = o.recorders;
    g_t.persist = o.persist;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what.c_str(), hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) {
        expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
        g_live = g_t.world[1]->heap.live();
    }
    ++g_pairs;
    if (r.stopped) MESSAGE(what << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
const StandIns& log_of() { return g_t.world[1]->si; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
float rf(const Machine& m, u32 va) { return std::bit_cast<float>(r32(m, va)); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float f) { w32(m, va, std::bit_cast<u32>(f)); }
u32 fbits(float f) { return std::bit_cast<u32>(f); }
bool near(float a, float b, float tol) { return std::fabs(a - b) <= tol * (1.0f + std::fabs(b)); }

constexpr u32 kGpReg = 0x7D2CF0u;
constexpr u32 kOut = 0x01F40000u;   // free in every snapshot (stand_ins.h) and in the ELF image
constexpr u32 kGBtlSlot = 0x7CE3ECu;

std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
bool load_snapshot(Machine& m, const char* s, std::vector<u8>* keep = nullptr) {
    std::vector<u8> snap = read_snapshot(s);
    if (snap.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    if (keep) *keep = std::move(snap);
    return true;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(script4): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    // the image as loaded, restored before each function (a stray store through a random pointer could re-aim a
    // function pointer the next body calls through, e.g. the class kind rows or the RW slots)
    const std::vector<u8> image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    int stops = 0, pairs = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        std::memcpy(m->mem.main_ram(), image.data(), image.size());
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
// COMM 146 through the script VM: a live script task of the dorm snapshot runs a COMM 146 instruction
// =====================================================================================================================
TEST_CASE("game(script4): COMM 146 SHAKE_STOP dispatched by CodeFunc_Comm on a live script task") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::vector<u8> snap;
    if (!load_snapshot(m, "dorm_replay_4900", &snap)) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    constexpr u32 kTaskListHead = 0x7CE580u, kCurrentTask = 0x7CE5A8u;
    constexpr u32 kTaskPc = 0x18, kTaskSp = 0x1C, kTaskInsn = 0xBC;  // ScrTask (script_vm.h / script3.h)
    std::vector<u32> tasks;
    for (u32 t = r32(m, kTaskListHead); t != 0 && tasks.size() < 16; t = r32(m, t + 0xEC)) tasks.push_back(t);
    REQUIRE(!tasks.empty());
    u32 seed = 1;
    for (u32 t : tasks) {
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        const u32 code = kOut;
        w16(m, code, 8);        // opcode COMM
        w16(m, code + 2, 146);  // operand: sScrCommandTable row 146
        const u32 sp0 = r32(m, t + kTaskSp);
        w32(m, t + kTaskInsn, code);
        w32(m, t + kTaskPc, 0);
        w32(m, kGpReg - 18296, 1);  // a shake request is running
        const hgp::Run r = s4_pair(m, "CodeFunc_Comm", {sx(t), 0, 0, 0}, seed++, "CodeFunc_Comm: COMM 146 on task " + hex64(t));
        if (r.stopped) continue;
        CHECK(v0_of(r) == 1);                    // SHAKE_STOP returned 1: the script goes on
        CHECK(r32(m, t + kTaskPc) == 1);             // pc + 1
        CHECK(r32(m, t + kTaskSp) == sp0);           // argc 0: nothing popped
        CHECK(r32(m, kCurrentTask) == t);        // the command's task
        CHECK(r32(m, kGpReg - 18296) == 0);      // the request's active flag cleared
        g_checks += 5;
    }
    // the handler itself, both bodies, from the same state
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    w32(m, kGpReg - 18296, 1);
    const hgp::Run h = s4_pair(m, "sub_350200", {0, 0, 0, 0}, 50, "sub_350200 direct");
    CHECK(v0_of(h) == 1);
    CHECK(r32(m, kGpReg - 18296) == 0);
    g_checks += 2;
    MESSAGE("COMM 146 on " << tasks.size() << " live script tasks");
}

// =====================================================================================================================
// The screen-shake request through its frames (dorm snapshot: the camera the shake moves is live)
// =====================================================================================================================
TEST_CASE("game(script4): the screen-shake request -- request, per-frame run, end, cancel") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::vector<u8> snap;
    if (!load_snapshot(m, "dorm_replay_4900", &snap)) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    constexpr u32 kReq = 0x957BC0u, kFrame = kGpReg - 18300, kActive = kGpReg - 18296;
    u32 seed = 100;
    for (u32 duration : {0u, 1u, 3u}) {
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        w32(m, kReq + 8, 0xDEAD);
        w32(m, kReq + 12, 0xBEEF);
        s4_pair(m, "sub_3500A0", {duration, 2, 0, 0}, seed++, "shake request " + std::to_string(duration));
        CHECK(r32(m, kReq) == duration);
        CHECK(r16(m, kReq + 4) == 2);
        CHECK(r32(m, kReq + 8) == 0);
        CHECK(r32(m, kReq + 12) == 0);
        CHECK(r32(m, kFrame) == 0);
        CHECK(r32(m, kActive) == 1);
        g_checks += 6;
        for (u32 f = 0; f < 6; ++f) {
            const bool was_active = r32(m, kActive) != 0;
            const u32 frame = r32(m, kFrame);
            s4_pair(m, "sub_350110", {0, 0, 0, 0}, seed++, "shake update d=" + std::to_string(duration) + " f=" + std::to_string(f));
            if (!was_active) {
                CHECK(r32(m, kFrame) == frame);  // nothing while no request runs
                CHECK(r32(m, kActive) == 0);
            } else {
                CHECK(r32(m, kFrame) == frame + 1);  // counts every running frame, also the last
                const bool ends = duration != 0 && frame >= duration;
                CHECK(r32(m, kActive) == (ends ? 0u : 1u));
            }
            g_checks += 2;
        }
    }
    // cancel
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    s4_pair(m, "sub_3500A0", {0, 1, 0, 0}, seed++, "shake request (cancelled)");
    s4_pair(m, "sub_3500E0", {0, 0, 0, 0}, seed++, "shake cancel");
    CHECK(r32(m, kActive) == 0);
    s4_pair(m, "sub_350110", {0, 0, 0, 0}, seed++, "shake update after cancel");
    CHECK(r32(m, kFrame) == 0);
    g_checks += 2;
}

// =====================================================================================================================
// effMiscRand: the 4-word shift-register generator against its rule
// =====================================================================================================================
TEST_CASE("game(script4): effMiscRand against the generator rule") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::mt19937 rng{0x5EED4u};
    const u32 st = kOut;
    for (u32 i = 0; i < 64; ++i) {
        u32 s[4];
        for (u32& x : s) {
            const u32 v = rng();
            x = v;
        }
        for (u32 k = 0; k < 4; ++k) w32(m, st + 4 * k, s[k]);
        const bool use_default = i % 8 == 7;
        if (use_default)
            for (u32 k = 0; k < 4; ++k) w32(m, 0x957BF0u + 4 * k, s[k]);
        const hgp::Run r = s4_pair(m, "sub_357FD0", {use_default ? 0 : sx(st), 0, 0, 0}, 200 + i, "effMiscRand " + std::to_string(i), Opt{{}, {}, false, {}});
        const u32 expect = ((s[1] << 2) | (s[0] >> 30)) ^ ((s[3] << 1) | (s[2] >> 31));
        const u32 base = use_default ? 0x957BF0u : st;
        CHECK(static_cast<u32>(v0_of(r)) == expect);
        CHECK(r32(m, base) == expect);
        CHECK(r32(m, base + 4) == s[0]);
        CHECK(r32(m, base + 8) == s[1]);
        CHECK(r32(m, base + 12) == s[2]);
        g_checks += 5;
    }
}

// =====================================================================================================================
// Class 31: the allocator, the slots, kind 10 (the battle camera's field of view)
// =====================================================================================================================
TEST_CASE("game(script4): class 31 allocator, slots and the field-of-view fade") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    write_rw_slots(m);
    g_live.clear();
    const u32 params = kOut + 0x100, gbtl = kOut + 0x1000;
    std::memset(m.at(gbtl), 0, 0x400);
    w32(m, kGBtlSlot, gbtl);
    for (u32 i = 0; i < 0x80; i += 4) w32(m, params + i, 0x11110000u + i);
    u32 seed = 300;
    for (u32 kind = 1; kind <= 11; ++kind) {
        const hgp::Run r = s4_pair(m, "sub_357770", {kind, sx(params), 0, 0}, seed++, "class 31 alloc kind " + std::to_string(kind));
        if (r.stopped) continue;
        const u32 inst = static_cast<u32>(v0_of(r));
        const u32 size = r32(m, 0x69CCF0u + 28 * kind + 24);
        REQUIRE(inst != 0);
        CHECK(log_of().calls_to(kRwSlotFns[0]) == 1);
        CHECK(log_of().log.front().args[0] == 64u + size);
        CHECK(r32(m, inst + 56) == inst + 64);
        CHECK(r32(m, inst + 40) == 0);
        CHECK(r32(m, inst + 44) == kind);
        CHECK(r32(m, inst + 36) == 0x80808080u);
        CHECK(r32(m, inst + 32) == 0x3F800000u);
        for (u32 q : {0u, 16u}) {
            CHECK(r32(m, inst + q) == 0);
            CHECK(r32(m, inst + q + 12) == 0x3F800000u);  // vf0 = (0, 0, 0, 1)
        }
        CHECK(std::memcmp(m.at(inst + 64), m.at(params), size) == 0);
        g_checks += 12;
    }
    // the setters on one instance
    const u32 inst = static_cast<u32>(v0_of(s4_pair(m, "sub_357770", {10, sx(params), 0, 0}, seed++, "kind 10 instance")));
    const u32 vec = kOut + 0x200;
    for (u32 k = 0; k < 4; ++k) wf(m, vec + 4 * k, 1.5f * static_cast<float>(k + 1));
    s4_pair(m, "sub_357D90", {sx(inst), sx(vec), 0, 0}, seed++, "set pos");
    s4_pair(m, "sub_357DA0", {sx(inst), sx(vec), 0, 0}, seed++, "set rot");
    s4_pair(m, "sub_357DB0", {sx(inst), 0x11223344, 0, 0}, seed++, "set colour");
    Opt sc;
    sc.fpr = {{12, fbits(2.25f)}};
    s4_pair(m, "sub_357DC0", {sx(inst), 0, 0, 0}, seed++, "set scale", sc);
    CHECK(std::memcmp(m.at(inst), m.at(vec), 16) == 0);
    CHECK(std::memcmp(m.at(inst + 16), m.at(vec), 16) == 0);
    CHECK(r32(m, inst + 36) == 0x11223344u);
    CHECK(rf(m, inst + 32) == 2.25f);
    g_checks += 4;
    // kind 10: duration 10, 30 -> 50 degrees; the update slot runs the kind's update and counts the frame
    const u32 p = r32(m, inst + 56);
    w32(m, p + 0, 10);
    wf(m, p + 4, 30.0f);
    wf(m, p + 8, 50.0f);
    wf(m, gbtl + 216, -1.0f);
    s4_pair(m, "sub_357BA0", {sx(inst), 0, 0, 0}, seed++, "kind 10 restart");
    CHECK(r32(m, inst + 40) == 0);
    for (u32 f = 0; f <= 12; ++f) {
        const float before = rf(m, gbtl + 216);
        s4_pair(m, f % 2 ? "sub_357C10" : "sub_357CE0", {sx(inst), 0, 0, 0}, seed++, "kind 10 frame " + std::to_string(f));
        CHECK(r32(m, inst + 40) == f + 1);
        const float fov = rf(m, gbtl + 216);
        if (f <= 10) {
            const float deg = 30.0f + (static_cast<float>(f) / 10.0f) * 20.0f;
            CHECK(near(fov, deg * 0.017453292f, 1e-5f));
        } else {
            CHECK(fov == before);  // past the duration: untouched
        }
        g_checks += 2;
    }
    // without a battle the kind slots do nothing (and do not count frames)
    w32(m, kGBtlSlot, 0);
    s4_pair(m, "sub_357C10", {sx(inst), 0, 0, 0}, seed++, "update without gBtl");
    CHECK(r32(m, inst + 40) == 13);
    w32(m, kGBtlSlot, gbtl);
    // destroy: kind 10's destroy puts the FOV back to 40 degrees, then RwFree(inst)
    const hgp::Run d = s4_pair(m, "sub_357930", {sx(inst), 0, 0, 0}, seed++, "kind 10 destroy");
    CHECK(r32(m, gbtl + 216) == 0x3F32B8C2u);
    CHECK(log_of().calls_to(kRwSlotFns[1]) == 1);
    CHECK(log_of().log.back().args[0] == inst);
    g_checks += 4;
    (void)d;
}

// =====================================================================================================================
// The fade kinds on the battle snapshot: kind 2 (the light pair of gBtl), kind 3 (every unit) and the unit filter
// =====================================================================================================================
namespace {
bool unit_selected(const Machine& m, u32 unit, const u8 sel[4]) {  // the host model of sub_352C70
    if (sel[3]) return true;
    for (u32 i = 0; i < 3; ++i) {
        const u32 u = r32(m, 0x957BD8u + 4 * i);
        if (u == 0) break;
        if ((sel[2] & (1u << i)) && u == unit) return true;
    }
    for (u32 k = 0; k < 2; ++k) {
        const u32 a = r32(m, 0x957BD0u + 4 * k);
        if (a == 0 || r8(m, unit + 162) != r8(m, a + 162)) continue;
        const u8 mode = sel[k];
        if (mode == 2) return true;
        if (mode == 1) return a == unit;
        if (mode == 0) return false;
    }
    return false;
}
std::vector<u32> battle_units(const Machine& m) {
    std::vector<u32> out;
    const u32 g = r32(m, kGBtlSlot);
    if (g == 0) return out;
    for (u32 i = 0; i < 4; ++i)
        for (u32 u = r32(m, g + 336 + 8 * i); u != 0 && out.size() < 64; u = r32(m, u + 2612)) out.push_back(u);
    return out;
}
}  // namespace

TEST_CASE("game(script4): the unit filter and the units' colour fade on the battle snapshot") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::vector<u8> snap;
    if (!load_snapshot(m, "b_5800", &snap)) {
        MESSAGE("SKIP: no b_5800 snapshot");
        return;
    }
    const std::vector<u32> units = battle_units(m);
    REQUIRE(units.size() >= 2);
    u32 seed = 400;
    // the actors and the list through their setters, then every unit x a set of selectors against the host model
    s4_pair(m, "sub_352C30", {sx(units[0]), sx(units.back()), 0, 0}, seed++, "set actors");
    s4_pair(m, "sub_352C50", {sx(units[1]), units.size() > 2 ? sx(units[2]) : 0, 0, 0}, seed++, "set list");
    CHECK(r32(m, 0x957BD0u) == units[0]);
    CHECK(r32(m, 0x957BD4u) == units.back());
    CHECK(r32(m, 0x957BD8u) == units[1]);
    CHECK(r32(m, 0x957BE0u) == 0);
    g_checks += 4;
    const u32 sel = kOut;
    int matches = 0;
    for (u32 mode_a = 0; mode_a < 4; ++mode_a)
        for (u32 mode_b = 0; mode_b < 4; mode_b += 3)
            for (u32 mask : {0u, 1u, 3u})
                for (u32 all : {0u, 1u}) {
                    const u8 s[4] = {static_cast<u8>(mode_a), static_cast<u8>(mode_b), static_cast<u8>(mask), static_cast<u8>(all)};
                    std::memcpy(m.at(sel), s, 4);
                    for (u32 u : units) {
                        const hgp::Run r = s4_pair(m, "sub_352C70", {sx(u), sx(sel), 0, 0}, seed++, "unit filter", Opt{{}, {}, false, {}});
                        CHECK((v0_of(r) != 0) == unit_selected(m, u, s));
                        ++g_checks;
                        ++matches;
                    }
                }
    // kind 3, duration 0, frame 0: every selected unit takes colour A at once and is marked (+152 bit 2)
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    const u32 inst = kOut + 0x100, params = kOut + 0x200;
    std::memset(m.at(inst), 0, 0x80);
    std::memset(m.at(params), 0, 0x20);
    w32(m, params + 8, 0x40302010u);  // colour A
    w8(m, params + 12 + 3, 1);         // selector: every unit
    w32(m, inst + 56, params);
    w32(m, inst + 44, 3);
    std::vector<u32> flags0;
    for (u32 u : units) flags0.push_back(r32(m, u + 152));
    s4_pair(m, "sub_3542A0", {sx(inst), 0, 0, 0}, seed++, "kind 3: colour A at once");
    for (std::size_t i = 0; i < units.size(); ++i) {
        CHECK(r32(m, units[i] + 60) == 0x40302010u);
        CHECK(r32(m, units[i] + 152) == (flags0[i] | 4u));
        g_checks += 2;
    }
    // kind 3 through a fade: duration 12, in 4, out 4, only actor A's side (mode 2), every frame paired
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    std::memset(m.at(inst), 0, 0x80);
    std::memset(m.at(params), 0, 0x20);
    w32(m, params + 0, 12);
    w16(m, params + 4, 4);
    w16(m, params + 6, 4);
    w32(m, params + 8, 0xFF8000FFu);
    w32(m, 0x957BD0u, units[0]);
    w8(m, params + 12, 2);
    w32(m, inst + 56, params);
    w32(m, inst + 44, 3);
    for (u32 f = 0; f <= 13; ++f) {
        w32(m, inst + 40, f);
        s4_pair(m, "sub_3542A0", {sx(inst), 0, 0, 0}, seed++, "kind 3 fade frame " + std::to_string(f));
        if (f == 4) CHECK(r32(m, units[0] + 60) == 0xFF8000FFu);  // the end of the fade-in: colour A (t = 1)
    }
    ++g_checks;
    MESSAGE("unit filter: " << units.size() << " units, " << matches << " selector checks");
}

TEST_CASE("game(script4): the battle scene-light fade (kind 2) and the light-block fade (kind 4) on the battle snapshot") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::vector<u8> snap;
    if (!load_snapshot(m, "b_5800", &snap)) {
        MESSAGE("SKIP: no b_5800 snapshot");
        return;
    }
    const u32 g = r32(m, kGBtlSlot);
    REQUIRE(g != 0);
    g_live.clear();
    u32 seed = 500;
    const u32 inst = kOut + 0x100, params = kOut + 0x200;
    // the state through the kind's create (RwMalloc 32)
    const hgp::Run c = s4_pair(m, "sub_353960", {0, 0, 0, 0}, seed++, "kind 2 create");
    const u32 state = static_cast<u32>(v0_of(c));
    REQUIRE(state != 0);
    CHECK(log_of().log.back().args[0] == 32u);
    std::memset(m.at(inst), 0, 0x80);
    std::memset(m.at(params), 0, 0x20);
    w32(m, params + 0, 20);
    w16(m, params + 4, 5);
    w16(m, params + 6, 5);
    w32(m, params + 8, 0x80FF4020u);   // target A
    w32(m, params + 12, 0x10C0E0A0u);  // target B
    w32(m, inst + 44, 2);
    w32(m, inst + 48, state);
    w32(m, inst + 56, params);
    float before[8], base[8];
    for (u32 k = 0; k < 8; ++k) before[k] = rf(m, g + 452 + 4 * k);
    for (u32 k = 0; k < 8; ++k) base[k] = rf(m, g + 500 + 4 * k);
    const float inv = std::bit_cast<float>(0x3B808081u);
    const u32 col[2] = {0x80FF4020u, 0x10C0E0A0u};
    for (u32 f = 0; f <= 21; ++f) {
        w32(m, inst + 40, f);
        s4_pair(m, "sub_3539C0", {sx(inst), 0, 0, 0}, seed++, "kind 2 frame " + std::to_string(f));
        if (f == 0)
            for (u32 k = 0; k < 8; ++k) CHECK(r32(m, state + 4 * k) == fbits(before[k]));  // saved at the phase start
        if (f == 5)  // t = 1: the targets x 1/255
            for (u32 k = 0; k < 8; ++k) CHECK(near(rf(m, g + 452 + 4 * k), inv * static_cast<float>((col[k / 4] >> (8 * (k % 4))) & 0xFF), 1e-6f));
        if (f == 20)  // the end of the fade-out (t = 0): the base pair exactly
            for (u32 k = 0; k < 8; ++k) CHECK(r32(m, g + 452 + 4 * k) == fbits(base[k]));
    }
    g_checks += 24;
    s4_pair(m, "sub_353990", {sx(state), 0, 0, 0}, seed++, "kind 2 destroy");
    CHECK(log_of().log.back().args[0] == state);
    ++g_checks;
    // kind 4 (the scene light blocks, the base colours of gBtl +404) through the same envelope: pairs only
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    g_live.clear();
    const u32 st4 = static_cast<u32>(v0_of(s4_pair(m, "sub_354B20", {0, 0, 0, 0}, seed++, "kind 4 create")));
    std::memset(m.at(inst), 0, 0x80);
    std::memset(m.at(params), 0, 0x20);
    w32(m, params + 0, 10);
    w16(m, params + 4, 3);
    w16(m, params + 6, 3);
    w32(m, params + 8, 0x7F7F7F7Fu);
    w32(m, params + 12, 0xFFFFFFFFu);
    w32(m, inst + 44, 4);
    w32(m, inst + 48, st4);
    w32(m, inst + 56, params);
    for (u32 f = 0; f <= 11; ++f) {
        w32(m, inst + 40, f);
        s4_pair(m, "sub_354B80", {sx(inst), 0, 0, 0}, seed++, "kind 4 frame " + std::to_string(f));
    }
    s4_pair(m, "sub_354B50", {sx(st4), 0, 0, 0}, seed++, "kind 4 destroy");
}

// =====================================================================================================================
// Class 30 kind 1: the colour-strip mesh, its colour rule (alpha 255 stored as 254)
// =====================================================================================================================
TEST_CASE("game(script4): class 30 kind 1 strip mesh and colour") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    write_rw_slots(m);
    g_live.clear();
    u32 seed = 600;
    const u32 block = kOut + 0x100, inst = kOut + 0x300;
    std::memset(m.at(block), 0, 0x100);
    for (u32 rows : {1u, 4u, 9u}) {
        w32(m, block + 56, rows);
        w32(m, block + 84, 0xAA112233u);
        w32(m, block + 88, 0x55667788u);
        const hgp::Run r = s4_pair(m, "sub_351D20", {sx(block), 0, 0, 0}, seed++, "strip create rows " + std::to_string(rows));
        if (r.stopped) continue;
        const u32 st = static_cast<u32>(v0_of(r));
        CHECK(r32(m, st) == st + 16);
        CHECK(r32(m, st + 8) == st);
        const u32 mesh = r32(m, st + 4);
        REQUIRE(mesh != 0);
        CHECK((r16(m, mesh) & 1u) == 0);
        const u32 verts = r32(m, r32(m, r32(m, mesh + 16) + 24) + 48);
        for (u32 k = 0; k < rows; ++k) {
            const u32 row = verts + 24 * k;
            CHECK(r32(m, row + 0) == 0x00112233u);
            CHECK(r32(m, row + 4) == 0xAA112233u);
            CHECK(r32(m, row + 8) == 0x00112233u);
            CHECK(r32(m, row + 12) == 0x00667788u);
            CHECK(r32(m, row + 16) == 0x55667788u);
            CHECK(r32(m, row + 20) == 0x00667788u);
            g_checks += 6;
        }
        g_checks += 3;
        // init: the strip colour from gp-18348 into the mesh material (+20 -> bytes +4..+7)
        std::memset(m.at(inst), 0, 0x40);
        w32(m, inst + 28, st);
        for (u32 alpha : {255u, 128u}) {
            const u8 rgba[4] = {10, 20, 30, static_cast<u8>(alpha)};
            std::memcpy(m.at(kGpReg - 18348), rgba, 4);
            s4_pair(m, "sub_351CA0", {sx(inst), 0, 0, 0}, seed++, "strip init alpha " + std::to_string(alpha));
            const u32 mat = r32(m, mesh + 20);
            CHECK(r8(m, mat + 4) == 10);
            CHECK(r8(m, mat + 5) == 20);
            CHECK(r8(m, mat + 6) == 30);
            CHECK(r8(m, mat + 7) == (alpha == 255 ? 254 : alpha));
            CHECK(r8(m, kGpReg - 18345) == alpha);  // the global keeps its alpha
            g_checks += 5;
        }
        // destroy: sub_3237C0 walks the mesh's RenderWare objects, which this world does not build (both bodies stop
        // at the same fault inside it); the pair still compares everything up to there
        s4_pair(m, "sub_351E20", {sx(st), 0, 0, 0}, seed++, "strip destroy");
    }
}

// =====================================================================================================================
// The VU0 matrix helpers against host maths
// =====================================================================================================================
TEST_CASE("game(script4): VU0 quaternion and axis-angle matrices against host maths") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::mt19937 rng{0xA11CEu};
    std::uniform_real_distribution<float> d(-1.0f, 1.0f);
    u32 seed = 700;
    const u32 out = kOut, in = kOut + 0x100;
    for (u32 i = 0; i < 24; ++i) {
        float q[4];
        for (float& x : q) {
            const float v = d(rng);
            x = v;
        }
        if (std::fabs(q[0]) + std::fabs(q[1]) + std::fabs(q[2]) + std::fabs(q[3]) < 0.1f) q[3] = 1.0f;
        for (u32 k = 0; k < 4; ++k) wf(m, in + 4 * k, q[k]);
        std::memset(m.at(out), 0xCD, 64);
        s4_pair(m, "sub_3296A0", {sx(out), sx(in), 0, 0}, seed++, "quat to matrix " + std::to_string(i), Opt{{}, {}, false, {}});
        const float n = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
        const float x = q[0] / n, y = q[1] / n, z = q[2] / n, w = q[3] / n;
        // sub_357E30's rows (read from its VU0 ops): row 0 = (1 - 2(y^2 + z^2), 2xy - 2wz, 2xz + 2wy), ...
        const float mat[3][3] = {{1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y)},
                                 {2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x)},
                                 {2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y)}};
        for (u32 r = 0; r < 3; ++r)
            for (u32 c = 0; c < 3; ++c) CHECK(near(rf(m, out + 16 * r + 4 * c), mat[r][c], 2e-4f));
        CHECK(r32(m, out + 48) == 0);
        CHECK(r32(m, out + 52) == 0);
        CHECK(r32(m, out + 56) == 0);
        g_checks += 12;
    }
    for (u32 i = 0; i < 24; ++i) {
        float a[3];
        for (float& x : a) {
            const float v = d(rng);
            x = v;
        }
        a[2] += 0.25f;
        const float ang = d(rng) * 3.0f;
        for (u32 k = 0; k < 3; ++k) wf(m, in + 4 * k, a[k]);
        wf(m, in + 12, 0.0f);
        Opt o{{}, {{12, fbits(ang)}}, false, {}};
        s4_pair(m, "sub_3581F0", {sx(in), sx(out), 0, 0}, seed++, "axis-angle " + std::to_string(i), o);
        const float n = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        const float x = a[0] / n, y = a[1] / n, z = a[2] / n, c = std::cos(ang), s = std::sin(ang), t = 1 - c;
        const float mat[3][3] = {{t * x * x + c, t * x * y + z * s, t * x * z - y * s},
                                 {t * x * y - z * s, t * y * y + c, t * y * z + x * s},
                                 {t * x * z + y * s, t * y * z - x * s, t * z * z + c}};
        for (u32 r = 0; r < 3; ++r)
            for (u32 cc = 0; cc < 3; ++cc) CHECK(near(rf(m, out + 16 * r + 4 * cc), mat[r][cc], 2e-4f));
        CHECK(r32(m, out + 60) == 0x3F800000u);  // row 3 = vf0
        g_checks += 10;
        s4_pair(m, "sub_358340", {sx(in), 0, 0, 0}, seed++, "axis-angle into vf28..31 " + std::to_string(i), o);
    }
}

// =====================================================================================================================
// itfPanel: create, move, the window layouts (stand-in heap and printf)
// =====================================================================================================================
TEST_CASE("game(script4): itfPanel create / move and the window layouts") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    write_rw_slots(m);
    g_live.clear();
    u32 seed = 800;
    for (u32 type = 0; type < 15; ++type) {
        const hgp::Run r = s4_pair(m, "sub_3A8B00", {type, type >= 6 && type <= 9 ? 0x1234u : 0u, 0, 0}, seed++, "itfPnlRegist2 type " + std::to_string(type));
        if (r.stopped) continue;
        const u32 p = static_cast<u32>(v0_of(r));
        REQUIRE(p != 0);
        CHECK(log_of().log.front().text == "itfPnlRegist2()\n");
        CHECK(r32(m, p) == p);
        CHECK(r8(m, p + 60) == type);
        const u32 work = r32(m, 0x6A1D10u + 4 * type);
        CHECK(r32(m, p + 4) == r32(m, p + 8));
        CHECK((r32(m, p + 4) != 0) == (work != 0));
        const u32 cb[5][3] = {{0x3A9140u, 0x3A9170u, 0x3A9230u}, {0x3A92A0u, 0x3A92D0u, 0x3A93A0u}, {0, 0x3A9400u, 0x3A9470u},
                              {0x3A94E0u, 0x3A9510u, 0x3A9580u}, {0, 0, 0}};
        if (type >= 10)
            for (u32 k = 0; k < 3; ++k) CHECK(r32(m, p + 64 + 4 * k) == cb[type - 10][k]);
        if (type >= 6 && type <= 9) CHECK(r32(m, r32(m, p + 8)) == 0x1234u);
        g_checks += 8;
        // move by (dx0, dy0, dx1, dy1, dz) = (3, -5, 7, 11, 2)
        const u32 x0 = r32(m, p + 16), y0 = r32(m, p + 20), x1 = r32(m, p + 24), y1 = r32(m, p + 28), z = r32(m, p + 12);
        Opt mv;
        mv.gpr_in = {{GPR_T0, 11}, {GPR_T1, 2}};
        s4_pair(m, "sub_3A8EA0", {sx(p), 3, sx(static_cast<u32>(-5)), 7}, seed++, "itfPnlSetPositionOffset type " + std::to_string(type), mv);
        CHECK(r32(m, p + 16) == x0 + 3);
        CHECK(r32(m, p + 20) == y0 - 5);
        CHECK(r32(m, p + 24) == x1 + 7);
        CHECK(r32(m, p + 28) == y1 + 11);
        CHECK(r32(m, p + 12) == z + 2);
        CHECK(log_of().log.front().text == "itfPnlSetPositionOffset()\n");
        g_checks += 6;
    }
    // the window layouts by window type and alpha
    const u32 rec = kOut;
    struct L {
        s32 x0, y0, x1, y1;
        u32 grey;
    };
    for (u32 type = 0; type < 7; ++type)
        for (s32 alpha : {0, -3, 77}) {
            std::memset(m.at(rec), 0xEE, 64);
            s4_pair(m, "sub_3A6CA0", {sx(rec), type, sx(static_cast<u32>(alpha)), 0}, seed++, "window layout " + std::to_string(type), Opt{{}, {}, false, {}});
            const L l = type == 5 ? L{0, 0, 9600, 1600, 0} : type == 4 ? L{0, 0, 0, 0, 0} : type == 2 ? L{-1552, -128, 7344, 648, 128} : L{-912, -128, 6704, 648, 128};
            CHECK(static_cast<s32>(r32(m, rec + 12)) == l.x0);
            CHECK(static_cast<s32>(r32(m, rec + 16)) == l.y0);
            CHECK(static_cast<s32>(r32(m, rec + 20)) == l.x1);
            CHECK(static_cast<s32>(r32(m, rec + 24)) == l.y1);
            for (u32 k = 0; k < 3; ++k) CHECK(r32(m, rec + 28 + 4 * k) == l.grey);
            CHECK(r32(m, rec + 40) == (alpha > 0 ? static_cast<u32>(alpha) : 128u));
            CHECK(r32(m, rec + 8) == 0xEEEEEEEEu);  // outside the layout: untouched
            g_checks += 9;
        }
}

// =====================================================================================================================
// The message manager on the dorm snapshot's live slots
// =====================================================================================================================
TEST_CASE("game(script4): message handles of the dorm snapshot -- tag parameters, arguments, panel step, draw, release") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::vector<u8> snap;
    if (!load_snapshot(m, "dorm_replay_4900", &snap)) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    g_live.clear();
    std::vector<u32> slots;
    for (u32 s = r32(m, 0x959ED0u); s != 0 && slots.size() < 64; s = r32(m, s + 4)) slots.push_back(r32(m, s + 8));
    REQUIRE(!slots.empty());
    const u32 slot = slots.back();
    const u32 h = r32(m, 0x959EECu + 52 * slot);
    REQUIRE(h != 0);
    u32 seed = 900;
    // tag parameters: the {key, value} pairs at handle +104, count at +102
    w16(m, h + 102, 0);
    auto tag = [&](u32 key, u32 value, const std::string& what) {
        return v0_of(s4_pair(m, "sub_3A4A70", {slot, sx(key), value, 0}, seed++, "tag param " + what, Opt{{}, {}, false, {}}));
    };
    CHECK(tag(3, 30, "new") == 1);
    CHECK(tag(6, 60, "6 stored as 5") == 1);
    CHECK(tag(3, 31, "overwrite") == 1);
    CHECK(tag(12, 1, "12 refused") == 0);
    CHECK(tag(14, 1, "14 refused") == 0);
    CHECK(tag(16, 1, "16 refused") == 0);
    CHECK(tag(static_cast<u32>(-1), 1, "-1 refused") == 0);
    CHECK(r16(m, h + 102) == 2);
    CHECK(r16(m, h + 104) == 3);
    CHECK(r16(m, h + 106) == 31);
    CHECK(r16(m, h + 108) == 5);
    CHECK(r16(m, h + 110) == 60);
    g_checks += 12;
    w16(m, h + 102, 15);
    for (u32 i = 0; i < 15; ++i) w16(m, h + 104 + 4 * i, static_cast<u16>(i == 7 ? 7 : 0));
    CHECK(tag(9, 1, "full") == 0);
    CHECK(tag(7, 77, "full, existing key") == 1);
    CHECK(r16(m, h + 104 + 4 * 7 + 2) == 77);
    g_checks += 3;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    // argument words: a word, a string, sized data
    const u32 data = kOut;
    m.put(data, "ZUNDA");
    for (u32 idx : {0u, 5u, 31u}) {
        const hgp::Run w = s4_pair(m, "sub_3A5EA0", {sx(h), idx, 0x0BADF00Du, 0}, seed++, "arg word " + std::to_string(idx));
        const u32 blk = r32(m, h + 212 + 4 * idx);
        CHECK(blk != 0);
        CHECK(r32(m, h + 340 + 4 * idx) == blk);
        CHECK(r32(m, blk) == 0x0BADF00Du);
        CHECK(static_cast<u32>(v0_of(w)) == blk);
        const hgp::Run s = s4_pair(m, "sub_3A5CA0", {sx(h), idx, sx(data), 0}, seed++, "arg string " + std::to_string(idx));
        const u32 blk2 = r32(m, h + 212 + 4 * idx);
        CHECK(m.str(blk2) == "ZUNDA");
        CHECK(log_of().calls_to(kHFree) == 1);  // the old block
        s4_pair(m, "sub_3A5CA0", {sx(h), idx, sx(data), 3}, seed++, "arg data " + std::to_string(idx));
        const u32 blk3 = r32(m, h + 212 + 4 * idx);
        CHECK(std::memcmp(m.at(blk3), "ZUN", 3) == 0);
        CHECK(r8(m, blk3 + 3) == 0);  // (3 + 5) & ~3 = 8 bytes, zeroed first
        g_checks += 8;
        (void)s;
    }
    // the per-frame step, the draw and the text rebuild of every live handle (not emitted here: the sprite handle create /
    // release -- other slices stand them in)
    Opt rec;
    std::memset(m.at(kOut + 0xE00), 0, 0x40);
    rec.recorders = {{0x1158B0u, "sprCreateHandle", sx(kOut + 0xE00)}, {0x115980u, "sprDestroyHandle", 0},
                     {0x109180u, "sub_109180 (the sound driver: a voice tag)", 0}};
    int drawn = 0;
    for (u32 s : slots) {
        const u32 hh = r32(m, 0x959EECu + 52 * s);
        if (hh == 0) continue;
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        g_live.clear();
        const std::string tag_s = " slot " + std::to_string(s);
        s4_pair(m, "sub_3A6E30", {sx(hh), 0, 0, 0}, seed++, "panel step" + tag_s, rec);
        s4_pair(m, "itfMesManagerDrawMsg", {sx(hh), 0, 0, 0}, seed++, "draw" + tag_s, rec);
        if (r32(m, hh + 44) != 0) {
            const hgp::Run t = s4_pair(m, "sub_3A5980", {sx(hh), 0, 0, 0}, seed++, "text rebuild" + tag_s, rec);
            if (!t.stopped) {
                CHECK(r32(m, hh + 48) != 0);  // the new chain
                ++g_checks;
            }
        }
        ++drawn;
    }
    // releasing the slot: no current handle, the entries cleared, unlinked, one handle less
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    g_live.clear();
    const u32 count0 = r32(m, 0x959EC0u);
    const hgp::Run rel = s4_pair(m, "sub_3A4DD0", {slot, 0, 0, 0}, seed++, "release slot");
    if (!rel.stopped) {
        const u32 row = 0x959EE0u + 52 * slot;
        CHECK(r32(m, row + 12) == 0);
        for (u32 e = 0; e < 4; ++e) CHECK(r32(m, row + 20 + 8 * e) == 0);
        CHECK(r32(m, 0x959EC0u) == count0 - 1);
        bool listed = false;
        for (u32 s = r32(m, 0x959ED0u), n = 0; s != 0 && n < 64; s = r32(m, s + 4), ++n) listed |= s == row;
        CHECK(!listed);
        g_checks += 7;
    }
    MESSAGE("dorm snapshot: " << slots.size() << " slots, " << drawn << " handles stepped and drawn");
}

// =====================================================================================================================
// The card effect's load steps on the stand-in file layer (the request of event/sys/cardeff.pak; the dorm snapshot's
// kwln lists for the task it creates). The read is left pending (the fake layer's completion registers the whole pak,
// past the pair runner's check-point budget), so state 2 is entered by hand.
// =====================================================================================================================
TEST_CASE("game(script4): the card effect's load steps") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    const u32 task = kOut, work = kOut + 0x100;
    std::memset(m.at(task), 0, 0x80);
    std::memset(m.at(work), 0, 0x200);
    w32(m, task + 60, work);
    w16(m, work + 4, 3);  // the social link
    Opt o;
    o.persist = true;  // one heap and one file layer per side for the whole sequence
    // not emitted here: mt_scene's model calls under ceCardEffectSaveModels (events2 stands them in too)
    o.recorders = {{0x3B83A0u, "sub_3B83A0", 0}, {0x3B8310u, "sub_3B8310", 0}, {0x3B83D0u, "sub_3B83D0", 0}};
    g_t.world[0].reset();
    g_t.world[1].reset();
    g_live.clear();
    u32 seed = 1200;
    // state 0: the pak requested
    hgp::Run r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: request", o);
    CHECK(v0_of(r) == 0);
    CHECK(r32(m, work) == 1);
    CHECK(r32(m, work + 16) != 0);
    bool requested = false;
    for (const StandInCall& c : log_of().log) {
        std::string s = c.text;
        for (char& ch : s) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        requested |= s.find("cardeff.pak") != std::string::npos;
    }
    CHECK(requested);
    g_checks += 4;
    // state 1 while the read is pending: nothing
    r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: pak pending", o);
    CHECK(v0_of(r) == 0);
    CHECK(r32(m, work) == 1);
    g_checks += 2;
    // state 2: the "CardEff" task (kwlnTaskCreate on the stand-in heap) and the model save, then 3 while it runs
    w32(m, work, 2);
    r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: create the task", o);
    if (!r.stopped) {
        CHECK(r32(m, work) == 3);
        CHECK(r32(m, work + 144) != 0);
        r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: the task runs", o);
        CHECK(r32(m, work) == 3);
        g_checks += 3;
    }
    // state 3 with no such task: 4; state 4 answers -1
    w32(m, work, 3);
    w32(m, work + 144, 0);  // no task
    r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: the task is gone", o);
    CHECK(r32(m, work) == 4);
    r = s4_pair(m, "sub_3A1C00", {sx(task), 0, 0, 0}, seed++, "card effect: done", o);
    CHECK(static_cast<s32>(v0_of(r)) == -1);
    g_checks += 2;
    g_t.world[0].reset();
    g_t.world[1].reset();
}

// =====================================================================================================================
// The event-message sequence on an idle MT_Msg slot; the event-busy test
// =====================================================================================================================
TEST_CASE("game(script4): the event-message sequence and the event-busy test") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 1100;
    const u32 work = kOut;
    for (u32 type = 0; type < 4; ++type) {
        std::memset(m.at(work), 0, 0x100);
        w16(m, work + 4, 3);  // id
        w32(m, work + 8, type);
        w32(m, work + 60, 1);  // the MT_Msg slot (work +60) is open: a request sets its phase 1 and its message
        std::vector<u32> requested;
        u32 steps = 0;
        u64 v0 = 0;
        while (steps < 40) {
            const u32 state = r32(m, work + 192);
            const std::string what = "sequence type " + std::to_string(type) + " state " + std::to_string(state);
            const hgp::Run r = s4_pair(m, "sub_3A0B50", {sx(work), 0, 0, 0}, seed++, what, Opt{{}, {}, false, {}});
            v0 = v0_of(r);
            ++steps;
            if (r.stopped || v0 == 1) break;
            const u32 now = r32(m, work + 192);
            if (state % 2 == 1 && now == state + 1) {  // a request state: the message went to the slot
                requested.push_back(r32(m, work + 60 + 16));
                CHECK(r32(m, work + 60 + 12) == 1);
                // the wait state holds while the slot is busy, then the request completes (MT_Msg_Update's phase 0)
                s4_pair(m, "sub_3A0B50", {sx(work), 0, 0, 0}, seed++, what + " (busy)", Opt{{}, {}, false, {}});
                CHECK(r32(m, work + 192) == now);
                w32(m, work + 60 + 12, 0);
                g_checks += 2;
            }
        }
        CHECK(v0 == 1);
        CHECK(r32(m, work + 192) == 15);
        if (type >= 2) CHECK(requested.empty());
        if (type == 0) CHECK(requested == std::vector<u32>{1});
        if (type == 1) CHECK((requested == std::vector<u32>{2, 3} || requested == std::vector<u32>{4, 5, 12, 13}));
        g_checks += 3;
    }
    // sub_3CF630 on a constructed event work
    const u32 ev = kOut + 0x200, panels = kOut + 0x300;
    w32(m, kGpReg - 18032, ev);
    for (u32 step : {0u, 1u})
        for (u32 f0 : {0u, 1u, 3u, 0x11u, 0x10u})
            for (u32 which : {0u, 2u}) {
                std::memset(m.at(ev), 0, 0x40);
                std::memset(m.at(panels), 0, 0x80);
                w32(m, ev + 4, step);
                w32(m, ev + 36, panels);
                w16(m, panels + 4 + 20 * which, static_cast<u16>(f0));
                const hgp::Run r = s4_pair(m, "sub_3CF630", {0, 0, 0, 0}, seed++, "event busy", Opt{{}, {}, false, {}});
                const bool busy = step != 0 || ((f0 & 1) && (f0 & 0x12));
                CHECK((v0_of(r) != 0) == busy);
                ++g_checks;
            }
}

TEST_CASE("game(script4): pair count") { MESSAGE("script4: " << g_pairs << " pairs outside the random worlds, " << g_checks << " rule checks"); }

#else

TEST_CASE("game(script4): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
