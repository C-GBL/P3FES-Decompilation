// Phase 5 pair tests for the fx_layers slice (game/src/fx/fx_layers.cpp): the after effects (trail rings, Bezier
// handles, trail geometry, trail scripts, the live list) and the effect manager (keyframe tracks, layer lists,
// sprite players, image sequences, effect meshes, placement matrices). Each hand-written function and the recompiled
// body it replaces run on identical guest machines, and EVERYTHING observable is compared:
//   * the whole register file (GPRs in 128 bits, HI/LO, SA, the FPRs, ACC, FCR31) and the cycle count at every check
//     point -- the function's own and those of the callees it reaches -- and at the return;
//   * guest memory: 0x600000..0x2000000 (.data/.bss with the layer tables 0x9572xx..0x957Axx, the gp words and the
//     live list; the heap; the test arena 0x1800000..; the stack with frames, spills and the dead stack), the whole
//     of main RAM for the cases on a snapshot's memory -- through PairRange (write_tracker.h), page-exact;
//   * the bus log length, syscall and trap counts.
// Callees kept recompiled but not emitted in this test build (the effect drawers, the program steps, image loading)
// end the run through rt::missing_function: the hooks snapshot the register file and memory AT that call, so both
// bodies must reach the same callee with the same state. FPRs, ACC, HI/LO and the upper GPR halves start random.
// Real game data: the battle snapshots holding a live after effect (extracted/_ours/bx_n4700, s_ref; skipped when
// absent) run the per-frame update for a dozen frames, the recompiled run's output carried into the next frame; the
// heap-backed mesh builders run on a snapshot's heap. Documented-rule checks restate fx_layers.h on the host.
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/game/fx_layers.h"

#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
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
P3FES_DECL_PAIR(fn_sub_1E8330_001e8330)
P3FES_DECL_PAIR(fn_sub_1E8360_001e8360)
P3FES_DECL_PAIR(fn_sub_1E88F0_001e88f0)
P3FES_DECL_PAIR(fn_sub_1E8E80_001e8e80)
P3FES_DECL_PAIR(fn_sub_1E9AF0_001e9af0)
P3FES_DECL_PAIR(fn_sub_1EB920_001eb920)
P3FES_DECL_PAIR(fn_sub_1EBA50_001eba50)
P3FES_DECL_PAIR(fn_sub_1EBA80_001eba80)
P3FES_DECL_PAIR(fn_sub_1EBD80_001ebd80)
P3FES_DECL_PAIR(fn_sub_1ECD90_001ecd90)
P3FES_DECL_PAIR(fn_sub_1ECEC0_001ecec0)
P3FES_DECL_PAIR(fn_sub_1ED080_001ed080)
P3FES_DECL_PAIR(fn_sub_1ED0B0_001ed0b0)
P3FES_DECL_PAIR(fn_sub_1ED0D0_001ed0d0)
P3FES_DECL_PAIR(fn_sub_1ED0F0_001ed0f0)
P3FES_DECL_PAIR(fn_sub_1ED8A0_001ed8a0)
P3FES_DECL_PAIR(fn_sub_1ED9E0_001ed9e0)
P3FES_DECL_PAIR(fn_sub_1EDA00_001eda00)
P3FES_DECL_PAIR(fn_sub_1EDA90_001eda90)
P3FES_DECL_PAIR(fn_sub_1EDBE0_001edbe0)
P3FES_DECL_PAIR(fn_sub_1EDED0_001eded0)
P3FES_DECL_PAIR(fn_sub_1EE1D0_001ee1d0)
P3FES_DECL_PAIR(fn_nullsub_10_001ee220)
P3FES_DECL_PAIR(fn_sub_1EE230_001ee230)
P3FES_DECL_PAIR(fn_sub_1EEE40_001eee40)
P3FES_DECL_PAIR(fn_sub_1EEFC0_001eefc0)
P3FES_DECL_PAIR(fn_sub_1EF000_001ef000)
P3FES_DECL_PAIR(fn_sub_320060_00320060)
P3FES_DECL_PAIR(fn_nullsub_106_00320070)
P3FES_DECL_PAIR(fn_sub_320080_00320080)
P3FES_DECL_PAIR(fn_sub_320380_00320380)
P3FES_DECL_PAIR(fn_sub_3204A0_003204a0)
P3FES_DECL_PAIR(fn_sub_320640_00320640)
P3FES_DECL_PAIR(fn_sub_320770_00320770)
P3FES_DECL_PAIR(fn_sub_320810_00320810)
P3FES_DECL_PAIR(fn_sub_320BA0_00320ba0)
P3FES_DECL_PAIR(fn_sub_320CF0_00320cf0)
P3FES_DECL_PAIR(fn_sub_320DA0_00320da0)
P3FES_DECL_PAIR(fn_sub_320DE0_00320de0)
P3FES_DECL_PAIR(fn_sub_320F70_00320f70)
P3FES_DECL_PAIR(fn_sub_321050_00321050)
P3FES_DECL_PAIR(fn_sub_321070_00321070)
P3FES_DECL_PAIR(fn_sub_3210A0_003210a0)
P3FES_DECL_PAIR(fn_sub_3210C0_003210c0)
P3FES_DECL_PAIR(fn_sub_321120_00321120)
P3FES_DECL_PAIR(fn_sub_321130_00321130)
P3FES_DECL_PAIR(fn_sub_321140_00321140)
P3FES_DECL_PAIR(fn_sub_321180_00321180)
P3FES_DECL_PAIR(fn_sub_3211D0_003211d0)
P3FES_DECL_PAIR(fn_sub_321220_00321220)
P3FES_DECL_PAIR(fn_sub_321260_00321260)
P3FES_DECL_PAIR(fn_sub_3212A0_003212a0)
P3FES_DECL_PAIR(fn_sub_3212E0_003212e0)
P3FES_DECL_PAIR(fn_sub_321320_00321320)
P3FES_DECL_PAIR(fn_effMng_UpdateEffectProgramTask_00321a60)
P3FES_DECL_PAIR(fn_effMng_UpdateEffect3dTask_00321cb0)
P3FES_DECL_PAIR(fn_effMng_UpdateEffect2dTask_00321e20)
P3FES_DECL_PAIR(fn_sub_321F10_00321f10)
P3FES_DECL_PAIR(fn_sub_321FE0_00321fe0)
P3FES_DECL_PAIR(fn_sub_3226B0_003226b0)
P3FES_DECL_PAIR(fn_sub_322AB0_00322ab0)
P3FES_DECL_PAIR(fn_sub_322D10_00322d10)
P3FES_DECL_PAIR(fn_sub_322D40_00322d40)
P3FES_DECL_PAIR(fn_sub_322DA0_00322da0)
P3FES_DECL_PAIR(fn_sub_322FB0_00322fb0)
P3FES_DECL_PAIR(fn_sub_322FD0_00322fd0)
P3FES_DECL_PAIR(fn_sub_323240_00323240)
P3FES_DECL_PAIR(fn_sub_3233A0_003233a0)
P3FES_DECL_PAIR(fn_sub_323640_00323640)
P3FES_DECL_PAIR(fn_sub_323860_00323860)
P3FES_DECL_PAIR(fn_sub_323880_00323880)
P3FES_DECL_PAIR(fn_sub_3238D0_003238d0)
P3FES_DECL_PAIR(fn_sub_323920_00323920)
P3FES_DECL_PAIR(fn_sub_323A30_00323a30)
P3FES_DECL_PAIR(fn_sub_323B90_00323b90)
P3FES_DECL_PAIR(fn_sub_323BF0_00323bf0)
P3FES_DECL_PAIR(fn_sub_323E10_00323e10)
P3FES_DECL_PAIR(fn_sub_323FB0_00323fb0)
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

// --- the whole register file -----------------------------------------------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0, acc = 0;
    std::array<u32, 32> fpr{};
};
Snap snap(const EEContext& c) {
    Snap s;
    s.cycles = c.cycles;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = c.gpr[r];
    s.hi = c.hi;
    s.lo = c.lo;
    s.sa = c.sa;
    s.fcr31 = c.fcr31;
    s.acc = c.acc;
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    return s;
}
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "GPR " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) +
                   " recomp " + hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "HI";
    if (!same_u128(a.lo, b.lo)) return "LO";
    if (a.sa != b.sa) return "SA";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "FPR " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.fcr31 != b.fcr31) return "FCR31: hand " + hex64(a.fcr31) + " recomp " + hex64(b.fcr31);
    if (a.acc != b.acc) return "ACC";
    if (a.cycles != b.cycles) return "cycles: hand " + std::to_string(a.cycles) + " recomp " + std::to_string(b.cycles);
    return "";
}

// --- the compared guest memory ---------------------------------------------------------------------------------------
// One guest window per pair, compared and restored through a PairRange (write_tracker.h: only the pages written are
// copied): .data/.bss, the heap, the test arena and the stack for the synthetic cases (0x600000..0x2000000), the
// whole of main RAM for the cases on a snapshot's memory.
using Ranges = GuestRange;
const Ranges kSynth = {0x00600000u, EEMemory::kMainRamSize - 0x00600000u};
const Ranges kWhole = {0x00000000u, EEMemory::kMainRamSize};

class FullHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    std::vector<Snap> snaps;
    int syscalls = 0, traps = 0;
    u32 stop_pc = 0;
    std::string stop_what;
    Snap at_stop{};

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        if (snaps.size() >= 400000) fatal(ctx, 0, "runaway: 400000 check points");  // a fixture that loops for ever
        snaps.push_back(snap(ctx));
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stop_pc = pc;
        stop_what = what ? what : "";
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
    void vu_control_write(EEContext&, u32, u32) override {}
};

struct Run {
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string stop_what;
    Snap end{};
    std::size_t bus = 0;
    int syscalls = 0, traps = 0;
    u64 v0() const { return end.gpr[GPR_V0].u64[0]; }
    float f0() const { return std::bit_cast<float>(end.fpr[0]); }
};

using Prep = std::function<void(EEContext&)>;

u32 rand_float(std::mt19937& rng);

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const Prep& prep) {
    FullHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rand_float(rng);
    m.ctx.acc = rand_float(rng);
    m.ctx.fcr31 = rng() & 0x0083F07Fu;
    for (int i = 0; i < 2; ++i) {
        m.ctx.hi.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
        m.ctx.lo.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
    }
    if (prep) prep(m.ctx);
    Run r;
    try {
        fn(m.ctx);
        r.end = snap(m.ctx);
    } catch (const rt_test::FatalEvent&) {
        r.stopped = true;
        r.stop_pc = h.stop_pc;
        r.stop_what = h.stop_what;
        r.end = h.at_stop;
    }
    r.snaps = std::move(h.snaps);
    r.bus = h.bus_.log.size();
    r.syscalls = h.syscalls;
    r.traps = h.traps;
    return r;
}

struct PairOut {
    Run hand, recomp;
};

int g_pairs = 0, g_stops = 0;
std::map<std::string, int> g_stop_kinds;  // "<case>: <first words of the stop>" -> count

// The pair: snapshot the ranges, run the hand version, restore, run the recompiled body, compare everything. After
// the pair the recompiled run's memory is in place.
PairOut pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const std::string& what, const Prep& prep = {},
             const Ranges& rs = kSynth) {
    PairOut p;
    std::size_t first = 0;
    {
        PairRange range(m.at(rs.va), m.at(rs.va) + rs.len);
        p.hand = run_one(m, hand, args, seed, prep);
        range.between();
        p.recomp = run_one(m, recomp, args, seed, prep);
        first = range.first_difference();
    }
    ++g_pairs;
    if (p.recomp.stopped) {
        ++g_stops;
        std::string w = p.recomp.stop_what.substr(0, p.recomp.stop_what.find(';'));
        w = w.substr(0, w.find(" at virtual"));  // faults grouped by kind, not by address
        ++g_stop_kinds[what.substr(0, what.find(' ')) + ": " + w.substr(0, 90)];
    }
    INFO(what << " seed " << seed);
    CHECK(p.hand.stopped == p.recomp.stopped);
    CHECK(p.hand.stop_pc == p.recomp.stop_pc);
    if (p.hand.stopped != p.recomp.stopped || p.hand.stop_pc != p.recomp.stop_pc)
        MESSAGE("stops: hand " << p.hand.stop_what << " / recomp " << p.recomp.stop_what);
    CHECK(p.hand.snaps.size() == p.recomp.snaps.size());
    const std::size_t n = std::min(p.hand.snaps.size(), p.recomp.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(p.hand.snaps[i], p.recomp.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(p.hand.end, p.recomp.end);
        INFO("at the return / stop: " << d);
        CHECK(d.empty());
    }
    {
        INFO("memory: first differing byte at " << hex64(rs.va + first));
        CHECK(first == rs.len);
    }
    CHECK(p.hand.bus == p.recomp.bus);
    CHECK(p.hand.syscalls == p.recomp.syscalls);
    CHECK(p.hand.traps == p.recomp.traps);
    return p;
}

// --- guest RAM helpers and random data ---------------------------------------------------------------------------------
void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void putf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 get16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
float getf(const Machine& m, u32 va) { return std::bit_cast<float>(get32(m, va)); }
void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void zero(Machine& m, u32 va, u32 len) { std::memset(m.at(va), 0, len); }
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 12) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng() & 0xBF7FFFFFu;
    case 3: return 0x3F800000u;
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 4001) - 2000) / 97.0f);
    }
}
float rf(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100001) / 100000.0f; }
void fill_floats(Machine& m, u32 va, u32 count, std::mt19937& rng) {
    for (u32 i = 0; i < count; ++i) put32(m, va + 4 * i, rand_float(rng));
}
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
u64 arg64(std::mt19937& rng, u32 low) { return rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | low : sx(low); }
Prep floats(std::initializer_list<u32> f) {
    std::vector<u32> v(f);
    return [v](EEContext& c) {
        for (std::size_t i = 0; i < v.size(); ++i) c.fpr[12 + i] = v[i];
    };
}
Prep regs(std::initializer_list<std::pair<unsigned, u64>> r) {
    std::vector<std::pair<unsigned, u64>> v(r);
    return [v](EEContext& c) {
        for (auto [i, x] : v) c.gpr[i].u64[0] = x;
    };
}

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

constexpr u32 gpv(s32 off) { return kGp + static_cast<u32>(off); }
constexpr u32 kAeHead = gpv(-18980), kAeTail = gpv(-18984), kBank = gpv(-25288);

// =====================================================================================================================
// Fixtures: an after-effect trail ring and its geometry (fx_layers.h has the layouts)
// =====================================================================================================================
constexpr u32 kRing = 0x01800000u, kDesc = 0x01800100u, kParams = 0x01800200u, kKeys = 0x01800300u;
constexpr u32 kRail0 = 0x01801000u, kRail1 = 0x01801400u;
constexpr u32 kH24 = 0x01801800u, kH28 = 0x01801C00u, kH32 = 0x01802000u, kH36 = 0x01802400u;
constexpr u32 kGeomSlot = 0x01802F00u, kGeom = 0x01803000u, kMorph = 0x01803200u;
constexpr u32 kTris = 0x01804000u, kPrelit = 0x01805000u, kUv = 0x01806000u, kVerts = 0x01807000u;
constexpr u32 kOut = 0x0180A000u;

struct RingSpec {
    s32 capacity = 8, count = 8, head = 0, n = 6;
    s16 shape = 0;
    bool textured = false;
};

// A ring with random rail points (a smooth path with noise), handles, curve parameters and colour keys.
void make_ring(Machine& m, std::mt19937& rng, const RingSpec& s) {
    zero(m, kRing, 0x100);
    put32(m, kRing + 0, kDesc);
    put32(m, kRing + 4, rng() & 0x3u);
    put32(m, kRing + 8, static_cast<u32>(s.count));
    put32(m, kRing + 12, static_cast<u32>(s.head));
    put32(m, kRing + 16, kRail0);
    put32(m, kRing + 20, kRail1);
    put32(m, kRing + 24, kH24);
    put32(m, kRing + 28, kH28);
    put32(m, kRing + 32, kH32);
    put32(m, kRing + 36, kH36);
    putf(m, kRing + 60, rf(rng, 0, 50));
    putf(m, kRing + 64, rf(rng, 0, 50));
    putf(m, kRing + 68, chance(rng, 15) ? 0.0f : rf(rng, -5, 30));
    put16(m, kRing + 72, static_cast<u16>(s.shape));
    zero(m, kDesc, 0x40);
    put32(m, kDesc + 0, kParams);
    put32(m, kDesc + 4, kKeys);
    put32(m, kDesc + 8, static_cast<u32>(s.capacity));
    put32(m, kDesc + 12, static_cast<u32>(s.n));
    putf(m, kDesc + 20, rf(rng, 0.5f, 20));
    for (u32 i = 0; i < 11; ++i) putf(m, kParams + 4 * i, chance(rng, 10) ? 0.0f : rf(rng, -1.5f, 2.0f));
    fill(m, kKeys, 0x40, rng);
    put32(m, kKeys, (rng() & ~1u) | (s.textured ? 1u : 0u));
    // the rails: a wandering path, rail 1 offset from rail 0
    float x = rf(rng, -50, 50), y = rf(rng, -50, 50), z = rf(rng, -50, 50);
    const u32 cap = static_cast<u32>(std::max(s.capacity, 1));
    for (u32 i = 0; i < cap + 2; ++i) {
        x += rf(rng, -3, 3);
        y += rf(rng, -3, 3);
        z += rf(rng, -3, 3);
        const bool dup = chance(rng, 3) && i > 0;  // a repeated point: zero-length segments
        if (!dup) {
            putf(m, kRail0 + 12 * i + 0, x);
            putf(m, kRail0 + 12 * i + 4, y);
            putf(m, kRail0 + 12 * i + 8, z);
            putf(m, kRail1 + 12 * i + 0, x + rf(rng, -2, 2));
            putf(m, kRail1 + 12 * i + 4, y + rf(rng, 0.5f, 4));
            putf(m, kRail1 + 12 * i + 8, z + rf(rng, -2, 2));
        } else {
            std::memcpy(m.at(kRail0 + 12 * i), m.at(kRail0 + 12 * (i - 1)), 12);
            std::memcpy(m.at(kRail1 + 12 * i), m.at(kRail1 + 12 * (i - 1)), 12);
        }
    }
    for (u32 h : {kH24, kH28, kH32, kH36})
        for (u32 i = 0; i < 3 * (cap + 2); ++i) putf(m, h + 4 * i, rf(rng, -2, 2));
}

