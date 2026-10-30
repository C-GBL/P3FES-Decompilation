// Phase 5 pair tests for the COMM handlers of indices 0-250 (game/src/script/comm_a.cpp, slice script_comm_a): each
// hand-written handler and the recompiled body it replaces run on identical guest machines (pair_harness.h: $v0,
// callee-saved registers, $sp/$ra, virtual cycles, check-point count, the arena, the caller's stack) and must also
// leave the same bytes in the dead stack (the hand versions perform the original prologue and keep the original
// values in $sN and $ra across their calls, so every frame byte matches), in low RAM (stores through a null record
// pointer) and in the whole .data/.bss band 0x680000-0x9E0000 (the gp words, the save-data block at 0x83xxxx with
// the party list, the money word, the social-link and persona tables, the battle/event records at 0x957BC0).
//
// The machine: a ScrTask in the arena with the arguments in its slots (argument i = slot sp - 1 - i, int tags and
// now and then a float tag), g_scrCurrentTask pointing at it, the save-data block 0x834000-0x840000 filled with
// random bytes (the getters below the handlers read it), the field record / floor record / event config record /
// social context in the arena (or null, for the asserted paths). Arguments come from each handler's domain plus
// edge cases (negative, out-of-range, the 16-bit and 8-bit truncation boundaries); writers get bounded indices so
// their stores stay inside the compared band. A few documented rules are checked on the host independently of both
// bodies (the money clamp, the party add/remove, the floor classes, the event config bytes).
#include "pair_harness.h"

