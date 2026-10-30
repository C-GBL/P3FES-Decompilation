// Phase 5 pair tests for the BF script COMM handlers of indices 251-501 (game/src/script/comm_b.cpp):
// each hand-written handler and the recompiled body it replaces run on identical guest machines
// (pair_harness.h: $v0, callee-saved registers, virtual cycles, check-point count, the arena and the
// caller's stack) and must also leave the same bytes in every guest region the handlers and their callees
// touch outside the arena (the $gp words, the g_data block and the character records below it, the
// float tables, effMiscRand's state, low RAM for the null-unit read). The handlers take their arguments
// from a ScrTask in the arena (g_scrCurrentTask points at it; argument i in slot sp - 1 - i, int tags and
// now and then a float tag that scrGetIntPara converts); the user word points at a record whose +48
// owner leads to a DatUnit. Arguments are random within ranges that keep the stores of the
// still-recompiled callees inside the compared regions, plus edge cases (negative and out-of-table
// indices, field ids 3999/4000/4021, a null field object, an empty unit list). clndScrCmd_TIME_SKIP
// gets day-part offsets up to 2000: its subtraction loop runs (time + arg) / 9 times. The documented
// rules (comm_b.h) are checked on the host independently of both bodies.
#include "pair_harness.h"

#include "p3fes/game/comm_b.h"
#include "p3fes/game/script_vm.h"

#include <cstring>
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
P3FES_DECL_PAIR(fn_sub_1C3A10_001c3a10)
P3FES_DECL_PAIR(fn_sub_2CD8C0_002cd8c0)
P3FES_DECL_PAIR(fn_sub_2CD940_002cd940)
P3FES_DECL_PAIR(fn_sub_1C3F60_001c3f60)
P3FES_DECL_PAIR(fn_sub_1C3F90_001c3f90)
P3FES_DECL_PAIR(fn_sub_1C3FE0_001c3fe0)
P3FES_DECL_PAIR(fn_sub_1C4080_001c4080)
P3FES_DECL_PAIR(fn_sub_2CDA10_002cda10)
P3FES_DECL_PAIR(fn_sub_16EB80_0016eb80)
P3FES_DECL_PAIR(fn_sub_16EBE0_0016ebe0)
P3FES_DECL_PAIR(fn_sub_1C3950_001c3950)
P3FES_DECL_PAIR(fn_sub_4250B0_004250b0)
P3FES_DECL_PAIR(fn_sub_4250E0_004250e0)
P3FES_DECL_PAIR(fn_sub_425190_00425190)
P3FES_DECL_PAIR(fn_sub_425220_00425220)
P3FES_DECL_PAIR(fn_sub_425270_00425270)
P3FES_DECL_PAIR(fn_sub_4252A0_004252a0)
P3FES_DECL_PAIR(fn_sub_2D0A30_002d0a30)
P3FES_DECL_PAIR(fn_sub_2D14D0_002d14d0)
P3FES_DECL_PAIR(fn_sub_2D1510_002d1510)
P3FES_DECL_PAIR(fn_sub_2D0CB0_002d0cb0)
P3FES_DECL_PAIR(fn_sub_4253D0_004253d0)
P3FES_DECL_PAIR(fn_sub_1C3990_001c3990)
P3FES_DECL_PAIR(fn_sub_424F10_00424f10)
P3FES_DECL_PAIR(fn_sub_10BF40_0010bf40)
P3FES_DECL_PAIR(fn_sub_2D1560_002d1560)
P3FES_DECL_PAIR(fn_sub_2D0EF0_002d0ef0)
P3FES_DECL_PAIR(fn_sub_2D0F90_002d0f90)
P3FES_DECL_PAIR(fn_sub_2CD9C0_002cd9c0)
P3FES_DECL_PAIR(fn_sub_1C3C40_001c3c40)
P3FES_DECL_PAIR(fn_sub_1C3C80_001c3c80)
P3FES_DECL_PAIR(fn_sub_1C2FF0_001c2ff0)
P3FES_DECL_PAIR(fn_sub_1C30F0_001c30f0)
P3FES_DECL_PAIR(fn_sub_1C3590_001c3590)
P3FES_DECL_PAIR(fn_sub_1C3600_001c3600)
P3FES_DECL_PAIR(fn_clndScrCmd_TIME_SKIP_00181c20)
P3FES_DECL_PAIR(fn_sub_1C4D10_001c4d10)
P3FES_DECL_PAIR(fn_sub_1C4D90_001c4d90)
P3FES_DECL_PAIR(fn_sub_1C4DF0_001c4df0)
P3FES_DECL_PAIR(fn_sub_17F990_0017f990)
P3FES_DECL_PAIR(fn_sub_1C58D0_001c58d0)
P3FES_DECL_PAIR(fn_sub_1C5E60_001c5e60)
P3FES_DECL_PAIR(fn_sub_27D840_0027d840)
P3FES_DECL_PAIR(fn_sub_2CE4E0_002ce4e0)
P3FES_DECL_PAIR(fn_sub_2CFA40_002cfa40)
P3FES_DECL_PAIR(fn_sub_1C3270_001c3270)
P3FES_DECL_PAIR(fn_sub_2D1490_002d1490)
P3FES_DECL_PAIR(fn_sub_17FD30_0017fd30)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
namespace cb = p3fes::game::comm_b;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the arena layout -----------------------------------------------------------------------------------
constexpr u32 kTask = kArena + 0x000;         // ScrTask (252 bytes)
constexpr u32 kUser = kArena + 0x100;         // the user record (+0 count, +4.. ids, +48 owner, ... +428)
constexpr u32 kFieldObj = kArena + 0x300;     // *kFieldTask: +60 -> kFieldWork
constexpr u32 kCalendarObj = kArena + 0x380;  // *kCalendarTask: +60 -> kCalendarWork
constexpr u32 kFieldWork = kArena + 0x400;    // +484 s16
constexpr u32 kCalendarWork = kArena + 0x600; // +0, +8, +32 written
constexpr u32 kEventWork = kArena + 0x640;    // *kEventWork: +284 -> kFd, +296 byte
constexpr u32 kFd = kArena + 0x780;           // field descriptor: +2 u16 id, +7 flags, +8 s32
constexpr u32 kRec3004 = kArena + 0x7A0;      // battle work +3004 -> record, +8 u16 index
constexpr u32 kBattle = kArena + 0x800;       // *kBattleWork: +332 unit list, +3004, +3376 s32[]
constexpr u32 kParams = kArena + 0x1000;      // *kFieldParams (stores reach -512 .. +880)
constexpr u32 kTable28 = kArena + 0x1700;     // *kBattleTable28
constexpr u32 kTable44 = kArena + 0x1900;     // *kBattleTable44
constexpr u32 kU16Pool = kArena + 0x1C00;     // what kFieldTable's +12 pointers point at

