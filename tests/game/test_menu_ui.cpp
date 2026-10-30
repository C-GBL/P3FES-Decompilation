// Phase 5 pair tests for the menu/UI leaves (game/src/ui/*.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved
// registers, memory outside the dead stack -- here the arena holding the cursor task/work records --,
// virtual cycles, check-point count) on randomised inputs; the documented rules
// (docs/ANALYSIS/20_menu_ui.md sections 3-5) are checked on the host, independently of both bodies:
// the April-based calendar, weekday 0 = Sunday on April 5, the moon-phase table ("Next: 2" on 4/7),
// the flag-bit addressing, the level thresholds and strings, the cursor record offsets.
#include "pair_harness.h"

#include "p3fes/game/ui.h"

#include <array>
#include <cstring>
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
P3FES_DECL_PAIR(fn_datGetDaysSinceApr5_0016ef20)
P3FES_DECL_PAIR(fn_datGetTime_0016ef30)
P3FES_DECL_PAIR(fn_clndGetMonthFromDaysSinceApr5_0017d830)
P3FES_DECL_PAIR(fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0)
P3FES_DECL_PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0)
P3FES_DECL_PAIR(fn_clndGetWeekDay_0017dae0)
P3FES_DECL_PAIR(fn_clndGetCurrentWeekDay_0017db00)
P3FES_DECL_PAIR(fn_clndGetCurrentMonth_0017d920)
P3FES_DECL_PAIR(fn_clndGetCurrentDay_0017da40)
P3FES_DECL_PAIR(fn_clndGetMoonPhase_00181b50)
P3FES_DECL_PAIR(fn_datGetFlag_0016f190)
P3FES_DECL_PAIR(fn_sprFontGetFile_001120a0)
P3FES_DECL_PAIR(fn_H_Camp_GetAcademicLevelString_0011a810)
P3FES_DECL_PAIR(fn_H_Camp_GetCharmLevelString_0011a840)
P3FES_DECL_PAIR(fn_H_Camp_GetCourageLevelString_0011a870)
P3FES_DECL_PAIR(fn_datGetAcademicLevel_00177280)
P3FES_DECL_PAIR(fn_datGetCharmLevel_001772f0)
P3FES_DECL_PAIR(fn_datGetCourageLevel_00177360)
P3FES_DECL_PAIR(fn_H_Cursor_SetPos_00100710)
P3FES_DECL_PAIR(fn_H_Cursor_SetRect_00100740)
P3FES_DECL_PAIR(fn_H_Cursor_SetZOffset_00100770)
P3FES_DECL_PAIR(fn_H_Cursor_SetColor_00100780)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game::ui;

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
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}

// --- host restatements of the documented rules (20_menu_ui.md section 3) -----------------------------------
constexpr int kMonthLen[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// The game's walk from April 5: month and day-of-month for a day count (the day count may be negative:
// the walk stops at once and April keeps a day below 5).
void host_month_day(s32 days, s32& month, s32& day) {
    s32 rem = days + 4;
    month = 4;
    while (rem >= kMonthLen[month - 1]) {
        rem -= kMonthLen[month - 1];
        month = month == 12 ? 1 : month + 1;
    }
    day = rem + 1;
}
s32 host_days_since_start(s32 month, s32 day) {
    s32 acc = 0;
    for (s32 m = 4; m != month; m = m == 12 ? 1 : m + 1) acc += kMonthLen[m - 1];
    return acc + day - 5;
}

// The $f12 argument of H_Cursor_SetZOffset: the harness seeds the GPRs only, so this variant of
// pair_harness::run also sets the float register before the call.
Outcome run_f12(Machine& m, Fn fn, const Args& args, u32 seed, u32 f12_bits) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    m.ctx.fpr[12] = f12_bits;
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Outcome o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    return o;
}

}  // namespace

