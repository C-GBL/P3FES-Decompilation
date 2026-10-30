// Pair tests for slice events3 (game/src/event/events3.cpp): the event editor's menu screens against their recompiled
// bodies. Every pair compares the whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and the cycle count at
// every check point and at the return, all 32 MiB of RAM (write-tracked) including the dead stack, the scratchpad, the
// bus log and, with stand-ins (stand_ins.h), every call to a function this test library does not emit: the debug text
// queue sub_1050E0 logs each line the menus draw (so both bodies draw the same screen, and the host checks what it
// says), the list-box value getters, the scene model table lookups and the curve rows answer from guest memory, the
// others are recorders; printf / sprintf / the heap stand in as usual.
//   * random worlds: every body on p3fes_handgen's random worlds (runs that reach a missing callee stop identically);
//   * a built editor world (the work with one menu on its stack, three units with keys, a scene with six models in four
//     classes): all 41 menus inactive (they only draw) and then 36 frames each through a table of pad inputs, with the
//     documented rules checked on the host -- confirm 1 / cancel -1, the row cursor's range, every changed key
//     parameter within its menu's limits;
//   * the menus' rules one by one: the integer / frame / float editors' steps and clamps, the condition editor's type
//     limits, the event-number menu's ranges and its "[E%3d_%03d.PM1+2+3]" header, the name keyboard's typing / delete /
//     accept, the choice list, the key list (new-frame line, delete -2, copy), the unit list's cursor unit, the model
//     pick list's rows, the position menu's model stepping, the resource list's rows, the function curve's load / store,
//     every tool kind of menu 26;
//   * the live opening event of the dorm route (E401_002; extracted/_ours/events_dorm_2100 / 2300, skipped when absent)
//     in editor mode: the unit list over every unit (the cursor's unit becomes the editor unit), every unit's key list
//     scrolled through all its keys (each key line through sub_3760A0), the settings menu (its 17 items and FIELD NO),
//     the resource list of every model class of the live scene, the model pick list, the model stepping of menus 23 / 24,
//     the unit settings of every unit type that has them, the motion and rotation editors on a live character model.
#include "handgen_pairs.h"

#include "stand_ins.h"

#include "p3fes/game/events3.h"

