// Phase 5 pair tests for the RenderWare sky-driver leaves (game/src/render/rw_leaves.cpp, slice render_rw): each
// hand-written function and the recompiled body it replaces run on identical guest machines built from random
// RenderWare records (matrices, frustum planes, images, texture-cache rings, morph targets, PS2All instance
// records, PDS registries) placed in the arena and in the RW globals / gp words they read. Stricter than
// pair_harness.h's Outcome: per call this file compares EVERY general register (both 64-bit halves), HI/LO, all FPU
// registers, ACC and FCR31, the whole VU0 state (vf, ACC, MAC, STATUS, Q, ...), the arena, the global regions the
// function touches, the WHOLE stack window (dead and live: the hand versions write the original's spills and
// frame words), the virtual cycles and the check-point count. The FPU / VU0 registers start random, so a lane or
// register the original leaves alone must stay alone. Callbacks (sub_49C330, sub_4F1540) are functions of the
// emitted set reached through the dispatch table, including non-leaf ones that spill $ra below the $sp they get.
// Host-side checks restate documented rules (docs/ANALYSIS/22_rendering.md and the RW record layouts in
// rw_leaves.h): the matrix product and orthonormal inverse on exact values, the MSB index, the transfer-size table,
// the interleaved bump-map name, the DMAC channel table.
#include "pair_harness.h"

#include "p3fes/game/rw_leaves.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
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
P3FES_DECL_PAIR(fn_sub_4C1C50_004c1c50)
P3FES_DECL_PAIR(fn_sub_4C1D10_004c1d10)
P3FES_DECL_PAIR(fn_sub_4C1E60_004c1e60)
P3FES_DECL_PAIR(fn_sub_4C2090_004c2090)
P3FES_DECL_PAIR(fn_sub_4C2120_004c2120)
P3FES_DECL_PAIR(fn_sub_4C21B0_004c21b0)
P3FES_DECL_PAIR(fn_sub_4C2F30_004c2f30)
P3FES_DECL_PAIR(fn_sub_4C6970_004c6970)
P3FES_DECL_PAIR(fn_sub_4C9DF0_004c9df0)
P3FES_DECL_PAIR(fn_sub_4CAE30_004cae30)
P3FES_DECL_PAIR(fn_sub_4C2860_004c2860)
P3FES_DECL_PAIR(fn_sub_4C32A0_004c32a0)
P3FES_DECL_PAIR(fn_sub_4CC0A0_004cc0a0)
P3FES_DECL_PAIR(fn_sub_4D6B60_004d6b60)
P3FES_DECL_PAIR(fn_sub_4D81B0_004d81b0)
P3FES_DECL_PAIR(fn_sub_4DB200_004db200)
P3FES_DECL_PAIR(fn_sub_4F0C60_004f0c60)
P3FES_DECL_PAIR(fn_sub_4F1540_004f1540)
P3FES_DECL_PAIR(fn_sub_4F1F80_004f1f80)
P3FES_DECL_PAIR(fn_sub_4F2710_004f2710)
P3FES_DECL_PAIR(fn_sub_4F2E60_004f2e60)
P3FES_DECL_PAIR(fn_sceGsGetGParam_004f9040)
P3FES_DECL_PAIR(fn_sceDmaGetChan_004fa8f0)
P3FES_DECL_PAIR(fn_sub_48A3E0_0048a3e0)
P3FES_DECL_PAIR(fn_sub_490D80_00490d80)
P3FES_DECL_PAIR(fn_sub_491100_00491100)
P3FES_DECL_PAIR(fn_sub_495320_00495320)
P3FES_DECL_PAIR(fn_sub_4992F0_004992f0)
P3FES_DECL_PAIR(fn_sub_49C330_0049c330)
P3FES_DECL_PAIR(fn_sub_49FEC0_0049fec0)
P3FES_DECL_PAIR(fn_sub_4A0C20_004a0c20)
P3FES_DECL_PAIR(fn_sub_4A24A0_004a24a0)
P3FES_DECL_PAIR(fn_sub_4A2BA0_004a2ba0)
P3FES_DECL_PAIR(fn_sub_4A35B0_004a35b0)
P3FES_DECL_PAIR(fn_sub_4A3F70_004a3f70)
P3FES_DECL_PAIR(fn_sub_46AD20_0046ad20)
P3FES_DECL_PAIR(fn_RpPDSGetPipe_0046a890)
P3FES_DECL_PAIR(fn_sub_468720_00468720)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }
constexpr u32 kGpWindow = gpv(-20800);  // every gp word these leaves read or write: gp-20800 .. gp-16800
constexpr u32 kGpWindowLen = 4000;
constexpr u32 kRwGlobals = game::rwl::kRwGlobals;
constexpr u32 kRwGlobalsLen = 0x800;    // plugin offsets used here stay below 0x600
constexpr u32 kTexCacheVars = 0x0077F200u;
constexpr u32 kTexCacheVarsLen = 0x40;
constexpr u32 kStackLo = kSp - kDeadStack;
constexpr u32 kStackLen = kDeadStack + 0x100;

struct Region {
    u32 va;
    u32 len;
};

