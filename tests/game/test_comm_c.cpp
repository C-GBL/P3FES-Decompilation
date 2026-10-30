// Phase 5 pair tests for slice comm_c (game/src/script/comm_c.cpp): 59 COMM handlers against their recompiled bodies,
// on real AI action objects and a field world.
//
// The machine (as test_comm_ai.cpp). Two guest machines run in lockstep: the hand-written handler on one, the __recomp
// body on the other, from identical memory (the world is built on the first and copied to the second). Each pair
// compares, through pair_harness.h's hardware-observing run (run_hw / expect_same_hw): $v0, every GPR in 128 bits,
// HI/LO, the whole register file and the cycle count at EVERY check point of the call tree (the AI table rows the
// handlers reach through jalr, the candidate filters, datCalcRand ... -- what the kernel would save on a preemption),
// the dead stack (the frames and the lists the handlers keep there), the gp-relative globals, the g_data / flag
// records, the datScript context and RNG state, the battle world, the field world, 14 KiB of deeper stack and the AI
// tables; the FPRs at the end; and every 32 pairs (and at the end of each case) the whole 32 MiB of main RAM.
//
// The battle world (21_battle.md sections 1.3, 2, 3): the eight battle/*.TBL files loaded the way btlTableLoad lays
// them out (real SKILL / UNIT / PERSONA / AICALC data from the extracted tree; random sections when absent), random
// party / persona / equipment records, flag words and RNG state; gBtl with a list of 2..8 btlAction objects (+8 uid,
// +26 active bits, +48 btlUnit, +1188/+1192 links; +0x14C the head the walks start from, +0x148 the current action),
// their btlUnits (+162 side, +164 id, +2604 DatUnit) and DatUnits (party ids 1..10 on side 0, enemy ids < 336 on side
// 1, random HP / level / statuses incl. dead), the battle stage record gBtl +0xBBC (u16 +8: the stage ids 0x1A5 /
// 0x1B0 / 0x1B4 the stage commands test, or another), the script task (arguments in its slots, the acting action as
// its user word). The field world: the four field unit records gFldUnitsPc 0x8717A0 (+0x48 / +0x54 / +0x16C -> an
// object whose +0x3C work bytes the party helpers read and write), sField (+0x18 the field object or none), the record
// list of sub_3C8EC0 ($gp - 0x4674), the social link table sub_173040 reads ($gp - 0x471C, 0x95B718). Pointer-like
// fields are kept aligned and inside main RAM; a world that still makes recompiled code fault (an unaligned or bus
// error on the EE) must fault identically in both bodies, and is counted and reported.
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/comm_ai.h"
#include "p3fes/game/comm_c.h"
#include "p3fes/game/script_vm.h"

#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name, addr8, index, argc) \
    void fn_##name##_##addr8(EEContext&);         \
    void fn_##name##_##addr8##__recomp(EEContext&);
P3FES_COMM_C_HANDLERS(P3FES_DECL_PAIR)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::btl;
using namespace p3fes::game::comm_ai;

struct Handler {
    const char* name;
    u32 addr;
    u32 index;
    u32 argc;
    Fn hand;
    Fn recomp;
};

