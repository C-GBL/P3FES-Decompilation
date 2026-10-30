// Pair tests of slice render_rw7 (game/src/render/render_rw7.cpp): RenderWare, seventh pass -- RpMatFX's plugin,
// RpMorph, the PDS registry, the PTank data layout and object set-ups, RpRandom, RpSpline, RpUserData, the pipeline-id
// streams, the bin-mesh / native-data streams, the tri-strip edge records, Rt2d's font layer. Every body runs against its
// recompiled body and tests/game/handgen_pairs.h compares the whole register file and cycles at every check point and at
// the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log; the
// stand-ins' call logs and heaps must be equal too (stand_ins.h).
//   * RpRandom against a host model of the generator (render_rw7.h): the snapshots' live generator states (their
//     invariants, then hundreds of draws each equal to the host's, the state after each), the seeding (the LCG fill and
//     the 310 discarded draws) for edge and random seeds, the open / close, RpRandomSeedMT's table;
//   * the PDS pipe registry and its rights callbacks against the snapshots' live registry and default pipelines; the
//     plugin registrations against the live engine registry entries of the same plugin ids;
//   * RpMatFX on the snapshots' live effect records (the effects flags and the slots' types agree) and on built
//     materials: every getter / setter against the host, the GS words, the extension stream size and write;
//   * streams through memory streams: user data arrays and lists (write, size, read back equal), the snapshots' real
//     bin-mesh headers (write, size, read back equal), the morph keys;
//   * RpSpline: the basis tables against the host's cubic B-spline weights (live and freshly built), the solve and
//     RpSplineFindPosition (the curve passes through the control points);
//   * the PTank allocations against the host's layout, the tank data size, the font helpers;
//   * every body on the snapshots with built records, and the random-world sweep (the p3fes_handgen skeleton).
// P3FES_HG_SEEDS sets the pairs per function of the random sweep, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces.
// Every random draw is its own statement (argument evaluation order differs between MSVC and clang-cl).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw7.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_4643B0_004643b0(EEContext&);  // generated body
void fn_sub_4643B0_004643b0__recomp(EEContext&);  // recompiled
void fn_sub_464540_00464540(EEContext&);  // generated body
void fn_sub_464540_00464540__recomp(EEContext&);  // recompiled
void fn_sub_467590_00467590(EEContext&);  // generated body
void fn_sub_467590_00467590__recomp(EEContext&);  // recompiled
void fn_sub_467600_00467600(EEContext&);  // generated body
void fn_sub_467600_00467600__recomp(EEContext&);  // recompiled
void fn_sub_4676A0_004676a0(EEContext&);  // generated body
void fn_sub_4676A0_004676a0__recomp(EEContext&);  // recompiled
void fn_sub_4676C0_004676c0(EEContext&);  // generated body
void fn_sub_4676C0_004676c0__recomp(EEContext&);  // recompiled
void fn_sub_4677F0_004677f0(EEContext&);  // generated body
void fn_sub_4677F0_004677f0__recomp(EEContext&);  // recompiled
void fn_sub_467B40_00467b40(EEContext&);  // generated body
void fn_sub_467B40_00467b40__recomp(EEContext&);  // recompiled
void fn_sub_467C20_00467c20(EEContext&);  // generated body
void fn_sub_467C20_00467c20__recomp(EEContext&);  // recompiled
void fn_sub_468350_00468350(EEContext&);  // generated body
void fn_sub_468350_00468350__recomp(EEContext&);  // recompiled
void fn_sub_4684C0_004684c0(EEContext&);  // generated body
void fn_sub_4684C0_004684c0__recomp(EEContext&);  // recompiled
void fn_sub_4684E0_004684e0(EEContext&);  // generated body
void fn_sub_4684E0_004684e0__recomp(EEContext&);  // recompiled
void fn_sub_468500_00468500(EEContext&);  // generated body
void fn_sub_468500_00468500__recomp(EEContext&);  // recompiled
void fn_sub_468530_00468530(EEContext&);  // generated body
void fn_sub_468530_00468530__recomp(EEContext&);  // recompiled
void fn_sub_4685D0_004685d0(EEContext&);  // generated body
void fn_sub_4685D0_004685d0__recomp(EEContext&);  // recompiled
void fn_sub_4685F0_004685f0(EEContext&);  // generated body
void fn_sub_4685F0_004685f0__recomp(EEContext&);  // recompiled
void fn_sub_468610_00468610(EEContext&);  // generated body
void fn_sub_468610_00468610__recomp(EEContext&);  // recompiled
void fn_sub_468630_00468630(EEContext&);  // generated body
void fn_sub_468630_00468630__recomp(EEContext&);  // recompiled
void fn_sub_468660_00468660(EEContext&);  // generated body
void fn_sub_468660_00468660__recomp(EEContext&);  // recompiled
void fn_sub_468690_00468690(EEContext&);  // generated body
void fn_sub_468690_00468690__recomp(EEContext&);  // recompiled
void fn_sub_468700_00468700(EEContext&);  // generated body
void fn_sub_468700_00468700__recomp(EEContext&);  // recompiled
void fn_sub_468C50_00468c50(EEContext&);  // generated body
void fn_sub_468C50_00468c50__recomp(EEContext&);  // recompiled
void fn_sub_468E30_00468e30(EEContext&);  // generated body
void fn_sub_468E30_00468e30__recomp(EEContext&);  // recompiled
void fn_sub_469030_00469030(EEContext&);  // generated body
void fn_sub_469030_00469030__recomp(EEContext&);  // recompiled
void fn_sub_469060_00469060(EEContext&);  // generated body
void fn_sub_469060_00469060__recomp(EEContext&);  // recompiled
void fn_sub_469280_00469280(EEContext&);  // generated body
void fn_sub_469280_00469280__recomp(EEContext&);  // recompiled
void fn_sub_4692E0_004692e0(EEContext&);  // generated body
void fn_sub_4692E0_004692e0__recomp(EEContext&);  // recompiled
void fn_sub_469340_00469340(EEContext&);  // generated body
void fn_sub_469340_00469340__recomp(EEContext&);  // recompiled
void fn_sub_4693A0_004693a0(EEContext&);  // generated body
void fn_sub_4693A0_004693a0__recomp(EEContext&);  // recompiled
void fn_sub_469400_00469400(EEContext&);  // generated body
void fn_sub_469400_00469400__recomp(EEContext&);  // recompiled
void fn_sub_4694B0_004694b0(EEContext&);  // generated body
void fn_sub_4694B0_004694b0__recomp(EEContext&);  // recompiled
void fn_sub_469590_00469590(EEContext&);  // generated body
void fn_sub_469590_00469590__recomp(EEContext&);  // recompiled
void fn_sub_4695F0_004695f0(EEContext&);  // generated body
void fn_sub_4695F0_004695f0__recomp(EEContext&);  // recompiled
void fn_sub_469650_00469650(EEContext&);  // generated body
void fn_sub_469650_00469650__recomp(EEContext&);  // recompiled
void fn_sub_4696B0_004696b0(EEContext&);  // generated body
void fn_sub_4696B0_004696b0__recomp(EEContext&);  // recompiled
void fn_sub_469710_00469710(EEContext&);  // generated body
void fn_sub_469710_00469710__recomp(EEContext&);  // recompiled
void fn_sub_4698E0_004698e0(EEContext&);  // generated body
void fn_sub_4698E0_004698e0__recomp(EEContext&);  // recompiled
void fn_sub_469940_00469940(EEContext&);  // generated body
void fn_sub_469940_00469940__recomp(EEContext&);  // recompiled
void fn_sub_4699B0_004699b0(EEContext&);  // generated body
void fn_sub_4699B0_004699b0__recomp(EEContext&);  // recompiled
void fn_sub_469A10_00469a10(EEContext&);  // generated body
void fn_sub_469A10_00469a10__recomp(EEContext&);  // recompiled
void fn_sub_469AA0_00469aa0(EEContext&);  // generated body
void fn_sub_469AA0_00469aa0__recomp(EEContext&);  // recompiled
void fn_sub_469B50_00469b50(EEContext&);  // generated body
void fn_sub_469B50_00469b50__recomp(EEContext&);  // recompiled
void fn_sub_469BC0_00469bc0(EEContext&);  // generated body
void fn_sub_469BC0_00469bc0__recomp(EEContext&);  // recompiled
void fn_sub_469CE0_00469ce0(EEContext&);  // generated body
void fn_sub_469CE0_00469ce0__recomp(EEContext&);  // recompiled
void fn_sub_469CF0_00469cf0(EEContext&);  // generated body
void fn_sub_469CF0_00469cf0__recomp(EEContext&);  // recompiled
void fn_sub_469DD0_00469dd0(EEContext&);  // generated body
void fn_sub_469DD0_00469dd0__recomp(EEContext&);  // recompiled
void fn_sub_469DF0_00469df0(EEContext&);  // generated body
void fn_sub_469DF0_00469df0__recomp(EEContext&);  // recompiled
void fn_sub_469E10_00469e10(EEContext&);  // generated body
void fn_sub_469E10_00469e10__recomp(EEContext&);  // recompiled
void fn_sub_469E30_00469e30(EEContext&);  // generated body
void fn_sub_469E30_00469e30__recomp(EEContext&);  // recompiled
void fn_sub_469FE0_00469fe0(EEContext&);  // generated body
void fn_sub_469FE0_00469fe0__recomp(EEContext&);  // recompiled
void fn_sub_46A040_0046a040(EEContext&);  // generated body
void fn_sub_46A040_0046a040__recomp(EEContext&);  // recompiled
void fn_sub_46A0F0_0046a0f0(EEContext&);  // generated body
void fn_sub_46A0F0_0046a0f0__recomp(EEContext&);  // recompiled
void fn_sub_46A230_0046a230(EEContext&);  // generated body
void fn_sub_46A230_0046a230__recomp(EEContext&);  // recompiled
void fn_sub_46A3C0_0046a3c0(EEContext&);  // generated body
void fn_sub_46A3C0_0046a3c0__recomp(EEContext&);  // recompiled
void fn_sub_46A400_0046a400(EEContext&);  // generated body
void fn_sub_46A400_0046a400__recomp(EEContext&);  // recompiled
void fn_sub_46A440_0046a440(EEContext&);  // generated body
void fn_sub_46A440_0046a440__recomp(EEContext&);  // recompiled
void fn_sub_46A470_0046a470(EEContext&);  // generated body
void fn_sub_46A470_0046a470__recomp(EEContext&);  // recompiled
void fn_sub_46A530_0046a530(EEContext&);  // generated body
void fn_sub_46A530_0046a530__recomp(EEContext&);  // recompiled
void fn_sub_46A660_0046a660(EEContext&);  // generated body
void fn_sub_46A660_0046a660__recomp(EEContext&);  // recompiled
void fn_sub_46A6C0_0046a6c0(EEContext&);  // generated body
void fn_sub_46A6C0_0046a6c0__recomp(EEContext&);  // recompiled
void fn_sub_46A6F0_0046a6f0(EEContext&);  // generated body
void fn_sub_46A6F0_0046a6f0__recomp(EEContext&);  // recompiled
void fn_sub_46A720_0046a720(EEContext&);  // generated body
void fn_sub_46A720_0046a720__recomp(EEContext&);  // recompiled
void fn_sub_46A750_0046a750(EEContext&);  // generated body
void fn_sub_46A750_0046a750__recomp(EEContext&);  // recompiled
void fn_sub_46A970_0046a970(EEContext&);  // generated body
void fn_sub_46A970_0046a970__recomp(EEContext&);  // recompiled
void fn_sub_46A9E0_0046a9e0(EEContext&);  // generated body
void fn_sub_46A9E0_0046a9e0__recomp(EEContext&);  // recompiled
void fn_sub_4734B0_004734b0(EEContext&);  // generated body
void fn_sub_4734B0_004734b0__recomp(EEContext&);  // recompiled
void fn_sub_473590_00473590(EEContext&);  // generated body
void fn_sub_473590_00473590__recomp(EEContext&);  // recompiled
void fn_sub_473600_00473600(EEContext&);  // generated body
void fn_sub_473600_00473600__recomp(EEContext&);  // recompiled
void fn_sub_473B10_00473b10(EEContext&);  // generated body
void fn_sub_473B10_00473b10__recomp(EEContext&);  // recompiled
void fn_sub_4753D0_004753d0(EEContext&);  // generated body
void fn_sub_4753D0_004753d0__recomp(EEContext&);  // recompiled
void fn_sub_475540_00475540(EEContext&);  // generated body
void fn_sub_475540_00475540__recomp(EEContext&);  // recompiled
void fn_sub_475C20_00475c20(EEContext&);  // generated body
void fn_sub_475C20_00475c20__recomp(EEContext&);  // recompiled
void fn_sub_477050_00477050(EEContext&);  // generated body
void fn_sub_477050_00477050__recomp(EEContext&);  // recompiled
void fn_sub_478CC0_00478cc0(EEContext&);  // generated body
void fn_sub_478CC0_00478cc0__recomp(EEContext&);  // recompiled
void fn_sub_47A050_0047a050(EEContext&);  // generated body
void fn_sub_47A050_0047a050__recomp(EEContext&);  // recompiled
void fn_sub_47ABF0_0047abf0(EEContext&);  // generated body
void fn_sub_47ABF0_0047abf0__recomp(EEContext&);  // recompiled
void fn_RpRandomSeedMT_00488c70(EEContext&);  // generated body
void fn_RpRandomSeedMT_00488c70__recomp(EEContext&);  // recompiled
void fn_sub_488CD0_00488cd0(EEContext&);  // generated body
void fn_sub_488CD0_00488cd0__recomp(EEContext&);  // recompiled
void fn_sub_488D40_00488d40(EEContext&);  // generated body
void fn_sub_488D40_00488d40__recomp(EEContext&);  // recompiled
void fn_RpRandomSeed_00488dd0(EEContext&);  // generated body
void fn_RpRandomSeed_00488dd0__recomp(EEContext&);  // recompiled
void fn_sub_488F30_00488f30(EEContext&);  // generated body
void fn_sub_488F30_00488f30__recomp(EEContext&);  // recompiled
void fn_sub_488FE0_00488fe0(EEContext&);  // generated body
void fn_sub_488FE0_00488fe0__recomp(EEContext&);  // recompiled
void fn_sub_48AD20_0048ad20(EEContext&);  // generated body
void fn_sub_48AD20_0048ad20__recomp(EEContext&);  // recompiled
void fn_sub_48AF80_0048af80(EEContext&);  // generated body
void fn_sub_48AF80_0048af80__recomp(EEContext&);  // recompiled
void fn_sub_48B910_0048b910(EEContext&);  // generated body
void fn_sub_48B910_0048b910__recomp(EEContext&);  // recompiled
void fn_sub_48CF00_0048cf00(EEContext&);  // generated body
void fn_sub_48CF00_0048cf00__recomp(EEContext&);  // recompiled
void fn_sub_48CFA0_0048cfa0(EEContext&);  // generated body
void fn_sub_48CFA0_0048cfa0__recomp(EEContext&);  // recompiled
void fn_sub_48D200_0048d200(EEContext&);  // generated body
void fn_sub_48D200_0048d200__recomp(EEContext&);  // recompiled
void fn_sub_48D370_0048d370(EEContext&);  // generated body
void fn_sub_48D370_0048d370__recomp(EEContext&);  // recompiled
void fn_sub_48D480_0048d480(EEContext&);  // generated body
void fn_sub_48D480_0048d480__recomp(EEContext&);  // recompiled
void fn_sub_48DCF0_0048dcf0(EEContext&);  // generated body
void fn_sub_48DCF0_0048dcf0__recomp(EEContext&);  // recompiled
void fn_sub_48DD30_0048dd30(EEContext&);  // generated body
void fn_sub_48DD30_0048dd30__recomp(EEContext&);  // recompiled
void fn_sub_48DD50_0048dd50(EEContext&);  // generated body
void fn_sub_48DD50_0048dd50__recomp(EEContext&);  // recompiled
void fn_sub_48DD70_0048dd70(EEContext&);  // generated body
void fn_sub_48DD70_0048dd70__recomp(EEContext&);  // recompiled
void fn_sub_48DE50_0048de50(EEContext&);  // generated body
void fn_sub_48DE50_0048de50__recomp(EEContext&);  // recompiled
void fn_sub_48E020_0048e020(EEContext&);  // generated body
void fn_sub_48E020_0048e020__recomp(EEContext&);  // recompiled
void fn_sub_48E2D0_0048e2d0(EEContext&);  // generated body
void fn_sub_48E2D0_0048e2d0__recomp(EEContext&);  // recompiled
void fn_sub_48E4F0_0048e4f0(EEContext&);  // generated body
void fn_sub_48E4F0_0048e4f0__recomp(EEContext&);  // recompiled
void fn_sub_48E610_0048e610(EEContext&);  // generated body
void fn_sub_48E610_0048e610__recomp(EEContext&);  // recompiled
void fn_sub_48E750_0048e750(EEContext&);  // generated body
void fn_sub_48E750_0048e750__recomp(EEContext&);  // recompiled
void fn_sub_48E890_0048e890(EEContext&);  // generated body
void fn_sub_48E890_0048e890__recomp(EEContext&);  // recompiled
void fn_sub_48EA90_0048ea90(EEContext&);  // generated body
void fn_sub_48EA90_0048ea90__recomp(EEContext&);  // recompiled
void fn_sub_48EAB0_0048eab0(EEContext&);  // generated body
void fn_sub_48EAB0_0048eab0__recomp(EEContext&);  // recompiled
void fn_sub_48EB50_0048eb50(EEContext&);  // generated body
void fn_sub_48EB50_0048eb50__recomp(EEContext&);  // recompiled
void fn_sub_48EC20_0048ec20(EEContext&);  // generated body
void fn_sub_48EC20_0048ec20__recomp(EEContext&);  // recompiled
void fn_sub_48ECF0_0048ecf0(EEContext&);  // generated body
void fn_sub_48ECF0_0048ecf0__recomp(EEContext&);  // recompiled
void fn_sub_48ED20_0048ed20(EEContext&);  // generated body
void fn_sub_48ED20_0048ed20__recomp(EEContext&);  // recompiled
void fn_sub_48EDE0_0048ede0(EEContext&);  // generated body
void fn_sub_48EDE0_0048ede0__recomp(EEContext&);  // recompiled
void fn_sub_48EE30_0048ee30(EEContext&);  // generated body
void fn_sub_48EE30_0048ee30__recomp(EEContext&);  // recompiled
void fn_sub_48EE70_0048ee70(EEContext&);  // generated body
void fn_sub_48EE70_0048ee70__recomp(EEContext&);  // recompiled
void fn_name__C9type_info_0_0048ef10(EEContext&);  // generated body
void fn_name__C9type_info_0_0048ef10__recomp(EEContext&);  // recompiled
void fn_sub_48EF20_0048ef20(EEContext&);  // generated body
void fn_sub_48EF20_0048ef20__recomp(EEContext&);  // recompiled
void fn_sub_48EF30_0048ef30(EEContext&);  // generated body
void fn_sub_48EF30_0048ef30__recomp(EEContext&);  // recompiled
void fn_sub_48EF40_0048ef40(EEContext&);  // generated body
void fn_sub_48EF40_0048ef40__recomp(EEContext&);  // recompiled
void fn_sub_48EF60_0048ef60(EEContext&);  // generated body
void fn_sub_48EF60_0048ef60__recomp(EEContext&);  // recompiled
void fn_sub_48EFA0_0048efa0(EEContext&);  // generated body
void fn_sub_48EFA0_0048efa0__recomp(EEContext&);  // recompiled
void fn_sub_48EFC0_0048efc0(EEContext&);  // generated body
void fn_sub_48EFC0_0048efc0__recomp(EEContext&);  // recompiled
void fn_sub_48EFE0_0048efe0(EEContext&);  // generated body
void fn_sub_48EFE0_0048efe0__recomp(EEContext&);  // recompiled
void fn_sub_48F340_0048f340(EEContext&);  // generated body
void fn_sub_48F340_0048f340__recomp(EEContext&);  // recompiled
void fn_sub_48F3C0_0048f3c0(EEContext&);  // generated body
void fn_sub_48F3C0_0048f3c0__recomp(EEContext&);  // recompiled
void fn_sub_48F430_0048f430(EEContext&);  // generated body
void fn_sub_48F430_0048f430__recomp(EEContext&);  // recompiled
void fn_sub_48F460_0048f460(EEContext&);  // generated body
void fn_sub_48F460_0048f460__recomp(EEContext&);  // recompiled
void fn_sub_48F4E0_0048f4e0(EEContext&);  // generated body
void fn_sub_48F4E0_0048f4e0__recomp(EEContext&);  // recompiled
void fn_sub_48F550_0048f550(EEContext&);  // generated body
void fn_sub_48F550_0048f550__recomp(EEContext&);  // recompiled
void fn_sub_494580_00494580(EEContext&);  // generated body
void fn_sub_494580_00494580__recomp(EEContext&);  // recompiled
void fn_sub_494E30_00494e30(EEContext&);  // generated body
void fn_sub_494E30_00494e30__recomp(EEContext&);  // recompiled
void fn_sub_495FB0_00495fb0(EEContext&);  // generated body
void fn_sub_495FB0_00495fb0__recomp(EEContext&);  // recompiled
void fn_sub_496230_00496230(EEContext&);  // generated body
void fn_sub_496230_00496230__recomp(EEContext&);  // recompiled
void fn_sub_4964F0_004964f0(EEContext&);  // generated body
void fn_sub_4964F0_004964f0__recomp(EEContext&);  // recompiled
void fn_sub_496580_00496580(EEContext&);  // generated body
void fn_sub_496580_00496580__recomp(EEContext&);  // recompiled
void fn_sub_496AD0_00496ad0(EEContext&);  // generated body
void fn_sub_496AD0_00496ad0__recomp(EEContext&);  // recompiled
void fn_sub_496BE0_00496be0(EEContext&);  // generated body
void fn_sub_496BE0_00496be0__recomp(EEContext&);  // recompiled
void fn_sub_496CD0_00496cd0(EEContext&);  // generated body
void fn_sub_496CD0_00496cd0__recomp(EEContext&);  // recompiled
void fn_sub_498E40_00498e40(EEContext&);  // generated body
void fn_sub_498E40_00498e40__recomp(EEContext&);  // recompiled
void fn_sub_499720_00499720(EEContext&);  // generated body
void fn_sub_499720_00499720__recomp(EEContext&);  // recompiled
void fn_sub_499850_00499850(EEContext&);  // generated body
void fn_sub_499850_00499850__recomp(EEContext&);  // recompiled
void fn_sub_49A980_0049a980(EEContext&);  // generated body
void fn_sub_49A980_0049a980__recomp(EEContext&);  // recompiled
void fn_sub_49BC50_0049bc50(EEContext&);  // generated body
void fn_sub_49BC50_0049bc50__recomp(EEContext&);  // recompiled
void fn_sub_49BC70_0049bc70(EEContext&);  // generated body
void fn_sub_49BC70_0049bc70__recomp(EEContext&);  // recompiled
void fn_sub_49BCC0_0049bcc0(EEContext&);  // generated body
void fn_sub_49BCC0_0049bcc0__recomp(EEContext&);  // recompiled
void fn_sub_49BD10_0049bd10(EEContext&);  // generated body
void fn_sub_49BD10_0049bd10__recomp(EEContext&);  // recompiled
void fn_sub_49BD60_0049bd60(EEContext&);  // generated body
void fn_sub_49BD60_0049bd60__recomp(EEContext&);  // recompiled
void fn_sub_49BD70_0049bd70(EEContext&);  // generated body
void fn_sub_49BD70_0049bd70__recomp(EEContext&);  // recompiled
void fn_sub_49BDC0_0049bdc0(EEContext&);  // generated body
void fn_sub_49BDC0_0049bdc0__recomp(EEContext&);  // recompiled
void fn_sub_49BE20_0049be20(EEContext&);  // generated body
void fn_sub_49BE20_0049be20__recomp(EEContext&);  // recompiled
void fn_sub_49BE50_0049be50(EEContext&);  // generated body
void fn_sub_49BE50_0049be50__recomp(EEContext&);  // recompiled
void fn_sub_49E6C0_0049e6c0(EEContext&);  // generated body
void fn_sub_49E6C0_0049e6c0__recomp(EEContext&);  // recompiled
void fn_sub_49E780_0049e780(EEContext&);  // generated body
void fn_sub_49E780_0049e780__recomp(EEContext&);  // recompiled
void fn_sub_49ECD0_0049ecd0(EEContext&);  // generated body
void fn_sub_49ECD0_0049ecd0__recomp(EEContext&);  // recompiled
void fn_sub_49F340_0049f340(EEContext&);  // generated body
void fn_sub_49F340_0049f340__recomp(EEContext&);  // recompiled
void fn_sub_49F500_0049f500(EEContext&);  // generated body
void fn_sub_49F500_0049f500__recomp(EEContext&);  // recompiled
void fn_sub_49FE40_0049fe40(EEContext&);  // generated body
void fn_sub_49FE40_0049fe40__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_0049ff00(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_0049ff00__recomp(EEContext&);  // recompiled
void fn_sub_4A5470_004a5470(EEContext&);  // generated body
void fn_sub_4A5470_004a5470__recomp(EEContext&);  // recompiled
void fn_sub_4A5DD0_004a5dd0(EEContext&);  // generated body
void fn_sub_4A5DD0_004a5dd0__recomp(EEContext&);  // recompiled
void fn_sub_4A6200_004a6200(EEContext&);  // generated body
void fn_sub_4A6200_004a6200__recomp(EEContext&);  // recompiled
void fn_sub_4A62E0_004a62e0(EEContext&);  // generated body
void fn_sub_4A62E0_004a62e0__recomp(EEContext&);  // recompiled
void fn_sub_4A6360_004a6360(EEContext&);  // generated body
void fn_sub_4A6360_004a6360__recomp(EEContext&);  // recompiled
void fn_sub_4A6530_004a6530(EEContext&);  // generated body
void fn_sub_4A6530_004a6530__recomp(EEContext&);  // recompiled
void fn_sub_4A7620_004a7620(EEContext&);  // generated body
void fn_sub_4A7620_004a7620__recomp(EEContext&);  // recompiled
void fn_sub_4A91F0_004a91f0(EEContext&);  // generated body
void fn_sub_4A91F0_004a91f0__recomp(EEContext&);  // recompiled
void fn_sub_4A9330_004a9330(EEContext&);  // generated body
void fn_sub_4A9330_004a9330__recomp(EEContext&);  // recompiled
void fn_sub_4A9490_004a9490(EEContext&);  // generated body
void fn_sub_4A9490_004a9490__recomp(EEContext&);  // recompiled
void fn_sub_4A9550_004a9550(EEContext&);  // generated body
void fn_sub_4A9550_004a9550__recomp(EEContext&);  // recompiled
void fn_sub_4A9560_004a9560(EEContext&);  // generated body
void fn_sub_4A9560_004a9560__recomp(EEContext&);  // recompiled
void fn_sub_4A96B0_004a96b0(EEContext&);  // generated body
void fn_sub_4A96B0_004a96b0__recomp(EEContext&);  // recompiled
void fn_sub_4A9BD0_004a9bd0(EEContext&);  // generated body
void fn_sub_4A9BD0_004a9bd0__recomp(EEContext&);  // recompiled
void fn_sub_4A9BE0_004a9be0(EEContext&);  // generated body
void fn_sub_4A9BE0_004a9be0__recomp(EEContext&);  // recompiled
void fn_sub_4F2AD0_004f2ad0(EEContext&);  // generated body
void fn_sub_4F2AD0_004f2ad0__recomp(EEContext&);  // recompiled
void fn_sub_4F3010_004f3010(EEContext&);  // generated body
void fn_sub_4F3010_004f3010__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_4643B0", 0x4643B0, &recomp_gen::fn_sub_4643B0_004643b0, &recomp_gen::fn_sub_4643B0_004643b0__recomp},
    {"sub_464540", 0x464540, &recomp_gen::fn_sub_464540_00464540, &recomp_gen::fn_sub_464540_00464540__recomp},
    {"sub_467590", 0x467590, &recomp_gen::fn_sub_467590_00467590, &recomp_gen::fn_sub_467590_00467590__recomp},
    {"sub_467600", 0x467600, &recomp_gen::fn_sub_467600_00467600, &recomp_gen::fn_sub_467600_00467600__recomp},
    {"sub_4676A0", 0x4676A0, &recomp_gen::fn_sub_4676A0_004676a0, &recomp_gen::fn_sub_4676A0_004676a0__recomp},
    {"sub_4676C0", 0x4676C0, &recomp_gen::fn_sub_4676C0_004676c0, &recomp_gen::fn_sub_4676C0_004676c0__recomp},
    {"sub_4677F0", 0x4677F0, &recomp_gen::fn_sub_4677F0_004677f0, &recomp_gen::fn_sub_4677F0_004677f0__recomp},
    {"sub_467B40", 0x467B40, &recomp_gen::fn_sub_467B40_00467b40, &recomp_gen::fn_sub_467B40_00467b40__recomp},
    {"sub_467C20", 0x467C20, &recomp_gen::fn_sub_467C20_00467c20, &recomp_gen::fn_sub_467C20_00467c20__recomp},
    {"sub_468350", 0x468350, &recomp_gen::fn_sub_468350_00468350, &recomp_gen::fn_sub_468350_00468350__recomp},
    {"sub_4684C0", 0x4684C0, &recomp_gen::fn_sub_4684C0_004684c0, &recomp_gen::fn_sub_4684C0_004684c0__recomp},
    {"sub_4684E0", 0x4684E0, &recomp_gen::fn_sub_4684E0_004684e0, &recomp_gen::fn_sub_4684E0_004684e0__recomp},
    {"sub_468500", 0x468500, &recomp_gen::fn_sub_468500_00468500, &recomp_gen::fn_sub_468500_00468500__recomp},
    {"sub_468530", 0x468530, &recomp_gen::fn_sub_468530_00468530, &recomp_gen::fn_sub_468530_00468530__recomp},
    {"sub_4685D0", 0x4685D0, &recomp_gen::fn_sub_4685D0_004685d0, &recomp_gen::fn_sub_4685D0_004685d0__recomp},
    {"sub_4685F0", 0x4685F0, &recomp_gen::fn_sub_4685F0_004685f0, &recomp_gen::fn_sub_4685F0_004685f0__recomp},
    {"sub_468610", 0x468610, &recomp_gen::fn_sub_468610_00468610, &recomp_gen::fn_sub_468610_00468610__recomp},
    {"sub_468630", 0x468630, &recomp_gen::fn_sub_468630_00468630, &recomp_gen::fn_sub_468630_00468630__recomp},
    {"sub_468660", 0x468660, &recomp_gen::fn_sub_468660_00468660, &recomp_gen::fn_sub_468660_00468660__recomp},
    {"sub_468690", 0x468690, &recomp_gen::fn_sub_468690_00468690, &recomp_gen::fn_sub_468690_00468690__recomp},
    {"sub_468700", 0x468700, &recomp_gen::fn_sub_468700_00468700, &recomp_gen::fn_sub_468700_00468700__recomp},
    {"sub_468C50", 0x468C50, &recomp_gen::fn_sub_468C50_00468c50, &recomp_gen::fn_sub_468C50_00468c50__recomp},
    {"sub_468E30", 0x468E30, &recomp_gen::fn_sub_468E30_00468e30, &recomp_gen::fn_sub_468E30_00468e30__recomp},
    {"sub_469030", 0x469030, &recomp_gen::fn_sub_469030_00469030, &recomp_gen::fn_sub_469030_00469030__recomp},
    {"sub_469060", 0x469060, &recomp_gen::fn_sub_469060_00469060, &recomp_gen::fn_sub_469060_00469060__recomp},
    {"sub_469280", 0x469280, &recomp_gen::fn_sub_469280_00469280, &recomp_gen::fn_sub_469280_00469280__recomp},
    {"sub_4692E0", 0x4692E0, &recomp_gen::fn_sub_4692E0_004692e0, &recomp_gen::fn_sub_4692E0_004692e0__recomp},
    {"sub_469340", 0x469340, &recomp_gen::fn_sub_469340_00469340, &recomp_gen::fn_sub_469340_00469340__recomp},
    {"sub_4693A0", 0x4693A0, &recomp_gen::fn_sub_4693A0_004693a0, &recomp_gen::fn_sub_4693A0_004693a0__recomp},
    {"sub_469400", 0x469400, &recomp_gen::fn_sub_469400_00469400, &recomp_gen::fn_sub_469400_00469400__recomp},
    {"sub_4694B0", 0x4694B0, &recomp_gen::fn_sub_4694B0_004694b0, &recomp_gen::fn_sub_4694B0_004694b0__recomp},
    {"sub_469590", 0x469590, &recomp_gen::fn_sub_469590_00469590, &recomp_gen::fn_sub_469590_00469590__recomp},
    {"sub_4695F0", 0x4695F0, &recomp_gen::fn_sub_4695F0_004695f0, &recomp_gen::fn_sub_4695F0_004695f0__recomp},
    {"sub_469650", 0x469650, &recomp_gen::fn_sub_469650_00469650, &recomp_gen::fn_sub_469650_00469650__recomp},
    {"sub_4696B0", 0x4696B0, &recomp_gen::fn_sub_4696B0_004696b0, &recomp_gen::fn_sub_4696B0_004696b0__recomp},
    {"sub_469710", 0x469710, &recomp_gen::fn_sub_469710_00469710, &recomp_gen::fn_sub_469710_00469710__recomp},
    {"sub_4698E0", 0x4698E0, &recomp_gen::fn_sub_4698E0_004698e0, &recomp_gen::fn_sub_4698E0_004698e0__recomp},
    {"sub_469940", 0x469940, &recomp_gen::fn_sub_469940_00469940, &recomp_gen::fn_sub_469940_00469940__recomp},
    {"sub_4699B0", 0x4699B0, &recomp_gen::fn_sub_4699B0_004699b0, &recomp_gen::fn_sub_4699B0_004699b0__recomp},
    {"sub_469A10", 0x469A10, &recomp_gen::fn_sub_469A10_00469a10, &recomp_gen::fn_sub_469A10_00469a10__recomp},
    {"sub_469AA0", 0x469AA0, &recomp_gen::fn_sub_469AA0_00469aa0, &recomp_gen::fn_sub_469AA0_00469aa0__recomp},
    {"sub_469B50", 0x469B50, &recomp_gen::fn_sub_469B50_00469b50, &recomp_gen::fn_sub_469B50_00469b50__recomp},
    {"sub_469BC0", 0x469BC0, &recomp_gen::fn_sub_469BC0_00469bc0, &recomp_gen::fn_sub_469BC0_00469bc0__recomp},
    {"sub_469CE0", 0x469CE0, &recomp_gen::fn_sub_469CE0_00469ce0, &recomp_gen::fn_sub_469CE0_00469ce0__recomp},
    {"sub_469CF0", 0x469CF0, &recomp_gen::fn_sub_469CF0_00469cf0, &recomp_gen::fn_sub_469CF0_00469cf0__recomp},
    {"sub_469DD0", 0x469DD0, &recomp_gen::fn_sub_469DD0_00469dd0, &recomp_gen::fn_sub_469DD0_00469dd0__recomp},
    {"sub_469DF0", 0x469DF0, &recomp_gen::fn_sub_469DF0_00469df0, &recomp_gen::fn_sub_469DF0_00469df0__recomp},
    {"sub_469E10", 0x469E10, &recomp_gen::fn_sub_469E10_00469e10, &recomp_gen::fn_sub_469E10_00469e10__recomp},
    {"sub_469E30", 0x469E30, &recomp_gen::fn_sub_469E30_00469e30, &recomp_gen::fn_sub_469E30_00469e30__recomp},
    {"sub_469FE0", 0x469FE0, &recomp_gen::fn_sub_469FE0_00469fe0, &recomp_gen::fn_sub_469FE0_00469fe0__recomp},
    {"sub_46A040", 0x46A040, &recomp_gen::fn_sub_46A040_0046a040, &recomp_gen::fn_sub_46A040_0046a040__recomp},
    {"sub_46A0F0", 0x46A0F0, &recomp_gen::fn_sub_46A0F0_0046a0f0, &recomp_gen::fn_sub_46A0F0_0046a0f0__recomp},
    {"sub_46A230", 0x46A230, &recomp_gen::fn_sub_46A230_0046a230, &recomp_gen::fn_sub_46A230_0046a230__recomp},
    {"sub_46A3C0", 0x46A3C0, &recomp_gen::fn_sub_46A3C0_0046a3c0, &recomp_gen::fn_sub_46A3C0_0046a3c0__recomp},
    {"sub_46A400", 0x46A400, &recomp_gen::fn_sub_46A400_0046a400, &recomp_gen::fn_sub_46A400_0046a400__recomp},
    {"sub_46A440", 0x46A440, &recomp_gen::fn_sub_46A440_0046a440, &recomp_gen::fn_sub_46A440_0046a440__recomp},
    {"sub_46A470", 0x46A470, &recomp_gen::fn_sub_46A470_0046a470, &recomp_gen::fn_sub_46A470_0046a470__recomp},
    {"sub_46A530", 0x46A530, &recomp_gen::fn_sub_46A530_0046a530, &recomp_gen::fn_sub_46A530_0046a530__recomp},
    {"sub_46A660", 0x46A660, &recomp_gen::fn_sub_46A660_0046a660, &recomp_gen::fn_sub_46A660_0046a660__recomp},
    {"sub_46A6C0", 0x46A6C0, &recomp_gen::fn_sub_46A6C0_0046a6c0, &recomp_gen::fn_sub_46A6C0_0046a6c0__recomp},
    {"sub_46A6F0", 0x46A6F0, &recomp_gen::fn_sub_46A6F0_0046a6f0, &recomp_gen::fn_sub_46A6F0_0046a6f0__recomp},
    {"sub_46A720", 0x46A720, &recomp_gen::fn_sub_46A720_0046a720, &recomp_gen::fn_sub_46A720_0046a720__recomp},
    {"sub_46A750", 0x46A750, &recomp_gen::fn_sub_46A750_0046a750, &recomp_gen::fn_sub_46A750_0046a750__recomp},
    {"sub_46A970", 0x46A970, &recomp_gen::fn_sub_46A970_0046a970, &recomp_gen::fn_sub_46A970_0046a970__recomp},
    {"sub_46A9E0", 0x46A9E0, &recomp_gen::fn_sub_46A9E0_0046a9e0, &recomp_gen::fn_sub_46A9E0_0046a9e0__recomp},
    {"sub_4734B0", 0x4734B0, &recomp_gen::fn_sub_4734B0_004734b0, &recomp_gen::fn_sub_4734B0_004734b0__recomp},
    {"sub_473590", 0x473590, &recomp_gen::fn_sub_473590_00473590, &recomp_gen::fn_sub_473590_00473590__recomp},
    {"sub_473600", 0x473600, &recomp_gen::fn_sub_473600_00473600, &recomp_gen::fn_sub_473600_00473600__recomp},
    {"sub_473B10", 0x473B10, &recomp_gen::fn_sub_473B10_00473b10, &recomp_gen::fn_sub_473B10_00473b10__recomp},
    {"sub_4753D0", 0x4753D0, &recomp_gen::fn_sub_4753D0_004753d0, &recomp_gen::fn_sub_4753D0_004753d0__recomp},
    {"sub_475540", 0x475540, &recomp_gen::fn_sub_475540_00475540, &recomp_gen::fn_sub_475540_00475540__recomp},
    {"sub_475C20", 0x475C20, &recomp_gen::fn_sub_475C20_00475c20, &recomp_gen::fn_sub_475C20_00475c20__recomp},
    {"sub_477050", 0x477050, &recomp_gen::fn_sub_477050_00477050, &recomp_gen::fn_sub_477050_00477050__recomp},
    {"sub_478CC0", 0x478CC0, &recomp_gen::fn_sub_478CC0_00478cc0, &recomp_gen::fn_sub_478CC0_00478cc0__recomp},
    {"sub_47A050", 0x47A050, &recomp_gen::fn_sub_47A050_0047a050, &recomp_gen::fn_sub_47A050_0047a050__recomp},
    {"sub_47ABF0", 0x47ABF0, &recomp_gen::fn_sub_47ABF0_0047abf0, &recomp_gen::fn_sub_47ABF0_0047abf0__recomp},
    {"RpRandomSeedMT", 0x488C70, &recomp_gen::fn_RpRandomSeedMT_00488c70, &recomp_gen::fn_RpRandomSeedMT_00488c70__recomp},
    {"sub_488CD0", 0x488CD0, &recomp_gen::fn_sub_488CD0_00488cd0, &recomp_gen::fn_sub_488CD0_00488cd0__recomp},
    {"sub_488D40", 0x488D40, &recomp_gen::fn_sub_488D40_00488d40, &recomp_gen::fn_sub_488D40_00488d40__recomp},
    {"RpRandomSeed", 0x488DD0, &recomp_gen::fn_RpRandomSeed_00488dd0, &recomp_gen::fn_RpRandomSeed_00488dd0__recomp},
    {"sub_488F30", 0x488F30, &recomp_gen::fn_sub_488F30_00488f30, &recomp_gen::fn_sub_488F30_00488f30__recomp},
    {"sub_488FE0", 0x488FE0, &recomp_gen::fn_sub_488FE0_00488fe0, &recomp_gen::fn_sub_488FE0_00488fe0__recomp},
    {"sub_48AD20", 0x48AD20, &recomp_gen::fn_sub_48AD20_0048ad20, &recomp_gen::fn_sub_48AD20_0048ad20__recomp},
    {"sub_48AF80", 0x48AF80, &recomp_gen::fn_sub_48AF80_0048af80, &recomp_gen::fn_sub_48AF80_0048af80__recomp},
    {"sub_48B910", 0x48B910, &recomp_gen::fn_sub_48B910_0048b910, &recomp_gen::fn_sub_48B910_0048b910__recomp},
    {"sub_48CF00", 0x48CF00, &recomp_gen::fn_sub_48CF00_0048cf00, &recomp_gen::fn_sub_48CF00_0048cf00__recomp},
    {"sub_48CFA0", 0x48CFA0, &recomp_gen::fn_sub_48CFA0_0048cfa0, &recomp_gen::fn_sub_48CFA0_0048cfa0__recomp},
    {"sub_48D200", 0x48D200, &recomp_gen::fn_sub_48D200_0048d200, &recomp_gen::fn_sub_48D200_0048d200__recomp},
    {"sub_48D370", 0x48D370, &recomp_gen::fn_sub_48D370_0048d370, &recomp_gen::fn_sub_48D370_0048d370__recomp},
    {"sub_48D480", 0x48D480, &recomp_gen::fn_sub_48D480_0048d480, &recomp_gen::fn_sub_48D480_0048d480__recomp},
    {"sub_48DCF0", 0x48DCF0, &recomp_gen::fn_sub_48DCF0_0048dcf0, &recomp_gen::fn_sub_48DCF0_0048dcf0__recomp},
    {"sub_48DD30", 0x48DD30, &recomp_gen::fn_sub_48DD30_0048dd30, &recomp_gen::fn_sub_48DD30_0048dd30__recomp},
    {"sub_48DD50", 0x48DD50, &recomp_gen::fn_sub_48DD50_0048dd50, &recomp_gen::fn_sub_48DD50_0048dd50__recomp},
    {"sub_48DD70", 0x48DD70, &recomp_gen::fn_sub_48DD70_0048dd70, &recomp_gen::fn_sub_48DD70_0048dd70__recomp},
    {"sub_48DE50", 0x48DE50, &recomp_gen::fn_sub_48DE50_0048de50, &recomp_gen::fn_sub_48DE50_0048de50__recomp},
    {"sub_48E020", 0x48E020, &recomp_gen::fn_sub_48E020_0048e020, &recomp_gen::fn_sub_48E020_0048e020__recomp},
    {"sub_48E2D0", 0x48E2D0, &recomp_gen::fn_sub_48E2D0_0048e2d0, &recomp_gen::fn_sub_48E2D0_0048e2d0__recomp},
    {"sub_48E4F0", 0x48E4F0, &recomp_gen::fn_sub_48E4F0_0048e4f0, &recomp_gen::fn_sub_48E4F0_0048e4f0__recomp},
    {"sub_48E610", 0x48E610, &recomp_gen::fn_sub_48E610_0048e610, &recomp_gen::fn_sub_48E610_0048e610__recomp},
    {"sub_48E750", 0x48E750, &recomp_gen::fn_sub_48E750_0048e750, &recomp_gen::fn_sub_48E750_0048e750__recomp},
    {"sub_48E890", 0x48E890, &recomp_gen::fn_sub_48E890_0048e890, &recomp_gen::fn_sub_48E890_0048e890__recomp},
    {"sub_48EA90", 0x48EA90, &recomp_gen::fn_sub_48EA90_0048ea90, &recomp_gen::fn_sub_48EA90_0048ea90__recomp},
    {"sub_48EAB0", 0x48EAB0, &recomp_gen::fn_sub_48EAB0_0048eab0, &recomp_gen::fn_sub_48EAB0_0048eab0__recomp},
    {"sub_48EB50", 0x48EB50, &recomp_gen::fn_sub_48EB50_0048eb50, &recomp_gen::fn_sub_48EB50_0048eb50__recomp},
    {"sub_48EC20", 0x48EC20, &recomp_gen::fn_sub_48EC20_0048ec20, &recomp_gen::fn_sub_48EC20_0048ec20__recomp},
    {"sub_48ECF0", 0x48ECF0, &recomp_gen::fn_sub_48ECF0_0048ecf0, &recomp_gen::fn_sub_48ECF0_0048ecf0__recomp},
    {"sub_48ED20", 0x48ED20, &recomp_gen::fn_sub_48ED20_0048ed20, &recomp_gen::fn_sub_48ED20_0048ed20__recomp},
    {"sub_48EDE0", 0x48EDE0, &recomp_gen::fn_sub_48EDE0_0048ede0, &recomp_gen::fn_sub_48EDE0_0048ede0__recomp},
    {"sub_48EE30", 0x48EE30, &recomp_gen::fn_sub_48EE30_0048ee30, &recomp_gen::fn_sub_48EE30_0048ee30__recomp},
    {"sub_48EE70", 0x48EE70, &recomp_gen::fn_sub_48EE70_0048ee70, &recomp_gen::fn_sub_48EE70_0048ee70__recomp},
    {"name__C9type_info_0", 0x48EF10, &recomp_gen::fn_name__C9type_info_0_0048ef10, &recomp_gen::fn_name__C9type_info_0_0048ef10__recomp},
    {"sub_48EF20", 0x48EF20, &recomp_gen::fn_sub_48EF20_0048ef20, &recomp_gen::fn_sub_48EF20_0048ef20__recomp},
    {"sub_48EF30", 0x48EF30, &recomp_gen::fn_sub_48EF30_0048ef30, &recomp_gen::fn_sub_48EF30_0048ef30__recomp},
    {"sub_48EF40", 0x48EF40, &recomp_gen::fn_sub_48EF40_0048ef40, &recomp_gen::fn_sub_48EF40_0048ef40__recomp},
    {"sub_48EF60", 0x48EF60, &recomp_gen::fn_sub_48EF60_0048ef60, &recomp_gen::fn_sub_48EF60_0048ef60__recomp},
    {"sub_48EFA0", 0x48EFA0, &recomp_gen::fn_sub_48EFA0_0048efa0, &recomp_gen::fn_sub_48EFA0_0048efa0__recomp},
    {"sub_48EFC0", 0x48EFC0, &recomp_gen::fn_sub_48EFC0_0048efc0, &recomp_gen::fn_sub_48EFC0_0048efc0__recomp},
    {"sub_48EFE0", 0x48EFE0, &recomp_gen::fn_sub_48EFE0_0048efe0, &recomp_gen::fn_sub_48EFE0_0048efe0__recomp},
    {"sub_48F340", 0x48F340, &recomp_gen::fn_sub_48F340_0048f340, &recomp_gen::fn_sub_48F340_0048f340__recomp},
    {"sub_48F3C0", 0x48F3C0, &recomp_gen::fn_sub_48F3C0_0048f3c0, &recomp_gen::fn_sub_48F3C0_0048f3c0__recomp},
    {"sub_48F430", 0x48F430, &recomp_gen::fn_sub_48F430_0048f430, &recomp_gen::fn_sub_48F430_0048f430__recomp},
    {"sub_48F460", 0x48F460, &recomp_gen::fn_sub_48F460_0048f460, &recomp_gen::fn_sub_48F460_0048f460__recomp},
    {"sub_48F4E0", 0x48F4E0, &recomp_gen::fn_sub_48F4E0_0048f4e0, &recomp_gen::fn_sub_48F4E0_0048f4e0__recomp},
    {"sub_48F550", 0x48F550, &recomp_gen::fn_sub_48F550_0048f550, &recomp_gen::fn_sub_48F550_0048f550__recomp},
    {"sub_494580", 0x494580, &recomp_gen::fn_sub_494580_00494580, &recomp_gen::fn_sub_494580_00494580__recomp},
    {"sub_494E30", 0x494E30, &recomp_gen::fn_sub_494E30_00494e30, &recomp_gen::fn_sub_494E30_00494e30__recomp},
    {"sub_495FB0", 0x495FB0, &recomp_gen::fn_sub_495FB0_00495fb0, &recomp_gen::fn_sub_495FB0_00495fb0__recomp},
    {"sub_496230", 0x496230, &recomp_gen::fn_sub_496230_00496230, &recomp_gen::fn_sub_496230_00496230__recomp},
    {"sub_4964F0", 0x4964F0, &recomp_gen::fn_sub_4964F0_004964f0, &recomp_gen::fn_sub_4964F0_004964f0__recomp},
    {"sub_496580", 0x496580, &recomp_gen::fn_sub_496580_00496580, &recomp_gen::fn_sub_496580_00496580__recomp},
    {"sub_496AD0", 0x496AD0, &recomp_gen::fn_sub_496AD0_00496ad0, &recomp_gen::fn_sub_496AD0_00496ad0__recomp},
    {"sub_496BE0", 0x496BE0, &recomp_gen::fn_sub_496BE0_00496be0, &recomp_gen::fn_sub_496BE0_00496be0__recomp},
    {"sub_496CD0", 0x496CD0, &recomp_gen::fn_sub_496CD0_00496cd0, &recomp_gen::fn_sub_496CD0_00496cd0__recomp},
    {"sub_498E40", 0x498E40, &recomp_gen::fn_sub_498E40_00498e40, &recomp_gen::fn_sub_498E40_00498e40__recomp},
    {"sub_499720", 0x499720, &recomp_gen::fn_sub_499720_00499720, &recomp_gen::fn_sub_499720_00499720__recomp},
    {"sub_499850", 0x499850, &recomp_gen::fn_sub_499850_00499850, &recomp_gen::fn_sub_499850_00499850__recomp},
    {"sub_49A980", 0x49A980, &recomp_gen::fn_sub_49A980_0049a980, &recomp_gen::fn_sub_49A980_0049a980__recomp},
    {"sub_49BC50", 0x49BC50, &recomp_gen::fn_sub_49BC50_0049bc50, &recomp_gen::fn_sub_49BC50_0049bc50__recomp},
    {"sub_49BC70", 0x49BC70, &recomp_gen::fn_sub_49BC70_0049bc70, &recomp_gen::fn_sub_49BC70_0049bc70__recomp},
    {"sub_49BCC0", 0x49BCC0, &recomp_gen::fn_sub_49BCC0_0049bcc0, &recomp_gen::fn_sub_49BCC0_0049bcc0__recomp},
    {"sub_49BD10", 0x49BD10, &recomp_gen::fn_sub_49BD10_0049bd10, &recomp_gen::fn_sub_49BD10_0049bd10__recomp},
    {"sub_49BD60", 0x49BD60, &recomp_gen::fn_sub_49BD60_0049bd60, &recomp_gen::fn_sub_49BD60_0049bd60__recomp},
    {"sub_49BD70", 0x49BD70, &recomp_gen::fn_sub_49BD70_0049bd70, &recomp_gen::fn_sub_49BD70_0049bd70__recomp},
    {"sub_49BDC0", 0x49BDC0, &recomp_gen::fn_sub_49BDC0_0049bdc0, &recomp_gen::fn_sub_49BDC0_0049bdc0__recomp},
    {"sub_49BE20", 0x49BE20, &recomp_gen::fn_sub_49BE20_0049be20, &recomp_gen::fn_sub_49BE20_0049be20__recomp},
    {"sub_49BE50", 0x49BE50, &recomp_gen::fn_sub_49BE50_0049be50, &recomp_gen::fn_sub_49BE50_0049be50__recomp},
    {"sub_49E6C0", 0x49E6C0, &recomp_gen::fn_sub_49E6C0_0049e6c0, &recomp_gen::fn_sub_49E6C0_0049e6c0__recomp},
    {"sub_49E780", 0x49E780, &recomp_gen::fn_sub_49E780_0049e780, &recomp_gen::fn_sub_49E780_0049e780__recomp},
    {"sub_49ECD0", 0x49ECD0, &recomp_gen::fn_sub_49ECD0_0049ecd0, &recomp_gen::fn_sub_49ECD0_0049ecd0__recomp},
    {"sub_49F340", 0x49F340, &recomp_gen::fn_sub_49F340_0049f340, &recomp_gen::fn_sub_49F340_0049f340__recomp},
    {"sub_49F500", 0x49F500, &recomp_gen::fn_sub_49F500_0049f500, &recomp_gen::fn_sub_49F500_0049f500__recomp},
    {"sub_49FE40", 0x49FE40, &recomp_gen::fn_sub_49FE40_0049fe40, &recomp_gen::fn_sub_49FE40_0049fe40__recomp},
    {"sceLibgcc32GetErxEntries", 0x49FF00, &recomp_gen::fn_sceLibgcc32GetErxEntries_0049ff00, &recomp_gen::fn_sceLibgcc32GetErxEntries_0049ff00__recomp},
    {"sub_4A5470", 0x4A5470, &recomp_gen::fn_sub_4A5470_004a5470, &recomp_gen::fn_sub_4A5470_004a5470__recomp},
    {"sub_4A5DD0", 0x4A5DD0, &recomp_gen::fn_sub_4A5DD0_004a5dd0, &recomp_gen::fn_sub_4A5DD0_004a5dd0__recomp},
    {"sub_4A6200", 0x4A6200, &recomp_gen::fn_sub_4A6200_004a6200, &recomp_gen::fn_sub_4A6200_004a6200__recomp},
    {"sub_4A62E0", 0x4A62E0, &recomp_gen::fn_sub_4A62E0_004a62e0, &recomp_gen::fn_sub_4A62E0_004a62e0__recomp},
    {"sub_4A6360", 0x4A6360, &recomp_gen::fn_sub_4A6360_004a6360, &recomp_gen::fn_sub_4A6360_004a6360__recomp},
    {"sub_4A6530", 0x4A6530, &recomp_gen::fn_sub_4A6530_004a6530, &recomp_gen::fn_sub_4A6530_004a6530__recomp},
    {"sub_4A7620", 0x4A7620, &recomp_gen::fn_sub_4A7620_004a7620, &recomp_gen::fn_sub_4A7620_004a7620__recomp},
    {"sub_4A91F0", 0x4A91F0, &recomp_gen::fn_sub_4A91F0_004a91f0, &recomp_gen::fn_sub_4A91F0_004a91f0__recomp},
    {"sub_4A9330", 0x4A9330, &recomp_gen::fn_sub_4A9330_004a9330, &recomp_gen::fn_sub_4A9330_004a9330__recomp},
    {"sub_4A9490", 0x4A9490, &recomp_gen::fn_sub_4A9490_004a9490, &recomp_gen::fn_sub_4A9490_004a9490__recomp},
    {"sub_4A9550", 0x4A9550, &recomp_gen::fn_sub_4A9550_004a9550, &recomp_gen::fn_sub_4A9550_004a9550__recomp},
    {"sub_4A9560", 0x4A9560, &recomp_gen::fn_sub_4A9560_004a9560, &recomp_gen::fn_sub_4A9560_004a9560__recomp},
    {"sub_4A96B0", 0x4A96B0, &recomp_gen::fn_sub_4A96B0_004a96b0, &recomp_gen::fn_sub_4A96B0_004a96b0__recomp},
    {"sub_4A9BD0", 0x4A9BD0, &recomp_gen::fn_sub_4A9BD0_004a9bd0, &recomp_gen::fn_sub_4A9BD0_004a9bd0__recomp},
    {"sub_4A9BE0", 0x4A9BE0, &recomp_gen::fn_sub_4A9BE0_004a9be0, &recomp_gen::fn_sub_4A9BE0_004a9be0__recomp},
    {"sub_4F2AD0", 0x4F2AD0, &recomp_gen::fn_sub_4F2AD0_004f2ad0, &recomp_gen::fn_sub_4F2AD0_004f2ad0__recomp},
    {"sub_4F3010", 0x4F3010, &recomp_gen::fn_sub_4F3010_004f3010, &recomp_gen::fn_sub_4F3010_004f3010__recomp},
};

