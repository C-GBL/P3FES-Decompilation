// Phase 5 pair tests for the menu/UI second wave (game/src/ui/ui2.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved registers,
// the arena, the caller's live stack, virtual cycles, check-point count) on randomised inputs and edge cases.
// On top of the harness every pair compares the guest windows the functions write (the $gp area, g_data.c's
// gGlobalWork with the flag and counter arrays, the itemtbl section pointers, the RenderWare random state),
// $f0 and pipe 0 of HI/LO. Two paths end in a function this test build does not emit (printf for flag 0x1376,
// the debug-log formatter for a zero-length date range): there both bodies must reach the same
// missing-function stop with the same memory, cycles, check points and argument. A few documented rules
// (docs/ANALYSIS/20_menu_ui.md) are checked on the host, independently of both bodies, and the real
// DATA/EVENT/ITEMTBL.BIN drives the section slicer and its lookups when the extracted tree is beside the ELF.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/ui2.h"

#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
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
P3FES_DECL_PAIR(fn_H_Cursor_GetShouldDraw_00100570)
P3FES_DECL_PAIR(fn_sprFileIsReady_00111f30)
P3FES_DECL_PAIR(fn_H_Camp_GetRootSelection_0011b9a0)
P3FES_DECL_PAIR(fn_H_DayPartsDraw_IsIdle_00184d90)
P3FES_DECL_PAIR(fn_kwlnTaskGetTimer_00195520)
P3FES_DECL_PAIR(fn_kwlnTaskSetWorkData_00195530)
P3FES_DECL_PAIR(fn_kwlnTaskGetWorkData_00195540)
P3FES_DECL_PAIR(fn_sub_17D800_0017d800)
P3FES_DECL_PAIR(fn_sub_17D810_0017d810)
P3FES_DECL_PAIR(fn_sub_17D820_0017d820)
P3FES_DECL_PAIR(fn_H_Memcard_ClearChkAreaSeq_00191240)
P3FES_DECL_PAIR(fn_sub_25A110_0025a110)
P3FES_DECL_PAIR(fn_sub_25A120_0025a120)
P3FES_DECL_PAIR(fn_sprGetSpriteWidth_001126b0)
P3FES_DECL_PAIR(fn_sprGetSpriteHeight_00112740)
P3FES_DECL_PAIR(fn_sub_16EF40_0016ef40)
P3FES_DECL_PAIR(fn_sub_16EF50_0016ef50)
P3FES_DECL_PAIR(fn_sub_16EF60_0016ef60)
P3FES_DECL_PAIR(fn_sub_16F150_0016f150)
P3FES_DECL_PAIR(fn_sub_16F160_0016f160)
P3FES_DECL_PAIR(fn_sub_16F170_0016f170)
P3FES_DECL_PAIR(fn_sub_16F180_0016f180)
P3FES_DECL_PAIR(fn_sub_16F380_0016f380)
P3FES_DECL_PAIR(fn_sub_16F3E0_0016f3e0)
P3FES_DECL_PAIR(fn_sub_16F450_0016f450)
P3FES_DECL_PAIR(fn_datSetFlag_0016f1f0)
P3FES_DECL_PAIR(fn_datClearFlagAll_0016f2e0)
P3FES_DECL_PAIR(fn_MT_Misc_BitChk_003951d0)
P3FES_DECL_PAIR(fn_sub_395170_00395170)
P3FES_DECL_PAIR(fn_sub_3951A0_003951a0)
P3FES_DECL_PAIR(fn_sub_16C6F0_0016c6f0)
P3FES_DECL_PAIR(fn_sub_16C740_0016c740)
P3FES_DECL_PAIR(fn_sub_16C790_0016c790)
P3FES_DECL_PAIR(fn_sub_16CFE0_0016cfe0)
P3FES_DECL_PAIR(fn_sub_16D090_0016d090)
P3FES_DECL_PAIR(fn_sub_16D160_0016d160)
P3FES_DECL_PAIR(fn_clndGetCurrentMoonPhase_00181b10)
P3FES_DECL_PAIR(fn_clndIsHolidayOrSunday_0017dcf0)
P3FES_DECL_PAIR(fn_sub_17DB40_0017db40)
P3FES_DECL_PAIR(fn_clndIsDateInRange_0017e480)
P3FES_DECL_PAIR(fn_sub_17E520_0017e520)
P3FES_DECL_PAIR(fn_clndIsDateInRangeFromStart_0017e5d0)
P3FES_DECL_PAIR(fn_datSetDaysSinceApr5_0016ef70)
P3FES_DECL_PAIR(fn_H_Camp_MoveListCursor_0011abd0)
P3FES_DECL_PAIR(fn_datItemTblSetSections_0016c2f0)
P3FES_DECL_PAIR(fn_sub_170D60_00170d60)
P3FES_DECL_PAIR(fn_sub_170DA0_00170da0)
P3FES_DECL_PAIR(fn_sub_170DF0_00170df0)
P3FES_DECL_PAIR(fn_sub_170E40_00170e40)
P3FES_DECL_PAIR(fn_sub_170E90_00170e90)
P3FES_DECL_PAIR(fn_sub_170ED0_00170ed0)
P3FES_DECL_PAIR(fn_sub_1714B0_001714b0)
P3FES_DECL_PAIR(fn_sub_1714D0_001714d0)
P3FES_DECL_PAIR(fn_sub_1714F0_001714f0)
P3FES_DECL_PAIR(fn_sub_171510_00171510)
P3FES_DECL_PAIR(fn_sub_171550_00171550)
#undef P3FES_DECL_PAIR
void fn_datGetFlag_0016f190(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game::ui2;
using p3fes::game::kSprFileSprites;
using p3fes::game::kSprRecordHeight;
using p3fes::game::kSprRecordSize;
using p3fes::game::kSprRecordU0;
using p3fes::game::kSprRecordU1;
using p3fes::game::kSprRecordV0;
using p3fes::game::kSprRecordV1;
using p3fes::game::kSprRecordWidth;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
s16 load16s(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}
bool chance(std::mt19937& rng, u32 percent) { return rng() % 100u < percent; }
// A 32-bit argument as a register holds it (sign-extended), or with garbage in the upper half of a 16-bit
// value for the functions that narrow their argument to s16 first.
u64 garbage16(std::mt19937& rng, s32 v) { return sx((rng() << 16) | (static_cast<u32>(v) & 0xFFFFu)); }

// --- the extended pair: windows, $f0, HI/LO, missing-function stops ----------------------------------------
struct Window {
    u32 va;
    u32 len;
};
constexpr Window kGlobals{0x7C0000u, 0x80000u};  // $gp data (0x7CBFA8..0x7CE878), gGlobalWork, flags, counters, item tail

struct XOutcome {
    Outcome o;
    u32 f0 = 0;
    u64 hi = 0, lo = 0;
    u64 a0 = 0;  // at a missing-function stop: the argument handed to the missing function
    bool fatal = false;
    u32 fatal_pc = 0;
    std::vector<std::vector<u8>> windows;
};

XOutcome run_x(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Window>& windows, const u64* t01) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    if (t01 != nullptr) {  // the fifth and sixth arguments ($t0/$t1 in the EE ABI)
        m.ctx.gpr[GPR_T0].u64[0] = t01[0];
        m.ctx.gpr[GPR_T1].u64[0] = t01[1];
    }
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    XOutcome x;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent& e) {
        x.fatal = true;
        x.fatal_pc = e.pc;
    }
    Outcome& o = x.o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    x.f0 = m.ctx.fpr[0];
    x.hi = m.ctx.hi.u64[0];
    x.lo = m.ctx.lo.u64[0];
    x.a0 = m.ctx.gpr[GPR_A0].u64[0];
    for (const Window& w : windows) x.windows.push_back(m.bytes(w.va, w.len));
    return x;
}