// Outside the arena: the battle units (+8 id, +26 flags, +48 owner, +1192 next), their owners (+162 side,
// +2604 -> DatUnit) and the 60-byte DatUnits; sub_170860's c == 1 store target.
constexpr u32 kExtra = 0x01804000u;
constexpr u32 kExtraSize = 0x6000u;
constexpr u32 kUnits = kExtra, kUnitStride = 0x4B0u, kUnitCount = 5;
constexpr u32 kOwners = kExtra + 0x2000u, kOwnerStride = 0xA40u;
constexpr u32 kDatUnits = kExtra + 0x5400u, kDatUnitStride = 0x40u;
constexpr u32 kItemPtrTarget = kExtra + 0x5800u;  // *(0x836798) = this + 8000: stores land at +2 * index

// --- guest regions outside the arena ------------------------------------------------------------------
constexpr u32 kGpArea = 0x7CDE00u;        // $gp words 0x7CDF14 .. 0x7CE6EC, g_scrCurrentTask 0x7CE5A8
constexpr u32 kGdataLow = 0x7FC000u;      // character records below g_data (sub_170860's loop stores)
constexpr u32 kGdata = 0x831000u;         // g_data: 0x831CE0 table, 868-byte records, counters, kGdataWords
constexpr u32 kItemPtr = 0x836798u;       // pointer read by sub_170760 / sub_170860 for c == 1
constexpr u32 kScenario = 0x7CDFA4u;      // sub_17D800
constexpr u32 kDays = 0x83679Cu, kTime = 0x83679Eu, kSkipFlag = 0x8367A0u, kSkipDays = 0x8367A4u, kSkipTime = 0x8367A6u;
constexpr u32 kCounters = 0x83A4DCu;
constexpr u32 kFloatArea = 0x957100u;     // the six-float tables and effMiscRand's state 0x957BF0
constexpr u32 kEffRand = 0x957BF0u;
constexpr u32 kVec4Area = 0x86BC00u;

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region>& regions() {
    static const std::vector<Region> r = {
        {kArena, kArenaSize}, {kExtra, kExtraSize}, {0, 0x200},           {kGpArea, 0xA00},
        {kGdataLow, 0x5000},  {kGdata, 0xA000},     {kVec4Area, 0xA00}, {kFloatArea, 0xB00},
    };
    return r;
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
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= len; i += 4) store32(m, va + i, rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}

