// Phase 5 pair tests for slice comm_ai (game/src/script/comm_ai.cpp): the 120 battle-AI COMM handlers against their
// recompiled bodies, on real AI action objects.
//
// The machine. Two guest machines run in lockstep: the hand-written handler on one, the __recomp body on the other,
// from identical memory (the battle world is built on the first and copied to the second). Each pair compares, through
// pair_harness.h's hardware-observing run (run_hw / expect_same_hw): $v0, every GPR in 128 bits, HI/LO, the whole
// register file and the cycle count at EVERY check point of the call tree (the AI table functions the handlers reach
// through jalr, datCalcDamage, datScriptCalc ... -- what the kernel would save on a preemption), the dead stack, the
// arena and live stack, and after the run the gp-relative globals, the party / flag records, the datScript context
// and RNG state, the battle world, 14 KiB of deeper stack and the AI tables; the FPRs at the end; and every 32 pairs
// (and at the end of each case) the whole 32 MiB of main RAM of both machines.
//
// The battle world (21_battle.md sections 1.3, 2, 3): the eight battle/*.TBL files loaded the way btlTableLoad lays
// them out (real SKILL / UNIT / PERSONA / AICALC data from the extracted tree, so AICALC section 15's per-enemy AI
// rows drive sub_2D13C0; random sections when absent), random party / persona / equipment records, flag words and RNG
// state; gBtl (`*(u32*)0x7CE3EC`) with a list of 2..8 btlAction objects (+8 uid, +26 active bits, +48 btlUnit,
// +1188/+1192 links), their btlUnits (+162 side, +164 id, +2604 DatUnit) and 60-byte DatUnits (party ids 1..10 on
// side 0, enemy ids < 336 on side 1, random HP and statuses incl. dead), the appointed action gBtl+328, the
// script task (g_scrCurrentTask, the arguments in its slots, the acting action as its user word). The AI table
// functions run for real: they are non-leaf (MYHP spills $ra in a 48-byte frame), so the handlers' frames and
// links are checked through the callees' spills (and directly, below). Pointer-like fields are kept aligned and inside
// main RAM, each side has a living active unit and the actions carry skills that target a side; a world that still
// makes the AI code fault (the default selector AI with an empty candidate list calls datCalcRand(0) and loads
// through the remainder -- a bus error on the EE, not a battle) must fault identically in both bodies, and is
// counted and reported. The rule cases replace the table rows with leaf stubs of the ELF (`jr ra; move v0, a1` /
// `li v0, 1` / `move v0, zero`) to check the query word, the param mask and the fallback.
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/comm_ai.h"
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
#define P3FES_DECL_PAIR(name, addr8, index, k)  \
    void fn_##name##_##addr8(EEContext&);       \
    void fn_##name##_##addr8##__recomp(EEContext&);
