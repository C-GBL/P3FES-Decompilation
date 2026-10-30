// Phase 5 pair tests for the battle data leaves (game/src/battle/*.cpp): each hand-written function and
// the recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved
// registers, memory outside the dead stack -- here the arena holding the unit records --, virtual cycles,
// check-point count) on randomised inputs; the documented rules (docs/ANALYSIS/21_battle.md sections 2.2,
// 3.2 and 5) are checked on the host, independently of both bodies: the 999 cap for party members, the
// 20/12 split of the bad-status word, the dead bit, the signed nibbles of the buff slots, the SKILL.TBL
// flags (on the real battle/SKILL.TBL when the extracted tree is beside the ELF) and the status -> element
// map.
#include "pair_harness.h"

#include "p3fes/game/battle.h"

#include <array>
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
P3FES_DECL_PAIR(fn_datCalcGetHp_002ffd70)
P3FES_DECL_PAIR(fn_datCalcGetSp_002ffd80)
P3FES_DECL_PAIR(fn_datCalcSetHp_002ffd90)
P3FES_DECL_PAIR(fn_datCalcSetSp_002ffdc0)
P3FES_DECL_PAIR(fn_datCalcGetBadStatus_00300550)
P3FES_DECL_PAIR(fn_datCalcGetBadStatusNoDown_00300530)
P3FES_DECL_PAIR(fn_datCalcSetBadStatus_003004f0)
P3FES_DECL_PAIR(fn_datCalcClearBadStatus_00300560)
P3FES_DECL_PAIR(fn_datCalcChkBadStatus_00300580)
P3FES_DECL_PAIR(fn_datCalcIsDead_0030b5a0)
P3FES_DECL_PAIR(fn_datCalcGetEffectLevel_00300f60)
P3FES_DECL_PAIR(fn_datCalcGetEffectState_00301750)
P3FES_DECL_PAIR(fn_datCalcIsSkillUsableOnField_00300af0)
P3FES_DECL_PAIR(fn_datCalcIsPhysicalSkill_003088b0)
P3FES_DECL_PAIR(fn_datCalcGetElementBit_003080c0)
P3FES_DECL_PAIR(fn_datCalcGetElementForStatus_00308120)
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

constexpr u32 kUnits = kArena + 0x100;          // eight 64-byte unit records in the arena
constexpr u32 kUnitStride = 64;
constexpr u32 kTableBase = 0x01810000u;         // SKILL.TBL images outside the arena (read-only for the bodies)
constexpr u32 kSection0 = kTableBase;           // { s8 element, u8 } per skill, 1,248 bytes
constexpr u32 kSection1 = kTableBase + 0x1000;  // SkillRecord[464], 20,416 bytes

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
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}

// A random unit record: random bytes everywhere, the enemy flag as asked.
u32 random_unit(Machine& m, std::mt19937& rng, unsigned slot, bool enemy) {
    const u32 va = kUnits + slot * kUnitStride;
    fill_random(m, va, kUnitStride, rng);
    u16 flags = load16(m, va);
    flags = enemy ? static_cast<u16>(flags | kUnitFlagEnemy) : static_cast<u16>(flags & ~kUnitFlagEnemy);
    store16(m, va, flags);
    return va;
}

// battle/SKILL.TBL beside the ELF: the sections are { u32 size, bytes } each starting at the next multiple
// of 16 (docs/ANALYSIS/21_battle.md section 3.1). Returns the sections, or an empty list when absent.
std::vector<std::vector<u8>> read_skill_tbl() {
    const std::filesystem::path path = std::filesystem::path(elf_path()).parent_path().parent_path() / "BTL" / "BATTLE" / "SKILL.TBL";
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

// Put a section-0 and a section-1 image into the guest and point the two table pointers at them; real
// data when available, random bytes otherwise (returns whether the data is real).
bool install_skill_table(Machine& m, std::mt19937& rng) {
    const std::vector<std::vector<u8>> secs = read_skill_tbl();
    const bool real = secs.size() == 3 && secs[0].size() == 0x4E0 && secs[1].size() == 0x4FC0;
    if (real) {
        std::memcpy(m.at(kSection0), secs[0].data(), secs[0].size());
        std::memcpy(m.at(kSection1), secs[1].data(), secs[1].size());
    } else {
        fill_random(m, kSection0, 0x4E0, rng);
        fill_random(m, kSection1, 0x4FC0, rng);
    }
    // The assertion paths read a little past both tables; keep those bytes defined too.
    fill_random(m, kSection0 + 0x4E0, 0x400, rng);
    fill_random(m, kSection1 + 0x4FC0, 0x2000, rng);
    store32(m, kSkillElementTablePtr, kSection0);
    store32(m, kSkillTablePtr, kSection1);
    return real;
}

// The host restatement of the signed nibble rule (21_battle.md section 2.2).
s32 host_effect_nibble(const Machine& m, u32 unit, u32 slot8) {
    const u8 byte = m.mem.main_ram()[unit + 0x1C + (slot8 >> 1)];
    s32 v = (slot8 & 1) ? (byte >> 4) : (byte & 0xF);
    if (v >= 8) v -= 15;
    return v;
}

}  // namespace

