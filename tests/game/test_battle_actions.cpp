// Phase 5 pair tests for slice battle_actions (game/src/battle/battle_actions.cpp): every hand-written battle state body
// and the recompiled body it replaces run on identical guest machines -- a random battle world (gBtl, the btlAction /
// btlUnit objects and their lists, DatUnits, the four packet queues, the turn-order lists, the btlMain state record,
// the panel / inventory words) and a random register file (GPRs in 128 bits, FPRs) -- and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * guest memory: all 32 MiB of main RAM on every pair (write_tracker.h BaseRange / PairRange: only the pages written
//     are copied and compared) -- the battle world, low RAM, the packet buffer, .data/.bss, the high globals, the stack
//     around $sp (the caller's live frame and the frames and spills of the run below it), the arena and the rest.
// The test build emits the small callee trees (tests/game/CMakeLists.txt: the packet creators, the queue insert, the
// btlUnit show / hide, the panel checks), so most paths run to the end; the RW heap hook the packet allocator calls
// through the device pointer 0x960178 is served by the emitted leaf sub_4B3710 (`jr ra; move v0, a1`), which returns
// the allocator's $a1 = 0x40000: every packet is built in the same aligned buffer kPacketBuf (the queue insert only
// appends, and these bodies never walk a queue after queueing, so the self-linked tail is harmless; the action
// creation of UNIT_CREATE would link one buffer twice into the action list, so that body runs without a hook and stops
// at the allocation). (The game's bump counter sub_17B180 gives distinct but misaligned packets.) Deeper
// callees are compared at their missing-function stop. Documented rules (battle_actions.h) are checked on the host.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/battle_actions.h"

#include <array>
#include <cstring>
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
P3FES_DECL_PAIR(fn_btlMainUpdateStateUnitLoad_0029c110)
P3FES_DECL_PAIR(fn_btlMainUpdateStateRevival_0029ccd0)
P3FES_DECL_PAIR(fn_btlMainInitStateWin_0029ce90)
P3FES_DECL_PAIR(fn_btlMainInitStateUnitLoad_0029be40)
P3FES_DECL_PAIR(fn_btlMainInitStateEnd_0029d870)
P3FES_DECL_PAIR(fn_sub_28BD10_0028bd10)
P3FES_DECL_PAIR(fn_sub_28BF80_0028bf80)
P3FES_DECL_PAIR(fn_sub_28C310_0028c310)
P3FES_DECL_PAIR(fn_sub_28C590_0028c590)
P3FES_DECL_PAIR(fn_btlMainInitStateRevival_0029c700)
P3FES_DECL_PAIR(fn_btlMainInitStateCondition_0029d1f0)
P3FES_DECL_PAIR(fn_btlMainInitStateUnitCreate_0029b280)
P3FES_DECL_PAIR(fn_btlMainUpdateStateUnitCreate_0029b760)
P3FES_DECL_PAIR(fn_btlActionUpdateStateEscape_00296890)
P3FES_DECL_PAIR(fn_btlActionUpdateStateAttack_0028eb50)
P3FES_DECL_PAIR(fn_btlActionUpdateStateSkill_00290be0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace ba = p3fes::game::btl_act;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }
#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the battle world (free RAM above the arena) ------------------------------------------------------------------
constexpr u32 kGBtlSlot = 0x7CE3ECu;           // *(gp - 18692)
constexpr u32 kHeapHook = 0x960178u;           // RwHeapMalloc device pointer (the packet allocator's jalr)
constexpr u32 kAllocStub = 0x4B3710u;          // `jr ra; move v0, a1`: returns the allocator's $a1 = 0x40000
constexpr u32 kPacketBuf = 0x40000u;           // ... so every packet is built at 0x40000
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x20000u;
constexpr u32 kG = kWorld;                     // gBtl (fields up to +3372)
constexpr u32 kActions = kWorld + 0x1000u;     // 8 x 0x500 (1,200-byte btlActions)
constexpr u32 kUnits = kWorld + 0x4000u;       // 8 x 0xB00 btlUnits (+2604 / +2608 / +2612)
constexpr u32 kDats = kWorld + 0xA000u;        // DatUnits, 64 bytes apart
constexpr u32 kPackets = kWorld + 0xB000u;     // 16 x 0x100 queued packets
constexpr u32 kHandles = kWorld + 0xC000u;     // fake task / result handles
constexpr u32 kSkillTbl = kWorld + 0x10000u;   // a SKILL.TBL stand-in: 1,024 x 44-byte records (*(gp-18680))
constexpr u32 kNumSkills = 1024;
constexpr u32 kSkillTblSlot = kGp - 18680u;
constexpr u32 kNumActions = 8, kNumUnits = 8, kNumPackets = 16;


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

