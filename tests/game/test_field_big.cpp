// Phase 5 pair tests for the field layer's larger functions (game/src/field/field_big.cpp): each hand-written function
// and the recompiled body it replaces run on identical guest machines on randomised inputs, and EVERYTHING observable
// is compared:
//   * the whole register file (GPRs in 128 bits, HI/LO, SA, the FPRs, ACC, FCR31) and the cycle count at every check
//     point -- the function's own and those of the callees it reaches (a check point may preempt the thread, and the
//     kernel then stores the register file in guest memory) -- and at the return;
//   * guest memory: all 32 MiB of main RAM through a PairRange (write_tracker.h: only the pages written are copied and
//     compared; it holds .data/.bss with sField, the field units, the gp globals and the scene record, the test arena
//     0x1800000..0x1820000 and the stack with the frames, spills and the dead stack), both bodies from the same RAM;
//   * the bus log length, syscall and trap counts.
// Callees that are kept recompiled but not emitted in this test build (the sound driver, the calendar) end the run
// through rt::missing_function: the hooks snapshot the register file and memory AT that call before the stop unwinds,
// so both bodies must reach the same callee with the same state. The documented rules (docs/ANALYSIS/26_field.md and
// game/include/p3fes/game/field_big.h) are checked on the host, independently of both bodies.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/field_big.h"

#include <algorithm>
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
P3FES_DECL_PAIR(fn_sub_19C2F0_0019c2f0)
P3FES_DECL_PAIR(fn_sub_19C300_0019c300)
P3FES_DECL_PAIR(fn_sub_19C310_0019c310)
P3FES_DECL_PAIR(fn_sub_19C490_0019c490)
P3FES_DECL_PAIR(fn_sub_1A4770_001a4770)
P3FES_DECL_PAIR(fn_sub_1A4780_001a4780)
P3FES_DECL_PAIR(fn_sub_1A47B0_001a47b0)
P3FES_DECL_PAIR(fn_sub_1B01B0_001b01b0)
P3FES_DECL_PAIR(fn_sub_1B01D0_001b01d0)
P3FES_DECL_PAIR(fn_sub_1B0230_001b0230)
P3FES_DECL_PAIR(fn_sub_1B0250_001b0250)
P3FES_DECL_PAIR(fn_sub_1C0880_001c0880)
P3FES_DECL_PAIR(fn_sub_1C0960_001c0960)
P3FES_DECL_PAIR(fn_sub_1BAB60_001bab60)
P3FES_DECL_PAIR(fn_sub_1BD950_001bd950)
P3FES_DECL_PAIR(fn_sub_1B6EB0_001b6eb0)
P3FES_DECL_PAIR(fn_sub_1A9850_001a9850)
P3FES_DECL_PAIR(fn_sub_1AA1B0_001aa1b0)
P3FES_DECL_PAIR(fn_sub_1BC630_001bc630)
P3FES_DECL_PAIR(fn_sub_1AD940_001ad940)
P3FES_DECL_PAIR(fn_sub_1ADD40_001add40)
P3FES_DECL_PAIR(fn_sub_1ADFF0_001adff0)
P3FES_DECL_PAIR(fn_K_FldFrame_HandleCollis_001ac750)
P3FES_DECL_PAIR(fn_sub_1D38D0_001d38d0)
P3FES_DECL_PAIR(fn_sub_1D3830_001d3830)
P3FES_DECL_PAIR(fn_K_Unit_UpdateEnemyPopSchedulerTask_001d32a0)
P3FES_DECL_PAIR(fn_sub_1C7130_001c7130)
P3FES_DECL_PAIR(fn_sub_1D5140_001d5140)
P3FES_DECL_PAIR(fn_sub_1E13F0_001e13f0)
P3FES_DECL_PAIR(fn_K_FldEvent_FindFldHitAt_001c5ee0)
P3FES_DECL_PAIR(fn_K_FldEvent_IsUnitNearFldHit_001c7b30)
P3FES_DECL_PAIR(fn_sub_1D0720_001d0720)
P3FES_DECL_PAIR(fn_sub_1E1590_001e1590)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::fldbig;

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

// Hooks: a register snapshot at every check point; rt::missing_function (a callee not emitted in this build) snapshots
// the register file at the call before it unwinds (memory is compared after the run: nothing writes it after the stop).
class FullHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    Machine* m = nullptr;
    std::vector<Snap> snaps;
    int syscalls = 0, traps = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop{};

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
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
    void vu_control_write(EEContext&, u32, u32) override {}
};

struct Run {
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap end{};
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
    } catch (const rt_test::FatalEvent&) {
        r.stopped = true;
        r.stop_pc = h.stop_pc;
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

int g_pairs = 0;

// A stand-in that ends the run at the callee the way a function this build does not emit does (rt::missing_function):
// the checks on the state at the call (stop pc, $a0.., $ra) hold whether the callee is recompiled or replaced, since
// the hooked forwarders ask the stand-ins first (finalA replaced the sound, collision and shadow callees these cases
// stop at). Installed for the scope of a case.
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
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    PairOut p;
    p.hand = run_one(m, hand, args, seed, prep);
    ram.between();
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
    {
        const std::size_t first = ram.first_difference();
        const std::size_t at = first < ram.size() ? first : 0;
        INFO("memory: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(at)) << " recomp "
                                               << unsigned(m.mem.main_ram()[at]));
        CHECK(first == ram.size());
    }
    CHECK(p.hand.bus == p.recomp.bus);
    CHECK(p.hand.syscalls == p.recomp.syscalls);
    CHECK(p.hand.traps == p.recomp.traps);
    return p;
}

// --- fixtures ------------------------------------------------------------------------------------------------------
constexpr u32 gpva(s32 off) { return kGp + static_cast<u32>(off); }

constexpr u32 kTask = 0x01800000u;   // a kwln task record (+60 = the work)
constexpr u32 kWork = 0x01800400u;   // its work (0x800 bytes)
constexpr u32 kObjs = 0x01804000u;   // objects / list nodes, 0x200 bytes apart (up to 0x01810000)
constexpr u32 kBuf = 0x01812000u;    // argument buffers

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
float getf(const Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.mem.main_ram() + va, 4);
    return f;
}
void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void zero(Machine& m, u32 va, u32 len) { std::memset(m.at(va), 0, len); }
u32 obj(int i) { return kObjs + 0x200u * static_cast<u32>(i); }