#define P3FES_H(name, addr8, index, argc) \
    Handler{#name, 0x##addr8, index, argc, &recomp_gen::fn_##name##_##addr8, &recomp_gen::fn_##name##_##addr8##__recomp},
const Handler kHandlers[] = {P3FES_COMM_C_HANDLERS(P3FES_H)};
#undef P3FES_H

const Handler& by_addr(u32 addr) {
    for (const Handler& h : kHandlers)
        if (h.addr == addr) return h;
    return kHandlers[0];
}

// What a handler answers with.
enum class Kind { Condition, Select, UnitId, Count, Field };
Kind kind_of(u32 addr) {
    switch (addr) {
    case 0x2CA7B0: case 0x2CE2B0: case 0x2CBAF0: case 0x2CC190: case 0x2CBBA0: case 0x2CBFD0: case 0x2CC0A0:
    case 0x2CC240: case 0x2CE170: case 0x2CE210:
        return Kind::Condition;
    case 0x2CD570: case 0x2CD690: case 0x2CD740: case 0x2CD620: case 0x2CE380: case 0x2D05C0: case 0x2D0760:
    case 0x2D0AF0: case 0x2D09D0:
        return Kind::Select;
    case 0x2CDB70: case 0x2CDBE0: case 0x2CDC50: case 0x2CDCC0: case 0x2CDD30: case 0x2CDDA0: case 0x2CF340:
    case 0x2CF7E0: case 0x2CF890: case 0x2CF940:
        return Kind::Count;
    case 0x1C3EB0: case 0x1C3F10: case 0x1C3DF0: case 0x1C3D60: case 0x1C5600: case 0x1C57B0: case 0x360250:
    case 0x1C5EB0: case 0x3A28A0: case 0x3A2C10:
        return Kind::Field;
    default:
        return Kind::UnitId;
    }
}
u32 expected_v0(u32 addr) {
    switch (addr) {
    case 0x2CEF10: case 0x2CF070: case 0x2CF1D0: case 0x2CF340: return 0xFFFFFFFFu;
    default: return 1u;
    }
}

// --- guest layout ------------------------------------------------------------------------------------------------
constexpr u32 kTask = kArena;                    // ScrTask (252 bytes)
constexpr u32 kWorld = kArena;                   // the battle world: [kArena, kArena + 64 KiB)
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kGBtl = kArena + 0x1000;           // gBtl (0xD20 bytes)
constexpr u32 kGBtlSize = 0xD20u;
constexpr u32 kUnits = kArena + 0x1E00;          // 8 DatUnits, 64-byte stride
constexpr u32 kActions = kArena + 0x2000;        // 8 btlAction objects
constexpr u32 kActStride = 1200;
constexpr u32 kBtlUnits = kArena + 0x4800;       // 8 btlUnit objects
constexpr u32 kBuStride = 0xA40;
constexpr u32 kStage = kArena + 0xC000;          // the battle stage record (gBtl +0xBBC)
constexpr u32 kMaxActions = 8;
constexpr u32 kGBtlPtr = 0x7CE3ECu;              // gBtl ($gp - 18692)
constexpr u32 kGBtlHead = 332;                   // gBtl +332 (0x14C): the action list
constexpr u32 kActUid = 8, kActFlags24 = 24, kActFlags26 = 26, kActPrev = 1188, kActNext = 1192;
constexpr u32 kFieldWorld = kArena + 0x10000u;   // the field world's objects: [kArena + 64 KiB, + 64 KiB)
constexpr u32 kFieldWorldSize = 0x10000u;
constexpr u32 kMsgSlotTable = 0x959EECu;        // the message manager's 52-byte slots, +0 the handle
constexpr u32 kMsgSlots = 8;
constexpr u32 kTaskMessageId = 0xCC;             // ScrTask +0xCC: the message handle id scrGetMessageID returns
constexpr u32 kSocialTable = 0x95B718u;          // u32*: 64 x 32-byte social link records (sub_3BEB10)
constexpr u32 kTables = 0x01900000u;             // the .TBL sections (about 1.2 MB)
constexpr u32 kWeapons = 0x01880000u;            // 1,000 x 40-byte weapon records (pointer 0x7CDFE4)
constexpr u32 kAccessories = 0x018A0000u;        // 1,000 x 36-byte accessory records (pointer 0x7CDFD4)
constexpr u32 kHeroInventory = 0x018C0000u;      // the hero's 20-byte item records (pointer 0x836794)
constexpr u32 kDataLo = 0x007C0000u, kDataHi = 0x009B0000u;
constexpr u32 kTableRecords = 0x00692D40u;       // off_692D40: the loader records of btlTableLoad
constexpr u32 kFlagWords = 0x83A21Cu;
constexpr u32 kRandState = 0x957BF0u;
constexpr u32 kDeepStack = kSp - 0x4000u;        // [kSp - 16 KiB, kSp - 2 KiB): below the harness's dead stack

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
// Words that are mostly zero or small, now and then wide; always multiples of 4 below 32 MiB (a field the code takes
// for a pointer never makes an unaligned or unmapped load).
void fill_words(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= len; i += 4) {
        const u32 r = rng() % 8;
        store32(m, va + i, (r < 4 ? 0u : r < 6 ? rng() % 32 : r < 7 ? rng() & 0xFFFFu : rng() & 0x01FFFFFFu) & ~3u);
    }
}
s32 rr(std::mt19937& rng, s32 lo, s32 hi) { return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1)); }
bool one_in(std::mt19937& rng, u32 n) { return rng() % n == 0; }
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}

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

struct Turn {
    u32 me = 0;
    std::array<s32, 4> args{};
    u32 argc = 0;
};

// --- the two machines ----------------------------------------------------------------------------------------------
struct Twin {
    std::unique_ptr<Machine> a = std::make_unique<Machine>();  // the hand-written handler
    std::unique_ptr<Machine> b = std::make_unique<Machine>();  // the recompiled body
    std::mt19937 rng;
    bool real = false;
    u32 n_actions = 0;
    std::array<u32, kMaxActions> actions{};
    std::array<std::array<u32, 2>, 4> records{};  // sub_3C8EC0's records: {+0x2C, +0x20}
    u32 n_records = 0;
    u64 pairs = 0;
    u64 full_checks = 0;
    u64 faults = 0;
    std::vector<u64> per_handler_pairs = std::vector<u64>(std::size(kHandlers));
    std::vector<u64> per_handler_faults = std::vector<u64>(std::size(kHandlers));
    std::vector<std::string> first_fault = std::vector<std::string>(std::size(kHandlers));
    HwCheck hw;

    explicit Twin(u32 seed) : rng(seed) {
        hw.compare_checkpoint_regs = true;
        hw.gpr_mask = kAllGprs;
        hw.compare_hilo = true;
        hw.compare_dead_stack = true;
        hw.ranges = {{0x7CD000u, 0x6000u},  {0x833000u, 0x8000u},   {0x957000u, 0x5000u}, {0x869000u, 0x1000u},
                     {0x86E000u, 0x5000u},  {kWorld, kWorldSize},   {kFieldWorld, kFieldWorldSize},
                     {kDeepStack, 0x3800u}, {comm_c::kCondTable, 0x500u}};
    }

    Machine& A() { return *a; }