TEST_CASE("game(battle): the unit record and the skill table layout are what the doc says") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    CHECK(sizeof(DatUnit) == 60);
    CHECK(sizeof(SkillRecord) == 44);
    CHECK(kSkillCount * kSkillRecordSize == 0x4FC0);   // SKILL.TBL section 1 is exactly 464 records
    CHECK(kEnemyCount * kEnemyRecordSize == 0x5160);   // UNIT.TBL section 0 is exactly 336 records
    CHECK(m.str(kDatCalcSourceFile) == "datCalc.c");
    const std::vector<std::vector<u8>> secs = read_skill_tbl();
    if (secs.empty()) {
        MESSAGE("SKIP: no battle/SKILL.TBL beside the ELF; the table tests run on random images");
        return;
    }
    REQUIRE(secs.size() == 3);
    CHECK(secs[0].size() == 0x4E0);
    CHECK(secs[1].size() == 0x4FC0);
    CHECK(secs[2].size() == 0xC0);
    int physical = 0, field = 0;
    for (u32 id = 0; id < kSkillCount; ++id) {
        const u8* rec = secs[1].data() + id * kSkillRecordSize;
        physical += (rec[0] & 2) ? 1 : 0;
        field += ((rec[0] & 2) == 0 && (rec[1] & 1)) ? 1 : 0;
        CHECK((rec[2] == 0 || rec[2] == 1 || rec[2] == 2));  // HP / SP effect kind
    }
    CHECK(physical == 16);  // the physical attacks (the weapon element applies)
    CHECK(field == 32);     // the skills the field menu may use
}

TEST_CASE("game(battle): datCalcGetHp/GetSp/SetHp/SetSp equal their recompiled bodies and the 999 cap") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{20261020u};
    int capped = 0;
    for (int it = 0; it < 2500; ++it) {
        const bool enemy = (rng() & 1) != 0;
        const u32 unit = random_unit(m, rng, it & 7, enemy);
        const u32 seed = rng();
        Pair p = run_pair(m, PAIR(fn_datCalcGetHp_002ffd70), Args{unit}, seed, "datCalcGetHp");
        CHECK(p.hand.v0 == load16(m, unit + 8));
        p = run_pair(m, PAIR(fn_datCalcGetSp_002ffd80), Args{unit}, seed, "datCalcGetSp");
        CHECK(p.hand.v0 == load16(m, unit + 10));
        // Values around the cap, random 16-bit values and negative / wide words (only the low 16 bits count).
        s32 v;
        switch (it % 5) {
        case 0: v = rand_range(rng, 990, 1010); break;
        case 1: v = rand_range(rng, 0, 65535); break;
        case 2: v = rand_range(rng, -70000, 70000); break;
        case 3: v = static_cast<s32>(rng()); break;
        default: v = rand_range(rng, 0, 999); break;
        }
        const u32 expect = ((static_cast<u32>(v) & 0xFFFFu) < 1000u || enemy) ? (static_cast<u32>(v) & 0xFFFFu) : 999u;
        if (expect == 999u && (static_cast<u32>(v) & 0xFFFFu) != 999u) ++capped;
        p = run_pair(m, PAIR(fn_datCalcSetHp_002ffd90), Args{unit, sx(static_cast<u32>(v))}, seed, "datCalcSetHp", {{unit, 60}});
        CHECK(load16(m, unit + 8) == expect);
        p = run_pair(m, PAIR(fn_datCalcSetSp_002ffdc0), Args{unit, sx(static_cast<u32>(v))}, seed, "datCalcSetSp", {{unit, 60}});
        CHECK(load16(m, unit + 10) == expect);
    }
    CHECK(capped > 300);
}