// A task record with a random work.
void make_task(Machine& m, std::mt19937& rng) {
    zero(m, kTask, 0x68);
    put32(m, kTask + 60, kWork);
    fill(m, kWork, 0x800, rng);
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
u64 arg64(std::mt19937& rng, u32 low) { return rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | low : sx(low); }
// A finite float of moderate size (sometimes 0 / negative / large).
float rfloat(std::mt19937& rng) {
    switch (rng() % 5) {
    case 0: return 0.0f;
    case 1: return static_cast<float>(rng() % 256);
    case 2: return -static_cast<float>(rng() % 1000) / 7.0f;
    default: return static_cast<float>(static_cast<s32>(rng() % 200000) - 100000) / 64.0f;
    }
}

// ======================================================================================================================
// Leaves
// ======================================================================================================================

TEST_CASE("game(field_big): the leaf setters / getters equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16001u};
    struct Setter {
        Fn hand, recomp;
        const char* what;
        u32 off, size;
    };
    const Setter setters[] = {
        {PAIR(fn_sub_19C2F0_0019c2f0), "sub_19C2F0", 4, 4},    {PAIR(fn_sub_19C310_0019c310), "sub_19C310", 10, 2},
        {PAIR(fn_sub_1A4770_001a4770), "sub_1A4770", 0, 4},    {PAIR(fn_sub_1B0230_001b0230), "sub_1B0230", 28, 4},
        {PAIR(fn_sub_1B0250_001b0250), "sub_1B0250", 1204, 4},
    };
    for (int it = 0; it < 60; ++it) {
        for (const Setter& s : setters) {
            make_task(m, rng);
            const u32 v = word(rng);
            pair(m, s.hand, s.recomp, Args{arg64(rng, kTask), arg64(rng, v)}, rng(), s.what);
            if (s.size == 4) CHECK(get32(m, kWork + s.off) == v);
            if (s.size == 2) CHECK(get16(m, kWork + s.off) == static_cast<u16>(v));
        }
        make_task(m, rng);
        const PairOut g = pair(m, PAIR(fn_sub_19C300_0019c300), Args{arg64(rng, kTask)}, rng(), "sub_19C300");
        CHECK(g.hand.v0() == get16(m, kWork + 10));
        // sub_19C490: the f32 behind work +76, or 0.0 for NULL.
        make_task(m, rng);
        const bool null = it % 3 == 0;
        put32(m, kWork + 76, null ? 0u : obj(1));
        putf(m, obj(1), rfloat(rng));
        const PairOut f = pair(m, PAIR(fn_sub_19C490_0019c490), Args{arg64(rng, kTask)}, rng(), "sub_19C490");
        CHECK(f.hand.f0() == (null ? 0u : get32(m, obj(1))));
        // sub_1A4780 / sub_1A47B0: the camera point's position and colour.
        make_task(m, rng);
        fill(m, kBuf, 16, rng);
        pair(m, PAIR(fn_sub_1A4780_001a4780), Args{arg64(rng, kTask), arg64(rng, kBuf)}, rng(), "sub_1A4780");
        CHECK(std::memcmp(m.at(kWork + 4), m.at(kBuf), 12) == 0);
        make_task(m, rng);
        pair(m, PAIR(fn_sub_1A47B0_001a47b0), Args{arg64(rng, kTask), arg64(rng, kBuf + 1)}, rng(), "sub_1A47B0");
        CHECK(std::memcmp(m.at(kWork + 16), m.at(kBuf + 1), 4) == 0);
        // The enemy-think queue entry address / copy.
        make_task(m, rng);
        const u32 i = it < 4 ? static_cast<u32>(it) : rng() % 47;
        const PairOut q = pair(m, PAIR(fn_sub_1B01B0_001b01b0), Args{arg64(rng, kTask), arg64(rng, i)}, rng(), "sub_1B01B0");
        CHECK(static_cast<u32>(q.hand.v0()) == kWork + 32 + 24 * i);
        make_task(m, rng);
        fill(m, kBuf, 24, rng);
        pair(m, PAIR(fn_sub_1B01D0_001b01d0), Args{arg64(rng, kTask), arg64(rng, i), arg64(rng, kBuf)}, rng(), "sub_1B01D0");
        CHECK(std::memcmp(m.at(kWork + 32 + 24 * i), m.at(kBuf), 24) == 0);
    }
}

// ======================================================================================================================
// The transparent-wall fades
// ======================================================================================================================

TEST_CASE("game(field_big): the wall fade callbacks equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16002u};
    for (int it = 0; it < 400; ++it) {
        // sub_1C0880: the f32 at target +24.
        make_task(m, rng);
        const u32 state = it % 7 == 0 ? 2u : rng() % 3 == 0 ? 1u : 0u;
        const s32 frames = it % 5 == 0 ? -static_cast<s32>(rng() % 3) : static_cast<s32>(rng() % 40);
        const float end = rfloat(rng), value = rfloat(rng);
        put32(m, kWork + kFadeState, state);
        put32(m, kWork + kFadeTarget, obj(0));
        put32(m, kWork + kFadeFrames, static_cast<u32>(frames));
        putf(m, kWork + kFadeEnd, end);
        putf(m, obj(0) + 24, value);
        const PairOut a = pair(m, PAIR(fn_sub_1C0880_001c0880), Args{arg64(rng, kTask)}, rng(), "sub_1C0880");
        CHECK(a.hand.v0() == (state == 1 ? ~0ull : 0ull));
        if (state == 0 && frames <= 0) {
            CHECK(getf(m, obj(0) + 24) == end);  // the last step lands on the end value
            CHECK(get32(m, kWork + kFadeState) == 1u);
        }
        if (state == 0 && frames > 0) CHECK(get32(m, kWork + kFadeFrames) == static_cast<u32>(frames - 1));

        // sub_1C0960: a wall resource -> model (+260) with its colour at +208 and the material table at +224.
        make_task(m, rng);
        put32(m, kWork + kFadeState, state);
        put32(m, kWork + kFadeTarget, obj(1));
        put32(m, kWork + kFadeFrames, static_cast<u32>(frames));
        putf(m, kWork + kFadeEnd, static_cast<float>(rng() % 300));  // alpha targets 0..299 (>= 256 wraps as the u8 store)
        put32(m, obj(1) + 260, obj(2));
        fill(m, obj(2) + 208, 4, rng);
        put32(m, obj(2) + 224, obj(3));
        // nine material lists, 0..3 nodes each (nodes from obj(4) on, 0x40 apart; +40 next, +24 f32 alpha)
        u32 next_node = obj(4);
        for (u32 list = 8; list <= 40; list += 4) {
            const u32 n = rng() % 4;
            u32 link = obj(3) + list;  // where the next node's address goes
            put32(m, link, 0);
            for (u32 k = 0; k < n; ++k) {
                put32(m, link, next_node);
                put32(m, next_node + 40, 0);
                putf(m, next_node + 24, -1.0f);
                link = next_node + 40;
                next_node += 0x40;
            }
        }
        fill(m, kSp - 0x100, 0x100, rng);  // stale frame bytes: the rgba copy lands on the original ones
        const PairOut b = pair(m, PAIR(fn_sub_1C0960_001c0960), Args{arg64(rng, kTask)}, rng(), "sub_1C0960");
        CHECK(b.hand.v0() == (state == 1 ? ~0ull : 0ull));
        if (state == 0 && frames <= 0) CHECK(get32(m, kWork + kFadeState) == 1u);
    }
}

// ======================================================================================================================
// The floor generator's block rotation
// ======================================================================================================================

// Host model of step 3: both nibbles of each door byte rotate left by k within 4 bits.
u8 rotate_doors(u8 b, unsigned k) {
    auto rot = [k](unsigned n) { return static_cast<unsigned>(((n << k) & 0xF) | ((n << k) >> 4)); };
    return static_cast<u8>(rot(b & 0xF) | (rot((b >> 4) & 0xF) << 4));
}

TEST_CASE("game(field_big): sub_1BAB60 rotates block descriptors as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16003u};
    const u32 turns[] = {1, 2, 4, 8, 0, 3, 16, 0xFFFFFFFFu};
    const u32 blk = kBuf;
    for (int it = 0; it < 600; ++it) {
        fill(m, blk, 96, rng);
        const u8 wd = static_cast<u8>(it % 9 == 0 ? rng() % 5 : 1 + rng() % 3);
        const u8 dp = static_cast<u8>(it % 9 == 0 ? rng() % 5 : 1 + rng() % 3);
        m.at(blk + kBlkWidth)[0] = wd;
        m.at(blk + kBlkDepth)[0] = dp;
        for (u32 i = 0; i < 9; ++i) m.at(blk + kBlkKinds + i)[0] = static_cast<u8>(rng() % 3 ? rng() % 40 : rng());
        const u32 turn = it < 8 ? turns[it] : turns[rng() % 4];
        fill(m, kSp - 0x100, 0x100, rng);
        const u64 turn64 = arg64(rng, turn);  // compared as the whole register: stray upper bits mean k = 0
        pair(m, PAIR(fn_sub_1BAB60_001bab60), Args{arg64(rng, blk), turn64}, rng(), "sub_1BAB60");
        // Documented rules on a 1 x 1 block (no cell moves): every cell is table[kind] with the door byte rotated.
        if (wd == 1 && dp == 1) {
            unsigned k = 0;
            for (unsigned j = 0; j < 4; ++j)
                if ((1ull << j) == turn64) {
                    k = j;
                    break;
                }
            for (u32 r = 0; r < 3; ++r)
                for (u32 c = 0; c < 3; ++c) {
                    const u32 kind = m.at(blk + kBlkKinds + 3 * r + c)[0];
                    const u32 cellva = blk + kBlkCells + kBlkRowSize * r + kBlkCellSize * c;
                    const u8* src = m.at(kBlockKindTable + 8 * kind);
                    CHECK(m.at(cellva)[0] == rotate_doors(src[0], k));
                    CHECK(std::memcmp(m.at(cellva + 1), src + 1, 7) == 0);
                }
        }
        // A 1 x 2 block turned once becomes 2 x 1.
        if (wd == 1 && dp == 2 && (turn64 == 2 || turn64 == 8)) {
            CHECK(m.at(blk + kBlkWidth)[0] == 2);
            CHECK(m.at(blk + kBlkDepth)[0] == 1);
        }
    }
}

// Host model of sub_1BC630's documented rule: the first origin (x - i, z - j), j < depth, i < width, with all cells free.
bool first_free_origin(const Machine& m, u32 blk, s32 x, s32 z, s32& ox, s32& oz) {
    const s32 w = m.mem.main_ram()[blk + kBlkWidth], d = m.mem.main_ram()[blk + kBlkDepth];
    for (s32 j = 0; j < d; ++j)
        for (s32 i = 0; i < w; ++i) {
            bool free = true;
            for (s32 r = 0; r < d && free; ++r)
                for (s32 c = 0; c < w && free; ++c) {
                    const s64 va = 0x869F60 + 72 + 256 * static_cast<s64>(z - j + r) + 16 * static_cast<s64>(x - i + c);
                    free = m.mem.main_ram()[va] == 0;
                }
            if (free) {
                ox = x - i;
                oz = z - j;
                return true;
            }
        }
    return false;
}

TEST_CASE("game(field_big): sub_1BC630 fits blocks on the floor grid as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16008u};
    const u32 blk = kBuf, px = kBuf + 0x100, pz = kBuf + 0x104;
    int fits = 0, origins = 0;
    for (int it = 0; it < 800; ++it) {
        // the grid: taken cells with door bytes (sparse to dense)
        const u32 density = rng() % 100;
        for (u32 c = 0; c < 256; ++c) {
            const u32 va = 0x869F60u + kGridBase + 16 * c;
            m.at(va)[0] = static_cast<u8>(rng() % 100 < density ? 1 : 0);
            m.at(va + 11)[0] = static_cast<u8>(rng());
        }
        fill(m, blk, 96, rng);
        m.at(blk + kBlkWidth)[0] = static_cast<u8>(it % 17 == 0 ? rng() % 5 : 1 + rng() % 3);
        m.at(blk + kBlkDepth)[0] = static_cast<u8>(it % 17 == 0 ? rng() % 5 : 1 + rng() % 3);
        // door bytes mostly matching a fully closed / open pattern so that some placements pass
        for (u32 r = 0; r < 3; ++r)
            for (u32 c = 0; c < 3; ++c)
                if (rng() % 2) m.at(blk + kBlkCells + kBlkRowSize * r + kBlkCellSize * c)[0] = 0;
        const s32 x = 2 + static_cast<s32>(rng() % 12), z = 2 + static_cast<s32>(rng() % 12);
        put32(m, px, static_cast<u32>(x));
        put32(m, pz, static_cast<u32>(z));
        fill(m, kSp - 0x100, 0x100, rng);
        s32 ox = 0, oz = 0;
        const bool origin = first_free_origin(m, blk, x, z, ox, oz);
        const PairOut p = pair(m, PAIR(fn_sub_1BC630_001bc630), Args{arg64(rng, blk), arg64(rng, px), arg64(rng, pz)},
                               rng(), "sub_1BC630");
        if (!origin) CHECK(p.hand.v0() == 0);
        origins += origin ? 1 : 0;
        if (p.hand.v0() == 1) {
            ++fits;
            CHECK(origin);
            CHECK(static_cast<s32>(get32(m, px)) == ox);
            CHECK(static_cast<s32>(get32(m, pz)) == oz);
        }
    }
    MESSAGE("sub_1BC630: " << origins << " free origins, " << fits << " fits");
    CHECK(fits > 50);
}

// ======================================================================================================================
// The per-frame block culling
// ======================================================================================================================

constexpr u32 kField = 0x869F60u;            // sField
constexpr u32 kSceneSlot = gpva(kGpSceneIds);  // -> the scene record
constexpr u32 kCameraSlot = gpva(-19504);    // kwlnGetMainCamera's global
constexpr u32 kScene = 0x01816000u;          // the scene record
constexpr u32 kMgr = 0x01816100u;            // the resource manager: list heads by type (+4 type)
constexpr u32 kRes = 0x01817000u;            // scene resources, 0x200 apart (up to 68)
constexpr u32 kCamera = 0x01811000u;         // the main camera (+4 its frame; the frame's matrix at +16)
constexpr u32 kCtlTask = 0x01811200u;        // the player's collision controller task / work
constexpr u32 kCtlWork = 0x01811300u;
static_assert(kSceneSlot == 0x7CD540u);

u32 res_va(unsigned i) { return kRes + 0x200u * i; }
void set_scene(Machine& m, s32 major, s32 minor) {
    put32(m, kSceneSlot, kScene);
    put32(m, kScene + 0, static_cast<u32>(major));
    put32(m, kScene + 4, static_cast<u32>(minor));
    put32(m, kScene + 8, kMgr);
    zero(m, kMgr, 64 * 4);
}
// Resource i with u16 id, linked at the head of its type's list.
u32 add_res(Machine& m, unsigned i, u16 id, u32 flags) {
    const u32 res = res_va(i);
    zero(m, res, 0x200);
    put16(m, res, id);
    put32(m, res + kResFlags, flags);
    const u32 type = (id >> 10) & 0x3F;
    put32(m, res + kResNext, get32(m, kMgr + 4 * type));
    put32(m, kMgr + 4 * type, res);
    return res;
}
// A rotation about y by `deg` (RW matrix: right, up, at, pos rows of 16 bytes) for the camera frame.
void set_camera(Machine& m, float deg, std::mt19937& rng) {
    put32(m, kCameraSlot, kCamera);
    put32(m, kCamera + 4, kCamera + 0x40);
    const u32 mat = kCamera + 0x40 + 16;
    const float r = deg * 3.14159265f / 180.0f;
    const float c = std::cos(r), s = std::sin(r);
    const float rows[4][4] = {{c, 0, -s, 0}, {0, 1, 0, 0}, {s, 0, c, 0}, {rfloat(rng), rfloat(rng), rfloat(rng), 1}};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) putf(m, mat + 16 * i + 4 * j, rows[i][j]);
    put32(m, mat + 12, 3);  // rwMATRIXTYPEORTHONORMAL-style flags word
}

