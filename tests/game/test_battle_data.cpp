// Phase 5 pair tests for slice battle_data (game/src/battle/battle_data.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved registers, the
// arena and the caller's stack, virtual cycles, check-point count) and, because these functions read and write
// guest globals far from the arena, every region they can touch is compared too: the battle scratch (gBtl, the
// action and btlUnit objects, the order lists, the unit records), the gp-relative battle globals, the datScript
// context, the effMiscRand state, the party / persona records of the global work area and the two state tables.
// HI/LO and the FPU registers are compared as well (datCalcRand divides, datCalcGetEffectMultiplier returns in
// $f0 and leaves $f1). Inputs are randomised worlds plus edge cases (assertion paths, empty and full lists, wide
// 64-bit arguments); documented rules (docs/ANALYSIS/21_battle.md sections 1.3, 1.4, 2, 3, 5) are checked on the
// host independently of both bodies. Real data: the eight battle .TBL files beside the ELF are loaded the way
// btlTableLoadAll does (the loader records of off_692D40 give each section's pointer), random images otherwise.
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/battle_data.h"
#include "p3fes/ee/fpu.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
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
P3FES_DECL_PAIR(fn_sub_2FF2D0_002ff2d0)
P3FES_DECL_PAIR(fn_sub_2FF2F0_002ff2f0)
P3FES_DECL_PAIR(fn_sub_2FF310_002ff310)
P3FES_DECL_PAIR(fn_datUnitIsGenusReady_002ff320)
P3FES_DECL_PAIR(fn_sub_2FF330_002ff330)
P3FES_DECL_PAIR(fn_datUnitEcRemoveEnemy_002ff660)
P3FES_DECL_PAIR(fn_datUnitIsGenusDead_002ff790)
P3FES_DECL_PAIR(fn_datUnitInit_002ff890)
P3FES_DECL_PAIR(fn_datCalcRand_002ffbc0)
P3FES_DECL_PAIR(fn_datCalcGetLevel_002ffcc0)
P3FES_DECL_PAIR(fn_datCalcGetMaxHp_002ffdf0)
P3FES_DECL_PAIR(fn_datCalcGetMaxSp_00300100)
P3FES_DECL_PAIR(fn_datCalcAddHp_00300410)
P3FES_DECL_PAIR(fn_datCalcAddSp_00300480)
P3FES_DECL_PAIR(fn_datCalcHasSkill_003005e0)
P3FES_DECL_PAIR(fn_sub_300750_00300750)
P3FES_DECL_PAIR(fn_datCalcCountEquipmentWithEffect_003009a0)
P3FES_DECL_PAIR(fn_sub_300B60_00300b60)
P3FES_DECL_PAIR(fn_datCalcGetStat_00300c90)
P3FES_DECL_PAIR(fn_datCalcGetPassiveSkillFlags_00300d80)
P3FES_DECL_PAIR(fn_datCalcSetEffectLevel_00301030)
P3FES_DECL_PAIR(fn_sub_301150_00301150)
P3FES_DECL_PAIR(fn_datCalcAddEffectLevel_00301230)
P3FES_DECL_PAIR(fn_datCalcClearEffect_00301540)
P3FES_DECL_PAIR(fn_datCalcClearAllEffects_00301690)
P3FES_DECL_PAIR(fn_sub_301870_00301870)
P3FES_DECL_PAIR(fn_datCalcGetEffectMultiplier_00301880)
P3FES_DECL_PAIR(fn_sub_311180_00311180)
P3FES_DECL_PAIR(fn_datScriptSetResult_00311190)
P3FES_DECL_PAIR(fn_sub_3111F0_003111f0)
P3FES_DECL_PAIR(fn_sub_311250_00311250)
P3FES_DECL_PAIR(fn_sub_3112C0_003112c0)
P3FES_DECL_PAIR(fn_btlMainCheckBattleEnd_0027d380)
P3FES_DECL_PAIR(fn_sub_27D880_0027d880)
P3FES_DECL_PAIR(fn_sub_27D8B0_0027d8b0)
P3FES_DECL_PAIR(fn_sub_27DBE0_0027dbe0)
P3FES_DECL_PAIR(fn_sub_27DC50_0027dc50)
P3FES_DECL_PAIR(fn_sub_27E310_0027e310)
P3FES_DECL_PAIR(fn_sub_27E390_0027e390)
P3FES_DECL_PAIR(fn_btlActionSetState_00299d60)
P3FES_DECL_PAIR(fn_sub_299E30_00299e30)
P3FES_DECL_PAIR(fn_sub_299E50_00299e50)
P3FES_DECL_PAIR(fn_sub_299E70_00299e70)
P3FES_DECL_PAIR(fn_sub_29A1D0_0029a1d0)
P3FES_DECL_PAIR(fn_sub_29A210_0029a210)
P3FES_DECL_PAIR(fn_sub_29A250_0029a250)
P3FES_DECL_PAIR(fn_sub_29A2C0_0029a2c0)
P3FES_DECL_PAIR(fn_sub_29A320_0029a320)
P3FES_DECL_PAIR(fn_sub_29A380_0029a380)
P3FES_DECL_PAIR(fn_sub_29A3E0_0029a3e0)
P3FES_DECL_PAIR(fn_sub_29A470_0029a470)
P3FES_DECL_PAIR(fn_sub_29A4F0_0029a4f0)
P3FES_DECL_PAIR(fn_btlOrderSortByAgility_0029a570)
P3FES_DECL_PAIR(fn_sub_29A690_0029a690)
P3FES_DECL_PAIR(fn_btlMainSetState_0029de20)
P3FES_DECL_PAIR(fn_btlMainUpdateState_0029de80)
P3FES_DECL_PAIR(fn_datGetEquipmentIdx_0016cb80)
P3FES_DECL_PAIR(fn_sub_16CC00_0016cc00)
P3FES_DECL_PAIR(fn_sub_16CCB0_0016ccb0)
P3FES_DECL_PAIR(fn_datGetUnit_0016cd60)
P3FES_DECL_PAIR(fn_sub_16F630_0016f630)
P3FES_DECL_PAIR(fn_sub_16F900_0016f900)
P3FES_DECL_PAIR(fn_sub_170E40_00170e40)
P3FES_DECL_PAIR(fn_sub_173220_00173220)
P3FES_DECL_PAIR(fn_sub_1732F0_001732f0)
P3FES_DECL_PAIR(fn_sub_173380_00173380)
P3FES_DECL_PAIR(fn_sub_1733B0_001733b0)
P3FES_DECL_PAIR(fn_sub_173460_00173460)
P3FES_DECL_PAIR(fn_sub_173510_00173510)
P3FES_DECL_PAIR(fn_sub_1738D0_001738d0)
P3FES_DECL_PAIR(fn_datPersonaGetByPcId_00174800)
P3FES_DECL_PAIR(fn_sub_174A90_00174a90)
P3FES_DECL_PAIR(fn_sub_175410_00175410)
P3FES_DECL_PAIR(fn_sub_1D75F0_001d75f0)
P3FES_DECL_PAIR(fn_sub_1D76E0_001d76e0)
P3FES_DECL_PAIR(fn_sub_1D77D0_001d77d0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::btl;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout of the tests --------------------------------------------------------------------------------
// Everything the functions may write lies in the battle scratch [kScratch, kScratch + 64 KB) or in the watched
// globals below; the .TBL images and the accessory table are read-only for the bodies.
constexpr u32 kScratch = kArena;                 // 0x01800000
constexpr u32 kScratchSize = 0x10000u;
constexpr u32 kGBtl = kScratch;                  // gBtl (0xD20 bytes: the task word is at +0xD18)
constexpr u32 kGBtlSize = 0xD20u;
constexpr u32 kUnits = kScratch + 0x1000;        // 16 DatUnits, 64-byte stride
constexpr u32 kUnitStride = 64;
constexpr u32 kGenus = kScratch + 0x1400;        // {u16 kind, u16 count, u32 units}
constexpr u32 kGenusUnits = kScratch + 0x1600;   // 6 x 60-byte enemy units of the genus
constexpr u32 kHeroEquip = kScratch + 0x1800;    // the hero's 20-byte equipment entries (pointer 0x836794)
constexpr u32 kEncounter = kScratch + 0x1C00;    // gBtl+3004 points here: u16 encounter id at +8
constexpr u32 kQuery = kScratch + 0x1D00;        // sub_45AF40's gp-17912 chain (+60 -> +80)
constexpr u32 kActions = kScratch + 0x2000;      // 8 btlAction objects
constexpr u32 kActStride = 1200;
constexpr u32 kBtlUnits = kScratch + 0x4800;     // 8 btlUnit objects
constexpr u32 kBuStride = 0xA40;
constexpr u32 kPackets = kScratch + 0xA000;      // 16 packets
constexpr u32 kPacketStride = 128;
constexpr u32 kList = kScratch + 0xB000;         // sub_29A250's word list
constexpr u32 kPacketWords = kScratch + 0xB100;  // flag words of sub_27DBE0 / sub_27DC50
constexpr u32 kTables = 0x01900000u;             // the .TBL images (about 1.2 MB)
constexpr u32 kAccessoryTable = 0x01AC0000u;     // 1,000 x 36-byte accessory records (pointer 0x7CDFD4)

constexpr u32 kQueryPtr = 0x7CE6F8u;             // gp-17912: read by sub_45AF40 (btlMainCheckBattleEnd's sub_2BFC90)
constexpr u32 kRandState = 0x957BF0u;            // effMiscRand(0)'s 16-byte state

struct Region {
    u32 va;
    u32 len;
};
const Region kWatched[] = {
    {kScratch, kScratchSize},  // gBtl, actions, btlUnits, packets, lists, units
    {0x7CDF00u, 0x900u},       // the gp-relative battle globals (table pointers, genus byte, datCalcRand's last roll)
    {0x957100u, 0x100u},       // the datScript context
    {kRandState, 0x10u},       // the RNG state
    {0x833000u, 0x8000u},      // party records, hero unit / equipment / persona stock, stock flags
    {kActionStateTbl, 0x400u}, // sBtlActionTbl (the tests install their own rows)
    {kMainStateTbl, 0x100u},   // sBtlMainStateTbl
};

using Snap = std::vector<std::vector<u8>>;
Snap snap(const Machine& m) {
    Snap s;
    for (const Region& r : kWatched) s.push_back(m.bytes(r.va, r.len));
    return s;
}
void restore(Machine& m, const Snap& s) {
    std::size_t i = 0;
    for (const Region& r : kWatched) std::memcpy(m.at(r.va), s[i++].data(), r.len);
}

struct Full {
    Outcome o;
    Snap mem;
    std::array<u32, 32> fpr{};
    u32 fcr31 = 0;
    u64 hi[2] = {}, lo[2] = {};
};
Full run_full(Machine& m, Fn fn, const Args& a, u32 seed) {
    Full f;
    f.o = run(m, fn, a, seed);
    f.mem = snap(m);
    for (int i = 0; i < 32; ++i) f.fpr[i] = m.ctx.fpr[i];
    f.fcr31 = m.ctx.fcr31;
    for (int i = 0; i < 2; ++i) {
        f.hi[i] = m.ctx.hi.u64[i];
        f.lo[i] = m.ctx.lo.u64[i];
    }
    return f;
}

struct Res {
    Outcome hand;
    Outcome recomp;
    u32 f0 = 0;            // $f0 after the run
    bool faulted = false;  // both bodies stopped at the same fault (pair_harness.h fault_of): no values to check
};
int g_faulted_pairs = 0;

// Both bodies from the same watched state; afterwards the recompiled run's state is in place.
Res pair(Machine& m, Fn hand, Fn recomp, const Args& a, u32 seed, const char* what) {
    const Snap before = snap(m);
    Full h, r;
    const std::string fh = fault_of([&] { h = run_full(m, hand, a, seed); });
    restore(m, before);
    const std::string fr = fault_of([&] { r = run_full(m, recomp, a, seed); });
    if (!fh.empty() || !fr.empty()) {
        INFO(what);
        CHECK(fh == fr);
        ++g_faulted_pairs;
        return Res{{}, {}, 0, true};
    }
    expect_same(h.o, r.o, what);
    INFO(what);
    for (std::size_t i = 0; i < std::size(kWatched); ++i) {
        INFO("watched region at 0x" << std::hex << kWatched[i].va);
        CHECK(h.mem[i] == r.mem[i]);
    }
    CHECK(h.fpr == r.fpr);
    CHECK(h.fcr31 == r.fcr31);
    CHECK(h.hi[0] == r.hi[0]);
    CHECK(h.lo[0] == r.lo[0]);
    CHECK(h.hi[1] == r.hi[1]);
    CHECK(h.lo[1] == r.lo[1]);
    return Res{h.o, r.o, r.fpr[0]};
}

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
u8 load8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
void store8(Machine& m, u32 va, u8 v) { m.at(va)[0] = v; }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
bool chance(std::mt19937& rng, u32 percent) { return rng() % 100 < percent; }
// A 64-bit argument register: mostly the sign extension of `v`, sometimes garbage in the upper half.
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 85) ? sx(v) : ((static_cast<u64>(rng()) << 32) | v); }