// --- guest RAM helpers ------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float f) { w32(m, va, std::bit_cast<u32>(f)); }
float rf(const Machine& m, u32 va) { return std::bit_cast<float>(r32(m, va)); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
// A 64-bit register image of a 32-bit value: usually sign-extended, sometimes with stray upper bits.
u64 reg_of(u32 v, std::mt19937& rng) {
    if (chance(rng, 15)) return (static_cast<u64>(rng()) << 32) | v;
    return sx(v);
}
// EE single bit patterns: mostly moderate values, some zeros of both signs, denormals and arbitrary patterns.
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 10) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    case 3: return rng() & 0x807FFFFFu;  // denormal
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 4001) - 2000) / 97.0f);
    }
}
void fill_floats(Machine& m, u32 va, u32 count, std::mt19937& rng) {
    for (u32 i = 0; i < count; ++i) w32(m, va + 4 * i, rand_float(rng));
}

// --- one run with the full machine state captured ------------------------------------------------------------------
struct Snap {
    std::array<u64, 64> gpr{};
    u64 hi[2]{}, lo[2]{};
    std::array<u32, 32> fpr{};
    u32 acc = 0, fcr31 = 0;
    std::vector<u32> vu0;
    u64 cycles = 0;
    int checks = 0;
    std::vector<u8> arena, stack;
    std::vector<std::vector<u8>> regions;
};

std::vector<u32> vu0_words(const VU0State& v) {
    std::vector<u32> w;
    for (const auto& r : v.vf) w.insert(w.end(), std::begin(r), std::end(r));
    for (u16 x : v.vi) w.push_back(x);
    w.insert(w.end(), std::begin(v.acc), std::end(v.acc));
    for (u32 x : {v.q, v.p, v.i, v.r, v.status, v.mac, v.clip, v.tpc, v.cmsar0}) w.push_back(x);
    return w;
}

Snap run_full(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Region>& regions) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (u32& f : m.ctx.fpr) f = rand_float(rng);
    m.ctx.acc = rand_float(rng);
    m.ctx.fcr31 = rng() & 0x0183F07Fu;
    m.ctx.hi.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.hi.u64[1] = rng();
    m.ctx.lo.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.lo.u64[1] = rng();
    for (unsigned r = 1; r < 32; ++r)
        for (u32& x : m.ctx.vu0.vf[r]) x = rand_float(rng);
    for (u32& x : m.ctx.vu0.acc) x = rand_float(rng);
    m.ctx.vu0.status = rng() & 0xFFFu;
    m.ctx.vu0.mac = rng() & 0xFFFFu;
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Snap s;
    for (unsigned r = 0; r < 32; ++r) {
        s.gpr[2 * r] = m.ctx.gpr[r].u64[0];
        s.gpr[2 * r + 1] = m.ctx.gpr[r].u64[1];
    }
    for (int i = 0; i < 2; ++i) {
        s.hi[i] = m.ctx.hi.u64[i];
        s.lo[i] = m.ctx.lo.u64[i];
    }
    std::copy(std::begin(m.ctx.fpr), std::end(m.ctx.fpr), s.fpr.begin());
    s.acc = m.ctx.acc;
    s.fcr31 = m.ctx.fcr31;
    s.vu0 = vu0_words(m.ctx.vu0);
    s.cycles = m.ctx.cycles - c0;
    s.checks = m.hooks.checks - k0;
    s.arena = m.bytes(kArena, kArenaSize);
    s.stack = m.bytes(kStackLo, kStackLen);
    for (const Region& r : regions) s.regions.push_back(m.bytes(r.va, r.len));
    std::memset(m.at(kStackLo), 0, kDeadStack);  // the next run starts from the same stack bytes
    return s;
}

int g_pairs = 0;

// Runs hand and recomp from the same machine state (the arena and every listed region are restored between the
// runs) and requires identical results everywhere. After the pair the recompiled run's output is in place.
std::pair<Snap, Snap> pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                           const std::vector<Region>& regions = {}) {
    const std::vector<u8> arena = m.bytes(kArena, kArenaSize);
    std::vector<std::vector<u8>> before;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    Snap h = run_full(m, hand, args, seed, regions);
    std::memcpy(m.at(kArena), arena.data(), kArenaSize);
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    Snap r = run_full(m, recomp, args, seed, regions);
    ++g_pairs;
    INFO(what << " seed " << seed);
    for (unsigned i = 0; i < 64; ++i) {
        INFO("gpr " << i / 2 << (i % 2 ? " (upper)" : ""));
        CHECK(h.gpr[i] == r.gpr[i]);
    }
    CHECK(h.hi[0] == r.hi[0]);
    CHECK(h.lo[0] == r.lo[0]);
    CHECK(h.hi[1] == r.hi[1]);
    CHECK(h.lo[1] == r.lo[1]);
    for (unsigned i = 0; i < 32; ++i) {
        INFO("fpr " << i);
        CHECK(h.fpr[i] == r.fpr[i]);
    }
    CHECK(h.acc == r.acc);
    CHECK(h.fcr31 == r.fcr31);
    CHECK(h.vu0 == r.vu0);
    CHECK(h.cycles == r.cycles);
    CHECK(h.checks == r.checks);
    CHECK(h.arena == r.arena);
    CHECK(h.stack == r.stack);
    for (std::size_t i = 0; i < regions.size(); ++i) {
        INFO("region " << std::hex << regions[i].va);
        CHECK(h.regions[i] == r.regions[i]);
    }
    return {std::move(h), std::move(r)};
}

u64 v0_of(const Snap& s) { return s.gpr[2 * GPR_V0]; }

const std::vector<Region> kRegGp = {{kGpWindow, kGpWindowLen}};
const std::vector<Region> kRegGpRw = {{kGpWindow, kGpWindowLen}, {kRwGlobals, kRwGlobalsLen}};

}  // namespace

