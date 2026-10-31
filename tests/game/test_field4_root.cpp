// Pair tests of slice field4, the field loaders / sequences / field root (game/src/field/field4_root.cpp): every body
// against its recompiled body (tests/game/handgen_pairs.h, pair_harness.h, stand_ins.h; all RAM, the registers and
// cycles), on
//   * random worlds: the p3fes_handgen sweep of every function;
//   * the replay snapshots' field roots (climb_ref_17000, shop_ref_4100, fusion_vr_5000, dorm_replay_4900): the running
//     state, the shutdown path (13 -> 18 -> -1), the pack predicates, the exit request (sub_1BAAA0);
//   * the stand-in world (heap, printf / sprintf, the fake H_Cdvd layer over extracted/): the boot loaders copy their
//     disc files byte for byte (field.bf, fuka.bf, DUNGEONAT / DUNGEONFES.BIN, comutbl.bin, npccomu.bf), the per-field
//     requests ask for the documented paths, the try-load functions copy a finished request into sField.
#include "handgen_pairs.h"
#include "field4_util.h"

#include "p3fes/game/field3_kosaka.h"
#include "p3fes/game/field4.h"

#include <cmath>
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
void fn_sub_1E05B0_001e05b0(EEContext&);  // generated body (field3_kosaka: K_VPad_UpdateTask)
void fn_sub_1E05B0_001e05b0__recomp(EEContext&);  // recompiled
void fn_sub_1B00C0_001b00c0(EEContext&);  // generated body
void fn_sub_1B00C0_001b00c0__recomp(EEContext&);  // recompiled
void fn_sub_1B02C0_001b02c0(EEContext&);  // generated body
void fn_sub_1B02C0_001b02c0__recomp(EEContext&);  // recompiled
void fn_sub_1B0710_001b0710(EEContext&);  // generated body
void fn_sub_1B0710_001b0710__recomp(EEContext&);  // recompiled
void fn_sub_1B07D0_001b07d0(EEContext&);  // generated body
void fn_sub_1B07D0_001b07d0__recomp(EEContext&);  // recompiled
void fn_sub_1B0840_001b0840(EEContext&);  // generated body
void fn_sub_1B0840_001b0840__recomp(EEContext&);  // recompiled
void fn_sub_1B0870_001b0870(EEContext&);  // generated body
void fn_sub_1B0870_001b0870__recomp(EEContext&);  // recompiled
void fn_sub_1B08D0_001b08d0(EEContext&);  // generated body
void fn_sub_1B08D0_001b08d0__recomp(EEContext&);  // recompiled
void fn_sub_1B0920_001b0920(EEContext&);  // generated body
void fn_sub_1B0920_001b0920__recomp(EEContext&);  // recompiled
void fn_sub_1B0950_001b0950(EEContext&);  // generated body
void fn_sub_1B0950_001b0950__recomp(EEContext&);  // recompiled
void fn_sub_1B09B0_001b09b0(EEContext&);  // generated body
void fn_sub_1B09B0_001b09b0__recomp(EEContext&);  // recompiled
void fn_sub_1B09F0_001b09f0(EEContext&);  // generated body
void fn_sub_1B09F0_001b09f0__recomp(EEContext&);  // recompiled
void fn_sub_1B0A20_001b0a20(EEContext&);  // generated body
void fn_sub_1B0A20_001b0a20__recomp(EEContext&);  // recompiled
void fn_sub_1B10F0_001b10f0(EEContext&);  // generated body
void fn_sub_1B10F0_001b10f0__recomp(EEContext&);  // recompiled
void fn_sub_1B2780_001b2780(EEContext&);  // generated body
void fn_sub_1B2780_001b2780__recomp(EEContext&);  // recompiled
void fn_sub_1B2860_001b2860(EEContext&);  // generated body
void fn_sub_1B2860_001b2860__recomp(EEContext&);  // recompiled
void fn_sub_1B2B30_001b2b30(EEContext&);  // generated body
void fn_sub_1B2B30_001b2b30__recomp(EEContext&);  // recompiled
void fn_sub_1B2B90_001b2b90(EEContext&);  // generated body
void fn_sub_1B2B90_001b2b90__recomp(EEContext&);  // recompiled
void fn_sub_1B2F00_001b2f00(EEContext&);  // generated body
void fn_sub_1B2F00_001b2f00__recomp(EEContext&);  // recompiled
void fn_sub_1B32F0_001b32f0(EEContext&);  // generated body
void fn_sub_1B32F0_001b32f0__recomp(EEContext&);  // recompiled
void fn_sub_1B3480_001b3480(EEContext&);  // generated body
void fn_sub_1B3480_001b3480__recomp(EEContext&);  // recompiled
void fn_sub_1B39E0_001b39e0(EEContext&);  // generated body
void fn_sub_1B39E0_001b39e0__recomp(EEContext&);  // recompiled
void fn_sub_1B3C90_001b3c90(EEContext&);  // generated body
void fn_sub_1B3C90_001b3c90__recomp(EEContext&);  // recompiled
void fn_sub_1B4E00_001b4e00(EEContext&);  // generated body
void fn_sub_1B4E00_001b4e00__recomp(EEContext&);  // recompiled
void fn_sub_1B5200_001b5200(EEContext&);  // generated body
void fn_sub_1B5200_001b5200__recomp(EEContext&);  // recompiled
void fn_sub_1B5380_001b5380(EEContext&);  // generated body
void fn_sub_1B5380_001b5380__recomp(EEContext&);  // recompiled
void fn_sub_1B5610_001b5610(EEContext&);  // generated body
void fn_sub_1B5610_001b5610__recomp(EEContext&);  // recompiled
void fn_sub_1B56F0_001b56f0(EEContext&);  // generated body
void fn_sub_1B56F0_001b56f0__recomp(EEContext&);  // recompiled
void fn_sub_1B5850_001b5850(EEContext&);  // generated body
void fn_sub_1B5850_001b5850__recomp(EEContext&);  // recompiled
void fn_sub_1B5880_001b5880(EEContext&);  // generated body
void fn_sub_1B5880_001b5880__recomp(EEContext&);  // recompiled
void fn_sub_1B58B0_001b58b0(EEContext&);  // generated body
void fn_sub_1B58B0_001b58b0__recomp(EEContext&);  // recompiled
void fn_sub_1B5950_001b5950(EEContext&);  // generated body
void fn_sub_1B5950_001b5950__recomp(EEContext&);  // recompiled
void fn_sub_1B5990_001b5990(EEContext&);  // generated body
void fn_sub_1B5990_001b5990__recomp(EEContext&);  // recompiled
void fn_sub_1B59C0_001b59c0(EEContext&);  // generated body
void fn_sub_1B59C0_001b59c0__recomp(EEContext&);  // recompiled
void fn_sub_1B5A00_001b5a00(EEContext&);  // generated body
void fn_sub_1B5A00_001b5a00__recomp(EEContext&);  // recompiled
void fn_sub_1B5A30_001b5a30(EEContext&);  // generated body
void fn_sub_1B5A30_001b5a30__recomp(EEContext&);  // recompiled
void fn_sub_1B5AE0_001b5ae0(EEContext&);  // generated body
void fn_sub_1B5AE0_001b5ae0__recomp(EEContext&);  // recompiled
void fn_sub_1B5B50_001b5b50(EEContext&);  // generated body
void fn_sub_1B5B50_001b5b50__recomp(EEContext&);  // recompiled
void fn_sub_1B5DF0_001b5df0(EEContext&);  // generated body
void fn_sub_1B5DF0_001b5df0__recomp(EEContext&);  // recompiled
void fn_sub_1B5E30_001b5e30(EEContext&);  // generated body
void fn_sub_1B5E30_001b5e30__recomp(EEContext&);  // recompiled
void fn_sub_1B5E60_001b5e60(EEContext&);  // generated body
void fn_sub_1B5E60_001b5e60__recomp(EEContext&);  // recompiled
void fn_sub_1B5E90_001b5e90(EEContext&);  // generated body
void fn_sub_1B5E90_001b5e90__recomp(EEContext&);  // recompiled
void fn_sub_1B6060_001b6060(EEContext&);  // generated body
void fn_sub_1B6060_001b6060__recomp(EEContext&);  // recompiled
void fn_sub_1B60A0_001b60a0(EEContext&);  // generated body
void fn_sub_1B60A0_001b60a0__recomp(EEContext&);  // recompiled
void fn_sub_1B60D0_001b60d0(EEContext&);  // generated body
void fn_sub_1B60D0_001b60d0__recomp(EEContext&);  // recompiled
void fn_sub_1B6100_001b6100(EEContext&);  // generated body
void fn_sub_1B6100_001b6100__recomp(EEContext&);  // recompiled
void fn_sub_1B61F0_001b61f0(EEContext&);  // generated body
void fn_sub_1B61F0_001b61f0__recomp(EEContext&);  // recompiled
void fn_sub_1B75E0_001b75e0(EEContext&);  // generated body
void fn_sub_1B75E0_001b75e0__recomp(EEContext&);  // recompiled
void fn_sub_1B76B0_001b76b0(EEContext&);  // generated body
void fn_sub_1B76B0_001b76b0__recomp(EEContext&);  // recompiled
void fn_sub_1B7700_001b7700(EEContext&);  // generated body
void fn_sub_1B7700_001b7700__recomp(EEContext&);  // recompiled
void fn_K_Seq_CallField_001b77b0(EEContext&);  // generated body
void fn_K_Seq_CallField_001b77b0__recomp(EEContext&);  // recompiled
void fn_K_Seq_ExitField_001b7850(EEContext&);  // generated body
void fn_K_Seq_ExitField_001b7850__recomp(EEContext&);  // recompiled
void fn_K_Seq_CallFieldEvent_001b7900(EEContext&);  // generated body
void fn_K_Seq_CallFieldEvent_001b7900__recomp(EEContext&);  // recompiled
void fn_K_Seq_ExitFieldEvent_001b79a0(EEContext&);  // generated body
void fn_K_Seq_ExitFieldEvent_001b79a0__recomp(EEContext&);  // recompiled
void fn_K_Seq_CallDungeon_001b7a50(EEContext&);  // generated body
void fn_K_Seq_CallDungeon_001b7a50__recomp(EEContext&);  // recompiled
void fn_K_Seq_ExitDungeon_001b7a90(EEContext&);  // generated body
void fn_K_Seq_ExitDungeon_001b7a90__recomp(EEContext&);  // recompiled
void fn_K_Data_LoadFldMainScript_001b7b10(EEContext&);  // generated body
void fn_K_Data_LoadFldMainScript_001b7b10__recomp(EEContext&);  // recompiled
void fn_sub_1B7BB0_001b7bb0(EEContext&);  // generated body
void fn_sub_1B7BB0_001b7bb0__recomp(EEContext&);  // recompiled
void fn_sub_1B7C40_001b7c40(EEContext&);  // generated body
void fn_sub_1B7C40_001b7c40__recomp(EEContext&);  // recompiled
void fn_sub_1B7D00_001b7d00(EEContext&);  // generated body
void fn_sub_1B7D00_001b7d00__recomp(EEContext&);  // recompiled
void fn_sub_1B7D60_001b7d60(EEContext&);  // generated body
void fn_sub_1B7D60_001b7d60__recomp(EEContext&);  // recompiled
void fn_sub_1B7DC0_001b7dc0(EEContext&);  // generated body
void fn_sub_1B7DC0_001b7dc0__recomp(EEContext&);  // recompiled
void fn_sub_1B7E30_001b7e30(EEContext&);  // generated body
void fn_sub_1B7E30_001b7e30__recomp(EEContext&);  // recompiled
void fn_sub_1B7E60_001b7e60(EEContext&);  // generated body
void fn_sub_1B7E60_001b7e60__recomp(EEContext&);  // recompiled
void fn_sub_1B8000_001b8000(EEContext&);  // generated body
void fn_sub_1B8000_001b8000__recomp(EEContext&);  // recompiled
void fn_sub_1B8030_001b8030(EEContext&);  // generated body
void fn_sub_1B8030_001b8030__recomp(EEContext&);  // recompiled
void fn_sub_1B80C0_001b80c0(EEContext&);  // generated body
void fn_sub_1B80C0_001b80c0__recomp(EEContext&);  // recompiled
void fn_sub_1B8160_001b8160(EEContext&);  // generated body
void fn_sub_1B8160_001b8160__recomp(EEContext&);  // recompiled
void fn_sub_1B81F0_001b81f0(EEContext&);  // generated body
void fn_sub_1B81F0_001b81f0__recomp(EEContext&);  // recompiled
void fn_sub_1B83F0_001b83f0(EEContext&);  // generated body
void fn_sub_1B83F0_001b83f0__recomp(EEContext&);  // recompiled
void fn_sub_1B85A0_001b85a0(EEContext&);  // generated body
void fn_sub_1B85A0_001b85a0__recomp(EEContext&);  // recompiled
void fn_sub_1B8600_001b8600(EEContext&);  // generated body
void fn_sub_1B8600_001b8600__recomp(EEContext&);  // recompiled
void fn_sub_1B8680_001b8680(EEContext&);  // generated body
void fn_sub_1B8680_001b8680__recomp(EEContext&);  // recompiled
void fn_sub_1B8710_001b8710(EEContext&);  // generated body
void fn_sub_1B8710_001b8710__recomp(EEContext&);  // recompiled
void fn_sub_1B8870_001b8870(EEContext&);  // generated body
void fn_sub_1B8870_001b8870__recomp(EEContext&);  // recompiled
void fn_sub_1B88D0_001b88d0(EEContext&);  // generated body
void fn_sub_1B88D0_001b88d0__recomp(EEContext&);  // recompiled
void fn_sub_1B8960_001b8960(EEContext&);  // generated body
void fn_sub_1B8960_001b8960__recomp(EEContext&);  // recompiled
void fn_sub_1B8AE0_001b8ae0(EEContext&);  // generated body
void fn_sub_1B8AE0_001b8ae0__recomp(EEContext&);  // recompiled
void fn_sub_1B8B40_001b8b40(EEContext&);  // generated body
void fn_sub_1B8B40_001b8b40__recomp(EEContext&);  // recompiled
void fn_sub_1B8C40_001b8c40(EEContext&);  // generated body
void fn_sub_1B8C40_001b8c40__recomp(EEContext&);  // recompiled
void fn_sub_1B8CF0_001b8cf0(EEContext&);  // generated body
void fn_sub_1B8CF0_001b8cf0__recomp(EEContext&);  // recompiled
void fn_sub_1B8D60_001b8d60(EEContext&);  // generated body
void fn_sub_1B8D60_001b8d60__recomp(EEContext&);  // recompiled
void fn_sub_1B8DB0_001b8db0(EEContext&);  // generated body
void fn_sub_1B8DB0_001b8db0__recomp(EEContext&);  // recompiled
void fn_sub_1B8FD0_001b8fd0(EEContext&);  // generated body
void fn_sub_1B8FD0_001b8fd0__recomp(EEContext&);  // recompiled
void fn_K_Field_Init_001b90f0(EEContext&);  // generated body
void fn_K_Field_Init_001b90f0__recomp(EEContext&);  // recompiled
void fn_sub_1B9140_001b9140(EEContext&);  // generated body
void fn_sub_1B9140_001b9140__recomp(EEContext&);  // recompiled
void fn_K_Field_UpdateFieldRootTask_001b9480(EEContext&);  // generated body
void fn_K_Field_UpdateFieldRootTask_001b9480__recomp(EEContext&);  // recompiled
void fn_K_Field_DestroyFieldRootTask_001ba3d0(EEContext&);  // generated body
void fn_K_Field_DestroyFieldRootTask_001ba3d0__recomp(EEContext&);  // recompiled
void fn_k_Field_CreateFieldRootTask_001ba5f0(EEContext&);  // generated body
void fn_k_Field_CreateFieldRootTask_001ba5f0__recomp(EEContext&);  // recompiled
void fn_K_Field_SetShouldShutdown_001ba880(EEContext&);  // generated body
void fn_K_Field_SetShouldShutdown_001ba880__recomp(EEContext&);  // recompiled
void fn_sub_1BA8D0_001ba8d0(EEContext&);  // generated body
void fn_sub_1BA8D0_001ba8d0__recomp(EEContext&);  // recompiled
void fn_sub_1BAA50_001baa50(EEContext&);  // generated body
void fn_sub_1BAA50_001baa50__recomp(EEContext&);  // recompiled
void fn_sub_1BAAA0_001baaa0(EEContext&);  // generated body
void fn_sub_1BAAA0_001baaa0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1B00C0", 0x1B00C0, &recomp_gen::fn_sub_1B00C0_001b00c0, &recomp_gen::fn_sub_1B00C0_001b00c0__recomp},
    {"sub_1B02C0", 0x1B02C0, &recomp_gen::fn_sub_1B02C0_001b02c0, &recomp_gen::fn_sub_1B02C0_001b02c0__recomp},
    {"sub_1B0710", 0x1B0710, &recomp_gen::fn_sub_1B0710_001b0710, &recomp_gen::fn_sub_1B0710_001b0710__recomp},
    {"sub_1B07D0", 0x1B07D0, &recomp_gen::fn_sub_1B07D0_001b07d0, &recomp_gen::fn_sub_1B07D0_001b07d0__recomp},
    {"sub_1B0840", 0x1B0840, &recomp_gen::fn_sub_1B0840_001b0840, &recomp_gen::fn_sub_1B0840_001b0840__recomp},
    {"sub_1B0870", 0x1B0870, &recomp_gen::fn_sub_1B0870_001b0870, &recomp_gen::fn_sub_1B0870_001b0870__recomp},
    {"sub_1B08D0", 0x1B08D0, &recomp_gen::fn_sub_1B08D0_001b08d0, &recomp_gen::fn_sub_1B08D0_001b08d0__recomp},
    {"sub_1B0920", 0x1B0920, &recomp_gen::fn_sub_1B0920_001b0920, &recomp_gen::fn_sub_1B0920_001b0920__recomp},
    {"sub_1B0950", 0x1B0950, &recomp_gen::fn_sub_1B0950_001b0950, &recomp_gen::fn_sub_1B0950_001b0950__recomp},
    {"sub_1B09B0", 0x1B09B0, &recomp_gen::fn_sub_1B09B0_001b09b0, &recomp_gen::fn_sub_1B09B0_001b09b0__recomp},
    {"sub_1B09F0", 0x1B09F0, &recomp_gen::fn_sub_1B09F0_001b09f0, &recomp_gen::fn_sub_1B09F0_001b09f0__recomp},
    {"sub_1B0A20", 0x1B0A20, &recomp_gen::fn_sub_1B0A20_001b0a20, &recomp_gen::fn_sub_1B0A20_001b0a20__recomp},
    {"sub_1B10F0", 0x1B10F0, &recomp_gen::fn_sub_1B10F0_001b10f0, &recomp_gen::fn_sub_1B10F0_001b10f0__recomp},
    {"sub_1B2780", 0x1B2780, &recomp_gen::fn_sub_1B2780_001b2780, &recomp_gen::fn_sub_1B2780_001b2780__recomp},
    {"sub_1B2860", 0x1B2860, &recomp_gen::fn_sub_1B2860_001b2860, &recomp_gen::fn_sub_1B2860_001b2860__recomp},
    {"sub_1B2B30", 0x1B2B30, &recomp_gen::fn_sub_1B2B30_001b2b30, &recomp_gen::fn_sub_1B2B30_001b2b30__recomp},
    {"sub_1B2B90", 0x1B2B90, &recomp_gen::fn_sub_1B2B90_001b2b90, &recomp_gen::fn_sub_1B2B90_001b2b90__recomp},
    {"sub_1B2F00", 0x1B2F00, &recomp_gen::fn_sub_1B2F00_001b2f00, &recomp_gen::fn_sub_1B2F00_001b2f00__recomp},
    {"sub_1B32F0", 0x1B32F0, &recomp_gen::fn_sub_1B32F0_001b32f0, &recomp_gen::fn_sub_1B32F0_001b32f0__recomp},
    {"sub_1B3480", 0x1B3480, &recomp_gen::fn_sub_1B3480_001b3480, &recomp_gen::fn_sub_1B3480_001b3480__recomp},
    {"sub_1B39E0", 0x1B39E0, &recomp_gen::fn_sub_1B39E0_001b39e0, &recomp_gen::fn_sub_1B39E0_001b39e0__recomp},
    {"sub_1B3C90", 0x1B3C90, &recomp_gen::fn_sub_1B3C90_001b3c90, &recomp_gen::fn_sub_1B3C90_001b3c90__recomp},
    {"sub_1B4E00", 0x1B4E00, &recomp_gen::fn_sub_1B4E00_001b4e00, &recomp_gen::fn_sub_1B4E00_001b4e00__recomp},
    {"sub_1B5200", 0x1B5200, &recomp_gen::fn_sub_1B5200_001b5200, &recomp_gen::fn_sub_1B5200_001b5200__recomp},
    {"sub_1B5380", 0x1B5380, &recomp_gen::fn_sub_1B5380_001b5380, &recomp_gen::fn_sub_1B5380_001b5380__recomp},
    {"sub_1B5610", 0x1B5610, &recomp_gen::fn_sub_1B5610_001b5610, &recomp_gen::fn_sub_1B5610_001b5610__recomp},
    {"sub_1B56F0", 0x1B56F0, &recomp_gen::fn_sub_1B56F0_001b56f0, &recomp_gen::fn_sub_1B56F0_001b56f0__recomp},
    {"sub_1B5850", 0x1B5850, &recomp_gen::fn_sub_1B5850_001b5850, &recomp_gen::fn_sub_1B5850_001b5850__recomp},
    {"sub_1B5880", 0x1B5880, &recomp_gen::fn_sub_1B5880_001b5880, &recomp_gen::fn_sub_1B5880_001b5880__recomp},
    {"sub_1B58B0", 0x1B58B0, &recomp_gen::fn_sub_1B58B0_001b58b0, &recomp_gen::fn_sub_1B58B0_001b58b0__recomp},
    {"sub_1B5950", 0x1B5950, &recomp_gen::fn_sub_1B5950_001b5950, &recomp_gen::fn_sub_1B5950_001b5950__recomp},
    {"sub_1B5990", 0x1B5990, &recomp_gen::fn_sub_1B5990_001b5990, &recomp_gen::fn_sub_1B5990_001b5990__recomp},
    {"sub_1B59C0", 0x1B59C0, &recomp_gen::fn_sub_1B59C0_001b59c0, &recomp_gen::fn_sub_1B59C0_001b59c0__recomp},
    {"sub_1B5A00", 0x1B5A00, &recomp_gen::fn_sub_1B5A00_001b5a00, &recomp_gen::fn_sub_1B5A00_001b5a00__recomp},
    {"sub_1B5A30", 0x1B5A30, &recomp_gen::fn_sub_1B5A30_001b5a30, &recomp_gen::fn_sub_1B5A30_001b5a30__recomp},
    {"sub_1B5AE0", 0x1B5AE0, &recomp_gen::fn_sub_1B5AE0_001b5ae0, &recomp_gen::fn_sub_1B5AE0_001b5ae0__recomp},
    {"sub_1B5B50", 0x1B5B50, &recomp_gen::fn_sub_1B5B50_001b5b50, &recomp_gen::fn_sub_1B5B50_001b5b50__recomp},
    {"sub_1B5DF0", 0x1B5DF0, &recomp_gen::fn_sub_1B5DF0_001b5df0, &recomp_gen::fn_sub_1B5DF0_001b5df0__recomp},
    {"sub_1B5E30", 0x1B5E30, &recomp_gen::fn_sub_1B5E30_001b5e30, &recomp_gen::fn_sub_1B5E30_001b5e30__recomp},
    {"sub_1B5E60", 0x1B5E60, &recomp_gen::fn_sub_1B5E60_001b5e60, &recomp_gen::fn_sub_1B5E60_001b5e60__recomp},
    {"sub_1B5E90", 0x1B5E90, &recomp_gen::fn_sub_1B5E90_001b5e90, &recomp_gen::fn_sub_1B5E90_001b5e90__recomp},
    {"sub_1B6060", 0x1B6060, &recomp_gen::fn_sub_1B6060_001b6060, &recomp_gen::fn_sub_1B6060_001b6060__recomp},
    {"sub_1B60A0", 0x1B60A0, &recomp_gen::fn_sub_1B60A0_001b60a0, &recomp_gen::fn_sub_1B60A0_001b60a0__recomp},
    {"sub_1B60D0", 0x1B60D0, &recomp_gen::fn_sub_1B60D0_001b60d0, &recomp_gen::fn_sub_1B60D0_001b60d0__recomp},
    {"sub_1B6100", 0x1B6100, &recomp_gen::fn_sub_1B6100_001b6100, &recomp_gen::fn_sub_1B6100_001b6100__recomp},
    {"sub_1B61F0", 0x1B61F0, &recomp_gen::fn_sub_1B61F0_001b61f0, &recomp_gen::fn_sub_1B61F0_001b61f0__recomp},
    {"sub_1B75E0", 0x1B75E0, &recomp_gen::fn_sub_1B75E0_001b75e0, &recomp_gen::fn_sub_1B75E0_001b75e0__recomp},
    {"sub_1B76B0", 0x1B76B0, &recomp_gen::fn_sub_1B76B0_001b76b0, &recomp_gen::fn_sub_1B76B0_001b76b0__recomp},
    {"sub_1B7700", 0x1B7700, &recomp_gen::fn_sub_1B7700_001b7700, &recomp_gen::fn_sub_1B7700_001b7700__recomp},
    {"K_Seq_CallField", 0x1B77B0, &recomp_gen::fn_K_Seq_CallField_001b77b0, &recomp_gen::fn_K_Seq_CallField_001b77b0__recomp},
    {"K_Seq_ExitField", 0x1B7850, &recomp_gen::fn_K_Seq_ExitField_001b7850, &recomp_gen::fn_K_Seq_ExitField_001b7850__recomp},
    {"K_Seq_CallFieldEvent", 0x1B7900, &recomp_gen::fn_K_Seq_CallFieldEvent_001b7900, &recomp_gen::fn_K_Seq_CallFieldEvent_001b7900__recomp},
    {"K_Seq_ExitFieldEvent", 0x1B79A0, &recomp_gen::fn_K_Seq_ExitFieldEvent_001b79a0, &recomp_gen::fn_K_Seq_ExitFieldEvent_001b79a0__recomp},
    {"K_Seq_CallDungeon", 0x1B7A50, &recomp_gen::fn_K_Seq_CallDungeon_001b7a50, &recomp_gen::fn_K_Seq_CallDungeon_001b7a50__recomp},
    {"K_Seq_ExitDungeon", 0x1B7A90, &recomp_gen::fn_K_Seq_ExitDungeon_001b7a90, &recomp_gen::fn_K_Seq_ExitDungeon_001b7a90__recomp},
    {"K_Data_LoadFldMainScript", 0x1B7B10, &recomp_gen::fn_K_Data_LoadFldMainScript_001b7b10, &recomp_gen::fn_K_Data_LoadFldMainScript_001b7b10__recomp},
    {"sub_1B7BB0", 0x1B7BB0, &recomp_gen::fn_sub_1B7BB0_001b7bb0, &recomp_gen::fn_sub_1B7BB0_001b7bb0__recomp},
    {"sub_1B7C40", 0x1B7C40, &recomp_gen::fn_sub_1B7C40_001b7c40, &recomp_gen::fn_sub_1B7C40_001b7c40__recomp},
    {"sub_1B7D00", 0x1B7D00, &recomp_gen::fn_sub_1B7D00_001b7d00, &recomp_gen::fn_sub_1B7D00_001b7d00__recomp},
    {"sub_1B7D60", 0x1B7D60, &recomp_gen::fn_sub_1B7D60_001b7d60, &recomp_gen::fn_sub_1B7D60_001b7d60__recomp},
    {"sub_1B7DC0", 0x1B7DC0, &recomp_gen::fn_sub_1B7DC0_001b7dc0, &recomp_gen::fn_sub_1B7DC0_001b7dc0__recomp},
    {"sub_1B7E30", 0x1B7E30, &recomp_gen::fn_sub_1B7E30_001b7e30, &recomp_gen::fn_sub_1B7E30_001b7e30__recomp},
    {"sub_1B7E60", 0x1B7E60, &recomp_gen::fn_sub_1B7E60_001b7e60, &recomp_gen::fn_sub_1B7E60_001b7e60__recomp},
    {"sub_1B8000", 0x1B8000, &recomp_gen::fn_sub_1B8000_001b8000, &recomp_gen::fn_sub_1B8000_001b8000__recomp},
    {"sub_1B8030", 0x1B8030, &recomp_gen::fn_sub_1B8030_001b8030, &recomp_gen::fn_sub_1B8030_001b8030__recomp},
    {"sub_1B80C0", 0x1B80C0, &recomp_gen::fn_sub_1B80C0_001b80c0, &recomp_gen::fn_sub_1B80C0_001b80c0__recomp},
    {"sub_1B8160", 0x1B8160, &recomp_gen::fn_sub_1B8160_001b8160, &recomp_gen::fn_sub_1B8160_001b8160__recomp},
    {"sub_1B81F0", 0x1B81F0, &recomp_gen::fn_sub_1B81F0_001b81f0, &recomp_gen::fn_sub_1B81F0_001b81f0__recomp},
    {"sub_1B83F0", 0x1B83F0, &recomp_gen::fn_sub_1B83F0_001b83f0, &recomp_gen::fn_sub_1B83F0_001b83f0__recomp},
    {"sub_1B85A0", 0x1B85A0, &recomp_gen::fn_sub_1B85A0_001b85a0, &recomp_gen::fn_sub_1B85A0_001b85a0__recomp},
    {"sub_1B8600", 0x1B8600, &recomp_gen::fn_sub_1B8600_001b8600, &recomp_gen::fn_sub_1B8600_001b8600__recomp},
    {"sub_1B8680", 0x1B8680, &recomp_gen::fn_sub_1B8680_001b8680, &recomp_gen::fn_sub_1B8680_001b8680__recomp},
    {"sub_1B8710", 0x1B8710, &recomp_gen::fn_sub_1B8710_001b8710, &recomp_gen::fn_sub_1B8710_001b8710__recomp},
    {"sub_1B8870", 0x1B8870, &recomp_gen::fn_sub_1B8870_001b8870, &recomp_gen::fn_sub_1B8870_001b8870__recomp},
    {"sub_1B88D0", 0x1B88D0, &recomp_gen::fn_sub_1B88D0_001b88d0, &recomp_gen::fn_sub_1B88D0_001b88d0__recomp},
    {"sub_1B8960", 0x1B8960, &recomp_gen::fn_sub_1B8960_001b8960, &recomp_gen::fn_sub_1B8960_001b8960__recomp},
    {"sub_1B8AE0", 0x1B8AE0, &recomp_gen::fn_sub_1B8AE0_001b8ae0, &recomp_gen::fn_sub_1B8AE0_001b8ae0__recomp},
    {"sub_1B8B40", 0x1B8B40, &recomp_gen::fn_sub_1B8B40_001b8b40, &recomp_gen::fn_sub_1B8B40_001b8b40__recomp},
    {"sub_1B8C40", 0x1B8C40, &recomp_gen::fn_sub_1B8C40_001b8c40, &recomp_gen::fn_sub_1B8C40_001b8c40__recomp},
    {"sub_1B8CF0", 0x1B8CF0, &recomp_gen::fn_sub_1B8CF0_001b8cf0, &recomp_gen::fn_sub_1B8CF0_001b8cf0__recomp},
    {"sub_1B8D60", 0x1B8D60, &recomp_gen::fn_sub_1B8D60_001b8d60, &recomp_gen::fn_sub_1B8D60_001b8d60__recomp},
    {"sub_1B8DB0", 0x1B8DB0, &recomp_gen::fn_sub_1B8DB0_001b8db0, &recomp_gen::fn_sub_1B8DB0_001b8db0__recomp},
    {"sub_1B8FD0", 0x1B8FD0, &recomp_gen::fn_sub_1B8FD0_001b8fd0, &recomp_gen::fn_sub_1B8FD0_001b8fd0__recomp},
    {"K_Field_Init", 0x1B90F0, &recomp_gen::fn_K_Field_Init_001b90f0, &recomp_gen::fn_K_Field_Init_001b90f0__recomp},
    {"sub_1B9140", 0x1B9140, &recomp_gen::fn_sub_1B9140_001b9140, &recomp_gen::fn_sub_1B9140_001b9140__recomp},
    {"K_Field_UpdateFieldRootTask", 0x1B9480, &recomp_gen::fn_K_Field_UpdateFieldRootTask_001b9480, &recomp_gen::fn_K_Field_UpdateFieldRootTask_001b9480__recomp},
    {"K_Field_DestroyFieldRootTask", 0x1BA3D0, &recomp_gen::fn_K_Field_DestroyFieldRootTask_001ba3d0, &recomp_gen::fn_K_Field_DestroyFieldRootTask_001ba3d0__recomp},
    {"k_Field_CreateFieldRootTask", 0x1BA5F0, &recomp_gen::fn_k_Field_CreateFieldRootTask_001ba5f0, &recomp_gen::fn_k_Field_CreateFieldRootTask_001ba5f0__recomp},
    {"K_Field_SetShouldShutdown", 0x1BA880, &recomp_gen::fn_K_Field_SetShouldShutdown_001ba880, &recomp_gen::fn_K_Field_SetShouldShutdown_001ba880__recomp},
    {"sub_1BA8D0", 0x1BA8D0, &recomp_gen::fn_sub_1BA8D0_001ba8d0, &recomp_gen::fn_sub_1BA8D0_001ba8d0__recomp},
    {"sub_1BAA50", 0x1BAA50, &recomp_gen::fn_sub_1BAA50_001baa50, &recomp_gen::fn_sub_1BAA50_001baa50__recomp},
    {"sub_1BAAA0", 0x1BAAA0, &recomp_gen::fn_sub_1BAAA0_001baaa0, &recomp_gen::fn_sub_1BAAA0_001baaa0__recomp},
};

