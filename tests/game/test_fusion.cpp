// Phase 5 pair tests for the fusion slice (game/src/facility/fusion.cpp): the Velvet Room persona fusion code of the
// facilities band, 0x3D02E0-0x3DF49C. No replay route reaches the Velvet Room, so these pairs carry the slice: every
// hand-written function and the recompiled body it replaces run on identical guest machines built on the REAL game
// tables -- the ELF's .data (the arcana charts 0x6A56B9 / 0x6A58E9 / 0x6A5AD9, the special recipes 0x6A5F40, the
// availability rules 0x6A5410) and battle/PERSONA.TBL + SKILL.TBL from F:\P3FES-PORT\p3fes-port\extracted, laid out the
// way the battle table loader (sub_27DCD0, docs/ANALYSIS/21_battle.md Â§3.1) lays them out -- with random game state on
// top: the flag bit array, the hero's persona slots and level, the RpRandom state, stock lists, fusion results and the
// list-menu records. The base machine is the fusion route's Velvet Room snapshot (extracted/_ours/fusion_vr_5000: the
// route of the gate's `fusion` entry, config/inputs/fusion.txt with card fusion.ps2, run in reference mode to vblank
// 5000 -- the fusion menu open) when present, so every pair runs inside a real game's memory; two cases replay the
// route's own fusion (personas 1 + 46 -> 14, the result fusion_ref_6300 holds) and its fclCombine root. The heap,
// printf and file requests are the test stand-ins (stand_ins.h); not-emitted callees are recorders.
//
// Stricter than the Outcome (run_pair_hw): per pair this file compares EVERY general register in 128 bits, HI/LO, all
// FPU registers, ACC and FCR31 at the return, the whole register file and the cycle count at EVERY check point, the
// WHOLE 32 MiB of RAM (PairRange), the dead stack (the hand versions write the original's spills), the scratchpad, the
// bus log, the virtual cycles and the check-point count. A callee the test build does not emit (the row text builders
// behind sprintf) stops a run with a fatal event; both runs must stop at the same callee with the same machine state.
//
// Documented-rule checks restate the fusion rules on the host from the decoded tables and require both bodies to agree
// with them: the normal fusion (chart arcana, (level0 + level1) / 2 + 1, the same-arcana rule, the special recipes),
// the triangle arcana and level, the result searches, the availability rules, the recipe matching.
#include "pair_harness.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/fusion.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstdio>
#include <cstdlib>
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
using game::kCombineListFile;
using game::kCombineMiscFile;
using game::kNormalChart;
using game::kRecipeCategories;
using game::kRecipeRules;
using game::kTriangleChart1;
using game::kTriangleChart2;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_sub_3D02E0_003d02e0)
P3FES_DECL_PAIR(fn_sub_3D0600_003d0600)
P3FES_DECL_PAIR(fn_sub_3D21D0_003d21d0)
P3FES_DECL_PAIR(fn_sub_3D25C0_003d25c0)
P3FES_DECL_PAIR(fn_sub_3D2640_003d2640)
P3FES_DECL_PAIR(fn_sub_3D26C0_003d26c0)
P3FES_DECL_PAIR(fn_sub_3D2710_003d2710)
P3FES_DECL_PAIR(fn_sub_3D2C00_003d2c00)
P3FES_DECL_PAIR(fn_sub_3D2DD0_003d2dd0)
P3FES_DECL_PAIR(fn_sub_3D2EF0_003d2ef0)
P3FES_DECL_PAIR(fn_sub_3D3010_003d3010)
P3FES_DECL_PAIR(fn_sub_3D3280_003d3280)
P3FES_DECL_PAIR(fn_sub_3D35C0_003d35c0)
P3FES_DECL_PAIR(fn_sub_3D3B70_003d3b70)
P3FES_DECL_PAIR(fn_sub_3D3C20_003d3c20)
P3FES_DECL_PAIR(fn_sub_3D3CA0_003d3ca0)
P3FES_DECL_PAIR(fn_sub_3D5510_003d5510)
P3FES_DECL_PAIR(fn_sub_3D5730_003d5730)
P3FES_DECL_PAIR(fn_sub_3D5850_003d5850)
P3FES_DECL_PAIR(fn_sub_3D58A0_003d58a0)
P3FES_DECL_PAIR(fn_sub_3D58C0_003d58c0)
P3FES_DECL_PAIR(fn_sub_3D5A40_003d5a40)
P3FES_DECL_PAIR(fn_sub_3D5BB0_003d5bb0)
P3FES_DECL_PAIR(fn_sub_3D5C90_003d5c90)
P3FES_DECL_PAIR(fn_sub_3D5CD0_003d5cd0)
P3FES_DECL_PAIR(fn_sub_3D5DC0_003d5dc0)
P3FES_DECL_PAIR(fn_sub_3D5E60_003d5e60)
P3FES_DECL_PAIR(fn_sub_3D6200_003d6200)
P3FES_DECL_PAIR(fn_sub_3D64A0_003d64a0)
P3FES_DECL_PAIR(fn_sub_3D6740_003d6740)
P3FES_DECL_PAIR(fn_sub_3D6910_003d6910)
P3FES_DECL_PAIR(fn_sub_3D6AE0_003d6ae0)
P3FES_DECL_PAIR(fn_sub_3D6C90_003d6c90)
P3FES_DECL_PAIR(fn_sub_3D6E60_003d6e60)
P3FES_DECL_PAIR(fn_sub_3D6F80_003d6f80)
P3FES_DECL_PAIR(fn_sub_3D7180_003d7180)
P3FES_DECL_PAIR(fn_sub_3D71D0_003d71d0)
P3FES_DECL_PAIR(fn_sub_3D72F0_003d72f0)
P3FES_DECL_PAIR(fn_sub_3D74B0_003d74b0)
P3FES_DECL_PAIR(fn_sub_3D7A30_003d7a30)
P3FES_DECL_PAIR(fn_sub_3D7AC0_003d7ac0)
P3FES_DECL_PAIR(fn_sub_3D7DA0_003d7da0)
P3FES_DECL_PAIR(fn_sub_3D8080_003d8080)
P3FES_DECL_PAIR(fn_sub_3D8230_003d8230)
P3FES_DECL_PAIR(fn_sub_3D8260_003d8260)
P3FES_DECL_PAIR(fn_sub_3D8370_003d8370)
P3FES_DECL_PAIR(fn_sub_3D84C0_003d84c0)
P3FES_DECL_PAIR(fn_sub_3D8630_003d8630)
P3FES_DECL_PAIR(fn_sub_3D8830_003d8830)
P3FES_DECL_PAIR(fn_sub_3D9C90_003d9c90)
P3FES_DECL_PAIR(fn_sub_3DA2A0_003da2a0)
P3FES_DECL_PAIR(fn_sub_3DA3A0_003da3a0)
P3FES_DECL_PAIR(fn_sub_3DA3E0_003da3e0)
P3FES_DECL_PAIR(fn_sub_3DA470_003da470)
P3FES_DECL_PAIR(fn_sub_3DA570_003da570)
P3FES_DECL_PAIR(fn_sub_3DB580_003db580)
P3FES_DECL_PAIR(fn_sub_3DB5E0_003db5e0)
P3FES_DECL_PAIR(fn_sub_3DC210_003dc210)
P3FES_DECL_PAIR(fn_sub_3DEB20_003deb20)
P3FES_DECL_PAIR(fn_sub_3DEB80_003deb80)
P3FES_DECL_PAIR(fn_sub_3DEC00_003dec00)
P3FES_DECL_PAIR(fn_sub_3DECD0_003decd0)
P3FES_DECL_PAIR(fn_sub_3DED40_003ded40)
P3FES_DECL_PAIR(fn_sub_3DED70_003ded70)
P3FES_DECL_PAIR(fn_sub_3DEE80_003dee80)
P3FES_DECL_PAIR(fn_sub_3DEF10_003def10)
P3FES_DECL_PAIR(fn_sub_3DEF40_003def40)
P3FES_DECL_PAIR(fn_sub_3DEF80_003def80)
P3FES_DECL_PAIR(fn_sub_3DF010_003df010)
P3FES_DECL_PAIR(fn_sub_3DF090_003df090)
P3FES_DECL_PAIR(fn_sub_3DF100_003df100)
P3FES_DECL_PAIR(fn_sub_3DF220_003df220)
P3FES_DECL_PAIR(fn_sub_3D02F0_003d02f0)
P3FES_DECL_PAIR(fn_fclCombine_CreateCombineTasks_003d0310)
P3FES_DECL_PAIR(fn_fclCombine_UpdateCombineTask_003d03c0)
P3FES_DECL_PAIR(fn_fclCombine_UpdateCombineDrawTask_003d0400)
P3FES_DECL_PAIR(fn_fclCombine_UpdateCombineDraw2Task_003d0470)
P3FES_DECL_PAIR(fn_sub_3D04B0_003d04b0)
P3FES_DECL_PAIR(fn_sub_3D04D0_003d04d0)
P3FES_DECL_PAIR(fn_sub_3D0560_003d0560)
P3FES_DECL_PAIR(fn_sub_3D0610_003d0610)
P3FES_DECL_PAIR(fn_sub_3D2F00_003d2f00)
P3FES_DECL_PAIR(fn_sub_3D4CD0_003d4cd0)
P3FES_DECL_PAIR(fn_sub_3D74F0_003d74f0)
P3FES_DECL_PAIR(fn_sub_3DEDA0_003deda0)
P3FES_DECL_PAIR(fn_sub_3D9CC0_003d9cc0)
P3FES_DECL_PAIR(fn_sub_3D9EA0_003d9ea0)
P3FES_DECL_PAIR(fn_sub_3DA0C0_003da0c0)
P3FES_DECL_PAIR(fn_sub_3DE290_003de290)
P3FES_DECL_PAIR(fn_sub_3DD800_003dd800)
P3FES_DECL_PAIR(fn_sub_3DD9E0_003dd9e0)
P3FES_DECL_PAIR(fn_sub_3DDA80_003dda80)
P3FES_DECL_PAIR(fn_sub_3DDB00_003ddb00)
P3FES_DECL_PAIR(fn_sub_3DE160_003de160)
P3FES_DECL_PAIR(fn_sub_3D2D80_003d2d80)
P3FES_DECL_PAIR(fn_sub_3D3B00_003d3b00)
P3FES_DECL_PAIR(fn_sub_3D3CD0_003d3cd0)
P3FES_DECL_PAIR(fn_sub_3D4C80_003d4c80)
P3FES_DECL_PAIR(fn_sub_3D53E0_003d53e0)
P3FES_DECL_PAIR(fn_sub_3D5420_003d5420)
P3FES_DECL_PAIR(fn_sub_3D54A0_003d54a0)
P3FES_DECL_PAIR(fn_sub_3D4F30_003d4f30)
P3FES_DECL_PAIR(fn_sub_3D4F90_003d4f90)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace fs = std::filesystem;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ------------------------------------------------------------------------------------------------
// (free in every replay snapshot: 0x1B80000-0x1C00000 is zero, the stand-in heap follows at 0x1C00000)
constexpr u32 kWorld = 0x01B80000u;       // the random records of a case
constexpr u32 kWorldLen = 0x20000u;
constexpr u32 kTables = 0x01BA0000u;      // PERSONA.TBL / SKILL.TBL sections, the loader's layout (no snapshot)
constexpr u32 kRandState = 0x01BF0000u;   // the RpRandom state words
constexpr u32 kRandBase = 0x960070u;      // RpRandom: 0x960070 + *(gp - 17784): {start, front, rear, end}
constexpr u32 kFlagWords = 0x83A21Cu;     // u32[176]: the flag bit array (datGetFlag)
constexpr u32 kHeroSlots = 0x836BACu;     // the hero's persona slots: 12 x 52 bytes, +0 flags (bit 0 used), +2 id
constexpr u32 kHeroMaxWord = 0x83A45Cu;   // sub_175410: bit 2 -> 12 slots, ...
constexpr u32 kHeroUnit = 0x836224u;      // party member 1 (sub_16C470(1) -> datCalcGetLevel)
constexpr u32 kRoot = kGp - 18028u;       // the fclCombine sequence object
constexpr u32 kPersonaPtr = 0x7CE420u;    // the persona table pointer (gp - 18640)