struct XPair {
    XOutcome hand;
    XOutcome recomp;
};

int g_stops = 0;  // pairs that ended in a missing-function stop (both bodies)

// Runs both bodies from the same guest state (the windows and the arena are restored in between; the recomp
// run's result stays in place) and compares everything. At a missing-function stop the recompiled body is
// still inside its frame, so only what is independent of the frame is compared there.
XPair pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::vector<Window> windows = {kGlobals},
           const u64* t01 = nullptr) {
    windows.push_back({kArena, kArenaSize});
    std::vector<std::vector<u8>> before;
    for (const Window& w : windows) before.push_back(m.bytes(w.va, w.len));
    XPair p;
    p.hand = run_x(m, hand, args, seed, windows, t01);
    for (std::size_t i = 0; i < windows.size(); ++i) std::memcpy(m.at(windows[i].va), before[i].data(), windows[i].len);
    p.recomp = run_x(m, recomp, args, seed, windows, t01);
    INFO(what);
    REQUIRE(p.hand.fatal == p.recomp.fatal);
    if (p.hand.fatal) {
        ++g_stops;
        CHECK(p.hand.fatal_pc == p.recomp.fatal_pc);
        CHECK(p.hand.a0 == p.recomp.a0);
        CHECK(p.hand.o.cycles == p.recomp.o.cycles);
        CHECK(p.hand.o.checks == p.recomp.o.checks);
        CHECK(p.hand.o.live_stack == p.recomp.o.live_stack);
    } else {
        expect_same(p.hand.o, p.recomp.o, what);
        CHECK(p.hand.f0 == p.recomp.f0);
        CHECK(p.hand.hi == p.recomp.hi);
        CHECK(p.hand.lo == p.recomp.lo);
    }
    for (std::size_t i = 0; i < windows.size(); ++i) CHECK(p.hand.windows[i] == p.recomp.windows[i]);
    return p;
}

Args a1(u64 x) { return {x, 0, 0, 0}; }
Args a2(u64 x, u64 y) { return {x, y, 0, 0}; }

bool flag_bit(const Machine& m, s32 id) { return ((load32(m, kFlagWords + 4u * static_cast<u32>(id / 32)) >> (id % 32)) & 1u) != 0; }

// --- host restatements of the documented calendar rules (20_menu_ui.md section 3) --------------------------
constexpr int kMonthLen[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
s32 host_days_since_start(s32 month, s32 day) {
    s32 acc = 0;
    for (s32 mo = 4; mo != month; mo = mo == 12 ? 1 : mo + 1) acc += kMonthLen[mo - 1];
    return acc + day - 5;
}

// --- event/itemtbl.bin -----------------------------------------------------------------------------------
// The section walk of datItemTblSetSections restated: first-record address of each of the 13 sections and of
// the 35 tail records.
struct HostItemTbl {
    u32 first[kItemTblSections];
    u32 count[kItemTblSections];
    u32 tail0;
};
HostItemTbl host_item_tbl(const Machine& m) {
    HostItemTbl h{};
    u32 p = kItemTbl;
    for (u32 s = 0; s < kItemTblSections; ++s) {
        h.count[s] = load32(m, p);
        h.first[s] = p + 16u;
        p = h.first[s] + h.count[s] * kItemTblRecordSize[s];
    }
    h.tail0 = p + 16u;
    return h;
}
void check_item_tbl(const Machine& m, const HostItemTbl& h) {
    for (u32 s = 0; s < kItemTblSections; ++s) CHECK(load32(m, kItemTblSectionSlot[s]) == h.first[s]);
    for (u32 i = 0; i < kItemTblTailCount; ++i) CHECK(load32(m, kItemTblTail + 4u * i) == h.tail0 + 32u * i);
}

// RpRandom (sub_488F30) keeps an additive lagged generator {start, a, b, end} at 0x960070 + the plugin offset
// in $gp - 0x4578; the tests give it a table in the arena so both runs draw the same numbers.
constexpr u32 kRwRandomBase = 0x960070u;
constexpr u32 kRwRandomOffsetSlot = 0x7CE878u;
constexpr u32 kRngTable = kArena + 0x1000u;
constexpr u32 kRngWords = 55;
Window setup_rng(Machine& m, std::mt19937& rng) {
    const u32 st = kRwRandomBase + load32(m, kRwRandomOffsetSlot);
    REQUIRE(st + 16u <= EEMemory::kMainRamSize);
    fill_random(m, kRngTable, kRngWords * 4u, rng);
    store32(m, st + 0, kRngTable);
    store32(m, st + 4, kRngTable + 4u * static_cast<u32>(rand_range(rng, 0, kRngWords - 1)));
    store32(m, st + 8, kRngTable + 4u * static_cast<u32>(rand_range(rng, 0, kRngWords - 1)));
    store32(m, st + 12, kRngTable + 4u * kRngWords);
    return {st, 16};
}

}  // namespace