    const char* load() {
        if (const char* err = A().load_elf(elf_path())) return err;
        install_tables();
        randomize_items();
        randomize_party();
        randomize_flags();
        store32(A(), scr::kCurrentTask, kTask);
        new_battle();
        new_field();
        mirror_all();
        return nullptr;
    }
    void mirror_all() {
        std::memcpy(b->mem.main_ram(), a->mem.main_ram(), EEMemory::kMainRamSize);
        std::memcpy(b->mem.scratchpad(), a->mem.scratchpad(), 0x4000);
    }
    void mirror(u32 va, u32 len) { std::memcpy(b->at(va), a->at(va), len); }
    void mirror_world() {
        mirror(kWorld, kWorldSize);
        mirror(kFieldWorld, kFieldWorldSize);
        mirror(kDataLo, kDataHi - kDataLo);
        mirror(kWeapons, kHeroInventory + 0x4000 - kWeapons);
    }
    void full_compare(const char* what) {
        INFO(what);
        const u8* x = a->mem.main_ram();
        const u8* y = b->mem.main_ram();
        std::size_t first = 0;
        const bool same = std::memcmp(x, y, EEMemory::kMainRamSize) == 0;
        if (!same)
            while (first < EEMemory::kMainRamSize && x[first] == y[first]) ++first;
        INFO("first differing main-RAM byte " << hex64(first));
        CHECK(same);
        ++full_checks;
    }

    void install_tables() {
        Machine& m = A();
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
    }

    void randomize_items() {
        Machine& m = A();
        fill_random(m, kWeapons, 1000 * 40, rng);
        for (u32 i = 0; i < 1000; ++i) store16(m, kWeapons + 40 * i + 30, static_cast<u16>(rr(rng, -1, 18)));
        fill_random(m, kAccessories, 1000 * 36, rng);
        for (u32 i = 0; i < 1000; ++i) store32(m, kAccessories + 36 * i + 28, rng() % 640);
        store32(m, 0x7CDFE4u, kWeapons);
        store32(m, 0x7CDFD4u, kAccessories);
    }

    void randomize_party() {
        Machine& m = A();
        fill_random(m, 0x833F00u, 0x836E00u - 0x833F00u, rng);
        auto item = [&](u32 va, u32 slot) {
            const u32 id = slot == 0 ? rng() % 1000 : (slot == 3 ? 3000 + rng() % 1000 : rng() % 4000);
            store16(m, va, static_cast<u16>(rng() % 10 ? id : rng()));
            m.at(va + 9)[0] = static_cast<u8>(rng() % 200);
        };
        for (u32 pc = 2; pc <= 10; ++pc) {
            const u32 base = 0x834010u + 868u * (pc - 2);
            for (u32 s = 0; s < 4; ++s) store16(m, base + 0x54 + 2 * s, static_cast<u16>(rng() % 12 ? s : static_cast<u32>(rr(rng, -1, 9))));
            for (u32 i = 0; i < 10; ++i) item(base + 0x5C + 20 * i, i < 4 ? i : rng() % 4);
            const u32 persona = base + 0xDC;
            store16(m, persona + 2, static_cast<u16>(rng() % 256));
            m.at(persona + 4)[0] = static_cast<u8>(rr(rng, 1, 99));
            for (u32 s = 0; s < 8; ++s) store16(m, persona + 12 + 2 * s, static_cast<u16>(rng() % 3 ? rng() % 640 : 0));
            store16(m, base + 0x4C, static_cast<u16>(rng() % 7));
        }
        for (u32 s = 0; s < 4; ++s) store16(m, 0x83678Cu + 2 * s, static_cast<u16>(s));
        for (u32 pc = 2; pc <= 13; ++pc) store16(m, 0x834010u + 868u * (pc - 2) + 6, static_cast<u16>(pc));
        store16(m, 0x836226u, 1);
        store16(m, 0x83626Cu, static_cast<u16>(rng() % 7));
        store32(m, 0x836794u, kHeroInventory);
        store32(m, 0x836798u, kHeroInventory + 0x800);
        fill_random(m, kHeroInventory, 0x4000, rng);
        for (u32 i = 0; i < 16; ++i) item(kHeroInventory + 20 * i, i % 4);
    }

    void randomize_flags() {
        Machine& m = A();
        const u32 density = rng() % 3;
        for (u32 i = 0; i < 176; ++i) {
            u32 w = rng();
            if (density == 0) w &= rng();
            if (density == 2) w |= rng();
            store32(m, kFlagWords + 4 * i, w);
        }
        store32(m, 0x7CDFA4u, rng() % 4 == 0 ? 1u : 0u);
        fill_random(m, kRandState, 16, rng);
    }

    void dat_unit(u32 va, bool enemy) {
        Machine& m = A();
        fill_random(m, va, 64, rng);
        u16 flags = load16(m, va);
        flags = enemy ? static_cast<u16>(flags | kUnitFlagEnemy) : static_cast<u16>(flags & ~kUnitFlagEnemy);
        if (rng() % 2) flags = static_cast<u16>(flags & ~0x570u);
        store16(m, va, flags);
        const u16 id = static_cast<u16>(enemy ? (rng() % 20 ? rng() % kEnemyCount : rng() % 400) : (rng() % 20 ? rr(rng, 1, 10) : rng() % 14));
        store16(m, va + 2, id);
        store16(m, va + 4, id);
        m.at(va + 6)[0] = static_cast<u8>(one_in(rng, 3) ? rr(rng, 1, 4) : rr(rng, 1, 99));  // ties of level now and then
        store16(m, va + 8, static_cast<u16>(rng() % 8 == 0 ? 0 : rng() % 10 ? rng() % 1000 : rng()));
        store16(m, va + 10, static_cast<u16>(rng() % 500));
        constexpr u32 kStatuses[] = {0, 0, 0, 0, 0, 8, 0x100000, 512, 2, 4, 64, 32, 0x10, 0x100, 0x80000, 0x80000};
        store32(m, va + 0xC, kStatuses[rng() % std::size(kStatuses)] | (rng() % 6 == 0 ? (rng() & 0xFFF00000u) : 0u));
        store32(m, va + 0x14, rng() % 3 ? 0u : rng());
        if (rng() % 3 != 0) std::memset(m.at(va + 0x1C), 0, 9);
    }

