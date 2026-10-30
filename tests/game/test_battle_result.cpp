// Phase 5 pair tests for slice battle_result (game/src/battle/battle_result.cpp): every hand-written battle-result
// function and the recompiled body it replaces run on identical guest machines -- a random result world (eight kwln tasks
// whose work records (+60) hold random fields, small values, zeros and pointers back into the world; the gp-relative
// records of the result screen -- the root's work gp-18968, br_res gp-18916, br_panel gp-18912, the persona birth
// gp-18880 / gp-18876, the AI panel gp-18872, the party members' equipment tables gp-18596..gp-18568, the br_data tables
// -- pointing into the world or left 0 for the K_Assert paths) and a random register file (GPRs in 128 bits, FPRs) --
// and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * the whole 32 MiB of main RAM (a PairRange, write_tracker.h: the world, .data / .bss, the stack with the frames and
//     spills of the run, whatever a random pointer reached) and the scratchpad.
// The test build emits the leaf callees named in tests/game/CMakeLists.txt (the g_data / item accessors, the 2D helpers,
// K_Assert), so most paths run to the end; the big screen builders, the message windows, the heap and printf are not
// emitted (compared stops). The real snapshots battle_ref_6150 / b_5800 / dorm_replay_4900 run the functions on the
// game's own state (the result screen is live at 6150). Documented rules (battle_result.h) are checked on the host.
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/game/battle_result.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
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
P3FES_DECL_PAIR(fn_sub_1F08C0_001f08c0)
P3FES_DECL_PAIR(fn_sub_1F0900_001f0900)
P3FES_DECL_PAIR(fn_sub_1F0940_001f0940)
P3FES_DECL_PAIR(fn_sub_1F0970_001f0970)
P3FES_DECL_PAIR(fn_sub_1F0A60_001f0a60)
P3FES_DECL_PAIR(fn_sub_1F0AB0_001f0ab0)
P3FES_DECL_PAIR(fn_sub_1F0C40_001f0c40)
P3FES_DECL_PAIR(fn_sub_1F0D70_001f0d70)
P3FES_DECL_PAIR(fn_sub_1F0EB0_001f0eb0)
P3FES_DECL_PAIR(fn_sub_1F0F40_001f0f40)
P3FES_DECL_PAIR(fn_sub_1F0FD0_001f0fd0)
P3FES_DECL_PAIR(fn_sub_1F0FF0_001f0ff0)
P3FES_DECL_PAIR(fn_sub_1F10B0_001f10b0)
P3FES_DECL_PAIR(fn_sub_1F10F0_001f10f0)
P3FES_DECL_PAIR(fn_sub_1F1140_001f1140)
P3FES_DECL_PAIR(fn_sub_1F1210_001f1210)
P3FES_DECL_PAIR(fn_sub_1F1240_001f1240)
P3FES_DECL_PAIR(fn_sub_1F1AA0_001f1aa0)
P3FES_DECL_PAIR(fn_sub_1F1AE0_001f1ae0)
P3FES_DECL_PAIR(fn_sub_1F1B00_001f1b00)
P3FES_DECL_PAIR(fn_sub_1F1B20_001f1b20)
P3FES_DECL_PAIR(fn_sub_1F1B40_001f1b40)
P3FES_DECL_PAIR(fn_sub_1F1B60_001f1b60)
P3FES_DECL_PAIR(fn_sub_1F1C20_001f1c20)
P3FES_DECL_PAIR(fn_sub_1F1C50_001f1c50)
P3FES_DECL_PAIR(fn_sub_1F1C90_001f1c90)
P3FES_DECL_PAIR(fn_sub_1F1DF0_001f1df0)
P3FES_DECL_PAIR(fn_sub_1F1E90_001f1e90)
P3FES_DECL_PAIR(fn_sub_1F1F40_001f1f40)
P3FES_DECL_PAIR(fn_sub_1F9D70_001f9d70)
P3FES_DECL_PAIR(fn_sub_1FA0D0_001fa0d0)
P3FES_DECL_PAIR(fn_sub_1FA4F0_001fa4f0)
P3FES_DECL_PAIR(fn_sub_1FAEA0_001faea0)
P3FES_DECL_PAIR(fn_sub_1FB130_001fb130)
P3FES_DECL_PAIR(fn_sub_1FB1B0_001fb1b0)
P3FES_DECL_PAIR(fn_sub_1FB1F0_001fb1f0)
P3FES_DECL_PAIR(fn_sub_1FB3F0_001fb3f0)
P3FES_DECL_PAIR(fn_sub_1FB4B0_001fb4b0)
P3FES_DECL_PAIR(fn_sub_1FBD50_001fbd50)
P3FES_DECL_PAIR(fn_sub_1FBDF0_001fbdf0)
P3FES_DECL_PAIR(fn_sub_1FBFA0_001fbfa0)
P3FES_DECL_PAIR(fn_sub_1FC1F0_001fc1f0)
P3FES_DECL_PAIR(fn_sub_1FC230_001fc230)
P3FES_DECL_PAIR(fn_sub_1FC3C0_001fc3c0)
P3FES_DECL_PAIR(fn_sub_1FC590_001fc590)
P3FES_DECL_PAIR(fn_sub_2338D0_002338d0)
P3FES_DECL_PAIR(fn_sub_2338F0_002338f0)
P3FES_DECL_PAIR(fn_sub_233910_00233910)
P3FES_DECL_PAIR(fn_sub_233930_00233930)
P3FES_DECL_PAIR(fn_sub_233950_00233950)
P3FES_DECL_PAIR(fn_sub_233960_00233960)
P3FES_DECL_PAIR(fn_sub_233970_00233970)
P3FES_DECL_PAIR(fn_sub_233AD0_00233ad0)
P3FES_DECL_PAIR(fn_sub_233BB0_00233bb0)
P3FES_DECL_PAIR(fn_sub_233D20_00233d20)
P3FES_DECL_PAIR(fn_sub_233D70_00233d70)
P3FES_DECL_PAIR(fn_sub_233DF0_00233df0)
P3FES_DECL_PAIR(fn_sub_234570_00234570)
P3FES_DECL_PAIR(fn_sub_2345D0_002345d0)
P3FES_DECL_PAIR(fn_sub_234630_00234630)
P3FES_DECL_PAIR(fn_sub_234690_00234690)
P3FES_DECL_PAIR(fn_sub_2347E0_002347e0)
P3FES_DECL_PAIR(fn_sub_234820_00234820)
P3FES_DECL_PAIR(fn_sub_234960_00234960)
P3FES_DECL_PAIR(fn_sub_234A00_00234a00)
P3FES_DECL_PAIR(fn_sub_235010_00235010)
P3FES_DECL_PAIR(fn_sub_2361D0_002361d0)
P3FES_DECL_PAIR(fn_sub_236280_00236280)
P3FES_DECL_PAIR(fn_sub_2362E0_002362e0)
P3FES_DECL_PAIR(fn_sub_236340_00236340)
P3FES_DECL_PAIR(fn_bpIfontSetDigitQuad_00238fd0)
P3FES_DECL_PAIR(fn_sub_239140_00239140)
P3FES_DECL_PAIR(fn_sub_24A870_0024a870)
P3FES_DECL_PAIR(fn_sub_24AA90_0024aa90)
P3FES_DECL_PAIR(fn_sub_24AB10_0024ab10)
P3FES_DECL_PAIR(fn_sub_24ABD0_0024abd0)
P3FES_DECL_PAIR(fn_sub_24AC40_0024ac40)
P3FES_DECL_PAIR(fn_sub_24ADF0_0024adf0)
P3FES_DECL_PAIR(fn_sub_24B8A0_0024b8a0)
P3FES_DECL_PAIR(fn_sub_24B9E0_0024b9e0)
P3FES_DECL_PAIR(fn_sub_24BA30_0024ba30)
P3FES_DECL_PAIR(fn_sub_24BED0_0024bed0)
P3FES_DECL_PAIR(fn_sub_24BF20_0024bf20)
P3FES_DECL_PAIR(fn_sub_24C040_0024c040)
P3FES_DECL_PAIR(fn_sub_24C090_0024c090)
P3FES_DECL_PAIR(fn_sub_24C100_0024c100)
P3FES_DECL_PAIR(fn_sub_24C110_0024c110)
P3FES_DECL_PAIR(fn_sub_24CF00_0024cf00)
P3FES_DECL_PAIR(fn_sub_24D0C0_0024d0c0)
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