#include "p3fes/game/comm_a.h"
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
P3FES_DECL_PAIR(fn_sub_1C2500_001c2500)
P3FES_DECL_PAIR(fn_sub_1C2610_001c2610)
P3FES_DECL_PAIR(fn_sub_1C2690_001c2690)
P3FES_DECL_PAIR(fn_sub_1C26C0_001c26c0)
P3FES_DECL_PAIR(fn_sub_1C26F0_001c26f0)
P3FES_DECL_PAIR(fn_sub_1C2720_001c2720)
P3FES_DECL_PAIR(fn_sub_1C2750_001c2750)
P3FES_DECL_PAIR(fn_sub_1C2780_001c2780)
P3FES_DECL_PAIR(fn_sub_16EA80_0016ea80)
P3FES_DECL_PAIR(fn_sub_16EC40_0016ec40)
P3FES_DECL_PAIR(fn_sub_1C2830_001c2830)
P3FES_DECL_PAIR(fn_sub_1C28D0_001c28d0)
P3FES_DECL_PAIR(fn_sub_1C2EA0_001c2ea0)
P3FES_DECL_PAIR(fn_sub_3111C0_003111c0)
P3FES_DECL_PAIR(fn_sub_30FDC0_0030fdc0)
P3FES_DECL_PAIR(fn_sub_350190_00350190)
P3FES_DECL_PAIR(fn_sub_3112E0_003112e0)
P3FES_DECL_PAIR(fn_sub_4243D0_004243d0)
P3FES_DECL_PAIR(fn_sub_424470_00424470)
P3FES_DECL_PAIR(fn_sub_424480_00424480)
P3FES_DECL_PAIR(fn_sub_4244A0_004244a0)
P3FES_DECL_PAIR(fn_sub_1C2ED0_001c2ed0)
P3FES_DECL_PAIR(fn_sub_1C2FA0_001c2fa0)
P3FES_DECL_PAIR(fn_sub_1C3050_001c3050)
P3FES_DECL_PAIR(fn_sub_1C30A0_001c30a0)
P3FES_DECL_PAIR(fn_sub_1C3150_001c3150)
P3FES_DECL_PAIR(fn_sub_1C31A0_001c31a0)
P3FES_DECL_PAIR(fn_sub_1C3370_001c3370)
P3FES_DECL_PAIR(fn_sub_1C33C0_001c33c0)
P3FES_DECL_PAIR(fn_sub_1C3410_001c3410)
P3FES_DECL_PAIR(fn_sub_1C3460_001c3460)
P3FES_DECL_PAIR(fn_sub_1C34B0_001c34b0)
P3FES_DECL_PAIR(fn_sub_1C3540_001c3540)
P3FES_DECL_PAIR(fn_sub_1C3690_001c3690)
P3FES_DECL_PAIR(fn_sub_1C3710_001c3710)
P3FES_DECL_PAIR(fn_sub_35FBD0_0035fbd0)
P3FES_DECL_PAIR(fn_sub_16EDD0_0016edd0)
P3FES_DECL_PAIR(fn_sub_16EE00_0016ee00)
P3FES_DECL_PAIR(fn_sub_16EE90_0016ee90)
P3FES_DECL_PAIR(fn_sub_16EC80_0016ec80)
P3FES_DECL_PAIR(fn_sub_16ECD0_0016ecd0)
P3FES_DECL_PAIR(fn_sub_1C3790_001c3790)
P3FES_DECL_PAIR(fn_sub_1C3880_001c3880)
P3FES_DECL_PAIR(fn_sub_1C38B0_001c38b0)
P3FES_DECL_PAIR(fn_sub_1C39E0_001c39e0)
P3FES_DECL_PAIR(fn_sub_1C3A70_001c3a70)
P3FES_DECL_PAIR(fn_sub_1C3AA0_001c3aa0)
P3FES_DECL_PAIR(fn_sub_1C3B00_001c3b00)
P3FES_DECL_PAIR(fn_sub_35F1B0_0035f1b0)
P3FES_DECL_PAIR(fn_sub_35F210_0035f210)
P3FES_DECL_PAIR(fn_sub_35F360_0035f360)
P3FES_DECL_PAIR(fn_sub_35FF80_0035ff80)
P3FES_DECL_PAIR(fn_sub_360020_00360020)
P3FES_DECL_PAIR(fn_sub_360280_00360280)
P3FES_DECL_PAIR(fn_sub_360300_00360300)
P3FES_DECL_PAIR(fn_sub_3603D0_003603d0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::comm_a;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// --- the arena layout -------------------------------------------------------------------------------------------
constexpr u32 kTask = kArena + 0x000;         // ScrTask (252 bytes)
constexpr u32 kField = kArena + 0x400;        // the field record (+8 u16, +284 floor pointer, +288 ...)
constexpr u32 kFloor = kArena + 0x800;        // the floor record (+2 u16 floor id, +6 u8)
constexpr u32 kEventCfg = kArena + 0x900;     // the event config record (bytes +0..+10)
constexpr u32 kSocialCtx = kArena + 0xA00;    // the social context (words +16..+24)
constexpr u32 kObj1BFF20 = kArena + 0xB00;    // K_FldDungeon_GetCurrentFloor's record chain ($gp - 19080 -> +60 -> +4)

constexpr u32 kSaveData = 0x834000u;          // the save-data block the getters read (random bytes)
constexpr u32 kSaveDataLen = 0xC000u;
// The compared band: .data/.bss, wide enough for the 52-byte social-link records `0x836BAC + 52 * index` that
// sub_174710 (under [208]) writes through for any s16 index (0x696000..0x9D7000).
constexpr u32 kBandLo = 0x680000u, kBandHi = 0x9E0000u;
constexpr u32 kCurrentLink = 0x836BA8u;       // s16: the social-link index sub_175360 returns
constexpr u32 kPtr1BFF20 = 0x7CE268u;         // $gp - 19080

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region>& regions() {
    static const std::vector<Region> r = {{kArena, kArenaSize}, {0, 0x1000}, {kBandLo, kBandHi - kBandLo}};
    return r;
}

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
s16 load16s(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rr(std::mt19937& rng, s32 lo, s32 hi) { return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1)); }
bool one_in(std::mt19937& rng, u32 n) { return rng() % n == 0; }
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}

