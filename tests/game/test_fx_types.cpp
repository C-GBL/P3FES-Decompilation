// Phase 5 pair tests for the fx_types slice (game/src/fx/fx_types.cpp): the effect system's effect-type handlers, the
// band 0x324160-0x34C160. Each hand-written function and the recompiled body it replaces run on identical guest machines
// built from a random "pointer soup" world -- 64 KiB whose words are pointers back into the world (16-byte aligned),
// small integers, plain floats and noise, so every chain of loads a handler follows stays inside it -- plus the records
// a function reads by shape (effect records with a class number and an instance, filter instances with a kind and a
// frame counter, effect parts, the gp-relative shake state). The class table 0x69BE20 and the kind rows of the filters
// (0x69CB98 / 0x69CC58) are the ELF's own; per case some slots are re-aimed at callbacks of the emitted set: leaves
// (0x3C4400 `v0 = 0`, identity, `v0 = a1`, 1) and a non-leaf that spills $ra below the $sp it receives
// (0x1F1C50). A slot left at a real handler the test build does not emit stops the run with a fatal event; both runs
// must stop at the same callee with the same machine state (likewise the layer manager 0x3210A0..0x3211D0, the
// fx_layers slice's range, which is left out of the emitted set on purpose).
//
// Stricter than the Outcome (run_pair_hw): per pair this file compares EVERY general register in 128 bits, HI/LO, all
// FPU registers, ACC and FCR31 and the whole VU0 register file at the return, the whole register file and the cycle
// count at EVERY check point, the WHOLE 32 MiB of RAM (PairRange: only the pages written are copied), the dead stack,
// the scratchpad, the bus log, the virtual cycles and the check-point count. FPRs, ACC, HI/LO and the VU0 registers
// start random, so a register the original leaves alone must stay alone. Host-side checks restate documented
// behaviour (fx_types.h), and the replay snapshots (battle_ref_6150 / b_5800 / dorm_replay_4900) are used where present:
// the whole snapshot RAM is loaded and the handlers run on the live effect state.
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/game/fx_types.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
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
P3FES_DECL_PAIR(fn_sub_3243D0_003243d0)
P3FES_DECL_PAIR(fn_sub_3244C0_003244c0)
P3FES_DECL_PAIR(fn_sub_3245B0_003245b0)
P3FES_DECL_PAIR(fn_sub_3245F0_003245f0)
P3FES_DECL_PAIR(fn_sub_324630_00324630)
P3FES_DECL_PAIR(fn_sub_324640_00324640)
P3FES_DECL_PAIR(fn_sub_324650_00324650)
P3FES_DECL_PAIR(fn_sub_324660_00324660)
P3FES_DECL_PAIR(fn_sub_324670_00324670)
P3FES_DECL_PAIR(fn_sub_324930_00324930)
P3FES_DECL_PAIR(fn_sub_324990_00324990)
P3FES_DECL_PAIR(fn_sub_3249E0_003249e0)
P3FES_DECL_PAIR(fn_sub_324A30_00324a30)
P3FES_DECL_PAIR(fn_sub_324A90_00324a90)
P3FES_DECL_PAIR(fn_sub_324AF0_00324af0)
P3FES_DECL_PAIR(fn_sub_324B50_00324b50)
P3FES_DECL_PAIR(fn_sub_326160_00326160)
P3FES_DECL_PAIR(fn_sub_326170_00326170)
P3FES_DECL_PAIR(fn_sub_326180_00326180)
P3FES_DECL_PAIR(fn_sub_326190_00326190)
P3FES_DECL_PAIR(fn_sub_3261C0_003261c0)
P3FES_DECL_PAIR(fn_sub_326200_00326200)
P3FES_DECL_PAIR(fn_sub_326240_00326240)
P3FES_DECL_PAIR(fn_sub_327220_00327220)
P3FES_DECL_PAIR(fn_sub_329350_00329350)
P3FES_DECL_PAIR(fn_sub_3293A0_003293a0)
P3FES_DECL_PAIR(fn_sub_3293D0_003293d0)
P3FES_DECL_PAIR(fn_sub_329430_00329430)
P3FES_DECL_PAIR(fn_sub_329460_00329460)
P3FES_DECL_PAIR(fn_sub_329490_00329490)
P3FES_DECL_PAIR(fn_sub_3294A0_003294a0)
P3FES_DECL_PAIR(fn_sub_329740_00329740)
P3FES_DECL_PAIR(fn_sub_3297A0_003297a0)
P3FES_DECL_PAIR(fn_sub_32A540_0032a540)
P3FES_DECL_PAIR(fn_sub_3321D0_003321d0)
P3FES_DECL_PAIR(fn_sub_332200_00332200)
P3FES_DECL_PAIR(fn_sub_332210_00332210)
P3FES_DECL_PAIR(fn_sub_3322B0_003322b0)
P3FES_DECL_PAIR(fn_sub_3322D0_003322d0)
P3FES_DECL_PAIR(fn_sub_3322F0_003322f0)
P3FES_DECL_PAIR(fn_sub_332310_00332310)
P3FES_DECL_PAIR(fn_sub_332330_00332330)
P3FES_DECL_PAIR(fn_sub_332B30_00332b30)
P3FES_DECL_PAIR(fn_sub_333020_00333020)
P3FES_DECL_PAIR(fn_sub_333050_00333050)
P3FES_DECL_PAIR(fn_sub_333080_00333080)
P3FES_DECL_PAIR(fn_sub_3330B0_003330b0)
P3FES_DECL_PAIR(fn_sub_3338B0_003338b0)
P3FES_DECL_PAIR(fn_sub_333900_00333900)
P3FES_DECL_PAIR(fn_sub_333920_00333920)
P3FES_DECL_PAIR(fn_sub_333940_00333940)
P3FES_DECL_PAIR(fn_sub_3342C0_003342c0)
P3FES_DECL_PAIR(fn_sub_337E10_00337e10)
P3FES_DECL_PAIR(fn_sub_337F80_00337f80)
P3FES_DECL_PAIR(fn_sub_338CE0_00338ce0)
P3FES_DECL_PAIR(fn_sub_338E50_00338e50)
P3FES_DECL_PAIR(fn_sub_3394F0_003394f0)
P3FES_DECL_PAIR(fn_sub_339530_00339530)
P3FES_DECL_PAIR(fn_sub_3395A0_003395a0)
P3FES_DECL_PAIR(fn_sub_3395D0_003395d0)
P3FES_DECL_PAIR(fn_sub_339620_00339620)
P3FES_DECL_PAIR(fn_sub_339680_00339680)
P3FES_DECL_PAIR(fn_sub_3396D0_003396d0)
P3FES_DECL_PAIR(fn_sub_339760_00339760)
P3FES_DECL_PAIR(fn_sub_339770_00339770)
P3FES_DECL_PAIR(fn_sub_339780_00339780)
P3FES_DECL_PAIR(fn_sub_339790_00339790)
P3FES_DECL_PAIR(fn_sub_3397B0_003397b0)
P3FES_DECL_PAIR(fn_sub_339950_00339950)
P3FES_DECL_PAIR(fn_sub_341FD0_00341fd0)
P3FES_DECL_PAIR(fn_sub_3420C0_003420c0)
P3FES_DECL_PAIR(fn_sub_342130_00342130)
P3FES_DECL_PAIR(fn_sub_342280_00342280)
P3FES_DECL_PAIR(fn_sub_3422D0_003422d0)
P3FES_DECL_PAIR(fn_sub_342330_00342330)
P3FES_DECL_PAIR(fn_sub_342380_00342380)
P3FES_DECL_PAIR(fn_sub_342410_00342410)
P3FES_DECL_PAIR(fn_sub_342420_00342420)
P3FES_DECL_PAIR(fn_sub_342430_00342430)
P3FES_DECL_PAIR(fn_sub_342440_00342440)
P3FES_DECL_PAIR(fn_sub_342460_00342460)
P3FES_DECL_PAIR(fn_sub_342A40_00342a40)
P3FES_DECL_PAIR(fn_sub_345DB0_00345db0)
P3FES_DECL_PAIR(fn_sub_345EA0_00345ea0)
P3FES_DECL_PAIR(fn_sub_345F00_00345f00)
P3FES_DECL_PAIR(fn_sub_345FA0_00345fa0)
P3FES_DECL_PAIR(fn_sub_345FF0_00345ff0)
P3FES_DECL_PAIR(fn_sub_346050_00346050)
P3FES_DECL_PAIR(fn_sub_3460A0_003460a0)
P3FES_DECL_PAIR(fn_sub_346130_00346130)
P3FES_DECL_PAIR(fn_sub_346140_00346140)
P3FES_DECL_PAIR(fn_sub_346150_00346150)
P3FES_DECL_PAIR(fn_sub_346160_00346160)
P3FES_DECL_PAIR(fn_sub_346180_00346180)
P3FES_DECL_PAIR(fn_sub_346500_00346500)
P3FES_DECL_PAIR(fn_sub_346510_00346510)
P3FES_DECL_PAIR(fn_sub_347130_00347130)
P3FES_DECL_PAIR(fn_sub_347140_00347140)
P3FES_DECL_PAIR(fn_sub_347150_00347150)
P3FES_DECL_PAIR(fn_sub_347160_00347160)
P3FES_DECL_PAIR(fn_sub_347300_00347300)
P3FES_DECL_PAIR(fn_sub_347380_00347380)
P3FES_DECL_PAIR(fn_sub_347390_00347390)
P3FES_DECL_PAIR(fn_sub_347CE0_00347ce0)
P3FES_DECL_PAIR(fn_sub_347CF0_00347cf0)
P3FES_DECL_PAIR(fn_sub_347D00_00347d00)
P3FES_DECL_PAIR(fn_sub_347D60_00347d60)
P3FES_DECL_PAIR(fn_sub_347F80_00347f80)
P3FES_DECL_PAIR(fn_sub_348100_00348100)
P3FES_DECL_PAIR(fn_sub_348110_00348110)
P3FES_DECL_PAIR(fn_sub_3482B0_003482b0)
P3FES_DECL_PAIR(fn_sub_3482F0_003482f0)
P3FES_DECL_PAIR(fn_sub_348300_00348300)
P3FES_DECL_PAIR(fn_sub_34B510_0034b510)
P3FES_DECL_PAIR(fn_sub_34B520_0034b520)
P3FES_DECL_PAIR(fn_sub_34B580_0034b580)
P3FES_DECL_PAIR(fn_sub_34B5C0_0034b5c0)
P3FES_DECL_PAIR(fn_sub_34B680_0034b680)
P3FES_DECL_PAIR(fn_sub_34B690_0034b690)
P3FES_DECL_PAIR(fn_sub_34B6A0_0034b6a0)
P3FES_DECL_PAIR(fn_sub_34BA20_0034ba20)
P3FES_DECL_PAIR(fn_sub_34BA30_0034ba30)
P3FES_DECL_PAIR(fn_sub_34BA90_0034ba90)
P3FES_DECL_PAIR(fn_sub_34BAD0_0034bad0)
P3FES_DECL_PAIR(fn_sub_34BB90_0034bb90)
P3FES_DECL_PAIR(fn_sub_34BBA0_0034bba0)
P3FES_DECL_PAIR(fn_sub_34BBB0_0034bbb0)
P3FES_DECL_PAIR(fn_sub_34BCF0_0034bcf0)
P3FES_DECL_PAIR(fn_sub_34BD10_0034bd10)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01900000u;  // the random records of a case
constexpr u32 kWorldLen = 0x10000u;
constexpr u32 kTables = 0x0069BE00u;  // the class table and the kind rows (restored from the ELF before every case)
constexpr u32 kTablesLen = 0xF00u;
constexpr u32 kClassTable = 0x0069BE20u;
constexpr u32 kFilterRows = 0x0069CB98u;   // class 4's filter kinds (sub_34B520 / sub_34B580)
constexpr u32 kFilter2Rows = 0x0069CC58u;  // class 5's (sub_34BA30 / sub_34BA90)