    u32 targeted_skill() {
        const u32 table = load32(A(), kSkillTablePtr);
        for (int tries = 0; tries < 64; ++tries) {
            const u32 id = rng() % kSkillCount;
            if (A().at(table + 44 * id + 9)[0] & 3u) return id;
        }
        return 0;
    }

    void new_battle() {
        Machine& m = A();
        std::memset(m.at(kWorld + 0x100), 0, kWorldSize - 0x100);
        fill_words(m, kGBtl, kGBtlSize, rng);
        store32(m, kGBtlPtr, kGBtl);
        // Mostly battles with several units on each side, so the target lists hold more than one candidate.
        const bool big = !one_in(rng, 4);
        n_actions = static_cast<u32>(big ? rr(rng, 5, static_cast<s32>(kMaxActions)) : rr(rng, 2, static_cast<s32>(kMaxActions)));
        const u32 party = static_cast<u32>(big ? rr(rng, 2, static_cast<s32>(n_actions) - 2) : rr(rng, 1, static_cast<s32>(n_actions) - 1));
        for (u32 i = 0; i < n_actions; ++i) {
            const u32 act = kActions + kActStride * i;
            const u32 bu = kBtlUnits + kBuStride * i;
            const u32 du = kUnits + 64 * i;
            actions[i] = act;
            fill_words(m, act, kActStride, rng);
            fill_words(m, bu, kBuStride, rng);
            const bool enemy = i >= party;
            dat_unit(du, enemy);
            store32(m, act + kActUid, one_in(rng, 8) ? rng() & 0x0FFFFFFFu : 100u + 7u * i);
            store16(m, act + kActFlags24, static_cast<u16>(rng() % 4 ? 0 : rng()));
            store16(m, act + kActFlags26, static_cast<u16>(rng() % 6 ? (9u | (rng() & 0xF6u)) : rng()));
            if (big && !one_in(rng, 3)) store32(m, du + 0xC, 0);  // more living units
            store32(m, act + kActUnit, bu);
            m.at(bu + kUnitSide)[0] = static_cast<u8>(one_in(rng, 30) ? rng() % 4 : (enemy ? 1 : 0));
            store16(m, bu + kUnitId, load16(m, du + 2));
            store32(m, bu + kUnitDat, du);
            if (i == 0 || i + 1 == n_actions) {
                // A battle always has a living, active unit on each side (the default selector divides by its
                // candidate count).
                store16(m, act + kActFlags24, 0);
                store16(m, act + kActFlags26, 9);
                store32(m, du + 0xC, 0);
                store16(m, du + 8, static_cast<u16>(rr(rng, 1, 999)));
                m.at(bu + kUnitSide)[0] = static_cast<u8>(enemy ? 1 : 0);
            }
            store16(m, act + kActSkill, static_cast<u16>(one_in(rng, 10) ? rng() % 500 : targeted_skill()));
            store32(m, act + kActPrev, i == 0 ? 0u : kActions + kActStride * (i - 1));
            store32(m, act + kActNext, i + 1 < n_actions ? kActions + kActStride * (i + 1) : 0u);
        }
        for (u32 side = 0; side < 2; ++side) {
            u32 prev = 0;
            for (u32 i = n_actions; i-- > 0;) {
                const u32 bu = kBtlUnits + kBuStride * i;
                if ((i >= party ? 1u : 0u) != side) continue;
                store32(m, bu + 2608, prev);
                prev = bu;
            }
            store32(m, kGBtl + 340 + 8 * side, prev);
        }
        for (u32 s = 0; s < 12; ++s) {
            const u32 e = kGBtl + 2656 + 4 * s;
            m.at(e)[0] = static_cast<u8>(one_in(rng, 2) ? 0xFF : rng() % 2);
            m.at(e + 1)[0] = static_cast<u8>(rng());
            store16(m, e + 2, static_cast<u16>(one_in(rng, 2) ? load16(m, kUnits + 64 * (rng() % n_actions) + 4) : rng() % 400));
        }
        store32(m, kGBtl + kGBtlHead, actions[0]);
        store32(m, kGBtl + kGBtlAppointed, one_in(rng, 3) ? 0u : actions[rng() % n_actions]);
        // The stage record: the ids the stage commands test, or another.
        fill_words(m, kStage, 0x100, rng);
        constexpr u16 kStages[] = {0x1A5, 0x1B0, 0x1B4, 0x1A4, 0x10};
        store16(m, kStage + 8, kStages[rng() % std::size(kStages)]);
        store32(m, kGBtl + 0xBBC, kStage);
    }

