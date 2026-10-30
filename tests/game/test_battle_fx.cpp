// Phase 5 pair tests for slice battle_fx (game/src/battle/battle_fx.cpp): every hand-written battle-effect function and
// the recompiled body it replaces run on identical guest machines -- a random effect world (words that are small values,
// zeros, pointers back into the world, the odd function address of this slice so the `jalr` callbacks run a non-leaf
// callee that spills $ra below the $sp it receives; the gp-relative records the bodies read -- the battle work
// gp-18692, gp-18680, gp-18436 -- pointing into the world or left 0) and a random register file (GPRs in 128 bits,
// FPRs, FCR31) -- and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31, the VU0 macro registers) and cycle count at
//     EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * the whole 32 MiB of main RAM (a PairRange, write_tracker.h: the world, .data / .bss, the stack with the frames and
//     spills of the run, whatever a random pointer reached), the scratchpad and the BIOS window.
// The packet allocator sub_27EC10 is emitted and allocates through the RW heap pointer 0x960178: the random worlds point
// it at a leaf that hands out a free world record (random_world), so the packet creators run to the end; the rest of
// the worlds leave it 0 and those paths end at a compared stop. The real snapshots battle_ref_6150 / b_5800 / dorm_replay_4900 run
// the functions on the game's own state: the kwln tasks (the "battle_command_calc" / "battle_command_draw" tasks are
// alive in b_5800), the effect packets whose callbacks (+104 / +108) are functions of this slice, and the unit records.
// Documented rules (battle_fx.h) are checked on the host.
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/game/battle_fx.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
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
P3FES_DECL_PAIR(fn_sub_2B77C0_002b77c0)
P3FES_DECL_PAIR(fn_sub_2B79E0_002b79e0)
P3FES_DECL_PAIR(fn_sub_2B7BD0_002b7bd0)
P3FES_DECL_PAIR(fn_sub_2B7C50_002b7c50)
P3FES_DECL_PAIR(fn_sub_2B8900_002b8900)
P3FES_DECL_PAIR(fn_sub_2B8970_002b8970)
P3FES_DECL_PAIR(fn_sub_2B8990_002b8990)
P3FES_DECL_PAIR(fn_sub_2B8B50_002b8b50)
P3FES_DECL_PAIR(fn_sub_2B8B70_002b8b70)
P3FES_DECL_PAIR(fn_sub_2B8C00_002b8c00)
P3FES_DECL_PAIR(fn_sub_2B8D60_002b8d60)
P3FES_DECL_PAIR(fn_sub_2B8DC0_002b8dc0)
P3FES_DECL_PAIR(fn_sub_2B8F40_002b8f40)
P3FES_DECL_PAIR(fn_sub_2B90D0_002b90d0)
P3FES_DECL_PAIR(fn_sub_2B9220_002b9220)
P3FES_DECL_PAIR(fn_sub_2B9300_002b9300)
P3FES_DECL_PAIR(fn_sub_2B9350_002b9350)
P3FES_DECL_PAIR(fn_sub_2B9370_002b9370)
P3FES_DECL_PAIR(fn_sub_2B93C0_002b93c0)
P3FES_DECL_PAIR(fn_sub_2B9590_002b9590)
P3FES_DECL_PAIR(fn_sub_2B9600_002b9600)
P3FES_DECL_PAIR(fn_sub_2B9640_002b9640)
P3FES_DECL_PAIR(fn_sub_2B96E0_002b96e0)
P3FES_DECL_PAIR(fn_sub_2B96F0_002b96f0)
P3FES_DECL_PAIR(fn_sub_2B99D0_002b99d0)
P3FES_DECL_PAIR(fn_sub_2B9B00_002b9b00)
P3FES_DECL_PAIR(fn_sub_2B9C00_002b9c00)
P3FES_DECL_PAIR(fn_sub_2B9D40_002b9d40)
P3FES_DECL_PAIR(fn_sub_2B9E80_002b9e80)
P3FES_DECL_PAIR(fn_sub_2B9F30_002b9f30)
P3FES_DECL_PAIR(fn_sub_2BA000_002ba000)
P3FES_DECL_PAIR(fn_sub_2BA0D0_002ba0d0)
P3FES_DECL_PAIR(fn_sub_2BA0F0_002ba0f0)
P3FES_DECL_PAIR(fn_sub_2BA3A0_002ba3a0)
P3FES_DECL_PAIR(fn_sub_2BA900_002ba900)
P3FES_DECL_PAIR(fn_sub_2BAC00_002bac00)
P3FES_DECL_PAIR(fn_sub_2BACB0_002bacb0)
P3FES_DECL_PAIR(fn_sub_2BAD60_002bad60)
P3FES_DECL_PAIR(fn_sub_2BAEC0_002baec0)
P3FES_DECL_PAIR(fn_sub_2BAF30_002baf30)
P3FES_DECL_PAIR(fn_sub_2BAF90_002baf90)
P3FES_DECL_PAIR(fn_sub_2BB050_002bb050)
P3FES_DECL_PAIR(fn_sub_2BB0B0_002bb0b0)
P3FES_DECL_PAIR(fn_sub_2BB290_002bb290)
P3FES_DECL_PAIR(fn_sub_2BB2F0_002bb2f0)
P3FES_DECL_PAIR(fn_sub_2BB3A0_002bb3a0)
P3FES_DECL_PAIR(fn_sub_2BB580_002bb580)
P3FES_DECL_PAIR(fn_nullsub_14_002bb760)
P3FES_DECL_PAIR(fn_sub_2BB770_002bb770)
P3FES_DECL_PAIR(fn_sub_2BB9C0_002bb9c0)
P3FES_DECL_PAIR(fn_sub_2BBAC0_002bbac0)
P3FES_DECL_PAIR(fn_sub_2BBBC0_002bbbc0)
P3FES_DECL_PAIR(fn_sub_2BBDC0_002bbdc0)
P3FES_DECL_PAIR(fn_sub_2BBDF0_002bbdf0)
P3FES_DECL_PAIR(fn_sub_2BBE00_002bbe00)
P3FES_DECL_PAIR(fn_sub_2BBF80_002bbf80)
P3FES_DECL_PAIR(fn_sub_2BBFA0_002bbfa0)
P3FES_DECL_PAIR(fn_sub_2BC0E0_002bc0e0)
P3FES_DECL_PAIR(fn_sub_2BC680_002bc680)
P3FES_DECL_PAIR(fn_sub_2BC7B0_002bc7b0)
P3FES_DECL_PAIR(fn_sub_2BC7E0_002bc7e0)
P3FES_DECL_PAIR(fn_sub_2BC830_002bc830)
P3FES_DECL_PAIR(fn_sub_2BC890_002bc890)
P3FES_DECL_PAIR(fn_sub_2BC910_002bc910)
P3FES_DECL_PAIR(fn_sub_2BC950_002bc950)
P3FES_DECL_PAIR(fn_sub_2BCDE0_002bcde0)
P3FES_DECL_PAIR(fn_sub_2BCE10_002bce10)
P3FES_DECL_PAIR(fn_sub_2BD060_002bd060)
P3FES_DECL_PAIR(fn_sub_2BD080_002bd080)
P3FES_DECL_PAIR(fn_sub_2BD210_002bd210)
P3FES_DECL_PAIR(fn_sub_2BD230_002bd230)
P3FES_DECL_PAIR(fn_sub_2BD2C0_002bd2c0)
P3FES_DECL_PAIR(fn_sub_2BD2E0_002bd2e0)
P3FES_DECL_PAIR(fn_sub_2BD460_002bd460)
P3FES_DECL_PAIR(fn_sub_2BD480_002bd480)
P3FES_DECL_PAIR(fn_sub_2BD590_002bd590)
P3FES_DECL_PAIR(fn_sub_2BD690_002bd690)
P3FES_DECL_PAIR(fn_sub_2BD780_002bd780)
P3FES_DECL_PAIR(fn_sub_2BD850_002bd850)
P3FES_DECL_PAIR(fn_sub_2BD8B0_002bd8b0)
P3FES_DECL_PAIR(fn_sub_2BDBA0_002bdba0)
P3FES_DECL_PAIR(fn_sub_2BDBD0_002bdbd0)
P3FES_DECL_PAIR(fn_sub_2BDCD0_002bdcd0)
P3FES_DECL_PAIR(fn_sub_2BDDD0_002bddd0)
P3FES_DECL_PAIR(fn_sub_2BDE10_002bde10)
P3FES_DECL_PAIR(fn_sub_2BDFB0_002bdfb0)
P3FES_DECL_PAIR(fn_nullsub_100_002be2e0)
P3FES_DECL_PAIR(fn_sub_2BE2F0_002be2f0)
P3FES_DECL_PAIR(fn_sub_2BE390_002be390)
P3FES_DECL_PAIR(fn_sub_2BE580_002be580)
P3FES_DECL_PAIR(fn_sub_2BE5D0_002be5d0)
P3FES_DECL_PAIR(fn_sub_2BE5F0_002be5f0)
P3FES_DECL_PAIR(fn_sub_2BE610_002be610)
P3FES_DECL_PAIR(fn_sub_2BE620_002be620)
P3FES_DECL_PAIR(fn_sub_2BE720_002be720)
P3FES_DECL_PAIR(fn_nullsub_101_002be9d0)
P3FES_DECL_PAIR(fn_sub_2BE9E0_002be9e0)
P3FES_DECL_PAIR(fn_sub_2BEA80_002bea80)
P3FES_DECL_PAIR(fn_sub_2BECC0_002becc0)
P3FES_DECL_PAIR(fn_btlCommand_UpdateBattleCommandCalcTask_002bef20)
P3FES_DECL_PAIR(fn_btlCommand_UpdateBattleCommandDrawTask_002bf2b0)
P3FES_DECL_PAIR(fn_sub_2BF650_002bf650)
P3FES_DECL_PAIR(fn_nullsub_15_002bf970)
P3FES_DECL_PAIR(fn_nullsub_16_002bf980)
P3FES_DECL_PAIR(fn_nullsub_17_002bf990)
P3FES_DECL_PAIR(fn_nullsub_18_002bf9a0)
P3FES_DECL_PAIR(fn_sub_2BF9B0_002bf9b0)
P3FES_DECL_PAIR(fn_sub_2BFAB0_002bfab0)
P3FES_DECL_PAIR(fn_sub_2BFAE0_002bfae0)
P3FES_DECL_PAIR(fn_sub_2BFB20_002bfb20)
P3FES_DECL_PAIR(fn_sub_2BFB50_002bfb50)
P3FES_DECL_PAIR(fn_sub_2BFB90_002bfb90)
P3FES_DECL_PAIR(fn_sub_2BFC00_002bfc00)
P3FES_DECL_PAIR(fn_sub_2BFC50_002bfc50)
P3FES_DECL_PAIR(fn_sub_2BFC70_002bfc70)
P3FES_DECL_PAIR(fn_sub_2BFC90_002bfc90)
P3FES_DECL_PAIR(fn_sub_2BFCB0_002bfcb0)
P3FES_DECL_PAIR(fn_sub_2BFF60_002bff60)
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

