// Pair tests of slice tartarus2 (game/src/field/tartarus2*.cpp): every hand body against its recompiled body.
//   1. Random worlds (tests/game/handgen_pairs.h): all 107 functions, the whole register file and cycles at every check
//      point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log.
//   2. The replay snapshots with live Tartarus state (extracted/_ours: climb_ref_17000 / climb_ref_39820 from the full
//      climb, b_6700 from the battle route; each part skips cleanly when absent): the live "npc think proc" tasks in
//      every mode, sub-state, tactic and pending action; the party helpers by member index; the path search and the
//      wall-following rules on the floors' real 16 x 16 grids; the live "y_smap draw proc" in every state.
//   3. Task creators with their updates and destroy callbacks on the stand-ins (stand_ins.h: the heap, printf /
//      sprintf, the H_Cdvd layer over extracted/ -- smap/*.tmx, stratum/stratum_dat --, recorders for the field
//      callees this test library does not emit): the stratum-parts task in every state, the Kyoto NPC tasks, the wait
//      task, the time limit, the enemy band's creators, the treasure-free and symbol-direction tasks.
//   4. Documented rules on the results of both bodies: the path search finds a path iff the host's breadth-first search
//      over the open sides reaches the goal (and the step list starts at the goal), the 2 x 2 block origin is 0 off
//      wide blocks, sub_43C7A0 sets the mode and clears the sub-states, the column test sub_437E20, the held flags, the
//      time limit's mm:ss digits, the stratum record's defaults, the creators' work fields, the waypoint pause table
//      0x7BC610, the wait task's frame count.
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function (random worlds), one function, a trace line per pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/tartarus2.h"

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
namespace tart2 = p3fes::game::tart2;

