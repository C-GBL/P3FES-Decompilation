// Phase 5 pair tests for the battle AICALC formulas (game/src/battle/battle_ai.cpp): datScriptCalc,
// datScriptGetValue and the 51 entries of sDatScriptFuncTbl1..3, each run against its recompiled body on
// identical guest machines. On top of pair_harness.h's outcome (result, callee-saved registers, the arena
// holding the unit records, the caller's stack, cycles, check-point count) every pair here also compares
//  * the cycle count at EVERY check point (a hash of the sequence, not only the last one), so a block cost
//    charged after a call instead of before it shows up,
//  * the datScript context words 0x957190..0x9571A7 (gDatScriptResult and the result-set bit live there),
//  * $f0 (the getter's result, a formula's cvt.w.s), the callee-saved $f20, ACC (MADD.S), FCR31 (the C bit
//    and the D/I flags of DIV.S/SQRT.S) and HI/LO (the getter's three DIVs).
// The inputs are the real battle/SKILL.TBL, UNIT.TBL and AICALC.TBL when the extracted tree is beside the
// ELF (random images otherwise), random unit records (party and enemy, NULL now and then: the K_Assert
// paths continue), random skills, modes, selectors and indices. The documented rules
// (docs/ANALYSIS/21_battle.md section 4) are checked on the host: the three formula tables and the jump
// table, the .lit4 constants, selectors 22/27/28/34 and the AICALC lookups 23/24/33, and the constant
// formulas (slots 6, 13, 14).
#include "pair_harness.h"

#include "p3fes/game/battle.h"
#include "p3fes/game/battle_ai.h"

#include <algorithm>
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

// The 51 formula-table entries: name, address (8 hex digits), table set, slot.
#define P3FES_AI_FORMULAS(X)                                                                                       \
    X(nullsub_62, 0030c510, 1, 0) X(sub_30C520, 0030c520, 1, 1) X(sub_30C930, 0030c930, 1, 2)                      \
    X(sub_30CB90, 0030cb90, 1, 3) X(sub_30CC40, 0030cc40, 1, 4) X(sub_30CDB0, 0030cdb0, 1, 5)                      \
    X(sub_30CEC0, 0030cec0, 1, 6) X(sub_30CF00, 0030cf00, 1, 7) X(sub_30D000, 0030d000, 1, 8)                      \
    X(sub_30D0E0, 0030d0e0, 1, 9) X(sub_30D1C0, 0030d1c0, 1, 10) X(sub_30D2A0, 0030d2a0, 1, 11)                    \
    X(sub_30D380, 0030d380, 1, 12) X(sub_30D460, 0030d460, 1, 13) X(sub_30D4A0, 0030d4a0, 1, 14)                   \
    X(sub_30D4E0, 0030d4e0, 1, 15) X(sub_30D610, 0030d610, 1, 16)                                                  \
    X(nullsub_63, 0030d750, 2, 0) X(sub_30D760, 0030d760, 2, 1) X(sub_30DB80, 0030db80, 2, 2)                      \
    X(sub_30DDF0, 0030ddf0, 2, 3) X(sub_30DEC0, 0030dec0, 2, 4) X(sub_30E030, 0030e030, 2, 5)                      \
    X(sub_30E140, 0030e140, 2, 6) X(sub_30E180, 0030e180, 2, 7) X(sub_30E280, 0030e280, 2, 8)                      \
    X(sub_30E360, 0030e360, 2, 9) X(sub_30E440, 0030e440, 2, 10) X(sub_30E520, 0030e520, 2, 11)                    \
    X(sub_30E600, 0030e600, 2, 12) X(sub_30E6E0, 0030e6e0, 2, 13) X(sub_30E720, 0030e720, 2, 14)                   \
    X(sub_30E760, 0030e760, 2, 15) X(sub_30E8A0, 0030e8a0, 2, 16)                                                  \
    X(nullsub_64, 0030e9f0, 3, 0) X(sub_30EA00, 0030ea00, 3, 1) X(sub_30EE10, 0030ee10, 3, 2)                      \
    X(sub_30F070, 0030f070, 3, 3) X(sub_30F120, 0030f120, 3, 4) X(sub_30F290, 0030f290, 3, 5)                      \
    X(sub_30F3A0, 0030f3a0, 3, 6) X(sub_30F3E0, 0030f3e0, 3, 7) X(sub_30F4E0, 0030f4e0, 3, 8)                      \
    X(sub_30F5C0, 0030f5c0, 3, 9) X(sub_30F6A0, 0030f6a0, 3, 10) X(sub_30F780, 0030f780, 3, 11)                    \
    X(sub_30F860, 0030f860, 3, 12) X(sub_30F940, 0030f940, 3, 13) X(sub_30F980, 0030f980, 3, 14)                   \
    X(sub_30F9C0, 0030f9c0, 3, 15) X(sub_30FAF0, 0030faf0, 3, 16)

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_datScriptCalc_0030fc40)
P3FES_DECL_PAIR(fn_datScriptGetValue_0030fdf0)
#define P3FES_DECL_FORMULA(name, addr, set, slot) P3FES_DECL_PAIR(fn_##name##_##addr)
P3FES_AI_FORMULAS(P3FES_DECL_FORMULA)
#undef P3FES_DECL_FORMULA
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::ai;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