P3FES_COMM_AI_ASK(P3FES_DECL_PAIR)
P3FES_COMM_AI_ASK_FIXED(P3FES_DECL_PAIR)
P3FES_COMM_AI_TARGET_FIXED(P3FES_DECL_PAIR)
P3FES_COMM_AI_TARGET(P3FES_DECL_PAIR)
P3FES_COMM_AI_COMMAND(P3FES_DECL_PAIR)
P3FES_COMM_AI_ASK_ALLY(P3FES_DECL_PAIR)
P3FES_COMM_AI_ALLY_FIXED(P3FES_DECL_PAIR)
P3FES_DECL_PAIR(sub_2C7340, 002c7340, 113, 0)
P3FES_DECL_PAIR(sub_2C7540, 002c7540, 116, 0)
P3FES_DECL_PAIR(sub_2C75D0, 002c75d0, 165, 0)
P3FES_DECL_PAIR(sub_2D13C0, 002d13c0, 117, 0)
P3FES_DECL_PAIR(sub_2C9BA0, 002c9ba0, 170, 0)
P3FES_DECL_PAIR(sub_2C9CE0, 002c9ce0, 171, 0)
P3FES_DECL_PAIR(sub_2CD4E0, 002cd4e0, 180, 0)
P3FES_DECL_PAIR(sub_2C73E0, 002c73e0, 235, 0)
P3FES_DECL_PAIR(sub_2CB190, 002cb190, 236, 0)
P3FES_DECL_PAIR(sub_2CDF40, 002cdf40, 248, 0)
P3FES_DECL_PAIR(sub_2CE010, 002ce010, 249, 0)
P3FES_DECL_PAIR(sub_2CE090, 002ce090, 250, 0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::btl;
using namespace p3fes::game::comm_ai;

// --- the handler table -----------------------------------------------------------------------------------------
enum class Fam { Ask, AskFixed, TargetFixed, Target, Command, AskAlly, AllyFixed, Own };

struct Handler {
    const char* name;
    u32 addr;
    u32 index;
    u32 argc;
    Fam fam;
    u32 k;
    Fn hand;
    Fn recomp;
};

#define P3FES_H(name, addr8, index, k, fam, argc)                                                                \
    Handler{#name, 0x##addr8, index, argc, fam, k, &recomp_gen::fn_##name##_##addr8, &recomp_gen::fn_##name##_##addr8##__recomp},
#define P3FES_H_ASK(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::Ask, 1)
#define P3FES_H_ASK_FIXED(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::AskFixed, 0)
#define P3FES_H_TARGET_FIXED(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::TargetFixed, 0)
#define P3FES_H_TARGET(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::Target, 1)
#define P3FES_H_COMMAND(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::Command, 0)
#define P3FES_H_ASK_ALLY(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::AskAlly, 2)
#define P3FES_H_ALLY_FIXED(name, addr8, index, k) P3FES_H(name, addr8, index, k, Fam::AllyFixed, 1)
const Handler kHandlers[] = {
    P3FES_COMM_AI_ASK(P3FES_H_ASK)
    P3FES_COMM_AI_ASK_FIXED(P3FES_H_ASK_FIXED)
    P3FES_COMM_AI_TARGET_FIXED(P3FES_H_TARGET_FIXED)
    P3FES_COMM_AI_TARGET(P3FES_H_TARGET)
    P3FES_COMM_AI_COMMAND(P3FES_H_COMMAND)
    P3FES_COMM_AI_ASK_ALLY(P3FES_H_ASK_ALLY)
    P3FES_COMM_AI_ALLY_FIXED(P3FES_H_ALLY_FIXED)
    P3FES_H(sub_2C7340, 002c7340, 113, 0, Fam::Own, 1)
    P3FES_H(sub_2C7540, 002c7540, 116, 0, Fam::Own, 1)
    P3FES_H(sub_2C75D0, 002c75d0, 165, 0, Fam::Own, 2)
    P3FES_H(sub_2D13C0, 002d13c0, 117, 0, Fam::Own, 0)
    P3FES_H(sub_2C9BA0, 002c9ba0, 170, 0, Fam::Own, 2)
    P3FES_H(sub_2C9CE0, 002c9ce0, 171, 0, Fam::Own, 2)
    P3FES_H(sub_2CD4E0, 002cd4e0, 180, 0, Fam::Own, 0)
    P3FES_H(sub_2C73E0, 002c73e0, 235, 0, Fam::Own, 1)
    P3FES_H(sub_2CB190, 002cb190, 236, 0, Fam::Own, 2)
    P3FES_H(sub_2CDF40, 002cdf40, 248, 0, Fam::Own, 2)
    P3FES_H(sub_2CE010, 002ce010, 249, 0, Fam::Own, 2)
    P3FES_H(sub_2CE090, 002ce090, 250, 0, Fam::Own, 1)
};
#undef P3FES_H
#undef P3FES_H_ASK
#undef P3FES_H_ASK_FIXED
#undef P3FES_H_TARGET_FIXED
#undef P3FES_H_TARGET
#undef P3FES_H_COMMAND
#undef P3FES_H_ASK_ALLY
#undef P3FES_H_ALLY_FIXED

const Handler& by_addr(u32 addr) {
    for (const Handler& h : kHandlers)
        if (h.addr == addr) return h;
    return kHandlers[0];
}

// --- guest layout ------------------------------------------------------------------------------------------------
constexpr u32 kTask = kArena;                    // ScrTask (252 bytes)
constexpr u32 kWorld = kArena;                   // everything the battle world owns: [kArena, kArena + 64 KiB)
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kGBtl = kArena + 0x1000;           // gBtl (0xD20 bytes)
constexpr u32 kGBtlSize = 0xD20u;
constexpr u32 kUnits = kArena + 0x1E00;          // 8 DatUnits, 64-byte stride
constexpr u32 kActions = kArena + 0x2000;        // 8 btlAction objects
constexpr u32 kActStride = 1200;
constexpr u32 kBtlUnits = kArena + 0x4800;       // 8 btlUnit objects
constexpr u32 kBuStride = 0xA40;
constexpr u32 kMaxActions = 8;
constexpr u32 kGBtlPtr = 0x7CE3ECu;              // gBtl ($gp - 18692)
constexpr u32 kGBtlHead = 332;                   // gBtl +332: the action list
constexpr u32 kActUid = 8, kActFlags24 = 24, kActFlags26 = 26, kActPrev = 1188, kActNext = 1192;
constexpr u32 kTables = 0x01900000u;             // the .TBL sections (about 1.2 MB)
constexpr u32 kWeapons = 0x01880000u;            // 1,000 x 40-byte weapon records (pointer 0x7CDFE4)
constexpr u32 kAccessories = 0x018A0000u;        // 1,000 x 36-byte accessory records (pointer 0x7CDFD4)
constexpr u32 kHeroInventory = 0x018C0000u;      // the hero's 20-byte item records (pointer 0x836794)
constexpr u32 kDataLo = 0x007C0000u, kDataHi = 0x009B0000u;
constexpr u32 kTableRecords = 0x00692D40u;       // off_692D40: the loader records of btlTableLoad
constexpr u32 kFlagWords = 0x83A21Cu;
constexpr u32 kRandState = 0x957BF0u;
constexpr u32 kDeepStack = kSp - 0x4000u;        // [kSp - 16 KiB, kSp - 2 KiB): below the harness's dead stack
// Leaf stubs of the ELF for the documented-rule tables: `jr ra; li v0, 1`, `jr ra; move v0, zero`, `jr ra; move v0, a1`.
constexpr u32 kStubRet1 = 0x4A2BA0u, kStubRet0 = 0x4A35B0u, kStubRetA1 = 0x4B3710u;

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
// Words that are mostly zero or small (counters, indices, flags), now and then wide; always multiples of 4 below
// 32 MiB, so a field the AI code takes for a pointer never makes an unaligned or unmapped load (an address error /
// bus error on the EE).
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

// What one turn looks like to the handler: the acting action and the arguments.
struct Turn {
    u32 me = 0;
    std::array<s32, 2> args{};
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
    u64 pairs = 0;
    u64 full_checks = 0;
    u64 faults = 0;
    HwCheck hw;

    explicit Twin(u32 seed) : rng(seed) {
        hw.compare_checkpoint_regs = true;
        hw.gpr_mask = kAllGprs;
        hw.compare_hilo = true;
        hw.compare_dead_stack = true;
        // Per pair: the gp-relative globals (gBtl pointer, table pointers, datCalcRand's last roll, the script task
        // pointer), the party / persona / flag records, the datScript context and RNG state, the world, the deeper
        // stack and the AI tables; the whole main RAM every 32 pairs.
        hw.ranges = {{0x7CD000u, 0x6000u}, {0x833000u, 0x8000u}, {0x957000u, 0x1000u}, {kWorld, kWorldSize},
                     {kDeepStack, 0x3800u}, {kCondTable, 0x500u}};
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
        mirror_all();
        return nullptr;
    }
    // B := A, the whole RAM and the scratchpad.
    void mirror_all() {
        std::memcpy(b->mem.main_ram(), a->mem.main_ram(), EEMemory::kMainRamSize);
        std::memcpy(b->mem.scratchpad(), a->mem.scratchpad(), 0x4000);
    }
    void mirror(u32 va, u32 len) { std::memcpy(b->at(va), a->at(va), len); }
    // What new_battle / randomize_* write: the world, the data window, the item tables and the hero's inventory.
    void mirror_world() {
        mirror(kWorld, kWorldSize);
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
            for (u32 s = 0; s < 8; ++s) store16(m, persona + 12 + 2 * s, static_cast<u16>(rng() % 640));
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

    // A DatUnit for a side: party ids 1..10 on side 0, enemy ids < 336 on side 1.
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
        m.at(va + 6)[0] = static_cast<u8>(rr(rng, 1, 99));
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

    // gBtl, 2..8 actions with their btlUnits and DatUnits, the appointed action.
    void new_battle() {
        Machine& m = A();
        std::memset(m.at(kWorld + 0x100), 0, kWorldSize - 0x100);
        fill_words(m, kGBtl, kGBtlSize, rng);
        store32(m, kGBtlPtr, kGBtl);
        n_actions = static_cast<u32>(rr(rng, 2, static_cast<s32>(kMaxActions)));
        const u32 party = static_cast<u32>(rr(rng, 1, static_cast<s32>(n_actions) - 1));
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
            store32(m, act + kActUnit, bu);
            m.at(bu + kUnitSide)[0] = static_cast<u8>(one_in(rng, 30) ? rng() % 4 : (enemy ? 1 : 0));
            store16(m, bu + kUnitId, load16(m, du + 2));
            store32(m, bu + kUnitDat, du);
            if (i == 0 || i + 1 == n_actions) {
                // A battle always has a living, active unit on each side: the default selector (AI) picks among the
                // candidates with datCalcRand(count), and an empty list divides by zero and loads through the
                // remainder (a bus error on the EE), so worlds without one are not battles.
                store16(m, act + kActFlags24, 0);
                store16(m, act + kActFlags26, 9);
                store32(m, du + 0xC, 0);
                store16(m, du + 8, static_cast<u16>(rr(rng, 1, 999)));
                m.at(bu + kUnitSide)[0] = static_cast<u8>(enemy ? 1 : 0);
            }
            // The skill the action is about to use: one whose SKILL.TBL target bits (+9, bits 0/1: a side) name a side
            // most of the time, so the target lists the selectors build are not empty.
            store16(m, act + kActSkill, static_cast<u16>(one_in(rng, 10) ? rng() % 500 : targeted_skill()));
            store32(m, act + kActPrev, i == 0 ? 0u : kActions + kActStride * (i - 1));
            store32(m, act + kActNext, i + 1 < n_actions ? kActions + kActStride * (i + 1) : 0u);
        }
        // The per-side btlUnit lists (gBtl +340 + 8 * side, btlUnit +2608 = next) and the 12 {s8 side, u8, u16 id}
        // slots at gBtl +2656 (side -1 = free) that sub_2E3120 walks.
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
    }

    // The arguments in the task's slots (argument i = slot sp - 1 - i; now and then a float tag) and the acting
    // action as the task's user word.
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
        mirror(kTask, 256);
        if (!one_in(rng, 4)) {  // the skill the acting unit is about to use (the handlers before may have changed it)
            store16(m, t.me + kActSkill, static_cast<u16>(targeted_skill()));
            mirror(t.me + kActSkill, 2);
        }
    }

    // A random acting unit and arguments that fit the handler.
    Turn turn(const Handler& h) {
        Turn t;
        t.argc = h.argc;
        t.me = actions[rng() % n_actions];
        const Machine& m = A();
        auto unit_of = [&](u32 act) { return load32(m, act + kActUnit); };
        auto some_id = [&]() -> s32 {  // the id of a unit of the list, now and then any
            if (one_in(rng, 6)) return rr(rng, -2, 400);
            return load16(m, unit_of(actions[rng() % n_actions]) + kUnitId);
        };
        auto some_uid = [&]() -> s32 {
            if (one_in(rng, 8)) return static_cast<s32>(rng());
            return static_cast<s32>(load32(m, actions[rng() % n_actions] + kActUid));
        };
        auto param = [&]() -> s32 {
            switch (rng() % 6) {
            case 0: return rr(rng, 0, 100);                         // a percentage / level / count
            case 1: return rr(rng, 0, 20);
            case 2: return static_cast<s32>(rng() & 0xFFFFFFu);     // any 24-bit param
            case 3: return static_cast<s32>(rng());                 // the high byte is masked off
            case 4: return static_cast<s32>(1u << (rng() % 24));    // one status / element bit
            default: return rr(rng, -5, 5);
            }
        };
        switch (h.fam) {
        case Fam::Ask:
        case Fam::Target: t.args[0] = param(); break;
        case Fam::AskAlly: t.args = {some_id(), param()}; break;
        case Fam::AllyFixed: t.args[0] = some_id(); break;
        default: break;
        }
        switch (h.addr) {
        case 0x2C7340: t.args[0] = one_in(rng, 3) ? 0 : one_in(rng, 3) ? rr(rng, -3, -1) : rr(rng, 1, 700); break;
        case 0x2C7540:
        case 0x2C75D0: t.args = {param(), param()}; break;
        case 0x2C9BA0: t.args = {some_id(), param() | static_cast<s32>(one_in(rng, 2) ? comm_ai::kStatusDead : 0u)}; break;
        case 0x2C9CE0: t.args = {some_id(), static_cast<s32>(rng() % 3 ? (1u << (rng() % 21)) : rng())}; break;
        case 0x2C73E0: t.args[0] = one_in(rng, 4) ? rr(rng, -3, -1) : rr(rng, 0, 1200); break;
        case 0x2CB190: t.args = {one_in(rng, 5) ? rr(rng, -1, 4) : rr(rng, 0, 1), one_in(rng, 3) ? some_id() : static_cast<s32>(load16(m, unit_of(t.me) + kUnitId))}; break;
        case 0x2CDF40: t.args = {some_uid(), param()}; break;
        case 0x2CE010: t.args = {some_uid(), static_cast<s32>(rng() % 3 ? (1u << (rng() % 21)) : rng())}; break;
        case 0x2CE090: t.args[0] = some_uid(); break;
        default: break;
        }
        return t;
    }

    // Both bodies from identical machines; afterwards both machines hold their own body's result.
    HwOutcome pair(const Handler& h, const Turn& t, const char* what) {
        char tag[200];
        std::snprintf(tag, sizeof tag, "%s [%u] %s me=0x%x a0=%d a1=%d", what, h.index, h.name, t.me, t.args[0], t.args[1]);
        const std::string context = tag;
        INFO(context);
        set_turn(t);
        const u32 seed = rng();
        // A world in which the AI code reaches an unmapped or unaligned address (a bus / address error on the EE) is not
        // a valid battle: both bodies must stop with the same fault; the machines are then re-synchronised.
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
            mirror_all();
            return x;
        }
        const std::array<u32, 32> fa = fprs(*a);
        expect_same_hw(x, y, hw, tag);
        CHECK(fa == fprs(*b));
        CHECK(x.base.v0 == 1u);
        if (++pairs % 32 == 0) full_compare(tag);
        return x;
    }
    static std::array<u32, 32> fprs(const Machine& m) {
        std::array<u32, 32> f{};
        for (int i = 0; i < 32; ++i) f[i] = m.ctx.fpr[i];
        return f;
    }

    u32 script_result() const { return load32(*a, kTask + scr::kValues + scr::kReturnSlot * 4); }
    u16 action16(u32 act, u32 off) const { return load16(*a, act + off); }
    // A table row of both machines.
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

}  // namespace

