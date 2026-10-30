// Pair tests for slice fusion_menu (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log.
// This file stays the generic sweep (random words, random pointers into a scratch window: mostly the bad-input and
// early-stop paths). The meaningful pairs of these 31 functions -- the real fusion route's snapshot, the real stock and
// list menus, the stand-in heap, the documented rules -- are in test_fusion.cpp.
#include "handgen_pairs.h"

#include "p3fes/game/fusion_menu.h"

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
void fn_sub_3D02F0_003d02f0(EEContext&);  // generated body
void fn_sub_3D02F0_003d02f0__recomp(EEContext&);  // recompiled
void fn_fclCombine_CreateCombineTasks_003d0310(EEContext&);  // generated body
void fn_fclCombine_CreateCombineTasks_003d0310__recomp(EEContext&);  // recompiled
void fn_fclCombine_UpdateCombineTask_003d03c0(EEContext&);  // generated body
void fn_fclCombine_UpdateCombineTask_003d03c0__recomp(EEContext&);  // recompiled
void fn_fclCombine_UpdateCombineDrawTask_003d0400(EEContext&);  // generated body
void fn_fclCombine_UpdateCombineDrawTask_003d0400__recomp(EEContext&);  // recompiled
void fn_fclCombine_UpdateCombineDraw2Task_003d0470(EEContext&);  // generated body
void fn_fclCombine_UpdateCombineDraw2Task_003d0470__recomp(EEContext&);  // recompiled
void fn_sub_3D04B0_003d04b0(EEContext&);  // generated body
void fn_sub_3D04B0_003d04b0__recomp(EEContext&);  // recompiled
void fn_sub_3D04D0_003d04d0(EEContext&);  // generated body
void fn_sub_3D04D0_003d04d0__recomp(EEContext&);  // recompiled
void fn_sub_3D0560_003d0560(EEContext&);  // generated body
void fn_sub_3D0560_003d0560__recomp(EEContext&);  // recompiled
void fn_sub_3D0610_003d0610(EEContext&);  // generated body
void fn_sub_3D0610_003d0610__recomp(EEContext&);  // recompiled
void fn_sub_3D2F00_003d2f00(EEContext&);  // generated body
void fn_sub_3D2F00_003d2f00__recomp(EEContext&);  // recompiled
void fn_sub_3D4CD0_003d4cd0(EEContext&);  // generated body
void fn_sub_3D4CD0_003d4cd0__recomp(EEContext&);  // recompiled
void fn_sub_3D74F0_003d74f0(EEContext&);  // generated body
void fn_sub_3D74F0_003d74f0__recomp(EEContext&);  // recompiled
void fn_sub_3DEDA0_003deda0(EEContext&);  // generated body
void fn_sub_3DEDA0_003deda0__recomp(EEContext&);  // recompiled
void fn_sub_3D9CC0_003d9cc0(EEContext&);  // generated body
void fn_sub_3D9CC0_003d9cc0__recomp(EEContext&);  // recompiled
void fn_sub_3D9EA0_003d9ea0(EEContext&);  // generated body
void fn_sub_3D9EA0_003d9ea0__recomp(EEContext&);  // recompiled
void fn_sub_3DA0C0_003da0c0(EEContext&);  // generated body
void fn_sub_3DA0C0_003da0c0__recomp(EEContext&);  // recompiled
void fn_sub_3DE290_003de290(EEContext&);  // generated body
void fn_sub_3DE290_003de290__recomp(EEContext&);  // recompiled
void fn_sub_3DD800_003dd800(EEContext&);  // generated body
void fn_sub_3DD800_003dd800__recomp(EEContext&);  // recompiled
void fn_sub_3DD9E0_003dd9e0(EEContext&);  // generated body
void fn_sub_3DD9E0_003dd9e0__recomp(EEContext&);  // recompiled
void fn_sub_3DDA80_003dda80(EEContext&);  // generated body
void fn_sub_3DDA80_003dda80__recomp(EEContext&);  // recompiled
void fn_sub_3DDB00_003ddb00(EEContext&);  // generated body
void fn_sub_3DDB00_003ddb00__recomp(EEContext&);  // recompiled
void fn_sub_3DE160_003de160(EEContext&);  // generated body
void fn_sub_3DE160_003de160__recomp(EEContext&);  // recompiled
void fn_sub_3D2D80_003d2d80(EEContext&);  // generated body
void fn_sub_3D2D80_003d2d80__recomp(EEContext&);  // recompiled
void fn_sub_3D3B00_003d3b00(EEContext&);  // generated body
void fn_sub_3D3B00_003d3b00__recomp(EEContext&);  // recompiled
void fn_sub_3D3CD0_003d3cd0(EEContext&);  // generated body
void fn_sub_3D3CD0_003d3cd0__recomp(EEContext&);  // recompiled
void fn_sub_3D4C80_003d4c80(EEContext&);  // generated body
void fn_sub_3D4C80_003d4c80__recomp(EEContext&);  // recompiled
void fn_sub_3D53E0_003d53e0(EEContext&);  // generated body
void fn_sub_3D53E0_003d53e0__recomp(EEContext&);  // recompiled
void fn_sub_3D5420_003d5420(EEContext&);  // generated body
void fn_sub_3D5420_003d5420__recomp(EEContext&);  // recompiled
void fn_sub_3D54A0_003d54a0(EEContext&);  // generated body
void fn_sub_3D54A0_003d54a0__recomp(EEContext&);  // recompiled
void fn_sub_3D4F30_003d4f30(EEContext&);  // generated body
void fn_sub_3D4F30_003d4f30__recomp(EEContext&);  // recompiled
void fn_sub_3D4F90_003d4f90(EEContext&);  // generated body
void fn_sub_3D4F90_003d4f90__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_3D02F0", 0x3D02F0, &recomp_gen::fn_sub_3D02F0_003d02f0, &recomp_gen::fn_sub_3D02F0_003d02f0__recomp},
    {"fclCombine_CreateCombineTasks", 0x3D0310, &recomp_gen::fn_fclCombine_CreateCombineTasks_003d0310, &recomp_gen::fn_fclCombine_CreateCombineTasks_003d0310__recomp},
    {"fclCombine_UpdateCombineTask", 0x3D03C0, &recomp_gen::fn_fclCombine_UpdateCombineTask_003d03c0, &recomp_gen::fn_fclCombine_UpdateCombineTask_003d03c0__recomp},
    {"fclCombine_UpdateCombineDrawTask", 0x3D0400, &recomp_gen::fn_fclCombine_UpdateCombineDrawTask_003d0400, &recomp_gen::fn_fclCombine_UpdateCombineDrawTask_003d0400__recomp},
    {"fclCombine_UpdateCombineDraw2Task", 0x3D0470, &recomp_gen::fn_fclCombine_UpdateCombineDraw2Task_003d0470, &recomp_gen::fn_fclCombine_UpdateCombineDraw2Task_003d0470__recomp},
    {"sub_3D04B0", 0x3D04B0, &recomp_gen::fn_sub_3D04B0_003d04b0, &recomp_gen::fn_sub_3D04B0_003d04b0__recomp},
    {"sub_3D04D0", 0x3D04D0, &recomp_gen::fn_sub_3D04D0_003d04d0, &recomp_gen::fn_sub_3D04D0_003d04d0__recomp},
    {"sub_3D0560", 0x3D0560, &recomp_gen::fn_sub_3D0560_003d0560, &recomp_gen::fn_sub_3D0560_003d0560__recomp},
    {"sub_3D0610", 0x3D0610, &recomp_gen::fn_sub_3D0610_003d0610, &recomp_gen::fn_sub_3D0610_003d0610__recomp},
    {"sub_3D2F00", 0x3D2F00, &recomp_gen::fn_sub_3D2F00_003d2f00, &recomp_gen::fn_sub_3D2F00_003d2f00__recomp},
    {"sub_3D4CD0", 0x3D4CD0, &recomp_gen::fn_sub_3D4CD0_003d4cd0, &recomp_gen::fn_sub_3D4CD0_003d4cd0__recomp},
    {"sub_3D74F0", 0x3D74F0, &recomp_gen::fn_sub_3D74F0_003d74f0, &recomp_gen::fn_sub_3D74F0_003d74f0__recomp},
    {"sub_3DEDA0", 0x3DEDA0, &recomp_gen::fn_sub_3DEDA0_003deda0, &recomp_gen::fn_sub_3DEDA0_003deda0__recomp},
    {"sub_3D9CC0", 0x3D9CC0, &recomp_gen::fn_sub_3D9CC0_003d9cc0, &recomp_gen::fn_sub_3D9CC0_003d9cc0__recomp},
    {"sub_3D9EA0", 0x3D9EA0, &recomp_gen::fn_sub_3D9EA0_003d9ea0, &recomp_gen::fn_sub_3D9EA0_003d9ea0__recomp},
    {"sub_3DA0C0", 0x3DA0C0, &recomp_gen::fn_sub_3DA0C0_003da0c0, &recomp_gen::fn_sub_3DA0C0_003da0c0__recomp},
    {"sub_3DE290", 0x3DE290, &recomp_gen::fn_sub_3DE290_003de290, &recomp_gen::fn_sub_3DE290_003de290__recomp},
    {"sub_3DD800", 0x3DD800, &recomp_gen::fn_sub_3DD800_003dd800, &recomp_gen::fn_sub_3DD800_003dd800__recomp},
    {"sub_3DD9E0", 0x3DD9E0, &recomp_gen::fn_sub_3DD9E0_003dd9e0, &recomp_gen::fn_sub_3DD9E0_003dd9e0__recomp},
    {"sub_3DDA80", 0x3DDA80, &recomp_gen::fn_sub_3DDA80_003dda80, &recomp_gen::fn_sub_3DDA80_003dda80__recomp},
    {"sub_3DDB00", 0x3DDB00, &recomp_gen::fn_sub_3DDB00_003ddb00, &recomp_gen::fn_sub_3DDB00_003ddb00__recomp},
    {"sub_3DE160", 0x3DE160, &recomp_gen::fn_sub_3DE160_003de160, &recomp_gen::fn_sub_3DE160_003de160__recomp},
    {"sub_3D2D80", 0x3D2D80, &recomp_gen::fn_sub_3D2D80_003d2d80, &recomp_gen::fn_sub_3D2D80_003d2d80__recomp},
    {"sub_3D3B00", 0x3D3B00, &recomp_gen::fn_sub_3D3B00_003d3b00, &recomp_gen::fn_sub_3D3B00_003d3b00__recomp},
    {"sub_3D3CD0", 0x3D3CD0, &recomp_gen::fn_sub_3D3CD0_003d3cd0, &recomp_gen::fn_sub_3D3CD0_003d3cd0__recomp},
    {"sub_3D4C80", 0x3D4C80, &recomp_gen::fn_sub_3D4C80_003d4c80, &recomp_gen::fn_sub_3D4C80_003d4c80__recomp},
    {"sub_3D53E0", 0x3D53E0, &recomp_gen::fn_sub_3D53E0_003d53e0, &recomp_gen::fn_sub_3D53E0_003d53e0__recomp},
    {"sub_3D5420", 0x3D5420, &recomp_gen::fn_sub_3D5420_003d5420, &recomp_gen::fn_sub_3D5420_003d5420__recomp},
    {"sub_3D54A0", 0x3D54A0, &recomp_gen::fn_sub_3D54A0_003d54a0, &recomp_gen::fn_sub_3D54A0_003d54a0__recomp},
    {"sub_3D4F30", 0x3D4F30, &recomp_gen::fn_sub_3D4F30_003d4f30, &recomp_gen::fn_sub_3D4F30_003d4f30__recomp},
    {"sub_3D4F90", 0x3D4F90, &recomp_gen::fn_sub_3D4F90_003d4f90, &recomp_gen::fn_sub_3D4F90_003d4f90__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(fusion_menu): every body equals its recompiled body on random worlds") {
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

#else

TEST_CASE("game(fusion_menu): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