TEST_CASE("game(field_big): sub_1BD950 culls the Tartarus blocks as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16004u};
    int culled = 0;
    for (int it = 0; it < 240; ++it) {
        const int kind = it % 6;  // 0: not Tartarus, 1..2: random floor, 3..5: fixed floor 51
        set_scene(m, kind == 0 ? 7 : kind < 3 ? 21 + static_cast<s32>(rng() % 8) : 51 + static_cast<s32>(rng() % 8),
                  kind == 0 || kind >= 3 ? static_cast<s32>(rng() % 3) : 0);
        // blocks (type 12) at cells of a 16 x 16 grid, parts (types 10 / 11) pointing at blocks
        zero(m, kField + kGridBase, 16 * 256);
        unsigned n = 0;
        std::vector<u32> blocks;
        const unsigned nblocks = 4 + rng() % 24;
        for (unsigned b = 0; b < nblocks; ++b) {
            const u32 x = rng() % 16, z = rng() % 16;
            const u16 id = static_cast<u16>(0x3000u + 16u * z + x);
            put16(m, kField + kGridBase + kGridRow * z + kGridCell * x + kGridCellRes, id);
            blocks.push_back(add_res(m, n++, id, rng() & 0xFFu));
        }
        for (unsigned p = 0; p < 6; ++p) {
            const u32 r10 = add_res(m, n++, static_cast<u16>(0x2800u + p), rng() & 0xFFu);
            put32(m, r10 + kResParent, rng() % 4 == 0 ? 0u : blocks[rng() % blocks.size()]);
            const u32 r11 = add_res(m, n++, static_cast<u16>(0x2C00u + p), rng() & 0xFFu);
            put32(m, r11 + kResParent, blocks[rng() % blocks.size()]);
        }
        // the player's character (id 1024) with its controller's grid cell (x = work +44, z = +48)
        const bool player = it % 7 != 0;
        if (player) {
            const u32 pres = add_res(m, n++, 1024, 0);
            put32(m, pres + kResController, kCtlTask);
            put32(m, kCtlTask + kTaskWork, kCtlWork);
            put32(m, kCtlWork + 44, 2 + rng() % 12);
            put32(m, kCtlWork + 48, 2 + rng() % 12);
        } else {
            put32(m, gpva(kGpPlayerCellX), 2 + rng() % 12);
            put32(m, gpva(kGpPlayerCellZ), 2 + rng() % 12);
        }
        // headings around the circle, the bounds themselves, and the half-way points
        const float bounds[] = {0.0f, 22.5f, -22.5f, 67.5f, -67.5f, 112.5f, -112.5f, 157.5f, -157.5f, 180.0f};
        const float yaw = it < 20 ? bounds[it % 10] : static_cast<float>(static_cast<s32>(rng() % 3600) - 1800) / 10.0f;
        set_camera(m, yaw, rng);
        // enemies: some live with a scene resource; the hero (gFldUnitsPc[0]) with an encounter and a model
        zero(m, kFldUnitsEc, kFldUnitSize * 28);
        for (u32 i = 0; i < kFldUnitsEcCount; ++i) {
            const u32 u = kFldUnitsEc + kFldUnitSize * i;
            if (rng() % 3 == 0) continue;
            put32(m, u + kUnitEncounter, 0x01500000u);
            if (rng() % 4 == 0) continue;
            put32(m, u + kUnitSceneRes, add_res(m, n++, static_cast<u16>(0x3C00u + i), rng() & 0xFFu));
            put32(m, u + 80, kObjs + 0x40u * (i % 8));  // model (its matrix at +48 is the position, sub_318B60)
        }
        put32(m, kFldUnitsPc + kUnitEncounter, rng() % 5 ? 0x01500100u : 0u);
        put32(m, kFldUnitsPc + 80, kObjs + 0x400u);
        fill(m, kObjs, 0x800, rng);
        for (u32 i = 0; i < 9; ++i) {  // finite positions
            for (u32 k = 0; k < 16; ++k) putf(m, kObjs + 0x40u * i + 4 * k, rfloat(rng));
        }
        const PairOut p = pair(m, PAIR(fn_sub_1BD950_001bd950), Args{}, rng(), "sub_1BD950");
        if (kind == 0) CHECK(p.hand.snaps.size() <= 4);  // not Tartarus: the two predicates and out
        if (kind != 0 && !p.hand.stopped && player) {
            ++culled;
            // Documented rule: the player's cell holds a block -> it is drawn (every wedge contains (0, 0)).
            const u32 x = get32(m, kCtlWork + 44), z = get32(m, kCtlWork + 48);
            CHECK(get32(m, gpva(kGpPlayerCellX)) == x);
            CHECK(get32(m, gpva(kGpPlayerCellZ)) == z);
            // (two blocks drawn at one cell share the id: MT_Scene_GetRes finds the one nearest the list head)
            const u16 id = get16(m, kField + kGridBase + kGridRow * z + kGridCell * x + kGridCellRes);
            bool any = id == 0, drawn = false;
            for (u32 b : blocks)
                if (get16(m, b) == id) {
                    any = true;
                    drawn = drawn || (get32(m, b + kResFlags) & kResDrawFlag) != 0;
                }
            CHECK(any);
            if (id != 0) CHECK(drawn);
        }
    }
    CHECK(culled > 100);
}

