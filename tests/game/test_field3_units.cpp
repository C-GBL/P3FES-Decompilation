// Pair tests for slice field3, part units (game/src/field/field3_units.cpp: the field units of k_unit.c). Three layers:
//   * every body against its recompiled body on random worlds (tests/game/handgen_pairs.h: the whole register file and
//     cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus);
//   * the real field of the battle route after its fight (snapshot b_6700) on the stand-ins (stand_ins.h), with variants
//     that patch the scene to a random floor, and documented-rule checks on the recompiled run's output (the buckets, the
//     placement pickers, destroy / suspend / remove, shadow / Reaper / party creation, the reload paths, the boxes and
//     the special chest, the helper tasks and the forced Reaper);
//   * the field table loaders on the fake H_Cdvd layer over extracted/ and the filter setter.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field3_units.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
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

namespace p3fes::recomp_gen {
void fn_K_FldUnit_CreateReaper_001cfc50(EEContext&);  // generated body
void fn_K_FldUnit_CreateReaper_001cfc50__recomp(EEContext&);  // recompiled
void fn_sub_1CFDD0_001cfdd0(EEContext&);  // generated body
void fn_sub_1CFDD0_001cfdd0__recomp(EEContext&);  // recompiled
void fn_sub_1D00B0_001d00b0(EEContext&);  // generated body
void fn_sub_1D00B0_001d00b0__recomp(EEContext&);  // recompiled
void fn_sub_1D0110_001d0110(EEContext&);  // generated body
void fn_sub_1D0110_001d0110__recomp(EEContext&);  // recompiled
void fn_sub_1D0330_001d0330(EEContext&);  // generated body
void fn_sub_1D0330_001d0330__recomp(EEContext&);  // recompiled
void fn_sub_1D0390_001d0390(EEContext&);  // generated body
void fn_sub_1D0390_001d0390__recomp(EEContext&);  // recompiled
void fn_sub_1D03F0_001d03f0(EEContext&);  // generated body
void fn_sub_1D03F0_001d03f0__recomp(EEContext&);  // recompiled
void fn_sub_1D0880_001d0880(EEContext&);  // generated body
void fn_sub_1D0880_001d0880__recomp(EEContext&);  // recompiled
void fn_sub_1D0BC0_001d0bc0(EEContext&);  // generated body
void fn_sub_1D0BC0_001d0bc0__recomp(EEContext&);  // recompiled
void fn_sub_1D0E50_001d0e50(EEContext&);  // generated body
void fn_sub_1D0E50_001d0e50__recomp(EEContext&);  // recompiled
void fn_sub_1D1360_001d1360(EEContext&);  // generated body
void fn_sub_1D1360_001d1360__recomp(EEContext&);  // recompiled
void fn_sub_1D1DB0_001d1db0(EEContext&);  // generated body
void fn_sub_1D1DB0_001d1db0__recomp(EEContext&);  // recompiled
void fn_sub_1D1FA0_001d1fa0(EEContext&);  // generated body
void fn_sub_1D1FA0_001d1fa0__recomp(EEContext&);  // recompiled
void fn_sub_1D2210_001d2210(EEContext&);  // generated body
void fn_sub_1D2210_001d2210__recomp(EEContext&);  // recompiled
void fn_sub_1D22A0_001d22a0(EEContext&);  // generated body
void fn_sub_1D22A0_001d22a0__recomp(EEContext&);  // recompiled
void fn_sub_1D2300_001d2300(EEContext&);  // generated body
void fn_sub_1D2300_001d2300__recomp(EEContext&);  // recompiled
void fn_sub_1D2610_001d2610(EEContext&);  // generated body
void fn_sub_1D2610_001d2610__recomp(EEContext&);  // recompiled
void fn_sub_1D2A10_001d2a10(EEContext&);  // generated body
void fn_sub_1D2A10_001d2a10__recomp(EEContext&);  // recompiled
void fn_sub_1D36C0_001d36c0(EEContext&);  // generated body
void fn_sub_1D36C0_001d36c0__recomp(EEContext&);  // recompiled
void fn_sub_1D36F0_001d36f0(EEContext&);  // generated body
void fn_sub_1D36F0_001d36f0__recomp(EEContext&);  // recompiled
void fn_sub_1D39C0_001d39c0(EEContext&);  // generated body
void fn_sub_1D39C0_001d39c0__recomp(EEContext&);  // recompiled
void fn_sub_1D3A30_001d3a30(EEContext&);  // generated body
void fn_sub_1D3A30_001d3a30__recomp(EEContext&);  // recompiled
void fn_sub_1D3C10_001d3c10(EEContext&);  // generated body
void fn_sub_1D3C10_001d3c10__recomp(EEContext&);  // recompiled
void fn_sub_1D3C40_001d3c40(EEContext&);  // generated body
void fn_sub_1D3C40_001d3c40__recomp(EEContext&);  // recompiled
void fn_sub_1D3CE0_001d3ce0(EEContext&);  // generated body
void fn_sub_1D3CE0_001d3ce0__recomp(EEContext&);  // recompiled
void fn_sub_1D40B0_001d40b0(EEContext&);  // generated body
void fn_sub_1D40B0_001d40b0__recomp(EEContext&);  // recompiled
void fn_sub_1D40E0_001d40e0(EEContext&);  // generated body
void fn_sub_1D40E0_001d40e0__recomp(EEContext&);  // recompiled
void fn_sub_1D4180_001d4180(EEContext&);  // generated body
void fn_sub_1D4180_001d4180__recomp(EEContext&);  // recompiled
void fn_sub_1D4290_001d4290(EEContext&);  // generated body
void fn_sub_1D4290_001d4290__recomp(EEContext&);  // recompiled
void fn_sub_1D4360_001d4360(EEContext&);  // generated body
void fn_sub_1D4360_001d4360__recomp(EEContext&);  // recompiled
void fn_sub_1D43E0_001d43e0(EEContext&);  // generated body
void fn_sub_1D43E0_001d43e0__recomp(EEContext&);  // recompiled
void fn_sub_1D4460_001d4460(EEContext&);  // generated body
void fn_sub_1D4460_001d4460__recomp(EEContext&);  // recompiled
void fn_sub_1D4560_001d4560(EEContext&);  // generated body
void fn_sub_1D4560_001d4560__recomp(EEContext&);  // recompiled
void fn_sub_1D50C0_001d50c0(EEContext&);  // generated body
void fn_sub_1D50C0_001d50c0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"K_FldUnit_CreateReaper", 0x1CFC50, &recomp_gen::fn_K_FldUnit_CreateReaper_001cfc50, &recomp_gen::fn_K_FldUnit_CreateReaper_001cfc50__recomp},
    {"sub_1CFDD0", 0x1CFDD0, &recomp_gen::fn_sub_1CFDD0_001cfdd0, &recomp_gen::fn_sub_1CFDD0_001cfdd0__recomp},
    {"sub_1D00B0", 0x1D00B0, &recomp_gen::fn_sub_1D00B0_001d00b0, &recomp_gen::fn_sub_1D00B0_001d00b0__recomp},
    {"sub_1D0110", 0x1D0110, &recomp_gen::fn_sub_1D0110_001d0110, &recomp_gen::fn_sub_1D0110_001d0110__recomp},
    {"sub_1D0330", 0x1D0330, &recomp_gen::fn_sub_1D0330_001d0330, &recomp_gen::fn_sub_1D0330_001d0330__recomp},
    {"sub_1D0390", 0x1D0390, &recomp_gen::fn_sub_1D0390_001d0390, &recomp_gen::fn_sub_1D0390_001d0390__recomp},
    {"sub_1D03F0", 0x1D03F0, &recomp_gen::fn_sub_1D03F0_001d03f0, &recomp_gen::fn_sub_1D03F0_001d03f0__recomp},
    {"sub_1D0880", 0x1D0880, &recomp_gen::fn_sub_1D0880_001d0880, &recomp_gen::fn_sub_1D0880_001d0880__recomp},
    {"sub_1D0BC0", 0x1D0BC0, &recomp_gen::fn_sub_1D0BC0_001d0bc0, &recomp_gen::fn_sub_1D0BC0_001d0bc0__recomp},
    {"sub_1D0E50", 0x1D0E50, &recomp_gen::fn_sub_1D0E50_001d0e50, &recomp_gen::fn_sub_1D0E50_001d0e50__recomp},
    {"sub_1D1360", 0x1D1360, &recomp_gen::fn_sub_1D1360_001d1360, &recomp_gen::fn_sub_1D1360_001d1360__recomp},
    {"sub_1D1DB0", 0x1D1DB0, &recomp_gen::fn_sub_1D1DB0_001d1db0, &recomp_gen::fn_sub_1D1DB0_001d1db0__recomp},
    {"sub_1D1FA0", 0x1D1FA0, &recomp_gen::fn_sub_1D1FA0_001d1fa0, &recomp_gen::fn_sub_1D1FA0_001d1fa0__recomp},
    {"sub_1D2210", 0x1D2210, &recomp_gen::fn_sub_1D2210_001d2210, &recomp_gen::fn_sub_1D2210_001d2210__recomp},
    {"sub_1D22A0", 0x1D22A0, &recomp_gen::fn_sub_1D22A0_001d22a0, &recomp_gen::fn_sub_1D22A0_001d22a0__recomp},
    {"sub_1D2300", 0x1D2300, &recomp_gen::fn_sub_1D2300_001d2300, &recomp_gen::fn_sub_1D2300_001d2300__recomp},
    {"sub_1D2610", 0x1D2610, &recomp_gen::fn_sub_1D2610_001d2610, &recomp_gen::fn_sub_1D2610_001d2610__recomp},
    {"sub_1D2A10", 0x1D2A10, &recomp_gen::fn_sub_1D2A10_001d2a10, &recomp_gen::fn_sub_1D2A10_001d2a10__recomp},
    {"sub_1D36C0", 0x1D36C0, &recomp_gen::fn_sub_1D36C0_001d36c0, &recomp_gen::fn_sub_1D36C0_001d36c0__recomp},
    {"sub_1D36F0", 0x1D36F0, &recomp_gen::fn_sub_1D36F0_001d36f0, &recomp_gen::fn_sub_1D36F0_001d36f0__recomp},
    {"sub_1D39C0", 0x1D39C0, &recomp_gen::fn_sub_1D39C0_001d39c0, &recomp_gen::fn_sub_1D39C0_001d39c0__recomp},
    {"sub_1D3A30", 0x1D3A30, &recomp_gen::fn_sub_1D3A30_001d3a30, &recomp_gen::fn_sub_1D3A30_001d3a30__recomp},
    {"sub_1D3C10", 0x1D3C10, &recomp_gen::fn_sub_1D3C10_001d3c10, &recomp_gen::fn_sub_1D3C10_001d3c10__recomp},
    {"sub_1D3C40", 0x1D3C40, &recomp_gen::fn_sub_1D3C40_001d3c40, &recomp_gen::fn_sub_1D3C40_001d3c40__recomp},
    {"sub_1D3CE0", 0x1D3CE0, &recomp_gen::fn_sub_1D3CE0_001d3ce0, &recomp_gen::fn_sub_1D3CE0_001d3ce0__recomp},
    {"sub_1D40B0", 0x1D40B0, &recomp_gen::fn_sub_1D40B0_001d40b0, &recomp_gen::fn_sub_1D40B0_001d40b0__recomp},
    {"sub_1D40E0", 0x1D40E0, &recomp_gen::fn_sub_1D40E0_001d40e0, &recomp_gen::fn_sub_1D40E0_001d40e0__recomp},
    {"sub_1D4180", 0x1D4180, &recomp_gen::fn_sub_1D4180_001d4180, &recomp_gen::fn_sub_1D4180_001d4180__recomp},
    {"sub_1D4290", 0x1D4290, &recomp_gen::fn_sub_1D4290_001d4290, &recomp_gen::fn_sub_1D4290_001d4290__recomp},
    {"sub_1D4360", 0x1D4360, &recomp_gen::fn_sub_1D4360_001d4360, &recomp_gen::fn_sub_1D4360_001d4360__recomp},
    {"sub_1D43E0", 0x1D43E0, &recomp_gen::fn_sub_1D43E0_001d43e0, &recomp_gen::fn_sub_1D43E0_001d43e0__recomp},
    {"sub_1D4460", 0x1D4460, &recomp_gen::fn_sub_1D4460_001d4460, &recomp_gen::fn_sub_1D4460_001d4460__recomp},
    {"sub_1D4560", 0x1D4560, &recomp_gen::fn_sub_1D4560_001d4560, &recomp_gen::fn_sub_1D4560_001d4560__recomp},
    {"sub_1D50C0", 0x1D50C0, &recomp_gen::fn_sub_1D50C0_001d50c0, &recomp_gen::fn_sub_1D50C0_001d50c0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field3_units): every body equals its recompiled body on random worlds") {
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

