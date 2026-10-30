// Phase 5 pair tests for the nm_message slice (game/src/ui/nm_message.cpp): nmlist.c / nmSequence.c / nmCmdList.c and
// the shared message-window helpers, the band 0x3C4430-0x3C7794. Each hand-written function and the recompiled body it
// replaces run on identical guest machines built from random structures -- node lists (well-formed, and with a broken
// count, cursor or flag word), list objects, nmSequence step lists, nmCmdList windows with their rows, the pad words,
// the message-window record 0x95BE90 and the itfMesMng slot table -- with the callbacks aimed at functions of the emitted
// set: leaves (0x3C4400 `v0 = 0`, identity, `v0 = a1`, 1) and a non-leaf that spills $ra below the $sp it receives and
// returns the word at gp-18968 (also the RwHeapMalloc of the eight heap functions the slice keeps recompiled: the slot
// 0x960178 points at it, 0x96017C at the `v0 = 0` leaf).
//
// Stricter than the Outcome (run_pair_hw): per pair this file compares EVERY general register in 128 bits, HI/LO, all
// FPU registers, ACC and FCR31 at the return, the whole register file and the cycle count at EVERY check point, the
// WHOLE 32 MiB of RAM (PairRange: only the pages written are copied), the dead stack (the hand versions write the
// original's spills), the scratchpad, the bus log, the virtual cycles and the check-point count. FPRs, ACC and HI/LO
// start random, so a register the original leaves alone must stay alone. A callee the test build does not emit (the
// itfMesMng window code behind printf, the sprite draw sub_3B2CB0) stops a run with a fatal event; both runs must stop
// at the same callee with the same machine state. Host-side checks restate documented behaviour (nm_message.h), and the
// real snapshots of the three replay routes (the message-window record, the three live nm list objects) are used where
// present.
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/game/nm_message.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
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
P3FES_DECL_PAIR(fn_nmListInsertAfter_003c4710)
P3FES_DECL_PAIR(fn_nmListUnlink_003c4820)
P3FES_DECL_PAIR(fn_nmListAppendNew_003c4910)
P3FES_DECL_PAIR(fn_nmListFindByKey_003c4b50)
P3FES_DECL_PAIR(fn_nmListFindByWord4_003c4bf0)
P3FES_DECL_PAIR(fn_nmListCursorNext_003c4c80)
P3FES_DECL_PAIR(fn_nmListCursorPrev_003c4d20)
P3FES_DECL_PAIR(fn_nmListCursorClearEnd_003c4dc0)
P3FES_DECL_PAIR(fn_sub_3C4DE0_003c4de0)
P3FES_DECL_PAIR(fn_nmListCursorSeek_003c4df0)
P3FES_DECL_PAIR(fn_nmListCursorHead_003c4e50)
P3FES_DECL_PAIR(fn_sub_3C4E60_003c4e60)
P3FES_DECL_PAIR(fn_nmListRemoveFiltered_003c4e70)
P3FES_DECL_PAIR(fn_nmByteSum_003c4f80)
P3FES_DECL_PAIR(fn_nmListRebuild_003c50b0)
P3FES_DECL_PAIR(fn_nmSeqNullStep_003c5170)
P3FES_DECL_PAIR(fn_nmSequenceCreate_003c5180)
P3FES_DECL_PAIR(fn_sub_3C5210_003c5210)
P3FES_DECL_PAIR(fn_nmSequenceDestroy_003c5220)
P3FES_DECL_PAIR(fn_nmSequenceAddStep_003c5240)
P3FES_DECL_PAIR(fn_sub_3C53E0_003c53e0)
P3FES_DECL_PAIR(fn_nmObjPayloadWord12_003c5460)
P3FES_DECL_PAIR(fn_sub_3C5470_003c5470)
P3FES_DECL_PAIR(fn_nmNodePayloadArea40_003c5480)
P3FES_DECL_PAIR(fn_sub_3C5490_003c5490)
P3FES_DECL_PAIR(fn_nmSequenceCallAll36_003c5760)
P3FES_DECL_PAIR(fn_sub_3C57E0_003c57e0)
P3FES_DECL_PAIR(fn_nmSeqStepOnRemove_003c5810)
P3FES_DECL_PAIR(fn_nmSeqStepRun_003c5840)
P3FES_DECL_PAIR(fn_nmSeqStepCall36_003c5870)
P3FES_DECL_PAIR(fn_nullsub_56_003c58a0)
P3FES_DECL_PAIR(fn_nullsub_57_003c58b0)
P3FES_DECL_PAIR(fn_nullsub_54_003c58c0)
P3FES_DECL_PAIR(fn_nullsub_55_003c58d0)
P3FES_DECL_PAIR(fn_nullsub_58_003c58e0)
P3FES_DECL_PAIR(fn_sub_3C58F0_003c58f0)
P3FES_DECL_PAIR(fn_nmCmdListDestroy_003c5a20)
P3FES_DECL_PAIR(fn_nmCmdListAddRow_003c5a40)
P3FES_DECL_PAIR(fn_sub_3C5AF0_003c5af0)
P3FES_DECL_PAIR(fn_nmCmdListCursorDown_003c5bb0)
P3FES_DECL_PAIR(fn_sub_3C5C50_003c5c50)
P3FES_DECL_PAIR(fn_nmCmdListSelect_003c5d40)
P3FES_DECL_PAIR(fn_nmCmdListSetDrawFunc_003c5e20)
P3FES_DECL_PAIR(fn_nmCmdListSetUpdateFunc_003c5e80)
P3FES_DECL_PAIR(fn_nmCmdListSetRowDrawFunc_003c5ee0)
P3FES_DECL_PAIR(fn_nmCmdListSetRowRemoveFunc_003c5f40)
P3FES_DECL_PAIR(fn_nmCmdListRemoveRow_003c5fa0)
P3FES_DECL_PAIR(fn_nmCmdListOnInsert_003c60c0)
P3FES_DECL_PAIR(fn_nmCmdListOnRemove_003c60f0)
P3FES_DECL_PAIR(fn_nmCmdListDrawRow_003c6120)
P3FES_DECL_PAIR(fn_nmCmdListUpdate_003c6270)
P3FES_DECL_PAIR(fn_nmCmdListDraw_003c6380)
P3FES_DECL_PAIR(fn_sub_3C63F0_003c63f0)
P3FES_DECL_PAIR(fn_nmCmdListStartFade_003c6900)
P3FES_DECL_PAIR(fn_sub_3C69D0_003c69d0)
P3FES_DECL_PAIR(fn_nmCmdListScrollBar_003c6b70)
P3FES_DECL_PAIR(fn_nmCmdListDecidedRow_003c6c50)
P3FES_DECL_PAIR(fn_nmCmdListCancelled_003c6c80)
P3FES_DECL_PAIR(fn_nmCmdListPagedDown_003c6ca0)
P3FES_DECL_PAIR(fn_nmCmdListMovedUp_003c6cc0)
P3FES_DECL_PAIR(fn_nmCmdListMovedDownRow_003c6ce0)
P3FES_DECL_PAIR(fn_nmCmdListScrolledRow_003c6d10)
P3FES_DECL_PAIR(fn_nmCmdListSetPosition_003c6d40)
P3FES_DECL_PAIR(fn_sub_3C6D60_003c6d60)
P3FES_DECL_PAIR(fn_nmCmdListStatus_003c6d80)
P3FES_DECL_PAIR(fn_nmCmdListStatus28_003c6e10)
P3FES_DECL_PAIR(fn_nmCmdListHold_003c6ea0)
P3FES_DECL_PAIR(fn_nmCmdListRelease_003c6ec0)
P3FES_DECL_PAIR(fn_sub_3C6EE0_003c6ee0)
P3FES_DECL_PAIR(fn_nmCmdListClose_003c6f10)
P3FES_DECL_PAIR(fn_nmCmdListCloseNow_003c6f50)
P3FES_DECL_PAIR(fn_nmCmdListVisibleRows_003c6f80)
P3FES_DECL_PAIR(fn_nmCmdListCursorLine_003c6fb0)
P3FES_DECL_PAIR(fn_nmCmdListSort_003c7000)
P3FES_DECL_PAIR(fn_sub_3C7070_003c7070)
P3FES_DECL_PAIR(fn_msgWinReset_003c7270)
P3FES_DECL_PAIR(fn_msgWinRecordInit_003c72a0)
P3FES_DECL_PAIR(fn_sub_3C72D0_003c72d0)
P3FES_DECL_PAIR(fn_msgWinSetStateFlags_003c7390)
P3FES_DECL_PAIR(fn_sub_3C73E0_003c73e0)
P3FES_DECL_PAIR(fn_msgWinRequestMessage_003c7430)
P3FES_DECL_PAIR(fn_sub_3C74E0_003c74e0)
P3FES_DECL_PAIR(fn_msgWinSetType_003c7560)
P3FES_DECL_PAIR(fn_msgWinGetSelection_003c75b0)
P3FES_DECL_PAIR(fn_msgWinLastSelection_003c7610)
P3FES_DECL_PAIR(fn_msgWinClose_003c7650)
P3FES_DECL_PAIR(fn_sub_3C7700_003c7700)
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

