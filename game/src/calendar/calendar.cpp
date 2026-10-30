// The calendar and time system (slice calendar; game/include/p3fes/game/calendar.h documents what the calendar keeps
// where, for the multiplayer server): clnd.c's band 0x17D7C0-0x18A000 -- the date arithmetic beyond the getters
// (the next holiday, the social timers' date codes), the "CalenderDraw" task that runs a day's time slots and advances
// the time (the time-skip rule), the nine time-slot sequences and the new-day processing (flag resets, scheduled
// conditions, the daily condition step), today's scheduled event lookup and start, The Answer's fixed day sequence,
// the day-part HUD and the date / time-slot change effects, the boot-up memory-card check, the game-clear save prompt
// -- plus the rest of datPersona.c / g_data.c (0x176210-0x177DB0 and 0x17AC60-0x17C2F0: the persona record helpers,
// the hero's names, the record backup entries, the dated list, item give / take, the bit arrays, the skill helpers
// on party units).
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): register for register and block for block as the
// recompiled bodies -- frame, spills, $ra links, cycle charges and check points -- with each function's role, the
// record offsets and the branch meanings named on top (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). Names are
// symbols/functions.json's; a proposed name stands in brackets (ADR-0009: from the instructions, callers and strings).
//
// Conventions in the bodies: a "day" is the s16 count of days since April 5 (gGlobalWork +0x59C; 0 = Sunday,
// April 5, 2009; the game year ends on day 360, March 31, 2010), a "slot" the u8 time of day (+0x59E; 0..8,
// calendar.h kSlot*); the month walk `rem = day + 4; month = 4; while (rem >= len[month - 1]) ...` over
// tbl_clndMonthLengths (0x5E3B60) is inlined in several functions; the weekday is (day + 7) % 7 through `div`/`mfhi`
// (0 = Sunday). K_Assert (sub_19D3F0) is `jr $ra` in retail: a failed check continues, as here.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/calendar.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_H_Cursor_CreateTask_001005b0(p3fes::EEContext&);
void fn_H_Cursor_SetPos_00100710(p3fes::EEContext&);
void fn_H_DayChgDraw_DrawStrip_00185b40(p3fes::EEContext&);
void fn_H_DayPartsDraw_IsIdle_00184d90(p3fes::EEContext&);
void fn_H_DayPartsDraw_SetDate_00184c80(p3fes::EEContext&);
void fn_H_DayParts_CreateTask_00184db0(p3fes::EEContext&);
void fn_H_Memcard_ClearChkAreaSeq_00191240(p3fes::EEContext&);
void fn_H_Memcard_UpdateChkAreaSeq_00191260(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_Y_McProc_CreateMcProcDrawTask_00420340(p3fes::EEContext&);
void fn_Y_Misc_CreateMCWNDProcTasks_004214e0(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetMonthFromDaysSinceApr5_0017d830(p3fes::EEContext&);
void fn_clndGetMoonPhase_00181b50(p3fes::EEContext&);
void fn_clndGetWeekDay_0017dae0(p3fes::EEContext&);
void fn_clndIsHolidayOrSunday_0017dcf0(p3fes::EEContext&);
void fn_clndUpdateBootupCheckMemcardTask_00188690(p3fes::EEContext&);
void fn_comu_CreateComuTimerProcessTask_003c1ab0(p3fes::EEContext&);
void fn_datCalcIsSkillUsableOnField_00300af0(p3fes::EEContext&);
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datSetDaysSinceApr5_0016ef70(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_k_Field_CreateFieldRootTask_001ba5f0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_4_00177270(p3fes::EEContext&);
void fn_nullsub_5_00188650(p3fes::EEContext&);
void fn_nullsub_6_00188670(p3fes::EEContext&);
void fn_nullsub_7_00188680(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_104D10_00104d10(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_1086D0_001086d0(p3fes::EEContext&);
void fn_sub_108F70_00108f70(p3fes::EEContext&);
void fn_sub_109F60_00109f60(p3fes::EEContext&);
void fn_sub_10A370_0010a370(p3fes::EEContext&);
void fn_sub_10BDA0_0010bda0(p3fes::EEContext&);
void fn_sub_111CB0_00111cb0(p3fes::EEContext&);
void fn_sub_111D50_00111d50(p3fes::EEContext&);
void fn_sub_111DD0_00111dd0(p3fes::EEContext&);
void fn_sub_111EC0_00111ec0(p3fes::EEContext&);
void fn_sub_111EE0_00111ee0(p3fes::EEContext&);
void fn_sub_111F20_00111f20(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_sub_16D9D0_0016d9d0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16EF40_0016ef40(p3fes::EEContext&);
void fn_sub_16EF50_0016ef50(p3fes::EEContext&);
void fn_sub_16EF60_0016ef60(p3fes::EEContext&);
void fn_sub_16F150_0016f150(p3fes::EEContext&);
void fn_sub_16F160_0016f160(p3fes::EEContext&);
void fn_sub_16F170_0016f170(p3fes::EEContext&);
void fn_sub_16F180_0016f180(p3fes::EEContext&);
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_16FF90_0016ff90(p3fes::EEContext&);
void fn_sub_170080_00170080(p3fes::EEContext&);
void fn_sub_170170_00170170(p3fes::EEContext&);
void fn_sub_170260_00170260(p3fes::EEContext&);
void fn_sub_170350_00170350(p3fes::EEContext&);
void fn_sub_170440_00170440(p3fes::EEContext&);
void fn_sub_170530_00170530(p3fes::EEContext&);
void fn_sub_170620_00170620(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170D60_00170d60(p3fes::EEContext&);
void fn_sub_170DA0_00170da0(p3fes::EEContext&);
void fn_sub_170DF0_00170df0(p3fes::EEContext&);
void fn_sub_170E40_00170e40(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_1714B0_001714b0(p3fes::EEContext&);
void fn_sub_1714D0_001714d0(p3fes::EEContext&);
void fn_sub_171550_00171550(p3fes::EEContext&);
void fn_sub_175CE0_00175ce0(p3fes::EEContext&);
void fn_sub_176210_00176210(p3fes::EEContext&);
void fn_sub_1764B0_001764b0(p3fes::EEContext&);
void fn_sub_176510_00176510(p3fes::EEContext&);
void fn_sub_176600_00176600(p3fes::EEContext&);
void fn_sub_176680_00176680(p3fes::EEContext&);
void fn_sub_176840_00176840(p3fes::EEContext&);
void fn_sub_1768E0_001768e0(p3fes::EEContext&);
void fn_sub_176990_00176990(p3fes::EEContext&);
void fn_sub_176A30_00176a30(p3fes::EEContext&);
void fn_sub_176AC0_00176ac0(p3fes::EEContext&);
void fn_sub_176C80_00176c80(p3fes::EEContext&);
void fn_sub_176D10_00176d10(p3fes::EEContext&);
void fn_sub_176DA0_00176da0(p3fes::EEContext&);
void fn_sub_176FB0_00176fb0(p3fes::EEContext&);
void fn_sub_1770D0_001770d0(p3fes::EEContext&);
void fn_sub_1773D0_001773d0(p3fes::EEContext&);
void fn_sub_177410_00177410(p3fes::EEContext&);
void fn_sub_1774E0_001774e0(p3fes::EEContext&);
void fn_sub_1775A0_001775a0(p3fes::EEContext&);
void fn_sub_177670_00177670(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_1778B0_001778b0(p3fes::EEContext&);
void fn_sub_1779A0_001779a0(p3fes::EEContext&);
void fn_sub_177A40_00177a40(p3fes::EEContext&);
void fn_sub_177A90_00177a90(p3fes::EEContext&);
void fn_sub_177B50_00177b50(p3fes::EEContext&);
void fn_sub_177B90_00177b90(p3fes::EEContext&);
void fn_sub_177C10_00177c10(p3fes::EEContext&);
void fn_sub_177C50_00177c50(p3fes::EEContext&);
void fn_sub_177CA0_00177ca0(p3fes::EEContext&);
void fn_sub_177CE0_00177ce0(p3fes::EEContext&);
void fn_sub_177D10_00177d10(p3fes::EEContext&);
void fn_sub_177D40_00177d40(p3fes::EEContext&);
void fn_sub_17AC60_0017ac60(p3fes::EEContext&);
void fn_sub_17AD90_0017ad90(p3fes::EEContext&);
void fn_sub_17ADF0_0017adf0(p3fes::EEContext&);
void fn_sub_17AE30_0017ae30(p3fes::EEContext&);
void fn_sub_17AE50_0017ae50(p3fes::EEContext&);
void fn_sub_17AF20_0017af20(p3fes::EEContext&);
void fn_sub_17AFD0_0017afd0(p3fes::EEContext&);
void fn_sub_17B070_0017b070(p3fes::EEContext&);
void fn_sub_17B100_0017b100(p3fes::EEContext&);
void fn_sub_17B160_0017b160(p3fes::EEContext&);
void fn_sub_17B170_0017b170(p3fes::EEContext&);
void fn_sub_17B180_0017b180(p3fes::EEContext&);
void fn_sub_17B1A0_0017b1a0(p3fes::EEContext&);
void fn_sub_17B1E0_0017b1e0(p3fes::EEContext&);
void fn_sub_17B220_0017b220(p3fes::EEContext&);
void fn_sub_17B260_0017b260(p3fes::EEContext&);
void fn_sub_17B2A0_0017b2a0(p3fes::EEContext&);
void fn_sub_17B2E0_0017b2e0(p3fes::EEContext&);
void fn_sub_17B3D0_0017b3d0(p3fes::EEContext&);
void fn_sub_17B480_0017b480(p3fes::EEContext&);
void fn_sub_17B4E0_0017b4e0(p3fes::EEContext&);
void fn_sub_17B500_0017b500(p3fes::EEContext&);
void fn_sub_17B5B0_0017b5b0(p3fes::EEContext&);
void fn_sub_17B660_0017b660(p3fes::EEContext&);
void fn_sub_17BB40_0017bb40(p3fes::EEContext&);
void fn_sub_17BBB0_0017bbb0(p3fes::EEContext&);
void fn_sub_17BC20_0017bc20(p3fes::EEContext&);
void fn_sub_17BE10_0017be10(p3fes::EEContext&);
void fn_sub_17BF70_0017bf70(p3fes::EEContext&);
void fn_sub_17BFA0_0017bfa0(p3fes::EEContext&);
void fn_sub_17C070_0017c070(p3fes::EEContext&);
void fn_sub_17C0E0_0017c0e0(p3fes::EEContext&);
void fn_sub_17C190_0017c190(p3fes::EEContext&);
void fn_sub_17C1C0_0017c1c0(p3fes::EEContext&);
void fn_sub_17C220_0017c220(p3fes::EEContext&);
void fn_sub_17C280_0017c280(p3fes::EEContext&);
void fn_sub_17D7C0_0017d7c0(p3fes::EEContext&);
void fn_sub_17D7F0_0017d7f0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_17D810_0017d810(p3fes::EEContext&);
void fn_sub_17D820_0017d820(p3fes::EEContext&);
void fn_sub_17DB40_0017db40(p3fes::EEContext&);
void fn_sub_17DDF0_0017ddf0(p3fes::EEContext&);
void fn_sub_17E050_0017e050(p3fes::EEContext&);
void fn_sub_17E680_0017e680(p3fes::EEContext&);
void fn_sub_17F8D0_0017f8d0(p3fes::EEContext&);
void fn_sub_17FA10_0017fa10(p3fes::EEContext&);
void fn_sub_17FAA0_0017faa0(p3fes::EEContext&);
void fn_sub_17FAD0_0017fad0(p3fes::EEContext&);
void fn_sub_17FB90_0017fb90(p3fes::EEContext&);
void fn_sub_17FC70_0017fc70(p3fes::EEContext&);
void fn_sub_17FE10_0017fe10(p3fes::EEContext&);
void fn_sub_180030_00180030(p3fes::EEContext&);
void fn_sub_180220_00180220(p3fes::EEContext&);
void fn_sub_180A20_00180a20(p3fes::EEContext&);
void fn_sub_180C40_00180c40(p3fes::EEContext&);
void fn_sub_180E60_00180e60(p3fes::EEContext&);
void fn_sub_180EE0_00180ee0(p3fes::EEContext&);
void fn_sub_181010_00181010(p3fes::EEContext&);
void fn_sub_181170_00181170(p3fes::EEContext&);
void fn_sub_181310_00181310(p3fes::EEContext&);
void fn_sub_181430_00181430(p3fes::EEContext&);
void fn_sub_181580_00181580(p3fes::EEContext&);
void fn_sub_181720_00181720(p3fes::EEContext&);
void fn_sub_181950_00181950(p3fes::EEContext&);
void fn_sub_181B70_00181b70(p3fes::EEContext&);
void fn_sub_181CC0_00181cc0(p3fes::EEContext&);
void fn_sub_182720_00182720(p3fes::EEContext&);
void fn_sub_182750_00182750(p3fes::EEContext&);
void fn_sub_182810_00182810(p3fes::EEContext&);
void fn_sub_1828D0_001828d0(p3fes::EEContext&);
void fn_sub_182C50_00182c50(p3fes::EEContext&);
void fn_sub_182D90_00182d90(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_1831E0_001831e0(p3fes::EEContext&);
void fn_sub_1833E0_001833e0(p3fes::EEContext&);
void fn_sub_184890_00184890(p3fes::EEContext&);
void fn_sub_1848F0_001848f0(p3fes::EEContext&);
void fn_sub_184F00_00184f00(p3fes::EEContext&);
void fn_sub_185830_00185830(p3fes::EEContext&);
void fn_sub_185880_00185880(p3fes::EEContext&);
void fn_sub_185980_00185980(p3fes::EEContext&);
void fn_sub_185AE0_00185ae0(p3fes::EEContext&);
void fn_sub_186050_00186050(p3fes::EEContext&);
void fn_sub_186100_00186100(p3fes::EEContext&);
void fn_sub_186140_00186140(p3fes::EEContext&);
void fn_sub_186190_00186190(p3fes::EEContext&);
void fn_sub_1868F0_001868f0(p3fes::EEContext&);
void fn_sub_186960_00186960(p3fes::EEContext&);
void fn_sub_186A40_00186a40(p3fes::EEContext&);
void fn_sub_186BD0_00186bd0(p3fes::EEContext&);
void fn_sub_186D50_00186d50(p3fes::EEContext&);
void fn_sub_187050_00187050(p3fes::EEContext&);
void fn_sub_1870E0_001870e0(p3fes::EEContext&);
void fn_sub_1871A0_001871a0(p3fes::EEContext&);
void fn_sub_187520_00187520(p3fes::EEContext&);
void fn_sub_187550_00187550(p3fes::EEContext&);
void fn_sub_187DF0_00187df0(p3fes::EEContext&);
void fn_sub_187E20_00187e20(p3fes::EEContext&);
void fn_sub_187EC0_00187ec0(p3fes::EEContext&);
void fn_sub_1883D0_001883d0(p3fes::EEContext&);
void fn_sub_188420_00188420(p3fes::EEContext&);
void fn_sub_188440_00188440(p3fes::EEContext&);
void fn_sub_188510_00188510(p3fes::EEContext&);
void fn_sub_1885A0_001885a0(p3fes::EEContext&);
void fn_sub_188640_00188640(p3fes::EEContext&);
void fn_sub_188830_00188830(p3fes::EEContext&);
void fn_sub_188860_00188860(p3fes::EEContext&);
void fn_sub_188900_00188900(p3fes::EEContext&);
void fn_sub_188B20_00188b20(p3fes::EEContext&);
void fn_sub_188B50_00188b50(p3fes::EEContext&);
void fn_sub_188C30_00188c30(p3fes::EEContext&);
void fn_sub_189230_00189230(p3fes::EEContext&);
void fn_sub_189810_00189810(p3fes::EEContext&);
void fn_sub_189DF0_00189df0(p3fes::EEContext&);
void fn_sub_191A10_00191a10(p3fes::EEContext&);
void fn_sub_191D10_00191d10(p3fes::EEContext&);
void fn_sub_1967D0_001967d0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A5CD0_001a5cd0(p3fes::EEContext&);
void fn_sub_1B7700_001b7700(p3fes::EEContext&);
void fn_sub_1FA450_001fa450(p3fes::EEContext&);
void fn_sub_27C2B0_0027c2b0(p3fes::EEContext&);
void fn_sub_27D8D0_0027d8d0(p3fes::EEContext&);
void fn_sub_306610_00306610(p3fes::EEContext&);
void fn_sub_3068D0_003068d0(p3fes::EEContext&);
void fn_sub_306BC0_00306bc0(p3fes::EEContext&);
void fn_sub_3083F0_003083f0(p3fes::EEContext&);
void fn_sub_3086C0_003086c0(p3fes::EEContext&);
void fn_sub_3086F0_003086f0(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3BD880_003bd880(p3fes::EEContext&);
void fn_sub_3BD890_003bd890(p3fes::EEContext&);
void fn_sub_3BD8A0_003bd8a0(p3fes::EEContext&);
void fn_sub_3BDD60_003bdd60(p3fes::EEContext&);
void fn_sub_4204F0_004204f0(p3fes::EEContext&);
void fn_sub_4215B0_004215b0(p3fes::EEContext&);
void fn_sub_421650_00421650(p3fes::EEContext&);
void fn_sub_421700_00421700(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00176210 sub_176210 -- 668 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_176210(persona, level) [datPersonaGetExpForLevel]: the exp total a persona needs for `level` (u16; < 2 -> 0,
// clamped to 99). A party member's persona (id 0xC0..0xDF, K_Assert 1444) reads s32 [level] of its member's 392-byte
// row of *0x7CE434 (the member pc 2..10 is u16 +0 of the persona's 622-byte record at *0x7CE430; K_Assert 1446); any
// other id (< 256, K_Assert 1433) computes it in single floats from level^3 times the float at 0x7CADA8 and the
// constants 0x7CAED4 / 0x7CAED8 / 0x7CAEDC with the R5900 multiply-add accumulator (The Answer, sub_17D800() != 0,
// takes the 2.5 / 10.0 variant).
void sub_176210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00176210
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFFFF;
    at = slti(v0, 2);
    if (at == 0) {
        // 0x0017624c
        charge(ctx, 3);
        at = slti(v0, 100);
        if (at == 0) {
            // 0x00176258
            charge(ctx, 1);
            s0 = 99;
        }
        // 0x0017625c
        charge(ctx, 4);
        lhu(v1, s1, 2);
        v0 = slti(v1, 192);
        if (v0 == 0) {
            // 0x0017626c
            charge(ctx, 3);
            at = slti(v1, 224);
            if (at == 0) {
                goto L_00176284;
            }
            // 0x00176278
            charge(ctx, 3);
            v0 = 1;
            goto L_00176288;
        }
    L_00176284:
        charge(ctx, 1);
        v0 = 0;
    L_00176288:
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x001763e8
            charge(ctx, 3);
            v0 = slti(v1, 192);
            {  // the inlined check: K_Assert unless (v0 == 0) and not (at == 0)
                bool bad = true;
                if (v0 == 0) {
                    // 0x001763f4
                    charge(ctx, 3);
                    at = slti(v1, 224);
                    bad = at == 0;
                }
                if (bad) {  // 0x00176400: K_Assert (returns in retail)
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12920);  // "datPersona.c"
                    a1 = 1444;
                    jal(ctx, 0x17640Cu, gen::fn_sub_19D3F0_0019d3f0);
                }
            }
            // 0x00176414
            charge(ctx, 11);
            lhu(v1, s1, 2);
            v0 = 622;
            mult(v1, v1, v0);
            lw(v0, gp, -18624);  // 0x7CE430
            v1 = addu(v1, v0);
            v0 = lui(0xFFFE);
            v0 = addu(v1, v0);
            lhu(s1, v0, 11648);
            at = slti(s1, 2);
            {  // the inlined check: K_Assert unless (at == 0) and not (v0 == 0)
                bool bad = true;
                if (at == 0) {
                    // 0x00176440
                    charge(ctx, 3);
                    v0 = slti(s1, 11);
                    bad = v0 == 0;
                }
                if (bad) {  // 0x0017644c: K_Assert (returns in retail)
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12920);  // "datPersona.c"
                    a1 = 1446;
                    jal(ctx, 0x176458u, gen::fn_sub_19D3F0_0019d3f0);
                }
            }
            // 0x00176460
            charge(ctx, 11);
            lw(a0, gp, -18620);  // 0x7CE434
            v0 = sll(s1, 3);
            v1 = subu(v0, s1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 3);
            v1 = addu(v0, a0);
            v0 = s0 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, -792);
        } else {
            // 0x00176290
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 == 0) {
                // 0x0017629c
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12920);  // "datPersona.c"
                a1 = 1433;
                jal(ctx, 0x1762A8u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001762b0
            charge(ctx, 2);
            if (i64(s0) < 0) {
                // 0x001762cc
                charge(ctx, 7);
                v1 = srl(s0, 1);
                v0 = s0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f20, f0);
                add_s(f20, f20, f20);
            } else {
                // 0x001762b8
                charge(ctx, 5);
                mtc1(s0, f0);
                cvt_s_w(f20, f0);
            }
            // 0x001762e8
            charge(ctx, 9);
            lhu(v1, s1, 2);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            lw(v0, gp, -18640);  // 0x7CE420
            v0 = addu(v1, v0);
            lbu(v0, v0, 3);
            if (i64(v0) < 0) {
                // 0x00176320
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f21, f0);
                add_s(f21, f21, f21);
            } else {
                // 0x0017630c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f21, f0);
            }
            // 0x0017633c
            charge(ctx, 4);
            jal(ctx, 0x17633Cu, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00176398
                charge(ctx, 20);
                lwc1(f0, gp, -32584);  // 0x7CADA8
                mul_s(f0, f0, f20);
                mul_s(f0, f0, f20);
                mul_s(f3, f20, f0);
                lwc1(f2, gp, -32276);  // 0x7CAEDC
                v0 = 0x40200000;
                mtc1(v0, f0);
                mtc1(zero, f1);
                adda_s(f1, f0);
                msub_s(f2, f2, f21);
                v0 = 0x41200000;
                mtc1(v0, f0);
                adda_s(f1, f0);
                madd_s(f0, f2, f3);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
            } else {
                // 0x0017634c
                charge(ctx, 19);
                lwc1(f1, gp, -32284);  // 0x7CAED4
                lwc1(f0, gp, -32280);  // 0x7CAED8
                mtc1(zero, f2);
                adda_s(f2, f0);
                msub_s(f3, f1, f21);
                lwc1(f0, gp, -32584);  // 0x7CADA8
                mul_s(f0, f0, f20);
                mul_s(f0, f0, f20);
                mul_s(f1, f20, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                adda_s(f2, f0);
                madd_s(f0, f3, f1);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
            }
        }
    } else {
        // 0x00176240
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017648c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001764B0 sub_1764B0 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1764B0(persona, n) [datPersonaAddExp]: persona.exp (+8) += n; K_Assert(datPersona.c, 1458) when n < 0
// (retail continues and adds).
void sub_1764B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001764b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (i64(s0) < 0) {
        // 0x001764d0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1458;
        jal(ctx, 0x1764DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001764e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, s1, 8);
    v1 = addu(v1, s0);
    sw(v1, s1, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00176510 sub_176510 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_176510(persona) [datPersonaPackSkills]: closes the gaps in skills[8] (+0xC): every empty slot takes the next
// non-empty one to its right, which is cleared (K_Assert 1478 on a null persona).
void sub_176510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176510
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x00176528
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1478;
        jal(ctx, 0x176534u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017653c
    charge(ctx, 5);
    a3 = 0;
    a2 = 0;
    a0 = 8;
    for (;;) {
        // 0x001765d8
        charge(ctx, 3);
        v1 = slti(a3, 8);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176550
        charge(ctx, 6);
        v1 = sll(a3, 1);
        v1 = addu(s0, v1);
        a1 = addiu(v1, 12);
        lhu(v1, v1, 12);
        if (v1 == 0) {
            // 0x00176568
            charge(ctx, 3);
            a2 = addiu(a3, 1);
            for (;;) {
                // 0x0017658c
                charge(ctx, 3);
                v1 = slti(a2, 8);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x00176574
                    charge(ctx, 5);
                    v1 = sll(a2, 1);
                    v1 = addu(s0, v1);
                    lhu(v1, v1, 12);
                    if (v1 == 0) {
                        // 0x00176588
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x00176598
            charge(ctx, 2);
            if (a2 == a0) {
                break;
            }
            goto L_001765a0;
        }
    L_001765a0:
        charge(ctx, 2);
        if (a3 != a2) {
            // 0x001765a8
            charge(ctx, 3);
            at = slti(a2, 8);
            if (at == 0) {
                // 0x001765cc
                charge(ctx, 1);
                sh(zero, a1, 0);
            } else {
                // 0x001765b4
                charge(ctx, 6);
                v1 = sll(a2, 1);
                v1 = addu(s0, v1);
                lhu(v1, v1, 12);
                sh(v1, a1, 0);
            }
        }
        // 0x001765d0
        charge(ctx, 2);
        a3 = addiu(a3, 1);
        a2 = addiu(a2, 1);
    }
    // 0x001765e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00176600 sub_176600 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_176600(persona) [datPersonaGetLockState]: 0 unless flags bit 2 (+0); then 2 with bit 3 also set, else 1 (the
// two flag bits datPersona keeps through a refill). K_Assert 1497 on a null persona.
void sub_176600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176600
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x00176618
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1497;
        jal(ctx, 0x176624u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017662c
    charge(ctx, 4);
    lhu(v1, s0, 0);
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x00176660
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0017663c
        charge(ctx, 3);
        v0 = v1 & 0x8;
        if (v0 == 0) {
            // 0x00176654
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00176648
            charge(ctx, 3);
            v0 = 2;
        }
        // 0x00176658
        charge(ctx, 2);
    }
    // 0x00176664 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00176680 sub_176680 -- 440 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176680(persona, id) [datPersonaInit]: builds persona `id` (1..255, K_Assert 1515 / 1516) from its 14-byte row of
// the persona table (*0x7CE420): id, level (row +3), byte +5 (row +9), exp = sub_176210(level), +0x2C / +0x30 = 0,
// base stats from row +4, bonus A / B and skills cleared; then the level-up record of the persona (sub_175CE0 on a
// 40-byte frame buffer) is applied (level += rec[0], stats += rec[34..38]; K_Assert 1362) and the innate skills are
// learnt (sub_176DA0).
void sub_176680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176680
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (s2 == 0) {
        // 0x001766a4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1515;
        jal(ctx, 0x1766B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001766b8
    charge(ctx, 3);
    v0 = s1 & 0xFFFF;
    {  // the inlined check: K_Assert unless (v0 != 0) and not (v0 == 0)
        bool bad = true;
        if (v0 != 0) {
            // 0x001766c4
            charge(ctx, 3);
            v0 = slti(v0, 256);
            bad = v0 == 0;
        }
        if (bad) {  // 0x001766d0: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1516;
            jal(ctx, 0x1766DCu, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x001766e4
    charge(ctx, 47);
    v1 = s1 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s0 = sll(v0, 1);
    lw(v0, gp, -18640);  // 0x7CE420
    v1 = addu(v0, s0);
    sh(s1, s2, 2);
    lbu(v0, v1, 3);
    sb(v0, s2, 4);
    lbu(v0, v1, 9);
    sb(v0, s2, 5);
    sw(zero, s2, 48);
    lbu(a1, v1, 3);
    a0 = s2;
    jal(ctx, 0x17671Cu, gen::fn_sub_176210_00176210);
    sw(v0, s2, 8);
    sw(zero, s2, 44);
    lw(v0, gp, -18640);  // 0x7CE420
    v0 = addu(v0, s0);
    a0 = addiu(s2, 28);
    a1 = addiu(v0, 4);
    a2 = 5;
    jal(ctx, 0x176740u, gen::fn_memcpy_00521250);
    a0 = addiu(s2, 33);
    a1 = 0;
    a2 = 5;
    jal(ctx, 0x176754u, gen::fn_memset_00521408);
    a0 = addiu(s2, 38);
    a1 = 0;
    a2 = 5;
    jal(ctx, 0x176768u, gen::fn_memset_00521408);
    a0 = addiu(s2, 12);
    a1 = 0;
    a2 = 16;
    jal(ctx, 0x17677Cu, gen::fn_memset_00521408);
    a0 = s2;
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x17678Cu, gen::fn_sub_175CE0_00175ce0);
    lhu(v0, s2, 2);
    {  // the inlined check: K_Assert unless (v0 != 0) and not (v0 == 0)
        bool bad = true;
        if (v0 != 0) {
            // 0x001767a0
            charge(ctx, 3);
            v0 = slti(v0, 256);
            bad = v0 == 0;
        }
        if (bad) {  // 0x001767ac: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1362;
            jal(ctx, 0x1767B8u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x001767c0
    charge(ctx, 7);
    lbu(v1, s2, 4);
    lbu(v0, sp, 0x40);
    v0 = addu(v1, v0);
    sb(v0, s2, 4);
    a1 = 0;
    for (;;) {
        // 0x00176800
        charge(ctx, 4);
        v0 = a1 & 0xFFFF;
        v0 = slti(v0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001767dc
        charge(ctx, 9);
        v1 = a1 & 0xFFFF;
        v0 = addu(v1, sp);
        a0 = addu(s2, v1);
        lbu(v1, a0, 28);
        lbu(v0, v0, 98);
        v0 = addu(v1, v0);
        sb(v0, a0, 28);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFFFF;
    }
    // 0x00176810
    charge(ctx, 10);
    a0 = s2;
    jal(ctx, 0x176814u, gen::fn_sub_176DA0_00176da0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00176840 sub_176840 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176840(persona, skill) [datPersonaAddSkill]: puts `skill` in the first empty slot of skills[8]: 1, or 0 when the
// eight are full. K_Assert 1546 on a null persona or skill 0.
void sub_176840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176840
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    {  // the inlined check: K_Assert unless (s1 != 0) and not (v0 == 0)
        bool bad = true;
        if (s1 != 0) {
            // 0x00176860
            charge(ctx, 3);
            v0 = s0 & 0xFFFF;
            bad = v0 == 0;
        }
        if (bad) {  // 0x0017686c: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1546;
            jal(ctx, 0x176878u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x00176880
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x001768b8
        charge(ctx, 3);
        v0 = slti(a0, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017688c
        charge(ctx, 6);
        v0 = sll(a0, 1);
        v0 = addu(s1, v0);
        v1 = addiu(v0, 12);
        lhu(v0, v0, 12);
        if (v0 == 0) {
            // 0x001768a4
            charge(ctx, 4);
            sh(s0, v1, 0);
            v0 = 1;
            // 0x001768c8 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x001768b4
        charge(ctx, 1);
        a0 = addiu(a0, 1);
    }
    // 0x001768c4
    charge(ctx, 1);
    v0 = 0;
    // 0x001768c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
}

// 0x001768E0 sub_1768E0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1768E0(persona, skill) [datPersonaRemoveSkill]: clears the slot holding `skill` and packs the list (sub_176510):
// 1, or 0 when the persona does not have it. K_Assert 1560.
void sub_1768E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001768e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    {  // the inlined check: K_Assert unless (s0 != 0) and not (v0 == 0)
        bool bad = true;
        if (s0 != 0) {
            // 0x00176900
            charge(ctx, 3);
            v0 = s1 & 0xFFFF;
            bad = v0 == 0;
        }
        if (bad) {  // 0x0017690c: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1560;
            jal(ctx, 0x176918u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x00176920
    charge(ctx, 4);
    a1 = 0;
    a0 = s1 & 0xFFFF;
    for (;;) {
        // 0x00176968
        charge(ctx, 3);
        v0 = slti(a1, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176930
        charge(ctx, 6);
        v0 = sll(a1, 1);
        v0 = addu(s0, v0);
        v1 = addiu(v0, 12);
        lhu(v0, v0, 12);
        if (v0 == a0) {
            // 0x00176948
            charge(ctx, 7);
            sh(zero, v1, 0);
            a0 = s0;
            jal(ctx, 0x176950u, gen::fn_sub_176510_00176510);
            v0 = 1;
            // 0x00176978 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x00176964
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x00176974
    charge(ctx, 1);
    v0 = 0;
    // 0x00176978 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
}

// 0x00176990 sub_176990 -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176990(persona, skill) [datPersonaFindSkill]: the slot index (0..7) of `skill`, -1 when absent. K_Assert 1588.
void sub_176990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176990
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    {  // the inlined check: K_Assert unless (s0 != 0) and not (v0 == 0)
        bool bad = true;
        if (s0 != 0) {
            // 0x001769b0
            charge(ctx, 3);
            v0 = s1 & 0xFFFF;
            bad = v0 == 0;
        }
        if (bad) {  // 0x001769bc: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1588;
            jal(ctx, 0x1769C8u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x001769d0
    charge(ctx, 4);
    v0 = 0;
    a0 = s1 & 0xFFFF;
    for (;;) {
        // 0x00176a00
        charge(ctx, 3);
        v1 = slti(v0, 8);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001769e0
        charge(ctx, 5);
        v1 = sll(v0, 1);
        v1 = addu(s0, v1);
        lhu(v1, v1, 12);
        if (v1 == a0) {
            // 0x001769f4
            charge(ctx, 2);
            // 0x00176a10 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x001769fc
        charge(ctx, 1);
        v0 = addiu(v0, 1);
    }
    // 0x00176a0c
    charge(ctx, 1);
    v0 = si(-1);
    // 0x00176a10 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
}

// 0x00176A30 sub_176A30 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176A30(persona) [datPersonaCountSkills]: the number of non-empty skill slots. K_Assert 1601.
void sub_176A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176a30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    if (s0 == 0) {
        // 0x00176a50
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1601;
        jal(ctx, 0x176A5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00176a64
    charge(ctx, 3);
    v1 = 0;
    for (;;) {
        // 0x00176a8c
        charge(ctx, 3);
        v0 = slti(v1, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176a70
        charge(ctx, 5);
        v0 = sll(v1, 1);
        v0 = addu(s0, v0);
        lhu(v0, v0, 12);
        if (v0 != 0) {
            // 0x00176a84
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x00176a88
        charge(ctx, 1);
        v1 = addiu(v1, 1);
    }
    // 0x00176a98
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00176AC0 sub_176AC0 -- 436 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176AC0(persona, list, n) [datPersonaInheritBonus] (fusion, sub_3D6910): per stat (5), sums bonus A (+0x21) and
// bonus B (+0x26) over the n personas of `list` (u32 pointers), then persona.bonus_b[stat] += sumA + sumB / n
// (divu), capped at 99. K_Assert 1671 (null arguments) and 1623 (inlined stat-index check). Returns 0.
void sub_176AC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176ac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    s2 = a2;
    if (s3 != 0) {
        // 0x00176aec
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00176afc;
        }
        // 0x00176af4
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_00176afc;
        }
        goto L_00176b10;
    }
L_00176afc:
    charge(ctx, 5);
    a0 = 0x5E0000;
    a0 = addiu(a0, 12920);  // "datPersona.c"
    a1 = 1671;
    jal(ctx, 0x176B08u, gen::fn_sub_19D3F0_0019d3f0);
L_00176b10:
    charge(ctx, 8);
    a0 = addiu(sp, 0x50);
    a1 = 0;
    a2 = 40;
    jal(ctx, 0x176B1Cu, gen::fn_memset_00521408);
    a3 = 0;
    for (;;) {
        // 0x00176b94
        charge(ctx, 3);
        v0 = slti(a3, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176b30
        charge(ctx, 6);
        a2 = 0;
        v0 = sll(a3, 3);
        v0 = addu(v0, sp);
        a1 = addiu(v0, 80);
        for (;;) {
            // 0x00176b84
            charge(ctx, 3);
            v0 = slt(a2, s2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00176b48
            charge(ctx, 15);
            v0 = sll(a2, 2);
            a0 = addu(s0, v0);
            lw(v0, a0, 0);
            v0 = addu(a3, v0);
            lbu(v1, v0, 33);
            lw(v0, a1, 0);
            v0 = addu(v0, v1);
            sw(v0, a1, 0);
            lw(v0, a0, 0);
            v0 = addu(a3, v0);
            lbu(v1, v0, 38);
            lw(v0, a1, 4);
            v0 = addu(v0, v1);
            sw(v0, a1, 4);
            a2 = addiu(a2, 1);
        }
        // 0x00176b90
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x00176ba0
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00176c44
        charge(ctx, 3);
        v0 = slti(s1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176bac
        charge(ctx, 10);
        v0 = sll(s1, 3);
        v0 = addu(v0, sp);
        a0 = addiu(v0, 80);
        lw(v0, a0, 4);
        divu(v0, s2);
        mflo(v1);
        lw(v0, a0, 0);
        s0 = addu(v0, v1);
        {  // the inlined check: K_Assert unless (s3 != 0) and not (v0 == 0)
            bool bad = true;
            if (s3 != 0) {
                // 0x00176bd4
                charge(ctx, 4);
                v0 = s1 & 0xFF;
                v0 = slti(v0, 5);
                bad = v0 == 0;
            }
            if (bad) {  // 0x00176be4: K_Assert (returns in retail)
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12920);  // "datPersona.c"
                a1 = 1623;
                jal(ctx, 0x176BF0u, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
        // 0x00176bf8
        charge(ctx, 8);
        v0 = s1 & 0xFF;
        v0 = addu(s3, v0);
        a0 = addiu(v0, 38);
        lbu(v1, v0, 38);
        v0 = addu(v1, s0);
        at = sltiu(v0, 100);
        if (at == 0) {
            // 0x00176c2c
            charge(ctx, 5);
            v0 = 99;
            v0 = subu(v0, v1);
            v0 = v0 & 0xFF;
            v0 = addu(v1, v0);
            sb(v0, a0, 0);
        } else {
            // 0x00176c18
            charge(ctx, 5);
            v0 = s0 & 0xFF;
            v0 = addu(v1, v0);
            sb(v0, a0, 0);
        }
        // 0x00176c40
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00176c50
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00176C80 sub_176C80 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176C80(dst, src) [datPersonaCopyBonus]: dst.bonus_a[5] / bonus_b[5] = src's. K_Assert 1691. Returns 0.
void sub_176C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176c80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    {  // the inlined check: K_Assert unless (s1 != 0) and not (s0 == 0)
        bool bad = true;
        if (s1 != 0) {
            // 0x00176ca0
            charge(ctx, 2);
            bad = s0 == 0;
        }
        if (bad) {  // 0x00176ca8: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1691;
            jal(ctx, 0x176CB4u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x00176cbc
    charge(ctx, 3);
    a1 = 0;
    for (;;) {
        // 0x00176ce4
        charge(ctx, 3);
        v0 = slti(a1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176cc8
        charge(ctx, 7);
        a0 = addu(s0, a1);
        v1 = addu(s1, a1);
        lbu(v0, a0, 33);
        sb(v0, v1, 33);
        lbu(v0, a0, 38);
        sb(v0, v1, 38);
        a1 = addiu(a1, 1);
    }
    // 0x00176cf0
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00176D10 sub_176D10 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176D10(dst, src): dst.bonus_b[5] = src.bonus_a[5]. K_Assert 1704. Returns 0.
void sub_176D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176d10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    {  // the inlined check: K_Assert unless (s1 != 0) and not (s0 == 0)
        bool bad = true;
        if (s1 != 0) {
            // 0x00176d30
            charge(ctx, 2);
            bad = s0 == 0;
        }
        if (bad) {  // 0x00176d38: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1704;
            jal(ctx, 0x176D44u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x00176d4c
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x00176d6c
        charge(ctx, 3);
        v0 = slti(a0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176d58
        charge(ctx, 5);
        v0 = addu(s0, a0);
        lbu(v1, v0, 33);
        v0 = addu(s1, a0);
        sb(v1, v0, 38);
        a0 = addiu(a0, 1);
    }
    // 0x00176d78
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00176DA0 sub_176DA0 -- 524 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176DA0(persona) [datPersonaLearnInnateSkills]: every skill-table entry of the persona with level byte 0 and
// kind 1 (4-byte entries {u8 level, u8 kind, u16 skill}) goes into the first empty skill slot (the inlined
// sub_176840, K_Assert 1546). Party personas (id 0xC0..0xDF): 32 entries at *0x7CE430 + 622 * (id - 0xC0) + 4;
// others: 16 entries at *0x7CE428 + 70 * id + 6.
void sub_176DA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176da0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(a0, a0, 2);
    v1 = slti(a0, 192);
    if (v1 == 0) {
        // 0x00176dcc
        charge(ctx, 3);
        at = slti(a0, 224);
        if (at == 0) {
            goto L_00176de4;
        }
        // 0x00176dd8
        charge(ctx, 3);
        v1 = 1;
        goto L_00176de8;
    }
L_00176de4:
    charge(ctx, 1);
    v1 = 0;
L_00176de8:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00176ebc
        charge(ctx, 12);
        a0 = a0 & 0xFFFF;
        v1 = sll(a0, 3);
        a0 = subu(v1, a0);
        v1 = sll(a0, 2);
        v1 = addu(a0, v1);
        a0 = sll(v1, 1);
        lw(v1, gp, -18632);  // 0x7CE428
        v1 = addu(v1, a0);
        s2 = addiu(v1, 6);
        s3 = 0;
        for (;;) {
            // 0x00176f80
            charge(ctx, 3);
            v1 = slti(s3, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00176eec
            charge(ctx, 5);
            v1 = sll(s3, 2);
            a1 = addu(s2, v1);
            lbu(v1, a1, 0);
            if (v1 == 0) {
                // 0x00176f00
                charge(ctx, 4);
                lb(a0, a1, 1);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00176f10
                    charge(ctx, 3);
                    lhu(s1, a1, 2);
                    {  // the inlined check: K_Assert unless (s0 != 0) and not (v1 == 0)
                        bool bad = true;
                        if (s0 != 0) {
                            // 0x00176f1c
                            charge(ctx, 3);
                            v1 = s1 & 0xFFFF;
                            bad = v1 == 0;
                        }
                        if (bad) {  // 0x00176f28: K_Assert (returns in retail)
                            charge(ctx, 5);
                            a0 = 0x5E0000;
                            a0 = addiu(a0, 12920);  // "datPersona.c"
                            a1 = 1546;
                            jal(ctx, 0x176F34u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                    }
                    // 0x00176f3c
                    charge(ctx, 3);
                    a1 = 0;
                    for (;;) {
                        // 0x00176f70
                        charge(ctx, 3);
                        v1 = slti(a1, 8);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00176f48
                        charge(ctx, 6);
                        v1 = sll(a1, 1);
                        v1 = addu(s0, v1);
                        a0 = addiu(v1, 12);
                        lhu(v1, v1, 12);
                        if (v1 == 0) {
                            // 0x00176f60
                            charge(ctx, 3);
                            sh(s1, a0, 0);
                            goto L_00176f7c;
                        }
                        // 0x00176f6c
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                }
            }
        L_00176f7c:
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    } else {
        // 0x00176df0
        charge(ctx, 9);
        a0 = addiu(a0, -192);
        v1 = 622;
        mult(a0, a0, v1);
        lw(v1, gp, -18624);  // 0x7CE430
        v1 = addu(v1, a0);
        s2 = addiu(v1, 4);
        s3 = 0;
        for (;;) {
            // 0x00176ea8
            charge(ctx, 3);
            v1 = slti(s3, 32);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00176e14
            charge(ctx, 5);
            v1 = sll(s3, 2);
            a1 = addu(s2, v1);
            lbu(v1, a1, 0);
            if (v1 == 0) {
                // 0x00176e28
                charge(ctx, 4);
                lb(a0, a1, 1);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00176e38
                    charge(ctx, 3);
                    lhu(s1, a1, 2);
                    {  // the inlined check: K_Assert unless (s0 != 0) and not (v1 == 0)
                        bool bad = true;
                        if (s0 != 0) {
                            // 0x00176e44
                            charge(ctx, 3);
                            v1 = s1 & 0xFFFF;
                            bad = v1 == 0;
                        }
                        if (bad) {  // 0x00176e50: K_Assert (returns in retail)
                            charge(ctx, 5);
                            a0 = 0x5E0000;
                            a0 = addiu(a0, 12920);  // "datPersona.c"
                            a1 = 1546;
                            jal(ctx, 0x176E5Cu, gen::fn_sub_19D3F0_0019d3f0);
                        }
                    }
                    // 0x00176e64
                    charge(ctx, 3);
                    a1 = 0;
                    for (;;) {
                        // 0x00176e98
                        charge(ctx, 3);
                        v1 = slti(a1, 8);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00176e70
                        charge(ctx, 6);
                        v1 = sll(a1, 1);
                        v1 = addu(s0, v1);
                        a0 = addiu(v1, 12);
                        lhu(v1, v1, 12);
                        if (v1 == 0) {
                            // 0x00176e88
                            charge(ctx, 3);
                            sh(s1, a0, 0);
                            goto L_00176ea4;
                        }
                        // 0x00176e94
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                }
            }
        L_00176ea4:
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x00176eb4
        charge(ctx, 2);
    }
    // 0x00176f8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
}

// 0x00176FB0 sub_176FB0 -- 280 bytes; leaf frame (no stack)
// sub_176FB0(id, out, count) [datPersonaListInnateSkills]: writes the innate skills of persona `id` (the entries
// sub_176DA0 learns) to u16 out[] and their number to *count.
void sub_176FB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28};
    // 0x00176fb0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0;
    t0 = a0 & 0xFFFF;
    a3 = slti(t0, 192);
    if (a3 == 0) {
        // 0x00176fc4
        charge(ctx, 3);
        at = slti(t0, 224);
        if (at == 0) {
            goto L_00177044;
        }
        // 0x00176fd0
        charge(ctx, 10);
        a3 = addiu(t0, -192);
        a0 = 622;
        mult(a3, a3, a0);
        lw(a0, gp, -18624);  // 0x7CE430
        a0 = addu(a0, a3);
        t1 = addiu(a0, 4);
        t2 = 0;
        t0 = 1;
        for (;;) {
            // 0x00177030
            charge(ctx, 3);
            a0 = slti(t2, 32);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00176ff8
            charge(ctx, 5);
            a0 = sll(t2, 2);
            a3 = addu(t1, a0);
            lbu(a0, a3, 0);
            if (a0 == 0) {
                // 0x0017700c
                charge(ctx, 3);
                lb(a0, a3, 1);
                if (a0 == t0) {
                    // 0x00177018
                    charge(ctx, 5);
                    lhu(a3, a3, 2);
                    a0 = sll(v1, 1);
                    a0 = addu(a1, a0);
                    sh(a3, a0, 0);
                    v1 = addiu(v1, 1);
                }
            }
            // 0x0017702c
            charge(ctx, 1);
            t2 = addiu(t2, 1);
        }
        // 0x0017703c
        charge(ctx, 2);
        // 0x001770bc (the shared epilogue, written out on this path)
        charge(ctx, 3);
        sw(v1, a2, 0);
        return;
    }
L_00177044:
    charge(ctx, 13);
    a3 = a0 & 0xFFFF;
    a0 = sll(a3, 3);
    a3 = subu(a0, a3);
    a0 = sll(a3, 2);
    a0 = addu(a3, a0);
    a3 = sll(a0, 1);
    lw(a0, gp, -18632);  // 0x7CE428
    a0 = addu(a0, a3);
    t1 = addiu(a0, 6);
    t2 = 0;
    t0 = 1;
    for (;;) {
        // 0x001770b0
        charge(ctx, 3);
        a0 = slti(t2, 16);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00177078
        charge(ctx, 5);
        a0 = sll(t2, 2);
        a3 = addu(t1, a0);
        lbu(a0, a3, 0);
        if (a0 == 0) {
            // 0x0017708c
            charge(ctx, 3);
            lb(a0, a3, 1);
            if (a0 == t0) {
                // 0x00177098
                charge(ctx, 5);
                lhu(a3, a3, 2);
                a0 = sll(v1, 1);
                a0 = addu(a1, a0);
                sh(a3, a0, 0);
                v1 = addiu(v1, 1);
            }
        }
        // 0x001770ac
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x001770bc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sw(v1, a2, 0);
}

// 0x001770D0 sub_1770D0 -- 416 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1770D0(id, skill): the index of `skill` among the persona's learnable (level byte != 0, kind 1) skill-table
// entries; K_Assert 1848 / 1829 when it is not one of them (the party table's check bounds the index by 16, as the
// instructions do).
void sub_1770D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001770d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    v1 = a0 & 0xFFFF;
    v0 = slti(v1, 192);
    if (v0 == 0) {
        // 0x001770f0
        charge(ctx, 3);
        at = slti(v1, 224);
        if (at == 0) {
            goto L_001771a8;
        }
        // 0x001770fc
        charge(ctx, 11);
        v1 = addiu(v1, -192);
        v0 = 622;
        mult(v1, v1, v0);
        lw(v0, gp, -18624);  // 0x7CE430
        v0 = addu(v0, v1);
        a2 = addiu(v0, 4);
        a3 = 0;
        a1 = a1 & 0xFFFF;
        v1 = 1;
        for (;;) {
            // 0x0017715c
            charge(ctx, 3);
            v0 = slti(a3, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00177128
            charge(ctx, 5);
            v0 = sll(a3, 2);
            a0 = addu(a2, v0);
            lbu(v0, a0, 0);
            if (v0 != 0) {
                // 0x0017713c
                charge(ctx, 3);
                lb(v0, a0, 1);
                if (v0 != v1) {
                    goto L_00177158;
                }
                // 0x00177148
                charge(ctx, 3);
                lhu(v0, a0, 2);
                if (a1 != v0) {
                    // 0x00177154
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                    goto L_00177158;
                }
                break;
            }
        L_00177158:
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
        // 0x00177168
        charge(ctx, 3);
        at = slti(a3, 16);
        if (at != 0) {
            // 0x00177174
            charge(ctx, 6);
            v0 = sll(a3, 2);
            v0 = addu(v0, a2);
            lb(v1, v0, 1);
            v0 = 1;
            if (v1 != v0) {
                goto L_0017718c;
            }
            // 0x00177258 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            v0 = s0;
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0017718c:
        charge(ctx, 7);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1829;
        jal(ctx, 0x177198u, gen::fn_sub_19D3F0_0019d3f0);
        // 0x00177258 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = s0;
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_001771a8:
    charge(ctx, 14);
    v1 = a0 & 0xFFFF;
    v0 = sll(v1, 3);
    v1 = subu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 1);
    lw(v0, gp, -18632);  // 0x7CE428
    v0 = addu(v0, v1);
    a2 = addiu(v0, 6);
    a3 = 0;
    a1 = a1 & 0xFFFF;
    v1 = 1;
    for (;;) {
        // 0x00177214
        charge(ctx, 3);
        v0 = slti(a3, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001771e0
        charge(ctx, 5);
        v0 = sll(a3, 2);
        a0 = addu(a2, v0);
        lbu(v0, a0, 0);
        if (v0 != 0) {
            // 0x001771f4
            charge(ctx, 3);
            lb(v0, a0, 1);
            if (v0 != v1) {
                goto L_00177210;
            }
            // 0x00177200
            charge(ctx, 3);
            lhu(v0, a0, 2);
            if (a1 != v0) {
                // 0x0017720c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                goto L_00177210;
            }
            break;
        }
    L_00177210:
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x00177220
    charge(ctx, 3);
    at = slti(a3, 16);
    if (at != 0) {
        // 0x0017722c
        charge(ctx, 6);
        v0 = sll(a3, 2);
        v0 = addu(v0, a2);
        lb(v1, v0, 1);
        v0 = 1;
        if (v1 != v0) {
            goto L_00177244;
        }
        // 0x00177258 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = s0;
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_00177244:
    charge(ctx, 5);
    a0 = 0x5E0000;
    a0 = addiu(a0, 12920);  // "datPersona.c"
    a1 = 1848;
    jal(ctx, 0x177250u, gen::fn_sub_19D3F0_0019d3f0);
    // 0x00177258 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00177270 nullsub_4 -- 8 bytes; leaf frame (no stack)
// nullsub_4: empty (called by btlTablePatchForAnswer).
void nullsub_4(EEContext& ctx) {
    using namespace hg;
    // 0x00177270
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x001773D0 sub_1773D0 -- 64 bytes; frame 0x10: ra sp+0x0
// sub_1773D0 [datInitHeroName]: clears the three name strings (0x833BB0 / 0x833BD0 / 0x833BF0) and sets both hero
// names to the default string *0x7CBFA0 (sub_177410).
void sub_1773D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001773d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x830000;
    sb(zero, v0, 15280);  // 0x833BB0
    v0 = 0x830000;
    sb(zero, v0, 15312);  // 0x833BD0
    v0 = 0x830000;
    sb(zero, v0, 15344);  // 0x833BF0
    a0 = addiu(gp, -27984);  // &0x7CBFA0
    a1 = a0;
    jal(ctx, 0x1773F8u, gen::fn_sub_177410_00177410);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00177410 sub_177410 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_177410(a, b) [datSetHeroName]: the hero's two names in gGlobalWork: +0x00 = a, +0x12 = b (18 bytes each, the
// first 36 bytes cleared first, copied up to the NUL), then the display copies (sub_1774E0).
void sub_177410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177410
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    a1 = 0;
    a2 = 36;
    jal(ctx, 0x177438u, gen::fn_memset_00521408);
    a1 = 0;
    v1 = 0x830000;
    v1 = addiu(v1, 25088);  // &0x836200
    for (;;) {
        // 0x00177470
        charge(ctx, 3);
        v0 = slti(a1, 18);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00177454
            charge(ctx, 4);
            v0 = addu(s1, a1);
            lb(a0, v0, 0);
            if (a0 != 0) {
                // 0x00177464
                charge(ctx, 3);
                v0 = addu(v1, a1);
                sb(a0, v0, 0);
                a1 = addiu(a1, 1);
                continue;
            }
        }
        break;
    }
    // 0x0017747c
    charge(ctx, 5);
    a1 = 0;
    v1 = 0x830000;
    v1 = addiu(v1, 25088);  // &0x836200
    for (;;) {
        // 0x001774ac
        charge(ctx, 3);
        v0 = slti(a1, 18);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00177490
            charge(ctx, 4);
            v0 = addu(s0, a1);
            lb(a0, v0, 0);
            if (a0 != 0) {
                // 0x001774a0
                charge(ctx, 3);
                v0 = addu(v1, a1);
                sb(a0, v0, 18);
                a1 = addiu(a1, 1);
                continue;
            }
        }
        break;
    }
    // 0x001774b8
    charge(ctx, 8);
    jal(ctx, 0x1774B8u, gen::fn_sub_1774E0_001774e0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001774E0 sub_1774E0 -- 188 bytes; frame 0x10: ra sp+0x0
// sub_1774E0 [datBuildHeroNameStrings]: 0x833BB0 = name +0x00, 0x833BD0 = name +0x12 (18 bytes each),
// 0x833BF0 = sprintf("%s %s", 0x833BD0, 0x833BB0) -- the full name.
void sub_1774E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001774e0
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x830000;
    a0 = addiu(a0, 15280);  // &0x833BB0
    a1 = 0;
    a2 = 18;
    jal(ctx, 0x1774F8u, gen::fn_memset_00521408);
    a0 = 0x830000;
    a0 = addiu(a0, 15312);  // &0x833BD0
    a1 = 0;
    a2 = 18;
    jal(ctx, 0x177510u, gen::fn_memset_00521408);
    a0 = 0x830000;
    a0 = addiu(a0, 15344);  // &0x833BF0
    a1 = 0;
    a2 = 36;
    jal(ctx, 0x177528u, gen::fn_memset_00521408);
    a0 = 0x830000;
    a0 = addiu(a0, 15280);  // &0x833BB0
    a1 = 0x830000;
    a1 = addiu(a1, 25088);  // &0x836200
    a2 = 18;
    jal(ctx, 0x177544u, gen::fn_memcpy_00521250);
    a0 = 0x830000;
    a0 = addiu(a0, 15312);  // &0x833BD0
    a1 = 0x830000;
    a1 = addiu(a1, 25106);  // &0x836212
    a2 = 18;
    jal(ctx, 0x177560u, gen::fn_memcpy_00521250);
    a0 = 0x830000;
    a0 = addiu(a0, 15344);  // &0x833BF0
    a1 = addiu(gp, -27768);  // "%s %s"
    a2 = 0x830000;
    a2 = addiu(a2, 15312);  // &0x833BD0
    a3 = 0x830000;
    a3 = addiu(a3, 15280);  // &0x833BB0
    jal(ctx, 0x177584u, gen::fn_sprintf_00523ac8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001775A0 sub_1775A0 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1775A0(pc) [datGetCharFullName]: the full-name string of character pc: in The Journey the hero (pc 1) is the
// built string 0x833BF0, others the table 0x5E35E0[pc]; in The Answer pc 1 is 0x5E35EC's string and pc 9 0x5E35E0[0].
void sub_1775A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001775a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1775B0u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x00177600
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x00177624
            charge(ctx, 3);
            v0 = 9;
            if (v1 != v0) {
                // 0x00177640
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 13792);  // &0x5E35E0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x00177630
                charge(ctx, 4);
                v0 = 0x5E0000;
                lw(v0, v0, 13792);  // 0x5E35E0
            }
        } else {
            // 0x00177614
            charge(ctx, 4);
            v0 = 0x5E0000;
            lw(v0, v0, 13804);  // 0x5E35EC
        }
    } else {
        // 0x001775c0
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x001775e4
            charge(ctx, 5);
            v1 = sll(v1, 2);
            v0 = 0x5E0000;
            v0 = addiu(v0, 13792);  // &0x5E35E0
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
        } else {
            // 0x001775d4
            charge(ctx, 4);
            v0 = 0x830000;
            v0 = addiu(v0, 15344);  // &0x833BF0
        }
        // 0x001775f8
        charge(ctx, 2);
    }
    // 0x00177654 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00177670 sub_177670 -- 280 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_177670(pc) [datGetCharNameA]: name A (the hero's +0x00 copy 0x833BB0 in The Journey) or the per-character
// string of 0x5E3790[pc] (pc < 11; 0x5E35E0[pc] above); The Answer: pc 1 -> 0x5E379C, pc 9 -> 0x5E3790[0].
void sub_177670(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177670
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x177680u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x001776f8
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x0017771c
            charge(ctx, 3);
            at = slti(v1, 11);
            if (at == 0) {
                // 0x00177760
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 13792);  // &0x5E35E0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x00177728
                charge(ctx, 3);
                v0 = 9;
                if (v1 != v0) {
                    // 0x00177744
                    charge(ctx, 5);
                    v1 = sll(v1, 2);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, 14224);  // &0x5E3790
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                } else {
                    // 0x00177734
                    charge(ctx, 4);
                    v0 = 0x5E0000;
                    lw(v0, v0, 14224);  // 0x5E3790
                }
                // 0x00177758
                charge(ctx, 2);
            }
        } else {
            // 0x0017770c
            charge(ctx, 4);
            v0 = 0x5E0000;
            lw(v0, v0, 14236);  // 0x5E379C
        }
    } else {
        // 0x00177690
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x001776b4
            charge(ctx, 3);
            at = slti(v1, 11);
            if (at == 0) {
                // 0x001776dc
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 13792);  // &0x5E35E0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x001776c0
                charge(ctx, 7);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 14224);  // &0x5E3790
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            }
            // 0x001776f0
            charge(ctx, 2);
        } else {
            // 0x001776a4
            charge(ctx, 4);
            v0 = 0x830000;
            v0 = addiu(v0, 15280);  // &0x833BB0
        }
    }
    // 0x00177774 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00177790 sub_177790 -- 280 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_177790(pc) [datGetCharNameB]: as sub_177670 with name B (0x833BD0) and the table 0x5E37D0 (The Answer: pc 1 ->
// 0x5E37DC, pc 9 -> 0x5E37D0[0]).
void sub_177790(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177790
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1777A0u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x00177818
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x0017783c
            charge(ctx, 3);
            at = slti(v1, 11);
            if (at == 0) {
                // 0x00177880
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 13792);  // &0x5E35E0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x00177848
                charge(ctx, 3);
                v0 = 9;
                if (v1 != v0) {
                    // 0x00177864
                    charge(ctx, 5);
                    v1 = sll(v1, 2);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, 14288);  // &0x5E37D0
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                } else {
                    // 0x00177854
                    charge(ctx, 4);
                    v0 = 0x5E0000;
                    lw(v0, v0, 14288);  // 0x5E37D0
                }
                // 0x00177878
                charge(ctx, 2);
            }
        } else {
            // 0x0017782c
            charge(ctx, 4);
            v0 = 0x5E0000;
            lw(v0, v0, 14300);  // 0x5E37DC
        }
    } else {
        // 0x001777b0
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 != v0) {
            // 0x001777d4
            charge(ctx, 3);
            at = slti(v1, 11);
            if (at == 0) {
                // 0x001777fc
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 13792);  // &0x5E35E0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x001777e0
                charge(ctx, 7);
                v1 = sll(v1, 2);
                v0 = 0x5E0000;
                v0 = addiu(v0, 14288);  // &0x5E37D0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            }
            // 0x00177810
            charge(ctx, 2);
        } else {
            // 0x001777c4
            charge(ctx, 4);
            v0 = 0x830000;
            v0 = addiu(v0, 15312);  // &0x833BD0
        }
    }
    // 0x00177894 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001778B0 sub_1778B0 -- 240 bytes; frame 0x10: ra sp+0x0
// sub_1778B0(pc) [datGetCharCallName]: the name a character is called by: name B (sub_177790) for pc 1, 2, 4..9,
// name A (sub_177670) otherwise (the 9-case jump table).
void sub_1778B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001778b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    at = sltiu(v0, 11);
    if (at != 0) {
        // 0x001778cc
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25808);  // &0x7B64D0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1778E8u:  // table[1]
            // 0x001778e8
            charge(ctx, 4);
            jal(ctx, 0x1778E8u, gen::fn_sub_177790_00177790);
            break;
        case 0x1778F8u:  // table[2]
            // 0x001778f8
            charge(ctx, 4);
            jal(ctx, 0x1778F8u, gen::fn_sub_177790_00177790);
            break;
        case 0x177908u:  // table[3]
            // 0x00177908
            charge(ctx, 4);
            jal(ctx, 0x177908u, gen::fn_sub_177670_00177670);
            break;
        case 0x177918u:  // table[4]
            // 0x00177918
            charge(ctx, 4);
            jal(ctx, 0x177918u, gen::fn_sub_177790_00177790);
            break;
        case 0x177928u:  // table[5]
            // 0x00177928
            charge(ctx, 4);
            jal(ctx, 0x177928u, gen::fn_sub_177790_00177790);
            break;
        case 0x177938u:  // table[6]
            // 0x00177938
            charge(ctx, 4);
            jal(ctx, 0x177938u, gen::fn_sub_177790_00177790);
            break;
        case 0x177948u:  // table[7]
            // 0x00177948
            charge(ctx, 4);
            jal(ctx, 0x177948u, gen::fn_sub_177790_00177790);
            break;
        case 0x177958u:  // table[8]
            // 0x00177958
            charge(ctx, 4);
            jal(ctx, 0x177958u, gen::fn_sub_177790_00177790);
            break;
        case 0x177968u:  // table[9]
            // 0x00177968
            charge(ctx, 4);
            jal(ctx, 0x177968u, gen::fn_sub_177790_00177790);
            break;
        case 0x177978u:  // table[10]
            // 0x00177978
            charge(ctx, 4);
            jal(ctx, 0x177978u, gen::fn_sub_177670_00177670);
            break;
        case 0x177988u:  // table[0]
        L_00177988:
            charge(ctx, 2);
            jal(ctx, 0x177988u, gen::fn_sub_177670_00177670);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00177990 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_00177988;
}

// 0x001779A0 sub_1779A0 -- 156 bytes; leaf frame (no stack)
// sub_1779A0 [datClearRecordBackups]: for the ten party records (pc 2..11): the item ids of the four backup entries
// at record +0x130 and the four words at record +0x110 are cleared.
void sub_1779A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x001779a0
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 16400);  // &0x834010
    for (;;) {
        // 0x00177a28
        charge(ctx, 3);
        v1 = slti(t0, 10);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001779b4
        charge(ctx, 9);
        a3 = 0;
        v1 = sll(t0, 5);
        a1 = subu(v1, t0);
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        v1 = sll(v1, 2);
        a2 = addu(a0, v1);
        for (;;) {
            // 0x001779f0
            charge(ctx, 3);
            v1 = slti(a3, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001779d8
            charge(ctx, 6);
            v1 = sll(a3, 2);
            v1 = addu(v1, a3);
            v1 = sll(v1, 2);
            v1 = addu(a2, v1);
            sh(zero, v1, 304);
            a3 = addiu(a3, 1);
        }
        // 0x001779fc
        charge(ctx, 3);
        a1 = 0;
        for (;;) {
            // 0x00177a18
            charge(ctx, 3);
            v1 = slti(a1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00177a08
            charge(ctx, 4);
            v1 = sll(a1, 2);
            v1 = addu(a2, v1);
            sw(zero, v1, 272);
            a1 = addiu(a1, 1);
        }
        // 0x00177a24
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x00177a34
    charge(ctx, 2);
}

// 0x00177A40 sub_177A40 -- 68 bytes; leaf frame (no stack)
// sub_177A40(pc, i): backup entry i of record pc (+0x130 + 20 i) holds an item (u16 id != 0).
void sub_177A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177a40
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 14968);  // &0x833A78
    v1 = addu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    v0 = sltu(0, v0);
}

// 0x00177A90 sub_177A90 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_177A90(pc, i): the address of backup entry i of record pc (K_Assert 3874 unless 2 <= pc < 12, 3875 unless i < 4).
void sub_177A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177a90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v0 = a0 & 0xFFFF;
    s1 = addiu(v0, -2);
    {  // the inlined check: K_Assert unless (i64(s1) >= 0) and not (v0 == 0)
        bool bad = true;
        if (i64(s1) >= 0) {
            // 0x00177ab4
            charge(ctx, 3);
            v0 = slti(s1, 10);
            bad = v0 == 0;
        }
        if (bad) {  // 0x00177ac0: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 3874;
            jal(ctx, 0x177ACCu, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x00177ad4
    charge(ctx, 2);
    if (i64(s0) >= 0) {
        // 0x00177adc
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            goto L_00177ae8;
        }
        // 0x00177afc (the shared epilogue, written out on this path)
        charge(ctx, 19);
        v0 = sll(s1, 5);
        v1 = subu(v0, s1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v1 = addu(v0, v1);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = addiu(v0, 304);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00177ae8:
    charge(ctx, 5);
    a0 = 0x5E0000;
    a0 = addiu(a0, 12440);  // "g_data.c"
    a1 = 3875;
    jal(ctx, 0x177AF4u, gen::fn_sub_19D3F0_0019d3f0);
    // 0x00177afc (the shared epilogue, written out on this path)
    charge(ctx, 19);
    v0 = sll(s1, 5);
    v1 = subu(v0, s1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 16400);  // &0x834010
    v1 = addu(v0, v1);
    v0 = sll(s0, 2);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 304);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00177B50 sub_177B50 -- 60 bytes; leaf frame (no stack)
// sub_177B50(pc, i): clears the item id of backup entry i of record pc.
void sub_177B50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177b50
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 14968);  // &0x833A78
    a0 = addu(v1, a0);
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    sh(zero, v1, 0);
}

// 0x00177B90 sub_177B90 -- 116 bytes; frame 0x10: ra sp+0x0
// sub_177B90(pc, dst, src): memcpy(backup entry dst (+0x130), equipment entry src (+0x5C), 20) of record pc.
void sub_177B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177b90
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0 & 0xFFFF;
    v1 = addiu(v0, -2);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 16400);  // &0x834010
    a0 = addu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    v1 = addu(a0, v0);
    v0 = sll(a2, 2);
    v0 = addu(v0, a2);
    v0 = sll(v0, 2);
    v0 = addu(a0, v0);
    a0 = addiu(v1, 304);
    a1 = addiu(v0, 92);
    a2 = 20;
    jal(ctx, 0x177BECu, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00177C10 sub_177C10 -- 64 bytes; leaf frame (no stack)
// sub_177C10(pc, i): sets bit 0 of word i at record +0x110.
void sub_177C10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177c10
    enter(ctx, 16);  // entry check point + this block's cycles
    a0 = addiu(a0, -2);
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 16672);  // &0x834120
    a0 = addu(v1, a0);
    v1 = sll(a1, 2);
    a0 = addu(v1, a0);
    lw(v1, a0, 0);
    v1 = v1 | 0x1;
    sw(v1, a0, 0);
}

// 0x00177C50 sub_177C50 -- 68 bytes; leaf frame (no stack)
// sub_177C50(pc, i): clears bit 0 of word i at record +0x110.
void sub_177C50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177c50
    enter(ctx, 17);  // entry check point + this block's cycles
    a0 = addiu(a0, -2);
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 16672);  // &0x834120
    a0 = addu(v1, a0);
    v1 = sll(a1, 2);
    a1 = addu(v1, a0);
    lw(a0, a1, 0);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, a1, 0);
}

// 0x00177CA0 sub_177CA0 -- 60 bytes; leaf frame (no stack)
// sub_177CA0(pc, i): bit 0 of word i at record +0x110.
void sub_177CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177ca0
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = addiu(a0, -2);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 16672);  // &0x834120
    v1 = addu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
}

// 0x00177CE0 sub_177CE0 -- 44 bytes; leaf frame (no stack)
// sub_177CE0(pc, v): record pc +0x360 (s32) = v.
void sub_177CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00177ce0
    enter(ctx, 11);  // entry check point + this block's cycles
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 15528);  // &0x833CA8
    v1 = addu(v1, a0);
    sw(a1, v1, 0);
}

// 0x00177D10 sub_177D10 -- 44 bytes; leaf frame (no stack)
// sub_177D10(pc): record pc +0x360 (s32).
void sub_177D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00177d10
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = sll(a0, 5);
    v1 = subu(v0, a0);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 15528);  // &0x833CA8
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x00177D40 sub_177D40 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_177D40 [datAllocHeroStocks] (kwlnInitMain): allocates the hero's equipment stock (300 x 20 bytes) and item
// counts (300 x 2) through the RW allocator slot *0x960184 (calloc-style (n, size, hint)) into gGlobalWork +0x594 /
// +0x598.
void sub_177D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00177d40
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 388);  // &0x960184
    a0 = 300;
    a1 = 20;
    a2 = 0x40000;
    lw(v0, s0, 0);  // 0x960184
    jalr(ctx, 0x177D64u, v0.u());
    v1 = 0x830000;
    sw(v0, v1, 26516);  // 0x836794
    a0 = 300;
    a1 = 2;
    a2 = 0x40000;
    lw(v0, s0, 0);  // 0x960184
    jalr(ctx, 0x177D84u, v0.u());
    v1 = 0x830000;
    sw(v0, v1, 26520);  // 0x836798
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017AC60 sub_17AC60 -- 296 bytes; frame 0x10
// sub_17AC60(key) [datDatedListPush]: the 256-entry list of 4-byte entries at gGlobalWork +0x5A7 (0x8367A7; entry
// bytes {a, b, c, d}, a = 0 ends the list): an entry whose bytes a, b, c equal the key's low three bytes is removed
// (the rest shifted down, the last byte 0x836BA3 cleared), then the key is stored (4 unaligned bytes) in the first
// free entry.
void sub_17AC60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29};
    // 0x0017ac60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sw(a0, sp, 0xC);
    t6 = 0;
    lbu(t4, sp, 0xC);
    lbu(t3, sp, 0xD);
    lbu(t2, sp, 0xE);
    t1 = 0x830000;
    t1 = addiu(t1, 25088);  // &0x836200
    v1 = 0x830000;
    for (;;) {
        // 0x0017ad0c
        charge(ctx, 3);
        a0 = slti(t6, 256);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017ac8c
        charge(ctx, 5);
        a0 = sll(t6, 2);
        a1 = addu(t1, a0);
        lbu(a0, a1, 1447);
        if (a0 != 0) {
            // 0x0017aca0
            charge(ctx, 2);
            if (a0 == t4) {
                // 0x0017aca8
                charge(ctx, 3);
                lbu(a0, a1, 1448);
                if (a0 == t3) {
                    // 0x0017acb4
                    charge(ctx, 3);
                    lbu(a0, a1, 1449);
                    if (a0 == t2) {
                        // 0x0017acc0
                        charge(ctx, 3);
                        t5 = t6;
                        for (;;) {
                            // 0x0017acf8
                            charge(ctx, 3);
                            a0 = slti(t5, 255);
                            if (a0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0017accc
                            charge(ctx, 11);
                            a0 = sll(t5, 2);
                            t0 = addu(t1, a0);
                            lbu(a3, t0, 1451);
                            lbu(a2, t0, 1452);
                            lbu(a1, t0, 1453);
                            lbu(a0, t0, 1454);
                            sb(a3, t0, 1447);
                            sb(a2, t0, 1448);
                            sb(a1, t0, 1449);
                            sb(a0, t0, 1450);
                            t5 = addiu(t5, 1);
                        }
                        // 0x0017ad04
                        charge(ctx, 1);
                        sb(zero, v1, 27555);
                    }
                }
            }
        }
        // 0x0017ad08
        charge(ctx, 1);
        t6 = addiu(t6, 1);
    }
    // 0x0017ad18
    charge(ctx, 5);
    a1 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0017ad70
        charge(ctx, 3);
        v1 = slti(a1, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017ad2c
        charge(ctx, 6);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        a3 = addiu(v1, 1447);
        lbu(v1, v1, 1447);
        if (v1 == 0) {
            // 0x0017ad44
            charge(ctx, 10);
            lbu(a2, sp, 0xC);
            lbu(a1, sp, 0xD);
            lbu(a0, sp, 0xE);
            lbu(v1, sp, 0xF);
            sb(a2, a3, 0);
            sb(a1, a3, 1);
            sb(a0, a3, 2);
            sb(v1, a3, 3);
            // 0x0017ad7c (the shared epilogue, written out on this path)
            charge(ctx, 3);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0017ad6c
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x0017ad7c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
    return;
}

// 0x0017AD90 sub_17AD90 -- 96 bytes; leaf frame (no stack)
// sub_17AD90 [datDatedListPop]: clears the first byte of the last entry of the 0x8367A7 list (none when it is empty).
void sub_17AD90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0017ad90
    enter(ctx, 5);  // entry check point + this block's cycles
    a2 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0017addc
        charge(ctx, 3);
        v1 = slti(a2, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017ada4
        charge(ctx, 5);
        a1 = sll(a2, 2);
        v1 = addu(a0, a1);
        lbu(v1, v1, 1447);
        if (v1 == 0) {
            // 0x0017adb8
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x0017adc0
                charge(ctx, 6);
                v1 = 0x830000;
                v1 = addiu(v1, 26531);  // &0x8367A3
                v1 = addu(v1, a1);
                sb(zero, v1, 0);
            }
            // 0x0017ade8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0017add8
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0017ade8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
}

// 0x0017ADF0 sub_17ADF0 -- 56 bytes; leaf frame (no stack)
// sub_17ADF0 [datDatedListClear]: clears the first byte of all 256 entries of the 0x8367A7 list.
void sub_17ADF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0017adf0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0017ae14
        charge(ctx, 3);
        v1 = slti(a1, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017ae04
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sb(zero, v1, 1447);
        a1 = addiu(a1, 1);
    }
    // 0x0017ae20
    charge(ctx, 2);
}

// 0x0017AE30 sub_17AE30 -- 28 bytes; leaf frame (no stack)
// sub_17AE30(i): the address of entry i of the 0x8367A7 list.
void sub_17AE30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0017ae30
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 25088);  // &0x836200
    v0 = addu(v0, v1);
    v0 = addiu(v0, 1447);
}

// 0x0017AE50 sub_17AE50 -- 196 bytes; leaf frame (no stack)
// sub_17AE50(item) [datHasItem]: an item reference (bit 15 set: an index into the hero's equipment stock, whose entry
// gives the id) is held: ids < 4000 are searched in the 300 stock entries, others need a non-zero count in the
// hero's count table (*gGlobalWork +0x598, item - 4000). 1 / 0.
void sub_17AE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0017ae50
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = v1 & 0x8000;
    if (v0 != 0) {
        // 0x0017ae60
        charge(ctx, 7);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        lw(v0, v0, 26516);  // 0x836794
        v0 = addu(v0, v1);
        lhu(a0, v0, 0);
    }
    // 0x0017ae7c
    charge(ctx, 4);
    a1 = a0 & 0xFFFF;
    v0 = slti(a1, 4000);
    if (v0 != 0) {
        // 0x0017aebc
        charge(ctx, 5);
        a0 = 0;
        v0 = 0x830000;
        lw(v1, v0, 26516);  // 0x836794
        for (;;) {
            // 0x0017aefc
            charge(ctx, 3);
            v0 = slti(a0, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017aed0
            charge(ctx, 7);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lhu(v0, v0, 0);
            if (a1 == v0) {
                // 0x0017aeec
                charge(ctx, 3);
                v0 = 1;
                // 0x0017af0c (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
            // 0x0017aef8
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
    L_0017af08:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0017ae8c
        charge(ctx, 9);
        v0 = 0x830000;
        lw(v1, v0, 26520);  // 0x836798
        v0 = dsll32(a0, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        lhu(v0, v0, -8000);
        if (v0 == 0) {
            goto L_0017af08;
        }
        // 0x0017aeb0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0017af0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
}

// 0x0017AF20 sub_17AF20 -- 172 bytes; frame 0x30: ra sp+0x0
// sub_17AF20(item) [datGiveItem]: gives one: a consumable (id >= 4000) through sub_170860(1, ..), an equipment id is
// rolled into a 20-byte entry on the frame (sub_1828D0) and stored in the first free stock slot (sub_1830C0).
void sub_17AF20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017af20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    v1 = a0 & 0xFFFF;
    v0 = v1 & 0x8000;
    if (v0 != 0) {
        // 0x0017af38
        charge(ctx, 7);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        lw(v0, v0, 26516);  // 0x836794
        v0 = addu(v0, v1);
        lhu(a0, v0, 0);
    }
    // 0x0017af54
    charge(ctx, 4);
    v0 = a0 & 0xFFFF;
    v0 = slti(v0, 4000);
    if (v0 != 0) {
        // 0x0017af9c
        charge(ctx, 8);
        a0 = dsll32(a0, 16);
        a0 = dsra32(a0, 16);
        a1 = addiu(sp, 0x10);
        jal(ctx, 0x17AFA8u, gen::fn_sub_1828D0_001828d0);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x17AFB4u, gen::fn_sub_1830C0_001830c0);
    } else {
        // 0x0017af64
        charge(ctx, 14);
        a1 = dsll32(a0, 16);
        a1 = dsra32(a1, 16);
        v0 = 0x830000;
        lw(v1, v0, 26520);  // 0x836798
        v0 = sll(a1, 1);
        v0 = addu(v0, v1);
        lhu(v0, v0, -8000);
        v0 = addiu(v0, 1);
        a2 = v0 & 0xFFFF;
        a0 = 1;
        jal(ctx, 0x17AF8Cu, gen::fn_sub_170860_00170860);
    }
    // 0x0017afbc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017AFD0 sub_17AFD0 -- 160 bytes; leaf frame (no stack)
// sub_17AFD0(item) [datHasRoomForItem]: 1 for a consumable, else 1 when the hero's equipment stock has a free entry.
void sub_17AFD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0017afd0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = v1 & 0x8000;
    if (v0 != 0) {
        // 0x0017afe0
        charge(ctx, 7);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        lw(v0, v0, 26516);  // 0x836794
        v0 = addu(v0, v1);
        lhu(a0, v0, 0);
    }
    // 0x0017affc
    charge(ctx, 4);
    v0 = a0 & 0xFFFF;
    v0 = slti(v0, 4000);
    if (v0 != 0) {
        // 0x0017b018
        charge(ctx, 5);
        a0 = 0;
        v0 = 0x830000;
        lw(v1, v0, 26516);  // 0x836794
        for (;;) {
            // 0x0017b058
            charge(ctx, 3);
            v0 = slti(a0, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017b02c
            charge(ctx, 7);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lhu(v0, v0, 0);
            if (v0 == 0) {
                // 0x0017b048
                charge(ctx, 3);
                v0 = 1;
                // 0x0017b068 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
            // 0x0017b054
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
        // 0x0017b064
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0017b00c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0017b068 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
}

// 0x0017B070 sub_17B070 -- 140 bytes; frame 0x10: ra sp+0x0
// sub_17B070(item) [datTakeItem]: a stock reference (negative) clears that entry's id; a consumable with a non-zero
// count is set to count - 1 (sub_170860(1, id, count - 1)).
void sub_17B070(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b070
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0 & 0xFFFF;
    v1 = a1 & 0x8000;
    if (v1 == 0) {
        // 0x0017b0b0
        charge(ctx, 10);
        a1 = dsll32(a0, 16);
        a1 = dsra32(a1, 16);
        a0 = sll(a1, 1);
        v1 = 0x830000;
        lw(v1, v1, 26520);  // 0x836798
        v1 = addiu(v1, -8000);
        v1 = addu(v1, a0);
        lhu(v1, v1, 0);
        if (v1 != 0) {
            // 0x0017b0d8
            charge(ctx, 5);
            v0 = addiu(v1, -1);
            a2 = v0 & 0xFFFF;
            a0 = 1;
            jal(ctx, 0x17B0E4u, gen::fn_sub_170860_00170860);
        }
    } else {
        // 0x0017b088
        charge(ctx, 10);
        a0 = a1 & 0x7FFF;
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        lw(v1, v1, 26516);  // 0x836794
        v1 = addu(v1, a0);
        sh(zero, v1, 0);
    }
    // 0x0017b0ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017B100 sub_17B100 -- 88 bytes; frame 0x10: ra sp+0x0
// sub_17B100(item): sub_171110(id, 2) on the resolved item id (a stock reference takes its entry's id).
void sub_17B100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b100
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = a0 & 0xFFFF;
    v0 = v1 & 0x8000;
    if (v0 != 0) {
        // 0x0017b118
        charge(ctx, 7);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        lw(v0, v0, 26516);  // 0x836794
        v0 = addu(v0, v1);
        lhu(a0, v0, 0);
    }
    // 0x0017b134
    charge(ctx, 9);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    a1 = 2;
    jal(ctx, 0x17B140u, gen::fn_sub_171110_00171110);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017B160 sub_17B160 -- 16 bytes; leaf frame (no stack)
// sub_17B160: gGlobalWork +0x44E8 (s32, a battle-counted word) = 0.
void sub_17B160(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3};
    // 0x0017b160
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x840000;
    sw(zero, v1, -22808);  // 0x83A6E8
}

// 0x0017B170 sub_17B170 -- 16 bytes; leaf frame (no stack)
// sub_17B170: gGlobalWork +0x44E8.
void sub_17B170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0017b170
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x840000;
    lw(v0, v0, -22808);  // 0x83A6E8
}

// 0x0017B180 sub_17B180 -- 28 bytes; leaf frame (no stack)
// sub_17B180(n): gGlobalWork +0x44E8 += n; returns the new value (btlMainInitStateInit).
void sub_17B180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0017b180
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x840000;
    lw(v0, v0, -22808);  // 0x83A6E8
    v0 = addu(v0, a0);
    v1 = 0x840000;
    sw(v0, v1, -22808);  // 0x83A6E8
}

// 0x0017B1A0 sub_17B1A0 -- 56 bytes; leaf frame (no stack)
// sub_17B1A0: clears the 11-word bit array at gGlobalWork +0x46C4 (0x83A8C4; sub_17B1E0 / sub_17B220 / sub_17B260).
void sub_17B1A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0017b1a0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0017b1c4
        charge(ctx, 3);
        v1 = slti(a1, 11);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017b1b4
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 18116);
        a1 = addiu(a1, 1);
    }
    // 0x0017b1d0
    charge(ctx, 2);
}

// 0x0017B1E0 sub_17B1E0 -- 56 bytes; leaf frame (no stack)
// sub_17B1E0(i): sets bit i of the 0x83A8C4 array.
void sub_17B1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0017b1e0
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0 & 0xFFFF;
    a0 = a2 & 0x1F;
    v1 = 1;
    a1 = sllv(v1, a0);
    v1 = sra(a2, 5);
    a0 = sll(v1, 2);
    v1 = 0x840000;
    v1 = addiu(v1, -22332);  // &0x83A8C4
    a0 = addu(v1, a0);
    lw(v1, a0, 0);
    v1 = v1 | a1;
    sw(v1, a0, 0);
}

// 0x0017B220 sub_17B220 -- 60 bytes; leaf frame (no stack)
// sub_17B220(i): clears bit i of the 0x83A8C4 array.
void sub_17B220(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0017b220
    enter(ctx, 15);  // entry check point + this block's cycles
    a2 = a0 & 0xFFFF;
    a0 = a2 & 0x1F;
    v1 = 1;
    v1 = sllv(v1, a0);
    a1 = nor(v1, 0);
    v1 = sra(a2, 5);
    a0 = sll(v1, 2);
    v1 = 0x840000;
    v1 = addiu(v1, -22332);  // &0x83A8C4
    a0 = addu(v1, a0);
    lw(v1, a0, 0);
    v1 = v1 & a1;
    sw(v1, a0, 0);
}

// 0x0017B260 sub_17B260 -- 52 bytes; leaf frame (no stack)
// sub_17B260(i): bit i of the 0x83A8C4 array (the masked word, not 0/1).
void sub_17B260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0017b260
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = a0 & 0xFFFF;
    v0 = sra(a1, 5);
    v1 = sll(v0, 2);
    v0 = 0x840000;
    v0 = addiu(v0, -22332);  // &0x83A8C4
    a0 = addu(v0, v1);
    v1 = a1 & 0x1F;
    v0 = 1;
    v1 = sllv(v0, v1);
    lw(v0, a0, 0);
    v0 = v0 & v1;
}

// 0x0017B2A0 sub_17B2A0 -- 56 bytes; leaf frame (no stack)
// sub_17B2A0: clears the 106-word bit array at gGlobalWork +0x46F0 (0x83A8F0; 336 x 10 bits, sub_17B2E0 / sub_17B3D0).
void sub_17B2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0017b2a0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0017b2c4
        charge(ctx, 3);
        v1 = slti(a1, 106);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017b2b4
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 18160);
        a1 = addiu(a1, 1);
    }
    // 0x0017b2d0
    charge(ctx, 2);
}

// 0x0017B2E0 sub_17B2E0 -- 236 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17B2E0(id, j, on): bit 10 id + j of the 0x83A8F0 array = on (K_Assert 5681 unless id < 336, 5682 unless j < 10).
void sub_17B2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b2e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    s2 = a0 & 0xFFFF;
    v1 = slti(s2, 336);
    if (v1 == 0) {
        // 0x0017b30c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5681;
        jal(ctx, 0x17B318u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017b320
    charge(ctx, 4);
    s1 = s1 & 0xFFFF;
    v1 = slti(s1, 10);
    if (v1 == 0) {
        // 0x0017b330
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5682;
        jal(ctx, 0x17B33Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017b344
    charge(ctx, 10);
    v1 = sll(s2, 2);
    v1 = addu(v1, s2);
    v1 = sll(v1, 1);
    v1 = addu(s1, v1);
    a1 = srl(v1, 5);
    a0 = v1 & 0x1F;
    v1 = 1;
    a2 = sllv(v1, a0);
    if (s0 == 0) {
        // 0x0017b390
        charge(ctx, 8);
        a0 = sll(a1, 2);
        v1 = 0x840000;
        v1 = addiu(v1, -22288);  // &0x83A8F0
        a1 = addu(v1, a0);
        a0 = nor(a2, 0);
        lw(v1, a1, 0);
        v1 = v1 & a0;
        sw(v1, a1, 0);
    } else {
        // 0x0017b36c
        charge(ctx, 9);
        a0 = sll(a1, 2);
        v1 = 0x840000;
        v1 = addiu(v1, -22288);  // &0x83A8F0
        a0 = addu(v1, a0);
        lw(v1, a0, 0);
        v1 = v1 | a2;
        sw(v1, a0, 0);
    }
    // 0x0017b3b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0017B3D0 sub_17B3D0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17B3D0(id, j): bit 10 id + j of the 0x83A8F0 array, 0/1 (K_Assert 5700 / 5701).
void sub_17B3D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b3d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = a0 & 0xFFFF;
    v0 = slti(s1, 336);
    if (v0 == 0) {
        // 0x0017b3f4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5700;
        jal(ctx, 0x17B400u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017b408
    charge(ctx, 4);
    s0 = s0 & 0xFFFF;
    v0 = slti(s0, 10);
    if (v0 == 0) {
        // 0x0017b418
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5701;
        jal(ctx, 0x17B424u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017b42c (the shared epilogue, written out on this path)
    charge(ctx, 21);
    v0 = sll(s1, 2);
    v0 = addu(v0, s1);
    v0 = sll(v0, 1);
    a1 = addu(s0, v0);
    v0 = srl(a1, 5);
    v1 = sll(v0, 2);
    v0 = 0x840000;
    v0 = addiu(v0, -22288);  // &0x83A8F0
    a0 = addu(v0, v1);
    v1 = a1 & 0x1F;
    v0 = 1;
    v1 = sllv(v0, v1);
    lw(v0, a0, 0);
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017B480 sub_17B480 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17B480(skill): the s8 element byte (+1) of the skill's 2-byte row in gBtlSkillElementTbl (K_Assert 5739
// unless skill < 0x270).
void sub_17B480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b480
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 624);
    if (v0 == 0) {
        // 0x0017b4a0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5739;
        jal(ctx, 0x17B4ACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017b4b4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v1, gp, -18684);  // gBtlSkillElementTbl
    v0 = s0 & 0xFFFF;
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    lb(v0, v0, 1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017B4E0 sub_17B4E0 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_17B4E0: tail call of datCalcIsSkillUsableOnField with the caller's arguments.
void sub_17B4E0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b4e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x17B4E8u, gen::fn_datCalcIsSkillUsableOnField_00300af0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017B500 sub_17B500 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17B500(pc, x): sub_3086C0(unit of pc, x) -- the unit is the hero's DatUnit (gGlobalWork +0x24) for pc 1, else
// record pc +4 (K_Assert 737 unless pc < 11, inlined).
void sub_17B500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b500
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = dsll32(a0, 16);
    s1 = dsra32(s1, 16);
    v0 = 1;
    if (s1 != v0) {
        // 0x0017b538
        charge(ctx, 3);
        v0 = slti(s1, 11);
        if (v0 == 0) {
            // 0x0017b544
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 737;
            jal(ctx, 0x17B550u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0017b558
        charge(ctx, 10);
        v1 = addiu(s1, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);
    } else {
        // 0x0017b528
        charge(ctx, 4);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &0x836224
    }
    // 0x0017b580
    charge(ctx, 9);
    a1 = s0;
    jal(ctx, 0x17B584u, gen::fn_sub_3086C0_003086c0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017B5B0 sub_17B5B0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17B5B0(pc, x): sub_3083F0(unit of pc, x) (the same unit resolution).
void sub_17B5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b5b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = dsll32(a0, 16);
    s1 = dsra32(s1, 16);
    v0 = 1;
    if (s1 != v0) {
        // 0x0017b5e8
        charge(ctx, 3);
        v0 = slti(s1, 11);
        if (v0 == 0) {
            // 0x0017b5f4
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 737;
            jal(ctx, 0x17B600u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0017b608
        charge(ctx, 10);
        v1 = addiu(s1, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);
    } else {
        // 0x0017b5d8
        charge(ctx, 4);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &0x836224
    }
    // 0x0017b630
    charge(ctx, 9);
    a1 = s0;
    jal(ctx, 0x17B634u, gen::fn_sub_3083F0_003083f0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017B660 sub_17B660 -- 512 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17B660(pc, skill): skills 425 and 415 are answered from the flag bits of the 8-byte rows 0x5E3844 / 0x5E3840
// indexed by the unit's id (4 when set, else 0); any other skill is sub_3086F0(unit, skill). K_Assert 5802 unless
// 1 <= unit id < 11.
void sub_17B660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b660
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = 1;
    if (s0 != v0) {
        // 0x0017b698
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            // 0x0017b6a4
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 737;
            jal(ctx, 0x17B6B0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0017b6b8
        charge(ctx, 10);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v0 = addu(v0, v1);
        s0 = addiu(v0, 4);
    } else {
        // 0x0017b688
        charge(ctx, 4);
        s0 = 0x830000;
        s0 = addiu(s0, 25124);  // &0x836224
    }
    // 0x0017b6e0
    charge(ctx, 3);
    lhu(v0, s0, 2);
    {  // the inlined check: K_Assert unless (v0 != 0) and not (v0 == 0)
        bool bad = true;
        if (v0 != 0) {
            // 0x0017b6ec
            charge(ctx, 3);
            v0 = slti(v0, 11);
            bad = v0 == 0;
        }
        if (bad) {  // 0x0017b6f8: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 5802;
            jal(ctx, 0x17B704u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x0017b70c
    charge(ctx, 4);
    v1 = s1 & 0xFFFF;
    v0 = 425;
    if (v1 == v0) {
        // 0x0017b7b4
        charge(ctx, 9);
        lhu(v0, s0, 2);
        v1 = sll(v0, 3);
        v0 = 0x5E0000;
        v0 = addiu(v0, 14404);  // &0x5E3844
        v0 = addu(v0, v1);
        lw(a1, v0, 0);
        v0 = sra(a1, 5);
        if (i64(a1) < 0) {
            // 0x0017b7d8
            charge(ctx, 2);
            v0 = addiu(a1, 31);
            v0 = sra(v0, 5);
        }
        // 0x0017b7e0
        charge(ctx, 7);
        v1 = sll(v0, 2);
        v0 = 0x840000;
        v0 = addiu(v0, -24036);  // &g_datFlagWords
        a0 = addu(v0, v1);
        v1 = a1 & 0x1F;
        if (i64(a1) < 0) {
            // 0x0017b7fc
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0017b804
                charge(ctx, 1);
                v1 = addiu(v1, -32);
            }
        }
        // 0x0017b808
        charge(ctx, 6);
        v0 = 1;
        v1 = sllv(v0, v1);
        lw(v0, a0, 0);
        v0 = v0 & v1;
        if (v0 == 0) {
            // 0x0017b82c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0017b820
            charge(ctx, 3);
            v0 = 4;
        }
        // 0x0017b830
        charge(ctx, 2);
    } else {
        // 0x0017b71c
        charge(ctx, 3);
        v0 = 415;
        if (v1 == v0) {
            // 0x0017b730
            charge(ctx, 9);
            lhu(v0, s0, 2);
            v1 = sll(v0, 3);
            v0 = 0x5E0000;
            v0 = addiu(v0, 14400);  // &0x5E3840
            v0 = addu(v0, v1);
            lw(a1, v0, 0);
            v0 = sra(a1, 5);
            if (i64(a1) < 0) {
                // 0x0017b754
                charge(ctx, 2);
                v0 = addiu(a1, 31);
                v0 = sra(v0, 5);
            }
            // 0x0017b75c
            charge(ctx, 7);
            v1 = sll(v0, 2);
            v0 = 0x840000;
            v0 = addiu(v0, -24036);  // &g_datFlagWords
            a0 = addu(v0, v1);
            v1 = a1 & 0x1F;
            if (i64(a1) < 0) {
                // 0x0017b778
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0017b780
                    charge(ctx, 1);
                    v1 = addiu(v1, -32);
                }
            }
            // 0x0017b784
            charge(ctx, 6);
            v0 = 1;
            v1 = sllv(v0, v1);
            lw(v0, a0, 0);
            v0 = v0 & v1;
            if (v0 == 0) {
                // 0x0017b7a8
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0017b79c
                charge(ctx, 3);
                v0 = 4;
            }
            // 0x0017b7ac
            charge(ctx, 2);
        } else {
            // 0x0017b728
            charge(ctx, 2);
            // 0x0017b838
            charge(ctx, 4);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x17B840u, gen::fn_sub_3086F0_003086f0);
        }
    }
    // 0x0017b848 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017BB40 sub_17BB40 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17BB40(skill): byte +8 of the skill's 44-byte row in gBtlSkillTbl (K_Assert 5853 unless skill < 0x1D0).
void sub_17BB40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017bb40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 464);
    if (v0 == 0) {
        // 0x0017bb60
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5853;
        jal(ctx, 0x17BB6Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017bb74 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, -18680);  // gBtlSkillTbl
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lbu(v0, v0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017BBB0 sub_17BBB0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17BBB0(skill): byte +9 of the skill's 44-byte row in gBtlSkillTbl (K_Assert 5868).
void sub_17BBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017bbb0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 464);
    if (v0 == 0) {
        // 0x0017bbd0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5868;
        jal(ctx, 0x17BBDCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017bbe4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, -18680);  // gBtlSkillTbl
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lbu(v0, v0, 9);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017BC20 sub_17BC20 -- 484 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17BC20(user, target, skill, x): skills 425 / 415 answer 0 when the target's condition (u16 +0x4C of its record,
// gGlobalWork +0x6C for the hero) is 5, else 8; any other skill is sub_3068D0(skill, unit(user), unit(target), x).
// K_Assert 5890 unless 1 <= target < 11.
void sub_17BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017bc20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s3 = a2;
    s2 = a3;
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    {  // the inlined check: K_Assert unless (s0 != 0) and not (v0 == 0)
        bool bad = true;
        if (s0 != 0) {
            // 0x0017bc54
            charge(ctx, 3);
            v0 = slti(s0, 11);
            bad = v0 == 0;
        }
        if (bad) {  // 0x0017bc60: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 5890;
            jal(ctx, 0x17BC6Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x0017bc74
    charge(ctx, 4);
    v1 = s3 & 0xFFFF;
    v0 = 425;
    if (v1 != v0) {
        // 0x0017bc84
        charge(ctx, 3);
        v0 = 415;
        if (v1 == v0) {
            goto L_0017bc98;
        }
        // 0x0017bc90
        charge(ctx, 2);
        // 0x0017bd00
        charge(ctx, 5);
        s1 = dsll32(s1, 16);
        s1 = dsra32(s1, 16);
        v0 = 1;
        if (s1 != v0) {
            // 0x0017bd24
            charge(ctx, 3);
            v0 = slti(s1, 11);
            if (v0 == 0) {
                // 0x0017bd30
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 737;
                jal(ctx, 0x17BD3Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0017bd44
            charge(ctx, 10);
            v1 = addiu(s1, -2);
            v0 = sll(v1, 5);
            v1 = subu(v0, v1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x830000;
            v0 = addiu(v0, 16400);  // &0x834010
            v0 = addu(v0, v1);
            s1 = addiu(v0, 4);
        } else {
            // 0x0017bd14
            charge(ctx, 4);
            s1 = 0x830000;
            s1 = addiu(s1, 25124);  // &0x836224
        }
        // 0x0017bd6c
        charge(ctx, 3);
        v0 = 1;
        if (s0 != v0) {
            // 0x0017bd88
            charge(ctx, 3);
            v0 = slti(s0, 11);
            if (v0 == 0) {
                // 0x0017bd94
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 737;
                jal(ctx, 0x17BDA0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0017bda8
            charge(ctx, 10);
            v1 = addiu(s0, -2);
            v0 = sll(v1, 5);
            v1 = subu(v0, v1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x830000;
            v0 = addiu(v0, 16400);  // &0x834010
            v0 = addu(v0, v1);
            a2 = addiu(v0, 4);
        } else {
            // 0x0017bd78
            charge(ctx, 4);
            a2 = 0x830000;
            a2 = addiu(a2, 25124);  // &0x836224
        }
        // 0x0017bdd0
        charge(ctx, 5);
        a0 = s3;
        a1 = s1;
        a3 = s2;
        jal(ctx, 0x17BDDCu, gen::fn_sub_3068D0_003068d0);
        // 0x0017bde4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0017bc98:
    charge(ctx, 3);
    v0 = 1;
    if (s0 != v0) {
        // 0x0017bcb4
        charge(ctx, 9);
        v0 = sll(s0, 5);
        v1 = subu(v0, s0);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14740);  // &0x833994
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0017bca4
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25196);  // 0x83626C
    }
    // 0x0017bcd8
    charge(ctx, 4);
    v1 = v0 & 0xFFFF;
    v0 = 5;
    if (v1 != v0) {
        // 0x0017bcf4
        charge(ctx, 1);
        v0 = 8;
    } else {
        // 0x0017bce8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017bcf8
    charge(ctx, 2);
    // 0x0017bde4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0017BE10 sub_17BE10 -- 352 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17BE10(a, b, skill, ...): sub_306BC0(skill, unit(a), unit(b), the remaining four arguments).
void sub_17BE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017be10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a1;
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    s6 = t2;
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = 1;
    if (s0 != v0) {
        // 0x0017be70
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            // 0x0017be7c
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 737;
            jal(ctx, 0x17BE88u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0017be90
        charge(ctx, 10);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v0 = addu(v0, v1);
        s0 = addiu(v0, 4);
    } else {
        // 0x0017be60
        charge(ctx, 4);
        s0 = 0x830000;
        s0 = addiu(s0, 25124);  // &0x836224
    }
    // 0x0017beb8
    charge(ctx, 5);
    s5 = dsll32(s5, 16);
    s5 = dsra32(s5, 16);
    v0 = 1;
    if (s5 != v0) {
        // 0x0017bedc
        charge(ctx, 3);
        v0 = slti(s5, 11);
        if (v0 == 0) {
            // 0x0017bee8
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 737;
            jal(ctx, 0x17BEF4u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0017befc
        charge(ctx, 10);
        v1 = addiu(s5, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &0x834010
        v0 = addu(v0, v1);
        a2 = addiu(v0, 4);
    } else {
        // 0x0017becc
        charge(ctx, 4);
        a2 = 0x830000;
        a2 = addiu(a2, 25124);  // &0x836224
    }
    // 0x0017bf24
    charge(ctx, 19);
    a0 = s4;
    a1 = s0;
    a3 = s3;
    t0 = s2;
    t1 = s1;
    t2 = s6;
    jal(ctx, 0x17BF3Cu, gen::fn_sub_306BC0_00306bc0);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0017BF70 sub_17BF70 -- 40 bytes; leaf frame (no stack)
// sub_17BF70(skill): 0x1BF <= skill < 0x1D0 (the 17 skills of the 5-byte table sub_17BFA0 reads).
void sub_17BF70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x0017bf70
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = a0 & 0xFFFF;
    at = slti(v0, 447);
    if (at == 0) {
        // 0x0017bf8c
        charge(ctx, 1);
        v0 = slti(v0, 464);
    } else {
        // 0x0017bf80
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017bf90 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0017BFA0 sub_17BFA0 -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17BFA0(skill, i): byte i (< 5, K_Assert 5947) of the skill's row in *0x7CE4A0 for skills 0x1BF..0x1CF, else 0.
void sub_17BFA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017bfa0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFF;
    {  // the inlined check: K_Assert unless (i64(v0) >= 0) and not (v0 == 0)
        bool bad = true;
        if (i64(v0) >= 0) {
            // 0x0017bfc4
            charge(ctx, 3);
            v0 = slti(v0, 5);
            bad = v0 == 0;
        }
        if (bad) {  // 0x0017bfd0: K_Assert (returns in retail)
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 5947;
            jal(ctx, 0x17BFDCu, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x0017bfe4
    charge(ctx, 4);
    a0 = s1 & 0xFFFF;
    at = slti(a0, 447);
    if (at == 0) {
        // 0x0017c000
        charge(ctx, 3);
        at = slti(a0, 464);
        if (at != 0) {
            // 0x0017c018
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x0017c00c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0017bff4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017c01c
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0017c030
        charge(ctx, 7);
        lw(v1, gp, -18512);  // 0x7CE4A0
        v0 = sll(a0, 2);
        v0 = addu(v0, a0);
        v1 = addu(v0, v1);
        v0 = s0 & 0xFF;
        v0 = addu(v0, v1);
        lbu(v0, v0, -2235);
    } else {
        // 0x0017c024
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017c04c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017C070 sub_17C070 -- 112 bytes; leaf frame (no stack)
// sub_17C070(skill): skill < 0x1D0 and its gBtlSkillTbl row has byte +17 == 11 and u16 +18 == 100.
void sub_17C070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0017c070
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = slti(v1, 464);
    if (v0 != 0) {
        // 0x0017c08c
        charge(ctx, 11);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, -18680);  // gBtlSkillTbl
        a0 = addu(v1, v0);
        lbu(v1, a0, 17);
        v0 = 11;
        if (v1 == v0) {
            // 0x0017c0b8
            charge(ctx, 4);
            lh(v1, a0, 18);
            v0 = 100;
            if (v1 != v0) {
                goto L_0017c0d4;
            }
            // 0x0017c0c8
            charge(ctx, 3);
            v0 = 1;
            // 0x0017c0d8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_0017c0d4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0017c080
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017c0d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0017C0E0 sub_17C0E0 -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17C0E0(id): the first of bits 2 / 4 / 8 set in the u16 flags of the 88-byte row id of *0x7CE42C (0 when none;
// K_Assert 5973 unless id < 256).
void sub_17C0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017c0e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = sltiu(s0, 256);
    if (v0 == 0) {
        // 0x0017c0fc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5973;
        jal(ctx, 0x17C108u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017c110
    charge(ctx, 11);
    v0 = sll(s0, 2);
    v0 = addu(v0, s0);
    v0 = sll(v0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    lw(v0, gp, -18628);  // 0x7CE42C
    v0 = addu(v0, v1);
    lhu(v1, v0, 0);
    v0 = v1 & 0x2;
    if (v0 == 0) {
        // 0x0017c148
        charge(ctx, 3);
        v0 = v1 & 0x4;
        if (v0 == 0) {
            // 0x0017c160
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x0017c178
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0017c16c
                charge(ctx, 3);
                v0 = 8;
            }
        } else {
            // 0x0017c154
            charge(ctx, 3);
            v0 = 4;
        }
    } else {
        // 0x0017c13c
        charge(ctx, 3);
        v0 = 2;
    }
    // 0x0017c17c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017C190 sub_17C190 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_17C190: clears the 28-byte block at gGlobalWork +0x44FC (0x83A6FC).
void sub_17C190(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017c190
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x840000;
    a0 = addiu(a0, -22788);  // &0x83A6FC
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x17C1A8u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017C1C0 sub_17C1C0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17C1C0(src): memcpy(0x83A6FC, src, 28) (K_Assert 5997 on null).
void sub_17C1C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017c1c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x0017c1d8
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 5997;
        jal(ctx, 0x17C1E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017c1ec
    charge(ctx, 11);
    a0 = 0x840000;
    a0 = addiu(a0, -22788);  // &0x83A6FC
    a1 = s0;
    a2 = 28;
    jal(ctx, 0x17C1FCu, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017C220 sub_17C220 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17C220(dst): memcpy(dst, 0x83A6FC, 28) (K_Assert 6005 on null).
void sub_17C220(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017c220
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x0017c238
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 6005;
        jal(ctx, 0x17C244u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0017c24c
    charge(ctx, 11);
    a0 = s0;
    a1 = 0x840000;
    a1 = addiu(a1, -22788);  // &0x83A6FC
    a2 = 28;
    jal(ctx, 0x17C25Cu, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017C280 sub_17C280 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17C280: the four 4-byte entries at gGlobalWork +0x4518 (0x83A718): each cleared, then its s16 +0 = -1.
void sub_17C280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017c280
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    for (;;) {
        // 0x0017c2cc
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017c29c
        charge(ctx, 12);
        v1 = sll(s1, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &0x836200
        s0 = addu(v0, v1);
        a0 = addiu(s0, 17688);
        a1 = 0;
        a2 = 4;
        jal(ctx, 0x17C2B8u, gen::fn_memset_00521408);
        v1 = si(-1);
        sh(v1, s0, 17688);
        s1 = addiu(s1, 1);
    }
    // 0x0017c2d8
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017D7C0 sub_17D7C0 -- 40 bytes; leaf frame (no stack)
// sub_17D7C0(n): 0x83AA98 = n, capped at 99 (unsigned).
void sub_17D7C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0017d7c0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x840000;
    sw(a0, v1, -21864);  // 0x83AA98
    at = sltiu(a0, 100);
    if (at == 0) {
        // 0x0017d7d4
        charge(ctx, 3);
        a0 = 99;
        v1 = 0x840000;
        sw(a0, v1, -21864);  // 0x83AA98
    }
    // 0x0017d7e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0017D7F0 sub_17D7F0 -- 12 bytes; leaf frame (no stack)
// sub_17D7F0(mode) [datSetScenarioMode]: kScenarioMode (0x7CDFA4) = mode (0 The Journey, 1 The Answer; sub_17D800
// reads it).
void sub_17D7F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x0017d7f0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a0, gp, -19788);  // 0x7CDFA4
}

// 0x0017DDF0 sub_17DDF0 -- 608 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17DDF0(&month, &day) [clndGetNextHoliday]: the first day after today (days since Apr 5 + 1, ...) that is a
// Sunday ((d + 7) % 7 == 0) or in tbl_clndHolidays; writes its s16 month and day of month and returns 1, or 0 when
// none comes before day 351 (March 22).
void sub_17DDF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017ddf0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    jal(ctx, 0x17DE14u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, 1);
    s1 = dsll32(v0, 16);  // s1 = d = today + 1
    s1 = dsra32(s1, 16);
    for (;;) {  // d = today + 1, ... until a Sunday or holiday
        // 0x0017de30
        charge(ctx, 5);
        s0 = dsll32(s1, 16);
        s0 = dsra32(s0, 16);
        v0 = slti(s0, calendar::kNextHolidayLimit);
        if (v0 == 0) {  // none before day 351: return 0
            charge(ctx, 3);
            v0 = 0;
            // 0x0017e02c (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
        // 0x0017de50: the weekday (d + 7) % 7
        charge(ctx, 6);
        v1 = addiu(s0, 7);
        v0 = 7;
        div(v1, v0);
        mfhi(v0);
        if (v0 != 0) {  // not a Sunday: search tbl_clndHolidays for (month, day of month)
            // 0x0017de74
            charge(ctx, 18);
            a0 = s0;
            jal(ctx, 0x17DE78u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
            s4 = dsll32(v0, 16);  // s4 = month
            s4 = dsra32(s4, 16);
            a0 = s0;
            jal(ctx, 0x17DE8Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
            a3 = dsll32(v0, 16);  // a3 = day of month
            a3 = dsra32(a3, 16);
            t0 = 0;               // t0 = i
            a2 = dsll32(s4, 16);  // a2 = month
            a2 = dsra32(a2, 16);
            a1 = 0x5E0000;
            a1 = addiu(a1, 14912);  // &tbl_clndHolidays
            a0 = si(-1);            // the end marker
            bool holiday = false;
            for (;;) {  // i < 356
                // 0x0017defc
                charge(ctx, 5);
                v1 = dsll32(t0, 16);
                v1 = dsra32(v1, 16);
                v0 = slti(v1, calendar::kHolidayScanMax);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0017debc
                charge(ctx, 5);
                v0 = sll(v1, 2);
                v1 = addu(a1, v0);  // &holidays[i]
                lh(v0, v1, 0);      // .month
                if (v0 == a0) {     // -1: the end of the table
                    break;
                }
                // 0x0017ded0
                charge(ctx, 2);
                if (a2 == v0) {
                    // 0x0017ded8
                    charge(ctx, 3);
                    lh(v0, v1, 2);  // .day
                    if (a3 == v0) {
                        holiday = true;
                        break;
                    }
                }
                // 0x0017def0: ++i
                charge(ctx, 3);
                v0 = addiu(t0, 1);
                t0 = dsll32(v0, 16);
                t0 = dsra32(t0, 16);
            }
            if (holiday) {
                // 0x0017dee4
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x0017df10
                charge(ctx, 1);
                v0 = 0;
            }
        } else {
            // 0x0017de68: a Sunday
            charge(ctx, 3);
            v0 = 1;
        }
        // 0x0017df14
        charge(ctx, 2);
        if (v0 != 0) {
            break;
        }
        // 0x0017df1c
        charge(ctx, 5);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 16);
        s1 = dsra32(s1, 16);
        backedge(ctx);
    }
    // 0x0017df30: the month walk, inlined twice (rem = d + 4, month = 4; while (rem >= len[month - 1]) rem -= len,
    // month = month == 12 ? 1 : month + 1): the first loop keeps the month, the second the day of month
    charge(ctx, 7);
    a3 = 4;
    t0 = addiu(s0, 4);
    t1 = dsll32(t0, 16);
    t1 = dsra32(t1, 16);
    v0 = 1;
    a1 = 0x5E0000;
    a1 = addiu(a1, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017df4c
        charge(ctx, 10);
        a2 = dsll32(a3, 16);
        a2 = dsra32(a2, 16);
        v1 = sll(a2, 1);
        v1 = addu(a1, v1);
        lh(a0, v1, -2);
        v1 = dsll32(t1, 16);
        v1 = dsra32(v1, 16);
        v1 = slt(v1, a0);
        if (v1 != 0) {
            break;
        }
        // 0x0017df74
        charge(ctx, 9);
        v1 = subu(t1, a0);
        t1 = dsll32(v1, 16);
        t1 = dsra32(t1, 16);
        v1 = addiu(a3, 1);
        a3 = dsll32(v1, 16);
        a3 = dsra32(a3, 16);
        at = slti(a3, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017df98
            charge(ctx, 3);
            a3 = v0;
            backedge(ctx);
        }
    }
    // 0x0017dfa4
    charge(ctx, 8);
    a3 = dsll32(a2, 16);
    a3 = dsra32(a3, 16);
    t1 = 4;
    t0 = dsll32(t0, 16);
    t0 = dsra32(t0, 16);
    v0 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017dfc4
        charge(ctx, 10);
        v1 = dsll32(t1, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(a2, v1);
        lh(a1, v1, -2);
        a0 = dsll32(t0, 16);
        a0 = dsra32(a0, 16);
        v1 = slt(a0, a1);
        if (v1 != 0) {
            break;
        }
        // 0x0017dfec
        charge(ctx, 9);
        v1 = subu(t0, a1);
        t0 = dsll32(v1, 16);
        t0 = dsra32(t0, 16);
        v1 = addiu(t1, 1);
        t1 = dsll32(v1, 16);
        t1 = dsra32(t1, 16);
        at = slti(t1, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017e010
            charge(ctx, 3);
            t1 = v0;
            backedge(ctx);
        }
    }
    // 0x0017e01c: *month_out = month, *day_out = day of month (the remainder + 1); return 1
    charge(ctx, 4);
    v0 = addiu(a0, 1);
    sh(a3, s3, 0);
    sh(v0, s2, 0);
    v0 = 1;
    // 0x0017e02c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0017E050 sub_17E050 -- 1064 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17E050(code, a, b) [clndMatchDateCode] (the social timers): today against a date code --
//   101: a weekday (not Sunday); 100: a holiday or Sunday (sub_17DB40); 1..7: weekday code - 1 (1 = Sunday ..
//   7 = Saturday); 10 n + m (n >= 1): the n-th week of the month (weeks start on Sunday: week 0 runs to the first
//   Saturday) on weekday m - 1; 0: a == the days from April 1 to the first of this month (the instructions compare the
//   running month-length sum, not the month number) and b == the day of month.
// The weekday of the first of the month is (days before it since April 1 + 3) % 7 (April 1, 2009 was a Wednesday).
void sub_17E050(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017e050
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;  // s3 = the date code
    s2 = a1;  // s2 = a (code 0)
    s1 = a2;  // s1 = b (code 0)
    s0 = 4;   // s0 = month (the walk starts in April)
    jal(ctx, 0x17E078u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, 4);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    a3 = 0;  // a3 = the sum of the month lengths before this month
    v0 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017e0a4
        charge(ctx, 10);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(a2, v1);
        lh(a1, v1, -2);
        v1 = dsll32(t0, 16);
        v1 = dsra32(v1, 16);
        a0 = slt(v1, a1);
        if (a0 != 0) {
            break;
        }
        // 0x0017e0cc
        charge(ctx, 12);
        v1 = subu(t0, a1);
        t0 = dsll32(v1, 16);
        t0 = dsra32(t0, 16);
        v1 = addu(a3, a1);
        a3 = dsll32(v1, 16);
        a3 = dsra32(a3, 16);
        v1 = addiu(s0, 1);
        s0 = dsll32(v1, 16);
        s0 = dsra32(s0, 16);
        at = slti(s0, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017e0fc
            charge(ctx, 3);
            s0 = v0;
            backedge(ctx);
        }
    }
    // 0x0017e108: t0 = the weekday of the first of the month ((days before it since April 1 + 3) % 7); then a2 =
    // the week of the month (one more each time the weekday wraps to Sunday over days 1..today - 1); v1 = day - 1
    charge(ctx, 12);
    a1 = dsll32(a3, 16);
    a1 = dsra32(a1, 16);
    v0 = addiu(a1, 3);
    a0 = 7;
    div(v0, a0);
    mfhi(v0);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    a2 = 0;
    a3 = 0;
    for (;;) {
        // 0x0017e168
        charge(ctx, 5);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017e138
        charge(ctx, 5);
        v0 = addiu(t0, 1);
        t0 = dsll32(v0, 16);
        t0 = dsra32(t0, 16);
        if (t0 == a0) {
            // 0x0017e14c
            charge(ctx, 4);
            v0 = addiu(a2, 1);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            t0 = 0;
        }
        // 0x0017e15c
        charge(ctx, 3);
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
    }
    // 0x0017e17c
    charge(ctx, 3);
    v0 = 101;
    if (s3 == v0) {  // code 101: a weekday (not Sunday)
        // 0x0017e3bc
        charge(ctx, 10);
        jal(ctx, 0x17E3BCu, gen::fn_datGetDaysSinceApr5_0016ef20);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        v1 = addiu(v0, 7);
        v0 = 7;
        div(v1, v0);
        mfhi(v0);
        if (v0 == 0) {
        L_0017e454:  // no match: return 0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0017e3e4
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0017e188
        charge(ctx, 3);
        v0 = 100;
        if (s3 == v0) {  // code 100: a holiday or Sunday (sub_17DB40)
            // 0x0017e394
            charge(ctx, 7);
            jal(ctx, 0x17E394u, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = v0;
            jal(ctx, 0x17E3A0u, gen::fn_sub_17DB40_0017db40);
            if (v0 == 0) {
                goto L_0017e454;
            }
            // 0x0017e3b0
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0017e194
            charge(ctx, 3);
            v0 = 7;
            if (s3 == v0) {  // code 7: Saturday
                // 0x0017e35c
                charge(ctx, 11);
                jal(ctx, 0x17E35Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v1 = addiu(v0, 7);
                v0 = 7;
                div(v1, v0);
                mfhi(v1);
                v0 = 6;
                if (v1 != v0) {
                    goto L_0017e454;
                }
                // 0x0017e388
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x0017e1a0
                charge(ctx, 3);
                v0 = 6;
                if (s3 == v0) {  // code 6: Friday
                    // 0x0017e324
                    charge(ctx, 11);
                    jal(ctx, 0x17E324u, gen::fn_datGetDaysSinceApr5_0016ef20);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    v1 = addiu(v0, 7);
                    v0 = 7;
                    div(v1, v0);
                    mfhi(v1);
                    v0 = 5;
                    if (v1 != v0) {
                        goto L_0017e454;
                    }
                    // 0x0017e350
                    charge(ctx, 3);
                    v0 = 1;
                } else {
                    // 0x0017e1ac
                    charge(ctx, 3);
                    v0 = 5;
                    if (s3 == v0) {  // code 5: Thursday
                        // 0x0017e2ec
                        charge(ctx, 11);
                        jal(ctx, 0x17E2ECu, gen::fn_datGetDaysSinceApr5_0016ef20);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        v1 = addiu(v0, 7);
                        v0 = 7;
                        div(v1, v0);
                        mfhi(v1);
                        v0 = 4;
                        if (v1 != v0) {
                            goto L_0017e454;
                        }
                        // 0x0017e318
                        charge(ctx, 3);
                        v0 = 1;
                    } else {
                        // 0x0017e1b8
                        charge(ctx, 3);
                        v0 = 4;
                        if (s3 == v0) {  // code 4: Wednesday
                            // 0x0017e2b4
                            charge(ctx, 11);
                            jal(ctx, 0x17E2B4u, gen::fn_datGetDaysSinceApr5_0016ef20);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            v1 = addiu(v0, 7);
                            v0 = 7;
                            div(v1, v0);
                            mfhi(v1);
                            v0 = 3;
                            if (v1 != v0) {
                                goto L_0017e454;
                            }
                            // 0x0017e2e0
                            charge(ctx, 3);
                            v0 = 1;
                        } else {
                            // 0x0017e1c4
                            charge(ctx, 3);
                            v0 = 3;
                            if (s3 == v0) {  // code 3: Tuesday
                                // 0x0017e27c
                                charge(ctx, 11);
                                jal(ctx, 0x17E27Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                                v0 = dsll32(v0, 16);
                                v0 = dsra32(v0, 16);
                                v1 = addiu(v0, 7);
                                v0 = 7;
                                div(v1, v0);
                                mfhi(v1);
                                v0 = 2;
                                if (v1 != v0) {
                                    goto L_0017e454;
                                }
                                // 0x0017e2a8
                                charge(ctx, 3);
                                v0 = 1;
                            } else {
                                // 0x0017e1d0
                                charge(ctx, 3);
                                v0 = 2;
                                if (s3 == v0) {  // code 2: Monday
                                    // 0x0017e248
                                    charge(ctx, 11);
                                    jal(ctx, 0x17E248u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                    v0 = dsll32(v0, 16);
                                    v0 = dsra32(v0, 16);
                                    v1 = addiu(v0, 7);
                                    v0 = 7;
                                    div(v1, v0);
                                    mfhi(v1);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_0017e454;
                                    }
                                    // 0x0017e274
                                    charge(ctx, 2);
                                } else {
                                    // 0x0017e1dc
                                    charge(ctx, 3);
                                    v0 = 1;
                                    if (s3 == v0) {  // code 1: Sunday
                                        // 0x0017e214
                                        charge(ctx, 10);
                                        jal(ctx, 0x17E214u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                        v0 = dsll32(v0, 16);
                                        v0 = dsra32(v0, 16);
                                        v1 = addiu(v0, 7);
                                        v0 = 7;
                                        div(v1, v0);
                                        mfhi(v0);
                                        if (v0 != 0) {
                                            goto L_0017e454;
                                        }
                                        // 0x0017e23c
                                        charge(ctx, 3);
                                        v0 = 1;
                                    } else {
                                        // 0x0017e1e8
                                        charge(ctx, 2);
                                        if (s3 == 0) {  // code 0: a == days before this month, b == day
                                            // 0x0017e1f8
                                            charge(ctx, 2);
                                            if (s2 != a1) {
                                                goto L_0017e454;
                                            }
                                            // 0x0017e200
                                            charge(ctx, 3);
                                            v1 = addiu(v1, 1);
                                            if (s1 != v1) {
                                                goto L_0017e454;
                                            }
                                            // 0x0017e20c
                                            charge(ctx, 2);
                                        } else {
                                            // 0x0017e1f0: code 10 n + m: week n - 1 of the month on weekday m - 1
                                            charge(ctx, 2);
                                            // 0x0017e3f0
                                            charge(ctx, 8);
                                            v1 = dsll32(a2, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = 10;
                                            div(s3, v0);
                                            mflo(v0);
                                            v0 = addiu(v0, -1);
                                            if (v1 != v0) {
                                                goto L_0017e454;
                                            }
                                            // 0x0017e410
                                            charge(ctx, 14);
                                            jal(ctx, 0x17E410u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            v0 = dsll32(v0, 16);
                                            v0 = dsra32(v0, 16);
                                            v1 = addiu(v0, 7);
                                            v0 = 7;
                                            div(v1, v0);
                                            mfhi(v1);
                                            v0 = 10;
                                            div(s3, v0);
                                            mfhi(v0);
                                            v0 = addiu(v0, -1);
                                            if (v0 != v1) {
                                                goto L_0017e454;
                                            }
                                            // 0x0017e448
                                            charge(ctx, 3);
                                            v0 = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x0017e458 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0017E680 sub_17E680 -- 4684 bytes; frame 0xB0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17E680 [clndCalendarTask_Update]: the update function of the "CalenderDraw" task (sub_17FAD0 / sub_17FB90; its
// work, 44 bytes: +0 state, +4 / +8 the debug cursors, +0xC the sequence task, +0x10 the day-parts HUD task, +0x20 a
// countdown, +0x24 'advance'). It runs the day's time slots:
//   0, 1: the debug date picker (pad word 0x7E0952: left / right = -1 / +1 day, wrapping in 0..364; up / down = -7 / +7
//         and L2 / R2 = a month back / forward, clamped to 0..364; L1 / R1 = previous / next time slot, across the
//         day boundary; the month grid and "%2d/%3d" with the slot name are printed through sub_104D10); bit 0x40 of
//         gPadFlags sets flag 0x141D and goes to 2;
//   2, 3: create the H_DayParts HUD, wait for it to be idle, show the date (H_DayPartsDraw_SetDate) unless a time skip
//         is pending ("####  next time skip"), then 5 -> 6 -> ... -> 13 (one frame each);
//   13:   flag 0x1410, then the sequence of the current time slot (the 9-case table: SOUCHOU sub_180A20, ASA sub_180C40,
//         GOZEN sub_180EE0, HIRUYASUMI sub_181010, GOGO sub_181170, HOUKAGO sub_181310, YORU sub_181430, SINYA
//         sub_17FC70, Dark Hour sub_181580): its task -> 14, the Dark Hour's return to the dungeon -> 16, none -> 22;
//   14, 15: wait for the event (adminiChangeSeq state 2 / 3 shows the next date), then 22; 16 shows the date -> 17;
//   18: wait for the sequence change; 19 / 20: the memory-card task (sub_188640); 21: a pending return to the field;
//   22: ADVANCE TIME: if a time skip is active (sub_16EF60) and the target (sub_16EF40 day / sub_16EF50 slot) is six
//       days away or reached, jump to it and end the skip; else the next slot: Dark Hour (8) -> slot 0 of the next day;
//       a school Saturday's GOZEN (2) -> HOUKAGO (5); a holiday's ASA (1) -> GOGO (4) and GOGO -> YORU (6); otherwise
//       slot + 1 (ASA also clears the morning flags, sub_180E60); then 4;
//   23: as 21 for a fresh game; 24: count down +0x20, -1 (task ends) at 0.
void sub_17E680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x0017e680
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 25);
    if (at != 0) {
        // 0x0017e6bc
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25952);  // &0x7B6560
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x17E6D8u:  // table[0] -- state 0: create the two debug cursors (H_Cursor_CreateTask) -> 1
            // 0x0017e6d8
            charge(ctx, 53);
            sw(zero, sp, 0x80);
            sw(zero, sp, 0x84);
            v0 = 252;
            sw(v0, sp, 0x88);
            v0 = 168;
            sw(v0, sp, 0x8C);
            v0 = 0x41C00000;
            sw(v0, sp, 0xA0);
            v0 = 0x42A80000;
            sw(v0, sp, 0xA4);
            v0 = 255;
            sb(v0, sp, 0xAF);
            sb(zero, sp, 0xAC);
            v0 = 100;
            sb(v0, sp, 0xAE);
            sb(zero, sp, 0xAD);
            v0 = 0x40000000;
            mtc1(v0, f12);
            ld(a1, sp, 0xA0);
            a2 = addiu(sp, 0x80);
            lw(a3, sp, 0xAC);
            jal(ctx, 0x17E72Cu, gen::fn_H_Cursor_CreateTask_001005b0);
            sw(v0, s0, 8);
            sw(zero, sp, 0x80);
            sw(zero, sp, 0x84);
            v0 = 36;
            sw(v0, sp, 0x88);
            v0 = 12;
            sw(v0, sp, 0x8C);
            v0 = 0x41C00000;
            sw(v0, sp, 0xA0);
            v0 = 0x42A80000;
            sw(v0, sp, 0xA4);
            v0 = 255;
            sb(v0, sp, 0xAF);
            v0 = 120;
            sb(v0, sp, 0xAC);
            sb(zero, sp, 0xAE);
            sb(zero, sp, 0xAD);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a0 = s2;
            ld(a1, sp, 0xA0);
            a2 = addiu(sp, 0x80);
            lw(a3, sp, 0xAC);
            jal(ctx, 0x17E790u, gen::fn_H_Cursor_CreateTask_001005b0);
            sw(v0, s0, 4);
            v0 = 1;
            sw(v0, s0, 0);
        L_0017f89c:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x17E7ACu:  // table[1] -- state 1: the debug date picker, the month grid, the date print
            // 0x0017e7ac
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2386);  // 0x7E0952
            v0 = v1 & 0x8000;
            if (v0 == 0) {
                // 0x0017e810
                charge(ctx, 3);
                v0 = v1 & 0x2000;
                if (v0 == 0) {
                    // 0x0017e870
                    charge(ctx, 3);
                    v0 = v1 & 0x1000;
                    if (v0 == 0) {
                        // 0x0017e8cc
                        charge(ctx, 3);
                        v0 = v1 & 0x4000;
                        if (v0 == 0) {
                            // 0x0017e92c
                            charge(ctx, 3);
                            v0 = v1 & 0x4;
                            if (v0 == 0) {
                                // 0x0017e9c0
                                charge(ctx, 3);
                                v0 = v1 & 0x8;
                                if (v0 == 0) {
                                    // 0x0017ea58
                                    charge(ctx, 3);
                                    v0 = v1 & 0x1;
                                    if (v0 == 0) {
                                        // 0x0017eb08
                                        charge(ctx, 3);
                                        v0 = v1 & 0x2;
                                        if (v0 == 0) {
                                            // 0x0017ebbc
                                            charge(ctx, 5);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, 2382);  // gPadFlags
                                            v0 = v0 & 0x40;
                                            if (v0 != 0) {
                                                // 0x0017ebd0
                                                charge(ctx, 6);
                                                a0 = 0x141D;  // the calendar started
                                                a1 = 0;
                                                jal(ctx, 0x17EBD8u, gen::fn_datSetFlag_0016f1f0);
                                                v0 = 2;
                                                sw(v0, s0, 0);
                                            }
                                        } else {
                                            // 0x0017eb14
                                            charge(ctx, 9);
                                            jal(ctx, 0x17EB14u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            jal(ctx, 0x17EB24u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                            v1 = 3;
                                            if (v0 != v1) {
                                                // 0x0017eb38
                                                charge(ctx, 28);
                                                jal(ctx, 0x17EB38u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                                a0 = dsll32(v0, 16);
                                                a0 = dsra32(a0, 16);
                                                jal(ctx, 0x17EB48u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                                s1 = v0;
                                                jal(ctx, 0x17EB54u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                                a0 = dsll32(v0, 16);
                                                a0 = dsra32(a0, 16);
                                                v1 = sll(s1, 1);
                                                v0 = 0x5E0000;
                                                v0 = addiu(v0, 15198);  // &0x5E3B5E
                                                v0 = addu(v0, v1);
                                                lh(v0, v0, 0);
                                                v0 = addu(a0, v0);
                                                a0 = dsll32(v0, 16);
                                                a0 = dsra32(a0, 16);
                                                jal(ctx, 0x17EB84u, gen::fn_datSetDaysSinceApr5_0016ef70);
                                                jal(ctx, 0x17EB8Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                at = slti(v0, 365);
                                                if (at == 0) {
                                                    // 0x0017eba8
                                                    charge(ctx, 5);
                                                    a0 = 364;
                                                    jal(ctx, 0x17EBACu, gen::fn_datSetDaysSinceApr5_0016ef70);
                                                }
                                            }
                                        }
                                    } else {
                                        // 0x0017ea64
                                        charge(ctx, 9);
                                        jal(ctx, 0x17EA64u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                        a0 = dsll32(v0, 16);
                                        a0 = dsra32(a0, 16);
                                        jal(ctx, 0x17EA74u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                        v1 = 4;
                                        if (v0 != v1) {
                                            // 0x0017ea88
                                            charge(ctx, 27);
                                            jal(ctx, 0x17EA88u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            jal(ctx, 0x17EA98u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                            s1 = v0;
                                            jal(ctx, 0x17EAA4u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            v1 = sll(s1, 1);
                                            v0 = 0x5E0000;
                                            v0 = addiu(v0, 15198);  // &0x5E3B5E
                                            v0 = addu(v0, v1);
                                            lh(v0, v0, 0);
                                            v0 = subu(a0, v0);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            jal(ctx, 0x17EAD4u, gen::fn_datSetDaysSinceApr5_0016ef70);
                                            jal(ctx, 0x17EADCu, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            v0 = dsll32(v0, 16);
                                            v0 = dsra32(v0, 16);
                                            if (i64(v0) < 0) {
                                                // 0x0017eaf4
                                                charge(ctx, 5);
                                                a0 = 0;
                                                jal(ctx, 0x17EAF8u, gen::fn_datSetDaysSinceApr5_0016ef70);
                                            }
                                        }
                                    }
                                } else {
                                    // 0x0017e9cc
                                    charge(ctx, 6);
                                    jal(ctx, 0x17E9CCu, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 != v0) {
                                        // 0x0017ea34
                                        charge(ctx, 9);
                                        jal(ctx, 0x17EA34u, gen::fn_datGetTime_0016ef30);
                                        v0 = v0 & 0xFF;
                                        v0 = addiu(v0, 1);
                                        a0 = v0 & 0xFF;
                                        jal(ctx, 0x17EA48u, gen::fn_sub_16F150_0016f150);
                                    } else {
                                        // 0x0017e9e4
                                        charge(ctx, 9);
                                        a0 = 0;
                                        jal(ctx, 0x17E9E8u, gen::fn_sub_16F150_0016f150);
                                        jal(ctx, 0x17E9F0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                        v0 = dsll32(v0, 16);
                                        v0 = dsra32(v0, 16);
                                        if (v0 != 0) {
                                            // 0x0017ea08
                                            charge(ctx, 11);
                                            jal(ctx, 0x17EA08u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                            v0 = dsll32(v0, 16);
                                            v0 = dsra32(v0, 16);
                                            v0 = addiu(v0, 1);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            jal(ctx, 0x17EA24u, gen::fn_datSetDaysSinceApr5_0016ef70);
                                        }
                                    }
                                }
                            } else {
                                // 0x0017e938
                                charge(ctx, 5);
                                jal(ctx, 0x17E938u, gen::fn_datGetTime_0016ef30);
                                v0 = v0 & 0xFF;
                                if (v0 != 0) {
                                    // 0x0017e99c
                                    charge(ctx, 9);
                                    jal(ctx, 0x17E99Cu, gen::fn_datGetTime_0016ef30);
                                    v0 = v0 & 0xFF;
                                    v0 = addiu(v0, -1);
                                    a0 = v0 & 0xFF;
                                    jal(ctx, 0x17E9B0u, gen::fn_sub_16F150_0016f150);
                                } else {
                                    // 0x0017e94c
                                    charge(ctx, 9);
                                    a0 = 8;
                                    jal(ctx, 0x17E950u, gen::fn_sub_16F150_0016f150);
                                    jal(ctx, 0x17E958u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                    v0 = dsll32(v0, 16);
                                    v0 = dsra32(v0, 16);
                                    if (v0 != 0) {
                                        // 0x0017e970
                                        charge(ctx, 11);
                                        jal(ctx, 0x17E970u, gen::fn_datGetDaysSinceApr5_0016ef20);
                                        v0 = dsll32(v0, 16);
                                        v0 = dsra32(v0, 16);
                                        v0 = addiu(v0, -1);
                                        a0 = dsll32(v0, 16);
                                        a0 = dsra32(a0, 16);
                                        jal(ctx, 0x17E98Cu, gen::fn_datSetDaysSinceApr5_0016ef70);
                                    }
                                }
                            }
                        } else {
                            // 0x0017e8d8
                            charge(ctx, 16);
                            jal(ctx, 0x17E8D8u, gen::fn_datGetDaysSinceApr5_0016ef20);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            v0 = addiu(v0, 7);
                            a0 = dsll32(v0, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x17E8F4u, gen::fn_datSetDaysSinceApr5_0016ef70);
                            jal(ctx, 0x17E8FCu, gen::fn_datGetDaysSinceApr5_0016ef20);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            at = slti(v0, 365);
                            if (at == 0) {
                                // 0x0017e918
                                charge(ctx, 5);
                                a0 = 364;
                                jal(ctx, 0x17E91Cu, gen::fn_datSetDaysSinceApr5_0016ef70);
                            }
                        }
                    } else {
                        // 0x0017e87c
                        charge(ctx, 15);
                        jal(ctx, 0x17E87Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        v0 = addiu(v0, -7);
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x17E898u, gen::fn_datSetDaysSinceApr5_0016ef70);
                        jal(ctx, 0x17E8A0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        if (i64(v0) < 0) {
                            // 0x0017e8b8
                            charge(ctx, 5);
                            a0 = 0;
                            jal(ctx, 0x17E8BCu, gen::fn_datSetDaysSinceApr5_0016ef70);
                        }
                    }
                } else {
                    // 0x0017e81c
                    charge(ctx, 16);
                    jal(ctx, 0x17E81Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 1);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x17E838u, gen::fn_datSetDaysSinceApr5_0016ef70);
                    jal(ctx, 0x17E840u, gen::fn_datGetDaysSinceApr5_0016ef20);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    at = slti(v0, 365);
                    if (at == 0) {
                        // 0x0017e85c
                        charge(ctx, 5);
                        a0 = 0;
                        jal(ctx, 0x17E860u, gen::fn_datSetDaysSinceApr5_0016ef70);
                    }
                }
            } else {
                // 0x0017e7c0
                charge(ctx, 15);
                jal(ctx, 0x17E7C0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, -1);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x17E7DCu, gen::fn_datSetDaysSinceApr5_0016ef70);
                jal(ctx, 0x17E7E4u, gen::fn_datGetDaysSinceApr5_0016ef20);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (i64(v0) < 0) {
                    // 0x0017e7fc
                    charge(ctx, 5);
                    a0 = 364;
                    jal(ctx, 0x17E800u, gen::fn_datSetDaysSinceApr5_0016ef70);
                }
            }
            // 0x0017ebe8
            charge(ctx, 12);
            s3 = 4;
            jal(ctx, 0x17EBECu, gen::fn_datGetDaysSinceApr5_0016ef20);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v0 = addiu(v0, 4);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
            a2 = 0;
            v0 = 1;
            a1 = 0x5E0000;
            a1 = addiu(a1, 15200);  // &tbl_clndMonthLengths
            for (;;) {
                // 0x0017ec18
                charge(ctx, 10);
                s2 = dsll32(s3, 16);
                s2 = dsra32(s2, 16);
                v1 = sll(s2, 1);
                s5 = addu(a1, v1);
                lh(a0, s5, -2);
                s1 = dsll32(a3, 16);
                s1 = dsra32(s1, 16);
                v1 = slt(s1, a0);
                if (v1 != 0) {
                    break;
                }
                // 0x0017ec40
                charge(ctx, 12);
                v1 = subu(a3, a0);
                a3 = dsll32(v1, 16);
                a3 = dsra32(a3, 16);
                v1 = addu(a2, a0);
                a2 = dsll32(v1, 16);
                a2 = dsra32(a2, 16);
                v1 = addiu(s3, 1);
                s3 = dsll32(v1, 16);
                s3 = dsra32(s3, 16);
                at = slti(s3, 13);
                if (at != 0) {
                    backedge(ctx);
                } else {
                    // 0x0017ec70
                    charge(ctx, 3);
                    s3 = v0;
                    backedge(ctx);
                }
            }
            // 0x0017ec7c
            charge(ctx, 26);
            v0 = dsll32(a2, 16);
            v0 = dsra32(v0, 16);
            v1 = addiu(v0, 3);
            v0 = 7;
            div(v1, v0);
            mfhi(s6);
            s4 = dsll32(s6, 16);
            s4 = dsra32(s4, 16);
            v0 = 0x40000000;
            mtc1(v0, f3);
            sw(v0, sp, 0x98);
            v0 = 0x41100000;
            sw(v0, sp, 0x9C);
            v0 = 0x40400000;
            mtc1(v0, f2);
            mtc1(s4, f0);
            cvt_s_w(f1, f0);
            mtc1(zero, f0);
            adda_s(f0, f3);
            madd_s(f0, f2, f1);
            swc1(f0, sp, 0x98);
            s3 = 0;
            for (;;) {
                // 0x0017ed6c
                charge(ctx, 6);
                v1 = dsll32(s3, 16);
                v1 = dsra32(v1, 16);
                lh(v0, s5, -2);
                v0 = slt(v1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0017ece4
                charge(ctx, 17);
                a2 = addiu(v1, 1);
                ld(a0, sp, 0x98);
                a1 = addiu(gp, -27760);  // "%3d"
                jal(ctx, 0x17ECF0u, gen::fn_sub_104D10_00104d10);
                lwc1(f1, sp, 0x98);
                v0 = 0x40400000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                swc1(f1, sp, 0x98);
                v0 = addiu(s4, 1);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                at = slti(s4, 7);
                if (at == 0) {
                    // 0x0017ed28
                    charge(ctx, 14);
                    v0 = addiu(s4, -7);
                    s4 = dsll32(v0, 16);
                    s4 = dsra32(s4, 16);
                    v0 = 0x41A80000;
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x98);
                    lwc1(f1, sp, 0x9C);
                    v0 = 0x40000000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x9C);
                }
                // 0x0017ed60
                charge(ctx, 3);
                v0 = addiu(s3, 1);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
            }
            // 0x0017ed84
            charge(ctx, 23);
            v0 = 0x40000000;
            sw(v0, sp, 0x98);
            v0 = 0x40E00000;
            sw(v0, sp, 0x9C);
            jal(ctx, 0x17ED94u, gen::fn_datGetTime_0016ef30);
            t0 = v0 & 0xFF;
            a3 = addiu(s1, 1);
            ld(a0, sp, 0x98);
            a1 = addiu(gp, -27752);  // "%2d/%3d"
            a2 = s2;
            jal(ctx, 0x17EDB0u, gen::fn_sub_104D10_00104d10);
            v0 = 0x41200000;
            sw(v0, sp, 0x98);
            v0 = 0x40E00000;
            sw(v0, sp, 0x9C);
            jal(ctx, 0x17EDC8u, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            at = sltiu(v0, 9);
            if (at != 0) {
                // 0x0017ede0
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 25904);  // &0x7B6530
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x17EDFCu:  // table[0] -- print slot 0 SOUCHOU (early morning)
                    // 0x0017edfc
                    charge(ctx, 7);
                    ld(a0, sp, 0x98);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 15264);  // "(SOUCHOU)"
                    jal(ctx, 0x17EE08u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE18u:  // table[1] -- print slot 1 ASA (morning)
                    // 0x0017ee18
                    charge(ctx, 6);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27744);  // "(ASA)"
                    jal(ctx, 0x17EE20u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE30u:  // table[2] -- print slot 2 GOZEN (forenoon)
                    // 0x0017ee30
                    charge(ctx, 6);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27736);  // "(GOZEN)"
                    jal(ctx, 0x17EE38u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE48u:  // table[3] -- print slot 3 HIRUYASUMI (lunch break)
                    // 0x0017ee48
                    charge(ctx, 7);
                    ld(a0, sp, 0x98);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 15280);  // "(HIRUYASUMI)"
                    jal(ctx, 0x17EE54u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE64u:  // table[4] -- print slot 4 GOGO (afternoon)
                    // 0x0017ee64
                    charge(ctx, 6);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27728);  // "(GOGO)"
                    jal(ctx, 0x17EE6Cu, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE7Cu:  // table[5] -- print slot 5 HOUKAGO (after school)
                    // 0x0017ee7c
                    charge(ctx, 7);
                    ld(a0, sp, 0x98);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 15296);  // "(HOUKAGO)"
                    jal(ctx, 0x17EE88u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EE98u:  // table[6] -- print slot 6 YORU (evening)
                    // 0x0017ee98
                    charge(ctx, 6);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27720);  // "(YORU)"
                    jal(ctx, 0x17EEA0u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EEB0u:  // table[7] -- print slot 7 SINYA (late night)
                    // 0x0017eeb0
                    charge(ctx, 6);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27712);  // "(SINYA)"
                    jal(ctx, 0x17EEB8u, gen::fn_sub_104D10_00104d10);
                    break;
                case 0x17EEC8u:  // table[8] -- print slot 8 the Dark Hour ("25")
                    // 0x0017eec8
                    charge(ctx, 4);
                    ld(a0, sp, 0x98);
                    a1 = addiu(gp, -27704);  // "(25)"
                    jal(ctx, 0x17EED0u, gen::fn_sub_104D10_00104d10);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x0017eed8
            charge(ctx, 28);
            v0 = 0x41C00000;
            mtc1(v0, f4);
            sw(v0, sp, 0x98);
            v0 = 0x42D80000;
            sw(v0, sp, 0x9C);
            a1 = dsll32(s6, 16);
            a1 = dsra32(a1, 16);
            v0 = 0x40400000;
            mtc1(v0, f1);
            mtc1(a1, f0);
            cvt_s_w(f0, f0);
            mul_s(f2, f1, f0);
            v0 = 0x41400000;
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f4);
            madd_s(f0, f1, f2);
            swc1(f0, sp, 0x98);
            a0 = 0;
            v0 = 0x437C0000;
            mtc1(v0, f1);
            v0 = 0x42100000;
            mtc1(v0, f3);
            v1 = 7;
            for (;;) {
                // 0x0017ef8c
                charge(ctx, 5);
                v0 = dsll32(a0, 16);
                v0 = dsra32(v0, 16);
                v0 = slt(v0, s1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0017ef48
                charge(ctx, 8);
                lwc1(f0, sp, 0x98);
                add_s(f2, f0, f3);
                swc1(f2, sp, 0x98);
                v0 = addiu(a1, 1);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                if (a1 == v1) {
                    // 0x0017ef68
                    charge(ctx, 6);
                    a1 = 0;
                    lwc1(f0, sp, 0x9C);
                    add_s(f0, f0, f4);
                    swc1(f0, sp, 0x9C);
                    sub_s(f0, f2, f1);
                    swc1(f0, sp, 0x98);
                }
                // 0x0017ef80
                charge(ctx, 3);
                v0 = addiu(a0, 1);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
            }
            // 0x0017efa0
            charge(ctx, 6);
            lw(a0, s0, 4);
            ld(a1, sp, 0x98);
            jal(ctx, 0x17EFA8u, gen::fn_H_Cursor_SetPos_00100710);
            goto L_0017f89c;
        case 0x17EFB8u:  // table[2] -- state 2: create the day-parts HUD, wait until idle -> 3
            // 0x0017efb8
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x0017efc4
                charge(ctx, 3);
                jal(ctx, 0x17EFC4u, gen::fn_H_DayParts_CreateTask_00184db0);
                sw(v0, s0, 16);
            }
            // 0x0017efd0
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x17EFD4u, gen::fn_H_DayPartsDraw_IsIdle_00184d90);
            if (v0 != 0) {
                // 0x0017eff0
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, 0);
                goto L_0017f89c;
            }
            // 0x0017efe4
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x17F000u:  // table[3] -- state 3: show the date (unless a time skip is pending), destroy the cursors -> 5
            // 0x0017f000
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x0017f00c
                charge(ctx, 3);
                jal(ctx, 0x17F00Cu, gen::fn_H_DayParts_CreateTask_00184db0);
                sw(v0, s0, 16);
            }
            // 0x0017f018
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x17F01Cu, gen::fn_H_DayPartsDraw_IsIdle_00184d90);
            if (v0 != 0) {
                // 0x0017f038
                charge(ctx, 4);
                jal(ctx, 0x17F038u, gen::fn_sub_16EF60_0016ef60);
                if (v0 != 0) {
                    // 0x0017f060
                    charge(ctx, 4);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 15312);  // "####  next time skip\n"
                    jal(ctx, 0x17F068u, gen::fn_printf_005225a8);
                } else {
                    // 0x0017f048
                    charge(ctx, 6);
                    lw(a0, s0, 16);
                    a1 = 1;
                    jal(ctx, 0x17F050u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
                }
                // 0x0017f070
                charge(ctx, 3);
                lw(a0, s0, 8);
                if (a0 != 0) {
                    // 0x0017f07c
                    charge(ctx, 2);
                    jal(ctx, 0x17F07Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                }
                // 0x0017f084
                charge(ctx, 3);
                lw(a0, s0, 4);
                if (a0 != 0) {
                    // 0x0017f090
                    charge(ctx, 2);
                    jal(ctx, 0x17F090u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                }
                // 0x0017f098
                charge(ctx, 6);
                sw(zero, s0, 8);
                sw(zero, s0, 4);
                v0 = 5;
                sw(v0, s0, 0);
                goto L_0017f89c;
            }
            // 0x0017f02c
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x17F0B0u:  // table[4] -- state 4 -> 5
            // 0x0017f0b0
            charge(ctx, 4);
            v0 = 5;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F0C0u:  // table[5] -- state 5 -> 6
            // 0x0017f0c0
            charge(ctx, 4);
            v0 = 6;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F0D0u:  // table[6] -- state 6 -> 7
            // 0x0017f0d0
            charge(ctx, 4);
            v0 = 7;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F0E0u:  // table[7] -- state 7 -> 8
            // 0x0017f0e0
            charge(ctx, 4);
            v0 = 8;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F0F0u:  // table[8] -- state 8 -> 9
            // 0x0017f0f0
            charge(ctx, 4);
            v0 = 9;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F100u:  // table[9] -- state 9 -> 10
            // 0x0017f100
            charge(ctx, 4);
            v0 = 10;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F110u:  // table[10] -- state 10 -> 11
            // 0x0017f110
            charge(ctx, 4);
            v0 = 11;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F120u:  // table[11] -- state 11 -> 12
            // 0x0017f120
            charge(ctx, 4);
            v0 = 12;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F130u:  // table[12] -- state 12 -> 13
            // 0x0017f130
            charge(ctx, 4);
            v0 = 13;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F140u:  // table[13] -- state 13: run the current slot's sequence (flag 0x1410)
            // 0x0017f140
            charge(ctx, 13);
            s1 = 0;
            a1 = 1;
            sw(a1, s0, 36);
            sw(zero, sp, 0xA8);
            a0 = 0x1410;  // a slot sequence ran
            jal(ctx, 0x17F154u, gen::fn_datSetFlag_0016f1f0);
            jal(ctx, 0x17F15Cu, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            at = sltiu(v0, 9);
            if (at != 0) {
                // 0x0017f174
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 25856);  // &0x7B6500
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x17F190u:  // table[0] -- slot 0 SOUCHOU (early morning): sub_180A20
                    // 0x0017f190
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F194u, gen::fn_sub_180A20_00180a20);
                    s1 = v0;
                    break;
                case 0x17F1A8u:  // table[1] -- slot 1 ASA (morning): sub_180C40
                    // 0x0017f1a8
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F1ACu, gen::fn_sub_180C40_00180c40);
                    s1 = v0;
                    break;
                case 0x17F1C0u:  // table[2] -- slot 2 GOZEN (forenoon): sub_180EE0
                    // 0x0017f1c0
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F1C4u, gen::fn_sub_180EE0_00180ee0);
                    s1 = v0;
                    break;
                case 0x17F1D8u:  // table[3] -- slot 3 HIRUYASUMI (lunch break): sub_181010
                    // 0x0017f1d8
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F1DCu, gen::fn_sub_181010_00181010);
                    s1 = v0;
                    break;
                case 0x17F1F0u:  // table[4] -- slot 4 GOGO (afternoon): sub_181170
                    // 0x0017f1f0
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F1F4u, gen::fn_sub_181170_00181170);
                    s1 = v0;
                    break;
                case 0x17F208u:  // table[5] -- slot 5 HOUKAGO (after school): sub_181310
                    // 0x0017f208
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F20Cu, gen::fn_sub_181310_00181310);
                    s1 = v0;
                    break;
                case 0x17F220u:  // table[6] -- slot 6 YORU (evening): sub_181430
                    // 0x0017f220
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F224u, gen::fn_sub_181430_00181430);
                    s1 = v0;
                    break;
                case 0x17F238u:  // table[7] -- slot 7 SINYA (late night): sub_17FC70
                    // 0x0017f238
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x17F23Cu, gen::fn_sub_17FC70_0017fc70);
                    s1 = v0;
                    break;
                case 0x17F250u:  // table[8] -- slot 8 the Dark Hour ("25"): sub_181580
                    // 0x0017f250
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = addiu(sp, 0xA8);
                    jal(ctx, 0x17F258u, gen::fn_sub_181580_00181580);
                    s1 = v0;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x0017f264
            charge(ctx, 3);
            lw(v0, sp, 0xA8);
            if (v0 == 0) {
                // 0x0017f280
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x0017f29c
                    charge(ctx, 4);
                    v0 = 22;
                    sw(v0, s0, 0);
                } else {
                    // 0x0017f288
                    charge(ctx, 5);
                    sw(s1, s0, 12);
                    v0 = 14;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x0017f270
                charge(ctx, 4);
                v0 = 16;
                sw(v0, s0, 0);
            }
            goto L_0017f89c;
        case 0x17F2ACu:  // table[14] -- state 14: wait for the event (-> 15 / -> 22)
            // 0x0017f2ac
            charge(ctx, 5);
            jal(ctx, 0x17F2ACu, gen::fn_sub_27C2B0_0027c2b0);
            v1 = 3;
            if (v0 != v1) {
                // 0x0017f2c0
                charge(ctx, 5);
                jal(ctx, 0x17F2C0u, gen::fn_sub_27C2B0_0027c2b0);
                v1 = 2;
                if (v0 == v1) {
                    goto L_0017f2d4;
                }
                goto L_0017f318;
            }
        L_0017f2d4:
            charge(ctx, 5);
            jal(ctx, 0x17F2D4u, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            if (v0 != 0) {
                // 0x0017f300
                charge(ctx, 4);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F308u, gen::fn_sub_1848F0_001848f0);
            } else {
                // 0x0017f2e8
                charge(ctx, 6);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F2F0u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
            }
            // 0x0017f310
            charge(ctx, 2);
            v0 = 15;
            sw(v0, s0, 0);
        L_0017f318:
            charge(ctx, 6);
            lw(a0, s0, 12);
            jal(ctx, 0x17F31Cu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0017f330
                charge(ctx, 5);
                sw(zero, s0, 12);
                v0 = 22;
                sw(v0, s0, 0);
            }
            goto L_0017f89c;
        case 0x17F344u:  // table[15] -- state 15: wait for the event task -> 22
            // 0x0017f344
            charge(ctx, 6);
            lw(a0, s0, 12);
            jal(ctx, 0x17F348u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0017f35c
                charge(ctx, 5);
                sw(zero, s0, 12);
                v0 = 22;
                sw(v0, s0, 0);
            }
            goto L_0017f89c;
        case 0x17F370u:  // table[16] -- state 16: show the date -> 17
            // 0x0017f370
            charge(ctx, 5);
            jal(ctx, 0x17F370u, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            if (v0 != 0) {
                // 0x0017f39c
                charge(ctx, 4);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F3A4u, gen::fn_sub_1848F0_001848f0);
            } else {
                // 0x0017f384
                charge(ctx, 6);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F38Cu, gen::fn_H_DayPartsDraw_SetDate_00184c80);
            }
            // 0x0017f3ac
            charge(ctx, 4);
            v0 = 17;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F3BCu:  // table[18] -- state 18: wait for the sequence change to finish -> 22
            // 0x0017f3bc
            charge(ctx, 4);
            jal(ctx, 0x17F3BCu, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x0017f3cc
                charge(ctx, 5);
                sw(zero, s0, 12);
                v0 = 22;
                sw(v0, s0, 0);
            }
            goto L_0017f89c;
        case 0x17F3E0u:  // table[22] -- state 22: ADVANCE THE TIME SLOT (calendar.h, 2.)
            // 0x0017f3e0
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x17F3E4u, gen::fn_H_DayPartsDraw_IsIdle_00184d90);  // the HUD is idle
            if (v0 != 0) {
                // 0x0017f400
                charge(ctx, 4);
                lw(v1, s0, calendar::task::kAdvance);  // 1: advance
                v0 = 1;
                if (v1 == v0) {
                    // 0x0017f410
                    charge(ctx, 5);
                    jal(ctx, 0x17F410u, gen::fn_sub_16EF60_0016ef60);  // a time skip active?
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x0017f424
                        charge(ctx, 12);
                        jal(ctx, 0x17F424u, gen::fn_datGetDaysSinceApr5_0016ef20);
                        s1 = dsll32(v0, 16);
                        s1 = dsra32(s1, 16);
                        jal(ctx, 0x17F434u, gen::fn_sub_16EF40_0016ef40);  // target day - today >= 6: jump
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        v0 = subu(v0, s1);
                        v0 = slti(v0, 6);
                        if (v0 != 0) {
                            // 0x0017f49c
                            charge(ctx, 10);
                            jal(ctx, 0x17F49Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                            s1 = dsll32(v0, 16);
                            s1 = dsra32(s1, 16);
                            jal(ctx, 0x17F4ACu, gen::fn_sub_16EF40_0016ef40);  // today == target day
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            if (s1 != v0) {
                                goto L_0017f52c;
                            }
                            // 0x0017f4c4
                            charge(ctx, 8);
                            jal(ctx, 0x17F4C4u, gen::fn_datGetTime_0016ef30);
                            s1 = v0 & 0xFF;
                            jal(ctx, 0x17F4D0u, gen::fn_sub_16EF50_0016ef50);  // and slot == target slot: jump
                            v0 = v0 & 0xFF;
                            if (s1 != v0) {
                                goto L_0017f52c;
                            }
                            // 0x0017f4e4
                            charge(ctx, 18);
                            jal(ctx, 0x17F4E4u, gen::fn_sub_16EF40_0016ef40);
                            a0 = v0;
                            jal(ctx, 0x17F4F0u, gen::fn_datSetDaysSinceApr5_0016ef70);  // JUMP: the date = the target day
                            jal(ctx, 0x17F4F8u, gen::fn_sub_16EF50_0016ef50);
                            a0 = v0;
                            jal(ctx, 0x17F504u, gen::fn_sub_16F150_0016f150);  //       the slot = the target slot
                            a0 = 0;
                            jal(ctx, 0x17F510u, gen::fn_sub_16F180_0016f180);  //       the skip ends -> state 4
                            v0 = 4;
                            sw(v0, s0, 0);
                            v0 = 0;
                        } else {
                            // 0x0017f454
                            charge(ctx, 18);
                            jal(ctx, 0x17F454u, gen::fn_sub_16EF40_0016ef40);
                            a0 = v0;
                            jal(ctx, 0x17F460u, gen::fn_datSetDaysSinceApr5_0016ef70);  // JUMP: the date = the target day
                            jal(ctx, 0x17F468u, gen::fn_sub_16EF50_0016ef50);
                            a0 = v0;
                            jal(ctx, 0x17F474u, gen::fn_sub_16F150_0016f150);  //       the slot = the target slot
                            a0 = 0;
                            jal(ctx, 0x17F480u, gen::fn_sub_16F180_0016f180);  //       the skip ends -> state 4
                            v0 = 4;
                            sw(v0, s0, 0);
                            v0 = 0;
                        }
                        break;
                    }
                L_0017f52c:
                    charge(ctx, 6);
                    jal(ctx, 0x17F52Cu, gen::fn_datGetTime_0016ef30);
                    v1 = v0 & 0xFF;
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0017f54c
                        charge(ctx, 2);
                        jal(ctx, 0x17F54Cu, gen::fn_sub_180E60_00180e60);  // leaving ASA: clear the morning flags
                    } else {
                        // 0x0017f544
                        charge(ctx, 2);
                    }
                    // 0x0017f554
                    charge(ctx, 6);
                    jal(ctx, 0x17F554u, gen::fn_datGetTime_0016ef30);
                    v1 = v0 & 0xFF;
                    v0 = 8;
                    if (v1 == v0) {
                        // 0x0017f69c
                        charge(ctx, 12);
                        a0 = 0;
                        jal(ctx, 0x17F6A0u, gen::fn_sub_16F150_0016f150);  // the Dark Hour -> slot 0 ...
                        jal(ctx, 0x17F6A8u, gen::fn_datGetDaysSinceApr5_0016ef20);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        v0 = addiu(v0, 1);
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x17F6C4u, gen::fn_datSetDaysSinceApr5_0016ef70);  // ... of the next day
                    } else {
                        // 0x0017f56c
                        charge(ctx, 7);
                        jal(ctx, 0x17F56Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                        a0 = v0;
                        jal(ctx, 0x17F578u, gen::fn_sub_17DB40_0017db40);  // not a holiday ...
                        if (v0 == 0) {
                            // 0x0017f588
                            charge(ctx, 11);
                            jal(ctx, 0x17F588u, gen::fn_datGetDaysSinceApr5_0016ef20);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            v1 = addiu(v0, 7);
                            v0 = 7;
                            div(v1, v0);
                            mfhi(v1);
                            v0 = 6;
                            if (v1 != v0) {
                                goto L_0017f5e0;
                            }
                            // 0x0017f5b4
                            charge(ctx, 6);
                            jal(ctx, 0x17F5B4u, gen::fn_datGetTime_0016ef30);
                            v1 = v0 & 0xFF;
                            v0 = 2;
                            if (v1 != v0) {
                                goto L_0017f5e0;
                            }
                            // 0x0017f5cc
                            charge(ctx, 5);
                            a0 = 5;
                            jal(ctx, 0x17F5D0u, gen::fn_sub_16F150_0016f150);  // ... school Saturday GOZEN -> HOUKAGO
                            goto L_0017f6cc;
                        }
                    L_0017f5e0:
                        charge(ctx, 8);
                        jal(ctx, 0x17F5E0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                        a0 = v0;
                        jal(ctx, 0x17F5ECu, gen::fn_sub_17DB40_0017db40);  // a holiday ...
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x0017f600
                            charge(ctx, 6);
                            jal(ctx, 0x17F600u, gen::fn_datGetTime_0016ef30);
                            v1 = v0 & 0xFF;
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_0017f62c;
                            }
                            // 0x0017f618
                            charge(ctx, 5);
                            a0 = 4;
                            jal(ctx, 0x17F61Cu, gen::fn_sub_16F150_0016f150);  // ... ASA -> GOGO
                            goto L_0017f6cc;
                        }
                    L_0017f62c:
                        charge(ctx, 8);
                        jal(ctx, 0x17F62Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                        a0 = v0;
                        jal(ctx, 0x17F638u, gen::fn_sub_17DB40_0017db40);  // a holiday ...
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x0017f64c
                            charge(ctx, 6);
                            jal(ctx, 0x17F64Cu, gen::fn_datGetTime_0016ef30);
                            v1 = v0 & 0xFF;
                            v0 = 4;
                            if (v1 != v0) {
                                goto L_0017f678;
                            }
                            // 0x0017f664
                            charge(ctx, 5);
                            a0 = 6;
                            jal(ctx, 0x17F668u, gen::fn_sub_16F150_0016f150);  // ... GOGO -> YORU
                            goto L_0017f6cc;
                        }
                    L_0017f678:
                        charge(ctx, 9);
                        jal(ctx, 0x17F678u, gen::fn_datGetTime_0016ef30);
                        v0 = v0 & 0xFF;
                        v0 = addiu(v0, 1);
                        a0 = v0 & 0xFF;
                        jal(ctx, 0x17F68Cu, gen::fn_sub_16F150_0016f150);  // otherwise slot + 1
                    }
                L_0017f6cc:
                    charge(ctx, 5);
                    jal(ctx, 0x17F6CCu, gen::fn_sub_16EF60_0016ef60);  // the step reached the skip target: the skip ends
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x0017f6e0
                        charge(ctx, 10);
                        jal(ctx, 0x17F6E0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                        s1 = dsll32(v0, 16);
                        s1 = dsra32(s1, 16);
                        jal(ctx, 0x17F6F0u, gen::fn_sub_16EF40_0016ef40);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        if (s1 == v0) {
                            // 0x0017f708
                            charge(ctx, 8);
                            jal(ctx, 0x17F708u, gen::fn_datGetTime_0016ef30);
                            s1 = v0 & 0xFF;
                            jal(ctx, 0x17F714u, gen::fn_sub_16EF50_0016ef50);
                            v0 = v0 & 0xFF;
                            if (s1 == v0) {
                                // 0x0017f728
                                charge(ctx, 3);
                                a0 = 0;
                                jal(ctx, 0x17F72Cu, gen::fn_sub_16F180_0016f180);
                            }
                        }
                    }
                }
                // 0x0017f734
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, 0);
                goto L_0017f89c;
            }
            // 0x0017f3f4
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x17F744u:  // table[19] -- state 19: the memory-card task (sub_188640) -> 20
            // 0x0017f744
            charge(ctx, 7);
            jal(ctx, 0x17F744u, gen::fn_sub_188640_00188640);
            sw(v0, s0, 4);
            v0 = 20;
            sw(v0, s0, 0);
            goto L_0017f89c;
        case 0x17F760u:  // table[20] -- state 20: wait for it -> 21
            // 0x0017f760
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x17F764u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0017f778
                charge(ctx, 5);
                sw(zero, s0, 4);
                v0 = 21;
                sw(v0, s0, 0);
            }
            goto L_0017f89c;
        case 0x17F78Cu:  // table[21] -- state 21: a pending return to the field (0x7CDFFC) -> 16, else -> 3
            // 0x0017f78c
            charge(ctx, 3);
            lw(v0, gp, -19700);  // 0x7CDFFC
            if (v0 == 0) {
                // 0x0017f804
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, 0);
                goto L_0017f89c;
            }
            // 0x0017f798
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x0017f7a4
                charge(ctx, 3);
                jal(ctx, 0x17F7A4u, gen::fn_H_DayParts_CreateTask_00184db0);
                sw(v0, s0, 16);
            }
            // 0x0017f7b0
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x17F7B4u, gen::fn_H_DayPartsDraw_IsIdle_00184d90);
            if (v0 != 0) {
                // 0x0017f7d0
                charge(ctx, 13);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F7D8u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
                jal(ctx, 0x17F7E0u, gen::fn_sub_181B70_00181b70);
                v0 = 16;
                sw(v0, s0, 0);
                sw(zero, gp, -19700);  // 0x7CDFFC
                v0 = 1;
                sw(v0, s0, 36);
                goto L_0017f89c;
            }
            // 0x0017f7c4
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x17F814u:  // table[23] -- state 23: a fresh game: show the date and return to the field -> 16
            // 0x0017f814
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x0017f820
                charge(ctx, 3);
                jal(ctx, 0x17F820u, gen::fn_H_DayParts_CreateTask_00184db0);
                sw(v0, s0, 16);
            }
            // 0x0017f82c
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x17F830u, gen::fn_H_DayPartsDraw_IsIdle_00184d90);
            if (v0 != 0) {
                // 0x0017f84c
                charge(ctx, 12);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x17F854u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
                jal(ctx, 0x17F85Cu, gen::fn_sub_181B70_00181b70);
                v0 = 1;
                sw(v0, s0, 36);
                v0 = 16;
                sw(v0, s0, 0);
                goto L_0017f89c;
            }
            // 0x0017f840
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x17F87Cu:  // table[24] -- state 24: count down work +0x20; -1 (the task ends) at 0
            // 0x0017f87c
            charge(ctx, 5);
            lw(v0, s0, 32);
            v0 = addiu(v0, -1);
            sw(v0, s0, 32);
            if (v0 != 0) {
                goto L_0017f89c;
            }
            // 0x0017f890
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x17F89Cu:  // table[17] -- state 17 (idle)
            goto L_0017f89c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0017f8a0 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xB0);
        return;
    }
    goto L_0017f89c;
}

// 0x0017F8D0 sub_17F8D0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_17F8D0 [clndCalendarEndSequence]: when the calendar task exists (0x7CDFEC): its state becomes 3 (The Answer, unless
// 4) or 16 (The Journey, unless 17) and its sequence task (+0xC) is destroyed.
void sub_17F8D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017f8d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -19716);  // 0x7CDFEC
    if (v1 != 0) {
        // 0x0017f8e8
        charge(ctx, 4);
        jal(ctx, 0x17F8E8u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x0017f938
            charge(ctx, 6);
            lw(v1, gp, -19716);  // 0x7CDFEC
            lw(s0, v1, 60);
            lw(a0, s0, 0);
            v1 = 4;
            if (a0 != v1) {
                // 0x0017f950
                charge(ctx, 2);
                v1 = 3;
                sw(v1, s0, 0);
            }
            // 0x0017f958
            charge(ctx, 3);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x0017f964
                charge(ctx, 3);
                jal(ctx, 0x17F964u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                sw(zero, s0, 12);
            }
        } else {
            // 0x0017f8f8
            charge(ctx, 6);
            lw(v1, gp, -19716);  // 0x7CDFEC
            lw(s0, v1, 60);
            lw(a0, s0, 0);
            v1 = 17;
            if (a0 != v1) {
                // 0x0017f910
                charge(ctx, 2);
                v1 = 16;
                sw(v1, s0, 0);
            }
            // 0x0017f918
            charge(ctx, 3);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x0017f924
                charge(ctx, 5);
                jal(ctx, 0x17F924u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                sw(zero, s0, 12);
            }
        }
    }
    // 0x0017f970 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017FA10 sub_17FA10 -- 140 bytes; frame 0x10: ra sp+0x0
// sub_17FA10: when the calendar task exists: its state = 5 (The Answer) / 18 (The Journey), then adminiChangeSeq(0).
void sub_17FA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fa10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, -19716);  // 0x7CDFEC
    if (v1 != 0) {
        // 0x0017fa24
        charge(ctx, 4);
        jal(ctx, 0x17FA24u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x0017fa64
            charge(ctx, 10);
            v1 = 5;
            lw(v0, gp, -19716);  // 0x7CDFEC
            lw(v0, v0, 60);
            sw(v1, v0, 0);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x17FA84u, gen::fn_adminiChangeSeq_0027c080);
        } else {
            // 0x0017fa34
            charge(ctx, 12);
            v1 = 18;
            lw(v0, gp, -19716);  // 0x7CDFEC
            lw(v0, v0, 60);
            sw(v1, v0, 0);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x17FA54u, gen::fn_adminiChangeSeq_0027c080);
        }
    }
    // 0x0017fa8c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017FAA0 sub_17FAA0 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_17FAA0: the calendar task's destroy function: frees its work (*0x96017C) and clears 0x7CDFEC.
void sub_17FAA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017faa0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x17FAB4u, v0.u());
    sw(zero, gp, -19716);  // 0x7CDFEC
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017FAD0 sub_17FAD0 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17FAD0 [clndCreateCalendarTask]: allocates the 44-byte work and creates the "CalenderDraw" task (sub_17E680 /
// sub_17FAA0, priority 4207) in state 3; 0x7CDFEC = the task. Returns it (0 on failure).
void sub_17FAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fad0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    a1 = 44;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x17FAF4u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0017fb14
        charge(ctx, 14);
        a0 = 0;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 15336);  // "CalenderDraw"
        a3 = 0x180000;
        a3 = addiu(a3, -6528);  // &sub_17E680
        t0 = 0x180000;
        t0 = addiu(t0, -1376);  // &sub_17FAA0
        t1 = s0;
        jal(ctx, 0x17FB38u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        if (s1 != 0) {
            // 0x0017fb58
            charge(ctx, 7);
            sw(s1, gp, -19716);  // 0x7CDFEC
            v0 = 3;
            sw(v0, s0, 0);
            a0 = s1;
            jal(ctx, 0x17FB68u, gen::fn_sub_10BDA0_0010bda0);
            v0 = s1;
        } else {
            // 0x0017fb4c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0017fb08
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017fb74 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017FB90 sub_17FB90 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17FB90 [clndCreateCalendarTaskNewGame]: as sub_17FAD0 in state 23, or 3 when today is day 2 (April 7).
void sub_17FB90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fb90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    a1 = 44;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x17FBB4u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0017fbd4
        charge(ctx, 14);
        a0 = 0;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 15336);  // "CalenderDraw"
        a3 = 0x180000;
        a3 = addiu(a3, -6528);  // &sub_17E680
        t0 = 0x180000;
        t0 = addiu(t0, -1376);  // &sub_17FAA0
        t1 = s0;
        jal(ctx, 0x17FBF8u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        if (s1 != 0) {
            // 0x0017fc18
            charge(ctx, 13);
            sw(s1, gp, -19716);  // 0x7CDFEC
            v0 = 23;
            sw(v0, s0, 0);
            a0 = s1;
            jal(ctx, 0x17FC28u, gen::fn_sub_10BDA0_0010bda0);
            jal(ctx, 0x17FC30u, gen::fn_datGetDaysSinceApr5_0016ef20);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 2;
            if (v1 == v0) {
                // 0x0017fc4c
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, 0);
            }
            // 0x0017fc54
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x0017fc0c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0017fbc8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0017fc58 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017FC70 sub_17FC70 -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17FC70(task) [clndSeq_Sinya]: the late-night slot (7, "!!!!!!!!sinya seq"): nothing during a time skip or with
// flag 0xA02; today's scheduled event (sub_181720 / sub_181950) or the social timer task.
void sub_17FC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fc70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    jal(ctx, 0x17FC88u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x0017fc98
        charge(ctx, 6);
        a0 = 0xA02;  // end the late-night slot
        jal(ctx, 0x17FC9Cu, gen::fn_datGetFlag_0016f190);
        v1 = 1;
        if (v0 == v1) {
            goto L_0017fd08;
        }
        // 0x0017fcb0
        charge(ctx, 5);
        jal(ctx, 0x17FCB0u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x0017fcdc
            charge(ctx, 11);
            a0 = 0x5E0000;
            a0 = addiu(a0, 15360);  // "!!!!!!!!sinya seq\n"
            jal(ctx, 0x17FCE4u, gen::fn_printf_005225a8);
            jal(ctx, 0x17FCECu, gen::fn_datGetTime_0016ef30);
            a1 = v0 & 0xFF;
            a0 = s1;
            jal(ctx, 0x17FCFCu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
            s0 = v0;
            goto L_0017fd08;
        }
        // 0x0017fcc4
        charge(ctx, 6);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x17FCCCu, gen::fn_sub_181950_00181950);
        // 0x0017fd0c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0017fd08:
    charge(ctx, 1);
    v0 = s0;
    // 0x0017fd0c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017FE10 sub_17FE10 -- 540 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17FE10(task) [clndNewDayReset]: the first morning step of a new day: flags 0xBD0..0xBFF, 0xA01, 0xA02 and 0xA04
// cleared, the 12 {u16, u16} pairs of records 2..10 (sub_170620) reloaded from the rows at 0x5E3C20 (48 bytes per
// member),
// the dated flag rows of sub_3BD8A0 ({month, day, set flag, clear flag}, 6 bytes) applied for today, then
// sub_1B7700(task).
void sub_17FE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fe10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s0 = 3024;
    for (;;) {
        // 0x0017fe58
        charge(ctx, 3);
        v0 = slti(s0, 3072);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017fe44
        charge(ctx, 5);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x17FE4Cu, gen::fn_datSetFlag_0016f1f0);
        s0 = addiu(s0, 1);
    }
    // 0x0017fe64
    charge(ctx, 18);
    a0 = 0xA01;  // end the evening slot
    a1 = 0;
    jal(ctx, 0x17FE6Cu, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA02;  // end the late-night slot
    a1 = 0;
    jal(ctx, 0x17FE7Cu, gen::fn_datSetFlag_0016f1f0);
    a0 = 2564;
    a1 = 0;
    jal(ctx, 0x17FE8Cu, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x17FE94u, gen::fn_sub_3BD8A0_003bd8a0);
    s2 = v0;
    s3 = 2;
    for (;;) {
        // 0x0017ff2c
        charge(ctx, 3);
        v0 = slti(s3, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017feac
        charge(ctx, 9);
        s4 = 0;
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v1 = sll(v0, 4);
        v0 = 0x5E0000;
        v0 = addiu(v0, 15392);  // &0x5E3C20
        s1 = addu(v0, v1);
        for (;;) {
            // 0x0017ff1c
            charge(ctx, 3);
            v0 = slti(s4, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017fed0
            charge(ctx, 19);
            v0 = sll(s4, 2);
            s0 = addu(s1, v0);
            lh(s6, s0, -96);
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x17FEECu, gen::fn_sub_170620_00170620);
            sh(s6, v0, 0);
            lh(s0, s0, -94);
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x17FF0Cu, gen::fn_sub_170620_00170620);
            sh(s0, v0, 2);
            s4 = addiu(s4, 1);
        }
        // 0x0017ff28
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x0017ff38
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0017ffe4
        charge(ctx, 4);
        lw(v0, s2, 4);
        v0 = sltu(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017ff44
        charge(ctx, 14);
        jal(ctx, 0x17FF44u, gen::fn_datGetDaysSinceApr5_0016ef20);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x17FF54u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
        v1 = sll(s1, 1);
        v1 = addu(v1, s1);
        s0 = sll(v1, 1);
        lw(v1, s2, 0);
        v1 = addu(v1, s0);
        lbu(v1, v1, 0);
        if (v1 == v0) {
            // 0x0017ff7c
            charge(ctx, 11);
            jal(ctx, 0x17FF7Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x17FF8Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
            lw(v1, s2, 0);
            a0 = addu(v1, s0);
            lbu(v1, a0, 1);
            if (v1 == v0) {
                // 0x0017ffa8
                charge(ctx, 3);
                lhu(a0, a0, 2);
                if (a0 != 0) {
                    // 0x0017ffb4
                    charge(ctx, 3);
                    a1 = 1;
                    jal(ctx, 0x17FFB8u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x0017ffc0
                charge(ctx, 5);
                lw(v0, s2, 0);
                v0 = addu(v0, s0);
                lhu(a0, v0, 4);
                if (a0 != 0) {
                    // 0x0017ffd4
                    charge(ctx, 3);
                    a1 = 0;
                    jal(ctx, 0x17FFD8u, gen::fn_datSetFlag_0016f1f0);
                }
            }
        }
        // 0x0017ffe0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0017fff4
    charge(ctx, 14);
    a0 = s5;
    jal(ctx, 0x17FFF8u, gen::fn_sub_1B7700_001b7700);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00180030 sub_180030 -- 492 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_180030 [clndApplyScheduledConditions]: the dated condition rows of sub_3BD890 ({month, day, pc, condition}):
// today's rows set the condition (sub_16D6B0); for the hero (pc 1) the condition flags 0xA95..0xA9C and 0xA7A are
// cleared first and 0xA98 / 0xA99 / 0xA9B set for condition 5 / 3 / 2.
void sub_180030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180030
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x180044u, gen::fn_sub_3BD890_003bd890);
    s1 = v0;
    s2 = 0;
    for (;;) {
        // 0x001801f0
        charge(ctx, 4);
        lw(v1, s1, 4);
        v1 = sltu(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018005c
        charge(ctx, 12);
        jal(ctx, 0x18005Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x18006Cu, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
        s0 = sll(s2, 2);
        lw(v1, s1, 0);
        v1 = addu(v1, s0);
        lbu(v1, v1, 0);
        if (v1 == v0) {
            // 0x0018008c
            charge(ctx, 11);
            jal(ctx, 0x18008Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x18009Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
            lw(v1, s1, 0);
            a0 = addu(v1, s0);
            lbu(v1, a0, 1);
            if (v1 == v0) {
                // 0x001800b8
                charge(ctx, 4);
                lbu(v1, a0, 2);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001800c8
                    charge(ctx, 42);
                    a0 = 0xA95;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x1800D0u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA96;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x1800E0u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA97;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x1800F0u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA98;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x180100u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA99;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x180110u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA9A;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x180120u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA7A;  // condition message 6 (forced tired)
                    a1 = 0;
                    jal(ctx, 0x180130u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA9B;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x180140u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 0xA9C;  // condition message flag
                    a1 = 0;
                    jal(ctx, 0x180150u, gen::fn_datSetFlag_0016f1f0);
                    lw(v0, s1, 0);
                    v0 = addu(v0, s0);
                    lbu(v1, v0, 3);
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x00180170
                        charge(ctx, 4);
                        a0 = 0xA98;  // condition message flag
                        a1 = 1;
                        jal(ctx, 0x180178u, gen::fn_datSetFlag_0016f1f0);
                    }
                    // 0x00180180
                    charge(ctx, 6);
                    lw(v0, s1, 0);
                    v0 = addu(v0, s0);
                    lbu(v1, v0, 3);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x00180198
                        charge(ctx, 4);
                        a0 = 0xA99;  // condition message flag
                        a1 = 1;
                        jal(ctx, 0x1801A0u, gen::fn_datSetFlag_0016f1f0);
                    }
                    // 0x001801a8
                    charge(ctx, 6);
                    lw(v0, s1, 0);
                    v0 = addu(v0, s0);
                    lbu(v1, v0, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x001801c0
                        charge(ctx, 4);
                        a0 = 0xA9B;  // condition message flag
                        a1 = 1;
                        jal(ctx, 0x1801C8u, gen::fn_datSetFlag_0016f1f0);
                    }
                }
                // 0x001801d0
                charge(ctx, 7);
                lw(v1, s1, 0);
                v0 = sll(s2, 2);
                v0 = addu(v1, v0);
                lbu(a0, v0, 2);
                lbu(a1, v0, 3);
                jal(ctx, 0x1801E4u, gen::fn_sub_16D6B0_0016d6b0);
            }
        }
        // 0x001801ec
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00180200
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00180220 sub_180220 -- 2040 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_180220 [clndUpdateConditions]: the daily condition step of pc 1..10 (each one without a dated row today; the
// counters are sub_16F380 / sub_16F3E0): condition 2 counts counter pc + 15 down by 1; condition 3 counts it down by
// 25 + rand % 20 (pc 3: counter 18; the others turn into condition 5 instead with 21% chance); condition 5 by
// 20 + rand % 40, 30 / 60 more with flag 0xA2E - pc / 0xA40 - pc (the hero: 0xA8E / 0xA8F); a counter reaching 0
// means condition 0, flag 0xA9E keeps the hero at 0, counter pc + 25 >= 100 forces 2 (not pc 3); the hero's
// condition-message flags 0xA95..0xA9F / 0xACD / 0xACE follow the change (0xA7A forces 2) and the bonus flags are
// cleared; then flag 0x141C, every member's HP / SP refilled to the maximum, sub_16D9D0(pc, 0x80000).
void sub_180220(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180220
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 1;
    for (;;) {
        // 0x00180958
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00180248
        charge(ctx, 8);
        jal(ctx, 0x180248u, gen::fn_sub_3BD890_003bd890);
        s3 = v0;
        s4 = 0;
        s2 = dsll32(s0, 16);
        s2 = dsra32(s2, 16);
        for (;;) {
            // 0x001802e0
            charge(ctx, 4);
            lw(v0, s3, 4);
            v0 = sltu(s4, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00180268
            charge(ctx, 12);
            jal(ctx, 0x180268u, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x180278u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
            s1 = sll(s4, 2);
            lw(v1, s3, 0);
            v1 = addu(v1, s1);
            lbu(v1, v1, 0);
            if (v1 == v0) {
                // 0x00180298
                charge(ctx, 11);
                jal(ctx, 0x180298u, gen::fn_datGetDaysSinceApr5_0016ef20);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1802A8u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                lw(v1, s3, 0);
                a0 = addu(v1, s1);
                lbu(v1, a0, 1);
                if (v1 != v0) {
                    goto L_001802dc;
                }
                // 0x001802c4
                charge(ctx, 3);
                lbu(v0, a0, 2);
                if (s2 != v0) {
                    goto L_001802dc;
                }
                // 0x001802d0
                charge(ctx, 3);
                v0 = 1;
                goto L_001802f4;
            }
        L_001802dc:
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x001802f0
        charge(ctx, 1);
        v0 = 0;
    L_001802f4:
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x001802fc
            charge(ctx, 17);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x180304u, gen::fn_sub_16C920_0016c920);
            s3 = v0 & 0xFFFF;
            s1 = s3;
            a0 = addiu(s0, 25);
            jal(ctx, 0x180318u, gen::fn_sub_16F380_0016f380);
            a0 = addiu(s0, 25);
            a1 = v0;
            jal(ctx, 0x180328u, gen::fn_sub_16F3E0_0016f3e0);
            v1 = s3 & 0xFFFF;
            v0 = 2;
            if (v1 == v0) {
                // 0x001805c4
                charge(ctx, 6);
                a0 = addiu(s0, 15);
                jal(ctx, 0x1805C8u, gen::fn_sub_16F380_0016f380);
                s2 = addiu(v0, -1);
                if (i64(s2) < 0) {
                    // 0x001805dc
                    charge(ctx, 1);
                    s2 = 0;
                }
                // 0x001805e0
                charge(ctx, 6);
                a0 = addiu(s0, 15);
                a1 = s2;
                jal(ctx, 0x1805E8u, gen::fn_sub_16F3E0_0016f3e0);
                if (s2 == 0) {
                    // 0x001805f8
                    charge(ctx, 1);
                    s3 = 0;
                }
            } else {
                // 0x00180340
                charge(ctx, 3);
                v0 = 3;
                if (v1 == v0) {
                    // 0x00180490
                    charge(ctx, 5);
                    a0 = addiu(s0, 25);
                    jal(ctx, 0x180494u, gen::fn_sub_16F380_0016f380);
                    if (i64(v0) < 0) {
                        // 0x001804a4
                        charge(ctx, 1);
                        v0 = 0;
                    }
                    // 0x001804a8
                    charge(ctx, 7);
                    a0 = addiu(s0, 25);
                    a1 = v0;
                    jal(ctx, 0x1804B0u, gen::fn_sub_16F3E0_0016f3e0);
                    v0 = 3;
                    if (s0 == v0) {
                        // 0x00180548
                        charge(ctx, 12);
                        jal(ctx, 0x180548u, gen::fn_sub_488F30_00488f30);
                        v1 = 20;
                        divu(v0, v1);
                        mfhi(s2);
                        a0 = addiu(s0, 15);
                        jal(ctx, 0x180560u, gen::fn_sub_16F380_0016f380);
                        v1 = addiu(s2, 25);
                        s2 = subu(v0, v1);
                        if (i64(s2) < 0) {
                            // 0x00180578
                            charge(ctx, 1);
                            s2 = 0;
                        }
                        // 0x0018057c
                        charge(ctx, 6);
                        a0 = addiu(s0, 15);
                        a1 = s2;
                        jal(ctx, 0x180584u, gen::fn_sub_16F3E0_0016f3e0);
                        if (s2 == 0) {
                            // 0x00180594
                            charge(ctx, 1);
                            s3 = 0;
                        }
                    } else {
                        // 0x001804c4
                        charge(ctx, 8);
                        jal(ctx, 0x1804C4u, gen::fn_sub_488F30_00488f30);
                        v1 = 100;
                        divu(v0, v1);
                        mfhi(v0);
                        at = sltiu(v0, 21);
                        if (at == 0) {
                            // 0x001804f0
                            charge(ctx, 12);
                            jal(ctx, 0x1804F0u, gen::fn_sub_488F30_00488f30);
                            v1 = 20;
                            divu(v0, v1);
                            mfhi(s2);
                            a0 = addiu(s0, 15);
                            jal(ctx, 0x180508u, gen::fn_sub_16F380_0016f380);
                            v1 = addiu(s2, 25);
                            s2 = subu(v0, v1);
                            if (i64(s2) < 0) {
                                // 0x00180520
                                charge(ctx, 1);
                                s2 = 0;
                            }
                            // 0x00180524
                            charge(ctx, 6);
                            a0 = addiu(s0, 15);
                            a1 = s2;
                            jal(ctx, 0x18052Cu, gen::fn_sub_16F3E0_0016f3e0);
                            if (s2 == 0) {
                                // 0x0018053c
                                charge(ctx, 3);
                                s3 = 0;
                            }
                        } else {
                            // 0x001804e4
                            charge(ctx, 3);
                            s3 = 5;
                        }
                    }
                    // 0x00180598
                    charge(ctx, 3);
                    v0 = 1;
                    if (s0 == v0) {
                        // 0x001805a4
                        charge(ctx, 5);
                        a0 = 0xA9E;  // hero kept well
                        jal(ctx, 0x1805A8u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x001805b8
                            charge(ctx, 3);
                            s3 = 0;
                        }
                    }
                } else {
                    // 0x0018034c
                    charge(ctx, 3);
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x00180368
                        charge(ctx, 5);
                        a0 = addiu(s0, 25);
                        jal(ctx, 0x18036Cu, gen::fn_sub_16F380_0016f380);
                        if (i64(v0) < 0) {
                            // 0x0018037c
                            charge(ctx, 1);
                            v0 = 0;
                        }
                        // 0x00180380
                        charge(ctx, 17);
                        a0 = addiu(s0, 25);
                        a1 = v0;
                        jal(ctx, 0x180388u, gen::fn_sub_16F3E0_0016f3e0);
                        jal(ctx, 0x180390u, gen::fn_sub_488F30_00488f30);
                        v1 = 40;
                        divu(v0, v1);
                        mfhi(s2);
                        a0 = addiu(s0, 15);
                        jal(ctx, 0x1803A8u, gen::fn_sub_16F380_0016f380);
                        v1 = addiu(s2, 20);
                        s2 = subu(v0, v1);
                        v0 = 1;
                        if (s0 != v0) {
                            // 0x00180404
                            charge(ctx, 6);
                            v0 = 2606;
                            a0 = subu(v0, s0);
                            jal(ctx, 0x18040Cu, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x0018041c
                                charge(ctx, 1);
                                s2 = addiu(s2, -30);
                            }
                            // 0x00180420
                            charge(ctx, 6);
                            v0 = 2624;
                            a0 = subu(v0, s0);
                            jal(ctx, 0x180428u, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x00180438
                                charge(ctx, 1);
                                s2 = addiu(s2, -60);
                            }
                        } else {
                            // 0x001803c4
                            charge(ctx, 5);
                            a0 = 0xA8E;  // hero recovery bonus 30
                            jal(ctx, 0x1803C8u, gen::fn_datGetFlag_0016f190);
                            if (v0 == 0) {
                                // 0x001803e4
                                charge(ctx, 5);
                                a0 = 0xA8F;  // hero recovery bonus 60
                                jal(ctx, 0x1803E8u, gen::fn_datGetFlag_0016f190);
                                if (v0 != 0) {
                                    // 0x001803f8
                                    charge(ctx, 3);
                                    s2 = addiu(s2, -60);
                                }
                            } else {
                                // 0x001803d8
                                charge(ctx, 3);
                                s2 = addiu(s2, -30);
                            }
                        }
                        // 0x0018043c
                        charge(ctx, 2);
                        if (i64(s2) <= 0) {
                            // 0x00180444
                            charge(ctx, 1);
                            s2 = 0;
                        }
                        // 0x00180448
                        charge(ctx, 6);
                        a0 = addiu(s0, 15);
                        a1 = s2;
                        jal(ctx, 0x180450u, gen::fn_sub_16F3E0_0016f3e0);
                        if (s2 == 0) {
                            // 0x00180460
                            charge(ctx, 1);
                            s3 = 0;
                        }
                        // 0x00180464
                        charge(ctx, 3);
                        v0 = 1;
                        if (s0 == v0) {
                            // 0x00180470
                            charge(ctx, 5);
                            a0 = 0xA9E;  // hero kept well
                            jal(ctx, 0x180474u, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x00180484
                                charge(ctx, 3);
                                s3 = 0;
                            }
                        }
                    } else {
                        // 0x00180358
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x00180360
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x001805fc
            charge(ctx, 3);
            v0 = 3;
            if (s0 != v0) {
                // 0x00180608
                charge(ctx, 6);
                a0 = addiu(s0, 25);
                jal(ctx, 0x18060Cu, gen::fn_sub_16F380_0016f380);
                v0 = slti(v0, 100);
                if (v0 == 0) {
                    // 0x00180620
                    charge(ctx, 1);
                    s3 = 2;
                }
            }
            // 0x00180624
            charge(ctx, 8);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            a1 = s3;
            jal(ctx, 0x180630u, gen::fn_sub_16D6B0_0016d6b0);
            v0 = 1;
            if (s0 == v0) {
                // 0x00180644
                charge(ctx, 50);
                a0 = 0xA95;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18064Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA96;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18065Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA97;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18066Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA98;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18067Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA99;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18068Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA9A;  // condition message flag
                a1 = 0;
                jal(ctx, 0x18069Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA9B;  // condition message flag
                a1 = 0;
                jal(ctx, 0x1806ACu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA9C;  // condition message flag
                a1 = 0;
                jal(ctx, 0x1806BCu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA9F;  // condition message flag
                a1 = 0;
                jal(ctx, 0x1806CCu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xACD;  // condition message flag
                a1 = 0;
                jal(ctx, 0x1806DCu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xACE;  // condition message flag
                a1 = 0;
                jal(ctx, 0x1806ECu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA7A;  // condition message 6 (forced tired)
                jal(ctx, 0x1806F8u, gen::fn_datGetFlag_0016f190);
                a1 = 1;
                if (v0 != a1) {
                    // 0x00180724
                    charge(ctx, 4);
                    v0 = s3 & 0xFFFF;
                    a2 = 2;
                    if (v0 == a2) {
                        // 0x001808c8
                        charge(ctx, 3);
                        v0 = s1 & 0xFFFF;
                        if (v0 == 0) {
                            // 0x001808dc
                            charge(ctx, 3);
                            a0 = 0xA9B;  // condition message flag
                            jal(ctx, 0x1808E0u, gen::fn_datSetFlag_0016f1f0);
                        } else {
                            // 0x001808d4
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x00180734
                        charge(ctx, 3);
                        a0 = 3;
                        if (v0 == a0) {
                            // 0x001808a0
                            charge(ctx, 3);
                            v0 = s1 & 0xFFFF;
                            if (v0 == a0) {
                                // 0x001808b4
                                charge(ctx, 5);
                                a0 = 0xA9D;  // condition message flag
                                jal(ctx, 0x1808B8u, gen::fn_datSetFlag_0016f1f0);
                            } else {
                                // 0x001808ac
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x00180740
                            charge(ctx, 3);
                            v1 = 5;
                            if (v0 == v1) {
                                // 0x0018085c
                                charge(ctx, 3);
                                v0 = s1 & 0xFFFF;
                                if (v0 == a0) {
                                    // 0x0018088c
                                    charge(ctx, 5);
                                    a0 = 0xA97;  // condition message flag
                                    jal(ctx, 0x180890u, gen::fn_datSetFlag_0016f1f0);
                                } else {
                                    // 0x00180868
                                    charge(ctx, 2);
                                    if (v0 == v1) {
                                        // 0x00180878
                                        charge(ctx, 5);
                                        a0 = 0xA96;  // condition message flag
                                        jal(ctx, 0x18087Cu, gen::fn_datSetFlag_0016f1f0);
                                    } else {
                                        // 0x00180870
                                        charge(ctx, 2);
                                    }
                                }
                            } else {
                                // 0x0018074c
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x0018075c
                                    charge(ctx, 3);
                                    v0 = s1 & 0xFFFF;
                                    if (v0 == a2) {
                                        // 0x00180848
                                        charge(ctx, 5);
                                        a0 = 0xA9C;  // condition message flag
                                        jal(ctx, 0x18084Cu, gen::fn_datSetFlag_0016f1f0);
                                    } else {
                                        // 0x00180768
                                        charge(ctx, 2);
                                        if (v0 == a0) {
                                            // 0x00180804
                                            charge(ctx, 5);
                                            a0 = 0xA9E;  // hero kept well
                                            jal(ctx, 0x180808u, gen::fn_datGetFlag_0016f190);
                                            if (v0 == 0) {
                                                // 0x00180830
                                                charge(ctx, 6);
                                                a0 = 0xA9A;  // condition message flag
                                                a1 = 1;
                                                jal(ctx, 0x180838u, gen::fn_datSetFlag_0016f1f0);
                                            } else {
                                                // 0x00180818
                                                charge(ctx, 6);
                                                a0 = 0xACD;  // condition message flag
                                                a1 = 1;
                                                jal(ctx, 0x180820u, gen::fn_datSetFlag_0016f1f0);
                                            }
                                        } else {
                                            // 0x00180770
                                            charge(ctx, 2);
                                            if (v0 == v1) {
                                                // 0x00180780
                                                charge(ctx, 5);
                                                a0 = 0xA8E;  // hero recovery bonus 30
                                                jal(ctx, 0x180784u, gen::fn_datGetFlag_0016f190);
                                                if (v0 == 0) {
                                                    // 0x00180794
                                                    charge(ctx, 5);
                                                    a0 = 0xA8F;  // hero recovery bonus 60
                                                    jal(ctx, 0x180798u, gen::fn_datGetFlag_0016f190);
                                                    if (v0 != 0) {
                                                        goto L_001807a8;
                                                    }
                                                    // 0x001807c0
                                                    charge(ctx, 5);
                                                    a0 = 0xA9E;  // hero kept well
                                                    jal(ctx, 0x1807C4u, gen::fn_datGetFlag_0016f190);
                                                    if (v0 == 0) {
                                                        // 0x001807ec
                                                        charge(ctx, 6);
                                                        a0 = 0xA95;  // condition message flag
                                                        a1 = 1;
                                                        jal(ctx, 0x1807F4u, gen::fn_datSetFlag_0016f1f0);
                                                    } else {
                                                        // 0x001807d4
                                                        charge(ctx, 6);
                                                        a0 = 0xA9F;  // condition message flag
                                                        a1 = 1;
                                                        jal(ctx, 0x1807DCu, gen::fn_datSetFlag_0016f1f0);
                                                    }
                                                    goto L_001808e8;
                                                }
                                            L_001807a8:
                                                charge(ctx, 6);
                                                a0 = 0xACE;  // condition message flag
                                                a1 = 1;
                                                jal(ctx, 0x1807B0u, gen::fn_datSetFlag_0016f1f0);
                                            } else {
                                                // 0x00180778
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                } else {
                                    // 0x00180754
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                } else {
                    // 0x0018070c
                    charge(ctx, 6);
                    a0 = a1;
                    a1 = 2;
                    jal(ctx, 0x180714u, gen::fn_sub_16D6B0_0016d6b0);
                }
            }
        L_001808e8:
            charge(ctx, 3);
            v0 = 1;
            if (s0 != v0) {
                // 0x0018092c
                charge(ctx, 10);
                v0 = 2606;
                a0 = subu(v0, s0);
                a1 = 0;
                jal(ctx, 0x180938u, gen::fn_datSetFlag_0016f1f0);
                v0 = 2624;
                a0 = subu(v0, s0);
                a1 = 0;
                jal(ctx, 0x18094Cu, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x001808f4
                charge(ctx, 14);
                a0 = 0xA8E;  // hero recovery bonus 30
                a1 = 0;
                jal(ctx, 0x1808FCu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA8F;  // hero recovery bonus 60
                a1 = 0;
                jal(ctx, 0x18090Cu, gen::fn_datSetFlag_0016f1f0);
                a0 = 0xA9E;  // hero kept well
                a1 = 0;
                jal(ctx, 0x18091Cu, gen::fn_datSetFlag_0016f1f0);
            }
        }
        // 0x00180954
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00180964
    charge(ctx, 7);
    a0 = 0x141C;  // conditions changed (the message is due)
    a1 = 1;
    jal(ctx, 0x18096Cu, gen::fn_datSetFlag_0016f1f0);
    s0 = 1;
    for (;;) {
        // 0x001809e8
        charge(ctx, 3);
        v1 = slti(s0, 11);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00180980
        charge(ctx, 26);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x180988u, gen::fn_sub_16C5F0_0016c5f0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1809A0u, gen::fn_sub_16CF40_0016cf40);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1809B0u, gen::fn_sub_16C670_0016c670);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1809C8u, gen::fn_sub_16CF90_0016cf90);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0x80000;
        jal(ctx, 0x1809DCu, gen::fn_sub_16D9D0_0016d9d0);
        s0 = addiu(s0, 1);
    }
    // 0x001809f4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
}

// 0x00180A20 sub_180A20 -- 544 bytes; frame 0x60: ra sp+0x50, s1 sp+0x40 (sq), s0 sp+0x30 (sq)
// sub_180A20(task) [clndSeq_Souchou]: the early-morning slot (0): day-part flag 0xA80..0xA87 all cleared; today's
// event, else (once per day, flag 0x1403) the time-skip target is set to now and, with flag 0xBDF, the date HUD shown
// and the field event 800 / 1 started.
void sub_180A20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180a20
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    s0 = a0;
    lw(s1, a0, 60);
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x180A40u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x180A50u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x180A60u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x180A70u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x180A80u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x180A90u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x180AA0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x180AB0u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x180AB8u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x00180ac8
        charge(ctx, 5);
        jal(ctx, 0x180AC8u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x00180af4
            charge(ctx, 6);
            a0 = 0xA00;  // end the early-morning slot
            jal(ctx, 0x180AF8u, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 != v1) {
                // 0x00180b18
                charge(ctx, 4);
                jal(ctx, 0x180B18u, gen::fn_sub_16EF60_0016ef60);
                if (v0 != 0) {
                    goto L_00180c24;
                }
                // 0x00180b28
                charge(ctx, 5);
                a0 = 0x1403;  // morning: early-morning skip target set
                jal(ctx, 0x180B2Cu, gen::fn_datGetFlag_0016f190);
                if (v0 != 0) {
                    goto L_00180c24;
                }
                // 0x00180b3c
                charge(ctx, 23);
                a0 = 0x1403;  // morning: early-morning skip target set
                a1 = 1;
                jal(ctx, 0x180B44u, gen::fn_datSetFlag_0016f1f0);
                jal(ctx, 0x180B4Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                a0 = v0;
                jal(ctx, 0x180B58u, gen::fn_sub_16F160_0016f160);
                jal(ctx, 0x180B60u, gen::fn_datGetTime_0016ef30);
                a0 = v0;
                jal(ctx, 0x180B6Cu, gen::fn_sub_16F170_0016f170);
                a0 = 1;
                jal(ctx, 0x180B78u, gen::fn_sub_16F180_0016f180);
                a0 = 0xBDF;  // flag 0xBDF
                jal(ctx, 0x180B84u, gen::fn_datGetFlag_0016f190);
                v1 = 1;
                if (v0 != v1) {
                    goto L_00180c24;
                }
                // 0x00180b98
                charge(ctx, 5);
                jal(ctx, 0x180B98u, gen::fn_datGetTime_0016ef30);
                v0 = v0 & 0xFF;
                if (v0 != 0) {
                    // 0x00180bc4
                    charge(ctx, 4);
                    lw(a0, s1, 16);
                    a1 = 1;
                    jal(ctx, 0x180BCCu, gen::fn_sub_1848F0_001848f0);
                } else {
                    // 0x00180bac
                    charge(ctx, 6);
                    lw(a0, s1, 16);
                    a1 = 1;
                    jal(ctx, 0x180BB4u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
                }
                // 0x00180bd4
                charge(ctx, 20);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 800;
                sd(v0, sp, 0x10);
                v0 = 1;
                sd(v0, sp, 0x18);
                sd(zero, sp, 0x20);
                sd(zero, sp, 0x28);
                a0 = s0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x180C14u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
            } else {
                // 0x00180b0c
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x00180adc
            charge(ctx, 6);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x180AE4u, gen::fn_sub_181950_00181950);
        }
        // 0x00180c28 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        sp = addiu(sp, 0x60);
        return;
    }
L_00180c24:
    charge(ctx, 1);
    v0 = 0;
    // 0x00180c28 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    sp = addiu(sp, 0x60);
}

// 0x00180C40 sub_180C40 -- 536 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_180C40(task) [clndSeq_Asa]: the morning slot (1, "!!!!!!!asa seq"): day-part flag 0xA80; the first call of a
// day (flag 0x1402) resets the day (flag 0xBD2 cleared, sub_27D8D0, sub_1FA450, sub_17FE10, work +0x24 = 0); the next ones run
// the daily conditions once (0x1406: sub_180220, sub_1A5CD0; 0x1405: sub_180030), then today's event or the social
// timer task.
void sub_180C40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180c40
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    a0 = 0x5E0000;
    a0 = addiu(a0, 15872);  // "!!!!!!!asa seq\n"
    jal(ctx, 0x180C60u, gen::fn_printf_005225a8);
    a0 = 0xA80;  // slot flag: ASA
    a1 = 1;
    jal(ctx, 0x180C70u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x180C80u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x180C90u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x180CA0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x180CB0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x180CC0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x180CD0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x180CE0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x1402;  // morning: new day done
    jal(ctx, 0x180CECu, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x00180d44
        charge(ctx, 5);
        a0 = 0x1406;  // morning: daily conditions done
        jal(ctx, 0x180D48u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x00180d58
            charge(ctx, 8);
            a0 = 0x1406;  // morning: daily conditions done
            a1 = 1;
            jal(ctx, 0x180D60u, gen::fn_datSetFlag_0016f1f0);
            jal(ctx, 0x180D68u, gen::fn_sub_180220_00180220);
            jal(ctx, 0x180D70u, gen::fn_sub_1A5CD0_001a5cd0);
        }
        // 0x00180d78
        charge(ctx, 5);
        a0 = 0x1405;  // morning: dated conditions done
        jal(ctx, 0x180D7Cu, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x00180d8c
            charge(ctx, 6);
            a0 = 0x1405;  // morning: dated conditions done
            a1 = 1;
            jal(ctx, 0x180D94u, gen::fn_datSetFlag_0016f1f0);
            jal(ctx, 0x180D9Cu, gen::fn_sub_180030_00180030);
        }
        // 0x00180da4
        charge(ctx, 4);
        jal(ctx, 0x180DA4u, gen::fn_sub_16EF60_0016ef60);
        if (v0 != 0) {
            // 0x00180e3c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00180db4
            charge(ctx, 5);
            jal(ctx, 0x180DB4u, gen::fn_sub_181720_00181720);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x00180de0
                charge(ctx, 7);
                jal(ctx, 0x180DE0u, gen::fn_datGetDaysSinceApr5_0016ef20);
                a0 = v0;
                jal(ctx, 0x180DECu, gen::fn_sub_17DB40_0017db40);
                if (v0 != 0) {
                    // 0x00180e1c
                    charge(ctx, 8);
                    jal(ctx, 0x180E1Cu, gen::fn_datGetTime_0016ef30);
                    a1 = v0 & 0xFF;
                    a0 = s1;
                    jal(ctx, 0x180E2Cu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                } else {
                    // 0x00180dfc
                    charge(ctx, 8);
                    jal(ctx, 0x180DFCu, gen::fn_datGetTime_0016ef30);
                    a1 = v0 & 0xFF;
                    a0 = s1;
                    jal(ctx, 0x180E0Cu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                }
            } else {
                // 0x00180dc8
                charge(ctx, 6);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x180DD0u, gen::fn_sub_181950_00181950);
            }
        }
    } else {
        // 0x00180cfc
        charge(ctx, 18);
        a0 = 0x1402;  // morning: new day done
        a1 = 1;
        jal(ctx, 0x180D04u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xBD2;  // flag 0xBD2
        a1 = 0;
        jal(ctx, 0x180D14u, gen::fn_datSetFlag_0016f1f0);
        jal(ctx, 0x180D1Cu, gen::fn_sub_27D8D0_0027d8d0);
        jal(ctx, 0x180D24u, gen::fn_sub_1FA450_001fa450);
        a0 = s1;
        jal(ctx, 0x180D30u, gen::fn_sub_17FE10_0017fe10);
        sw(zero, s0, 36);
    }
    // 0x00180e40 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00180E60 sub_180E60 -- 120 bytes; frame 0x10: ra sp+0x0
// sub_180E60 [clndClearMorningFlags]: flags 0x1402..0x1406 and 0xA00 cleared (when ASA ends).
void sub_180E60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180e60
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x1402;  // morning: new day done
    a1 = 0;
    jal(ctx, 0x180E70u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x1403;  // morning: early-morning skip target set
    a1 = 0;
    jal(ctx, 0x180E80u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x1404;  // morning flag 0x1404
    a1 = 0;
    jal(ctx, 0x180E90u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x1405;  // morning: dated conditions done
    a1 = 0;
    jal(ctx, 0x180EA0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x1406;  // morning: daily conditions done
    a1 = 0;
    jal(ctx, 0x180EB0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA00;  // end the early-morning slot
    a1 = 0;
    jal(ctx, 0x180EC0u, gen::fn_datSetFlag_0016f1f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00180EE0 sub_180EE0 -- 304 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_180EE0(task) [clndSeq_Gozen]: the forenoon slot (2, "!!!!!!!gozen seq"): day-part flag 0xA81; today's event or
// the social timer task.
void sub_180EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00180ee0
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    a0 = 0x5E0000;
    a0 = addiu(a0, 15888);  // "!!!!!!!gozen seq\n"
    jal(ctx, 0x180F00u, gen::fn_printf_005225a8);
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x180F10u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 1;
    jal(ctx, 0x180F20u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x180F30u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x180F40u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x180F50u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x180F60u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x180F70u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x180F80u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x180F88u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x00180f98
        charge(ctx, 5);
        jal(ctx, 0x180F98u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x00180fc4
            charge(ctx, 12);
            jal(ctx, 0x180FC4u, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = v0;
            jal(ctx, 0x180FD0u, gen::fn_sub_17DB40_0017db40);
            jal(ctx, 0x180FD8u, gen::fn_datGetTime_0016ef30);
            a1 = v0 & 0xFF;
            a0 = s1;
            jal(ctx, 0x180FE8u, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
            s0 = v0;
            goto L_00180ff4;
        }
        // 0x00180fac
        charge(ctx, 6);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x180FB4u, gen::fn_sub_181950_00181950);
        // 0x00180ff8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00180ff4:
    charge(ctx, 1);
    v0 = s0;
    // 0x00180ff8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181010 sub_181010 -- 340 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181010(task) [clndSeq_Hiruyasumi]: the lunch-break slot (3): day-part flag 0xA82; today's event, else the social
// timer task except on Saturdays.
void sub_181010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181010
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x181030u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x181040u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 1;
    jal(ctx, 0x181050u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x181060u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x181070u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x181080u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x181090u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x1810A0u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x1810A8u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x001810b8
        charge(ctx, 9);
        a0 = 0x5E0000;
        a0 = addiu(a0, 15920);  // "!!!!!!!hiruyasumi seq\n"
        jal(ctx, 0x1810C0u, gen::fn_printf_005225a8);
        jal(ctx, 0x1810C8u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x001810f4
            charge(ctx, 11);
            jal(ctx, 0x1810F4u, gen::fn_datGetDaysSinceApr5_0016ef20);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v1 = addiu(v0, 7);
            v0 = 7;
            div(v1, v0);
            mfhi(v1);
            v0 = 6;
            if (v1 != v0) {
                // 0x0018112c
                charge(ctx, 7);
                jal(ctx, 0x18112Cu, gen::fn_datGetTime_0016ef30);
                a1 = v0 & 0xFF;
                a0 = s0;
                jal(ctx, 0x18113Cu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                s1 = v0;
                goto L_00181148;
            }
            // 0x00181120
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x001810dc
            charge(ctx, 6);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x1810E4u, gen::fn_sub_181950_00181950);
        }
        // 0x0018114c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00181148:
    charge(ctx, 1);
    v0 = s1;
    // 0x0018114c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181170 sub_181170 -- 404 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181170(task) [clndSeq_Gogo]: the afternoon slot (4): day-part flag 0xA83; today's event, else the social timer
// task except on school Saturdays (not a holiday).
void sub_181170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181170
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x181190u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x1811A0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x1811B0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 1;
    jal(ctx, 0x1811C0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x1811D0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x1811E0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x1811F0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x181200u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x181208u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x00181218
        charge(ctx, 9);
        a0 = 0x5E0000;
        a0 = addiu(a0, 15952);  // "!!!!!!!gogo seq\n"
        jal(ctx, 0x181220u, gen::fn_printf_005225a8);
        jal(ctx, 0x181228u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x00181254
            charge(ctx, 7);
            jal(ctx, 0x181254u, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = v0;
            jal(ctx, 0x181260u, gen::fn_sub_17DB40_0017db40);
            if (v0 != 0) {
                // 0x00181270
                charge(ctx, 9);
                jal(ctx, 0x181270u, gen::fn_datGetTime_0016ef30);
                a1 = v0 & 0xFF;
                a0 = s0;
                jal(ctx, 0x181280u, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                s1 = v0;
                goto L_001812e8;
            }
            // 0x00181294
            charge(ctx, 11);
            jal(ctx, 0x181294u, gen::fn_datGetDaysSinceApr5_0016ef20);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v1 = addiu(v0, 7);
            v0 = 7;
            div(v1, v0);
            mfhi(v1);
            v0 = 6;
            if (v1 != v0) {
                // 0x001812cc
                charge(ctx, 7);
                jal(ctx, 0x1812CCu, gen::fn_datGetTime_0016ef30);
                a1 = v0 & 0xFF;
                a0 = s0;
                jal(ctx, 0x1812DCu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                s1 = v0;
                goto L_001812e8;
            }
            // 0x001812c0
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x0018123c
            charge(ctx, 6);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x181244u, gen::fn_sub_181950_00181950);
        }
        // 0x001812ec (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_001812e8:
    charge(ctx, 1);
    v0 = s1;
    // 0x001812ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181310 sub_181310 -- 284 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181310(task) [clndSeq_Houkago]: the after-school slot (5): day-part flag 0xA84; today's event or the social timer.
void sub_181310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181310
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x181330u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x181340u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x181350u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x181360u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 1;
    jal(ctx, 0x181370u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x181380u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x181390u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x1813A0u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x1813A8u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x001813b8
        charge(ctx, 9);
        a0 = 0x5E0000;
        a0 = addiu(a0, 15984);  // "!!!!!!!houkago seq\n"
        jal(ctx, 0x1813C0u, gen::fn_printf_005225a8);
        jal(ctx, 0x1813C8u, gen::fn_sub_181720_00181720);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x001813f4
            charge(ctx, 7);
            jal(ctx, 0x1813F4u, gen::fn_datGetTime_0016ef30);
            a1 = v0 & 0xFF;
            a0 = s1;
            jal(ctx, 0x181404u, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
            s0 = v0;
            goto L_00181410;
        }
        // 0x001813dc
        charge(ctx, 6);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x1813E4u, gen::fn_sub_181950_00181950);
        // 0x00181414 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00181410:
    charge(ctx, 1);
    v0 = s0;
    // 0x00181414 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181430 sub_181430 -- 324 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181430(task) [clndSeq_Yoru]: the evening slot (6): day-part flag 0xA85; with flag 0xA01 nothing (the flag is
// cleared); else today's event, or the social timer task (and 0xA01 cleared).
void sub_181430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181430
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x181450u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x181460u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x181470u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x181480u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x181490u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 1;
    jal(ctx, 0x1814A0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x1814B0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 0;
    jal(ctx, 0x1814C0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0x5E0000;
    a0 = addiu(a0, 16016);  // "!!!!!!!yoru seq\n"
    jal(ctx, 0x1814D0u, gen::fn_printf_005225a8);
    jal(ctx, 0x1814D8u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x001814e8
        charge(ctx, 6);
        a0 = 0xA01;  // end the evening slot
        jal(ctx, 0x1814ECu, gen::fn_datGetFlag_0016f190);
        v1 = 1;
        if (v0 != v1) {
            // 0x00181500
            charge(ctx, 5);
            jal(ctx, 0x181500u, gen::fn_sub_181720_00181720);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x0018152c
                charge(ctx, 7);
                jal(ctx, 0x18152Cu, gen::fn_datGetTime_0016ef30);
                a1 = v0 & 0xFF;
                a0 = s1;
                jal(ctx, 0x18153Cu, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                s0 = v0;
                goto L_00181548;
            }
            // 0x00181514
            charge(ctx, 6);
            a0 = s1;
            a1 = v0;
            jal(ctx, 0x18151Cu, gen::fn_sub_181950_00181950);
            // 0x0018155c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_00181548:
        charge(ctx, 4);
        a0 = 0xA01;  // end the evening slot
        a1 = 0;
        jal(ctx, 0x181550u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x00181558
    charge(ctx, 1);
    v0 = s0;
    // 0x0018155c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181580 sub_181580 -- 412 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181580(task, &to_dungeon) [clndSeq_DarkHour]: the Dark Hour slot (8): day-part flag 0xA87; flag 0xA05 sends the
// game to the dungeon (adminiChangeSeq(5, {1, 0})), *to_dungeon = 1; flag 0xA03 runs today's event or the social timer.
void sub_181580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181580
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    a0 = 0xA80;  // slot flag: ASA
    a1 = 0;
    jal(ctx, 0x1815A8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA81;  // slot flag: GOZEN
    a1 = 0;
    jal(ctx, 0x1815B8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA82;  // slot flag: HIRUYASUMI
    a1 = 0;
    jal(ctx, 0x1815C8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA83;  // slot flag: GOGO
    a1 = 0;
    jal(ctx, 0x1815D8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA84;  // slot flag: HOUKAGO
    a1 = 0;
    jal(ctx, 0x1815E8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA85;  // slot flag: YORU
    a1 = 0;
    jal(ctx, 0x1815F8u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA86;  // slot flag (unused)
    a1 = 0;
    jal(ctx, 0x181608u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0xA87;  // slot flag: the Dark Hour
    a1 = 1;
    jal(ctx, 0x181618u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x181620u, gen::fn_sub_16EF60_0016ef60);
    if (v0 == 0) {
        // 0x00181630
        charge(ctx, 6);
        a0 = 0xA05;  // go to the dungeon at the Dark Hour
        jal(ctx, 0x181634u, gen::fn_datGetFlag_0016f190);
        v1 = 1;
        if (v0 != v1) {
            // 0x0018168c
            charge(ctx, 6);
            a0 = 0xA03;  // a Dark Hour event pending
            jal(ctx, 0x181690u, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 != v1) {
                goto L_001816fc;
            }
            // 0x001816a4
            charge(ctx, 9);
            a0 = 0xA03;  // a Dark Hour event pending
            a1 = 0;
            jal(ctx, 0x1816ACu, gen::fn_datSetFlag_0016f1f0);
            jal(ctx, 0x1816B4u, gen::fn_sub_181720_00181720);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x001816e0
                charge(ctx, 7);
                jal(ctx, 0x1816E0u, gen::fn_datGetTime_0016ef30);
                a1 = v0 & 0xFF;
                a0 = s2;
                jal(ctx, 0x1816F0u, gen::fn_comu_CreateComuTimerProcessTask_003c1ab0);
                s0 = v0;
                goto L_001816fc;
            }
            // 0x001816c8
            charge(ctx, 6);
            a0 = s2;
            a1 = v0;
            jal(ctx, 0x1816D0u, gen::fn_sub_181950_00181950);
        } else {
            // 0x00181648
            charge(ctx, 17);
            sw(v1, sp, 0x48);
            sw(zero, sp, 0x4C);
            a0 = 5;
            a1 = addiu(sp, 0x48);
            a2 = 8;
            a3 = 0;
            jal(ctx, 0x181660u, gen::fn_adminiChangeSeq_0027c080);
            v0 = 1;
            sw(v0, s1, 0);
            a0 = 0xA05;  // go to the dungeon at the Dark Hour
            a1 = 0;
            jal(ctx, 0x181678u, gen::fn_datSetFlag_0016f1f0);
            v0 = 0;
        }
        // 0x00181700 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_001816fc:
    charge(ctx, 1);
    v0 = s0;
    // 0x00181700 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00181720 sub_181720 -- 560 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_181720 [clndFindTodaysEvent]: the scheduled-event rows of sub_3BD880 (24 bytes: +0 month, +1 day, +2 time slot,
// +4 u16 event / script id, +6 / +7 field major / minor (0xFF = a script), +8 / +9 / +10 the skip target month, day,
// slot, +11 a social link (0xFF none) whose rank must reach u16 +12, +14 / +16 flags that must be set, +18 / +20
// flags that must be clear, +22 the 'done' flag): the first row for today's date and slot whose conditions hold gets
// its done flag set and is returned ("## EXEC EVENT = %d ##"), else -1 ("## NO EVENT ##").
void sub_181720(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181720
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x18173Cu, gen::fn_sub_3BD880_003bd880);  // s2 = the scheduled-event table {rows, count}
    s2 = v0;
    s3 = 0;
    for (;;) {
        // 0x00181908
        charge(ctx, 4);
        lw(v0, s2, 4);  // table.count
        v0 = sltu(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00181754
        charge(ctx, 14);
        jal(ctx, 0x181754u, gen::fn_datGetDaysSinceApr5_0016ef20);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x181764u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
        v1 = sll(s3, 1);
        v1 = addu(v1, s3);
        s1 = sll(v1, 3);
        lw(v1, s2, 0);
        v1 = addu(v1, s1);
        lbu(v1, v1, calendar::event::kMonth);
        if (v1 == v0) {
            // 0x0018178c
            charge(ctx, 11);
            jal(ctx, 0x18178Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x18179Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
            lw(v1, s2, 0);
            s0 = addu(v1, s1);
            lbu(v1, s0, calendar::event::kDay);
            if (v1 != v0) {
                goto L_00181904;
            }
            // 0x001817b8
            charge(ctx, 6);
            lbu(s4, s0, calendar::event::kSlot);
            jal(ctx, 0x1817BCu, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            if (s4 != v0) {
                goto L_00181904;
            }
            // 0x001817d0
            charge(ctx, 4);
            s4 = 1;
            lhu(a0, s0, calendar::event::kFlagSet1);  // a flag that must be set (0 = none)
            if (a0 != 0) {
                // 0x001817e0
                charge(ctx, 4);
                jal(ctx, 0x1817E0u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x001817f0
                    charge(ctx, 1);
                    s4 = 0;
                }
            }
            // 0x001817f4
            charge(ctx, 5);
            lw(v0, s2, 0);
            v0 = addu(v0, s1);
            lhu(a0, v0, calendar::event::kFlagSet2);  // a second flag that must be set
            if (a0 != 0) {
                // 0x00181808
                charge(ctx, 4);
                jal(ctx, 0x181808u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x00181818
                    charge(ctx, 1);
                    s4 = 0;
                }
            }
            // 0x0018181c
            charge(ctx, 5);
            lw(v0, s2, 0);
            v0 = addu(v0, s1);
            lhu(a0, v0, calendar::event::kFlagClear1);  // a flag that must be clear
            if (a0 != 0) {
                // 0x00181830
                charge(ctx, 5);
                jal(ctx, 0x181830u, gen::fn_datGetFlag_0016f190);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00181844
                    charge(ctx, 1);
                    s4 = 0;
                }
            }
            // 0x00181848
            charge(ctx, 5);
            lw(v0, s2, 0);
            v0 = addu(v0, s1);
            lhu(a0, v0, calendar::event::kFlagClear2);  // a second flag that must be clear
            if (a0 != 0) {
                // 0x0018185c
                charge(ctx, 5);
                jal(ctx, 0x18185Cu, gen::fn_datGetFlag_0016f190);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00181870
                    charge(ctx, 1);
                    s4 = 0;
                }
            }
            // 0x00181874
            charge(ctx, 6);
            lw(v0, s2, 0);
            v0 = addu(v0, s1);
            lbu(a0, v0, calendar::event::kComu);  // a social link (0xFF = none)
            v0 = 255;
            if (a0 != v0) {
                // 0x0018188c
                charge(ctx, 13);
                v0 = sll(s3, 1);
                v0 = addu(v0, s3);
                s0 = sll(v0, 3);
                jal(ctx, 0x181898u, gen::fn_sub_16DBA0_0016dba0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                lw(v0, s2, 0);
                v0 = addu(v0, s0);
                lhu(v0, v0, calendar::event::kComuRank);  // the rank it must reach
                at = slt(v1, v0);
                if (at != 0) {
                    // 0x001818c0
                    charge(ctx, 1);
                    s4 = 0;
                }
            }
            // 0x001818c4
            charge(ctx, 2);
            if (s4 == 0) {
                goto L_00181904;
            }
            // 0x001818cc
            charge(ctx, 14);
            a0 = 0x5E0000;
            a0 = addiu(a0, 16048);  // "## EXEC EVENT = %d ##\n"
            a1 = s3;
            jal(ctx, 0x1818D8u, gen::fn_printf_005225a8);
            lw(v0, s2, 0);
            v0 = addu(s1, v0);
            lhu(a0, v0, calendar::event::kDoneFlag);  // datSetFlag(done, 1)
            a1 = 1;
            jal(ctx, 0x1818F0u, gen::fn_datSetFlag_0016f1f0);
            v0 = s3;
            // 0x0018192c (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00181904:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00181918
    charge(ctx, 5);
    a0 = 0x5E0000;
    a0 = addiu(a0, 16080);  // "## NO EVENT ##\n"
    jal(ctx, 0x181920u, gen::fn_printf_005225a8);
    v0 = si(-1);
    // 0x0018192c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
}

// 0x00181950 sub_181950 -- 436 bytes; frame 0x90: ra sp+0x80, s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq)
// sub_181950(task, row) [clndExecEvent]: starts event row `row`: a script (major 0xFF) through sub_3BDD60(15, id), else
// the field event k_Field_CreateFieldRootTask(task, .., id, major, minor) with the date HUD; then the time-skip
// target = the row's month / day (clndGetDaysSinceStartFromDate) and slot, enabled (sub_16F160 / 170 / 180).
void sub_181950(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181950
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    s4 = a0;
    s3 = a1;
    lw(s2, a0, calendar::task::kWork);  // s2 = the calendar task's work
    jal(ctx, 0x181978u, gen::fn_sub_3BD880_003bd880);
    s1 = v0;
    v1 = sll(s3, 1);
    v1 = addu(v1, s3);
    s0 = sll(v1, 3);
    lw(v0, v0, 0);
    a0 = addu(s0, v0);
    lbu(v1, a0, calendar::event::kMinor);  // 0xFF: a script
    v0 = 255;
    if (v1 == v0) {
        // 0x00181a58
        charge(ctx, 12);
        lhu(a1, a0, calendar::event::kId);
        a0 = 0x5E0000;
        a0 = addiu(a0, 16112);  // "Exe script = %d"
        jal(ctx, 0x181A64u, gen::fn_sub_1052B0_001052b0);
        lw(v0, s1, 0);
        v0 = addu(s0, v0);
        lhu(a1, v0, calendar::event::kId);
        a0 = 15;
        jal(ctx, 0x181A7Cu, gen::fn_sub_3BDD60_003bdd60);
        s0 = v0;
    } else {
        // 0x001819a8
        charge(ctx, 32);
        lhu(a1, a0, calendar::event::kId);
        a0 = 0x5E0000;
        a0 = addiu(a0, 16096);  // "Exe Event = %d"
        jal(ctx, 0x1819B4u, gen::fn_sub_1052B0_001052b0);
        lw(v0, s1, 0);
        sd(zero, sp, 0x0);
        sd(zero, sp, 0x8);
        v1 = addu(s0, v0);
        lhu(v0, v1, calendar::event::kId);
        sd(v0, sp, 0x10);
        lbu(v0, v1, calendar::event::kMajor);
        sd(v0, sp, 0x18);
        lbu(v0, v1, calendar::event::kMinor);
        sd(v0, sp, 0x20);
        sd(zero, sp, 0x28);
        a0 = s4;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        t2 = 0;
        t3 = 0;
        jal(ctx, 0x181A08u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
        s0 = v0;
        jal(ctx, 0x181A14u, gen::fn_datGetTime_0016ef30);
        v0 = v0 & 0xFF;
        if (v0 != 0) {
            // 0x00181a40
            charge(ctx, 6);
            lw(a0, s2, calendar::task::kDayPartsTask);
            a1 = 1;
            jal(ctx, 0x181A48u, gen::fn_sub_1848F0_001848f0);
        } else {
            // 0x00181a28
            charge(ctx, 6);
            lw(a0, s2, calendar::task::kDayPartsTask);
            a1 = 1;
            jal(ctx, 0x181A30u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
        }
    }
    // 0x00181a88
    charge(ctx, 31);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    s2 = sll(v0, 3);
    lw(v0, s1, 0);
    v0 = addu(s2, v0);
    lbu(a0, v0, calendar::event::kSkipMonth);  // the time-skip target date
    lbu(a1, v0, calendar::event::kSkipDay);
    jal(ctx, 0x181AA4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x181AB4u, gen::fn_sub_16F160_0016f160);  // [datSetDaysSkipTarget]
    lw(v0, s1, 0);
    v0 = addu(s2, v0);
    lbu(a0, v0, calendar::event::kSkipSlot);
    jal(ctx, 0x181AC8u, gen::fn_sub_16F170_0016f170);  // [datSetTimeSkipTarget]
    a0 = 1;
    jal(ctx, 0x181AD4u, gen::fn_sub_16F180_0016f180);  // [datSetSkipToTarget](1)
    v0 = s0;
    ld(ra, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    sp = addiu(sp, 0x90);
}

// 0x00181B70 sub_181B70 -- 164 bytes; frame 0x40: ra sp+0x0
// sub_181B70 [clndReturnToField]: back from the calendar: to the dungeon floor saved in counter 53 when 0x83A6F4 is
// set (adminiChangeSeq(5, {floor, 255})), else the calendar sequence ends (sub_17F8D0) and the field
// 0x83A6EC / 0x83A6F0 is entered (adminiChangeSeq(2, ..)).
void sub_181B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181b70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    v0 = 0x840000;
    lw(v0, v0, -22796);  // 0x83A6F4
    if (v0 != 0) {
        // 0x00181bd4
        charge(ctx, 12);
        a0 = 53;
        jal(ctx, 0x181BD8u, gen::fn_sub_16F380_0016f380);
        sw(v0, sp, 0x38);
        v0 = 255;
        sw(v0, sp, 0x3C);
        a0 = 5;
        a1 = addiu(sp, 0x38);
        a2 = 8;
        a3 = 0;
        jal(ctx, 0x181BFCu, gen::fn_adminiChangeSeq_0027c080);
    } else {
        // 0x00181b88
        charge(ctx, 19);
        jal(ctx, 0x181B88u, gen::fn_sub_17F8D0_0017f8d0);
        v0 = 0x840000;
        lw(v0, v0, -22804);  // 0x83A6EC
        sh(v0, sp, 0x10);
        v0 = 0x840000;
        lw(v0, v0, -22800);  // 0x83A6F0
        sh(v0, sp, 0x12);
        v0 = 255;
        sh(v0, sp, 0x14);
        sh(zero, sp, 0x18);
        a0 = 2;
        a1 = addiu(sp, 0x10);
        a2 = 28;
        a3 = 0;
        jal(ctx, 0x181BC4u, gen::fn_adminiChangeSeq_0027c080);
    }
    // 0x00181c04 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00181CC0 sub_181CC0 -- 2644 bytes; frame 0xD0: ra sp+0x90, s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq)
// sub_181CC0 [clndAigisCalendarTask_Update]: the "AigesCalenderTask" (The Answer's fixed day sequence): row
// 0x83A6F8 (sub_17D810) of the 40-byte table at 0x83AB30 ({u16 event, u8 major, u8 minor (0xFF = a script); u8
// month, day, slot; s16 flags to set[10] at +8, s16 flags to clear[6] at +0x1C}, -1 = none) sets the date and slot,
// its flags, the "Gojitsu" HUD
// (sub_188440 / sub_188420) and starts the event or script; 1 / 5 wait for it, then the next row; 9 / 10 the debug row
// picker ("SEQUENCE NUM = %3d"); with 0x7CDFFC set it returns to the field (as sub_181B70); 8 counts down, -1 at 0.
void sub_181CC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181cc0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    s0 = a0;
    lw(s4, a0, 60);
    s3 = 0x840000;
    s3 = addiu(s3, -21712);  // &0x83AB30
    lw(v0, s4, 0);
    at = sltiu(v0, 11);
    if (at != 0) {
        // 0x00181d00
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26064);  // &0x7B65D0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x181D1Cu:  // table[0]
            // 0x00181d1c
            charge(ctx, 3);
            lw(v0, gp, -19700);  // 0x7CDFFC
            if (v0 == 0) {
                // 0x00181e48
                charge(ctx, 42);
                jal(ctx, 0x181E48u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lbu(s5, v0, 4);
                jal(ctx, 0x181E64u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lbu(s2, v0, 5);
                jal(ctx, 0x181E80u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lbu(s1, v0, 6);
                a0 = s5;
                a1 = s2;
                jal(ctx, 0x181EA4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x181EB4u, gen::fn_datSetDaysSinceApr5_0016ef70);
                a0 = s1 & 0xFF;
                jal(ctx, 0x181EC0u, gen::fn_sub_16F150_0016f150);
                jal(ctx, 0x181EC8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 8);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00181ef0
                    charge(ctx, 10);
                    jal(ctx, 0x181EF0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 8);
                    a1 = 1;
                    jal(ctx, 0x181F10u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00181f18
                charge(ctx, 10);
                jal(ctx, 0x181F18u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 10);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00181f40
                    charge(ctx, 10);
                    jal(ctx, 0x181F40u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 10);
                    a1 = 1;
                    jal(ctx, 0x181F60u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00181f68
                charge(ctx, 10);
                jal(ctx, 0x181F68u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 12);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00181f90
                    charge(ctx, 10);
                    jal(ctx, 0x181F90u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 12);
                    a1 = 1;
                    jal(ctx, 0x181FB0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00181fb8
                charge(ctx, 10);
                jal(ctx, 0x181FB8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 14);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00181fe0
                    charge(ctx, 10);
                    jal(ctx, 0x181FE0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 14);
                    a1 = 1;
                    jal(ctx, 0x182000u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182008
                charge(ctx, 10);
                jal(ctx, 0x182008u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 16);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182030
                    charge(ctx, 10);
                    jal(ctx, 0x182030u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 16);
                    a1 = 1;
                    jal(ctx, 0x182050u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182058
                charge(ctx, 10);
                jal(ctx, 0x182058u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 18);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182080
                    charge(ctx, 10);
                    jal(ctx, 0x182080u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 18);
                    a1 = 1;
                    jal(ctx, 0x1820A0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x001820a8
                charge(ctx, 10);
                jal(ctx, 0x1820A8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 20);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x001820d0
                    charge(ctx, 10);
                    jal(ctx, 0x1820D0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 20);
                    a1 = 1;
                    jal(ctx, 0x1820F0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x001820f8
                charge(ctx, 10);
                jal(ctx, 0x1820F8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 22);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182120
                    charge(ctx, 10);
                    jal(ctx, 0x182120u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 22);
                    a1 = 1;
                    jal(ctx, 0x182140u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182148
                charge(ctx, 10);
                jal(ctx, 0x182148u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 24);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182170
                    charge(ctx, 10);
                    jal(ctx, 0x182170u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 24);
                    a1 = 1;
                    jal(ctx, 0x182190u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182198
                charge(ctx, 10);
                jal(ctx, 0x182198u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 26);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x001821c0
                    charge(ctx, 10);
                    jal(ctx, 0x1821C0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 26);
                    a1 = 1;
                    jal(ctx, 0x1821E0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x001821e8
                charge(ctx, 10);
                jal(ctx, 0x1821E8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 28);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182210
                    charge(ctx, 10);
                    jal(ctx, 0x182210u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 28);
                    a1 = 0;
                    jal(ctx, 0x182230u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182238
                charge(ctx, 10);
                jal(ctx, 0x182238u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 30);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182260
                    charge(ctx, 10);
                    jal(ctx, 0x182260u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 30);
                    a1 = 0;
                    jal(ctx, 0x182280u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182288
                charge(ctx, 10);
                jal(ctx, 0x182288u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 32);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x001822b0
                    charge(ctx, 10);
                    jal(ctx, 0x1822B0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 32);
                    a1 = 0;
                    jal(ctx, 0x1822D0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x001822d8
                charge(ctx, 10);
                jal(ctx, 0x1822D8u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 34);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182300
                    charge(ctx, 10);
                    jal(ctx, 0x182300u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 34);
                    a1 = 0;
                    jal(ctx, 0x182320u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182328
                charge(ctx, 10);
                jal(ctx, 0x182328u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 36);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00182350
                    charge(ctx, 10);
                    jal(ctx, 0x182350u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 36);
                    a1 = 0;
                    jal(ctx, 0x182370u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x00182378
                charge(ctx, 10);
                jal(ctx, 0x182378u, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lh(v1, v0, 38);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x001823a0
                    charge(ctx, 10);
                    jal(ctx, 0x1823A0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lh(a0, v0, 38);
                    a1 = 0;
                    jal(ctx, 0x1823C0u, gen::fn_datSetFlag_0016f1f0);
                }
                // 0x001823c8
                charge(ctx, 3);
                lw(a0, s4, 20);
                if (a0 != 0) {
                    // 0x001823f8
                    charge(ctx, 5);
                    a1 = s5;
                    a2 = s2;
                    a3 = s1;
                    jal(ctx, 0x182404u, gen::fn_sub_188420_00188420);
                } else {
                    // 0x001823d4
                    charge(ctx, 9);
                    a0 = s0;
                    a1 = s5;
                    a2 = s2;
                    a3 = s1;
                    jal(ctx, 0x1823E4u, gen::fn_sub_188440_00188440);
                    sw(v0, s4, 20);
                }
                // 0x0018240c
                charge(ctx, 10);
                jal(ctx, 0x18240Cu, gen::fn_sub_17D810_0017d810);
                v1 = sll(v0, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, s3);
                lbu(v1, v0, 3);
                v0 = 255;
                if (v1 == v0) {
                    // 0x001824d0
                    charge(ctx, 10);
                    jal(ctx, 0x1824D0u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(s3, v0);
                    lhu(a1, v0, 0);
                    a0 = 15;
                    jal(ctx, 0x1824F0u, gen::fn_sub_3BDD60_003bdd60);
                } else {
                    // 0x00182434
                    charge(ctx, 39);
                    jal(ctx, 0x182434u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(s3, v0);
                    lhu(s2, v0, 0);
                    jal(ctx, 0x182450u, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lbu(s1, v0, 2);
                    jal(ctx, 0x18246Cu, gen::fn_sub_17D810_0017d810);
                    v1 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s3);
                    lbu(v0, v0, 3);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    sd(s2, sp, 0x10);
                    sd(s1, sp, 0x18);
                    sd(v0, sp, 0x20);
                    sd(zero, sp, 0x28);
                    a0 = s0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x1824C0u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
                }
                // 0x001824f8
                charge(ctx, 5);
                sw(v0, s4, 12);
                v0 = 1;
                sw(v0, s4, 0);
            } else {
                // 0x00181d28
                charge(ctx, 20);
                jal(ctx, 0x181D28u, gen::fn_datGetDaysSinceApr5_0016ef20);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x181D38u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                s2 = v0;
                jal(ctx, 0x181D44u, gen::fn_datGetDaysSinceApr5_0016ef20);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x181D54u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                s1 = v0;
                jal(ctx, 0x181D60u, gen::fn_datGetTime_0016ef30);
                a3 = v0 & 0xFF;
                lw(a0, s4, 20);
                if (a0 != 0) {
                    // 0x00181d98
                    charge(ctx, 4);
                    a1 = s2;
                    a2 = s1;
                    jal(ctx, 0x181DA0u, gen::fn_sub_188420_00188420);
                } else {
                    // 0x00181d78
                    charge(ctx, 8);
                    a0 = s0;
                    a1 = s2;
                    a2 = s1;
                    jal(ctx, 0x181D84u, gen::fn_sub_188440_00188440);
                    sw(v0, s4, 20);
                }
                // 0x00181da8
                charge(ctx, 4);
                v0 = 0x840000;
                lw(v0, v0, -22796);  // 0x83A6F4
                if (v0 != 0) {
                    // 0x00181e04
                    charge(ctx, 12);
                    a0 = 53;
                    jal(ctx, 0x181E08u, gen::fn_sub_16F380_0016f380);
                    sw(v0, sp, 0xC0);
                    v0 = 255;
                    sw(v0, sp, 0xC4);
                    a0 = 5;
                    a1 = addiu(sp, 0xC0);
                    a2 = 8;
                    a3 = 0;
                    jal(ctx, 0x181E2Cu, gen::fn_adminiChangeSeq_0027c080);
                } else {
                    // 0x00181db8
                    charge(ctx, 19);
                    jal(ctx, 0x181DB8u, gen::fn_sub_17F8D0_0017f8d0);
                    v0 = 0x840000;
                    lw(v0, v0, -22804);  // 0x83A6EC
                    sh(v0, sp, 0xA0);
                    v0 = 0x840000;
                    lw(v0, v0, -22800);  // 0x83A6F0
                    sh(v0, sp, 0xA2);
                    v0 = 255;
                    sh(v0, sp, 0xA4);
                    sh(zero, sp, 0xA8);
                    a0 = 2;
                    a1 = addiu(sp, 0xA0);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x181DF4u, gen::fn_adminiChangeSeq_0027c080);
                }
                // 0x00181e34
                charge(ctx, 5);
                v0 = 4;
                sw(v0, s4, 0);
                sw(zero, gp, -19700);  // 0x7CDFFC
            }
        L_001826e8:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x18250Cu:  // table[1]
            // 0x0018250c
            charge(ctx, 5);
            jal(ctx, 0x18250Cu, gen::fn_sub_27C2B0_0027c2b0);
            v1 = 3;
            if (v0 != v1) {
                // 0x00182520
                charge(ctx, 5);
                jal(ctx, 0x182520u, gen::fn_sub_27C2B0_0027c2b0);
                v1 = 2;
                if (v0 == v1) {
                    goto L_00182534;
                }
                // 0x00182544
                charge(ctx, 6);
                lw(a0, s4, 12);
                jal(ctx, 0x182548u, gen::fn_kwlnTaskGetState_00195290);
                v1 = 3;
                if (v0 == v1) {
                    // 0x0018255c
                    charge(ctx, 4);
                    sw(zero, s4, 12);
                    lw(v0, s4, 16);
                    if (v0 == 0) {
                        // 0x0018257c
                        charge(ctx, 8);
                        jal(ctx, 0x18257Cu, gen::fn_sub_17D810_0017d810);
                        a0 = addiu(v0, 1);
                        jal(ctx, 0x182588u, gen::fn_sub_17D820_0017d820);
                        sw(zero, s4, 0);
                    } else {
                        // 0x0018256c
                        charge(ctx, 4);
                        v0 = 9;
                        sw(v0, s4, 0);
                    }
                }
                goto L_001826e8;
            }
        L_00182534:
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s4, 0);
            goto L_001826e8;
        case 0x18259Cu:  // table[3]
            // 0x0018259c
            charge(ctx, 4);
            v0 = 4;
            sw(v0, s4, 0);
            goto L_001826e8;
        case 0x1825ACu:  // table[5]
            // 0x001825ac
            charge(ctx, 4);
            jal(ctx, 0x1825ACu, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x001825bc
                charge(ctx, 4);
                sw(zero, s4, 12);
                lw(v0, s4, 16);
                if (v0 == 0) {
                    // 0x001825dc
                    charge(ctx, 8);
                    jal(ctx, 0x1825DCu, gen::fn_sub_17D810_0017d810);
                    a0 = addiu(v0, 1);
                    jal(ctx, 0x1825E8u, gen::fn_sub_17D820_0017d820);
                    sw(zero, s4, 0);
                } else {
                    // 0x001825cc
                    charge(ctx, 4);
                    v0 = 9;
                    sw(v0, s4, 0);
                }
            }
            goto L_001826e8;
        case 0x1825FCu:  // table[9]
            // 0x001825fc
            charge(ctx, 6);
            jal(ctx, 0x1825FCu, gen::fn_sub_1085C0_001085c0);
            v0 = 10;
            sw(v0, s4, 0);
            goto L_001826e8;
        case 0x182614u:  // table[10]
            // 0x00182614
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 == 0) {
                // 0x00182634
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2386);  // 0x7E0952
                v0 = v1 & 0x1000;
                if (v0 == 0) {
                    // 0x00182664
                    charge(ctx, 3);
                    v0 = v1 & 0x4000;
                    if (v0 != 0) {
                        // 0x00182670
                        charge(ctx, 4);
                        jal(ctx, 0x182670u, gen::fn_sub_17D810_0017d810);
                        if (v0 != 0) {
                            // 0x00182680
                            charge(ctx, 5);
                            jal(ctx, 0x182680u, gen::fn_sub_17D810_0017d810);
                            a0 = addiu(v0, -1);
                            jal(ctx, 0x18268Cu, gen::fn_sub_17D820_0017d820);
                        }
                    }
                } else {
                    // 0x00182648
                    charge(ctx, 7);
                    jal(ctx, 0x182648u, gen::fn_sub_17D810_0017d810);
                    a0 = addiu(v0, 1);
                    jal(ctx, 0x182654u, gen::fn_sub_17D820_0017d820);
                }
            } else {
                // 0x00182628
                charge(ctx, 3);
                sw(zero, s4, 0);
            }
            // 0x00182694
            charge(ctx, 13);
            v0 = 0x40000000;
            sw(v0, sp, 0xC8);
            sw(v0, sp, 0xCC);
            jal(ctx, 0x1826A0u, gen::fn_sub_17D810_0017d810);
            ld(a0, sp, 0xC8);
            a1 = 0x5E0000;
            a1 = addiu(a1, 16128);  // "SEQUENCE NUM = %3d"
            a2 = v0;
            jal(ctx, 0x1826B8u, gen::fn_sub_104D10_00104d10);
            goto L_001826e8;
        case 0x1826C8u:  // table[8]
            // 0x001826c8
            charge(ctx, 5);
            lw(v0, s4, 8);
            v0 = addiu(v0, -1);
            sw(v0, s4, 8);
            if (v0 != 0) {
                goto L_001826e8;
            }
            // 0x001826dc
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x1826E8u:  // table[2, 4, 6, 7]
            goto L_001826e8;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001826ec (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        sp = addiu(sp, 0xD0);
        return;
    }
    goto L_001826e8;
}

// 0x00182720 sub_182720 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_182720: the Aigis calendar task's destroy function (frees the work, clears 0x7CDFEC).
void sub_182720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00182720
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x182734u, v0.u());
    sw(zero, gp, -19716);  // 0x7CDFEC
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00182750 sub_182750 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_182750(parent) [clndCreateAigisCalendarTask]: the 24-byte work and the "AigesCalenderTask" (sub_181CC0 /
// sub_182720, priority 4207) in state 0; 0x7CDFEC = the task.
void sub_182750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00182750
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x182778u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00182798
        charge(ctx, 14);
        a0 = s1;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 16160);  // "AigesCalenderTask"
        a3 = 0x180000;
        a3 = addiu(a3, 7360);  // &sub_181CC0
        t0 = 0x180000;
        t0 = addiu(t0, 10016);  // &sub_182720
        t1 = s0;
        jal(ctx, 0x1827BCu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        if (s1 != 0) {
            // 0x001827dc
            charge(ctx, 6);
            sw(s1, gp, -19716);  // 0x7CDFEC
            sw(zero, s0, 0);
            a0 = s1;
            jal(ctx, 0x1827E8u, gen::fn_sub_10BDA0_0010bda0);
            v0 = s1;
        } else {
            // 0x001827d0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018278c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001827f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00182810 sub_182810 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_182810(item) [datRollItemGrade]: a random grade from the item's chance row (sub_1714B0: u8 chances at +4, +3,
// +2, +1 in percent): r = rand() % 100 -> 4, 3, 2 by cumulative chance, then 1 or 0.
void sub_182810(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00182810
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x18281Cu, gen::fn_sub_1714B0_001714b0);
    s0 = v0;
    jal(ctx, 0x182828u, gen::fn_sub_488F30_00488f30);
    v1 = 100;
    divu(v0, v1);
    mfhi(a2);
    lbu(a1, s0, 4);
    at = slt(a2, a1);
    if (at == 0) {
        // 0x00182858
        charge(ctx, 5);
        lbu(a0, s0, 3);
        v0 = addu(a0, a1);
        at = slt(a2, v0);
        if (at == 0) {
            // 0x00182878
            charge(ctx, 6);
            lbu(v1, s0, 2);
            v0 = addu(v1, a0);
            v0 = addu(a1, v0);
            at = slt(a2, v0);
            if (at == 0) {
                // 0x0018289c
                charge(ctx, 5);
                lbu(v0, s0, 1);
                v0 = addu(v0, v1);
                v0 = addu(a0, v0);
                v0 = addu(a1, v0);
                v0 = slt(a2, v0);
            } else {
                // 0x00182890
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x0018286c
            charge(ctx, 3);
            v0 = 3;
        }
    } else {
        // 0x0018284c
        charge(ctx, 3);
        v0 = 4;
    }
    // 0x001828b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001828D0 sub_1828D0 -- 892 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1828D0(id, out) [datMakeEquipEntryRandom]: fills the 20-byte EquipEntry `out` for item id (< 4000; 1 / else 0):
// weapons (< 1000) power and accuracy, armour (1000..) evasion, accessories (2000..) defense, each base * (lo + (rand %
// 100 + 1) * (hi - lo) / 100) / 100 with the grade's {lo, hi} (sub_1714D0), grade = sub_182810, effect = sub_171550;
// 3000.. ids get grade 2 and no effect.
void sub_1828D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001828d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v1 = dsll32(s1, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 4000);
    if (v0 != 0) {
        // 0x00182910
        charge(ctx, 3);
        v0 = slti(v1, 3000);
        if (v0 != 0) {
            // 0x00182948
            charge(ctx, 3);
            v0 = slti(v1, 2000);
            if (v0 != 0) {
                // 0x00182a1c
                charge(ctx, 3);
                v0 = slti(v1, 1000);
                if (v0 != 0) {
                    // 0x00182af0
                    charge(ctx, 79);
                    jal(ctx, 0x182AF0u, gen::fn_sub_170D60_00170d60);
                    s3 = v0;
                    sh(s1, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    lhu(a0, v0, 0);
                    jal(ctx, 0x182B0Cu, gen::fn_sub_182810_00182810);
                    sb(v0, s0, 8);
                    lbu(s1, s0, 8);
                    lhu(a0, s3, 10);
                    jal(ctx, 0x182B20u, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s1, 2);
                    v0 = addu(v0, v1);
                    lhu(s2, v0, 0);
                    lhu(s1, v0, 2);
                    jal(ctx, 0x182B38u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s2 & 0xFFFF;
                    v0 = s1 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s3, 8);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 10);
                    lbu(s1, s0, 8);
                    lhu(a0, s3, 14);
                    jal(ctx, 0x182B9Cu, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s1, 2);
                    v0 = addu(v0, v1);
                    lhu(s2, v0, 0);
                    lhu(s1, v0, 2);
                    jal(ctx, 0x182BB4u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s2 & 0xFFFF;
                    v0 = s1 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s3, 12);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 12);
                    lbu(a0, s0, 8);
                    lw(a1, s0, 4);
                    lhu(a2, s3, 20);
                    jal(ctx, 0x182C1Cu, gen::fn_sub_171550_00171550);
                    sb(v0, s0, 9);
                    v0 = 1;
                } else {
                    // 0x00182a28
                    charge(ctx, 50);
                    jal(ctx, 0x182A28u, gen::fn_sub_170DA0_00170da0);
                    s3 = v0;
                    sh(s1, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    lhu(a0, v0, 0);
                    jal(ctx, 0x182A44u, gen::fn_sub_182810_00182810);
                    sb(v0, s0, 8);
                    lbu(s1, s0, 8);
                    lhu(a0, s3, 10);
                    jal(ctx, 0x182A58u, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s1, 2);
                    v0 = addu(v0, v1);
                    lhu(s2, v0, 0);
                    lhu(s1, v0, 2);
                    jal(ctx, 0x182A70u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s2 & 0xFFFF;
                    v0 = s1 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s3, 8);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 14);
                    lbu(a0, s0, 8);
                    lw(a1, s0, 4);
                    lhu(a2, s3, 12);
                    jal(ctx, 0x182AD8u, gen::fn_sub_171550_00171550);
                    sb(v0, s0, 9);
                    v0 = 1;
                }
            } else {
                // 0x00182954
                charge(ctx, 50);
                jal(ctx, 0x182954u, gen::fn_sub_170DF0_00170df0);
                s3 = v0;
                sh(s1, s0, 0);
                lw(v1, v0, 4);
                sw(v1, s0, 4);
                lhu(a0, v0, 0);
                jal(ctx, 0x182970u, gen::fn_sub_182810_00182810);
                sb(v0, s0, 8);
                lbu(s1, s0, 8);
                lhu(a0, s3, 10);
                jal(ctx, 0x182984u, gen::fn_sub_1714D0_001714d0);
                v1 = sll(s1, 2);
                v0 = addu(v0, v1);
                lhu(s2, v0, 0);
                lhu(s1, v0, 2);
                jal(ctx, 0x18299Cu, gen::fn_sub_488F30_00488f30);
                a1 = 100;
                divu(v0, a1);
                mfhi(v0);
                a0 = addiu(v0, 1);
                v1 = s2 & 0xFFFF;
                v0 = s1 & 0xFFFF;
                v0 = subu(v0, v1);
                mult(v0, a0, v0);
                div(v0, a1);
                mflo(v0);
                v0 = addu(v1, v0);
                v1 = v0 & 0xFFFF;
                lhu(v0, s3, 8);
                mult(v0, v0, v1);
                div(v0, a1);
                mflo(v0);
                sh(v0, s0, 16);
                lbu(a0, s0, 8);
                lw(a1, s0, 4);
                lhu(a2, s3, 12);
                jal(ctx, 0x182A04u, gen::fn_sub_171550_00171550);
                sb(v0, s0, 9);
                v0 = 1;
            }
        } else {
            // 0x0018291c
            charge(ctx, 11);
            jal(ctx, 0x18291Cu, gen::fn_sub_170E40_00170e40);
            sh(s1, s0, 0);
            lw(v0, v0, 0);
            sw(v0, s0, 4);
            v0 = 2;
            sb(v0, s0, 8);
            sb(zero, s0, 9);
            v0 = 1;
        }
    } else {
        // 0x00182904
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00182c2c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00182C50 sub_182C50 -- 316 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_182C50(id, out) [datMakeEquipEntry]: the entry with the table's base values (grade 2, no effect).
void sub_182C50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00182c50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v1 = dsll32(s1, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 4000);
    if (v0 != 0) {
        // 0x00182c88
        charge(ctx, 3);
        v0 = slti(v1, 3000);
        if (v0 != 0) {
            // 0x00182cc0
            charge(ctx, 3);
            v0 = slti(v1, 2000);
            if (v0 != 0) {
                // 0x00182d00
                charge(ctx, 3);
                v0 = slti(v1, 1000);
                if (v0 != 0) {
                    // 0x00182d40
                    charge(ctx, 13);
                    jal(ctx, 0x182D40u, gen::fn_sub_170D60_00170d60);
                    sh(s1, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    v1 = 2;
                    sb(v1, s0, 8);
                    lhu(v1, v0, 8);
                    sh(v1, s0, 10);
                    lhu(v0, v0, 12);
                    sh(v0, s0, 12);
                    sb(zero, s0, 9);
                    v0 = 1;
                } else {
                    // 0x00182d0c
                    charge(ctx, 13);
                    jal(ctx, 0x182D0Cu, gen::fn_sub_170DA0_00170da0);
                    sh(s1, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    v1 = 2;
                    sb(v1, s0, 8);
                    lhu(v0, v0, 8);
                    sh(v0, s0, 14);
                    sb(zero, s0, 9);
                    v0 = 1;
                }
            } else {
                // 0x00182ccc
                charge(ctx, 13);
                jal(ctx, 0x182CCCu, gen::fn_sub_170DF0_00170df0);
                sh(s1, s0, 0);
                lw(v1, v0, 4);
                sw(v1, s0, 4);
                v1 = 2;
                sb(v1, s0, 8);
                lhu(v0, v0, 8);
                sh(v0, s0, 16);
                sb(zero, s0, 9);
                v0 = 1;
            }
        } else {
            // 0x00182c94
            charge(ctx, 11);
            jal(ctx, 0x182C94u, gen::fn_sub_170E40_00170e40);
            sh(s1, s0, 0);
            lw(v0, v0, 0);
            sw(v0, s0, 4);
            v0 = 2;
            sb(v0, s0, 8);
            sb(zero, s0, 9);
            v0 = 1;
        }
    } else {
        // 0x00182c7c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00182d74 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00182D90 sub_182D90 -- 812 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_182D90(id, grade, effect, out) [datMakeEquipEntryGraded]: as sub_1828D0 with the given grade and effect.
void sub_182D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00182d90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 4000);
    if (v0 != 0) {
        // 0x00182ddc
        charge(ctx, 3);
        v0 = slti(v1, 3000);
        if (v0 != 0) {
            // 0x00182e14
            charge(ctx, 3);
            v0 = slti(v1, 2000);
            if (v0 != 0) {
                // 0x00182ec8
                charge(ctx, 3);
                v0 = slti(v1, 1000);
                if (v0 != 0) {
                    // 0x00182f7c
                    charge(ctx, 71);
                    jal(ctx, 0x182F7Cu, gen::fn_sub_170D60_00170d60);
                    s4 = v0;
                    sh(s3, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    sb(s2, s0, 8);
                    lbu(s2, s0, 8);
                    lhu(a0, v0, 10);
                    jal(ctx, 0x182FA0u, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s2, 2);
                    v0 = addu(v0, v1);
                    lhu(s3, v0, 0);
                    lhu(s2, v0, 2);
                    jal(ctx, 0x182FB8u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s3 & 0xFFFF;
                    v0 = s2 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s4, 8);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 10);
                    lbu(s2, s0, 8);
                    lhu(a0, s4, 14);
                    jal(ctx, 0x18301Cu, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s2, 2);
                    v0 = addu(v0, v1);
                    lhu(s3, v0, 0);
                    lhu(s2, v0, 2);
                    jal(ctx, 0x183034u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s3 & 0xFFFF;
                    v0 = s2 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s4, 12);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 12);
                    sb(s1, s0, 9);
                    v0 = 1;
                } else {
                    // 0x00182ed4
                    charge(ctx, 42);
                    jal(ctx, 0x182ED4u, gen::fn_sub_170DA0_00170da0);
                    s4 = v0;
                    sh(s3, s0, 0);
                    lw(v1, v0, 4);
                    sw(v1, s0, 4);
                    sb(s2, s0, 8);
                    lbu(s2, s0, 8);
                    lhu(a0, v0, 10);
                    jal(ctx, 0x182EF8u, gen::fn_sub_1714D0_001714d0);
                    v1 = sll(s2, 2);
                    v0 = addu(v0, v1);
                    lhu(s3, v0, 0);
                    lhu(s2, v0, 2);
                    jal(ctx, 0x182F10u, gen::fn_sub_488F30_00488f30);
                    a1 = 100;
                    divu(v0, a1);
                    mfhi(v0);
                    a0 = addiu(v0, 1);
                    v1 = s3 & 0xFFFF;
                    v0 = s2 & 0xFFFF;
                    v0 = subu(v0, v1);
                    mult(v0, a0, v0);
                    div(v0, a1);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    v1 = v0 & 0xFFFF;
                    lhu(v0, s4, 8);
                    mult(v0, v0, v1);
                    div(v0, a1);
                    mflo(v0);
                    sh(v0, s0, 14);
                    sb(s1, s0, 9);
                    v0 = 1;
                }
            } else {
                // 0x00182e20
                charge(ctx, 42);
                jal(ctx, 0x182E20u, gen::fn_sub_170DF0_00170df0);
                s4 = v0;
                sh(s3, s0, 0);
                lw(v1, v0, 4);
                sw(v1, s0, 4);
                sb(s2, s0, 8);
                lbu(s2, s0, 8);
                lhu(a0, v0, 10);
                jal(ctx, 0x182E44u, gen::fn_sub_1714D0_001714d0);
                v1 = sll(s2, 2);
                v0 = addu(v0, v1);
                lhu(s3, v0, 0);
                lhu(s2, v0, 2);
                jal(ctx, 0x182E5Cu, gen::fn_sub_488F30_00488f30);
                a1 = 100;
                divu(v0, a1);
                mfhi(v0);
                a0 = addiu(v0, 1);
                v1 = s3 & 0xFFFF;
                v0 = s2 & 0xFFFF;
                v0 = subu(v0, v1);
                mult(v0, a0, v0);
                div(v0, a1);
                mflo(v0);
                v0 = addu(v1, v0);
                v1 = v0 & 0xFFFF;
                lhu(v0, s4, 8);
                mult(v0, v0, v1);
                div(v0, a1);
                mflo(v0);
                sh(v0, s0, 16);
                sb(s1, s0, 9);
                v0 = 1;
            }
        } else {
            // 0x00182de8
            charge(ctx, 11);
            jal(ctx, 0x182DE8u, gen::fn_sub_170E40_00170e40);
            sh(s3, s0, 0);
            lw(v0, v0, 0);
            sw(v0, s0, 4);
            v0 = 2;
            sb(v0, s0, 8);
            sb(zero, s0, 9);
            v0 = 1;
        }
    } else {
        // 0x00182dd0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00183098 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001830C0 sub_1830C0 -- 276 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1830C0(entry) [datAddEquipToStock]: stores the entry in the first free slot of the hero's 300-entry stock
// through the field setters (sub_16FEA0 ..); 1, or 0 when full.
void sub_1830C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001830c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        // 0x001831ac
        charge(ctx, 3);
        v0 = slti(s0, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001830e0
        charge(ctx, 7);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x1830E8u, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) {
            // 0x001830fc
            charge(ctx, 43);
            a0 = 1;
            a1 = s0;
            lhu(a2, s1, 0);
            jal(ctx, 0x183108u, gen::fn_sub_16FEA0_0016fea0);
            a0 = 1;
            a1 = s0;
            lw(a2, s1, 4);
            jal(ctx, 0x18311Cu, gen::fn_sub_16FF90_0016ff90);
            a0 = 1;
            a1 = s0;
            lbu(a2, s1, 8);
            jal(ctx, 0x183130u, gen::fn_sub_170080_00170080);
            a0 = 1;
            a1 = s0;
            lbu(a2, s1, 9);
            jal(ctx, 0x183144u, gen::fn_sub_170170_00170170);
            a0 = 1;
            a1 = s0;
            lhu(a2, s1, 10);
            jal(ctx, 0x183158u, gen::fn_sub_170260_00170260);
            a0 = 1;
            a1 = s0;
            lhu(a2, s1, 12);
            jal(ctx, 0x18316Cu, gen::fn_sub_170350_00170350);
            a0 = 1;
            a1 = s0;
            lhu(a2, s1, 14);
            jal(ctx, 0x183180u, gen::fn_sub_170440_00170440);
            a0 = 1;
            a1 = s0;
            lhu(a2, s1, 16);
            jal(ctx, 0x183194u, gen::fn_sub_170530_00170530);
            v0 = 1;
            // 0x001831bc (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x001831a8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001831b8
    charge(ctx, 1);
    v0 = 0;
    // 0x001831bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
}

// 0x001831E0 sub_1831E0 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1831E0(owner, i, entry) [datSetEquipEntry]: writes the eight fields of entry i of `owner`. Returns 1.
void sub_1831E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001831e0
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    a1 = s0;
    lhu(a2, a2, 0);
    jal(ctx, 0x18320Cu, gen::fn_sub_16FEA0_0016fea0);
    a0 = s2;
    a1 = s0;
    lw(a2, s1, 4);
    jal(ctx, 0x183220u, gen::fn_sub_16FF90_0016ff90);
    a0 = s2;
    a1 = s0;
    lbu(a2, s1, 8);
    jal(ctx, 0x183234u, gen::fn_sub_170080_00170080);
    a0 = s2;
    a1 = s0;
    lbu(a2, s1, 9);
    jal(ctx, 0x183248u, gen::fn_sub_170170_00170170);
    a0 = s2;
    a1 = s0;
    lhu(a2, s1, 10);
    jal(ctx, 0x18325Cu, gen::fn_sub_170260_00170260);
    a0 = s2;
    a1 = s0;
    lhu(a2, s1, 12);
    jal(ctx, 0x183270u, gen::fn_sub_170350_00170350);
    a0 = s2;
    a1 = s0;
    lhu(a2, s1, 14);
    jal(ctx, 0x183284u, gen::fn_sub_170440_00170440);
    a0 = s2;
    a1 = s0;
    lhu(a2, s1, 16);
    jal(ctx, 0x183298u, gen::fn_sub_170530_00170530);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001833E0 sub_1833E0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1833E0: the H_DayPartsPos task's destroy function (frees its work).
void sub_1833E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001833e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1833F4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00184890 sub_184890 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_184890: the H_DayPartsDraw task's destroy function: releases its sprite file (+0x198), clears 0x7CDFF0, frees
// the work.
void sub_184890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00184890
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 408);
    if (a0 != 0) {
        // 0x001848ac
        charge(ctx, 3);
        jal(ctx, 0x1848ACu, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 408);
    }
    // 0x001848b8
    charge(ctx, 11);
    sw(zero, gp, -19712);  // 0x7CDFF0
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1848C8u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00184DB0 H_DayParts_CreateTask -- 328 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_DayParts_CreateTask(parent): the day-part HUD: the "H_DayPartsDraw" task (416-byte work: +0x18 month, +0x1C day,
// +0x20 slot of now) and its "H_DayPartsPos" child (36 bytes, both x = 400.0, also 0x7CDFF8).
void H_DayParts_CreateTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00184db0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0x960000;
    s1 = addiu(s1, 388);  // &0x960184
    a0 = 1;
    a1 = 416;
    a2 = 0x40000;
    lw(v0, s1, 0);  // 0x960184
    jalr(ctx, 0x184DE0u, v0.u());
    s2 = v0;
    if (s2 != 0) {
        // 0x00184e00
        charge(ctx, 14);
        a0 = s0;
        a1 = 0x5E0000;
        a1 = addiu(a1, 16808);  // "H_DayPartsDraw"
        a2 = 7381;
        a3 = 0x180000;
        a3 = addiu(a3, 13328);  // &H_DayPartsDraw_UpdateTask
        t0 = 0x180000;
        t0 = addiu(t0, 18576);  // &sub_184890
        t1 = s2;
        jal(ctx, 0x184E24u, gen::fn_kwlnTaskCreate_00194b20);
        s0 = v0;
        if (s0 != 0) {
            // 0x00184e44
            charge(ctx, 19);
            jal(ctx, 0x184E44u, gen::fn_clndGetCurrentMonth_0017d920);
            sw(v0, s2, 24);
            jal(ctx, 0x184E50u, gen::fn_clndGetCurrentDay_0017da40);
            sw(v0, s2, 28);
            jal(ctx, 0x184E5Cu, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            sw(v0, s2, 32);
            a0 = 1;
            a1 = 36;
            a2 = 0x40000;
            lw(v0, s1, 0);
            jalr(ctx, 0x184E7Cu, v0.u());
            s1 = v0;
            if (s1 != 0) {
                // 0x00184e90
                charge(ctx, 13);
                a0 = s0;
                a1 = 0x5E0000;
                a1 = addiu(a1, 16184);  // "H_DayPartsPos"
                a2 = 7381;
                a3 = 0x180000;
                a3 = addiu(a3, 12992);  // &H_DayPartsPos_UpdateTask
                t0 = 0x180000;
                t0 = addiu(t0, 13280);  // &sub_1833E0
                t1 = s1;
                jal(ctx, 0x184EB4u, gen::fn_kwlnTaskCreate_00194b20);
                if (v0 != 0) {
                    // 0x00184ec4
                    charge(ctx, 5);
                    v0 = 0x43C80000;
                    mtc1(v0, f0);
                    sw(v0, s1, 16);
                    sw(v0, s1, 8);
                    swc1(f0, gp, -19704);  // 0x7CDFF8
                }
            }
            // 0x00184ed8
            charge(ctx, 1);
            v0 = s0;
        } else {
            // 0x00184e38
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00184df4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00184edc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00184F00 sub_184F00 -- 2352 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_184F00 [H_DayChgDraw_Update]: the date-change strip ("camp/i_date_change01.spr"; work +0x8/+0xA from month/day,
// +0x10/+0x12 the shown date, +0x14/+0x16 the target, +0xC frame): load, slide in (60 + 30 frames), then one day per
// 15 frames (the strip scrolled by 87 * sin) until the target date, hold 20 frames, the condition message
// (flag 0x141C: sub_187550) and fade out; -1 at the end.
void sub_184F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00184f00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 10);
    if (at != 0) {
        // 0x00184f2c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26368);  // &0x7B6700
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x184F48u:  // table[0]
            // 0x00184f48
            charge(ctx, 9);
            a0 = 0x5E0000;
            a0 = addiu(a0, 16832);  // "camp/i_date_change01.spr"
            jal(ctx, 0x184F50u, gen::fn_sprAddFile_00112370);
            sw(v0, s0, 4);
            v0 = 1;
            sw(v0, s0, 0);
        L_00185810:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x184F6Cu:  // table[1]
            // 0x00184f6c
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x184F70u, gen::fn_sprFileIsReady_00111f30);
            v1 = 1;
            if (v0 == v1) {
                // 0x00184f84
                charge(ctx, 9);
                sh(zero, s0, 12);
                lh(v0, s0, 8);
                sh(v0, s0, 16);
                lh(v0, s0, 10);
                sh(v0, s0, 18);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_00185810;
        case 0x184FA8u:  // table[2]
            // 0x00184fa8
            charge(ctx, 8);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 61);
            if (at == 0) {
                // 0x00184fc8
                charge(ctx, 5);
                sh(zero, s0, 12);
                v0 = 3;
                sw(v0, s0, 0);
            }
            goto L_00185810;
        case 0x184FDCu:  // table[3]
            // 0x00184fdc
            charge(ctx, 50);
            sw(zero, sp, 0x48);
            lh(v1, s0, 12);
            v0 = 30;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = lui(0xC2A0);
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            swc1(f0, sp, 0x4C);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185028u, gen::fn_sub_186100_00186100);
            sw(zero, sp, 0x48);
            lh(v1, s0, 12);
            v0 = 30;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42A00000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            swc1(f0, sp, 0x4C);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x18507Cu, gen::fn_sub_186140_00186140);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 30;
            if (v1 == v0) {
                // 0x001850a4
                charge(ctx, 5);
                sh(zero, s0, 12);
                v0 = 4;
                sw(v0, s0, 0);
            }
            goto L_00185810;
        case 0x1850B8u:  // table[4]
            // 0x001850b8
            charge(ctx, 8);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 15);
            if (at == 0) {
                // 0x00185130
                charge(ctx, 6);
                mtc1(zero, f0);
                sw(zero, sp, 0x48);
                sw(zero, sp, 0x4C);
                neg_s(f0, f0);
                swc1(f0, sp, 0x4C);
                s1 = 0;
            } else {
                // 0x001850d8
                charge(ctx, 22);
                sw(zero, sp, 0x48);
                a0 = 15;
                v1 = subu(a0, v0);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                div(v0, a0);
                mflo(v0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x4C);
                neg_s(f0, f0);
                swc1(f0, sp, 0x4C);
                v0 = sll(v1, 8);
                v0 = subu(v0, v1);
                div1(v0, a0);
                mflo1(v0);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
            }
            // 0x00185148
            charge(ctx, 53);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 16);
            jal(ctx, 0x185158u, gen::fn_sub_185980_00185980);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 16);
            jal(ctx, 0x185170u, gen::fn_sub_185AE0_00185ae0);
            lh(v0, s0, 12);
            a0 = 60;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(v0);
            s1 = dsll32(v0, 16);
            s1 = dsra32(s1, 16);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 16);
            lh(t0, s0, 10);
            jal(ctx, 0x1851B8u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            jal(ctx, 0x1851D4u, gen::fn_sub_186050_00186050);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x1851F0u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185204u, gen::fn_sub_186140_00186140);
            lh(v1, s0, 12);
            v0 = 60;
            if (v1 == v0) {
                // 0x0018521c
                charge(ctx, 5);
                sh(zero, s0, 12);
                v0 = 5;
                sw(v0, s0, 0);
            }
            goto L_00185810;
        case 0x185230u:  // table[5]
            // 0x00185230
            charge(ctx, 12);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 16);
            jal(ctx, 0x185248u, gen::fn_sub_185980_00185980);
            lh(v1, s0, 12);
            at = slti(v1, 10);
            if (at == 0) {
                // 0x00185280
                charge(ctx, 3);
                v0 = 15;
                if (v1 == v0) {
                    // 0x00185304
                    charge(ctx, 4);
                    v0 = 0x40000000;
                    sw(v0, sp, 0x4C);
                } else {
                    // 0x0018528c
                    charge(ctx, 3);
                    v0 = 14;
                    if (v1 == v0) {
                        // 0x001852f4
                        charge(ctx, 4);
                        v0 = 0x40A00000;
                        sw(v0, sp, 0x4C);
                    } else {
                        // 0x00185298
                        charge(ctx, 3);
                        v0 = 13;
                        if (v1 == v0) {
                            // 0x001852e4
                            charge(ctx, 4);
                            v0 = 0x40800000;
                            sw(v0, sp, 0x4C);
                        } else {
                            // 0x001852a4
                            charge(ctx, 3);
                            v0 = 12;
                            if (v1 == v0) {
                                // 0x001852d4
                                charge(ctx, 4);
                                v0 = 0x40400000;
                                sw(v0, sp, 0x4C);
                            } else {
                                // 0x001852b0
                                charge(ctx, 3);
                                v0 = 11;
                                if (v1 == v0) {
                                    // 0x001852c4
                                    charge(ctx, 4);
                                    v0 = 0x3F800000;
                                    sw(v0, sp, 0x4C);
                                } else {
                                    // 0x001852bc
                                    charge(ctx, 2);
                                    // 0x00185314
                                    charge(ctx, 1);
                                    sw(zero, sp, 0x4C);
                                }
                            }
                        }
                    }
                }
                // 0x00185318
                charge(ctx, 6);
                lw(a0, s0, 4);
                ld(a1, sp, 0x48);
                a2 = 0;
                lh(a3, s0, 16);
                jal(ctx, 0x185328u, gen::fn_sub_185AE0_00185ae0);
            } else {
                // 0x00185260
                charge(ctx, 8);
                lw(a0, s0, 4);
                ld(a1, sp, 0x48);
                a2 = 0;
                lh(a3, s0, 16);
                jal(ctx, 0x185270u, gen::fn_sub_185AE0_00185ae0);
            }
            // 0x00185330
            charge(ctx, 63);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 4);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 15;
            div(v1, v0);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x185394u, gen::fn_sinf_0052e878);
            v0 = 0x42AE0000;
            mtc1(v0, f1);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x48);
            neg_s(f0, f0);
            swc1(f0, sp, 0x48);
            sw(zero, sp, 0x4C);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 16);
            lh(t0, s0, 18);
            jal(ctx, 0x1853D0u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x1853ECu, gen::fn_sub_186050_00186050);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185400u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185414u, gen::fn_sub_186140_00186140);
            lh(v1, s0, 12);
            v0 = 15;
            if (v1 == v0) {
                // 0x0018542c
                charge(ctx, 12);
                lh(a0, s0, 16);
                lh(a1, s0, 18);
                jal(ctx, 0x185434u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
                s2 = v0;
                s1 = addiu(s2, 1);
                lh(a0, s0, 20);
                lh(a1, s0, 22);
                jal(ctx, 0x18544Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
                if (s1 != v0) {
                    // 0x00185470
                    charge(ctx, 11);
                    a0 = s1;
                    jal(ctx, 0x185474u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                    sh(v0, s0, 16);
                    a0 = s1;
                    jal(ctx, 0x185484u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                    sh(v0, s0, 18);
                    sh(zero, s0, 12);
                } else {
                    // 0x0018545c
                    charge(ctx, 5);
                    sh(zero, s0, 12);
                    v0 = 6;
                    sw(v0, s0, 0);
                }
            }
            goto L_00185810;
        case 0x18549Cu:  // table[6]
            // 0x0018549c
            charge(ctx, 46);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x1854B4u, gen::fn_sub_185980_00185980);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x1854CCu, gen::fn_sub_185AE0_00185ae0);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            lh(t0, s0, 22);
            jal(ctx, 0x1854E8u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185504u, gen::fn_sub_186050_00186050);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185518u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x18552Cu, gen::fn_sub_186140_00186140);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 20;
            if (v1 == v0) {
                // 0x00185554
                charge(ctx, 5);
                sh(zero, s0, 12);
                v0 = 8;
                sw(v0, s0, 0);
            }
            goto L_00185810;
        case 0x185568u:  // table[8]
            // 0x00185568
            charge(ctx, 5);
            a0 = 0x141C;  // conditions changed (the message is due)
            jal(ctx, 0x18556Cu, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x001855ac
                charge(ctx, 2);
                v0 = 7;
                sw(v0, s0, 0);
            } else {
                // 0x0018557c
                charge(ctx, 12);
                a0 = s1;
                jal(ctx, 0x185580u, gen::fn_sub_187550_00187550);
                sw(v0, s0, 24);
                v0 = 9;
                sw(v0, s0, 0);
                a0 = 0x141C;  // conditions changed (the message is due)
                a1 = 0;
                jal(ctx, 0x18559Cu, gen::fn_datSetFlag_0016f1f0);
            }
            // 0x001855b4
            charge(ctx, 42);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x1855CCu, gen::fn_sub_185980_00185980);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x1855E4u, gen::fn_sub_185AE0_00185ae0);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            lh(t0, s0, 22);
            jal(ctx, 0x185608u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185624u, gen::fn_sub_186050_00186050);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185638u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x18564Cu, gen::fn_sub_186140_00186140);
            goto L_00185810;
        case 0x18565Cu:  // table[9]
            // 0x0018565c
            charge(ctx, 6);
            lw(a0, s0, 24);
            jal(ctx, 0x185660u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x00185674
                charge(ctx, 2);
                v0 = 7;
                sw(v0, s0, 0);
            }
            // 0x0018567c
            charge(ctx, 42);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x185694u, gen::fn_sub_185980_00185980);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            jal(ctx, 0x1856ACu, gen::fn_sub_185AE0_00185ae0);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            lh(a3, s0, 20);
            lh(t0, s0, 22);
            jal(ctx, 0x1856D0u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x1856ECu, gen::fn_sub_186050_00186050);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185700u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = 0;
            jal(ctx, 0x185714u, gen::fn_sub_186140_00186140);
            goto L_00185810;
        case 0x185724u:  // table[7]
            // 0x00185724
            charge(ctx, 56);
            lh(v0, s0, 12);
            v0 = addiu(v0, 1);
            sh(v0, s0, 12);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 15;
            div(v1, v0);
            mflo(v0);
            s1 = dsll32(v0, 16);
            s1 = dsra32(s1, 16);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 20);
            jal(ctx, 0x18576Cu, gen::fn_sub_185980_00185980);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 20);
            jal(ctx, 0x185784u, gen::fn_sub_185AE0_00185ae0);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            lh(a3, s0, 20);
            lh(t0, s0, 22);
            jal(ctx, 0x1857A8u, gen::fn_H_DayChgDraw_DrawStrip_00185b40);
            sw(zero, sp, 0x4C);
            sw(zero, sp, 0x48);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            jal(ctx, 0x1857C4u, gen::fn_sub_186050_00186050);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            jal(ctx, 0x1857D8u, gen::fn_sub_186100_00186100);
            lw(a0, s0, 4);
            ld(a1, sp, 0x48);
            a2 = s1;
            jal(ctx, 0x1857ECu, gen::fn_sub_186140_00186140);
            lh(v1, s0, 12);
            v0 = 15;
            if (v1 != v0) {
                goto L_00185810;
            }
            // 0x00185804
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00185814 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    goto L_00185810;
}

// 0x00185830 sub_185830 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_185830: the h_DayChgDraw task's destroy function (sprite file +4, then the work).
void sub_185830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00185830
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x0018584c
        charge(ctx, 3);
        jal(ctx, 0x18584Cu, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 4);
    }
    // 0x00185858
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x185864u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00185880 sub_185880 -- 244 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_185880(parent, month, day, to_month, to_day) [H_DayChgDraw_Create]: the "h_DayChgDraw" task (28-byte work).
void sub_185880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00185880
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a0 = 1;
    a1 = 28;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1858C8u, v0.u());
    s5 = v0;
    if (s5 != 0) {
        // 0x001858e8
        charge(ctx, 14);
        a0 = s4;
        a1 = 0x5E0000;
        a1 = addiu(a1, 16864);  // "h_DayChgDraw"
        a2 = 6336;
        a3 = 0x180000;
        a3 = addiu(a3, 20224);  // &sub_184F00
        t0 = 0x180000;
        t0 = addiu(t0, 22576);  // &sub_185830
        t1 = s5;
        jal(ctx, 0x18590Cu, gen::fn_kwlnTaskCreate_00194b20);
        s4 = v0;
        if (s4 != 0) {
            // 0x0018592c
            charge(ctx, 8);
            sh(s3, s5, 8);
            sh(s2, s5, 10);
            sh(s1, s5, 20);
            sh(s0, s5, 22);
            a0 = 5;
            jal(ctx, 0x185940u, gen::fn_sub_108670_00108670);
            v0 = s4;
        } else {
            // 0x00185920
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001858dc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018594c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00185980 sub_185980 -- 352 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_185980(spr, pos, alpha, month): the strip's month label sprites (79 from April on, else 80; month - 1; month + 11).
void sub_185980(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00185980
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    sd(a1, sp, 0x68);
    s2 = a2;
    s1 = a3;
    lwc1(f21, sp, 0x6C);
    v0 = 289;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x68);
    add_s(f12, f1, f0);
    v0 = 0x42E00000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    at = slti(v0, 4);
    if (at == 0) {
        // 0x00185a18
        charge(ctx, 8);
        a3 = s2 & 0xFF;
        v0 = 0x42480000;
        mtc1(v0, f14);
        a0 = s0;
        a1 = s3;
        a2 = 79;
        jal(ctx, 0x185A30u, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        // 0x001859f0
        charge(ctx, 10);
        a3 = s2 & 0xFF;
        v0 = 0x42480000;
        mtc1(v0, f14);
        a0 = s0;
        a1 = s3;
        a2 = 80;
        jal(ctx, 0x185A08u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x00185a38
    charge(ctx, 42);
    v0 = 0x437B0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x68);
    add_s(f20, f1, f0);
    v0 = 0x43030000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    s1 = dsll32(s1, 16);
    s1 = dsra32(s1, 16);
    a2 = addiu(s1, -1);
    a3 = s2 & 0xFF;
    v0 = 0x42480000;
    mtc1(v0, f14);
    a0 = s0;
    a1 = s3;
    mov_s(f12, f20);
    jal(ctx, 0x185A7Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 0x43230000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a2 = addiu(s1, 11);
    a3 = s2 & 0xFF;
    v0 = 0x42480000;
    mtc1(v0, f14);
    a0 = s0;
    a1 = s3;
    mov_s(f12, f20);
    jal(ctx, 0x185AB0u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00185AE0 sub_185AE0 -- 96 bytes; frame 0x20: ra sp+0x0
// sub_185AE0(spr, pos, alpha): the strip frame sprite 78.
void sub_185AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00185ae0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sd(a1, sp, 0x18);
    v0 = 305;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x18);
    add_s(f12, f1, f0);
    v0 = 0x433C0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1C);
    add_s(f13, f1, f0);
    a3 = a2 & 0xFF;
    v0 = 0x42480000;
    mtc1(v0, f14);
    a1 = a0;
    a2 = 78;
    jal(ctx, 0x185B28u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00185B40 H_DayChgDraw_DrawStrip -- 1296 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// H_DayChgDraw_DrawStrip(spr, pos, alpha, month, day): eight day cells from three days before (month, day), 87 units
// apart: the day of month (one or two digit sprites 24..33), the weekday sprite (Sunday 40, Monday 34 .. Saturday 39)
// and the moon phase sprite 47 + clndGetMoonPhase(day); colours: holiday / Sunday red, Saturday blue, others white
// (dimmed off the centre cell).
void H_DayChgDraw_DrawStrip(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00185b40
    enter(ctx, 69);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s6 = a0;
    sd(a1, sp, 0xE8);
    sh(a2, sp, 0xE6);
    s1 = a3;
    s0 = t0;
    lwc1(f20, sp, 0xEC);
    v0 = 0x42440000;
    mtc1(v0, f12);
    v0 = 627;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    v0 = 0x433E0000;
    mtc1(v0, f14);
    a0 = si(-256);
    a1 = 30;
    a2 = a1;
    jal(ctx, 0x185BC0u, gen::fn_sub_113A30_00113a30);
    v0 = 0x42440000;
    mtc1(v0, f12);
    mtc1(zero, f13);
    v0 = 0x433E0000;
    mtc1(v0, f14);
    a0 = si(-256);
    a1 = 21;
    a2 = 30;
    jal(ctx, 0x185BE8u, gen::fn_sub_113A30_00113a30);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x185C00u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    sq(v0, sp, 0xD0);
    paddub(v1, v0, zero);
    s4 = addiu(v1, -3);
    fp = 0;
    a0 = 255;
    lh(v1, sp, 0xE6);
    // daddu v1: a 64-bit move to itself (no effect)
    v1 = subu(a0, v1);
    sq(v1, sp, 0xC0);
    v1 = 0x41880000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0xE8);
    add_s(f21, f1, f0);
    v1 = 0x43550000;
    mtc1(v1, f0);
    add_s(f20, f0, f20);
    for (;;) {
        // 0x00185ff8
        charge(ctx, 5);
        a0 = dsll32(fp, 16);
        a0 = dsra32(a0, 16);
        v1 = slti(a0, 8);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00185c54
        charge(ctx, 3);
        v1 = 3;
        if (a0 != v1) {
            // 0x00185c70
            charge(ctx, 7);
            lq(v1, sp, 0xC0);
            a0 = dsll32(v1, 16);
            a0 = dsra32(a0, 16);
            v1 = 255;
            v1 = subu(v1, a0);
            s5 = dsll32(v1, 16);
            s5 = dsra32(s5, 16);
        } else {
            // 0x00185c60
            charge(ctx, 4);
            lh(v1, sp, 0xE6);
            s5 = v1;
        }
        // 0x00185c8c
        charge(ctx, 2);
        if (i64(s4) >= 0) {
            // 0x00185c94
            charge(ctx, 16);
            v0 = 0x42AE0000;
            mtc1(v0, f2);
            mtc1(fp, f0);
            cvt_s_w(f1, f0);
            mtc1(zero, f0);
            adda_s(f0, f21);
            madd_s(f23, f2, f1);
            a0 = s4;
            jal(ctx, 0x185CBCu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
            sq(v0, sp, 0xB0);
            lq(v0, sp, 0xD0);
            if (s4 != v0) {
                // 0x00185d48
                charge(ctx, 6);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x185D50u, gen::fn_sub_17DB40_0017db40);
                if (v0 == 0) {
                    // 0x00185d74
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x185D78u, gen::fn_clndGetWeekDay_0017dae0);
                    v1 = 6;
                    if (v0 == v1) {
                        // 0x00185d94
                        charge(ctx, 5);
                        s2 = 92;
                        s1 = 114;
                        s0 = 136;
                    } else {
                        // 0x00185d8c
                        charge(ctx, 2);
                        // 0x00185da8
                        charge(ctx, 3);
                        s2 = 88;
                        s1 = 100;
                        s0 = 106;
                    }
                } else {
                    // 0x00185d60
                    charge(ctx, 5);
                    s2 = 136;
                    s1 = 92;
                    s0 = 98;
                }
            } else {
                // 0x00185cd4
                charge(ctx, 6);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x185CDCu, gen::fn_sub_17DB40_0017db40);
                if (v0 == 0) {
                    // 0x00185d00
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x185D04u, gen::fn_clndGetWeekDay_0017dae0);
                    v1 = 6;
                    if (v0 == v1) {
                        // 0x00185d20
                        charge(ctx, 5);
                        s2 = 168;
                        s1 = 170;
                        s0 = 255;
                    } else {
                        // 0x00185d18
                        charge(ctx, 2);
                        // 0x00185d34
                        charge(ctx, 5);
                        s2 = 255;
                        s1 = s2;
                        s0 = s2;
                    }
                } else {
                    // 0x00185cec
                    charge(ctx, 5);
                    s2 = 255;
                    s1 = 162;
                    s0 = 186;
                }
            }
            // 0x00185db4
            charge(ctx, 4);
            lq(v0, sp, 0xB0);
            v0 = slti(v0, 10);
            if (v0 != 0) {
                // 0x00185e70
                charge(ctx, 20);
                lq(v0, sp, 0xB0);
                a2 = addiu(v0, 24);
                v0 = 0x41C80000;
                mtc1(v0, f0);
                add_s(f12, f0, f23);
                v0 = 0x41200000;
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s5 & 0xFF;
                v0 = 0x42480000;
                mtc1(v0, f14);
                a0 = s7;
                a1 = s6;
                t0 = s2;
                t1 = s1;
                t2 = s0;
                jal(ctx, 0x185EB8u, gen::fn_sub_115BC0_00115bc0);
            } else {
                // 0x00185dc4
                charge(ctx, 43);
                v0 = 0x41200000;
                mtc1(v0, f0);
                add_s(f22, f0, f20);
                v1 = 10;
                lq(v0, sp, 0xB0);
                div(v0, v1);
                mflo(v0);
                a2 = addiu(v0, 24);
                add_s(f12, f0, f23);
                a3 = s5 & 0xFF;
                v0 = 0x42480000;
                mtc1(v0, f14);
                a0 = s7;
                a1 = s6;
                mov_s(f13, f22);
                t0 = s2;
                t1 = s1;
                t2 = s0;
                jal(ctx, 0x185E10u, gen::fn_sub_115BC0_00115bc0);
                v1 = 10;
                lq(v0, sp, 0xB0);
                div(v0, v1);
                mfhi(v0);
                a2 = addiu(v0, 24);
                v0 = 0x421C0000;
                mtc1(v0, f0);
                add_s(f12, f0, f23);
                a3 = s5 & 0xFF;
                v0 = 0x42480000;
                mtc1(v0, f14);
                a0 = s7;
                a1 = s6;
                mov_s(f13, f22);
                t0 = s2;
                t1 = s1;
                t2 = s0;
                jal(ctx, 0x185E60u, gen::fn_sub_115BC0_00115bc0);
            }
            // 0x00185ec0
            charge(ctx, 6);
            a0 = s4;
            jal(ctx, 0x185EC4u, gen::fn_clndGetWeekDay_0017dae0);
            at = sltiu(v0, 7);
            if (at != 0) {
                // 0x00185ed8
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 26416);  // &0x7B6730
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x185EF4u:  // table[0]
                    // 0x00185ef4
                    charge(ctx, 3);
                    s3 = 40;
                    break;
                case 0x185F00u:  // table[1]
                    // 0x00185f00
                    charge(ctx, 3);
                    s3 = 34;
                    break;
                case 0x185F0Cu:  // table[2]
                    // 0x00185f0c
                    charge(ctx, 3);
                    s3 = 35;
                    break;
                case 0x185F18u:  // table[3]
                    // 0x00185f18
                    charge(ctx, 3);
                    s3 = 36;
                    break;
                case 0x185F24u:  // table[4]
                    // 0x00185f24
                    charge(ctx, 3);
                    s3 = 37;
                    break;
                case 0x185F30u:  // table[5]
                    // 0x00185f30
                    charge(ctx, 3);
                    s3 = 38;
                    break;
                case 0x185F3Cu:  // table[6]
                    // 0x00185f3c
                    charge(ctx, 1);
                    s3 = 39;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x00185f40
            charge(ctx, 42);
            v0 = 0x41880000;
            mtc1(v0, f0);
            add_s(f12, f0, f23);
            v0 = 0x42340000;
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s5 & 0xFF;
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s7;
            a1 = s6;
            a2 = s3;
            t0 = s2;
            t1 = s1;
            t2 = s0;
            jal(ctx, 0x185F84u, gen::fn_sub_115BC0_00115bc0);
            a0 = s4;
            jal(ctx, 0x185F90u, gen::fn_clndGetMoonPhase_00181b50);
            v0 = v0 & 0xFF;
            a2 = addiu(v0, 47);
            v0 = 0x41C80000;
            mtc1(v0, f0);
            add_s(f12, f0, f23);
            v0 = 0x426C0000;
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s5 & 0xFF;
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s7;
            a1 = s6;
            t0 = 255;
            t1 = t0;
            t2 = t0;
            jal(ctx, 0x185FE0u, gen::fn_sub_115BC0_00115bc0);
        }
        // 0x00185fe8
        charge(ctx, 4);
        s4 = addiu(s4, 1);
        v1 = addiu(fp, 0x1);
        fp = dsll32(v1, 16);
        fp = dsra32(fp, 16);
    }
    // 0x0018600c
    charge(ctx, 17);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00186050 sub_186050 -- 172 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_186050(spr, pos, alpha): sprites 43 and 44 of the strip.
void sub_186050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00186050
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0x58);
    s1 = a2;
    lwc1(f20, sp, 0x5C);
    a3 = s1 & 0xFF;
    v0 = 0x42400000;
    mtc1(v0, f14);
    a0 = s0;
    a1 = s2;
    a2 = 43;
    lwc1(f12, sp, 0x58);
    mov_s(f13, f20);
    jal(ctx, 0x186098u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 449;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x58);
    add_s(f12, f1, f0);
    a3 = s1 & 0xFF;
    v0 = 0x42400000;
    mtc1(v0, f14);
    a0 = s0;
    a1 = s2;
    a2 = 44;
    mov_s(f13, f20);
    jal(ctx, 0x1860D4u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00186100 sub_186100 -- 64 bytes; frame 0x20: ra sp+0x0
// sub_186100(spr, pos, alpha): sprite 41 of the strip.
void sub_186100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00186100
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sd(a1, sp, 0x18);
    lwc1(f13, sp, 0x1C);
    a3 = a2 & 0xFF;
    v0 = 0x42400000;
    mtc1(v0, f14);
    a1 = a0;
    a2 = 41;
    lwc1(f12, sp, 0x18);
    jal(ctx, 0x186128u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00186140 sub_186140 -- 76 bytes; frame 0x20: ra sp+0x0
// sub_186140(spr, pos, alpha): sprite 42 of the strip.
void sub_186140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00186140
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sd(a1, sp, 0x18);
    v0 = 0x43CA0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1C);
    add_s(f13, f1, f0);
    a3 = a2 & 0xFF;
    v0 = 0x42400000;
    mtc1(v0, f14);
    a1 = a0;
    a2 = 42;
    lwc1(f12, sp, 0x18);
    jal(ctx, 0x186174u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00186190 sub_186190 -- 1880 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_186190 [H_TimeChgDraw_Update]: the time-slot change effect ("camp/time_chg.pak": work +4 sprite file, +8 from
// slot, +0xC shown slot, +0x10 target slot, +0x14 frame, +0x18 / +0x1C child tasks, +0x20 the file request): fades the
// old slot label out and the new one in (300 * sin slides); the Dark Hour (8) plays h_Time25ChgDraw (sub_1870E0);
// on slot 1 with flag 0x141C the condition message first. -1 at the end.
void sub_186190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00186190
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s1, a0, 60);
    lw(v0, s1, 0);
    at = sltiu(v0, 12);
    if (at != 0) {
        // 0x001861b8
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26448);  // &0x7B6750
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1861D4u:  // table[0]
            // 0x001861d4
            charge(ctx, 5);
            lw(a0, s1, 32);
            jal(ctx, 0x1861D8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x001861e8
                charge(ctx, 13);
                lw(a0, s1, 32);
                a1 = 0;
                a2 = addiu(sp, 0x3C);
                jal(ctx, 0x1861F4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                a0 = v0;
                jal(ctx, 0x186200u, gen::fn_sprCreateHandleFromData_00112420);
                sw(v0, s1, 4);
                v0 = 1;
                sw(v0, s1, 0);
            }
        L_001868cc:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x18621Cu:  // table[1]
            // 0x0018621c
            charge(ctx, 6);
            lw(a0, s1, 4);
            jal(ctx, 0x186220u, gen::fn_sprFileIsReady_00111f30);
            v1 = 1;
            if (v0 == v1) {
                // 0x00186234
                charge(ctx, 7);
                sw(zero, s1, 20);
                lw(v0, s1, 8);
                sw(v0, s1, 12);
                v0 = 2;
                sw(v0, s1, 0);
            }
            goto L_001868cc;
        case 0x186250u:  // table[2]
            // 0x00186250
            charge(ctx, 29);
            lw(v0, s1, 20);
            v0 = addiu(v0, 1);
            sw(v0, s1, 20);
            sw(zero, sp, 0x34);
            sw(zero, sp, 0x30);
            a0 = 5;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(v0);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x186294u, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x1862ACu, gen::fn_sub_186BD0_00186bd0);
            lw(v1, s1, 20);
            v0 = 5;
            if (v1 == v0) {
                // 0x001862c4
                charge(ctx, 5);
                sw(zero, s1, 20);
                v0 = 3;
                sw(v0, s1, 0);
            }
            goto L_001868cc;
        case 0x1862D8u:  // table[3]
            // 0x001862d8
            charge(ctx, 21);
            lw(v0, s1, 20);
            v0 = addiu(v0, 1);
            sw(v0, s1, 20);
            sw(zero, sp, 0x34);
            sw(zero, sp, 0x30);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = 0;
            jal(ctx, 0x1862FCu, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = 0;
            jal(ctx, 0x186314u, gen::fn_sub_186BD0_00186bd0);
            lw(v1, s1, 20);
            v0 = 5;
            if (v1 == v0) {
                // 0x0018632c
                charge(ctx, 7);
                sw(zero, s1, 20);
                v0 = 4;
                sw(v0, s1, 0);
                lw(v1, s1, 16);
                v0 = 8;
                if (v1 == v0) {
                    // 0x00186348
                    charge(ctx, 3);
                    sw(v0, s1, 0);
                }
            }
            goto L_001868cc;
        case 0x186354u:  // table[11]
            // 0x00186354
            charge(ctx, 20);
            sw(zero, sp, 0x34);
            sw(zero, sp, 0x30);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = 0;
            jal(ctx, 0x18636Cu, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = 0;
            jal(ctx, 0x186384u, gen::fn_sub_186BD0_00186bd0);
            lw(a0, s1, 28);
            jal(ctx, 0x186390u, gen::fn_kwlnTaskGetState_00195290);
            a0 = 3;
            if (v0 == a0) {
                // 0x001863a4
                charge(ctx, 5);
                sw(zero, s1, 20);
                lw(v1, s1, 12);
                lw(v0, s1, 16);
                if (v1 != v0) {
                    // 0x001863c8
                    charge(ctx, 3);
                    sw(a0, s1, 0);
                } else {
                    // 0x001863b8
                    charge(ctx, 4);
                    v0 = 7;
                    sw(v0, s1, 0);
                }
            }
            goto L_001868cc;
        case 0x1863D4u:  // table[4]
            // 0x001863d4
            charge(ctx, 55);
            lw(v0, s1, 20);
            v1 = addiu(v0, 1);
            sw(v1, s1, 20);
            v0 = sll(v1, 4);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x186430u, gen::fn_sinf_0052e878);
            v0 = 0x43960000;
            mtc1(v0, f1);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x30);
            sw(zero, sp, 0x34);
            lw(v1, s1, 20);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x186480u, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x186498u, gen::fn_sub_186BD0_00186bd0);
            lw(v1, s1, 20);
            v0 = 10;
            if (v1 == v0) {
                // 0x001864b0
                charge(ctx, 7);
                lw(v0, s1, 16);
                sw(v0, s1, 12);
                sw(zero, s1, 20);
                v0 = 5;
                sw(v0, s1, 0);
            }
            goto L_001868cc;
        case 0x1864CCu:  // table[5]
            // 0x001864cc
            charge(ctx, 50);
            lw(v0, s1, 20);
            v0 = addiu(v0, 1);
            sw(v0, s1, 20);
            sw(zero, sp, 0x34);
            a0 = 10;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(v0);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            v0 = sll(v1, 4);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v0 = sll(v0, 1);
            div1(v0, a0);
            mflo1(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x186548u, gen::fn_sinf_0052e878);
            v0 = lui(0xC396);
            mtc1(v0, f1);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x30);
            sw(zero, sp, 0x34);
            a2 = dsll32(s0, 16);
            a2 = dsra32(a2, 16);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            jal(ctx, 0x18657Cu, gen::fn_sub_186A40_00186a40);
            lw(v1, s1, 20);
            v0 = 10;
            if (v1 == v0) {
                // 0x00186594
                charge(ctx, 5);
                sw(zero, s1, 20);
                v0 = 6;
                sw(v0, s1, 0);
            }
            goto L_001868cc;
        case 0x1865A8u:  // table[6]
            // 0x001865a8
            charge(ctx, 15);
            lw(v0, s1, 20);
            v0 = addiu(v0, 1);
            sw(v0, s1, 20);
            sw(zero, sp, 0x34);
            sw(zero, sp, 0x30);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = 0;
            jal(ctx, 0x1865CCu, gen::fn_sub_186A40_00186a40);
            lw(v1, s1, 20);
            at = slti(v1, 10);
            if (at == 0) {
                // 0x0018662c
                charge(ctx, 6);
                lh(a3, s1, 12);
                lw(a0, s1, 4);
                ld(a1, sp, 0x30);
                a2 = 0;
                jal(ctx, 0x18663Cu, gen::fn_sub_186BD0_00186bd0);
            } else {
                // 0x001865e4
                charge(ctx, 18);
                v0 = sll(v1, 8);
                v1 = subu(v0, v1);
                v0 = 10;
                div(v1, v0);
                mflo(v0);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = 255;
                v0 = subu(v0, v1);
                a2 = dsll32(v0, 16);
                a2 = dsra32(a2, 16);
                lh(a3, s1, 12);
                lw(a0, s1, 4);
                ld(a1, sp, 0x30);
                jal(ctx, 0x18661Cu, gen::fn_sub_186BD0_00186bd0);
            }
            // 0x00186644
            charge(ctx, 4);
            lw(v1, s1, 20);
            v0 = 20;
            if (v1 == v0) {
                // 0x00186654
                charge(ctx, 5);
                sw(zero, s1, 20);
                lw(v1, s1, 12);
                lw(v0, s1, 16);
                if (v1 != v0) {
                    // 0x00186678
                    charge(ctx, 2);
                    v0 = 3;
                    sw(v0, s1, 0);
                } else {
                    // 0x00186668
                    charge(ctx, 4);
                    v0 = 7;
                    sw(v0, s1, 0);
                }
                // 0x00186680
                charge(ctx, 4);
                lw(v1, s1, 12);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00186690
                    charge(ctx, 5);
                    a0 = 0x141C;  // conditions changed (the message is due)
                    jal(ctx, 0x186694u, gen::fn_datGetFlag_0016f190);
                    if (v0 != 0) {
                        // 0x001866a4
                        charge(ctx, 8);
                        a0 = s0;
                        jal(ctx, 0x1866A8u, gen::fn_sub_187550_00187550);
                        sw(v0, s1, 28);
                        v0 = 11;
                        sw(v0, s1, 0);
                    }
                }
            }
            goto L_001868cc;
        case 0x1866C4u:  // table[7]
            // 0x001866c4
            charge(ctx, 78);
            lw(v0, s1, 20);
            v1 = addiu(v0, 1);
            sw(v1, s1, 20);
            v0 = sll(v1, 4);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x186720u, gen::fn_sinf_0052e878);
            lwc1(f1, gp, -31612);  // 0x7CB174
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x30);
            lw(v1, s1, 20);
            v0 = sll(v1, 4);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x186788u, gen::fn_sinf_0052e878);
            lwc1(f1, gp, -31608);  // 0x7CB178
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x34);
            lw(v1, s1, 20);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x1867CCu, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x1867E4u, gen::fn_sub_186BD0_00186bd0);
            lw(v1, s1, 20);
            v0 = 5;
            if (v1 != v0) {
                goto L_001868cc;
            }
            // 0x001867fc
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x186808u:  // table[8]
            // 0x00186808
            charge(ctx, 28);
            lw(v0, s1, 20);
            v1 = addiu(v0, 1);
            sw(v1, s1, 20);
            sw(zero, sp, 0x34);
            sw(zero, sp, 0x30);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x186848u, gen::fn_sub_186A40_00186a40);
            lh(a3, s1, 12);
            lw(a0, s1, 4);
            ld(a1, sp, 0x30);
            a2 = s0;
            jal(ctx, 0x186860u, gen::fn_sub_186BD0_00186bd0);
            lw(v1, s1, 20);
            v0 = 10;
            if (v1 == v0) {
                // 0x00186878
                charge(ctx, 5);
                sw(zero, s1, 20);
                v0 = 9;
                sw(v0, s1, 0);
            }
            goto L_001868cc;
        case 0x18688Cu:  // table[9]
            // 0x0018688c
            charge(ctx, 7);
            jal(ctx, 0x18688Cu, gen::fn_sub_1870E0_001870e0);
            sw(v0, s1, 24);
            v0 = 10;
            sw(v0, s1, 0);
            goto L_001868cc;
        case 0x1868A8u:  // table[10]
            // 0x001868a8
            charge(ctx, 6);
            lw(a0, s1, 24);
            jal(ctx, 0x1868ACu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                goto L_001868cc;
            }
            // 0x001868c0
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001868d0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    goto L_001868cc;
}

// 0x001868F0 sub_1868F0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1868F0: the h_TimeChgDraw task's destroy function (sprite file, the file request, the work).
void sub_1868F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001868f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x0018690c
        charge(ctx, 3);
        jal(ctx, 0x18690Cu, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 4);
    }
    // 0x00186918
    charge(ctx, 3);
    lw(a0, s0, 32);
    if (a0 != 0) {
        // 0x00186924
        charge(ctx, 3);
        jal(ctx, 0x186924u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 32);
    }
    // 0x00186930
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18693Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00186960 sub_186960 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_186960(parent, from, to) [H_TimeChgDraw_Create]: the "h_TimeChgDraw" task (36-byte work) and the request of
// "camp/time_chg.pak".
void sub_186960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00186960
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s3 = a1;
    s2 = a2;
    a0 = 1;
    a1 = 36;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x186998u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001869b8
        charge(ctx, 14);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, 16880);  // "h_TimeChgDraw"
        a2 = 6335;
        a3 = 0x180000;
        a3 = addiu(a3, 24976);  // &sub_186190
        t0 = 0x180000;
        t0 = addiu(t0, 26864);  // &sub_1868F0
        t1 = s0;
        jal(ctx, 0x1869DCu, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x001869fc
            charge(ctx, 9);
            sw(s3, s0, 8);
            sw(s2, s0, 16);
            a0 = 0x5E0000;
            a0 = addiu(a0, 16896);  // "camp/time_chg.pak"
            a1 = 1;
            jal(ctx, 0x186A10u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 32);
            v0 = s1;
        } else {
            // 0x001869f0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001869ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00186a20 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00186A40 sub_186A40 -- 396 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_186A40(spr, pos, alpha, slot): the slot label sprite: slot 0 / 7 -> 6, 1..6 -> 0..5, 8 -> 8; on a holiday or
// Sunday slots 2..5 show 7 ('holiday').
void sub_186A40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00186a40
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    sd(a1, sp, 0x78);
    s3 = a2;
    s2 = a3;
    v0 = 0x434F0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f21, f1, f0);
    v0 = 0x43370000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f20, f1, f0);
    s0 = 0;
    jal(ctx, 0x186A98u, gen::fn_clndIsHolidayOrSunday_0017dcf0);
    v1 = 1;
    if (v0 == v1) {
        // 0x00186aac
        charge(ctx, 5);
        v1 = dsll32(s2, 16);
        v1 = dsra32(v1, 16);
        v0 = 2;
        if (v1 != v0) {
            // 0x00186ac0
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                goto L_00186ae4;
            }
            // 0x00186acc
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                goto L_00186ae4;
            }
            // 0x00186ad8
            charge(ctx, 3);
            v0 = 5;
            if (v1 != v0) {
                goto L_00186af0;
            }
            goto L_00186ae4;
        }
    L_00186ae4:
        charge(ctx, 3);
        s0 = 7;
        goto L_00186b78;
    }
L_00186af0:
    charge(ctx, 5);
    v0 = dsll32(s2, 16);
    v0 = dsra32(v0, 16);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x00186b04
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26496);  // &0x7B6780
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x186B20u:  // table[1]
            // 0x00186b20
            charge(ctx, 3);
            s0 = 0;
            break;
        case 0x186B2Cu:  // table[2]
            // 0x00186b2c
            charge(ctx, 3);
            s0 = 1;
            break;
        case 0x186B38u:  // table[3]
            // 0x00186b38
            charge(ctx, 3);
            s0 = 2;
            break;
        case 0x186B44u:  // table[4]
            // 0x00186b44
            charge(ctx, 3);
            s0 = 3;
            break;
        case 0x186B50u:  // table[5]
            // 0x00186b50
            charge(ctx, 3);
            s0 = 4;
            break;
        case 0x186B5Cu:  // table[6]
            // 0x00186b5c
            charge(ctx, 3);
            s0 = 5;
            break;
        case 0x186B68u:  // table[0, 7]
            // 0x00186b68
            charge(ctx, 3);
            s0 = 6;
            break;
        case 0x186B74u:  // table[8]
            // 0x00186b74
            charge(ctx, 1);
            s0 = 8;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
L_00186b78:
    charge(ctx, 21);
    a3 = s3 & 0xFF;
    v0 = 0x42480000;
    mtc1(v0, f14);
    a0 = s1;
    a1 = s4;
    a2 = s0;
    mov_s(f12, f21);
    mov_s(f13, f20);
    jal(ctx, 0x186B98u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00186BD0 sub_186BD0 -- 384 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_186BD0(spr, pos, alpha, slot): the second label layer (10 + the same mapping, holiday 17, Dark Hour 18); nothing
// at alpha 255.
void sub_186BD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00186bd0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    sd(a1, sp, 0x68);
    s3 = a2;
    s2 = a3;
    v1 = 255;
    if (s3 != v1) {
        // 0x00186c08
        charge(ctx, 6);
        s0 = 0;
        jal(ctx, 0x186C0Cu, gen::fn_clndIsHolidayOrSunday_0017dcf0);
        v1 = 1;
        if (v0 == v1) {
            // 0x00186c20
            charge(ctx, 5);
            v1 = dsll32(s2, 16);
            v1 = dsra32(v1, 16);
            v0 = 2;
            if (v1 != v0) {
                // 0x00186c34
                charge(ctx, 3);
                v0 = 3;
                if (v1 == v0) {
                    goto L_00186c58;
                }
                // 0x00186c40
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    goto L_00186c58;
                }
                // 0x00186c4c
                charge(ctx, 3);
                v0 = 5;
                if (v1 != v0) {
                    goto L_00186c64;
                }
                goto L_00186c58;
            }
        L_00186c58:
            charge(ctx, 3);
            s0 = 17;
            goto L_00186cec;
        }
    L_00186c64:
        charge(ctx, 5);
        v0 = dsll32(s2, 16);
        v0 = dsra32(v0, 16);
        at = sltiu(v0, 9);
        if (at != 0) {
            // 0x00186c78
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 26544);  // &0x7B67B0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x186C94u:  // table[1]
                // 0x00186c94
                charge(ctx, 3);
                s0 = 10;
                break;
            case 0x186CA0u:  // table[2]
                // 0x00186ca0
                charge(ctx, 3);
                s0 = 11;
                break;
            case 0x186CACu:  // table[3]
                // 0x00186cac
                charge(ctx, 3);
                s0 = 12;
                break;
            case 0x186CB8u:  // table[4]
                // 0x00186cb8
                charge(ctx, 3);
                s0 = 13;
                break;
            case 0x186CC4u:  // table[5]
                // 0x00186cc4
                charge(ctx, 3);
                s0 = 14;
                break;
            case 0x186CD0u:  // table[6]
                // 0x00186cd0
                charge(ctx, 3);
                s0 = 15;
                break;
            case 0x186CDCu:  // table[0, 7]
                // 0x00186cdc
                charge(ctx, 3);
                s0 = 16;
                break;
            case 0x186CE8u:  // table[8]
                // 0x00186ce8
                charge(ctx, 1);
                s0 = 18;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    L_00186cec:
        charge(ctx, 16);
        v0 = 0x434F0000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        v0 = 0x43530000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x6C);
        add_s(f13, f1, f0);
        a3 = s3 & 0xFF;
        v0 = 0x42480000;
        mtc1(v0, f14);
        a0 = s1;
        a1 = s4;
        a2 = s0;
        jal(ctx, 0x186D24u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x00186d2c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00186D50 sub_186D50 -- 764 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_186D50 [H_Time25ChgDraw_Update]: the Dark Hour transition ("camp/if_t25_5a.anm" / "_5b.anm" and the event voice
// "SOUND2/EVENT/EVE_138.ADX" through the animation / sound helpers): load both, play a, then b, -1 when b ends.
void sub_186D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00186d50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v1, s0, 0);
    v0 = 4;
    if (v1 != v0) {
        // 0x00186d78
        charge(ctx, 3);
        a0 = 3;
        if (v1 == a0) {
            // 0x00186f40
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x186F44u, gen::fn_sub_111EC0_00111ec0);
            if (v0 != 0) {
                // 0x00186f54
                charge(ctx, 9);
                a0 = 7;
                jal(ctx, 0x186F58u, gen::fn_sub_108670_00108670);
                a0 = 40;
                jal(ctx, 0x186F64u, gen::fn_sub_1086A0_001086a0);
                lw(a0, s0, 12);
                if (a0 != 0) {
                    // 0x00186f78
                    charge(ctx, 3);
                    jal(ctx, 0x186F78u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    sw(zero, s0, 12);
                }
                // 0x00186f84
                charge(ctx, 8);
                lw(a0, s0, 16);
                jal(ctx, 0x186F88u, gen::fn_sub_111EE0_00111ee0);
                sw(zero, s0, 4);
                v0 = 4;
                sw(v0, s0, 0);
            }
        } else {
            // 0x00186d84
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00186e7c
                charge(ctx, 6);
                lw(v0, s0, 8);
                v1 = addiu(v0, 1);
                sw(v1, s0, 8);
                v0 = 25;
                if (v1 == v0) {
                    // 0x00186e94
                    charge(ctx, 4);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 16992);  // "SOUND2/EVENT/EVE_138.ADX"
                    jal(ctx, 0x186E9Cu, gen::fn_sub_10A370_0010a370);
                }
                // 0x00186ea4
                charge(ctx, 4);
                lw(v1, s0, 8);
                v0 = 20;
                if (v1 == v0) {
                    // 0x00186eb4
                    charge(ctx, 4);
                    jal(ctx, 0x186EB4u, gen::fn_sub_1086D0_001086d0);
                    if (v0 == 0) {
                        // 0x00186ec4
                        charge(ctx, 5);
                        jal(ctx, 0x186EC4u, gen::fn_sub_108570_00108570);
                        a0 = 5;
                        jal(ctx, 0x186ED0u, gen::fn_sub_108670_00108670);
                    }
                }
                // 0x00186ed8
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = 20;
                if (v1 != v0) {
                    // 0x00186ee8
                    charge(ctx, 2);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, 4);
                }
                // 0x00186ef0
                charge(ctx, 16);
                lwc1(f0, s0, 4);
                cvt_s_w(f1, f0);
                v0 = 0x41A00000;
                mtc1(v0, f0);
                div_s(f12, f1, f0);
                lw(a0, s0, 12);
                jal(ctx, 0x186F14u, gen::fn_sub_111D50_00111d50);
                lw(a0, s0, 12);
                jal(ctx, 0x186F20u, gen::fn_sub_111CB0_00111cb0);
                if (v0 != 0) {
                    // 0x00186f30
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x00186d90
                charge(ctx, 3);
                s1 = 1;
                if (v1 == s1) {
                    // 0x00186df4
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x00186e24
                        charge(ctx, 3);
                        v0 = slti(s2, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00186e00
                        charge(ctx, 7);
                        v0 = sll(s2, 2);
                        v0 = addu(s0, v0);
                        lw(a0, v0, 12);
                        jal(ctx, 0x186E0Cu, gen::fn_sub_111EC0_00111ec0);
                        if (v0 == 0) {
                            // 0x00186e1c
                            charge(ctx, 1);
                            s1 = 0;
                        }
                        // 0x00186e20
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x00186e30
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x00186e38
                        charge(ctx, 17);
                        lw(a0, s0, 12);
                        a1 = 1;
                        jal(ctx, 0x186E40u, gen::fn_sub_111F20_00111f20);
                        lw(a0, s0, 12);
                        jal(ctx, 0x186E4Cu, gen::fn_sub_111EE0_00111ee0);
                        sw(zero, s0, 8);
                        mtc1(zero, f12);
                        lw(a0, s0, 12);
                        jal(ctx, 0x186E60u, gen::fn_sub_111D50_00111d50);
                        sw(zero, s0, 4);
                        v0 = 2;
                        sw(v0, s0, 0);
                    }
                } else {
                    // 0x00186d9c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00186dac
                        charge(ctx, 18);
                        a0 = 0;
                        a1 = 7378;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, 16928);  // "camp/if_t25_5a.anm"
                        jal(ctx, 0x186DBCu, gen::fn_sub_111DD0_00111dd0);
                        sw(v0, s0, 12);
                        a0 = 0;
                        a1 = 7378;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, 16960);  // "camp/if_t25_5b.anm"
                        jal(ctx, 0x186DD8u, gen::fn_sub_111DD0_00111dd0);
                        sw(v0, s0, 16);
                        v0 = s1;
                        sw(v0, s0, 0);
                    } else {
                        // 0x00186da4
                        charge(ctx, 2);
                    }
                }
            }
        }
        goto L_0018702c;
    }
    // 0x00186fa4
    charge(ctx, 6);
    lw(v0, s0, 4);
    v1 = addiu(v0, 1);
    sw(v1, s0, 4);
    at = slti(v1, 41);
    if (at == 0) {
        // 0x00186fbc
        charge(ctx, 3);
        at = slti(v1, 140);
        if (at != 0) {
            // 0x00186fc8
            charge(ctx, 12);
            v0 = 0x42C80000;
            mtc1(v0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            sub_s(f0, f1, f0);
            div_s(f12, f0, f1);
            lw(a0, s0, 16);
            jal(ctx, 0x186FF0u, gen::fn_sub_111D50_00111d50);
        }
    }
    // 0x00186ff8
    charge(ctx, 6);
    lw(a0, s0, 16);
    jal(ctx, 0x186FFCu, gen::fn_kwlnTaskGetState_00195290);
    a0 = 3;
    if (v0 != a0) {
    L_0018702c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00187010
        charge(ctx, 7);
        sw(zero, s0, 16);
        a1 = 0;
        jal(ctx, 0x187018u, gen::fn_sub_109F60_00109f60);
        v0 = si(-1);
    }
    // 0x00187030 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00187050 sub_187050 -- 136 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_187050: the h_Time25ChgDraw task's destroy function (its two animation tasks, then the work).
void sub_187050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187050
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 60);
    s1 = 0;
    for (;;) {
        // 0x0018709c
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00187074
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s2, v0);
        s0 = addiu(v0, 12);
        lw(a0, v0, 12);
        if (a0 != 0) {
            // 0x0018708c
            charge(ctx, 3);
            jal(ctx, 0x18708Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, s0, 0);
        }
        // 0x00187098
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x001870a8
    charge(ctx, 12);
    a0 = s2;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1870B4u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001870E0 sub_1870E0 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1870E0(parent) [H_Time25ChgDraw_Create]: sub_108F70, the "h_Time25ChgDraw" task, flag 0x1412 set.
void sub_1870E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001870e0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x187108u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00187128
        charge(ctx, 16);
        jal(ctx, 0x187128u, gen::fn_sub_108F70_00108f70);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17024);  // "h_Time25ChgDraw"
        a2 = 6336;
        a3 = 0x180000;
        a3 = addiu(a3, 27984);  // &sub_186D50
        t0 = 0x180000;
        t0 = addiu(t0, 28752);  // &sub_187050
        t1 = s0;
        jal(ctx, 0x187154u, gen::fn_kwlnTaskCreate_00194b20);
        s0 = v0;
        if (s0 != 0) {
            // 0x00187174
            charge(ctx, 5);
            a0 = 0x1412;  // the Dark Hour effect ran
            a1 = 1;
            jal(ctx, 0x18717Cu, gen::fn_datSetFlag_0016f1f0);
            v0 = s0;
        } else {
            // 0x00187168
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018711c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00187188 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001871A0 sub_1871A0 -- 888 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1871A0 [H_ConditionHelpDraw_Update]: picks the condition message from the flags 0xA95..0xA9C, 0xA7A, 0xA9D,
// 0xA9F, 0xACD, 0xACE (the last set wins: 0..12), clears them, then shows text 0x5E4150[msg] for 90 frames (fade 10
// in / 10 out through sub_3B2CB0); -1 when none or done.
void sub_1871A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x001871a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 == v0) {
        // 0x00187438
        charge(ctx, 4);
        lw(v1, s0, 8);
        at = slti(v1, 10);
        if (at == 0) {
            // 0x00187464
            charge(ctx, 3);
            at = slti(v1, 81);
            if (at != 0) {
                // 0x00187494
                charge(ctx, 1);
                v1 = 255;
            } else {
                // 0x00187470
                charge(ctx, 9);
                v0 = 90;
                v1 = subu(v0, v1);
                v0 = sll(v1, 8);
                v1 = subu(v0, v1);
                v0 = 10;
                div(v1, v0);
                mflo(v1);
            }
        } else {
            // 0x00187448
            charge(ctx, 7);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
        }
        // 0x00187498
        charge(ctx, 23);
        mtc1(zero, f12);
        v0 = si(-256);
        a2 = v1 | v0;
        lw(v0, s0, 4);
        v1 = sll(v0, 2);
        v0 = 0x5E0000;
        v0 = addiu(v0, 16720);  // "P?^"
        v0 = addu(v0, v1);
        a0 = 320;
        a1 = 380;
        a3 = 6;
        t0 = 1;
        lw(t1, v0, 0);
        t2 = 24;
        t3 = 0;
        jal(ctx, 0x1874D4u, gen::fn_sub_3B2CB0_003b2cb0);
        lw(v0, s0, 8);
        v0 = addiu(v0, 1);
        sw(v0, s0, 8);
        v0 = slti(v0, 90);
        if (v0 != 0) {
        L_00187500:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x001874f4
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x001871c0
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x001871c8
            charge(ctx, 2);
            goto L_00187500;
        }
        // 0x001871d0
        charge(ctx, 7);
        v0 = si(-1);
        sw(v0, s0, 4);
        a0 = 0xA95;  // condition message flag
        jal(ctx, 0x1871DCu, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x001871ec
            charge(ctx, 1);
            sw(zero, s0, 4);
        }
        // 0x001871f0
        charge(ctx, 5);
        a0 = 0xA96;  // condition message flag
        jal(ctx, 0x1871F4u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187204
            charge(ctx, 2);
            v0 = 1;
            sw(v0, s0, 4);
        }
        // 0x0018720c
        charge(ctx, 5);
        a0 = 0xA97;  // condition message flag
        jal(ctx, 0x187210u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187220
            charge(ctx, 2);
            v0 = 2;
            sw(v0, s0, 4);
        }
        // 0x00187228
        charge(ctx, 5);
        a0 = 0xA98;  // condition message flag
        jal(ctx, 0x18722Cu, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x0018723c
            charge(ctx, 2);
            v0 = 3;
            sw(v0, s0, 4);
        }
        // 0x00187244
        charge(ctx, 5);
        a0 = 0xA99;  // condition message flag
        jal(ctx, 0x187248u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187258
            charge(ctx, 2);
            v0 = 4;
            sw(v0, s0, 4);
        }
        // 0x00187260
        charge(ctx, 5);
        a0 = 0xA9A;  // condition message flag
        jal(ctx, 0x187264u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187274
            charge(ctx, 2);
            v0 = 5;
            sw(v0, s0, 4);
        }
        // 0x0018727c
        charge(ctx, 5);
        a0 = 0xA7A;  // condition message 6 (forced tired)
        jal(ctx, 0x187280u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187290
            charge(ctx, 2);
            v0 = 6;
            sw(v0, s0, 4);
        }
        // 0x00187298
        charge(ctx, 5);
        a0 = 0xA9B;  // condition message flag
        jal(ctx, 0x18729Cu, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x001872ac
            charge(ctx, 2);
            v0 = 7;
            sw(v0, s0, 4);
        }
        // 0x001872b4
        charge(ctx, 5);
        a0 = 0xA9C;  // condition message flag
        jal(ctx, 0x1872B8u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x001872c8
            charge(ctx, 2);
            v0 = 8;
            sw(v0, s0, 4);
        }
        // 0x001872d0
        charge(ctx, 5);
        a0 = 0xA9D;  // condition message flag
        jal(ctx, 0x1872D4u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x001872e4
            charge(ctx, 2);
            v0 = 9;
            sw(v0, s0, 4);
        }
        // 0x001872ec
        charge(ctx, 5);
        a0 = 0xA9F;  // condition message flag
        jal(ctx, 0x1872F0u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187300
            charge(ctx, 2);
            v0 = 10;
            sw(v0, s0, 4);
        }
        // 0x00187308
        charge(ctx, 5);
        a0 = 0xACD;  // condition message flag
        jal(ctx, 0x18730Cu, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x0018731c
            charge(ctx, 2);
            v0 = 11;
            sw(v0, s0, 4);
        }
        // 0x00187324
        charge(ctx, 5);
        a0 = 0xACE;  // condition message flag
        jal(ctx, 0x187328u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x00187338
            charge(ctx, 2);
            v0 = 12;
            sw(v0, s0, 4);
        }
        // 0x00187340
        charge(ctx, 56);
        a0 = 0xA95;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187348u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA96;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187358u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA97;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187368u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA98;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187378u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA99;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187388u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA9A;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187398u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA7A;  // condition message 6 (forced tired)
        a1 = 0;
        jal(ctx, 0x1873A8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA9B;  // condition message flag
        a1 = 0;
        jal(ctx, 0x1873B8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA9C;  // condition message flag
        a1 = 0;
        jal(ctx, 0x1873C8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA9D;  // condition message flag
        a1 = 0;
        jal(ctx, 0x1873D8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xA9F;  // condition message flag
        a1 = 0;
        jal(ctx, 0x1873E8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xACD;  // condition message flag
        a1 = 0;
        jal(ctx, 0x1873F8u, gen::fn_datSetFlag_0016f1f0);
        a0 = 0xACE;  // condition message flag
        a1 = 0;
        jal(ctx, 0x187408u, gen::fn_datSetFlag_0016f1f0);
        lw(v1, s0, 4);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x00187428
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s0, 0);
            goto L_00187500;
        }
        // 0x00187420
        charge(ctx, 2);
    }
    // 0x00187504 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00187520 sub_187520 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_187520: the h_ConditionHelpDraw task's destroy function.
void sub_187520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187520
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x187534u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00187550 sub_187550 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_187550(parent) [H_ConditionHelpDraw_Create]: the "h_ConditionHelpDraw" task (12-byte work).
void sub_187550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187550
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x187574u, v0.u());
    if (v0 != 0) {
        // 0x00187590
        charge(ctx, 13);
        a0 = s0;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17040);  // "h_ConditionHelpDraw"
        a2 = 6337;
        a3 = 0x180000;
        a3 = addiu(a3, 29088);  // &sub_1871A0
        t0 = 0x180000;
        t0 = addiu(t0, 29984);  // &sub_187520
        t1 = v0;
        jal(ctx, 0x1875B4u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 == 0) {
            // 0x001875c4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00187584
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001875d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00187DF0 sub_187DF0 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_187DF0: the "NOW LOADING" moon-icon task's destroy function (sub_191A10 on its work).
void sub_187DF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187df0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    jal(ctx, 0x187DFCu, gen::fn_sub_191A10_00191a10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00187E20 sub_187E20 -- 124 bytes; frame 0x10: ra sp+0x0
// sub_187E20 [H_MoonIcon_Create]: the "NOW LOADING" task (H_MoonIcon_UpdateTask, 20-byte work from sub_191D10).
void sub_187E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187e20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 20;
    jal(ctx, 0x187E30u, gen::fn_sub_191D10_00191d10);
    if (v0 != 0) {
        // 0x00187e4c
        charge(ctx, 13);
        a0 = 0;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17080);  // "NOW LOADING"
        a2 = 7382;
        a3 = 0x180000;
        a3 = addiu(a3, 31712);  // &H_MoonIcon_UpdateTask
        t0 = 0x180000;
        t0 = addiu(t0, 32240);  // &sub_187DF0
        t1 = v0;
        jal(ctx, 0x187E70u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 == 0) {
            // 0x00187e80
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00187e40
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00187e8c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00187EC0 sub_187EC0 -- 904 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_187EC0(task, month, day, slot) [H_GojituDayParts_Draw]: the later-day HUD (The Answer): unless flag 0x141D or
// 0x1407, the frame (58), the slot colour (57: Dark Hour green, else blue) and the day label: 3/31 afternoon /
// evening / late night (slots 4 / 6 / 7) 80 / 81 / 82, 4/2 late night 83, 4/1 forenoon 84, else 85.
void sub_187EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00187ec0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    lw(s0, a0, 60);
    a0 = 0x141D;  // the calendar started
    jal(ctx, 0x187EF0u, gen::fn_datGetFlag_0016f190);
    if (v0 == 0) {
        // 0x00187f00
        charge(ctx, 5);
        a0 = 0x1407;  // flag 0x1407 (no later-day HUD)
        jal(ctx, 0x187F04u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            goto L_00187f14;
        }
        // 0x00187f1c
        charge(ctx, 19);
        v0 = 514;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -19704);  // 0x7CDFF8
        add_s(f12, f1, f0);
        v0 = 0x41B80000;
        mtc1(v0, f13);
        v0 = 0x42480000;
        mtc1(v0, f14);
        a0 = s1;
        lw(a1, s0, 16);
        a2 = 58;
        a3 = 0;
        jal(ctx, 0x187F54u, gen::fn_sprDrawSpriteBasic_001159f0);
        v0 = 8;
        if (s2 != v0) {
            // 0x00187fb4
            charge(ctx, 17);
            v0 = 0x43C30000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = lui(0xC100);
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 57;
            a3 = 0;
            t0 = 76;
            t1 = 154;
            t2 = 255;
            jal(ctx, 0x187FF0u, gen::fn_sub_115BC0_00115bc0);
        } else {
            // 0x00187f68
            charge(ctx, 19);
            v0 = 0x43C30000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = lui(0xC100);
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 57;
            a3 = 0;
            t0 = 124;
            t1 = 255;
            t2 = 144;
            jal(ctx, 0x187FA4u, gen::fn_sub_115BC0_00115bc0);
        }
        // 0x00187ff8
        charge(ctx, 3);
        v0 = 3;
        if (s4 == v0) {
            // 0x00188004
            charge(ctx, 3);
            v0 = 31;
            if (s3 != v0) {
                goto L_0018805c;
            }
            // 0x00188010
            charge(ctx, 3);
            v0 = 4;
            if (s2 != v0) {
                goto L_0018805c;
            }
            // 0x0018801c
            charge(ctx, 16);
            v0 = 0x43D00000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = 0x41600000;
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 80;
            a3 = 0;
            jal(ctx, 0x18804Cu, gen::fn_sprDrawSpriteBasic_001159f0);
            // 0x00188224 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0018805c:
        charge(ctx, 3);
        v0 = 3;
        if (s4 == v0) {
            // 0x00188068
            charge(ctx, 3);
            v0 = 31;
            if (s3 != v0) {
                goto L_001880c0;
            }
            // 0x00188074
            charge(ctx, 3);
            v0 = 6;
            if (s2 != v0) {
                goto L_001880c0;
            }
            // 0x00188080
            charge(ctx, 16);
            v0 = 0x43D00000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = 0x41600000;
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 81;
            a3 = 0;
            jal(ctx, 0x1880B0u, gen::fn_sprDrawSpriteBasic_001159f0);
            // 0x00188224 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_001880c0:
        charge(ctx, 3);
        v0 = 3;
        if (s4 == v0) {
            // 0x001880cc
            charge(ctx, 3);
            v0 = 31;
            if (s3 != v0) {
                goto L_00188124;
            }
            // 0x001880d8
            charge(ctx, 3);
            v0 = 7;
            if (s2 != v0) {
                goto L_00188124;
            }
            // 0x001880e4
            charge(ctx, 16);
            v0 = 0x43D00000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = 0x41600000;
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 82;
            a3 = 0;
            jal(ctx, 0x188114u, gen::fn_sprDrawSpriteBasic_001159f0);
            // 0x00188224 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00188124:
        charge(ctx, 3);
        v0 = 4;
        if (s4 == v0) {
            // 0x00188130
            charge(ctx, 3);
            v0 = 2;
            if (s3 != v0) {
                goto L_00188188;
            }
            // 0x0018813c
            charge(ctx, 3);
            v0 = 7;
            if (s2 != v0) {
                goto L_00188188;
            }
            // 0x00188148
            charge(ctx, 16);
            v0 = 0x43D00000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = 0x41600000;
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 83;
            a3 = 0;
            jal(ctx, 0x188178u, gen::fn_sprDrawSpriteBasic_001159f0);
            // 0x00188224 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00188188:
        charge(ctx, 3);
        v0 = 4;
        if (s4 == v0) {
            // 0x00188194
            charge(ctx, 3);
            v0 = 1;
            if (s3 != v0) {
                goto L_001881ec;
            }
            // 0x001881a0
            charge(ctx, 3);
            v0 = 2;
            if (s2 != v0) {
                goto L_001881ec;
            }
            // 0x001881ac
            charge(ctx, 16);
            v0 = 0x43D00000;
            mtc1(v0, f1);
            lwc1(f0, gp, -19704);  // 0x7CDFF8
            add_s(f12, f1, f0);
            v0 = 0x41600000;
            mtc1(v0, f13);
            v0 = 0x42480000;
            mtc1(v0, f14);
            a0 = s1;
            lw(a1, s0, 16);
            a2 = 84;
            a3 = 0;
            jal(ctx, 0x1881DCu, gen::fn_sprDrawSpriteBasic_001159f0);
            // 0x00188224 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_001881ec:
        charge(ctx, 14);
        v0 = 0x43D00000;
        mtc1(v0, f1);
        lwc1(f0, gp, -19704);  // 0x7CDFF8
        add_s(f12, f1, f0);
        v0 = 0x41600000;
        mtc1(v0, f13);
        v0 = 0x42480000;
        mtc1(v0, f14);
        a0 = s1;
        lw(a1, s0, 16);
        a2 = 85;
        a3 = 0;
        jal(ctx, 0x18821Cu, gen::fn_sprDrawSpriteBasic_001159f0);
        // 0x00188224 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_00187f14:
    charge(ctx, 2);
    // 0x00188224 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001883D0 sub_1883D0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1883D0: the GojituDayPartsDraw task's destroy function (sprite file +0x10, the work).
void sub_1883D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001883d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x001883ec
        charge(ctx, 3);
        jal(ctx, 0x1883ECu, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 16);
    }
    // 0x001883f8
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x188404u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00188440 sub_188440 -- 208 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_188440(parent, month, day, slot) [H_GojituDayParts_Create]: the "GojituDayPartsDraw" task (20-byte work).
void sub_188440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188440
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a0 = 1;
    a1 = 20;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x188480u, v0.u());
    s4 = v0;
    if (s4 != 0) {
        // 0x001884a0
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17104);  // "GojituDayPartsDraw"
        a2 = 6322;
        a3 = 0x190000;
        a3 = addiu(a3, -32176);  // &sub_188250
        t0 = 0x190000;
        t0 = addiu(t0, -31792);  // &sub_1883D0
        t1 = s4;
        jal(ctx, 0x1884C4u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x001884e0
            charge(ctx, 3);
            sw(s2, s4, 4);
            sw(s1, s4, 8);
            sw(s0, s4, 12);
        } else {
            // 0x001884d4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00188494
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001884ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00188510 sub_188510 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_188510 [clndScrCmd_SET_DATE] (a script command): date = (month, day) = scrGetIntPara(0, 1)
// (datSetDaysSinceApr5(clndGetDaysSinceStartFromDate)), time slot = scrGetIntPara(2) (sub_16F150). Returns 1.
void sub_188510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188510
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x188528u, gen::fn_scrGetIntPara_0035ed20);  // month
    s2 = v0;
    a0 = 1;
    jal(ctx, 0x188538u, gen::fn_scrGetIntPara_0035ed20);  // day of month
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x188548u, gen::fn_scrGetIntPara_0035ed20);  // time slot
    s0 = v0;
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x18855Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x18856Cu, gen::fn_datSetDaysSinceApr5_0016ef70);  // the date (and its weekday / holiday flags)
    a0 = s0 & 0xFF;
    jal(ctx, 0x188578u, gen::fn_sub_16F150_0016f150);  // [datSetTime]
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001885A0 sub_1885A0 -- 76 bytes; frame 0x10: ra sp+0x0
// sub_1885A0 (a script command): counter 53 = the current dungeon floor, 0x7CE00C = 0 and the memory-card save window
// (Y_McProc_CreateMcProcDrawTask(0, 1)) into 0x7CE000. Returns 1.
void sub_1885A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001885a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1885A8u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
    a0 = 53;
    a1 = v0;
    jal(ctx, 0x1885B8u, gen::fn_sub_16F3E0_0016f3e0);
    sw(zero, gp, -19684);  // 0x7CE00C
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x1885CCu, gen::fn_Y_McProc_CreateMcProcDrawTask_00420340);
    sw(v0, gp, -19696);  // 0x7CE000
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00188650 nullsub_5 -- 8 bytes; leaf frame (no stack)
// nullsub_5: empty (K_Field_UpdateFieldRootTask).
void nullsub_5(EEContext& ctx) {
    using namespace hg;
    // 0x00188650
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00188670 nullsub_6 -- 8 bytes; leaf frame (no stack)
// nullsub_6: empty.
void nullsub_6(EEContext& ctx) {
    using namespace hg;
    // 0x00188670
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00188680 nullsub_7 -- 8 bytes; leaf frame (no stack)
// nullsub_7: empty.
void nullsub_7(EEContext& ctx) {
    using namespace hg;
    // 0x00188680
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00188690 clndUpdateBootupCheckMemcardTask -- 408 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// clndUpdateBootupCheckMemcardTask: the boot-time memory-card check (work: +0 state, +4 result, +8 countdown,
// +0xC the message window): window message 15, 60 frames, H_Memcard_ClearChkAreaSeq, then H_Memcard_UpdateChkAreaSeq
// until it answers (100 = fine: close and -1); an error shows message 21 (result -6) or 16 and waits for the choice
// (1 = continue: close and -1, 2 = retry).
void clndUpdateBootupCheckMemcardTask(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x001886b0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26592);  // &0x7B67E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1886CCu:  // table[0]
            // 0x001886cc
            charge(ctx, 8);
            a1 = 1;
            jal(ctx, 0x1886D0u, gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0);
            sw(v0, s0, 12);
            v0 = 1;
            sw(v0, s0, 0);
        L_00188810:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1886ECu:  // table[1]
            // 0x001886ec
            charge(ctx, 10);
            lw(a0, s0, 12);
            a1 = 15;
            jal(ctx, 0x1886F4u, gen::fn_sub_4215B0_004215b0);
            v0 = 60;
            sw(v0, s0, 8);
            v0 = 2;
            sw(v0, s0, 0);
            goto L_00188810;
        case 0x188714u:  // table[2]
            // 0x00188714
            charge(ctx, 5);
            lw(v0, s0, 8);
            v0 = addiu(v0, -1);
            sw(v0, s0, 8);
            if (v0 == 0) {
                // 0x00188728
                charge(ctx, 6);
                jal(ctx, 0x188728u, gen::fn_H_Memcard_ClearChkAreaSeq_00191240);
                v0 = 3;
                sw(v0, s0, 0);
            }
            goto L_00188810;
        case 0x188740u:  // table[3]
            // 0x00188740
            charge(ctx, 5);
            jal(ctx, 0x188740u, gen::fn_H_Memcard_UpdateChkAreaSeq_00191260);
            sw(v0, s0, 4);
            if (v0 == 0) {
                goto L_00188810;
            }
            // 0x00188754
            charge(ctx, 3);
            v1 = 100;
            if (v0 != v1) {
                // 0x00188778
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, 0);
                goto L_00188810;
            }
            // 0x00188760
            charge(ctx, 6);
            lw(a0, s0, 12);
            jal(ctx, 0x188764u, gen::fn_sub_421650_00421650);
            v0 = si(-1);
            break;
        case 0x188788u:  // table[4]
            // 0x00188788
            charge(ctx, 4);
            lw(v1, s0, 4);
            v0 = si(-6);
            if (v1 != v0) {
                // 0x001887b0
                charge(ctx, 4);
                lw(a0, s0, 12);
                a1 = 16;
                jal(ctx, 0x1887B8u, gen::fn_sub_4215B0_004215b0);
            } else {
                // 0x00188798
                charge(ctx, 6);
                lw(a0, s0, 12);
                a1 = 21;
                jal(ctx, 0x1887A0u, gen::fn_sub_4215B0_004215b0);
            }
            // 0x001887c0
            charge(ctx, 4);
            v0 = 5;
            sw(v0, s0, 0);
            goto L_00188810;
        case 0x1887D0u:  // table[5]
            // 0x001887d0
            charge(ctx, 6);
            lw(a0, s0, 12);
            jal(ctx, 0x1887D4u, gen::fn_sub_421700_00421700);
            a0 = 1;
            if (v0 != a0) {
                // 0x00188800
                charge(ctx, 3);
                v1 = 2;
                if (v0 == v1) {
                    // 0x0018880c
                    charge(ctx, 1);
                    sw(a0, s0, 0);
                }
                goto L_00188810;
            }
            // 0x001887e8
            charge(ctx, 6);
            lw(a0, s0, 12);
            jal(ctx, 0x1887ECu, gen::fn_sub_421650_00421650);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00188814 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    goto L_00188810;
}

// 0x00188830 sub_188830 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_188830: the BootupCheckMemcard task's destroy function.
void sub_188830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188830
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x188844u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00188860 sub_188860 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_188860(parent) [clndCreateBootupCheckMemcardTask] (gmRoot_CreateGameRootTask): the "BootupCheckMemcard" task.
void sub_188860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 16;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x188884u, v0.u());
    if (v0 != 0) {
        // 0x001888a0
        charge(ctx, 13);
        a0 = s0;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 17136);  // "BootupCheckMemcard"
        a3 = 0x190000;
        a3 = addiu(a3, -31088);  // &clndUpdateBootupCheckMemcardTask
        t0 = 0x190000;
        t0 = addiu(t0, -30672);  // &sub_188830
        t1 = v0;
        jal(ctx, 0x1888C4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x001888d4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00188894
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001888e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00188900 sub_188900 -- 540 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_188900 [H_GameClear_Update]: the game-clear save prompt (sub_1967D0, the message window: 17, then 18 save /
// 19 skip-and-confirm; the save draws the memory-card window and loops back on failure); -1 when done.
void sub_188900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188900
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x00188928
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26624);  // &0x7B6800
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x188944u:  // table[0]
            // 0x00188944
            charge(ctx, 11);
            jal(ctx, 0x188944u, gen::fn_sub_1967D0_001967d0);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x188954u, gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0);
            sw(v0, s0, 4);
            v0 = 1;
            sw(v0, s0, 0);
        L_00188b00:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x188970u:  // table[1]
            // 0x00188970
            charge(ctx, 8);
            lw(a0, s0, 4);
            a1 = 17;
            jal(ctx, 0x188978u, gen::fn_sub_4215B0_004215b0);
            v0 = 2;
            sw(v0, s0, 0);
            goto L_00188b00;
        case 0x188990u:  // table[2]
            // 0x00188990
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x188994u, gen::fn_sub_421700_00421700);
            v1 = 1;
            if (v0 != v1) {
                // 0x001889c8
                charge(ctx, 3);
                v1 = 2;
                if (v0 == v1) {
                    // 0x001889d4
                    charge(ctx, 8);
                    lw(a0, s0, 4);
                    a1 = 19;
                    jal(ctx, 0x1889DCu, gen::fn_sub_4215B0_004215b0);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001889a8
                charge(ctx, 8);
                lw(a0, s0, 4);
                a1 = 18;
                jal(ctx, 0x1889B0u, gen::fn_sub_4215B0_004215b0);
                v0 = 4;
                sw(v0, s0, 0);
            }
            goto L_00188b00;
        case 0x1889F4u:  // table[3]
            // 0x001889f4
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x1889F8u, gen::fn_sub_421700_00421700);
            a0 = 1;
            if (v0 != a0) {
                // 0x00188a24
                charge(ctx, 3);
                v1 = 2;
                if (v0 == v1) {
                    // 0x00188a30
                    charge(ctx, 3);
                    sw(a0, s0, 0);
                }
                goto L_00188b00;
            }
            // 0x00188a0c
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x188A10u, gen::fn_sub_421650_00421650);
            v0 = si(-1);
            break;
        case 0x188A3Cu:  // table[4]
            // 0x00188a3c
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x188A40u, gen::fn_sub_421700_00421700);
            v1 = 1;
            if (v0 == v1) {
                // 0x00188a54
                charge(ctx, 13);
                lw(a0, s0, 4);
                jal(ctx, 0x188A58u, gen::fn_sub_421650_00421650);
                sw(zero, gp, -19684);  // 0x7CE00C
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x188A6Cu, gen::fn_Y_McProc_CreateMcProcDrawTask_00420340);
                sw(v0, s0, 8);
                v0 = 5;
                sw(v0, s0, 0);
            }
            goto L_00188b00;
        case 0x188A88u:  // table[5]
            // 0x00188a88
            charge(ctx, 6);
            lw(a0, s0, 8);
            jal(ctx, 0x188A8Cu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                goto L_00188b00;
            }
            // 0x00188aa0
            charge(ctx, 5);
            lw(a0, s0, 8);
            jal(ctx, 0x188AA4u, gen::fn_sub_4204F0_004204f0);
            if (v0 == 0) {
                // 0x00188ab4
                charge(ctx, 13);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x188ABCu, gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0);
                sw(v0, s0, 4);
                a0 = v0;
                a1 = 19;
                jal(ctx, 0x188AD0u, gen::fn_sub_4215B0_004215b0);
                v0 = 3;
                sw(v0, s0, 0);
                goto L_00188b00;
            }
            // 0x00188ae8
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x188AECu, gen::fn_sub_421650_00421650);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00188b04 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    goto L_00188b00;
}

// 0x00188B20 sub_188B20 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_188B20: the GameClearDraw task's destroy function.
void sub_188B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188b20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x188B34u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00188B50 sub_188B50 -- 136 bytes; frame 0x10: ra sp+0x0
// sub_188B50 [H_GameClear_Create] (a script command): the "GameClearDraw" task into 0x7CE004. Returns 1.
void sub_188B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00188b50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x188B6Cu, v0.u());
    if (v0 != 0) {
        // 0x00188b88
        charge(ctx, 13);
        a0 = 0;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 17160);  // "GameClearDraw"
        a3 = 0x190000;
        a3 = addiu(a3, -30464);  // &sub_188900
        t0 = 0x190000;
        t0 = addiu(t0, -29920);  // &sub_188B20
        t1 = v0;
        jal(ctx, 0x188BACu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x00188bbc
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x00188b7c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00188bc0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(v0, gp, -19692);  // 0x7CE004
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00188C30 sub_188C30 -- 1528 bytes; frame 0x10: ra sp+0x0
// sub_188C30: a zoom effect update (work: +0 state, +4 / +8 frame counters, +0xC target): scale 95% + 30% * t / 50
// (12-bit fixed point) through sub_1140D0, faded out after frame 39, -1 at frame 50.
void sub_188C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00188c30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v1 = addiu(v1, 1);
    sw(v1, v0, 4);
    lw(v1, v0, 8);
    v1 = addiu(v1, 1);
    sw(v1, v0, 8);
    lw(v1, v0, 0);
    at = sltiu(v1, 8);
    if (at != 0) {
        // 0x00188c64
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 26656);  // &0x7B6820
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x188C80u:  // table[0]
            // 0x00188c80
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 3;
            if (a0 == v1) {
                // 0x00188c90
                charge(ctx, 6);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                v1 = 1;
                sw(v1, v0, 0);
            }
        L_00189214:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x188CA8u:  // table[1]
            // 0x00188ca8
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 5;
            if (a0 == v1) {
                // 0x00188cb8
                charge(ctx, 4);
                v1 = 2;
                sw(v1, v0, 0);
            }
            goto L_00189214;
        case 0x188CC8u:  // table[2]
            // 0x00188cc8
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 8;
            if (a0 == v1) {
                // 0x00188cd8
                charge(ctx, 2);
                v1 = 3;
                sw(v1, v0, 0);
            }
            // 0x00188ce0
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -6);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x433E0000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40800000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x41A00000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 4);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 95);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00188d78
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00188d80
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x188D90u, gen::fn_sub_1140D0_001140d0);
            goto L_00189214;
        case 0x188DA0u:  // table[3]
            // 0x00188da0
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 10;
            if (a0 == v1) {
                // 0x00188db0
                charge(ctx, 2);
                v1 = 4;
                sw(v1, v0, 0);
            }
            // 0x00188db8
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -8);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x433D0000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40800000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x41800000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 4);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 95);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00188e50
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00188e58
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x188E68u, gen::fn_sub_1140D0_001140d0);
            goto L_00189214;
        case 0x188E78u:  // table[4]
            // 0x00188e78
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 14;
            if (a0 == v1) {
                // 0x00188e88
                charge(ctx, 2);
                v1 = 5;
                sw(v1, v0, 0);
            }
            // 0x00188e90
            charge(ctx, 41);
            lw(v1, v0, 4);
            a0 = addiu(v1, -10);
            v1 = 0x40400000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x40800000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x43390000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x41300000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x41A00000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 4);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 95);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00188f34
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00188f3c
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x188F4Cu, gen::fn_sub_1140D0_001140d0);
            goto L_00189214;
        case 0x188F5Cu:  // table[5]
            // 0x00188f5c
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 16;
            if (a0 == v1) {
                // 0x00188f6c
                charge(ctx, 2);
                v1 = 6;
                sw(v1, v0, 0);
            }
            // 0x00188f74
            charge(ctx, 38);
            lw(v1, v0, 4);
            a0 = addiu(v1, -14);
            v1 = 0x40000000;
            mtc1(v1, f3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
            mul_s(f0, f3, f2);
            div_s(f1, f0, f3);
            v1 = 0x43390000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40E00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f2);
            div_s(f1, f0, f3);
            v1 = 0x41100000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 4);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 95);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018900c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189014
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189024u, gen::fn_sub_1140D0_001140d0);
            goto L_00189214;
        case 0x189034u:  // table[6]
            // 0x00189034
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 39;
            if (a0 == v1) {
                // 0x00189044
                charge(ctx, 2);
                v1 = 7;
                sw(v1, v0, 0);
            }
            // 0x0018904c
            charge(ctx, 41);
            lw(v1, v0, 4);
            a0 = addiu(v1, -16);
            v1 = 0x42240000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x42080000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x43370000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x42480000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x41800000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 4);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 95);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x001890f0
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x001890f8
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189108u, gen::fn_sub_1140D0_001140d0);
            goto L_00189214;
        case 0x189118u:  // table[7]
            // 0x00189118
            charge(ctx, 4);
            lw(a2, v0, 4);
            a1 = 50;
            if (a2 != a1) {
                // 0x00189134
                charge(ctx, 47);
                a0 = addiu(a2, -16);
                v1 = 0x42240000;
                mtc1(v1, f1);
                mtc1(a0, f0);
                cvt_s_w(f3, f0);
                mul_s(f0, f1, f3);
                v1 = 0x42080000;
                mtc1(v1, f2);
                div_s(f1, f0, f2);
                v1 = 0x43370000;
                mtc1(v1, f0);
                sub_s(f13, f0, f1);
                v1 = 0x42480000;
                mtc1(v1, f0);
                mul_s(f0, f0, f3);
                div_s(f1, f0, f2);
                v1 = 0x41800000;
                mtc1(v1, f0);
                sub_s(f14, f0, f1);
                a0 = addiu(a2, -39);
                v1 = sll(a0, 8);
                a0 = subu(v1, a0);
                v1 = 11;
                div(a0, v1);
                mflo(a0);
                v1 = 255;
                a2 = subu(v1, a0);
                lw(a0, v0, 8);
                v1 = sll(a0, 4);
                v1 = subu(v1, a0);
                v1 = sll(v1, 1);
                div1(v1, a1);
                mflo1(v1);
                v1 = addiu(v1, 95);
                a0 = sll(v1, 12);
                v1 = 100;
                div(a0, v1);
                mflo(v1);
                v1 = sll(v1, 7);
                a1 = sra(v1, 12);
                if (i64(v1) < 0) {
                    // 0x001891f0
                    charge(ctx, 2);
                    v1 = addiu(v1, 4095);
                    a1 = sra(v1, 12);
                }
                // 0x001891f8
                charge(ctx, 7);
                mtc1(zero, f12);
                v1 = si(-256);
                a0 = a2 | v1;
                a2 = a1;
                lw(a3, v0, 12);
                jal(ctx, 0x18920Cu, gen::fn_sub_1140D0_001140d0);
                goto L_00189214;
            }
            // 0x00189128
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00189218 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_00189214;
}

// 0x00189230 sub_189230 -- 1500 bytes; frame 0x10: ra sp+0x0
// sub_189230: as sub_188C30 with scale 90% + 20% * t / 50 and longer holds.
void sub_189230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00189230
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v1 = addiu(v1, 1);
    sw(v1, v0, 4);
    lw(v1, v0, 8);
    v1 = addiu(v1, 1);
    sw(v1, v0, 8);
    lw(v1, v0, 0);
    at = sltiu(v1, 8);
    if (at != 0) {
        // 0x00189264
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 26688);  // &0x7B6840
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x189280u:  // table[0]
            // 0x00189280
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 3;
            if (a0 == v1) {
                // 0x00189290
                charge(ctx, 6);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                v1 = 1;
                sw(v1, v0, 0);
            }
        L_001897f8:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1892A8u:  // table[1]
            // 0x001892a8
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 8;
            if (a0 == v1) {
                // 0x001892b8
                charge(ctx, 4);
                v1 = 2;
                sw(v1, v0, 0);
            }
            goto L_001897f8;
        case 0x1892C8u:  // table[2]
            // 0x001892c8
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 11;
            if (a0 == v1) {
                // 0x001892d8
                charge(ctx, 2);
                v1 = 3;
                sw(v1, v0, 0);
            }
            // 0x001892e0
            charge(ctx, 41);
            lw(v1, v0, 4);
            a0 = addiu(v1, -9);
            v1 = 0x40400000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x43660000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40E00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x42B20000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189384
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018938c
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18939Cu, gen::fn_sub_1140D0_001140d0);
            goto L_001897f8;
        case 0x1893ACu:  // table[3]
            // 0x001893ac
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 13;
            if (a0 == v1) {
                // 0x001893bc
                charge(ctx, 2);
                v1 = 4;
                sw(v1, v0, 0);
            }
            // 0x001893c4
            charge(ctx, 38);
            lw(v1, v0, 4);
            a0 = addiu(v1, -11);
            v1 = 0x40000000;
            mtc1(v1, f3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
            mul_s(f0, f3, f2);
            div_s(f1, f0, f3);
            v1 = 0x43630000;
            mtc1(v1, f0);
            add_s(f13, f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f2);
            div_s(f1, f0, f3);
            v1 = 0x42A60000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018945c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189464
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189474u, gen::fn_sub_1140D0_001140d0);
            goto L_001897f8;
        case 0x189484u:  // table[4]
            // 0x00189484
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 17;
            if (a0 == v1) {
                // 0x00189494
                charge(ctx, 2);
                v1 = 5;
                sw(v1, v0, 0);
            }
            // 0x0018949c
            charge(ctx, 41);
            lw(v1, v0, 4);
            a0 = addiu(v1, -13);
            v1 = 0x40C00000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x40800000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x43650000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40E00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x42B20000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189540
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189548
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189558u, gen::fn_sub_1140D0_001140d0);
            goto L_001897f8;
        case 0x189568u:  // table[5]
            // 0x00189568
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 19;
            if (a0 == v1) {
                // 0x00189578
                charge(ctx, 2);
                v1 = 6;
                sw(v1, v0, 0);
            }
            // 0x00189580
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -17);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x435F0000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x40A00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x42A40000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189618
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189620
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189630u, gen::fn_sub_1140D0_001140d0);
            goto L_001897f8;
        case 0x189640u:  // table[6]
            // 0x00189640
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 39;
            if (a0 == v1) {
                // 0x00189650
                charge(ctx, 2);
                v1 = 7;
                sw(v1, v0, 0);
            }
            // 0x00189658
            charge(ctx, 36);
            lw(v1, v0, 4);
            a0 = addiu(v1, -19);
            v1 = 0x41880000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f0, f0);
            mul_s(f1, f1, f0);
            v1 = 0x41F80000;
            mtc1(v1, f0);
            div_s(f1, f1, f0);
            v1 = 0x435E0000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x42AE0000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x001896e8
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x001896f0
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189700u, gen::fn_sub_1140D0_001140d0);
            goto L_001897f8;
        case 0x189710u:  // table[7]
            // 0x00189710
            charge(ctx, 4);
            lw(a2, v0, 4);
            a1 = 50;
            if (a2 != a1) {
                // 0x0018972c
                charge(ctx, 42);
                a0 = addiu(a2, -19);
                v1 = 0x41880000;
                mtc1(v1, f1);
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v1 = 0x41F80000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x435E0000;
                mtc1(v1, f0);
                sub_s(f13, f0, f1);
                v1 = 0x42AE0000;
                mtc1(v1, f0);
                sub_s(f14, f0, f1);
                a0 = addiu(a2, -39);
                v1 = sll(a0, 8);
                a0 = subu(v1, a0);
                v1 = 11;
                div(a0, v1);
                mflo(a0);
                v1 = 255;
                a2 = subu(v1, a0);
                lw(a0, v0, 8);
                v1 = sll(a0, 2);
                v1 = addu(v1, a0);
                v1 = sll(v1, 2);
                div1(v1, a1);
                mflo1(v1);
                v1 = addiu(v1, 90);
                a0 = sll(v1, 12);
                v1 = 100;
                div(a0, v1);
                mflo(v1);
                v1 = sll(v1, 7);
                a1 = sra(v1, 12);
                if (i64(v1) < 0) {
                    // 0x001897d4
                    charge(ctx, 2);
                    v1 = addiu(v1, 4095);
                    a1 = sra(v1, 12);
                }
                // 0x001897dc
                charge(ctx, 7);
                mtc1(zero, f12);
                v1 = si(-256);
                a0 = a2 | v1;
                a2 = a1;
                lw(a3, v0, 12);
                jal(ctx, 0x1897F0u, gen::fn_sub_1140D0_001140d0);
                goto L_001897f8;
            }
            // 0x00189720
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x001897fc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_001897f8;
}

// 0x00189810 sub_189810 -- 1492 bytes; frame 0x10: ra sp+0x0
// sub_189810: as sub_188C30 with scale 80% + 20% * t / 50.
void sub_189810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00189810
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v1 = addiu(v1, 1);
    sw(v1, v0, 4);
    lw(v1, v0, 8);
    v1 = addiu(v1, 1);
    sw(v1, v0, 8);
    lw(v1, v0, 0);
    at = sltiu(v1, 8);
    if (at != 0) {
        // 0x00189844
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 26720);  // &0x7B6860
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x189860u:  // table[0]
            // 0x00189860
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 3;
            if (a0 == v1) {
                // 0x00189870
                charge(ctx, 6);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                v1 = 1;
                sw(v1, v0, 0);
            }
        L_00189dd0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x189888u:  // table[1]
            // 0x00189888
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 11;
            if (a0 == v1) {
                // 0x00189898
                charge(ctx, 4);
                v1 = 2;
                sw(v1, v0, 0);
            }
            goto L_00189dd0;
        case 0x1898A8u:  // table[2]
            // 0x001898a8
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 14;
            if (a0 == v1) {
                // 0x001898b8
                charge(ctx, 2);
                v1 = 3;
                sw(v1, v0, 0);
            }
            // 0x001898c0
            charge(ctx, 39);
            lw(v1, v0, 4);
            v1 = addiu(v1, -12);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 311;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x40E00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x42FA0000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 80);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018995c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189964
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189974u, gen::fn_sub_1140D0_001140d0);
            goto L_00189dd0;
        case 0x189984u:  // table[3]
            // 0x00189984
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 16;
            if (a0 == v1) {
                // 0x00189994
                charge(ctx, 2);
                v1 = 4;
                sw(v1, v0, 0);
            }
            // 0x0018999c
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -14);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x439C0000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x41200000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x43040000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 80);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189a34
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189a3c
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189A4Cu, gen::fn_sub_1140D0_001140d0);
            goto L_00189dd0;
        case 0x189A5Cu:  // table[4]
            // 0x00189a5c
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 20;
            if (a0 == v1) {
                // 0x00189a6c
                charge(ctx, 2);
                v1 = 5;
                sw(v1, v0, 0);
            }
            // 0x00189a74
            charge(ctx, 39);
            lw(v1, v0, 4);
            v1 = addiu(v1, -16);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40800000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 311;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            sub_s(f13, f0, f1);
            v1 = 0x41100000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x42F40000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 80);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189b10
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189b18
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189B28u, gen::fn_sub_1140D0_001140d0);
            goto L_00189dd0;
        case 0x189B38u:  // table[5]
            // 0x00189b38
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 22;
            if (a0 == v1) {
                // 0x00189b48
                charge(ctx, 2);
                v1 = 6;
                sw(v1, v0, 0);
            }
            // 0x00189b50
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -20);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x439B0000;
            mtc1(v1, f0);
            add_s(f13, f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x43030000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 80);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189be8
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189bf0
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189C00u, gen::fn_sub_1140D0_001140d0);
            goto L_00189dd0;
        case 0x189C10u:  // table[6]
            // 0x00189c10
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 39;
            if (a0 == v1) {
                // 0x00189c20
                charge(ctx, 2);
                v1 = 7;
                sw(v1, v0, 0);
            }
            // 0x00189c28
            charge(ctx, 37);
            lw(v1, v0, 4);
            a0 = addiu(v1, -22);
            v1 = 0x40800000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f0, f0);
            mul_s(f1, f1, f0);
            v1 = 0x41E00000;
            mtc1(v1, f0);
            div_s(f1, f1, f0);
            v1 = 311;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x42FA0000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 80);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189cbc
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189cc4
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189CD4u, gen::fn_sub_1140D0_001140d0);
            goto L_00189dd0;
        case 0x189CE4u:  // table[7]
            // 0x00189ce4
            charge(ctx, 4);
            lw(a2, v0, 4);
            a1 = 50;
            if (a2 != a1) {
                // 0x00189d00
                charge(ctx, 43);
                a0 = addiu(a2, -22);
                v1 = 0x40800000;
                mtc1(v1, f1);
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v1 = 0x41E00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 311;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                v1 = 0x42FA0000;
                mtc1(v1, f0);
                sub_s(f14, f0, f1);
                a0 = addiu(a2, -39);
                v1 = sll(a0, 8);
                a0 = subu(v1, a0);
                v1 = 11;
                div(a0, v1);
                mflo(a0);
                v1 = 255;
                a2 = subu(v1, a0);
                lw(a0, v0, 8);
                v1 = sll(a0, 2);
                v1 = addu(v1, a0);
                v1 = sll(v1, 2);
                div1(v1, a1);
                mflo1(v1);
                v1 = addiu(v1, 80);
                a0 = sll(v1, 12);
                v1 = 100;
                div(a0, v1);
                mflo(v1);
                v1 = sll(v1, 7);
                a1 = sra(v1, 12);
                if (i64(v1) < 0) {
                    // 0x00189dac
                    charge(ctx, 2);
                    v1 = addiu(v1, 4095);
                    a1 = sra(v1, 12);
                }
                // 0x00189db4
                charge(ctx, 7);
                mtc1(zero, f12);
                v1 = si(-256);
                a0 = a2 | v1;
                a2 = a1;
                lw(a3, v0, 12);
                jal(ctx, 0x189DC8u, gen::fn_sub_1140D0_001140d0);
                goto L_00189dd0;
            }
            // 0x00189cf4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00189dd4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_00189dd0;
}

// 0x00189DF0 sub_189DF0 -- 1524 bytes; frame 0x10: ra sp+0x0
// sub_189DF0: as sub_188C30 with scale 70% + 20% * t / 50.
void sub_189DF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00189df0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v1 = addiu(v1, 1);
    sw(v1, v0, 4);
    lw(v1, v0, 8);
    v1 = addiu(v1, 1);
    sw(v1, v0, 8);
    lw(v1, v0, 0);
    at = sltiu(v1, 8);
    if (at != 0) {
        // 0x00189e24
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 26752);  // &0x7B6880
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x189E40u:  // table[0]
            // 0x00189e40
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 3;
            if (a0 == v1) {
                // 0x00189e50
                charge(ctx, 6);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                v1 = 1;
                sw(v1, v0, 0);
            }
        L_0018a3d0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x189E68u:  // table[1]
            // 0x00189e68
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 14;
            if (a0 == v1) {
                // 0x00189e78
                charge(ctx, 4);
                v1 = 2;
                sw(v1, v0, 0);
            }
            goto L_0018a3d0;
        case 0x189E88u:  // table[2]
            // 0x00189e88
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 17;
            if (a0 == v1) {
                // 0x00189e98
                charge(ctx, 2);
                v1 = 3;
                sw(v1, v0, 0);
            }
            // 0x00189ea0
            charge(ctx, 39);
            lw(v1, v0, 4);
            v1 = addiu(v1, -15);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 351;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x40400000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x434F0000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 70);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x00189f3c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x00189f44
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x189F54u, gen::fn_sub_1140D0_001140d0);
            goto L_0018a3d0;
        case 0x189F64u:  // table[3]
            // 0x00189f64
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 19;
            if (a0 == v1) {
                // 0x00189f74
                charge(ctx, 2);
                v1 = 4;
                sw(v1, v0, 0);
            }
            // 0x00189f7c
            charge(ctx, 38);
            lw(v1, v0, 4);
            a0 = addiu(v1, -17);
            v1 = 0x40000000;
            mtc1(v1, f3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
            mul_s(f0, f3, f2);
            div_s(f1, f0, f3);
            v1 = 0x43B00000;
            mtc1(v1, f0);
            sub_s(f13, f0, f1);
            v1 = 0x41100000;
            mtc1(v1, f0);
            mul_s(f0, f0, f2);
            div_s(f1, f0, f3);
            v1 = 0x434C0000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 70);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a014
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a01c
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A02Cu, gen::fn_sub_1140D0_001140d0);
            goto L_0018a3d0;
        case 0x18A03Cu:  // table[4]
            // 0x0018a03c
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 23;
            if (a0 == v1) {
                // 0x0018a04c
                charge(ctx, 2);
                v1 = 5;
                sw(v1, v0, 0);
            }
            // 0x0018a054
            charge(ctx, 38);
            lw(v1, v0, 4);
            v1 = addiu(v1, -19);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40800000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x43AF0000;
            mtc1(v1, f0);
            add_s(f13, f1, f0);
            v1 = 0x41000000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x43550000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 70);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a0ec
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a0f4
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A104u, gen::fn_sub_1140D0_001140d0);
            goto L_0018a3d0;
        case 0x18A114u:  // table[5]
            // 0x0018a114
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 25;
            if (a0 == v1) {
                // 0x0018a124
                charge(ctx, 2);
                v1 = 6;
                sw(v1, v0, 0);
            }
            // 0x0018a12c
            charge(ctx, 39);
            lw(v1, v0, 4);
            v1 = addiu(v1, -23);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 351;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x41100000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x434D0000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 70);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a1c8
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a1d0
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A1E0u, gen::fn_sub_1140D0_001140d0);
            goto L_0018a3d0;
        case 0x18A1F0u:  // table[6]
            // 0x0018a1f0
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 39;
            if (a0 == v1) {
                // 0x0018a200
                charge(ctx, 2);
                v1 = 7;
                sw(v1, v0, 0);
            }
            // 0x0018a208
            charge(ctx, 41);
            lw(v1, v0, 4);
            a0 = addiu(v1, -25);
            v1 = 0x41100000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x41C80000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x43B00000;
            mtc1(v1, f0);
            add_s(f13, f1, f0);
            v1 = 0x40400000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x43560000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 70);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 7);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a2ac
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a2b4
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A2C4u, gen::fn_sub_1140D0_001140d0);
            goto L_0018a3d0;
        case 0x18A2D4u:  // table[7]
            // 0x0018a2d4
            charge(ctx, 4);
            lw(a2, v0, 4);
            a1 = 50;
            if (a2 != a1) {
                // 0x0018a2f0
                charge(ctx, 47);
                a0 = addiu(a2, -25);
                v1 = 0x41100000;
                mtc1(v1, f1);
                mtc1(a0, f0);
                cvt_s_w(f3, f0);
                mul_s(f0, f1, f3);
                v1 = 0x41C80000;
                mtc1(v1, f2);
                div_s(f1, f0, f2);
                v1 = 0x43B00000;
                mtc1(v1, f0);
                add_s(f13, f1, f0);
                v1 = 0x40400000;
                mtc1(v1, f0);
                mul_s(f0, f0, f3);
                div_s(f1, f0, f2);
                v1 = 0x43560000;
                mtc1(v1, f0);
                add_s(f14, f1, f0);
                a0 = addiu(a2, -39);
                v1 = sll(a0, 8);
                a0 = subu(v1, a0);
                v1 = 11;
                div(a0, v1);
                mflo(a0);
                v1 = 255;
                a2 = subu(v1, a0);
                lw(a0, v0, 8);
                v1 = sll(a0, 2);
                v1 = addu(v1, a0);
                v1 = sll(v1, 2);
                div1(v1, a1);
                mflo1(v1);
                v1 = addiu(v1, 70);
                a0 = sll(v1, 12);
                v1 = 100;
                div(a0, v1);
                mflo(v1);
                v1 = sll(v1, 7);
                a1 = sra(v1, 12);
                if (i64(v1) < 0) {
                    // 0x0018a3ac
                    charge(ctx, 2);
                    v1 = addiu(v1, 4095);
                    a1 = sra(v1, 12);
                }
                // 0x0018a3b4
                charge(ctx, 7);
                mtc1(zero, f12);
                v1 = si(-256);
                a0 = a2 | v1;
                a2 = a1;
                lw(a3, v0, 12);
                jal(ctx, 0x18A3C8u, gen::fn_sub_1140D0_001140d0);
                goto L_0018a3d0;
            }
            // 0x0018a2e4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x0018a3d4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_0018a3d0;
}

}  // namespace p3fes::game