#include <algorithm>
#include <cmath>
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
void fn_sub_1A4330_001a4330(EEContext&);  // generated body
void fn_sub_1A4330_001a4330__recomp(EEContext&);  // recompiled
void fn_sub_350040_00350040(EEContext&);  // generated body
void fn_sub_350040_00350040__recomp(EEContext&);  // recompiled
void fn_sub_3B5460_003b5460(EEContext&);  // generated body
void fn_sub_3B5460_003b5460__recomp(EEContext&);  // recompiled
void fn_sub_3B55D0_003b55d0(EEContext&);  // generated body
void fn_sub_3B55D0_003b55d0__recomp(EEContext&);  // recompiled
void fn_sub_3B5DA0_003b5da0(EEContext&);  // generated body
void fn_sub_3B5DA0_003b5da0__recomp(EEContext&);  // recompiled
void fn_sub_36FA80_0036fa80(EEContext&);  // generated body
void fn_sub_36FA80_0036fa80__recomp(EEContext&);  // recompiled
void fn_sub_36FDA0_0036fda0(EEContext&);  // generated body
void fn_sub_36FDA0_0036fda0__recomp(EEContext&);  // recompiled
void fn_sub_370230_00370230(EEContext&);  // generated body
void fn_sub_370230_00370230__recomp(EEContext&);  // recompiled
void fn_sub_3702A0_003702a0(EEContext&);  // generated body
void fn_sub_3702A0_003702a0__recomp(EEContext&);  // recompiled
void fn_sub_3709D0_003709d0(EEContext&);  // generated body
void fn_sub_3709D0_003709d0__recomp(EEContext&);  // recompiled
void fn_sub_371350_00371350(EEContext&);  // generated body
void fn_sub_371350_00371350__recomp(EEContext&);  // recompiled
void fn_sub_3715B0_003715b0(EEContext&);  // generated body
void fn_sub_3715B0_003715b0__recomp(EEContext&);  // recompiled
void fn_sub_371710_00371710(EEContext&);  // generated body
void fn_sub_371710_00371710__recomp(EEContext&);  // recompiled
void fn_sub_371790_00371790(EEContext&);  // generated body
void fn_sub_371790_00371790__recomp(EEContext&);  // recompiled
void fn_sub_371DD0_00371dd0(EEContext&);  // generated body
void fn_sub_371DD0_00371dd0__recomp(EEContext&);  // recompiled
void fn_sub_372260_00372260(EEContext&);  // generated body
void fn_sub_372260_00372260__recomp(EEContext&);  // recompiled
void fn_sub_3722D0_003722d0(EEContext&);  // generated body
void fn_sub_3722D0_003722d0__recomp(EEContext&);  // recompiled
void fn_sub_372790_00372790(EEContext&);  // generated body
void fn_sub_372790_00372790__recomp(EEContext&);  // recompiled
void fn_sub_372C40_00372c40(EEContext&);  // generated body
void fn_sub_372C40_00372c40__recomp(EEContext&);  // recompiled
void fn_sub_373590_00373590(EEContext&);  // generated body
void fn_sub_373590_00373590__recomp(EEContext&);  // recompiled
void fn_sub_373700_00373700(EEContext&);  // generated body
void fn_sub_373700_00373700__recomp(EEContext&);  // recompiled
void fn_sub_3747A0_003747a0(EEContext&);  // generated body
void fn_sub_3747A0_003747a0__recomp(EEContext&);  // recompiled
void fn_sub_374AF0_00374af0(EEContext&);  // generated body
void fn_sub_374AF0_00374af0__recomp(EEContext&);  // recompiled
void fn_sub_374C90_00374c90(EEContext&);  // generated body
void fn_sub_374C90_00374c90__recomp(EEContext&);  // recompiled
void fn_sub_374D30_00374d30(EEContext&);  // generated body
void fn_sub_374D30_00374d30__recomp(EEContext&);  // recompiled
void fn_sub_375000_00375000(EEContext&);  // generated body
void fn_sub_375000_00375000__recomp(EEContext&);  // recompiled
void fn_sub_375350_00375350(EEContext&);  // generated body
void fn_sub_375350_00375350__recomp(EEContext&);  // recompiled
void fn_sub_3753C0_003753c0(EEContext&);  // generated body
void fn_sub_3753C0_003753c0__recomp(EEContext&);  // recompiled
void fn_sub_375590_00375590(EEContext&);  // generated body
void fn_sub_375590_00375590__recomp(EEContext&);  // recompiled
void fn_sub_3756E0_003756e0(EEContext&);  // generated body
void fn_sub_3756E0_003756e0__recomp(EEContext&);  // recompiled
void fn_sub_375750_00375750(EEContext&);  // generated body
void fn_sub_375750_00375750__recomp(EEContext&);  // recompiled
void fn_sub_375900_00375900(EEContext&);  // generated body
void fn_sub_375900_00375900__recomp(EEContext&);  // recompiled
void fn_sub_375A40_00375a40(EEContext&);  // generated body
void fn_sub_375A40_00375a40__recomp(EEContext&);  // recompiled
void fn_sub_375AB0_00375ab0(EEContext&);  // generated body
void fn_sub_375AB0_00375ab0__recomp(EEContext&);  // recompiled
void fn_sub_375D70_00375d70(EEContext&);  // generated body
void fn_sub_375D70_00375d70__recomp(EEContext&);  // recompiled
void fn_sub_375F30_00375f30(EEContext&);  // generated body
void fn_sub_375F30_00375f30__recomp(EEContext&);  // recompiled
void fn_sub_3760A0_003760a0(EEContext&);  // generated body
void fn_sub_3760A0_003760a0__recomp(EEContext&);  // recompiled
void fn_sub_3797B0_003797b0(EEContext&);  // generated body
void fn_sub_3797B0_003797b0__recomp(EEContext&);  // recompiled
void fn_sub_3798F0_003798f0(EEContext&);  // generated body
void fn_sub_3798F0_003798f0__recomp(EEContext&);  // recompiled
void fn_sub_379C30_00379c30(EEContext&);  // generated body
void fn_sub_379C30_00379c30__recomp(EEContext&);  // recompiled
void fn_sub_379F30_00379f30(EEContext&);  // generated body
void fn_sub_379F30_00379f30__recomp(EEContext&);  // recompiled
void fn_sub_37A150_0037a150(EEContext&);  // generated body
void fn_sub_37A150_0037a150__recomp(EEContext&);  // recompiled
void fn_sub_37A1E0_0037a1e0(EEContext&);  // generated body
void fn_sub_37A1E0_0037a1e0__recomp(EEContext&);  // recompiled
void fn_sub_37A2B0_0037a2b0(EEContext&);  // generated body
void fn_sub_37A2B0_0037a2b0__recomp(EEContext&);  // recompiled
void fn_sub_37A4D0_0037a4d0(EEContext&);  // generated body
void fn_sub_37A4D0_0037a4d0__recomp(EEContext&);  // recompiled
void fn_sub_37A560_0037a560(EEContext&);  // generated body
void fn_sub_37A560_0037a560__recomp(EEContext&);  // recompiled
void fn_sub_37A640_0037a640(EEContext&);  // generated body
void fn_sub_37A640_0037a640__recomp(EEContext&);  // recompiled
void fn_sub_37A790_0037a790(EEContext&);  // generated body
void fn_sub_37A790_0037a790__recomp(EEContext&);  // recompiled
void fn_sub_37ABD0_0037abd0(EEContext&);  // generated body
void fn_sub_37ABD0_0037abd0__recomp(EEContext&);  // recompiled
void fn_sub_37ACC0_0037acc0(EEContext&);  // generated body
void fn_sub_37ACC0_0037acc0__recomp(EEContext&);  // recompiled
void fn_sub_37AD30_0037ad30(EEContext&);  // generated body
void fn_sub_37AD30_0037ad30__recomp(EEContext&);  // recompiled
void fn_sub_37AFC0_0037afc0(EEContext&);  // generated body
void fn_sub_37AFC0_0037afc0__recomp(EEContext&);  // recompiled
void fn_sub_37B2E0_0037b2e0(EEContext&);  // generated body
void fn_sub_37B2E0_0037b2e0__recomp(EEContext&);  // recompiled
void fn_sub_37B350_0037b350(EEContext&);  // generated body
void fn_sub_37B350_0037b350__recomp(EEContext&);  // recompiled
void fn_sub_37B5D0_0037b5d0(EEContext&);  // generated body
void fn_sub_37B5D0_0037b5d0__recomp(EEContext&);  // recompiled
void fn_sub_37BA80_0037ba80(EEContext&);  // generated body
void fn_sub_37BA80_0037ba80__recomp(EEContext&);  // recompiled
void fn_sub_37BAF0_0037baf0(EEContext&);  // generated body
void fn_sub_37BAF0_0037baf0__recomp(EEContext&);  // recompiled
void fn_sub_37BE50_0037be50(EEContext&);  // generated body
void fn_sub_37BE50_0037be50__recomp(EEContext&);  // recompiled
void fn_sub_37C2E0_0037c2e0(EEContext&);  // generated body
void fn_sub_37C2E0_0037c2e0__recomp(EEContext&);  // recompiled
void fn_sub_37C350_0037c350(EEContext&);  // generated body
void fn_sub_37C350_0037c350__recomp(EEContext&);  // recompiled
void fn_sub_37CAF0_0037caf0(EEContext&);  // generated body
void fn_sub_37CAF0_0037caf0__recomp(EEContext&);  // recompiled
void fn_sub_37CFE0_0037cfe0(EEContext&);  // generated body
void fn_sub_37CFE0_0037cfe0__recomp(EEContext&);  // recompiled
void fn_sub_37D4D0_0037d4d0(EEContext&);  // generated body
void fn_sub_37D4D0_0037d4d0__recomp(EEContext&);  // recompiled
void fn_sub_37D540_0037d540(EEContext&);  // generated body
void fn_sub_37D540_0037d540__recomp(EEContext&);  // recompiled
void fn_sub_37D5D0_0037d5d0(EEContext&);  // generated body
void fn_sub_37D5D0_0037d5d0__recomp(EEContext&);  // recompiled
void fn_sub_37DF50_0037df50(EEContext&);  // generated body
void fn_sub_37DF50_0037df50__recomp(EEContext&);  // recompiled
void fn_sub_37DFC0_0037dfc0(EEContext&);  // generated body
void fn_sub_37DFC0_0037dfc0__recomp(EEContext&);  // recompiled
void fn_sub_37E1B0_0037e1b0(EEContext&);  // generated body
void fn_sub_37E1B0_0037e1b0__recomp(EEContext&);  // recompiled
void fn_sub_37E3F0_0037e3f0(EEContext&);  // generated body
void fn_sub_37E3F0_0037e3f0__recomp(EEContext&);  // recompiled
void fn_sub_37E460_0037e460(EEContext&);  // generated body
void fn_sub_37E460_0037e460__recomp(EEContext&);  // recompiled
void fn_sub_37EAD0_0037ead0(EEContext&);  // generated body
void fn_sub_37EAD0_0037ead0__recomp(EEContext&);  // recompiled
void fn_sub_37F050_0037f050(EEContext&);  // generated body
void fn_sub_37F050_0037f050__recomp(EEContext&);  // recompiled
void fn_sub_37F0C0_0037f0c0(EEContext&);  // generated body
void fn_sub_37F0C0_0037f0c0__recomp(EEContext&);  // recompiled
void fn_sub_37F3D0_0037f3d0(EEContext&);  // generated body
void fn_sub_37F3D0_0037f3d0__recomp(EEContext&);  // recompiled
void fn_sub_37F5E0_0037f5e0(EEContext&);  // generated body
void fn_sub_37F5E0_0037f5e0__recomp(EEContext&);  // recompiled
void fn_sub_37F650_0037f650(EEContext&);  // generated body
void fn_sub_37F650_0037f650__recomp(EEContext&);  // recompiled
void fn_sub_37FAE0_0037fae0(EEContext&);  // generated body
void fn_sub_37FAE0_0037fae0__recomp(EEContext&);  // recompiled
void fn_sub_37FF10_0037ff10(EEContext&);  // generated body
void fn_sub_37FF10_0037ff10__recomp(EEContext&);  // recompiled
void fn_sub_37FF80_0037ff80(EEContext&);  // generated body
void fn_sub_37FF80_0037ff80__recomp(EEContext&);  // recompiled
void fn_sub_380200_00380200(EEContext&);  // generated body
void fn_sub_380200_00380200__recomp(EEContext&);  // recompiled
void fn_sub_380310_00380310(EEContext&);  // generated body
void fn_sub_380310_00380310__recomp(EEContext&);  // recompiled
void fn_sub_380380_00380380(EEContext&);  // generated body
void fn_sub_380380_00380380__recomp(EEContext&);  // recompiled
void fn_sub_3806F0_003806f0(EEContext&);  // generated body
void fn_sub_3806F0_003806f0__recomp(EEContext&);  // recompiled
void fn_sub_3809C0_003809c0(EEContext&);  // generated body
void fn_sub_3809C0_003809c0__recomp(EEContext&);  // recompiled
void fn_sub_380A30_00380a30(EEContext&);  // generated body
void fn_sub_380A30_00380a30__recomp(EEContext&);  // recompiled
void fn_sub_380D70_00380d70(EEContext&);  // generated body
void fn_sub_380D70_00380d70__recomp(EEContext&);  // recompiled
void fn_sub_3810A0_003810a0(EEContext&);  // generated body
void fn_sub_3810A0_003810a0__recomp(EEContext&);  // recompiled
void fn_sub_381110_00381110(EEContext&);  // generated body
void fn_sub_381110_00381110__recomp(EEContext&);  // recompiled
void fn_sub_381280_00381280(EEContext&);  // generated body
void fn_sub_381280_00381280__recomp(EEContext&);  // recompiled
void fn_sub_3814D0_003814d0(EEContext&);  // generated body
void fn_sub_3814D0_003814d0__recomp(EEContext&);  // recompiled
void fn_sub_381540_00381540(EEContext&);  // generated body
void fn_sub_381540_00381540__recomp(EEContext&);  // recompiled
void fn_sub_3819B0_003819b0(EEContext&);  // generated body
void fn_sub_3819B0_003819b0__recomp(EEContext&);  // recompiled
void fn_sub_381BF0_00381bf0(EEContext&);  // generated body
void fn_sub_381BF0_00381bf0__recomp(EEContext&);  // recompiled
void fn_sub_381C60_00381c60(EEContext&);  // generated body
void fn_sub_381C60_00381c60__recomp(EEContext&);  // recompiled
void fn_sub_3820E0_003820e0(EEContext&);  // generated body
void fn_sub_3820E0_003820e0__recomp(EEContext&);  // recompiled
void fn_sub_382320_00382320(EEContext&);  // generated body
void fn_sub_382320_00382320__recomp(EEContext&);  // recompiled
void fn_sub_382390_00382390(EEContext&);  // generated body
void fn_sub_382390_00382390__recomp(EEContext&);  // recompiled
void fn_sub_382500_00382500(EEContext&);  // generated body
void fn_sub_382500_00382500__recomp(EEContext&);  // recompiled
void fn_sub_3826F0_003826f0(EEContext&);  // generated body
void fn_sub_3826F0_003826f0__recomp(EEContext&);  // recompiled
void fn_sub_382760_00382760(EEContext&);  // generated body
void fn_sub_382760_00382760__recomp(EEContext&);  // recompiled
void fn_sub_382840_00382840(EEContext&);  // generated body
void fn_sub_382840_00382840__recomp(EEContext&);  // recompiled
void fn_sub_382C10_00382c10(EEContext&);  // generated body
void fn_sub_382C10_00382c10__recomp(EEContext&);  // recompiled
void fn_sub_382C80_00382c80(EEContext&);  // generated body
void fn_sub_382C80_00382c80__recomp(EEContext&);  // recompiled
void fn_sub_382D60_00382d60(EEContext&);  // generated body
void fn_sub_382D60_00382d60__recomp(EEContext&);  // recompiled
void fn_sub_382EC0_00382ec0(EEContext&);  // generated body
void fn_sub_382EC0_00382ec0__recomp(EEContext&);  // recompiled
void fn_sub_382F30_00382f30(EEContext&);  // generated body
void fn_sub_382F30_00382f30__recomp(EEContext&);  // recompiled
void fn_sub_383360_00383360(EEContext&);  // generated body
void fn_sub_383360_00383360__recomp(EEContext&);  // recompiled
void fn_sub_383810_00383810(EEContext&);  // generated body
void fn_sub_383810_00383810__recomp(EEContext&);  // recompiled
void fn_sub_383880_00383880(EEContext&);  // generated body
void fn_sub_383880_00383880__recomp(EEContext&);  // recompiled
void fn_sub_383D80_00383d80(EEContext&);  // generated body
void fn_sub_383D80_00383d80__recomp(EEContext&);  // recompiled
void fn_sub_384060_00384060(EEContext&);  // generated body
void fn_sub_384060_00384060__recomp(EEContext&);  // recompiled
void fn_sub_3840D0_003840d0(EEContext&);  // generated body
void fn_sub_3840D0_003840d0__recomp(EEContext&);  // recompiled
void fn_sub_384370_00384370(EEContext&);  // generated body
void fn_sub_384370_00384370__recomp(EEContext&);  // recompiled
void fn_sub_3844B0_003844b0(EEContext&);  // generated body
void fn_sub_3844B0_003844b0__recomp(EEContext&);  // recompiled
void fn_sub_384520_00384520(EEContext&);  // generated body
void fn_sub_384520_00384520__recomp(EEContext&);  // recompiled
void fn_sub_384780_00384780(EEContext&);  // generated body
void fn_sub_384780_00384780__recomp(EEContext&);  // recompiled
void fn_sub_3849E0_003849e0(EEContext&);  // generated body
void fn_sub_3849E0_003849e0__recomp(EEContext&);  // recompiled
void fn_sub_384A50_00384a50(EEContext&);  // generated body
void fn_sub_384A50_00384a50__recomp(EEContext&);  // recompiled
void fn_sub_384D30_00384d30(EEContext&);  // generated body
void fn_sub_384D30_00384d30__recomp(EEContext&);  // recompiled
void fn_sub_3851F0_003851f0(EEContext&);  // generated body
void fn_sub_3851F0_003851f0__recomp(EEContext&);  // recompiled
void fn_sub_385260_00385260(EEContext&);  // generated body
void fn_sub_385260_00385260__recomp(EEContext&);  // recompiled
void fn_sub_385520_00385520(EEContext&);  // generated body
void fn_sub_385520_00385520__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1A4330", 0x1A4330, &recomp_gen::fn_sub_1A4330_001a4330, &recomp_gen::fn_sub_1A4330_001a4330__recomp},
    {"sub_350040", 0x350040, &recomp_gen::fn_sub_350040_00350040, &recomp_gen::fn_sub_350040_00350040__recomp},
    {"sub_3B5460", 0x3B5460, &recomp_gen::fn_sub_3B5460_003b5460, &recomp_gen::fn_sub_3B5460_003b5460__recomp},
    {"sub_3B55D0", 0x3B55D0, &recomp_gen::fn_sub_3B55D0_003b55d0, &recomp_gen::fn_sub_3B55D0_003b55d0__recomp},
    {"sub_3B5DA0", 0x3B5DA0, &recomp_gen::fn_sub_3B5DA0_003b5da0, &recomp_gen::fn_sub_3B5DA0_003b5da0__recomp},
    {"sub_36FA80", 0x36FA80, &recomp_gen::fn_sub_36FA80_0036fa80, &recomp_gen::fn_sub_36FA80_0036fa80__recomp},
    {"sub_36FDA0", 0x36FDA0, &recomp_gen::fn_sub_36FDA0_0036fda0, &recomp_gen::fn_sub_36FDA0_0036fda0__recomp},
    {"sub_370230", 0x370230, &recomp_gen::fn_sub_370230_00370230, &recomp_gen::fn_sub_370230_00370230__recomp},
    {"sub_3702A0", 0x3702A0, &recomp_gen::fn_sub_3702A0_003702a0, &recomp_gen::fn_sub_3702A0_003702a0__recomp},
    {"sub_3709D0", 0x3709D0, &recomp_gen::fn_sub_3709D0_003709d0, &recomp_gen::fn_sub_3709D0_003709d0__recomp},
    {"sub_371350", 0x371350, &recomp_gen::fn_sub_371350_00371350, &recomp_gen::fn_sub_371350_00371350__recomp},
    {"sub_3715B0", 0x3715B0, &recomp_gen::fn_sub_3715B0_003715b0, &recomp_gen::fn_sub_3715B0_003715b0__recomp},
    {"sub_371710", 0x371710, &recomp_gen::fn_sub_371710_00371710, &recomp_gen::fn_sub_371710_00371710__recomp},
    {"sub_371790", 0x371790, &recomp_gen::fn_sub_371790_00371790, &recomp_gen::fn_sub_371790_00371790__recomp},
    {"sub_371DD0", 0x371DD0, &recomp_gen::fn_sub_371DD0_00371dd0, &recomp_gen::fn_sub_371DD0_00371dd0__recomp},
    {"sub_372260", 0x372260, &recomp_gen::fn_sub_372260_00372260, &recomp_gen::fn_sub_372260_00372260__recomp},
    {"sub_3722D0", 0x3722D0, &recomp_gen::fn_sub_3722D0_003722d0, &recomp_gen::fn_sub_3722D0_003722d0__recomp},
    {"sub_372790", 0x372790, &recomp_gen::fn_sub_372790_00372790, &recomp_gen::fn_sub_372790_00372790__recomp},
    {"sub_372C40", 0x372C40, &recomp_gen::fn_sub_372C40_00372c40, &recomp_gen::fn_sub_372C40_00372c40__recomp},
    {"sub_373590", 0x373590, &recomp_gen::fn_sub_373590_00373590, &recomp_gen::fn_sub_373590_00373590__recomp},
    {"sub_373700", 0x373700, &recomp_gen::fn_sub_373700_00373700, &recomp_gen::fn_sub_373700_00373700__recomp},
    {"sub_3747A0", 0x3747A0, &recomp_gen::fn_sub_3747A0_003747a0, &recomp_gen::fn_sub_3747A0_003747a0__recomp},
    {"sub_374AF0", 0x374AF0, &recomp_gen::fn_sub_374AF0_00374af0, &recomp_gen::fn_sub_374AF0_00374af0__recomp},
    {"sub_374C90", 0x374C90, &recomp_gen::fn_sub_374C90_00374c90, &recomp_gen::fn_sub_374C90_00374c90__recomp},
    {"sub_374D30", 0x374D30, &recomp_gen::fn_sub_374D30_00374d30, &recomp_gen::fn_sub_374D30_00374d30__recomp},
    {"sub_375000", 0x375000, &recomp_gen::fn_sub_375000_00375000, &recomp_gen::fn_sub_375000_00375000__recomp},
    {"sub_375350", 0x375350, &recomp_gen::fn_sub_375350_00375350, &recomp_gen::fn_sub_375350_00375350__recomp},
    {"sub_3753C0", 0x3753C0, &recomp_gen::fn_sub_3753C0_003753c0, &recomp_gen::fn_sub_3753C0_003753c0__recomp},
    {"sub_375590", 0x375590, &recomp_gen::fn_sub_375590_00375590, &recomp_gen::fn_sub_375590_00375590__recomp},
    {"sub_3756E0", 0x3756E0, &recomp_gen::fn_sub_3756E0_003756e0, &recomp_gen::fn_sub_3756E0_003756e0__recomp},
    {"sub_375750", 0x375750, &recomp_gen::fn_sub_375750_00375750, &recomp_gen::fn_sub_375750_00375750__recomp},
    {"sub_375900", 0x375900, &recomp_gen::fn_sub_375900_00375900, &recomp_gen::fn_sub_375900_00375900__recomp},
    {"sub_375A40", 0x375A40, &recomp_gen::fn_sub_375A40_00375a40, &recomp_gen::fn_sub_375A40_00375a40__recomp},
    {"sub_375AB0", 0x375AB0, &recomp_gen::fn_sub_375AB0_00375ab0, &recomp_gen::fn_sub_375AB0_00375ab0__recomp},
    {"sub_375D70", 0x375D70, &recomp_gen::fn_sub_375D70_00375d70, &recomp_gen::fn_sub_375D70_00375d70__recomp},
    {"sub_375F30", 0x375F30, &recomp_gen::fn_sub_375F30_00375f30, &recomp_gen::fn_sub_375F30_00375f30__recomp},
    {"sub_3760A0", 0x3760A0, &recomp_gen::fn_sub_3760A0_003760a0, &recomp_gen::fn_sub_3760A0_003760a0__recomp},
    {"sub_3797B0", 0x3797B0, &recomp_gen::fn_sub_3797B0_003797b0, &recomp_gen::fn_sub_3797B0_003797b0__recomp},
    {"sub_3798F0", 0x3798F0, &recomp_gen::fn_sub_3798F0_003798f0, &recomp_gen::fn_sub_3798F0_003798f0__recomp},
    {"sub_379C30", 0x379C30, &recomp_gen::fn_sub_379C30_00379c30, &recomp_gen::fn_sub_379C30_00379c30__recomp},
    {"sub_379F30", 0x379F30, &recomp_gen::fn_sub_379F30_00379f30, &recomp_gen::fn_sub_379F30_00379f30__recomp},
    {"sub_37A150", 0x37A150, &recomp_gen::fn_sub_37A150_0037a150, &recomp_gen::fn_sub_37A150_0037a150__recomp},
    {"sub_37A1E0", 0x37A1E0, &recomp_gen::fn_sub_37A1E0_0037a1e0, &recomp_gen::fn_sub_37A1E0_0037a1e0__recomp},
    {"sub_37A2B0", 0x37A2B0, &recomp_gen::fn_sub_37A2B0_0037a2b0, &recomp_gen::fn_sub_37A2B0_0037a2b0__recomp},
    {"sub_37A4D0", 0x37A4D0, &recomp_gen::fn_sub_37A4D0_0037a4d0, &recomp_gen::fn_sub_37A4D0_0037a4d0__recomp},
    {"sub_37A560", 0x37A560, &recomp_gen::fn_sub_37A560_0037a560, &recomp_gen::fn_sub_37A560_0037a560__recomp},
    {"sub_37A640", 0x37A640, &recomp_gen::fn_sub_37A640_0037a640, &recomp_gen::fn_sub_37A640_0037a640__recomp},
    {"sub_37A790", 0x37A790, &recomp_gen::fn_sub_37A790_0037a790, &recomp_gen::fn_sub_37A790_0037a790__recomp},
    {"sub_37ABD0", 0x37ABD0, &recomp_gen::fn_sub_37ABD0_0037abd0, &recomp_gen::fn_sub_37ABD0_0037abd0__recomp},
    {"sub_37ACC0", 0x37ACC0, &recomp_gen::fn_sub_37ACC0_0037acc0, &recomp_gen::fn_sub_37ACC0_0037acc0__recomp},
    {"sub_37AD30", 0x37AD30, &recomp_gen::fn_sub_37AD30_0037ad30, &recomp_gen::fn_sub_37AD30_0037ad30__recomp},
    {"sub_37AFC0", 0x37AFC0, &recomp_gen::fn_sub_37AFC0_0037afc0, &recomp_gen::fn_sub_37AFC0_0037afc0__recomp},
    {"sub_37B2E0", 0x37B2E0, &recomp_gen::fn_sub_37B2E0_0037b2e0, &recomp_gen::fn_sub_37B2E0_0037b2e0__recomp},
    {"sub_37B350", 0x37B350, &recomp_gen::fn_sub_37B350_0037b350, &recomp_gen::fn_sub_37B350_0037b350__recomp},
    {"sub_37B5D0", 0x37B5D0, &recomp_gen::fn_sub_37B5D0_0037b5d0, &recomp_gen::fn_sub_37B5D0_0037b5d0__recomp},
    {"sub_37BA80", 0x37BA80, &recomp_gen::fn_sub_37BA80_0037ba80, &recomp_gen::fn_sub_37BA80_0037ba80__recomp},
    {"sub_37BAF0", 0x37BAF0, &recomp_gen::fn_sub_37BAF0_0037baf0, &recomp_gen::fn_sub_37BAF0_0037baf0__recomp},
    {"sub_37BE50", 0x37BE50, &recomp_gen::fn_sub_37BE50_0037be50, &recomp_gen::fn_sub_37BE50_0037be50__recomp},
    {"sub_37C2E0", 0x37C2E0, &recomp_gen::fn_sub_37C2E0_0037c2e0, &recomp_gen::fn_sub_37C2E0_0037c2e0__recomp},
    {"sub_37C350", 0x37C350, &recomp_gen::fn_sub_37C350_0037c350, &recomp_gen::fn_sub_37C350_0037c350__recomp},
    {"sub_37CAF0", 0x37CAF0, &recomp_gen::fn_sub_37CAF0_0037caf0, &recomp_gen::fn_sub_37CAF0_0037caf0__recomp},
    {"sub_37CFE0", 0x37CFE0, &recomp_gen::fn_sub_37CFE0_0037cfe0, &recomp_gen::fn_sub_37CFE0_0037cfe0__recomp},
    {"sub_37D4D0", 0x37D4D0, &recomp_gen::fn_sub_37D4D0_0037d4d0, &recomp_gen::fn_sub_37D4D0_0037d4d0__recomp},
    {"sub_37D540", 0x37D540, &recomp_gen::fn_sub_37D540_0037d540, &recomp_gen::fn_sub_37D540_0037d540__recomp},
    {"sub_37D5D0", 0x37D5D0, &recomp_gen::fn_sub_37D5D0_0037d5d0, &recomp_gen::fn_sub_37D5D0_0037d5d0__recomp},
    {"sub_37DF50", 0x37DF50, &recomp_gen::fn_sub_37DF50_0037df50, &recomp_gen::fn_sub_37DF50_0037df50__recomp},
    {"sub_37DFC0", 0x37DFC0, &recomp_gen::fn_sub_37DFC0_0037dfc0, &recomp_gen::fn_sub_37DFC0_0037dfc0__recomp},
    {"sub_37E1B0", 0x37E1B0, &recomp_gen::fn_sub_37E1B0_0037e1b0, &recomp_gen::fn_sub_37E1B0_0037e1b0__recomp},
    {"sub_37E3F0", 0x37E3F0, &recomp_gen::fn_sub_37E3F0_0037e3f0, &recomp_gen::fn_sub_37E3F0_0037e3f0__recomp},
    {"sub_37E460", 0x37E460, &recomp_gen::fn_sub_37E460_0037e460, &recomp_gen::fn_sub_37E460_0037e460__recomp},
    {"sub_37EAD0", 0x37EAD0, &recomp_gen::fn_sub_37EAD0_0037ead0, &recomp_gen::fn_sub_37EAD0_0037ead0__recomp},
    {"sub_37F050", 0x37F050, &recomp_gen::fn_sub_37F050_0037f050, &recomp_gen::fn_sub_37F050_0037f050__recomp},
    {"sub_37F0C0", 0x37F0C0, &recomp_gen::fn_sub_37F0C0_0037f0c0, &recomp_gen::fn_sub_37F0C0_0037f0c0__recomp},
    {"sub_37F3D0", 0x37F3D0, &recomp_gen::fn_sub_37F3D0_0037f3d0, &recomp_gen::fn_sub_37F3D0_0037f3d0__recomp},
    {"sub_37F5E0", 0x37F5E0, &recomp_gen::fn_sub_37F5E0_0037f5e0, &recomp_gen::fn_sub_37F5E0_0037f5e0__recomp},
    {"sub_37F650", 0x37F650, &recomp_gen::fn_sub_37F650_0037f650, &recomp_gen::fn_sub_37F650_0037f650__recomp},
    {"sub_37FAE0", 0x37FAE0, &recomp_gen::fn_sub_37FAE0_0037fae0, &recomp_gen::fn_sub_37FAE0_0037fae0__recomp},
    {"sub_37FF10", 0x37FF10, &recomp_gen::fn_sub_37FF10_0037ff10, &recomp_gen::fn_sub_37FF10_0037ff10__recomp},
    {"sub_37FF80", 0x37FF80, &recomp_gen::fn_sub_37FF80_0037ff80, &recomp_gen::fn_sub_37FF80_0037ff80__recomp},
    {"sub_380200", 0x380200, &recomp_gen::fn_sub_380200_00380200, &recomp_gen::fn_sub_380200_00380200__recomp},
    {"sub_380310", 0x380310, &recomp_gen::fn_sub_380310_00380310, &recomp_gen::fn_sub_380310_00380310__recomp},
    {"sub_380380", 0x380380, &recomp_gen::fn_sub_380380_00380380, &recomp_gen::fn_sub_380380_00380380__recomp},
    {"sub_3806F0", 0x3806F0, &recomp_gen::fn_sub_3806F0_003806f0, &recomp_gen::fn_sub_3806F0_003806f0__recomp},
    {"sub_3809C0", 0x3809C0, &recomp_gen::fn_sub_3809C0_003809c0, &recomp_gen::fn_sub_3809C0_003809c0__recomp},
    {"sub_380A30", 0x380A30, &recomp_gen::fn_sub_380A30_00380a30, &recomp_gen::fn_sub_380A30_00380a30__recomp},
    {"sub_380D70", 0x380D70, &recomp_gen::fn_sub_380D70_00380d70, &recomp_gen::fn_sub_380D70_00380d70__recomp},
    {"sub_3810A0", 0x3810A0, &recomp_gen::fn_sub_3810A0_003810a0, &recomp_gen::fn_sub_3810A0_003810a0__recomp},
    {"sub_381110", 0x381110, &recomp_gen::fn_sub_381110_00381110, &recomp_gen::fn_sub_381110_00381110__recomp},
    {"sub_381280", 0x381280, &recomp_gen::fn_sub_381280_00381280, &recomp_gen::fn_sub_381280_00381280__recomp},
    {"sub_3814D0", 0x3814D0, &recomp_gen::fn_sub_3814D0_003814d0, &recomp_gen::fn_sub_3814D0_003814d0__recomp},
    {"sub_381540", 0x381540, &recomp_gen::fn_sub_381540_00381540, &recomp_gen::fn_sub_381540_00381540__recomp},
    {"sub_3819B0", 0x3819B0, &recomp_gen::fn_sub_3819B0_003819b0, &recomp_gen::fn_sub_3819B0_003819b0__recomp},
    {"sub_381BF0", 0x381BF0, &recomp_gen::fn_sub_381BF0_00381bf0, &recomp_gen::fn_sub_381BF0_00381bf0__recomp},
    {"sub_381C60", 0x381C60, &recomp_gen::fn_sub_381C60_00381c60, &recomp_gen::fn_sub_381C60_00381c60__recomp},
    {"sub_3820E0", 0x3820E0, &recomp_gen::fn_sub_3820E0_003820e0, &recomp_gen::fn_sub_3820E0_003820e0__recomp},
    {"sub_382320", 0x382320, &recomp_gen::fn_sub_382320_00382320, &recomp_gen::fn_sub_382320_00382320__recomp},
    {"sub_382390", 0x382390, &recomp_gen::fn_sub_382390_00382390, &recomp_gen::fn_sub_382390_00382390__recomp},
    {"sub_382500", 0x382500, &recomp_gen::fn_sub_382500_00382500, &recomp_gen::fn_sub_382500_00382500__recomp},
    {"sub_3826F0", 0x3826F0, &recomp_gen::fn_sub_3826F0_003826f0, &recomp_gen::fn_sub_3826F0_003826f0__recomp},
    {"sub_382760", 0x382760, &recomp_gen::fn_sub_382760_00382760, &recomp_gen::fn_sub_382760_00382760__recomp},
    {"sub_382840", 0x382840, &recomp_gen::fn_sub_382840_00382840, &recomp_gen::fn_sub_382840_00382840__recomp},
    {"sub_382C10", 0x382C10, &recomp_gen::fn_sub_382C10_00382c10, &recomp_gen::fn_sub_382C10_00382c10__recomp},
    {"sub_382C80", 0x382C80, &recomp_gen::fn_sub_382C80_00382c80, &recomp_gen::fn_sub_382C80_00382c80__recomp},
    {"sub_382D60", 0x382D60, &recomp_gen::fn_sub_382D60_00382d60, &recomp_gen::fn_sub_382D60_00382d60__recomp},
    {"sub_382EC0", 0x382EC0, &recomp_gen::fn_sub_382EC0_00382ec0, &recomp_gen::fn_sub_382EC0_00382ec0__recomp},
    {"sub_382F30", 0x382F30, &recomp_gen::fn_sub_382F30_00382f30, &recomp_gen::fn_sub_382F30_00382f30__recomp},
    {"sub_383360", 0x383360, &recomp_gen::fn_sub_383360_00383360, &recomp_gen::fn_sub_383360_00383360__recomp},
    {"sub_383810", 0x383810, &recomp_gen::fn_sub_383810_00383810, &recomp_gen::fn_sub_383810_00383810__recomp},
    {"sub_383880", 0x383880, &recomp_gen::fn_sub_383880_00383880, &recomp_gen::fn_sub_383880_00383880__recomp},
    {"sub_383D80", 0x383D80, &recomp_gen::fn_sub_383D80_00383d80, &recomp_gen::fn_sub_383D80_00383d80__recomp},
    {"sub_384060", 0x384060, &recomp_gen::fn_sub_384060_00384060, &recomp_gen::fn_sub_384060_00384060__recomp},
    {"sub_3840D0", 0x3840D0, &recomp_gen::fn_sub_3840D0_003840d0, &recomp_gen::fn_sub_3840D0_003840d0__recomp},
    {"sub_384370", 0x384370, &recomp_gen::fn_sub_384370_00384370, &recomp_gen::fn_sub_384370_00384370__recomp},
    {"sub_3844B0", 0x3844B0, &recomp_gen::fn_sub_3844B0_003844b0, &recomp_gen::fn_sub_3844B0_003844b0__recomp},
    {"sub_384520", 0x384520, &recomp_gen::fn_sub_384520_00384520, &recomp_gen::fn_sub_384520_00384520__recomp},
    {"sub_384780", 0x384780, &recomp_gen::fn_sub_384780_00384780, &recomp_gen::fn_sub_384780_00384780__recomp},
    {"sub_3849E0", 0x3849E0, &recomp_gen::fn_sub_3849E0_003849e0, &recomp_gen::fn_sub_3849E0_003849e0__recomp},
    {"sub_384A50", 0x384A50, &recomp_gen::fn_sub_384A50_00384a50, &recomp_gen::fn_sub_384A50_00384a50__recomp},
    {"sub_384D30", 0x384D30, &recomp_gen::fn_sub_384D30_00384d30, &recomp_gen::fn_sub_384D30_00384d30__recomp},
    {"sub_3851F0", 0x3851F0, &recomp_gen::fn_sub_3851F0_003851f0, &recomp_gen::fn_sub_3851F0_003851f0__recomp},
    {"sub_385260", 0x385260, &recomp_gen::fn_sub_385260_00385260, &recomp_gen::fn_sub_385260_00385260__recomp},
    {"sub_385520", 0x385520, &recomp_gen::fn_sub_385520_00385520, &recomp_gen::fn_sub_385520_00385520__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (the random worlds; the editor worlds below build there).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(events3): every body equals its recompiled body on random worlds") {
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


// ===== The slice's own worlds: built editor records, the menus over frames of pad input, the live dorm event =======
namespace {

namespace rg = p3fes::recomp_gen;
namespace ev = p3fes::game::evt;
namespace ev2 = p3fes::game::evt2;
namespace ev3 = p3fes::game::evt3;

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
f32 rdf(Machine& m, u32 va) {
    f32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void wr32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wr16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void wr8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wrf(Machine& m, u32 va, f32 v) { std::memcpy(m.at(va), &v, 4); }
void wrstr(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
s32 v0_of(const SiPair& p) { return static_cast<s32>(p.hw.recomp.gpr[GPR_V0].u64[0]); }

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

std::string guest_string(EEContext& ctx, u64 va) {
    std::string s;
    for (u32 a = static_cast<u32>(va); s.size() < 255; ++a) {
        const char ch = static_cast<char>(ctx.memory->read<u8>(a));
        if (ch == 0) break;
        s += ch;
    }
    return s;
}

// The callees the bodies can reach that this test library does not emit (tools: the pseudocode reference's callee
// lists, walked through every emitted function) -- recorders; the ones below them get their own stand-ins.
struct Callee {
    u32 va;
    const char* name;
};
const Callee kRecorded[] = {
    {0x1A0430u, "sub_1A0430"}, {0x1A0D00u, "sub_1A0D00"}, {0x1A0D40u, "sub_1A0D40"}, {0x1A0D80u, "sub_1A0D80"},
    {0x1A1150u, "sub_1A1150"}, {0x1A1190u, "sub_1A1190"}, {0x1A11D0u, "sub_1A11D0"}, {0x1A4510u, "sub_1A4510"},
    {0x3B7460u, "sub_3B7460"}, {0x3B79A0u, "sub_3B79A0"}, {0x3B7AC0u, "sub_3B7AC0"}, {0x3B8310u, "sub_3B8310"},
    {0x3BB280u, "sub_3BB280"}, {0x3BB9B0u, "sub_3BB9B0"}, {0x3BBAA0u, "sub_3BBAA0"}, {0x3BBC90u, "sub_3BBC90"},
    {0x464020u, "sub_464020"},
};
constexpr u32 kSceneSlot = 0x7CD540u;  // the scene record pointer sub_3B5D00 / sub_3B5D10 / sub_3B5DF0 read (+8: models)
constexpr u32 kTextFn = 0x1050E0u;     // the debug text queue (x / y floats in $a0, colour $a1, text $a2)
constexpr u32 kCells = kWorld + 0x9000u;  // the list-box item values sub_1A41B0 / sub_1A42F0 answer with

u32 scene_models(EEContext& ctx) {
    const u32 scene = ctx.memory->read<u32>(kSceneSlot);
    return scene ? ctx.memory->read<u32>(scene + 8) : 0u;
}
// Host walk of one model class of the scene table (the heads at table + 4 * class, chained at +248).
std::vector<u32> class_models(Machine& m, u32 cls) {
    std::vector<u32> out;
    const u32 scene = rd32(m, kSceneSlot);
    const u32 table = scene ? rd32(m, scene + 8) : 0u;
    if (!table || cls >= 22) return out;
    for (u32 r = rd32(m, table + 4 * cls); r != 0 && out.size() < 512; r = rd32(m, r + 248)) out.push_back(r);
    return out;
}

WorldSetup editor_world() {
    return [](StandInWorld& w) {
        install_standard(w);
        for (const Callee& c : kRecorded) w.si.install_recorder(c.va, c.name, 0);
        // the screen: every line the menus draw, as "text" (both bodies' logs are compared)
        w.si.install(kTextFn, "sub_1050E0 (debug text)", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = guest_string(ctx, c.args[2]); });
        // the list-box value getters: a pointer to item i's value cell
        w.si.install(0x1A41B0u, "sub_1A41B0 (box int)", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = kCells + 4u * (static_cast<u32>(c.args[1]) & 15u); });
        w.si.install(0x1A42F0u, "sub_1A42F0 (box float)", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = kCells + 0x40u + 4u * (static_cast<u32>(c.args[1]) & 15u); });
        // the scene's model table (sub_3B5D00: *(scene + 8)), the class count (sub_3B5DF0), a curve row (sub_3B55B0)
        w.si.install(0x3B5D00u, "sub_3B5D00 (scene models)", [](EEContext& ctx, StandIns&, StandInCall& c) { c.v0 = sx(scene_models(ctx)); });
        w.si.install(0x3B5DF0u, "sub_3B5DF0 (class count)", [](EEContext& ctx, StandIns&, StandInCall& c) {
            const u32 table = scene_models(ctx), cls = static_cast<u32>(c.args[0]);
            u32 n = 0;
            if (table && cls < 22)
                for (u32 r = ctx.memory->read<u32>(table + 4 * cls); r != 0 && n < 512; r = ctx.memory->read<u32>(r + 248)) ++n;
            c.v0 = n;
        });
        w.si.install(0x3B55B0u, "sub_3B55B0 (curve row)", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = ev3::kCurveTable + 16u * static_cast<u32>(c.args[0]); });
    };
}
std::vector<std::string> screen(const SiPair& p) {
    std::vector<std::string> out;
    for (const StandInCall& c : p.recomp->si.log)
        if (c.va == kTextFn) out.push_back(c.text);
    return out;
}
bool shows(const std::vector<std::string>& lines, const std::string& s) {
    return std::any_of(lines.begin(), lines.end(), [&](const std::string& l) { return l.find(s) != std::string::npos; });
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

// --- a built editor world -----------------------------------------------------------------------------------------
// The work at W (kSelf, the menu on top of a one-entry stack at (2, 3), level 1), three units (the first of `type`
// with `nkeys` keys, frames 10 * i), a scene with six models (class 1: one character; class 3: two; class 8: two;
// class 10: one), the choice list, the typed name, the value editors and the condition.
constexpr u32 W = kWorld;
constexpr u32 U = kWorld + 0x1000u;   // units at U + 0xA0 * i
constexpr u32 K = kWorld + 0x2000u;   // keys at K + 0x60 * i
constexpr u32 S = kWorld + 0x6000u;   // the scene record (+8: the class table at T)
constexpr u32 T = kWorld + 0x6100u;
constexpr u32 M = kWorld + 0x7000u;   // models at M + 0x140 * i
constexpr u32 STR = kWorld + 0xA000u; // strings
constexpr u32 kModelRes[6] = {(1u << 10) | 1u, (3u << 10) | 5u, (3u << 10) | 6u, (8u << 10) | 2u, (8u << 10) | 3u, (10u << 10) | 7u};
constexpr u32 kModelClass[6] = {1, 3, 3, 8, 8, 10};
u32 unit_at(int i) { return U + 0xA0u * static_cast<u32>(i); }
u32 key_at(int i) { return K + 0x60u * static_cast<u32>(i); }
u32 model_at(int i) { return M + 0x140u * static_cast<u32>(i); }

void build_editor(Machine& m, int menu, u32 type, int nkeys, std::mt19937& rng) {
    std::memset(m.at(kWorld), 0, kWorldSize);
    wr32(m, W + ev::work::kSelf, W);
    wr32(m, W + ev2::work::kFrameCount, 300);
    wr32(m, W + ev::work::kEndFrame, 299);
    wr32(m, W + ev::work::kFrame, 40);
    wr32(m, W + ev::work::kMenuDepth, 1);
    wr16(m, W + ev::work::kMenuStack + ev3::stack::kSize + ev3::stack::kMenu, static_cast<u16>(menu));
    wr16(m, W + ev::work::kMenuStack + ev3::stack::kSize + ev3::stack::kX, 2);
    wr16(m, W + ev::work::kMenuStack + ev3::stack::kSize + ev3::stack::kY, 3);
    wr32(m, W + ev::work::kMenuId, static_cast<u32>(menu));
    wr32(m, W + ev::work::kMenuFont, 1);
    // units: `type` with keys, a camera (type 10) and a field object (type 48)
    const u32 types[3] = {type, 10, 48};
    for (int i = 0; i < 3; ++i) {
        const u32 un = unit_at(i);
        wr32(m, un + ev::unit::kType, types[i]);
        wr32(m, un + ev::unit::kName, 0xFFFFFFFFu);
        wr16(m, un + ev::unit::kResId, static_cast<u16>(kModelRes[i == 2 ? 1 : 0]));
        wr32(m, un + ev::unit::kNext, i < 2 ? unit_at(i + 1) : 0u);
        wr32(m, un + ev::unit::kPrev, i > 0 ? unit_at(i - 1) : 0u);
    }
    wr32(m, W + ev::work::kUnitHead, unit_at(0));
    wr32(m, W + ev::work::kUnitTail, unit_at(2));
    wr32(m, W + ev::work::kUnitCount, 3);
    u32 prev = 0;
    for (int i = 0; i < nkeys; ++i) {
        const u32 k = key_at(i);
        wr16(m, k + ev::key::kFrame, static_cast<u16>(10 * i));
        wr16(m, k + ev::key::kLength, static_cast<u16>(rng() % 30));
        wr32(m, k + ev::key::kName, 0xFFFFFFFFu);
        wr32(m, k + ev::key::kOwnerType, type);
        wr32(m, k + ev::key::kPrev, prev);
        if (prev) wr32(m, prev + ev::key::kNext, k);
        else wr32(m, unit_at(0) + ev::unit::kKeyHead, k);
        prev = k;
    }
    wr32(m, unit_at(0) + ev::unit::kKeyTail, prev);
    wr32(m, unit_at(0) + ev::unit::kKeyCount, static_cast<u32>(nkeys));
    wr32(m, W + ev::work::kEdUnit, unit_at(0));
    // the scene's models
    wr32(m, kSceneSlot, S);
    wr32(m, S + 8, T);
    u32 last[22] = {};
    for (int i = 0; i < 6; ++i) {
        const u32 mo = model_at(i), c = kModelClass[i];
        wr16(m, mo, static_cast<u16>(kModelRes[i]));
        for (int j = 0; j < 3; ++j) wrf(m, mo + 4 + 4 * j, static_cast<f32>(10 * i + j));
        if (last[c]) {
            wr32(m, last[c] + 248, mo);
            wr32(m, mo + 252, last[c]);
        } else {
            wr32(m, T + 4 * c, mo);
        }
        last[c] = mo;
    }
    wr32(m, W + ev3::work::kEdRotModel, model_at(0));
    // the choice list, the name, the editors, the condition
    wrstr(m, STR, "TEST CHOICE");
    wrstr(m, STR + 0x20, "FIRST");
    wrstr(m, STR + 0x30, "SECOND");
    wrstr(m, STR + 0x40, "THIRD");
    wr32(m, STR + 0x80, STR + 0x20);
    wr32(m, STR + 0x84, STR + 0x30);
    wr32(m, STR + 0x88, STR + 0x40);
    wr32(m, W + ev2::work::kEdChoiceTitle, STR);
    wr32(m, W + ev2::work::kEdChoiceItems, STR + 0x80);
    wr32(m, W + ev2::work::kEdChoiceCount, 3);
    wrstr(m, W + ev3::work::kEdName, "AB");
    wrstr(m, W + ev3::work::kEdNameExt, "PM1");
    wr32(m, W + ev2::work::kEdValue, 5);
    wr32(m, W + ev2::work::kEdValueMin, 0);
    wr32(m, W + ev2::work::kEdValueMax, 20);
    wrf(m, W + ev2::work::kEdValueF, 1.5f);
    wrf(m, W + ev3::work::kEdValueFMin, 0.0f);
    wrf(m, W + ev3::work::kEdValueFMax, 10.0f);
    wr16(m, W + ev2::work::kEdCondition, 0x10);
    wr16(m, W + ev2::work::kEdCondition + 2, 1);
    wr8(m, W + ev2::work::kEdCondition + 4, 2);
    wr8(m, W + ev2::work::kEdCondition + 6, 0);
    wr16(m, ev3::kEventMajor, 401);
    wr16(m, ev3::kEventMinor, 2);
    for (int i = 0; i < 4; ++i) wr8(m, 0x7E095Eu + static_cast<u32>(i), 0x80);  // the analog sticks centred
    wr32(m, W + ev3::work::kEdToolModel, model_at(0));
    for (int i = 0; i < 16; ++i) wr32(m, kCells + 4u * static_cast<u32>(i), rng() % 64);
    for (int i = 0; i < 16; ++i) wrf(m, kCells + 0x40u + 4u * static_cast<u32>(i), static_cast<f32>(rng() % 64));
}

struct Pad {
    u16 pressed, repeat, held;
    const char* name;
};
const Pad kPads[] = {{0, 0, 0, "none"},           {0x4000, 0x4000, 0x4000, "down"},  {0x4000, 0x4000, 0x4000, "down"},
                     {0x2000, 0x2000, 0x2000, "right"}, {0x2000, 0x2000, 0x2000, "right"}, {8, 8, 8, "R1"},
                     {0x8000, 0x8000, 0x8000, "left"}, {4, 4, 4, "L1"},          {0x1000, 0x1000, 0x1000, "up"},
                     {2, 2, 2, "R2"},                  {1, 1, 1, "L2"},          {0x80, 0x80, 0x80, "square"},
                     {0x2000, 0x2000, 0x2010, "triangle+right"}, {0x100, 0x100, 0x100, "select"},
                     {0x800, 0x800, 0x800, "start"}, {0x4000, 0x4000, 0x4000, "down"}, {0x40, 0x40, 0x40, "confirm"},
                     {0x20, 0x20, 0x20, "cancel"}};
void set_pad(Machine& m, const Pad& p) {
    wr16(m, ev3::kPadPressed, p.pressed);
    wr16(m, ev3::kPadRepeat, p.repeat);
    wr16(m, ev3::kPadHeld, p.held);
}

struct Menu {
    int id;
    Fn update, update_r;
    u32 type;     // the editor unit's type the menu is driven with
    int rows;     // kEdSubChoice's range [0, rows - 1] (0: the menu does not use it)
    bool confirm_one;  // confirm returns 1 / cancel returns -1
};
#define MENU(id, fn, type, rows, one) {id, &rg::fn_##fn, &rg::fn_##fn##__recomp, type, rows, one}
const Menu kMenus[] = {
    MENU(1, sub_37ABD0_0037abd0, 1, 0, false),  MENU(2, sub_37A640_0037a640, 1, 0, false),
    MENU(3, sub_37A2B0_0037a2b0, 1, 0, false),  MENU(4, sub_379F30_00379f30, 1, 0, false),
    MENU(5, sub_3798F0_003798f0, 1, 0, false),  MENU(6, sub_375D70_00375d70, 1, 0, true),
    MENU(7, sub_375900_00375900, 1, 0, true),   MENU(8, sub_375590_00375590, 1, 0, true),
    MENU(9, sub_375000_00375000, 1, 0, true),   MENU(10, sub_374AF0_00374af0, 1, 0, false),
    MENU(11, sub_373590_00373590, 6, 0, false), MENU(13, sub_371DD0_00371dd0, 4, 0, false),
    MENU(14, sub_372790_00372790, 1, 0, true),  MENU(15, sub_36FDA0_0036fda0, 48, 0, false),
    MENU(16, sub_3709D0_003709d0, 1, 0, false), MENU(17, sub_3715B0_003715b0, 1, 0, false),
    MENU(23, sub_37AFC0_0037afc0, 1, 0, true),  MENU(24, sub_37B5D0_0037b5d0, 10, 0, true),
    MENU(25, sub_37BE50_0037be50, 1, 4, false), MENU(26, sub_373700_00373700, 1, 0, false),
    MENU(27, sub_37CAF0_0037caf0, 1, 8, true),  MENU(28, sub_37D5D0_0037d5d0, 1, 0, false),
    MENU(29, sub_37E1B0_0037e1b0, 1, 2, true),  MENU(30, sub_37EAD0_0037ead0, 1, 0, true),
    MENU(31, sub_37F3D0_0037f3d0, 1, 3, true),  MENU(32, sub_37FAE0_0037fae0, 34, 8, true),
    MENU(33, sub_380200_00380200, 41, 3, true), MENU(34, sub_3806F0_003806f0, 34, 6, true),
    MENU(35, sub_380D70_00380d70, 1, 4, true),  MENU(36, sub_381280_00381280, 34, 2, true),
    MENU(37, sub_3819B0_003819b0, 41, 7, true), MENU(38, sub_3820E0_003820e0, 34, 8, true),
    MENU(39, sub_382500_00382500, 34, 3, true), MENU(40, sub_382840_00382840, 33, 0, true),
    MENU(41, sub_382D60_00382d60, 41, 0, true), MENU(42, sub_383360_00383360, 48, 5, true),
    MENU(43, sub_383D80_00383d80, 41, 8, true), MENU(44, sub_384370_00384370, 1, 4, true),
    MENU(45, sub_384780_00384780, 41, 0, true), MENU(46, sub_384D30_00384d30, 1, 4, true),
    MENU(47, sub_385520_00385520, 19, 4, true),
};

// The documented ranges of the key-parameter menus: kParam index -> [lo, hi] (a value the frame changed must be in it).
struct Range {
    int menu, param;
    s32 lo, hi;
};
const Range kRanges[] = {
    {29, 0, 0, 1},    {31, 0, 0, 1},    {31, 1, 0, 1},    {32, 0, 0, 100},  {32, 1, 0, 100},  {32, 2, 0, 100},
    {32, 3, 0, 100},  {32, 4, 0, 30000}, {32, 5, 0, 30000}, {32, 6, 0, 30000}, {32, 7, 0, 30000}, {34, 0, 0, 30000},
    {34, 1, 0, 30000}, {34, 2, 0, 30000}, {34, 3, 0, 30000}, {34, 4, 0, 30000}, {34, 5, 0, 30000}, {35, 0, 0, 1},
    {35, 1, 0, 2},    {35, 2, 0, 9},    {35, 3, 0, 0xFFFF}, {36, 0, 0, 30000}, {36, 1, 0, 30000}, {37, 0, 0, 1},
    {37, 1, 0, 7},    {37, 2, 0, 20},   {37, 3, 0, 20},   {37, 4, 0, 20},   {37, 5, 0, 20},   {38, 0, 0, 8},
    {38, 1, 0, 250},  {38, 2, 0, 250},  {38, 3, 0, 250},  {38, 4, 0, 60000}, {38, 5, 0, 60000}, {38, 6, 0, 60000},
    {38, 7, 0, 60000}, {39, 0, 0, 60000}, {39, 1, 0, 60000}, {39, 2, 0, 60000}, {41, 0, 0, 30000}, {42, 4, 10, 500},
    {43, 0, 0, 30000}, {43, 1, 0, 30000}, {43, 2, 0, 30000}, {43, 3, 0, 30000}, {43, 5, 0, 30000}, {43, 6, 0, 30000},
    {43, 7, 0, 1},    {45, 0, 0, 3},    {45, 2, 0, 29},   {46, 8, 0, 1},    {46, 9, 0, 3},    {46, 10, 0, 60},
    {46, 11, 0, 60},  {47, 0, 0, 1},    {47, 1, 0, 1},    {47, 2, 0, 4},    {47, 3, 0, 127},  {27, 0, 0, 2},
    {27, 1, 0, 1},    {16, 6, 10, 500}, {16, 7, 10, 500},
};
s32 param(Machine& m, int i) { return static_cast<s32>(rd32(m, W + ev3::work::kParam0 + 4 * i)); }

}  // namespace