// The world of the random sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// --- guest helpers ---------------------------------------------------------------------------------------------------
u32 ld(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
float ldf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
void st(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void sts(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
std::string lds(Machine& m, u32 va) { return reinterpret_cast<const char*>(m.at(va)); }
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float frand(std::mt19937& rng, float lo, float hi) {
    const u32 r = rng() % 100001;
    return lo + (hi - lo) * static_cast<float>(r) / 100000.0f;
}
bool in_ram(u32 va, u32 len = 4) { return va != 0 && va < EEMemory::kMainRamSize - len; }

const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw7 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read (render_rw5.h / render_rw7.h).
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpRandom = 0x7CE778u, kGpMatFxMaterial = 0x7CE738u, kGpMorphAtomic = 0x7CE744u, kGpMorphGeometry = 0x7CE748u,
              kGpPipeModule = 0x7CEB28u, kGpSplineBasis = 0x7CE77Cu, kGpMeshSerial = 0x7CE850u;
constexpr u32 kEngineRegistry = 0x77E630u;
constexpr u32 kPdsRegistry = 0x95C44Cu;
constexpr u32 kMatFxFreeList = 0x95C400u;
constexpr u32 kRwMalloc = 0x104140u, kRwFree = 0x104280u;
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// A function this build does not emit, served by a recorder (callbacks the bodies call through pointers).
constexpr u32 kCallback = 0x10A860u;

// The live entries of an RW free list (the block chain behind +16, the used bits after each block's header).
std::vector<u32> live_entries(Machine& m, u32 fl) {
    std::vector<u32> out;
    if (!in_ram(fl, 64)) return out;
    const u32 es = ld(m, fl), hs = ld(m, fl + 8), al = ld(m, fl + 12);
    if (al == 0 || hs > 64 || es == 0) return out;
    const u32 head = fl + 16;
    u32 b = ld(m, head);
    for (int nb = 0; b != head && in_ram(b) && nb < 256; ++nb, b = ld(m, b)) {
        const u32 base = (b + hs + al + 7) & ~(al - 1);
        for (u32 i = 0; i < hs; ++i) {
            const u8 bits = m.at(b + 8)[i];
            for (u32 k = 0; k < 8; ++k)
                if (bits & (0x80u >> k)) out.push_back(base + es * (8 * i + k));
        }
    }
    return out;
}

std::unique_ptr<Machine> snapshot_machine(const char* dir, std::vector<u8>& image) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    image = read_snapshot(dir);
    if (image.empty()) return nullptr;
    std::memcpy(m->mem.main_ram(), image.data(), image.size());
    write_rw_slots(*m);
    return m;
}
void restore(Machine& m, const std::vector<u8>& image) {
    std::memcpy(m.mem.main_ram(), image.data(), image.size());
    write_rw_slots(m);
    std::memset(m.at(kData), 0, kDataSize);
}

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair with a fresh stand-in world around each body (the heap behind the RW memory slots and the free-list entry
// points, printf / sprintf, the H_Cdvd layer); afterwards both worlds' call logs, live heap blocks and bad frees must be
// equal. Float arguments go in through g_fpr (set after the harness's randomised registers).
Fn g_body[2];
StandInWorld* g_world[2];
std::map<unsigned, float> g_fpr;
void thunk(int k, EEContext& ctx) {
    StandInsScope s(g_world[k]->si);
    for (const auto& [r, f] : g_fpr) ctx.fpr[r] = fbits(f);
    g_body[k](ctx);
}
void thunk_hand(EEContext& ctx) { thunk(0, ctx); }
void thunk_recomp(EEContext& ctx) { thunk(1, ctx); }

struct WPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    u32 v0() const { return static_cast<u32>(run.end.gpr[GPR_V0].u64[0]); }
    u64 v0_64() const { return run.end.gpr[GPR_V0].u64[0]; }
    float f0() const {
        float f;
        std::memcpy(&f, &run.end.fpr[0], 4);
        return f;
    }
};

WPair wpair(Machine& m, const Case& c, const Args& args, u32 seed, const WorldSetup& setup, const HwCheck& hw = {}) {
    WPair p;
    p.hand = std::make_unique<StandInWorld>();
    p.recomp = std::make_unique<StandInWorld>();
    setup(*p.hand);
    setup(*p.recomp);
    g_body[0] = c.hand;
    g_body[1] = c.recomp;
    g_world[0] = p.hand.get();
    g_world[1] = p.recomp.get();
    p.run = hgp::pair(m, thunk_hand, thunk_recomp, args, seed, c.name, hw);
    expect_same_log(p.hand->si, p.recomp->si, c.name);
    CHECK(p.hand->heap.live() == p.recomp->heap.live());
    CHECK(p.hand->heap.bad_frees == p.recomp->heap.bad_frees);
    g_fpr.clear();
    return p;
}
WPair wp(Machine& m, const char* name, const Args& args, u32 seed, const WorldSetup& setup = install_standard, const HwCheck& hw = {}) {
    return wpair(m, by_name(name), args, seed, setup, hw);
}

// A memory stream record over guest bytes (stream type 3, the access, position 0): access 1 reads [start, start + size),
// 2 writes into a buffer the stream grows through RwRealloc (the stand-in heap).
u32 mem_stream(Machine& m, u32 rec, u32 access, u32 start, u32 size) {
    std::memset(m.at(rec), 0, 36);
    st(m, rec + 0, 3);
    st(m, rec + 4, access);
    st(m, rec + 12, access == 3 ? size : 0);
    st(m, rec + 16, access == 2 ? 0 : size);
    st(m, rec + 20, access == 2 ? 0 : start);
    return rec;
}

// The engine-plugin entries of a registry with a plugin id (rw4::plugreg / plugentry).
std::vector<u32> registry_entries(Machine& m, u32 reg, u32 id) {
    std::vector<u32> out;
    u32 n = 0;
    for (u32 e = ld(m, reg + 16); in_ram(e, 60) && n < 256; e = ld(m, e + 48), ++n)
        if (ld(m, e + 8) == id) out.push_back(e);
    return out;
}

// =====================================================================================================================
// RpRandom
// =====================================================================================================================
// The host model of render_rw7.h: 31 words, front / rear indices.
struct HostRand {
    std::array<u32, 31> t{};
    int f = 3, r = 0;
    u32 draw() {
        t[f] += t[r];
        const u32 out = t[f] >> 1;
        ++f;
        if (f >= 31) {
            f = 0;
            ++r;
        } else {
            ++r;
            if (r >= 31) r = 0;
        }
        return out;
    }
    void seed(u32 s) {
        t[0] = s;
        for (int i = 1; i < 31; ++i) t[i] = t[i - 1] * 1103515245u + 12345u;
        f = 3;
        r = 0;
        for (int i = 0; i < 310; ++i) draw();
    }
};
struct GuestRand {
    u32 blk, table, front, rear, end;
};
GuestRand guest_rand(Machine& m) {
    GuestRand g{};
    g.blk = kEngine + ld(m, kGpRandom);
    g.table = ld(m, g.blk);
    g.front = ld(m, g.blk + 4);
    g.rear = ld(m, g.blk + 8);
    g.end = ld(m, g.blk + 12);
    return g;
}
HostRand host_from_guest(Machine& m, const GuestRand& g) {
    HostRand h;
    for (int i = 0; i < 31; ++i) h.t[static_cast<std::size_t>(i)] = ld(m, g.table + 4u * static_cast<u32>(i));
    h.f = static_cast<int>((g.front - g.table) / 4);
    h.r = static_cast<int>((g.rear - g.table) / 4);
    return h;
}
bool same_state(Machine& m, const HostRand& h) {
    const GuestRand g = guest_rand(m);
    if (g.front != g.table + 4u * static_cast<u32>(h.f) || g.rear != g.table + 4u * static_cast<u32>(h.r)) return false;
    for (int i = 0; i < 31; ++i)
        if (ld(m, g.table + 4u * static_cast<u32>(i)) != h.t[static_cast<std::size_t>(i)]) return false;
    return true;
}

// The snapshots' live generator: its invariants (end = table + 124, both pointers word-aligned inside the table, front
// three words ahead of rear modulo 31), then 160 draws, each pair's result equal to the host model's and the guest state
// after it equal to the host's; the results are 31-bit and zero-extended. Then the seeding: RpRandomSeed for edge and
// random seeds gives the host's table and pointers (the LCG fill and the 310 discarded draws) and the host's next draws;
// the open seeds 0x9A319039 into a new 124-byte table; the close frees it; RpRandomSeedMT fills its own 624 words.
TEST_CASE("game(render_rw7): RpRandom follows the host model -- the live generators, the seeding, open / close, SeedMT") {
    int snaps = 0, draws = 0, seeds = 0;
    for (const char* sn : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snaps;
        Machine& m = *mp;
        restore(m, image);
        const GuestRand g = guest_rand(m);
        INFO("snapshot " << sn << " block " << std::hex << g.blk << " table " << g.table << " front " << g.front << " rear " << g.rear);
        REQUIRE(in_ram(g.table, 124));
        CHECK(g.end == g.table + 124);
        CHECK((g.front - g.table) % 4 == 0);
        CHECK((g.rear - g.table) % 4 == 0);
        CHECK(g.front >= g.table);
        CHECK(g.front < g.end);
        CHECK(g.rear >= g.table);
        CHECK(g.rear < g.end);
        CHECK(((g.front - g.rear) / 4 + 31) % 31 == 3);
        HostRand h = host_from_guest(m, g);
        for (int k = 0; k < 160; ++k) {
            const u32 want = h.draw();
            const WPair p = wp(m, "sub_488F30", {0, 0, 0, 0}, 100000u + static_cast<u32>(snaps * 1000 + k));
            CHECK(p.v0_64() == want);
            CHECK(p.v0_64() < 0x80000000ull);
            CHECK(same_state(m, h));
            ++draws;
        }
        // RpRandomSeed
        std::mt19937 rng{0x52524E44u + static_cast<u32>(snaps)};
        std::vector<u32> list = {0u, 1u, 0x9A319039u, 0xFFFFFFFFu, 0x80000000u, 12345u};
        for (int i = 0; i < 6; ++i) {
            const u32 s = rng();
            list.push_back(s);
        }
        for (const u32 s : list) {
            restore(m, image);
            HostRand hs;
            hs.seed(s);
            wp(m, "RpRandomSeed", {s, 0, 0, 0}, 110000u + seeds);
            CHECK(same_state(m, hs));
            for (int k = 0; k < 8; ++k) {
                const u32 want = hs.draw();
                CHECK(wp(m, "sub_488F30", {0, 0, 0, 0}, 120000u + static_cast<u32>(seeds * 16 + k)).v0_64() == want);
            }
            CHECK(same_state(m, hs));
            ++seeds;
        }
        // the open: a new table from the heap, seeded 0x9A319039; the close frees it
        restore(m, image);
        const WPair o = wp(m, "sub_488D40", {kEngine, 0, 0, 0}, 130000u + snaps);
        CHECK(o.v0() == kEngine);
        CHECK(o.recomp->si.calls_to(kRwMalloc) == 1u);
        const GuestRand go = guest_rand(m);
        CHECK(o.recomp->heap.size_of(go.table) == 128u);  // 124 rounded to 16
        CHECK(go.end == go.table + 124);
        HostRand ho;
        ho.seed(0x9A319039u);
        CHECK(same_state(m, ho));
        const WPair c = wp(m, "sub_488CD0", {kEngine, 0, 0, 0}, 131000u + snaps);
        CHECK(c.v0() == kEngine);
        CHECK(c.recomp->si.calls_to(kRwFree) == 1u);
        CHECK(ld(m, go.blk) == 0u);
        // the close with no table: no free
        CHECK(wp(m, "sub_488CD0", {kEngine, 0, 0, 0}, 132000u + snaps).recomp->si.calls_to(kRwFree) == 0u);
        // RpRandomSeedMT
        for (int i = 0; i < 4; ++i) {
            const u32 s = i == 0 ? 0u : rng();
            restore(m, image);
            st(m, 0x7CDBC4u, 0x55u);
            wp(m, "RpRandomSeedMT", {s, 0, 0, 0}, 140000u + static_cast<u32>(snaps * 8 + i));
            u32 x = s | 1u;
            CHECK(ld(m, 0x95D410u) == x);
            CHECK(ld(m, 0x7CDBC4u) == 0u);
            bool ok = true;
            for (u32 j = 0; j < 623; ++j) {
                x *= 69069u;
                ok = ok && ld(m, 0x95D414u + 4 * j) == x;
            }
            CHECK(ok);
        }
    }
    if (snaps) MESSAGE("RpRandom: " << snaps << " live generators, " << draws << " draws, " << seeds << " seeds");
}

// =====================================================================================================================
// Plugin registrations and the PDS registry
// =====================================================================================================================
// Each attach run on a snapshot (whose engine has every plugin already) registers its plugins again: the engine entry it
// adds carries the same size, open and close as the live entry of that plugin id (RpRandom 0x10C, RpSpline 0x102,
// RpMatFX 0x120, RpMorph 0x105, PTank 0x12F, PDS 0x131), and the object-registry entries (materials, atomics, sectors,
// geometries) the same sizes and callbacks as the live ones.
TEST_CASE("game(render_rw7): the plugin registrations match the live registry entries of the same plugins") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    // unlinks a registry entry (next +48, prev +52; the registry's first +16 / last +20)
    auto unlink = [&m](u32 reg, u32 e) {
        const u32 next = ld(m, e + 48), prev = ld(m, e + 52);
        if (prev) st(m, prev + 48, next); else st(m, reg + 16, next);
        if (next) st(m, next + 52, prev); else st(m, reg + 20, prev);
    };
    struct Att {
        const char* name;
        u32 id;
        std::vector<u32> regs;  // the object registries it registers on
    };
    const std::vector<Att> atts = {
        {"sub_488FE0", 0x10C, {}},
        {"sub_48DCF0", 0x102, {}},
        {"sub_468C50", 0x120, {0x77DD60u, 0x77DCE0u, 0x77DDB0u}},
        {"sub_46A530", 0x105, {0x77DCE0u, 0x77DD20u}},
        {"sub_473590", 0x12F, {0x77DCE0u}},
        {"sub_46A750", 0x131, {0x77DD60u, 0x77DCE0u, 0x77DDB0u}},
    };
    int compared = 0;
    for (const Att& a : atts) {
        restore(m, image);
        std::vector<u32> regs = {kEngineRegistry};
        regs.insert(regs.end(), a.regs.begin(), a.regs.end());
        // the live entries of the id taken out of their registries (a registration refuses an id already there; the
        // entries' bytes stay where they are) and the engine-started query (sub_4CA500) answered 0, as before the start
        std::vector<u32> live;
        for (const u32 reg : regs) {
            const std::vector<u32> l = registry_entries(m, reg, a.id);
            INFO(a.name << " registry " << std::hex << reg);
            REQUIRE(l.size() == 1);
            live.push_back(l.front());
            unlink(reg, l.front());
        }
        auto setup = [](StandInWorld& w) {
            install_standard(w);
            w.si.install_recorder(0x4CA500u, "engine started", 0);  // not emitted: answered 'not started'
        };
        const WPair p = wp(m, a.name, {9, 0, 0, 0}, 150000u + a.id, setup);
        INFO(a.name << " id " << std::hex << a.id);
        CHECK(p.v0() == 1u);
        for (std::size_t i = 0; i < regs.size(); ++i) {
            INFO("registry " << std::hex << regs[i]);
            const std::vector<u32> now = registry_entries(m, regs[i], a.id);
            REQUIRE(now.size() == 1);
            const u32 e = now.front(), l = live[i];
            CHECK(ld(m, e + 4) == ld(m, l + 4));  // size
            for (u32 off = 12; off <= 44; off += 4) CHECK(ld(m, e + off) == ld(m, l + off));  // the callbacks
            ++compared;
        }
    }
    // the PDS attach also set the registry up for its argument
    CHECK(ld(m, kPdsRegistry + 8) == 9u);
    CHECK(ld(m, kPdsRegistry + 4) == 0u);
    CHECK(ld(m, 0x95C45Cu) == 9u);
    MESSAGE("registrations: " << compared << " registry entries compared with the live ones");
}

// The PDS registry of each snapshot: every live entry's pipeline is what the three rights callbacks give an object
// streamed with that id; an unknown id gives 0; the engine's default material / atomic / sector pipelines are the
// registry's pipes 0x1001 / 0x1002 / 0x1003 (rw6's default-pipeline opens). The registry set-up: 20 x n bytes, 9 for 0.
TEST_CASE("game(render_rw7): the PDS registry, its rights callbacks and the live default pipelines") {
    int snaps = 0, entries = 0;
    for (const char* sn : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snaps;
        Machine& m = *mp;
        restore(m, image);
        const u32 ents = ld(m, kPdsRegistry), count = ld(m, kPdsRegistry + 4), cap = ld(m, kPdsRegistry + 8);
        INFO("snapshot " << sn << " registry " << std::hex << ents << " count " << std::dec << count << " capacity " << cap);
        REQUIRE(in_ram(ents, 20 * cap));
        CHECK(count <= cap);
        std::map<u32, u32> pipe_of;
        for (u32 i = 0; i < count; ++i) pipe_of[ld(m, ents + 20 * i + 8)] = ld(m, ents + 20 * i + 16);
        CHECK(pipe_of.size() == count);  // the ids are distinct
        const u32 pm = kEngine + ld(m, kGpPipeModule);
        CHECK(ld(m, pm + 68) == pipe_of[0x1001]);
        CHECK(ld(m, pm + 60) == pipe_of[0x1002]);
        CHECK(ld(m, pm + 64) == pipe_of[0x1003]);
        const u32 obj = kData + 0x100;
        u32 k = 0;
        std::vector<std::pair<u32, u32>> ids(pipe_of.begin(), pipe_of.end());
        ids.push_back({0x7777u, 0u});
        for (const auto& [id, pipe] : ids) {
            for (const auto& [fn, off] : std::vector<std::pair<const char*, u32>>{{"sub_46A6C0", 8u}, {"sub_46A6F0", 108u}, {"sub_46A720", 124u}}) {
                st(m, obj + off, 0xDEADBEEFu);
                const WPair p = wp(m, fn, {obj, 0, 0, id}, 160000u + snaps * 1000 + k++);
                CHECK(p.v0() == 1u);
                CHECK(ld(m, obj + off) == pipe);
            }
            ++entries;
        }
        // the registry set-up on a scratch record
        for (const u32 n : {0u, 1u, 9u, 40u}) {
            const u32 rec = kData + 0x200;
            const WPair p = wp(m, "sub_46A970", {rec, n, 0, 0}, 161000u + snaps * 100 + n);
            const u32 want = n ? n : 9u;
            CHECK(p.v0() == rec);
            CHECK(ld(m, rec + 4) == 0u);
            CHECK(ld(m, rec + 8) == want);
            CHECK(ld(m, rec + 12) == 0u);
            CHECK(p.recomp->heap.size_of(ld(m, rec)) == ((20 * want + 15) & ~15u));
        }
    }
    if (snaps) MESSAGE("PDS: " << entries << " registry ids through the three rights callbacks on " << snaps << " snapshots");
}

// =====================================================================================================================
// RpMatFX
// =====================================================================================================================
// The slot types of each effects flag (render_rw7.h): 1 bump, 2 env, 3 bump + env, 4 dual, 5 UV, 6 UV + dual.
const std::map<u32, std::pair<u32, u32>> kMatFxSlots = {{1, {1, 0}}, {2, {2, 0}}, {3, {1, 2}}, {4, {4, 0}}, {5, {5, 0}}, {6, {5, 4}}};

// A material with an RpMatFX extension in the test area: the extension pointer at material + offset, two slots.
u32 build_matfx(Machine& m, u32 mat, u32 ext, u32 flags, std::mt19937& rng) {
    const u32 off = ld(m, kGpMatFxMaterial);
    std::memset(m.at(mat), 0, 0x100);
    std::memset(m.at(ext), 0, 144);
    st(m, mat + off, ext);
    st(m, ext + 128, flags);
    const auto it = kMatFxSlots.find(flags);
    const u32 t0 = it != kMatFxSlots.end() ? it->second.first : 0, t1 = it != kMatFxSlots.end() ? it->second.second : 0;
    st(m, ext + 32, t0);
    st(m, ext + 64 + 32, t1);
    for (u32 s = 0; s < 2; ++s)
        for (u32 w = 0; w < 5; ++w) {
            const u32 v = rng();
            st(m, ext + 64 * s + 4 * w, v);
        }
    return off;
}

// The snapshots' live effect records (RpMatFX's free list): the effects flags are 0..6 and the slots' types those of
// the flags. Then on built materials of every flags value: each getter / setter against the host (the bump coefficient
// stored negated, a missing slot type faults at address 0 + offset in both bodies), RpMatFXMaterialGetEffects, the
// default GS words of each flags value, the environment / dual ALPHA words, the extension constructor and the
// atomic / sector words and their stream sizes, and the material extension's stream size against the host's sum.
TEST_CASE("game(render_rw7): RpMatFX -- the live effect records, the slot getters / setters, the GS words, the stream size") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    int live = 0;
    for (const char* sn : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        std::vector<u8> img = read_snapshot(sn);
        if (img.empty()) continue;
        restore(m, img);
        for (const u32 e : live_entries(m, ld(m, kMatFxFreeList))) {
            const u32 flags = ld(m, e + 128);
            INFO(sn << " effect record " << std::hex << e << " flags " << flags);
            const auto it = kMatFxSlots.find(flags);
            CHECK((flags == 0 || it != kMatFxSlots.end()));
            if (it == kMatFxSlots.end()) continue;
            CHECK(ld(m, e + 32) == it->second.first);
            CHECK(ld(m, e + 64 + 32) == it->second.second);
            ++live;
        }
    }
    restore(m, image);
    std::mt19937 rng{0x4D465821u};
    const u32 mat = kData + 0x100, ext = kData + 0x400;
    int checks = 0;
    for (u32 flags = 1; flags <= 6; ++flags) {
        for (int rep = 0; rep < 4; ++rep) {
            const u32 seed = 170000u + flags * 100 + static_cast<u32>(rep) * 20;
            build_matfx(m, mat, ext, flags, rng);
            const auto [t0, t1] = kMatFxSlots.at(flags);
            CHECK(wp(m, "sub_469030", {mat, 0, 0, 0}, seed).v0() == flags);
            auto slot_of = [&](u32 type) -> u32 { return t0 == type ? ext : t1 == type ? ext + 64 : 0; };
            const u32 v = rng();
            const float f = frand(rng, -4.0f, 4.0f);
            // bump
            if (const u32 s = slot_of(1)) {
                CHECK(wp(m, "sub_469280", {mat, v, 0, 0}, seed + 1).v0() == mat);
                CHECK(ld(m, s) == v);
                CHECK(wp(m, "sub_469340", {mat, 0, 0, 0}, seed + 2).v0() == v);
                g_fpr[12] = f;
                wp(m, "sub_4692E0", {mat, 0, 0, 0}, seed + 3);
                CHECK(ldf(m, s + 12) == -f);
                CHECK(wp(m, "sub_4693A0", {mat, 0, 0, 0}, seed + 4).f0() == f);
                ++checks;
            }
            if (const u32 s = slot_of(2)) {
                CHECK(wp(m, "sub_4694B0", {mat, v, 0, 0}, seed + 5).v0() == mat);
                CHECK(ld(m, s) == v);
                CHECK(wp(m, "sub_469650", {mat, 0, 0, 0}, seed + 6).v0() == v);
                g_fpr[12] = f;
                wp(m, "sub_469590", {mat, 0, 0, 0}, seed + 7);
                CHECK(ldf(m, s + 8) == f);
                CHECK(wp(m, "sub_469710", {mat, 0, 0, 0}, seed + 8).f0() == f);
                CHECK(wp(m, "sub_4695F0", {mat, 0, 0, 0}, seed + 9).v0() == ld(m, s + 4));
                CHECK(wp(m, "sub_4696B0", {mat, 0, 0, 0}, seed + 10).v0() == ld(m, s + 12));
                // the ALPHA word of the environment pass from the frame-buffer alpha switch
                for (const u32 fb : {0u, 1u}) {
                    st(m, s + 12, fb);
                    wp(m, "sub_469B50", {mat, 0, 0, 0}, seed + 11 + fb);
                    const u32 w = flags == 3 ? ext + 104 : ext + 40;
                    const u64 got = static_cast<u64>(ld(m, w)) | (static_cast<u64>(ld(m, w + 4)) << 32);
                    CHECK(got == (fb ? 88ull : 0x8000000068ull));
                }
                ++checks;
            }
            if (const u32 s = slot_of(4)) {
                CHECK(wp(m, "sub_4698E0", {mat, 0, 0, 0}, seed + 13).v0() == ld(m, s));
                const u32 out = kData + 0x800;
                CHECK(wp(m, "sub_469940", {mat, out, out + 4, 0}, seed + 14).v0() == mat);
                CHECK(ld(m, out) == ld(m, s + 4));
                CHECK(ld(m, out + 4) == ld(m, s + 8));
                // the dual ALPHA word: the 6 x 6 table by the blend modes (1, 2, 5, 6, 7 -> 0..4, else 5)
                for (int k = 0; k < 6; ++k) {
                    const u32 modes[] = {1, 2, 5, 6, 7, 3, 0, 11};
                    const u32 sb = modes[rng() % 8];
                    const u32 db = modes[rng() % 8];
                    st(m, s + 4, sb);
                    st(m, s + 8, db);
                    wp(m, "sub_469BC0", {mat, 0, 0, 0}, seed + 15 + static_cast<u32>(k));
                    auto idx = [](u32 b) -> u32 { return b == 1 ? 0 : b == 2 ? 1 : b == 5 ? 2 : b == 6 ? 3 : b == 7 ? 4 : 5; };
                    const u32 w = flags == 4 ? ext + 40 : ext + 104;
                    const u64 got = static_cast<u64>(ld(m, w)) | (static_cast<u64>(ld(m, w + 4)) << 32);
                    CHECK(got == (0x8000000000ull | m.at(0x6B4EB0u + 6 * idx(db) + idx(sb))[0]));
                }
                ++checks;
            }
            if (const u32 s = slot_of(5)) {
                const u32 b = rng();
                const u32 d = rng();
                CHECK(wp(m, "sub_4699B0", {mat, b, d, 0}, seed + 1).v0() == mat);
                CHECK(ld(m, s) == b);
                CHECK(ld(m, s + 4) == d);
                const u32 out = kData + 0x800;
                st(m, out, 0), st(m, out + 4, 0);
                CHECK(wp(m, "sub_469A10", {mat, out, out + 4, 0}, seed + 2).v0() == mat);
                CHECK(ld(m, out) == b);
                CHECK(ld(m, out + 4) == d);
                wp(m, "sub_469A10", {mat, 0, 0, 0}, seed + 3);  // null outputs: nothing stored
                ++checks;
            }
            // a getter of a slot the material lacks: both bodies fault at address 0 + offset
            if (!slot_of(5)) wp(m, "sub_469A10", {mat, kData + 0x800, 0, 0}, seed + 19);
            // the default GS words
            wp(m, "sub_469AA0", {mat, 0, 0, 0}, seed + 4);
            auto w64 = [&](u32 off) { return static_cast<u64>(ld(m, ext + off)) | (static_cast<u64>(ld(m, ext + off + 4)) << 32); };
            if (flags == 1 || flags == 3) CHECK(w64(40) == 0x8000000048ull);
            if (flags == 3) CHECK(w64(104) == 88ull);
            if (flags == 2) CHECK(w64(40) == 0x8000000068ull);
            if (flags == 4) CHECK(w64(48) == 0x1000000ull);
            if (flags == 6) CHECK(w64(112) == 0x1000000ull);
        }
    }
    // the extension constructor, the atomic / sector words and their sizes
    const u32 obj = kData + 0x1000;
    for (const auto& [ctor, dtor, copy, size, gpoff] :
         std::vector<std::tuple<const char*, const char*, const char*, const char*, u32>>{
             {"sub_4684C0", "sub_4684E0", "sub_468500", "sub_4685D0", 0x7CE73Cu}, {"sub_4685F0", "sub_468610", "sub_468630", "sub_468700", 0x7CE740u}}) {
        const u32 off = ld(m, gpoff);
        st(m, obj + off, 7);
        CHECK(wp(m, ctor, {obj, 0, 0, 0}, 179000u).v0() == obj);
        CHECK(ld(m, obj + off) == 0u);
        CHECK(wp(m, size, {obj, 0, 0, 0}, 179001u).v0() == 0u);
        st(m, obj + 0x100 + off, 5);
        wp(m, copy, {obj, obj + 0x100, 0, 0}, 179002u);
        CHECK(ld(m, obj + off) == 1u);
        CHECK(wp(m, size, {obj, 0, 0, 0}, 179003u).v0() == 4u);
        wp(m, dtor, {obj, 0, 0, 0}, 179004u);
        CHECK(ld(m, obj + off) == 0u);
    }
    st(m, obj + ld(m, kGpMatFxMaterial), 9);
    wp(m, "sub_4676A0", {obj, 0, 0, 0}, 179005u);
    CHECK(ld(m, obj + ld(m, kGpMatFxMaterial)) == 0u);
    // the material extension's stream size: texture-free slots (all texture pointers 0)
    for (u32 flags = 0; flags <= 6; ++flags) {
        build_matfx(m, mat, ext, flags, rng);
        for (u32 s = 0; s < 2; ++s)
            for (u32 w = 0; w < 3; ++w) st(m, ext + 64 * s + 4 * w, 0);
        u32 want = 0;
        if (flags) {
            want = 4;
            for (u32 s = 0; s < 2; ++s) {
                const u32 t = ld(m, ext + 64 * s + 32);
                want += 4;
                if (t == 1) want += 4 + 4 + 4;      // coefficient, two missing textures
                if (t == 2) want += 4 + 4 + 4;      // coefficient, alpha, a missing texture
                if (t == 4) want += 4 + 4 + 4;      // two blend modes, a missing texture
            }
        }
        CHECK(wp(m, "sub_468350", {mat, 0, 0, 0}, 179100u + flags).v0() == want);
    }
    MESSAGE("RpMatFX: " << live << " live effect records, " << checks << " slot checks");
}