// Callbacks of the emitted set (tests/game/CMakeLists.txt lists them).
constexpr u32 kRet0 = 0x3C4400u;      // `v0 = 0`
constexpr u32 kIdentity = 0x489950u;  // `v0 = a0`
constexpr u32 kSecond = 0x4B3710u;    // `v0 = a1`
constexpr u32 kOne = 0x469A90u;       // `v0 = 1`
constexpr u32 kNonLeaf = 0x1F1C50u;   // spills $ra below its $sp, returns the word at gp-18968

// --- guest RAM helpers -----------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
float rf(const Machine& m, u32 va) { return std::bit_cast<float>(r32(m, va)); }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();
    return (hi << 32) | rng();
}
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 8) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 2001) - 1000) / 997.0f);
    }
}
u32 fbits(float f) { return std::bit_cast<u32>(f); }

// --- the pair: trampolines that randomise the FPU / HI / LO / VU0 and catch a fatal event --------------------------------
struct RunExtra {
    bool fatal = false;
    u32 pc = 0;
    std::string what;
    std::array<u32, 32> fpr{};
    u32 acc = 0, fcr31 = 0;
    VU0State vu0{};
};
Fn g_fn[2] = {};
RunExtra g_extra[2];
u32 g_seed = 0;
std::map<unsigned, u32> g_fpr_in;
int g_pairs = 0;
std::map<std::string, std::pair<int, int>> g_tally;  // label -> (pairs, pairs stopped by a fatal event)
std::map<std::string, std::map<std::string, int>> g_fatal_kinds;  // label -> fatal event text (callee / fault) -> count

template <int K>
void trampoline(EEContext& c) {
    std::mt19937 r{g_seed ^ 0x5BD1E995u};
    for (u32& f : c.fpr) f = rand_float(r);
    for (const auto& [i, v] : g_fpr_in) c.fpr[i] = v;
    c.acc = rand_float(r);
    c.fcr31 = r() & 0x0083F078u;
    c.hi.u64[0] = rng64(r);
    c.hi.u64[1] = rng64(r);
    c.lo.u64[0] = rng64(r);
    c.lo.u64[1] = rng64(r);
    for (unsigned v = 1; v < 32; ++v)
        for (u32& x : c.vu0.vf[v]) x = rand_float(r);
    for (u32& x : c.vu0.acc) x = rand_float(r);
    c.vu0.q = rand_float(r);
    c.vu0.status = r() & 0xFFFu;
    c.vu0.mac = r() & 0xFFFFu;
    RunExtra& x = g_extra[K];
    x = RunExtra{};
    try {
        g_fn[K](c);
    } catch (const rt_test::FatalEvent& e) {
        x.fatal = true;
        x.pc = e.pc;
        x.what = e.what;
        // a memory fault names the host return address inside the body that faulted: the only part that may differ
        const std::size_t host = x.what.find("; host return address");
        if (host != std::string::npos) x.what.resize(host);
    }
    std::copy(std::begin(c.fpr), std::end(c.fpr), x.fpr.begin());
    x.acc = c.acc;
    x.fcr31 = c.fcr31;
    x.vu0 = c.vu0;
}

bool same_vu0(const VU0State& a, const VU0State& b) {
    return std::memcmp(a.vf, b.vf, sizeof a.vf) == 0 && std::memcmp(a.vi, b.vi, sizeof a.vi) == 0 &&
           std::memcmp(a.acc, b.acc, sizeof a.acc) == 0 && a.q == b.q && a.p == b.p && a.i == b.i && a.r == b.r &&
           a.status == b.status && a.mac == b.mac && a.clip == b.clip;
}

