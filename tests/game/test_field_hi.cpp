// Phase 5 pair tests for the field layer's second pass (game/src/field/field_hi.cpp): each hand-written function and
// the recompiled body it replaces run on identical guest machines on randomised inputs, and EVERYTHING observable is
// compared:
//   * the whole register file (GPRs in 128 bits, HI/LO, SA, the FPRs, ACC, FCR31) and the cycle count at every check
//     point -- the function's own and those of the callees it reaches (a check point may preempt the thread, and the
//     kernel then stores the register file in guest memory) -- and at the return;
//   * guest memory: .data/.bss 0x600000..0xA00000 (the field units, the scene / dungeon words, the kwln lists), the
//     test arena 0x1800000..0x1820000 and the stack 0x1FF0000..0x2000000 (frames, spills and the dead stack);
//   * the bus log length, syscall and trap counts.
// Callees that are kept recompiled but not emitted in this test build (the model / effect / task creators: deep call
// trees) end the run through rt::missing_function: the hooks snapshot the register file and memory AT that call
// before the stop unwinds, so both bodies must reach the same callee with the same state. The documented rules
// (docs/ANALYSIS/26_field.md) are checked on the host, independently of both bodies.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/field_hi.h"

#include <array>
#include <cmath>
#include <cstring>
#include <functional>
#include <iterator>
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
P3FES_DECL_PAIR(fn_K_FldDungeon_GetScrSize_001c0010)
P3FES_DECL_PAIR(fn_sub_1C0070_001c0070)
P3FES_DECL_PAIR(fn_sub_1C03B0_001c03b0)
P3FES_DECL_PAIR(fn_sub_1C00D0_001c00d0)
P3FES_DECL_PAIR(fn_sub_1C0110_001c0110)
P3FES_DECL_PAIR(fn_sub_1C2000_001c2000)
P3FES_DECL_PAIR(fn_sub_1C6080_001c6080)
P3FES_DECL_PAIR(fn_sub_1C65E0_001c65e0)
P3FES_DECL_PAIR(fn_K_FldEvent_IsUnitHero_001c7b10)
P3FES_DECL_PAIR(fn_sub_1CD650_001cd650)
P3FES_DECL_PAIR(fn_sub_1CD670_001cd670)
P3FES_DECL_PAIR(fn_sub_1CD690_001cd690)
P3FES_DECL_PAIR(fn_sub_1CD790_001cd790)
P3FES_DECL_PAIR(fn_sub_1CD870_001cd870)
P3FES_DECL_PAIR(fn_sub_1CD8E0_001cd8e0)
P3FES_DECL_PAIR(fn_sub_1CD940_001cd940)
P3FES_DECL_PAIR(fn_sub_1CE880_001ce880)
P3FES_DECL_PAIR(fn_sub_1D0270_001d0270)
P3FES_DECL_PAIR(fn_sub_1D0E40_001d0e40)
P3FES_DECL_PAIR(fn_sub_1D11B0_001d11b0)
P3FES_DECL_PAIR(fn_sub_1D12D0_001d12d0)
P3FES_DECL_PAIR(fn_sub_1D1780_001d1780)
P3FES_DECL_PAIR(fn_sub_1D17F0_001d17f0)
P3FES_DECL_PAIR(fn_sub_1D1860_001d1860)
P3FES_DECL_PAIR(fn_sub_1D1910_001d1910)
P3FES_DECL_PAIR(fn_sub_1D19D0_001d19d0)
P3FES_DECL_PAIR(fn_sub_1D1A90_001d1a90)
P3FES_DECL_PAIR(fn_sub_1D1B60_001d1b60)
P3FES_DECL_PAIR(fn_sub_1D1C20_001d1c20)
P3FES_DECL_PAIR(fn_sub_1D1CE0_001d1ce0)
P3FES_DECL_PAIR(fn_sub_1D3790_001d3790)
P3FES_DECL_PAIR(fn_sub_1D37F0_001d37f0)
P3FES_DECL_PAIR(fn_sub_1D3810_001d3810)
P3FES_DECL_PAIR(fn_sub_1D38A0_001d38a0)
P3FES_DECL_PAIR(fn_sub_1D5130_001d5130)
P3FES_DECL_PAIR(fn_sub_1D5C00_001d5c00)
P3FES_DECL_PAIR(fn_sub_1D5E10_001d5e10)
P3FES_DECL_PAIR(fn_sub_1D5F30_001d5f30)
P3FES_DECL_PAIR(fn_sub_1D8C60_001d8c60)
P3FES_DECL_PAIR(fn_sub_1D8D50_001d8d50)
P3FES_DECL_PAIR(fn_sub_1D8D60_001d8d60)
P3FES_DECL_PAIR(fn_sub_1D9FD0_001d9fd0)
P3FES_DECL_PAIR(fn_sub_1DA000_001da000)
P3FES_DECL_PAIR(fn_sub_1DD5E0_001dd5e0)
P3FES_DECL_PAIR(fn_sub_1DD5F0_001dd5f0)
P3FES_DECL_PAIR(fn_sub_1E13C0_001e13c0)
P3FES_DECL_PAIR(fn_sub_1E1820_001e1820)
P3FES_DECL_PAIR(fn_sub_1E1840_001e1840)
P3FES_DECL_PAIR(fn_sub_1E2810_001e2810)
P3FES_DECL_PAIR(fn_sub_1E29E0_001e29e0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::fldhi;

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
// "" when equal, else the first difference.
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

// --- the compared guest memory -----------------------------------------------------------------------------------------
constexpr GuestRange kRanges[] = {{0x00600000u, 0x00400000u}, {0x01800000u, 0x00020000u}, {0x01FF0000u, 0x00010000u}};
using Mem = std::vector<std::vector<u8>>;
Mem capture(const Machine& m) {
    Mem out;
    for (const GuestRange& r : kRanges) out.push_back(m.bytes(r.va, r.len));
    return out;
}
void restore(Machine& m, const Mem& mem) {
    for (std::size_t i = 0; i < std::size(kRanges); ++i) std::memcpy(m.at(kRanges[i].va), mem[i].data(), kRanges[i].len);
}

// Hooks: a register snapshot at every check point; rt::missing_function (a callee not emitted in this build) snapshots
// the register file and memory at the call before it unwinds.
class FullHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    Machine* m = nullptr;
    std::vector<Snap> snaps;
    int syscalls = 0, traps = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop{};
    Mem mem_at_stop;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override { snaps.push_back(snap(ctx)); }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        at_stop = snap(ctx);
        mem_at_stop = capture(*m);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
    void vu_control_write(EEContext&, u32, u32) override {}
};