TEST_CASE("game(ui2): the task-record, file-state and $gp-word accessors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x0A11CE5u};
    const u32 task = kArena, work = kArena + 0x100, file = kArena + 0x200, sfl = kArena + 0x300;
    for (int it = 0; it < 300; ++it) {
        fill_random(m, kArena, 0x400, rng);
        store32(m, task + kTaskWorkData, work);
        if (chance(rng, 35)) store32(m, work, 2);
        if (chance(rng, 35)) store16(m, file, 5);
        if (chance(rng, 10)) store16(m, file, 0x8005);  // only the s16 value 5 counts
        pair(m, PAIR(fn_H_Cursor_GetShouldDraw_00100570), a1(sx(task)), rng(), "H_Cursor_GetShouldDraw");
        pair(m, PAIR(fn_H_Camp_GetRootSelection_0011b9a0), a1(sx(task)), rng(), "H_Camp_GetRootSelection");
        const XPair idle = pair(m, PAIR(fn_H_DayPartsDraw_IsIdle_00184d90), a1(sx(task)), rng(), "H_DayPartsDraw_IsIdle");
        CHECK(idle.hand.o.v0 == (load32(m, work) == 2 ? 1u : 0u));
        pair(m, PAIR(fn_kwlnTaskGetTimer_00195520), a1(sx(task)), rng(), "kwlnTaskGetTimer");
        pair(m, PAIR(fn_kwlnTaskGetWorkData_00195540), a1(sx(task)), rng(), "kwlnTaskGetWorkData");
        const u32 nw = rng();
        pair(m, PAIR(fn_kwlnTaskSetWorkData_00195530), a2(sx(task), sx(nw)), rng(), "kwlnTaskSetWorkData");
        CHECK(load32(m, task + kTaskWorkData) == nw);
        const XPair ready = pair(m, PAIR(fn_sprFileIsReady_00111f30), a1(sx(file)), rng(), "sprFileIsReady");
        CHECK(ready.hand.o.v0 == (load16s(m, file) == 5 ? 1u : 0u));

        // The $gp words and the calendar word.
        store32(m, kScenarioMode, chance(rng, 50) ? rng() % 2 : rng());
        store32(m, kAigisCalendarState, rng());
        for (u32 va : kMemcardChkAreaSeq) store32(m, va, rng());
        store32(m, kSflCursorWork, rng());
        pair(m, PAIR(fn_sub_17D800_0017d800), a1(sx(rng())), rng(), "sub_17D800");
        pair(m, PAIR(fn_sub_17D810_0017d810), a1(sx(rng())), rng(), "sub_17D810");
        const u32 cal = rng();
        pair(m, PAIR(fn_sub_17D820_0017d820), a1(sx(cal)), rng(), "sub_17D820");
        CHECK(load32(m, kAigisCalendarState) == cal);
        pair(m, PAIR(fn_H_Memcard_ClearChkAreaSeq_00191240), a1(sx(rng())), rng(), "H_Memcard_ClearChkAreaSeq");
        for (u32 va : kMemcardChkAreaSeq) CHECK(load32(m, va) == 0);
        pair(m, PAIR(fn_sub_25A110_0025a110), a1(sx(sfl)), rng(), "sub_25A110");
        CHECK(load32(m, kSflCursorWork) == sfl);
        CHECK(load32(m, sfl) == 0);
        pair(m, PAIR(fn_sub_25A120_0025a120), a1(sx(rng())), rng(), "sub_25A120");
        CHECK(load32(m, kSflCursorWork) == 0);
    }
}

TEST_CASE("game(ui2): the day-skip targets and the day-part setter of g_data.c") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xDA75u};
    for (int it = 0; it < 300; ++it) {
        fill_random(m, kDaysSinceApr5, 12, rng);
        pair(m, PAIR(fn_sub_16EF40_0016ef40), a1(sx(rng())), rng(), "sub_16EF40");
        pair(m, PAIR(fn_sub_16EF50_0016ef50), a1(sx(rng())), rng(), "sub_16EF50");
        pair(m, PAIR(fn_sub_16EF60_0016ef60), a1(sx(rng())), rng(), "sub_16EF60");
        const u32 v = rng();
        pair(m, PAIR(fn_sub_16F150_0016f150), a1(sx(v)), rng(), "sub_16F150");
        CHECK(m.at(kTimeOfDay)[0] == static_cast<u8>(v));
        pair(m, PAIR(fn_sub_16F160_0016f160), a1(sx(v)), rng(), "sub_16F160");
        CHECK(load16s(m, kDaysSkipTarget) == static_cast<s16>(v));
        const XPair g = pair(m, PAIR(fn_sub_16EF40_0016ef40), a1(0), rng(), "sub_16EF40 after the store");
        CHECK(g.hand.o.v0 == sx(static_cast<u32>(static_cast<s32>(static_cast<s16>(v)))));
        pair(m, PAIR(fn_sub_16F170_0016f170), a1(sx(v)), rng(), "sub_16F170");
        CHECK(m.at(kTimeSkipTarget)[0] == static_cast<u8>(v));
        pair(m, PAIR(fn_sub_16F180_0016f180), a1(sx(v)), rng(), "sub_16F180");
        CHECK(load32(m, kSkipToTarget) == v);
    }
}

