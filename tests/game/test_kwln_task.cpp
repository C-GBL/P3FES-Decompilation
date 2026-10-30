// Phase 5 pair tests for the kwln task kernel (game/src/kwln/task.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines built from random task worlds -- three state
// lists in priority order, a parent/child forest, the pause words, the kwlnRoot flags, the pads, and
// H_Malloc's slot table so that creation and destruction allocate and free inside the compared arena. Per
// call the harness compares $v0, the callee-saved registers, the cycles and the check points; on top of
// that this file compares the kernel's $gp variables (0x7CE040..0x7CE140), the two pad records, the WHOLE
// dead stack (the kernel's frames are live on the stack while a task callback runs, so the hand versions
// write the original prologue spills: the bytes must be identical, not just masked) and every general
// register (game code reads caller-saved ones the kernel leaves). Update/destroy callbacks are replaced
// kernel functions reached through the dispatch table (kwlnTaskGetWorkData returns the record's work word,
// so the work word scripts what an update returns: 0 keep, -1 finish, or the next callback). The worlds
// avoid the configurations on which the original itself never terminates (see make_world and the destroy
// test). Host-side checks restate the documented rules
// (docs/ANALYSIS/10_frame_loop_gs.md section 3, 20_menu_ui.md section 2.1): priority order with FIFO among
// equals, the start/end waits, name lookup, the 25th-byte quirk of the name copy.
#include "pair_harness.h"

#include "p3fes/game/task.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string>
#include <utility>
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
P3FES_DECL_PAIR(fn_kwlnTaskRemoveFromList_001939d0)
P3FES_DECL_PAIR(fn_kwlnTaskAddToList_00193ba0)
P3FES_DECL_PAIR(fn_kwlnTaskUpdate_00193ec0)
P3FES_DECL_PAIR(fn_kwlnTaskUpdateAll_00194100)
P3FES_DECL_PAIR(fn_kwlnTaskDestroyHierarchy_001941f0)
P3FES_DECL_PAIR(fn_kwlnTaskDestroy_00194280)
P3FES_DECL_PAIR(fn_kwlnTaskSetFlagsRecursive_001943b0)
P3FES_DECL_PAIR(fn_kwlnTaskSetFlagsByMode_001944c0)
P3FES_DECL_PAIR(fn_kwlnTaskMain_001949e0)
P3FES_DECL_PAIR(fn_kwlnTaskCreate_00194b20)
P3FES_DECL_PAIR(fn_kwlnTaskCreateWithAutoPriority_00194b80)
P3FES_DECL_PAIR(fn_kwlnTaskInit_00194c50)
P3FES_DECL_PAIR(fn_kwlnTaskInitEx_00194e10)
P3FES_DECL_PAIR(fn_kwlnTaskDestroyWithHierarchyByName_00194fe0)
P3FES_DECL_PAIR(fn_kwlnTaskDestroyWithHierarchy_00195020)
P3FES_DECL_PAIR(fn_kwlnTaskGetState_00195290)
P3FES_DECL_PAIR(fn_kwlnTaskGetTaskByName_00195340)
P3FES_DECL_PAIR(fn_kwlnTaskGetUpdating_00195450)
P3FES_DECL_PAIR(fn_kwlnTaskExists_00195460)
P3FES_DECL_PAIR(fn_kwlnTaskGetTimer_00195520)
P3FES_DECL_PAIR(fn_kwlnTaskSetWorkData_00195530)
P3FES_DECL_PAIR(fn_kwlnTaskGetWorkData_00195540)
P3FES_DECL_PAIR(fn_kwlnTaskAddChild_00195550)
P3FES_DECL_PAIR(fn_kwlnTaskDetachParent_001955f0)
P3FES_DECL_PAIR(fn_kwlnTaskDetachAllChildren_00195690)
P3FES_DECL_PAIR(fn_kwlnTaskSetFlags_001956d0)
P3FES_DECL_PAIR(fn_kwlnTaskClearFlags_00195710)
P3FES_DECL_PAIR(fn_kwlnTaskIsBandAEnabled_00195750)
P3FES_DECL_PAIR(fn_kwlnTaskSetBandBEnabled_00195770)
P3FES_DECL_PAIR(fn_kwlnTaskIsBandBEnabled_00195790)
P3FES_DECL_PAIR(fn_kwlnTaskMoveAfter_001957b0)
P3FES_DECL_PAIR(fn_kwlnTaskMoveBefore_001958a0)
P3FES_DECL_PAIR(fn_kwlnGetFlags_00198600)
P3FES_DECL_PAIR(fn_kwlnSetFlags_00198610)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game::kwln;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout of the test worlds ----------------------------------------------------------------------
constexpr u32 kNames = kArena;           // name strings handed to Init / GetTaskByName (0x100 bytes)
constexpr u32 kTable = kArena + 0x100;   // H_Malloc's slot table: kSlots x {addr, size}
constexpr u32 kSlots = 32;
constexpr u32 kHeap = kArena + 0x200;    // the records; the H_Malloc limit is the arena's end
constexpr u32 kLimit = kArena + kArenaSize;
constexpr u32 kStride = 0x70;            // H_Malloc rounds 0x68 up to 0x70
constexpr u32 kMaxStatic = 24;           // pre-built records; the other 8 slots are for Init

constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 kGlobals = 0x007CE040u;    // H_Malloc's count/limit/table, the three lists, updating, pause words,
constexpr u32 kGlobalsLen = 0x100;       // ..., kwlnRoot's flag word (0x7CE120)
constexpr u32 kPadArea = 0x007E0940u;    // gPads + gWorkPads
constexpr u32 kPadAreaLen = 0xE0;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }
constexpr u32 kMallocCount = gpv(-19628), kMallocLimit = gpv(-19624), kMallocTable = gpv(-19620);

// Callbacks (replaced kernel functions, reached through the dispatch table like any jalr target).
constexpr u32 kCbWork = 0x195540;          // kwlnTaskGetWorkData: returns the work word
constexpr u32 kCbDetachParent = 0x1955F0;  // leaves $v0 alone: the kernel's -1 finishes the task
constexpr u32 kCbDetachAll = 0x195690;     // destroy callback only: as an update it leaves task->child stale, the
                                           // kernel's own DetachAll then clears whatever $a1 points at and a later
                                           // DetachParent loops forever (in the original too)
constexpr u32 kCbDestroy = 0x194280;       // kwlnTaskDestroy(task) as an update: the task moves itself to ending
constexpr u32 kCbDestroyTree = 0x195020;   // kwlnTaskDestroyWithHierarchy(task)

u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }

u32 random_priority(std::mt19937& rng) {
    if (chance(rng, 60))
        return pick(rng, {0u, 1u, 5u, 0x100u, 0x815u, 0x816u, 0x817u, 0x832u, 0x833u, 0x900u, 0x103Du, 0x103Eu, 0x1063u,
                          0x1064u, 0x1500u, 0x1CD9u, 0x1CDAu, 0x1CE5u, 0x1CE6u, 0x2000u, 0x7FFFFFFFu, 0x80000000u, 0xFFFFFFFFu});
    return chance(rng, 50) ? rng() % 0x2400u : rng();
}

// --- one run with the extra state this kernel needs compared -----------------------------------------------
using Regs = std::initializer_list<std::pair<unsigned, u64>>;

struct Result {
    Outcome o;
    std::vector<u8> globals, pads;
    std::array<u64, 32> gpr{};
};