// --- guest layout ------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01900000u;      // the random records of a case
constexpr u32 kWorldLen = 0x10000u;
constexpr u32 kHeapBlock = 0x01920000u;  // what the RwHeapMalloc stand-in hands out
constexpr u32 kHeapLen = 0x2000u;
constexpr u32 kMallocSlot = 0x960178u;   // RwEngineInstance memory functions: malloc, free
constexpr u32 kFreeSlot = 0x96017Cu;
constexpr u32 kGpWord = kGp - 18968u;    // the word the non-leaf callback returns
constexpr u32 kMsgRec = 0x95BE90u;       // the shared message-window record
constexpr u32 kSlotTable = 0x959EECu;    // itfMesMng slot table: the current handle of slot i at + 52 * i
constexpr u32 kPad = 0x7E094Cu;          // the pad words sub_3C63F0 reads (16 bytes)
constexpr u32 kFadeTable = 0x7BB4C0u;    // sub_3C69D0's jump table

// Callbacks of the emitted set (tests/game/CMakeLists.txt lists them).
constexpr u32 kRet0 = 0x3C4400u;      // `v0 = 0` (the nmlist default callbacks)
constexpr u32 kIdentity = 0x489950u;  // `v0 = a0`
constexpr u32 kSecond = 0x4B3710u;    // `v0 = a1`
constexpr u32 kOne = 0x469A90u;       // `v0 = 1`
constexpr u32 kNonLeaf = 0x1F1C50u;   // spills $ra below its $sp, returns the word at gp-18968

// --- guest RAM helpers -----------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();
    return (hi << 32) | rng();
}
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
// A 32-bit register value, sometimes with garbage in the upper half (the functions compare whole registers).
u64 reg_of(u32 v, std::mt19937& rng) { return chance(rng, 10) ? (rng64(rng) & 0xFFFFFFFF00000000ull) | v : sx(v); }
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 8) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 2001) - 1000) / 997.0f);
    }
}

// --- the pair: trampolines that randomise the FPU / HI / LO and catch a fatal event ----------------------------------
struct RunExtra {
    bool fatal = false;
    u32 pc = 0;
    std::string what;
    std::array<u32, 32> fpr{};
    u32 acc = 0, fcr31 = 0;
};
Fn g_fn[2] = {};
RunExtra g_extra[2];
u32 g_seed = 0;
std::map<unsigned, u32> g_fpr_in;
int g_pairs = 0;
std::map<std::string, std::pair<int, int>> g_tally;  // label -> (pairs, pairs stopped by a fatal event)

template <int K>
void trampoline(EEContext& c) {
    std::mt19937 r{g_seed ^ 0x5BD1E995u};
    for (u32& f : c.fpr) f = rand_float(r);
    for (const auto& [i, v] : g_fpr_in) c.fpr[i] = v;
    c.acc = rand_float(r);
    c.fcr31 = r() & 0x0083F078u;
    c.hi.u64[0] = rng64(r);
    c.hi.u64[1] = rng64(r);
    c.lo.u64[0] = rng64(r);
    c.lo.u64[1] = rng64(r);
    RunExtra& x = g_extra[K];
    x = RunExtra{};
    try {
        g_fn[K](c);
    } catch (const rt_test::FatalEvent& e) {
        x.fatal = true;
        x.pc = e.pc;
        x.what = e.what;
        // a memory fault names the host return address inside the body that faulted: the only part that may differ
        const std::size_t host = x.what.find("; host return address");
        if (host != std::string::npos) x.what.resize(host);
    }
    std::copy(std::begin(c.fpr), std::end(c.fpr), x.fpr.begin());
    x.acc = c.acc;
    x.fcr31 = c.fcr31;
}

struct Result {
    u64 v0 = 0;
    bool fatal = false;
    std::string what;
    std::array<u32, 32> fpr{};
};

