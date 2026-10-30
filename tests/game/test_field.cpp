// Phase 5 pair tests for the field layer leaves (game/src/field/field.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved registers, the
// arena, the caller's live stack, virtual cycles, check-point count) on randomised inputs. Because these leaves are
// called from compiled code that may keep or spill scratch registers, the WHOLE register file is compared too: all
// 32 GPRs (128 bits), the 32 FPRs, ACC and FCR31 (condition bit and the sticky DIV.S flags), plus the dead stack
// (K_FldFrame_CtlMoveInDir keeps its direction copy there). The documented rules (docs/ANALYSIS/26_field.md) are checked on the
// host, independently of both bodies.
#include "pair_harness.h"

#include "p3fes/game/field.h"

#include <array>
#include <cmath>
#include <cstring>
#include <functional>
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
P3FES_DECL_PAIR(fn_K_Field_Get_001b9120)
P3FES_DECL_PAIR(fn_K_Fld_GetPhase_001b9130)
P3FES_DECL_PAIR(fn_K_Field_GetMajorId_001bab20)
P3FES_DECL_PAIR(fn_K_Field_GetMinorId_001bab30)
P3FES_DECL_PAIR(fn_K_FldDungeon_GetCurrentFloor_001bff20)
P3FES_DECL_PAIR(fn_K_FldDungeon_IsCurrentFloorExplorable_001bff50)
P3FES_DECL_PAIR(fn_K_FldDungeon_GetCurrentFloorData_001bffa0)
P3FES_DECL_PAIR(fn_K_FldDungeon_GetFloorKind_001c0040)
P3FES_DECL_PAIR(fn_K_Scene_IsRandomFloor_001a0250)
P3FES_DECL_PAIR(fn_K_FldFrame_IsPointInTriangle_001aaad0)
P3FES_DECL_PAIR(fn_K_FldFrame_ClosestPointOnSegment_001aae10)
P3FES_DECL_PAIR(fn_K_FldFrame_CtlMoveInDir_001addf0)
P3FES_DECL_PAIR(fn_K_Battle_FindTaskOfUnit_001d8d80)
P3FES_DECL_PAIR(fn_K_Battle_GetNthDatUnit_001d7b70)
P3FES_DECL_PAIR(fn_K_Battle_GetNthFieldUnit_001d7c60)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::fld;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// gp-relative globals as crt0's $gp places them (the bodies read them through $gp = kGp).
constexpr u32 kPhaseVa = kGp - 19108;        // 0x7CE24C
constexpr u32 kDungeonTaskVa = kGp - 19080;  // 0x7CE268
constexpr u32 kSceneIdsVa = kGp - 22448;     // 0x7CD540
static_assert(kPhaseVa == 0x7CE24Cu && kDungeonTaskVa == 0x7CE268u && kSceneIdsVa == 0x7CD540u);

void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void putf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
float getf(const Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.mem.main_ram() + va, 4);
    return f;
}
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}

// The whole register file after a run.
struct Regs {
    u64 gpr[32][2];
    u32 fpr[32];
    u32 acc;
    u32 fcr31;
};
Regs grab(const EEContext& c) {
    Regs r{};
    for (int i = 0; i < 32; ++i) {
        r.gpr[i][0] = c.gpr[i].u64[0];
        r.gpr[i][1] = c.gpr[i].u64[1];
        r.fpr[i] = c.fpr[i];
    }
    r.acc = c.acc;
    r.fcr31 = c.fcr31;
    return r;
}

struct FullPair {
    Outcome hand, recomp;
    Regs hand_regs, recomp_regs;
};

using Prepare = std::function<void(EEContext&)>;