// --- the .TBL files -------------------------------------------------------------------------------------------
std::filesystem::path battle_dir() { return std::filesystem::path(elf_path()).parent_path().parent_path() / "BTL" / "BATTLE"; }

std::vector<std::vector<u8>> read_tbl(const std::string& name) {
    std::ifstream in(battle_dir() / name, std::ios::binary);
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

// What btlTableLoadAll 0x27DE40 does with the 8 loader records of off_692D40 (168 bytes each: name, name_F,
// then up to 20 {u32* dst, u32 size} pairs): each section goes into the image area and its pointer is stored.
// Returns the number of files found beside the ELF (absent ones get random sections of the recorded size).
int load_battle_tables(Machine& m, std::mt19937& rng) {
    constexpr u32 kLoaderRecords = 0x692D40u;
    u32 at = kTables;
    int real = 0;
    for (u32 rec = 0; rec < 8; ++rec) {
        const u32 base = kLoaderRecords + 168 * rec;
        std::string name = m.str(load32(m, base));
        const std::size_t slash = name.find_last_of("/\\");
        if (slash != std::string::npos) name = name.substr(slash + 1);
        for (char& c : name) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        const std::vector<std::vector<u8>> secs = read_tbl(name);
        if (!secs.empty()) ++real;
        for (u32 s = 0; s < 20; ++s) {
            const u32 dst = load32(m, base + 8 + 8 * s);
            const u32 size = load32(m, base + 12 + 8 * s);
            if (dst == 0) break;
            fill_random(m, at, size + 0x400, rng);  // the assertion paths read a little past a section
            if (s < secs.size()) std::memcpy(m.at(at), secs[s].data(), std::min<std::size_t>(secs[s].size(), size + 0x400));
            store32(m, dst, at);
            at = (at + size + 0x400 + 15) & ~15u;
        }
    }
    REQUIRE(at < kAccessoryTable);
    return real;
}

// --- a random world: party records, hero, persona stock, accessory table ----------------------------------------
// Skill ids the datCalc bonuses look for, mixed into the persona and enemy skill lists.
constexpr u32 kInterestingSkills[] = {537, 538, 539, 620, 540, 541, 542, 621, 567, 568, 547, 548, 549, 550, 551, 552,
                                      607, 608, 544, 545, 546};
constexpr u32 kInterestingEffects[] = {26, 27, 28, 29, 30, 142, 31, 32, 33, 34, 35, 143};

u32 random_skill(std::mt19937& rng) {
    return chance(rng, 40) ? kInterestingSkills[rng() % std::size(kInterestingSkills)] : rng() % 700;
}
u32 equip_index_va(u32 pc) { return pc == 1 ? kHeroEquipment : kPartyEquipment + kPartyRecordSize * pc; }
u32 party_record_va(u32 pc) { return kPartyRecords + (pc - 2) * kPartyRecordSize; }

void random_persona(Machine& m, u32 va, std::mt19937& rng) {
    fill_random(m, va, 52, rng);
    store16(m, va, static_cast<u16>((load16(m, va) & ~1u) | (chance(rng, 90) ? 1u : 0u)));
    store16(m, va + 2, static_cast<u16>(chance(rng, 50) ? 192 + rng() % 32 : rng() % (chance(rng, 95) ? 256 : 0x10000)));
    store8(m, va + 4, static_cast<u8>(chance(rng, 95) ? 1 + rng() % 99 : (chance(rng, 50) ? 0 : rng())));
    for (u32 i = 0; i < 8; ++i) store16(m, va + 12 + 2 * i, static_cast<u16>(random_skill(rng)));
    for (u32 i = 0; i < 5; ++i) store8(m, va + 28 + i, static_cast<u8>(chance(rng, 90) ? rng() % 100 : rng()));
}

void random_equipment_entries(Machine& m, u32 va, u32 n, std::mt19937& rng) {
    for (u32 i = 0; i < n; ++i) {
        const u32 e = va + 20 * i;
        fill_random(m, e, 20, rng);
        store16(m, e, static_cast<u16>(chance(rng, 50) ? 3000 + rng() % 1000 : rng()));
        store8(m, e + 9, static_cast<u8>(chance(rng, 60) ? kInterestingEffects[rng() % std::size(kInterestingEffects)] : rng()));
    }
}

void random_world(Machine& m, std::mt19937& rng) {
    fill_random(m, 0x833000u, 0x8000u, rng);
    for (u32 pc = 2; pc <= 10; ++pc) {
        const u32 rec = party_record_va(pc);
        const u32 unit = rec + 4;
        store16(m, unit, static_cast<u16>(load16(m, unit) & ~kUnitFlagEnemy));
        store16(m, unit + 2, static_cast<u16>(chance(rng, 90) ? pc : rng() % 12));
        for (u32 slot = 0; slot < 4; ++slot)
            store16(m, equip_index_va(pc) + 2 * slot, static_cast<u16>(chance(rng, 85) ? rng() % 6 : (chance(rng, 50) ? 0xFFFFu : rng())));
        random_equipment_entries(m, kPartyEquipment + kPartyRecordSize * pc + 8, 6, rng);
        random_persona(m, rec + 220, rng);
    }
    store16(m, kHeroUnit, static_cast<u16>(load16(m, kHeroUnit) & ~kUnitFlagEnemy));
    store16(m, kHeroUnit + 2, 1);
    store8(m, kHeroUnit + 6, static_cast<u8>(chance(rng, 95) ? 1 + rng() % 99 : 0));
    for (u32 slot = 0; slot < 4; ++slot)
        store16(m, kHeroEquipment + 2 * slot, static_cast<u16>(chance(rng, 85) ? rng() % 8 : (chance(rng, 50) ? 0xFFFFu : rng() % 64)));
    store32(m, 0x836794u, kHeroEquip);
    random_equipment_entries(m, kHeroEquip, 64, rng);
    random_equipment_entries(m, 0x833E80u, 8, rng);  // owner -1: the shared stock
    store16(m, kHeroPersonaIdx, static_cast<u16>(chance(rng, 90) ? rng() % 12 : (chance(rng, 50) ? 0xFFFFu : rng() % 40)));
    for (u32 s = 0; s < 12; ++s) random_persona(m, kHeroPersonaStock + 52 * s, rng);
    store32(m, kPersonaStockFlags, chance(rng, 80) ? pick(rng, {0u, 4u, 2u, 1u, 0x2000u, 0x1000u, 0x3000u, 6u}) : rng());
    // Accessory records: the +28 word is the skill an accessory grants.
    for (u32 i = 0; i < 1000; ++i) {
        const u32 r = kAccessoryTable + 36 * i;
        fill_random(m, r, 36, rng);
        store32(m, r + 28, chance(rng, 70) ? random_skill(rng) : rng());
    }
    store32(m, kAccessoryTablePtr, kAccessoryTable);
}

// A random DatUnit at `va`: an enemy with a valid (mostly) id, or a party member 1..10 (mostly).
void random_unit_at(Machine& m, u32 va, std::mt19937& rng, bool enemy) {
    fill_random(m, va, 60, rng);
    u16 flags = load16(m, va);
    flags = enemy ? static_cast<u16>(flags | kUnitFlagEnemy) : static_cast<u16>(flags & ~kUnitFlagEnemy);
    store16(m, va, flags);
    const u32 id = enemy ? (chance(rng, 95) ? rng() % kEnemyCount : kEnemyCount + rng() % 64)
                         : (chance(rng, 92) ? 1 + rng() % 10 : pick(rng, {0u, 11u, 12u, 15u}));
    store16(m, va + 2, static_cast<u16>(id));
    store8(m, va + 6, static_cast<u8>(chance(rng, 95) ? 1 + rng() % 99 : 0));
}
u32 random_unit(Machine& m, std::mt19937& rng, unsigned slot) {
    const u32 va = kUnits + (slot % 16) * kUnitStride;
    random_unit_at(m, va, rng, chance(rng, 50));
    return va;
}
// The arguments of the unit readers: an arena unit, or one of the real party units of the world.
u32 some_unit(Machine& m, std::mt19937& rng, unsigned slot) {
    if (chance(rng, 20)) {
        const u32 pc = 1 + rng() % 10;
        return pc == 1 ? kHeroUnit : party_record_va(pc) + 4;
    }
    return random_unit(m, rng, slot);
}

// The signed nibble of a buff slot, independently of both bodies (21_battle.md section 2.2).
s32 host_effect_nibble(const Machine& m, u32 unit, u32 slot8) {
    const u8 byte = load8(m, unit + 0x1C + (slot8 >> 1));
    s32 v = (slot8 & 1) ? (byte >> 4) : (byte & 0xF);
    if (v >= 8) v -= 15;
    return v;
}

// --- a random battle: gBtl, the action list, btlUnits, order lists, packet lists ----------------------------------
struct Battle {
    u32 n_actions = 0;
    u32 actions[8] = {};
};

Battle random_battle(Machine& m, std::mt19937& rng) {
    Battle b;
    fill_random(m, kGBtl, kGBtlSize, rng);
    store32(m, kBtlPtr, kGBtl);
    for (u32 i = 0; i < 16; ++i) random_unit(m, rng, i);
    b.n_actions = rng() % 9;
    for (u32 i = 0; i < 8; ++i) {
        const u32 a = kActions + i * kActStride;
        const u32 bu = kBtlUnits + i * kBuStride;
        fill_random(m, a, kActStride, rng);
        fill_random(m, bu, kBuStride, rng);
        store32(m, a + 48, bu);
        store8(m, a + 40, static_cast<u8>(chance(rng, 80) ? 0 : rng()));
        store8(m, a + 41, static_cast<u8>(chance(rng, 80) ? 0 : rng()));
        store8(m, bu + 162, static_cast<u8>(rng() % 2));  // only sides 0 and 1: a third side makes sub_29A690 swap forever (as the original would)
        store16(m, bu + 164, static_cast<u16>(pick(rng, {241u, 261u, 262u, 1u, rng() % 400})));
        store32(m, bu + 2604, kUnits + (rng() % 16) * kUnitStride);
        store32(m, bu + 2612, i + 1 < 8 && chance(rng, 85) ? bu + kBuStride : 0);
        b.actions[i] = a;
    }
    // The action list from gBtl+0x14C through +1192 (+1188 back), in a random order.
    u32 order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    std::shuffle(order, order + 8, rng);
    u32 prev = 0;
    store32(m, kGBtl + 332, b.n_actions ? b.actions[order[0]] : 0);
    for (u32 i = 0; i < b.n_actions; ++i) {
        const u32 a = b.actions[order[i]];
        store32(m, a + 1188, prev);
        store32(m, a + 1192, i + 1 < b.n_actions ? b.actions[order[i + 1]] : 0);
        prev = a;
    }
    // The two 12-slot order lists: a prefix of actions, zeros after (sometimes a hole).
    for (u32 list : {596u, 644u}) {
        const u32 n = rng() % 13;
        for (u32 i = 0; i < 12; ++i) store32(m, kGBtl + list + 4 * i, i < n ? b.actions[rng() % 8] : 0);
        if (n > 2 && chance(rng, 10)) store32(m, kGBtl + list + 4 * (rng() % n), 0);
    }
    // btlMainCheckBattleEnd's helpers: the encounter id (never the two that call into the boss scripts), the
    // btlUnit list of the boss rule, and sub_45AF40's pointer chain.
    store32(m, kGBtl + 3004, kEncounter);
    fill_random(m, kEncounter, 16, rng);
    store16(m, kEncounter + 8, static_cast<u16>(pick(rng, {420u, 436u, 1u, 0u, 100u + rng() % 300})));
    store32(m, kGBtl + 344, chance(rng, 90) ? kBtlUnits + (rng() % 8) * kBuStride : 0);
    if (chance(rng, 70)) {
        store32(m, kQueryPtr, kQuery);
        store32(m, kQuery + 60, kQuery + 0x40);
        store32(m, kQuery + 0x40 + 80, chance(rng, 70) ? 1 : 0);
    } else {
        store32(m, kQueryPtr, 0);
    }
    // The four packet lists at gBtl+0x174 (8-byte heads), linked through +124.
    for (u32 p = 0; p < 16; ++p) fill_random(m, kPackets + p * kPacketStride, kPacketStride, rng);
    u32 next_packet = 0;
    for (u32 l = 0; l < 4; ++l) {
        const u32 n = rng() % 5;
        u32 head = 0, last = 0;
        for (u32 i = 0; i < n && next_packet < 16; ++i) {
            const u32 p = kPackets + (next_packet++) * kPacketStride;
            store32(m, p + 124, 0);
            if (last) store32(m, last + 124, p); else head = p;
            last = p;
        }
        store32(m, kGBtl + 372 + 8 * l, head);
    }
    return b;
}

}  // namespace