// --- the result world (free RAM above the arena) --------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x20000u;
constexpr u32 kTasks = kWorld;              // 8 kwln tasks, 0x100 apart (+60 work)
constexpr u32 kNumTasks = 8;
constexpr u32 kWorks = kWorld + 0x1000u;    // their work records, 0x3000 apart (the root's reaches +10844)
constexpr u32 kRecords = kWorld + 0x19000u; // records the gp words and the world's pointers point at, 0x7000 bytes
constexpr u32 task_of(u32 i) { return kTasks + 0x100u * i; }
constexpr u32 work_of(u32 i) { return kWorks + 0x3000u * i; }
constexpr u32 kGp = 0x7D2CF0u;
constexpr u32 gp(s32 off) { return kGp + static_cast<u32>(off); }

// The gp words the bodies read (battle_result.h): each points into the world, at a work record, or is 0.
const s32 kGpWords[] = {-18968, -18916, -18912, -18880, -18876, -18872, -18596, -18592, -18588, -18584, -18580, -18576,
                        -18572, -18568, -18600, -18624, -18632, -18640, -18504, -18516, -31820, -31824, -32656, -32184,
                        -32632, -32004};

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }

// A world word: small values (switch indices, counts, ids), zeros, pointers into the world, random bits.
u32 world_word(std::mt19937& rng) {
    const unsigned k = rng() % 100;
    if (k < 30) return rng() % 16;
    if (k < 45) return 0;
    if (k < 60) return kRecords + (rng() % 0x7000u & ~15u);
    if (k < 70) return work_of(rng() % kNumTasks) + (chance(rng, 50) ? 0 : (rng() % 0x400u & ~3u));
    if (k < 75) return rng() % 0x10000u;
    return rng();
}