namespace p3fes::recomp_gen {
void fn_Y_SMap_UpdateSmapDrawTask_004281f0(EEContext&);  // generated body
void fn_Y_SMap_UpdateSmapDrawTask_004281f0__recomp(EEContext&);  // recompiled
void fn_sub_429C60_00429c60(EEContext&);  // generated body
void fn_sub_429C60_00429c60__recomp(EEContext&);  // recompiled
void fn_Y_SMap_CreateSmapDrawTask_00429d40(EEContext&);  // generated body
void fn_Y_SMap_CreateSmapDrawTask_00429d40__recomp(EEContext&);  // recompiled
void fn_sub_42AA40_0042aa40(EEContext&);  // generated body
void fn_sub_42AA40_0042aa40__recomp(EEContext&);  // recompiled
void fn_sub_42AC60_0042ac60(EEContext&);  // generated body
void fn_sub_42AC60_0042ac60__recomp(EEContext&);  // recompiled
void fn_sub_4302B0_004302b0(EEContext&);  // generated body
void fn_sub_4302B0_004302b0__recomp(EEContext&);  // recompiled
void fn_Y_SMap_CreateSmapMaskDrawTask_00431110(EEContext&);  // generated body
void fn_Y_SMap_CreateSmapMaskDrawTask_00431110__recomp(EEContext&);  // recompiled
void fn_Y_Npc_UpdateNpcThinkTask_004312b0(EEContext&);  // generated body
void fn_Y_Npc_UpdateNpcThinkTask_004312b0__recomp(EEContext&);  // recompiled
void fn_sub_431630_00431630(EEContext&);  // generated body
void fn_sub_431630_00431630__recomp(EEContext&);  // recompiled
void fn_Y_Npc_CreateNpcThinkTask_00431670(EEContext&);  // generated body
void fn_Y_Npc_CreateNpcThinkTask_00431670__recomp(EEContext&);  // recompiled
void fn_sub_431880_00431880(EEContext&);  // generated body
void fn_sub_431880_00431880__recomp(EEContext&);  // recompiled
void fn_sub_431AA0_00431aa0(EEContext&);  // generated body
void fn_sub_431AA0_00431aa0__recomp(EEContext&);  // recompiled
void fn_sub_432050_00432050(EEContext&);  // generated body
void fn_sub_432050_00432050__recomp(EEContext&);  // recompiled
void fn_sub_432600_00432600(EEContext&);  // generated body
void fn_sub_432600_00432600__recomp(EEContext&);  // recompiled
void fn_sub_432BB0_00432bb0(EEContext&);  // generated body
void fn_sub_432BB0_00432bb0__recomp(EEContext&);  // recompiled
void fn_sub_433160_00433160(EEContext&);  // generated body
void fn_sub_433160_00433160__recomp(EEContext&);  // recompiled
void fn_sub_4332F0_004332f0(EEContext&);  // generated body
void fn_sub_4332F0_004332f0__recomp(EEContext&);  // recompiled
void fn_sub_4333D0_004333d0(EEContext&);  // generated body
void fn_sub_4333D0_004333d0__recomp(EEContext&);  // recompiled
void fn_sub_4334D0_004334d0(EEContext&);  // generated body
void fn_sub_4334D0_004334d0__recomp(EEContext&);  // recompiled
void fn_sub_433810_00433810(EEContext&);  // generated body
void fn_sub_433810_00433810__recomp(EEContext&);  // recompiled
void fn_sub_4339D0_004339d0(EEContext&);  // generated body
void fn_sub_4339D0_004339d0__recomp(EEContext&);  // recompiled
void fn_sub_433DE0_00433de0(EEContext&);  // generated body
void fn_sub_433DE0_00433de0__recomp(EEContext&);  // recompiled
void fn_sub_4343D0_004343d0(EEContext&);  // generated body
void fn_sub_4343D0_004343d0__recomp(EEContext&);  // recompiled
void fn_sub_4344F0_004344f0(EEContext&);  // generated body
void fn_sub_4344F0_004344f0__recomp(EEContext&);  // recompiled
void fn_sub_434770_00434770(EEContext&);  // generated body
void fn_sub_434770_00434770__recomp(EEContext&);  // recompiled
void fn_sub_434920_00434920(EEContext&);  // generated body
void fn_sub_434920_00434920__recomp(EEContext&);  // recompiled
void fn_sub_434C90_00434c90(EEContext&);  // generated body
void fn_sub_434C90_00434c90__recomp(EEContext&);  // recompiled
void fn_sub_434D30_00434d30(EEContext&);  // generated body
void fn_sub_434D30_00434d30__recomp(EEContext&);  // recompiled
void fn_sub_434E60_00434e60(EEContext&);  // generated body
void fn_sub_434E60_00434e60__recomp(EEContext&);  // recompiled
void fn_sub_434F60_00434f60(EEContext&);  // generated body
void fn_sub_434F60_00434f60__recomp(EEContext&);  // recompiled
void fn_sub_435060_00435060(EEContext&);  // generated body
void fn_sub_435060_00435060__recomp(EEContext&);  // recompiled
void fn_sub_4350E0_004350e0(EEContext&);  // generated body
void fn_sub_4350E0_004350e0__recomp(EEContext&);  // recompiled
void fn_sub_435260_00435260(EEContext&);  // generated body
void fn_sub_435260_00435260__recomp(EEContext&);  // recompiled
void fn_sub_4352E0_004352e0(EEContext&);  // generated body
void fn_sub_4352E0_004352e0__recomp(EEContext&);  // recompiled
void fn_sub_435370_00435370(EEContext&);  // generated body
void fn_sub_435370_00435370__recomp(EEContext&);  // recompiled
void fn_sub_4353F0_004353f0(EEContext&);  // generated body
void fn_sub_4353F0_004353f0__recomp(EEContext&);  // recompiled
void fn_sub_435440_00435440(EEContext&);  // generated body
void fn_sub_435440_00435440__recomp(EEContext&);  // recompiled
void fn_sub_435660_00435660(EEContext&);  // generated body
void fn_sub_435660_00435660__recomp(EEContext&);  // recompiled
void fn_sub_435810_00435810(EEContext&);  // generated body
void fn_sub_435810_00435810__recomp(EEContext&);  // recompiled
void fn_sub_4359F0_004359f0(EEContext&);  // generated body
void fn_sub_4359F0_004359f0__recomp(EEContext&);  // recompiled
void fn_sub_435C00_00435c00(EEContext&);  // generated body
void fn_sub_435C00_00435c00__recomp(EEContext&);  // recompiled
void fn_sub_437E00_00437e00(EEContext&);  // generated body
void fn_sub_437E00_00437e00__recomp(EEContext&);  // recompiled
void fn_sub_437E20_00437e20(EEContext&);  // generated body
void fn_sub_437E20_00437e20__recomp(EEContext&);  // recompiled
void fn_sub_437E80_00437e80(EEContext&);  // generated body
void fn_sub_437E80_00437e80__recomp(EEContext&);  // recompiled
void fn_sub_438010_00438010(EEContext&);  // generated body
void fn_sub_438010_00438010__recomp(EEContext&);  // recompiled
void fn_sub_439400_00439400(EEContext&);  // generated body
void fn_sub_439400_00439400__recomp(EEContext&);  // recompiled
void fn_sub_439520_00439520(EEContext&);  // generated body
void fn_sub_439520_00439520__recomp(EEContext&);  // recompiled
void fn_sub_439F60_00439f60(EEContext&);  // generated body
void fn_sub_439F60_00439f60__recomp(EEContext&);  // recompiled
void fn_sub_43A0B0_0043a0b0(EEContext&);  // generated body
void fn_sub_43A0B0_0043a0b0__recomp(EEContext&);  // recompiled
void fn_sub_43A1A0_0043a1a0(EEContext&);  // generated body
void fn_sub_43A1A0_0043a1a0__recomp(EEContext&);  // recompiled
void fn_sub_43A230_0043a230(EEContext&);  // generated body
void fn_sub_43A230_0043a230__recomp(EEContext&);  // recompiled
void fn_sub_43A2F0_0043a2f0(EEContext&);  // generated body
void fn_sub_43A2F0_0043a2f0__recomp(EEContext&);  // recompiled
void fn_sub_43A960_0043a960(EEContext&);  // generated body
void fn_sub_43A960_0043a960__recomp(EEContext&);  // recompiled
void fn_sub_43A9D0_0043a9d0(EEContext&);  // generated body
void fn_sub_43A9D0_0043a9d0__recomp(EEContext&);  // recompiled
void fn_sub_43B980_0043b980(EEContext&);  // generated body
void fn_sub_43B980_0043b980__recomp(EEContext&);  // recompiled
void fn_sub_43BC20_0043bc20(EEContext&);  // generated body
void fn_sub_43BC20_0043bc20__recomp(EEContext&);  // recompiled
void fn_sub_43BDA0_0043bda0(EEContext&);  // generated body
void fn_sub_43BDA0_0043bda0__recomp(EEContext&);  // recompiled
void fn_sub_43BF50_0043bf50(EEContext&);  // generated body
void fn_sub_43BF50_0043bf50__recomp(EEContext&);  // recompiled
void fn_sub_43C180_0043c180(EEContext&);  // generated body
void fn_sub_43C180_0043c180__recomp(EEContext&);  // recompiled
void fn_sub_43C340_0043c340(EEContext&);  // generated body
void fn_sub_43C340_0043c340__recomp(EEContext&);  // recompiled
void fn_Y_Npc_UpdateTreasureFreeTask_0043c500(EEContext&);  // generated body
void fn_Y_Npc_UpdateTreasureFreeTask_0043c500__recomp(EEContext&);  // recompiled
void fn_sub_43C660_0043c660(EEContext&);  // generated body
void fn_sub_43C660_0043c660__recomp(EEContext&);  // recompiled
void fn_Y_Npc_CreateTreasureFreeTask_0043c690(EEContext&);  // generated body
void fn_Y_Npc_CreateTreasureFreeTask_0043c690__recomp(EEContext&);  // recompiled
void fn_sub_43C730_0043c730(EEContext&);  // generated body
void fn_sub_43C730_0043c730__recomp(EEContext&);  // recompiled
void fn_sub_43C7A0_0043c7a0(EEContext&);  // generated body
void fn_sub_43C7A0_0043c7a0__recomp(EEContext&);  // recompiled
void fn_sub_43C7F0_0043c7f0(EEContext&);  // generated body
void fn_sub_43C7F0_0043c7f0__recomp(EEContext&);  // recompiled
void fn_sub_43C910_0043c910(EEContext&);  // generated body
void fn_sub_43C910_0043c910__recomp(EEContext&);  // recompiled
void fn_Y_StParts_UpdateStratumPartsTask_0043ca30(EEContext&);  // generated body
void fn_Y_StParts_UpdateStratumPartsTask_0043ca30__recomp(EEContext&);  // recompiled
void fn_sub_447AD0_00447ad0(EEContext&);  // generated body
void fn_sub_447AD0_00447ad0__recomp(EEContext&);  // recompiled
void fn_Y_Stratum_CreateStratumPartsTask_00447e70(EEContext&);  // generated body
void fn_Y_Stratum_CreateStratumPartsTask_00447e70__recomp(EEContext&);  // recompiled
void fn_sub_449ED0_00449ed0(EEContext&);  // generated body
void fn_sub_449ED0_00449ed0__recomp(EEContext&);  // recompiled
void fn_sub_449FA0_00449fa0(EEContext&);  // generated body
void fn_sub_449FA0_00449fa0__recomp(EEContext&);  // recompiled
void fn_sub_44A990_0044a990(EEContext&);  // generated body
void fn_sub_44A990_0044a990__recomp(EEContext&);  // recompiled
void fn_sub_44ACF0_0044acf0(EEContext&);  // generated body
void fn_sub_44ACF0_0044acf0__recomp(EEContext&);  // recompiled
void fn_Y_Stratum_CreateEneThinkTask_0044ad20(EEContext&);  // generated body
void fn_Y_Stratum_CreateEneThinkTask_0044ad20__recomp(EEContext&);  // recompiled
void fn_sub_454290_00454290(EEContext&);  // generated body
void fn_sub_454290_00454290__recomp(EEContext&);  // recompiled
void fn_Y_Stratum_CreateEneDeadEffectTask_004542c0(EEContext&);  // generated body
void fn_Y_Stratum_CreateEneDeadEffectTask_004542c0__recomp(EEContext&);  // recompiled
void fn_sub_455E00_00455e00(EEContext&);  // generated body
void fn_sub_455E00_00455e00__recomp(EEContext&);  // recompiled
void fn_sub_456050_00456050(EEContext&);  // generated body
void fn_sub_456050_00456050__recomp(EEContext&);  // recompiled
void fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0(EEContext&);  // generated body
void fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_UpdateKyotoNpcModeReadTask_004575e0(EEContext&);  // generated body
void fn_Y_Kyoto_UpdateKyotoNpcModeReadTask_004575e0__recomp(EEContext&);  // recompiled
void fn_sub_457980_00457980(EEContext&);  // generated body
void fn_sub_457980_00457980__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0(EEContext&);  // generated body
void fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_UpdateKyotoNpcThinkTask_00457a40(EEContext&);  // generated body
void fn_Y_Kyoto_UpdateKyotoNpcThinkTask_00457a40__recomp(EEContext&);  // recompiled
void fn_sub_458600_00458600(EEContext&);  // generated body
void fn_sub_458600_00458600__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630(EEContext&);  // generated body
void fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630__recomp(EEContext&);  // recompiled
void fn_sub_458850_00458850(EEContext&);  // generated body
void fn_sub_458850_00458850__recomp(EEContext&);  // recompiled
void fn_sub_458870_00458870(EEContext&);  // generated body
void fn_sub_458870_00458870__recomp(EEContext&);  // recompiled
void fn_sub_458890_00458890(EEContext&);  // generated body
void fn_sub_458890_00458890__recomp(EEContext&);  // recompiled
void fn_sub_458920_00458920(EEContext&);  // generated body
void fn_sub_458920_00458920__recomp(EEContext&);  // recompiled
void fn_sub_458930_00458930(EEContext&);  // generated body
void fn_sub_458930_00458930__recomp(EEContext&);  // recompiled
void fn_sub_4589D0_004589d0(EEContext&);  // generated body
void fn_sub_4589D0_004589d0__recomp(EEContext&);  // recompiled
void fn_sub_4589E0_004589e0(EEContext&);  // generated body
void fn_sub_4589E0_004589e0__recomp(EEContext&);  // recompiled
void fn_sub_458A80_00458a80(EEContext&);  // generated body
void fn_sub_458A80_00458a80__recomp(EEContext&);  // recompiled
void fn_sub_458B00_00458b00(EEContext&);  // generated body
void fn_sub_458B00_00458b00__recomp(EEContext&);  // recompiled
void fn_sub_458B60_00458b60(EEContext&);  // generated body
void fn_sub_458B60_00458b60__recomp(EEContext&);  // recompiled
void fn_sub_458BB0_00458bb0(EEContext&);  // generated body
void fn_sub_458BB0_00458bb0__recomp(EEContext&);  // recompiled
void fn_sub_458CB0_00458cb0(EEContext&);  // generated body
void fn_sub_458CB0_00458cb0__recomp(EEContext&);  // recompiled
void fn_sub_459790_00459790(EEContext&);  // generated body
void fn_sub_459790_00459790__recomp(EEContext&);  // recompiled
void fn_sub_459D60_00459d60(EEContext&);  // generated body
void fn_sub_459D60_00459d60__recomp(EEContext&);  // recompiled
void fn_sub_459E00_00459e00(EEContext&);  // generated body
void fn_sub_459E00_00459e00__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_UpdateWaitTask_00459e80(EEContext&);  // generated body
void fn_Y_Kyoto_UpdateWaitTask_00459e80__recomp(EEContext&);  // recompiled
void fn_sub_459F30_00459f30(EEContext&);  // generated body
void fn_sub_459F30_00459f30__recomp(EEContext&);  // recompiled
void fn_Y_Kyoto_CreateWaitTask_00459f60(EEContext&);  // generated body
void fn_Y_Kyoto_CreateWaitTask_00459f60__recomp(EEContext&);  // recompiled
void fn_sub_45A220_0045a220(EEContext&);  // generated body
void fn_sub_45A220_0045a220__recomp(EEContext&);  // recompiled
void fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280(EEContext&);  // generated body
void fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"Y_SMap_UpdateSmapDrawTask", 0x4281F0, &recomp_gen::fn_Y_SMap_UpdateSmapDrawTask_004281f0, &recomp_gen::fn_Y_SMap_UpdateSmapDrawTask_004281f0__recomp},
    {"sub_429C60", 0x429C60, &recomp_gen::fn_sub_429C60_00429c60, &recomp_gen::fn_sub_429C60_00429c60__recomp},
    {"Y_SMap_CreateSmapDrawTask", 0x429D40, &recomp_gen::fn_Y_SMap_CreateSmapDrawTask_00429d40, &recomp_gen::fn_Y_SMap_CreateSmapDrawTask_00429d40__recomp},
    {"sub_42AA40", 0x42AA40, &recomp_gen::fn_sub_42AA40_0042aa40, &recomp_gen::fn_sub_42AA40_0042aa40__recomp},
    {"sub_42AC60", 0x42AC60, &recomp_gen::fn_sub_42AC60_0042ac60, &recomp_gen::fn_sub_42AC60_0042ac60__recomp},
    {"sub_4302B0", 0x4302B0, &recomp_gen::fn_sub_4302B0_004302b0, &recomp_gen::fn_sub_4302B0_004302b0__recomp},
    {"Y_SMap_CreateSmapMaskDrawTask", 0x431110, &recomp_gen::fn_Y_SMap_CreateSmapMaskDrawTask_00431110, &recomp_gen::fn_Y_SMap_CreateSmapMaskDrawTask_00431110__recomp},
    {"Y_Npc_UpdateNpcThinkTask", 0x4312B0, &recomp_gen::fn_Y_Npc_UpdateNpcThinkTask_004312b0, &recomp_gen::fn_Y_Npc_UpdateNpcThinkTask_004312b0__recomp},
    {"sub_431630", 0x431630, &recomp_gen::fn_sub_431630_00431630, &recomp_gen::fn_sub_431630_00431630__recomp},
    {"Y_Npc_CreateNpcThinkTask", 0x431670, &recomp_gen::fn_Y_Npc_CreateNpcThinkTask_00431670, &recomp_gen::fn_Y_Npc_CreateNpcThinkTask_00431670__recomp},
    {"sub_431880", 0x431880, &recomp_gen::fn_sub_431880_00431880, &recomp_gen::fn_sub_431880_00431880__recomp},
    {"sub_431AA0", 0x431AA0, &recomp_gen::fn_sub_431AA0_00431aa0, &recomp_gen::fn_sub_431AA0_00431aa0__recomp},
    {"sub_432050", 0x432050, &recomp_gen::fn_sub_432050_00432050, &recomp_gen::fn_sub_432050_00432050__recomp},
    {"sub_432600", 0x432600, &recomp_gen::fn_sub_432600_00432600, &recomp_gen::fn_sub_432600_00432600__recomp},
    {"sub_432BB0", 0x432BB0, &recomp_gen::fn_sub_432BB0_00432bb0, &recomp_gen::fn_sub_432BB0_00432bb0__recomp},
    {"sub_433160", 0x433160, &recomp_gen::fn_sub_433160_00433160, &recomp_gen::fn_sub_433160_00433160__recomp},
    {"sub_4332F0", 0x4332F0, &recomp_gen::fn_sub_4332F0_004332f0, &recomp_gen::fn_sub_4332F0_004332f0__recomp},
    {"sub_4333D0", 0x4333D0, &recomp_gen::fn_sub_4333D0_004333d0, &recomp_gen::fn_sub_4333D0_004333d0__recomp},
    {"sub_4334D0", 0x4334D0, &recomp_gen::fn_sub_4334D0_004334d0, &recomp_gen::fn_sub_4334D0_004334d0__recomp},
    {"sub_433810", 0x433810, &recomp_gen::fn_sub_433810_00433810, &recomp_gen::fn_sub_433810_00433810__recomp},
    {"sub_4339D0", 0x4339D0, &recomp_gen::fn_sub_4339D0_004339d0, &recomp_gen::fn_sub_4339D0_004339d0__recomp},
    {"sub_433DE0", 0x433DE0, &recomp_gen::fn_sub_433DE0_00433de0, &recomp_gen::fn_sub_433DE0_00433de0__recomp},
    {"sub_4343D0", 0x4343D0, &recomp_gen::fn_sub_4343D0_004343d0, &recomp_gen::fn_sub_4343D0_004343d0__recomp},
    {"sub_4344F0", 0x4344F0, &recomp_gen::fn_sub_4344F0_004344f0, &recomp_gen::fn_sub_4344F0_004344f0__recomp},
    {"sub_434770", 0x434770, &recomp_gen::fn_sub_434770_00434770, &recomp_gen::fn_sub_434770_00434770__recomp},
    {"sub_434920", 0x434920, &recomp_gen::fn_sub_434920_00434920, &recomp_gen::fn_sub_434920_00434920__recomp},
    {"sub_434C90", 0x434C90, &recomp_gen::fn_sub_434C90_00434c90, &recomp_gen::fn_sub_434C90_00434c90__recomp},
    {"sub_434D30", 0x434D30, &recomp_gen::fn_sub_434D30_00434d30, &recomp_gen::fn_sub_434D30_00434d30__recomp},
    {"sub_434E60", 0x434E60, &recomp_gen::fn_sub_434E60_00434e60, &recomp_gen::fn_sub_434E60_00434e60__recomp},
    {"sub_434F60", 0x434F60, &recomp_gen::fn_sub_434F60_00434f60, &recomp_gen::fn_sub_434F60_00434f60__recomp},
    {"sub_435060", 0x435060, &recomp_gen::fn_sub_435060_00435060, &recomp_gen::fn_sub_435060_00435060__recomp},
    {"sub_4350E0", 0x4350E0, &recomp_gen::fn_sub_4350E0_004350e0, &recomp_gen::fn_sub_4350E0_004350e0__recomp},
    {"sub_435260", 0x435260, &recomp_gen::fn_sub_435260_00435260, &recomp_gen::fn_sub_435260_00435260__recomp},
    {"sub_4352E0", 0x4352E0, &recomp_gen::fn_sub_4352E0_004352e0, &recomp_gen::fn_sub_4352E0_004352e0__recomp},
    {"sub_435370", 0x435370, &recomp_gen::fn_sub_435370_00435370, &recomp_gen::fn_sub_435370_00435370__recomp},
    {"sub_4353F0", 0x4353F0, &recomp_gen::fn_sub_4353F0_004353f0, &recomp_gen::fn_sub_4353F0_004353f0__recomp},
    {"sub_435440", 0x435440, &recomp_gen::fn_sub_435440_00435440, &recomp_gen::fn_sub_435440_00435440__recomp},
    {"sub_435660", 0x435660, &recomp_gen::fn_sub_435660_00435660, &recomp_gen::fn_sub_435660_00435660__recomp},
    {"sub_435810", 0x435810, &recomp_gen::fn_sub_435810_00435810, &recomp_gen::fn_sub_435810_00435810__recomp},
    {"sub_4359F0", 0x4359F0, &recomp_gen::fn_sub_4359F0_004359f0, &recomp_gen::fn_sub_4359F0_004359f0__recomp},
    {"sub_435C00", 0x435C00, &recomp_gen::fn_sub_435C00_00435c00, &recomp_gen::fn_sub_435C00_00435c00__recomp},
    {"sub_437E00", 0x437E00, &recomp_gen::fn_sub_437E00_00437e00, &recomp_gen::fn_sub_437E00_00437e00__recomp},
    {"sub_437E20", 0x437E20, &recomp_gen::fn_sub_437E20_00437e20, &recomp_gen::fn_sub_437E20_00437e20__recomp},
    {"sub_437E80", 0x437E80, &recomp_gen::fn_sub_437E80_00437e80, &recomp_gen::fn_sub_437E80_00437e80__recomp},
    {"sub_438010", 0x438010, &recomp_gen::fn_sub_438010_00438010, &recomp_gen::fn_sub_438010_00438010__recomp},
    {"sub_439400", 0x439400, &recomp_gen::fn_sub_439400_00439400, &recomp_gen::fn_sub_439400_00439400__recomp},
    {"sub_439520", 0x439520, &recomp_gen::fn_sub_439520_00439520, &recomp_gen::fn_sub_439520_00439520__recomp},
    {"sub_439F60", 0x439F60, &recomp_gen::fn_sub_439F60_00439f60, &recomp_gen::fn_sub_439F60_00439f60__recomp},
    {"sub_43A0B0", 0x43A0B0, &recomp_gen::fn_sub_43A0B0_0043a0b0, &recomp_gen::fn_sub_43A0B0_0043a0b0__recomp},
    {"sub_43A1A0", 0x43A1A0, &recomp_gen::fn_sub_43A1A0_0043a1a0, &recomp_gen::fn_sub_43A1A0_0043a1a0__recomp},
    {"sub_43A230", 0x43A230, &recomp_gen::fn_sub_43A230_0043a230, &recomp_gen::fn_sub_43A230_0043a230__recomp},
    {"sub_43A2F0", 0x43A2F0, &recomp_gen::fn_sub_43A2F0_0043a2f0, &recomp_gen::fn_sub_43A2F0_0043a2f0__recomp},
    {"sub_43A960", 0x43A960, &recomp_gen::fn_sub_43A960_0043a960, &recomp_gen::fn_sub_43A960_0043a960__recomp},
    {"sub_43A9D0", 0x43A9D0, &recomp_gen::fn_sub_43A9D0_0043a9d0, &recomp_gen::fn_sub_43A9D0_0043a9d0__recomp},
    {"sub_43B980", 0x43B980, &recomp_gen::fn_sub_43B980_0043b980, &recomp_gen::fn_sub_43B980_0043b980__recomp},
    {"sub_43BC20", 0x43BC20, &recomp_gen::fn_sub_43BC20_0043bc20, &recomp_gen::fn_sub_43BC20_0043bc20__recomp},
    {"sub_43BDA0", 0x43BDA0, &recomp_gen::fn_sub_43BDA0_0043bda0, &recomp_gen::fn_sub_43BDA0_0043bda0__recomp},
    {"sub_43BF50", 0x43BF50, &recomp_gen::fn_sub_43BF50_0043bf50, &recomp_gen::fn_sub_43BF50_0043bf50__recomp},
    {"sub_43C180", 0x43C180, &recomp_gen::fn_sub_43C180_0043c180, &recomp_gen::fn_sub_43C180_0043c180__recomp},
    {"sub_43C340", 0x43C340, &recomp_gen::fn_sub_43C340_0043c340, &recomp_gen::fn_sub_43C340_0043c340__recomp},
    {"Y_Npc_UpdateTreasureFreeTask", 0x43C500, &recomp_gen::fn_Y_Npc_UpdateTreasureFreeTask_0043c500, &recomp_gen::fn_Y_Npc_UpdateTreasureFreeTask_0043c500__recomp},
    {"sub_43C660", 0x43C660, &recomp_gen::fn_sub_43C660_0043c660, &recomp_gen::fn_sub_43C660_0043c660__recomp},
    {"Y_Npc_CreateTreasureFreeTask", 0x43C690, &recomp_gen::fn_Y_Npc_CreateTreasureFreeTask_0043c690, &recomp_gen::fn_Y_Npc_CreateTreasureFreeTask_0043c690__recomp},
    {"sub_43C730", 0x43C730, &recomp_gen::fn_sub_43C730_0043c730, &recomp_gen::fn_sub_43C730_0043c730__recomp},
    {"sub_43C7A0", 0x43C7A0, &recomp_gen::fn_sub_43C7A0_0043c7a0, &recomp_gen::fn_sub_43C7A0_0043c7a0__recomp},
    {"sub_43C7F0", 0x43C7F0, &recomp_gen::fn_sub_43C7F0_0043c7f0, &recomp_gen::fn_sub_43C7F0_0043c7f0__recomp},
    {"sub_43C910", 0x43C910, &recomp_gen::fn_sub_43C910_0043c910, &recomp_gen::fn_sub_43C910_0043c910__recomp},
    {"Y_StParts_UpdateStratumPartsTask", 0x43CA30, &recomp_gen::fn_Y_StParts_UpdateStratumPartsTask_0043ca30, &recomp_gen::fn_Y_StParts_UpdateStratumPartsTask_0043ca30__recomp},
    {"sub_447AD0", 0x447AD0, &recomp_gen::fn_sub_447AD0_00447ad0, &recomp_gen::fn_sub_447AD0_00447ad0__recomp},
    {"Y_Stratum_CreateStratumPartsTask", 0x447E70, &recomp_gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70, &recomp_gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70__recomp},
    {"sub_449ED0", 0x449ED0, &recomp_gen::fn_sub_449ED0_00449ed0, &recomp_gen::fn_sub_449ED0_00449ed0__recomp},
    {"sub_449FA0", 0x449FA0, &recomp_gen::fn_sub_449FA0_00449fa0, &recomp_gen::fn_sub_449FA0_00449fa0__recomp},
    {"sub_44A990", 0x44A990, &recomp_gen::fn_sub_44A990_0044a990, &recomp_gen::fn_sub_44A990_0044a990__recomp},
    {"sub_44ACF0", 0x44ACF0, &recomp_gen::fn_sub_44ACF0_0044acf0, &recomp_gen::fn_sub_44ACF0_0044acf0__recomp},
    {"Y_Stratum_CreateEneThinkTask", 0x44AD20, &recomp_gen::fn_Y_Stratum_CreateEneThinkTask_0044ad20, &recomp_gen::fn_Y_Stratum_CreateEneThinkTask_0044ad20__recomp},
    {"sub_454290", 0x454290, &recomp_gen::fn_sub_454290_00454290, &recomp_gen::fn_sub_454290_00454290__recomp},
    {"Y_Stratum_CreateEneDeadEffectTask", 0x4542C0, &recomp_gen::fn_Y_Stratum_CreateEneDeadEffectTask_004542c0, &recomp_gen::fn_Y_Stratum_CreateEneDeadEffectTask_004542c0__recomp},
    {"sub_455E00", 0x455E00, &recomp_gen::fn_sub_455E00_00455e00, &recomp_gen::fn_sub_455E00_00455e00__recomp},
    {"sub_456050", 0x456050, &recomp_gen::fn_sub_456050_00456050, &recomp_gen::fn_sub_456050_00456050__recomp},
    {"Y_Stratum_CreateSmapSymbolDirpTask", 0x4560D0, &recomp_gen::fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0, &recomp_gen::fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0__recomp},
    {"Y_Kyoto_UpdateKyotoNpcModeReadTask", 0x4575E0, &recomp_gen::fn_Y_Kyoto_UpdateKyotoNpcModeReadTask_004575e0, &recomp_gen::fn_Y_Kyoto_UpdateKyotoNpcModeReadTask_004575e0__recomp},
    {"sub_457980", 0x457980, &recomp_gen::fn_sub_457980_00457980, &recomp_gen::fn_sub_457980_00457980__recomp},
    {"Y_Kyoto_CreateKyotoNpcModeReadTask", 0x4579B0, &recomp_gen::fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0, &recomp_gen::fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0__recomp},
    {"Y_Kyoto_UpdateKyotoNpcThinkTask", 0x457A40, &recomp_gen::fn_Y_Kyoto_UpdateKyotoNpcThinkTask_00457a40, &recomp_gen::fn_Y_Kyoto_UpdateKyotoNpcThinkTask_00457a40__recomp},
    {"sub_458600", 0x458600, &recomp_gen::fn_sub_458600_00458600, &recomp_gen::fn_sub_458600_00458600__recomp},
    {"Y_Kyoto_CreateKyotoNpcThinkTask", 0x458630, &recomp_gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630, &recomp_gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630__recomp},
    {"sub_458850", 0x458850, &recomp_gen::fn_sub_458850_00458850, &recomp_gen::fn_sub_458850_00458850__recomp},
    {"sub_458870", 0x458870, &recomp_gen::fn_sub_458870_00458870, &recomp_gen::fn_sub_458870_00458870__recomp},
    {"sub_458890", 0x458890, &recomp_gen::fn_sub_458890_00458890, &recomp_gen::fn_sub_458890_00458890__recomp},
    {"sub_458920", 0x458920, &recomp_gen::fn_sub_458920_00458920, &recomp_gen::fn_sub_458920_00458920__recomp},
    {"sub_458930", 0x458930, &recomp_gen::fn_sub_458930_00458930, &recomp_gen::fn_sub_458930_00458930__recomp},
    {"sub_4589D0", 0x4589D0, &recomp_gen::fn_sub_4589D0_004589d0, &recomp_gen::fn_sub_4589D0_004589d0__recomp},
    {"sub_4589E0", 0x4589E0, &recomp_gen::fn_sub_4589E0_004589e0, &recomp_gen::fn_sub_4589E0_004589e0__recomp},
    {"sub_458A80", 0x458A80, &recomp_gen::fn_sub_458A80_00458a80, &recomp_gen::fn_sub_458A80_00458a80__recomp},
    {"sub_458B00", 0x458B00, &recomp_gen::fn_sub_458B00_00458b00, &recomp_gen::fn_sub_458B00_00458b00__recomp},
    {"sub_458B60", 0x458B60, &recomp_gen::fn_sub_458B60_00458b60, &recomp_gen::fn_sub_458B60_00458b60__recomp},
    {"sub_458BB0", 0x458BB0, &recomp_gen::fn_sub_458BB0_00458bb0, &recomp_gen::fn_sub_458BB0_00458bb0__recomp},
    {"sub_458CB0", 0x458CB0, &recomp_gen::fn_sub_458CB0_00458cb0, &recomp_gen::fn_sub_458CB0_00458cb0__recomp},
    {"sub_459790", 0x459790, &recomp_gen::fn_sub_459790_00459790, &recomp_gen::fn_sub_459790_00459790__recomp},
    {"sub_459D60", 0x459D60, &recomp_gen::fn_sub_459D60_00459d60, &recomp_gen::fn_sub_459D60_00459d60__recomp},
    {"sub_459E00", 0x459E00, &recomp_gen::fn_sub_459E00_00459e00, &recomp_gen::fn_sub_459E00_00459e00__recomp},
    {"Y_Kyoto_UpdateWaitTask", 0x459E80, &recomp_gen::fn_Y_Kyoto_UpdateWaitTask_00459e80, &recomp_gen::fn_Y_Kyoto_UpdateWaitTask_00459e80__recomp},
    {"sub_459F30", 0x459F30, &recomp_gen::fn_sub_459F30_00459f30, &recomp_gen::fn_sub_459F30_00459f30__recomp},
    {"Y_Kyoto_CreateWaitTask", 0x459F60, &recomp_gen::fn_Y_Kyoto_CreateWaitTask_00459f60, &recomp_gen::fn_Y_Kyoto_CreateWaitTask_00459f60__recomp},
    {"sub_45A220", 0x45A220, &recomp_gen::fn_sub_45A220_0045a220, &recomp_gen::fn_sub_45A220_0045a220__recomp},
    {"Y_TimeLimit_CreateTimeLimitDrawTask", 0x45A280, &recomp_gen::fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280, &recomp_gen::fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 16;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that set chosen FPRs after the random register file
// and give each body its own stand-in world (stand_ins.h: the heap behind H_Malloc and the RW slots, printf / sprintf,
// the H_Cdvd layer over extracted/, plus recorders for the field callees this test library does not emit). The two
// worlds' call logs must match. With `persist` the two worlds live on across pairs (a create followed by updates).
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

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = false;
    bool persist = false;
    WorldSetup setup;
};