// =================================================================================================================

TEST_CASE("game(battle_data): the loader records, the source-file strings and the documented constants") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{1u};
    const int real = load_battle_tables(m, rng);
    MESSAGE("battle .TBL files beside the ELF: " << real << " of 8");
    CHECK(m.str(kDatUnitSourceFile) == "datUnit.c");
    CHECK(m.str(kDatScriptSourceFile) == "datScript.c");
    CHECK(m.str(kDatPersonaSourceFile) == "datPersona.c");
    // The loader records name the eight battle tables and store SKILL.TBL section 1 at gp-0x48F8.
    CHECK(load32(m, kSkillTablePtr) != 0);
    CHECK(load32(m, kUnitTablePtr) != 0);
    CHECK(load32(m, kAicalc5Ptr) != 0);
    CHECK(load32(m, kEncountSec1Ptr) != 0);
    CHECK(load32(m, kEncountSec2Ptr) != 0);
    CHECK(load32(m, kPersonaNamesPtr) != 0);
    CHECK(load32(m, kPersonaAffinityPtr) != 0);
    if (real == 8) {
        // UNIT.TBL record 1 is "Cowardly Maya" (MSG.TBL section 2, 19-byte names), level and HP from the record.
        CHECK(m.str(load32(m, 0x7CE4E8u) + 19) == "Cowardly Maya");
        const u32 rec1 = load32(m, kUnitTablePtr) + kEnemyRecordSize;
        CHECK(load8(m, rec1 + 3) > 0);
        CHECK(load16(m, rec1 + 4) > 0);
        // MSG.TBL section 3: persona 1 has a printable name.
        const std::string p1 = m.str(load32(m, kPersonaNamesPtr) + 17);
        CHECK(!p1.empty());
        CHECK(p1.size() < 17);
    }
    // The growth table rows are 44 bytes: 11 x {u16 hp, u16 sp}; HP grows with the level for every member.
    for (u32 pc = 1; pc <= 10; ++pc) CHECK(load16(m, kGrowthTable + 44 * 99 + 4 * pc) >= load16(m, kGrowthTable + 44 * 1 + 4 * pc));
}