    // The field world: gFldUnitsPc[0..3], sField's object, sub_3C8EC0's record list, the social link table.
    void new_field() {
        Machine& m = A();
        std::memset(m.at(kFieldWorld), 0, kFieldWorldSize);
        u32 next = kFieldWorld;
        auto alloc = [&](u32 size) {
            const u32 va = next;
            next += (size + 15) & ~15u;
            return va;
        };
        auto object = [&]() {  // an object whose +0x3C is a 0x1300-byte work area
            const u32 obj = alloc(0x80);
            fill_words(m, obj, 0x80, rng);
            const u32 work = alloc(0x1300);
            fill_random(m, work, 0x1300, rng);
            m.at(work + 1)[0] = static_cast<u8>(rng() % 8);       // the unit state sub_43C7F0 reads (5 / 6 matter)
            m.at(work + 0x1218)[0] = static_cast<u8>(rng() % 8);  // the sub-state sub_43A230 reads (3 / 6 matter)
            m.at(work + 0x1222)[0] = static_cast<u8>(rng() % 3 ? 0 : 1);
            store32(m, obj + 0x3C, work);
            return obj;
        };
        for (u32 k = 0; k < 4; ++k) {
            const u32 rec = comm_c::kFldUnitsPc + 448 * k;
            fill_words(m, rec, 448, rng);
            store32(m, rec + 0x48, rng() % 4 ? 1u : 0u);
            store32(m, rec + 0x54, rng() % 4 ? 1u : 0u);
            store32(m, rec + 0x16C, rng() % 5 ? object() : 0u);
        }
        store32(m, comm_c::kField + 0x14, rng() % 3);
        store32(m, comm_c::kField + 0x18, rng() % 3 ? object() : 0u);
        // sub_3C8EC0: *(*(*($gp - 0x4674)) + 4) is the first node; node +0x10 next, +0x14 the record (+0x2C, +0x20).
        const u32 p = alloc(16), q = alloc(16);
        store32(m, kGp - 0x4674, p);
        store32(m, p, q);
        n_records = static_cast<u32>(rng() % 5);
        u32 prev_link = q + 4;
        for (u32 i = 0; i < n_records; ++i) {
            const u32 node = alloc(0x20), rec = alloc(0x40);
            fill_words(m, rec, 0x40, rng);
            records[i] = {rng() % 8, rng() % 8};
            store32(m, rec + 0x2C, records[i][0]);
            store32(m, rec + 0x20, records[i][1]);
            store32(m, node + 0x14, rec);
            store32(m, prev_link, node);
            prev_link = node + 0x10;
        }
        store32(m, prev_link, 0);
        // The social link table (64 x 32 bytes) and the index sub_360250 hands to sub_173040.
        const u32 social = alloc(64 * 32);
        fill_random(m, social, 64 * 32, rng);
        for (u32 i = 0; i < 64; ++i)
            for (u32 j = 0; j < 4; ++j) store16(m, social + 32 * i + 4 + 2 * j, static_cast<u16>(rng() % 4 ? 0xFA0 + rng() % 0x100 : rng() % 0xFA0));
        store32(m, kSocialTable, social);
        store32(m, kGp - 0x471C, rng() % 64);
        for (u32 i = 0; i < 64; ++i) m.at(0x8366F4u + i)[0] = static_cast<u8>(rng() % 3);
        // The message manager slots 0..7 (0x959EEC + 52 * id -> a 488-byte handle): the choice mask +80, the
        // {s16 key, s16 value} pairs at +0x68 with their s16 count at +0x66 (sub_3A4A70).
        for (u32 id = 0; id < kMsgSlots; ++id) {
            const u32 handle = alloc(488);
            fill_random(m, handle, 488, rng);
            store16(m, handle + 0x66, static_cast<u16>(rr(rng, -1, 16)));
            for (u32 k = 0; k < 15; ++k) store16(m, handle + 0x68 + 4 * k, static_cast<u16>(rr(rng, -1, 17)));
            store32(m, kMsgSlotTable + 52 * id, handle);
        }
    }

    void set_turn(const Turn& t) {
        Machine& m = A();
        fill_random(m, kTask, 252, rng);
        const u32 junk = rng() % 4;
        const u32 sp = t.argc + junk;
        store32(m, kTask + scr::kSp, sp);
        for (u32 i = 0; i < t.argc; ++i) {
            const u32 slot = sp - 1 - i;
            const bool as_float = one_in(rng, 12);
            m.at(kTask + scr::kTags + slot)[0] = static_cast<u8>(as_float ? scr::kTagFloat : scr::kTagInt);
            store32(m, kTask + scr::kValues + slot * 4, as_float ? fbits(static_cast<float>(t.args[i])) : static_cast<u32>(t.args[i]));
        }
        store32(m, kTask + scr::kUserData, t.me);
        store32(m, kTask + kTaskMessageId, static_cast<u32>(rr(rng, -2, static_cast<s32>(kMsgSlots) - 1)));  // scrGetMessageID
        mirror(kTask, 256);
        if (!one_in(rng, 4)) {
            store16(m, t.me + kActSkill, static_cast<u16>(targeted_skill()));
            mirror(t.me + kActSkill, 2);
        }
    }

