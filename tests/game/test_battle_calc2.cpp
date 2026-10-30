// Phase 5 pair tests for slice battle_calc2 (game/src/battle/battle_calc2.cpp): 97 functions of the targeting /
// efficacy / support and boss-rule bands against their recompiled bodies, on random battle worlds.
//
// The machine (as test_comm_c.cpp). Two guest machines run in lockstep: the hand-written function on one, the __recomp
// body on the other, from identical memory (the world is built on the first and copied to the second before every
// pair). Each pair compares, through pair_harness.h's hardware-observing run (run_hw / expect_same_hw): $v0, every GPR
// in 128 bits, HI/LO, the whole register file (GPRs, HI/LO, SA, FPRs, FCR31) and the cycle count at EVERY check point
// of the call tree (what the kernel would save on a preemption), the dead stack (the frames), the live stack, the bus
// log, the scratchpad, the battle world and the gp-relative globals; and every 64 pairs (and at the end) the whole 32
// MiB of main RAM.
//
// The battle world (21_battle.md sections 1-3, battle_calc2.h): gBtl with random flag words, support state, support
// slots and boss words; the battle setup block (u16 +8 = the encounter id, drawn from the boss ids 417 / 421 / 424 /
// 429..436 / 456 and random ids; sometimes no block); 8 btlActions (1,200 bytes: +24 / +26 flags, +48 the btlUnit,
// the btlTarget at +56 whose entries are other actions with the u16 count at +106, the result count byte +200 and the
// 28-byte results from +224, +204 / +212, the 24 status counters at +1122, the list link +1192) linked in a random
// order from gBtl +332, gBtl's current action +328; 8 btlUnits (+26, +152, +156, +160, side +162 in {0, 1, rarely 2},
// the unit id +164 from the ids the boss rules test and random ids, the model record +2548, the DatUnit +2604 (rarely
// none), the list link +2612 from gBtl +344); 8 DatUnits (flags, id, level, HP, the status word); 8 model records
// (+1022, +1053); the .TBL sections the functions index (SKILL.TBL sections 0 and 1, EFFECT.TBL section 0, MODEL.TBL
// section 3: the real files from the extracted tree when present, random sections otherwise) behind their $gp pointers;
// the scenario word sub_17D800 reads. Arguments are pointers of the kind each function takes, ids, masks and flags
// drawn from the interesting values, with random upper register halves for the non-pointer ones.
#include "pair_harness.h"

#include "p3fes/game/battle_calc2.h"

#include <algorithm>

#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name, addr8)      \
    void fn_##name##_##addr8(EEContext&); \
    void fn_##name##_##addr8##__recomp(EEContext&);
P3FES_BATTLE_CALC2_FUNCS(P3FES_DECL_PAIR)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

struct Func {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};
#define P3FES_F(name, addr8) Func{#name, 0x##addr8, &recomp_gen::fn_##name##_##addr8, &recomp_gen::fn_##name##_##addr8##__recomp},
const Func kFuncs[] = {P3FES_BATTLE_CALC2_FUNCS(P3FES_F)};
#undef P3FES_F