// Callbacks of the emitted set (tests/game/CMakeLists.txt lists them).
constexpr u32 kRet0 = 0x3C4400u;      // `v0 = 0` (the nmlist default callbacks)

// The Velvet Room snapshot: the fusion route (config/inputs/fusion.txt, card fusion.ps2) at vblank 5000 in reference
// mode -- the fusion menu open, the hero holding persona 1 (Lv 2) and 46 (Lv 2); fusion_ref_6300 (the route's gate
// point) holds the result, persona 14 at Lv 3.
constexpr const char* kVrSnapshot = "fusion_vr_5000";
constexpr const char* kAfterSnapshot = "fusion_ref_6300";

// The PERSONA.TBL / SKILL.TBL section pointers of the loader records 0x692F38 / 0x692D40 (21_battle.md Â§3.2).
constexpr u32 kPersonaDst[] = {0x7CE420, 0x7CE428, 0x7CE430, 0x7CE434, 0x7CE44C, 0x7CE450, 0x7CE454, 0x7CE458, 0x7CE45C,
                               0x7CE460, 0x7CE464, 0x7CE468, 0x7CE438, 0x7CE43C, 0x7CE440, 0x7CE444, 0x7CE448};
constexpr u32 kSkillDst[] = {0x7CE3F4, 0x7CE3F8, 0x7CE3FC};

// --- guest RAM helpers -----------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();
    return (hi << 32) | rng();
}
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
u64 reg_of(u32 v, std::mt19937& rng) { return chance(rng, 10) ? (rng64(rng) & 0xFFFFFFFF00000000ull) | v : sx(v); }
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 8) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 2001) - 1000) / 997.0f);
    }
}

// --- the pair: trampolines that randomise the FPU / HI / LO and catch a fatal event ----------------------------------
struct RunExtra {
    bool fatal = false;
    u32 pc = 0;
    std::string what;
    std::array<u32, 32> fpr{};
    u32 acc = 0, fcr31 = 0;
};
Fn g_fn[2] = {};
RunExtra g_extra[2];
u32 g_seed = 0;
int g_pairs = 0;
std::map<std::string, std::pair<int, int>> g_tally;  // label -> (pairs, pairs stopped by a fatal event)
std::map<std::string, std::string> g_stop;            // label -> the first fatal event's text

template <int K>
void trampoline(EEContext& c) {
    std::mt19937 r{g_seed ^ 0x5BD1E995u};
    for (u32& f : c.fpr) f = rand_float(r);
    c.acc = rand_float(r);
    c.fcr31 = r() & 0x0083F078u;
    c.hi.u64[0] = rng64(r);
    c.hi.u64[1] = rng64(r);
    c.lo.u64[0] = rng64(r);
    c.lo.u64[1] = rng64(r);
    RunExtra& x = g_extra[K];
    x = RunExtra{};
    try {
        g_fn[K](c);
    } catch (const rt_test::FatalEvent& e) {
        x.fatal = true;
        x.pc = e.pc;
        x.what = e.what;
        const std::size_t host = x.what.find("; host return address");
        if (host != std::string::npos) x.what.resize(host);
    }
    std::copy(std::begin(c.fpr), std::end(c.fpr), x.fpr.begin());
    x.acc = c.acc;
    x.fcr31 = c.fcr31;
}

struct Result {
    u64 v0 = 0;
    bool fatal = false;
    std::string what;
};

// The stand-ins of every pair (tests/game/stand_ins.h): the heap (RwMalloc / RwFree through the RW slots, H_Malloc),
// printf / sprintf, the H_Cdvd layer, and recorders for the callees the test build does not emit -- the row text
// builders and element drawers (sprintf, sprites), the facility background / text objects of the shop band, the menu
// text builder sub_3D06D0, the panel animator sub_3D8850, the sequence and filter callbacks -- so the pairs run past
// them instead of stopping.
void fusion_world(StandInWorld& w) {
    install_standard(w);
    const std::pair<u32, const char*> rec[] = {
        {0x3DB650u, "row text (sub_3DB650)"}, {0x3DD260u, "row draw (sub_3DD260)"}, {0x3DFAE0u, "elem draw (sub_3DFAE0)"},
        {0x3D1DF0u, "elem draw (sub_3D1DF0)"}, {0x3D38B0u, "elem anim (sub_3D38B0)"}, {0x3C9D00u, "panel mode (sub_3C9D00)"},
        {0x3D06D0u, "menu text (sub_3D06D0)"}, {0x3D8850u, "panel anim (sub_3D8850)"}, {0x40C6F0u, "bg create (sub_40C6F0)"},
        {0x40C9A0u, "bg end (sub_40C9A0)"}, {0x40CAD0u, "bg free (sub_40CAD0)"}, {0x401420u, "bg start (sub_401420)"},
        {0x4014E0u, "bg state (sub_4014E0)"}, {0x40E360u, "text cleanup (sub_40E360)"}, {0x3C77A0u, "msg cleanup (sub_3C77A0)"},
        {0x3D2200u, "root seq fn (sub_3D2200)"}, {0x3DF4A0u, "elem filter (sub_3DF4A0)"}, {0x1052B0u, "log (sub_1052B0)"},
        {0x3D32E0u, "menu step (sub_3D32E0)"}, {0x3D3620u, "menu step (sub_3D3620)"},
    };
    for (const auto& [va, name] : rec) w.si.install_recorder(va, name, 0);
}

// Runs hand and recomp from the same machine (RAM restored in between) and requires identical results everywhere.
// After the pair the recompiled run's output is in place.
Result pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::map<unsigned, u64> gpr_in = {}) {
    static const bool trace = std::getenv("P3FES_FUSION_TRACE") != nullptr;  // name and seed of every pair on stderr
    if (trace) std::fprintf(stderr, "%s seed %u\n", what, seed);
    g_fn[0] = hand;
    g_fn[1] = recomp;
    g_seed = seed;
    HwCheck hw;
    hw.ranges = {{0, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in = std::move(gpr_in);
    const SiPair sp = run_pair_si(m, &trampoline<0>, &trampoline<1>, args, seed, what, hw, fusion_world);
    const HwPair& p = sp.hw;
    INFO(what);
    const RunExtra& a = g_extra[0];
    const RunExtra& b = g_extra[1];
    CHECK(a.fatal == b.fatal);
    CHECK(a.pc == b.pc);
    CHECK(a.what == b.what);
    CHECK(a.fpr == b.fpr);
    CHECK(a.acc == b.acc);
    CHECK(a.fcr31 == b.fcr31);
    ++g_pairs;
    auto& t = g_tally[what];
    ++t.first;
    if (b.fatal) {
        ++t.second;
        g_stop.emplace(what, b.what);
    }
    return Result{p.recomp.base.v0, b.fatal, b.what};
}

// The argument registers of a call; the ones a function does not take hold garbage, as at a real call site.
constexpr u64 kUnused = 0x5EED5EED5EED5EEDull;
std::mt19937_64 g_garbage{0x6A5F70u};
Args args4(u64 a0 = kUnused, u64 a1 = kUnused, u64 a2 = kUnused, u64 a3 = kUnused) {
    Args a{a0, a1, a2, a3};
    for (u64& x : a)
        if (x == kUnused) x = g_garbage();
    return a;
}

// --- the real tables ---------------------------------------------------------------------------------------------

std::vector<u8> read_file(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>(std::istreambuf_iterator<char>(f), {});
}

// The battle table loader's layout (sub_27DCD0): section k (u32 size + data, 16-aligned) copied to the arena, its
// pointer stored in dst[k]. Returns the next free arena address, 0 when the file is missing or short.
u32 load_table(Machine& m, const fs::path& file, const u32* dst, std::size_t n, u32 arena) {
    const std::vector<u8> t = read_file(file);
    if (t.empty()) return 0;
    std::size_t pos = 0;
    for (std::size_t k = 0; k < n; ++k) {
        if (pos + 4 > t.size()) return 0;
        u32 size;
        std::memcpy(&size, t.data() + pos, 4);
        if (pos + 4 + size > t.size()) return 0;
        std::memcpy(m.at(arena), t.data() + pos + 4, size);
        w32(m, dst[k], arena);
        arena += (size + 15u) & ~15u;
        pos += (size + 4u + 15u) & ~15u;
    }
    return arena;
}

// A machine with the ELF and the real tables; false (and a SKIP message) without the extracted files.
// With the Velvet Room snapshot present the machine is that snapshot (the real tables, flags, social links, hero and
// heap of a running game, the fusion menu open); else the ELF plus the tables as the loader lays them out.
bool g_snapshot_base = false;
std::vector<u8> g_base;  // the base machine's RAM: every case starts from it (a pair on bad input can scribble anywhere)
void reset(Machine& m) {
    if (g_base.size() == EEMemory::kMainRamSize) std::memcpy(m.mem.main_ram(), g_base.data(), g_base.size());
}
bool real_machine(Machine& m) {
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err));
        return false;
    }
    const std::vector<u8> snap = read_snapshot(kVrSnapshot);
    g_snapshot_base = snap.size() == EEMemory::kMainRamSize;
    if (g_snapshot_base) {
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(m);
        g_base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        return true;
    }
    write_rw_slots(m);
    const fs::path root = fs::path(extracted_root()) / "BTL" / "BATTLE";
    u32 arena = load_table(m, root / "PERSONA.TBL", kPersonaDst, std::size(kPersonaDst), kTables);
    if (arena) arena = load_table(m, root / "SKILL.TBL", kSkillDst, std::size(kSkillDst), arena);
    if (!arena) {
        MESSAGE("SKIP: battle/PERSONA.TBL or SKILL.TBL not found under " << root.string());
        return false;
    }
    g_base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    return true;
}