    Turn turn(const Handler& h) {
        Turn t;
        t.argc = h.argc;
        t.me = actions[rng() % n_actions];
        const Machine& m = A();
        auto unit_of = [&](u32 act) { return load32(m, act + kActUnit); };
        auto some_id = [&]() -> s32 {
            if (one_in(rng, 6)) return rr(rng, -2, 400);
            return load16(m, unit_of(actions[rng() % n_actions]) + kUnitId);
        };
        auto some_uid = [&]() -> s32 {
            if (one_in(rng, 8)) return static_cast<s32>(rng());
            return static_cast<s32>(load32(m, actions[rng() % n_actions] + kActUid));
        };
        auto param = [&]() -> s32 {
            switch (rng() % 6) {
            case 0: return rr(rng, 0, 100);
            case 1: return rr(rng, 0, 20);
            case 2: return static_cast<s32>(rng() & 0xFFFFFFu);
            case 3: return static_cast<s32>(rng());
            case 4: return static_cast<s32>(1u << (rng() % 24));
            default: return rr(rng, -5, 5);
            }
        };
        auto side = [&]() -> s32 { return one_in(rng, 6) ? rr(rng, -1, 4) : rr(rng, 0, 1); };
        for (u32 i = 0; i < 4; ++i) t.args[i] = param();
        // The candidate filters' predicates take the param as an element (sub_2C1ED0: the affinity's weak bit; sub_2C30F0
        // / sub_2C3120: sub_2C2ED0) or an effect mask (sub_2C3400): small values most of the time, so lists are not empty.
        if (kind_of(h.addr) == Kind::UnitId && !one_in(rng, 3)) t.args[0] = rr(rng, 0, 10);
        switch (h.addr) {
        case 0x2CA7B0: t.args = {some_id(), param() | static_cast<s32>(one_in(rng, 2) ? comm_c::kStatusDead : 0u), 0, 0}; break;
        case 0x2CE2B0: case 0x2CE170: case 0x2CE210: case 0x2CF7E0: case 0x2CF890: case 0x2CF940: case 0x2CFFC0:
        case 0x2CE380:
            t.args[0] = some_uid();
            if (h.addr == 0x2CF940 || h.addr == 0x2CF7E0 || h.addr == 0x2CF890) t.args[2] = rr(rng, -2, 3);
            break;
        case 0x2CBBA0: t.args = {side(), some_id(), param(), 0}; break;
        case 0x2CBFD0: t.args = {side(), some_id(), 0, 0}; break;
        case 0x2CC0A0: case 0x2CC240: t.args = {some_id(), param(), 0, 0}; break;
        case 0x2D05C0: {
            constexpr s32 kSkills[] = {0x68, 0x132, 0x133, 0x10, 0x131};
            t.args = {kSkills[rng() % std::size(kSkills)], rr(rng, -2, 400), rr(rng, -2, 400), rr(rng, -2, 400)};
            break;
        }
        case 0x2D0760: t.args[0] = rr(rng, -2, 20); break;
        case 0x2D0AF0: t.args[0] = rr(rng, -40000, 40000); break;
        case 0x1C3EB0: case 0x1C3DF0: t.args[0] = one_in(rng, 3) ? 0 : one_in(rng, 2) ? 1 : param(); break;
        case 0x1C3F10: t.args[0] = rr(rng, -300, 300); break;
        case 0x1C3D60: {
            if (n_records != 0 && one_in(rng, 2)) {
                const auto& r = records[rng() % n_records];
                t.args = {static_cast<s32>(r[0]), static_cast<s32>(r[1]), 0, 0};
            } else {
                t.args = {rr(rng, -1, 8), rr(rng, -1, 8), 0, 0};
            }
            break;
        }
        case 0x1C5600: t.args[0] = one_in(rng, 8) ? param() : rr(rng, -1, 2); break;
        case 0x1C57B0: {
            const s32 pc = one_in(rng, 8) ? rr(rng, 0, 15) : rr(rng, 2, 10);
            s32 skill = rr(rng, 0, 640);
            if (pc >= 2 && pc <= 10 && one_in(rng, 2))
                skill = load16(m, 0x834010u + 868u * static_cast<u32>(pc - 2) + 0xDC + 12 + 2 * (rng() % 8));
            t.args = {pc, skill, 0, 0};
            break;
        }
        default: break;
        }
        return t;
    }

    HwOutcome pair(std::size_t hi, const Turn& t, const char* what) {
        const Handler& h = kHandlers[hi];
        char tag[220];
        std::snprintf(tag, sizeof tag, "%s [%u] %s me=0x%x a0=%d a1=%d a2=%d a3=%d", what, h.index, h.name, t.me, t.args[0], t.args[1], t.args[2],
                      t.args[3]);
        const std::string context = tag;
        INFO(context);
        set_turn(t);
        const u32 seed = rng();
        HwOutcome x, y;
        std::string fault_hand, fault_recomp;
        try {
            x = run_hw(*a, h.hand, Args{}, seed, hw);
        } catch (const rt_test::FatalEvent& e) {
            fault_hand = e.what;
        }
        try {
            y = run_hw(*b, h.recomp, Args{}, seed, hw);
        } catch (const rt_test::FatalEvent& e) {
            fault_recomp = e.what;
        }
        if (!fault_hand.empty() || !fault_recomp.empty()) {
            CHECK(fault_hand == fault_recomp);
            ++faults;
            if (per_handler_faults[hi]++ == 0) first_fault[hi] = fault_recomp;
            mirror_all();
            return x;
        }
        const std::array<u32, 32> fa = fprs(*a);
        expect_same_hw(x, y, hw, tag);
        CHECK(fa == fprs(*b));
        CHECK(x.base.v0 == sx(h.addr == 0x1C3D60 ? static_cast<u32>(x.base.v0) : expected_v0(h.addr)));
        ++per_handler_pairs[hi];
        if (++pairs % 32 == 0) full_compare(tag);
        return x;
    }
    static std::array<u32, 32> fprs(const Machine& m) {
        std::array<u32, 32> f{};
        for (int i = 0; i < 32; ++i) f[i] = m.ctx.fpr[i];
        return f;
    }

