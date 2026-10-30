// Phase 5 pair tests for the second pass over the BF script COMM handlers of indices 251-501
// (game/src/script/comm_b2.cpp): each hand-written handler and the recompiled body it replaces run on identical
// guest machines through the hardware-observing pair (pair_harness.h run_hw): $v0, every GPR in 128 bits, HI/LO,
// the FPRs and FCR31 at the return, the whole register file and the cycle count at every check point (the kernel
// stores it in guest memory when a check point preempts), the dead stack (frames and spills), the arena, and
// every guest region the handlers and their callees touch outside it (the battle units, the $gp words, g_data,
// the field object table, effMiscRand's state, low RAM for null-pointer reads).
//
// The handlers take their arguments from a ScrTask in the arena (g_scrCurrentTask points at it; argument i in slot
// sp - 1 - i, int tags and now and then a float tag that scrGetIntPara converts). The user word points at an AI
// action record whose +48 owner leads to a DatUnit; the battle work holds a unit list (0..5 units, sides 0/1/2,
// owner ids 0..5 so the id searches hit), the turn-order slots, the current unit and the stage record (ids 421,
// 429, 432, 436, 456 and random). Field / event objects are null now and then. Documented rules (comm_b2.h) are
// checked on the host independently of both bodies.
#include "pair_harness.h"

