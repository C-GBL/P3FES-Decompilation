// The pair harness of slice battle_camera (tests/game/test_battle_camera*.cpp): a random battle world, the whole
// register file at every check point / the return / a missing-function stop, the whole 32 MiB of RAM per pair
// (PairRange), argument generators and the spec runner. test_battle_camera.cpp documents what a pair compares.
// Header-only, everything in an unnamed namespace: each test file of the slice gets its own copy (and its own stats).
#pragma once

#include "pair_harness.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#include "p3fes/game/battle_camera.h"

#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

// Declares the hand-written entry point of a replaced function and its recompiled body (an X-list's X).
#define P3FES_BCAM_DECL_PAIR(name, addr)  \
    void fn_##name##_##addr(EEContext&); \
    void fn_##name##_##addr##__recomp(EEContext&);

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::game_test::bcam_test {

namespace {

namespace bc = p3fes::game::btl_cam;

// --- the battle world (free RAM above the arena) ------------------------------------------------------------------
constexpr u32 kGBtlSlot = 0x7CE3ECu;           // *(gp - 18692)
constexpr u32 kHeapHook = 0x960178u;           // RwHeapMalloc device pointer (the packet allocator's jalr)
constexpr u32 kAllocStub = 0x4B3710u;          // `jr ra; move v0, a1`: returns the allocator's $a1 = 0x40000
constexpr u32 kPacketBuf = 0x40000u;           // ... so every packet is built at 0x40000
constexpr u32 kPacketBufSize = 0x10000u;
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x20000u;
constexpr u32 kG = kWorld;                     // gBtl (fields up to +3372)
constexpr u32 kActions = kWorld + 0x1000u;     // 8 x 0x500 (1,200-byte btlActions)
constexpr u32 kUnits = kWorld + 0x4000u;       // 8 x 0xB00 btlUnits
constexpr u32 kData = kWorld + 0xA000u;        // packet data blocks / camera objects / vectors for the arguments
constexpr u32 kDataSize = 0x4000u;
constexpr u32 kSkillTbl = kWorld + 0x10000u;   // a SKILL.TBL stand-in: 1,024 x 44-byte records (*(gp-18680))
constexpr u32 kNumSkills = 1024;
constexpr u32 kSkillTblSlot = kGp - 18680u;
constexpr u32 kNumActions = 8, kNumUnits = 8;

struct Window {
    u32 va;
    u32 len;
};
// Restored before every body of a world (the next body starts from the same world, not from the previous one's output).
const Window kFresh[] = {
    {kWorld, kWorldSize},              // the battle world
    {0x0u, 0x10000u},                  // low RAM: a body that follows a null / small pointer writes there
    {kPacketBuf, kPacketBufSize},      // the packet buffer
};

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
float loadf(const Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void storef(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }
// A 32-bit value as a register argument, sometimes with garbage in the upper half (the bodies take whole registers).
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 25) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }

struct World {
    std::array<u32, kNumActions> actions{};
    std::array<u32, kNumUnits> units{};
};

// A background word: a float in a camera-ish range, a small number, an aligned pointer into the world, or anything
// unmapped (so pointer chases mostly stay inside the world instead of faulting on the first wild address).
u32 background(std::mt19937& rng) {
    const u32 k = rng() % 100;
    return k < 30   ? fbits(frand(rng, -200.0f, 200.0f))
           : k < 40 ? fbits(frand(rng, 0.0f, 1.0f))
           : k < 55 ? rng() % 256
           : k < 60 ? (rng() % 256) & ~0xFu
           : k < 90 ? kWorld + (rng() % kWorldSize & ~0xFu)
                    : 0x02000000u + rng() % 0x0E000000u;  // unmapped: faults, never a stray write
}

World random_world(Machine& m, std::mt19937& rng) {
    World w;
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, background(rng));
    for (u32 i = 0; i < kNumActions; ++i) w.actions[i] = kActions + 0x500u * i;
    for (u32 i = 0; i < kNumUnits; ++i) w.units[i] = kUnits + 0xB00u * i;
    store32(m, kGBtlSlot, kG);
    store32(m, kHeapHook, kAllocStub);
    // RW's engine table: sub_4C6C60 / sub_4C31B0 call the matrix routines through *(gp-17376) + 0x960070 (+8 .. +0x24)
    // (the battle snapshots' values: code addresses of the ELF and the engine's own globals)
    store32(m, kGp - 17376u, 0x134u);
    {
        const u32 words[] = {0x4E3EC0u, 0x4E3F20u, 0x4E3FC0u, 0x4E4020u, 0x95FF50u, 0x20000u, 0x4E3E40u};
        for (u32 k = 0; k < std::size(words); ++k) store32(m, 0x960070u + 0x134u + 8 + 4 * k, words[k]);
    }
    // the game's random state (sub_357FD0's 16 bytes at 0x957BF0; all zero in the ELF, which makes every datCalcRand 0)
    for (u32 k = 0; k < 4; ++k) store32(m, 0x957BF0u + 4 * k, rng() | 1u);
    const auto pick = [&](std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); };
    store32(m, kSkillTblSlot, kSkillTbl);
    for (u32 k = 0; k < kNumSkills; ++k) m.at(kSkillTbl + 44 * k + 17)[0] = static_cast<u8>(pick({0u, 16u, 1u, rng() & 0xFFu}));
    // gBtl flags
    store32(m, kG + 12, rng());
    store32(m, kG + 16, rng() & ~(chance(rng, 70) ? 0x8u : 0u));
    store16(m, kG + 24, static_cast<u16>(rng()));
    // the per-side btlUnit lists (+336 + 8 * side along +2612)
    for (u32 i = 0; i < kNumUnits; ++i)
        m.at(w.units[i] + 162)[0] = static_cast<u8>(chance(rng, 95) ? (i < 4 ? 0 : 1) : rng());
    for (u32 side = 0; side < 2; ++side) {
        std::vector<u32> mine;
        for (u32 u : w.units)
            if (m.at(u + 162)[0] == side) mine.push_back(u);
        std::shuffle(mine.begin(), mine.end(), rng);
        const u32 n = mine.empty() || chance(rng, 10) ? 0u : 1 + rng() % static_cast<u32>(mine.size());
        store32(m, kG + bc::kSideListB + 8 * side, n ? mine[0] : 0u);
        for (u32 i = 0; i < mine.size(); ++i) store32(m, mine[i] + bc::kUnitNextB, i + 1 < n ? mine[i + 1] : 0u);
    }
    for (u32 i = 0; i < kNumUnits; ++i) {
        const u32 u = w.units[i];
        store32(m, u + 156, chance(rng, 70) ? (rng() & ~1u) : rng());
        store16(m, u + bc::kUnitModelId, static_cast<u16>(chance(rng, 20) ? 0u : rng()));
    }
    for (u32 i = 0; i < kNumActions; ++i) {
        const u32 a = w.actions[i];
        store32(m, a + 48, w.units[chance(rng, 80) ? i : rng() % kNumUnits]);
        store16(m, a + bc::kActTargetCount, static_cast<u16>(chance(rng, 90) ? rng() % 5 : rng()));
        for (u32 k = 0; k < 12; ++k) store32(m, a + bc::kActTargets + 4 * k, w.actions[rng() % kNumActions]);
    }
    return w;
}