    u32 script_result() const { return load32(*a, kTask + scr::kValues + scr::kReturnSlot * 4); }
    void set_row(u32 va, u32 fn) {
        store32(*a, va, fn);
        store32(*b, va, fn);
    }
};

#define LOAD_TWIN_OR_SKIP(t)                                                                                  \
    if (const char* err = (t).load()) {                                                                       \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

std::size_t index_of(u32 addr) {
    for (std::size_t i = 0; i < std::size(kHandlers); ++i)
        if (kHandlers[i].addr == addr) return i;
    return 0;
}

}  // namespace

TEST_CASE("game(comm_c): the COMM table rows are what comm_c.h says") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF: " << std::string(err));
        return;
    }
    CHECK(std::size(kHandlers) == 59);
    for (const Handler& h : kHandlers) {
        INFO(h.name << " [" << h.index << "]");
        CHECK(load32(m, 0x7B92B0u + 8 * h.index) == h.addr);
        CHECK(load32(m, 0x7B92B0u + 8 * h.index + 4) == h.argc);
        // No other entry of the table points at the handler.
        int rows = 0;
        for (u32 i = 0; i < 502; ++i) rows += load32(m, 0x7B92B0u + 8 * i) == h.addr ? 1 : 0;
        CHECK(rows == 1);
    }
    // The table rows the handlers name.
    CHECK(m.str(load32(m, comm_c::kTargetTable + 4)) == "AI");
    CHECK(m.str(load32(m, comm_c::kSelMyAi + 4)) == "MYAI");
    CHECK(m.str(load32(m, comm_c::kCondTable + 12 * 0x0B + 4)) == "MYBAD");
    CHECK(load32(m, comm_c::kCondRow67) - 0x2C1000u < 0x3000u);
    CHECK(load32(m, comm_c::kSelRow34) - 0x2C3000u < 0x2000u);
}

TEST_CASE("game(comm_c): every handler equals its recompiled body on random battles and fields") {
    Twin t{0xC0C0A1u};
    LOAD_TWIN_OR_SKIP(t);
    MESSAGE("battle tables: " << std::string(t.real ? "real battle/*.TBL" : "random sections"));
    u64 cond_true = 0, cond_false = 0, found = 0, none = 0, multi = 0;
    const int rounds = 128;
    u64 n = 0;
    for (int round = 0; round < rounds; ++round) {
        if (round % 4 == 0) {
            t.randomize_flags();
            if (round % 16 == 0) t.randomize_party();
            t.new_field();
            t.mirror_world();
        }
        for (std::size_t hi = 0; hi < std::size(kHandlers); ++hi) {
            const Handler& h = kHandlers[hi];
            if (n++ % 24 == 0) {
                t.new_battle();
                t.mirror_world();
            }
            const u64 faults_before = t.faults;
            const Turn turn = t.turn(h);
            t.pair(hi, turn, "random world");
            if (t.faults != faults_before) continue;
            switch (kind_of(h.addr)) {
            case Kind::Condition: (t.script_result() != 0 ? cond_true : cond_false) += 1; break;
            case Kind::UnitId:
                (t.script_result() != 0xFFFFFFFFu ? found : none) += 1;
                // A list of several candidates (the walks and the random picks ran), for the sub_2C3430 handlers.
                if (t.script_result() != 0xFFFFFFFFu && load16(t.A(), turn.me + 0x6A) > 1) ++multi;                break;
            default: break;
            }
        }
    }
    t.full_compare("end of the random worlds");
    std::string faulting;
    for (std::size_t hi = 0; hi < std::size(kHandlers); ++hi) {
        INFO(kHandlers[hi].name << ": " << t.per_handler_pairs[hi] << " pairs, " << t.per_handler_faults[hi] << " faulting worlds");
        CHECK(t.per_handler_pairs[hi] >= 32);
        if (t.per_handler_faults[hi] != 0)
            faulting += std::string(" ") + kHandlers[hi].name + " " + std::to_string(t.per_handler_faults[hi]) + " [" + t.first_fault[hi] + "]";
    }
    MESSAGE("pairs: " << t.pairs << ", conditions true " << cond_true << " / false " << cond_false << ", units found " << found << " (from "
                      << multi << " multi-candidate lists) / none " << none << ", faulting worlds " << t.faults << " (" << faulting
                      << " ), full-RAM compares " << t.full_checks);
    CHECK(cond_true > 50);
    CHECK(cond_false > 50);
    CHECK(found > 400);
    CHECK(multi > 60);
    CHECK(none > 20);
}