struct Formula {
    Fn hand;
    Fn recomp;
    const char* name;
    u32 addr;
    int set;
    int slot;
};
#define P3FES_FORMULA_ROW(name, addr, set, slot) \
    Formula{&recomp_gen::fn_##name##_##addr, &recomp_gen::fn_##name##_##addr##__recomp, #name, 0x##addr##u, set, slot},
const Formula kFormulas[] = {P3FES_AI_FORMULAS(P3FES_FORMULA_ROW)};
#undef P3FES_FORMULA_ROW

// --- guest layout of the inputs --------------------------------------------------------------------------------
constexpr u32 kUnits = kArena + 0x100;  // eight 64-byte unit records in the arena (compared by the harness)
constexpr u32 kUnitStride = 64;
constexpr u32 kBtl = 0x01820000u;        // a gBtl image (random; +0xB98 / +0xB9E are read)
constexpr u32 kBtlSize = 0x1000u;
constexpr u32 kSkillBase = 0x01830000u;  // SKILL.TBL sections 0 / 1
constexpr u32 kSkillSec0 = kSkillBase;
constexpr u32 kSkillSec1 = kSkillBase + 0x1000;
constexpr u32 kUnitTbl = 0x01838000u;    // UNIT.TBL section 0 (EnemyRecord[336], 62 B)
constexpr u32 kAiCalcBase = 0x01840000u; // the whole AICALC.TBL file (524,240 bytes) or a random stand-in
constexpr u32 kContext = kAttacker;      // the datScript context words 0x957190..0x9571A7
constexpr u32 kContextSize = 0x18;
constexpr u32 kFlagWord = 0x83A21Cu + (0x1311u / 32u) * 4u;  // gGlobalWork flag word holding 0x1311 (bit 17) and 0x1319 (bit 25)

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

// battle/<name> beside the ELF (extracted/BTL/BATTLE): sections of { u32 size, bytes }, each at the next multiple
// of 16 (21_battle.md section 3.1). Returns the file bytes, empty when absent.
std::vector<u8> read_battle_file(const char* name) {
    const std::filesystem::path path = std::filesystem::path(elf_path()).parent_path().parent_path() / "BTL" / "BATTLE" / name;
    std::ifstream in(path, std::ios::binary);
    if (!in) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}
// File offsets of the section payloads.
std::vector<std::size_t> section_offsets(const std::vector<u8>& file) {
    std::vector<std::size_t> offs;
    std::size_t off = 0;
    while (off + 4 <= file.size()) {
        u32 n;
        std::memcpy(&n, file.data() + off, 4);
        if (off + 4 + n > file.size()) break;
        offs.push_back(off + 4);
        off = (off + 4 + n + 15) & ~static_cast<std::size_t>(15);
    }
    return offs;
}

struct Tables {
    bool real_skill = false;
    bool real_unit = false;
    bool real_aicalc = false;
    u32 aicalc[5] = {};  // guest addresses of AICALC sections 0..4
};

// Installs SKILL.TBL, UNIT.TBL and AICALC.TBL images and points the table words at them.
Tables install_tables(Machine& m, std::mt19937& rng) {
    Tables t;
    const std::vector<u8> skill = read_battle_file("SKILL.TBL");
    const std::vector<std::size_t> so = section_offsets(skill);
    fill_random(m, kSkillSec0, 0x1000, rng);
    fill_random(m, kSkillSec1, 0x7000, rng);  // section 1 and the bytes a bad id reads past it
    if (so.size() == 3) {
        std::memcpy(m.at(kSkillSec0), skill.data() + so[0], 0x4E0);
        std::memcpy(m.at(kSkillSec1), skill.data() + so[1], 0x4FC0);
        t.real_skill = true;
    }
    store32(m, btl::kSkillElementTablePtr, kSkillSec0);
    store32(m, btl::kSkillTablePtr, kSkillSec1);

    const std::vector<u8> unit = read_battle_file("UNIT.TBL");
    const std::vector<std::size_t> uo = section_offsets(unit);
    fill_random(m, kUnitTbl, 0x6000, rng);
    if (!uo.empty() && unit.size() >= uo[0] + 0x5160) {
        std::memcpy(m.at(kUnitTbl), unit.data() + uo[0], 0x5160);
        t.real_unit = true;
    }
    store32(m, btl::kUnitTablePtr, kUnitTbl);

    const std::vector<u8> ai = read_battle_file("AICALC.TBL");
    const std::vector<std::size_t> ao = section_offsets(ai);
    if (ao.size() >= 5 && ai.size() <= 0x80000) {
        std::memcpy(m.at(kAiCalcBase), ai.data(), ai.size());
        for (int i = 0; i < 5; ++i) t.aicalc[i] = kAiCalcBase + static_cast<u32>(ao[static_cast<std::size_t>(i)]);
        t.real_aicalc = true;
    } else {
        fill_random(m, kAiCalcBase, 0x400, rng);
        const u32 offs[5] = {0x4, 0x204, 0x244, 0x284, 0x2A4};  // the real file's layout
        for (int i = 0; i < 5; ++i) t.aicalc[i] = kAiCalcBase + offs[i];
    }
    store32(m, kAiCalc0Ptr, t.aicalc[0]);
    store32(m, kAiCalc1Ptr, t.aicalc[1]);
    store32(m, kAiCalc3Ptr, t.aicalc[3]);
    store32(m, kAiCalc4Ptr, t.aicalc[4]);
    fill_random(m, kBtl, kBtlSize, rng);
    return t;
}

// A random unit record: random bytes, the enemy flag as asked, an id the tables index (party 1..10, enemy
// 0..335), a level 1..99 at +6 most of the time (0 now and then: datCalcGetLevel's assertion path).
u32 random_unit(Machine& m, std::mt19937& rng, unsigned slot, bool enemy) {
    const u32 va = kUnits + slot * kUnitStride;
    fill_random(m, va, kUnitStride, rng);
    u16 flags = load16(m, va);
    flags = enemy ? static_cast<u16>(flags | btl::kUnitFlagEnemy) : static_cast<u16>(flags & ~btl::kUnitFlagEnemy);
    store16(m, va, flags);
    {  // ids always in range: the recompiled callees index the persona / enemy tables with them unchecked
        const u16 id = enemy ? static_cast<u16>(rng() % btl::kEnemyCount) : static_cast<u16>(1 + rng() % 10);
        store16(m, va + 2, id);
        store16(m, va + 4, id);
    }
    if (rng() % 8 != 0) m.at(va + 6)[0] = static_cast<u8>(1 + rng() % 99);
    return va;
}

// A random datScript context: attacker / target (NULL now and then), skill, mode, gBtl, the two table flags.
void random_context(Machine& m, std::mt19937& rng) {
    for (unsigned s = 0; s < 8; ++s) random_unit(m, rng, s, (rng() & 1) != 0);
    const auto pick_unit = [&]() -> u32 { return rng() % 20 == 0 ? 0u : kUnits + (rng() % 8) * kUnitStride; };
    store32(m, kAttacker, pick_unit());
    store32(m, kTarget, pick_unit());
    store32(m, kResult, rng());
    store16(m, kSkill, rng() % 6 == 0 ? static_cast<u16>(rng()) : static_cast<u16>(rng() % btl::kSkillCount));
    u32 mode;
    switch (rng() % 6) {
    case 0: mode = 1; break;
    case 1: mode = 2; break;
    case 2: mode = 1u << (rng() % 17); break;
    case 3: mode = rng() % 4; break;
    case 4: mode = rng(); break;
    default: mode = (rng() & 1) ? 1u : 2u; break;
    }
    store32(m, kMode, mode);
    store16(m, kFlags, static_cast<u16>(rng()));
    store32(m, kBtlPtr, rng() % 10 == 0 ? 0u : kBtl);
    const u32 flags = load32(m, kFlagWord) & ~((1u << 17) | (1u << 25));
    store32(m, kFlagWord, flags | ((rng() % 3 == 0) ? (1u << 17) : 0u) | ((rng() % 3 == 0) ? (1u << 25) : 0u));
}

// --- the extended pair ------------------------------------------------------------------------------------------
// RtHooks that also hashes the cycle count at every check point.
class TraceHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    int checks = 0;
    u64 trace = 0;
    void syscall(EEContext&, u32) override { FAIL("unexpected syscall"); }
    void check_events(EEContext& ctx) override {
        ++checks;
        trace = (trace ^ ctx.cycles) * 0x100000001B3ull;
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { FAIL("unexpected trap"); }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw rt_test::FatalEvent{pc, what, &ctx}; }
};