hgp::Run t2_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    if (!o.persist) {
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    g_t.persist = o.persist;
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    ++g_pairs;
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
s16 r16(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }

// The field callees no test library emits, served by recorders so the pairs run past them: the mover's walk target
// sub_1AFA20 (returns `arrived`), sub_1B00C0, the nearest shadow sub_1C6720 / chest sub_1C7270 (return `shadow` /
// `chest`), the persona animation lookups sub_1DED40 / sub_1DDE00, the SP payment sub_17B860, the battle task creator
// K_Battle_CreateBattleTask and sub_1D8E60.
struct FieldWorld {
    u64 arrived = 0, shadow = 0, chest = 0;
};
WorldSetup field_world(FieldWorld f) {
    return [f](StandInWorld& w) {
        w.si.install_recorder(0x1AFA20u, "sub_1AFA20", f.arrived);
        w.si.install_recorder(0x1B00C0u, "sub_1B00C0", 0);
        w.si.install_recorder(0x1C6720u, "sub_1C6720", f.shadow);
        w.si.install_recorder(0x1C7270u, "sub_1C7270", f.chest);
        w.si.install_recorder(0x1DED40u, "sub_1DED40", 0);
        w.si.install_recorder(0x1DDE00u, "sub_1DDE00", 0);
        w.si.install_recorder(0x17B860u, "sub_17B860", 0);
        w.si.install_recorder(0x1D8B00u, "K_Battle_CreateBattleTask", 0);
        w.si.install_recorder(0x1D8E60u, "sub_1D8E60", 0);
    };
}

// --- the replay snapshots ---------------------------------------------------------------------------------------------
// Live Tartarus state: the full-climb snapshots climb_ref_17000 / climb_ref_39820 and the battle route's b_6700 (one
// or two "npc think proc" tasks in follow mode, the "y_smap draw proc" task in state 14 = the random-floor map, the
// "smap_symbol_dirp" task, four "ene think proc" tasks), on a random floor whose 16 x 16 grid is at sField + 72.
constexpr const char* kSnaps[] = {"climb_ref_17000", "climb_ref_39820", "b_6700"};
constexpr u32 kField = 0x869F60u;  // sField: K_Field_Get()'s result
constexpr u32 kGrid = kField + 72;
constexpr u32 kTactic = 0x7CE6BCu;  // s8: the party tactic (tartarus2.h)
constexpr u32 kPcUnits = 0x8717A0u, kUnitSize = 448;
constexpr u32 kOut = 0x01F40000u;  // free in every snapshot (stand_ins.h) and in the ELF image

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

// The kwln tasks (0x68-byte records) whose update callback (+0x34) is `update`: a scan for records with a printable
// name whose byte sum matches +0x18 and a work pointer (+0x3C) in RAM.
std::vector<u32> tasks_with_update(const Machine& m, u32 update) {
    std::vector<u32> out;
    const u8* ram = m.mem.main_ram();
    for (u32 va = 0x100000u; va + 0x68 < EEMemory::kMainRamSize; va += 4) {
        if (r32(m, va + 0x34) != update) continue;
        const u32 work = r32(m, va + 0x3C);
        if (work == 0 || work >= EEMemory::kMainRamSize) continue;
        s32 sum = 0;
        int n = 0;
        while (n < 24 && ram[va + n] >= 0x20 && ram[va + n] < 0x7F) sum += static_cast<s8>(ram[va + n++]);
        if (n < 3 || ram[va + n] != 0 || static_cast<s32>(r32(m, va + 0x18)) != sum) continue;
        out.push_back(va);
    }
    return out;
}

std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}