// Runs hand and recomp from the same machine (RAM restored in between) and requires identical results everywhere.
// After the pair the recompiled run's output is in place.
Result pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::map<unsigned, u64> gpr_in = {},
            std::map<unsigned, u32> fpr_in = {}) {
    g_fn[0] = hand;
    g_fn[1] = recomp;
    g_seed = seed;
    g_fpr_in = std::move(fpr_in);
    HwCheck hw;
    hw.ranges = {{0, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in = std::move(gpr_in);
    const HwPair p = run_pair_hw(m, &trampoline<0>, &trampoline<1>, args, seed, what, hw);
    INFO(what);
    const RunExtra& a = g_extra[0];
    const RunExtra& b = g_extra[1];
    CHECK(a.fatal == b.fatal);
    CHECK(a.pc == b.pc);
    CHECK(a.what == b.what);
    CHECK(a.fpr == b.fpr);
    CHECK(a.acc == b.acc);
    CHECK(a.fcr31 == b.fcr31);
    ++g_pairs;
    auto& t = g_tally[what];
    ++t.first;
    if (b.fatal) ++t.second;
    return Result{p.recomp.base.v0, b.fatal, b.what, b.fpr};
}

// --- world builders --------------------------------------------------------------------------------------------------
struct World {
    Machine& m;
    std::mt19937& rng;
    u32 next = kWorld;

    World(Machine& mm, std::mt19937& r) : m(mm), rng(r) {
        std::memset(m.at(kWorld), 0, kWorldLen);
        for (u32 i = 0; i < kHeapLen; i += 4) w32(m, kHeapBlock + i, rng());
        w32(m, kMallocSlot, kNonLeaf);
        w32(m, kFreeSlot, chance(rng, 80) ? kRet0 : kIdentity);
        w32(m, kGpWord, kHeapBlock);
        for (u32 i = 0; i < 16; i += 2) w16(m, kPad + i, 0);
        std::memset(m.at(0), 0, 0x200);  // the retail null-pointer paths write here
    }
    u32 alloc(u32 n) {
        const u32 a = next;
        next += (n + 15u) & ~15u;
        REQUIRE(next <= kWorld + kWorldLen);
        return a;
    }
    u32 cb() { return pick(rng, {kRet0, kRet0, kIdentity, kSecond, kOne, kNonLeaf}); }
    u32 small_key() { return chance(rng, 85) ? rng() % 8 : rng(); }

    // `n` nodes of `psize` payload bytes, linked; payload pointer node + 24 (0 without a payload)
    std::vector<u32> chain(unsigned n, u32 psize) {
        std::vector<u32> v;
        for (unsigned i = 0; i < n; ++i) {
            const u32 a = alloc(24 + psize);
            w32(m, a + 0, small_key());
            w32(m, a + 4, small_key());
            w32(m, a + 8, 24 + psize);
            w32(m, a + 20, psize ? a + 24 : 0);
            for (u32 k = 0; k < psize; k += 4) w32(m, a + 24 + k, rng() % 4 ? rng() % 16 : rng());
            v.push_back(a);
        }
        for (unsigned i = 0; i < n; ++i) {
            w32(m, v[i] + 12, i ? v[i - 1] : 0);
            w32(m, v[i] + 16, i + 1 < n ? v[i + 1] : 0);
        }
        return v;
    }
    u32 any_of(const std::vector<u32>& v) { return v.empty() || chance(rng, 15) ? 0 : v[rng() % v.size()]; }
    // a list header: head, tail, cursor, count, flags (sometimes inconsistent)
    void header(u32 h, const std::vector<u32>& v) {
        w32(m, h + 0, v.empty() ? 0 : v.front());
        w32(m, h + 4, v.empty() ? 0 : v.back());
        w32(m, h + 8, pick(rng, {0, 1, 2}) == 0 ? 0 : any_of(v));
        w16(m, h + 12, static_cast<u16>(chance(rng, 10) ? rng() % 12 : v.size()));
        w16(m, h + 14, static_cast<u16>(chance(rng, 10) ? rng() : rng() % 4));
    }
    // a list object with `n` nodes; payload of `psize` (+36 = obj + 40)
    u32 object(unsigned n, u32 node_psize, u32 psize, std::vector<u32>* nodes = nullptr) {
        const u32 obj = alloc(40 + psize);
        const std::vector<u32> v = chain(n, node_psize);
        header(obj + 4, v);
        w32(m, obj + 20, cb());
        w32(m, obj + 24, cb());
        w32(m, obj + 28, cb());
        w32(m, obj + 32, 40 + psize);
        w32(m, obj + 36, obj + 40);
        if (nodes) *nodes = v;
        return obj;
    }
    // a NUL-terminated string of up to 15 random bytes
    u32 string() {
        const u32 a = alloc(32);
        const unsigned len = rng() % 16;
        for (unsigned i = 0; i < len; ++i) w8(m, a + i, static_cast<u8>(1 + rng() % 255));
        return a;
    }
    // an nmCmdList: rows with payload {x, y, highlight, number, colour, .., user}; the window state in obj + 40
    u32 cmdlist(unsigned n, std::vector<u32>* rows_out = nullptr) {
        std::vector<u32> rows;
        const u32 obj = object(n, 32, 72, &rows);
        for (unsigned i = 0; i < rows.size(); ++i) {
            const u32 p = rows[i] + 24;
            w32(m, p + 8, chance(rng, 20) ? rng() | 1 : 0);
            w32(m, p + 12, chance(rng, 10) ? rng() % 12 : i + 1);
        }
        if (chance(rng, 75)) {  // the cmdlist callbacks
            w32(m, obj + 20, 0x3C60C0u);
            w32(m, obj + 24, 0x3C60F0u);
            w32(m, obj + 28, chance(rng, 50) ? 0x3C6120u : cb());
        }
        const u32 win = obj + 40;
        u32 flags = rng();
        if (chance(rng, 50)) flags &= 0x0071FFFFu;
        w32(m, win + 0, flags);
        w16(m, win + 4, static_cast<u16>(static_cast<s32>(rng() % 9) - 1));
        w16(m, win + 6, static_cast<u16>(pick(rng, {0, 1, 5, 5, 7, 0xFFFF})));
        w16(m, win + 8, static_cast<u16>(pick(rng, {0, 2, 5, 5, 9, 0xFFFE})));
        w16(m, win + 10, static_cast<u16>(chance(rng, 90) ? rng() % 7 : rng()));
        w32(m, win + 12, rng() % 40);
        w32(m, win + 16, chance(rng, 80) ? n : rng() % 10);
        w32(m, win + 20, rng() % 640);
        w32(m, win + 24, rng() % 448);
        w32(m, win + 28, rng() % 256);
        w32(m, win + 32, chance(rng, 90) ? rng() % 8 : pick(rng, {0xFFFFFFFFu, 0xFFFFFFFBu, 100u}));  // rows (loop bounds)
        w32(m, win + 44, chance(rng, 90) && !rows.empty() ? rows[rng() % rows.size()] : 0);
        for (u32 k = 48; k <= 64; k += 4) w32(m, win + k, cb());
        w32(m, win + 68, win + 72);
        if (rows_out) *rows_out = rows;
        return obj;
    }
    // an nmSequence: active steps in the object's list, pending (+16) and finished (+32) lists in the payload
    u32 sequence(std::vector<u32>* steps = nullptr) {
        std::vector<u32> active, pending, finished;
        const u32 obj = object(0, 0, 48 + 16);
        auto steps_of = [&](unsigned n) {
            std::vector<u32> v = chain(n, 64);
            for (u32 s : v) {
                const u32 p = s + 24;
                w32(m, p + 0, small_key());
                w32(m, p + 20, rng() % 16);
                for (u32 k = 24; k <= 36; k += 4) w32(m, p + k, cb());
                w16(m, p + 44, static_cast<u16>(rng() % 3));
                w16(m, p + 46, static_cast<u16>(rng() % 3));
            }
            return v;
        };
        active = steps_of(rng() % 4);
        pending = steps_of(rng() % 4);
        finished = steps_of(rng() % 4);
        header(obj + 4, active);
        const u32 pay = obj + 40;
        w32(m, pay + 0, rng() % 4);
        w32(m, pay + 8, cb());
        header(pay + 16, pending);
        header(pay + 32, finished);
        if (steps) {
            *steps = active;
            steps->insert(steps->end(), pending.begin(), pending.end());
        }
        return obj;
    }
    // the message-window record and the itfMesMng slot table (slots 0..3 with handle blocks)
    void msgwin() {
        w32(m, kMsgRec + 0, chance(rng, 30) ? 0xFFFFFFFFu : chance(rng, 80) ? rng() % 4 : rng());
        w8(m, kMsgRec + 4, static_cast<u8>(rng()));
        w8(m, kMsgRec + 5, static_cast<u8>(rng()));
        w32(m, kMsgRec + 8, rng());
        w8(m, kMsgRec + 12, static_cast<u8>(rng()));
        w8(m, kMsgRec + 13, static_cast<u8>(rng()));
        for (u32 s = 0; s < 4; ++s) {
            u32 h = 0;
            if (chance(rng, 80)) {
                h = alloc(488);
                for (u32 k = 0; k < 488; k += 4) w32(m, h + k, rng() % 3 ? rng() % 64 : rng());
            }
            w32(m, kSlotTable + 52 * s, h);
        }
    }
    void pads() {
        for (u32 i = 0; i < 16; i += 2) w16(m, kPad + i, static_cast<u16>(chance(rng, 40) ? 1u << (rng() % 16) : chance(rng, 50) ? rng() : 0));
    }
};

// The argument registers of a call; the ones a function does not take hold garbage, as at a real call site (a body
// that leaves one of them behind must leave the original's value).
constexpr u64 kUnused = 0x5EED5EED5EED5EEDull;
std::mt19937_64 g_garbage{0x6A3DE8u};
Args args4(u64 a0, u64 a1 = kUnused, u64 a2 = kUnused, u64 a3 = kUnused) {
    Args a{a0, a1, a2, a3};
    for (u64& x : a)
        if (x == kUnused) x = g_garbage();
    return a;
}

// =====================================================================================================================
// [nmlist]
// =====================================================================================================================

TEST_CASE("game(nm_message): the node-list primitives equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 1300; ++i) {
        const u32 seed = seed_of(i, 0x11u);
        std::mt19937 rng{seed};
        World w(m, rng);
        std::vector<u32> nodes;
        const u32 obj = w.object(rng() % 6, chance(rng, 70) ? 8 : 0, 16, &nodes);
        const u32 list = chance(rng, 95) ? obj + 4 : 0;
        const u32 node = w.any_of(nodes);
        const std::vector<u32> extra = w.chain(1, 8);
        const u32 fresh = chance(rng, 90) ? extra[0] : 0;
        const u32 o = chance(rng, 95) ? obj : 0;
        const u64 key = reg_of(w.small_key(), rng);
        switch (i % 13) {
        case 0: pair(m, PAIR(fn_nmListInsertAfter_003c4710), args4(sx(list), sx(w.any_of(nodes)), sx(fresh)), seed, "nmListInsertAfter insert"); break;
        case 1: pair(m, PAIR(fn_nmListUnlink_003c4820), args4(sx(list), sx(chance(rng, 95) ? node : 0)), seed, "nmListUnlink unlink"); break;
        case 2: pair(m, PAIR(fn_nmListFindByKey_003c4b50), args4(sx(o), sx(list), key), seed, "nmListFindByKey find key"); break;
        case 3: pair(m, PAIR(fn_nmListFindByWord4_003c4bf0), args4(sx(o), sx(list), key), seed, "nmListFindByWord4 find word 4"); break;
        case 4: pair(m, PAIR(fn_nmListCursorNext_003c4c80), args4(sx(o), sx(list)), seed, "nmListCursorNext cursor next"); break;
        case 5: pair(m, PAIR(fn_nmListCursorPrev_003c4d20), args4(sx(o), sx(list)), seed, "nmListCursorPrev cursor prev"); break;
        case 6: pair(m, PAIR(fn_nmListCursorClearEnd_003c4dc0), args4(sx(o), sx(list)), seed, "nmListCursorClearEnd clear end"); break;
        case 7: pair(m, PAIR(fn_sub_3C4DE0_003c4de0), args4(sx(o), sx(obj + 4), sx(node)), seed, "sub_3C4DE0 cursor set"); break;
        case 8: {
            const u64 idx = chance(rng, 20) ? ~0ull : chance(rng, 10) ? reg_of(rng() % 8, rng) : sx(rng() % 8);
            pair(m, PAIR(fn_nmListCursorSeek_003c4df0), args4(sx(o), sx(obj + 4), idx), seed, "nmListCursorSeek seek");
            break;
        }
        case 9: pair(m, PAIR(fn_nmListCursorHead_003c4e50), args4(sx(o), sx(obj + 4)), seed, "nmListCursorHead head"); break;
        case 10: pair(m, PAIR(fn_sub_3C4E60_003c4e60), args4(sx(o), sx(obj + 4)), seed, "sub_3C4E60 tail"); break;
        case 11: pair(m, PAIR(fn_nmByteSum_003c4f80), args4(sx(w.string())), seed, "nmByteSum byte sum"); break;
        case 12: {
            const u32 arr = w.alloc(32);
            const unsigned n = rng() % 6;
            for (unsigned k = 0; k < n; ++k) w32(m, arr + 4 * k, chance(rng, 90) ? w.chain(1, 0)[0] : 0);
            pair(m, PAIR(fn_nmListRebuild_003c50b0), args4(sx(obj), sx(chance(rng, 90) ? arr : 0), chance(rng, 10) ? reg_of(n, rng) : sx(n)),
                 seed, "nmListRebuild rebuild");
            break;
        }
        }
    }
}

TEST_CASE("game(nm_message): the list-object calls (append, filtered removal, sorted insert) equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 600; ++i) {
        const u32 seed = seed_of(i, 0x22u);
        std::mt19937 rng{seed};
        World w(m, rng);
        std::vector<u32> nodes;
        const u32 obj = w.object(rng() % 6, 8, 16, &nodes);
        switch (i % 3) {
        case 0: {
            const u32 size = pick(rng, {0, 4, 16, 40});
            pair(m, PAIR(fn_nmListAppendNew_003c4910), args4(sx(chance(rng, 95) ? obj : 0), reg_of(chance(rng, 50) ? 0 : w.small_key(), rng), sx(size)),
                 seed, "nmListAppendNew append");
            break;
        }
        case 1: pair(m, PAIR(fn_nmListRemoveFiltered_003c4e70), args4(sx(obj)), seed, "nmListRemoveFiltered filtered removal"); break;
        case 2: {
            const u32 node = w.chain(1, 0)[0];
            pair(m, PAIR(fn_sub_3C53E0_003c53e0), args4(sx(obj + 4), sx(w.small_key()), sx(node)), seed, "sub_3C53E0 sorted insert");
            break;
        }
        }
    }
}