World random_world(Machine& m, std::mt19937& rng) {
    World w;
    // Background words: small numbers, aligned pointers into the world, or anything (so the callees' pointer chases
    // mostly stay inside the world instead of faulting on the first unmapped address).
    for (u32 off = 0; off < kWorldSize; off += 4) {
        const u32 k = rng() % 100;
        store32(m, kWorld + off, k < 20 ? rng() % 256
                                 : k < 40 ? (rng() % 256) & ~0xFu
                                 : k < 80 ? kWorld + (rng() % kWorldSize & ~0xFu)
                                          : 0x02000000u + rng() % 0x0E000000u);  // unmapped: faults, never a stray write
    }
    for (u32 i = 0; i < kNumActions; ++i) w.actions[i] = kActions + 0x500u * i;
    for (u32 i = 0; i < kNumUnits; ++i) w.units[i] = kUnits + 0xB00u * i;
    store32(m, kGBtlSlot, kG);
    store32(m, kHeapHook, kAllocStub);
    const auto pick = [&](std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); };
    const auto some_action = [&] { return w.actions[rng() % kNumActions]; };
    store32(m, kSkillTblSlot, kSkillTbl);
    for (u32 k = 0; k < kNumSkills; ++k) {  // the target kind byte +8 (1 / 2 a whole side), its side arguments
        m.at(kSkillTbl + 44 * k + 8)[0] = static_cast<u8>(pick({0u, 1u, 2u, 3u, rng() & 0xFFu}));
        m.at(kSkillTbl + 44 * k + 9)[0] = static_cast<u8>(rng() % 4);
        m.at(kSkillTbl + 44 * k + 10)[0] = static_cast<u8>(rng() % 4);
    }
    // the pad words (gPads 0x7E0940..): mostly released
    for (u32 off = 0; off < 0x40; off += 2) store16(m, 0x7E0940u + off, static_cast<u16>(chance(rng, 70) ? 0u : rng()));

    // gBtl
    u32 flags = rng();
    for (u32 bit : {0x1u, 0x80u, 0x400u, 0x800u, 0x80000u, 0x100000u, 0x400000u, 0x800000u, 0x8000000u})
        flags = chance(rng, 50) ? (flags | bit) : (flags & ~bit);
    store32(m, kG + ba::kFlags, flags);
    store32(m, kG + ba::kFlags2, rng());
    store16(m, kG + ba::kOutcome, static_cast<u16>(pick({0u, 1u, 1u, 2u, 2u, 3u, 3u, rng() & 0xFFFFu})));
    store32(m, kG + ba::kCurrentAction, some_action());
    // the btlAction list (+332, +1192 next): a random subset in a random order
    {
        std::array<u32, kNumActions> order = w.actions;
        std::shuffle(order.begin(), order.end(), rng);
        const u32 n = chance(rng, 10) ? 0u : 1 + rng() % kNumActions;
        store32(m, kG + ba::kActionList, n ? order[0] : 0u);
        for (u32 i = 0; i < kNumActions; ++i) store32(m, order[i] + ba::kActNextInList, i + 1 < n ? order[i + 1] : 0u);
    }
    // the btlUnit sides, then the per-side lists A (+340 + 8 * side, +2608 next) and B (+336 + 8 * side, +2612 next):
    // a random subset of the side's units in a random order each
    for (u32 i = 0; i < kNumUnits; ++i)
        m.at(w.units[i] + ba::kUnitSide)[0] = static_cast<u8>(chance(rng, 95) ? (i < 4 ? 0 : 1) ^ (chance(rng, 10) ? 1 : 0) : rng());
    for (u32 side = 0; side < 2; ++side) {
        std::vector<u32> mine;
        for (u32 u : w.units)
            if (m.at(u + ba::kUnitSide)[0] == side) mine.push_back(u);
        for (u32 list = 0; list < 2; ++list) {
            const u32 head = kG + (list == 0 ? ba::kSideListA : ba::kSideListB) + 8 * side;
            const u32 next = list == 0 ? ba::kUnitNext : ba::kUnitNextB;
            std::shuffle(mine.begin(), mine.end(), rng);
            const u32 n = mine.empty() || chance(rng, 10) ? 0u : 1 + rng() % static_cast<u32>(mine.size());
            store32(m, head, n ? mine[0] : 0u);
            for (u32 i = 0; i < mine.size(); ++i) store32(m, mine[i] + next, i + 1 < n ? mine[i + 1] : 0u);
        }
    }
    for (u32 i = 0; i < kNumUnits; ++i) {
        const u32 u = w.units[i];
        u32 uf = rng();
        for (u32 bit : {0x1u, 0x8u, 0x10u}) uf = chance(rng, 40) ? (uf | bit) : (uf & ~bit);
        store32(m, u + ba::kUnitFlags, uf);
        store16(m, u + 200, static_cast<u16>(chance(rng, 50) ? (rng() & 0xFFFEu) : rng()));  // bit 0: still moving
        const u32 dat = kDats + 64u * i;
        store32(m, u + ba::kUnitDat, dat);
        u32 status = rng();
        status = chance(rng, 40) ? (status | 0x80000u) : (status & ~0x80000u);
        store16(m, dat + 0, static_cast<u16>(chance(rng, 80) ? 1 : rng() % 0x20));      // flags (bit 0: in use)
        store16(m, dat + 2, static_cast<u16>(chance(rng, 80) ? 1 + rng() % 10 : rng() % 400));  // character / enemy id
        store32(m, dat + 12, status);
        store16(m, dat + 8, static_cast<u16>(chance(rng, 20) ? 0u : rng() % 999u));
    }
    // the packet queues: 0..4 packets each (30 %: all empty), +124 next, +128 previous, tails at 368 + 8q
    const bool empty = chance(rng, 30);
    u32 next_packet = 0;
    for (u32 q = 0; q < 4; ++q) {
        const u32 n = empty ? 0u : (chance(rng, 50) ? 0u : rng() % 5);
        u32 prev = 0;
        store32(m, kG + ba::kPacketQueues + 8 * q, 0);
        for (u32 k = 0; k < n && next_packet < kNumPackets; ++k) {
            const u32 p = kPackets + 0x100u * next_packet++;
            if (prev == 0) store32(m, kG + ba::kPacketQueues + 8 * q, p);
            else store32(m, prev + 124, p);
            store32(m, p + 124, 0);
            store32(m, p + 128, prev);
            store32(m, p + 64, pick({1286u, 2048u, 1286u, 2048u, rng() & 0xFFFFu, 0x80000506u, rng()}));
            // the owner uid: sometimes the current action's
            store64(m, p + 96, chance(rng, 30) ? 0u : (static_cast<u64>(rng()) << 32) | rng());
            prev = p;
        }
        store32(m, kG + ba::kPacketQueues - 4 + 8 * q, prev);
    }
    // the order lists
    for (u32 i = 0; i < 12; ++i) {
        store32(m, kG + ba::kOrderList + 4 * i, chance(rng, 30) ? 0u : some_action());
        store32(m, kG + ba::kOrderListNext + 4 * i, chance(rng, 40) ? 0u : some_action());
    }
    store32(m, kG + ba::kOrderCount, rng() % 13);
    store16(m, kG + ba::kOrderFlags, static_cast<u16>(rng()));
    // the btlMain state record (the state functions' $a0 = gBtl + 692)
    store32(m, kG + ba::kMainState, rng() % 20);
    store32(m, kG + ba::kMainPending, chance(rng, 50) ? 0u : rng() % 20);
    store32(m, kG + ba::kMainFrames, chance(rng, 90) ? rng() % 80 : rng());
    store16(m, kG + ba::kMainState + 12, static_cast<u16>(rng() % 30));
    store32(m, kG + ba::kRootChildTask, chance(rng, 50) ? 0u : kHandles);
    store32(m, kG + ba::kResultTask, chance(rng, 20) ? 0u : kHandles + 0x100u);
    store32(m, kG + ba::kEndTask, chance(rng, 50) ? 0u : kHandles + 0x200u);
    // the actions
    for (u32 i = 0; i < kNumActions; ++i) {
        const u32 a = w.actions[i];
        store64(m, a + ba::kActUid, (static_cast<u64>(rng()) << 32) | rng());
        store16(m, a + ba::kActState, static_cast<u16>(rng() % 36));
        store16(m, a + ba::kActFlags, static_cast<u16>(rng()));
        store16(m, a + ba::kActFlags2, static_cast<u16>(rng()));
        store32(m, a + ba::kActUnit, w.units[chance(rng, 80) ? i : rng() % kNumUnits]);
        store16(m, a + ba::kActMoveKind, static_cast<u16>(pick({0u, 1u, 2u, 3u, 4u, 4u, 9u, rng() & 0xFFFFu})));
        store16(m, a + ba::kActSkill, static_cast<u16>(chance(rng, 90) ? rng() % kNumSkills : rng() % 64));
        store16(m, a + ba::kActPrev, static_cast<u16>(rng() % 36));
        const u32 ncand = chance(rng, 15) ? 0u : 1 + rng() % 8;
        store16(m, a + ba::kActCandidateCount, static_cast<u16>(ncand));
        for (u32 k = 0; k < 12; ++k) store32(m, a + ba::kActCandidates + 4 * k, some_action());
        store16(m, a + ba::kActTargetCount, static_cast<u16>(rng() % 4));
        for (u32 k = 0; k < 12; ++k) store32(m, a + ba::kActTarget + 4 * k, some_action());
        // the result block a hit leaves in the target (ATTACK / SKILL read it): records, hits, flags, damage, the
        // 28-byte records from +200 (+248 reaction motion, +250 flags)
        m.at(a + 200)[0] = static_cast<u8>(1 + rng() % 2);
        m.at(a + 201)[0] = static_cast<u8>(chance(rng, 10) ? 0 : 1 + rng() % 3);
        store16(m, a + 204, static_cast<u16>(pick({0u, 0u, 4u, 1024u, rng() & 0xFFFFu})));
        store16(m, a + 206, static_cast<u16>(pick({0u, 0u, 2u, 4u, rng() & 0xFFFFu})));
        store32(m, a + 208, chance(rng, 80) ? 0u : 1u);
        store32(m, a + 212, chance(rng, 80) ? 0u : 1u);
        store32(m, a + 220, chance(rng, 60) ? 0u : rng() % 64);
        for (u32 k = 0; k < 2; ++k) {
            store32(m, a + 224 + 28 * k, chance(rng, 20) ? 0u : rng() % 500);
            store32(m, a + 232 + 28 * k, chance(rng, 30) ? (rng() | 0x100000u) : (rng() & ~0x100000u));
            m.at(a + 248 + 28 * k)[0] = static_cast<u8>(pick({18u, 8u, 0xFDu, 22u, 2u, rng() & 0xFFu}));
            store16(m, a + 250 + 28 * k, static_cast<u16>(chance(rng, 50) ? 0u : rng() % 8));
        }
        store16(m, a + ba::kActWait, static_cast<u16>(chance(rng, 50) ? 0u : rng() % 30));
        store32(m, a + ba::kActWaitOn, chance(rng, 30) ? 1u : 0u);
    }
    // some queued packets belong to the current action
    const u32 cur = load32(m, kG + ba::kCurrentAction);
    for (u32 k = 0; k < next_packet; ++k)
        if (chance(rng, 20)) store64(m, kPackets + 0x100u * k + 96, load32(m, cur) | (static_cast<u64>(load32(m, cur + 4)) << 32));
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
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds), with a
// cycle budget (a queue that a packet buffer reused in one run turned into a loop would never end; both bodies stop
// at the same check point).
constexpr u64 kBudget = 400'000'000;
constexpr std::size_t kMaxSnaps = 200'000;  // check points kept (all are counted)
class ActHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    Snap at_stop;
    int syscalls = 0;
    u64 limit = 0;
    int loop_breaks = 0;
    std::size_t checks = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        if (snaps.size() < kMaxSnaps) snaps.push_back(snap(ctx));
        if (ctx.cycles > limit) {
            // A queue walk around the packet buffer queued twice (its +124 next pointing at itself): break the link,
            // in both runs at the same check point, and go on (a throw here could cross a noexcept guest::backedge
            // of another slice's hand-written callee).
            u32 next = 0;
            std::memcpy(&next, ctx.memory->main_ram() + kPacketBuf + 124, 4);
            if (next == kPacketBuf) {
                const u32 zero = 0;
                std::memcpy(ctx.memory->main_ram() + kPacketBuf + 124, &zero, 4);
                limit = ctx.cycles + kBudget;
                ++loop_breaks;
                return;
            }
            fatal(ctx, 0xB0D6E7u, "cycle budget");
        }
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        if (std::getenv("P3FES_BA_TRACE")) std::fprintf(stderr, "  fatal %08x %s (ra %08x)\n", pc, what, ctx.gpr[31].u32[0]);
        stopped = true;
        stop_pc = pc;
        this->what = what;
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