struct Result {
    u64 v0 = 0;
    bool fatal = false;
    std::string what;
    std::array<u32, 32> fpr{};
};

// Runs hand and recomp from the same machine (RAM restored in between) and requires identical results everywhere.
// After the pair the recompiled run's output is in place.
Result pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::map<unsigned, u64> gpr_in = {},
            std::map<unsigned, u32> fpr_in = {}) {
    g_fn[0] = hand;
    g_fn[1] = recomp;
    g_seed = seed;
    g_fpr_in = std::move(fpr_in);
    HwCheck hw;
    hw.ranges = {{0, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in = std::move(gpr_in);
    const HwPair p = run_pair_hw(m, &trampoline<0>, &trampoline<1>, args, seed, what, hw);
    INFO(what);
    const RunExtra& a = g_extra[0];
    const RunExtra& b = g_extra[1];
    CHECK(a.fatal == b.fatal);
    CHECK(a.pc == b.pc);
    CHECK(a.what == b.what);
    CHECK(a.fpr == b.fpr);
    CHECK(a.acc == b.acc);
    CHECK(a.fcr31 == b.fcr31);
    CHECK(same_vu0(a.vu0, b.vu0));
    ++g_pairs;
    auto& t = g_tally[what];
    ++t.first;
    if (b.fatal) {
        ++t.second;
        ++g_fatal_kinds[what][b.what.substr(0, 90)];
    }
    return Result{p.recomp.base.v0, b.fatal, b.what, b.fpr};
}

// The argument registers of a call; the ones a function does not take hold garbage, as at a real call site.
constexpr u64 kUnused = 0x5EED5EED5EED5EEDull;
std::mt19937_64 g_garbage{0x69BE20u};
Args args4(u64 a0 = kUnused, u64 a1 = kUnused, u64 a2 = kUnused, u64 a3 = kUnused) {
    Args a{a0, a1, a2, a3};
    for (u64& x : a)
        if (x == kUnused) x = g_garbage();
    return a;
}
// args4 with arguments that draw from the world's generator: a braced list is evaluated left to right, a call's
// arguments in an unspecified order (MSVC and clang-cl differ), so both compilers build the same worlds.
struct InOrder {
    u64 a0 = kUnused, a1 = kUnused, a2 = kUnused, a3 = kUnused;
    operator Args() const { return args4(a0, a1, a2, a3); }
};

// --- the world -------------------------------------------------------------------------------------------------------
std::vector<u8> g_tables;  // the ELF's class table and kind rows

struct World {
    Machine& m;
    std::mt19937& rng;
    u32 next = kWorld + 0x8000u;  // records go in the upper half; the lower half is the soup they point into

    World(Machine& mm, std::mt19937& r) : m(mm), rng(r) {
        if (g_tables.empty()) g_tables = m.bytes(kTables, kTablesLen);
        std::memcpy(m.at(kTables), g_tables.data(), kTablesLen);
        for (u32 a = kWorld; a < kWorld + kWorldLen; a += 4) w32(m, a, soup_word());
        // the callbacks' globals: the word the non-leaf returns
        w32(m, kGp - 18968u, ptr());
        std::memset(m.at(0), 0, 0x200);  // the retail null-pointer paths read and write here
    }
    u32 ptr() { return kWorld + ((rng() % (kWorldLen / 16)) * 16); }
    u32 soup_word() {
        switch (rng() % 10) {
        case 0: case 1: case 2: case 3: return ptr();
        case 4: case 5: return rng() % 16;
        case 6: case 7: return rand_float(rng);
        case 8: return 0;
        default: return rng();
        }
    }
    u32 alloc(u32 n) {
        const u32 a = next;
        next += (n + 15u) & ~15u;
        REQUIRE(next <= kWorld + kWorldLen);
        return a;
    }
    u32 cb() { return pick(rng, {kRet0, kRet0, kIdentity, kSecond, kOne, kNonLeaf}); }
    // a pointer argument: mostly a soup pointer, sometimes null
    u32 arg_ptr() { return chance(rng, 95) ? ptr() : 0; }
    // an effect record: +4 the u16 class (one of the 0x69BE20 rows), +8 the instance; with some slots of its class row
    // re-aimed at callbacks
    u32 effect() {
        const u32 e = alloc(64);
        const u32 cls = chance(rng, 90) ? rng() % 27 : rng() % 0x10000;
        w16(m, e + 4, static_cast<u16>(cls));
        w32(m, e + 8, chance(rng, 95) ? ptr() : 0);
        if (cls < 27)
            for (u32 s = 0; s < 13; ++s)
                if (chance(rng, 50)) w32(m, kClassTable + 52 * cls + 4 * s, chance(rng, 15) ? 0 : cb());
        return e;
    }
    // a filter instance of class 4 / 5: +24 the kind (rows of six words at `rows`), +28 the frame counter, +36 the owner
    u32 filter(u32 rows) {
        const u32 f = alloc(48);
        const u32 kind = chance(rng, 90) ? rng() % 6 : rng() % 64;
        w32(m, f + 24, kind);
        w32(m, f + 28, pick(rng, {0, 0, 1, 2, 0xFFFFFFFFu, 0x7FFFFFFFu, 0x80000000u}));
        w32(m, f + 36, ptr());
        if (kind < 6)
            for (u32 s = 0; s < 6; ++s)
                if (chance(rng, 60)) w32(m, rows + 24 * kind + 4 * s, cb());
        return f;
    }
};

// =====================================================================================================================
// [base]
// =====================================================================================================================

TEST_CASE("game(fx_types): the shared defaults, the block getters and the class-slot dispatchers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 1600; ++i) {
        const u32 seed = seed_of(i, 0x11u);
        std::mt19937 rng{seed};
        World w(m, rng);
        const u32 e = w.effect();
        const u32 rec = w.alloc(48);
        // the block getters: +24 / +40 the allocations, +16 / +32 the pointer or offset
        w32(m, rec + 24, chance(rng, 50) ? 0 : w.ptr());
        w32(m, rec + 40, chance(rng, 50) ? 0 : w.ptr());
        w32(m, rec + 16, chance(rng, 30) ? 0 : chance(rng, 50) ? rng() % 0x400 : w.ptr());
        w32(m, rec + 32, chance(rng, 30) ? 0 : chance(rng, 50) ? rng() % 0x400 : w.ptr());
        switch (i % 16) {
        case 0: pair(m, PAIR(fn_sub_324630_00324630), args4(), seed, "sub_324630 nop"); break;
        case 1: pair(m, PAIR(fn_sub_324640_00324640), args4(), seed, "sub_324640 nop"); break;
        case 2: pair(m, PAIR(fn_sub_324650_00324650), args4(), seed, "sub_324650 zero"); break;
        case 3: pair(m, PAIR(fn_sub_324660_00324660), args4(), seed, "sub_324660 nop"); break;
        case 4: pair(m, PAIR(fn_sub_324670_00324670), args4(), seed, "sub_324670 nop"); break;
        case 5: pair(m, PAIR(fn_sub_3245B0_003245b0), args4(sx(rec)), seed, "sub_3245B0 block A"); break;
        case 6: pair(m, PAIR(fn_sub_3245F0_003245f0), args4(sx(rec)), seed, "sub_3245F0 block B"); break;
        case 7: pair(m, PAIR(fn_sub_324930_00324930), args4(sx(e)), seed, "sub_324930 slot 7"); break;
        case 8: pair(m, PAIR(fn_sub_324990_00324990), args4(sx(e)), seed, "sub_324990 slot 2"); break;
        case 9: pair(m, PAIR(fn_sub_3249E0_003249e0), args4(sx(e)), seed, "sub_3249E0 slot 3"); break;
        case 10: pair(m, PAIR(fn_sub_324A30_00324a30), args4(sx(e)), seed, "sub_324A30 slot 8"); break;
        case 11: pair(m, PAIR(fn_sub_324A90_00324a90), args4(sx(e)), seed, "sub_324A90 slot 10"); break;
        case 12: pair(m, PAIR(fn_sub_324AF0_00324af0), args4(sx(e)), seed, "sub_324AF0 slot 12"); break;
        case 13: pair(m, PAIR(fn_sub_3243D0_003243d0), InOrder{sx(w.ptr()), sx(w.ptr()), rng64(rng), rng64(rng)}, seed, "sub_3243D0 layer"); break;
        case 14: case 15: {
            const u32 eff = w.alloc(32);
            w32(m, eff + 12, w.ptr());
            pair(m, PAIR(fn_sub_3244C0_003244c0), args4(sx(eff)), seed, "sub_3244C0 matrix");
            break;
        }
        }
    }
}

TEST_CASE("game(fx_types): documented rules of the base handlers") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{7};
    World w(m, rng);
    const u32 rec = w.alloc(48);
    // the block getters: absolute with an allocation, record-relative without, 0 stays 0
    w32(m, rec + 24, 0x1234);
    w32(m, rec + 16, 0x01901230u);
    CHECK(pair(m, PAIR(fn_sub_3245B0_003245b0), args4(sx(rec)), 1, "block A absolute").v0 == sx(0x01901230u));
    w32(m, rec + 24, 0);
    w32(m, rec + 16, 0x40);
    CHECK(pair(m, PAIR(fn_sub_3245B0_003245b0), args4(sx(rec)), 2, "block A relative").v0 == sx(rec + 0x40));
    w32(m, rec + 16, 0);
    CHECK(pair(m, PAIR(fn_sub_3245B0_003245b0), args4(sx(rec)), 3, "block A none").v0 == 0);
    w32(m, rec + 40, 0);
    w32(m, rec + 32, 0x80);
    CHECK(pair(m, PAIR(fn_sub_3245F0_003245f0), args4(sx(rec)), 4, "block B relative").v0 == sx(rec + 0x80));
    // sub_324650 returns 0; the class-slot dispatcher calls the class row's slot with the instance: aim slot 2 of
    // class 3 at the identity callback, which returns the instance
    CHECK(pair(m, PAIR(fn_sub_324650_00324650), args4(), 5, "default zero").v0 == 0);
    const u32 e = w.alloc(16);
    w16(m, e + 4, 3);
    w32(m, e + 8, 0x01904560u);
    w32(m, kClassTable + 52 * 3 + 8, kIdentity);
    CHECK(pair(m, PAIR(fn_sub_324990_00324990), args4(sx(e)), 6, "slot 2 identity").v0 == sx(0x01904560u));
}

