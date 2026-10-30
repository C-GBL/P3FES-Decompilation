// Phase 5 pair tests for the datCalc.c hit / damage / affinity layer (game/src/battle/battle_calc.cpp): every
// hand-written function and the recompiled body it replaces run on identical guest machines on randomised
// battle states. Beyond pair_harness.h's Outcome (result, callee-saved GPRs, the arena, the caller's live stack,
// cycles, check points) each pair here also compares the callee-saved FPRs f20..f31, FCR31, HI/LO, and the whole
// game data window [0x5A0000, 0x9B0000) after both runs -- the RNG state of datCalcRand/effMiscRand, the AICALC
// script globals, every unit and party record -- and restores that window between the two runs, so both bodies
// consume the same random stream from the same state.
//
// The battle state: the eight battle/*.TBL files are loaded the way btlTableLoad (sub_27DCD0) does, by walking
// the record list off_692D40 of the ELF (real SKILL/UNIT/PERSONA/AICALC data from the extracted tree; random
// sections when it is absent), plus random weapon / accessory item tables, a random party in gGlobalWork with
// equipment and persona skills drawn from the effect and skill ids the formulas test, and random unit records
// (enemies with real or skill-pool EnemyRecords). The documented rules (docs/ANALYSIS/21_battle.md section 5)
// are checked on the host where they are simple to restate.
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/battle_calc.h"

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
P3FES_DECL_PAIR(fn_datCalcGetSkillElement_003082f0)
P3FES_DECL_PAIR(fn_sub_3086C0_003086c0)
P3FES_DECL_PAIR(fn_sub_308860_00308860)
P3FES_DECL_PAIR(fn_sub_308A50_00308a50)
P3FES_DECL_PAIR(fn_datCalcGetSkillSlotCount_00308ba0)
P3FES_DECL_PAIR(fn_datCalcGetSkillList_00308bb0)
P3FES_DECL_PAIR(fn_sub_308930_00308930)
P3FES_DECL_PAIR(fn_datCalcGetHeldWeaponType_00308c60)
P3FES_DECL_PAIR(fn_sub_308ED0_00308ed0)
P3FES_DECL_PAIR(fn_sub_308F80_00308f80)
P3FES_DECL_PAIR(fn_sub_308FD0_00308fd0)
P3FES_DECL_PAIR(fn_sub_3093A0_003093a0)
P3FES_DECL_PAIR(fn_datCalcGetWeaponParam_00309080)
P3FES_DECL_PAIR(fn_datCalcGetArmorParam_00309250)
P3FES_DECL_PAIR(fn_datCalcGetAffinityChecked_0030b4b0)
P3FES_DECL_PAIR(fn_datCalcIsLowHp_0030b5e0)
P3FES_DECL_PAIR(fn_datCalcGetAffinity_00306e80)
P3FES_DECL_PAIR(fn_datCalcCheckHit_00309490)
P3FES_DECL_PAIR(fn_datCalcDamage_00303130)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::btl;

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout of the battle state ------------------------------------------------------------------------
constexpr u32 kUnits = kArena + 0x100;      // eight 64-byte unit records in the arena (compared by the harness)
constexpr u32 kUnitStride = 64;
constexpr u32 kTables = 0x01900000u;        // the .TBL sections, as btlTableLoad lays them out in its arena
constexpr u32 kWeapons = 0x01880000u;       // 1,000 x 40-byte weapon records (pointer gp-0x4D0C = 0x7CDFE4)
constexpr u32 kAccessories = 0x018A0000u;   // 1,000 x 36-byte accessory records (pointer gp-0x4D1C = 0x7CDFD4)
constexpr u32 kHeroInventory = 0x018C0000u; // the hero's 20-byte item records (pointer 0x836794)
constexpr u32 kSynthEnemies = 0x018D0000u;  // a synthetic EnemyRecord[336] with skill-pool skills
constexpr u32 kBtlWork = 0x018E0000u;       // a stand-in gBtl block
constexpr u32 kDataLo = 0x005A0000u, kDataHi = 0x009B0000u;  // .data/.bss window compared and restored per pair
constexpr u32 kTableRecords = 0x00692D40u;  // off_692D40: 8 x 168-byte {name, name_F, {u32* dst, u32 size} x 20}

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