// The generic sweep: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field4 root): every body equals its recompiled body on random worlds") {
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

// The field pad heading sub_1B02C0 (the hero's walk direction relative to the camera, K_VPad_UpdateTask) on a centred
// x byte: the keyboard's S is (0x80, 0xFF). With a truncating SQRT.S the acosf argument was 0x3F800001 there (64 y bytes
// in all, with x = 0x80) and the heading came back as the 0/0 clamp: the hero turned away and stopped
// (fpu.h sqrt_nearest). Every y byte with x = 0x80 must give the heading of the vector (0, z): 180 for z > 0, 360 for z < 0.
TEST_CASE("game(field4 root): the pad heading of a centred stick x is 180 / 360 degrees for every y byte") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const Case& c = [] () -> const Case& {
        for (const Case& k : kCases)
            if (std::string(k.name) == "sub_1B02C0") return k;
        std::abort();
    }();
    auto heading = [&](u8 x, u8 y) {
        *m->at(0x7E094Cu) = 0;  // no d-pad bits (held word, port 0)
        *m->at(0x7E094Du) = 0;
        *m->at(0x7E095Eu) = x;  // left stick x
        *m->at(0x7E095Fu) = y;  // left stick y
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0, 0, 0, 0}, 1, c.name);
        REQUIRE_FALSE(r.stopped);
        float f;
        std::memcpy(&f, &r.end.fpr[0], 4);
        return f;
    };
    int checked = 0;
    for (int y = 0; y < 256; ++y) {
        if (y >= 128 - 48 && y <= 128 + 48) continue;  // the dead zone: heading 0
        const float h = heading(0x80, static_cast<u8>(y));
        CHECK_MESSAGE(std::fabs(h - (y > 128 ? 180.0f : 360.0f)) < 0.01f, "y byte " << y << ": heading " << h);
        ++checked;
    }
    CHECK(checked == 159);
    CHECK(heading(0x80, 0xFF) == 180.0f);                    // S (was the 0/0 clamp)
    CHECK(std::fabs(heading(0x81, 0xFF) - 180.45f) < 0.01f); // one step right of centre (always worked)
    CHECK(heading(0x80, 0x80) == 0.0f);                      // dead zone
}