// A trail geometry for the ring (sub_1E9AF0 / sub_1ED8A0): mesh header present (the lock / unlock fast paths).
void make_geometry(Machine& m, std::mt19937& rng, u32 vertices) {
    zero(m, kGeom, 0x100);
    put16(m, kGeom + 12, static_cast<u16>(rng() & 0xF0u));
    put32(m, kGeom + 16, 0);
    put32(m, kGeom + 20, vertices);
    put32(m, kGeom + 44, kTris);
    put32(m, kGeom + 48, kPrelit);
    put32(m, kGeom + 52, kUv);
    put32(m, kGeom + 84, 0x01803400u);  // the mesh header (instanced)
    put32(m, kGeom + 92, kMorph);
    zero(m, kMorph, 0x40);
    put32(m, kMorph + 20, kVerts);
    put32(m, kGeomSlot, kGeom);
    fill(m, kPrelit, 0x1000, rng);
    fill(m, kVerts, 0x2000, rng);
    fill(m, kUv, 0x1000, rng);
}

// =====================================================================================================================
// After effects: the ring math
// =====================================================================================================================

TEST_CASE("game(fx_layers): sub_1E8330 the ring slot of the k-th newest sample") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 300; ++i) {
        const u32 seed = seed_of(i, 0x1E8330u);
        std::mt19937 rng{seed};
        const s32 cap = static_cast<s32>(rng() % 40) - (chance(rng, 5) ? 3 : 0);
        put32(m, kRing + 8, static_cast<u32>(cap));
        put32(m, kRing + 12, rng() % 45);
        const s32 k = static_cast<s32>(rng() % 50) - 5;
        const PairOut p = pair(m, PAIR(fn_sub_1E8330_001e8330), {sx(kRing), arg64(rng, static_cast<u32>(k)), 0, 0}, seed,
                               "sub_1E8330");
        // the documented rule: (head - 1 - k), wrapped once by the capacity
        s32 e = static_cast<s32>(get32(m, kRing + 12)) - 1 - k;
        if (e < 0) e += cap;
        if (!p.recomp.stopped) CHECK(static_cast<s32>(p.recomp.v0()) == e);
    }
}

TEST_CASE("game(fx_layers): sub_1E88F0 / sub_1E8360 / sub_1ECD90 / sub_1ECEC0 the trail's frame vectors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    int checked = 0;
    for (int i = 0; i < 160; ++i) {
        const u32 seed = seed_of(i, 0x1E88F0u);
        std::mt19937 rng{seed};
        RingSpec s;
        s.capacity = 2 + static_cast<s32>(rng() % 20);
        s.count = chance(rng, 10) ? static_cast<s32>(rng() % 2) : 2 + static_cast<s32>(rng() % (s.capacity - 1));
        s.head = static_cast<s32>(rng() % s.capacity);
        make_ring(m, rng, s);
        const s32 sample = static_cast<s32>(rng() % std::max(s.count, 1)) - (chance(rng, 5) ? 1 : 0);
        const s32 side = static_cast<s32>(rng() % 3);
        pair(m, PAIR(fn_sub_1E88F0_001e88f0), {sx(kRing), sx(static_cast<u32>(sample)), sx(kOut), 0}, seed, "sub_1E88F0");
        pair(m, PAIR(fn_sub_1E8360_001e8360), {sx(kRing), sx(static_cast<u32>(sample)), sx(static_cast<u32>(side)), sx(kOut + 64)},
             seed, "sub_1E8360");
        const s32 rail = static_cast<s32>(rng() % 2);
        const PairOut l = pair(m, PAIR(fn_sub_1ECD90_001ecd90), {sx(kRing), sx(static_cast<u32>(sample)), sx(static_cast<u32>(rail)), 0},
                               seed, "sub_1ECD90");
        pair(m, PAIR(fn_sub_1ECEC0_001ecec0), {sx(kRing), sx(static_cast<u32>(sample)), 0, 0}, seed, "sub_1ECEC0");
        // documented rule: the segment length is |p[sample + 1] - p[sample]| on the rail (host model, loose tolerance)
        if (!l.recomp.stopped && s.count >= 2 && sample >= 0 && sample < s.count - 1) {
            const u32 cap = static_cast<u32>(s.count);
            auto slot = [&](s32 k) { s32 e = s.head - 1 - k; if (e < 0) e += static_cast<s32>(cap); return static_cast<u32>(e); };
            const u32 base = rail ? kRail1 : kRail0;
            const u32 a = base + 12 * slot(sample), b = base + 12 * slot(sample + 1);
            const float dx = getf(m, a) - getf(m, b), dy = getf(m, a + 4) - getf(m, b + 4), dz = getf(m, a + 8) - getf(m, b + 8);
            const float len = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (std::isfinite(len) && len < 1e6f) {
                CHECK(std::fabs(l.recomp.f0() - len) <= 1e-2f * (1.0f + len));
                ++checked;
            }
        }
    }
    CHECK(checked > 20);
}

TEST_CASE("game(fx_layers): sub_1EB920 / sub_1EBD80 pushing samples and building the Bezier handles") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 120; ++i) {
        const u32 seed = seed_of(i, 0x1EB920u);
        std::mt19937 rng{seed};
        RingSpec s;
        s.capacity = 2 + static_cast<s32>(rng() % 12);
        s.count = static_cast<s32>(rng() % (s.capacity + 1));
        s.head = static_cast<s32>(rng() % s.capacity);
        make_ring(m, rng, s);
        fill_floats(m, kOut, 6, rng);
        // a run of pushes, the recompiled result carried on (counts 0, 1, 2, 3.. up to the capacity)
        for (int k = 0; k < 4; ++k)
            pair(m, PAIR(fn_sub_1EB920_001eb920), {sx(kRing), sx(kOut), sx(kOut + 12), 0}, seed + static_cast<u32>(k),
                 "sub_1EB920");
        if (s.count >= 2) {
            const s32 sample = static_cast<s32>(rng() % (s.count - 1));
            pair(m, PAIR(fn_sub_1EBD80_001ebd80), {sx(kRing), arg64(rng, static_cast<u32>(sample)), 0, 0}, seed, "sub_1EBD80");
        }
    }
    // a zero capacity: the count stays 0 (K_Assert line 1470, `div` by zero leaves HI/LO as the EE does)
    std::mt19937 rng{0x1470u};
    RingSpec z;
    z.capacity = 0;
    z.count = 0;
    make_ring(m, rng, z);
    pair(m, PAIR(fn_sub_1EB920_001eb920), {sx(kRing), sx(kOut), sx(kOut + 12), 0}, 7, "sub_1EB920 capacity 0");
}

TEST_CASE("game(fx_layers): sub_1ED0F0 key colours, fade, unsigned conversions; sub_1ED080 / 1ED0B0 / 1ED0D0 / 1ED9E0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    int faded = 0;
    for (int i = 0; i < 400; ++i) {
        const u32 seed = seed_of(i, 0x1ED0F0u);
        std::mt19937 rng{seed};
        RingSpec s;
        make_ring(m, rng, s);
        put32(m, kRing + 4, rng() & 1u);  // flag 1: fading
        const int mode = static_cast<int>(rng() % 6);
        if (mode == 0) putf(m, kRing + 68, 0.0f);                       // zero length
        if (mode == 1) putf(m, kRing + 68, -rf(rng, 0.1f, 5));         // negative length (keeps $f0)
        if (mode == 2) putf(m, kRing + 64, getf(m, kRing + 60) + 1);  // start after the clock
        const s32 key = static_cast<s32>(rng() % 3);
        const u32 t = chance(rng, 20) ? (chance(rng, 50) ? 0x3F800000u : 0u) : std::bit_cast<u32>(rf(rng, -0.2f, 1.2f));
        const PairOut p = pair(m, PAIR(fn_sub_1ED0F0_001ed0f0), {sx(kRing), arg64(rng, static_cast<u32>(key)), sx(kOut), 0}, seed,
                               "sub_1ED0F0", floats({t}));
        // documented rule (no fade, t in [0, 1]): channel = a * (1 - t) + b * t, truncated
        if (!(get32(m, kRing + 4) & 1u) && !p.recomp.stopped) {
            const float tf = std::bit_cast<float>(t);
            if (tf >= 0 && tf <= 1) {
                for (u32 c = 0; c < 4; ++c) {
                    const float a = m.at(kKeys + 8 * key + 8)[c], b = m.at(kKeys + 8 * key + 12)[c];
                    const float v = a * (1 - tf) + b * tf;
                    CHECK(std::fabs(static_cast<float>(m.at(kOut)[c]) - v) <= 1.01f);
                }
            }
        } else {
            ++faded;
        }
        pair(m, PAIR(fn_sub_1ED080_001ed080), {sx(kRing), 0, 0, 0}, seed, "sub_1ED080", floats({rand_float(rng)}));
        put32(m, kOut + 32, rand_float(rng));
        pair(m, PAIR(fn_sub_1ED0D0_001ed0d0), {sx(kRing), sx(kOut + 32), 0, 0}, seed, "sub_1ED0D0");
        pair(m, PAIR(fn_sub_1ED0B0_001ed0b0), {sx(kRing), 0, 0, 0}, seed, "sub_1ED0B0");
        put32(m, kOut + 64, kOut + 80);
        put16(m, kOut + 80, static_cast<u16>(chance(rng, 50) ? 0 : rng()));
        pair(m, PAIR(fn_sub_1ED9E0_001ed9e0), {sx(kOut + 60), 0, 0, 0}, seed, "sub_1ED9E0");
    }
    CHECK(faded > 50);
}

