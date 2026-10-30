// Menu / UI layer leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md): the calendar
// arithmetic behind the date/time HUD (clnd*, g_data.c), the global flag bit array (datGetFlag), the
// camp-menu string/threshold tables, the sprite-font file table and the H_Cursor setters.
//
// Names: the IDA names of symbols/p3fes.sym, promoted on the master 2026-10-20 from
// symbols/deltas/menu_ui.sym (before that every function here was `sub_<addr>`: its community name was a
// withheld hint, ADR-0009). The trailing comment gives the function's address.
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

namespace ui {

// --- calendar (g_data.c / clnd*; 20_menu_ui.md section 3) ----------------------------------------------
inline constexpr u32 kDaysSinceApr5 = 0x83679Cu;   // s16: the game date, 0 = April 5 (datGetDaysSinceApr5)
inline constexpr u32 kTimeOfDay = 0x83679Eu;       // u8: day part (datGetTime)
inline constexpr u32 kMonthLengths = 0x5E3B60u;    // s16[12] {31,28,31,30,31,30,31,31,30,31,30,31}, read as tbl[month-1]
inline constexpr u32 kMoonPhaseTable = 0x5E38D0u;  // u8[368]: moon phase per day since April 5 (0..0x1D; 0x0E = full moon)
inline constexpr u32 kFlagWords = 0x83A21Cu;       // u32[176]: gGlobalWork+0x401C, 5,632 flag bits (datSetFlag asserts id < 0x1600)

// --- camp menu tables (h_camp.c, g_data.c) -------------------------------------------------------------
inline constexpr u32 kCourageLevelStrings = 0x5D7E7Cu;  // const char*[7]: 0, "Timid", "Ordinary", "Determined", "Tough", "Fearless", "Badass"
inline constexpr u32 kCharmLevelStrings = 0x5D7E98u;    // const char*[7]: "Badass"(sic, shared), "Plain", "Unpolished", "Confident", "Smooth", "Popular", "Charismatic"
inline constexpr u32 kAcademicLevelStrings = 0x5D7EB4u; // const char*[7]: "Charismatic"(shared), "Slacker", "Average", "Above Average", "Smart", "Intelligent", "Genius"
inline constexpr u32 kAcademicThresholds = 0x5E3068u;   // s16[7] {0, 20, 80, 140, 200, 260, 999}
inline constexpr u32 kCharmThresholds = 0x5E3078u;      // s16[7] {0, 15, 30, 45, 60, 80, 999}
inline constexpr u32 kCourageThresholds = 0x5E3088u;    // s16[7] {0, 15, 30, 45, 60, 80, 999}
inline constexpr u32 kSprFontFiles = 0x833A40u;         // SprFile*[3]: camp/font/i_font01a.spr, i_font02a.spr, i_font02b.spr (sprFontInit)

// --- kwln task record: the fields the UI leaves touch -------------------------------------------------
inline constexpr u32 kTaskWorkData = 0x3C;  // kwlnTask +0x3C: the work-data pointer (kwlnTaskGetWorkData 0x195540)
}  // namespace ui

// The H_Cursor work record (RwHeapCalloc(1, 0x150) in H_Cursor_CreateTask 0x1005B0; 20_menu_ui.md
// section 4.2). The four 64-byte vertex records at +0 are rebuilt every frame by H_Cursor_UpdateDrawTask
// from the fields below.
struct HCursorWork {  // 336 bytes
    u8 vertices[0x110];   // +0x000 4 x RwIm2DVertex-style records (pos +0/+4, z +8, rhw +0x18, rgba floats +0x20..+0x2C)
    s16 state;            // +0x110 0 = rebuild, 1 = built, 2 = finished (task returns -1)
    u8 pad112[2];         // +0x112
    f32 pos_x;            // +0x114 H_Cursor_SetPos (a1 = packed {x, y} floats)
    f32 pos_y;            // +0x118
    u32 rect[4];          // +0x11C H_Cursor_SetRect: four words copied as bits; [2], [3] are ints (width, height) in UpdateDrawTask
    f32 z_offset;         // +0x12C H_Cursor_SetZOffset ($f12)
    u8 rgba[4][4];        // +0x130 H_Cursor_SetColor: the same RGBA bytes for the 4 vertices
    s32 should_draw;      // +0x140 1 after creation; H_Cursor_GetShouldDraw returns its address
    u8 pad144[0xC];       // +0x144
};
static_assert(sizeof(HCursorWork) == 0x150);
static_assert(offsetof(HCursorWork, state) == 0x110 && offsetof(HCursorWork, pos_x) == 0x114 && offsetof(HCursorWork, rect) == 0x11C &&
              offsetof(HCursorWork, z_offset) == 0x12C && offsetof(HCursorWork, rgba) == 0x130 && offsetof(HCursorWork, should_draw) == 0x140);