// pair_harness.h's run() plus the registers beyond $a0..$a3 ($t0..$t2 for the creators) and the kernel's
// state outside the arena.
Result run_one(Machine& m, Fn fn, const Args& args, u32 seed, Regs regs) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (const auto& [r, v] : regs) m.ctx.gpr[r].u64[0] = v;
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Result res;
    Outcome& o = res.o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned saved[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[saved[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    res.globals = m.bytes(kGlobals, kGlobalsLen);
    res.pads = m.bytes(kPadArea, kPadAreaLen);
    for (unsigned i = 0; i < 32; ++i) res.gpr[i] = m.ctx.gpr[i].u64[0];
    return res;
}

long g_pairs = 0;

// Hand version, then the recompiled body on the restored world; the recompiled run's results stay in place.
// The worlds must be ones on which the original terminates: a hang inside the (hand-written) kernel callees
// cannot be unwound (guest::enter/backedge are noexcept), so make_world avoids the known infinite walks.
Result pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, Regs regs = {}) {
    const std::vector<u8> arena = m.bytes(kArena, kArenaSize), globals = m.bytes(kGlobals, kGlobalsLen),
                          pads = m.bytes(kPadArea, kPadAreaLen);
    const Result h = run_one(m, hand, args, seed, regs);
    std::memcpy(m.at(kArena), arena.data(), arena.size());
    std::memcpy(m.at(kGlobals), globals.data(), globals.size());
    std::memcpy(m.at(kPadArea), pads.data(), pads.size());
    const Result r = run_one(m, recomp, args, seed, regs);
    expect_same(h.o, r.o, what);
    INFO(std::string(what));
    CHECK(h.globals == r.globals);
    CHECK(h.pads == r.pads);
    CHECK(h.o.dead_stack == r.o.dead_stack);
    // Every general register but $zero/$k0/$k1: game code reads caller-saved registers the kernel leaves
    // behind (a kwlnTaskExists caller in the boot path, kwlnTaskDetachAllChildren's $a1, an update callback
    // that keeps the kernel's -1 in $v0).
    for (unsigned i = 1; i < 32; ++i) {
        if (i == GPR_K0 || i == GPR_K1) continue;
        INFO("gpr " << i);
        CHECK(h.gpr[i] == r.gpr[i]);
    }
    ++g_pairs;
    return r;
}

// --- random task worlds --------------------------------------------------------------------------------------
struct WorldOpts {
    unsigned max_tasks = kMaxStatic;
    bool callbacks = false;     // valid update/destroy callbacks and scripted work words (for runs that call them)
    bool sorted = true;         // lists in priority order (AddToList's invariant)
    unsigned flag_percent = 30; // chance of random flag bits (0x10 / 0x20 among them)
    u32 force_flags = 0;        // OR-ed into every state word (0x40: no ending task ever reads as a whole 3)
};

struct World {
    std::vector<u32> tasks;      // record addresses
    std::array<std::vector<u32>, 4> lists;  // by state 1..3, in list order
};

void init_heap(Machine& m) {
    w32(m, kMallocCount, kSlots);
    w32(m, kMallocLimit, kLimit);
    w32(m, kMallocTable, kTable);
    std::memset(m.at(kTable), 0, kSlots * 8);
}

u32 name_sum(const Machine& m, u32 rec) {
    s32 sum = 0;
    const u8* p = m.mem.main_ram() + rec;
    for (u32 i = 0; i < 24 && p[i] != 0; ++i) sum += static_cast<s8>(p[i]);
    return static_cast<u32>(sum);
}

void random_name(Machine& m, u32 va, u32 len, std::mt19937& rng, bool ascii) {
    for (u32 i = 0; i < len; ++i) {
        u8 c = ascii ? static_cast<u8>('A' + rng() % 26) : static_cast<u8>(rng());
        if (c == 0) c = 'x';
        m.at(va)[i] = c;
    }
    m.at(va)[len] = 0;
}

// Links the records of each list in the order given, with heads, tails and counts.
void link_lists(Machine& m, World& w, std::mt19937& rng) {
    const ListVars lv[4] = {{}, kStartingList, kRunningList, kEndingList};
    for (u32 s = 1; s <= 3; ++s) {
        const std::vector<u32>& l = w.lists[s];
        for (std::size_t i = 0; i < l.size(); ++i) {
            const u32 t = l[i];
            w32(m, t + kOffNext, i + 1 < l.size() ? l[i + 1] : 0);
            w32(m, t + kOffPrev, i > 0 ? l[i - 1] : 0);
            // +0x48 equals prev after an insertion; a head inserted into a non-empty list keeps the value of its
            // previous list (UpdateAll's walk reads it): a starting task for a running head, a running task for
            // an ending head.
            u32 prev2 = i > 0 ? l[i - 1] : 0;
            if (i == 0 && s > 1 && !w.lists[s - 1].empty() && chance(rng, 50)) prev2 = w.lists[s - 1][rng() % w.lists[s - 1].size()];
            w32(m, t + kOffPrev2, prev2);
        }
        w32(m, gpv(lv[s].head), l.empty() ? 0 : l.front());
        w32(m, gpv(lv[s].tail), l.empty() ? 0 : l.back());
        w32(m, gpv(lv[s].count), static_cast<u32>(l.size()));
    }
}

World make_world(Machine& m, std::mt19937& rng, const WorldOpts& o) {
    World w;
    fill_random(m, kArena, kArenaSize, rng);
    init_heap(m);
    fill_random(m, kPadArea, kPadAreaLen, rng);
    std::memset(m.at(kGlobals + 0x24), 0, 0x30);  // the list variables, updating, the pause words
    w32(m, gpv(kGpPauseBandA), pick(rng, {0u, 0u, 1u, 2u}));
    w32(m, gpv(kGpPauseBandB), pick(rng, {0u, 0u, 1u, 2u}));
    w32(m, gpv(kGpKwlnFlags), pick(rng, {0u, 0u, 0x40000000u, 0x80000000u, 0x00000001u}) | (rng() & 0x0F00u));
    const unsigned n = o.max_tasks == 0 ? 0 : rng() % (o.max_tasks + 1);
    std::vector<unsigned> depth;
    for (unsigned i = 0; i < n; ++i) {
        const u32 t = kHeap + i * kStride;
        w.tasks.push_back(t);
        w32(m, kTable + i * 8, t);
        w32(m, kTable + i * 8 + 4, kStride);
        const u32 len = chance(rng, 10) ? 23 : 1 + rng() % 12;
        random_name(m, t, len, rng, chance(rng, 70));
        m.at(t)[23] = 0;
        w32(m, t + kOffNameSum, chance(rng, 90) ? name_sum(m, t) : rng());
        const u32 list = 1 + rng() % 3;
        u32 flags = (chance(rng, o.flag_percent) ? (rng() & kFlagBits) : 0) | o.force_flags;
        if (chance(rng, 15)) flags |= kFlagNeutralPads;
        if (chance(rng, 8)) flags |= kFlagPaused;
        w32(m, t + kOffState, list | flags);
        w32(m, t + kOffPriority, random_priority(rng));
        w32(m, t + kOffStartWait, pick(rng, {0u, 1u, 1u, 2u, 3u, 0xFFFFFFFFu}));
        w32(m, t + kOffEndWait, pick(rng, {0u, 1u, 2u, 2u, 3u, 0xFFFFFFFFu}));
        if (o.callbacks) {
            const bool may_destroy_self = flags == 0;  // otherwise the walk would continue into the ending list
            u32 up = pick(rng, {kCbWork, kCbWork, kCbWork, kCbWork, 0u, 0xFFFFFFFFu, kCbDetachParent, kCbDetachParent,
                                kCbDestroy, kCbDestroyTree});
            if (!may_destroy_self && (up == kCbDestroy || up == kCbDestroyTree)) up = kCbWork;
            w32(m, t + kOffUpdate, up);
            w32(m, t + kOffDestroy, pick(rng, {0u, 0u, kCbWork, kCbDetachAll, kCbDestroyTree}));
            u32 work = pick(rng, {0u, 0u, 0u, 0xFFFFFFFFu, kCbWork, kCbDetachParent});
            if (may_destroy_self && chance(rng, 5)) work = kCbDestroy;
            w32(m, t + kOffWork, work);
        }
        w32(m, t + kOffParent, 0);
        w32(m, t + kOffChild, 0);
        w32(m, t + kOffSibling, 0);
        // The forest: a parent among the earlier records, at most three levels deep.
        unsigned d = 0;
        if (i > 0 && chance(rng, 60)) {
            const unsigned p = rng() % i;
            if (depth[p] < 3) {
                const u32 pt = w.tasks[p];
                d = depth[p] + 1;
                w32(m, t + kOffParent, pt);
                if (r32(m, pt + kOffChild) == 0) {
                    w32(m, pt + kOffChild, t);
                } else {
                    u32 c = r32(m, pt + kOffChild);
                    while (r32(m, c + kOffSibling) != 0) c = r32(m, c + kOffSibling);
                    w32(m, c + kOffSibling, t);
                }
            }
        }
        depth.push_back(d);
        w.lists[list].push_back(t);
    }
    if (o.sorted) {
        for (u32 s = 1; s <= 3; ++s)
            std::stable_sort(w.lists[s].begin(), w.lists[s].end(),
                             [&](u32 a, u32 b) { return r32(m, a + kOffPriority) < r32(m, b + kOffPriority); });
    }
    link_lists(m, w, rng);
    return w;
}

// The list of state `s` read back from the guest (bounded, so a broken list cannot hang the host).
std::vector<u32> read_list(const Machine& m, u32 s) {
    const ListVars lv[4] = {{}, kStartingList, kRunningList, kEndingList};
    std::vector<u32> out;
    for (u32 t = r32(m, gpv(lv[s].head)); t != 0 && out.size() < 200; t = r32(m, t + kOffNext)) out.push_back(t);
    return out;
}

}  // namespace