// The COMM argument stack of the task: argument i in slot sp - 1 - i (a few junk slots below the arguments).
// Now and then an argument goes in as a float (tag 1), which scrGetIntPara converts with cvt.w.s.
void set_args(Machine& m, std::mt19937& rng, const std::vector<s32>& args, bool floats = true) {
    const u32 junk = rng() % 4;
    const u32 sp = static_cast<u32>(args.size()) + junk;
    store32(m, kTask + scr::kSp, sp);
    for (u32 i = 0; i < args.size(); ++i) {
        const u32 slot = sp - 1 - i;
        const bool as_float = floats && one_in(rng, 10);
        m.at(kTask + scr::kTags + slot)[0] = static_cast<u8>(as_float ? scr::kTagFloat : scr::kTagInt);
        store32(m, kTask + scr::kValues + slot * 4, as_float ? fbits(static_cast<float>(args[i])) : static_cast<u32>(args[i]));
    }
}
u32 ret_value(const Machine& m) { return load32(m, kTask + scr::kValues + scr::kReturnSlot * 4); }
s8 ret_tag(const Machine& m) { return static_cast<s8>(m.mem.main_ram()[kTask + scr::kTags + scr::kReturnSlot]); }

// The world every case starts from.
void seed_world(Machine& m, std::mt19937& rng) {
    fill_random(m, kArena, kArenaSize, rng);
    fill_random(m, 0, 0x1000, rng);
    fill_random(m, kSaveData, kSaveDataLen, rng);
    store32(m, scr::kCurrentTask, kTask);
    // the party: member ids 0..10 (0 = empty), duplicates allowed
    for (u32 i = 0; i < kPartyCount; ++i) store16(m, kParty + 2 * i, static_cast<u16>(one_in(rng, 3) ? 0 : rr(rng, 1, 10)));
    // money: anywhere below the limit, sometimes at it or (corrupt) above or negative
    const u32 money_kind = rng() % 8;
    store32(m, kMoney, money_kind == 0 ? kMoneyLimit - 1 : money_kind == 1 ? static_cast<u32>(rr(rng, -100, 100))
                                     : money_kind == 2 ? kMoneyLimit + rng() % 100 : rng() % kMoneyLimit);
    // the field record and its floor record
    store32(m, kFieldPtr, kField);
    store32(m, kField + kFieldFloorPtr, kFloor);
    static const u16 floors[] = {4021, 3999, 4000, 4001, 4999, 5000, 5001, 0, 65535, 4020, 4022};
    store16(m, kFloor + 2, one_in(rng, 3) ? static_cast<u16>(rng()) : floors[rng() % (sizeof floors / sizeof floors[0])]);
    // the event config record (null now and then: the stores go to low RAM)
    store32(m, kEventCfgPtr, one_in(rng, 8) ? 0u : kEventCfg);
    if (one_in(rng, 3)) m.at(kEventCfg + 8)[0] = 1;
    // the social context (null now and then: asserted, then read through null)
    store32(m, kSocialCtxPtr, one_in(rng, 8) ? 0u : kSocialCtx);
    store32(m, kSocialCtxArg, static_cast<u32>(rr(rng, 0, 30)));
    // K_FldDungeon_GetCurrentFloor's chain: null or a record whose +60 points at a word pair
    store32(m, kPtr1BFF20, one_in(rng, 2) ? 0u : kObj1BFF20);
    store32(m, kObj1BFF20 + 60, kObj1BFF20 + 0x40);
    // the current social-link index (sub_175360): mostly a small one, now and then any s16
    if (!one_in(rng, 8)) store16(m, kCurrentLink, static_cast<u16>(rr(rng, 0, 30)));
    // sub_35F360's four candidate persona ids
    for (u32 k = 0; k < 4; ++k) store16(m, kPersonaIds4 + 2 * k, static_cast<u16>(rr(rng, 0, 200)));
}

