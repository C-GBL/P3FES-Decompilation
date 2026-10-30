// Pair tests of slice sweep3 (game/src/battle/sweep3.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the packet's replay snapshots (dorm_replay_4900, b_5800, climb_ref_17000, fusion_ref_6300, shop_ref_4100) with
//     arguments drawn from their real structures: gBtl's btlActions (the action-state bodies), the battle camera
//     gBtl+32 aimed at a real action (the camera shots), the gBtl+400 list of 36-byte records;
//   * documented rules: the move pick of sub_295A10 and the exchange init of sub_2964F0 on b_5800's real actions, the
//     gBtl+400 record unlink (sub_2BB610). sub_2DCE90 is hand-written since finalB; test_battle9.cpp stands it in.
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
#include "handgen_pairs.h"
#include "sweep2_util.h"

#include "p3fes/game/sweep3.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
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
using namespace p3fes::game_test::s2t;

namespace p3fes::recomp_gen {
void fn_sub_294D40_00294d40(EEContext&);  // generated body
void fn_sub_294D40_00294d40__recomp(EEContext&);  // recompiled
void fn_sub_295160_00295160(EEContext&);  // generated body
void fn_sub_295160_00295160__recomp(EEContext&);  // recompiled
void fn_sub_295A10_00295a10(EEContext&);  // generated body
void fn_sub_295A10_00295a10__recomp(EEContext&);  // recompiled
void fn_sub_295C00_00295c00(EEContext&);  // generated body
void fn_sub_295C00_00295c00__recomp(EEContext&);  // recompiled
void fn_sub_295FA0_00295fa0(EEContext&);  // generated body
void fn_sub_295FA0_00295fa0__recomp(EEContext&);  // recompiled
void fn_sub_2964F0_002964f0(EEContext&);  // generated body
void fn_sub_2964F0_002964f0__recomp(EEContext&);  // recompiled
void fn_sub_296660_00296660(EEContext&);  // generated body
void fn_sub_296660_00296660__recomp(EEContext&);  // recompiled
void fn_sub_297760_00297760(EEContext&);  // generated body
void fn_sub_297760_00297760__recomp(EEContext&);  // recompiled
void fn_sub_2A6EE0_002a6ee0(EEContext&);  // generated body
void fn_sub_2A6EE0_002a6ee0__recomp(EEContext&);  // recompiled
void fn_sub_2B1BC0_002b1bc0(EEContext&);  // generated body
void fn_sub_2B1BC0_002b1bc0__recomp(EEContext&);  // recompiled
void fn_sub_2B47B0_002b47b0(EEContext&);  // generated body
void fn_sub_2B47B0_002b47b0__recomp(EEContext&);  // recompiled
void fn_sub_2B4C00_002b4c00(EEContext&);  // generated body
void fn_sub_2B4C00_002b4c00__recomp(EEContext&);  // recompiled
void fn_sub_2B5000_002b5000(EEContext&);  // generated body
void fn_sub_2B5000_002b5000__recomp(EEContext&);  // recompiled
void fn_sub_2B5240_002b5240(EEContext&);  // generated body
void fn_sub_2B5240_002b5240__recomp(EEContext&);  // recompiled
void fn_sub_2B56E0_002b56e0(EEContext&);  // generated body
void fn_sub_2B56E0_002b56e0__recomp(EEContext&);  // recompiled
void fn_sub_2B5CD0_002b5cd0(EEContext&);  // generated body
void fn_sub_2B5CD0_002b5cd0__recomp(EEContext&);  // recompiled
void fn_sub_2B6070_002b6070(EEContext&);  // generated body
void fn_sub_2B6070_002b6070__recomp(EEContext&);  // recompiled
void fn_sub_2BB610_002bb610(EEContext&);  // generated body
void fn_sub_2BB610_002bb610__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_294D40", 0x294D40, &recomp_gen::fn_sub_294D40_00294d40, &recomp_gen::fn_sub_294D40_00294d40__recomp},
    {"sub_295160", 0x295160, &recomp_gen::fn_sub_295160_00295160, &recomp_gen::fn_sub_295160_00295160__recomp},
    {"sub_295A10", 0x295A10, &recomp_gen::fn_sub_295A10_00295a10, &recomp_gen::fn_sub_295A10_00295a10__recomp},
    {"sub_295C00", 0x295C00, &recomp_gen::fn_sub_295C00_00295c00, &recomp_gen::fn_sub_295C00_00295c00__recomp},
    {"sub_295FA0", 0x295FA0, &recomp_gen::fn_sub_295FA0_00295fa0, &recomp_gen::fn_sub_295FA0_00295fa0__recomp},
    {"sub_2964F0", 0x2964F0, &recomp_gen::fn_sub_2964F0_002964f0, &recomp_gen::fn_sub_2964F0_002964f0__recomp},
    {"sub_296660", 0x296660, &recomp_gen::fn_sub_296660_00296660, &recomp_gen::fn_sub_296660_00296660__recomp},
    {"sub_297760", 0x297760, &recomp_gen::fn_sub_297760_00297760, &recomp_gen::fn_sub_297760_00297760__recomp},
    {"sub_2A6EE0", 0x2A6EE0, &recomp_gen::fn_sub_2A6EE0_002a6ee0, &recomp_gen::fn_sub_2A6EE0_002a6ee0__recomp},
    {"sub_2B1BC0", 0x2B1BC0, &recomp_gen::fn_sub_2B1BC0_002b1bc0, &recomp_gen::fn_sub_2B1BC0_002b1bc0__recomp},
    {"sub_2B47B0", 0x2B47B0, &recomp_gen::fn_sub_2B47B0_002b47b0, &recomp_gen::fn_sub_2B47B0_002b47b0__recomp},
    {"sub_2B4C00", 0x2B4C00, &recomp_gen::fn_sub_2B4C00_002b4c00, &recomp_gen::fn_sub_2B4C00_002b4c00__recomp},
    {"sub_2B5000", 0x2B5000, &recomp_gen::fn_sub_2B5000_002b5000, &recomp_gen::fn_sub_2B5000_002b5000__recomp},
    {"sub_2B5240", 0x2B5240, &recomp_gen::fn_sub_2B5240_002b5240, &recomp_gen::fn_sub_2B5240_002b5240__recomp},
    {"sub_2B56E0", 0x2B56E0, &recomp_gen::fn_sub_2B56E0_002b56e0, &recomp_gen::fn_sub_2B56E0_002b56e0__recomp},
    {"sub_2B5CD0", 0x2B5CD0, &recomp_gen::fn_sub_2B5CD0_002b5cd0, &recomp_gen::fn_sub_2B5CD0_002b5cd0__recomp},
    {"sub_2B6070", 0x2B6070, &recomp_gen::fn_sub_2B6070_002b6070, &recomp_gen::fn_sub_2B6070_002b6070__recomp},
    {"sub_2BB610", 0x2BB610, &recomp_gen::fn_sub_2BB610_002bb610, &recomp_gen::fn_sub_2BB610_002bb610__recomp},
};