// --- the effect world (free RAM above the arena) --------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x20000u;
constexpr u32 kTasks = kWorld;              // 8 kwln tasks, 0x100 apart (+0x34 update, +0x3C work)
constexpr u32 kNumTasks = 8;
constexpr u32 kWorks = kWorld + 0x1000u;    // their work records, 0x3000 apart
constexpr u32 kRecords = kWorld + 0x19000u; // records the gp words and the world's pointers point at, 0x7000 bytes
constexpr u32 task_of(u32 i) { return kTasks + 0x100u * i; }
constexpr u32 work_of(u32 i) { return kWorks + 0x3000u * i; }
constexpr u32 kGp = 0x7D2CF0u;
constexpr u32 gp(s32 off) { return kGp + static_cast<u32>(off); }

// The gp words the bodies read: each points into the world, at a work record, or is 0.
const s32 kGpWords[] = {-18692, -18680, -18436};
// Function addresses a world word may hold (callbacks reached through `jalr`): sub_2BD080 opens a frame and spills $ra
// below the $sp it receives, sub_2B8970 / sub_2BD060 are leaves, nullsub_14 returns at once.
const u32 kCallbacks[] = {0x2BD080u, 0x2B8970u, 0x2BD060u, 0x2BB760u};

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
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }

// A world word: small values (switch indices, counts, ids, kinds), zeros, pointers into the world, random bits.
u32 world_word(std::mt19937& rng) {
    const unsigned k = rng() % 100;
    if (k < 30) return rng() % 16;
    if (k < 45) return 0;
    if (k < 62) return kRecords + (rng() % 0x7000u & ~15u);
    if (k < 70) return work_of(rng() % kNumTasks) + (chance(rng, 50) ? 0 : (rng() % 0x400u & ~3u));
    if (k < 73) return kCallbacks[rng() % std::size(kCallbacks)];
    if (k < 78) return rng() % 0x10000u;
    return rng();
}