struct Run {
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap end{};
    Mem mem;
    std::size_t bus = 0;
    int syscalls = 0, traps = 0;
    u64 v0() const { return end.gpr[GPR_V0].u64[0]; }
    u32 f0() const { return end.fpr[0]; }
};

using Prep = std::function<void(EEContext&)>;

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const Prep& prep) {
    FullHooks h;
    h.m = &m;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng() & 0xBF7FFFFFu;
    m.ctx.acc = rng() & 0xBF7FFFFFu;
    m.ctx.fcr31 = rng() & 0x00800000u;
    for (int i = 0; i < 2; ++i) {
        m.ctx.hi.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
        m.ctx.lo.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
    }
    if (prep) prep(m.ctx);
    Run r;
    try {
        fn(m.ctx);
        r.end = snap(m.ctx);
        r.mem = capture(m);
    } catch (const rt_test::FatalEvent&) {
        r.stopped = true;
        r.stop_pc = h.stop_pc;
        r.end = h.at_stop;
        r.mem = std::move(h.mem_at_stop);
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

int g_pairs = 0;

// A stand-in that ends the run at the callee the way a function this build does not emit does (rt::missing_function):
// the checks on the state at the call (stop pc, $a0.., $f12) hold whether the callee is recompiled or replaced, since
// the hooked forwarders ask the stand-ins first (finalA replaced the floor-effect, fade, release and font callees
// these cases stop at, earlier sweeps the EPL start and the model calls). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas)
            si.install(va, "stop (as not emitted)", [va](EEContext&, StandIns&, StandInCall&) { rt::missing_function(va); });
        scope = std::make_unique<StandInsScope>(si);
    }
};

PairOut pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Prep& prep = {}) {
    const Mem before = capture(m);
    PairOut p;
    p.hand = run_one(m, hand, args, seed, prep);
    restore(m, before);
    p.recomp = run_one(m, recomp, args, seed, prep);
    ++g_pairs;
    INFO(what);
    CHECK(p.hand.stopped == p.recomp.stopped);
    CHECK(p.hand.stop_pc == p.recomp.stop_pc);
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
    for (std::size_t i = 0; i < std::size(kRanges); ++i) {
        const auto& a = p.hand.mem[i];
        const auto& b = p.recomp.mem[i];
        const std::size_t first = first_difference(a.data(), b.data(), a.size());
        INFO("memory: first differing byte at " << hex64(kRanges[i].va + first));
        CHECK(first == a.size());
    }
    CHECK(p.hand.bus == p.recomp.bus);
    CHECK(p.hand.syscalls == p.recomp.syscalls);
    CHECK(p.hand.traps == p.recomp.traps);
    return p;
}

// --- fixtures ------------------------------------------------------------------------------------------------------
constexpr u32 kGpVa(s32 off) { return kGp + static_cast<u32>(off); }
constexpr u32 kDungeonSlot = kGpVa(kGpDungeonTask);  // 0x7CE268
constexpr u32 kSceneSlot = kGpVa(kGpSceneIds);       // 0x7CD540
static_assert(kDungeonSlot == 0x7CE268u && kSceneSlot == 0x7CD540u);

constexpr u32 kTask = 0x01800000u;     // a kwln task record (+60 = the work)
constexpr u32 kWork = 0x01800400u;     // its work (0x400 bytes)
constexpr u32 kRec = 0x01801000u;      // a scene record
constexpr u32 kObjs = 0x01802000u;     // resources / models / list nodes, 0x200 bytes apart
constexpr u32 kTasks2 = 0x01810000u;   // small task records, 0x100 apart (+28 flags, +60 work, +64 next)
constexpr u32 kFlagWord3173 = 0x83A21Cu + 4u * (3173u >> 5);  // datGetFlag's bit array
constexpr u32 kKwlnList0 = kGpVa(-19596);                     // kwlnTaskExists' three list heads

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
void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void zero(Machine& m, u32 va, u32 len) { std::memset(m.at(va), 0, len); }
u32 obj(int i) { return kObjs + 0x200u * static_cast<u32>(i); }
u32 task2(int i) { return kTasks2 + 0x100u * static_cast<u32>(i); }

