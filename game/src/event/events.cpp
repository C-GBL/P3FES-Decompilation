// The story-event player, hand-decompiled from SLUS_216.21 (slice events; layouts and roles in
// game/include/p3fes/game/events.h, the band in docs/ANALYSIS/27_unmapped_bands.md section 7): the event viewer task
// of mt_evtMain.c and its step functions, the per-frame key interpreter (sub_366AC0 and the unit-type appliers), the
// unit / key lists, the scene loaders of mt_evtLoadSave.c / mt_evtMisc.c, and the remaining scrComuCommand.c COMM
// handlers. 86 of these functions run on the dorm replay route (the opening event E401_002) and 85 on the battle
// route.
//
// Every body started as p3fes_handgen's output and keeps the recompiled body's registers, frame, spills, $ra links,
// cycle charges and check points statement for statement (game/include/p3fes/game/hg_cpu.h); what was added is the
// role of each function, the named offsets of the work / unit / key records (`lw(a3, a0, unit::kKeyHead)` is the
// original `lw a3, 108(a0)`), names for the gp-relative globals and structure. Callees run through their recomp_gen
// entry points (hand-written or recompiled alike).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/events.h"

namespace p3fes::recomp_gen {
void fn_H_Cursor_CreateTask_001005b0(p3fes::EEContext&);
void fn_H_Cursor_GetShouldDraw_00100570(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_comu_CreateRevMailSeqTask_003c2350(p3fes::EEContext&);
void fn_datGetArcanaName_0030bbb0(p3fes::EEContext&);
void fn_datGetSkillName_0030bb40(p3fes::EEContext&);
void fn_dds3GetProcessWorkData_0035ae10(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0(p3fes::EEContext&);
void fn_mtEvtMain_UpdateZikkiPlayModeEventViewerTask_0036ee30(p3fes::EEContext&);
void fn_nullsub_114_00362100(p3fes::EEContext&);
void fn_nullsub_115_00362110(p3fes::EEContext&);
void fn_nullsub_22_0035ae50(p3fes::EEContext&);
void fn_nullsub_23_0035ae60(p3fes::EEContext&);
void fn_nullsub_24_0035ae70(p3fes::EEContext&);
void fn_nullsub_25_0035ae80(p3fes::EEContext&);
void fn_nullsub_26_00385b90(p3fes::EEContext&);
void fn_nullsub_27_003952a0(p3fes::EEContext&);
void fn_nullsub_28_00395420(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrGetCmdTimer_0035f130(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrGetMessageID_0035f140(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_103C30_00103c30(p3fes::EEContext&);
void fn_sub_103CB0_00103cb0(p3fes::EEContext&);
void fn_sub_1071B0_001071b0(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_108F70_00108f70(p3fes::EEContext&);
void fn_sub_108FD0_00108fd0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A720_0010a720(p3fes::EEContext&);
void fn_sub_10A770_0010a770(p3fes::EEContext&);
void fn_sub_10BC20_0010bc20(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DBC0_0016dbc0(p3fes::EEContext&);
void fn_sub_16DCE0_0016dce0(p3fes::EEContext&);
void fn_sub_16DD40_0016dd40(p3fes::EEContext&);
void fn_sub_16DDD0_0016ddd0(p3fes::EEContext&);
void fn_sub_16DE50_0016de50(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16E2B0_0016e2b0(p3fes::EEContext&);
void fn_sub_16E410_0016e410(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_1717B0_001717b0(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_172200_00172200(p3fes::EEContext&);
void fn_sub_172820_00172820(p3fes::EEContext&);
void fn_sub_172C50_00172c50(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_176FB0_00176fb0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A0420_001a0420(p3fes::EEContext&);
void fn_sub_1A0430_001a0430(p3fes::EEContext&);
void fn_sub_1A0D00_001a0d00(p3fes::EEContext&);
void fn_sub_1A0D40_001a0d40(p3fes::EEContext&);
void fn_sub_1A0D80_001a0d80(p3fes::EEContext&);
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_1A4600_001a4600(p3fes::EEContext&);
void fn_sub_1A7020_001a7020(p3fes::EEContext&);
void fn_sub_1A7060_001a7060(p3fes::EEContext&);
void fn_sub_2FF260_002ff260(p3fes::EEContext&);
void fn_sub_2FF310_002ff310(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3185B0_003185b0(p3fes::EEContext&);
void fn_sub_318870_00318870(p3fes::EEContext&);
void fn_sub_318B00_00318b00(p3fes::EEContext&);
void fn_sub_319090_00319090(p3fes::EEContext&);
void fn_sub_319100_00319100(p3fes::EEContext&);
void fn_sub_319190_00319190(p3fes::EEContext&);
void fn_sub_3191D0_003191d0(p3fes::EEContext&);
void fn_sub_31B680_0031b680(p3fes::EEContext&);
void fn_sub_31BE80_0031be80(p3fes::EEContext&);
void fn_sub_360110_00360110(p3fes::EEContext&);
void fn_sub_3604A0_003604a0(p3fes::EEContext&);
void fn_sub_360570_00360570(p3fes::EEContext&);
void fn_sub_360640_00360640(p3fes::EEContext&);
void fn_sub_3606F0_003606f0(p3fes::EEContext&);
void fn_sub_3607A0_003607a0(p3fes::EEContext&);
void fn_sub_3608E0_003608e0(p3fes::EEContext&);
void fn_sub_360990_00360990(p3fes::EEContext&);
void fn_sub_360A40_00360a40(p3fes::EEContext&);
void fn_sub_360AB0_00360ab0(p3fes::EEContext&);
void fn_sub_360B00_00360b00(p3fes::EEContext&);
void fn_sub_360B70_00360b70(p3fes::EEContext&);
void fn_sub_360C50_00360c50(p3fes::EEContext&);
void fn_sub_360CF0_00360cf0(p3fes::EEContext&);
void fn_sub_360D40_00360d40(p3fes::EEContext&);
void fn_sub_360ED0_00360ed0(p3fes::EEContext&);
void fn_sub_361050_00361050(p3fes::EEContext&);
void fn_sub_361070_00361070(p3fes::EEContext&);
void fn_sub_361140_00361140(p3fes::EEContext&);
void fn_sub_361200_00361200(p3fes::EEContext&);
void fn_sub_361270_00361270(p3fes::EEContext&);
void fn_sub_361350_00361350(p3fes::EEContext&);
void fn_sub_361830_00361830(p3fes::EEContext&);
void fn_sub_361890_00361890(p3fes::EEContext&);
void fn_sub_361B60_00361b60(p3fes::EEContext&);
void fn_sub_361C30_00361c30(p3fes::EEContext&);
void fn_sub_361CA0_00361ca0(p3fes::EEContext&);
void fn_sub_361D60_00361d60(p3fes::EEContext&);
void fn_sub_361DD0_00361dd0(p3fes::EEContext&);
void fn_sub_361EE0_00361ee0(p3fes::EEContext&);
void fn_sub_361F20_00361f20(p3fes::EEContext&);
void fn_sub_361F60_00361f60(p3fes::EEContext&);
void fn_sub_361FE0_00361fe0(p3fes::EEContext&);
void fn_sub_362120_00362120(p3fes::EEContext&);
void fn_sub_362240_00362240(p3fes::EEContext&);
void fn_sub_362290_00362290(p3fes::EEContext&);
void fn_sub_362310_00362310(p3fes::EEContext&);
void fn_sub_362390_00362390(p3fes::EEContext&);
void fn_sub_3625E0_003625e0(p3fes::EEContext&);
void fn_sub_362F20_00362f20(p3fes::EEContext&);
void fn_sub_362FA0_00362fa0(p3fes::EEContext&);
void fn_sub_362FF0_00362ff0(p3fes::EEContext&);
void fn_sub_363030_00363030(p3fes::EEContext&);
void fn_sub_3638E0_003638e0(p3fes::EEContext&);
void fn_sub_364470_00364470(p3fes::EEContext&);
void fn_sub_3645C0_003645c0(p3fes::EEContext&);
void fn_sub_3646D0_003646d0(p3fes::EEContext&);
void fn_sub_3648E0_003648e0(p3fes::EEContext&);
void fn_sub_364A30_00364a30(p3fes::EEContext&);
void fn_sub_364B10_00364b10(p3fes::EEContext&);
void fn_sub_364E40_00364e40(p3fes::EEContext&);
void fn_sub_3650C0_003650c0(p3fes::EEContext&);
void fn_sub_365250_00365250(p3fes::EEContext&);
void fn_sub_365360_00365360(p3fes::EEContext&);
void fn_sub_365430_00365430(p3fes::EEContext&);
void fn_sub_3655F0_003655f0(p3fes::EEContext&);
void fn_sub_3657E0_003657e0(p3fes::EEContext&);
void fn_sub_3658B0_003658b0(p3fes::EEContext&);
void fn_sub_365A40_00365a40(p3fes::EEContext&);
void fn_sub_365B70_00365b70(p3fes::EEContext&);
void fn_sub_365CD0_00365cd0(p3fes::EEContext&);
void fn_sub_365F80_00365f80(p3fes::EEContext&);
void fn_sub_366210_00366210(p3fes::EEContext&);
void fn_sub_366330_00366330(p3fes::EEContext&);
void fn_sub_3663F0_003663f0(p3fes::EEContext&);
void fn_sub_366540_00366540(p3fes::EEContext&);
void fn_sub_366660_00366660(p3fes::EEContext&);
void fn_sub_366970_00366970(p3fes::EEContext&);
void fn_sub_366AC0_00366ac0(p3fes::EEContext&);
void fn_sub_36D030_0036d030(p3fes::EEContext&);
void fn_sub_36D320_0036d320(p3fes::EEContext&);
void fn_sub_36D470_0036d470(p3fes::EEContext&);
void fn_sub_36D500_0036d500(p3fes::EEContext&);
void fn_sub_36DA10_0036da10(p3fes::EEContext&);
void fn_sub_36DB20_0036db20(p3fes::EEContext&);
void fn_sub_36E140_0036e140(p3fes::EEContext&);
void fn_sub_36E260_0036e260(p3fes::EEContext&);
void fn_sub_36E690_0036e690(p3fes::EEContext&);
void fn_sub_36ED30_0036ed30(p3fes::EEContext&);
void fn_sub_36EDD0_0036edd0(p3fes::EEContext&);
void fn_sub_36EFB0_0036efb0(p3fes::EEContext&);
void fn_sub_36F000_0036f000(p3fes::EEContext&);
void fn_sub_36F260_0036f260(p3fes::EEContext&);
void fn_sub_36F370_0036f370(p3fes::EEContext&);
void fn_sub_36F480_0036f480(p3fes::EEContext&);
void fn_sub_36F490_0036f490(p3fes::EEContext&);
void fn_sub_36F4C0_0036f4c0(p3fes::EEContext&);
void fn_sub_36F4D0_0036f4d0(p3fes::EEContext&);
void fn_sub_36F500_0036f500(p3fes::EEContext&);
void fn_sub_36F5F0_0036f5f0(p3fes::EEContext&);
void fn_sub_36F640_0036f640(p3fes::EEContext&);
void fn_sub_36F900_0036f900(p3fes::EEContext&);
void fn_sub_36FA40_0036fa40(p3fes::EEContext&);
void fn_sub_385860_00385860(p3fes::EEContext&);
void fn_sub_3858C0_003858c0(p3fes::EEContext&);
void fn_sub_385990_00385990(p3fes::EEContext&);
void fn_sub_385B20_00385b20(p3fes::EEContext&);
void fn_sub_385BA0_00385ba0(p3fes::EEContext&);
void fn_sub_386110_00386110(p3fes::EEContext&);
void fn_sub_386210_00386210(p3fes::EEContext&);
void fn_sub_386390_00386390(p3fes::EEContext&);
void fn_sub_386AA0_00386aa0(p3fes::EEContext&);
void fn_sub_386AE0_00386ae0(p3fes::EEContext&);
void fn_sub_386B70_00386b70(p3fes::EEContext&);
void fn_sub_386C40_00386c40(p3fes::EEContext&);
void fn_sub_386CD0_00386cd0(p3fes::EEContext&);
void fn_sub_386D50_00386d50(p3fes::EEContext&);
void fn_sub_386E10_00386e10(p3fes::EEContext&);
void fn_sub_386E20_00386e20(p3fes::EEContext&);
void fn_sub_386E30_00386e30(p3fes::EEContext&);
void fn_sub_386E40_00386e40(p3fes::EEContext&);
void fn_sub_388DF0_00388df0(p3fes::EEContext&);
void fn_sub_388FF0_00388ff0(p3fes::EEContext&);
void fn_sub_3890E0_003890e0(p3fes::EEContext&);
void fn_sub_389F40_00389f40(p3fes::EEContext&);
void fn_sub_38A0B0_0038a0b0(p3fes::EEContext&);
void fn_sub_38A0C0_0038a0c0(p3fes::EEContext&);
void fn_sub_38A140_0038a140(p3fes::EEContext&);
void fn_sub_38A180_0038a180(p3fes::EEContext&);
void fn_sub_38A220_0038a220(p3fes::EEContext&);
void fn_sub_38A480_0038a480(p3fes::EEContext&);
void fn_sub_38A4B0_0038a4b0(p3fes::EEContext&);
void fn_sub_38A590_0038a590(p3fes::EEContext&);
void fn_sub_38A620_0038a620(p3fes::EEContext&);
void fn_sub_38A6C0_0038a6c0(p3fes::EEContext&);
void fn_sub_38A730_0038a730(p3fes::EEContext&);
void fn_sub_38A900_0038a900(p3fes::EEContext&);
void fn_sub_38C460_0038c460(p3fes::EEContext&);
void fn_sub_38C540_0038c540(p3fes::EEContext&);
void fn_sub_38CA00_0038ca00(p3fes::EEContext&);
void fn_sub_38CA80_0038ca80(p3fes::EEContext&);
void fn_sub_38CC10_0038cc10(p3fes::EEContext&);
void fn_sub_38D560_0038d560(p3fes::EEContext&);
void fn_sub_38D6B0_0038d6b0(p3fes::EEContext&);
void fn_sub_38D6F0_0038d6f0(p3fes::EEContext&);
void fn_sub_38D720_0038d720(p3fes::EEContext&);
void fn_sub_38D790_0038d790(p3fes::EEContext&);
void fn_sub_38D840_0038d840(p3fes::EEContext&);
void fn_sub_38D910_0038d910(p3fes::EEContext&);
void fn_sub_38D980_0038d980(p3fes::EEContext&);
void fn_sub_38DA10_0038da10(p3fes::EEContext&);
void fn_sub_38F0F0_0038f0f0(p3fes::EEContext&);
void fn_sub_38F440_0038f440(p3fes::EEContext&);
void fn_sub_38F8C0_0038f8c0(p3fes::EEContext&);
void fn_sub_38FA10_0038fa10(p3fes::EEContext&);
void fn_sub_38FFB0_0038ffb0(p3fes::EEContext&);
void fn_sub_3912F0_003912f0(p3fes::EEContext&);
void fn_sub_393E30_00393e30(p3fes::EEContext&);
void fn_sub_393F30_00393f30(p3fes::EEContext&);
void fn_sub_394070_00394070(p3fes::EEContext&);
void fn_sub_394270_00394270(p3fes::EEContext&);
void fn_sub_3942F0_003942f0(p3fes::EEContext&);
void fn_sub_394C30_00394c30(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);
void fn_sub_3951A0_003951a0(p3fes::EEContext&);
void fn_sub_395230_00395230(p3fes::EEContext&);
void fn_sub_395270_00395270(p3fes::EEContext&);
void fn_sub_3952B0_003952b0(p3fes::EEContext&);
void fn_sub_3952C0_003952c0(p3fes::EEContext&);
void fn_sub_3952D0_003952d0(p3fes::EEContext&);
void fn_sub_395350_00395350(p3fes::EEContext&);
void fn_sub_3953E0_003953e0(p3fes::EEContext&);
void fn_sub_395430_00395430(p3fes::EEContext&);
void fn_sub_3954E0_003954e0(p3fes::EEContext&);
void fn_sub_396410_00396410(p3fes::EEContext&);
void fn_sub_396480_00396480(p3fes::EEContext&);
void fn_sub_3964C0_003964c0(p3fes::EEContext&);
void fn_sub_396530_00396530(p3fes::EEContext&);
void fn_sub_3965D0_003965d0(p3fes::EEContext&);
void fn_sub_3965F0_003965f0(p3fes::EEContext&);
void fn_sub_396760_00396760(p3fes::EEContext&);
void fn_sub_3968A0_003968a0(p3fes::EEContext&);
void fn_sub_396910_00396910(p3fes::EEContext&);
void fn_sub_3969B0_003969b0(p3fes::EEContext&);
void fn_sub_396C70_00396c70(p3fes::EEContext&);
void fn_sub_396E30_00396e30(p3fes::EEContext&);
void fn_sub_396ED0_00396ed0(p3fes::EEContext&);
void fn_sub_396F50_00396f50(p3fes::EEContext&);
void fn_sub_397030_00397030(p3fes::EEContext&);
void fn_sub_3970D0_003970d0(p3fes::EEContext&);
void fn_sub_397500_00397500(p3fes::EEContext&);
void fn_sub_397510_00397510(p3fes::EEContext&);
void fn_sub_397520_00397520(p3fes::EEContext&);
void fn_sub_397580_00397580(p3fes::EEContext&);
void fn_sub_397630_00397630(p3fes::EEContext&);
void fn_sub_3976F0_003976f0(p3fes::EEContext&);
void fn_sub_397870_00397870(p3fes::EEContext&);
void fn_sub_397F80_00397f80(p3fes::EEContext&);
void fn_sub_398060_00398060(p3fes::EEContext&);
void fn_sub_3980E0_003980e0(p3fes::EEContext&);
void fn_sub_39B8B0_0039b8b0(p3fes::EEContext&);
void fn_sub_39E1B0_0039e1b0(p3fes::EEContext&);
void fn_sub_39E6F0_0039e6f0(p3fes::EEContext&);
void fn_sub_39E820_0039e820(p3fes::EEContext&);
void fn_sub_39E880_0039e880(p3fes::EEContext&);
void fn_sub_39EA20_0039ea20(p3fes::EEContext&);
void fn_sub_39EB90_0039eb90(p3fes::EEContext&);
void fn_sub_39EEE0_0039eee0(p3fes::EEContext&);
void fn_sub_39EEF0_0039eef0(p3fes::EEContext&);
void fn_sub_39EF30_0039ef30(p3fes::EEContext&);
void fn_sub_39F210_0039f210(p3fes::EEContext&);
void fn_sub_39F350_0039f350(p3fes::EEContext&);
void fn_sub_39F410_0039f410(p3fes::EEContext&);
void fn_sub_39F6E0_0039f6e0(p3fes::EEContext&);
void fn_sub_39F750_0039f750(p3fes::EEContext&);
void fn_sub_3A2090_003a2090(p3fes::EEContext&);
void fn_sub_3A4010_003a4010(p3fes::EEContext&);
void fn_sub_3A4220_003a4220(p3fes::EEContext&);
void fn_sub_3A4270_003a4270(p3fes::EEContext&);
void fn_sub_3B5430_003b5430(p3fes::EEContext&);
void fn_sub_3B5550_003b5550(p3fes::EEContext&);
void fn_sub_3B5620_003b5620(p3fes::EEContext&);
void fn_sub_3B58C0_003b58c0(p3fes::EEContext&);
void fn_sub_3B5980_003b5980(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D00_003b5d00(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B5DF0_003b5df0(p3fes::EEContext&);
void fn_sub_3B5F70_003b5f70(p3fes::EEContext&);
void fn_sub_3B6000_003b6000(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3B7460_003b7460(p3fes::EEContext&);
void fn_sub_3B78B0_003b78b0(p3fes::EEContext&);
void fn_sub_3B7930_003b7930(p3fes::EEContext&);
void fn_sub_3B79A0_003b79a0(p3fes::EEContext&);
void fn_sub_3B8310_003b8310(p3fes::EEContext&);
void fn_sub_3B8470_003b8470(p3fes::EEContext&);
void fn_sub_3B8690_003b8690(p3fes::EEContext&);
void fn_sub_3B86C0_003b86c0(p3fes::EEContext&);
void fn_sub_3B8730_003b8730(p3fes::EEContext&);
void fn_sub_3B87F0_003b87f0(p3fes::EEContext&);
void fn_sub_3B89F0_003b89f0(p3fes::EEContext&);
void fn_sub_3B8A60_003b8a60(p3fes::EEContext&);
void fn_sub_3B8B30_003b8b30(p3fes::EEContext&);
void fn_sub_3B8C30_003b8c30(p3fes::EEContext&);
void fn_sub_3B8E10_003b8e10(p3fes::EEContext&);
void fn_sub_3B8E80_003b8e80(p3fes::EEContext&);
void fn_sub_3B8F30_003b8f30(p3fes::EEContext&);
void fn_sub_3B8FF0_003b8ff0(p3fes::EEContext&);
void fn_sub_3B9260_003b9260(p3fes::EEContext&);
void fn_sub_3B9500_003b9500(p3fes::EEContext&);
void fn_sub_3B9550_003b9550(p3fes::EEContext&);
void fn_sub_3BB010_003bb010(p3fes::EEContext&);
void fn_sub_3BB180_003bb180(p3fes::EEContext&);
void fn_sub_3BB1D0_003bb1d0(p3fes::EEContext&);
void fn_sub_3BB280_003bb280(p3fes::EEContext&);
void fn_sub_3BB340_003bb340(p3fes::EEContext&);
void fn_sub_3BB390_003bb390(p3fes::EEContext&);
void fn_sub_3BB400_003bb400(p3fes::EEContext&);
void fn_sub_3BB450_003bb450(p3fes::EEContext&);
void fn_sub_3BCBF0_003bcbf0(p3fes::EEContext&);
void fn_sub_3BCC80_003bcc80(p3fes::EEContext&);
void fn_sub_3BD8B0_003bd8b0(p3fes::EEContext&);
void fn_sub_3BDED0_003bded0(p3fes::EEContext&);
void fn_sub_3BEA20_003bea20(p3fes::EEContext&);
void fn_sub_3BEB10_003beb10(p3fes::EEContext&);
void fn_sub_3BECA0_003beca0(p3fes::EEContext&);
void fn_sub_3BEE80_003bee80(p3fes::EEContext&);
void fn_sub_3C2EE0_003c2ee0(p3fes::EEContext&);
void fn_sub_3C3F40_003c3f40(p3fes::EEContext&);
void fn_sub_3C3F80_003c3f80(p3fes::EEContext&);
void fn_sub_3C3FE0_003c3fe0(p3fes::EEContext&);
void fn_sub_3C4130_003c4130(p3fes::EEContext&);
void fn_sub_3C43F0_003c43f0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7B90_003c7b90(p3fes::EEContext&);
void fn_sub_3C9790_003c9790(p3fes::EEContext&);
void fn_sub_3CF440_003cf440(p3fes::EEContext&);
void fn_sub_3CF630_003cf630(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
// The record layouts of events.h, by the record each offset belongs to.
namespace work = evt::work;
namespace unit = evt::unit;
namespace key = evt::key;
namespace pm = evt::pm;

// 0x00360110 sub_360110 -- 308 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x14C (no arguments; sScrCommandTable 0x7B92B0) [scrComu_SetMemberMessageParams]: for the social link in
// 0x7CE5D4 (kGpComuIndex), sub_3BEB10 gives its member record; for each of (count + 2) members -- count = the byte at
// sub_1717B0() + link + 1152 -- it fills message parameters 2i (the u16 name id at record + 4 + 2i, through
// sub_171110 / sub_3A4270), 2i + 1 (the byte at record + 12 + i, sub_3A4010) and i + 13 on the script's message
// (scrGetMessageID; asserted >= 0, scrComuCommand.c line 606), then sets the return register. Returns 1 (continue).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360110
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x360134u, gen::fn_sub_1717B0_001717b0);
    s2 = v0;
    lw(s0, gp, evt::kGpComuIndex);  // 0x7CE5D4
    a0 = s0;
    jal(ctx, 0x360148u, gen::fn_sub_3BEB10_003beb10);
    s1 = v0;
    jal(ctx, 0x360154u, gen::fn_scrGetMessageID_0035f140);
    s4 = v0;
    if (i64(s4) < 0) {
        // 0x00360168
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 606;
        jal(ctx, 0x360174u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036017c
    charge(ctx, 5);
    v0 = addu(s0, s2);
    lbu(s6, v0, 1152);
    s5 = 0;
    for (;;) {
        // 0x003601fc
        charge(ctx, 4);
        a0 = addiu(s6, 2);
        v0 = slt(s5, a0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00360190
        charge(ctx, 27);
        s2 = sll(s5, 1);
        v0 = addu(s1, s2);
        lh(s0, v0, 4);
        v0 = addu(s1, s5);
        lbu(s3, v0, 12);
        a0 = s0;
        a1 = 2;
        jal(ctx, 0x3601ACu, gen::fn_sub_171110_00171110);
        a2 = dsll32(s0, 16);
        a2 = dsra32(a2, 16);
        a0 = s4;
        a1 = s2;
        jal(ctx, 0x3601C4u, gen::fn_sub_3A4270_003a4270);
        a1 = addiu(s2, 1);
        a0 = s4;
        a2 = s3;
        a3 = 0;
        jal(ctx, 0x3601DCu, gen::fn_sub_3A4010_003a4010);
        a1 = addiu(s5, 13);
        a0 = s4;
        a2 = 2;
        jal(ctx, 0x3601F0u, gen::fn_sub_3A4270_003a4270);
        s5 = addiu(s5, 1);
    }
    // 0x0036020c
    charge(ctx, 14);
    jal(ctx, 0x36020Cu, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
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

// 0x003604A0 sub_3604A0 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x0EA (2 arguments) [scrComu_SetLinkValue]: arg0 = social link (asserted valid by sub_16DCE0, line 722),
// arg1 >= 0 (line 726); when the link is active (sub_16E100) sub_16E2B0(link, arg1). Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3604A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003604a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3604B4u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3604C8u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003604d8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 722;
        jal(ctx, 0x3604E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003604ec
    charge(ctx, 6);
    a0 = 1;
    jal(ctx, 0x3604F0u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    if (i64(s1) < 0) {
        // 0x00360504
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 726;
        jal(ctx, 0x360510u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360518
    charge(ctx, 6);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360520u, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        // 0x0036053c
        charge(ctx, 6);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = s1;
        jal(ctx, 0x360548u, gen::fn_sub_16E2B0_0016e2b0);
        v0 = 1;
    } else {
        // 0x00360530
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00360554 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00360570 sub_360570 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 0x11D (1 argument) [scrComu_RankUp]: arg0 = social link (line 746); when active, its rank (sub_16DBA0, s8) in
// 1..9 becomes rank + 1 through sub_16E410. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360570(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360570
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360580u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360594u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003605a4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 746;
        jal(ctx, 0x3605B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003605b8
    charge(ctx, 6);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3605C0u, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        // 0x003605dc
        charge(ctx, 8);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3605E4u, gen::fn_sub_16DBA0_0016dba0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        if (i64(v0) > 0) {
            // 0x003605fc
            charge(ctx, 3);
            at = slti(v0, 10);
            if (at != 0) {
                // 0x00360608
                charge(ctx, 7);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                v0 = addiu(v0, 1);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                jal(ctx, 0x36061Cu, gen::fn_sub_16E410_0016e410);
            }
        }
        // 0x00360624
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003605d0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00360628 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00360640 sub_360640 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x121 (2 arguments): arg0 = social link (line 774), arg1 = on / off; when the link is active
// sub_171C40(link, arg1 != 0). Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360640
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360654u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x360664u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360678u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x00360688
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 774;
        jal(ctx, 0x360694u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036069c
    charge(ctx, 6);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3606A4u, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        // 0x003606c0
        charge(ctx, 5);
        a1 = sltu(0, s0);
        a0 = s1;
        jal(ctx, 0x3606C8u, gen::fn_sub_171C40_00171c40);
        v0 = 1;
    } else {
        // 0x003606b4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003606d4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003606F0 sub_3606F0 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x122 (2 arguments): the same shape as COMM 0x121 (line 801) with sub_172200(link, arg1 != 0). Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3606F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003606f0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360704u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x360714u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360728u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x00360738
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 801;
        jal(ctx, 0x360744u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036074c
    charge(ctx, 6);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360754u, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        // 0x00360770
        charge(ctx, 5);
        a1 = sltu(0, s0);
        a0 = s1;
        jal(ctx, 0x360778u, gen::fn_sub_172200_00172200);
        v0 = 1;
    } else {
        // 0x00360764
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00360784 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003607A0 sub_3607A0 -- 320 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x124 (1 argument) [scrComu_SetLinkMessageParams]: arg0 = social link (line 829); message parameters of the
// script's message (line 835): 0 = sub_3C3F80(link) (a name string), 1 = datGetArcanaName(sub_16DF30(link)), 2 = the
// rank (sub_16DBA0) when the link is active (sub_16E100 == 1), else 0. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3607A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003607a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3607B8u, gen::fn_scrGetIntPara_0035ed20);
    s2 = v0;
    s0 = 0;
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3607D0u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003607e0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 829;
        jal(ctx, 0x3607ECu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003607f4
    charge(ctx, 5);
    jal(ctx, 0x3607F4u, gen::fn_scrGetMessageID_0035f140);
    s1 = v0;
    if (i64(s1) < 0) {
        // 0x00360808
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 835;
        jal(ctx, 0x360814u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036081c
    charge(ctx, 7);
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360824u, gen::fn_sub_16E100_0016e100);
    v1 = 1;
    if (v0 == v1) {
        // 0x00360838
        charge(ctx, 6);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x360840u, gen::fn_sub_16DBA0_0016dba0);
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
    }
    // 0x00360850
    charge(ctx, 36);
    a0 = s2;
    jal(ctx, 0x360854u, gen::fn_sub_3C3F80_003c3f80);
    a0 = s1;
    a1 = 0;
    a2 = v0;
    jal(ctx, 0x360868u, gen::fn_sub_3A4220_003a4220);
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360878u, gen::fn_sub_16DF30_0016df30);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    a0 = v0 & 0xFF;
    jal(ctx, 0x36088Cu, gen::fn_datGetArcanaName_0030bbb0);
    a0 = s1;
    a1 = 1;
    a2 = v0;
    jal(ctx, 0x3608A0u, gen::fn_sub_3A4220_003a4220);
    a0 = s1;
    a1 = 2;
    a2 = s0;
    a3 = 0;
    jal(ctx, 0x3608B8u, gen::fn_sub_3A4010_003a4010);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003608E0 sub_3608E0 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 0x125 (1 argument): arg0 = social link (asserted valid, line 871, and active, line 874); returns
// sub_3BDED0(link) in the script's return register. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3608E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003608e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3608F0u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360904u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x00360914
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 871;
        jal(ctx, 0x360920u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360928
    charge(ctx, 6);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360930u, gen::fn_sub_16E100_0016e100);
    if (v0 == 0) {
        // 0x00360940
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 874;
        jal(ctx, 0x36094Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360954
    charge(ctx, 12);
    a0 = s0;
    jal(ctx, 0x360958u, gen::fn_sub_3BDED0_003bded0);
    a0 = v0;
    jal(ctx, 0x360964u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00360990 sub_360990 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x126 (2 arguments) [scrComu_WaitMessageTask]: a two-phase command. First frame (scrGetCmdTimer() == 0):
// creates the task sub_3A2090(0, arg0, arg1, 1024) into 0x7CE5BC and yields (0). Later frames: yields while the task
// exists (kwlnTaskExists), then clears 0x7CE5BC and continues (1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360990
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3609A4u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x3609B4u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    jal(ctx, 0x3609C0u, gen::fn_scrGetCmdTimer_0035f130);
    if (v0 == 0) {
        // 0x003609d0
        charge(ctx, 9);
        a0 = 0;
        a1 = s1;
        a2 = s0;
        a3 = 1024;
        jal(ctx, 0x3609E0u, gen::fn_sub_3A2090_003a2090);
        sw(v0, gp, evt::kGpComuMsgTask);  // 0x7CE5BC
        goto L_00360a18;
    }
    // 0x003609f4
    charge(ctx, 5);
    lw(a0, gp, evt::kGpComuMsgTask);  // 0x7CE5BC
    jal(ctx, 0x3609F8u, gen::fn_kwlnTaskExists_00195460);
    if (v0 != 0) {
    L_00360a18:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00360a08
        charge(ctx, 4);
        sw(zero, gp, evt::kGpComuMsgTask);  // 0x7CE5BC
        v0 = 1;
    }
    // 0x00360a1c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00360A40 sub_360A40 -- 108 bytes; frame 0x10: ra sp+0x0
// COMM 0x129 (no arguments) [scrComu_RunRevMailSeq]: first frame creates the "RevMailSeq" task
// (comu_CreateRevMailSeqTask(0, 3072)) into 0x7CE5C0 and yields; later frames wait for it to end, then clear 0x7CE5C0
// and continue.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360a40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x360A48u, gen::fn_scrGetCmdTimer_0035f130);
    if (v0 == 0) {
        // 0x00360a58
        charge(ctx, 7);
        a0 = 0;
        a1 = 3072;
        jal(ctx, 0x360A60u, gen::fn_comu_CreateRevMailSeqTask_003c2350);
        sw(v0, gp, evt::kGpRevMailTask);  // 0x7CE5C0
        goto L_00360a98;
    }
    // 0x00360a74
    charge(ctx, 5);
    lw(a0, gp, evt::kGpRevMailTask);  // 0x7CE5C0
    jal(ctx, 0x360A78u, gen::fn_kwlnTaskExists_00195460);
    if (v0 != 0) {
    L_00360a98:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00360a88
        charge(ctx, 4);
        sw(zero, gp, evt::kGpRevMailTask);  // 0x7CE5C0
        v0 = 1;
    }
    // 0x00360a9c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00360AB0 sub_360AB0 -- 80 bytes; frame 0x90: ra sp+0x0
// COMM 0x172 (no arguments): sets the return register to 1 when sub_3BECA0(&local) is non-zero, else 0 (the local is a
// 128-byte buffer in the frame). Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360ab0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x0);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x360ABCu, gen::fn_sub_3BECA0_003beca0);
    if (v0 != 0) {
        // 0x00360ae0
        charge(ctx, 3);
        a0 = 1;
        jal(ctx, 0x360AE4u, gen::fn_scrSetIntReturnVal_0035f060);
    } else {
        // 0x00360acc
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x360AD0u, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x00360aec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00360B00 sub_360B00 -- 108 bytes; frame 0x10: ra sp+0x0
// COMM 0x12A (no arguments): COMM 0x129's shape for the task sub_39B8B0(0, 3072) in 0x7CE5C4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360B00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360b00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x360B08u, gen::fn_scrGetCmdTimer_0035f130);
    if (v0 == 0) {
        // 0x00360b18
        charge(ctx, 7);
        a0 = 0;
        a1 = 3072;
        jal(ctx, 0x360B20u, gen::fn_sub_39B8B0_0039b8b0);
        sw(v0, gp, evt::kGpComuTask3);  // 0x7CE5C4
        goto L_00360b58;
    }
    // 0x00360b34
    charge(ctx, 5);
    lw(a0, gp, evt::kGpComuTask3);  // 0x7CE5C4
    jal(ctx, 0x360B38u, gen::fn_kwlnTaskExists_00195460);
    if (v0 != 0) {
    L_00360b58:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00360b48
        charge(ctx, 4);
        sw(zero, gp, evt::kGpComuTask3);  // 0x7CE5C4
        v0 = 1;
    }
    // 0x00360b5c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00360B70 sub_360B70 -- 220 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x17D (1 argument): arg0 = social link (line 985); when sub_16DBC0(link, &id) == 1: message parameter 0 =
// sub_173220(id) (when the script has a message) and the return register = id; else the return register = 0.
// Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360b70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360B84u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x360B98u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x00360ba8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 985;
        jal(ctx, 0x360BB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360bbc
    charge(ctx, 11);
    jal(ctx, 0x360BBCu, gen::fn_scrGetMessageID_0035f140);
    s1 = v0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x360BD4u, gen::fn_sub_16DBC0_0016dbc0);
    v1 = 1;
    if (v0 != v1) {
        // 0x00360c24
        charge(ctx, 3);
        a0 = 0;
        jal(ctx, 0x360C28u, gen::fn_scrSetIntReturnVal_0035f060);
    } else {
        // 0x00360be8
        charge(ctx, 2);
        if (i64(s1) >= 0) {
            // 0x00360bf0
            charge(ctx, 8);
            lhu(a0, sp, 0x3C);
            jal(ctx, 0x360BF4u, gen::fn_sub_173220_00173220);
            a0 = s1;
            a1 = 0;
            a2 = v0;
            jal(ctx, 0x360C08u, gen::fn_sub_3A4220_003a4220);
        }
        // 0x00360c10
        charge(ctx, 5);
        lw(a0, sp, 0x3C);
        jal(ctx, 0x360C14u, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x00360c30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00360C50 sub_360C50 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x19E (3 arguments) [scrComu_PlayVoice]: arg0 == 1 -> sub_395350(arg1 + 3, 0); arg0 == 0 -> sub_3952D0(0, arg2,
// arg1 + 3) (the event sound channels 3.. also used by the adx keys of sub_363030); other values do nothing.
// Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360c50
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360C64u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x360C74u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = 2;
    jal(ctx, 0x360C84u, gen::fn_scrGetIntPara_0035ed20);
    v1 = 1;
    if (s1 == v1) {
        // 0x00360cc4
        charge(ctx, 4);
        a0 = addiu(s0, 3);
        a1 = 0;
        jal(ctx, 0x360CCCu, gen::fn_sub_395350_00395350);
    } else {
        // 0x00360c98
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x00360ca8
            charge(ctx, 7);
            a2 = addiu(s0, 3);
            a0 = 0;
            a1 = v0;
            jal(ctx, 0x360CB4u, gen::fn_sub_3952D0_003952d0);
        } else {
            // 0x00360ca0
            charge(ctx, 2);
        }
    }
    // 0x00360cd4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00360CF0 sub_360CF0 -- 76 bytes; frame 0x10: ra sp+0x0
// COMM 0x1A8 (1 argument) [scrComu_GetSkillList]: resets the cursor 0x7CE5C8, stores the list sub_3BEE80(arg0,
// &count) in 0x7CE5CC (count in 0x7CE5D0) and returns the count. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360cf0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x360CFCu, gen::fn_scrGetIntPara_0035ed20);
    sw(zero, gp, evt::kGpSkillCursor);  // 0x7CE5C8
    a0 = v0;
    a1 = addiu(gp, -18208);  // &0x7CE5D0
    jal(ctx, 0x360D10u, gen::fn_sub_3BEE80_003bee80);
    sw(v0, gp, evt::kGpSkillList);  // 0x7CE5CC
    lw(a0, gp, evt::kGpSkillCount);  // 0x7CE5D0
    jal(ctx, 0x360D20u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00360D40 sub_360D40 -- 388 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 0x1A9 (no arguments) [scrComu_SetSkillListMessage]: for entry 0x7CE5C8 of COMM 0x1A8's list (asserted below
// the count, line 1063; message asserted, line 1060): message parameter 0 = the byte +3 of the 14-byte record of that
// id in the table at *0x7CE420, 1 = sub_173220(id), 2..4 = sub_3C43F0(), then 2.. = datGetSkillName of each skill
// sub_176FB0(id, list, &n) lists; advances the cursor. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360D40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360d40
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, evt::kGpSkillCursor);  // 0x7CE5C8
    v1 = sll(v0, 1);
    lw(v0, gp, evt::kGpSkillList);  // 0x7CE5CC
    v0 = addu(v0, v1);
    lhu(s0, v0, 0);
    jal(ctx, 0x360D68u, gen::fn_scrGetMessageID_0035f140);
    s1 = v0;
    if (i64(s1) < 0) {
        // 0x00360d7c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 1060;
        jal(ctx, 0x360D88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360d90
    charge(ctx, 5);
    lw(v1, gp, evt::kGpSkillCount);  // 0x7CE5D0
    lw(v0, gp, evt::kGpSkillCursor);  // 0x7CE5C8
    at = slt(v0, v1);
    if (at == 0) {
        // 0x00360da4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 1063;
        jal(ctx, 0x360DB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360db8
    charge(ctx, 22);
    lw(v1, gp, -18640);  // 0x7CE420
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    lbu(a2, v0, 3);
    a0 = s1;
    a1 = 0;
    a3 = 0;
    jal(ctx, 0x360DDCu, gen::fn_sub_3A4010_003a4010);
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x360DE8u, gen::fn_sub_173220_00173220);
    a0 = s1;
    a1 = 1;
    a2 = v0;
    jal(ctx, 0x360DFCu, gen::fn_sub_3A4220_003a4220);
    s2 = 0;
    for (;;) {
        // 0x00360e30
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00360e10
        charge(ctx, 8);
        jal(ctx, 0x360E10u, gen::fn_sub_3C43F0_003c43f0);
        a1 = addiu(s2, 2);
        a0 = s1;
        a2 = v0;
        jal(ctx, 0x360E24u, gen::fn_sub_3A4220_003a4220);
        s2 = addiu(s2, 1);
    }
    // 0x00360e3c
    charge(ctx, 8);
    a0 = s0 & 0xFFFF;
    a1 = addiu(sp, 0x40);
    a2 = addiu(sp, 0x5C);
    jal(ctx, 0x360E48u, gen::fn_sub_176FB0_00176fb0);
    s0 = 0;
    for (;;) {
        // 0x00360e88
        charge(ctx, 4);
        lw(v0, sp, 0x5C);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00360e5c
        charge(ctx, 11);
        v0 = sll(s0, 1);
        v0 = addu(v0, sp);
        lhu(a0, v0, 64);
        jal(ctx, 0x360E68u, gen::fn_datGetSkillName_0030bb40);
        a1 = addiu(s0, 2);
        a0 = s1;
        a2 = v0;
        jal(ctx, 0x360E7Cu, gen::fn_sub_3A4220_003a4220);
        s0 = addiu(s0, 1);
    }
    // 0x00360e98
    charge(ctx, 11);
    lw(v0, gp, evt::kGpSkillCursor);  // 0x7CE5C8
    v0 = addiu(v0, 1);
    sw(v0, gp, evt::kGpSkillCursor);  // 0x7CE5C8
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00360ED0 sub_360ED0 -- 372 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtKeyCondTrue] (key) -> 1 when the key fires. Keys of unit types without conditions (sub_36F500 == 0) always
// fire. kCondType 2: MT_Misc_BitChk(flag + bank base) compared with kCondValue (bank 0 +0, 1 +1024, 2 +4096; bank >= 3
// -> 0); kCondType 1: event counter kCondFlag (sub_38D6F0) == kCondValue; 0: fires; any other type prints "ASSERT!!
// Comp flag Invalid Value!!", clears the condition (memset 8 bytes at +8) and fires.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_360ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360ed0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    lw(a0, a0, key::kOwnerType);
    jal(ctx, 0x360EECu, gen::fn_sub_36F500_0036f500);
    if (v0 != 0) {
        // 0x00360f08
        charge(ctx, 4);
        lb(v1, s1, key::kCondType);
        a0 = 2;
        if (v1 == a0) {
            // 0x00360f5c
            charge(ctx, 4);
            lbu(v1, s1, key::kCondBank);
            v0 = slti(v1, 3);
            if (v0 != 0) {
                // 0x00360f78
                charge(ctx, 2);
                if (v1 == a0) {
                    // 0x00360fb0
                    charge(ctx, 1);
                    s0 = 4096;
                } else {
                    // 0x00360f80
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00360fa4
                        charge(ctx, 3);
                        s0 = 1024;
                    } else {
                        // 0x00360f8c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00360f9c
                            charge(ctx, 2);
                        } else {
                            // 0x00360f94
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x00360fb4
                charge(ctx, 3);
                lh(v0, s1, key::kCondValue);
                if (v0 != 0) {
                    // 0x00360fe0
                    charge(ctx, 8);
                    lh(v0, s1, key::kCondFlag);
                    a0 = addu(v0, s0);
                    jal(ctx, 0x360FE8u, gen::fn_MT_Misc_BitChk_003951d0);
                    v0 = v0 ^ 0x1;
                    v0 = sltiu(v0, 1);
                } else {
                    // 0x00360fc0
                    charge(ctx, 8);
                    lh(v0, s1, key::kCondFlag);
                    a0 = addu(v0, s0);
                    jal(ctx, 0x360FC8u, gen::fn_MT_Misc_BitChk_003951d0);
                    // xor v0: a 64-bit move to itself (no effect)
                    v0 = sltiu(v0, 1);
                }
            } else {
                // 0x00360f6c
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x00360f18
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00360f3c
                charge(ctx, 8);
                lh(a0, s1, key::kCondFlag);
                jal(ctx, 0x360F40u, gen::fn_sub_38D6F0_0038d6f0);
                lh(v1, s1, key::kCondValue);
                v0 = v1 ^ v0;
                v0 = sltiu(v0, 1);
            } else {
                // 0x00360f24
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00360f34
                    charge(ctx, 2);
                } else {
                    // 0x00360f2c
                    charge(ctx, 2);
                    // 0x00361000
                    charge(ctx, 11);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -10928);  // "ASSERT!! Comp flag Invalid Value!! objtype =%d\n"
                    lw(a1, s1, key::kOwnerType);
                    jal(ctx, 0x36100Cu, gen::fn_printf_005225a8);
                    a0 = addiu(s1, 8);
                    a1 = 0;
                    a2 = 8;
                    jal(ctx, 0x361020u, gen::fn_memset_00521408);
                    v0 = 1;
                }
            }
        }
    } else {
        // 0x00360efc
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0036102c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00361050 sub_361050 -- 20 bytes; leaf frame (no stack)
// [evtRequestJump] (work, frame): kJumpFrame = frame, kJumpRequest = 1 -- the next frame advance jumps there.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361050(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00361050
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(a1, a0, work::kJumpFrame);
    v1 = 1;
    sw(v1, a0, work::kJumpRequest);
}

// 0x00361070 sub_361070 -- 196 bytes; frame 0x90: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtWorkReset] (work): clears the 2448-byte record except +0 (self) and the 23 words at kField2344.. (task
// handles), which it keeps through a 92-byte copy in the frame; then sub_386AA0 (memory counters), kFlagPaused,
// +12 = 540, kEndFrame = 539, kMetrics = 1. Called by sub_36DB20's first load state.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361070
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s1, a0, 0);
    a1 = addiu(s0, 2344);
    a0 = addiu(sp, 0x30);
    v1 = 23;
    for (;;) {
        // 0x00361094
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003610b0
    charge(ctx, 9);
    a0 = s0;
    a1 = 0;
    a2 = 2448;
    jal(ctx, 0x3610BCu, gen::fn_memset_00521408);
    sw(s1, s0, work::kSelf);
    a1 = addiu(sp, 0x30);
    a0 = addiu(s0, 2344);
    v1 = 23;
    for (;;) {
        // 0x003610d4
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003610f0
    charge(ctx, 17);
    jal(ctx, 0x3610F0u, gen::fn_sub_386AA0_00386aa0);
    lw(v1, s0, work::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, work::kFlags);
    v1 = 540;
    sw(v1, s0, work::kField12);
    v1 = addiu(v1, -1);
    sw(v1, s0, work::kEndFrame);
    v1 = 1;
    sw(v1, s0, work::kMetrics);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00361140 sub_361140 -- 184 bytes; leaf frame (no stack)
// [evtUnitInsertKey] (unit, key): links the key into the unit's list sorted by kFrame (before the first key with a
// greater frame; at the tail otherwise) and counts it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00361140
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a3, a0, unit::kKeyHead);
    if (a3 != 0) {
        for (;;) {
            // 0x003611bc
            charge(ctx, 2);
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00361164
            charge(ctx, 5);
            lhu(a2, a1, key::kFrame);
            lhu(v1, a3, key::kFrame);
            at = slt(a2, v1);
            if (at != 0) {
                goto L_00361178_3;
            }
            // 0x003611b8
            charge(ctx, 1);
            lw(a3, a3, key::kNext);
        }
    L_003611c4:
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x003611cc
            charge(ctx, 6);
            lw(v1, a0, unit::kKeyTail);
            sw(a1, v1, 76);
            lw(v1, a0, unit::kKeyTail);
            sw(v1, a1, key::kPrev);
            sw(zero, a1, key::kNext);
            sw(a1, a0, unit::kKeyTail);
        }
    } else {
        // 0x0036114c
        charge(ctx, 6);
        sw(a1, a0, unit::kKeyHead);
        sw(a1, a0, unit::kKeyTail);
        sw(zero, a1, key::kNext);
        sw(zero, a1, key::kPrev);
    }
    // 0x003611e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lw(v1, a0, unit::kKeyCount);
    v1 = addiu(v1, 1);
    sw(v1, a0, unit::kKeyCount);
    return;
L_00361178_3:
    charge(ctx, 3);
    lw(v1, a3, key::kPrev);
    if (v1 != 0) {
        // 0x0036119c
        charge(ctx, 7);
        sw(a1, v1, 76);
        lw(v1, a3, key::kPrev);
        sw(v1, a1, key::kPrev);
        sw(a3, a1, key::kNext);
        sw(a1, a3, key::kPrev);
    } else {
        // 0x00361184
        charge(ctx, 6);
        sw(a1, a0, unit::kKeyHead);
        sw(a1, a3, key::kPrev);
        sw(zero, a1, key::kPrev);
        sw(a3, a1, key::kNext);
    }
    goto L_003611c4;
}

// 0x00361200 sub_361200 -- 100 bytes; leaf frame (no stack)
// [evtUnitUnlinkKey] (unit, key): unlinks the key (head / tail fixed up), clears its links, uncounts it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00361200
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a2, a1, key::kPrev);
    if (a2 != 0) {
        // 0x0036121c
        charge(ctx, 2);
        lw(v1, a1, key::kNext);
        sw(v1, a2, key::kNext);
    } else {
        // 0x0036120c
        charge(ctx, 4);
        lw(v1, a1, key::kNext);
        sw(v1, a0, unit::kKeyHead);
    }
    // 0x00361224
    charge(ctx, 3);
    lw(a2, a1, key::kNext);
    if (a2 != 0) {
        // 0x00361240
        charge(ctx, 2);
        lw(v1, a1, key::kPrev);
        sw(v1, a2, key::kPrev);
    } else {
        // 0x00361230
        charge(ctx, 4);
        lw(v1, a1, key::kPrev);
        sw(v1, a0, unit::kKeyTail);
    }
    // 0x00361248 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, a1, key::kPrev);
    sw(zero, a1, key::kNext);
    lw(v1, a0, unit::kKeyCount);
    v1 = addiu(v1, -1);
    sw(v1, a0, unit::kKeyCount);
}

// 0x00361270 sub_361270 -- 212 bytes; frame 0x10: ra sp+0x0
// [evtUnitSortKeys] (unit): one pass of re-sorting: for each key, the first later key with a smaller frame is unlinked
// and re-inserted through sub_361140 (the outer walk then continues from the re-inserted key's successor).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361270
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00361280
        charge(ctx, 3);
        lw(a3, a0, unit::kKeyHead);
        for (;;) {
            // 0x0036132c
            charge(ctx, 2);
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0036128c
            charge(ctx, 3);
            lw(a1, a3, key::kNext);
            for (;;) {
                // 0x00361320
                charge(ctx, 2);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00361298
                charge(ctx, 5);
                lhu(a2, a3, key::kFrame);
                lhu(v1, a1, key::kFrame);
                at = slt(v1, a2);
                if (at != 0) {
                    goto L_003612ac_4;
                }
                // 0x0036131c
                charge(ctx, 1);
                lw(a1, a1, key::kNext);
            }
        L_00361328:
            charge(ctx, 1);
            lw(a3, a3, key::kNext);
        }
    }
    // 0x00361334 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_003612ac_4:
    charge(ctx, 3);
    lw(a2, a1, key::kPrev);
    if (a2 != 0) {
        // 0x003612c8
        charge(ctx, 2);
        lw(v1, a1, key::kNext);
        sw(v1, a2, key::kNext);
    } else {
        // 0x003612b8
        charge(ctx, 4);
        lw(v1, a1, key::kNext);
        sw(v1, a0, unit::kKeyHead);
    }
    // 0x003612d0
    charge(ctx, 3);
    lw(a2, a1, key::kNext);
    if (a2 != 0) {
        // 0x003612ec
        charge(ctx, 2);
        lw(v1, a1, key::kPrev);
        sw(v1, a2, key::kPrev);
    } else {
        // 0x003612dc
        charge(ctx, 4);
        lw(v1, a1, key::kPrev);
        sw(v1, a0, unit::kKeyTail);
    }
    // 0x003612f4
    charge(ctx, 10);
    sw(zero, a1, key::kPrev);
    sw(zero, a1, key::kNext);
    lw(v1, a0, unit::kKeyCount);
    v1 = addiu(v1, -1);
    sw(v1, a0, unit::kKeyCount);
    jal(ctx, 0x361308u, gen::fn_sub_361140_00361140);
    a3 = a1;
    goto L_00361328;
}

// 0x00361350 sub_361350 -- 1248 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateKey] (unit, frame, work) -> key: allocates an 84-byte key (sub_386AE0, memory class 8; asserted, line
// 562), zeroes it, sets kFrame, kName = -1, kPath = 0, kOwnerType = the unit's type, inserts it (sub_361140) and
// initialises the per-type parameters in a 51-way switch on the unit type (jump table 0x7BA2F0): types 1/2/3/9/18/
// 20/21/24/26 take a name index from the work's name table (sub_361FE0 with the unit's kName); camera units (10) first
// allocate their 48-byte record (class 9; line 519) and fill it with sub_38C540; type 41 allocates a path
// (sub_38D790); an unknown type asserts (line 885).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361350(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00361350
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s0 = 0;
    lw(v1, a0, 0);
    v0 = 25;
    if (v1 != v0) {
        // 0x0036138c
        charge(ctx, 3);
        v0 = 24;
        if (v1 != v0) {
            // 0x00361398
            charge(ctx, 3);
            v0 = 10;
            if (v1 == v0) {
                // 0x003613ac
                charge(ctx, 7);
                a0 = 48;
                a1 = 9;
                jal(ctx, 0x3613B4u, gen::fn_sub_386AE0_00386ae0);
                s0 = v0;
                if (s0 == 0) {
                    // 0x003613c8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -10880);  // "mt_evtMain.c"
                    a1 = 519;
                    jal(ctx, 0x3613D4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003613dc
                charge(ctx, 8);
                a0 = s2;
                a1 = s4;
                a2 = s3;
                a3 = s0;
                t0 = addiu(sp, 0x8C);
                t1 = addiu(sp, 0x88);
                jal(ctx, 0x3613F4u, gen::fn_sub_38C540_0038c540);
            } else {
                // 0x003613a4
                charge(ctx, 2);
            }
        }
    }
    // 0x003613fc
    charge(ctx, 7);
    a0 = 84;
    a1 = 8;
    jal(ctx, 0x361404u, gen::fn_sub_386AE0_00386ae0);
    s1 = v0;
    if (s1 == 0) {
        // 0x00361418
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 562;
        jal(ctx, 0x361424u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036142c
    charge(ctx, 19);
    a0 = s1;
    a1 = 0;
    a2 = 84;
    jal(ctx, 0x361438u, gen::fn_memset_00521408);
    sh(s3, s1, key::kFrame);
    v0 = si(-1);
    sw(v0, s1, key::kName);
    sw(zero, s1, key::kPath);
    lw(v0, s4, unit::kType);
    sw(v0, s1, key::kOwnerType);
    a0 = s4;
    a1 = s1;
    jal(ctx, 0x361460u, gen::fn_sub_361140_00361140);
    lw(v0, s4, unit::kType);
    at = sltiu(v0, 51);
    if (at != 0) {
        // 0x00361478
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -23824);  // &0x7BA2F0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        // unit type 2: +16 = *0x7CB10C, a name index
        case 0x361494u:  // table[2]
            // 0x00361494
            charge(ctx, 12);
            lwc1(f0, gp, -31716);  // 0x7CB10C
            swc1(f0, s1, key::kCmd);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x3614B0u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            break;
        // unit type 1 (character): a name index, +16 = 0, +22 = 0, +23 = 20
        case 0x3614C4u:  // table[1]
            // 0x003614c4
            charge(ctx, 14);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x3614D8u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            sb(zero, s1, key::kCmd);
            sb(zero, s1, 22);
            v0 = 20;
            sb(v0, s1, 23);
            break;
        // unit type 48 (field object): +16 = 0, +48 = the unit's kParam
        case 0x3614FCu:  // table[48]
            // 0x003614fc
            charge(ctx, 5);
            sb(zero, s1, key::kCmd);
            lw(v0, s4, unit::kParam);
            sb(v0, s1, 48);
            break;
        // unit type 3: a name index, +16 = -1, +18 = 0, +20 = 0, +21 = -1, +22 = -1, +24 = 0
        case 0x361510u:  // table[3]
            // 0x00361510
            charge(ctx, 17);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x361524u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            v0 = si(-1);
            sb(v0, s1, key::kCmd);
            sh(zero, s1, 18);
            sb(zero, s1, key::kArg20);
            sb(v0, s1, 21);
            sh(v0, s1, 22);
            sh(zero, s1, 24);
            break;
        // unit type 18: a name index, +16 = 0, +18 = -1
        case 0x361554u:  // table[18]
            // 0x00361554
            charge(ctx, 14);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x361568u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            sh(zero, s1, key::kCmd);
            v0 = si(-1);
            sh(v0, s1, 18);
            sb(zero, s1, key::kCmd);
            break;
        // unit types 20 / 21: a name index, +16 = -1, +17 = 0, +18 = 0, +20..+23 = -1, +24 = 0
        case 0x36158Cu:  // table[20, 21]
            // 0x0036158c
            charge(ctx, 19);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x3615A0u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            v0 = si(-1);
            sb(v0, s1, key::kCmd);
            sb(zero, s1, 17);
            sh(zero, s1, 18);
            sb(v0, s1, key::kArg20);
            sb(v0, s1, 21);
            sb(v0, s1, 22);
            sb(v0, s1, 23);
            sh(zero, s1, 24);
            break;
        // unit type 26: as type 3
        case 0x3615D8u:  // table[26]
            // 0x003615d8
            charge(ctx, 17);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x3615ECu, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            v0 = si(-1);
            sb(v0, s1, key::kCmd);
            sh(zero, s1, 18);
            sb(zero, s1, key::kArg20);
            sb(v0, s1, 21);
            sh(v0, s1, 22);
            sh(zero, s1, 24);
            break;
        // unit type 9: a name index, +16 = -1, +18 = 1
        case 0x36161Cu:  // table[9]
            // 0x0036161c
            charge(ctx, 14);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x361630u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            v0 = si(-1);
            sh(v0, s1, key::kCmd);
            v0 = 1;
            sh(v0, s1, 18);
            break;
        // unit type 12: +16 = 1, +18 = 128, +20 = 0
        case 0x361654u:  // table[12]
            // 0x00361654
            charge(ctx, 7);
            v0 = 1;
            sh(v0, s1, key::kCmd);
            v0 = 128;
            sh(v0, s1, 18);
            sw(zero, s1, key::kArg20);
            break;
        // unit type 22: +16 = 1
        case 0x361670u:  // table[22]
            // 0x00361670
            charge(ctx, 4);
            v0 = 1;
            sh(v0, s1, key::kCmd);
            break;
        // unit type 10 (camera): kExtra = the 48-byte record sub_38C540 filled, +16 / +20 = its two floats, +24 = kParam, kName = 0
        case 0x361680u:  // table[10]
            // 0x00361680
            charge(ctx, 10);
            sw(s0, s1, key::kExtra);
            lwc1(f0, sp, 0x8C);
            swc1(f0, s1, key::kCmd);
            lwc1(f0, sp, 0x88);
            swc1(f0, s1, key::kArg20);
            lw(v0, s4, unit::kParam);
            sh(v0, s1, 24);
            sw(zero, s1, key::kName);
            break;
        // unit type 6 (fade): +16 = 0, +18 = -1
        case 0x3616A8u:  // table[6]
            // 0x003616a8
            charge(ctx, 5);
            sh(zero, s1, key::kCmd);
            v0 = si(-1);
            sh(v0, s1, 18);
            break;
        // unit type 24: a name index and the fields of a zeroed 32-byte frame record
        case 0x3616BCu:  // table[24]
            // 0x003616bc
            charge(ctx, 37);
            lw(v0, s4, unit::kName);
            v0 = sll(v0, 5);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 84);
            a1 = s2;
            jal(ctx, 0x3616D0u, gen::fn_sub_361FE0_00361fe0);
            sw(v0, s1, key::kName);
            a0 = addiu(sp, 0x60);
            a1 = 0;
            a2 = 32;
            jal(ctx, 0x3616E8u, gen::fn_memset_00521408);
            lw(v0, sp, 0x74);
            sb(v0, s1, key::kCmd);
            lw(v0, sp, 0x78);
            sb(v0, s1, 17);
            lw(v0, sp, 0x60);
            sh(v0, s1, key::kArg20);
            lw(v0, sp, 0x64);
            sh(v0, s1, 22);
            lbu(v0, sp, 0x68);
            sb(v0, s1, 24);
            lbu(v0, sp, 0x69);
            sb(v0, s1, 25);
            lbu(v0, sp, 0x6A);
            sb(v0, s1, 26);
            lbu(v0, sp, 0x6B);
            sb(v0, s1, 27);
            lwc1(f0, sp, 0x70);
            swc1(f0, s1, 28);
            lwc1(f0, sp, 0x6C);
            swc1(f0, s1, 32);
            lw(v0, sp, 0x7C);
            sb(v0, s1, 36);
            break;
        // unit type 33 (camera model): +16 = 30 (s16), +24 = 0, +28.. = 640.0, -780.0, 32.0, 0, 35.0 (the default camera)
        case 0x361750u:  // table[33]
            // 0x00361750
            charge(ctx, 14);
            v0 = 30;
            sh(v0, s1, key::kCmd);
            sw(zero, s1, 24);
            v0 = 0x44200000;
            sw(v0, s1, 28);
            v0 = lui(0xC443);
            sw(v0, s1, 32);
            v0 = 0x42000000;
            sw(v0, s1, 36);
            sw(zero, s1, 40);
            v0 = 0x420C0000;
            sw(v0, s1, 44);
            break;
        // unit type 35 (volume): +17 = kParam; channel 1 starts at +20 = 380
        case 0x361788u:  // table[35]
            // 0x00361788
            charge(ctx, 6);
            lw(v0, s4, unit::kParam);
            sb(v0, s1, 17);
            lw(v1, s4, unit::kParam);
            v0 = 1;
            if (v1 == v0) {
                // 0x003617a0
                charge(ctx, 4);
                v0 = 380;
                sh(v0, s1, key::kArg20);
            }
            break;
        // unit type 36 (effect): +17 = kParam
        case 0x3617B0u:  // table[36]
            // 0x003617b0
            charge(ctx, 4);
            lw(v0, s4, unit::kParam);
            sb(v0, s1, 17);
            break;
        // unit type 39 (keyfree): +16 = 0
        case 0x3617C0u:  // table[39]
            // 0x003617c0
            charge(ctx, 3);
            sb(zero, s1, key::kCmd);
            break;
        // unit type 41: +16 = 0 and a path (sub_38D790; the test of the byte just stored is always true)
        case 0x3617CCu:  // table[41]
            // 0x003617cc
            charge(ctx, 5);
            sb(zero, s1, key::kCmd);
            v0 = dsll32(0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                // 0x003617e0
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x3617E4u, gen::fn_sub_38D790_0038d790);
            }
            break;
        // unit type 0: no such unit -- asserts (mt_evtMain.c line 885)
        case 0x3617F4u:  // table[0]
        L_003617f4:
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -10880);  // "mt_evtMain.c"
            a1 = 885;
            jal(ctx, 0x361800u, gen::fn_sub_19D3F0_0019d3f0);
            break;
        // the other unit types: no defaults
        case 0x361808u:  // table[4, 5, 7, 8, 11, 13, 14, 15, 16, 17, 19, 23, 25, 27, 28, 29, 30, 31, 32, 34, 37, 38, 40, 42, 43, 44, 45, 46, 47, 49, 50]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00361808 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        v0 = s1;
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
    goto L_003617f4;
}

// 0x00361830 sub_361830 -- 88 bytes; leaf frame (no stack)
// [evtEdGetCursorKey] (work) -> the key at index kEdKeyIndex + kEdKeyScroll of the editor's unit (0 past the end or
// without a unit). An editor helper (mt_evtMenu.c).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00361830
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, work::kEdUnit);
    if (v0 != 0) {
        // 0x00361848
        charge(ctx, 7);
        lw(v0, v0, 108);
        a2 = 0;
        lw(a1, a0, work::kEdKeyScroll);
        lw(v1, a0, work::kEdKeyIndex);
        v1 = addu(a1, v1);
        for (;;) {
            // 0x0036186c
            charge(ctx, 3);
            at = slt(a2, v1);
            if (at != 0) {
                // 0x00361878
                charge(ctx, 2);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00361864
                    charge(ctx, 2);
                    lw(v0, v0, 76);
                    a2 = addiu(a2, 1);
                    continue;
                }
            }
            break;
        }
    } else {
        // 0x0036183c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00361880 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00361890 sub_361890 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtUnitFreeKey] (unit, key): unlinks the key (sub_361200's code inlined), frees its camera record (class 9; not for
// type-18 units) and its path (class 10, 304 bytes), then the key itself (class 8, 84 bytes) through sub_386B70.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361890
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, key::kPrev);
    if (v1 != 0) {
        // 0x003618bc
        charge(ctx, 2);
        lw(v0, s0, key::kNext);
        sw(v0, v1, 76);
    } else {
        // 0x003618ac
        charge(ctx, 4);
        lw(v0, s0, key::kNext);
        sw(v0, a0, unit::kKeyHead);
    }
    // 0x003618c4
    charge(ctx, 3);
    lw(v1, s0, key::kNext);
    if (v1 != 0) {
        // 0x003618e0
        charge(ctx, 2);
        lw(v0, s0, key::kPrev);
        sw(v0, v1, 80);
    } else {
        // 0x003618d0
        charge(ctx, 4);
        lw(v0, s0, key::kPrev);
        sw(v0, a0, unit::kKeyTail);
    }
    // 0x003618e8
    charge(ctx, 8);
    sw(zero, s0, key::kPrev);
    sw(zero, s0, key::kNext);
    lw(v0, a0, unit::kKeyCount);
    v0 = addiu(v0, -1);
    sw(v0, a0, unit::kKeyCount);
    lw(a1, s0, key::kExtra);
    if (a1 != 0) {
        // 0x00361908
        charge(ctx, 4);
        lw(v1, a0, unit::kType);
        v0 = 18;
        if (v1 != v0) {
            // 0x00361918
            charge(ctx, 5);
            a0 = a1;
            a1 = 9;
            a2 = 0;
            jal(ctx, 0x361924u, gen::fn_sub_386B70_00386b70);
        }
        // 0x0036192c
        charge(ctx, 1);
        sw(zero, s0, key::kExtra);
    }
    // 0x00361930
    charge(ctx, 3);
    lw(a0, s0, key::kPath);
    if (a0 != 0) {
        // 0x0036193c
        charge(ctx, 5);
        a1 = 10;
        a2 = 304;
        jal(ctx, 0x361944u, gen::fn_sub_386B70_00386b70);
        sw(zero, s0, key::kPath);
    }
    // 0x00361950
    charge(ctx, 10);
    a0 = s0;
    a1 = 8;
    a2 = 84;
    jal(ctx, 0x36195Cu, gen::fn_sub_386B70_00386b70);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00361B60 sub_361B60 -- 208 bytes; leaf frame (no stack)
// [evtWorkInsertUnit] (unit, work): links the unit into the work's unit list sorted by the rank of its type (byte
// table 0x69D590: the type itself except 47 / 49 -> 5, 50 -> 6) and counts it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00361b60
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(t0, a1, work::kUnitHead);
    if (t0 != 0) {
        for (;;) {
            // 0x00361bf4
            charge(ctx, 2);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00361b84
            charge(ctx, 11);
            lw(v1, a0, unit::kType);
            a3 = 0x6A0000;
            a3 = addiu(a3, -10864);  // &0x69D590
            v1 = addu(a3, v1);
            lb(a2, v1, 0);
            lw(v1, t0, unit::kType);
            v1 = addu(a3, v1);
            lb(v1, v1, 0);
            at = slt(a2, v1);
            if (at != 0) {
                goto L_00361bb0_3;
            }
            // 0x00361bf0
            charge(ctx, 1);
            lw(t0, t0, unit::kNext);
        }
    L_00361bfc:
        charge(ctx, 2);
        if (t0 == 0) {
            // 0x00361c04
            charge(ctx, 6);
            lw(v1, a1, work::kUnitTail);
            sw(a0, v1, 148);
            lw(v1, a1, work::kUnitTail);
            sw(v1, a0, unit::kPrev);
            sw(zero, a0, unit::kNext);
            sw(a0, a1, work::kUnitTail);
        }
    } else {
        // 0x00361b6c
        charge(ctx, 6);
        sw(a0, a1, work::kUnitHead);
        sw(a0, a1, work::kUnitTail);
        sw(zero, a0, unit::kNext);
        sw(zero, a0, unit::kPrev);
    }
    // 0x00361c1c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lw(v1, a1, work::kUnitCount);
    v1 = addiu(v1, 1);
    sw(v1, a1, work::kUnitCount);
    return;
L_00361bb0_3:
    charge(ctx, 3);
    lw(v1, t0, unit::kPrev);
    if (v1 != 0) {
        // 0x00361bd4
        charge(ctx, 7);
        sw(a0, v1, 148);
        lw(v1, t0, unit::kPrev);
        sw(v1, a0, unit::kPrev);
        sw(t0, a0, unit::kNext);
        sw(a0, t0, unit::kPrev);
    } else {
        // 0x00361bbc
        charge(ctx, 6);
        sw(a0, a1, work::kUnitHead);
        sw(a0, t0, unit::kPrev);
        sw(zero, a0, unit::kPrev);
        sw(t0, a0, unit::kNext);
    }
    goto L_00361bfc;
}

// 0x00361C30 sub_361C30 -- 100 bytes; leaf frame (no stack)
// [evtWorkUnlinkUnit] (unit, work): unlinks the unit from the work's list and uncounts it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00361c30
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a2, a0, unit::kPrev);
    if (a2 != 0) {
        // 0x00361c4c
        charge(ctx, 2);
        lw(v1, a0, unit::kNext);
        sw(v1, a2, unit::kNext);
    } else {
        // 0x00361c3c
        charge(ctx, 4);
        lw(v1, a0, unit::kNext);
        sw(v1, a1, work::kUnitHead);
    }
    // 0x00361c54
    charge(ctx, 3);
    lw(a2, a0, unit::kNext);
    if (a2 != 0) {
        // 0x00361c70
        charge(ctx, 2);
        lw(v1, a0, unit::kPrev);
        sw(v1, a2, unit::kPrev);
    } else {
        // 0x00361c60
        charge(ctx, 4);
        lw(v1, a0, unit::kPrev);
        sw(v1, a1, work::kUnitTail);
    }
    // 0x00361c78 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, a0, unit::kPrev);
    sw(zero, a0, unit::kNext);
    lw(v1, a1, work::kUnitCount);
    v1 = addiu(v1, -1);
    sw(v1, a1, work::kUnitCount);
}

// 0x00361CA0 sub_361CA0 -- 180 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateUnit] (type, work) -> unit: allocates a 156-byte unit (sub_386AE0, class 7), zeroes it, kType = type,
// kName = -1, kResId = 0, kPathMove = 0, kCamMode = -1 for type 48, and inserts it (sub_361B60). 0 when the allocation
// fails.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361CA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361ca0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 156;
    a1 = 7;
    jal(ctx, 0x361CC4u, gen::fn_sub_386AE0_00386ae0);
    s0 = v0;
    if (s0 != 0) {
        // 0x00361ce4
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        a2 = 156;
        jal(ctx, 0x361CF0u, gen::fn_memset_00521408);
        sw(s2, s0, unit::kType);
        v1 = si(-1);
        sw(v1, s0, unit::kName);
        sh(zero, s0, unit::kResId);
        sw(zero, s0, unit::kPathMove);
        v0 = 48;
        if (s2 == v0) {
            // 0x00361d20
            charge(ctx, 1);
            sb(v1, s0, unit::kCamMode);
        } else {
            // 0x00361d18
            charge(ctx, 2);
        }
        // 0x00361d24
        charge(ctx, 5);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x361D2Cu, gen::fn_sub_361B60_00361b60);
        v0 = s0;
    } else {
        // 0x00361cd8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00361d38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00361D60 sub_361D60 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitSetModel] (unit, resId, model): kResId = resId, kModelFlags = the +40 flags of sub_3B5D10(resId) (0 when
// there is no such model), kModel = model. Does nothing for a null unit.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361d60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    if (s1 != 0) {
        // 0x00361d80
        charge(ctx, 6);
        sh(a1, s1, unit::kResId);
        lhu(a0, s1, unit::kResId);
        jal(ctx, 0x361D88u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 == 0) {
            // 0x00361da8
            charge(ctx, 1);
            sw(zero, s1, unit::kModelFlags);
        } else {
            // 0x00361d98
            charge(ctx, 4);
            lw(v1, v0, 40);
            sw(v1, s1, unit::kModelFlags);
        }
        // 0x00361dac
        charge(ctx, 1);
        sw(s0, s1, unit::kModel);
    }
    // 0x00361db0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00361DD0 sub_361DD0 -- 268 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateModelUnit] (type, work, resId, model) -> unit: sub_361CA0 and sub_361D60 inlined.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361DD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361dd0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    a0 = 156;
    a1 = 7;
    jal(ctx, 0x361E04u, gen::fn_sub_386AE0_00386ae0);
    s0 = v0;
    if (s0 != 0) {
        // 0x00361e24
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        a2 = 156;
        jal(ctx, 0x361E30u, gen::fn_memset_00521408);
        sw(s4, s0, unit::kType);
        v1 = si(-1);
        sw(v1, s0, unit::kName);
        sh(zero, s0, unit::kResId);
        sw(zero, s0, unit::kPathMove);
        v0 = 48;
        if (s4 == v0) {
            // 0x00361e60
            charge(ctx, 1);
            sb(v1, s0, unit::kCamMode);
        } else {
            // 0x00361e58
            charge(ctx, 2);
        }
        // 0x00361e64
        charge(ctx, 4);
        a0 = s0;
        a1 = s3;
        jal(ctx, 0x361E6Cu, gen::fn_sub_361B60_00361b60);
    } else {
        // 0x00361e18
        charge(ctx, 3);
        s0 = 0;
    }
    // 0x00361e74
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00361e7c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00361e84
            charge(ctx, 6);
            sh(s2, s0, unit::kResId);
            lhu(a0, s0, unit::kResId);
            jal(ctx, 0x361E8Cu, gen::fn_sub_3B5D10_003b5d10);
            if (v0 == 0) {
                // 0x00361eac
                charge(ctx, 1);
                sw(zero, s0, unit::kModelFlags);
            } else {
                // 0x00361e9c
                charge(ctx, 4);
                lw(v0, v0, 40);
                sw(v0, s0, unit::kModelFlags);
            }
            // 0x00361eb0
            charge(ctx, 1);
            sw(s1, s0, unit::kModel);
        }
    }
    // 0x00361eb4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s0;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00361EE0 sub_361EE0 -- 52 bytes; leaf frame (no stack)
// [evtCountUnitsOfType] (type, work) -> the number of units of that type.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00361ee0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0;
    lw(a1, a1, 132);
    for (;;) {
        // 0x00361f04
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00361ef0
        charge(ctx, 3);
        lw(v1, a1, 0);
        if (v1 == a0) {
            // 0x00361efc
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        // 0x00361f00
        charge(ctx, 1);
        lw(a1, a1, 148);
    }
    // 0x00361f0c
    charge(ctx, 2);
}

// 0x00361F20 sub_361F20 -- 52 bytes; leaf frame (no stack)
// [evtCountUnits] (work) -> the number of units in the work's list.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00361f20
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0;
    lw(v1, a0, work::kUnitHead);
    for (;;) {
        // 0x00361f38
        charge(ctx, 5);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00361f30
        charge(ctx, 2);
        v0 = addiu(v0, 1);
        lw(v1, v1, unit::kNext);
    }
    // 0x00361f4c
    charge(ctx, 2);
}

// 0x00361F60 sub_361F60 -- 124 bytes; leaf frame (no stack)
// [evtCountSoundKeys] (kind, work) -> the summed key counts of the sound units: kind 2 = all units except types 5 and
// 19, kind 3 = types 5 and 19 only; other kinds 0. (mt_evtLoadSave.c's sizes.)
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00361f60
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0;
    lw(t1, a1, work::kUnitHead);
    t0 = 2;
    a3 = 5;
    a2 = 19;
    a1 = 3;
    for (;;) {
        // 0x00361fcc
        charge(ctx, 2);
        if (t1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00361f80
        charge(ctx, 2);
        if (a0 != t0) {
            // 0x00361fa4
            charge(ctx, 2);
            if (a0 == a1) {
                // 0x00361fac
                charge(ctx, 3);
                lw(v1, t1, unit::kType);
                if (v1 == a3) {
                L_00361fc0:
                    charge(ctx, 2);
                    lw(v1, t1, unit::kKeyCount);
                    v0 = addu(v0, v1);
                } else {
                    // 0x00361fb8
                    charge(ctx, 2);
                    if (v1 == a2) {
                        goto L_00361fc0;
                    }
                }
            }
        } else {
            // 0x00361f88
            charge(ctx, 3);
            lw(v1, t1, unit::kType);
            if (v1 != a3) {
                // 0x00361f94
                charge(ctx, 2);
                if (v1 != a2) {
                    goto L_00361fc0;
                }
                // 0x00361f9c
                charge(ctx, 2);
            }
        }
        // 0x00361fc8
        charge(ctx, 1);
        lw(t1, t1, unit::kNext);
    }
    // 0x00361fd4
    charge(ctx, 2);
}

// 0x00361FE0 sub_361FE0 -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtAddName] (name, work) -> index: the index of `name` in the work's name table, or appends it (strcpy; asserts
// when the table already holds one, line 1426: one name per event in practice).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_361FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00361fe0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (s2 == 0) {
        // 0x00362004
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 1419;
        jal(ctx, 0x362010u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00362018
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x00362020
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 1393;
        jal(ctx, 0x36202Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00362034
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x0036206c
        charge(ctx, 4);
        lw(v0, s1, work::kNameCount);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00362040
        charge(ctx, 8);
        v0 = sll(s0, 5);
        v0 = addu(s1, v0);
        a0 = s2;
        a1 = addiu(v0, 84);
        jal(ctx, 0x362050u, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            goto L_00362060_6;
        }
        // 0x00362068
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0036207c
    charge(ctx, 1);
    s0 = si(-1);
L_00362080:
    charge(ctx, 2);
    if (i64(s0) < 0) {
        // 0x00362094
        charge(ctx, 3);
        lw(s0, s1, work::kNameCount);
        if (i64(s0) > 0) {
            // 0x003620a0
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -10880);  // "mt_evtMain.c"
            a1 = 1426;
            jal(ctx, 0x3620ACu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003620b4
        charge(ctx, 10);
        v0 = sll(s0, 5);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 84);
        a1 = s2;
        jal(ctx, 0x3620C4u, gen::fn_strcpy_00524270);
        lw(v0, s1, work::kNameCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, work::kNameCount);
        v0 = s0;
    } else {
        // 0x00362088
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x003620dc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00362060_6:
    charge(ctx, 2);
    goto L_00362080;
}

// 0x00362100 nullsub_114 -- 8 bytes; leaf frame (no stack)
// An empty callback of sub_361980's unit deletion (debug hook).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void nullsub_114(EEContext& ctx) {
    using namespace hg;
    // 0x00362100
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00362110 nullsub_115 -- 8 bytes; leaf frame (no stack)
// An empty callback of sub_361980's unit deletion (debug hook).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void nullsub_115(EEContext& ctx) {
    using namespace hg;
    // 0x00362110
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00362120 sub_362120 -- 284 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtSetModelsPaused] (resume, frame, work): for every model unit (types 1 / 48) with a resource, sub_3B8310(resId,
// !resume); then for every field object (sub_3B5D50(7) list) likewise. Holds or releases the actors while the
// timeline stops (sub_36D030).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00362120
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a2;
    jal(ctx, 0x362138u, gen::fn_sub_3B5D00_003b5d00);
    if (v0 != 0) {
        // 0x00362148
        charge(ctx, 3);
        lw(s1, s1, 132);
        for (;;) {
            // 0x003621c8
            charge(ctx, 2);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00362154
            charge(ctx, 4);
            lw(v1, s1, 0);
            v0 = 1;
            if (v1 != v0) {
                // 0x00362164
                charge(ctx, 3);
                v0 = 48;
                if (v1 == v0) {
                    goto L_00362170;
                }
                goto L_003621c4;
            }
        L_00362170:
            charge(ctx, 3);
            lhu(a0, s1, 12);
            if (a0 != 0) {
                // 0x0036217c
                charge(ctx, 4);
                lw(v0, s1, 100);
                a1 = 1;
                if (v0 != a1) {
                    // 0x003621a0
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x003621b8
                        charge(ctx, 3);
                        a1 = 0;
                        jal(ctx, 0x3621BCu, gen::fn_sub_3B8310_003b8310);
                    } else {
                        // 0x003621a8
                        charge(ctx, 4);
                        jal(ctx, 0x3621A8u, gen::fn_sub_3B8310_003b8310);
                    }
                } else {
                    // 0x0036218c
                    charge(ctx, 5);
                    a1 = 0;
                    jal(ctx, 0x362190u, gen::fn_sub_3B8310_003b8310);
                }
            }
        L_003621c4:
            charge(ctx, 1);
            lw(s1, s1, 148);
        }
        // 0x003621d0
        charge(ctx, 6);
        a0 = 7;
        jal(ctx, 0x3621D4u, gen::fn_sub_3B5D50_003b5d50);
        s1 = v0;
        for (;;) {
            // 0x0036221c
            charge(ctx, 2);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003621e8
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x00362208
                charge(ctx, 4);
                lhu(a0, s1, 0);
                a1 = 0;
                jal(ctx, 0x362210u, gen::fn_sub_3B8310_003b8310);
            } else {
                // 0x003621f0
                charge(ctx, 6);
                lhu(a0, s1, 0);
                a1 = 1;
                jal(ctx, 0x3621F8u, gen::fn_sub_3B8310_003b8310);
            }
            // 0x00362218
            charge(ctx, 1);
            lw(s1, s1, 248);
        }
    }
    // 0x00362224 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00362240 sub_362240 -- 80 bytes; frame 0x10: ra sp+0x0
// [evtApplyStopState] (work): sub_362120(0, frame, work) when kStopped == 1, else sub_362120(1, ...).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00362240
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lw(v0, a0, work::kStopped);
    a0 = 1;
    if (v0 != a0) {
        // 0x00362274
        charge(ctx, 3);
        lw(a1, a2, 24);
        jal(ctx, 0x362278u, gen::fn_sub_362120_00362120);
    } else {
        // 0x0036225c
        charge(ctx, 6);
        a0 = 0;
        lw(a1, a2, 24);
        jal(ctx, 0x362264u, gen::fn_sub_362120_00362120);
    }
    // 0x00362280 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00362290 sub_362290 -- 128 bytes; leaf frame (no stack)
// [evtFindNextMessageKey] (work) -> the message-unit key (type 2 units) with the smallest frame after kFrame, or 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362290(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00362290
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0;
    v1 = 0x10000;
    a3 = v1 | 0x869F;
    lw(t0, a0, work::kUnitHead);
    a2 = 2;
    for (;;) {
        // 0x00362300
        charge(ctx, 2);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003622ac
        charge(ctx, 3);
        lw(v1, t0, unit::kType);
        if (v1 == a2) {
            // 0x003622b8
            charge(ctx, 3);
            lw(t1, t0, unit::kKeyHead);
            for (;;) {
                // 0x003622f4
                charge(ctx, 2);
                if (t1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003622c4
                charge(ctx, 5);
                lhu(a1, t1, key::kFrame);
                lw(v1, a0, work::kFrame);
                at = slt(v1, a1);
                if (at != 0) {
                    // 0x003622d8
                    charge(ctx, 4);
                    v1 = subu(a1, v1);
                    at = slt(v1, a3);
                    if (at != 0) {
                        // 0x003622e8
                        charge(ctx, 2);
                        a3 = v1;
                        v0 = t1;
                    }
                }
                // 0x003622f0
                charge(ctx, 1);
                lw(t1, t1, key::kNext);
            }
        }
        // 0x003622fc
        charge(ctx, 1);
        lw(t0, t0, unit::kNext);
    }
    // 0x00362308
    charge(ctx, 2);
}

// 0x00362310 sub_362310 -- 128 bytes; leaf frame (no stack)
// [evtFindPrevMessageKey] (work) -> the message-unit key with the greatest frame before kFrame, or 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362310(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00362310
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0;
    v1 = 0x10000;
    a3 = v1 | 0x869F;
    lw(t0, a0, work::kUnitHead);
    a2 = 2;
    for (;;) {
        // 0x00362380
        charge(ctx, 2);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036232c
        charge(ctx, 3);
        lw(v1, t0, unit::kType);
        if (v1 == a2) {
            // 0x00362338
            charge(ctx, 3);
            lw(t1, t0, unit::kKeyHead);
            for (;;) {
                // 0x00362374
                charge(ctx, 2);
                if (t1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00362344
                charge(ctx, 5);
                lhu(a1, t1, key::kFrame);
                lw(v1, a0, work::kFrame);
                at = slt(a1, v1);
                if (at != 0) {
                    // 0x00362358
                    charge(ctx, 4);
                    v1 = subu(v1, a1);
                    at = slt(v1, a3);
                    if (at != 0) {
                        // 0x00362368
                        charge(ctx, 2);
                        a3 = v1;
                        v0 = t1;
                    }
                }
                // 0x00362370
                charge(ctx, 1);
                lw(t1, t1, key::kNext);
            }
        }
        // 0x0036237c
        charge(ctx, 1);
        lw(t0, t0, unit::kNext);
    }
    // 0x00362388
    charge(ctx, 2);
}

// 0x00362F20 sub_362F20 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtToggleCamera] (work): with a stage loaded (sub_3B5D00), switches between the event cameras 0x1E58 and 0x1E59
// (sub_38A0B0 / sub_38A0C0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00362f20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x362F30u, gen::fn_sub_3B5D00_003b5d00);
    if (v0 != 0) {
        // 0x00362f40
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x362F44u, gen::fn_sub_38A0B0_0038a0b0);
        a1 = 1;
        if (v0 == a1) {
            // 0x00362f7c
            charge(ctx, 4);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x362F84u, gen::fn_sub_38A0C0_0038a0c0);
        } else {
            // 0x00362f58
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00362f68
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x362F6Cu, gen::fn_sub_38A0C0_0038a0c0);
            } else {
                // 0x00362f60
                charge(ctx, 2);
            }
        }
    }
    // 0x00362f8c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00362FA0 sub_362FA0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtCloseMessage] (work): with a scene, closes the work's message when one is open (sub_39EEE0 / sub_39F350).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00362fa0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, work::kScene);
    if (v1 != 0) {
        // 0x00362fbc
        charge(ctx, 5);
        a0 = addiu(s0, 2092);
        jal(ctx, 0x362FC0u, gen::fn_sub_39EEE0_0039eee0);
        if (v0 != 0) {
            // 0x00362fd0
            charge(ctx, 3);
            a0 = addiu(s0, 2092);
            jal(ctx, 0x362FD4u, gen::fn_sub_39F350_0039f350);
        }
    }
    // 0x00362fdc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00362FF0 sub_362FF0 -- 52 bytes; frame 0x10: ra sp+0x0
// [evtDrawMetrics] (work): draws the memory overlay (sub_386D50) while kMetrics is set.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_362FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00362ff0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00363000
        charge(ctx, 3);
        lw(v1, a0, work::kMetrics);
        if (v1 != 0) {
            // 0x0036300c
            charge(ctx, 2);
            jal(ctx, 0x36300Cu, gen::fn_sub_386D50_00386d50);
        }
    }
    // 0x00363014 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00363030 sub_363030 -- 2212 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyEventKey] (unit, key, frame, work): the one-shot keys of the "event" unit types, run by sub_366AC0 for every
// key whose frame (or [frame, frame + hold)) contains the current frame. A switch on the unit type (jump tables
// 0x7BA3E0 / 0x7BA3C0): 5 adx sound (channel kind at +18: 0 / 2 per event, 1 / 3 fixed; "play AdxSe start frame=%d"),
// 7 screen filter on / off (sub_3BCBF0 / sub_3BCC80, kFlagFilter), 19 sound commands (+16: 0 sub_395270, 1 sub_3952B0,
// 2 sub_108FD0(120), 3 nullsub_27, 6 sub_108F70; others assert, line 2646), 28 sub_103C30 / sub_103CB0, 29 start a
// sub task (sub_10BC20; kFlagSubTask), 41 sub_39E1B0, 42 / 44 / 45 / 46 comu branches that pick the jump frame from the
// key's s16 table by the calendar or link state and request the jump (kJumpFrame / kJumpRequest), 50 sub_10A4E0. Sound
// keys are skipped under kFlagNoSound.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_363030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00363030
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a3;
    lw(v1, a0, 0);
    a0 = 46;
    if (v1 == a0) {
        // 0x00363794
        charge(ctx, 3);
        lhu(v1, s3, key::kFrame);
        if (a2 == v1) {
            // 0x003637a0
            charge(ctx, 8);
            jal(ctx, 0x3637A0u, gen::fn_sub_16DD40_0016dd40);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            s1 = 0;
            v1 = 255;
            if (a0 != v1) {
                // 0x003637c0
                charge(ctx, 5);
                jal(ctx, 0x3637C0u, gen::fn_sub_3C2EE0_003c2ee0);
                s0 = v0;
                if (s0 != 0) {
                    // 0x003637d4
                    charge(ctx, 1);
                    s1 = 1;
                }
                // 0x003637d8
                charge(ctx, 3);
                v1 = 1;
                if (s1 != v1) {
                    // 0x003638a4
                    charge(ctx, 1);
                    lh(v1, s3, 18);
                } else {
                    // 0x003637e4
                    charge(ctx, 11);
                    a0 = addiu(s2, 2092);
                    a1 = 7;
                    lw(a2, s0, 8);
                    jal(ctx, 0x3637F0u, gen::fn_sub_39EEF0_0039eef0);
                    lw(a0, s0, 4);
                    lw(a1, s0, 8);
                    jal(ctx, 0x363800u, gen::fn_sub_3C4130_003c4130);
                    if (v0 != 0) {
                        // 0x00363810
                        charge(ctx, 5);
                        a0 = addiu(s2, 2092);
                        a1 = 8;
                        a2 = v0;
                        jal(ctx, 0x36381Cu, gen::fn_sub_39EF30_0039ef30);
                    }
                    // 0x00363824
                    charge(ctx, 9);
                    a0 = 0;
                    a1 = addiu(s0, 12);
                    jal(ctx, 0x36382Cu, gen::fn_sub_3BEA20_003bea20);
                    a0 = v0 & 0xFF;
                    jal(ctx, 0x363838u, gen::fn_sub_3C3F40_003c3f40);
                    if (v0 != 0) {
                        // 0x00363848
                        charge(ctx, 5);
                        a0 = addiu(s2, 2092);
                        a1 = 9;
                        a2 = v0;
                        jal(ctx, 0x363854u, gen::fn_sub_39EF30_0039ef30);
                    }
                    // 0x0036385c
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x5E);
                    jal(ctx, 0x363860u, gen::fn_sub_172C50_00172c50);
                    if (v0 != 0) {
                        // 0x00363870
                        charge(ctx, 6);
                        lh(a0, sp, 0x5E);
                        jal(ctx, 0x363874u, gen::fn_sub_3C3FE0_003c3fe0);
                        a2 = v0;
                        if (a2 != 0) {
                            // 0x00363888
                            charge(ctx, 4);
                            a0 = addiu(s2, 2092);
                            a1 = 10;
                            jal(ctx, 0x363890u, gen::fn_sub_39EF30_0039ef30);
                        }
                    }
                    // 0x00363898
                    charge(ctx, 3);
                    lh(v1, s3, key::kCmd);
                }
                // 0x003638a8
                charge(ctx, 3);
                sw(v1, s2, work::kJumpFrame);
                v1 = 1;
                sw(v1, s2, work::kJumpRequest);
            }
        }
    } else {
        // 0x00363060
        charge(ctx, 3);
        a0 = 45;
        if (v1 == a0) {
            // 0x00363680
            charge(ctx, 3);
            lhu(v1, s3, key::kFrame);
            if (a2 == v1) {
                // 0x0036368c
                charge(ctx, 3);
                lb(v1, s3, key::kCmd);
                if (v1 != 0) {
                    // 0x00363698
                    charge(ctx, 15);
                    s1 = si(-1);
                    s0 = 0;
                    a0 = addiu(v1, -1);
                    jal(ctx, 0x3636A4u, gen::fn_sub_16DE50_0016de50);
                    a0 = v0 & 0xFF;
                    lbu(v1, s3, key::kArg20);
                    sw(v1, sp, 0x50);
                    lbu(v1, s3, 21);
                    sw(v1, sp, 0x54);
                    lbu(v1, s3, 22);
                    sw(v1, sp, 0x58);
                    a1 = 0;
                    for (;;) {
                        // 0x003636fc
                        charge(ctx, 3);
                        v1 = slti(a1, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003636d4
                        charge(ctx, 6);
                        v1 = sll(a1, 2);
                        v1 = addu(v1, sp);
                        lw(v1, v1, 80);
                        v1 = slt(v1, a0);
                        if (v1 == 0) {
                            goto L_003636ec_98;
                        }
                        // 0x003636f8
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                L_00363708:
                    charge(ctx, 3);
                    v1 = si(-1);
                    if (s1 == v1) {
                        // 0x0036377c
                        charge(ctx, 1);
                        lh(s0, s3, 30);
                    } else {
                        // 0x00363714
                        charge(ctx, 3);
                        v1 = 2;
                        if (s1 == v1) {
                            // 0x00363754
                            charge(ctx, 3);
                            lh(s0, s3, 28);
                        } else {
                            // 0x00363720
                            charge(ctx, 3);
                            v1 = 1;
                            if (s1 == v1) {
                                // 0x00363748
                                charge(ctx, 3);
                                lh(s0, s3, 26);
                            } else {
                                // 0x0036372c
                                charge(ctx, 2);
                                if (s1 == 0) {
                                    // 0x0036373c
                                    charge(ctx, 3);
                                    lh(s0, s3, 24);
                                } else {
                                    // 0x00363734
                                    charge(ctx, 2);
                                    // 0x00363760
                                    charge(ctx, 7);
                                    a0 = 0x6A0000;
                                    a0 = addiu(a0, -10880);  // "mt_evtMain.c"
                                    a1 = 2849;
                                    jal(ctx, 0x36376Cu, gen::fn_sub_19D3F0_0019d3f0);
                                }
                            }
                        }
                    }
                    // 0x00363780
                    charge(ctx, 5);
                    sw(s0, s2, work::kJumpFrame);
                    v1 = 1;
                    sw(v1, s2, work::kJumpRequest);
                }
            }
        } else {
            // 0x0036306c
            charge(ctx, 3);
            a0 = 44;
            if (v1 == a0) {
                // 0x00363608
                charge(ctx, 3);
                lhu(v1, s3, key::kFrame);
                if (a2 == v1) {
                    // 0x00363614
                    charge(ctx, 7);
                    jal(ctx, 0x363614u, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    v1 = 255;
                    if (a0 != v1) {
                        // 0x00363630
                        charge(ctx, 11);
                        jal(ctx, 0x363630u, gen::fn_sub_16DBA0_0016dba0);
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = sll(v1, 2);
                        a0 = addu(v0, v1);
                        jal(ctx, 0x363648u, gen::fn_sub_395230_00395230);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x00363668
                            charge(ctx, 1);
                            lh(v1, s3, 18);
                        } else {
                            // 0x0036365c
                            charge(ctx, 3);
                            lh(v1, s3, key::kCmd);
                        }
                        // 0x0036366c
                        charge(ctx, 5);
                        sw(v1, s2, work::kJumpFrame);
                        v1 = 1;
                        sw(v1, s2, work::kJumpRequest);
                    }
                }
            } else {
                // 0x00363078
                charge(ctx, 3);
                a0 = 42;
                if (v1 == a0) {
                    // 0x00363560
                    charge(ctx, 3);
                    lhu(v1, s3, key::kFrame);
                    if (a2 == v1) {
                        // 0x0036356c
                        charge(ctx, 8);
                        a0 = 1;
                        jal(ctx, 0x363570u, gen::fn_sub_16C920_0016c920);
                        v1 = v0 & 0xFFFF;
                        a1 = si(-1);
                        at = sltiu(v1, 6);
                        if (at != 0) {
                            // 0x0036358c
                            charge(ctx, 7);
                            a0 = 0x7C0000;
                            a0 = addiu(a0, -23616);  // &0x7BA3C0
                            v1 = sll(v1, 2);
                            v1 = addu(v1, a0);
                            lw(v1, v1, 0);
                            switch (v1.u()) {
                            case 0x3635A8u:  // table[0]
                                // 0x003635a8
                                charge(ctx, 3);
                                lh(a1, s3, 22);
                                break;
                            case 0x3635B4u:  // table[1]
                                // 0x003635b4
                                charge(ctx, 3);
                                lh(a1, s3, 24);
                                break;
                            case 0x3635C0u:  // table[2]
                                // 0x003635c0
                                charge(ctx, 3);
                                lh(a1, s3, 26);
                                break;
                            case 0x3635CCu:  // table[3]
                                // 0x003635cc
                                charge(ctx, 3);
                                lh(a1, s3, key::kArg20);
                                break;
                            case 0x3635D8u:  // table[4]
                                // 0x003635d8
                                charge(ctx, 3);
                                lh(a1, s3, 18);
                                break;
                            case 0x3635E4u:  // table[5]
                                // 0x003635e4
                                charge(ctx, 1);
                                lh(a1, s3, key::kCmd);
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, v1.u());
                                return;
                            }
                        }
                        // 0x003635e8
                        charge(ctx, 3);
                        v1 = si(-1);
                        if (a1 != v1) {
                            // 0x003635f4
                            charge(ctx, 5);
                            sw(a1, s2, work::kJumpFrame);
                            v1 = 1;
                            sw(v1, s2, work::kJumpRequest);
                        }
                    }
                } else {
                    // 0x00363084
                    charge(ctx, 3);
                    a0 = 32;
                    if (v1 != a0) {
                        // 0x00363090
                        charge(ctx, 3);
                        a0 = 29;
                        if (v1 == a0) {
                            // 0x00363508
                            charge(ctx, 3);
                            lw(a0, s2, work::kSubTask);
                            if (a0 != 0) {
                                // 0x00363514
                                charge(ctx, 5);
                                jal(ctx, 0x363514u, gen::fn_kwlnTaskExists_00195460);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x00363528
                                    charge(ctx, 3);
                                    lw(a0, s2, work::kSubTask);
                                    jal(ctx, 0x36352Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                }
                                // 0x00363534
                                charge(ctx, 1);
                                sw(zero, s2, work::kSubTask);
                            }
                            // 0x00363538
                            charge(ctx, 10);
                            lw(a0, s2, work::kTask);
                            lh(a1, s3, key::kCmd);
                            jal(ctx, 0x363540u, gen::fn_sub_10BC20_0010bc20);
                            sw(v0, s2, work::kSubTask);
                            lw(v1, s2, work::kFlags);
                            v1 = v1 | 0x4000;
                            sw(v1, s2, work::kFlags);
                        } else {
                            // 0x0036309c
                            charge(ctx, 3);
                            a0 = 28;
                            if (v1 == a0) {
                                // 0x003634b4
                                charge(ctx, 3);
                                lhu(v1, s3, key::kFrame);
                                if (a2 == v1) {
                                    // 0x003634c0
                                    charge(ctx, 3);
                                    lb(a0, s3, key::kCmd);
                                    if (a0 != 0) {
                                        // 0x003634ec
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (a0 == v1) {
                                            // 0x003634f8
                                            charge(ctx, 4);
                                            jal(ctx, 0x3634F8u, gen::fn_sub_103CB0_00103cb0);
                                        }
                                    } else {
                                        // 0x003634cc
                                        charge(ctx, 8);
                                        lh(a0, s3, key::kArg20);
                                        lh(a1, s3, 22);
                                        lh(a2, s3, 24);
                                        lh(a3, s3, 26);
                                        jal(ctx, 0x3634DCu, gen::fn_sub_103C30_00103c30);
                                    }
                                }
                            } else {
                                // 0x003630a8
                                charge(ctx, 3);
                                a0 = 7;
                                if (v1 == a0) {
                                    // 0x0036344c
                                    charge(ctx, 3);
                                    lhu(v1, s3, key::kLength);
                                    if (v1 == 0) {
                                        // 0x00363458
                                        charge(ctx, 3);
                                        lh(v1, s3, key::kCmd);
                                        if (v1 != 0) {
                                            goto L_00363484;
                                        }
                                        // 0x00363464
                                        charge(ctx, 8);
                                        lw(v1, s2, work::kFlags);
                                        v0 = si(-3);
                                        v0 = v1 & v0;
                                        sw(v0, s2, work::kFlags);
                                        jal(ctx, 0x363474u, gen::fn_sub_3BCC80_003bcc80);
                                        // 0x003638b4 (the shared epilogue, written out on this path)
                                        charge(ctx, 8);
                                        ld(ra, sp, 0x40);
                                        lq(s3, sp, 0x30);
                                        lq(s2, sp, 0x20);
                                        lq(s1, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x60);
                                        return;
                                    }
                                L_00363484:
                                    charge(ctx, 3);
                                    lhu(v1, s3, key::kFrame);
                                    if (a2 == v1) {
                                        // 0x00363490
                                        charge(ctx, 9);
                                        lw(v0, s2, work::kFlags);
                                        v0 = v0 | 0x2;
                                        sw(v0, s2, work::kFlags);
                                        lhu(a0, s3, key::kLength);
                                        lh(a1, s3, key::kCmd);
                                        jal(ctx, 0x3634A4u, gen::fn_sub_3BCBF0_003bcbf0);
                                    }
                                } else {
                                    // 0x003630b4
                                    charge(ctx, 3);
                                    a0 = 19;
                                    if (v1 == a0) {
                                        // 0x00363360
                                        charge(ctx, 6);
                                        lw(v1, s2, work::kFlags);
                                        v1 = v1 & 0x10;
                                        a0 = sltu(0, v1);
                                        v1 = 1;
                                        if (a0 != v1) {
                                            // 0x00363378
                                            charge(ctx, 3);
                                            lhu(v1, s3, key::kFrame);
                                            if (a2 == v1) {
                                                // 0x00363384
                                                charge(ctx, 4);
                                                lh(v1, s3, key::kCmd);
                                                at = sltiu(v1, 7);
                                                if (at == 0) {
                                                    // 0x00363430
                                                    charge(ctx, 7);
                                                    a0 = 0x6A0000;
                                                    a0 = addiu(a0, -10880);  // "mt_evtMain.c"
                                                    a1 = 2646;
                                                    jal(ctx, 0x36343Cu, gen::fn_sub_19D3F0_0019d3f0);
                                                } else {
                                                    // 0x00363394
                                                    charge(ctx, 7);
                                                    a0 = 0x7C0000;
                                                    a0 = addiu(a0, -23584);  // &0x7BA3E0
                                                    v1 = sll(v1, 2);
                                                    v1 = addu(v1, a0);
                                                    lw(v1, v1, 0);
                                                    switch (v1.u()) {
                                                    case 0x3633B0u:  // table[0]
                                                        // 0x003633b0
                                                        charge(ctx, 5);
                                                        lh(a0, s3, 18);
                                                        jal(ctx, 0x3633B4u, gen::fn_sub_395270_00395270);
                                                        break;
                                                    case 0x3633C4u:  // table[1]
                                                        // 0x003633c4
                                                        charge(ctx, 9);
                                                        a0 = s2;
                                                        jal(ctx, 0x3633C8u, gen::fn_sub_386E10_00386e10);
                                                        lh(a1, s3, 18);
                                                        a0 = v0;
                                                        jal(ctx, 0x3633D8u, gen::fn_sub_3952B0_003952b0);
                                                        break;
                                                    case 0x3633E8u:  // table[2]
                                                        // 0x003633e8
                                                        charge(ctx, 5);
                                                        a0 = 120;
                                                        jal(ctx, 0x3633ECu, gen::fn_sub_108FD0_00108fd0);
                                                        break;
                                                    case 0x3633FCu:  // table[3]
                                                        // 0x003633fc
                                                        charge(ctx, 9);
                                                        a0 = s2;
                                                        jal(ctx, 0x363400u, gen::fn_sub_386E10_00386e10);
                                                        lh(a1, s3, 18);
                                                        a0 = v0;
                                                        jal(ctx, 0x363410u, gen::fn_nullsub_27_003952a0);
                                                        break;
                                                    case 0x363420u:  // table[6]
                                                        // 0x00363420
                                                        charge(ctx, 4);
                                                        jal(ctx, 0x363420u, gen::fn_sub_108F70_00108f70);
                                                        break;
                                                    case 0x3638B4u:  // table[4, 5]
                                                        break;
                                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                                        tail(ctx, v1.u());
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        // 0x003630c0
                                        charge(ctx, 3);
                                        a0 = 50;
                                        if (v1 == a0) {
                                            // 0x003632f8
                                            charge(ctx, 3);
                                            lhu(v1, s3, key::kFrame);
                                            if (a2 == v1) {
                                                // 0x00363304
                                                charge(ctx, 4);
                                                lb(v1, s3, key::kCmd);
                                                a0 = 1;
                                                if (v1 == a0) {
                                                    // 0x00363340
                                                    charge(ctx, 8);
                                                    lb(a1, s3, 17);
                                                    lb(a2, s3, 18);
                                                    lb(a3, s3, 19);
                                                    a0 = 0;
                                                    jal(ctx, 0x363350u, gen::fn_sub_10A4E0_0010a4e0);
                                                } else {
                                                    // 0x00363314
                                                    charge(ctx, 2);
                                                    if (v1 == 0) {
                                                        // 0x00363324
                                                        charge(ctx, 7);
                                                        lb(a1, s3, 17);
                                                        lb(a2, s3, 18);
                                                        lb(a3, s3, 19);
                                                        jal(ctx, 0x363330u, gen::fn_sub_10A4E0_0010a4e0);
                                                    } else {
                                                        // 0x0036331c
                                                        charge(ctx, 2);
                                                    }
                                                }
                                            }
                                        } else {
                                            // 0x003630cc
                                            charge(ctx, 3);
                                            a0 = 5;
                                            if (v1 == a0) {
                                                // 0x003631f8
                                                charge(ctx, 6);
                                                lw(v1, s2, work::kFlags);
                                                v1 = v1 & 0x10;
                                                a0 = sltu(0, v1);
                                                v1 = 1;
                                                if (a0 != v1) {
                                                    // 0x00363210
                                                    charge(ctx, 3);
                                                    lhu(v1, s3, key::kFrame);
                                                    if (a2 == v1) {
                                                        // 0x0036321c
                                                        charge(ctx, 9);
                                                        a0 = 0x6A0000;
                                                        a0 = addiu(a0, -10688);  // "play AdxSe start frame=%d\n"
                                                        a1 = a2;
                                                        jal(ctx, 0x363228u, gen::fn_printf_005225a8);
                                                        lb(a1, s3, 18);
                                                        a0 = 3;
                                                        if (a1 == a0) {
                                                            // 0x003632e0
                                                            charge(ctx, 6);
                                                            lh(a1, s3, key::kCmd);
                                                            a0 = 4;
                                                            jal(ctx, 0x3632E8u, gen::fn_sub_395350_00395350);
                                                        } else {
                                                            // 0x00363240
                                                            charge(ctx, 3);
                                                            v1 = 2;
                                                            if (a1 == v1) {
                                                                // 0x003632b8
                                                                charge(ctx, 10);
                                                                a0 = s2;
                                                                jal(ctx, 0x3632BCu, gen::fn_sub_386E10_00386e10);
                                                                lh(a1, s3, key::kCmd);
                                                                a0 = v0;
                                                                a2 = 4;
                                                                jal(ctx, 0x3632D0u, gen::fn_sub_3952D0_003952d0);
                                                            } else {
                                                                // 0x0036324c
                                                                charge(ctx, 3);
                                                                v1 = 1;
                                                                if (a1 == v1) {
                                                                    // 0x003632a4
                                                                    charge(ctx, 5);
                                                                    lh(a1, s3, key::kCmd);
                                                                    jal(ctx, 0x3632A8u, gen::fn_sub_395350_00395350);
                                                                } else {
                                                                    // 0x00363258
                                                                    charge(ctx, 2);
                                                                    if (a1 == 0) {
                                                                        // 0x00363268
                                                                        charge(ctx, 15);
                                                                        a0 = s2;
                                                                        jal(ctx, 0x36326Cu, gen::fn_sub_386E10_00386e10);
                                                                        lh(a1, s3, key::kCmd);
                                                                        a0 = v0;
                                                                        a2 = 3;
                                                                        jal(ctx, 0x363280u, gen::fn_sub_3952D0_003952d0);
                                                                        lh(a1, s3, key::kCmd);
                                                                        a0 = 0x6A0000;
                                                                        a0 = addiu(a0, -10656);  // "play adx se %d\n"
                                                                        jal(ctx, 0x363294u, gen::fn_printf_005225a8);
                                                                    } else {
                                                                        // 0x00363260
                                                                        charge(ctx, 2);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                // 0x003630d8
                                                charge(ctx, 3);
                                                a0 = 41;
                                                if (v1 == a0) {
                                                    // 0x003631d8
                                                    charge(ctx, 3);
                                                    lhu(v1, s3, key::kFrame);
                                                    if (a2 == v1) {
                                                        // 0x003631e4
                                                        charge(ctx, 5);
                                                        a0 = s2;
                                                        jal(ctx, 0x3631E8u, gen::fn_sub_39E1B0_0039e1b0);
                                                    }
                                                } else {
                                                    // 0x003630e4
                                                    charge(ctx, 3);
                                                    a0 = 18;
                                                    if (v1 != a0) {
                                                        // 0x003630f0
                                                        charge(ctx, 3);
                                                        a0 = 21;
                                                        if (v1 != a0) {
                                                            // 0x003630fc
                                                            charge(ctx, 3);
                                                            a0 = 20;
                                                            if (v1 != a0) {
                                                                // 0x00363108
                                                                charge(ctx, 3);
                                                                a0 = 26;
                                                                if (v1 != a0) {
                                                                    // 0x00363114
                                                                    charge(ctx, 3);
                                                                    a0 = 3;
                                                                    if (v1 != a0) {
                                                                        // 0x00363120
                                                                        charge(ctx, 3);
                                                                        a0 = 27;
                                                                        if (v1 != a0) {
                                                                            // 0x0036312c
                                                                            charge(ctx, 3);
                                                                            a0 = 23;
                                                                            if (v1 != a0) {
                                                                                // 0x00363138
                                                                                charge(ctx, 3);
                                                                                a0 = 22;
                                                                                if (v1 != a0) {
                                                                                    // 0x00363144
                                                                                    charge(ctx, 3);
                                                                                    a0 = 17;
                                                                                    if (v1 != a0) {
                                                                                        // 0x00363150
                                                                                        charge(ctx, 3);
                                                                                        a0 = 16;
                                                                                        if (v1 != a0) {
                                                                                            // 0x0036315c
                                                                                            charge(ctx, 3);
                                                                                            a0 = 15;
                                                                                            if (v1 != a0) {
                                                                                                // 0x00363168
                                                                                                charge(ctx, 3);
                                                                                                a0 = 14;
                                                                                                if (v1 != a0) {
                                                                                                    // 0x00363174
                                                                                                    charge(ctx, 3);
                                                                                                    a0 = 13;
                                                                                                    if (v1 != a0) {
                                                                                                        // 0x00363180
                                                                                                        charge(ctx, 3);
                                                                                                        a0 = 11;
                                                                                                        if (v1 != a0) {
                                                                                                            // 0x0036318c
                                                                                                            charge(ctx, 3);
                                                                                                            a0 = 10;
                                                                                                            if (v1 != a0) {
                                                                                                                // 0x00363198
                                                                                                                charge(ctx, 3);
                                                                                                                a0 = 12;
                                                                                                                if (v1 != a0) {
                                                                                                                    // 0x003631a4
                                                                                                                    charge(ctx, 3);
                                                                                                                    a0 = 6;
                                                                                                                    if (v1 != a0) {
                                                                                                                        // 0x003631b0
                                                                                                                        charge(ctx, 3);
                                                                                                                        a0 = 2;
                                                                                                                        if (v1 != a0) {
                                                                                                                            // 0x003631bc
                                                                                                                            charge(ctx, 3);
                                                                                                                            a0 = 1;
                                                                                                                            if (v1 != a0) {
                                                                                                                                // 0x003631c8
                                                                                                                                charge(ctx, 2);
                                                                                                                                if (v1 != 0) {
                                                                                                                                    // 0x003631d0
                                                                                                                                    charge(ctx, 2);
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
        }
    }
    // 0x003638b4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_003636ec_98:
    charge(ctx, 3);
    s1 = a1;
    goto L_00363708;
}

// 0x003638E0 sub_3638E0 -- 2948 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyStateKey] (unit, nextKey, key, frame, work): the "state" unit types, run by sub_366AC0 every frame with the
// unit's current key (the latest one that fired; null before the first) and the next one (null after the last). The
// prologue computes the progress between them, (frame - key.frame) / (next.frame - key.frame) in $f12 (the start / end
// frame stand in for a missing key; 0 for an empty span), which the camera interpolation (sub_394070) receives.
// 6 fade (fade in / out, a fade colour 7 sets kMode bit 2; "fade clear" when no key is current), 8 the values at
// +16 / +18 (interpolated over the span) set or clear kFlagShake, 10 camera (sub_394070 with both keys' camera records into 0x958440; modes 1 / 2 / 3
// then set a camera slot with sub_38D560), 13..17 / 23 / 27 light switches (the kLightOn words), 36 effects (play /
// stop on channel kParam; kFlagFx0..2), 39 "keyfree" (sub_36F490 and the start position 0x7CE5F4 for the field),
// 43 sub_172820 / sub_16D6B0. Jump table 0x7BA400.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3638E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003638e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    s3 = a3;
    s0 = t0;
    a0 = 1;
    lw(a2, t0, 4);
    if (s1 == 0) {
        // 0x00363938
        charge(ctx, 1);
        lw(t0, s0, work::kStartFrame);
    } else {
        // 0x0036392c
        charge(ctx, 3);
        lhu(t0, s1, key::kFrame);
    }
    // 0x0036393c
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00363950
        charge(ctx, 1);
        lw(v1, s0, work::kEndFrame);
    } else {
        // 0x00363944
        charge(ctx, 3);
        lhu(v1, a1, key::kFrame);  // the next key's frame
    }
    // 0x00363954
    charge(ctx, 3);
    a3 = subu(v1, t0);
    if (a3 == 0) {
        // 0x00363994
        charge(ctx, 1);
        mtc1(zero, f12);
    } else {
        // 0x00363960
        charge(ctx, 13);
        v1 = subu(s3, t0);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        mtc1(a3, f0);
        cvt_s_w(f0, f0);
        div_s(f12, f1, f0);
    }
    // 0x00363998
    charge(ctx, 4);
    lw(v1, s2, unit::kType);
    a3 = 36;
    if (v1 == a3) {
        // 0x00364290
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x003642b8
            charge(ctx, 3);
            lhu(v1, s1, key::kFrame);
            if (s3 == v1) {
                // 0x003642c4
                charge(ctx, 4);
                lb(a0, s1, key::kCmd);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00364424
                    charge(ctx, 3);
                    lw(a0, s2, unit::kParam);
                    jal(ctx, 0x364428u, gen::fn_sub_396F50_00396f50);
                } else {
                    // 0x003642d4
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0036439c
                        charge(ctx, 6);
                        lw(a0, s2, unit::kParam);
                        jal(ctx, 0x3643A0u, gen::fn_sub_396ED0_00396ed0);
                        a0 = 1;
                        if (v0 == a0) {
                            // 0x003643b4
                            charge(ctx, 4);
                            lw(v1, s2, unit::kParam);
                            v0 = 2;
                            if (v1 == v0) {
                                // 0x00364404
                                charge(ctx, 3);
                                lw(v0, s0, work::kFlags);
                                v0 = v0 | 0x800;
                                sw(v0, s0, work::kFlags);
                            } else {
                                // 0x003643c4
                                charge(ctx, 2);
                                if (v1 == a0) {
                                    // 0x003643f0
                                    charge(ctx, 5);
                                    lw(v0, s0, work::kFlags);
                                    v0 = v0 | 0x400;
                                    sw(v0, s0, work::kFlags);
                                } else {
                                    // 0x003643cc
                                    charge(ctx, 2);
                                    if (v1 == 0) {
                                        // 0x003643dc
                                        charge(ctx, 5);
                                        lw(v0, s0, work::kFlags);
                                        v0 = v0 | 0x200;
                                        sw(v0, s0, work::kFlags);
                                    } else {
                                        // 0x003643d4
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                        // 0x00364410
                        charge(ctx, 5);
                        lw(a0, s2, unit::kParam);
                        jal(ctx, 0x364414u, gen::fn_sub_396E30_00396e30);
                    } else {
                        // 0x003642e0
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x003642f0
                            charge(ctx, 9);
                            s6 = 0;
                            s5 = 0;
                            s4 = 0;
                            s3 = 0;
                            lh(s7, s1, 28);
                            lh(fp, s1, 30);
                            lb(v0, s1, 32);
                            if (v0 != 0) {
                                // 0x0036432c
                                charge(ctx, 2);
                                if (v0 == v1) {
                                    // 0x00364334
                                    charge(ctx, 11);
                                    lb(a1, s1, 33);
                                    a0 = s0;
                                    a2 = addiu(sp, 0xAC);
                                    a3 = addiu(sp, 0xA8);
                                    t0 = addiu(sp, 0xA4);
                                    t1 = addiu(sp, 0xA0);
                                    jal(ctx, 0x36434Cu, gen::fn_sub_397870_00397870);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x00364360
                                        charge(ctx, 4);
                                        lw(s6, sp, 0xAC);
                                        lw(s5, sp, 0xA8);
                                        lw(s4, sp, 0xA4);
                                        lw(s3, sp, 0xA0);
                                    }
                                }
                            } else {
                                // 0x00364314
                                charge(ctx, 6);
                                lh(s6, s1, key::kArg20);
                                lh(s5, s1, 22);
                                lh(s4, s1, 24);
                                lh(s3, s1, 26);
                            }
                            // 0x00364370
                            charge(ctx, 11);
                            lw(a0, s2, unit::kParam);
                            a1 = s7;
                            a2 = fp;
                            a3 = s6;
                            t0 = s5;
                            t1 = s4;
                            t2 = s3;
                            jal(ctx, 0x36438Cu, gen::fn_sub_396C70_00396c70);
                        } else {
                            // 0x003642e8
                            charge(ctx, 2);
                        }
                    }
                }
            }
        } else {
            // 0x00364298
            charge(ctx, 3);
            v1 = a2 & 0x8;
            if (v1 == 0) {
                // 0x003642a4
                charge(ctx, 5);
                lw(a0, s2, unit::kParam);
                jal(ctx, 0x3642A8u, gen::fn_sub_397030_00397030);
            }
        }
    } else {
        // 0x003639a8
        charge(ctx, 3);
        a3 = 43;
        if (v1 == a3) {
            // 0x003641c0
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x003641f8
                charge(ctx, 3);
                lhu(v1, s1, key::kFrame);
                if (s3 == v1) {
                    // 0x00364204
                    charge(ctx, 5);
                    a0 = si(-1);
                    lb(v1, s1, key::kCmd);
                    at = sltiu(v1, 6);
                    if (at != 0) {
                        // 0x00364218
                        charge(ctx, 7);
                        a1 = 0x7C0000;
                        a1 = addiu(a1, -23552);  // "4B6"
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a1);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x364234u:  // table[0]
                            // 0x00364234
                            charge(ctx, 3);
                            a0 = 5;
                            break;
                        case 0x364240u:  // table[1]
                            // 0x00364240
                            charge(ctx, 3);
                            a0 = 4;
                            break;
                        case 0x36424Cu:  // table[2]
                            // 0x0036424c
                            charge(ctx, 3);
                            a0 = 3;
                            break;
                        case 0x364258u:  // table[3]
                            // 0x00364258
                            charge(ctx, 3);
                            a0 = 0;
                            break;
                        case 0x364264u:  // table[4]
                            // 0x00364264
                            charge(ctx, 3);
                            a0 = 1;
                            break;
                        case 0x364270u:  // table[5]
                            // 0x00364270
                            charge(ctx, 1);
                            a0 = 2;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                    }
                    // 0x00364274
                    charge(ctx, 3);
                    v1 = si(-1);
                    if (a0 != v1) {
                        // 0x00364280
                        charge(ctx, 4);
                        jal(ctx, 0x364280u, gen::fn_sub_172820_00172820);
                    }
                }
            } else {
                // 0x003641c8
                charge(ctx, 3);
                v1 = a2 & 0x8;
                if (v1 == 0) {
                    // 0x003641d4
                    charge(ctx, 3);
                    lw(v1, s0, work::kStartFrame);
                    if (s3 == v1) {
                        // 0x003641e0
                        charge(ctx, 6);
                        lhu(a1, s0, work::kFadeUnitArg);
                        a0 = 1;
                        jal(ctx, 0x3641E8u, gen::fn_sub_16D6B0_0016d6b0);
                    }
                }
            }
        } else {
            // 0x003639b4
            charge(ctx, 3);
            a3 = 39;
            if (v1 == a3) {
                // 0x00364154
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x0036415c
                    charge(ctx, 3);
                    lhu(v1, s1, key::kFrame);
                    if (v1 == s3) {
                        // 0x00364168
                        charge(ctx, 3);
                        lb(v0, s1, key::kCmd);
                        if (v0 != 0) {
                            // 0x0036418c
                            charge(ctx, 5);
                            a0 = 1;
                            jal(ctx, 0x364190u, gen::fn_sub_36F490_0036f490);
                            lh(v0, s1, key::kArg20);
                            sw(v0, gp, evt::kGpStartPos);  // 0x7CE5F4
                        } else {
                            // 0x00364174
                            charge(ctx, 6);
                            sw(zero, gp, evt::kGpStartPos);  // 0x7CE5F4
                            a0 = 0;
                            jal(ctx, 0x36417Cu, gen::fn_sub_36F490_0036f490);
                        }
                        // 0x003641a0
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -10624);  // "keyfree %d startpos=%d\n"
                        lw(a1, gp, evt::kGpKeyFree);  // 0x7CE5F0
                        lw(a2, gp, evt::kGpStartPos);  // 0x7CE5F4
                        jal(ctx, 0x3641B0u, gen::fn_printf_005225a8);
                    }
                }
            } else {
                // 0x003639c0
                charge(ctx, 3);
                a3 = 25;
                if (v1 != a3) {
                    // 0x003639cc
                    charge(ctx, 3);
                    a3 = 8;
                    if (v1 == a3) {
                        // 0x00364044
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0036413c
                            charge(ctx, 6);
                            lw(a0, s0, work::kFlags);
                            v1 = si(-5);
                            v1 = a0 & v1;
                            sw(v1, s0, work::kFlags);
                        } else {
                            // 0x0036404c
                            charge(ctx, 3);
                            lh(v1, s1, key::kArg20);
                            if (v1 != 0) {
                                // 0x00364068
                                charge(ctx, 3);
                                lw(a3, s1, key::kNext);
                                if (a3 != 0) {
                                    // 0x00364084
                                    charge(ctx, 27);
                                    lhu(a0, s1, key::kFrame);
                                    a2 = subu(s3, a0);
                                    lhu(v1, a3, 0);
                                    a1 = subu(v1, a0);
                                    a0 = subu(a1, a2);
                                    lh(v1, s1, key::kCmd);
                                    mult(v1, v1, a0);
                                    lh(v1, a3, 16);
                                    maddu(v1, v1, a2);
                                    div(v1, a1);
                                    mflo(v1);
                                    t0 = dsll32(v1, 16);
                                    t0 = dsra32(t0, 16);
                                    lh(v1, s1, 18);
                                    mult1(v1, v1, a0);
                                    lh(v1, a3, 18);
                                    maddu1(v1, v1, a2);
                                    div(v1, a1);
                                    mflo(v1);
                                    a0 = dsll32(v1, 16);
                                    a0 = dsra32(a0, 16);
                                } else {
                                    // 0x00364074
                                    charge(ctx, 4);
                                    lh(t0, s1, key::kCmd);
                                    lh(a0, s1, 18);
                                }
                            } else {
                                // 0x00364058
                                charge(ctx, 4);
                                lh(t0, s1, key::kCmd);
                                lh(a0, s1, 18);
                            }
                            // 0x003640f0
                            charge(ctx, 4);
                            v1 = dsll32(t0, 16);
                            v1 = dsra32(v1, 16);
                            if (v1 == 0) {
                                // 0x00364100
                                charge(ctx, 4);
                                v1 = dsll32(a0, 16);
                                v1 = dsra32(v1, 16);
                                if (v1 != 0) {
                                    goto L_00364128;
                                }
                                // 0x00364110
                                charge(ctx, 6);
                                lw(a0, s0, work::kFlags);
                                v1 = si(-5);
                                v1 = a0 & v1;
                                sw(v1, s0, work::kFlags);
                                // 0x00364430 (the shared epilogue, written out on this path)
                                charge(ctx, 13);
                                ld(ra, sp, 0x90);
                                lq(fp, sp, 0x80);
                                lq(s7, sp, 0x70);
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
                        L_00364128:
                            charge(ctx, 5);
                            lw(v1, s0, work::kFlags);
                            v1 = v1 | 0x4;
                            sw(v1, s0, work::kFlags);
                        }
                    } else {
                        // 0x003639d8
                        charge(ctx, 3);
                        a3 = 17;
                        if (v1 == a3) {
                            // 0x00363fd4
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x00363fe8
                                charge(ctx, 1);
                                a0 = 0;
                            } else {
                                // 0x00363fdc
                                charge(ctx, 3);
                                lw(a0, s1, key::kExtra);
                            }
                            // 0x00363fec
                            charge(ctx, 2);
                            if (a1 == 0) {
                                // 0x00364000
                                charge(ctx, 1);
                                v1 = 0;
                            } else {
                                // 0x00363ff4
                                charge(ctx, 3);
                                lw(v1, a1, 72);
                            }
                            // 0x00364004
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x0036400c
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    goto L_00364014;
                                }
                                // 0x00364430 (the shared epilogue, written out on this path)
                                charge(ctx, 13);
                                ld(ra, sp, 0x90);
                                lq(fp, sp, 0x80);
                                lq(s7, sp, 0x70);
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
                        L_00364014:
                            charge(ctx, 5);
                            v1 = 0x960000;
                            lw(v1, v1, -31492);  // 0x9584FC
                            v1 = srl(v1, 24);
                            if (v1 != 0) {
                                // 0x00364034
                                charge(ctx, 4);
                                v1 = 1;
                                sw(v1, s0, 252);
                            } else {
                                // 0x00364028
                                charge(ctx, 3);
                                sw(zero, s0, 252);
                            }
                        } else {
                            // 0x003639e4
                            charge(ctx, 3);
                            a3 = 16;
                            if (v1 == a3) {
                                // 0x00363f64
                                charge(ctx, 2);
                                if (s1 == 0) {
                                    // 0x00363f78
                                    charge(ctx, 1);
                                    a0 = 0;
                                } else {
                                    // 0x00363f6c
                                    charge(ctx, 3);
                                    lw(a0, s1, key::kExtra);
                                }
                                // 0x00363f7c
                                charge(ctx, 2);
                                if (a1 == 0) {
                                    // 0x00363f90
                                    charge(ctx, 1);
                                    v1 = 0;
                                } else {
                                    // 0x00363f84
                                    charge(ctx, 3);
                                    lw(v1, a1, 72);
                                }
                                // 0x00363f94
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x00363f9c
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        goto L_00363fa4;
                                    }
                                    // 0x00364430 (the shared epilogue, written out on this path)
                                    charge(ctx, 13);
                                    ld(ra, sp, 0x90);
                                    lq(fp, sp, 0x80);
                                    lq(s7, sp, 0x70);
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
                            L_00363fa4:
                                charge(ctx, 5);
                                v1 = 0x960000;
                                lw(v1, v1, -31536);  // 0x9584D0
                                v1 = srl(v1, 24);
                                if (v1 != 0) {
                                    // 0x00363fc4
                                    charge(ctx, 4);
                                    v1 = 1;
                                    sw(v1, s0, 248);
                                } else {
                                    // 0x00363fb8
                                    charge(ctx, 3);
                                    sw(zero, s0, 248);
                                }
                            } else {
                                // 0x003639f0
                                charge(ctx, 3);
                                a3 = 27;
                                if (v1 == a3) {
                                    // 0x00363ef4
                                    charge(ctx, 2);
                                    if (s1 == 0) {
                                        // 0x00363f08
                                        charge(ctx, 1);
                                        a0 = 0;
                                    } else {
                                        // 0x00363efc
                                        charge(ctx, 3);
                                        lw(a0, s1, key::kExtra);
                                    }
                                    // 0x00363f0c
                                    charge(ctx, 2);
                                    if (a1 == 0) {
                                        // 0x00363f20
                                        charge(ctx, 1);
                                        v1 = 0;
                                    } else {
                                        // 0x00363f14
                                        charge(ctx, 3);
                                        lw(v1, a1, 72);
                                    }
                                    // 0x00363f24
                                    charge(ctx, 2);
                                    if (a0 == 0) {
                                        // 0x00363f2c
                                        charge(ctx, 2);
                                        if (v1 != 0) {
                                            goto L_00363f34;
                                        }
                                        // 0x00364430 (the shared epilogue, written out on this path)
                                        charge(ctx, 13);
                                        ld(ra, sp, 0x90);
                                        lq(fp, sp, 0x80);
                                        lq(s7, sp, 0x70);
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
                                L_00363f34:
                                    charge(ctx, 5);
                                    v1 = 0x960000;
                                    lw(v1, v1, -31360);  // 0x958580
                                    v1 = srl(v1, 24);
                                    if (v1 != 0) {
                                        // 0x00363f54
                                        charge(ctx, 4);
                                        v1 = 1;
                                        sw(v1, s0, work::kLight27On);
                                    } else {
                                        // 0x00363f48
                                        charge(ctx, 3);
                                        sw(zero, s0, work::kLight27On);
                                    }
                                } else {
                                    // 0x003639fc
                                    charge(ctx, 3);
                                    a3 = 23;
                                    if (v1 == a3) {
                                        // 0x00363e84
                                        charge(ctx, 2);
                                        if (s1 == 0) {
                                            // 0x00363e98
                                            charge(ctx, 1);
                                            a0 = 0;
                                        } else {
                                            // 0x00363e8c
                                            charge(ctx, 3);
                                            lw(a0, s1, key::kExtra);
                                        }
                                        // 0x00363e9c
                                        charge(ctx, 2);
                                        if (a1 == 0) {
                                            // 0x00363eb0
                                            charge(ctx, 1);
                                            v1 = 0;
                                        } else {
                                            // 0x00363ea4
                                            charge(ctx, 3);
                                            lw(v1, a1, 72);
                                        }
                                        // 0x00363eb4
                                        charge(ctx, 2);
                                        if (a0 == 0) {
                                            // 0x00363ebc
                                            charge(ctx, 2);
                                            if (v1 != 0) {
                                                goto L_00363ec4;
                                            }
                                            // 0x00364430 (the shared epilogue, written out on this path)
                                            charge(ctx, 13);
                                            ld(ra, sp, 0x90);
                                            lq(fp, sp, 0x80);
                                            lq(s7, sp, 0x70);
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
                                    L_00363ec4:
                                        charge(ctx, 5);
                                        v1 = 0x960000;
                                        lw(v1, v1, -31396);  // 0x95855C
                                        v1 = srl(v1, 24);
                                        if (v1 != 0) {
                                            // 0x00363ee4
                                            charge(ctx, 4);
                                            v1 = 1;
                                            sw(v1, s0, 256);
                                        } else {
                                            // 0x00363ed8
                                            charge(ctx, 3);
                                            sw(zero, s0, 256);
                                        }
                                    } else {
                                        // 0x00363a08
                                        charge(ctx, 3);
                                        a3 = 15;
                                        if (v1 == a3) {
                                            // 0x00363e14
                                            charge(ctx, 2);
                                            if (s1 == 0) {
                                                // 0x00363e28
                                                charge(ctx, 1);
                                                a0 = 0;
                                            } else {
                                                // 0x00363e1c
                                                charge(ctx, 3);
                                                lw(a0, s1, key::kExtra);
                                            }
                                            // 0x00363e2c
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x00363e40
                                                charge(ctx, 1);
                                                v1 = 0;
                                            } else {
                                                // 0x00363e34
                                                charge(ctx, 3);
                                                lw(v1, a1, 72);
                                            }
                                            // 0x00363e44
                                            charge(ctx, 2);
                                            if (a0 == 0) {
                                                // 0x00363e4c
                                                charge(ctx, 2);
                                                if (v1 != 0) {
                                                    goto L_00363e54;
                                                }
                                                // 0x00364430 (the shared epilogue, written out on this path)
                                                charge(ctx, 13);
                                                ld(ra, sp, 0x90);
                                                lq(fp, sp, 0x80);
                                                lq(s7, sp, 0x70);
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
                                        L_00363e54:
                                            charge(ctx, 5);
                                            v1 = 0x960000;
                                            lw(v1, v1, -31444);  // 0x95852C
                                            v1 = srl(v1, 24);
                                            if (v1 != 0) {
                                                // 0x00363e74
                                                charge(ctx, 4);
                                                v1 = 1;
                                                sw(v1, s0, 244);
                                            } else {
                                                // 0x00363e68
                                                charge(ctx, 3);
                                                sw(zero, s0, 244);
                                            }
                                        } else {
                                            // 0x00363a14
                                            charge(ctx, 3);
                                            a3 = 14;
                                            if (v1 == a3) {
                                                // 0x00363da4
                                                charge(ctx, 2);
                                                if (s1 == 0) {
                                                    // 0x00363db8
                                                    charge(ctx, 1);
                                                    a0 = 0;
                                                } else {
                                                    // 0x00363dac
                                                    charge(ctx, 3);
                                                    lw(a0, s1, key::kExtra);
                                                }
                                                // 0x00363dbc
                                                charge(ctx, 2);
                                                if (a1 == 0) {
                                                    // 0x00363dd0
                                                    charge(ctx, 1);
                                                    v1 = 0;
                                                } else {
                                                    // 0x00363dc4
                                                    charge(ctx, 3);
                                                    lw(v1, a1, 72);
                                                }
                                                // 0x00363dd4
                                                charge(ctx, 2);
                                                if (a0 == 0) {
                                                    // 0x00363ddc
                                                    charge(ctx, 2);
                                                    if (v1 != 0) {
                                                        goto L_00363de4;
                                                    }
                                                    // 0x00364430 (the shared epilogue, written out on this path)
                                                    charge(ctx, 13);
                                                    ld(ra, sp, 0x90);
                                                    lq(fp, sp, 0x80);
                                                    lq(s7, sp, 0x70);
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
                                            L_00363de4:
                                                charge(ctx, 5);
                                                v1 = 0x960000;
                                                lw(v1, v1, -31580);  // 0x9584A4
                                                v1 = srl(v1, 24);
                                                if (v1 != 0) {
                                                    // 0x00363e04
                                                    charge(ctx, 4);
                                                    v1 = 1;
                                                    sw(v1, s0, 240);
                                                } else {
                                                    // 0x00363df8
                                                    charge(ctx, 3);
                                                    sw(zero, s0, 240);
                                                }
                                            } else {
                                                // 0x00363a20
                                                charge(ctx, 3);
                                                a3 = 13;
                                                if (v1 == a3) {
                                                    // 0x00363d34
                                                    charge(ctx, 2);
                                                    if (s1 == 0) {
                                                        // 0x00363d48
                                                        charge(ctx, 1);
                                                        a0 = 0;
                                                    } else {
                                                        // 0x00363d3c
                                                        charge(ctx, 3);
                                                        lw(a0, s1, key::kExtra);
                                                    }
                                                    // 0x00363d4c
                                                    charge(ctx, 2);
                                                    if (a1 == 0) {
                                                        // 0x00363d60
                                                        charge(ctx, 1);
                                                        v1 = 0;
                                                    } else {
                                                        // 0x00363d54
                                                        charge(ctx, 3);
                                                        lw(v1, a1, 72);
                                                    }
                                                    // 0x00363d64
                                                    charge(ctx, 2);
                                                    if (a0 == 0) {
                                                        // 0x00363d6c
                                                        charge(ctx, 2);
                                                        if (v1 != 0) {
                                                            goto L_00363d74;
                                                        }
                                                        // 0x00364430 (the shared epilogue, written out on this path)
                                                        charge(ctx, 13);
                                                        ld(ra, sp, 0x90);
                                                        lq(fp, sp, 0x80);
                                                        lq(s7, sp, 0x70);
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
                                                L_00363d74:
                                                    charge(ctx, 5);
                                                    v1 = 0x960000;
                                                    lw(v1, v1, -31632);  // 0x958470
                                                    v1 = srl(v1, 24);
                                                    if (v1 != 0) {
                                                        // 0x00363d94
                                                        charge(ctx, 4);
                                                        v1 = 1;
                                                        sw(v1, s0, work::kLightOn);
                                                    } else {
                                                        // 0x00363d88
                                                        charge(ctx, 3);
                                                        sw(zero, s0, work::kLightOn);
                                                    }
                                                } else {
                                                    // 0x00363a2c
                                                    charge(ctx, 3);
                                                    a3 = 11;
                                                    if (v1 == a3) {
                                                        // 0x00363d04
                                                        charge(ctx, 2);
                                                        if (s1 == 0) {
                                                            // 0x00363d18
                                                            charge(ctx, 1);
                                                            v1 = 0;
                                                        } else {
                                                            // 0x00363d0c
                                                            charge(ctx, 3);
                                                            lw(v1, s1, key::kExtra);
                                                        }
                                                        // 0x00363d1c
                                                        charge(ctx, 2);
                                                        if (v1 == 0) {
                                                            // 0x00363d24
                                                            charge(ctx, 2);
                                                            if (a1 != 0) {
                                                            }
                                                            // 0x00363d2c
                                                            charge(ctx, 2);
                                                        }
                                                    } else {
                                                        // 0x00363a38
                                                        charge(ctx, 3);
                                                        a3 = 10;
                                                        if (v1 == a3) {
                                                            // 0x00363b78
                                                            charge(ctx, 2);
                                                            if (s1 == 0) {
                                                                // 0x00363b90
                                                                charge(ctx, 1);
                                                                v1 = 0;
                                                            } else {
                                                                // 0x00363b80
                                                                charge(ctx, 4);
                                                                lw(v1, s1, key::kExtra);
                                                                lw(a0, s1, key::kName);
                                                            }
                                                            // 0x00363b94
                                                            charge(ctx, 2);
                                                            if (a1 == 0) {
                                                                // 0x00363ba8
                                                                charge(ctx, 1);
                                                                a2 = 0;
                                                            } else {
                                                                // 0x00363b9c
                                                                charge(ctx, 3);
                                                                lw(a2, a1, 72);
                                                            }
                                                            // 0x00363bac
                                                            charge(ctx, 2);
                                                            if (v1 == 0) {
                                                                // 0x00363bb4
                                                                charge(ctx, 2);
                                                                if (a2 != 0) {
                                                                    goto L_00363bbc;
                                                                }
                                                                // 0x00364430 (the shared epilogue, written out on this path)
                                                                charge(ctx, 13);
                                                                ld(ra, sp, 0x90);
                                                                lq(fp, sp, 0x80);
                                                                lq(s7, sp, 0x70);
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
                                                        L_00363bbc:
                                                            charge(ctx, 8);
                                                            a1 = v1;
                                                            a3 = 0x960000;
                                                            a3 = addiu(a3, -31680);  // &0x958440
                                                            jal(ctx, 0x363BC8u, gen::fn_sub_394070_00394070);
                                                            lb(a1, s2, unit::kCamMode);
                                                            if (a1 != 0) {
                                                                // 0x00363bdc
                                                                charge(ctx, 3);
                                                                a0 = 1;
                                                                if (a1 != a0) {
                                                                    // 0x00363c20
                                                                    charge(ctx, 4);
                                                                    s4 = 0;
                                                                    v1 = 3;
                                                                    if (a1 != v1) {
                                                                        // 0x00363c78
                                                                        charge(ctx, 3);
                                                                        v1 = 2;
                                                                        if (a1 != v1) {
                                                                            // 0x00363cbc
                                                                            charge(ctx, 5);
                                                                            a0 = 0x6A0000;
                                                                            a0 = addiu(a0, -10880);  // "mt_evtMain.c"
                                                                            a1 = 3433;
                                                                            jal(ctx, 0x363CC8u, gen::fn_sub_19D3F0_0019d3f0);
                                                                        L_00363cd0:
                                                                            charge(ctx, 13);
                                                                            lb(a1, s2, unit::kCamMode);
                                                                            lw(a0, s2, unit::kParam);
                                                                            a2 = s4;
                                                                            a3 = 0x960000;
                                                                            a3 = addiu(a3, -31680);  // &0x958440
                                                                            t0 = 0x960000;
                                                                            t0 = addiu(t0, -31664);  // &0x958450
                                                                            t1 = 0x960000;
                                                                            t1 = addiu(t1, -31648);  // &0x958460
                                                                            jal(ctx, 0x363CF4u, gen::fn_sub_38D560_0038d560);
                                                                        } else {
                                                                            // 0x00363c84
                                                                            charge(ctx, 2);
                                                                            if (s1 != 0) {
                                                                                // 0x00363c8c
                                                                                charge(ctx, 3);
                                                                                lhu(v1, s1, key::kFrame);
                                                                                if (v1 != s3) {
                                                                                    goto L_00363cd0;
                                                                                }
                                                                                // 0x00363c98
                                                                                charge(ctx, 3);
                                                                                lh(v1, s1, 28);
                                                                                if (v1 != a0) {
                                                                                    goto L_00363cd0;
                                                                                }
                                                                                // 0x00363ca4
                                                                                charge(ctx, 4);
                                                                                lw(v1, s0, work::kFlags);
                                                                                v1 = v1 & 0x1;
                                                                                if (v1 != 0) {
                                                                                    goto L_00363cd0;
                                                                                }
                                                                                // 0x00363cb4
                                                                                charge(ctx, 2);
                                                                            }
                                                                        }
                                                                    } else {
                                                                        // 0x00363c30
                                                                        charge(ctx, 6);
                                                                        lhu(a0, s2, unit::kCamTarget);
                                                                        jal(ctx, 0x363C34u, gen::fn_sub_3B5D10_003b5d10);
                                                                        s4 = v0;
                                                                        if (s4 != 0) {
                                                                            // 0x00363c48
                                                                            charge(ctx, 2);
                                                                            if (s1 != 0) {
                                                                                // 0x00363c50
                                                                                charge(ctx, 3);
                                                                                lhu(a0, s1, key::kLength);
                                                                                if (a0 == 0) {
                                                                                    goto L_00363cd0;
                                                                                }
                                                                                // 0x00363c5c
                                                                                charge(ctx, 5);
                                                                                lhu(v1, s1, key::kFrame);
                                                                                v1 = addu(v1, a0);
                                                                                at = slt(v1, s3);
                                                                                if (at == 0) {
                                                                                    goto L_00363cd0;
                                                                                }
                                                                                // 0x00363c70
                                                                                charge(ctx, 2);
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    // 0x00363be8
                                                                    charge(ctx, 2);
                                                                    if (s1 != 0) {
                                                                        // 0x00363bf0
                                                                        charge(ctx, 12);
                                                                        lw(a0, s2, unit::kParam);
                                                                        a2 = 0;
                                                                        a3 = 0x960000;
                                                                        a3 = addiu(a3, -31680);  // &0x958440
                                                                        t0 = 0x960000;
                                                                        t0 = addiu(t0, -31664);  // &0x958450
                                                                        t1 = 0x960000;
                                                                        t1 = addiu(t1, -31648);  // &0x958460
                                                                        jal(ctx, 0x363C10u, gen::fn_sub_38D560_0038d560);
                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            // 0x00363a44
                                                            charge(ctx, 3);
                                                            a0 = 6;
                                                            if (v1 == a0) {
                                                                // 0x00363a58
                                                                charge(ctx, 2);
                                                                if (s1 != 0) {
                                                                    // 0x00363aa0
                                                                    charge(ctx, 5);
                                                                    v1 = a2 & 0x10;
                                                                    v1 = sltu(0, v1);
                                                                    a1 = 1;
                                                                    if (v1 != a1) {
                                                                        // 0x00363ab4
                                                                        charge(ctx, 3);
                                                                        lhu(v1, s1, key::kFrame);
                                                                        if (v1 == s3) {
                                                                            // 0x00363ac0
                                                                            charge(ctx, 3);
                                                                            lh(v1, s1, key::kCmd);
                                                                            if (v1 == a1) {
                                                                                // 0x00363b0c
                                                                                charge(ctx, 4);
                                                                                lh(a0, s1, 18);
                                                                                v1 = 7;
                                                                                if (a0 != v1) {
                                                                                    // 0x00363b30
                                                                                    charge(ctx, 6);
                                                                                    sw(a1, s0, work::kFading);
                                                                                    jal(ctx, 0x363B34u, gen::fn_sub_108570_00108570);
                                                                                    v1 = 1;
                                                                                    if (v0 == v1) {
                                                                                        // 0x00363b48
                                                                                        charge(ctx, 6);
                                                                                        lh(a0, s1, 18);
                                                                                        jal(ctx, 0x363B4Cu, gen::fn_sub_108670_00108670);
                                                                                        lhu(v1, s1, key::kLength);
                                                                                        if (v1 != 0) {
                                                                                            // 0x00363b60
                                                                                            charge(ctx, 6);
                                                                                            a0 = dsll32(v1, 16);
                                                                                            a0 = dsra32(a0, 16);
                                                                                            jal(ctx, 0x363B68u, gen::fn_sub_1086A0_001086a0);
                                                                                        }
                                                                                    }
                                                                                } else {
                                                                                    // 0x00363b1c
                                                                                    charge(ctx, 5);
                                                                                    lb(v1, s0, work::kMode);
                                                                                    v1 = v1 | 0x4;
                                                                                    sb(v1, s0, work::kMode);
                                                                                }
                                                                            } else {
                                                                                // 0x00363acc
                                                                                charge(ctx, 2);
                                                                                if (v1 == 0) {
                                                                                    // 0x00363adc
                                                                                    charge(ctx, 6);
                                                                                    sw(a1, s0, work::kFading);
                                                                                    jal(ctx, 0x363AE0u, gen::fn_sub_1085C0_001085c0);
                                                                                    lhu(v1, s1, key::kLength);
                                                                                    if (v1 != 0) {
                                                                                        // 0x00363af4
                                                                                        charge(ctx, 6);
                                                                                        a0 = dsll32(v1, 16);
                                                                                        a0 = dsra32(a0, 16);
                                                                                        jal(ctx, 0x363AFCu, gen::fn_sub_1086A0_001086a0);
                                                                                    }
                                                                                } else {
                                                                                    // 0x00363ad4
                                                                                    charge(ctx, 2);
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    // 0x00363a60
                                                                    charge(ctx, 3);
                                                                    v1 = a2 & 0x8;
                                                                    if (v1 == 0) {
                                                                        // 0x00363a6c
                                                                        charge(ctx, 4);
                                                                        lw(a0, s0, work::kFading);
                                                                        v1 = 1;
                                                                        if (a0 == v1) {
                                                                            // 0x00363a7c
                                                                            charge(ctx, 9);
                                                                            a0 = 0x6A0000;
                                                                            a0 = addiu(a0, -10640);  // "fade clear\n"
                                                                            jal(ctx, 0x363A84u, gen::fn_printf_005225a8);
                                                                            jal(ctx, 0x363A8Cu, gen::fn_sub_1071B0_001071b0);
                                                                            sw(zero, s0, work::kFading);
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                // 0x00363a50
                                                                charge(ctx, 2);
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
                    }
                }
            }
        }
    }
    // 0x00364430 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00364470 sub_364470 -- 328 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyRotKey] (frame, unit): the model unit's latest firing key with command 4 at or before the frame; when it
// fires now: rotate the actor (sub_3B8B30 with the angle at +20 and the time at +36) and, when +40 is set, a footstep
// sound setting (sub_3BB1D0; "set rot asioto"). Returns the key (or 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_364470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00364470
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = si(-1);
    s1 = 0;
    lw(s2, a1, unit::kKeyHead);
    for (;;) {
        // 0x003644f4
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003644a8
        charge(ctx, 4);
        lb(v1, s2, key::kCmd);
        v0 = 4;
        if (v1 == v0) {
            // 0x003644b8
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3644BCu, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x003644cc
                charge(ctx, 4);
                lhu(v0, s2, key::kFrame);
                at = slt(s4, v0);
                if (at == 0) {
                    // 0x003644dc
                    charge(ctx, 3);
                    at = slt(s0, v0);
                    if (at != 0) {
                        // 0x003644e8
                        charge(ctx, 2);
                        s0 = v0;
                        s1 = s2;
                    }
                }
            }
        }
        // 0x003644f0
        charge(ctx, 1);
        lw(s2, s2, key::kNext);
    }
    // 0x003644fc
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00364510
        charge(ctx, 3);
        lhu(v0, s1, key::kFrame);
        if (v0 == s4) {
            // 0x00364528
            charge(ctx, 13);
            sw(zero, sp, 0x60);
            lwc1(f0, s1, key::kArg20);
            swc1(f0, sp, 0x64);
            sw(zero, sp, 0x68);
            lh(a2, s1, 36);
            lhu(a0, s3, unit::kResId);
            a1 = addiu(sp, 0x60);
            a3 = 0;
            jal(ctx, 0x364548u, gen::fn_sub_3B8B30_003b8b30);
            lb(v0, s1, 40);
            if (v0 != 0) {
                // 0x0036455c
                charge(ctx, 13);
                lb(v0, s1, 41);
                v0 = addiu(v0, 1);
                a2 = v0 & 0xFF;
                lb(a3, s1, 42);
                lb(t0, s1, 43);
                lhu(a0, s3, unit::kResId);
                a1 = 2;
                jal(ctx, 0x364578u, gen::fn_sub_3BB1D0_003bb1d0);
                a0 = 0x6A0000;
                a0 = addiu(a0, -10592);  // "set rot asioto\n"
                jal(ctx, 0x364588u, gen::fn_printf_005225a8);
            }
            // 0x00364590
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x0036451c
            charge(ctx, 3);
            v0 = s1;
        }
    } else {
        // 0x00364504
        charge(ctx, 3);
        v0 = s1;
    }
    // 0x00364594 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003645C0 sub_3645C0 -- 260 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyScaleKey] (frame, unit): command 10: when the key fires now, sub_3B8C30(resId, {s, s, s} from +24, time
// +20). Returns the key.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3645C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003645c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = si(-1);
    s1 = 0;
    lw(s2, a1, unit::kKeyHead);
    for (;;) {
        // 0x00364644
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003645f8
        charge(ctx, 4);
        lb(v1, s2, key::kCmd);
        v0 = 10;
        if (v1 == v0) {
            // 0x00364608
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x36460Cu, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x0036461c
                charge(ctx, 4);
                lhu(v0, s2, key::kFrame);
                at = slt(s4, v0);
                if (at == 0) {
                    // 0x0036462c
                    charge(ctx, 3);
                    at = slt(s0, v0);
                    if (at != 0) {
                        // 0x00364638
                        charge(ctx, 2);
                        s0 = v0;
                        s1 = s2;
                    }
                }
            }
        }
        // 0x00364640
        charge(ctx, 1);
        lw(s2, s2, key::kNext);
    }
    // 0x0036464c
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00364660
        charge(ctx, 3);
        lhu(v0, s1, key::kFrame);
        if (v0 == s4) {
            // 0x00364678
            charge(ctx, 10);
            lh(a2, s1, key::kArg20);
            lwc1(f0, s1, 24);
            swc1(f0, sp, 0x68);
            swc1(f0, sp, 0x64);
            swc1(f0, sp, 0x60);
            lhu(a0, s3, unit::kResId);
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x364694u, gen::fn_sub_3B8C30_003b8c30);
            v0 = s1;
        } else {
            // 0x0036466c
            charge(ctx, 3);
            v0 = s1;
        }
    } else {
        // 0x00364654
        charge(ctx, 3);
        v0 = s1;
    }
    // 0x003646a0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003646D0 sub_3646D0 -- 528 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [evtUnitApplyPosChangeKey] (frame, unit): command 3 keys with a target (+22): mode 0 = sub_3B8470(resId, target)
// (take the target's place), mode 1 = turn towards the target (sub_3B86C0 / sub_3B8690 / sub_3B8A60; "pos change
// takano"), mode 2 nothing. Returns the key.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3646D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003646d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = si(-1);
    s2 = 0;
    lw(s1, a1, unit::kKeyHead);
    for (;;) {
        // 0x00364764
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036470c
        charge(ctx, 4);
        lb(v1, s1, key::kCmd);
        v0 = 3;
        if (v1 == v0) {
            // 0x0036471c
            charge(ctx, 3);
            lh(v0, s1, 22);
            if (v0 != 0) {
                // 0x00364728
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x36472Cu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x0036473c
                    charge(ctx, 4);
                    lhu(v0, s1, key::kFrame);
                    at = slt(s4, v0);
                    if (at == 0) {
                        // 0x0036474c
                        charge(ctx, 3);
                        at = slt(s0, v0);
                        if (at != 0) {
                            // 0x00364758
                            charge(ctx, 2);
                            s0 = v0;
                            s2 = s1;
                        }
                    }
                }
            }
        }
        // 0x00364760
        charge(ctx, 1);
        lw(s1, s1, key::kNext);
    }
    // 0x0036476c
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x00364780
        charge(ctx, 3);
        lhu(v0, s2, key::kFrame);
        if (v0 == s4) {
            // 0x00364798
            charge(ctx, 5);
            lh(s0, s2, 22);
            lb(v1, s2, key::kArg20);
            v0 = 2;
            if (v1 != v0) {
                // 0x003647ac
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x003647e0
                    charge(ctx, 15);
                    lb(a0, s2, 21);
                    jal(ctx, 0x3647E4u, gen::fn_sub_38A900_0038a900);
                    mov_s(f20, f0);
                    sw(zero, sp, 0x7C);
                    lhu(a0, s3, unit::kResId);
                    jal(ctx, 0x3647F8u, gen::fn_sub_3B5D10_003b5d10);
                    s1 = v0;
                    a0 = s0 & 0xFFFF;
                    jal(ctx, 0x364808u, gen::fn_sub_3B5D10_003b5d10);
                    s0 = v0;
                    if (s1 != 0) {
                        // 0x0036481c
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x00364824
                            charge(ctx, 13);
                            a0 = s1;
                            a1 = addiu(s0, 4);
                            mov_s(f12, f20);
                            jal(ctx, 0x364830u, gen::fn_sub_3B86C0_003b86c0);
                            a0 = addiu(s1, 4);
                            a1 = addiu(s0, 4);
                            a2 = addiu(sp, 0x7C);
                            jal(ctx, 0x364844u, gen::fn_sub_3B8690_003b8690);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x00364858
                                charge(ctx, 4);
                                v1 = addiu(sp, 0x70);
                                v0 = 12;
                                if (v1 != 0) {
                                    for (;;) {
                                        // 0x00364868
                                        charge(ctx, 7);
                                        sb(zero, v1, 0);
                                        v1 = addiu(v1, 1);
                                        v0 = addiu(v0, -1);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                                // 0x00364884
                                charge(ctx, 8);
                                lwc1(f0, sp, 0x7C);
                                swc1(f0, sp, 0x74);
                                a0 = s1;
                                a1 = addiu(sp, 0x70);
                                a2 = 15;
                                a3 = 0;
                                jal(ctx, 0x36489Cu, gen::fn_sub_3B8A60_003b8a60);
                            }
                        }
                    }
                    // 0x003648a4
                    charge(ctx, 4);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -10576);  // "pos change takano\n"
                    jal(ctx, 0x3648ACu, gen::fn_printf_005225a8);
                } else {
                    // 0x003647b8
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x003647c8
                        charge(ctx, 6);
                        a1 = s0 & 0xFFFF;
                        lhu(a0, s3, unit::kResId);
                        jal(ctx, 0x3647D0u, gen::fn_sub_3B8470_003b8470);
                    } else {
                        // 0x003647c0
                        charge(ctx, 2);
                    }
                }
            }
            // 0x003648b4
            charge(ctx, 1);
            v0 = s2;
        } else {
            // 0x0036478c
            charge(ctx, 3);
            v0 = s2;
        }
    } else {
        // 0x00364774
        charge(ctx, 3);
        v0 = s2;
    }
    // 0x003648b8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003648E0 sub_3648E0 -- 336 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyShowKey] (work, frame, unit): command 0 (show / hide): when the key fires now, sub_3B9550(resId, +20 ==
// 0); without any key the actor follows its setup flag (kModelFlags bit 1), except in play mode.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3648E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003648e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s0 = si(-1);
    s1 = 0;
    lw(s2, a2, unit::kKeyHead);
    for (;;) {
        // 0x00364968
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00364920
        charge(ctx, 3);
        lb(v1, s2, key::kCmd);
        if (v1 == 0) {
            // 0x0036492c
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x364930u, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x00364940
                charge(ctx, 4);
                lhu(v1, s2, key::kFrame);
                at = slt(s4, v1);
                if (at == 0) {
                    // 0x00364950
                    charge(ctx, 3);
                    at = slt(s0, v1);
                    if (at != 0) {
                        // 0x0036495c
                        charge(ctx, 2);
                        s0 = v1;
                        s1 = s2;
                    }
                }
            }
        }
        // 0x00364964
        charge(ctx, 1);
        lw(s2, s2, key::kNext);
    }
    // 0x00364970
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003649c8
        charge(ctx, 3);
        lhu(v1, s1, key::kFrame);
        if (v1 == s4) {
            // 0x003649d4
            charge(ctx, 3);
            lb(v0, s1, key::kArg20);
            if (v0 != 0) {
                // 0x003649f8
                charge(ctx, 4);
                lhu(a0, s3, unit::kResId);
                a1 = 0;
                jal(ctx, 0x364A00u, gen::fn_sub_3B9550_003b9550);
            } else {
                // 0x003649e0
                charge(ctx, 6);
                lhu(a0, s3, unit::kResId);
                a1 = 1;
                jal(ctx, 0x3649E8u, gen::fn_sub_3B9550_003b9550);
            }
        }
    } else {
        // 0x00364978
        charge(ctx, 4);
        lw(v1, s5, work::kFlags);
        v1 = v1 & 0x8;
        if (v1 == 0) {
            // 0x00364988
            charge(ctx, 4);
            lw(v0, s3, unit::kModelFlags);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x003649b0
                charge(ctx, 4);
                lhu(a0, s3, unit::kResId);
                a1 = 0;
                jal(ctx, 0x3649B8u, gen::fn_sub_3B9550_003b9550);
            } else {
                // 0x00364998
                charge(ctx, 6);
                lhu(a0, s3, unit::kResId);
                a1 = 1;
                jal(ctx, 0x3649A0u, gen::fn_sub_3B9550_003b9550);
            }
        }
        // 0x003649c0
        charge(ctx, 2);
    }
    // 0x00364a08 (the shared epilogue, written out on this path)
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

// 0x00364A30 sub_364A30 -- 220 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyKey9] (frame, unit): command 9: when the key fires now, sub_3BB180(resId, +20 == 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_364A30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00364a30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = si(-1);
    s1 = 0;
    lw(s2, a1, unit::kKeyHead);
    for (;;) {
        // 0x00364ab4
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00364a68
        charge(ctx, 4);
        lb(a0, s2, key::kCmd);
        v1 = 9;
        if (a0 == v1) {
            // 0x00364a78
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x364A7Cu, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x00364a8c
                charge(ctx, 4);
                lhu(v1, s2, key::kFrame);
                at = slt(s4, v1);
                if (at == 0) {
                    // 0x00364a9c
                    charge(ctx, 3);
                    at = slt(s0, v1);
                    if (at != 0) {
                        // 0x00364aa8
                        charge(ctx, 2);
                        s0 = v1;
                        s1 = s2;
                    }
                }
            }
        }
        // 0x00364ab0
        charge(ctx, 1);
        lw(s2, s2, key::kNext);
    }
    // 0x00364abc
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00364ac4
        charge(ctx, 3);
        lhu(v1, s1, key::kFrame);
        if (v1 == s4) {
            // 0x00364ad0
            charge(ctx, 6);
            lb(v0, s1, key::kArg20);
            a1 = v0;
            a1 = sltiu(a1, 1);
            lhu(a0, s3, unit::kResId);
            jal(ctx, 0x364AE0u, gen::fn_sub_3BB180_003bb180);
        }
    }
    // 0x00364ae8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00364B10 sub_364B10 -- 816 bytes; frame 0x1E0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [evtUnitApplyMoveKey] (frame, unit): command 1 (move): mode 0 walks to the point at +24 (sub_3B8730) and turns
// (sub_3B8690 / sub_3B8B30) unless +38; mode 1 follows the key's bezier path (sub_38D840 into a 304-byte frame
// buffer, sub_3B89F0; "bezier path move"); mode 2 places the actor (sub_3B7460). Speed through sub_38A900, footsteps
// through sub_3BB1D0, kPathMove from +37. Returns the key.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_364B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00364b10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = si(-1);
    s2 = 0;
    lw(s1, a1, unit::kKeyHead);
    for (;;) {
        // 0x00364b98
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00364b4c
        charge(ctx, 4);
        lb(v1, s1, key::kCmd);
        v0 = 1;
        if (v1 == v0) {
            // 0x00364b5c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x364B60u, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x00364b70
                charge(ctx, 4);
                lhu(v0, s1, key::kFrame);
                at = slt(s4, v0);
                if (at == 0) {
                    // 0x00364b80
                    charge(ctx, 3);
                    at = slt(s0, v0);
                    if (at != 0) {
                        // 0x00364b8c
                        charge(ctx, 2);
                        s0 = v0;
                        s2 = s1;
                    }
                }
            }
        }
        // 0x00364b94
        charge(ctx, 1);
        lw(s1, s1, key::kNext);
    }
    // 0x00364ba0
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x00364bb4
        charge(ctx, 3);
        lhu(v0, s2, key::kFrame);
        if (v0 == s4) {
            // 0x00364bcc
            charge(ctx, 4);
            lb(v1, s2, key::kArg20);
            v0 = 2;
            if (v1 == v0) {
                // 0x00364dbc
                charge(ctx, 5);
                lhu(a0, s3, unit::kResId);
                jal(ctx, 0x364DC0u, gen::fn_sub_3B5D10_003b5d10);
                if (v0 != 0) {
                    // 0x00364dd0
                    charge(ctx, 17);
                    lwc1(f0, s2, 24);
                    swc1(f0, sp, 0x1B0);
                    lwc1(f0, s2, 28);
                    swc1(f0, sp, 0x1B4);
                    lwc1(f0, s2, 32);
                    swc1(f0, sp, 0x1B8);
                    lwc1(f0, s2, 40);
                    swc1(f0, sp, 0x1A0);
                    lwc1(f0, s2, 44);
                    swc1(f0, sp, 0x1A4);
                    sw(zero, sp, 0x1A8);
                    a0 = v0;
                    a1 = addiu(sp, 0x1B0);
                    a2 = addiu(sp, 0x1A0);
                    a3 = 0;
                    jal(ctx, 0x364E0Cu, gen::fn_sub_3B7460_003b7460);
                }
            } else {
                // 0x00364bdc
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00364d0c
                    charge(ctx, 8);
                    lw(a0, s2, key::kPath);
                    a1 = addiu(sp, 0x70);
                    a2 = 0;
                    jal(ctx, 0x364D18u, gen::fn_sub_38D840_0038d840);
                    lb(v0, s2, 21);
                    if (v0 == 0) {
                        // 0x00364d2c
                        charge(ctx, 11);
                        lh(a0, s2, 22);
                        jal(ctx, 0x364D30u, gen::fn_sub_38A900_0038a900);
                        mov_s(f20, f0);
                        lb(v0, s2, 36);
                        s1 = sltu(0, v0);
                        lb(v0, s2, 37);
                        s0 = sltu(0, v0);
                        lb(v0, s2, 52);
                        if (v0 != 0) {
                            // 0x00364d58
                            charge(ctx, 9);
                            lb(v0, s2, 53);
                            v0 = addiu(v0, 1);
                            a2 = v0 & 0xFF;
                            lb(a3, s2, 54);
                            lb(t0, s2, 55);
                            lhu(a0, s3, unit::kResId);
                            a1 = 1;
                            jal(ctx, 0x364D74u, gen::fn_sub_3BB1D0_003bb1d0);
                        }
                        // 0x00364d7c
                        charge(ctx, 3);
                        lb(v0, sp, 0x70);
                        if (i64(v0) > 0) {
                            // 0x00364d88
                            charge(ctx, 13);
                            lhu(a0, s3, unit::kResId);
                            a1 = addiu(sp, 0x70);
                            mov_s(f12, f20);
                            a2 = s1;
                            jal(ctx, 0x364D98u, gen::fn_sub_3B89F0_003b89f0);
                            sw(s0, s3, unit::kPathMove);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -10544);  // "bezier path move\n"
                            jal(ctx, 0x364DACu, gen::fn_printf_005225a8);
                        }
                    }
                } else {
                    // 0x00364be8
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00364bf8
                        charge(ctx, 9);
                        lwc1(f0, s2, 24);
                        swc1(f0, sp, 0x1D0);
                        lwc1(f0, s2, 28);
                        swc1(f0, sp, 0x1D4);
                        lwc1(f0, s2, 32);
                        swc1(f0, sp, 0x1D8);
                        lb(v0, s2, 21);
                        if (v0 == 0) {
                            // 0x00364c1c
                            charge(ctx, 11);
                            lh(a0, s2, 22);
                            jal(ctx, 0x364C20u, gen::fn_sub_38A900_0038a900);
                            lhu(a0, s3, unit::kResId);
                            a1 = addiu(sp, 0x1D0);
                            mov_s(f12, f0);
                            jal(ctx, 0x364C34u, gen::fn_sub_3B8730_003b8730);
                            a1 = 1;
                            if (v0 == a1) {
                                // 0x00364c48
                                charge(ctx, 6);
                                lb(v0, s2, 37);
                                v0 = sltu(0, v0);
                                sw(v0, s3, unit::kPathMove);
                                lb(v0, s2, 52);
                                if (v0 != 0) {
                                    // 0x00364c60
                                    charge(ctx, 8);
                                    lb(v0, s2, 53);
                                    v0 = addiu(v0, 1);
                                    a2 = v0 & 0xFF;
                                    lb(a3, s2, 54);
                                    lb(t0, s2, 55);
                                    lhu(a0, s3, unit::kResId);
                                    jal(ctx, 0x364C78u, gen::fn_sub_3BB1D0_003bb1d0);
                                }
                                // 0x00364c80
                                charge(ctx, 3);
                                lb(v0, s2, 38);
                                if (v0 == 0) {
                                    // 0x00364c8c
                                    charge(ctx, 11);
                                    lhu(a0, s3, unit::kResId);
                                    jal(ctx, 0x364C90u, gen::fn_sub_3B5D10_003b5d10);
                                    a0 = addiu(v0, 4);
                                    a1 = addiu(sp, 0x1D0);
                                    a2 = addiu(sp, 0x1DC);
                                    jal(ctx, 0x364CA4u, gen::fn_sub_3B8690_003b8690);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x00364cb8
                                        charge(ctx, 4);
                                        v1 = addiu(sp, 0x1C0);
                                        v0 = 12;
                                        if (v1 != 0) {
                                            for (;;) {
                                                // 0x00364cc8
                                                charge(ctx, 7);
                                                sb(zero, v1, 0);
                                                v1 = addiu(v1, 1);
                                                v0 = addiu(v0, -1);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                        }
                                        // 0x00364ce4
                                        charge(ctx, 10);
                                        lwc1(f0, sp, 0x1DC);
                                        swc1(f0, sp, 0x1C4);
                                        lhu(a0, s3, unit::kResId);
                                        a1 = addiu(sp, 0x1C0);
                                        a2 = 15;
                                        a3 = 0;
                                        jal(ctx, 0x364CFCu, gen::fn_sub_3B8B30_003b8b30);
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x00364bf0
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00364e14
            charge(ctx, 1);
            v0 = s2;
        } else {
            // 0x00364bc0
            charge(ctx, 3);
            v0 = s2;
        }
    } else {
        // 0x00364ba8
        charge(ctx, 3);
        v0 = s2;
    }
    // 0x00364e18 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x00364E40 sub_364E40 -- 628 bytes; frame 0xD0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [evtUnitApplyLookKey] (frame, work, unit): command 6 on the model's head controller (model +296 for model kinds 1 / 3):
// at the key's frame mode 0 looks at the angles at +24 / +28 (sub_3B79A0, sub_319090, sub_319100), mode 1 resets
// (sub_319090 / sub_319190); at the start frame without keys the controller is reset.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_364E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00364e40
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s4 = a2;
    s2 = 0;
    lhu(a0, a2, 12);
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    a1 = sra(v1, 10);
    v1 = 1;
    if (a1 == v1) {
        // 0x00364ec0
        charge(ctx, 4);
        jal(ctx, 0x364EC0u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x00364ed0
            charge(ctx, 1);
            lw(s2, v0, 296);
        }
    } else {
        // 0x00364e90
        charge(ctx, 3);
        v1 = 3;
        if (a1 == v1) {
            // 0x00364ea4
            charge(ctx, 4);
            jal(ctx, 0x364EA4u, gen::fn_sub_3B5D10_003b5d10);
            if (v0 != 0) {
                // 0x00364eb4
                charge(ctx, 3);
                lw(s2, v0, 296);
            }
        } else {
            // 0x00364e9c
            charge(ctx, 2);
        }
    }
    // 0x00364ed4
    charge(ctx, 4);
    s3 = 0;
    lw(s4, s4, 108);
    for (;;) {
        // 0x00365034
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00364ee4
        charge(ctx, 4);
        lb(a0, s4, 16);
        v1 = 6;
        if (a0 == v1) {
            // 0x00364ef4
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x364EF8u, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x00364f08
                charge(ctx, 4);
                lhu(v1, s4, 0);
                at = slt(s1, v1);
                if (at == 0) {
                    // 0x00364f18
                    charge(ctx, 3);
                    s3 = s4;
                    if (v1 == s1) {
                        // 0x00364f24
                        charge(ctx, 3);
                        lb(a0, s4, 20);
                        if (a0 != 0) {
                            // 0x00364fe8
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x00364ff4
                                charge(ctx, 2);
                                if (s2 != 0) {
                                    // 0x00364ffc
                                    charge(ctx, 6);
                                    a0 = s2;
                                    jal(ctx, 0x365000u, gen::fn_sub_3191D0_003191d0);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x00365014
                                        charge(ctx, 7);
                                        a0 = s2;
                                        lwc1(f12, gp, -32004);  // 0x7CAFEC
                                        jal(ctx, 0x36501Cu, gen::fn_sub_319090_00319090);
                                        a0 = s2;
                                        jal(ctx, 0x365028u, gen::fn_sub_319190_00319190);
                                    }
                                }
                            }
                        } else {
                            // 0x00364f30
                            charge(ctx, 2);
                            if (s2 != 0) {
                                // 0x00364f38
                                charge(ctx, 5);
                                mtc1(zero, f20);
                                lb(v1, s4, 21);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x00364f68
                                    charge(ctx, 1);
                                    lwc1(f20, gp, -32544);  // 0x7CADD0
                                } else {
                                    // 0x00364f4c
                                    charge(ctx, 2);
                                    if (v1 == 0) {
                                        // 0x00364f5c
                                        charge(ctx, 3);
                                        lwc1(f20, gp, -32004);  // 0x7CAFEC
                                    } else {
                                        // 0x00364f54
                                        charge(ctx, 2);
                                    }
                                }
                                // 0x00364f6c
                                charge(ctx, 4);
                                v1 = addiu(sp, 0xB0);
                                v0 = 12;
                                if (v1 != 0) {
                                    for (;;) {
                                        // 0x00364f7c
                                        charge(ctx, 7);
                                        sb(zero, v1, 0);
                                        v1 = addiu(v1, 1);
                                        v0 = addiu(v0, -1);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                                // 0x00364f98
                                charge(ctx, 20);
                                lwc1(f0, s4, 24);
                                swc1(f0, sp, 0xC0);
                                lwc1(f0, s4, 28);
                                swc1(f0, sp, 0xC4);
                                sw(zero, sp, 0xC8);
                                a0 = addiu(sp, 0x70);
                                a1 = addiu(sp, 0xB0);
                                a2 = addiu(sp, 0xC0);
                                jal(ctx, 0x364FB8u, gen::fn_sub_3B79A0_003b79a0);
                                a0 = s2;
                                mov_s(f12, f20);
                                jal(ctx, 0x364FC8u, gen::fn_sub_319090_00319090);
                                a0 = s2;
                                a1 = addiu(sp, 0x90);
                                jal(ctx, 0x364FD8u, gen::fn_sub_319100_00319100);
                            }
                        }
                    }
                }
            }
        }
        // 0x00365030
        charge(ctx, 1);
        lw(s4, s4, 76);
    }
    // 0x0036503c
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x00365044
        charge(ctx, 3);
        lw(v1, s0, work::kStartFrame);
        if (v1 == s1) {
            // 0x00365050
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00365058
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x36505Cu, gen::fn_sub_3191D0_003191d0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00365070
                    charge(ctx, 7);
                    a0 = s2;
                    lwc1(f12, gp, -32004);  // 0x7CAFEC
                    jal(ctx, 0x365078u, gen::fn_sub_319090_00319090);
                    a0 = s2;
                    jal(ctx, 0x365084u, gen::fn_sub_319190_00319190);
                }
            }
        }
    }
    // 0x0036508c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x003650C0 sub_3650C0 -- 400 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyExprKey] (frame, work, unit): command 7 on the model's controller (model +296): mode 0 sub_39E880(work,
// ctl, +21, +22, +24), mode 1 sub_39EA20(ctl, +21); without keys sub_39E820(ctl).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3650C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003650c0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s0 = 0;
    lhu(a0, a2, 12);
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    a1 = sra(v1, 10);
    v1 = 1;
    if (a1 == v1) {
        // 0x0036513c
        charge(ctx, 4);
        jal(ctx, 0x36513Cu, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x0036514c
            charge(ctx, 1);
            lw(s0, v0, 296);
        }
    } else {
        // 0x0036510c
        charge(ctx, 3);
        v1 = 3;
        if (a1 == v1) {
            // 0x00365120
            charge(ctx, 4);
            jal(ctx, 0x365120u, gen::fn_sub_3B5D10_003b5d10);
            if (v0 != 0) {
                // 0x00365130
                charge(ctx, 3);
                lw(s0, v0, 296);
            }
        } else {
            // 0x00365118
            charge(ctx, 2);
        }
    }
    // 0x00365150
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00365158
        charge(ctx, 4);
        s1 = 0;
        lw(s2, s2, 108);
        for (;;) {
            // 0x00365208
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00365168
            charge(ctx, 4);
            lb(a0, s2, 16);
            v1 = 7;
            if (a0 == v1) {
                // 0x00365178
                charge(ctx, 5);
                a0 = s2;
                jal(ctx, 0x36517Cu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x0036518c
                    charge(ctx, 4);
                    lhu(v1, s2, 0);
                    at = slt(s4, v1);
                    if (at == 0) {
                        // 0x0036519c
                        charge(ctx, 3);
                        s1 = s2;
                        if (v1 == s4) {
                            // 0x003651a8
                            charge(ctx, 3);
                            lb(a0, s2, 20);
                            if (a0 != 0) {
                                // 0x003651e0
                                charge(ctx, 3);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x003651ec
                                    charge(ctx, 2);
                                    if (s0 != 0) {
                                        // 0x003651f4
                                        charge(ctx, 4);
                                        lb(a1, s2, 21);
                                        a0 = s0;
                                        jal(ctx, 0x3651FCu, gen::fn_sub_39EA20_0039ea20);
                                    }
                                }
                            } else {
                                // 0x003651b4
                                charge(ctx, 2);
                                if (s0 != 0) {
                                    // 0x003651bc
                                    charge(ctx, 9);
                                    lb(a2, s2, 21);
                                    lb(a3, s2, 22);
                                    a0 = s3;
                                    a1 = s0;
                                    lw(t0, s2, 24);
                                    jal(ctx, 0x3651D0u, gen::fn_sub_39E880_0039e880);
                                }
                            }
                        }
                    }
                }
            }
            // 0x00365204
            charge(ctx, 1);
            lw(s2, s2, 76);
        }
        // 0x00365210
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x00365218
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x00365220
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x365224u, gen::fn_sub_39E820_0039e820);
            }
        }
    }
    // 0x0036522c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00365250 sub_365250 -- 260 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyKey5] (frame, work, unit): command 5 keys firing now: sub_3BB010(resId, value) with the value at +20
// (mode +21 == 0) or the one sub_397630(work, +20) gives (mode 1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365250(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00365250
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    lw(s0, a2, unit::kKeyHead);
    for (;;) {
        // 0x0036532c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365280
        charge(ctx, 4);
        lb(a0, s0, key::kCmd);
        v1 = 5;
        if (a0 == v1) {
            // 0x00365290
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x365294u, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x003652a4
                charge(ctx, 4);
                lhu(v1, s0, key::kFrame);
                at = slt(s3, v1);
                if (at == 0) {
                    // 0x003652b4
                    charge(ctx, 2);
                    if (v1 == s3) {
                        // 0x003652bc
                        charge(ctx, 4);
                        lb(a0, s0, 21);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x003652f4
                            charge(ctx, 9);
                            sw(zero, sp, 0x5C);
                            lb(a1, s0, key::kArg20);
                            a0 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x365304u, gen::fn_sub_397630_00397630);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x00365318
                                charge(ctx, 4);
                                lbu(a1, sp, 0x5C);
                                lhu(a0, s1, unit::kResId);
                                jal(ctx, 0x365320u, gen::fn_sub_3BB010_003bb010);
                            }
                        } else {
                            // 0x003652cc
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x003652dc
                                charge(ctx, 6);
                                lbu(a1, s0, key::kArg20);
                                lhu(a0, s1, unit::kResId);
                                jal(ctx, 0x3652E4u, gen::fn_sub_3BB010_003bb010);
                            } else {
                                // 0x003652d4
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
        // 0x00365328
        charge(ctx, 1);
        lw(s0, s0, key::kNext);
    }
    // 0x00365334
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00365360 sub_365360 -- 208 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUnitApplyMotionKey] (frame, work, unit): command 8 keys firing now: sub_3B8E10(resId, motion +24, blend +20,
// loop +25 != 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365360(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00365360
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a2;
    s0 = si(-1);
    lw(s1, a2, unit::kKeyHead);
    for (;;) {
        // 0x00365408
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365390
        charge(ctx, 4);
        lb(a0, s1, key::kCmd);
        v1 = 8;
        if (a0 == v1) {
            // 0x003653a0
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x3653A4u, gen::fn_sub_360ED0_00360ed0);
            if (v0 != 0) {
                // 0x003653b4
                charge(ctx, 4);
                lhu(v1, s1, key::kFrame);
                at = slt(s3, v1);
                if (at == 0) {
                    // 0x003653c4
                    charge(ctx, 3);
                    at = slt(s0, v1);
                    if (at != 0) {
                        // 0x003653d0
                        charge(ctx, 1);
                        s0 = v1;
                    }
                    // 0x003653d4
                    charge(ctx, 2);
                    if (v1 == s3) {
                        // 0x003653dc
                        charge(ctx, 4);
                        a3 = 0;
                        lb(v0, s1, 25);
                        if (v0 != 0) {
                            // 0x003653ec
                            charge(ctx, 1);
                            a3 = 1;
                        }
                        // 0x003653f0
                        charge(ctx, 5);
                        lh(a2, s1, key::kArg20);
                        lhu(a0, s2, unit::kResId);
                        lbu(a1, s1, 24);
                        jal(ctx, 0x3653FCu, gen::fn_sub_3B8E10_003b8e10);
                    }
                }
            }
        }
        // 0x00365404
        charge(ctx, 1);
        lw(s1, s1, key::kNext);
    }
    // 0x00365410
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00365430 sub_365430 -- 436 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyModelUnits] (frame, work): for every model unit (types 1 / 48) whose actor exists: at the start frame (not in
// play mode) put it at its setup position / rotation (sub_3B78B0, sub_3B7930 with the constant at 0x69D6E8,
// sub_3B8F30, sub_3B8E10 with the unit's colour byte); then its keys: pos change, move, rotation, scale, show, 9,
// expression, look, 5 and motion (sub_3646D0 .. sub_365360).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00365430
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a1, work::kUnitHead);
    for (;;) {
        // 0x003655c0
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365458
        charge(ctx, 4);
        lw(a0, s0, unit::kType);
        v1 = 1;
        if (a0 != v1) {
            // 0x00365468
            charge(ctx, 3);
            v1 = 48;
            if (a0 == v1) {
                goto L_00365474;
            }
            goto L_003655bc;
        }
    L_00365474:
        charge(ctx, 5);
        lhu(a0, s0, unit::kResId);
        jal(ctx, 0x365478u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x00365488
            charge(ctx, 4);
            lw(v0, s1, work::kFlags);
            v0 = v0 & 0x8;
            if (v0 == 0) {
                // 0x00365498
                charge(ctx, 3);
                lw(v0, s1, work::kStartFrame);
                if (s2 == v0) {
                    // 0x003654a4
                    charge(ctx, 25);
                    lhu(a0, s0, unit::kResId);
                    a1 = addiu(s0, 60);
                    a2 = addiu(s0, 72);
                    jal(ctx, 0x3654B0u, gen::fn_sub_3B78B0_003b78b0);
                    a1 = addiu(sp, 0x40);
                    v0 = 0x6A0000;
                    ld(v1, v0, -10520);  // 0x69D6E8
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -10512);  // 0x69D6F0
                    sd(v1, sp, 0x40);
                    swc1(f0, sp, 0x48);
                    lhu(a0, s0, unit::kResId);
                    jal(ctx, 0x3654D8u, gen::fn_sub_3B7930_003b7930);
                    lhu(a0, s0, unit::kResId);
                    jal(ctx, 0x3654E4u, gen::fn_sub_3B8F30_003b8f30);
                    lhu(a0, s0, unit::kResId);
                    lbu(a1, s0, 87);
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x3654FCu, gen::fn_sub_3B8E10_003b8e10);
                    sw(zero, s0, unit::kPathMove);
                }
            }
            // 0x00365508
            charge(ctx, 45);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x365510u, gen::fn_sub_3646D0_003646d0);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x365520u, gen::fn_sub_364B10_00364b10);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x365530u, gen::fn_sub_364470_00364470);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x365540u, gen::fn_sub_3645C0_003645c0);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x365554u, gen::fn_sub_3648E0_003648e0);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x365564u, gen::fn_sub_364A30_00364a30);
            a0 = s2;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x365578u, gen::fn_sub_3650C0_003650c0);
            a0 = s2;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x36558Cu, gen::fn_sub_364E40_00364e40);
            a0 = s2;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3655A0u, gen::fn_sub_365250_00365250);
            a0 = s2;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3655B4u, gen::fn_sub_365360_00365360);
        }
    L_003655bc:
        charge(ctx, 1);
        lw(s0, s0, unit::kNext);
    }
    // 0x003655c8
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003655F0 sub_3655F0 -- 496 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCameraUnitApplyKey] (frame, unit, work): the camera-model unit's latest firing key; when it fires now: mode 0 moves
// the camera model 0x1E58 to the key's position / rotation over kLength (sub_3BB400, sub_3B87F0, sub_3B8B30,
// sub_3B8E80; "move direct length=%d"), mode 1 links it to a model (sub_3BB390; "link camera resrc").
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3655F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003655f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    s3 = si(-1);
    lw(s4, a1, 108);
    for (;;) {
        // 0x00365664
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365628
        charge(ctx, 5);
        a0 = s4;
        jal(ctx, 0x36562Cu, gen::fn_sub_360ED0_00360ed0);
        if (v0 != 0) {
            // 0x0036563c
            charge(ctx, 4);
            lhu(v0, s4, key::kFrame);
            at = slt(s2, v0);
            if (at == 0) {
                // 0x0036564c
                charge(ctx, 3);
                at = slt(s3, v0);
                if (at != 0) {
                    // 0x00365658
                    charge(ctx, 2);
                    s3 = v0;
                    s0 = s4;
                }
            }
        }
        // 0x00365660
        charge(ctx, 1);
        lw(s4, s4, key::kNext);
    }
    // 0x0036566c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00365680
        charge(ctx, 3);
        lhu(v0, s0, key::kFrame);
        if (v0 == s2) {
            // 0x00365698
            charge(ctx, 5);
            lhu(a0, s1, unit::kResId);
            jal(ctx, 0x36569Cu, gen::fn_sub_3B5D10_003b5d10);
            if (v0 != 0) {
                // 0x003656b8
                charge(ctx, 4);
                lb(v1, s0, 18);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00365770
                    charge(ctx, 7);
                    lhu(a1, s0, key::kArg20);
                    v0 = 0xF0000;
                    v0 = v0 | 0xFC00;
                    v0 = a1 & v0;
                    v0 = sra(v0, 10);
                    if (v0 != 0) {
                        // 0x0036578c
                        charge(ctx, 11);
                        lh(v0, s0, 22);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = 7768;
                        jal(ctx, 0x3657A0u, gen::fn_sub_3BB390_003bb390);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -10464);  // "link camera resrc\n"
                        jal(ctx, 0x3657B0u, gen::fn_printf_005225a8);
                    }
                } else {
                    // 0x003656c8
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x003656d8
                        charge(ctx, 38);
                        a0 = 7768;
                        jal(ctx, 0x3656DCu, gen::fn_sub_3BB400_003bb400);
                        lwc1(f0, s0, 24);
                        swc1(f0, sp, 0x70);
                        lwc1(f0, s0, 28);
                        swc1(f0, sp, 0x74);
                        lwc1(f0, s0, 32);
                        swc1(f0, sp, 0x78);
                        lwc1(f0, s0, 36);
                        swc1(f0, sp, 0x60);
                        lwc1(f0, s0, 40);
                        swc1(f0, sp, 0x64);
                        sw(zero, sp, 0x68);
                        lhu(a2, s0, key::kLength);
                        lhu(a0, s1, unit::kResId);
                        a1 = addiu(sp, 0x70);
                        lb(a3, s0, 48);
                        jal(ctx, 0x365720u, gen::fn_sub_3B87F0_003b87f0);
                        lhu(a2, s0, key::kLength);
                        lbu(a3, s0, 48);
                        lhu(a0, s1, unit::kResId);
                        a1 = addiu(sp, 0x60);
                        jal(ctx, 0x365738u, gen::fn_sub_3B8B30_003b8b30);
                        lhu(a1, s0, key::kLength);
                        lhu(a0, s1, unit::kResId);
                        lwc1(f12, s0, 44);
                        jal(ctx, 0x36574Cu, gen::fn_sub_3B8E80_003b8e80);
                        lhu(a1, s0, key::kLength);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -10496);  // "move direct length=%d\n"
                        jal(ctx, 0x365760u, gen::fn_printf_005225a8);
                    } else {
                        // 0x003656d0
                        charge(ctx, 2);
                    }
                }
                // 0x003657b8
                charge(ctx, 1);
                v0 = s0;
            } else {
                // 0x003656ac
                charge(ctx, 3);
                v0 = s0;
            }
        } else {
            // 0x0036568c
            charge(ctx, 3);
            v0 = s0;
        }
    } else {
        // 0x00365674
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x003657bc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003657E0 sub_3657E0 -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyCameraUnits] (frame, work): for each type-33 unit: at the start frame reset the camera model (sub_3BB400,
// sub_3B78B0 with the unit's setup pose, sub_3B8F30, model +256 = kFieldScale), then sub_3655F0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3657E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003657e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a1, work::kUnitHead);
    for (;;) {
        // 0x00365884
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365808
        charge(ctx, 4);
        lw(a0, s0, unit::kType);
        v1 = 33;
        if (a0 == v1) {
            // 0x00365818
            charge(ctx, 3);
            lw(v0, s1, work::kStartFrame);
            if (s2 == v0) {
                // 0x00365824
                charge(ctx, 16);
                a0 = 7768;
                jal(ctx, 0x365828u, gen::fn_sub_3BB400_003bb400);
                lhu(a0, s0, unit::kResId);
                a1 = addiu(s0, 60);
                a2 = addiu(s0, 72);
                jal(ctx, 0x36583Cu, gen::fn_sub_3B78B0_003b78b0);
                lhu(a0, s0, unit::kResId);
                jal(ctx, 0x365848u, gen::fn_sub_3B8F30_003b8f30);
                a0 = 7768;
                jal(ctx, 0x365854u, gen::fn_sub_3B5D10_003b5d10);
                if (v0 != 0) {
                    // 0x00365864
                    charge(ctx, 2);
                    lwc1(f0, s1, work::kFieldScale);
                    swc1(f0, v0, 256);
                }
            }
            // 0x0036586c
            charge(ctx, 5);
            a0 = s2;
            a1 = s0;
            a2 = s1;
            jal(ctx, 0x365878u, gen::fn_sub_3655F0_003655f0);
        }
        // 0x00365880
        charge(ctx, 1);
        lw(s0, s0, unit::kNext);
    }
    // 0x0036588c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003658B0 sub_3658B0 -- 396 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyModelShowUnits] (frame, work): type-47 units: keys firing now on an existing model (+18): command 1
// sub_3B8FF0, command 0 sub_3B9500.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3658B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003658b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s2, a1, work::kUnitHead);
    for (;;) {
        // 0x00365a14
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003658d8
        charge(ctx, 4);
        lw(a0, s2, unit::kType);
        v1 = 47;
        if (a0 == v1) {
            // 0x003658e8
            charge(ctx, 4);
            s0 = si(-1);
            lw(s1, s2, unit::kKeyHead);
            for (;;) {
                // 0x00365a08
                charge(ctx, 2);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003658f8
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x3658FCu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x0036590c
                    charge(ctx, 4);
                    lhu(v0, s1, key::kFrame);
                    at = slt(s3, v0);
                    if (at == 0) {
                        // 0x0036591c
                        charge(ctx, 3);
                        at = slt(s0, v0);
                        if (at != 0) {
                            // 0x00365928
                            charge(ctx, 1);
                            s0 = v0;
                        }
                    }
                    // 0x0036592c
                    charge(ctx, 6);
                    lhu(a0, s1, 18);
                    jal(ctx, 0x365930u, gen::fn_sub_3B5D10_003b5d10);
                    a0 = v0;
                    if (a0 != 0) {
                        // 0x00365944
                        charge(ctx, 3);
                        lhu(v1, s1, key::kFrame);
                        if (v1 == s3) {
                            // 0x00365950
                            charge(ctx, 4);
                            lb(v1, s1, key::kCmd);
                            a1 = 1;
                            if (v1 == a1) {
                                // 0x003659a0
                                charge(ctx, 7);
                                lb(a2, s1, key::kArg20);
                                t0 = 0;
                                lh(t1, s1, 24);
                                lh(a3, s1, 22);
                                lb(v0, s1, 21);
                                if (v0 == 0) {
                                    // 0x003659bc
                                    charge(ctx, 1);
                                    t0 = a1;
                                }
                                // 0x003659c0
                                charge(ctx, 3);
                                lh(v0, s1, 26);
                                if (i64(v0) > 0) {
                                    // 0x003659dc
                                    charge(ctx, 7);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x42C80000;
                                    mtc1(v0, f0);
                                    div_s(f12, f1, f0);
                                } else {
                                    // 0x003659cc
                                    charge(ctx, 4);
                                    v0 = 0x3F800000;
                                    mtc1(v0, f12);
                                }
                                // 0x003659f8
                                charge(ctx, 3);
                                a1 = 0;
                                jal(ctx, 0x3659FCu, gen::fn_sub_3B8FF0_003b8ff0);
                            } else {
                                // 0x00365960
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x00365970
                                    charge(ctx, 3);
                                    lb(v0, s1, key::kArg20);
                                    if (v0 != 0) {
                                        // 0x0036598c
                                        charge(ctx, 5);
                                        a1 = 0;
                                        jal(ctx, 0x365990u, gen::fn_sub_3B9500_003b9500);
                                    } else {
                                        // 0x0036597c
                                        charge(ctx, 4);
                                        jal(ctx, 0x36597Cu, gen::fn_sub_3B9500_003b9500);
                                    }
                                } else {
                                    // 0x00365968
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x00365a04
                charge(ctx, 1);
                lw(s1, s1, key::kNext);
            }
        }
        // 0x00365a10
        charge(ctx, 1);
        lw(s2, s2, unit::kNext);
    }
    // 0x00365a1c
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00365A40 sub_365A40 -- 296 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyVisibilityUnits] (frame, work): type-49 units: command-0 keys firing now on an existing model (+18):
// sub_3B9550(model, +20 == 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365A40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00365a40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, a1, work::kUnitHead);
    for (;;) {
        // 0x00365b3c
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365a6c
        charge(ctx, 4);
        lw(a0, s3, unit::kType);
        v1 = 49;
        if (a0 == v1) {
            // 0x00365a7c
            charge(ctx, 4);
            s1 = si(-1);
            lw(s2, s3, unit::kKeyHead);
            for (;;) {
                // 0x00365b30
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00365a8c
                charge(ctx, 5);
                a0 = s2;
                jal(ctx, 0x365A90u, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x00365aa0
                    charge(ctx, 4);
                    lhu(v0, s2, key::kFrame);
                    at = slt(s4, v0);
                    if (at == 0) {
                        // 0x00365ab0
                        charge(ctx, 3);
                        at = slt(s1, v0);
                        if (at != 0) {
                            // 0x00365abc
                            charge(ctx, 1);
                            s1 = v0;
                        }
                    }
                    // 0x00365ac0
                    charge(ctx, 6);
                    lhu(s0, s2, 18);
                    a0 = s0;
                    jal(ctx, 0x365AC8u, gen::fn_sub_3B5D10_003b5d10);
                    if (v0 != 0) {
                        // 0x00365ad8
                        charge(ctx, 3);
                        lhu(v1, s2, key::kFrame);
                        if (v1 == s4) {
                            // 0x00365ae4
                            charge(ctx, 3);
                            lb(v1, s2, key::kCmd);
                            if (v1 == 0) {
                                // 0x00365af8
                                charge(ctx, 3);
                                lb(v0, s2, key::kArg20);
                                if (v0 != 0) {
                                    // 0x00365b1c
                                    charge(ctx, 4);
                                    a0 = s0;
                                    a1 = 0;
                                    jal(ctx, 0x365B24u, gen::fn_sub_3B9550_003b9550);
                                } else {
                                    // 0x00365b04
                                    charge(ctx, 6);
                                    a0 = s0;
                                    a1 = 1;
                                    jal(ctx, 0x365B0Cu, gen::fn_sub_3B9550_003b9550);
                                }
                            } else {
                                // 0x00365af0
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00365b2c
                charge(ctx, 1);
                lw(s2, s2, key::kNext);
            }
        }
        // 0x00365b38
        charge(ctx, 1);
        lw(s3, s3, unit::kNext);
    }
    // 0x00365b44
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00365B70 sub_365B70 -- 352 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyVolumeUnits] (frame, work): type-35 units: keys firing now: command 0 sub_395430(work, channel, +24, +26,
// +28), command 1 sub_3954E0(channel); without keys at the start frame sub_3954E0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365B70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00365b70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lw(s3, a1, work::kUnitHead);
    for (;;) {
        // 0x00365ca0
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00365ba4
        charge(ctx, 4);
        lw(a0, s3, unit::kType);
        v1 = 35;
        if (a0 == v1) {
            // 0x00365bb4
            charge(ctx, 5);
            s0 = si(-1);
            s1 = 0;
            lw(s2, s3, unit::kKeyHead);
            for (;;) {
                // 0x00365c74
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00365bc8
                charge(ctx, 5);
                a0 = s2;
                jal(ctx, 0x365BCCu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x00365bdc
                    charge(ctx, 4);
                    lhu(v1, s2, key::kFrame);
                    at = slt(s5, v1);
                    if (at == 0) {
                        // 0x00365bec
                        charge(ctx, 3);
                        at = slt(s0, v1);
                        if (at != 0) {
                            // 0x00365bf8
                            charge(ctx, 2);
                            s0 = v1;
                            s1 = s2;
                        }
                    }
                    // 0x00365c00
                    charge(ctx, 2);
                    if (v1 == s5) {
                        // 0x00365c08
                        charge(ctx, 4);
                        lb(a0, s2, key::kCmd);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x00365c18
                            charge(ctx, 3);
                            v1 = 2;
                            if (a0 != v1) {
                                // 0x00365c24
                                charge(ctx, 3);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x00365c64
                                    charge(ctx, 3);
                                    lw(a0, s3, unit::kParam);
                                    jal(ctx, 0x365C68u, gen::fn_sub_3954E0_003954e0);
                                } else {
                                    // 0x00365c30
                                    charge(ctx, 2);
                                    if (a0 == 0) {
                                        // 0x00365c40
                                        charge(ctx, 9);
                                        lh(a2, s2, 24);
                                        lh(a3, s2, 26);
                                        lh(t0, s2, 28);
                                        a0 = s4;
                                        lw(a1, s3, unit::kParam);
                                        jal(ctx, 0x365C54u, gen::fn_sub_395430_00395430);
                                    } else {
                                        // 0x00365c38
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                    }
                }
                // 0x00365c70
                charge(ctx, 1);
                lw(s2, s2, key::kNext);
            }
            // 0x00365c7c
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x00365c84
                charge(ctx, 3);
                lw(v1, s4, work::kStartFrame);
                if (v1 == s5) {
                    // 0x00365c90
                    charge(ctx, 3);
                    lw(a0, s3, unit::kParam);
                    jal(ctx, 0x365C94u, gen::fn_sub_3954E0_003954e0);
                }
            }
        }
        // 0x00365c9c
        charge(ctx, 1);
        lw(s3, s3, unit::kNext);
    }
    // 0x00365ca8
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

// 0x00365CD0 sub_365CD0 -- 684 bytes; frame 0xC0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyP3EffectUnits] (frame, work): with an effect set (kEffectSet): at the start frame sub_3969B0; type-37 units,
// for each of the 16 effect slots in order, keys of that slot (+17) firing now: 0 create ("p3 eff create",
// sub_396760 + sub_3B78B0), 1 move ("effect move", sub_3B87F0 / sub_3B8B30), 2 sub_396910, 3 motion (sub_3B8E10).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365CD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00365cd0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lw(a0, a1, work::kEffectSet);
    if (a0 != 0) {
        // 0x00365d08
        charge(ctx, 3);
        lw(v1, s4, work::kStartFrame);
        if (s5 == v1) {
            // 0x00365d14
            charge(ctx, 2);
            jal(ctx, 0x365D14u, gen::fn_sub_3969B0_003969b0);
        }
        // 0x00365d1c
        charge(ctx, 3);
        lw(s3, s4, work::kUnitHead);
        for (;;) {
            // 0x00365f48
            charge(ctx, 2);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00365d28
            charge(ctx, 4);
            lw(a0, s3, unit::kType);
            v1 = 37;
            if (a0 == v1) {
                // 0x00365d38
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00365f38
                    charge(ctx, 3);
                    v1 = slti(s1, 16);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00365d44
                    charge(ctx, 3);
                    lw(s2, s3, unit::kKeyHead);
                    for (;;) {
                        // 0x00365f2c
                        charge(ctx, 2);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00365d50
                        charge(ctx, 3);
                        lb(v1, s2, 17);
                        if (v1 == s1) {
                            // 0x00365d5c
                            charge(ctx, 5);
                            a0 = s2;
                            jal(ctx, 0x365D60u, gen::fn_sub_360ED0_00360ed0);
                            if (v0 != 0) {
                                // 0x00365d70
                                charge(ctx, 4);
                                lhu(v1, s2, key::kFrame);
                                at = slt(s5, v1);
                                if (at == 0) {
                                    // 0x00365d80
                                    charge(ctx, 2);
                                    if (v1 == s5) {
                                        // 0x00365d88
                                        charge(ctx, 4);
                                        lb(a0, s2, key::kCmd);
                                        v1 = 3;
                                        if (a0 == v1) {
                                            // 0x00365f00
                                            charge(ctx, 10);
                                            lw(a0, s4, work::kEffectSet);
                                            a1 = s1;
                                            jal(ctx, 0x365F08u, gen::fn_sub_3968A0_003968a0);
                                            a0 = v0 & 0xFFFF;
                                            lh(a2, s2, key::kArg20);
                                            lbu(a1, s2, 18);
                                            a3 = 0;
                                            jal(ctx, 0x365F20u, gen::fn_sub_3B8E10_003b8e10);
                                        } else {
                                            // 0x00365d98
                                            charge(ctx, 3);
                                            v1 = 2;
                                            if (a0 == v1) {
                                                // 0x00365ee8
                                                charge(ctx, 6);
                                                lw(a0, s4, work::kEffectSet);
                                                a1 = s1;
                                                jal(ctx, 0x365EF0u, gen::fn_sub_396910_00396910);
                                            } else {
                                                // 0x00365da4
                                                charge(ctx, 3);
                                                v1 = 1;
                                                if (a0 == v1) {
                                                    // 0x00365e50
                                                    charge(ctx, 7);
                                                    lw(a0, s4, work::kEffectSet);
                                                    a1 = s1;
                                                    jal(ctx, 0x365E58u, gen::fn_sub_3968A0_003968a0);
                                                    s0 = v0 & 0xFFFF;
                                                    if (s0 != 0) {
                                                        // 0x00365e6c
                                                        charge(ctx, 31);
                                                        lwc1(f0, s2, key::kArg20);
                                                        swc1(f0, sp, 0x90);
                                                        lwc1(f0, s2, 24);
                                                        swc1(f0, sp, 0x94);
                                                        lwc1(f0, s2, 28);
                                                        swc1(f0, sp, 0x98);
                                                        lwc1(f0, s2, 32);
                                                        swc1(f0, sp, 0x80);
                                                        lwc1(f0, s2, 36);
                                                        swc1(f0, sp, 0x84);
                                                        lwc1(f0, s2, 40);
                                                        swc1(f0, sp, 0x88);
                                                        lh(s6, s2, 18);
                                                        a0 = s0;
                                                        a1 = addiu(sp, 0x90);
                                                        a2 = s6;
                                                        a3 = 0;
                                                        jal(ctx, 0x365EB0u, gen::fn_sub_3B87F0_003b87f0);
                                                        a0 = s0;
                                                        a1 = addiu(sp, 0x80);
                                                        a2 = s6;
                                                        a3 = 0;
                                                        jal(ctx, 0x365EC8u, gen::fn_sub_3B8B30_003b8b30);
                                                        a0 = 0x6A0000;
                                                        a0 = addiu(a0, -10424);  // "effect move\n"
                                                        jal(ctx, 0x365ED8u, gen::fn_printf_005225a8);
                                                    }
                                                } else {
                                                    // 0x00365db0
                                                    charge(ctx, 2);
                                                    if (a0 == 0) {
                                                        // 0x00365dc0
                                                        charge(ctx, 14);
                                                        lb(a2, s2, 18);
                                                        lb(v0, s2, 19);
                                                        a3 = sltu(0, v0);
                                                        lw(a0, s4, work::kEffectSet);
                                                        a1 = s1;
                                                        jal(ctx, 0x365DD4u, gen::fn_sub_396760_00396760);
                                                        lw(a0, s4, work::kEffectSet);
                                                        a1 = s1;
                                                        jal(ctx, 0x365DE4u, gen::fn_sub_3968A0_003968a0);
                                                        a0 = v0 & 0xFFFF;
                                                        if (a0 != 0) {
                                                            // 0x00365df8
                                                            charge(ctx, 22);
                                                            lwc1(f0, s2, key::kArg20);
                                                            swc1(f0, sp, 0xB0);
                                                            lwc1(f0, s2, 24);
                                                            swc1(f0, sp, 0xB4);
                                                            lwc1(f0, s2, 28);
                                                            swc1(f0, sp, 0xB8);
                                                            lwc1(f0, s2, 32);
                                                            swc1(f0, sp, 0xA0);
                                                            lwc1(f0, s2, 36);
                                                            swc1(f0, sp, 0xA4);
                                                            lwc1(f0, s2, 40);
                                                            swc1(f0, sp, 0xA8);
                                                            a1 = addiu(sp, 0xB0);
                                                            a2 = addiu(sp, 0xA0);
                                                            jal(ctx, 0x365E30u, gen::fn_sub_3B78B0_003b78b0);
                                                            a0 = 0x6A0000;
                                                            a0 = addiu(a0, -10440);  // "p3 eff create\n"
                                                            jal(ctx, 0x365E40u, gen::fn_printf_005225a8);
                                                        }
                                                    } else {
                                                        // 0x00365db8
                                                        charge(ctx, 2);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // 0x00365f28
                        charge(ctx, 1);
                        lw(s2, s2, key::kNext);
                    }
                    // 0x00365f34
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
            }
            // 0x00365f44
            charge(ctx, 1);
            lw(s3, s3, unit::kNext);
        }
    }
    // 0x00365f50 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x00365F80 sub_365F80 -- 648 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyMessageUnits] (frame, work): with a scene and an open message handle: the message unit's (type 4) keys whose
// condition holds, sound is on and the message number resolves (sub_38A4B0) at this frame: a branch message
// (sub_39F750) records the branch slot (kBranchPos; "branch message mesno ..."); others are shown through sub_39F210
// (or a comu message, sub_3C9790, when +22 == 1 and kMode bit 3). A waiting key (+20 == 0) sets kFlagMessage
// (kFlagComuMessage for comu messages).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_365F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00365f80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    fp = a0;
    s5 = a1;
    sw(zero, sp, 0xAC);
    sw(zero, sp, 0xA8);
    s2 = 0;
    s1 = 0;
    s0 = si(-1);
    s6 = s0;
    s7 = 0;
    if (s5 != 0) {
        // 0x00365fd8
        charge(ctx, 3);
        lw(v1, s5, work::kScene);
        if (v1 != 0) {
            // 0x00365fe4
            charge(ctx, 5);
            a0 = addiu(s5, 2092);
            jal(ctx, 0x365FE8u, gen::fn_sub_39EEE0_0039eee0);
            if (v0 != 0) {
                // 0x00365ff8
                charge(ctx, 3);
                lw(s4, s5, work::kUnitHead);
                for (;;) {
                    // 0x0036613c
                    charge(ctx, 2);
                    if (s4 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00366004
                    charge(ctx, 4);
                    lw(a0, s4, unit::kType);
                    v1 = 4;
                    if (a0 == v1) {
                        // 0x00366014
                        charge(ctx, 3);
                        lw(s3, s4, unit::kKeyHead);
                        for (;;) {
                            // 0x00366130
                            charge(ctx, 2);
                            if (s3 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00366020
                            charge(ctx, 5);
                            a0 = s3;
                            jal(ctx, 0x366024u, gen::fn_sub_360ED0_00360ed0);
                            if (v0 != 0) {
                                // 0x00366034
                                charge(ctx, 6);
                                lw(v1, s5, work::kFlags);
                                v1 = v1 & 0x10;
                                a0 = sltu(0, v1);
                                v1 = 1;
                                if (a0 != v1) {
                                    // 0x0036604c
                                    charge(ctx, 8);
                                    a0 = s5;
                                    a1 = s3;
                                    a2 = addiu(sp, 0xAC);
                                    a3 = addiu(sp, 0xA8);
                                    jal(ctx, 0x36605Cu, gen::fn_sub_38A4B0_0038a4b0);
                                    if (v0 != 0) {
                                        // 0x0036606c
                                        charge(ctx, 3);
                                        lhu(v1, s3, key::kFrame);
                                        if (v1 == fp) {
                                            // 0x00366078
                                            charge(ctx, 6);
                                            a0 = addiu(s5, 2092);
                                            lw(a1, sp, 0xAC);
                                            jal(ctx, 0x366080u, gen::fn_sub_39F750_0039f750);
                                            if (v0 != 0) {
                                                // 0x003660c0
                                                charge(ctx, 2);
                                                if (v0 != 0) {
                                                    // 0x003660c8
                                                    charge(ctx, 3);
                                                    lw(v0, sp, 0xA8);
                                                    if (v0 != 0) {
                                                        // 0x003660d4
                                                        charge(ctx, 3);
                                                        at = slti(v0, 11);
                                                        if (at == 0) {
                                                            goto L_003660e0;
                                                        }
                                                        // 0x003660ec
                                                        charge(ctx, 1);
                                                        v0 = addiu(v0, -1);
                                                        goto L_003660f0;
                                                    }
                                                L_003660e0:
                                                    charge(ctx, 3);
                                                    v0 = si(-1);
                                                L_003660f0:
                                                    charge(ctx, 8);
                                                    sh(v0, s5, work::kBranchPos);
                                                    lw(a1, sp, 0xAC);
                                                    s6 = a1;
                                                    s7 = dsll32(v0, 16);
                                                    s7 = dsra32(s7, 16);
                                                    lb(v0, s3, key::kArg20);
                                                    if (v0 == 0) {
                                                        // 0x00366110
                                                        charge(ctx, 1);
                                                        s2 = 1;
                                                    }
                                                    // 0x00366114
                                                    charge(ctx, 6);
                                                    a3 = addiu(s7, -200);
                                                    a0 = 0x6A0000;
                                                    a0 = addiu(a0, -10400);  // "branch message mesno  =  %d nowframe = %d  branchpos= B%d\n"
                                                    a2 = fp;
                                                    jal(ctx, 0x366124u, gen::fn_printf_005225a8);
                                                }
                                            } else {
                                                // 0x00366090
                                                charge(ctx, 4);
                                                lw(s0, sp, 0xAC);
                                                lb(v1, s3, key::kArg20);
                                                if (v1 == 0) {
                                                    // 0x003660a0
                                                    charge(ctx, 1);
                                                    s2 = 1;
                                                }
                                                // 0x003660a4
                                                charge(ctx, 4);
                                                lb(a0, s3, 22);
                                                v1 = 1;
                                                if (a0 == v1) {
                                                    // 0x003660b4
                                                    charge(ctx, 3);
                                                    s1 = v1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x0036612c
                            charge(ctx, 1);
                            lw(s3, s3, key::kNext);
                        }
                    }
                    // 0x00366138
                    charge(ctx, 1);
                    lw(s4, s4, unit::kNext);
                }
                // 0x00366144
                charge(ctx, 3);
                v1 = si(-1);
                if (s0 == v1) {
                    // 0x00366150
                    charge(ctx, 2);
                    if (s6 != v1) {
                        goto L_00366158;
                    }
                    // 0x003661d4 (the shared epilogue, written out on this path)
                    charge(ctx, 13);
                    ld(ra, sp, 0x90);
                    lq(fp, sp, 0x80);
                    lq(s7, sp, 0x70);
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
            L_00366158:
                charge(ctx, 3);
                v1 = 1;
                if (s2 == v1) {
                    // 0x00366164
                    charge(ctx, 2);
                    if (s1 != v1) {
                        // 0x00366180
                        charge(ctx, 3);
                        lw(v1, s5, work::kFlags);
                        v1 = v1 | 0x20;
                        sw(v1, s5, work::kFlags);
                    } else {
                        // 0x0036616c
                        charge(ctx, 5);
                        lw(v1, s5, work::kFlags);
                        v1 = v1 | 0x8000;
                        sw(v1, s5, work::kFlags);
                    }
                }
                // 0x0036618c
                charge(ctx, 3);
                v1 = 1;
                if (s1 != v1) {
                    // 0x003661bc
                    charge(ctx, 6);
                    a0 = addiu(s5, 2092);
                    a1 = s0;
                    a2 = s6;
                    a3 = s7;
                    jal(ctx, 0x3661CCu, gen::fn_sub_39F210_0039f210);
                } else {
                    // 0x00366198
                    charge(ctx, 4);
                    lb(v1, s5, work::kMode);
                    v1 = v1 & 0x8;
                    if (v1 != 0) {
                        // 0x003661a8
                        charge(ctx, 5);
                        a0 = s0;
                        jal(ctx, 0x3661ACu, gen::fn_sub_3C9790_003c9790);
                    }
                }
            }
        }
    }
    // 0x003661d4 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00366210 sub_366210 -- 288 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyFadeWaitUnit] (frame, work): the type-34 unit's current key (sub_38C460) at its own frame: command 1 waits
// for a fade (kFlagFadeWait while sub_108710() == 0); command 0 waits for the message to close (kFlagMessage).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00366210
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    sw(zero, sp, 0x3C);
    sw(zero, sp, 0x38);
    lw(a0, a1, work::kUnitHead);
    v1 = 34;
    for (;;) {
        // 0x00366250
        charge(ctx, 4);
        if (a0 != 0) {
            backedge(ctx);
            // 0x00366240
            charge(ctx, 3);
            lw(a1, a0, 0);
            if (a1 != v1) {
                // 0x0036624c
                charge(ctx, 1);
                lw(a0, a0, 148);
                continue;
            }
        }
        break;
    }
    // 0x00366260
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00366268
        charge(ctx, 8);
        a1 = s1;
        a2 = addiu(sp, 0x3C);
        a3 = addiu(sp, 0x38);
        jal(ctx, 0x366274u, gen::fn_sub_38C460_0038c460);
        lw(a0, sp, 0x3C);
        if (a0 != 0) {
            // 0x00366288
            charge(ctx, 3);
            lhu(v1, a0, 0);
            if (v1 == s1) {
                // 0x00366294
                charge(ctx, 4);
                lb(a0, a0, 16);
                v1 = 1;
                if (a0 == v1) {
                    // 0x003662fc
                    charge(ctx, 4);
                    jal(ctx, 0x3662FCu, gen::fn_sub_108710_00108710);
                    if (v0 == 0) {
                        // 0x0036630c
                        charge(ctx, 3);
                        lw(v1, s0, work::kFlags);
                        v1 = v1 | 0x2000;
                        sw(v1, s0, work::kFlags);
                    }
                } else {
                    // 0x003662a4
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003662b4
                        charge(ctx, 5);
                        a0 = addiu(s0, 2092);
                        jal(ctx, 0x3662B8u, gen::fn_sub_39EEE0_0039eee0);
                        if (v0 != 0) {
                            // 0x003662c8
                            charge(ctx, 5);
                            a0 = addiu(s0, 2092);
                            jal(ctx, 0x3662CCu, gen::fn_sub_39F6E0_0039f6e0);
                            if (v0 == 0) {
                                // 0x003662dc
                                charge(ctx, 8);
                                lw(v0, s0, work::kFlags);
                                v0 = v0 | 0x20;
                                sw(v0, s0, work::kFlags);
                                a0 = addiu(gp, -25216);  // "stop\n"
                                jal(ctx, 0x3662ECu, gen::fn_printf_005225a8);
                            }
                        }
                    } else {
                        // 0x003662ac
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x00366318 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00366330 sub_366330 -- 184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyJumpUnits] (frame, work): the first type-38 key firing at this frame requests a jump to its frame at +16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00366330
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a1, work::kUnitHead);
    for (;;) {
        // 0x003663c0
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036635c
        charge(ctx, 4);
        lw(a0, s0, unit::kType);
        v1 = 38;
        if (a0 == v1) {
            // 0x0036636c
            charge(ctx, 3);
            lw(s3, s0, unit::kKeyHead);
            for (;;) {
                // 0x003663b4
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00366378
                charge(ctx, 5);
                a0 = s3;
                jal(ctx, 0x36637Cu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x0036638c
                    charge(ctx, 3);
                    lhu(v1, s3, key::kFrame);
                    if (v1 != s2) {
                        goto L_003663b0;
                    }
                    goto L_00366398_5;
                }
            L_003663b0:
                charge(ctx, 1);
                lw(s3, s3, key::kNext);
            }
        }
        // 0x003663bc
        charge(ctx, 1);
        lw(s0, s0, unit::kNext);
    }
    // 0x003663c8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00366398_5:
    charge(ctx, 6);
    lh(v1, s3, key::kCmd);
    sw(v1, s1, work::kJumpFrame);
    v1 = 1;
    sw(v1, s1, work::kJumpRequest);
    // 0x003663c8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003663F0 sub_3663F0 -- 324 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyRandomJumpUnits] (frame, work): the first type-40 key firing now picks one of four jump frames (+24.. +30)
// with sub_388DF0(4, the four weights at +16..+19) and requests the jump.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3663F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003663f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(s0, a1, work::kUnitHead);
    for (;;) {
        // 0x0036650c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036641c
        charge(ctx, 4);
        lw(a0, s0, unit::kType);
        v1 = 40;
        if (a0 == v1) {
            // 0x0036642c
            charge(ctx, 3);
            lw(s1, s0, unit::kKeyHead);
            for (;;) {
                // 0x00366500
                charge(ctx, 2);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00366438
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x36643Cu, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x0036644c
                    charge(ctx, 3);
                    lhu(v1, s1, key::kFrame);
                    if (v1 != s3) {
                        goto L_003664fc;
                    }
                    goto L_00366458_5;
                }
            L_003664fc:
                charge(ctx, 1);
                lw(s1, s1, key::kNext);
            }
        }
        // 0x00366508
        charge(ctx, 1);
        lw(s0, s0, unit::kNext);
    }
    // 0x00366514 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00366458_5:
    charge(ctx, 16);
    s0 = 0;
    lb(v0, s1, key::kCmd);
    sw(v0, sp, 0x50);
    lb(v0, s1, 17);
    sw(v0, sp, 0x54);
    lb(v0, s1, 18);
    sw(v0, sp, 0x58);
    lb(v0, s1, 19);
    sw(v0, sp, 0x5C);
    a0 = 4;
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x366484u, gen::fn_sub_388DF0_00388df0);
    v1 = 3;
    if (v0 == v1) {
        // 0x003664e4
        charge(ctx, 1);
        lh(s0, s1, 30);
    } else {
        // 0x00366498
        charge(ctx, 3);
        v1 = 2;
        if (v0 == v1) {
            // 0x003664d8
            charge(ctx, 3);
            lh(s0, s1, 28);
        } else {
            // 0x003664a4
            charge(ctx, 3);
            v1 = 1;
            if (v0 == v1) {
                // 0x003664cc
                charge(ctx, 3);
                lh(s0, s1, 26);
            } else {
                // 0x003664b0
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x003664c0
                    charge(ctx, 3);
                    lh(s0, s1, 24);
                } else {
                    // 0x003664b8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x003664e8
    charge(ctx, 5);
    sw(s0, s2, work::kJumpFrame);
    v1 = 1;
    sw(v1, s2, work::kJumpRequest);
    // 0x00366514 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00366540 sub_366540 -- 288 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtFindMotionKey] (work, unit, frame, slot) -> the latest command-2 key at or before the frame for animation slot
// `slot` (+20, or sub_3976F0's slot for indirect keys +34 == 1) whose condition holds.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00366540
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a2;
    s3 = a3;
    s1 = 0;
    s0 = si(-1);
    lw(s2, a1, unit::kKeyHead);
    for (;;) {
        // 0x0036662c
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00366580
        charge(ctx, 4);
        lhu(v0, s2, key::kFrame);
        at = slt(s4, v0);
        if (at == 0) {
            // 0x00366590
            charge(ctx, 3);
            lb(v1, s2, 34);
            if (v1 == 0) {
                // 0x0036659c
                charge(ctx, 3);
                lb(a0, s2, key::kArg20);
                goto L_003665e0;
            }
            // 0x003665a8
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003665b4
                charge(ctx, 10);
                sw(zero, sp, 0x7C);
                sw(zero, sp, 0x78);
                lb(a1, s2, 21);
                a0 = s5;
                a2 = addiu(sp, 0x7C);
                a3 = addiu(sp, 0x78);
                jal(ctx, 0x3665CCu, gen::fn_sub_3976F0_003976f0);
                if (v0 != 0) {
                    // 0x003665dc
                    charge(ctx, 1);
                    lw(a0, sp, 0x7C);
                L_003665e0:
                    charge(ctx, 4);
                    lhu(v0, s2, key::kFrame);
                    at = slt(s0, v0);
                    if (at != 0) {
                        // 0x003665f0
                        charge(ctx, 4);
                        lb(v1, s2, key::kCmd);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00366600
                            charge(ctx, 2);
                            if (a0 == s3) {
                                // 0x00366608
                                charge(ctx, 6);
                                a0 = s2;
                                jal(ctx, 0x36660Cu, gen::fn_sub_360ED0_00360ed0);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x00366620
                                    charge(ctx, 2);
                                    lhu(s0, s2, key::kFrame);
                                    s1 = s2;
                                }
                            }
                        }
                    }
                }
            }
        }
        // 0x00366628
        charge(ctx, 1);
        lw(s2, s2, key::kNext);
    }
    // 0x00366634
    charge(ctx, 11);
    v0 = s1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00366660 sub_366660 -- 780 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtModelApplyMotionKeys] (frame, model, unit, work): for a model with a motion controller (+296, kinds 1 / 3) and
// each of its 4 animation slots: the current motion key (sub_366540); at its frame play the motion (sub_3B8FF0) and,
// with +35 == 1, its blend (sub_3B9260); remember it in the unit's kSlotKeys[slot].
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00366660
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    s5 = a1;
    s7 = a2;
    s4 = a3;
    s3 = 0;
    lhu(a0, a1, 0);
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    a0 = sra(v1, 10);
    v1 = 1;
    if (a0 != v1) {
        // 0x003666cc
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            // 0x003666d8
            charge(ctx, 1);
            lw(s3, s5, 296);
        }
    } else {
        // 0x003666c0
        charge(ctx, 3);
        lw(s3, s5, 296);
    }
    // 0x003666dc
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x003666e4
        charge(ctx, 6);
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x3666ECu, gen::fn_sub_3185B0_003185b0);
        if (v0 != 0) {
            // 0x003666fc
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x0036692c
                charge(ctx, 3);
                v1 = slti(s2, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00366708
                charge(ctx, 6);
                a1 = s2 & 0xFFFF;
                a0 = s3;
                jal(ctx, 0x366710u, gen::fn_sub_3185B0_003185b0);
                if (v0 != 0) {
                    // 0x00366720
                    charge(ctx, 9);
                    a0 = s4;
                    a1 = s7;
                    a2 = s6;
                    a3 = s2;
                    jal(ctx, 0x366730u, gen::fn_sub_366540_00366540);
                    s1 = v0;
                    if (s1 != 0) {
                        // 0x00366744
                        charge(ctx, 3);
                        lb(v1, s1, 22);
                        if (v1 != 0) {
                            // 0x00366760
                            charge(ctx, 2);
                            v1 = 0;
                            sw(zero, sp, 0xAC);
                        } else {
                            // 0x00366750
                            charge(ctx, 4);
                            v1 = 1;
                            sw(v1, sp, 0xAC);
                        }
                        // 0x00366768
                        charge(ctx, 3);
                        lb(s0, s1, 34);
                        if (v1 == 0) {
                            // 0x00366774
                            charge(ctx, 4);
                            a1 = s2 & 0xFFFF;
                            a0 = s3;
                            jal(ctx, 0x36677Cu, gen::fn_sub_318870_00318870);
                        }
                        // 0x00366784
                        charge(ctx, 3);
                        lhu(v1, s1, key::kFrame);
                        if (v1 == s6) {
                            // 0x00366790
                            charge(ctx, 2);
                            if (s0 == 0) {
                                // 0x00366798
                                charge(ctx, 5);
                                lb(fp, s1, 21);
                                lb(v0, s1, 23);
                                sw(v0, sp, 0xB0);
                                goto L_003667e8;
                            }
                            // 0x003667ac
                            charge(ctx, 3);
                            v0 = 1;
                            if (s0 != v0) {
                            L_003667e8:
                                charge(ctx, 3);
                                lh(v0, s1, 32);
                                if (i64(v0) <= 0) {
                                    // 0x00366810
                                    charge(ctx, 1);
                                    t1 = 0;
                                } else {
                                    // 0x003667f4
                                    charge(ctx, 7);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(t1, f0);
                                }
                                // 0x00366814
                                charge(ctx, 3);
                                lh(v0, s1, 40);
                                if (i64(v0) > 0) {
                                    // 0x00366830
                                    charge(ctx, 7);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x42C80000;
                                    mtc1(v0, f0);
                                    div_s(f12, f1, f0);
                                } else {
                                    // 0x00366820
                                    charge(ctx, 4);
                                    v0 = 0x3F800000;
                                    mtc1(v0, f12);
                                }
                                // 0x0036684c
                                charge(ctx, 11);
                                a0 = s5;
                                a1 = s2;
                                a2 = fp;
                                lw(a3, sp, 0xB0);
                                lw(t0, sp, 0xAC);
                                jal(ctx, 0x366860u, gen::fn_sub_3B8FF0_003b8ff0);
                                lb(a0, s1, 35);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x00366878
                                    charge(ctx, 2);
                                    if (s0 == 0) {
                                        // 0x00366880
                                        charge(ctx, 4);
                                        a1 = s2;
                                        lb(a2, s1, 36);
                                        goto L_003668c4;
                                    }
                                    // 0x00366890
                                    charge(ctx, 2);
                                    if (s0 == v1) {
                                        // 0x00366898
                                        charge(ctx, 9);
                                        lb(a1, s1, 36);
                                        a0 = s4;
                                        a2 = addiu(sp, 0xC4);
                                        a3 = addiu(sp, 0xC0);
                                        jal(ctx, 0x3668A8u, gen::fn_sub_3976F0_003976f0);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            // 0x003668bc
                                            charge(ctx, 2);
                                            lw(a1, sp, 0xC4);
                                            lw(a2, sp, 0xC0);
                                        L_003668c4:
                                            charge(ctx, 7);
                                            lb(v0, s1, 37);
                                            t0 = v0;
                                            t0 = sltiu(t0, 1);
                                            lh(a3, s1, 38);
                                            lh(v0, s1, 42);
                                            if (i64(v0) > 0) {
                                                // 0x003668f0
                                                charge(ctx, 7);
                                                mtc1(v0, f0);
                                                cvt_s_w(f1, f0);
                                                v0 = 0x42C80000;
                                                mtc1(v0, f0);
                                                div_s(f12, f1, f0);
                                            } else {
                                                // 0x003668e0
                                                charge(ctx, 4);
                                                v0 = 0x3F800000;
                                                mtc1(v0, f12);
                                            }
                                            // 0x0036690c
                                            charge(ctx, 4);
                                            a0 = s5;
                                            t1 = 0;
                                            jal(ctx, 0x366914u, gen::fn_sub_3B9260_003b9260);
                                            goto L_0036691c;
                                        }
                                    }
                                    goto L_00366928;
                                }
                            L_0036691c:
                                charge(ctx, 3);
                                v1 = sll(s2, 2);
                                v1 = addu(s7, v1);
                                sw(s1, v1, 116);
                            } else {
                                // 0x003667b8
                                charge(ctx, 9);
                                lb(a1, s1, 21);
                                a0 = s4;
                                a2 = addiu(sp, 0xCC);
                                a3 = addiu(sp, 0xC8);
                                jal(ctx, 0x3667C8u, gen::fn_sub_3976F0_003976f0);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x003667dc
                                    charge(ctx, 3);
                                    lw(fp, sp, 0xC8);
                                    lb(v0, s1, 23);
                                    sw(v0, sp, 0xB0);
                                    goto L_003667e8;
                                }
                            }
                        }
                    }
                }
            L_00366928:
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
        }
    }
    // 0x00366938 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x00366970 sub_366970 -- 324 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyMotionUnits] (frame, work): sub_366660 for every model of the stage (sub_3B5D00 list) and every field object
// (sub_3B5D50(3)) that a unit drives (kModel).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00366970
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x36698Cu, gen::fn_sub_3B5D00_003b5d00);
    if (v0 != 0) {
        // 0x0036699c
        charge(ctx, 3);
        lw(s2, v0, 4);
        for (;;) {
            // 0x00366a0c
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003669a8
            charge(ctx, 4);
            v1 = 0;
            lw(a2, s0, work::kUnitHead);
            for (;;) {
                // 0x003669d4
                charge(ctx, 2);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003669b8
                charge(ctx, 3);
                lw(v0, a2, unit::kModel);
                if (v0 == s2) {
                    goto L_003669c4_4;
                }
                // 0x003669d0
                charge(ctx, 1);
                lw(a2, a2, unit::kNext);
            }
        L_003669dc:
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x003669f0
                charge(ctx, 7);
                a0 = s1;
                a1 = s2;
                a3 = s0;
                t0 = 0;
                jal(ctx, 0x366A00u, gen::fn_sub_366660_00366660);
                lw(s2, s2, 248);
            } else {
                // 0x003669e4
                charge(ctx, 3);
                lw(s2, s2, 248);
            }
        }
        // 0x00366a14
        charge(ctx, 6);
        a0 = 3;
        jal(ctx, 0x366A18u, gen::fn_sub_3B5D50_003b5d50);
        s2 = v0;
        for (;;) {
            // 0x00366a90
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00366a2c
            charge(ctx, 4);
            a0 = 0;
            lw(a2, s0, work::kUnitHead);
            for (;;) {
                // 0x00366a58
                charge(ctx, 2);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00366a3c
                charge(ctx, 3);
                lw(v1, a2, unit::kModel);
                if (v1 == s2) {
                    goto L_00366a48_14;
                }
                // 0x00366a54
                charge(ctx, 1);
                lw(a2, a2, unit::kNext);
            }
        L_00366a60:
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x00366a74
                charge(ctx, 7);
                a0 = s1;
                a1 = s2;
                a3 = s0;
                t0 = 0;
                jal(ctx, 0x366A84u, gen::fn_sub_366660_00366660);
                lw(s2, s2, 248);
            } else {
                // 0x00366a68
                charge(ctx, 3);
                lw(s2, s2, 248);
            }
        }
    }
    // 0x00366a98 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003669c4_4:
    charge(ctx, 3);
    v1 = a2;
    goto L_003669dc;
L_00366a48_14:
    charge(ctx, 3);
    a0 = a2;
    goto L_00366a60;
}

// 0x00366AC0 sub_366AC0 -- 988 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtApplyFrame] (frame, work): everything a frame of the timeline does. Clears kFlagFilter / kFlagShake and the light
// words, resets the camera slots (sub_38CA00), applies motion, model, camera, show, visibility, volume, p3-effect and
// message units, then the one-shot event keys (sub_363030; units of types 5 7 19 28 29 41 42 44 45 46 50, a key is due
// on its frame, or during its hold when the unit has one), the state keys (sub_3638E0; types 6 10 36 39 43 with the
// current key -- skipping keys whose condition fails), fade-wait, jump and random-jump units; finally turns the filter
// off (sub_3BCC80) when the timeline is paused and no filter key ran.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_366AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // clear the per-frame flags and light words, then the unit appliers
    // 0x00366ac0
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a1, work::kFlags);
    v0 = si(-3);
    v1 = v1 & v0;
    sw(v1, a1, work::kFlags);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, a1, work::kFlags);
    sw(zero, a1, work::kLightOn);
    sw(zero, a1, 240);
    sw(zero, a1, 248);
    sw(zero, a1, 252);
    sw(zero, a1, 244);
    sw(zero, a1, 256);
    sw(zero, a1, work::kLight27On);
    jal(ctx, 0x366B1Cu, gen::fn_sub_38CA00_0038ca00);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B2Cu, gen::fn_sub_366970_00366970);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B3Cu, gen::fn_sub_365430_00365430);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B4Cu, gen::fn_sub_3657E0_003657e0);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B5Cu, gen::fn_sub_3658B0_003658b0);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B6Cu, gen::fn_sub_365A40_00365a40);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B7Cu, gen::fn_sub_365B70_00365b70);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B8Cu, gen::fn_sub_365CD0_00365cd0);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366B9Cu, gen::fn_sub_365F80_00365f80);
    lw(s4, s0, work::kUnitHead);
    for (;;) {
        // 0x00366ce8
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00366bb0
        charge(ctx, 4);
        lw(v1, s4, unit::kType);
        v0 = 1;
        if (v1 != v0) {
            // 0x00366bc0
            charge(ctx, 3);
            v0 = 46;
            if (v1 != v0) {
                // 0x00366bcc
                charge(ctx, 3);
                v0 = 45;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366bd8
                charge(ctx, 3);
                v0 = 44;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366be4
                charge(ctx, 3);
                v0 = 42;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366bf0
                charge(ctx, 3);
                v0 = 29;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366bfc
                charge(ctx, 3);
                v0 = 28;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c08
                charge(ctx, 3);
                v0 = 7;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c14
                charge(ctx, 3);
                v0 = 19;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c20
                charge(ctx, 3);
                v0 = 50;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c2c
                charge(ctx, 3);
                v0 = 5;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c38
                charge(ctx, 3);
                v0 = 41;
                if (v1 == v0) {
                    goto L_00366c4c;
                }
                // 0x00366c44
                charge(ctx, 2);
                // 0x00366c58
                charge(ctx, 1);
                v0 = 0;
                goto L_00366c5c;
            }
        L_00366c4c:
            charge(ctx, 3);
            v0 = 1;
        L_00366c5c:
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00366c64
                charge(ctx, 3);
                lw(s3, s4, unit::kKeyHead);
                for (;;) {
                    // 0x00366cdc
                    charge(ctx, 2);
                    if (s3 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00366c70
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x366C74u, gen::fn_sub_360ED0_00360ed0);
                    if (v0 != 0) {
                        // 0x00366c84
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x00366c8c
                            charge(ctx, 3);
                            lhu(v0, s3, key::kFrame);
                            if (s1 != v0) {
                                goto L_00366c98;
                            }
                        L_00366cc0:
                            charge(ctx, 6);
                            a0 = s4;
                            a1 = s3;
                            a2 = s1;
                            a3 = s0;
                            jal(ctx, 0x366CD0u, gen::fn_sub_363030_00363030);
                            goto L_00366cd8;
                        }
                    L_00366c98:
                        charge(ctx, 2);
                        if (i64(s2) > 0) {
                            // 0x00366ca0
                            charge(ctx, 4);
                            lhu(v1, s3, key::kFrame);
                            v0 = slt(s1, v1);
                            if (v0 == 0) {
                                // 0x00366cb0
                                charge(ctx, 4);
                                v0 = addu(v1, s2);
                                at = slt(s1, v0);
                                if (at != 0) {
                                    goto L_00366cc0;
                                }
                            }
                        }
                    }
                L_00366cd8:
                    charge(ctx, 1);
                    lw(s3, s3, key::kNext);
                }
            }
        }
        // 0x00366ce4
        charge(ctx, 1);
        lw(s4, s4, unit::kNext);
    }
    // 0x00366cf0
    charge(ctx, 3);
    lw(s4, s0, work::kUnitHead);
    for (;;) {
        // 0x00366e1c
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00366cfc
        charge(ctx, 4);
        lw(v1, s4, unit::kType);
        v0 = 36;
        if (v1 != v0) {
            // 0x00366d0c
            charge(ctx, 3);
            v0 = 43;
            if (v1 == v0) {
                goto L_00366d44;
            }
            // 0x00366d18
            charge(ctx, 3);
            v0 = 39;
            if (v1 == v0) {
                goto L_00366d44;
            }
            // 0x00366d24
            charge(ctx, 3);
            v0 = 10;
            if (v1 == v0) {
                goto L_00366d44;
            }
            // 0x00366d30
            charge(ctx, 3);
            v0 = 6;
            if (v1 == v0) {
                goto L_00366d44;
            }
            // 0x00366d3c
            charge(ctx, 2);
            // 0x00366d50
            charge(ctx, 1);
            v0 = 0;
            goto L_00366d54;
        }
    L_00366d44:
        charge(ctx, 3);
        v0 = 1;
    L_00366d54:
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x00366d5c
            charge(ctx, 4);
            lh(s2, s4, unit::kHold);
            lw(s3, s4, unit::kKeyHead);
            for (;;) {
                // 0x00366d98
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00366d6c
                charge(ctx, 5);
                a0 = s3;
                jal(ctx, 0x366D70u, gen::fn_sub_360ED0_00360ed0);
                if (v0 != 0) {
                    // 0x00366d80
                    charge(ctx, 5);
                    lhu(v0, s3, key::kFrame);
                    v0 = addu(v0, s2);
                    at = slt(s1, v0);
                    if (at != 0) {
                        break;
                    }
                    goto L_00366d94;
                }
            L_00366d94:
                charge(ctx, 1);
                lw(s3, s3, key::kNext);
            }
            // 0x00366da0
            charge(ctx, 2);
            if (s3 == 0) {
                // 0x00366db4
                charge(ctx, 1);
                lw(s2, s4, unit::kKeyTail);
            } else {
                // 0x00366da8
                charge(ctx, 3);
                lw(s2, s3, key::kPrev);
            }
            // 0x00366db8
            charge(ctx, 6);
            lw(a0, s4, unit::kType);
            jal(ctx, 0x366DBCu, gen::fn_sub_36F500_0036f500);
            v1 = 1;
            if (v0 == v1) {
                // 0x00366dd0
                charge(ctx, 2);
                for (;;) {
                    // 0x00366df4
                    charge(ctx, 2);
                    if (s2 != 0) {
                        backedge(ctx);
                        // 0x00366dd8
                        charge(ctx, 6);
                        a0 = s2;
                        jal(ctx, 0x366DDCu, gen::fn_sub_360ED0_00360ed0);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x00366df0
                            charge(ctx, 1);
                            lw(s2, s2, 80);
                            continue;
                        }
                    }
                    break;
                }
            }
            // 0x00366dfc
            charge(ctx, 7);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            a3 = s1;
            t0 = s0;
            jal(ctx, 0x366E10u, gen::fn_sub_3638E0_003638e0);
        }
        // 0x00366e18
        charge(ctx, 1);
        lw(s4, s4, unit::kNext);
    }
    // 0x00366e24
    charge(ctx, 16);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366E2Cu, gen::fn_sub_366210_00366210);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366E3Cu, gen::fn_sub_366330_00366330);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x366E4Cu, gen::fn_sub_3663F0_003663f0);
    lw(a0, s0, work::kFlags);
    v1 = a0 & 0x1;
    if (v1 != 0) {
        // 0x00366e64
        charge(ctx, 3);
        v1 = a0 & 0x2;
        if (v1 == 0) {
            // 0x00366e70
            charge(ctx, 2);
            jal(ctx, 0x366E70u, gen::fn_sub_3BCC80_003bcc80);
        }
    }
    // 0x00366e78 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0036D030 sub_36D030 -- 740 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtUpdateStopState] (work): clears the wait flags whose waits are over (message closed, comu message, effect channels,
// sub_3CF630, fade, sub task), recomputes "stopped" (any of paused / message / fx / 0x1000 / overlay / fade / sub task /
// comu message) and, when it changes, holds or releases the actors (sub_362120) -- "stop manager exec".
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36D030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036d030
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x0036d048
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x20;
        if (v1 != 0) {
            // 0x0036d058
            charge(ctx, 6);
            a0 = addiu(s0, 2092);
            jal(ctx, 0x36D05Cu, gen::fn_sub_39F6E0_0039f6e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x0036d070
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-33);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d080
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x8000;
        if (v1 != 0) {
            // 0x0036d090
            charge(ctx, 4);
            lb(v1, s0, work::kMode);
            v1 = v1 & 0x8;
            if (v1 != 0) {
                // 0x0036d0a0
                charge(ctx, 4);
                jal(ctx, 0x36D0A0u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x0036d0b0
                    charge(ctx, 7);
                    jal(ctx, 0x36D0B0u, gen::fn_sub_3C7700_003c7700);
                    lw(v1, s0, work::kFlags);
                    v0 = lui(0xFFFF);
                    v0 = v0 | 0x7FFF;
                    v0 = v1 & v0;
                    sw(v0, s0, work::kFlags);
                }
                // 0x0036d0cc
                charge(ctx, 2);
                jal(ctx, 0x36D0CCu, gen::fn_sub_3C7B90_003c7b90);
            }
        }
        // 0x0036d0d4
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x200;
        if (v1 != 0) {
            // 0x0036d0e4
            charge(ctx, 6);
            a0 = 0;
            jal(ctx, 0x36D0E8u, gen::fn_sub_396ED0_00396ed0);
            v1 = 1;
            if (v0 != v1) {
                // 0x0036d0fc
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-513);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d10c
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x400;
        if (v1 != 0) {
            // 0x0036d11c
            charge(ctx, 6);
            a0 = 1;
            jal(ctx, 0x36D120u, gen::fn_sub_396ED0_00396ed0);
            v1 = 1;
            if (v0 != v1) {
                // 0x0036d134
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-1025);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d144
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x800;
        if (v1 != 0) {
            // 0x0036d154
            charge(ctx, 6);
            a0 = 2;
            jal(ctx, 0x36D158u, gen::fn_sub_396ED0_00396ed0);
            v1 = 1;
            if (v0 != v1) {
                // 0x0036d16c
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-2049);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d17c
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x1000;
        if (v1 != 0) {
            // 0x0036d18c
            charge(ctx, 4);
            jal(ctx, 0x36D18Cu, gen::fn_sub_3CF630_003cf630);
            if (v0 == 0) {
                // 0x0036d19c
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-4097);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d1ac
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x2000;
        if (v1 != 0) {
            // 0x0036d1bc
            charge(ctx, 5);
            jal(ctx, 0x36D1BCu, gen::fn_sub_108710_00108710);
            v1 = 1;
            if (v0 == v1) {
                // 0x0036d1d0
                charge(ctx, 4);
                lw(a0, s0, work::kFlags);
                v1 = si(-8193);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
            }
        }
        // 0x0036d1e0
        charge(ctx, 4);
        lw(v1, s0, work::kFlags);
        v1 = v1 & 0x4000;
        if (v1 != 0) {
            // 0x0036d1f0
            charge(ctx, 5);
            lw(a0, s0, work::kSubTask);
            jal(ctx, 0x36D1F4u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x0036d204
                charge(ctx, 5);
                lw(a0, s0, work::kFlags);
                v1 = si(-16385);
                v1 = a0 & v1;
                sw(v1, s0, work::kFlags);
                sw(zero, s0, work::kSubTask);
            }
        }
        // 0x0036d218
        charge(ctx, 4);
        lw(a0, s0, work::kFlags);
        v1 = a0 & 0x1;
        if (v1 == 0) {
            // 0x0036d228
            charge(ctx, 3);
            v1 = a0 & 0x20;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d234
            charge(ctx, 3);
            v1 = a0 & 0x200;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d240
            charge(ctx, 3);
            v1 = a0 & 0x400;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d24c
            charge(ctx, 3);
            v1 = a0 & 0x800;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d258
            charge(ctx, 3);
            v1 = a0 & 0x1000;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d264
            charge(ctx, 4);
            v1 = 0x20000;
            v1 = a0 & v1;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d274
            charge(ctx, 3);
            v1 = a0 & 0x2000;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d280
            charge(ctx, 3);
            v1 = a0 & 0x4000;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d28c
            charge(ctx, 3);
            v1 = a0 & 0x8000;
            if (v1 != 0) {
                goto L_0036d298;
            }
            // 0x0036d2a4
            charge(ctx, 1);
            a1 = 0;
            goto L_0036d2a8;
        }
    L_0036d298:
        charge(ctx, 3);
        a1 = 1;
    L_0036d2a8:
        charge(ctx, 3);
        lw(v1, s0, work::kStopped);
        if (v1 != a1) {
            // 0x0036d2b4
            charge(ctx, 4);
            sw(a1, s0, work::kStopped);
            a0 = 1;
            if (a1 != a0) {
                // 0x0036d2e0
                charge(ctx, 4);
                lw(a1, s0, work::kFrame);
                a2 = s0;
                jal(ctx, 0x36D2E8u, gen::fn_sub_362120_00362120);
            } else {
                // 0x0036d2c4
                charge(ctx, 7);
                a0 = 0;
                lw(a1, s0, work::kFrame);
                a2 = s0;
                jal(ctx, 0x36D2D0u, gen::fn_sub_362120_00362120);
            }
            // 0x0036d2f0
            charge(ctx, 4);
            a0 = 0x6A0000;
            a0 = addiu(a0, -8672);  // "stop manager exec\n"
            jal(ctx, 0x36D2F8u, gen::fn_printf_005225a8);
        }
    }
    // 0x0036d300 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036D320 sub_36D320 -- 336 bytes; leaf frame (no stack)
// [evtEdMenuAllowsPlay] (work) -> 0 for the editor menus (and sub-modes of menu 26) during which the timeline must not
// run, else 1 (menu 46 -> 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36D320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0036d320
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, work::kMenuId);
    v0 = 26;
    if (v1 != v0) {
        // 0x0036d3b8
        charge(ctx, 3);
        v0 = 23;
        if (v1 != v0) {
            // 0x0036d3d0
            charge(ctx, 3);
            v0 = 25;
            if (v1 != v0) {
                // 0x0036d3e8
                charge(ctx, 3);
                v0 = 24;
                if (v1 != v0) {
                    // 0x0036d400
                    charge(ctx, 3);
                    v0 = 19;
                    if (v1 != v0) {
                        // 0x0036d418
                        charge(ctx, 3);
                        v0 = 28;
                        if (v1 != v0) {
                            // 0x0036d430
                            charge(ctx, 3);
                            v0 = 10;
                            if (v1 != v0) {
                                // 0x0036d448
                                charge(ctx, 3);
                                v0 = 40;
                                if (v1 != v0) {
                                    // 0x0036d460
                                    charge(ctx, 2);
                                    v0 = v1 ^ 0x2E;
                                    v0 = sltu(0, v0);
                                } else {
                                    // 0x0036d454
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            } else {
                                // 0x0036d43c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x0036d424
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x0036d40c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x0036d3f4
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x0036d3dc
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x0036d3c4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0036d330
        charge(ctx, 4);
        lw(a0, a0, work::kEdField364);
        v0 = 13;
        if (a0 != v0) {
            // 0x0036d340
            charge(ctx, 3);
            v0 = 12;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d34c
            charge(ctx, 3);
            v0 = 10;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d358
            charge(ctx, 3);
            v0 = 9;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d364
            charge(ctx, 3);
            v0 = 8;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d370
            charge(ctx, 3);
            v0 = 6;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d37c
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                goto L_0036d3a4;
            }
            // 0x0036d388
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_0036d3a4;
            }
            // 0x0036d390
            charge(ctx, 3);
            v1 = 4;
            if (a0 == v1) {
                goto L_0036d3a4;
            }
            // 0x0036d39c
            charge(ctx, 2);
            // 0x0036d3b0
            charge(ctx, 2);
            // 0x0036d468 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_0036d3a4:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0036d468 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0036D470 sub_36D470 -- 132 bytes; leaf frame (no stack)
// [evtEdMenuFrameStep] (work) -> 0, or -6 for the editor's menu 5 on a type-33 unit (types 3 / 17 / 26 -> 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36D470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0036d470
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
    if (a0 != 0) {
        // 0x0036d484
        charge(ctx, 3);
        lw(v1, a0, work::kEdUnit);
        if (v1 != 0) {
            // 0x0036d498
            charge(ctx, 5);
            lw(a1, v1, 0);
            lw(a0, a0, work::kMenuId);
            v1 = 5;
            if (a0 == v1) {
                // 0x0036d4ac
                charge(ctx, 3);
                v1 = 3;
                if (a1 != v1) {
                    // 0x0036d4b8
                    charge(ctx, 3);
                    v1 = 26;
                    if (a1 == v1) {
                        goto L_0036d4d0;
                    }
                    // 0x0036d4c4
                    charge(ctx, 3);
                    v1 = 17;
                    if (a1 == v1) {
                        goto L_0036d4d0;
                    }
                    // 0x0036d4dc
                    charge(ctx, 3);
                    v1 = 33;
                    if (a1 == v1) {
                        // 0x0036d4e8
                        charge(ctx, 1);
                        v0 = si(-6);
                    }
                    // 0x0036d4ec (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
            L_0036d4d0:
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x0036d490
            charge(ctx, 2);
        }
    } else {
        // 0x0036d47c
        charge(ctx, 2);
    }
    // 0x0036d4ec (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0036D500 sub_36D500 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtStepWaitPmReader] (process step): waits until the PM reader task kPmTask has ended plus 5 more frames
// (0x7CE5E4), then restarts the scene (sub_393E30 with sub_36E690 as the next step), clears kFlagPmWait and re-selects
// the camera. Returns the next step (sub_36E690) or 0 (stay).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36D500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036d500
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x36D510u, gen::fn_dds3GetProcessWorkData_0035ae10);
    s0 = v0;
    lw(a0, v0, work::kPmTask);
    jal(ctx, 0x36D520u, gen::fn_kwlnTaskExists_00195460);
    if (v0 != 0) {
        // 0x0036d5d0
        charge(ctx, 1);
        sw(zero, gp, evt::kGpPmWaitCount);  // 0x7CE5E4
    L_0036d5d4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0036d530
        charge(ctx, 4);
        lw(v1, gp, evt::kGpPmWaitCount);  // 0x7CE5E4
        v0 = slti(v1, 5);
        if (v0 != 0) {
            // 0x0036d5c0
            charge(ctx, 4);
            v0 = addiu(v1, 1);
            sw(v0, gp, evt::kGpPmWaitCount);  // 0x7CE5E4
            goto L_0036d5d4;
        }
        // 0x0036d540
        charge(ctx, 32);
        a0 = s0;
        jal(ctx, 0x36D544u, gen::fn_sub_386E10_00386e10);
        s1 = v0;
        a0 = s0;
        jal(ctx, 0x36D554u, gen::fn_sub_386E30_00386e30);
        a0 = s0;
        a1 = s1;
        a2 = v0;
        a3 = 0;
        t0 = 0;
        t1 = 0x370000;
        t1 = addiu(t1, -6512);  // &sub_36E690
        jal(ctx, 0x36D578u, gen::fn_sub_393E30_00393e30);
        lw(v1, s0, work::kFlags);
        v0 = si(-257);
        v0 = v1 & v0;
        sw(v0, s0, work::kFlags);
        a0 = s0;
        jal(ctx, 0x36D594u, gen::fn_sub_38A0B0_0038a0b0);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x36D5A4u, gen::fn_sub_38A0C0_0038a0c0);
        sw(zero, gp, evt::kGpPmWaitCount);  // 0x7CE5E4
        v0 = 0x370000;
        v0 = addiu(v0, -6512);  // &sub_36E690
    }
    // 0x0036d5d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0036DA10 sub_36DA10 -- 264 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtLoadEventField] (work) -> 1 when the event's field is ready: the scene header (+148) names a field (major +16,
// minor +20); in play mode that is all; else when sub_3B5620 allows it, MT_Scene_Load(major, minor), sub_3B58C0
// (+26) and sub_3B5980(+28) ("load field majorno=%d minorno=%d"). 0 when the event has no field or it cannot load
// yet.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36DA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036da10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, work::kScene);
    lw(v1, v0, 148);
    lw(s3, v1, 16);
    lw(s2, v1, 20);
    lbu(v0, v1, 26);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    lh(s0, v1, 28);
    if (s3 == 0) {
        // 0x0036da50
        charge(ctx, 2);
        if (s2 != 0) {
            goto L_0036da64;
        }
        // 0x0036da58
        charge(ctx, 3);
        v0 = 0;
        // 0x0036daf8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0036da64:
    charge(ctx, 4);
    lw(v0, a0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036da80
        charge(ctx, 6);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x36DA88u, gen::fn_sub_3B5620_003b5620);
        if (v0 != 0) {
            // 0x0036daa4
            charge(ctx, 11);
            a0 = s3;
            a1 = s2;
            jal(ctx, 0x36DAACu, gen::fn_MT_Scene_Load_003b5760);
            a0 = s1;
            jal(ctx, 0x36DAB8u, gen::fn_sub_3B58C0_003b58c0);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            if (v0 != 0) {
                // 0x0036dad0
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x36DAD4u, gen::fn_sub_3B5980_003b5980);
            }
            // 0x0036dadc
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, -8416);  // "load field majorno=%d minorno=%d\n"
            a1 = s3;
            a2 = s2;
            jal(ctx, 0x36DAECu, gen::fn_printf_005225a8);
            v0 = 1;
        } else {
            // 0x0036da98
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0036da74
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0036daf8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0036DB20 sub_36DB20 -- 1564 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtStepSceneRead] (process step) "evtEventViewerProcessSceneRead": the loading state machine (kLoadState, jump
// table 0x7BA600). 0 free the previous scene (sub_36F000), reset the work (sub_361070), remember sub_1A4600's value;
// 1 start the PM reader (sub_397F80; "evt majorno=%d minorno=%d"); 2 wait for it (sub_398060); 3 build the scene
// (sub_394270, sub_3942F0 on the message handle; "data create!"); 4 load the field (sub_36DA10; "scene read");
// 5 wait for the stage (sub_3B5A10) and count the field's NPC models; 6 / 7 load them one by one (sub_316E00 /
// sub_316F70, sub_3B6000, sub_1A0DC0); 8 set up the field objects (sub_31BE80); 9 / 10 build and load the effect set
// (sub_3964C0, sub_396480, sub_3965D0 / sub_3965F0); 11 run the event interpreter sub_3912F0 (units and keys from the
// PM data); 13 wait for kWaitTask; 14 / 15 the voice / movie loader (sub_10A770 / sub_10A720) when kMode bit 0;
// 16 clear kFlagReload, play the event BGM (sub_3BD8B0 / sub_395270), back up resources (sub_3890E0, not in play
// mode), and when sub_397520 says so start the scene (sub_397510, sub_393F30). Returns kLoadResult in state 16, else
// 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36DB20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0036db20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    // s2 = &work[kLoadState] (its +0 is the state, +24 kLoadResult)
    s2 = addiu(s0, 2400);
    lw(v0, s0, work::kLoadState);
    at = sltiu(v0, 17);
    if (at != 0) {
        // 0x0036db54
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -23040);  // &0x7BA600
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        // state 0: free the previous scene, reset the work, pause, remember sub_1A4600(sub_198590())
        case 0x36DB70u:  // table[0]
            // 0x0036db70
            charge(ctx, 17);
            a0 = s0;
            jal(ctx, 0x36DB74u, gen::fn_sub_36F000_0036f000);
            a0 = s0;
            jal(ctx, 0x36DB80u, gen::fn_sub_361070_00361070);
            lw(v0, s0, work::kFlags);
            v0 = v0 | 0x1;
            sw(v0, s0, work::kFlags);
            v0 = 1;
            sw(v0, s0, work::kLoadState);
            jal(ctx, 0x36DB9Cu, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x36DBA8u, gen::fn_sub_1A4600_001a4600);
            swc1(f0, s0, work::kFieldScale);
        L_0036dbb4:
            charge(ctx, 3);
            lw(v0, s0, work::kPmReader);
            if (v0 == 0) {
                // 0x0036dbc0
                charge(ctx, 18);
                a0 = s0;
                jal(ctx, 0x36DBC4u, gen::fn_sub_386E10_00386e10);
                s3 = v0;
                a0 = s0;
                jal(ctx, 0x36DBD4u, gen::fn_sub_386E30_00386e30);
                s1 = v0;
                a0 = s0;
                jal(ctx, 0x36DBE4u, gen::fn_sub_397500_00397500);
                a0 = s3;
                a1 = s1;
                a2 = v0;
                lw(a3, s0, work::kLoadArg);
                jal(ctx, 0x36DBFCu, gen::fn_sub_397F80_00397f80);
                sw(v0, s0, work::kPmReader);
            }
            // 0x0036dc08
            charge(ctx, 15);
            a0 = s0;
            jal(ctx, 0x36DC0Cu, gen::fn_sub_386E10_00386e10);
            s1 = v0;
            a0 = s0;
            jal(ctx, 0x36DC1Cu, gen::fn_sub_386E30_00386e30);
            a0 = 0x6A0000;
            a0 = addiu(a0, -8368);  // "evt majorno=%d minorno=%d\n"
            a1 = s1;
            a2 = v0;
            jal(ctx, 0x36DC34u, gen::fn_printf_005225a8);
            v0 = 2;
            sw(v0, s0, work::kLoadState);
        L_0036dc44:
            charge(ctx, 5);
            lw(a0, s0, work::kPmReader);
            jal(ctx, 0x36DC48u, gen::fn_sub_398060_00398060);
            if (v0 == 0) {
            L_0036e114:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0036dc58
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, work::kLoadState);
            L_0036dc60:
                charge(ctx, 16);
                lw(a0, s0, work::kPmReader);
                jal(ctx, 0x36DC64u, gen::fn_sub_3980E0_003980e0);
                s1 = v0;
                jal(ctx, 0x36DC70u, gen::fn_sub_394270_00394270);
                s3 = v0;
                a0 = addiu(s0, 2092);
                a1 = s3;
                lw(a2, s1, 52);
                lw(a3, s1, 56);
                lw(t0, s1, 60);
                jal(ctx, 0x36DC90u, gen::fn_sub_3942F0_003942f0);
                if (s3 != 0) {
                    // 0x0036dcc4
                    charge(ctx, 23);
                    lw(v0, s1, 40);
                    sw(v0, s3, 8);
                    lw(v0, s1, 44);
                    sw(v0, s3, 112);
                    lw(v0, s1, 48);
                    sw(v0, s3, 124);
                    lw(v0, s1, 28);
                    sw(v0, s3, 276);
                    lw(v0, s1, 32);
                    sw(v0, s3, 280);
                    lw(v0, s1, 36);
                    sw(v0, s3, 284);
                    lw(v0, s1, 12);
                    sw(v0, s3, 288);
                    lw(v0, s1, 16);
                    sw(v0, s3, 292);
                    sw(s3, s0, work::kScene);
                    v0 = 4;
                    sw(v0, s2, 0);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -8336);  // "[evtEventViewerProcessSceneRead] data create!\n"
                    jal(ctx, 0x36DD18u, gen::fn_printf_005225a8);
                L_0036dd20:
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x36DD24u, gen::fn_sub_36DA10_0036da10);
                    if (v0 != 0) {
                        // 0x0036dd44
                        charge(ctx, 8);
                        v0 = 5;
                        sw(v0, s0, work::kLoadState);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -8288);  // "[evtEventViewerProcessSceneRead] scene read\n"
                        jal(ctx, 0x36DD54u, gen::fn_printf_005225a8);
                    } else {
                        // 0x0036dd34
                        charge(ctx, 4);
                        v0 = 6;
                        sw(v0, s0, work::kLoadState);
                    }
                    goto L_0036e114;
                }
                // 0x0036dca0
                charge(ctx, 9);
                sw(zero, s0, work::kScene);
                a0 = 0x6A0000;
                a0 = addiu(a0, -10880);  // "mt_evtMain.c"
                a1 = 11617;
                jal(ctx, 0x36DCB0u, gen::fn_sub_19D3F0_0019d3f0);
                v0 = 0;
            }
            break;
        // state 1: start the PM reader when there is none
        case 0x36DBB4u:  // table[1]
            goto L_0036dbb4;
        // state 2: wait for the PM reader
        case 0x36DC44u:  // table[2]
            goto L_0036dc44;
        // state 3: build the scene from the PM data ("data create!")
        case 0x36DC60u:  // table[3]
            goto L_0036dc60;
        // state 4: load the event's field ("scene read")
        case 0x36DD20u:  // table[4]
            goto L_0036dd20;
        // state 5: wait for the stage; NPC models to load (header +24, not in play mode)
        case 0x36DD64u:  // table[5]
            // 0x0036dd64
            charge(ctx, 4);
            jal(ctx, 0x36DD64u, gen::fn_sub_3B5A10_003b5a10);
            if (v0 != 0) {
                // 0x0036dd74
                charge(ctx, 4);
                lw(v0, s0, work::kFlags);
                v0 = v0 & 0x8;
                if (v0 == 0) {
                    // 0x0036dd84
                    charge(ctx, 5);
                    lw(v0, s0, work::kScene);
                    lw(v0, v0, 148);
                    lb(v0, v0, 24);
                    if (v0 == 0) {
                        goto L_0036dda8;
                    }
                    // 0x0036dd98
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s0, work::kNpcLoads);
                    goto L_0036ddac;
                }
            L_0036dda8:
                charge(ctx, 1);
                sw(zero, s0, work::kNpcLoads);
            L_0036ddac:
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s0, work::kLoadState);
            }
            goto L_0036e114;
        // state 6: request the next NPC model, or go on
        case 0x36DDBCu:  // table[6]
            // 0x0036ddbc
            charge(ctx, 3);
            lw(v0, s0, work::kNpcLoads);
            if (i64(v0) > 0) {
                // 0x0036ddd8
                charge(ctx, 10);
                a0 = 0;
                a1 = 2;
                a2 = 0;
                jal(ctx, 0x36DDE4u, gen::fn_sub_316E00_00316e00);
                sw(v0, gp, evt::kGpNpcLoad);  // 0x7CE5E8
                v0 = 7;
                sw(v0, s0, work::kLoadState);
            } else {
                // 0x0036ddc8
                charge(ctx, 4);
                v0 = 8;
                sw(v0, s0, work::kLoadState);
            }
            goto L_0036e114;
        // state 7: wait for it, register it (sub_3B6000 / sub_1A0DC0)
        case 0x36DE00u:  // table[7]
            // 0x0036de00
            charge(ctx, 6);
            lw(a0, gp, evt::kGpNpcLoad);  // 0x7CE5E8
            jal(ctx, 0x36DE04u, gen::fn_sub_316F70_00316f70);
            v1 = 1;
            if (v0 == v1) {
                // 0x0036de18
                charge(ctx, 16);
                a0 = 0;
                lw(a1, gp, evt::kGpNpcLoad);  // 0x7CE5E8
                jal(ctx, 0x36DE20u, gen::fn_sub_3B6000_003b6000);
                sh(v0, gp, evt::kGpNpcModel);  // 0x7CE5EC
                lhu(a0, gp, evt::kGpNpcModel);  // 0x7CE5EC
                a1 = 1;
                jal(ctx, 0x36DE34u, gen::fn_sub_1A0DC0_001a0dc0);
                lw(v0, s0, work::kNpcLoads);
                v0 = addiu(v0, -1);
                sw(v0, s0, work::kNpcLoads);
                v0 = 6;
                sw(v0, s0, work::kLoadState);
            }
            goto L_0036e114;
        // state 8: set up every field object (sub_31BE80 on model +296)
        case 0x36DE58u:  // table[8]
            // 0x0036de58
            charge(ctx, 6);
            a0 = 3;
            jal(ctx, 0x36DE5Cu, gen::fn_sub_3B5D50_003b5d50);
            s1 = v0;
            for (;;) {
                // 0x0036de80
                charge(ctx, 4);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0036de70
                charge(ctx, 4);
                lw(a0, s1, 296);
                jal(ctx, 0x36DE74u, gen::fn_sub_31BE80_0031be80);
                lw(s1, s1, 248);
            }
            // 0x0036de90
            charge(ctx, 2);
            v0 = 9;
            sw(v0, s0, work::kLoadState);
        L_0036de98:
            charge(ctx, 6);
            jal(ctx, 0x36DE98u, gen::fn_sub_3964C0_003964c0);
            sw(v0, s0, work::kEffectSet);
            s1 = 0;
            for (;;) {
                // 0x0036def4
                charge(ctx, 5);
                lw(v1, s0, work::kScene);
                lw(v0, v1, 68);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0036deb0
                charge(ctx, 7);
                lw(v1, v1, 64);
                v0 = sll(s1, 4);
                a0 = addu(v1, v0);
                lw(v1, a0, 8);
                v0 = 4;
                if (v1 == v0) {
                    // 0x0036ded4
                    charge(ctx, 7);
                    lw(v0, s0, work::kScene);
                    lw(v1, v0, 16);
                    lw(v0, a0, 4);
                    a1 = addu(v1, v0);
                    lw(a0, s0, work::kEffectSet);
                    jal(ctx, 0x36DEE8u, gen::fn_sub_396480_00396480);
                } else {
                    // 0x0036decc
                    charge(ctx, 2);
                }
                // 0x0036def0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0036df08
            charge(ctx, 7);
            lw(a0, s0, work::kEffectSet);
            jal(ctx, 0x36DF0Cu, gen::fn_sub_3965D0_003965d0);
            v0 = 10;
            sw(v0, s0, work::kLoadState);
            goto L_0036e114;
        // state 9: build the effect set from the scene's type-4 resources
        case 0x36DE98u:  // table[9]
            goto L_0036de98;
        // state 10: wait for the effect set, then (11) run the event interpreter sub_3912F0
        case 0x36DF24u:  // table[10]
            // 0x0036df24
            charge(ctx, 5);
            lw(a0, s0, work::kEffectSet);
            jal(ctx, 0x36DF28u, gen::fn_sub_3965F0_003965f0);
            if (v0 != 0) {
                // 0x0036df38
                charge(ctx, 2);
                v0 = 11;
                sw(v0, s0, work::kLoadState);
            L_0036df40:
                charge(ctx, 6);
                lw(a0, s0, work::kScene);
                a1 = s0;
                jal(ctx, 0x36DF48u, gen::fn_sub_3912F0_003912f0);
                v0 = 12;
                sw(v0, s0, work::kLoadState);
            L_0036df58:
                charge(ctx, 4);
                v0 = 14;
                sw(v0, s0, work::kLoadState);
            }
            goto L_0036e114;
        // state 11: run the event interpreter (units and keys from the PM data)
        case 0x36DF40u:  // table[11]
            goto L_0036df40;
        // state 12: on to 14
        case 0x36DF58u:  // table[12]
            goto L_0036df58;
        // state 13: wait for kWaitTask
        case 0x36DF68u:  // table[13]
            // 0x0036df68
            charge(ctx, 6);
            lw(a0, s0, work::kWaitTask);
            jal(ctx, 0x36DF6Cu, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x0036df80
                charge(ctx, 2);
                v0 = 14;
                sw(v0, s0, work::kLoadState);
            L_0036df88:
                charge(ctx, 4);
                lb(v0, s0, work::kMode);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x0036dfe8
                    charge(ctx, 4);
                    v0 = 16;
                    sw(v0, s0, work::kLoadState);
                } else {
                    // 0x0036df98
                    charge(ctx, 20);
                    a0 = s0;
                    jal(ctx, 0x36DF9Cu, gen::fn_sub_386E10_00386e10);
                    s1 = v0;
                    a0 = s0;
                    jal(ctx, 0x36DFACu, gen::fn_sub_386E30_00386e30);
                    lw(a0, s0, work::kTask);
                    a1 = 2;
                    a2 = 0;
                    a3 = a1;
                    t0 = s1;
                    t1 = v0;
                    jal(ctx, 0x36DFCCu, gen::fn_sub_10A770_0010a770);
                    sw(v0, s0, work::kVoiceTask);
                    v0 = 15;
                    sw(v0, s0, work::kLoadState);
                }
            }
            goto L_0036e114;
        // state 14: start the voice / movie loader when kMode bit 0
        case 0x36DF88u:  // table[14]
            goto L_0036df88;
        // state 15: wait for it
        case 0x36DFF8u:  // table[15]
            // 0x0036dff8
            charge(ctx, 5);
            lw(a0, s0, work::kVoiceTask);
            jal(ctx, 0x36DFFCu, gen::fn_sub_10A720_0010a720);
            if (v0 == 0) {
                goto L_0036e114;
            }
            // 0x0036e00c
            charge(ctx, 2);
            v0 = 16;
            sw(v0, s0, work::kLoadState);
        L_0036e014:
            charge(ctx, 27);
            lw(a0, s0, work::kPmReader);
            jal(ctx, 0x36E018u, gen::fn_sub_3980E0_003980e0);
            s1 = v0;
            lw(v1, s0, work::kFlags);
            v0 = si(-129);
            v0 = v1 & v0;
            sw(v0, s0, work::kFlags);
            a0 = s0;
            jal(ctx, 0x36E038u, gen::fn_sub_386E10_00386e10);
            s4 = v0;
            a0 = s0;
            jal(ctx, 0x36E048u, gen::fn_sub_386E30_00386e30);
            s3 = v0;
            a0 = s0;
            jal(ctx, 0x36E058u, gen::fn_sub_397500_00397500);
            a0 = s4;
            a1 = s3;
            a2 = v0;
            jal(ctx, 0x36E06Cu, gen::fn_sub_3BD8B0_003bd8b0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x0036e080
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0036e088
                    charge(ctx, 3);
                    a0 = v0;
                    jal(ctx, 0x36E08Cu, gen::fn_sub_395270_00395270);
                }
            }
            // 0x0036e094
            charge(ctx, 4);
            lw(v0, s0, work::kFlags);
            v0 = v0 & 0x8;
            if (v0 == 0) {
                // 0x0036e0a4
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x36E0A8u, gen::fn_sub_3890E0_003890e0);
            }
            // 0x0036e0b0
            charge(ctx, 7);
            a0 = s0;
            a1 = addiu(sp, 0x6C);
            jal(ctx, 0x36E0B8u, gen::fn_sub_397520_00397520);
            v1 = 1;
            if (v0 == v1) {
                // 0x0036e0cc
                charge(ctx, 5);
                lw(a1, s1, 20);
                lw(v0, sp, 0x6C);
                at = slt(a1, v0);
                if (at != 0) {
                    // 0x0036e0e0
                    charge(ctx, 2);
                    if (i64(a1) >= 0) {
                        // 0x0036e0e8
                        charge(ctx, 8);
                        a0 = s0;
                        jal(ctx, 0x36E0ECu, gen::fn_sub_397510_00397510);
                        a0 = s0;
                        a1 = 0x370000;
                        a1 = addiu(a1, -6512);  // &sub_36E690
                        jal(ctx, 0x36E100u, gen::fn_sub_393F30_00393f30);
                    }
                }
            }
            // 0x0036e108
            charge(ctx, 3);
            lw(v0, s2, 24);
            break;
        // state 16: event BGM, resource backup, start the scene; returns kLoadResult
        case 0x36E014u:  // table[16]
            goto L_0036e014;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0036e118 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
    goto L_0036e114;
}

// 0x0036E140 sub_36E140 -- 276 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtStepOverlay] (process step): toggles the metrics overlay on the pad bit 0x200 (in play mode only when sub_39E6F0
// allows it), draws it, and returns to sub_36E690 once kOverlayTask has ended (clearing kFlagOverlay).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36E140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036e140
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036e1ac
        charge(ctx, 5);
        v0 = 0x7E0000;
        lhu(v0, v0, 2382);  // gPadFlags
        v0 = v0 & 0x200;
        if (v0 != 0) {
            // 0x0036e1c0
            charge(ctx, 3);
            lw(v0, s0, work::kMetrics);
            if (v0 == 0) {
                // 0x0036e1d8
                charge(ctx, 2);
                v0 = 1;
                sw(v0, s0, work::kMetrics);
            } else {
                // 0x0036e1cc
                charge(ctx, 3);
                sw(zero, s0, work::kMetrics);
            }
        }
    } else {
        // 0x0036e160
        charge(ctx, 5);
        jal(ctx, 0x36E160u, gen::fn_sub_39E6F0_0039e6f0);
        v1 = 1;
        if (v0 == v1) {
            // 0x0036e174
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x200;
            if (v0 != 0) {
                // 0x0036e188
                charge(ctx, 3);
                lw(v0, s0, work::kMetrics);
                if (v0 == 0) {
                    // 0x0036e1a0
                    charge(ctx, 3);
                    sw(v1, s0, work::kMetrics);
                } else {
                    // 0x0036e194
                    charge(ctx, 3);
                    sw(zero, s0, work::kMetrics);
                }
            }
        }
    }
    // 0x0036e1e0
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0036e1e8
        charge(ctx, 3);
        lw(v0, s0, work::kMetrics);
        if (v0 != 0) {
            // 0x0036e1f4
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x36E1F8u, gen::fn_sub_386D50_00386d50);
        }
    }
    // 0x0036e200
    charge(ctx, 5);
    lw(a0, s0, work::kOverlayTask);
    jal(ctx, 0x36E204u, gen::fn_kwlnTaskExists_00195460);
    if (v0 != 0) {
        // 0x0036e23c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0036e214
        charge(ctx, 10);
        lw(v1, s0, work::kFlags);
        v0 = lui(0xFFFD);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, s0, work::kFlags);
        sw(zero, s0, work::kOverlayTask);
        v0 = 0x370000;
        v0 = addiu(v0, -6512);  // &sub_36E690
    }
    // 0x0036e240 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036E260 sub_36E260 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtStepEnd] (process step): waits for the screen fade (sub_108710; "wait fade end") and, with kMode bit 2, for the
// field fade (sub_2FF310); then -1 (the process ends).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36E260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036e260
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    jal(ctx, 0x36E270u, gen::fn_sub_108710_00108710);
    if (v0 != 0) {
        // 0x0036e29c
        charge(ctx, 4);
        lb(v0, s0, work::kMode);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x0036e2ac
            charge(ctx, 5);
            jal(ctx, 0x36E2ACu, gen::fn_sub_2FF310_002ff310);
            v1 = 1;
            if (v0 == v1) {
                goto L_0036e2cc;
            }
            // 0x0036e2c0
            charge(ctx, 3);
            v0 = 0;
            // 0x0036e2d0 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0036e2cc:
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x0036e280
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, -8240);  // "wait fade end\n"
        jal(ctx, 0x36E288u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x0036e2d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036E690 sub_36E690 -- 1692 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtStepPlay] (process step): one frame of a playing event. Hands over to sub_36E260 (kFlagEnd), sub_36DB20
// (kFlagReload), sub_36E2F0 (0x10000) or sub_36E140 (kFlagOverlay); else draws the overlay, applies the frame's keys
// when the frame changed (sub_366AC0), handles the debug pad (metrics, "metrics draw" task, pause / editor entry,
// camera toggle), updates the camera (sub_38CA80), the message (sub_39F410) and the stop state (sub_36D030); ends the
// event on its last frame in play mode (or on the skip of events 80-1 / 80-5 after frame 30), and otherwise advances
// the frame (or takes a requested jump). Entering the editor (pad bit 2) returns sub_36D5F0 after resetting the
// camera, message, effects and fades.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36E690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036e690
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    s0 = 0;
    a0 = s1;
    jal(ctx, 0x36E6ACu, gen::fn_sub_385B20_00385b20);
    lw(v1, s1, work::kFlags);
    v0 = 0x40000;
    v0 = v1 & v0;
    if (v0 == 0) {
        // kFlagEnd -> sub_36E260; kFlagReload -> sub_36DB20; 0x10000 -> sub_36E2F0; kFlagOverlay -> sub_36E140
        // 0x0036e6d8
        charge(ctx, 3);
        v0 = v1 & 0x80;
        if (v0 == 0) {
            // 0x0036e6f4
            charge(ctx, 4);
            v0 = 0x10000;
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0036e714
                charge(ctx, 4);
                v0 = 0x20000;
                v0 = v1 & v0;
                if (v0 == 0) {
                    // playing: the overlay, then the keys of the frame when it changed since the last apply
                    // 0x0036e734
                    charge(ctx, 7);
                    a0 = s1;
                    jal(ctx, 0x36E738u, gen::fn_sub_362FF0_00362ff0);
                    lw(a0, s1, work::kFrame);
                    lw(v0, s1, work::kPrevFrame);
                    if (a0 != v0) {
                        // 0x0036e750
                        charge(ctx, 3);
                        a1 = s1;
                        jal(ctx, 0x36E754u, gen::fn_sub_366AC0_00366ac0);
                    }
                    // 0x0036e75c
                    charge(ctx, 5);
                    lw(v0, s1, work::kFrame);
                    sw(v0, s1, work::kPrevFrame);
                    lw(v0, s1, work::kMenuArg);
                    if (v0 == 0) {
                        // pad bit 0x200 toggles the metrics overlay (in play mode only when sub_39E6F0 allows the debug pad)
                        // 0x0036e770
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x200;
                        if (v0 != 0) {
                            // 0x0036e784
                            charge(ctx, 4);
                            lw(v0, s1, work::kFlags);
                            v0 = v0 & 0x8;
                            if (v0 == 0) {
                                // 0x0036e7cc
                                charge(ctx, 3);
                                lw(v0, s1, work::kMetrics);
                                if (v0 == 0) {
                                    // 0x0036e7e4
                                    charge(ctx, 2);
                                    v0 = 1;
                                    sw(v0, s1, work::kMetrics);
                                } else {
                                    // 0x0036e7d8
                                    charge(ctx, 3);
                                    sw(zero, s1, work::kMetrics);
                                }
                            } else {
                                // 0x0036e794
                                charge(ctx, 5);
                                jal(ctx, 0x36E794u, gen::fn_sub_39E6F0_0039e6f0);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x0036e7a8
                                    charge(ctx, 3);
                                    lw(v0, s1, work::kMetrics);
                                    if (v0 == 0) {
                                        // 0x0036e7c0
                                        charge(ctx, 3);
                                        sw(v1, s1, work::kMetrics);
                                    } else {
                                        // 0x0036e7b4
                                        charge(ctx, 3);
                                        sw(zero, s1, work::kMetrics);
                                    }
                                }
                            }
                        }
                    }
                    // 0x0036e7ec
                    charge(ctx, 4);
                    lw(v1, s1, work::kMetrics);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x0036e808
                        charge(ctx, 1);
                        sw(zero, gp, evt::kGpMetricsOn);  // 0x7CE5D8
                    } else {
                        // 0x0036e7fc
                        charge(ctx, 3);
                        sw(v0, gp, evt::kGpMetricsOn);  // 0x7CE5D8
                    }
                    // pad bit 0x1: the "metrics draw" task off (sub_1A7060) when it exists, else on (sub_1A7020)
                    // 0x0036e80c
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v0, v0, 2382);  // gPadFlags
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x0036e820
                        charge(ctx, 4);
                        lw(v0, s1, work::kFlags);
                        v0 = v0 & 0x8;
                        if (v0 == 0) {
                            // 0x0036e884
                            charge(ctx, 6);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -8224);  // "metrics draw"
                            jal(ctx, 0x36E88Cu, gen::fn_kwlnTaskGetTaskByName_00195340);
                            if (v0 != 0) {
                                // 0x0036e8b0
                                charge(ctx, 3);
                                a0 = 0;
                                jal(ctx, 0x36E8B4u, gen::fn_sub_1A7060_001a7060);
                            } else {
                                // 0x0036e89c
                                charge(ctx, 5);
                                a0 = 0;
                                jal(ctx, 0x36E8A0u, gen::fn_sub_1A7020_001a7020);
                            }
                        } else {
                            // 0x0036e830
                            charge(ctx, 5);
                            jal(ctx, 0x36E830u, gen::fn_sub_39E6F0_0039e6f0);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x0036e844
                                charge(ctx, 6);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, -8224);  // "metrics draw"
                                jal(ctx, 0x36E84Cu, gen::fn_kwlnTaskGetTaskByName_00195340);
                                if (v0 != 0) {
                                    // 0x0036e870
                                    charge(ctx, 5);
                                    a0 = 0;
                                    jal(ctx, 0x36E874u, gen::fn_sub_1A7060_001a7060);
                                } else {
                                    // 0x0036e85c
                                    charge(ctx, 5);
                                    a0 = 0;
                                    jal(ctx, 0x36E860u, gen::fn_sub_1A7020_001a7020);
                                }
                            }
                        }
                    }
                    // outside play mode: pad bit 0x2 enters the editor; else sub_3625E0, the camera toggle (pad 0x80), pause (pad 0x800)
                    // 0x0036e8bc
                    charge(ctx, 4);
                    lw(v1, s1, work::kFlags);
                    v0 = v1 & 0x8;
                    if (v0 == 0) {
                        // 0x0036e8cc
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x2;
                        if (v0 == 0) {
                            // 0x0036e8f8
                            charge(ctx, 7);
                            a0 = s1;
                            jal(ctx, 0x36E8FCu, gen::fn_sub_3625E0_003625e0);
                            jal(ctx, 0x36E904u, gen::fn_sub_3B5D00_003b5d00);
                            if (v0 != 0) {
                                // 0x0036e914
                                charge(ctx, 5);
                                v0 = 0x7E0000;
                                lhu(v0, v0, 2382);  // gPadFlags
                                v0 = v0 & 0x80;
                                if (v0 != 0) {
                                    // 0x0036e928
                                    charge(ctx, 3);
                                    a0 = s1;
                                    jal(ctx, 0x36E92Cu, gen::fn_sub_362F20_00362f20);
                                }
                            }
                            // 0x0036e934
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, 2382);  // gPadFlags
                            v0 = v0 & 0x800;
                            if (v0 != 0) {
                                // pad 0x800: pause when nothing holds the timeline, resume when only the pause holds it (the sub_36D030 condition)
                                // 0x0036e948
                                charge(ctx, 4);
                                lw(a0, s1, work::kFlags);
                                v1 = a0 & 0x1;
                                if (v1 == 0) {
                                    // 0x0036e958
                                    charge(ctx, 3);
                                    v0 = a0 & 0x20;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e964
                                    charge(ctx, 3);
                                    v0 = a0 & 0x200;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e970
                                    charge(ctx, 3);
                                    v0 = a0 & 0x400;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e97c
                                    charge(ctx, 3);
                                    v0 = a0 & 0x800;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e988
                                    charge(ctx, 3);
                                    v0 = a0 & 0x1000;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e994
                                    charge(ctx, 4);
                                    v0 = 0x20000;
                                    v0 = a0 & v0;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e9a4
                                    charge(ctx, 3);
                                    v0 = a0 & 0x2000;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e9b0
                                    charge(ctx, 3);
                                    v0 = a0 & 0x4000;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e9bc
                                    charge(ctx, 3);
                                    v0 = a0 & 0x8000;
                                    if (v0 != 0) {
                                        goto L_0036e9c8;
                                    }
                                    // 0x0036e9d4
                                    charge(ctx, 1);
                                    a0 = 0;
                                    goto L_0036e9d8;
                                }
                            L_0036e9c8:
                                charge(ctx, 3);
                                a0 = 1;
                            L_0036e9d8:
                                charge(ctx, 3);
                                v0 = 1;
                                if (a0 != v0) {
                                    // 0x0036ea04
                                    charge(ctx, 3);
                                    lw(v0, s1, work::kFlags);
                                    v0 = v0 | 0x1;
                                    sw(v0, s1, work::kFlags);
                                } else {
                                    // 0x0036e9e4
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        // 0x0036e9ec
                                        charge(ctx, 6);
                                        lw(v1, s1, work::kFlags);
                                        v0 = si(-2);
                                        v0 = v1 & v0;
                                        sw(v0, s1, work::kFlags);
                                    }
                                }
                            }
                            // 0x0036ea10
                            charge(ctx, 4);
                            lw(v0, s1, work::kFlags);
                            v0 = v0 & 0x1;
                            if (v0 != 0) {
                                // 0x0036ea20
                                charge(ctx, 3);
                                a0 = s1;
                                jal(ctx, 0x36EA24u, gen::fn_sub_362390_00362390);
                            }
                        } else {
                            // 0x0036e8e0
                            charge(ctx, 6);
                            v0 = v1 | 0x1;
                            sw(v0, s1, work::kFlags);
                            s0 = 0x370000;
                            s0 = addiu(s0, -10768);  // &sub_36D5F0
                        }
                    }
                    // every frame: model cameras, the message, the stop state
                    // 0x0036ea2c
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x36EA30u, gen::fn_sub_38CA80_0038ca80);
                    lw(v0, s1, work::kScene);
                    if (v0 != 0) {
                        // 0x0036ea44
                        charge(ctx, 5);
                        a0 = addiu(s1, 2092);
                        jal(ctx, 0x36EA48u, gen::fn_sub_39EEE0_0039eee0);
                        if (v0 != 0) {
                            // 0x0036ea58
                            charge(ctx, 3);
                            a0 = addiu(s1, 2092);
                            jal(ctx, 0x36EA5Cu, gen::fn_sub_39F410_0039f410);
                        }
                    }
                    // 0x0036ea64
                    charge(ctx, 7);
                    a0 = s1;
                    jal(ctx, 0x36EA68u, gen::fn_sub_36D030_0036d030);
                    lw(v0, s1, work::kFlags);
                    v0 = v0 & 0x8;
                    if (v0 != 0) {
                        // play mode: the skip combination (sub_39E6F0, pad 0x7E094C bits 0x4 and 0x8) ends the event
                        // 0x0036ea80
                        charge(ctx, 5);
                        jal(ctx, 0x36EA80u, gen::fn_sub_39E6F0_0039e6f0);
                        a0 = 1;
                        if (v0 != a0) {
                            goto L_0036eae8;
                        }
                        // 0x0036ea94
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v1, v0, 2380);  // 0x7E094C
                        v0 = v1 & 0x4;
                        if (v0 == 0) {
                            goto L_0036eae8;
                        }
                        // 0x0036eaa8
                        charge(ctx, 3);
                        v0 = v1 & 0x8;
                        if (v0 == 0) {
                            goto L_0036eae8;
                        }
                        // 0x0036eab4
                        charge(ctx, 4);
                        lb(v0, s1, work::kMode);
                        v0 = v0 & 0x4;
                        if (v0 != 0) {
                            // 0x0036eac4
                            charge(ctx, 2);
                            jal(ctx, 0x36EAC4u, gen::fn_sub_2FF260_002ff260);
                        }
                        // 0x0036eacc
                        charge(ctx, 7);
                        lw(v1, s1, work::kFlags);
                        v0 = 0x40000;
                        v0 = v1 | v0;
                        sw(v0, s1, work::kFlags);
                        v0 = 0;
                        // 0x0036ed14 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        ld(ra, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                // events 80-1 and 80-5 can be skipped (pad 0x800) from frame 31 on
                L_0036eae8:
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x36EAECu, gen::fn_sub_386E10_00386e10);
                    v1 = 80;
                    if (v0 == v1) {
                        // 0x0036eb00
                        charge(ctx, 6);
                        a0 = s1;
                        jal(ctx, 0x36EB04u, gen::fn_sub_386E30_00386e30);
                        v1 = 1;
                        if (v0 != v1) {
                            goto L_0036eb18;
                        }
                    L_0036eb48:
                        charge(ctx, 4);
                        lw(v0, s1, work::kFrame);
                        at = slti(v0, 31);
                        if (at != 0) {
                        // the last frame in play mode ends the event; otherwise advance (unless stopped; outside play mode the end toggles the pause) or jump
                        L_0036ebac:
                            charge(ctx, 4);
                            lw(v0, s1, work::kFlags);
                            a0 = v0 & 0x8;
                            if (a0 != 0) {
                                // 0x0036ebbc
                                charge(ctx, 5);
                                lw(v1, s1, work::kFrame);
                                lw(v0, s1, work::kEndFrame);
                                v0 = slt(v1, v0);
                                if (v0 != 0) {
                                    goto L_0036ec08;
                                }
                                // 0x0036ebd0
                                charge(ctx, 4);
                                lb(v0, s1, work::kMode);
                                v0 = v0 & 0x4;
                                if (v0 != 0) {
                                    // 0x0036ebe0
                                    charge(ctx, 3);
                                    a0 = 1;
                                    jal(ctx, 0x36EBE4u, gen::fn_sub_2FF260_002ff260);
                                }
                                // 0x0036ebec
                                charge(ctx, 7);
                                lw(v1, s1, work::kFlags);
                                v0 = 0x40000;
                                v0 = v1 | v0;
                                sw(v0, s1, work::kFlags);
                                v0 = 0;
                                // 0x0036ed14 (the shared epilogue, written out on this path)
                                charge(ctx, 6);
                                ld(ra, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x30);
                                return;
                            }
                        L_0036ec08:
                            charge(ctx, 4);
                            lw(v1, s1, work::kFrame);
                            lw(v0, s1, work::kStopped);
                            if (v0 == 0) {
                                // 0x0036ec18
                                charge(ctx, 4);
                                lw(v0, s1, work::kEndFrame);
                                v0 = slt(v1, v0);
                                if (v0 != 0) {
                                    // 0x0036ec44
                                    charge(ctx, 1);
                                    v1 = addiu(v1, 1);
                                } else {
                                    // 0x0036ec28
                                    charge(ctx, 2);
                                    if (a0 == 0) {
                                        // 0x0036ec30
                                        charge(ctx, 5);
                                        lw(v0, s1, work::kFlags);
                                        v0 = v0 ^ 0x1;
                                        sw(v0, s1, work::kFlags);
                                    }
                                }
                            }
                            // 0x0036ec48
                            charge(ctx, 3);
                            lw(v0, s1, work::kJumpRequest);
                            if (v0 != 0) {
                                // 0x0036ec54
                                charge(ctx, 2);
                                lw(v1, s1, work::kJumpFrame);
                                sw(zero, s1, work::kJumpRequest);
                            }
                            // 0x0036ec5c
                            charge(ctx, 5);
                            sw(v1, s1, work::kFrame);
                            v0 = 0x370000;
                            v0 = addiu(v0, -10768);  // &sub_36D5F0
                            if (s0 == v0) {
                                // entering the editor: menu stack reset, camera saved, menu 1 pushed, message closed, effects / sound / fades stopped, camera 1
                                // 0x0036ec70
                                charge(ctx, 15);
                                sw(zero, s1, work::kMenuId);
                                sw(zero, s1, work::kMenuDepth);
                                sw(zero, s1, work::kMenuArg);
                                a0 = s1;
                                jal(ctx, 0x36EC80u, gen::fn_sub_38A6C0_0038a6c0);
                                a0 = 1;
                                a1 = 2;
                                a2 = a1;
                                a3 = s1;
                                jal(ctx, 0x36EC98u, gen::fn_sub_36F5F0_0036f5f0);
                                lw(v0, s1, work::kScene);
                                if (v0 != 0) {
                                    // 0x0036ecac
                                    charge(ctx, 5);
                                    a0 = addiu(s1, 2092);
                                    jal(ctx, 0x36ECB0u, gen::fn_sub_39EEE0_0039eee0);
                                    if (v0 != 0) {
                                        // 0x0036ecc0
                                        charge(ctx, 3);
                                        a0 = addiu(s1, 2092);
                                        jal(ctx, 0x36ECC4u, gen::fn_sub_39F350_0039f350);
                                    }
                                }
                                // 0x0036eccc
                                charge(ctx, 10);
                                jal(ctx, 0x36ECCCu, gen::fn_sub_3970D0_003970d0);
                                jal(ctx, 0x36ECD4u, gen::fn_sub_3CF440_003cf440);
                                jal(ctx, 0x36ECDCu, gen::fn_sub_108F70_00108f70);
                                lw(v1, s1, work::kFading);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x0036ecf4
                                    charge(ctx, 3);
                                    jal(ctx, 0x36ECF4u, gen::fn_sub_1071B0_001071b0);
                                    sw(zero, s1, work::kFading);
                                }
                                // 0x0036ed00
                                charge(ctx, 4);
                                a0 = s1;
                                a1 = 1;
                                jal(ctx, 0x36ED08u, gen::fn_sub_38A0C0_0038a0c0);
                            }
                            // 0x0036ed10
                            charge(ctx, 1);
                            v0 = s0;
                        } else {
                            // 0x0036eb58
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, 2382);  // gPadFlags
                            v0 = v0 & 0x800;
                            if (v0 == 0) {
                                goto L_0036ebac;
                            }
                            // 0x0036eb6c
                            charge(ctx, 6);
                            jal(ctx, 0x36EB6Cu, gen::fn_sub_108F70_00108f70);
                            lb(v0, s1, work::kMode);
                            v0 = v0 & 0x4;
                            if (v0 != 0) {
                                // 0x0036eb84
                                charge(ctx, 3);
                                a0 = 1;
                                jal(ctx, 0x36EB88u, gen::fn_sub_2FF260_002ff260);
                            }
                            // 0x0036eb90
                            charge(ctx, 7);
                            lw(v1, s1, work::kFlags);
                            v0 = 0x40000;
                            v0 = v1 | v0;
                            sw(v0, s1, work::kFlags);
                            v0 = 0;
                        }
                        // 0x0036ed14 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        ld(ra, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                L_0036eb18:
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x36EB1Cu, gen::fn_sub_386E10_00386e10);
                    v1 = 80;
                    if (v0 != v1) {
                        goto L_0036ebac;
                    }
                    // 0x0036eb30
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x36EB34u, gen::fn_sub_386E30_00386e30);
                    v1 = 5;
                    if (v0 != v1) {
                        goto L_0036ebac;
                    }
                    goto L_0036eb48;
                }
                // 0x0036e724
                charge(ctx, 4);
                v0 = 0x370000;
                v0 = addiu(v0, -7872);  // &sub_36E140
            } else {
                // 0x0036e704
                charge(ctx, 4);
                v0 = 0x370000;
                v0 = addiu(v0, -7440);  // &sub_36E2F0
            }
        } else {
            // 0x0036e6e4
            charge(ctx, 4);
            v0 = 0x370000;
            v0 = addiu(v0, -9440);  // &sub_36DB20
        }
    } else {
        // 0x0036e6c8
        charge(ctx, 4);
        v0 = 0x370000;
        v0 = addiu(v0, -7584);  // &sub_36E260
    }
    // 0x0036ed14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0036ED30 sub_36ED30 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtStepMovieStart] (process step): after the PM data of a movie event: sound bank 2576 (sub_3951A0), sub_3953E0(own
// task), sub_396410, sub_1A4580(sub_198590()), sub_1A0420(1), event camera 0; next step sub_36E690.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36ED30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0036ed30
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    a0 = 2576;
    jal(ctx, 0x36ED4Cu, gen::fn_sub_3951A0_003951a0);
    lw(a0, s0, work::kTask);
    jal(ctx, 0x36ED58u, gen::fn_sub_3953E0_003953e0);
    a0 = s1;
    jal(ctx, 0x36ED64u, gen::fn_sub_396410_00396410);
    jal(ctx, 0x36ED6Cu, gen::fn_sub_198590_00198590);
    v1 = 0x420C0000;
    mtc1(v1, f12);
    a0 = v0;
    jal(ctx, 0x36ED80u, gen::fn_sub_1A4580_001a4580);
    a0 = 1;
    jal(ctx, 0x36ED8Cu, gen::fn_sub_1A0420_001a0420);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x36ED9Cu, gen::fn_sub_38A0C0_0038a0c0);
    v0 = 0x370000;
    v0 = addiu(v0, -6512);  // &sub_36E690
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0036EDD0 sub_36EDD0 -- 88 bytes; frame 0x10: ra sp+0x0
// [evtStepAfterPmLoad] (process step): sub_36DB20 when kFlagReload is set, else "polygon movie start!!" and
// sub_36ED30.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36EDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036edd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x36EDD8u, gen::fn_dds3GetProcessWorkData_0035ae10);
    lw(v0, v0, 4);
    v0 = v0 & 0x80;
    if (v0 == 0) {
        // 0x0036ee00
        charge(ctx, 6);
        a0 = 0x6A0000;
        a0 = addiu(a0, -8208);  // "(polygon movie start!! zikki load&datset complete)\n"
        jal(ctx, 0x36EE08u, gen::fn_printf_005225a8);
        v0 = 0x370000;
        v0 = addiu(v0, -4816);  // &sub_36ED30
    } else {
        // 0x0036edf0
        charge(ctx, 4);
        v0 = 0x370000;
        v0 = addiu(v0, -9440);  // &sub_36DB20
    }
    // 0x0036ee18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0036EE30 mtEvtMain_UpdateZikkiPlayModeEventViewerTask -- 384 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The kwln update of "(ZikkiPlayMode)EventViewer" (its first frame): initialises the work (sub_36F370), takes the event
// numbers from the PM reader's header (major +12, minor +16, +20 -> sub_397510; the reader is asserted, line 12399),
// writes the event name "E%3d_%03d", sets play mode (flags = kFlagPlayMode, metrics off) and switches the process to
// its step functions (sub_393E30 with sub_36EDD0 as the first step).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void mtEvtMain_UpdateZikkiPlayModeEventViewerTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036ee30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x36EE44u, gen::fn_dds3GetProcessWorkData_0035ae10);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x36EE54u, gen::fn_sub_36F370_0036f370);
    lw(v0, s0, work::kPmReader);
    if (v0 == 0) {
        // 0x0036ee68
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 12399;
        jal(ctx, 0x36EE74u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036ee7c
    charge(ctx, 77);
    lw(a0, s0, work::kPmReader);
    jal(ctx, 0x36EE80u, gen::fn_sub_3980E0_003980e0);
    s1 = v0;
    a0 = s0;
    lw(a1, v0, 12);
    jal(ctx, 0x36EE94u, gen::fn_sub_386E20_00386e20);
    a0 = s0;
    lw(a1, s1, 16);
    jal(ctx, 0x36EEA4u, gen::fn_sub_386E40_00386e40);
    a0 = s0;
    lw(a1, s1, 20);
    jal(ctx, 0x36EEB4u, gen::fn_sub_397510_00397510);
    a0 = s0;
    jal(ctx, 0x36EEC0u, gen::fn_sub_386E10_00386e10);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x36EED0u, gen::fn_sub_386E30_00386e30);
    a0 = addiu(s0, 324);
    a1 = 0x6A0000;
    a1 = addiu(a1, -10336);  // "E%3d_%03d"
    a2 = s1;
    a3 = v0;
    jal(ctx, 0x36EEECu, gen::fn_sprintf_00523ac8);
    a0 = s0;
    jal(ctx, 0x36EEF8u, gen::fn_sub_386E10_00386e10);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x36EF08u, gen::fn_sub_386E30_00386e30);
    a0 = 0x6A0000;
    a0 = addiu(a0, -8144);  // "(zikki playmode process1)majorno = %d minarno = %d\n"
    a1 = s1;
    a2 = v0;
    jal(ctx, 0x36EF20u, gen::fn_printf_005225a8);
    sw(zero, s0, work::kFlags);
    sw(zero, s0, work::kMetrics);
    lw(v0, s0, work::kFlags);
    v0 = v0 | 0x8;
    sw(v0, s0, work::kFlags);
    a0 = s0;
    jal(ctx, 0x36EF40u, gen::fn_sub_386E10_00386e10);
    s2 = v0;
    a0 = s0;
    jal(ctx, 0x36EF50u, gen::fn_sub_386E30_00386e30);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x36EF60u, gen::fn_sub_397500_00397500);
    a0 = s0;
    a1 = s2;
    a2 = s1;
    a3 = v0;
    t0 = 0;
    t1 = 0x370000;
    t1 = addiu(t1, -4656);  // &sub_36EDD0
    jal(ctx, 0x36EF84u, gen::fn_sub_393E30_00393e30);
    v0 = 0x370000;
    v0 = addiu(v0, -4656);  // &sub_36EDD0
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0036EFB0 sub_36EFB0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtResetPlayerModel] (): for the player model (resource 0x400): sub_3174E0(model +296), sub_3B7090(model id).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36EFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036efb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1024;
    jal(ctx, 0x36EFC0u, gen::fn_sub_3B5D10_003b5d10);
    s0 = v0;
    if (s0 != 0) {
        // 0x0036efd4
        charge(ctx, 6);
        lw(a0, s0, 296);
        jal(ctx, 0x36EFD8u, gen::fn_sub_3174E0_003174e0);
        lhu(a0, s0, 0);
        jal(ctx, 0x36EFE4u, gen::fn_sub_3B7090_003b7090);
    }
    // 0x0036efec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036F000 sub_36F000 -- 608 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtFreeScene] (work): stops what the event started (sub_3CF440, nullsub_28, sub_103CB0, the filter, effects, camera
// slots, the message, the sound bank entries, the sub task), frees the effect set; outside play mode also the player
// model state, resource backups (sub_388FF0) and the stage (sub_3B5AB0; "free stage"), clears a fade ("fade clear");
// then frees every unit with its keys (sub_361890 / sub_361C30 / sub_386B70), the scene (sub_394C30) and
// kOverlayTask.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f000
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x36F014u, gen::fn_sub_3CF440_003cf440);
    jal(ctx, 0x36F01Cu, gen::fn_nullsub_28_00395420);
    jal(ctx, 0x36F024u, gen::fn_sub_103CB0_00103cb0);
    jal(ctx, 0x36F02Cu, gen::fn_sub_3BCC80_003bcc80);
    jal(ctx, 0x36F034u, gen::fn_sub_3970D0_003970d0);
    jal(ctx, 0x36F03Cu, gen::fn_sub_38CA00_0038ca00);
    lw(v0, s0, work::kScene);
    if (v0 != 0) {
        // 0x0036f050
        charge(ctx, 5);
        a0 = addiu(s0, 2092);
        jal(ctx, 0x36F054u, gen::fn_sub_39EEE0_0039eee0);
        if (v0 != 0) {
            // 0x0036f064
            charge(ctx, 3);
            a0 = addiu(s0, 2092);
            jal(ctx, 0x36F068u, gen::fn_sub_39F350_0039f350);
        }
    }
    // 0x0036f070
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x36F074u, gen::fn_sub_38D720_0038d720);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036f08c
        charge(ctx, 2);
        jal(ctx, 0x36F08Cu, gen::fn_sub_108F70_00108f70);
    }
    // 0x0036f094
    charge(ctx, 3);
    lw(a0, s0, work::kSubTask);
    if (a0 != 0) {
        // 0x0036f0a0
        charge(ctx, 3);
        jal(ctx, 0x36F0A0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, s0, work::kSubTask);
    }
    // 0x0036f0ac
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0036f0b4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 359;
        jal(ctx, 0x36F0C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036f0c8
    charge(ctx, 10);
    jal(ctx, 0x36F0C8u, gen::fn_sub_39EB90_0039eb90);
    lw(a0, s0, work::kEffectSet);
    jal(ctx, 0x36F0D4u, gen::fn_sub_396530_00396530);
    sw(zero, s0, work::kEffectSet);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036f0f0
        charge(ctx, 6);
        a0 = 1024;
        jal(ctx, 0x36F0F4u, gen::fn_sub_3B5D10_003b5d10);
        s1 = v0;
        if (s1 != 0) {
            // 0x0036f108
            charge(ctx, 6);
            lw(a0, s1, 296);
            jal(ctx, 0x36F10Cu, gen::fn_sub_3174E0_003174e0);
            lhu(a0, s1, 0);
            jal(ctx, 0x36F118u, gen::fn_sub_3B7090_003b7090);
        }
        // 0x0036f120
        charge(ctx, 9);
        a0 = s0;
        jal(ctx, 0x36F124u, gen::fn_sub_388FF0_00388ff0);
        jal(ctx, 0x36F12Cu, gen::fn_sub_3B5AB0_003b5ab0);
        a0 = 0x6A0000;
        a0 = addiu(a0, -8088);  // "free stage\n"
        jal(ctx, 0x36F13Cu, gen::fn_printf_005225a8);
    }
    // 0x0036f144
    charge(ctx, 4);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036f154
        charge(ctx, 4);
        lw(v1, s0, work::kFading);
        v0 = 1;
        if (v1 == v0) {
            // 0x0036f164
            charge(ctx, 7);
            jal(ctx, 0x36F164u, gen::fn_sub_1071B0_001071b0);
            sw(zero, s0, work::kFading);
            a0 = 0x6A0000;
            a0 = addiu(a0, -8072);  // "fade clear \n"
            jal(ctx, 0x36F178u, gen::fn_printf_005225a8);
        }
    }
    // 0x0036f180
    charge(ctx, 10);
    jal(ctx, 0x36F180u, gen::fn_nullsub_22_0035ae50);
    jal(ctx, 0x36F188u, gen::fn_nullsub_23_0035ae60);
    jal(ctx, 0x36F190u, gen::fn_nullsub_24_0035ae70);
    jal(ctx, 0x36F198u, gen::fn_nullsub_25_0035ae80);
    for (;;) {
        // 0x0036f1f0
        charge(ctx, 3);
        lw(s1, s0, work::kUnitHead);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036f1a8
        charge(ctx, 2);
        for (;;) {
            // 0x0036f1bc
            charge(ctx, 5);
            lw(a1, s1, 108);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0036f1b0
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x36F1B4u, gen::fn_sub_361890_00361890);
        }
        // 0x0036f1d0
        charge(ctx, 8);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x36F1D8u, gen::fn_sub_361C30_00361c30);
        a1 = 7;
        a2 = 156;
        jal(ctx, 0x36F1E8u, gen::fn_sub_386B70_00386b70);
    }
    // 0x0036f1fc
    charge(ctx, 3);
    lw(a0, s0, work::kScene);
    if (a0 != 0) {
        // 0x0036f208
        charge(ctx, 4);
        a1 = addiu(s0, 2092);
        jal(ctx, 0x36F20Cu, gen::fn_sub_394C30_00394c30);
        sw(zero, s0, work::kScene);
    }
    // 0x0036f218
    charge(ctx, 3);
    lw(a0, s0, work::kOverlayTask);
    if (a0 != 0) {
        // 0x0036f224
        charge(ctx, 5);
        jal(ctx, 0x36F224u, gen::fn_kwlnTaskExists_00195460);
        v1 = 1;
        if (v0 == v1) {
            // 0x0036f238
            charge(ctx, 4);
            lw(a0, s0, work::kOverlayTask);
            jal(ctx, 0x36F23Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, s0, work::kOverlayTask);
        }
    }
    // 0x0036f248 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0036F260 sub_36F260 -- 268 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtViewerShutdown] the kwln destroy callback of the viewer task: sub_36F000, resource restore (sub_389F40, not in
// play mode), sub_3BB340, in play mode the comu index +69 (1..8) through sub_16DDD0, the PM reader (not in play mode),
// sub_1A0420(0), sound bank 5145 off, sub_3CF440, frees the work (class 0) and checks the memory counters
// (sub_386CD0); "evt Shutdown".
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f260
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x36F26Cu, gen::fn_dds3GetProcessWorkData_0035ae10);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x36F27Cu, gen::fn_sub_36F000_0036f000);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036f294
        charge(ctx, 2);
        jal(ctx, 0x36F294u, gen::fn_sub_389F40_00389f40);
    }
    // 0x0036f29c
    charge(ctx, 6);
    jal(ctx, 0x36F29Cu, gen::fn_sub_3BB340_003bb340);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0036f2b4
        charge(ctx, 3);
        lb(v0, s0, work::kComuIndex);
        if (i64(v0) > 0) {
            // 0x0036f2c0
            charge(ctx, 3);
            at = slti(v0, 9);
            if (at != 0) {
                // 0x0036f2cc
                charge(ctx, 3);
                a0 = addiu(v0, -1);
                jal(ctx, 0x36F2D0u, gen::fn_sub_16DDD0_0016ddd0);
            }
        }
    }
    // 0x0036f2d8
    charge(ctx, 4);
    lw(v0, s0, work::kFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0036f2e8
        charge(ctx, 3);
        lw(a0, s0, work::kPmReader);
        if (a0 != 0) {
            // 0x0036f2f4
            charge(ctx, 3);
            jal(ctx, 0x36F2F4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, s0, work::kPmReader);
        }
    }
    // 0x0036f300
    charge(ctx, 27);
    a0 = 0;
    jal(ctx, 0x36F304u, gen::fn_sub_1A0420_001a0420);
    a0 = s0;
    jal(ctx, 0x36F310u, gen::fn_nullsub_26_00385b90);
    a0 = 5145;
    jal(ctx, 0x36F31Cu, gen::fn_sub_3951A0_003951a0);
    jal(ctx, 0x36F324u, gen::fn_sub_3CF440_003cf440);
    lw(a0, s0, work::kSelf);
    a1 = 0;
    a2 = 2448;
    jal(ctx, 0x36F338u, gen::fn_sub_386B70_00386b70);
    jal(ctx, 0x36F340u, gen::fn_sub_386CD0_00386cd0);
    a0 = 0x6A0000;
    a0 = addiu(a0, -8056);  // "evt Shutdown\n"
    jal(ctx, 0x36F350u, gen::fn_printf_005225a8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036F370 sub_36F370 -- 60 bytes; frame 0x10: ra sp+0x0
// [evtViewerInit] (work): kField2344 = *0x7CDEAC, the editor cursors (sub_3858C0), the memory counters (sub_386AA0),
// sound bank 5145 on (sub_395170).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f370
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -20036);  // 0x7CDEAC
    sw(v0, a0, work::kField2344);
    jal(ctx, 0x36F380u, gen::fn_sub_3858C0_003858c0);
    jal(ctx, 0x36F388u, gen::fn_sub_386AA0_00386aa0);
    a0 = 5145;
    jal(ctx, 0x36F394u, gen::fn_sub_395170_00395170);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0036F3B0 mtEvtMain_CreateZikkiPlayModeEventViewerTask -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the event viewer (called by K_Field_UpdateFieldRootTask with the parent task and the PM reader that loaded the
// event): allocates the 2448-byte work (class 0; asserted, line 12714), zeroes it, kSelf, clears the field-resume pair
// 0x7CE5F0 / 0x7CE5F4, and creates the kwln task "(ZikkiPlayMode)EventViewer" (priority 15, update
// mtEvtMain_UpdateZikkiPlayModeEventViewerTask, destroy sub_36F260) -> kTask; kPmReader = the reader. Returns the
// task.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void mtEvtMain_CreateZikkiPlayModeEventViewerTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f3b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 2448;
    a1 = 0;
    jal(ctx, 0x36F3D4u, gen::fn_sub_386AE0_00386ae0);
    s0 = v0;
    if (s0 == 0) {
        // 0x0036f3e8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10880);  // "mt_evtMain.c"
        a1 = 12714;
        jal(ctx, 0x36F3F4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036f3fc
    charge(ctx, 31);
    a0 = s0;
    a1 = 0;
    a2 = 2448;
    jal(ctx, 0x36F408u, gen::fn_memset_00521408);
    sw(s0, s0, work::kSelf);
    jal(ctx, 0x36F414u, gen::fn_sub_36F4D0_0036f4d0);
    a0 = 0;
    jal(ctx, 0x36F420u, gen::fn_sub_36F490_0036f490);
    a0 = s2;
    a1 = 0x6A0000;
    a1 = addiu(a1, -8032);  // "(ZikkiPlayMode)EventViewer"
    a2 = 15;
    a3 = 0x370000;
    a3 = addiu(a3, -4560);  // &mtEvtMain_UpdateZikkiPlayModeEventViewerTask
    t0 = 0x370000;
    t0 = addiu(t0, -3488);  // &sub_36F260
    t1 = s0;
    jal(ctx, 0x36F44Cu, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, work::kTask);
    sw(s1, s0, work::kPmReader);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0036F480 sub_36F480 -- 16 bytes; leaf frame (no stack)
// [evtGetKeyFree] () -> 0x7CE5F0 != 0: whether the field resumes free movement after the event (a type-39 key).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0036f480
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, evt::kGpKeyFree);  // 0x7CE5F0
    v0 = sltu(0, v0);
}

// 0x0036F490 sub_36F490 -- 36 bytes; leaf frame (no stack)
// [evtSetKeyFree] (on): 0x7CE5F0 = (on == 1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0036f490
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 1;
    if (a0 != v1) {
        // 0x0036f4a8
        charge(ctx, 1);
        sw(zero, gp, evt::kGpKeyFree);  // 0x7CE5F0
    } else {
        // 0x0036f49c
        charge(ctx, 3);
        sw(v1, gp, evt::kGpKeyFree);  // 0x7CE5F0
    }
    // 0x0036f4ac (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0036F4C0 sub_36F4C0 -- 12 bytes; leaf frame (no stack)
// [evtGetStartPos] () -> 0x7CE5F4: the entrance the field places the party at after the event.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F4C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0036f4c0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, evt::kGpStartPos);  // 0x7CE5F4
}

// 0x0036F4D0 sub_36F4D0 -- 44 bytes; frame 0x10: ra sp+0x0
// [evtClearKeyFree] (): clears 0x7CE5F0 / 0x7CE5F4 (memset 8).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F4D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f4d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(gp, -18176);  // &0x7CE5F0
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x36F4E4u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0036F500 sub_36F500 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtUnitTypeHasCondition] (type) -> 1 when keys of this unit type can carry a condition: the unit type's row of the
// editor table 0x69E1A0 (12 bytes: s16 count, menu ids from +2, a cache byte at +10) lists menu 18; the answer is cached
// in the row (1 yes, 2 no). Type >= 51 asserts (mt_evtMenu.c line 160).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0036f500
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = slti(s0, 51);
    if (v0 == 0) {
        // 0x0036f51c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -7160);  // "mt_evtMenu.c"
        a1 = 160;
        jal(ctx, 0x36F528u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0036f530
    charge(ctx, 10);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    a0 = sll(v0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, -7766);  // &0x69E1AA
    a2 = addu(v0, a0);
    lb(v1, a2, 0);
    v0 = 1;
    if (v1 != v0) {
        // 0x0036f560
        charge(ctx, 3);
        v0 = 2;
        if (v1 != v0) {
            // 0x0036f578
            charge(ctx, 8);
            a3 = 0;
            v0 = 0x6A0000;
            v0 = addiu(v0, -7776);  // &0x69E1A0
            a1 = addu(v0, a0);
            lh(a0, a1, 0);
            v1 = 18;
            for (;;) {
                // 0x0036f5bc
                charge(ctx, 3);
                v0 = slt(a3, a0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0036f598
                charge(ctx, 4);
                v0 = addu(a1, a3);
                lb(v0, v0, 2);
                if (v0 == v1) {
                    goto L_0036f5a8_8;
                }
                // 0x0036f5b8
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0036f5c8
            charge(ctx, 3);
            v0 = 2;
            sb(v0, a2, 0);
            v0 = 0;
        } else {
            // 0x0036f56c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0036f558
        charge(ctx, 2);
    }
    // 0x0036f5d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0036f5a8_8:
    charge(ctx, 4);
    v0 = 1;
    sb(v0, a2, 0);
    // 0x0036f5d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0036F5F0 sub_36F5F0 -- 72 bytes; leaf frame (no stack)
// [evtEdPushMenu] (menu, a, b, work): pushes {menu, a, b} on the editor's menu stack, kMenuId = menu.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0036f5f0
    enter(ctx, 18);  // entry check point + this block's cycles
    lw(v1, a3, work::kMenuDepth);
    v1 = addiu(v1, 1);
    sw(v1, a3, work::kMenuDepth);
    a0 = a0 & 0xFF;
    v1 = sll(v1, 3);
    v1 = addu(v1, a3);
    sh(a0, v1, 144);
    lw(v1, a3, work::kMenuDepth);
    v1 = sll(v1, 3);
    v1 = addu(v1, a3);
    sh(a1, v1, 146);
    lw(v1, a3, work::kMenuDepth);
    v1 = sll(v1, 3);
    v1 = addu(v1, a3);
    sh(a2, v1, 148);
    sw(a0, a3, work::kMenuId);
}

// 0x0036F640 sub_36F640 -- 60 bytes; leaf frame (no stack)
// [evtEdPopMenu] (work) -> the menu below the top (kMenuId), 0 when the stack is empty.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x0036f640
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, work::kMenuDepth);
    if (v0 != 0) {
        // 0x0036f65c
        charge(ctx, 6);
        v0 = addiu(v0, -1);
        sw(v0, a0, work::kMenuDepth);
        v0 = sll(v0, 3);
        v0 = addu(v0, a0);
        lh(v0, v0, 144);
        sw(v0, a0, work::kMenuId);
    } else {
        // 0x0036f64c
        charge(ctx, 4);
        sw(zero, a0, work::kMenuId);
        v0 = 0;
    }
    // 0x0036f674 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0036F900 sub_36F900 -- 320 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtEdDrawList] (x, y, w, h, first, ?, ?, work, header fn, row fn): the editor's list frame (sub_38A220 size,
// sub_385990 cursor box at 12-pixel cells), an optional header callback and one row callback per line (jalr).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36F900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0036f900
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t2;
    s7 = t3;
    lw(fp, sp, 0xA0);
    s6 = 0;
    lw(a0, t2, 224);
    jal(ctx, 0x36F954u, gen::fn_sub_38A220_0038a220);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    add_s(f12, f1, f0);
    v0 = sll(s5, 1);
    v0 = addu(v0, s5);
    a1 = sll(v0, 2);
    v0 = sll(s4, 1);
    v0 = addu(v0, s4);
    a2 = sll(v0, 2);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    a3 = sll(v0, 2);
    v0 = sll(s2, 1);
    v0 = addu(v0, s2);
    t0 = sll(v0, 2);
    a0 = s0;
    jal(ctx, 0x36F9A0u, gen::fn_sub_385990_00385990);
    if (s7 != 0) {
        // 0x0036f9b0
        charge(ctx, 7);
        a0 = s5;
        a1 = s4;
        a2 = s0;
        jalr(ctx, 0x36F9BCu, s7.u());
        s4 = addu(s4, v0);
        s6 = addu(s6, v0);
    }
    // 0x0036f9cc
    charge(ctx, 2);
    for (;;) {
        // 0x0036fa00
        charge(ctx, 3);
        v1 = slt(s6, s2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0036f9d4
        charge(ctx, 2);
        if (fp != 0) {
            // 0x0036f9dc
            charge(ctx, 8);
            a0 = s5;
            a1 = s4;
            a2 = s1;
            a3 = s0;
            jalr(ctx, 0x36F9ECu, fp.u());
            s1 = addiu(s1, 1);
            s4 = addiu(s4, 1);
        }
        // 0x0036f9fc
        charge(ctx, 1);
        s6 = addiu(s6, 1);
    }
    // 0x0036fa0c
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x0036FA40 sub_36FA40 -- 52 bytes; leaf frame (no stack)
// [evtEdMenuValue] (work) -> the byte at column kEdColumn (+616) of the row of the editor unit's type in the table 0x69E422.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_36FA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0036fa40
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v0, a0, work::kEdUnit);
    lw(v1, v0, 0);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, -7134);  // &0x69E422
    v1 = addu(v0, v1);
    lw(v0, a0, work::kEdColumn);
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
}

// 0x00385860 sub_385860 -- 96 bytes; frame 0x10: ra sp+0x0
// [evtEdCallMenu] (id, arg, a, b, work) -> the menu function 0x6A0270[id](a, b, work) after noting id / arg in the work;
// 0 for an empty slot.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_385860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00385860
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = sll(a0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 624);  // &0x6A0270
    v1 = addu(v0, v1);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x00385890
        charge(ctx, 8);
        sw(a0, t0, work::kMenuFn);
        sw(a1, t0, work::kMenuFont);
        a0 = a2;
        a1 = a3;
        a2 = t0;
        lw(v0, v1, 0);
        jalr(ctx, 0x3858A8u, v0.u());
    } else {
        // 0x00385884
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003858b0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003858C0 sub_3858C0 -- 204 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtEdCreateCursors] (work): seven H_Cursor tasks (box 130 x 288) under the viewer task, hidden.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_3858C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003858c0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sw(zero, sp, 0x40);
    sw(zero, sp, 0x44);
    v1 = 130;
    sw(v1, sp, 0x48);
    v1 = 288;
    sw(v1, sp, 0x4C);
    sw(zero, sp, 0x50);
    sw(zero, sp, 0x54);
    v1 = 180;
    sb(v1, sp, 0x5F);
    v1 = 10;
    sb(v1, sp, 0x5C);
    sb(v1, sp, 0x5E);
    v1 = 64;
    sb(v1, sp, 0x5D);
    s0 = 0;
    for (;;) {
        // 0x00385964
        charge(ctx, 3);
        v1 = slti(s0, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00385920
        charge(ctx, 17);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 2372);
        v0 = 0x40000000;
        mtc1(v0, f12);
        lw(a0, s1, work::kTask);
        ld(a1, sp, 0x50);
        a2 = addiu(sp, 0x40);
        lw(a3, sp, 0x5C);
        jal(ctx, 0x385944u, gen::fn_H_Cursor_CreateTask_001005b0);
        sw(v0, s2, 0);
        a0 = v0;
        jal(ctx, 0x385954u, gen::fn_H_Cursor_GetShouldDraw_00100570);
        sw(zero, v0, 0);
        s0 = addiu(s0, 1);
    }
    // 0x00385970
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00385B20 sub_385B20 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtEdHideCursors] (work): hides the seven cursors and clears kCursorShown.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_385B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00385b20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sb(zero, a0, work::kCursorShown);
    s0 = 0;
    for (;;) {
        // 0x00385b68
        charge(ctx, 3);
        v1 = slti(s0, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00385b44
        charge(ctx, 5);
        v1 = sll(s0, 2);
        v1 = addu(s1, v1);
        lw(a0, v1, 2372);
        if (a0 != 0) {
            // 0x00385b58
            charge(ctx, 3);
            jal(ctx, 0x385B58u, gen::fn_H_Cursor_GetShouldDraw_00100570);
            sw(zero, v0, 0);
        }
        // 0x00385b64
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00385b74
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00385B90 nullsub_26 -- 8 bytes; leaf frame (no stack)
// An empty hook of the viewer shutdown (sub_36F260).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void nullsub_26(EEContext& ctx) {
    using namespace hg;
    // 0x00385b90
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00385BA0 sub_385BA0 -- 44 bytes; frame 0x10: ra sp+0x0
// The editor's placeholder menu function: printf("this is new menu func lid=%d\n", 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_385BA0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00385ba0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x6A0000;
    a0 = addiu(a0, 816);  // "this is new menu func lid=%d\n"
    a1 = 0;
    jal(ctx, 0x385BB4u, gen::fn_printf_005225a8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00386110 sub_386110 -- 32 bytes; leaf frame (no stack)
// (out a, out b): *a = 0x9588A0, *b = 0x958890 (two float vectors the editor edits).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386110(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00386110
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, -30560);  // &0x9588A0
    sw(v1, a0, 0);
    v1 = 0x960000;
    v1 = addiu(v1, -30576);  // &0x958890
    sw(v1, a1, 0);
}

// 0x00386210 sub_386210 -- 32 bytes; leaf frame (no stack)
// The same as sub_386110 (a second caller-facing copy).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386210(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00386210
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, -30560);  // &0x9588A0
    sw(v1, a0, 0);
    v1 = 0x960000;
    v1 = addiu(v1, -30576);  // &0x958890
    sw(v1, a1, 0);
}

// 0x00386390 sub_386390 -- 44 bytes; leaf frame (no stack)
// (out a, out b, out c, out d): *a = *0x958850, *b = 0x7CE60C, *c = 0x7CE608, *d = *0x7CE604.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386390(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x00386390
    enter(ctx, 11);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, -30640);  // &0x958850
    sw(v1, a0, 0);
    v1 = addiu(gp, -18148);  // &0x7CE60C
    sw(v1, a1, 0);
    v1 = addiu(gp, -18152);  // &0x7CE608
    sw(v1, a2, 0);
    lw(v1, gp, -18156);  // 0x7CE604
    sw(v1, a3, 0);
}

// 0x00386AA0 sub_386AA0 -- 64 bytes; leaf frame (no stack)
// [evtMemResetCounters] (): clears the memory counters 1..12 of 0x958A60 (counter 0 kept).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00386aa0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    a0 = 0x960000;
    a0 = addiu(a0, -30112);  // &0x958A60
    for (;;) {
        // 0x00386acc
        charge(ctx, 3);
        v1 = slti(a1, 13);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00386ab4
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x00386abc
            charge(ctx, 3);
            v1 = sll(a1, 2);
            v1 = addu(a0, v1);
            sw(zero, v1, 0);
        }
        // 0x00386ac8
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x00386ad8
    charge(ctx, 2);
}

// 0x00386AE0 sub_386AE0 -- 136 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtAlloc] (size, class) -> block: RwMalloc-style allocation through the slot 0x960184 (hint 0x40000; asserted,
// mt_evtMisc.c line 59) and adds the size to memory counter `class` (sub_386C40).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00386ae0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = s2;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x386B10u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x00386b24
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 2576);  // "mt_evtMisc.c"
        a1 = 59;
        jal(ctx, 0x386B30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00386b38
    charge(ctx, 12);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x386B40u, gen::fn_sub_386C40_00386c40);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00386B70 sub_386B70 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtFree] (block, class, size): frees through the slot 0x96017C; counters 0 / 4 / 5 / 6 are cleared, the others (but
// 9) lose `size`.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00386b70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x386B90u, v0.u());
    at = slti(s1, 13);
    if (at != 0) {
        // 0x00386ba4
        charge(ctx, 2);
        if (i64(s1) >= 0) {
            // 0x00386bac
            charge(ctx, 3);
            v1 = 9;
            if (s1 != v1) {
                // 0x00386bb8
                charge(ctx, 3);
                v1 = 6;
                if (s1 != v1) {
                    // 0x00386bc4
                    charge(ctx, 3);
                    v1 = 5;
                    if (s1 == v1) {
                        goto L_00386bec;
                    }
                    // 0x00386bd0
                    charge(ctx, 3);
                    v1 = 4;
                    if (s1 == v1) {
                        goto L_00386bec;
                    }
                    // 0x00386bdc
                    charge(ctx, 2);
                    if (s1 == 0) {
                        goto L_00386bec;
                    }
                    // 0x00386be4
                    charge(ctx, 2);
                    // 0x00386c08
                    charge(ctx, 7);
                    a0 = sll(s1, 2);
                    v1 = 0x960000;
                    v1 = addiu(v1, -30112);  // &0x958A60
                    a0 = addu(v1, a0);
                    lw(v1, a0, 0);
                    v1 = subu(v1, s0);
                    sw(v1, a0, 0);
                    // 0x00386c24 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_00386bec:
                charge(ctx, 7);
                a0 = sll(s1, 2);
                v1 = 0x960000;
                v1 = addiu(v1, -30112);  // &0x958A60
                v1 = addu(v1, a0);
                sw(zero, v1, 0);
            }
        }
    }
    // 0x00386c24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00386C40 sub_386C40 -- 136 bytes; leaf frame (no stack)
// [evtMemCount] (class, size): counters 0 / 4 / 5 / 6 are set to `size`, the others (<= 12) grow by it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386C40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00386c40
    enter(ctx, 3);  // entry check point + this block's cycles
    at = slti(a0, 13);
    if (at != 0) {
        // 0x00386c4c
        charge(ctx, 2);
        if (i64(a0) >= 0) {
            // 0x00386c54
            charge(ctx, 3);
            v1 = 6;
            if (a0 != v1) {
                // 0x00386c60
                charge(ctx, 3);
                v1 = 5;
                if (a0 == v1) {
                    goto L_00386c88;
                }
                // 0x00386c6c
                charge(ctx, 3);
                v1 = 4;
                if (a0 == v1) {
                    goto L_00386c88;
                }
                // 0x00386c78
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_00386c88;
                }
                // 0x00386c80
                charge(ctx, 2);
                // 0x00386ca4
                charge(ctx, 7);
                a0 = sll(a0, 2);
                v1 = 0x960000;
                v1 = addiu(v1, -30112);  // &0x958A60
                a0 = addu(v1, a0);
                lw(v1, a0, 0);
                v1 = addu(v1, a1);
                sw(v1, a0, 0);
                // 0x00386cc0 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
        L_00386c88:
            charge(ctx, 7);
            a0 = sll(a0, 2);
            v1 = 0x960000;
            v1 = addiu(v1, -30112);  // &0x958A60
            v1 = addu(v1, a0);
            sw(a1, v1, 0);
        }
    }
    // 0x00386cc0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00386CD0 sub_386CD0 -- 124 bytes; leaf frame (no stack)
// [evtMemAllFreed] () -> 1 when the counters 1..12 except 4 / 5 / 6 are all zero.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00386cd0
    enter(ctx, 8);  // entry check point + this block's cycles
    a3 = 0;
    v1 = 0x960000;
    v1 = addiu(v1, -30112);  // &0x958A60
    a0 = 6;
    a1 = 5;
    a2 = 4;
    for (;;) {
        // 0x00386d34
        charge(ctx, 3);
        v0 = slti(a3, 13);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00386cf0
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x00386cf8
            charge(ctx, 2);
            if (a3 == a2) {
                goto L_00386d30;
            }
            // 0x00386d00
            charge(ctx, 2);
            if (a3 == a1) {
                goto L_00386d30;
            }
            // 0x00386d08
            charge(ctx, 2);
            if (a3 == a0) {
                goto L_00386d30;
            }
            // 0x00386d10
            charge(ctx, 5);
            v0 = sll(a3, 2);
            v0 = addu(v1, v0);
            lw(v0, v0, 0);
            if (v0 == 0) {
                goto L_00386d30;
            }
            goto L_00386d24_6;
        }
    L_00386d30:
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x00386d40
    charge(ctx, 1);
    v0 = 1;
    // 0x00386d44 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00386d24_6:
    charge(ctx, 3);
    v0 = 0;
    // 0x00386d44 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00386E10 sub_386E10 -- 12 bytes; leaf frame (no stack)
// [evtGetMajor] (work) -> kMajor.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00386e10
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, work::kMajor);
}

// 0x00386E20 sub_386E20 -- 16 bytes; leaf frame (no stack)
// [evtSetMajor] (work, major): kMajor and the global 0x7CCA68.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386E20(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00386e20
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a1, a0, work::kMajor);
    sh(a1, gp, -25224);  // 0x7CCA68
}

// 0x00386E30 sub_386E30 -- 12 bytes; leaf frame (no stack)
// [evtGetMinor] (work) -> kMinor.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00386e30
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, work::kMinor);
}

// 0x00386E40 sub_386E40 -- 16 bytes; leaf frame (no stack)
// [evtSetMinor] (work, minor): kMinor and the global 0x7CCA6C.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_386E40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00386e40
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a1, a0, work::kMinor);
    sh(a1, gp, -25220);  // 0x7CCA6C
}

// 0x00388FF0 sub_388FF0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtFreeResources] (work): frees every resource backup of kResources (slot 0x96017C), then the array, lowering the
// counter 0x958A90 by its size; clears the count.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_388FF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00388ff0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v1, a0, work::kResources);
    if (v1 != 0) {
        // 0x00389024
        charge(ctx, 4);
        lw(s1, s3, work::kResCount);
        s2 = 0;
        for (;;) {
            // 0x00389074
            charge(ctx, 3);
            v0 = slt(s2, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00389034
            charge(ctx, 6);
            lw(v0, s3, work::kResources);
            s0 = sll(s2, 2);
            v0 = addu(v0, s0);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x0038904c
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x00389054
                    charge(ctx, 7);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    jalr(ctx, 0x38905Cu, v0.u());
                    lw(v0, s3, work::kResources);
                    v0 = addu(v0, s0);
                    sw(zero, v0, 0);
                }
            }
            // 0x00389070
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x00389080
        charge(ctx, 14);
        lw(v0, s3, work::kResCount);
        s0 = sll(v0, 2);
        lw(a0, s3, work::kResources);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x389094u, v0.u());
        v1 = 0x960000;
        lw(v1, v1, -30064);  // 0x958A90
        a0 = subu(v1, s0);
        v1 = 0x960000;
        sw(a0, v1, -30064);  // 0x958A90
        sw(zero, s3, work::kResources);
        sw(zero, s3, work::kResCount);
    } else {
        // 0x00389018
        charge(ctx, 3);
        sw(zero, s3, work::kResCount);
    }
    // 0x003890b8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00389F40 sub_389F40 -- 368 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtFreeNpcBackups] (): frees the 84-byte NPC backup records' buffers (+64) of the table 0x9589CC (count 0x9589C8),
// then the table; the counter update indexes 0x958A60 by 84 * count (as the original computes it).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_389F40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00389f40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0x960000;
    lw(s1, v1, -30264);  // 0x9589C8
    v1 = 0x960000;
    lw(s0, v1, -30260);  // 0x9589CC
    if (s1 != 0) {
        // 0x00389f70
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x00389fbc
            charge(ctx, 3);
            v0 = slt(s2, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00389f7c
            charge(ctx, 10);
            v0 = sll(s2, 3);
            v1 = subu(v0, s2);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 64);
            lw(a0, v0, 64);
            if (a0 != 0) {
                // 0x00389fa4
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x389FACu, v0.u());
                sw(zero, s3, 0);
            }
            // 0x00389fb8
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x00389fc8
        charge(ctx, 14);
        v0 = 0x960000;
        lw(a0, v0, -30260);  // 0x9589CC
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x389FD8u, v0.u());
        v1 = sll(s1, 3);
        a0 = subu(v1, s1);
        v1 = sll(a0, 2);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        at = slti(a0, 13);
        if (at != 0) {
            // 0x0038a000
            charge(ctx, 2);
            if (i64(a0) >= 0) {
                // 0x0038a008
                charge(ctx, 3);
                v1 = 9;
                if (a0 != v1) {
                    // 0x0038a014
                    charge(ctx, 3);
                    v1 = 6;
                    if (a0 != v1) {
                        // 0x0038a020
                        charge(ctx, 3);
                        v1 = 5;
                        if (a0 == v1) {
                            goto L_0038a048;
                        }
                        // 0x0038a02c
                        charge(ctx, 3);
                        v1 = 4;
                        if (a0 == v1) {
                            goto L_0038a048;
                        }
                        // 0x0038a038
                        charge(ctx, 2);
                        if (a0 == 0) {
                            goto L_0038a048;
                        }
                        // 0x0038a040
                        charge(ctx, 2);
                        // 0x0038a064
                        charge(ctx, 7);
                        a0 = sll(a0, 2);
                        v1 = 0x960000;
                        v1 = addiu(v1, -30112);  // &0x958A60
                        a0 = addu(v1, a0);
                        lw(v1, a0, 0);
                        v1 = addiu(v1, -1);
                        sw(v1, a0, 0);
                        goto L_0038a080;
                    }
                L_0038a048:
                    charge(ctx, 7);
                    a0 = sll(a0, 2);
                    v1 = 0x960000;
                    v1 = addiu(v1, -30112);  // &0x958A60
                    v1 = addu(v1, a0);
                    sw(zero, v1, 0);
                }
            }
        }
    L_0038a080:
        charge(ctx, 4);
        v1 = 0x960000;
        sw(zero, v1, -30260);  // 0x9589CC
        v1 = 0x960000;
        sw(zero, v1, -30264);  // 0x9589C8
    }
    // 0x0038a090 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0038A0B0 sub_38A0B0 -- 12 bytes; leaf frame (no stack)
// [evtGetCameraSel] (work) -> kCamSel.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0038a0b0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, work::kCamSel);
}

// 0x0038A0C0 sub_38A0C0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtSetCameraSel] (work, sel): sel 0 / 1 activates the event camera 0x1E58 / 0x1E59 (sub_3BB280) and stores it.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A0C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a0c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    at = slti(s0, 2);
    if (at != 0) {
        // 0x0038a0e4
        charge(ctx, 3);
        v1 = 1;
        if (s0 == v1) {
            // 0x0038a114
            charge(ctx, 3);
            a0 = 7769;
            jal(ctx, 0x38A118u, gen::fn_sub_3BB280_003bb280);
        } else {
            // 0x0038a0f0
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x0038a100
                charge(ctx, 5);
                a0 = 7768;
                jal(ctx, 0x38A104u, gen::fn_sub_3BB280_003bb280);
            } else {
                // 0x0038a0f8
                charge(ctx, 2);
            }
        }
        // 0x0038a120
        charge(ctx, 1);
        sw(s0, s1, work::kCamSel);
    }
    // 0x0038a124 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038A140 sub_38A140 -- 52 bytes; leaf frame (no stack)
// [evtEdCopyKey] (type, src): remembers a 84-byte key image (21 words) at 0x958970 with its unit type (editor copy).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A140(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0038a140
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a0, gp, -18140);  // 0x7CE614
    a2 = 0x960000;
    a2 = addiu(a2, -30352);  // &0x958970
    a0 = 21;
    for (;;) {
        // 0x0038a150
        charge(ctx, 7);
        lw(v1, a1, 0);
        a1 = addiu(a1, 4);
        a0 = addiu(a0, -1);
        sw(v1, a2, 0);
        a2 = addiu(a2, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0038a16c
    charge(ctx, 2);
}

// 0x0038A180 sub_38A180 -- 156 bytes; leaf frame (no stack)
// [evtEdPasteKey] (type, dst): pastes the remembered camera-model key (type 33) fields into dst.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A180(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, gp{ctx, 28};
    Fpr f0{ctx, 0};
    // 0x0038a180
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a2, gp, -18140);  // 0x7CE614
    if (a2 == a0) {
        // 0x0038a18c
        charge(ctx, 3);
        v1 = 33;
        if (a2 == v1) {
            // 0x0038a1a0
            charge(ctx, 12);
            v1 = 0x960000;
            lhu(v1, v1, -30350);  // 0x958972
            sh(v1, a1, 2);
            t5 = 0;
            t4 = 0x960000;
            t4 = addiu(t4, -30352);  // &0x958970
            a3 = 0x960000;
            a2 = 0x960000;
            a0 = 0x960000;
            v1 = 0x960000;
            for (;;) {
                // 0x0038a208
                charge(ctx, 3);
                t0 = slti(t5, 10);
                if (t0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0038a1d0
                charge(ctx, 14);
                t0 = sll(t5, 2);
                t1 = addu(t4, t0);
                t0 = addu(a1, t0);
                lwc1(f0, t1, 16);
                swc1(f0, t0, 16);
                lh(t3, a3, -30344);
                lh(t2, a2, -30342);
                lh(t1, a0, -30340);
                lh(t0, v1, -30338);
                sh(t3, a1, 8);
                sh(t2, a1, 10);
                sh(t1, a1, 12);
                sh(t0, a1, 14);
                t5 = addiu(t5, 1);
            }
        } else {
            // 0x0038a198
            charge(ctx, 2);
        }
    }
    // 0x0038a214 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0038A220 sub_38A220 -- 52 bytes; leaf frame (no stack)
// [evtEdTextScale] (n) -> 100 - 10 * n as a float (adda.s / msub.s): the editor's line height.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A220(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0038a220
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 0x41200000;
    mtc1(v0, f3);
    mtc1(a0, f0);
    cvt_s_w(f2, f0);
    v0 = 0x42C80000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    msub_s(f0, f3, f2);
}

// 0x0038A480 sub_38A480 -- 48 bytes; leaf frame (no stack)
// [evtClampAdd] (a, b, lo, hi) -> clamp(a + b, lo, hi) (hi wins over lo).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A480(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0038a480
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = addu(a0, a1);
    at = slt(a0, a2);
    if (at != 0) {
        // 0x0038a490
        charge(ctx, 1);
        a0 = a2;
    }
    // 0x0038a494
    charge(ctx, 3);
    v0 = slt(a0, a3);
    if (v0 == 0) {
        // 0x0038a4a0
        charge(ctx, 1);
        a0 = a3;
    }
    // 0x0038a4a4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
}

// 0x0038A4B0 sub_38A4B0 -- 220 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [evtMessageKeyNumber] (work, key, out mes, out branch) -> 1 when the message key resolves: the message number is the
// low 12 bits of +16 (branch slot the top 4); +21 = 1..5 adds the offset sub_397580 gives (0xFFFF -> 0), 6 -> 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A4B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a4b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lh(v0, a1, key::kCmd);
    v0 = v0 & 0xFFF;
    sw(v0, a2, 0);
    lh(v0, a1, key::kCmd);
    v0 = sra(v0, 12);
    v0 = v0 & 0xF;
    sw(v0, a3, 0);
    lb(v0, a1, 21);
    at = sltiu(v0, 7);
    if (at != 0) {
        // 0x0038a4ec
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -21456);  // &0x7BAC30
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x38A508u:  // table[1, 2, 3, 4, 5]
            // 0x0038a508
            charge(ctx, 9);
            sh(zero, sp, 0x2E);
            lb(v0, a1, 21);
            a1 = addiu(v0, -1);
            a2 = addiu(sp, 0x2E);
            jal(ctx, 0x38A518u, gen::fn_sub_397580_00397580);
            v1 = 1;
            if (v0 != v1) {
                // 0x0038a55c
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x0038a52c
                charge(ctx, 4);
                lhu(v1, sp, 0x2E);
                v0 = 0xFFFF;
                if (v1 != v0) {
                    // 0x0038a548
                    charge(ctx, 5);
                    lw(v0, s0, 0);
                    v0 = addu(v0, v1);
                    sw(v0, s0, 0);
                L_0038a574:
                    charge(ctx, 1);
                    v0 = 1;
                } else {
                    // 0x0038a53c
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
            break;
        case 0x38A568u:  // table[6]
            // 0x0038a568
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x38A574u:  // table[0]
            goto L_0038a574;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0038a578 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    goto L_0038a574;
}

// 0x0038A590 sub_38A590 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtSaveCameraSlot] (work, slot): copies the camera model 0x1E59's 272-byte state into kCamSaves[slot] (slot < 3).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A590(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a590
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 7769;
    jal(ctx, 0x38A5ACu, gen::fn_sub_3B5D10_003b5d10);
    a3 = v0;
    at = slti(s0, 3);
    if (at != 0) {
        // 0x0038a5c4
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x0038a5cc
            charge(ctx, 6);
            v1 = sll(s0, 4);
            v1 = addu(v1, s0);
            v1 = sll(v1, 4);
            v1 = addu(v1, s1);
            a2 = addiu(v1, 808);
            a1 = 34;
            for (;;) {
                // 0x0038a5e4
                charge(ctx, 9);
                lw(a0, a3, 0);
                lw(v1, a3, 4);
                a3 = addiu(a3, 8);
                a1 = addiu(a1, -1);
                sw(a0, a2, 0);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0038a608 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038A620 sub_38A620 -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtRestoreCameraSlot] (work, slot): slot 2 only: copies kCamSave2 back into the camera model 0x1E59.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a620
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    a0 = 7769;
    jal(ctx, 0x38A63Cu, gen::fn_sub_3B5D10_003b5d10);
    a3 = v0;
    at = slti(s1, 3);
    if (at != 0) {
        // 0x0038a654
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x0038a65c
            charge(ctx, 3);
            v1 = 2;
            if (s1 == v1) {
                // 0x0038a668
                charge(ctx, 6);
                v1 = sll(s1, 4);
                v1 = addu(v1, s1);
                v1 = sll(v1, 4);
                v1 = addu(v1, s0);
                a2 = addiu(v1, 808);
                a1 = 34;
                for (;;) {
                    // 0x0038a680
                    charge(ctx, 9);
                    lw(a0, a2, 0);
                    lw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    a1 = addiu(a1, -1);
                    sw(a0, a3, 0);
                    sw(v1, a3, 4);
                    a3 = addiu(a3, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x0038a6a4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038A6C0 sub_38A6C0 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtSaveCamera] (work): the camera model 0x1E59 into kCamSaves[0], and kCamSelSaved = kCamSel.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A6C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a6c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 7769;
    jal(ctx, 0x38A6D4u, gen::fn_sub_3B5D10_003b5d10);
    a3 = v0;
    if (a3 != 0) {
        // 0x0038a6e8
        charge(ctx, 2);
        a2 = addiu(s0, 808);
        a1 = 34;
        for (;;) {
            // 0x0038a6f0
            charge(ctx, 9);
            lw(a0, a3, 0);
            lw(v1, a3, 4);
            a3 = addiu(a3, 8);
            a1 = addiu(a1, -1);
            sw(a0, a2, 0);
            sw(v1, a2, 4);
            a2 = addiu(a2, 8);
            if (i64(a1) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0038a714 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, s0, work::kCamSel);
    sw(v1, s0, work::kCamSelSaved);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0038A730 sub_38A730 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtRestoreCameraSel] (work): re-activates the saved camera selection (sub_3BB280) -> kCamSel.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A730(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038a730
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 7769;
    jal(ctx, 0x38A748u, gen::fn_sub_3B5D10_003b5d10);
    lw(s0, s1, work::kCamSelSaved);
    at = slti(s0, 2);
    if (at != 0) {
        // 0x0038a760
        charge(ctx, 3);
        v1 = 1;
        if (s0 == v1) {
            // 0x0038a790
            charge(ctx, 3);
            a0 = 7769;
            jal(ctx, 0x38A794u, gen::fn_sub_3BB280_003bb280);
        } else {
            // 0x0038a76c
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x0038a77c
                charge(ctx, 5);
                a0 = 7768;
                jal(ctx, 0x38A780u, gen::fn_sub_3BB280_003bb280);
            } else {
                // 0x0038a774
                charge(ctx, 2);
            }
        }
        // 0x0038a79c
        charge(ctx, 1);
        sw(s0, s1, work::kCamSel);
    }
    // 0x0038a7a0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038A900 sub_38A900 -- 32 bytes; leaf frame (no stack)
// [evtSpeedOf] (n) -> n + 2.0 as a float (move speed of a key).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38A900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0038a900
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x40000000;
    mtc1(v0, f1);
    mtc1(a0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
}

// 0x0038C460 sub_38C460 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtUnitCurrentKey] (unit, frame, out prev, out cur): cur = the first key whose frame + hold is after the frame,
// prev = the key before it (the tail when none); for types with conditions prev moves back past keys whose condition
// fails.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38C460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038c460
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    sw(zero, a2, 0);
    sw(zero, a3, 0);
    if (a0 != 0) {
        // 0x0038c480
        charge(ctx, 5);
        lh(a2, a0, unit::kHold);
        lw(v0, a0, unit::kKeyHead);
        sw(v0, a3, 0);
        for (;;) {
            // 0x0038c4b0
            charge(ctx, 3);
            lw(v0, a3, 0);
            if (v0 != 0) {
                backedge(ctx);
                // 0x0038c494
                charge(ctx, 5);
                lhu(v1, v0, 0);
                v1 = addu(v1, a2);
                at = slt(a1, v1);
                if (at == 0) {
                    // 0x0038c4a8
                    charge(ctx, 2);
                    lw(v0, v0, 76);
                    sw(v0, a3, 0);
                    continue;
                }
            }
            break;
        }
        // 0x0038c4bc
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0038c4d4
            charge(ctx, 2);
            lw(v0, a0, unit::kKeyTail);
            sw(v0, s0, 0);
        } else {
            // 0x0038c4c4
            charge(ctx, 4);
            lw(v0, v0, 80);
            sw(v0, s0, 0);
        }
        // 0x0038c4dc
        charge(ctx, 6);
        lw(a0, a0, unit::kType);
        jal(ctx, 0x38C4E0u, gen::fn_sub_36F500_0036f500);
        v1 = 1;
        if (v0 == v1) {
            // 0x0038c4f4
            charge(ctx, 2);
            for (;;) {
                // 0x0038c51c
                charge(ctx, 3);
                lw(a0, s0, 0);
                if (a0 != 0) {
                    backedge(ctx);
                    // 0x0038c4fc
                    charge(ctx, 5);
                    jal(ctx, 0x38C4FCu, gen::fn_sub_360ED0_00360ed0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x0038c510
                        charge(ctx, 3);
                        lw(v1, s0, 0);
                        lw(v1, v1, 80);
                        sw(v1, s0, 0);
                        continue;
                    }
                }
                break;
            }
        }
    }
    // 0x0038c528 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0038CA00 sub_38CA00 -- 128 bytes; leaf frame (no stack)
// [evtResetCameraSlots] (): the three 64-byte camera slots at 0x9588B0: mode 0, position 0, two vectors from the field
// constants 0x7CADD0 / 0x7CAFEC, the last word pair = 0x40DFF000 (7.0f, 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38CA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0038ca00
    enter(ctx, 8);  // entry check point + this block's cycles
    a2 = 0;
    a1 = 0x960000;
    a1 = addiu(a1, -30544);  // &0x9588B0
    lwc1(f1, gp, -32544);  // 0x7CADD0
    lwc1(f0, gp, -32004);  // 0x7CAFEC
    a0 = 0x40E00000;
    for (;;) {
        // 0x0038ca6c
        charge(ctx, 3);
        v1 = slti(a2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0038ca20
        charge(ctx, 19);
        v1 = sll(a2, 6);
        v1 = addu(a1, v1);
        swc1(f1, v1, 8);
        swc1(f1, v1, 12);
        swc1(f1, v1, 16);
        sw(zero, v1, 20);
        sw(zero, v1, 24);
        sw(zero, v1, 28);
        sw(zero, v1, 32);
        sw(zero, v1, 36);
        swc1(f0, v1, 40);
        swc1(f0, v1, 44);
        swc1(f0, v1, 48);
        sw(zero, v1, 52);
        sw(a0, v1, 56);
        sw(zero, v1, 60);
        sw(zero, v1, 0);
        sw(zero, v1, 4);
        a2 = addiu(a2, 1);
    }
    // 0x0038ca78
    charge(ctx, 2);
}

// 0x0038CA80 sub_38CA80 -- 400 bytes; frame 0x110: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtUpdateModelCameras] (work): for every field object, NPC and type-12 model (at most 50), its resource backup
// (kResources, matched by model id) and sub_38CC10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38CA80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038ca80
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 0;
    s1 = 0;
    a0 = 3;
    jal(ctx, 0x38CAA4u, gen::fn_sub_3B5DF0_003b5df0);
    s0 = addu(s0, v0);
    a0 = 1;
    jal(ctx, 0x38CAB4u, gen::fn_sub_3B5DF0_003b5df0);
    s0 = addu(s0, v0);
    a0 = 12;
    jal(ctx, 0x38CAC4u, gen::fn_sub_3B5DF0_003b5df0);
    s0 = addu(s0, v0);
    at = slti(s0, 51);
    if (at != 0) {
        // 0x0038cadc
        charge(ctx, 5);
        a0 = 3;
        jal(ctx, 0x38CAE0u, gen::fn_sub_3B5D50_003b5d50);
        for (;;) {
            // 0x0038cb04
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038caf0
            charge(ctx, 5);
            v1 = sll(s1, 2);
            v1 = addu(v1, sp);
            sw(v0, v1, 64);
            s1 = addiu(s1, 1);
            lw(v0, v0, 248);
        }
        // 0x0038cb0c
        charge(ctx, 5);
        a0 = 1;
        jal(ctx, 0x38CB10u, gen::fn_sub_3B5D50_003b5d50);
        for (;;) {
            // 0x0038cb34
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038cb20
            charge(ctx, 5);
            v1 = sll(s1, 2);
            v1 = addu(v1, sp);
            sw(v0, v1, 64);
            s1 = addiu(s1, 1);
            lw(v0, v0, 248);
        }
        // 0x0038cb3c
        charge(ctx, 6);
        a0 = 12;
        jal(ctx, 0x38CB40u, gen::fn_sub_3B5D50_003b5d50);
        a0 = v0;
        for (;;) {
            // 0x0038cb68
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038cb54
            charge(ctx, 5);
            v1 = sll(s1, 2);
            v1 = addu(v1, sp);
            sw(a0, v1, 64);
            s1 = addiu(s1, 1);
            lw(a0, a0, 248);
        }
        // 0x0038cb70
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x0038cbe8
            charge(ctx, 3);
            v1 = slt(s1, s0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038cb7c
            charge(ctx, 9);
            v0 = sll(s1, 2);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 64);
            lw(a1, v0, 0);
            lhu(a3, a1, 0);
            lw(a0, s2, work::kResCount);
            t0 = 0;
            for (;;) {
                // 0x0038cbc8
                charge(ctx, 3);
                v0 = slt(t0, a0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0038cba0
                charge(ctx, 7);
                v1 = sll(t0, 2);
                lw(v0, s2, work::kResources);
                v0 = addu(v0, v1);
                lw(a2, v0, 0);
                lhu(v0, a2, 0);
                if (v0 == a3) {
                    goto L_0038cbbc_13;
                }
                // 0x0038cbc4
                charge(ctx, 1);
                t0 = addiu(t0, 1);
            }
            // 0x0038cbd4
            charge(ctx, 1);
            a2 = 0;
        L_0038cbd8:
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x38CBDCu, gen::fn_sub_38CC10_0038cc10);
            s1 = addiu(s1, 1);
        }
    }
    // 0x0038cbf4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
    return;
L_0038cbbc_13:
    charge(ctx, 2);
    goto L_0038cbd8;
}

// 0x0038CC10 sub_38CC10 -- 2372 bytes; frame 0x130: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [evtModelApplyCameraSlot] (work, model, backup, id): picks the camera slot driving this model (mode 3 following it,
// else mode 2, else mode 1) and writes its light / view vectors and a fresh matrix (sub_4C31B0 with 0x6A2A70 /
// 0x6A2A60) into the model (+256.. for kind 12, +300.. for kinds 1 / 3); with no slot, restores the backup (kind 3 also
// the field camera kFieldCam).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38CC10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0038cc10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = si(-1);
    s0 = 0;
    if (s3 != 0) {
        // 0x0038cc4c
        charge(ctx, 8);
        lhu(a0, s3, 0);
        v1 = 0xF0000;
        v1 = v1 | 0xFC00;
        v1 = a0 & v1;
        a1 = sra(v1, 10);
        v1 = 3;
        if (a1 == v1) {
            // 0x0038cc74
            charge(ctx, 3);
            a1 = 0;
            jal(ctx, 0x38CC78u, gen::fn_sub_1A0430_001a0430);
        } else {
            // 0x0038cc6c
            charge(ctx, 2);
        }
        // 0x0038cc80
        charge(ctx, 6);
        a3 = 0;
        a2 = 0x960000;
        a2 = addiu(a2, -30544);  // &0x9588B0
        a1 = 3;
        for (;;) {
            // 0x0038ccf0
            charge(ctx, 3);
            v1 = slti(a3, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038cc98
            charge(ctx, 5);
            v1 = sll(a3, 6);
            a0 = addu(a2, v1);
            lw(v1, a0, 0);
            if (v1 == a1) {
                // 0x0038ccac
                charge(ctx, 3);
                lw(v1, a0, 4);
                if (v1 != s3) {
                    goto L_0038ccec;
                }
                goto L_0038ccb8_7;
            }
        L_0038ccec:
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
    L_0038ccfc:
        charge(ctx, 3);
        v1 = si(-1);
        if (s1 == v1) {
            // 0x0038cd08
            charge(ctx, 8);
            lhu(a0, s3, 0);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 12;
            if (a0 != v1) {
                // 0x0038cd28
                charge(ctx, 6);
                a2 = 0;
                a1 = 0x960000;
                a1 = addiu(a1, -30544);  // &0x9588B0
                a0 = 2;
                for (;;) {
                    // 0x0038cd64
                    charge(ctx, 3);
                    v1 = slti(a2, 3);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0038cd40
                    charge(ctx, 5);
                    v1 = sll(a2, 6);
                    v1 = addu(a1, v1);
                    lw(v1, v1, 0);
                    if (v1 == a0) {
                        goto L_0038cd54_15;
                    }
                    // 0x0038cd60
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
            }
        }
    L_0038cd70:
        charge(ctx, 3);
        v1 = si(-1);
        if (s1 == v1) {
            // 0x0038cd7c
            charge(ctx, 6);
            a2 = 0;
            a1 = 0x960000;
            a1 = addiu(a1, -30544);  // &0x9588B0
            a0 = 1;
            for (;;) {
                // 0x0038cdb8
                charge(ctx, 3);
                v1 = slti(a2, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0038cd94
                charge(ctx, 5);
                v1 = sll(a2, 6);
                v1 = addu(a1, v1);
                lw(v1, v1, 0);
                if (v1 == a0) {
                    goto L_0038cda8_21;
                }
                // 0x0038cdb4
                charge(ctx, 1);
                a2 = addiu(a2, 1);
            }
        }
    L_0038cdc4:
        charge(ctx, 3);
        v1 = si(-1);
        if (s1 != v1) {
            // 0x0038d010
            charge(ctx, 8);
            a0 = sll(s1, 6);
            v1 = 0x960000;
            v1 = addiu(v1, -30544);  // &0x9588B0
            v1 = addu(v1, a0);
            lw(a0, v1, 0);
            v1 = 2;
            if (a0 != v1) {
                // 0x0038d030
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    goto L_0038d03c;
                }
                goto L_0038d060;
            }
        L_0038d03c:
            charge(ctx, 8);
            lhu(a0, s3, 0);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 3;
            if (a0 == v1) {
                // 0x0038d05c
                charge(ctx, 1);
                s0 = 1;
            }
        L_0038d060:
            charge(ctx, 8);
            lhu(a0, s3, 0);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 3;
            if (a0 != v1) {
                // 0x0038d274
                charge(ctx, 3);
                a2 = 1;
                if (a0 != a2) {
                    // 0x0038d3d4
                    charge(ctx, 3);
                    v1 = 12;
                    if (a0 == v1) {
                        // 0x0038d3e0
                        charge(ctx, 74);
                        v1 = sll(s1, 6);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30504);  // &0x9588D8
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 256);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30500);  // &0x9588DC
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 260);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30496);  // &0x9588E0
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 264);
                        sw(zero, s3, 268);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30536);  // &0x9588B8
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 272);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30532);  // &0x9588BC
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 276);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30528);  // &0x9588C0
                        v0 = addu(v0, v1);
                        lwc1(f0, v0, 0);
                        swc1(f0, s3, 280);
                        sw(zero, s3, 284);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30520);  // &0x9588C8
                        v0 = addu(v0, v1);
                        lwc1(f20, v0, 0);
                        v0 = 0x960000;
                        v0 = addiu(v0, -30516);  // &0x9588CC
                        v0 = addu(v0, v1);
                        lwc1(f12, v0, 0);
                        v0 = 0x3F800000;
                        sw(v0, sp, 0x98);
                        sw(v0, sp, 0x84);
                        sw(v0, sp, 0x70);
                        sw(zero, sp, 0x80);
                        sw(zero, sp, 0x78);
                        sw(zero, sp, 0x74);
                        sw(zero, sp, 0x94);
                        sw(zero, sp, 0x90);
                        sw(zero, sp, 0x88);
                        sw(zero, sp, 0xA8);
                        sw(zero, sp, 0xA4);
                        sw(zero, sp, 0xA0);
                        lw(v1, sp, 0x7C);
                        v0 = 0x20000;
                        v0 = v0 | 0x3;
                        v0 = v1 | v0;
                        sw(v0, sp, 0x7C);
                        a0 = addiu(sp, 0x70);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 10864);  // &0x6A2A70
                        jal(ctx, 0x38D4D8u, gen::fn_sub_4C31B0_004c31b0);
                        a0 = addiu(sp, 0x70);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 10848);  // &0x6A2A60
                        mov_s(f12, f20);
                        a2 = 1;
                        jal(ctx, 0x38D4F4u, gen::fn_sub_4C31B0_004c31b0);
                        a3 = addiu(sp, 0x70);
                        a2 = addiu(s3, 288);
                        a1 = 8;
                        for (;;) {
                            // 0x0038d508
                            charge(ctx, 9);
                            lw(a0, a3, 0);
                            lw(v1, a3, 4);
                            a3 = addiu(a3, 8);
                            a1 = addiu(a1, -1);
                            sw(a0, a2, 0);
                            sw(v1, a2, 4);
                            a2 = addiu(a2, 8);
                            if (i64(a1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                } else {
                    // 0x0038d280
                    charge(ctx, 74);
                    v1 = sll(s1, 6);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30504);  // &0x9588D8
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 300);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30500);  // &0x9588DC
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 304);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30496);  // &0x9588E0
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 308);
                    sw(zero, s3, 312);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30536);  // &0x9588B8
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 316);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30532);  // &0x9588BC
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 320);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30528);  // &0x9588C0
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, 0);
                    swc1(f0, s3, 324);
                    sw(zero, s3, 328);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30520);  // &0x9588C8
                    v0 = addu(v0, v1);
                    lwc1(f20, v0, 0);
                    v0 = 0x960000;
                    v0 = addiu(v0, -30516);  // &0x9588CC
                    v0 = addu(v0, v1);
                    lwc1(f12, v0, 0);
                    v0 = 0x3F800000;
                    sw(v0, sp, 0xD8);
                    sw(v0, sp, 0xC4);
                    sw(v0, sp, 0xB0);
                    sw(zero, sp, 0xC0);
                    sw(zero, sp, 0xB8);
                    sw(zero, sp, 0xB4);
                    sw(zero, sp, 0xD4);
                    sw(zero, sp, 0xD0);
                    sw(zero, sp, 0xC8);
                    sw(zero, sp, 0xE8);
                    sw(zero, sp, 0xE4);
                    sw(zero, sp, 0xE0);
                    lw(v1, sp, 0xBC);
                    v0 = 0x20000;
                    v0 = v0 | 0x3;
                    v0 = v1 | v0;
                    sw(v0, sp, 0xBC);
                    a0 = addiu(sp, 0xB0);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 10864);  // &0x6A2A70
                    jal(ctx, 0x38D378u, gen::fn_sub_4C31B0_004c31b0);
                    a0 = addiu(sp, 0xB0);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 10848);  // &0x6A2A60
                    mov_s(f12, f20);
                    a2 = 1;
                    jal(ctx, 0x38D394u, gen::fn_sub_4C31B0_004c31b0);
                    a3 = addiu(sp, 0xB0);
                    a2 = addiu(s3, 336);
                    a1 = 8;
                    for (;;) {
                        // 0x0038d3a8
                        charge(ctx, 9);
                        lw(a0, a3, 0);
                        lw(v1, a3, 4);
                        a3 = addiu(a3, 8);
                        a1 = addiu(a1, -1);
                        sw(a0, a2, 0);
                        sw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0038d3cc
                    charge(ctx, 2);
                }
            } else {
                // 0x0038d080
                charge(ctx, 75);
                v1 = sll(s1, 6);
                v0 = 0x960000;
                v0 = addiu(v0, -30504);  // &0x9588D8
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 300);
                v0 = 0x960000;
                v0 = addiu(v0, -30500);  // &0x9588DC
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 304);
                v0 = 0x960000;
                v0 = addiu(v0, -30496);  // &0x9588E0
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 308);
                sw(zero, s3, 312);
                v0 = 0x960000;
                v0 = addiu(v0, -30536);  // &0x9588B8
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 316);
                v0 = 0x960000;
                v0 = addiu(v0, -30532);  // &0x9588BC
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 320);
                v0 = 0x960000;
                v0 = addiu(v0, -30528);  // &0x9588C0
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 324);
                sw(zero, s3, 328);
                v0 = 0x960000;
                v0 = addiu(v0, -30520);  // &0x9588C8
                v0 = addu(v0, v1);
                lwc1(f20, v0, 0);
                v0 = 0x960000;
                v0 = addiu(v0, -30516);  // &0x9588CC
                v0 = addu(v0, v1);
                lwc1(f12, v0, 0);
                v0 = 0x3F800000;
                sw(v0, sp, 0x118);
                sw(v0, sp, 0x104);
                sw(v0, sp, 0xF0);
                sw(zero, sp, 0x100);
                sw(zero, sp, 0xF8);
                sw(zero, sp, 0xF4);
                sw(zero, sp, 0x114);
                sw(zero, sp, 0x110);
                sw(zero, sp, 0x108);
                sw(zero, sp, 0x128);
                sw(zero, sp, 0x124);
                sw(zero, sp, 0x120);
                lw(v1, sp, 0xFC);
                v0 = 0x20000;
                v0 = v0 | 0x3;
                v0 = v1 | v0;
                sw(v0, sp, 0xFC);
                a0 = addiu(sp, 0xF0);
                a1 = 0x6A0000;
                a1 = addiu(a1, 10864);  // &0x6A2A70
                a2 = 1;
                jal(ctx, 0x38D17Cu, gen::fn_sub_4C31B0_004c31b0);
                a0 = addiu(sp, 0xF0);
                a1 = 0x6A0000;
                a1 = addiu(a1, 10848);  // &0x6A2A60
                mov_s(f12, f20);
                a2 = 1;
                jal(ctx, 0x38D198u, gen::fn_sub_4C31B0_004c31b0);
                a3 = addiu(sp, 0xF0);
                a2 = addiu(s3, 336);
                a1 = 8;
                for (;;) {
                    // 0x0038d1ac
                    charge(ctx, 9);
                    lw(a0, a3, 0);
                    lw(v1, a3, 4);
                    a3 = addiu(a3, 8);
                    a1 = addiu(a1, -1);
                    sw(a0, a2, 0);
                    sw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0038d1d0
                charge(ctx, 3);
                v1 = 1;
                if (s0 == v1) {
                    // 0x0038d1dc
                    charge(ctx, 27);
                    jal(ctx, 0x38D1DCu, gen::fn_sub_1A0D00_001a0d00);
                    s1 = v0;
                    jal(ctx, 0x38D1E8u, gen::fn_sub_1A0D40_001a0d40);
                    s0 = v0;
                    jal(ctx, 0x38D1F4u, gen::fn_sub_1A0D80_001a0d80);
                    a3 = v0;
                    lwc1(f3, s3, 300);
                    lwc1(f2, s3, 304);
                    lwc1(f1, s3, 308);
                    lwc1(f0, s3, 312);
                    swc1(f3, s1, 0);
                    swc1(f2, s1, 4);
                    swc1(f1, s1, 8);
                    swc1(f0, s1, 12);
                    lwc1(f3, s3, 316);
                    lwc1(f2, s3, 320);
                    lwc1(f1, s3, 324);
                    lwc1(f0, s3, 328);
                    swc1(f3, s0, 0);
                    swc1(f2, s0, 4);
                    swc1(f1, s0, 8);
                    swc1(f0, s0, 12);
                    a2 = addiu(s3, 336);
                    a1 = 8;
                    for (;;) {
                        // 0x0038d248
                        charge(ctx, 9);
                        lw(a0, a2, 0);
                        lw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        a1 = addiu(a1, -1);
                        sw(a0, a3, 0);
                        sw(v1, a3, 4);
                        a3 = addiu(a3, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0038d26c
                    charge(ctx, 2);
                }
            }
        } else {
            // 0x0038cdd0
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x0038cdd8
                charge(ctx, 8);
                lhu(a0, s3, 0);
                v1 = 0xF0000;
                v1 = v1 | 0xFC00;
                v1 = a0 & v1;
                a0 = sra(v1, 10);
                v1 = 12;
                if (a0 == v1) {
                    // 0x0038cf98
                    charge(ctx, 19);
                    lwc1(f3, s2, 256);
                    lwc1(f2, s2, 260);
                    lwc1(f1, s2, 264);
                    lwc1(f0, s2, 268);
                    swc1(f3, s3, 256);
                    swc1(f2, s3, 260);
                    swc1(f1, s3, 264);
                    swc1(f0, s3, 268);
                    lwc1(f3, s2, 272);
                    lwc1(f2, s2, 276);
                    lwc1(f1, s2, 280);
                    lwc1(f0, s2, 284);
                    swc1(f3, s3, 272);
                    swc1(f2, s3, 276);
                    swc1(f1, s3, 280);
                    swc1(f0, s3, 284);
                    a3 = addiu(s2, 288);
                    a2 = addiu(s3, 288);
                    a1 = 8;
                    for (;;) {
                        // 0x0038cfe4
                        charge(ctx, 9);
                        lw(a0, a3, 0);
                        lw(v1, a3, 4);
                        a3 = addiu(a3, 8);
                        a1 = addiu(a1, -1);
                        sw(a0, a2, 0);
                        sw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x0038cdf8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0038cf20
                        charge(ctx, 19);
                        lwc1(f3, s2, 300);
                        lwc1(f2, s2, 304);
                        lwc1(f1, s2, 308);
                        lwc1(f0, s2, 312);
                        swc1(f3, s3, 300);
                        swc1(f2, s3, 304);
                        swc1(f1, s3, 308);
                        swc1(f0, s3, 312);
                        lwc1(f3, s2, 316);
                        lwc1(f2, s2, 320);
                        lwc1(f1, s2, 324);
                        lwc1(f0, s2, 328);
                        swc1(f3, s3, 316);
                        swc1(f2, s3, 320);
                        swc1(f1, s3, 324);
                        swc1(f0, s3, 328);
                        a3 = addiu(s2, 336);
                        a2 = addiu(s3, 336);
                        a1 = 8;
                        for (;;) {
                            // 0x0038cf6c
                            charge(ctx, 9);
                            lw(a0, a3, 0);
                            lw(v1, a3, 4);
                            a3 = addiu(a3, 8);
                            a1 = addiu(a1, -1);
                            sw(a0, a2, 0);
                            sw(v1, a2, 4);
                            a2 = addiu(a2, 8);
                            if (i64(a1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0038cf90
                        charge(ctx, 2);
                    } else {
                        // 0x0038ce04
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 == v1) {
                            // 0x0038ce18
                            charge(ctx, 19);
                            lwc1(f3, s2, 300);
                            lwc1(f2, s2, 304);
                            lwc1(f1, s2, 308);
                            lwc1(f0, s2, 312);
                            swc1(f3, s3, 300);
                            swc1(f2, s3, 304);
                            swc1(f1, s3, 308);
                            swc1(f0, s3, 312);
                            lwc1(f3, s2, 316);
                            lwc1(f2, s2, 320);
                            lwc1(f1, s2, 324);
                            lwc1(f0, s2, 328);
                            swc1(f3, s3, 316);
                            swc1(f2, s3, 320);
                            swc1(f1, s3, 324);
                            swc1(f0, s3, 328);
                            a2 = addiu(s2, 336);
                            a1 = addiu(s3, 336);
                            a0 = 8;
                            for (;;) {
                                // 0x0038ce64
                                charge(ctx, 9);
                                lw(v1, a2, 0);
                                lw(v0, a2, 4);
                                a2 = addiu(a2, 8);
                                a0 = addiu(a0, -1);
                                sw(v1, a1, 0);
                                sw(v0, a1, 4);
                                a1 = addiu(a1, 8);
                                if (i64(a0) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0038ce88
                            charge(ctx, 27);
                            jal(ctx, 0x38CE88u, gen::fn_sub_1A0D00_001a0d00);
                            s1 = v0;
                            jal(ctx, 0x38CE94u, gen::fn_sub_1A0D40_001a0d40);
                            s0 = v0;
                            jal(ctx, 0x38CEA0u, gen::fn_sub_1A0D80_001a0d80);
                            a3 = v0;
                            lwc1(f3, s4, work::kFieldCam);
                            lwc1(f2, s4, 2164);
                            lwc1(f1, s4, 2168);
                            lwc1(f0, s4, 2172);
                            swc1(f3, s1, 0);
                            swc1(f2, s1, 4);
                            swc1(f1, s1, 8);
                            swc1(f0, s1, 12);
                            lwc1(f3, s4, 2176);
                            lwc1(f2, s4, 2180);
                            lwc1(f1, s4, 2184);
                            lwc1(f0, s4, 2188);
                            swc1(f3, s0, 0);
                            swc1(f2, s0, 4);
                            swc1(f1, s0, 8);
                            swc1(f0, s0, 12);
                            a2 = addiu(s4, 2192);
                            a1 = 8;
                            for (;;) {
                                // 0x0038cef4
                                charge(ctx, 9);
                                lw(a0, a2, 0);
                                lw(v1, a2, 4);
                                a2 = addiu(a2, 8);
                                a1 = addiu(a1, -1);
                                sw(a0, a3, 0);
                                sw(v1, a3, 4);
                                a3 = addiu(a3, 8);
                                if (i64(a1) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0038cf18
                            charge(ctx, 2);
                        } else {
                            // 0x0038ce10
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0038d008
            charge(ctx, 2);
        }
    }
    // 0x0038d52c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x130);
    return;
L_0038ccb8_7:
    charge(ctx, 8);
    s1 = a3;
    lhu(a0, s3, 0);
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    v1 = sra(v1, 10);
    if (v1 == a1) {
        // 0x0038ccd8
        charge(ctx, 5);
        a1 = 1;
        jal(ctx, 0x38CCDCu, gen::fn_sub_1A0430_001a0430);
    }
    goto L_0038ccfc;
L_0038cd54_15:
    charge(ctx, 3);
    s1 = a2;
    goto L_0038cd70;
L_0038cda8_21:
    charge(ctx, 3);
    s1 = a2;
    goto L_0038cdc4;
}

// 0x0038D560 sub_38D560 -- 328 bytes; leaf frame (no stack)
// [evtSetCameraSlot] (slot, mode, model, a[3], b[4], c[3]): fills camera slot `slot` (< 3) at 0x9588B0: vectors b / c
// / a, the mode, the followed model for mode 3.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    Fpr f0{ctx, 0};
    // 0x0038d560
    enter(ctx, 3);  // entry check point + this block's cycles
    at = slti(a0, 3);
    if (at != 0) {
        // 0x0038d56c
        charge(ctx, 67);
        v1 = sll(a0, 6);
        lwc1(f0, a3, 0);
        a0 = 0x960000;
        a0 = addiu(a0, -30536);  // &0x9588B8
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, a3, 4);
        a0 = 0x960000;
        a0 = addiu(a0, -30532);  // &0x9588BC
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, a3, 8);
        a0 = 0x960000;
        a0 = addiu(a0, -30528);  // &0x9588C0
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        a0 = 0x960000;
        a0 = addiu(a0, -30524);  // &0x9588C4
        a0 = addu(a0, v1);
        sw(zero, a0, 0);
        lwc1(f0, t0, 0);
        a0 = 0x960000;
        a0 = addiu(a0, -30520);  // &0x9588C8
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t0, 4);
        a0 = 0x960000;
        a0 = addiu(a0, -30516);  // &0x9588CC
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t0, 8);
        a0 = 0x960000;
        a0 = addiu(a0, -30512);  // &0x9588D0
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t0, 12);
        a0 = 0x960000;
        a0 = addiu(a0, -30508);  // &0x9588D4
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t1, 0);
        a0 = 0x960000;
        a0 = addiu(a0, -30504);  // &0x9588D8
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t1, 4);
        a0 = 0x960000;
        a0 = addiu(a0, -30500);  // &0x9588DC
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        lwc1(f0, t1, 8);
        a0 = 0x960000;
        a0 = addiu(a0, -30496);  // &0x9588E0
        a0 = addu(a0, v1);
        swc1(f0, a0, 0);
        a3 = 0x3F800000;
        a0 = 0x960000;
        a0 = addiu(a0, -30492);  // &0x9588E4
        a0 = addu(a0, v1);
        sw(a3, a0, 0);
        a0 = 0x960000;
        a0 = addiu(a0, -30544);  // &0x9588B0
        a0 = addu(a0, v1);
        sw(a1, a0, 0);
        a0 = 3;
        if (a1 != a0) {
            // 0x0038d690
            charge(ctx, 4);
            a0 = 0x960000;
            a0 = addiu(a0, -30540);  // &0x9588B4
            v1 = addu(a0, v1);
            sw(zero, v1, 0);
        } else {
            // 0x0038d678
            charge(ctx, 6);
            a0 = 0x960000;
            a0 = addiu(a0, -30540);  // &0x9588B4
            v1 = addu(a0, v1);
            sw(a2, v1, 0);
        }
    }
    // 0x0038d6a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0038D6B0 sub_38D6B0 -- 52 bytes; leaf frame (no stack)
// [evtSetCounter] (n, value): event counter n (< 10) = g_scrGlobals + 800 + 4n.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D6B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0038d6b0
    enter(ctx, 3);  // entry check point + this block's cycles
    at = slti(a0, 10);
    if (at != 0) {
        // 0x0038d6bc
        charge(ctx, 2);
        if (i64(a0) < 0) {
            goto L_0038d6c4;
        }
        // 0x0038d6cc
        charge(ctx, 4);
        a0 = sll(a0, 2);
        lw(v1, gp, -25236);  // g_scrGlobalsPtr
        v1 = addu(v1, a0);
        sw(a1, v1, 800);
        // 0x0038d6dc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0038d6c4:
    charge(ctx, 2);
    // 0x0038d6dc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0038D6F0 sub_38D6F0 -- 48 bytes; leaf frame (no stack)
// [evtGetCounter] (n) -> event counter n, -1 for n >= 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0038d6f0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = slti(a0, 10);
    if (v0 != 0) {
        // 0x0038d708
        charge(ctx, 4);
        v1 = sll(a0, 2);
        lw(v0, gp, -25236);  // g_scrGlobalsPtr
        v0 = addu(v0, v1);
        lw(v0, v0, 800);
    } else {
        // 0x0038d6fc
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x0038d718 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0038D720 sub_38D720 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtReleaseSounds] (work): releases each of kSeCount entries kSeIds from the scene's sound bank (scene +288,
// sub_3952C0); clears the count.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038d720
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        // 0x0038d760
        charge(ctx, 4);
        lw(v1, s1, work::kSeCount);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0038d740
        charge(ctx, 8);
        lw(v1, s1, work::kScene);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        lw(a0, v1, 288);
        lw(a1, v0, 688);
        jal(ctx, 0x38D754u, gen::fn_sub_3952C0_003952c0);
        s0 = addiu(s0, 1);
    }
    // 0x0038d770
    charge(ctx, 7);
    sw(zero, s1, work::kSeCount);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038D790 sub_38D790 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtKeyAllocPath] (key): allocates the key's 304-byte path (class 10) when it has none (asserted, line 4705).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038d790
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, a0, key::kPath);
    if (v1 == 0) {
        // 0x0038d7b0
        charge(ctx, 10);
        a0 = 1;
        a1 = 304;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x38D7C4u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x0038d7d8
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 2576);  // "mt_evtMisc.c"
            a1 = 59;
            jal(ctx, 0x38D7E4u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0038d7ec
        charge(ctx, 7);
        a0 = 10;
        a1 = 304;
        jal(ctx, 0x38D7F4u, gen::fn_sub_386C40_00386c40);
        sw(s0, s1, key::kPath);
        if (s0 == 0) {
            // 0x0038d808
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 2576);  // "mt_evtMisc.c"
            a1 = 4705;
            jal(ctx, 0x38D814u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x0038d81c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038D840 sub_38D840 -- 196 bytes; leaf frame (no stack)
// [evtCopyPath] (src, dst, reverse): copies an unpacked path (src[0] == 0): the point count byte and 3n + 1 points of 12
// bytes, in reverse order when reverse == 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D840(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0038d840
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v1, a0, 0);
    if (v1 == 0) {
        // 0x0038d84c
        charge(ctx, 10);
        lbu(a3, a0, 1);
        v1 = sll(a3, 1);
        v1 = addu(v1, a3);
        t2 = addiu(v1, 1);
        sb(a3, a1, 0);
        t3 = 0;
        t1 = 1;
        t0 = addiu(t2, -1);
        for (;;) {
            // 0x0038d8f0
            charge(ctx, 3);
            v1 = slt(t3, t2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038d874
            charge(ctx, 2);
            if (a2 != t1) {
                // 0x0038d8c0
                charge(ctx, 11);
                v1 = sll(t3, 1);
                v1 = addu(v1, t3);
                v1 = sll(v1, 2);
                a3 = addu(a0, v1);
                v1 = addu(a1, v1);
                lwc1(f2, a3, 4);
                lwc1(f1, a3, 8);
                lwc1(f0, a3, 12);
                swc1(f2, v1, 4);
                swc1(f1, v1, 8);
                swc1(f0, v1, 12);
            } else {
                // 0x0038d87c
                charge(ctx, 17);
                a3 = subu(t0, t3);
                v1 = sll(a3, 1);
                v1 = addu(v1, a3);
                v1 = sll(v1, 2);
                a3 = addu(a0, v1);
                v1 = sll(t3, 1);
                v1 = addu(v1, t3);
                v1 = sll(v1, 2);
                v1 = addu(a1, v1);
                lwc1(f2, a3, 4);
                lwc1(f1, a3, 8);
                lwc1(f0, a3, 12);
                swc1(f2, v1, 4);
                swc1(f1, v1, 8);
                swc1(f0, v1, 12);
            }
            // 0x0038d8ec
            charge(ctx, 1);
            t3 = addiu(t3, 1);
        }
    }
    // 0x0038d8fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0038D910 sub_38D910 -- 112 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [evtNpcHideIfAbsent] (model): when sub_31B680 says the NPC (model +296: +212 / +214) is not present today, hides it
// (sub_3B9500(model, 0)).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038d910
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, sp, 0x2C);
    sw(zero, sp, 0x28);
    lw(v0, a0, 296);
    lhu(a0, v0, 212);
    lhu(a1, v0, 214);
    a2 = addiu(sp, 0x2C);
    a3 = addiu(sp, 0x28);
    jal(ctx, 0x38D93Cu, gen::fn_sub_31B680_0031b680);
    v1 = 1;
    if (v0 == v1) {
        // 0x0038d950
        charge(ctx, 3);
        lw(v1, sp, 0x2C);
        if (v1 == 0) {
            // 0x0038d95c
            charge(ctx, 4);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x38D964u, gen::fn_sub_3B9500_003b9500);
        }
    }
    // 0x0038d96c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0038D980 sub_38D980 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 0x0B8 (1 argument; mt_evtMisc.c) [scrEvt_GetCounter]: returns event counter arg0 (g_scrGlobals + 800 + 4 *
// arg0, the same counters as sub_38D6F0) in the return register; arg0 >= 10 asserts (line 4850) and returns -1.
// Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38D980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038d980
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x38D990u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    v0 = slti(s0, 10);
    if (v0 == 0) {
        // 0x0038d9a8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 2576);  // "mt_evtMisc.c"
        a1 = 4850;
        jal(ctx, 0x38D9B4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0038d9bc
    charge(ctx, 3);
    v0 = slti(s0, 10);
    if (v0 != 0) {
        // 0x0038d9d4
        charge(ctx, 4);
        v1 = sll(s0, 2);
        lw(v0, gp, -25236);  // g_scrGlobalsPtr
        v0 = addu(v0, v1);
        lw(a0, v0, 800);
    } else {
        // 0x0038d9c8
        charge(ctx, 3);
        a0 = si(-1);
    }
    // 0x0038d9e4
    charge(ctx, 8);
    jal(ctx, 0x38D9E4u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0038DA10 sub_38DA10 -- 192 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [evtKeyHasPath] (key) -> 1 for keys that carry a path: type-41 keys with command 0 or 5, model keys (types 1 / 48)
// with command 1 and mode 1 ("unit path frameno =%d"); else 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38DA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038da10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, key::kOwnerType);
    v0 = 41;
    if (v1 == v0) {
        // 0x0038da88
        charge(ctx, 3);
        lb(v1, s0, key::kCmd);
        if (v1 != 0) {
            // 0x0038daa0
            charge(ctx, 3);
            v0 = 5;
            if (v1 != v0) {
            L_0038dab8:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0038daac
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x0038da94
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0038da30
        charge(ctx, 3);
        v0 = 48;
        if (v1 != v0) {
            // 0x0038da3c
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0038da50;
            }
            // 0x0038da48
            charge(ctx, 2);
            goto L_0038dab8;
        }
    L_0038da50:
        charge(ctx, 9);
        lhu(a1, s0, key::kFrame);
        a0 = 0x6A0000;
        a0 = addiu(a0, 2752);  // "unit path frameno =%d\n"
        jal(ctx, 0x38DA5Cu, gen::fn_printf_005225a8);
        lb(v1, s0, key::kCmd);
        v0 = 1;
        if (v1 != v0) {
            goto L_0038dab8;
        }
        // 0x0038da74
        charge(ctx, 3);
        lb(v1, s0, key::kArg20);
        if (v1 != v0) {
            goto L_0038dab8;
        }
        // 0x0038da80
        charge(ctx, 2);
    }
    // 0x0038dabc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0038F0F0 sub_38F0F0 -- 840 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateFieldUnits] (work): with a stage, creates a type-1 unit for the player (model 0x400) and one per NPC
// (sub_3B5550 / sub_3B5430 lists; "npc unit no=%d") with their current pose, colour (sub_318B00) and presence
// (sub_38D910) as the setup values ("x=%d y=%d z=%d" via fptodp), and saves the field camera (type-5 object) into
// kFieldCam.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38F0F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x0038f0f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    jal(ctx, 0x38F11Cu, gen::fn_sub_3B5D00_003b5d00);
    s2 = v0;
    if (s2 != 0) {
        // 0x0038f130
        charge(ctx, 6);
        a0 = 1024;
        jal(ctx, 0x38F134u, gen::fn_sub_3B5D10_003b5d10);
        s1 = v0;
        if (s1 == 0) {
            // 0x0038f228
            charge(ctx, 9);
            a0 = 1;
            a1 = s5;
            jal(ctx, 0x38F230u, gen::fn_sub_361CA0_00361ca0);
            a0 = v0;
            a1 = 1024;
            a2 = 0;
            jal(ctx, 0x38F244u, gen::fn_sub_361D60_00361d60);
        } else {
            // 0x0038f148
            charge(ctx, 56);
            a0 = 1;
            a1 = s5;
            jal(ctx, 0x38F150u, gen::fn_sub_361CA0_00361ca0);
            s0 = v0;
            a0 = s0;
            a1 = 1024;
            a2 = s1;
            jal(ctx, 0x38F168u, gen::fn_sub_361D60_00361d60);
            v0 = si(-1);
            sw(v0, s0, unit::kName);
            sw(zero, s0, 20);
            lwc1(f2, s1, 4);
            lwc1(f1, s1, 8);
            lwc1(f0, s1, 12);
            swc1(f2, s0, unit::kPos);
            swc1(f1, s0, 64);
            swc1(f0, s0, 68);
            lwc1(f2, s1, 16);
            lwc1(f1, s1, 20);
            lwc1(f0, s1, 24);
            swc1(f2, s0, unit::kRot);
            swc1(f1, s0, 76);
            swc1(f0, s0, 80);
            lwc1(f12, s1, 4);
            jal(ctx, 0x38F1B0u, gen::fn_fptodp_00530da0);
            s4 = v0;
            lwc1(f12, s1, 8);
            jal(ctx, 0x38F1C0u, gen::fn_fptodp_00530da0);
            s3 = v0;
            lwc1(f12, s1, 12);
            jal(ctx, 0x38F1D0u, gen::fn_fptodp_00530da0);
            a0 = 0x6A0000;
            a0 = addiu(a0, 3024);  // "x=%d y=%d z=%d\n"
            a1 = s4;
            a2 = s3;
            a3 = v0;
            jal(ctx, 0x38F1ECu, gen::fn_printf_005225a8);
            lw(a0, s1, 296);
            jal(ctx, 0x38F1F8u, gen::fn_sub_318B00_00318b00);
            lbu(a1, v0, 0);
            lbu(a0, v0, 1);
            lbu(v1, v0, 2);
            lbu(v0, v0, 3);
            sb(a1, s0, unit::kColor);
            sb(a0, s0, 85);
            sb(v1, s0, 86);
            sb(v0, s0, 87);
        }
        // 0x0038f24c
        charge(ctx, 18);
        a0 = s2;
        a1 = 3;
        jal(ctx, 0x38F254u, gen::fn_sub_3B5550_003b5550);
        s4 = v0;
        a0 = s2;
        a1 = 3;
        jal(ctx, 0x38F268u, gen::fn_sub_3B5430_003b5430);
        s1 = v0;
        a0 = 0x6A0000;
        a0 = addiu(a0, 3040);  // "npc unit no=%d \n"
        a1 = s4;
        jal(ctx, 0x38F280u, gen::fn_printf_005225a8);
        s3 = 0;
        for (;;) {
            // 0x0038f374
            charge(ctx, 3);
            v0 = slt(s3, s4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0038f294
            charge(ctx, 56);
            a0 = s1;
            jal(ctx, 0x38F298u, gen::fn_sub_38D910_0038d910);
            a0 = 1;
            a1 = s5;
            lhu(a2, s1, 0);
            a3 = s1;
            jal(ctx, 0x38F2B0u, gen::fn_sub_361DD0_00361dd0);
            s0 = v0;
            v1 = si(-1);
            sw(v1, v0, 8);
            sw(zero, v0, 20);
            lwc1(f2, s1, 4);
            lwc1(f1, s1, 8);
            lwc1(f0, s1, 12);
            swc1(f2, v0, 60);
            swc1(f1, v0, 64);
            swc1(f0, v0, 68);
            lwc1(f2, s1, 16);
            lwc1(f1, s1, 20);
            lwc1(f0, s1, 24);
            swc1(f2, v0, 72);
            swc1(f1, v0, 76);
            swc1(f0, v0, 80);
            lwc1(f12, s1, 4);
            jal(ctx, 0x38F2FCu, gen::fn_fptodp_00530da0);
            s6 = v0;
            lwc1(f12, s1, 8);
            jal(ctx, 0x38F30Cu, gen::fn_fptodp_00530da0);
            s7 = v0;
            lwc1(f12, s1, 12);
            jal(ctx, 0x38F31Cu, gen::fn_fptodp_00530da0);
            a0 = 0x6A0000;
            a0 = addiu(a0, 3024);  // "x=%d y=%d z=%d\n"
            a1 = s6;
            a2 = s7;
            a3 = v0;
            jal(ctx, 0x38F338u, gen::fn_printf_005225a8);
            lw(a0, s1, 296);
            jal(ctx, 0x38F344u, gen::fn_sub_318B00_00318b00);
            lbu(a1, v0, 0);
            lbu(a0, v0, 1);
            lbu(v1, v0, 2);
            lbu(v0, v0, 3);
            sb(a1, s0, unit::kColor);
            sb(a0, s0, 85);
            sb(v1, s0, 86);
            sb(v0, s0, 87);
            s3 = addiu(s3, 1);
            lw(s1, s1, 248);
        }
        // 0x0038f380
        charge(ctx, 6);
        a0 = s2;
        a1 = 5;
        jal(ctx, 0x38F388u, gen::fn_sub_3B5430_003b5430);
        if (v0 != 0) {
            // 0x0038f398
            charge(ctx, 19);
            lwc1(f3, v0, 256);
            lwc1(f2, v0, 260);
            lwc1(f1, v0, 264);
            lwc1(f0, v0, 268);
            swc1(f3, s5, work::kFieldCam);
            swc1(f2, s5, 2164);
            swc1(f1, s5, 2168);
            swc1(f0, s5, 2172);
            lwc1(f3, v0, 272);
            lwc1(f2, v0, 276);
            lwc1(f1, v0, 280);
            lwc1(f0, v0, 284);
            swc1(f3, s5, 2176);
            swc1(f2, s5, 2180);
            swc1(f1, s5, 2184);
            swc1(f0, s5, 2188);
            a3 = addiu(v0, 288);
            a2 = addiu(s5, 2192);
            a1 = 8;
            for (;;) {
                // 0x0038f3e4
                charge(ctx, 9);
                lw(a0, a3, 0);
                lw(v1, a3, 4);
                a3 = addiu(a3, 8);
                a1 = addiu(a1, -1);
                sw(a0, a2, 0);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0038f408 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0038F440 sub_38F440 -- 1148 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtKeyLoadParams] (pm, key, row): copies row `row` of the PM key table into the key: the condition (+12..+19 ->
// kCondFlag..), the parameters (+20.. or the version-4 rows' +8..) into +16..+48, the extra word +52; clamps the
// fade speeds of command 2; for path-move keys allocates and copies the 304-byte path (sub_38D790, line 1761).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38F440(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038f440
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    t3 = sll(a2, 4);
    v1 = subu(t3, a2);
    v1 = sll(v1, 2);
    lw(a3, a0, 156);
    t2 = addu(v1, a3);
    lh(t1, t2, 12);
    lh(t0, t2, 14);
    lh(a3, t2, 16);
    lh(t2, t2, 18);
    sh(t1, sp, 0x48);
    sh(t0, sp, 0x4A);
    sh(a3, sp, 0x4C);
    sh(t2, sp, 0x4E);
    lh(t1, sp, 0x48);
    lh(t0, sp, 0x4A);
    lh(a3, sp, 0x4C);
    sh(t1, a1, 8);
    sh(t0, a1, 10);
    sh(a3, a1, 12);
    sh(t2, a1, 14);
    lw(a0, a0, 132);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f4d4
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f4c0
        charge(ctx, 5);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, t3);
        a0 = addiu(a0, 8);
    }
    // 0x0038f4e0
    charge(ctx, 7);
    lb(a0, a0, 0);
    sb(a0, s1, key::kCmd);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f514
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f4fc
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f520
    charge(ctx, 7);
    lw(a0, a0, 4);
    sw(a0, s1, key::kArg20);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f554
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f53c
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f560
    charge(ctx, 7);
    lw(a0, a0, 8);
    sw(a0, s1, 24);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f594
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f57c
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f5a0
    charge(ctx, 7);
    lw(a0, a0, 12);
    sw(a0, s1, 28);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f5d4
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f5bc
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f5e0
    charge(ctx, 7);
    lw(a0, a0, 16);
    sw(a0, s1, 32);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f614
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f5fc
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f620
    charge(ctx, 7);
    lw(a0, a0, 20);
    sw(a0, s1, 36);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f654
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f63c
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f660
    charge(ctx, 7);
    lw(a0, a0, 24);
    sw(a0, s1, 40);
    lw(a0, s2, pm::kHeader);
    lw(a1, a0, 20);
    a0 = 4;
    if (a1 != a0) {
        // 0x0038f694
        charge(ctx, 3);
        lw(a0, s2, pm::kKeys);
        a0 = addu(a0, v1);
        a0 = addiu(a0, 20);
    } else {
        // 0x0038f67c
        charge(ctx, 6);
        a1 = sll(a2, 4);
        lw(a0, s2, pm::kKeys4);
        a0 = addu(a0, a1);
        a0 = addiu(a0, 8);
    }
    // 0x0038f6a0
    charge(ctx, 6);
    lw(a0, a0, 28);
    sw(a0, s1, 44);
    lw(a1, s1, key::kOwnerType);
    a0 = 1;
    if (a1 != a0) {
        // 0x0038f6c4
        charge(ctx, 3);
        a0 = 48;
        if (a1 == a0) {
            // 0x0038f6d0
            charge(ctx, 5);
            lw(a0, s2, pm::kHeader);
            lw(a1, a0, 20);
            a0 = 4;
            if (a1 != a0) {
                // 0x0038f6fc
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                a0 = addu(a0, v1);
                a0 = addiu(a0, 20);
            } else {
                // 0x0038f6e4
                charge(ctx, 6);
                a1 = sll(a2, 4);
                lw(a0, s2, pm::kKeys4);
                a0 = addu(a0, a1);
                a0 = addiu(a0, 8);
            }
            // 0x0038f708
            charge(ctx, 2);
            lw(a0, a0, 32);
            sw(a0, s1, 48);
        }
    } else {
        // 0x0038f6b8
        charge(ctx, 3);
        sw(zero, s1, 48);
    }
    // 0x0038f710
    charge(ctx, 5);
    lw(a0, s2, pm::kHeader);
    lw(a3, a0, 20);
    at = slti(a3, 12);
    if (at == 0) {
        // 0x0038f774
        charge(ctx, 3);
        a0 = 4;
        if (a3 != a0) {
            // 0x0038f798
            charge(ctx, 3);
            lw(a0, s2, pm::kKeys);
            a0 = addu(a0, v1);
            a0 = addiu(a0, 20);
        } else {
            // 0x0038f780
            charge(ctx, 6);
            a1 = sll(a2, 4);
            lw(a0, s2, pm::kKeys4);
            a0 = addu(a0, a1);
            a0 = addiu(a0, 8);
        }
        // 0x0038f7a4
        charge(ctx, 2);
        lw(a0, a0, 36);
        sw(a0, s1, 52);
    } else {
        // 0x0038f724
        charge(ctx, 4);
        lw(a1, s1, key::kOwnerType);
        a0 = 1;
        if (a1 == a0) {
            // 0x0038f734
            charge(ctx, 3);
            a0 = 4;
            if (a3 != a0) {
                // 0x0038f758
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                a0 = addu(a0, v1);
                a0 = addiu(a0, 20);
            } else {
                // 0x0038f740
                charge(ctx, 6);
                a1 = sll(a2, 4);
                lw(a0, s2, pm::kKeys4);
                a0 = addu(a0, a1);
                a0 = addiu(a0, 8);
            }
            // 0x0038f764
            charge(ctx, 4);
            lw(a0, a0, 32);
            sw(a0, s1, 52);
        }
    }
    // 0x0038f7ac
    charge(ctx, 6);
    a0 = si(-1);
    sw(a0, s1, key::kName);
    lb(a2, s1, key::kCmd);
    a0 = 2;
    if (a2 == a0) {
        // 0x0038f858
        charge(ctx, 4);
        lh(a0, s1, 40);
        v1 = slti(a0, 10);
        if (v1 == 0) {
            // 0x0038f868
            charge(ctx, 3);
            at = slti(a0, 501);
            if (at == 0) {
                goto L_0038f874;
            }
            goto L_0038f87c;
        }
    L_0038f874:
        charge(ctx, 2);
        v1 = 100;
        sh(v1, s1, 40);
    L_0038f87c:
        charge(ctx, 4);
        lh(a0, s1, 42);
        v1 = slti(a0, 10);
        if (v1 == 0) {
            // 0x0038f88c
            charge(ctx, 3);
            at = slti(a0, 501);
            if (at == 0) {
                goto L_0038f898;
            }
            // 0x0038f8a0 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
    L_0038f898:
        charge(ctx, 2);
        v1 = 100;
        sh(v1, s1, 42);
    } else {
        // 0x0038f7c4
        charge(ctx, 3);
        a1 = 1;
        if (a2 == a1) {
            // 0x0038f7d8
            charge(ctx, 3);
            lb(a0, s1, key::kArg20);
            if (a0 == a1) {
                // 0x0038f7ec
                charge(ctx, 9);
                lw(v0, s2, pm::kKeys);
                v0 = addu(v1, v0);
                lh(s0, v0, 10);
                a0 = s1;
                jal(ctx, 0x38F7FCu, gen::fn_sub_38D790_0038d790);
                lw(v0, s1, key::kPath);
                if (v0 == 0) {
                    // 0x0038f810
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 2816);  // "mt_evtLoadSave.c"
                    a1 = 1761;
                    jal(ctx, 0x38F81Cu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0038f824
                charge(ctx, 13);
                v0 = sll(s0, 3);
                v0 = addu(v0, s0);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                v1 = sll(v0, 4);
                lw(v0, s2, pm::kPaths);
                a1 = addu(v0, v1);
                lw(a0, s1, key::kPath);
                a2 = 304;
                jal(ctx, 0x38F848u, gen::fn_memcpy_00521250);
            } else {
                // 0x0038f7e4
                charge(ctx, 2);
            }
        } else {
            // 0x0038f7d0
            charge(ctx, 2);
        }
    }
    // 0x0038f8a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0038F8C0 sub_38F8C0 -- 336 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtLoadUnitKeys] (pm, work, unit, unitId): for every PM key row of unit type 1 whose unit id (+8) matches, creates
// the key (sub_361350) and loads it (sub_38F440).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38F8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038f8c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    if (s4 != 0) {
        // 0x0038f8f0
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_0038f8f8;
        }
        // 0x0038f900
        charge(ctx, 3);
        s0 = a3 & 0xFFFF;
        if (s0 != 0) {
            // 0x0038f90c
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0038f9dc
                charge(ctx, 4);
                lw(v1, s4, pm::kKeyCount);
                v1 = slt(s1, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0038f918
                charge(ctx, 5);
                lw(v1, s4, pm::kHeader);
                lw(v1, v1, 20);
                a0 = 4;
                if (v1 != a0) {
                    // 0x0038f944
                    charge(ctx, 6);
                    a0 = sll(s1, 4);
                    a0 = subu(a0, s1);
                    a1 = sll(a0, 2);
                    lw(a0, s4, pm::kKeys);
                    a0 = addu(a0, a1);
                    lhu(a0, a0, 0);
                } else {
                    // 0x0038f92c
                    charge(ctx, 6);
                    a1 = sll(s1, 4);
                    lw(a0, s4, pm::kKeys4);
                    a0 = addu(a0, a1);
                    lhu(a0, a0, 0);
                }
                // 0x0038f95c
                charge(ctx, 4);
                a1 = a0 & 0xFFFF;
                a0 = 1;
                if (a1 == a0) {
                    // 0x0038f96c
                    charge(ctx, 8);
                    lw(a1, s4, pm::kKeys);
                    a2 = sll(s1, 4);
                    a0 = subu(a2, s1);
                    a0 = sll(a0, 2);
                    a1 = addu(a1, a0);
                    lhu(a0, a1, 8);
                    if (s0 == a0) {
                        // 0x0038f98c
                        charge(ctx, 3);
                        v0 = 4;
                        if (v1 != v0) {
                            // 0x0038f9ac
                            charge(ctx, 1);
                            lhu(v0, a1, 2);
                        } else {
                            // 0x0038f998
                            charge(ctx, 5);
                            lw(v0, s4, pm::kKeys4);
                            v0 = addu(v0, a2);
                            lhu(v0, v0, 2);
                        }
                        // 0x0038f9b0
                        charge(ctx, 10);
                        a1 = v0 & 0xFFFF;
                        a0 = s2;
                        a2 = s3;
                        jal(ctx, 0x38F9BCu, gen::fn_sub_361350_00361350);
                        a0 = s4;
                        a1 = v0;
                        a2 = s1;
                        jal(ctx, 0x38F9D0u, gen::fn_sub_38F440_0038f440);
                    }
                }
                // 0x0038f9d8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
        }
        // 0x0038f9ec (the shared epilogue, written out on this path)
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
L_0038f8f8:
    charge(ctx, 2);
    // 0x0038f9ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0038FA10 sub_38FA10 -- 1436 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateCameraUnit] (pm, work): sets up the event camera models 0x1E58 / 0x1E59 (sub_3B5F70 when missing) at the
// default pose (0x6A0BF8) through sub_3BB450, selects camera 0, creates the type-33 unit and its keys from the PM
// rows of type 33.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38FA10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x0038fa10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    v1 = addiu(sp, 0x70);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x0038fa40
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0038fa5c
    charge(ctx, 10);
    v0 = 0x6A0000;
    ld(v1, v0, 3064);  // 0x6A0BF8
    v0 = 0x6A0000;
    lwc1(f0, v0, 3072);  // 0x6A0C00
    sd(v1, sp, 0x60);
    swc1(f0, sp, 0x68);
    jal(ctx, 0x38FA74u, gen::fn_sub_3B5D00_003b5d00);
    if (v0 != 0) {
        // 0x0038fa84
        charge(ctx, 6);
        a0 = 7768;
        jal(ctx, 0x38FA88u, gen::fn_sub_3B5D10_003b5d10);
        s1 = v0;
        if (s1 != 0) {
            // 0x0038fac4
            charge(ctx, 1);
            lhu(s0, s1, 0);
        } else {
            // 0x0038fa9c
            charge(ctx, 10);
            a0 = 600;
            jal(ctx, 0x38FAA0u, gen::fn_sub_3B5F70_003b5f70);
            s0 = v0 & 0xFFFF;
            a0 = s0;
            jal(ctx, 0x38FAB0u, gen::fn_sub_3B5D10_003b5d10);
            s1 = v0;
        }
        // 0x0038fac8
        charge(ctx, 30);
        a0 = s0;
        a1 = addiu(sp, 0x70);
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x38FAD4u, gen::fn_sub_3B78B0_003b78b0);
        sw(zero, s1, 260);
        a0 = s0;
        jal(ctx, 0x38FAE4u, gen::fn_sub_3B5D10_003b5d10);
        sw(v0, s2, work::kCamUnit);
        v0 = 0x44610000;
        mtc1(v0, f12);
        v0 = 0x42340000;
        mtc1(v0, f13);
        mtc1(zero, f14);
        a0 = addiu(sp, 0x70);
        mov_s(f15, f14);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x38FB10u, gen::fn_sub_3BB450_003bb450);
        a0 = s0;
        a1 = addiu(sp, 0x80);
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x38FB24u, gen::fn_sub_3B78B0_003b78b0);
        a0 = 7769;
        jal(ctx, 0x38FB30u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x0038fb64
            charge(ctx, 1);
            lhu(s0, v0, 0);
        } else {
            // 0x0038fb40
            charge(ctx, 9);
            a0 = 601;
            jal(ctx, 0x38FB44u, gen::fn_sub_3B5F70_003b5f70);
            s0 = v0 & 0xFFFF;
            a0 = s0;
            jal(ctx, 0x38FB54u, gen::fn_sub_3B5D10_003b5d10);
        }
        // 0x0038fb68
        charge(ctx, 16);
        a0 = s0;
        a1 = addiu(sp, 0x80);
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x38FB74u, gen::fn_sub_3B78B0_003b78b0);
        a0 = s0;
        jal(ctx, 0x38FB80u, gen::fn_sub_3B5D10_003b5d10);
        sw(zero, v0, 260);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x38FB94u, gen::fn_sub_38A0C0_0038a0c0);
        lw(v1, s2, work::kCamUnit);
        if (v1 != 0) {
            // 0x0038fba8
            charge(ctx, 25);
            a0 = 33;
            a1 = s2;
            lhu(a2, v1, 0);
            a3 = 0;
            jal(ctx, 0x38FBB8u, gen::fn_sub_361DD0_00361dd0);
            s0 = v0;
            v1 = si(-1);
            sw(v1, v0, 8);
            sw(zero, v0, 20);
            lwc1(f2, sp, 0x80);
            lwc1(f1, sp, 0x84);
            lwc1(f0, sp, 0x88);
            swc1(f2, v0, 60);
            swc1(f1, v0, 64);
            swc1(f0, v0, 68);
            lwc1(f2, sp, 0x60);
            lwc1(f1, sp, 0x64);
            lwc1(f0, sp, 0x68);
            swc1(f2, v0, 72);
            swc1(f1, v0, 76);
            swc1(f0, v0, 80);
            s1 = 0;
            for (;;) {
                // 0x0038ff7c
                charge(ctx, 4);
                lw(v1, s3, pm::kKeyCount);
                v1 = slt(s1, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0038fc0c
                charge(ctx, 5);
                lw(v1, s3, pm::kHeader);
                lw(a1, v1, 20);
                v1 = 4;
                if (a1 != v1) {
                    // 0x0038fc38
                    charge(ctx, 6);
                    v1 = sll(s1, 4);
                    v1 = subu(v1, s1);
                    a0 = sll(v1, 2);
                    lw(v1, s3, pm::kKeys);
                    v1 = addu(v1, a0);
                    lhu(v1, v1, 0);
                } else {
                    // 0x0038fc20
                    charge(ctx, 6);
                    a0 = sll(s1, 4);
                    lw(v1, s3, pm::kKeys4);
                    v1 = addu(v1, a0);
                    lhu(v1, v1, 0);
                }
                // 0x0038fc50
                charge(ctx, 4);
                a0 = v1 & 0xFFFF;
                v1 = 33;
                if (a0 == v1) {
                    // 0x0038fc60
                    charge(ctx, 3);
                    v0 = 4;
                    if (a1 != v0) {
                        // 0x0038fc84
                        charge(ctx, 6);
                        v0 = sll(s1, 4);
                        v0 = subu(v0, s1);
                        v1 = sll(v0, 2);
                        lw(v0, s3, pm::kKeys);
                        v0 = addu(v0, v1);
                        lhu(v0, v0, 2);
                    } else {
                        // 0x0038fc6c
                        charge(ctx, 6);
                        v1 = sll(s1, 4);
                        lw(v0, s3, pm::kKeys4);
                        v0 = addu(v0, v1);
                        lhu(v0, v0, 2);
                    }
                    // 0x0038fc9c
                    charge(ctx, 30);
                    a1 = v0 & 0xFFFF;
                    a0 = s0;
                    a2 = s2;
                    jal(ctx, 0x38FCA8u, gen::fn_sub_361350_00361350);
                    t0 = sll(s1, 4);
                    v1 = subu(t0, s1);
                    v1 = sll(v1, 2);
                    lw(a0, s3, pm::kKeys);
                    a3 = addu(a0, v1);
                    lh(a2, a3, 12);
                    lh(a1, a3, 14);
                    lh(a0, a3, 16);
                    lh(a3, a3, 18);
                    sh(a2, sp, 0x58);
                    sh(a1, sp, 0x5A);
                    sh(a0, sp, 0x5C);
                    sh(a3, sp, 0x5E);
                    lh(a2, sp, 0x58);
                    lh(a1, sp, 0x5A);
                    lh(a0, sp, 0x5C);
                    sh(a2, v0, 8);
                    sh(a1, v0, 10);
                    sh(a0, v0, 12);
                    sh(a3, v0, 14);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fd28
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        lhu(a0, a0, 4);
                    } else {
                        // 0x0038fd14
                        charge(ctx, 5);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, t0);
                        lhu(a0, a0, 4);
                    }
                    // 0x0038fd34
                    charge(ctx, 6);
                    sh(a0, v0, 2);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fd64
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fd4c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fd70
                    charge(ctx, 7);
                    lw(a0, a0, 0);
                    sw(a0, v0, 16);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fda4
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fd8c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fdb0
                    charge(ctx, 7);
                    lw(a0, a0, 4);
                    sw(a0, v0, 20);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fde4
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fdcc
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fdf0
                    charge(ctx, 7);
                    lw(a0, a0, 8);
                    sw(a0, v0, 24);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fe24
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fe0c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fe30
                    charge(ctx, 7);
                    lw(a0, a0, 12);
                    sw(a0, v0, 28);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fe64
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fe4c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fe70
                    charge(ctx, 7);
                    lw(a0, a0, 16);
                    sw(a0, v0, 32);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fea4
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fe8c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038feb0
                    charge(ctx, 7);
                    lw(a0, a0, 20);
                    sw(a0, v0, 36);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038fee4
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038fecc
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038fef0
                    charge(ctx, 7);
                    lw(a0, a0, 24);
                    sw(a0, v0, 40);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038ff24
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        a0 = addu(a0, v1);
                        a0 = addiu(a0, 20);
                    } else {
                        // 0x0038ff0c
                        charge(ctx, 6);
                        a1 = sll(s1, 4);
                        lw(a0, s3, pm::kKeys4);
                        a0 = addu(a0, a1);
                        a0 = addiu(a0, 8);
                    }
                    // 0x0038ff30
                    charge(ctx, 7);
                    lw(a0, a0, 28);
                    sw(a0, v0, 44);
                    lw(a0, s3, pm::kHeader);
                    lw(a1, a0, 20);
                    a0 = 4;
                    if (a1 != a0) {
                        // 0x0038ff64
                        charge(ctx, 3);
                        lw(a0, s3, pm::kKeys);
                        v1 = addu(a0, v1);
                        v1 = addiu(v1, 20);
                    } else {
                        // 0x0038ff4c
                        charge(ctx, 6);
                        a0 = sll(s1, 4);
                        lw(v1, s3, pm::kKeys4);
                        v1 = addu(v1, a0);
                        v1 = addiu(v1, 8);
                    }
                    // 0x0038ff70
                    charge(ctx, 2);
                    lw(v1, v1, 32);
                    sw(v1, v0, 48);
                }
                // 0x0038ff78
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
        }
    }
    // 0x0038ff8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0038FFB0 sub_38FFB0 -- 776 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [evtCreateVolumeUnits] (pm, work): two type-35 units (channels 0 / 1) and their keys from the PM rows of type 35
// (channel from the row's +21; invalid commands >= 4 cleared).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_38FFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0038ffb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {
        // 0x00390014
        charge(ctx, 3);
        v1 = slti(s0, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0038ffdc
        charge(ctx, 14);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        s3 = addiu(v0, 88);
        a0 = 35;
        a1 = s1;
        jal(ctx, 0x38FFF0u, gen::fn_sub_361CA0_00361ca0);
        sw(v0, s3, 0);
        v1 = si(-1);
        sw(v1, v0, 8);
        sw(zero, v0, 20);
        sw(zero, v0, 56);
        sw(s0, v0, 4);
        s0 = addiu(s0, 1);
    }
    // 0x00390020
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00390288
        charge(ctx, 4);
        lw(v1, s2, pm::kKeyCount);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0039002c
        charge(ctx, 5);
        lw(v1, s2, pm::kHeader);
        lw(v1, v1, 20);
        a0 = 4;
        if (v1 != a0) {
            // 0x00390058
            charge(ctx, 6);
            a0 = sll(s0, 4);
            a0 = subu(a0, s0);
            a1 = sll(a0, 2);
            lw(a0, s2, pm::kKeys);
            a0 = addu(a0, a1);
            lhu(a0, a0, 0);
        } else {
            // 0x00390040
            charge(ctx, 6);
            a1 = sll(s0, 4);
            lw(a0, s2, pm::kKeys4);
            a0 = addu(a0, a1);
            lhu(a0, a0, 0);
        }
        // 0x00390070
        charge(ctx, 4);
        a1 = a0 & 0xFFFF;
        a0 = 35;
        if (a1 == a0) {
            // 0x00390080
            charge(ctx, 3);
            v0 = 4;
            if (v1 != v0) {
                // 0x003900a4
                charge(ctx, 6);
                v0 = sll(s0, 4);
                v0 = subu(v0, s0);
                a0 = sll(v0, 2);
                lw(v0, s2, pm::kKeys);
                v0 = addu(v0, a0);
                v0 = addiu(v0, 20);
            } else {
                // 0x0039008c
                charge(ctx, 6);
                a0 = sll(s0, 4);
                lw(v0, s2, pm::kKeys4);
                v0 = addu(v0, a0);
                v0 = addiu(v0, 8);
            }
            // 0x003900bc
            charge(ctx, 6);
            lb(v0, v0, 1);
            v0 = sll(v0, 2);
            a0 = addu(v0, sp);
            v0 = 4;
            if (v1 != v0) {
                // 0x003900ec
                charge(ctx, 6);
                v0 = sll(s0, 4);
                v0 = subu(v0, s0);
                v1 = sll(v0, 2);
                lw(v0, s2, pm::kKeys);
                v0 = addu(v0, v1);
                lhu(v0, v0, 2);
            } else {
                // 0x003900d4
                charge(ctx, 6);
                v1 = sll(s0, 4);
                lw(v0, s2, pm::kKeys4);
                v0 = addu(v0, v1);
                lhu(v0, v0, 2);
            }
            // 0x00390104
            charge(ctx, 30);
            a1 = v0 & 0xFFFF;
            lw(a0, a0, 88);
            a2 = s1;
            jal(ctx, 0x390110u, gen::fn_sub_361350_00361350);
            t0 = sll(s0, 4);
            v1 = subu(t0, s0);
            v1 = sll(v1, 2);
            lw(a0, s2, pm::kKeys);
            a3 = addu(a0, v1);
            lh(a2, a3, 12);
            lh(a1, a3, 14);
            lh(a0, a3, 16);
            lh(a3, a3, 18);
            sh(a2, sp, 0x50);
            sh(a1, sp, 0x52);
            sh(a0, sp, 0x54);
            sh(a3, sp, 0x56);
            lh(a2, sp, 0x50);
            lh(a1, sp, 0x52);
            lh(a0, sp, 0x54);
            sh(a2, v0, 8);
            sh(a1, v0, 10);
            sh(a0, v0, 12);
            sh(a3, v0, 14);
            lw(a0, s2, pm::kHeader);
            lw(a1, a0, 20);
            a0 = 4;
            if (a1 != a0) {
                // 0x00390190
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                a0 = addu(a0, v1);
                a0 = addiu(a0, 20);
            } else {
                // 0x0039017c
                charge(ctx, 5);
                lw(a0, s2, pm::kKeys4);
                a0 = addu(a0, t0);
                a0 = addiu(a0, 8);
            }
            // 0x0039019c
            charge(ctx, 7);
            lw(a0, a0, 0);
            sw(a0, v0, 16);
            lw(a0, s2, pm::kHeader);
            lw(a1, a0, 20);
            a0 = 4;
            if (a1 != a0) {
                // 0x003901d0
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                a0 = addu(a0, v1);
                a0 = addiu(a0, 20);
            } else {
                // 0x003901b8
                charge(ctx, 6);
                a1 = sll(s0, 4);
                lw(a0, s2, pm::kKeys4);
                a0 = addu(a0, a1);
                a0 = addiu(a0, 8);
            }
            // 0x003901dc
            charge(ctx, 7);
            lw(a0, a0, 4);
            sw(a0, v0, 20);
            lw(a0, s2, pm::kHeader);
            lw(a1, a0, 20);
            a0 = 4;
            if (a1 != a0) {
                // 0x00390210
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                a0 = addu(a0, v1);
                a0 = addiu(a0, 20);
            } else {
                // 0x003901f8
                charge(ctx, 6);
                a1 = sll(s0, 4);
                lw(a0, s2, pm::kKeys4);
                a0 = addu(a0, a1);
                a0 = addiu(a0, 8);
            }
            // 0x0039021c
            charge(ctx, 7);
            lw(a0, a0, 8);
            sw(a0, v0, 24);
            lw(a0, s2, pm::kHeader);
            lw(a1, a0, 20);
            a0 = 4;
            if (a1 != a0) {
                // 0x00390250
                charge(ctx, 3);
                lw(a0, s2, pm::kKeys);
                v1 = addu(a0, v1);
                v1 = addiu(v1, 20);
            } else {
                // 0x00390238
                charge(ctx, 6);
                a0 = sll(s0, 4);
                lw(v1, s2, pm::kKeys4);
                v1 = addu(v1, a0);
                v1 = addiu(v1, 8);
            }
            // 0x0039025c
            charge(ctx, 6);
            lw(v1, v1, 12);
            sw(v1, v0, 28);
            lb(v1, v0, 16);
            v1 = slti(v1, 4);
            if (v1 == 0) {
                // 0x00390274
                charge(ctx, 4);
                sw(zero, v0, 16);
                sw(zero, v0, 20);
                sw(zero, v0, 24);
                sw(zero, v0, 28);
            }
        }
        // 0x00390284
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00390298
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game