// --- the register file at a check point / the return / a stop ----------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0;
    std::array<u32, 32> fpr{};
    std::array<u32, 1> acc{};
};
Snap snap(const EEContext& c) {
    Snap s;
    s.cycles = c.cycles;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = c.gpr[r];
    s.hi = c.hi;
    s.lo = c.lo;
    s.sa = c.sa;
    s.fcr31 = c.fcr31;
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    std::memcpy(s.acc.data(), &c.acc, 4);
    return s;
}
// The first difference (empty when equal): "gpr N", "hi", "lo", "sa/fcr31", "fpr", "acc", "cycles".
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa || a.fcr31 != b.fcr31) return "sa/fcr31";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.acc != b.acc) return "acc";
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds), with a
// cycle budget (a random world can make a queue or list walk circular; both bodies stop at the same check point).
constexpr u64 kBudget = 50'000'000;
constexpr std::size_t kMaxSnaps = 100'000;  // check points kept (all are counted)
class CamHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    Snap at_stop;
    int syscalls = 0;
    u64 limit = 0;
    std::size_t checks = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        if (snaps.size() < kMaxSnaps) snaps.push_back(snap(ctx));
        if (ctx.cycles > limit) fatal(ctx, 0xB0D6E7u, "cycle budget");
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* msg) override {
        if (std::getenv("P3FES_BCAM_TRACE")) std::fprintf(stderr, "  fatal %08x %s (ra %08x)\n", pc, msg, ctx.gpr[31].u32[0]);
        stopped = true;
        stop_pc = pc;
        what = msg;
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, msg, &ctx};
    }
};

