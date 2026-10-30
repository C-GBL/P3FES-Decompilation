// Phase 5 pair tests for slice battle_task (game/src/battle/battle_task.cpp): every hand-written battle task / state
// function and the recompiled body it replaces run on identical guest machines -- a random battle world (gBtl, the
// btlAction and btlUnit objects, DatUnits, the four packet queues, the turn-order lists, the btlMain state record, the
// pad words) and a random register file -- and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * guest memory: the battle world, the gp-relative globals, the pad words, the stack around $sp (live frame,
//     the frames and spills of the run below it) and the arena.
// The state functions call deep recompiled trees (sound, panel, scene, effects); the test build emits only the small
// ones (tests/game/CMakeLists.txt), so most paths end in a compared stop at the first big callee; the state tables
// sBtlActionTbl / 0x693760 are the real ones, so btlActionSetState's `jalr` reaches the hand-written init states of
// this slice. Documented rules (21_battle.md sections 1.2-1.4 and battle_task.h) are checked on the host
// independently of both bodies.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/battle_task.h"

#include <array>
#include <cstring>
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
P3FES_DECL_PAIR(fn_btlStart_0027d1d0)
P3FES_DECL_PAIR(fn_sub_27D560_0027d560)
P3FES_DECL_PAIR(fn_sub_29B090_0029b090)
P3FES_DECL_PAIR(fn_btlUpdateTask_0027cc30)
P3FES_DECL_PAIR(fn_btlDestroyTask_0027cdf0)
P3FES_DECL_PAIR(fn_sub_27CE10_0027ce10)
P3FES_DECL_PAIR(fn_sub_27E410_0027e410)
P3FES_DECL_PAIR(fn_sub_27E470_0027e470)
P3FES_DECL_PAIR(fn_sub_27E4D0_0027e4d0)
P3FES_DECL_PAIR(fn_sub_28A990_0028a990)
P3FES_DECL_PAIR(fn_sub_28A9A0_0028a9a0)
P3FES_DECL_PAIR(fn_sub_28A9B0_0028a9b0)
P3FES_DECL_PAIR(fn_sub_28A9C0_0028a9c0)
P3FES_DECL_PAIR(fn_sub_28B9C0_0028b9c0)
P3FES_DECL_PAIR(fn_sub_28BCA0_0028bca0)
P3FES_DECL_PAIR(fn_sub_28C9F0_0028c9f0)
P3FES_DECL_PAIR(fn_sub_28D070_0028d070)
P3FES_DECL_PAIR(fn_sub_28DBE0_0028dbe0)
P3FES_DECL_PAIR(fn_sub_28E740_0028e740)
P3FES_DECL_PAIR(fn_sub_28EA90_0028ea90)
P3FES_DECL_PAIR(fn_sub_28EB40_0028eb40)
P3FES_DECL_PAIR(fn_sub_290BD0_00290bd0)
P3FES_DECL_PAIR(fn_sub_294D10_00294d10)
P3FES_DECL_PAIR(fn_sub_295150_00295150)
P3FES_DECL_PAIR(fn_sub_295B20_00295b20)
P3FES_DECL_PAIR(fn_sub_295B90_00295b90)
P3FES_DECL_PAIR(fn_sub_295BA0_00295ba0)
P3FES_DECL_PAIR(fn_sub_295BF0_00295bf0)
P3FES_DECL_PAIR(fn_sub_295F00_00295f00)
P3FES_DECL_PAIR(fn_sub_296310_00296310)
P3FES_DECL_PAIR(fn_sub_296880_00296880)
P3FES_DECL_PAIR(fn_sub_2976D0_002976d0)
P3FES_DECL_PAIR(fn_sub_297750_00297750)
P3FES_DECL_PAIR(fn_sub_2990F0_002990f0)
P3FES_DECL_PAIR(fn_sub_299100_00299100)
P3FES_DECL_PAIR(fn_sub_299170_00299170)
P3FES_DECL_PAIR(fn_sub_299760_00299760)
P3FES_DECL_PAIR(fn_sub_299AA0_00299aa0)
P3FES_DECL_PAIR(fn_sub_299D20_00299d20)
P3FES_DECL_PAIR(fn_sub_299D30_00299d30)
P3FES_DECL_PAIR(fn_btlActionSetStateWithDelay_00299db0)
P3FES_DECL_PAIR(fn_sub_29AD20_0029ad20)
P3FES_DECL_PAIR(fn_sub_29AD50_0029ad50)
P3FES_DECL_PAIR(fn_sub_29AD60_0029ad60)
P3FES_DECL_PAIR(fn_sub_29ADA0_0029ada0)
P3FES_DECL_PAIR(fn_sub_29ADF0_0029adf0)
P3FES_DECL_PAIR(fn_sub_29B040_0029b040)
P3FES_DECL_PAIR(fn_sub_29B070_0029b070)
P3FES_DECL_PAIR(fn_sub_29B0C0_0029b0c0)
P3FES_DECL_PAIR(fn_btlMainInitStateNon_0029b0e0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateNon_0029b0f0)
P3FES_DECL_PAIR(fn_btlMainInitStateInit_0029b100)
P3FES_DECL_PAIR(fn_btlMainUpdateStateInit_0029b160)
P3FES_DECL_PAIR(fn_btlMainInitStateSceneSet_0029b170)
P3FES_DECL_PAIR(fn_btlMainUpdateStateSceneSet_0029b190)
P3FES_DECL_PAIR(fn_btlMainInitStateStart_0029c250)
P3FES_DECL_PAIR(fn_btlMainUpdateStateStart_0029c290)
P3FES_DECL_PAIR(fn_btlMainInitStateAction_0029c330)
P3FES_DECL_PAIR(fn_btlMainUpdateStateAction_0029c340)
P3FES_DECL_PAIR(fn_btlMainInitStateRevivalMes_0029c5d0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateRevivalMes_0029c680)
P3FES_DECL_PAIR(fn_btlMainInitStateEnemyDead_0029cde0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateEnemyDead_0029ce20)
P3FES_DECL_PAIR(fn_btlMainUpdateStateWin_0029d0d0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateCondition_0029d6e0)
P3FES_DECL_PAIR(fn_btlMainInitStateLose_0029d720)
P3FES_DECL_PAIR(fn_btlMainUpdateStateLose_0029d730)
P3FES_DECL_PAIR(fn_btlMainInitStateFadeOut_0029d760)
P3FES_DECL_PAIR(fn_btlMainUpdateStateFadeOut_0029d800)
P3FES_DECL_PAIR(fn_btlMainUpdateStateEnd_0029db60)
P3FES_DECL_PAIR(fn_btlMainInitStateResult_0029dbf0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateResult_0029dc20)
P3FES_DECL_PAIR(fn_btlMainInitStateExit_0029dcf0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateExit_0029dd50)
P3FES_DECL_PAIR(fn_btlMainInitStateTest_0029ddb0)
P3FES_DECL_PAIR(fn_btlMainUpdateStateTest_0029ddc0)
P3FES_DECL_PAIR(fn_btlMainInitStateMc_0029de00)
P3FES_DECL_PAIR(fn_btlMainUpdateStateMc_0029de10)
P3FES_DECL_PAIR(fn_btlMainSetStateNon_0029df40)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace bt = p3fes::game::btl_task;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }
#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the battle world (free RAM above the arena) ------------------------------------------------------------------
constexpr u32 kGBtlSlot = 0x7CE3ECu;  // *(gp - 18692)
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kG = kWorld;                     // gBtl (fields up to +3372)
constexpr u32 kActions = kWorld + 0x1000u;     // 6 x 0x500 (1,200-byte btlActions)
constexpr u32 kUnits = kWorld + 0x3000u;       // 5 x 0xB00 btlUnits (+2604 / +2608)
constexpr u32 kDats = kWorld + 0x6800u;        // DatUnits, 64 bytes apart
constexpr u32 kPackets = kWorld + 0x7000u;     // 16 x 0x100 packets
constexpr u32 kHandles = kWorld + 0x8000u;     // fake task / result handles
constexpr u32 kNumActions = 6, kNumUnits = 5, kNumPackets = 16;
constexpr u32 kPadBase = 0x7E0940u;            // the pad words read by btlMainUpdateStateWin (0x7E094C..0x7E0958)