// =====================================================================================================================
// Streams: user data, bin-mesh headers, morph keys
// =====================================================================================================================
// A written memory stream's bytes, copied into the test area (the next pair's heap starts where the buffer was).
std::vector<u8> stream_bytes(Machine& m, u32 rec) {
    const u32 pos = ld(m, rec + 12), start = ld(m, rec + 20);
    std::vector<u8> out(pos);
    if (pos && in_ram(start, pos)) std::memcpy(out.data(), m.at(start), pos);
    return out;
}
u32 place(Machine& m, u32 at, const std::vector<u8>& bytes) {
    if (!bytes.empty()) std::memcpy(m.at(at), bytes.data(), bytes.size());
    return at;
}

struct HostArray {
    std::string name;
    u32 format = 0;
    std::vector<u32> words;          // ints / reals
    std::vector<std::string> strs;   // strings ("" = a null string pointer)
    std::vector<bool> null_str;
};
// Builds a user data list {count, arrays} at `list` with its arrays, names and elements in the test area from `pool`.
void build_userdata(Machine& m, u32 list, u32& pool, const std::vector<HostArray>& arrays) {
    const u32 arr = pool;
    pool += 16 * static_cast<u32>(arrays.size()) + 16;
    st(m, list, static_cast<u32>(arrays.size()));
    st(m, list + 4, arrays.empty() ? 0 : arr);
    for (std::size_t i = 0; i < arrays.size(); ++i) {
        const HostArray& a = arrays[i];
        const u32 r = arr + 16 * static_cast<u32>(i);
        u32 name = 0;
        if (!a.name.empty()) {
            name = pool;
            sts(m, name, a.name.c_str());
            pool += (static_cast<u32>(a.name.size()) + 16) & ~15u;
        }
        st(m, r, name);
        st(m, r + 4, a.format);
        const u32 n = a.format == 3 ? static_cast<u32>(a.strs.size()) : static_cast<u32>(a.words.size());
        st(m, r + 8, n);
        const u32 data = pool;
        pool += (4 * n + 16) & ~15u;
        st(m, r + 12, data);
        for (u32 j = 0; j < n; ++j) {
            if (a.format == 3) {
                u32 sp = 0;
                if (!a.null_str[j]) {
                    sp = pool;
                    sts(m, sp, a.strs[j].c_str());
                    pool += (static_cast<u32>(a.strs[j].size()) + 16) & ~15u;
                }
                st(m, data + 4 * j, sp);
            } else {
                st(m, data + 4 * j, a.words[j]);
            }
        }
    }
}
std::string rand_name(std::mt19937& rng) {
    const u32 len = rng() % 12;
    std::string s;
    for (u32 i = 0; i < len; ++i) {
        const u32 c = rng() % 26;
        s += static_cast<char>('a' + c);
    }
    return s;
}