TEST_CASE("game(ui): the month tables and the moon-phase table of the ELF are what the doc says") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    for (int i = 0; i < 12; ++i) {
        s16 len;
        std::memcpy(&len, m.at(kMonthLengths + 2 * i), 2);
        CHECK(len == kMonthLen[i]);
    }
    // 4/7 (days 2) is the dorm scene's date: Tuesday, moon phase 0x0C; the next full moon (0x0E) is two days
    // away -> the HUD's "Next: 2" (H_DayPartsDraw_DrawHud scans the table from the current day for the first 0x0E).
    CHECK(m.at(kMoonPhaseTable)[2] == 0x0C);
    CHECK(m.at(kMoonPhaseTable)[3] == 0x0D);
    CHECK(m.at(kMoonPhaseTable)[4] == 0x0E);
    CHECK((2 + 7) % 7 == 2);  // Tuesday with 0 = Sunday
    s16 thr[7];
    std::memcpy(thr, m.at(kAcademicThresholds), sizeof thr);
    CHECK(thr[0] == 0);
    CHECK(thr[1] == 20);
    CHECK(thr[6] == 999);
    std::memcpy(thr, m.at(kCharmThresholds), sizeof thr);
    CHECK(thr[1] == 15);
    CHECK(thr[5] == 80);
    CHECK(m.str(load32(m, kAcademicLevelStrings + 4 * 6)) == "Genius");
    CHECK(m.str(load32(m, kCharmLevelStrings + 4 * 1)) == "Plain");
    CHECK(m.str(load32(m, kCourageLevelStrings + 4 * 1)) == "Timid");
}