// pair_harness's run(), with random FPR / ACC / FCR31 contents and a hook that sets float arguments before the call.
Outcome run_full(Machine& m, Fn fn, const Args& args, u32 seed, const Prepare& prepare, Regs& regs) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (int i = 0; i < 32; ++i) m.ctx.fpr[i] = rng() & 0xBF7FFFFFu;  // random finite patterns
    m.ctx.acc = rng() & 0xBF7FFFFFu;
    m.ctx.fcr31 = rng() & 0x00800000u;
    if (prepare) prepare(m.ctx);
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Outcome o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned saved[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[saved[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    regs = grab(m.ctx);
    return o;
}

// Both runs on the same inputs (the arena is restored before the second); everything compared.
FullPair full_pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Prepare& prepare = {}) {
    const std::vector<u8> arena = m.bytes(kArena, kArenaSize);
    FullPair p;
    p.hand = run_full(m, hand, args, seed, prepare, p.hand_regs);
    std::memcpy(m.at(kArena), arena.data(), kArenaSize);
    p.recomp = run_full(m, recomp, args, seed, prepare, p.recomp_regs);
    INFO(what);
    expect_same(p.hand, p.recomp, what);
    CHECK(p.hand.dead_stack == p.recomp.dead_stack);
    for (int i = 0; i < 32; ++i) {
        INFO("gpr " << i);
        CHECK(p.hand_regs.gpr[i][0] == p.recomp_regs.gpr[i][0]);
        CHECK(p.hand_regs.gpr[i][1] == p.recomp_regs.gpr[i][1]);
    }
    for (int i = 0; i < 32; ++i) {
        INFO("fpr " << i);
        CHECK(p.hand_regs.fpr[i] == p.recomp_regs.fpr[i]);
    }
    CHECK(p.hand_regs.acc == p.recomp_regs.acc);
    CHECK(p.hand_regs.fcr31 == p.recomp_regs.fcr31);
    return p;
}

// --- shared fixtures -------------------------------------------------------------------------------------------
constexpr u32 kTask = kArena + 0x40;   // a kwln task record (only +60 is read)
constexpr u32 kWork = kArena + 0x100;  // its work

void make_task(Machine& m, u32 task, u32 work) {
    std::memset(m.at(task), 0, 0x68);
    put32(m, task + kTaskWork, work);
}

TEST_CASE("game(field): sField, the load phase and the root's field ids equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D001u};
    for (int it = 0; it < 20; ++it) {
        const FullPair p = full_pair(m, PAIR(fn_K_Field_Get_001b9120), Args{}, rng(), "K_Field_Get");
        CHECK(p.hand.v0 == 0x869F60u);  // sField
    }
    const s32 phases[] = {0, 1, 2, 3, -1, 0x7FFFFFFF, static_cast<s32>(0x80000000u)};
    for (int it = 0; it < 40; ++it) {
        const s32 ph = it < 7 ? phases[it] : static_cast<s32>(rng());
        put32(m, kPhaseVa, static_cast<u32>(ph));
        const FullPair p = full_pair(m, PAIR(fn_K_Fld_GetPhase_001b9130), Args{}, rng(), "K_Fld_GetPhase");
        CHECK(p.hand.v0 == sx(static_cast<u32>(ph)));  // lw: sign-extended
    }
    for (int it = 0; it < 60; ++it) {
        make_task(m, kTask, kWork);
        std::memset(m.at(kWork), 0, 104);
        const u16 major = static_cast<u16>(it < 4 ? (it == 0 ? 0 : it == 1 ? 0xFFFF : it == 2 ? 0x8000 : 51) : rng());
        const u16 minor = static_cast<u16>(rng());
        put16(m, kWork + kRootMajor, major);
        put16(m, kWork + kRootMinor, minor);
        const FullPair a = full_pair(m, PAIR(fn_K_Field_GetMajorId_001bab20), Args{sx(kTask)}, rng(), "K_Field_GetMajorId");
        const FullPair b = full_pair(m, PAIR(fn_K_Field_GetMinorId_001bab30), Args{sx(kTask)}, rng(), "K_Field_GetMinorId");
        CHECK(a.hand.v0 == major);  // lhu: zero-extended
        CHECK(b.hand.v0 == minor);
    }
}

TEST_CASE("game(field): the dungeon floor accessors equal their recompiled bodies and the 2..399 rule") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D002u};
    const s32 floors[] = {0, 1, 2, 3, 16, 263, 398, 399, 400, 401, 511, -1, -2, 0x7FFFFFFF, static_cast<s32>(0x80000000u)};
    const u32 table = 0x867F60u;  // gFldDngFloorsData
    for (int it = 0; it < 120; ++it) {
        const bool have = it % 7 != 0;
        make_task(m, kTask, kWork);
        std::memset(m.at(kWork), 0, 64);
        const s32 floor = it < 15 ? floors[it] : static_cast<s32>(it % 3 ? rng() % 600 : rng());
        const s32 kind = static_cast<s32>(it % 5 == 4 ? rng() : rng() % 5);
        const u32 tbl = it % 4 ? table : rng();
        put32(m, kWork + kDngFloor, static_cast<u32>(floor));
        put32(m, kWork + kDngFloorKind, static_cast<u32>(kind));
        put32(m, kWork + kDngFloorTable, tbl);
        put32(m, kDungeonTaskVa, have ? kTask : 0u);
        const FullPair a = full_pair(m, PAIR(fn_K_FldDungeon_GetCurrentFloor_001bff20), Args{}, rng(), "K_FldDungeon_GetCurrentFloor");
        const FullPair b = full_pair(m, PAIR(fn_K_FldDungeon_IsCurrentFloorExplorable_001bff50), Args{}, rng(), "K_FldDungeon_IsCurrentFloorExplorable");
        const FullPair c = full_pair(m, PAIR(fn_K_FldDungeon_GetCurrentFloorData_001bffa0), Args{}, rng(), "K_FldDungeon_GetCurrentFloorData");
        const FullPair d = full_pair(m, PAIR(fn_K_FldDungeon_GetFloorKind_001c0040), Args{}, rng(), "K_FldDungeon_GetFloorKind");
        if (have) {
            CHECK(a.hand.v0 == sx(static_cast<u32>(floor)));
            CHECK(b.hand.v0 == ((floor >= 2 && floor < 400) ? 1u : 0u));
            CHECK(static_cast<u32>(c.hand.v0) == tbl + 16u * static_cast<u32>(floor));
            CHECK(d.hand.v0 == sx(static_cast<u32>(kind)));
        } else {
            CHECK(a.hand.v0 == 0);
            CHECK(b.hand.v0 == 0);  // floor 0: not explorable
            CHECK(c.hand.v0 == 0);
            CHECK(d.hand.v0 == 0);
        }
    }
}