// The host's model of the party path search: cells (x, z) joined through their open sides (grid cell +11: 1 -> z - 1,
// 2 -> x - 1, 8 -> x + 1, 4 -> z + 1), breadth first. sub_4359F0 reports a path iff the goal is reachable.
bool host_reachable(const Machine& m, int sx0, int sz0, int gx, int gz) {
    std::vector<int> seen(256, 0), q;
    q.push_back(sz0 * 16 + sx0);
    seen[sz0 * 16 + sx0] = 1;
    for (std::size_t i = 0; i < q.size(); ++i) {
        const int x = q[i] % 16, z = q[i] / 16;
        if (x == gx && z == gz) return true;
        const u8 sides = r8(m, kGrid + 256 * z + 16 * x + 11);
        const int nx[4] = {x, x - 1, x + 1, x}, nz[4] = {z - 1, z, z, z + 1}, bit[4] = {1, 2, 8, 4};
        for (int k = 0; k < 4; ++k) {
            if (!(sides & bit[k]) || nx[k] < 0 || nx[k] > 15 || nz[k] < 0 || nz[k] > 15) continue;
            const int c = nz[k] * 16 + nx[k];
            if (!seen[c]) seen[c] = 1, q.push_back(c);
        }
    }
    return false;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton, fewer seeds: the tests below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(tartarus2): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int stops_total = 0, pairs_total = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops_total += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs_total;
        }
    }
    MESSAGE("random worlds: " << pairs_total << " pairs, " << stops_total << " stopped early");
}

