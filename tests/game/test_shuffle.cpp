// Phase 5 pair tests for slice shuffle (game/src/battle/shuffle.cpp): every Shuffle Time body against its recompiled
// body (__recomp) on identical guest machines. Shuffle Time is on no replay route (no snapshot has a "shuffle root"
// task), so these tests carry the slice:
//   * structured shuffle worlds (game/include/p3fes/game/shuffle.h has the layouts): the card work (gp-18844) with its
//     16 card records -- a well-formed doubly linked deal list of the cards in use, top-level cards numbered 0..n-1 by
//     their order field, stacks with children (flag 0x2, parent +4040), gc_pose objects in every card --, the stack
//     list and the command ring; the shuffle script (gp-18840) with a command stream written by the game's own
//     encoding (sub_259850, re-implemented on the host); the root (gp-18964, the kwln tasks' +60), the result
//     (gp-18960) with its entries and id lists, the cursor, the counter, the persona-select page, the pose manager;
//     every other word random (small values, zeros, pointers back into the world);
//   * each pair compares the whole register file and the cycle count at every check point and at the return or stop,
//     all 32 MiB of RAM (a PairRange: the dead stack, every stray store), the scratchpad, the BIOS window, the bus log
//     (tests/game/handgen_pairs.h's comparison), plus the stand-in call log: printf (the sfli debug lines, the card
//     dump), the heap, the H_Cdvd layer and recorders for the big still-recompiled callees that the test build does
//     not emit (the card model draw, the camera / pose animators, the texture loaders) stand in identically for both
//     bodies, so the runs go on past what used to be a missing-function stop;
//   * the replay snapshots battle_ref_6150 / b_5800 / dorm_replay_4900 (the shuffle records are absent there: the
//     K_Assert paths, and the real game counters 56 / 57 read by sub_1F56B0 / sub_25B440);
//   * documented-rule checks on the host: the script encoding, the deal-list queries, the stack children, the result
//     entries, card creation and the shuffle counters.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/shuffle.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_sub_1F30B0_001f30b0)
P3FES_DECL_PAIR(fn_sub_1F30D0_001f30d0)
P3FES_DECL_PAIR(fn_sub_1F4650_001f4650)
P3FES_DECL_PAIR(fn_sub_1F4910_001f4910)
P3FES_DECL_PAIR(fn_sub_1F4970_001f4970)
P3FES_DECL_PAIR(fn_sub_1F4990_001f4990)
P3FES_DECL_PAIR(fn_sub_1F48D0_001f48d0)
P3FES_DECL_PAIR(fn_sub_1F4930_001f4930)
P3FES_DECL_PAIR(fn_sub_1F5510_001f5510)
P3FES_DECL_PAIR(fn_sub_1F5650_001f5650)
P3FES_DECL_PAIR(fn_sub_1F56B0_001f56b0)
P3FES_DECL_PAIR(fn_sub_1F5760_001f5760)
P3FES_DECL_PAIR(fn_sub_1F58F0_001f58f0)
P3FES_DECL_PAIR(fn_sub_1F65E0_001f65e0)
P3FES_DECL_PAIR(fn_sub_1F6D20_001f6d20)
P3FES_DECL_PAIR(fn_sub_1F9630_001f9630)
P3FES_DECL_PAIR(fn_sub_1F9680_001f9680)
P3FES_DECL_PAIR(fn_sub_1F9770_001f9770)
P3FES_DECL_PAIR(fn_sub_1F9800_001f9800)
P3FES_DECL_PAIR(fn_sub_1F9890_001f9890)
P3FES_DECL_PAIR(fn_sub_24DA60_0024da60)
P3FES_DECL_PAIR(fn_sub_24DAF0_0024daf0)
P3FES_DECL_PAIR(fn_sub_24F960_0024f960)
P3FES_DECL_PAIR(fn_sub_24F9F0_0024f9f0)
P3FES_DECL_PAIR(fn_sub_24FAF0_0024faf0)
P3FES_DECL_PAIR(fn_sub_24FDA0_0024fda0)
P3FES_DECL_PAIR(fn_sub_24FE00_0024fe00)
P3FES_DECL_PAIR(fn_sub_2534D0_002534d0)
P3FES_DECL_PAIR(fn_sub_253560_00253560)
P3FES_DECL_PAIR(fn_sub_253600_00253600)
P3FES_DECL_PAIR(fn_sub_2536B0_002536b0)
P3FES_DECL_PAIR(fn_sub_2537F0_002537f0)
P3FES_DECL_PAIR(fn_sub_253920_00253920)
P3FES_DECL_PAIR(fn_sub_254B90_00254b90)
P3FES_DECL_PAIR(fn_sub_254E10_00254e10)
P3FES_DECL_PAIR(fn_sub_254F20_00254f20)
P3FES_DECL_PAIR(fn_sub_254F70_00254f70)
P3FES_DECL_PAIR(fn_sub_2550B0_002550b0)
P3FES_DECL_PAIR(fn_sub_255130_00255130)
P3FES_DECL_PAIR(fn_sub_255170_00255170)
P3FES_DECL_PAIR(fn_sub_255190_00255190)
P3FES_DECL_PAIR(fn_sub_2551B0_002551b0)
P3FES_DECL_PAIR(fn_sub_2551D0_002551d0)
P3FES_DECL_PAIR(fn_sub_255390_00255390)
P3FES_DECL_PAIR(fn_sub_255440_00255440)
P3FES_DECL_PAIR(fn_sub_2554F0_002554f0)
P3FES_DECL_PAIR(fn_sub_255570_00255570)
P3FES_DECL_PAIR(fn_sub_255810_00255810)
P3FES_DECL_PAIR(fn_sub_255F30_00255f30)
P3FES_DECL_PAIR(fn_sub_255F80_00255f80)
P3FES_DECL_PAIR(fn_sub_255FE0_00255fe0)
P3FES_DECL_PAIR(fn_sub_256030_00256030)
P3FES_DECL_PAIR(fn_sub_256110_00256110)
P3FES_DECL_PAIR(fn_sub_2561C0_002561c0)
P3FES_DECL_PAIR(fn_sub_2561D0_002561d0)
P3FES_DECL_PAIR(fn_sub_2561E0_002561e0)
P3FES_DECL_PAIR(fn_sub_256430_00256430)
P3FES_DECL_PAIR(fn_sub_256F20_00256f20)
P3FES_DECL_PAIR(fn_sub_256FA0_00256fa0)
P3FES_DECL_PAIR(fn_sub_257D00_00257d00)
P3FES_DECL_PAIR(fn_sub_257D90_00257d90)
P3FES_DECL_PAIR(fn_sub_257E20_00257e20)
P3FES_DECL_PAIR(fn_sub_257F10_00257f10)
P3FES_DECL_PAIR(fn_sub_258090_00258090)
P3FES_DECL_PAIR(fn_sub_2580E0_002580e0)
P3FES_DECL_PAIR(fn_sub_258140_00258140)
P3FES_DECL_PAIR(fn_sub_2582B0_002582b0)
P3FES_DECL_PAIR(fn_sub_258300_00258300)
P3FES_DECL_PAIR(fn_sub_258490_00258490)
P3FES_DECL_PAIR(fn_sub_2584E0_002584e0)
P3FES_DECL_PAIR(fn_sub_258540_00258540)
P3FES_DECL_PAIR(fn_sub_258A50_00258a50)
P3FES_DECL_PAIR(fn_sub_258AF0_00258af0)
P3FES_DECL_PAIR(fn_sub_258F80_00258f80)
P3FES_DECL_PAIR(fn_sub_259190_00259190)
P3FES_DECL_PAIR(fn_sub_259250_00259250)
P3FES_DECL_PAIR(fn_sub_2592C0_002592c0)
P3FES_DECL_PAIR(fn_sub_259310_00259310)
P3FES_DECL_PAIR(fn_sub_259380_00259380)
P3FES_DECL_PAIR(fn_sub_2593D0_002593d0)
P3FES_DECL_PAIR(fn_sub_2594C0_002594c0)
P3FES_DECL_PAIR(fn_sub_2595C0_002595c0)
P3FES_DECL_PAIR(fn_sub_259610_00259610)
P3FES_DECL_PAIR(fn_sub_259630_00259630)
P3FES_DECL_PAIR(fn_sub_259640_00259640)
P3FES_DECL_PAIR(fn_sub_259690_00259690)
P3FES_DECL_PAIR(fn_sub_2596F0_002596f0)
P3FES_DECL_PAIR(fn_sub_259740_00259740)
P3FES_DECL_PAIR(fn_sub_259850_00259850)
P3FES_DECL_PAIR(fn_sub_259970_00259970)
P3FES_DECL_PAIR(fn_sub_2599C0_002599c0)
P3FES_DECL_PAIR(fn_sub_259A60_00259a60)
P3FES_DECL_PAIR(fn_sub_259B00_00259b00)
P3FES_DECL_PAIR(fn_sub_259B60_00259b60)
P3FES_DECL_PAIR(fn_sub_259BC0_00259bc0)
P3FES_DECL_PAIR(fn_sub_259C10_00259c10)
P3FES_DECL_PAIR(fn_sub_259C60_00259c60)
P3FES_DECL_PAIR(fn_sub_259CC0_00259cc0)
P3FES_DECL_PAIR(fn_sub_259D10_00259d10)
P3FES_DECL_PAIR(fn_sub_259D80_00259d80)
P3FES_DECL_PAIR(fn_sub_259E00_00259e00)
P3FES_DECL_PAIR(fn_sub_259E60_00259e60)
P3FES_DECL_PAIR(fn_sub_259EA0_00259ea0)
P3FES_DECL_PAIR(fn_sub_259ED0_00259ed0)
P3FES_DECL_PAIR(fn_sub_259F40_00259f40)
P3FES_DECL_PAIR(fn_sub_259FC0_00259fc0)
P3FES_DECL_PAIR(fn_sub_25A030_0025a030)
P3FES_DECL_PAIR(fn_sub_25AA70_0025aa70)
P3FES_DECL_PAIR(fn_sub_25B300_0025b300)
P3FES_DECL_PAIR(fn_sub_25B3B0_0025b3b0)
P3FES_DECL_PAIR(fn_sub_25B440_0025b440)
P3FES_DECL_PAIR(fn_sub_25B4A0_0025b4a0)
P3FES_DECL_PAIR(fn_sub_25B4B0_0025b4b0)
P3FES_DECL_PAIR(fn_sub_25B4F0_0025b4f0)
P3FES_DECL_PAIR(fn_sub_25B5F0_0025b5f0)
P3FES_DECL_PAIR(fn_sub_25B640_0025b640)
P3FES_DECL_PAIR(fn_sub_260A10_00260a10)
P3FES_DECL_PAIR(fn_sub_260BD0_00260bd0)
P3FES_DECL_PAIR(fn_sub_260C20_00260c20)
P3FES_DECL_PAIR(fn_sub_260C70_00260c70)
P3FES_DECL_PAIR(fn_sub_260CD0_00260cd0)
#undef P3FES_DECL_PAIR
void fn_sub_16F380_0016f380(EEContext&);  // the game counters (getter), read by the counter rule
void fn_sub_16F3E0_0016f3e0(EEContext&);  // (setter)
}  // namespace p3fes::recomp_gen