TEST_CASE("game(nm_message): documented rules of the node list") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{7};
    // nmByteSum: the signed byte sum
    for (int i = 0; i < 50; ++i) {
        World w(m, rng);
        const u32 s = w.string();
        s32 sum = 0;
        for (u32 k = 0; m.at(s)[k]; ++k) sum += static_cast<s8>(m.at(s)[k]);
        const Result r = pair(m, PAIR(fn_nmByteSum_003c4f80), args4(sx(s)), 1000 + i, "byte sum rule");
        CHECK(static_cast<s32>(r.v0) == sum);
    }
    // insert at the head of an empty list, then after it; unlink returns the neighbour
    {
        World w(m, rng);
        const u32 hdr = w.alloc(16);
        const std::vector<u32> n = w.chain(2, 0);
        for (u32 x : n) {
            w32(m, x + 12, 0xDEAD);
            w32(m, x + 16, 0xBEEF);
        }
        pair(m, PAIR(fn_nmListInsertAfter_003c4710), args4(sx(hdr), 0, sx(n[0])), 2000, "insert first");
        CHECK(r32(m, hdr) == n[0]);
        CHECK(r32(m, hdr + 4) == n[0]);
        CHECK(r32(m, hdr + 8) == n[0]);
        CHECK(r16(m, hdr + 12) == 1);
        pair(m, PAIR(fn_nmListInsertAfter_003c4710), args4(sx(hdr), sx(n[0]), sx(n[1])), 2001, "insert after");
        CHECK(r32(m, hdr + 4) == n[1]);
        CHECK(r32(m, n[0] + 16) == n[1]);
        CHECK(r32(m, n[1] + 12) == n[0]);
        CHECK(r32(m, n[1] + 16) == 0);
        const Result r = pair(m, PAIR(fn_nmListUnlink_003c4820), args4(sx(hdr), sx(n[0])), 2002, "unlink head");
        CHECK(r.v0 == n[1]);
        CHECK(r32(m, hdr) == n[1]);
        CHECK(r16(m, hdr + 12) == 1);
        const Result r2 = pair(m, PAIR(fn_nmListUnlink_003c4820), args4(sx(hdr), sx(n[1])), 2003, "unlink last");
        CHECK(r2.v0 == 0);
        CHECK(r32(m, hdr) == 0);
        CHECK(r32(m, hdr + 4) == 0);
    }
    // the cursor wraps once at the tail, then stops until the end flag is cleared
    {
        World w(m, rng);
        const u32 hdr = w.alloc(16);
        const std::vector<u32> n = w.chain(3, 0);
        w32(m, hdr, n[0]);
        w32(m, hdr + 4, n[2]);
        w32(m, hdr + 8, n[2]);
        w16(m, hdr + 12, 3);
        w16(m, hdr + 14, 0);
        CHECK(pair(m, PAIR(fn_nmListCursorNext_003c4c80), args4(1, sx(hdr)), 2010, "wrap").v0 == n[0]);
        CHECK((r16(m, hdr + 14) & 2) != 0);
        w32(m, hdr + 8, n[2]);
        CHECK(pair(m, PAIR(fn_nmListCursorNext_003c4c80), args4(1, sx(hdr)), 2011, "no second wrap").v0 == 0);
        pair(m, PAIR(fn_nmListCursorClearEnd_003c4dc0), args4(1, sx(hdr)), 2012, "clear end");
        CHECK((r16(m, hdr + 14) & 2) == 0);
        CHECK(pair(m, PAIR(fn_nmListCursorPrev_003c4d20), args4(1, sx(hdr)), 2013, "prev").v0 == n[1]);
    }
}