// The persona table as the bodies see it.
struct Table {
    const Machine& m;
    u32 base() const { return r32(m, kPersonaPtr); }
    u16 flags(u32 id) const { return r16(m, base() + 14 * id); }
    u8 arcana(u32 id) const { return r8(m, base() + 14 * id + 2); }
    u8 level(u32 id) const { return r8(m, base() + 14 * id + 3); }
};

// --- world builders --------------------------------------------------------------------------------------------------
struct World {
    Machine& m;
    std::mt19937& rng;
    u32 next = kWorld;
    std::vector<u32> ids;  // persona ids with an arcana (the usable ones)

    explicit World(Machine& mm, std::mt19937& r) : m(mm), rng(r) {
        std::memset(m.at(kWorld), 0, kWorldLen);
        if (!g_snapshot_base) std::memset(m.at(0), 0, 0x1000);  // the retail null-pointer paths read and write here
        const Table t{m};
        for (u32 id = 1; id < 256; ++id)
            if (t.arcana(id)) ids.push_back(id);
        // flags: mostly the rule flags and 3037, random
        for (u32 i = 0; i < 176; ++i) w32(m, kFlagWords + 4 * i, chance(rng, 30) ? rng() : 0);
        // the hero: level (unit +6, datCalcGetLevel) and persona slots
        w8(m, kHeroUnit + 6, static_cast<u8>(chance(rng, 90) ? 1 + rng() % 99 : rng()));
        w32(m, kHeroMaxWord, pick(rng, {4, 4, 4, 2, 1, 0}));
        for (u32 s = 0; s < 12; ++s) persona_at(kHeroSlots + 52 * s, chance(rng, 70) ? any_id() : 0, chance(rng, 85));
        // RpRandom: a 31-word additive state
        w32(m, kGp - 17784u, 0);
        for (u32 i = 0; i < 31; ++i) w32(m, kRandState + 4 * i, rng());
        w32(m, kRandBase + 0, kRandState);
        w32(m, kRandBase + 4, kRandState + 4 * (3 + rng() % 20));
        w32(m, kRandBase + 8, kRandState + 4 * (rng() % 3));
        w32(m, kRandBase + 12, kRandState + 4 * 31);
    }
    u32 alloc(u32 n) {
        const u32 a = next;
        next += (n + 15u) & ~15u;
        REQUIRE(next <= kWorld + kWorldLen);
        return a;
    }
    u32 any_id() { return ids[rng() % ids.size()]; }
    // a 52-byte persona instance: flags, id, level, skills, stats
    void persona_at(u32 p, u32 id, bool used = true) {
        std::memset(m.at(p), 0, 52);
        if (!id) return;
        const Table t{m};
        w16(m, p + 0, static_cast<u16>((used ? 1u : 0u) | (chance(rng, 20) ? (rng() & 0xC) : 0u)));
        w16(m, p + 2, static_cast<u16>(id));
        w8(m, p + 4, static_cast<u8>(chance(rng, 80) ? std::min<u32>(99, t.level(id) + rng() % 6) : rng() % 100));
        for (u32 k = 0; k < 8; ++k) w16(m, p + 12 + 2 * k, static_cast<u16>(chance(rng, 55) ? 1 + rng() % 0x1F0 : 0));
        for (u32 k = 0; k < 5; ++k) w8(m, p + 28 + k, static_cast<u8>(1 + rng() % 60));
        for (u32 k = 33; k < 52; ++k) w8(m, p + k, static_cast<u8>(chance(rng, 50) ? rng() : 0));
    }
    u32 persona(u32 id) {
        const u32 p = alloc(52);
        persona_at(p, id);
        return p;
    }
    // a 144-byte stock list from personas (0 = an empty entry)
    u32 stock(const std::vector<u32>& personas) {
        const Table t{m};
        const u32 s = alloc(144);
        for (u32 i = 0; i < personas.size() && i < 12; ++i) {
            w32(m, s + 12 * i, 0);
            w32(m, s + 12 * i + 4, personas[i]);
            w32(m, s + 12 * i + 8, personas[i] ? t.base() + 14 * r16(m, personas[i] + 2) : 0);
        }
        return s;
    }
    // n personas, some from a recipe of `category` (its ingredients, an arcana ingredient by a persona of that arcana)
    std::vector<u32> personas_for(unsigned n, int category) {
        std::vector<u32> ids_out;
        if (category >= 0) {
            const u32 table = r32(m, kRecipeCategories + 8 * category);
            const u32 count = r32(m, kRecipeCategories + 8 * category + 4);
            const u32 rec = table + 32 * (rng() % count);
            for (u32 k = 0; k < 8; ++k) {
                const u16 ing = r16(m, rec + 8 + 2 * k);
                const u32 v = ing & 0x3FF;
                if (!v || chance(rng, 8)) continue;
                if (ing & 0x4000) {
                    std::vector<u32> of;
                    const Table t{m};
                    for (u32 id : ids)
                        if (t.arcana(id) == v) of.push_back(id);
                    if (!of.empty()) ids_out.push_back(of[rng() % of.size()]);
                } else {
                    ids_out.push_back(v);
                }
            }
        }
        while (ids_out.size() < n) ids_out.push_back(chance(rng, 10) ? 0 : any_id());
        std::shuffle(ids_out.begin(), ids_out.end(), rng);
        std::vector<u32> out;
        for (u32 id : ids_out) out.push_back(id ? persona(id) : 0);
        return out;
    }
    // a pointer array of personas
    u32 ptrs(const std::vector<u32>& personas) {
        const u32 a = alloc(4 * 8);
        for (u32 i = 0; i < personas.size() && i < 8; ++i) w32(m, a + 4 * i, personas[i]);
        return a;
    }
    // a u16 id array (n entries)
    u32 id_array(const std::vector<u32>& personas) {
        const u32 a = alloc(2 * 16);
        for (u32 i = 0; i < personas.size() && i < 16; ++i) w16(m, a + 2 * i, personas[i] ? r16(m, personas[i] + 2) : 0);
        return a;
    }
    // a 12-entry exclusion list
    u32 exclude(std::initializer_list<u32> some = {}) {
        const u32 a = alloc(24);
        u32 k = 0;
        for (u32 v : some) w16(m, a + 2 * k++, static_cast<u16>(v));
        while (k < 12) w16(m, a + 2 * k++, static_cast<u16>(chance(rng, 15) ? any_id() : 0));
        return a;
    }
    // an 84-byte fusion result around a persona
    u32 result(u32 id) {
        const u32 r = alloc(84);
        w32(m, r, rng() & 7);
        persona_at(r + 4, id);
        for (u32 k = 0; k < 8; ++k) w16(m, r + 62 + 2 * k, static_cast<u16>(chance(rng, 30) ? 1 + rng() % 0x1F0 : 0));
        return r;
    }
};

u32 cat_count(const Machine& m, u32 c) { return r32(m, kRecipeCategories + 8 * c + 4); }

// =====================================================================================================================
// Host model of the rules (fusion.h), from the decoded tables
// =====================================================================================================================
struct Host {
    const Machine& m;
    Table t{m};
    bool flag(u32 id) const { return (r32(m, kFlagWords + 4 * (id >> 5)) >> (id & 31)) & 1; }
    // sub_3D5BB0
    bool available(u32 id) const {
        bool result = true;
        for (u32 i = 0; i < 67; ++i) {
            const u32 r = kRecipeRules + 8 * i;
            if (static_cast<s16>(r16(m, r + 4)) != static_cast<s32>(id)) continue;
            const u16 mode = r16(m, r + 6);
            if (mode & 1) {
                if (!flag(r32(m, r))) return false;
            } else if (mode & 2) {
                result = false;
                if (flag(r32(m, r))) return true;
            }
        }
        return result;
    }
    // sub_3D7AC0 (up) / sub_3D7DA0 (down)
    u32 find(u32 arcana, u32 target, const std::vector<u16>& excl, bool up) const {
        u32 best = 0, pick = 0;
        for (u32 id = 0; id < 192; ++id) {
            if (t.arcana(id) != arcana || (t.flags(id) & 3) || !available(id)) continue;
            if (!best || t.level(best) < t.level(id)) best = id;
            const u32 lv = t.level(id);
            if (up ? lv < target : lv > target) continue;
            if (std::find(excl.begin(), excl.end(), id) != excl.end()) continue;
            if (!pick || (up ? lv < t.level(pick) : t.level(pick) < lv)) pick = id;
        }
        if (!pick && best && t.level(best) < target) pick = best;
        return pick;
    }
    u8 chart(u32 base, u32 a, u32 b) const { return a <= b ? r8(m, base + 22 * a + b) : r8(m, base + 22 * b + a); }
    // sub_3D6200's choice: the first recipe of the category matching the ids with an available result
    u32 special(u32 category, const std::vector<u16>& ids) const {
        const u32 table = r32(m, kRecipeCategories + 8 * category);
        for (u32 k = 0; k < cat_count(m, category); ++k) {
            const u32 rec = table + 32 * k;
            if (!r16(m, rec)) continue;
            u32 used = 0, matched = 0;
            bool ok = true;
            for (u32 i = 0; i < 8 && ok; ++i) {
                const u16 ing = r16(m, rec + 8 + 2 * i);
                const s32 v = static_cast<s32>(static_cast<u32>(ing) << 22) >> 22;
                if (!v) continue;
                bool found = false;
                for (u32 j = 0; j < ids.size(); ++j) {
                    if (used & (1u << j)) continue;
                    const u32 key = (ing & 0x4000) ? t.arcana(ids[j]) : ids[j];
                    if (static_cast<s32>(key) == v) {
                        used |= 1u << j;
                        ++matched;
                        found = true;
                        break;
                    }
                }
                if ((ing & 0x8000) && !found) ok = false;
            }
            if (!ok || used == 0 || matched < category + 2) continue;
            if (available(r16(m, rec))) return r16(m, rec);
        }
        return 0;
    }
    // sub_3D64A0: {code, id}
    std::pair<u32, u32> normal(u32 id0, u32 id1) const {
        if (const u32 s = special(0, {static_cast<u16>(id0), static_cast<u16>(id1)})) return {2, s};
        const u32 r = chart(kNormalChart, t.arcana(id0), t.arcana(id1));
        if (!r) return {0, 0};
        const u32 target = ((t.level(id0) + t.level(id1)) / 2 + 1) & 0xFF;
        const std::vector<u16> excl{static_cast<u16>(id0), static_cast<u16>(id1)};
        const bool same = t.arcana(id0) == r && t.arcana(id1) == r;
        const u32 res = find(r, target, excl, !same);
        return {res ? 1u : 0u, res};
    }
};