void random_world(Machine& m, std::mt19937& rng) {
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, world_word(rng));
    for (u32 i = 0; i < kNumTasks; ++i) store32(m, task_of(i) + 60, work_of(i));
    for (s32 off : kGpWords) {
        const unsigned k = rng() % 100;
        store32(m, gp(off), k < 8 ? 0u : k < 60 ? kRecords + (rng() % 0x6000u & ~15u) : work_of(rng() % kNumTasks));
    }
    store32(m, gp(-18968), chance(rng, 8) ? 0u : work_of(0));  // the root's work is task 0's
}

// --- the register file at a check point / the return / a stop ----------------------------------------------------
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
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa || a.fcr31 != b.fcr31) return "sa/fcr31";
    if (a.acc != b.acc) return "acc";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds).
class BrHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop;
    int syscalls = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    // A body that walks random data without end (a table scan that finds no terminator) is cut at the same check point
    // in both runs and compared there like a missing-function stop (stop_pc 0xFFFFFFFF).
    static constexpr std::size_t kMaxChecks = 20000;
    void check_events(EEContext& ctx) override {
        snaps.push_back(snap(ctx));
        if (snaps.size() >= kMaxChecks) {
            stopped = true;
            stop_pc = 0xFFFFFFFFu;
            at_stop = snaps.back();
            throw rt_test::FatalEvent{stop_pc, "runaway", &ctx};
        }
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

struct Run {
    bool stopped = false;
    u32 stop_pc = 0;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
    std::vector<u8> spr;
};

std::optional<u64> g_t0;  // a fixed fifth argument ($t0) for the rule checks

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed) {
    BrHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = sx(world_word(rng));  // a 5th / 6th argument
    if (g_t0) m.ctx.gpr[GPR_T0].u64[0] = *g_t0;
    for (unsigned i = 0; i < 32; ++i) {  // random singles (small magnitudes, zeros, the odd NaN pattern)
        const float f = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / static_cast<float>(1 + rng() % 64);
        u32 bits;
        std::memcpy(&bits, &f, 4);
        m.ctx.fpr[i] = chance(rng, 10) ? rng() : bits;
    }
    m.ctx.fcr31 = rng() & 0x00800000u;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    return r;
}