#include "p3fes/game/comm_b2.h"
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
P3FES_DECL_PAIR(fn_sub_2CE440_002ce440)
P3FES_DECL_PAIR(fn_sub_2CBCD0_002cbcd0)
P3FES_DECL_PAIR(fn_sub_2CBD90_002cbd90)
P3FES_DECL_PAIR(fn_sub_2CBE50_002cbe50)
P3FES_DECL_PAIR(fn_sub_2CBF10_002cbf10)
P3FES_DECL_PAIR(fn_sub_2CDA50_002cda50)
P3FES_DECL_PAIR(fn_sub_2CDAD0_002cdad0)
P3FES_DECL_PAIR(fn_sub_2CA900_002ca900)
P3FES_DECL_PAIR(fn_sub_2D12E0_002d12e0)
P3FES_DECL_PAIR(fn_sub_2CFEB0_002cfeb0)
P3FES_DECL_PAIR(fn_sub_2D0150_002d0150)
P3FES_DECL_PAIR(fn_sub_2CC330_002cc330)
P3FES_DECL_PAIR(fn_sub_2CF9F0_002cf9f0)
P3FES_DECL_PAIR(fn_sub_2CDED0_002cded0)
P3FES_DECL_PAIR(fn_sub_2D06E0_002d06e0)
P3FES_DECL_PAIR(fn_sub_2D0720_002d0720)
P3FES_DECL_PAIR(fn_sub_2D0B90_002d0b90)
P3FES_DECL_PAIR(fn_sub_2D0BD0_002d0bd0)
P3FES_DECL_PAIR(fn_sub_2D0C10_002d0c10)
P3FES_DECL_PAIR(fn_sub_2D0C80_002d0c80)
P3FES_DECL_PAIR(fn_sub_2D0860_002d0860)
P3FES_DECL_PAIR(fn_sub_2D0970_002d0970)
P3FES_DECL_PAIR(fn_sub_2D0AC0_002d0ac0)
P3FES_DECL_PAIR(fn_sub_2D0C50_002d0c50)
P3FES_DECL_PAIR(fn_sub_2D11D0_002d11d0)
P3FES_DECL_PAIR(fn_sub_2D1260_002d1260)
P3FES_DECL_PAIR(fn_sub_2D12A0_002d12a0)
P3FES_DECL_PAIR(fn_sub_1C5670_001c5670)
P3FES_DECL_PAIR(fn_sub_425360_00425360)
P3FES_DECL_PAIR(fn_sub_4254C0_004254c0)
P3FES_DECL_PAIR(fn_sub_425530_00425530)
P3FES_DECL_PAIR(fn_sub_425580_00425580)
P3FES_DECL_PAIR(fn_sub_4255D0_004255d0)
P3FES_DECL_PAIR(fn_sub_425640_00425640)
P3FES_DECL_PAIR(fn_sub_1C5460_001c5460)
P3FES_DECL_PAIR(fn_sub_35FD80_0035fd80)
P3FES_DECL_PAIR(fn_sub_4244E0_004244e0)
P3FES_DECL_PAIR(fn_sub_4245C0_004245c0)
P3FES_DECL_PAIR(fn_sub_424730_00424730)
P3FES_DECL_PAIR(fn_sub_424880_00424880)
P3FES_DECL_PAIR(fn_sub_4249B0_004249b0)
P3FES_DECL_PAIR(fn_sub_1C4F70_001c4f70)
P3FES_DECL_PAIR(fn_sub_1C5040_001c5040)
P3FES_DECL_PAIR(fn_sub_1C5180_001c5180)
P3FES_DECL_PAIR(fn_sub_1C4E50_001c4e50)
P3FES_DECL_PAIR(fn_sub_1C2F20_001c2f20)
P3FES_DECL_PAIR(fn_sub_2CD7F0_002cd7f0)
P3FES_DECL_PAIR(fn_sub_2D03E0_002d03e0)
P3FES_DECL_PAIR(fn_sub_2CDE10_002cde10)
P3FES_DECL_PAIR(fn_sub_2CDE60_002cde60)
P3FES_DECL_PAIR(fn_sub_35FC70_0035fc70)
P3FES_DECL_PAIR(fn_sub_360090_00360090)
P3FES_DECL_PAIR(fn_sub_2CA480_002ca480)
P3FES_DECL_PAIR(fn_sub_2CA590_002ca590)
P3FES_DECL_PAIR(fn_sub_2CA6A0_002ca6a0)
P3FES_DECL_PAIR(fn_sub_2CA9D0_002ca9d0)
P3FES_DECL_PAIR(fn_sub_2CAAE0_002caae0)
P3FES_DECL_PAIR(fn_sub_2CABF0_002cabf0)
P3FES_DECL_PAIR(fn_sub_2CAD00_002cad00)
P3FES_DECL_PAIR(fn_sub_2CAE10_002cae10)
P3FES_DECL_PAIR(fn_sub_2CAF20_002caf20)
P3FES_DECL_PAIR(fn_sub_2CB030_002cb030)
P3FES_DECL_PAIR(fn_sub_2CB0E0_002cb0e0)
P3FES_DECL_PAIR(fn_sub_2CBA00_002cba00)
P3FES_DECL_PAIR(fn_sub_2CBA50_002cba50)
P3FES_DECL_PAIR(fn_sub_2CBAA0_002cbaa0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
namespace cb2 = p3fes::game::comm_b2;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the arena layout -----------------------------------------------------------------------------------------
constexpr u32 kTask = kArena + 0x000;       // ScrTask (252 bytes)
constexpr u32 kUser = kArena + 0x100;       // AI action record: +32 word, +48 owner, +108/+110 u16, +184 s64 key
constexpr u32 kStage = kArena + 0x1E0;      // battle->+3004: u16 +8 stage id
constexpr u32 kFxObj = kArena + 0x200;      // *kFieldFx: +60 -> kFxWork
constexpr u32 kFxWork = kArena + 0x280;     // s8 +4, +5, u16 +68, s8 +76, +80, +88, s8 +92
constexpr u32 kFieldObj = kArena + 0x300;   // *(gp - 19080): +60 -> kFieldWork
constexpr u32 kFieldWork = kArena + 0x380;  // +4, +40
constexpr u32 kTableObjs = kArena + 0x400;  // four objects (stride 0x50): +60 -> a work byte at kTableWork + 4i
constexpr u32 kTableWork = kArena + 0x5C0;
constexpr u32 kFlagA = kArena + 0x600;      // *kBtlFlagsA
constexpr u32 kFlagB = kArena + 0x610;      // *kBtlFlagsB
constexpr u32 kBattle = kArena + 0x800;     // *kBattleWork (offsets up to +3004)

// Outside the arena: the battle units (+0 s64 key, +8 id, +24 / +26 flags, +32 word, +48 owner, +110, +184 key,
// +1192 next), their owners (+162 side, +164 id, +2604 -> DatUnit) and the 60-byte DatUnits.
constexpr u32 kExtra = 0x01804000u;
constexpr u32 kExtraSize = 0x6000u;
constexpr u32 kUnits = kExtra, kUnitStride = 0x4B0u, kUnitCount = 5;
constexpr u32 kOwners = kExtra + 0x2000u, kOwnerStride = 0xA40u;
constexpr u32 kDatUnits = kExtra + 0x5400u, kDatUnitStride = 0x40u;

// --- guest regions outside the arena -----------------------------------------------------------------------------
constexpr u32 kGpArea = 0x7CDE00u;        // $gp words 0x7CDF14 .. 0x7CE6F8, g_scrCurrentTask 0x7CE5A8
constexpr u32 kGdata = 0x831000u;         // g_data: persona stock 0x836BA8.., social / item tables
constexpr u32 kSoundWords = 0x7E4400u;    // sub_1099A0's 0x7E4430 / 0x7E4438
constexpr u32 kObjTableArea = 0x86E600u;  // kFieldObjTable records 0..3 (+364)
constexpr u32 kFloatArea = 0x957100u;     // effMiscRand's state 0x957BF0
constexpr u32 kEffRand = 0x957BF0u;
constexpr u32 kSocialPtr = 0x95B700u;       // *(0x95B718): the 64 x 32-byte social link records (sub_3BEB10)
constexpr u32 kSocialTable = 0x01805800u;   // kExtra + 0x1800
constexpr u32 kSocialState = 0x8364F4u;     // s32[64] state (1 = active), then s32[64] at +256 (0 = not done)
constexpr u32 kFieldTableArea = 0x871700u;  // kFieldTable 0x8717E8 records 1..3 (sub_4249B0)
constexpr u32 kFieldTable = 0x8717E8u;
constexpr u32 kSlotPairs = 0x833C58u;       // 868 * pc + 4 * slot: { u16 item, s16 count }
constexpr u32 kInventory = 0x833E80u;       // owner -1: 20-byte records, u16 +0 = item id
constexpr u32 kPersonaUsed = 0x833A78u;     // 868 * pc + 20 * slot: u16, non-zero = used
constexpr u32 kFieldPtr = cb2::kGp - 19080;   // 0x7CE268
constexpr u32 kFxClock = cb2::kGp - 19432;    // 0x7CE108 (sub_45A430)

const std::vector<GuestRange>& regions() {
    static const std::vector<GuestRange> r = {
        {kArena, kArenaSize}, {kExtra, kExtraSize}, {0, 0x200},          {kGpArea, 0xA00},
        {kGdata, 0xC000},        {kSocialPtr, 0x40},     {kSoundWords, 0x100}, {kObjTableArea, 0xA00}, {kFloatArea, 0xB00}, {kFieldTableArea, 0x800}, {0x697100u, 0x500},
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
u8 load8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
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

// One pair over every region with the whole register file compared (at each check point and at the return,
// FPRs included). Afterwards the recompiled run's output is in place. Returns the hand run's $v0.
int pairs_run = 0;
int faulted_pairs = 0;
u64 pair(Machine& m, Fn hand_fn, Fn recomp_fn, u32 seed, const char* what, std::mt19937& rng) {
    INFO(std::string(what));
    HwCheck hw;
    hw.ranges = regions();
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    std::vector<std::vector<u8>> before;
    for (const GuestRange& r : hw.ranges) before.push_back(m.bytes(r.va, r.len));
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    const Args args{rng(), rng(), rng(), rng()};
    HwOutcome hand, recomp;
    const std::string fh = fault_of([&] { hand = run_hw(m, hand_fn, args, seed, hw); });
    std::array<u32, 32> hand_fpr;
    for (unsigned i = 0; i < 32; ++i) hand_fpr[i] = m.ctx.fpr[i];
    const u32 hand_fcr31 = m.ctx.fcr31;
    std::size_t i = 0;
    for (const GuestRange& r : hw.ranges) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    const std::string fr = fault_of([&] { recomp = run_hw(m, recomp_fn, args, seed, hw); });
    if (!fh.empty() || !fr.empty()) {  // an impossible id of the random world (sub_1732F0 reads through it): the original
        CHECK(fh == fr);               // faults as well, at the same instruction
        std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
        ++faulted_pairs;
        return ~u64{0};
    }
    expect_same_hw(hand, recomp, hw, what);
    for (unsigned f = 0; f < 32; ++f) {
        INFO("fpr " << f);
        CHECK(hand_fpr[f] == m.ctx.fpr[f]);
    }
    CHECK(hand_fcr31 == m.ctx.fcr31);
    ++pairs_run;
    return hand.base.v0;
}

// The COMM arguments: arg i in slot sp - 1 - i. Integer arguments get tag 0, or now and then tag 1 with the
// value as a float (scrGetIntPara truncates it back).
void set_args(Machine& m, std::mt19937& rng, const std::vector<s32>& args) {
    const u32 sp = static_cast<u32>(args.size());
    store32(m, kTask + scr::kSp, sp);
    for (u32 i = 0; i < sp; ++i) {
        const u32 slot = sp - 1 - i;
        const bool exact = args[i] >= -(1 << 24) && args[i] <= (1 << 24);
        const bool as_float = exact && chance(rng, 8);
        m.at(kTask + scr::kTags + slot)[0] = static_cast<u8>(as_float ? scr::kTagFloat : scr::kTagInt);
        store32(m, kTask + scr::kValues + slot * 4, as_float ? fbits(static_cast<float>(args[i])) : static_cast<u32>(args[i]));
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
    fill_random(m, kGdata, 0xC000, rng);
    fill_random(m, kObjTableArea, 0xA00, rng);
    fill_random(m, kFloatArea, 0xB00, rng);
    fill_random(m, kSoundWords, 0x100, rng);
    // The task and the user record.
    store32(m, kTask + scr::kSp, 0);
    store32(m, kTask + scr::kUserData, kUser);
    store32(m, scr::kCurrentTask, kTask);
    store32(m, kUser + 48, owner(rng() % kUnitCount));
    // Battle work: units, owners, DatUnits, order slots, stage.
    store32(m, cb2::kBattleWork, kBattle);
    const u32 n = rng() % (kUnitCount + 1);
    store32(m, kBattle + 332, n ? unit(0) : 0u);
    for (u32 i = 0; i < kUnitCount; ++i) {
        store64(m, unit(i), static_cast<u64>(rng() % 4));  // keys 0..3: some collide with the user's
        store32(m, unit(i) + 1192, i + 1 < n ? unit(i + 1) : 0u);
        store16(m, unit(i) + 26, static_cast<u16>(chance(rng, 75) ? (0x9u | (rng() & 0xFFF6u)) : rng()));
        store16(m, unit(i) + 110, static_cast<u16>(chance(rng, 30) ? 343 : rng()));
        store32(m, unit(i) + 48, owner(i));
        m.at(owner(i) + 162)[0] = static_cast<u8>(rng() % 3);
        store16(m, owner(i) + 164, static_cast<u16>(chance(rng, 85) ? rng() % 3 : rng()));
        if (chance(rng, 20)) store16(m, owner(i) + 164, 274);
        store32(m, owner(i) + 2604, chance(rng, 10) ? 0u : dat_unit(i));
        store16(m, dat_unit(i) + 8, static_cast<u16>(chance(rng, 80) ? rand_range(rng, 0, 999) : rng()));
        store32(m, dat_unit(i) + 12, chance(rng, 70) ? (rng() & ~0x00080000u) : rng());
    }
    store64(m, kUser + 184, static_cast<u64>(rng() % 5));
    store32(m, kBattle + 328, chance(rng, 85) ? unit(rng() % kUnitCount) : (chance(rng, 50) ? 0u : kUser));
    store32(m, kBattle + 344, owner(rng() % kUnitCount));
    for (u32 k = 0; k < 12; ++k) {
        u32 v = chance(rng, 15) ? 0u : unit(rng() % kUnitCount);
        if (chance(rng, 12)) v = kUser;
        store32(m, kBattle + 596 + 4 * k, v);
    }
    store32(m, kBattle + 644, chance(rng, 50) ? 0u : unit(rng() % kUnitCount));
    store32(m, kBattle + 3004, kStage);
    static const u16 kStages[] = {421, 432, 436, 429, 456, 421, 432, 436};
    store16(m, kStage + 8, chance(rng, 85) ? kStages[rng() % 8] : static_cast<u16>(rng()));
    store32(m, kBattle + 12, rng());
    store32(m, cb2::kBtlFlagsA, chance(rng, 10) ? 0u : kFlagA);
    store32(m, cb2::kBtlFlagsB, chance(rng, 10) ? 0u : kFlagB);
    // Field / event objects.
    store32(m, kFieldPtr, chance(rng, 15) ? 0u : kFieldObj);
    store32(m, kFieldObj + 60, kFieldWork);
    store32(m, cb2::kFieldFx, chance(rng, 20) ? 0u : kFxObj);
    store32(m, kFxObj + 60, kFxWork);
    store32(m, kFxClock, rng());
    for (u32 i = 0; i < 4; ++i) {
        store32(m, cb2::kFieldObjTable + 448 * i + 364, kTableObjs + 0x50 * i);
        store32(m, kTableObjs + 0x50 * i + 60, kTableWork + 4 * i);
    }
    // g_data words read as indices.
    store16(m, 0x836BA8u, static_cast<u16>(chance(rng, 85) ? rand_range(rng, 0, 11) : rand_range(rng, -2, 40)));
    store32(m, 0x7E4430u, chance(rng, 30) ? 0u : rng());
}

bool alive(const Machine& m, u32 dat) { return (load32(m, dat + 12) & 0x00080000u) == 0 && load16(m, dat + 8) != 0; }
// The documented rule of sub_2C0E30 as the handlers use it: the first listed unit (flags 1 | 8) of a side in
// `side_mask` whose DatUnit is alive and whose owner's id is `id`.
u32 expected_unit(const Machine& m, u32 id, u32 side_mask) {
    for (u32 u = load32(m, kBattle + 332); u != 0; u = load32(m, u + 1192)) {
        const u32 own = load32(m, u + 48);
        const u16 flags = load16(m, u + 26);
        if ((flags & 9u) != 9u || !((side_mask >> load8(m, own + 162)) & 1u)) continue;
        const u32 dat = load32(m, own + 2604);
        if (!alive(m, dat) || load16(m, own + 164) != id) continue;
        return u;
    }
    return 0;
}

// sub_2CFEB0 / sub_2D0150 pick among the living side-1 units with datCalcRand(count); with none listed the pick
// reads a stale frame slot (retail would too). The tests keep one candidate: unit 0 first in the list, alive.
void ensure_side1_candidate(Machine& m) {
    if (load32(m, kBattle + 332) == 0) {
        store32(m, kBattle + 332, unit(0));
        store32(m, unit(0) + 1192, 0);
    }
    store16(m, unit(0) + 26, static_cast<u16>(load16(m, unit(0) + 26) | 9u));
    m.at(owner(0) + 162)[0] = 1;
    if (load32(m, owner(0) + 2604) != 0) {
        store32(m, dat_unit(0) + 12, load32(m, dat_unit(0) + 12) & ~0x00080000u);
        store16(m, dat_unit(0) + 8, static_cast<u16>(load16(m, dat_unit(0) + 8) | 1u));
    }
}

}  // namespace

TEST_CASE("game(comm_b2): the battle COMM handlers equal their recompiled bodies, register file included") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0B20001u};
    int found = 0;
    for (int it = 0; it < 250; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        const s32 side = chance(rng, 85) ? rand_range(rng, 0, 1) : rand_range(rng, 2, 0x10001);
        const s32 id = chance(rng, 85) ? rand_range(rng, 0, 2) : static_cast<s32>(rng());
        set_args(m, rng, {side, id});
        clear_ret(m);
        pair(m, PAIR(fn_sub_2CE440_002ce440), seed, "sub_2CE440", rng);
        {
            const u32 s = static_cast<u32>(side) & 0xFFFFu;
            const u32 u = s <= 1 ? expected_unit(m, static_cast<u32>(id) & 0xFFFFu, s == 1 ? 2u : 1u) : 0u;
            CHECK(ret_value(m) == (load32(m, u + 8) | 0x80000000u));
            found += u != 0 ? 1 : 0;
        }
        set_args(m, rng, {side, id});
        pair(m, PAIR(fn_sub_2CBCD0_002cbcd0), seed, "sub_2CBCD0", rng);
        set_args(m, rng, {side, id});
        pair(m, PAIR(fn_sub_2CBD90_002cbd90), seed, "sub_2CBD90", rng);
        set_args(m, rng, {side, id});
        pair(m, PAIR(fn_sub_2CBE50_002cbe50), seed, "sub_2CBE50", rng);
        set_args(m, rng, {side, id});
        pair(m, PAIR(fn_sub_2CBF10_002cbf10), seed, "sub_2CBF10", rng);
        set_args(m, rng, {id});
        pair(m, PAIR(fn_sub_2CDA50_002cda50), seed, "sub_2CDA50", rng);
        set_args(m, rng, {id});
        pair(m, PAIR(fn_sub_2CDAD0_002cdad0), seed, "sub_2CDAD0", rng);
        set_args(m, rng, {id, static_cast<s32>(rng())});
        pair(m, PAIR(fn_sub_2CA900_002ca900), seed, "sub_2CA900", rng);
        set_args(m, rng, {side, id});
        pair(m, PAIR(fn_sub_2D12E0_002d12e0), seed, "sub_2D12E0", rng);
        // Random picks and scans.
        ensure_side1_candidate(m);
        fill_random(m, kEffRand, 16, rng);
        pair(m, PAIR(fn_sub_2CFEB0_002cfeb0), seed, "sub_2CFEB0", rng);
        fill_random(m, kEffRand, 16, rng);
        pair(m, PAIR(fn_sub_2D0150_002d0150), seed, "sub_2D0150", rng);
        pair(m, PAIR(fn_sub_2CC330_002cc330), seed, "sub_2CC330", rng);
        pair(m, PAIR(fn_sub_2CF9F0_002cf9f0), seed, "sub_2CF9F0", rng);
        set_args(m, rng, {chance(rng, 80) ? rand_range(rng, 0, 400) : static_cast<s32>(rng())});
        CHECK(pair(m, PAIR(fn_sub_2CDED0_002cded0), seed, "sub_2CDED0", rng) == ~u64{0});
        // Stage words and flags.
        pair(m, PAIR(fn_sub_2D06E0_002d06e0), seed, "sub_2D06E0", rng);
        CHECK(load16(m, kUser + 108) == 8);
        pair(m, PAIR(fn_sub_2D0720_002d0720), seed, "sub_2D0720", rng);
        pair(m, PAIR(fn_sub_2D0B90_002d0b90), seed, "sub_2D0B90", rng);
        pair(m, PAIR(fn_sub_2D0BD0_002d0bd0), seed, "sub_2D0BD0", rng);
        pair(m, PAIR(fn_sub_2D0C10_002d0c10), seed, "sub_2D0C10", rng);
        pair(m, PAIR(fn_sub_2D0C80_002d0c80), seed, "sub_2D0C80", rng);
        clear_ret(m);
        pair(m, PAIR(fn_sub_2D0860_002d0860), seed, "sub_2D0860", rng);
        pair(m, PAIR(fn_sub_2D0970_002d0970), seed, "sub_2D0970", rng);
        CHECK(ret_value(m) == (load16(m, kStage + 8) == 432 ? load32(m, kBattle + 2904) : 7u));
        pair(m, PAIR(fn_sub_2D0AC0_002d0ac0), seed, "sub_2D0AC0", rng);
        CHECK(ret_value(m) == (load32(m, kBattle + 2900) != 0 ? 1u : 0u));
        pair(m, PAIR(fn_sub_2D0C50_002d0c50), seed, "sub_2D0C50", rng);
        pair(m, PAIR(fn_sub_2D11D0_002d11d0), seed, "sub_2D11D0", rng);
        pair(m, PAIR(fn_sub_2D1260_002d1260), seed, "sub_2D1260", rng);
        pair(m, PAIR(fn_sub_2D12A0_002d12a0), seed, "sub_2D12A0", rng);
    }
    CHECK(found > 15);
}

TEST_CASE("game(comm_b2): the field / event COMM handlers equal their recompiled bodies, register file included") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0B20002u};
    int no_fx = 0;
    for (int it = 0; it < 250; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        pair(m, PAIR(fn_sub_1C5670_001c5670), seed, "sub_1C5670", rng);
        CHECK(ret_value(m) == (load32(m, kFieldPtr) ? load32(m, kFieldWork + 40) : 0u));
        pair(m, PAIR(fn_sub_425360_00425360), seed, "sub_425360", rng);
        for (u32 i = 0; i < 4; ++i) CHECK(load8(m, kTableWork + 4 * i) == 1);
        const bool fx = load32(m, cb2::kFieldFx) != 0;
        no_fx += fx ? 0 : 1;
        pair(m, PAIR(fn_sub_4254C0_004254c0), seed, "sub_4254C0", rng);
        pair(m, PAIR(fn_sub_425530_00425530), seed, "sub_425530", rng);
        pair(m, PAIR(fn_sub_425580_00425580), seed, "sub_425580", rng);
        set_args(m, rng, {chance(rng, 50) ? 0 : static_cast<s32>(rng())});
        pair(m, PAIR(fn_sub_4255D0_004255d0), seed, "sub_4255D0", rng);
        pair(m, PAIR(fn_sub_425640_00425640), seed, "sub_425640", rng);
        CHECK(ret_value(m) == (fx ? load32(m, kFxWork + 80) : 0xFFFFFFFFu));
        pair(m, PAIR(fn_sub_1C5460_001c5460), seed, "sub_1C5460", rng);
        pair(m, PAIR(fn_sub_35FD80_0035fd80), seed, "sub_35FD80", rng);
    }
    CHECK(no_fx > 20);
}