struct Ext {
    Outcome o;
    u64 trace = 0;
    u32 f0 = 0, f20 = 0, acc = 0, fcr31 = 0;
    u64 hi[2] = {}, lo[2] = {};
    std::vector<u8> context;
};

// pair_harness.h's run() with random FPU state, $t0 (the fifth argument) and the check-point trace.
Ext run_ext(Machine& m, Fn fn, const Args& args, u64 t0, u32 seed) {
    TraceHooks hooks;
    rt_test::HooksScope scope{&hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    m.ctx.gpr[GPR_T0].u64[0] = t0;
    for (u32& f : m.ctx.fpr) f = rng();
    m.ctx.acc = rng();
    m.ctx.fcr31 = rng() & 0x0083C078u;
    m.ctx.hi.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.lo.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    const u64 c0 = m.ctx.cycles;
    fn(m.ctx);
    Ext e;
    e.o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) e.o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    e.o.cycles = m.ctx.cycles - c0;
    e.o.checks = hooks.checks;
    e.o.arena = m.bytes(kArena, kArenaSize);
    e.o.live_stack = m.bytes(kSp, 0x100);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    e.trace = hooks.trace;
    e.f0 = m.ctx.fpr[0];
    e.f20 = m.ctx.fpr[20];
    e.acc = m.ctx.acc;
    e.fcr31 = m.ctx.fcr31;
    for (int i = 0; i < 2; ++i) {
        e.hi[i] = m.ctx.hi.u64[i];
        e.lo[i] = m.ctx.lo.u64[i];
    }
    e.context = m.bytes(kContext, kContextSize);
    return e;
}