struct Run {
    std::size_t checks = 0;
    int loop_breaks = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
};

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed) {
    ActHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
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
    r.loop_breaks = h.loop_breaks;
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;  // missing function -> count
    std::map<std::string, int> faults;  // other stops by message (up to the address)
};
std::map<std::string, Stats> g_stats;

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled run.
// Every pair restores and compares the whole 32 MiB of main RAM (write_tracker.h: only the pages written are copied and
// compared), on the test's BaseRange when it has one (g_ram: the random worlds, restored before every body), else on
// a PairRange of its own. (Until 2026-10-21: the windows below on every pair, the whole RAM on every 25th.)
BaseRange* g_ram = nullptr;
int g_full_compares = 0;
int g_loop_breaks = 0;

Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    std::optional<PairRange> own;
    if (g_ram) g_ram->begin();
    else own.emplace(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    Run h = run_one(m, hand, args, seed);
    if (g_ram) g_ram->between();
    else own->between();
    Run r = run_one(m, recomp, args, seed);
    {
        ++g_full_compares;
        const std::size_t first = g_ram ? g_ram->first_difference() : own->first_difference();
        const std::size_t at = first < EEMemory::kMainRamSize ? first : 0;
        INFO(std::string(what) << ": whole main RAM, first differing byte at " << hex64(first) << " hand "
                               << unsigned(g_ram ? g_ram->first_body_byte(at) : own->first_body_byte(at)) << " recomp "
                               << unsigned(m.mem.main_ram()[at]));
        CHECK(first == EEMemory::kMainRamSize);
    }
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
        if (r.what.rfind("missing_function", 0) != 0) ++st.faults[r.what.substr(0, r.what.find(" at virtual"))];
    }
    const std::string name(what);
    INFO(name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed);
    REQUIRE(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.checks == r.checks);
    CHECK(h.loop_breaks == r.loop_breaks);
    g_loop_breaks += r.loop_breaks;
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(h.snaps[i], r.snaps[i]);
        if (!d.empty() && std::getenv("P3FES_BA_DEBUG")) {  // the check points around the first difference ($ra names the call)
            for (std::size_t k = i > 6 ? i - 6 : 0; k < std::min(n, i + 3); ++k)
                std::printf("cp %zu: hand cyc %llu ra %08x v0 %llx v1 %llx | recomp cyc %llu ra %08x v0 %llx v1 %llx\n", k,
                            static_cast<unsigned long long>(h.snaps[k].cycles), h.snaps[k].gpr[31].u32[0],
                            static_cast<unsigned long long>(h.snaps[k].gpr[2].u64[0]), static_cast<unsigned long long>(h.snaps[k].gpr[3].u64[0]),
                            static_cast<unsigned long long>(r.snaps[k].cycles), r.snaps[k].gpr[31].u32[0],
                            static_cast<unsigned long long>(r.snaps[k].gpr[2].u64[0]), static_cast<unsigned long long>(r.snaps[k].gpr[3].u64[0]));
        }
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
    return r;
}

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

