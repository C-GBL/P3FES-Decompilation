// Phase 5 pair tests for the rest of the datCalc.c battle band (game/src/battle/battle_rest.cpp): every hand-written
// function and the recompiled body it replaces run on identical guest machines on randomised battle states. Beyond
// pair_harness.h's Outcome (result, callee-saved GPRs, the arena, the caller's live stack, cycles, check points) each
// pair compares all 32 FPRs, FCR31, HI/LO, the game data window [0x7C0000, 0x9B0000) after both runs (RNG
// state, flags, units, party records; restored between the runs so both consume one random stream) and the dead
// stack 8 KiB below $sp: the hand versions write the original prologue spills, keep the s-registers and $ra of the
// original at every call, so the callees' frames -- among them non-leaf recompiled ones (datScriptCalc's formula
// functions, K_Assert's callers) -- must hold the same bytes. The other caller-saved GPRs are counted, not required
// (battle_rest.cpp's header comment).
//
// The battle state follows test_battle_calc.cpp: the eight battle/*.TBL files loaded the way btlTableLoad lays them
// out (real SKILL/UNIT/PERSONA/AICALC/MSG data from the extracted tree; random sections when it is absent), random
// weapon / accessory tables, a random party, random unit records, random flag words.
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/battle_rest.h"

#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
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
P3FES_DECL_PAIR(fn_sub_302380_00302380)
P3FES_DECL_PAIR(fn_sub_302C50_00302c50)
P3FES_DECL_PAIR(fn_sub_302D40_00302d40)
P3FES_DECL_PAIR(fn_sub_302F50_00302f50)
P3FES_DECL_PAIR(fn_sub_305970_00305970)
P3FES_DECL_PAIR(fn_sub_306020_00306020)
P3FES_DECL_PAIR(fn_sub_306510_00306510)
P3FES_DECL_PAIR(fn_sub_306610_00306610)
P3FES_DECL_PAIR(fn_sub_3068D0_003068d0)
P3FES_DECL_PAIR(fn_sub_306BC0_00306bc0)
P3FES_DECL_PAIR(fn_sub_306D90_00306d90)
P3FES_DECL_PAIR(fn_sub_3083F0_003083f0)
P3FES_DECL_PAIR(fn_sub_3086F0_003086f0)
P3FES_DECL_PAIR(fn_sub_308A80_00308a80)
P3FES_DECL_PAIR(fn_sub_30A740_0030a740)
P3FES_DECL_PAIR(fn_sub_30AF00_0030af00)
P3FES_DECL_PAIR(fn_sub_30B130_0030b130)
P3FES_DECL_PAIR(fn_sub_30B210_0030b210)
P3FES_DECL_PAIR(fn_sub_30B640_0030b640)
P3FES_DECL_PAIR(fn_sub_30B9A0_0030b9a0)
P3FES_DECL_PAIR(fn_datGetSkillName_0030bb40)
P3FES_DECL_PAIR(fn_datGetArcanaName_0030bbb0)
P3FES_DECL_PAIR(fn_sub_30BC20_0030bc20)
P3FES_DECL_PAIR(fn_sub_30BC50_0030bc50)
P3FES_DECL_PAIR(fn_sub_30BDE0_0030bde0)
P3FES_DECL_PAIR(fn_sub_30C0C0_0030c0c0)
P3FES_DECL_PAIR(fn_sub_30C220_0030c220)
P3FES_DECL_PAIR(fn_sub_30C2A0_0030c2a0)
P3FES_DECL_PAIR(fn_sub_30C3A0_0030c3a0)
P3FES_DECL_PAIR(fn_datCalcRestorePartyAll_0030c440)
P3FES_DECL_PAIR(fn_sub_30C490_0030c490)
P3FES_DECL_PAIR(fn_datUnitEcAddEnemy_002ff540)
P3FES_DECL_PAIR(fn_sub_2FFB00_002ffb00)
P3FES_DECL_PAIR(fn_sub_3005A0_003005a0)
P3FES_DECL_PAIR(fn_sub_300700_00300700)
P3FES_DECL_PAIR(fn_sub_300870_00300870)
P3FES_DECL_PAIR(fn_sub_300E90_00300e90)
P3FES_DECL_PAIR(fn_sub_301CA0_00301ca0)
P3FES_DECL_PAIR(fn_sub_30FDC0_0030fdc0)
P3FES_DECL_PAIR(fn_sub_3111C0_003111c0)
P3FES_DECL_PAIR(fn_sub_3112E0_003112e0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::btl;

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout of the battle state ------------------------------------------------------------------------
constexpr u32 kUnits = kArena + 0x100;      // eight 64-byte unit records in the arena (compared by the harness)
constexpr u32 kUnitStride = 64;
constexpr u32 kOuts = kArena + 0x40;        // result words for the pointer arguments (in the arena)
constexpr u32 kTables = 0x01900000u;        // the .TBL sections, as btlTableLoad lays them out in its arena
constexpr u32 kWeapons = 0x01880000u;       // 1,000 x 40-byte weapon records (pointer gp-0x4D0C = 0x7CDFE4)
constexpr u32 kAccessories = 0x018A0000u;   // 1,000 x 36-byte accessory records (pointer gp-0x4D1C = 0x7CDFD4)
constexpr u32 kHeroInventory = 0x018C0000u; // the hero's 20-byte item records (pointer 0x836794)
constexpr u32 kSynthEnemies = 0x018D0000u;  // a synthetic EnemyRecord[336] with skill-pool skills
constexpr u32 kDataLo = 0x007C0000u, kDataHi = 0x009B0000u;  // the .data/.bss part these touch, compared and restored per pair
constexpr u32 kTableRecords = 0x00692D40u;  // off_692D40: 8 x 168-byte {name, name_F, {u32* dst, u32 size} x 20}
constexpr u32 kDeadBytes = 0x2000u;         // the dead stack compared (and scrubbed) per run
constexpr u32 kFlagWords = 0x83A21Cu;       // datGetFlag's u32[176]
constexpr u32 kNoCostMode = 0x7CDFA4u;      // the word sub_17D800 returns (gp-19788)
constexpr u32 kStockCurrent = 0x836BA8u;    // s16: the hero's current stock slot (sub_1752B0)
constexpr u32 kStock = 0x836BACu;           // the hero's 52-byte persona stock slots: u16 +0 bit 0 used, u16 +2 persona
constexpr u32 kRandState = 0x957BF0u;       // effMiscRand's four state words (datCalcRand's source)

constexpr u32 kWeaponTablePtr = 0x7CDFE4u;
constexpr u32 kAccessoryTablePtr = 0x7CDFD4u;

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 load16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) { return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1)); }
template <std::size_t N>
u32 pick(std::mt19937& rng, const u16 (&pool)[N]) { return pool[rng() % N]; }