// =====================================================================================================================
// The party think on the snapshots' live "npc think proc" tasks: every mode and sub-state, the three tactics, the
// pending flags; and the mode functions directly
// =====================================================================================================================
TEST_CASE("game(tartarus2): the party think on the snapshots' live tasks") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    int tasks_seen = 0, stopped = 0;
    u32 seed = 100;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) {
            MESSAGE("SKIP: extracted/_ours/" << dir << " not found");
            continue;
        }
        const std::vector<u32> tasks = tasks_with_update(m, 0x4312B0u);
        for (const u32 task : tasks) {
            ++tasks_seen;
            const u32 work = r32(m, task + tart2::kTaskWork);
            struct Var {
                const char* fn;
                u32 off;    // the sub-state byte
                u32 count;  // its values
                s8 mode;
            };
            const Var vars[] = {{"sub_435C00", tart2::kNpcFollowState, 16, 1},
                                {"sub_438010", tart2::kNpcExploreState, 9, 2},
                                {"sub_439520", tart2::kNpcFightState, 7, 5}};
            for (const Var& v : vars)
                for (u32 st = 0; st < v.count; ++st)
                    for (u8 tactic = 0; tactic < 3; ++tactic)
                        for (const FieldWorld fw : {FieldWorld{0, 0, 0}, FieldWorld{1, sx(kPcUnits + kUnitSize), 0}}) {
                            restore(m, dir);
                            w8(m, work + tart2::kNpcMode, static_cast<u8>(v.mode));
                            w8(m, work + v.off, static_cast<u8>(st));
                            w8(m, kTactic, tactic);
                            const Opt o{{}, {}, true, false, field_world(fw)};
                            stopped += t2_pair(m, "Y_Npc_UpdateNpcThinkTask", {sx(task), 0, 0, 0}, ++seed, "think update", o).stopped;
                            restore(m, dir);
                            w8(m, work + tart2::kNpcMode, static_cast<u8>(v.mode));
                            w8(m, work + v.off, static_cast<u8>(st));
                            w8(m, kTactic, tactic);
                            stopped += t2_pair(m, v.fn, {sx(task), 0, 0, 0}, ++seed, v.fn, o).stopped;
                        }
            // modes 0 and 6, the held member, and each pending action (mode-change script, skill use, support walk)
            for (const u8 mode : {u8{0}, u8{6}})
                for (u8 tactic = 0; tactic < 3; ++tactic) {
                    restore(m, dir);
                    w8(m, work + tart2::kNpcMode, mode);
                    w8(m, kTactic, tactic);
                    stopped += t2_pair(m, "Y_Npc_UpdateNpcThinkTask", {sx(task), 0, 0, 0}, ++seed, "think mode 0 / 6",
                                       Opt{{}, {}, true, false, field_world({})}).stopped;
                }
            struct Flag {
                u32 off, sub;
                const char* fn;
            };
            for (const Flag f : {Flag{tart2::kNpcHeld, 0, nullptr}, Flag{tart2::kNpcModeChange, tart2::kNpcModeScriptState, "sub_43A2F0"},
                                 Flag{tart2::kNpcSkillUse, tart2::kNpcSkillState, "sub_43A960"},
                                 Flag{tart2::kNpcSupport, tart2::kNpcSupportState, "sub_43BF50"}})
                for (u8 sub = 0; sub < 3; ++sub)
                    for (u8 order = 0; order < (f.off == tart2::kNpcModeChange ? 8 : 1); ++order) {
                        restore(m, dir);
                        w8(m, work + f.off, 1);
                        if (f.sub) w8(m, work + f.sub, sub);
                        w8(m, work + tart2::kNpcModeOrder, order);
                        const Opt o{{}, {}, true, false, field_world({})};
                        stopped += t2_pair(m, "Y_Npc_UpdateNpcThinkTask", {sx(task), 0, 0, 0}, ++seed, "think flags", o).stopped;
                        if (f.fn) {
                            restore(m, dir);
                            w8(m, work + f.off, 1);
                            if (f.sub) w8(m, work + f.sub, sub);
                            w8(m, work + tart2::kNpcModeOrder, order);
                            stopped += t2_pair(m, f.fn, {sx(task), 0, 0, 0}, ++seed, f.fn, o).stopped;
                        }
                    }
            // the destroy callback on a copy of the live state
            restore(m, dir);
            t2_pair(m, "sub_431630", {sx(task), 0, 0, 0}, ++seed, "think destroy", Opt{{}, {}, true});
        }
    }
    MESSAGE("party think: " << tasks_seen << " live tasks, " << g_pairs << " pairs so far, " << stopped << " stopped early");
}