namespace {
// One frame on the live scene. The editor was made for its own scenes; on a play-mode scene some screens make the
// ORIGINAL itself fault (a camera / model record the event never loaded): then both bodies must stop at the same
// instruction -- each runs alone from the same bytes (fault_of) -- and the caller ends that sequence.
struct LiveFrame {
    bool faulted = false;
    std::vector<std::string> screen;
    s32 v0 = 0;
};
LiveFrame live_frame(Machine& m, Fn hand, Fn recomp, const Args& a, u32 seed, const char* what, const HwCheck& hw) {
    const std::vector<u8> ram(m.at(0), m.at(0) + EEMemory::kMainRamSize);
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    auto restore = [&] {
        std::memcpy(m.at(0), ram.data(), ram.size());
        std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    };
    const std::string fr = fault_of([&] { run_pair_si(m, recomp, recomp, a, seed, what, hw, editor_world()); });
    restore();
    LiveFrame out;
    if (!fr.empty()) {
        const std::string fh = fault_of([&] { run_pair_si(m, hand, hand, a, seed, what, hw, editor_world()); });
        restore();
        INFO(what << ": the original stops at " << fr);
        CHECK(fh == fr);
        out.faulted = true;
        return out;
    }
    const SiPair p = run_pair_si(m, hand, recomp, a, seed, what, hw, editor_world());
    out.screen = screen(p);
    out.v0 = v0_of(p);
    return out;
}
}  // namespace