bool bios_clean(const Machine& m) {
    static const std::vector<u8> zeros(EEMemory::kBiosSize, 0);
    return std::memcmp(const_cast<Machine&>(m).mem.bios(), zeros.data(), EEMemory::kBiosSize) == 0;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;  // missing function -> count
};
std::map<std::string, Stats> g_stats;
const char* g_current = "";

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled run.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    g_current = what;
    std::set_terminate([] {
        std::fprintf(stderr, "terminate in %s\n", g_current);
        std::abort();
    });
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    Run h = run_one(m, hand, args, seed);
    // The BIOS window (0x1FC00000.., and every address that folds onto it, such as 0xFFFFxxxx) is writable guest
    // memory outside the RAM buffer: a stray store through a random pointer lands there. It starts zero; a pair that
    // dirties it is compared there too and leaves it zero again.
    std::vector<u8> bios_h;
    if (!bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    Run r = run_one(m, recomp, args, seed);
    const bool bios_r = !bios_clean(m);
    {
        INFO(what << ": the BIOS window");
        CHECK(bios_r == !bios_h.empty());
        if (bios_r && !bios_h.empty()) CHECK(std::memcmp(bios_h.data(), m.mem.bios(), EEMemory::kBiosSize) == 0);
    }
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
    }
    const std::string name(what);
    INFO(name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " seed=" << seed);
    REQUIRE(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            if (std::getenv("P3FES_BR_DUMP")) {  // the leading check points of both runs, for a failing pair
                for (std::size_t k = 0; k < n && k <= i + 2; ++k)
                    std::fprintf(stderr, "cp %zu: hand c=%llu v0=%llx v1=%llx a0=%llx a1=%llx a2=%llx ra=%llx | recomp c=%llu v0=%llx v1=%llx a0=%llx a1=%llx a2=%llx ra=%llx\n", k,
                                 (unsigned long long)h.snaps[k].cycles, (unsigned long long)h.snaps[k].gpr[2].u64[0], (unsigned long long)h.snaps[k].gpr[3].u64[0],
                                 (unsigned long long)h.snaps[k].gpr[4].u64[0], (unsigned long long)h.snaps[k].gpr[5].u64[0], (unsigned long long)h.snaps[k].gpr[6].u64[0],
                                 (unsigned long long)h.snaps[k].gpr[31].u64[0],
                                 (unsigned long long)r.snaps[k].cycles, (unsigned long long)r.snaps[k].gpr[2].u64[0], (unsigned long long)r.snaps[k].gpr[3].u64[0],
                                 (unsigned long long)r.snaps[k].gpr[4].u64[0], (unsigned long long)r.snaps[k].gpr[5].u64[0], (unsigned long long)r.snaps[k].gpr[6].u64[0],
                                 (unsigned long long)r.snaps[k].gpr[31].u64[0]);
            }
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                                  << unsigned(m.mem.main_ram()[first]));
        CHECK(false);
    }
    {
        std::size_t first = 0;
        while (first < h.spr.size() && h.spr[first] == r.spr[first]) ++first;
        INFO("scratchpad: first differing byte at " << hex64(first));
        CHECK(first == h.spr.size());
    }
    return r;
}

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// --- the specs -----------------------------------------------------------------------------------------------------
// Argument kinds: task = $a0 a world task (task 0 is the root's), index = $a0 a small index (party member, slot, page),
// any = every argument a world word.
// page = the root task with its state word +12 one of the pages sub_1F0D70 knows (7, 9, 8, 12: any other state
// K_Asserts and retries the same state forever in retail).
enum class Arg { task, index, any, page };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};
#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_sub_1F08C0_001f08c0, any),
    SPEC(fn_sub_1F0900_001f0900, any),
    SPEC(fn_sub_1F0940_001f0940, any),
    SPEC(fn_sub_1F0970_001f0970, any),
    SPEC(fn_sub_1F0A60_001f0a60, index),
    SPEC(fn_sub_1F0AB0_001f0ab0, any),
    SPEC(fn_sub_1F0C40_001f0c40, index),
    SPEC(fn_sub_1F0D70_001f0d70, page),
    SPEC(fn_sub_1F0EB0_001f0eb0, index),
    SPEC(fn_sub_1F0F40_001f0f40, index),
    SPEC(fn_sub_1F0FD0_001f0fd0, any),
    SPEC(fn_sub_1F0FF0_001f0ff0, any),
    SPEC(fn_sub_1F10B0_001f10b0, any),
    SPEC(fn_sub_1F10F0_001f10f0, any),
    SPEC(fn_sub_1F1140_001f1140, index),
    SPEC(fn_sub_1F1210_001f1210, any),
    SPEC(fn_sub_1F1240_001f1240, index),
    SPEC(fn_sub_1F1AA0_001f1aa0, any),
    SPEC(fn_sub_1F1AE0_001f1ae0, any),
    SPEC(fn_sub_1F1B00_001f1b00, any),
    SPEC(fn_sub_1F1B20_001f1b20, any),
    SPEC(fn_sub_1F1B40_001f1b40, any),
    SPEC(fn_sub_1F1B60_001f1b60, index),
    SPEC(fn_sub_1F1C20_001f1c20, any),
    SPEC(fn_sub_1F1C50_001f1c50, index),
    SPEC(fn_sub_1F1C90_001f1c90, index),
    SPEC(fn_sub_1F1DF0_001f1df0, index),
    SPEC(fn_sub_1F1E90_001f1e90, index),
    SPEC(fn_sub_1F1F40_001f1f40, index),
    SPEC(fn_sub_1F9D70_001f9d70, index),
    SPEC(fn_sub_1FA0D0_001fa0d0, index),
    SPEC(fn_sub_1FA4F0_001fa4f0, index),
    SPEC(fn_sub_1FAEA0_001faea0, index),
    SPEC(fn_sub_1FB130_001fb130, index),
    SPEC(fn_sub_1FB1B0_001fb1b0, any),
    SPEC(fn_sub_1FB1F0_001fb1f0, index),
    SPEC(fn_sub_1FB3F0_001fb3f0, index),
    SPEC(fn_sub_1FB4B0_001fb4b0, index),
    SPEC(fn_sub_1FBD50_001fbd50, index),
    SPEC(fn_sub_1FBDF0_001fbdf0, index),
    SPEC(fn_sub_1FBFA0_001fbfa0, index),
    SPEC(fn_sub_1FC1F0_001fc1f0, any),
    SPEC(fn_sub_1FC230_001fc230, index),
    SPEC(fn_sub_1FC3C0_001fc3c0, index),
    SPEC(fn_sub_1FC590_001fc590, index),
    SPEC(fn_sub_2338D0_002338d0, any),
    SPEC(fn_sub_2338F0_002338f0, any),
    SPEC(fn_sub_233910_00233910, any),
    SPEC(fn_sub_233930_00233930, any),
    SPEC(fn_sub_233950_00233950, any),
    SPEC(fn_sub_233960_00233960, any),
    SPEC(fn_sub_233970_00233970, index),
    SPEC(fn_sub_233AD0_00233ad0, index),
    SPEC(fn_sub_233BB0_00233bb0, index),
    SPEC(fn_sub_233D20_00233d20, index),
    SPEC(fn_sub_233D70_00233d70, index),
    SPEC(fn_sub_233DF0_00233df0, index),
    SPEC(fn_sub_234570_00234570, index),
    SPEC(fn_sub_2345D0_002345d0, index),
    SPEC(fn_sub_234630_00234630, index),
    SPEC(fn_sub_234690_00234690, index),
    SPEC(fn_sub_2347E0_002347e0, index),
    SPEC(fn_sub_234820_00234820, index),
    SPEC(fn_sub_234960_00234960, index),
    SPEC(fn_sub_234A00_00234a00, index),
    SPEC(fn_sub_235010_00235010, index),
    SPEC(fn_sub_2361D0_002361d0, index),
    SPEC(fn_sub_236280_00236280, index),
    SPEC(fn_sub_2362E0_002362e0, index),
    SPEC(fn_sub_236340_00236340, index),
    SPEC(fn_bpIfontSetDigitQuad_00238fd0, index),
    SPEC(fn_sub_239140_00239140, any),
    SPEC(fn_sub_24A870_0024a870, index),
    SPEC(fn_sub_24AA90_0024aa90, index),
    SPEC(fn_sub_24AB10_0024ab10, index),
    SPEC(fn_sub_24ABD0_0024abd0, index),
    SPEC(fn_sub_24AC40_0024ac40, index),
    SPEC(fn_sub_24ADF0_0024adf0, index),
    SPEC(fn_sub_24B8A0_0024b8a0, index),
    SPEC(fn_sub_24B9E0_0024b9e0, index),
    SPEC(fn_sub_24BA30_0024ba30, any),
    SPEC(fn_sub_24BED0_0024bed0, index),
    SPEC(fn_sub_24BF20_0024bf20, index),
    SPEC(fn_sub_24C040_0024c040, index),
    SPEC(fn_sub_24C090_0024c090, index),
    SPEC(fn_sub_24C100_0024c100, any),
    SPEC(fn_sub_24C110_0024c110, index),
    SPEC(fn_sub_24CF00_0024cf00, index),
    SPEC(fn_sub_24D0C0_0024d0c0, index),
};
#undef SPEC