TEST_CASE("game(field): the random-floor predicate equals its recompiled body: major 21..28 / 41..48 with minor 0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D003u};
    const u32 rec = kArena + 0x300;
    put32(m, kSceneIdsVa, rec);
    int yes = 0;
    for (s32 major = -3; major <= 82; ++major) {
        for (const s32 minor : {0, 1, 2, 50, -1}) {
            put32(m, rec + 0, static_cast<u32>(major));
            put32(m, rec + 4, static_cast<u32>(minor));
            const FullPair p = full_pair(m, PAIR(fn_K_Scene_IsRandomFloor_001a0250), Args{}, rng(), "K_Scene_IsRandomFloor");
            const bool expect = minor == 0 && ((major >= 21 && major < 29) || (major >= 41 && major < 49));
            CHECK(p.hand.v0 == (expect ? 1u : 0u));
            yes += expect;
        }
    }
    CHECK(yes == 16);
    for (int it = 0; it < 50; ++it) {
        put32(m, rec + 0, rng());
        put32(m, rec + 4, it % 2 ? 0u : rng());
        full_pair(m, PAIR(fn_K_Scene_IsRandomFloor_001a0250), Args{}, rng(), "K_Scene_IsRandomFloor(random)");
    }
}

// --- the point-in-triangle test ------------------------------------------------------------------------------------
constexpr u32 kVerts = kArena + 0x400;  // u32[3] pointers
constexpr u32 kVert0 = kArena + 0x440;  // three f32[3] at 16-byte strides
constexpr u32 kPoint = kArena + 0x480;
constexpr u32 kNormal = kArena + 0x4A0;