// A task record with a random work.
void make_task(Machine& m, std::mt19937& rng) {
    zero(m, kTask, 0x68);
    put32(m, kTask + 60, kWork);
    fill(m, kWork, 0x400, rng);
}
// Random words that are often small, sometimes special.
u32 word(std::mt19937& rng) {
    switch (rng() % 6) {
    case 0: return 0;
    case 1: return rng() % 8;
    case 2: return static_cast<u32>(-static_cast<s32>(rng() % 4));
    case 3: return 0x80000000u;
    default: return rng();
    }
}
// 64-bit argument registers: sign-extended words, or a value with stray upper bits (the whole-register tests).
u64 arg64(std::mt19937& rng, u32 low) {
    return rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | low : sx(low);
}
// Clear both field-unit arrays and the party model slots.
void clear_units(Machine& m) {
    zero(m, kEcUnits, kUnitSize * kEcUnitCount);
    zero(m, kPcUnits, kUnitSize * kPcUnitCount);
    zero(m, kPcModelSlots, 32);
}
u32 unit_va(bool pc, u32 i) { return (pc ? kPcUnits : kEcUnits) + kUnitSize * i; }
// A unit is "live" with +72 and +84 set; `p` in percent.
void random_units(Machine& m, std::mt19937& rng, bool pc, int p, bool only_instance = false) {
    const u32 n = pc ? kPcUnitCount : kEcUnitCount;
    for (u32 i = 0; i < n; ++i) {
        const u32 u = unit_va(pc, i);
        const bool live = static_cast<int>(rng() % 100) < p;
        put32(m, u + kUnitInstance, live || rng() % 4 == 0 ? 0x01500000u + 0x40u * i : 0u);
        put32(m, u + kUnitResource, live || (!only_instance && rng() % 3 == 0) ? obj(static_cast<int>(i % 16)) : 0u);
        if (!live && rng() % 2) put32(m, u + kUnitInstance, 0);
    }
}

// ======================================================================================================================

TEST_CASE("game(field_hi): the dungeon accessors equal their recompiled bodies (script size, kind scale, requests)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D101u};
    const s32 kinds[] = {0, 1, 2, 3, 4, 5, -1, 0x7FFFFFFF};
    for (int it = 0; it < 160; ++it) {
        make_task(m, rng);
        const bool have = it % 5 != 0;
        put32(m, kDungeonSlot, have ? kTask : 0u);
        const s32 kind = it < 8 ? kinds[it] : static_cast<s32>(rng() % 3 ? rng() % 6 : rng());
        put32(m, kWork + 40, static_cast<u32>(kind));
        const u32 size = word(rng);
        put32(m, kWork + 56, size);
        const PairOut a = pair(m, PAIR(fn_K_FldDungeon_GetScrSize_001c0010), Args{}, rng(), "K_FldDungeon_GetScrSize");
        CHECK(a.hand.v0() == (have ? sx(size) : 0u));
        const PairOut b = pair(m, PAIR(fn_sub_1C0070_001c0070), Args{}, rng(), "sub_1C0070");
        const bool dbl = have && (kind == 1 || kind == 3);
        CHECK(b.hand.f0() == (dbl ? 0x40000000u : 0x3F800000u));  // 2.0 / 1.0 (26_field.md 6.3)
        // The request poll: 0 -> 1, else request +12 == 4.
        const u32 req = it % 4 == 0 ? 0u : obj(1);
        put32(m, obj(1) + 12, it % 3 == 0 ? 4u : word(rng));
        const PairOut c = pair(m, PAIR(fn_sub_1C03B0_001c03b0), Args{arg64(rng, req)}, rng(), "sub_1C03B0");
        if (req == 0 && c.hand.end.gpr[GPR_A0].u64[0] == 0) CHECK(c.hand.v0() == 1);
    }
}

TEST_CASE("game(field_hi): the floor effect start / stop reach their callees with the original state") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D102u};
    StopAt stop{0x1A9400u, 0x1A91B0u};  // the effect stop / start: stopped at, as when they were not emitted
    for (int it = 0; it < 60; ++it) {
        make_task(m, rng);
        const bool have = it % 4 != 0;
        put32(m, kDungeonSlot, have ? kTask : 0u);
        const u32 epl = it % 3 == 0 ? 0u : obj(2);
        put32(m, kWork + 44, epl);
        fill(m, kSp - 0x100, 0x100, rng);  // stale frame bytes: the 12-byte clear must land on the original ones
        const PairOut a = pair(m, PAIR(fn_sub_1C00D0_001c00d0), Args{}, rng(), "sub_1C00D0");
        CHECK(a.hand.stopped == (have && epl != 0));  // sub_1A9400 is not emitted here: the run stops at the call
        if (a.hand.stopped) CHECK(a.hand.stop_pc == 0x1A9400u);
        const PairOut b = pair(m, PAIR(fn_sub_1C0110_001c0110), Args{}, rng(), "sub_1C0110");
        CHECK(b.hand.stopped == (have && epl != 0));
        if (b.hand.stopped) {
            CHECK(b.hand.stop_pc == 0x1A91B0u);
            const u32 pos = static_cast<u32>(b.hand.end.gpr[GPR_A1].u64[0]);  // &pos, zeroed
            CHECK(pos == kSp - 48 + 32);
        }
    }
}