namespace {

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;  // per argument $a0..$a3 (mktest.py / the table below)
};
const Case kCases[] = {
    {"sub_1F30B0", 0x1F30B0, PAIR(fn_sub_1F30B0_001f30b0), "t"},
    {"sub_1F30D0", 0x1F30D0, PAIR(fn_sub_1F30D0_001f30d0), "t"},
    {"sub_1F4650", 0x1F4650, PAIR(fn_sub_1F4650_001f4650), "tp"},
    {"sub_1F4910", 0x1F4910, PAIR(fn_sub_1F4910_001f4910), "t"},
    {"sub_1F4970", 0x1F4970, PAIR(fn_sub_1F4970_001f4970), "t"},
    {"sub_1F4990", 0x1F4990, PAIR(fn_sub_1F4990_001f4990), ""},
    {"sub_1F48D0", 0x1F48D0, PAIR(fn_sub_1F48D0_001f48d0), "t"},
    {"sub_1F4930", 0x1F4930, PAIR(fn_sub_1F4930_001f4930), "t"},
    {"sub_1F5510", 0x1F5510, PAIR(fn_sub_1F5510_001f5510), ""},
    {"sub_1F5650", 0x1F5650, PAIR(fn_sub_1F5650_001f5650), ""},
    {"sub_1F56B0", 0x1F56B0, PAIR(fn_sub_1F56B0_001f56b0), ""},
    {"sub_1F5760", 0x1F5760, PAIR(fn_sub_1F5760_001f5760), "o"},
    {"sub_1F58F0", 0x1F58F0, PAIR(fn_sub_1F58F0_001f58f0), "R"},
    {"sub_1F65E0", 0x1F65E0, PAIR(fn_sub_1F65E0_001f65e0), ""},
    {"sub_1F6D20", 0x1F6D20, PAIR(fn_sub_1F6D20_001f6d20), "p"},
    {"sub_1F9630", 0x1F9630, PAIR(fn_sub_1F9630_001f9630), ""},
    {"sub_1F9680", 0x1F9680, PAIR(fn_sub_1F9680_001f9680), "p"},
    {"sub_1F9770", 0x1F9770, PAIR(fn_sub_1F9770_001f9770), "pp"},
    {"sub_1F9800", 0x1F9800, PAIR(fn_sub_1F9800_001f9800), "pp"},
    {"sub_1F9890", 0x1F9890, PAIR(fn_sub_1F9890_001f9890), ""},
    {"sub_24DA60", 0x24DA60, PAIR(fn_sub_24DA60_0024da60), "q"},
    {"sub_24DAF0", 0x24DAF0, PAIR(fn_sub_24DAF0_0024daf0), "q"},
    {"sub_24F960", 0x24F960, PAIR(fn_sub_24F960_0024f960), "qp"},
    {"sub_24F9F0", 0x24F9F0, PAIR(fn_sub_24F9F0_0024f9f0), "qp"},
    {"sub_24FAF0", 0x24FAF0, PAIR(fn_sub_24FAF0_0024faf0), "qp"},
    {"sub_24FDA0", 0x24FDA0, PAIR(fn_sub_24FDA0_0024fda0), "q"},
    {"sub_24FE00", 0x24FE00, PAIR(fn_sub_24FE00_0024fe00), "q"},
    {"sub_2534D0", 0x2534D0, PAIR(fn_sub_2534D0_002534d0), "C"},
    {"sub_253560", 0x253560, PAIR(fn_sub_253560_00253560), ""},
    {"sub_253600", 0x253600, PAIR(fn_sub_253600_00253600), "c"},
    {"sub_2536B0", 0x2536B0, PAIR(fn_sub_2536B0_002536b0), "oo"},
    {"sub_2537F0", 0x2537F0, PAIR(fn_sub_2537F0_002537f0), "o"},
    {"sub_253920", 0x253920, PAIR(fn_sub_253920_00253920), ""},
    {"sub_254B90", 0x254B90, PAIR(fn_sub_254B90_00254b90), ""},
    {"sub_254E10", 0x254E10, PAIR(fn_sub_254E10_00254e10), ""},
    {"sub_254F20", 0x254F20, PAIR(fn_sub_254F20_00254f20), ""},
    {"sub_254F70", 0x254F70, PAIR(fn_sub_254F70_00254f70), ""},
    {"sub_2550B0", 0x2550B0, PAIR(fn_sub_2550B0_002550b0), ""},
    {"sub_255130", 0x255130, PAIR(fn_sub_255130_00255130), ""},
    {"sub_255170", 0x255170, PAIR(fn_sub_255170_00255170), "c"},
    {"sub_255190", 0x255190, PAIR(fn_sub_255190_00255190), "c"},
    {"sub_2551B0", 0x2551B0, PAIR(fn_sub_2551B0_002551b0), "c"},
    {"sub_2551D0", 0x2551D0, PAIR(fn_sub_2551D0_002551d0), "oo"},
    {"sub_255390", 0x255390, PAIR(fn_sub_255390_00255390), ""},
    {"sub_255440", 0x255440, PAIR(fn_sub_255440_00255440), "o"},
    {"sub_2554F0", 0x2554F0, PAIR(fn_sub_2554F0_002554f0), ""},
    {"sub_255570", 0x255570, PAIR(fn_sub_255570_00255570), "oo"},
    {"sub_255810", 0x255810, PAIR(fn_sub_255810_00255810), "o"},
    {"sub_255F30", 0x255F30, PAIR(fn_sub_255F30_00255f30), ""},
    {"sub_255F80", 0x255F80, PAIR(fn_sub_255F80_00255f80), ""},
    {"sub_255FE0", 0x255FE0, PAIR(fn_sub_255FE0_00255fe0), ""},
    {"sub_256030", 0x256030, PAIR(fn_sub_256030_00256030), ""},
    {"sub_256110", 0x256110, PAIR(fn_sub_256110_00256110), "o"},
    {"sub_2561C0", 0x2561C0, PAIR(fn_sub_2561C0_002561c0), "c"},
    {"sub_2561D0", 0x2561D0, PAIR(fn_sub_2561D0_002561d0), "c"},
    {"sub_2561E0", 0x2561E0, PAIR(fn_sub_2561E0_002561e0), "c"},
    {"sub_256430", 0x256430, PAIR(fn_sub_256430_00256430), ""},
    {"sub_256F20", 0x256F20, PAIR(fn_sub_256F20_00256f20), "cpp"},
    {"sub_256FA0", 0x256FA0, PAIR(fn_sub_256FA0_00256fa0), "cpp"},
    {"sub_257D00", 0x257D00, PAIR(fn_sub_257D00_00257d00), "pooo"},
    {"sub_257D90", 0x257D90, PAIR(fn_sub_257D90_00257d90), "po"},
    {"sub_257E20", 0x257E20, PAIR(fn_sub_257E20_00257e20), ""},
    {"sub_257F10", 0x257F10, PAIR(fn_sub_257F10_00257f10), ""},
    {"sub_258090", 0x258090, PAIR(fn_sub_258090_00258090), ""},
    {"sub_2580E0", 0x2580E0, PAIR(fn_sub_2580E0_002580e0), ""},
    {"sub_258140", 0x258140, PAIR(fn_sub_258140_00258140), ""},
    {"sub_2582B0", 0x2582B0, PAIR(fn_sub_2582B0_002582b0), ""},
    {"sub_258300", 0x258300, PAIR(fn_sub_258300_00258300), ""},
    {"sub_258490", 0x258490, PAIR(fn_sub_258490_00258490), ""},
    {"sub_2584E0", 0x2584E0, PAIR(fn_sub_2584E0_002584e0), "o"},
    {"sub_258540", 0x258540, PAIR(fn_sub_258540_00258540), "op"},
    {"sub_258A50", 0x258A50, PAIR(fn_sub_258A50_00258a50), ""},
    {"sub_258AF0", 0x258AF0, PAIR(fn_sub_258AF0_00258af0), ""},
    {"sub_258F80", 0x258F80, PAIR(fn_sub_258F80_00258f80), "c"},
    {"sub_259190", 0x259190, PAIR(fn_sub_259190_00259190), "cpp"},
    {"sub_259250", 0x259250, PAIR(fn_sub_259250_00259250), ""},
    {"sub_2592C0", 0x2592C0, PAIR(fn_sub_2592C0_002592c0), ""},
    {"sub_259310", 0x259310, PAIR(fn_sub_259310_00259310), ""},
    {"sub_259380", 0x259380, PAIR(fn_sub_259380_00259380), ""},
    {"sub_2593D0", 0x2593D0, PAIR(fn_sub_2593D0_002593d0), ""},
    {"sub_2594C0", 0x2594C0, PAIR(fn_sub_2594C0_002594c0), ""},
    {"sub_2595C0", 0x2595C0, PAIR(fn_sub_2595C0_002595c0), ""},
    {"sub_259610", 0x259610, PAIR(fn_sub_259610_00259610), "S"},
    {"sub_259630", 0x259630, PAIR(fn_sub_259630_00259630), ""},
    {"sub_259640", 0x259640, PAIR(fn_sub_259640_00259640), ""},
    {"sub_259690", 0x259690, PAIR(fn_sub_259690_00259690), "pv"},
    {"sub_2596F0", 0x2596F0, PAIR(fn_sub_2596F0_002596f0), ""},
    {"sub_259740", 0x259740, PAIR(fn_sub_259740_00259740), ""},
    {"sub_259850", 0x259850, PAIR(fn_sub_259850_00259850), "op"},
    {"sub_259970", 0x259970, PAIR(fn_sub_259970_00259970), ""},
    {"sub_2599C0", 0x2599C0, PAIR(fn_sub_2599C0_002599c0), "oo"},
    {"sub_259A60", 0x259A60, PAIR(fn_sub_259A60_00259a60), "oo"},
    {"sub_259B00", 0x259B00, PAIR(fn_sub_259B00_00259b00), "o"},
    {"sub_259B60", 0x259B60, PAIR(fn_sub_259B60_00259b60), "o"},
    {"sub_259BC0", 0x259BC0, PAIR(fn_sub_259BC0_00259bc0), ""},
    {"sub_259C10", 0x259C10, PAIR(fn_sub_259C10_00259c10), ""},
    {"sub_259C60", 0x259C60, PAIR(fn_sub_259C60_00259c60), "o"},
    {"sub_259CC0", 0x259CC0, PAIR(fn_sub_259CC0_00259cc0), ""},
    {"sub_259D10", 0x259D10, PAIR(fn_sub_259D10_00259d10), "p"},
    {"sub_259D80", 0x259D80, PAIR(fn_sub_259D80_00259d80), "p"},
    {"sub_259E00", 0x259E00, PAIR(fn_sub_259E00_00259e00), "p"},
    {"sub_259E60", 0x259E60, PAIR(fn_sub_259E60_00259e60), "p"},
    {"sub_259EA0", 0x259EA0, PAIR(fn_sub_259EA0_00259ea0), "p"},
    {"sub_259ED0", 0x259ED0, PAIR(fn_sub_259ED0_00259ed0), "p"},
    {"sub_259F40", 0x259F40, PAIR(fn_sub_259F40_00259f40), "p"},
    {"sub_259FC0", 0x259FC0, PAIR(fn_sub_259FC0_00259fc0), "p"},
    {"sub_25A030", 0x25A030, PAIR(fn_sub_25A030_0025a030), "p"},
    {"sub_25AA70", 0x25AA70, PAIR(fn_sub_25AA70_0025aa70), ""},
    {"sub_25B300", 0x25B300, PAIR(fn_sub_25B300_0025b300), "o"},
    {"sub_25B3B0", 0x25B3B0, PAIR(fn_sub_25B3B0_0025b3b0), "o"},
    {"sub_25B440", 0x25B440, PAIR(fn_sub_25B440_0025b440), ""},
    {"sub_25B4A0", 0x25B4A0, PAIR(fn_sub_25B4A0_0025b4a0), "K"},
    {"sub_25B4B0", 0x25B4B0, PAIR(fn_sub_25B4B0_0025b4b0), ""},
    {"sub_25B4F0", 0x25B4F0, PAIR(fn_sub_25B4F0_0025b4f0), ""},
    {"sub_25B5F0", 0x25B5F0, PAIR(fn_sub_25B5F0_0025b5f0), ""},
    {"sub_25B640", 0x25B640, PAIR(fn_sub_25B640_0025b640), ""},
    {"sub_260A10", 0x260A10, PAIR(fn_sub_260A10_00260a10), ""},
    {"sub_260BD0", 0x260BD0, PAIR(fn_sub_260BD0_00260bd0), ""},
    {"sub_260C20", 0x260C20, PAIR(fn_sub_260C20_00260c20), ""},
    {"sub_260C70", 0x260C70, PAIR(fn_sub_260C70_00260c70), ""},
    {"sub_260CD0", 0x260CD0, PAIR(fn_sub_260CD0_00260cd0), ""},
};