struct Window {
    u32 va;
    u32 len;
};
const Window kWindows[] = {
    {kWorld, kWorldSize},              // the battle world
    // low RAM: callees that follow a null global pointer write there (since sweep5, sub_299AA0's sub_1FDD40 tree reaches
    // 0x5A40: unrestored, the recompiled run read what the hand run had written)
    {0x0u, 0x8000u},
    // newlib's state: the reentrancy record 0x782C40 (__sinit sets up its std streams on the first sprintf, reached
    // since sweep5a replaced sprintf / vsprintf: unrestored, the recompiled run met the streams the hand run had set
    // up), _impure_ptr 0x782F30 and dlmalloc's bins / top / trim words 0x782F40..0x783353
    {0x782C00u, 0x800u},
    {0x7C0000u, 0x80000u},             // .data / .bss: gp-relative words, the pad words, gGlobalWork, the flags
    {0x950000u, 0x10000u},             // the datScript context and the other high globals
    {kSp - 0x1000u, 0x1100u},          // the stack: frames and spills of the run, and the caller's live frame
    {kArena, kArenaSize},
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
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
// A 32-bit value as a register argument, sometimes with garbage in the upper half (the bodies take whole registers).
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 25) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }

struct World {
    std::array<u32, kNumActions> actions{};
    std::array<u32, kNumUnits> units{};
};