// =====================================================================================================================
// [part] [shake] [filters]
// =====================================================================================================================

TEST_CASE("game(fx_types): the part helpers, the screen shake and the screen filters equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 1800; ++i) {
        const u32 seed = seed_of(i, 0x22u);
        std::mt19937 rng{seed};
        World w(m, rng);
        // the shake state (gp-relative) and its inputs
        w8(m, kGp - 18340u, static_cast<u8>(chance(rng, 70) ? 1 : 0));
        for (u32 off : {18332u, 18328u, 18312u, 18308u, 25248u, 25244u, 32108u, 25256u})
            w32(m, kGp - off, chance(rng, 15) ? 0 : rand_float(rng));
        w32(m, kGp - 18320u, w.ptr());
        w32(m, kGp - 19504u, w.ptr());  // sub_198590's scene record
        switch (i % 18) {
        case 0: pair(m, PAIR(fn_sub_324B50_00324b50), args4(sx(w.alloc(144))), seed, "sub_324B50 part reset"); break;
        case 1: pair(m, PAIR(fn_sub_326190_00326190), InOrder{sx(w.alloc(144)), sx(w.ptr() & ~0xFFFu)}, seed, "sub_326190 part copy"); break;
        case 2: pair(m, PAIR(fn_sub_347D00_00347d00), args4(), seed, "sub_347D00 shake init"); break;
        case 3: case 4: pair(m, PAIR(fn_sub_347D60_00347d60), args4(), seed, "sub_347D60 shake update"); break;
        case 5: pair(m, PAIR(fn_sub_347F80_00347f80), args4(), seed, "sub_347F80 shake stop"); break;
        case 6: pair(m, PAIR(fn_sub_34BD10_0034bd10), args4(), seed, "sub_34BD10 screen size"); break;
        case 7: pair(m, PAIR(fn_sub_34B520_0034b520), args4(sx(w.filter(kFilterRows))), seed, "sub_34B520 filter update"); break;
        case 8: pair(m, PAIR(fn_sub_34B580_0034b580), args4(sx(w.filter(kFilterRows))), seed, "sub_34B580 filter draw"); break;
        case 9: pair(m, PAIR(fn_sub_34B5C0_0034b5c0), args4(sx(w.filter(kFilterRows))), seed, "sub_34B5C0 filter notify"); break;
        case 10: pair(m, PAIR(fn_sub_34BA30_0034ba30), args4(sx(w.filter(kFilter2Rows))), seed, "sub_34BA30 filter2 update"); break;
        case 11: pair(m, PAIR(fn_sub_34BA90_0034ba90), args4(sx(w.filter(kFilter2Rows))), seed, "sub_34BA90 filter2 draw"); break;
        case 12: pair(m, PAIR(fn_sub_34BAD0_0034bad0), args4(sx(w.filter(kFilter2Rows))), seed, "sub_34BAD0 filter2 notify"); break;
        case 13:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_34B680_0034b680), InOrder{sx(w.ptr()), sx(w.ptr())}, seed, "sub_34B680 set quad");
            else pair(m, PAIR(fn_sub_34BB90_0034bb90), InOrder{sx(w.ptr()), sx(w.ptr())}, seed, "sub_34BB90 set quad");
            break;
        case 14:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_34B690_0034b690), InOrder{sx(w.ptr()), rng64(rng)}, seed, "sub_34B690 set word");
            else pair(m, PAIR(fn_sub_34BBA0_0034bba0), InOrder{sx(w.ptr()), rng64(rng)}, seed, "sub_34BBA0 set word");
            break;
        case 15:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_34B6A0_0034b6a0), args4(sx(w.ptr())), seed, "sub_34B6A0 set float");
            else pair(m, PAIR(fn_sub_34BBB0_0034bbb0), args4(sx(w.ptr())), seed, "sub_34BBB0 set float");
            break;
        case 16: pair(m, PAIR(fn_sub_34B680_0034b680), InOrder{sx(w.ptr() + 4), sx(w.ptr())}, seed, "sub_34B680 unaligned"); break;
        case 17: pair(m, PAIR(fn_sub_347D60_00347d60), args4(), seed, "sub_347D60 shake update (idle)"); break;
        }
    }
}

TEST_CASE("game(fx_types): documented rules of the shake and the filters") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{9};
    World w(m, rng);
    // sub_34B520: the kind's update runs, then the frame counter (+28) counts up
    const u32 f = w.alloc(48);
    w32(m, f + 24, 2);
    w32(m, f + 28, 41);
    w32(m, kFilterRows + 48, kRet0);
    pair(m, PAIR(fn_sub_34B520_0034b520), args4(sx(f)), 1, "filter frame count");
    CHECK(r32(m, f + 28) == 42);
    // sub_34B6A0: +20 = $f12
    pair(m, PAIR(fn_sub_34B6A0_0034b6a0), args4(sx(f)), 2, "filter float", {}, {{12, fbits(2.5f)}});
    CHECK(rf(m, f + 20) == 2.5f);
    // sub_347F80 clears the active byte
    w8(m, kGp - 18340u, 1);
    const u32 cam = w.alloc(176);
    const u32 dirty = w.alloc(16);
    w32(m, cam + 160, dirty);
    w8(m, dirty + 3, 3);  // already on the dirty list: sub_4CB750 only marks it
    w32(m, kGp - 18320u, cam);
    CHECK_FALSE(pair(m, PAIR(fn_sub_347F80_00347f80), args4(), 3, "shake stop").fatal);
    CHECK(*m.at(kGp - 18340u) == 0);
    // sub_347D60 with the active byte clear does nothing but its frame
    w8(m, kGp - 18340u, 0);
    w32(m, kGp - 18312u, fbits(1.0f));
    pair(m, PAIR(fn_sub_347D60_00347d60), args4(), 4, "shake idle");
    CHECK(rf(m, kGp - 18312u) == 1.0f);
}