// =====================================================================================================================
// [nmSequence]
// =====================================================================================================================

TEST_CASE("game(nm_message): the nmSequence functions equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 1120; ++i) {
        const u32 seed = seed_of(i, 0x33u);
        std::mt19937 rng{seed};
        World w(m, rng);
        std::vector<u32> steps;
        const u32 seq = w.sequence(&steps);
        const u32 step = w.any_of(steps);
        w32(m, kGpWord, pick(rng, {kRet0, kRet0, 0, kOne, kHeapBlock}));
        switch (i % 14) {
        case 0: pair(m, PAIR(fn_sub_3C5490_003c5490), args4(sx(chance(rng, 97) ? seq : 0)), seed, "sub_3C5490 update"); break;
        case 1: pair(m, PAIR(fn_nmSequenceCallAll36_003c5760), args4(sx(chance(rng, 97) ? seq : 0)), seed, "nmSequenceCallAll36 call all"); break;
        case 2: pair(m, PAIR(fn_sub_3C57E0_003c57e0), args4(sx(seq), sx(step)), seed, "sub_3C57E0"); break;
        case 3: pair(m, PAIR(fn_nmSeqStepOnRemove_003c5810), args4(sx(seq), sx(step)), seed, "nmSeqStepOnRemove"); break;
        case 4: pair(m, PAIR(fn_nmSeqStepRun_003c5840), args4(sx(seq), sx(step)), seed, "nmSeqStepRun"); break;
        case 5: pair(m, PAIR(fn_nmSeqStepCall36_003c5870), args4(sx(seq), sx(step)), seed, "nmSeqStepCall36"); break;
        case 6: {
            w32(m, kGpWord, kHeapBlock);
            const u32 desc = w.alloc(48);
            for (u32 k = 0; k < 16; k += 4) w32(m, desc + k, w.cb());
            w32(m, desc + 16, pick(rng, {0, 0, 8, 32}));
            const unsigned len = rng() % 16;
            for (unsigned k = 0; k < len; ++k) w8(m, desc + 20 + k, static_cast<u8>(1 + rng() % 255));
            const u64 delay = sx(rng() % 4), life = sx(rng() % 4);
            pair(m, PAIR(fn_nmSequenceAddStep_003c5240),
                 args4(sx(chance(rng, 97) ? seq : 0), reg_of(chance(rng, 95) ? 1 + rng() % 9 : 0, rng), sx(chance(rng, 97) ? desc : 0), delay), seed,
                 "nmSequenceAddStep add step", {{GPR_T0, life}});
            break;
        }
        case 7: {
            w32(m, kGpWord, kHeapBlock);
            pair(m, PAIR(fn_nmSequenceCreate_003c5180), args4(sx(chance(rng, 70) ? w.cb() : 0), sx(pick(rng, {0, 0, 16, 64}))), seed, "nmSequenceCreate create");
            break;
        }
        case 8: {
            std::vector<u32> nodes;
            const u32 obj = w.object(rng() % 4, 8, 16, &nodes);
            pair(m, PAIR(fn_nmSequenceDestroy_003c5220), args4(sx(chance(rng, 95) ? obj : 0)), seed, "nmSequenceDestroy destroy");
            break;
        }
        case 9: pair(m, PAIR(fn_nmObjPayloadWord12_003c5460), args4(sx(seq)), seed, "nmObjPayloadWord12"); break;
        case 10: pair(m, PAIR(fn_sub_3C5470_003c5470), args4(sx(steps.empty() ? seq : steps[0])), seed, "sub_3C5470"); break;
        case 11: pair(m, PAIR(fn_nmNodePayloadArea40_003c5480), args4(sx(steps.empty() ? seq : steps[0])), seed, "nmNodePayloadArea40"); break;
        case 12: {
            pair(m, PAIR(fn_nmSeqNullStep_003c5170), args4(sx(seq)), seed, "nmSeqNullStep");
            pair(m, PAIR(fn_sub_3C5210_003c5210), args4(sx(seq)), seed + 1, "sub_3C5210");
            break;
        }
        case 13: {
            pair(m, PAIR(fn_nullsub_54_003c58c0), args4(sx(seq)), seed, "nullsub_54");
            pair(m, PAIR(fn_nullsub_55_003c58d0), args4(sx(seq)), seed + 1, "nullsub_55");
            pair(m, PAIR(fn_nullsub_56_003c58a0), args4(sx(seq)), seed + 2, "nullsub_56");
            pair(m, PAIR(fn_nullsub_57_003c58b0), args4(sx(seq)), seed + 3, "nullsub_57");
            pair(m, PAIR(fn_nullsub_58_003c58e0), args4(sx(seq)), seed + 4, "nullsub_58");
            break;
        }
        }
    }
}