// Targets for the EVENT state's callback (+1184): emitted functions with defined behaviour. sub_1F1C50 is a non-leaf
// that spills the $ra it gets below the $sp it gets (the frame / link discipline of the `jalr`).
constexpr u32 kEventTargets[] = {0x281270u, 0x2D5550u, 0x1F1C50u, 0x17B180u, 0x2FF310u, 0x2FF330u};

World random_world(Machine& m, std::mt19937& rng) {
    World w;
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, rng());
    for (u32 i = 0; i < kNumActions; ++i) w.actions[i] = kActions + 0x500u * i;
    for (u32 i = 0; i < kNumUnits; ++i) w.units[i] = kUnits + 0xB00u * i;
    store32(m, kGBtlSlot, kG);
    const auto pick = [&](std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); };

    // gBtl
    u32 flags = rng();
    for (u32 bit : {0x1u, 0x80u, 0x400u, 0x800u, 0x80000u, 0x400000u, 0x800000u, 0x8000000u})
        flags = chance(rng, 50) ? (flags | bit) : (flags & ~bit);
    store32(m, kG + bt::kFlags, flags);
    store16(m, kG + bt::kOutcome, static_cast<u16>(pick({0u, 1u, 1u, 2u, 2u, 3u, 3u, rng() & 0xFFFFu})));
    store32(m, kG + bt::kCurrentAction, w.actions[rng() % kNumActions]);
    store32(m, kG + bt::kActionList, chance(rng, 50) ? 0u : w.actions[rng() % kNumActions]);
    // the btlUnit list (0..5 units) and their DatUnits
    const u32 nunits = rng() % (kNumUnits + 1);
    store32(m, kG + bt::kUnitList, nunits ? w.units[0] : 0u);
    for (u32 i = 0; i < kNumUnits; ++i) {
        const u32 u = w.units[i];
        u32 uf = rng();
        for (u32 bit : {0x1u, 0x8u, 0x10u}) uf = chance(rng, 40) ? (uf | bit) : (uf & ~bit);
        store32(m, u + bt::kUnitFlags, uf);
        m.at(u + bt::kUnitSide)[0] = static_cast<u8>(chance(rng, 80) ? rng() % 2 : rng());
        store16(m, u + 200, static_cast<u16>(chance(rng, 50) ? (rng() & 0xFFFEu) : rng()));  // bit 0: still moving
        const u32 dat = kDats + 64u * i;
        store32(m, u + bt::kUnitDat, chance(rng, 10) ? 0u : dat);
        store32(m, u + bt::kUnitNext, i + 1 < nunits ? w.units[i + 1] : 0u);
        u32 status = rng();
        status = chance(rng, 40) ? (status | 0x80000u) : (status & ~0x80000u);
        store32(m, dat + 12, status);
        store16(m, dat + 8, static_cast<u16>(chance(rng, 20) ? 0u : rng() % 999u));
    }
    // the packet queues: 0..4 packets each (30 %: all empty), +124 next, +128 previous, tails at 368 + 8q
    const bool empty = chance(rng, 30);
    u32 next_packet = 0;
    for (u32 q = 0; q < 4; ++q) {
        const u32 n = empty ? 0u : (chance(rng, 50) ? 0u : rng() % 5);
        u32 prev = 0;
        store32(m, kG + bt::kPacketQueues + 8 * q, 0);
        for (u32 k = 0; k < n && next_packet < kNumPackets; ++k) {
            const u32 p = kPackets + 0x100u * next_packet++;
            if (prev == 0) store32(m, kG + bt::kPacketQueues + 8 * q, p);
            else store32(m, prev + 124, p);
            store32(m, p + 124, 0);
            store32(m, p + 128, prev);
            store32(m, p + 64, pick({1286u, 2048u, 1286u, 2048u, rng() & 0xFFFFu, 0x80000506u, rng()}));
            prev = p;
        }
        store32(m, kG + bt::kPacketQueues - 4 + 8 * q, prev);
    }
    // the order lists
    for (u32 i = 0; i < 12; ++i) {
        store32(m, kG + bt::kOrderList + 4 * i, chance(rng, 30) ? 0u : w.actions[rng() % kNumActions]);
        store32(m, kG + bt::kOrderListNext + 4 * i, chance(rng, 40) ? 0u : w.actions[rng() % kNumActions]);
    }
    // the btlMain state record (the state functions' $a0 = gBtl + 692)
    store32(m, kG + bt::kMainState, rng() % 20);
    store32(m, kG + bt::kMainPending, chance(rng, 50) ? 0u : rng() % 20);
    store32(m, kG + bt::kMainFrames, chance(rng, 90) ? rng() % 80 : rng());
    store16(m, kG + bt::kMainState + 12, static_cast<u16>(rng() % 30));
    store16(m, kG + bt::kMainState + 14, static_cast<u16>(rng() % 30));
    store16(m, kG + bt::kMainState + 16, static_cast<u16>(rng() % 60));
    store32(m, kG + bt::kMainState + 20, chance(rng, 50) ? 0u : (chance(rng, 80) ? 1u : rng()));
    store16(m, kG + bt::kRounds, static_cast<u16>(chance(rng, 30) ? 0u : (chance(rng, 90) ? 1 + rng() % 20 : rng())));
    m.at(kG + bt::kTestBattle)[0] = static_cast<u8>(pick({0u, 1u, 1u, rng() & 0xFFu}));
    store32(m, kG + bt::kRootChildTask, chance(rng, 50) ? 0u : kHandles);
    store32(m, kG + bt::kResultTask, chance(rng, 20) ? 0u : kHandles + 0x100u);
    store32(m, kG + bt::kEndTask, chance(rng, 50) ? 0u : kHandles + 0x200u);
    // the actions
    for (u32 i = 0; i < kNumActions; ++i) {
        const u32 a = w.actions[i];
        store64(m, a + bt::kActUid, (static_cast<u64>(rng()) << 32) | rng());
        store16(m, a + bt::kActState, static_cast<u16>(rng() % 36));
        // never START HOME (3) as the state to go back to: its init (sub_28B800, hand-written since sweep5f) sets the
        // return state when the unit is home already, so 3 -> 3 recursed until the host stack overflowed (on the
        // console too: the guest stack); before sweep5f the pair stopped at the not-emitted sub_28B800
        u16 ret = static_cast<u16>(chance(rng, 90) ? rng() % 36 : rng() % 36);
        if (ret == 3) ret = static_cast<u16>(4 + rng() % 32);
        store16(m, a + bt::kActReturn, ret);
        store32(m, a + bt::kActUnit, chance(rng, 95) ? w.units[rng() % kNumUnits] : 0u);
        store16(m, a + bt::kActMoveKind, static_cast<u16>(pick({0u, 1u, 2u, 3u, 9u, rng() & 0xFFFFu})));
        store16(m, a + bt::kActCommand, static_cast<u16>(pick({0u, 0u, 571u, 572u, rng() & 0xFFFFu})));
        store32(m, a + bt::kActHome, pick({0u, 1u, 1u, rng()}));
        store16(m, a + bt::kActEventReturn, static_cast<u16>(rng() % 36));
        store32(m, a + bt::kActEventFn, kEventTargets[rng() % std::size(kEventTargets)]);
    }
    // the pad words: mostly released
    for (u32 off = 0; off < 0x40; off += 2) store16(m, kPadBase + off, static_cast<u16>(chance(rng, 85) ? 0u : rng()));
    return w;
}