// --- field4 tests ---

namespace {
const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    std::fprintf(stderr, "no case %s\n", name);
    std::abort();
}
hgp::Run call(Machine& m, const char* fn, Args a, u32 seed = 1) {
    const Case& c = find_case(fn);
    return hgp::pair(m, c.hand, c.recomp, a, seed, fn);
}
using namespace f4t;
namespace fld = game::f4::fld;
namespace root = game::f4::root;
const char* const kFieldSnapshots[] = {"climb_ref_17000", "shop_ref_4100", "fusion_vr_5000", "dorm_replay_4900"};
}  // namespace

// The hero's pad task on the real field snapshots (no stand-ins): the keyboard's S, (0x80, 0xFF), and straight up on a
// controller, (0x80, 0x01), steer the hero like their neighbours one x step right of centre. One update of
// K_VPad_UpdateTask (sub_1E05B0) per input from the same world: the published speed is the same and the
// hero's controller and rotate task (its orientation, position, the turn it was handed) end within 0.45 degrees of the
// neighbour's. With a truncating SQRT.S the centred x gave the heading sub_1B02C0 its 0/0 clamp (fpu.h sqrt_nearest):
// the hero turned away and stood still.
TEST_CASE("game(field4 root): a centred stick x walks the hero like its neighbour (the field pad task, real snapshots)") {
    namespace ks = game::f3ks;
    int checked = 0;
    for (const char* snap : kFieldSnapshots) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        const u32 pad = r32(m, kSField + ks::kFieldPadTask);
        if (pad == 0) continue;
        const u32 work = r32(m, pad + game::f4::kTaskWork);
        const u32 ctl = r32(m, work + ks::kPadController), rot = r32(m, work + ks::kPadRotateTask);
        if (ctl == 0 || rot == 0) continue;
        const u32 rotWork = r32(m, rot + game::f4::kTaskWork);
        struct Out {
            bool stopped;
            u32 speed;
            std::vector<u8> ctl, rot;
        };
        auto step = [&](u8 x, u8 y) {
            reset(m, base);
            w32(m, work + ks::kPadState, 1);  // running, unlocked, not waiting for a turn
            w32(m, work + ks::kPadLockEvent, 0);
            w32(m, work + ks::kPadLockNpc, 0);
            w32(m, gpv(ks::kGpPadSpeed), 0);
            w16(m, ks::kPadHeld, 0);
            w16(m, ks::kPadPressed, 0);
            w8(m, ks::kPadStickLX, x);
            w8(m, ks::kPadStickLX + 1, y);
            w8(m, ks::kPadStickLX + 2, 0x80);
            w8(m, ks::kPadStickLX + 3, 0x80);
            const hgp::Run r = hgp::pair(m, &recomp_gen::fn_sub_1E05B0_001e05b0, &recomp_gen::fn_sub_1E05B0_001e05b0__recomp,
                                         Args{pad, 0, 0, 0}, 1, "sub_1E05B0");
            return Out{r.stopped, r32(m, gpv(ks::kGpPadSpeed)), std::vector<u8>(m.at(ctl), m.at(ctl) + 0x100),
                       std::vector<u8>(m.at(rotWork), m.at(rotWork) + 0x80)};
        };
        // words that are no longer close (floats more than 0.02 apart relative to 1 + |b|, or non-floats that differ)
        auto far_words = [](const std::vector<u8>& a, const std::vector<u8>& b) {
            int n = 0;
            for (std::size_t k = 0; k + 4 <= a.size(); k += 4) {
                float fa, fb;
                std::memcpy(&fa, &a[k], 4);
                std::memcpy(&fb, &b[k], 4);
                if (std::memcmp(&a[k], &b[k], 4) == 0) continue;
                if (!(std::isfinite(fa) && std::isfinite(fb) && std::fabs(fa - fb) <= 0.02f * (1.0f + std::fabs(fb)))) ++n;
            }
            return n;
        };
        for (const u8 y : {u8{0xFF}, u8{0x01}}) {
            const Out o80 = step(0x80, y), o81 = step(0x81, y);
            REQUIRE_FALSE(o80.stopped);
            REQUIRE_FALSE(o81.stopped);
            CHECK_MESSAGE(o80.speed == o81.speed, std::string(snap) << " y " << int(y));
            CHECK_MESSAGE(far_words(o80.ctl, o81.ctl) == 0, std::string(snap) << " y " << int(y) << ": the controller");
            CHECK_MESSAGE(far_words(o80.rot, o81.rot) == 0, std::string(snap) << " y " << int(y) << ": the rotate task");
            ++checked;
        }
    }
    if (checked == 0) MESSAGE("SKIP: no field snapshot with the pad task");
    else MESSAGE(checked << " centred-x steps checked");
}