enum class Arg { action, state };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};

#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_btlMainUpdateStateUnitLoad_0029c110, state),
    SPEC(fn_btlMainUpdateStateRevival_0029ccd0, state),
    SPEC(fn_btlMainInitStateWin_0029ce90, state),
    SPEC(fn_btlMainInitStateUnitLoad_0029be40, state),
    SPEC(fn_btlMainInitStateEnd_0029d870, state),
    SPEC(fn_sub_28BD10_0028bd10, action),
    SPEC(fn_sub_28BF80_0028bf80, action),
    SPEC(fn_sub_28C310_0028c310, action),
    SPEC(fn_sub_28C590_0028c590, action),
    SPEC(fn_btlMainInitStateRevival_0029c700, state),
    SPEC(fn_btlMainInitStateCondition_0029d1f0, state),
    SPEC(fn_btlMainInitStateUnitCreate_0029b280, state),
    SPEC(fn_btlMainUpdateStateUnitCreate_0029b760, state),
    SPEC(fn_btlActionUpdateStateEscape_00296890, action),
    SPEC(fn_btlActionUpdateStateAttack_0028eb50, action),
    SPEC(fn_btlActionUpdateStateSkill_00290be0, action),
};
#undef SPEC

Args args_for(Arg kind, const World& w, std::mt19937& rng) {
    switch (kind) {
    case Arg::action:
        return Args{wide(rng, w.actions[rng() % kNumActions]), rng(), rng(), rng()};
    case Arg::state:
        return Args{wide(rng, kG + ba::kMainState), rng(), rng(), rng()};
    }
    return {};
}

}  // namespace