TEST_CASE("game(battle_data): the datUnit.c genus leaves equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{2u};
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kGenusReady, 8, rng);
        if (chance(rng, 30)) store8(m, kGenusReady, 0);
        const u32 seed = rng();
        const u32 v = rng();
        pair(m, PAIR(fn_sub_2FF2D0_002ff2d0), Args{wide(rng, v)}, seed, "sub_2FF2D0");
        CHECK(load8(m, kGenusReady) == 1);
        CHECK(load16(m, kGenusReadyA) == 0);
        CHECK(load16(m, kGenusReadyArg) == (v & 0xFFFFu));
        fill_random(m, kGenusReady, 8, rng);
        pair(m, PAIR(fn_sub_2FF2F0_002ff2f0), Args{}, seed, "sub_2FF2F0");
        CHECK(load16(m, kGenusReadyArg) == 0);
        fill_random(m, kGenusReady, 8, rng);
        if (chance(rng, 50)) store8(m, kGenusReady, 0);
        Res r = pair(m, PAIR(fn_datUnitIsGenusReady_002ff320), Args{}, seed, "datUnitIsGenusReady");
        CHECK(r.hand.v0 == (load8(m, kGenusReady) != 0 ? 1u : 0u));
        r = pair(m, PAIR(fn_sub_2FF310_002ff310), Args{}, seed, "sub_2FF310");
        CHECK(r.hand.v0 == 1);
        r = pair(m, PAIR(fn_sub_2FF330_002ff330), Args{}, seed, "sub_2FF330");
        CHECK(r.hand.v0 == 0);
    }
}

TEST_CASE("game(battle_data): datUnitEcRemoveEnemy and datUnitIsGenusDead equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{3u};
    int removed = 0, dead = 0, alive = 0;
    for (int it = 0; it < 3000; ++it) {
        fill_random(m, kGenusUnits, 6 * 60, rng);
        const u32 kind = chance(rng, 80) ? 1u : pick(rng, {0u, 2u, rng() & 0xFFFFu});
        const u32 count = chance(rng, 85) ? rng() % 7 : 7 + rng() % 4;
        store16(m, kGenus, static_cast<u16>(kind));
        store16(m, kGenus + 2, static_cast<u16>(count));
        store32(m, kGenus + 4, kGenusUnits);
        for (u32 i = 0; i < 6; ++i) {
            const u32 u = kGenusUnits + 60 * i;
            store16(m, u + 2, static_cast<u16>(chance(rng, 30) ? 0 : 1 + rng() % 335));
            store16(m, u + 8, static_cast<u16>(chance(rng, 50) ? 0 : rng() % 50));
            store32(m, u + 12, load32(m, u + 12) & (chance(rng, 70) ? ~0x80000u : ~0u));
        }
        const u32 seed = rng();
        // The removed unit: one of the six slots, a non-slot address, or a slot with garbage in the upper word.
        const u32 slot = rng() % 8;
        const u32 target = slot < 6 ? kGenusUnits + 60 * slot : kGenusUnits + 60 * slot + 4;
        const u64 arg = chance(rng, 90) ? sx(target) : (static_cast<u64>(rng() | 1u) << 32) | target;
        const u16 before_count = load16(m, kGenus + 2);
        pair(m, PAIR(fn_datUnitEcRemoveEnemy_002ff660), Args{kGenus, arg}, seed, "datUnitEcRemoveEnemy");
        if (slot < 6 && arg == sx(target)) {
            CHECK(load16(m, target + 2) == 0);
            CHECK(load16(m, kGenus + 2) == static_cast<u16>(before_count - 1));
            ++removed;
        }
        // IsGenusDead on the same genus; a party genus (kind != 1) points at one unit.
        if (kind != 1 && chance(rng, 50)) store16(m, kGenus + 2, 1);
        const Res r = pair(m, PAIR(fn_datUnitIsGenusDead_002ff790), Args{kGenus}, seed, "datUnitIsGenusDead");
        bool expect;
        auto is_dead = [&](u32 u) {
            return (load32(m, u + 12) & kStatusDead) != 0 || static_cast<s32>(load16(m, u + 8)) <= 0;
        };
        if (kind == 1) {
            expect = true;
            for (u32 i = 0; i < 6; ++i) {
                const u32 u = kGenusUnits + 60 * i;
                if (load16(m, u + 2) != 0 && !is_dead(u)) expect = false;
            }
        } else {
            expect = is_dead(kGenusUnits);
        }
        CHECK(r.hand.v0 == (expect ? 1u : 0u));
        (expect ? dead : alive)++;
    }
    CHECK(removed > 1000);
    CHECK(dead > 300);
    CHECK(alive > 300);
}

TEST_CASE("game(battle_data): datUnitInit equals its recompiled body (party, enemy from UNIT.TBL, bad kinds)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{4u};
    load_battle_tables(m, rng);
    const u32 table = load32(m, kUnitTablePtr);
    int enemies = 0, evade = 0;
    for (int it = 0; it < 3000; ++it) {
        const u32 unit = random_unit(m, rng, it);
        const u32 kind = chance(rng, 90) ? pick(rng, {0u, 1u}) : pick(rng, {2u, 0x101u, 0x100u, rng()});
        const u32 id = (kind & 0xFF) == 1 ? (chance(rng, 95) ? rng() % kEnemyCount : rng() % 0x10000) : (chance(rng, 90) ? rng() % 11 : rng());
        pair(m, PAIR(fn_datUnitInit_002ff890), Args{unit, wide(rng, kind), wide(rng, id)}, rng(), "datUnitInit");
        CHECK(load16(m, unit + 2) == (id & 0xFFFFu));
        CHECK(load16(m, unit + 4) == (id & 0xFFFFu));
        CHECK((load16(m, unit) & 1u) != 0);
        CHECK((load32(m, unit + 0x14) & 0x1FFFFFu) == 0);  // every buff slot cleared
        if ((kind & 0xFF) == 1 && (id & 0xFFFF) < kEnemyCount) {
            const u32 rec = table + (id & 0xFFFF) * kEnemyRecordSize;
            CHECK(load8(m, unit + 6) == load8(m, rec + 3));
            CHECK(load16(m, unit + 8) == load16(m, rec + 4));
            CHECK(load16(m, unit + 10) == load16(m, rec + 6));
            CHECK(load32(m, unit + 12) == 0);
            CHECK((load16(m, unit) & kUnitFlagEnemy) != 0);
            bool has_evade = false;
            for (u32 s = 0; s < 8; ++s) {
                const u32 sk = load16(m, rec + 14 + 2 * s);
                has_evade = has_evade || sk == 544 || sk == 545 || sk == 546;
            }
            CHECK(((load16(m, unit) & 0x200u) != 0) == has_evade);
            ++enemies;
            evade += has_evade ? 1 : 0;
        } else if ((kind & 0xFF) == 0) {
            CHECK((load16(m, unit) & (kUnitFlagEnemy | 0x30u)) == 0);
        }
    }
    CHECK(enemies > 1200);
    MESSAGE("datUnitInit: " << enemies << " enemy inits, " << evade << " with an evade skill");
}

TEST_CASE("game(battle_data): datCalcRand equals its recompiled body (the n == 100 re-roll, divu by any n)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{5u};
    int rerolls = 0;
    for (int it = 0; it < 4000; ++it) {
        fill_random(m, kRandState, 16, rng);
        store32(m, kRandPrev, chance(rng, 90) ? rng() % 100 : rng());
        u64 n;
        switch (it % 6) {
        case 0: case 1: case 2: n = 100; break;
        case 3: n = sx(1 + rng() % 1000); break;
        case 4: n = chance(rng, 50) ? 0 : sx(rng()); break;
        default: n = (static_cast<u64>(rng()) << 32) | pick(rng, {100u, 7u, 60u, 11u}); break;
        }
        const Res r = pair(m, PAIR(fn_datCalcRand_002ffbc0), Args{n}, rng(), "datCalcRand");
        if (n == 100) {
            CHECK(r.hand.v0 < 100);
            CHECK(load32(m, kRandPrev) == r.hand.v0);
            if (r.hand.cycles > 60) ++rerolls;  // the second draw costs another two effMiscRand calls
        }
    }
    CHECK(rerolls > 50);
}