void put_v3(Machine& m, u32 va, float x, float y, float z) {
    putf(m, va + 0, x);
    putf(m, va + 4, y);
    putf(m, va + 8, z);
}

// Host reference for a point strictly inside / outside an XZ triangle (the floor case, normal (0, 1, 0)).
float edge(float ax, float az, float bx, float bz, float px, float pz) { return (bx - ax) * (pz - az) - (bz - az) * (px - ax); }

TEST_CASE("game(field): K_FldFrame_IsPointInTriangle equals its recompiled body and the floor crossing rule") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D004u};
    std::uniform_real_distribution<float> coord(-2000.0f, 2000.0f);
    for (int k = 0; k < 3; ++k) put32(m, kVerts + 4 * k, kVert0 + 16 * k);
    int inside = 0, outside = 0, checked = 0;
    for (int it = 0; it < 1500; ++it) {
        const bool grid = it % 3 == 1;  // small integer grid: equal coordinates, edges through the point
        auto c = [&] { return grid ? static_cast<float>(static_cast<int>(rng() % 9) - 4) * 100.0f : coord(rng); };
        float v[3][3];
        for (auto& vv : v)
            for (float& x : vv) x = c();
        for (int k = 0; k < 3; ++k) put_v3(m, kVert0 + 16 * k, v[k][0], v[k][1], v[k][2]);
        const float px = c(), py = c(), pz = c();
        put_v3(m, kPoint, px, py, pz);
        float n[3];
        switch (it % 6) {
        case 0: n[0] = 0; n[1] = 1; n[2] = 0; break;  // the floor case
        case 1: n[0] = 1; n[1] = 0.5f; n[2] = -0.25f; break;
        case 2: n[0] = 0.1f; n[1] = -0.2f; n[2] = -3; break;
        case 3: n[0] = 1; n[1] = 1; n[2] = 1; break;  // ties
        case 4: n[0] = 0; n[1] = 0; n[2] = 0; break;
        default: n[0] = coord(rng); n[1] = coord(rng); n[2] = coord(rng); break;
        }
        put_v3(m, kNormal, n[0], n[1], n[2]);
        const FullPair p = full_pair(m, PAIR(fn_K_FldFrame_IsPointInTriangle_001aaad0), Args{sx(kPoint), sx(kVerts), sx(kNormal)}, rng(),
                                     "K_FldFrame_IsPointInTriangle");
        if (it % 6 == 0 && !grid) {
            const float e0 = edge(v[0][0], v[0][2], v[1][0], v[1][2], px, pz);
            const float e1 = edge(v[1][0], v[1][2], v[2][0], v[2][2], px, pz);
            const float e2 = edge(v[2][0], v[2][2], v[0][0], v[0][2], px, pz);
            const float margin = 1000.0f;  // well away from an edge (float rounding differs from the EE's)
            const bool in = (e0 > margin && e1 > margin && e2 > margin) || (e0 < -margin && e1 < -margin && e2 < -margin);
            const bool out = (e0 < -margin || e1 < -margin || e2 < -margin) && (e0 > margin || e1 > margin || e2 > margin);
            if (in) {
                CHECK(p.hand.v0 == 1);
                ++inside;
            } else if (out) {
                CHECK(p.hand.v0 == 0);
                ++outside;
            }
            checked += in || out;
        }
    }
    CHECK(inside > 10);
    CHECK(outside > 50);
    CHECK(checked > 100);
    // A vertical edge pair with equal s on both ends never divides (the straddle test excludes it); a zero-height
    // triangle (all s equal) is never inside.
    put_v3(m, kVert0 + 0, 0, 0, 0);
    put_v3(m, kVert0 + 16, 100, 0, 0);
    put_v3(m, kVert0 + 32, 50, 0, 0);
    put_v3(m, kPoint, 50, 0, 0);
    put_v3(m, kNormal, 0, 1, 0);
    const FullPair z = full_pair(m, PAIR(fn_K_FldFrame_IsPointInTriangle_001aaad0), Args{sx(kPoint), sx(kVerts), sx(kNormal)}, 7, "degenerate");
    CHECK(z.hand.v0 == 0);
}