// --- the shuffle world -------------------------------------------------------------------------------------------
constexpr u32 kGp = 0x7D2CF0u;
constexpr u32 gp(s32 off) { return kGp + static_cast<u32>(off); }
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x30000u;
constexpr u32 kCard = kWorld;                   // sfl_card.c work (0x12890 bytes)
constexpr u32 kRoot = kWorld + 0x13000u;        // sfl_root.c work (reaches +0xC0FC)
constexpr u32 kResult = kWorld + 0x1F400u;      // sfl_result.c work (reaches +0x341C)
constexpr u32 kCursor = kWorld + 0x22C00u;      // sfl_cursor.c work (reaches +0xCA0)
constexpr u32 kScript = kWorld + 0x23A00u;      // sfl_script.c work (24 bytes)
constexpr u32 kScriptBuf = kWorld + 0x23B00u;   // its command buffer
constexpr u32 kScriptBufSize = 0x400u;
constexpr u32 kCount = kWorld + 0x24000u;       // sfl_count.c work (three digit sprites up to +0x4F0)
constexpr u32 kPsel2 = kWorld + 0x24800u;       // sfl_psel2.c work
constexpr u32 kPoseMgr = kWorld + 0x24900u;     // gc_pose.c manager {head, tail}
constexpr u32 kTasks = kWorld + 0x24A00u;       // 4 kwln task records, 0x80 apart (+60 = the root work)
constexpr u32 kParams = kWorld + 0x24C00u;      // argument blocks and out buffers (0x400)
// card records: 16 of 4708 bytes from work +4
constexpr u32 kCardStride = 4708;
constexpr u32 card_of(u32 i) { return kCard + 4 + kCardStride * i; }
constexpr u32 kPoseOffsets[] = {4044, 4144, 4244, 4344, 4456, 4568};
// card work fields (shuffle.h)
constexpr u32 kListHead = 0x1265C, kListTail = 0x12660, kStacks = 0x12664, kCardCount = 0x1267C, kStackCount = 0x12684;
constexpr u32 kCmdCount = 0x127A8, kSelected = 0x127AC, kSpeed = 0x127B0;
constexpr u32 kScriptTable = 0x68EAD0u;  // {fn, u16 argsize} x 9: END SWAP WAIT CLOSE OPEN NOMARK START_ACT SPEED ACTWAIT

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 load16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void storef(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }

struct World {
    u32 n_top = 0;               // top-level cards in the deal list (orders 0..n_top-1)
    std::vector<u32> list;       // the deal list in link order
};

// The script command encoding (sub_259850): u16 op; when the op has arguments, align to 4, the argument bytes; then
// align the write pointer to 2. Returns the new write pointer.
u32 encode_op(Machine& m, u32 wp, u32 op, const u8* args) {
    const u32 size = load16(m, kScriptTable + 8 * op + 4);
    store16(m, wp, static_cast<u16>(op));
    u32 p = wp + 2;
    if (size != 0) {
        if (p & 3) p += 2;
        std::memcpy(m.at(p), args, size);
        p += size;
    }
    if (p & 1) p += 1;
    return p;
}

World shuffle_world(Machine& m, std::mt19937& rng) {
    World w;
    hgp::random_world(m, kWorld, kWorldSize, rng);
    // --- card work: 16 records, the deal list, stacks, poses -------------------------------------------------------
    std::vector<u32> in_use;
    const u32 want = rng() % 12;
    for (u32 i = 0; i < 16; ++i) {
        const u32 c = card_of(i);
        u32 flags = 0;
        for (u32 bit : {0x1u, 0x10u, 0x20u, 0x80u, 0x100u, 0x400u})
            if (chance(rng, 25)) flags |= bit;
        const bool use = in_use.size() < want && chance(rng, 70);
        if (use) flags |= 0x4u;
        store32(m, c + 0, flags);
        store32(m, c + 4, chance(rng, 90) ? rng() % 3 : rng() % 8);  // kind: persona / arcana / blank
        store32(m, c + 8, rng() % 0x60);
        store32(m, c + 12, rng() % 22);
        store32(m, c + 20, i);
        store32(m, c + 4040, 0);
        for (u32 off : kPoseOffsets) {
            const u32 p = c + off;
            store32(m, p + 12, chance(rng, 70) ? 0 : rng() % 3);  // pose type
            store32(m, p + 32, rng() % 5);                        // pose state (< 4 valid)
            for (u32 k = 0; k < 3; ++k) storef(m, p + 20 + 4 * k, hgp::small_float(rng));
        }
        store32(m, c + 4684, rng() % 4);
        store32(m, c + 4688, rng() % 16);
        store32(m, c + 4692, rng() % 16);
        if (use) in_use.push_back(c);
    }
    std::shuffle(in_use.begin(), in_use.end(), rng);
    // children: a card with flag 0x2 hangs under a stack (flag 0x8) and is numbered inside it
    std::vector<u32> tops, children;
    for (u32 c : in_use) (chance(rng, 25) && !tops.empty() ? children : tops).push_back(c);
    std::vector<u32> order(tops.size());
    std::iota(order.begin(), order.end(), 0u);
    std::shuffle(order.begin(), order.end(), rng);
    for (std::size_t k = 0; k < tops.size(); ++k) {
        store32(m, tops[k], load32(m, tops[k]) & ~0x2u);
        store32(m, tops[k] + 16, order[k]);
    }
    std::vector<u32> nchild(tops.size(), 0);
    for (u32 c : children) {
        const std::size_t t = rng() % tops.size();
        store32(m, tops[t], load32(m, tops[t]) | 0x8u);
        store32(m, c, load32(m, c) | 0x2u);
        store32(m, c + 4040, tops[t]);
        store32(m, c + 16, nchild[t]++);
    }
    for (std::size_t k = 0; k < tops.size(); ++k)
        if (nchild[k] == 0 && chance(rng, 85)) store32(m, tops[k], load32(m, tops[k]) & ~0x8u);
    w.list = in_use;
    w.n_top = static_cast<u32>(tops.size());
    for (std::size_t k = 0; k < in_use.size(); ++k) {
        store32(m, in_use[k] + 4032, k == 0 ? 0 : in_use[k - 1]);
        store32(m, in_use[k] + 4036, k + 1 == in_use.size() ? 0 : in_use[k + 1]);
    }
    store32(m, kCard + 0, rng() & 0x3FFFu);
    store32(m, kCard + kListHead, in_use.empty() ? 0 : in_use.front());
    store32(m, kCard + kListTail, in_use.empty() ? 0 : in_use.back());
    const u32 nstack = chance(rng, 90) ? std::min<u32>(w.n_top, rng() % 9) : rng() % 12;
    for (u32 k = 0; k < 8; ++k) store32(m, kCard + kStacks + 4 * k, tops.empty() ? 0 : tops[rng() % tops.size()]);
    store32(m, kCard + kStackCount, nstack);
    store32(m, kCard + kCardCount, chance(rng, 90) ? w.n_top : rng() % 20);
    store32(m, kCard + kCmdCount, rng() % 4);
    store32(m, kCard + kSelected, rng() % (w.n_top + 1));
    store32(m, kCard + kSpeed, rng() % 30);
    // --- the pose manager: an empty list or two of the cards' poses -----------------------------------------------
    store32(m, kPoseMgr, 0);
    store32(m, kPoseMgr + 4, 0);
    if (!in_use.empty() && chance(rng, 60)) {
        const u32 a = in_use[0] + kPoseOffsets[0], b = in_use.back() + kPoseOffsets[2];
        store32(m, kPoseMgr, a);
        store32(m, kPoseMgr + 4, b);
        store32(m, a + 0, b), store32(m, a + 4, 0), store32(m, b + 0, 0), store32(m, b + 4, a);
    }
    // --- the script: a command stream in the game's encoding, ended by END -----------------------------------------
    {
        u32 wp = kScriptBuf;
        const u32 n = rng() % 8;
        for (u32 k = 0; k <= n; ++k) {
            const u32 op = k == n ? 0u : rng() % 9;
            u8 args[4];
            const u16 x = static_cast<u16>(rng() % (w.n_top + 2)), y = static_cast<u16>(rng() % (w.n_top + 2));
            std::memcpy(args, &x, 2);
            std::memcpy(args + 2, &y, 2);
            wp = encode_op(m, wp, op, args);
        }
        store32(m, kScript + 0, (rng() & 0x2u) | (chance(rng, 80) ? 1u : 0u));
        store32(m, kScript + 4, kScriptBuf);
        store32(m, kScript + 8, kScriptBuf);
        store32(m, kScript + 12, wp);
        store32(m, kScript + 16, chance(rng, 90) ? kScriptBufSize : rng() % 0x20);
        store32(m, kScript + 20, rng() % 4);
    }
    // --- root, result, cursor, counter, persona select -------------------------------------------------------------
    store32(m, kRoot + 4, rng() & 0x13FFu);
    store32(m, kRoot + 8, rng() % 32);
    const u32 kinds[] = {468, 469, rng() % 1000};
    store32(m, kRoot + 0x10000 - 16132, kinds[rng() % 3]);
    store32(m, kRoot + 228, rng() % 2);
    for (u32 t = 0; t < 4; ++t) store32(m, kTasks + 0x80 * t + 60, chance(rng, 90) ? kRoot : kWorld + (rng() % kWorldSize & ~3u));
    store32(m, kResult + 0, rng() & 3u);
    store32(m, kResult + 13276, chance(rng, 90) ? rng() % 8 : 8 + rng() % 2);
    for (u32 e = 0; e < 8; ++e) {
        store32(m, kResult + 92 + 1648 * e, rng() % 3);
        store32(m, kResult + 96 + 1648 * e, rng() % 6);
        store32(m, kResult + 100 + 1648 * e, rng() % 6);
    }
    store32(m, kResult + 13312, rng() % 9);
    store32(m, kResult + 13316, rng() % 9);
    store32(m, kResult + 13336, chance(rng, 90) ? rng() % 8 : 8);
    store32(m, kResult + 13340, chance(rng, 90) ? rng() % 8 : 8);
    store32(m, kCursor + 0, rng() & 3u);
    store32(m, kCursor + 48, rng() % (w.n_top + 1));
    store32(m, kCursor + 3232, rng() % 4);
    store32(m, kCount + 0, rng() & 3u);
    store32(m, kPsel2 + 0, rng() & 3u);
    // --- the gp slots (now and then 0: the K_Assert paths) ---------------------------------------------------------
    const std::pair<s32, u32> slots[] = {{-18964, kRoot},   {-18960, kResult}, {-18844, kCard},  {-18840, kScript},
                                         {-18832, kCursor}, {-18828, kCount},  {-18808, kPsel2}, {-18864, kPoseMgr}};
    for (const auto& [off, va] : slots) store32(m, gp(off), chance(rng, 6) ? 0u : va);
    store32(m, gp(-18836), rng() % 2);
    return w;
}

