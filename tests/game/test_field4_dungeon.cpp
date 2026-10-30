// Pair tests of slice field4, Tartarus (game/src/field/field4_dungeon.cpp): every body against its recompiled body, on
//   * random worlds: the p3fes_handgen sweep;
//   * real machine states: the floor generator for block sets 1..7 with DUNGEONAT.BIN's cell bounds (its rules:
//     min..max cells, stairs at the start, no border cells, open sides lead to floor cells) and its reproducibility from
//     RpRandom's state alone (the same state in another snapshot gives the same bytes) -- the multiplayer property of
//     field4.h; the dungeon task's running / shutdown states, the floor-kind countdown, the cell exit lookup.
#include "handgen_pairs.h"
#include "field4_util.h"

#include "p3fes/game/field4.h"

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
void fn_sub_1BB300_001bb300(EEContext&);  // generated body
void fn_sub_1BB300_001bb300__recomp(EEContext&);  // recompiled
void fn_sub_1BCAC0_001bcac0(EEContext&);  // generated body
void fn_sub_1BCAC0_001bcac0__recomp(EEContext&);  // recompiled
void fn_sub_1BD450_001bd450(EEContext&);  // generated body
void fn_sub_1BD450_001bd450__recomp(EEContext&);  // recompiled
void fn_sub_1BD8C0_001bd8c0(EEContext&);  // generated body
void fn_sub_1BD8C0_001bd8c0__recomp(EEContext&);  // recompiled
void fn_sub_1BF220_001bf220(EEContext&);  // generated body
void fn_sub_1BF220_001bf220__recomp(EEContext&);  // recompiled
void fn_sub_1BF340_001bf340(EEContext&);  // generated body
void fn_sub_1BF340_001bf340__recomp(EEContext&);  // recompiled
void fn_K_FldDungeon_UpdateTask_001bf570(EEContext&);  // generated body
void fn_K_FldDungeon_UpdateTask_001bf570__recomp(EEContext&);  // recompiled
void fn_sub_1BFAF0_001bfaf0(EEContext&);  // generated body
void fn_sub_1BFAF0_001bfaf0__recomp(EEContext&);  // recompiled
void fn_K_FldDungeon_CreateTask_001bfbc0(EEContext&);  // generated body
void fn_K_FldDungeon_CreateTask_001bfbc0__recomp(EEContext&);  // recompiled
void fn_sub_1BFCC0_001bfcc0(EEContext&);  // generated body
void fn_sub_1BFCC0_001bfcc0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1BB300", 0x1BB300, &recomp_gen::fn_sub_1BB300_001bb300, &recomp_gen::fn_sub_1BB300_001bb300__recomp},
    {"sub_1BCAC0", 0x1BCAC0, &recomp_gen::fn_sub_1BCAC0_001bcac0, &recomp_gen::fn_sub_1BCAC0_001bcac0__recomp},
    {"sub_1BD450", 0x1BD450, &recomp_gen::fn_sub_1BD450_001bd450, &recomp_gen::fn_sub_1BD450_001bd450__recomp},
    {"sub_1BD8C0", 0x1BD8C0, &recomp_gen::fn_sub_1BD8C0_001bd8c0, &recomp_gen::fn_sub_1BD8C0_001bd8c0__recomp},
    {"sub_1BF220", 0x1BF220, &recomp_gen::fn_sub_1BF220_001bf220, &recomp_gen::fn_sub_1BF220_001bf220__recomp},
    {"sub_1BF340", 0x1BF340, &recomp_gen::fn_sub_1BF340_001bf340, &recomp_gen::fn_sub_1BF340_001bf340__recomp},
    {"K_FldDungeon_UpdateTask", 0x1BF570, &recomp_gen::fn_K_FldDungeon_UpdateTask_001bf570, &recomp_gen::fn_K_FldDungeon_UpdateTask_001bf570__recomp},
    {"sub_1BFAF0", 0x1BFAF0, &recomp_gen::fn_sub_1BFAF0_001bfaf0, &recomp_gen::fn_sub_1BFAF0_001bfaf0__recomp},
    {"K_FldDungeon_CreateTask", 0x1BFBC0, &recomp_gen::fn_K_FldDungeon_CreateTask_001bfbc0, &recomp_gen::fn_K_FldDungeon_CreateTask_001bfbc0__recomp},
    {"sub_1BFCC0", 0x1BFCC0, &recomp_gen::fn_sub_1BFCC0_001bfcc0, &recomp_gen::fn_sub_1BFCC0_001bfcc0__recomp},
};