// --- closest point on a segment --------------------------------------------------------------------------------------
TEST_CASE("game(field): the closest point on a segment equals its recompiled body (and with out aliasing an input)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D005u};
    std::uniform_real_distribution<float> coord(-3000.0f, 3000.0f);
    const u32 out = kArena + 0x500, pp = kArena + 0x520, aa = kArena + 0x540, bb = kArena + 0x560;
    int at_a = 0, at_b = 0, between = 0;
    for (int it = 0; it < 1200; ++it) {
        const bool grid = it % 4 == 0;
        auto c = [&] { return grid ? static_cast<float>(static_cast<int>(rng() % 7) - 3) * 50.0f : coord(rng); };
        const float a[3] = {c(), c(), c()}, b[3] = {c(), c(), c()}, p[3] = {c(), c(), c()};
        put_v3(m, aa, a[0], a[1], a[2]);
        put_v3(m, bb, b[0], b[1], b[2]);
        put_v3(m, pp, p[0], p[1], p[2]);
        put_v3(m, out, 1.5f, 2.5f, 3.5f);
        const u32 o = it % 10 == 9 ? aa : (it % 10 == 8 ? pp : out);  // aliasing cases
        const FullPair r = full_pair(m, PAIR(fn_K_FldFrame_ClosestPointOnSegment_001aae10), Args{sx(o), sx(pp), sx(aa), sx(bb)}, rng(),
                                     "K_FldFrame_ClosestPointOnSegment");
        CHECK(r.hand.v0 == sx(o));
        if (o != out) continue;
        // Host rule: t = (p - a).d / |d|^2 clamped to [0, 1]; out = a + t d (tolerance: EE truncation).
        const double d[3] = {double(b[0]) - a[0], double(b[1]) - a[1], double(b[2]) - a[2]};
        const double dd = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        const double t = ((p[0] - a[0]) * d[0] + (p[1] - a[1]) * d[1] + (p[2] - a[2]) * d[2]);
        if (dd < 1.0) continue;
        const double tt = t <= 0 ? 0 : (t >= dd ? 1 : t / dd);
        at_a += tt == 0;
        at_b += tt == 1;
        between += tt > 0 && tt < 1;
        for (int k = 0; k < 3; ++k) {
            const double want = a[k] + tt * d[k];
            CHECK(std::fabs(getf(m, out + 4 * k) - want) <= 0.5 + 1e-4 * std::fabs(want) + 1e-3 * std::sqrt(dd));
        }
    }
    CHECK(at_a > 50);
    CHECK(at_b > 50);
    CHECK(between > 50);
}

// --- the movement request --------------------------------------------------------------------------------------------
TEST_CASE("game(field): K_FldFrame_CtlMoveInDir equals its recompiled body; only an idle controller takes a move") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D006u};
    std::uniform_real_distribution<float> unit(-1.0f, 1.0f);
    const u32 dir = kArena + 0x600;
    const float speeds[] = {0.0f, 1.0f, 7.5f, 30.0f, -12.0f, 2147483648.0f, 3.0e9f, 4.5e9f, 1.0e20f, -1.0e20f, 0.49f};
    int moved = 0;
    for (int it = 0; it < 400; ++it) {
        make_task(m, kTask, kWork);
        std::memset(m.at(kWork), 0, 52);
        const u32 state = it % 4 == 0 ? rng() % 3 : (it % 4 == 1 ? rng() : 1u);
        put32(m, kWork + kCtlState, state);
        const s32 dist0 = static_cast<s32>(rng());
        put32(m, kWork + kCtlDistance, static_cast<u32>(dist0));
        put_v3(m, kWork + kCtlVelocity, 9.0f, 9.0f, 9.0f);
        const float dx = unit(rng), dy = unit(rng) * 0.1f, dz = unit(rng);
        put_v3(m, dir, dx, dy, dz);
        const float speed = it < 11 ? speeds[it] : (it % 2 ? unit(rng) * 40.0f : unit(rng) * 5.0e9f);
        const FullPair p = full_pair(m, PAIR(fn_K_FldFrame_CtlMoveInDir_001addf0), Args{sx(kTask), sx(dir)}, rng(), "K_FldFrame_CtlMoveInDir",
                                     [&](EEContext& c) { c.fpr[12] = fbits(speed); });
        if (state == 1) {
            ++moved;
            CHECK(get32(m, kWork + kCtlState) == 0u);
            if (std::fabs(speed) < 1.0e6f) {
                CHECK(std::fabs(getf(m, kWork + kCtlVelocity + 0) - dx * speed) <= 1e-3f * (1.0f + std::fabs(speed)));
                CHECK(std::fabs(getf(m, kWork + kCtlVelocity + 8) - dz * speed) <= 1e-3f * (1.0f + std::fabs(speed)));
                CHECK(get32(m, kWork + kCtlDistance) == static_cast<u32>(dist0) + static_cast<u32>(static_cast<s32>(speed)));
            }
        } else {
            CHECK(get32(m, kWork + kCtlState) == state);
            CHECK(getf(m, kWork + kCtlVelocity) == 9.0f);
            CHECK(get32(m, kWork + kCtlDistance) == static_cast<u32>(dist0));
        }
    }
    CHECK(moved > 100);
}