// =====================================================================================================================
// After effects: the trail geometry
// =====================================================================================================================

TEST_CASE("game(fx_layers): sub_1ED8A0 clearing and sub_1E9AF0 rebuilding a trail geometry, all shapes") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 150; ++i) {
        const u32 seed = seed_of(i, 0x1E9AF0u);
        std::mt19937 rng{seed};
        RingSpec s;
        s.n = 2 + static_cast<s32>(rng() % 6);
        s.capacity = 2 + static_cast<s32>(rng() % 10);
        s.count = chance(rng, 15) ? static_cast<s32>(rng() % 2) : 2 + static_cast<s32>(rng() % (s.capacity - 1));
        s.head = static_cast<s32>(rng() % s.capacity);
        s.shape = static_cast<s16>(chance(rng, 5) ? 3 : rng() % 3);
        s.textured = chance(rng, 50);
        make_ring(m, rng, s);
        const u32 nv = s.shape == 0 ? static_cast<u32>(2 * s.n + 2) : static_cast<u32>(3 * s.n + 6);
        make_geometry(m, rng, nv);
        put32(m, kRing + 4, rng() & 3u);
        pair(m, PAIR(fn_sub_1ED8A0_001ed8a0), {sx(kRing), sx(kGeom), 0, sx(nv)}, seed, "sub_1ED8A0");
        make_geometry(m, rng, nv);
        pair(m, PAIR(fn_sub_1E9AF0_001e9af0), {sx(kRing), sx(kGeomSlot), 0, 0}, seed, "sub_1E9AF0");
    }
}

TEST_CASE("game(fx_layers): sub_1E8E80 creating a trail geometry on a snapshot's heap") {
    int ran = 0;
    for (const char* dir : {"bx_n4700", "battle_ref_6150"}) {
        const std::vector<u8> snapmem = read_snapshot(dir);
        if (snapmem.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(dir) << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snapmem.data(), snapmem.size());
        for (int i = 0; i < 8; ++i) {
            const u32 seed = seed_of(i, 0x1E8E80u);
            std::mt19937 rng{seed};
            RingSpec s;
            s.n = 2 + static_cast<s32>(rng() % 5);
            s.shape = static_cast<s16>(i % 4);  // 3: an unknown shape (no triangles, colours or UVs written)
            s.textured = (i / 4) % 2 == 0;
            make_ring(m, rng, s);
            pair(m, PAIR(fn_sub_1E8E80_001e8e80), {sx(kRing), 0, 0, 0}, seed, std::string("sub_1E8E80 ") + dir, {}, kWhole);
            ++ran;
        }
    }
    MESSAGE("sub_1E8E80 snapshot pairs: " << ran);
}

// =====================================================================================================================
// After effects: the scripts and the live list
// =====================================================================================================================
constexpr u32 kState = 0x01808000u, kScript = 0x01808100u;

// A random script: opcodes with their operands, ending in 0x0000; operands placed at random alignments.
void make_script(Machine& m, std::mt19937& rng, u32 at) {
    u32 pc = at;
    const int n = 1 + static_cast<int>(rng() % 6);
    for (int k = 0; k < n; ++k) {
        switch (rng() % 9) {
        case 0: put16(m, pc, 1); put16(m, pc + 2, static_cast<u16>(rng() % 4)); put16(m, pc + 4, 0); pc += 6; break;
        case 1: put16(m, pc, 0x100); pc += 2; break;
        case 2: put16(m, pc, 0x101); pc += 2; break;
        case 3: put16(m, pc, 0x102); pc += 2; break;
        case 4: put16(m, pc, 0x200); pc += 2; break;
        case 5: put16(m, pc, 0x201); put16(m, pc + 2, static_cast<u16>(chance(rng, 50) ? 0 : rng())); pc += 4; break;
        case 6: put16(m, pc, 0x202); put16(m, pc + 2, static_cast<u16>(rng())); put16(m, pc + 4, static_cast<u16>(chance(rng, 50) ? 0 : rng())); pc += 6; break;
        case 7: put16(m, pc, 0x400); pc += 2; break;
        default: put16(m, pc, 1); put16(m, pc + 2, static_cast<u16>(rng() % 3)); put16(m, pc + 4, 0); pc += 6; break;
        }
    }
    put16(m, pc, 0);
}

TEST_CASE("game(fx_layers): sub_1EBA80 / sub_1EBA50 the trail scripts") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 300; ++i) {
        const u32 seed = seed_of(i, 0x1EBA80u);
        std::mt19937 rng{seed};
        RingSpec s;
        make_ring(m, rng, s);
        const u32 script = kScript + 2 * (rng() % 4);  // operands on and off word boundaries
        make_script(m, rng, script);
        zero(m, kState, 32);
        put32(m, kState + 0, rng() & 0xBu);
        put32(m, kState + 4, script);
        put32(m, kState + 8, script);
        put32(m, kState + 16, kRing);
        put32(m, kState + 20, rng() % 4);
        put16(m, kState + 24, static_cast<u16>(chance(rng, 60) ? 0 : rng()));
        put32(m, kState + 28, chance(rng, 30) ? 0u : (chance(rng, 20) ? 0x80000000u | rng() : rng() % 200));
        for (int k = 0; k < 4; ++k)  // run it frame after frame
            pair(m, PAIR(fn_sub_1EBA80_001eba80), {sx(kState), 0, 0, 0}, seed + static_cast<u32>(k), "sub_1EBA80");
        pair(m, PAIR(fn_sub_1EBA50_001eba50), {sx(kState), 0, 0, 0}, seed, "sub_1EBA50");
        CHECK(get32(m, kState + 4) == get32(m, kState + 8));  // restart: pc = start, flags = 0
        CHECK(get32(m, kState + 0) == 0u);
    }
}

// The live list: up to four after effects linked through +24 / +28 from gp-18980 / gp-18984.
constexpr u32 kEff = 0x01810000u;
u32 eff(int i) { return kEff + 0x200u * static_cast<u32>(i); }
int make_list(Machine& m, std::mt19937& rng) {
    const int n = static_cast<int>(rng() % 5);
    for (int i = 0; i < 5; ++i) {
        fill(m, eff(i), 0x40, rng);
        put32(m, eff(i), rng() & 0x1Fu);
    }
    for (int i = 0; i < n; ++i) {
        put32(m, eff(i) + 24, i > 0 ? eff(i - 1) : 0);
        put32(m, eff(i) + 28, i + 1 < n ? eff(i + 1) : 0);
    }
    put32(m, kAeHead, n ? eff(0) : 0);
    put32(m, kAeTail, n ? eff(n - 1) : 0);
    return n;
}

TEST_CASE("game(fx_layers): the live list -- sub_1EEFC0 / sub_1EF000 / sub_1EDED0 / sub_1EE230 / sub_1EE1D0 / sub_1EDA00") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 300; ++i) {
        const u32 seed = seed_of(i, 0x1EF000u);
        std::mt19937 rng{seed};
        const int n = make_list(m, rng);
        const int who = static_cast<int>(rng() % 5);  // a member (< n) or not
        const PairOut q = pair(m, PAIR(fn_sub_1EF000_001ef000), {sx(eff(who)), 0, 0, 0}, seed, "sub_1EF000");
        const bool live = who < n && !(get32(m, eff(who)) & 8u);
        CHECK(q.recomp.v0() == (live ? 1u : 0u));
        pair(m, PAIR(fn_sub_1EDED0_001eded0), {sx(eff(who)), 0, 0, 0}, seed, "sub_1EDED0");
        put32(m, kOut, chance(rng, 30) ? get32(m, eff(who) + 32) : rng());
        pair(m, PAIR(fn_sub_1EE230_001ee230), {sx(eff(who)), sx(kOut), 0, 0}, seed, "sub_1EE230");
        put32(m, eff(who) + 4, 0x01811000u);  // the descriptor (+32 the pack)
        put32(m, 0x01811000u + 32, 0x01812000u);
        pair(m, PAIR(fn_sub_1EE1D0_001ee1d0), {sx(eff(who)), 0, 0, 0}, seed, "sub_1EE1D0");
        make_list(m, rng);
        pair(m, PAIR(fn_sub_1EEFC0_001eefc0), {sx(eff(4)), 0, 0, 0}, seed, "sub_1EEFC0");
        CHECK(get32(m, kAeTail) == eff(4));
        // creation: flag 0x1400 set -> nothing (0), else the allocator (stops here when not emitted)
        const u32 flags = 0x83A21Cu + 4u * (5120u >> 5);
        put32(m, flags, chance(rng, 50) ? 0xFFFFFFFFu : 0u);
        pair(m, PAIR(fn_sub_1EDA00_001eda00), {sx(0x01812000u), sx(rng()), 0, 0}, seed, "sub_1EDA00");
        pair(m, PAIR(fn_nullsub_10_001ee220), {0, 0, 0, 0}, seed, "nullsub_10");
    }
}