// The argument kinds of each case (a0..a3, then $t0): A a btlAction of gBtl's list, C the battle camera gBtl+32 (its
// +224 aimed at a btlAction first), L a record of the gBtl+400 list, F a gFldUnitsEc slot, E an encounter word
// (kind << 16 | id), B a cleared 1 KiB block (small counts at +56 / +140, pointers to cleared blocks at +60 / +64),
// n a small id 0..7, z 0 / 1, h an s16 -1..299, - no argument (random small).
const std::map<std::string, const char*> kKinds = {
    {"sub_294D40", "A"},   {"sub_295160", "A"},    {"sub_295A10", "A"},    {"sub_295C00", "A"},   {"sub_295FA0", "A"},
    {"sub_2964F0", "A"},   {"sub_296660", "A"},    {"sub_297760", "A"},    {"sub_2A6EE0", "C"},   {"sub_2B1BC0", "C"},
    {"sub_2B47B0", "C"},   {"sub_2B4C00", "C"},    {"sub_2B5000", "C"},    {"sub_2B5240", "C"},   {"sub_2B56E0", "C"},
    {"sub_2B5CD0", "C"},   {"sub_2B6070", "C"},    {"sub_2BB610", "L"},
};

constexpr u32 kGBtl = 0x7CE3ECu;          // gBtl's slot ($gp - 18692)
constexpr u32 kActLinkNext = 1192;        // btlAction: the next action of gBtl+332's list (battle_core2.h)
constexpr u32 kActUnit = 48;              // btlAction: its btlUnit
constexpr u32 kCamera = 32;               // gBtl: the battle camera record (the shots' $a0)
constexpr u32 kCamAction = 224;           // camera: the btlAction it frames
constexpr u32 kRecList = 400;             // gBtl: head of the 36-byte record list (+28 previous, +32 next)
constexpr u32 kFldUnitsEc = 0x86EDA0u;    // gFldUnitsEc: 24 encounter units of 448 bytes (+72 the DatUnitEc, 0 = free)
constexpr u32 kFldUnitSize = 448;

struct Objects {
    u32 btl = 0;
    std::vector<u32> acts, recs, fld;
};