TEST_CASE("game(nm_message): documented rules of nmSequence") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11};
    // a step whose delay ran out moves to the active list and loses flag bit 2; the walk then continues after the
    // unlinked step's successor (nmListUnlink returned it and the loop steps once more), so that successor is NOT counted
    // down on this frame -- a quirk of the original
    World w(m, rng);
    const u32 seq = w.object(0, 0, 64);
    const u32 pay = seq + 40;
    w32(m, seq + 20, kRet0);
    w32(m, seq + 24, kRet0);
    w32(m, seq + 28, kRet0);
    w32(m, pay + 0, 0);
    w32(m, pay + 8, kRet0);  // the sequence function: not finished
    const std::vector<u32> st = w.chain(2, 64);
    for (u32 s : st) {
        w32(m, s + 24 + 20, 0x4);
        for (u32 k = 24; k <= 36; k += 4) w32(m, s + 24 + k, kRet0);
        w16(m, s + 24 + 46, 2);
    }
    w16(m, st[0] + 24 + 44, 0);  // due
    w16(m, st[1] + 24 + 44, 3);  // waits
    w.header(pay + 16, st);
    w16(m, pay + 16 + 14, 0);
    w32(m, pay + 16 + 8, 0);
    w16(m, pay + 16 + 12, 2);
    const Result r = pair(m, PAIR(fn_sub_3C5490_003c5490), args4(sx(seq)), 3000, "sequence rule");
    CHECK(r.v0 == 0);
    CHECK(r32(m, seq + 4) == st[0]);                 // active
    CHECK((r32(m, st[0] + 24 + 20) & 0x4) == 0);     // no longer queued
    CHECK(r16(m, st[1] + 24 + 44) == 3);             // skipped this frame
    CHECK(r32(m, pay + 16) == st[1]);                // still pending
}

// =====================================================================================================================
// [nmCmdList]
// =====================================================================================================================

TEST_CASE("game(nm_message): the nmCmdList functions equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 2520; ++i) {
        const u32 seed = seed_of(i, 0x44u);
        std::mt19937 rng{seed};
        World w(m, rng);
        std::vector<u32> rows;
        const u32 obj = w.cmdlist(rng() % 7, &rows);
        const u32 row = w.any_of(rows);
        w.pads();
        w32(m, kGpWord, pick(rng, {kRet0, kHeapBlock}));
        const u64 o = sx(obj);
        switch (i % 42) {
        case 0: pair(m, PAIR(fn_sub_3C5AF0_003c5af0), args4(o), seed, "sub_3C5AF0 up"); break;
        case 1: pair(m, PAIR(fn_nmCmdListCursorDown_003c5bb0), args4(o), seed, "nmCmdListCursorDown down"); break;
        case 2: pair(m, PAIR(fn_sub_3C5C50_003c5c50), args4(o), seed, "sub_3C5C50 page down"); break;
        case 3: pair(m, PAIR(fn_nmCmdListSelect_003c5d40), args4(o, sx(row), reg_of(rng() % 8, rng)), seed, "nmCmdListSelect select"); break;
        case 4: pair(m, PAIR(fn_nmCmdListSetDrawFunc_003c5e20), args4(o, sx(chance(rng, 90) ? w.cb() : 0)), seed, "nmCmdListSetDrawFunc"); break;
        case 5: pair(m, PAIR(fn_nmCmdListSetUpdateFunc_003c5e80), args4(o, sx(chance(rng, 90) ? w.cb() : 0)), seed, "nmCmdListSetUpdateFunc"); break;
        case 6: pair(m, PAIR(fn_nmCmdListSetRowDrawFunc_003c5ee0), args4(o, sx(chance(rng, 90) ? w.cb() : 0)), seed, "nmCmdListSetRowDrawFunc"); break;
        case 7: pair(m, PAIR(fn_nmCmdListSetRowRemoveFunc_003c5f40), args4(o, sx(chance(rng, 90) ? w.cb() : 0)), seed, "nmCmdListSetRowRemoveFunc"); break;
        case 8: pair(m, PAIR(fn_nmCmdListRemoveRow_003c5fa0), args4(o, sx(rows.empty() ? 0 : rows[rng() % rows.size()])), seed, "nmCmdListRemoveRow remove row"); break;
        case 9: pair(m, PAIR(fn_nmCmdListOnInsert_003c60c0), args4(o, sx(rows.empty() ? obj : rows[0])), seed, "nmCmdListOnInsert"); break;
        case 10: pair(m, PAIR(fn_nmCmdListOnRemove_003c60f0), args4(o, sx(row)), seed, "nmCmdListOnRemove"); break;
        case 11: {
            const u32 r = rows.empty() ? obj : rows[rng() % rows.size()];
            if (!rows.empty() && chance(rng, 50)) {  // on screen, often highlighted (the sprite draw stops the run)
                w32(m, obj + 40 + 44, rows[0]);
                w32(m, rows[0] + 24 + 12, 1);
                w32(m, r + 24 + 12, 1 + static_cast<u32>(rng() % rows.size()));
                w32(m, obj + 40 + 32, 8);
                w32(m, r + 24 + 8, chance(rng, 40) ? 1 : 0);
            }
            pair(m, PAIR(fn_nmCmdListDrawRow_003c6120), args4(o, sx(r)), seed, "nmCmdListDrawRow draw row");
            break;
        }
        case 12: pair(m, PAIR(fn_nmCmdListUpdate_003c6270), args4(o), seed, "nmCmdListUpdate update"); break;
        case 13: pair(m, PAIR(fn_nmCmdListDraw_003c6380), args4(o), seed, "nmCmdListDraw draw"); break;
        case 14:
        case 15:
        case 16: pair(m, PAIR(fn_sub_3C63F0_003c63f0), args4(o), seed, "sub_3C63F0 input"); break;
        case 17: pair(m, PAIR(fn_nmCmdListStartFade_003c6900), args4(o), seed, "nmCmdListStartFade start fade"); break;
        case 18:
        case 19: pair(m, PAIR(fn_sub_3C69D0_003c69d0), args4(o), seed, "sub_3C69D0 fade step"); break;
        case 20: pair(m, PAIR(fn_nmCmdListScrollBar_003c6b70), args4(o), seed, "nmCmdListScrollBar scroll bar"); break;
        case 21: pair(m, PAIR(fn_nmCmdListDecidedRow_003c6c50), args4(o), seed, "nmCmdListDecidedRow"); break;
        case 22: pair(m, PAIR(fn_nmCmdListCancelled_003c6c80), args4(o), seed, "nmCmdListCancelled"); break;
        case 23: pair(m, PAIR(fn_nmCmdListPagedDown_003c6ca0), args4(o), seed, "nmCmdListPagedDown"); break;
        case 24: pair(m, PAIR(fn_nmCmdListMovedUp_003c6cc0), args4(o), seed, "nmCmdListMovedUp"); break;
        case 25: pair(m, PAIR(fn_nmCmdListMovedDownRow_003c6ce0), args4(o), seed, "nmCmdListMovedDownRow"); break;
        case 26: pair(m, PAIR(fn_nmCmdListScrolledRow_003c6d10), args4(o), seed, "nmCmdListScrolledRow"); break;
        case 27: pair(m, PAIR(fn_nmCmdListSetPosition_003c6d40), args4(o, reg_of(rng(), rng), reg_of(rng(), rng)), seed, "nmCmdListSetPosition"); break;
        case 28: pair(m, PAIR(fn_sub_3C6D60_003c6d60), args4(o, reg_of(1u << (rng() % 32), rng)), seed, "sub_3C6D60"); break;
        case 29: pair(m, PAIR(fn_nmCmdListStatus_003c6d80), args4(o), seed, "nmCmdListStatus status"); break;
        case 30: pair(m, PAIR(fn_nmCmdListStatus28_003c6e10), args4(o), seed, "nmCmdListStatus28 status"); break;
        case 31: pair(m, PAIR(fn_nmCmdListHold_003c6ea0), args4(o), seed, "nmCmdListHold"); break;
        case 32: pair(m, PAIR(fn_nmCmdListRelease_003c6ec0), args4(o), seed, "nmCmdListRelease"); break;
        case 33: pair(m, PAIR(fn_sub_3C6EE0_003c6ee0), args4(o), seed, "sub_3C6EE0"); break;
        case 34: pair(m, PAIR(fn_nmCmdListClose_003c6f10), args4(o), seed, "nmCmdListClose"); break;
        case 35: pair(m, PAIR(fn_nmCmdListCloseNow_003c6f50), args4(o), seed, "nmCmdListCloseNow"); break;
        case 36: pair(m, PAIR(fn_nmCmdListVisibleRows_003c6f80), args4(o), seed, "nmCmdListVisibleRows"); break;
        case 37: pair(m, PAIR(fn_nmCmdListCursorLine_003c6fb0), args4(o), seed, "nmCmdListCursorLine"); break;
        case 38: pair(m, PAIR(fn_nmCmdListSort_003c7000), args4(o, sx(w.cb())), seed, "nmCmdListSort sort"); break;
        case 39: {
            w32(m, kGpWord, kHeapBlock);
            pair(m, PAIR(fn_sub_3C58F0_003c58f0), args4(reg_of(rng() % 4, rng), sx(pick(rng, {0, 0, 16})), reg_of(rng() % 8, rng), reg_of(rng(), rng)),
                 seed, "sub_3C58F0 create");
            break;
        }
        case 40: {
            w32(m, kGpWord, kHeapBlock);
            const u32 name = chance(rng, 60) ? w.string() : 0;
            pair(m, PAIR(fn_nmCmdListAddRow_003c5a40), args4(o, reg_of(w.small_key(), rng), sx(pick(rng, {0, 0, 8, 24})), sx(name)), seed, "nmCmdListAddRow add row");
            break;
        }
        case 41: pair(m, PAIR(fn_nmCmdListDestroy_003c5a20), args4(chance(rng, 95) ? o : 0), seed, "nmCmdListDestroy destroy"); break;
        }
    }
}