// The field root on the replay snapshots' live roots (climb: Tartarus floor 5 = 51/4, state 13; shop 8/4 and fusion 8/3:
// state 13; dorm 7/2 is inside an event): the running state only watches the shutdown word (26_field.md 2.2), the
// shutdown word leads to state 18 and state 18 returns -1 (the kwln kernel then destroys the task); the pack
// predicates say "loaded" when no request is pending (the .pac / .fpc are released once the field has loaded).
TEST_CASE("game(field4 root): the field root task and the pack predicates on the replay snapshots") {
    int checked = 0;
    for (const char* snap : kFieldSnapshots) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        const u32 rootTask = r32(m, kSField + fld::kRoot);
        if (rootTask == 0) continue;  // no field root in this snapshot
        const u32 work = r32(m, rootTask + game::f4::kTaskWork);
        const u32 state = r32(m, work + root::kState);
        CHECK(r16(m, work + root::kMajor) == static_cast<u16>(rs32(m, kSceneRecord + 0)));
        // the pack predicates (both requests released after the load)
        if (r32(m, gpv(game::f4::gpv::kPacRequest)) == 0 && r32(m, gpv(game::f4::gpv::kFpcRequest)) == 0) {
            CHECK(v0_of(call(m, "sub_1B08D0", {0, 0, 0, 0})) == 1);
            CHECK(v0_of(call(m, "sub_1B09B0", {0, 0, 0, 0})) == 1);
            CHECK(v0_of(call(m, "sub_1B07D0", {0, 0, 0, 0})) == 1);
        }
        if (state == 13) {
            hgp::Run r = call(m, "K_Field_UpdateFieldRootTask", {rootTask, 0, 0, 0});
            CHECK_FALSE(r.stopped);
            CHECK(v0_of(r) == 0);
            CHECK(r32(m, work + root::kState) == 13);
            w32(m, work + root::kShutdown, 1);  // K_Field_SetShouldShutdown's word
            r = call(m, "K_Field_UpdateFieldRootTask", {rootTask, 0, 0, 0}, 2);
            CHECK(v0_of(r) == 0);
            CHECK(r32(m, work + root::kState) == 18);
            r = call(m, "K_Field_UpdateFieldRootTask", {rootTask, 0, 0, 0}, 3);
            CHECK(v0_of(r) == -1);
            reset(m, base);
        }
        // the root's accessors of the shutdown / hold words and the exit request
        call(m, "sub_1BAA50", {rootTask, 1, 0, 0});
        call(m, "K_Field_SetShouldShutdown", {rootTask, 1, 0, 0});
        hgp::Run r = call(m, "sub_1BAAA0", {rootTask, 9, 4, 2});
        if (!r.stopped) {
            CHECK(r32(m, work + root::kState) == 17);
            CHECK(r16(m, work + root::kNextMajor) == 9);
            CHECK(r16(m, work + root::kNextMinor) == 4);
            CHECK(r16(m, work + root::kNextEntry) == 2);
        }
        ++checked;
        MESSAGE(std::string(snap) << ": root state " << state << ", field " << r16(m, work + root::kMajor) << "/" << r16(m, work + root::kMinor));
    }
    if (checked == 0) MESSAGE("SKIP: no replay snapshot");
}