Objects objects_of(Machine& m) {
    Objects o;
    o.btl = r32(m, kGBtl);
    if (o.btl >= 0x100000u && o.btl < EEMemory::kMainRamSize) {
        for (u32 a = r32(m, o.btl + 332); a && a < EEMemory::kMainRamSize && o.acts.size() < 32; a = r32(m, a + kActLinkNext))
            if (r32(m, a + kActUnit) != 0) o.acts.push_back(a);
        for (u32 r = r32(m, o.btl + kRecList); r && r < EEMemory::kMainRamSize && o.recs.size() < 64; r = r32(m, r + 32))
            o.recs.push_back(r);
    } else {
        o.btl = 0;
    }
    for (u32 i = 0; i < 24; ++i) o.fld.push_back(kFldUnitsEc + kFldUnitSize * i);
    return o;
}

bool needs_battle(const char* kinds) {
    for (const char* k = kinds; *k; ++k)
        if (*k == 'A' || *k == 'C' || *k == 'L') return true;
    return false;
}

// One argument of kind `k` (writes the world it needs); B blocks come from kScratch upwards.
u64 arg_of(Machine& m, char k, const Objects& o, std::mt19937& rng, u32& blk) {
    switch (k) {
    case 'A': return o.acts[rng() % o.acts.size()];
    case 'C': {
        const u32 cam = o.btl + kCamera;
        w32(m, cam + kCamAction, o.acts[rng() % o.acts.size()]);
        return cam;
    }
    case 'L': return o.recs.empty() ? 0 : o.recs[rng() % o.recs.size()];
    case 'F': return o.fld[rng() % o.fld.size()];
    case 'E': {
        static const u32 kinds[] = {1, 2, 4};
        return (static_cast<u64>(kinds[rng() % 3]) << 16) | (rng() % 400);
    }
    case 'B': {
        const u32 b = kScratch + 0x4000u * blk++;
        std::memset(m.at(b), 0, 0x3000);
        w32(m, b + 56, 1 + rng() % 4);
        w32(m, b + 140, rng() % 6);
        w32(m, b + 60, b + 0x400);
        w32(m, b + 64, b + 0x800);
        w32(m, b + 0x800 + 56, 1 + rng() % 3);
        for (u32 i = 0; i < 16; ++i) wf32(m, b + 256 + 4 * i, static_cast<f32>(static_cast<int>(rng() % 1601) - 800));
        return b;
    }
    case 'n': return rng() % 8;
    case 'z': return rng() % 2;
    case 'h': return static_cast<u64>(static_cast<s64>(static_cast<int>(rng() % 301) - 1));
    default: return rng() % 8;
    }
}

}  // namespace

TEST_CASE("game(sweep3): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// Every body on the packet's snapshots: arguments from the real structures (above), the snapshot restored between pairs.
// The pairs run on the stand-ins (every callee this build does not emit recorded); a pair whose original faults is run
// again as a plain pair, which compares the two stops.
TEST_CASE("game(sweep3): every body on the replay snapshots with real structures") {
    struct Snap {
        const char* dir;
        u32 reps;
    };
    const Snap snaps[] = {{"b_5800", 12}, {"dorm_replay_4900", 3}, {"climb_ref_17000", 3}, {"fusion_ref_6300", 2}, {"shop_ref_4100", 2}};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    int pairs = 0, stood = 0, stops = 0, used = 0;
    std::map<std::string, int> stop_of;
    for (const Snap& sn : snaps) {
        std::vector<u8> base;
        auto mp = real_machine(sn.dir, base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or snapshot " << std::string(sn.dir));
            continue;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        const Objects o = objects_of(m);
        ++used;
        MESSAGE(std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions, " << o.recs.size() << " +400 records");
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            const char* kinds = kKinds.at(c.name);
            if (needs_battle(kinds) && (o.btl == 0 || o.acts.empty())) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                const std::mt19937 rng0{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                u64 a[5] = {};
                // the arguments and the world they need (the same draws after every reset)
                auto draw = [&](Machine& mm) {
                    std::mt19937 rng = rng0;
                    u32 blk = 0;
                    for (u64& x : a) x = rng() % 8;
                    for (std::size_t i = 0; i < 5 && kinds[i]; ++i) a[i] = arg_of(mm, kinds[i], o, rng, blk);
                    return rng();
                };
                const u32 seed = draw(m);
                ++pairs;
                try {
                    // the stand-in pair: heap, printf / sprintf, the file layer; every not-emitted callee recorded
                    run_case(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); }, 0,
                             {{GPR_T0, a[4]}});
                    ++stood;
                } catch (const rt_test::FatalEvent&) {
                    // a guest fault in the original: the plain pair compares the two stops
                    reset(m, base);
                    draw(m);
                    HwCheck h = hw;
                    h.gpr_in[GPR_T0] = a[4];
                    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, Args{a[0], a[1], a[2], a[3]}, seed, c.name, h);
                    if (r.stopped) {
                        ++stops;
                        ++stop_of[std::string(c.name) + " (" + r.what.substr(0, 40) + " at " + hex64(r.stop_pc) + ")"];
                    }
                }
                reset(m, base);
            }
        }
    }
    std::string why;
    for (const auto& [k, n] : stop_of) why += " " + k + " x" + std::to_string(n) + ";";
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stood << " on the stand-ins, " << stops
                          << " ended at a compared fault stop:" << why.substr(0, 1500));
}