TEST_CASE("game(kwln): the task record and the kernel variables are where the doc says") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    CHECK(sizeof(KwlnTask) == kTaskSize);
    CHECK(gpv(kStartingList.head) == 0x7CE064u);
    CHECK(gpv(kRunningList.head) == 0x7CE07Cu);
    CHECK(gpv(kGpKwlnFlags) == 0x7CE120u);
    CHECK(m.str(kStrSourceFile) == "kwlnTask.c");
    CHECK(m.str(kStrStatInvalid) == "Process stat Invalid!!");
    CHECK(m.str(kStrStatInvalidNl) == "Process stat Invalid!!\n");
    CHECK(m.str(kStrIdInvalid) == "ProcessID invalid!!\n");
}

TEST_CASE("game(kwln): RemoveFromList / AddToList equal their recompiled bodies; priority order, FIFO among equals") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{20261020u};
    int removed = 0, added = 0, invalid = 0, asserted = 0;
    for (int it = 0; it < 1500; ++it) {
        World w = make_world(m, rng, WorldOpts{});
        if (w.tasks.empty()) continue;
        const u32 t = w.tasks[rng() % w.tasks.size()];
        const u32 seed = rng();
        if (chance(rng, 8)) {  // a dead or invalid state: K_Abort (jr $ra in retail) and return
            w32(m, t + kOffState, (r32(m, t + kOffState) & ~kStateMask) | pick(rng, {0u, 4u, 9u, 15u}));
            pair(m, PAIR(fn_kwlnTaskRemoveFromList_001939d0), Args{t}, seed, "kwlnTaskRemoveFromList (invalid)");
            pair(m, PAIR(fn_kwlnTaskAddToList_00193ba0), Args{t}, seed, "kwlnTaskAddToList (invalid)");
            ++invalid;
            continue;
        }
        const u32 s = r32(m, t + kOffState) & kStateMask;
        pair(m, PAIR(fn_kwlnTaskRemoveFromList_001939d0), Args{t}, seed, "kwlnTaskRemoveFromList");
        ++removed;
        std::vector<u32> expect = w.lists[s];
        expect.erase(std::find(expect.begin(), expect.end(), t));
        CHECK(read_list(m, s) == expect);
        // Re-insert, possibly into another list and with another priority.
        const u32 s2 = 1 + rng() % 3;
        w32(m, t + kOffState, (r32(m, t + kOffState) & ~kStateMask) | s2);
        if (chance(rng, 50)) w32(m, t + kOffPriority, random_priority(rng));
        if (chance(rng, 5)) {  // the count assertion at 10,001
            const ListVars lv[4] = {{}, kStartingList, kRunningList, kEndingList};
            w32(m, gpv(lv[s2].count), pick(rng, {9999u, 10000u, 10001u, 0x7FFFFFFFu}));
            ++asserted;
        }
        std::vector<u32> before = read_list(m, s2);
        pair(m, PAIR(fn_kwlnTaskAddToList_00193ba0), Args{t}, seed + 1, "kwlnTaskAddToList");
        ++added;
        // The documented rule: before the first strictly greater (unsigned) priority.
        const u32 p = r32(m, t + kOffPriority);
        auto pos = std::find_if(before.begin(), before.end(), [&](u32 x) { return r32(m, x + kOffPriority) > p; });
        before.insert(pos, t);
        if (std::is_sorted(before.begin(), before.end(), [&](u32 a, u32 b) { return r32(m, a + kOffPriority) < r32(m, b + kOffPriority); }))
            CHECK(read_list(m, s2) == before);
    }
    CHECK(removed > 1000);
    CHECK(invalid > 50);
    CHECK(asserted > 30);
    MESSAGE("remove/add: " << removed << " / " << added << ", invalid " << invalid << ", count asserts " << asserted);
}