struct ExtPair {
    Ext hand;
    Ext recomp;
};

// Runs hand then recomp from the same guest state (the context words are restored in between) and compares
// everything listed at the top of the file. Returns the pair (the recomp run's memory is in place after).
ExtPair pair_ext(Machine& m, Fn hand, Fn recomp, const Args& args, u64 t0, u32 seed, const std::string& what) {
    INFO(what);
    const std::vector<u8> before = m.bytes(kContext, kContextSize);
    ExtPair p;
    p.hand = run_ext(m, hand, args, t0, seed);
    std::memcpy(m.at(kContext), before.data(), kContextSize);
    p.recomp = run_ext(m, recomp, args, t0, seed);
    expect_same(p.hand.o, p.recomp.o, what.c_str());
    CHECK(p.hand.trace == p.recomp.trace);
    CHECK(p.hand.f0 == p.recomp.f0);
    CHECK(p.hand.f20 == p.recomp.f20);
    CHECK(p.hand.acc == p.recomp.acc);
    CHECK(p.hand.fcr31 == p.recomp.fcr31);
    CHECK(p.hand.hi[0] == p.recomp.hi[0]);
    CHECK(p.hand.hi[1] == p.recomp.hi[1]);
    CHECK(p.hand.lo[0] == p.recomp.lo[0]);
    CHECK(p.hand.lo[1] == p.recomp.lo[1]);
    CHECK(p.hand.context == p.recomp.context);
    return p;
}