// =====================================================================================================================
// The real field: the battle route back on the field after its fight (snapshot b_6700, vblank 6700: scene 51/1 "Thebel",
// three live shadows with models, resources and tasks, three party units, four placed treasure boxes, the special
// chest placed, placements of types 14..17, the 16 x 16 grid). Each case restores the whole snapshot, then pairs the
// two bodies on stand-ins (stand_ins.h: the heap, printf / sprintf, the H_Cdvd layer, recorders for every callee this
// build does not emit), comparing the whole RAM, the scratchpad, every GPR, HI/LO, the register file at every check
// point, the dead stack and the stand-ins' logs; documented rules are checked on the recompiled run's output.
// Variants patch the scene record to a random floor (major 21, minor 0) so the random-floor paths run on real data.
// =====================================================================================================================
namespace {

constexpr u32 kEc = 0x86EDA0u, kPc = 0x8717A0u, kUnitSize = 448u;
constexpr u32 kBoxes = 0x86BE80u, kBoxSize = 312u;
constexpr u32 kBuckets = 0x86B180u;
constexpr u32 kSpecial = 0x86E580u;
constexpr u32 kSceneSlot = 0x7CD540u;            // gp-22448 -> the scene record
constexpr u32 kLiveEc = 0x7CE28Cu, kBoxCount = 0x7CE288u, kEncountSlot = 0x7CE4A8u;
constexpr u32 kFlagWords = 0x83A21Cu;           // g_datFlagWords (datGetFlag)
constexpr u32 kScratch = 0x01EE0000u;           // inside the stand-in heap's arena, far above its first blocks
constexpr u32 kFakeModel = 0x01EF0000u;         // the model handle the model recorders return (zeroed)
constexpr u32 kFakeTask = 0x01EF1000u;          // the task the effect-task recorder returns (+60 -> a zeroed work)
constexpr u32 kSnapInstance = 0x1876A90u;       // b_6700: shadow 1's encounter instance (u16 +2 count, +4 DatUnits)
constexpr u32 kSnapResId = 0x465u;              // b_6700: shadow 1's scene resource id (type 1)
constexpr u32 kSnapBoxResId = 0x2BFEu;          // b_6700: box 0's scene resource id (type 10)
constexpr u32 kSnapContents = 0x8AA58Cu;        // b_6700: box 0's contents (ENCOUNT section 4, item 4004)

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
float rdf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void wr32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wrf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }

const std::vector<u8>& snapshot() {
    static const std::vector<u8> s = read_snapshot("b_6700");
    return s;
}
Machine* snap_machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        return mm;
    }();
    return m;
}
// The whole snapshot back in place; `random_floor` patches the scene ids to 21/0.
void restore(Machine& m, bool random_floor = false) {
    copy_from_snapshot(m, snapshot(), 0, EEMemory::kMainRamSize);
    std::memset(m.at(kFakeModel), 0, 0x2000);
    wr32(m, kFakeTask + 60, kFakeTask + 0x100);
    std::memset(m.at(kScratch), 0, 0x2000);
    if (random_floor) {
        const u32 scene = rd32(m, kSceneSlot);
        wr32(m, scene + 0, 21);
        wr32(m, scene + 4, 0);
    }
}

// The placements of one type: the scene record's resource manager (+8), list head = manager + 4 * type, next at +248.
std::vector<u32> placements(Machine& m, u32 type) {
    std::vector<u32> out;
    const u32 scene = rd32(m, kSceneSlot);
    const u32 mgr = scene ? rd32(m, scene + 8) : 0;
    for (u32 r = mgr ? rd32(m, mgr + 4 * type) : 0; r != 0 && out.size() < 256; r = rd32(m, r + 248)) out.push_back(r);
    return out;
}

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// Every callee of the unit bodies (and of their replaced callees) that this build does not emit, as a recorder.
WorldSetup unit_world(u32 instance = kSnapInstance) {
    return [instance](StandInWorld& w) {
        install_standard(w);
        StandIns& s = w.si;
        s.install_recorder(0x2FF3E0u, "datUnitCreateEc", instance);
        s.install_recorder(0x2FF340u, "datUnitCreatePc", instance);
        s.install_recorder(0x2FF760u, "datUnitDestroyGenus");
        s.install_recorder(0x431670u, "Y_Npc_CreateNpcThinkTask");
        s.install_recorder(0x44AD20u, "Y_Stratum_CreateEneThinkTask");
        s.install_recorder(0x1D78C0u, "K_Encount_PickEncounter", kSnapContents);
        s.install_recorder(0x182D90u, "sub_182D90");
        s.install_recorder(0x1A5EA0u, "sub_1A5EA0");
        s.install_recorder(0x1A91B0u, "sub_1A91B0", 7);
        s.install_recorder(0x1A92D0u, "sub_1A92D0");
        s.install_recorder(0x1A9400u, "sub_1A9400");
        s.install_recorder(0x1CD9A0u, "sub_1CD9A0", kFakeModel);
        s.install_recorder(0x1DD460u, "sub_1DD460", kFakeTask);
        s.install_recorder(0x1DDE00u, "sub_1DDE00", 3);
        s.install_recorder(0x316E00u, "sub_316E00", kFakeModel);
        s.install_recorder(0x316F70u, "sub_316F70", 1);
        // the model band (sub_317450 clone, sub_3174E0 free, sub_3182D0 animation, sub_318B70 frame) is hand-written
        // and always runs; what it reaches that this build does not emit is stood in here: the clone's allocation
        // (sub_316690 -> the zeroed fake model) and copy, the animation lookups, the free path's helpers
        s.install_recorder(0x316690u, "sub_316690", kFakeModel);
        s.install_recorder(0x3170C0u, "sub_3170C0");
        s.install_recorder(0x314850u, "sub_314850");
        s.install_recorder(0x318620u, "sub_318620");
        s.install_recorder(0x3138E0u, "sub_3138E0");
        s.install_recorder(0x31EF80u, "sub_31EF80");
        s.install_recorder(0x319770u, "sub_319770");
        s.install_recorder(0x491EA0u, "sub_491EA0");
        s.install_recorder(0x3132C0u, "sub_3132C0");
        s.install_recorder(0x313BE0u, "sub_313BE0");
        s.install_recorder(0x313E60u, "sub_313E60");
        s.install_recorder(0x1A7710u, "sub_1A7710");
        s.install_recorder(0x3196F0u, "sub_3196F0");
        s.install_recorder(0x1EF340u, "sub_1EF340");
        s.install_recorder(0x31D790u, "sub_31D790");
        s.install_recorder(0x31EEE0u, "sub_31EEE0");
        // further not-emitted functions the real model / RW code can reach (tools: the reach of the pseudocode callee lists)
        s.install_recorder(0x314D30u, "sub_314D30");
        s.install_recorder(0x313490u, "sub_313490");
        s.install_recorder(0x324BD0u, "sub_324BD0");
        s.install_recorder(0x3252A0u, "sub_3252A0");
        s.install_recorder(0x325920u, "sub_325920");
        s.install_recorder(0x4663D0u, "sub_4663D0");
        s.install_recorder(0x498720u, "sub_498720");
        s.install_recorder(0x498E70u, "sub_498E70");
        s.install_recorder(0x4B6980u, "sub_4B6980");
        s.install_recorder(0x4B6EB0u, "sub_4B6EB0");
        s.install_recorder(0x4B78B0u, "sub_4B78B0");
        s.install_recorder(0x1948B0u, "sub_1948B0");
        s.install_recorder(0x109AE0u, "sub_109AE0");
        s.install_recorder(0x109DF0u, "sub_109DF0");
        s.install_recorder(0x10A0E0u, "sub_10A0E0");
        s.install_recorder(0x10A240u, "sub_10A240");
        s.install_recorder(0x51DF58u, "sceSkSsSESQ_Control");
        s.install_recorder(0x51E028u, "sceSkSsSESQ_Status");
        s.install_recorder(0x523730u, "isinf");
        s.install_recorder(0x523778u, "isnan");
        s.install_recorder(0x3B6030u, "sub_3B6030", kSnapResId);
        s.install_recorder(0x3B65D0u, "sub_3B65D0", kSnapBoxResId);
        s.install_recorder(0x3B7090u, "sub_3B7090");
        s.install_recorder(0x434F60u, "sub_434F60");
        s.install_recorder(0x4C2F10u, "sub_4C2F10");
        s.install_recorder(0x4C2CC0u, "sub_4C2CC0");  // RW matrix helpers behind the controller turns
        s.install_recorder(0x4C2D20u, "sub_4C2D20");
        s.install_recorder(0x1008B0u, "H_Cdvd_FileExists", 1);
    };
}