// An after effect with trails: descriptor, rings, atomics / materials, script states, anchor pairs; a model with the
// frame step at +244 and the matrix flag at +216.
constexpr u32 kAe = 0x01820000u, kAeDesc = 0x01820100u, kAeRings = 0x01820200u, kAeAtoms = 0x01820400u;
constexpr u32 kAeStates = 0x01820500u, kAeAnchors = 0x01820600u, kAeModel = 0x01821000u, kAeScripts = 0x01822000u;
constexpr u32 kAeBones = 0x01823000u, kAeMats = 0x01823100u;
void make_effect(Machine& m, std::mt19937& rng, int trails) {
    zero(m, kAe, 0x40);
    put32(m, kAe + 0, rng() & 0x1Fu);
    put32(m, kAe + 4, kAeDesc);
    put32(m, kAe + 8, kAeRings);
    put32(m, kAe + 12, kAeAtoms);
    put32(m, kAe + 16, kAeStates);
    put32(m, kAe + 20, kAeAnchors);
    fill(m, kAe + 32, 4, rng);
    zero(m, kAeDesc, 0x40);
    put16(m, kAeDesc + 4, static_cast<u16>(trails));
    put32(m, kAeDesc + 24, kAeBones);
    put32(m, kAeDesc + 28, kAeScripts);
    put32(m, kAeDesc + 32, kAeModel);
    zero(m, kAeModel, 0x100);
    putf(m, kAeModel + 244, chance(rng, 25) ? 0.0f : rf(rng, 0.2f, 2.0f));
    put16(m, kAeModel + 216, static_cast<u16>(rng()));
    fill_floats(m, kAeModel + 144, 16, rng);
    put32(m, gpv(-32540), std::bit_cast<u32>(rf(rng, 0.5f, 2)));
    for (int t = 0; t < trails; ++t) {
        const u32 ring = kAeRings + 76u * static_cast<u32>(t);
        // each ring copies the shared fixture's shape (descriptor / rails / handles from make_ring)
        std::memcpy(m.at(ring), m.at(kRing), 76);
        put32(m, kAeAtoms + 8u * t, 0x01824000u + 0x40u * t);  // the atomic (+24 the geometry)
        put32(m, 0x01824000u + 0x40u * t + 24, kGeom);
        put32(m, kAeAtoms + 8u * t + 4, kAeMats + 16u * t);
        const u32 st = kAeStates + 32u * static_cast<u32>(t);
        fill(m, st, 32, rng);
        put32(m, st + 0, rng() & 0xBu);
        const u32 sc = kAeScripts + 0x40u * static_cast<u32>(t);
        make_script(m, rng, sc + 0x100);
        put32(m, kAeScripts + 4u * t, sc + 0x100);
        put32(m, st + 4, sc + 0x100);
        put32(m, st + 8, sc + 0x100);
        put32(m, st + 16, ring);
        fill_floats(m, kAeAnchors + 24u * t, 6, rng);
        put32(m, kAeBones + 8u * t, rng() % 4);
        put32(m, kAeBones + 8u * t + 4, rng() % 4);
    }
}

TEST_CASE("game(fx_layers): sub_1EEE40 / sub_1EDBE0 starting and updating a synthetic after effect") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 80; ++i) {
        const u32 seed = seed_of(i, 0x1EDBE0u);
        std::mt19937 rng{seed};
        RingSpec s;
        s.n = 2 + static_cast<s32>(rng() % 4);
        s.capacity = 2 + static_cast<s32>(rng() % 8);
        s.count = static_cast<s32>(rng() % (s.capacity + 1));
        s.head = static_cast<s32>(rng() % s.capacity);
        s.shape = static_cast<s16>(rng() % 2);
        make_ring(m, rng, s);
        const u32 nv = s.shape == 0 ? static_cast<u32>(2 * s.n + 2) : static_cast<u32>(3 * s.n + 6);
        make_geometry(m, rng, nv);
        const int trails = 1 + static_cast<int>(rng() % 2);
        make_effect(m, rng, trails);
        pair(m, PAIR(fn_sub_1EEE40_001eee40), {sx(kAe), 0, 0, 0}, seed, "sub_1EEE40");
        // local anchors (state flag 8) on some trails: no model matrices; the others reach sub_4C38C0 (heap)
        for (int t = 0; t < trails; ++t)
            if (chance(rng, 70)) put32(m, kAeStates + 32u * t, get32(m, kAeStates + 32u * t) | 0xAu);
        put32(m, kAe, get32(m, kAe) & ~8u);
        for (int k = 0; k < 3; ++k)
            pair(m, PAIR(fn_sub_1EDBE0_001edbe0), {sx(kAe), 0, 0, 0}, seed + static_cast<u32>(k), "sub_1EDBE0");
    }
}

// The real after effect of the battle snapshots: a dozen frames of the update (and the anchor pass), the recompiled
// run's memory carried into the next frame, the whole of main RAM compared.
TEST_CASE("game(fx_layers): the live after effect of the battle snapshots, frame after frame") {
    int ran = 0;
    for (const char* dir : {"bx_n4700", "s_ref"}) {
        const std::vector<u8> snapmem = read_snapshot(dir);
        if (snapmem.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(dir) << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snapmem.data(), snapmem.size());
        const u32 ae = get32(m, kAeHead);
        if (ae == 0) {
            MESSAGE("SKIP: " << std::string(dir) << " holds no live after effect");
            continue;
        }
        INFO(std::string(dir));
        const u32 model = get32(m, get32(m, ae + 4) + 32);
        const u16 mflags = get16(m, model + 216);
        for (int f = 0; f < 12; ++f) {
            const u32 seed = seed_of(f, 0x4700u);
            // frames 8.. with the model's bit 15 (+216) flipped: the other world matrix (root via sub_318B60 / +144)
            if (f == 8) put16(m, model + 216, static_cast<u16>(mflags ^ 0x8000u));
            pair(m, PAIR(fn_sub_1EDA90_001eda90), {sx(ae), 0, 0, 0}, seed, std::string("sub_1EDA90 ") + dir, {}, kWhole);
            pair(m, PAIR(fn_sub_1EDBE0_001edbe0), {sx(ae), 0, 0, 0}, seed, std::string("sub_1EDBE0 ") + dir, {}, kWhole);
            pair(m, PAIR(fn_sub_1EDED0_001eded0), {sx(ae), 0, 0, 0}, seed, std::string("sub_1EDED0 ") + dir, {}, kWhole);
            ++ran;
        }
        put16(m, model + 216, mflags);
        const u32 ring = get32(m, ae + 8);
        MESSAGE(std::string(dir) << ": after 12 frames the first ring holds " << get32(m, ring + 8) << " samples");
        // a second after effect from the same pack (the heap allocators, the trail builders, the link, the scripts),
        // then both updated, then the first killed (its pack released)
        const u32 pack = get32(m, get32(m, ae + 4) + 32);
        const u32 flags = 0x83A21Cu + 4u * (5120u >> 5);
        put32(m, flags, get32(m, flags) & ~(1u << (5120u & 31)));
        const PairOut c = pair(m, PAIR(fn_sub_1EDA00_001eda00), {sx(pack), sx(0x80FFFFFFu), 0, 0}, 1,
                               std::string("sub_1EDA00 ") + dir, {}, kWhole);
        if (!c.recomp.stopped && c.recomp.v0() != 0) {
            const u32 ae2 = static_cast<u32>(c.recomp.v0());
            for (int f = 0; f < 4; ++f)
                pair(m, PAIR(fn_sub_1EDBE0_001edbe0), {sx(ae2), 0, 0, 0}, seed_of(f, 0x4701u),
                     std::string("sub_1EDBE0 (new) ") + dir, {}, kWhole);
        }
        pair(m, PAIR(fn_sub_1EE1D0_001ee1d0), {sx(ae), 0, 0, 0}, 2, std::string("sub_1EE1D0 ") + dir, {}, kWhole);
    }
    MESSAGE("snapshot frames: " << ran);
}

// =====================================================================================================================
// Effect manager: tracks, layer lists, user data
// =====================================================================================================================
constexpr u32 kFx = 0x01830000u, kFxElems = 0x01834000u, kFxTracks = 0x01836000u, kFxList = 0x0183F000u;
u32 fxrec(int i) { return kFx + 0x100u * static_cast<u32>(i); }