// --- calendar leaves (game/src/ui/ui_calendar.cpp) -------------------------------------------------------
s32 datGetDaysSinceApr5(EEContext& ctx);                                // 0x16EF20: the s16 at 0x83679C
u32 datGetTime(EEContext& ctx);                                         // 0x16EF30: the u8 at 0x83679E
void clndGetMonthFromDaysSinceApr5(EEContext& ctx);  // [register ABI] 0x17D830: walk the month lengths from April
void clndGetDayOfMonthFromDaysSinceApr5(EEContext& ctx);  // [register ABI] 0x17D9C0: the remainder + 1
void clndGetDaysSinceStartFromDate(EEContext& ctx);  // [register ABI] 0x17D8B0: inverse of the two above
void clndGetWeekDay(EEContext& ctx);  // [register ABI] 0x17DAE0: (days + 7) % 7 (EE div), 0 = Sunday
void clndGetCurrentWeekDay_regs(EEContext& ctx);  // [register ABI] 0x17DB00: clndGetWeekDay(datGetDaysSinceApr5())
void clndGetCurrentMonth_regs(EEContext& ctx);  // [register ABI] 0x17D920
void clndGetCurrentDay_regs(EEContext& ctx);  // [register ABI] 0x17DA40
void clndGetMoonPhase(EEContext& ctx);  // [register ABI] 0x181B50: kMoonPhaseTable[days]

// --- flag bits and tables (game/src/ui/ui_tables.cpp) ----------------------------------------------------
void datGetFlag(EEContext& ctx);  // [register ABI] 0x16F190: bit (flag_id % 32) of word (flag_id / 32), C division
void sprFontGetFile(EEContext& ctx);  // [register ABI] 0x1120A0: kSprFontFiles[index]
void H_Camp_GetAcademicLevelString(EEContext& ctx);  // [register ABI] 0x11A810: kAcademicLevelStrings[(s16)level]
void H_Camp_GetCharmLevelString(EEContext& ctx);  // [register ABI] 0x11A840
void H_Camp_GetCourageLevelString(EEContext& ctx);  // [register ABI] 0x11A870
void datGetAcademicLevel(EEContext& ctx);  // [register ABI] 0x177280: highest i in 5..0 with points >= threshold[i], + 1
void datGetCharmLevel(EEContext& ctx);  // [register ABI] 0x1772F0
void datGetCourageLevel(EEContext& ctx);  // [register ABI] 0x177360

// --- H_Cursor setters (game/src/ui/ui_cursor.cpp); `task` is the kwln task, the work record is at +0x3C -----
void H_Cursor_SetPos(EEContext& ctx);  // [register ABI] 0x100710 H_Cursor_SetPos(task, {x, y})
void H_Cursor_SetRect(EEContext& ctx);  // [register ABI] 0x100740 H_Cursor_SetRect(task, const u32 rect[4])
void H_Cursor_SetZOffset(EEContext& ctx);  // [register ABI] 0x100770 H_Cursor_SetZOffset(task, float z)
void H_Cursor_SetColor(EEContext& ctx);  // [register ABI] 0x100780 H_Cursor_SetColor(task, u32 rgba little-endian bytes)

}  // namespace p3fes::game