u64 arg_of(char kind, const World& w, std::mt19937& rng) {
    const u32 k = rng() % 100;
    if (k < 8) return hgp::random_arg(rng, kWorld, kWorldSize);  // anything, now and then
    switch (kind) {
    case 'c': return sx(card_of(rng() % 16));
    case 'o': return rng() % (w.n_top + 2);
    case 'p': return sx(kParams + 16 * (rng() % 32));
    case 't': return sx(kTasks + 0x80 * (rng() % 4));
    case 'q': return sx(k < 90 ? card_of(rng() % 16) + kPoseOffsets[rng() % 6] : kCard + (k < 95 ? 0x127D4 : 0x12800));
    case 'v': return k < 60 ? kScriptBufSize : rng() % 0x800;
    case 'C': return sx(kCard);
    case 'R': return sx(kResult);
    case 'S': return sx(kScript);
    case 'K': return sx(kCount);
    default: return rng() % 16;
    }
}
Args args_for(const Case& c, const World& w, std::mt19937& rng) {
    Args a{};
    for (unsigned i = 0; i < 4; ++i) a[i] = arg_of(c.kinds[0] && std::strlen(c.kinds) > i ? c.kinds[i] : 'n', w, rng);
    return a;
}

// --- the pair, with stand-ins ----------------------------------------------------------------------------------------
// The callees the test build does not emit and the shuffle bodies reach, served by recorders (both bodies meet the
// same recorder; its log is compared): the ground / card-model / texture loaders and drawers, the pose and camera
// animators, the screen-projection helpers, the persona stock.
constexpr u32 kRecorded[] = {0x20E2C0, 0x23C280, 0x258630, 0x255B20, 0x257130, 0x25AAD0, 0x250CF0, 0x24F090, 0x21A920,
                             0x21AB80, 0x21A670, 0x21A760, 0x20B250, 0x20C400, 0x20C500, 0x174B40, 0x34FCF0};