// The boot loaders on the H_Cdvd stand-ins (stand_ins.h FakeCd: the files come from extracted/): each copies its file
// into the heap (or the floor table) byte for byte -- the main field script, fuka.bf, both dungeon tables, the
// social-link NPC table (its lists counted by their 0xFFFF records) and npccomu.bf.
TEST_CASE("game(field4 root): the boot data loaders copy the disc files (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const HwCheck hw = whole_ram_check();
    const auto field_bf = read_extracted("DATA/FIELD/SCRIPT/FIELD.BF");
    if (field_bf.empty()) {
        MESSAGE("SKIP: no extracted DATA/FIELD");
        return;
    }
    {
        const Case& c = find_case("K_Data_LoadFldMainScript");
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 1, c.name, hw);
        CHECK(r32(m, 0x7CE224) == field_bf.size());        // g_fldMainScriptSize
        CHECK(guest_equals(m, r32(m, 0x7CE228), field_bf));  // g_fldMainScriptPtr
    }
    {
        const auto fuka = read_extracted("DATA/FIELD/SCRIPT/FUKA.BF");
        const Case& c = find_case("sub_1B7BB0");
        run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 2, c.name, hw);
        CHECK(guest_equals(m, r32(m, 0x7CE220), fuka));
    }
    for (int fes = 0; fes < 2; ++fes) {
        const auto table = read_extracted(fes ? "DATA/FIELD/TABLE/DUNGEONFES.BIN" : "DATA/FIELD/TABLE/DUNGEONAT.BIN");
        const Case& c = find_case("sub_1B7C40");
        std::memset(m.at(game::f4::dngfloor::kTable), 0xEE, 0x2000);
        run_pair_si(m, c.hand, c.recomp, {S(fes), 0, 0, 0}, 3 + fes, c.name, hw);
        CHECK(guest_equals(m, game::f4::dngfloor::kTable, table));
        // DUNGEONAT.BIN: floor 1 = the entrance 32/2, floor 5 = the fixed floor 51/4 (climb_ref_17000's floor)
        if (!fes) {
            CHECK(r16(m, game::f4::dngfloor::kTable + 16 * 1) == 32);
            CHECK(r16(m, game::f4::dngfloor::kTable + 16 * 5) == 51);
            CHECK(r16(m, game::f4::dngfloor::kTable + 16 * 5 + 2) == 4);
        }
    }
    {
        const auto comu = read_extracted("DATA/FIELD/TABLE/COMUTBL.BIN");
        const Case& c = find_case("sub_1B8B40");
        w32(m, 0x7CE244, 0);
        run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 5, c.name, hw, install_field_world);
        if (!comu.empty()) {
            CHECK(guest_equals(m, r32(m, 0x7CE240), comu));
            CHECK(r32(m, 0x7CE248) == comu.size() / 128);
            u32 lists = 0;
            for (std::size_t i = 0; i + 1 < comu.size(); i += 128) lists += (comu[i] == 0xFF && comu[i + 1] == 0xFF);
            CHECK(r32(m, 0x7CE244) == lists);
        }
    }
    {
        const auto npccomu = read_extracted("DATA/FIELD/SCRIPT/NPCCOMU.BF");
        const Case& c = find_case("sub_1B8C40");
        run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 6, c.name, hw, install_field_world);
        if (!npccomu.empty()) {
            CHECK(r32(m, 0x7CE238) == npccomu.size());
            CHECK(guest_equals(m, r32(m, 0x7CE23C), npccomu));
        }
    }
}