// =====================================================================================================================
// [part list] [track] [mask]
// =====================================================================================================================

constexpr u32 kTrackRows = 0x0069C510u;  // the track types: four words per type (update, time setter, two sizes)

// a track: +0 u16 type, +8 a word, +16 the frame, +24 the key slots, +32 the value block
u32 make_track(World& w) {
    Machine& m = w.m;
    std::mt19937& rng = w.rng;
    const u32 t = w.alloc(48);
    const u32 type = chance(rng, 90) ? 1 + rng() % 11 : rng() % 0x10000;
    w16(m, t + 0, static_cast<u16>(type));
    w32(m, t + 8, chance(rng, 95) ? rng() % 5 : rng() % 0x100);  // the key count (the slots hold 4)
    w32(m, t + 16, chance(rng, 50) ? 0 : rng() % 100);
    w32(m, t + 24, chance(rng, 95) ? w.alloc(128) : w.ptr());
    w32(m, t + 32, w.ptr());
    if (type < 12)
        for (u32 s = 0; s < 2; ++s)
            if (chance(rng, 70)) w32(m, kTrackRows + 16 * type + 4 * s, w.cb());
    return t;
}

// a part list of n parts (+140 head, +172 next, +144 id)
u32 make_part_list(World& w, std::vector<u32>& parts) {
    Machine& m = w.m;
    std::mt19937& rng = w.rng;
    const u32 owner = w.alloc(176);
    const unsigned n = rng() % 6;
    parts.clear();
    for (unsigned k = 0; k < n; ++k) {
        const u32 p = w.alloc(176);
        w32(m, p + 144, chance(rng, 80) ? rng() % 6 : rng());
        parts.push_back(p);
    }
    for (unsigned k = 0; k < n; ++k) w32(m, parts[k] + 172, k + 1 < n ? parts[k + 1] : 0);
    w32(m, owner + 140, n ? parts[0] : 0);
    return owner;
}

TEST_CASE("game(fx_types): the part list, the animation track and the mask helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 2600; ++i) {
        const u32 seed = seed_of(i, 0x33u);
        std::mt19937 rng{seed};
        World w(m, rng);
        std::vector<u32> parts;
        const u32 owner = make_part_list(w, parts);
        const u32 track = make_track(w);
        const u32 obj = w.alloc(96);
        w32(m, obj + 76, chance(rng, 85) ? track : 0);
        w32(m, obj + 48, chance(rng, 85) ? track : 0);
        w32(m, obj + 44, chance(rng, 70) ? w.alloc(16) : 0);
        w32(m, obj + 24, w.ptr());
        const u64 small = chance(rng, 85) ? rng() % 8 : rng64(rng);
        switch (i % 26) {
        case 0: pair(m, PAIR(fn_sub_326160_00326160), InOrder{sx(w.ptr()), sx(w.ptr())}, seed, "sub_326160 quad 64"); break;
        case 1: pair(m, PAIR(fn_sub_326170_00326170), InOrder{sx(w.ptr()), sx(w.ptr())}, seed, "sub_326170 quad 80"); break;
        case 2: pair(m, PAIR(fn_sub_326180_00326180), args4(sx(w.ptr())), seed, "sub_326180 word 100"); break;
        case 3: pair(m, PAIR(fn_sub_3261C0_003261c0), args4(sx(owner), small), seed, "sub_3261C0 find id"); break;
        case 4: pair(m, PAIR(fn_sub_326200_00326200), args4(sx(owner), small), seed, "sub_326200 part at"); break;
        case 5: {
            const u64 p = parts.empty() || chance(rng, 20) ? sx(w.ptr()) : sx(parts[rng() % parts.size()]);
            pair(m, PAIR(fn_sub_326240_00326240), args4(sx(owner), p), seed, "sub_326240 index of");
            break;
        }
        case 6: pair(m, PAIR(fn_sub_332200_00332200), args4(sx(track)), seed, "sub_332200 restart"); break;
        case 7: case 8: pair(m, PAIR(fn_sub_332210_00332210), args4(sx(track)), seed, "sub_332210 track update"); break;
        case 9: pair(m, PAIR(fn_sub_3322B0_003322b0), args4(sx(track), sx(w.ptr())), seed, "sub_3322B0 get value"); break;
        case 10: pair(m, PAIR(fn_sub_3322D0_003322d0), args4(sx(track), sx(w.ptr())), seed, "sub_3322D0 set value"); break;
        case 11: pair(m, PAIR(fn_sub_3322F0_003322f0), args4(sx(track), sx(w.ptr())), seed, "sub_3322F0 get value 2"); break;
        case 12: pair(m, PAIR(fn_sub_332310_00332310), args4(sx(track), sx(w.ptr())), seed, "sub_332310 set value 2"); break;
        case 13: pair(m, PAIR(fn_sub_332330_00332330), args4(sx(track)), seed, "sub_332330 set time"); break;
        case 14:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_327220_00327220), args4(sx(obj)), seed, "sub_327220 obj restart");
            else pair(m, PAIR(fn_sub_332B30_00332b30), args4(sx(obj)), seed, "sub_332B30 obj restart");
            break;
        case 15:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_329430_00329430), args4(sx(obj), sx(w.ptr())), seed, "sub_329430 obj set value");
            else pair(m, PAIR(fn_sub_333020_00333020), args4(sx(obj), sx(w.ptr())), seed, "sub_333020 obj set value");
            break;
        case 16:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_329460_00329460), args4(sx(obj), sx(w.ptr())), seed, "sub_329460 obj set value 2");
            else pair(m, PAIR(fn_sub_333050_00333050), args4(sx(obj), sx(w.ptr())), seed, "sub_333050 obj set value 2");
            break;
        case 17:
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_3294A0_003294a0), args4(sx(obj)), seed, "sub_3294A0 obj set time");
            else pair(m, PAIR(fn_sub_3330B0_003330b0), args4(sx(obj)), seed, "sub_3330B0 obj set time");
            break;
        case 18: pair(m, PAIR(fn_sub_329490_00329490), args4(sx(obj), rng64(rng)), seed, "sub_329490 set word"); break;
        case 19: pair(m, PAIR(fn_sub_333080_00333080), args4(sx(obj), rng64(rng)), seed, "sub_333080 set word child"); break;
        case 20: pair(m, PAIR(fn_sub_329350_00329350), args4(sx(obj)), seed, "sub_329350 obj1 update"); break;
        case 21: pair(m, PAIR(fn_sub_3293A0_003293a0), args4(sx(obj)), seed, "sub_3293A0 obj1 draw"); break;
        case 22: pair(m, PAIR(fn_sub_3293D0_003293d0), args4(sx(obj)), seed, "sub_3293D0 obj1 update draw"); break;
        case 23: pair(m, PAIR(fn_sub_333900_00333900), args4(sx(obj), small), seed, "sub_333900 mask clear"); break;
        case 24: pair(m, PAIR(fn_sub_333920_00333920), args4(sx(obj), small), seed, "sub_333920 mask set"); break;
        case 25: pair(m, PAIR(fn_sub_333940_00333940), args4(sx(obj), small), seed, "sub_333940 mask test"); break;
        }
    }
}