// ======================================================================================================================
// The field root's choices: scene variant, BGM, ambience
// ======================================================================================================================

constexpr u32 kDaysSinceApr5 = 0x83679Cu;  // s16 game date (0 = April 5)
constexpr u32 kTimeOfDay = 0x83679Eu;      // u8 day part (datGetTime)
constexpr u32 kFlagBits = 0x83A21Cu;       // datGetFlag's bit array
void set_flag(Machine& m, u32 id, bool on) {
    u32 w = get32(m, kFlagBits + 4 * (id >> 5));
    w = on ? (w | (1u << (id & 31))) : (w & ~(1u << (id & 31)));
    put32(m, kFlagBits + 4 * (id >> 5), w);
}
struct SceneIdT {
    s32 major, minor;
};
// The majors / minors the chains name, and neighbours.
s32 pick_major(std::mt19937& rng) {
    static const s32 majors[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 16, 19, 20, 21, 25, 28, 29, 30, 31, 32, 33,
                                 34, 35, 37, 38, 39, 40, 41, 45, 48, 49, 50, 51, 55, 58, 59, 70, 71, 78, 79, 199, 200, 251};
    return rng() % 8 == 0 ? static_cast<s32>(rng() % 300) : majors[rng() % std::size(majors)];
}
s32 pick_minor(std::mt19937& rng) {
    return rng() % 6 == 0 ? static_cast<s32>(rng() % 120) : static_cast<s32>(rng() % 24);
}