TEST_CASE("game(battle): the bad-status word accessors equal their recompiled bodies and the 20/12 split") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{3u};
    int replaced = 0;
    for (int it = 0; it < 3000; ++it) {
        const u32 unit = random_unit(m, rng, it & 7, (rng() & 1) != 0);
        const u32 status = load32(m, unit + 12);
        const u32 seed = rng();
        Pair p = run_pair(m, PAIR(fn_datCalcGetBadStatus_00300550), Args{unit}, seed, "datCalcGetBadStatus");
        CHECK(p.hand.v0 == sx(status));
        p = run_pair(m, PAIR(fn_datCalcGetBadStatusNoDown_00300530), Args{unit}, seed, "datCalcGetBadStatusNoDown");
        CHECK(p.hand.v0 == (status & 0xFFFFFu));
        // Masks: single bits, random words, high-only and low-only words.
        u32 bits;
        switch (it % 4) {
        case 0: bits = 1u << (rng() % 32); break;
        case 1: bits = rng(); break;
        case 2: bits = rng() & 0xFFF00000u; break;
        default: bits = rng() & 0x000FFFFFu; break;
        }
        p = run_pair(m, PAIR(fn_datCalcChkBadStatus_00300580), Args{unit, sx(bits)}, seed, "datCalcChkBadStatus");
        CHECK(p.hand.v0 == ((status & bits) != 0 ? 1u : 0u));
        p = run_pair(m, PAIR(fn_datCalcSetBadStatus_003004f0), Args{unit, sx(bits)}, seed, "datCalcSetBadStatus", {{unit, 60}});
        u32 expect = status;
        if ((bits & 0xFFFFFu) != 0) {
            expect = (expect & 0xFFF00000u) | (bits & 0xFFFFFu);
            ++replaced;
        }
        expect |= bits & 0xFFF00000u;
        CHECK(load32(m, unit + 12) == expect);
        CHECK(p.hand.v0 == sx(expect));
        const u32 after_set = expect;
        p = run_pair(m, PAIR(fn_datCalcClearBadStatus_00300560), Args{unit, sx(bits)}, seed, "datCalcClearBadStatus", {{unit, 60}});
        CHECK(load32(m, unit + 12) == (after_set & ~bits));
        CHECK(p.hand.v0 == sx(after_set & ~bits));
    }
    CHECK(replaced > 1500);
}

TEST_CASE("game(battle): datCalcIsDead equals its recompiled body: the dead bit or hp + delta <= 0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11u};
    int dead_by_bit = 0, dead_by_hp = 0;
    for (int it = 0; it < 3000; ++it) {
        const u32 unit = random_unit(m, rng, it & 7, (rng() & 1) != 0);
        const u16 hp = static_cast<u16>(rand_range(rng, 0, it % 3 == 0 ? 10 : 999));
        store16(m, unit + 8, hp);
        u32 status = load32(m, unit + 12);
        if (it % 4 != 0) status &= ~0x80000u;  // mostly alive by the bit, so the hp rule is exercised
        store32(m, unit + 12, status);
        s32 delta;
        switch (it % 6) {
        case 0: delta = -static_cast<s32>(hp); break;        // exactly zero
        case 1: delta = -static_cast<s32>(hp) + 1; break;    // one above
        case 2: delta = -static_cast<s32>(hp) - 1; break;    // one below
        case 3: delta = rand_range(rng, -2000, 2000); break;
        case 4: delta = static_cast<s32>(rng()); break;      // the 32-bit wrap of addu
        default: delta = 0; break;
        }
        const Pair p = run_pair(m, PAIR(fn_datCalcIsDead_0030b5a0), Args{unit, sx(static_cast<u32>(delta))}, rng(), "datCalcIsDead");
        u32 expect;
        if (status & 0x80000u) {
            expect = 1;
            ++dead_by_bit;
        } else {
            const s32 sum = static_cast<s32>(static_cast<u32>(hp) + static_cast<u32>(delta));
            expect = sum > 0 ? 0u : 1u;
            dead_by_hp += static_cast<int>(expect);
        }
        CHECK(p.hand.v0 == expect);
    }
    CHECK(dead_by_bit > 300);  // the bit stays random in one iteration of four
    CHECK(dead_by_hp > 500);
}