TEST_CASE("game(comm_b2): the g_data item / persona COMM handlers equal their recompiled bodies, register file included") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0B20003u};
    int counted = 0, copied = 0;
    for (int it = 0; it < 200; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        // Sparse lists: about half the slots empty.
        for (u32 pc = 0; pc < 13; ++pc)
            for (u32 k = 0; k < 20; ++k)
                if (chance(rng, 50)) store32(m, kSlotPairs + 868 * pc + 4 * k, chance(rng, 50) ? 0u : (rng() & 0x7FFF0000u));
        for (u32 k = 0; k < 21; ++k)
            if (chance(rng, it % 3 == 0 ? 3 : 25)) store16(m, kInventory + 20 * k, 0);
        for (u32 pc = 0; pc < 13; ++pc)
            for (u32 k = 0; k < 4; ++k)
                if (chance(rng, 40)) store16(m, kPersonaUsed + 868 * pc + 20 * k, 0);
        for (u32 r = 1; r <= 3; ++r) {
            store32(m, kFieldTable + 448 * r, chance(rng, 25) ? 0u : rng());
            store32(m, kFieldTable + 448 * r + 12, chance(rng, 25) ? 0u : rng());
            store16(m, kFieldTable + 448 * r + 352, static_cast<u16>(rand_range(rng, 0, 12)));
        }
        const s32 pc = chance(rng, 85) ? rand_range(rng, 1, 11) : rand_range(rng, -2, 14);
        const s32 k = chance(rng, 85) ? rand_range(rng, 0, 12) : rand_range(rng, -3, 25);
        set_args(m, rng, {pc});
        clear_ret(m);
        pair(m, PAIR(fn_sub_4244E0_004244e0), seed, "sub_4244E0", rng);
        if (pc >= 1 && pc <= 11) {
            u32 n = 0;
            for (u32 j = 0; j < 20; ++j) n += static_cast<s16>(load16(m, kSlotPairs + 868 * static_cast<u32>(pc) + 4 * j + 2)) > 0 ? 1u : 0u;
            CHECK(ret_value(m) >= n);
            counted += n > 0 ? 1 : 0;
        } else {
            CHECK(ret_value(m) == 0);
        }
        set_args(m, rng, {pc, k});
        pair(m, PAIR(fn_sub_4245C0_004245c0), seed, "sub_4245C0", rng);
        set_args(m, rng, {pc, k});
        pair(m, PAIR(fn_sub_424730_00424730), seed, "sub_424730", rng);
        set_args(m, rng, {pc, k});
        pair(m, PAIR(fn_sub_424880_00424880), seed, "sub_424880", rng);
        set_args(m, rng, {pc});
        pair(m, PAIR(fn_sub_4249B0_004249b0), seed, "sub_4249B0", rng);
        if (pc >= 1 && pc <= 11)
            for (u32 j = 0; j < 20; ++j) CHECK(load32(m, kSlotPairs + 868 * static_cast<u32>(pc) + 4 * j) == 0);
        // Koromaru's persona slots and equipment.
        pair(m, PAIR(fn_sub_1C4F70_001c4f70), seed, "sub_1C4F70", rng);
        const u32 owned = ret_value(m);
        CHECK(owned <= 8);
        set_args(m, rng, {rand_range(rng, -1, 8)});
        pair(m, PAIR(fn_sub_1C5040_001c5040), seed, "sub_1C5040", rng);
        pair(m, PAIR(fn_sub_1C5180_001c5180), seed, "sub_1C5180", rng);
        copied += owned > 0 ? 1 : 0;
        set_args(m, rng, {chance(rng, 90) ? rand_range(rng, 2, 11) : rand_range(rng, 0, 12)});
        pair(m, PAIR(fn_sub_1C4E50_001c4e50), seed, "sub_1C4E50", rng);
    }
    CHECK(counted > 50);
    CHECK(copied > 50);
}