// printf (0x5225A8) is hand-written since finalB (game/src/fx/finalB.cpp): its forwarder runs the body -- vfprintf into
// the stdout FILE, which waits on the IOP until the cycle budget -- where these pairs ended at it as at a function this
// build does not emit. The stop keeps the stop: both runs end at the call and are compared there
// (StandIns::install_stop). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas) si.install_stop(va, "stopped at, as when it was not emitted");
        scope = std::make_unique<StandInsScope>(si);
    }
};

TEST_CASE("game(battle_actions): every replaced state body equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0xBA77u};
    g_stats.clear();
#ifdef NDEBUG
    constexpr int kWorlds = 600;
#else
    constexpr int kWorlds = 200;  // Debug builds (clang-cl): the same worlds, a third of them
#endif
    // the whole RAM of the current world (write_tracker.h BaseRange: restoring copies back only the pages written)
    BaseRange fresh(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    g_ram = &fresh;
    struct Unset {
        ~Unset() { g_ram = nullptr; }
    } unset;
    for (int it = 0; it < kWorlds; ++it) {
        const World w = random_world(m, rng);
        // every body starts from the same fresh world (not from the previous body's output: a packet buffer queued
        // twice links to itself, and a later queue walk would never end) -- all of main RAM since 2026-10-21 (was the
        // windows below)
        fresh.rebase();
        for (const Spec& s : kSpecs) {
            fresh.restore();
            const Args a = args_for(s.arg, w, rng);
            store32(m, kHeapHook, s.hand == &recomp_gen::fn_btlMainInitStateUnitCreate_0029b280 ? 0u : kAllocStub);
            // ESCAPE rebuilds the turn order through sub_29A750 when gBtl+584 bit 1 is set; on these random worlds that
            // order builder (and the hand-written battle_data sort below it) can loop forever, so the bit stays clear
            if (s.hand == &recomp_gen::fn_btlActionUpdateStateEscape_00296890)
                store16(m, kG + ba::kOrderFlags, static_cast<u16>(load16(m, kG + ba::kOrderFlags) & ~2u));
            if (std::getenv("P3FES_BA_TRACE")) std::fprintf(stderr, "%d %s\n", it, s.name);
            pair(m, s.hand, s.recomp, a, rng(), s.name);
        }
    }
    int pairs = 0, stops = 0;
    std::string detail;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        detail += "\n  " + name + ": " + std::to_string(st.pairs) + " pairs, " + std::to_string(st.pairs - st.stops) + " returned";
        for (const auto& [pc, n] : st.stop_at) detail += ", " + std::to_string(n) + " at " + hex64(pc);
        for (const auto& [msg, n] : st.faults) detail += "\n    " + std::to_string(n) + " x " + msg;
    }
    MESSAGE("battle_actions: " << pairs << " pairs over " << std::size(kSpecs) << " functions (" << g_full_compares
                               << " with the whole main RAM restored and compared; " << g_loop_breaks
                               << " self-linked packet-buffer queue walks broken), " << stops
                               << " ended at a compared stop:" << detail);
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_actions): the documented rules (REVIVAL wait, the command wait, the whole-side targets)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0x5EEDu};
    g_stats.clear();
    int revival_waits = 0, command_waits = 0, side_targets = 0;
    for (int it = 0; it < 400; ++it) {
        const World w = random_world(m, rng);
        store32(m, kHeapHook, kAllocStub);
        // REVIVAL update: while an active packet (+71 bit 5) of the current action is queued (+96 with the two tag
        // bits masked equal to the action's uid: btlPacketFindFirstByActionUID) it stays (0).
        {
            const u32 cur = load32(m, kG + ba::kCurrentAction);
            u64 uid;
            std::memcpy(&uid, m.at(cur), 8);
            if (chance(rng, 70)) {  // make one queued packet the current action's (a uid without the tag bits)
                uid &= 0x3FFFFFFFFFFFFFFFull;
                store64(m, cur, uid);
                for (u32 q = 0; q < 4; ++q)
                    if (const u32 p = load32(m, kG + ba::kPacketQueues + 8 * q); p != 0) {
                        store64(m, p + 96, uid | (static_cast<u64>(rng() & 3) << 62));
                        m.at(p + 71)[0] |= 0x20;
                        break;
                    }
            }
            bool queued = false;
            for (u32 q = 0; q < 4; ++q)
                for (u32 p = load32(m, kG + ba::kPacketQueues + 8 * q); p != 0; p = load32(m, p + 124)) {
                    u64 owner;
                    std::memcpy(&owner, m.at(p + 96), 8);
                    queued = queued || ((owner & 0x3FFFFFFFFFFFFFFFull) == uid && (m.at(p + 71)[0] & 0x20) != 0);
                }
            const Run r = pair(m, PAIR(fn_btlMainUpdateStateRevival_0029ccd0), Args{sx(kG + ba::kMainState), 0, 0, 0}, rng(), "revival rule");
            if (queued && !r.stopped) {
                CHECK(v0_of(r) == 0);
                ++revival_waits;
            }
        }
        // COMMAND update: a refused command's wait (+1160 == 1) counts +1156 down and stays in COMMAND.
        {
            const u32 a = w.actions[rng() % kNumActions];
            store32(m, a + ba::kActWaitOn, 1);
            const u16 n = static_cast<u16>(1 + rng() % 20);
            store16(m, a + ba::kActWait, n);
            const u16 state = load16(m, a + ba::kActState);
            const Run r = pair(m, PAIR(fn_sub_28BF80_0028bf80), Args{sx(a), 0, 0, 0}, rng(), "command rule");
            if (!r.stopped) {
                CHECK(load16(m, a + ba::kActWait) == n - 1);
                CHECK(load32(m, a + ba::kActWaitOn) == 1u);
                CHECK(load16(m, a + ba::kActState) == state);
                ++command_waits;
            }
        }
        // TARGET update with a whole-side skill (SKILL.TBL +8 == 1 or 2): every candidate becomes a target.
        {
            const u32 a = w.actions[rng() % kNumActions];
            const u16 skill = static_cast<u16>(rng() % kNumSkills);
            store16(m, a + ba::kActSkill, skill);
            m.at(kSkillTbl + 44u * skill + 8)[0] = static_cast<u8>(1 + rng() % 2);
            const u16 n = load16(m, a + ba::kActCandidateCount);
            std::array<u32, 12> cand{};
            for (u32 k = 0; k < 12; ++k) cand[k] = load32(m, a + ba::kActCandidates + 4 * k);
            store16(m, a + ba::kActTargetCount, 0xFFFFu);  // a sentinel: the copy writes the count when it ran
            store16(m, a + ba::kActState, 6);  // TARGET
            const u16 state = 6;
            pair(m, PAIR(fn_sub_28C590_0028c590), Args{sx(a), 0, 0, 0}, rng(), "target rule");
            // (a cancel or a confirm moves on to COMMAND / READY, whose inits reset the target record)
            if (load16(m, a + ba::kActTargetCount) != 0xFFFFu && load16(m, a + ba::kActState) == state) {
                CHECK(load16(m, a + ba::kActTargetCount) == n);
                bool same = true;
                for (u32 k = 0; k < n && k < 12; ++k) same = same && load32(m, a + ba::kActTarget + 4 * k) == cand[k];
                CHECK(same);
                ++side_targets;
            }
        }
    }
    MESSAGE("rules: " << revival_waits << " revival waits, " << command_waits << " command waits, " << side_targets
                      << " whole-side target copies");
    CHECK(revival_waits > 20);
    CHECK(command_waits > 20);
    CHECK(side_targets > 20);
}

#else
TEST_CASE("game(battle_actions): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