// --- guest layout ------------------------------------------------------------------------------------------------
constexpr u32 kWorld = kArena;                    // [kArena, kArena + kWorldSize)
constexpr u32 kWorldSize = 0x22000u;
constexpr u32 kGBtl = kWorld;                     // gBtl (0x1000 bytes)
constexpr u32 kSetup = kWorld + 0x1000;           // the battle setup block
constexpr u32 kActions = kWorld + 0x2000;         // 8 btlActions
constexpr u32 kActStride = 1200;
constexpr u32 kUnits = kWorld + 0x5000;           // 8 btlUnits
constexpr u32 kUnitStride = 0xA40;
constexpr u32 kDatUnits = kWorld + 0xB000;        // 8 DatUnits
constexpr u32 kModels = kWorld + 0xC000;          // 8 model records
constexpr u32 kModelStride = 0x420;
constexpr u32 kNodes = kWorld + 0xE800;           // 3 list nodes of sub_2D3FE0
constexpr u32 kNodeStride = 0xA00;
constexpr u32 kSkillElem = kWorld + 0x11000;      // SKILL.TBL section 0: {s8 element, u8}[624]
constexpr u32 kSkillRec = kWorld + 0x11800;       // SKILL.TBL section 1: SkillRecord[464]
constexpr u32 kEffect = kWorld + 0x17000;         // EFFECT.TBL section 0: 464 x 28
constexpr u32 kModelTbl = kWorld + 0x1B000;       // MODEL.TBL section 3: 256 x 88
constexpr u32 kMisc = kWorld + 0x21000;           // pointer pairs, small argument objects
constexpr u32 kN = 8;
constexpr u32 kScenario = 0x7CDFA4u;              // sub_17D800: 0 = The Journey, 1 = The Answer
constexpr u32 kGpLo = 0x7CD000u, kGpLen = 0x6000u;  // the gp-relative globals compared every pair

u32 action(u32 k) { return kActions + kActStride * k; }
u32 unit(u32 k) { return kUnits + kUnitStride * k; }
u32 datunit(u32 k) { return kDatUnits + 64 * k; }
u32 model(u32 k) { return kModels + kModelStride * k; }
u32 node(u32 k) { return kNodes + kNodeStride * k; }

