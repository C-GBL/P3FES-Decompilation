// Pair tests of the field7 slice, part draw: the frame helpers, circle draw, matrix angles, model fade and k_clump.c draw lists
// (game/src/field/field7_draw.cpp).
// First every body against its recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/
// handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all 32 MiB of
// RAM, the scratchpad, the BIOS window, the bus log), then built worlds with real data and the documented rules.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field7_draw.h"
#include "p3fes/game/boot.h"

#include <cmath>
#include <cstring>
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
void fn_sub_1A13B0_001a13b0(EEContext&);  // generated body
void fn_sub_1A13B0_001a13b0__recomp(EEContext&);  // recompiled
void fn_sub_1A1540_001a1540(EEContext&);  // generated body
void fn_sub_1A1540_001a1540__recomp(EEContext&);  // recompiled
void fn_sub_1A4DF0_001a4df0(EEContext&);  // generated body
void fn_sub_1A4DF0_001a4df0__recomp(EEContext&);  // recompiled
void fn_sub_1A4E50_001a4e50(EEContext&);  // generated body
void fn_sub_1A4E50_001a4e50__recomp(EEContext&);  // recompiled
void fn_sub_1A4ED0_001a4ed0(EEContext&);  // generated body
void fn_sub_1A4ED0_001a4ed0__recomp(EEContext&);  // recompiled
void fn_sub_1A4F40_001a4f40(EEContext&);  // generated body
void fn_sub_1A4F40_001a4f40__recomp(EEContext&);  // recompiled
void fn_sub_1A5000_001a5000(EEContext&);  // generated body
void fn_sub_1A5000_001a5000__recomp(EEContext&);  // recompiled
void fn_sub_1A56B0_001a56b0(EEContext&);  // generated body
void fn_sub_1A56B0_001a56b0__recomp(EEContext&);  // recompiled
void fn_sub_1A56C0_001a56c0(EEContext&);  // generated body
void fn_sub_1A56C0_001a56c0__recomp(EEContext&);  // recompiled
void fn_sub_1A56D0_001a56d0(EEContext&);  // generated body
void fn_sub_1A56D0_001a56d0__recomp(EEContext&);  // recompiled
void fn_sub_1A5700_001a5700(EEContext&);  // generated body
void fn_sub_1A5700_001a5700__recomp(EEContext&);  // recompiled
void fn_sub_1A57A0_001a57a0(EEContext&);  // generated body
void fn_sub_1A57A0_001a57a0__recomp(EEContext&);  // recompiled
void fn_sub_1A5AA0_001a5aa0(EEContext&);  // generated body
void fn_sub_1A5AA0_001a5aa0__recomp(EEContext&);  // recompiled
void fn_sub_1A5B30_001a5b30(EEContext&);  // generated body
void fn_sub_1A5B30_001a5b30__recomp(EEContext&);  // recompiled
void fn_sub_1A5BC0_001a5bc0(EEContext&);  // generated body
void fn_sub_1A5BC0_001a5bc0__recomp(EEContext&);  // recompiled
void fn_sub_1A5E70_001a5e70(EEContext&);  // generated body
void fn_sub_1A5E70_001a5e70__recomp(EEContext&);  // recompiled
void fn_sub_1A5F30_001a5f30(EEContext&);  // generated body
void fn_sub_1A5F30_001a5f30__recomp(EEContext&);  // recompiled
void fn_sub_1A60A0_001a60a0(EEContext&);  // generated body
void fn_sub_1A60A0_001a60a0__recomp(EEContext&);  // recompiled
void fn_sub_1A6260_001a6260(EEContext&);  // generated body
void fn_sub_1A6260_001a6260__recomp(EEContext&);  // recompiled
void fn_sub_1A6290_001a6290(EEContext&);  // generated body
void fn_sub_1A6290_001a6290__recomp(EEContext&);  // recompiled
void fn_sub_1A7030_001a7030(EEContext&);  // generated body
void fn_sub_1A7030_001a7030__recomp(EEContext&);  // recompiled
void fn_sub_1A70A0_001a70a0(EEContext&);  // generated body
void fn_sub_1A70A0_001a70a0__recomp(EEContext&);  // recompiled
void fn_sub_1A71A0_001a71a0(EEContext&);  // generated body
void fn_sub_1A71A0_001a71a0__recomp(EEContext&);  // recompiled
void fn_sub_1A74B0_001a74b0(EEContext&);  // generated body
void fn_sub_1A74B0_001a74b0__recomp(EEContext&);  // recompiled
void fn_sub_1A7660_001a7660(EEContext&);  // generated body
void fn_sub_1A7660_001a7660__recomp(EEContext&);  // recompiled
void fn_sub_1A76E0_001a76e0(EEContext&);  // generated body
void fn_sub_1A76E0_001a76e0__recomp(EEContext&);  // recompiled
void fn_sub_1A8820_001a8820(EEContext&);  // generated body
void fn_sub_1A8820_001a8820__recomp(EEContext&);  // recompiled
void fn_sub_1A8910_001a8910(EEContext&);  // generated body
void fn_sub_1A8910_001a8910__recomp(EEContext&);  // recompiled
void fn_sub_1A8920_001a8920(EEContext&);  // generated body
void fn_sub_1A8920_001a8920__recomp(EEContext&);  // recompiled
void fn_sub_1A89C0_001a89c0(EEContext&);  // generated body
void fn_sub_1A89C0_001a89c0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1A13B0", 0x1A13B0, &recomp_gen::fn_sub_1A13B0_001a13b0, &recomp_gen::fn_sub_1A13B0_001a13b0__recomp},
    {"sub_1A1540", 0x1A1540, &recomp_gen::fn_sub_1A1540_001a1540, &recomp_gen::fn_sub_1A1540_001a1540__recomp},
    {"sub_1A4DF0", 0x1A4DF0, &recomp_gen::fn_sub_1A4DF0_001a4df0, &recomp_gen::fn_sub_1A4DF0_001a4df0__recomp},
    {"sub_1A4E50", 0x1A4E50, &recomp_gen::fn_sub_1A4E50_001a4e50, &recomp_gen::fn_sub_1A4E50_001a4e50__recomp},
    {"sub_1A4ED0", 0x1A4ED0, &recomp_gen::fn_sub_1A4ED0_001a4ed0, &recomp_gen::fn_sub_1A4ED0_001a4ed0__recomp},
    {"sub_1A4F40", 0x1A4F40, &recomp_gen::fn_sub_1A4F40_001a4f40, &recomp_gen::fn_sub_1A4F40_001a4f40__recomp},
    {"sub_1A5000", 0x1A5000, &recomp_gen::fn_sub_1A5000_001a5000, &recomp_gen::fn_sub_1A5000_001a5000__recomp},
    {"sub_1A56B0", 0x1A56B0, &recomp_gen::fn_sub_1A56B0_001a56b0, &recomp_gen::fn_sub_1A56B0_001a56b0__recomp},
    {"sub_1A56C0", 0x1A56C0, &recomp_gen::fn_sub_1A56C0_001a56c0, &recomp_gen::fn_sub_1A56C0_001a56c0__recomp},
    {"sub_1A56D0", 0x1A56D0, &recomp_gen::fn_sub_1A56D0_001a56d0, &recomp_gen::fn_sub_1A56D0_001a56d0__recomp},
    {"sub_1A5700", 0x1A5700, &recomp_gen::fn_sub_1A5700_001a5700, &recomp_gen::fn_sub_1A5700_001a5700__recomp},
    {"sub_1A57A0", 0x1A57A0, &recomp_gen::fn_sub_1A57A0_001a57a0, &recomp_gen::fn_sub_1A57A0_001a57a0__recomp},
    {"sub_1A5AA0", 0x1A5AA0, &recomp_gen::fn_sub_1A5AA0_001a5aa0, &recomp_gen::fn_sub_1A5AA0_001a5aa0__recomp},
    {"sub_1A5B30", 0x1A5B30, &recomp_gen::fn_sub_1A5B30_001a5b30, &recomp_gen::fn_sub_1A5B30_001a5b30__recomp},
    {"sub_1A5BC0", 0x1A5BC0, &recomp_gen::fn_sub_1A5BC0_001a5bc0, &recomp_gen::fn_sub_1A5BC0_001a5bc0__recomp},
    {"sub_1A5E70", 0x1A5E70, &recomp_gen::fn_sub_1A5E70_001a5e70, &recomp_gen::fn_sub_1A5E70_001a5e70__recomp},
    {"sub_1A5F30", 0x1A5F30, &recomp_gen::fn_sub_1A5F30_001a5f30, &recomp_gen::fn_sub_1A5F30_001a5f30__recomp},
    {"sub_1A60A0", 0x1A60A0, &recomp_gen::fn_sub_1A60A0_001a60a0, &recomp_gen::fn_sub_1A60A0_001a60a0__recomp},
    {"sub_1A6260", 0x1A6260, &recomp_gen::fn_sub_1A6260_001a6260, &recomp_gen::fn_sub_1A6260_001a6260__recomp},
    {"sub_1A6290", 0x1A6290, &recomp_gen::fn_sub_1A6290_001a6290, &recomp_gen::fn_sub_1A6290_001a6290__recomp},
    {"sub_1A7030", 0x1A7030, &recomp_gen::fn_sub_1A7030_001a7030, &recomp_gen::fn_sub_1A7030_001a7030__recomp},
    {"sub_1A70A0", 0x1A70A0, &recomp_gen::fn_sub_1A70A0_001a70a0, &recomp_gen::fn_sub_1A70A0_001a70a0__recomp},
    {"sub_1A71A0", 0x1A71A0, &recomp_gen::fn_sub_1A71A0_001a71a0, &recomp_gen::fn_sub_1A71A0_001a71a0__recomp},
    {"sub_1A74B0", 0x1A74B0, &recomp_gen::fn_sub_1A74B0_001a74b0, &recomp_gen::fn_sub_1A74B0_001a74b0__recomp},
    {"sub_1A7660", 0x1A7660, &recomp_gen::fn_sub_1A7660_001a7660, &recomp_gen::fn_sub_1A7660_001a7660__recomp},
    {"sub_1A76E0", 0x1A76E0, &recomp_gen::fn_sub_1A76E0_001a76e0, &recomp_gen::fn_sub_1A76E0_001a76e0__recomp},
    {"sub_1A8820", 0x1A8820, &recomp_gen::fn_sub_1A8820_001a8820, &recomp_gen::fn_sub_1A8820_001a8820__recomp},
    {"sub_1A8910", 0x1A8910, &recomp_gen::fn_sub_1A8910_001a8910, &recomp_gen::fn_sub_1A8910_001a8910__recomp},
    {"sub_1A8920", 0x1A8920, &recomp_gen::fn_sub_1A8920_001a8920, &recomp_gen::fn_sub_1A8920_001a8920__recomp},
    {"sub_1A89C0", 0x1A89C0, &recomp_gen::fn_sub_1A89C0_001a89c0, &recomp_gen::fn_sub_1A89C0_001a89c0__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena (the built worlds follow below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field7_draw): every body equals its recompiled body on random worlds") {
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
// Meaningful pairs (stand-in world: the heap behind the RW calloc slot): the matrix angle helpers on the main camera's
// frame matrices of three replay snapshots (dorm, Tartarus climb, battle) and on host-built rotations, checked against
// atan2 on the host; the k_clump.c draw-node lists built node by node with the list-per-kind table and the two list
// predicates; the translucent queue up to its 128-node bound; the model alpha fade over its frames. Each call is one
// pair (hand vs recompiled, whole RAM, every register at every check point, the dead stack, the stand-ins' logs).
// =====================================================================================================================

namespace {

namespace rg = p3fes::recomp_gen;
using namespace p3fes::game::f7::draw;

Machine* draw_machine() {
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
float gf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void pf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }
float f0_of(Machine& m) {
    float v;
    std::memcpy(&v, &m.ctx.fpr[0], 4);
    return v;
}

HwCheck draw_check(u64 t0 = 0) {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in[GPR_T0] = t0;
    return hw;
}

using Live = std::map<u32, u32>;
struct World {
    Machine& m;
    Live live;
    int pairs = 0;
    u32 seed = 1;
    u32 call(Fn hand, Fn recomp, const Args& args, const char* what, u64 t0 = 0) {
        const Live carried = live;
        SiPair p = run_pair_si(m, hand, recomp, args, seed++, what, draw_check(t0), [carried](StandInWorld& w) {
            install_standard(w);
            for (const auto& [b, n] : carried) w.heap.reserve(b, n);
        });
        ++pairs;
        live = p.recomp->heap.live();
        return static_cast<u32>(p.hw.recomp.base.v0);
    }
};

constexpr u32 kArea = 0x01B80000u;  // the test's guest structures
constexpr float kPi = 3.14159265358979f;

void put_rotation(Machine& m, u32 va, float yaw, float pitch, float roll) {
    // R = Ry(yaw) * Rx(pitch) * Rz(roll), rows right / up / at as an RwMatrix (16 floats, flags word 3)
    const float cy = std::cos(yaw), sy = std::sin(yaw), cp = std::cos(pitch), sp = std::sin(pitch);
    const float cr = std::cos(roll), sr = std::sin(roll);
    const float r[3][3] = {{cy * cr + sy * sp * sr, cp * sr, -sy * cr + cy * sp * sr},
                           {-cy * sr + sy * sp * cr, cp * cr, sy * sr + cy * sp * cr},
                           {sy * cp, -sp, cy * cp}};
    float mtx[16] = {};
    for (int i = 0; i < 3; ++i)
        for (int k = 0; k < 3; ++k) mtx[4 * i + k] = r[i][k];
    mtx[12] = 10.0f;
    mtx[13] = -20.0f;
    mtx[14] = 30.0f;
    std::memcpy(m.at(va), mtx, 64);
    p32(m, va + 12, 3);  // rwMATRIXINTERNALIDENTITY-free flags: orthonormal
}

}  // namespace

TEST_CASE("game(field7_draw): the matrix angle helpers on the snapshots' camera frames and on built rotations") {
    Machine* mp = draw_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    World w{m, {}};
    constexpr u32 kMat = kArea;
    std::vector<std::pair<std::string, std::vector<u8>>> mats;
    for (const char* snap : {"dorm_replay_4900", "climb_ref_17000", "b_5800"}) {
        const std::vector<u8> s = read_snapshot(snap);
        if (s.empty()) continue;
        auto rd = [&](u32 va) {
            u32 v = 0;
            if (va + 4u <= s.size()) std::memcpy(&v, s.data() + va, 4);
            return v;
        };
        const u32 camera = rd(game::boot::kMainCamera);
        const u32 frame = camera ? rd(camera + 4u) : 0u;
        if (frame == 0 || frame + 0x90u > s.size()) continue;
        for (u32 off : {0x10u, 0x50u})  // the frame's modelling matrix and its LTM
            mats.emplace_back(std::string(snap) + (off == 0x10u ? " modelling" : " ltm"),
                              std::vector<u8>(s.begin() + frame + off, s.begin() + frame + off + 64));
    }
    std::mt19937 rng{0xA9u};
    int checked = 0;
    for (int i = 0; i < 40 + static_cast<int>(mats.size()); ++i) {
        std::string what;
        if (i < static_cast<int>(mats.size())) {
            std::memcpy(m.at(kMat), mats[static_cast<std::size_t>(i)].second.data(), 64);
            what = mats[static_cast<std::size_t>(i)].first;
        } else {
            const u32 a = rng();
            const u32 b = rng();
            const u32 c = rng();
            put_rotation(m, kMat, static_cast<float>(a % 3600u) / 1800.0f * kPi - kPi,
                         static_cast<float>(b % 1400u) / 1800.0f * kPi - 0.39f * kPi,
                         static_cast<float>(c % 1400u) / 1800.0f * kPi - 0.39f * kPi);
            what = "built rotation";
        }
        float mt[16];
        std::memcpy(mt, m.at(kMat), 64);
        const float yaw = -std::atan2(mt[2], mt[0]) * 180.0f / kPi;
        const float pitch = -std::atan2(mt[6], mt[5]) * 180.0f / kPi;
        const float roll = std::atan2(mt[4], mt[5]) * 180.0f / kPi;
        INFO(what);
        w.call(&rg::fn_sub_1A5AA0_001a5aa0, &rg::fn_sub_1A5AA0_001a5aa0__recomp, {sx(kMat), 0, 0, 0}, "sub_1A5AA0");
        CHECK(std::fabs(f0_of(m) - yaw) < 0.05f);
        w.call(&rg::fn_sub_1A5B30_001a5b30, &rg::fn_sub_1A5B30_001a5b30__recomp, {sx(kMat), 0, 0, 0}, "sub_1A5B30");
        CHECK(std::fabs(f0_of(m) - pitch) < 0.05f);
        w.call(&rg::fn_sub_1A5BC0_001a5bc0, &rg::fn_sub_1A5BC0_001a5bc0__recomp, {sx(kMat), 0, 0, 0}, "sub_1A5BC0");
        CHECK(std::fabs(f0_of(m) - roll) < 0.05f);
        CHECK(std::memcmp(m.at(kMat), mt, 64) == 0);  // the input is copied, not changed
        ++checked;
    }
    MESSAGE("matrix angles: " << mats.size() << " snapshot matrices, " << checked << " matrices, " << w.pairs << " pairs");
}

TEST_CASE("game(field7_draw): the draw-node lists take each kind's list and the predicates read them") {
    Machine* mp = draw_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    World w{m, {}};
    constexpr u32 kLists = kArea + 0x100u;
    static const int kListOfKind[10] = {2, 2, 5, 9, 10, 3, 4, 6, 7, 8};  // the jump table 0x7B6AA0, word index
    std::mt19937 rng{0xD7A0u};
    int nodes_total = 0;
    for (int round = 0; round < 8; ++round) {
        std::memset(m.at(kLists), 0, 44);
        w.live.clear();
        std::vector<u32> list[11];
        u32 flagged_count = 0;
        const int n = 1 + static_cast<int>(rng() % 24u);
        for (int i = 0; i < n; ++i) {
            const u32 kind = rng() % 12u;  // 10 and 11: no list (the bound check)
            const u32 value = rng();
            const u32 flagged = rng() % 3u;
            const u32 arg = rng();
            const u32 node = w.call(&rg::fn_sub_1A71A0_001a71a0, &rg::fn_sub_1A71A0_001a71a0__recomp,
                                    {sx(kLists), sx(kind), sx(value), sx(flagged)}, "sub_1A71A0", sx(arg));
            ++nodes_total;
            REQUIRE(node != 0);
            CHECK(g32(m, node + 0) == value);
            CHECK(g32(m, node + 4) == (flagged == 1 ? 1u : 0u));
            CHECK(g32(m, node + 8) == arg);
            for (u32 k = 0; k < 4; ++k) CHECK(gf(m, node + 12 + 4 * k) == 1.0f);
            if (flagged == 1) ++flagged_count;
            if (kind < 10) {
                const int l = kListOfKind[kind];
                CHECK(g32(m, node + 28) == (kind == 0 ? 1u : kind));
                CHECK(g32(m, node + kDrawNodeNext) == (list[l].empty() ? 0u : list[l].back()));
                list[l].push_back(node);
            }
            for (int l = 2; l <= 10; ++l) CHECK(g32(m, kLists + 4u * static_cast<u32>(l)) == (list[l].empty() ? 0u : list[l].back()));
            CHECK(g32(m, kLists + kListsNodes) == static_cast<u32>(i + 1));
            CHECK(g32(m, kLists + kListsFlagged) == flagged_count);
        }
        // the predicates over the built lists and with lists emptied
        for (int variant = 0; variant < 6; ++variant) {
            if (variant > 0) {
                const u32 l = 2u + rng() % 9u;
                p32(m, kLists + 4u * l, 0);
            }
            const bool has = g32(m, kLists) != 0 && (g32(m, kLists + 16) || g32(m, kLists + 12) || g32(m, kLists + 20) ||
                                                     g32(m, kLists + 36) || g32(m, kLists + 40));
            CHECK(w.call(&rg::fn_sub_1A7660_001a7660, &rg::fn_sub_1A7660_001a7660__recomp, {sx(kLists), 0, 0, 0},
                         "sub_1A7660") == (has ? 1u : 0u));
            CHECK(w.call(&rg::fn_sub_1A76E0_001a76e0, &rg::fn_sub_1A76E0_001a76e0__recomp, {sx(kLists), 0, 0, 0},
                         "sub_1A76E0") == (g32(m, kLists + 32) != 0 ? 1u : 0u));
        }
    }
    CHECK(w.call(&rg::fn_sub_1A7660_001a7660, &rg::fn_sub_1A7660_001a7660__recomp, {0, 0, 0, 0}, "sub_1A7660 NULL") == 0);
    CHECK(w.call(&rg::fn_sub_1A76E0_001a76e0, &rg::fn_sub_1A76E0_001a76e0__recomp, {0, 0, 0, 0}, "sub_1A76E0 NULL") == 0);
    // the translucent queue: 44-byte nodes copied in order; the 129th and 130th assert and still store (K_Assert
    // returns in retail)
    constexpr u32 kQueue = kArea + 0x1000u;
    constexpr u32 kNode = kArea + 0x100u;
    std::memset(m.at(kQueue), 0, 4 + 131 * 44);
    for (u32 i = 0; i < 130; ++i) {
        u32 words[11];
        for (u32& x : words) x = rng();
        std::memcpy(m.at(kNode), words, 44);
        w.call(&rg::fn_sub_1A8920_001a8920, &rg::fn_sub_1A8920_001a8920__recomp, {sx(kQueue), sx(kNode), 0, 0},
               "sub_1A8920");
        CHECK(g32(m, kQueue + kQueueCount) == i + 1u);
        CHECK(std::memcmp(m.at(kQueue + kQueueNodes + 44u * i), words, 44) == 0);
    }
    MESSAGE("draw lists: " << nodes_total << " nodes, " << w.pairs << " pairs");
}

TEST_CASE("game(field7_draw): the model alpha fade moves 1 / frames of the way each frame, then ends at the target") {
    Machine* mp = draw_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    World w{m, {}};
    constexpr u32 kTask = kArea + 0x2000u;
    constexpr u32 kWork = kArea + 0x2100u;
    constexpr u32 kModel = kArea + 0x3000u;  // a zeroed model record (mdlSetColor writes its colour)
    std::mt19937 rng{0xFADEu};
    int frames_run = 0;
    for (int round = 0; round < 10; ++round) {
        std::memset(m.at(kWork), 0, 32);
        std::memset(m.at(kModel), 0, 0x400);
        p32(m, kTask + kTaskWork, kWork);
        p32(m, kWork + kFadeModel, kModel);
        const float target = static_cast<float>(rng() % 256u);
        const float start = static_cast<float>(rng() % 256u);
        const u32 frames = rng() % 12u;
        pf(m, kWork + kFadeTarget, target);
        pf(m, kWork + kFadeAlpha, start);
        p32(m, kWork + kFadeFrames, frames);
        float alpha = start;
        for (u32 f = 0; f <= frames; ++f) {
            const u32 left = g32(m, kWork + kFadeFrames);
            const u32 r = w.call(&rg::fn_sub_1A5F30_001a5f30, &rg::fn_sub_1A5F30_001a5f30__recomp, {sx(kTask), 0, 0, 0},
                                 "sub_1A5F30");
            ++frames_run;
            if (left == 0) {
                CHECK(r == 0xFFFFFFFFu);  // done: the target alpha set
                CHECK(gf(m, kWork + kFadeAlpha) == alpha);
                break;
            }
            alpha = alpha + (target - alpha) / static_cast<float>(left);
            CHECK(r == 0);
            CHECK(std::fabs(gf(m, kWork + kFadeAlpha) - alpha) <= 1e-3f);
            CHECK(g32(m, kWork + kFadeFrames) == left - 1u);
        }
        // after the last step the alpha is the target (the moves add up to it)
        CHECK(std::fabs(gf(m, kWork + kFadeAlpha) - (frames ? target : start)) <= 1e-2f);
    }
    MESSAGE("model fade: " << frames_run << " frames, " << w.pairs << " pairs");
}

#else

TEST_CASE("game(field7_draw): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
