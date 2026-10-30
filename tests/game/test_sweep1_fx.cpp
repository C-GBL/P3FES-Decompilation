// Pair tests of slice sweep1, group fx (game/src/sweep/sweep1_fx.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the stand-in heap: the class-10 kind 3 / 7 constructors' block layout;
//   * hand-built filter cells: the two cell pulses' delay, negative phase and rectangle rules.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_331650_00331650(EEContext&);  // generated body
void fn_sub_331650_00331650__recomp(EEContext&);  // recompiled
void fn_sub_33B0D0_0033b0d0(EEContext&);  // generated body
void fn_sub_33B0D0_0033b0d0__recomp(EEContext&);  // recompiled
void fn_sub_33B1C0_0033b1c0(EEContext&);  // generated body
void fn_sub_33B1C0_0033b1c0__recomp(EEContext&);  // recompiled
void fn_sub_33B250_0033b250(EEContext&);  // generated body
void fn_sub_33B250_0033b250__recomp(EEContext&);  // recompiled
void fn_sub_33B2A0_0033b2a0(EEContext&);  // generated body
void fn_sub_33B2A0_0033b2a0__recomp(EEContext&);  // recompiled
void fn_sub_33BBE0_0033bbe0(EEContext&);  // generated body
void fn_sub_33BBE0_0033bbe0__recomp(EEContext&);  // recompiled
void fn_sub_33E700_0033e700(EEContext&);  // generated body
void fn_sub_33E700_0033e700__recomp(EEContext&);  // recompiled
void fn_sub_33E7F0_0033e7f0(EEContext&);  // generated body
void fn_sub_33E7F0_0033e7f0__recomp(EEContext&);  // recompiled
void fn_sub_33E890_0033e890(EEContext&);  // generated body
void fn_sub_33E890_0033e890__recomp(EEContext&);  // recompiled
void fn_sub_33E8E0_0033e8e0(EEContext&);  // generated body
void fn_sub_33E8E0_0033e8e0__recomp(EEContext&);  // recompiled
void fn_sub_33F2E0_0033f2e0(EEContext&);  // generated body
void fn_sub_33F2E0_0033f2e0__recomp(EEContext&);  // recompiled
void fn_sub_344AA0_00344aa0(EEContext&);  // generated body
void fn_sub_344AA0_00344aa0__recomp(EEContext&);  // recompiled
void fn_sub_344B70_00344b70(EEContext&);  // generated body
void fn_sub_344B70_00344b70__recomp(EEContext&);  // recompiled
void fn_sub_345080_00345080(EEContext&);  // generated body
void fn_sub_345080_00345080__recomp(EEContext&);  // recompiled
void fn_sub_3450D0_003450d0(EEContext&);  // generated body
void fn_sub_3450D0_003450d0__recomp(EEContext&);  // recompiled
void fn_sub_345970_00345970(EEContext&);  // generated body
void fn_sub_345970_00345970__recomp(EEContext&);  // recompiled
void fn_sub_348950_00348950(EEContext&);  // generated body
void fn_sub_348950_00348950__recomp(EEContext&);  // recompiled
void fn_sub_349090_00349090(EEContext&);  // generated body
void fn_sub_349090_00349090__recomp(EEContext&);  // recompiled
void fn_sub_349620_00349620(EEContext&);  // generated body
void fn_sub_349620_00349620__recomp(EEContext&);  // recompiled
void fn_sub_34DC00_0034dc00(EEContext&);  // generated body
void fn_sub_34DC00_0034dc00__recomp(EEContext&);  // recompiled
void fn_sub_34EAE0_0034eae0(EEContext&);  // generated body
void fn_sub_34EAE0_0034eae0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_331650", 0x331650, &recomp_gen::fn_sub_331650_00331650, &recomp_gen::fn_sub_331650_00331650__recomp},
    {"sub_33B0D0", 0x33B0D0, &recomp_gen::fn_sub_33B0D0_0033b0d0, &recomp_gen::fn_sub_33B0D0_0033b0d0__recomp},
    {"sub_33B1C0", 0x33B1C0, &recomp_gen::fn_sub_33B1C0_0033b1c0, &recomp_gen::fn_sub_33B1C0_0033b1c0__recomp},
    {"sub_33B250", 0x33B250, &recomp_gen::fn_sub_33B250_0033b250, &recomp_gen::fn_sub_33B250_0033b250__recomp},
    {"sub_33B2A0", 0x33B2A0, &recomp_gen::fn_sub_33B2A0_0033b2a0, &recomp_gen::fn_sub_33B2A0_0033b2a0__recomp},
    {"sub_33BBE0", 0x33BBE0, &recomp_gen::fn_sub_33BBE0_0033bbe0, &recomp_gen::fn_sub_33BBE0_0033bbe0__recomp},
    {"sub_33E700", 0x33E700, &recomp_gen::fn_sub_33E700_0033e700, &recomp_gen::fn_sub_33E700_0033e700__recomp},
    {"sub_33E7F0", 0x33E7F0, &recomp_gen::fn_sub_33E7F0_0033e7f0, &recomp_gen::fn_sub_33E7F0_0033e7f0__recomp},
    {"sub_33E890", 0x33E890, &recomp_gen::fn_sub_33E890_0033e890, &recomp_gen::fn_sub_33E890_0033e890__recomp},
    {"sub_33E8E0", 0x33E8E0, &recomp_gen::fn_sub_33E8E0_0033e8e0, &recomp_gen::fn_sub_33E8E0_0033e8e0__recomp},
    {"sub_33F2E0", 0x33F2E0, &recomp_gen::fn_sub_33F2E0_0033f2e0, &recomp_gen::fn_sub_33F2E0_0033f2e0__recomp},
    {"sub_344AA0", 0x344AA0, &recomp_gen::fn_sub_344AA0_00344aa0, &recomp_gen::fn_sub_344AA0_00344aa0__recomp},
    {"sub_344B70", 0x344B70, &recomp_gen::fn_sub_344B70_00344b70, &recomp_gen::fn_sub_344B70_00344b70__recomp},
    {"sub_345080", 0x345080, &recomp_gen::fn_sub_345080_00345080, &recomp_gen::fn_sub_345080_00345080__recomp},
    {"sub_3450D0", 0x3450D0, &recomp_gen::fn_sub_3450D0_003450d0, &recomp_gen::fn_sub_3450D0_003450d0__recomp},
    {"sub_345970", 0x345970, &recomp_gen::fn_sub_345970_00345970, &recomp_gen::fn_sub_345970_00345970__recomp},
    {"sub_348950", 0x348950, &recomp_gen::fn_sub_348950_00348950, &recomp_gen::fn_sub_348950_00348950__recomp},
    {"sub_349090", 0x349090, &recomp_gen::fn_sub_349090_00349090, &recomp_gen::fn_sub_349090_00349090__recomp},
    {"sub_349620", 0x349620, &recomp_gen::fn_sub_349620_00349620, &recomp_gen::fn_sub_349620_00349620__recomp},
    {"sub_34DC00", 0x34DC00, &recomp_gen::fn_sub_34DC00_0034dc00, &recomp_gen::fn_sub_34DC00_0034dc00__recomp},
    {"sub_34EAE0", 0x34EAE0, &recomp_gen::fn_sub_34EAE0_0034eae0, &recomp_gen::fn_sub_34EAE0_0034eae0__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 fx): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kParams = kScratch + 0x100;