TEST_CASE("game(ui): datGetDaysSinceApr5 / datGetTime and the clnd* date arithmetic equal their recompiled bodies and the calendar rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{20261020u};
    int checked = 0;
    for (int it = 0; it < 1200; ++it) {
        const s32 days = rand_range(rng, -40, 420);
        const u8 tod = static_cast<u8>(rng());
        store16(m, kDaysSinceApr5, static_cast<u16>(days));
        m.at(kTimeOfDay)[0] = tod;
        const u32 seed = rng();
        Pair p = run_pair(m, PAIR(fn_datGetDaysSinceApr5_0016ef20), Args{}, seed, "datGetDaysSinceApr5");
        CHECK(p.hand.v0 == sx(static_cast<u32>(days)));
        p = run_pair(m, PAIR(fn_datGetTime_0016ef30), Args{}, seed, "datGetTime");
        CHECK(p.hand.v0 == tod);

        s32 month, day;
        host_month_day(days, month, day);
        p = run_pair(m, PAIR(fn_clndGetMonthFromDaysSinceApr5_0017d830), Args{sx(static_cast<u32>(days))}, seed, "clndGetMonthFromDaysSinceApr5");
        CHECK(p.hand.v0 == sx(static_cast<u32>(month)));
        p = run_pair(m, PAIR(fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0), Args{sx(static_cast<u32>(days))}, seed, "clndGetDayOfMonthFromDaysSinceApr5");
        CHECK(p.hand.v0 == sx(static_cast<u32>(day)));
        p = run_pair(m, PAIR(fn_clndGetCurrentMonth_0017d920), Args{}, seed, "clndGetCurrentMonth");
        CHECK(p.hand.v0 == sx(static_cast<u32>(month)));
        p = run_pair(m, PAIR(fn_clndGetCurrentDay_0017da40), Args{}, seed, "clndGetCurrentDay");
        CHECK(p.hand.v0 == sx(static_cast<u32>(day)));
        if (days >= 0 && days <= 360) {  // the inverse holds within the game year (April 5 .. March 31)
            p = run_pair(m, PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0), Args{sx(static_cast<u32>(month)), sx(static_cast<u32>(day))}, seed,
                         "clndGetDaysSinceStartFromDate(month, day)");
            CHECK(p.hand.v0 == sx(static_cast<u32>(days)));
            CHECK(host_days_since_start(month, day) == days);
            ++checked;
        } else {  // past March 31 the walk has wrapped into the next April and the inverse is 365 short
            p = run_pair(m, PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0), Args{sx(static_cast<u32>(month)), sx(static_cast<u32>(day))}, seed,
                         "clndGetDaysSinceStartFromDate(month, day) outside the year");
            CHECK(p.hand.v0 == sx(static_cast<u32>(host_days_since_start(month, day))));
        }
        const s32 wd_host = (days + 7) % 7;  // C remainder, as the EE's div leaves it in HI
        p = run_pair(m, PAIR(fn_clndGetWeekDay_0017dae0), Args{sx(static_cast<u32>(days))}, seed, "clndGetWeekDay");
        CHECK(p.hand.v0 == sx(static_cast<u32>(wd_host)));
        p = run_pair(m, PAIR(fn_clndGetCurrentWeekDay_0017db00), Args{}, seed, "clndGetCurrentWeekDay");
        CHECK(p.hand.v0 == sx(static_cast<u32>(wd_host)));
    }
    CHECK(checked > 800);
    // Fixed points of the documented calendar: April 5 -> (4, 5) Sunday; 4/7 -> Tuesday; May 1 is day 26;
    // Jan 1 is day 271; days-since-start of arbitrary (month, day) pairs incl. months above 12 wrap.
    const u32 seed = rng();
    Pair p = run_pair(m, PAIR(fn_clndGetMonthFromDaysSinceApr5_0017d830), Args{0}, seed, "month of day 0");
    CHECK(p.hand.v0 == 4);
    p = run_pair(m, PAIR(fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0), Args{0}, seed, "day of day 0");
    CHECK(p.hand.v0 == 5);
    p = run_pair(m, PAIR(fn_clndGetWeekDay_0017dae0), Args{0}, seed, "weekday of day 0");
    CHECK(p.hand.v0 == 0);
    p = run_pair(m, PAIR(fn_clndGetWeekDay_0017dae0), Args{2}, seed, "weekday of 4/7");
    CHECK(p.hand.v0 == 2);
    p = run_pair(m, PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0), Args{5, 1}, seed, "May 1");
    CHECK(p.hand.v0 == 26);
    p = run_pair(m, PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0), Args{1, 1}, seed, "Jan 1");
    CHECK(p.hand.v0 == 271);
    for (int it = 0; it < 300; ++it) {
        const s32 month = rand_range(rng, 1, 40), day = rand_range(rng, -50, 80);
        run_pair(m, PAIR(fn_clndGetDaysSinceStartFromDate_0017d8b0), Args{sx(static_cast<u32>(month)), sx(static_cast<u32>(day))}, rng(),
                 "clndGetDaysSinceStartFromDate random");
    }
    for (int it = 0; it < 300; ++it) {  // large and negative day counts, including the s16 wrap of the walk
        const s32 days = rand_range(rng, -40000, 40000);
        const u32 s = rng();
        run_pair(m, PAIR(fn_clndGetMonthFromDaysSinceApr5_0017d830), Args{sx(static_cast<u32>(days))}, s, "month of a far day");
        run_pair(m, PAIR(fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0), Args{sx(static_cast<u32>(days))}, s, "day of a far day");
        run_pair(m, PAIR(fn_clndGetWeekDay_0017dae0), Args{sx(static_cast<u32>(days))}, s, "weekday of a far day");
    }
}

TEST_CASE("game(ui): clndGetMoonPhase equals its recompiled body over the whole table") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{7u};
    for (u32 days = 0; days < 0x170; ++days) {
        const Pair p = run_pair(m, PAIR(fn_clndGetMoonPhase_00181b50), Args{days}, rng(), "clndGetMoonPhase");
        CHECK(p.hand.v0 == m.at(kMoonPhaseTable)[days]);
        CHECK(p.hand.v0 <= 0x1D);
    }
    for (int it = 0; it < 200; ++it) run_pair(m, PAIR(fn_clndGetMoonPhase_00181b50), Args{rng() % 0x4000}, rng(), "clndGetMoonPhase beyond");
}