TEST_CASE("game(kwln): kwlnTaskUpdate equals its recompiled body on every skip band, flag and callback result") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{1949u};
    int ran = 0;
    for (int it = 0; it < 3000; ++it) {
        WorldOpts o;
        o.callbacks = true;
        World w = make_world(m, rng, o);
        if (w.lists[2].empty()) continue;
        const u32 t = w.lists[2][rng() % w.lists[2].size()];
        if (chance(rng, 20)) w32(m, t + kOffState, (r32(m, t + kOffState) & ~kStateMask) | pick(rng, {1u, 3u}));
        pair(m, PAIR(fn_kwlnTaskUpdate_00193ec0), Args{sx(t)}, rng(), "kwlnTaskUpdate");
        ++ran;
    }
    CHECK(ran > 1500);
}

TEST_CASE("game(kwln): UpdateAll and kwlnTaskMain equal their recompiled bodies over many frames") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1949E0u};
    int frames = 0, retired = 0, started = 0;
    for (int it = 0; it < 400; ++it) {
        WorldOpts o;
        o.callbacks = true;
        o.flag_percent = it % 4 == 0 ? 0 : 20;
        make_world(m, rng, o);
        if (chance(rng, 30)) pair(m, PAIR(fn_kwlnTaskUpdateAll_00194100), Args{}, rng(), "kwlnTaskUpdateAll");
        for (int f = 0; f < 8; ++f) {
            const std::size_t ending_before = read_list(m, 3).size(), starting_before = read_list(m, 1).size();
            const Result r = pair(m, PAIR(fn_kwlnTaskMain_001949e0), Args{}, rng(), "kwlnTaskMain");
            CHECK(r.o.v0 == 1);
            ++frames;
            if (read_list(m, 3).size() < ending_before) ++retired;
            if (read_list(m, 1).size() < starting_before) ++started;
        }
    }
    CHECK(retired > 100);
    CHECK(started > 100);
    MESSAGE("kwlnTaskMain: " << frames << " frames, " << retired << " with retirements, " << started << " with starts");
}

