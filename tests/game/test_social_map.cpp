// Pair tests of the social_map slice (game/src/ui/social_map.cpp): the social-link code 0x3C03F0-0x3C442C and the area
// map 0x421770-0x4281E4. Every pair runs the hand body and its recompiled body from the same guest machine through
// tests/game/handgen_pairs.h -- the whole register file and the cycle count at every check point and at the return /
// stop, all 32 MiB of RAM (write-tracked), the scratchpad, the BIOS window, the bus log -- and, where a body allocates or
// loads files, on two identical stand-in worlds (tests/game/stand_ins.h) whose call logs must match.
//
// Inputs: the p3fes_handgen random worlds for every function; the comu tables of a replay snapshot (loaded at boot,
// the same in every snapshot) for every day of the year with documented-rule checks against a host decode of the
// tables; the timer states in every phase and the event executor in every type and phase; the task creators, the
// RevMailSeq / y_lmap updates and sequence 4 on the heap and file stand-ins; comuData.c's static tables against the
// ELF; the area map's easing curves, alignment, path matrix and record setters against their documented results.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/social_map.h"

#include <bit>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
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
void fn_sub_3C03F0_003c03f0(EEContext&);  // generated body
void fn_sub_3C03F0_003c03f0__recomp(EEContext&);  // recompiled
void fn_sub_3C0570_003c0570(EEContext&);  // generated body
void fn_sub_3C0570_003c0570__recomp(EEContext&);  // recompiled
void fn_sub_3C07C0_003c07c0(EEContext&);  // generated body
void fn_sub_3C07C0_003c07c0__recomp(EEContext&);  // recompiled
void fn_sub_3C09A0_003c09a0(EEContext&);  // generated body
void fn_sub_3C09A0_003c09a0__recomp(EEContext&);  // recompiled
void fn_sub_3C0B30_003c0b30(EEContext&);  // generated body
void fn_sub_3C0B30_003c0b30__recomp(EEContext&);  // recompiled
void fn_sub_3C0BD0_003c0bd0(EEContext&);  // generated body
void fn_sub_3C0BD0_003c0bd0__recomp(EEContext&);  // recompiled
void fn_sub_3C0C30_003c0c30(EEContext&);  // generated body
void fn_sub_3C0C30_003c0c30__recomp(EEContext&);  // recompiled
void fn_sub_3C0D20_003c0d20(EEContext&);  // generated body
void fn_sub_3C0D20_003c0d20__recomp(EEContext&);  // recompiled
void fn_sub_3C0DB0_003c0db0(EEContext&);  // generated body
void fn_sub_3C0DB0_003c0db0__recomp(EEContext&);  // recompiled
void fn_sub_3C0F20_003c0f20(EEContext&);  // generated body
void fn_sub_3C0F20_003c0f20__recomp(EEContext&);  // recompiled
void fn_sub_3C1150_003c1150(EEContext&);  // generated body
void fn_sub_3C1150_003c1150__recomp(EEContext&);  // recompiled
void fn_sub_3C1300_003c1300(EEContext&);  // generated body
void fn_sub_3C1300_003c1300__recomp(EEContext&);  // recompiled
void fn_sub_3C1340_003c1340(EEContext&);  // generated body
void fn_sub_3C1340_003c1340__recomp(EEContext&);  // recompiled
void fn_sub_3C1430_003c1430(EEContext&);  // generated body
void fn_sub_3C1430_003c1430__recomp(EEContext&);  // recompiled
void fn_sub_3C1440_003c1440(EEContext&);  // generated body
void fn_sub_3C1440_003c1440__recomp(EEContext&);  // recompiled
void fn_sub_3C15D0_003c15d0(EEContext&);  // generated body
void fn_sub_3C15D0_003c15d0__recomp(EEContext&);  // recompiled
void fn_sub_3C1810_003c1810(EEContext&);  // generated body
void fn_sub_3C1810_003c1810__recomp(EEContext&);  // recompiled
void fn_sub_3C18C0_003c18c0(EEContext&);  // generated body
void fn_sub_3C18C0_003c18c0__recomp(EEContext&);  // recompiled
void fn_sub_3C1A70_003c1a70(EEContext&);  // generated body
void fn_sub_3C1A70_003c1a70__recomp(EEContext&);  // recompiled
void fn_comu_CreateComuTimerProcessTask_003c1ab0(EEContext&);  // generated body
void fn_comu_CreateComuTimerProcessTask_003c1ab0__recomp(EEContext&);  // recompiled
void fn_comu_UpdateRevMailSeqTask_003c1d20(EEContext&);  // generated body
void fn_comu_UpdateRevMailSeqTask_003c1d20__recomp(EEContext&);  // recompiled
void fn_sub_3C22F0_003c22f0(EEContext&);  // generated body
void fn_sub_3C22F0_003c22f0__recomp(EEContext&);  // recompiled
void fn_comu_CreateRevMailSeqTask_003c2350(EEContext&);  // generated body
void fn_comu_CreateRevMailSeqTask_003c2350__recomp(EEContext&);  // recompiled
void fn_sub_3C23F0_003c23f0(EEContext&);  // generated body
void fn_sub_3C23F0_003c23f0__recomp(EEContext&);  // recompiled
void fn_sub_3C2570_003c2570(EEContext&);  // generated body
void fn_sub_3C2570_003c2570__recomp(EEContext&);  // recompiled
void fn_sub_3C2630_003c2630(EEContext&);  // generated body
void fn_sub_3C2630_003c2630__recomp(EEContext&);  // recompiled
void fn_sub_3C2770_003c2770(EEContext&);  // generated body
void fn_sub_3C2770_003c2770__recomp(EEContext&);  // recompiled
void fn_sub_3C2780_003c2780(EEContext&);  // generated body
void fn_sub_3C2780_003c2780__recomp(EEContext&);  // recompiled
void fn_sub_3C28A0_003c28a0(EEContext&);  // generated body
void fn_sub_3C28A0_003c28a0__recomp(EEContext&);  // recompiled
void fn_sub_3C2AB0_003c2ab0(EEContext&);  // generated body
void fn_sub_3C2AB0_003c2ab0__recomp(EEContext&);  // recompiled
void fn_sub_3C2B40_003c2b40(EEContext&);  // generated body
void fn_sub_3C2B40_003c2b40__recomp(EEContext&);  // recompiled
void fn_sub_3C2C50_003c2c50(EEContext&);  // generated body
void fn_sub_3C2C50_003c2c50__recomp(EEContext&);  // recompiled
void fn_sub_3C2DF0_003c2df0(EEContext&);  // generated body
void fn_sub_3C2DF0_003c2df0__recomp(EEContext&);  // recompiled
void fn_sub_3C2EE0_003c2ee0(EEContext&);  // generated body
void fn_sub_3C2EE0_003c2ee0__recomp(EEContext&);  // recompiled
void fn_sub_3C3050_003c3050(EEContext&);  // generated body
void fn_sub_3C3050_003c3050__recomp(EEContext&);  // recompiled
void fn_sub_3C30B0_003c30b0(EEContext&);  // generated body
void fn_sub_3C30B0_003c30b0__recomp(EEContext&);  // recompiled
void fn_sub_3C3120_003c3120(EEContext&);  // generated body
void fn_sub_3C3120_003c3120__recomp(EEContext&);  // recompiled
void fn_sub_3C3190_003c3190(EEContext&);  // generated body
void fn_sub_3C3190_003c3190__recomp(EEContext&);  // recompiled
void fn_sub_3C3390_003c3390(EEContext&);  // generated body
void fn_sub_3C3390_003c3390__recomp(EEContext&);  // recompiled
void fn_sub_3C33C0_003c33c0(EEContext&);  // generated body
void fn_sub_3C33C0_003c33c0__recomp(EEContext&);  // recompiled
void fn_sub_3C3E80_003c3e80(EEContext&);  // generated body
void fn_sub_3C3E80_003c3e80__recomp(EEContext&);  // recompiled
void fn_sub_3C3F40_003c3f40(EEContext&);  // generated body
void fn_sub_3C3F40_003c3f40__recomp(EEContext&);  // recompiled
void fn_sub_3C3F80_003c3f80(EEContext&);  // generated body
void fn_sub_3C3F80_003c3f80__recomp(EEContext&);  // recompiled
void fn_sub_3C3FE0_003c3fe0(EEContext&);  // generated body
void fn_sub_3C3FE0_003c3fe0__recomp(EEContext&);  // recompiled
void fn_sub_3C4040_003c4040(EEContext&);  // generated body
void fn_sub_3C4040_003c4040__recomp(EEContext&);  // recompiled
void fn_sub_3C40F0_003c40f0(EEContext&);  // generated body
void fn_sub_3C40F0_003c40f0__recomp(EEContext&);  // recompiled
void fn_sub_3C4110_003c4110(EEContext&);  // generated body
void fn_sub_3C4110_003c4110__recomp(EEContext&);  // recompiled
void fn_sub_3C4130_003c4130(EEContext&);  // generated body
void fn_sub_3C4130_003c4130__recomp(EEContext&);  // recompiled
void fn_sub_3C4210_003c4210(EEContext&);  // generated body
void fn_sub_3C4210_003c4210__recomp(EEContext&);  // recompiled
void fn_sub_3C4270_003c4270(EEContext&);  // generated body
void fn_sub_3C4270_003c4270__recomp(EEContext&);  // recompiled
void fn_sub_3C4390_003c4390(EEContext&);  // generated body
void fn_sub_3C4390_003c4390__recomp(EEContext&);  // recompiled
void fn_sub_3C43F0_003c43f0(EEContext&);  // generated body
void fn_sub_3C43F0_003c43f0__recomp(EEContext&);  // recompiled
void fn_sub_3C4400_003c4400(EEContext&);  // generated body
void fn_sub_3C4400_003c4400__recomp(EEContext&);  // recompiled
void fn_sub_3C4410_003c4410(EEContext&);  // generated body
void fn_sub_3C4410_003c4410__recomp(EEContext&);  // recompiled
void fn_sub_3C4420_003c4420(EEContext&);  // generated body
void fn_sub_3C4420_003c4420__recomp(EEContext&);  // recompiled
void fn_Y_LMap_UpdateLmapTask_00421770(EEContext&);  // generated body
void fn_Y_LMap_UpdateLmapTask_00421770__recomp(EEContext&);  // recompiled
void fn_sub_421D70_00421d70(EEContext&);  // generated body
void fn_sub_421D70_00421d70__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateLmapTask_00421de0(EEContext&);  // generated body
void fn_Y_LMap_CreateLmapTask_00421de0__recomp(EEContext&);  // recompiled
void fn_sub_421EF0_00421ef0(EEContext&);  // generated body
void fn_sub_421EF0_00421ef0__recomp(EEContext&);  // recompiled
void fn_sub_421F10_00421f10(EEContext&);  // generated body
void fn_sub_421F10_00421f10__recomp(EEContext&);  // recompiled
void fn_sub_421F20_00421f20(EEContext&);  // generated body
void fn_sub_421F20_00421f20__recomp(EEContext&);  // recompiled
void fn_sub_421FB0_00421fb0(EEContext&);  // generated body
void fn_sub_421FB0_00421fb0__recomp(EEContext&);  // recompiled
void fn_sub_421FE0_00421fe0(EEContext&);  // generated body
void fn_sub_421FE0_00421fe0__recomp(EEContext&);  // recompiled
void fn_sub_4221A0_004221a0(EEContext&);  // generated body
void fn_sub_4221A0_004221a0__recomp(EEContext&);  // recompiled
void fn_sub_4222D0_004222d0(EEContext&);  // generated body
void fn_sub_4222D0_004222d0__recomp(EEContext&);  // recompiled
void fn_sub_4229A0_004229a0(EEContext&);  // generated body
void fn_sub_4229A0_004229a0__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateBoxfillTasks_004229d0(EEContext&);  // generated body
void fn_Y_LMap_CreateBoxfillTasks_004229d0__recomp(EEContext&);  // recompiled
void fn_sub_422C10_00422c10(EEContext&);  // generated body
void fn_sub_422C10_00422c10__recomp(EEContext&);  // recompiled
void fn_sub_422C30_00422c30(EEContext&);  // generated body
void fn_sub_422C30_00422c30__recomp(EEContext&);  // recompiled
void fn_sub_422C90_00422c90(EEContext&);  // generated body
void fn_sub_422C90_00422c90__recomp(EEContext&);  // recompiled
void fn_sub_422CD0_00422cd0(EEContext&);  // generated body
void fn_sub_422CD0_00422cd0__recomp(EEContext&);  // recompiled
void fn_Y_LMap_UpdateLMapMenuTask_00422ce0(EEContext&);  // generated body
void fn_Y_LMap_UpdateLMapMenuTask_00422ce0__recomp(EEContext&);  // recompiled
void fn_sub_423790_00423790(EEContext&);  // generated body
void fn_sub_423790_00423790__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateLMapMenuTask_004238b0(EEContext&);  // generated body
void fn_Y_LMap_CreateLMapMenuTask_004238b0__recomp(EEContext&);  // recompiled
void fn_sub_423B50_00423b50(EEContext&);  // generated body
void fn_sub_423B50_00423b50__recomp(EEContext&);  // recompiled
void fn_sub_423B70_00423b70(EEContext&);  // generated body
void fn_sub_423B70_00423b70__recomp(EEContext&);  // recompiled
void fn_sub_423BA0_00423ba0(EEContext&);  // generated body
void fn_sub_423BA0_00423ba0__recomp(EEContext&);  // recompiled
void fn_sub_423BF0_00423bf0(EEContext&);  // generated body
void fn_sub_423BF0_00423bf0__recomp(EEContext&);  // recompiled
void fn_sub_423C10_00423c10(EEContext&);  // generated body
void fn_sub_423C10_00423c10__recomp(EEContext&);  // recompiled
void fn_sub_423CD0_00423cd0(EEContext&);  // generated body
void fn_sub_423CD0_00423cd0__recomp(EEContext&);  // recompiled
void fn_sub_423FC0_00423fc0(EEContext&);  // generated body
void fn_sub_423FC0_00423fc0__recomp(EEContext&);  // recompiled
void fn_sub_423FE0_00423fe0(EEContext&);  // generated body
void fn_sub_423FE0_00423fe0__recomp(EEContext&);  // recompiled
void fn_sub_4241E0_004241e0(EEContext&);  // generated body
void fn_sub_4241E0_004241e0__recomp(EEContext&);  // recompiled
void fn_sub_424230_00424230(EEContext&);  // generated body
void fn_sub_424230_00424230__recomp(EEContext&);  // recompiled
void fn_sub_4242B0_004242b0(EEContext&);  // generated body
void fn_sub_4242B0_004242b0__recomp(EEContext&);  // recompiled
void fn_sub_424310_00424310(EEContext&);  // generated body
void fn_sub_424310_00424310__recomp(EEContext&);  // recompiled
void fn_sub_424370_00424370(EEContext&);  // generated body
void fn_sub_424370_00424370__recomp(EEContext&);  // recompiled
void fn_sub_424B60_00424b60(EEContext&);  // generated body
void fn_sub_424B60_00424b60__recomp(EEContext&);  // recompiled
void fn_sub_424F80_00424f80(EEContext&);  // generated body
void fn_sub_424F80_00424f80__recomp(EEContext&);  // recompiled
void fn_sub_425020_00425020(EEContext&);  // generated body
void fn_sub_425020_00425020__recomp(EEContext&);  // recompiled
void fn_sub_425070_00425070(EEContext&);  // generated body
void fn_sub_425070_00425070__recomp(EEContext&);  // recompiled
void fn_sub_4252D0_004252d0(EEContext&);  // generated body
void fn_sub_4252D0_004252d0__recomp(EEContext&);  // recompiled
void fn_sub_425320_00425320(EEContext&);  // generated body
void fn_sub_425320_00425320__recomp(EEContext&);  // recompiled
void fn_sub_425480_00425480(EEContext&);  // generated body
void fn_sub_425480_00425480__recomp(EEContext&);  // recompiled
void fn_sub_425690_00425690(EEContext&);  // generated body
void fn_sub_425690_00425690__recomp(EEContext&);  // recompiled
void fn_sub_425BA0_00425ba0(EEContext&);  // generated body
void fn_sub_425BA0_00425ba0__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateLmapModelTask_00425c60(EEContext&);  // generated body
void fn_Y_LMap_CreateLmapModelTask_00425c60__recomp(EEContext&);  // recompiled
void fn_sub_425D10_00425d10(EEContext&);  // generated body
void fn_sub_425D10_00425d10__recomp(EEContext&);  // recompiled
void fn_sub_425D30_00425d30(EEContext&);  // generated body
void fn_sub_425D30_00425d30__recomp(EEContext&);  // recompiled
void fn_sub_425D50_00425d50(EEContext&);  // generated body
void fn_sub_425D50_00425d50__recomp(EEContext&);  // recompiled
void fn_sub_426040_00426040(EEContext&);  // generated body
void fn_sub_426040_00426040__recomp(EEContext&);  // recompiled
void fn_sub_426050_00426050(EEContext&);  // generated body
void fn_sub_426050_00426050__recomp(EEContext&);  // recompiled
void fn_sub_426070_00426070(EEContext&);  // generated body
void fn_sub_426070_00426070__recomp(EEContext&);  // recompiled
void fn_sub_426090_00426090(EEContext&);  // generated body
void fn_sub_426090_00426090__recomp(EEContext&);  // recompiled
void fn_sub_4260A0_004260a0(EEContext&);  // generated body
void fn_sub_4260A0_004260a0__recomp(EEContext&);  // recompiled
void fn_sub_4264A0_004264a0(EEContext&);  // generated body
void fn_sub_4264A0_004264a0__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateLmapModelMoveTask_004264d0(EEContext&);  // generated body
void fn_Y_LMap_CreateLmapModelMoveTask_004264d0__recomp(EEContext&);  // recompiled
void fn_sub_426590_00426590(EEContext&);  // generated body
void fn_sub_426590_00426590__recomp(EEContext&);  // recompiled
void fn_sub_427640_00427640(EEContext&);  // generated body
void fn_sub_427640_00427640__recomp(EEContext&);  // recompiled
void fn_Y_LMap_CreateTmxDispTask_00427670(EEContext&);  // generated body
void fn_Y_LMap_CreateTmxDispTask_00427670__recomp(EEContext&);  // recompiled
void fn_sub_427830_00427830(EEContext&);  // generated body
void fn_sub_427830_00427830__recomp(EEContext&);  // recompiled
void fn_sub_427A10_00427a10(EEContext&);  // generated body
void fn_sub_427A10_00427a10__recomp(EEContext&);  // recompiled
void fn_sub_427BF0_00427bf0(EEContext&);  // generated body
void fn_sub_427BF0_00427bf0__recomp(EEContext&);  // recompiled
void fn_sub_427DB0_00427db0(EEContext&);  // generated body
void fn_sub_427DB0_00427db0__recomp(EEContext&);  // recompiled
void fn_sub_427DE0_00427de0(EEContext&);  // generated body
void fn_sub_427DE0_00427de0__recomp(EEContext&);  // recompiled
void fn_sub_427E20_00427e20(EEContext&);  // generated body
void fn_sub_427E20_00427e20__recomp(EEContext&);  // recompiled
void fn_sub_427E50_00427e50(EEContext&);  // generated body
void fn_sub_427E50_00427e50__recomp(EEContext&);  // recompiled
void fn_sub_427E60_00427e60(EEContext&);  // generated body
void fn_sub_427E60_00427e60__recomp(EEContext&);  // recompiled
void fn_sub_427E70_00427e70(EEContext&);  // generated body
void fn_sub_427E70_00427e70__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_3C03F0", 0x3C03F0, &recomp_gen::fn_sub_3C03F0_003c03f0, &recomp_gen::fn_sub_3C03F0_003c03f0__recomp},
    {"sub_3C0570", 0x3C0570, &recomp_gen::fn_sub_3C0570_003c0570, &recomp_gen::fn_sub_3C0570_003c0570__recomp},
    {"sub_3C07C0", 0x3C07C0, &recomp_gen::fn_sub_3C07C0_003c07c0, &recomp_gen::fn_sub_3C07C0_003c07c0__recomp},
    {"sub_3C09A0", 0x3C09A0, &recomp_gen::fn_sub_3C09A0_003c09a0, &recomp_gen::fn_sub_3C09A0_003c09a0__recomp},
    {"sub_3C0B30", 0x3C0B30, &recomp_gen::fn_sub_3C0B30_003c0b30, &recomp_gen::fn_sub_3C0B30_003c0b30__recomp},
    {"sub_3C0BD0", 0x3C0BD0, &recomp_gen::fn_sub_3C0BD0_003c0bd0, &recomp_gen::fn_sub_3C0BD0_003c0bd0__recomp},
    {"sub_3C0C30", 0x3C0C30, &recomp_gen::fn_sub_3C0C30_003c0c30, &recomp_gen::fn_sub_3C0C30_003c0c30__recomp},
    {"sub_3C0D20", 0x3C0D20, &recomp_gen::fn_sub_3C0D20_003c0d20, &recomp_gen::fn_sub_3C0D20_003c0d20__recomp},
    {"sub_3C0DB0", 0x3C0DB0, &recomp_gen::fn_sub_3C0DB0_003c0db0, &recomp_gen::fn_sub_3C0DB0_003c0db0__recomp},
    {"sub_3C0F20", 0x3C0F20, &recomp_gen::fn_sub_3C0F20_003c0f20, &recomp_gen::fn_sub_3C0F20_003c0f20__recomp},
    {"sub_3C1150", 0x3C1150, &recomp_gen::fn_sub_3C1150_003c1150, &recomp_gen::fn_sub_3C1150_003c1150__recomp},
    {"sub_3C1300", 0x3C1300, &recomp_gen::fn_sub_3C1300_003c1300, &recomp_gen::fn_sub_3C1300_003c1300__recomp},
    {"sub_3C1340", 0x3C1340, &recomp_gen::fn_sub_3C1340_003c1340, &recomp_gen::fn_sub_3C1340_003c1340__recomp},
    {"sub_3C1430", 0x3C1430, &recomp_gen::fn_sub_3C1430_003c1430, &recomp_gen::fn_sub_3C1430_003c1430__recomp},
    {"sub_3C1440", 0x3C1440, &recomp_gen::fn_sub_3C1440_003c1440, &recomp_gen::fn_sub_3C1440_003c1440__recomp},
    {"sub_3C15D0", 0x3C15D0, &recomp_gen::fn_sub_3C15D0_003c15d0, &recomp_gen::fn_sub_3C15D0_003c15d0__recomp},
    {"sub_3C1810", 0x3C1810, &recomp_gen::fn_sub_3C1810_003c1810, &recomp_gen::fn_sub_3C1810_003c1810__recomp},
    {"sub_3C18C0", 0x3C18C0, &recomp_gen::fn_sub_3C18C0_003c18c0, &recomp_gen::fn_sub_3C18C0_003c18c0__recomp},
    {"sub_3C1A70", 0x3C1A70, &recomp_gen::fn_sub_3C1A70_003c1a70, &recomp_gen::fn_sub_3C1A70_003c1a70__recomp},
    {"comu_CreateComuTimerProcessTask", 0x3C1AB0, &recomp_gen::fn_comu_CreateComuTimerProcessTask_003c1ab0, &recomp_gen::fn_comu_CreateComuTimerProcessTask_003c1ab0__recomp},
    {"comu_UpdateRevMailSeqTask", 0x3C1D20, &recomp_gen::fn_comu_UpdateRevMailSeqTask_003c1d20, &recomp_gen::fn_comu_UpdateRevMailSeqTask_003c1d20__recomp},
    {"sub_3C22F0", 0x3C22F0, &recomp_gen::fn_sub_3C22F0_003c22f0, &recomp_gen::fn_sub_3C22F0_003c22f0__recomp},
    {"comu_CreateRevMailSeqTask", 0x3C2350, &recomp_gen::fn_comu_CreateRevMailSeqTask_003c2350, &recomp_gen::fn_comu_CreateRevMailSeqTask_003c2350__recomp},
    {"sub_3C23F0", 0x3C23F0, &recomp_gen::fn_sub_3C23F0_003c23f0, &recomp_gen::fn_sub_3C23F0_003c23f0__recomp},
    {"sub_3C2570", 0x3C2570, &recomp_gen::fn_sub_3C2570_003c2570, &recomp_gen::fn_sub_3C2570_003c2570__recomp},
    {"sub_3C2630", 0x3C2630, &recomp_gen::fn_sub_3C2630_003c2630, &recomp_gen::fn_sub_3C2630_003c2630__recomp},
    {"sub_3C2770", 0x3C2770, &recomp_gen::fn_sub_3C2770_003c2770, &recomp_gen::fn_sub_3C2770_003c2770__recomp},
    {"sub_3C2780", 0x3C2780, &recomp_gen::fn_sub_3C2780_003c2780, &recomp_gen::fn_sub_3C2780_003c2780__recomp},
    {"sub_3C28A0", 0x3C28A0, &recomp_gen::fn_sub_3C28A0_003c28a0, &recomp_gen::fn_sub_3C28A0_003c28a0__recomp},
    {"sub_3C2AB0", 0x3C2AB0, &recomp_gen::fn_sub_3C2AB0_003c2ab0, &recomp_gen::fn_sub_3C2AB0_003c2ab0__recomp},
    {"sub_3C2B40", 0x3C2B40, &recomp_gen::fn_sub_3C2B40_003c2b40, &recomp_gen::fn_sub_3C2B40_003c2b40__recomp},
    {"sub_3C2C50", 0x3C2C50, &recomp_gen::fn_sub_3C2C50_003c2c50, &recomp_gen::fn_sub_3C2C50_003c2c50__recomp},
    {"sub_3C2DF0", 0x3C2DF0, &recomp_gen::fn_sub_3C2DF0_003c2df0, &recomp_gen::fn_sub_3C2DF0_003c2df0__recomp},
    {"sub_3C2EE0", 0x3C2EE0, &recomp_gen::fn_sub_3C2EE0_003c2ee0, &recomp_gen::fn_sub_3C2EE0_003c2ee0__recomp},
    {"sub_3C3050", 0x3C3050, &recomp_gen::fn_sub_3C3050_003c3050, &recomp_gen::fn_sub_3C3050_003c3050__recomp},
    {"sub_3C30B0", 0x3C30B0, &recomp_gen::fn_sub_3C30B0_003c30b0, &recomp_gen::fn_sub_3C30B0_003c30b0__recomp},
    {"sub_3C3120", 0x3C3120, &recomp_gen::fn_sub_3C3120_003c3120, &recomp_gen::fn_sub_3C3120_003c3120__recomp},
    {"sub_3C3190", 0x3C3190, &recomp_gen::fn_sub_3C3190_003c3190, &recomp_gen::fn_sub_3C3190_003c3190__recomp},
    {"sub_3C3390", 0x3C3390, &recomp_gen::fn_sub_3C3390_003c3390, &recomp_gen::fn_sub_3C3390_003c3390__recomp},
    {"sub_3C33C0", 0x3C33C0, &recomp_gen::fn_sub_3C33C0_003c33c0, &recomp_gen::fn_sub_3C33C0_003c33c0__recomp},
    {"sub_3C3E80", 0x3C3E80, &recomp_gen::fn_sub_3C3E80_003c3e80, &recomp_gen::fn_sub_3C3E80_003c3e80__recomp},
    {"sub_3C3F40", 0x3C3F40, &recomp_gen::fn_sub_3C3F40_003c3f40, &recomp_gen::fn_sub_3C3F40_003c3f40__recomp},
    {"sub_3C3F80", 0x3C3F80, &recomp_gen::fn_sub_3C3F80_003c3f80, &recomp_gen::fn_sub_3C3F80_003c3f80__recomp},
    {"sub_3C3FE0", 0x3C3FE0, &recomp_gen::fn_sub_3C3FE0_003c3fe0, &recomp_gen::fn_sub_3C3FE0_003c3fe0__recomp},
    {"sub_3C4040", 0x3C4040, &recomp_gen::fn_sub_3C4040_003c4040, &recomp_gen::fn_sub_3C4040_003c4040__recomp},
    {"sub_3C40F0", 0x3C40F0, &recomp_gen::fn_sub_3C40F0_003c40f0, &recomp_gen::fn_sub_3C40F0_003c40f0__recomp},
    {"sub_3C4110", 0x3C4110, &recomp_gen::fn_sub_3C4110_003c4110, &recomp_gen::fn_sub_3C4110_003c4110__recomp},
    {"sub_3C4130", 0x3C4130, &recomp_gen::fn_sub_3C4130_003c4130, &recomp_gen::fn_sub_3C4130_003c4130__recomp},
    {"sub_3C4210", 0x3C4210, &recomp_gen::fn_sub_3C4210_003c4210, &recomp_gen::fn_sub_3C4210_003c4210__recomp},
    {"sub_3C4270", 0x3C4270, &recomp_gen::fn_sub_3C4270_003c4270, &recomp_gen::fn_sub_3C4270_003c4270__recomp},
    {"sub_3C4390", 0x3C4390, &recomp_gen::fn_sub_3C4390_003c4390, &recomp_gen::fn_sub_3C4390_003c4390__recomp},
    {"sub_3C43F0", 0x3C43F0, &recomp_gen::fn_sub_3C43F0_003c43f0, &recomp_gen::fn_sub_3C43F0_003c43f0__recomp},
    {"sub_3C4400", 0x3C4400, &recomp_gen::fn_sub_3C4400_003c4400, &recomp_gen::fn_sub_3C4400_003c4400__recomp},
    {"sub_3C4410", 0x3C4410, &recomp_gen::fn_sub_3C4410_003c4410, &recomp_gen::fn_sub_3C4410_003c4410__recomp},
    {"sub_3C4420", 0x3C4420, &recomp_gen::fn_sub_3C4420_003c4420, &recomp_gen::fn_sub_3C4420_003c4420__recomp},
    {"Y_LMap_UpdateLmapTask", 0x421770, &recomp_gen::fn_Y_LMap_UpdateLmapTask_00421770, &recomp_gen::fn_Y_LMap_UpdateLmapTask_00421770__recomp},
    {"sub_421D70", 0x421D70, &recomp_gen::fn_sub_421D70_00421d70, &recomp_gen::fn_sub_421D70_00421d70__recomp},
    {"Y_LMap_CreateLmapTask", 0x421DE0, &recomp_gen::fn_Y_LMap_CreateLmapTask_00421de0, &recomp_gen::fn_Y_LMap_CreateLmapTask_00421de0__recomp},
    {"sub_421EF0", 0x421EF0, &recomp_gen::fn_sub_421EF0_00421ef0, &recomp_gen::fn_sub_421EF0_00421ef0__recomp},
    {"sub_421F10", 0x421F10, &recomp_gen::fn_sub_421F10_00421f10, &recomp_gen::fn_sub_421F10_00421f10__recomp},
    {"sub_421F20", 0x421F20, &recomp_gen::fn_sub_421F20_00421f20, &recomp_gen::fn_sub_421F20_00421f20__recomp},
    {"sub_421FB0", 0x421FB0, &recomp_gen::fn_sub_421FB0_00421fb0, &recomp_gen::fn_sub_421FB0_00421fb0__recomp},
    {"sub_421FE0", 0x421FE0, &recomp_gen::fn_sub_421FE0_00421fe0, &recomp_gen::fn_sub_421FE0_00421fe0__recomp},
    {"sub_4221A0", 0x4221A0, &recomp_gen::fn_sub_4221A0_004221a0, &recomp_gen::fn_sub_4221A0_004221a0__recomp},
    {"sub_4222D0", 0x4222D0, &recomp_gen::fn_sub_4222D0_004222d0, &recomp_gen::fn_sub_4222D0_004222d0__recomp},
    {"sub_4229A0", 0x4229A0, &recomp_gen::fn_sub_4229A0_004229a0, &recomp_gen::fn_sub_4229A0_004229a0__recomp},
    {"Y_LMap_CreateBoxfillTasks", 0x4229D0, &recomp_gen::fn_Y_LMap_CreateBoxfillTasks_004229d0, &recomp_gen::fn_Y_LMap_CreateBoxfillTasks_004229d0__recomp},
    {"sub_422C10", 0x422C10, &recomp_gen::fn_sub_422C10_00422c10, &recomp_gen::fn_sub_422C10_00422c10__recomp},
    {"sub_422C30", 0x422C30, &recomp_gen::fn_sub_422C30_00422c30, &recomp_gen::fn_sub_422C30_00422c30__recomp},
    {"sub_422C90", 0x422C90, &recomp_gen::fn_sub_422C90_00422c90, &recomp_gen::fn_sub_422C90_00422c90__recomp},
    {"sub_422CD0", 0x422CD0, &recomp_gen::fn_sub_422CD0_00422cd0, &recomp_gen::fn_sub_422CD0_00422cd0__recomp},
    {"Y_LMap_UpdateLMapMenuTask", 0x422CE0, &recomp_gen::fn_Y_LMap_UpdateLMapMenuTask_00422ce0, &recomp_gen::fn_Y_LMap_UpdateLMapMenuTask_00422ce0__recomp},
    {"sub_423790", 0x423790, &recomp_gen::fn_sub_423790_00423790, &recomp_gen::fn_sub_423790_00423790__recomp},
    {"Y_LMap_CreateLMapMenuTask", 0x4238B0, &recomp_gen::fn_Y_LMap_CreateLMapMenuTask_004238b0, &recomp_gen::fn_Y_LMap_CreateLMapMenuTask_004238b0__recomp},
    {"sub_423B50", 0x423B50, &recomp_gen::fn_sub_423B50_00423b50, &recomp_gen::fn_sub_423B50_00423b50__recomp},
    {"sub_423B70", 0x423B70, &recomp_gen::fn_sub_423B70_00423b70, &recomp_gen::fn_sub_423B70_00423b70__recomp},
    {"sub_423BA0", 0x423BA0, &recomp_gen::fn_sub_423BA0_00423ba0, &recomp_gen::fn_sub_423BA0_00423ba0__recomp},
    {"sub_423BF0", 0x423BF0, &recomp_gen::fn_sub_423BF0_00423bf0, &recomp_gen::fn_sub_423BF0_00423bf0__recomp},
    {"sub_423C10", 0x423C10, &recomp_gen::fn_sub_423C10_00423c10, &recomp_gen::fn_sub_423C10_00423c10__recomp},
    {"sub_423CD0", 0x423CD0, &recomp_gen::fn_sub_423CD0_00423cd0, &recomp_gen::fn_sub_423CD0_00423cd0__recomp},
    {"sub_423FC0", 0x423FC0, &recomp_gen::fn_sub_423FC0_00423fc0, &recomp_gen::fn_sub_423FC0_00423fc0__recomp},
    {"sub_423FE0", 0x423FE0, &recomp_gen::fn_sub_423FE0_00423fe0, &recomp_gen::fn_sub_423FE0_00423fe0__recomp},
    {"sub_4241E0", 0x4241E0, &recomp_gen::fn_sub_4241E0_004241e0, &recomp_gen::fn_sub_4241E0_004241e0__recomp},
    {"sub_424230", 0x424230, &recomp_gen::fn_sub_424230_00424230, &recomp_gen::fn_sub_424230_00424230__recomp},
    {"sub_4242B0", 0x4242B0, &recomp_gen::fn_sub_4242B0_004242b0, &recomp_gen::fn_sub_4242B0_004242b0__recomp},
    {"sub_424310", 0x424310, &recomp_gen::fn_sub_424310_00424310, &recomp_gen::fn_sub_424310_00424310__recomp},
    {"sub_424370", 0x424370, &recomp_gen::fn_sub_424370_00424370, &recomp_gen::fn_sub_424370_00424370__recomp},
    {"sub_424B60", 0x424B60, &recomp_gen::fn_sub_424B60_00424b60, &recomp_gen::fn_sub_424B60_00424b60__recomp},
    {"sub_424F80", 0x424F80, &recomp_gen::fn_sub_424F80_00424f80, &recomp_gen::fn_sub_424F80_00424f80__recomp},
    {"sub_425020", 0x425020, &recomp_gen::fn_sub_425020_00425020, &recomp_gen::fn_sub_425020_00425020__recomp},
    {"sub_425070", 0x425070, &recomp_gen::fn_sub_425070_00425070, &recomp_gen::fn_sub_425070_00425070__recomp},
    {"sub_4252D0", 0x4252D0, &recomp_gen::fn_sub_4252D0_004252d0, &recomp_gen::fn_sub_4252D0_004252d0__recomp},
    {"sub_425320", 0x425320, &recomp_gen::fn_sub_425320_00425320, &recomp_gen::fn_sub_425320_00425320__recomp},
    {"sub_425480", 0x425480, &recomp_gen::fn_sub_425480_00425480, &recomp_gen::fn_sub_425480_00425480__recomp},
    {"sub_425690", 0x425690, &recomp_gen::fn_sub_425690_00425690, &recomp_gen::fn_sub_425690_00425690__recomp},
    {"sub_425BA0", 0x425BA0, &recomp_gen::fn_sub_425BA0_00425ba0, &recomp_gen::fn_sub_425BA0_00425ba0__recomp},
    {"Y_LMap_CreateLmapModelTask", 0x425C60, &recomp_gen::fn_Y_LMap_CreateLmapModelTask_00425c60, &recomp_gen::fn_Y_LMap_CreateLmapModelTask_00425c60__recomp},
    {"sub_425D10", 0x425D10, &recomp_gen::fn_sub_425D10_00425d10, &recomp_gen::fn_sub_425D10_00425d10__recomp},
    {"sub_425D30", 0x425D30, &recomp_gen::fn_sub_425D30_00425d30, &recomp_gen::fn_sub_425D30_00425d30__recomp},
    {"sub_425D50", 0x425D50, &recomp_gen::fn_sub_425D50_00425d50, &recomp_gen::fn_sub_425D50_00425d50__recomp},
    {"sub_426040", 0x426040, &recomp_gen::fn_sub_426040_00426040, &recomp_gen::fn_sub_426040_00426040__recomp},
    {"sub_426050", 0x426050, &recomp_gen::fn_sub_426050_00426050, &recomp_gen::fn_sub_426050_00426050__recomp},
    {"sub_426070", 0x426070, &recomp_gen::fn_sub_426070_00426070, &recomp_gen::fn_sub_426070_00426070__recomp},
    {"sub_426090", 0x426090, &recomp_gen::fn_sub_426090_00426090, &recomp_gen::fn_sub_426090_00426090__recomp},
    {"sub_4260A0", 0x4260A0, &recomp_gen::fn_sub_4260A0_004260a0, &recomp_gen::fn_sub_4260A0_004260a0__recomp},
    {"sub_4264A0", 0x4264A0, &recomp_gen::fn_sub_4264A0_004264a0, &recomp_gen::fn_sub_4264A0_004264a0__recomp},
    {"Y_LMap_CreateLmapModelMoveTask", 0x4264D0, &recomp_gen::fn_Y_LMap_CreateLmapModelMoveTask_004264d0, &recomp_gen::fn_Y_LMap_CreateLmapModelMoveTask_004264d0__recomp},
    {"sub_426590", 0x426590, &recomp_gen::fn_sub_426590_00426590, &recomp_gen::fn_sub_426590_00426590__recomp},
    {"sub_427640", 0x427640, &recomp_gen::fn_sub_427640_00427640, &recomp_gen::fn_sub_427640_00427640__recomp},
    {"Y_LMap_CreateTmxDispTask", 0x427670, &recomp_gen::fn_Y_LMap_CreateTmxDispTask_00427670, &recomp_gen::fn_Y_LMap_CreateTmxDispTask_00427670__recomp},
    {"sub_427830", 0x427830, &recomp_gen::fn_sub_427830_00427830, &recomp_gen::fn_sub_427830_00427830__recomp},
    {"sub_427A10", 0x427A10, &recomp_gen::fn_sub_427A10_00427a10, &recomp_gen::fn_sub_427A10_00427a10__recomp},
    {"sub_427BF0", 0x427BF0, &recomp_gen::fn_sub_427BF0_00427bf0, &recomp_gen::fn_sub_427BF0_00427bf0__recomp},
    {"sub_427DB0", 0x427DB0, &recomp_gen::fn_sub_427DB0_00427db0, &recomp_gen::fn_sub_427DB0_00427db0__recomp},
    {"sub_427DE0", 0x427DE0, &recomp_gen::fn_sub_427DE0_00427de0, &recomp_gen::fn_sub_427DE0_00427de0__recomp},
    {"sub_427E20", 0x427E20, &recomp_gen::fn_sub_427E20_00427e20, &recomp_gen::fn_sub_427E20_00427e20__recomp},
    {"sub_427E50", 0x427E50, &recomp_gen::fn_sub_427E50_00427e50, &recomp_gen::fn_sub_427E50_00427e50__recomp},
    {"sub_427E60", 0x427E60, &recomp_gen::fn_sub_427E60_00427e60, &recomp_gen::fn_sub_427E60_00427e60__recomp},
    {"sub_427E70", 0x427E70, &recomp_gen::fn_sub_427E70_00427e70, &recomp_gen::fn_sub_427E70_00427e70__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that (a) set chosen FPRs after the random register
// file ($f12.. arguments) and (b) optionally give each body a fresh, identical stand-in world (stand_ins.h: the heap
// behind H_Malloc and the RW slots, printf / sprintf, the H_Cdvd layer over extracted/), whose call logs must match.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
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
    g_t.world[K] = std::make_unique<StandInWorld>();
    install_standard(*g_t.world[K]);
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
};