TEST_CASE("game(field_hi): the task-work setters and getters equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D103u};
    struct Setter {
        Fn hand, recomp;
        const char* what;
        u32 off;
        bool checked;
    };
    const Setter setters[] = {
        {PAIR(fn_sub_1C2000_001c2000), "sub_1C2000", 516, false}, {PAIR(fn_sub_1CD790_001cd790), "sub_1CD790", 0, false},
        {PAIR(fn_sub_1DD5E0_001dd5e0), "sub_1DD5E0", 0, false},   {PAIR(fn_sub_1DD5F0_001dd5f0), "sub_1DD5F0", 548, false},
        {PAIR(fn_sub_1CD650_001cd650), "sub_1CD650", 4, true},    {PAIR(fn_sub_1CD670_001cd670), "sub_1CD670", 8, true},
        {PAIR(fn_sub_1D37F0_001d37f0), "sub_1D37F0", 4, true},    {PAIR(fn_sub_1D3810_001d3810), "sub_1D3810", 8, true},
    };
    for (int it = 0; it < 40; ++it) {
        for (const Setter& s : setters) {
            make_task(m, rng);
            const bool null_task = s.checked && it % 4 == 0;
            const u64 task = null_task ? (it % 8 == 0 ? 0u : static_cast<u64>(rng()) << 32) : arg64(rng, kTask);
            const u32 value = word(rng);
            const PairOut p = pair(m, s.hand, s.recomp, Args{task, arg64(rng, value)}, rng(), s.what);
            if (static_cast<u32>(task) == kTask) CHECK(get32(m, kWork + s.off) == value);
            CHECK(p.hand.snaps.size() == 1u);  // the entry check point only
        }
        // The footstep setter also copies $gp-19432.
        make_task(m, rng);
        put32(m, kGpVa(kGpFootstepFrame), word(rng));
        const u64 ft = it % 5 == 0 ? 0u : arg64(rng, kTask);
        const u32 fv = word(rng);
        pair(m, PAIR(fn_sub_1DA000_001da000), Args{ft, sx(fv)}, rng(), "sub_1DA000");
        if (ft != 0) {
            CHECK(get32(m, kWork + 4) == fv);
            CHECK(get32(m, kWork + 12) == get32(m, kGpVa(kGpFootstepFrame)));
        }
        // The plain getters.
        make_task(m, rng);
        const PairOut g1 = pair(m, PAIR(fn_sub_1D5C00_001d5c00), Args{arg64(rng, kTask)}, rng(), "sub_1D5C00");
        CHECK(g1.hand.v0() == sx(get32(m, kWork + 8)));
        const PairOut g2 = pair(m, PAIR(fn_sub_1D8D50_001d8d50), Args{arg64(rng, kTask)}, rng(), "sub_1D8D50");
        CHECK(g2.hand.v0() == sx(get32(m, kWork + 16)));
        const PairOut g3 = pair(m, PAIR(fn_sub_1D5E10_001d5e10), Args{arg64(rng, kTask)}, rng(), "sub_1D5E10");
        CHECK(static_cast<u32>(g3.hand.v0()) == get32(m, kWork + 12) + 64u);
        const u32 n = rng() % 8;
        const PairOut g4 = pair(m, PAIR(fn_sub_1D8D60_001d8d60), Args{arg64(rng, kTask), arg64(rng, n)}, rng(), "sub_1D8D60");
        CHECK(g4.hand.v0() == sx(get32(m, kWork + 24 + 4 * n)));
        put32(m, kWork + 64, it % 3 == 0 ? 1u : word(rng));
        const PairOut g5 = pair(m, PAIR(fn_sub_1E1820_001e1820), Args{arg64(rng, kTask)}, rng(), "sub_1E1820");
        CHECK(g5.hand.v0() == (get32(m, kWork + 64) == 1u ? 1u : 0u));
        put32(m, kWork + 0, word(rng));
        const u64 ftask = it % 6 == 0 ? 0u : arg64(rng, kTask);
        const PairOut g6 = pair(m, PAIR(fn_sub_1D9FD0_001d9fd0), Args{ftask}, rng(), "sub_1D9FD0");
        CHECK(g6.hand.v0() == (ftask == 0 ? 1u : (static_cast<s32>(get32(m, kWork)) > 0 ? 1u : 0u)));
    }
}

TEST_CASE("game(field_hi): the global words and the hero test equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D104u};
    for (int it = 0; it < 60; ++it) {
        put32(m, kGpVa(kGpLiveEcCount), word(rng));
        const PairOut a = pair(m, PAIR(fn_sub_1D0E40_001d0e40), Args{}, rng(), "sub_1D0E40");
        CHECK(a.hand.v0() == sx(get32(m, kGpVa(kGpLiveEcCount))));
        const u32 v = word(rng);
        pair(m, PAIR(fn_sub_1D5130_001d5130), Args{arg64(rng, v)}, rng(), "sub_1D5130");
        CHECK(get32(m, kGpVa(kGpCameraWord)) == v);
        const PairOut c = pair(m, PAIR(fn_sub_1E1840_001e1840), Args{}, rng(), "sub_1E1840");
        CHECK(c.hand.v0() == 0x7CE2B8u);
        // The hero: unit == 0x8717A0 as a whole register.
        const u32 picks[] = {kPcUnits, kPcUnits + kUnitSize, kEcUnits, 0u};
        const u32 low = picks[it % 4];
        const u64 unit = it % 3 == 0 ? (static_cast<u64>(rng() | 1u) << 32) | low : sx(low);
        const PairOut d = pair(m, PAIR(fn_K_FldEvent_IsUnitHero_001c7b10), Args{unit}, rng(), "K_FldEvent_IsUnitHero");
        CHECK(d.hand.v0() == (unit == kPcUnits ? 1u : 0u));
    }
}