// User data lists of random arrays (ints, reals, strings with empty and null ones, named and unnamed) on an object at a
// plugin offset: the extension's stream size equals the host's sum and the bytes written; reading the written bytes
// back on another object gives the same arrays; the destructor frees every name, string, element array and the array
// of arrays (RwFree calls counted); the constructor clears; the array getters / setters and the format size.
TEST_CASE("game(render_rw7): user data lists -- stream size, write and read back equal, destroy, the array accessors") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x55534452u};
    int lists = 0, arrays_n = 0;
    for (int k = 0; k < 24; ++k) {
        restore(m, image);
        std::vector<HostArray> arrays;
        const u32 na = k == 0 ? 0u : 1 + rng() % 4;
        u32 want_size = 0;
        for (u32 i = 0; i < na; ++i) {
            HostArray a;
            a.name = rand_name(rng);
            a.format = 1 + rng() % 3;
            // (an int / real array without elements fails the read: RwStreamReadInt32 / Real of 0 bytes returns 0, and
            // the extension reader goes on with a null stream -- checked below)
            const u32 n0 = rng() % 6;
            const u32 n = a.format == 3 ? n0 : 1 + n0;
            for (u32 j = 0; j < n; ++j) {
                if (a.format == 3) {
                    const bool nul = rng() % 5 == 0;
                    a.null_str.push_back(nul);
                    a.strs.push_back(nul ? std::string() : rand_name(rng));
                } else {
                    const u32 w = a.format == 2 ? fbits(frand(rng, -100.0f, 100.0f)) : static_cast<u32>(rng());
                    a.words.push_back(w);
                }
            }
            u32 sz = 4 + (a.name.empty() ? 0 : static_cast<u32>(a.name.size()) + 1) + 8;
            if (a.format == 3)
                for (std::size_t j = 0; j < a.strs.size(); ++j) sz += 4 + (a.null_str[j] ? 0 : static_cast<u32>(a.strs[j].size()) + 1);
            else
                sz += 4 * static_cast<u32>(a.words.size());
            want_size += sz;
            arrays.push_back(a);
        }
        if (want_size) want_size += 4;
        const u32 off = 0x40, obj = kData + 0x100, obj2 = kData + 0x200, srec = kData + 0x300;
        u32 pool = kData + 0x1000;
        build_userdata(m, obj + off, pool, arrays);
        const u32 seed = 200000u + static_cast<u32>(k) * 16;
        CHECK(wp(m, "sub_48ED20", {obj, off, 0, 0}, seed).v0() == want_size);
        mem_stream(m, srec, 2, 0, 0);
        CHECK(wp(m, "sub_48ECF0", {srec, 0, obj, off}, seed + 1).v0() == srec);
        const std::vector<u8> bytes = stream_bytes(m, srec);
        CHECK(bytes.size() == want_size);
        // read back (the arrays with a format: all of them here)
        const u32 buf = place(m, kData + 0x20000, bytes);
        mem_stream(m, srec, 1, buf, static_cast<u32>(bytes.size()));
        std::memset(m.at(obj2), 0, 0x80);
        if (!bytes.empty()) {
            CHECK(wp(m, "sub_48EC20", {srec, 0, obj2, off}, seed + 2).v0() == srec);
            REQUIRE(ld(m, obj2 + off) == na);
            const u32 arr = ld(m, obj2 + off + 4);
            for (u32 i = 0; i < na; ++i) {
                const HostArray& a = arrays[i];
                const u32 r = arr + 16 * i;
                std::string desc;
                for (const HostArray& x : arrays)
                    desc += " {" + std::to_string(x.format) + "," + std::to_string(x.format == 3 ? x.strs.size() : x.words.size()) + ",'" + x.name + "'}";
                INFO("list " << k << " array " << i << ":" << desc);
                REQUIRE(in_ram(r, 16));
                // (an unnamed array's name word is left as RwMalloc returned it: the reader skips a 0 length)
                if (!a.name.empty()) {
                    REQUIRE(in_ram(ld(m, r), 16));
                    CHECK(lds(m, ld(m, r)) == a.name);
                }
                CHECK(ld(m, r + 4) == a.format);
                const u32 n = ld(m, r + 8);
                CHECK(n == (a.format == 3 ? a.strs.size() : a.words.size()));
                const u32 data = ld(m, r + 12);
                REQUIRE(in_ram(data, 4 * std::min(n, 8u)));
                for (u32 j = 0; j < n && j < 8; ++j) {
                    if (a.format == 3) {
                        const u32 sp = ld(m, data + 4 * j);
                        CHECK((sp == 0) == a.null_str[j]);
                        if (sp) CHECK(lds(m, sp) == a.strs[j]);
                    } else {
                        CHECK(ld(m, data + 4 * j) == a.words[j]);
                    }
                }
                ++arrays_n;
            }
        }
        // the destructor on the built list: every name, string, element array and the array of arrays
        u32 frees = na ? 1u : 0u;
        for (const HostArray& a : arrays) {
            frees += a.name.empty() ? 0 : 1;
            frees += 1;  // the elements
            if (a.format == 3)
                for (std::size_t j = 0; j < a.strs.size(); ++j) frees += a.null_str[j] ? 0 : 1;
        }
        const WPair d = wp(m, "sub_48EAB0", {obj, off, 0, 0}, seed + 3);
        CHECK(d.v0() == obj);
        CHECK(d.recomp->si.calls_to(kRwFree) == frees);
        CHECK(ld(m, obj + off) == 0u);
        CHECK(ld(m, obj + off + 4) == 0u);
        st(m, obj + off, 5), st(m, obj + off + 4, 6);
        wp(m, "sub_48EA90", {obj, off, 0, 0}, seed + 4);
        CHECK(ld(m, obj + off) == 0u);
        CHECK(ld(m, obj + off + 4) == 0u);
        ++lists;
    }
    // the accessors on one array
    restore(m, image);
    const u32 r = kData + 0x100, data = kData + 0x200;
    st(m, r, kData + 0x180), st(m, r + 4, 2), st(m, r + 8, 7), st(m, r + 12, data);
    CHECK(wp(m, "name__C9type_info_0", {r, 0, 0, 0}, 201000u).v0() == kData + 0x180);
    CHECK(wp(m, "sub_48EF20", {r, 0, 0, 0}, 201001u).v0() == 2u);
    CHECK(wp(m, "sub_48EF30", {r, 0, 0, 0}, 201002u).v0() == 7u);
    for (u32 i = 0; i < 7; ++i) {
        const u32 v = rng();
        wp(m, "sub_48EFA0", {r, i, v, 0}, 201010u + i);
        CHECK(ld(m, data + 4 * i) == v);
        CHECK(wp(m, "sub_48EF40", {r, i, 0, 0}, 201020u + i).v0() == v);
        const float f = frand(rng, -9.0f, 9.0f);
        g_fpr[12] = f;
        wp(m, "sub_48EFC0", {r, i, 0, 0}, 201030u + i);
        CHECK(ldf(m, data + 4 * i) == f);
        CHECK(wp(m, "sub_48EF60", {r, i, 0, 0}, 201040u + i).f0() == f);
    }
    for (u32 fmt = 0; fmt < 6; ++fmt) CHECK(wp(m, "sub_48EFE0", {fmt, 0, 0, 0}, 201050u + fmt).v0() == ((fmt >= 1 && fmt <= 3) ? 4u : 0u));
    // the rule above: an array of no ints / reals cannot be read back (0); one of no strings can (the stream)
    for (u32 fmt = 1; fmt <= 4; ++fmt) {
        const u32 buf = kData + 0x3000, srec = kData + 0x3100;
        st(m, buf, 0), st(m, buf + 4, fmt), st(m, buf + 8, 0);
        mem_stream(m, srec, 1, buf, 12);
        CHECK(wp(m, "sub_48E020", {kData + 0x3200, srec, 0, 0}, 201060u + fmt).v0() == (fmt == 3 ? srec : 0u));
    }
    // adding arrays to a list (the first array without data is reused, else the list grows by one) and the extension
    // copy (every array duplicated: names and strings as new strings, elements copied)
    for (int k = 0; k < 8; ++k) {
        restore(m, image);
        const u32 off = 0x40, obj = kData + 0x100, obj2 = kData + 0x200;
        std::memset(m.at(obj), 0, 0x100);
        std::memset(m.at(obj2), 0, 0x100);
        sts(m, kData + 0x3000, "first"), sts(m, kData + 0x3010, "second"), sts(m, kData + 0x3020, "third");
        // one pair per added array; each step's world reserves the heap the earlier steps used, so their blocks stay
        for (u32 i = 0; i < 3; ++i) {
            const u32 fmt = 1 + rng() % 3;
            const u32 cnt = 1 + rng() % 4;
            const u32 base = 0x01C00000u + 0x20000u * (i + 1);
            auto w2 = [base](StandInWorld& w) {
                install_standard(w);
                w.heap.reserve(0x01C00000u, base - 0x01C00000u);  // the earlier steps' blocks stay allocated
            };
            const u32 name = i == 2 ? 0u : kData + 0x3000 + 16 * i;
            const WPair p = wp(m, "sub_48E890", {obj + off, name, fmt, cnt}, 205000u + static_cast<u32>(k) * 8 + i, w2);
            CHECK(p.v0() == i);
            CHECK(ld(m, obj + off) == i + 1);
            const u32 r = ld(m, obj + off + 4) + 16 * i;
            CHECK(ld(m, r + 4) == fmt);
            CHECK(ld(m, r + 8) == cnt);
            if (name) CHECK(lds(m, ld(m, r)) == lds(m, name));
            else CHECK(ld(m, r) == 0u);
            bool zero = true;
            for (u32 j = 0; j < 4 * cnt; j += 4) zero = zero && ld(m, ld(m, r + 12) + j) == 0;
            CHECK(zero);
        }
        // give the string arrays strings, then copy the list onto obj2
        const u32 arr = ld(m, obj + off + 4);
        for (u32 i = 0; i < 3; ++i)
            if (ld(m, arr + 16 * i + 4) == 3)
                for (u32 j = 0; j < ld(m, arr + 16 * i + 8); ++j) st(m, ld(m, arr + 16 * i + 12) + 4 * j, j % 2 ? kData + 0x3010 : 0);
            else
                for (u32 j = 0; j < ld(m, arr + 16 * i + 8); ++j) {
                    const u32 v = rng();
                    st(m, ld(m, arr + 16 * i + 12) + 4 * j, v);
                }
        auto w3 = [](StandInWorld& w) {
            install_standard(w);
            w.heap.reserve(0x01C00000u, 0x80000u);
        };
        CHECK(wp(m, "sub_48EB50", {obj2, obj, off, 0}, 205100u + static_cast<u32>(k), w3).v0() == obj2);
        REQUIRE(ld(m, obj2 + off) == 3u);
        const u32 arr2 = ld(m, obj2 + off + 4);
        for (u32 i = 0; i < 3; ++i) {
            const u32 a = arr + 16 * i, b = arr2 + 16 * i;
            CHECK(ld(m, b + 4) == ld(m, a + 4));
            CHECK(ld(m, b + 8) == ld(m, a + 8));
            if (ld(m, a)) {
                CHECK(ld(m, b) != ld(m, a));
                CHECK(lds(m, ld(m, b)) == lds(m, ld(m, a)));
            }
            for (u32 j = 0; j < ld(m, a + 8); ++j) {
                const u32 x = ld(m, ld(m, a + 12) + 4 * j), y = ld(m, ld(m, b + 12) + 4 * j);
                if (ld(m, a + 4) == 3) {
                    CHECK((x == 0) == (y == 0));
                    if (x) CHECK(lds(m, y) == lds(m, x));
                } else {
                    CHECK(y == x);
                }
            }
        }
    }
    MESSAGE("user data: " << lists << " lists, " << arrays_n << " arrays read back");
}