// The skill ids the functions test (passives, boosts, counters, costs, the mix-raid band 192..197) and the
// equipment effects (49..69 weapon statuses, 67..69, 100..102, 170..172).
constexpr u16 kSkillPool[] = {192, 193, 194, 195, 196, 197, 438, 503, 504, 536, 561, 562, 565, 566, 571, 572, 577, 578,
                              580, 581, 587, 588, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 609, 464, 470,
                              480, 500, 520, 545, 550, 1, 2, 10, 50, 100, 150, 200, 300, 400};
constexpr u16 kEffectPool[] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 100, 101,
                               102, 170, 171, 172, 0, 30, 90, 120};
constexpr u16 kWeaponMasks[] = {0x8000, 0x80, 0x4000, 0x40, 0x2000, 0x20, 0x1000, 0x10, 0x800, 0x8, 0x400, 0x4, 0x200, 0x2, 0x100, 0x1, 0x3};

// A .TBL file of the extracted tree: { u32 size, bytes } sections, each at the next multiple of 16.
std::vector<std::vector<u8>> read_tbl(const std::string& name) {
    const std::filesystem::path path = std::filesystem::path(elf_path()).parent_path().parent_path() / "BTL" / "BATTLE" / name;
    std::ifstream in(path, std::ios::binary);
    std::vector<std::vector<u8>> sections;
    if (!in) return sections;
    std::vector<u8> file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::size_t off = 0;
    while (off + 4 <= file.size()) {
        u32 n;
        std::memcpy(&n, file.data() + off, 4);
        if (off + 4 + n > file.size()) break;
        sections.emplace_back(file.begin() + static_cast<std::ptrdiff_t>(off + 4), file.begin() + static_cast<std::ptrdiff_t>(off + 4 + n));
        off = (off + 4 + n + 15) & ~static_cast<std::size_t>(15);
    }
    return sections;
}

struct Extra {
    std::array<u32, 32> fpr{};
    u32 fcr31 = 0;
    u64 hi = 0, lo = 0;
    std::array<u64, 32> gpr{};
    std::vector<u8> dead;
};

struct World {
    Machine m;
    std::mt19937 rng;
    bool real = false;
    u32 real_enemy_table = 0;
    u64 pairs = 0;
    u64 scratch_diffs = 0;  // pairs whose caller-saved GPRs other than $v0 differ (reported, not required)
    u64 faulted = 0;        // pairs where both bodies stopped at the same fault (an impossible id of the random world)
    bool with_t_args = false;
    std::array<u64, 4> t_args{};

    explicit World(u32 seed) : rng(seed) {}

    const char* load() {
        if (const char* err = m.load_elf(elf_path())) return err;
        install_tables();
        randomize_items();
        randomize_party();
        randomize_flags();
        return nullptr;
    }

    void install_tables() {
        u32 offset = 0;
        int found = 0;
        for (u32 r = 0; r < 8; ++r) {
            const u32 rec = kTableRecords + 168 * r;
            const std::string name = m.str(load32(m, rec));
            const std::string file = name.substr(name.find('/') + 1);
            const std::vector<std::vector<u8>> secs = read_tbl(file);
            if (!secs.empty()) ++found;
            for (u32 k = 0; k < 20; ++k) {
                const u32 dst = load32(m, rec + 8 + 8 * k);
                if (dst == 0) break;
                const u32 va = kTables + offset;
                u32 size;
                if (k < secs.size()) {
                    size = static_cast<u32>(secs[k].size());
                    std::memcpy(m.at(va), secs[k].data(), size);
                } else {
                    size = load32(m, rec + 12 + 8 * k);
                    if (size == 0) size = 0x400;
                    fill_random(m, va, size, rng);
                }
                store32(m, dst, va);
                offset += (size + 15) & ~15u;
            }
        }
        fill_random(m, kTables + offset, 0x4000, rng);
        real = found == 8;
        real_enemy_table = load32(m, kUnitTablePtr);
        std::memcpy(m.at(kSynthEnemies), m.at(real_enemy_table), kEnemyCount * kEnemyRecordSize);
        for (u32 id = 0; id < kEnemyCount; ++id)
            for (u32 s = 0; s < 8; ++s) store16(m, kSynthEnemies + id * kEnemyRecordSize + 14 + 2 * s, static_cast<u16>(pick(rng, kSkillPool)));
        fill_random(m, kSynthEnemies + kEnemyCount * kEnemyRecordSize, 0x2000, rng);
    }
    void use_enemy_table(bool synthetic) { store32(m, kUnitTablePtr, synthetic ? kSynthEnemies : real_enemy_table); }