void st8(Machine& m, u32 va, u32 v) { m.at(va)[0] = static_cast<u8>(v); }
void st16(Machine& m, u32 va, u32 v) { const u16 x = static_cast<u16>(v); std::memcpy(m.at(va), &x, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 ld32(const Machine& m, u32 va) { u32 v; std::memcpy(&v, m.mem.main_ram() + va, 4); return v; }
u16 ld16(const Machine& m, u32 va) { u16 v; std::memcpy(&v, m.mem.main_ram() + va, 2); return v; }
u8 ld8(const Machine& m, u32 va) { return m.mem.main_ram()[va]; }

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

// The ids the boss rules and the support pickers compare with (encounters / unit ids / skills).
constexpr u32 kEncounters[] = {417, 421, 424, 429, 430, 431, 432, 433, 434, 435, 436, 456, 416, 437};
constexpr u32 kUnitIds[] = {1, 9, 2, 233, 234, 235, 236, 237, 238, 239, 240, 241, 263, 264, 266, 267, 268, 269, 271, 272, 274, 294, 293, 295, 296};
constexpr u32 kSkills[] = {327, 328, 329, 330, 331, 326, 332, 0, 1, 463, 464, 465, 0x7FFF, 0x8000, 0xFFFF};

struct Twin {
    std::unique_ptr<Machine> a = std::make_unique<Machine>();  // the hand-written function
    std::unique_ptr<Machine> b = std::make_unique<Machine>();  // the recompiled body
    std::mt19937 rng;
    bool real = false;
    HwCheck hw;
    u64 pairs = 0;
    u64 full_checks = 0;
    u64 faults = 0;
    std::string fault_log;
    std::vector<u32> hp_skills;  // SkillRecord kind == 1 (the branch sub_2D63B0 / datCalcIsHpSkill test)

    explicit Twin(u32 seed) : rng(seed) {
        hw.compare_checkpoint_regs = true;
        hw.gpr_mask = kAllGprs;
        hw.compare_hilo = true;
        hw.compare_dead_stack = true;
        hw.ranges = {{kGpLo, kGpLen}, {kWorld, kWorldSize}};
    }
    Machine& A() { return *a; }

    u32 r(u32 n) { return static_cast<u32>(rng() % n); }
    bool chance(u32 pct) { return r(100) < pct; }
    template <typename T, std::size_t N> u32 pick(const T (&v)[N]) { return static_cast<u32>(v[r(static_cast<u32>(N))]); }

    const char* load() {
        if (const char* err = A().load_elf(elf_path())) return err;
        install_tables();
        new_world();
        std::memcpy(b->mem.main_ram(), a->mem.main_ram(), EEMemory::kMainRamSize);
        std::memcpy(b->mem.scratchpad(), a->mem.scratchpad(), 0x4000);
        return nullptr;
    }

    void install_tables() {
        Machine& m = A();
        const auto skill = read_tbl("SKILL.TBL");
        const auto effect = read_tbl("EFFECT.TBL");
        const auto model_tbl = read_tbl("MODEL.TBL");
        real = skill.size() >= 2 && skill[0].size() == 0x4E0 && skill[1].size() == 0x4FC0 && !effect.empty() &&
               effect[0].size() == 0x32C0 && model_tbl.size() >= 4 && model_tbl[3].size() == 0x5800;
        if (real) {
            std::memcpy(m.at(kSkillElem), skill[0].data(), 0x4E0);
            std::memcpy(m.at(kSkillRec), skill[1].data(), 0x4FC0);
            std::memcpy(m.at(kEffect), effect[0].data(), 0x32C0);
            std::memcpy(m.at(kModelTbl), model_tbl[3].data(), 0x5800);
        } else {
            for (u32 i = 0; i < 624; ++i) st8(m, kSkillElem + 2 * i, r(5) == 0 ? 0xFF : r(8));
            for (u32 i = 0; i < 0x4FC0; ++i) st8(m, kSkillRec + i, rng());
            for (u32 i = 0; i < 464; ++i) st8(m, kSkillRec + 44 * i + 2, r(3));
            for (u32 i = 0; i < 0x32C0; ++i) st8(m, kEffect + i, chance(30) ? 0 : rng());
            for (u32 i = 0; i < 0x5800; ++i) st8(m, kModelTbl + i, rng());
        }
        st32(m, game::bc2::kGBtlPtr, kGBtl);
        st32(m, 0x7CE3F4u, kSkillElem);
        st32(m, 0x7CE3F8u, kSkillRec);
        st32(m, 0x7CE400u, kEffect);
        st32(m, 0x7CE42Cu, kModelTbl);
        for (u32 i = 0; i < 464; ++i)
            if (ld8(m, kSkillRec + 44 * i + 2) == 1) hp_skills.push_back(i);
    }

    // A fresh random world on machine A (the tables stay).
    void new_world() {
        Machine& m = A();
        for (u32 va = kWorld; va < kSkillElem; va += 4) st32(m, va, chance(50) ? 0 : static_cast<u32>(rng()));
        for (u32 va = kMisc; va < kWorld + kWorldSize; va += 4) st32(m, va, static_cast<u32>(rng()));
        st32(m, kScenario, r(4) == 0 ? 2 : r(2));
        // gBtl
        st32(m, kGBtl + 12, static_cast<u32>(rng()) & ~(chance(50) ? 0x200000u : 0u));
        st32(m, kGBtl + 16, static_cast<u32>(rng()) & ~(chance(50) ? 0x10u : 0u));
        st32(m, kGBtl + 3004, chance(5) ? 0 : kSetup);
        st16(m, kSetup + 8, chance(80) ? pick(kEncounters) : r(1024));
        st16(m, kGBtl + 2564, rng());
        st32(m, kGBtl + 2568, rng());
        st16(m, kGBtl + 2582, rng());
        st32(m, kGBtl + 2592, r(8));
        st32(m, kGBtl + 2600, r(8));
        st8(m, kGBtl + 2706, chance(40) ? 0xFF : r(5));
        for (u32 k = 0; k < 16; ++k) {  // the support slots: {s16, s16, s8 timer}
            st16(m, kGBtl + 2708 + 6 * k, rng());
            st16(m, kGBtl + 2710 + 6 * k, rng());
            st8(m, kGBtl + 2712 + 6 * k, chance(40) ? 0x80 + r(128) : r(5));
        }
        static constexpr u32 kSmall[] = {0, 0, 1, 2, 40, 5};
        for (u32 off : {2824u, 2828u, 2832u, 2856u, 2884u, 2888u, 2892u, 2896u, 2900u, 2904u})
            st32(m, kGBtl + off, chance(60) ? pick(kSmall) : static_cast<u32>(rng()));
        st16(m, kGBtl + 2948, r(4));
        // objects
        for (u32 k = 0; k < kN; ++k) {
            const u32 act = action(k), u = unit(k), d = datunit(k), mo = model(k);
            st16(m, act + 24, rng());
            st16(m, act + 26, rng());
            st32(m, act + 48, unit(chance(85) ? k : r(kN)));
            const u32 nt = r(4) == 0 ? r(9) : r(4);
            for (u32 i = 0; i < 8; ++i) st32(m, act + 56 + 4 * i, action(r(kN)));
            if (chance(50) && nt > 0) st32(m, act + 56 + 4 * r(nt), act);  // itself among its targets
            st16(m, act + 106, nt);
            st16(m, act + 108, rng());
            st16(m, act + 110, rng());
            st8(m, act + 200, chance(3) ? 255 : r(6));
            st16(m, act + 204, chance(70) ? rng() & ~0x500u : rng());
            st32(m, act + 212, chance(75) ? 0 : static_cast<u32>(rng()));
            for (u32 j = 0; j < 12; ++j) {
                const u32 res = act + 224 + 28 * j;
                st32(m, res, chance(40) ? 0 : (chance(50) ? static_cast<u32>(-static_cast<s32>(r(500))) : r(500)));
                st32(m, res + 8, chance(70) ? 0 : static_cast<u32>(rng()));
                st32(m, res + 12, chance(70) ? 0 : static_cast<u32>(rng()));
                st16(m, res + 26, chance(70) ? rng() & ~4u : rng());
            }
            for (u32 j = 0; j < 24; ++j) st8(m, act + 1122 + j, chance(20) ? 255 - r(2) : r(10));
            st16(m, u + 26, rng());
            st32(m, u + 152, rng());
            st32(m, u + 156, rng());
            st16(m, u + 160, rng());
            st8(m, u + 162, chance(5) ? 2 : r(2));
            st16(m, u + 164, chance(75) ? pick(kUnitIds) : r(336));
            st32(m, u + 2548, mo);
            st32(m, u + 2604, chance(5) ? 0 : d);
            st16(m, d + 0, rng());
            st16(m, d + 2, chance(50) ? pick(kUnitIds) : r(400));
            st8(m, d + 6, chance(10) ? 0 : 1 + r(99));
            st16(m, d + 8, r(999));
            st32(m, d + 12, chance(40) ? 0 : static_cast<u32>(rng()) & (chance(50) ? 0xFFFFFu : 0xFFFFFFFFu));
            st16(m, mo + 1022, rng());
            static constexpr u32 kFade[] = {0, 20, 32, 33, 200, 222, 223, 224, 255};
            st8(m, mo + 1053, chance(70) ? pick(kFade) : rng());
        }
        // the lists: a random subset of the actions from gBtl +332 (next +1192), of the units from gBtl +344 (next +2612)
        link(kGBtl + 332, 1192, [](u32 k) { return action(k); });
        link(kGBtl + 344, 2612, [](u32 k) { return unit(k); });
        st32(m, kGBtl + 328, chance(60) ? action(r(kN)) : (chance(50) ? 0 : static_cast<u32>(rng())));
        // sub_2D3FE0's nodes
        for (u32 k = 0; k < 3; ++k) {
            st32(m, node(k) + 156, rng());
            st32(m, node(k) + 2500, chance(30) ? 0 : node(r(3)));
            st32(m, node(k) + 2504, chance(30) ? 0 : node(r(3)));
        }
        // argument objects: pointer pairs (sub_2D7970...), {ptr, flags} (sub_2D7F10), {unit} (sub_2DD8B0)
        st32(m, kMisc + 0, action(r(kN)));
        st32(m, kMisc + 4, action(r(kN)));
        st32(m, kMisc + 16, model(r(kN)));
        st8(m, kMisc + 20, rng());
        st32(m, kMisc + 32, unit(r(kN)));
    }

    template <typename F> void link(u32 head, u32 next_off, F obj) {
        Machine& m = A();
        std::array<u32, kN> order{};
        for (u32 i = 0; i < kN; ++i) order[i] = i;
        std::shuffle(order.begin(), order.end(), rng);
        const u32 n = r(kN + 1);
        u32 prev = head;
        for (u32 i = 0; i < n; ++i) {
            st32(m, prev, obj(order[i]));
            prev = obj(order[i]) + next_off;
        }
        st32(m, prev, 0);
        for (u32 i = n; i < kN; ++i) st32(m, obj(order[i]) + next_off, chance(50) ? 0 : obj(r(kN)));
    }

    void mirror_world() {
        std::memcpy(b->at(kWorld), a->at(kWorld), kWorldSize);
        std::memcpy(b->at(kGpLo), a->at(kGpLo), kGpLen);
    }

    void full_compare(const char* what) {
        INFO(std::string(what));
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

    // A value argument: an interesting value with random upper register bits sometimes (the bodies take the low
    // halves through andi / dsll32+dsra32 or compare whole registers, and both must agree).
    u64 value(u32 v) {
        if (chance(25)) return (static_cast<u64>(rng()) << 32) | v;
        return sx(v);
    }

    Args args_for(u32 addr) {
        Args x{sx(action(r(kN))), sx(unit(r(kN))), value(r(3)), value(rng())};
        switch (addr) {
        case 0x2D15E0: case 0x2D1600:
            x[0] = sx(action(r(kN)) + 56);  // the btlTarget of an action
            break;
        case 0x2D3FE0:
            x[0] = sx(node(r(3)));
            break;
        case 0x2D4800: case 0x2D5E00:
            x[0] = sx(kMisc + 48);
            break;
        case 0x2D4CC0:
            x[0] = value(chance(80) ? r(464) : pick(kSkills));
            break;
        case 0x2D4CF0: case 0x2D4E10:
            x[0] = value(r(8));
            x[1] = value(chance(30) ? 0 : (chance(50) ? 0x80000u : static_cast<u32>(rng())));
            break;
        case 0x2D5B50:
            x[0] = chance(80) ? sx(pick(kSkills)) : value(pick(kSkills));
            break;
        case 0x2D5BF0: case 0x2D5C70: case 0x2EC4B0: case 0x2F23D0: case 0x2F2410: case 0x2F9690: case 0x2FC410:
        case 0x2FDCB0:
            x[0] = sx(unit(r(kN)));
            break;
        case 0x2D6370:
            x[0] = value(chance(80) ? r(464) : pick(kSkills));
            break;
        case 0x2D63B0:
            x[0] = sx(unit(r(kN)));
            x[1] = value(chance(60) && !hp_skills.empty() ? hp_skills[r(static_cast<u32>(hp_skills.size()))] : r(464));
            x[2] = chance(30) ? 0 : value(rng());
            break;
        case 0x2D7970: case 0x2D7DF0: case 0x2D7EF0: case 0x2D7F90: case 0x2D8020: case 0x2D8070: case 0x2D80F0:
        case 0x2D8310:
            x[0] = sx(kMisc + 0);
            break;
        case 0x2D7F10:
            x[0] = sx(kMisc + 16);
            break;
        case 0x2D8680:
            x[1] = chance(70) ? sx(r(3)) : value(r(3));
            break;
        case 0x2D8EF0: case 0x2D8F40: case 0x2D9AA0:
            {
            const u32 cur = ld32(A(), kGBtl + 328);  // gBtl's current action, when it is one
            x[0] = chance(70) && cur >= kActions && cur < kActions + kN * kActStride ? sx(cur) : sx(action(r(kN)));
        }
            x[1] = value(r(8));
            break;
        case 0x2DB420: case 0x2DB450:
            x[0] = value(r(20));
            break;
        case 0x2DB9F0:
            x[0] = value(rng());
            x[1] = chance(70) ? sx(r(8)) : value(r(8));
            break;
        case 0x2DC550:
            x[1] = chance(20) ? 0 : value(static_cast<u32>(rng()));
            break;
        case 0x2DD8B0: case 0x2DD930:
            x[0] = sx(kMisc + 32);
            break;
        case 0x2F2510:
            x[0] = sx(kMisc + 64);
            st32(A(), kMisc + 96, chance(50) ? ld32(A(), kGBtl + 2892) + r(3) - 1 : static_cast<u32>(rng()));
            break;
        case 0x2F8840:
            x[0] = value(r(40));
            break;
        case 0x2F8EB0:
            x[0] = sx(unit(r(kN)));
            x[1] = value(chance(85) ? r(464) : pick(kSkills));
            break;
        case 0x2F9560:
            x[0] = sx(unit(r(kN)));
            x[1] = sx(kMisc + 128);
            st16(A(), kMisc + 130, chance(50) ? (chance(50) ? 23 : 25) : r(30));
            break;
        case 0x2FDCF0: case 0x2FDD40:
            x[0] = sx(unit(r(kN)));
            x[1] = chance(20) ? x[0] : sx(unit(r(kN)));
            break;
        case 0x2FDED0:
            x[0] = value(chance(80) ? 293 + r(4) : r(400));
            break;
        default:
            break;
        }
        return x;
    }

    // One pair: the world is mirrored, both bodies run, everything is compared. Returns the hand run (for the
    // documented-rule checks) or nothing when the world made both fault.
    bool pair(const Func& f, const Args& args, HwOutcome* out = nullptr) {
        mirror_world();
        const u32 seed = static_cast<u32>(rng());
        HwOutcome h, c;
        bool fault_h = false, fault_c = false;
        std::string what_h, what_c;
        try {
            h = run_hw(*a, f.hand, args, seed, hw);
        } catch (const rt_test::FatalEvent& e) {
            fault_h = true;
            what_h = e.what.substr(0, e.what.find("; host"));
        }
        try {
            c = run_hw(*b, f.recomp, args, seed, hw);
        } catch (const rt_test::FatalEvent& e) {
            fault_c = true;
            what_c = e.what.substr(0, e.what.find("; host"));
        }
        ++pairs;
        INFO(std::string(f.name));
        CHECK(fault_h == fault_c);
        CHECK(what_h == what_c);
        if (fault_h || fault_c) {
            ++faults;
            if (fault_log.size() < 2000) fault_log += std::string(" ") + f.name + " (" + what_h + ")";
            std::memcpy(b->mem.main_ram(), a->mem.main_ram(), EEMemory::kMainRamSize);
            return false;
        }
        expect_same_hw(h, c, hw, f.name);
        if (pairs % 64 == 0) full_compare(f.name);
        if (out) *out = std::move(h);
        return true;
    }
};

#define P3FES_BC2_LOAD(t)                                                                            \
    Twin t(0xBC2u);                                                                                  \
    if (const char* err = t.load()) {                                                                \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)); \
        return;                                                                                      \
    }

const Func& by_addr(u32 addr) {
    for (const Func& f : kFuncs)
        if (f.addr == addr) return f;
    FAIL("no function at " << hex64(addr));
    return kFuncs[0];
}

}  // namespace