// The inputs of a call: GPRs $a0..$a3, $t0..$t3 and the float argument registers $f12..$f15 (set after the random
// register file).
struct Inputs {
    std::map<unsigned, u64> gpr;
    std::map<unsigned, u32> fpr;
};

struct Run {
    std::size_t checks = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
};

Run run_one(Machine& m, Fn fn, const Inputs& in, u32 seed) {
    CamHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(Args{}, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
    for (const auto& [r, v] : in.gpr) m.ctx.gpr[r].u64[0] = v;
    for (const auto& [f, v] : in.fpr) m.ctx.fpr[f] = v;
    h.limit = m.ctx.cycles + kBudget;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.checks = h.checks;
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;         // missing function -> count
    std::map<std::string, int> faults;  // other stops by message (up to the address)
    std::map<u64, int> results;         // $v0 at the return (up to 8 distinct values)
};
std::map<std::string, Stats> g_stats;

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled
// run. The whole 32 MiB of main RAM is compared through a PairRange (write_tracker.h): only the pages a body writes are
// copied and compared, so every byte of RAM is checked on every pair.
int g_pair_count = 0;

Run pair(Machine& m, Fn hand, Fn recomp, const Inputs& in, u32 seed, const char* what) {
    ++g_pair_count;
    std::size_t first = 0;
    Run h, r;
    {
        PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        h = run_one(m, hand, in, seed);
        ram.between();
        r = run_one(m, recomp, in, seed);
        first = ram.first_difference();
    }
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
        if (r.what.rfind("missing_function", 0) != 0) ++st.faults[r.what.substr(0, r.what.find(" at virtual"))];
    } else if (st.results.size() < 8 || st.results.count(r.end.gpr[GPR_V0].u64[0])) {
        ++st.results[r.end.gpr[GPR_V0].u64[0]];
    }
    const std::string name(what);
    INFO(name << " seed=" << seed);
    CHECK(h.stopped == r.stopped);
    if (h.stopped != r.stopped) return r;  // (the rest compares like with like only)
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.checks == r.checks);
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << " (ra " << hex64(r.snaps[i].gpr[31].u32[0]) << "): " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(h.end, r.end);
        const std::string where = r.stopped ? "at the stop: " : "at the return: ";
        INFO(where << d);
        CHECK(d.empty());
    }
    INFO("main RAM: first differing byte at " << hex64(first));
    CHECK(first == EEMemory::kMainRamSize);
    return r;
}

// --- the argument kinds ----------------------------------------------------------------------------------------------
// A data block / camera object in the world (16-byte aligned, filled with floats and pointers).
u32 some_data(std::mt19937& rng) { return kData + ((rng() % (kDataSize - 0x400u)) & ~0xFu); }
u32 some_rgba(std::mt19937& rng) { return chance(rng, 50) ? rng() : (rng() & 0xFFFFFFu) | 0x80000000u; }
// Fills `len` bytes at va with floats in [lo, hi) (camera vectors, colours, interpolation keys).
void fill_floats(Machine& m, std::mt19937& rng, u32 va, u32 len, float lo, float hi) {
    for (u32 off = 0; off < len; off += 4) storef(m, va + off, frand(rng, lo, hi));
}

using Gen = std::function<Inputs(Machine&, const World&, std::mt19937&)>;
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Gen gen;
};

#define PAIR(name, addr) &recomp_gen::fn_##name##_##addr, &recomp_gen::fn_##name##_##addr##__recomp