// The generic sweep: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field4 dungeon): every body equals its recompiled body on random worlds") {
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
namespace cell = game::f4::cell;
namespace dng = game::f4::dng;

constexpr u32 kGrid = kSField + fld::kGrid;
u32 cell_va(u32 x, u32 z) { return kGrid + cell::kRow * z + cell::kSize * x; }

// RpRandom's state (sub_488F30, field4.h): the plugin block at RwEngineInstance 0x960070 + the plugin offset 0x7CE778
// holds {table, ptr1, ptr2, end}; the 31-word table follows.
struct RandState {
    std::array<u32, 4> ptrs{};
    std::array<u32, 31> table{};
};
u32 rand_block(Machine& m) { return 0x960070u + r32(m, 0x7CE778u); }
RandState rand_state(Machine& m) {
    RandState s;
    const u32 b = rand_block(m);
    for (int i = 0; i < 4; ++i) s.ptrs[i] = r32(m, b + 4 * i);
    for (int i = 0; i < 31; ++i) s.table[i] = r32(m, s.ptrs[0] + 4 * i);
    return s;
}
// Puts a state into a machine whose plugin block lives elsewhere: the pointers are rebased onto its table.
void set_rand_state(Machine& m, const RandState& s) {
    const u32 b = rand_block(m);
    const u32 table = r32(m, b);
    for (int i = 1; i < 4; ++i) w32(m, b + 4 * i, table + (s.ptrs[i] - s.ptrs[0]));
    for (int i = 0; i < 31; ++i) w32(m, table + 4 * i, s.table[i]);
}
// The generator runs ~10^5..10^6 check points (more than hgp::pair's runaway cut): paired with run_pair_hw over all RAM,
// the registers and cycles compared at the end (the faithfulness audit compares them at every check point).
void generate(Machine& m, u32 set, u32 seed) {
    const Case& c = find_case("sub_1BD450");
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_dead_stack = true;
    run_pair_hw(m, c.hand, c.recomp, {set, 0, 0, 0}, seed, c.name, hw);
}
// The generator's output: the header bytes +60..+65 (start / seed cells and turns) and the 4,096-byte grid.
std::vector<u8> grid_bytes(Machine& m) {
    std::vector<u8> v(m.at(kSField + fld::kStartX), m.at(kSField + fld::kSeedRot) + 1);
    v.insert(v.end(), m.at(kGrid), m.at(kGrid) + 4096);
    return v;
}

struct FloorStats {
    int floor_cells = 0, stairs = 0, border_bad = 0, door_bad = 0;
};
FloorStats stats(Machine& m) {
    FloorStats s;
    for (u32 z = 0; z < 16; ++z)
        for (u32 x = 0; x < 16; ++x) {
            const u32 c = cell_va(x, z);
            const u8 st = r8(m, c + cell::kState);
            const bool border = x == 0 || z == 0 || x == 15 || z == 15;
            if (border && st == 1) ++s.border_bad;
            if (st != 1) continue;
            ++s.floor_cells;
            if (r8(m, c + cell::kKind) == 4) ++s.stairs;
            // an open side leads to a floor cell (bits 4..7: z-1, x-1, z+1, x+1)
            const u8 doors = r8(m, c + cell::kDoors);
            const int dx[4] = {0, -1, 0, 1}, dz[4] = {-1, 0, 1, 0};
            for (int k = 0; k < 4; ++k) {
                if (!(doors & (0x10 << k))) continue;
                const int nx = static_cast<int>(x) + dx[k], nz = static_cast<int>(z) + dz[k];
                if (nx < 0 || nz < 0 || nx > 15 || nz > 15 || r8(m, cell_va(nx, nz) + cell::kState) != 1) ++s.door_bad;
            }
        }
    return s;
}
}  // namespace