TEST_CASE("game(battle): the buff-slot getters equal their recompiled bodies: signed nibbles and the flag bits") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{17u};
    int negatives = 0, asserted = 0;
    for (int it = 0; it < 1200; ++it) {
        const u32 unit = random_unit(m, rng, it & 7, (rng() & 1) != 0);
        for (u32 slot = 0; slot < 44; ++slot) {  // 0..16 nibbles, 17..20 flags, 21..43 the assertion no-op paths
            const u32 arg = it % 7 == 0 ? (slot | (rng() << 8)) : slot;  // only the low byte of the slot counts
            const u32 seed = rng();
            Pair p = run_pair(m, PAIR(fn_datCalcGetEffectLevel_00300f60), Args{unit, arg}, seed, "datCalcGetEffectLevel");
            const s32 nibble = host_effect_nibble(m, unit, slot);
            CHECK(p.hand.v0 == sx(static_cast<u32>(nibble)));
            if (nibble < 0) ++negatives;
            if (slot >= 21) ++asserted;
            p = run_pair(m, PAIR(fn_datCalcGetEffectState_00301750), Args{unit, arg}, seed, "datCalcGetEffectState");
            if (slot < 17) {
                CHECK(p.hand.v0 == sx(static_cast<u32>(nibble)));
            } else {
                const u32 flags = load32(m, unit + 0x14);
                CHECK(p.hand.v0 == ((flags & (1u << (slot & 31))) != 0 ? 1u : 0u));
            }
        }
    }
    CHECK(negatives > 5000);
    CHECK(asserted > 20000);
}

TEST_CASE("game(battle): the SKILL.TBL flag lookups equal their recompiled bodies over every skill id") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{23u};
    const bool real = install_skill_table(m, rng);
    if (real) {
        MESSAGE("battle/SKILL.TBL: real sections 0 and 1");
    } else {
        MESSAGE("battle/SKILL.TBL absent: random images");
    }
    int physical = 0, field = 0;
    for (u32 id = 0; id < 600; ++id) {  // 464 real ids, then the K_Assert no-op path past the table
        const u32 seed = rng();
        const u8* rec = m.mem.main_ram() + kSection1 + id * kSkillRecordSize;
        Pair p = run_pair(m, PAIR(fn_datCalcIsPhysicalSkill_003088b0), Args{id}, seed, "datCalcIsPhysicalSkill");
        CHECK(p.hand.v0 == ((rec[0] & 2) ? 1u : 0u));
        physical += (id < kSkillCount && (rec[0] & 2)) ? 1 : 0;
        p = run_pair(m, PAIR(fn_datCalcIsSkillUsableOnField_00300af0), Args{id}, seed, "datCalcIsSkillUsableOnField");
        const u32 expect = id < kSkillCount && (rec[0] & 2) == 0 && (rec[1] & 1) ? 1u : 0u;
        CHECK(p.hand.v0 == expect);
        field += static_cast<int>(expect);
        // The id is taken as 16 bits: high garbage does not change the lookup.
        p = run_pair(m, PAIR(fn_datCalcIsPhysicalSkill_003088b0), Args{id | (rng() << 16)}, seed, "datCalcIsPhysicalSkill (wide id)");
        CHECK(p.hand.v0 == ((rec[0] & 2) ? 1u : 0u));
        p = run_pair(m, PAIR(fn_datCalcIsSkillUsableOnField_00300af0), Args{sx(id | (rng() << 16))}, seed, "datCalcIsSkillUsableOnField (wide id)");
        CHECK(p.hand.v0 == expect);
    }
    if (real) {
        CHECK(physical == 16);
        CHECK(field == 32);
    }
    for (int it = 0; it < 400; ++it) {  // random ids up to the 16-bit range
        const u32 id = rng() & 0xFFFFu;
        run_pair(m, PAIR(fn_datCalcIsPhysicalSkill_003088b0), Args{id}, rng(), "datCalcIsPhysicalSkill (random)");
        run_pair(m, PAIR(fn_datCalcIsSkillUsableOnField_00300af0), Args{id}, rng(), "datCalcIsSkillUsableOnField (random)");
    }
}