void shuffle_setup(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "rec_" + hex64(va), 0, 4);
}

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

// hgp::pair (whole register file at every check point, the end / stop, all RAM, scratchpad, BIOS, bus) with a fresh
// stand-in world around each body, and the two call logs compared. Returns the recompiled run.
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    shuffle_setup(*wh);
    shuffle_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

}  // namespace

TEST_CASE("game(shuffle): every body equals its recompiled body on shuffle worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 40;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    std::string always;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int st = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            const World w = shuffle_world(*m, rng);
            const Args a = args_for(c, w, rng);
            st += pair(*m, c.hand, c.recomp, a, seed, c.name).stopped ? 1 : 0;
        }
        pairs += static_cast<int>(seeds);
        stops += st;
        if (st == static_cast<int>(seeds)) always += std::string(" ") + c.name;
    }
    MESSAGE("shuffle: " << pairs << " pairs over " << std::size(kCases) << " functions, " << stops
                        << " ended at a compared stop (fault / runaway); always stopped:" << (always.empty() ? " none" : always));
}

TEST_CASE("game(shuffle): every body on the replay snapshots' real state") {
    int ran = 0, used = 0;
    for (const char* dir : {"battle_ref_6150", "b_5800", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        ++used;
        auto m = std::make_unique<Machine>();
        if (const char* err = m->load_elf(elf_path())) {
            MESSAGE("SKIP: " << err);
            return;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        std::mt19937 rng{0x5F1u};
        for (const Case& c : kCases) {
            for (int rep = 0; rep < 2; ++rep) {
                // pointer arguments into the stand-in heap's upper half (zero in every snapshot), small values otherwise
                Args a{};
                for (unsigned i = 0; i < 4; ++i) {
                    const char k = std::strlen(c.kinds) > i ? c.kinds[i] : 'n';
                    a[i] = (k == 'o' || k == 'n' || k == 'v') ? rng() % 8 : sx(kStandInHeap + 0x200000u + 0x100u * (rng() % 64));
                }
                pair(*m, c.hand, c.recomp, a, rng(), c.name);
                ++ran;
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            }
        }
    }
    MESSAGE("snapshots: " << ran << " pairs on " << used << " snapshot(s)");
}

TEST_CASE("game(shuffle): the shuffle functions follow the documented rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    std::mt19937 rng{0x5AFEu};
    int checks = 0;
    // 0. The command table: nine commands, END and the waits without arguments, SWAP / CLOSE two u16, the rest one.
    {
        const u16 sizes[9] = {0, 4, 2, 4, 2, 0, 0, 2, 0};
        for (u32 op = 0; op < 9; ++op) {
            CHECK(load16(*m, kScriptTable + 8 * op + 4) == sizes[op]);
            CHECK(load32(*m, kScriptTable + 8 * op) != 0);
        }
        CHECK(load32(*m, kScriptTable + 8 * 9) == 0x5F6C6673u);  // the table ends; the "sfl_..." strings follow
    }
    for (int it = 0; it < 60; ++it) {
        World w = shuffle_world(*m, rng);
        store32(*m, gp(-18844), kCard);
        store32(*m, gp(-18840), kScript);
        store32(*m, gp(-18960), kResult);
        // 1. sub_259850 (emit op + arguments) writes exactly the host encoding and advances the write pointer.
        {
            const u32 op = rng() % 9, wp0 = kScriptBuf + 2 * (rng() % 64);
            store32(*m, kScript + 4, kScriptBuf);
            store32(*m, kScript + 12, wp0);
            store32(*m, kScript + 16, kScriptBufSize);
            u8 argb[4];
            for (u8& b : argb) b = static_cast<u8>(rng());
            std::memcpy(m->at(kParams), argb, 4);
            // the host encoding, computed in place on a saved copy of the buffer, then the buffer put back
            const std::vector<u8> before(m->at(kScriptBuf), m->at(kScriptBuf) + kScriptBufSize);
            const u32 wp1 = encode_op(*m, wp0, op, argb);
            const std::vector<u8> want(m->at(kScriptBuf), m->at(kScriptBuf) + kScriptBufSize);
            std::memcpy(m->at(kScriptBuf), before.data(), kScriptBufSize);
            pair(*m, PAIR(fn_sub_259850_00259850), Args{op, sx(kParams), 0, 0}, rng(), "rule 259850");
            CHECK(std::memcmp(m->at(kScriptBuf), want.data(), kScriptBufSize) == 0);
            CHECK(load32(*m, kScript + 12) == wp1);
            // the writers: op codes 0 / 1 / 3 / 2 / 4 / 5 / 6 / 7 / 8 with their u16 arguments
            struct W { Fn h, r; u32 op; unsigned nargs; };
            const W writers[] = {{PAIR(fn_sub_259970_00259970), 0, 0}, {PAIR(fn_sub_2599C0_002599c0), 1, 2},
                                 {PAIR(fn_sub_259B00_00259b00), 2, 1}, {PAIR(fn_sub_259A60_00259a60), 3, 2},
                                 {PAIR(fn_sub_259B60_00259b60), 4, 1}, {PAIR(fn_sub_259BC0_00259bc0), 5, 0},
                                 {PAIR(fn_sub_259C10_00259c10), 6, 0}, {PAIR(fn_sub_259C60_00259c60), 7, 1},
                                 {PAIR(fn_sub_259CC0_00259cc0), 8, 0}};
            const W& wr = writers[rng() % 9];
            const u16 x = static_cast<u16>(rng()), y = static_cast<u16>(rng());
            store32(*m, kScript + 12, kScriptBuf);
            pair(*m, wr.h, wr.r, Args{x, y, 0, 0}, rng(), "rule script writer");
            CHECK(load16(*m, kScriptBuf) == wr.op);
            if (wr.nargs >= 1) CHECK(load16(*m, kScriptBuf + 4) == x);
            if (wr.nargs == 2) CHECK(load16(*m, kScriptBuf + 6) == y);
            CHECK(load32(*m, kScript + 12) == kScriptBuf + (wr.nargs == 0 ? 2u : wr.nargs == 1 ? 6u : 8u));
            checks += 5;
        }
        w = shuffle_world(*m, rng);
        store32(*m, gp(-18844), kCard);
        // 2. sub_2554F0: the top-level cards in the deal list; sub_255440 / sub_256110: the one with an order.
        {
            u32 n = 0;
            for (u32 c : w.list) n += (load32(*m, c) & 0x2u) == 0;
            CHECK(v0_of(pair(*m, PAIR(fn_sub_2554F0_002554f0), Args{}, rng(), "rule 2554F0")) == n);
            CHECK(n == w.n_top);
            if (w.n_top > 0) {
                const u32 order = rng() % w.n_top;
                u32 want = 0;
                for (u32 c : w.list)
                    if ((load32(*m, c) & 0x2u) == 0 && load32(*m, c + 16) == order) want = c;
                CHECK(v0_of(pair(*m, PAIR(fn_sub_255440_00255440), Args{order, 0, 0, 0}, rng(), "rule 255440")) == want);
                CHECK(v0_of(pair(*m, PAIR(fn_sub_256110_00256110), Args{order, 0, 0, 0}, rng(), "rule 256110")) == want);
            }
            checks += 4;
        }
        // 3. sub_259190(parent, out, count): the children of a stack land at out[child order]; count = how many.
        if (!w.list.empty()) {
            const u32 parent = w.list[rng() % w.list.size()];
            const u32 out = kParams, cnt = kParams + 0x100;
            std::vector<u32> want(16, 0xFFFFFFFFu);
            u32 n = 0;
            for (u32 c : w.list)
                if ((load32(*m, c) & 0x2u) != 0 && load32(*m, c + 4040) == parent) want[load32(*m, c + 16)] = c, ++n;
            for (u32 k = 0; k < 16; ++k) store32(*m, out + 4 * k, 0xFFFFFFFFu);
            pair(*m, PAIR(fn_sub_259190_00259190), Args{sx(parent), sx(out), sx(cnt), 0}, rng(), "rule 259190");
            CHECK(load32(*m, cnt) == n);
            for (u32 k = 0; k < 16; ++k) CHECK(load32(*m, out + 4 * k) == want[k]);
            checks += 17;
        }
        // 4. Card creation (sub_2536B0 arcana / sub_2537F0 persona / sub_253920 blank): a free slot joins the deal list at
        //    the tail with flag 0x4, kind 1 / 0 / 2, the order = the card count, which grows by one.
        {
            const u32 count = load32(*m, kCard + kCardCount), tail = load32(*m, kCard + kListTail);
            u32 free_slot = 0;  // sub_255390 takes the first slot without flag 0x4
            for (u32 i = 16; i-- > 0;)
                if ((load32(*m, card_of(i)) & 0x4u) == 0) free_slot = card_of(i);
            if (free_slot != 0) {
                const u32 kind = rng() % 3, a = rng() % 22, b = rng() % 12;
                if (kind == 1) pair(*m, PAIR(fn_sub_2536B0_002536b0), Args{a, b, 0, 0}, rng(), "rule 2536B0");
                else if (kind == 0) pair(*m, PAIR(fn_sub_2537F0_002537f0), Args{a, 0, 0, 0}, rng(), "rule 2537F0");
                else pair(*m, PAIR(fn_sub_253920_00253920), Args{}, rng(), "rule 253920");
                CHECK((load32(*m, free_slot) & 0x4u) != 0);
                CHECK(load32(*m, free_slot + 4) == kind);
                CHECK(load32(*m, free_slot + 16) == count);
                CHECK(load32(*m, kCard + kCardCount) == count + 1);
                CHECK(load32(*m, kCard + kListTail) == free_slot);
                CHECK(load32(*m, free_slot + 4036) == 0);
                CHECK(load32(*m, free_slot + 4032) == tail);
                if (kind == 1) CHECK((load32(*m, free_slot + 8) == a && load32(*m, free_slot + 12) == b));
                if (kind == 0) CHECK(load16(*m, free_slot + 8) == a);
                checks += 8;
            }
        }
        // 5. The result entries: sub_1F6D20 appends {kind, a, b} at +92 + 1648 n and indexes it in the kind's list;
        //    sub_1F9680 finds an entry of the same kind with the same u16 id (kind 0) or the same +4 or +8 (kind 1).
        {
            const u32 n = rng() % 8, kind = rng() % 2, a = rng() % 6, b = rng() % 6;
            store32(*m, gp(-18960), kResult);
            store32(*m, kResult + 13276, n);
            store32(*m, kResult + 13336, rng() % 8);
            store32(*m, kResult + 13340, rng() % 8);
            const u32 l1 = load32(*m, kResult + 13336), l0 = load32(*m, kResult + 13340);
            store32(*m, kParams + 0, kind), store32(*m, kParams + 4, a), store32(*m, kParams + 8, b);
            bool found = false;
            for (u32 e = 0; e < n; ++e) {
                const u32 r = kResult + 92 + 1648 * e;
                if (load32(*m, r) != kind) continue;
                if (kind == 0 && load16(*m, r + 4) == static_cast<u16>(a)) found = true;
                if (kind == 1 && (load32(*m, r + 4) == a || load32(*m, r + 8) == b)) found = true;
            }
            CHECK(v0_of(pair(*m, PAIR(fn_sub_1F9680_001f9680), Args{sx(kParams), 0, 0, 0}, rng(), "rule 1F9680")) == (found ? 1u : 0u));
            pair(*m, PAIR(fn_sub_1F6D20_001f6d20), Args{sx(kParams), 0, 0, 0}, rng(), "rule 1F6D20");
            CHECK(load32(*m, kResult + 13276) == n + 1);
            CHECK(load32(*m, kResult + 92 + 1648 * n) == kind);
            CHECK(load32(*m, kResult + 96 + 1648 * n) == a);
            CHECK(load32(*m, kResult + 100 + 1648 * n) == b);
            if (kind == 1) {
                CHECK(load32(*m, kResult + 13336) == l1 + 1);
                CHECK(load32(*m, kResult + 28 + 4 * l1) == n);
            } else {
                CHECK(load32(*m, kResult + 13340) == l0 + 1);
                CHECK(load32(*m, kResult + 60 + 4 * l0) == n);
            }
            checks += 7;
        }
    }
    // 6. The shuffle counters (game counters 56 / 57): sub_25B440 re-arms them -- 57 = 0, 56 = 24 + rand % 5; sub_1F56B0
    //    counts a battle: 57 + 1, or the re-arm when 57 had reached 56.
    {
        auto counter = [&](u32 id) {  // (a hooks scope per call: a pair's scope ends with none installed)
            rt_test::HooksScope hooks{&m->hooks};
            m->fresh_context(Args{id, 0, 0, 0}, rng);
            rt::bind_context(&m->ctx);
            recomp_gen::fn_sub_16F380_0016f380(m->ctx);
            return static_cast<u32>(m->ctx.gpr[GPR_V0].u64[0]);
        };
        auto set_counter = [&](u32 id, u32 v) {
            rt_test::HooksScope hooks{&m->hooks};
            m->fresh_context(Args{id, v, 0, 0}, rng);
            rt::bind_context(&m->ctx);
            recomp_gen::fn_sub_16F3E0_0016f3e0(m->ctx);
        };
        int rearmed = 0;
        for (int it = 0; it < 40; ++it) {
            pair(*m, PAIR(fn_sub_25B440_0025b440), Args{}, rng(), "rule 25B440");
            CHECK(counter(57) == 0);
            const u32 lim = counter(56);
            CHECK((lim >= 24 && lim <= 28));
            const u32 c57 = rng() % 2 ? lim : rng() % lim;
            set_counter(57, c57);
            pair(*m, PAIR(fn_sub_1F56B0_001f56b0), Args{}, rng(), "rule 1F56B0");
            if (c57 == lim) {
                ++rearmed;
                CHECK(counter(57) == 0);
                CHECK((counter(56) >= 24 && counter(56) <= 28));
            } else {
                CHECK(counter(57) == c57 + 1);
                CHECK(counter(56) == lim);
            }
            checks += 4;
        }
        CHECK(rearmed > 0);
    }
    MESSAGE("rules: " << checks << " checks");
}

#else

TEST_CASE("game(shuffle): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