    void randomize_items() {
        fill_random(m, kWeapons, 1000 * 40, rng);
        for (u32 i = 0; i < 1000; ++i) {
            store32(m, kWeapons + 40 * i + 4, rng() % 8 ? kWeaponMasks[rng() % std::size(kWeaponMasks)] : rng());
            store16(m, kWeapons + 40 * i + 30, static_cast<u16>(rng() % 6 ? rand_range(rng, -1, 18) : static_cast<s32>(rng())));
        }
        fill_random(m, kAccessories, 1000 * 36, rng);
        for (u32 i = 0; i < 1000; ++i) store32(m, kAccessories + 36 * i + 28, pick(rng, kSkillPool));
        store32(m, kWeaponTablePtr, kWeapons);
        store32(m, kAccessoryTablePtr, kAccessories);
    }

    void randomize_party() {
        fill_random(m, 0x833F00u, 0x836E00u - 0x833F00u, rng);
        auto item = [&](u32 va, u32 slot) {
            const u32 id = slot == 0 ? rng() % 1000 : (slot == 3 ? 3000 + rng() % 1000 : rng() % 4000);
            store16(m, va, static_cast<u16>(rng() % 10 ? id : rng()));
            m.at(va + 9)[0] = static_cast<u8>(rng() % 8 ? pick(rng, kEffectPool) : rng());
        };
        for (u32 pc = 2; pc <= 10; ++pc) {
            const u32 base = 0x834010u + 868u * (pc - 2);
            for (u32 s = 0; s < 4; ++s) store16(m, base + 0x54 + 2 * s, static_cast<u16>(rng() % 12 ? s : static_cast<u32>(rand_range(rng, -1, 9))));
            for (u32 i = 0; i < 10; ++i) item(base + 0x5C + 20 * i, i < 4 ? i : rng() % 4);
            const u32 persona = base + 0xDC;
            store16(m, persona + 2, static_cast<u16>(rng() % 256));
            m.at(persona + 4)[0] = static_cast<u8>(rand_range(rng, 1, 99));
            for (u32 s = 0; s < 8; ++s) store16(m, persona + 12 + 2 * s, static_cast<u16>(pick(rng, kSkillPool)));
            store16(m, base + 0x4C, static_cast<u16>(rng() % 7));  // the condition
        }
        for (u32 s = 0; s < 4; ++s) store16(m, 0x83678Cu + 2 * s, static_cast<u16>(s));
        for (u32 pc = 2; pc <= 13; ++pc) store16(m, 0x834010u + 868u * (pc - 2) + 6, static_cast<u16>(pc));
        store16(m, 0x836226u, 1);
        store16(m, 0x83626Cu, static_cast<u16>(rng() % 7));
        store32(m, 0x836794u, kHeroInventory);
        store32(m, 0x836798u, kHeroInventory + 0x800);  // the hero's u16 table sub_170760 reads (pc 1)
        fill_random(m, kHeroInventory, 0x4000, rng);
        for (u32 i = 0; i < 16; ++i) item(kHeroInventory + 20 * i, i % 4);
    }

    // The flag words (datGetFlag / MT_Misc_BitChk), denser or sparser, and the no-cost mode word.
    void randomize_flags() {
        const u32 density = rng() % 3;
        for (u32 i = 0; i < 176; ++i) {
            u32 w = rng();
            if (density == 0) w &= rng();
            if (density == 2) w |= rng();
            store32(m, kFlagWords + 4 * i, w);
        }
        store32(m, kNoCostMode, rng() % 4 == 0 ? 1u : 0u);
        fill_random(m, kRandState, 16, rng);  // effMiscRand's state: zero in the image, and a zero state rolls 0 forever
    }

    u32 unit(unsigned slot, bool enemy) {
        const u32 va = kUnits + slot * kUnitStride;
        fill_random(m, va, kUnitStride, rng);
        u16 flags = load16(m, va);
        flags = enemy ? static_cast<u16>(flags | kUnitFlagEnemy) : static_cast<u16>(flags & ~kUnitFlagEnemy);
        if (rng() % 2) flags = static_cast<u16>(flags & ~0x570u);  // fewer of the blocking flags 0x10/0x20/0x40/0x100/0x400
        store16(m, va, flags);
        if (enemy) {
            store16(m, va + 2, static_cast<u16>(rng() % 20 ? rng() % kEnemyCount : rng() % 400));
            store16(m, va + 4, static_cast<u16>(rng() % 20 ? rng() % kEnemyCount : rng() % 400));
        } else {
            store16(m, va + 2, static_cast<u16>(rng() % 20 ? rand_range(rng, 1, 10) : rng() % 14));
        }
        constexpr u32 kStatuses[] = {0, 0, 0, 0, 8, 0x100000, 512, 2, 4, 64, 32, 0x100, 0x80000};
        store32(m, va + 0xC, kStatuses[rng() % std::size(kStatuses)] | (rng() % 4 == 0 ? (rng() & 0xFFF00000u) : 0u));
        if (rng() % 3 != 0) std::memset(m.at(va + 0x1C), 0, 9);
        return va;
    }