// =================================================================================================================

TEST_CASE("game(render_rw): the error slot, the va_list builder and the singly linked array accessors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4C1C50u};
    for (u32 i = 0; i < 400; ++i) {
        const u32 off = 4 * (rng() % 64);
        w32(m, gpv(game::rwl::kGpErrorOffset), off);
        const u32 slot = kRwGlobals + off;
        w32(m, slot, chance(rng, 60) ? 0 : rng());
        w32(m, slot + 4, chance(rng, 60) ? 0x80000000u : rng());
        const u32 err = kArena + 8 * (rng() % 16);
        w32(m, err, rng());
        w32(m, err + 4, chance(rng, 50) ? (rng() | 0x80000000u) : (rng() & 0x7FFFFFFFu));
        pair(m, PAIR(fn_sub_4C1C50_004c1c50), {reg_of(err, rng), 0, 0, 0}, i, "sub_4C1C50", kRegGpRw);
        pair(m, PAIR(fn_sub_4C1D10_004c1d10), {(static_cast<u64>(rng()) << 32) | rng(), rng(), rng(), rng()}, i, "sub_4C1D10");
    }
    // documented rule on the host: an empty slot takes the first error only.
    w32(m, gpv(game::rwl::kGpErrorOffset), 0x10);
    w32(m, kRwGlobals + 0x10, 0);
    w32(m, kRwGlobals + 0x14, 0x80000000u);
    w32(m, kArena, 7);
    w32(m, kArena + 4, 0x13);
    pair(m, PAIR(fn_sub_4C1C50_004c1c50), {sx(kArena), 0, 0, 0}, 1, "sub_4C1C50 rule", kRegGpRw);
    CHECK(r32(m, kRwGlobals + 0x10) == 7);
    CHECK(r32(m, kRwGlobals + 0x14) == 0x13);
    w32(m, kArena, 9);
    w32(m, kArena + 4, 0x14);
    pair(m, PAIR(fn_sub_4C1C50_004c1c50), {sx(kArena), 0, 0, 0}, 2, "sub_4C1C50 rule 2", kRegGpRw);
    CHECK(r32(m, kRwGlobals + 0x10) == 7);

    for (u32 i = 0; i < 300; ++i) {
        const u32 list = kArena + 16 * (rng() % 32);
        w32(m, list, rng());
        w32(m, list + 4, chance(rng, 30) ? 0 : rng() % 100);
        w32(m, list + 8, rng() % 100);
        w32(m, list + 12, chance(rng, 80) ? 4 * (rng() % 40) : rng());
        const u64 index = reg_of(chance(rng, 80) ? rng() % 64 : rng(), rng);
        pair(m, PAIR(fn_sub_4C2090_004c2090), {sx(list), 0, 0, 0}, i, "sub_4C2090");
        pair(m, PAIR(fn_sub_4C2120_004c2120), {sx(list), 0, 0, 0}, i, "sub_4C2120");
        const auto e = pair(m, PAIR(fn_sub_4C21B0_004c21b0), {sx(list), index, 0, 0}, i, "sub_4C21B0");
        CHECK(static_cast<u32>(v0_of(e.first)) == r32(m, list) + r32(m, list + 12) * static_cast<u32>(index));
        pair(m, PAIR(fn_sub_4C1E60_004c1e60), {sx(list), 0, 0, 0}, i, "sub_4C1E60");
        CHECK(r32(m, list + 4) == 0);
    }
}

TEST_CASE("game(render_rw): sub_4C2F30 matrix product on VU0 equals its recompiled body and multiplies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4C2F30u};
    const u32 A = kArena + 0x100, B = kArena + 0x200, D = kArena + 0x300;
    for (u32 i = 0; i < 400; ++i) {
        fill_floats(m, A, 16, rng);
        fill_floats(m, B, 16, rng);
        w32(m, A + 12, rng());
        w32(m, B + 12, rng());
        const u32 skew = chance(rng, 10) ? 4 * (rng() % 4) : 0;  // LQC2/SQC2 ignore the low four address bits
        const u32 dst = pick(rng, {D, D, D, A, B}) + skew;
        pair(m, PAIR(fn_sub_4C2F30_004c2f30), {reg_of(dst, rng), sx(A + skew), sx(B), 0}, i, "sub_4C2F30");
    }
    // rule: exact small integers -- row i of a * b = sum_k a[i][k] b[k] (+ b's position row for the position row).
    const float a[4][3] = {{1, 2, 0}, {0, 1, 3}, {2, 0, 1}, {5, 6, 7}};
    const float b[4][3] = {{2, 0, 1}, {1, 1, 0}, {0, 3, 1}, {10, 20, 30}};
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c) {
            wf(m, A + 16 * r + 4 * c, a[r][c]);
            wf(m, B + 16 * r + 4 * c, b[r][c]);
        }
    w32(m, A + 12, 0x20003);
    w32(m, B + 12, 0x3);
    pair(m, PAIR(fn_sub_4C2F30_004c2f30), {sx(D), sx(A), sx(B), 0}, 7, "sub_4C2F30 rule");
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c) {
            float want = a[r][0] * b[0][c] + a[r][1] * b[1][c] + a[r][2] * b[2][c] + (r == 3 ? b[3][c] : 0.0f);
            CHECK(rf(m, D + 16 * r + 4 * c) == want);
        }
    CHECK(r32(m, D + 12) == 3);
}

