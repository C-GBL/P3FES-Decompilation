// Menu / UI layer, second wave (slice ui2), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md):
// the remaining calendar / holiday / moon helpers, the flag-bit setters and wrappers, the day-skip and
// counter accessors of g_data.c, the social-stat point getters/setters, the camp list cursor, the small
// task-record accessors of the UI and the event/itemtbl.bin section slicer with its record lookups.
//
// Names: the IDA names of symbols/functions.json as they are now. Functions still `sub_<addr>` there keep
// that name; the proposed name is given in brackets in the comments (no delta file yet).
// Globals addressed through $gp are given as absolute addresses ($gp = 0x7D2CF0, crt0).
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

namespace ui2 {

// --- g_data.c (gGlobalWork 0x836200) -------------------------------------------------------------------
inline constexpr u32 kDaysSinceApr5 = 0x83679Cu;      // s16 (ui::kDaysSinceApr5)
inline constexpr u32 kTimeOfDay = 0x83679Eu;          // u8 (datGetTime / sub_16F150)
inline constexpr u32 kSkipToTarget = 0x8367A0u;       // u32 (sub_16EF60 / sub_16F180)
inline constexpr u32 kDaysSkipTarget = 0x8367A4u;     // s16 (sub_16EF40 / sub_16F160)
inline constexpr u32 kTimeSkipTarget = 0x8367A6u;     // u8  (sub_16EF50 / sub_16F170)
inline constexpr u32 kFlagWords = 0x83A21Cu;          // u32[176], 5,632 flag bits (ui::kFlagWords)
inline constexpr s32 kFlagCount = 0x1600;             // datSetFlag asserts 0 <= id < 0x1600
inline constexpr s32 kFlagWordCount = 176;
inline constexpr u32 kCounters = 0x83A4DCu;           // u32[128] indexed counters (sub_16F380 / sub_16F3E0); sub_16F450 zeroes 127 of them
inline constexpr u32 kProtagonistStats = 0x836260u;   // s16 {academic, charm, courage}: character 1, the protagonist
inline constexpr u32 kCharacterStats = 0x833988u;     // s16 {academic, charm, courage} at + 868 * character for the others
inline constexpr u32 kCharacterStride = 868u;
inline constexpr u32 kAigisCalendarState = 0x83A6F8u;  // u32 (sub_17D810 / sub_17D820)
inline constexpr u32 kGDataSourceFile = 0x5E3098u;    // "g_data.c", the K_Assert file argument
inline constexpr u32 kHitString = 0x7CBFA8u;          // "hit \n" ($gp - 0x6D48), printed by datSetFlag for flag 0x1376
inline constexpr s32 kHitFlag = 0x1376;
inline constexpr u32 kScenarioMode = 0x7CDFA4u;       // u32 $gp - 0x4D4C: 0 = The Journey, 1 = The Answer (sub_17D800)

// Weekday flags set by datSetDaysSinceApr5 (jump table 0x7B6460, weekday 0 = Sunday).
inline constexpr s32 kWeekdayFlagFirst = 0xA08;  // 0xA08 Monday .. 0xA0D Saturday, 0xA0E Sunday
inline constexpr s32 kHolidayFlag = 0xA0F;       // set when clndIsHolidayOrSunday() after the store
inline constexpr s32 kDayChangedFlag = 0x98C;    // cleared when the date actually changes

// --- datCalendar ----------------------------------------------------------------------------------------
inline constexpr u32 kMonthLengths = 0x5E3B60u;    // s16[12] (ui::kMonthLengths)
inline constexpr u32 kMoonPhaseTable = 0x5E38D0u;  // u8[368] (ui::kMoonPhaseTable)
inline constexpr u32 kHolidays = 0x5E3A40u;        // s16 {month, day}[], -1-terminated; at most 356 entries are scanned
inline constexpr s32 kHolidayScanLimit = 356;
inline constexpr u32 kRangeZeroString = 0x5E3B80u;  // "Calender chk range is 0 " (clndIsDateInRangeFromStart)

// --- pad words read by H_Camp_MoveListCursor (20_menu_ui.md section 4.1) ---------------------------------
inline constexpr u32 kPadHeld = 0x7E094Eu;      // gPadFlags (the wrap-around tests)
inline constexpr u32 kPadPressed = 0x7E0952u;   // newly pressed: 0x1000 / 0x4000 move, 0x1 / 0x2 page
inline constexpr u32 kPadRepeatHeld = 0x7E0958u;
inline constexpr u32 kPadRepeat = 0x7E095Au;    // repeat-generator edge
inline constexpr u32 kPadUp = 0x1000u;          // moves toward index 0 (the SCE pad's up bit)
inline constexpr u32 kPadDown = 0x4000u;
inline constexpr u32 kPadPagePrev = 0x1u;
inline constexpr u32 kPadPageNext = 0x2u;

// --- other UI globals -----------------------------------------------------------------------------------
inline constexpr u32 kMemcardChkAreaSeq[3] = {0x7CE03Cu, 0x7CE038u, 0x7CE034u};  // $gp - 0x4CB4 / -0x4CB8 / -0x4CBC
inline constexpr u32 kSflCursorWork = 0x7CE360u;  // $gp - 0x4990: the shuffle-time card cursor's work pointer

// --- event/itemtbl.bin (20_menu_ui.md section 6) --------------------------------------------------------
// The file is copied whole to kItemTbl. It is 13 sections {u32 count, u32, u32, u32; record[count]} and a
// 14th header followed by 35 records of 32 bytes. datItemTblSetSections stores the address of each
// section's first record in a $gp slot, in this order, and the 35 record addresses in kItemTblTail.
inline constexpr u32 kItemTbl = 0x83BB30u;
inline constexpr u32 kItemTblTail = 0x83AAA0u;  // u32[35]
inline constexpr u32 kItemTblTailCount = 35;
inline constexpr u32 kItemTblSections = 13;
inline constexpr u32 kItemTblSectionSlot[kItemTblSections] = {
    0x7CDFE4u, 0x7CDFE0u, 0x7CDFDCu, 0x7CDFD8u, 0x7CDFD4u, 0x7CDFD0u, 0x7CDFCCu,
    0x7CDFC4u, 0x7CDFC0u, 0x7CDFBCu, 0x7CDFB4u, 0x7CDFC8u, 0x7CDFB8u};
inline constexpr u32 kItemTblRecordSize[kItemTblSections] = {40, 16, 32, 32, 36, 28, 28, 16, 32, 20, 32, 8, 12};

// --- record offsets -------------------------------------------------------------------------------------
inline constexpr u32 kTaskTimer = 0x28;     // kwlnTask +0x28 (kwlnTaskGetTimer)
inline constexpr u32 kTaskWorkData = 0x3C;  // kwlnTask +0x3C (kwlnTaskGetWorkData)

}  // namespace ui2

