// Pair tests of the field7 slice, part epl: the field EPL player tasks of k_epl.c (game/src/field/field7_epl.cpp).
// First every body against its recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/
// handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all 32 MiB of
// RAM, the scratchpad, the BIOS window, the bus log), then built worlds with real data and the documented rules.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field7_epl.h"
#include "p3fes/game/hcdvd.h"
#include "p3fes/game/task.h"

#include <cstring>
#include <fstream>
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
void fn_sub_1A8DB0_001a8db0(EEContext&);  // generated body
void fn_sub_1A8DB0_001a8db0__recomp(EEContext&);  // recompiled
void fn_sub_1A8FE0_001a8fe0(EEContext&);  // generated body
void fn_sub_1A8FE0_001a8fe0__recomp(EEContext&);  // recompiled
void fn_sub_1A9080_001a9080(EEContext&);  // generated body
void fn_sub_1A9080_001a9080__recomp(EEContext&);  // recompiled
void fn_sub_1A9330_001a9330(EEContext&);  // generated body
void fn_sub_1A9330_001a9330__recomp(EEContext&);  // recompiled
void fn_sub_1A9470_001a9470(EEContext&);  // generated body
void fn_sub_1A9470_001a9470__recomp(EEContext&);  // recompiled
void fn_sub_1A9690_001a9690(EEContext&);  // generated body
void fn_sub_1A9690_001a9690__recomp(EEContext&);  // recompiled
void fn_sub_1A96C0_001a96c0(EEContext&);  // generated body
void fn_sub_1A96C0_001a96c0__recomp(EEContext&);  // recompiled
void fn_sub_1A9760_001a9760(EEContext&);  // generated body
void fn_sub_1A9760_001a9760__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1A8DB0", 0x1A8DB0, &recomp_gen::fn_sub_1A8DB0_001a8db0, &recomp_gen::fn_sub_1A8DB0_001a8db0__recomp},
    {"sub_1A8FE0", 0x1A8FE0, &recomp_gen::fn_sub_1A8FE0_001a8fe0, &recomp_gen::fn_sub_1A8FE0_001a8fe0__recomp},
    {"sub_1A9080", 0x1A9080, &recomp_gen::fn_sub_1A9080_001a9080, &recomp_gen::fn_sub_1A9080_001a9080__recomp},
    {"sub_1A9330", 0x1A9330, &recomp_gen::fn_sub_1A9330_001a9330, &recomp_gen::fn_sub_1A9330_001a9330__recomp},
    {"sub_1A9470", 0x1A9470, &recomp_gen::fn_sub_1A9470_001a9470, &recomp_gen::fn_sub_1A9470_001a9470__recomp},
    {"sub_1A9690", 0x1A9690, &recomp_gen::fn_sub_1A9690_001a9690, &recomp_gen::fn_sub_1A9690_001a9690__recomp},
    {"sub_1A96C0", 0x1A96C0, &recomp_gen::fn_sub_1A96C0_001a96c0, &recomp_gen::fn_sub_1A96C0_001a96c0__recomp},
    {"sub_1A9760", 0x1A9760, &recomp_gen::fn_sub_1A9760_001a9760, &recomp_gen::fn_sub_1A9760_001a9760__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena (the built worlds follow below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field7_epl): every body equals its recompiled body on random worlds") {
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
// Meaningful pairs on the stand-in world (tests/game/stand_ins.h: the heap behind the RW calloc / free slots, the H_Cdvd
// layer over extracted/): the Tartarus floor effect "field/effect/DNG%02d.EPL" (the request K_FldDungeon_UpdateTask
// makes: frames -1, not cached) created, loaded and turned into its main node, then the play state's frame counters
// and end rules, the stop, the destroy, and the "epl delay" queue. Each step is one pair (hand vs recompiled, whole
// RAM, every register at every check point, the dead stack, the stand-ins' logs); the machine keeps the recompiled
// run's state for the next step. The effect-node internals below the hand-written wrappers that this build does not
// emit are recorders: sub_324BD0 (create; returns a fake node), sub_3252A0 (step), sub_325500 (layer draw).
// =====================================================================================================================

namespace {

namespace rg = p3fes::recomp_gen;
using namespace p3fes::game::f7::epl;

Machine* epl_machine() {
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

u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void p16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

HwCheck epl_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

constexpr u32 kParent = 0x01B80000u;   // a running parent task (zeroed record, its work behind it)
constexpr u32 kTask = 0x01B81000u;     // the EPL task record of the update steps (+60 -> kWork)
constexpr u32 kWork = 0x01B81100u;     // its 180-byte work
constexpr u32 kFakeNode = 0x01B82000u; // what the create recorder returns: a zeroed node
constexpr u32 kPathBuf = 0x01B83000u;  // the guest path string
constexpr u32 kPosBuf = 0x01B83100u;   // a vec3

void clean_world(Machine& m) {
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
    std::memset(m.at(0x7CE064u), 0, 0x7CE088u - 0x7CE064u);  // the kwln starting / ending / running lists
    std::memset(m.at(kParent), 0, 0x6000);
    p32(m, kParent + game::kwln::kOffWork, kParent + 0x100u);
    p32(m, kParent + game::kwln::kOffState, 2);
    p32(m, kTask + kTaskWork, kWork);
}

using Live = std::map<u32, u32>;
WorldSetup epl_world(const Live& live) {
    return [live](StandInWorld& w) {
        install_standard(w);
        for (const auto& [p, n] : live) w.heap.reserve(p, n);
        w.si.install_recorder(0x324BD0u, "sub_324BD0 (effect node create)", kFakeNode);
        w.si.install_recorder(0x3252A0u, "sub_3252A0 (effect step)", 0);
        w.si.install_recorder(0x325500u, "sub_325500 (effect layer draw)", 0);
    };
}

// What H_Cdvd_Update does for a pending node: the whole file 64-byte aligned at `raw`, the node's data / size words,
// state 4 (as test_boot.cpp's host_load). Returns the bytes ("" = not under extracted/).
std::vector<u8> host_load(Machine& m, u32 node, u32 raw) {
    GuestHeap scratch;
    FakeCd cd{scratch};
    const std::string hp = cd.host_path(m.str(node + 16, 256));
    if (hp.empty()) return {};
    std::ifstream f(hp, std::ios::binary);
    std::vector<u8> bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    const u32 data = (raw + 63u) & ~63u;
    std::memcpy(m.at(data), bytes.data(), bytes.size());
    p32(m, node + 276, raw);
    p32(m, node + 272, data);
    p32(m, node + 292, static_cast<u32>(bytes.size()));
    p32(m, node + 280, static_cast<u32>(bytes.size()));
    p32(m, node + 12, game::kHCdvdStateLoaded);
    return bytes;
}

SiPair step(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Live& live,
            u64 t0 = 0) {
    HwCheck hw = epl_check();
    hw.gpr_in[GPR_T0] = t0;  // the fifth argument
    return run_pair_si(m, hand, recomp, args, seed, what, hw, epl_world(live));
}

}  // namespace

TEST_CASE("game(field7_epl): the floor EPL task requests its DNG file, makes its node once loaded, then idles") {
    Machine* mp = epl_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    int pairs = 0, loaded = 0;
    for (u32 floor : {0u, 3u, 7u}) {
        clean_world(m);
        char path[64];
        std::snprintf(path, sizeof path, "field/effect/DNG%02u.EPL", floor);
        std::memset(m.at(kPathBuf), 0, 64);
        std::memcpy(m.at(kPathBuf), path, std::strlen(path));
        // create: "epl(kosaka)" at priority 20 under the parent, the request, frames -1, the path
        SiPair c = step(m, &rg::fn_sub_1A9080_001a9080, &rg::fn_sub_1A9080_001a9080__recomp,
                        {sx(kParent), sx(kPathBuf), sx(0xFFFFFFFFu), 0}, 100 + floor, "sub_1A9080 create", {});
        ++pairs;
        const u32 task = static_cast<u32>(c.hw.recomp.base.v0);
        REQUIRE(task != 0);
        CHECK(m.str(task + game::kwln::kOffName, 24) == "epl(kosaka)");
        CHECK(g32(m, task + game::kwln::kOffPriority) == 20);
        CHECK(g32(m, task + game::kwln::kOffParent) == kParent);
        CHECK(g32(m, task + game::kwln::kOffUpdate) == 0x1A8DB0u);
        CHECK(g32(m, task + game::kwln::kOffDestroy) == 0x1A8FE0u);
        const u32 work = g32(m, task + kTaskWork);
        REQUIRE(work != 0);
        const StandIns& si = c.recomp->si;
        REQUIRE(si.calls_to(kHCdvdRequestFn) == 1);
        u32 node = 0;
        for (const StandInCall& call : si.log)
            if (call.va == kHCdvdRequestFn) {
                CHECK(call.text == FakeCd::build_path(path));
                CHECK(call.args[1] == 0);  // a plain file
                node = static_cast<u32>(call.v0);
            }
        CHECK(g32(m, work + kRequest) == node);
        CHECK(g32(m, work + kCached) == 0);
        CHECK(g32(m, work + kFrames) == 0xFFFFFFFFu);
        CHECK(m.str(work + kPath, 64) == path);
        CHECK(g32(m, work + kState) == 0);
        Live live = c.recomp->heap.live();
        // frame 1: not read yet -- still state 0, returns 0
        SiPair f1 = step(m, &rg::fn_sub_1A8DB0_001a8db0, &rg::fn_sub_1A8DB0_001a8db0__recomp, {sx(task), 0, 0, 0},
                         110 + floor, "sub_1A8DB0 waiting", live);
        ++pairs;
        CHECK(f1.hw.recomp.base.v0 == 0);
        CHECK(g32(m, work + kState) == 0);
        CHECK(g32(m, work + kMainNode) == 0);
        // the read completes
        const u32 raw = kStandInHeap + 0x200000u;
        const std::vector<u8> bytes = host_load(m, node, raw);
        if (bytes.empty()) {
            MESSAGE(path << " is not under extracted/: the load part skipped");
            continue;
        }
        live[raw] = (static_cast<u32>(bytes.size()) + 64u + 15u) & ~15u;
        // frame 2: the node from the file's data, the request destroyed, state 1
        SiPair f2 = step(m, &rg::fn_sub_1A8DB0_001a8db0, &rg::fn_sub_1A8DB0_001a8db0__recomp, {sx(task), 0, 0, 0},
                         120 + floor, "sub_1A8DB0 loaded", live);
        ++pairs;
        ++loaded;
        CHECK(f2.hw.recomp.base.v0 == 0);
        CHECK(g32(m, work + kState) == 1);
        CHECK(g32(m, work + kMainNode) == kFakeNode);
        CHECK(g32(m, work + kRequest) == 0);
        const StandIns& s2 = f2.recomp->si;
        CHECK(s2.calls_to(0x324BD0u) == 1);
        CHECK(s2.calls_to(kHCdvdDestroyFn) == 1);
        for (const StandInCall& call : s2.log) {
            if (call.va == 0x324BD0u) CHECK(static_cast<u32>(call.args[0]) == ((raw + 63u) & ~63u));  // the EPL data
            if (call.va == kHCdvdDestroyFn) CHECK(static_cast<u32>(call.args[0]) == node);
        }
        // the EPL header as the file has it: the node gets the data as loaded
        CHECK(std::memcmp(m.at((raw + 63u) & ~63u), bytes.data(), bytes.size()) == 0);
        // frame 3: state 1 idles
        SiPair f3 = step(m, &rg::fn_sub_1A8DB0_001a8db0, &rg::fn_sub_1A8DB0_001a8db0__recomp, {sx(task), 0, 0, 0},
                         130 + floor, "sub_1A8DB0 idle", f2.recomp->heap.live());
        ++pairs;
        CHECK(f3.hw.recomp.base.v0 == 0);
        CHECK(g32(m, work + kState) == 1);
        CHECK(f3.recomp->si.log.empty());
        MESSAGE(path << ": " << bytes.size() << " bytes");
    }
    // the cached variant: no request, the cache flag, the caller's word kept
    clean_world(m);
    std::memcpy(m.at(kPathBuf), "field/effect/DNG01.EPL", 23);
    SiPair c = step(m, &rg::fn_sub_1A9080_001a9080, &rg::fn_sub_1A9080_001a9080__recomp,
                    {sx(kParent), sx(kPathBuf), 90, 0x55}, 140, "sub_1A9080 cached", {});
    ++pairs;
    const u32 work = g32(m, static_cast<u32>(c.hw.recomp.base.v0) + kTaskWork);
    CHECK(c.recomp->si.calls_to(kHCdvdRequestFn) == 0);
    CHECK(g32(m, work + kRequest) == 0x55);
    CHECK(g32(m, work + kCached) == 1);
    CHECK(g32(m, work + kFrames) == 90);
    MESSAGE("floor EPL: " << pairs << " pairs, " << loaded << " DNG files loaded from extracted/");
}

TEST_CASE("game(field7_epl): playing steps and draws each node until its frame count, then the task idles") {
    Machine* mp = epl_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0xE91u};
    int pairs = 0, frames_run = 0;
    for (int round = 0; round < 24; ++round) {
        clean_world(m);
        std::memset(m.at(kWork), 0, kWorkSize);
        std::memset(m.at(kFakeNode), 0, 0x1000);
        const u32 frames = 1u + rng() % 6u;
        p32(m, kWork + kState, 2);
        p32(m, kWork + kFrames, frames);
        const bool main_on = (rng() & 1u) != 0;
        p32(m, kWork + kMainOn, main_on ? 1u : 0u);
        p32(m, kWork + kMainNode, kFakeNode);
        const u32 main_frame = rng() % frames;
        p32(m, kWork + kMainFrame, main_frame);
        p16(m, kWork + kMainLayer, static_cast<u16>(rng() % 4u));
        u32 live_children = 0;
        u32 child_frame[kMaxChildren] = {};
        bool child_on[kMaxChildren] = {};
        for (u32 i = 0; i < kMaxChildren; ++i) {
            child_on[i] = rng() % 3u == 0;
            if (!child_on[i]) continue;
            ++live_children;
            const u32 f = rng() % frames;
            child_frame[i] = f;
            p32(m, kWork + kChildNodes + 4u * i, kFakeNode + 0x100u * (i + 1u));
            p32(m, kWork + kChildFrames + 4u * i, child_frame[i]);
            p16(m, kWork + kChildLayers + 2u * i, static_cast<u16>(i));
        }
        p32(m, kWork + kLiveChildren, live_children);
        // run frames until the task falls back to idle (at most frames + 2)
        u32 main_left = main_on ? frames - main_frame : 0u;
        for (u32 f = 0; f < frames + 2u; ++f) {
            const bool was_done = !(g32(m, kWork + kMainOn) != 0) && g32(m, kWork + kLiveChildren) == 0;
            const u32 main_count_before = g32(m, kWork + kMainFrame);
            SiPair p = step(m, &rg::fn_sub_1A8DB0_001a8db0, &rg::fn_sub_1A8DB0_001a8db0__recomp,
                            {sx(kTask), 0, 0, 0}, 1000u + static_cast<u32>(round) * 16u + f, "sub_1A8DB0 play", {});
            ++pairs;
            ++frames_run;
            CHECK(p.hw.recomp.base.v0 == 0);
            if (was_done) {
                CHECK(g32(m, kWork + kState) == 1);  // nothing left: back to idle
                break;
            }
            CHECK(g32(m, kWork + kState) == 2);
            // the main node: drawn (step + layer draw) while below the frame count, then switched off
            if (main_left > 0) {
                CHECK(g32(m, kWork + kMainFrame) == main_count_before + 1u);
                --main_left;
            } else {
                CHECK(g32(m, kWork + kMainOn) == 0);
            }
            // the children: counted up, destroyed at the frame count
            u32 alive = 0;
            for (u32 i = 0; i < kMaxChildren; ++i) {
                if (!child_on[i]) continue;
                if (child_frame[i] < frames) {
                    ++child_frame[i];
                    CHECK(g32(m, kWork + kChildFrames + 4u * i) == child_frame[i]);
                    ++alive;
                } else {
                    CHECK(g32(m, kWork + kChildNodes + 4u * i) == 0);
                    child_on[i] = false;
                }
            }
            CHECK(g32(m, kWork + kLiveChildren) == alive);
        }
    }
    // the stop: children destroyed and cleared, the count 0, the main node off
    clean_world(m);
    std::memset(m.at(kWork), 0, kWorkSize);
    p32(m, kWork + kState, 2);
    p32(m, kWork + kMainOn, 1);
    p32(m, kWork + kMainNode, kFakeNode);
    for (u32 i : {1u, 4u, 6u}) p32(m, kWork + kChildNodes + 4u * i, kFakeNode + 0x100u * (i + 1u));
    p32(m, kWork + kLiveChildren, 3);
    SiPair s = step(m, &rg::fn_sub_1A9470_001a9470, &rg::fn_sub_1A9470_001a9470__recomp, {sx(kTask), 0, 0, 0}, 2000,
                    "sub_1A9470 stop", {});
    ++pairs;
    for (u32 i = 0; i < kMaxChildren; ++i) CHECK(g32(m, kWork + kChildNodes + 4u * i) == 0);
    CHECK(g32(m, kWork + kLiveChildren) == 0);
    CHECK(g32(m, kWork + kMainOn) == 0);
    CHECK(g32(m, kWork + kMainNode) == kFakeNode);  // kept: the destroy callback frees it
    // a NULL task: nothing
    step(m, &rg::fn_sub_1A9470_001a9470, &rg::fn_sub_1A9470_001a9470__recomp, {0, 0, 0, 0}, 2001, "sub_1A9470 NULL", {});
    ++pairs;
    MESSAGE("EPL play: " << pairs << " pairs, " << frames_run << " update frames");
}

TEST_CASE("game(field7_epl): the delay task queues up to eight requests (id, position, two words)") {
    Machine* mp = epl_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    clean_world(m);
    SiPair c = step(m, &rg::fn_sub_1A96C0_001a96c0, &rg::fn_sub_1A96C0_001a96c0__recomp, {sx(kParent), 0, 0, 0}, 3000,
                    "sub_1A96C0 create", {});
    const u32 task = static_cast<u32>(c.hw.recomp.base.v0);
    REQUIRE(task != 0);
    CHECK(m.str(task + game::kwln::kOffName, 24) == "epl delay(kosaka)");
    CHECK(g32(m, task + game::kwln::kOffUpdate) == 0x1A9500u);
    CHECK(g32(m, task + game::kwln::kOffDestroy) == 0x1A9690u);
    const u32 work = g32(m, task + kTaskWork);
    CHECK(g32(m, work + kDelayWait) == 20);
    CHECK(g32(m, work + kDelayCount) == 0);
    Live live = c.recomp->heap.live();
    std::mt19937 rng{0xDE1u};
    int pairs = 1;
    for (u32 i = 0; i < 9; ++i) {  // the ninth asserts (K_Assert returns) and writes past the arrays
        float pos[3];
        for (float& f : pos) {
            const u32 r = rng();
            f = static_cast<float>(static_cast<s32>(r % 20001u) - 10000) / 4.0f;
        }
        std::memcpy(m.at(kPosBuf), pos, 12);
        const u32 id = rng() % 64u;
        const u32 w3 = rng();
        const u32 w4 = rng() % 100u;
        step(m, &rg::fn_sub_1A9760_001a9760, &rg::fn_sub_1A9760_001a9760__recomp,
             {sx(task), sx(id), sx(kPosBuf), sx(w3)}, 3001 + i, "sub_1A9760 queue", live, sx(w4));
        ++pairs;
        CHECK(g32(m, work + kDelayCount) == i + 1u);
        if (i >= 8) continue;
        CHECK(g32(m, work + kDelayId + 4u * i) == id);
        CHECK(std::memcmp(m.at(work + kDelayPos + 12u * i), pos, 12) == 0);
        CHECK(g32(m, work + kDelayArg3 + 4u * i) == w3);
        CHECK(g32(m, work + kDelayArg4 + 4u * i) == w4);
    }
    // a NULL task: nothing
    step(m, &rg::fn_sub_1A9760_001a9760, &rg::fn_sub_1A9760_001a9760__recomp, {0, 1, sx(kPosBuf), 2}, 3100,
         "sub_1A9760 NULL", live, 3);
    ++pairs;
    MESSAGE("EPL delay queue: " << pairs << " pairs");
}

#else

TEST_CASE("game(field7_epl): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