TEST_CASE("game(battle): datCalcGetElementBit equals its recompiled body for every element row") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{29u};
    for (s32 e = -40; e <= 60; ++e) {
        const Pair p = run_pair(m, PAIR(fn_datCalcGetElementBit_003080c0), Args{sx(static_cast<u32>(e))}, rng(), "datCalcGetElementBit");
        CHECK(p.hand.v0 == sx(1u << (static_cast<u32>(e + 1) & 31u)));
    }
    // The element is a 16-bit argument: 0x10000 + e behaves as e.
    for (int it = 0; it < 200; ++it) {
        const s32 e = rand_range(rng, -5, 25);
        const u32 wide = (static_cast<u32>(e) & 0xFFFFu) | (rng() << 16);
        const Pair p = run_pair(m, PAIR(fn_datCalcGetElementBit_003080c0), Args{sx(wide)}, rng(), "datCalcGetElementBit (wide)");
        CHECK(p.hand.v0 == sx(1u << (static_cast<u32>(e + 1) & 31u)));
    }
}

TEST_CASE("game(battle): datCalcGetElementForStatus equals its recompiled body: the status map and the skill element") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{31u};
    const bool real = install_skill_table(m, rng);
    struct Row {
        u32 bit;
        s32 element;
    };
    constexpr Row rows[13] = {{0x100000u, 7}, {0x80000u, 9}, {0x400u, 7}, {0x200u, 7}, {0x100u, 7}, {0x80u, 11}, {0x40u, 5},
                              {0x20u, 4},     {0x10u, 15},   {0x8u, 14},  {0x4u, 13},  {0x2u, 12},  {0x1u, 10}};
    // No skill: the table alone.
    for (const Row& r : rows) {
        const Pair p = run_pair(m, PAIR(fn_datCalcGetElementForStatus_00308120), Args{sx(0xFFFFFFFFu), r.bit}, rng(), "datCalcGetElementForStatus(-1, bit)");
        CHECK(p.hand.v0 == sx(static_cast<u32>(r.element)));
    }
    // No skill and no matching bit: the K_Assert no-op path returns the caller's $s0 (both bodies do).
    int unmatched = 0;
    for (int it = 0; it < 300; ++it) {
        const u32 bit = it % 2 ? (rng() & ~0x1807FFu) : (1u << (21 + rng() % 11));
        bool matches = false;
        for (const Row& r : rows) matches = matches || r.bit == bit;
        if (matches) continue;
        run_pair(m, PAIR(fn_datCalcGetElementForStatus_00308120), Args{sx(0xFFFFFFFFu), bit}, rng(), "datCalcGetElementForStatus(-1, unmatched)");
        ++unmatched;
    }
    CHECK(unmatched > 200);
    // With a skill: element 8 from section 0 wins, every other element falls back to the table.
    int dark = 0, table = 0;
    for (u32 id = 0; id < kSkillCount; ++id) {
        const s32 element = static_cast<s8>(m.mem.main_ram()[kSection0 + 2 * id]);
        const Row& r = rows[rng() % 13];
        const u32 seed = rng();
        const Pair p = run_pair(m, PAIR(fn_datCalcGetElementForStatus_00308120), Args{id, r.bit}, seed, "datCalcGetElementForStatus(skill, bit)");
        if (element == 8) {
            CHECK(p.hand.v0 == 8);
            ++dark;
        } else {
            CHECK(p.hand.v0 == sx(static_cast<u32>(r.element)));
            ++table;
        }
        // an unmatched bit with a skill returns the skill's element (the $s0 the callee's result left)
        const u64 stray = u64{1} << (21 + rng() % 11);
        const Pair q = run_pair(m, PAIR(fn_datCalcGetElementForStatus_00308120), Args{id, stray}, seed, "datCalcGetElementForStatus(skill, unmatched)");
        CHECK(q.hand.v0 == (element == 8 ? 8u : sx(static_cast<u32>(element))));
    }
    if (real) {
        CHECK(dark == 7);  // the seven Dark skills of SKILL.TBL section 0
        CHECK(table > 400);
    }
}

#else
TEST_CASE("game(battle): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