hgp::Run sm_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    ++g_pairs;
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u32 f0_of(const hgp::Run& r) { return r.end.fpr[0]; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
u32 fbits(float f) { return std::bit_cast<u32>(f); }
float fval(u32 b) { return std::bit_cast<float>(b); }

constexpr u32 kDaysSinceApr5 = 0x83679Cu;  // s16 (ui.h)
constexpr u32 kTimeOfDay = 0x83679Eu;      // u8 (ui.h)
constexpr u32 kOut = 0x01F40000u;          // free in every snapshot (stand_ins.h) and in the ELF image
constexpr u32 kTask = 0x01F41000u;         // a fake task: +0x3C -> kWork
constexpr u32 kWork = 0x01F41100u;
constexpr u32 kRec = 0x01F42000u;          // an area-map record (task +0x3C)

// The game calendar of the snapshots: day 0 = April 5 .. day 360 = March 31 of the next year (28 days in February).
constexpr u32 kCalendarDays = 361;
struct Date {
    u32 month, day;
};
Date date_of(u32 days) {
    static const u32 len[12] = {30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31};  // April first
    u32 d = days + 4;  // April 1 + 4 = April 5
    for (u32 i = 0; i < 12; ++i) {
        if (d < len[i]) return {(i + 3) % 12 + 1, d + 1};
        d -= len[i];
    }
    return {3, 31};
}

bool load_snapshot(Machine& m, std::string* which = nullptr) {
    for (const char* s : {"dorm_replay_4900", "b_5800", "battle_ref_6150", "v_m1"}) {
        const std::vector<u8> snap = read_snapshot(s);
        if (snap.size() != EEMemory::kMainRamSize) continue;
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        if (which) *which = s;
        return true;
    }
    return false;
}

std::string guest_str(const Machine& m, u32 va) { return va ? m.str(va, 64) : std::string(); }

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton, fewer seeds: the tests below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(social_map): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
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
// The comu tables of a replay snapshot (loaded at boot, identical in every snapshot), every day of the year
// =====================================================================================================================
TEST_CASE("game(social_map): comu lookups on the snapshot's tables, every day of the year") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::string snap;
    if (!load_snapshot(m, &snap)) {
        MESSAGE("SKIP: no replay snapshot under extracted/_ours");
        return;
    }
    const u32 event_rows = r32(m, game::kComuData + game::kComuEventRows), event_n = r32(m, game::kComuData + game::kComuEventCount);
    const u32 busy_rows = r32(m, game::kComuData + game::kComuBusyRows), busy_n = r32(m, game::kComuData + game::kComuBusyCount);
    const u32 nocall_rows = r32(m, game::kComuData2 + 8), nocall_n = r32(m, game::kComuData2 + 12);
    MESSAGE(snap << ": comu tables: " << event_n << " event rows, " << busy_n << " no-call rows, " << nocall_n << " no-call days, "
                 << r32(m, game::kComuData + game::kComuAvailCount) << " availability rows, "
                 << r32(m, game::kComuData + game::kComuSasoiCount) << " invitation rows");
    REQUIRE(event_n > 0);
    REQUIRE(event_n < 1000);
    int events_found = 0, busy_found = 0, nocall_found = 0;
    for (u32 days = 0; days < kCalendarDays; ++days) {  // April 5 .. March 31
        const Date d = date_of(days);
        const u32 slot = (days & 1) ? 4u : 2u;  // evening / after school
        w16(m, kDaysSinceApr5, static_cast<u16>(days));
        w8(m, kTimeOfDay, static_cast<u8>(slot));
        const u32 seed = 1000 + days;
        // sub_3C0DB0: today's timer event (documented rule: the first row of the date for the time slot)
        std::memset(m.at(kOut), 0xEE, 16);
        const hgp::Run r = sm_pair(m, "sub_3C0DB0", {sx(kOut), sx(kOut + 4), sx(kOut + 8), 0}, seed, "snapshot: sub_3C0DB0");
        if (!r.stopped) {
            int expect = -1;
            for (u32 i = 0; i < event_n && expect < 0; ++i) {
                const u32 row = event_rows + 12 * i;
                if (r8(m, row) != d.month || r8(m, row + 1) != d.day) continue;
                const u32 need = r32(m, row + 4) == 0 ? 2u : 4u;
                if (need == slot) expect = static_cast<int>(i);
            }
            INFO("day " << days << " = " << d.month << "/" << d.day << " slot " << slot);
            CHECK(v0_of(r) == (expect >= 0 ? 1u : 0u));
            if (expect >= 0) {
                ++events_found;
                const u32 row = event_rows + 12 * static_cast<u32>(expect);
                CHECK(r32(m, kOut) == r16(m, row + 8));
                CHECK(r32(m, kOut + 4) == r8(m, row + 10));
                CHECK(r32(m, kOut + 8) == r8(m, row + 11));
            } else {
                CHECK(r32(m, kOut) == 0xEEEEEEEEu);
            }
        }
        // sub_3C2DF0: a no-call row for today and the link (or 0xFF)
        const u32 link = days % game::kComuNumLinks;
        const hgp::Run b = sm_pair(m, "sub_3C2DF0", {link, 0, 0, 0}, seed, "snapshot: sub_3C2DF0");
        if (!b.stopped) {
            bool busy = false;
            for (u32 i = 0; i < busy_n; ++i) {
                const u32 row = busy_rows + 3 * i;
                if (r8(m, row) == d.month && r8(m, row + 1) == d.day && (r8(m, row + 2) == link || r8(m, row + 2) == 0xFF)) busy = true;
            }
            CHECK(v0_of(b) == (busy ? 1u : 0u));
            busy_found += busy;
        }
        // sub_3C2AB0: the no-call days of 0x95B6A8 +8
        const hgp::Run n = sm_pair(m, "sub_3C2AB0", {d.month, d.day, 0, 0}, seed, "snapshot: sub_3C2AB0");
        if (!n.stopped) {
            bool nocall = false;
            for (u32 i = 0; i < nocall_n; ++i)
                if (r8(m, nocall_rows + 2 * i) == d.month && r8(m, nocall_rows + 2 * i + 1) == d.day) nocall = true;
            CHECK(v0_of(n) == (nocall ? 1u : 0u));
            nocall_found += nocall;
        }
        // the availability rules, the rank-gated invitation row, the tier, the can-call test
        sm_pair(m, "sub_3C23F0", {link, d.month, d.day, 0}, seed, "snapshot: sub_3C23F0");
        if (days % 4 == 0) {
            sm_pair(m, "sub_3C2C50", {link, 0, 0, 0}, seed, "snapshot: sub_3C2C50");
            sm_pair(m, "sub_3C2780", {link, 0, 0, 0}, seed, "snapshot: sub_3C2780");
            sm_pair(m, "sub_3C2570", {link, 0, 0, 0}, seed, "snapshot: sub_3C2570");
            sm_pair(m, "sub_3C28A0", {d.month, d.day, sx(kOut + 0x100), 2}, seed, "snapshot: sub_3C28A0",
                    Opt{{{GPR_T0, sx(kOut + 0x200)}, {GPR_T1, sx(kOut + 0x300)}}, {}, false});
            sm_pair(m, "sub_3C2B40", {sx(kOut), sx(kOut + 4), 0, 0}, seed, "snapshot: sub_3C2B40");
        }
        if (days % 9 == 0) {
            sm_pair(m, "sub_3C2630", {sx(0x1234), 0, 0, 0}, seed, "snapshot: sub_3C2630");
            sm_pair(m, "sub_3C2EE0", {link, 0, 0, 0}, seed, "snapshot: sub_3C2EE0");
            sm_pair(m, "sub_3C3050", {link, 0, 0, 0}, seed, "snapshot: sub_3C3050");
            sm_pair(m, "sub_3C30B0", {0, 0, 0, 0}, seed, "snapshot: sub_3C30B0");
            sm_pair(m, "sub_3C3120", {0, 0, 0, 0}, seed, "snapshot: sub_3C3120");
            sm_pair(m, "sub_3C3190", {sx(kOut), 0, 0, 0}, seed, "snapshot: sub_3C3190");
            sm_pair(m, "sub_3C3390", {0, 0, 0, 0}, seed, "snapshot: sub_3C3390");
        }
        // the "when" texts: the day after today is "tomorrow" (documented rule)
        const Date t = date_of(days + 1 < kCalendarDays ? days + 1 : days);
        const hgp::Run w = sm_pair(m, "sub_3C4270", {t.month, t.day, 0, 0}, seed, "snapshot: sub_3C4270");
        INFO("day " << days << " tomorrow " << t.month << "/" << t.day);
        if (!w.stopped && days + 1 < kCalendarDays) CHECK(guest_str(m, static_cast<u32>(v0_of(w))) == "tomorrow");
        if (days % 7 == 0) sm_pair(m, "sub_3C4130", {d.month, d.day, 0, 0}, seed, "snapshot: sub_3C4130");
    }
    MESSAGE("dates with a timer event for the slot: " << events_found << ", busy (link, day) pairs: " << busy_found
                                                      << ", no-call days: " << nocall_found);
    CHECK(events_found > 0);
    CHECK(nocall_found > 0);
}