TEST_CASE("game(field_big): sub_1B6EB0 picks the scene variant as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16005u};
    set_scene(m, 1, 1);
    for (int it = 0; it < 1200; ++it) {
        const s32 major = pick_major(rng);
        const s32 minor = pick_minor(rng);
        const u8 tod = static_cast<u8>(it % 13 == 0 ? 9 + rng() % 4 : rng() % 9);
        const s16 days = static_cast<s16>(rng() % 400);
        put16(m, kDaysSinceApr5, static_cast<u16>(days));
        m.at(kTimeOfDay)[0] = tod;
        set_flag(m, 728, rng() % 2 != 0);
        put32(m, kScene + 0, static_cast<u32>(rng() % 4 == 0 ? 21 + rng() % 30 : rng() % 20));  // Tartarus or not
        put32(m, kScene + 4, rng() % 3);
        const PairOut p = pair(m, PAIR(fn_sub_1B6EB0_001b6eb0),
                               Args{arg64(rng, static_cast<u32>(major) | (rng() % 3 == 0 ? 0xABCD0000u : 0u)),
                                    arg64(rng, static_cast<u32>(minor) | (rng() % 3 == 0 ? 0x12340000u : 0u))},
                               rng(), "sub_1B6EB0");
        // Documented rules (26_field.md 2.2): field 1 -> 201 at time 6, else 1; 15/6 -> 6.
        const s32 r = static_cast<s32>(p.hand.v0());
        if (major == 15 && minor == 6) CHECK(r == 6);
        if (major == 1) CHECK(r == (tod == 6 ? 201 : 1));
    }
}

constexpr u32 kDungeonSlot = gpva(-19080);   // gp-0x4A88: the dungeon task
constexpr u32 kCounter1 = 0x83A4DCu + 4u;     // sub_16F380(1): g_data counter 1
constexpr u32 kScenarioSlot = gpva(-19788);  // sub_17D800's word
constexpr u32 kDngTask = 0x01811400u, kDngWork = 0x01811500u;

// The field-entry state the BGM / ambience choices read: dungeon floor (0 = none), scene, date, time, flags, counters.
void field_entry_state(Machine& m, std::mt19937& rng) {
    const bool dungeon = rng() % 3 == 0;
    put32(m, kDungeonSlot, dungeon ? kDngTask : 0u);
    put32(m, kDngTask + kTaskWork, kDngWork);
    static const s32 floors[] = {0, 1, 2, 16, 17, 20, 21, 40, 41, 64, 65, 70, 71, 100, 101, 114, 115, 130, 131, 160,
                                 161, 164, 165, 214, 215, 254, 255, 289, 290, 399, 400, 401, 450, -1};
    put32(m, kDngWork + 4, static_cast<u32>(rng() % 4 ? floors[rng() % std::size(floors)] : static_cast<s32>(rng() % 500)));
    put32(m, kCounter1, rng() % 3 == 0 ? rng() % 120 : 0u);
    put32(m, kScenarioSlot, rng() % 3 == 0 ? 1u : 0u);
    put32(m, gpva(kGpFieldBgmSuppressed), rng() % 8 == 0 ? 1u : 0u);
    static const s32 majors[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 51};
    put32(m, kScene + 0, static_cast<u32>(rng() % 6 ? majors[rng() % std::size(majors)] : static_cast<s32>(rng() % 60)));
    put32(m, kScene + 4, rng() % 5 ? rng() % 10 : rng() % 60);
    put16(m, kDaysSinceApr5, static_cast<u16>(rng() % 400));
    m.at(kTimeOfDay)[0] = static_cast<u8>(rng() % 10);
    for (u32 f : {3584u, 3680u, 3823u, 728u}) set_flag(m, f, rng() % 5 == 0);
}

TEST_CASE("game(field_big): sub_1A9850 chooses the field BGM as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16006u};
    StopAt stop{0x1099D0u, 0x108FD0u};  // the sound driver calls: stopped at, as when they were not emitted
    set_scene(m, 1, 1);
    int floor400 = 0;
    std::vector<u64> sites;  // the call sites reached (the $ra at the stop)
    for (int it = 0; it < 1500; ++it) {
        field_entry_state(m, rng);
        const PairOut p = pair(m, PAIR(fn_sub_1A9850_001a9850), Args{}, rng(), "sub_1A9850");
        // The sound driver is not emitted here: a choice stops the run at sub_1099D0 (play) / sub_108FD0 (fade out).
        if (p.hand.stopped) {
            CHECK((p.hand.stop_pc == 0x1099D0u || p.hand.stop_pc == 0x108FD0u));
            const u64 ra = p.hand.end.gpr[GPR_RA].u64[0];
            if (std::find(sites.begin(), sites.end(), ra) == sites.end()) sites.push_back(ra);
        }
        // Documented rule (the battle route's Thebel floor, 26_field.md 8): floor 400 plays BGM 1.
        const bool dungeon = get32(m, kDungeonSlot) != 0;
        if (dungeon && get32(m, kDngWork + 4) == 400 && get32(m, gpva(kGpFieldBgmSuppressed)) != 1 &&
            get32(m, kScenarioSlot) == 0 && get32(m, kCounter1) == 0) {
            ++floor400;
            CHECK(p.hand.stopped);
            CHECK(p.hand.stop_pc == 0x1099D0u);
            CHECK(p.hand.end.gpr[GPR_A0].u64[0] == 1);
        }
    }
    CHECK(floor400 > 0);
    MESSAGE("sub_1A9850: " << sites.size() << " of 46 call sites reached");
    CHECK(sites.size() >= 30);
}