TEST_CASE("game(comm_c): the query words, the fallback and the frames, through stub table rows (documented rules)") {
    Twin t{0xC0C0A2u};
    LOAD_TWIN_OR_SKIP(t);
    constexpr u32 kStubRet1 = 0x4A2BA0u, kStubRet0 = 0x4A35B0u, kStubRetA1 = 0x4B3710u;  // jr ra; li 1 / move zero / move a1
    std::vector<u32> cond(72), target(37);
    for (u32 k = 0; k < 72; ++k) cond[k] = load32(t.A(), comm_c::kCondTable + 12 * k);
    for (u32 k = 0; k < 37; ++k) target[k] = load32(t.A(), comm_c::kTargetTable + 8 * k);
    // Every condition row returns its param: the script sees `(arg & 0xFFFFFF) != 0` for the handlers whose subject is
    // the user (sub_2CBAF0 / sub_2CC190).
    for (u32 k = 1; k < 72; ++k) t.set_row(comm_c::kCondTable + 12 * k, kStubRetA1);
    int checked = 0;
    for (u32 addr : {0x2CBAF0u, 0x2CC190u}) {
        const std::size_t hi = index_of(addr);
        for (s32 arg : {0, 1, 0x1000000, 0x1000001, -1, 0x7F000000, 0xFFFFFF, 100}) {
            Turn turn = t.turn(kHandlers[hi]);
            turn.args[0] = arg;
            t.pair(hi, turn, "condition param");
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot)[0] == scr::kTagInt) {
                CHECK(t.script_result() == ((static_cast<u32>(arg) & 0xFFFFFFu) != 0 ? 1u : 0u));
                ++checked;
            }
        }
    }
    CHECK(checked > 8);
    // Rows returning 1 / 0: the condition handlers answer exactly that when their subject exists.
    for (u32 stub : {kStubRet1, kStubRet0}) {
        for (u32 k = 1; k < 72; ++k) t.set_row(comm_c::kCondTable + 12 * k, stub);
        for (u32 addr : {0x2CBAF0u, 0x2CC190u, 0x2CE2B0u}) {
            const std::size_t hi = index_of(addr);
            t.pair(hi, t.turn(kHandlers[hi]), "fixed condition rows");
            CHECK(t.script_result() == (stub == kStubRet1 ? 1u : 0u));
        }
    }
    // Selectors returning 0: the fallback row 0 runs (it returns 0 too); returning 1: it does not. Both on the
    // stubs, every selecting handler.
    for (u32 stub : {kStubRet0, kStubRet1, kStubRetA1}) {
        for (u32 k = 0; k < 37; ++k) t.set_row(comm_c::kTargetTable + 8 * k, stub);
        for (std::size_t hi = 0; hi < std::size(kHandlers); ++hi)
            if (kind_of(kHandlers[hi].addr) == Kind::Select)
                for (int it = 0; it < 8; ++it) t.pair(hi, t.turn(kHandlers[hi]), "stub selectors");
    }
    for (u32 k = 0; k < 72; ++k) t.set_row(comm_c::kCondTable + 12 * k, cond[k]);
    for (u32 k = 0; k < 37; ++k) t.set_row(comm_c::kTargetTable + 8 * k, target[k]);
    // The jalr link and frame: sub_2CD620 (frame 32) calls selector row 34 through the jalr at 0x2CD648; its own spill
    // of the caller's $ra sits at kSp - 32 + 16.
    {
        const std::size_t hi = index_of(0x2CD620);
        const HwOutcome x = t.pair(hi, t.turn(kHandlers[hi]), "frame");
        u64 own_ra;
        std::memcpy(&own_ra, x.base.dead_stack.data() + (kDeadStack - 16), 8);
        CHECK(own_ra == 0x100008u);
    }
    // sub_1C3D60: 0 (run again) exactly while a record with (arg0, arg1) is in the list.
    {
        const std::size_t hi = index_of(0x1C3D60);
        for (int it = 0; it < 64; ++it) {
            if (it % 8 == 0) {
                t.new_field();
                t.mirror_world();
            }
            const Turn turn = t.turn(kHandlers[hi]);
            const HwOutcome x = t.pair(hi, turn, "record wait");
            bool listed = false;
            for (u32 i = 0; i < t.n_records; ++i)
                listed = listed || (static_cast<s32>(t.records[i][0]) == turn.args[0] && static_cast<s32>(t.records[i][1]) == turn.args[1]);
            const u32 slot0 = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot0)[0] == scr::kTagInt && t.A().at(kTask + scr::kTags + slot0 - 1)[0] == scr::kTagInt)
                CHECK(x.base.v0 == (listed ? 0u : 1u));
        }
    }
    // sub_2D05C0: the skill it stores and the command kind 9 for the skills without a stage function.
    {
        const std::size_t hi = index_of(0x2D05C0);
        for (int it = 0; it < 64; ++it) {
            const Turn turn = t.turn(kHandlers[hi]);
            const u64 faults_before = t.faults;
            t.pair(hi, turn, "stage skill");
            if (t.faults != faults_before) continue;
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot)[0] != scr::kTagInt) continue;
            const s32 s = turn.args[0];
            CHECK(load16(t.A(), turn.me + 0x6E) == static_cast<u16>(s));
            if (s != 0x68 && s != 0x132 && s != 0x133) CHECK(load16(t.A(), turn.me + kActCommand) == 9u);  // the others call a stage function after writing 8
        }
    }
    // sub_3A28A0: the choice mask of the script's message handle is arg0; no handle (id < 0) -> nothing.
    {
        const std::size_t hi = index_of(0x3A28A0);
        int masks = 0;
        for (int it = 0; it < 64; ++it) {
            const Turn turn = t.turn(kHandlers[hi]);
            t.pair(hi, turn, "choice mask");
            const s32 id = static_cast<s32>(load32(t.A(), kTask + kTaskMessageId));
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (id >= 0 && t.A().at(kTask + scr::kTags + slot)[0] == scr::kTagInt) {
                CHECK(load32(t.A(), load32(t.A(), kMsgSlotTable + 52 * static_cast<u32>(id)) + 80) == static_cast<u32>(turn.args[0]));
                ++masks;
            }
        }
        CHECK(masks > 20);
    }
    t.full_compare("end of the documented rules");
    MESSAGE("rule pairs: " << t.pairs << ", faulting worlds " << t.faults << ", condition params checked " << checked);
}

#endif  // P3FES_GAME_HAVE_GENERATED