TEST_CASE("game(fx_types): documented rules of the part list and the track") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11};
    World w(m, rng);
    std::vector<u32> parts;
    u32 owner = 0;
    do owner = make_part_list(w, parts);
    while (parts.size() < 3 && (w.next = kWorld + 0x8000u));
    for (std::size_t k = 0; k < parts.size(); ++k) w32(m, parts[k] + 144, 100 + static_cast<u32>(k));
    CHECK(pair(m, PAIR(fn_sub_3261C0_003261c0), args4(sx(owner), 101), 1, "find id rule").v0 == sx(parts[1]));
    CHECK(pair(m, PAIR(fn_sub_3261C0_003261c0), args4(sx(owner), 99), 2, "find id miss").v0 == 0);
    CHECK(pair(m, PAIR(fn_sub_326200_00326200), args4(sx(owner), 2), 3, "part at rule").v0 == sx(parts[2]));
    CHECK(pair(m, PAIR(fn_sub_326240_00326240), args4(sx(owner), sx(parts[2])), 4, "index of rule").v0 == 2);
    // the track update clears the key slots on frame 0 and counts the frame
    const u32 t = make_track(w);
    w16(m, t, 1);
    w32(m, kTrackRows + 16, kRet0);
    w32(m, t + 16, 0);
    w32(m, t + 8, 3);
    const u32 keys = r32(m, t + 24);
    pair(m, PAIR(fn_sub_332210_00332210), args4(sx(t)), 5, "track frame 0");
    CHECK(r32(m, t + 16) == 1);
    for (u32 k = 0; k < r32(m, t + 8); ++k) CHECK(r32(m, keys + 32 * k + 16) == 0xFFFFFFFFu);
    // the mask: set, test, clear, test
    const u32 obj = w.alloc(32);
    const u32 mask = w.alloc(16);
    w32(m, obj + 24, mask);
    pair(m, PAIR(fn_sub_333920_00333920), args4(sx(obj), 3), 6, "mask set");
    CHECK(pair(m, PAIR(fn_sub_333940_00333940), args4(sx(obj), 3), 7, "mask is set").v0 == 1);
    pair(m, PAIR(fn_sub_333900_00333900), args4(sx(obj), 0x10003), 8, "mask clear (u16 index)");
    CHECK(pair(m, PAIR(fn_sub_333940_00333940), args4(sx(obj), 3), 9, "mask is clear").v0 == 0);
}

// =====================================================================================================================
// [kind objects] [misc]
// =====================================================================================================================

constexpr u32 kMallocSlot = 0x960178u;  // RwEngineInstance memory functions: malloc (the creators kept recompiled use it)

// The kind-object classes: kind / counter / parameter offsets, the rows, their stride and the number of kinds.
struct KClass {
    u32 kind_off, count_off, params_off, rows, stride, kinds;
};
constexpr KClass kK12{56, 52, 64, 0x69C650u, 24, 4};
constexpr KClass kK10{56, 52, 64, 0x69C850u, 28, 10};
constexpr KClass kK16{56, 52, 64, 0x69C970u, 28, 4};

u32 make_kobj(World& w, const KClass& k) {
    Machine& m = w.m;
    std::mt19937& rng = w.rng;
    const u32 o = w.alloc(96);
    const u32 kind = chance(rng, 92) ? 1 + rng() % (k.kinds - 1) : rng() % 64;
    w32(m, o + k.kind_off, kind);
    w32(m, o + k.count_off, pick(rng, {0, 0, 1, 2, 5, 0xFFFFFFFFu, 0x80000000u, 0x7FFFFFFFu}));
    w32(m, o + k.params_off, w.ptr());
    if (kind < k.kinds)
        for (u32 s = 0; s < 6; ++s)  // (the size words -- stride 24: the sixth, stride 28: the seventh -- are left alone)
            if ((k.stride == 28 || s < 5) && chance(rng, 70)) w32(m, k.rows + k.stride * kind + 4 * s, w.cb());
    return o;
}