u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 20) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }

Args args_for(Machine& m, Arg kind, std::mt19937& rng) {
    Args a{};
    for (u64& x : a) x = wide(rng, world_word(rng));
    switch (kind) {
    case Arg::task: a[0] = wide(rng, chance(rng, 70) ? task_of(0) : task_of(rng() % kNumTasks)); break;
    case Arg::page: {
        const u32 t = chance(rng, 70) ? 0 : rng() % kNumTasks;
        a[0] = wide(rng, task_of(t));
        const u32 pages[] = {7, 8, 9, 12};
        store32(m, work_of(t) + 12, pages[rng() % 4]);
        break;
    }
    case Arg::index: a[0] = wide(rng, chance(rng, 90) ? rng() % 14 : rng()); a[1] = wide(rng, chance(rng, 60) ? rng() % 8 : world_word(rng)); break;
    case Arg::any: break;
    }
    return a;
}

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

// The kwln tasks of a snapshot: the three lists (gp-19596, gp-19572, gp-19584), linked through +64.
std::vector<u32> snapshot_tasks(const Machine& m) {
    std::vector<u32> out;
    for (s32 head : {-19596, -19572, -19584}) {
        u32 t = load32(m, gp(head));
        for (int n = 0; t != 0 && t < EEMemory::kMainRamSize - 0x100 && n < 4096; ++n) {
            out.push_back(t);
            t = load32(m, t + 64);
        }
    }
    return out;
}

}  // namespace