// The snapshots' real bin-mesh headers (the live atomics' geometries, +84): the geometry's bin-mesh stream size equals
// the bytes its write produces; reading them back onto a copy of the geometry gives the same header -- flags, mesh
// count, total indices, each mesh's index count, material and (unless native data) indices -- with the next serial
// number (the engine counter, incremented). Then the morph keys of built geometries: the size and the written words.
TEST_CASE("game(render_rw7): bin-mesh headers of the snapshots' geometries -- size, write, read back equal; the morph keys") {
    int geos = 0, meshes = 0, inconsistent = 0;
    for (const char* sn : {"dorm_replay_4900", "b_5800"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        Machine& m = *mp;
        restore(m, image);
        std::set<u32> gset;
        for (const u32 a : live_entries(m, ld(m, kEngine + ld(m, 0x7CE820u)))) {
            const u32 g = ld(m, a + 24);
            if (in_ram(g, 128) && in_ram(ld(m, g + 84), 16)) gset.insert(g);
        }
        int k = 0;
        for (const u32 g : gset) {
            if (k >= 24) break;
            restore(m, image);
            const u32 hdr = ld(m, g + 84);
            const u32 srec = kData + 0x300, g2 = kData + 0x400;
            const u32 seed = 210000u + static_cast<u32>(geos) * 8;
            const u32 size = wp(m, "sub_49BCC0", {g, 0, 0, 0}, seed).v0();
            mem_stream(m, srec, 2, 0, 0);
            CHECK(wp(m, "sub_49BC50", {srec, 0, g, 0}, seed + 1).v0() == srec);
            const std::vector<u8> bytes = stream_bytes(m, srec);
            INFO(sn << " geometry " << std::hex << g << " header " << hdr);
            // the size counts the header's total index count (+8), the write each mesh's own count: equal unless the
            // header's total disagrees with its meshes (some snapshot geometries carry a total of 0)
            const bool nat = (ld(m, g + 8) & 0x1000000u) != 0 && (m.at(g)[0] == 7 || m.at(g)[0] == 8);
            const u32 nm = ld16(m, hdr + 4);
            u32 sum = 0;
            for (u32 i = 0; i < nm; ++i) sum += ld(m, hdr + 16 + 12 * i + 4);
            CHECK(size == 12 + 8 * nm + (nat ? 0 : 4 * ld(m, hdr + 8)));
            CHECK(bytes.size() == 12 + 8 * nm + (nat ? 0 : 4 * sum));
            if (ld(m, hdr + 8) != sum) ++inconsistent;
            const u32 buf = place(m, kData + 0x20000, bytes);
            mem_stream(m, srec, 1, buf, static_cast<u32>(bytes.size()));
            std::memcpy(m.at(g2), m.at(g), 128);
            st(m, g2 + 84, 0);
            const u32 ctr = kEngine + ld(m, kGpMeshSerial);
            const u16 serial = ld16(m, ctr);
            CHECK(wp(m, "sub_49BC70", {srec, 0, g2, 0}, seed + 2).v0() == srec);
            const u32 h2 = ld(m, g2 + 84);
            REQUIRE(in_ram(h2, 16));
            CHECK(ld16(m, h2 + 6) == serial);
            CHECK(ld16(m, ctr) == static_cast<u16>(serial + 1));
            CHECK(ld(m, h2) == ld(m, hdr));
            CHECK(ld16(m, h2 + 4) == ld16(m, hdr + 4));
            CHECK(ld(m, h2 + 8) == ld(m, hdr + 8));
            const bool native = (ld(m, g + 8) & 0x1000000u) != 0 && (m.at(g)[0] == 7 || m.at(g)[0] == 8);
            for (u32 i = 0; i < ld16(m, hdr + 4); ++i) {
                const u32 a = hdr + 16 + 12 * i, b = h2 + 16 + 12 * i;
                CHECK(ld(m, b + 4) == ld(m, a + 4));
                CHECK(ld(m, b + 8) == ld(m, a + 8));
                if (!native && in_ram(ld(m, a), 2 * ld(m, a + 4))) {
                    bool same = true;
                    for (u32 j = 0; j < ld(m, a + 4); ++j) same = same && ld16(m, ld(m, b) + 2 * j) == ld16(m, ld(m, a) + 2 * j);
                    CHECK(same);
                }
                ++meshes;
            }
            ++geos;
            ++k;
        }
    }
    // the morph keys
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (mp) {
        Machine& m = *mp;
        std::mt19937 rng{0x4D525048u};
        for (int k = 0; k < 8; ++k) {
            restore(m, image);
            const u32 geo = kData + 0x100, keys = kData + 0x400, srec = kData + 0x300;
            const u32 off = ld(m, kGpMorphGeometry);
            const u32 n = static_cast<u32>(k);
            st(m, geo + off, n), st(m, geo + off + 4, 0x46A400u), st(m, geo + off + 8, n ? keys : 0);
            for (u32 i = 0; i < n; ++i) {
                const u32 kk = keys + 20 * i;
                const u32 typ = rng() % 3;
                const u32 s0 = rng() % 9;
                const u32 s1 = rng() % 9;
                const u32 nx = rng() % n;
                st(m, kk, typ), st16(m, kk + 4, static_cast<u16>(s0)), st16(m, kk + 6, static_cast<u16>(s1));
                stf(m, kk + 8, frand(rng, 0.1f, 3.0f));
                st(m, kk + 16, keys + 20 * nx);
            }
            const u32 seed = 220000u + static_cast<u32>(k) * 4;
            CHECK(wp(m, "sub_46A3C0", {geo, 0, 0, 0}, seed).v0() == (n ? 20 * n + 4 : 0u));
            mem_stream(m, srec, 2, 0, 0);
            CHECK(wp(m, "sub_46A0F0", {srec, 0, geo, 0}, seed + 1).v0() == srec);
            const std::vector<u8> bytes = stream_bytes(m, srec);
            REQUIRE(bytes.size() == 4 + 20 * n);
            auto w = [&](u32 i) {
                u32 v;
                std::memcpy(&v, bytes.data() + 4 * i, 4);
                return v;
            };
            CHECK(w(0) == n);
            for (u32 i = 0; i < n; ++i) {
                const u32 kk = keys + 20 * i;
                CHECK(w(1 + 5 * i) == ld(m, kk));
                CHECK(w(2 + 5 * i) == static_cast<u32>(static_cast<s32>(static_cast<s16>(ld16(m, kk + 4)))));
                CHECK(w(3 + 5 * i) == static_cast<u32>(static_cast<s32>(static_cast<s16>(ld16(m, kk + 6)))));
                CHECK(w(4 + 5 * i) == ld(m, kk + 8));
                CHECK(w(5 + 5 * i) == (ld(m, kk + 16) - keys) / 20);
            }
            // the default key-end callback: the atomic's key becomes its next
            if (n) {
                const u32 atom = kData + 0x800, aoff = ld(m, kGpMorphAtomic);
                st(m, atom + aoff, keys);
                CHECK(wp(m, "sub_46A400", {atom, 0, 0, 0}, seed + 2).v0() == ld(m, keys + 16));
                CHECK(ld(m, atom + aoff) == ld(m, keys + 16));
            }
            // read the written keys back onto another geometry (RpMorphGeometryCreateInterpolators inside): the same
            // keys, 1 / duration at +12, the next keys as pointers into the new array
            const u32 geo2 = kData + 0x1000, buf = place(m, kData + 0x20000, bytes);
            std::memset(m.at(geo2), 0, 0x100);
            mem_stream(m, srec, 1, buf, static_cast<u32>(bytes.size()));
            const WPair rd = wp(m, "sub_46A230", {srec, 0, geo2, 0}, seed + 3);
            CHECK(rd.v0() == srec);
            if (n) {
                CHECK(ld(m, geo2 + off) == n);
                const u32 k2 = ld(m, geo2 + off + 8);
                CHECK(rd.recomp->heap.size_of(k2) == ((20 * n + 15) & ~15u));
                for (u32 i = 0; i < n; ++i) {
                    const u32 a = keys + 20 * i, b = k2 + 20 * i;
                    CHECK(ld(m, b) == ld(m, a));
                    CHECK(ld16(m, b + 4) == ld16(m, a + 4));
                    CHECK(ld16(m, b + 6) == ld16(m, a + 6));
                    CHECK(ld(m, b + 8) == ld(m, a + 8));
                    CHECK(std::fabs(ldf(m, b + 12) * ldf(m, a + 8) - 1.0f) < 1e-5f);
                    CHECK(ld(m, b + 16) - k2 == ld(m, a + 16) - keys);
                }
            }
            // RpMorphGeometryCreateInterpolators: the old keys freed, n zeroed keys
            const u32 m2 = 1 + rng() % 8;
            const WPair cr = wp(m, "sub_46A470", {geo2, m2, 0, 0}, seed + 4);
            CHECK(cr.v0() == geo2);
            CHECK(cr.recomp->si.calls_to(kRwFree) == (n ? 1u : 0u));
            CHECK(ld(m, geo2 + off) == m2);
            bool zero = true;
            for (u32 i = 0; i < 20 * m2; i += 4) zero = zero && ld(m, ld(m, geo2 + off + 8) + i) == 0;
            CHECK(zero);
        }
    }
    MESSAGE("bin-mesh: " << geos << " geometries, " << meshes << " meshes read back; " << inconsistent << " headers whose total index count is not their meshes' sum");
}

// =====================================================================================================================
// RpSpline
// =====================================================================================================================
// The uniform cubic B-spline basis at t and its first and second derivatives.
void host_basis(double t, double b[12]) {
    const double u = 1.0 - t;
    b[0] = u * u * u / 6.0;
    b[1] = (3 * t * t * t - 6 * t * t + 4) / 6.0;
    b[2] = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0;
    b[3] = t * t * t / 6.0;
    b[4] = -u * u / 2.0;
    b[5] = (3 * t * t - 4 * t) / 2.0;
    b[6] = (-3 * t * t + 2 * t + 1) / 2.0;
    b[7] = t * t / 2.0;
    b[8] = u;
    b[9] = 3 * t - 2;
    b[10] = -3 * t + 1;
    b[11] = t;
}
// The live basis tables (each snapshot) and a freshly built set: each of the twelve 257-entry tables is one of the host's
// basis functions (or derivatives) at t = i / 256, every function exactly once; the fresh tables equal the live ones.
// Then splines with 4..9 control points, open and closed: the solve, then RpSplineFindPosition at every control point's
// parameter returns that point (the curve interpolates), the tangent is a unit vector, the nice-ends path agrees at the
// ends; RpSplineSetControlPoint moves one point and the curve follows; an index out of range fails.
TEST_CASE("game(render_rw7): RpSpline -- the basis tables, the solve, RpSplineFindPosition, RpSplineSetControlPoint") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    restore(m, image);
    auto check_tables = [&](const char* what) {
        std::set<int> used;
        for (u32 k = 0; k < 12; ++k) {
            const u32 tab = ld(m, kGpSplineBasis + 4 * k);
            REQUIRE(in_ram(tab, 257 * 4));
            int best = -1;
            double best_err = 1e9;
            for (int f = 0; f < 12; ++f) {
                double err = 0;
                for (u32 i = 0; i <= 256; ++i) {
                    double b[12];
                    host_basis(i / 256.0, b);
                    err = std::max(err, std::fabs(ldf(m, tab + 4 * i) - b[f]));
                }
                if (err < best_err) best_err = err, best = f;
            }
            INFO(what << " table " << k << " best " << best << " err " << best_err);
            CHECK(best_err < 2e-5);
            used.insert(best);
        }
        CHECK(used.size() == 12u);
    };
    check_tables("live");
    std::vector<std::vector<float>> live(12);
    for (u32 k = 0; k < 12; ++k)
        for (u32 i = 0; i <= 256; ++i) live[k].push_back(ldf(m, ld(m, kGpSplineBasis + 4 * k) + 4 * i));
    CHECK(wp(m, "sub_48AD20", {0, 0, 0, 0}, 230000u).v0() == 1u);
    check_tables("fresh");
    bool same = true;
    for (u32 k = 0; k < 12; ++k)
        for (u32 i = 0; i <= 256; ++i) same = same && fbits(ldf(m, ld(m, kGpSplineBasis + 4 * k) + 4 * i)) == fbits(live[k][i]);
    CHECK(same);
    // the end matrices: freshly built for 4..10 points, equal to the live ones of the open (0x95DE40 + 4 n)
    int matrices = 0;
    for (u32 n = 4; n <= 10; ++n) {
        const u32 live_m = ld(m, 0x95DE40u + 4 * n);
        REQUIRE(in_ram(live_m, 4 * n * n));
        const WPair p = wp(m, "sub_48AF80", {n, 0, 0, 0}, 230100u + n);
        REQUIRE(in_ram(p.v0(), 4 * n * n));
        bool eq = true;
        for (u32 i = 0; i < n * n; ++i) eq = eq && ld(m, p.v0() + 4 * i) == ld(m, live_m + 4 * i);
        CHECK(eq);
        ++matrices;
    }
    // splines
    std::mt19937 rng{0x53504C4Eu};
    int splines = 0, points = 0;
    for (int k = 0; k < 24; ++k) {
        restore(m, image);
        const u32 type = 1 + static_cast<u32>(k % 2);
        const u32 n = 4 + rng() % 6;
        const u32 internal = n + (type == 2 ? 3 : 2);
        const u32 sp = kData + 0x2000, user = kData + 0x3000;
        std::memset(m.at(sp), 0, 56 + 12 * internal + 64);
        st(m, sp + 8, internal), st(m, sp + 12, type), st(m, sp + 20, user);
        std::vector<std::array<float, 3>> pts(n);
        for (u32 i = 0; i < n; ++i)
            for (u32 c = 0; c < 3; ++c) {
                pts[i][c] = frand(rng, -50.0f, 50.0f);
                stf(m, user + 12 * i + 4 * c, pts[i][c]);
            }
        const u32 seed = 231000u + static_cast<u32>(k) * 64;
        CHECK(wp(m, "sub_48B910", {sp, user, 0, 0}, seed).v0() != 0u);
        CHECK(wp(m, "sub_48D200", {sp, 0, 0, 0}, seed + 1).v0() == n);
        const u32 segs = type == 2 ? n : n - 1;
        const u32 pos = kData + 0x4000, tan = kData + 0x4010;
        for (u32 i = 0; i < n; ++i) {
            g_fpr[12] = static_cast<float>(i) / static_cast<float>(segs);
            CHECK(wp(m, "sub_48D480", {sp, 10, pos, tan}, seed + 2 + i).v0() == pos);
            double err = 0, tl = 0;
            for (u32 c = 0; c < 3; ++c) {
                err = std::max(err, static_cast<double>(std::fabs(ldf(m, pos + 4 * c) - pts[i][c])));
                tl += static_cast<double>(ldf(m, tan + 4 * c)) * ldf(m, tan + 4 * c);
            }
            INFO("spline " << k << " type " << type << " n " << n << " point " << i);
            CHECK(err < 1e-2);
            CHECK(std::fabs(tl - 1.0) < 1e-3);
            ++points;
        }
        // the nice-ends path agrees with the smooth one at both ends
        for (const float t : {0.0f, 1.0f}) {
            g_fpr[12] = t;
            wp(m, "sub_48D480", {sp, 10, pos, 0}, seed + 30);
            const std::array<float, 3> a = {ldf(m, pos), ldf(m, pos + 4), ldf(m, pos + 8)};
            g_fpr[12] = t;
            wp(m, "sub_48D480", {sp, 11, pos, 0}, seed + 31);
            for (u32 c = 0; c < 3; ++c) CHECK(std::fabs(ldf(m, pos + 4 * c) - a[c]) < 1e-3);
        }
        // move one point
        const u32 i = rng() % n;
        const u32 np = kData + 0x4100;
        std::array<float, 3> q{};
        for (u32 c = 0; c < 3; ++c) {
            q[c] = frand(rng, -50.0f, 50.0f);
            stf(m, np + 4 * c, q[c]);
        }
        CHECK(wp(m, "sub_48D370", {sp, i, np, 0}, seed + 40).v0() == sp);
        g_fpr[12] = static_cast<float>(i) / static_cast<float>(segs);
        wp(m, "sub_48D480", {sp, 10, pos, 0}, seed + 41);
        for (u32 c = 0; c < 3; ++c) CHECK(std::fabs(ldf(m, pos + 4 * c) - q[c]) < 1e-2);
        CHECK(wp(m, "sub_48D370", {sp, n, np, 0}, seed + 42).v0() == 0u);
        CHECK(wp(m, "sub_48D370", {sp, 0xFFFFFFFFu, np, 0}, seed + 43).v0() == 0u);
        ++splines;
    }
    MESSAGE("RpSpline: " << splines << " splines, " << points << " control points found on the curve, " << matrices << " end matrices equal to the live ones");
}