// A pair over every region (pair_harness expect_same plus the regions, $ra/$sp and the dead stack). Afterwards
// the recompiled run's output is in place.
struct Pair2 {
    Outcome hand, recomp;
    bool faulted = false;  // both bodies stopped at the same fault (pair_harness.h fault_of)
};
int g_faulted_pairs = 0;
Pair2 pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const std::string& what) {
    // The band (3.5 MiB) goes through a PairRange (write_tracker.h): the same snapshot / restore / compare, but only
    // the pages written are copied (copying it into fresh vectors was ~10 ms a pair, nearly all of this file's time).
    const Region& band = regions().back();
    std::vector<std::vector<u8>> before, after_hand;
    for (const Region& r : regions()) before.push_back(&r == &band ? std::vector<u8>{} : m.bytes(r.va, r.len));
    PairRange band_pair(m.at(band.va), m.at(band.va + band.len));
    Pair2 p;
    const std::string fh = fault_of([&] { p.hand = run(m, hand, args, seed); });
    for (const Region& r : regions()) after_hand.push_back(&r == &band ? std::vector<u8>{} : m.bytes(r.va, r.len));
    band_pair.between();
    std::size_t i = 0;
    for (const Region& r : regions()) {
        if (&r != &band) std::memcpy(m.at(r.va), before[i].data(), r.len);
        ++i;
    }
    const std::string fr = fault_of([&] { p.recomp = run(m, recomp, args, seed); });
    INFO(what);
    if (!fh.empty() || !fr.empty()) {  // a pointer of the random world the original itself faults on
        CHECK(fh == fr);
        std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
        ++g_faulted_pairs;
        p.faulted = true;
        return p;
    }
    expect_same(p.hand, p.recomp, what.c_str());
    CHECK(p.hand.dead_stack == p.recomp.dead_stack);
    i = 0;
    for (const Region& r : regions()) {
        std::size_t k = 0;
        bool same;
        if (&r == &band) {
            k = band_pair.first_difference();
            same = k == band_pair.size();
        } else {
            const std::vector<u8> now = m.bytes(r.va, r.len);
            same = after_hand[i] == now;
            while (!same && k < now.size() && now[k] == after_hand[i][k]) ++k;
        }
        if (!same) {
            INFO("region 0x" << std::hex << r.va << " first difference at 0x" << (r.va + k));
            CHECK(same);
        }
        ++i;
    }
    return p;
}

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// An argument generator per handler.
using ArgGen = std::vector<s32> (*)(std::mt19937&);
struct Case {
    const char* name;
    Fn hand;
    Fn recomp;
    ArgGen args;
};

s32 any_int(std::mt19937& rng) {
    switch (rng() % 6) {
        case 0: return static_cast<s32>(rng());
        case 1: return rr(rng, -3, 3);
        case 2: return 0x7FFF + rr(rng, -2, 2);   // the 16-bit truncation boundary
        case 3: return -0x8000 + rr(rng, -2, 2);
        case 4: return 0x7F + rr(rng, -2, 2);     // the 8-bit one
        default: return rr(rng, 0, 300);
    }
}
s32 member(std::mt19937& rng) { return one_in(rng, 10) ? rr(rng, -2, 15) : rr(rng, 0, 10); }   // party member / character
s32 persona(std::mt19937& rng) { return one_in(rng, 10) ? rr(rng, -2, 400) : rr(rng, 0, 200); }  // persona id
std::vector<s32> none(std::mt19937&) { return {}; }
std::vector<s32> two_any(std::mt19937& rng) { return {any_int(rng), any_int(rng)}; }
std::vector<s32> four_any(std::mt19937& rng) { return {any_int(rng), any_int(rng), any_int(rng), any_int(rng)}; }
std::vector<s32> one_member(std::mt19937& rng) { return {member(rng)}; }
std::vector<s32> one_persona(std::mt19937& rng) { return {persona(rng)}; }