TEST_CASE("game(battle_data): the g_data / datPersona.c record readers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{6u};
    load_battle_tables(m, rng);
    int named = 0, accessories = 0, hero_null = 0;
    for (int it = 0; it < 1500; ++it) {
        random_world(m, rng);
        const u32 seed = rng();
        const u32 pc = chance(rng, 92) ? 1 + rng() % 10 : pick(rng, {0u, 11u, 12u, rng() % 40});
        const u32 slot = chance(rng, 90) ? rng() % 4 : rng() % 16;
        Res r = pair(m, PAIR(fn_datGetEquipmentIdx_0016cb80), Args{wide(rng, pc), wide(rng, slot)}, seed, "datGetEquipmentIdx");
        if (pc >= 1 && pc <= 10 && slot < 4) CHECK(r.hand.v0 == sx(static_cast<u32>(static_cast<s16>(load16(m, equip_index_va(pc) + 2 * slot)))));
        if (pc >= 1 && pc <= 10) {
            pair(m, PAIR(fn_sub_16CC00_0016cc00), Args{wide(rng, pc)}, seed, "sub_16CC00 (growth hp)");
            pair(m, PAIR(fn_sub_16CCB0_0016ccb0), Args{wide(rng, pc)}, seed, "sub_16CCB0 (growth sp)");
        }
        r = pair(m, PAIR(fn_datGetUnit_0016cd60), Args{wide(rng, pc)}, seed, "datGetUnit");
        if (pc >= 2 && pc <= 10) CHECK(r.hand.v0 == party_record_va(pc) + 4);
        if (pc == 1) CHECK(r.hand.v0 == kHeroUnit);
        // Equipment entries: owner -1 (stock), 1 (hero), a member, a bank (>= 256).
        const u32 owner = pick(rng, {0xFFFFFFFFu, 1u, 2 + rng() % 9, 256 + rng() % 64, rng() % 11});
        const u32 idx = chance(rng, 90) ? rng() % 6 : rng() % 64;
        r = pair(m, PAIR(fn_sub_16F630_0016f630), Args{wide(rng, owner), wide(rng, idx)}, seed, "sub_16F630 (item id)");
        if (owner == 0xFFFFFFFFu) CHECK(r.hand.v0 == load16(m, 0x833E80u + 20 * idx));
        if (owner == 1) CHECK(r.hand.v0 == load16(m, kHeroEquip + 20 * idx));
        r = pair(m, PAIR(fn_sub_16F900_0016f900), Args{wide(rng, owner), wide(rng, idx)}, seed, "sub_16F900 (effect)");
        if (owner >= 2 && owner <= 10) CHECK(r.hand.v0 == load8(m, kPartyEquipment + kPartyRecordSize * owner + 8 + 20 * idx + 9));
        const u32 item = chance(rng, 50) ? 2990 + rng() % 1020 : rng();
        r = pair(m, PAIR(fn_sub_170E40_00170e40), Args{wide(rng, item)}, seed, "sub_170E40 (accessory record)");
        const s32 item16 = static_cast<s16>(item & 0xFFFF);
        CHECK(r.hand.v0 == (item16 >= 3000 && item16 < 4000 ? kAccessoryTable + 36u * static_cast<u32>(item16 - 3000) : 0u));
        accessories += r.hand.v0 != 0 ? 1 : 0;
        const u32 persona_id = chance(rng, 90) ? rng() % 256 : rng();
        r = pair(m, PAIR(fn_sub_173220_00173220), Args{wide(rng, persona_id)}, seed, "sub_173220 (persona name)");
        CHECK(r.hand.v0 == load32(m, kPersonaNamesPtr) + 17u * (persona_id & 0xFFFF));
        named += (persona_id & 0xFFFF) < 256 ? 1 : 0;
        // Persona records: a member's, the hero's stock slots, the stock size.
        const u32 persona = pc >= 2 && pc <= 10 ? party_record_va(pc) + 220 : kHeroPersonaStock + 52 * (rng() % 12);
        r = pair(m, PAIR(fn_sub_1732F0_001732f0), Args{persona}, seed, "sub_1732F0 (persona level)");
        CHECK(r.hand.v0 == load8(m, persona + 4));
        r = pair(m, PAIR(fn_datPersonaGetByPcId_00174800), Args{wide(rng, pc)}, seed, "datPersonaGetByPcId");
        if (pc >= 2 && pc <= 10) CHECK(r.hand.v0 == party_record_va(pc) + 220);
        if (pc == 1 && r.hand.v0 == 0) ++hero_null;
        pair(m, PAIR(fn_sub_173380_00173380), Args{wide(rng, pc)}, seed, "sub_173380 (skill list)");
        const u32 element = chance(rng, 90) ? rng() % 16 : rng();
        pair(m, PAIR(fn_sub_1733B0_001733b0), Args{persona, wide(rng, element)}, seed, "sub_1733B0 (persona affinity)");
        pair(m, PAIR(fn_sub_173460_00173460), Args{wide(rng, pc), wide(rng, element)}, seed, "sub_173460 (affinity by pc)");
        const u32 stat = chance(rng, 90) ? rng() % 5 : rng();
        r = pair(m, PAIR(fn_sub_173510_00173510), Args{wide(rng, pc), wide(rng, stat)}, seed, "sub_173510 (base stat)");
        if (pc >= 2 && pc <= 10 && (stat & 0xFFFF) < 5) CHECK(r.hand.v0 == load8(m, party_record_va(pc) + 220 + 28 + (stat & 0xFFFF)));
        r = pair(m, PAIR(fn_sub_1738D0_001738d0), Args{wide(rng, pc), wide(rng, stat)}, seed, "sub_1738D0 (persona stat)");
        CHECK(r.hand.v0 <= 99);
        const u32 stock_slot = chance(rng, 85) ? rng() % 12 : pick(rng, {0xFFFFFFFFu, 12u, 40u, rng()});
        r = pair(m, PAIR(fn_sub_174A90_00174a90), Args{wide(rng, stock_slot)}, seed, "sub_174A90 (hero persona slot)");
        if ((stock_slot & 0xFFFF) < 12) {
            const u32 at = kHeroPersonaStock + 52 * (stock_slot & 0xFFFF);
            CHECK(r.hand.v0 == ((load16(m, at) & 1) ? at : 0u));
        }
        r = pair(m, PAIR(fn_sub_175410_00175410), Args{}, seed, "sub_175410 (stock size)");
        const u32 w = load32(m, kPersonaStockFlags);
        const u32 size = (w & 4) ? 12 : (w & 2) ? 10 : (w & 1) ? 9 : (w & 0x2000) ? 8 : (w & 0x1000) ? 6 : 4;
        CHECK(r.hand.v0 == size);
    }
    CHECK(named > 1200);
    CHECK(accessories > 300);
    MESSAGE("hero persona slot empty (datPersonaGetByPcId asserts and returns 0): " << hero_null);
}

TEST_CASE("game(battle_data): the datCalc.c unit readers equal their recompiled bodies (level, stats, skills, equipment)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{7u};
    load_battle_tables(m, rng);
    int has_skill = 0;
    for (int it = 0; it < 1500; ++it) {
        random_world(m, rng);
        const u32 seed = rng();
        const u32 unit = some_unit(m, rng, it);
        const bool enemy = (load16(m, unit) & kUnitFlagEnemy) != 0;
        Res r = pair(m, PAIR(fn_datCalcGetLevel_002ffcc0), Args{unit}, seed, "datCalcGetLevel");
        if (enemy || load16(m, unit + 2) == 1) CHECK(r.hand.v0 == load8(m, unit + 6));
        // A skill the unit has (its list or its accessory), or a random one.
        u32 skill = random_skill(rng);
        if (enemy && chance(rng, 40) && load16(m, unit + 2) < kEnemyCount)
            skill = load16(m, load32(m, kUnitTablePtr) + load16(m, unit + 2) * kEnemyRecordSize + 14 + 2 * (rng() % 8));
        r = pair(m, PAIR(fn_datCalcHasSkill_003005e0), Args{unit, wide(rng, skill)}, seed, "datCalcHasSkill");
        has_skill += static_cast<int>(r.hand.v0);
        const u32 effect = chance(rng, 70) ? kInterestingEffects[rng() % std::size(kInterestingEffects)] : rng();
        const u32 pc = chance(rng, 92) ? 1 + rng() % 10 : pick(rng, {0u, 11u, rng() % 30});
        pair(m, PAIR(fn_sub_300750_00300750), Args{wide(rng, pc), wide(rng, effect)}, seed, "sub_300750 (equipment effect)");
        r = pair(m, PAIR(fn_datCalcCountEquipmentWithEffect_003009a0), Args{unit, wide(rng, effect)}, seed, "datCalcCountEquipmentWithEffect");
        CHECK(r.hand.v0 <= 3);
        if (enemy) CHECK(r.hand.v0 == 0);
        const u32 stat = chance(rng, 90) ? rng() % 5 : rng();
        r = pair(m, PAIR(fn_sub_300B60_00300b60), Args{unit, wide(rng, stat)}, seed, "sub_300B60 (base stat)");
        CHECK(r.hand.v0 >= 1);
        CHECK(r.hand.v0 <= 99);
        r = pair(m, PAIR(fn_datCalcGetStat_00300c90), Args{unit, wide(rng, stat)}, seed, "datCalcGetStat");
        CHECK(r.hand.v0 >= 1);
        CHECK(r.hand.v0 <= 99);
        r = pair(m, PAIR(fn_datCalcGetPassiveSkillFlags_00300d80), Args{unit}, seed, "datCalcGetPassiveSkillFlags");
        CHECK(r.hand.v0 < 256);
    }
    CHECK(has_skill > 200);
}