TEST_CASE("game(comm_ai): the COMM table rows and the AI tables are what comm_ai.h says") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF: " << std::string(err));
        return;
    }
    CHECK(std::size(kHandlers) == 120);
    for (const Handler& h : kHandlers) {
        INFO(h.name << " [" << h.index << "]");
        CHECK(load32(m, 0x7B92B0u + 8 * h.index) == h.addr);
        CHECK(load32(m, 0x7B92B0u + 8 * h.index + 4) == h.argc);
    }
    // The table rows the header names (their own strings).
    auto cond_name = [&](u32 k) { return m.str(load32(m, kCondTable + kCondRow * k + 4)); };
    auto target_name = [&](u32 k) { return m.str(load32(m, kTargetTable + kTargetRow * k + 4)); };
    CHECK(load32(m, kCondTable) == 0);
    CHECK(cond_name(1) == "MYHP");
    CHECK(cond_name(11) == "MYBAD");
    CHECK(cond_name(19) == "ESCAPE");
    CHECK(cond_name(40) == "MYGROUP");
    CHECK(cond_name(45) == "MYHREC");
    CHECK(cond_name(66) == "ENNOMAL_DW");
    CHECK(cond_name(71) == "MYHOJO");
    CHECK(target_name(0) == "AI");
    CHECK(target_name(8) == "MYAI");
    CHECK(target_name(18) == "APPOINT");
    CHECK(target_name(28) == "NOTWEAK_ST");
    for (u32 k = 1; k <= 71; ++k) CHECK(load32(m, kCondTable + kCondRow * k) - 0x2C1000u < 0x3000u);
    for (u32 k = 0; k <= 36; ++k) CHECK(load32(m, kTargetTable + kTargetRow * k) - 0x2C3000u < 0x2000u);
    // The stubs of the rule tests.
    CHECK(load32(m, kStubRet1) == 0x03E00008u);
    CHECK(load32(m, kStubRet1 + 4) == 0x24020001u);
    CHECK(load32(m, kStubRet0 + 4) == 0x0000102Du);
    CHECK(load32(m, kStubRetA1 + 4) == 0x00A0102Du);
}