namespace rg = p3fes::recomp_gen;

#define NEED_SNAPSHOT()                                                 \
    Machine* mp = snap_machine();                                       \
    if (!mp) {                                                          \
        MESSAGE("SKIP: no ELF at " << elf_path());                      \
        return;                                                         \
    }                                                                   \
    if (snapshot().empty()) {                                           \
        MESSAGE("SKIP: no extracted/_ours/b_6700 snapshot");            \
        return;                                                         \
    }                                                                   \
    Machine& m = *mp

SiPair pair_on(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
               const WorldSetup& setup = unit_world()) {
    return run_pair_si(m, hand, recomp, args, seed, what, full_check(), setup);
}
u32 v0_of(const SiPair& p) { return static_cast<u32>(p.hw.recomp.base.v0); }

}  // namespace

TEST_CASE("game(field3_units): the proximity buckets on the real field and on a random-floor patch") {
    NEED_SNAPSHOT();
    for (int variant = 0; variant < 2; ++variant) {
        restore(m, variant == 1);
        // the bodies' inputs, read before the pair
        std::vector<u32> live, boxes;
        for (u32 i = 0; i < 24; ++i)
            if (rd32(m, kEc + kUnitSize * i + 72)) live.push_back(kEc + kUnitSize * i);
        for (u32 i = 0; i < 32; ++i)
            if (rd32(m, kBoxes + kBoxSize * i) == 1) boxes.push_back(kBoxes + kBoxSize * i);
        const bool special = rd32(m, kSpecial) == 1;
        REQUIRE(live.size() == 3);
        pair_on(m, rg::fn_sub_1D2A10_001d2a10, rg::fn_sub_1D2A10_001d2a10__recomp, {0, 0, 0, 0}, 1, "sub_1D2A10");
        if (variant == 0) {
            // off random floors one flat list: shadows 0..23, boxes 24..47, the special chest 48
            for (u32 k = 0; k < 24; ++k) CHECK(rd32(m, kBuckets + 4 * k) == (k < live.size() ? live[k] : 0u));
            for (u32 k = 0; k < 24; ++k) CHECK(rd32(m, kBuckets + 96 + 4 * k) == (k < boxes.size() ? boxes[k] : 0u));
            CHECK(rd32(m, kBuckets + 192) == (special ? kSpecial : 0u));
        } else {
            // on a random floor every non-Reaper shadow is in the bucket of its own position's 4 x 4 cell block
            for (u32 u : live) {
                if (rd32(m, u + 396) == 4) continue;
                const u32 model = rd32(m, u + 80);
                const float x = rdf(m, model + 48), z = rdf(m, model + 56);
                const int bx = static_cast<int>(static_cast<float>(static_cast<int>(x + 400.0f)) / 800.0f) / 4;
                const int bz = static_cast<int>(static_cast<float>(static_cast<int>(z + 400.0f)) / 800.0f) / 4;
                if (bx < 0 || bx > 3 || bz < 0 || bz > 3) continue;
                const u32 bucket = kBuckets + 784u * static_cast<u32>(bz) + 196u * static_cast<u32>(bx);  // z rows of 4 x 49 words
                bool found = false;
                for (u32 k = 0; k < 24; ++k) found = found || rd32(m, bucket + 4 * k) == u;
                CHECK(found);
            }
        }
    }
}