TEST_CASE("game(kwln): the destroy family equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x194280u};
    for (int it = 0; it < 1500; ++it) {
        WorldOpts o;
        o.callbacks = true;
        // An update that destroys its running predecessor makes the walk resume through the ending head's
        // stale +0x48; when that leads into the ending list, a task there whose state word is exactly 3 ends
        // again on every visit and the original loops forever. A spare flag bit keeps these worlds finite.
        o.force_flags = 0x40;
        World w = make_world(m, rng, o);
        if (w.tasks.empty()) continue;
        const u32 t = w.tasks[rng() % w.tasks.size()];
        switch (it % 5) {
        case 0:
            pair(m, PAIR(fn_kwlnTaskDestroy_00194280), Args{sx(t)}, rng(), "kwlnTaskDestroy");
            break;
        case 1:
            pair(m, PAIR(fn_kwlnTaskDestroyHierarchy_001941f0), Args{chance(rng, 5) ? 0 : sx(t)}, rng(), "kwlnTaskDestroyHierarchy");
            break;
        case 2: {
            u64 arg = sx(t);
            if (chance(rng, 5)) arg = 0;
            if (chance(rng, 5)) arg = ~0ull;
            if (chance(rng, 5)) w32(m, t + kOffState, (r32(m, t + kOffState) & ~kStateMask) | pick(rng, {0u, 5u}));
            pair(m, PAIR(fn_kwlnTaskDestroyWithHierarchy_00195020), Args{arg}, rng(), "kwlnTaskDestroyWithHierarchy");
            break;
        }
        case 3: {
            // By name: a listed task's name, or a fresh string (no match).
            u32 name = t;
            if (chance(rng, 30)) {
                random_name(m, kNames, 1 + rng() % 10, rng, true);
                name = kNames;
            }
            pair(m, PAIR(fn_kwlnTaskDestroyWithHierarchyByName_00194fe0), Args{name}, rng(), "kwlnTaskDestroyWithHierarchyByName");
            break;
        }
        default:
            // A whole frame after a destroy, so the ending list retires what was destroyed.
            pair(m, PAIR(fn_kwlnTaskDestroyWithHierarchy_00195020), Args{sx(t)}, rng(), "kwlnTaskDestroyWithHierarchy");
            pair(m, PAIR(fn_kwlnTaskMain_001949e0), Args{}, rng(), "kwlnTaskMain after a destroy");
            pair(m, PAIR(fn_kwlnTaskMain_001949e0), Args{}, rng(), "kwlnTaskMain after a destroy");
            break;
        }
    }
}

TEST_CASE("game(kwln): the flag helpers equal their recompiled bodies in every mode") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1944C0u};
    for (int it = 0; it < 1500; ++it) {
        World w = make_world(m, rng, WorldOpts{});
        const u32 t = w.tasks.empty() || chance(rng, 5) ? 0 : w.tasks[rng() % w.tasks.size()];
        const u64 set = pick(rng, {0u, 1u, 2u}) == 0 ? 0 : (chance(rng, 50) ? 1 : sx(rng()));
        const u64 mask = chance(rng, 50) ? sx(rng()) : sx(pick(rng, {0x10u, 0x20u, 0x30u, 0xFFFFFFFFu, 0x0Fu}));
        const u64 mode = chance(rng, 90) ? rng() % 4 : sx(pick(rng, {4u, 7u, 0xFFFFFFFFu}));
        if (t != 0 && it % 4 == 0)
            pair(m, PAIR(fn_kwlnTaskSetFlagsRecursive_001943b0), Args{set, sx(t), mask}, rng(), "kwlnTaskSetFlagsRecursive");
        pair(m, PAIR(fn_kwlnTaskSetFlagsByMode_001944c0), Args{set, sx(t), mask, mode}, rng(), "kwlnTaskSetFlagsByMode");
        pair(m, PAIR(fn_kwlnTaskSetFlags_001956d0), Args{sx(t), mask, mode}, rng(), "kwlnTaskSetFlags");
        pair(m, PAIR(fn_kwlnTaskClearFlags_00195710), Args{sx(t), mask, mode}, rng(), "kwlnTaskClearFlags");
    }
}