TEST_CASE("game(field_big): sub_1AA1B0 chooses the field ambience as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16007u};
    StopAt stop{0x10A410u, 0x109F60u};  // the sound driver calls: stopped at, as when they were not emitted
    set_scene(m, 1, 1);
    std::vector<u64> sites;  // the call sites reached (the $ra at the stop)
    for (int it = 0; it < 2000; ++it) {
        field_entry_state(m, rng);
        // bias the scene towards the rules' fields and the date towards their ranges
        static const SceneIdT kScenes[] = {{6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 7}, {6, 11}, {6, 16}, {6, 20},
                                           {7, 1}, {7, 9}, {9, 1}, {9, 2}, {9, 7}, {12, 1}, {14, 1}, {14, 5}, {33, 1},
                                           {33, 4}, {6, 9}};
        if (rng() % 4 != 0) {
            const SceneIdT s = kScenes[rng() % std::size(kScenes)];
            put32(m, kScene + 0, static_cast<u32>(s.major));
            put32(m, kScene + 4, static_cast<u32>(s.minor));
        }
        // days since 4/5: 7/18 = 104, 9/18 = 166, 9/20 = 168, 10/16 = 194, 11/25 = 234
        static const u16 kDays[] = {104, 120, 166, 168, 169, 194, 234, 235, 30, 300};
        if (rng() % 2) put16(m, kDaysSinceApr5, kDays[rng() % std::size(kDays)]);
        const PairOut p = pair(m, PAIR(fn_sub_1AA1B0_001aa1b0), Args{}, rng(), "sub_1AA1B0");
        // The sound driver is not emitted: every run stops at sub_10A410 (start ENV_*.ADX) or sub_109F60 (stop).
        CHECK(p.hand.stopped);
        CHECK((p.hand.stop_pc == 0x10A410u || p.hand.stop_pc == 0x109F60u));
        CHECK(p.hand.end.gpr[GPR_A0].u64[0] == 4);  // channel 4
        if (p.hand.stop_pc == 0x10A410u) {
            const std::string file = m.str(static_cast<u32>(p.hand.end.gpr[GPR_A1].u64[0]));
            CHECK(file.rfind("ENV_0", 0) == 0);
        }
        const u64 ra = p.hand.end.gpr[GPR_RA].u64[0];
        if (std::find(sites.begin(), sites.end(), ra) == sites.end()) sites.push_back(ra);
        // Documented rule: 14/1 always plays ENV_050.
        if (get32(m, kScene) == 14 && get32(m, kScene + 4) == 1) {
            CHECK(p.hand.stop_pc == 0x10A410u);
            CHECK(m.str(static_cast<u32>(p.hand.end.gpr[GPR_A1].u64[0])) == "ENV_050.ADX");
        }
    }
    MESSAGE("sub_1AA1B0: " << sites.size() << " of 15 call sites reached");
    CHECK(sites.size() >= 13);
}

// ======================================================================================================================
// The collision controller and the pop scheduler helpers
// ======================================================================================================================

constexpr u32 kModel = 0x01811800u;  // a model: mdlGetMatrix(model) == model, the position row at +48
constexpr s32 kGpLiveShadowsT = -19044;  // gp-0x4A64: the live shadow count

void random_matrix(Machine& m, u32 va, std::mt19937& rng) {
    for (u32 k = 0; k < 16; ++k) putf(m, va + 4 * k, k % 4 == 3 ? 0.0f : rfloat(rng));
    put32(m, va + 12, 3);
}

TEST_CASE("game(field_big): the collision controller helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16009u};
    for (int it = 0; it < 400; ++it) {
        make_task(m, rng);
        const bool model = it % 5 != 0;
        put32(m, kWork + 16, model ? kModel : 0u);
        random_matrix(m, kModel, rng);
        // sub_1AD940: the position (or zeros)
        fill(m, kSp - 0x100, 0x100, rng);
        pair(m, PAIR(fn_sub_1AD940_001ad940), Args{arg64(rng, kBuf), arg64(rng, kTask)}, rng(), "sub_1AD940");
        for (u32 k = 0; k < 3; ++k) CHECK(get32(m, kBuf + 4 * k) == (model ? get32(m, kModel + 48 + 4 * k) : 0u));
        // sub_1ADD40: the grid cell (always with a model: the original does not test it)
        put32(m, kWork + 16, kModel);
        const float x = static_cast<float>(rng() % 12800), z = static_cast<float>(rng() % 12800);
        putf(m, kModel + 48, x);
        putf(m, kModel + 56, z);
        pair(m, PAIR(fn_sub_1ADD40_001add40), Args{arg64(rng, kTask)}, rng(), "sub_1ADD40");
        CHECK(static_cast<s32>(get32(m, kWork + 44)) == static_cast<s32>((x + 400.0f) / 800.0f));
        CHECK(static_cast<s32>(get32(m, kWork + 48)) == static_cast<s32>((z + 400.0f) / 800.0f));
        // sub_1ADFF0: the turn (translate / rotate / translate, run for real)
        put32(m, kWork + 16, model ? kModel : 0u);
        fill(m, kBuf, 12, rng);
        for (u32 k = 0; k < 3; ++k) putf(m, kBuf + 4 * k, k == 1 ? 1.0f : 0.0f);
        const u32 angle = [&] {
            const float a = static_cast<float>(static_cast<s32>(rng() % 720) - 360);
            u32 b;
            std::memcpy(&b, &a, 4);
            return b;
        }();
        pair(m, PAIR(fn_sub_1ADFF0_001adff0), Args{arg64(rng, kTask), arg64(rng, kBuf)}, rng(), "sub_1ADFF0",
             [angle](EEContext& c) { c.fpr[12] = angle; });
    }
}

TEST_CASE("game(field_big): K_FldFrame_HandleCollis picks the collision mesh as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x1AB390u, 0x1ABD20u};  // the two push-outs: stopped at, as when they were not emitted
    std::mt19937 rng{0xF1B1600Au};
    int block_meshes = 0;
    for (int it = 0; it < 600; ++it) {
        const int kind = it % 4;  // 0: RW world, 1: field mesh, 2: random floor, 3: fixed floor
        set_scene(m, kind == 2 ? 21 + static_cast<s32>(rng() % 8) : kind == 3 ? 51 + static_cast<s32>(rng() % 28)
                                                                              : 1 + static_cast<s32>(rng() % 20),
                  kind == 2 ? 0 : static_cast<s32>(rng() % 3));
        const u32 rec = kBuf + 0x200;  // the field's collision record
        put32(m, kField + 4460, rec);
        put32(m, rec + 0, kind == 0 ? 1u : (rng() & ~1u));
        put32(m, rec + 8, 0x01500000u);   // the field's mesh
        put32(m, rec + 12, 0x01500100u);  // the RW collision world
        // blocks at random cells, each with its mesh at +352 -> +8
        zero(m, kField + kGridBase, 16 * 256);
        unsigned n = 0;
        u32 bx = 0, bz = 0;
        for (unsigned b = 0; b < 12; ++b) {
            const u32 x = rng() % 16, z = rng() % 16;
            bx = x;
            bz = z;
            const u16 id = static_cast<u16>(0x3000u + 16u * z + x);
            if (rng() % 4) put16(m, kField + kGridBase + kGridRow * z + kGridCell * x + kGridCellRes, id);
            const u32 r = add_res(m, n++, id, 0);
            put32(m, r + 352, kObjs + 0x20u * b);
            put32(m, kObjs + 0x20u * b + 8, 0x01600000u + 0x100u * b);
        }
        // the mover: a character (type 1, controller +480) or another resource (+488), its controller's cell
        const bool character = rng() % 2 != 0;
        const u16 mover = character ? static_cast<u16>(0x400u + rng() % 4) : static_cast<u16>(0x3C00u + rng() % 4);
        const u32 res = add_res(m, n++, mover, 0);
        put32(m, res + (character ? 480 : 488), kCtlTask);
        put32(m, kCtlTask + kTaskWork, kCtlWork);
        const bool on_block = rng() % 2 != 0;  // often over the last block placed
        put32(m, kCtlWork + 44, on_block ? bx : rng() % 16);
        put32(m, kCtlWork + 48, on_block ? bz : rng() % 16);
        const u32 f12 = rng() & 0xBF7FFFFFu;
        const PairOut p = pair(m, PAIR(fn_K_FldFrame_HandleCollis_001ac750),
                               Args{arg64(rng, kBuf), arg64(rng, kBuf + 0x10), arg64(rng, mover)}, rng(),
                               "K_FldFrame_HandleCollis", [f12](EEContext& c) { c.fpr[12] = f12; });
        // The collision itself is not emitted here: the run stops at sub_1AB390 (world) / sub_1ABD20 (mesh).
        CHECK(p.hand.stopped);
        CHECK(p.hand.stop_pc == (kind == 0 ? 0x1AB390u : 0x1ABD20u));
        CHECK(p.hand.end.fpr[12] == f12);
        if (kind == 1) CHECK(p.hand.end.gpr[GPR_A0].u64[0] == 0x01500000u);
        if (kind >= 2 && p.hand.end.gpr[GPR_A0].u64[0] >= 0x01600000u) ++block_meshes;
    }
    CHECK(block_meshes > 20);
}