TEST_CASE("game(field3_units): placement pickers for shadows and treasure on the real placements") {
    NEED_SNAPSHOT();
    std::mt19937 rng{0xF3A0001};
    int pairs = 0;
    for (int i = 0; i < 24; ++i) {
        const bool random_floor = (i & 1) != 0;
        restore(m, random_floor);
        const std::vector<u32> t15 = placements(m, 15), t16 = placements(m, 16);
        REQUIRE(t15.size() == 4);
        REQUIRE(t16.size() == 4);
        const u32 index = rng() % 6, wanted = rng() % 8;
        SiPair a = pair_on(m, rg::fn_sub_1D0880_001d0880, rg::fn_sub_1D0880_001d0880__recomp, {index, wanted, 0, 0}, rng(), "sub_1D0880");
        if (!random_floor) CHECK(v0_of(a) == (index < t15.size() ? t15[index] : 0u));  // off random floors: the index-th
        restore(m, random_floor);
        SiPair b = pair_on(m, rg::fn_sub_1D2300_001d2300, rg::fn_sub_1D2300_001d2300__recomp, {index, wanted, 0, 0}, rng(), "sub_1D2300");
        if (!random_floor) CHECK(v0_of(b) == (index < t16.size() ? t16[index] : 0u));
        if (random_floor && v0_of(b) != 0) {
            // a picked treasure placement is at least 500 from the hero
            const u32 hero = rd32(m, kPc + 80);
            const float dx = rdf(m, v0_of(b) + 256) - rdf(m, hero + 48), dy = rdf(m, v0_of(b) + 260) - rdf(m, hero + 52),
                        dz = rdf(m, v0_of(b) + 264) - rdf(m, hero + 56);
            CHECK(dx * dx + dy * dy + dz * dz >= 499.0f * 499.0f);
        }
        restore(m, random_floor);
        const u32 n = rng() % 5;
        pair_on(m, rg::fn_sub_1D0BC0_001d0bc0, rg::fn_sub_1D0BC0_001d0bc0__recomp, {kScratch, n, 0, 0}, rng(), "sub_1D0BC0");
        if (random_floor) {
            // every filled output entry is a copy of one of the placements
            for (u32 k = 0; k < n && k < t15.size(); ++k) {
                bool same = false;
                for (u32 p : t15) same = same || std::memcmp(m.at(kScratch + 272 * k), m.at(p), 272) == 0;
                CHECK(same);
            }
        } else {
            for (u32 k = 0; k < 816; ++k) CHECK(m.at(kScratch)[k] == 0);  // only the clear off random floors
        }
        pairs += 3;
    }
    MESSAGE("placement pickers: " << pairs << " pairs");
}