TEST_CASE("game(ui2): the sprite extents, override and 4.12 scale, as floats") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5B17u};
    const u32 handle = kArena, file = kArena + 0x100, sprites = kArena + 0x400;
    int plain = 0;
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kArena, 0x800, rng);
        const s32 idx = rand_range(rng, 0, 7);
        store32(m, handle + 8, file);
        store32(m, handle + 0xC, static_cast<u32>(idx));
        store32(m, file + kSprFileSprites, sprites);
        const u32 rec = sprites + kSprRecordSize * static_cast<u32>(idx);
        for (u32 off : {kSprRecordU0, kSprRecordV0, kSprRecordU1, kSprRecordV1}) {
            const s32 v = chance(rng, 80) ? rand_range(rng, -16, 1024) : static_cast<s32>(rng());
            store32(m, rec + off, static_cast<u32>(v));
        }
        for (u32 off : {kSprRecordWidth, kSprRecordHeight}) store16(m, rec + off, chance(rng, 50) ? 0 : static_cast<u16>(rng()));
        for (u32 off : {0x28u, 0x2Au}) store16(m, handle + off, chance(rng, 40) ? 0 : static_cast<u16>(chance(rng, 50) ? rng() % 0x2000u : rng()));
        const XPair w = pair(m, PAIR(fn_sprGetSpriteWidth_001126b0), a1(sx(handle)), rng(), "sprGetSpriteWidth");
        const XPair h = pair(m, PAIR(fn_sprGetSpriteHeight_00112740), a1(sx(handle)), rng(), "sprGetSpriteHeight");
        // The rule without override and scale: (u1 - u0) as a float, exactly for small extents.
        const s32 ext_w = static_cast<s32>(load32(m, rec + kSprRecordU1) - load32(m, rec + kSprRecordU0));
        if (load16s(m, rec + kSprRecordWidth) == 0 && load16s(m, handle + 0x28) == 0 && ext_w >= 0 && ext_w < (1 << 24)) {
            CHECK(w.hand.f0 == std::bit_cast<u32>(static_cast<float>(ext_w)));
            ++plain;
        }
        (void)h;
    }
    MESSAGE("sprGetSprite{Width,Height}: 600 handles each, " << plain << " plain widths checked against u1 - u0");
}

TEST_CASE("game(ui2): the indexed counters and their reset") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xC0047u};
    for (int it = 0; it < 400; ++it) {
        fill_random(m, kCounters - 32, 128 * 4 + 64, rng);
        const s32 idx = chance(rng, 80) ? rand_range(rng, 0, 127) : rand_range(rng, -8, 140);
        const XPair g = pair(m, PAIR(fn_sub_16F380_0016f380), a1(sx(static_cast<u32>(idx))), rng(), "sub_16F380");
        CHECK(g.hand.o.v0 == sx(load32(m, kCounters + 4u * static_cast<u32>(idx))));
        const u32 v = rng();
        pair(m, PAIR(fn_sub_16F3E0_0016f3e0), a2(sx(static_cast<u32>(idx)), sx(v)), rng(), "sub_16F3E0");
        CHECK(load32(m, kCounters + 4u * static_cast<u32>(idx)) == v);
        if (it % 20 == 0) {
            const u32 last = load32(m, kCounters + 4u * 127);
            pair(m, PAIR(fn_sub_16F450_0016f450), a1(sx(rng())), rng(), "sub_16F450");
            for (u32 i = 0; i < 127; ++i) CHECK(load32(m, kCounters + 4u * i) == 0);
            CHECK(load32(m, kCounters + 4u * 127) == last);  // the reset stops one short
        }
    }
}

TEST_CASE("game(ui2): datSetFlag, datClearFlagAll and the MT_Misc flag wrappers") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF1A65u};
    fill_random(m, kFlagWords - 32, kFlagWordCount * 4 + 64, rng);
    pair(m, PAIR(fn_datClearFlagAll_0016f2e0), a1(0), rng(), "datClearFlagAll");
    for (s32 i = 0; i < kFlagWordCount; ++i) CHECK(load32(m, kFlagWords + 4u * static_cast<u32>(i)) == 0);
    const s32 edges[] = {0, 1, 31, 32, 0x15FF, 0x1600, 0x1601, -1, -31, -32, -33, kHitFlag, kWeekdayFlagFirst, kHolidayFlag};
    int hits = 0;
    for (int it = 0; it < 1500; ++it) {
        if (it % 100 == 0) fill_random(m, kFlagWords - 32, kFlagWordCount * 4 + 64, rng);
        const s32 id = it < 2 * static_cast<int>(std::size(edges)) ? edges[it % std::size(edges)]
                       : chance(rng, 85)                           ? rand_range(rng, 0, kFlagCount - 1)
                                                                    : rand_range(rng, -200, kFlagCount + 200);
        u64 on;
        switch (rng() % 6) {
        case 0: on = 0; break;
        case 1: on = 1; break;
        case 2: on = 1ull << 32; break;  // only the upper word set: still "on" (the test is on the whole register)
        case 3: on = 1ull << 63; break;
        default: on = sx(rng()); break;
        }
        // printf (the "hit" report) is served by a recorder in both bodies through the hooked forwarder, whether it
        // is recompiled or hand-written (finalB).
        StandIns si;
        si.install_recorder(0x5225A8u, "printf", 0);
        const XPair p = [&] {
            StandInsScope scope{si};
            return pair(m, PAIR(fn_datSetFlag_0016f1f0), a2(sx(static_cast<u32>(id)), on), rng(), "datSetFlag");
        }();
        if (id == kHitFlag) {
            // "hit \n" through printf: each body calls it once with the format in $a0.
            REQUIRE(si.calls_to(0x5225A8u) == 2u);
            CHECK(si.log[0].args[0] == sx(kHitString));
            CHECK(si.log[1].args[0] == sx(kHitString));
            CHECK(m.str(kHitString) == "hit \n");
            ++hits;
        } else if (id >= 0 && id < kFlagCount) {
            CHECK(flag_bit(m, id) == (on != 0));
        }
        // the wrappers, on in-range ids
        const s32 wid = rand_range(rng, 0, kFlagCount - 1);
        if (wid == kHitFlag) continue;
        pair(m, PAIR(fn_sub_395170_00395170), a2(sx(static_cast<u32>(wid)), sx(rng())), rng(), "sub_395170 (bit on)");
        CHECK(flag_bit(m, wid));
        const XPair c1 = pair(m, PAIR(fn_MT_Misc_BitChk_003951d0), a1(sx(static_cast<u32>(wid))), rng(), "MT_Misc_BitChk (on)");
        CHECK(c1.hand.o.v0 == 1);
        pair(m, PAIR(fn_sub_3951A0_003951a0), a2(sx(static_cast<u32>(wid)), sx(rng())), rng(), "sub_3951A0 (bit off)");
        CHECK_FALSE(flag_bit(m, wid));
        const XPair c0 = pair(m, PAIR(fn_MT_Misc_BitChk_003951d0), a1(sx(static_cast<u32>(wid))), rng(), "MT_Misc_BitChk (off)");
        CHECK(c0.hand.o.v0 == 0);
    }
    MESSAGE("datSetFlag: 1500 calls, " << hits << " of them flag 0x1376 (printf recorded)");
}