// =====================================================================================================================
// The comu timer states on the snapshot: every state in every phase (the sequence manager, the RW heap stand-ins)
// =====================================================================================================================
TEST_CASE("game(social_map): comu timer states and the event executor on the snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m)) {
        MESSAGE("SKIP: no replay snapshot under extracted/_ours");
        return;
    }
    const char* states[] = {"sub_3C03F0", "sub_3C0570", "sub_3C07C0", "sub_3C09A0", "sub_3C0B30", "sub_3C0BD0",
                            "sub_3C0C30", "sub_3C0D20", "sub_3C0F20", "sub_3C1150", "sub_3C1300", "sub_3C1340",
                            "sub_3C1440", "sub_3C15D0", "sub_3C1810", "sub_3C18C0"};
    const u32 dates[] = {16, 22, 30, 100, 200, 300};  // April 21 (16), April 27 (22) are the dated events of sub_3C0570
    int finished = 0, handed_over = 0;
    for (u32 di = 0; di < std::size(dates); ++di) {
        w16(m, kDaysSinceApr5, static_cast<u16>(dates[di]));
        w8(m, kTimeOfDay, static_cast<u8>(di & 1 ? 4 : 2));
        for (const char* s : states) {
            for (u32 phase = 0; phase <= 4; ++phase) {
                for (u32 wait = 0; wait < 3; wait += 2) {
                    std::memset(m.at(kTask), 0, 0x40);
                    w32(m, kTask + 0x3C, kWork);
                    std::memset(m.at(kWork), 0, 0x60);
                    w32(m, kWork + game::kComuWorkPhase, phase);
                    w32(m, kWork + game::kComuWorkWait, wait);
                    w32(m, kWork + game::kComuWorkWaitLimit, 2);
                    const u32 seed = 5000 + di * 100 + phase * 10 + wait;
                    const hgp::Run r = sm_pair(m, s, {sx(kTask), 0, 0, 0}, seed, s, Opt{{}, {}, true});
                    if (r.stopped) continue;
                    const u64 v = v0_of(r);
                    if (v == ~0ull) ++finished;
                    else if (v != 0) {
                        ++handed_over;
                        // documented rule: a hand-over clears the six work words
                        for (s32 o = 0; o < 24; o += 4) CHECK(r32(m, kWork + static_cast<u32>(o)) == 0);
                    }
                }
            }
        }
    }
    MESSAGE("timer states: " << finished << " finished, " << handed_over << " handed over");
    CHECK(finished > 0);
    CHECK(handed_over > 0);
    // the event executor: each type 0..7 in each phase 0..3
    for (u32 type = 0; type < 8; ++type)
        for (u32 phase = 0; phase < 4; ++phase)
            for (u32 step = 0; step < 6; step += 3) {
                std::memset(m.at(kWork), 0, 0x40);
                w8(m, kWork + 0, static_cast<u8>((type * 3 + 1) % 30));
                w8(m, kWork + 1, static_cast<u8>((type * 7 + 2) % 30));
                w8(m, kWork + 2, static_cast<u8>(type));
                w8(m, kWork + 8, static_cast<u8>(step));
                w32(m, kWork + 12, phase);
                const u32 seed = 7000 + type * 100 + phase * 10 + step;
                sm_pair(m, "sub_3C33C0", {sx(kWork), sx(kOut), phase == 2 ? 1u : 0u, 0}, seed, "sub_3C33C0", Opt{{}, {}, true});
                w32(m, kWork + 12, phase);
                sm_pair(m, "sub_3C3E80", {sx(kWork), 0, 0, 0}, seed + 1, "sub_3C3E80", Opt{{}, {}, true});
            }
}