TEST_CASE("game(battle_result): every replaced function equals its recompiled body on random result worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    REQUIRE(bios_clean(m));
    std::mt19937 rng{0xB7E5u};
    g_stats.clear();
    constexpr int kWorlds = 70;  // ~3 ms a pair (two PairRange arms over 32 MiB, the BIOS check)
    for (int it = 0; it < kWorlds; ++it) {
        random_world(m, rng);
        for (const Spec& s : kSpecs) {
            const Args a = args_for(m, s.arg, rng);
            pair(m, s.hand, s.recomp, a, rng(), s.name);
        }
    }
    int pairs = 0, stops = 0, complete = 0;
    std::string always_stopped;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        if (st.stops < st.pairs) {
            ++complete;
        } else {
            always_stopped += " " + name + " (at";
            for (const auto& [pc, n] : st.stop_at) always_stopped += " " + hex64(pc);
            always_stopped += ")";
        }
    }
    MESSAGE("battle_result: " << pairs << " pairs over " << std::size(kSpecs) << " functions, " << stops
                              << " ended at a compared missing-function stop; " << complete
                              << " functions also returned normally; always at a stop (a big callee first):" << always_stopped);
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_result): every function on the snapshots' real state (the result screen live at battle 6150)") {
    int ran = 0, live = 0;
    for (const char* dir : {"battle_ref_6150", "b_5800", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(dir);
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        std::mt19937 rng{0x6150u};
        // The live "battle result" task: the kwln task whose work (+60) is gp-18968 (0 outside the result screen).
        const u32 root_work = load32(m, gp(-18968));
        u32 root = 0;
        const std::vector<u32> tasks = snapshot_tasks(m);
        for (u32 t : tasks)
            if (root_work != 0 && load32(m, t + 60) == root_work) root = t;
        if (root != 0) ++live;
        for (int rep = 0; rep < 3; ++rep) {
            for (const Spec& s : kSpecs) {
                Args a{};
                for (u64& x : a) x = sx(rng() % 12);
                if (s.arg == Arg::task || s.arg == Arg::page)
                    a[0] = sx(root != 0 ? root : (tasks.empty() ? 0u : tasks[rng() % tasks.size()]));
                if (s.arg == Arg::page && root != 0) {
                    const u32 st = load32(m, root_work + 12);
                    if (st != 7 && st != 8 && st != 9 && st != 12) continue;  // the retail endless K_Assert loop
                }
                pair(m, s.hand, s.recomp, a, rng(), s.name);
                ++ran;
            }
            std::memcpy(m.mem.main_ram(), snap.data(), snap.size());  // every repetition from the snapshot again
        }
    }
    MESSAGE("snapshots: " << ran << " pairs; the result root live in " << live << " snapshot(s)");
}