TEST_CASE("game(comm_ai): every handler equals its recompiled body on random battles") {
    Twin t{0xA1C0DEu};
    LOAD_TWIN_OR_SKIP(t);
    MESSAGE("battle tables: " << std::string(t.real ? "real battle/*.TBL" : "random sections"));
    u64 ask_true = 0, ask_false = 0;
    const int rounds = 96;
    u64 n = 0;
    for (int round = 0; round < rounds; ++round) {
        if (round % 4 == 0) {
            t.randomize_flags();
            if (round % 16 == 0) t.randomize_party();
            t.mirror_world();
        }
        for (const Handler& h : kHandlers) {
            if (n++ % 24 == 0) {
                t.new_battle();
                t.mirror_world();
            }
            t.pair(h, t.turn(h), "random battle");
            if (h.fam == Fam::Ask || h.fam == Fam::AskFixed || h.fam == Fam::AskAlly || h.fam == Fam::AllyFixed)
                (t.script_result() != 0 ? ask_true : ask_false) += 1;
        }
    }
    t.full_compare("end of the random battles");
    MESSAGE("pairs: " << t.pairs << ", conditions true " << ask_true << " / false " << ask_false << ", faulting worlds " << t.faults << ", full-RAM compares "
                      << t.full_checks);
    CHECK(ask_true > 100);
    CHECK(ask_false > 100);
}