TEST_CASE("game(field_hi): the pad-script scene rule equals its recompiled body and 26_field.md's list") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D105u};
    put32(m, kSceneSlot, kRec);
    auto rule = [](s32 major, s32 minor) {
        const s32 majors[] = {4, 5, 6, 7, 8, 9, 10, 12, 14, 33, 39};
        for (s32 x : majors)
            if (major == x) return 0u;
        if ((major == 26 && (minor == 51 || minor == 52 || minor == 53)) || (major == 27 && minor == 50) ||
            (major == 32 && (minor == 1 || minor == 2)) || (major == 35 && minor == 1) || (major == 37 && minor == 1))
            return 0u;
        return 1u;
    };
    int off = 0;
    for (s32 major = -2; major <= 80; ++major) {
        for (const s32 minor : {0, 1, 2, 3, 50, 51, 52, 53, -1}) {
            put32(m, kRec + 0, static_cast<u32>(major));
            put32(m, kRec + 4, static_cast<u32>(minor));
            const PairOut p = pair(m, PAIR(fn_sub_1C6080_001c6080), Args{}, rng(), "sub_1C6080");
            CHECK(p.hand.v0() == rule(major, minor));
            off += rule(major, minor) == 0;
        }
    }
    CHECK(off == 11 * 9 + 8);
    // The pop-scheduler idle test: field 14/5, or work state 2.
    for (int it = 0; it < 80; ++it) {
        make_task(m, rng);
        const s32 major = it % 3 == 0 ? 14 : static_cast<s32>(rng() % 60);
        const s32 minor = it % 2 == 0 ? 5 : static_cast<s32>(rng() % 8);
        put32(m, kRec + 0, static_cast<u32>(major));
        put32(m, kRec + 4, static_cast<u32>(minor));
        const u32 state = it % 4 == 0 ? 2u : word(rng);
        put32(m, kWork + 0, state);
        const PairOut p = pair(m, PAIR(fn_sub_1D3790_001d3790), Args{arg64(rng, kTask)}, rng(), "sub_1D3790");
        CHECK(p.hand.v0() == (((major == 14 && minor == 5) || state == 2u) ? 1u : 0u));
    }
}

TEST_CASE("game(field_hi): the Reaper timer and the turn speed equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D106u};
    for (int it = 0; it < 120; ++it) {
        make_task(m, rng);
        const u32 limit = it % 3 == 0 ? rng() % 2000 : word(rng);
        const u32 frames = it % 3 == 0 ? rng() % 60000 : word(rng);
        put32(m, kWork + 12, limit);
        put32(m, kWork + 16, frames);
        const PairOut p = pair(m, PAIR(fn_sub_1D38A0_001d38a0), Args{arg64(rng, kTask)}, rng(), "sub_1D38A0");
        const s32 left = static_cast<s32>(limit - frames / 30u);
        CHECK(p.hand.v0() == sx(static_cast<u32>(left < 0 ? 0 : left)));
    }
    const float speeds[] = {0.0f, -0.0f, 1.5f, -2.0f, 1e-40f, -1e-40f, 1e30f};
    for (int it = 0; it < 60; ++it) {
        const float s = it < 7 ? speeds[it] : static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 100.0f;
        putf(m, kGpVa(kGpPadTurnSpeed), s);
        putf(m, kGpVa(kGpPadTurnDefault), static_cast<float>(rng() % 100) / 10.0f);
        const PairOut p = pair(m, PAIR(fn_sub_1E13C0_001e13c0), Args{}, rng(), "sub_1E13C0");
        if (s > 1e-30f) CHECK(p.hand.f0() == get32(m, kGpVa(kGpPadTurnSpeed)));
        if (s < -1e-30f) CHECK(p.hand.f0() == get32(m, kGpVa(kGpPadTurnDefault)));
    }
}

TEST_CASE("game(field_hi): the list lookups and the encounter pause equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D107u};
    for (int it = 0; it < 120; ++it) {
        const bool npc = it % 2 == 0;
        const s32 head = npc ? kGpNpcList : kGpObjList;
        const u32 id_off = npc ? 8 : 80, next_off = npc ? 108 : 88;
        const int len = static_cast<int>(rng() % 7);
        std::vector<u16> ids;
        for (int k = 0; k < len; ++k) {
            const u32 node = obj(k);
            zero(m, node, 0x200);
            const u16 id = static_cast<u16>(rng() % 3 == 0 ? rng() : rng() % 12);
            ids.push_back(id);
            put16(m, node + id_off, id);
            put32(m, node + next_off, k + 1 < len ? obj(k + 1) : 0u);
        }
        put32(m, kGpVa(head), len ? obj(0) : 0u);
        const u16 want = len && rng() % 2 ? ids[rng() % len] : static_cast<u16>(rng() % 12);
        const u64 a0 = (static_cast<u64>(rng()) << 32) | (rng() & 0xFFFF0000u) | want;  // only the low 16 bits count
        const PairOut p = npc ? pair(m, PAIR(fn_sub_1E2810_001e2810), Args{a0}, rng(), "sub_1E2810")
                              : pair(m, PAIR(fn_sub_1E29E0_001e29e0), Args{a0}, rng(), "sub_1E29E0");
        u32 expect = 0;
        for (int k = 0; k < len; ++k)
            if (ids[k] == want) {
                expect = obj(k);
                break;
            }
        CHECK(static_cast<u32>(p.hand.v0()) == expect);
    }
    for (int it = 0; it < 60; ++it) {
        for (int k = 0; k < 3; ++k) {
            const bool live = rng() % 3 != 0;
            put32(m, kBattleKosakaTasks + 4 * k, live ? task2(k) : 0u);
            zero(m, task2(k), 0x100);
            put32(m, task2(k) + 60, obj(k));
            fill(m, obj(k), 16, rng);
        }
        const u32 v = word(rng);
        pair(m, PAIR(fn_sub_1D8C60_001d8c60), Args{arg64(rng, v)}, rng(), "sub_1D8C60");
        for (int k = 0; k < 3; ++k)
            if (get32(m, kBattleKosakaTasks + 4 * k)) CHECK(get32(m, obj(k) + 8) == v);
    }
}