TEST_CASE("game(ui2): the social-stat point getters and setters") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x57A75u};
    struct Stat {
        Fn get, get_r, set, set_r;
        u32 field;
        const char* name;
    };
    const Stat stats[3] = {
        {PAIR(fn_sub_16C6F0_0016c6f0), PAIR(fn_sub_16CFE0_0016cfe0), 0, "academic"},
        {PAIR(fn_sub_16C740_0016c740), PAIR(fn_sub_16D090_0016d090), 2, "charm"},
        {PAIR(fn_sub_16C790_0016c790), PAIR(fn_sub_16D160_0016d160), 4, "courage"},
    };
    const u32 lo = kCharacterStats - 2 * kCharacterStride, len = 24 * kCharacterStride;
    for (int it = 0; it < 500; ++it) {
        if (it % 50 == 0) fill_random(m, lo, len, rng);
        const s32 who = chance(rng, 40) ? 1 : rand_range(rng, -2, 20);
        const s32 pts = chance(rng, 80) ? rand_range(rng, 0, 999) : rand_range(rng, -40, 1040);
        const Stat& s = stats[rng() % 3];
        const u32 va = who == 1 ? kProtagonistStats + s.field
                                : kCharacterStats + s.field + static_cast<u32>(who) * kCharacterStride;
        const XPair g = pair(m, s.get, s.get_r, a1(garbage16(rng, who)), rng(), s.name);
        CHECK(g.hand.o.v0 == sx(static_cast<u32>(static_cast<s32>(load16s(m, va)))));
        pair(m, s.set, s.set_r, a2(garbage16(rng, who), garbage16(rng, pts)), rng(), s.name);
        CHECK(load16s(m, va) == static_cast<s16>(pts));
    }
}