TEST_CASE("game(field3_units): destroying, suspending and removing units and boxes") {
    NEED_SNAPSHOT();
    std::mt19937 rng{0xF3A0002};
    const u32 units[] = {kEc, kEc + kUnitSize, kEc + 2 * kUnitSize, kEc + 3 * kUnitSize, kPc, kPc + kUnitSize, kPc + 2 * kUnitSize, kPc + 3 * kUnitSize};
    for (u32 u : units) {
        restore(m);
        const u32 live0 = rd32(m, kLiveEc), was = rd32(m, u + 72), kind = rd32(m, u + 396);
        const std::vector<u8> before = m.bytes(u, kUnitSize);
        pair_on(m, rg::fn_sub_1D0110_001d0110, rg::fn_sub_1D0110_001d0110__recomp, {u, 0, 0, 0}, rng(), "sub_1D0110");
        if (was != 0) {
            for (u32 off : {72u, 80u, 84u, 364u, 368u, 372u, 376u, 384u, 436u}) CHECK(rd32(m, u + off) == 0);
            for (u32 k = 408; k < 413; ++k) CHECK(m.at(u)[k] == 0);
            CHECK(rd32(m, kLiveEc) == live0 - (kind != 0 ? 1u : 0u));
            for (u32 k = 0; k < 24; ++k) CHECK(rd32(m, kBuckets + 4 * k) != u);  // gone from the buckets
        } else {
            CHECK(m.bytes(u, kUnitSize) == before);
        }
    }
    restore(m);
    pair_on(m, rg::fn_sub_1D0390_001d0390, rg::fn_sub_1D0390_001d0390__recomp, {0, 0, 0, 0}, 1, "sub_1D0390");
    for (u32 i = 0; i < 24; ++i) CHECK(rd32(m, kEc + kUnitSize * i + 72) == 0);
    CHECK(rd32(m, kLiveEc) == 0);
    restore(m);
    pair_on(m, rg::fn_sub_1D0330_001d0330, rg::fn_sub_1D0330_001d0330__recomp, {0, 0, 0, 0}, 2, "sub_1D0330");
    for (u32 i = 0; i < 4; ++i) CHECK(rd32(m, kPc + kUnitSize * i + 72) == 0);
    restore(m);
    pair_on(m, rg::fn_sub_1D4180_001d4180, rg::fn_sub_1D4180_001d4180__recomp, {0, 0, 0, 0}, 3, "sub_1D4180");
    for (u32 i = 0; i < 3; ++i) CHECK(rd32(m, kPc + kUnitSize * i + 384) == 0);  // the party's badstat tasks gone
    for (u32 b = 0; b < 4; ++b) {
        restore(m);
        const u32 box = kBoxes + kBoxSize * b, count = rd32(m, kBoxCount);
        pair_on(m, rg::fn_sub_1D22A0_001d22a0, rg::fn_sub_1D22A0_001d22a0__recomp, {box, 0, 0, 0}, rng(), "sub_1D22A0");
        for (u32 k = 0; k < 12; ++k) CHECK(m.at(box)[k] == 0);
        CHECK(rd32(m, kBoxCount) == count - 1);
        for (u32 k = 0; k < 24; ++k) CHECK(rd32(m, kBuckets + 96 + 4 * k) != box);
    }
}

TEST_CASE("game(field3_units): creating the Reaper and the party on the real field") {
    NEED_SNAPSHOT();
    std::mt19937 rng{0xF3A0003};
    const u32 tbl0 = [&] {
        restore(m);
        return rd32(m, kEncountSlot);
    }();
    for (int i = 0; i < 8; ++i) {
        restore(m);
        const bool flag = (i & 3) == 3;
        if (flag) wr32(m, kFlagWords + 4 * (5141 >> 5), rd32(m, kFlagWords + 4 * (5141 >> 5)) | (1u << (5141 & 31)));
        const float pos[3] = {static_cast<float>(rng() % 12800), 0.0f, static_cast<float>(rng() % 12800)};
        for (int k = 0; k < 3; ++k) wrf(m, kScratch + 4 * k, pos[k]);
        u32 slot = 0;
        for (u32 s = 0; s < 24 && slot == 0; ++s)
            if (rd32(m, kEc + kUnitSize * s + 72) == 0) slot = kEc + kUnitSize * s;
        const u32 live0 = rd32(m, kLiveEc);
        SiPair p = pair_on(m, rg::fn_K_FldUnit_CreateReaper_001cfc50, rg::fn_K_FldUnit_CreateReaper_001cfc50__recomp, {1, kScratch, 0, 0},
                           rng(), "K_FldUnit_CreateReaper");
        if (flag) {
            CHECK(v0_of(p) == 0);
            continue;
        }
        REQUIRE(v0_of(p) == slot);
        CHECK(rd32(m, slot + 76) == tbl0 + 28 * 506);  // encounter 506
        CHECK(rd32(m, slot + 396) == 4);
        CHECK(rd32(m, slot + 400) == 0);
        CHECK(rd32(m, slot + 388) == 1000);
        CHECK(rdf(m, slot + 344) == pos[0]);
        CHECK(rdf(m, slot + 352) == pos[2]);
        CHECK(rd16(m, slot + 404) == static_cast<u16>(static_cast<int>((pos[0] + 400.0f) / 800.0f)));
        CHECK(rd32(m, kLiveEc) == live0 + 1);
    }
    // the party: cleared units, then K_FldUnit_CreateAllPc for a few entries (the reserve scripts stay pending)
    for (u32 entry : {0u, 1u, 3u, 0xFFFFu}) {
        restore(m);
        std::memset(m.at(kPc), 0, 4 * kUnitSize);
        pair_on(m, rg::fn_sub_1D03F0_001d03f0, rg::fn_sub_1D03F0_001d03f0__recomp, {entry, 0, 0, 0}, entry + 7, "sub_1D03F0");
        CHECK(rd32(m, kPc + 72) == kSnapInstance);  // the hero first
        CHECK(rd16(m, kPc + 424) == 1);
        u32 want = 0;
        for (u32 r : placements(m, 14))
            if ((rd16(m, r) & 0x3FF) == (entry & 0xFFFF) && want == 0) want = r;
        CHECK(rd32(m, kPc + 360) == want);
    }
}