TEST_CASE("game(battle_data): datCalcGetMaxHp/MaxSp and datCalcAddHp/AddSp equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{8u};
    load_battle_tables(m, rng);
    int capped = 0;
    for (int it = 0; it < 1500; ++it) {
        random_world(m, rng);
        const u32 seed = rng();
        const u32 unit = some_unit(m, rng, it);
        const bool enemy = (load16(m, unit) & kUnitFlagEnemy) != 0;
        Res r = pair(m, PAIR(fn_datCalcGetMaxHp_002ffdf0), Args{unit}, seed, "datCalcGetMaxHp");
        if (r.faulted) continue;  // an impossible persona pointer in the random world: the original faults as well
        if (!enemy) CHECK(r.hand.v0 <= 999);
        capped += r.hand.v0 == 999 ? 1 : 0;
        const u32 max_hp = static_cast<u32>(r.hand.v0);
        r = pair(m, PAIR(fn_datCalcGetMaxSp_00300100), Args{unit}, seed, "datCalcGetMaxSp");
        if (r.faulted) continue;
        if (!enemy) CHECK(r.hand.v0 <= 999);
        const u32 max_sp = static_cast<u32>(r.hand.v0);
        const s32 delta = pick(rng, {0u, 1u, 0xFFFFFFFFu, rng() % 2000, static_cast<u32>(-static_cast<s32>(rng() % 2000)), rng()});
        const u16 hp0 = load16(m, unit + 8);
        r = pair(m, PAIR(fn_datCalcAddHp_00300410), Args{unit, sx(static_cast<u32>(delta))}, seed, "datCalcAddHp");
        s32 expect = static_cast<s32>(hp0 + static_cast<u32>(delta));
        if (expect < 0) expect = 0;
        if (expect > static_cast<s32>(max_hp)) expect = static_cast<s32>(max_hp);
        CHECK(load16(m, unit + 8) == static_cast<u16>(expect));
        CHECK(r.hand.v0 == static_cast<u16>(expect));
        const u16 sp0 = load16(m, unit + 10);
        r = pair(m, PAIR(fn_datCalcAddSp_00300480), Args{unit, sx(static_cast<u32>(delta))}, seed, "datCalcAddSp");
        expect = static_cast<s32>(sp0 + static_cast<u32>(delta));
        if (expect < 0) expect = 0;
        if (expect > static_cast<s32>(max_sp)) expect = static_cast<s32>(max_sp);
        CHECK(load16(m, unit + 10) == static_cast<u16>(expect));
    }
    MESSAGE("datCalcGetMaxHp at the 999 cap: " << capped << "; pairs where both bodies fault alike: " << g_faulted_pairs);
}

TEST_CASE("game(battle_data): the buff-slot writers and datCalcGetEffectMultiplier equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{9u};
    load_battle_tables(m, rng);
    int set_checked = 0, boosted = 0;
    for (int it = 0; it < 2500; ++it) {
        const u32 unit = random_unit(m, rng, it);
        const u32 seed = rng();
        const u32 slot = chance(rng, 85) ? rng() % 21 : (chance(rng, 50) ? 21 + rng() % 30 : rng());
        const u32 slot8 = slot & 0xFF;
        const s32 level = chance(rng, 85) ? static_cast<s32>(rng() % 15) - 7 : static_cast<s32>(rng());
        pair(m, PAIR(fn_datCalcSetEffectLevel_00301030), Args{unit, wide(rng, slot), wide(rng, static_cast<u32>(level))}, seed, "datCalcSetEffectLevel");
        if (slot8 < 17 && static_cast<s8>(level) >= -7 && static_cast<s8>(level) <= 7) {
            CHECK(host_effect_nibble(m, unit, slot8) == static_cast<s8>(level));
            ++set_checked;
        }
        const u32 turns = chance(rng, 85) ? rng() % 16 : rng();
        pair(m, PAIR(fn_sub_301150_00301150), Args{unit, wide(rng, slot), wide(rng, turns)}, seed, "sub_301150 (turns)");
        const u32 delta = chance(rng, 85) ? static_cast<u32>(pick(rng, {0u, 1u, 0xFFu, 2u, 0xFEu})) : rng();
        const s32 before = slot8 < 17 ? host_effect_nibble(m, unit, slot8) : 0;
        Res r = pair(m, PAIR(fn_datCalcAddEffectLevel_00301230), Args{unit, wide(rng, slot), wide(rng, delta)}, seed, "datCalcAddEffectLevel");
        if (slot8 < 17) {
            const s32 d = static_cast<s8>(delta & 0xFF);
            if (d == 0) {
                CHECK(r.hand.v0 == sx(static_cast<u32>(before)));
            } else {
                s32 sum = static_cast<s16>(static_cast<u16>(before + d));
                sum = std::clamp(sum, -1, 1);
                CHECK(r.hand.v0 == sx(static_cast<u32>(sum)));
                CHECK(host_effect_nibble(m, unit, slot8) == sum);
                CHECK(((load32(m, unit + 0x14) >> slot8) & 1u) == (sum != 0 ? 1u : 0u));
            }
        } else if (slot8 < 21) {
            CHECK(r.hand.v0 == 0);
            CHECK(((load32(m, unit + 0x14) >> slot8) & 1u) == 1u);
        }
        // The multiplier at the current level (slot levels outside -1..1 take the assertion path).
        r = pair(m, PAIR(fn_datCalcGetEffectMultiplier_00301880), Args{unit, wide(rng, slot)}, seed, "datCalcGetEffectMultiplier");
        boosted += r.f0 != ee::fpu::kOne ? 1 : 0;
        pair(m, PAIR(fn_datCalcClearEffect_00301540), Args{unit, wide(rng, slot)}, seed, "datCalcClearEffect");
        if (slot8 < 17) CHECK(host_effect_nibble(m, unit, slot8) == 0);
        if (slot8 < 21) CHECK(((load32(m, unit + 0x14) >> slot8) & 1u) == 0u);
        if (it % 5 == 0) {
            pair(m, PAIR(fn_datCalcClearAllEffects_00301690), Args{unit}, seed, "datCalcClearAllEffects");
            CHECK((load32(m, unit + 0x14) & 0x1FFFFFu) == 0);
            for (u32 s = 0; s < 17; ++s) CHECK(host_effect_nibble(m, unit, s) == 0);
        }
        pair(m, PAIR(fn_sub_301870_00301870), Args{unit}, seed, "sub_301870");
        CHECK(load32(m, unit + 0x18) == 0);
    }
    // Every slot at every legal level of both sides, the attack-type flags on and off.
    for (u32 slot = 0; slot < 24; ++slot) {
        for (s32 level = -2; level <= 2; ++level) {
            for (u32 variant = 0; variant < 4; ++variant) {
                const u32 unit = random_unit(m, rng, slot);
                store16(m, unit, static_cast<u16>((variant & 1) ? (load16(m, unit) | kUnitFlagEnemy) : (load16(m, unit) & ~kUnitFlagEnemy)));
                u32 flags = load32(m, unit + 0x14) & ~0x180000u;
                if (variant & 2) flags |= 0x180000u;
                if (slot >= 17 && slot < 21) flags = level > 0 ? (flags | (1u << slot)) : (flags & ~(1u << slot));
                store32(m, unit + 0x14, flags);
                if (slot < 17) {
                    const u32 at = unit + 0x1C + (slot >> 1);
                    const u32 nib = static_cast<u32>(level < 0 ? level + 15 : level) & 0xF;
                    store8(m, at, static_cast<u8>((slot & 1) ? ((load8(m, at) & 0xF) | (nib << 4)) : ((load8(m, at) & 0xF0) | nib)));
                }
                pair(m, PAIR(fn_datCalcGetEffectMultiplier_00301880), Args{unit, slot}, rng(), "datCalcGetEffectMultiplier (sweep)");
            }
        }
    }
    CHECK(set_checked > 1300);
    CHECK(boosted > 100);
}