// --- the register file at a check point / the return / a stop ----------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0;
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
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    return s;
}
// The first difference (empty when equal): "gpr N", "hi", "lo", "sa/fcr31", "fpr", "cycles".
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa || a.fcr31 != b.fcr31) return "sa/fcr31";
    if (a.fpr != b.fpr) return "fpr";
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds the hand
// version's frames, whose destructors run the epilogue).
class TaskHooks final : public RtHooks {
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
    void check_events(EEContext& ctx) override { snaps.push_back(snap(ctx)); }
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
    std::vector<std::vector<u8>> mem;
};

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed) {
    TaskHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
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
    for (const Window& w : kWindows) r.mem.push_back(m.bytes(w.va, w.len));
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;  // missing function -> count
};
std::map<std::string, Stats> g_stats;

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled run.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    std::vector<std::vector<u8>> before;
    for (const Window& w : kWindows) before.push_back(m.bytes(w.va, w.len));
    Run h = run_one(m, hand, args, seed);
    for (std::size_t i = 0; i < std::size(kWindows); ++i) std::memcpy(m.at(kWindows[i].va), before[i].data(), kWindows[i].len);
    Run r = run_one(m, recomp, args, seed);
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
    }
    const std::string name(what);
    INFO(name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed);
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
        const std::string where = r.stopped ? "at the stop: " : "at the return: ";
        INFO(where << d);
        CHECK(d.empty());
    }
    for (std::size_t i = 0; i < std::size(kWindows); ++i) {
        const auto& a = h.mem[i];
        const auto& b = r.mem[i];
        const std::size_t first = first_difference(a.data(), b.data(), a.size());
        INFO("memory window " << hex64(kWindows[i].va) << ": first differing byte at " << hex64(kWindows[i].va + first));
        CHECK(first == a.size());
    }
    return r;
}

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