// =====================================================================================================================
// Task creation, RevMailSeq (real event/sys/revmail.pak through the file stand-in), the y_lmap task, sequence 4
// =====================================================================================================================
TEST_CASE("game(social_map): task creators and updates on the snapshot (heap and file stand-ins)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m)) {
        MESSAGE("SKIP: no replay snapshot under extracted/_ours");
        return;
    }
    const Opt si{{}, {}, true};
    // comuTimerProcess for every kind (the day rules of sub_17E050), then its destroy callback on the work it made
    for (u32 kind = 0; kind <= 9; ++kind) {
        w16(m, kDaysSinceApr5, static_cast<u16>(20 + kind * 30));
        const hgp::Run r = sm_pair(m, "comu_CreateComuTimerProcessTask", {0, kind, 0, 0}, 8000 + kind, "comu_CreateComuTimerProcessTask", si);
        if (!r.stopped && v0_of(r) != 0) sm_pair(m, "sub_3C1A70", {v0_of(r), 0, 0, 0}, 8100 + kind, "sub_3C1A70", si);
    }
    // RevMailSeq: create, then step its update through the phases (each step a pair; the file stand-in loads the PAK)
    const hgp::Run c = sm_pair(m, "comu_CreateRevMailSeqTask", {0, 7, 0, 0}, 8200, "comu_CreateRevMailSeqTask", si);
    if (!c.stopped && v0_of(c) != 0) {
        const u32 task = static_cast<u32>(v0_of(c));
        for (u32 phase = 0; phase < 22; ++phase) {
            const u32 work = r32(m, task + 0x3C);
            if (work == 0) break;
            w32(m, work, phase);
            sm_pair(m, "comu_UpdateRevMailSeqTask", {sx(task), 0, 0, 0}, 8300 + phase, "comu_UpdateRevMailSeqTask", si);
        }
        sm_pair(m, "sub_3C22F0", {sx(task), 0, 0, 0}, 8400, "sub_3C22F0", si);
    }
    // sequence 4: create the y_lmap task from a 5-byte parameter, step its update, poll and destroy it
    const u8 param[5] = {1, 2, 3, 0, 1};
    std::memcpy(m.at(kOut + 0x400), param, 5);
    const hgp::Run s4 = sm_pair(m, "sub_4241E0", {0, sx(kOut + 0x400), 0, 0}, 8500, "sub_4241E0", si);
    sm_pair(m, "sub_4242B0", {0, 0, 0, 0}, 8501, "sub_4242B0", si);
    if (!s4.stopped) {
        const u32 slot = r32(m, 0x7CE6A4u);  // sub_421760's slot (gp-0x464C)
        if (slot != 0 && r32(m, slot + 0x3C) != 0) {
            const u32 work = r32(m, slot + 0x3C);
            for (u32 phase = 0; phase <= 15; ++phase) {
                w32(m, work, phase);
                sm_pair(m, "Y_LMap_UpdateLmapTask", {sx(slot), 0, 0, 0}, 8600 + phase, "Y_LMap_UpdateLmapTask", si);
            }
            sm_pair(m, "sub_421D70", {sx(slot), 0, 0, 0}, 8700, "sub_421D70", si);
        }
    }
    sm_pair(m, "sub_424230", {0, 0, 0, 0}, 8701, "sub_424230", si);
    sm_pair(m, "sub_421F20", {0, 0, 0, 0}, 8702, "sub_421F20", si);
    sm_pair(m, "sub_421FB0", {0, 0, 0, 0}, 8703, "sub_421FB0", si);
    // the other creators (boxfill / menu / model / move / tmx), each with a fresh parent of 0
    for (const char* n : {"Y_LMap_CreateBoxfillTasks", "Y_LMap_CreateLMapMenuTask", "Y_LMap_CreateLmapModelTask",
                          "Y_LMap_CreateLmapModelMoveTask", "Y_LMap_CreateTmxDispTask", "sub_427830", "sub_427A10", "sub_427BF0"})
        for (u32 k = 0; k < 3; ++k) {
            const hgp::Run r = sm_pair(m, n, {0, k, k + 1, 2}, 8800 + k, n, Opt{{{GPR_T0, 1}, {GPR_T1, 2}}, {}, true});
            (void)r;
        }
}