// A pair over every region: snapshot, run the hand version, restore, run the recompiled body, compare.
// Afterwards the recompiled run's output is in place.
Outcome pair(Machine& m, Fn hand_fn, Fn recomp_fn, u32 seed, const char* what, std::mt19937& rng) {
    std::vector<std::vector<u8>> before, after_hand;
    for (const Region& r : regions()) before.push_back(m.bytes(r.va, r.len));
    const Args args{rng(), rng(), rng(), rng()};
    const Outcome hand = run(m, hand_fn, args, seed);
    const u32 hand_f0 = m.ctx.fpr[0];
    u64 hand_gpr[32];
    for (unsigned r = 0; r < 32; ++r) hand_gpr[r] = m.ctx.gpr[r].u64[0];
    for (const Region& r : regions()) after_hand.push_back(m.bytes(r.va, r.len));
    std::size_t i = 0;
    for (const Region& r : regions()) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    const Outcome recomp = run(m, recomp_fn, args, seed);
    INFO(std::string(what));
    expect_same(hand, recomp, what);
    CHECK(hand_f0 == m.ctx.fpr[0]);
    for (unsigned r = 1; r < 32; ++r) {
        if (r == GPR_K0 || r == GPR_K1) continue;
        INFO("gpr " << r);
        CHECK(hand_gpr[r] == m.ctx.gpr[r].u64[0]);
    }
    i = 0;
    for (const Region& r : regions()) {
        INFO("region 0x" << std::hex << r.va);
        CHECK(after_hand[i++] == m.bytes(r.va, r.len));
    }
    return hand;
}

// The COMM arguments: arg i in slot sp - 1 - i. Integer arguments get tag 0, or now and then tag 1
// with the value as a float (scrGetIntPara truncates it back).
void set_args(Machine& m, std::mt19937& rng, const std::vector<s32>& args, bool floats = false) {
    const u32 sp = static_cast<u32>(args.size());
    store32(m, kTask + scr::kSp, sp);
    for (u32 i = 0; i < sp; ++i) {
        const u32 slot = sp - 1 - i;
        // A float tag only where the value survives the round trip (|v| <= 2^24).
        const bool exact = args[i] >= -(1 << 24) && args[i] <= (1 << 24);
        const bool as_float = floats ? !chance(rng, 10) : (exact && chance(rng, 8));
        m.at(kTask + scr::kTags + slot)[0] = static_cast<u8>(as_float ? scr::kTagFloat : scr::kTagInt);
        store32(m, kTask + scr::kValues + slot * 4,
                as_float ? fbits(static_cast<float>(args[i]) + (floats ? 0.25f : 0.0f)) : static_cast<u32>(args[i]));
    }
}
u32 ret_value(const Machine& m) { return load32(m, kTask + scr::kValues + scr::kReturnSlot * 4); }
void clear_ret(Machine& m) { store32(m, kTask + scr::kValues + scr::kReturnSlot * 4, 0xDEADBEEFu); }

u32 unit(u32 i) { return kUnits + i * kUnitStride; }
u32 owner(u32 i) { return kOwners + i * kOwnerStride; }
u32 dat_unit(u32 i) { return kDatUnits + i * kDatUnitStride; }