TEST_CASE("game(field_big): the pop scheduler helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B1600Bu};
    for (int it = 0; it < 200; ++it) {
        set_scene(m, it % 3 ? 21 + static_cast<s32>(rng() % 8) : 51, it % 3 ? 0 : 1);
        u32 cells = 0;
        const u32 density = rng() % 100;
        for (u32 c = 0; c < 256; ++c) {
            const u8 v = static_cast<u8>(rng() % 100 < density ? 1 : (rng() % 8 == 0 ? 2 : 0));
            m.at(kField + kGridBase + 16 * c)[0] = v;
            cells += v == 1 ? 1u : 0u;
        }
        make_task(m, rng);
        const u32 limit = word(rng);
        put32(m, kWork + 12, limit);
        const u32 per_cell = it % 7 == 0 ? word(rng) : 10;
        pair(m, PAIR(fn_sub_1D38D0_001d38d0), Args{arg64(rng, kTask), arg64(rng, per_cell)}, rng(), "sub_1D38D0");
        if (it % 3 && it % 7) {  // random floor, 10 per cell (26_field.md 6.4): the unsigned minimum
            const u32 want = 10u * cells < limit ? 10u * cells : limit;
            CHECK(get32(m, kWork + 12) == want);
        }
        // sub_1D3830 over the Reaper timer (sub_1D38A0: limit - frames / 30, floored at 0)
        make_task(m, rng);
        put32(m, kWork + 12, it % 4 == 0 ? 0u : rng() % 200);
        put32(m, kWork + 16, rng() % 7000);
        const PairOut p = pair(m, PAIR(fn_sub_1D3830_001d3830), Args{arg64(rng, kTask)}, rng(), "sub_1D3830");
        const s32 r = static_cast<s32>(p.hand.v0());
        CHECK((r == -1 || r == 1 || r == 2));
    }
}

TEST_CASE("game(field_big): the enemy pop scheduler task equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B1600Cu};
    const u32 table = 0x0181A000u;  // the k_encount floor table behind gp-0x4840
    int full = 0;
    for (int it = 0; it < 800; ++it) {
        const int kind = it % 4;
        set_scene(m, kind == 0 ? 14 : kind == 1 ? 21 + static_cast<s32>(rng() % 8) : 51, kind == 0 ? (rng() % 2 ? 5 : 1) : kind == 1 ? 0 : 1);
        for (u32 c = 0; c < 256; ++c) m.at(kField + kGridBase + 16 * c)[0] = static_cast<u8>(rng() % 3 == 0);
        put32(m, gpva(-18496), table);
        fill(m, table, 0x1000, rng);
        for (u32 k = 0; k < 0x1000; k += 4) m.at(table + k)[0] = static_cast<u8>(rng() % 8);
        put32(m, kDungeonSlot, kDngTask);
        put32(m, kDngTask + kTaskWork, kDngWork);
        put32(m, kDngWork + 4, rng() % 400);  // floor
        put32(m, kDngWork + 40, rng() % 6);   // floor kind
        make_task(m, rng);
        put32(m, kWork + 0, rng() % 4);                   // state
        put32(m, kWork + 4, rng() % 6 == 0 ? 1u : 0u);    // paused
        put32(m, kWork + 8, rng() % 6 == 0 ? 1u : 0u);
        put32(m, kWork + 12, rng() % 3 == 0 ? 0u : rng() % 300);  // the Reaper limit
        put32(m, kWork + 16, rng() % 12000);                       // frames
        put32(m, kWork + 20, rng() % 4 == 0 ? 1u : 0u);            // Reapers out
        put32(m, gpva(kGpLiveShadowsT), rng() % 2 ? 99u : rng() % 6);  // live shadows (99: no respawn call)
        const PairOut p = pair(m, PAIR(fn_K_Unit_UpdateEnemyPopSchedulerTask_001d32a0), Args{arg64(rng, kTask)}, rng(),
                               "K_Unit_UpdateEnemyPopSchedulerTask");
        if (!p.hand.stopped) {
            ++full;
            CHECK(p.hand.v0() == 0);
        }
    }
    CHECK(full > 100);
}

TEST_CASE("game(field_big): the event / camera / virtual-pad helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B1600Du};
    for (int it = 0; it < 300; ++it) {
        // sub_1C7130: the distance test against the hero (run for real)
        zero(m, kFldUnitsEc, kFldUnitSize * 28);
        const u32 unit = kFldUnitsEc + kFldUnitSize * (rng() % 24);
        put32(m, unit + kUnitEncounter, rng() % 5 ? 0x01500000u : 0u);
        put32(m, unit + 80, kObjs);
        put32(m, kFldUnitsPc + kUnitEncounter, rng() % 5 ? 0x01500100u : 0u);
        put32(m, kFldUnitsPc + 80, kObjs + 0x100);
        random_matrix(m, kObjs, rng);
        random_matrix(m, kObjs + 0x100, rng);
        const float d = static_cast<float>(rng() % 3000);
        u32 dbits;
        std::memcpy(&dbits, &d, 4);
        pair(m, PAIR(fn_sub_1C7130_001c7130), Args{arg64(rng, unit)}, rng(), "sub_1C7130",
             [dbits](EEContext& c) { c.fpr[12] = dbits; });

        // sub_1D5140: the camera point nearest the player
        make_task(m, rng);
        put32(m, kWork + 204, kBuf + 0x300);   // the player resource
        put32(m, kBuf + 0x300 + kResController, kCtlTask);
        put32(m, kCtlTask + kTaskWork, kCtlWork);
        put32(m, kCtlWork + 16, rng() % 5 ? kModel : 0u);
        random_matrix(m, kModel, rng);
        for (u32 k = 0; k < 27; ++k) putf(m, kWork + 96 + 4 * k, rfloat(rng));
        const PairOut p = pair(m, PAIR(fn_sub_1D5140_001d5140), Args{arg64(rng, kTask)}, rng(), "sub_1D5140");
        CHECK(!p.hand.stopped);

        // sub_1E13F0: the rotate task (sub_1AD9E0 is not emitted: the last frame stops there)
        make_task(m, rng);
        put32(m, kWork + 64, rng() % 4 ? 1u : rng() % 3);
        put32(m, kWork + 68, kCtlTask);
        put32(m, kCtlWork + 16, rng() % 5 ? kModel : 0u);
        putf(m, kWork + 84, static_cast<float>(static_cast<s32>(rng() % 60) - 30));
        put32(m, kWork + 88, rng() % 10);
        put32(m, kWork + 92, rng() % 10);
        fill(m, kSp - 0x100, 0x100, rng);
        const PairOut q = pair(m, PAIR(fn_sub_1E13F0_001e13f0), Args{arg64(rng, kTask)}, rng(), "sub_1E13F0");
        if (q.hand.stopped) CHECK(q.hand.stop_pc == 0x1AD9E0u);
    }
}