TEST_CASE("game(render_rw): sub_4C6970 normalise and sub_4C9DF0 sphere frustum test equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4C6970u};
    const u32 V = kArena + 0x40;
    for (u32 i = 0; i < 400; ++i) {
        fill_floats(m, V, 3, rng);
        if (chance(rng, 10)) {
            w32(m, V, 0);
            w32(m, V + 4, 0x80000000u);
            w32(m, V + 8, 0);
        }
        const u32 dst = pick(rng, {kArena + 0x80, V, V + 4, V - 4});
        pair(m, PAIR(fn_sub_4C6970_004c6970), {sx(dst), sx(V), 0, 0}, i, "sub_4C6970");
    }
    wf(m, V, 3.0f);
    wf(m, V + 4, 0.0f);
    wf(m, V + 8, 4.0f);
    pair(m, PAIR(fn_sub_4C6970_004c6970), {sx(kArena + 0x80), sx(V), 0, 0}, 1, "sub_4C6970 rule");
    CHECK(std::abs(rf(m, kArena + 0x80) - 0.6f) < 1e-6f);
    CHECK(std::abs(rf(m, kArena + 0x88) - 0.8f) < 1e-6f);

    const u32 cam = kArena + 0x400, sphere = kArena + 0x100;
    int outcomes[3] = {};
    for (u32 i = 0; i < 600; ++i) {
        fill_floats(m, sphere, 3, rng);
        wf(m, sphere + 12, static_cast<float>(rng() % 50) / 4.0f);
        for (u32 p = 0; p < 6; ++p) {
            const u32 pl = cam + 148 + 20 * p;
            fill_floats(m, pl, 3, rng);
            // distances around the centre's projection so that all three outcomes happen
            wf(m, pl + 12, static_cast<float>(static_cast<s32>(rng() % 400) - 300) / 7.0f);
            w32(m, pl + 16, rng());
        }
        const auto p = pair(m, PAIR(fn_sub_4C9DF0_004c9df0), {sx(cam), sx(sphere), 0, 0}, i, "sub_4C9DF0");
        const u64 res = v0_of(p.first);
        CHECK(res <= 2);
        if (res <= 2) ++outcomes[res];
    }
    CHECK(outcomes[0] > 0);
    CHECK(outcomes[1] > 0);
    CHECK(outcomes[2] > 0);
    for (u32 i = 0; i < 100; ++i) {
        const u32 frame = kArena + 0x600, root = kArena + 0x700;
        w32(m, frame + 160, root);
        w8(m, root + 3, static_cast<u8>(rng()));
        const auto p = pair(m, PAIR(fn_sub_4CAE30_004cae30), {sx(frame), 0, 0, 0}, i, "sub_4CAE30");
        CHECK(v0_of(p.first) == (m.at(root)[3] & 3u));
    }
}

TEST_CASE("game(render_rw): sub_4C2860 / sub_4C32A0 matrix inverses equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4C2860u};
    const u32 S = kArena + 0x100, D = kArena + 0x200;
    for (u32 i = 0; i < 500; ++i) {
        fill_floats(m, S, 16, rng);
        w32(m, S + 12, rng());
        if (chance(rng, 10))  // singular: a zero row gives a +0 determinant
            for (u32 k = 0; k < 3; ++k) w32(m, S + 16 + 4 * k, 0);
        const u32 dst = chance(rng, 85) ? D : S;
        pair(m, PAIR(fn_sub_4C2860_004c2860), {reg_of(dst, rng), sx(S), 0, 0}, i, "sub_4C2860");
    }
    for (u32 i = 0; i < 600; ++i) {
        fill_floats(m, S, 16, rng);
        const u32 off = 4 * (rng() % 64);
        w32(m, gpv(game::rwl::kGpMatrixOffset), off);
        w32(m, kRwGlobals + off + 4, chance(rng, 50) ? 0x20000u : rng());
        w32(m, S + 12, pick(rng, {0u, 1u, 2u, 3u, 0x20000u, 0x20003u, rng()}));
        const u32 dst = chance(rng, 85) ? D : S;
        pair(m, PAIR(fn_sub_4C32A0_004c32a0), {reg_of(dst, rng), reg_of(S, rng), rng(), rng()}, i, "sub_4C32A0", kRegGpRw);
    }
    // rule: orthonormal inverse = transpose, pos' = -(pos . column).
    const float rot[3][3] = {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c) wf(m, S + 16 * r + 4 * c, rot[r][c]);
    wf(m, S + 48, 2.0f);
    wf(m, S + 52, 3.0f);
    wf(m, S + 56, 4.0f);
    w32(m, S + 12, 3);
    w32(m, gpv(game::rwl::kGpMatrixOffset), 0);
    w32(m, kRwGlobals + 4, 0);
    pair(m, PAIR(fn_sub_4C32A0_004c32a0), {sx(D), sx(S), 0, 0}, 3, "sub_4C32A0 rule", kRegGpRw);
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c) CHECK(rf(m, D + 16 * r + 4 * c) == rot[c][r]);
    CHECK(rf(m, D + 48) == -3.0f);  // -(2*0 + 3*1 + 4*0)
    CHECK(rf(m, D + 52) == 2.0f);   // -(2*-1 + 3*0 + 4*0)
    CHECK(rf(m, D + 56) == -4.0f);
    CHECK(r32(m, D + 12) == 3);
}