TEST_CASE("game(field3_units): finishing and re-creating units, boxes and the special chest after a reload") {
    NEED_SNAPSHOT();
    std::mt19937 rng{0xF3A0004};
    for (u32 slot = 0; slot < 4; ++slot) {
        restore(m);
        const u32 u = kEc + kUnitSize * slot;
        const bool clear_res = (slot & 1) != 0;
        if (clear_res) wr32(m, u + 84, 0);
        SiPair p = pair_on(m, rg::fn_sub_1CFDD0_001cfdd0, rg::fn_sub_1CFDD0_001cfdd0__recomp, {slot, 0, 0, 0}, rng(), "sub_1CFDD0");
        CHECK(v0_of(p) == 1);  // done (the model recorder says loaded)
        if (clear_res && rd32(m, u + 72) != 0) CHECK(rd32(m, u + 84) != 0);
    }
    restore(m);
    for (u32 s = 0; s < 4; ++s) wr32(m, kEc + kUnitSize * s + 84, 0);
    pair_on(m, rg::fn_sub_1D00B0_001d00b0, rg::fn_sub_1D00B0_001d00b0__recomp, {0, 0, 0, 0}, 11, "sub_1D00B0");
    for (u32 skip = 0; skip < 2; ++skip) {
        restore(m);
        pair_on(m, rg::fn_sub_1D0E50_001d0e50, rg::fn_sub_1D0E50_001d0e50__recomp, {skip, 0, 0, 0}, 12 + skip, "sub_1D0E50");
        CHECK(rd32(m, kPc + 84) != 0);
    }
    restore(m);
    pair_on(m, rg::fn_sub_1D1360_001d1360, rg::fn_sub_1D1360_001d1360__recomp, {0, 0, 0, 0}, 14, "sub_1D1360");
    // boxes: one model, all models, all boxes placed again
    for (u32 b = 0; b < 4; ++b) {
        restore(m);
        const u32 box = kBoxes + kBoxSize * b, count = rd32(m, kBoxCount);
        pair_on(m, rg::fn_sub_1D1DB0_001d1db0, rg::fn_sub_1D1DB0_001d1db0__recomp, {box, box + 12, 1022 - b, 0}, rng(), "sub_1D1DB0");
        CHECK(rd16(m, box + 8) == kSnapBoxResId);
        u32 res = 0;  // the box's scene resource (type 10, the id the resource recorder returns)
        for (u32 r : placements(m, 10))
            if (rd16(m, r) == kSnapBoxResId && res == 0) res = r;
        REQUIRE(res != 0);
        CHECK(rd32(m, box + 308) == rd32(m, res + 300));  // the blob-shadow model the resource holds
        CHECK(rd32(m, box + 308) != 0);
        CHECK(rd32(m, kBoxCount) == count + 1);
    }
    restore(m);
    pair_on(m, rg::fn_sub_1D2210_001d2210, rg::fn_sub_1D2210_001d2210__recomp, {0, 0, 0, 0}, 15, "sub_1D2210");
    for (int variant = 0; variant < 2; ++variant) {
        restore(m, variant == 1);
        pair_on(m, rg::fn_sub_1D1FA0_001d1fa0, rg::fn_sub_1D1FA0_001d1fa0__recomp, {0, 0, 0, 0}, 16 + variant, "sub_1D1FA0");
        u32 placed = 0;
        for (u32 i = 0; i < 32; ++i) placed += rd32(m, kBoxes + kBoxSize * i) == 1 ? 1u : 0u;
        CHECK(rd32(m, kBoxCount) == placed);
        MESSAGE("sub_1D1FA0 variant " << variant << ": " << placed << " boxes placed");
        for (u32 i = 0; i < placed; ++i) CHECK(rd32(m, kBoxes + kBoxSize * i + 284) == kSnapContents);
    }
    // the special chest from each state, the floor percentage drawn at random
    for (int i = 0; i < 12; ++i) {
        restore(m, (i & 4) != 0);
        const u32 state = static_cast<u32>(i % 3);
        wr32(m, kSpecial, state);
        const u32 field = 0x869F60u;
        const u16 pct = static_cast<u16>(rng() % 120);
        std::memcpy(m.at(field + 68), &pct, 2);
        pair_on(m, rg::fn_sub_1D2610_001d2610, rg::fn_sub_1D2610_001d2610__recomp, {0, 0, 0, 0}, rng(), "sub_1D2610");
        const u32 after = rd32(m, kSpecial);
        MESSAGE("sub_1D2610 from state " << state << " (pct " << pct << "): state " << after);
        if (state == 0) CHECK((after == 1 || after == 2));
        else CHECK(after == state);
        if (state == 0 && after == 1) {
            bool same = false;
            for (u32 p : placements(m, 17)) same = same || std::memcmp(m.at(kSpecial + 4), m.at(p), 272) == 0;
            CHECK(same);
        }
    }
}