TEST_CASE("game(field_hi): the party-slot helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D108u};
    StopAt stop{0x3174E0u, 0x3B2CB0u};  // the model release / the string draw: stopped at, as when not emitted
    for (int it = 0; it < 80; ++it) {
        clear_units(m);
        fill(m, kPcUnits, kUnitSize * kPcUnitCount, rng);
        fill(m, kPcModelSlots, 32, rng);
        u32 free_unit = 0;
        for (u32 i = 0; i < kPcUnitCount; ++i) {
            const bool used = rng() % 3 != 0;
            put32(m, unit_va(true, i) + kUnitInstance, used ? 0x01500000u + i : 0u);
            if (!used && free_unit == 0) free_unit = unit_va(true, i);
        }
        const PairOut a = pair(m, PAIR(fn_sub_1CD940_001cd940), Args{}, rng(), "sub_1CD940");
        CHECK(static_cast<u32>(a.hand.v0()) == free_unit);
        pair(m, PAIR(fn_sub_1CD8E0_001cd8e0), Args{}, rng(), "sub_1CD8E0");
        for (u32 i = 0; i < kPcUnitCount; ++i) {
            CHECK(get32(m, unit_va(true, i) + kUnitActiveFlag) == 1u);
            CHECK(get32(m, kPcModelSlots + 8 * i + 4) == 0u);
        }
        // Free a party model: the release (sub_3174E0) is not emitted here, so a set handle stops the run at it.
        fill(m, kPcModelSlots, 32, rng);
        const u32 slot = rng() % 4;
        if (it % 3 == 0) put32(m, kPcModelSlots + 8 * slot + 4, 0);
        const PairOut b = pair(m, PAIR(fn_sub_1CD870_001cd870), Args{arg64(rng, slot)}, rng(), "sub_1CD870");
        CHECK(b.hand.stopped == (get32(m, kPcModelSlots + 8 * slot + 4) != 0));
        // The draw-command update: always reaches sub_3B2CB0 (not emitted) with the eight arguments and $f12 = 0.
        make_task(m, rng);
        const PairOut c = pair(m, PAIR(fn_sub_1CD690_001cd690), Args{arg64(rng, kTask)}, rng(), "sub_1CD690");
        CHECK(c.hand.stopped);
        CHECK(c.hand.stop_pc == 0x3B2CB0u);
        CHECK(c.hand.end.fpr[12] == 0u);
        CHECK(c.hand.end.gpr[GPR_A0].u64[0] == 320u);
        CHECK(c.hand.end.gpr[GPR_A0 + 5].u64[0] == sx(get32(m, kWork)));  // $t1 = work[0]
    }
}

TEST_CASE("game(field_hi): the level-gap rule equals its recompiled body (flag 3173, party average, table)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D109u};
    // The table rows {s16 level, s16 gap} at 0x6836B0, from the ELF.
    std::vector<std::pair<s16, s16>> rows;
    for (u32 va = kLevelGapTable;; va += 4) {
        const s16 lv = static_cast<s16>(get16(m, va));
        if (lv == -1 || rows.size() > 200) break;
        rows.emplace_back(lv, static_cast<s16>(get16(m, va + 2)));
    }
    CHECK(!rows.empty());
    int ones = 0, zeros = 0;
    for (int it = 0; it < 200; ++it) {
        clear_units(m);
        const bool flag = it % 7 == 0;
        u32 w = get32(m, kFlagWord3173);
        w = flag ? (w | (1u << (3173 & 31))) : (w & ~(1u << (3173 & 31)));
        put32(m, kFlagWord3173, w);
        s32 sum = 0, cnt = 0;
        for (u32 i = 0; i < kPcUnitCount; ++i) {
            const u32 u = unit_va(true, i);
            const bool live = it % 11 == 1 ? false : rng() % 4 != 0;
            put32(m, u + kUnitInstance, live || rng() % 3 == 0 ? 0x01500000u : 0u);
            put32(m, u + kUnitResource, live ? obj(1) : (rng() % 2 ? obj(2) : 0u));
            const s32 lv = static_cast<s32>(rng() % 100);
            put32(m, u + kUnitLevel, static_cast<u32>(lv));
            if (get32(m, u + kUnitInstance) && get32(m, u + kUnitResource)) {
                sum += lv;
                ++cnt;
            }
        }
        const u32 unit = rng() % 2 ? obj(3) : unit_va(true, rng() % 4);
        if (unit == obj(3)) put32(m, unit + kUnitLevel, rng() % 100);
        const s32 own = static_cast<s32>(get32(m, unit + kUnitLevel));
        const PairOut p = pair(m, PAIR(fn_sub_1C65E0_001c65e0), Args{arg64(rng, unit)}, rng(), "sub_1C65E0");
        if (flag) {
            CHECK(p.hand.v0() == 1u);
        } else if (cnt > 0) {
            const s32 avg = sum / cnt;
            u32 expect = 1;
            for (const auto& [lv, gap] : rows)
                if (lv >= avg) {
                    expect = (avg - own) < gap ? 1u : 0u;
                    break;
                }
            CHECK(p.hand.v0() == expect);
        }
        (p.hand.v0() ? ones : zeros)++;
    }
    CHECK(ones > 10);
}