enum class Arg { none, action, state, index, type, delay, setup };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};

#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_btlStart_0027d1d0, setup),
    SPEC(fn_sub_27D560_0027d560, none),
    SPEC(fn_sub_29B090_0029b090, none),
    SPEC(fn_btlUpdateTask_0027cc30, none),
    SPEC(fn_btlDestroyTask_0027cdf0, none),
    SPEC(fn_sub_27CE10_0027ce10, none),
    SPEC(fn_sub_27E410_0027e410, none),
    SPEC(fn_sub_27E470_0027e470, type),
    SPEC(fn_sub_27E4D0_0027e4d0, none),
    SPEC(fn_sub_28A990_0028a990, action),
    SPEC(fn_sub_28A9A0_0028a9a0, action),
    SPEC(fn_sub_28A9B0_0028a9b0, action),
    SPEC(fn_sub_28A9C0_0028a9c0, action),
    SPEC(fn_sub_28B9C0_0028b9c0, action),
    SPEC(fn_sub_28BCA0_0028bca0, action),
    SPEC(fn_sub_28C9F0_0028c9f0, action),
    SPEC(fn_sub_28D070_0028d070, action),
    SPEC(fn_sub_28DBE0_0028dbe0, action),
    SPEC(fn_sub_28E740_0028e740, action),
    SPEC(fn_sub_28EA90_0028ea90, action),
    SPEC(fn_sub_28EB40_0028eb40, action),
    SPEC(fn_sub_290BD0_00290bd0, action),
    SPEC(fn_sub_294D10_00294d10, action),
    SPEC(fn_sub_295150_00295150, action),
    SPEC(fn_sub_295B20_00295b20, action),
    SPEC(fn_sub_295B90_00295b90, action),
    SPEC(fn_sub_295BA0_00295ba0, action),
    SPEC(fn_sub_295BF0_00295bf0, action),
    SPEC(fn_sub_295F00_00295f00, action),
    SPEC(fn_sub_296310_00296310, action),
    SPEC(fn_sub_296880_00296880, action),
    SPEC(fn_sub_2976D0_002976d0, action),
    SPEC(fn_sub_297750_00297750, action),
    SPEC(fn_sub_2990F0_002990f0, action),
    SPEC(fn_sub_299100_00299100, action),
    SPEC(fn_sub_299170_00299170, action),
    SPEC(fn_sub_299760_00299760, action),
    SPEC(fn_sub_299AA0_00299aa0, action),
    SPEC(fn_sub_299D20_00299d20, action),
    SPEC(fn_sub_299D30_00299d30, action),
    SPEC(fn_btlActionSetStateWithDelay_00299db0, delay),
    SPEC(fn_sub_29AD20_0029ad20, none),
    SPEC(fn_sub_29AD50_0029ad50, none),
    SPEC(fn_sub_29AD60_0029ad60, index),
    SPEC(fn_sub_29ADA0_0029ada0, index),
    SPEC(fn_sub_29ADF0_0029adf0, action),
    SPEC(fn_sub_29B040_0029b040, none),
    SPEC(fn_sub_29B070_0029b070, none),
    SPEC(fn_sub_29B0C0_0029b0c0, action),
    SPEC(fn_btlMainInitStateNon_0029b0e0, state),
    SPEC(fn_btlMainUpdateStateNon_0029b0f0, state),
    SPEC(fn_btlMainInitStateInit_0029b100, state),
    SPEC(fn_btlMainUpdateStateInit_0029b160, state),
    SPEC(fn_btlMainInitStateSceneSet_0029b170, state),
    SPEC(fn_btlMainUpdateStateSceneSet_0029b190, state),
    SPEC(fn_btlMainInitStateStart_0029c250, state),
    SPEC(fn_btlMainUpdateStateStart_0029c290, state),
    SPEC(fn_btlMainInitStateAction_0029c330, state),
    SPEC(fn_btlMainUpdateStateAction_0029c340, state),
    SPEC(fn_btlMainInitStateRevivalMes_0029c5d0, state),
    SPEC(fn_btlMainUpdateStateRevivalMes_0029c680, state),
    SPEC(fn_btlMainInitStateEnemyDead_0029cde0, state),
    SPEC(fn_btlMainUpdateStateEnemyDead_0029ce20, state),
    SPEC(fn_btlMainUpdateStateWin_0029d0d0, state),
    SPEC(fn_btlMainUpdateStateCondition_0029d6e0, state),
    SPEC(fn_btlMainInitStateLose_0029d720, state),
    SPEC(fn_btlMainUpdateStateLose_0029d730, state),
    SPEC(fn_btlMainInitStateFadeOut_0029d760, state),
    SPEC(fn_btlMainUpdateStateFadeOut_0029d800, state),
    SPEC(fn_btlMainUpdateStateEnd_0029db60, state),
    SPEC(fn_btlMainInitStateResult_0029dbf0, state),
    SPEC(fn_btlMainUpdateStateResult_0029dc20, state),
    SPEC(fn_btlMainInitStateExit_0029dcf0, state),
    SPEC(fn_btlMainUpdateStateExit_0029dd50, state),
    SPEC(fn_btlMainInitStateTest_0029ddb0, state),
    SPEC(fn_btlMainUpdateStateTest_0029ddc0, state),
    SPEC(fn_btlMainInitStateMc_0029de00, state),
    SPEC(fn_btlMainUpdateStateMc_0029de10, state),
    SPEC(fn_btlMainSetStateNon_0029df40, state),
};
#undef SPEC