// The skill ids the formulas test (passives 464..621) and the equipment effects (26..188).
constexpr u16 kSkillPool[] = {464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482, 483,
                              484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 505,
                              506, 507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 526, 527, 528, 529,
                              530, 531, 532, 533, 534, 535, 537, 538, 539, 543, 544, 545, 546, 563, 564, 567, 568, 570, 573, 574,
                              575, 582, 583, 584, 585, 586, 612, 613, 614, 615, 616, 619, 620, 621, 1, 2, 100, 300};
constexpr u16 kEffectPool[] = {26,  27,  28,  29,  30,  36,  40,  48,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,
                               85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  103, 104, 105, 106, 107,
                               108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
                               128, 129, 142, 144, 150, 169, 173, 174, 175, 176, 177, 178, 179, 183, 184, 185, 186, 187, 188, 0};
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

// One pair outcome beyond the harness's: what the battle functions may also touch.
struct Extra {
    std::array<u32, 12> fpr{};  // f20..f31
    u32 fcr31 = 0;
    u64 hi = 0, lo = 0;
};

struct World {
    Machine m;
    std::mt19937 rng;
    bool real = false;          // the extracted tables were found
    u32 real_enemy_table = 0;   // the real UNIT.TBL section 0 (kUnitTablePtr may point at the synthetic one)
    u64 pairs = 0;
    bool with_t_args = false;    // the eight-argument datCalcDamage: $t0..$t3 from t_args (sign-extended values)
    std::array<u64, 4> t_args{};

    explicit World(u32 seed) : rng(seed) {}

    const char* load() {
        if (const char* err = m.load_elf(elf_path())) return err;
        install_tables();
        randomize_items();
        randomize_party();
        fill_random(m, kBtlWork, 0x1000, rng);
        return nullptr;
    }