TEST_CASE("game(render_rw): sub_4CC0A0 image alpha from colour equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4CC0A0u};
    const u32 img = kArena, pixels = kArena + 0x100, palette = kArena + 0x1000;
    for (u32 i = 0; i < 300; ++i) {
        const u32 depth = pick(rng, {32u, 32u, 8u, 4u, 4u, 16u, 1u, 0u});
        const s32 width = chance(rng, 10) ? -static_cast<s32>(rng() % 3) : static_cast<s32>(rng() % 9);
        const s32 height = chance(rng, 10) ? -1 : static_cast<s32>(rng() % 7);
        const u32 stride = 4 * static_cast<u32>(width > 0 ? width : 1) + 4 * (rng() % 3);
        w32(m, img + 4, static_cast<u32>(width));
        w32(m, img + 8, static_cast<u32>(height));
        w32(m, img + 12, depth);
        w32(m, img + 16, stride);
        w32(m, img + 20, pixels);
        w32(m, img + 24, palette);
        fill_random(m, pixels, 0xE00, rng);
        fill_random(m, palette, 0x400, rng);
        pair(m, PAIR(fn_sub_4CC0A0_004cc0a0), {reg_of(img, rng), 0, 0, 0}, i, "sub_4CC0A0");
    }
    // rule: alpha = max(r, g, b) per 32-bit pixel.
    w32(m, img + 4, 2);
    w32(m, img + 8, 1);
    w32(m, img + 12, 32);
    w32(m, img + 16, 8);
    w32(m, pixels, 0x00203010u);
    w32(m, pixels + 4, 0xFF0000F0u);
    pair(m, PAIR(fn_sub_4CC0A0_004cc0a0), {sx(img), 0, 0, 0}, 1, "sub_4CC0A0 rule");
    CHECK(r32(m, pixels) == 0x30203010u);
    CHECK(r32(m, pixels + 4) == 0xF00000F0u);
}

TEST_CASE("game(render_rw): MSB, render-state getter and transfer sizes equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D6B60u};
    for (u32 i = 0; i < 300; ++i) {
        u64 v = pick(rng, {0u, 1u, 2u, 3u, 0x80000000u, rng(), rng() >> (rng() % 32)});
        if (chance(rng, 15)) v |= static_cast<u64>(rng()) << 32;
        const auto p = pair(m, PAIR(fn_sub_4D6B60_004d6b60), {v, 0, 0, 0}, i, "sub_4D6B60");
        if ((v >> 32) == 0) CHECK(static_cast<s32>(v0_of(p.first)) == (v ? 31 - std::countl_zero(static_cast<u32>(v)) : -1));
    }
    const u32 out = kArena + 0x10, raster = kArena + 0x100;
    for (u32 i = 0; i < 400; ++i) {
        for (s32 off : {-20256, -16860, -16864, -17072, -16936, -16960}) w32(m, gpv(off), chance(rng, 30) ? 0 : rng());
        w32(m, gpv(-17032), rng());
        w32(m, gpv(-17028), rng());
        w32(m, gpv(-17120), raster);
        w32(m, raster + 8, chance(rng, 40) ? 32 : pick(rng, {8u, 16u, 24u, 4u}));
        u64 state = pick(rng, {0u, 1u, 1u, 2u, 3u, 4u, 4u, 5u, 6u, rng()});
        if (chance(rng, 5)) state |= 0x100000000ull;
        pair(m, PAIR(fn_sub_4D81B0_004d81b0), {state, sx(out), 0, 0}, i, "sub_4D81B0", kRegGp);
    }
    for (u32 i = 0; i < 400; ++i) {
        u64 fmt = pick(rng, {44u, 36u, 20u, 27u, 19u, 58u, 50u, 10u, 2u, 49u, 1u, 48u, 0u, 3u, 100u, rng()});
        if (chance(rng, 5)) fmt |= 0x100000000ull;
        const u32 flags = chance(rng, 50) ? pick(rng, {0u, 2u, 4u, 6u}) : rng();
        pair(m, PAIR(fn_sub_4DB200_004db200), {fmt, reg_of(flags, rng), sx(out), sx(out + 4)}, i, "sub_4DB200");
    }
    // rule: the table (width, height).
    struct Row {
        u32 fmt, flags, w, h;
    };
    for (const Row& r : {Row{44, 0, 8, 1}, Row{58, 0, 4, 1}, Row{48, 0, 2, 1}, Row{0, 0, 2, 1}, Row{3, 0, 0, 1}, Row{19, 2, 16, 4},
                         Row{20, 4, 32, 4}, Row{20, 2, 8, 1}}) {
        pair(m, PAIR(fn_sub_4DB200_004db200), {r.fmt, r.flags, sx(out), sx(out + 4)}, r.fmt, "sub_4DB200 rule");
        CHECK(r32(m, out) == r.w);
        CHECK(r32(m, out + 4) == r.h);
    }
    pair(m, PAIR(fn_sub_4F0C60_004f0c60), {0, 0, 0, 0}, 1, "sub_4F0C60");
}