TEST_CASE("game(ui2): moon phase, holiday-or-Sunday and the date-range tests") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xCA1E0u};
    int sundays = 0, holidays = 0;
    for (s32 d = -10; d <= 420; ++d) {
        store16(m, kDaysSinceApr5, static_cast<u16>(d));
        if (d >= 0 && d < 368) pair(m, PAIR(fn_clndGetCurrentMoonPhase_00181b10), a1(sx(rng())), rng(), "clndGetCurrentMoonPhase");
        const XPair cur = pair(m, PAIR(fn_clndIsHolidayOrSunday_0017dcf0), a1(sx(rng())), rng(), "clndIsHolidayOrSunday");
        const XPair of = pair(m, PAIR(fn_sub_17DB40_0017db40), a1(garbage16(rng, d)), rng(), "sub_17DB40");
        if (d >= 0) CHECK(of.hand.o.v0 == cur.hand.o.v0);  // the same test for a given day
        if ((d + 7) % 7 == 0) {                           // April 5 was a Sunday
            CHECK(cur.hand.o.v0 == 1);
            ++sundays;
        } else {
            holidays += static_cast<int>(cur.hand.o.v0);
        }
    }
    // The 356-entry scan limit: with the -1 terminator gone the scan runs on into the data after the table
    // (the month lengths, strings, ...) until a -1 month or the limit. Restored afterwards.
    {
        const u32 table_len = kMonthLengths - kHolidays;
        const std::vector<u8> saved = m.bytes(kHolidays, table_len);
        for (u32 off = 0; off < table_len; off += 4) {
            store16(m, kHolidays + off, static_cast<u16>(rand_range(rng, 13, 40)));
            store16(m, kHolidays + off + 2, static_cast<u16>(rand_range(rng, 1, 31)));
        }
        s32 entries = 0;
        while (entries < kHolidayScanLimit && load16s(m, kHolidays + 4u * static_cast<u32>(entries)) != -1) ++entries;
        for (s32 d = 0; d < 400; d += 3) {
            store16(m, kDaysSinceApr5, static_cast<u16>(d));
            pair(m, PAIR(fn_clndIsHolidayOrSunday_0017dcf0), a1(0), rng(), "clndIsHolidayOrSunday (no terminator)");
            pair(m, PAIR(fn_sub_17DB40_0017db40), a1(sx(static_cast<u32>(d))), rng(), "sub_17DB40 (no terminator)");
        }
        std::memcpy(m.at(kHolidays), saved.data(), table_len);
        MESSAGE("holiday scan without the terminator: " << entries << " entries scanned before a -1 month or the limit");
    }
    for (int it = 0; it < 300; ++it) {  // other day counts through the 16-bit argument
        pair(m, PAIR(fn_sub_17DB40_0017db40), a1(garbage16(rng, static_cast<s32>(rng()))), rng(), "sub_17DB40 (any s16)");
    }
    int inside = 0, stops = 0;
    for (int it = 0; it < 600; ++it) {
        const s32 today = rand_range(rng, 0, 365);
        store16(m, kDaysSinceApr5, static_cast<u16>(today));
        const s32 m0 = rand_range(rng, 1, 12), d0 = rand_range(rng, 1, 31), m1 = rand_range(rng, 1, 12), d1 = rand_range(rng, 1, 31);
        const s32 s0 = host_days_since_start(m0, d0), s1 = host_days_since_start(m1, d1);
        const XPair r = pair(m, PAIR(fn_clndIsDateInRange_0017e480), {sx(m0), sx(d0), sx(m1), sx(d1)}, rng(), "clndIsDateInRange");
        CHECK(r.hand.o.v0 == ((s0 <= today && today <= s1) ? 1u : 0u));
        inside += static_cast<int>(r.hand.o.v0);
        const s32 mm = rand_range(rng, 1, 12), dd = rand_range(rng, 1, 31);
        const u64 t01[2] = {sx(m1), sx(d1)};
        const XPair f = pair(m, PAIR(fn_sub_17E520_0017e520), {sx(mm), sx(dd), sx(m0), sx(d0)}, rng(), "sub_17E520", {kGlobals}, t01);
        const s32 x = host_days_since_start(mm, dd);
        CHECK(f.hand.o.v0 == ((s0 <= x && x <= s1) ? 1u : 0u));
        const s32 n = it % 25 == 0 ? 0 : chance(rng, 90) ? rand_range(rng, 1, 60) : rand_range(rng, -20, -1);
        // the debug-log formatter sub_1052B0 is served by a recorder in both bodies (hooked forwarder; hand-written
        // since finalB)
        StandIns si;
        si.install_recorder(0x1052B0u, "sub_1052B0", 0);
        const XPair s = [&] {
            StandInsScope scope{si};
            return pair(m, PAIR(fn_clndIsDateInRangeFromStart_0017e5d0), {sx(m0), sx(d0), sx(static_cast<u32>(n)), sx(rng())}, rng(),
                        "clndIsDateInRangeFromStart");
        }();
        if (n == 0) {
            // "Calender chk range is 0 " through sub_1052B0: each body calls it once with the format in $a0.
            REQUIRE(si.calls_to(0x1052B0u) == 2u);
            CHECK(si.log[0].args[0] == sx(kRangeZeroString));
            CHECK(si.log[1].args[0] == sx(kRangeZeroString));
            CHECK(m.str(kRangeZeroString) == "Calender chk range is 0 ");
            ++stops;
        } else {
            CHECK(s.hand.o.v0 == ((s0 <= today && today <= s0 + n - 1) ? 1u : 0u));
        }
    }
    MESSAGE("calendar: 431 days (" << sundays << " Sundays, " << holidays << " other holidays), 600 ranges (" << inside << " inside), " << stops << " zero-length stops");
}

TEST_CASE("game(ui2): datSetDaysSinceApr5 keeps the weekday and holiday flags") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xDA7Eu};
    int changes = 0;
    for (int it = 0; it < 400; ++it) {
        if (it % 40 == 0) {
            fill_random(m, kFlagWords, kFlagWordCount * 4, rng);
            fill_random(m, 0x836458u, 0x60, rng);  // what the two day-change resets clear
        }
        const s32 cur = rand_range(rng, 0, 365);
        store16(m, kDaysSinceApr5, static_cast<u16>(cur));
        const s32 d = chance(rng, 30) ? cur : rand_range(rng, -5, 400);
        const bool changed = static_cast<s16>(d) != static_cast<s16>(cur);
        if (changed) store32(m, kFlagWords + 4u * (kDayChangedFlag / 32), load32(m, kFlagWords + 4u * (kDayChangedFlag / 32)) | (1u << (kDayChangedFlag % 32)));
        pair(m, PAIR(fn_datSetDaysSinceApr5_0016ef70), a1(garbage16(rng, d)), rng(), "datSetDaysSinceApr5");
        CHECK(load16s(m, kDaysSinceApr5) == static_cast<s16>(d));
        if (changed) {
            CHECK_FALSE(flag_bit(m, kDayChangedFlag));
            ++changes;
        }
        // Exactly the new weekday's flag among 0xA08..0xA0E (Monday..Saturday, then Sunday) for a day >= 0.
        if (d >= 0) {
            const s32 wd = (d + 7) % 7;
            const s32 want = wd == 0 ? kWeekdayFlagFirst + 6 : kWeekdayFlagFirst + wd - 1;
            for (s32 f = kWeekdayFlagFirst; f < kHolidayFlag; ++f) CHECK(flag_bit(m, f) == (f == want));
            if (wd == 0) CHECK(flag_bit(m, kHolidayFlag));
        }
    }
    MESSAGE("datSetDaysSinceApr5: 400 calls, " << changes << " date changes");
}