// The packet creators: five arguments of every kind.
Inputs gen_creator(Machine&, const World& w, std::mt19937& rng) {
    Inputs in;
    for (unsigned r = GPR_A0; r <= GPR_T3; ++r) {
        const u32 k = rng() % 4;
        in.gpr[r] = wide(rng, k == 0 ? some_rgba(rng) : k == 1 ? rng() % 64 : k == 2 ? w.actions[rng() % kNumActions] : rng());
    }
    return in;
}
// A screen-fade callback's data block: the frame counter below / at / above the frame count.
Inputs gen_fade_data(Machine& m, const World&, std::mt19937& rng, u32 frames_off, u32 frame_off) {
    Inputs in;
    const u32 d = some_data(rng);
    fill_floats(m, rng, d, 64, 0.0f, 1.0f);
    const u32 frames = chance(rng, 10) ? 0x80000000u + rng() % 16 : rng() % 60;
    store32(m, d + frames_off, frames);
    store32(m, d + frame_off, chance(rng, 20) ? 0u : chance(rng, 10) ? 0x80000000u + rng() % 8 : rng() % 64);
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}
// The unit fade callbacks: data +0 an action (sub_2A1710) / frames.
Inputs gen_unit_fade(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    const u32 d = some_data(rng);
    store32(m, d + 0, w.actions[rng() % kNumActions]);
    store32(m, d + 4, chance(rng, 10) ? 0x80000000u + rng() % 16 : rng() % 40);
    store32(m, d + 8, chance(rng, 20) ? 0u : rng() % 50);
    store16(m, d + 12, static_cast<u16>(rng() % kNumSkills));
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}
Inputs gen_unit_fade_in(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    const u32 d = some_data(rng);
    store32(m, d + 0, chance(rng, 10) ? 0x80000000u + rng() % 16 : rng() % 40);
    store32(m, d + 4, chance(rng, 20) ? 0u : rng() % 50);
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}

// The camera work record gBtl+32: the camera table's init / update functions (0x6939F0 rows) take it in $a0. +224 the
// subject btlAction (or 0); the rest floats and pointers. $f12..$f15 floats. Mostly the record, sometimes any block.
constexpr u32 kCamWork = kG + 32;
Inputs gen_cam_state(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    const u32 rec = chance(rng, 85) ? kCamWork : some_data(rng);
    if (chance(rng, 50)) fill_floats(m, rng, rec, 0x200, -100.0f, 100.0f);
    store32(m, rec + 224, chance(rng, 15) ? 0u : w.actions[rng() % kNumActions]);
    in.gpr[GPR_A0] = wide(rng, rec);
    in.gpr[GPR_A1] = wide(rng, chance(rng, 50) ? some_data(rng) : rng() % 64);
    in.gpr[GPR_A2] = wide(rng, chance(rng, 50) ? some_data(rng) : rng() % 64);
    in.gpr[GPR_A3] = wide(rng, rng() % 0x100);
    for (unsigned f = 12; f < 16; ++f) in.fpr[f] = fbits(frand(rng, -2.0f, 2.0f));
    return in;
}

std::string report() {
    int pairs = 0, stops = 0;
    std::string detail;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        detail += "\n  " + name + ": " + std::to_string(st.pairs) + " pairs, " + std::to_string(st.pairs - st.stops) + " returned";
        if (!st.results.empty()) {
            detail += " (v0";
            for (const auto& [v, n] : st.results) detail += " " + hex64(v) + "x" + std::to_string(n);
            detail += ")";
        }
        for (const auto& [pc, n] : st.stop_at) detail += ", " + std::to_string(n) + " at " + hex64(pc);
        for (const auto& [msg, n] : st.faults) detail += "\n    " + std::to_string(n) + " x " + msg;
    }
    return std::to_string(pairs) + " pairs, " + std::to_string(stops) + " ended at a compared stop:" + detail;
}

// Runs every spec once per random world (each body from the same fresh world) and reports the stats.
inline void run_specs(Machine& m, const std::vector<Spec>& specs, int worlds, u32 seed, const char* slice) {
    std::mt19937 rng{seed};
    g_stats.clear();
    for (int it = 0; it < worlds; ++it) {
        const World w = random_world(m, rng);
        std::vector<std::vector<u8>> fresh;
        for (const Window& win : kFresh) fresh.push_back(m.bytes(win.va, win.len));
        for (const Spec& s : specs) {
            for (std::size_t i = 0; i < std::size(kFresh); ++i) std::memcpy(m.at(kFresh[i].va), fresh[i].data(), kFresh[i].len);
            const Inputs in = s.gen(m, w, rng);
            if (std::getenv("P3FES_BCAM_TRACE")) std::fprintf(stderr, "%d %s\n", it, s.name);
            pair(m, s.hand, s.recomp, in, rng(), s.name);
        }
    }
    MESSAGE(std::string(slice) << ": " << specs.size() << " functions; " << report());
    CHECK(g_stats.size() == specs.size());
}

}  // namespace

}  // namespace p3fes::game_test::bcam_test

#endif  // P3FES_GAME_HAVE_GENERATED