// The sprite handle fields sprGetSpriteWidth / sprGetSpriteHeight read (sprCreateHandle 0x1158B0 allocates
// 0x34 bytes; 20_menu_ui.md section 5.1).
struct SprHandle {
    u8 pad0[8];      // +0x00
    u32 file;        // +0x08 SprFile*
    s32 sprite;      // +0x0C sprite index into the file's 128-byte sprite records
    u8 pad10[0x18];  // +0x10
    u16 scale_x;     // +0x28 4.12 fixed point, 0 = 1.0
    u16 scale_y;     // +0x2A
    u8 pad2c[8];     // +0x2C
};
static_assert(sizeof(SprHandle) == 0x34 && offsetof(SprHandle, file) == 8 && offsetof(SprHandle, sprite) == 0xC &&
              offsetof(SprHandle, scale_x) == 0x28 && offsetof(SprHandle, scale_y) == 0x2A);
inline constexpr u32 kSprFileSprites = 0x184;    // SprFile +0x184: base of the 128-byte sprite records
inline constexpr u32 kSprRecordSize = 0x80;
inline constexpr u32 kSprRecordU0 = 0x54, kSprRecordV0 = 0x58, kSprRecordU1 = 0x5C, kSprRecordV1 = 0x60;
inline constexpr u32 kSprRecordWidth = 0x74, kSprRecordHeight = 0x76;  // s16 overrides, 0 = use u1 - u0 / v1 - v0