TEST_CASE("game(ui): datGetFlag equals its recompiled body and reads bit id % 32 of word id / 32") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{3u};
    fill_random(m, kFlagWords - 0x100, 0x2C0 + 0x200, rng);
    int set = 0;
    for (int it = 0; it < 3000; ++it) {
        const s32 id = it < 2400 ? rand_range(rng, 0, 0x15FF) : rand_range(rng, -200, 6000);
        const Pair p = run_pair(m, PAIR(fn_datGetFlag_0016f190), Args{sx(static_cast<u32>(id))}, rng(), "datGetFlag");
        const s32 word = id / 32, bit = id % 32;  // C semantics, as the compiler's fix-ups implement
        const u32 w = load32(m, kFlagWords + static_cast<u32>(word) * 4u);
        const u32 expect = (w & (1u << (static_cast<u32>(bit) & 31u))) ? 1u : 0u;
        CHECK(p.hand.v0 == expect);
        set += static_cast<int>(expect);
    }
    CHECK(set > 1000);
}

TEST_CASE("game(ui): sprFontGetFile and the H_Camp level-string tables equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11u};
    fill_random(m, kSprFontFiles, 0x40, rng);
    for (u32 i = 0; i < 16; ++i) {
        const Pair p = run_pair(m, PAIR(fn_sprFontGetFile_001120a0), Args{i}, rng(), "sprFontGetFile");
        CHECK(p.hand.v0 == sx(load32(m, kSprFontFiles + 4 * i)));
    }
    static const char* const kAcademic[7] = {"", "Slacker", "Average", "Above Average", "Smart", "Intelligent", "Genius"};
    static const char* const kCharm[7] = {"", "Plain", "Unpolished", "Confident", "Smooth", "Popular", "Charismatic"};
    static const char* const kCourage[7] = {"", "Timid", "Ordinary", "Determined", "Tough", "Fearless", "Badass"};
    for (s32 level = 1; level <= 6; ++level) {
        const u32 seed = rng();
        Pair p = run_pair(m, PAIR(fn_H_Camp_GetAcademicLevelString_0011a810), Args{sx(static_cast<u32>(level))}, seed, "H_Camp_GetAcademicLevelString");
        CHECK(m.str(static_cast<u32>(p.hand.v0)) == kAcademic[level]);
        p = run_pair(m, PAIR(fn_H_Camp_GetCharmLevelString_0011a840), Args{sx(static_cast<u32>(level))}, seed, "H_Camp_GetCharmLevelString");
        CHECK(m.str(static_cast<u32>(p.hand.v0)) == kCharm[level]);
        p = run_pair(m, PAIR(fn_H_Camp_GetCourageLevelString_0011a870), Args{sx(static_cast<u32>(level))}, seed, "H_Camp_GetCourageLevelString");
        CHECK(m.str(static_cast<u32>(p.hand.v0)) == kCourage[level]);
    }
    // Level 0 of each table is the previous table's last entry (the arrays are contiguous); slot 0 of the
    // courage table is a null pointer. Out-of-range levels index the neighbouring data like the original.
    Pair p = run_pair(m, PAIR(fn_H_Camp_GetCourageLevelString_0011a870), Args{0}, rng(), "courage level 0");
    CHECK(p.hand.v0 == 0);
    p = run_pair(m, PAIR(fn_H_Camp_GetCharmLevelString_0011a840), Args{0}, rng(), "charm level 0");
    CHECK(m.str(static_cast<u32>(p.hand.v0)) == "Badass");
    for (int it = 0; it < 300; ++it) {
        const s32 level = rand_range(rng, -8, 16);
        const u32 seed = rng();
        run_pair(m, PAIR(fn_H_Camp_GetAcademicLevelString_0011a810), Args{sx(static_cast<u32>(level))}, seed, "academic string random");
        run_pair(m, PAIR(fn_H_Camp_GetCharmLevelString_0011a840), Args{sx(static_cast<u32>(level))}, seed, "charm string random");
        run_pair(m, PAIR(fn_H_Camp_GetCourageLevelString_0011a870), Args{sx(static_cast<u32>(level))}, seed, "courage string random");
    }
}