// =====================================================================================================================
// The leaves and table readers
// =====================================================================================================================

TEST_CASE("game(fusion): the small accessors and arithmetic equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 900; ++i) {
        const u32 seed = seed_of(i, 0x11u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        w32(m, kRoot, chance(rng, 50) ? w.alloc(64) : 0);
        switch (i % 15) {
        case 0: pair(m, PAIR(fn_sub_3D02E0_003d02e0), args4(), seed, "sub_3D02E0"); break;
        case 1: pair(m, PAIR(fn_sub_3D0600_003d0600), args4(), seed, "sub_3D0600"); break;
        case 2: pair(m, PAIR(fn_sub_3D2C00_003d2c00), args4(), seed, "sub_3D2C00"); break;
        case 3: pair(m, PAIR(fn_sub_3D2EF0_003d2ef0), args4(), seed, "sub_3D2EF0"); break;
        case 4: {
            const u32 menu = w.alloc(16), win = w.alloc(16);
            w32(m, menu, chance(rng, 80) ? win : 0);
            w32(m, win + 4, rng());
            pair(m, PAIR(fn_sub_3D3010_003d3010), args4(sx(chance(rng, 90) ? menu : 0)), seed, "sub_3D3010");
            break;
        }
        case 5: pair(m, PAIR(fn_sub_3DEF10_003def10), args4(chance(rng, 50) ? reg_of(rng() % 8, rng) : rng64(rng)), seed, "sub_3DEF10"); break;
        case 6: {
            const u64 n = chance(rng, 20) ? sx(rng() % 3) : sx(2 + rng() % 9);
            pair(m, PAIR(fn_sub_3DEF40_003def40), args4(sx(rng() % 640), n, sx(rng() % 12)), seed, "sub_3DEF40");
            break;
        }
        case 7: pair(m, PAIR(fn_sub_3D8830_003d8830), args4(sx(rng() % 5)), seed, "sub_3D8830"); break;
        case 8: pair(m, PAIR(fn_sub_3D5850_003d5850), args4(sx(rng() % 5)), seed, "sub_3D5850"); break;
        case 9: pair(m, PAIR(fn_sub_3D74B0_003d74b0), args4(reg_of(w.any_id(), rng)), seed, "sub_3D74B0"); break;
        case 10: pair(m, PAIR(fn_sub_3D5C90_003d5c90), args4(), seed, "sub_3D5C90"); break;
        case 11: pair(m, PAIR(fn_sub_3D58A0_003d58a0), args4(), seed, "sub_3D58A0"); break;
        case 12: pair(m, PAIR(fn_sub_3D7180_003d7180), args4(), seed, "sub_3D7180"); break;
        case 13: pair(m, PAIR(fn_sub_3D6C90_003d6c90), args4(sx(rng() % 4)), seed, "sub_3D6C90"); break;
        case 14: pair(m, PAIR(fn_sub_3D58C0_003d58c0), args4(reg_of(rng() % 24, rng), sx(rng() % 100)), seed, "sub_3D58C0 price"); break;
        }
    }
}

TEST_CASE("game(fusion): documented rules of the small functions") {
    Machine m;
    if (!real_machine(m)) return;
    std::mt19937 rng{3};
    World w(m, rng);
    CHECK(m.str(kCombineMiscFile) == "fclCombineMisc.c");
    CHECK(m.str(kCombineListFile) == "fclCombineList.c");
    for (u32 n = 0; n < 12; ++n) {
        const Result r = pair(m, PAIR(fn_sub_3DEF10_003def10), args4(sx(n)), 100 + n, "rule sub_3DEF10");
        CHECK(r.v0 == (n < 2 ? 0u : 9u * (n + 1)));
    }
    for (u32 c = 0; c < 5; ++c) {
        const Result r = pair(m, PAIR(fn_sub_3D8830_003d8830), args4(sx(c)), 200 + c, "rule sub_3D8830");
        CHECK(r.v0 == cat_count(m, c));
    }
    const u32 counts[5] = {2, 1, 8, 5, 5};  // retail: the special recipes of 2..6 personas
    for (u32 c = 0; c < 5; ++c) CHECK(cat_count(m, c) == counts[c]);
    for (s32 width : {0, 100, 255, 640})
        for (s32 n : {0, 1, 2, 5})
            for (s32 i : {0, 1, 3}) {
                const Result r = pair(m, PAIR(fn_sub_3DEF40_003def40), args4(sx(width), sx(n), sx(i)), 300, "rule sub_3DEF40");
                const s32 expect = (width >> 1) - (n < 2 ? 0 : i * width / (n - 1)) + 90;
                CHECK(static_cast<s32>(r.v0) == expect);
            }
    // the scenario word: 0x6A4BA0 outside The Answer
    w32(m, 0x83A21Cu, 0);
    const Result sc = pair(m, PAIR(fn_sub_3D5C90_003d5c90), args4(), 400, "rule sub_3D5C90");
    CHECK((sc.v0 == 0x6A4BA0u || sc.v0 == 0x6A4E10u));
    // the triangle pair table at gp - 21856 (retail: (0,2), (0,1), (1,2))
    CHECK(r8(m, kGp - 21856) == 0);
    CHECK(r8(m, kGp - 21855) == 2);
    // the normal chart: Fool (1) x Magician (2) = Hierophant (6); Fool x Fool = Fool (same arcana)
    CHECK(r8(m, kNormalChart + 22 * 1 + 2) == 6);
    CHECK(r8(m, kNormalChart + 22 * 1 + 1) == 1);
}

// =====================================================================================================================
// The fusion rules
// =====================================================================================================================

TEST_CASE("game(fusion): the availability rules and the result searches equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 700; ++i) {
        const u32 seed = seed_of(i, 0x22u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        Host h{m};
        switch (i % 4) {
        case 0: {
            const u32 id = chance(rng, 50) ? r16(m, kRecipeRules + 8 * (rng() % 67) + 4) : w.any_id();
            const Result r = pair(m, PAIR(fn_sub_3D5BB0_003d5bb0), args4(reg_of(id, rng)), seed, "sub_3D5BB0 available");
            if (!r.fatal) CHECK(r.v0 == (h.available(id & 0xFFFF) ? 1u : 0u));
            break;
        }
        case 1:
        case 2: {
            const u32 arcana = 1 + rng() % 21;
            const u32 level = chance(rng, 10) ? rng() % 256 : rng() % 100;
            const u32 ex = w.exclude();
            const bool up = i % 4 == 1;
            const Result r = up ? pair(m, PAIR(fn_sub_3D7AC0_003d7ac0), args4(reg_of(arcana, rng), reg_of(level, rng), sx(ex)), seed, "sub_3D7AC0 find up")
                                : pair(m, PAIR(fn_sub_3D7DA0_003d7da0), args4(reg_of(arcana, rng), reg_of(level, rng), sx(ex)), seed, "sub_3D7DA0 find down");
            std::vector<u16> excl;
            for (u32 k = 0; k < 12; ++k) excl.push_back(r16(m, ex + 2 * k));
            if (!r.fatal) CHECK(r.v0 == h.find(arcana, level & 0xFF, excl, up));
            break;
        }
        case 3: {
            const u32 c = rng() % 5;
            pair(m, PAIR(fn_sub_3D84C0_003d84c0), args4(kUnused, reg_of(c, rng)), seed, "sub_3D84C0 any recipe available");
            break;
        }
        }
    }
}

TEST_CASE("game(fusion): the recipe matching equals its recompiled bodies and the host rules") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 900; ++i) {
        const u32 seed = seed_of(i, 0x33u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        Host h{m};
        const u32 cat = rng() % 5;
        const unsigned n = cat + 2 + rng() % 4;
        const std::vector<u32> ps = w.personas_for(std::min(n, 12u), chance(rng, 80) ? static_cast<int>(cat) : -1);
        const u32 stock = w.stock(ps);
        switch (i % 6) {
        case 0: {
            const u32 table = r32(m, kRecipeCategories + 8 * cat);
            const u32 rec = table + 32 * (rng() % cat_count(m, cat));
            const u32 out = w.alloc(40);
            pair(m, PAIR(fn_sub_3D5510_003d5510), args4(sx(chance(rng, 95) ? out : 0), sx(rec), sx(cat + 2), sx(stock)), seed, "sub_3D5510 match");
            break;
        }
        case 1: {
            const u32 out = w.alloc(40);
            pair(m, PAIR(fn_sub_3D5730_003d5730), args4(sx(out), sx(cat), sx(rng() % (cat_count(m, cat) + 1)), sx(stock)), seed, "sub_3D5730 recipe");
            break;
        }
        case 2: {
            const u32 table = r32(m, kRecipeCategories + 8 * cat);
            const u32 rec = table + 32 * (rng() % cat_count(m, cat));
            const u32 ids = w.id_array(ps);
            const u32 found = chance(rng, 80) ? w.alloc(4) : 0;
            pair(m, PAIR(fn_sub_3D5A40_003d5a40), args4(sx(rec), sx(cat + 2), sx(ids), sx(static_cast<u32>(ps.size()))), seed,
                 "sub_3D5A40 mask", {{GPR_T0, sx(found)}});
            break;
        }
        case 3: {
            const u32 out = w.alloc(52);
            const u32 ids = w.id_array(ps);
            std::vector<u16> idv;
            for (u32 p : ps) idv.push_back(p ? r16(m, p + 2) : 0);
            const Result r = pair(m, PAIR(fn_sub_3D6200_003d6200), args4(sx(out), sx(cat), sx(ids), sx(static_cast<u32>(ps.size()))), seed,
                                  "sub_3D6200 special");
            if (!r.fatal) {
                const u32 expect = h.special(cat, idv);
                CHECK((r.v0 != 0) == (expect != 0));
                if (expect && r.v0) {
                    CHECK(r16(m, out + 2) == expect);
                    CHECK(r.v0 == h.t.arcana(expect));
                }
            }
            break;
        }
        case 4: pair(m, PAIR(fn_sub_3D8630_003d8630), args4(sx(stock), sx(cat)), seed, "sub_3D8630 recipe in stock"); break;
        case 5: {
            const u32 out = w.alloc(52);
            const u32 pp = w.ptrs(ps);
            const u32 kind = chance(rng, 40) ? cat : rng() % 5;
            pair(m, PAIR(fn_sub_3D6910_003d6910), args4(sx(out), sx(kind), sx(pp)), seed, "sub_3D6910 by kind");
            break;
        }
        }
    }
}