TEST_CASE("game(nm_message): documented rules of nmCmdList") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 200; ++i) {
        const u32 seed = seed_of(i, 0x55u);
        std::mt19937 rng{seed};
        World w(m, rng);
        const u32 obj = w.cmdlist(rng() % 7);
        const u32 win = obj + 40;
        // nmCmdListVisibleRows: min(rows, count)
        const s32 rows = static_cast<s32>(r32(m, win + 32));
        const s32 count = r16(m, obj + 16);
        CHECK(static_cast<s32>(pair(m, PAIR(fn_nmCmdListVisibleRows_003c6f80), args4(sx(obj)), seed, "visible rows").v0) == std::min(rows, count));
        // nmCmdListStatus: the packed status word
        const u32 f = r32(m, win);
        u32 st = (f & 0x400 ? 0x80000000u : 0) | (f & 0x4 ? 0x40000000u : 0);
        st |= !(f & 0x2) ? 0x2u : (f & 0x100) ? 0x14u : (f & 0x80) ? 0xCu : 0x1u;
        CHECK(static_cast<u32>(pair(m, PAIR(fn_nmCmdListStatus_003c6d80), args4(sx(obj)), seed + 1, "status").v0) == st);
        CHECK(pair(m, PAIR(fn_nmCmdListStatus28_003c6e10), args4(sx(obj)), seed + 2, "status 28").v0 == (st & 0x0FFFFFFFu));
        // sub_3C69D0: a fade-in step sets alpha = 255 * frame / length
        w16(m, win + 10, 2);
        w16(m, win + 4, 1);
        w16(m, win + 6, 5);
        pair(m, PAIR(fn_sub_3C69D0_003c69d0), args4(sx(obj)), seed + 3, "fade in");
        CHECK(r32(m, win + 28) == 255u * 2 / 5);
        CHECK(r16(m, win + 4) == 2);
    }
}

TEST_CASE("game(nm_message): the quaternion slerp sub_3C7070 equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 300; ++i) {
        const u32 seed = seed_of(i, 0x66u);
        std::mt19937 rng{seed};
        World w(m, rng);
        const u32 q0 = w.alloc(16), q1 = w.alloc(16), out = w.alloc(16);
        const bool unit = chance(rng, 70);
        float a[4], b[4];
        for (int k = 0; k < 4; ++k) {
            a[k] = std::bit_cast<float>(rand_float(rng));
            b[k] = chance(rng, 30) ? a[k] : std::bit_cast<float>(rand_float(rng));
        }
        if (unit) {
            float na = 0, nb = 0;
            for (int k = 0; k < 4; ++k) na += a[k] * a[k], nb += b[k] * b[k];
            na = std::sqrt(na), nb = std::sqrt(nb);
            for (int k = 0; k < 4; ++k) {
                if (na > 0) a[k] /= na;
                if (nb > 0) b[k] /= nb;
            }
        }
        for (int k = 0; k < 4; ++k) {
            w32(m, q0 + 4 * k, std::bit_cast<u32>(a[k]));
            w32(m, q1 + 4 * k, std::bit_cast<u32>(b[k]));
        }
        const u32 t = std::bit_cast<u32>(static_cast<float>(rng() % 1001) / 1000.0f);
        pair(m, PAIR(fn_sub_3C7070_003c7070), args4(sx(out), sx(q0), sx(q1)), seed, "sub_3C7070 slerp", {}, {{12, t}});
    }
}

// =====================================================================================================================
// [msgwin]
// =====================================================================================================================