// The Tartarus floor generator (sub_1BD450 -> sub_1BCAC0) on real machine states: for each block set 1..7 with the
// first floor's cell bounds of DUNGEONAT.BIN (field4.h dngfloor +6 / +7), the hand-written and recompiled generators
// make the same grid (the pair compares all RAM), and the grid keeps the documented rules: min..max floor cells, the
// start cell a stairs block (kind 4), at least two stairs, nothing on the border ring, every open side leading to a
// floor cell. Then the multiplayer property (field4.h): the layout depends only on the set, the bounds and RpRandom's
// state -- the same state put into another machine (another snapshot, other grid contents) gives the same bytes.
TEST_CASE("game(field4 dungeon): the floor generator on real states, its rules and its reproducibility") {
    std::vector<u8> base, base2;
    auto mp = real_machine("climb_ref_17000", base);
    auto mp2 = real_machine("shop_ref_4100", base2);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    const auto table = read_extracted("DATA/FIELD/TABLE/DUNGEONAT.BIN");
    const u32 first_floor[8] = {0, 2, 17, 65, 115, 165, 215, 290};
    int generated = 0;
    for (u32 set = 1; set <= 7; ++set) {
        reset(m, base);
        u8 lo = 30, hi = 50;
        if (table.size() >= 16 * 300) {
            lo = table[16 * first_floor[set] + 6];
            hi = table[16 * first_floor[set] + 7];
        }
        w8(m, kSField + fld::kMinCells, lo);
        w8(m, kSField + fld::kMaxCells, hi);
        const RandState before = rand_state(m);
        generate(m, set, set);
        ++generated;
        const FloorStats s = stats(m);
        CHECK(s.floor_cells >= lo);
        CHECK(s.floor_cells <= hi);
        CHECK(s.stairs >= 2);
        CHECK(s.border_bad == 0);
        CHECK(s.door_bad == 0);
        const u32 sx = r8(m, kSField + fld::kStartX), sz = r8(m, kSField + fld::kStartZ);
        CHECK(r8(m, cell_va(sx, sz) + cell::kState) == 1);
        CHECK(r8(m, cell_va(sx, sz) + cell::kKind) == 4);
        CHECK(r32(m, gpv(game::f4::gpv::kGenFailed)) == 0);
        const std::vector<u8> grid = grid_bytes(m);
        // the same RpRandom state and inputs, other grid contents: the same layout
        reset(m, base);
        std::memset(m.at(kGrid), 0x5A, 4096);
        w8(m, kSField + fld::kMinCells, lo);
        w8(m, kSField + fld::kMaxCells, hi);
        generate(m, set, set + 100);
        CHECK(grid_bytes(m) == grid);
        // ... and in another machine (shop_ref_4100: a town field, its own heap and tasks) given that state
        if (mp2) {
            Machine& m2 = *mp2;
            reset(m2, base2);
            set_rand_state(m2, before);
            w8(m2, kSField + fld::kMinCells, lo);
            w8(m2, kSField + fld::kMaxCells, hi);
            generate(m2, set, set + 200);
            CHECK(grid_bytes(m2) == grid);
        }
        // a different state: (almost surely) a different floor
        reset(m, base);
        RandState other = before;
        other.table[3] ^= 0x13579BDFu;
        set_rand_state(m, other);
        w8(m, kSField + fld::kMinCells, lo);
        w8(m, kSField + fld::kMaxCells, hi);
        generate(m, set, set + 300);
        MESSAGE("set " << set << ": " << s.floor_cells << " floor cells (" << int(lo) << ".." << int(hi) << "), " << s.stairs
                       << " stairs, start (" << sx << "," << sz << "); another RpRandom state "
                       << std::string(grid_bytes(m) == grid ? "gave the same floor" : "gave another floor"));
    }
    CHECK(generated > 0);
}