TEST_CASE("game(field_hi): the party-unit walks with emitted callees equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D10Au};
    for (int it = 0; it < 60; ++it) {
        // sub_1CE880: five animation slots per live unit through the model's +952 table (sub_319230 runs).
        clear_units(m);
        zero(m, kObjs, 0x10000);
        random_units(m, rng, true, 60);
        for (u32 i = 0; i < kPcUnitCount; ++i) {
            const u32 u = unit_va(true, i);
            const u32 model = obj(16 + static_cast<int>(i));  // 0x200 bytes are not enough for +952 + 60: use 2 slots
            put32(m, u + kUnitModel, model);
            for (u32 k = 0; k < 5; ++k) {
                put16(m, u + kUnitAnimIds + 2 * k, static_cast<u16>(rng()));
                put32(m, model + 952 + 12 * k, rng() % 3 ? obj(24 + static_cast<int>(k)) : 0u);
            }
        }
        pair(m, PAIR(fn_sub_1CE880_001ce880), Args{}, rng(), "sub_1CE880");
        // sub_1D1860: sub_19C2F0(resource[+484], arg) -> (+484 task)->work +4 = arg.
        clear_units(m);
        random_units(m, rng, true, 60);
        for (int k = 0; k < 16; ++k) {
            zero(m, obj(k), 0x200);
            put32(m, obj(k) + 484, task2(k));
            zero(m, task2(k), 0x100);
            put32(m, task2(k) + 60, task2(k) + 0x80);
        }
        const u32 arg = word(rng);
        pair(m, PAIR(fn_sub_1D1860_001d1860), Args{arg64(rng, arg)}, rng(), "sub_1D1860");
        for (u32 i = 0; i < kPcUnitCount; ++i) {
            const u32 u = unit_va(true, i);
            if (get32(m, u + kUnitInstance) && get32(m, u + kUnitResource)) {
                const u32 t = get32(m, get32(m, u + kUnitResource) + 484);
                CHECK(get32(m, t + 0x80 + 4) == arg);
            }
        }
        // sub_1D0270: kwln flag 32 on every unit's +364 task (kwlnTaskSetFlags -> kwlnTaskSetFlagsByMode: task +28 |= 32).
        clear_units(m);
        for (int k = 0; k < 28; ++k) {
            zero(m, task2(k), 0x100);
            put32(m, task2(k) + 28, rng());
        }
        for (u32 i = 0; i < kPcUnitCount + kEcUnitCount; ++i) {
            const bool pc = i < kPcUnitCount;
            const u32 u = unit_va(pc, pc ? i : i - kPcUnitCount);
            put32(m, u + kUnitTask364, rng() % 3 ? task2(static_cast<int>(i)) : 0u);
        }
        pair(m, PAIR(fn_sub_1D0270_001d0270), Args{}, rng(), "sub_1D0270");
        for (int k = 0; k < 28; ++k) {
            const bool pc = k < 4;
            const u32 u = unit_va(pc, pc ? static_cast<u32>(k) : static_cast<u32>(k - 4));
            if (get32(m, u + kUnitTask364)) CHECK((get32(m, task2(k) + 28) & 32u) != 0);
        }
        // sub_1D1A90 / sub_1D1CE0: kwlnTaskExists on the +380 tasks; stale handles cleared.
        for (const bool pc : {true, false}) {
            clear_units(m);
            random_units(m, rng, pc, 50);
            const u32 n = pc ? kPcUnitCount : kEcUnitCount;
            put32(m, kKwlnList0, 0);
            put32(m, kKwlnList0 + 12, 0);
            put32(m, kKwlnList0 + 24, 0);
            int listed = 0;
            for (u32 i = 0; i < n; ++i) {
                const u32 t = task2(static_cast<int>(i));
                zero(m, t, 0x100);
                put32(m, unit_va(pc, i) + kUnitTask380, rng() % 4 ? t : 0u);
                if (rng() % 3 == 0 && listed < 3) {  // in one of the kernel's lists
                    put32(m, t + 64, get32(m, kKwlnList0 + 12u * (listed % 3)));
                    put32(m, kKwlnList0 + 12u * (listed % 3), t);
                    ++listed;
                }
            }
            const PairOut p = pc ? pair(m, PAIR(fn_sub_1D1A90_001d1a90), Args{}, rng(), "sub_1D1A90")
                                 : pair(m, PAIR(fn_sub_1D1CE0_001d1ce0), Args{}, rng(), "sub_1D1CE0");
            CHECK(p.hand.v0() <= 1u);
        }
    }
}