const std::vector<Case>& cases() {
    static const std::vector<Case> c = {
        {"sub_1C2500 [121]", PAIR(fn_sub_1C2500_001c2500), two_any},
        {"sub_1C2610 [14]", PAIR(fn_sub_1C2610_001c2610), two_any},
        {"sub_1C2690 [127]", PAIR(fn_sub_1C2690_001c2690), none},
        {"sub_1C26C0 [128]", PAIR(fn_sub_1C26C0_001c26c0), none},
        {"sub_1C26F0 [129]", PAIR(fn_sub_1C26F0_001c26f0), none},
        {"sub_1C2720 [130]", PAIR(fn_sub_1C2720_001c2720), none},
        {"sub_1C2750 [131]", PAIR(fn_sub_1C2750_001c2750), none},
        {"sub_1C2780 [132]",
         PAIR(fn_sub_1C2780_001c2780),
         [](std::mt19937& rng) -> std::vector<s32> {
             // valid month/day pairs only: clndIsDateInRange walks the calendar one month at a time until it meets
             // the date, so a month outside 1..12 runs for minutes (the same in both bodies)
             return {rr(rng, 1, 12), rr(rng, 1, 31), rr(rng, 1, 12), rr(rng, 1, 31)};
         }},
        {"sub_16EA80 [133]", PAIR(fn_sub_16EA80_0016ea80), [](std::mt19937& rng) -> std::vector<s32> { return {any_int(rng), member(rng)}; }},
        {"sub_16EC40 [134]", PAIR(fn_sub_16EC40_0016ec40), [](std::mt19937& rng) -> std::vector<s32> { return {rr(rng, -4, 8)}; }},
        {"sub_1C2830 [135]", PAIR(fn_sub_1C2830_001c2830), four_any},
        {"sub_1C28D0 [136]", PAIR(fn_sub_1C28D0_001c28d0), none},
        {"sub_1C2EA0 [138]", PAIR(fn_sub_1C2EA0_001c2ea0), none},
        {"sub_3111C0 [48]", PAIR(fn_sub_3111C0_003111c0), none},
        {"sub_30FDC0 [50]", PAIR(fn_sub_30FDC0_0030fdc0), two_any},
        {"sub_350190 [145]", PAIR(fn_sub_350190_00350190), two_any},
        {"sub_3112E0 [147]", PAIR(fn_sub_3112E0_003112e0), none},
        {"sub_4243D0 [189]",
         PAIR(fn_sub_4243D0_004243d0),
         [](std::mt19937& rng) -> std::vector<s32> {
             return {any_int(rng), any_int(rng), any_int(rng), any_int(rng), any_int(rng), any_int(rng)};
         }},
        {"sub_424470 [190]", PAIR(fn_sub_424470_00424470), none},
        {"sub_424480 [191]", PAIR(fn_sub_424480_00424480), none},
        {"sub_4244A0 [206]", PAIR(fn_sub_4244A0_004244a0), [](std::mt19937& rng) -> std::vector<s32> { return {any_int(rng)}; }},
        {"sub_1C2ED0 [192]", PAIR(fn_sub_1C2ED0_001c2ed0), one_member},
        {"sub_1C2FA0 [193]", PAIR(fn_sub_1C2FA0_001c2fa0), one_member},
        {"sub_1C3050 [194]", PAIR(fn_sub_1C3050_001c3050), one_member},
        {"sub_1C30A0 [195]", PAIR(fn_sub_1C30A0_001c30a0), one_member},
        {"sub_1C3150 [196]", PAIR(fn_sub_1C3150_001c3150), one_member},
        {"sub_1C31A0 [197]", PAIR(fn_sub_1C31A0_001c31a0), [](std::mt19937& rng) -> std::vector<s32> { return {member(rng), rr(rng, -1, 3)}; }},
        {"sub_1C3370 [198]", PAIR(fn_sub_1C3370_001c3370), one_member},
        {"sub_1C33C0 [199]", PAIR(fn_sub_1C33C0_001c33c0), one_member},
        {"sub_1C3410 [200]", PAIR(fn_sub_1C3410_001c3410), one_member},
        {"sub_1C3460 [201]", PAIR(fn_sub_1C3460_001c3460), one_member},
        {"sub_1C34B0 [202]", PAIR(fn_sub_1C34B0_001c34b0), [](std::mt19937& rng) -> std::vector<s32> { return {member(rng), any_int(rng)}; }},
        {"sub_1C3540 [203]", PAIR(fn_sub_1C3540_001c3540), one_member},
        {"sub_1C3690 [204]", PAIR(fn_sub_1C3690_001c3690), [](std::mt19937& rng) -> std::vector<s32> { return {member(rng), rr(rng, -1, 5)}; }},
        {"sub_1C3710 [205]",
         PAIR(fn_sub_1C3710_001c3710),
         [](std::mt19937& rng) -> std::vector<s32> { return {member(rng), rr(rng, -1, 4), any_int(rng)}; }},
        {"sub_35FBD0 [208]", PAIR(fn_sub_35FBD0_0035fbd0), [](std::mt19937& rng) -> std::vector<s32> { return {rr(rng, -1, 6), any_int(rng)}; }},
        {"sub_16EDD0 [209]", PAIR(fn_sub_16EDD0_0016edd0), none},
        {"sub_16EE00 [210]",
         PAIR(fn_sub_16EE00_0016ee00),
         [](std::mt19937& rng) -> std::vector<s32> {
             return {one_in(rng, 3) ? any_int(rng) : rr(rng, 0, 2000000) * (one_in(rng, 5) ? 5 : 1)};
         }},
        {"sub_16EE90 [211]",
         PAIR(fn_sub_16EE90_0016ee90),
         [](std::mt19937& rng) -> std::vector<s32> { return {one_in(rng, 3) ? any_int(rng) : rr(rng, 0, 12000000)}; }},
        {"sub_16EC80 [212]", PAIR(fn_sub_16EC80_0016ec80), [](std::mt19937& rng) -> std::vector<s32> { return {rr(rng, -4, 8)}; }},
        {"sub_16ECD0 [213]", PAIR(fn_sub_16ECD0_0016ecd0), one_member},
        {"sub_1C3790 [215]", PAIR(fn_sub_1C3790_001c3790), none},
        {"sub_1C3880 [226]", PAIR(fn_sub_1C3880_001c3880), none},
        {"sub_1C38B0 [227]", PAIR(fn_sub_1C38B0_001c38b0), none},
        {"sub_1C39E0 [228]", PAIR(fn_sub_1C39E0_001c39e0), none},
        {"sub_1C3A70 [229]", PAIR(fn_sub_1C3A70_001c3a70), none},
        {"sub_1C3AA0 [230]", PAIR(fn_sub_1C3AA0_001c3aa0), none},
        {"sub_1C3B00 [232]", PAIR(fn_sub_1C3B00_001c3b00), none},
        {"sub_35F1B0 [124]", PAIR(fn_sub_35F1B0_0035f1b0), one_persona},
        {"sub_35F210 [186]", PAIR(fn_sub_35F210_0035f210), none},
        {"sub_35F360 [187]", PAIR(fn_sub_35F360_0035f360), none},
        {"sub_35FF80 [224]", PAIR(fn_sub_35FF80_0035ff80), [](std::mt19937& rng) -> std::vector<s32> { return {rr(rng, -2, 4)}; }},
        {"sub_360020 [225]", PAIR(fn_sub_360020_00360020), [](std::mt19937& rng) -> std::vector<s32> { return {rr(rng, -1, 3)}; }},
        {"sub_360280 [218]", PAIR(fn_sub_360280_00360280), one_persona},
        {"sub_360300 [219]", PAIR(fn_sub_360300_00360300), one_persona},
        {"sub_3603D0 [220]", PAIR(fn_sub_3603D0_003603d0), one_persona},
    };
    return c;
}

}  // namespace