TEST_CASE("game(ui2): H_Camp_MoveListCursor over random lists, pads and positions") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xCA3Bu};
    const u32 scroll_va = kArena + 0x10, cursor_va = kArena + 0x14;
    const u32 bits[4] = {kPadUp, kPadDown, kPadPagePrev, kPadPageNext};
    auto random_pad = [&](u32 percent) {
        u32 v = 0;
        for (u32 b : bits)
            if (chance(rng, percent)) v |= b;
        if (chance(rng, 20)) v |= rng() & 0xFFFFu;
        return static_cast<u16>(v);
    };
    int moved = 0;
    for (int it = 0; it < 4000; ++it) {
        const s32 count = chance(rng, 90) ? rand_range(rng, 0, 12) : rand_range(rng, 0, 40);
        const s32 page = chance(rng, 90) ? rand_range(rng, 1, 8) : rand_range(rng, -1, 12);
        store32(m, scroll_va, static_cast<u32>(chance(rng, 90) ? rand_range(rng, 0, count > 0 ? count : 1) : rand_range(rng, -2, 50)));
        store32(m, cursor_va, static_cast<u32>(chance(rng, 90) ? rand_range(rng, 0, page > 0 ? page : 1) : rand_range(rng, -2, 12)));
        store16(m, kPadPressed, random_pad(25));
        store16(m, kPadRepeat, random_pad(25));
        store16(m, kPadHeld, random_pad(50));
        store16(m, kPadRepeatHeld, random_pad(30));
        const XPair p = pair(m, PAIR(fn_H_Camp_MoveListCursor_0011abd0), {sx(static_cast<u32>(count)), sx(static_cast<u32>(page)), sx(scroll_va), sx(cursor_va)},
                             rng(), "H_Camp_MoveListCursor");
        moved += static_cast<int>(p.hand.o.v0);
    }
    // Documented cases (20_menu_ui.md section 4.1): down on the last entry with the button held wraps to the top;
    // up on row 1 with scroll 0 moves the cursor to row 0; up on row 1 with scroll > 0 scrolls.
    struct Case {
        s32 count, page, scroll, cursor;
        u16 pressed, held;
        u32 v0;
        s32 scroll_after, cursor_after;
    };
    const Case cases[] = {
        {5, 8, 0, 4, kPadDown, kPadDown, 1, 0, 0},
        {5, 8, 0, 4, kPadDown, 0, 0, 0, 4},
        {10, 4, 0, 1, kPadUp, 0, 1, 0, 0},
        {10, 4, 3, 1, kPadUp, 0, 1, 2, 1},
        {10, 4, 0, 2, kPadDown, 0, 1, 1, 2},  // cursor on row page - 2 scrolls while it can
        {1, 4, 0, 0, kPadDown, kPadDown, 0, 0, 0},
    };
    for (const Case& c : cases) {
        store32(m, scroll_va, static_cast<u32>(c.scroll));
        store32(m, cursor_va, static_cast<u32>(c.cursor));
        store16(m, kPadPressed, c.pressed);
        store16(m, kPadRepeat, 0);
        store16(m, kPadHeld, c.held);
        store16(m, kPadRepeatHeld, 0);
        const XPair p = pair(m, PAIR(fn_H_Camp_MoveListCursor_0011abd0), {sx(static_cast<u32>(c.count)), sx(static_cast<u32>(c.page)), sx(scroll_va), sx(cursor_va)},
                             rng(), "H_Camp_MoveListCursor (documented case)");
        CHECK(p.hand.o.v0 == c.v0);
        CHECK(static_cast<s32>(load32(m, scroll_va)) == c.scroll_after);
        CHECK(static_cast<s32>(load32(m, cursor_va)) == c.cursor_after);
    }
    MESSAGE("H_Camp_MoveListCursor: 4000 random calls, " << moved << " moved");
}

TEST_CASE("game(ui2): datItemTblSetSections and the itemtbl record lookups on synthetic tables") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x17E3u};
    for (int it = 0; it < 60; ++it) {
        // 13 counted sections and the tail header, small counts, garbage in the records.
        u32 p = kItemTbl;
        for (u32 s = 0; s < kItemTblSections; ++s) {
            const u32 count = chance(rng, 10) ? 0 : rng() % 24u;
            fill_random(m, p, 16 + count * kItemTblRecordSize[s], rng);
            store32(m, p, count);
            p += 16 + count * kItemTblRecordSize[s];
        }
        fill_random(m, p, 16 + 35 * 32, rng);
        pair(m, PAIR(fn_datItemTblSetSections_0016c2f0), a1(sx(rng())), rng(), "datItemTblSetSections");
        check_item_tbl(m, host_item_tbl(m));
    }
    // Lookups over the section pointers now in place, with any s16 id.
    const u32 kind_va = kArena + 0x1F00;
    const Window rngw = setup_rng(m, rng);
    for (int it = 0; it < 1500; ++it) {
        const s32 id = chance(rng, 70) ? rand_range(rng, -50, 4600) : static_cast<s32>(static_cast<s16>(rng()));
        const u64 a = garbage16(rng, id);
        const XPair r0 = pair(m, PAIR(fn_sub_170D60_00170d60), a1(a), rng(), "sub_170D60");
        pair(m, PAIR(fn_sub_170DA0_00170da0), a1(a), rng(), "sub_170DA0");
        pair(m, PAIR(fn_sub_170DF0_00170df0), a1(a), rng(), "sub_170DF0");
        pair(m, PAIR(fn_sub_170E40_00170e40), a1(a), rng(), "sub_170E40");
        pair(m, PAIR(fn_sub_170E90_00170e90), a1(a), rng(), "sub_170E90");
        const XPair any = pair(m, PAIR(fn_sub_170ED0_00170ed0), a2(a, sx(kind_va)), rng(), "sub_170ED0");
        const u32 kind = load32(m, kind_va);
        CHECK(kind == (id < 1000 ? 0u : id < 2000 ? 1u : id < 3000 ? 2u : id < 4000 ? 3u : 4u));
        if (id < 1000) CHECK(any.hand.o.v0 == r0.hand.o.v0);
        const u32 index = chance(rng, 80) ? rng() % 64u : rng();
        pair(m, PAIR(fn_sub_1714B0_001714b0), a1(sx(index)), rng(), "sub_1714B0");
        pair(m, PAIR(fn_sub_1714D0_001714d0), a1(sx(index)), rng(), "sub_1714D0");
        pair(m, PAIR(fn_sub_1714F0_001714f0), a1(sx(index)), rng(), "sub_1714F0");
        const u32 rows = load32(m, load32(m, kItemTblSectionSlot[9]) - 16);
        if (rows != 0) {
            const s32 row = rand_range(rng, 0, static_cast<s32>(rows) - 1), col = rand_range(rng, 0, 4);
            const XPair f = pair(m, PAIR(fn_sub_171510_00171510), a2(garbage16(rng, row), garbage16(rng, col)), rng(), "sub_171510");
            CHECK(f.hand.f0 == load32(m, load32(m, kItemTblSectionSlot[9]) + 20u * static_cast<u32>(row) + 4u * static_cast<u32>(col)));
        }
        const u32 picks = load32(m, load32(m, kItemTblSectionSlot[10]) - 16);
        if (picks != 0) {
            const u32 table = (rng() & 0xFFFF0000u) | (rng() % picks);
            pair(m, PAIR(fn_sub_171550_00171550), {sx(rng()), sx(rng()), sx(table), sx(rng())}, rng(), "sub_171550", {kGlobals, rngw});
        }
    }
}