TEST_CASE("game(comm_ai): the query word and the fallbacks, through stub table rows (documented rules)") {
    Twin t{0xA1C0DFu};
    LOAD_TWIN_OR_SKIP(t);
    // Every condition and target row returns its param ($a1): the script sees `(arg & 0xFFFFFF) != 0` (ASK), the
    // selector's 0 calls row 0, which returns 0 too.
    std::vector<u32> cond(72), target(37);
    for (u32 k = 0; k < 72; ++k) cond[k] = load32(t.A(), kCondTable + kCondRow * k);
    for (u32 k = 0; k < 37; ++k) target[k] = load32(t.A(), kTargetTable + kTargetRow * k);
    for (u32 k = 1; k < 72; ++k) t.set_row(kCondTable + kCondRow * k, kStubRetA1);
    for (u32 k = 0; k < 37; ++k) t.set_row(kTargetTable + kTargetRow * k, kStubRetA1);
    for (int it = 0; it < 6; ++it) {
        for (const Handler& h : kHandlers) {
            t.pair(h, t.turn(h), "param stubs");
            if (h.fam == Fam::Ask || h.fam == Fam::AskAlly) CHECK(t.script_result() <= 1u);  // a boolean
            if (h.fam == Fam::AskFixed) CHECK(t.script_result() == 0u);                       // param 0
        }
    }
    // ASK: exactly (arg & 0xFFFFFF) != 0 (checked when the argument went in with an int tag).
    int checked = 0;
    for (const Handler& h : kHandlers) {
        if (h.fam != Fam::Ask) continue;
        for (s32 arg : {0, 1, 0x1000000, 0x1000001, -1, 0x7F000000, 0xFFFFFF, 100}) {
            Turn turn = t.turn(h);
            turn.args[0] = arg;
            t.pair(h, turn, "ASK exact param");
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot)[0] == scr::kTagInt) {
                CHECK(t.script_result() == ((static_cast<u32>(arg) & 0xFFFFFFu) != 0 ? 1u : 0u));
                ++checked;
            }
        }
    }
    CHECK(checked > 300);
    // Fixed rows returning 1 / 0.
    for (u32 stub : {kStubRet1, kStubRet0}) {
        for (u32 k = 1; k < 72; ++k) t.set_row(kCondTable + kCondRow * k, stub);
        for (const Handler& h : kHandlers) {
            if (h.fam != Fam::AskFixed) continue;
            t.pair(h, t.turn(h), "fixed rows");
            CHECK(t.script_result() == (stub == kStubRet1 ? 1u : 0u));
        }
    }
    for (u32 k = 0; k < 72; ++k) t.set_row(kCondTable + kCondRow * k, cond[k]);
    for (u32 k = 0; k < 37; ++k) t.set_row(kTargetTable + kTargetRow * k, target[k]);
    t.full_compare("end of the stub rows");
    MESSAGE("stub-row pairs: " << t.pairs << ", faulting worlds " << t.faults << ", ASK results checked " << checked);
}