TEST_CASE("game(script_comm_a): the constants are what the ELF holds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    // sScrCommandTable: the handlers of this slice at their indices with their argc.
    struct Row {
        u32 index, fn, argc;
    };
    static const Row rows[] = {{14, 0x1C2610, 2},  {48, 0x3111C0, 0},  {50, 0x30FDC0, 2},  {121, 0x1C2500, 2}, {124, 0x35F1B0, 1},
                               {127, 0x1C2690, 0}, {132, 0x1C2780, 4}, {133, 0x16EA80, 2}, {145, 0x350190, 2}, {186, 0x35F210, 0},
                               {187, 0x35F360, 0}, {189, 0x4243D0, 6}, {197, 0x1C31A0, 2}, {205, 0x1C3710, 3}, {213, 0x16ECD0, 1},
                               {224, 0x35FF80, 1}, {229, 0x1C3A70, 0}, {232, 0x1C3B00, 0}};
    for (const Row& r : rows) {
        INFO("COMM " << r.index);
        CHECK(load32(m, 0x7B92B0u + 8 * r.index) == r.fn);
        CHECK(load32(m, 0x7B92B0u + 8 * r.index + 4) == r.argc);
    }
    CHECK(load32(m, 0x7BA260u) == 502);  // the table's entry count
    // the K_Assert file arguments are strings
    CHECK(m.str(kFileDatMisc).size() > 2);
    CHECK(m.str(kFileScrCommand).size() > 2);
    CHECK(m.str(kFileFieldCommand).size() > 2);
}