TEST_CASE("game(comm_b2): the party / persona / social COMM handlers equal their recompiled bodies, register file included") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0B20004u};
    int found = 0, due = 0;
    for (int it = 0; it < 200; ++it) {
        seed_world(m, rng);
        const u32 seed = rng();
        store32(m, 0x95B718u, kSocialTable);
        for (u32 i = 0; i < 64; ++i) {
            store32(m, kSocialState + 4 * i, chance(rng, 6) ? 1u : rng() % 3);
            store32(m, kSocialState + 256 + 4 * i, chance(rng, 70) ? 0u : rng());
            m.at(kSocialTable + 32 * i + 2)[0] = static_cast<u8>(rand_range(rng, 1, 12));
            m.at(kSocialTable + 32 * i + 3)[0] = static_cast<u8>(rand_range(rng, 1, 31));
        }
        store16(m, 0x83679Cu, static_cast<u16>(rand_range(rng, 0, 400)));
        store32(m, kTask + scr::kMessageId, chance(rng, 90) ? rng() % 100 : 0xFFFFFFF0u);
        const s32 pc = chance(rng, 85) ? rand_range(rng, 1, 11) : rand_range(rng, 0, 12);
        set_args(m, rng, {pc});
        pair(m, PAIR(fn_sub_1C2F20_001c2f20), seed, "sub_1C2F20", rng);
        set_args(m, rng, {static_cast<s32>(rng())});
        pair(m, PAIR(fn_sub_2CD7F0_002cd7f0), seed, "sub_2CD7F0", rng);
        const s32 min_hp = chance(rng, 80) ? rand_range(rng, 0, 600) : static_cast<s32>(rng());
        const s32 percent = chance(rng, 80) ? rand_range(rng, 0, 150) : static_cast<s32>(rng());
        static const s32 kMasks[] = {0, 0, 0x80000, 0x1, 0x400, 0x80001};
        const s32 mask = chance(rng, 85) ? kMasks[rng() % 6] : static_cast<s32>(rng());
        set_args(m, rng, {min_hp, percent, mask});
        clear_ret(m);
        pair(m, PAIR(fn_sub_2D03E0_002d03e0), seed, "sub_2D03E0", rng);
        found += ret_value(m) != 0xFFFFFFFFu ? 1 : 0;
        CHECK(pair(m, PAIR(fn_sub_2CDE10_002cde10), seed, "sub_2CDE10", rng) == ~u64{0});
        CHECK(pair(m, PAIR(fn_sub_2CDE60_002cde60), seed, "sub_2CDE60", rng) == ~u64{0});
        const s32 stat = chance(rng, 85) ? rand_range(rng, 0, 4) : rand_range(rng, 5, 7);
        set_args(m, rng, {pc, stat, rand_range(rng, -5, 5)});
        pair(m, PAIR(fn_sub_35FC70_0035fc70), seed, "sub_35FC70", rng);
        clear_ret(m);
        pair(m, PAIR(fn_sub_360090_00360090), seed, "sub_360090", rng);
        CHECK((ret_value(m) == 0 || ret_value(m) == 1));
        due += ret_value(m) == 1 ? 1 : 0;
    }
    CHECK(found > 10);
    CHECK(due > 20);
}