TEST_CASE("game(battle_calc2): every function equals its recompiled body on random battle worlds") {
    P3FES_BC2_LOAD(t)
    MESSAGE("battle tables: " << std::string(t.real ? "real battle/*.TBL" : "random sections"));
    constexpr int kPairsPerFunc = 240;
    u64 paths = 0;
    std::string single_path;
    for (const Func& f : kFuncs) {
        std::set<std::pair<u64, u64>> seen;  // (cycles, $v0): the distinct paths and results a function took
        for (int i = 0; i < kPairsPerFunc; ++i) {
            if (i % 3 == 0) t.new_world();
            const Args args = t.args_for(f.addr);
            HwOutcome h;
            if (t.pair(f, args, &h)) seen.emplace(h.base.cycles, h.base.v0);
        }
        paths += seen.size();
        if (seen.size() == 1) single_path += std::string(" ") + f.name;
    }
    t.full_compare("end");
    MESSAGE("pairs: " << t.pairs << " (" << std::size(kFuncs) << " functions), distinct (cycles, $v0) outcomes " << paths
                      << ", full-RAM compares " << t.full_checks << ", faulting worlds " << t.faults
                      << "; single-outcome functions:" << single_path);
    INFO("faults:" << t.fault_log);
    CHECK(t.faults == 0);
}