TEST_CASE("game(events3): every menu on a built editor world, frame by frame with pad input") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE3E3001u};
    int pairs = 0, checked = 0, frames_total = 0;
    std::size_t lines = 0;
    for (const Menu& mn : kMenus) {
        build_editor(m, mn.id, mn.type, 6, rng);
        INFO("menu " << mn.id);
        // inactive (another menu on top): the menu only draws -- 0 (or -1 where it needs what is missing)
        wr32(m, W + ev::work::kMenuId, 0);
        set_pad(m, kPads[16]);
        {
            std::vector<s32> before;
            for (int i = 0; i < 12; ++i) before.push_back(param(m, i));
            const SiPair p = run_pair_si(m, mn.update, mn.update_r, {2, 3, sx(W), 0}, rng(), "menu inactive", hw, editor_world());
            ++pairs;
            CHECK((v0_of(p) == 0 || v0_of(p) == -1));
            if (mn.id != 26)  // menu 26 applies its tool whether or not it is on top
                for (int i = 0; i < 12; ++i) CHECK(param(m, i) == before[static_cast<std::size_t>(i)]);
            checked += 13;
        }
        wr32(m, W + ev::work::kMenuId, static_cast<u32>(mn.id));
        // on top: 36 frames cycling through the pad table
        for (int f = 0; f < 36; ++f) {
            const Pad& pad = kPads[static_cast<std::size_t>(f) % (sizeof kPads / sizeof kPads[0])];
            set_pad(m, pad);
            std::vector<s32> before;
            for (int i = 0; i < 12; ++i) before.push_back(param(m, i));
            const SiPair p = run_pair_si(m, mn.update, mn.update_r, {2, 3, sx(W), 0}, rng(), "menu frame", hw, editor_world());
            ++pairs;
            ++frames_total;
            lines += screen(p).size();
            INFO("frame " << f << " pad " << pad.name << " result " << v0_of(p));
            if (mn.confirm_one && pad.pressed == 0x40) {
                CHECK(v0_of(p) == 1);
                ++checked;
            }
            if (mn.confirm_one && pad.pressed == 0x20) {
                CHECK(v0_of(p) == -1);
                ++checked;
            }
            if (mn.rows > 0) {
                const s32 row = static_cast<s32>(rd32(m, W + ev2::work::kEdSubChoice));
                CHECK(row >= 0);
                CHECK(row < mn.rows);
                ++checked;
            }
            for (const Range& r : kRanges) {
                if (r.menu != mn.id) continue;
                const s32 v = param(m, r.param);
                if (v == before[static_cast<std::size_t>(r.param)]) continue;
                INFO("kParam" << r.param << " = " << v);
                CHECK(v >= r.lo);
                CHECK(v <= r.hi);
                ++checked;
            }
        }
    }
    MESSAGE("menus: " << sizeof kMenus / sizeof kMenus[0] << " menus, " << frames_total << " frames, " << pairs << " pairs, "
                      << checked << " rules checked, " << lines << " text lines compared");
}