TEST_CASE("game(comm_b2): the AI-condition COMM handlers (jalr through the condition table) equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0B20005u};
    // The condition functions: a third of the iterations use the ELF's own for the entries whose callees run on
    // this test world (0x22, 0x25, 40, 67..69; the persona-based ones need real persona tables and get sub_2C1710
    // there), a third sub_2C1710 (non-leaf: spills $ra below the $sp it receives) and a third sub_2C22D0 (a leaf),
    // so the frame and link of each jalr are compared with known callees too.
    constexpr u32 kTbl = cb2::kAiConditions;
    static const u32 kEntries[] = {1, 2, 6, 0x16, 0x17, 0x18, 0x19, 0x22, 0x25, 40, 45, 67, 68, 69};
    std::vector<u32> original;
    for (u32 e : kEntries) original.push_back(load32(m, kTbl + 12 * e));
    int yes = 0, no = 0;
    for (int it = 0; it < 150; ++it) {
        seed_world(m, rng);
        const int mode = it % 3;  // 0: the ELF's functions, 1: sub_2C1710, 2: sub_2C22D0
        for (std::size_t k = 0; k < std::size(kEntries); ++k)
            store32(m, kTbl + 12 * kEntries[k],
                    mode == 0 ? (kEntries[k] >= 0x22 && kEntries[k] != 45 ? original[k] : 0x2C1710u)
                              : (mode == 1 ? 0x2C1710u : 0x2C22D0u));
        const u32 seed = rng();
        const auto cond = [&](Fn hand, Fn recomp, const char* what, int argc) {
            const s32 id = chance(rng, 85) ? rand_range(rng, 0, 2) : static_cast<s32>(rng());
            const s32 arg = chance(rng, 70) ? rand_range(rng, 0, 0x100) : static_cast<s32>(rng());
            if (argc == 2) set_args(m, rng, {id, arg});
            if (argc == 1) set_args(m, rng, {id});
            clear_ret(m);
            pair(m, hand, recomp, seed, what, rng);
            CHECK((ret_value(m) == 0 || ret_value(m) == 1));
            (ret_value(m) ? yes : no) += 1;
        };
        cond(PAIR(fn_sub_2CA480_002ca480), "sub_2CA480", 2);
        cond(PAIR(fn_sub_2CA590_002ca590), "sub_2CA590", 2);
        cond(PAIR(fn_sub_2CA6A0_002ca6a0), "sub_2CA6A0", 2);
        cond(PAIR(fn_sub_2CA9D0_002ca9d0), "sub_2CA9D0", 2);
        cond(PAIR(fn_sub_2CAAE0_002caae0), "sub_2CAAE0", 2);
        cond(PAIR(fn_sub_2CABF0_002cabf0), "sub_2CABF0", 2);
        cond(PAIR(fn_sub_2CAD00_002cad00), "sub_2CAD00", 2);
        cond(PAIR(fn_sub_2CAE10_002cae10), "sub_2CAE10", 2);
        cond(PAIR(fn_sub_2CAF20_002caf20), "sub_2CAF20", 2);
        cond(PAIR(fn_sub_2CB030_002cb030), "sub_2CB030", 1);
        cond(PAIR(fn_sub_2CB0E0_002cb0e0), "sub_2CB0E0", 1);
        cond(PAIR(fn_sub_2CBA00_002cba00), "sub_2CBA00", 0);
        cond(PAIR(fn_sub_2CBA50_002cba50), "sub_2CBA50", 0);
        cond(PAIR(fn_sub_2CBAA0_002cbaa0), "sub_2CBAA0", 0);
    }
    for (std::size_t k = 0; k < std::size(kEntries); ++k) store32(m, kTbl + 12 * kEntries[k], original[k]);
    CHECK(yes > 100);
    CHECK(no > 100);
    MESSAGE("comm_b2 pairs run so far: " << pairs_run);
}

#endif  // P3FES_GAME_HAVE_GENERATED