TEST_CASE("game(nm_message): the message-window helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 960; ++i) {
        const u32 seed = seed_of(i, 0x77u);
        std::mt19937 rng{seed};
        World w(m, rng);
        w.msgwin();
        const u64 arg = reg_of(chance(rng, 50) ? 1u << (rng() % 32) : rng() % 8, rng);
        switch (i % 12) {
        case 0: pair(m, PAIR(fn_msgWinReset_003c7270), args4(arg), seed, "msgWinReset"); break;
        case 1: pair(m, PAIR(fn_msgWinRecordInit_003c72a0), args4(chance(rng, 90) ? sx(kMsgRec) : 0), seed, "msgWinRecordInit"); break;
        case 2: pair(m, PAIR(fn_sub_3C72D0_003c72d0), args4(sx(w.alloc(64))), seed, "sub_3C72D0 open"); break;
        case 3: pair(m, PAIR(fn_msgWinSetStateFlags_003c7390), args4(arg), seed, "msgWinSetStateFlags"); break;
        case 4: pair(m, PAIR(fn_sub_3C73E0_003c73e0), args4(arg), seed, "sub_3C73E0"); break;
        case 5: pair(m, PAIR(fn_msgWinRequestMessage_003c7430), args4(arg), seed, "msgWinRequestMessage request"); break;
        case 6: pair(m, PAIR(fn_sub_3C74E0_003c74e0), args4(arg), seed, "sub_3C74E0 selection"); break;
        case 7: pair(m, PAIR(fn_msgWinSetType_003c7560), args4(arg), seed, "msgWinSetType"); break;
        case 8: pair(m, PAIR(fn_msgWinGetSelection_003c75b0), args4(arg), seed, "msgWinGetSelection"); break;
        case 9: pair(m, PAIR(fn_msgWinLastSelection_003c7610), args4(arg), seed, "msgWinLastSelection"); break;
        case 10: pair(m, PAIR(fn_msgWinClose_003c7650), args4(arg), seed, "msgWinClose close"); break;
        case 11: pair(m, PAIR(fn_sub_3C7700_003c7700), args4(arg), seed, "sub_3C7700 close all"); break;
        }
    }
    // documented: msgWinReset resets the record
    std::mt19937 rng{3};
    World w(m, rng);
    w.msgwin();
    pair(m, PAIR(fn_msgWinReset_003c7270), args4(0), 4000, "record reset");
    CHECK(r32(m, kMsgRec) == 0xFFFFFFFFu);
    CHECK(*m.at(kMsgRec + 4) == 0);
    CHECK(*m.at(kMsgRec + 5) == 0);
    CHECK(r32(m, kMsgRec + 8) == 0xFFFFFFFFu);
    CHECK(*m.at(kMsgRec + 12) == 1);
    CHECK(*m.at(kMsgRec + 13) == 1);
    // without a handle the getters answer -1 / the stored byte, and the requests 0
    w32(m, kMsgRec, 0xFFFFFFFFu);
    CHECK(pair(m, PAIR(fn_msgWinGetSelection_003c75b0), args4(0), 4001, "no handle").v0 == ~0ull);
    CHECK(pair(m, PAIR(fn_msgWinRequestMessage_003c7430), args4(3), 4002, "no handle request").v0 == 0);
}

// =====================================================================================================================
// Real snapshots: the message-window record and the three live nm list objects of the replay routes
// =====================================================================================================================

TEST_CASE("game(nm_message): real snapshots of the three replay routes") {
    namespace fs = std::filesystem;
    const fs::path root = fs::path(elf_path()).parent_path().parent_path() / "_ours";
    const char* snaps[] = {"battle_ref_6150", "b_5800", "dorm_replay_4900", "v_m1"};
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    int used = 0;
    for (const char* s : snaps) {
        const fs::path p = root / s / "eeMemory.bin";
        std::ifstream f(p, std::ios::binary);
        if (!f) continue;
        f.read(reinterpret_cast<char*>(m.mem.main_ram()), EEMemory::kMainRamSize);
        if (f.gcount() != static_cast<std::streamsize>(EEMemory::kMainRamSize)) continue;
        ++used;
        // the live list objects: the default callbacks 0x3C4400 / 0x3C4410 / 0x3C4420 at +20
        std::vector<u32> objs;
        for (u32 a = 0x100000u; a + 32 < EEMemory::kMainRamSize; a += 4)
            if (r32(m, a + 20) == kRet0 && r32(m, a + 24) == 0x3C4410u && r32(m, a + 28) == 0x3C4420u) objs.push_back(a);
        MESSAGE(std::string(s) << ": " << objs.size() << " live nm list objects, message-window handle " << static_cast<s32>(r32(m, kMsgRec)));
        const std::vector<u8> ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (int i = 0; i < 24; ++i) {
            std::memcpy(m.mem.main_ram(), ram.data(), ram.size());
            const u32 seed = seed_of(i, 0x88u ^ static_cast<u32>(used));
            std::mt19937 rng{seed};
            const u32 obj = objs.empty() ? 0 : objs[rng() % objs.size()];
            // the real record and slot table (the window code past the first deep callee stops the run)
            switch (i % 8) {
            case 0: pair(m, PAIR(fn_msgWinGetSelection_003c75b0), args4(0), seed, "real: msgWinGetSelection"); break;
            case 1: pair(m, PAIR(fn_msgWinLastSelection_003c7610), args4(0), seed, "real: msgWinLastSelection"); break;
            case 2: pair(m, PAIR(fn_sub_3C74E0_003c74e0), args4(sx(rng() % 4)), seed, "real: sub_3C74E0"); break;
            case 3: pair(m, PAIR(fn_msgWinSetStateFlags_003c7390), args4(sx(1u << (16 + rng() % 16))), seed, "real: msgWinSetStateFlags"); break;
            case 4: pair(m, PAIR(fn_msgWinClose_003c7650), args4(sx(rng() % 2)), seed, "real: msgWinClose"); break;
            case 5: {  // append to a live list (the RwHeapMalloc slot handed the stand-in) and walk it
                if (!obj) break;
                w32(m, kMallocSlot, kNonLeaf);
                w32(m, kFreeSlot, kRet0);
                w32(m, kGpWord, kHeapBlock);
                pair(m, PAIR(fn_nmListAppendNew_003c4910), args4(sx(obj), sx(rng() % 4), sx(16)), seed, "real: nmListAppendNew");
                pair(m, PAIR(fn_nmListCursorNext_003c4c80), args4(sx(obj), sx(obj + 4)), seed + 1, "real: nmListCursorNext");
                pair(m, PAIR(fn_nmListFindByKey_003c4b50), args4(sx(obj), sx(obj + 4), sx(rng() % 4)), seed + 2, "real: nmListFindByKey");
                pair(m, PAIR(fn_nmListRemoveFiltered_003c4e70), args4(sx(obj)), seed + 3, "real: nmListRemoveFiltered");
                break;
            }
            case 6:
                if (obj) pair(m, PAIR(fn_nmListCursorSeek_003c4df0), args4(sx(obj), sx(obj + 4), sx(rng() % 3)), seed, "real: nmListCursorSeek");
                break;
            case 7: pair(m, PAIR(fn_sub_3C72D0_003c72d0), args4(sx(0x01900000u)), seed, "real: sub_3C72D0"); break;
            }
        }
    }
    if (used == 0) MESSAGE("SKIP: no replay snapshot under " << root.string());
}

TEST_CASE("game(nm_message): pair count") {
    MESSAGE("nm_message pairs run: " << g_pairs);
    std::string s;
    for (const auto& [k, v] : g_tally)
        if (v.second) s += k + " " + std::to_string(v.second) + "/" + std::to_string(v.first) + "; ";
    MESSAGE("stopped at a callee left out of the test build (label fatal/pairs): " << s);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