// Effect records: four 16-byte track slots at +0 ({+0 key count, +4 length, +8 key stride, +12 keys or 0}; slot k
// uses entry k of the type table 0x69BB10: scalar keys {t, v}, vector keys {t, x, y, z}, the constant record, none),
// the colour / vector at +64..+79, the element array at +80 (materials, the elements the apply functions colour),
// the next record at +84; the list head at kFxList.
void make_fx(Machine& m, std::mt19937& rng, int n, bool shared) {
    put32(m, gpv(-17680), 0x40u);  // the materials' user-data plugin offset
    const u32 udoff = 0x40u;
    for (int e = 0; e < 4; ++e) {
        const u32 el = kFxElems + 0x800u * static_cast<u32>(e);
        put32(m, el + 0, el + 0x10);
        put16(m, el + 4, static_cast<u16>(rng() % 4));
        for (u32 k = 0; k < 4; ++k) {
            const u32 mat = el + 0x100 + 0x180 * k;
            put32(m, el + 0x10 + 4 * k, mat);
            fill(m, mat, 0x40, rng);
            // the two integer user-data arrays the apply functions look up by name (0x69BAF0 / 0x678F90)
            const u32 arrays = mat + 0x80;
            put32(m, mat + udoff, 2);
            put32(m, mat + udoff + 4, arrays);
            const u32 names[2] = {0x0069BAF0u, 0x00678F90u};
            for (u32 a = 0; a < 2; ++a) {
                put32(m, arrays + 16 * a + 0, names[a]);
                put32(m, arrays + 16 * a + 4, 1);
                put32(m, arrays + 16 * a + 8, 1);
                put32(m, arrays + 16 * a + 12, arrays + 0x40 + 8 * a);
                put32(m, arrays + 0x40 + 8 * a, rng());
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        const u32 r = fxrec(i);
        fill(m, r, 0x60, rng);
        for (u32 k = 0; k < 4; ++k) {
            const u32 slot = r + 16 * k;
            const u32 keys = kFxTracks + 0x200u * (4 * i + k);
            const bool on = chance(rng, k == 2 ? 15 : 65);
            const u32 count = 1 + rng() % 5;
            const u32 stride = k == 1 ? 16u : 8u;
            put32(m, slot + 0, count);
            putf(m, slot + 4, rf(rng, 0, 100));
            put32(m, slot + 8, stride);
            put32(m, slot + 12, on ? keys : 0u);
            float tt = rf(rng, -5, 5);
            for (u32 j = 0; j < count + 1; ++j) {
                tt += rf(rng, 0.1f, 10);
                putf(m, keys + stride * j, tt);
                fill_floats(m, keys + stride * j + 4, stride / 4 - 1, rng);
            }
        }
        put32(m, r + 80, kFxElems + 0x800u * static_cast<u32>(shared ? 0 : rng() % 4));
        put32(m, r + 84, i + 1 < n ? fxrec(i + 1) : 0);
    }
    put32(m, kFxList, n ? fxrec(0) : 0);
}

TEST_CASE("game(fx_layers): the keyframe-track walks sub_320080 / 320380 / 3204A0 / 320640 / 320770 / 320810") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 150; ++i) {
        const u32 seed = seed_of(i, 0x320080u);
        std::mt19937 rng{seed};
        const int n = static_cast<int>(rng() % 4);
        make_fx(m, rng, n, chance(rng, 50));
        const u32 t = std::bit_cast<u32>(rf(rng, -5, 60)), u = std::bit_cast<u32>(rf(rng, -5, 60)), v = std::bit_cast<u32>(rf(rng, 0, 1));
        pair(m, PAIR(fn_sub_320080_00320080), {sx(fxrec(0)), sx(fxrec(chance(rng, 50) ? 0 : 1)), 0, 0}, seed, "sub_320080",
             floats({t, u, v}));
        make_fx(m, rng, n, chance(rng, 50));
        pair(m, PAIR(fn_sub_320380_00320380), {sx(kFxList), 0, 0, 0}, seed, "sub_320380", floats({t}));
        make_fx(m, rng, n, chance(rng, 50));
        pair(m, PAIR(fn_sub_3204A0_003204a0), {sx(kFxList), 0, 0, 0}, seed, "sub_3204A0", floats({t, u, v}));
        make_fx(m, rng, n, chance(rng, 50));
        pair(m, PAIR(fn_sub_320640_00320640), {sx(kFxList), 0, 0, 0}, seed, "sub_320640", floats({t, u}));
        make_fx(m, rng, n, false);
        pair(m, PAIR(fn_sub_320770_00320770), {sx(kFxList), 0, 0, 0}, seed, "sub_320770");
        const PairOut mx = pair(m, PAIR(fn_sub_320810_00320810), {sx(kFxList), 0, 0, 0}, seed, "sub_320810");
        // documented rule: the largest track length (+4) among the slots with a track, from 0.0
        float best = 0;
        for (u32 e = n ? fxrec(0) : 0; e; e = get32(m, e + 84))
            for (u32 k = 0; k < 4; ++k)
                if (get32(m, e + 12 + 16 * k) && getf(m, e + 4 + 16 * k) > best) best = getf(m, e + 4 + 16 * k);
        CHECK(mx.recomp.f0() == best);
    }
    // the type table's own entries
    pair(m, PAIR(fn_sub_320060_00320060), {0, 0, 0, 0}, 1, "sub_320060");
    pair(m, PAIR(fn_nullsub_106_00320070), {0, 0, 0, 0}, 1, "nullsub_106");
}

TEST_CASE("game(fx_layers): the layer lists sub_321120 / 321130 / 321140..3212E0 / 323860 / 321F10 / 321320") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    struct L {
        const char* name;
        Fn hand, recomp;
        u32 table;
        u32 link;
        bool at_least_5;
    };
    const L lists[] = {{"sub_321140", PAIR(fn_sub_321140_00321140), 0x957920u, 24, false},
                       {"sub_321180", PAIR(fn_sub_321180_00321180), 0x957820u, 44, true},
                       {"sub_3211D0", PAIR(fn_sub_3211D0_003211d0), 0x957720u, 44, true},
                       {"sub_321220", PAIR(fn_sub_321220_00321220), 0x957620u, 100, false},
                       {"sub_321260", PAIR(fn_sub_321260_00321260), 0x957520u, 92, false},
                       {"sub_3212A0", PAIR(fn_sub_3212A0_003212a0), 0x957420u, 108, false},
                       {"sub_3212E0", PAIR(fn_sub_3212E0_003212e0), 0x957320u, 156, false},
                       {"sub_323860", PAIR(fn_sub_323860_00323860), 0x957920u, 24, false}};
    for (int i = 0; i < 200; ++i) {
        const u32 seed = seed_of(i, 0x321140u);
        std::mt19937 rng{seed};
        const u32 bank = rng() % 10;
        pair(m, PAIR(fn_sub_321120_00321120), {arg64(rng, bank | (rng() & 0xFFFF0000u)), 0, 0, 0}, seed, "sub_321120");
        CHECK(get16(m, kBank) == static_cast<u16>(bank));
        pair(m, PAIR(fn_sub_321130_00321130), {0, 0, 0, 0}, seed, "sub_321130");
        for (const L& l : lists) {
            const u32 layer = rng() % 7;
            const u32 obj = 0x01838000u + 0x100u * (rng() % 8);
            fill(m, obj, 0x100, rng);
            const u32 b = l.at_least_5 ? std::max(bank, 5u) : bank;
            const u32 head = l.table + 28 * b + 4 * layer;
            const u32 old = get32(m, head);
            pair(m, l.hand, l.recomp, {sx(obj), arg64(rng, layer | (rng() & 0xFFFF0000u)), 0, 0}, seed, l.name);
            CHECK(get32(m, head) == obj);  // documented rule: object pushed at the head, link = the old head
            CHECK(get32(m, obj + l.link) == old);
        }
        pair(m, PAIR(fn_sub_321F10_00321f10), {arg64(rng, (rng() % 10) | (rng() & 0xFFFF0000u)), 0, 0, 0}, seed, "sub_321F10");
        fill(m, kOut, 64, rng);
        pair(m, PAIR(fn_sub_321320_00321320), {sx(kOut), 0, 0, 0}, seed, "sub_321320");
        CHECK(std::memcmp(m.at(0x9572E0u), m.at(kOut), 64) == 0);
        CHECK(get32(m, gpv(-18352)) == 1u);
    }
}