// A fresh world: random arena and records, every pointer wired into the compared regions.
void seed_world(Machine& m, std::mt19937& rng) {
    fill_random(m, kArena, kArenaSize, rng);
    fill_random(m, kExtra, kExtraSize, rng);
    fill_random(m, kGdataLow, 0x5000, rng);
    fill_random(m, kGdata, 0xA000, rng);
    fill_random(m, kVec4Area, 0xA00, rng);
    fill_random(m, kFloatArea, 0xB00, rng);
    // The task.
    store32(m, kTask + scr::kSp, 0);
    store32(m, kTask + scr::kCmdTimer, chance(rng, 70) ? static_cast<u32>(rand_range(rng, -2, 5)) : rng());
    store32(m, kTask + scr::kUserData, kUser);
    store32(m, scr::kCurrentTask, kTask);
    // The user record.
    store32(m, kUser + 0, static_cast<u32>(chance(rng, 90) ? rand_range(rng, 0, 6) : rand_range(rng, -3, -1)));
    for (u32 k = 0; k < 6; ++k) store32(m, kUser + 4 + 4 * k, static_cast<u32>(rand_range(rng, 0, 12)));
    store32(m, kUser + 48, owner(rng() % kUnitCount));
    store16(m, kUser + 426, chance(rng, 40) ? cb::kField4021 : static_cast<u16>(rng()));
    // Field objects.
    store32(m, cb::kFieldTask, chance(rng, 20) ? 0u : kFieldObj);
    store32(m, kFieldObj + 60, kFieldWork);
    store16(m, kFieldWork + 484, chance(rng, 40) ? 0 : static_cast<u16>(rng()));
    store32(m, cb::kCalendarTask, chance(rng, 20) ? 0u : kCalendarObj);
    store32(m, kCalendarObj + 60, kCalendarWork);
    store32(m, kScenario, static_cast<u32>(rand_range(rng, 0, 2)));
    store32(m, cb::kEventWork, kEventWork);
    store32(m, kEventWork + 284, kFd);
    static const u16 kIds[] = {3999, 4000, 4001, 4021, 4021, 0, 0xFFFF};
    store16(m, kFd + 2, chance(rng, 80) ? kIds[rng() % 7] : static_cast<u16>(rng()));
    // Field parameters: the slot count byte stays near 0 so the appends land in the arena.
    store32(m, cb::kFieldParams, kParams);
    m.at(kParams + 160)[0] = static_cast<u8>(rand_range(rng, -8, 8));
    // Battle work, its tables and the unit list (0..5 units; side bytes 0/1/2, flags mostly 1|8).
    store32(m, cb::kBattleWork, kBattle);
    store32(m, kBattle + 3004, kRec3004);
    store16(m, kRec3004 + 8, static_cast<u16>(chance(rng, 90) ? rand_range(rng, 0, 15) : rng()));
    store32(m, cb::kBattleTable28, kTable28);
    store32(m, cb::kBattleTable44, kTable44);
    const u32 n = rng() % (kUnitCount + 1);
    store32(m, kBattle + 332, n ? unit(0) : 0u);
    for (u32 i = 0; i < kUnitCount; ++i) {
        store32(m, unit(i) + 1192, i + 1 < n ? unit(i + 1) : 0u);
        store16(m, unit(i) + 26, static_cast<u16>(chance(rng, 70) ? (0x9u | (rng() & 0xFFF6u)) : rng()));
        store32(m, unit(i) + 48, owner(i));
        m.at(owner(i) + 162)[0] = static_cast<u8>(rng() % 3);
        store32(m, owner(i) + 2604, dat_unit(i));
        store16(m, dat_unit(i) + 8, static_cast<u16>(chance(rng, 80) ? rand_range(rng, 0, 999) : rng()));
        store32(m, dat_unit(i) + 12, chance(rng, 70) ? (rng() & ~0x00080000u) : rng());
    }
    // kFieldTable records 0..7: word +0 and pointer +12, each zero now and then.
    for (u32 i = 0; i < 8; ++i) {
        store32(m, cb::kFieldTable + i * 448, chance(rng, 25) ? 0u : rng());
        store32(m, cb::kFieldTable + 12 + i * 448, chance(rng, 25) ? 0u : kU16Pool + 2 * (rng() % 64));
    }
    // g_data words the callees read as pointers or small values.
    store32(m, kItemPtr, kItemPtrTarget + 8000);
    store16(m, kDays, static_cast<u16>(rand_range(rng, 0, 400)));
    m.at(kTime)[0] = static_cast<u8>(chance(rng, 80) ? rand_range(rng, 0, 8) : rng());
}