TEST_CASE("game(kwln): Init / InitEx / Create / CreateWithAutoPriority equal their recompiled bodies; the name copy") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x194C50u};
    int created = 0, long_names = 0;
    for (int it = 0; it < 1200; ++it) {
        WorldOpts o;
        o.max_tasks = 16;
        o.callbacks = true;
        World w = make_world(m, rng, o);
        // The name: empty (asserts), short, exactly 23/24/25 bytes (the copy's edge), longer.
        const u32 len = pick(rng, {0u, 1u, 5u, 11u, 22u, 23u, 24u, 25u, 26u, 40u});
        random_name(m, kNames, len, rng, chance(rng, 60));
        const u32 prio = random_priority(rng);
        const u32 parent = w.tasks.empty() || chance(rng, 20) ? 0 : w.tasks[rng() % w.tasks.size()];
        const u64 update = sx(kCbWork), destroy = sx(pick(rng, {0u, kCbWork})), work = sx(pick(rng, {0u, 0xFFFFFFFFu}));
        const u32 seed = rng();
        Result r;
        switch (it % 4) {
        case 0:
            r = pair(m, PAIR(fn_kwlnTaskInit_00194c50), Args{sx(kNames), sx(prio), update, destroy}, seed, "kwlnTaskInit",
                     {{GPR_T0, work}});
            break;
        case 1: {
            const u64 sw = sx(pick(rng, {0u, 0u, 1u, 3u, 0xFFFFFFFFu})), ew = sx(pick(rng, {0u, 1u, 2u}));
            r = pair(m, PAIR(fn_kwlnTaskInitEx_00194e10), Args{sx(kNames), sx(prio), sw, ew}, seed, "kwlnTaskInitEx",
                     {{GPR_T0, update}, {GPR_T1, destroy}, {GPR_T2, work}});
            break;
        }
        case 2:
            r = pair(m, PAIR(fn_kwlnTaskCreate_00194b20), Args{sx(parent), sx(kNames), sx(prio), update}, seed,
                     "kwlnTaskCreate", {{GPR_T0, destroy}, {GPR_T1, work}});
            break;
        default:
            r = pair(m, PAIR(fn_kwlnTaskCreateWithAutoPriority_00194b80), Args{sx(parent), sx(prio), sx(kNames), update}, seed,
                     "kwlnTaskCreateWithAutoPriority", {{GPR_T0, destroy}, {GPR_T1, work}});
            break;
        }
        const u32 rec = static_cast<u32>(r.o.v0);
        REQUIRE(rec >= kHeap);
        REQUIRE(rec + kTaskSize <= kLimit);
        ++created;
        // The copy: bytes up to the terminator or 25 bytes (the 25th lands in the low byte of +0x18), [23] = 0;
        // the sum covers at most the first 24 bytes.
        const u32 copied = std::min<u32>(len, 24);
        s32 sum = 0;
        for (u32 i = 0; i < copied; ++i) sum += static_cast<s8>(m.at(kNames)[i]);
        const u32 sum_word = r32(m, rec + kOffNameSum);
        if (len >= 24) {
            ++long_names;
            CHECK((sum_word & 0xFFu) == m.at(kNames)[24]);
            CHECK((sum_word & ~0xFFu) == (static_cast<u32>(sum) & ~0xFFu));
        } else {
            CHECK(sum_word == static_cast<u32>(sum));
        }
        CHECK(m.at(rec)[23] == 0);
        CHECK(std::memcmp(m.at(rec), m.at(kNames), std::min<u32>(copied, 23)) == 0);
        CHECK((r32(m, rec + kOffState) & kStateMask) == (r32(m, rec + kOffStartWait) == 0 ? kStateRunning : kStateStarting));
    }
    CHECK(created > 1000);
    CHECK(long_names > 300);
}