Args args_for(Arg kind, const World& w, std::mt19937& rng) {
    switch (kind) {
    case Arg::none:
        return Args{rng(), rng(), rng(), rng()};
    case Arg::action:
        return Args{wide(rng, w.actions[rng() % kNumActions]), rng(), rng(), rng()};
    case Arg::state:
        return Args{wide(rng, kG + bt::kMainState), rng(), rng(), rng()};
    case Arg::index:
        return Args{wide(rng, chance(rng, 80) ? rng() % 16 : rng()), rng(), rng(), rng()};
    case Arg::type: {
        const u32 t = chance(rng, 70) ? (chance(rng, 50) ? 1286u : 2048u) : rng();
        return Args{wide(rng, t), rng(), rng(), rng()};
    }
    case Arg::setup:  // a 52-byte setup block in the world, or none (TEST / MC)
        return Args{chance(rng, 30) ? (chance(rng, 50) ? 0u : static_cast<u64>(rng()) << 32) : wide(rng, kHandles + 0x400u), rng(), rng(), rng()};
    case Arg::delay: {
        const u32 s = chance(rng, 85) ? rng() % 36 : (rng() % 36) | (rng() << 16);
        const u32 d = chance(rng, 50) ? (chance(rng, 50) ? 0u : (rng() & 0xFFFF0000u)) : rng();
        return Args{wide(rng, w.actions[rng() % kNumActions]), wide(rng, s), wide(rng, d), rng()};
    }
    }
    return {};
}

