// Pair tests of the field7 slice, part ud: the RpUserData frame searches (game/src/field/field7_ud.cpp).
// First every body against its recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/
// handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all 32 MiB of
// RAM, the scratchpad, the BIOS window, the bus log), then the replay snapshots' real clumps and the documented rule.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field7_ud.h"
#include "p3fes/game/models.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
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
void fn_sub_1A69A0_001a69a0(EEContext&);  // generated body
void fn_sub_1A69A0_001a69a0__recomp(EEContext&);  // recompiled
void fn_sub_1A6AF0_001a6af0(EEContext&);  // generated body
void fn_sub_1A6AF0_001a6af0__recomp(EEContext&);  // recompiled
void fn_sub_1A6D20_001a6d20(EEContext&);  // generated body
void fn_sub_1A6D20_001a6d20__recomp(EEContext&);  // recompiled
void fn_sub_1A6E90_001a6e90(EEContext&);  // generated body
void fn_sub_1A6E90_001a6e90__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1A69A0", 0x1A69A0, &recomp_gen::fn_sub_1A69A0_001a69a0, &recomp_gen::fn_sub_1A69A0_001a69a0__recomp},
    {"sub_1A6AF0", 0x1A6AF0, &recomp_gen::fn_sub_1A6AF0_001a6af0, &recomp_gen::fn_sub_1A6AF0_001a6af0__recomp},
    {"sub_1A6D20", 0x1A6D20, &recomp_gen::fn_sub_1A6D20_001a6d20, &recomp_gen::fn_sub_1A6D20_001a6d20__recomp},
    {"sub_1A6E90", 0x1A6E90, &recomp_gen::fn_sub_1A6E90_001a6e90, &recomp_gen::fn_sub_1A6E90_001a6e90__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena (the snapshots follow below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field7_ud): every body equals its recompiled body on random worlds") {
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
// Meaningful pairs on the replay snapshots' live model clumps (dorm, Tartarus climb, battle): the user-data searches
// on the real frame hierarchies and their real RpUserData arrays (the models' "per3HelperId" helpers and the field
// objects' arrays), with the documented rule checked across the three functions: sub_1A6AF0 counts the int entries
// named X in the whole hierarchy, and sub_1A6E90 finds the n-th one exactly for n below that count (value and frame),
// out = {0, 0} past it; a value it found, searched by sub_1A69A0 on the root frame, finds that frame when the frame is
// the root. sub_1A6860 (sub_1A69A0's descendant callback, not emitted in this build; test_models stands it in too) is
// stood in by a pass-through that keeps the walk going.
// =====================================================================================================================

namespace {

namespace rg = p3fes::recomp_gen;
using namespace p3fes::game::f7::ud;

u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

constexpr u32 kMdlLists = 0x9571F0u;  // gMdlLists[12] (test_models.cpp)
constexpr u32 kScratch = 0x01FF0000u; // below the main-thread stack's top page: the record, names, out

bool load_snapshot(Machine& m, const char* name) {
    const auto p = std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / name / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    in.read(reinterpret_cast<char*>(m.mem.main_ram()), EEMemory::kMainRamSize);
    return in.gcount() == static_cast<std::streamsize>(EEMemory::kMainRamSize);
}

HwCheck ud_check(u64 t0 = 0) {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in[GPR_T0] = t0;
    return hw;
}

const WorldSetup kUdWorld = [](StandInWorld& w) {
    install_standard(w);
    w.si.install(0x1A6860u, "sub_1A6860 (pass-through)", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
};

}  // namespace

TEST_CASE("game(field7_ud): the user-data searches on the snapshots' model clumps agree with the count") {
    auto mp = std::make_unique<Machine>();
    if (mp->load_elf(elf_path()) != nullptr) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const char* names[] = {"per3HelperId", "per3FieldObjectId", "per3FieldObjectType", "per3FieldObjectResid"};
    int pairs = 0, clumps = 0, entries = 0, snaps = 0;
    u32 seed = 1;
    for (const char* snap : {"dorm_replay_4900", "climb_ref_17000", "b_5800"}) {
        if (!load_snapshot(m, snap)) continue;
        ++snaps;
        write_rw_slots(m);
        INFO(snap);
        std::vector<u32> clump_list;
        for (u32 k = 0; k < static_cast<u32>(game::mdl::kMdlListCount); ++k)
            for (u32 md = g32(m, kMdlLists + 4u * k); md != 0 && clump_list.size() < 24; md = g32(m, md + game::mdl::kMdlNext)) {
                const u32 clump = g32(m, md + game::mdl::kMdlClump);
                if (clump != 0 && g32(m, clump + 4) != 0) clump_list.push_back(clump);
            }
        for (u32 clump : clump_list) {
            ++clumps;
            const u32 root = g32(m, clump + 4);
            for (const char* name : names) {
                // the count over the whole hierarchy
                const u32 rec = kScratch;
                std::memset(m.at(rec), 0, kRecSize);
                std::memcpy(m.at(rec + kRecName), name, std::strlen(name));
                SiPair c = run_pair_si(m, &rg::fn_sub_1A6AF0_001a6af0, &rg::fn_sub_1A6AF0_001a6af0__recomp,
                                       {sx(root), sx(rec), 0, 0}, seed++, "sub_1A6AF0 count", ud_check(), kUdWorld);
                ++pairs;
                CHECK(c.hw.recomp.base.v0 == root);
                const u32 count = g32(m, rec + kRecTotal);
                entries += static_cast<int>(count);
                // the n-th entry for n = 0 .. count (one past)
                const u32 name_va = kScratch + 0x100u;
                std::memset(m.at(name_va), 0, 64);
                std::memcpy(m.at(name_va), name, std::strlen(name));
                const u32 out = kScratch + 0x200u;
                for (u32 n = 0; n <= std::min<u32>(count, 6u); ++n) {
                    p32(m, out, 0xDEADBEEFu);
                    p32(m, out + 4, 0xDEADBEEFu);
                    run_pair_si(m, &rg::fn_sub_1A6E90_001a6e90, &rg::fn_sub_1A6E90_001a6e90__recomp,
                                {sx(out), sx(clump), sx(name_va), sx(n)}, seed++, "sub_1A6E90 n-th", ud_check(), kUdWorld);
                    ++pairs;
                    const u32 value = g32(m, out), frame = g32(m, out + 4);
                    if (n < count) {
                        CHECK(frame != 0);  // found: the frame that carries it
                        // by value from the root: finds the root when the entry sits on the root frame
                        const u32 found = static_cast<u32>(
                            run_pair_si(m, &rg::fn_sub_1A69A0_001a69a0, &rg::fn_sub_1A69A0_001a69a0__recomp,
                                        {sx(clump), sx(name_va), sx(value), 0}, seed++, "sub_1A69A0 by value", ud_check(),
                                        kUdWorld)
                                .hw.recomp.base.v0);
                        ++pairs;
                        if (frame == root) CHECK(found == root);
                    } else {
                        CHECK(value == 0);  // past the last: the zeroed record's value / frame
                        CHECK(frame == 0);
                    }
                }
            }
        }
    }
    if (snaps == 0) MESSAGE("SKIP: no replay snapshot under extracted/_ours");
    MESSAGE("user-data searches: " << snaps << " snapshots, " << clumps << " clumps, " << entries << " named int entries, "
                                   << pairs << " pairs");
}

#else

TEST_CASE("game(field7_ud): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