TEST_CASE("game(script_comm_a): every handler equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0AA0250u};
    int pairs = 0;
    for (const Case& c : cases()) {
        for (int it = 0; it < 64; ++it) {
            seed_world(m, rng);
            set_args(m, rng, c.args(rng));
            pair(m, c.hand, c.recomp, Args{rng(), rng(), rng(), rng()}, rng(), std::string(c.name) + " #" + std::to_string(it));
            ++pairs;
        }
    }
    MESSAGE("script_comm_a: " << pairs << " pairs over " << cases().size() << " handlers");
}

TEST_CASE("game(script_comm_a): the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5EEDu};

    // money: += clamps at 9,999,999; -= floors at 0; the getter returns the word.
    for (int it = 0; it < 64; ++it) {
        seed_world(m, rng);
        const s32 money = static_cast<s32>(rng() % kMoneyLimit);
        store32(m, kMoney, static_cast<u32>(money));
        const s32 add = rr(rng, 0, 3000000);
        set_args(m, rng, {add}, false);
        pair(m, PAIR(fn_sub_16EE00_0016ee00), Args{}, rng(), "money +=");
        const s64 expect_add = static_cast<s64>(money) + add;
        CHECK(static_cast<s32>(load32(m, kMoney)) == (expect_add >= kMoneyLimit ? static_cast<s32>(kMoneyLimit - 1) : expect_add));
        const s32 now = static_cast<s32>(load32(m, kMoney));
        const s32 sub = rr(rng, 0, 12000000);
        set_args(m, rng, {sub}, false);
        pair(m, PAIR(fn_sub_16EE90_0016ee90), Args{}, rng(), "money -=");
        CHECK(static_cast<s32>(load32(m, kMoney)) == (now < sub ? 0 : now - sub));
        pair(m, PAIR(fn_sub_16EDD0_0016edd0), Args{}, rng(), "money");
        CHECK(ret_value(m) == load32(m, kMoney));
        CHECK(ret_tag(m) == scr::kTagInt);
    }

    // the party: add puts a new member into the first empty slot of 0-2 (else slot 2) and leaves a member that is
    // already in slots 0-2 alone; remove clears the member's slot and closes the gap.
    for (int it = 0; it < 64; ++it) {
        seed_world(m, rng);
        s16 party[4];
        for (u32 i = 0; i < 4; ++i) party[i] = load16s(m, kParty + 2 * i);
        const s16 who = static_cast<s16>(rr(rng, 1, 10));
        set_args(m, rng, {0, who}, false);
        pair(m, PAIR(fn_sub_16EA80_0016ea80), Args{}, rng(), "party add");
        s16 expect[4] = {party[0], party[1], party[2], party[3]};
        if (party[0] != who && party[1] != who && party[2] != who) {
            u32 k = 0;
            while (k < 3 && expect[k] != 0) ++k;
            expect[k < 3 ? k : 2] = who;
        }
        for (u32 i = 0; i < 4; ++i) CHECK(load16s(m, kParty + 2 * i) == expect[i]);

        for (u32 i = 0; i < 4; ++i) party[i] = load16s(m, kParty + 2 * i);
        const s16 gone = one_in(rng, 2) ? party[rng() % 4] : static_cast<s16>(rr(rng, 1, 10));
        set_args(m, rng, {gone}, false);
        pair(m, PAIR(fn_sub_16ECD0_0016ecd0), Args{}, rng(), "party remove");
        s16 after[4] = {party[0], party[1], party[2], party[3]};
        for (u32 i = 0; i < 4; ++i)
            if (after[i] == gone) {
                after[i] = 0;
                break;
            }
        for (u32 j = 0; j < 4; ++j)
            if (after[j] == 0) {
                for (u32 k = j; k < 3; ++k) after[k] = after[k + 1];
                break;
            }
        for (u32 i = 0; i < 4; ++i) CHECK(load16s(m, kParty + 2 * i) == after[i]);
        // the slot getter
        const s32 slot = rr(rng, 0, 3);
        set_args(m, rng, {slot}, false);
        pair(m, PAIR(fn_sub_16EC80_0016ec80), Args{}, rng(), "party slot");
        CHECK(static_cast<s32>(ret_value(m)) == load16s(m, kParty + 2 * static_cast<u32>(slot)));
    }

    // the floor classes of [227] and the floor id of [228] / [229]
    struct FloorClass {
        u16 id;
        u32 cls;
    };
    static const FloorClass floors[] = {{4021, 1}, {5000, 0}, {65535, 0}, {4999, 1}, {4000, 1}, {3999, 2}, {0, 2}, {4022, 1}};
    for (const FloorClass& f : floors) {
        seed_world(m, rng);
        store16(m, kFloor + 2, f.id);
        pair(m, PAIR(fn_sub_1C38B0_001c38b0), Args{}, rng(), "floor class");
        CHECK(ret_value(m) == f.cls);  // 4021 sets 3 first, then the >= 4000 class
        pair(m, PAIR(fn_sub_1C39E0_001c39e0), Args{}, rng(), "floor id");
        CHECK(ret_value(m) == f.id);
        pair(m, PAIR(fn_sub_1C3A70_001c3a70), Args{}, rng(), "floor id (second copy)");
        CHECK(ret_value(m) == f.id);
    }

    // the event config bytes and the wait on +8
    for (int it = 0; it < 16; ++it) {
        seed_world(m, rng);
        store32(m, kEventCfgPtr, kEventCfg);
        std::vector<s32> six;
        for (int k = 0; k < 6; ++k) six.push_back(any_int(rng));
        set_args(m, rng, six, false);
        pair(m, PAIR(fn_sub_4243D0_004243d0), Args{}, rng(), "event config");
        for (u32 k = 0; k < 6; ++k) CHECK(m.at(kEventCfg + k)[0] == static_cast<u8>(six[k]));
        CHECK(m.at(kEventCfgDirty)[0] == 0);
        const s8 flag = static_cast<s8>(rr(rng, -1, 2));
        m.at(kEventCfg + 8)[0] = static_cast<u8>(flag);
        const Pair2 p = pair(m, PAIR(fn_sub_424480_00424480), Args{}, rng(), "event wait");
        CHECK(p.hand.v0 == (flag == 1 ? 1u : 0u));
    }

    // the constant returns
    seed_world(m, rng);
    pair(m, PAIR(fn_sub_3111C0_003111c0), Args{}, rng(), "return 1");
    CHECK(ret_value(m) == 1);
    CHECK(ret_tag(m) == scr::kTagInt);
    pair(m, PAIR(fn_sub_30FDC0_0030fdc0), Args{}, rng(), "return 0.0f");
    CHECK(ret_value(m) == 0);
    CHECK(ret_tag(m) == scr::kTagFloat);

    // the social context words
    for (s32 i = 0; i < 3; ++i) {
        seed_world(m, rng);
        store32(m, kSocialCtxPtr, kSocialCtx);
        set_args(m, rng, {i}, false);
        pair(m, PAIR(fn_sub_35FF80_0035ff80), Args{}, rng(), "social word");
        CHECK(ret_value(m) == load32(m, kSocialCtx + 16 + 4 * static_cast<u32>(i)));
    }
}

#endif  // P3FES_GAME_HAVE_GENERATED