// =====================================================================================================================
// The party helpers by member index on the snapshots, with documented rules on their results
// =====================================================================================================================
TEST_CASE("game(tartarus2): the party helpers by member index (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 3000;
    int rules = 0;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) continue;
        const Opt si{{}, {}, true, false, field_world({1, 0, 0})};
        for (u32 pc = 0; pc < 8; ++pc) {
            for (const char* fn : {"sub_43C7F0", "sub_43C910", "sub_435260", "sub_435440", "sub_435660", "sub_43BC20", "sub_43C180",
                                   "sub_43C340", "sub_43A230", "sub_439400", "sub_437E20", "sub_434C90", "sub_43C730", "sub_437E00"}) {
                if (pc > 3 && std::string(fn) != "sub_43C7F0" && std::string(fn) != "sub_43C910") continue;
                restore(m, dir);
                t2_pair(m, fn, {pc, 0, 0, 0}, ++seed, fn, si);
            }
            for (u32 b = 0; b < 4 && pc < 4; ++b) {
                for (const char* fn : {"sub_43B980", "sub_43BDA0", "sub_43A1A0", "sub_4350E0"}) {
                    restore(m, dir);
                    t2_pair(m, fn, {pc, b, 0, 0}, ++seed, fn, si);
                }
                for (u32 flag = 0; flag < 2; ++flag) {
                    restore(m, dir);
                    t2_pair(m, "sub_43A9D0", {pc, b, flag, 0}, ++seed, "sub_43A9D0", si);
                }
                restore(m, dir);
                t2_pair(m, "sub_439F60", {0, pc, 0, 0}, ++seed, "sub_439F60", si);
                restore(m, dir);
                t2_pair(m, "sub_43A0B0", {0, pc, 0, 0}, ++seed, "sub_43A0B0", si);
                restore(m, dir);
                t2_pair(m, "sub_437E80", {sx(kOut), pc, 0, 0}, ++seed, "sub_437E80", si);
            }
        }
        for (u32 v = 0; v < 2; ++v)
            for (const char* fn : {"sub_435370", "sub_435060", "sub_434F60"}) {
                restore(m, dir);
                t2_pair(m, fn, {v, 0, 0, 0}, ++seed, fn, si);
            }
        for (const char* fn : {"sub_4352E0", "sub_434D30", "sub_434E60", "sub_435810"}) {
            restore(m, dir);
            t2_pair(m, fn, {0, 0, 0, 0}, ++seed, fn, si);
        }
        for (u32 i = 0; i < 4; ++i) {  // sub_4353F0 on the party units
            restore(m, dir);
            t2_pair(m, "sub_4353F0", {sx(kPcUnits + i * kUnitSize), 0, 0, 0}, ++seed, "sub_4353F0", si);
        }
        // rules on the live members
        for (u32 pc = 1; pc < 4; ++pc) {
            const u32 task = r32(m, kPcUnits + pc * kUnitSize + tart2::kUnitThinkTask);
            if (task == 0 || r32(m, kPcUnits + pc * kUnitSize + tart2::kUnitUsed) == 0) continue;
            const u32 work = r32(m, task + tart2::kTaskWork);
            for (u8 mode = 0; mode < 7; ++mode) {  // sub_43C7A0 sets the mode and clears the five sub-state bytes
                restore(m, dir);
                for (u32 off : {tart2::kNpcFollowState, tart2::kNpcByte4644, tart2::kNpcExploreState, tart2::kNpcByte4641, tart2::kNpcFightState})
                    w8(m, work + off, 9);
                const hgp::Run r = t2_pair(m, "sub_43C7A0", {pc, mode, 0, 0}, ++seed, "sub_43C7A0", si);
                if (r.stopped) continue;
                CHECK(r8(m, work + tart2::kNpcMode) == mode);
                for (u32 off : {tart2::kNpcFollowState, tart2::kNpcByte4644, tart2::kNpcExploreState, tart2::kNpcByte4641, tart2::kNpcFightState})
                    CHECK(r8(m, work + off) == 0);
                ++rules;
            }
            for (u8 st = 0; st < 16; ++st) {  // sub_437E20: 1 outside the column states 7..12
                restore(m, dir);
                w8(m, work + tart2::kNpcFollowState, st);
                const hgp::Run r = t2_pair(m, "sub_437E20", {pc, 0, 0, 0}, ++seed, "sub_437E20", si);
                if (r.stopped) continue;
                CHECK((v0_of(r) & 0xFF) == ((st < 7 || st >= 13) ? 1u : 0u));
                ++rules;
            }
            for (u8 held = 0; held < 2; ++held) {  // sub_435260: the member's kNpcHeld; sub_4352E0: any held
                restore(m, dir);
                w8(m, work + tart2::kNpcHeld, held);
                const hgp::Run r = t2_pair(m, "sub_435260", {pc, 0, 0, 0}, ++seed, "sub_435260", si);
                if (!r.stopped) {
                    CHECK(static_cast<s64>(v0_of(r)) == held);
                    ++rules;
                }
                const hgp::Run a = t2_pair(m, "sub_4352E0", {0, 0, 0, 0}, ++seed, "sub_4352E0", si);
                if (!a.stopped && held) {
                    CHECK(v0_of(a) == 1);
                    ++rules;
                }
            }
        }
    }
    MESSAGE("party helpers: " << rules << " documented-rule checks");
}

// =====================================================================================================================
// Exploring and the path search on the snapshots' real 16 x 16 grids
// =====================================================================================================================
TEST_CASE("game(tartarus2): exploring and the path search on the real grids (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 6000;
    int found = 0, rules = 0;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) continue;
        const std::vector<u32> tasks = tasks_with_update(m, 0x4312B0u);
        if (tasks.empty()) continue;
        const u32 task = tasks[0];
        const u32 work = r32(m, task + tart2::kTaskWork);
        std::vector<std::pair<int, int>> rooms;
        for (int z = 0; z < 16; ++z)
            for (int x = 0; x < 16; ++x)
                if (r8(m, kGrid + 256 * z + 16 * x + 11) != 0 && (x || z)) rooms.emplace_back(x, z);
        const Opt si{{}, {}, true, false, field_world({1, 0, 0})};
        // sub_433810: the 2 x 2 block origin of every cell; 0 for a cell whose +7 is not 2
        for (int z = 0; z < 16; ++z)
            for (int x = 0; x < 16; ++x) {
                restore(m, dir);
                const hgp::Run r = t2_pair(m, "sub_433810", {static_cast<u64>(x), static_cast<u64>(z), 0, 0}, ++seed, "sub_433810", si);
                if (!r.stopped && r8(m, kGrid + 256 * z + 16 * x + 7) != 2) {
                    CHECK(v0_of(r) == 0);
                    ++rules;
                }
            }
        // the path search between pairs of open cells: a path iff the host's breadth-first search reaches the goal
        std::mt19937 rng{seed};
        for (int k = 0; k < 48 && rooms.size() > 1; ++k) {
            const auto [x0, z0] = rooms[rng() % rooms.size()];
            const auto [gx, gz] = rooms[rng() % rooms.size()];
            if (x0 == gx && z0 == gz) continue;
            restore(m, dir);
            const float pos[3] = {800.0f * x0, 0.0f, 800.0f * z0};
            std::memcpy(m.at(kOut), pos, sizeof pos);
            Opt o = si;
            o.gpr_in = {{GPR_T0, static_cast<u64>(gx)}, {GPR_T0 + 1, static_cast<u64>(gz)}};
            const hgp::Run r = t2_pair(m, "sub_4359F0", {sx(task), static_cast<u64>(x0), static_cast<u64>(z0), sx(kOut)}, ++seed, "sub_4359F0", o);
            if (r.stopped) continue;
            const bool reach = host_reachable(m, x0, z0, gx, gz);
            CHECK((v0_of(r) & 0xFF) == (reach ? 1u : 0u));
            found += reach;
            ++rules;
            if (reach) {  // the step list starts at the goal (sub_4343D0 walks back from it)
                CHECK(r16(m, work + tart2::kNpcSteps) == gx);
                CHECK(r16(m, work + tart2::kNpcSteps + 2) == gz);
            }
        }
        // the wall-following rules, the unvisited / least-visited side, the visit count, the rule flips, the block marks:
        // the member placed on open cells with every facing
        std::shuffle(rooms.begin(), rooms.end(), rng);  // a sample of 24 open cells: every facing and helper on each
        if (rooms.size() > 24) rooms.resize(24);
        for (const auto& [x, z] : rooms) {
            for (u8 facing = 0; facing <= 4; ++facing) {
                for (const char* fn : {"sub_431AA0", "sub_432050", "sub_432600", "sub_432BB0"}) {
                    restore(m, dir);
                    w8(m, work + tart2::kNpcCellX, static_cast<u8>(x));
                    w8(m, work + tart2::kNpcCellZ, static_cast<u8>(z));
                    w8(m, work + tart2::kNpcWalkX, static_cast<u8>(x));
                    w8(m, work + tart2::kNpcWalkZ, static_cast<u8>(z));
                    w8(m, work + tart2::kNpcFacing, facing);
                    t2_pair(m, fn, {sx(task), 0, 0, 0}, ++seed, fn, si);
                }
            }
            for (const char* fn : {"sub_433160", "sub_4339D0", "sub_431880", "sub_4332F0", "sub_4333D0", "sub_4334D0"}) {
                restore(m, dir);
                w8(m, work + tart2::kNpcCellX, static_cast<u8>(x));
                w8(m, work + tart2::kNpcCellZ, static_cast<u8>(z));
                w8(m, work + tart2::kNpcWalkX, static_cast<u8>((x + 1) & 15));
                w8(m, work + tart2::kNpcWalkZ, static_cast<u8>(z));
                const float pos[3] = {800.0f * x, 0.0f, 800.0f * z};
                std::memcpy(m.at(work + tart2::kNpcCellPosX), pos, sizeof pos);
                for (int i = 0; i < 256; ++i) w8(m, work + tart2::kNpcVisits + i, static_cast<u8>(rng() % 4));
                w32(m, work + tart2::kNpcCount, rng() % 10);
                t2_pair(m, fn, {sx(task), 0, 0, 0}, ++seed, fn, si);
            }
        }
    }
    MESSAGE("grids: " << rules << " documented-rule checks, " << found << " reachable goals");
}