// =====================================================================================================================
// comuData.c's tables: the ELF's static data (documented rules)
// =====================================================================================================================
TEST_CASE("game(social_map): comu text tables (documented rules)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const bool snap = load_snapshot(m);  // the social-link state for sub_16DCE0 (the ELF's .bss otherwise)
    for (u32 i = 0; i < 64; ++i) {
        const u64 arg = i < 48 ? i : 0x100u + i;  // `andi 0xFF`: 0x13F is 0x3F
        const hgp::Run r = sm_pair(m, "sub_3C3F40", {arg, 0, 0, 0}, 9000 + i, "sub_3C3F40");
        const u32 idx = static_cast<u32>(arg & 0xFF);
        CHECK(v0_of(r) == (idx < 42 ? sx(r32(m, game::kComuPlaceNames + 4 * idx)) : 0u));
    }
    CHECK(guest_str(m, r32(m, game::kComuPlaceNames)) == "Club");
    for (u32 link = 0; link < game::kComuNumLinks; ++link) {
        const hgp::Run k = sm_pair(m, "sub_3C40F0", {link, 0, 0, 0}, 9100 + link, "sub_3C40F0");
        CHECK(v0_of(k) == sx(static_cast<u32>(static_cast<s32>(static_cast<s8>(r8(m, game::kComuSasoiKinds + 4 * link))))));
        const hgp::Run g = sm_pair(m, "sub_3C4110", {link, 0, 0, 0}, 9200 + link, "sub_3C4110");
        CHECK(v0_of(g) == r16(m, game::kComuSasoiKinds + 4 * link + 2));
        const hgp::Run t = sm_pair(m, "sub_3C3F80", {link, 0, 0, 0}, 9300 + link, "sub_3C3F80");
        CHECK((v0_of(t) == 0 || v0_of(t) == sx(r32(m, game::kComuLinkTitles + 4 * link))));
        const hgp::Run p = sm_pair(m, "sub_3C3FE0", {link, 0, 0, 0}, 9400 + link, "sub_3C3FE0");
        CHECK((v0_of(p) == 0 || v0_of(p) == sx(r32(m, game::kComuPartnerNames + 4 * link))));
        sm_pair(m, "sub_3C4040", {link, (link * 7) % 30, 0, 0}, 9500 + link, "sub_3C4040");
    }
    // the invitation kinds: 2 for the links that invite, 0 for the rest (the ELF's table)
    for (u32 link : {1u, 4u, 6u, 14u, 17u, 19u, 23u, 27u}) CHECK(static_cast<s8>(r8(m, game::kComuSasoiKinds + 4 * link)) == 2);
    for (u32 link : {0u, 2u, 3u, 5u, 15u, 16u, 20u, 29u}) CHECK(static_cast<s8>(r8(m, game::kComuSasoiKinds + 4 * link)) == 0);
    CHECK(guest_str(m, r32(m, game::kComuPartnerNames + 4)) == "Kenji");
    CHECK(guest_str(m, r32(m, game::kComuLinkTitles + 4)) == "Classmate");
    for (u32 i = 0; i <= 23; ++i) {
        const hgp::Run r = sm_pair(m, "sub_3C4390", {i, 0, 0, 0}, 9600 + i, "sub_3C4390");
        if (i >= 1 && i <= 22) CHECK(v0_of(r) == sx(r32(m, game::kComuUltimatePersonas + 4 * (i - 1))));
        if (i == 1) CHECK(guest_str(m, static_cast<u32>(v0_of(r))) == "Susano-o");
        if (i == 22) CHECK(guest_str(m, static_cast<u32>(v0_of(r))) == "Metatron");
    }
    for (u32 i = 0; i < 7; ++i) {
        const hgp::Run r = sm_pair(m, "sub_3C4210", {i, 0, 0, 0}, 9700 + i, "sub_3C4210");
        if (i < 6) CHECK(v0_of(r) == sx(r32(m, game::kComuGiftTexts + 4 * i)));
    }
    // the day limit byte per link: 30 for every link (the threshold of flag 0xA2D in sub_3C33C0)
    for (u32 link = 0; link < game::kComuNumLinks; ++link) CHECK(static_cast<s8>(r8(m, game::kComuDayLimits + link)) == 30);
    for (const char* n : {"sub_3C1430", "sub_3C2770", "sub_3C43F0", "sub_3C4400", "sub_3C4410", "sub_3C4420"}) sm_pair(m, n, {0, 0, 0, 0}, 9800, n);
    CHECK(v0_of(sm_pair(m, "sub_3C1430", {0, 0, 0, 0}, 9801, "sub_3C1430")) == sx(game::kComuPending));
    CHECK(v0_of(sm_pair(m, "sub_3C2770", {0, 0, 0, 0}, 9802, "sub_3C2770")) == sx(game::kComuSasoiList));
    if (!snap) MESSAGE("note: no snapshot; sub_3C3F80 / sub_3C3FE0 ran on the ELF's social-link state");
}