TEST_CASE("game(comm_ai): frames, links and the action fields the handlers write (documented rules)") {
    Twin t{0xA1C0E0u};
    LOAD_TWIN_OR_SKIP(t);
    // The jalr link and frame: sub_2C76B0 (frame 32) calls MYHP sub_2C12F0 (frame 48, `sd ra, 32(sp)`), so the
    // callee's saved $ra sits at kSp - 32 - 48 + 32 and holds the link of the jalr at 0x2C7728.
    {
        const Handler& h = by_addr(0x2C76B0);
        const HwOutcome x = t.pair(h, t.turn(h), "MYHP link");
        u64 ra;
        std::memcpy(&ra, x.base.dead_stack.data() + (kDeadStack - 48), 8);
        CHECK(ra == 0x2C7730u);
        u64 own_ra;  // the handler's own spill of the caller's $ra (0x100008 from the harness) at kSp - 32 + 16
        std::memcpy(&own_ra, x.base.dead_stack.data() + (kDeadStack - 16), 8);
        CHECK(own_ra == 0x100008u);
    }
    for (int it = 0; it < 200; ++it) {
        if (it % 20 == 0) {
            t.new_battle();
            t.mirror_world();
        }
        // COMMAND: the command kind lands at action +108 (attack 1, then 6 / 7 / 8).
        for (u32 addr : {0x2C7300u, 0x2C7460u, 0x2C74A0u, 0x2C7670u}) {
            const Handler& h = by_addr(addr);
            const Turn turn = t.turn(h);
            t.pair(h, turn, "command");
            const u16 kind = t.action16(turn.me, kActCommand);
            CHECK(kind == (h.k == kCmdAttack ? 1u : h.k == kCmdKind6 ? 6u : h.k == kCmdKind7 ? 7u : 8u));
        }
        // sub_2C7340: 0 -> attack (1), > 0 -> skill (2, +110 = the id), < 0 -> command 7.
        {
            const Handler& h = by_addr(0x2C7340);
            Turn turn = t.turn(h);
            t.pair(h, turn, "attack or skill");
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot)[0] == scr::kTagInt) {
                const s32 arg = turn.args[0];
                const u16 kind = t.action16(turn.me, kActCommand);
                if (arg == 0) CHECK(kind == 1u);
                if (arg < 0) CHECK(kind == 7u);
                if (arg > 0 && arg < 0x1000) {
                    CHECK(kind == 2u);
                    CHECK(t.action16(turn.me, kActSkill) == static_cast<u16>(arg));
                }
            }
        }
        // sub_2C7540 / sub_2C75D0: command 9, skill 341, the arguments at +118 / +120.
        for (u32 addr : {0x2C7540u, 0x2C75D0u}) {
            const Handler& h = by_addr(addr);
            Turn turn = t.turn(h);
            t.pair(h, turn, "skill 341");
            CHECK(t.action16(turn.me, kActCommand) == kSkill341Command);
            CHECK(t.action16(turn.me, kActSkill) == kSkill341);
        }
        // sub_2C73E0: item command 3 with the item at +112.
        {
            const Handler& h = by_addr(0x2C73E0);
            Turn turn = t.turn(h);
            turn.args[0] = rr(t.rng, 0, 999);
            t.pair(h, turn, "item");
            const u32 slot = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot)[0] == scr::kTagInt) {
                CHECK(t.action16(turn.me, kActCommand) == kItemCommand);
                CHECK(t.action16(turn.me, kActItem) == static_cast<u16>(turn.args[0]));
            }
        }
        // sub_2CB190: the side and id test, against a host model.
        {
            const Handler& h = by_addr(0x2CB190);
            Turn turn = t.turn(h);
            t.pair(h, turn, "side and id");
            const u32 slot0 = load32(t.A(), kTask + scr::kSp) - 1;
            if (t.A().at(kTask + scr::kTags + slot0)[0] == scr::kTagInt && t.A().at(kTask + scr::kTags + slot0 - 1)[0] == scr::kTagInt) {
                const u32 bu = load32(t.A(), turn.me + kActUnit);
                const u32 side = t.A().at(bu + kUnitSide)[0];
                const u32 want_side = static_cast<u32>(turn.args[0]) & 0xFFFFu;
                const bool side_ok = want_side > 1 || side == want_side;
                const bool id_ok = load16(t.A(), bu + kUnitId) == (static_cast<u32>(turn.args[1]) & 0xFFFFu);
                CHECK(t.script_result() == (side_ok && id_ok ? 1u : 0u));
            }
        }
    }
    t.full_compare("end of the documented rules");
    MESSAGE("rule pairs: " << t.pairs << ", faulting worlds " << t.faults);
}

#endif  // P3FES_GAME_HAVE_GENERATED