TEST_CASE("game(render_rw): sub_4F1540 texture-cache release equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F1540u};
    const u32 raster = kArena + 0x40, slots = kArena + 0x400, other = kArena + 0x20;
    const std::vector<Region> regions = {{kGpWindow, kGpWindowLen}, {kTexCacheVars, kTexCacheVarsLen}};
    int with_callback = 0;
    for (u32 i = 0; i < 800; ++i) {
        const u32 ext_off = 4 * (rng() % 32);
        w32(m, gpv(game::rwl::kGpRasterExt), ext_off);
        const u32 count = 1 + rng() % 10;
        w32(m, game::rwl::kTexCacheCount, count);
        w32(m, game::rwl::kTexCacheSlots, slots);
        for (u32 k = 0; k < count; ++k) {
            w32(m, slots + 12 * k, chance(rng, 50) ? 0 : 0x01801000u + 0x40 * k);
            w32(m, slots + 12 * k + 4, rng());
            w32(m, slots + 12 * k + 8, rng());
        }
        const u32 index = rng() % count;
        w32(m, raster + ext_off + 88, chance(rng, 15) ? 0 : slots + 12 * index);
        auto some_index = [&] { return chance(rng, 40) ? index : (chance(rng, 20) ? 0xFFFFFFFFu : rng() % count); };
        w32(m, game::rwl::kTexCacheHit0, some_index());
        w32(m, game::rwl::kTexCacheHit1, some_index());
        // Both ring ends inside [0, count): the trims stop at the other end (with -1 and every slot free the
        // original walks forever).
        w32(m, game::rwl::kTexCacheBack, chance(rng, 50) ? index : rng() % count);
        w32(m, game::rwl::kTexCacheFront, chance(rng, 50) ? index : rng() % count);
        w32(m, game::rwl::kTexCache, chance(rng, 70) ? 1 : 0);
        // Release callback: none, the do-nothing clump callback (leaf) or RpPDSGetPipe (non-leaf, spills $ra).
        const u32 cb = pick(rng, {0u, 0x490D80u, 0x46A890u});
        w32(m, game::rwl::kTexCacheRelease, cb);
        w32(m, game::rwl::kTexCacheLast, chance(rng, 50) ? raster : other);
        const bool calls = r32(m, game::rwl::kTexCache) == 0 && cb != 0 && r32(m, raster + ext_off + 88) != 0;
        with_callback += calls;
        const u64 a0 = reg_of(raster, rng);
        pair(m, PAIR(fn_sub_4F1540_004f1540), {a0, rng(), rng(), rng()}, i, "sub_4F1540", regions);
        CHECK(r32(m, raster + ext_off + 88) == 0);
        // the "last accessed" raster is forgotten when it is this one (compared as the whole $a0 register)
        if (a0 == sx(raster)) CHECK(r32(m, game::rwl::kTexCacheLast) != raster);
    }
    CHECK(with_callback > 0);
}

TEST_CASE("game(render_rw): the Im3D, RxHeap, libgraph and libdma accessors equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F1F80u};
    for (u32 i = 0; i < 200; ++i) {
        const u32 off = 4 * (rng() % 256);
        w32(m, gpv(game::rwl::kGpIm3DOffset), off);
        fill_random(m, kRwGlobals + off + 64, 64, rng);
        w32(m, kRwGlobals + off + 68, chance(rng, 50) ? 0 : rng());
        w32(m, gpv(game::rwl::kGpRxHeap), rng());
        const bool open = r32(m, kRwGlobals + off + 68) != 0;
        const auto p = pair(m, PAIR(fn_sub_4F1F80_004f1f80), {rng(), rng(), rng(), rng()}, i, "sub_4F1F80", kRegGpRw);
        CHECK(v0_of(p.first) == (open ? 1u : 0u));
        if (open) CHECK(r32(m, kRwGlobals + off + 68) == 0);
        pair(m, PAIR(fn_sub_4F2710_004f2710), {0, 0, 0, 0}, i, "sub_4F2710", kRegGp);
        pair(m, PAIR(fn_sub_4F2E60_004f2e60), {0, 0, 0, 0}, i, "sub_4F2E60", kRegGp);
        pair(m, PAIR(fn_sceGsGetGParam_004f9040), {0, 0, 0, 0}, i, "sceGsGetGParam");
        u64 chan = chance(rng, 80) ? rng() % 12 : rng();
        if (chance(rng, 10)) chan |= 0x100000000ull;
        pair(m, PAIR(fn_sceDmaGetChan_004fa8f0), {chan, 0, 0, 0}, i, "sceDmaGetChan");
    }
    // rule: libdma's channel table holds the ten DMAC channel register blocks.
    const u32 bases[10] = {0x10008000u, 0x10009000u, 0x1000A000u, 0x1000B000u, 0x1000B400u,
                           0x1000C000u, 0x1000C400u, 0x1000C800u, 0x1000D000u, 0x1000D400u};
    for (u32 c = 0; c < 10; ++c) {
        const auto p = pair(m, PAIR(fn_sceDmaGetChan_004fa8f0), {c, 0, 0, 0}, c, "sceDmaGetChan rule");
        CHECK(static_cast<u32>(v0_of(p.first)) == bases[c]);
    }
}