TEST_CASE("game(fusion): normal and triangle fusion equal their recompiled bodies and the documented rules") {
    Machine m;
    if (!real_machine(m)) return;
    int checked = 0;
    for (int i = 0; i < 1200; ++i) {
        const u32 seed = seed_of(i, 0x44u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        Host h{m};
        switch (i % 4) {
        case 0:
        case 1: {
            u32 id0 = w.any_id(), id1 = w.any_id();
            if (chance(rng, 15)) {  // a special recipe of two
                const u32 rec = r32(m, kRecipeCategories) + 32 * (rng() % cat_count(m, 0));
                id0 = r16(m, rec + 8) & 0x3FF;
                id1 = r16(m, rec + 10) & 0x3FF;
            }
            if (chance(rng, 15)) {  // the same arcana
                const Table t{m};
                std::vector<u32> of;
                for (u32 id : w.ids)
                    if (t.arcana(id) == t.arcana(id0) && id != id0) of.push_back(id);
                if (!of.empty()) id1 = of[rng() % of.size()];
            }
            const u32 out = w.alloc(52);
            const Result r = pair(m, PAIR(fn_sub_3D64A0_003d64a0), args4(sx(out), reg_of(id0, rng), reg_of(id1, rng)), seed, "sub_3D64A0 normal");
            if (!r.fatal) {
                const auto [code, id] = h.normal(id0, id1);
                CHECK(r.v0 == code);
                if (code) CHECK(r16(m, out + 2) == id);
                ++checked;
            }
            break;
        }
        case 2: {
            const std::vector<u32> ps = w.personas_for(3, chance(rng, 20) ? 1 : -1);
            if (!ps[0] || !ps[1] || !ps[2]) break;
            const Result r = pair(m, PAIR(fn_sub_3D5E60_003d5e60), args4(sx(ps[0]), sx(ps[1]), sx(ps[2])), seed, "sub_3D5E60 triangle arcana");
            if (!r.fatal) {
                // the host: sort by level (then arcana), highest first; chart1 of the two lower, chart2 with the highest
                std::array<u32, 3> p{ps[0], ps[1], ps[2]};
                const Table t{m};
                const std::pair<int, int> steps[3] = {{0, 2}, {0, 1}, {1, 2}};
                for (auto [a, b] : steps) {
                    const u32 la = r8(m, p[a] + 4), lb = r8(m, p[b] + 4);
                    if (la < lb || (la == lb && t.arcana(r16(m, p[b] + 2)) < t.arcana(r16(m, p[a] + 2)))) std::swap(p[a], p[b]);
                }
                const u32 r1 = h.chart(kTriangleChart1, t.arcana(r16(m, p[1] + 2)), t.arcana(r16(m, p[2] + 2)));
                const u32 expect = r1 ? h.chart(kTriangleChart2, t.arcana(r16(m, p[0] + 2)), r1) : 0;
                CHECK(r.v0 == expect);
            }
            break;
        }
        case 3: {
            const std::vector<u32> ps = w.personas_for(3, chance(rng, 20) ? 1 : -1);
            const u32 out = w.alloc(52);
            const u32 p0 = ps[0] ? ps[0] : w.persona(w.any_id());
            const u32 p1 = ps[1] ? ps[1] : w.persona(w.any_id());
            const u32 p2 = ps[2] ? ps[2] : w.persona(w.any_id());
            pair(m, PAIR(fn_sub_3D6740_003d6740), args4(sx(out), sx(p0), sx(p1), sx(p2)), seed, "sub_3D6740 triangle");
            break;
        }
        }
    }
    MESSAGE("normal fusions checked against the host rules: " << checked);
}

TEST_CASE("game(fusion): the stock, partner masks and fusion previews equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 640; ++i) {
        const u32 seed = seed_of(i, 0x55u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const unsigned n = 2 + rng() % 11;
        const std::vector<u32> ps = w.personas_for(n, chance(rng, 30) ? static_cast<int>(rng() % 5) : -1);
        const u32 stock = w.stock(ps);
        switch (i % 8) {
        case 0: pair(m, PAIR(fn_sub_3D5CD0_003d5cd0), args4(sx(w.alloc(144))), seed, "sub_3D5CD0 build stock"); break;
        case 1: pair(m, PAIR(fn_sub_3D8260_003d8260), args4(sx(stock), sx(rng() % n)), seed, "sub_3D8260 partners"); break;
        case 2: {
            const u32 a = rng() % n;
            const u32 b = (a + 1 + rng() % (n - 1)) % n;
            pair(m, PAIR(fn_sub_3D8370_003d8370), args4(sx(stock), sx(a), sx(b)), seed, "sub_3D8370 triangle partners");
            break;
        }
        case 3: {
            const u32 kind = rng() % 5;
            std::vector<u32> sel;
            for (u32 p : ps)
                if (p) sel.push_back(p);
            while (sel.size() < 6) sel.push_back(w.persona(w.any_id()));
            pair(m, PAIR(fn_sub_3D6AE0_003d6ae0), args4(sx(w.alloc(84)), sx(kind), sx(w.ptrs(sel))), seed, "sub_3D6AE0 preview");
            break;
        }
        case 4: {
            std::vector<u32> sel;
            for (u32 p : ps)
                if (p) sel.push_back(p);
            while (sel.size() < 3) sel.push_back(w.persona(w.any_id()));
            const u32 cnt = 1 + rng() % std::min<u32>(6, static_cast<u32>(sel.size()));
            pair(m, PAIR(fn_sub_3D7A30_003d7a30), args4(sx(w.persona(w.any_id())), sx(w.ptrs(sel)), sx(cnt)), seed, "sub_3D7A30 inherit");
            break;
        }
        case 5: pair(m, PAIR(fn_sub_3D5DC0_003d5dc0), args4(reg_of(w.any_id(), rng)), seed, "sub_3D5DC0 rank letter"); break;
        case 6: pair(m, PAIR(fn_sub_3D72F0_003d72f0), args4(sx(w.persona(w.any_id()))), seed, "sub_3D72F0 bonus roll"); break;
        case 7: {
            const u32 res = w.result(w.any_id());
            pair(m, PAIR(fn_sub_3D8230_003d8230), args4(sx(res)), seed, "sub_3D8230 registered");
            break;
        }
        }
    }
}

TEST_CASE("game(fusion): the accidents, skill copy and commit equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 480; ++i) {
        const u32 seed = seed_of(i, 0x66u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const u32 from = w.result(w.any_id());
        switch (i % 4) {
        case 0: pair(m, PAIR(fn_sub_3D6E60_003d6e60), args4(sx(w.result(w.any_id())), sx(from)), seed, "sub_3D6E60 copy skills"); break;
        case 1: pair(m, PAIR(fn_sub_3D6F80_003d6f80), args4(sx(w.alloc(84)), sx(from), sx(w.exclude())), seed, "sub_3D6F80 accident"); break;
        case 2: pair(m, PAIR(fn_sub_3D71D0_003d71d0), args4(sx(w.alloc(84)), sx(from), sx(w.exclude())), seed, "sub_3D71D0 accident fool"); break;
        case 3: {
            std::vector<u32> sel;
            const unsigned cnt = 2 + rng() % 4;
            for (unsigned k = 0; k < cnt; ++k) {  // ingredients: mostly the hero's own personas
                const u32 slot = kHeroSlots + 52 * (rng() % 12);
                sel.push_back(chance(rng, 80) && r16(m, slot + 2) ? slot : w.persona(w.any_id()));
            }
            pair(m, PAIR(fn_sub_3D8080_003d8080), args4(sx(from), sx(w.ptrs(sel)), sx(cnt)), seed, "sub_3D8080 commit");
            break;
        }
        }
    }
}

// =====================================================================================================================
// The menu steps and the list menu
// =====================================================================================================================

// A sequence object for gp - 18028 (an nm list object with an nmSequence payload; nm_message.h).
u32 sequence_object(World& w) {
    Machine& m = w.m;
    const u32 obj = w.alloc(40 + 64);
    w32(m, obj + 20, kRet0);
    w32(m, obj + 24, kRet0);
    w32(m, obj + 28, kRet0);
    w32(m, obj + 32, 40 + 64);
    w32(m, obj + 36, obj + 40);
    return obj;
}

// A step node: payload (+20) -> a record whose +20 -> state word.
u32 step_node(World& w, bool done) {
    Machine& m = w.m;
    const u32 node = w.alloc(64), rec = w.alloc(64), pay = w.alloc(64);
    w32(m, node + 20, rec);
    w32(m, rec + 20, done ? 8u | (w.rng() & 7u) : w.rng() & ~8u);
    w32(m, rec + 40, pay);  // nmNodePayloadWord40
    w32(m, pay, w.rng() % 100);
    return node;
}

TEST_CASE("game(fusion): the menu step helpers equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 600; ++i) {
        const u32 seed = seed_of(i, 0x77u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        w32(m, kRoot, sequence_object(w));
        const u32 work = w.alloc(64);
        w32(m, work + 40, chance(rng, 80) ? step_node(w, chance(rng, 50)) : 0);
        w32(m, work + 24, chance(rng, 80) ? step_node(w, chance(rng, 50)) : 0);
        const u32 node = step_node(w, false);
        const u32 pay = r32(m, r32(m, node + 20) + 40);
        switch (i % 12) {
        case 0: pair(m, PAIR(fn_sub_3D2640_003d2640), args4(sx(work)), seed, "sub_3D2640 take step 40"); break;
        case 1: pair(m, PAIR(fn_sub_3D3C20_003d3c20), args4(sx(work)), seed, "sub_3D3C20 take step 24"); break;
        case 2: pair(m, PAIR(fn_sub_3D26C0_003d26c0), args4(sx(r32(m, kRoot)), sx(node)), seed, "sub_3D26C0 step clear"); break;
        case 3: pair(m, PAIR(fn_sub_3D2710_003d2710), args4(kUnused, sx(node)), seed, "sub_3D2710 step nop"); break;
        case 4: pair(m, PAIR(fn_sub_3D2DD0_003d2dd0), args4(kUnused, sx(node)), seed, "sub_3D2DD0 step nop"); break;
        case 5: pair(m, PAIR(fn_sub_3D3CA0_003d3ca0), args4(kUnused, sx(node)), seed, "sub_3D3CA0 step done"); break;
        case 6: pair(m, PAIR(fn_sub_3D25C0_003d25c0), args4(sx(chance(rng, 80) ? work : 0)), seed, "sub_3D25C0 add step 6"); break;
        case 7: pair(m, PAIR(fn_sub_3D3B70_003d3b70), args4(sx(chance(rng, 80) ? work : 0), rng64(rng)), seed, "sub_3D3B70 add step 2"); break;
        case 8: pair(m, PAIR(fn_sub_3D21D0_003d21d0), args4(), seed, "sub_3D21D0 call all"); break;
        case 9: {
            const u32 menu = w.alloc(16), holder = w.alloc(16);
            w32(m, menu, chance(rng, 80) ? holder : 0);
            w32(m, holder + 8, 0);  // no window: the close calls see a null object
            pair(m, PAIR(fn_sub_3D3280_003d3280), args4(sx(chance(rng, 90) ? menu : 0)), seed, "sub_3D3280 menu close");
            break;
        }
        case 10: {
            w32(m, pay + 16, 0);
            w32(m, pay + 20, 0);
            w32(m, pay + 8, 0);
            pair(m, PAIR(fn_sub_3D35C0_003d35c0), args4(kUnused, sx(node)), seed, "sub_3D35C0 step free");
            break;
        }
        case 11: {
            const u32 holder = w.alloc(16);
            w32(m, holder + 4, 0);
            pair(m, PAIR(fn_sub_3DED40_003ded40), args4(sx(chance(rng, 50) ? holder : 0)), seed, "sub_3DED40 elem destroy");
            break;
        }
        }
    }
}

// A facility element list: holder {owner, list object}; elements are node payloads (+4 node, +8 flags, ...).
struct Elems {
    u32 holder, obj, owner_state;
    std::vector<u32> elems;
};
Elems element_list(World& w, unsigned n) {
    Machine& m = w.m;
    Elems e;
    e.holder = w.alloc(16);
    e.obj = w.alloc(40 + 20);
    w32(m, e.obj + 20, kRet0);
    w32(m, e.obj + 24, kRet0);
    w32(m, e.obj + 28, kRet0);
    w32(m, e.obj + 32, 60);
    w32(m, e.obj + 36, e.holder);
    w32(m, e.holder + 4, e.obj);
    // the owner chain sub_3DFAC0 reads: holder->+0 -> +12 -> +20 -> +28 -> word
    const u32 owner = w.alloc(32), a = w.alloc(32), b = w.alloc(32), c = w.alloc(64);
    e.owner_state = c;
    w32(m, e.holder, owner);
    w32(m, owner + 12, a);
    w32(m, a + 20, b);
    w32(m, b + 28, c);
    w32(m, c, chance(w.rng, 85) ? w.alloc(64) : 0);
    std::vector<u32> nodes;
    for (unsigned k = 0; k < n; ++k) {
        const u32 node = w.alloc(24 + 64);
        const u32 el = node + 24;
        w32(m, node + 20, el);
        w32(m, el + 4, node);
        w32(m, el + 8, chance(w.rng, 60) ? 4u | (w.rng() & 3u) : w.rng() & 3u);
        for (u32 k2 = 12; k2 < 56; k2 += 4) w32(m, el + k2, w.rng() % 1000);
        nodes.push_back(node);
        e.elems.push_back(el);
    }
    for (unsigned k = 0; k < n; ++k) {
        w32(m, nodes[k] + 12, k ? nodes[k - 1] : 0);
        w32(m, nodes[k] + 16, k + 1 < n ? nodes[k + 1] : 0);
    }
    w32(m, e.obj + 4, n ? nodes.front() : 0);
    w32(m, e.obj + 8, n ? nodes.back() : 0);
    w16(m, e.obj + 16, static_cast<u16>(n));
    return e;
}

TEST_CASE("game(fusion): the facility element helpers equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 700; ++i) {
        const u32 seed = seed_of(i, 0x88u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const Elems e = element_list(w, rng() % 5);
        const u32 el = e.elems.empty() ? w.alloc(64) : e.elems[rng() % e.elems.size()];
        switch (i % 7) {
        case 0: pair(m, PAIR(fn_sub_3DF010_003df010), args4(sx(e.holder)), seed, "sub_3DF010 all done"); break;
        case 1: pair(m, PAIR(fn_sub_3DEF80_003def80), args4(sx(e.holder)), seed, "sub_3DEF80 restart all"); break;
        case 2: pair(m, PAIR(fn_sub_3DF090_003df090), args4(sx(e.holder), sx(chance(rng, 50) ? 16 * (rng() % 4) : 0)), seed, "sub_3DF090 new"); break;
        case 3: {
            const u32 desc = w.alloc(32);
            for (u32 k = 0; k < 28; k += 2) w16(m, desc + k, static_cast<u16>(chance(rng, 30) ? 0x8000 : rng()));
            pair(m, PAIR(fn_sub_3DF100_003df100), args4(sx(el), sx(desc)), seed, "sub_3DF100 params");
            break;
        }
        case 4:
            pair(m, PAIR(fn_sub_3DF220_003df220), args4(sx(el), rng64(rng), sx(rng() % 3), rng64(rng)), seed, "sub_3DF220 start",
                 {{GPR_T0, sx(rng() % 360)}, {GPR_T1, rng64(rng)}});
            break;
        case 5:
            pair(m, PAIR(fn_sub_3DEE80_003dee80), args4(sx(e.holder), rng64(rng), sx(rng() % 3), rng64(rng)), seed, "sub_3DEE80 add",
                 {{GPR_T0, sx(rng() % 360)}, {GPR_T1, rng64(rng)}});
            break;
        case 6: pair(m, PAIR(fn_sub_3DED70_003ded70), args4(sx(e.holder)), seed, "sub_3DED70 remove filtered"); break;
        }
    }
}

// A list-menu record (fclCombineList.c): +4 kind, +12 slots, +16 selected count, +20 the command window object
// (its row list: rows whose payload +28 is the row record {+8 persona, +12 the 84-byte result, +96 elements}),
// +24 the selected array, +284 the stock list, +428 elements.
struct ListMenu {
    u32 list, win;
    std::vector<u32> rows;
};
// An element list record of the other kind ({+0 the list object}, sub_3DFEB0's: the list menu's +428 and the row
// records' +96, walked by sub_3E0680 / sub_3E0650 / sub_3DFF00), with n nodes (mostly none: a node makes sub_3E0680
// call the row text builders, which the test build leaves out).
u32 element_record(World& w, unsigned n) {
    Machine& m = w.m;
    const u32 rec = w.alloc(16), obj = w.alloc(40 + 8);
    w32(m, rec, obj);
    w32(m, obj + 20, kRet0);
    w32(m, obj + 24, kRet0);
    w32(m, obj + 28, kRet0);
    w32(m, obj + 32, 48);
    w32(m, obj + 36, obj + 40);
    u32 prev = 0;
    for (unsigned k = 0; k < n; ++k) {
        const u32 node = w.alloc(24 + 64);
        w32(m, node + 20, node + 24);
        w32(m, node + 12, prev);
        if (prev) w32(m, prev + 16, node);
        else w32(m, obj + 4, node);
        w32(m, obj + 8, node);
        prev = node;
    }
    w16(m, obj + 16, static_cast<u16>(n));
    return rec;
}
ListMenu list_menu(World& w, unsigned nrows) {
    Machine& m = w.m;
    ListMenu L;
    L.list = w.alloc(448);
    const u32 sel = w.alloc(32);
    const unsigned slots = 2 + w.rng() % 5;
    std::vector<u32> ps = w.personas_for(nrows, -1);
    w32(m, L.list + 4, w.rng() % 5);
    w32(m, L.list + 12, chance(w.rng, 90) ? slots : w.rng() % 12);
    w32(m, L.list + 16, w.rng() % (slots + 1));
    w32(m, L.list + 24, sel);
    for (unsigned k = 0; k < slots; ++k) w32(m, sel + 4 * k, chance(w.rng, 70) && !ps.empty() ? ps[w.rng() % ps.size()] : 0);
    const u32 st = w.stock(ps);
    std::memcpy(m.at(L.list + 284), m.at(st), 144);
    // the window object: a list object whose rows are nodes
    L.win = w.alloc(40 + 72);
    w32(m, L.win + 20, kRet0);  // the list object's callbacks (insert / remove / filter)
    w32(m, L.win + 24, kRet0);
    w32(m, L.win + 28, kRet0);
    w32(m, L.win + 32, 40 + 72);
    w32(m, L.win + 36, L.win + 40);
    w32(m, L.win + 40 + 68, L.list);  // payload +68: the owner list (sub_3DB5E0 / sub_3DC210)
    for (u32 k = 48; k <= 64; k += 4) w32(m, L.win + 40 + k, kRet0);  // the window's draw / update / input callbacks
    w32(m, L.list + 20, L.win);
    std::vector<u32> nodes;
    for (unsigned k = 0; k < nrows; ++k) {
        const u32 node = w.alloc(24 + 32), rec = w.alloc(112);
        w32(m, node + 20, node + 24);
        w32(m, node + 24 + 28, rec);
        w32(m, rec + 8, ps[k]);
        w32(m, rec + 96, element_record(w, chance(w.rng, 10) ? 1 : 0));
        nodes.push_back(node);
        L.rows.push_back(rec);
    }
    for (unsigned k = 0; k < nrows; ++k) w32(m, nodes[k] + 16, k + 1 < nrows ? nodes[k + 1] : 0);
    w32(m, L.win + 4, nrows ? nodes.front() : 0);
    w32(m, L.list + 428, element_record(w, chance(w.rng, 10) ? 1 : 0));
    return L;
}

TEST_CASE("game(fusion): the list menu functions equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 600; ++i) {
        const u32 seed = seed_of(i, 0x99u);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const ListMenu L = list_menu(w, 1 + rng() % 8);
        switch (i % 10) {
        case 0: pair(m, PAIR(fn_sub_3DA3E0_003da3e0), args4(sx(chance(rng, 95) ? L.list : 0), reg_of(rng() % 8, rng)), seed, "sub_3DA3E0 selected"); break;
        case 1: {
            const u32 p = chance(rng, 60) ? r32(m, r32(m, L.list + 24) + 4 * (rng() % 2)) : L.rows.empty() ? 0 : r32(m, L.rows[0] + 8);
            pair(m, PAIR(fn_sub_3DA470_003da470), args4(sx(chance(rng, 95) ? L.list : 0), sx(p)), seed, "sub_3DA470 is selected");
            break;
        }
        case 2: pair(m, PAIR(fn_sub_3DA570_003da570), args4(sx(L.list)), seed, "sub_3DA570 preview all"); break;
        case 3: pair(m, PAIR(fn_sub_3DA2A0_003da2a0), args4(sx(L.list)), seed, "sub_3DA2A0 mark triangle"); break;
        case 4: {
            // the owner chain of sub_3DEB20: list+20 -> +12 -> +20 -> +28 -> words at +108
            const u32 a = w.alloc(32), b = w.alloc(32), c = w.alloc(160);
            w32(m, L.win + 12, a);
            w32(m, a + 20, b);
            w32(m, b + 28, c);
            for (u32 k = 0; k < 12; ++k) w32(m, c + 108 + 4 * k, rng());
            pair(m, PAIR(fn_sub_3DEB20_003deb20), args4(sx(L.list)), seed, "sub_3DEB20 copy selection");
            break;
        }
        case 5: pair(m, PAIR(fn_sub_3DA3A0_003da3a0), args4(sx(L.list)), seed, "sub_3DA3A0 free"); break;
        case 6: pair(m, PAIR(fn_sub_3DB5E0_003db5e0), args4(sx(L.win)), seed, "sub_3DB5E0 remove filtered"); break;
        case 7: {
            const u32 row = w.alloc(24 + 32);
            w32(m, row + 20, row + 24);
            w32(m, row + 24 + 28, L.rows.empty() ? w.alloc(112) : L.rows[0]);
            pair(m, PAIR(fn_sub_3D9C90_003d9c90), args4(kUnused, sx(row)), seed, "sub_3D9C90 row free");
            break;
        }
        case 8: pair(m, PAIR(fn_sub_3DEB80_003deb80), args4(kUnused, kUnused, kUnused, sx(L.win)), seed, "sub_3DEB80 refresh"); break;
        case 9: pair(m, PAIR(fn_sub_3DC210_003dc210), args4(kUnused, kUnused, kUnused, sx(L.win)), seed, "sub_3DC210 refresh 2"); break;
        }
    }
    // the draw / row callbacks and the element list creator (their deep callees stop the runs where they are not emitted)
    for (int i = 0; i < 90; ++i) {
        const u32 seed = seed_of(i, 0xAAu);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const ListMenu L = list_menu(w, 1 + rng() % 4);
        switch (i % 3) {
        case 0: pair(m, PAIR(fn_sub_3DB580_003db580), args4(sx(chance(rng, 70) ? L.list : 0)), seed, "sub_3DB580 draw"); break;
        case 1: {
            const u32 node = w.alloc(24 + 32);
            w32(m, node + 20, node + 24);
            w32(m, node + 24 + 28, L.rows[0]);
            w32(m, L.win + 12, chance(rng, 50) ? node : 0);
            pair(m, PAIR(fn_sub_3DEC00_003dec00), args4(sx(rng() % 640), sx(rng() % 448), sx(rng() % 256), sx(L.win)), seed, "sub_3DEC00 draw row",
                 {{GPR_T0, sx(node)}});
            break;
        }
        case 2: pair(m, PAIR(fn_sub_3DECD0_003decd0), args4(sx(chance(rng, 90) ? L.list : 0)), seed, "sub_3DECD0 elem create"); break;
        }
    }
}