TEST_CASE("game(kwln): lookups, accessors, tree links, pause words and MoveAfter/Before equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x195340u};
    int found = 0;
    for (int it = 0; it < 2000; ++it) {
        WorldOpts o;
        o.sorted = chance(rng, 80);
        World w = make_world(m, rng, o);
        const u32 t = w.tasks.empty() ? kHeap : w.tasks[rng() % w.tasks.size()];
        const u32 u = w.tasks.empty() ? kHeap : w.tasks[rng() % w.tasks.size()];
        const u32 seed = rng();
        // kwlnTaskGetTaskByName: a listed name (also from inside the record: the sum must match), or random text.
        u32 name = t;
        if (chance(rng, 30)) {
            random_name(m, kNames, rng() % 12, rng, true);
            name = kNames;
        }
        const Result byname = pair(m, PAIR(fn_kwlnTaskGetTaskByName_00195340), Args{name}, seed, "kwlnTaskGetTaskByName");
        if (byname.o.v0 != 0) {
            ++found;
            CHECK(m.str(static_cast<u32>(byname.o.v0)) == m.str(name));
        }
        pair(m, PAIR(fn_kwlnTaskGetUpdating_00195450), Args{}, seed, "kwlnTaskGetUpdating");
        // Exists: a listed record, an unlisted address, null, a wide register.
        const u64 probe = pick(rng, {0u, 1u, 2u, 3u}) == 0 ? 0 : (chance(rng, 70) ? sx(t) : sx(kHeap + 0x1800));
        pair(m, PAIR(fn_kwlnTaskExists_00195460), Args{probe}, seed, "kwlnTaskExists");
        if (!w.tasks.empty()) {
            pair(m, PAIR(fn_kwlnTaskGetState_00195290), Args{chance(rng, 80) ? sx(t) : 0}, seed, "kwlnTaskGetState");
            pair(m, PAIR(fn_kwlnTaskGetTimer_00195520), Args{t}, seed, "kwlnTaskGetTimer");
            pair(m, PAIR(fn_kwlnTaskSetWorkData_00195530), Args{t, sx(rng())}, seed, "kwlnTaskSetWorkData");
            pair(m, PAIR(fn_kwlnTaskGetWorkData_00195540), Args{t}, seed, "kwlnTaskGetWorkData");
            // Tree links: DetachAllChildren (with a stale $a1 when a child no longer points back), DetachParent
            // (whose $a1 the former reads), AddChild (null parent = no-op; re-parenting detaches first).
            switch (it % 3) {
            case 0:
                if (chance(rng, 30) && r32(m, t + kOffChild) != 0) w32(m, r32(m, t + kOffChild) + kOffParent, 0);
                pair(m, PAIR(fn_kwlnTaskDetachAllChildren_00195690), Args{t, kArena + 0x40}, seed, "kwlnTaskDetachAllChildren");
                break;
            case 1:
                if (chance(rng, 10) && r32(m, t + kOffParent) == 0) w32(m, t + kOffSibling, u);  // the 1519 assertion
                pair(m, PAIR(fn_kwlnTaskDetachParent_001955f0), Args{t}, seed, "kwlnTaskDetachParent");
                break;
            default: {
                // Never make a task its own ancestor (the original would loop forever in the walks).
                bool cycle = false;
                for (u32 a = u; a != 0; a = r32(m, a + kOffParent)) cycle |= a == t;
                if (!cycle) pair(m, PAIR(fn_kwlnTaskAddChild_00195550), Args{chance(rng, 10) ? 0 : sx(u), sx(t)}, seed, "kwlnTaskAddChild");
                break;
            }
            }
            // MoveAfter / MoveBefore on the running list (they do not fix the head or the tail: a game bug kept).
            if (it % 2 == 0) pair(m, PAIR(fn_kwlnTaskMoveAfter_001957b0), Args{u, t}, seed, "kwlnTaskMoveAfter");
            else pair(m, PAIR(fn_kwlnTaskMoveBefore_001958a0), Args{u, t}, seed, "kwlnTaskMoveBefore");
        }
        pair(m, PAIR(fn_kwlnTaskIsBandAEnabled_00195750), Args{}, seed, "kwlnTaskIsBandAEnabled");
        pair(m, PAIR(fn_kwlnTaskIsBandBEnabled_00195790), Args{}, seed, "kwlnTaskIsBandBEnabled");
        pair(m, PAIR(fn_kwlnTaskSetBandBEnabled_00195770), Args{pick(rng, {0u, 1u, 2u, 3u}) == 3 ? sx(rng()) : rng() % 3}, seed,
             "kwlnTaskSetBandBEnabled");
        pair(m, PAIR(fn_kwlnGetFlags_00198600), Args{}, seed, "kwlnGetFlags");
        pair(m, PAIR(fn_kwlnSetFlags_00198610), Args{sx(rng()), chance(rng, 50) ? 1 : sx(rng() % 3)}, seed, "kwlnSetFlags");
    }
    CHECK(found > 800);
    MESSAGE("kwln pairs in all: " << g_pairs);
}

#endif  // P3FES_GAME_HAVE_GENERATED