// =====================================================================================================================
// PTank, fonts, brushes
// =====================================================================================================================
// The tank data allocations for random formats against the host's layout: the component order position, matrix, normal,
// size, colour, vertex colours, rotation, two / four tex coords, the strides of the table 0x7BC900; one RwMalloc of the
// summed sizes + 16 (separate) or particles x the record (interleaved; 16-rounded with a matrix); the component count;
// the format's low 9 bits rewritten. The data size of sub_4753D0 for random counts and formats.
TEST_CASE("game(render_rw7): the PTank allocations and data size follow the host's layout") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    restore(m, image);
    const u32 flag[9] = {0x1, 0x8, 0x10, 0x4, 0x2, 0x40, 0x20, 0x80, 0x100};
    const u32 slot[9] = {84, 92, 100, 108, 116, 124, 132, 140, 148};
    const u32 sep_stride[9] = {12, 64, 12, 8, 4, 16, 4, 16, 32};
    u32 tab[9];
    for (u32 i = 0; i < 9; ++i) tab[i] = ld(m, 0x7BC900u + 4 * i);
    std::mt19937 rng{0x5054414Eu};
    int allocs = 0;
    for (int k = 0; k < 48; ++k) {
        restore(m, image);
        const u32 data = kData + 0x100;
        std::memset(m.at(data), 0, 176);
        const u32 count = 1 + rng() % 40;
        const u32 fmt = rng() & 0x1FFu;
        const u32 high = rng() & 0xFFFFFE00u;
        st(m, data, count);
        st(m, data + 168, high | 0x1FFu);
        const bool inter = (k & 1) != 0;
        const WPair p = wp(m, inter ? "sub_473B10" : "sub_473600", {data, fmt, 0, 0}, 240000u + static_cast<u32>(k));
        INFO("format " << std::hex << fmt << " count " << std::dec << count << (inter ? " interleaved" : " separate"));
        CHECK(p.v0() == 1u);
        CHECK(p.recomp->si.calls_to(kRwMalloc) == 1u);
        u32 ncomp = 0, rec = 0;
        for (u32 i = 0; i < 9; ++i)
            if (fmt & flag[i]) ++ncomp, rec += tab[i];
        if (inter && (fmt & 8)) rec = (rec + 15) & ~15u;
        CHECK(ld(m, data + 160) == ncomp);
        CHECK(ld(m, data + 168) == (high | fmt));
        const u32 block = ld(m, data + 12);
        const u32 base = (block + 15) & ~15u;
        const u32 req = rec * count + 16;  // separate: the arrays one after the other, the same total
        CHECK(p.recomp->heap.size_of(block) == ((req + 15) & ~15u));
        u32 at = 0;
        for (u32 i = 0; i < 9; ++i) {
            if (!(fmt & flag[i])) continue;
            CHECK(ld(m, data + slot[i]) == base + at);
            CHECK(ld(m, data + slot[i] + 4) == (inter ? rec : sep_stride[i]));
            at += inter ? tab[i] : tab[i] * count;
        }
        if (inter) CHECK(ld(m, data + 164) == rec);
        ++allocs;
    }
    // the data size
    for (int k = 0; k < 64; ++k) {
        const u32 n = rng() % 100;
        const u32 fmt = rng() & 0x1FFu;
        u32 want = 0;
        if (fmt & 1) want = (16 * n + 15) & ~15u;
        const u32 order[8] = {0x8, 0x10, 0x4, 0x2, 0x40, 0x20, 0x80, 0x100};
        const u32 ti[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (u32 j = 0; j < 8; ++j)
            if (fmt & order[j]) want += (n * tab[ti[j]] + ((order[j] == 0x4 || order[j] == 0x2) ? 79 : 15)) & ~15u;
        CHECK(wp(m, "sub_4753D0", {n, fmt, 0, 0}, 241000u + static_cast<u32>(k)).v0() == want);
    }
    MESSAGE("PTank: " << allocs << " allocations");
}