    u32 skill() { return rng() % 8 ? rng() % kSkillCount : (rng() % 2 ? rng() % 700 : rng()); }

    Outcome run1(Fn fn, const Args& args, u32 seed, Extra& x) {
        rt_test::HooksScope scope{&m.hooks};
        rt::bind_context(&m.ctx);
        std::mt19937 r{seed};
        m.fresh_context(args, r);
        if (with_t_args)
            for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = t_args[i];
        for (u32& f : m.ctx.fpr) f = r();
        m.ctx.fcr31 = r() & 0x0083C078u;
        const u64 c0 = m.ctx.cycles;
        const int k0 = m.hooks.checks;
        fn(m.ctx);
        Outcome o;
        o.v0 = m.ctx.gpr[GPR_V0].u64[0];
        const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
        for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
        o.cycles = m.ctx.cycles - c0;
        o.checks = m.hooks.checks - k0;
        o.arena = m.bytes(kArena, kArenaSize);
        o.live_stack = m.bytes(kSp, 0x100);
        x.dead = m.bytes(kSp - kDeadBytes, kDeadBytes);
        std::memset(m.at(kSp - kDeadBytes), 0, kDeadBytes);
        for (int i = 0; i < 32; ++i) x.fpr[i] = m.ctx.fpr[i];
        for (int i = 0; i < 32; ++i) x.gpr[i] = m.ctx.gpr[i].u64[0];
        x.fcr31 = m.ctx.fcr31;
        x.hi = m.ctx.hi.u64[0];
        x.lo = m.ctx.lo.u64[0];
        return o;
    }

    Pair pair(Fn hand, Fn recomp, const Args& args, const char* what) {
        char tag[200];
        std::snprintf(tag, sizeof tag, "%s a0=0x%llx a1=0x%llx a2=0x%llx a3=0x%llx", what, static_cast<unsigned long long>(args[0]),
                      static_cast<unsigned long long>(args[1]), static_cast<unsigned long long>(args[2]),
                      static_cast<unsigned long long>(args[3]));
        const std::string context = tag;
        INFO(context);
        const u32 seed = rng();
        // the window through a PairRange (write_tracker.h): only the pages written are copied and compared
        PairRange window(m.at(kDataLo), m.at(kDataHi));
        const std::vector<u8> arena = m.bytes(kArena, kArenaSize);
        Pair p;
        Extra xh, xr;
        const std::string fh = fault_of([&] { p.hand = run1(hand, args, seed, xh); });
        window.between();
        std::memcpy(m.at(kArena), arena.data(), arena.size());
        const std::string fr = fault_of([&] { p.recomp = run1(recomp, args, seed, xr); });
        if (!fh.empty() || !fr.empty()) {  // an impossible id of the random world: the original faults too
            CHECK(fh == fr);
            std::memset(m.at(kSp - kDeadBytes), 0, kDeadBytes);
            ++faulted;
            p.faulted = true;
            return p;
        }
        expect_same(p.hand, p.recomp, what);
        CHECK(xh.fpr == xr.fpr);
        CHECK(xh.fcr31 == xr.fcr31);
        CHECK(xh.hi == xr.hi);
        CHECK(xh.lo == xr.lo);
        CHECK(xh.dead == xr.dead);
        const bool same_data = window.first_difference() == window.size();
        CHECK(same_data);
        if (xh.gpr != xr.gpr) ++scratch_diffs;
        ++pairs;
        return p;
    }
};

#define LOAD_WORLD_OR_SKIP(w)                                                                                 \
    if (const char* err = (w).load()) {                                                                       \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// The signed nibble of buff slot k (the layout datCalcGetEffectLevel reads).
s32 nibble(const Machine& m, u32 unit, u32 k) {
    const u8 b = m.mem.main_ram()[unit + 0x1C + k / 2];
    const u32 n = (k & 1) ? (b >> 4) : (b & 0xF);
    return static_cast<s32>(n << 28) >> 28;
}

}  // namespace