    // btlTableLoad: for each record of off_692D40, each {dst, size} pair: *dst = arena + offset, the section
    // bytes there, offset advanced by the 16-aligned size. Random sections of the record's size when absent.
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
        fill_random(m, kTables + offset, 0x4000, rng);  // reads past the last section stay defined
        real = found == 8;
        real_enemy_table = load32(m, kUnitTablePtr);
        // A synthetic enemy table: the real records with their eight skills drawn from the skill pool.
        std::memcpy(m.at(kSynthEnemies), m.at(real_enemy_table), kEnemyCount * kEnemyRecordSize);
        for (u32 id = 0; id < kEnemyCount; ++id)
            for (u32 s = 0; s < 8; ++s) store16(m, kSynthEnemies + id * kEnemyRecordSize + 14 + 2 * s, static_cast<u16>(pick(rng, kSkillPool)));
        fill_random(m, kSynthEnemies + kEnemyCount * kEnemyRecordSize, 0x2000, rng);
    }
    void use_enemy_table(bool synthetic) { store32(m, kUnitTablePtr, synthetic ? kSynthEnemies : real_enemy_table); }

    // Weapon records (40 B): +4 the hero's type mask, +30 the element / type; accessory records (36 B): +28 the
    // granted skill.
    void randomize_items() {
        fill_random(m, kWeapons, 1000 * 40, rng);
        for (u32 i = 0; i < 1000; ++i) {
            store32(m, kWeapons + 40 * i + 4, rng() % 8 ? kWeaponMasks[rng() % std::size(kWeaponMasks)] : rng());
            store16(m, kWeapons + 40 * i + 30, static_cast<u16>(rng() % 6 ? rand_range(rng, -1, 9) : static_cast<s32>(rng())));
        }
        fill_random(m, kAccessories, 1000 * 36, rng);
        for (u32 i = 0; i < 1000; ++i) store32(m, kAccessories + 36 * i + 28, pick(rng, kSkillPool));
        store32(m, kWeaponTablePtr, kWeapons);
        store32(m, kAccessoryTablePtr, kAccessories);
    }

    // The party in gGlobalWork: member pc 2..10 at 0x834010 + 868 (pc - 2) (equipment indices s16[4] at +0x54,
    // 20-byte items at +0x5C: u16 id, u8 effect at +9; the persona at +0xDC: u16 id at +2, u16 skills[8] at
    // +12); the hero's equipment indices at 0x83678C and its item array through the pointer at 0x836794.
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
        }
        for (u32 s = 0; s < 4; ++s) store16(m, 0x83678Cu + 2 * s, static_cast<u16>(s));
        // The members' unit-like headers at record +4 (datCalcGetLevel through sub_16CC00 reads the id at +2), also for
        // the out-of-range ids 11..13 the unit records use, and the hero's at 0x836224 (id 1).
        for (u32 pc = 2; pc <= 13; ++pc) store16(m, 0x834010u + 868u * (pc - 2) + 6, static_cast<u16>(pc));
        store16(m, 0x836226u, 1);
        store32(m, 0x836794u, kHeroInventory);
        fill_random(m, kHeroInventory, 0x400, rng);
        for (u32 i = 0; i < 16; ++i) item(kHeroInventory + 20 * i, i % 4);
    }

    // A random unit record in slot `slot`: enemies with ids/base ids mostly < 336, party members mostly 1..10.
    u32 unit(unsigned slot, bool enemy) {
        const u32 va = kUnits + slot * kUnitStride;
        fill_random(m, va, kUnitStride, rng);
        u16 flags = load16(m, va);
        flags = enemy ? static_cast<u16>(flags | kUnitFlagEnemy) : static_cast<u16>(flags & ~kUnitFlagEnemy);
        store16(m, va, flags);
        if (enemy) {
            store16(m, va + 2, static_cast<u16>(rng() % 20 ? rng() % kEnemyCount : rng() % 400));
            store16(m, va + 4, static_cast<u16>(rng() % 20 ? rng() % kEnemyCount : rng() % 400));
        } else {
            store16(m, va + 2, static_cast<u16>(rng() % 20 ? rand_range(rng, 1, 10) : rng() % 14));
        }
        return va;
    }

    // An element row argument: mostly -1..18, sometimes out of range or with high garbage.
    u32 element() {
        const u32 r = rng() % 16;
        if (r == 0) return rng();
        if (r == 1) return static_cast<u32>(rand_range(rng, -40, 40));
        return static_cast<u32>(rand_range(rng, -1, 18)) | (r == 2 ? (rng() << 16) : 0u);
    }

    static Extra extra(const EEContext& c) {
        Extra e;
        for (int i = 0; i < 12; ++i) e.fpr[i] = c.fpr[20 + i];
        e.fcr31 = c.fcr31;
        e.hi = c.hi.u64[0];
        e.lo = c.lo.u64[0];
        return e;
    }

    // Like pair_harness.h's run, with random FPRs as well.
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
        std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
        x = extra(m.ctx);
        return o;
    }

    // Both bodies from the same machine state; the data window is restored between them and compared after.
    Pair pair(Fn hand, Fn recomp, const Args& args, const char* what) {
        char tag[160];
        std::snprintf(tag, sizeof tag, "%s a0=0x%llx a1=0x%llx", what, static_cast<unsigned long long>(args[0]),
                      static_cast<unsigned long long>(args[1]));
        const std::string context = tag;
        INFO(context);
        const u32 seed = rng();
        // the window through a PairRange (write_tracker.h): only the pages written are copied and compared
        // (copying the whole 4 MiB per pair was ~2 ms, nearly all of these tests' time)
        PairRange window(m.at(kDataLo), m.at(kDataHi));
        const std::vector<u8> arena = m.bytes(kArena, kArenaSize);
        Pair p;
        Extra xh, xr;
        p.hand = run1(hand, args, seed, xh);
        window.between();
        std::memcpy(m.at(kArena), arena.data(), arena.size());
        p.recomp = run1(recomp, args, seed, xr);
        expect_same(p.hand, p.recomp, what);
        CHECK(xh.fpr == xr.fpr);
        CHECK(xh.fcr31 == xr.fcr31);
        CHECK(xh.hi == xr.hi);
        CHECK(xh.lo == xr.lo);
        const bool same_data = window.first_difference() == window.size();
        CHECK(same_data);
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

}  // namespace