TEST_CASE("game(battle_data): the datScript.c context leaves equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{10u};
    load_battle_tables(m, rng);
    for (int it = 0; it < 2000; ++it) {
        fill_random(m, 0x957180u, 0x30, rng);
        const u32 seed = rng();
        Res r = pair(m, PAIR(fn_sub_311180_00311180), Args{}, seed, "sub_311180");
        CHECK(r.hand.v0 == 1);
        const u32 v = rng();
        const u16 flags = load16(m, kDatScriptFlags);
        pair(m, PAIR(fn_datScriptSetResult_00311190), Args{wide(rng, v)}, seed, "datScriptSetResult");
        CHECK(load32(m, kDatScriptResult) == v);
        CHECK(load16(m, kDatScriptFlags) == (flags | 1u));
        const u32 attacker = chance(rng, 90) ? random_unit(m, rng, it) : 0;
        store32(m, kDatScriptAttacker, attacker);
        r = pair(m, PAIR(fn_sub_3111F0_003111f0), Args{}, seed, "sub_3111F0 (attacker not an enemy)");
        if (attacker) CHECK(r.hand.v0 == ((load16(m, attacker) & kUnitFlagEnemy) == 0 ? 1u : 0u));
        store16(m, kDatScriptSkill, static_cast<u16>(chance(rng, 90) ? rng() % kSkillCount : rng()));
        r = pair(m, PAIR(fn_sub_311250_00311250), Args{}, seed, "sub_311250 (physical skill)");
        const u32 skill = load16(m, kDatScriptSkill);
        if (skill < kSkillCount) CHECK(r.hand.v0 == ((load8(m, load32(m, kSkillTablePtr) + skill * kSkillRecordSize) & 2) ? 1u : 0u));
        const u32 word = rng();
        store32(m, kBtlCompareWord, word);
        const u64 key = pick(rng, {0u, 1u, 2u}) == 0 ? sx(word) : wide(rng, chance(rng, 50) ? word : rng());
        r = pair(m, PAIR(fn_sub_3112C0_003112c0), Args{key}, seed, "sub_3112C0");
        CHECK(r.hand.v0 == (key == sx(word) ? 1u : 0u));
    }
}

TEST_CASE("game(battle_data): the btl root helpers and btlMainCheckBattleEnd equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11u};
    load_battle_tables(m, rng);
    random_world(m, rng);
    int outcomes[4] = {};
    for (int it = 0; it < 2500; ++it) {
        const Battle b = random_battle(m, rng);
        const u32 seed = rng();
        // Make deaths and standing units of both sides likely.
        for (u32 i = 0; i < 16; ++i) {
            const u32 u = kUnits + i * kUnitStride;
            store32(m, u + 12, load32(m, u + 12) & (chance(rng, 80) ? ~kStatusDead : ~0u));
            store16(m, u + 8, static_cast<u16>(chance(rng, 30) ? 0 : 1 + rng() % 500));
            if (chance(rng, 15)) store16(m, u + 2, 1);  // the hero
        }
        for (u32 i = 0; i < 8; ++i) {
            const u32 a = b.actions[i];
            store16(m, a + 26, static_cast<u16>(chance(rng, 85) ? (load16(m, a + 26) | 1u) : (load16(m, a + 26) & ~1u)));
            store16(m, a + 24, static_cast<u16>(chance(rng, 85) ? (load16(m, a + 24) & ~0x20u) : (load16(m, a + 24) | 0x20u)));
        }
        Res r = pair(m, PAIR(fn_btlMainCheckBattleEnd_0027d380), Args{}, seed, "btlMainCheckBattleEnd");
        const u32 outcome = load16(m, kGBtl + 28);
        CHECK(outcome <= 3);
        CHECK((r.hand.v0 != 0) == (outcome != 0));
        outcomes[outcome & 3]++;
        // btlGetTask: gBtl or no battle.
        if (chance(rng, 20)) store32(m, kBtlPtr, 0);
        r = pair(m, PAIR(fn_sub_27D880_0027d880), Args{}, seed, "sub_27D880 (btlGetTask)");
        CHECK(r.hand.v0 == (load32(m, kBtlPtr) ? sx(load32(m, kGBtl + 0xD18)) : 0u));
        store32(m, kBtlPtr, kGBtl);
        const u32 f0 = load32(m, kGBtl + 12);
        pair(m, PAIR(fn_sub_27D8B0_0027d8b0), Args{}, seed, "sub_27D8B0");
        CHECK(load32(m, kGBtl + 12) == (f0 | 0x8000u));
        store32(m, kPacketWords, rng());
        const u32 f1 = load32(m, kGBtl + 12);
        r = pair(m, PAIR(fn_sub_27DBE0_0027dbe0), Args{kPacketWords}, seed, "sub_27DBE0 (set flags)");
        CHECK(r.hand.v0 == 1);
        CHECK(load32(m, kGBtl + 12) == (f1 | load32(m, kPacketWords)));
        store32(m, kPacketWords, rng());
        const u32 f2 = load32(m, kGBtl + 12);
        r = pair(m, PAIR(fn_sub_27DC50_0027dc50), Args{kPacketWords}, seed, "sub_27DC50 (clear flags)");
        CHECK(r.hand.v0 == 1);
        CHECK(load32(m, kGBtl + 12) == (f2 & ~load32(m, kPacketWords)));
        // Packet lookups: a key from some packet (often), masks full / partial / zero.
        const u32 p = kPackets + (rng() % 16) * kPacketStride;
        for (u32 field : {88u, 96u}) {
            u64 key;
            std::memcpy(&key, m.at(p + field), 8);
            const u64 mask = pick(rng, {0u, 1u, 2u, 3u}) == 0 ? ~u64{0} : (chance(rng, 50) ? 0xFFFFu : ((static_cast<u64>(rng()) << 32) | rng()));
            key &= mask;
            if (chance(rng, 20)) key = (static_cast<u64>(rng()) << 32) | rng();
            if (chance(rng, 50)) store8(m, p + 71, static_cast<u8>(load8(m, p + 71) | 0x20u));
            if (field == 88) {
                pair(m, PAIR(fn_sub_27E310_0027e310), Args{key, mask}, seed, "sub_27E310 (packet by +88)");
            } else {
                pair(m, PAIR(fn_sub_27E390_0027e390), Args{key, mask}, seed, "sub_27E390 (packet by +96)");
            }
        }
    }
    MESSAGE("battle-end outcomes 0/1/2/3: " << outcomes[0] << " / " << outcomes[1] << " / " << outcomes[2] << " / " << outcomes[3]);
    for (int o = 0; o < 4; ++o) CHECK(outcomes[o] > 50);
}

TEST_CASE("game(battle_data): the btlAction list and the turn-order list helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{12u};
    load_battle_tables(m, rng);
    int found = 0, sorted_checked = 0;
    for (int it = 0; it < 2500; ++it) {
        random_world(m, rng);
        const Battle b = random_battle(m, rng);
        const u32 seed = rng();
        const u32 a = b.actions[rng() % 8];
        pair(m, PAIR(fn_sub_299E30_00299e30), Args{a}, seed, "sub_299E30");
        CHECK((load16(m, a + 24) & 1u) == 1u);
        pair(m, PAIR(fn_sub_299E50_00299e50), Args{a}, seed, "sub_299E50");
        CHECK((load16(m, a + 24) & 1u) == 0u);
        const u32 bu = kBtlUnits + (rng() % 8) * kBuStride;
        pair(m, PAIR(fn_sub_299E70_00299e70), Args{a, bu}, seed, "sub_299E70 (set unit)");
        CHECK(load32(m, a + 48) == bu);
        CHECK((load16(m, a + 26) & 1u) == 1u);
        // List walks by unit / uid.
        const u32 other = b.actions[rng() % 8];
        u64 key = sx(chance(rng, 70) ? load32(m, other + 48) : rng());
        if (chance(rng, 10)) key ^= u64{1} << 40;
        Res r = pair(m, PAIR(fn_sub_29A1D0_0029a1d0), Args{key}, seed, "sub_29A1D0 (action by unit)");
        found += r.hand.v0 != 0 ? 1 : 0;
        key = sx(chance(rng, 70) ? load32(m, other + 8) : rng());
        pair(m, PAIR(fn_sub_29A210_0029a210), Args{key}, seed, "sub_29A210 (action by uid)");
        // Remove from an arbitrary word list.
        const u32 pool[4] = {rng(), rng(), rng(), 0};
        for (u32 i = 0; i < 16; ++i) store32(m, kList + 4 * i, pool[rng() % 4]);
        const u32 count = chance(rng, 90) ? rng() % 15 : 0;
        const u64 item = wide(rng, pool[rng() % 4]);
        r = pair(m, PAIR(fn_sub_29A250_0029a250), Args{kList, sx(count), item}, seed, "sub_29A250 (list remove)");
        // The order lists.
        const u32 act = chance(rng, 80) ? b.actions[rng() % 8] : rng();
        pair(m, PAIR(fn_sub_29A2C0_0029a2c0), Args{act}, seed, "sub_29A2C0 (order add)");
        pair(m, PAIR(fn_sub_29A380_0029a380), Args{act}, seed, "sub_29A380 (order 2 add)");
        r = pair(m, PAIR(fn_sub_29A320_0029a320), Args{sx(act)}, seed, "sub_29A320 (order remove all)");
        for (u32 i = 0; i < 12; ++i) CHECK(load32(m, kGBtl + 596 + 4 * i) != act);
        pair(m, PAIR(fn_sub_29A320_0029a320), Args{wide(rng, b.actions[rng() % 8])}, seed, "sub_29A320 (wide)");
        const u32 act2 = b.actions[rng() % 8];
        store32(m, kGBtl + 12, load32(m, kGBtl + 12) ^ (chance(rng, 50) ? 8u : 0u));
        pair(m, PAIR(fn_sub_29A3E0_0029a3e0), Args{wide(rng, act2)}, seed, "sub_29A3E0");
        const u64 move = wide(rng, chance(rng, 80) ? b.actions[rng() % 8] : rng());
        pair(m, PAIR(fn_sub_29A470_0029a470), Args{move}, seed, "sub_29A470 (move to front)");
        pair(m, PAIR(fn_sub_29A4F0_0029a4f0), Args{move}, seed, "sub_29A4F0 (move to back)");
        // The two sorts (an empty prefix makes the pass bound wrap: keep at least one entry then).
        if (load32(m, kGBtl + 596) == 0) store32(m, kGBtl + 596, b.actions[0]);
        pair(m, PAIR(fn_btlOrderSortByAgility_0029a570), Args{}, seed, "btlOrderSortByAgility");
        u32 n = 0;
        if (load32(m, kGBtl + 596) == 0) store32(m, kGBtl + 596, b.actions[0]);
        const u32 side = rng() % 2;
        pair(m, PAIR(fn_sub_29A690_0029a690), Args{wide(rng, side)}, seed, "sub_29A690 (sort by side)");
        // Host check of the side sort: no unit of another side precedes a unit of `side` within the prefix.
        n = 0;
        while (n < 12 && load32(m, kGBtl + 596 + 4 * n) != 0) ++n;
        bool other_seen = false, ok = true;
        for (u32 i = 0; i < n; ++i) {
            const u32 s = load8(m, load32(m, load32(m, kGBtl + 596 + 4 * i) + 48) + 162);
            if (s != (side & 0xFFFF)) other_seen = true;
            else if (other_seen) ok = false;
        }
        if (n > 0) {
            CHECK(ok);
            ++sorted_checked;
        }
    }
    CHECK(found > 800);
    CHECK(sorted_checked > 1500);
}