// Fonts: the high-code map from a code table (minimum / maximum positive codes, a u16 glyph index per code, -1 for
// none), the string width against the host's float sum (one- and two-byte codes, unmapped codes adding nothing), the
// unicode flag; brushes: the UV set-up (origins, deltas, flag bit 1) and the texture set (reference count, flag).
TEST_CASE("game(render_rw7): the Rt2d font map, string width, unicode flag and the brush set-ups") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x464F4E54u};
    int fonts = 0;
    for (int k = 0; k < 16; ++k) {
        restore(m, image);
        const u32 font = kData + 0x100, codes = kData + 0x400, glyphs = kData + 0x800, sl = kData + 0x700;
        std::memset(m.at(font), 0, 324);
        const u32 ng = 4 + rng() % 20;
        std::vector<s32> code(ng);
        for (u32 i = 0; i < ng; ++i) {
            const u32 r = rng() % 6;
            code[i] = r == 0 ? 0 : r == 1 ? -5 : static_cast<s32>(128 + rng() % 300);
            st(m, codes + 4 * i, static_cast<u32>(code[i]));
        }
        st(m, 0x95F984u, codes);
        st(m, font + 304, ng);
        const WPair p = wp(m, "sub_4A7620", {font, 0, 0, 0}, 250000u + static_cast<u32>(k) * 8);
        s32 lo = 0xFFFF, hi = 0;
        bool any = false;
        for (const s32 c : code)
            if (c > 0) lo = std::min(lo, c), hi = std::max(hi, c), any = true;
        CHECK(p.v0() == font);
        if (any) {
            CHECK(ld(m, font + 292) == static_cast<u32>(lo));
            CHECK(ld(m, font + 296) == static_cast<u32>(hi - lo + 1));
            const u32 map = ld(m, font + 300);
            for (s32 c = lo; c <= hi; ++c) {
                s32 want = -1;
                for (u32 i = 0; i < ng; ++i)
                    if (code[i] == c) want = static_cast<s32>(i);
                CHECK(static_cast<s16>(ld16(m, map + 2 * static_cast<u32>(c - lo))) == want);
            }
        } else {
            CHECK(p.recomp->si.calls_to(kRwMalloc) == 0u);
        }
        // the string width: glyph advances in an sList, the low map, a gap
        const u32 nglyph = 16;
        st(m, sl, glyphs), st(m, sl + 4, nglyph), st(m, sl + 8, nglyph), st(m, sl + 12, 32);
        std::vector<float> adv(nglyph);
        for (u32 i = 0; i < nglyph; ++i) {
            adv[i] = frand(rng, 0.5f, 20.0f);
            stf(m, glyphs + 32 * i, adv[i]);
        }
        st(m, font + 308, sl);
        const float gap = frand(rng, 0.0f, 2.0f);
        stf(m, font + 12, gap);
        for (u32 c = 0; c < 128; ++c) {
            const u32 r = rng() % 20;
            st16(m, font + 36 + 2 * c, static_cast<u16>(r < 16 ? r : 0xFFFFu));
        }
        const bool uni = (k & 1) != 0;
        st(m, font + 16, uni ? 2u : 0u);
        CHECK(wp(m, "sub_4A9BD0", {font, 0, 0, 0}, 250000u + static_cast<u32>(k) * 8 + 1).v0() == (uni ? 1u : 0u));
        const u32 str = kData + 0x1800;
        const u32 len = 1 + rng() % 20;
        std::vector<u8> bytes;
        for (u32 i = 0; i < len; ++i) {
            const u32 c = 1 + rng() % 127;
            bytes.push_back(static_cast<u8>(c));
            if (uni) bytes.push_back(0);
        }
        bytes.push_back(0);
        bytes.push_back(0);
        std::memcpy(m.at(str), bytes.data(), bytes.size());
        float want = 0.0f;
        for (u32 i = 0; i < len; ++i) {
            const u32 c = bytes[uni ? 2 * i : i];
            const s16 gi = static_cast<s16>(ld16(m, font + 36 + 2 * c));
            if (gi >= 0) want = want + (adv[static_cast<u32>(gi)] + gap);
        }
        const float height = frand(rng, 0.25f, 4.0f);
        want = want * height;  // the sum times the height ($f12)
        g_fpr[12] = height;
        const WPair w = wp(m, "sub_4A9560", {font, str, 0, 0}, 250000u + static_cast<u32>(k) * 8 + 2);
        // (the R5900's single precision rounds towards zero: a few units in the last place from the host's sum)
        CHECK(std::fabs(w.f0() - want) <= 1e-5f * std::fabs(want) + 1e-6f);
        ++fonts;
    }
    // brushes
    restore(m, image);
    const u32 br = kData + 0x100, pts = kData + 0x200;
    for (int k = 0; k < 8; ++k) {
        std::memset(m.at(br), 0, 120);
        st(m, br + 100, 0xF0u | (k & 1 ? 2u : 0u));
        for (u32 i = 0; i < 8; ++i) stf(m, pts + 4 * i, k == 0 ? 0.25f : frand(rng, -1.0f, 1.0f));
        wp(m, "sub_4A6200", {br, pts, pts + 8, pts + 16}, 251000u + static_cast<u32>(k), install_standard, HwCheck{{}, {}, {}, {{GPR_T0, pts + 24}}});
        CHECK(ldf(m, br + 16) == ldf(m, pts + 24));
        CHECK(ldf(m, br + 40) == ldf(m, pts + 16) - ldf(m, pts + 24));
        CHECK(ldf(m, br + 64) == ldf(m, pts));
        CHECK(ldf(m, br + 88) == ldf(m, pts + 8) - ldf(m, pts));
        const bool moving = ldf(m, br + 40) != 0.0f || ldf(m, br + 44) != 0.0f || ldf(m, br + 88) != 0.0f || ldf(m, br + 92) != 0.0f;
        CHECK(ld(m, br + 100) == (0xF0u | (moving ? 2u : 0u)));
    }
    const u32 tex = kData + 0x400;
    std::memset(m.at(tex), 0, 96);
    st(m, tex + 84, 3);
    st(m, br + 104, 0);
    CHECK(wp(m, "sub_4A62E0", {br, tex, 0, 0}, 252000u).v0() == br);
    CHECK(ld(m, tex + 84) == 4u);
    CHECK(ld(m, br + 104) == tex);
    CHECK((ld(m, br + 100) & 2u) == 2u);
    // the brush colours: four byte colours as floats, the edge deltas, the first packed
    for (int k = 0; k < 8; ++k) {
        const u32 cols = kData + 0x500;
        std::array<u8, 16> c{};
        for (u32 i = 0; i < 16; ++i) {
            const u32 v = rng() % 256;
            c[i] = static_cast<u8>(v);
            m.at(cols)[i] = c[i];
        }
        // $a1 = colour 1, $a2 = colour 2, $a3 = colour 3, $t0 = colour 0
        CHECK(wp(m, "sub_4A5DD0", {br, cols + 4, cols + 8, cols + 12}, 253000u + static_cast<u32>(k), install_standard,
                 HwCheck{{}, {}, {}, {{GPR_T0, cols}}}).v0() == br);
        for (u32 i = 0; i < 4; ++i) {
            CHECK(ldf(m, br + 4 * i) == static_cast<float>(c[i]));
            CHECK(ldf(m, br + 24 + 4 * i) == static_cast<float>(c[12 + i]) - static_cast<float>(c[i]));
            CHECK(ldf(m, br + 48 + 4 * i) == static_cast<float>(c[4 + i]));
            CHECK(ldf(m, br + 72 + 4 * i) == static_cast<float>(c[8 + i]) - static_cast<float>(c[4 + i]));
            CHECK(m.at(br + 96)[i] == c[i]);
        }
    }
    // the brush create: white, no UVs, no texture, 0.5 at +112, one reference, from the brush free list
    const WPair cb = wp(m, "sub_4A5470", {0, 0, 0, 0}, 254000u);
    const u32 nb = cb.v0();
    REQUIRE(in_ram(nb, 120));
    CHECK(cb.recomp->si.calls_to(0x4C3D10u) == 1u);
    for (u32 i = 0; i < 4; ++i) {
        CHECK(ldf(m, nb + 4 * i) == 255.0f);
        CHECK(ldf(m, nb + 48 + 4 * i) == 255.0f);
        CHECK(ldf(m, nb + 24 + 4 * i) == 0.0f);
        CHECK(m.at(nb + 96)[i] == 0xFF);
    }
    CHECK(ldf(m, nb + 16) == 0.0f);
    CHECK(ld(m, nb + 104) == 0u);
    CHECK((ld(m, nb + 100) & 2u) == 0u);
    CHECK(ldf(m, nb + 112) == 0.5f);
    CHECK(ld(m, nb + 116) == 1u);
    MESSAGE("fonts: " << fonts << " fonts");
}