TEST_CASE("game(ui2): the real DATA/EVENT/ITEMTBL.BIN through the slicer and every lookup") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const std::filesystem::path path = std::filesystem::path(elf_path()).parent_path().parent_path() / "DATA" / "EVENT" / "ITEMTBL.BIN";
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        MESSAGE("SKIP: no ITEMTBL.BIN at " << path.string());
        return;
    }
    const std::vector<u8> file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    REQUIRE(file.size() > 16);
    std::memcpy(m.at(kItemTbl), file.data(), file.size());  // as the file-setup task's memcpy does
    std::mt19937 rng{0x17EBu};
    pair(m, PAIR(fn_datItemTblSetSections_0016c2f0), a1(0), rng(), "datItemTblSetSections (ITEMTBL.BIN)");
    const HostItemTbl h = host_item_tbl(m);
    check_item_tbl(m, h);
    CHECK(h.tail0 + 35u * 32u <= kItemTbl + file.size());  // the 35 tail records end inside the file
    const u32 kind_va = kArena + 0x1F00;
    for (s32 id = -20; id < 4400; ++id) {
        const XPair any = pair(m, PAIR(fn_sub_170ED0_00170ed0), a2(sx(static_cast<u32>(id)), sx(kind_va)), rng(), "sub_170ED0 (ITEMTBL.BIN)");
        Fn hand = nullptr, rec = nullptr;
        switch (load32(m, kind_va)) {
        case 0: hand = &recomp_gen::fn_sub_170D60_00170d60, rec = &recomp_gen::fn_sub_170D60_00170d60__recomp; break;
        case 1: hand = &recomp_gen::fn_sub_170DA0_00170da0, rec = &recomp_gen::fn_sub_170DA0_00170da0__recomp; break;
        case 2: hand = &recomp_gen::fn_sub_170DF0_00170df0, rec = &recomp_gen::fn_sub_170DF0_00170df0__recomp; break;
        case 3: hand = &recomp_gen::fn_sub_170E40_00170e40, rec = &recomp_gen::fn_sub_170E40_00170e40__recomp; break;
        default: hand = &recomp_gen::fn_sub_170E90_00170e90, rec = &recomp_gen::fn_sub_170E90_00170e90__recomp; break;
        }
        const XPair one = pair(m, hand, rec, a1(sx(static_cast<u32>(id))), rng(), "item lookup by kind (ITEMTBL.BIN)");
        CHECK(one.hand.o.v0 == any.hand.o.v0);  // sub_170ED0 = the lookup of its kind
    }
    for (u32 i = 0; i < h.count[7] + 2; ++i) pair(m, PAIR(fn_sub_1714B0_001714b0), a1(i), rng(), "sub_1714B0 (ITEMTBL.BIN)");
    for (u32 i = 0; i < h.count[8] + 2; ++i) pair(m, PAIR(fn_sub_1714D0_001714d0), a1(i), rng(), "sub_1714D0 (ITEMTBL.BIN)");
    for (u32 i = 0; i < h.count[11] + 2; ++i) pair(m, PAIR(fn_sub_1714F0_001714f0), a1(i), rng(), "sub_1714F0 (ITEMTBL.BIN)");
    for (u32 r = 0; r < h.count[9]; ++r)
        for (u32 c = 0; c < 5; ++c) pair(m, PAIR(fn_sub_171510_00171510), a2(r, c), rng(), "sub_171510 (ITEMTBL.BIN)");
    const Window rngw = setup_rng(m, rng);
    int picks = 0;
    for (u32 t = 0; t < h.count[10]; ++t)
        for (int k = 0; k < 20; ++k) {
            const XPair p = pair(m, PAIR(fn_sub_171550_00171550), {0, 0, sx(t), 0}, rng(), "sub_171550 (ITEMTBL.BIN)", {kGlobals, rngw});
            // The pick is one of the record's 16 values.
            bool listed = false;
            const u32 rec = h.first[10] + 32u * t;
            for (u32 j = 0; j < 16; ++j) listed = listed || m.at(rec + 2 * j + 1)[0] == static_cast<u8>(p.hand.o.v0);
            CHECK(listed);
            ++picks;
        }
    MESSAGE("ITEMTBL.BIN: " << file.size() << " bytes, section counts " << h.count[0] << "/" << h.count[1] << "/" << h.count[2] << "/" << h.count[3] << "/"
                            << h.count[4] << "/" << h.count[5] << "/" << h.count[6] << "/" << h.count[7] << "/" << h.count[8] << "/" << h.count[9]
                            << "/" << h.count[10] << "/" << h.count[11] << "/" << h.count[12] << ", 4420 item ids, " << picks
                            << " weighted picks; missing-function stops so far: " << g_stops);
}

#endif  // P3FES_GAME_HAVE_GENERATED