TEST_CASE("game(battle_data): the btlAction / btlMain state drivers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{13u};
    load_battle_tables(m, rng);
    // Install known init/update functions in both state tables (hand-written and recompiled ones; sub_299E30 /
    // sub_299E50 use the $a0 the driver passes, sub_45AF40 reads gp-17912, sub_1F1C50 is a non-leaf that spills
    // the $ra it gets into a 16-byte frame below the $sp it gets).
    const u32 targets[] = {0x2FF310u, 0x2FF330u, 0x45AF40u, 0x299E30u, 0x299E50u, 0x2FF320u, 0x1F1C50u};
    // The drivers' 16-byte frame ($ra spilled at 0) is live while the state function runs, and the real state
    // functions run deep call trees in it that read stack bytes they never wrote: so for these three the dead
    // stack must match too (it holds the driver's spill and the state function's frame, i.e. the $sp and $ra it
    // was given), and so must the caller-saved registers the original leaves ($v1, $a0). Before 2026-10-20 the
    // hand versions ran the state functions without the frame (16 bytes higher), which the comparison outside
    // the dead stack could not see; the battle route's heap picked up stale stack bytes shifted by 16.
    int frames_checked = 0;
    const auto driver = [&](Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
        const Snap before = snap(m);
        const Outcome h = run(m, hand, args, seed);
        const u64 h_v1 = m.ctx.gpr[GPR_V1].u64[0], h_a0 = m.ctx.gpr[GPR_A0].u64[0];
        restore(m, before);
        const Outcome r = run(m, recomp, args, seed);
        const u64 r_v1 = m.ctx.gpr[GPR_V1].u64[0], r_a0 = m.ctx.gpr[GPR_A0].u64[0];
        restore(m, before);
        pair(m, hand, recomp, args, seed, what);
        INFO(what);
        CHECK(h.dead_stack == r.dead_stack);
        CHECK(h_v1 == r_v1);
        CHECK(h_a0 == r_a0);
        // Documented rule: the driver's spill at entry $sp - 16 is the caller's $ra (fresh_context: 0x100008).
        u64 spill = 0;
        std::memcpy(&spill, h.dead_stack.data() + kDeadStack - 16, 8);
        CHECK(spill == sx(0x00100008u));
        ++frames_checked;
    };
    int entered = 0;
    for (int it = 0; it < 2500; ++it) {
        const Battle b = random_battle(m, rng);
        for (u32 s = 0; s < 36; ++s) {
            store32(m, kActionStateTbl + 12 * s, targets[rng() % std::size(targets)]);
            store32(m, kActionStateTbl + 12 * s + 4, targets[rng() % std::size(targets)]);
        }
        for (u32 s = 0; s < 20; ++s) {
            store32(m, kMainStateTbl + 12 * s, targets[rng() % std::size(targets)]);
            store32(m, kMainStateTbl + 12 * s + 4, targets[rng() % std::size(targets)]);
        }
        const u32 seed = rng();
        const u32 a = b.actions[rng() % 8];
        const u32 state = (rng() % 36) | (chance(rng, 20) ? rng() << 16 : 0);
        const u16 old = load16(m, a + 12);
        driver(PAIR(fn_btlActionSetState_00299d60), Args{a, wide(rng, state)}, seed, "btlActionSetState");
        CHECK(load16(m, a + 16) == old);
        CHECK(load16(m, a + 12) == (state & 0xFFFF));
        CHECK(load32(m, a + 28) == 0);
        const u32 main_state = rng() % 20;
        driver(PAIR(fn_btlMainSetState_0029de20), Args{wide(rng, main_state)}, seed, "btlMainSetState");
        CHECK(load32(m, kGBtl + 692) == main_state);
        CHECK(load32(m, kGBtl + 700) == 0);
        store32(m, kGBtl + 692, rng() % 20);
        store32(m, kGBtl + 696, chance(rng, 50) ? 0 : rng() % 20);
        if (load32(m, kGBtl + 696) != 0) ++entered;
        const u32 frames = load32(m, kGBtl + 700);
        const bool pending = load32(m, kGBtl + 696) != 0;
        driver(PAIR(fn_btlMainUpdateState_0029de80), Args{}, seed, "btlMainUpdateState");
        CHECK(load32(m, kGBtl + 700) == (pending ? 1u : frames + 1u));
    }
    CHECK(entered > 1000);
    CHECK(frames_checked == 3 * 2500);
}

TEST_CASE("game(battle_data): the k_encount.c floor-layout readers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{14u};
    load_battle_tables(m, rng);
    const u32 sec1 = load32(m, kEncountSec1Ptr);
    const u32 sec2 = load32(m, kEncountSec2Ptr);
    int from1 = 0, from2 = 0;
    for (u32 floor = 0; floor < 100; ++floor) {
        for (int k = 0; k < 12; ++k) {
            const u32 block = k < 4 ? 0u : (k < 8 ? 1u : rng());
            const u32 group = chance(rng, 90) ? rng() % 500 : rng() % 0x10000;
            const u64 f = wide(rng, floor | (chance(rng, 10) ? rng() << 16 : 0));
            const u32 seed = rng();
            const u32 fl = floor;
            const bool b0 = (block & 0xFFFF) == 0;
            const bool s1 = (fl >= 20 && fl < 29 && b0) || (fl >= 40 && fl < 49 && b0) || (fl >= 51 && fl < 59) || (fl >= 71 && fl < 79);
            const bool s2 = !s1 && fl >= 30 && fl < 40;
            const u32 at1[3] = {3, 2, 4};
            const s32 at2[3] = {-5997, -5998, -5996};
            const Fn hands[3] = {&recomp_gen::fn_sub_1D75F0_001d75f0, &recomp_gen::fn_sub_1D76E0_001d76e0, &recomp_gen::fn_sub_1D77D0_001d77d0};
            const Fn recomps[3] = {&recomp_gen::fn_sub_1D75F0_001d75f0__recomp, &recomp_gen::fn_sub_1D76E0_001d76e0__recomp,
                                   &recomp_gen::fn_sub_1D77D0_001d77d0__recomp};
            const char* names[3] = {"sub_1D75F0", "sub_1D76E0", "sub_1D77D0"};
            for (int which = 0; which < 3; ++which) {
                const Res r = pair(m, hands[which], recomps[which], Args{f, wide(rng, block), wide(rng, group)}, seed, names[which]);
                u32 expect = 0;
                if (s1) expect = load8(m, sec1 + 10 * (group & 0xFFFF) + at1[which]);
                if (s2) expect = load8(m, sec2 + static_cast<u32>(200 * static_cast<s32>(fl) + at2[which]));
                CHECK(r.hand.v0 == expect);
            }
            from1 += s1 ? 1 : 0;
            from2 += s2 ? 1 : 0;
        }
    }
    CHECK(from1 > 200);
    CHECK(from2 > 100);
}

#else
TEST_CASE("game(battle_data): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