// --- small accessors (game/src/ui/ui2.cpp) -----------------------------------------------------------
void H_Cursor_GetShouldDraw(EEContext& ctx);  // [register ABI] 0x100570: &work->should_draw (work + 0x140)
void sprFileIsReady(EEContext& ctx);  // [register ABI] 0x111F30: (s16)file->state == 5
void H_Camp_GetRootSelection(EEContext& ctx);  // [register ABI] 0x11B9A0: work +0xC
void H_DayPartsDraw_IsIdle(EEContext& ctx);  // [register ABI] 0x184D90: work->state == 2
// The three kwln accessors below are defined by the task-system slice (src/kwln/task.cpp, task.h).
u32 kwlnTaskGetTimer(EEContext& ctx, u32 task);         // 0x195520: task +0x28
void kwlnTaskSetWorkData(EEContext& ctx, u32 task, u32 work);  // 0x195530: task +0x3C = work
u32 kwlnTaskGetWorkData(EEContext& ctx, u32 task);      // 0x195540: task +0x3C
u32 sub_17D800(EEContext& ctx);                         // 0x17D800 [datGetScenarioMode]
u32 sub_17D810(EEContext& ctx);                         // 0x17D810: load kAigisCalendarState
void sub_17D820(EEContext& ctx);  // [register ABI] 0x17D820: store kAigisCalendarState
void H_Memcard_ClearChkAreaSeq(EEContext& ctx);         // 0x191240
void sub_25A110(EEContext& ctx);  // [register ABI] 0x25A110: *work = 0; kSflCursorWork = work
void sub_25A120(EEContext& ctx);                        // 0x25A120: kSflCursorWork = 0
void sprGetSpriteWidth(EEContext& ctx);  // [register ABI] 0x1126B0: float bits ($f0); leaves the original's $v0
void sprGetSpriteHeight(EEContext& ctx);  // [register ABI] 0x112740

// --- g_data.c day-skip accessors and counters ---------------------------------------------------------
s32 sub_16EF40(EEContext& ctx);                    // 0x16EF40 [datGetDaysSkipTarget]
u32 sub_16EF50(EEContext& ctx);                    // 0x16EF50 [datGetTimeSkipTarget]
u32 sub_16EF60(EEContext& ctx);                    // 0x16EF60 [datGetSkipToTarget]
void sub_16F150(EEContext& ctx);  // [register ABI] 0x16F150 [datSetTime]
void sub_16F160(EEContext& ctx);  // [register ABI] 0x16F160 [datSetDaysSkipTarget]
void sub_16F170(EEContext& ctx);  // [register ABI] 0x16F170 [datSetTimeSkipTarget]
void sub_16F180(EEContext& ctx);  // [register ABI] 0x16F180 [datSetSkipToTarget]
void sub_16F380(EEContext& ctx);  // [register ABI] 0x16F380: kCounters[index] (K_Assert index < 128)
void sub_16F3E0(EEContext& ctx);  // [register ABI] 0x16F3E0
void sub_16F450(EEContext& ctx);                   // 0x16F450: zero kCounters[0..126]