bool alive(const Machine& m, u32 i) {
    return (load32(m, dat_unit(i) + 12) & 0x00080000u) == 0 && load16(m, dat_unit(i) + 8) != 0;
}
// The documented rule of sub_2CE4E0 / sub_2CFA40: the first living unit of the side with the lowest HP.
u32 expected_lowest(const Machine& m, u32 side) {
    u32 best = 0;
    u32 best_hp = 0x0FFFFFFFu;
    for (u32 u = load32(m, kBattle + 332); u != 0; u = load32(m, u + 1192)) {
        const u32 i = (u - kUnits) / kUnitStride;
        const u16 flags = load16(m, u + 26);
        if (!(flags & 1u) || !(flags & 8u) || m.mem.main_ram()[owner(i) + 162] != side || !alive(m, i)) continue;
        const u32 hp = load16(m, dat_unit(i) + 8);
        if (hp < best_hp) {
            best = u;
            best_hp = hp;
        }
    }
    return load32(m, best + 8) | 0x80000000u;
}

}  // namespace

TEST_CASE("game(script_comm_b): the leaf COMM handlers equal their recompiled bodies and the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0BB0001u};
    int found_ids = 0, have_field = 0, waits = 0;
    for (int it = 0; it < 300; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        // Field descriptor readers.
        clear_ret(m);
        pair(m, PAIR(fn_sub_1C3A10_001c3a10), seed, "sub_1C3A10", rng);
        CHECK(ret_value(m) == (load16(m, kFd + 2) < 4000 ? m.mem.main_ram()[kEventWork + 296] : 0u));
        pair(m, PAIR(fn_sub_1C3950_001c3950), seed, "sub_1C3950", rng);
        CHECK(ret_value(m) == (m.mem.main_ram()[kFd + 7] & 1u));
        pair(m, PAIR(fn_sub_1C3990_001c3990), seed, "sub_1C3990", rng);
        CHECK(ret_value(m) == (load16(m, kFd + 2) == 4021 ? load32(m, kFd + 8) : 0u));
        // Unit flags through user->+48->+2604.
        const u32 rec = load32(m, load32(m, kUser + 48) + 2604);
        const s32 on = chance(rng, 50) ? 0 : (chance(rng, 50) ? 0x10000 : rand_range(rng, -5, 5));
        set_args(m, rng, {on});
        pair(m, PAIR(fn_sub_2CD8C0_002cd8c0), seed, "sub_2CD8C0", rng);
        CHECK(((load16(m, rec) & 0x10u) != 0) == ((static_cast<u32>(on) & 0xFFFFu) == 0));
        set_args(m, rng, {on});
        pair(m, PAIR(fn_sub_2CD940_002cd940), seed, "sub_2CD940", rng);
        CHECK(((load16(m, rec) & 0x20u) != 0) == ((static_cast<u32>(on) & 0xFFFFu) == 0));
        pair(m, PAIR(fn_sub_2CDA10_002cda10), seed, "sub_2CDA10", rng);
        CHECK(ret_value(m) == load16(m, rec + 4));
        // The user's id list.
        pair(m, PAIR(fn_sub_1C3F60_001c3f60), seed, "sub_1C3F60", rng);
        CHECK(ret_value(m) == load32(m, kUser));
        const s32 idx = chance(rng, 85) ? rand_range(rng, 0, 5) : rand_range(rng, -40, 40);
        set_args(m, rng, {idx});
        pair(m, PAIR(fn_sub_1C3F90_001c3f90), seed, "sub_1C3F90", rng);
        CHECK(ret_value(m) == load32(m, kUser + 4 + 4 * static_cast<u32>(idx)));
        const s32 id = rand_range(rng, -1, 13);
        set_args(m, rng, {id});
        pair(m, PAIR(fn_sub_1C3FE0_001c3fe0), seed, "sub_1C3FE0", rng);
        bool listed = false;
        for (s32 k = 0; k < static_cast<s32>(load32(m, kUser)); ++k)
            listed = listed || load32(m, kUser + 4 + 4 * static_cast<u32>(k)) == static_cast<u32>(id);
        CHECK(ret_value(m) == (listed ? 1u : 0u));
        found_ids += listed ? 1 : 0;
        // kFieldTable.
        const s32 rec_index = chance(rng, 90) ? rand_range(rng, 0, 7) : rand_range(rng, -3, 12);
        set_args(m, rng, {rec_index});
        pair(m, PAIR(fn_sub_1C4080_001c4080), seed, "sub_1C4080", rng);
        if (rec_index >= 0 && rec_index < 8) {
            const u32 r = cb::kFieldTable + static_cast<u32>(rec_index) * 448;
            const bool have = load32(m, r) != 0 && load32(m, r + 12) != 0;
            CHECK(ret_value(m) == (have ? load16(m, load32(m, r + 12)) : 0u));
            have_field += have ? 1 : 0;
        }
        // The four saved words.
        pair(m, PAIR(fn_sub_16EB80_0016eb80), seed, "sub_16EB80", rng);
        CHECK(m.bytes(cb::kSavedWords, 8) == m.bytes(cb::kGdataWords, 8));
        fill_random(m, cb::kSavedWords, 8, rng);
        pair(m, PAIR(fn_sub_16EBE0_0016ebe0), seed, "sub_16EBE0", rng);
        CHECK(m.bytes(cb::kSavedWords, 8) == m.bytes(cb::kGdataWords, 8));
        // kFieldParams writers.
        const s32 b = static_cast<s32>(rng());
        set_args(m, rng, {b});
        pair(m, PAIR(fn_sub_4250B0_004250b0), seed, "sub_4250B0", rng);
        set_args(m, rng, {b});
        pair(m, PAIR(fn_sub_425270_00425270), seed, "sub_425270", rng);
        set_args(m, rng, {b});
        pair(m, PAIR(fn_sub_4252A0_004252a0), seed, "sub_4252A0", rng);
        const s32 slot = chance(rng, 80) ? rand_range(rng, 1, 8) : rand_range(rng, -128, 127);
        const s32 h = static_cast<s32>(rng());
        set_args(m, rng, {slot, b, h});
        pair(m, PAIR(fn_sub_4250E0_004250e0), seed, "sub_4250E0", rng);
        const u32 s = static_cast<u32>(static_cast<s32>(static_cast<s8>(static_cast<s8>(slot) - 1)));
        CHECK(load16(m, kParams + 124 + 6 * s) == static_cast<u16>(h));
        CHECK(m.mem.main_ram()[kParams + 166 + s] == static_cast<u8>(b));
        const s32 kind = chance(rng, 25) ? 0 : rand_range(rng, -3, 300);
        const s8 count = static_cast<s8>(m.mem.main_ram()[kParams + 160]);
        set_args(m, rng, {kind, h});
        pair(m, PAIR(fn_sub_425190_00425190), seed, "sub_425190", rng);
        CHECK(static_cast<s8>(m.mem.main_ram()[kParams + 160]) == static_cast<s8>(kind != 0 ? count + 1 : count));
        set_args(m, rng, {b, h});
        pair(m, PAIR(fn_sub_425220_00425220), seed, "sub_425220", rng);
        CHECK(load16(m, kParams + 162) == static_cast<u16>(h));
        // Battle words.
        const s32 cmd = chance(rng, 90) ? rand_range(rng, 0, 8) : rand_range(rng, -5, 40);
        set_args(m, rng, {cmd});
        pair(m, PAIR(fn_sub_2D0A30_002d0a30), seed, "sub_2D0A30", rng);
        CHECK(load16(m, kUser + 108) == 1);
        CHECK(load16(m, kUser + 110) == static_cast<u16>(cmd));
        const s32 word = chance(rng, 90) ? rand_range(rng, 0, 96) : rand_range(rng, -24, 120);
        set_args(m, rng, {word, h});
        pair(m, PAIR(fn_sub_2D1510_002d1510), seed, "sub_2D1510", rng);
        set_args(m, rng, {word});
        pair(m, PAIR(fn_sub_2D14D0_002d14d0), seed, "sub_2D14D0", rng);
        CHECK(ret_value(m) == static_cast<u32>(h));
        pair(m, PAIR(fn_sub_2D0CB0_002d0cb0), seed, "sub_2D0CB0", rng);
        // The vec4 table (s16 index) and the float tables.
        const s32 v = chance(rng, 90) ? rand_range(rng, -16, 80) : static_cast<s32>(static_cast<u32>(rand_range(rng, -16, 80)) | 0x10000u);
        const s32 f1 = rand_range(rng, -100000, 100000), f2 = static_cast<s32>(rng());
        set_args(m, rng, {v, b, f1, f2});
        pair(m, PAIR(fn_sub_4253D0_004253d0), seed, "sub_4253D0", rng);
        const u32 vrec = cb::kVec4Table + (static_cast<u32>(static_cast<s32>(static_cast<s16>(v))) << 4);
        CHECK(load32(m, vrec + 4) == fbits(static_cast<float>(f1)));
        std::vector<s32> six(6);
        for (s32& x : six) x = rand_range(rng, -2000, 2000);
        set_args(m, rng, six, true);
        pair(m, PAIR(fn_sub_2D0EF0_002d0ef0), seed, "sub_2D0EF0", rng);
        set_args(m, rng, six, true);
        pair(m, PAIR(fn_sub_2D0F90_002d0f90), seed, "sub_2D0F90", rng);
        // User words and flags.
        set_args(m, rng, {h, b});
        pair(m, PAIR(fn_sub_2CD9C0_002cd9c0), seed, "sub_2CD9C0", rng);
        CHECK(load16(m, kUser + 128) == static_cast<u16>(h));
        CHECK(m.mem.main_ram()[kUser + 130] == static_cast<u8>(b));
        pair(m, PAIR(fn_sub_424F10_00424f10), seed, "sub_424F10", rng);
        CHECK(ret_value(m) == (load16(m, kUser + 426) == 4021 ? 0u : ((load16(m, kUser + 428) & 1u) ? 1u : 2u)));
        // The two leaf waits.
        const Outcome w = pair(m, PAIR(fn_sub_10BF40_0010bf40), seed, "sub_10BF40", rng);
        const bool done = load32(m, cb::kFieldTask) == 0 || load16(m, kFieldWork + 484) == 0;
        CHECK(w.v0 == (done ? 1u : 0u));
        waits += done ? 0 : 1;
        CHECK(pair(m, PAIR(fn_sub_2D1560_002d1560), seed, "sub_2D1560", rng).v0 == 1);
    }
    CHECK(found_ids > 30);
    CHECK(have_field > 30);
    CHECK(waits > 30);
}