TEST_CASE("game(render_rw): sub_491100 interpolated sphere and the rpworld accessors equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x491100u};
    const u32 atomic = kArena, geom = kArena + 0x100, targets = kArena + 0x200;
    for (u32 i = 0; i < 600; ++i) {
        fill_random(m, atomic, 0x60, rng);
        w32(m, atomic + 24, chance(rng, 10) ? 0 : geom);
        const u32 n = rng() % 4;
        w32(m, geom + 24, chance(rng, 5) ? 0xFFFFFFFFu : n);
        w32(m, geom + 92, targets);
        fill_floats(m, targets, 7 * 4, rng);
        w16(m, atomic + 80, static_cast<u16>(pick(rng, {0u, 1u, 2u, 3u, 0xFFFFu})));
        w16(m, atomic + 82, static_cast<u16>(pick(rng, {0u, 1u, 2u, 3u, 0xFFFFu})));
        w32(m, atomic + 88, rand_float(rng));
        w32(m, atomic + 92, rand_float(rng));
        pair(m, PAIR(fn_sub_491100_00491100), {sx(atomic), rng(), rng(), rng()}, i, "sub_491100");
        if (r32(m, atomic + 24) != 0) CHECK((r32(m, atomic + 76) & 2) == 0);
    }
    for (u32 i = 0; i < 200; ++i) {
        const u32 rec = kArena + 0x40;
        fill_random(m, rec, 0x40, rng);
        w32(m, rec, kArena + 0x400);
        fill_random(m, kArena + 0x400, 0x100, rng);
        pair(m, PAIR(fn_sub_48A3E0_0048a3e0), {sx(rec), 0, 0, 0}, i, "sub_48A3E0");
        pair(m, PAIR(fn_sub_490D80_00490d80), {(static_cast<u64>(rng()) << 32) | rng(), 0, 0, 0}, i, "sub_490D80");
        pair(m, PAIR(fn_sub_495320_00495320), {sx(rec), reg_of(rng() % 64, rng), 0, 0}, i, "sub_495320");
        // find-sector callback
        const u32 q = kArena + 0x80;
        const u32 sector = rng();
        w32(m, q, chance(rng, 50) ? sector : rng());
        w32(m, q + 4, 0);
        const auto p = pair(m, PAIR(fn_sub_4992F0_004992f0), {reg_of(sector, rng), sx(q), 0, 0}, i, "sub_4992F0");
        CHECK((v0_of(p.first) == 0) == (r32(m, q + 4) == 1));
        // PS2All group-meshes setter
        const u32 node = kArena + 0xC0, priv = kArena + 0xE0;
        w32(m, node + 20, chance(rng, 30) ? 0 : priv);
        pair(m, PAIR(fn_sub_49FEC0_0049fec0), {chance(rng, 15) ? 0 : reg_of(node, rng), rng(), 0, 0}, i, "sub_49FEC0");
        pair(m, PAIR(fn_sub_4A2BA0_004a2ba0), {0, 0, 0, 0}, i, "sub_4A2BA0");
        pair(m, PAIR(fn_sub_4A35B0_004a35b0), {0, 0, 0, 0}, i, "sub_4A35B0");
    }
}

TEST_CASE("game(render_rw): sub_49C330 for-all-sectors-in-frustum equals its recompiled body with real callbacks") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49C330u};
    const u32 cam = kArena, sectors = kArena + 0x200, data = kArena + 0x100, scratch = kArena + 0x800;
    int stopped = 0, completed = 0;
    for (u32 i = 0; i < 400; ++i) {
        const u32 off = 4 * (rng() % 32);
        w32(m, gpv(game::rwl::kGpCameraSectors), off);
        const u32 count = chance(rng, 10) ? 0 : 1 + rng() % 8;
        w32(m, cam + off, sectors);
        w32(m, cam + off + 4, rng());
        w32(m, cam + off + 8, count);
        for (u32 k = 0; k < 8; ++k) w32(m, sectors + 4 * k, scratch + 0x80 * k);
        fill_random(m, scratch, 0x400, rng);
        fill_floats(m, data, 16, rng);
        w32(m, data + 12, pick(rng, {0u, 3u, 0x20003u}));
        // Callbacks: the find-sector test (leaf; stops on the matching sector), the do-nothing clump callback (leaf;
        // continues), RpPDSGetPipe (non-leaf; 0 unless the id is registered -> stops) and the matrix inverse (non-leaf,
        // calls sub_4C2860 itself; returns its dst -> continues, writes a matrix into the "sector").
        const u32 cb = pick(rng, {0x4992F0u, 0x490D80u, 0x46A890u, 0x4C32A0u});
        if (cb == 0x4992F0u) w32(m, data, scratch + 0x80 * (rng() % 9));
        const u64 camera = reg_of(cam, rng);
        const auto p = pair(m, PAIR(fn_sub_49C330_0049c330), {camera, sx(cb), sx(data), rng()}, i, "sub_49C330", kRegGpRw);
        CHECK(v0_of(p.first) == camera);  // returns the camera register as passed
        (cb == 0x490D80u || cb == 0x4C32A0u) ? ++completed : ++stopped;
    }
    CHECK(stopped > 0);
    CHECK(completed > 0);
}