TEST_CASE("game(field3_units): the helper tasks and the scheduler's forced Reaper") {
    NEED_SNAPSHOT();
    std::mt19937 rng{0xF3A0005};
    // task creators (RwMalloc'd work on the stand-in heap, the hand-written kwln kernel)
    for (int i = 0; i < 4; ++i) {
        restore(m);
        SiPair a = pair_on(m, rg::fn_sub_1D36F0_001d36f0, rg::fn_sub_1D36F0_001d36f0__recomp, {0, 0, 0, 0}, rng(), "sub_1D36F0");
        CHECK(v0_of(a) != 0);
        restore(m);
        const u32 model = rd32(m, kEc + kUnitSize + 80);
        SiPair b = pair_on(m, rg::fn_sub_1D3C40_001d3c40, rg::fn_sub_1D3C40_001d3c40__recomp, {0, model, 0, 0}, rng(), "sub_1D3C40");
        if (v0_of(b) != 0) CHECK(rd32(m, rd32(m, v0_of(b) + 60) + 4) == model);  // work +4 = the model
        restore(m);
        SiPair c = pair_on(m, rg::fn_sub_1D40E0_001d40e0, rg::fn_sub_1D40E0_001d40e0__recomp, {0, kPc, 0, 0}, rng(), "sub_1D40E0");
        if (v0_of(c) != 0) CHECK(rd32(m, rd32(m, v0_of(c) + 60) + 4) == kPc);  // work +4 = the unit
    }
    // the material-anim update on shadow 1's model: the 31-frame timer
    for (u32 t : {0u, 1u, 29u, 30u, 31u, 40u}) {
        restore(m);
        const u32 task = kScratch, work = kScratch + 0x100;
        wr32(m, task + 60, work);
        wr32(m, work + 4, rd32(m, kEc + kUnitSize + 80));
        wr32(m, work + 8, t);
        SiPair p = pair_on(m, rg::fn_sub_1D3A30_001d3a30, rg::fn_sub_1D3A30_001d3a30__recomp, {task, 0, 0, 0}, rng(), "sub_1D3A30");
        CHECK(v0_of(p) == 0);
        CHECK(rd32(m, work + 8) == (t + 1 >= 31 ? 0u : t + 1));
    }
    // the badstat update on the party's real tasks
    for (u32 i = 0; i < 3; ++i) {
        restore(m, false);
        const u32 task = rd32(m, kPc + kUnitSize * i + 384);
        if (task == 0) continue;
        SiPair p = pair_on(m, rg::fn_sub_1D3CE0_001d3ce0, rg::fn_sub_1D3CE0_001d3ce0__recomp, {task, 0, 0, 0}, rng(), "sub_1D3CE0");
        CHECK(v0_of(p) == 0);
    }
    // the forced Reaper: a scheduler work in scratch
    for (int i = 0; i < 3; ++i) {
        restore(m);
        const u32 task = kScratch, work = kScratch + 0x100;
        wr32(m, task + 60, work);
        wr32(m, work + 20, static_cast<u32>(i));
        pair_on(m, rg::fn_sub_1D39C0_001d39c0, rg::fn_sub_1D39C0_001d39c0__recomp, {task, 0, 0, 0}, rng(), "sub_1D39C0");
        CHECK(rd32(m, work + 0) == 1);
        CHECK(rd32(m, work + 20) == static_cast<u32>(i) + 1);
    }
}

TEST_CASE("game(field3_units): the field table loaders on the fake file layer and the filter setter") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    for (u32 answer = 0; answer < 2; ++answer) {
        wr32(*m, kGp - 19788, answer);  // The Answer (sub_17D800): enemy_aegis.bin
        pair_on(*m, rg::fn_sub_1D4290_001d4290, rg::fn_sub_1D4290_001d4290__recomp, {0, 0, 0, 0}, 21 + answer, "sub_1D4290",
                [](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(0x1008B0u, "H_Cdvd_FileExists", 1);
                });
        const u32 tbl = rd32(*m, kGp - 19040);
        MESSAGE("sub_1D4290 (The Answer " << answer << "): table " << (tbl ? "loaded" : "absent"));
        if (tbl != 0) {
            CHECK(tbl == 0x871EC0u);
            CHECK(rd32(*m, kGp - 19036) == tbl + 384);
        }
        pair_on(*m, rg::fn_sub_1D4360_001d4360, rg::fn_sub_1D4360_001d4360__recomp, {0, 0, 0, 0}, 23 + answer, "sub_1D4360",
                [](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(0x1008B0u, "H_Cdvd_FileExists", 1);
                    w.cd.load = false;
                });
    }
    wr32(*m, kGp - 19032, 0);
    pair_on(*m, rg::fn_sub_1D4560_001d4560, rg::fn_sub_1D4560_001d4560__recomp, {0, 0, 0, 0}, 25, "sub_1D4560",
            [](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(0x1008B0u, "H_Cdvd_FileExists", 1);
                });
    // the filter setter: immediate and faded
    const u32 buf = 0x01810000u;
    std::mt19937 rng{0xF3A0006};
    for (int i = 0; i < 16; ++i) {
        wr32(*m, kGp - 19032, buf);
        const u32 prev = rng() % 20, filter = rng() % 20, value = rng(), frames = (i & 1) ? 0u : 1u + rng() % 60;
        wr32(*m, kGp - 19032 + 8, prev);
        pair_on(*m, rg::fn_sub_1D50C0_001d50c0, rg::fn_sub_1D50C0_001d50c0__recomp, {filter, value, frames, 0}, rng(), "sub_1D50C0",
                [](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(0x1008B0u, "H_Cdvd_FileExists", 1);
                });
        CHECK(rd32(*m, kGp - 19032 + 8) == filter);
        CHECK(rd32(*m, buf + 292 * filter) == value);
        if (frames == 0) {
            CHECK(rd32(*m, kGp - 19032 + 12) == filter);
            CHECK(rdf(*m, kGp - 19032 + 16) == 1.0f);
            CHECK(rdf(*m, kGp - 19032 + 20) == 1.0f);
        } else {
            CHECK(rd32(*m, kGp - 19032 + 12) == prev);
            CHECK(rdf(*m, kGp - 19032 + 16) == 0.0f);
            CHECK(rdf(*m, kGp - 19032 + 20) == static_cast<float>(frames));
        }
    }
}

#else

TEST_CASE("game(field3_units): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