// The automatic dungeon on climb_ref_17000 (floor 5, the fixed floor 51/4, state 3): the running state only watches the
// shutdown word; the floor-kind pick on the real g_data counters (field4.h: c12 the highest floor, c58 / c59 the
// countdown): a countdown above 1 only counts down; the exit-marker lookup of every grid cell.
TEST_CASE("game(field4 dungeon): the dungeon task, the floor kind and the cell exits on climb_ref_17000") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 task = r32(m, gpv(game::f4::gpv::kDungeonTask));
    REQUIRE(task != 0);
    const u32 work = r32(m, task + game::f4::kTaskWork);
    CHECK(r32(m, work + dng::kFloor) == 5);
    CHECK(r32(m, work + dng::kFloorTable) == game::f4::dngfloor::kTable);
    CHECK(r32(m, work + dng::kRoot) == r32(m, kSField + fld::kRoot));
    if (r32(m, work + dng::kState) == 3) {
        hgp::Run r = call(m, "K_FldDungeon_UpdateTask", {task, 0, 0, 0});
        CHECK(v0_of(r) == 0);
        CHECK(r32(m, work + dng::kState) == 3);
        w32(m, work + dng::kShutdown, 1);
        call(m, "K_FldDungeon_UpdateTask", {task, 0, 0, 0}, 2);
        CHECK(r32(m, work + dng::kState) == 9);
        CHECK(v0_of(call(m, "K_FldDungeon_UpdateTask", {task, 0, 0, 0}, 3)) == -1);
        reset(m, base);
    }
    // the floor kind: the counters at 0x83A4DC (sub_16F380)
    const u32 counters = 0x83A4DCu;
    for (u32 floor : {2u, 3u, 17u, 30u}) {
        for (s32 countdown : {0, 1, 2, 5}) {
            reset(m, base);
            w32(m, counters + 4 * 59, static_cast<u32>(countdown));
            w32(m, counters + 4 * 12, 300);  // the highest floor reached above the current one
            const s64 kind = v0_of(call(m, "sub_1BF340", {game::f4::dngfloor::kTable + 16 * floor, 0, 0, 0}, floor));
            CHECK(kind >= 0);
            CHECK(kind <= 4);
            if (countdown > 1) {
                CHECK(kind == 0);
                CHECK(rs32(m, counters + 4 * 59) == countdown - 1);
            }
            if (countdown < 1) CHECK(rs32(m, counters + 4 * 59) == rs32(m, counters + 4 * 58));
        }
    }
    reset(m, base);
    w32(m, counters + 4 * 12, 0);  // at or above the highest floor reached: kind 0
    CHECK(v0_of(call(m, "sub_1BF340", {game::f4::dngfloor::kTable + 16 * 2, 0, 0, 0}, 9)) == 0);
    reset(m, base);
    int with_exit = 0;
    for (u32 z = 0; z < 16; ++z)
        for (u32 x = 0; x < 16; ++x) {
            call(m, "sub_1BF220", {kScratch, x, z, 0}, 16 * z + x + 1);
            with_exit += (r32(m, kScratch) | r32(m, kScratch + 4) | r32(m, kScratch + 8)) != 0;
        }
    MESSAGE("climb floor 5: " << with_exit << " cells with an exit marker position");
}
// --- end of the field4 tests ---

#else

TEST_CASE("game(field4 dungeon): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