// =====================================================================================================================
// The real Velvet Room: the fusion route's snapshot at vblank 5000 (the fusion menu open, the hero holding personas 1
// and 46) and its result at the route's gate point (fusion_ref_6300: the hero holds persona 14, Lv 3)
// =====================================================================================================================

// The machine of the snapshot, with the World allocator but the snapshot's own game state (flags, hero, RpRandom).
bool vr_machine(Machine& m, std::vector<u8>& snap) {
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF: " << std::string(err));
        return false;
    }
    snap = read_snapshot(kVrSnapshot);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: no snapshot extracted/_ours/" << kVrSnapshot << " (the fusion route, reference mode, vblank 5000)");
        return false;
    }
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(m);
    g_snapshot_base = true;
    return true;
}
void restore_game_state(Machine& m, const std::vector<u8>& snap) {
    const std::pair<u32, u32> regions[] = {{kFlagWords, 176 * 4}, {kHeroUnit, 60},   {kHeroMaxWord, 4},
                                           {kHeroSlots, 12 * 52}, {kGp - 17784u, 4}, {kRandBase, 16}};
    for (const auto& [va, len] : regions) copy_from_snapshot(m, snap, va, len);
}
std::vector<u32> hero_ids(const Machine& m) {
    std::vector<u32> ids;
    for (u32 s = 0; s < 12; ++s)
        if (r16(m, kHeroSlots + 52 * s) & 1) ids.push_back(r16(m, kHeroSlots + 52 * s + 2));
    return ids;
}