TEST_CASE("game(fx_types): the kind-object classes and the small class handlers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 4200; ++i) {
        const u32 seed = seed_of(i, 0x44u);
        std::mt19937 rng{seed};
        World w(m, rng);
        w32(m, kMallocSlot, kNonLeaf);  // the creators' RwMalloc: the non-leaf returns the block at gp-18968
        w32(m, kGp - 18968u, w.alloc(0x400));
        w32(m, kMallocSlot + 4, chance(rng, 70) ? kRet0 : kNonLeaf);  // RwFree
        const KClass& k = *std::array<const KClass*, 3>{&kK12, &kK10, &kK16}[rng() % 3];
        const u32 o = make_kobj(w, k);
        // an effect record for the creates: u16 +12 the kind, u16 +28 the effect type, the two data blocks
        const u32 e = w.alloc(48);
        w16(m, e + 12, static_cast<u16>(chance(rng, 90) ? 1 + rng() % 3 : rng()));
        w16(m, e + 28, static_cast<u16>(pick(rng, {1, 4, 0, 2, 4, 1})));
        w32(m, e + 24, chance(rng, 50) ? 0 : w.ptr());
        w32(m, e + 40, chance(rng, 50) ? 0 : w.ptr());
        // (the pointer is drawn before the relative choice: the operands of `-` have no fixed order)
        const auto block_word = [&]() -> u32 {
            if (chance(rng, 20)) return 0;
            const u32 ptr = w.ptr();
            return ptr - (chance(rng, 50) ? e : 0);
        };
        w32(m, e + 16, block_word());
        w32(m, e + 32, block_word());
        for (const KClass* kc : {&kK12, &kK10, &kK16})
            for (u32 kd = 1; kd < 4; ++kd)
                for (u32 s = 0; s < (kc->stride == 28 ? 6u : 5u); ++s)  // (not the size words)
                    if (chance(rng, 30)) w32(m, kc->rows + kc->stride * kd + 4 * s, w.cb());
        const u32 src = w.ptr();
        // the tint bytes of sub_337E10 / sub_338CE0 and a material chain obj +60 -> +0 -> +20
        for (u32 b = 18345; b <= 18348; ++b) w8(m, kGp - b, static_cast<u8>(chance(rng, 30) ? 255 : rng()));
        const u32 tobj = w.alloc(64);
        const u32 mat0 = w.alloc(16);
        const u32 mat = w.alloc(32);
        w32(m, tobj + 60, mat0);
        w32(m, mat0 + 0, mat);
        w32(m, mat + 20, w.ptr());
        struct Row {
            const char* what;
            Fn hand, recomp;
            const KClass* cls;
            int args;  // 0: (obj), 1: (obj, src), 2: (obj, word), 3: (effect), 4: (obj) with $f12
        };
        static const Row rows[] = {
            {"sub_3394F0 k12 create", PAIR(fn_sub_3394F0_003394f0), &kK12, 3},
            {"sub_3395A0 k12 clone", PAIR(fn_sub_3395A0_003395a0), &kK12, 0},
            {"sub_3395D0 k12 init", PAIR(fn_sub_3395D0_003395d0), &kK12, 0},
            {"sub_339620 k12 update", PAIR(fn_sub_339620_00339620), &kK12, 0},
            {"sub_339680 k12 draw", PAIR(fn_sub_339680_00339680), &kK12, 0},
            {"sub_3396D0 k12 update draw", PAIR(fn_sub_3396D0_003396d0), &kK12, 0},
            {"sub_339760 k12 quad 0", PAIR(fn_sub_339760_00339760), &kK12, 1},
            {"sub_339770 k12 quad 16", PAIR(fn_sub_339770_00339770), &kK12, 1},
            {"sub_339780 k12 word 48", PAIR(fn_sub_339780_00339780), &kK12, 2},
            {"sub_339790 k12 scale", PAIR(fn_sub_339790_00339790), &kK12, 4},
            {"sub_3397B0 k12 scale3", PAIR(fn_sub_3397B0_003397b0), &kK12, 1},
            {"sub_341FD0 k10 create", PAIR(fn_sub_341FD0_00341fd0), &kK10, 3},
            {"sub_342130 k10 clone", PAIR(fn_sub_342130_00342130), &kK10, 0},
            {"sub_342280 k10 init", PAIR(fn_sub_342280_00342280), &kK10, 0},
            {"sub_3422D0 k10 update", PAIR(fn_sub_3422D0_003422d0), &kK10, 0},
            {"sub_342330 k10 draw", PAIR(fn_sub_342330_00342330), &kK10, 0},
            {"sub_342380 k10 update draw", PAIR(fn_sub_342380_00342380), &kK10, 0},
            {"sub_342410 k10 quad 0", PAIR(fn_sub_342410_00342410), &kK10, 1},
            {"sub_342420 k10 quad 16", PAIR(fn_sub_342420_00342420), &kK10, 1},
            {"sub_342430 k10 word 48", PAIR(fn_sub_342430_00342430), &kK10, 2},
            {"sub_342440 k10 scale", PAIR(fn_sub_342440_00342440), &kK10, 4},
            {"sub_342460 k10 scale3", PAIR(fn_sub_342460_00342460), &kK10, 1},
            {"sub_345DB0 k16 create", PAIR(fn_sub_345DB0_00345db0), &kK16, 3},
            {"sub_345F00 k16 clone", PAIR(fn_sub_345F00_00345f00), &kK16, 0},
            {"sub_345FA0 k16 init", PAIR(fn_sub_345FA0_00345fa0), &kK16, 0},
            {"sub_345FF0 k16 update", PAIR(fn_sub_345FF0_00345ff0), &kK16, 0},
            {"sub_346050 k16 draw", PAIR(fn_sub_346050_00346050), &kK16, 0},
            {"sub_3460A0 k16 update draw", PAIR(fn_sub_3460A0_003460a0), &kK16, 0},
            {"sub_346130 k16 quad 0", PAIR(fn_sub_346130_00346130), &kK16, 1},
            {"sub_346140 k16 quad 16", PAIR(fn_sub_346140_00346140), &kK16, 1},
            {"sub_346150 k16 word 48", PAIR(fn_sub_346150_00346150), &kK16, 2},
            {"sub_346160 k16 scale", PAIR(fn_sub_346160_00346160), &kK16, 4},
            {"sub_346180 k16 scale3", PAIR(fn_sub_346180_00346180), &kK16, 1},
            {"sub_346500 obj7 restart", PAIR(fn_sub_346500_00346500), nullptr, 0},
            {"sub_346510 obj7 count", PAIR(fn_sub_346510_00346510), nullptr, 0},
            {"sub_347130 obj7 quad 0", PAIR(fn_sub_347130_00347130), nullptr, 1},
            {"sub_347140 obj7 quad 16", PAIR(fn_sub_347140_00347140), nullptr, 1},
            {"sub_347150 obj7 word 36", PAIR(fn_sub_347150_00347150), nullptr, 2},
            {"sub_347160 obj7 float 32", PAIR(fn_sub_347160_00347160), nullptr, 4},
            {"sub_347380 obj9 restart", PAIR(fn_sub_347380_00347380), nullptr, 0},
            {"sub_347390 obj9 count", PAIR(fn_sub_347390_00347390), nullptr, 0},
            {"sub_347CE0 obj9 quad 0", PAIR(fn_sub_347CE0_00347ce0), nullptr, 1},
            {"sub_347CF0 obj9 word 20", PAIR(fn_sub_347CF0_00347cf0), nullptr, 2},
            {"sub_3342C0 obj2 attach both", PAIR(fn_sub_3342C0_003342c0), nullptr, 2},
            {"sub_337E10 tint", PAIR(fn_sub_337E10_00337e10), nullptr, 5},
            {"sub_338CE0 tint", PAIR(fn_sub_338CE0_00338ce0), nullptr, 5},
            {"sub_348100 obj21 restart", PAIR(fn_sub_348100_00348100), nullptr, 0},
            {"sub_3482B0 obj21 update", PAIR(fn_sub_3482B0_003482b0), nullptr, 0},
            {"sub_3482F0 obj21 nop", PAIR(fn_sub_3482F0_003482f0), nullptr, 0},
            {"sub_348300 obj21 update draw", PAIR(fn_sub_348300_00348300), nullptr, 0},
            {"sub_34B510 filter restart", PAIR(fn_sub_34B510_0034b510), nullptr, 0},
            {"sub_34BA20 filter2 restart", PAIR(fn_sub_34BA20_0034ba20), nullptr, 0},
            {"sub_34BCF0 ref inc", PAIR(fn_sub_34BCF0_0034bcf0), nullptr, 0},
            {"sub_339530 k12 destroy", PAIR(fn_sub_339530_00339530), &kK12, 0},
            {"sub_3420C0 k10 destroy", PAIR(fn_sub_3420C0_003420c0), &kK10, 0},
            {"sub_345EA0 k16 destroy", PAIR(fn_sub_345EA0_00345ea0), &kK16, 0},
            {"sub_3321D0 track free keys", PAIR(fn_sub_3321D0_003321d0), nullptr, 0},
            {"sub_3338B0 obj2 destroy", PAIR(fn_sub_3338B0_003338b0), nullptr, 0},
            {"sub_337F80 release free", PAIR(fn_sub_337F80_00337f80), nullptr, 0},
            {"sub_338E50 release free", PAIR(fn_sub_338E50_00338e50), nullptr, 0},
            {"sub_347300 obj9 destroy", PAIR(fn_sub_347300_00347300), nullptr, 0},
            {"sub_339950 kind release", PAIR(fn_sub_339950_00339950), nullptr, 0},
            {"sub_342A40 kind release atomic", PAIR(fn_sub_342A40_00342a40), nullptr, 0},
        };
        const Row& r = rows[static_cast<std::size_t>(i) % std::size(rows)];
        u32 obj = r.cls ? make_kobj(w, *r.cls) : (chance(rng, 50) ? o : w.ptr());
        if (r.args == 5) obj = tobj;
        switch (r.args) {
        case 0: case 4: case 5: pair(m, r.hand, r.recomp, args4(sx(obj)), seed, r.what); break;
        case 1: pair(m, r.hand, r.recomp, args4(sx(obj), sx(chance(rng, 95) ? src : src + 4)), seed, r.what); break;
        case 2: pair(m, r.hand, r.recomp, args4(sx(obj), rng64(rng)), seed, r.what); break;
        case 3: pair(m, r.hand, r.recomp, args4(sx(e)), seed, r.what); break;
        }
    }
}

TEST_CASE("game(fx_types): documented rules of the kind objects") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{13};
    World w(m, rng);
    // kobjUpdateDraw: the update runs, the counter counts, the draw runs once the counter is positive -- aim the update
    // at `v0 = 0` and the draw at `v0 = 1`: $v0 ends 1 only when the draw ran
    const u32 o = w.alloc(96);
    w32(m, o + 56, 1);
    w32(m, kK12.rows + 24 + 12, kRet0);
    w32(m, kK12.rows + 24 + 16, kOne);
    w32(m, o + 52, 0xFFFFFFFFu);
    CHECK(pair(m, PAIR(fn_sub_3396D0_003396d0), args4(sx(o)), 1, "update draw at -1").v0 == 0);
    CHECK(r32(m, o + 52) == 0);
    CHECK(pair(m, PAIR(fn_sub_3396D0_003396d0), args4(sx(o)), 2, "update draw at 0").v0 == 1);
    CHECK(r32(m, o + 52) == 1);
    // kobjInit resets the counter; the stride-28 rows of class 10 index 28 * kind
    w32(m, o + 52, 77);
    w32(m, kK10.rows + 28 * 2, kSecond);
    w32(m, o + 56, 2);
    pair(m, PAIR(fn_sub_342280_00342280), args4(sx(o)), 3, "k10 init");
    CHECK(r32(m, o + 52) == 0);
    // the tint: an alpha of 255 is copied as 254 and restored
    const u32 tobj = w.alloc(64), mat0 = w.alloc(16), mat = w.alloc(32), col = w.alloc(16);
    w32(m, tobj + 60, mat0);
    w32(m, mat0, mat);
    w32(m, mat + 20, col);
    w8(m, kGp - 18348u, 10);
    w8(m, kGp - 18347u, 20);
    w8(m, kGp - 18346u, 30);
    w8(m, kGp - 18345u, 255);
    pair(m, PAIR(fn_sub_337E10_00337e10), args4(sx(tobj)), 4, "tint opaque");
    CHECK(r32(m, col + 4) == (10u | 20u << 8 | 30u << 16 | 254u << 24));
    CHECK(*m.at(kGp - 18345u) == 255);
}

