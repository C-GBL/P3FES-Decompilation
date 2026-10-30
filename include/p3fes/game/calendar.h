// Phase 5 slice calendar: the calendar and time system of clnd.c (band 0x17D7C0-0x18A000) and the rest of
// datPersona.c / g_data.c (0x176210-0x177DB0, 0x17AC60-0x17C2F0). The bodies (game/src/calendar/calendar.cpp) are
// p3fes_handgen's, register for register as the recompiled bodies; their roles and the state below are this slice's
// reading of the instructions, checked on the replay snapshots (tests/game/test_calendar.cpp).
//
// =====================================================================================================================
// WHAT THE CALENDAR KEEPS WHERE (for the multiplayer server, which will drive the in-game date and time from the real
// clock). Every address is the ELF's (.bss / .data), the same in every run.
// =====================================================================================================================
//
// 1. The date and the time of day (gGlobalWork 0x836200; ui2.h has the accessors):
//      0x83679C  s16  days since April 5 (+0x59C). Day 0 = Sunday, April 5, 2009; day 360 = March 31, 2010 (the month
//                     table has 365 days, the pickers clamp to 0..364). Real date = 2009-04-05 + day; weekday =
//                     (day + 7) % 7 with 0 = Sunday (clndGetWeekDay). Read: datGetDaysSinceApr5 0x16EF20.
//                     WRITE THROUGH datSetDaysSinceApr5 0x16EF70, not a plain store: it also sets the weekday flags
//                     0xA08..0xA0E (one-hot, Sunday first) and 0xA0F (holiday or Sunday), and on a change of date runs
//                     the day-change resets sub_172890 / sub_172E10 and clears flag 0x98C.
//      0x83679E  u8   the time slot (+0x59E), datGetTime 0x16EF30 / sub_16F150 [datSetTime]:
//                     0 SOUCHOU early morning, 1 ASA morning, 2 GOZEN forenoon (classes), 3 HIRUYASUMI lunch break,
//                     4 GOGO afternoon, 5 HOUKAGO after school, 6 YORU evening, 7 SINYA late night, 8 "25" the Dark
//                     Hour (kSlot* below; the names are the debug strings of sub_17E680).
//      0x8367A0  u32  time skip active (sub_16EF60 / sub_16F180), 0x8367A4 s16 its target day (sub_16EF40 /
//                     sub_16F160), 0x8367A6 u8 its target slot (sub_16EF50 / sub_16F170): set by a scheduled event
//                     (sub_181950: the row's month / day / slot) and by the early-morning slot (sub_180A20: now).
//    The script command sub_188510 [clndScrCmd_SET_DATE] is the model of a "set the clock" operation:
//    datSetDaysSinceApr5(clndGetDaysSinceStartFromDate(month, day)); sub_16F150(slot).
//
// 2. How time advances (the "CalenderDraw" task sub_17E680, state 22, once per finished slot):
//      - a time skip whose target is >= 6 days ahead, or reached, jumps to the target and ends the skip;
//      - Dark Hour (8) -> slot 0 of day + 1 (datSetDaysSinceApr5(day + 1));
//      - on a school Saturday (weekday 6 and not sub_17DB40) GOZEN (2) -> HOUKAGO (5);
//      - on a holiday or Sunday (sub_17DB40) ASA (1) -> GOGO (4) and GOGO (4) -> YORU (6);
//      - otherwise slot + 1; leaving ASA clears the morning flags (sub_180E60).
//    Each slot then runs its sequence (state 13): today's scheduled event if one matches (sub_181720 / sub_181950),
//    else the social timer task (comu_CreateComuTimerProcessTask) -- see the per-slot functions below.
//
// 3. Day-change processing (the first ASA call of a day, sub_180C40):
//      flags 0xBD0..0xBFF, 0xA01, 0xA02, 0xA04 cleared; the party records' {u16, u16} pair rows reloaded (0x5E3C20);
//      the dated flag rows applied (sub_3BD8A0: {u8 month, u8 day, u16 set flag, u16 clear flag}); sub_1B7700;
//      then, once each: the daily condition step (sub_180220, flag 0x1406) with sub_1A5CD0, and the dated conditions
//      (sub_180030, flag 0x1405: rows {month, day, pc, condition} of sub_3BD890).
//      Party conditions: u16 +0x6C of gGlobalWork (hero) / +0x4C of the records (gamedata.h); counters 0x83A4DC
//      (s32[128], sub_16F380 / sub_16F3E0): pc + 15 the condition countdown, pc + 25 a fatigue counter (>= 100
//      forces condition 2), 53 the dungeon floor to return to.
//
// 4. Flags (the bit array 0x83A21C, datGetFlag 0x16F190 / datSetFlag 0x16F1F0) the calendar sets:
//      0xA80..0xA87  the running slot's sequence (one-hot; SOUCHOU clears all, ASA 0xA80 .. YORU 0xA85, the Dark Hour
//                    0xA87; SINYA sets none)
//      0xA00..0xA05  sequence control (0xA00 ends the early-morning slot at once, 0xA01 the evening slot (and is
//                    cleared), 0xA02 the late-night slot, 0xA03 a Dark Hour event pending, 0xA05 go to the dungeon at the Dark Hour)
//      0x1402..0x1406 the morning steps done today (0x1402 new day reset, 0x1403 early-morning skip target, 0x1405
//                    dated conditions, 0x1406 daily conditions); 0x1410 a slot sequence ran; 0x1412 the Dark Hour
//                    effect ran; 0x141C conditions changed (the condition message is due); 0x141D the calendar started
//      0xA95..0xA9F, 0xA7A, 0xACD, 0xACE  the hero's condition messages (sub_1871A0 shows one and clears them)
//
// 5. Tables (read-only, in the ELF):
//      tbl_clndMonthLengths 0x5E3B60  s16[12], January first: 31 28 31 30 31 30 31 31 30 31 30 31 (365)
//      tbl_clndHolidays     0x5E3A40  {s16 month, s16 day}, -1 ends, searched up to 356 entries; retail has 71:
//                                     4/29, 5/4, 5/5, 7/20-7/23, 7/26-8/31, 9/21-9/23, 10/12, 11/3, 11/17-11/20,
//                                     11/23, 12/23, 12/27-1/7, 1/10, 1/11, 2/11, 3/22 (Sundays are holidays by rule)
//      tbl_clndMoonPhase    0x5E38D0  u8[368], one per day: 0..29, 0 = new moon, 14 = full moon (days 4, 34, 64,
//                                     93, 123, 153, 182, 212, 241, 270, 301, 329, 359 = 4/9, 5/9, 6/8, 7/7, 8/6,
//                                     9/5, 10/4, 11/3, 12/2, 12/31, 1/31, 2/28, 3/30); clndGetMoonPhase 0x181B50
//      the scheduled events      *sub_3BD880()  {u32 rows, s32 count}, 24-byte rows (sub_181720's comment)
//      The Answer's day sequence 0x83AB30      40-byte rows, index 0x83A6F8 (sub_181CC0's comment)
//
// 6. Other state the slice's functions touch: 0x7CDFEC the calendar task (0 when none), 0x7CDFF0 / 0x7CDFF8 the
//    day-part HUD, 0x7CDFFC a pending return to the field, 0x83A6EC / 0x83A6F0 the field to return to (major /
//    minor), 0x83A6F4 non-zero: return to the dungeon instead, 0x7CDFA4 the scenario (0 The Journey, 1 The Answer).
// =====================================================================================================================
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace calendar {

// --- the date and the time of day (gGlobalWork 0x836200) ------------------------------------------------------------
inline constexpr u32 kGlobalWork = 0x836200u;
inline constexpr u32 kDaysSinceApr5 = 0x83679Cu;   // s16 (+0x59C)
inline constexpr u32 kTimeSlot = 0x83679Eu;        // u8  (+0x59E)
inline constexpr u32 kSkipActive = 0x8367A0u;      // u32 (+0x5A0)
inline constexpr u32 kSkipDay = 0x8367A4u;         // s16 (+0x5A4)
inline constexpr u32 kSkipSlot = 0x8367A6u;        // u8  (+0x5A6)
inline constexpr u32 kAigisRow = 0x83A6F8u;        // s32 (+0x44F8, sub_17D810 / sub_17D820)
inline constexpr u32 kReturnFieldMajor = 0x83A6ECu, kReturnFieldMinor = 0x83A6F0u, kReturnToDungeon = 0x83A6F4u;
inline constexpr u32 kFlagWords = 0x83A21Cu;       // u32[176], datGetFlag / datSetFlag
inline constexpr u32 kCounters = 0x83A4DCu;        // s32[128], sub_16F380 / sub_16F3E0

// --- the tables --------------------------------------------------------------------------------------------------------
inline constexpr u32 kMonthLengths = 0x5E3B60u;    // s16[12], January first
inline constexpr u32 kHolidays = 0x5E3A40u;        // {s16 month, s16 day}[], -1 ends
inline constexpr s32 kHolidayScanMax = 356;
inline constexpr u32 kMoonPhases = 0x5E38D0u;      // u8[368]
inline constexpr u32 kAigisDays = 0x83AB30u;       // 40-byte rows
inline constexpr s32 kAigisDaySize = 40;

// --- calendar facts ----------------------------------------------------------------------------------------------------
inline constexpr s32 kFirstMonth = 4;              // the month walk starts in April
inline constexpr s32 kStartDayOfMonth = 5;         // day 0 = April 5 (2009, a Sunday)
inline constexpr s32 kFirstOfAprilWeekday = 3;     // April 1, 2009 was a Wednesday (sub_17E050)
inline constexpr s32 kLastDay = 364;               // the date pickers clamp to 0..364
inline constexpr s32 kNextHolidayLimit = 351;      // sub_17DDF0 stops before day 351 (March 22)
inline constexpr s32 kFullMoon = 14, kNewMoon = 0;

// time slots (gGlobalWork +0x59E)
inline constexpr s32 kSlotSouchou = 0, kSlotAsa = 1, kSlotGozen = 2, kSlotHiruyasumi = 3, kSlotGogo = 4,
                     kSlotHoukago = 5, kSlotYoru = 6, kSlotSinya = 7, kSlotDarkHour = 8;
// weekdays ((day + 7) % 7)
inline constexpr s32 kSunday = 0, kSaturday = 6;
// sub_17E050's date codes
inline constexpr s32 kCodeWeekday = 101, kCodeHoliday = 100, kCodeDate = 0;

// flags
inline constexpr s32 kFlagSlotFirst = 0xA80;       // 0xA80..0xA87: the running slot's sequence
inline constexpr s32 kFlagMorningFirst = 0x1402;   // 0x1402..0x1406: the morning steps done today
inline constexpr s32 kFlagConditionMessage = 0x141C;
inline constexpr s32 kFlagCalendarStarted = 0x141D;
inline constexpr s32 kFlagDarkHourShown = 0x1412;
inline constexpr s32 kFlagSlotRan = 0x1410;
inline constexpr s32 kFlagNewDayClearFirst = 0xBD0, kFlagNewDayClearLast = 0xBFF;

// counters (kCounters)
inline constexpr s32 kCounterConditionBase = 15;   // pc + 15: the condition countdown
inline constexpr s32 kCounterFatigueBase = 25;     // pc + 25
inline constexpr s32 kCounterDungeonFloor = 53;

// the "CalenderDraw" task work (44 bytes, KwlnTask +0x3C)
namespace task {
inline constexpr s32 kState = 0x0, kCursorA = 0x4, kCursorB = 0x8, kSequenceTask = 0xC, kDayPartsTask = 0x10,
                     kCountdown = 0x20, kAdvance = 0x24;
inline constexpr s32 kWork = 0x3C;                 // KwlnTask +0x3C: the work pointer
inline constexpr s32 kStateAdvance = 22;           // the time-advance state
}  // namespace task

// the scheduled-event row (24 bytes, sub_181720 / sub_181950)
namespace event {
inline constexpr s32 kMonth = 0, kDay = 1, kSlot = 2, kId = 4, kMajor = 6, kMinor = 7, kSkipMonth = 8, kSkipDay = 9,
                     kSkipSlot = 10, kComu = 11, kComuRank = 12, kFlagSet1 = 14, kFlagSet2 = 16, kFlagClear1 = 18,
                     kFlagClear2 = 20, kDoneFlag = 22, kSize = 24;
}  // namespace event

// The real calendar date of a day (host side; tests and a future server): date_of_day for day 0..364 (361..364 are
// April 1..4 again), day_of_date (clndGetDaysSinceStartFromDate's walk) for April 5..March 31 (April 1..4 give -4..-1).
struct Date {
    s32 month, day;
};
constexpr s32 kMonthLen[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
constexpr Date date_of_day(s32 d) {
    s32 m = kFirstMonth, rem = d + (kStartDayOfMonth - 1);
    while (rem >= kMonthLen[m - 1]) {
        rem -= kMonthLen[m - 1];
        m = m == 12 ? 1 : m + 1;
    }
    return {m, rem + 1};
}
constexpr s32 day_of_date(s32 month, s32 day) {
    s32 sum = 0;
    for (s32 m = kFirstMonth; m != month; m = m == 12 ? 1 : m + 1) sum += kMonthLen[m - 1];
    return sum + day - kStartDayOfMonth;
}
constexpr s32 weekday_of_day(s32 d) { return (d + 7) % 7; }
static_assert(date_of_day(0).month == 4 && date_of_day(0).day == 5 && day_of_date(5, 1) == 26 && day_of_date(1, 1) == 271);
static_assert(date_of_day(360).month == 3 && date_of_day(360).day == 31);

}  // namespace calendar

// --- the register-ABI bodies (arguments in $a0.., the result in $v0; game/src/calendar/calendar.cpp) -------------
void sub_176210(EEContext& ctx);  // 0x176210 (register ABI: arguments in $a0.., the result in $v0)
void sub_1764B0(EEContext& ctx);  // 0x1764B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_176510(EEContext& ctx);  // 0x176510 (register ABI: arguments in $a0.., the result in $v0)
void sub_176600(EEContext& ctx);  // 0x176600 (register ABI: arguments in $a0.., the result in $v0)
void sub_176680(EEContext& ctx);  // 0x176680 (register ABI: arguments in $a0.., the result in $v0)
void sub_176840(EEContext& ctx);  // 0x176840 (register ABI: arguments in $a0.., the result in $v0)
void sub_1768E0(EEContext& ctx);  // 0x1768E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_176990(EEContext& ctx);  // 0x176990 (register ABI: arguments in $a0.., the result in $v0)
void sub_176A30(EEContext& ctx);  // 0x176A30 (register ABI: arguments in $a0.., the result in $v0)
void sub_176AC0(EEContext& ctx);  // 0x176AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_176C80(EEContext& ctx);  // 0x176C80 (register ABI: arguments in $a0.., the result in $v0)
void sub_176D10(EEContext& ctx);  // 0x176D10 (register ABI: arguments in $a0.., the result in $v0)
void sub_176DA0(EEContext& ctx);  // 0x176DA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_176FB0(EEContext& ctx);  // 0x176FB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1770D0(EEContext& ctx);  // 0x1770D0 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_4(EEContext& ctx);  // 0x177270 (register ABI: arguments in $a0.., the result in $v0)
void sub_1773D0(EEContext& ctx);  // 0x1773D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_177410(EEContext& ctx);  // 0x177410 (register ABI: arguments in $a0.., the result in $v0)
void sub_1774E0(EEContext& ctx);  // 0x1774E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1775A0(EEContext& ctx);  // 0x1775A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_177670(EEContext& ctx);  // 0x177670 (register ABI: arguments in $a0.., the result in $v0)
void sub_177790(EEContext& ctx);  // 0x177790 (register ABI: arguments in $a0.., the result in $v0)
void sub_1778B0(EEContext& ctx);  // 0x1778B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1779A0(EEContext& ctx);  // 0x1779A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_177A40(EEContext& ctx);  // 0x177A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_177A90(EEContext& ctx);  // 0x177A90 (register ABI: arguments in $a0.., the result in $v0)
void sub_177B50(EEContext& ctx);  // 0x177B50 (register ABI: arguments in $a0.., the result in $v0)
void sub_177B90(EEContext& ctx);  // 0x177B90 (register ABI: arguments in $a0.., the result in $v0)
void sub_177C10(EEContext& ctx);  // 0x177C10 (register ABI: arguments in $a0.., the result in $v0)
void sub_177C50(EEContext& ctx);  // 0x177C50 (register ABI: arguments in $a0.., the result in $v0)
void sub_177CA0(EEContext& ctx);  // 0x177CA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_177CE0(EEContext& ctx);  // 0x177CE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_177D10(EEContext& ctx);  // 0x177D10 (register ABI: arguments in $a0.., the result in $v0)
void sub_177D40(EEContext& ctx);  // 0x177D40 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AC60(EEContext& ctx);  // 0x17AC60 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AD90(EEContext& ctx);  // 0x17AD90 (register ABI: arguments in $a0.., the result in $v0)
void sub_17ADF0(EEContext& ctx);  // 0x17ADF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AE30(EEContext& ctx);  // 0x17AE30 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AE50(EEContext& ctx);  // 0x17AE50 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AF20(EEContext& ctx);  // 0x17AF20 (register ABI: arguments in $a0.., the result in $v0)
void sub_17AFD0(EEContext& ctx);  // 0x17AFD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B070(EEContext& ctx);  // 0x17B070 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B100(EEContext& ctx);  // 0x17B100 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B160(EEContext& ctx);  // 0x17B160 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B170(EEContext& ctx);  // 0x17B170 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B180(EEContext& ctx);  // 0x17B180 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B1A0(EEContext& ctx);  // 0x17B1A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B1E0(EEContext& ctx);  // 0x17B1E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B220(EEContext& ctx);  // 0x17B220 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B260(EEContext& ctx);  // 0x17B260 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B2A0(EEContext& ctx);  // 0x17B2A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B2E0(EEContext& ctx);  // 0x17B2E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B3D0(EEContext& ctx);  // 0x17B3D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B480(EEContext& ctx);  // 0x17B480 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B4E0(EEContext& ctx);  // 0x17B4E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B500(EEContext& ctx);  // 0x17B500 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B5B0(EEContext& ctx);  // 0x17B5B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17B660(EEContext& ctx);  // 0x17B660 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BB40(EEContext& ctx);  // 0x17BB40 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BBB0(EEContext& ctx);  // 0x17BBB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BC20(EEContext& ctx);  // 0x17BC20 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BE10(EEContext& ctx);  // 0x17BE10 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BF70(EEContext& ctx);  // 0x17BF70 (register ABI: arguments in $a0.., the result in $v0)
void sub_17BFA0(EEContext& ctx);  // 0x17BFA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C070(EEContext& ctx);  // 0x17C070 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C0E0(EEContext& ctx);  // 0x17C0E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C190(EEContext& ctx);  // 0x17C190 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C1C0(EEContext& ctx);  // 0x17C1C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C220(EEContext& ctx);  // 0x17C220 (register ABI: arguments in $a0.., the result in $v0)
void sub_17C280(EEContext& ctx);  // 0x17C280 (register ABI: arguments in $a0.., the result in $v0)
void sub_17D7C0(EEContext& ctx);  // 0x17D7C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17D7F0(EEContext& ctx);  // 0x17D7F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17DDF0(EEContext& ctx);  // 0x17DDF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17E050(EEContext& ctx);  // 0x17E050 (register ABI: arguments in $a0.., the result in $v0)
void sub_17E680(EEContext& ctx);  // 0x17E680 (register ABI: arguments in $a0.., the result in $v0)
void sub_17F8D0(EEContext& ctx);  // 0x17F8D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FA10(EEContext& ctx);  // 0x17FA10 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FAA0(EEContext& ctx);  // 0x17FAA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FAD0(EEContext& ctx);  // 0x17FAD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FB90(EEContext& ctx);  // 0x17FB90 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FC70(EEContext& ctx);  // 0x17FC70 (register ABI: arguments in $a0.., the result in $v0)
void sub_17FE10(EEContext& ctx);  // 0x17FE10 (register ABI: arguments in $a0.., the result in $v0)
void sub_180030(EEContext& ctx);  // 0x180030 (register ABI: arguments in $a0.., the result in $v0)
void sub_180220(EEContext& ctx);  // 0x180220 (register ABI: arguments in $a0.., the result in $v0)
void sub_180A20(EEContext& ctx);  // 0x180A20 (register ABI: arguments in $a0.., the result in $v0)
void sub_180C40(EEContext& ctx);  // 0x180C40 (register ABI: arguments in $a0.., the result in $v0)
void sub_180E60(EEContext& ctx);  // 0x180E60 (register ABI: arguments in $a0.., the result in $v0)
void sub_180EE0(EEContext& ctx);  // 0x180EE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_181010(EEContext& ctx);  // 0x181010 (register ABI: arguments in $a0.., the result in $v0)
void sub_181170(EEContext& ctx);  // 0x181170 (register ABI: arguments in $a0.., the result in $v0)
void sub_181310(EEContext& ctx);  // 0x181310 (register ABI: arguments in $a0.., the result in $v0)
void sub_181430(EEContext& ctx);  // 0x181430 (register ABI: arguments in $a0.., the result in $v0)
void sub_181580(EEContext& ctx);  // 0x181580 (register ABI: arguments in $a0.., the result in $v0)
void sub_181720(EEContext& ctx);  // 0x181720 (register ABI: arguments in $a0.., the result in $v0)
void sub_181950(EEContext& ctx);  // 0x181950 (register ABI: arguments in $a0.., the result in $v0)
void sub_181B70(EEContext& ctx);  // 0x181B70 (register ABI: arguments in $a0.., the result in $v0)
void sub_181CC0(EEContext& ctx);  // 0x181CC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_182720(EEContext& ctx);  // 0x182720 (register ABI: arguments in $a0.., the result in $v0)
void sub_182750(EEContext& ctx);  // 0x182750 (register ABI: arguments in $a0.., the result in $v0)
void sub_182810(EEContext& ctx);  // 0x182810 (register ABI: arguments in $a0.., the result in $v0)
void sub_1828D0(EEContext& ctx);  // 0x1828D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_182C50(EEContext& ctx);  // 0x182C50 (register ABI: arguments in $a0.., the result in $v0)
void sub_182D90(EEContext& ctx);  // 0x182D90 (register ABI: arguments in $a0.., the result in $v0)
void sub_1830C0(EEContext& ctx);  // 0x1830C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1831E0(EEContext& ctx);  // 0x1831E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1833E0(EEContext& ctx);  // 0x1833E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_184890(EEContext& ctx);  // 0x184890 (register ABI: arguments in $a0.., the result in $v0)
void H_DayParts_CreateTask(EEContext& ctx);  // 0x184DB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_184F00(EEContext& ctx);  // 0x184F00 (register ABI: arguments in $a0.., the result in $v0)
void sub_185830(EEContext& ctx);  // 0x185830 (register ABI: arguments in $a0.., the result in $v0)
void sub_185880(EEContext& ctx);  // 0x185880 (register ABI: arguments in $a0.., the result in $v0)
void sub_185980(EEContext& ctx);  // 0x185980 (register ABI: arguments in $a0.., the result in $v0)
void sub_185AE0(EEContext& ctx);  // 0x185AE0 (register ABI: arguments in $a0.., the result in $v0)
void H_DayChgDraw_DrawStrip(EEContext& ctx);  // 0x185B40 (register ABI: arguments in $a0.., the result in $v0)
void sub_186050(EEContext& ctx);  // 0x186050 (register ABI: arguments in $a0.., the result in $v0)
void sub_186100(EEContext& ctx);  // 0x186100 (register ABI: arguments in $a0.., the result in $v0)
void sub_186140(EEContext& ctx);  // 0x186140 (register ABI: arguments in $a0.., the result in $v0)
void sub_186190(EEContext& ctx);  // 0x186190 (register ABI: arguments in $a0.., the result in $v0)
void sub_1868F0(EEContext& ctx);  // 0x1868F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_186960(EEContext& ctx);  // 0x186960 (register ABI: arguments in $a0.., the result in $v0)
void sub_186A40(EEContext& ctx);  // 0x186A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_186BD0(EEContext& ctx);  // 0x186BD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_186D50(EEContext& ctx);  // 0x186D50 (register ABI: arguments in $a0.., the result in $v0)
void sub_187050(EEContext& ctx);  // 0x187050 (register ABI: arguments in $a0.., the result in $v0)
void sub_1870E0(EEContext& ctx);  // 0x1870E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1871A0(EEContext& ctx);  // 0x1871A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_187520(EEContext& ctx);  // 0x187520 (register ABI: arguments in $a0.., the result in $v0)
void sub_187550(EEContext& ctx);  // 0x187550 (register ABI: arguments in $a0.., the result in $v0)
void sub_187DF0(EEContext& ctx);  // 0x187DF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_187E20(EEContext& ctx);  // 0x187E20 (register ABI: arguments in $a0.., the result in $v0)
void sub_187EC0(EEContext& ctx);  // 0x187EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1883D0(EEContext& ctx);  // 0x1883D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_188440(EEContext& ctx);  // 0x188440 (register ABI: arguments in $a0.., the result in $v0)
void sub_188510(EEContext& ctx);  // 0x188510 (register ABI: arguments in $a0.., the result in $v0)
void sub_1885A0(EEContext& ctx);  // 0x1885A0 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_5(EEContext& ctx);  // 0x188650 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_6(EEContext& ctx);  // 0x188670 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_7(EEContext& ctx);  // 0x188680 (register ABI: arguments in $a0.., the result in $v0)
void clndUpdateBootupCheckMemcardTask(EEContext& ctx);  // 0x188690 (register ABI: arguments in $a0.., the result in $v0)
void sub_188830(EEContext& ctx);  // 0x188830 (register ABI: arguments in $a0.., the result in $v0)
void sub_188860(EEContext& ctx);  // 0x188860 (register ABI: arguments in $a0.., the result in $v0)
void sub_188900(EEContext& ctx);  // 0x188900 (register ABI: arguments in $a0.., the result in $v0)
void sub_188B20(EEContext& ctx);  // 0x188B20 (register ABI: arguments in $a0.., the result in $v0)
void sub_188B50(EEContext& ctx);  // 0x188B50 (register ABI: arguments in $a0.., the result in $v0)
void sub_188C30(EEContext& ctx);  // 0x188C30 (register ABI: arguments in $a0.., the result in $v0)
void sub_189230(EEContext& ctx);  // 0x189230 (register ABI: arguments in $a0.., the result in $v0)
void sub_189810(EEContext& ctx);  // 0x189810 (register ABI: arguments in $a0.., the result in $v0)
void sub_189DF0(EEContext& ctx);  // 0x189DF0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