// --- flags --------------------------------------------------------------------------------------------
void datSetFlag(EEContext& ctx, s32 flag_id, u64 on);  // 0x16F1F0
void datClearFlagAll(EEContext& ctx);                  // 0x16F2E0
void MT_Misc_BitChk_regs(EEContext& ctx);  // [register ABI] 0x3951D0: datGetFlag($a0) != 0
void sub_395170(EEContext& ctx);                       // 0x395170 [MT_Misc_BitOn]: datSetFlag($a0, 1)
void sub_3951A0(EEContext& ctx);                       // 0x3951A0 [MT_Misc_BitOff]: datSetFlag($a0, 0)

// --- social-stat points (character 1 = the protagonist) ---------------------------------------------------
void sub_16C6F0(EEContext& ctx);  // [register ABI] 0x16C6F0 [datGetAcademicPoint]
void sub_16C740(EEContext& ctx);  // [register ABI] 0x16C740 [datGetCharmPoint]
void sub_16C790(EEContext& ctx);  // [register ABI] 0x16C790 [datGetCouragePoint]
void sub_16CFE0(EEContext& ctx);  // [register ABI] 0x16CFE0 [datSetAcademicPoint]
void sub_16D090(EEContext& ctx);  // [register ABI] 0x16D090 [datSetCharmPoint]
void sub_16D160(EEContext& ctx);  // [register ABI] 0x16D160 [datSetCouragePoint]

// --- calendar -------------------------------------------------------------------------------------------
void clndGetCurrentMoonPhase_regs(EEContext& ctx);  // [register ABI] 0x181B10
void clndIsHolidayOrSunday_regs(EEContext& ctx);  // [register ABI] 0x17DCF0: of the current day
void sub_17DB40(EEContext& ctx);  // [register ABI] 0x17DB40 [clndIsHolidayOrSundayFromDays]: of a given day
void clndIsDateInRange_regs(EEContext& ctx);  // [register ABI] 0x17E480(m0, d0, m1, d1): the current day within [start, end]
void sub_17E520_regs(EEContext& ctx);  // [register ABI] 0x17E520 [clndIsDateInRangeFromDate](m, d, m0, d0, m1, d1)
void clndIsDateInRangeFromStart_regs(EEContext& ctx);  // [register ABI] 0x17E5D0(m, d, n): the current day within the n days from (m, d)
void datSetDaysSinceApr5(EEContext& ctx);  // [register ABI] 0x16EF70

// --- camp ---------------------------------------------------------------------------------------------------
void H_Camp_MoveListCursor(EEContext& ctx);  // [register ABI] 0x11ABD0

// --- event/itemtbl.bin ------------------------------------------------------------------------------------
void datItemTblSetSections(EEContext& ctx);       // 0x16C2F0
void sub_170D60(EEContext& ctx);  // [register ABI] 0x170D60: section 0 record, id 0..999
void sub_170DA0(EEContext& ctx);  // [register ABI] 0x170DA0: section 2 record, id 1000..1999
void sub_170DF0(EEContext& ctx);  // [register ABI] 0x170DF0: section 3 record, id 2000..2999
void sub_170E40(EEContext& ctx);  // [register ABI] 0x170E40: section 4 record, id 3000..3999
void sub_170E90(EEContext& ctx);  // [register ABI] 0x170E90: section 6 record, id - 4000 for any id >= 3000
void sub_170ED0(EEContext& ctx);  // [register ABI] 0x170ED0: any of the five by id range, *kind = 0..4
void sub_1714B0(EEContext& ctx);  // [register ABI] 0x1714B0: section 7 record
void sub_1714D0(EEContext& ctx);  // [register ABI] 0x1714D0: section 8 record
void sub_1714F0(EEContext& ctx);  // [register ABI] 0x1714F0: section 11 record
void sub_171510(EEContext& ctx);  // [register ABI] 0x171510: section 9 float (bits); leaves the address in $v0
void sub_171550(EEContext& ctx);  // [register ABI] 0x171550: weighted random pick from a section 10 record

}  // namespace p3fes::game