TEST_CASE("game(fx_layers): small accessors sub_321050 / 321070 / 3210A0 / 322DA0 / 322FB0 / 323BF0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 200; ++i) {
        const u32 seed = seed_of(i, 0x321050u);
        std::mt19937 rng{seed};
        fill(m, kOut, 0x200, rng);
        pair(m, PAIR(fn_sub_321050_00321050), {sx(kOut), 0, 0, 0}, seed, "sub_321050");
        put32(m, kOut + 0x20, kOut + 0x100);
        put16(m, kOut + 0x24, static_cast<u16>(rng() % 32));
        pair(m, PAIR(fn_sub_321070_00321070), {sx(kOut + 0x20), sx(rng()), 0, 0}, seed, "sub_321070");
        pair(m, PAIR(fn_sub_3210A0_003210a0), {arg64(rng, rng()), 0, 0, 0}, seed, "sub_3210A0");
        put32(m, kOut + 0x40, kOut + 0x60);
        put32(m, kOut + 0x60 + 20, kOut + 0x100);
        pair(m, PAIR(fn_sub_322DA0_00322da0), {sx(kOut + 0x40), sx(rng() % 16), 0, 0}, seed, "sub_322DA0");
        pair(m, PAIR(fn_sub_322FB0_00322fb0), {sx(kOut), 0, 0, 0}, seed, "sub_322FB0");
        put32(m, kOut + 0x80 + 20, kOut + 0x90);
        put32(m, kOut + 0x90, chance(rng, 30) ? 0u : kOut + 0xA0);
        put32(m, kOut + 0xA0, kOut + 0xC0);
        pair(m, PAIR(fn_sub_323BF0_00323bf0), {sx(kOut + 0x80), sx(kOut + 0x1E0), 0, 0}, seed, "sub_323BF0");
    }
}

// Materials with user-data arrays (the RpUserData layout the accessors read: plugin offset gp-17680 -> {count,
// 16-byte arrays {+0 name, +4 format, +8 count, +12 elements}}), atomics with geometries, a clump of atomics.
constexpr u32 kUd = 0x01839000u;
u32 g_udoff = 0;
void make_materials(Machine& m, std::mt19937& rng, u32 geometry, int mats, const char* tag, const char* want) {
    put32(m, gpv(-17680), 0x40u);
    g_udoff = 0x40u;
    const u32 strs = kUd + 0x2000;
    std::memcpy(m.at(strs), want, std::strlen(want) + 1);
    std::memcpy(m.at(strs + 0x20), "other", 6);
    std::memcpy(m.at(strs + 0x40), tag, std::strlen(tag) + 1);
    put32(m, geometry + 32, kUd + 0x1000);
    put32(m, geometry + 36, static_cast<u32>(mats));
    put32(m, geometry + 8, rng() & 0xBFu);
    for (int i = 0; i < mats; ++i) {
        const u32 mat = kUd + 0x100u * static_cast<u32>(i);
        put32(m, kUd + 0x1000 + 4u * i, mat);
        const u32 ext = mat + g_udoff;
        const u32 arrays = kUd + 0x3000 + 0x100u * static_cast<u32>(i);
        const int na = static_cast<int>(rng() % 3);
        put32(m, ext + 0, static_cast<u32>(na));
        put32(m, ext + 4, arrays);
        for (int a = 0; a < na; ++a) {
            const u32 arr = arrays + 16u * a;
            const bool named = chance(rng, 70);
            put32(m, arr + 0, named ? strs + 0x40 : strs + 0x20);
            put32(m, arr + 4, chance(rng, 80) ? 3u : rng() % 4);
            const u32 ne = rng() % 3;
            put32(m, arr + 8, ne);
            put32(m, arr + 12, arrays + 0x80 + 16u * a);
            for (u32 e = 0; e < ne; ++e) put32(m, arrays + 0x80 + 16u * a + 4 * e, chance(rng, 50) ? strs : strs + 0x20);
        }
    }
}

TEST_CASE("game(fx_layers): tagged materials -- sub_320BA0 / 320CF0 / 320DE0 / 320DA0 / 320F70") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const char* tag = reinterpret_cast<const char*>(m.at(gpv(-25296)));  // the user-data array name the game looks for
    const std::string tagname(tag, strnlen(tag, 32));
    for (int i = 0; i < 200; ++i) {
        const u32 seed = seed_of(i, 0x320BA0u);
        std::mt19937 rng{seed};
        const u32 atomic = 0x0183A000u, geometry = 0x0183A100u, list = 0x0183A200u, rec = 0x0183A300u;
        zero(m, atomic, 0x100);
        put32(m, atomic + 24, geometry);
        make_materials(m, rng, geometry, static_cast<int>(rng() % 4), tagname.c_str(), "wanted");
        put32(m, list + 0, list + 0x20);
        put16(m, list + 4, 0);
        put32(m, rec + 0, list);
        put32(m, rec + 4, kUd + 0x2000);  // "wanted"
        pair(m, PAIR(fn_sub_320BA0_00320ba0), {sx(kUd), sx(rec), 0, 0}, seed, "sub_320BA0");
        pair(m, PAIR(fn_sub_320CF0_00320cf0), {sx(atomic), sx(rec), 0, 0}, seed, "sub_320CF0");
        put32(m, rec + 0x10, kUd + 0x2000);
        put16(m, rec + 0x14, static_cast<u16>(rng() % 3));
        pair(m, PAIR(fn_sub_320DE0_00320de0), {sx(atomic), sx(rec + 0x10), 0, 0}, seed, "sub_320DE0");
        // a clump: its atomic list at +8 (links at atomic +64, back to the clump's +8)
        const u32 clump = 0x0183A400u;
        const u32 link = atomic + 64;
        put32(m, clump + 8, link);
        put32(m, link + 0, clump + 8);
        pair(m, PAIR(fn_sub_320DA0_00320da0), {sx(clump), sx(rec), 0, 0}, seed, "sub_320DA0");
        pair(m, PAIR(fn_sub_320F70_00320f70), {sx(clump), sx(kUd + 0x2000), 0, 0}, seed, "sub_320F70");
    }
}

// =====================================================================================================================
// Effect manager: sprite players and image sequences
// =====================================================================================================================
constexpr u32 kSet = 0x0183B000u, kSetAnims = 0x0183B100u, kSetKeys = 0x0183C000u, kSetTex = 0x0183B800u;
constexpr u32 kPlayer = 0x0183D000u, kTrackStates = 0x0183D100u, kQuad = 0x0183D400u;

void make_sprite_set(Machine& m, std::mt19937& rng) {
    put32(m, kSet + 0, kSetKeys);
    put32(m, kSet + 4, kSetAnims);
    put32(m, kSet + 20, kSetTex);
    for (u32 a = 0; a < 8; ++a) {
        const u32 rec = kSetAnims + 20 * a;
        put32(m, rec + 0, 24u * (rng() % 8));
        put32(m, rec + 4, 4u * (rng() % 8));
        put32(m, rec + 8, chance(rng, 30) ? 0xC0u : rng() & 0x3Fu);
        put32(m, rec + 12, chance(rng, 10) ? 0u : 1 + rng() % 4);
        u32 fl = rng() & 0x17u;
        if (chance(rng, 25)) fl |= 0x10000000u;
        put32(m, rec + 16, fl);
    }
    for (u32 k = 0; k < 24; ++k) {
        const u32 key = kSetKeys + 24 * k;
        fill(m, key, 24, rng);
        put16(m, key + 0, static_cast<u16>(rng() % 6));                       // the entry's animation (lists)
        put16(m, key + 2, static_cast<u16>(rng() % 5));                       // start delay
        put16(m, key + 16, static_cast<u16>(rng() % 4));                      // texture index
        put16(m, key + 18, static_cast<u16>(chance(rng, 20) ? 0 : rng() % 6));  // frames
        putf(m, key + 20, rf(rng, 0, 1));
    }
    for (u32 t = 0; t < 4; ++t) {
        const u32 tex = 0x0183B900u + 0x40 * t, ras = tex + 0x20;
        put32(m, kSetTex + 4 * t, tex);
        put32(m, tex, ras);
        put32(m, ras + 12, 8u << (rng() % 4));
        put32(m, ras + 16, 8u << (rng() % 4));
    }
}

TEST_CASE("game(fx_layers): the sprite players sub_3226B0 / 322AB0 / 322D10 / 322D40 and sub_322FD0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 250; ++i) {
        const u32 seed = seed_of(i, 0x3226B0u);
        std::mt19937 rng{seed};
        make_sprite_set(m, rng);
        fill(m, kPlayer, 0x40, rng);
        put32(m, kPlayer + 0, kSet);
        put32(m, kPlayer + 16, kTrackStates);
        fill(m, kTrackStates, 0x100, rng);
        for (u32 t = 0; t < 8; ++t) {  // valid track states: a record and its keys (sub_3226B0 rewrites the ones it starts)
            const u32 st = kTrackStates + 20 * t, a = rng() % 6;
            put32(m, st + 4, rng() % 4);
            put32(m, st + 8, rng() % 4 - 1);
            put32(m, st + 12, kSetAnims + 20 * a);
            put32(m, st + 16, kSetKeys + get32(m, kSetAnims + 20 * a));
        }
        pair(m, PAIR(fn_sub_3226B0_003226b0), {sx(kPlayer), sx(rng() % 7), 0, 0}, seed, "sub_3226B0");
        // step the tracks a few frames; records flagged 0x10000000 stay untouched
        for (int k = 0; k < 5; ++k) {
            const u32 tr = kTrackStates + 20u * (rng() % 2);
            pair(m, PAIR(fn_sub_322AB0_00322ab0), {sx(kPlayer), sx(tr), sx(kQuad), 0}, seed + k, "sub_322AB0");
        }
        pair(m, PAIR(fn_sub_322D10_00322d10), {sx(kPlayer), sx(kQuad), 0, 0}, seed, "sub_322D10");
        put32(m, kPlayer + 12, rng() % 3);
        pair(m, PAIR(fn_sub_322D40_00322d40), {sx(kPlayer), arg64(rng, rng() % 1000), 0, 0}, seed, "sub_322D40");
        // an image sequence: frames {duration}, flags 1 loop / 4 double, the textures, the length
        const u32 seq = 0x0183E000u, frames = seq + 0x100;
        const u32 nf = chance(rng, 15) ? 1u : 1 + rng() % 6;
        u32 total = 0;
        for (u32 f = 0; f < nf; ++f) {
            const u32 d = rng() % 10;
            put32(m, frames + 16 * f, d);
            total += d + 1;
        }
        put32(m, seq + 4, nf);
        put32(m, seq + 8, rng() & 5u);
        put32(m, seq + 16, frames);
        put32(m, seq + 20, kSetTex);
        put32(m, seq + 24, chance(rng, 10) ? 0u : total);
        const u32 time = rng() % (total + 20);
        pair(m, PAIR(fn_sub_322FD0_00322fd0), {sx(seq), arg64(rng, time), sx(kQuad + 0x80), 0}, seed, "sub_322FD0");
    }
}