// --- the battle kosaka lookups -------------------------------------------------------------------------------------
constexpr u32 kTasks = 0x875A40u;          // the three live battle kosaka tasks
constexpr u32 kBkTask0 = kArena + 0x700;   // up to three tasks (0x68 apart)
constexpr u32 kBkWork0 = kArena + 0x840;   // their works (0x60 apart)
constexpr u32 kUnits0 = kArena + 0x980;    // 16 field units (0x50 apart; only +72 is read)
constexpr u32 kEnc0 = kArena + 0xE80;      // 16 encounter instances (0x10 apart: +4 -> DatUnit array)
constexpr u32 kDat0 = kArena + 0xF80;      // 8 DatUnit arrays (6 x 60 = 360 bytes each), up to kArena + 0x1AC0
static_assert(kDat0 + 8 * 360 <= kArena + kArenaSize);

u32 unit_va(int i) { return kUnits0 + 0x50u * static_cast<u32>(i); }
u32 enc_va(int i) { return kEnc0 + 0x10u * static_cast<u32>(i); }
u32 dat_va(int i) { return kDat0 + 360u * static_cast<u32>(i); }

TEST_CASE("game(field): the battle kosaka task lookup equals its recompiled body (64-bit unit compare)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D007u};
    int hits = 0, misses = 0;
    for (int it = 0; it < 400; ++it) {
        std::vector<u32> entries[3];
        for (int t = 0; t < 3; ++t) {
            const bool live = rng() % 4 != 0;
            const u32 task = kBkTask0 + 0x68u * t, work = kBkWork0 + 0x60u * t;
            put32(m, kTasks + 4 * t, live ? task : 0u);
            make_task(m, task, work);
            std::memset(m.at(work), 0, 0x54);
            const s32 np = static_cast<s32>(rng() % 6) - 1, ne = static_cast<s32>(rng() % 6) - 1;  // -1..4
            put32(m, work + kBkPartyCount, static_cast<u32>(np));
            put32(m, work + kBkEnemyCount, static_cast<u32>(ne));
            for (int k = 0; k < 4; ++k) {
                const u32 pu = unit_va(rng() % 16), eu = unit_va(rng() % 16);
                put32(m, work + kBkParty + 4 * k, pu);
                put32(m, work + kBkEnemy + 4 * k, eu);
                if (live && k < np) entries[t].push_back(pu);
                if (live && k < ne) entries[t].push_back(eu);
            }
        }
        u64 unit;
        switch (it % 5) {
        case 0: unit = 0; break;
        case 1: unit = 0xFFFFFFFF00000000ull | unit_va(rng() % 16); break;  // upper half differs: never equal
        default: unit = sx(unit_va(rng() % 16)); break;
        }
        const FullPair p = full_pair(m, PAIR(fn_K_Battle_FindTaskOfUnit_001d8d80), Args{unit, rng(), rng(), rng()}, rng(), "K_Battle_FindTaskOfUnit");
        u32 want = 0;
        for (int t = 0; t < 3 && unit != 0 && want == 0; ++t)
            for (u32 e : entries[t])
                if (sx(e) == unit) {
                    want = kBkTask0 + 0x68u * t;
                    break;
                }
        // The original stops at the first match scanning party then enemy lists: the first task with the unit.
        CHECK(static_cast<u32>(p.hand.v0) == want);
        (want ? hits : misses)++;
    }
    CHECK(hits > 60);
    CHECK(misses > 50);
}