TEST_CASE("game(events3): the value, condition, event-number, name and list menus follow their rules") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE3E3002u};
    int pairs = 0;
    auto frame = [&](int menu, Fn h, Fn r, const Pad& pad) {
        wr32(m, W + ev::work::kMenuId, static_cast<u32>(menu));
        set_pad(m, pad);
        SiPair p = run_pair_si(m, h, r, {2, 3, sx(W), 0}, rng(), "rule frame", hw, editor_world());
        ++pairs;
        return p;
    };
    const Pad none{0, 0, 0, "none"}, right{0x2000, 0x2000, 0x2000, "right"}, left{0x8000, 0x8000, 0x8000, "left"},
        up{0x1000, 0x1000, 0x1000, "up"}, down{0x4000, 0x4000, 0x4000, "down"}, l1{4, 4, 4, "L1"}, r1{8, 8, 8, "R1"},
        r2{2, 2, 2, "R2"}, square{0x80, 0x80, 0x80, "square"}, confirm{0x40, 0x40, 0x40, "confirm"};
    auto value = [&] { return static_cast<s32>(rd32(m, W + ev2::work::kEdValue)); };
    // menu 7 [evtMenuIntValue]: left / right -+1, up / down -+10, clamped to [kEdValueMin, kEdValueMax]
    build_editor(m, 7, 1, 2, rng);
    {
        const std::pair<Pad, s32> steps[] = {{right, 6}, {down, 16}, {down, 20}, {left, 19}, {up, 9}, {up, 0}, {left, 0}};
        for (const auto& [pad, want] : steps) {
            const SiPair p = frame(7, rg::fn_sub_375900_00375900, rg::fn_sub_375900_00375900__recomp, pad);
            INFO("int editor after " << pad.name);
            CHECK(value() == want);
            CHECK(v0_of(p) == 0);
        }
        // the screen shows the value (drawn before the frame's input) and the help lines
        const SiPair p = frame(7, rg::fn_sub_375900_00375900, rg::fn_sub_375900_00375900__recomp, none);
        CHECK(shows(screen(p), "VALUE CHANGE."));
        CHECK(shows(screen(p), " RR  = ENTER"));
        CHECK(shows(screen(p), "     0"));
    }
    // menu 6 [evtMenuFrameValue]: L1 / R1 -+100, square = the current frame; start held makes it the current frame
    build_editor(m, 6, 1, 2, rng);
    wr32(m, W + ev2::work::kEdValueMax, 299);
    {
        frame(6, rg::fn_sub_375D70_00375d70, rg::fn_sub_375D70_00375d70__recomp, r1);
        CHECK(value() == 105);
        frame(6, rg::fn_sub_375D70_00375d70, rg::fn_sub_375D70_00375d70__recomp, l1);
        CHECK(value() == 5);
        frame(6, rg::fn_sub_375D70_00375d70, rg::fn_sub_375D70_00375d70__recomp, square);
        CHECK(value() == 40);  // kFrame
        frame(6, rg::fn_sub_375D70_00375d70, rg::fn_sub_375D70_00375d70__recomp, Pad{0x2000, 0x2000, 0x800, "right+start"});
        CHECK(value() == 41);
        CHECK(rd32(m, W + ev::work::kFrame) == 41u);  // the timeline follows
    }
    // menu 8 [evtMenuFloatValue]: -+0.1 / -+1.0, clamped to [+392, +396]
    build_editor(m, 8, 1, 2, rng);
    {
        const std::pair<Pad, f32> steps[] = {{right, 1.6f}, {down, 2.6f}, {up, 1.6f}, {left, 1.5f}, {up, 0.5f}, {up, 0.0f}};
        for (const auto& [pad, want] : steps) {
            frame(8, rg::fn_sub_375590_00375590, rg::fn_sub_375590_00375590__recomp, pad);
            INFO("float editor after " << pad.name);
            CHECK(std::fabs(rdf(m, W + ev2::work::kEdValueF) - want) < 1e-4f);
        }
    }
    // menu 14 [evtMenuCondition]: type / number / value / bank with the type's limits
    build_editor(m, 14, 1, 2, rng);
    {
        auto cond = [&](int i) { return i == 2 ? static_cast<s32>(static_cast<s8>(rd8(m, W + ev2::work::kEdCondition + 4))) : i == 3 ? static_cast<s32>(rd8(m, W + ev2::work::kEdCondition + 6)) : static_cast<s32>(rd16(m, W + ev2::work::kEdCondition + 2 * i)); };
        // row 1 (number, type 2: flag 0..4999): R2 x 60 reaches the top
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, down);
        CHECK(rd32(m, W + ev3::work::kEdCondCursor) == 1u);
        for (int i = 0; i < 60; ++i) frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, r2);
        CHECK(cond(0) == 4999);
        // row 2 (value, type 2: 0..1)
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, down);
        for (int i = 0; i < 3; ++i) frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, right);
        CHECK(cond(1) == 1);
        // row 3 (bank 0..2, wrapping)
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, down);
        for (int i = 0; i < 4; ++i) frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, right);
        CHECK(cond(3) == 1);
        // row 0: the type steps and clears the other three; type 1 limits the counter to 0..9
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, down);
        CHECK(rd32(m, W + ev3::work::kEdCondCursor) == 0u);
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, left);
        CHECK(cond(2) == 1);
        CHECK((cond(0) == 0 && cond(1) == 0 && cond(3) == 0));
        frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, down);
        for (int i = 0; i < 3; ++i) frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, r2);
        CHECK(cond(0) == 9);
        const SiPair p = frame(14, rg::fn_sub_372790_00372790, rg::fn_sub_372790_00372790__recomp, confirm);
        CHECK(v0_of(p) == 1);
        CHECK(shows(screen(p), "FLAG COMPARE MENU"));
        CHECK(shows(screen(p), "  (CMP VALUE)"));
    }
    // menu 9 [evtMenuEventNumber]: major 0..999 / minor 1..999 in 1 / 10 / 100 steps; the header names the files
    build_editor(m, 9, 1, 2, rng);
    {
        const SiPair p0 = frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, none);
        CHECK(shows(screen(p0), "[E401_002.PM1+2+3]"));
        frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, r2);
        CHECK(rd16(m, ev3::kEventMajor) == 501);
        for (int i = 0; i < 6; ++i) frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, r2);
        CHECK(rd16(m, ev3::kEventMajor) == 999);
        frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, down);  // the minor
        CHECK(rd32(m, W + ev3::work::kEdKbdRow) == 1u);
        frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, left);
        frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, left);
        CHECK(rd16(m, ev3::kEventMinor) == 1);  // never below 1
        frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, l1);
        CHECK(rd16(m, ev3::kEventMinor) == 1);
        const SiPair p1 = frame(9, rg::fn_sub_375000_00375000, rg::fn_sub_375000_00375000__recomp, confirm);
        CHECK(v0_of(p1) == 1);
        CHECK(shows(screen(p1), "[E999_001.PM1+2+3]"));
    }
    // menu 3 [evtMenuNameEntry]: confirm types the grid character, [B] deletes, [OK] accepts a non-empty name
    build_editor(m, 3, 1, 2, rng);
    {
        frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, confirm);  // row 0 col 0: '1'
        CHECK(std::string(reinterpret_cast<const char*>(m.at(W + ev3::work::kEdName))) == "AB1");
        frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, right);
        frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, down);
        frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, confirm);  // row 1 col 1: 'C'
        CHECK(std::string(reinterpret_cast<const char*>(m.at(W + ev3::work::kEdName))) == "AB1C");
        const SiPair p = frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, none);
        CHECK(shows(screen(p), "[AB1C.PM1]"));
        // to row 3: col 5 is [B] (delete), col 8 is K of [OK] (accept)
        wr32(m, W + ev3::work::kEdKbdRow, 3);
        wr32(m, W + ev3::work::kEdKbdCol, 5);
        frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, confirm);
        CHECK(std::string(reinterpret_cast<const char*>(m.at(W + ev3::work::kEdName))) == "AB1");
        wr32(m, W + ev3::work::kEdKbdCol, 8);
        const SiPair ok = frame(3, rg::fn_sub_37A2B0_0037a2b0, rg::fn_sub_37A2B0_0037a2b0__recomp, confirm);
        CHECK(v0_of(ok) == 1);
    }
    // menu 2 [evtMenuChoice]: the title and the items; confirm returns the cursor helper's result
    build_editor(m, 2, 1, 2, rng);
    {
        const SiPair p = frame(2, rg::fn_sub_37A640_0037a640, rg::fn_sub_37A640_0037a640__recomp, down);
        CHECK(shows(screen(p), "TEST CHOICE"));
        CHECK(shows(screen(p), "SECOND"));
        CHECK(rd32(m, W + ev2::work::kEdChoice) == 1u);
    }
    // menu 5 [evtMenuKeyList]: every key's line plus the new-frame line; square = -2; the copy / paste logs
    build_editor(m, 5, 1, 6, rng);
    {
        const SiPair p = frame(5, rg::fn_sub_3798F0_003798f0, rg::fn_sub_3798F0_003798f0__recomp, none);
        CHECK(shows(screen(p), "----- NEW FRAME -----"));
        const SiPair d = frame(5, rg::fn_sub_3798F0_003798f0, rg::fn_sub_3798F0_003798f0__recomp, square);
        CHECK(v0_of(d) == -2);
        const SiPair c = frame(5, rg::fn_sub_3798F0_003798f0, rg::fn_sub_3798F0_003798f0__recomp, Pad{0x100, 0x100, 0x100, "select"});
        bool copied = false;
        for (const StandInCall& cl : c.recomp->si.log) copied |= cl.text == "copy\n";
        CHECK(copied);
    }
    // menu 4's row draw makes the cursor's unit the editor unit (when menu 4 is on top)
    build_editor(m, 4, 1, 6, rng);
    {
        wr32(m, W + ev3::work::kEdUnitPos, 2);
        frame(4, rg::fn_sub_379F30_00379f30, rg::fn_sub_379F30_00379f30__recomp, none);
        CHECK(rd32(m, W + ev::work::kEdUnit) == unit_at(2));
        CHECK(rd32(m, W + ev::work::kEdKeyIndex) == 0u);
    }
    // menu 17 [evtMenuModelPick]: the scene's class-3 then class-1 models after the three fixed rows
    build_editor(m, 17, 1, 2, rng);
    {
        const SiPair p = frame(17, rg::fn_sub_3715B0_003715b0, rg::fn_sub_3715B0_003715b0__recomp, none);
        const auto sc = screen(p);
        CHECK(shows(sc, "DISABLE"));
        CHECK(shows(sc, "UNIT ALL"));
        char buf[32];
        for (int i : {1, 2, 0}) {
            std::snprintf(buf, sizeof buf, "resId 0x%x", kModelRes[i]);
            CHECK(shows(sc, buf));
        }
    }
    // menu 23 [evtMenuPosChange]: row 2 steps through the class-8 models (and back to none past the end)
    build_editor(m, 23, 1, 2, rng);
    {
        wr32(m, W + ev3::work::kEdPosCursor, 2);
        frame(23, rg::fn_sub_37AFC0_0037afc0, rg::fn_sub_37AFC0_0037afc0__recomp, right);
        CHECK((rd32(m, W + ev2::work::kEdValue) >> 16) == kModelRes[3]);
        frame(23, rg::fn_sub_37AFC0_0037afc0, rg::fn_sub_37AFC0_0037afc0__recomp, right);
        CHECK((rd32(m, W + ev2::work::kEdValue) >> 16) == kModelRes[4]);
        frame(23, rg::fn_sub_37AFC0_0037afc0, rg::fn_sub_37AFC0_0037afc0__recomp, right);
        CHECK((rd32(m, W + ev2::work::kEdValue) >> 16) == 0u);
        frame(23, rg::fn_sub_37AFC0_0037afc0, rg::fn_sub_37AFC0_0037afc0__recomp, left);  // from none: the last one
        CHECK((rd32(m, W + ev2::work::kEdValue) >> 16) == kModelRes[4]);
    }
    // menu 10 [evtMenuResourceList]: 1 + the class's models rows, "RESID %d" each
    build_editor(m, 10, 1, 2, rng);
    {
        wr32(m, W + ev2::work::kEdResClass, 3);
        const SiPair p = frame(10, rg::fn_sub_374AF0_00374af0, rg::fn_sub_374AF0_00374af0__recomp, none);
        CHECK(shows(screen(p), "RESID  5"));
        CHECK(shows(screen(p), "RESID  6"));
    }
    // menu 40 [evtMenuFuncCurve]: picking a curve loads its four values; square stores the edited ones
    build_editor(m, 40, 33, 2, rng);
    {
        frame(40, rg::fn_sub_382840_00382840, rg::fn_sub_382840_00382840__recomp, right);
        CHECK(param(m, 0) == 1);
        for (int i = 0; i < 4; ++i) CHECK(rd32(m, W + ev3::work::kEdCurve + 4 * i) == rd32(m, ev3::kCurveTable + 16 + 4 * i));
        wrf(m, W + ev3::work::kEdCurve, 0.25f);
        frame(40, rg::fn_sub_382840_00382840, rg::fn_sub_382840_00382840__recomp, square);
        CHECK(rdf(m, ev3::kCurveTable + 16) == 0.25f);
    }
    // menu 5's key lines for every unit type: the header names the type's columns (table 0x69E1A0, titles 0x69E100),
    // and each key line goes through sub_3760A0's formatter for those column kinds (random key parameters)
    {
        int types = 0;
        std::string faulted_types;
        for (u32 type = 1; type <= 50; ++type) {
            build_editor(m, 5, type, 3, rng);
            for (int i = 0; i < 3; ++i)
                for (u32 b = 8; b < 56; ++b) wr8(m, key_at(i) + b, static_cast<u8>(rng() % 8));
            wr32(m, W + ev::work::kMenuId, 5);
            set_pad(m, none);
            const LiveFrame f = live_frame(m, rg::fn_sub_3798F0_003798f0, rg::fn_sub_3798F0_003798f0__recomp, {2, 3, sx(W), 0}, rng(), "key lines", hw);
            ++pairs;
            if (f.faulted) {
                faulted_types += " " + std::to_string(type);
                continue;
            }
            const u8 first_kind = rd8(m, ev2::kColumnTable + 12 * type + 2);
            const char* title = reinterpret_cast<const char*>(m.at(rd32(m, 0x69E100u + 4u * first_kind)));
            INFO("unit type " << type << " first column " << title);
            CHECK(shows(f.screen, title));
            CHECK(shows(f.screen, "----- NEW FRAME -----"));
            ++types;
        }
        MESSAGE("key lines: " << types << " unit types drawn; the original faults on the random keys of types:" << faulted_types);
        CHECK(types >= 40);
    }
    // menu 26 [evtMenuToolApply]: every tool kind once (the list-box items read into kEdParams)
    for (u32 kind = 0; kind < 19; ++kind) {
        if (kind == 4) continue;  // kind 4 moves a real model's RW frames (sub_38B550): the live test does it
        build_editor(m, 26, 1, 2, rng);
        wr32(m, W + ev2::work::kEdValue, kind);
        INFO("tool kind " << kind);
        const SiPair p = frame(26, rg::fn_sub_373700_00373700, rg::fn_sub_373700_00373700__recomp, none);
        CHECK(v0_of(p) == 0);  // the tool keeps running without confirm / cancel / start
        if (kind == 3 || kind == 11 || kind == 17) CHECK(param(m, 0) == static_cast<s32>(rd32(m, kCells)));
    }
    MESSAGE("rules: " << pairs << " pairs");
}