TEST_CASE("game(render_rw): the PS2All instance test, the Im3D mesh-cache callback and the sector box test") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A0C20u};
    for (u32 i = 0; i < 400; ++i) {
        const u32 mi = kArena, obj = kArena + 0x100, mesh = kArena + 0x140, resp = kArena + 0x180, res = kArena + 0x1C0;
        fill_random(m, mi, 0x40, rng);
        w32(m, mi + 12, obj);
        w32(m, mi + 44, mesh);
        w32(m, mi + 48, resp);
        w32(m, resp, res);
        w32(m, obj, pick(rng, {0u, 2u, 3u, rng()}));
        const u32 n = rng() % 20;
        w32(m, mesh + 4, n);
        w32(m, res + 36, chance(rng, 60) ? ((r32(m, obj) & 2) ? 3 * (n - 2) : n) : rng() % 20);
        w32(m, res + 44, chance(rng, 60) ? r32(m, obj) : rng());
        w32(m, mi + 52, chance(rng, 70) ? (rng() & ~8u) : rng());
        pair(m, PAIR(fn_sub_4A0C20_004a0c20), {sx(mi), rng(), rng(), 0}, i, "sub_4A0C20");
    }
    const std::vector<Region> im3d = {{kGpWindow, kGpWindowLen}, {kRwGlobals, kRwGlobalsLen}, {0x0077DEC0u, 0x40}};
    for (u32 i = 0; i < 300; ++i) {
        const u32 src = kArena, dst = kArena + 0x100;
        fill_random(m, src, 0x40, rng);
        w8(m, src + 36, static_cast<u8>(rng() % 8));
        w32(m, src + 40, chance(rng, 40) ? 0 : rng());
        fill_random(m, dst, 0x20, rng);
        w32(m, gpv(game::rwl::kGpIm3DPrimTable), 4 * (rng() % 64));
        fill_random(m, 0x0077DEC0u, 0x40, rng);
        pair(m, PAIR(fn_sub_4A24A0_004a24a0), {sx(src), sx(dst), rng(), rng()}, i, "sub_4A24A0", im3d);
    }
    const std::vector<Region> frustum = {{kGpWindow, kGpWindowLen}, {kRwGlobals, 16}};
    int outcomes[3] = {};
    for (u32 i = 0; i < 500; ++i) {
        const u32 camblk = kArena + 0x400, sector = kArena + 0x100, out = kArena + 0x10;
        const u32 off = 4 * (rng() % 32);
        w32(m, kRwGlobals, camblk);
        w32(m, gpv(game::rwl::kGpCameraFrustum), off);
        for (u32 p = 0; p < 6; ++p) {
            const u32 pl = camblk + off + 96 + 20 * p;
            fill_floats(m, pl, 3, rng);
            wf(m, pl + 12, static_cast<float>(static_cast<s32>(rng() % 200) - 50) / 3.0f);
            for (u32 k = 0; k < 3; ++k) w8(m, pl + 16 + k, static_cast<u8>(chance(rng, 95) ? rng() % 2 : 2));
            w8(m, pl + 19, static_cast<u8>(rng()));
        }
        fill_floats(m, sector + 96 - 12, 12, rng);
        pair(m, PAIR(fn_sub_4A3F70_004a3f70), {sx(sector), sx(out), rng(), rng()}, i, "sub_4A3F70", frustum);
        const u32 res = r32(m, out);
        CHECK((res == 1 || res == 2));
        if (res <= 2) ++outcomes[res];
    }
    CHECK(outcomes[1] > 0);
    CHECK(outcomes[2] > 0);
}

TEST_CASE("game(render_rw): the PDS registry lookups and the MatFX bump-map name equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46AD20u};
    const std::vector<Region> registry = {{game::rwl::kPdsRegistry, 8}};
    for (u32 i = 0; i < 400; ++i) {
        const u32 reg = kArena, entries = kArena + 0x40;
        const u32 count = chance(rng, 10) ? 0 : rng() % 12;
        w32(m, reg, entries);
        w32(m, reg + 4, count);
        for (u32 k = 0; k < 12; ++k) {
            w32(m, entries + 20 * k + 8, 0x11000u + k);
            w32(m, entries + 20 * k + 16, 0x1A00000u + k);
        }
        u64 id = 0x11000u + rng() % 14;
        if (chance(rng, 10)) id |= 0x100000000ull;
        const auto p = pair(m, PAIR(fn_sub_46AD20_0046ad20), {sx(reg), id, rng(), rng()}, i, "sub_46AD20");
        const u32 k = static_cast<u32>(id) - 0x11000u;
        if (id < 0x100000000ull) CHECK(static_cast<u32>(v0_of(p.first)) == (k < count ? entries + 20 * k : 0u));
        w32(m, game::rwl::kPdsRegistry, entries);
        w32(m, game::rwl::kPdsRegistry + 4, count);
        const auto q = pair(m, PAIR(fn_RpPDSGetPipe_0046a890), {id, rng(), rng(), rng()}, i, "RpPDSGetPipe", registry);
        if (id < 0x100000000ull) CHECK(static_cast<u32>(v0_of(q.first)) == (k < count ? 0x1A00000u + k : 0u));
    }
    const u32 dst = kArena + 0x400, texa = kArena + 0x100, texb = kArena + 0x200;
    auto put_name = [&](u32 tex, const std::string& s) { m.put(tex + 16, s); };
    for (u32 i = 0; i < 300; ++i) {
        std::string a, b;
        for (u32 n = rng() % 24; n--;) a.push_back(static_cast<char>(chance(rng, 90) ? 'a' + rng() % 26 : 0x80 + rng() % 0x7F));
        for (u32 n = rng() % 24; n--;) b.push_back(static_cast<char>('A' + rng() % 26));
        put_name(texa, a);
        put_name(texb, b);
        fill_random(m, dst, 0x40, rng);
        pair(m, PAIR(fn_sub_468720_00468720), {sx(dst), chance(rng, 15) ? 0 : reg_of(texa, rng), sx(texb), rng()}, i, "sub_468720");
    }
    // rule: the names interleaved character by character.
    put_name(texa, "abc");
    put_name(texb, "XYZ12");
    pair(m, PAIR(fn_sub_468720_00468720), {sx(dst), sx(texa), sx(texb), 0}, 1, "sub_468720 rule");
    CHECK(m.str(dst) == "aXbYcZ12");
    pair(m, PAIR(fn_sub_468720_00468720), {sx(dst), 0, sx(texb), 0}, 2, "sub_468720 rule (no base)");
    CHECK(m.str(dst) == "XXYYZZ1122");
    MESSAGE("render_rw pairs compared: " << g_pairs);
}

#else
TEST_CASE("game(render_rw): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