// The per-field request functions build their paths from the scene record's ids (the H_Cdvd_Request / FileExists
// stand-ins record them): the field packs, the NPC table / messages / script and the ENV (the FBN / HBN / field
// script / MAP requests: test_field4_npc.cpp); with the .pac slot set, the loaders taken from the pack answer 1, no request.
TEST_CASE("game(field4 root): the field file requests and their paths (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const HwCheck hw = whole_ram_check();
    struct Req {
        const char* fn;
        Args args;
        const char* path;  // the path asked for (FileExists or Request)
    };
    const Req reqs[] = {
        {"sub_1B0870", {51, 4, 0, 0}, "field/pack/f051_004.pac"},
        {"sub_1B0950", {51, 4, 0, 0}, "field/pack/f051_004.fpc"},
        {"sub_1B8160", {0, 0, 0, 0}, "field/table/n051_004.bin"},
        {"sub_1B8680", {0, 0, 0, 0}, "field/script/nm051_004.bmd"},
        {"sub_1B88D0", {0, 0, 0, 0}, "field/script/ns051_004.bf"},
        {"sub_1B6100", {7, 0, 0, 0}, "field/env/f021_000.ENV"},  // a fixed floor 51..58 uses major - 30, sub 0
    };
    int seed = 1;
    for (const Req& q : reqs) {
        w32(m, gpv(game::f4::gpv::kPacRequest), 0);
        w32(m, gpv(game::f4::gpv::kFpcRequest), 0);
        const Case& c = find_case(q.fn);
        SiPair sp = run_pair_si(m, c.hand, c.recomp, q.args, static_cast<u32>(seed++), q.fn, hw, install_field_world);
        bool asked = false;  // FileExists logs the path, Request the built one (FakeCd::build_path)
        for (const StandInCall& call_ : sp.recomp->si.log)
            asked |= call_.text == q.path || call_.text == FakeCd::build_path(q.path);
        CHECK_MESSAGE(asked, q.fn << " did not ask for " << q.path);
        reset(m, base);
        write_rw_slots(m);
    }
    // with the .pac resident the per-field loaders take the files from it: 1, no request
    for (const char* fn : {"sub_1B8160", "sub_1B8680", "sub_1B88D0"}) {
        w32(m, gpv(game::f4::gpv::kPacRequest), kScratch);
        const Case& c = find_case(fn);
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {51, 4, 0, 0}, static_cast<u32>(seed++), fn, hw, install_field_world);
        CHECK(v0_of(sp.hw) == 1);
        CHECK(sp.recomp->si.log.empty());
    }
}