u64 random_selector(std::mt19937& rng) {
    const u32 r = rng() % 100;
    if (r < 88) return rng() % kSelectorCount;
    if (r < 96) return kSelectorCount + rng() % 30;
    return (static_cast<u64>(rng()) << 32) | rng();
}
u64 random_index(std::mt19937& rng) {
    switch (rng() % 10) {
    case 0: return 5 + rng() % 10;
    case 1: return ~static_cast<u64>(rng() % 4);  // -1..-4
    case 2: return (static_cast<u64>(rng()) << 32) | rng();
    default: return rng() % 5;
    }
}

f32 as_float(u32 bits) {
    f32 f;
    std::memcpy(&f, &bits, 4);
    return f;
}

// One getter call through the hand entry point on the current context (no pair), for the documented rules.
u32 get_value(Machine& m, u64 selector, u64 index) {
    return run_ext(m, &recomp_gen::fn_datScriptGetValue_0030fdf0, Args{selector, index}, 0, 1u).f0;
}

}  // namespace

TEST_CASE("game(battle_ai): the formula tables, the jump table and the constants are what the doc says") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    CHECK(m.str(kDatScriptSourceFile) == "datScript.c");
    // sDatScriptFuncTbl1..3: 17 entries each in slot order, the replaced functions; three zero words between.
    const u32 bases[3] = {kFuncTbl1, kFuncTbl2, kFuncTbl3};
    for (const Formula& f : kFormulas) CHECK(load32(m, bases[f.set - 1] + 4u * static_cast<u32>(f.slot)) == f.addr);
    for (u32 i = kFuncCount; i < 20; ++i) {  // Tbl1 and Tbl2 are padded to 20 words; "datScript.c" follows Tbl3's 18th
        CHECK(load32(m, kFuncTbl1 + 4 * i) == 0);
        CHECK(load32(m, kFuncTbl2 + 4 * i) == 0);
    }
    CHECK(load32(m, kFuncTbl3 + 4 * kFuncCount) == 0);
    // The getter's jump table: 35 labels inside datScriptGetValue, 15 and 16 shared, 0 the assertion label.
    std::vector<u32> labels;
    for (u32 i = 0; i < kSelectorCount; ++i) labels.push_back(load32(m, kGetValueJumpTable + 4 * i));
    for (u32 l : labels) CHECK((l >= 0x30FDF0u && l < 0x30FDF0u + 4996u));
    CHECK(labels[15] == labels[16]);
    CHECK(labels[0] == 0x311140u);
    // The .lit4 constants the three sets read.
    CHECK(load32(m, kLit0_80) == 0x3F4CCCCDu);
    CHECK(load32(m, kLit1_35) == 0x3FACCCCDu);
    CHECK(load32(m, kLit0_60) == 0x3F19999Au);
    CHECK(load32(m, kLit1_30) == 0x3FA66666u);
    CHECK(load32(m, kLit0_90) == 0x3F666666u);
}