TEST_CASE("game(fusion): the real fusion of the fusion route equals the recompiled bodies and the route's result") {
    Machine m;
    std::vector<u8> snap;
    if (!vr_machine(m, snap)) return;
    std::mt19937 rng{0x5000};
    World w(m, rng);
    restore_game_state(m, snap);
    Host h{m};
    const std::vector<u32> held = hero_ids(m);
    MESSAGE(std::string(kVrSnapshot) << ": the hero holds " << held.size() << " personas");
    REQUIRE(held.size() == 2);
    CHECK(held[0] == 1);
    CHECK(held[1] == 46);

    // the stock list the menu builds from the hero's personas
    const u32 stock = w.alloc(144);
    const Result built = pair(m, PAIR(fn_sub_3D5CD0_003d5cd0), args4(sx(stock)), 1, "real: sub_3D5CD0 build stock");
    REQUIRE(built.v0 == 2);
    const u32 p0 = r32(m, stock + 4), p1 = r32(m, stock + 12 + 4);
    CHECK(r16(m, p0 + 2) == 1);
    CHECK(r16(m, p1 + 2) == 46);

    // the normal fusion the route makes: Orpheus (1, Fool) x Pixie (46, Lovers) -> 14, the host rules agree, and the
    // route's later snapshot holds exactly that persona
    const u32 out = w.alloc(52);
    const Result r = pair(m, PAIR(fn_sub_3D64A0_003d64a0), args4(sx(out), sx(1), sx(46)), 2, "real: sub_3D64A0 normal");
    CHECK(r.v0 == 1);
    CHECK(r16(m, out + 2) == 14);
    const auto [code, id] = h.normal(1, 46);
    CHECK(code == 1);
    CHECK(id == 14);
    const std::vector<u8> after = read_snapshot(kAfterSnapshot);
    if (after.size() == EEMemory::kMainRamSize) {
        u16 first;
        std::memcpy(&first, after.data() + kHeroSlots + 2, 2);
        CHECK(first == 14);  // the persona the route's fusion produced
        CHECK(after[kHeroSlots + 4] == 3);
    }
    CHECK(h.t.level(14) == 3);  // (2 + 2) / 2 + 1 = 3: the lowest persona of the arcana at Lv >= 3 is 14's base level

    // the preview the menu shows (sub_3D6AE0: the fused persona, the inheritance through the stand-in heap, the deltas)
    const u32 preview = w.alloc(84);
    pair(m, PAIR(fn_sub_3D6AE0_003d6ae0), args4(sx(preview), sx(0), sx(w.ptrs({p0, p1}))), 3, "real: sub_3D6AE0 preview");
    CHECK(r16(m, preview + 6) == 14);
    CHECK(r8(m, preview + 8) == 3);
    // the skill inheritance on its own, and the partner masks of the two rows
    pair(m, PAIR(fn_sub_3D74F0_003d74f0), args4(sx(w.persona(14)), sx(w.ptrs({p0, p1})), sx(2)), 4, "real: sub_3D74F0 inherit");
    const Result m0 = pair(m, PAIR(fn_sub_3D8260_003d8260), args4(sx(stock), sx(0)), 5, "real: sub_3D8260 partners");
    CHECK(m0.v0 == 2u);  // row 0 fuses with row 1
    const Result m1 = pair(m, PAIR(fn_sub_3D8260_003d8260), args4(sx(stock), sx(1)), 6, "real: sub_3D8260 partners");
    CHECK(m1.v0 == 1u);
    for (u32 k = 0; k < 2; ++k)
        pair(m, PAIR(fn_sub_3D5DC0_003d5dc0), args4(sx(held[k])), 7 + k, "real: sub_3D5DC0 rank letter");

    // the list menu over the real stock (the command window and the rows through the stand-in heap)
    pair(m, PAIR(fn_sub_3DA0C0_003da0c0), args4(sx(stock), sx(0)), 9, "real: sub_3DA0C0 list create");
    pair(m, PAIR(fn_sub_3DE290_003de290), args4(sx(stock), sx(2)), 10, "real: sub_3DE290 recipe list create");

    // the commit: the ingredients leave the hero's list, the result takes a slot (the route's later state: 14 alone)
    pair(m, PAIR(fn_sub_3D8080_003d8080), args4(sx(preview), sx(w.ptrs({p0, p1})), sx(2)), 11, "real: sub_3D8080 commit");
    const std::vector<u32> now = hero_ids(m);
    CHECK(std::find(now.begin(), now.end(), 14u) != now.end());

    // the rules over the real flags
    restore_game_state(m, snap);
    for (u32 c = 0; c < 5; ++c) {
        pair(m, PAIR(fn_sub_3D84C0_003d84c0), args4(kUnused, sx(c)), 20 + c, "real: sub_3D84C0");
        pair(m, PAIR(fn_sub_3D8630_003d8630), args4(sx(stock), sx(c)), 30 + c, "real: sub_3D8630");
    }
    for (u32 pid = 0; pid < 192; pid += 3) {
        const Result a = pair(m, PAIR(fn_sub_3D5BB0_003d5bb0), args4(sx(pid)), 100 + pid, "real: sub_3D5BB0");
        CHECK(a.v0 == (h.available(pid) ? 1u : 0u));
    }
    for (u32 arcana = 1; arcana <= 21; ++arcana) {
        const u32 ex = w.exclude({});
        const u32 level = 1 + (arcana * 7) % 90;
        std::vector<u16> excl(12, 0);
        for (u32 k = 0; k < 12; ++k) excl[k] = r16(m, ex + 2 * k);
        const Result up = pair(m, PAIR(fn_sub_3D7AC0_003d7ac0), args4(sx(arcana), sx(level), sx(ex)), 400 + arcana, "real: sub_3D7AC0");
        CHECK(up.v0 == h.find(arcana, level, excl, true));
        const Result dn = pair(m, PAIR(fn_sub_3D7DA0_003d7da0), args4(sx(arcana), sx(level), sx(ex)), 500 + arcana, "real: sub_3D7DA0");
        CHECK(dn.v0 == h.find(arcana, level, excl, false));
    }
}