TEST_CASE("game(battle_result): the result functions follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xDA7Au};
    int checks = 0;
    for (int it = 0; it < 80; ++it) {
        random_world(m, rng);
        const u32 w = work_of(0);
        const Args task{sx(task_of(0)), 0, 0, 0};
        // 1. The root's flag accessors: sub_1F1B00 = flags & 1, sub_1F1B40 = flags & 0x2000; sub_1F1B20 sets 0x2000.
        const u32 flags = load32(m, w);
        CHECK(v0_of(pair(m, PAIR(fn_sub_1F1B00_001f1b00), task, rng(), "rule 1F1B00")) == (flags & 1u));
        CHECK(v0_of(pair(m, PAIR(fn_sub_1F1B40_001f1b40), task, rng(), "rule 1F1B40")) == (flags & 0x2000u));
        pair(m, PAIR(fn_sub_1F1B20_001f1b20), task, rng(), "rule 1F1B20");
        CHECK(load32(m, w) == (flags | 0x2000u));
        // 2. sub_1F0AB0: +40 = 0, state 7.
        pair(m, PAIR(fn_sub_1F0AB0_001f0ab0), task, rng(), "rule 1F0AB0");
        CHECK(load32(m, w + 40) == 0);
        CHECK(load32(m, w + 12) == 7);
        // 3. sub_1F1C50 returns gp-18968 (sign-extended).
        CHECK(v0_of(pair(m, PAIR(fn_sub_1F1C50_001f1c50), Args{}, rng(), "rule 1F1C50")) == sx(load32(m, gp(-18968))));
        // 4. sub_1F1DF0: out[0] = 1, out[1 + i] = +268[i], *count = n + 1.
        {
            const u32 n = rng() % 5;
            store32(m, gp(-18968), w);
            store32(m, w + 276, n);
            u16 ids[4];
            for (u32 i = 0; i < 4; ++i) {
                ids[i] = static_cast<u16>(rng());
                store16(m, w + 268 + 2 * i, ids[i]);
            }
            const u32 out = kRecords + 0x100, cnt = kRecords + 0x200;
            pair(m, PAIR(fn_sub_1F1DF0_001f1df0), Args{sx(out), sx(cnt), 0, 0}, rng(), "rule 1F1DF0");
            u16 first;
            std::memcpy(&first, m.at(out), 2);
            CHECK(first == 1);
            for (u32 i = 0; i < n; ++i) {
                u16 v;
                std::memcpy(&v, m.at(out + 2 + 2 * i), 2);
                CHECK(v == ids[i]);
            }
            CHECK(load32(m, cnt) == n + 1);
        }
        // 5. The br_res accessors: +56 / +72 / +28 / +36 / +48 + 4 i, +44.
        {
            const u32 res = kRecords + 0x1000;
            store32(m, gp(-18916), res);
            store32(m, res + 4, load32(m, res + 4) | 0x10u);
            const u32 i = rng() % 4;
            CHECK(v0_of(pair(m, PAIR(fn_sub_233D70_00233d70), Args{i, 0, 0, 0}, rng(), "rule 233D70")) == sx(load32(m, res + 56 + 4 * i)));
            CHECK(v0_of(pair(m, PAIR(fn_sub_233DF0_00233df0), Args{i, 0, 0, 0}, rng(), "rule 233DF0")) == sx(load32(m, res + 72 + 4 * i)));
            CHECK(v0_of(pair(m, PAIR(fn_sub_234570_00234570), Args{i, 0, 0, 0}, rng(), "rule 234570")) == sx(load32(m, res + 28 + 4 * i)));
            CHECK(v0_of(pair(m, PAIR(fn_sub_2345D0_002345d0), Args{i, 0, 0, 0}, rng(), "rule 2345D0")) == sx(load32(m, res + 36 + 4 * i)));
            CHECK(v0_of(pair(m, PAIR(fn_sub_234630_00234630), Args{i, 0, 0, 0}, rng(), "rule 234630")) == sx(load32(m, res + 48 + 4 * i)));
            CHECK(v0_of(pair(m, PAIR(fn_sub_2347E0_002347e0), Args{}, rng(), "rule 2347E0")) == sx(load32(m, res + 44)));
        }
        // 6. The panel's open / close: +9832 = 0, kind 1 / 2, flag 0x2; the step counts to 10 and then clears 0x2.
        {
            const u32 panel = kRecords + 0x3000;
            store32(m, gp(-18912), panel);
            pair(m, PAIR(fn_sub_236280_00236280), Args{}, rng(), "rule 236280");
            CHECK(load32(m, panel + 9836) == 1);
            CHECK(load32(m, panel + 9832) == 0);
            CHECK((load32(m, panel) & 2u) == 2u);
            store32(m, panel, load32(m, panel) | 1u);
            const u32 frame = rng() % 12;
            store32(m, panel + 9832, frame);
            pair(m, PAIR(fn_sub_235010_00235010), Args{}, rng(), "rule 235010");  // stops in sub_236390 (not emitted)
            if (frame < 10) CHECK(load32(m, panel + 9832) == frame + 1);
            else CHECK((load32(m, panel) & 2u) == 0u);
        }
        // 7. sub_1FB3F0 against a host scan of a 10-byte row table.
        {
            const u32 rows = kRecords + 0x5000;
            const u32 nrows = 1 + rng() % 12;
            for (u32 r = 0; r < nrows; ++r) {
                m.at(rows + 10 * r)[0] = static_cast<u8>(rng() % 40);
                for (u32 k = 0; k < 4; ++k) store16(m, rows + 10 * r + 2 + 2 * k, static_cast<u16>(chance(rng, 70) ? 1 + rng() % 500 : 0));
                if (load32(m, rows + 10 * r + 2) == 0 && load32(m, rows + 10 * r + 6) == 0) store16(m, rows + 10 * r + 2, 7);
            }
            for (u32 k = 0; k < 8; ++k) m.at(rows + 10 * nrows + 2 + k)[0] = 0;
            const u32 level = rng() % 40, gained = rng() % 10;
            const u32 out_first = kRecords + 0x5800, out_count = kRecords + 0x5810;
            // first matching row and (last - first + 1), or 0 / 0 (the count pointer is the fifth argument, $t0)
            bool any = false;
            u32 first = 0, last = 0;
            for (u32 r = 0; r < nrows; ++r) {
                const u32 lv = m.at(rows + 10 * r)[0];
                if (level < lv && lv <= level + gained) {
                    if (!any) first = r;
                    any = true;
                    last = r;
                }
            }
            g_t0 = sx(out_count);
            pair(m, PAIR(fn_sub_1FB3F0_001fb3f0), Args{sx(rows), sx(level), sx(gained), sx(out_first)},
                 rng(), "rule 1FB3F0");
            g_t0.reset();
            CHECK(load32(m, out_first) == (any ? first : 0u));
            CHECK(load32(m, out_count) == (any ? last - first + 1 : 0u));
        }
        checks += 20;
    }
    // 8. sub_1F9D70: members 2..5 and 7..10 raise flags 4625..4628, 4630..4633 (host decode of jump table 0x7B70E0:
    //    each case is `addiu a0, zero, flag` at its target); the others K_Assert and raise nothing.
    int flags_seen = 0;
    for (u32 member = 0; member < 12; ++member) {
        random_world(m, rng);
        for (u32 i = 0; i < 0x2C0; i += 4) store32(m, 0x83A21Cu + i, 0);  // the 0x1600 flag bits
        int want = -1;
        if (member < 11) {
            const u32 target = load32(m, 0x7B70E0u + 4 * member);
            const u32 insn = load32(m, target);
            if ((insn & 0xFFFF0000u) == 0x24040000u) want = static_cast<int>(insn & 0xFFFFu);
        }
        pair(m, PAIR(fn_sub_1F9D70_001f9d70), Args{sx(member), 0, 0, 0}, rng(), "rule 1F9D70");
        int set = -1, nset = 0;
        for (u32 id = 0; id < 0x1600; ++id)
            if (load32(m, 0x83A21Cu + 4 * (id / 32)) & (1u << (id % 32))) set = static_cast<int>(id), ++nset;
        INFO("member " << member);
        CHECK(set == want);
        CHECK(nset == (want >= 0 ? 1 : 0));
        flags_seen += want >= 0;
    }
    CHECK(flags_seen == 8);
    MESSAGE("rules: " << checks << " checks on random worlds, " << flags_seen << " member flags");
}

#else
TEST_CASE("game(battle_result): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