// sub_2BB610 (release a gBtl+400 record): it resets the record (+0 = 512, +4 = -1, +8 = 20, +12 = 0), unlinks it
// (+28 previous, +32 next; the head gBtl+400 when it has no previous) and hands it to the free hook *(0x96017C).
TEST_CASE("game(sweep3): sub_2BB610 unlinks a gBtl+400 record") {
    std::vector<u8> base;
    auto mp = real_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot b_5800");
        return;
    }
    Machine& m = *mp;
    const u32 btl = r32(m, kGBtl);
    REQUIRE(btl != 0u);
    const u32 hook = r32(m, 0x96017Cu);
    const u32 A = kScratch, B = kScratch + 0x40, C = kScratch + 0x80;
    auto build = [&](Machine& mm) {
        std::memset(mm.at(kScratch), 0, 0x100);
        for (u32 r : {A, B, C}) {
            w16(mm, r, 0x123);
            w32(mm, r + 4, 7);
            w8(mm, r + 8, 3);
            w32(mm, r + 12, 9);
        }
        w32(mm, btl + kRecList, A);
        w32(mm, A + 32, B);
        w32(mm, B + 28, A);
        w32(mm, B + 32, C);
        w32(mm, C + 28, B);
    };
    auto world = [hook](StandInWorld& w) {
        if (hook != 0 && !w.si.has(hook)) w.si.install_recorder(hook, "free hook", 0);
    };
    for (const u32 victim : {B, A, C}) {
        const SiPair sp = run_case_w(m, base, kCases, "sub_2BB610", {victim, 0, 0, 0}, 840 + (victim - A), build, world);
        INFO("record +" << (victim - A));
        CHECK(r16(m, victim) == 512u);
        CHECK(r32(m, victim + 4) == 0xFFFFFFFFu);
        CHECK(r8(m, victim + 8) == 20u);
        CHECK(r32(m, victim + 12) == 0u);
        if (victim == B) {
            CHECK(r32(m, A + 32) == C);
            CHECK(r32(m, C + 28) == A);
            CHECK(r32(m, btl + kRecList) == A);
        } else if (victim == A) {
            CHECK(r32(m, btl + kRecList) == B);
            CHECK(r32(m, B + 28) == 0u);
        } else {
            CHECK(r32(m, B + 32) == 0u);
            CHECK(r32(m, btl + kRecList) == A);
        }
        const auto c = calls(sp, hook);
        REQUIRE(c.size() == 1u);
        CHECK(c[0].args[0] == victim);
    }
}

// Two action-state bodies on b_5800's real btlActions: sub_295A10 picks the move (+108 = 2) and sets +24 bit 1 (the
// other bits kept); sub_2964F0 sets +24 bit 9 and starts sub_296660's count-down (+1156 = +1160 = 0, +1164 = 12).
TEST_CASE("game(sweep3): the move pick and the exchange init on real actions") {
    std::vector<u8> base;
    auto mp = real_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot b_5800");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const Objects o = objects_of(m);
    REQUIRE(!o.acts.empty());
    u32 seed = 880;
    for (const u32 act : o.acts) {
        INFO("action " << hex64(act));
        const u16 flags = r16(m, act + 24);
        run_case_w(m, base, kCases, "sub_295A10", {act, 0, 0, 0}, ++seed, {});
        CHECK(r16(m, act + 108) == 2u);
        CHECK(r16(m, act + 24) == static_cast<u16>(flags | 2u));
        run_case_w(m, base, kCases, "sub_2964F0", {act, 0, 0, 0}, ++seed, {});
        CHECK(r16(m, act + 24) == static_cast<u16>(flags | 0x200u));
        CHECK(r32(m, act + 1156) == 0u);
        CHECK(r32(m, act + 1160) == 0u);
        CHECK(r16(m, act + 1164) == 12u);
    }
}
#else

TEST_CASE("game(sweep3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