// The "try load" functions on a finished request (a loaded node made in guest memory with a real file's bytes): the
// NPC script / messages / schedule table are copied into the heap and sField points at the
// copies; the table's entry and list pointers follow its count; the node is destroyed (recorded).
TEST_CASE("game(field4 root): the per-field try-load functions copy a loaded file into the field (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    const auto bytes = read_extracted("DATA/FIELD/SCRIPT/DUNGEONAT.BF");
    if (bytes.empty()) {
        MESSAGE("SKIP: no extracted DATA/FIELD");
        return;
    }
    const HwCheck hw = whole_ram_check();
    const u32 node = kScratch, data = kScratch + 0x400;
    struct Load {
        const char* fn;
        s32 block, size;  // the sField words it fills (size -1: none)
    };
    const Load loads[] = {{"sub_1B8960", fld::kNpcScript, fld::kNpcScriptSize},
                          {"sub_1B8710", fld::kNpcMessages, -1},
                          {"sub_1B81F0", fld::kNpcTable, -1}};
    int seed = 1;
    for (const Load& l : loads) {
        reset(m, base);
        write_rw_slots(m);
        w32(m, gpv(game::f4::gpv::kPacRequest), 0);
        make_loaded_node(m, node, data, bytes);
        const Case& c = find_case(l.fn);
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {node, 51, 0, 0}, static_cast<u32>(seed++), l.fn, hw,
                                [](StandInWorld& w) {
                                    w.heap.install_all(w.si);
                                    w.si.install_recorder(kHCdvdDestroyFn, "H_Cdvd_Destroy", 1);
                                });
        CHECK(v0_of(sp.hw) == 1);
        const u32 copy = r32(m, kSField + l.block);
        CHECK(copy != 0);
        CHECK(guest_equals(m, copy, bytes));
        if (l.size >= 0) CHECK(r32(m, kSField + l.size) == bytes.size());
        if (std::string(l.fn) == "sub_1B81F0") {
            const u32 count = r32(m, copy);
            CHECK(r32(m, kSField + fld::kNpcTableCount) == count);
            CHECK(r32(m, kSField + fld::kNpcTableEntries) == copy + 32);
            CHECK(r32(m, kSField + fld::kNpcTableLists) == copy + 32 + 32 * count);
        }
        CHECK(sp.recomp->si.calls_to(kHCdvdDestroyFn) == 1);
    }
}
// --- end of the field4 tests ---

#else

TEST_CASE("game(field4 root): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