namespace {
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
}  // namespace


TEST_CASE("game(events3): the editor on the live dorm event -- unit list, key rows, settings, resources, models") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xE3E3003u};
    int pairs = 0, snapshots = 0, keys_drawn = 0, faults = 0;
    std::size_t lines = 0;
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
        std::vector<u32> units;
        for (u32 un = rd32(m, w + ev::work::kUnitHead); un != 0 && units.size() < 400; un = rd32(m, un + ev::unit::kNext)) units.push_back(un);
        REQUIRE(!units.empty());
        CHECK(units.size() == rd32(m, w + ev::work::kUnitCount));
        auto editor = [&](int menu) {
            fresh();
            wr32(m, w + ev::work::kMenuDepth, 1);
            wr16(m, w + ev::work::kMenuStack + ev3::stack::kSize + ev3::stack::kMenu, static_cast<u16>(menu));
            wr32(m, w + ev::work::kMenuId, static_cast<u32>(menu));
            wr32(m, w + ev::work::kMenuFont, 1);
            set_pad(m, Pad{0, 0, 0, "none"});
            for (int i = 0; i < 4; ++i) wr8(m, 0x7E095Eu + static_cast<u32>(i), 0x80);
        };
        auto run = [&](Fn h, Fn r, const char* what) {
            LiveFrame f = live_frame(m, h, r, {2, 3, sx(w), 0}, rng(), what, hw);
            ++pairs;
            faults += f.faulted ? 1 : 0;
            lines += f.screen.size();
            return f;
        };
        // menu 4: the unit list with the cursor on every unit in turn (the row under it becomes the editor unit and the
        // camera looks at its model), then the cursor walking down from the top over the frames
        int listed = 0;
        for (std::size_t i = 0; i < units.size(); ++i) {
            editor(4);
            wr32(m, w + ev3::work::kEdUnitTop, static_cast<u32>(i - i % 15));
            wr32(m, w + ev3::work::kEdUnitPos, static_cast<u32>(i % 15));
            const LiveFrame f = run(rg::fn_sub_379F30_00379f30, rg::fn_sub_379F30_00379f30__recomp, "unit list live");
            if (f.faulted) continue;
            INFO("unit list row " << i);
            CHECK(rd32(m, w + ev::work::kEdUnit) == units[i]);
            CHECK(rd32(m, w + ev3::work::kEdFocusUnit) == units[i]);
            const u32 name = rd32(m, units[i] + ev::unit::kName);
            if (name != 0xFFFFFFFFu && name < 8) CHECK(shows(f.screen, reinterpret_cast<const char*>(m.at(w + ev::work::kNames + 32 * name))));
            ++listed;
        }
        CHECK(listed == static_cast<int>(units.size()));
        editor(4);
        for (std::size_t i = 0; i < units.size(); ++i) {
            const u32 top = rd32(m, w + ev3::work::kEdUnitTop), pos = rd32(m, w + ev3::work::kEdUnitPos);
            set_pad(m, Pad{0x4000, 0x4000, 0x4000, "down"});
            const LiveFrame f = run(rg::fn_sub_379F30_00379f30, rg::fn_sub_379F30_00379f30__recomp, "unit list walk live");
            if (f.faulted) break;
            CHECK(rd32(m, w + ev::work::kEdUnit) == units[top + pos]);
        }
        // menu 5: every unit's key list, scrolled through all its keys (each key's line through sub_3760A0)
        for (u32 un : units) {
            const u32 type = rd32(m, un + ev::unit::kType);
            const u32 n = rd32(m, un + ev::unit::kKeyCount);
            if (type >= 52 || rd16(m, ev2::kColumnTable + 12 * type) == 0) continue;
            for (u32 top = 0; top <= n; top += 10) {
                editor(5);
                wr32(m, w + ev::work::kEdUnit, un);
                wr32(m, w + ev::work::kEdKeyScroll, top);
                const LiveFrame f = run(rg::fn_sub_3798F0_003798f0, rg::fn_sub_3798F0_003798f0__recomp, "key list live");
                if (f.faulted) break;
                keys_drawn += static_cast<int>(std::min<u32>(10, n - top));
                if (n - top < 10) CHECK(shows(f.screen, "----- NEW FRAME -----"));
            }
        }
        // menu 1: the settings, its items; the FIELD NO line shows the work's numbers
        editor(1);
        {
            const LiveFrame f = run(rg::fn_sub_37ABD0_0037abd0, rg::fn_sub_37ABD0_0037abd0__recomp, "settings live");
            if (!f.faulted) {
                for (const char* item : {"SAVE PROJ", "LOAD NEW PROJ", "SET TOTAL FRAME", "FIELD NO", "COUNT IDX", "BATTLE BLUR"}) {
                    INFO(item);
                    CHECK(shows(f.screen, item));
                }
                char buf[64];
                std::snprintf(buf, sizeof buf, "(%d,%d,%d,%d)", static_cast<s32>(rd32(m, w + ev3::work::kFieldMajor)),
                              static_cast<s32>(rd32(m, w + ev3::work::kFieldMinor)), rd8(m, w + ev3::work::kFieldArg70),
                              static_cast<s16>(rd16(m, w + ev3::work::kFieldArg72)));
                CHECK(shows(f.screen, buf));
            }
        }
        // menu 10: the resource list of every model class of the live scene, the cursor on its first rows
        int classes = 0;
        for (u32 cls = 0; cls < 22; ++cls) {
            fresh();
            const auto models = class_models(m, cls);
            if (models.empty()) continue;
            ++classes;
            for (u32 row = 0; row <= std::min<u32>(3, static_cast<u32>(models.size())); ++row) {
                editor(10);
                wr32(m, w + ev2::work::kEdResClass, cls);
                wr32(m, w + ev3::work::kEdListCursor, row);
                const LiveFrame f = run(rg::fn_sub_374AF0_00374af0, rg::fn_sub_374AF0_00374af0__recomp, "resource list live");
                if (f.faulted) break;
                char buf[32];
                std::snprintf(buf, sizeof buf, "RESID  %d", rd16(m, models[0]) & 0x3FF);
                INFO("class " << cls << " row " << row);
                CHECK(shows(f.screen, buf));
            }
        }
        CHECK(classes > 0);
        {
            std::string cl;
            for (u32 c = 0; c < 22; ++c)
                if (!class_models(m, c).empty()) cl += " " + std::to_string(c) + ":" + std::to_string(class_models(m, c).size());
            MESSAGE(std::string(dir) << " model classes (class:count):" << cl);
        }
        // menu 17: the live class-3 / class-1 models after the fixed rows
        editor(17);
        {
            const LiveFrame f = run(rg::fn_sub_3715B0_003715b0, rg::fn_sub_3715B0_003715b0__recomp, "model pick live");
            const auto c3 = class_models(m, 3);
            if (!f.faulted && !c3.empty()) {
                char buf[32];
                std::snprintf(buf, sizeof buf, "resId 0x%x", rd16(m, c3[0]));
                CHECK(shows(f.screen, buf));
            }
        }
        // menus 23 / 24: stepping the target model through the live lists
        for (int menu : {23, 24}) {
            editor(menu);
            wr32(m, w + (menu == 23 ? ev3::work::kEdPosCursor : ev3::work::kEdCamCursor), menu == 23 ? 2u : 1u);
            for (int f = 0; f < 8; ++f) {
                set_pad(m, f < 5 ? Pad{0x2000, 0x2000, 0x2000, "right"} : Pad{0x8000, 0x8000, 0x8000, "left"});
                if (run(menu == 23 ? rg::fn_sub_37AFC0_0037afc0 : rg::fn_sub_37B5D0_0037b5d0,
                        menu == 23 ? rg::fn_sub_37AFC0_0037afc0__recomp : rg::fn_sub_37B5D0_0037b5d0__recomp, "model step live").faulted)
                    break;
            }
        }
        // menu 15: the unit settings of every unit type that has them
        for (u32 un : units) {
            const u32 type = rd32(m, un + ev::unit::kType);
            if (type >= 52 || rd16(m, ev2::kUnitColumnTable - 2 + 12 * type) == 0) continue;
            editor(15);
            wr32(m, w + ev::work::kEdUnit, un);
            for (int f = 0; f < 3; ++f) {
                set_pad(m, f == 1 ? Pad{0x2000, 0x2000, 0x2000, "right"} : Pad{0, 0, 0, "none"});
                if (run(rg::fn_sub_36FDA0_0036fda0, rg::fn_sub_36FDA0_0036fda0__recomp, "unit settings live").faulted) break;
            }
        }
        // menus 16 / 25 / 26: the motion and rotation editors on a live character model, the tool kinds on the scene
        // a model of the live scene: a character (class 1, the party; 3) if the table has one, else the first of the
        // classes the event loaded (in these snapshots: 4 / 5 / 7 / 12 / 20)
        u32 chara_model = 0, chara_class = 0;
        fresh();
        for (u32 c : {1u, 3u, 5u, 4u, 12u, 20u, 7u}) {
            if (chara_model == 0 && !class_models(m, c).empty()) {
                chara_model = class_models(m, c)[0];
                chara_class = c;
            }
        }
        if (chara_model != 0) {
            editor(16);
            wr32(m, w + ev3::work::kEdMotionModel, chara_model);
            for (int f = 0; f < 24; ++f) {
                set_pad(m, kPads[static_cast<std::size_t>(f) % 12]);
                if (run(rg::fn_sub_3709D0_003709d0, rg::fn_sub_3709D0_003709d0__recomp, "motion live").faulted) break;
            }
            editor(25);
            wr32(m, w + ev3::work::kEdRotModel, chara_model);
            for (int f = 0; f < 12; ++f) {
                set_pad(m, kPads[static_cast<std::size_t>(f) % 12]);
                if (run(rg::fn_sub_37BE50_0037be50, rg::fn_sub_37BE50_0037be50__recomp, "rotation live").faulted) break;
            }
            for (u32 kind : {4u, 8u}) {
                editor(26);
                wr32(m, w + ev2::work::kEdValue, kind);
                wr32(m, w + ev3::work::kEdToolModel, chara_model);
                for (int f = 0; f < 12; ++f) {
                    set_pad(m, kPads[static_cast<std::size_t>(f) % 12]);
                    if (run(rg::fn_sub_373700_00373700, rg::fn_sub_373700_00373700__recomp, "tool live").faulted) break;
                }
            }
        }
        u32 keys = 0;
        for (u32 un : units) keys += rd32(m, un + ev::unit::kKeyCount);
        MESSAGE(std::string(dir) << ": " << units.size() << " units with " << keys << " keys (" << listed << " listed), " << classes
                                 << " model classes, edited model of class " << chara_class);
    }
    MESSAGE("live: " << snapshots << " snapshots, " << pairs << " frames, " << keys_drawn << " key lines drawn, " << lines
                     << " text lines compared, " << faults << " frames where the original itself faults (the same fault in both bodies)");
}

#else

TEST_CASE("game(events3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