// =====================================================================================================================
// The area map: the easing curves, the alignment, the path matrix, the record setters (documented rules)
// =====================================================================================================================
TEST_CASE("game(social_map): area-map curves, path matrix and record setters (documented rules)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0x5A5A};
    // sub_421FE0 (s16 ends, s8 kind): kind 0 is from + (to - from) * frame / len in integer math; frame == len gives
    // the end; kind 1 / 2 start at `from`; other kinds give -1.0
    for (int i = 0; i < 160; ++i) {
        const s32 kind = i % 5 == 4 ? 3 + static_cast<s32>(rng() % 4) : i % 3;
        const s32 from = static_cast<s32>(rng() % 601) - 300, to = static_cast<s32>(rng() % 601) - 300;
        const s32 len = 1 + static_cast<s32>(rng() % 60);
        const s32 frame = i % 7 == 0 ? len : (i % 11 == 0 ? 0 : static_cast<s32>(rng() % static_cast<u32>(len)));
        const hgp::Run r = sm_pair(m, "sub_421FE0", {sx(static_cast<u32>(kind)), sx(static_cast<u32>(from)), sx(static_cast<u32>(to)),
                                                     sx(static_cast<u32>(frame))},
                                   10000 + i, "sub_421FE0", Opt{{{GPR_T0, sx(static_cast<u32>(len))}}, {}, false});
        const float f = fval(f0_of(r));
        INFO("kind " << kind << " " << from << " -> " << to << " frame " << frame << "/" << len);
        if (frame == len) CHECK(f == static_cast<float>(to));
        else if (kind == 0) CHECK(f == static_cast<float>(from + (to - from) * frame / len));
        else if (kind > 2) CHECK(f == -1.0f);
        else if (frame == 0 && kind == 1) CHECK(f == static_cast<float>(from));
    }
    // sub_4221A0: the float version ($f12 from, $f13 to, $f14 frame, $f15 length)
    for (int i = 0; i < 120; ++i) {
        const s32 kind = i % 4;
        const float from = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 8.0f;
        const float to = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 8.0f;
        const float len = static_cast<float>(1 + rng() % 30);
        const float frame = i % 9 == 0 ? len : static_cast<float>(rng() % static_cast<u32>(len));
        const hgp::Run r = sm_pair(m, "sub_4221A0", {sx(static_cast<u32>(kind)), 0, 0, 0}, 10500 + i, "sub_4221A0",
                                   Opt{{}, {{12, fbits(from)}, {13, fbits(to)}, {14, fbits(frame)}, {15, fbits(len)}}, false});
        const float f = fval(f0_of(r));
        if (frame == len) CHECK(f == to);
        else if (kind == 3) CHECK(f == -1.0f);
        else if (kind == 0) CHECK(std::fabs(f - (from + (to - from) * frame / len)) <= 1e-3f * (1.0f + std::fabs(to) + std::fabs(from)));
    }
    // sub_4222D0: two curves into a float pair at $a0 ($a1 kind, x $a2 -> $a3, y $t0 -> $t1, frame $t2 of $t3)
    for (int i = 0; i < 80; ++i) {
        const u32 kind = i % 4;
        const s32 x0 = static_cast<s32>(rng() % 641), x1 = static_cast<s32>(rng() % 641);
        const s32 y0 = static_cast<s32>(rng() % 449), y1 = static_cast<s32>(rng() % 449);
        const s32 len = 1 + static_cast<s32>(rng() % 30);
        const s32 frame = i % 5 == 0 ? len : static_cast<s32>(rng() % static_cast<u32>(len));
        const hgp::Run r = sm_pair(m, "sub_4222D0", {sx(kOut), kind, sx(static_cast<u32>(x0)), sx(static_cast<u32>(x1))}, 11000 + i, "sub_4222D0",
                                   Opt{{{GPR_T0, sx(static_cast<u32>(y0))}, {GPR_T1, sx(static_cast<u32>(y1))}, {GPR_T2, sx(static_cast<u32>(frame))},
                                        {GPR_T3, sx(static_cast<u32>(len))}},
                                       {}, false});
        if (r.stopped) continue;
        if (frame == len) {
            CHECK(fval(r32(m, kOut)) == static_cast<float>(x1));
            CHECK(fval(r32(m, kOut + 4)) == static_cast<float>(y1));
        } else if (kind == 0) {
            CHECK(fval(r32(m, kOut)) == static_cast<float>(x0 + (x1 - x0) * frame / len));
            CHECK(fval(r32(m, kOut + 4)) == static_cast<float>(y0 + (y1 - y0) * frame / len));
        }
    }
    // sub_423FE0 mode 0: the centre (w / 2, h / 2), C division toward zero
    for (int i = 0; i < 60; ++i) {
        const u32 mode = i % 4;
        const s32 w = static_cast<s32>(rng() % 1201) - 600, h = static_cast<s32>(rng() % 901) - 450;
        const s32 x = static_cast<s32>(rng() % 641), y = static_cast<s32>(rng() % 449);
        const hgp::Run r = sm_pair(m, "sub_423FE0", {sx(kOut), mode, sx(static_cast<u32>(w)), sx(static_cast<u32>(h))}, 11500 + i, "sub_423FE0",
                                   Opt{{{GPR_T0, sx(static_cast<u32>(x))}, {GPR_T1, sx(static_cast<u32>(y))}}, {}, false});
        if (!r.stopped && mode == 0) {
            CHECK(fval(r32(m, kOut)) == static_cast<float>(w / 2));
            CHECK(fval(r32(m, kOut + 4)) == static_cast<float>(h / 2));
        }
    }
    // sub_425D50: the path from area a to area b -- 0 on the diagonal and out of range, 1..5 between two areas
    for (s32 a = -1; a <= 6; ++a)
        for (s32 b = -1; b <= 6; ++b) {
            const hgp::Run r = sm_pair(m, "sub_425D50", {sx(static_cast<u32>(a)), sx(static_cast<u32>(b)), 0, 0},
                                       12000 + static_cast<u32>((a + 1) * 8 + b + 1), "sub_425D50");
            const u64 v = v0_of(r);
            INFO("path " << a << " -> " << b);
            CHECK(v <= 5);
            if (a < 0 || b < 0 || a > 5 || b > 5 || a == b) CHECK(v == 0);
            else CHECK(v != 0);
        }
    // the record setters on a task whose +0x3C is the record
    std::memset(m.at(kTask), 0, 0x40);
    w32(m, kTask + 0x3C, kRec);
    std::memset(m.at(kRec), 0, 0x200);
    for (int i = 0; i < 24; ++i) {
        const s32 alpha = static_cast<s32>(rng() % 512) - 128;
        sm_pair(m, "sub_422C10", {sx(kTask), sx(static_cast<u32>(alpha)), 0, 0}, 12500 + i, "sub_422C10");
        CHECK(fval(r32(m, kRec + game::kBoxAlpha)) == static_cast<float>(alpha));
        const u32 c4[4] = {rng() & 0xFF, rng() & 0xFF, rng() & 0xFF, rng() & 0xFF};
        sm_pair(m, "sub_422C90", {sx(kTask), c4[0], c4[1], c4[2]}, 12600 + i, "sub_422C90", Opt{{{GPR_T0, c4[3]}}, {}, false});
        for (u32 k = 0; k < 4; ++k)
            for (u32 ch = 0; ch < 4; ++ch) CHECK(r8(m, kRec + game::kBoxColors + 4 * k + ch) == c4[ch]);
        sm_pair(m, "sub_427DE0", {sx(kTask), c4[3], c4[2], c4[1]}, 12700 + i, "sub_427DE0", Opt{{{GPR_T0, c4[0]}}, {}, false});
        for (u32 k = 0; k < 4; ++k) CHECK(r8(m, kRec + game::kBoxColors + 4 * k) == c4[3]);
        const float sw = static_cast<float>(rng() % 640), sh = static_cast<float>(rng() % 448);
        sm_pair(m, "sub_427E20", {sx(kTask), 0, 0, 0}, 12800 + i, "sub_427E20", Opt{{}, {{12, fbits(sw)}, {13, fbits(sh)}}, false});
        CHECK(r32(m, kRec + game::kBoxSize) == static_cast<u32>(sw));
        CHECK(r32(m, kRec + game::kBoxSize + 4) == static_cast<u32>(sh));
        const u32 v = rng() & 0xFF;
        sm_pair(m, "sub_422CD0", {sx(kTask), v, 0, 0}, 12900 + i, "sub_422CD0");
        CHECK(r8(m, kRec + 318) == v);
        sm_pair(m, "sub_427E50", {sx(kTask), v, 0, 0}, 13000 + i, "sub_427E50");
        CHECK(r8(m, kRec + 336) == v);
        sm_pair(m, "sub_427E60", {sx(kTask), v, 0, 0}, 13100 + i, "sub_427E60");
        CHECK(r8(m, kRec + 396) == v);
        w32(m, kOut, fbits(sw));
        w32(m, kOut + 4, fbits(sh));
        sm_pair(m, "sub_427DB0", {sx(kTask), (static_cast<u64>(fbits(sh)) << 32) | fbits(sw), 0, 0}, 13200 + i, "sub_427DB0");
        CHECK(r32(m, kRec + game::kBoxPos) == fbits(sw));
        CHECK(r32(m, kRec + game::kBoxPos + 4) == fbits(sh));
        sm_pair(m, "sub_422C30", {sx(kTask), (static_cast<u64>(fbits(sh)) << 32) | fbits(sw), sx(kOut), 0}, 13300 + i, "sub_422C30");
        CHECK(r32(m, kRec + game::kBoxPos) == fbits(sw));
        // the model / menu bytes
        sm_pair(m, "sub_425D10", {sx(kTask), v, 0, 0}, 13400 + i, "sub_425D10");
        CHECK(r8(m, kRec + 1) == v);
        CHECK(r8(m, kRec + 0) == 1);
        sm_pair(m, "sub_425D30", {sx(kTask), v, v ^ 0x55, 0}, 13500 + i, "sub_425D30");
        CHECK(r8(m, kRec + 2) == (v ^ 0x55));
        CHECK(r8(m, game::kLmapModelArea) == v);
        sm_pair(m, "sub_426040", {sx(kTask), v, 0, 0}, 13600 + i, "sub_426040");
        CHECK(r8(m, kRec + 3) == v);
        sm_pair(m, "sub_426050", {sx(kTask), 0, 0, 0}, 13700 + i, "sub_426050");
        CHECK(r8(m, kRec + 0) == 3);
        const hgp::Run mv = sm_pair(m, "sub_426070", {sx(kTask), 0, 0, 0}, 13800 + i, "sub_426070");
        CHECK(v0_of(mv) == 1u);  // state 3 != 2
        w32(m, kRec, static_cast<u32>(i % 16));
        const hgp::Run ph = sm_pair(m, "sub_421EF0", {sx(kTask), 0, 0, 0}, 13900 + i, "sub_421EF0");
        CHECK(v0_of(ph) == (i % 16 == 15 ? 1u : 0u));
        sm_pair(m, "sub_421F10", {sx(kTask), 0, 0, 0}, 14000 + i, "sub_421F10");
    }
    // the menu record: entries at +143.., count +142, selection +150, state byte +0
    for (int i = 0; i < 24; ++i) {
        std::memset(m.at(kRec), 0, 0x200);
        const u32 n = 1 + rng() % 6;
        w8(m, kRec + 142, static_cast<u8>(n));
        for (u32 k = 0; k < n; ++k) w8(m, kRec + 143 + k, static_cast<u8>((k * 3 + i) % 7));
        w8(m, kRec + 150, static_cast<u8>(rng() % n));
        w8(m, kRec, static_cast<u8>(rng() % 14));
        // the sprite handles sub_423CD0 writes through (+204 .. +348), apart from the entry positions (+396 / +400)
        std::memset(m.at(kRec + 0x400), 0, 0x40);
        for (u32 k = 0; k < 37; ++k) w32(m, kRec + 204 + 4 * k, kRec + 0x400);
        for (u32 k = 0; k < 6; ++k) {
            w32(m, kRec + 396 + 8 * k, fbits(static_cast<float>(rng() % 640)));
            w32(m, kRec + 400 + 8 * k, fbits(static_cast<float>(rng() % 448)));
        }
        const u8 st = r8(m, kRec);
        const hgp::Run d = sm_pair(m, "sub_423B70", {sx(kTask), 0, 0, 0}, 14100 + i, "sub_423B70");
        CHECK(v0_of(d) == ((st == 6 || st == 12) ? 1u : 0u));
        const hgp::Run o = sm_pair(m, "sub_423BF0", {sx(kTask), 0, 0, 0}, 14200 + i, "sub_423BF0");
        CHECK(v0_of(o) == (st >= 2 ? 1u : 0u));
        const hgp::Run sel = sm_pair(m, "sub_423B50", {sx(kTask), 0, 0, 0}, 14300 + i, "sub_423B50");
        CHECK(v0_of(sel) == sx(static_cast<u32>(static_cast<s32>(static_cast<s8>(r8(m, kRec + 143 + r8(m, kRec + 150)))))));
        const u32 want = (i * 5) % 7;
        sm_pair(m, "sub_423C10", {sx(kTask), want, 0, 0}, 14400 + i, "sub_423C10");
        bool present = false;
        for (u32 k = 0; k < n; ++k) present |= r8(m, kRec + 143 + k) == want;
        if (present) {
            CHECK(r8(m, kRec) == 6);
            CHECK(r8(m, kRec + 143 + r8(m, kRec + 150)) == want);
        }
        sm_pair(m, "sub_423CD0", {sx(kTask), 0, 0, 0}, 14500 + i, "sub_423CD0");
        sm_pair(m, "sub_423FC0", {sx(kTask), 0, 0, 0}, 14600 + i, "sub_423FC0");
        CHECK(r8(m, kRec + 149) == 1);
        sm_pair(m, "sub_423BA0", {sx(kTask), 0, 0, 0}, 14700 + i, "sub_423BA0");
        CHECK(r8(m, kRec) == 10);
    }
}

TEST_CASE("game(social_map): pair count") { MESSAGE("social_map pairs run (outside the random-world case): " << g_pairs); }

#else

TEST_CASE("game(social_map): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