TEST_CASE("game(field_hi): the unit walks reach their (not emitted) callees with the original state") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D10Bu};
    // the fade / release / model callees the walks reach: stopped at, as when they were not emitted
    StopAt stop{0x1A60D0u, 0x1D1640u, 0x316E00u, 0x316F70u};
    struct Walk {
        Fn hand, recomp;
        const char* what;
        bool pc;
        u32 callee;
        bool instance_only;  // sub_1D11B0 / sub_1D12D0 test +72 only
    };
    const Walk walks[] = {
        {PAIR(fn_sub_1D1910_001d1910), "sub_1D1910", true, 0x1A60D0u, false},
        {PAIR(fn_sub_1D19D0_001d19d0), "sub_1D19D0", true, 0x1A60D0u, false},
        {PAIR(fn_sub_1D1B60_001d1b60), "sub_1D1B60", false, 0x1A60D0u, false},
        {PAIR(fn_sub_1D1C20_001d1c20), "sub_1D1C20", false, 0x1A60D0u, false},
        {PAIR(fn_sub_1D11B0_001d11b0), "sub_1D11B0", false, 0x316E00u, true},
        {PAIR(fn_sub_1D12D0_001d12d0), "sub_1D12D0", false, 0x316F70u, true},
        {PAIR(fn_sub_1D1780_001d1780), "sub_1D1780", true, 0x1D1640u, false},
        {PAIR(fn_sub_1D17F0_001d17f0), "sub_1D17F0", false, 0x1D1640u, false},
    };
    for (int it = 0; it < 40; ++it) {
        for (const Walk& w : walks) {
            clear_units(m);
            const u32 n = w.pc ? kPcUnitCount : kEcUnitCount;
            // Sparse live units, so the first call lands on varying indices; sometimes none at all.
            const int p = it % 5 == 0 ? 0 : static_cast<int>(100 / n + rng() % 20);
            random_units(m, rng, w.pc, p, w.instance_only);
            for (u32 i = 0; i < n; ++i) {
                const u32 u = unit_va(w.pc, i);
                put32(m, u + kUnitModel, obj(static_cast<int>(i % 16)));
                put32(m, u + kUnitTask380, rng());
                put32(m, u + kUnitModelKind, rng() % 3 ? rng() % 7 : rng());
            }
            const u64 arg = arg64(rng, it % 3 ? 0u : word(rng));
            const PairOut r = pair(m, w.hand, w.recomp, Args{arg}, rng(), w.what);
            if (r.hand.stopped) CHECK(r.hand.stop_pc == w.callee);
        }
    }
    // sub_1D11B0's kind -> model argument mapping at the call: 1/5 -> 1, 2 -> 2, 3 -> 4, 4 -> 3.
    for (const s32 kind : {1, 2, 3, 4, 5, 6, 0, -1}) {
        clear_units(m);
        const u32 i = rng() % kEcUnitCount;
        put32(m, unit_va(false, i) + kUnitInstance, 0x01500000u);
        put32(m, unit_va(false, i) + kUnitModelKind, static_cast<u32>(kind));
        const PairOut r = pair(m, PAIR(fn_sub_1D11B0_001d11b0), Args{}, rng(), "sub_1D11B0(kind)");
        const bool calls = kind >= 1 && kind <= 5;
        CHECK(r.hand.stopped == calls);
        if (calls) {
            const u64 expect = kind == 1 || kind == 5 ? 1u : kind == 2 ? 2u : kind == 3 ? 4u : 3u;
            CHECK(r.hand.end.gpr[GPR_A0].u64[0] == 8u);
            CHECK(r.hand.end.gpr[GPR_A1].u64[0] == expect);
        }
    }
}

TEST_CASE("game(field_hi): the camera target setter equals its recompiled body (type-1 ids through MT_Scene_GetRes)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1E1D10Cu};
    put32(m, kSceneSlot, kRec);
    for (int it = 0; it < 120; ++it) {
        make_task(m, rng);
        zero(m, kRec, 64);
        zero(m, obj(0), 0x200);
        // The resource manager: 22 list heads; type 1 holds a short list of {u16 id, ..., +248 next}.
        const bool mgr = it % 4 != 0;
        put32(m, kRec + 8, mgr ? obj(0) : 0u);
        const int len = static_cast<int>(rng() % 4);
        std::vector<u16> ids;
        for (int k = 0; k < len; ++k) {
            const u32 node = obj(4 + 2 * k);  // 0x400 apart: +248 fits
            zero(m, node, 0x400);
            const u16 id = static_cast<u16>(0x400 + rng() % 8);
            ids.push_back(id);
            put16(m, node, id);
            put32(m, node + 248, k + 1 < len ? obj(4 + 2 * (k + 1)) : 0u);
        }
        put32(m, obj(0) + 4, len ? obj(4) : 0u);
        const u32 low = it % 3 == 0 ? static_cast<u32>(rng()) : 0x400u + rng() % 8;
        const u64 id = arg64(rng, low);
        const u32 before = rng();
        put32(m, kWork + 204, before);
        const PairOut p = pair(m, PAIR(fn_sub_1D5F30_001d5f30), Args{arg64(rng, kTask), id}, rng(), "sub_1D5F30");
        const bool type1 = ((static_cast<u32>(id) & 0xFFFFu) >> 10) == 1;
        if (!type1) CHECK(get32(m, kWork + 204) == before);
        if (type1 && !mgr) CHECK(get32(m, kWork + 204) == 0u);
        CHECK(!p.hand.stopped);
    }
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