TEST_CASE("game(battle_calc): the battle tables load as btlTableLoad lays them out") {
    World w{1u};
    LOAD_WORLD_OR_SKIP(w);
    if (!w.real) {
        MESSAGE("SKIP: battle/*.TBL not beside the ELF; the pair tests run on random sections");
        return;
    }
    // UNIT.TBL section 1, enemy 1 ("Cowardly Maya"): 0x0014 = 100 % at row 0 and 0x0800 = weak at row 3 (21_battle.md 2.3).
    const u32 aff = load32(w.m, kEnemyAffinityTablePtr);
    CHECK(load16(w.m, aff + 32 * 1 + 0) == 0x0014);
    CHECK(load16(w.m, aff + 32 * 1 + 2 * 3) == 0x0800);
    CHECK(load32(w.m, kAiCalc7TablePtr) != 0);
}

TEST_CASE("game(battle_calc): the unit / weapon / skill helpers equal their recompiled bodies") {
    World w{2u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    int elements_from_weapon = 0;
    for (int it = 0; it < 3000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        w.use_enemy_table(it % 2 == 0);
        const bool enemy = (rng() & 1) != 0;
        const u32 unit = w.unit(it & 7, enemy);
        const u32 skill = rng() % 4 ? rng() % 500 : rng();
        Pair p = w.pair(PAIR(fn_datCalcGetSkillElement_003082f0), Args{it % 50 == 0 ? 0u : unit, skill}, "datCalcGetSkillElement");
        const u32 id = skill & 0xFFFFu;
        const u8* rec = w.m.mem.main_ram() + load32(w.m, kSkillTablePtr) + id * kSkillRecordSize;
        if (it % 50 != 0 && id < kSkillCount && (rec[0] & 2) && !enemy) ++elements_from_weapon;
        w.pair(PAIR(fn_sub_3086C0_003086c0), Args{rng(), rng() % 464}, "datCalcGetSkillByte3");
        w.pair(PAIR(fn_sub_308860_00308860), Args{rng() % 3 ? static_cast<u32>(rand_range(rng, 185, 200)) : rng()}, "datCalcIsMixRaidSkill");
        w.pair(PAIR(fn_sub_308A50_00308a50), Args{rng() % 3 ? static_cast<u32>(rand_range(rng, 265, 310)) : rng()}, "sub_308A50");
        w.pair(PAIR(fn_datCalcGetSkillSlotCount_00308ba0), Args{}, "datCalcGetSkillSlotCount");
        w.pair(PAIR(fn_datCalcGetSkillList_00308bb0), Args{unit}, "datCalcGetSkillList");
        w.pair(PAIR(fn_sub_308930_00308930), Args{unit}, "datCalcGetAttackSkill");
        w.pair(PAIR(fn_datCalcGetHeldWeaponType_00308c60), Args{unit}, "datCalcGetHeldWeaponType");
        w.pair(PAIR(fn_sub_308ED0_00308ed0), Args{unit}, "datCalcGetHeldWeaponId");
        w.pair(PAIR(fn_sub_308F80_00308f80), Args{unit}, "datCalcGetWeaponClass");
        constexpr u32 kModes[] = {0, 1, 2, 4, 6, 8, 16, 0x10008};
        w.pair(PAIR(fn_sub_308FD0_00308fd0), Args{unit, kModes[rng() % 8]}, "datCalcGetWeaponHitClass");
        w.pair(PAIR(fn_sub_3093A0_003093a0), Args{unit}, "datCalcGetWeaponAiCalcByte");
        const u32 which = rng() % 5 ? rng() % 2 : rng() % 4 + (rng() % 2 ? 0x100u : 0u);
        w.pair(PAIR(fn_datCalcGetWeaponParam_00309080), Args{unit, which}, "datCalcGetWeaponParam");
        w.pair(PAIR(fn_datCalcGetArmorParam_00309250), Args{unit, which}, "datCalcGetArmorParam");
        p = w.pair(PAIR(fn_datCalcIsLowHp_0030b5e0), Args{unit}, "datCalcIsLowHp");
        CHECK(p.hand.v0 <= 1);
    }
    CHECK(elements_from_weapon > 30);
    MESSAGE("helper pairs: " << w.pairs);
}

TEST_CASE("game(battle_calc): datCalcGetAffinity / GetAffinityChecked equal their recompiled bodies") {
    World w{3u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u32, int> flags_seen;  // high byte of the result
    int enemy_rows = 0, rates_checked = 0;
    for (int it = 0; it < 6000; ++it) {
        if (it % 600 == 0) w.randomize_party();
        const bool synthetic = it % 3 != 0;
        w.use_enemy_table(synthetic);
        const bool enemy = (rng() % 3) != 0;
        const u32 unit = w.unit(it & 7, enemy);
        // buff walls up now and then (slots 13..16 live in bytes +0x22/+0x23 of the nibble array)
        if (rng() % 3 == 0) std::memset(w.m.at(unit + 0x1C), 0, 9);
        const u32 e = w.element();
        Pair p = w.pair(PAIR(fn_datCalcGetAffinity_00306e80), Args{it % 97 == 0 ? 0u : unit, e}, "datCalcGetAffinity");
        ++flags_seen[static_cast<u32>(p.hand.v0 >> 24) & 0xFFu];
        const s32 row = static_cast<s16>(static_cast<u16>(e));
        if (row == 16 || row == 17 || row == 18) CHECK(p.hand.v0 == 100);
        if (row == -1) CHECK(p.hand.v0 == 0);
        // An enemy with the real table, a physical/magic row and no passives in its skill list: the rate is
        // 5 x the table's low byte (or the flag default when it is 0).
        if (enemy && !synthetic && row >= 0 && row < 16 && it % 97 != 0) {
            const u32 base = load16(w.m, unit + 4);
            if (base < kEnemyCount) {
                ++enemy_rows;
                const u16 raw = load16(w.m, load32(w.m, kEnemyAffinityTablePtr) + base * 32 + 2 * static_cast<u32>(row));
                bool passives = false;
                for (u32 s = 0; s < 8; ++s) {
                    const u32 sk = load16(w.m, w.real_enemy_table + load16(w.m, unit + 2) * kEnemyRecordSize + 14 + 2 * s);
                    passives = passives || (sk >= 464 && sk <= 621);
                }
                if (!passives && (raw & 0xFF) != 0 && (raw >> 8) == 0) {
                    CHECK((p.hand.v0 & 0xFFFF) == static_cast<u64>((raw & 0xFF) * 5) );
                    ++rates_checked;
                }
            }
        }
        w.pair(PAIR(fn_datCalcGetAffinityChecked_0030b4b0), Args{unit, e}, "datCalcGetAffinityChecked");
    }
    MESSAGE("affinity pairs: " << w.pairs << ", enemy rows " << enemy_rows << ", plain rates checked " << rates_checked);
    CHECK(flags_seen.size() > 6);
    if (w.real) CHECK(rates_checked > 100);
}

// The state datCalcCheckHit reads beyond the helpers': the flags 4881/4889 (bits 17 and 25 of the flag word
// 0x83A47C: datScriptCalc's formula table, the condition multipliers), the party members' conditions (u16 at
// 0x83626C for the hero, record +0x4C for pc 2..10; 1/2/4/5 matter), and a target shaped towards each early exit.
void randomize_hit_state(World& w) {
    std::mt19937& rng = w.rng;
    u32 flags = load32(w.m, 0x83A47Cu) & ~((1u << 17) | (1u << 25));
    flags |= (rng() & 1u) << 17;
    flags |= (rng() & 1u) << 25;
    store32(w.m, 0x83A47Cu, flags);
    store16(w.m, 0x83626Cu, static_cast<u16>(rng() % 7));
    for (u32 pc = 2; pc <= 10; ++pc) store16(w.m, 0x834010u + 868u * (pc - 2) + 0x4C, static_cast<u16>(rng() % 7));
}
void shape_target(World& w, u32 target) {
    std::mt19937& rng = w.rng;
    constexpr u32 kStatuses[] = {8, 0x100000, 512, 2, 64, 32, 0x100, 0, 0, 0};
    const u32 r = rng() % 14;
    if (r < std::size(kStatuses)) store32(w.m, target + 0xC, kStatuses[r] | (rng() % 4 == 0 ? (rng() & 0xFFF00000u) : 0u));
    if (rng() % 4 != 0) store32(w.m, target + 0x14, load32(w.m, target + 0x14) & ~0x60000u);  // the dodge flags
    if (rng() % 3 != 0) std::memset(w.m.at(target + 0x1C), 0, 9);                           // no buffs
    if (rng() % 4 == 0) store16(w.m, target, static_cast<u16>(load16(w.m, target) & ~0x80u));
}

TEST_CASE("game(battle_calc): datCalcCheckHit equals its recompiled body") {
    World w{4u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    std::map<u64, int> results;
    int formula_runs = 0;
    for (int it = 0; it < 8000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        w.use_enemy_table(it % 3 != 0);
        randomize_hit_state(w);
        const unsigned a_slot = it & 7, t_slot = (a_slot + 1 + rng() % 7) & 7;
        const u32 attacker = w.unit(a_slot, (rng() & 1) != 0);
        const u32 target = w.unit(t_slot, rng() % 3 != 0);
        shape_target(w, target);
        const u32 skill = rng() % 8 ? rng() % kSkillCount : (rng() % 2 ? rng() % 600 : rng());
        const u32 flags = rng() % 4;
        Pair p = w.pair(PAIR(fn_datCalcCheckHit_00309490), Args{it % 211 == 0 ? 0u : attacker, target, skill, flags}, "datCalcCheckHit");
        ++results[p.hand.v0];
        if (p.hand.checks > 20) ++formula_runs;
        // Documented rules: the result is one of the five codes; a miss on the rate path stores the message.
        const u64 v = p.hand.v0;
        CHECK((v == kHit || v == kMiss || v == kNullified || v == kRepelled || v == kDrained));
    }
    MESSAGE("check-hit pairs: " << w.pairs << ", hit " << results[kHit] << ", miss " << results[kMiss] << ", null "
                                << results[kNullified] << ", repel/evade " << results[kRepelled] << ", drain " << results[kDrained]
                                << ", rate-formula runs " << formula_runs);
    CHECK(results[kHit] > 100);
    CHECK(results[kMiss] > 100);
    CHECK(results[kNullified] > 20);
    CHECK(results[kRepelled] > 100);
    if (w.real) CHECK(results[kDrained] > 0);
}

TEST_CASE("game(battle_calc): datCalcDamage equals its recompiled body") {
    World w{5u};
    LOAD_WORLD_OR_SKIP(w);
    std::mt19937& rng = w.rng;
    w.with_t_args = true;
    std::map<u32, int> formulas;  // SKILL formula (+17 / +20) of the HP/SP calls with a valid id
    int damage = 0, recovery = 0, zeroed = 0;
    for (int it = 0; it < 8000; ++it) {
        if (it % 500 == 0) {
            w.randomize_party();
            w.randomize_items();
        }
        w.use_enemy_table(it % 3 != 0);
        randomize_hit_state(w);
        const unsigned a_slot = it & 7, t_slot = (a_slot + 1 + rng() % 7) & 7;
        const u32 attacker = w.unit(a_slot, (rng() & 1) != 0);
        const u32 target = w.unit(t_slot, rng() % 3 != 0);
        shape_target(w, target);
        shape_target(w, attacker);  // the attacker's statuses 0x10 (critical) and 0x100 matter too
        const u32 skill = rng() % 8 ? rng() % kSkillCount : (rng() % 2 ? rng() % 700 : rng());
        const u32 hits = rng() % 4 ? rng() % 5 : rng();
        constexpr u32 kResults[] = {0, 1, 1, 1, 2, 4, 256, 512, 1024, 1024};
        const u32 result = rng() % 12 ? kResults[rng() % std::size(kResults)] : rng();
        constexpr u32 kKinds[] = {0, 1, 2, 2, 8, 16};
        const u32 kind = rng() % 10 ? kKinds[rng() % std::size(kKinds)] : rng();
        const u32 flags = rng() % 4 == 0 ? 1u : (rng() % 8 == 0 ? rng() : 0u);
        const u32 hp_or_sp = rng() % 12 ? 1 + rng() % 2 : rng() % 5;
        if (rng() % 3 == 0 && (skill & 0xFFFFu) < kSkillCount) {
            // A reshaped SKILL record (the real table has no skills with formulas 6, 7, 9, 10, 14, 15): formula
            // +17 / +20, base +18 / +22, kind +2, class +36, minimum +40.
            const u32 rec = load32(w.m, kSkillTablePtr) + (skill & 0xFFFFu) * kSkillRecordSize;
            w.m.at(rec + 17)[0] = static_cast<u8>(rng() % 19);
            w.m.at(rec + 20)[0] = static_cast<u8>(rng() % 19);
            store16(w.m, rec + 18, static_cast<u16>(rng() % 4 ? rand_range(rng, -20, 300) : static_cast<s32>(rng())));
            store16(w.m, rec + 22, static_cast<u16>(rng() % 4 ? rand_range(rng, -20, 300) : static_cast<s32>(rng())));
            w.m.at(rec + 2)[0] = static_cast<u8>(rng() % 8 ? 1 + rng() % 2 : rng() % 4);
            w.m.at(rec + 36)[0] = static_cast<u8>(rng() % 10);
            store16(w.m, rec + 40, static_cast<u16>(rng() % 3 ? rng() % 50 : rng()));
        }
        w.t_args ={sx(result), sx(kind), sx(flags), sx(hp_or_sp)};
        Pair p = w.pair(PAIR(fn_datCalcDamage_00303130), Args{sx(skill), sx(attacker), sx(target), sx(hits)}, "datCalcDamage");
        const u32 id = skill & 0xFFFFu, hs = hp_or_sp & 0xFFu;
        if (id < kSkillCount && (hs == 1 || hs == 2))
            ++formulas[w.m.mem.main_ram()[load32(w.m, kSkillTablePtr) + id * kSkillRecordSize + (hs == 1 ? 17 : 20)]];
        const s32 v = static_cast<s32>(static_cast<u32>(p.hand.v0));
        CHECK(p.hand.v0 == sx(static_cast<u32>(v)));
        // Documented rule: a miss / result 2 / nullified changes nothing.
        const u32 res = result & 0xFFFFu;
        if (res == kMiss || res == 2 || res == kNullified) {
            CHECK(v == 0);
            ++zeroed;
        } else if (v < 0) {
            ++damage;
        } else if (v > 0) {
            ++recovery;
        }
    }
    std::string kinds;
    for (const auto& [f, n] : formulas) kinds += " " + std::to_string(f) + ":" + std::to_string(n);
    MESSAGE("damage pairs: " << w.pairs << ", damage " << damage << ", recovery " << recovery << ", zeroed " << zeroed
                             << "; formulas" << kinds);
    CHECK(damage > 500);
    CHECK(recovery > 100);
    if (w.real) CHECK(formulas.size() >= 8);
}

#else
TEST_CASE("game(battle_calc): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