// The packet allocator sub_27EC10 calls RwMalloc through the RW heap pointer 0x960178 (0 in the test image: a compared
// stop). In most worlds the pointer is set to sub_1F1C50, a leaf that returns the word gp-18968, which then names a
// free world record: the allocation "succeeds" and the creators run to the end, filling the payload and the callbacks.
constexpr u32 kRwMallocSlot = 0x960178u;
constexpr u32 kFakeMalloc = 0x1F1C50u;
constexpr s32 kGpFakeMallocResult = -18968;

void random_world(Machine& m, std::mt19937& rng) {
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, world_word(rng));
    for (u32 i = 0; i < kNumTasks; ++i) store32(m, task_of(i) + 0x3C, work_of(i));
    for (s32 off : kGpWords) {
        const unsigned k = rng() % 100;
        store32(m, gp(off), k < 8 ? 0u : k < 60 ? kRecords + (rng() % 0x6000u & ~15u) : work_of(rng() % kNumTasks));
    }
    const bool malloc_ok = chance(rng, 75);
    store32(m, kRwMallocSlot, malloc_ok ? kFakeMalloc : 0u);
    store32(m, gp(kGpFakeMallocResult), kRecords + 0x6000u + (rng() % 0x400u & ~15u));
}

// --- the register file at a check point / the return / a stop ----------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0, acc = 0;
    std::array<u32, 32> fpr{};
    VU0State vu0{};  // the VU0 macro registers (vf, vi, ACC, Q, flags) the position solver and the orientation use
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
    s.vu0 = c.vu0;
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
    {  // field by field (the struct has padding)
        const VU0State &x = a.vu0, &y = b.vu0;
        if (std::memcmp(x.vf, y.vf, sizeof x.vf) != 0) return "vu0 vf";
        if (std::memcmp(x.vi, y.vi, sizeof x.vi) != 0) return "vu0 vi";
        if (std::memcmp(x.acc, y.acc, sizeof x.acc) != 0) return "vu0 acc";
        if (x.q != y.q || x.p != y.p || x.i != y.i || x.r != y.r) return "vu0 q/p/i/r";
        if (x.status != y.status || x.mac != y.mac || x.clip != y.clip) return "vu0 flags";
    }
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds).
class FxHooks final : public RtHooks {
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
    // A body that walks random data without end (a list that loops) is cut at the same check point in both runs and
    // compared there like a missing-function stop (stop_pc 0xFFFFFFFF).
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

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed) {
    FxHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = sx(world_word(rng));  // arguments 5..8
    for (unsigned i = 0; i < 32; ++i) {  // random singles (small magnitudes, zeros, the odd NaN pattern)
        const float f = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / static_cast<float>(1 + rng() % 64);
        u32 bits;
        std::memcpy(&bits, &f, 4);
        m.ctx.fpr[i] = chance(rng, 10) ? rng() : bits;
    }
    m.ctx.fcr31 = rng() & 0x00800000u;
    for (unsigned r = 1; r < 32; ++r)  // VU0: random singles in vf01..vf31, and ACC
        for (u32& x : m.ctx.vu0.vf[r]) {
            const float f = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / static_cast<float>(1 + rng() % 64);
            std::memcpy(&x, &f, 4);
        }
    for (u32& x : m.ctx.vu0.acc) x = rng() & 0x7F7FFFFFu;
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
    // The BIOS window is writable guest memory outside the RAM buffer: a stray store through a random pointer lands
    // there. It starts zero; a pair that dirties it is compared there too and leaves it zero again.
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
// Argument kinds: ptr = $a0 a world record (an effect packet, a unit, a work), task = $a0 a world kwln task (the task
// updates), any = every argument a world word.
enum class Arg { ptr, task, any };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};
#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_sub_2B77C0_002b77c0, ptr),
    SPEC(fn_sub_2B79E0_002b79e0, ptr),
    SPEC(fn_sub_2B7BD0_002b7bd0, ptr),
    SPEC(fn_sub_2B7C50_002b7c50, ptr),
    SPEC(fn_sub_2B8900_002b8900, ptr),
    SPEC(fn_sub_2B8970_002b8970, ptr),
    SPEC(fn_sub_2B8990_002b8990, ptr),
    SPEC(fn_sub_2B8B50_002b8b50, ptr),
    SPEC(fn_sub_2B8B70_002b8b70, ptr),
    SPEC(fn_sub_2B8C00_002b8c00, ptr),
    SPEC(fn_sub_2B8D60_002b8d60, ptr),
    SPEC(fn_sub_2B8DC0_002b8dc0, ptr),
    SPEC(fn_sub_2B8F40_002b8f40, ptr),
    SPEC(fn_sub_2B90D0_002b90d0, ptr),
    SPEC(fn_sub_2B9220_002b9220, ptr),
    SPEC(fn_sub_2B9300_002b9300, ptr),
    SPEC(fn_sub_2B9350_002b9350, ptr),
    SPEC(fn_sub_2B9370_002b9370, ptr),
    SPEC(fn_sub_2B93C0_002b93c0, ptr),
    SPEC(fn_sub_2B9590_002b9590, ptr),
    SPEC(fn_sub_2B9600_002b9600, ptr),
    SPEC(fn_sub_2B9640_002b9640, ptr),
    SPEC(fn_sub_2B96E0_002b96e0, ptr),
    SPEC(fn_sub_2B96F0_002b96f0, ptr),
    SPEC(fn_sub_2B99D0_002b99d0, ptr),
    SPEC(fn_sub_2B9B00_002b9b00, ptr),
    SPEC(fn_sub_2B9C00_002b9c00, ptr),
    SPEC(fn_sub_2B9D40_002b9d40, ptr),
    SPEC(fn_sub_2B9E80_002b9e80, ptr),
    SPEC(fn_sub_2B9F30_002b9f30, ptr),
    SPEC(fn_sub_2BA000_002ba000, ptr),
    SPEC(fn_sub_2BA0D0_002ba0d0, ptr),
    SPEC(fn_sub_2BA0F0_002ba0f0, ptr),
    SPEC(fn_sub_2BA3A0_002ba3a0, ptr),
    SPEC(fn_sub_2BA900_002ba900, ptr),
    SPEC(fn_sub_2BAC00_002bac00, ptr),
    SPEC(fn_sub_2BACB0_002bacb0, ptr),
    SPEC(fn_sub_2BAD60_002bad60, ptr),
    SPEC(fn_sub_2BAEC0_002baec0, ptr),
    SPEC(fn_sub_2BAF30_002baf30, ptr),
    SPEC(fn_sub_2BAF90_002baf90, ptr),
    SPEC(fn_sub_2BB050_002bb050, ptr),
    SPEC(fn_sub_2BB0B0_002bb0b0, ptr),
    SPEC(fn_sub_2BB290_002bb290, ptr),
    SPEC(fn_sub_2BB2F0_002bb2f0, ptr),
    SPEC(fn_sub_2BB3A0_002bb3a0, any),
    SPEC(fn_sub_2BB580_002bb580, ptr),
    SPEC(fn_nullsub_14_002bb760, any),
    SPEC(fn_sub_2BB770_002bb770, any),
    SPEC(fn_sub_2BB9C0_002bb9c0, ptr),
    SPEC(fn_sub_2BBAC0_002bbac0, ptr),
    SPEC(fn_sub_2BBBC0_002bbbc0, ptr),
    SPEC(fn_sub_2BBDC0_002bbdc0, ptr),
    SPEC(fn_sub_2BBDF0_002bbdf0, ptr),
    SPEC(fn_sub_2BBE00_002bbe00, ptr),
    SPEC(fn_sub_2BBF80_002bbf80, ptr),
    SPEC(fn_sub_2BBFA0_002bbfa0, ptr),
    SPEC(fn_sub_2BC0E0_002bc0e0, ptr),
    SPEC(fn_sub_2BC680_002bc680, any),
    SPEC(fn_sub_2BC7B0_002bc7b0, ptr),
    SPEC(fn_sub_2BC7E0_002bc7e0, ptr),
    SPEC(fn_sub_2BC830_002bc830, ptr),
    SPEC(fn_sub_2BC890_002bc890, ptr),
    SPEC(fn_sub_2BC910_002bc910, ptr),
    SPEC(fn_sub_2BC950_002bc950, ptr),
    SPEC(fn_sub_2BCDE0_002bcde0, ptr),
    SPEC(fn_sub_2BCE10_002bce10, ptr),
    SPEC(fn_sub_2BD060_002bd060, ptr),
    SPEC(fn_sub_2BD080_002bd080, ptr),
    SPEC(fn_sub_2BD210_002bd210, ptr),
    SPEC(fn_sub_2BD230_002bd230, ptr),
    SPEC(fn_sub_2BD2C0_002bd2c0, ptr),
    SPEC(fn_sub_2BD2E0_002bd2e0, ptr),
    SPEC(fn_sub_2BD460_002bd460, ptr),
    SPEC(fn_sub_2BD480_002bd480, ptr),
    SPEC(fn_sub_2BD590_002bd590, ptr),
    SPEC(fn_sub_2BD690_002bd690, ptr),
    SPEC(fn_sub_2BD780_002bd780, ptr),
    SPEC(fn_sub_2BD850_002bd850, ptr),
    SPEC(fn_sub_2BD8B0_002bd8b0, ptr),
    SPEC(fn_sub_2BDBA0_002bdba0, ptr),
    SPEC(fn_sub_2BDBD0_002bdbd0, ptr),
    SPEC(fn_sub_2BDCD0_002bdcd0, ptr),
    SPEC(fn_sub_2BDDD0_002bddd0, any),
    SPEC(fn_sub_2BDE10_002bde10, ptr),
    SPEC(fn_sub_2BDFB0_002bdfb0, ptr),
    SPEC(fn_nullsub_100_002be2e0, any),
    SPEC(fn_sub_2BE2F0_002be2f0, any),
    SPEC(fn_sub_2BE390_002be390, ptr),
    SPEC(fn_sub_2BE580_002be580, ptr),
    SPEC(fn_sub_2BE5D0_002be5d0, ptr),
    SPEC(fn_sub_2BE5F0_002be5f0, ptr),
    SPEC(fn_sub_2BE610_002be610, ptr),
    SPEC(fn_sub_2BE620_002be620, ptr),
    SPEC(fn_sub_2BE720_002be720, ptr),
    SPEC(fn_nullsub_101_002be9d0, any),
    SPEC(fn_sub_2BE9E0_002be9e0, ptr),
    SPEC(fn_sub_2BEA80_002bea80, ptr),
    SPEC(fn_sub_2BECC0_002becc0, any),
    SPEC(fn_btlCommand_UpdateBattleCommandCalcTask_002bef20, task),
    SPEC(fn_btlCommand_UpdateBattleCommandDrawTask_002bf2b0, task),
    SPEC(fn_sub_2BF650_002bf650, any),
    SPEC(fn_nullsub_15_002bf970, any),
    SPEC(fn_nullsub_16_002bf980, any),
    SPEC(fn_nullsub_17_002bf990, any),
    SPEC(fn_nullsub_18_002bf9a0, any),
    SPEC(fn_sub_2BF9B0_002bf9b0, any),
    SPEC(fn_sub_2BFAB0_002bfab0, any),
    SPEC(fn_sub_2BFAE0_002bfae0, any),
    SPEC(fn_sub_2BFB20_002bfb20, any),
    SPEC(fn_sub_2BFB50_002bfb50, any),
    SPEC(fn_sub_2BFB90_002bfb90, ptr),
    SPEC(fn_sub_2BFC00_002bfc00, any),
    SPEC(fn_sub_2BFC50_002bfc50, any),
    SPEC(fn_sub_2BFC70_002bfc70, any),
    SPEC(fn_sub_2BFC90_002bfc90, any),
    SPEC(fn_sub_2BFCB0_002bfcb0, ptr),
    SPEC(fn_sub_2BFF60_002bff60, ptr),
};
#undef SPEC