TEST_CASE("game(battle_ai): datScriptGetValue equals its recompiled body over all 35 selectors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xA1CA1Cu};
    const Tables t = install_tables(m, rng);
    if (!t.real_skill || !t.real_aicalc) MESSAGE("SKIP (partial): no battle/*.TBL beside the ELF; random table images");
    int per_selector[kSelectorCount + 1] = {};
    for (int it = 0; it < 12000; ++it) {
        random_context(m, rng);
        const u64 sel = it < 35 * 40 ? static_cast<u64>(it % 35) : random_selector(rng);  // every selector 40 times first
        const u64 idx = random_index(rng);
        ++per_selector[sel < kSelectorCount ? sel : kSelectorCount];
        pair_ext(m, &recomp_gen::fn_datScriptGetValue_0030fdf0, &recomp_gen::fn_datScriptGetValue_0030fdf0__recomp,
                 Args{sel, idx}, rng(), rng(), "datScriptGetValue selector " + std::to_string(sel) + " index " + std::to_string(idx));
    }
    for (u32 s = 0; s <= kSelectorCount; ++s) CHECK(per_selector[s] >= 40);
}

TEST_CASE("game(battle_ai): the 51 formula functions equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF0F0u};
    install_tables(m, rng);
    for (const Formula& f : kFormulas) {
        for (int it = 0; it < 600; ++it) {
            random_context(m, rng);
            pair_ext(m, f.hand, f.recomp, Args{rng(), rng(), rng(), rng()}, rng(), rng(), std::string(f.name) + " #" + std::to_string(it));
        }
    }
}

TEST_CASE("game(battle_ai): datScriptCalc equals its recompiled body: table choice, dispatch, result") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xCA1Cu};
    install_tables(m, rng);
    for (int it = 0; it < 6000; ++it) {
        random_context(m, rng);
        // fn < 17 (entries 17..19 are zero words: no function to call); now and then with high bits set, which the
        // 64-bit sltiu sees (K_Assert, continues) and the 32-bit index does not.
        u64 fn = rng() % kFuncCount;
        if (rng() % 16 == 0) fn |= static_cast<u64>(1 + rng() % 0xFFFF) << 32;
        const u32 attacker = rng() % 20 == 0 ? 0u : kUnits + (rng() % 8) * kUnitStride;
        const u32 target = rng() % 20 == 0 ? 0u : kUnits + (rng() % 8) * kUnitStride;
        const u32 skill = rng() % 6 == 0 ? rng() : rng() % btl::kSkillCount;
        const u32 mode = (rng() % 3 == 0) ? 1u << (rng() % 17) : 1u + rng() % 2;
        pair_ext(m, &recomp_gen::fn_datScriptCalc_0030fc40, &recomp_gen::fn_datScriptCalc_0030fc40__recomp,
                 Args{fn, sx(attacker), sx(target), sx(skill)}, sx(mode), rng(),
                 "datScriptCalc fn " + std::to_string(fn));
    }
}