// =====================================================================================================================
// [math]
// =====================================================================================================================

TEST_CASE("game(fx_types): the keyframe curve, the shake trigger and the camera getters equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 2400; ++i) {
        const u32 seed = seed_of(i, 0x55u);
        std::mt19937 rng{seed};
        World w(m, rng);
        switch (i % 6) {
        case 0: case 1: case 2: {
            // a curve: mode, start / end, the middle values +20 / +28, the key fractions +24 / +32
            const u32 c = w.alloc(48);
            w8(m, c, static_cast<u8>(chance(rng, 90) ? rng() % 3 : rng()));
            for (u32 off : {4u, 8u, 20u, 28u}) w32(m, c + off, rand_float(rng));
            const float k1 = static_cast<float>(rng() % 101) / 100.0f;
            w32(m, c + 24, chance(rng, 90) ? fbits(k1) : rand_float(rng));
            w32(m, c + 32, chance(rng, 90) ? fbits(k1 + (1.0f - k1) * static_cast<float>(rng() % 101) / 100.0f) : rand_float(rng));
            const u32 dur = chance(rng, 10) ? 0 : chance(rng, 5) ? rng() : 1 + rng() % 120;
            const u32 frame = chance(rng, 85) ? rng() % (dur + 2) : rng();
            pair(m, PAIR(fn_sub_32A540_0032a540), args4(sx(c), sx(frame), sx(dur)), seed, "sub_32A540 curve");
            break;
        }
        case 3: case 4: {
            // a shake record: +0 the start frame, +4 u16 the strength, +8 / +12 the fade lengths
            const u32 r = w.alloc(16);
            w32(m, r + 0, chance(rng, 15) ? 0 : chance(rng, 5) ? rng() : rng() % 60);
            w16(m, r + 4, static_cast<u16>(rng()));
            w32(m, r + 8, chance(rng, 20) ? 0 : chance(rng, 5) ? 0x80000000u | rng() : rng() % 30);
            w32(m, r + 12, chance(rng, 20) ? 0 : chance(rng, 5) ? 0x80000000u | rng() : rng() % 30);
            pair(m, PAIR(fn_sub_348110_00348110), args4(sx(r), sx(chance(rng, 90) ? rng() % 70 : rng())), seed, "sub_348110 shake start");
            break;
        }
        case 5: {
            // the scene record (gp-19504) -> +4 the camera; sub_4CB2F0 returns its matrix
            w32(m, kGp - 19504u, w.ptr());
            if (chance(rng, 50)) pair(m, PAIR(fn_sub_329740_00329740), args4(sx(w.ptr())), seed, "sub_329740 camera pos");
            else pair(m, PAIR(fn_sub_3297A0_003297a0), args4(sx(w.ptr())), seed, "sub_3297A0 camera at");
            break;
        }
        }
    }
}

TEST_CASE("game(fx_types): documented rules of the curve and the shake trigger") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{17};
    World w(m, rng);
    const u32 c = w.alloc(48);
    w8(m, c, 0);
    w32(m, c + 4, fbits(10.0f));
    w32(m, c + 8, fbits(20.0f));
    // mode 0 at frame 5 of 10: halfway; a zero duration gives the start value
    CHECK(std::bit_cast<float>(pair(m, PAIR(fn_sub_32A540_0032a540), args4(sx(c), 5, 10), 1, "curve mode 0").fpr[0]) == 15.0f);
    CHECK(std::bit_cast<float>(pair(m, PAIR(fn_sub_32A540_0032a540), args4(sx(c), 5, 0), 2, "curve no duration").fpr[0]) == 10.0f);
    // mode 1: start -> +20 over the first key (+24 = 0.5 of 10 frames), then +20 -> end
    w8(m, c, 1);
    w32(m, c + 20, fbits(30.0f));
    w32(m, c + 24, fbits(0.5f));
    CHECK(std::bit_cast<float>(pair(m, PAIR(fn_sub_32A540_0032a540), args4(sx(c), 0, 10), 3, "curve mode 1 start").fpr[0]) == 10.0f);
    CHECK(std::bit_cast<float>(pair(m, PAIR(fn_sub_32A540_0032a540), args4(sx(c), 5, 10), 4, "curve mode 1 key").fpr[0]) == 30.0f);
    // the shake trigger: inside the hold the weight is 1, amplitude = 10 * strength, the other = 4 * that / 10
    const u32 r = w.alloc(16);
    w32(m, r + 0, 30);
    w16(m, r + 4, 2);
    w32(m, r + 8, 5);
    w32(m, r + 12, 5);
    w8(m, kGp - 18340u, 0);
    pair(m, PAIR(fn_sub_348110_00348110), args4(sx(r), 10), 5, "shake hold");
    CHECK(rf(m, kGp - 25256u) == 1.0f);
    CHECK(rf(m, kGp - 18328u) == 20.0f);
    CHECK(rf(m, kGp - 18332u) == 8.0f);
    CHECK(*m.at(kGp - 18340u) == 1);
}

// The replay snapshots: the whole RAM of a route, the handlers run on the live state.
std::vector<std::filesystem::path> snapshots() {
    std::vector<std::filesystem::path> v;
    const std::filesystem::path base = std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours";
    for (const char* s : {"battle_ref_6150", "b_5800", "dorm_replay_4900"}) {
        const auto p = base / s / "eeMemory.bin";
        if (std::filesystem::exists(p)) v.push_back(p);
    }
    return v;
}
bool load_snapshot(Machine& m, const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    in.read(reinterpret_cast<char*>(m.mem.main_ram()), EEMemory::kMainRamSize);
    return in.gcount() == static_cast<std::streamsize>(EEMemory::kMainRamSize);
}

TEST_CASE("game(fx_types): the handlers on the replay snapshots") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const auto snaps = snapshots();
    if (snaps.empty()) {
        MESSAGE("SKIP: no replay snapshot under extracted/_ours");
        return;
    }
    for (const auto& p : snaps) {
        REQUIRE(load_snapshot(m, p));
        INFO(p.string());
        // the shake state as the route left it, and once more with the shake active
        for (int k = 0; k < 4; ++k) {
            if (k == 2) w8(m, kGp - 18340u, 1);
            pair(m, PAIR(fn_sub_347D60_00347d60), args4(), 100 + k, "snapshot shake update");
        }
        pair(m, PAIR(fn_sub_34BD10_0034bd10), args4(), 110, "snapshot screen size");
    }
}

TEST_CASE("game(fx_types): pair-test tally") {
    for (const auto& [what, t] : g_tally) {
        std::string kinds;
        for (const auto& [k, n] : g_fatal_kinds[what]) kinds += "\n    " + std::to_string(n) + "x " + k;
        MESSAGE(what << ": " << t.first << " pairs, " << t.second << " stopped by a fatal event" << kinds);
    }
    MESSAGE("fx_types pairs: " << g_pairs);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