TEST_CASE("game(fusion): the fclCombine root, tasks and menu steps on the real Velvet Room") {
    Machine m;
    std::vector<u8> snap;
    if (!vr_machine(m, snap)) return;
    std::mt19937 rng{0x5001};
    World w(m, rng);
    restore_game_state(m, snap);
    const u32 root = r32(m, kRoot);
    REQUIRE(root != 0);
    const u32 payload = r32(m, r32(m, root + 36) + 12);  // nmObjPayloadWord12(root): the 224-byte work record
    MESSAGE(std::string(kVrSnapshot) << ": fclCombine root " << hex64(root) << ", work record " << hex64(payload));
    // root present: the create step returns 0; the per-frame updates and the steps that read the work record
    CHECK(pair(m, PAIR(fn_sub_3D04D0_003d04d0), args4(), 1, "real: sub_3D04D0 create root").v0 == 0);
    pair(m, PAIR(fn_sub_3D04B0_003d04b0), args4(), 2, "real: sub_3D04B0 active");
    pair(m, PAIR(fn_fclCombine_UpdateCombineDrawTask_003d0400), args4(), 3, "real: fclCombine draw task");
    pair(m, PAIR(fn_fclCombine_UpdateCombineDraw2Task_003d0470), args4(), 4, "real: fclCombine draw2 task");
    pair(m, PAIR(fn_sub_3D5420_003d5420), args4(), 5, "real: sub_3D5420 bg start");
    pair(m, PAIR(fn_sub_3D54A0_003d54a0), args4(), 6, "real: sub_3D54A0 bg done");
    {  // sub_3D4CD0 reads a step record whose +924 is the list menu: one over a list of the real stock
        const u32 stock = w.alloc(144);
        pair(m, PAIR(fn_sub_3D5CD0_003d5cd0), args4(sx(stock)), 70, "real: sub_3D5CD0 build stock");
        const u32 list = static_cast<u32>(pair(m, PAIR(fn_sub_3DA0C0_003da0c0), args4(sx(stock), sx(0)), 71, "real: sub_3DA0C0 list create").v0);
        const u32 rec = w.alloc(1024);
        w32(m, rec, rng() & 3);
        w32(m, rec + 8, 2);
        w32(m, rec + 924, list);
        pair(m, PAIR(fn_sub_3D4CD0_003d4cd0), args4(sx(rec), sx(w.alloc(24))), 7, "real: sub_3D4CD0 selection");
    }
    pair(m, PAIR(fn_sub_3D2F00_003d2f00), args4(), 8, "real: sub_3D2F00 root list start");
    // the step callbacks on a step node whose payload area is a fresh record
    for (int i = 0; i < 40; ++i) {
        const u32 node = w.alloc(64), rec = w.alloc(1024);
        w32(m, node + 20, rec);
        const u32 area = w.alloc(64);
        w32(m, rec + 40, area);
        w32(m, area + 16, 0);
        w32(m, area + 20, 0);
        w32(m, area + 924, 0);
        const u32 seed = seed_of(i, 0x5002u);
        switch (i % 8) {
        case 0: pair(m, PAIR(fn_sub_3D2D80_003d2d80), args4(sx(root), sx(node)), seed, "real: sub_3D2D80 step"); break;
        case 1: pair(m, PAIR(fn_sub_3D3B00_003d3b00), args4(sx(root), sx(node)), seed, "real: sub_3D3B00 step"); break;
        case 2: pair(m, PAIR(fn_sub_3D3CD0_003d3cd0), args4(sx(root), sx(node)), seed, "real: sub_3D3CD0 step"); break;
        case 3: pair(m, PAIR(fn_sub_3D4C80_003d4c80), args4(sx(root), sx(node)), seed, "real: sub_3D4C80 step"); break;
        case 4: pair(m, PAIR(fn_sub_3D53E0_003d53e0), args4(sx(root), sx(node)), seed, "real: sub_3D53E0 step"); break;
        case 5: pair(m, PAIR(fn_sub_3D4F30_003d4f30), args4(sx(root), sx(node)), seed, "real: sub_3D4F30 step"); break;
        case 6: pair(m, PAIR(fn_sub_3D4F90_003d4f90), args4(sx(root), sx(node)), seed, "real: sub_3D4F90 step"); break;
        case 7: pair(m, PAIR(fn_sub_3DEDA0_003deda0), args4(sx(element_list(w, rng() % 4).holder)), seed, "sub_3DEDA0 elem draw"); break;
        }
    }
    // one frame of the root sequence, then the teardown and a fresh root with its three tasks
    pair(m, PAIR(fn_fclCombine_UpdateCombineTask_003d03c0), args4(), 9, "real: fclCombine task");
    pair(m, PAIR(fn_sub_3D0560_003d0560), args4(), 10, "real: sub_3D0560 destroy root");
    CHECK(r32(m, kRoot) == 0);
    pair(m, PAIR(fn_sub_3D02F0_003d02f0), args4(), 11, "real: sub_3D02F0 start (tasks + root)");
    CHECK(r32(m, kRoot) != 0);
    pair(m, PAIR(fn_sub_3D0610_003d0610), args4(), 12, "real: sub_3D0610 update root");
}

TEST_CASE("game(fusion): the list-menu builders and panels on random stocks equal their recompiled bodies") {
    Machine m;
    if (!real_machine(m)) return;
    for (int i = 0; i < 300; ++i) {
        const u32 seed = seed_of(i, 0xBBu);
        std::mt19937 rng{seed};
        reset(m);
        World w(m, rng);
        const unsigned n = 1 + rng() % 12;
        const u32 stock = w.stock(w.personas_for(n, chance(rng, 40) ? static_cast<int>(rng() % 5) : -1));
        const ListMenu L = list_menu(w, 1 + rng() % 6);
        const u32 panel = w.alloc(64);
        w32(m, L.list + 112, panel);
        w32(m, L.list, rng() & 0x3F);
        switch (i % 9) {
        case 0: pair(m, PAIR(fn_sub_3DA0C0_003da0c0), args4(sx(stock), sx(chance(rng, 90) ? rng() % 2 : 2)), seed, "sub_3DA0C0 list create"); break;
        case 1: pair(m, PAIR(fn_sub_3DE290_003de290), args4(sx(stock), sx(chance(rng, 90) ? 2 + rng() % 3 : rng() % 2)), seed, "sub_3DE290 recipe list"); break;
        case 2: pair(m, PAIR(fn_sub_3DD9E0_003dd9e0), args4(sx(L.list)), seed, "sub_3DD9E0 status open"); break;
        case 3: {
            w16(m, 0x7E094Eu, static_cast<u16>(chance(rng, 50) ? 0x20 : rng() & ~0x20u));  // gPadFlags
            w16(m, 0x7E0958u, static_cast<u16>(chance(rng, 20) ? 0x20 : 0));
            const bool cancel = ((r16(m, 0x7E094Eu) | r16(m, 0x7E0958u)) & 0x20) != 0;
            const u32 flags = r32(m, L.list);
            const Result r = pair(m, PAIR(fn_sub_3DDA80_003dda80), args4(sx(L.list)), seed, "sub_3DDA80 status input");
            if (!r.fatal) {
                CHECK(r.v0 == (cancel ? 1u : 0u));  // the cancel button (0x20) closes the panel: flag bit 5 cleared
                CHECK(r32(m, L.list) == (cancel ? flags & ~0x20u : flags));
            }
            break;
        }
        case 4: pair(m, PAIR(fn_sub_3DDB00_003ddb00), args4(sx(L.list)), seed, "sub_3DDB00 status draw"); break;
        case 5: {
            const u32 pr = L.list + 116;
            w32(m, pr, rng() & 0xF);
            w32(m, pr + 12, rng() % 3);
            w32(m, pr + 20, rng() % 3);
            w32(m, pr + 16, r32(m, L.list + 24));
            w32(m, pr + 160, panel);
            pair(m, PAIR(fn_sub_3DE160_003de160), args4(sx(pr)), seed, "sub_3DE160 persona panel");
            break;
        }
        case 6: {
            const u32 node = w.alloc(24 + 32);
            w32(m, node + 20, node + 24);
            w32(m, node + 24 + 28, L.rows[0]);
            w32(m, L.win + 12, chance(rng, 50) ? node : 0);
            pair(m, PAIR(fn_sub_3DD800_003dd800), args4(sx(rng() % 640), sx(rng() % 448), sx(rng() % 256), sx(L.win)), seed,
                 "sub_3DD800 row draw", {{GPR_T0, sx(node)}});
            break;
        }
        case 7: pair(m, PAIR(fn_sub_3D9CC0_003d9cc0), args4(sx(L.list)), seed, "sub_3D9CC0 rows"); break;
        case 8: pair(m, PAIR(fn_sub_3D9EA0_003d9ea0), args4(sx(L.list)), seed, "sub_3D9EA0 recipe rows"); break;
        }
    }
}


TEST_CASE("game(fusion): pair count") {
    MESSAGE("fusion pairs run: " << g_pairs);
    std::string s;
    for (const auto& [k, v] : g_tally)
        if (v.second) s += k + " " + std::to_string(v.second) + "/" + std::to_string(v.first) + "; ";
    MESSAGE("stopped at a callee left out of the test build (label fatal/pairs): " << s);
    for (const auto& [k, v] : g_stop) MESSAGE("  first stop of " << k << ": " << v);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