TEST_CASE("game(battle_rest): the buff-slot functions equal their recompiled bodies") {
    World w{11u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    int found = 0, cleared = 0;
    for (int it = 0; it < 2500; ++it) {
        if (it % 500 == 0) w.randomize_party();
        const u32 unit = w.unit(it & 7, (rng() & 1) != 0);
        if (rng() % 2) {  // live buffs: random nibbles and counters, flags for the set ones
            for (u32 b = 0; b < 9; ++b) w.m.at(unit + 0x1C + b)[0] = static_cast<u8>(rng());
            for (u32 b = 0; b < 9; ++b) w.m.at(unit + 0x29 + b)[0] = static_cast<u8>(rng() % 3 ? rng() & 0x33 : rng());
        }
        const u32 mask = rng() % 4 ? (rng() & 0x07FFFFFFu) : (rng() % 2 ? 0x1000u | 0x2000u : rng());
        const u32 delta = rng() % 4 ? static_cast<u32>(rand_range(rng, -3, 3)) : rng();
        w.pair(PAIR(fn_sub_302380_00302380), Args{sx(unit), sx(mask), sx(delta)}, "datCalcApplyEffectMask");
        store32(w.m, unit + 24, rng() % 3 ? (rng() & 0x1FFFFFu) : 0u);
        w.pair(PAIR(fn_sub_302C50_00302c50), Args{sx(unit)}, "datCalcClearMaskedEffects");
        if (load32(w.m, unit + 24) == 0) ++cleared;
        w.pair(PAIR(fn_sub_302D40_00302d40), Args{sx(unit)}, "datCalcTickEffectTurns");
        Pair p = w.pair(PAIR(fn_sub_302F50_00302f50), Args{sx(unit)}, "datCalcFindExpiredEffect");
        const s64 slot = static_cast<s64>(p.hand.v0);
        CHECK((slot == -1 || (slot >= 0 && slot < 17 && slot != 11)));
        if (slot >= 0) {
            ++found;
            CHECK(nibble(w.m, unit, static_cast<u32>(slot)) != 0);  // documented rule: an expired slot has a level
        }
    }
    MESSAGE("buff pairs: " << w.pairs << ", expired found " << found << ", masks cleared " << cleared
                           << ", pairs with other scratch GPRs differing " << w.scratch_diffs);
    CHECK(found > 100);
    CHECK(cleared == 2500);
}

TEST_CASE("game(battle_rest): the status rolls equal their recompiled bodies") {
    World w{12u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u64, int> statuses;
    int formula = 0;
    for (int it = 0; it < 4000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 100 == 0) w.randomize_flags();
        w.use_enemy_table(it % 3 != 0);
        const u32 attacker = w.unit(it & 7, (rng() & 1) != 0);
        const u32 target = w.unit((it + 1 + rng() % 7) & 7, rng() % 3 != 0);
        u32 skill = w.skill();
        if (rng() % 3 == 0 && (skill & 0xFFFFu) < kSkillCount) {  // a status skill: kind +24 1/2/3, bits +28, rate +25
            const u32 rec = load32(w.m, kSkillTablePtr) + (skill & 0xFFFFu) * kSkillRecordSize;
            w.m.at(rec + 24)[0] = static_cast<u8>(rng() % 6 ? 1 + rng() % 3 : rng() % 5);
            w.m.at(rec + 25)[0] = static_cast<u8>(rng() % 4 ? rng() % 100 : 100 + rng() % 50);
            store32(w.m, rec + 28, rng() % 4 ? (1u << (rng() % 24)) | (rng() % 3 ? 0u : (1u << (rng() % 24))) : rng());
            w.m.at(rec + 36)[0] = static_cast<u8>(rng() % 4 ? 0 : 1);
        }
        Pair p = w.pair(PAIR(fn_sub_305970_00305970), Args{sx(skill), sx(attacker), sx(target)}, "datCalcRollStatus");
        ++statuses[p.hand.v0 != 0];
        if (p.hand.checks > 12) ++formula;
        const u32 hit = rng() % 3 ? 1u : rng() % 4;
        w.pair(PAIR(fn_sub_306020_00306020), Args{sx(skill), sx(attacker), sx(target), sx(hit)}, "datCalcRollWeaponStatus");
        w.pair(PAIR(fn_sub_306510_00306510), Args{sx(skill), sx(attacker), sx(target), sx(hit)}, "datCalcRollSkillStatus");
    }
    MESSAGE("status pairs: " << w.pairs << ", inflicted " << statuses[1] << ", none " << statuses[0] << ", deep runs "
                             << formula << ", scratch-diff pairs " << w.scratch_diffs);
    CHECK(statuses[1] > 200);
    CHECK(statuses[0] > 200);
}

TEST_CASE("game(battle_rest): the skill-application wrappers equal their recompiled bodies") {
    World w{13u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u64, int> masks;
    for (int it = 0; it < 3000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 100 == 0) w.randomize_flags();
        w.use_enemy_table(it % 3 != 0);
        const u32 attacker = w.unit(it & 7, (rng() & 1) != 0);
        const u32 target = w.unit((it + 1 + rng() % 7) & 7, rng() % 3 != 0);
        const u32 skill = w.skill();
        const u32 flags = rng() % 4 == 0 ? 1u : 0u;
        const u32 a = it % 97 == 0 ? 0u : attacker, t = it % 89 == 0 ? 0u : target;
        Pair p = w.pair(PAIR(fn_sub_306610_00306610), Args{sx(skill), sx(a), sx(t), sx(flags)}, "datCalcApplySkill");
        CHECK(p.hand.v0 <= 1);
        p = w.pair(PAIR(fn_sub_3068D0_003068d0), Args{sx(skill), sx(a), sx(t), sx(flags)}, "datCalcGetSkillEffectMask");
        ++masks[p.hand.v0];
        w.with_t_args = true;
        w.t_args = {rng() % 4 ? sx(kOuts) : 0u, rng() % 4 ? sx(kOuts + 4) : 0u, rng() % 4 ? sx(kOuts + 8) : 0u, sx(rng())};
        w.pair(PAIR(fn_sub_306BC0_00306bc0), Args{sx(skill), sx(a), sx(t), sx(flags)}, "datCalcSkillResults");
        w.with_t_args = false;
    }
    std::string kinds;
    for (const auto& [v, n] : masks) kinds += " " + std::to_string(v) + ":" + std::to_string(n);
    MESSAGE("application pairs: " << w.pairs << "; effect masks" << kinds << "; scratch-diff pairs " << w.scratch_diffs);
    CHECK(masks.size() >= 4);
}

TEST_CASE("game(battle_rest): affinity decode, skill costs and the mix-raid pick equal their recompiled bodies") {
    World w{14u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u64, int> pay;
    int raids = 0;
    for (int it = 0; it < 3000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 100 == 0) w.randomize_flags();
        w.use_enemy_table(it % 2 == 0);
        const u32 word = rng() % 3 ? (rng() & 0xFF00u) | (rng() % 4 ? 0u : rng() & 0xFFu) : rng();
        const u32 boost = rng() % 2 ? 0u : rng();
        Pair p = w.pair(PAIR(fn_sub_306D90_00306d90), Args{sx(boost), sx(word)}, "datCalcDecodeAffinity");
        // documented rule: flags << 16 | 5 * rate when the rate byte is set
        const u32 w16 = word & 0xFFFFu;
        if ((w16 & 0xFFu) != 0) CHECK(p.hand.v0 == (sx((w16 & 0xFF00u) << 16) | (5u * (w16 & 0xFFu))));
        const u32 unit = w.unit(it & 7, rng() % 3 == 0);
        const u32 skill = w.skill();
        if (rng() % 2 && (skill & 0xFFFFu) < kSkillCount) {  // cost kind +3, percent +4, add +6, flags0
            const u32 rec = load32(w.m, kSkillTablePtr) + (skill & 0xFFFFu) * kSkillRecordSize;
            w.m.at(rec + 3)[0] = static_cast<u8>(rng() % 5 ? 1 + rng() % 2 : rng() % 4);
            store16(w.m, rec + 4, static_cast<u16>(rng() % 60));
            store16(w.m, rec + 6, static_cast<u16>(rng() % 4 ? rng() % 30 : rng()));
            w.m.at(rec)[0] = static_cast<u8>(rng());
        }
        w.pair(PAIR(fn_sub_3083F0_003083f0), Args{sx(unit), sx(skill)}, "datCalcGetSkillCost");
        p = w.pair(PAIR(fn_sub_3086F0_003086f0), Args{sx(unit), sx(skill)}, "datCalcCheckSkillCost");
        CHECK(p.hand.v0 <= 3);
        ++pay[p.hand.v0];
        p = w.pair(PAIR(fn_sub_308A80_00308a80), Args{sx(unit)}, "datCalcPickMixRaidSkill");
        if (p.hand.v0 != 0) {
            ++raids;
            CHECK((p.hand.v0 >= 192 && p.hand.v0 < 198));
        }
    }
    MESSAGE("cost pairs: " << w.pairs << ", payable " << pay[0] << ", HP short " << pay[1] << ", SP short " << pay[2]
                           << ", free " << pay[3] << ", mix raids " << raids << ", scratch-diff pairs " << w.scratch_diffs);
    CHECK(pay[0] > 100);
    CHECK(pay[1] > 20);
    CHECK(pay[2] > 20);
    CHECK(raids > 100);
}

TEST_CASE("game(battle_rest): the action rolls equal their recompiled bodies") {
    World w{15u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u64, int> kills, hits;
    int downs = 0, follow = 0, counters = 0;
    for (int it = 0; it < 4000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 100 == 0) w.randomize_flags();
        w.use_enemy_table(it % 3 != 0);
        const u32 attacker = w.unit(it & 7, (rng() & 1) != 0);
        const u32 target = w.unit((it + 1 + rng() % 7) & 7, rng() % 3 != 0);
        const u32 skill = w.skill();
        if (rng() % 3 == 0 && (skill & 0xFFFFu) < kSkillCount) {  // kill rate +37, kind +2, down +17, hits +15/+16
            const u32 rec = load32(w.m, kSkillTablePtr) + (skill & 0xFFFFu) * kSkillRecordSize;
            w.m.at(rec + 37)[0] = static_cast<u8>(rng() % 4 ? rng() % 60 : (rng() % 2 ? 100 : 0));
            w.m.at(rec + 2)[0] = static_cast<u8>(rng() % 6 ? 1 : rng() % 4);
            w.m.at(rec + 17)[0] = static_cast<u8>(rng() % 2);
            w.m.at(rec + 15)[0] = static_cast<u8>(1 + rng() % 3);
            w.m.at(rec + 16)[0] = static_cast<u8>(rng() % 8 ? 1 + rng() % 5 : 0);
        }
        constexpr u32 kResults[] = {0, 1, 1, 1, 2, 4, 8, 256, 512, 1024};
        const u32 result = rng() % 10 ? kResults[rng() % std::size(kResults)] : rng();
        const u32 a = it % 113 == 0 ? 0u : attacker;
        Pair p = w.pair(PAIR(fn_sub_30A740_0030a740), Args{sx(a), sx(target), sx(skill), sx(result)}, "datCalcRollInstantKill");
        ++kills[p.hand.v0];
        CHECK((p.hand.v0 == 1 || p.hand.v0 == 2 || p.hand.v0 == 4 || p.hand.v0 == 8));
        p = w.pair(PAIR(fn_sub_30AF00_0030af00), Args{sx(a), sx(target), sx(skill), sx(result)}, "datCalcCanKnockDown");
        downs += p.hand.v0 != 0;
        w.with_t_args = true;
        w.t_args = {sx(rng() % 4 ? rng() % 6 : rng()), 0, 0, 0};
        w.pair(PAIR(fn_sub_30B130_0030b130), Args{sx(a), sx(target), sx(skill), sx(result)}, "datCalcCheckKnockDown");
        w.with_t_args = false;
        const u32 fresult = rng() % 2 ? (rng() % 2 ? 4u : 2u) : result;  // the follow-up only rolls after results 4 / 2
        p = w.pair(PAIR(fn_sub_30B210_0030b210), Args{sx(attacker), sx(target), sx(skill), sx(fresult)}, "datCalcRollFollowUp");
        follow += p.hand.v0 != 0;
        p = w.pair(PAIR(fn_sub_30B640_0030b640), Args{sx(it % 211 == 0 ? 0u : attacker), sx(skill)}, "datCalcGetCounterSkill");
        counters += p.hand.v0 != ~u64{0} && p.hand.v0 != 0;
        p = w.pair(PAIR(fn_sub_30B9A0_0030b9a0), Args{sx(attacker), sx(skill), sx(result)}, "datCalcGetHitCount");
        ++hits[p.hand.v0];
    }
    std::string ks, hs;
    for (const auto& [v, n] : kills) ks += " " + std::to_string(v) + ":" + std::to_string(n);
    for (const auto& [v, n] : hits) hs += " " + std::to_string(v) + ":" + std::to_string(n);
    MESSAGE("roll pairs: " << w.pairs << "; kill results" << ks << "; knock-down " << downs << ", follow-up " << follow
                           << ", counters " << counters << "; hit counts" << hs << "; scratch-diff pairs " << w.scratch_diffs);
    CHECK(kills[2] > 50);
    CHECK(kills[4] > 15);
    CHECK(downs > 100);
    CHECK(follow > 20);
    CHECK(counters > 50);
    CHECK(hits.size() >= 4);
}

TEST_CASE("game(battle_rest): the readers equal their recompiled bodies") {
    World w{16u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    int drops = 0, escapes = 0, sec2 = 0;
    for (int it = 0; it < 1500; ++it) {
        if (it % 300 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 50 == 0) w.randomize_flags();
        w.use_enemy_table(it % 2 == 0);
        const u32 id = rng() % 6 ? rng() % 624 : rng();
        Pair p = w.pair(PAIR(fn_datGetSkillName_0030bb40), Args{sx(id)}, "datGetSkillName");
        CHECK(p.hand.v0 == sx(load32(w.m, kSkillNamesPtr) + 19u * (id & 0xFFFFu)));
        const u32 arc = rng() % 6 ? rng() % 32 : rng();
        p = w.pair(PAIR(fn_datGetArcanaName_0030bbb0), Args{sx(arc)}, "datGetArcanaName");
        CHECK(p.hand.v0 == sx(load32(w.m, kArcanaNamesPtr) + 21u * (arc & 0xFFu)));
        w.pair(PAIR(fn_sub_30BC20_0030bc20), Args{sx(rng() % 4 ? rng() % 1000 : rng())}, "datGetItemPrice");
        const u32 enemy = w.unit(it & 7, true);
        w.pair(PAIR(fn_sub_30BC50_0030bc50), Args{sx(enemy)}, "datCalcGetEnemyExp");
        const u32 out = rng() % 3 ? kOuts : 0u;
        p = w.pair(PAIR(fn_sub_30BDE0_0030bde0), Args{sx(enemy), sx(out)}, "datCalcRollEnemyDrop");
        drops += p.hand.v0 != 0;
        if (rng() % 2) {  // a stock holding both personas of a section-2 record, the current one first
            const u32 rec = load32(w.m, kSkillSection2Ptr) + 6u * (rng() % 32);
            const u32 slot = rng() % 3;
            store16(w.m, kStockCurrent, static_cast<u16>(slot));
            store16(w.m, kStock + 52 * slot, 1);
            store16(w.m, kStock + 52 * slot + 2, load16(w.m, rec + (rng() % 2 ? 2 : 4)));
            const u32 other = slot + 1 + rng() % 3;
            store16(w.m, kStock + 52 * other, static_cast<u16>(rng() % 4 ? 1 : 0));
            store16(w.m, kStock + 52 * other + 2, load16(w.m, rec + 2) == load16(w.m, kStock + 52 * slot + 2) ? load16(w.m, rec + 4) : load16(w.m, rec + 2));
            store32(w.m, kNoCostMode, 0);
        }
        p = w.pair(PAIR(fn_sub_30C0C0_0030c0c0), Args{}, "datGetSkillSection2ForParty");
        sec2 += p.hand.v0 != 0;
        const u32 s2 = rng() % 4 ? 272 + rng() % 33 : rng();
        p = w.pair(PAIR(fn_sub_30C220_0030c220), Args{sx(s2)}, "datGetSkillSection2");
        CHECK(p.hand.v0 == sx(load32(w.m, kSkillSection2Ptr) + 6u * ((s2 & 0xFFFFu) - 272u)));
        const u32 any = w.unit((it + 3) & 7, (rng() & 1) != 0);
        p = w.pair(PAIR(fn_sub_30C2A0_0030c2a0), Args{sx(any)}, "datCalcRollEscape");
        escapes += p.hand.v0 != 0;
        w.pair(PAIR(fn_sub_30C3A0_0030c3a0), Args{sx(any)}, "datCalcIsEnemyFlag4");
        w.pair(PAIR(fn_sub_30C490_0030c490), Args{sx(rng() % 4 ? 1 + rng() % 10 : (rng() % 16) | (rng() % 2 ? rng() << 16 : 0u))}, "datCalcRestorePartyMember");
        if (it % 10 == 0) w.pair(PAIR(fn_datCalcRestorePartyAll_0030c440), Args{}, "datCalcRestorePartyAll");
    }
    MESSAGE("reader pairs: " << w.pairs << ", drops " << drops << ", escapes " << escapes << ", section-2 matches " << sec2
                             << ", scratch-diff pairs " << w.scratch_diffs << ", faulting alike " << w.faulted);
    CHECK(drops > 50);
    CHECK(escapes > 300);
    CHECK(sec2 > 50);
}

TEST_CASE("game(battle_rest): the rest of the datUnit / datCalc / datScript band equals its recompiled bodies") {
    World w{17u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    constexpr u32 kGenus = kArena + 0x800, kSlots = kArena + 0x840, kRecord = kArena + 0xA00, kTask = kArena + 0x1000;
    constexpr u32 kCurrentTask = 0x7CE5A8u;  // g_scrCurrentTask, written by the COMM handlers' return values
    std::map<u64, int> added, effect_checks;
    int walls = 0;
    for (int it = 0; it < 2000; ++it) {
        if (it % 400 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        if (it % 100 == 0) w.randomize_flags();
        w.use_enemy_table(it % 2 == 0);
        // datUnitEcAddEnemy: a genus with six 60-byte slots, some taken
        store16(w.m, kGenus, static_cast<u16>(rng() % 8 ? 1 : rng() % 3));
        store16(w.m, kGenus + 2, static_cast<u16>(rng() % 7));
        store32(w.m, kGenus + 4, kSlots);
        fill_random(w.m, kSlots, 6 * 60, rng);
        for (u32 k = 0; k < 6; ++k) store16(w.m, kSlots + 60 * k + 2, static_cast<u16>(rng() % 3 ? 0 : 1 + rng() % 300));
        const u32 enemy = rng() % 10 ? rng() % kEnemyCount : rng() % 400;
        Pair p = w.pair(PAIR(fn_datUnitEcAddEnemy_002ff540), Args{sx(kGenus), sx(enemy)}, "datUnitEcAddEnemy");
        ++added[(p.hand.v0 - sx(kSlots)) / 60];
        // sub_2FFB00: a record whose +4 points at a unit-like header with the pc at +2
        store16(w.m, kRecord, static_cast<u16>(rng() % 4 ? 0 : 1));
        store32(w.m, kRecord + 4, kRecord + 0x20);
        store16(w.m, kRecord + 0x22, static_cast<u16>(1 + rng() % 10));
        w.pair(PAIR(fn_sub_2FFB00_002ffb00), Args{sx(kRecord)}, "datCalcUpdatePartyCondition");
        const u32 unit = w.unit(it & 7, (rng() & 1) != 0);
        w.pair(PAIR(fn_sub_3005A0_003005a0), Args{sx(unit)}, "datCalcGetCondition");
        w.pair(PAIR(fn_sub_300700_00300700), Args{sx(unit), sx(rng() % 2 ? 4039u : rng() % 200)}, "datCalcHasCounter");
        const u32 pc = rng() % 8 ? 1 + rng() % 10 : rng() % 12;
        p = w.pair(PAIR(fn_sub_300870_00300870), Args{sx(pc), sx(rng() % 3 ? pick(rng, kEffectPool) : rng())}, "datCalcCountEquipmentEffect");
        CHECK(p.hand.v0 <= 3);
        if (rng() % 2) std::memset(w.m.at(unit + 0x14), 0, 4);
        else store32(w.m, unit + 0x14, rng() & 0x60000u);
        p = w.pair(PAIR(fn_sub_300E90_00300e90), Args{sx(unit), sx(w.skill())}, "datCalcIsBlockedByWall");
        walls += p.hand.v0 != 0;
        if (rng() % 2) {  // live buffs
            for (u32 b = 0; b < 9; ++b) w.m.at(unit + 0x1C + b)[0] = static_cast<u8>(rng());
            store32(w.m, unit + 0x14, rng());
        }
        const u32 mask = rng() % 3 ? (1u << (rng() % 27)) : (rng() % 2 ? rng() & 0x07FFFFFFu : rng());
        p = w.pair(PAIR(fn_sub_301CA0_00301ca0), Args{sx(unit), sx(mask)}, "datCalcCheckEffectMask");
        ++effect_checks[p.hand.v0];
        store32(w.m, kCurrentTask, kTask);
        w.pair(PAIR(fn_sub_30FDC0_0030fdc0), Args{}, "datScriptCmdFloatZero");
        w.pair(PAIR(fn_sub_3111C0_003111c0), Args{}, "datScriptCmdTrue");
        if (it % 10 == 0) w.pair(PAIR(fn_sub_3112E0_003112e0), Args{}, "datScriptCmdRestoreParty");
    }
    MESSAGE("band pairs: " << w.pairs << ", enemy slots taken 0.." << added.size() << ", effect checks 0/1 " << effect_checks[0]
                           << "/" << effect_checks[1] << ", walls " << walls << ", scratch-diff pairs " << w.scratch_diffs);
    CHECK(effect_checks[1] > 200);
    CHECK(walls > 20);
}

#else
TEST_CASE("game(battle_rest): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