// =====================================================================================================================
// Effect manager: placement matrices, meshes, the layer tasks
// =====================================================================================================================

TEST_CASE("game(fx_layers): placement matrices sub_323920 / 323A30 / 323880 / 3238D0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 200; ++i) {
        const u32 seed = seed_of(i, 0x323920u);
        std::mt19937 rng{seed};
        const u32 mat = 0x0183F100u, tr = 0x0183F200u, rot = 0x0183F300u, sc = 0x0183F400u;
        fill_floats(m, mat, 16, rng);
        put32(m, mat + 12, rng());
        fill_floats(m, tr, 3, rng);
        fill_floats(m, rot, 4, rng);
        put16(m, rot, static_cast<u16>(rng()));
        fill_floats(m, sc, 3, rng);
        const u32 scale = chance(rng, 30) ? 0x3F800000u : rand_float(rng);
        const u32 a1 = chance(rng, 30) ? 0u : tr, a2 = chance(rng, 40) ? 0u : rot, a3 = chance(rng, 40) ? 0u : sc;
        pair(m, PAIR(fn_sub_323920_00323920), {sx(mat), sx(a1), sx(a2), 0}, seed, "sub_323920", floats({scale}));
        pair(m, PAIR(fn_sub_323A30_00323a30), {sx(mat), sx(a1), sx(a2), sx(a3)}, seed, "sub_323A30");
        // an object with a frame (+12): RwFrameTransform
        const u32 obj = 0x0183F500u, frame = 0x0183F600u;
        fill(m, frame, 0x100, rng);
        put32(m, frame + 160, frame);  // a root frame
        put32(m, 0x96012Cu, 0x96012Cu);  // RW's dirty-frame list, empty
        put32(m, 0x960130u, 0x96012Cu);
        put32(m, obj + 12, frame);
        pair(m, PAIR(fn_sub_323880_00323880), {sx(obj), sx(a1), sx(a2), 0}, seed, "sub_323880", floats({scale}));
        pair(m, PAIR(fn_sub_3238D0_003238d0), {sx(obj), sx(a1), sx(a2), sx(a3)}, seed, "sub_3238D0");
    }
}

TEST_CASE("game(fx_layers): the effect mesh builders and copies on a snapshot's heap") {
    int ran = 0;
    for (const char* dir : {"bx_n4700", "battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snapmem = read_snapshot(dir);
        if (snapmem.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(dir) << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snapmem.data(), snapmem.size());
        // a real texture: effect/z0.tmx, which effAfter_CreateAfterEffectRenderTask keeps at gp-18972 in every snapshot
        const u32 texture = get32(m, gpv(-18972));
        MESSAGE(std::string(dir) << ": the z0 texture is at " << hex64(texture));
        for (int i = 0; i < 4; ++i) {
            const u32 seed = seed_of(i, 0x323240u);
            std::mt19937 rng{seed};
            const u32 idx = 0x0183F800u;  // a 6-index cell template (two triangles)
            const u16 cell[6] = {0, 1, 3, 1, 4, 3};
            for (u32 k = 0; k < 6; ++k) put16(m, idx + 2 * k, static_cast<u16>(cell[k] + (rng() % 2)));
            const u32 rows = 1 + rng() % 3, cols = 2 + rng() % 3;
            const std::string d = std::string(" ") + dir;
            const PairOut g = pair(m, PAIR(fn_sub_323240_00323240), {sx(rows), sx(idx), sx(cols), sx(rng() & 0x1u)}, seed,
                                   "sub_323240" + d, {}, kWhole);
            pair(m, PAIR(fn_sub_3233A0_003233a0), {sx(rows), sx(2), sx(cols), sx(idx)}, seed, "sub_3233A0" + d,
                 regs({{GPR_T0, sx(rng() & 0x1u)}}), kWhole);
            pair(m, PAIR(fn_sub_323E10_00323e10), {sx(2), sx(rows), sx(2), sx(cols)}, seed, "sub_323E10" + d,
                 regs({{GPR_T0, sx(idx)}, {GPR_T1, sx(0)}}), kWhole);
            pair(m, PAIR(fn_sub_323FB0_00323fb0), {sx(2), sx(rows), sx(idx), sx(cols)}, seed, "sub_323FB0" + d,
                 regs({{GPR_T0, sx(0)}}), kWhole);
            if (!g.recomp.stopped && g.recomp.v0() != 0) {
                const u32 mesh = static_cast<u32>(g.recomp.v0());
                pair(m, PAIR(fn_sub_323640_00323640), {sx(mesh), 0, 0, 0}, seed, "sub_323640" + d, {}, kWhole);
                pair(m, PAIR(fn_sub_323BF0_00323bf0), {sx(mesh), sx(0x0183F900u), 0, 0}, seed, "sub_323BF0" + d, {}, kWhole);
                // the copy with a texture on the source material, and the flag-2 copy (sub_3234F0)
                if (texture != 0) {
                    const u32 mat = get32(m, mesh + 20);
                    put32(m, mat + 0, texture);
                    put32(m, get32(m, get32(m, get32(m, get32(m, mesh + 16) + 24) + 32)), texture);
                }
                pair(m, PAIR(fn_sub_323640_00323640), {sx(mesh), 0, 0, 0}, seed + 1, "sub_323640 (textured)" + d, {}, kWhole);
                put16(m, mesh + 0, static_cast<u16>(get16(m, mesh) | 2u));
                pair(m, PAIR(fn_sub_323640_00323640), {sx(mesh), 0, 0, 0}, seed + 2, "sub_323640 (flag 2)" + d, {}, kWhole);
            }
            pair(m, PAIR(fn_sub_3210C0_003210c0), {sx(0x0183FA00u), 0, 0, 0}, seed, "sub_3210C0" + d, {}, kWhole);
            // the program task with a pending camera update (0x9572D0): the two 2-D vectors and the frame matrix
            fill_floats(m, 0x009572B0u, 8, rng);
            fill_floats(m, 0x00957270u, 16, rng);
            put32(m, 0x0095727Cu, 0x00020003u);
            put32(m, 0x009572D0u, i % 2 ? 1u : 0u);
            pair(m, PAIR(fn_effMng_UpdateEffectProgramTask_00321a60), {0, 0, 0, 0}, seed, "effMng_UpdateEffectProgramTask" + d, {}, kWhole);
            ++ran;
        }
    }
    MESSAGE("mesh snapshot rounds: " << ran);
}

TEST_CASE("game(fx_layers): the layer tasks and the program task (effMng_UpdateEffect3dTask / 321E20 / 321FE0 / 321A60), sub_323B90") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 20; ++i) {
        const u32 seed = seed_of(i, 0x321CB0u);
        pair(m, PAIR(fn_effMng_UpdateEffect3dTask_00321cb0), {0, 0, 0, 0}, seed, "effMng_UpdateEffect3dTask");
        pair(m, PAIR(fn_effMng_UpdateEffect2dTask_00321e20), {0, 0, 0, 0}, seed, "effMng_UpdateEffect2dTask");
        pair(m, PAIR(fn_sub_321FE0_00321fe0), {0, 0, 0, 0}, seed, "sub_321FE0");
        pair(m, PAIR(fn_effMng_UpdateEffectProgramTask_00321a60), {0, 0, 0, 0}, seed, "effMng_UpdateEffectProgramTask");
        pair(m, PAIR(fn_sub_323B90_00323b90), {sx(0x0183FB00u), sx(0x0183FC00u), 0, 0}, seed, "sub_323B90");
    }
}

TEST_CASE("game(fx_layers): pair totals") {
    MESSAGE("fx_layers pairs: " << g_pairs << " (" << g_stops << " ended at a callee not emitted in this build)");
    for (const auto& [k, n] : g_stop_kinds) MESSAGE("  stop " << n << "x " << k);
    CHECK(g_pairs > 0);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