TEST_CASE("game(ui): datGet{Academic,Charm,Courage}Level equal their recompiled bodies and the threshold rule") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{13u};
    const u32 tables[3] = {kAcademicThresholds, kCharmThresholds, kCourageThresholds};
    const Fn hands[3] = {&recomp_gen::fn_datGetAcademicLevel_00177280, &recomp_gen::fn_datGetCharmLevel_001772f0, &recomp_gen::fn_datGetCourageLevel_00177360};
    const Fn recomps[3] = {&recomp_gen::fn_datGetAcademicLevel_00177280__recomp, &recomp_gen::fn_datGetCharmLevel_001772f0__recomp,
                           &recomp_gen::fn_datGetCourageLevel_00177360__recomp};
    int levels[7] = {};
    for (int it = 0; it < 1500; ++it) {
        const int t = it % 3;
        s16 thr[7];
        std::memcpy(thr, m.at(tables[t]), sizeof thr);
        // Around the thresholds (never below 0: negative points walk the search into the data before the
        // table through negative s16 indices -- both bodies do, but the rule below does not model it).
        const s32 points = (it % 5 == 0) ? thr[rand_range(rng, 1, 6)] + rand_range(rng, -1, 1) : rand_range(rng, 0, 1100);
        const Pair p = run_pair(m, hands[t], recomps[t], Args{sx(static_cast<u32>(points))}, rng(), "datGet*Level");
        s32 expect = 1;
        for (int i = 5; i >= 0; --i) {
            if (points >= thr[i]) {
                expect = i + 1;
                break;
            }
        }
        CHECK(p.hand.v0 == sx(static_cast<u32>(expect)));
        ++levels[expect];
    }
    for (int l = 1; l <= 6; ++l) CHECK(levels[l] > 0);
}

TEST_CASE("game(ui): the H_Cursor setters equal their recompiled bodies and store into the work record") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{17u};
    constexpr u32 kTask = kArena + 0x40;
    constexpr u32 kWork = kArena + 0x100;
    constexpr u32 kRect = kArena + 0x300;
    store32(m, kTask + kTaskWorkData, kWork);
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kWork, sizeof(p3fes::game::HCursorWork), rng);
        fill_random(m, kRect, 16, rng);
        const u32 x = rng(), y = rng(), z = rng(), rgba = rng();
        const u32 seed = rng();
        Pair p = run_pair(m, PAIR(fn_H_Cursor_SetPos_00100710), Args{kTask, (static_cast<u64>(y) << 32) | x}, seed, "H_Cursor_SetPos");
        CHECK(load32(m, kWork + 0x114) == x);
        CHECK(load32(m, kWork + 0x118) == y);
        p = run_pair(m, PAIR(fn_H_Cursor_SetRect_00100740), Args{kTask, kRect}, seed, "H_Cursor_SetRect");
        for (u32 i = 0; i < 4; ++i) CHECK(load32(m, kWork + 0x11C + 4 * i) == load32(m, kRect + 4 * i));
        {
            const Outcome hand = run_f12(m, &recomp_gen::fn_H_Cursor_SetZOffset_00100770, Args{kTask}, seed, z);
            const Outcome recomp = run_f12(m, &recomp_gen::fn_H_Cursor_SetZOffset_00100770__recomp, Args{kTask}, seed, z);
            expect_same(hand, recomp, "H_Cursor_SetZOffset");
            CHECK(load32(m, kWork + 0x12C) == z);
        }
        p = run_pair(m, PAIR(fn_H_Cursor_SetColor_00100780), Args{kTask, rgba}, seed, "H_Cursor_SetColor");
        for (u32 v = 0; v < 4; ++v) CHECK(load32(m, kWork + 0x130 + 4 * v) == rgba);
        // the setters touch nothing else in the record
        (void)p;
    }
}

#else

TEST_CASE("game(ui): menu/UI replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