TEST_CASE("game(script_comm_b): the g_data / calendar / battle COMM handlers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0BB0002u};
    int answer = 0, picked = 0, skipped_days = 0;
    for (int it = 0; it < 300; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        // Counters (index asserted < 128; outside reads and writes still happen).
        const s32 ci = chance(rng, 90) ? rand_range(rng, 0, 127) : rand_range(rng, -8, 140);
        const s32 cv = static_cast<s32>(rng());
        set_args(m, rng, {ci, cv});
        pair(m, PAIR(fn_sub_1C3C80_001c3c80), seed, "sub_1C3C80", rng);
        CHECK(load32(m, kCounters + 4 * static_cast<u32>(ci)) == static_cast<u32>(cv));
        set_args(m, rng, {ci});
        clear_ret(m);
        pair(m, PAIR(fn_sub_1C3C40_001c3c40), seed, "sub_1C3C40", rng);
        if (ci >= 0 && ci < 128) CHECK(ret_value(m) == static_cast<u32>(cv));
        // Character record setters / item counts (characters kept where the stores stay in g_data).
        const s32 c = chance(rng, 85) ? rand_range(rng, 1, 12) : rand_range(rng, -3, 14);
        set_args(m, rng, {c, cv});
        pair(m, PAIR(fn_sub_1C2FF0_001c2ff0), seed, "sub_1C2FF0", rng);
        set_args(m, rng, {c, cv});
        pair(m, PAIR(fn_sub_1C30F0_001c30f0), seed, "sub_1C30F0", rng);
        static const s32 kItemChars[] = {-1, 1, 2, 3, 5, 8, 12, 255, 256, 300, 0, -3};
        const s32 ic = kItemChars[rng() % 12];
        const s32 item = chance(rng, 85) ? rand_range(rng, 0, 19) : rand_range(rng, -2, 25);
        const s32 count = chance(rng, 80) ? rand_range(rng, 0, 120) : static_cast<s32>(rng());
        set_args(m, rng, {ic, item, count});
        pair(m, PAIR(fn_sub_1C3600_001c3600), seed, "sub_1C3600", rng);
        set_args(m, rng, {ic, item});
        pair(m, PAIR(fn_sub_1C3590_001c3590), seed, "sub_1C3590", rng);
        // Persona / social records (read only).
        // (sub_177A40 reads record pc & 0xFFFF of 868 bytes: kept inside main RAM.)
        const s32 pc = chance(rng, 85) ? rand_range(rng, 2, 11) : rand_range(rng, 0, 20000);
        const s32 slot = chance(rng, 85) ? rand_range(rng, 0, 3) : rand_range(rng, -2, 8);
        set_args(m, rng, {pc, slot});
        pair(m, PAIR(fn_sub_1C4D10_001c4d10), seed, "sub_1C4D10", rng);
        set_args(m, rng, {pc, slot});
        pair(m, PAIR(fn_sub_1C4D90_001c4d90), seed, "sub_1C4D90", rng);
        set_args(m, rng, {pc, slot});
        pair(m, PAIR(fn_sub_1C4DF0_001c4df0), seed, "sub_1C4DF0", rng);
        const s32 who = chance(rng, 85) ? rand_range(rng, 0, 12) : rand_range(rng, -2, 20);
        const s32 stat = chance(rng, 85) ? rand_range(rng, 0, 2) : rand_range(rng, -2, 5);
        set_args(m, rng, {who, stat});
        clear_ret(m);
        pair(m, PAIR(fn_sub_1C3270_001c3270), seed, "sub_1C3270", rng);
        if (stat < 0 || stat > 2) CHECK(ret_value(m) == 0);
        // Calendar.
        const u32 today = load16(m, kDays), part = m.mem.main_ram()[kTime];
        const s32 add = chance(rng, 85) ? rand_range(rng, -10, 30) : rand_range(rng, -3000, 2000);
        set_args(m, rng, {add});
        pair(m, PAIR(fn_clndScrCmd_TIME_SKIP_00181c20), seed, "clndScrCmd_TIME_SKIP", rng);
        const s32 t = static_cast<s32>(part) + add;
        const s32 extra = t >= 9 ? t / 9 : 0;
        CHECK(load16(m, kSkipDays) == static_cast<u16>(today + static_cast<u32>(extra)));
        CHECK(m.mem.main_ram()[kSkipTime] == static_cast<u8>(t >= 9 ? t % 9 : t));
        CHECK(load32(m, kSkipFlag) == 1);
        skipped_days += extra > 0 ? 1 : 0;
        pair(m, PAIR(fn_sub_1C58D0_001c58d0), seed, "sub_1C58D0", rng);
        CHECK(ret_value(m) < 256);
        pair(m, PAIR(fn_sub_1C5E60_001c5e60), seed, "sub_1C5E60", rng);
        CHECK(ret_value(m) == (load32(m, kScenario) == 1 ? 1u : 0u));
        answer += load32(m, kScenario) == 1 ? 1 : 0;
        pair(m, PAIR(fn_sub_17F990_0017f990), seed, "sub_17F990", rng);
        if (load32(m, cb::kCalendarTask) != 0)
            CHECK(load32(m, kCalendarWork) == (load32(m, kScenario) != 0 ? 8u : 24u));
        // Battle.
        const Outcome w = pair(m, PAIR(fn_sub_27D840_0027d840), seed, "sub_27D840", rng);
        CHECK(w.v0 == (static_cast<s32>(load32(m, kTask + scr::kCmdTimer)) > 0 ? 1u : 0u));
        pair(m, PAIR(fn_sub_2CE4E0_002ce4e0), seed, "sub_2CE4E0", rng);
        CHECK(ret_value(m) == expected_lowest(m, 1));
        pair(m, PAIR(fn_sub_2CFA40_002cfa40), seed, "sub_2CFA40", rng);
        CHECK(ret_value(m) == expected_lowest(m, 0));
        picked += ret_value(m) != (load32(m, 8) | 0x80000000u) ? 1 : 0;
        fill_random(m, kEffRand, 16, rng);
        const s32 range = chance(rng, 80) ? rand_range(rng, 0, 100) : static_cast<s32>(rng());
        set_args(m, rng, {range});
        pair(m, PAIR(fn_sub_2D1490_002d1490), seed, "sub_2D1490", rng);
        // The persona skill rows (no input but g_data).
        if (it % 4 == 0) pair(m, PAIR(fn_sub_17FD30_0017fd30), seed, "sub_17FD30", rng);
    }
    CHECK(answer > 50);
    CHECK(picked > 50);
    CHECK(skipped_days > 30);
}

#endif  // P3FES_GAME_HAVE_GENERATED