// =====================================================================================================================
// Task creators, destroy callbacks and the Kyoto / time-limit / stratum tasks (heap and file stand-ins)
// =====================================================================================================================
TEST_CASE("game(tartarus2): task creators and their updates (stand-ins)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    if (!restore(m, kSnaps[0]) && !restore(m, kSnaps[2])) {
        MESSAGE("SKIP: no Tartarus snapshot under extracted/_ours");
        return;
    }
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    u32 seed = 9000;
    int rules = 0;
    const Opt si{{}, {}, true, false, field_world({})};
    Opt keep = si;
    keep.persist = true;
    // the time limit: the four digits of mm:ss
    for (u32 secs : {0u, 59u, 60u, 125u, 599u, 3599u, 5999u}) {
        reset();
        const hgp::Run r = t2_pair(m, "Y_TimeLimit_CreateTimeLimitDrawTask", {0, secs, 0, 0}, ++seed, "time limit", si);
        if (r.stopped || v0_of(r) == 0) continue;
        const u32 work = r32(m, static_cast<u32>(v0_of(r)) + tart2::kTaskWork);
        CHECK(r32(m, work + tart2::kTlSeconds) == secs);
        CHECK(r8(m, work + tart2::kTlMinTens) == (secs / 60) / 10);
        CHECK(r8(m, work + tart2::kTlMinOnes) == (secs / 60) % 10);
        CHECK(r8(m, work + tart2::kTlSecTens) == (secs % 60) / 10);
        CHECK(r8(m, work + tart2::kTlSecOnes) == (secs % 60) % 10);
        ++rules;
        t2_pair(m, "sub_45A220", {v0_of(r), 0, 0, 0}, ++seed, "time limit destroy", si);
    }
    // the stratum record's defaults (sub_449ED0), freed again by sub_449FA0
    reset();
    if (const hgp::Run r = t2_pair(m, "sub_449ED0", {0, 0, 0, 0}, ++seed, "stratum record", si); !r.stopped) {
        const u32 rec = r32(m, 0x7CE6ECu);
        CHECK(rec != 0);
        if (rec) {
            CHECK(r16(m, rec + tart2::kStRecFloor) == 1);
            CHECK(r8(m, rec + tart2::kStRecBlock) == 1);
            CHECK(r8(m, rec + tart2::kStRecBlocksOpen) == 1);
            for (u32 b = 0; b < 6; ++b) CHECK(r8(m, rec + tart2::kStRecBlockStates + b) == 2);
            ++rules;
        }
        t2_pair(m, "sub_449FA0", {0, 0, 0, 0}, ++seed, "stratum record free", si);
    }
    // the stratum-parts task: create (both forms), then every state of the update from the fresh work, and the destroy
    for (u32 mode = 0; mode < 2; ++mode)
        for (u32 from_map = 0; from_map < 2; ++from_map) {
            reset();
            const hgp::Run c = t2_pair(m, "Y_Stratum_CreateStratumPartsTask", {0, mode, from_map, 0}, ++seed, "stratum create", keep);
            if (c.stopped || v0_of(c) == 0) continue;
            const u32 task = static_cast<u32>(v0_of(c));
            const u32 work = r32(m, task + tart2::kTaskWork);
            CHECK(r8(m, work + tart2::kSpMode) == mode);
            CHECK(r8(m, work + tart2::kSpFromMap) == from_map);
            ++rules;
            const std::vector<u8> made(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
            for (u32 state = 0; state <= 50; ++state) {
                std::memcpy(m.mem.main_ram(), made.data(), made.size());
                w8(m, work + tart2::kSpState, static_cast<u8>(state));
                t2_pair(m, "Y_StParts_UpdateStratumPartsTask", {sx(task), 0, 0, 0}, ++seed, "stratum update", keep);
            }
            std::memcpy(m.mem.main_ram(), made.data(), made.size());
            t2_pair(m, "sub_447AD0", {sx(task), 0, 0, 0}, ++seed, "stratum destroy", keep);
        }
    // the stratum update's loading chain run as the game runs it: state after state on the same work
    reset();
    if (const hgp::Run c = t2_pair(m, "Y_Stratum_CreateStratumPartsTask", {0, 1, 0, 0}, ++seed, "stratum create", keep); !c.stopped && v0_of(c)) {
        const u32 task = static_cast<u32>(v0_of(c));
        for (int frame = 0; frame < 40; ++frame) {
            const hgp::Run r = t2_pair(m, "Y_StParts_UpdateStratumPartsTask", {sx(task), 0, 0, 0}, ++seed, "stratum frames", keep);
            if (r.stopped) break;
        }
    }
    // the Kyoto NPCs: the mode-read task through its states, the think task and its helpers, the wait task
    reset();
    if (const hgp::Run c = t2_pair(m, "Y_Kyoto_CreateKyotoNpcModeReadTask", {0, 0, 0, 0}, ++seed, "kyoto read create", keep); !c.stopped && v0_of(c)) {
        const u32 task = static_cast<u32>(v0_of(c));
        const u32 work = r32(m, task + tart2::kTaskWork);
        const std::vector<u8> made(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (u32 state = 0; state <= 10; ++state) {
            std::memcpy(m.mem.main_ram(), made.data(), made.size());
            w8(m, work, static_cast<u8>(state));
            t2_pair(m, "Y_Kyoto_UpdateKyotoNpcModeReadTask", {sx(task), 0, 0, 0}, ++seed, "kyoto read", keep);
        }
        std::memcpy(m.mem.main_ram(), made.data(), made.size());
        t2_pair(m, "sub_457980", {sx(task), 0, 0, 0}, ++seed, "kyoto read destroy", keep);
    }
    for (u32 npc = 0; npc < 4; ++npc) {
        reset();
        const hgp::Run c = t2_pair(m, "Y_Kyoto_CreateKyotoNpcThinkTask", {0, npc, npc % 3, 0}, ++seed, "kyoto think create", keep);
        if (c.stopped || v0_of(c) == 0) continue;
        const u32 task = static_cast<u32>(v0_of(c));
        const u32 work = r32(m, task + tart2::kTaskWork);
        CHECK(r8(m, work + tart2::kKyotoIndex) == npc);
        CHECK(r8(m, work + tart2::kKyotoRoute) == npc % 3);
        ++rules;
        const std::vector<u8> made(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (u32 st = 0; st < 6; ++st)
            for (u32 caught = 0; caught < 10; ++caught) {
                std::memcpy(m.mem.main_ram(), made.data(), made.size());
                w8(m, work + tart2::kKyotoState, static_cast<u8>(st));
                w8(m, work + tart2::kKyotoCatch, static_cast<u8>(caught));
                t2_pair(m, "Y_Kyoto_UpdateKyotoNpcThinkTask", {sx(task), 0, 0, 0}, ++seed, "kyoto think", keep);
            }
        for (const char* fn : {"sub_458850", "sub_458870", "sub_458920"}) {
            std::memcpy(m.mem.main_ram(), made.data(), made.size());
            t2_pair(m, fn, {sx(task), 0, 0, 0}, ++seed, fn, keep);
        }
        for (u32 v = 0; v < 2; ++v) {
            std::memcpy(m.mem.main_ram(), made.data(), made.size());
            t2_pair(m, "sub_4589D0", {sx(task), v, 0, 0}, ++seed, "sub_4589D0", keep);
            CHECK(r8(m, work + tart2::kKyotoPaused) == v);
            ++rules;
        }
        std::memcpy(m.mem.main_ram(), made.data(), made.size());
        t2_pair(m, "sub_458600", {sx(task), 0, 0, 0}, ++seed, "kyoto think destroy", keep);
    }
    // the waypoint pause table: sub_458A80(npc, w) == 1 iff w is in npc's row of 0x7BC610 (10 words, -1 ended)
    reset();
    for (u32 npc = 0; npc < 4; ++npc)
        for (u32 wp = 0; wp < 36; ++wp) {
            const hgp::Run r = t2_pair(m, "sub_458A80", {npc, wp, 0, 0}, ++seed, "sub_458A80", si);
            bool in = false;
            for (u32 i = 0; i < 10; ++i) {
                const s32 v = static_cast<s32>(r32(m, 0x7BC610u + 40 * npc + 4 * i));
                if (v == -1) break;
                in = in || v == static_cast<s32>(wp);
            }
            if (!r.stopped) {
                    CHECK((v0_of(r) & 1) == (in ? 1u : 0u));
                    ++rules;
                }
        }
    // the Kyoto helpers over the four NPC units (no Kyoto field in the snapshots: on the units as they are)
    for (const char* fn : {"sub_458890", "sub_458930", "sub_4589E0", "sub_458B00", "sub_458B60", "sub_458BB0", "sub_459D60"}) {
        reset();
        t2_pair(m, fn, {0, 0, 0, 0}, ++seed, fn, si);
    }
    for (u32 npc = 0; npc < 4; ++npc) {
        reset();
        t2_pair(m, "sub_459E00", {npc, 0, 0, 0}, ++seed, "sub_459E00", si);
        reset();
        t2_pair(m, "sub_458CB0", {0, npc, npc % 3, 0}, ++seed, "sub_458CB0", si);
        reset();
        t2_pair(m, "sub_459790", {0, npc, npc % 3, 0}, ++seed, "sub_459790", si);
    }
    // the wait task: create, count frames, run its procedure at the end, destroy
    for (u32 proc = 0; proc < 2; ++proc) {
        reset();
        const hgp::Run c = t2_pair(m, "Y_Kyoto_CreateWaitTask", {0, 3, proc * 5, 0}, ++seed, "wait create", keep);
        if (c.stopped || v0_of(c) == 0) continue;
        const u32 task = static_cast<u32>(v0_of(c));
        for (int frame = 0; frame < 5; ++frame) {
            const hgp::Run r = t2_pair(m, "Y_Kyoto_UpdateWaitTask", {sx(task), 0, 0, 0}, ++seed, "wait update", keep);
            if (r.stopped) break;
            CHECK(static_cast<s32>(v0_of(r)) == (frame < 3 ? 0 : -1));  // 3 frames counted, then done
            ++rules;
        }
        t2_pair(m, "sub_459F30", {sx(task), 0, 0, 0}, ++seed, "wait destroy", keep);
    }
    // the enemy band's creators on the snapshot's shadows, and the treasure-free / symbol-direction / mini-map tasks
    for (u32 ec = 0; ec < 6; ++ec) {
        reset();
        const hgp::Run c = t2_pair(m, "Y_Stratum_CreateEneThinkTask", {0, ec, 0, 0}, ++seed, "ene think create", keep);
        if (!c.stopped && v0_of(c)) {
            const u32 work = r32(m, static_cast<u32>(v0_of(c)) + tart2::kTaskWork);
            CHECK(r8(m, work + tart2::kEneUnit) == ec);
            ++rules;
            t2_pair(m, "sub_44ACF0", {v0_of(c), 0, 0, 0}, ++seed, "ene think destroy", keep);
        }
        reset();
        const hgp::Run d = t2_pair(m, "Y_Stratum_CreateEneDeadEffectTask", {ec, 0, 0, 0}, ++seed, "ene dead create", keep);
        if (!d.stopped && v0_of(d)) t2_pair(m, "sub_454290", {v0_of(d), 0, 0, 0}, ++seed, "ene dead destroy", keep);
    }
    reset();
    if (const hgp::Run c = t2_pair(m, "Y_Npc_CreateTreasureFreeTask", {0x00860000u, 0, 0, 0}, ++seed, "treasure create", keep); !c.stopped && v0_of(c)) {
        const u32 task = static_cast<u32>(v0_of(c));
        const u32 work = r32(m, task + tart2::kTaskWork);
        CHECK(r32(m, work + tart2::kNpcTfChest) == 0x00860000u);
        ++rules;
        const std::vector<u8> made(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (u32 st = 0; st < 5; ++st) {
            std::memcpy(m.mem.main_ram(), made.data(), made.size());
            w8(m, work + tart2::kNpcTfState, static_cast<u8>(st));
            t2_pair(m, "Y_Npc_UpdateTreasureFreeTask", {sx(task), 0, 0, 0}, ++seed, "treasure update", keep);
        }
        std::memcpy(m.mem.main_ram(), made.data(), made.size());
        t2_pair(m, "sub_43C660", {sx(task), 0, 0, 0}, ++seed, "treasure destroy", keep);
    }
    for (u32 pc = 1; pc < 4; ++pc) {  // the party think creator: slot rules (hand by slot, facing 1, mode from the unit)
        reset();
        const hgp::Run c = t2_pair(m, "Y_Npc_CreateNpcThinkTask", {0, pc, sx(kPcUnits + pc * kUnitSize), 0}, ++seed, "think create", keep);
        if (c.stopped || v0_of(c) == 0) continue;
        const u32 work = r32(m, static_cast<u32>(v0_of(c)) + tart2::kTaskWork);
        CHECK(r32(m, work + tart2::kNpcPc) == pc);
        CHECK(r8(m, work + tart2::kNpcHand) == pc - 1);
        CHECK(r8(m, work + tart2::kNpcFacing) == 1);
        CHECK(r32(m, work + tart2::kNpcUnit) == kPcUnits + pc * kUnitSize);
        const u8 kept = r8(m, kPcUnits + pc * kUnitSize + 410);
        CHECK(r8(m, work + tart2::kNpcMode) == kept);
        ++rules;
    }
    reset();
    if (const hgp::Run c = t2_pair(m, "Y_Stratum_CreateSmapSymbolDirpTask", {0, 1, 2, 0}, ++seed, "dirp create", Opt{{}, {{12, 0x42C80000u}, {13, 0x43480000u}, {14, 0x3F800000u}}, true, true, field_world({})});
        !c.stopped && v0_of(c)) {
        const u32 task = static_cast<u32>(v0_of(c));
        const u32 work = r32(m, task + tart2::kTaskWork);
        const std::vector<u8> made(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (u32 st = 0; st < 4; ++st)
            for (u8 shown = 0; shown < 2; ++shown) {
                std::memcpy(m.mem.main_ram(), made.data(), made.size());
                w8(m, work + tart2::kEneDirpState, static_cast<u8>(st));
                w8(m, work + tart2::kEneDirpShown, shown);
                t2_pair(m, "sub_455E00", {sx(task), 0, 0, 0}, ++seed, "dirp update", keep);
            }
        std::memcpy(m.mem.main_ram(), made.data(), made.size());
        t2_pair(m, "sub_456050", {sx(task), 0, 0, 0}, ++seed, "dirp destroy", keep);
    }
    for (const char* fn : {"Y_SMap_CreateSmapDrawTask", "Y_Kyoto_CreateKyotoNpcModeReadTask"}) {
        reset();
        const hgp::Run c = t2_pair(m, fn, {0, 0, 0, 0}, ++seed, fn, keep);
        if (!c.stopped && v0_of(c) && std::string(fn) == "Y_SMap_CreateSmapDrawTask")
            t2_pair(m, "sub_429C60", {v0_of(c), 0, 0, 0}, ++seed, "smap destroy", keep);
    }
    reset();
    t2_pair(m, "sub_4302B0", {0, 0, 0, 0}, ++seed, "smap boot loads", si);  // real smap/*.tmx and the sprite through FakeCd
    MESSAGE("creators: " << rules << " documented-rule checks");
}

// =====================================================================================================================
// The mini-map task on the snapshots' live "y_smap draw proc": every state, shown and hidden
// =====================================================================================================================
TEST_CASE("game(tartarus2): the mini-map update on the snapshots' live task") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 12000;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) continue;
        for (const u32 task : tasks_with_update(m, 0x4281F0u)) {
            const u32 work = r32(m, task + tart2::kTaskWork);
            for (u32 state = 0; state <= 20; ++state)
                for (u8 shown = 0; shown < 2; ++shown) {
                    restore(m, dir);
                    w8(m, work, static_cast<u8>(state));
                    w8(m, work + tart2::kSmapWorkShown, shown);
                    t2_pair(m, "Y_SMap_UpdateSmapDrawTask", {sx(task), 0, 0, 0}, ++seed, "smap update", Opt{{}, {}, true, false, field_world({})});
                }
            for (const char* fn : {"sub_42AA40", "sub_42AC60", "Y_SMap_CreateSmapMaskDrawTask"})
                for (u32 k = 0; k < 2; ++k) {
                    restore(m, dir);
                    t2_pair(m, fn, {sx(task), k, 0, 0}, ++seed, fn, Opt{{}, {}, true, false, field_world({})});
                }
        }
    }
}

TEST_CASE("game(tartarus2): pair count") { MESSAGE("tartarus2 pairs run (outside the random-world case): " << g_pairs); }

#else

TEST_CASE("game(tartarus2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