TEST_CASE("game(battle_ai): documented values -- constants, gBtl words, the AICALC level-difference tables") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xD0Cu};
    const Tables t = install_tables(m, rng);
    for (int it = 0; it < 400; ++it) {
        random_context(m, rng);
        // Two enemy units with known levels (datCalcGetLevel: unit +6 for enemies).
        const u32 a = random_unit(m, rng, 0, true), b = random_unit(m, rng, 1, true);
        const s32 la = 1 + static_cast<s32>(rng() % 99), lb = 1 + static_cast<s32>(rng() % 99);
        m.at(a + 6)[0] = static_cast<u8>(la);
        m.at(b + 6)[0] = static_cast<u8>(lb);
        store32(m, kAttacker, a);
        store32(m, kTarget, b);
        const bool in_battle = (rng() & 1) != 0;
        store32(m, kBtlPtr, in_battle ? kBtl : 0u);
        CHECK(as_float(get_value(m, 22, 0)) == 31000.0f);
        if (in_battle) {
            CHECK(as_float(get_value(m, 27, 0)) == static_cast<f32>(load16(m, kBtl + 0xB98) + 1));
            CHECK(as_float(get_value(m, 34, 0)) == static_cast<f32>(load16(m, kBtl + 0xB9E)));
        }
        const s32 result = static_cast<s32>(rng() % 20000) - 10000;
        store32(m, kResult, static_cast<u32>(result));
        CHECK(as_float(get_value(m, 28, 0)) == static_cast<f32>(result));
        // 23: AICALC0[clamp(la - lb, -31, 31) + 31], +94 outside a battle; 33: always the +31 (in-battle) row; 24: AICALC1 of
        // the C-truncated (d -/+ 1) / 3 clamped to -6..6, + 6.
        const s32 d = std::clamp(la - lb, -31, 31);
        CHECK(get_value(m, 23, 0) == load32(m, t.aicalc[0] + 4u * static_cast<u32>(d + (in_battle ? 31 : 94))));
        CHECK(get_value(m, 33, 0) == load32(m, t.aicalc[0] + 4u * static_cast<u32>(d + 31)));
        const s32 q = std::clamp((la > lb ? la - lb - 1 : la - lb + 1) / 3, -6, 6);
        CHECK(get_value(m, 24, 0) == load32(m, t.aicalc[1] + 4u * static_cast<u32>(q + 6)));
    }
    if (t.real_aicalc) {
        // The real AICALC0: the in-battle row is 1.0 at an equal level and grows with the attacker's lead (0.44 at
        // -31, 2.19 at +31); the second row, used when gBtl is NULL, is 1.0 throughout. AICALC1 is 1.0 everywhere.
        CHECK(as_float(load32(m, t.aicalc[0] + 4 * 31)) == 1.0f);
        CHECK(as_float(load32(m, t.aicalc[0])) < as_float(load32(m, t.aicalc[0] + 4 * 62)));
        for (u32 i = 63; i < 126; ++i) CHECK(as_float(load32(m, t.aicalc[0] + 4 * i)) == 1.0f);
        for (u32 i = 0; i < 13; ++i) CHECK(as_float(load32(m, t.aicalc[1] + 4 * i)) == 1.0f);
    }
}

TEST_CASE("game(battle_ai): the constant formulas -- slot 6 is SkillRecord+38, slots 13/14 are 100") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x6u};
    install_tables(m, rng);
    for (int it = 0; it < 300; ++it) {
        random_context(m, rng);
        const u16 skill = static_cast<u16>(rng() % btl::kSkillCount);
        store16(m, kSkill, skill);
        for (const Formula& f : kFormulas) {
            if (f.slot != 6 && f.slot != 13 && f.slot != 14) continue;
            run_ext(m, f.hand, Args{}, 0, rng());
            const s32 got = static_cast<s32>(load32(m, kResult));
            CHECK((load16(m, kFlags) & 1u) == 1u);
            if (f.slot == 6) CHECK(got == m.at(kSkillSec1 + skill * btl::kSkillRecordSize + 38)[0]);
            else CHECK(got == 100);
        }
    }
}

#endif  // P3FES_GAME_HAVE_GENERATED