u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 20) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }

Args args_for(Arg kind, std::mt19937& rng) {
    Args a{};
    for (u64& x : a) x = wide(rng, world_word(rng));
    switch (kind) {
    case Arg::ptr: a[0] = wide(rng, chance(rng, 85) ? kRecords + (rng() % 0x6000u & ~15u) : world_word(rng)); break;
    case Arg::task: a[0] = wide(rng, task_of(rng() % kNumTasks)); break;
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

// The kwln tasks of a snapshot: the three lists (gp-19596, gp-19572, gp-19584), linked through +0x40.
std::vector<u32> snapshot_tasks(const Machine& m) {
    std::vector<u32> out;
    for (s32 head : {-19596, -19572, -19584}) {
        u32 t = load32(m, gp(head));
        for (int n = 0; t != 0 && t < EEMemory::kMainRamSize - 0x100 && n < 4096; ++n) {
            out.push_back(t);
            t = load32(m, t + 0x40);
        }
    }
    return out;
}

bool in_slice(u32 a) { return a >= 0x2B7060u && a < 0x2C006Cu; }

}  // namespace

TEST_CASE("game(battle_fx): every replaced function equals its recompiled body on random effect worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    REQUIRE(bios_clean(m));
    std::mt19937 rng{0xBEDu};
    g_stats.clear();
    constexpr int kWorlds = 60;
    for (int it = 0; it < kWorlds; ++it) {
        random_world(m, rng);
        for (const Spec& s : kSpecs) {
            const Args a = args_for(s.arg, rng);
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
    MESSAGE("battle_fx: " << pairs << " pairs over " << std::size(kSpecs) << " functions, " << stops
                          << " ended at a compared stop; " << complete
                          << " functions also returned normally; always at a stop:" << always_stopped);
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_fx): every function on the snapshots' real state (tasks, effect packets, units)") {
    int ran = 0, cmd_tasks = 0, packets = 0;
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
        std::mt19937 rng{0x5800u};
        const std::vector<u32> tasks = snapshot_tasks(m);
        // The command tasks (update 0x2BEF20 "battle_command_calc" / 0x2BF2B0 "battle_command_draw"): the live ones and
        // the stale records left in RAM after the command phase (name at +0, update +0x34, work +0x3C).
        std::vector<u32> cmd;
        for (u32 t = 0x100000u; t + 0x60 < EEMemory::kMainRamSize; t += 16) {
            const u32 upd = load32(m, t + 0x34);
            if ((upd == 0x2BEF20u || upd == 0x2BF2B0u) && std::memcmp(m.at(t), "battle_command_", 15) == 0) cmd.push_back(t);
        }
        cmd_tasks += static_cast<int>(cmd.size());
        // Effect packets: records whose callback words +104 / +108 are functions of this slice.
        std::vector<u32> pk;
        for (u32 a = 0x100000u; a + 112 < EEMemory::kMainRamSize && pk.size() < 64; a += 16) {
            const u32 c1 = load32(m, a + 104), c2 = load32(m, a + 108);
            if ((in_slice(c1) || in_slice(c2)) && load32(m, a + 120) == a + 144) pk.push_back(a);
        }
        packets += static_cast<int>(pk.size());
        // The battle work's pointers (gp-18692): its first words are unit / record pointers.
        const u32 bw = load32(m, gp(-18692));
        for (int rep = 0; rep < 3; ++rep) {
            for (const Spec& s : kSpecs) {
                Args a{};
                for (u64& x : a) x = sx(rng() % 12);
                if (s.arg == Arg::task) {
                    a[0] = sx(!cmd.empty() ? cmd[rng() % cmd.size()] : (tasks.empty() ? 0u : tasks[rng() % tasks.size()]));
                } else if (s.arg == Arg::ptr) {
                    const unsigned k = rng() % 3;
                    if (k == 0 && !pk.empty()) a[0] = sx(pk[rng() % pk.size()]);
                    else if (k == 1 && !tasks.empty()) a[0] = sx(load32(m, tasks[rng() % tasks.size()] + 0x3C));
                    else a[0] = sx(bw);
                }
                pair(m, s.hand, s.recomp, a, rng(), s.name);
                ++ran;
            }
            std::memcpy(m.mem.main_ram(), snap.data(), snap.size());  // every repetition from the snapshot again
        }
        // Every effect packet with its own callback (the packet is the callback's argument).
        for (u32 p : pk) {
            for (u32 cb : {load32(m, p + 104), load32(m, p + 108)}) {
                char want[16];
                std::snprintf(want, sizeof want, "_%08x", cb);
                for (const Spec& s : kSpecs) {
                    const std::string nm(s.name);
                    if (nm.size() > 9 && nm.compare(nm.size() - 9, 9, want) == 0) {
                        pair(m, s.hand, s.recomp, Args{sx(p), 0, 0, 0}, rng(), s.name);
                        ++ran;
                        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
                    }
                }
            }
        }
    }
    MESSAGE("snapshots: " << ran << " pairs; " << cmd_tasks << " command task(s), " << packets << " effect packet(s) found");
}

TEST_CASE("game(battle_fx): the effect functions follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF00Du};
    int checks = 0;
    for (int it = 0; it < 60; ++it) {
        random_world(m, rng);
        const u32 rec = kRecords + 0x100u * (rng() % 0x20u);  // a record with room for +1600
        const u32 unit = kRecords + 0x3000u, unit2 = kRecords + 0x3400u;
        // 1. The busy-count starts / ends: u16 +160 of payload[0] (and payload[1]) +1 / -1.
        {
            store32(m, rec, unit);
            store32(m, rec + 4, unit2);
            const u16 b1 = static_cast<u16>(rng()), b2 = static_cast<u16>(rng());
            store16(m, unit + 160, b1);
            store16(m, unit2 + 160, b2);
            const Args a{sx(rec), 0, 0, 0};
            pair(m, PAIR(fn_sub_2B8970_002b8970), a, rng(), "rule 2B8970");
            CHECK(load16(m, unit + 160) == static_cast<u16>(b1 + 1));
            pair(m, PAIR(fn_sub_2BD060_002bd060), a, rng(), "rule 2BD060");
            pair(m, PAIR(fn_sub_2BD2C0_002bd2c0), a, rng(), "rule 2BD2C0");
            CHECK(load16(m, unit + 160) == static_cast<u16>(b1 + 3));
            pair(m, PAIR(fn_sub_2B8B50_002b8b50), a, rng(), "rule 2B8B50");
            pair(m, PAIR(fn_sub_2BD210_002bd210), a, rng(), "rule 2BD210");
            pair(m, PAIR(fn_sub_2BD460_002bd460), a, rng(), "rule 2BD460");
            CHECK(load16(m, unit + 160) == b1);
            pair(m, PAIR(fn_sub_2BD8B0_002bd8b0), a, rng(), "rule 2BD8B0");
            CHECK(load16(m, unit + 160) == static_cast<u16>(b1 + 1));
            CHECK(load16(m, unit2 + 160) == static_cast<u16>(b2 + 1));
            pair(m, PAIR(fn_sub_2BDBA0_002bdba0), a, rng(), "rule 2BDBA0");
            CHECK(load16(m, unit + 160) == b1);
            CHECK(load16(m, unit2 + 160) == b2);
        }
        // 2. The BED accessors: bound flag 0x2 of +1584, durations +8 / +808, group word +12 + 788 n, file +1588.
        {
            const u16 flags = static_cast<u16>(rng());
            store16(m, rec + 1584, flags);
            CHECK(v0_of(pair(m, PAIR(fn_sub_2B9350_002b9350), Args{sx(rec), 0, 0, 0}, rng(), "rule 2B9350")) ==
                  ((flags & 2u) ? 1u : 0u));
            const u32 side = rng() % 3;
            const u64 dur = v0_of(pair(m, PAIR(fn_sub_2B9370_002b9370), Args{sx(rec), side, 0, 0}, rng(), "rule 2B9370"));
            CHECK(dur == (side == 0 ? sx(load32(m, rec + 8)) : side == 1 ? sx(load32(m, rec + 808)) : 0u));
            const u32 g = rng() % 2;
            CHECK(v0_of(pair(m, PAIR(fn_sub_2B93C0_002b93c0), Args{sx(rec), g, 0, 0}, rng(), "rule 2B93C0")) ==
                  sx(load32(m, rec + 788 * g + 12)));
            const u32 file = rng();
            pair(m, PAIR(fn_sub_2B96E0_002b96e0), Args{sx(rec), sx(file), 0, 0}, rng(), "rule 2B96E0");
            CHECK(load32(m, rec + 1588) == file);
        }
        // 3. The slot accessors: alpha word +20, effect id +16 with the dirty bit +0.0, the 48-slot hide.
        {
            const u32 alpha = rng();
            pair(m, PAIR(fn_sub_2BBF80_002bbf80), Args{sx(rec), sx(alpha), 0, 0}, rng(), "rule 2BBF80");
            CHECK(load32(m, rec + 20) == ((alpha & 0xFF000000u) | 0xFFFFFFu));
            m.at(rec)[0] = 0;
            const u16 id = static_cast<u16>(rng() % 8);
            store16(m, rec + 16, static_cast<u16>(rng() % 8));
            const bool change = load16(m, rec + 16) != id;
            pair(m, PAIR(fn_sub_2BBDC0_002bbdc0), Args{sx(rec), id, 0, 0}, rng(), "rule 2BBDC0");
            CHECK(load16(m, rec + 16) == id);
            CHECK((m.at(rec)[0] & 1u) == (change ? 1u : 0u));
            CHECK(v0_of(pair(m, PAIR(fn_sub_2BBDF0_002bbdf0), Args{sx(rec), 0, 0, 0}, rng(), "rule 2BBDF0")) == id);
            const u32 pool = kRecords + 0x4000u;
            for (u32 i = 0; i < 48; ++i) {
                store32(m, pool + 4 * i, kRecords + 0x4200u + 16 * i);
                store16(m, kRecords + 0x4200u + 16 * i, static_cast<u16>(rng()));
            }
            pair(m, PAIR(fn_sub_2BBBC0_002bbbc0), Args{sx(pool), 0, 0, 0}, rng(), "rule 2BBBC0");
            for (u32 i = 0; i < 48; ++i) CHECK((load16(m, kRecords + 0x4200u + 16 * i) & 0x200u) == 0u);
        }
        // 4. The vec4 zero of position callback 12, the matrix copy to 0x957100, the instance flags.
        {
            const u32 out = kRecords + 0x5000u;
            pair(m, PAIR(fn_sub_2BA0D0_002ba0d0), Args{0, 0, 0, sx(out)}, rng(), "rule 2BA0D0");
            for (u32 k = 0; k < 4; ++k) CHECK(load32(m, out + 4 * k) == 0u);
            pair(m, PAIR(fn_sub_2B9600_002b9600), Args{sx(rec), 0, 0, 0}, rng(), "rule 2B9600");
            CHECK(std::memcmp(m.at(0x957100u), m.at(rec), 64) == 0);
            u32 want = 0;
            const u16 w4 = load16(m, rec + 4), w6 = load16(m, rec + 6);
            if (load32(m, rec + 8)) want |= 0x80;
            if (load32(m, rec + 12)) want |= 0x1;
            if (w4 & 0x400) want |= 0x2;
            if (w4 & 0x100) want |= 0x4;
            if (w4 & 0x4) want |= 0x10;
            if (w4 & 0x2) want |= 0x8;
            if (w6 & 0x2) want |= 0x20;
            if (w6 & 0x4) want |= 0x40;
            CHECK(v0_of(pair(m, PAIR(fn_sub_2B9640_002b9640), Args{sx(rec), 0, 0, 0}, rng(), "rule 2B9640")) == want);
        }
        // 5. The command words of the Escape / Wait lists and the skill list's init.
        {
            pair(m, PAIR(fn_sub_2BE5D0_002be5d0), Args{sx(rec), sx(unit), 0, 0}, rng(), "rule 2BE5D0");
            CHECK(load16(m, unit + 108) == 6);
            CHECK(load16(m, unit + 110) == 0);
            CHECK(v0_of(pair(m, PAIR(fn_sub_2BE5F0_002be5f0), Args{sx(rec), sx(unit), 0, 0}, rng(), "rule 2BE5F0")) == 6);
            CHECK(load16(m, unit + 108) == 7);
            pair(m, PAIR(fn_sub_2BE610_002be610), Args{sx(rec), 0, 0, 0}, rng(), "rule 2BE610");
            CHECK(load16(m, rec + 12) == 623);
        }
        // 6. The gauges' reset: +0 / +20 = -1.0, +4 / +24 = 1.0, frames +16 / +36 = -1.
        {
            pair(m, PAIR(fn_sub_2BCDE0_002bcde0), Args{0, sx(rec), 0, 0}, rng(), "rule 2BCDE0");
            CHECK(load32(m, rec + 0) == 0xBF800000u);
            CHECK(load32(m, rec + 4) == 0x3F800000u);
            CHECK(load16(m, rec + 16) == 0xFFFFu);
            CHECK(load32(m, rec + 20) == 0xBF800000u);
            CHECK(load32(m, rec + 24) == 0x3F800000u);
            CHECK(load16(m, rec + 36) == 0xFFFFu);
        }
        // 7. The list input: decide (0x40) -> 2, cancel (0x20) -> 1, nothing -> 0 (the pad words 0x7E094E / 0x7E0958 /
        //    0x7E0952 / 0x7E095A), on a list whose cursor is inside the count.
        {
            const u32 list = kRecords + 0x5100u;
            store16(m, list + 4, 0);
            store16(m, list + 6, 1);
            store16(m, list + 10, 4);
            store16(m, list + 12, 6);
            for (u32 pad : {0x7E094Eu, 0x7E0958u, 0x7E0952u, 0x7E095Au}) store16(m, pad, 0);
            const unsigned k = rng() % 3;
            if (k == 1) store16(m, 0x7E094Eu, 0x40);
            if (k == 2) store16(m, 0x7E0958u, 0x20);
            const u64 r = v0_of(pair(m, PAIR(fn_sub_2BDFB0_002bdfb0), Args{sx(list), 0, 0, 0}, rng(), "rule 2BDFB0"));
            CHECK(r == (k == 1 ? 2u : k == 2 ? 1u : 0u));
        }
        // 8. The slot pool: reset (colour -1, step 20, frame 0, flags 0x200), alloc = the first clear bit of the in-use
        //    mask +192 (0 when full), free = clear the slot's bit (1) or 0 when the slot is not in the pool.
        {
            const u32 pool = kRecords + 0x5400u, slots = kRecords + 0x5600u;
            for (u32 i = 0; i < 48; ++i) {
                const u32 s = slots + 32 * i;
                store32(m, pool + 4 * i, s);
                for (u32 o : {16u, 20u, 24u}) store32(m, s + o, 0);
            }
            const u32 one = slots + 32 * (rng() % 48);
            pair(m, PAIR(fn_sub_2BB580_002bb580), Args{sx(one), 0, 0, 0}, rng(), "rule 2BB580");
            CHECK(load32(m, one + 4) == 0xFFFFFFFFu);
            CHECK(m.at(one)[8] == 20);
            CHECK(load32(m, one + 12) == 0u);
            CHECK(load16(m, one) == 512);
            // The mask is one 32-bit word for 48 slots: the bit of slot i is 1 << i shifted as a 32-bit value, 0 from slot
            // 32 on -- so with slots 0..31 in use, slot 32 is handed out (again and again) and the mask stays as it was.
            const u32 mask = chance(rng, 15) ? 0xFFFFFFFFu : rng() & rng();
            store32(m, pool + 192, mask);
            u32 first = 0;
            while (first < 32 && (mask >> first & 1u)) ++first;
            const u64 got = v0_of(pair(m, PAIR(fn_sub_2BB9C0_002bb9c0), Args{sx(pool), 0, 0, 0}, rng(), "rule 2BB9C0"));
            if (first < 32) {
                CHECK(got == sx(slots + 32 * first));
                CHECK(load32(m, pool + 192) == (mask | (1u << first)));
                const u64 freed = v0_of(pair(m, PAIR(fn_sub_2BBAC0_002bbac0), Args{sx(pool), sx(slots + 32 * first), 0, 0},
                                             rng(), "rule 2BBAC0"));
                CHECK(freed == 1u);
                CHECK(load32(m, pool + 192) == mask);
            } else {
                CHECK(got == sx(slots + 32 * 32));
                CHECK(load32(m, pool + 192) == mask);
            }
            const u64 none = v0_of(pair(m, PAIR(fn_sub_2BBAC0_002bbac0), Args{sx(pool), sx(kRecords + 0x5300u), 0, 0},
                                        rng(), "rule 2BBAC0 not in pool"));
            CHECK(none == 0u);
        }
        // 9. The position solver's four modes (8 above, 9 / 10 toward the camera through VU0, others rotated): every mode
        //    runs to the end and writes a vec4 whose w is 0.
        {
            const u32 base = kRecords + 0x5900u, quat = kRecords + 0x5940u, entry = kRecords + 0x5980u, out = kRecords + 0x59C0u;
            for (u32 k = 0; k < 4; ++k) {
                const float f = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 8.0f;
                const float q = static_cast<float>(static_cast<int>(rng() % 201) - 100) / 100.0f;
                std::memcpy(m.at(base + 4 * k), &f, 4);
                std::memcpy(m.at(quat + 4 * k), &q, 4);
            }
            const u8 modes[] = {8, 9, 10, static_cast<u8>(rng() % 8)};
            const u8 mode = modes[rng() % 4];
            m.at(entry)[1] = static_cast<u8>(rng() % 5);
            m.at(entry)[2] = mode;
            store16(m, entry + 4, static_cast<u16>(chance(rng, 50) ? 0 : rng() % 200));
            store32(m, out + 12, 0xDEADBEEFu);
            const Run r = pair(m, PAIR(fn_sub_2B96F0_002b96f0), Args{sx(base), sx(quat), sx(entry), sx(out)}, rng(), "rule 2B96F0");
            INFO("mode " << unsigned(mode));
            CHECK(!r.stopped);
            CHECK(load32(m, out + 12) == 0u);
        }
        checks += 72;
    }
    // 8. The affinity icons and colours (every single bit, 0 and a two-bit value).
    {
        random_world(m, rng);
        const std::map<u32, int> icon = {{1u, 39},     {2u, 40},     {4u, 41},   {8u, 42},    {0x10u, 43},  {0x20u, 36},
                                         {0x40u, 37},  {0x80u, 38},  {0x100u, 45}, {0x200u, 44}, {0x400u, -1}, {0x80000u, -1},
                                         {0x100000u, -1}, {0u, -1}, {3u, -1}};
        for (const auto& [bit, want] : icon) {
            INFO("affinity " << bit);
            CHECK(v0_of(pair(m, PAIR(fn_sub_2BBFA0_002bbfa0), Args{sx(bit), 0, 0, 0}, rng(), "rule 2BBFA0")) == sx(static_cast<u32>(want)));
        }
        const std::map<u32, std::array<u8, 3>> colour = {{1u, {255, 148, 188}}, {2u, {178, 158, 255}}, {4u, {205, 178, 205}},
                                                         {8u, {168, 168, 255}}, {0x10u, {255, 178, 158}}, {0x20u, {138, 198, 255}},
                                                         {0x40u, {245, 218, 128}}, {0x80u, {255, 108, 228}}, {0x200u, {255, 58, 68}},
                                                         {0x400u, {255, 64, 18}}};
        const u32 out = kRecords + 0x5200u;
        for (const auto& [bit, rgb] : colour) {
            INFO("affinity " << bit);
            pair(m, PAIR(fn_sub_2BC0E0_002bc0e0), Args{sx(bit), sx(out), 0, 0}, rng(), "rule 2BC0E0");
            CHECK(m.at(out)[0] == rgb[0]);
            CHECK(m.at(out)[1] == rgb[1]);
            CHECK(m.at(out)[2] == rgb[2]);
            CHECK(m.at(out)[3] == 255);
        }
        pair(m, PAIR(fn_sub_2BC0E0_002bc0e0), Args{sx(0x100u), sx(out), 0, 0}, rng(), "rule 2BC0E0 default");
        CHECK(std::memcmp(m.at(out), m.at(gp(-25472)), 4) == 0);
        checks += 40;
    }
    MESSAGE("rules: " << checks << " checks");
}

#else
TEST_CASE("game(battle_fx): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