TEST_CASE("game(battle_calc2): documented rules (21_battle.md, battle_calc2.h)") {
    P3FES_BC2_LOAD(t)
    Machine& m = t.A();
    HwOutcome h;
    auto v0 = [&](const HwOutcome& o) { return static_cast<s64>(o.base.v0); };

    // btlGetEncounterId: the encounter id of the setup block.
    for (u32 id : {417u, 436u, 1u}) {
        t.new_world();
        st32(m, kGBtl + 3004, kSetup);
        st16(m, kSetup + 8, id);
        REQUIRE(t.pair(by_addr(0x2D5550), Args{}, &h));
        CHECK(v0(h) == static_cast<s64>(id));
    }
    // btlTargetGetSideMask: the side mask of a target list.
    {
        t.new_world();
        const u32 tgt = action(0) + 56;
        st16(m, tgt + 50, 3);
        st32(m, tgt + 0, action(1));
        st32(m, tgt + 4, action(2));
        st32(m, tgt + 8, action(3));
        st32(m, action(1) + 48, unit(1));
        st32(m, action(2) + 48, unit(2));
        st32(m, action(3) + 48, unit(3));
        st8(m, unit(1) + 162, 0);
        st8(m, unit(2) + 162, 0);
        st8(m, unit(3) + 162, 2);
        REQUIRE(t.pair(by_addr(0x2D1600), Args{sx(tgt)}, &h));
        CHECK(v0(h) == 0x5);
    }
    // btlSupportTestFlag / btlSupportClearFlag: one bit of gBtl +2564.
    {
        t.new_world();
        st16(m, kGBtl + 2564, 0x0120);
        REQUIRE(t.pair(by_addr(0x2DB450), Args{5}, &h));
        CHECK(v0(h) == 1);
        REQUIRE(t.pair(by_addr(0x2DB450), Args{6}, &h));
        CHECK(v0(h) == 0);
        REQUIRE(t.pair(by_addr(0x2DB420), Args{8}, &h));
        CHECK(ld16(m, kGBtl + 2564) == 0x0020);
    }
    // sub_2E33F0: the enemy-id codes (233 / 234 keep the compare constant) and a party unit's id.
    {
        const std::pair<u32, s64> cases[] = {{240, 4}, {239, 2}, {234, 234}, {233, 233}, {294, 103}, {267, 15}, {100, -1}};
        for (const auto& [id, want] : cases) {
            t.new_world();
            st32(m, action(0) + 48, unit(0));
            st8(m, unit(0) + 162, 1);
            st16(m, unit(0) + 164, id);
            REQUIRE(t.pair(by_addr(0x2E33F0), Args{sx(action(0))}, &h));
            CHECK(v0(h) == want);
        }
        t.new_world();
        st32(m, action(0) + 48, unit(0));
        st8(m, unit(0) + 162, 0);
        st16(m, unit(0) + 164, 0xFFF0);
        REQUIRE(t.pair(by_addr(0x2E33F0), Args{sx(action(0))}, &h));
        CHECK(v0(h) == -16);
    }
    // sub_2F8EB0: encounter 430, enemy 294: skill element 0 / 1 / 2 -> 4 / 5 / 6, other -> -1.
    {
        const std::pair<u32, s64> cases[] = {{0, 4}, {1, 5}, {2, 6}, {3, -1}, {0xFF, -1}};
        for (const auto& [elem, want] : cases) {
            t.new_world();
            st16(m, kSetup + 8, 430);
            st32(m, kGBtl + 3004, kSetup);
            st8(m, unit(0) + 162, 1);
            st16(m, unit(0) + 164, 294);
            const u8 saved = ld8(m, kSkillElem + 2 * 10);
            st8(m, kSkillElem + 2 * 10, elem);
            REQUIRE(t.pair(by_addr(0x2F8EB0), Args{sx(unit(0)), 10}, &h));
            CHECK(v0(h) == want);
            st8(m, kSkillElem + 2 * 10, saved);
            st8(*t.b, kSkillElem + 2 * 10, saved);
        }
    }
    // btlSupportResetTimers then btlSupportTickTimers: the slots reset to {-1, -1, 3}, the timer to -1, and a tick resets a slot at 3.
    {
        t.new_world();
        REQUIRE(t.pair(by_addr(0x2DCBC0), Args{}, &h));
        CHECK(ld16(m, kGBtl + 2704) == 5);
        CHECK(ld8(m, kGBtl + 2706) == 0xFF);
        for (u32 k = 0; k < 16; ++k) {
            CHECK(ld16(m, kGBtl + 2708 + 6 * k) == 0xFFFF);
            CHECK(ld8(m, kGBtl + 2712 + 6 * k) == 3);
        }
        st8(m, kGBtl + 2712, 1);
        st16(m, kGBtl + 2708, 7);
        st16(m, kGBtl + 2708 + 6, 7);
        REQUIRE(t.pair(by_addr(0x2DCC40), Args{}, &h));
        CHECK(ld8(m, kGBtl + 2712) == 2);  // 1 counts on to 2
        CHECK(ld16(m, kGBtl + 2708) == 7);
        CHECK(ld8(m, kGBtl + 2712 + 6) == 0xFF);  // 3 counts on to 4 >= 3: the slot resets
        CHECK(ld16(m, kGBtl + 2708 + 6) == 0xFFFF);
    }
    // sub_2FDED0 returns the address of btlBossResetCounters for 296 / 295 / 293 in encounter 436.
    {
        t.new_world();
        st32(m, kGBtl + 3004, kSetup);
        st16(m, kSetup + 8, 436);
        REQUIRE(t.pair(by_addr(0x2FDED0), Args{295}, &h));
        CHECK(v0(h) == 0x2F6BC0);
        CHECK(ld32(m, kGBtl + 2908) == 295);
        REQUIRE(t.pair(by_addr(0x2FDED0), Args{294}, &h));
        CHECK(v0(h) == 0);
        REQUIRE(t.pair(by_addr(0x2FDED0), Args{297}, &h));
        CHECK(ld32(m, kGBtl + 2908) == 0xFFFFFFFFu);
    }
    MESSAGE("rule pairs: " << t.pairs << ", faulting worlds " << t.faults);
}