// --- host restatements of the documented rules ------------------------------------------------------------------
u32 host_packet_count(const Machine& m, bool by_type, u32 type) {
    u32 n = 0;
    for (u32 q = 0; q < 4; ++q)
        for (u32 p = load32(m, kG + bt::kPacketQueues + 8 * q); p != 0; p = load32(m, p + 124))
            if (!by_type || (static_cast<s32>(load32(m, p + 64)) >= 0 && load32(m, p + 64) == (type & 0xFFFFu))) ++n;
    return n;
}

}  // namespace

// printf (0x5225A8) is hand-written since finalB (game/src/fx/finalB.cpp): its forwarder runs the body -- vfprintf into
// the stdout FILE, which waits on the IOP without end -- where these pairs ended at it as at a function this build does
// not emit (an endless walk grew `snaps` until the host ran out of memory). The stop keeps the stop: both runs end at
// the call and are compared there (StandIns::install_stop). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas) si.install_stop(va, "stopped at, as when it was not emitted");
        scope = std::make_unique<StandInsScope>(si);
    }
};

TEST_CASE("game(battle_task): every replaced function equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0xB7A5u};
    g_stats.clear();
    constexpr int kWorlds = 400;
    for (int it = 0; it < kWorlds; ++it) {
        const World w = random_world(m, rng);
        for (const Spec& s : kSpecs) {
            const Args a = args_for(s.arg, w, rng);
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
    MESSAGE("battle_task: " << pairs << " pairs over " << std::size(kSpecs) << " functions, " << stops
                            << " ended at a compared missing-function stop; " << complete
                            << " functions also returned normally; always at a stop (a big callee first):" << always_stopped);
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_task): the packet counters, the order readers and the waits follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x51A7u};
    int moved = 0, pending = 0, lose_checked = 0, enemy_dead = 0;
    for (int it = 0; it < 1000; ++it) {
        const World w = random_world(m, rng);
        // sub_27E410 / sub_27E470: queued packets along +124 (21_battle.md 1.2: the states wait for empty queues).
        const u32 all = host_packet_count(m, false, 0);
        CHECK(v0_of(pair(m, PAIR(fn_sub_27E410_0027e410), Args{}, rng(), "count all")) == all);
        const u32 type = chance(rng, 50) ? 1286u : 2048u;
        const u32 typed = host_packet_count(m, true, type);
        CHECK(v0_of(pair(m, PAIR(fn_sub_27E470_0027e470), Args{wide(rng, type), 0, 0, 0}, rng(), "count type")) == typed);
        // the order list readers
        const u32 i = rng() % 16;
        const u32 slot = i < 12 ? load32(m, kG + bt::kOrderList + 4 * i) : 0u;
        CHECK(v0_of(pair(m, PAIR(fn_sub_29AD60_0029ad60), Args{wide(rng, i), 0, 0, 0}, rng(), "order slot")) == sx(slot));
        const bool in_world = slot == 0 || (slot >= kWorld && slot < kWorld + kWorldSize);  // (random words: no host check)
        const u32 unit = slot != 0 && in_world ? load32(m, slot + bt::kActUnit) : 0u;
        const u64 got_unit = v0_of(pair(m, PAIR(fn_sub_29ADA0_0029ada0), Args{sx(i), 0, 0, 0}, rng(), "order unit"));
        if (in_world) CHECK(got_unit == sx(unit));
        const u32 first = load32(m, kG + bt::kOrderListNext) != 0 ? load32(m, kG + bt::kOrderListNext) : load32(m, kG + bt::kOrderList);
        CHECK(v0_of(pair(m, PAIR(fn_sub_29AD20_0029ad20), Args{}, rng(), "order first")) == sx(first));
        const u32 a = w.actions[rng() % kNumActions];
        bool in_next = false;
        for (u32 k = 0; k < 12; ++k) in_next = in_next || load32(m, kG + bt::kOrderListNext + 4 * k) == a;
        CHECK(v0_of(pair(m, PAIR(fn_sub_29ADF0_0029adf0), Args{sx(a), 0, 0, 0}, rng(), "order contains")) == (in_next ? 1u : 0u));
        // btlActionSetStateWithDelay with a delay only records the pending state.
        {
            const u16 old = load16(m, a + bt::kActState);
            const u32 s = rng() % 36, d = 1 + rng() % 0xFFFE;
            pair(m, PAIR(fn_btlActionSetStateWithDelay_00299db0), Args{sx(a), sx(s), sx(d), 0}, rng(), "delay");
            CHECK(load16(m, a + bt::kActState) == old);
            CHECK(load16(m, a + bt::kActNext) == s);
            CHECK(load16(m, a + bt::kActDelay) == d);
            ++pending;
        }
        // MOVE TARGET: a unit that stopped moving goes on by its move kind (9 summon, 3/2 skill, 1 attack, else NON);
        // every init state of those rows is in this slice, so the run completes.
        {
            const u32 act = w.actions[rng() % kNumActions];
            const u32 un = load32(m, act + bt::kActUnit);
            const u16 kind = load16(m, act + bt::kActMoveKind);
            const bool moving = (load16(m, un + 200) & 1u) != 0;  // sub_281270 (a null unit reads low RAM)
            const Run r = pair(m, PAIR(fn_sub_28E740_0028e740), Args{sx(act), 0, 0, 0}, rng(), "move target");
            if (!moving && !r.stopped) {
                const u16 want = kind == 9 ? 18 : (kind == 3 || kind == 2) ? 16 : kind == 1 ? 15 : 0;
                CHECK(load16(m, act + bt::kActState) == want);
                ++moved;
            }
        }
        // LOSE: FADE_OUT (14) after 31 frames in the state.
        {
            const u32 frames = load32(m, kG + bt::kMainFrames);
            const Run r = pair(m, PAIR(fn_btlMainUpdateStateLose_0029d730), Args{sx(kG + bt::kMainState), 0, 0, 0}, rng(), "lose");
            CHECK(v0_of(r) == (static_cast<s32>(frames) >= 31 ? 14u : 0u));
            ++lose_checked;
        }
        // ENEMY DEAD: once the queues are empty the 0x80000 pass flag is cleared; FADE_OUT when the battle is over.
        if (host_packet_count(m, false, 0) == 0) {
            const bool over = (load32(m, kG + bt::kFlags) & 0x80u) != 0;
            const Run r = pair(m, PAIR(fn_btlMainUpdateStateEnemyDead_0029ce20), Args{}, rng(), "enemy dead");
            CHECK(v0_of(r) == (over ? 14u : 7u));
            CHECK((load32(m, kG + bt::kFlags) & 0x80000u) == 0);
            ++enemy_dead;
        }
    }
    MESSAGE("rules: " << moved << " move-target transitions, " << pending << " pending states, " << lose_checked
                      << " lose waits, " << enemy_dead << " enemy-dead passes");
    CHECK(moved > 100);
    CHECK(enemy_dead > 100);
}

#else
TEST_CASE("game(battle_task): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