TEST_CASE("game(field): the n-th battle unit / field unit walks equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D008u};
    int found = 0;
    for (int it = 0; it < 300; ++it) {
        make_task(m, kBkTask0, kBkWork0);
        std::memset(m.at(kBkWork0), 0, 0x54);
        // Field units: +72 -> encounter instance; party instances' +4 is a DatUnit*, enemy ones' +4 a DatUnit[6].
        for (int u = 0; u < 16; ++u) put32(m, unit_va(u) + kFldUnitEncounter, enc_va(u));
        for (int e = 0; e < 16; ++e) put32(m, enc_va(e) + kEncounterUnits, dat_va(e % 8));
        for (int d = 0; d < 8; ++d)
            for (int s = 0; s < 6; ++s) put16(m, dat_va(d) + 60u * s + 2, static_cast<u16>(rng() % 3 == 0 ? 0 : 1 + rng() % 300));
        const s32 np = static_cast<s32>(rng() % 6) - 1, ne = static_cast<s32>(rng() % 6) - 1;
        put32(m, kBkWork0 + kBkPartyCount, static_cast<u32>(np));
        put32(m, kBkWork0 + kBkEnemyCount, static_cast<u32>(ne));
        std::vector<u32> party, enemy;
        for (int k = 0; k < 4; ++k) {
            const int pu = rng() % 16, eu = rng() % 16;
            put32(m, kBkWork0 + kBkParty + 4 * k, unit_va(pu));
            put32(m, kBkWork0 + kBkEnemy + 4 * k, unit_va(eu));
            party.push_back(unit_va(pu));
            enemy.push_back(unit_va(eu));
        }
        // Host walk (26_field.md section 7.3).
        std::vector<std::pair<u32, u32>> walk;  // {DatUnit, field unit}
        for (int k = 0; k < np && k < 4; ++k) walk.push_back({get32(m, get32(m, party[k] + kFldUnitEncounter) + kEncounterUnits), party[k]});
        for (int k = 0; k < ne && k < 4; ++k) {
            const u32 arr = get32(m, get32(m, enemy[k] + kFldUnitEncounter) + kEncounterUnits);
            for (int s = 0; s < 6; ++s) {
                u16 id;
                std::memcpy(&id, m.at(arr + 60u * s + 2), 2);
                if (id) walk.push_back({arr + 60u * s, enemy[k]});
            }
        }
        const u64 n = it % 13 == 0 ? (0xFFFFFFFF00000000ull | (rng() % 4)) : static_cast<u64>(rng() % 30) - (it % 17 == 0 ? 40 : 0);
        const FullPair a = full_pair(m, PAIR(fn_K_Battle_GetNthDatUnit_001d7b70), Args{sx(kBkTask0), n, rng(), rng()}, rng(), "K_Battle_GetNthDatUnit");
        const FullPair b = full_pair(m, PAIR(fn_K_Battle_GetNthFieldUnit_001d7c60), Args{sx(kBkTask0), n, rng(), rng()}, rng(), "K_Battle_GetNthFieldUnit");
        if (n < walk.size()) {
            CHECK(static_cast<u32>(a.hand.v0) == walk[n].first);
            CHECK(static_cast<u32>(b.hand.v0) == walk[n].second);
            ++found;
        } else {
            CHECK(a.hand.v0 == 0);
            CHECK(b.hand.v0 == 0);
        }
    }
    CHECK(found > 50);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