TEST_CASE("game(battle_calc2): the SKILL.TBL / EFFECT.TBL readers on every skill id (real data when present)") {
    P3FES_BC2_LOAD(t)
    Machine& m = t.A();
    HwOutcome h;
    u32 hp_skills = 0, checked = 0;
    for (u32 id = 0; id < 464; ++id) {
        // datCalcIsHpSkill: SkillRecord kind == 1; sub_2D4CC0: EFFECT.TBL byte 0, 0 -> 1.
        REQUIRE(t.pair(by_addr(0x2D6370), Args{sx(id)}, &h));
        const bool hp = ld8(m, kSkillRec + 44 * id + 2) == 1;
        CHECK(static_cast<s64>(h.base.v0) == (hp ? 1 : 0));
        hp_skills += hp ? 1u : 0u;
        REQUIRE(t.pair(by_addr(0x2D4CC0), Args{sx(id)}, &h));
        const u32 e = ld8(m, kEffect + 28 * id);
        CHECK(static_cast<s64>(h.base.v0) == (e == 0 ? 1 : static_cast<s64>(e)));
        ++checked;
    }
    MESSAGE("battle tables: " << std::string(t.real ? "real" : "random") << "; skills checked " << checked << ", HP skills (kind 1) "
                              << hp_skills << ", pairs " << t.pairs);
    if (t.real) CHECK(hp_skills > 0);
}

#endif  // P3FES_GAME_HAVE_GENERATED