// ======================================================================================================================
// Field hits and shadow spawning
// ======================================================================================================================

// A field-hit resource (type 13, id 0x3400 + i) with a horizontal quad around (cx, cz) at height y, half size h.
u32 add_field_hit(Machine& m, unsigned i, float cx, float y, float cz, float h, std::mt19937& rng) {
    const u32 r = add_res(m, i, static_cast<u16>(0x3400u + i), 0);
    const float corners[4][3] = {{cx - h, y, cz - h}, {cx + h, y, cz - h}, {cx + h, y + (rng() % 2 ? 0.0f : 30.0f), cz + h},
                                 {cx - h, y, cz + h}};
    for (u32 k = 0; k < 4; ++k)
        for (u32 j = 0; j < 3; ++j) putf(m, r + 284 + 12 * k + 4 * j, corners[k][j]);
    return r;
}

TEST_CASE("game(field_big): the field-hit lookups equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B1600Eu};
    int found = 0, near = 0;
    for (int it = 0; it < 600; ++it) {
        const bool random_floor = it % 2 == 0;
        set_scene(m, random_floor ? 21 + static_cast<s32>(rng() % 8) : 7, random_floor ? 0 : 1);
        const unsigned n = rng() % 6;
        for (unsigned i = 0; i < n; ++i)
            add_field_hit(m, i, static_cast<float>(rng() % 4000), static_cast<float>(rng() % 400), static_cast<float>(rng() % 4000),
                          50.0f + static_cast<float>(rng() % 300), rng);
        // a point near one quad (or anywhere)
        const float px = static_cast<float>(rng() % 4000), py = static_cast<float>(rng() % 500), pz = static_cast<float>(rng() % 4000);
        putf(m, kBuf + 0, px);
        putf(m, kBuf + 4, py);
        putf(m, kBuf + 8, pz);
        if (n && rng() % 2) {
            const u32 r = res_va(rng() % n);
            putf(m, kBuf + 0, getf(m, r + 284) + 40.0f);
            putf(m, kBuf + 4, getf(m, r + 288) + static_cast<float>(static_cast<s32>(rng() % 240) - 120));
            putf(m, kBuf + 8, getf(m, r + 292) + 40.0f);
        }
        put32(m, kBuf + 0x20, 0xDEADBEEFu);
        const PairOut a = pair(m, PAIR(fn_K_FldEvent_FindFldHitAt_001c5ee0), Args{arg64(rng, kBuf), arg64(rng, kBuf + 0x20)},
                               rng(), "K_FldEvent_FindFldHitAt");
        if (random_floor) CHECK(a.hand.v0() == 0xFFFFu);
        if (a.hand.v0() != 0xFFFFu) {
            ++found;
            CHECK(get16(m, get32(m, kBuf + 0x20)) == a.hand.v0());
        }
        // the unit form: the model position of a unit
        put32(m, kBuf + 0x40 + 80, kModel);
        for (u32 k = 0; k < 16; ++k) putf(m, kModel + 4 * k, 0.0f);
        putf(m, kModel + 48, getf(m, kBuf + 0));
        putf(m, kModel + 52, getf(m, kBuf + 4));
        putf(m, kModel + 56, getf(m, kBuf + 8));
        const PairOut b = pair(m, PAIR(fn_K_FldEvent_IsUnitNearFldHit_001c7b30), Args{arg64(rng, kBuf + 0x40)}, rng(),
                               "K_FldEvent_IsUnitNearFldHit");
        if (!random_floor) CHECK(b.hand.v0() == 0);
        near += b.hand.v0() == 1 ? 1 : 0;
    }
    MESSAGE("field hits: " << found << " found, " << near << " near");
    CHECK(found > 20);
    CHECK(near > 20);
}

TEST_CASE("game(field_big): sub_1D0720 spawns as its recompiled body (up to the shadow creation)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B1600Fu};
    StopAt stop{0x1CF940u};  // the shadow creation: stopped at, as when it was not emitted
    int searched = 0;
    for (int it = 0; it < 400; ++it) {
        static const s32 majors[] = {7, 20, 21, 25, 28, 29, 39, 40, 45, 48, 49, 51};
        set_scene(m, majors[rng() % std::size(majors)], rng() % 3 == 0 ? 0 : 1);
        set_flag(m, 5141, rng() % 5 == 0);
        // the spawn points (scene resources of type 15): off random floors sub_1D0880's slot i is the i-th of them
        const unsigned points = rng() % 5;
        for (unsigned i = 0; i < points; ++i) add_res(m, i, static_cast<u16>(0x3C00u + i), 0);
        put32(m, gpva(-18496), 0x0181A000u);
        fill(m, 0x0181A000u, 0x1000, rng);
        const PairOut p = pair(m, PAIR(fn_sub_1D0720_001d0720), Args{arg64(rng, rng() % 20)}, rng(), "sub_1D0720");
        // sub_1CF940 (the shadow creation: models, sprintf) is not emitted: a spawn stops there, after the slot search and
        // the encounter pick ran for real.
        if (p.hand.stopped) {
            ++searched;
            CHECK(p.hand.stop_pc == 0x1CF940u);
            if (get32(m, kScene) == 51 && get32(m, kScene + 4) == 1) CHECK(p.hand.end.gpr[GPR_A0].u64[0] == 0x10000u + 466u);
        } else {
            CHECK(p.hand.v0() == 0);
        }
    }
    MESSAGE("sub_1D0720: " << searched << " spawns reached sub_1CF940");
    CHECK(searched > 20);
}

TEST_CASE("game(field_big): sub_1E1590 starts the turn in place as its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1B16010u};
    int started = 0;
    for (int it = 0; it < 800; ++it) {
        make_task(m, rng);
        put32(m, kWork + 64, rng() % 6 == 0 ? 1u : 0u);
        fill(m, kBuf, 64, rng);
        put32(m, kBuf + 64, 0);  // (the source's +64 word lands at work +64: keep it 0 / 1 to exercise both)
        auto heading = [&]() {
            switch (rng() % 5) {
            case 0: return static_cast<float>(rng() % 721);            // 0..720
            case 1: return static_cast<float>(rng() % 20);             // near 0
            case 2: return 340.0f + static_cast<float>(rng() % 40);    // near 360
            default: return static_cast<float>(rng() % 36000) / 100.0f;
            }
        };
        const float from = heading(), to = heading();
        u32 fb, tb;
        std::memcpy(&fb, &from, 4);
        std::memcpy(&tb, &to, 4);
        const PairOut p = pair(m, PAIR(fn_sub_1E1590_001e1590), Args{arg64(rng, kTask), arg64(rng, kBuf)}, rng(), "sub_1E1590",
                               [fb, tb](EEContext& c) {
                                   c.fpr[12] = fb;
                                   c.fpr[13] = tb;
                               });
        if (p.hand.v0() == 1) {
            ++started;
            CHECK(get32(m, kWork + 64) == 1u);
            CHECK(static_cast<s32>(get32(m, kWork + 92)) >= 1);
        }
    }
    CHECK(started > 100);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