constexpr u32 kCells = kScratch + 0x1000;

u32 rw_malloc_size(const SiPair& sp) {
    const std::vector<StandInCall> c = calls(sp, kRwSlotFns[0]);
    return c.empty() ? 0u : static_cast<u32>(c[0].args[0]);
}

}  // namespace

// The kind-object constructors on the stand-in heap (the mesh builders stood in): one RwMalloc block of 16 + 44 *
// count bytes whose head points at its records (+0) and at itself (+8).
TEST_CASE("game(sweep1 fx): the class-10 kind 3 / 7 constructors") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    for (const u32 count : {1u, 6u, 40u}) {
        for (const char* fn : {"sub_33B1C0", "sub_33E7F0"}) {
            SiPair sp = run_case(m, base, kCases, fn, {kParams, 0, 0, 0}, count, [&](Machine& mm) {
                std::memset(mm.at(kParams), 0, 0x100);
                w32(mm, kParams + 56, count);
            });
            const u32 blk = static_cast<u32>(v0_of(sp.hw));
            INFO(fn << " count " << count);
            CHECK(rw_malloc_size(sp) == 16u + 44u * count);
            REQUIRE(blk != 0u);
            CHECK(r32(m, blk + 0) == blk + 16);
            CHECK(r32(m, blk + 8) == blk);
        }
    }
}

// The screen-filter cell pulses: a delayed cell (sub_349090) counts its delay down with alpha 0; a cell with a negative
// phase (sub_349620) only advances it by the step +4 of the parameters; the other cells are paired.
TEST_CASE("game(sweep1 fx): the screen-filter cell pulses") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    auto setup = [&](Machine& mm) {
        std::memset(mm.at(kParams), 0, 0x100);
        std::memset(mm.at(kCells), 0, 52 * 4);
        w32(mm, kParams, 4);  // four cells
        wf32(mm, kParams + 4, 0.25f);
        wf32(mm, kParams + 8, 0.125f);
        w32(mm, kParams + 12, 0xC0000000u);  // max alpha 0xC0 in the top byte
        wf32(mm, kParams + 24, 0.5f);
        wf32(mm, kParams + 28, 0.0625f);
        wf32(mm, kParams + 32, 300.0f);
        wf32(mm, kParams + 36, 200.0f);
        w32(mm, kParams + 40, 64);
        w32(mm, kCells + 0, 3);            // cell 0: a delay of 3
        w8(mm, kCells + 15, 0x77);
        wf32(mm, kCells + 52 + 4, 0.1f);   // cell 1: a running phase
        wf32(mm, kCells + 104 + 0, -0.5f); // cell 2: a negative phase (sub_349620)
        wf32(mm, kCells + 156 + 0, 0.5f);
    };
    SiPair sp = run_case(m, base, kCases, "sub_349090", {kParams, kCells, 0, 0}, 1, setup);
    CHECK(r32(m, kCells + 0) == 2u);
    CHECK(r8(m, kCells + 15) == 0u);
    sp = run_case(m, base, kCases, "sub_349620", {kParams, kCells, 0, 0}, 2, setup);
    CHECK(rf32(m, kCells + 104) == -0.25f);
    // the cell with phase 0.5: its rectangle is the centre -+ size x phase
    CHECK(rf32(m, kCells + 156 + 28) == 300.0f);
    CHECK(rf32(m, kCells + 156 + 32) == 200.0f);
    CHECK(rf32(m, kCells + 156 + 36) == 300.0f - 32.0f);
    CHECK(rf32(m, kCells + 156 + 48) == 200.0f + 32.0f);
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 fx): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