// =====================================================================================================================
// The sweeps
// =====================================================================================================================
// Every body on the three snapshots with built records: a soup of words pointing into itself, at small values and at
// the snapshot's live RW records, arguments drawn from the soup, small values and the live engine block.
TEST_CASE("game(render_rw7): every body equals its recompiled body on the snapshots with built records") {
    int pairs = 0, whole = 0, snapshots = 0;
    std::map<std::string, int> runs;
    for (const char* sn : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snapshots;
        Machine& m = *mp;
        std::mt19937 rng{0x52574F00u + static_cast<u32>(snapshots)};
        const std::vector<u32> fx = live_entries(m, ld(m, kMatFxFreeList));
        for (const Case& c : kCases) {
            // the two BSP walks recurse through any plane the soup offers (a cycle overflows the host stack before the
            // guest's): they run on built trees below
            if (c.addr == 0x499720 || c.addr == 0x499850) continue;
            for (int k = 0; k < 10; ++k) {
                restore(m, image);
                const u32 soup = kData + 0x1000;
                const u32 seed = rng();
                auto setup = [&m, soup, seed, &fx](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(kCallback, "callback (returns 0)", 0);
                    w.si.install_recorder(0x4CA500u, "engine started", 0);
                    st(m, 0x95EFD0u, kCallback);  // the Rt2d toolkit hook sub_4A9BE0 calls
                    std::mt19937 r{seed};
                    for (u32 i = 0; i < 0x2000; i += 4) {
                        const u32 kind = r() % 8;
                        u32 v;
                        if (kind < 3) {
                            const u32 off = r() % 0x2000;
                            v = soup + (off & ~15u);
                        } else if (kind < 5) {
                            v = r() % 8;
                        } else if (kind < 6 && !fx.empty()) {
                            const u32 j = r() % static_cast<u32>(fx.size());
                            v = fx[j];
                        } else {
                            v = r() % 3 == 0 ? 0xFFFFFFFFu : 0;
                        }
                        st(m, soup + i, v);
                    }
                };
                Args a{};
                for (int i = 0; i < 4; ++i) {
                    const u32 pick = rng() % 4;
                    const u32 off = rng() % 0x2000;
                    a[static_cast<std::size_t>(i)] = pick < 2 ? soup + (off & ~15u) : pick == 2 ? off % 6 : kEngine;
                }
                const u32 t0off = rng() % 0x2000;
                const WPair p = wpair(m, c, a, 190000u + static_cast<u32>(pairs), setup, HwCheck{{}, {}, {}, {{GPR_T0, soup + (t0off & ~15u)}, {GPR_T1, soup + 0x600}}});
                ++pairs;
                whole += p.run.stopped ? 0 : 1;
                runs[c.name] += p.run.stopped ? 0 : 1;
            }
        }
    }
    if (snapshots == 0) return;
    // the BSP walks on built trees: planes (type 0 / 4 / 8) down to sectors (type -1, empty tie lists) and type -2 leaves
    {
        std::vector<u8> image;
        auto mp = snapshot_machine("dorm_replay_4900", image);
        if (mp) {
            Machine& m = *mp;
            std::mt19937 rng{0x42535054u};
            for (int k = 0; k < 24; ++k) {
                restore(m, image);
                u32 next = kData + 0x1000;
                std::function<u32(int)> build = [&](int depth) -> u32 {
                    const u32 n = next;
                    next += 0x100;
                    std::memset(m.at(n), 0, 0x100);
                    const u32 r = rng() % 4;
                    if (depth == 0 || r == 0) {
                        st(m, n, 0xFFFFFFFFu);  // a sector
                        st(m, n + 56, n + 56), st(m, n + 60, n + 56);
                        st(m, n + 64, n + 64), st(m, n + 68, n + 64);
                    } else if (r == 1) {
                        st(m, n, 0xFFFFFFFEu);
                    } else {
                        st(m, n, 4 * (rng() % 3));
                        const u32 left = build(depth - 1);
                        const u32 right = build(depth - 1);
                        st(m, n + 8, left), st(m, n + 12, right);
                    }
                    return n;
                };
                const u32 root = build(1 + static_cast<int>(rng() % 4));
                const WPair p = wp(m, k % 2 ? "sub_499850" : "sub_499720", {root, 0, 0, 0}, 195000u + static_cast<u32>(k));
                ++pairs;
                whole += p.run.stopped ? 0 : 1;
            }
        }
    }
    MESSAGE("built-record pairs: " << pairs << " on " << snapshots << " snapshots, run whole " << whole);
    std::string never;
    for (const auto& [name, r] : runs)
        if (r == 0) never += name + " ";
    if (!never.empty()) MESSAGE("never run whole there: " << never);
}

// Every body against its recompiled body on random worlds (the p3fes_handgen sweep), each function from a fresh ELF
// image (the module opens / closes of earlier functions write the words later ones read).
TEST_CASE("game(render_rw7): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> elf_image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        std::memcpy(m->mem.main_ram(), elf_image.data(), elf_image.size());
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (std::size_t i = 0; i < 4; ++i) args[i] = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

#else

TEST_CASE("game(render_rw7): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
